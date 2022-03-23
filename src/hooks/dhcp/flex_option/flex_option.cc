// Copyright (C) 2019-2022 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option_vendor.h>
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
/// @note Shared code for option and sub-option.
///
/// @param option The option element.
/// @param opt_cfg The option configuration.
/// @param universe The universe.
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

const SimpleKeywords FlexOptionImpl::OPTION_PARAMETERS = {
    { "code",          Element::integer },
    { "name",          Element::string },
    { "space",         Element::string },
    { "csv-format",    Element::boolean },
    { "add",           Element::string },
    { "supersede",     Element::string },
    { "remove",        Element::string },
    { "sub-options",   Element::list },
    { "client-class",  Element::string },
    { "comment",       Element::string }
};

const SimpleKeywords FlexOptionImpl::SUB_OPTION_PARAMETERS = {
    { "code",              Element::integer },
    { "name",              Element::string },
    { "space",             Element::string },
    { "csv-format",        Element::boolean },
    { "add",               Element::string },
    { "supersede",         Element::string },
    { "remove",            Element::string },
    { "container-add",     Element::boolean },
    { "container-remove",  Element::boolean },
    { "client-class",      Element::string },
    { "comment",           Element::string }
};

FlexOptionImpl::OptionConfig::OptionConfig(uint16_t code,
                                           OptionDefinitionPtr def)
    : code_(code), def_(def), action_(NONE), class_("") {
}

FlexOptionImpl::OptionConfig::~OptionConfig() {
}

FlexOptionImpl::SubOptionConfig::SubOptionConfig(uint16_t code,
                                                 OptionDefinitionPtr def,
                                                 OptionConfigPtr container)
    : OptionConfig(code, def), container_(container), vendor_id_(0),
      container_action_(NONE) {
    if (!container) {
        isc_throw(Unexpected, "null container?");
    }
}

FlexOptionImpl::SubOptionConfig::~SubOptionConfig() {
}

FlexOptionImpl::FlexOptionImpl() {
}

FlexOptionImpl::~FlexOptionImpl() {
    sub_option_config_map_.clear();
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
    // See SimpleParser::checkKeywords
    for (auto entry : option->mapValue()) {
        if (OPTION_PARAMETERS.count(entry.first) == 0) {
            isc_throw(BadValue, "unknown parameter '" << entry.first << "'");
        }
        Element::types expected = OPTION_PARAMETERS.at(entry.first);
        if (entry.second->getType() == expected) {
            continue;
        }
        isc_throw(BadValue, "'" << entry.first << "' must be "
                  << (expected == Element::integer ? "an " : "a ")
                  << Element::typeToName(expected)
                  << ": " << entry.second->str());
    }
    ConstElementPtr code_elem = option->get("code");
    ConstElementPtr name_elem = option->get("name");
    ConstElementPtr space_elem = option->get("space");
    ConstElementPtr csv_format_elem = option->get("csv-format");
    ConstElementPtr class_elem = option->get("client-class");
    ConstElementPtr sub_options = option->get("sub-options");
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
    if (space_elem) {
        space = space_elem->stringValue();
        if (!OptionSpace::validateName(space)) {
            isc_throw(BadValue, "'" << space << "' is not a valid space name");
        }
    }
    uint16_t code;
    if (code_elem) {
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
        if (space == DHCP4_OPTION_SPACE) {
            if (value == DHO_PAD) {
                isc_throw(BadValue,
                          "invalid 'code' value 0: reserved for PAD");
            } else if (value == DHO_END) {
                isc_throw(BadValue,
                          "invalid 'code' value 255: reserved for END");
            }
        } else if (space == DHCP6_OPTION_SPACE) {
            if (value == 0) {
                isc_throw(BadValue, "invalid 'code' value 0: reserved");
            }
        }
        code = static_cast<uint16_t>(value);
    }
    OptionDefinitionPtr def;
    if (name_elem) {
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

    bool csv_format = false;
    if (csv_format_elem) {
        csv_format = csv_format_elem->boolValue();
    }

    if (!csv_format && !sub_options) {
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
        if (!def && csv_format) {
            isc_throw(BadValue, "no known option with code '" << code
                      << "' in '" << space << "' space");
        }
    }

    OptionConfigPtr opt_cfg(new OptionConfig(code, def));
    if (class_elem) {
        opt_cfg->setClass(class_elem->stringValue());
    }

    // opt_cfg initial action is NONE.
    if (sub_options) {
        string action;
        if (option->contains("add")) {
            action = "add";
        } else if (option->contains("supersede")) {
            action = "supersede";
        } else if (option->contains("remove")) {
            action = "remove";
        }
        if (!action.empty()) {
            isc_throw(BadValue, "'sub-options' and '" << action << "' are "
                      << "incompatible in the same entry");
        }
        parseSubOptions(sub_options, opt_cfg, universe);
    } else {
        parseAction(option, opt_cfg, universe,
                    "add", ADD, EvalContext::PARSER_STRING);
        parseAction(option, opt_cfg, universe,
                    "supersede", SUPERSEDE, EvalContext::PARSER_STRING);
        parseAction(option, opt_cfg, universe,
                    "remove", REMOVE, EvalContext::PARSER_BOOL);

        if (opt_cfg->getAction() == NONE) {
            isc_throw(BadValue, "no action: " << option->str());
        }

        // The [] operator creates the item if it does not exist before
        // returning a reference to it.
        OptionConfigList& opt_lst = option_config_map_[code];
        opt_lst.push_back(opt_cfg);
    }
}

void
FlexOptionImpl::parseSubOptions(ConstElementPtr sub_options,
                                OptionConfigPtr opt_cfg,
                                Option::Universe universe) {
    for (ConstElementPtr sub_option : sub_options->listValue()) {
        parseSubOption(sub_option, opt_cfg, universe);
    }
}

void
FlexOptionImpl::parseSubOption(ConstElementPtr sub_option,
                               OptionConfigPtr opt_cfg,
                               Option::Universe universe) {
    if (!sub_option) {
        isc_throw(BadValue, "null sub-option element");
    }
    if (sub_option->getType() != Element::map) {
        isc_throw(BadValue, "sub-option element is not a map");
    }
    // See SimpleParser::checkKeywords
    for (auto entry : sub_option->mapValue()) {
        if (SUB_OPTION_PARAMETERS.count(entry.first) == 0) {
            isc_throw(BadValue, "unknown parameter '" << entry.first << "'");
        }
        Element::types expected = SUB_OPTION_PARAMETERS.at(entry.first);
        if (entry.second->getType() == expected) {
            continue;
        }
        isc_throw(BadValue, "'" << entry.first << "' must be "
                  << (expected == Element::integer ? "an " : "a ")
                  << Element::typeToName(expected)
                  << ": " << entry.second->str());
    }
    ConstElementPtr code_elem = sub_option->get("code");
    ConstElementPtr name_elem = sub_option->get("name");
    ConstElementPtr space_elem = sub_option->get("space");
    ConstElementPtr csv_format_elem = sub_option->get("csv-format");
    ConstElementPtr class_elem = sub_option->get("client-class");
    if (!code_elem && !name_elem) {
        isc_throw(BadValue, "'code' or 'name' must be specified: "
                  << sub_option->str());
    }
    string space;
    if (space_elem) {
        space = space_elem->stringValue();
        if (!OptionSpace::validateName(space)) {
            isc_throw(BadValue, "'" << space << "' is not a valid space name");
        }
    } else {
        OptionDefinitionPtr opt_def = opt_cfg->getOptionDef();
        if (!opt_def) {
            isc_throw(BadValue, "container is not defined: can't get space");
        }
        space = opt_def->getEncapsulatedSpace();
        if (space.empty()) {
            isc_throw(BadValue, "container does not encapsulate a space");
        }
    }
    uint32_t vendor_id = LibDHCP::optionSpaceToVendorId(space);
    uint16_t code;
    if (code_elem) {
        int64_t value = code_elem->intValue();
        int64_t max_code;
        if (universe == Option::V4) {
            max_code = numeric_limits<uint8_t>::max();
        } else {
            max_code = numeric_limits<uint16_t>::max();
        }
        if ((value < 0) || (value > max_code)) {
            isc_throw(OutOfRange, "invalid 'code' value " << value
                      << " not in [0.." << max_code << "]");
        }
        code = static_cast<uint16_t>(value);
    }
    OptionDefinitionPtr def;
    if (name_elem) {
        string name = name_elem->stringValue();
        if (name.empty()) {
            isc_throw(BadValue, "'name' must not be empty");
        }
        def = LibDHCP::getOptionDef(space, name);
        if (!def && vendor_id) {
            def = LibDHCP::getVendorOptionDef(universe, vendor_id, name);
        }
        if (!def) {
            def = LibDHCP::getRuntimeOptionDef(space, name);
        }
        if (!def) {
            isc_throw(BadValue, "no known '" << name << "' sub-option in '"
                      << space << "' space");
        }
        if (code_elem && (def->getCode() != code)) {
            isc_throw(BadValue, "sub-option '" << name
                      << "' is defined as code: " << def->getCode()
                      << ", not the specified code: " << code);
        }
        code = def->getCode();
    }

    bool csv_format = false;
    if (csv_format_elem) {
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
        if (!def && vendor_id) {
            def = LibDHCP::getVendorOptionDef(universe, vendor_id, code);
        }
        if (!def) {
            def = isc::dhcp::LibDHCP::getRuntimeOptionDef(space, code);
        }
        if (!def) {
            isc_throw(BadValue, "no known sub-option with code '" << code
                      << "' in '" << space << "' space");
        }
    }

    SubOptionConfigPtr sub_cfg(new SubOptionConfig(code, def, opt_cfg));
    if (vendor_id) {
        if (((universe == Option::V4) &&
             (opt_cfg->getCode() == DHO_VIVSO_SUBOPTIONS)) ||
            ((universe == Option::V6) &&
             (opt_cfg->getCode() == D6O_VENDOR_OPTS))) {
            sub_cfg->setVendorId(vendor_id);
        }
    }
    if (class_elem) {
        sub_cfg->setClass(class_elem->stringValue());
    }

    // sub_cfg initial action is NONE.
    parseAction(sub_option, sub_cfg, universe,
                "add", ADD, EvalContext::PARSER_STRING);
    parseAction(sub_option, sub_cfg, universe,
                "supersede", SUPERSEDE, EvalContext::PARSER_STRING);
    parseAction(sub_option, sub_cfg, universe,
                "remove", REMOVE, EvalContext::PARSER_BOOL);

    if (sub_cfg->getAction() == NONE) {
        isc_throw(BadValue, "no action: " << sub_option->str());
    }

    ConstElementPtr container_add = sub_option->get("container-add");
    ConstElementPtr container_remove = sub_option->get("container-remove");
    if ((sub_cfg->getAction() == ADD) || (sub_cfg->getAction() == SUPERSEDE)) {
        sub_cfg->setContainerAction(ADD);
        if (container_add && !container_add->boolValue()) {
            sub_cfg->setContainerAction(NONE);
        }
    } else if (sub_cfg->getAction() == REMOVE) {
        sub_cfg->setContainerAction(REMOVE);
        if (container_remove && !container_remove->boolValue()) {
            sub_cfg->setContainerAction(NONE);
        }
    }

    // The [] operator creates the item if it does not exist before
    // returning a reference to it.
    uint16_t opt_code = opt_cfg->getCode();
    SubOptionConfigMap& sub_map = sub_option_config_map_[opt_code];
    if (sub_map.count(code)) {
        isc_throw(BadValue, "sub-option " << code << " of option " << opt_code
                  << " was already specified");
    }
    sub_map[code] = sub_cfg;
}

void
FlexOptionImpl::logClass(const ClientClass& client_class, uint16_t code) {
    LOG_DEBUG(flex_option_logger, DBGLVL_TRACE_BASIC,
              FLEX_OPTION_PROCESS_CLIENT_CLASS)
        .arg(client_class)
        .arg(code);
    return;
}

void
FlexOptionImpl::logAction(Action action, uint16_t code,
                          const string& value) {
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

void
FlexOptionImpl::logAction(Action action, uint16_t code,
                          uint32_t vendor_id) {
    if (action == SUPERSEDE) {
        LOG_DEBUG(flex_option_logger, DBGLVL_TRACE_BASIC,
                  FLEX_OPTION_PROCESS_SUPERSEDE)
            .arg(code)
            .arg(vendor_id);
    } else {
        LOG_DEBUG(flex_option_logger, DBGLVL_TRACE_BASIC,
                  FLEX_OPTION_PROCESS_ADD)
            .arg(code)
            .arg(vendor_id);
    }
}

void
FlexOptionImpl::logSubClass(const ClientClass& client_class, uint16_t code,
                            uint16_t container_code) {
    LOG_DEBUG(flex_option_logger, DBGLVL_TRACE_BASIC,
              FLEX_OPTION_PROCESS_SUB_CLIENT_CLASS)
        .arg(client_class)
        .arg(code)
        .arg(container_code);
    return;
}

void
FlexOptionImpl::logSubAction(Action action, uint16_t code,
                             uint16_t container_code,
                             const string& value) {
    if (action == NONE) {
        return;
    }
    if (action == REMOVE) {
        LOG_DEBUG(flex_option_logger, DBGLVL_TRACE_BASIC,
                  FLEX_OPTION_PROCESS_SUB_REMOVE)
            .arg(code)
            .arg(container_code);
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
                  FLEX_OPTION_PROCESS_SUB_SUPERSEDE)
            .arg(code)
            .arg(container_code)
            .arg(repr.str());
    } else {
        LOG_DEBUG(flex_option_logger, DBGLVL_TRACE_BASIC,
                  FLEX_OPTION_PROCESS_SUB_ADD)
            .arg(code)
            .arg(container_code)
            .arg(repr.str());
    }
}

bool
FlexOptionImpl::checkVendor(OptionPtr opt, uint32_t vendor_id) {
    OptionVendorPtr vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    bool ret = (!vendor || (vendor->getVendorId() == vendor_id));
    if (!ret) {
        LOG_DEBUG(flex_option_logger, DBGLVL_TRACE_BASIC,
                  FLEX_OPTION_PROCESS_VENDOR_ID_MISMATCH)
            .arg(opt->getType())
            .arg(vendor->getVendorId())
            .arg(vendor_id);
    }
    return (ret);
}

} // end of namespace flex_option
} // end of namespace isc
