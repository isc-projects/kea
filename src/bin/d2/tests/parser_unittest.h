// Copyright (C) 2017-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PARSER_UNITTEST_H
#define PARSER_UNITTEST_H

#include <gtest/gtest.h>
#include <cc/data.h>
#include <d2/parser_context.h>

using namespace isc::data;
using namespace std;

namespace isc {
namespace d2 {
namespace test {

/// @brief Runs parser in JSON mode, useful for parser testing
///
/// @param in string to be parsed
/// @return ElementPtr structure representing parsed JSON
inline isc::data::ElementPtr
parseJSON(const std::string& in)
{
    isc::d2::D2ParserContext ctx;
    return (ctx.parseString(in, isc::d2::D2ParserContext::PARSER_JSON));
}

}
}
}

#endif // PARSER_UNITTEST_H
