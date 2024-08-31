// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/option4_dnr.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {

// This test verifies constructor from convenient string notation
// with one ADN-only-mode DNR instance.
TEST(Option4DnrTest, fromConfigCtorOneAdnOnlyModeInstance) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com.";

    OptionBuffer in_buf;
    in_buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor doesn't throw.
    Option4DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr(in_buf.begin(), in_buf.end(), true)));
    ASSERT_TRUE(option);

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

// This test verifies constructor from convenient string notation
// with multiple ADN-only-mode DNR instances.
TEST(Option4DnrTest, fromConfigCtorMultipleAdnOnlyModeInstances) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com. | "
                               "3, myhost3.example.com.";

    OptionBuffer in_buf;
    in_buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor doesn't throw.
    Option4DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr(in_buf.begin(), in_buf.end(), true)));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V4, option->getUniverse());
    EXPECT_EQ(DHO_V4_DNR, option->getType());

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

// This test verifies constructor from convenient string notation
// with two DNR instances:
// 1. ADN-only-mode DNR instance
// 2. All fields included (IP addresses and service params also) DNR instance.
TEST(Option4DnrTest, fromConfigCtorMixedDnrInstances) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, "
                               "alpn=h3 port=1234 dohpath=/q{?dns}";

    OptionBuffer in_buf;
    in_buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor doesn't throw.
    Option4DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr(in_buf.begin(), in_buf.end(), true)));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set inside DNR instances.
    EXPECT_EQ(2, option->getDnrInstances().size());
    EXPECT_EQ(1, option->getDnrInstances()[0].getServicePriority());
    EXPECT_EQ(21, option->getDnrInstances()[0].getAdnLength());
    EXPECT_EQ("myhost1.example.com.", option->getDnrInstances()[0].getAdnAsText());
    EXPECT_EQ(2, option->getDnrInstances()[1].getServicePriority());
    EXPECT_EQ(21, option->getDnrInstances()[1].getAdnLength());
    EXPECT_EQ("myhost2.example.com.", option->getDnrInstances()[1].getAdnAsText());

    EXPECT_EQ(0, option->getDnrInstances()[0].getAddrLength());
    EXPECT_EQ(0, option->getDnrInstances()[0].getSvcParamsLength());
    EXPECT_EQ(2, option->getDnrInstances()[1].getAddresses().size());
    EXPECT_EQ(8, option->getDnrInstances()[1].getAddrLength());
    EXPECT_EQ("192.168.0.1", option->getDnrInstances()[1].getAddresses()[0].toText());
    EXPECT_EQ("192.168.0.2", option->getDnrInstances()[1].getAddresses()[1].toText());

    // Reference SvcParams on-wire data buffer.
    const OptionBuffer svc_params = {
        0,   1,                                  // SvcParamKey alpn
        0,   3,                                  // SvcParamVal Len
        2,   'h',  '3',                          // 2 octets long alpn-id http/3
        0,   3,                                  // SvcParamKey port
        0,   2,                                  // SvcParamVal Len
        0x4, 0xD2,                               // 1234 in hex
        0,   7,                                  // SvcParamKey dohpath
        0,   8,                                  // SvcParamVal Len
        '/', 'q',  '{', '?', 'd', 'n', 's', '}'  // dohpath value
    };

    EXPECT_EQ(svc_params, option->getDnrInstances()[1].getSvcParams());
    EXPECT_EQ(svc_params.size(), option->getDnrInstances()[1].getSvcParamsLength());

    // BTW let's check if len() works ok. In ADN only mode, DNR Instance Data Len
    // is set to ADN Len (21) + 3 = 24.
    // expected len: 1x(24 (ADN+ADN Len+Service priority) + 2 (DNR Instance Data Len)) + 2 (headers)
    // + 24 (ADN+ADN Len+Service priority) + 2 (DNR Instance Data Len) + 1 (Addr Len)
    // + 8 (IP addresses) + 25 (svc params)
    // = 88
    EXPECT_EQ(88, option->len());

    // BTW let's check if toText() works ok.
    // toText() len does not count in headers len.
    EXPECT_EQ("type=162(V4_DNR), len=86, "
              "DNR Instance 1(Instance len=24, service_priority=1, "
              "adn_length=21, adn='myhost1.example.com.'), "
              "DNR Instance 2(Instance len=58, service_priority=2, "
              "adn_length=21, adn='myhost2.example.com.', "
              "addr_length=8, address(es): 192.168.0.1 192.168.0.2, "
              "svc_params='alpn=h3 port=1234 dohpath=/q{?dns}')",
              option->toText());
}

// This test verifies option packing into wire data.
// Provided data to pack contains 1 DNR instance:
// 1. ADN only mode
TEST(Option4DnrTest, fromConfigCtorPackOneAdnOnlyModeInstance) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com.";

    OptionBuffer in_buf;
    in_buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor doesn't throw.
    Option4DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr(in_buf.begin(), in_buf.end(), true)));
    ASSERT_TRUE(option);

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

// This test verifies option packing into wire data.
// Provided data to pack contains 3 DNR instances:
// 1. ADN only mode
// 2. ADN only mode
// 3. ADN only mode
TEST(Option4DnrTest, fromConfigCtorPackMultipleAdnOnlyModeInstances) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com. | "
                               "3, myhost3.example.com.";

    OptionBuffer in_buf;
    in_buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor doesn't throw.
    Option4DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr(in_buf.begin(), in_buf.end(), true)));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V4, option->getUniverse());
    EXPECT_EQ(DHO_V4_DNR, option->getType());

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
        0x07,       0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '2',   // FQDN: myhost2.
        0x07,       0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03,       0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00,       24,                                        // DNR Instance Data Len
        0x00,       0x03,                                      // Service priority is 3 dec
        21,                                                    // ADN Length is 21 dec
        0x07,       0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '3',   // FQDN: myhost3.
        0x07,       0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03,       0x63, 0x6F, 0x6D, 0x00                     // com.
    };

    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, buf.getData(), buf.getLength()));
}

// This test verifies option packing into wire data.
// Provided data to pack contains 2 DNR instances:
// 1. ADN only mode
// 2. All fields included (IP addresses and service params also).
TEST(Option4DnrTest, fromConfigCtorPackMixedDnrInstances) {
    // Create option instance. Check that constructor doesn't throw.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,doq";
    OptionBuffer opt_buf;
    opt_buf.assign(config.begin(), config.end());
    Option4DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr(opt_buf.begin(), opt_buf.end(), true)));
    ASSERT_TRUE(option);

    // Prepare on-wire format of the option.
    isc::util::OutputBuffer out_buf(10);
    ASSERT_NO_THROW(option->pack(out_buf));

    // Prepare reference data.
    const uint8_t ref_data[] = {
        DHO_V4_DNR,                                      // Option code
        73,                                              // Option len
        0x00, 24,                                        // DNR Instance Data Len
        0x00, 0x01,                                      // Service priority is 1 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00, 45,                                        // DNR Instance Data Len
        0x00, 0x02,                                      // Service priority is 2 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '2',   // FQDN: myhost2.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        8,                                               // Addr Len
        192,  168,  0,    1,                             // IP address 1
        192,  168,  0,    2,                             // IP address 2
        0,    1,                                         // SvcParamKey alpn
        0,    8,                                         // SvcParamVal Len
        3,    'd',  'o',  't',                           // 3 octets long alpn-id dot
        3,    'd',  'o',  'q'                            // 3 octets long alpn-id doq

    };

    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, out_buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, out_buf.getData(), out_buf.getLength()));
}

// This test verifies option packing into wire data.
// Provided data to pack contains 2 DNR instances:
// 1. ADN only mode
// 2. Almost all fields included (IP addresses but no service params).
TEST(Option4DnrTest, fromConfigCtorPackMixedDnrInstancesTwo) {
    // Create option instance. Check that constructor doesn't throw.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2";
    OptionBuffer opt_buf;
    opt_buf.assign(config.begin(), config.end());
    Option4DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr(opt_buf.begin(), opt_buf.end(), true)));
    ASSERT_TRUE(option);

    // Prepare on-wire format of the option.
    isc::util::OutputBuffer out_buf(10);
    ASSERT_NO_THROW(option->pack(out_buf));

    // Prepare reference data.
    const uint8_t ref_data[] = {
        DHO_V4_DNR,                                      // Option code
        61,                                              // Option len
        0x00, 24,                                        // DNR Instance Data Len
        0x00, 0x01,                                      // Service priority is 1 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00, 33,                                        // DNR Instance Data Len
        0x00, 0x02,                                      // Service priority is 2 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '2',   // FQDN: myhost2.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        8,                                               // Addr Len
        192,  168,  0,    1,                             // IP address 1
        192,  168,  0,    2                              // IP address 2
    };

    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, out_buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, out_buf.getData(), out_buf.getLength()));
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - DnrInstance config has only Svc Priority.
TEST(Option4DnrTest, fromConfigCtorNotEnoughFields) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,h3 "
                               "dohpath=/some\\|path{?dns} | " // "pipe char" escape is tested here
                               "3"; // 3rd dnr instance config has only Svc Priority

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 BadValue);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - DnrInstance config has too many comma separated fields.
TEST(Option4DnrTest, fromConfigCtorTooManyFields) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,h3 "
                               "dohpath=/some-path{?dns} | "
                               "3, test.com., 10.2.3.4, port=1234, extra"; // too many fields

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 BadValue);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - DnrInstance config has malformed Svc priority.
TEST(Option4DnrTest, fromConfigCtorWrongSvcPriority) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,h3 "
                               "dohpath=/some-path{?dns} | "
                               "what?, test.com., 10.2.3.4, port=1234"; // non-parsable Svc Priority

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 BadValue);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - DnrInstance config has malformed ADN.
TEST(Option4DnrTest, fromConfigCtorWrongAdn) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,h3 "
                               "dohpath=/some-path{?dns} | "
                               "100, , 10.2.3.4, port=1234"; // wrong ADN - empty

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 InvalidOptionDnrDomainName);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - DnrInstance config has malformed IP address.
TEST(Option4DnrTest, fromConfigCtorWrongIpAddr) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,h3 "
                               "dohpath=/some-path{?dns} | "
                               "100, test.net. , what?, port=1234"; // wrong IP address

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 BadValue);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - DnrInstance config has no IP address.
TEST(Option4DnrTest, fromConfigCtorNoIpAddr) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,h3 "
                               "dohpath=/some-path{?dns} | "
                               "100, test.net. , , port=1234"; // no IP address

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 BadValue);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - DnrInstance config has malformed SvcParams.
TEST(Option4DnrTest, fromConfigCtorWrongSvcParams) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,h3 "
                               "dohpath=/some-path{?dns} | "
                               "100, test.net. , 10.2.3.4, ="; // wrong SvcParams

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - DnrInstance config has malformed SvcParams - forbidden SvcParam.
TEST(Option4DnrTest, fromConfigCtorWrongSvcParamsForbiddenSvcParam) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,h3 "
                               "dohpath=/some-path{?dns} | "
                               "100, test.net. , 10.2.3.4, ipv4hint=1"; // forbidden SvcParam

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - DnrInstance config has malformed SvcParams - unknown SvcParam.
TEST(Option4DnrTest, fromConfigCtorWrongSvcParamsUnknownSvcParam) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,h3 "
                               "dohpath=/some-path{?dns} | "
                               "100, test.net. , 10.2.3.4, unknown=1"; // unknown SvcParam

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - DnrInstance config has malformed SvcParams - not supported SvcParam.
TEST(Option4DnrTest, fromConfigCtorWrongSvcParamsNotSupportedSvcParam) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,h3 "
                               "dohpath=/some-path{?dns} | "
                               "100, test.net. , 10.2.3.4, ech=1"; // ech is not supported in DNR

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - DnrInstance config has malformed SvcParams - duplicated SvcParam.
TEST(Option4DnrTest, fromConfigCtorWrongSvcParamsDuplicatedSvcParam) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,h3 "
                               "dohpath=/some-path{?dns} | "
                               "100, test.net. , 10.2.3.4,"
                               " port=1234 port=2345"; // duplicated SvcParam

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - DnrInstance config has malformed SvcParams - unknown AlpnId.
TEST(Option4DnrTest, fromConfigCtorWrongSvcParamsUnknownAlpnId) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,h3 "
                               "dohpath=/some-path{?dns} | "
                               "100, test.net. , 10.2.3.4, alpn=dot\\,unknown"; // unknown alpn-id

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - DnrInstance config has malformed SvcParams - dohpath is missing.
TEST(Option4DnrTest, fromConfigCtorWrongSvcParamsSkippedDohpath) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,h3 "
                               "dohpath=/some-path{?dns} | "
                               "100, test.net. , 10.2.3.4, alpn=h3"; // dohpath must be there
                                                                     // when any of http alpn-ids
                                                                     // are included

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - DnrInstance config has malformed SvcParams - port can't be parsed.
TEST(Option4DnrTest, fromConfigCtorWrongSvcParamsWrongPort) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,h3 "
                               "dohpath=/some-path{?dns} | "
                               "100, test.net. , 10.2.3.4, port=what?"; // port must be uint_16

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - DnrInstance config has malformed SvcParams - dns var missing in dohpath.
TEST(Option4DnrTest, fromConfigCtorWrongSvcParamsMissingVarInDohpath) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, alpn=dot\\,h3 "
                               "dohpath=/some-path{?dns} | "
                               "100, test.net. , 10.2.3.4, alpn=dot\\,h3 "
                               "dohpath=/some-path"; // dns var is missing in the uri of dohpath

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// This test verifies that option constructor throws
// an exception when config provided via ctor is malformed
// - IPv6 address given.
TEST(Option4DnrTest, fromConfigCtorIPv6Address) {
    // Prepare example config.
    const std::string config = "100, dot1.example.org., 2001:db8::1";

    OptionBuffer buf;
    buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor throws.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end(), true)),
                 BadValue);
    ASSERT_FALSE(option);
}

// This test verifies option packing into wire data.
// Provided data to pack contains 2 DNR instances:
// 1. ADN only mode
// 2. All fields included and SvcParams are given in wrong order.
TEST(Option4DnrTest, fromConfigCtorPackUnorderedSvcParams) {
    // Create option instance. Check that constructor doesn't throw.
    const std::string config = "1, myhost1.example.com. | "
                               "2, myhost2.example.com., 192.168.0.1 192.168.0.2, port=85"
                               " alpn=dot\\,doq"; // SvcParams are NOT in increasing order
    OptionBuffer opt_buf;
    opt_buf.assign(config.begin(), config.end());
    Option4DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr(opt_buf.begin(), opt_buf.end(), true)));
    ASSERT_TRUE(option);

    // Prepare on-wire format of the option.
    isc::util::OutputBuffer out_buf(10);
    ASSERT_NO_THROW(option->pack(out_buf));

    // Prepare reference data.
    const uint8_t ref_data[] = {
        DHO_V4_DNR,                                      // Option code
        79,                                              // Option len
        0x00, 24,                                        // DNR Instance Data Len
        0x00, 0x01,                                      // Service priority is 1 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00, 51,                                        // DNR Instance Data Len
        0x00, 0x02,                                      // Service priority is 2 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '2',   // FQDN: myhost2.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        8,                                               // Addr Len
        192,  168,  0,    1,                             // IP address 1
        192,  168,  0,    2,                             // IP address 2
        0,    1,                                         // SvcParamKey alpn
        0,    8,                                         // SvcParamVal Len
        3,    'd',  'o',  't',                           // 3 octets long alpn-id dot
        3,    'd',  'o',  'q',                           // 3 octets long alpn-id doq
        0,    3,                                         // SvcParamKey port is in correct order
                                                         // after alpn
        0,    2,                                         // SvcParamVal Len
        0,    85                                         // port nr
    };

    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, out_buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, out_buf.getData(), out_buf.getLength()));
}

// This test verifies option constructor from wire data in terms
// of proper data unpacking.
// Provided wire data contains 1 DNR instance:
// 1. ADN only mode
TEST(Option4DnrTest, unpackOneAdnOnly) {
    // Prepare data to decode - ADN only mode 1 DNR instance.
    const uint8_t buf_data[] = {
        0x00, 24,                                        // DNR Instance Data Len
        0x00, 0x01,                                      // Service priority is 1 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00                     // com.
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor doesn't throw.
    Option4DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V4, option->getUniverse());
    EXPECT_EQ(DHO_V4_DNR, option->getType());

    // Check if data was unpacked correctly from wire data.
    EXPECT_EQ(24, option->getDnrInstances()[0].getDnrInstanceDataLength());
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

// This test verifies option constructor from wire data in terms
// of proper data unpacking.
// Provided wire data contains 1 DNR instance:
// 1. All fields included (IP addresses and service params also).
TEST(Option4DnrTest, unpackOneDnrInstance) {
    // Prepare data to decode - 1 DNR instance.
    const uint8_t buf_data[] = {
        0x00, 45,                                        // DNR Instance Data Len
        0x00, 0x01,                                      // Service priority is 1 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        8,                                               // Addr Len
        192,  168,  0,    1,                             // IP address 1
        192,  168,  0,    2,                             // IP address 2
        0,    1,                                         // SvcParamKey alpn
        0,    8,                                         // SvcParamVal Len
        3,    'd',  'o',  't',                           // 3 octets long alpn-id dot
        3,    'd',  'o',  'q'                            // 3 octets long alpn-id doq
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor doesn't throw.
    Option4DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V4, option->getUniverse());
    EXPECT_EQ(DHO_V4_DNR, option->getType());

    // Check if data was unpacked correctly from wire data.
    const DnrInstance& dnr_i = option->getDnrInstances()[0];
    EXPECT_EQ(45, dnr_i.getDnrInstanceDataLength());
    EXPECT_EQ(1, dnr_i.getServicePriority());
    EXPECT_EQ(21, dnr_i.getAdnLength());
    EXPECT_EQ("myhost1.example.com.", dnr_i.getAdnAsText());
    EXPECT_EQ(8, dnr_i.getAddrLength());
    EXPECT_EQ(2, dnr_i.getAddresses().size());
    EXPECT_EQ("192.168.0.1", dnr_i.getAddresses()[0].toText());
    EXPECT_EQ("192.168.0.2", dnr_i.getAddresses()[1].toText());

    // Reference SvcParams on-wire data buffer.
    const OptionBuffer svc_params = {
        0, 1,              // SvcParamKey alpn
        0, 8,              // SvcParamVal Len
        3, 'd', 'o', 't',  // 3 octets long alpn-id dot
        3, 'd', 'o', 'q'   // 3 octets long alpn-id doq
    };

    EXPECT_EQ(svc_params, dnr_i.getSvcParams());
    EXPECT_EQ(svc_params.size(), dnr_i.getSvcParamsLength());
    EXPECT_EQ(49, option->len());
}

// This test verifies option constructor from wire data in terms
// of proper data unpacking.
// Provided wire data contains 2 DNR instances:
// 1. ADN only mode
// 2. All fields included (IP addresses and service params also).
TEST(Option4DnrTest, unpackMixedDnrInstances) {
    // Prepare data to decode - 2 DNR instances.
    const uint8_t buf_data[] = {
        0x00, 24,                                        // DNR Instance Data Len
        0x00, 0x01,                                      // Service priority is 1 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00, 58,                                        // DNR Instance Data Len
        0x00, 0x02,                                      // Service priority is 2 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '2',   // FQDN: myhost2.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        8,                                               // Addr Len
        192,  168,  0,    1,                             // IP address 1
        192,  168,  0,    2,                             // IP address 2
        0,   1,                                  // SvcParamKey alpn
        0,   3,                                  // SvcParamVal Len
        2,   'h',  '3',                          // 2 octets long alpn-id http/3
        0,   3,                                  // SvcParamKey port
        0,   2,                                  // SvcParamVal Len
        0x4, 0xD2,                               // 1234 in hex
        0,   7,                                  // SvcParamKey dohpath
        0,   8,                                  // SvcParamVal Len
        '/', 'q',  '{', '?', 'd', 'n', 's', '}'  // dohpath value
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    // Create option instance. Check that constructor doesn't throw.
    Option4DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end())));
    ASSERT_TRUE(option);

    // Check if member variables were correctly set by ctor.
    EXPECT_EQ(Option::V4, option->getUniverse());
    EXPECT_EQ(DHO_V4_DNR, option->getType());

    // Check if data was unpacked correctly from wire data.
    const DnrInstance& dnr_1 = option->getDnrInstances()[0];
    EXPECT_EQ(24, dnr_1.getDnrInstanceDataLength());
    EXPECT_EQ(1, dnr_1.getServicePriority());
    EXPECT_EQ(21, dnr_1.getAdnLength());
    EXPECT_EQ("myhost1.example.com.", dnr_1.getAdnAsText());
    EXPECT_EQ(0, dnr_1.getAddrLength());
    EXPECT_EQ(0, dnr_1.getSvcParamsLength());

    const DnrInstance& dnr_2 = option->getDnrInstances()[1];
    EXPECT_EQ(58, dnr_2.getDnrInstanceDataLength());
    EXPECT_EQ(2, dnr_2.getServicePriority());
    EXPECT_EQ(21, dnr_2.getAdnLength());
    EXPECT_EQ("myhost2.example.com.", dnr_2.getAdnAsText());
    EXPECT_EQ(8, dnr_2.getAddrLength());
    EXPECT_EQ(2, dnr_2.getAddresses().size());
    EXPECT_EQ("192.168.0.1", dnr_2.getAddresses()[0].toText());
    EXPECT_EQ("192.168.0.2", dnr_2.getAddresses()[1].toText());

    // Reference SvcParams on-wire data buffer.
    const OptionBuffer svc_params = {
        0,   1,                                  // SvcParamKey alpn
        0,   3,                                  // SvcParamVal Len
        2,   'h',  '3',                          // 2 octets long alpn-id http/3
        0,   3,                                  // SvcParamKey port
        0,   2,                                  // SvcParamVal Len
        0x4, 0xD2,                               // 1234 in hex
        0,   7,                                  // SvcParamKey dohpath
        0,   8,                                  // SvcParamVal Len
        '/', 'q',  '{', '?', 'd', 'n', 's', '}'  // dohpath value
    };
    EXPECT_EQ(svc_params, dnr_2.getSvcParams());
    EXPECT_EQ(svc_params.size(), dnr_2.getSvcParamsLength());

    EXPECT_EQ(88, option->len());
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - mandatory fields are truncated - Service Priority and ADN Len truncated.
TEST(Option4DnrTest, unpackTruncatedDnrInstanceDataLen) {
    // Prepare malformed data to decode.
    const uint8_t buf_data[] = {
        0x00, 24,                                        // DNR Instance Data Len
        0x00, 0x01,                                      // Service priority is 1 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00, 62                                         // DNR Instance Data Len truncated
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor throws an exception while doing unpack.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end())), OutOfRange);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - DNR instance data truncated when compared to DNR Instance Data Len field.
TEST(Option4DnrTest, unpackTruncatedDnrInstanceData) {
    // Prepare malformed data to decode.
    const uint8_t buf_data[] = {
        0x00, 24,                                        // DNR Instance Data Len
        0x00, 0x01,                                      // Service priority is 1 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00, 62,                                        // DNR Instance Data Len
        0x00, 0x02,                                      // Service priority is 2 dec
        21                                               // ADN Length is 21 dec
        // the rest of DNR instance data is truncated
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor throws an exception while doing unpack.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end())), OutOfRange);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - ADN field data truncated.
TEST(Option4DnrTest, unpackTruncatedAdn) {
    // Prepare malformed data to decode.
    const uint8_t buf_data[] = {
        0x00, 24,                                        // DNR Instance Data Len
        0x00, 0x01,                                      // Service priority is 1 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00, 3,                                         // DNR Instance Data Len
        0x00, 0x02,                                      // Service priority is 2 dec
        21                                               // ADN Length is 21 dec
        // ADN data is missing.
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor throws an exception while doing unpack.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end())), BadValue);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - ADN FQDN contains only whitespace - non-valid FQDN.
TEST(Option4DnrTest, unpackInvalidFqdnAdn) {
    // Prepare malformed data to decode.
    const uint8_t buf_data[] = {
        0x00, 24,                                        // DNR Instance Data Len
        0x00, 0x01,                                      // Service priority is 1 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00, 4,                                         // DNR Instance Data Len
        0x00, 0x02,                                      // Service priority is 2 dec
        1,                                               // ADN Length is 1 dec
        ' '                                              // ADN contains only whitespace
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor throws an exception while doing unpack.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end())), InvalidOptionDnrDomainName);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - ADN Length is 0 and no ADN FQDN at all.
TEST(Option4DnrTest, unpackNoFqdnAdn) {
    // Prepare malformed data to decode.
    const uint8_t buf_data[] = {
        0x00, 24,                                        // DNR Instance Data Len
        0x00, 0x01,                                      // Service priority is 1 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00, 3,                                         // DNR Instance Data Len
        0x00, 0x02,                                      // Service priority is 2 dec
        0                                                // ADN Length is 0 dec
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor throws an exception while doing unpack.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end())), InvalidOptionDnrDomainName);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - IPv4 address(es) field data truncated.
TEST(Option4DnrTest, unpackTruncatedIpAddress) {
    // Prepare malformed data to decode.
    const uint8_t buf_data[] = {
        0x00, 24,                                        // DNR Instance Data Len
        0x00, 0x01,                                      // Service priority is 1 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00, 25,                                        // DNR Instance Data Len
        0x00, 0x02,                                      // Service priority is 2 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '2',   // FQDN: myhost2.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        8                                                // Addr Len
        // the rest of DNR instance data is truncated.
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor throws an exception while doing unpack.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end())), BadValue);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - Addr length is 0 and no IPv4 addresses at all.
TEST(Option4DnrTest, unpackNoIpAddress) {
    // Prepare malformed data to decode.
    const uint8_t buf_data[] = {
        0x00, 24,                                        // DNR Instance Data Len
        0x00, 0x01,                                      // Service priority is 1 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00, 25,                                        // DNR Instance Data Len
        0x00, 0x02,                                      // Service priority is 2 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '2',   // FQDN: myhost2.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        0                                                // Addr Len = 0
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor throws an exception while doing unpack.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end())), OutOfRange);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - Addr length is not a multiple of 4.
TEST(Option4DnrTest, unpackIpAddressNon4Modulo) {
    // Prepare malformed data to decode.
    const uint8_t buf_data[] = {
        0x00, 24,                                        // DNR Instance Data Len
        0x00, 0x01,                                      // Service priority is 1 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00, 32,                                        // DNR Instance Data Len
        0x00, 0x02,                                      // Service priority is 2 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '2',   // FQDN: myhost2.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        7,                                               // Addr Len
        192,  168,  0,    1,                             // IP address 1
        192,  168,  0                                    // IP address 2 truncated
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor throws an exception while doing unpack.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end())), OutOfRange);
    ASSERT_FALSE(option);
}

// Test checks that exception is thrown when trying to unpack malformed wire data
// - SvcParams contain unknown SvcParamKey.
TEST(Option4DnrTest, unpackvcParamsInvalidCharKey) {
    // Prepare malformed data to decode.
    const uint8_t buf_data[] = {
        0x00, 24,                                        // DNR Instance Data Len
        0x00, 0x01,                                      // Service priority is 1 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '1',   // FQDN: myhost1.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        0x00, 39,                                        // DNR Instance Data Len
        0x00, 0x02,                                      // Service priority is 2 dec
        21,                                              // ADN Length is 21 dec
        0x07, 0x6D, 0x79, 0x68, 0x6F, 0x73, 0x74, '2',   // FQDN: myhost2.
        0x07, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65,  // example.
        0x03, 0x63, 0x6F, 0x6D, 0x00,                    // com.
        8,                                               // Addr Len
        192,  168,  0,    1,                             // IP address 1
        192,  168,  0,    2,                             // IP address 2 truncated
        0,    1,                                         // SvcParamKey alpn
        0,    8,                                         // SvcParamVal Len
        3,    'd',  'o',  't',                           // 3 octets long alpn-id dot
        3,    'd',  'o',  'q',                           // 3 octets long alpn-id doq
        0,    99,                                        // unknown SvcParamKey
        0,    2,                                         // SvcParamVal Len
        1,    2                                          // random data
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    // Create option instance. Check that constructor throws an exception while doing unpack.
    Option4DnrPtr option;
    EXPECT_THROW(option.reset(new Option4Dnr(buf.begin(), buf.end())), InvalidOptionDnrSvcParams);
    ASSERT_FALSE(option);
}

// This test verifies that string representation of the option returned by
// toText method is correctly formatted.
TEST(Option4DnrTest, toText) {
    // Prepare example config.
    const std::string config = "1, myhost1.example.com.";

    OptionBuffer in_buf;
    in_buf.assign(config.begin(), config.end());

    // Create option instance. Check that constructor doesn't throw.
    Option4DnrPtr option;
    EXPECT_NO_THROW(option.reset(new Option4Dnr(in_buf.begin(), in_buf.end(), true)));
    ASSERT_TRUE(option);

    // Let's check if toText() works ok.
    // toText() len does not count in headers len.
    const int indent = 4;
    std::string expected = "    type=162(V4_DNR), len=26, "  // the indentation of 4 spaces
                           "DNR Instance 1(Instance len=24, service_priority=1, "
                           "adn_length=21, adn='myhost1.example.com.')";
    EXPECT_EQ(expected, option->toText(indent));
}

}  // namespace