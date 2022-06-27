// Copyright (C) 2015-2022 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/parsers/simple_parser4.h>
#include <dhcpsrv/parsers/simple_parser6.h>
#include <eval/eval_context.h>
#include <asiolink/io_address.h>
#include <asiolink/io_error.h>

#include <boost/foreach.hpp>
#include <algorithm>
#include <sstream>

using namespace isc::data;
using namespace isc::asiolink;
using namespace isc::util;
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
                            uint16_t family,
                            bool append_error_position,
                            bool check_dependencies) {
    // name is now mandatory, so let's deal with it first.
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
    bool depend_on_known = false;
    if (test_cfg) {
        ExpressionParser parser;
        auto check_defined =
            [&class_dictionary, &depend_on_known, check_dependencies]
            (const ClientClass& cclass) {
                return (!check_dependencies || isClientClassDefined(class_dictionary,
                                                                    depend_on_known,
                                                                    cclass));
        };
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

        OptionDefParser parser(family);
        BOOST_FOREACH(ConstElementPtr option_def, option_defs->listValue()) {
            OptionDefinitionPtr def = parser.parse(option_def);

            // Verify if the definition is for an option which is in a deferred
            // processing list.
            if (!LibDHCP::shouldDeferOptionUnpack(def->getOptionSpaceName(),
                                                  def->getCode())) {
                isc_throw(DhcpConfigError,
                          "Not allowed option definition for code '"
                          << def->getCode() << "' in space '"
                          << def->getOptionSpaceName() << "' at ("
                          << option_def->getPosition() << ")");
            }
            try {
                defs->add(def);
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
        auto opts_parser = createOptionDataListParser(family, defs);
        opts_parser->parse(options, option_data);
    }

    // Parse user context
    ConstElementPtr user_context = class_def_cfg->get("user-context");
    if (user_context) {
        if (user_context->getType() != Element::map) {
            isc_throw(isc::dhcp::DhcpConfigError, "User context has to be a map ("
                      << user_context->getPosition() << ")");
        }
    }

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

    // Parse valid lifetime triplet.
    Triplet<uint32_t> valid_lft = parseIntTriplet(class_def_cfg, "valid-lifetime");

    Triplet<uint32_t> preferred_lft;
    if (family != AF_INET) {
        // Parse preferred lifetime triplet.
        preferred_lft = parseIntTriplet(class_def_cfg, "preferred-lifetime");
    }

    // Sanity checks on built-in classes
    for (auto bn : builtinNames) {
        if (name == bn) {
            if (required) {
                isc_throw(DhcpConfigError, "built-in class '" << name
                          << "' only-if-required flag must be false");
            }
            if (!test.empty()) {
                isc_throw(DhcpConfigError, "built-in class '" << name
                          << "' test expression must be empty");
            }
        }
    }

    // Sanity checks on DROP
    if (name == "DROP") {
        if (required) {
            isc_throw(DhcpConfigError, "special class '" << name
                      << "' only-if-required flag must be false");
        }
        // depend_on_known is now allowed
    }

    // Add the client class definition
    try {
        class_dictionary->addClass(name, match_expr, test, required,
                                   depend_on_known, options, defs,
                                   user_context, next_server, sname, filename,
                                   valid_lft, preferred_lft);
    } catch (const std::exception& ex) {
        std::ostringstream s;
        s << "Can't add class: " << ex.what();
        // Append position of the error in JSON string if required.
        if (append_error_position) {
            s << " (" << class_def_cfg->getPosition() << ")";
        }
        isc_throw(DhcpConfigError, s.str());
    }
}

void
ClientClassDefParser::checkParametersSupported(const ConstElementPtr& class_def_cfg,
                                               const uint16_t family) {
    // Make sure that the client class definition is stored in a map.
    if (!class_def_cfg || (class_def_cfg->getType() != Element::map)) {
        isc_throw(DhcpConfigError, "client class definition is not a map");
    }

    // Common v4 and v6 parameters supported for the client class.
    static std::set<std::string> supported_params = { "name",
                                                      "test",
                                                      "option-data",
                                                      "user-context",
                                                      "only-if-required",
                                                      "valid-lifetime",
                                                      "min-valid-lifetime",
                                                      "max-valid-lifetime" };


    // The v4 client class supports additional parameters.
    static std::set<std::string> supported_params_v4 = { "option-def",
                                                         "next-server",
                                                         "server-hostname",
                                                         "boot-file-name" };

    // The v6 client class supports additional parameters.
    static std::set<std::string> supported_params_v6 = { "preferred-lifetime",
                                                         "min-preferred-lifetime",
                                                         "max-preferred-lifetime" };

    // Iterate over the specified parameters and check if they are all supported.
    for (auto name_value_pair : class_def_cfg->mapValue()) {
        if ((supported_params.count(name_value_pair.first) > 0) ||
            ((family == AF_INET) && (supported_params_v4.count(name_value_pair.first) > 0)) ||
            ((family != AF_INET) && (supported_params_v6.count(name_value_pair.first) > 0))) {
            continue;
        } else {
            isc_throw(DhcpConfigError, "unsupported client class parameter '"
                      << name_value_pair.first << "'");
        }
    }
}

boost::shared_ptr<OptionDataListParser>
ClientClassDefParser::createOptionDataListParser(const uint16_t address_family,
                                                 CfgOptionDefPtr cfg_option_def) const {
    auto parser = boost::make_shared<OptionDataListParser>(address_family, cfg_option_def);
    return (parser);
}

// ****************** ClientClassDefListParser ************************

ClientClassDictionaryPtr
ClientClassDefListParser::parse(ConstElementPtr client_class_def_list,
                                uint16_t family, bool check_dependencies) {
    ClientClassDictionaryPtr dictionary(new ClientClassDictionary());
    BOOST_FOREACH(ConstElementPtr client_class_def,
                  client_class_def_list->listValue()) {
        ClientClassDefParser parser;
        parser.parse(dictionary, client_class_def, family, true, check_dependencies);
    }
    return (dictionary);
}

} // end of namespace isc::dhcp
} // end of namespace isc
