// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <boost/foreach.hpp>

using namespace isc::data;

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
    // Here is where we would call bison parser with our string
    // For now we'll just create an expression with a string token
    // containing the expression text
    try {
        if (expression_cfg->getType() != Element::string) {
            isc_throw(TypeError, "expression value must be a string");
        } 
        std::string expression_text = expression_cfg->str();
        TokenPtr dummy(new TokenString(expression_text));
        local_expression_.reset(new Expression());
        local_expression_->push_back(dummy);
    } catch (const std::exception& ex) {
        // Append position if there is a failure.
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << expression_cfg->getPosition() << ")");
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
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << class_def_cfg->getPosition() << ")");
    }

    try {
        // an OptionCollectionPtr
        class_dictionary_->addClass(name, match_expr_, options_);
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
