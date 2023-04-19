// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/opaque_data_tuple.h>
#include <dhcp/option4_dnr.h>

#include <boost/scoped_ptr.hpp>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using boost::scoped_ptr;

namespace {

TEST(Option4DnrTest, emptyCtor) {
    // Create option instance. Check that constructor doesn't throw.
    scoped_ptr<Option4Dnr> option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr()));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V4, option->getUniverse());
    EXPECT_EQ(DHO_V4_DNR, option->getType());
}

TEST(Option4DnrTest, oneDnrOnlyModeInstance) {
    // Create option instance. Check that constructor doesn't throw.
    scoped_ptr<Option4Dnr> option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr()));
    ASSERT_TRUE(option);

    // Prepare example DNR instance to add.
    DnrInstance dnr_1 = DnrInstance(Option::V4, 1, "myhost1.example.com.");

    // Add DNR instance.
    option->addDnrInstance(dnr_1);

    // Check if member variables were correctly set inside DNR instances.
    EXPECT_EQ(1, option->getDnrInstances().size());
    EXPECT_EQ(1, option->getDnrInstances()[0].getServicePriority());
    EXPECT_EQ(21, option->getDnrInstances()[0].getAdnLength());
    EXPECT_EQ("myhost1.example.com.", option->getDnrInstances()[0].getAdnAsText());

    // This is ADN only mode, so Addr Length and SvcParams Length
    // are both expected to be zero.
    EXPECT_EQ(0, option->getDnrInstances()[0].getAddrLength());
    EXPECT_EQ(0, option->getDnrInstances()[0].getSvcParamsLength());

    // BTW let's check if len() works ok. In ADN only mode, DNR Instance Data Len
    // is set to ADN Len (21) + 3 = 24.
    // expected len: 1x(24 (ADN+ADN Len+Service priority) + 2 (DNR Instance Data Len)) + 2 (headers)
    // = 28
    EXPECT_EQ(28, option->len());

    // BTW let's check if toText() works ok.
    // toText() len does not count in headers len.
    EXPECT_EQ("type=162(V4_DNR), len=26, "
              "DNR Instance 1(Instance len=24, service_priority=1, "
              "adn_length=21, adn='myhost1.example.com.')",
              option->toText());
}

TEST(Option4DnrTest, multipleDnrOnlyModeInstances) {
    // Create option instance. Check that constructor doesn't throw.
    scoped_ptr<Option4Dnr> option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr()));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V4, option->getUniverse());
    EXPECT_EQ(DHO_V4_DNR, option->getType());

    // Prepare example DNR instances to add.
    DnrInstance dnr_1 = DnrInstance(Option::V4, 1, "myhost1.example.com.");
    DnrInstance dnr_2 = DnrInstance(Option::V4, 2, "myhost2.example.com.");
    DnrInstance dnr_3 = DnrInstance(Option::V4, 3, "myhost3.example.com.");

    // Add DNR instances.
    option->addDnrInstance(dnr_1);
    option->addDnrInstance(dnr_2);
    option->addDnrInstance(dnr_3);

    // Check if member variables were correctly set inside DNR instances.
    EXPECT_EQ(3, option->getDnrInstances().size());
    EXPECT_EQ(1, option->getDnrInstances()[0].getServicePriority());
    EXPECT_EQ(2, option->getDnrInstances()[1].getServicePriority());
    EXPECT_EQ(3, option->getDnrInstances()[2].getServicePriority());
    EXPECT_EQ(21, option->getDnrInstances()[0].getAdnLength());
    EXPECT_EQ(21, option->getDnrInstances()[1].getAdnLength());
    EXPECT_EQ(21, option->getDnrInstances()[2].getAdnLength());
    EXPECT_EQ("myhost1.example.com.", option->getDnrInstances()[0].getAdnAsText());
    EXPECT_EQ("myhost2.example.com.", option->getDnrInstances()[1].getAdnAsText());
    EXPECT_EQ("myhost3.example.com.", option->getDnrInstances()[2].getAdnAsText());

    // This is ADN only mode, so Addr Length and SvcParams Length
    // are both expected to be zero.
    EXPECT_EQ(0, option->getDnrInstances()[0].getAddrLength());
    EXPECT_EQ(0, option->getDnrInstances()[0].getSvcParamsLength());
    EXPECT_EQ(0, option->getDnrInstances()[1].getAddrLength());
    EXPECT_EQ(0, option->getDnrInstances()[1].getSvcParamsLength());
    EXPECT_EQ(0, option->getDnrInstances()[2].getAddrLength());
    EXPECT_EQ(0, option->getDnrInstances()[2].getSvcParamsLength());

    // BTW let's check if len() works ok. In ADN only mode, DNR Instance Data Len
    // is set to ADN Len (21) + 3 = 24.
    // expected len: 3x(24 (ADN+ADN Len+Service priority) + 2 (DNR Instance Data Len)) + 2 (headers)
    // = 78 + 2 = 80
    EXPECT_EQ(80, option->len());

    // BTW let's check if toText() works ok.
    // toText() len does not count in headers len.
    EXPECT_EQ("type=162(V4_DNR), len=78, "
              "DNR Instance 1(Instance len=24, service_priority=1, "
              "adn_length=21, adn='myhost1.example.com.'), "
              "DNR Instance 2(Instance len=24, service_priority=2, "
              "adn_length=21, adn='myhost2.example.com.'), "
              "DNR Instance 3(Instance len=24, service_priority=3, "
              "adn_length=21, adn='myhost3.example.com.')",
              option->toText());
}

TEST(Option4DnrTest, packOneDnrOnlyModeInstance) {
    // Create option instance. Check that constructor doesn't throw.
    scoped_ptr<Option4Dnr> option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr()));
    ASSERT_TRUE(option);

    // Prepare example DNR instance to add.
    DnrInstance dnr_1 = DnrInstance(Option::V4, 1, "myhost1.example.com.");

    // Add DNR instance.
    option->addDnrInstance(dnr_1);

    // Prepare on-wire format of the option.
    isc::util::OutputBuffer buf(10);
    ASSERT_NO_THROW(option->pack(buf));

    // Prepare reference data.
    const uint8_t ref_data[] = {
        DHO_V4_DNR,                                            // Option code
        26,                                                    // Option len=26 dec
        0x00,       24,                                        // DNR Instance Data Len
        0x00,       0x01,                                      // Service priority is 1 dec
        21,                                                    // ADN Length is 21 dec
        0x07,       0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07,       0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03,       0x63, 0x6F, 0x6D, 0x00                     // com.
    };

    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, buf.getData(), buf.getLength()));
}

TEST(Option4DnrTest, packMultipleDnrOnlyModeInstances) {
    // Create option instance. Check that constructor doesn't throw.
    scoped_ptr<Option4Dnr> option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr()));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V4, option->getUniverse());
    EXPECT_EQ(DHO_V4_DNR, option->getType());

    // Prepare example DNR instances to add.
    DnrInstance dnr_1 = DnrInstance(Option::V4, 1, "myhost1.example.com.");
    DnrInstance dnr_2 = DnrInstance(Option::V4, 2, "myhost2.example.com.");
    DnrInstance dnr_3 = DnrInstance(Option::V4, 3, "myhost3.example.com.");

    // Add DNR instances.
    option->addDnrInstance(dnr_1);
    option->addDnrInstance(dnr_2);
    option->addDnrInstance(dnr_3);

    // Prepare on-wire format of the option.
    isc::util::OutputBuffer buf(10);
    ASSERT_NO_THROW(option->pack(buf));

    // Prepare reference data.
    const uint8_t ref_data[] = {
        DHO_V4_DNR,                                            // Option code
        78,                                                    // Option len=78 dec
        0x00,       24,                                        // DNR Instance Data Len
        0x00,       0x01,                                      // Service priority is 1 dec
        21,                                                    // ADN Length is 21 dec
        0x07,       0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07,       0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03,       0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00,       24,                                        // DNR Instance Data Len
        0x00,       0x02,                                      // Service priority is 2 dec
        21,                                                    // ADN Length is 21 dec
        0x07,       0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '2',   // FQDN: myhost1.
        0x07,       0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03,       0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00,       24,                                        // DNR Instance Data Len
        0x00,       0x03,                                      // Service priority is 3 dec
        21,                                                    // ADN Length is 21 dec
        0x07,       0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '3',   // FQDN: myhost1.
        0x07,       0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03,       0x63, 0x6F, 0x6D, 0x00                     // com.
    };

    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, buf.getData(), buf.getLength()));
}

}  // namespace