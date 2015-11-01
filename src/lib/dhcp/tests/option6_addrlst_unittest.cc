// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <boost/scoped_ptr.hpp>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::util;
using boost::scoped_ptr;

namespace {
class Option6AddrLstTest : public ::testing::Test {
public:
    Option6AddrLstTest(): buf_(255), out_buf_(255) {
        for (unsigned i = 0; i < 255; i++) {
            buf_[i] = 255 - i;
        }
    }
    OptionBuffer buf_;
    OutputBuffer out_buf_;
};

TEST_F(Option6AddrLstTest, basic) {

    // Limiting tests to just a 2001:db8::/32 is *wrong*.
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

    // Just a single address
    scoped_ptr<Option6AddrLst> opt1;
    EXPECT_NO_THROW(
        opt1.reset(new Option6AddrLst(D6O_NAME_SERVERS,
                                      buf_.begin(), buf_.begin() + 16));
    );

    EXPECT_EQ(Option::V6, opt1->getUniverse());

    EXPECT_EQ(D6O_NAME_SERVERS, opt1->getType());
    EXPECT_EQ(20, opt1->len());
    Option6AddrLst::AddressContainer addrs = opt1->getAddresses();
    ASSERT_EQ(1, addrs.size());
    IOAddress addr = addrs[0];
    EXPECT_EQ("2001:db8:1::dead:beef", addr.toText());

    // Pack this option
    opt1->pack(out_buf_);

    EXPECT_EQ(20, out_buf_.getLength());
    EXPECT_EQ(0, memcmp(expected1, out_buf_.getData(), 20));

    // Two addresses
    scoped_ptr<Option6AddrLst> opt2;
    EXPECT_NO_THROW(
        opt2.reset(new Option6AddrLst(D6O_SIP_SERVERS_ADDR,
                                      buf_.begin(), buf_.begin() + 32));
    );
    EXPECT_EQ(D6O_SIP_SERVERS_ADDR, opt2->getType());
    EXPECT_EQ(36, opt2->len());
    addrs = opt2->getAddresses();
    ASSERT_EQ(2, addrs.size());
    EXPECT_EQ("2001:db8:1::dead:beef", addrs[0].toText());
    EXPECT_EQ("ff02::face:b00c", addrs[1].toText());

    // Pack this option
    out_buf_.clear();
    opt2->pack(out_buf_);

    EXPECT_EQ(36, out_buf_.getLength() );
    EXPECT_EQ(0, memcmp(expected2, out_buf_.getData(), 36));

    // Three addresses
    scoped_ptr<Option6AddrLst> opt3;
    EXPECT_NO_THROW(
        opt3.reset(new Option6AddrLst(D6O_NIS_SERVERS,
                                      buf_.begin(), buf_.begin() + 48));
    );

    EXPECT_EQ(D6O_NIS_SERVERS, opt3->getType());
    EXPECT_EQ(52, opt3->len());
    addrs = opt3->getAddresses();
    ASSERT_EQ(3, addrs.size());
    EXPECT_EQ("2001:db8:1::dead:beef", addrs[0].toText());
    EXPECT_EQ("ff02::face:b00c", addrs[1].toText());
    EXPECT_EQ("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", addrs[2].toText());

    // Pack this option
    out_buf_.clear();
    opt3->pack(out_buf_);

    EXPECT_EQ(52, out_buf_.getLength());
    EXPECT_EQ(0, memcmp(expected3, out_buf_.getData(), 52));

    EXPECT_NO_THROW(opt1.reset());
    EXPECT_NO_THROW(opt2.reset());
    EXPECT_NO_THROW(opt3.reset());
}

TEST_F(Option6AddrLstTest, constructors) {

    scoped_ptr<Option6AddrLst> opt1;
    EXPECT_NO_THROW(
        opt1.reset(new Option6AddrLst(1234, IOAddress("::1")));
    );
    EXPECT_EQ(Option::V6, opt1->getUniverse());
    EXPECT_EQ(1234, opt1->getType());

    Option6AddrLst::AddressContainer addrs = opt1->getAddresses();
    ASSERT_EQ(1, addrs.size() );
    EXPECT_EQ("::1", addrs[0].toText());

    addrs.clear();
    addrs.push_back(IOAddress(string("fe80::1234")));
    addrs.push_back(IOAddress(string("2001:db8:1::baca")));

    scoped_ptr<Option6AddrLst> opt2;
    EXPECT_NO_THROW(
        opt2.reset(new Option6AddrLst(5678, addrs));
    );

    Option6AddrLst::AddressContainer check = opt2->getAddresses();
    ASSERT_EQ(2, check.size() );
    EXPECT_EQ("fe80::1234", check[0].toText());
    EXPECT_EQ("2001:db8:1::baca", check[1].toText());

    EXPECT_NO_THROW(opt1.reset());
    EXPECT_NO_THROW(opt2.reset());
}

TEST_F(Option6AddrLstTest, setAddress) {
    scoped_ptr<Option6AddrLst> opt1;
    EXPECT_NO_THROW(
        opt1.reset(new Option6AddrLst(1234, IOAddress("::1")));
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
    ASSERT_EQ(1, addrs.size());
    EXPECT_EQ("2001:db8:1::2", addrs[0].toText());

    EXPECT_NO_THROW(opt1.reset());
}

// This test checks that the option holding IPv6 address list can
// be converted to textual format.
TEST_F(Option6AddrLstTest, toText) {
    Option6AddrLst opt(1234, IOAddress("2001:db8:1::1"));
    // Generate a few IPv6 addresses.
    Option6AddrLst::AddressContainer addresses;
    for (int i = 2; i < 6; ++i) {
        std::stringstream s;
        s << "2001:db8:1::" << i;
        addresses.push_back(IOAddress(s.str()));
    }
    opt.setAddresses(addresses);

    EXPECT_EQ("type=01234, len=00064: 2001:db8:1::2 2001:db8:1::3 "
              "2001:db8:1::4 2001:db8:1::5", opt.toText());
}

// A helper for the 'empty' test.  Exercise public interfaces of an empty
// Option6AddrLst.  It assumes the option type is D6O_DHCPV4_O_DHCPV6_SERVER.
void
checkEmpty(Option6AddrLst& addrs) {
    uint8_t expected[] = {
        D6O_DHCPV4_O_DHCPV6_SERVER/256, D6O_DHCPV4_O_DHCPV6_SERVER%256,
        0, 0
    };
    EXPECT_EQ(4, addrs.len());  // just 2-byte type and 2-byte len fields
    EXPECT_EQ("type=00088, len=00000:", addrs.toText());

    OutputBuffer out_buf(255);
    addrs.pack(out_buf);
    EXPECT_EQ(4, out_buf.getLength());
    EXPECT_EQ(0, memcmp(expected, out_buf.getData(), 4));
}

// Confirms no disruption happens for an empty set of addresses.
TEST_F(Option6AddrLstTest, empty) {
    boost::scoped_ptr<Option6AddrLst> addrs(
        new Option6AddrLst(D6O_DHCPV4_O_DHCPV6_SERVER,
                           Option6AddrLst::AddressContainer()));
    checkEmpty(*addrs);

    const OptionBuffer empty_buf;
    addrs.reset(new Option6AddrLst(D6O_DHCPV4_O_DHCPV6_SERVER,
                                   empty_buf.begin(), empty_buf.end()));
    checkEmpty(*addrs);
}

} // namespace
