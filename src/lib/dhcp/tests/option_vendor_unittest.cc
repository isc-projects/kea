// Copyright (C) 2013,2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <exceptions/exceptions.h>
#include <util/buffer.h>
#include <util/encode/hex.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;
using boost::scoped_ptr;

namespace {

class OptionVendorTest : public ::testing::Test {
public:
    OptionVendorTest() {
    }

    OptionBuffer createV4VendorOptions() {

        // Copied from wireshark, file docsis-*-CG3000DCR-Registration-Filtered.cap
        // packet #1
        /* V-I Vendor-specific Information (125)
           Length: 127
           Enterprise ID: Cable Television Laboratories, Inc. (4491)
           Suboption 1: Option Request
           Suboption 5: Modem capabilties */
        string from_wireshark = "7d7f0000118b7a01010205750101010201030301010401"
            "0105010106010107010f0801100901030a01010b01180c01010d0200400e020010"
            "0f010110040000000211010014010015013f1601011701011801041901041a0104"
            "1b01201c01021d01081e01201f0110200110210102220101230100240100250101"
            "260200ff270101";

        OptionBuffer bin;
        // Decode the hex string and store it in bin (which happens
        // to be OptionBuffer format)
        isc::util::encode::decodeHex(from_wireshark, bin);

        return (bin);
    }

    OptionBuffer createV6VendorOption() {

        // Copied from wireshark, docsis-CG3000DCR-Registration-v6CMM-Filtered.cap
        // packet #1 (v6 vendor option with lots of cable modem specific data)
        string from_wireshark = "001100ff0000118b0001000a0020002100220025002600"
            "02000345434d0003000b45434d3a45524f555445520004000d3242523232395534"
            "303034344300050004312e30340006000856312e33332e303300070007322e332e"
            "3052320008000630303039354200090009434733303030444352000a00074e6574"
            "6765617200230077057501010102010303010104010105010106010107010f0801"
            "100901030a01010b01180c01010d0200400e0200100f0101100400000002110100"
            "14010015013f1601011701011801041901041a01041b01201c01021d01081e0120"
            "1f0110200110210102220101230100240100250101260200ff2701010024000620"
            "e52ab81514";
        /* Vendor-specific Information
                Option: Vendor-specific Information (17)
                Length: 255
                Value: 0000118b0001000a00200021002200250026000200034543...
                Enterprise ID: Cable Television Laboratories, Inc. (4491)
                Suboption 1: Option Request =  32 33 34 37 38
                Suboption 2: Device Type = "ECM"
                Suboption 3: Embedded Components = "ECM:EROUTER"
                Suboption 4: Serial Number = "2BR229U40044C"
                Suboption 5: Hardware Version = "1.04"
                Suboption 6: Software Version = "V1.33.03"
                Suboption 7: Boot ROM Version = "2.3.0R2"
                Suboption 8: Organization Unique Identifier = "00095B"
                Suboption 9: Model Number = "CG3000DCR"
                Suboption 10: Vendor Name = "Netgear"
                Suboption 35: TLV5 = 057501010102010303010104010105010106010107010f08...
                Suboption 36: Device Identifier = 20e52ab81514 */

        OptionBuffer bin;
        // Decode the hex string and store it in bin (which happens
        // to be OptionBuffer format)
        isc::util::encode::decodeHex(from_wireshark, bin);

        return (bin);
    }
};

// Basic test for v4 vendor option functionality
TEST_F(OptionVendorTest, v4Basic) {

    uint32_t vendor_id = 1234;

    scoped_ptr<Option> opt;
    EXPECT_NO_THROW(opt.reset(new OptionVendor(Option::V4, vendor_id)));

    EXPECT_EQ(Option::V4, opt->getUniverse());
    EXPECT_EQ(DHO_VIVSO_SUBOPTIONS, opt->getType());

    // Minimal length is 7: 1(type) + 1(length) + 4(vendor-id) + datalen(1)
    EXPECT_EQ(7, opt->len());

    // Check destructor
    EXPECT_NO_THROW(opt.reset());
}

// Basic test for v6 vendor option functionality
TEST_F(OptionVendorTest, v6Basic) {

    uint32_t vendor_id = 1234;

    scoped_ptr<Option> opt;
    EXPECT_NO_THROW(opt.reset(new OptionVendor(Option::V6, vendor_id)));

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(D6O_VENDOR_OPTS, opt->getType());

    // Minimal length is 8: 2(type) + 2(length) + 4(vendor-id)
    EXPECT_EQ(8, opt->len());

    // Check destructor
    EXPECT_NO_THROW(opt.reset());
}

// Tests whether we can parse v4 vendor options properly
TEST_F(OptionVendorTest, v4Parse) {
    OptionBuffer binary = createV4VendorOptions();

    // Let's create vendor option based on incoming buffer
    OptionVendorPtr vendor;
    ASSERT_NO_THROW(vendor.reset(new OptionVendor(Option::V4, binary.begin() + 2,
                                                  binary.end())));

    // We know that there are supposed to be 2 options inside
    EXPECT_TRUE(vendor->getOption(DOCSIS3_V4_ORO));
    EXPECT_TRUE(vendor->getOption(5));
}

// Tests whether we can parse and then pack a v4 option.
TEST_F(OptionVendorTest, packUnpack4) {
    OptionBuffer binary = createV4VendorOptions();

    OptionVendorPtr vendor;

    // Create vendor option (ignore the first 2 bytes, these are option code
    // and option length
    ASSERT_NO_THROW(vendor.reset(new OptionVendor(Option::V4, binary.begin() + 2,
                                                  binary.end())));

    OutputBuffer output(0);

    EXPECT_NO_THROW(vendor->pack(output));

    ASSERT_EQ(binary.size(), output.getLength());

    // We're lucky, because the packet capture we have happens to have options
    // with monotonically increasing values (1 and 5), so our pack() method
    // will pack them in exactly the same order as in the original.
    EXPECT_FALSE(memcmp(&binary[0], output.getData(), output.getLength()));
}

// Tests whether we can parse v6 vendor options properly
TEST_F(OptionVendorTest, v6Parse) {
    OptionBuffer binary = createV6VendorOption();

    OptionVendorPtr vendor;
    // Create vendor option (ignore the first 4 bytes. These are option code
    // (2 bytes) and option length (2 bytes).
    ASSERT_NO_THROW(vendor.reset(new OptionVendor(Option::V6, binary.begin() + 4,
                                                  binary.end())));

    OptionPtr opt;
    opt = vendor->getOption(DOCSIS3_V6_ORO);
    ASSERT_TRUE(opt);
    OptionUint16ArrayPtr oro =
        boost::dynamic_pointer_cast<OptionUint16Array>(opt);

    // Check that all remaining expected options are there
    EXPECT_TRUE(vendor->getOption(2));
    EXPECT_TRUE(vendor->getOption(3));
    EXPECT_TRUE(vendor->getOption(4));
    EXPECT_TRUE(vendor->getOption(5));
    EXPECT_TRUE(vendor->getOption(6));
    EXPECT_TRUE(vendor->getOption(7));
    EXPECT_TRUE(vendor->getOption(8));
    EXPECT_TRUE(vendor->getOption(9));
    EXPECT_TRUE(vendor->getOption(10));
    EXPECT_TRUE(vendor->getOption(35));
    EXPECT_TRUE(vendor->getOption(36));

    // Check that there are no other options there
    for (uint16_t i = 11; i < 35; ++i) {
        EXPECT_FALSE(vendor->getOption(i));
    }

    for (uint16_t i = 37; i < 65535; ++i) {
        EXPECT_FALSE(vendor->getOption(i));
    }
}

// Tests whether we can parse and then pack a v6 option.
TEST_F(OptionVendorTest, packUnpack6) {
    OptionBuffer binary = createV6VendorOption();

    OptionVendorPtr vendor;

    // Create vendor option (ignore the first 4 bytes. These are option code
    // (2 bytes) and option length (2 bytes).
    ASSERT_NO_THROW(vendor.reset(new OptionVendor(Option::V6, binary.begin() + 4,
                                                  binary.end())));

    OutputBuffer output(0);

    EXPECT_NO_THROW(vendor->pack(output));

    ASSERT_EQ(binary.size(), output.getLength());
    EXPECT_FALSE(memcmp(&binary[0], output.getData(), output.getLength()));
}

// Tests that the vendor option is correctly returned in the textual
// format for DHCPv4 case.
TEST_F(OptionVendorTest, toText4) {
    OptionVendor option(Option::V4, 1024);
    option.addOption(OptionPtr(new OptionUint32(Option::V4, 1, 100)));

    EXPECT_EQ("type=125, len=011: 1024 (uint32) 6 (uint8),\n"
              "options:\n"
              "  type=001, len=004: 100 (uint32)",
              option.toText());
}

// Tests that the vendor option is correctly returned in the textual
// format for DHCPv6 case.
TEST_F(OptionVendorTest, toText6) {
    OptionVendor option(Option::V6, 2048);
    option.addOption(OptionPtr(new OptionUint16(Option::V6, 1, 100)));

    EXPECT_EQ("type=00017, len=00010: 2048 (uint32),\n"
              "options:\n"
              "  type=00001, len=00002: 100 (uint16)",
              option.toText());
}

}
