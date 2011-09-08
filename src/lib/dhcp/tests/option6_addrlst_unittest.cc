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

#include "io_address.h"
#include "dhcp/dhcp6.h"
#include "dhcp/option.h"
#include "dhcp/option6_addrlst.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {
class Option6AddrLstTest : public ::testing::Test {
public:
    Option6AddrLstTest() {
    }
};

TEST_F(Option6AddrLstTest, basic) {

    char sampledata[] = {
        // 2001:db8:1::dead:beef
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0, 0,
        0, 0, 0, 0, 0xde, 0xad, 0xbe, 0xef,

        // ff02::face:b00c
        0xff, 02, 0, 0, 0, 0, 0 , 0,
        0, 0, 0, 0, 0xfa, 0xce, 0xb0, 0x0c,

        // ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };

    char expected1[] = {
        D6O_NAME_SERVERS/256, D6O_NAME_SERVERS%256,//type
        0, 16, // len = 16 (1 address)
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0, 0,
        0, 0, 0, 0, 0xde, 0xad, 0xbe, 0xef,

    };

    char expected2[] = {
        D6O_SIP_SERVERS_ADDR/256, D6O_SIP_SERVERS_ADDR%256,
        0, 32, // len = 32 (2 addresses)
        // 2001:db8:1::dead:beef
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0, 0,
        0, 0, 0, 0, 0xde, 0xad, 0xbe, 0xef,

        // ff02::face:b00c
        0xff, 02, 0, 0, 0, 0, 0 , 0,
        0, 0, 0, 0, 0xfa, 0xce, 0xb0, 0x0c,

        // ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };

    char expected3[] = {
        D6O_NIS_SERVERS/256, D6O_NIS_SERVERS%256,
        0, 48,
        // 2001:db8:1::dead:beef
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0, 0,
        0, 0, 0, 0, 0xde, 0xad, 0xbe, 0xef,

        // ff02::face:b00c
        0xff, 02, 0, 0, 0, 0, 0 , 0,
        0, 0, 0, 0, 0xfa, 0xce, 0xb0, 0x0c,

        // ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };

    boost::shared_array<char> buf(new char[300]);
    for (int i=0; i<300; i++)
        buf[i] = 0;

    memcpy(&buf[0], sampledata, 48);

    // just a single address
    Option6AddrLst* opt1 = new Option6AddrLst(D6O_NAME_SERVERS,
                                              buf,
                                              128,
                                              0,
                                              16);


    EXPECT_EQ(D6O_NAME_SERVERS, opt1->getType());
    EXPECT_EQ(20, opt1->len());
    Option6AddrLst::AddrsContainer addrs = opt1->getAddresses();
    ASSERT_EQ(1, addrs.size());
    IOAddress addr = addrs[0];
    EXPECT_EQ("2001:db8:1::dead:beef", addr.toText());

    // pack this option again in the same buffer, but in
    // different place
    int offset = opt1->pack(buf,300, 100);

    EXPECT_EQ(120, offset);
    EXPECT_EQ( 0, memcmp(expected1, &buf[100], 20) );

    // two addresses
    Option6AddrLst* opt2 = new Option6AddrLst(D6O_SIP_SERVERS_ADDR,
                                              buf,
                                              128,
                                              0,
                                              32);
    EXPECT_EQ(D6O_SIP_SERVERS_ADDR, opt2->getType());
    EXPECT_EQ(36, opt2->len());
    addrs = opt2->getAddresses();
    ASSERT_EQ(2, addrs.size());
    EXPECT_EQ("2001:db8:1::dead:beef", addrs[0].toText());
    EXPECT_EQ("ff02::face:b00c", addrs[1].toText());

    // pack this option again in the same buffer, but in
    // different place
    offset = opt2->pack(buf,300, 150);

    EXPECT_EQ(150+36, offset);
    EXPECT_EQ( 0, memcmp(expected2, &buf[150], 36));


    // three addresses
    Option6AddrLst* opt3 = new Option6AddrLst(D6O_NIS_SERVERS,
                                              buf,
                                              128,
                                              0,
                                              48);

    EXPECT_EQ(D6O_NIS_SERVERS, opt3->getType());
    EXPECT_EQ(52, opt3->len());
    addrs = opt3->getAddresses();
    ASSERT_EQ(3, addrs.size());
    EXPECT_EQ("2001:db8:1::dead:beef", addrs[0].toText());
    EXPECT_EQ("ff02::face:b00c", addrs[1].toText());
    EXPECT_EQ("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", addrs[2].toText());

    // pack this option again in the same buffer, but in
    // different place
    offset = opt3->pack(buf,300, 200);

    EXPECT_EQ(252, offset);
    EXPECT_EQ( 0, memcmp(expected3, &buf[200], 52) );

    delete opt1;
    delete opt2;
    delete opt3;
}

TEST_F(Option6AddrLstTest, constructors) {
     Option6AddrLst * opt1 = new Option6AddrLst(1234,
                                                IOAddress("::1"));
     EXPECT_EQ(1234, opt1->getType());

     Option6AddrLst::AddrsContainer addrs = opt1->getAddresses();
     ASSERT_EQ(1, addrs.size() );
     EXPECT_EQ("::1", addrs[0].toText());

     addrs.clear();
     addrs.push_back(IOAddress(string("fe80::1234")));
     addrs.push_back(IOAddress(string("2001:db8:1::baca")));

     Option6AddrLst * opt2 = new Option6AddrLst(5678,
                                                addrs);

     Option6AddrLst::AddrsContainer check = opt2->getAddresses();
     ASSERT_EQ(2, check.size() );
     EXPECT_EQ("fe80::1234", check[0].toText());
     EXPECT_EQ("2001:db8:1::baca", check[1].toText());

     delete opt1;
     delete opt2;
}

TEST_F(Option6AddrLstTest, setAddress) {
    Option6AddrLst * opt1 = new Option6AddrLst(1234,
                                                IOAddress("::1"));
    opt1->setAddress(IOAddress("::2"));

    Option6AddrLst::AddrsContainer addrs = opt1->getAddresses();
    ASSERT_EQ(1, addrs.size() );
    EXPECT_EQ("::2", addrs[0].toText());

    delete opt1;
}

} // namespace
