// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
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
TEST(OptionDnr6Test, onWireCtorAdnOnlyMode) {
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
              "adn='myhost.example.com.'", option->toText());
}

TEST(OptionDnr6Test, onWireCtorDataTruncated) {
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

TEST(OptionDnr6Test, onWireCtorOnlyWhitespaceFqdn) {
    // Prepare data to decode - ADN only mode.
    const uint8_t buf_data[] = {
        0x80, 0x01,  // Service priority is 32769 dec
        0x00, 0x02,  // ADN Length is 2 dec
        0x01, 0x20   // FQDN consists only of whitespace
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws InvalidOptionDnrDomainName exception.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(buf.begin(), buf.end())), InvalidOptionDnrDomainName);
    ASSERT_FALSE(option);
}

TEST(OptionDnr6Test, onWireCtorNoAdnFqdn) {
    // Prepare data to decode - ADN only mode.
    const uint8_t buf_data[] = {
        0x00, 0x01,  // Service priority is 1 dec
        0x00, 0x00   // ADN Length is 0 dec
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Encrypted DNS options are designed to ALWAYS include
    // an authentication domain name, so check that constructor throws
    // InvalidOptionDnrDomainName exception.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(buf.begin(), buf.end())), InvalidOptionDnrDomainName);
    ASSERT_FALSE(option);
}

TEST(OptionDnr6Test, onWireCtorTruncatedFqdn) {
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

TEST(OptionDnr6Test, onWireCtorAddrLenTruncated) {
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

TEST(OptionDnr6Test, onWireCtorAddrLenZero) {
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
    // Create option instance. Check that constructor throws OutOfRange exception.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(buf.begin(), buf.end())), OutOfRange);
    ASSERT_FALSE(option);
}

TEST(OptionDnr6Test, onWireCtorAddrLenNot16Modulo) {
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

TEST(OptionDnr6Test, onWireCtorValidIpV6Addresses) {
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

    // BTW let's check if len() works ok.
    // expected len: 20 (FQDN) + 2 (ADN Len) + 2 (Service priority) + 4 (headers) = 28
    // + 48 (3 IP addresses) + 2 (Addr Len) = 78
    EXPECT_EQ(78, option->len());

    // BTW let's check if toText() works ok.
    // toText() len does not count in headers len.
    EXPECT_EQ("type=144(V6_DNR), len=74, "
              "service_priority=32769, adn_length=20, "
              "adn='myhost.example.com.', "
              "addr_length=48, "
              "address(es): 2001:db8:1::dead:beef "
              "ff02::face:b00c "
              "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", option->toText());
}

TEST(OptionDnr6Test, onWireCtorTruncatedIpV6Addresses) {
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
        0xff, 0x02, 0x00                                 // IPv6 address truncated
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws OutOfRange exception.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(buf.begin(), buf.end())), OutOfRange);
    ASSERT_FALSE(option);
}

TEST(OptionDnr6Test, onWireCtorSvcParamsIncluded) {
    // Prepare data to decode
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x00, 0x10,                                      // Addr Len field value = 16 dec
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,  // 2001:db8:1::dead:beef
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef,
        'a', 'b', 'c'                                    // example SvcParams data
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
    EXPECT_EQ(3, option->getSvcParamsLength());

    // BTW let's check if len() works ok.
    // expected len: 20 (FQDN) + 2 (ADN Len) + 2 (Service priority) + 4 (headers) = 28
    // + 16 (IP address) + 2 (Addr Len) + 3 (SvcParams) = 49
    EXPECT_EQ(49, option->len());

    // BTW let's check if toText() works ok.
    // toText() len does not count in headers len.
    EXPECT_EQ("type=144(V6_DNR), len=45, "
              "service_priority=32769, adn_length=20, "
              "adn='myhost.example.com.', "
              "addr_length=16, "
              "address(es): 2001:db8:1::dead:beef, "
              "svc_params='abc'", option->toText());
}

TEST(OptionDnr6Test, onWireCtorSvcParamsInvalidCharKey) {
    // Prepare data to decode with invalid SvcParams
    const uint8_t buf_data[] = {
        0x80, 0x01,                                      // Service priority is 32769 dec
        0x00, 0x14,                                      // ADN Length is 20 dec
        0x06, 0x4D, 0x79, 0x68, 0x6F, 0x73, 0x74,        // FQDN: Myhost.
        0x07, 0x45, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // Example.
        0x03, 0x43, 0x6F, 0x6D, 0x00,                    // Com.
        0x00, 0x10,                                      // Addr Len field value = 48 dec
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01, 0x00, 0x00,  // 2001:db8:1::dead:beef
        0x00, 0x00, 0x00, 0x00, 0xde, 0xad, 0xbe, 0xef,
        'a', '+', 'c'                                    // Allowed "a"-"z", "0"-"9", and "-".
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor throws InvalidOptionDnrSvcParams exception.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(buf.begin(), buf.end())), InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// This test verifies option constructor in ADN only mode.
// Service priority and ADN are provided via ctor.
TEST(OptionDnr6Test, adnOnlyModeCtor) {
    // Prepare example parameters
    const uint16_t service_priority = 9;
    const std::string adn = "myhost.example.com.";

    // Create option instance. Check that constructor doesn't throw.
    scoped_ptr<OptionDnr6> option;
    EXPECT_NO_THROW(option.reset(new OptionDnr6(service_priority, adn)));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V6, option->getUniverse());
    EXPECT_EQ(D6O_V6_DNR, option->getType());
    EXPECT_EQ(service_priority, option->getServicePriority());
    EXPECT_EQ(20, option->getAdnLength());
    EXPECT_EQ(adn, option->getAdn());

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
              "service_priority=9, adn_length=20, "
              "adn='myhost.example.com.'", option->toText());
}

TEST(OptionDnr6Test, adnOnlyModeCtorNoFqdn) {
    // Prepare example parameters
    const uint16_t service_priority = 9;
    const std::string adn = ""; // invalid empty ADN

    // Create option instance. Check that constructor throws.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(service_priority, adn)), InvalidOptionDnrDomainName);
    ASSERT_FALSE(option);
}

// This test verifies option constructor where all fields
// i.e. Service priority, ADN, IP address(es) and Service params
// are provided as ctor parameters.
TEST(OptionDnr6Test, allFieldsCtor) {
    // Prepare example parameters
    const uint16_t service_priority = 9;
    const std::string adn = "myhost.example.com.";
    OptionDnr6::AddressContainer addresses;
    addresses.push_back(isc::asiolink::IOAddress("2001:db8:1::baca"));
    const std::string svc_params = "alpn";

    // Create option instance. Check that constructor throws.
    scoped_ptr<OptionDnr6> option;
    EXPECT_NO_THROW(option.reset(new OptionDnr6(service_priority, adn, addresses, svc_params)));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V6, option->getUniverse());
    EXPECT_EQ(D6O_V6_DNR, option->getType());
    EXPECT_EQ(service_priority, option->getServicePriority());
    EXPECT_EQ(20, option->getAdnLength());
    EXPECT_EQ(adn, option->getAdn());
    EXPECT_EQ(16, option->getAddrLength());
    EXPECT_EQ(4, option->getSvcParamsLength());

    // BTW let's check if len() works ok.
    // expected len: 20 (FQDN) + 2 (ADN Len) + 2 (Service priority) + 4 (headers) = 28
    //             + 16 (IPv6) + 2 (Addr Len) + 4 (Svc Params) = 50
    EXPECT_EQ(50, option->len());

    // BTW let's check if toText() works ok.
    // toText() len does not count in headers len.
    EXPECT_EQ("type=144(V6_DNR), len=46, "
              "service_priority=9, adn_length=20, "
              "adn='myhost.example.com.', addr_length=16, "
              "address(es): 2001:db8:1::baca, svc_params='alpn'", option->toText());
}

TEST(OptionDnr6Test, allFieldsCtorNoIpAddress) {
    // Prepare example parameters
    const uint16_t service_priority = 9;
    const std::string adn = "myhost.example.com.";
    const OptionDnr6::AddressContainer addresses; // no IPv6 address in here
    const std::string svc_params = "alpn";

    // Create option instance. Check that constructor throws.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(service_priority, adn, addresses, svc_params)), OutOfRange);
    ASSERT_FALSE(option);
}

TEST(OptionDnr6Test, svcParamsTwoEqualSignsPerParam) {
    // Prepare example parameters
    const uint16_t service_priority = 9;
    const std::string adn = "myhost.example.com.";
    OptionDnr6::AddressContainer addresses;
    addresses.push_back(isc::asiolink::IOAddress("2001:db8:1::baca"));
    const std::string svc_params = "key123=val1=val2 key234"; // invalid svc param - 2 equal signs

    // Create option instance. Check that constructor throws.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(service_priority, adn, addresses, svc_params)), InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

TEST(OptionDnr6Test, svcParamsForbiddenKey) {
    // Prepare example parameters
    const uint16_t service_priority = 9;
    const std::string adn = "myhost.example.com.";
    OptionDnr6::AddressContainer addresses;
    addresses.push_back(isc::asiolink::IOAddress("2001:db8:1::baca"));
    const std::string svc_params = "key123=val1 ipv6hint"; // forbidden svc param key - ipv6hint

    // Create option instance. Check that constructor throws.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(service_priority, adn, addresses, svc_params)), InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

TEST(OptionDnr6Test, svcParamsKeyRepeated) {
    // Prepare example parameters
    const uint16_t service_priority = 9;
    const std::string adn = "myhost.example.com.";
    OptionDnr6::AddressContainer addresses;
    addresses.push_back(isc::asiolink::IOAddress("2001:db8:1::baca"));
    const std::string svc_params = "key123=val1 key234 key123"; // svc param key key123 repeated

    // Create option instance. Check that constructor throws.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(service_priority, adn, addresses, svc_params)), InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

TEST(OptionDnr6Test, svcParamsKeyTooLong) {
    // Prepare example parameters
    const uint16_t service_priority = 9;
    const std::string adn = "myhost.example.com.";
    OptionDnr6::AddressContainer addresses;
    addresses.push_back(isc::asiolink::IOAddress("2001:db8:1::baca"));
    const std::string svc_params = "thisisveryveryveryvery"
                                   "veryveryveryveryveryvery"
                                   "veryveryveryveryveryvery"
                                   "veryveryverylongkey"; // svc param key longer than 63

    // Create option instance. Check that constructor throws.
    scoped_ptr<OptionDnr6> option;
    EXPECT_THROW(option.reset(new OptionDnr6(service_priority, adn, addresses, svc_params)), InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

}  // namespace