// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <limits.h>
#include <gtest/gtest.h>

// Need to define the following macro to get UINT32_MAX
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif
#include <stdint.h>


#include "../asiolink.h"
#include "../address_entry.h"

static std::string V4A_TEXT("1.2.3.4");
static std::string V4B_TEXT("5.6.7.8");
static std::string V6A_TEXT("2001:dead:beef::0");
static std::string V6B_TEXT("1984:1985::1986:1987");

using namespace asiolink;
using namespace std;
using namespace isc::nsas;

/// \brief Test Fixture Class
///
/// Constructs four IOAddress objects, two V4 addresses and two V6 addresses.
/// They are initialised in the constructor owing to the restrictions of
/// the IOAddress class.

class AddressEntryTest : public ::testing::Test {
protected:
    AddressEntryTest() :
        v4a_(V4A_TEXT), v4b_(V4B_TEXT),
        v6a_(V6A_TEXT), v6b_(V6B_TEXT)
    {}

    IOAddress       v4a_;       ///< First V4 address
    IOAddress       v4b_;       ///< Second V4 address
    IOAddress       v6a_;       ///< First V6 address
    IOAddress       v6b_;       ///< Second V6 address
};

/// Tests of the various constructors
TEST_F(AddressEntryTest, Constructor) {

    // Basic constructor with V4 address
    AddressEntry alpha(v4a_);
    EXPECT_EQ(V4A_TEXT, alpha.getAddress().toText());
    EXPECT_EQ(0, alpha.getRTT());

    // General constructor with V4 address
    AddressEntry beta(v4b_, 42);
    EXPECT_EQ(V4B_TEXT, beta.getAddress().toText());
    EXPECT_EQ(42, beta.getRTT());

    // Basic constructor with V6 address
    AddressEntry gamma(v6a_);
    EXPECT_EQ(V6A_TEXT, gamma.getAddress().toText());
    EXPECT_EQ(0, gamma.getRTT());

    // General constructor with V6 address
    AddressEntry delta(v6b_, 75);
    EXPECT_EQ(V6B_TEXT, delta.getAddress().toText());
    EXPECT_EQ(75, delta.getRTT());
}

/// Setting and getting the round-trip time.  Also includes unreachable
/// checks.
TEST_F(AddressEntryTest, RTT) {

    AddressEntry alpha(v4a_);
    EXPECT_EQ(0, alpha.getRTT());

    // Check set and get of RTT
    long rtt = 1276;
    alpha.setRTT(rtt);
    EXPECT_EQ(rtt, alpha.getRTT());

    // Check unreachability
    alpha.setUnreachable();
    EXPECT_TRUE(alpha.isUnreachable());

    alpha.setRTT(27);
    EXPECT_FALSE(alpha.isUnreachable());

    // ... and check the implementation of unreachability
    alpha.setUnreachable();
    EXPECT_EQ(AddressEntry::UNREACHABLE, alpha.getRTT());
}

/// Checking the address type.
TEST_F(AddressEntryTest, AddressType) {

    AddressEntry alpha(v4a_);
    EXPECT_TRUE(alpha.isV4());
    EXPECT_FALSE(alpha.isV6());

    AddressEntry beta(v6a_);
    EXPECT_FALSE(beta.isV4());
    EXPECT_TRUE(beta.isV6());
}
