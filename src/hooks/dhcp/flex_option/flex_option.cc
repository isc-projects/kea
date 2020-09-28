// Copyright (C) 2019-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <flex_option.h>
#include <flex_option_log.h>
#include <util/strutil.h>
#include <cc/simple_parser.h>
#include <dhcp/dhcp4.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/cfgmgr.h>
#include <eval/eval_context.h>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::eval;
using namespace isc::flex_option;
using namespace isc::log;
using namespace isc::util;
using namespace std;

namespace {

/// @brief Parse an action.
///
/// @param option The option element.
/// @param opt_cfg The option configuration.
/// @param name The action name.
/// @param action The action.
/// @param parser_type The type of the parser of the expression.
void
parseAction(ConstElementPtr option,
            FlexOptionImpl::OptionConfigPtr opt_cfg,
            Option::Universe universe,
            const string& name,
            FlexOptionImpl::Action action,
            EvalContext::ParserType parser_type) {
    ConstElementPtr elem = option->get(name);
    if (elem) {
        if (elem->getType() != Element::string) {
            isc_throw(BadValue, "'" << name << "' must be a string: "
                      << elem->str());
        }
        string expr_text = elem->stringValue();
        if (expr_text.empty()) {
            isc_throw(BadValue, "'" << name << "' must not be empty");
        }
        if (opt_cfg->getAction() != FlexOptionImpl::NONE) {
            isc_throw(BadValue, "multiple actions: " << option->str());
        }
        opt_cfg->setAction(action);
        opt_cfg->setText(expr_text);
        try {
            EvalContext eval_ctx(universe);
            eval_ctx.parseString(expr_text, parser_type);
            ExpressionPtr expr(new Expression(eval_ctx.expression));
            opt_cfg->setExpr(expr);
        } catch (const std::exception& ex) {
            isc_throw(BadValue, "can't parse " << name << " expression ["
                      << expr_text << "] error: " << ex.what());
        }
    }
}

} // end of anonymous namespace

namespace isc {
namespace flex_option {

FlexOptionImpl::OptionConfig::OptionConfig(uint16_t code,
                                           OptionDefinitionPtr def)
    : code_(code), def_(def), action_(NONE) {
}

FlexOptionImpl::OptionConfig::~OptionConfig() {
}

FlexOptionImpl::FlexOptionImpl() {
}

FlexOptionImpl::~FlexOptionImpl() {
    option_config_map_.clear();
}

void
FlexOptionImpl::configure(ConstElementPtr options) {
    if (!options) {
        isc_throw(BadValue, "'options' parameter is mandatory");
    }
    if (options->getType() != Element::list) {
        isc_throw(BadValue, "'options' parameter must be a list");
    }
    if (options->empty()) {
        return;
    }
    for (auto option : options->listValue()) {
        parseOptionConfig(option);
    }
}

void
FlexOptionImpl::parseOptionConfig(ConstElementPtr option) {
    uint16_t family = CfgMgr::instance().getFamily();
    if (!option) {
        isc_throw(BadValue, "null option element");
    }
    if (option->getType() != Element::map) {
        isc_throw(BadValue, "option element is not a map");
    }
    ConstElementPtr code_elem = option->get("code");
    ConstElementPtr name_elem = option->get("name");
    ConstElementPtr csv_format_elem = option->get("csv-format");
    OptionDefinitionPtr def;
    if (!code_elem && !name_elem) {
        isc_throw(BadValue, "'code' or 'name' must be specified: "
                  << option->str());
    }
    string space;
    Option::Universe universe;
    if (family == AF_INET) {
        space = DHCP4_OPTION_SPACE;
        universe = Option::V4;
    } else {
        space = DHCP6_OPTION_SPACE;
        universe = Option::V6;
    }
    uint16_t code;
    if (code_elem) {
        if (code_elem->getType() != Element::integer) {
            isc_throw(BadValue, "'code' must be an integer: "
                      << code_elem->str());
        }
        int64_t value = code_elem->intValue();
        int64_t max_code;
        if (family == AF_INET) {
            max_code = numeric_limits<uint8_t>::max();
        } else {
            max_code = numeric_limits<uint16_t>::max();
        }
        if ((value < 0) || (value > max_code)) {
            isc_throw(OutOfRange, "invalid 'code' value " << value
                      << " not in [0.." << max_code << "]");
        }
        if (family == AF_INET) {
            if (value == DHO_PAD) {
                isc_throw(BadValue,
                          "invalid 'code' value 0: reserved for PAD");
            } else if (value == DHO_END) {
                isc_throw(BadValue,
                          "invalid 'code' value 255: reserved for END");
            }
        } else {
            if (value == 0) {
                isc_throw(BadValue, "invalid 'code' value 0: reserved");
            }
        }
        code = static_cast<uint16_t>(value);
    }
    if (name_elem) {
        if (name_elem->getType() != Element::string) {
            isc_throw(BadValue, "'name' must be a string: "
                      << name_elem->str());
        }
        string name = name_elem->stringValue();
        if (name.empty()) {
            isc_throw(BadValue, "'name' must not be empty");
        }
        def = LibDHCP::getOptionDef(space, name);
        if (!def) {
            def = LibDHCP::getRuntimeOptionDef(space, name);
        }
        if (!def) {
            def = LibDHCP::getLastResortOptionDef(space, name);
        }
        if (!def) {
            isc_throw(BadValue, "no known '" << name << "' option in '"
                      << space << "' space");
        }
        if (code_elem && (def->getCode() != code)) {
            isc_throw(BadValue, "option '" << name << "' is defined as code: "
                      << def->getCode() << ", not the specified code: "
                      << code);
        }
        code = def->getCode();
    }
    if (option_config_map_.count(code)) {
        isc_throw(BadValue, "option " << code << " was already specified");
    }

    bool csv_format = false;
    if (csv_format_elem) {
        if (csv_format_elem->getType() != Element::boolean) {
            isc_throw(BadValue, "'csv-format' must be a boolean: "
                      << csv_format_elem->str());
        }
        csv_format = csv_format_elem->boolValue();
    }

    if (!csv_format) {
        // No definition means no csv format.
        if (def) {
            def.reset();
        }
    } else if (!def) {
        // Definition is required with csv format.
        def = isc::dhcp::LibDHCP::getOptionDef(space, code);
        if (!def) {
            def = isc::dhcp::LibDHCP::getRuntimeOptionDef(space, code);
        }
        if (!def) {
            def = isc::dhcp::LibDHCP::getLastResortOptionDef(space, code);
        }
        if (!def) {
            isc_throw(BadValue, "no known option with code '" << code
                      << "' in '" << space << "' space");
        }
    }

    OptionConfigPtr opt_cfg(new OptionConfig(code, def));

    // opt_cfg initial action is NONE.
    parseAction(option, opt_cfg, universe,
                "add", ADD, EvalContext::PARSER_STRING);
    parseAction(option, opt_cfg, universe,
                "supersede", SUPERSEDE, EvalContext::PARSER_STRING);
    parseAction(option, opt_cfg, universe,
                "remove", REMOVE, EvalContext::PARSER_BOOL);

    if (opt_cfg->getAction() == NONE) {
        isc_throw(BadValue, "no action: " << option->str());
    }

    option_config_map_[code] = opt_cfg;
}

void
FlexOptionImpl::logAction(Action action, uint16_t code,
                          const string& value) const {
    if (action == NONE) {
        return;
    }
    if (action == REMOVE) {
        LOG_DEBUG(flex_option_logger, DBGLVL_TRACE_BASIC,
                  FLEX_OPTION_PROCESS_REMOVE)
            .arg(code);
        return;
    }
    ostringstream repr;
    if (str::isPrintable(value)) {
        repr << "'" << value << "'";
    } else {
        repr << "0x" << hex;
        for (const char& ch : value) {
            repr << setw(2) << setfill('0') << static_cast<unsigned>(ch);
        }
    }
    if (action == SUPERSEDE) {
        LOG_DEBUG(flex_option_logger, DBGLVL_TRACE_BASIC,
                  FLEX_OPTION_PROCESS_SUPERSEDE)
            .arg(code)
            .arg(repr.str());
    } else {
        LOG_DEBUG(flex_option_logger, DBGLVL_TRACE_BASIC,
                  FLEX_OPTION_PROCESS_ADD)
            .arg(code)
            .arg(repr.str());
    }
}

} // end of namespace flex_option
} // end of namespace isc
