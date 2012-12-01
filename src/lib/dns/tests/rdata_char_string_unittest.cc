// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <util/unittests/wiredata.h>
#include <dns/rdata/generic/detail/char_string.h>

#include <gtest/gtest.h>

#include <string>
#include <vector>

using namespace isc::dns;
using namespace isc::dns::rdata;
using isc::dns::rdata::generic::detail::CharString;
using isc::dns::rdata::generic::detail::strToCharString;
using isc::util::unittests::matchWireData;

namespace {
const uint8_t test_charstr[] = {
    sizeof("Test String") - 1,
    'T', 'e', 's', 't', ' ', 'S', 't', 'r', 'i', 'n', 'g'
};

class CharStringTest : public ::testing::Test {
protected:
    CharStringTest() :
        test_str("Test String")
    {
        str_region.beg = &test_str[0];
        str_region.len = test_str.size();
    }
    CharString chstr;           // placeholder
    const std::string test_str;
    MasterToken::StringRegion str_region;
};

TEST_F(CharStringTest, test) {
    strToCharString(str_region, chstr);
    matchWireData(test_charstr, sizeof(test_charstr), &chstr[0], chstr.size());
}

} // unnamed namespace
