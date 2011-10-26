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
#include <util/buffer.h>
#include <dhcp/libdhcp.h>
#include "config.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {
class LibDhcpTest : public ::testing::Test {
public:
    LibDhcpTest() {
    }
};

static const uint8_t packed[] = {
    0, 12, 0, 5, 100, 101, 102, 103, 104, // opt1 (9 bytes)
    0, 13, 0, 3, 105, 106, 107, // opt2 (7 bytes)
    0, 14, 0, 2, 108, 109, // opt3 (6 bytes)
    1,  0, 0, 4, 110, 111, 112, 113, // opt4 (8 bytes)
    1,  1, 0, 1, 114 // opt5 (5 bytes)
};

TEST(LibDhcpTest, packOptions6) {
    boost::shared_array<uint8_t> buf(new uint8_t[512]);
    isc::dhcp::Option::Option6Collection opts; // list of options

    // generate content for options
    for (int i = 0; i < 64; i++) {
        buf[i]=i+100;
    }

    boost::shared_ptr<Option> opt1(new Option(Option::V6, 12, buf, 0, 5));
    boost::shared_ptr<Option> opt2(new Option(Option::V6, 13, buf, 5, 3));
    boost::shared_ptr<Option> opt3(new Option(Option::V6, 14, buf, 8, 2));
    boost::shared_ptr<Option> opt4(new Option(Option::V6,256, buf,10, 4));
    boost::shared_ptr<Option> opt5(new Option(Option::V6,257, buf,14, 1));

    opts.insert(pair<int, boost::shared_ptr<Option> >(opt1->getType(), opt1));
    opts.insert(pair<int, boost::shared_ptr<Option> >(opt1->getType(), opt2));
    opts.insert(pair<int, boost::shared_ptr<Option> >(opt1->getType(), opt3));
    opts.insert(pair<int, boost::shared_ptr<Option> >(opt1->getType(), opt4));
    opts.insert(pair<int, boost::shared_ptr<Option> >(opt1->getType(), opt5));

    unsigned int offset;
    EXPECT_NO_THROW ({
         offset = LibDHCP::packOptions6(buf, 512, 100, opts);
    });
    EXPECT_EQ(135, offset); // options should take 35 bytes
    EXPECT_EQ(0, memcmp(&buf[100], packed, 35) );
}

TEST(LibDhcpTest, unpackOptions6) {

    // just couple of random options
    // Option is used as a simple option implementation
    // More advanced uses are validated in tests dedicated for
    // specific derived classes.
    isc::dhcp::Option::Option6Collection options; // list of options

    // we can't use packed directly, as shared_array would try to
    // free it eventually
    boost::shared_array<uint8_t> buf(new uint8_t[512]);
    memcpy(&buf[0], packed, 35);

    unsigned int offset;
    EXPECT_NO_THROW ({
        offset = LibDHCP::unpackOptions6(buf, 512, 0, 35, options);
    });

    EXPECT_EQ(35, offset); // parsed first 35 bytes (offset 0..34)
    EXPECT_EQ(options.size(), 5); // there should be 5 options

    isc::dhcp::Option::Option6Collection::const_iterator x = options.find(12);
    ASSERT_FALSE(x == options.end()); // option 1 should exist
    EXPECT_EQ(12, x->second->getType());  // this should be option 12
    ASSERT_EQ(9, x->second->len()); // it should be of length 9
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], packed+4, 5)); // data len=5

    x = options.find(13);
    ASSERT_FALSE(x == options.end()); // option 13 should exist
    EXPECT_EQ(13, x->second->getType());  // this should be option 13
    ASSERT_EQ(7, x->second->len()); // it should be of length 7
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], packed+13, 3)); // data len=3

    x = options.find(14);
    ASSERT_FALSE(x == options.end()); // option 3 should exist
    EXPECT_EQ(14, x->second->getType());  // this should be option 14
    ASSERT_EQ(6, x->second->len()); // it should be of length 6
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], packed+20, 2)); // data len=2

    x = options.find(256);
    ASSERT_FALSE(x == options.end()); // option 256 should exist
    EXPECT_EQ(256, x->second->getType());  // this should be option 256
    ASSERT_EQ(8, x->second->len()); // it should be of length 7
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], packed+26, 4)); // data len=4

    x = options.find(257);
    ASSERT_FALSE(x == options.end()); // option 257 should exist
    EXPECT_EQ(257, x->second->getType());  // this should be option 257
    ASSERT_EQ(5, x->second->len()); // it should be of length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], packed+34, 1)); // data len=1

    x = options.find(0);
    EXPECT_TRUE(x == options.end()); // option 0 not found

    x = options.find(1); // 1 is htons(256) on little endians. Worth checking
    EXPECT_TRUE(x == options.end()); // option 1 not found

    x = options.find(2);
    EXPECT_TRUE(x == options.end()); // option 2 not found

    x = options.find(32000);
    EXPECT_TRUE(x == options.end()); // option 32000 not found
}


static uint8_t v4Opts[] = {
    12,  3, 0,   1,  2,
    13,  3, 10, 11, 12,
    14,  3, 20, 21, 22,
    254, 3, 30, 31, 32,
    128, 3, 40, 41, 42
};

TEST(LibDhcpTest, packOptions4) {

    vector<uint8_t> payload[5];
    for (int i = 0; i < 5; i++) {
        payload[i].resize(3);
        payload[i][0] = i*10;
        payload[i][1] = i*10+1;
        payload[i][2] = i*10+2;
    }

    boost::shared_ptr<Option> opt1(new Option(Option::V4, 12, payload[0]));
    boost::shared_ptr<Option> opt2(new Option(Option::V4, 13, payload[1]));
    boost::shared_ptr<Option> opt3(new Option(Option::V4, 14, payload[2]));
    boost::shared_ptr<Option> opt4(new Option(Option::V4,254, payload[3]));
    boost::shared_ptr<Option> opt5(new Option(Option::V4,128, payload[4]));

    isc::dhcp::Option::Option6Collection opts; // list of options
    opts.insert(pair<int, boost::shared_ptr<Option> >(opt1->getType(), opt1));
    opts.insert(pair<int, boost::shared_ptr<Option> >(opt1->getType(), opt2));
    opts.insert(pair<int, boost::shared_ptr<Option> >(opt1->getType(), opt3));
    opts.insert(pair<int, boost::shared_ptr<Option> >(opt1->getType(), opt4));
    opts.insert(pair<int, boost::shared_ptr<Option> >(opt1->getType(), opt5));

    vector<uint8_t> expVect(v4Opts, v4Opts + sizeof(v4Opts));

    OutputBuffer buf(100);
    EXPECT_NO_THROW (
        LibDHCP::packOptions(buf, opts);
    );
    ASSERT_EQ(buf.getLength(), sizeof(v4Opts));
    EXPECT_EQ(0, memcmp(v4Opts, buf.getData(), sizeof(v4Opts)));

}

TEST(LibDhcpTest, unpackOptions4) {

    vector<uint8_t> packed(v4Opts, v4Opts + sizeof(v4Opts));
    isc::dhcp::Option::Option6Collection options; // list of options

    ASSERT_NO_THROW(
        LibDHCP::unpackOptions4(packed, options);
    );

    isc::dhcp::Option::Option6Collection::const_iterator x = options.find(12);
    ASSERT_FALSE(x == options.end()); // option 1 should exist
    EXPECT_EQ(12, x->second->getType());  // this should be option 12
    ASSERT_EQ(3, x->second->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->second->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v4Opts+2, 3)); // data len=3

    x = options.find(13);
    ASSERT_FALSE(x == options.end()); // option 1 should exist
    EXPECT_EQ(13, x->second->getType());  // this should be option 13
    ASSERT_EQ(3, x->second->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->second->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v4Opts+7, 3)); // data len=3

    x = options.find(14);
    ASSERT_FALSE(x == options.end()); // option 3 should exist
    EXPECT_EQ(14, x->second->getType());  // this should be option 14
    ASSERT_EQ(3, x->second->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->second->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v4Opts+12, 3)); // data len=3

    x = options.find(254);
    ASSERT_FALSE(x == options.end()); // option 3 should exist
    EXPECT_EQ(254, x->second->getType());  // this should be option 254
    ASSERT_EQ(3, x->second->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->second->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v4Opts+17, 3)); // data len=3

    x = options.find(128);
    ASSERT_FALSE(x == options.end()); // option 3 should exist
    EXPECT_EQ(128, x->second->getType());  // this should be option 254
    ASSERT_EQ(3, x->second->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->second->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->second->getData()[0], v4Opts+22, 3)); // data len=3

    x = options.find(0);
    EXPECT_TRUE(x == options.end()); // option 0 not found

    x = options.find(1);
    EXPECT_TRUE(x == options.end()); // option 1 not found

    x = options.find(2);
    EXPECT_TRUE(x == options.end()); // option 2 not found
}

}
