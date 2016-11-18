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
Parser6Context::parseString(const std::string& str, ParserType parser_type)
{
    scanStringBegin(str, parser_type);
    isc::dhcp::Dhcp6Parser parser(*this);
    // Uncomment this to get detailed parser logs.
    // trace_parsing_ = true;
    parser.set_debug_level(trace_parsing_);
    int res = parser.parse();
    if (res != 0) {
        // @todo: handle exception here
    }
    scanStringEnd();
    if (stack_.size() == 1) {
        return (stack_[0]);
    } else {
        isc_throw(BadValue, "Expected exactly one terminal Element expected, found "
                  << stack_.size());
    }
}

isc::data::ConstElementPtr
Parser6Context::parseFile(const std::string& filename, ParserType parser_type) {
    FILE* f = fopen(filename.c_str(), "r");
    if (!f) {
        isc_throw(BadValue, "Unable to open file " << filename);
    }
    scanFileBegin(f, filename, parser_type);

    isc::dhcp::Dhcp6Parser parser(*this);
    // Uncomment this to get detailed parser logs.
    // trace_parsing_ = true;
    parser.set_debug_level(trace_parsing_);
    int res = parser.parse();
    if (res != 0) {
        // @todo: handle exception here
    }
    scanFileEnd(f);
    if (stack_.size() == 1) {
        return (stack_[0]);
    } else {
        isc_throw(BadValue, "Expected exactly one terminal Element expected, found "
                  << stack_.size());
    }
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
