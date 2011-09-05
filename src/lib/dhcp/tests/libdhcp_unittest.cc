// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>
#include <iostream>
#include <sstream>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "dhcp/libdhcp.h"
#include "config.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;

namespace {
class LibDhcpTest : public ::testing::Test {
public:
    LibDhcpTest() {
    }
};

TEST_F(LibDhcpTest, basic) {
    // dummy test

    EXPECT_EQ(LibDHCP::version(), PACKAGE_VERSION);
}

TEST_F(LibDhcpTest, packOptions6) {
    boost::shared_array<char> buf(new char[512]);
    isc::dhcp::Option::Option6Lst opts; // list of options

    // generate content for options
    for (int i=0;i<64;i++) {
        buf[i]=i+100;
    }

    boost::shared_ptr<Option> opt1(new Option(Option::V6, 12, buf, 0, 5));
    boost::shared_ptr<Option> opt2(new Option(Option::V6, 13, buf, 5, 3));
    boost::shared_ptr<Option> opt3(new Option(Option::V6, 14, buf, 8, 2));
    boost::shared_ptr<Option> opt4(new Option(Option::V6,256, buf,10, 4));
    boost::shared_ptr<Option> opt5(new Option(Option::V6,257, buf,14, 1));

    char expected[] = {
        0, 12, 0, 5, 100, 101, 102, 103, 104, // opt1
        0, 13, 0, 3, 105, 106, 107, // opt2
        0, 14, 0, 2, 108, 109, // opt3
        1,  0, 0, 4, 110, 111, 112, 113, // opt4
        1,  1, 0, 1, 114
    };

    opts.insert(pair<int, boost::shared_ptr<Option> >(opt1->getType(), opt1));
    opts.insert(pair<int, boost::shared_ptr<Option> >(opt1->getType(), opt2));
    opts.insert(pair<int, boost::shared_ptr<Option> >(opt1->getType(), opt3));
    opts.insert(pair<int, boost::shared_ptr<Option> >(opt1->getType(), opt4));
    opts.insert(pair<int, boost::shared_ptr<Option> >(opt1->getType(), opt5));

    unsigned int offset;
    EXPECT_NO_THROW (
    {
         offset = LibDHCP::packOptions6(buf, 512, 100, opts);
    });
    EXPECT_EQ(135, offset); // options should take 35 bytes
    EXPECT_EQ(0, memcmp(&buf[100], expected, 35) );
}

TEST_F(LibDhcpTest, unpackOptions6) {

}

}
