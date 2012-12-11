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

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option6_addrlst.h>
#include <util/buffer.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::util;

namespace {
class Option6AddrLstTest : public ::testing::Test {
public:
    Option6AddrLstTest(): buf_(255), outBuf_(255) {
        for (int i = 0; i < 255; i++) {
            buf_[i] = 255 - i;
        }
    }
    OptionBuffer buf_;
    OutputBuffer outBuf_;
};

TEST_F(Option6AddrLstTest, basic) {

    // Limiting tests to just a 2001:db8::/32 as is *wrong*.
    // Good tests check corner cases as well.
    // ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff checks
    // for integer overflow.
    // ff02::face:b00c checks if multicast addresses
    // can be represented properly.

    uint8_t sampledata[] = {
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

    uint8_t expected1[] = {
        D6O_NAME_SERVERS/256, D6O_NAME_SERVERS%256,//type
        0, 16, // len = 16 (1 address)
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0, 0,
        0, 0, 0, 0, 0xde, 0xad, 0xbe, 0xef,

    };

    uint8_t expected2[] = {
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

    uint8_t expected3[] = {
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

    memcpy(&buf_[0], sampledata, 48);

    // just a single address
    Option6AddrLst* opt1 = 0;
    EXPECT_NO_THROW(
        opt1 = new Option6AddrLst(D6O_NAME_SERVERS, buf_.begin(), buf_.begin() + 16 );
    );

    EXPECT_EQ(Option::V6, opt1->getUniverse());

    EXPECT_EQ(D6O_NAME_SERVERS, opt1->getType());
    EXPECT_EQ(20, opt1->len());
    Option6AddrLst::AddressContainer addrs = opt1->getAddresses();
    ASSERT_EQ(1, addrs.size());
    IOAddress addr = addrs[0];
    EXPECT_EQ("2001:db8:1::dead:beef", addr.toText());

    // pack this option
    opt1->pack(outBuf_);

    EXPECT_EQ(20, outBuf_.getLength());
    EXPECT_EQ(0, memcmp(expected1, outBuf_.getData(), 20));

    // two addresses
    Option6AddrLst* opt2 = 0;
    EXPECT_NO_THROW(
        opt2 = new Option6AddrLst(D6O_SIP_SERVERS_ADDR, buf_.begin(), buf_.begin() + 32);
    );
    EXPECT_EQ(D6O_SIP_SERVERS_ADDR, opt2->getType());
    EXPECT_EQ(36, opt2->len());
    addrs = opt2->getAddresses();
    ASSERT_EQ(2, addrs.size());
    EXPECT_EQ("2001:db8:1::dead:beef", addrs[0].toText());
    EXPECT_EQ("ff02::face:b00c", addrs[1].toText());

    // pack this option
    outBuf_.clear();
    opt2->pack(outBuf_);

    EXPECT_EQ(36, outBuf_.getLength() );
    EXPECT_EQ(0, memcmp(expected2, outBuf_.getData(), 36));

    // three addresses
    Option6AddrLst* opt3 = 0;
    EXPECT_NO_THROW(
        opt3 = new Option6AddrLst(D6O_NIS_SERVERS, buf_.begin(), buf_.begin() + 48);
    );

    EXPECT_EQ(D6O_NIS_SERVERS, opt3->getType());
    EXPECT_EQ(52, opt3->len());
    addrs = opt3->getAddresses();
    ASSERT_EQ(3, addrs.size());
    EXPECT_EQ("2001:db8:1::dead:beef", addrs[0].toText());
    EXPECT_EQ("ff02::face:b00c", addrs[1].toText());
    EXPECT_EQ("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", addrs[2].toText());

    // pack this option
    outBuf_.clear();
    opt3->pack(outBuf_);

    EXPECT_EQ(52, outBuf_.getLength());
    EXPECT_EQ(0, memcmp(expected3, outBuf_.getData(), 52));

    EXPECT_NO_THROW(
        delete opt1;
        delete opt2;
        delete opt3;
    );
}

TEST_F(Option6AddrLstTest, constructors) {

    Option6AddrLst* opt1 = 0;
    EXPECT_NO_THROW(
        opt1 = new Option6AddrLst(1234, IOAddress("::1"));
    );
    EXPECT_EQ(Option::V6, opt1->getUniverse());
    EXPECT_EQ(1234, opt1->getType());

    Option6AddrLst::AddressContainer addrs = opt1->getAddresses();
    ASSERT_EQ(1, addrs.size() );
    EXPECT_EQ("::1", addrs[0].toText());

    addrs.clear();
    addrs.push_back(IOAddress(string("fe80::1234")));
    addrs.push_back(IOAddress(string("2001:db8:1::baca")));

    Option6AddrLst* opt2 = 0;
    EXPECT_NO_THROW(
        opt2 = new Option6AddrLst(5678, addrs);
    );

    Option6AddrLst::AddressContainer check = opt2->getAddresses();
    ASSERT_EQ(2, check.size() );
    EXPECT_EQ("fe80::1234", check[0].toText());
    EXPECT_EQ("2001:db8:1::baca", check[1].toText());

    EXPECT_NO_THROW(
        delete opt1;
        delete opt2;
    );
}

TEST_F(Option6AddrLstTest, setAddress) {
    Option6AddrLst* opt1 = 0;
    EXPECT_NO_THROW(
        opt1 = new Option6AddrLst(1234, IOAddress("::1"));
    );
    opt1->setAddress(IOAddress("2001:db8:1::2"));
    /// TODO It used to be ::2 address, but io_address represents
    /// it as ::0.0.0.2. Purpose of this test is to verify
    /// that setAddress() works, not deal with subtleties of
    /// io_address handling of IPv4-mapped IPv6 addresses, we
    /// switched to a more common address. User interested
    /// in pursuing this matter further is encouraged to look
    /// at section 2.5.5 of RFC4291 (and possibly implement
    /// a test for IOAddress)

    Option6AddrLst::AddressContainer addrs = opt1->getAddresses();
    ASSERT_EQ(1, addrs.size() );
    EXPECT_EQ("2001:db8:1::2", addrs[0].toText());

    EXPECT_NO_THROW(
        delete opt1;
    );
}

} // namespace
