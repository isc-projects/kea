// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <eval/eval_context.h>
#include <asiolink/io_address.h>
#include <asiolink/io_error.h>

#include <boost/foreach.hpp>

using namespace isc::data;
using namespace isc::asiolink;
using namespace std;

/// @file client_class_def.cc
///
/// @brief Method implementations for client class definition parsing

namespace isc {
namespace dhcp {

// ********************** ExpressionParser ****************************

ExpressionParser::ExpressionParser(const std::string&,
    ExpressionPtr& expression, ParserContextPtr global_context)
    : local_expression_(ExpressionPtr()), expression_(expression),
      global_context_(global_context) {
}

void
ExpressionParser::build(ConstElementPtr expression_cfg) {
    if (expression_cfg->getType() != Element::string) {
        isc_throw(DhcpConfigError, "expression ["
            << expression_cfg->str() << "] must be a string, at ("
            << expression_cfg->getPosition() << ")");
    }

    // Get the expression's text via getValue() as the text returned
    // by str() enclosed in quotes.
    std::string value;
    expression_cfg->getValue(value);
    try {
        EvalContext eval_ctx(global_context_->universe_);
        eval_ctx.parseString(value);
        local_expression_.reset(new Expression());
        *local_expression_ = eval_ctx.expression;
    } catch (const std::exception& ex) {
        // Append position if there is a failure.
        isc_throw(DhcpConfigError,
                  "expression: [" << value
                  <<  "] error: " << ex.what() << " at ("
                  <<  expression_cfg->getPosition() << ")");
    }
}

void
ExpressionParser::commit() {
    expression_ = local_expression_;
}

// ********************** ClientClassDefParser ****************************

ClientClassDefParser::ClientClassDefParser(const std::string&,
    ClientClassDictionaryPtr& class_dictionary, ParserContextPtr global_context)
    : string_values_(new StringStorage()),
      match_expr_(ExpressionPtr()),
      options_(new CfgOption()),
      class_dictionary_(class_dictionary),
      global_context_(global_context) {
}

void
ClientClassDefParser::build(ConstElementPtr class_def_cfg) {

    // Parse the elements that make up the option definition.
    BOOST_FOREACH(ConfigPair param, class_def_cfg->mapValue()) {
        std::string entry(param.first);
        ParserPtr parser;
        if (entry == "name") {
            StringParserPtr str_parser(new StringParser(entry, string_values_));
            parser = str_parser;
        } else if (entry == "test") {
            ExpressionParserPtr exp_parser(new ExpressionParser(entry,
                                                                match_expr_,
                                                                global_context_));
            parser = exp_parser;
        } else if (entry == "option-data") {
            OptionDataListParserPtr opts_parser;
            uint16_t family = (global_context_->universe_ == Option::V4 ?
                                                             AF_INET : AF_INET6);

            opts_parser.reset(new OptionDataListParser(entry, options_, family));
            parser = opts_parser;
        } else if (entry == "next-server") {
            StringParserPtr str_parser(new StringParser(entry, string_values_));
            parser = str_parser;
        } else if (entry == "server-hostname") {
            StringParserPtr str_parser(new StringParser(entry, string_values_));
            parser = str_parser;

        } else if (entry == "boot-file-name") {
            StringParserPtr str_parser(new StringParser(entry, string_values_));
            parser = str_parser;
        } else {
            isc_throw(DhcpConfigError, "invalid parameter '" << entry
                      << "' (" << param.second->getPosition() << ")");
        }

        parser->build(param.second);
        parser->commit();
    }

    std::string name;
    try {
        name = string_values_->getParam("name");

        // Let's parse the next-server field
        IOAddress next_server("0.0.0.0");
        string next_server_txt = string_values_->getOptionalParam("next-server", "0.0.0.0");
        try {
            next_server = IOAddress(next_server_txt);
        } catch (const IOError& ex) {
            isc_throw(DhcpConfigError, "Invalid next-server value specified: '"
                      << next_server_txt);
        }

        if (next_server.getFamily() != AF_INET) {
            isc_throw(DhcpConfigError, "Invalid next-server value: '"
                      << next_server_txt << "', must be IPv4 address");
        }

        if (next_server.isV4Bcast()) {
            isc_throw(DhcpConfigError, "Invalid next-server value: '"
                      << next_server_txt << "', must not be a broadcast");
        }

        // Let's try to parse sname
        string sname = string_values_->getOptionalParam("server-hostname", "");
        if (sname.length() >= Pkt4::MAX_SNAME_LEN) {
            isc_throw(DhcpConfigError, "server-hostname must be at most "
                      << Pkt4::MAX_SNAME_LEN - 1 << " bytes long, it is "
                      << sname.length());
        }

        string filename = string_values_->getOptionalParam("boot-file-name", "");
        if (filename.length() > Pkt4::MAX_FILE_LEN) {
            isc_throw(DhcpConfigError, "boot-file-name must be at most "
                      << Pkt4::MAX_FILE_LEN - 1 << " bytes long, it is "
                      << filename.length());
        }

        // an OptionCollectionPtr
        class_dictionary_->addClass(name, match_expr_, options_, next_server,
                                    sname, filename);
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what()
                  << " (" << class_def_cfg->getPosition() << ")");
    }
}

// ****************** ClientClassDefListParser ************************

ClientClassDefListParser::ClientClassDefListParser(const std::string&,
                                                   ParserContextPtr
                                                   global_context)
    : local_dictionary_(new ClientClassDictionary()),
      global_context_(global_context) {
}

void
ClientClassDefListParser::build(ConstElementPtr client_class_def_list) {
    if (!client_class_def_list) {
        isc_throw(DhcpConfigError, "parser error: a pointer to a list of"
                  << " client class definitions is NULL ("
                  << client_class_def_list->getPosition() << ")");
    }

    BOOST_FOREACH(ConstElementPtr client_class_def,
                  client_class_def_list->listValue()) {
        boost::shared_ptr<ClientClassDefParser>
            parser(new ClientClassDefParser("client-class-def",
                                            local_dictionary_,
                                            global_context_));
        parser->build(client_class_def);
    }
}

void
ClientClassDefListParser::commit() {
    CfgMgr::instance().getStagingCfg()->setClientClassDictionary(local_dictionary_);
}

} // end of namespace isc::dhcp
} // end of namespace isc
