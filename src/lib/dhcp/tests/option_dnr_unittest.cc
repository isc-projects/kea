// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp6.h>
#include <dhcp/opaque_data_tuple.h>
#include <dhcp/option_dnr.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using boost::scoped_ptr;

namespace {

// This test verifies option constructor from wire data.
// Provided wire data is in the ADN only mode i.e. only
// Service priority and Authentication domain name FQDN
// fields are present.
TEST(OptionDnr6Test, constructorAdnOnlyMode) {
    // Prepare data to decode - ADN only mode.
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00                     // Com.
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor doesn't throw.
    scoped_ptr<OptionDnr6> option;
    EXPECT_NO_THROW(option.reset(new OptionDnr6(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V6, option->getUniverse());
    EXPECT_EQ(D6O_V6_DNR, option->getType());

    // Check if data was unpacked correctly from wire data.
    EXPECT_EQ(0x8001, option->getServicePriority());
    EXPECT_EQ(20, option->getAdnLength());
    EXPECT_EQ("myhost.example.com.", option->getAdn());
    EXPECT_EQ(0, option->getAddrLength());
    EXPECT_EQ(0, option->getSvcParamsLength());
    EXPECT_EQ(28, option->len());
}

TEST(OptionDnr6Test, constructorDataTruncated) {
    // Prepare data to decode - data too short.
    const uint8_t buf_data[] = {
        0x80, 0x01  // Service priority is 32769 dec, other data is missing
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws OutOfRange exception.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(buf.begin(), buf.end())), OutOfRange);
    ASSERT_FALSE(option);
}

TEST(OptionDnr6Test, onlyWhitespaceFqdn) {
    // Prepare data to decode - ADN only mode.
    const uint8_t buf_data[] = {
        0x80, 0x01,  // Service priority is 32769 dec
        0x00, 0x02,  // ADN Length is 2 dec
        0x01, 0x20   // FQDN consists only of whitespace
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws InvalidOptionDnr6DomainName exception.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(buf.begin(), buf.end())), InvalidOptionDnr6DomainName);
    ASSERT_FALSE(option);
}

TEST(OptionDnr6Test, noAdnFqdn) {
    // Prepare data to decode - ADN only mode.
    const uint8_t buf_data[] = {
        0x00, 0x01,  // Service priority is 1 dec
        0x00, 0x00   // ADN Length is 0 dec
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Encrypted DNS options are designed to ALWAYS include
    // an authentication domain name, so check that constructor throws
    // InvalidOptionDnr6DomainName exception.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(buf.begin(), buf.end())), InvalidOptionDnr6DomainName);
    ASSERT_FALSE(option);
}

TEST(OptionDnr6Test, truncatedFqdn) {
    // Prepare data to decode - ADN only mode.
    const uint8_t buf_data[] = {
        0x80, 0x01,                               // Service priority is 32769 dec
        0x00, 0x14,                               // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74  // FQDN data is truncated
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws OpaqueDataTupleError exception.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(buf.begin(), buf.end())), OpaqueDataTupleError);
    ASSERT_FALSE(option);
}

TEST(OptionDnr6Test, addrLenTruncated) {
    // Prepare data to decode
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x10                                             // Truncated Addr Len field
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws OutOfRange exception.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(buf.begin(), buf.end())), OutOfRange);
    ASSERT_FALSE(option);
}

TEST(OptionDnr6Test, addrLenZero) {
    // Prepare data to decode
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x00, 0x00                                       // Addr Len field value = 0
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor doesn't throw.
    scoped_ptr<OptionDnr6> option;
    EXPECT_NO_THROW(option.reset(new OptionDnr6(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V6, option->getUniverse());
    EXPECT_EQ(D6O_V6_DNR, option->getType());

    // Check if data was unpacked correctly from wire data.
    EXPECT_EQ(0x8001, option->getServicePriority());
    EXPECT_EQ(20, option->getAdnLength());
    EXPECT_EQ("myhost.example.com.", option->getAdn());
    EXPECT_EQ(0, option->getAddrLength());
    EXPECT_EQ(0, option->getSvcParamsLength());
    EXPECT_EQ(30, option->len());
}

TEST(OptionDnr6Test, addrLenNot16Modulo) {
    // Prepare data to decode
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0xFF, 0xFE                                       // Addr Len is not a multiple of 16
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws OutOfRange exception.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(buf.begin(), buf.end())), OutOfRange);
    ASSERT_FALSE(option);
}

TEST(OptionDnr6Test, validIpV6Addresses) {
    // Prepare data to decode
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x00, 0x30,                                      // Addr Len field value = 48 dec
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,  // 2001:db8:1::dead:beef
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef,
        0xff, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // ff02::face:b00c
        0x00, 0x00, 0x00, 0x00, 0xfa, 0xce, 0xb0, 0x0c,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,  // ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor doesn't throw.
    scoped_ptr<OptionDnr6> option;
    EXPECT_NO_THROW(option.reset(new OptionDnr6(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V6, option->getUniverse());
    EXPECT_EQ(D6O_V6_DNR, option->getType());

    // Check if data was unpacked correctly from wire data.
    EXPECT_EQ(0x8001, option->getServicePriority());
    EXPECT_EQ(20, option->getAdnLength());
    EXPECT_EQ("myhost.example.com.", option->getAdn());
    EXPECT_EQ(48, option->getAddrLength());
    const OptionDnr6::AddressContainer& addresses = option->getAddresses();
    EXPECT_EQ(3, addresses.size());
    EXPECT_EQ("2001:db8:1::dead:beef", addresses[0].toText());
    EXPECT_EQ("ff02::face:b00c", addresses[1].toText());
    EXPECT_EQ("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", addresses[2].toText());
    EXPECT_EQ(0, option->getSvcParamsLength());
    EXPECT_EQ(78, option->len());
}

TEST(OptionDnr6Test, svcParamsIncluded) {
    // Prepare data to decode
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x00, 0x10,                                      // Addr Len field value = 48 dec
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,  // 2001:db8:1::dead:beef
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef,
        0xff, 0xff                                       // example SvcParams data
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor doesn't throw.
    scoped_ptr<OptionDnr6> option;
    EXPECT_NO_THROW(option.reset(new OptionDnr6(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V6, option->getUniverse());
    EXPECT_EQ(D6O_V6_DNR, option->getType());

    // Check if data was unpacked correctly from wire data.
    EXPECT_EQ(0x8001, option->getServicePriority());
    EXPECT_EQ(20, option->getAdnLength());
    EXPECT_EQ("myhost.example.com.", option->getAdn());
    EXPECT_EQ(16, option->getAddrLength());
    const OptionDnr6::AddressContainer& addresses = option->getAddresses();
    EXPECT_EQ(1, addresses.size());
    EXPECT_EQ("2001:db8:1::dead:beef", addresses[0].toText());
    EXPECT_EQ(2, option->getSvcParamsLength());
    EXPECT_EQ(48, option->len());
}

}  // namespace