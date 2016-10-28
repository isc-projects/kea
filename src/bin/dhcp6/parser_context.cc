// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp6/parser_context.h>
#include <dhcp6/dhcp6_parser.h>
#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <limits>

namespace isc {
namespace dhcp {

Parser6Context::Parser6Context()
  : trace_scanning_(false), trace_parsing_(false)
{
}

Parser6Context::~Parser6Context()
{
}

isc::data::ConstElementPtr
Parser6Context::parseString(const std::string& str)
{
    file_ = "<string>";
    string_ = str;
    scanStringBegin();
    isc::dhcp::Dhcp6Parser parser(*this);
    parser.set_debug_level(trace_parsing_);
    int res = parser.parse();
    if (res != 0) {

    }
    scanStringEnd();
    return (*stack_.end());
}

void
Parser6Context::error(const isc::dhcp::location& loc, const std::string& what)
{
    isc_throw(EvalParseError, loc << ": " << what);
}

void
Parser6Context::error (const std::string& what)
{
    isc_throw(EvalParseError, what);
}

void
Parser6Context::fatal (const std::string& what)
{
    isc_throw(Unexpected, what);
}

};
};
