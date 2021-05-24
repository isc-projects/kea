// Copyright (C) 2015-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option_definition.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_space.h>
#include <eval/eval_context.h>
#include <eval/parser.h>
#include <exceptions/exceptions.h>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <limits>

EvalContext::EvalContext(const Option::Universe& option_universe,
                         CheckDefined check_defined)
    : trace_scanning_(false), trace_parsing_(false),
      option_universe_(option_universe), check_defined_(check_defined)
{
}

EvalContext::~EvalContext() {
}

bool
EvalContext::acceptAll(const ClientClass&) {
    return (true);
}

bool
EvalContext::parseString(const std::string& str, ParserType type) {
    file_ = "<string>";
    string_ = str;
    scanStringBegin(type);
    int res = -1;
    try {
        isc::eval::EvalParser parser(*this);
        parser.set_debug_level(trace_parsing_);
        res = parser.parse();
    } catch (...) {
        scanStringEnd();
        throw;
    }
    scanStringEnd();
    return (res == 0);
}

void
EvalContext::error(const isc::eval::location& loc, const std::string& what) {
    isc_throw(EvalParseError, loc << ": " << what);
}

void
EvalContext::error (const std::string& what) {
    isc_throw(EvalParseError, what);
}

uint16_t
EvalContext::convertOptionCode(const std::string& option_code,
                               const isc::eval::location& loc) {
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
                               const isc::eval::location& loc) {
    const std::string global_space = (option_universe_ == Option::V4) ?
        DHCP4_OPTION_SPACE : DHCP6_OPTION_SPACE;

    OptionDefinitionPtr option_def = LibDHCP::getOptionDef(global_space,
                                                           option_name);
    if (!option_def) {
        option_def = LibDHCP::getRuntimeOptionDef(global_space, option_name);
    }

    if (!option_def) {
        option_def = LibDHCP::getLastResortOptionDef(global_space, option_name);
    }

    if (!option_def) {
        error(loc, "option '" + option_name + "' is not defined");
    }

    return (option_def->getCode());
}

int8_t
EvalContext::convertNestLevelNumber(const std::string& nest_level,
                                    const isc::eval::location& loc) {
    int8_t n = convertInt8(nest_level, loc);
    if (option_universe_ == Option::V6) {
        if ((n < - HOP_COUNT_LIMIT) || (n >= HOP_COUNT_LIMIT)) {
            error(loc, "Nest level has invalid value in "
                      + nest_level + ". Allowed range: -32..31");
        }
    } else {
        error(loc, "Nest level invalid for DHCPv4 packets");
    }

    return (n);
}

uint8_t
EvalContext::convertUint8(const std::string& number,
                          const isc::eval::location& loc) {
    int64_t n = 0;
    try {
        n = boost::lexical_cast<int64_t>(number);
    } catch (const boost::bad_lexical_cast &) {
        error(loc, "Invalid integer value in " + number);
    }
    if (n < 0 || n > std::numeric_limits<uint8_t>::max()) {
        error(loc, "Invalid value in "
              + number + ". Allowed range: 0..255");
    }

    return (static_cast<uint8_t>(n));
}

int8_t
EvalContext::convertInt8(const std::string& number,
                         const isc::eval::location& loc) {
    int64_t n = 0;
    try {
        n = boost::lexical_cast<int64_t>(number);
    } catch (const boost::bad_lexical_cast &) {
        error(loc, "Invalid integer value in " + number);
    }
    if (n < std::numeric_limits<int8_t>::min() ||
        n > std::numeric_limits<int8_t>::max()) {
        error(loc, "Invalid value in "
              + number + ". Allowed range: -128..127");
    }

    return (static_cast<int8_t>(n));
}

uint16_t
EvalContext::convertUint16(const std::string& number,
                           const isc::eval::location& loc) {
    int64_t n = 0;
    try {
        n = boost::lexical_cast<int64_t>(number);
    } catch (const boost::bad_lexical_cast &) {
        error(loc, "Invalid value in " + number);
    }
    if (n < 0 || n > std::numeric_limits<uint16_t>::max()) {
        error(loc, "Invalid value in "
              + number + ". Allowed range: 0..65535");
    }

    return (static_cast<uint16_t>(n));
}

int16_t
EvalContext::convertInt16(const std::string& number,
                          const isc::eval::location& loc) {
    uint64_t n = 0;
    try {
        n = boost::lexical_cast<int64_t>(number);
    } catch (const boost::bad_lexical_cast &) {
        error(loc, "Invalid value in " + number);
    }
    if (n > std::numeric_limits<int16_t>::max() ||
        n < std::numeric_limits<int16_t>::max()) {
        error(loc, "Invalid value in "
              + number + ". Allowed range: -32768..32767");
    }

    return (static_cast<int16_t>(n));
}

uint32_t
EvalContext::convertUint32(const std::string& number,
                           const isc::eval::location& loc) {
    int64_t n = 0;
    try {
        n = boost::lexical_cast<int64_t>(number);
    } catch (const boost::bad_lexical_cast &) {
        error(loc, "Invalid value in " + number);
    }
    if (n < 0 || n > std::numeric_limits<uint32_t>::max()) {
        error(loc, "Invalid value in "
              + number + ". Allowed range: 0..4294967295");
    }

    return (static_cast<uint32_t>(n));
}

int32_t
EvalContext::convertInt32(const std::string& number,
                          const isc::eval::location& loc) {
    int64_t n = 0;
    try {
        n = boost::lexical_cast<int64_t>(number);
    } catch (const boost::bad_lexical_cast &) {
        error(loc, "Invalid value in " + number);
    }
    if (n > std::numeric_limits<int32_t>::max() ||
        n < std::numeric_limits<int32_t>::max()) {
        error(loc, "Invalid value in "
              + number + ". Allowed range: -2147483648..2147483647");
    }

    return (static_cast<int32_t>(n));
}

std::string
EvalContext::fromUint32(const uint32_t integer) {
    std::string tmp(4, 0);
    tmp[0] = (integer >> 24) & 0xff;
    tmp[1] = (integer >> 16) & 0xff;
    tmp[2] = (integer >> 8) & 0xff;
    tmp[3] = integer & 0xff;

    return (tmp);
}

std::string
EvalContext::fromUint16(const uint16_t integer) {
    std::string tmp(2, 0);
    tmp[0] = (integer >> 8) & 0xff;
    tmp[1] = integer & 0xff;

    return (tmp);
}

bool
EvalContext::isClientClassDefined(const ClientClass& client_class) {
    return (check_defined_(client_class));
}

void
EvalContext::fatal(const std::string& what) {
    isc_throw(Unexpected, what);
}
