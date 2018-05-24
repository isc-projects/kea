// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <dhcpsrv/parsers/simple_parser4.h>
#include <dhcpsrv/parsers/simple_parser6.h>
#include <eval/eval_context.h>
#include <asiolink/io_address.h>
#include <asiolink/io_error.h>

#include <boost/foreach.hpp>
#include <algorithm>

using namespace isc::data;
using namespace isc::asiolink;
using namespace std;

/// @file client_class_def_parser.cc
///
/// @brief Method implementations for client class definition parsing

namespace isc {
namespace dhcp {

// ********************** ExpressionParser ****************************

void
ExpressionParser::parse(ExpressionPtr& expression,
                        ConstElementPtr expression_cfg,
                        uint16_t family,
                        EvalContext::CheckDefined check_defined) {
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
        EvalContext eval_ctx(family == AF_INET ? Option::V4 : Option::V6,
                             check_defined);
        eval_ctx.parseString(value);
        expression.reset(new Expression());
        *expression = eval_ctx.expression;
    } catch (const std::exception& ex) {
        // Append position if there is a failure.
        isc_throw(DhcpConfigError,
                  "expression: [" << value
                  <<  "] error: " << ex.what() << " at ("
                  <<  expression_cfg->getPosition() << ")");
    }
}

// ********************** ClientClassDefParser ****************************

void
ClientClassDefParser::parse(ClientClassDictionaryPtr& class_dictionary,
                            ConstElementPtr class_def_cfg,
                            uint16_t family) {
    // name is now mandatory
    std::string name = getString(class_def_cfg, "name");
    if (name.empty()) {
        isc_throw(DhcpConfigError,
                  "not empty parameter 'name' is required "
                  << getPosition("name", class_def_cfg) << ")");
    }

    // Parse matching expression
    ExpressionPtr match_expr;
    ConstElementPtr test_cfg = class_def_cfg->get("test");
    std::string test;
    if (test_cfg) {
        ExpressionParser parser;
        using std::placeholders::_1;
        auto check_defined =
            std::bind(isClientClassDefined, class_dictionary, _1);
        parser.parse(match_expr, test_cfg, family, check_defined);
        test = test_cfg->stringValue();
    }

    // Parse option def
    CfgOptionDefPtr defs(new CfgOptionDef());
    ConstElementPtr option_defs = class_def_cfg->get("option-def");
    if (option_defs) {
        // Apply defaults
        SimpleParser::setListDefaults(option_defs,
            family == AF_INET ?
                SimpleParser4::OPTION4_DEF_DEFAULTS :
                SimpleParser6::OPTION6_DEF_DEFAULTS);

        OptionDefParser parser;
        BOOST_FOREACH(ConstElementPtr option_def, option_defs->listValue()) {
            OptionDefinitionTuple def;
                
            def = parser.parse(option_def);
            // Verify if the defition is for an option which are
            // in a deferred processing list.
            if (!LibDHCP::shouldDeferOptionUnpack(def.second,
                                                  def.first->getCode())) {
                isc_throw(DhcpConfigError,
                          "Not allowed option definition for code '"
                          << def.first->getCode() << "' in space '"
                          << def.second << "' at ("
                          << option_def->getPosition() << ")");
            }
            try {
                defs->add(def.first, def.second);
            } catch (const std::exception& ex) {
                // Sanity check: it should never happen
                isc_throw(DhcpConfigError, ex.what() << " ("
                          << option_def->getPosition() << ")");
            }
        }
    }

    // Parse option data
    CfgOptionPtr options(new CfgOption());
    ConstElementPtr option_data = class_def_cfg->get("option-data");
    if (option_data) {
        OptionDataListParser opts_parser(family, defs);
        opts_parser.parse(options, option_data);
    }

    // Parse user context
    ConstElementPtr user_context = class_def_cfg->get("user-context");

    // Let's try to parse the only-if-required flag
    bool required = false;
    if (class_def_cfg->contains("only-if-required")) {
        required = getBoolean(class_def_cfg, "only-if-required");
    }

    // Let's try to parse the next-server field
    IOAddress next_server("0.0.0.0");
    if (class_def_cfg->contains("next-server")) {
        std::string next_server_txt = getString(class_def_cfg, "next-server");
        try {
            next_server = IOAddress(next_server_txt);
        } catch (const IOError& ex) {
            isc_throw(DhcpConfigError,
                      "Invalid next-server value specified: '"
                      << next_server_txt << "' ("
                      << getPosition("next-server", class_def_cfg) << ")");
        }

        if (next_server.getFamily() != AF_INET) {
            isc_throw(DhcpConfigError, "Invalid next-server value: '"
                      << next_server_txt << "', must be IPv4 address ("
                      << getPosition("next-server", class_def_cfg) << ")");
        }

        if (next_server.isV4Bcast()) {
            isc_throw(DhcpConfigError, "Invalid next-server value: '"
                      << next_server_txt << "', must not be a broadcast ("
                      << getPosition("next-server", class_def_cfg) << ")");
        }
    }

    // Let's try to parse server-hostname
    std::string sname;
    if (class_def_cfg->contains("server-hostname")) {
        sname = getString(class_def_cfg, "server-hostname");

        if (sname.length() >= Pkt4::MAX_SNAME_LEN) {
            isc_throw(DhcpConfigError, "server-hostname must be at most "
                      << Pkt4::MAX_SNAME_LEN - 1 << " bytes long, it is "
                      << sname.length() << " ("
                      << getPosition("server-hostname", class_def_cfg) << ")");
        }
    }

    // Let's try to parse boot-file-name
    std::string filename;
    if (class_def_cfg->contains("boot-file-name")) {
        filename = getString(class_def_cfg, "boot-file-name");

        if (filename.length() > Pkt4::MAX_FILE_LEN) {
            isc_throw(DhcpConfigError, "boot-file-name must be at most "
                      << Pkt4::MAX_FILE_LEN - 1 << " bytes long, it is "
                      << filename.length() << " ("
                      << getPosition("boot-file-name", class_def_cfg) << ")");
        }

    }

    // Add the client class definition
    try {
        class_dictionary->addClass(name, match_expr, test, required, options,
                                   defs, user_context, next_server, sname,
                                   filename);
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, "Can't add class: " << ex.what()
                  << " (" << class_def_cfg->getPosition() << ")");
    }
}

// ****************** ClientClassDefListParser ************************

ClientClassDictionaryPtr
ClientClassDefListParser::parse(ConstElementPtr client_class_def_list,
                                uint16_t family) {
    ClientClassDictionaryPtr dictionary(new ClientClassDictionary());
    BOOST_FOREACH(ConstElementPtr client_class_def,
                  client_class_def_list->listValue()) {
        ClientClassDefParser parser;
        parser.parse(dictionary, client_class_def, family);
    }
    return (dictionary);
}

} // end of namespace isc::dhcp
} // end of namespace isc
