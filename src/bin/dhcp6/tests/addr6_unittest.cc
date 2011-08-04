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


#include "dhcp6/addr6.h"

using namespace std;
using namespace isc;

namespace {
// empty class for now, but may be extended once Addr6 becomes bigger
class Addr6Test : public ::testing::Test {
public:
    Addr6Test() {
    }
};

TEST_F(Addr6Test, constructor) {

    char buf[16];

    string addr1("2001:db8:1::abcd");
    inet_pton(AF_INET6, addr1.c_str(), buf);

    Addr6 test1(addr1.c_str(), true);

    EXPECT_EQ(test1.getPlain(), addr1);
    EXPECT_EQ(memcmp(test1.get(),buf, 16), 0);

    Addr6 test2(buf, false);

    EXPECT_EQ(test2.getPlain(), addr1);
    EXPECT_EQ(memcmp(test2.get(),buf, 16), 0);
}

TEST_F(Addr6Test, mcast_linklocal) {

    Addr6 mcast("ff00:2001:db8:1::abcd", true);
    Addr6 global("2001:db8:1::dead:beef", true);
    Addr6 local("fe80::face:b00c", true);

    EXPECT_TRUE(mcast.multicast());
    EXPECT_FALSE(mcast.linkLocal());

    EXPECT_FALSE(global.multicast());
    EXPECT_FALSE(global.linkLocal());

    EXPECT_FALSE(local.multicast());
    EXPECT_TRUE(local.linkLocal());
}

TEST_F(Addr6Test, equal) {

    Addr6 one("2001:db8:1::abcd");
    Addr6 two("2001:db8:1::abcd");
    Addr6 three("2001:db8:1::4321");

    EXPECT_TRUE( one==two );
    EXPECT_FALSE( one==three );
}

TEST_F(Addr6Test, stream) {

    string plain("2001:db8:1::abcd");
    Addr6 addr(plain.c_str(), true);

    stringstream tmp;
    tmp << addr;

    EXPECT_STREQ( tmp.str().c_str(), plain.c_str() );
}

}
