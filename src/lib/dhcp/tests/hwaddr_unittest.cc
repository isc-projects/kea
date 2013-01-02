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

    scoped_ptr<HWAddr> hwaddr1(new HWAddr(data1, sizeof(data1), htype));
    scoped_ptr<HWAddr> hwaddr2(new HWAddr(data2, htype));
    scoped_ptr<HWAddr> hwaddr3(new HWAddr());

    EXPECT_TRUE(data2 == hwaddr1->hwaddr_);
    EXPECT_EQ(htype, hwaddr1->htype_);

    EXPECT_TRUE(data2 == hwaddr2->hwaddr_);
    EXPECT_EQ(htype, hwaddr2->htype_);

    EXPECT_EQ(0, hwaddr3->hwaddr_.size());
    EXPECT_EQ(htype, hwaddr3->htype_);
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

TEST(HWAddrTest, toText) {
    uint8_t data[] = {0, 1, 2, 3, 4, 5}; // last digit different
    uint8_t htype = 15;

    HWAddrPtr hw(new HWAddr(data, sizeof(data), htype));

    EXPECT_EQ("hwtype=15 00:01:02:03:04:05", hw->toText());

}

} // end of anonymous namespace
