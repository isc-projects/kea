// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// Author: Andrei Pavel <andrei.pavel@qualitance.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <exceptions/exceptions.h>
#include <dhcp/option6_pdexclude.h>
#include <dhcpsrv/pool.h>
#include <util/buffer.h>
#include <util/encode/hex.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace asiolink;

namespace {

// Prefix constants used in unit tests.
const IOAddress v4("192.0.2.0");
const IOAddress bee0("2001:db8:dead:bee0::");
const IOAddress beef("2001:db8:dead:beef::");
const IOAddress cafe("2001:db8:dead:cafe::");
const IOAddress beef01("2001:db8:dead:beef::01");

// This test verifies that the constructor sets parameters appropriately.
TEST(Option6PDExcludeTest, constructor) {
    Option6PDExclude option = Option6PDExclude(beef, 56, beef01, 60);

    EXPECT_EQ(bee0, option.getExcludedPrefix(beef, 56));
    EXPECT_EQ(60, option.getExcludedPrefixLength());
    EXPECT_EQ("E0", util::encode::encodeHex(option.getExcludedPrefixSubnetID()));

    // Total length is a sum of option header length, excluded prefix
    // length (always 1 byte) and delegated prefix length - excluded prefix
    // length rounded to bytes.
    EXPECT_EQ(Option::OPTION6_HDR_LEN + 1 + 1, option.len());

    // v4 prefix is not accepted.
    EXPECT_THROW(Option6PDExclude(v4, 56, beef01, 64), BadValue);
    EXPECT_THROW(Option6PDExclude(beef, 56, v4, 64), BadValue);
    // Length greater than 128 is not accepted.
    EXPECT_THROW(Option6PDExclude(beef, 128, beef01, 129), BadValue);
    // Excluded prefix length must be greater than delegated prefix length.
    EXPECT_THROW(Option6PDExclude(beef, 56, beef01, 56), BadValue);
    // Both prefixes shifted by 56 must be equal (see RFC6603, section 4.2).
    EXPECT_THROW(Option6PDExclude(cafe, 56, beef01, 64), BadValue);
}

// This test verifies that on-wire format of the Prefix Exclude option is
// created properly.
TEST(Option6PDExcludeTest, pack) {
    // Expected wire format of the option.
    const uint8_t expected_data[] = {
        0x00, 0x43, // option code 67
        0x00, 0x02, // option length 2
        0x3F, 0x70  // excluded prefix length 63 + subnet id
    };
    std::vector<uint8_t> expected_vec(expected_data,
                                      expected_data + sizeof(expected_data));
    // Generate wire format of the option.
    util::OutputBuffer buf(128);
    Option6PDExcludePtr option;
    ASSERT_NO_THROW(option.reset(new Option6PDExclude(IOAddress("2001:db8:dead:bee0::"),
                                                      59,
                                                      IOAddress("2001:db8:dead:beef::"),
                                                      63)));
    ASSERT_NO_THROW(option->pack(buf));

    // Check that size matches.
    ASSERT_EQ(expected_vec.size(), buf.getLength());

    // Check that the generated wire format is correct.
    const uint8_t* data = static_cast<const uint8_t*>(buf.getData());
    std::vector<uint8_t> vec(data, data + buf.getLength());
    ASSERT_TRUE(std::equal(vec.begin(), vec.end(), expected_vec.begin()));
}

// This test verifies parsing option wire format with subnet id of
// 1 byte.
TEST(Option6PDExcludeTest, unpack1ByteSubnetId) {
    const uint8_t data[] = {
        0x00, 0x43, // option code 67
        0x00, 0x02, // option length 2
        0x40, 0x78  // excluded prefix length 60 + subnet id
    };
    std::vector<uint8_t> vec(data, data + sizeof(data));

    // Parse option.
    Option6PDExcludePtr option;
    ASSERT_NO_THROW(
        option.reset(new Option6PDExclude(vec.begin() + 4, vec.end()))
    );

    // Make sure that the option has been parsed correctly.
    EXPECT_EQ("2001:db8:dead:beef::",
              option->getExcludedPrefix(IOAddress("2001:db8:dead:bee0::1"), 59).toText());
    EXPECT_EQ(64, static_cast<int>(option->getExcludedPrefixLength()));
}

// This test verifies parsing option wire format with subnet id of
// 2 bytes.
TEST(Option6PDExcludeTest, unpack2ByteSubnetId) {
    const uint8_t data[] = {
        0x00, 0x43,       // option code 67
        0x00, 0x02,       // option length
        0x40, 0xbe, 0xef  // excluded prefix length 60 + subnet id
    };
    std::vector<uint8_t> vec(data, data + sizeof(data));

    // Parse option.
    Option6PDExcludePtr option;
    ASSERT_NO_THROW(
        option.reset(new Option6PDExclude(vec.begin() + 4, vec.end()))
    );

    // Make sure that the option has been parsed correctly.
    EXPECT_EQ("2001:db8:dead:beef::",
              option->getExcludedPrefix(IOAddress("2001:db8:dead::"), 48).toText());
    EXPECT_EQ(64, static_cast<int>(option->getExcludedPrefixLength()));
}

// This test verifies that errors are reported when option buffer contains
// invalid option data.
TEST(Option6PDExcludeTest, unpackErrors) {
    const uint8_t data[] = {
        0x00, 0x43,
        0x00, 0x02,
        0x40, 0x78
    };
    std::vector<uint8_t> vec(data, data + sizeof(data));

    // Option has no IPv6 subnet id.
    EXPECT_THROW(Option6PDExclude(vec.begin() + 4, vec.end() - 1),
                 BadValue);

    // IPv6 subnet id is 0.
    vec[4] = 0x00;
    EXPECT_THROW(Option6PDExclude(vec.begin() + 4, vec.end()),
                 BadValue);
}

// This test verifies conversion of the Prefix Exclude option to the
// textual format.
TEST(Option6PDExcludeTest, toText) {
    Option6PDExclude option(bee0, 59, beef, 64);
    EXPECT_EQ("type=00067, len=00002: excluded-prefix-len=64, subnet-id=0x78",
              option.toText());
}

// This test verifies calculation of the Prefix Exclude option length.
TEST(Option6PDExcludeTest, len) {
   Option6PDExcludePtr option;
   // The IPv6 subnet id is 2 bytes long. Hence the total length is
   // 2 bytes (option code) +  2 bytes (option length) + 1 byte
   // (excluded prefix length) + 2 bytes (IPv6 subnet id) = 7 bytes.
   ASSERT_NO_THROW(option.reset(new Option6PDExclude(bee0, 48, beef, 64)));
   EXPECT_EQ(7, option->len());

   // IPv6 subnet id is 1 byte long. The total length is 6.
   ASSERT_NO_THROW(option.reset(new Option6PDExclude(bee0, 59, beef, 64)));
   EXPECT_EQ(6, option->len());
}

} // anonymous namespace
