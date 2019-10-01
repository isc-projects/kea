// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <flex_option.h>
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
using namespace std;

namespace isc {
namespace flex_option {

FlexOptionImpl::OptionConfig::OptionConfig(uint16_t code)
    : code_(code), action_(NONE) {
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
    if (!code_elem && !name_elem) {
        isc_throw(BadValue, "'code' or 'name' must be specified: "
                  << option->str());
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
        string space;
        if (family == AF_INET) {
            space = DHCP4_OPTION_SPACE;
        } else {
            space = DHCP6_OPTION_SPACE;
        }
        OptionDefinitionPtr def = LibDHCP::getOptionDef(space, name);
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
            isc_throw(BadValue, "option '" << name << "' has code "
                      << def->getCode() << " but 'code' is " << code);
        }
        code = def->getCode();
    }

    if (option_config_map_.count(code)) {
        isc_throw(BadValue, "option " << code << " was already specified");
    }

    Option::Universe universe;
    if (family == AF_INET) {
        universe = Option::V4;
    } else {
        universe = Option::V6;
    }

    OptionConfigPtr opt_cfg(new OptionConfig(code));
    ConstElementPtr add_elem = option->get("add");
    if (add_elem) {
        if (add_elem->getType() != Element::string) {
            isc_throw(BadValue, "'add' must be a string: "
                      << add_elem->str());
        }
        string add = add_elem->stringValue();
        if (add.empty()) {
            isc_throw(BadValue, "'add' must not be empty");
        }
        opt_cfg->setAction(ADD);
        opt_cfg->setText(add);
        try {
            EvalContext eval_ctx(universe);
            eval_ctx.parseString(add, EvalContext::PARSER_STRING);
            ExpressionPtr expr(new Expression(eval_ctx.expression));
            opt_cfg->setExpr(expr);
        } catch (const std::exception& ex) {
            isc_throw(BadValue, "can't parse add expression ["
                      << add << "] error: " << ex.what());
        }
    }
    ConstElementPtr supersede_elem = option->get("supersede");
    if (supersede_elem) {
        if (supersede_elem->getType() != Element::string) {
            isc_throw(BadValue, "'supersede' must be a string: "
                      << supersede_elem->str());
        }
        string supersede = supersede_elem->stringValue();
        if (supersede.empty()) {
            isc_throw(BadValue, "'supersede' must not be empty");
        }
        if (opt_cfg->getAction() != NONE) {
            isc_throw(BadValue, "multiple actions: " << option->str());
        }
        opt_cfg->setAction(SUPERSEDE);
        opt_cfg->setText(supersede);
        try {
            EvalContext eval_ctx(universe);
            eval_ctx.parseString(supersede, EvalContext::PARSER_STRING);
            ExpressionPtr expr(new Expression(eval_ctx.expression));
            opt_cfg->setExpr(expr);
        } catch (const std::exception& ex) {
            isc_throw(BadValue, "can't parse supersede expression ["
                      << supersede << "] error: " << ex.what());
        }
    }
    ConstElementPtr remove_elem = option->get("remove");
    if (remove_elem) {
        if (remove_elem->getType() != Element::string) {
            isc_throw(BadValue, "'remove' must be a string: "
                      << remove_elem->str());
        }
        string remove = remove_elem->stringValue();
        if (remove.empty()) {
            isc_throw(BadValue, "'remove' must not be empty");
        }
        if (opt_cfg->getAction() != NONE) {
            isc_throw(BadValue, "multiple actions: " << option->str());
        }
        opt_cfg->setAction(REMOVE);
        opt_cfg->setText(remove);
        try {
            EvalContext eval_ctx(universe);
            eval_ctx.parseString(remove, EvalContext::PARSER_BOOL);
            ExpressionPtr expr(new Expression(eval_ctx.expression));
            opt_cfg->setExpr(expr);
        } catch (const std::exception& ex) {
            isc_throw(BadValue, "can't parse remove expression ["
                      << remove << "] error: " << ex.what());
        }
    }

    if (opt_cfg->getAction() == NONE) {
        isc_throw(BadValue, "no action: " << option->str());
    }
    option_config_map_[code] = opt_cfg;
}

} // end of namespace flex_option
} // end of namespace isc
