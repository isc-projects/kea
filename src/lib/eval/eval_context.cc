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
    OptionDefinitionPtr option_def = LibDHCP::getOptionDef(option_universe_,
                                                           option_name);
    if (!option_def) {
        const std::string global_space =
            (option_universe_ == Option::V4) ? "dhcp4" : "dhcp6";
        option_def = LibDHCP::getRuntimeOptionDef(global_space, option_name);
    }

    if (!option_def) {
        error(loc, "option '" + option_name + "' is not defined");
    }

    return (option_def->getCode());
}

void
EvalContext::fatal (const std::string& what)
{
    isc_throw(Unexpected, what);
}
