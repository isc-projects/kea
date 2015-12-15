// Copyright (C) 2011-2013  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/option.h>
#include <dhcp/option4_addrlst.h>
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

// a sample data (list of 4 addresses)
const uint8_t sampledata[] = {
    192, 0, 2, 3,     // 192.0.2.3
    255, 255, 255, 0, // 255.255.255.0 - popular netmask
    0, 0, 0 , 0,      // used for default routes or (any address)
    127, 0, 0, 1      // loopback
};

// expected on-wire format for an option with 1 address
const uint8_t expected1[] = { // 1 address
    DHO_DOMAIN_NAME_SERVERS, 4, // type, length
    192, 0, 2, 3,     // 192.0.2.3
};

// expected on-wire format for an option with 4 addresses
const uint8_t expected4[] = { // 4 addresses
    254, 16,            // type = 254, len = 16
    192, 0, 2, 3,       // 192.0.2.3
    255, 255, 255, 0,   // 255.255.255.0 - popular netmask
    0, 0, 0 ,0,         // used for default routes or (any address)
    127, 0, 0, 1        // loopback
};

class Option4AddrLstTest : public ::testing::Test {
protected:

    Option4AddrLstTest():
        vec_(vector<uint8_t>(300, 0)) // 300 bytes long filled with 0s
    {
        sampleAddrs_.push_back(IOAddress("192.0.2.3"));
        sampleAddrs_.push_back(IOAddress("255.255.255.0"));
        sampleAddrs_.push_back(IOAddress("0.0.0.0"));
        sampleAddrs_.push_back(IOAddress("127.0.0.1"));
    }

    vector<uint8_t> vec_;
    Option4AddrLst::AddressContainer sampleAddrs_;

};

TEST_F(Option4AddrLstTest, parse1) {

    memcpy(&vec_[0], sampledata, sizeof(sampledata));

    // Just one address
    scoped_ptr<Option4AddrLst> opt1;
    EXPECT_NO_THROW(
        opt1.reset(new Option4AddrLst(DHO_DOMAIN_NAME_SERVERS,
                                      vec_.begin(),
                                      vec_.begin()+4));
        // Use just first address (4 bytes), not the whole
        // sampledata
    );

    EXPECT_EQ(Option::V4, opt1->getUniverse());

    EXPECT_EQ(DHO_DOMAIN_NAME_SERVERS, opt1->getType());
    EXPECT_EQ(6, opt1->len()); // 2 (header) + 4 (1x IPv4 addr)

    Option4AddrLst::AddressContainer addrs = opt1->getAddresses();
    ASSERT_EQ(1, addrs.size());

    EXPECT_EQ("192.0.2.3", addrs[0].toText());

    EXPECT_NO_THROW(opt1.reset());
}

TEST_F(Option4AddrLstTest, parse4) {

    vector<uint8_t> buffer(300, 0); // 300 bytes long filled with 0s

    memcpy(&buffer[0], sampledata, sizeof(sampledata));

    // 4 addresses
    scoped_ptr<Option4AddrLst> opt4;
    EXPECT_NO_THROW(
        opt4.reset(new Option4AddrLst(254,
                                      buffer.begin(),
                                      buffer.begin()+sizeof(sampledata)));
    );

    EXPECT_EQ(Option::V4, opt4->getUniverse());

    EXPECT_EQ(254, opt4->getType());
    EXPECT_EQ(18, opt4->len()); // 2 (header) + 16 (4x IPv4 addrs)

    Option4AddrLst::AddressContainer addrs = opt4->getAddresses();
    ASSERT_EQ(4, addrs.size());

    EXPECT_EQ("192.0.2.3", addrs[0].toText());
    EXPECT_EQ("255.255.255.0", addrs[1].toText());
    EXPECT_EQ("0.0.0.0", addrs[2].toText());
    EXPECT_EQ("127.0.0.1", addrs[3].toText());

    EXPECT_NO_THROW(opt4.reset());
}

TEST_F(Option4AddrLstTest, assembly1) {

    scoped_ptr<Option4AddrLst> opt;
    EXPECT_NO_THROW(
        opt.reset(new Option4AddrLst(DHO_DOMAIN_NAME_SERVERS,
                                     IOAddress("192.0.2.3")));
    );
    EXPECT_EQ(Option::V4, opt->getUniverse());
    EXPECT_EQ(DHO_DOMAIN_NAME_SERVERS, opt->getType());

    Option4AddrLst::AddressContainer addrs = opt->getAddresses();
    ASSERT_EQ(1, addrs.size() );
    EXPECT_EQ("192.0.2.3", addrs[0].toText());

    OutputBuffer buf(100);
    EXPECT_NO_THROW(
        opt->pack(buf);
    );

    ASSERT_EQ(6, opt->len());
    ASSERT_EQ(6, buf.getLength());

    EXPECT_EQ(0, memcmp(expected1, buf.getData(), 6));

    EXPECT_NO_THROW(opt.reset());

    // This is old-fashioned option. We don't serve IPv6 types here!
    EXPECT_THROW(
        opt.reset(new Option4AddrLst(DHO_DOMAIN_NAME_SERVERS,
                                     IOAddress("2001:db8::1"))),
        BadValue
    );
}

TEST_F(Option4AddrLstTest, assembly4) {

    scoped_ptr<Option4AddrLst> opt;
    EXPECT_NO_THROW(
        opt.reset(new Option4AddrLst(254, sampleAddrs_));
    );
    EXPECT_EQ(Option::V4, opt->getUniverse());
    EXPECT_EQ(254, opt->getType());

    Option4AddrLst::AddressContainer addrs = opt->getAddresses();
    ASSERT_EQ(4, addrs.size() );
    EXPECT_EQ("192.0.2.3", addrs[0].toText());
    EXPECT_EQ("255.255.255.0", addrs[1].toText());
    EXPECT_EQ("0.0.0.0", addrs[2].toText());
    EXPECT_EQ("127.0.0.1", addrs[3].toText());

    OutputBuffer buf(100);
    EXPECT_NO_THROW(
        opt->pack(buf);
    );

    ASSERT_EQ(18, opt->len()); // 2(header) + 4xsizeof(IPv4addr)
    ASSERT_EQ(18, buf.getLength());

    ASSERT_EQ(0, memcmp(expected4, buf.getData(), 18));

    EXPECT_NO_THROW(opt.reset());

    // This is old-fashioned option. We don't serve IPv6 types here!
    sampleAddrs_.push_back(IOAddress("2001:db8::1"));
    EXPECT_THROW(
        opt.reset(new Option4AddrLst(DHO_DOMAIN_NAME_SERVERS, sampleAddrs_)),
        BadValue
    );
}

TEST_F(Option4AddrLstTest, setAddress) {

    scoped_ptr<Option4AddrLst> opt;
    EXPECT_NO_THROW(
        opt.reset(new Option4AddrLst(123, IOAddress("1.2.3.4")));
    );
    opt->setAddress(IOAddress("192.0.255.255"));

    Option4AddrLst::AddressContainer addrs = opt->getAddresses();
    ASSERT_EQ(1, addrs.size() );
    EXPECT_EQ("192.0.255.255", addrs[0].toText());

    // We should accept IPv4-only addresses.
    EXPECT_THROW(
        opt->setAddress(IOAddress("2001:db8::1")),
        BadValue
    );

    EXPECT_NO_THROW(opt.reset());
}

TEST_F(Option4AddrLstTest, setAddresses) {

    scoped_ptr<Option4AddrLst> opt;

    EXPECT_NO_THROW(
        opt.reset(new Option4AddrLst(123)); // Empty list
    );

    opt->setAddresses(sampleAddrs_);

    Option4AddrLst::AddressContainer addrs = opt->getAddresses();
    ASSERT_EQ(4, addrs.size() );
    EXPECT_EQ("192.0.2.3", addrs[0].toText());
    EXPECT_EQ("255.255.255.0", addrs[1].toText());
    EXPECT_EQ("0.0.0.0", addrs[2].toText());
    EXPECT_EQ("127.0.0.1", addrs[3].toText());

    // We should accept IPv4-only addresses.
    sampleAddrs_.push_back(IOAddress("2001:db8::1"));
    EXPECT_THROW(
        opt->setAddresses(sampleAddrs_),
        BadValue
    );

    EXPECT_NO_THROW(opt.reset());
}

// This test checks that the option holding IPv4 address list can
// be converted to textual format.
TEST_F(Option4AddrLstTest, toText) {
    Option4AddrLst opt(111);
    // Generate a few IPv4 addresses.
    Option4AddrLst::AddressContainer addresses;
    for (int i = 2; i < 6; ++i) {
        std::stringstream s;
        s << "192.0.2." << i;
        addresses.push_back(IOAddress(s.str()));
    }
    opt.setAddresses(addresses);

    EXPECT_EQ("type=111, len=016: 192.0.2.2 192.0.2.3 192.0.2.4 192.0.2.5",
              opt.toText());
}

} // namespace
