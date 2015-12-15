// Copyright (C) 2012, 2014 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/hwaddr.h>
#include <dhcp/dhcp4.h>
#include <exceptions/exceptions.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

using boost::scoped_ptr;

namespace {

// This test verifies if the constructors are working as expected
// and process passed parameters.
TEST(HWAddrTest, constructor) {

    const uint8_t data1[] = {0, 1, 2, 3, 4, 5, 6};
    const uint8_t htype = HTYPE_ETHER;
    vector<uint8_t> data2(data1, data1 + sizeof(data1));

    // Over the limit data 
    vector<uint8_t> big_data_vector(HWAddr::MAX_HWADDR_LEN + 1, 0); 

    scoped_ptr<HWAddr> hwaddr1(new HWAddr(data1, sizeof(data1), htype));
    scoped_ptr<HWAddr> hwaddr2(new HWAddr(data2, htype));
    scoped_ptr<HWAddr> hwaddr3(new HWAddr());

    EXPECT_TRUE(data2 == hwaddr1->hwaddr_);
    EXPECT_EQ(htype, hwaddr1->htype_);

    EXPECT_TRUE(data2 == hwaddr2->hwaddr_);
    EXPECT_EQ(htype, hwaddr2->htype_);

    EXPECT_EQ(0, hwaddr3->hwaddr_.size());
    EXPECT_EQ(htype, hwaddr3->htype_);

    // Check that over the limit data length throws exception 
    EXPECT_THROW(HWAddr(&big_data_vector[0], big_data_vector.size(), HTYPE_ETHER), 
        BadValue);

    // Check that over the limit vector throws exception
    EXPECT_THROW(HWAddr(big_data_vector, HTYPE_ETHER), BadValue);
}

// This test checks if the comparison operators are sane.
TEST(HWAddrTest, operators) {
    uint8_t data1[] = {0, 1, 2, 3, 4, 5, 6};
    uint8_t data2[] = {0, 1, 2, 3, 4};
    uint8_t data3[] = {0, 1, 2, 3, 4, 5, 7}; // last digit different
    uint8_t data4[] = {0, 1, 2, 3, 4, 5, 6}; // the same as 1

    uint8_t htype1 = HTYPE_ETHER;
    uint8_t htype2 = HTYPE_FDDI;

    scoped_ptr<HWAddr> hw1(new HWAddr(data1, sizeof(data1), htype1));
    scoped_ptr<HWAddr> hw2(new HWAddr(data2, sizeof(data2), htype1));
    scoped_ptr<HWAddr> hw3(new HWAddr(data3, sizeof(data3), htype1));
    scoped_ptr<HWAddr> hw4(new HWAddr(data4, sizeof(data4), htype1));

    // MAC address the same as data1 and data4, but different hardware type
    scoped_ptr<HWAddr> hw5(new HWAddr(data4, sizeof(data4), htype2));

    EXPECT_TRUE(*hw1 == *hw4);
    EXPECT_FALSE(*hw1 == *hw2);
    EXPECT_FALSE(*hw1 == *hw3);

    EXPECT_FALSE(*hw1 != *hw4);
    EXPECT_TRUE(*hw1 != *hw2);
    EXPECT_TRUE(*hw1 != *hw3);

    EXPECT_FALSE(*hw1 == *hw5);
    EXPECT_FALSE(*hw4 == *hw5);

    EXPECT_TRUE(*hw1 != *hw5);
    EXPECT_TRUE(*hw4 != *hw5);
}

// Checks that toText() method produces appropriate text representation
TEST(HWAddrTest, toText) {
    uint8_t data[] = {0, 1, 2, 3, 4, 5};
    uint8_t htype = 15;

    HWAddrPtr hw(new HWAddr(data, sizeof(data), htype));

    EXPECT_EQ("hwtype=15 00:01:02:03:04:05", hw->toText());

    // In some cases we don't want htype value to be included. Check that
    // it can be forced.
    EXPECT_EQ("00:01:02:03:04:05", hw->toText(false));
}

TEST(HWAddrTest, stringConversion) {

    // Check that an empty vector returns an appropriate string
    HWAddr hwaddr;
    std::string result = hwaddr.toText();
    EXPECT_EQ(std::string("hwtype=1 "), result);

    // ... that a single-byte string is OK
    hwaddr.hwaddr_.push_back(0xc3);
    result = hwaddr.toText();
    EXPECT_EQ(std::string("hwtype=1 c3"), result);

    // ... and that a multi-byte string works
    hwaddr.hwaddr_.push_back(0x7);
    hwaddr.hwaddr_.push_back(0xa2);
    hwaddr.hwaddr_.push_back(0xe8);
    hwaddr.hwaddr_.push_back(0x42);
    result = hwaddr.toText();
    EXPECT_EQ(std::string("hwtype=1 c3:07:a2:e8:42"), result);
}

// Checks that the HW address can be created from the textual format.
TEST(HWAddrTest, fromText) {
    scoped_ptr<HWAddr> hwaddr;
    // Create HWAddr from text.
    ASSERT_NO_THROW(
        hwaddr.reset(new HWAddr(HWAddr::fromText("00:01:A:bc:d:67")));
    );
    EXPECT_EQ("00:01:0a:bc:0d:67", hwaddr->toText(false));

    // HWAddr class should allow empty address.
    ASSERT_NO_THROW(
        hwaddr.reset(new HWAddr(HWAddr::fromText("")));
    );
    EXPECT_TRUE(hwaddr->toText(false).empty());

    // HWAddr should not allow multiple consecutive colons.
    EXPECT_THROW(
       hwaddr.reset(new HWAddr(HWAddr::fromText("00::01:00:bc:0d:67"))),
       isc::BadValue
    );

    // There should be no more than two digits per byte of the HW addr.
    EXPECT_THROW(
       hwaddr.reset(new HWAddr(HWAddr::fromText("00:01:00A:bc:0d:67"))),
       isc::BadValue
    );

}

// Checks that 16 bits values can be stored in HWaddr
TEST(HWAddrTest, 16bits) {

    uint8_t data[] = {0, 1, 2, 3, 4, 5};
    uint16_t htype = 257;
    HWAddrPtr hw(new HWAddr(data, sizeof(data), htype));

    EXPECT_EQ("hwtype=257 00:01:02:03:04:05", hw->toText());


}

} // end of anonymous namespace
