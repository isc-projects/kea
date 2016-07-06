// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option_definition.h>
#include <dhcp/libdhcp++.h>
#include <eval/eval_context.h>
#include <eval/parser.h>
#include <exceptions/exceptions.h>
#include <boost/lexical_cast.hpp>
#include <fstream>

EvalContext::EvalContext(const Option::Universe& option_universe)
  : trace_scanning_(false), trace_parsing_(false),
    option_universe_(option_universe)
{
}

EvalContext::~EvalContext()
{
}

bool
EvalContext::parseString(const std::string& str)
{
    file_ = "<string>";
    string_ = str;
    scanStringBegin();
    isc::eval::EvalParser parser(*this);
    parser.set_debug_level(trace_parsing_);
    int res = parser.parse();
    scanStringEnd();
    return (res == 0);
}

void
EvalContext::error(const isc::eval::location& loc, const std::string& what)
{
    isc_throw(EvalParseError, loc << ": " << what);
}

void
EvalContext::error (const std::string& what)
{
    isc_throw(EvalParseError, what);
}

uint16_t
EvalContext::convertOptionCode(const std::string& option_code,
                               const isc::eval::location& loc)
{
    int n = 0;
    try {
        n  = boost::lexical_cast<int>(option_code);
    } catch (const boost::bad_lexical_cast &) {
        // This can't happen...
        error(loc, "Option code has invalid value in " + option_code);
    }
    if (option_universe_ == Option::V6) {
        if (n < 0 || n > 65535) {
            error(loc, "Option code has invalid value in "
                      + option_code + ". Allowed range: 0..65535");
        }
    } else {
        if (n < 0 || n > 255) {
            error(loc, "Option code has invalid value in "
                      + option_code + ". Allowed range: 0..255");
        }
    }
    return (static_cast<uint16_t>(n));
}

uint16_t
EvalContext::convertOptionName(const std::string& option_name,
                               const isc::eval::location& loc)
{
    const std::string global_space =
        (Option::V4 == option_universe_) ? DHCP4_OPTION_SPACE : DHCP6_OPTION_SPACE;

    OptionDefinitionPtr option_def_ptr =
        LibDHCP::getOptionDef(option_universe_, option_name, global_space);

    if (!option_def_ptr) {
        option_def_ptr = LibDHCP::getRuntimeOptionDef(global_space, option_name);
    }

    if (!option_def_ptr) {
        error(loc, "option '" + option_name + "' is not defined");
    }

    return (option_def_ptr->getCode());
}

uint8_t
EvalContext::convertNestLevelNumber(const std::string& nest_level,
                                    const isc::eval::location& loc)
{
    int n = 0;
    try {
        n  = boost::lexical_cast<int>(nest_level);
    } catch (const boost::bad_lexical_cast &) {
        error(loc, "Nest level has invalid value in " + nest_level);
    }
    if (option_universe_ == Option::V6) {
        if (n < 0 || n >= HOP_COUNT_LIMIT) {
            error(loc, "Nest level has invalid value in "
                      + nest_level + ". Allowed range: 0..31");
	}
    } else {
        error(loc, "Nest level invalid for DHCPv4 packets");
    }

    return (static_cast<uint8_t>(n));
}


void
EvalContext::fatal (const std::string& what)
{
    isc_throw(Unexpected, what);
}
