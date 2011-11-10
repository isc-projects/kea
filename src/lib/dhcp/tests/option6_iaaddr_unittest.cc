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

#include "dhcp/dhcp6.h"
#include "dhcp/option.h"
#include "dhcp/option6_iaaddr.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;

namespace {
class Option6IAAddrTest : public ::testing::Test {
public:
    Option6IAAddrTest() {
    }
};

/// TODO reenable this once ticket #1313 is implemented.
TEST_F(Option6IAAddrTest, basic) {

    boost::shared_array<uint8_t> simple_buf(new uint8_t[128]);
    for (int i = 0; i < 128; i++)
        simple_buf[i] = 0;

    simple_buf[0] = 0x20;
    simple_buf[1] = 0x01;
    simple_buf[2] = 0x0d;
    simple_buf[3] = 0xb8;
    simple_buf[4] = 0x00;
    simple_buf[5] = 0x01;
    simple_buf[12] = 0xde;
    simple_buf[13] = 0xad;
    simple_buf[14] = 0xbe;
    simple_buf[15] = 0xef; // 2001:db8:1::dead:beef

    simple_buf[16] = 0x00;
    simple_buf[17] = 0x00;
    simple_buf[18] = 0x03;
    simple_buf[19] = 0xe8; // 1000

    simple_buf[20] = 0xb2;
    simple_buf[21] = 0xd0;
    simple_buf[22] = 0x5e;
    simple_buf[23] = 0x00; // 3,000,000,000

    // create an option (unpack content)
    Option6IAAddr* opt = new Option6IAAddr(D6O_IAADDR,
                                           simple_buf,
                                           128,
                                           0,
                                           24);

    // pack this option again in the same buffer, but in
    // different place
    int offset = opt->pack(simple_buf, 128, 50);

    EXPECT_EQ(78, offset);

    EXPECT_EQ(Option::V6, opt->getUniverse());

    // 4 bytes header + 4 bytes content
    EXPECT_EQ("2001:db8:1::dead:beef", opt->getAddress().toText());
    EXPECT_EQ(1000, opt->getPreferred());
    EXPECT_EQ(3000000000U, opt->getValid());

    EXPECT_EQ(D6O_IAADDR, opt->getType());

    EXPECT_EQ(Option::OPTION6_HDR_LEN + Option6IAAddr::OPTION6_IAADDR_LEN,
              opt->len());

    // check if pack worked properly:
    // if option type is correct
    EXPECT_EQ(D6O_IAADDR, simple_buf[50]*256 + simple_buf[51]);

    // if option length is correct
    EXPECT_EQ(24, simple_buf[52]*256 + simple_buf[53]);

    // if option content is correct
    EXPECT_EQ(0, memcmp(&simple_buf[0], &simple_buf[54],24));

    EXPECT_NO_THROW(
        delete opt;
    );
}

}
