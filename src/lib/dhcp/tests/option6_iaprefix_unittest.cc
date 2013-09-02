// Copyright (C) 2011-2013 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option6_iaprefix.h>
#include <util/buffer.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {
class Option6IAPrefixTest : public ::testing::Test {
public:
    Option6IAPrefixTest() : buf_(255), outBuf_(255) {
        for (int i = 0; i < 255; i++) {
            buf_[i] = 255 - i;
        }
    }
    OptionBuffer buf_;
    OutputBuffer outBuf_;
};

TEST_F(Option6IAPrefixTest, basic) {
    for (int i = 0; i < 255; i++) {
        buf_[i] = 0;
    }

    buf_[ 0] = 0x00;
    buf_[ 1] = 0x00;
    buf_[ 2] = 0x03;
    buf_[ 3] = 0xe8; // preferred lifetime = 1000

    buf_[ 4]  = 0xb2;
    buf_[ 5] = 0xd0;
    buf_[ 6] = 0x5e;
    buf_[ 7] = 0x00; // valid lifetime = 3,000,000,000

    buf_[ 8] = 77; // Prefix length = 77

    buf_[ 9] = 0x20;
    buf_[10] = 0x01;
    buf_[11] = 0x0d;
    buf_[12] = 0xb8;
    buf_[13] = 0x00;
    buf_[14] = 0x01;
    buf_[21] = 0xde;
    buf_[22] = 0xad;
    buf_[23] = 0xbe;
    buf_[24] = 0xef; // 2001:db8:1::dead:beef

    // Create an option (unpack content)
    boost::scoped_ptr<Option6IAPrefix> opt(new Option6IAPrefix(D6O_IAPREFIX,
                                                           buf_.begin(),
                                                           buf_.begin() + 25));

    // Pack this option
    opt->pack(outBuf_);

    EXPECT_EQ(29, outBuf_.getLength());

    EXPECT_EQ(Option::V6, opt->getUniverse());

    // 4 bytes header + 4 bytes content
    EXPECT_EQ("2001:db8:1::dead:beef", opt->getAddress().toText());
    EXPECT_EQ(1000, opt->getPreferred());
    EXPECT_EQ(3000000000U, opt->getValid());
    EXPECT_EQ(77, opt->getLength());

    EXPECT_EQ(D6O_IAPREFIX, opt->getType());

    EXPECT_EQ(Option::OPTION6_HDR_LEN + Option6IAPrefix::OPTION6_IAPREFIX_LEN,
              opt->len());

    // Check if pack worked properly:
    const uint8_t* out = (const uint8_t*)outBuf_.getData();

    // - if option type is correct
    EXPECT_EQ(D6O_IAPREFIX, out[0]*256 + out[1]);

    // - if option length is correct
    EXPECT_EQ(25, out[2]*256 + out[3]);

    // - if option content is correct
    EXPECT_EQ(0, memcmp(out + 4, &buf_[0], 25));

    EXPECT_NO_THROW(opt.reset());
}

}
