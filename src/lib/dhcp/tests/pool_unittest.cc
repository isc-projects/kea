// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <vector>
#include <sstream>
#include <gtest/gtest.h>
#include <dhcp/pool.h>
#include <asiolink/io_address.h>

using boost::scoped_ptr;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {

TEST(Pool6Test, constructor_first_last) {

    // let's construct 2001:db8:1:: - 2001:db8:1::ffff:ffff:ffff:ffff pool
    Pool6 pool1(Pool6::TYPE_IA, IOAddress("2001:db8:1::"),
                IOAddress("2001:db8:1::ffff:ffff:ffff:ffff"));

    EXPECT_EQ(Pool6::TYPE_IA, pool1.getType());
    EXPECT_EQ(IOAddress("2001:db8:1::"), pool1.getFirstAddress());
    EXPECT_EQ(IOAddress("2001:db8:1::ffff:ffff:ffff:ffff"),
              pool1.getLastAddress());

    // This is Pool6, IPv4 addresses do not belong here
    EXPECT_THROW(Pool6(Pool6::TYPE_IA, IOAddress("2001:db8::1"),
                       IOAddress("192.168.0.5")), BadValue);
    EXPECT_THROW(Pool6(Pool6::TYPE_IA, IOAddress("192.168.0.2"),
                       IOAddress("2001:db8::1")), BadValue);

    // Should throw. Range should be 2001:db8::1 - 2001:db8::2, not
    // the other way around.
    EXPECT_THROW(Pool6(Pool6::TYPE_IA, IOAddress("2001:db8::2"),
                       IOAddress("2001:db8::1")), BadValue);
}

TEST(Pool6Test, constructor_prefix_len) {

    // let's construct 2001:db8:1::/96 pool
    Pool6 pool1(Pool6::TYPE_IA, IOAddress("2001:db8:1::"), 96);

    EXPECT_EQ(Pool6::TYPE_IA, pool1.getType());
    EXPECT_EQ("2001:db8:1::", pool1.getFirstAddress().toText());
    EXPECT_EQ("2001:db8:1::ffff:ffff", pool1.getLastAddress().toText());

    // No such thing as /130 prefix
    EXPECT_THROW(Pool6(Pool6::TYPE_IA, IOAddress("2001:db8::"), 130),
                 BadValue);

    // /0 prefix does not make sense
    EXPECT_THROW(Pool6(Pool6::TYPE_IA, IOAddress("2001:db8::"), 0),
                 BadValue);

    // This is Pool6, IPv4 addresses do not belong here
    EXPECT_THROW(Pool6(Pool6::TYPE_IA, IOAddress("192.168.0.2"), 96),
                 BadValue);
}

TEST(Pool6Test, in_range) {
   Pool6 pool1(Pool6::TYPE_IA, IOAddress("2001:db8:1::1"),
               IOAddress("2001:db8:1::f"));

   EXPECT_FALSE(pool1.inRange(IOAddress("2001:db8:1::")));
   EXPECT_TRUE(pool1.inRange(IOAddress("2001:db8:1::1")));
   EXPECT_TRUE(pool1.inRange(IOAddress("2001:db8:1::7")));
   EXPECT_TRUE(pool1.inRange(IOAddress("2001:db8:1::f")));
   EXPECT_FALSE(pool1.inRange(IOAddress("2001:db8:1::10")));
   EXPECT_FALSE(pool1.inRange(IOAddress("::")));
}

// This test creates 100 pools and verifies that their IDs are unique.
TEST(Pool6Test, unique_id) {

    const int num_pools = 100;
    std::vector<Pool6Ptr> pools;

    for (int i = 0; i < num_pools; ++i) {
        pools.push_back(Pool6Ptr(new Pool6(Pool6::TYPE_IA, IOAddress("2001:db8:1::"),
                                           IOAddress("2001:db8:1::ffff:ffff:ffff:ffff"))));
    }

    for (int i = 0; i < num_pools; ++i) {
        for (int j = i + 1; j < num_pools; ++j) {
            if (pools[i]->getId() == pools[j]->getId()) {
                FAIL() << "Pool-ids must be unique";
            }
        }
    }

}

}; // end of anonymous namespace

