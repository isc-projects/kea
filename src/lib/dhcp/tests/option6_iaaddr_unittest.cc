// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option6_iaaddr.h>
#include <util/buffer.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {
class Option6IAAddrTest : public ::testing::Test {
public:
    Option6IAAddrTest() : buf_(255), outBuf_(255) {
        for (int i = 0; i < 255; i++) {
            buf_[i] = 255 - i;
        }
    }
    OptionBuffer buf_;
    OutputBuffer outBuf_;
};

TEST_F(Option6IAAddrTest, basic) {
    for (int i = 0; i < 255; i++) {
        buf_[i] = 0;
    }
    buf_[0] = 0x20;
    buf_[1] = 0x01;
    buf_[2] = 0x0d;
    buf_[3] = 0xb8;
    buf_[4] = 0x00;
    buf_[5] = 0x01;
    buf_[12] = 0xde;
    buf_[13] = 0xad;
    buf_[14] = 0xbe;
    buf_[15] = 0xef; // 2001:db8:1::dead:beef

    buf_[16] = 0x00;
    buf_[17] = 0x00;
    buf_[18] = 0x03;
    buf_[19] = 0xe8; // 1000

    buf_[20] = 0xb2;
    buf_[21] = 0xd0;
    buf_[22] = 0x5e;
    buf_[23] = 0x00; // 3,000,000,000

    // create an option (unpack content)
    Option6IAAddr* opt = new Option6IAAddr(D6O_IAADDR,
                                           buf_.begin(),
                                           buf_.begin() + 24);

    // pack this option
    opt->pack(outBuf_);

    EXPECT_EQ(28, outBuf_.getLength());

    EXPECT_EQ(Option::V6, opt->getUniverse());

    // 4 bytes header + 4 bytes content
    EXPECT_EQ("2001:db8:1::dead:beef", opt->getAddress().toText());
    EXPECT_EQ(1000, opt->getPreferred());
    EXPECT_EQ(3000000000U, opt->getValid());

    EXPECT_EQ(D6O_IAADDR, opt->getType());

    EXPECT_EQ(Option::OPTION6_HDR_LEN + Option6IAAddr::OPTION6_IAADDR_LEN,
              opt->len());

    // check if pack worked properly:
    const uint8_t* out = (const uint8_t*)outBuf_.getData();

    // if option type is correct
    EXPECT_EQ(D6O_IAADDR, out[0]*256 + out[1]);

    // if option length is correct
    EXPECT_EQ(24, out[2]*256 + out[3]);

    // if option content is correct
    EXPECT_EQ(0, memcmp(out + 4, &buf_[0], 24));

    EXPECT_NO_THROW( delete opt );
}

}
