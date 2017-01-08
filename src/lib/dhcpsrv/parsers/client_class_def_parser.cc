// Copyright (C) 2015-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <eval/eval_context.h>
#include <asiolink/io_address.h>
#include <asiolink/io_error.h>

#include <boost/foreach.hpp>

using namespace isc::data;
using namespace isc::asiolink;
using namespace std;

/// @file client_class_def_parser.cc
///
/// @brief Method implementations for client class definition parsing

namespace isc {
namespace dhcp {

// ********************** ExpressionParser ****************************

ExpressionParser::ExpressionParser(ExpressionPtr& expression)
    : local_expression_(ExpressionPtr()), expression_(expression) {
}

void
ExpressionParser::parse(ConstElementPtr expression_cfg, uint16_t family) {
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
        EvalContext eval_ctx(family == AF_INET ? Option::V4 : Option::V6);
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

    // Success so commit.
    expression_ = local_expression_;
}

// ********************** ClientClassDefParser ****************************

ClientClassDefParser::ClientClassDefParser(ClientClassDictionaryPtr& class_dictionary)
    : match_expr_(ExpressionPtr()),
      options_(new CfgOption()),
      class_dictionary_(class_dictionary) {
}

void
ClientClassDefParser::parse(ConstElementPtr class_def_cfg, uint16_t family) {

    try {
        std::string name;
        std::string next_server_txt = "0.0.0.0";
        std::string sname;
        std::string filename;

        // Parse the elements that make up the client class definition.
        BOOST_FOREACH(ConfigPair param, class_def_cfg->mapValue()) {
            std::string entry(param.first);
            ConstElementPtr value(param.second);

            if (entry == "name") {
                name = value->stringValue();

            } else if (entry == "test") {
                ExpressionParser parser(match_expr_);
                parser.parse(value, family);
                
            } else if (entry == "option-data") {
                OptionDataListParser opts_parser(family);
                opts_parser.parse(options_, value);

            } else if (entry == "next-server") {
                next_server_txt = value->stringValue();

            } else if (entry == "server-hostname") {
                sname = value->stringValue();

            } else if (entry == "boot-file-name") {
                filename = value->stringValue();

            } else {
                isc_throw(DhcpConfigError, "invalid parameter '" << entry
                          << "' (" << value->getPosition() << ")");
            }
        }

        // Make name mandatory?

        // Let's parse the next-server field
        IOAddress next_server("0.0.0.0");
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

        // Let's try to parse server-hostname
        if (sname.length() >= Pkt4::MAX_SNAME_LEN) {
            isc_throw(DhcpConfigError, "server-hostname must be at most "
                      << Pkt4::MAX_SNAME_LEN - 1 << " bytes long, it is "
                      << sname.length());
        }

        // Let's try to parse boot-file-name
        if (filename.length() > Pkt4::MAX_FILE_LEN) {
            isc_throw(DhcpConfigError, "boot-file-name must be at most "
                      << Pkt4::MAX_FILE_LEN - 1 << " bytes long, it is "
                      << filename.length());
        }

        // Add the client class definition
        class_dictionary_->addClass(name, match_expr_, options_, next_server,
                                    sname, filename);
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what()
                  << " (" << class_def_cfg->getPosition() << ")");
    }
}

// ****************** ClientClassDefListParser ************************

ClientClassDefListParser::ClientClassDefListParser()
    : local_dictionary_(new ClientClassDictionary()) {
}

void
ClientClassDefListParser::parse(ConstElementPtr client_class_def_list,
                                uint16_t family) {
    BOOST_FOREACH(ConstElementPtr client_class_def,
                  client_class_def_list->listValue()) {
        ClientClassDefParser parser(local_dictionary_);
        parser.parse(client_class_def, family);
    }
    // Success so commit
    CfgMgr::instance().getStagingCfg()->setClientClassDictionary(local_dictionary_);
}

} // end of namespace isc::dhcp
} // end of namespace isc
