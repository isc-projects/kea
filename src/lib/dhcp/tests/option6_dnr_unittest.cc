// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/option6_dnr.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;

namespace {

// This test verifies option constructor from wire data.
// Provided wire data is in the ADN only mode i.e. only
// Service priority and Authentication domain name FQDN
// fields are present.
TEST(Option6DnrTest, onWireCtorAdnOnlyMode) {
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
    Option6DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V6, option->getUniverse());
    EXPECT_EQ(D6O_V6_DNR, option->getType());

    // Check if data was unpacked correctly from wire data.
    EXPECT_EQ(0x8001, option->getServicePriority());
    EXPECT_EQ(20, option->getAdnLength());
    EXPECT_EQ("myhost.example.com.", option->getAdnAsText());

    // This is ADN only mode, so Addr Length and SvcParams Length
    // are both expected to be zero.
    EXPECT_EQ(0, option->getAddrLength());
    EXPECT_EQ(0, option->getSvcParamsLength());

    // BTW let's check if len() works ok.
    // expected len: 20 (FQDN) + 2 (ADN Len) + 2 (Service priority) + 4 (headers) = 28.
    EXPECT_EQ(28, option->len());

    // BTW let's check if toText() works ok.
    // toText() len does not count in headers len.
    EXPECT_EQ("type=144(V6_DNR), len=24, "
              "service_priority=32769, adn_length=20, "
              "adn='myhost.example.com.'",
              option->toText());
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - mandatory fields are truncated.
TEST(Option6DnrTest, onWireCtorDataTruncated) {
    // Prepare data to decode - data too short.
    const uint8_t buf_data[] = {
        0x80, 0x01  // Service priority is 32769 dec, other data is missing
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws OutOfRange exception.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())), OutOfRange);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - ADN FQDN contains only whitespace - non-valid FQDN.
TEST(Option6DnrTest, onWireCtorOnlyWhitespaceFqdn) {
    // Prepare data to decode - ADN only mode.
    const uint8_t buf_data[] = {
        0x80, 0x01,  // Service priority is 32769 dec
        0x00, 0x02,  // ADN Length is 2 dec
        0x01, 0x20   // FQDN consists only of whitespace
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws InvalidOptionDnrDomainName exception.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())), InvalidOptionDnrDomainName);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - ADN Length is 0 and no ADN FQDN at all.
TEST(Option6DnrTest, onWireCtorNoAdnFqdn) {
    // Prepare data to decode - ADN only mode.
    const uint8_t buf_data[] = {
        0x00, 0x01,  // Service priority is 1 dec
        0x00, 0x00   // ADN Length is 0 dec
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Encrypted DNS options are designed to ALWAYS include
    // an authentication domain name, so check that constructor throws
    // InvalidOptionDnrDomainName exception.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())), InvalidOptionDnrDomainName);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - FQDN data is truncated.
TEST(Option6DnrTest, onWireCtorTruncatedFqdn) {
    // Prepare data to decode - ADN only mode.
    const uint8_t buf_data[] = {
        0x80, 0x01,                               // Service priority is 32769 dec
        0x00, 0x14,                               // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74  // FQDN data is truncated
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws BadValue exception.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())), BadValue);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - Addr Length field truncated.
TEST(Option6DnrTest, onWireCtorAddrLenTruncated) {
    // Prepare data to decode.
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
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())), OutOfRange);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - Addr length is 0 and no IPv6 addresses at all.
TEST(Option6DnrTest, onWireCtorAddrLenZero) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x00, 0x00                                       // Addr Len field value = 0
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws OutOfRange exception.
    // If additional data is supplied (i.e. not ADN only mode),
    // the option includes at least one valid IP address.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())), OutOfRange);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - Addr length is not a multiple of 16.
TEST(Option6DnrTest, onWireCtorAddrLenNot16Modulo) {
    // Prepare data to decode.
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
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())), OutOfRange);
    ASSERT_FALSE(option);
}

// This test verifies option constructor from wire data.
// Provided wire data contains also IPv6 addresses.
TEST(Option6DnrTest, onWireCtorValidIpV6Addresses) {
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
    Option6DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V6, option->getUniverse());
    EXPECT_EQ(D6O_V6_DNR, option->getType());

    // Check if data was unpacked correctly from wire data.
    EXPECT_EQ(0x8001, option->getServicePriority());
    EXPECT_EQ(20, option->getAdnLength());
    EXPECT_EQ("myhost.example.com.", option->getAdnAsText());
    EXPECT_EQ(48, option->getAddrLength());
    const Option6Dnr::AddressContainer& addresses = option->getAddresses();
    EXPECT_EQ(3, addresses.size());
    EXPECT_EQ("2001:db8:1::dead:beef", addresses[0].toText());
    EXPECT_EQ("ff02::face:b00c", addresses[1].toText());
    EXPECT_EQ("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", addresses[2].toText());
    EXPECT_EQ(0, option->getSvcParamsLength());

    // BTW let's check if len() works ok.
    // expected len: 20 (FQDN) + 2 (ADN Len) + 2 (Service priority) + 4 (headers) = 28
    //             + 48 (3 IP addresses) + 2 (Addr Len) = 78.
    EXPECT_EQ(78, option->len());

    // BTW let's check if toText() works ok.
    // toText() len does not count in headers len.
    EXPECT_EQ("type=144(V6_DNR), len=74, "
              "service_priority=32769, adn_length=20, "
              "adn='myhost.example.com.', "
              "addr_length=48, "
              "address(es): 2001:db8:1::dead:beef "
              "ff02::face:b00c "
              "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff",
              option->toText());
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - IPv6 addresses are truncated.
TEST(Option6DnrTest, onWireCtorTruncatedIpV6Addresses) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x00, 0x30,                                      // Addr Len field value = 48 dec
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,  // 2001:db8:1::dead:beef
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef,
        0xff, 0x02, 0x00                                 // IPv6 address truncated
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws OutOfRange exception.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())), OutOfRange);
    ASSERT_FALSE(option);
}

// This test verifies option constructor from wire data.
// Provided wire data contains also IPv6 address and Svc Params.
TEST(Option6DnrTest, onWireCtorSvcParamsIncluded) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x00, 0x10,                                      // Addr Len field value = 16 dec
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,  // 2001:db8:1::dead:beef
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef,  //
        0,    1,                                         // SvcParamKey alpn
        0,    8,                                         // SvcParamVal Len
        3,    'd',  'o',  't',                           // 3 octets long alpn-id dot
        3,    'd',  'o',  'q'                            // 3 octets long alpn-id doq
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor doesn't throw.
    Option6DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V6, option->getUniverse());
    EXPECT_EQ(D6O_V6_DNR, option->getType());

    // Check if data was unpacked correctly from wire data.
    EXPECT_EQ(0x8001, option->getServicePriority());
    EXPECT_EQ(20, option->getAdnLength());
    EXPECT_EQ("myhost.example.com.", option->getAdnAsText());
    EXPECT_EQ(16, option->getAddrLength());
    const Option6Dnr::AddressContainer& addresses = option->getAddresses();
    EXPECT_EQ(1, addresses.size());
    EXPECT_EQ("2001:db8:1::dead:beef", addresses[0].toText());

    // Reference SvcParams on-wire data buffer.
    const OptionBuffer svc_params = {
        0, 1,              // SvcParamKey alpn
        0, 8,              // SvcParamVal Len
        3, 'd', 'o', 't',  // 3 octets long alpn-id dot
        3, 'd', 'o', 'q'   // 3 octets long alpn-id doq
    };
    EXPECT_EQ(svc_params, option->getSvcParams());
    EXPECT_EQ(svc_params.size(), option->getSvcParamsLength());

    // BTW let's check if len() works ok.
    // expected len: 20 (FQDN) + 2 (ADN Len) + 2 (Service priority) + 4 (headers) = 28
    //             + 16 (IP address) + 2 (Addr Len) + 12 (SvcParams) = 58.
    EXPECT_EQ(58, option->len());

    // BTW let's check if toText() works ok.
    // toText() len does not count in headers len.
    EXPECT_EQ("type=144(V6_DNR), len=54, "
              "service_priority=32769, adn_length=20, "
              "adn='myhost.example.com.', "
              "addr_length=16, "
              "address(es): 2001:db8:1::dead:beef, "
              "svc_params='alpn=dot,doq'",
              option->toText());
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - SvcParams Key contains truncated SvcParamVal Len data.
TEST(Option6DnrTest, onWireCtorSvcParamsTruncatedParamLen) {
    // Prepare data to decode with invalid SvcParams.
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x00, 0x10,                                      // Addr Len field value
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,  // 2001:db8:1::dead:beef
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef,  //
        0,    1,                                         // SvcParamKey alpn
        0,    8,                                         // SvcParamVal Len
        3,    'd',  'o',  't',                           // 3 octets long alpn-id dot
        3,    'd',  'o',  'q',                           // 3 octets long alpn-id doq
        0,    3,                                         // SvcParamKey port
        0                                                // truncated SvcParamVal Len
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws exception.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())), OutOfRange);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - SvcParams Key contains truncated data.
TEST(Option6DnrTest, onWireCtorSvcParamsTruncatedParamData) {
    // Prepare data to decode with invalid SvcParams.
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x00, 0x10,                                      // Addr Len field value
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,  // 2001:db8:1::dead:beef
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef,  //
        0,    1,                                         // SvcParamKey alpn
        0,    8,                                         // SvcParamVal Len
        3,    'd',  'o',  't',                           // 3 octets long alpn-id dot
        3,    'd',  'o',  'q',                           // 3 octets long alpn-id doq
        0,    3,                                         // SvcParamKey port
        0,    2,                                         // SvcParamVal Len
        1                                                // truncated data
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws exception.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())), InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - SvcParams Key contains unknown key.
TEST(Option6DnrTest, onWireCtorSvcParamsUnknownKey) {
    // Prepare data to decode with invalid SvcParams.
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x00, 0x10,                                      // Addr Len field value
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,  // 2001:db8:1::dead:beef
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef,  //
        0,    1,                                         // SvcParamKey alpn
        0,    8,                                         // SvcParamVal Len
        3,    'd',  'o',  't',                           // 3 octets long alpn-id dot
        3,    'd',  'o',  'q',                           // 3 octets long alpn-id doq
        0,    99,                                        // unknown SvcParamKey
        0,    2,                                         // SvcParamVal Len
        1,    2                                          // random data
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws exception.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())), InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - SvcParams Key contains forbidden key.
TEST(Option6DnrTest, onWireCtorSvcParamsForbiddenKey) {
    // Prepare data to decode with invalid SvcParams.
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x00, 0x10,                                      // Addr Len field value
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,  // 2001:db8:1::dead:beef
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef,  //
        0,    1,                                         // SvcParamKey alpn
        0,    8,                                         // SvcParamVal Len
        3,    'd',  'o',  't',                           // 3 octets long alpn-id dot
        3,    'd',  'o',  'q',                           // 3 octets long alpn-id doq
        0,    4,                                         // SvcParamKey ipv4hint is forbidden
        0,    2,                                         // SvcParamVal Len
        1,    2                                          // random data
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws exception.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())), InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - SvcParams Key contains unsupported key.
TEST(Option6DnrTest, onWireCtorSvcParamsUnsupportedKey) {
    // Prepare data to decode with invalid SvcParams.
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x00, 0x10,                                      // Addr Len field value
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,  // 2001:db8:1::dead:beef
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef,  //
        0,    1,                                         // SvcParamKey alpn
        0,    8,                                         // SvcParamVal Len
        3,    'd',  'o',  't',                           // 3 octets long alpn-id dot
        3,    'd',  'o',  'q',                           // 3 octets long alpn-id doq
        0,    5,  // SvcParamKey ech is unsupported in DHCP DNR option
        0,    2,  // SvcParamVal Len
        1,    2   // random data
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws exception.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())), InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - SvcParams Key contains duplicated key.
TEST(Option6DnrTest, onWireCtorSvcParamsDuplicatedKey) {
    // Prepare data to decode with invalid SvcParams.
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x00, 0x10,                                      // Addr Len field value
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,  // 2001:db8:1::dead:beef
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef,  //
        0,    1,                                         // SvcParamKey alpn
        0,    8,                                         // SvcParamVal Len
        3,    'd',  'o',  't',                           // 3 octets long alpn-id dot
        3,    'd',  'o',  'q',                           // 3 octets long alpn-id doq
        0,    1,                                         // SvcParamKey alpn is duplicated
        0,    4,                                         // SvcParamVal Len
        3,    'd',  'o',  't'                            // 3 octets long alpn-id dot
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws exception.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())), InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - SvcParams Keys are in wrong order.
TEST(Option6DnrTest, onWireCtorSvcParamsWrongKeyOrder) {
    // Prepare data to decode with invalid SvcParams.
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x00, 0x10,                                      // Addr Len field value
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,  // 2001:db8:1::dead:beef
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef,  //
        0,    3,                                         // SvcParamKey port
        0,    2,                                         // SvcParamVal Len
        23,   23,                                        // 2 octets long port number
        0,    1,                                         // SvcParamKey alpn is duplicated
        0,    4,                                         // SvcParamVal Len
        3,    'd',  'o',  't'                            // 3 octets long alpn-id dot
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws exception.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end())), InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - SvcParam key=val pair has 2 equal signs.
TEST(Option6DnrTest, fromConfigCtorSvcParamsTwoEqualSignsPerParam) {
    // Prepare example config.
    const std::string config = "100, dot1.example.org., 2001:db8::1 2001:db8::2, "
                               "alpn=dot=doq port=8530 dohpath=/q{?dns}";

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end(), true)),
                 InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - SvcParam has forbidden key.
TEST(Option6DnrTest, fromConfigCtorSvcParamsForbiddenKey) {
    // Prepare example config.
    const std::string config = "100, dot1.example.org., 2001:db8::1 2001:db8::2, "
                               "ipv6hint=something port=8530 dohpath=/q{?dns}";

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end(), true)),
                 InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - Svc Params key was repeated.
TEST(Option6DnrTest, fromConfigCtorSvcParamsKeyRepeated) {
    // Prepare example config.
    const std::string config = "100, dot1.example.org., 2001:db8::1 2001:db8::2, "
                               "port=8530 port=1234 dohpath=/q{?dns}";

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end(), true)),
                 InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - IPv4 address given.
TEST(Option6DnrTest, fromConfigCtorIPv4Address) {
    // Prepare example config.
    const std::string config = "100, dot1.example.org., 10.0.2.3";

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option6DnrPtr option;
    EXPECT_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end(), true)),
                 BadValue);
    ASSERT_FALSE(option);
}

// This test verifies that string representation of the option returned by
// toText method is correctly formatted.
TEST(Option6DnrTest, toText) {
    // Prepare example config.
    const std::string config = "9, myhost.example.com., 2001:db8:1::baca, "
                               "alpn=h3 port=1234 dohpath=/q{?dns}";

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor doesn't throw.
    Option6DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option6Dnr(buf.begin(), buf.end(), true)));
    ASSERT_TRUE(option);

    const int indent = 4;
    std::string expected = "    type=144(V6_DNR), len=67, "  // the indentation of 4 spaces
                           "service_priority=9, adn_length=20, "
                           "adn='myhost.example.com.', addr_length=16, "
                           "address(es): 2001:db8:1::baca, svc_params='alpn=h3 port=1234 "
                           "dohpath=/q{?dns}'";
    EXPECT_EQ(expected, option->toText(indent));
}

// This test verifies that the option is correctly created in ADN only mode,
// when constructor from convenient string notation is used.
TEST(Option6DnrTest, fromConfigCtorPackAdnOnlyMode) {
    // Prepare example config.
    const std::string config = "9, myhost.example.com.";

    OptionBuffer in_buf;
    in_buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor doesn't throw.
    Option6DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option6Dnr(in_buf.begin(), in_buf.end(), true)));
    ASSERT_TRUE(option);

    // Prepare on-wire format of the option.
    isc::util::OutputBuffer buf(10);
    ASSERT_NO_THROW(option->pack(buf));

    // Prepare reference data.
    const uint8_t ref_data[] = {
        0x00, D6O_V6_DNR,                                // Option code
        0x00, 24,                                        // Option len=24 dec
        0x00, 0x09,                                      // Service priority is 9 dec
        0x00, 20,                                        // ADN Length is 20 dec
        0x06, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: myhost.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00                     // com.
    };

    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, buf.getData(), buf.getLength()));
}

// This test verifies on-wire format of the option is correctly created with pack
// method when IP addresses and Svc Params are also included.
TEST(Option6DnrTest, pack) {
    // Prepare example config.
    const std::string config = "9, myhost.example.com., 2001:db8:1::dead:beef ff02::face:b00c,"
                               " alpn=imap";

    OptionBuffer in_buf;
    in_buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor doesn't throw.
    Option6DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option6Dnr(in_buf.begin(), in_buf.end(), true)));
    ASSERT_TRUE(option);

    // Prepare on-wire format of the option.
    isc::util::OutputBuffer buf(10);
    ASSERT_NO_THROW(option->pack(buf));

    // Prepare reference data.
    const uint8_t ref_data[] = {
        0x00, D6O_V6_DNR,                                           // Option code
        0x00, 67,                                                   // Option len=67 dec
        0x00, 0x09,                                                 // Service priority is 9 dec
        0x00, 0x14,                                                 // ADN Length is 20 dec
        0x06, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74,                   // FQDN: myhost.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,             // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                               // com.
        0x00, 0x20,                                                 // Addr Len field value = 32 dec
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,             // 2001:db8:1::dead:beef
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef, 0xff, 0x02, //
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                         // ff02::face:b00c
        0x00, 0x00, 0x00, 0x00, 0xfa, 0xce, 0xb0, 0x0c,             //
        0,    1,                                                    // SvcParamKey alpn
        0,    5,                                                    // SvcParamVal len
        4,    'i',  'm',  'a',  'p'                                 // alpn-id
    };

    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, buf.getData(), buf.getLength()));
}

}  // namespace