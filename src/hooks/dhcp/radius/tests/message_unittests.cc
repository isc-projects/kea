// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the attribute,
/// attribute collection and config attribute collection classes.

#include <config.h>

#include <client_attribute.h>
#include <client_message.h>
#include <cryptolink/crypto_hash.h>
#include <testutils/gtest_utils.h>
#include <util/str.h>
#include <attribute_test.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::cryptolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::radius;
using namespace isc::util;
using namespace std;

namespace {

// Verifies that MD5 returns AUTH_VECTOR_LEN (16) octets.
TEST(Md5OutputLength, digest16) {
    boost::scoped_ptr<Hash> md(CryptoLink::getCryptoLink().createHash(MD5));
    ASSERT_EQ(AUTH_VECTOR_LEN, md->getOutputLength());
}

/// @brief Test fixture for testing code of attribute classes.
class MessageTest : public radius::test::AttributeTest {
};

// Verifies Message constructors.
TEST_F(MessageTest, constructors) {
    MsgCode code = PW_ACCESS_REQUEST;
    vector<uint8_t> auth;
    for (uint8_t i = 0; i < AUTH_VECTOR_LEN; ++i) {
        auth.push_back(100 + i);
    }
    string secret = "foobar";
    AttributesPtr attrs(new Attributes());
    ASSERT_TRUE(attrs);
    attrs->add(Attribute::fromString(PW_USER_NAME, "me"));
    attrs->add(Attribute::fromInt(PW_NAS_PORT, 1));
    ASSERT_EQ(2, attrs->size());

    MessagePtr message;
    ASSERT_NO_THROW(message.reset(new Message(code, 1234, auth,
                                              secret, attrs)));
    ASSERT_TRUE(message);

    // Code.
    EXPECT_EQ(PW_ACCESS_REQUEST, message->getCode());
    EXPECT_EQ("Access-Request", msgCodeToText(message->getCode()));
    message->setCode(123);
    EXPECT_EQ(123, message->getCode());
    EXPECT_EQ("Message-Code-123", msgCodeToText(message->getCode()));

    // Identifier.
    ASSERT_NO_THROW(message->randomIdentifier());
    uint8_t id = message->getIdentifier();
    for (size_t round = 0; round < 10; ++round) {
        if (id == 0) {
            ASSERT_NO_THROW(message->randomIdentifier());
            id = message->getIdentifier();
        }
    }
    ASSERT_NE(0, id);
    id ^= 16;
    message->setIdentifier(id);
    EXPECT_EQ(id, message->getIdentifier());

    // Length.
    EXPECT_EQ(1234, message->getLength());
    message->setLength(2345);
    EXPECT_EQ(2345, message->getLength());

    // Authenticator.
    vector<uint8_t> got_auth = message->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0);
    auth[8] = 66;
    EXPECT_THROW(message->setAuth(vector<uint8_t>()), BadValue);
    EXPECT_THROW(message->setAuth(vector<uint8_t>(11)), BadValue);
    EXPECT_NO_THROW(message->setAuth(auth));
    got_auth = message->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0);
    message->zeroAuth();
    got_auth = message->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    for (size_t i = 0; i < AUTH_VECTOR_LEN; ++i) {
        EXPECT_EQ(0, got_auth[i]);
    }
    got_auth = Message::ZERO_AUTH();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    for (size_t i = 0; i < AUTH_VECTOR_LEN; ++i) {
        EXPECT_EQ(0, got_auth[i]);
    }
    bool got_zero = true;
    for (size_t round = 0; round < 5; ++round) {
        message->randomAuth();
        got_auth = message->getAuth();
        ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
        for (size_t i = 0; i < AUTH_VECTOR_LEN; ++i) {
            if (got_auth[i] != 0) {
                got_zero = false;
                break;
            }
        }
        if (!got_zero) {
            break;
        }
    }
    EXPECT_FALSE(got_zero);

    // Secret.
    EXPECT_EQ(secret, message->getSecret());
    EXPECT_THROW(message->setSecret(""), BadValue);
    EXPECT_NO_THROW(message->setSecret("another secret"));
    EXPECT_EQ("another secret", message->getSecret());

    // Attributes.
    AttributesPtr got_attrs = message->getAttributes();
    ASSERT_TRUE(got_attrs);
    EXPECT_TRUE(compare(*got_attrs, *attrs));
    attrs->add(Attribute::fromIpAddr(PW_NAS_IP_ADDRESS,
                                     IOAddress("192.0.2.1")));
    message->setAttributes(attrs);
    got_attrs = message->getAttributes();
    ASSERT_TRUE(got_attrs);
    EXPECT_TRUE(compare(*got_attrs, *attrs));
    message->setAttributes(AttributesPtr());
    got_attrs = message->getAttributes();
    EXPECT_FALSE(got_attrs);

    // Buffer.
    vector<uint8_t> got_buffer = message->getBuffer();
    EXPECT_TRUE(got_buffer.empty());
    vector<uint8_t> buffer;
    for (size_t i = 0; i < 32; ++i) {
        buffer.push_back(111 + i);
    }
    message->setBuffer(buffer);
    got_buffer = message->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);
    message->setBuffer(vector<uint8_t>());
    got_buffer = message->getBuffer();
    EXPECT_TRUE(got_buffer.empty());

    // Second constructor.
    ASSERT_NO_THROW(message.reset(new Message(buffer, auth, secret)));

    // Buffer.
    got_buffer = message->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);

    // Authenticator.
    got_auth = message->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0);

    // Secret.
    EXPECT_EQ(secret, message->getSecret());
}

// Verifies basic (no User-Password) Accept-Request processing.
TEST_F(MessageTest, acceptRequest) {
    MsgCode code = PW_ACCESS_REQUEST;
    uint8_t id = 0x67;
    vector<uint8_t> auth = {
        0x35, 0x6a, 0x48, 0xfd, 0x66, 0x24, 0x6a, 0xe3,
        0x45, 0x43, 0x4b, 0xf7, 0xa4, 0xe5, 0x5a, 0xcf
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, auth.size());
    string secret = "foo";
    AttributesPtr attrs(new Attributes());
    ASSERT_TRUE(attrs);
    attrs->add(Attribute::fromString(PW_USER_NAME, "user"));
    attrs->add(Attribute::fromInt(PW_NAS_PORT, 1));
    attrs->add(Attribute::fromIpAddr(PW_NAS_IP_ADDRESS,
                                     IOAddress("127.0.0.1")));

    // Create message (request).
    MessagePtr request;
    ASSERT_NO_THROW(request.reset(new Message(code, 0, auth, secret, attrs)));
    ASSERT_TRUE(request);
    // Identifier must be set explicitly.
    request->setIdentifier(id);

    // Encode request.
    vector<uint8_t> buffer;
    ASSERT_NO_THROW(buffer = request->encode());

    // Check buffer.
    uint16_t length = request->getLength();
    ASSERT_EQ(length, buffer.size());
    ASSERT_EQ(38, length);
    vector<uint8_t> got_buffer = request->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);

    // Verify buffer.
    vector<uint8_t> expected = {
        0x01,           // Code (Access-Request).
        0x67,           // Identifier (0x67)
        0x00, 0x26,     // Length (38).
        // Authenticator.
        0x35, 0x6a, 0x48, 0xfd, 0x66, 0x24, 0x6a, 0xe3,
        0x45, 0x43, 0x4b, 0xf7, 0xa4, 0xe5, 0x5a, 0xcf,
        // User-Name ("user").
        0x01, 0x06, 0x75, 0x73, 0x65, 0x72,
        // NAS-Port (1).
        0x05, 0x06, 0x00, 0x00, 0x00, 0x01,
        // NAS-IP-Address (127.0.0.1).
        0x04, 0x06, 0x7f, 0x00, 0x00, 0x01
    };
    ASSERT_EQ(38, expected.size());
    EXPECT_TRUE(memcmp(&expected[0], &buffer[0], buffer.size()) == 0)
        << str::dumpAsHex(&buffer[0], 38) << "\n"
        << str::dumpAsHex(&expected[0], 38);

    // Create message (response).
    MessagePtr response;
    ASSERT_NO_THROW(response.reset(new Message(buffer, auth, secret)));
    ASSERT_TRUE(response);

    // Decode response.
    ASSERT_NO_THROW(response->decode());

    // Verify response.
    EXPECT_EQ(code, response->getCode());
    EXPECT_EQ(id, response->getIdentifier());
    EXPECT_EQ(length, response->getLength());
    vector<uint8_t> got_auth = response->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&auth[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    AttributesPtr got_attrs = response->getAttributes();
    ASSERT_TRUE(got_attrs);
    EXPECT_TRUE(compare(*got_attrs, *attrs));
}

// Verifies Access-Accept processing.
TEST_F(MessageTest, accessAccept) {
    MsgCode code = PW_ACCESS_ACCEPT;
    uint8_t id = 0x67;
    vector<uint8_t> auth = {
        0x74, 0x28, 0xcd, 0x4d, 0xa1, 0x32, 0xf5, 0x65,
        0xd5, 0xb2, 0xf1, 0xbc, 0xf1, 0x3e, 0x49, 0x49
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, auth.size());
    string secret = "foo";
    AttributesPtr attrs(new Attributes());
    ASSERT_TRUE(attrs);
    attrs->add(Attribute::fromString(PW_USER_NAME, "user"));

    // Create message (request).
    MessagePtr request;
    ASSERT_NO_THROW(request.reset(new Message(code, 0, auth, secret, attrs)));
    ASSERT_TRUE(request);
    // Identifier must be set explicitly.
    request->setIdentifier(id);

    // Encode request.
    vector<uint8_t> buffer;
    ASSERT_NO_THROW(buffer = request->encode());

    // Check buffer.
    uint16_t length = request->getLength();
    ASSERT_EQ(length, buffer.size());
    ASSERT_EQ(26, length);
    vector<uint8_t> got_buffer = request->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);

    // Verify buffer.
    vector<uint8_t> expected = {
        0x02,           // Code (Access-Accept).
        0x67,           // Identifier (9x67)
        0x00, 0x1a,     // Length (26).
        // Authenticator.
        0x2e, 0x8b, 0xcc, 0xb3, 0x4c, 0x10, 0xea, 0xd7,
        0x57, 0xd5, 0x5a, 0x48, 0x00, 0xd0, 0x7e, 0x2a,
        // User-Name ("user").
        0x01, 0x06, 0x75, 0x73, 0x65, 0x72
    };
    ASSERT_EQ(26, expected.size());
    EXPECT_TRUE(memcmp(&expected[0], &buffer[0], buffer.size()) == 0)
        << str::dumpAsHex(&buffer[0], 26) << "\n"
        << str::dumpAsHex(&expected[0], 26);

    // Create message (response).
    MessagePtr response;
    ASSERT_NO_THROW(response.reset(new Message(buffer, auth, secret)));
    ASSERT_TRUE(response);

    // Decode response.
    ASSERT_NO_THROW(response->decode());

    // Verify response.
    EXPECT_EQ(code, response->getCode());
    EXPECT_EQ(id, response->getIdentifier());
    EXPECT_EQ(length, response->getLength());
    vector<uint8_t> got_auth = response->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&auth[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    vector<uint8_t> digest = {
        0x2e, 0x8b, 0xcc, 0xb3, 0x4c, 0x10, 0xea, 0xd7,
        0x57, 0xd5, 0x5a, 0x48, 0x00, 0xd0, 0x7e, 0x2a
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, digest.size());
    memmove(&got_auth[0], &buffer[4], got_auth.size());
    EXPECT_TRUE(memcmp(&digest[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&digest[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    AttributesPtr got_attrs = response->getAttributes();
    ASSERT_TRUE(got_attrs);
    EXPECT_TRUE(compare(*got_attrs, *attrs));
}

// Verifies Accounting-Request processing.
TEST_F(MessageTest, accountingRequest) {
    MsgCode code = PW_ACCOUNTING_REQUEST;
    uint8_t id = 0x67;
    string secret = "bar";
    AttributesPtr attrs(new Attributes());
    ASSERT_TRUE(attrs);
    attrs->add(Attribute::fromString(PW_USER_NAME, "user"));
    attrs->add(Attribute::fromInt(PW_NAS_PORT, 1));
    attrs->add(Attribute::fromInt(PW_ACCT_DELAY_TIME, 0));
    attrs->add(Attribute::fromIpAddr(PW_NAS_IP_ADDRESS,
                                     IOAddress("127.0.0.1")));

    // Create message (request).
    MessagePtr request;
    ASSERT_NO_THROW(request.reset(new Message(code, 0, Message::ZERO_AUTH(),
                                              secret, attrs)));
    ASSERT_TRUE(request);
    // Identifier must be set explicitly.
    request->setIdentifier(id);

    // Encode request.
    vector<uint8_t> buffer;
    ASSERT_NO_THROW(buffer = request->encode());

    // Check buffer.
    uint16_t length = request->getLength();
    ASSERT_EQ(length, buffer.size());
    ASSERT_EQ(44, length);
    vector<uint8_t> got_buffer = request->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);

    // Verify buffer.
    vector<uint8_t> expected = {
        0x04,           // Code (Accounting-Request).
        0x67,           // Identifier (9x67)
        0x00, 0x2c,     // Length (44).
        // Authenticator.
        0x66, 0x13, 0x3a, 0x40, 0x31, 0x53, 0x61, 0xcd,
        0xf3, 0x29, 0xe2, 0xb5, 0x00, 0x5f, 0x4f, 0x74,
        // User-Name ("user").
        0x01, 0x06, 0x75, 0x73, 0x65, 0x72,
        // NAS-Port (1).
        0x05, 0x06, 0x00, 0x00, 0x00, 0x01,
        // Acct-Delay-Time (0).
        0x29, 0x06, 0x00, 0x00, 0x00, 0x00,
        // NAS-IP-Address (127.0.0.1).
        0x04, 0x06, 0x7f, 0x00, 0x00, 0x01
    };
    ASSERT_EQ(44, expected.size());
    EXPECT_TRUE(memcmp(&expected[0], &buffer[0], buffer.size()) == 0)
        << str::dumpAsHex(&buffer[0], 44) << "\n"
        << str::dumpAsHex(&expected[0], 44);

    // Create message (response).
    MessagePtr response;
    ASSERT_NO_THROW(response.reset(new Message(buffer, Message::ZERO_AUTH(),
                                               secret)));
    ASSERT_TRUE(response);

    // Decode response.
    ASSERT_NO_THROW(response->decode());

    // Verify response.
    EXPECT_EQ(code, response->getCode());
    EXPECT_EQ(id, response->getIdentifier());
    EXPECT_EQ(length, response->getLength());
    vector<uint8_t> auth = {
        0x66, 0x13, 0x3a, 0x40, 0x31, 0x53, 0x61, 0xcd,
        0xf3, 0x29, 0xe2, 0xb5, 0x00, 0x5f, 0x4f, 0x74
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, auth.size());
    vector<uint8_t> got_auth = response->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&auth[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    AttributesPtr got_attrs = response->getAttributes();
    ASSERT_TRUE(got_attrs);
    EXPECT_TRUE(compare(*got_attrs, *attrs));
}

// Verifies Accounting-Response processing.
TEST_F(MessageTest, accountingResponse) {
    MsgCode code = PW_ACCOUNTING_RESPONSE;
    uint8_t id = 0x67;
    vector<uint8_t> auth = {
        0x66, 0x13, 0x3a, 0x40, 0x31, 0x53, 0x61, 0xcd,
        0xf3, 0x29, 0xe2, 0xb5, 0x00, 0x5f, 0x4f, 0x74
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, auth.size());
    string secret = "bar";
    AttributesPtr attrs;

    // Create message (request).
    MessagePtr request;
    ASSERT_NO_THROW(request.reset(new Message(code, 0, auth, secret, attrs)));
    ASSERT_TRUE(request);
    // Identifier must be set explicitly.
    request->setIdentifier(id);

    // Encode request.
    vector<uint8_t> buffer;
    ASSERT_NO_THROW(buffer = request->encode());

    // Check buffer.
    uint16_t length = request->getLength();
    ASSERT_EQ(length, buffer.size());
    ASSERT_EQ(20, length);
    vector<uint8_t> got_buffer = request->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);

    // Verify buffer.
    vector<uint8_t> expected = {
        0x05,           // Code (Accounting-Response).
        0x67,           // Identifier (9x67)
        0x00, 0x14,     // Length (20).
        // Authenticator.
        0x88, 0xc4, 0x21, 0xc3, 0x25, 0xf3, 0xdc, 0x57,
        0x14, 0x01, 0x4c, 0xef, 0x78, 0x03, 0x64, 0xbe
    };
    ASSERT_EQ(20, expected.size());
    EXPECT_TRUE(memcmp(&expected[0], &buffer[0], buffer.size()) == 0)
        << str::dumpAsHex(&buffer[0], 20) << "\n"
        << str::dumpAsHex(&expected[0], 20);

    // Create message (response).
    MessagePtr response;
    ASSERT_NO_THROW(response.reset(new Message(buffer, auth, secret)));
    ASSERT_TRUE(response);

    // Decode response.
    ASSERT_NO_THROW(response->decode());

    // Verify response.
    EXPECT_EQ(code, response->getCode());
    EXPECT_EQ(id, response->getIdentifier());
    EXPECT_EQ(length, response->getLength());
    vector<uint8_t> got_auth = response->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&auth[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    vector<uint8_t> digest = {
        0x88, 0xc4, 0x21, 0xc3, 0x25, 0xf3, 0xdc, 0x57,
        0x14, 0x01, 0x4c, 0xef, 0x78, 0x03, 0x64, 0xbe
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, digest.size());
    memmove(&got_auth[0], &buffer[4], got_auth.size());
    EXPECT_TRUE(memcmp(&digest[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&digest[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    EXPECT_FALSE(response->getAttributes());
}

// Verifies Accept-Request with short User-Password processing.
TEST_F(MessageTest, shortUserPassword) {
    MsgCode code = PW_ACCESS_REQUEST;
    uint8_t id = 0x67;
    vector<uint8_t> auth = {
        0xa5, 0xc2, 0x74, 0x1f, 0xf6, 0xa9, 0xa2, 0x85,
        0x6e, 0xee, 0x10, 0xce, 0xf2, 0x41, 0x9e, 0x3f
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, auth.size());
    string secret = "foo";
    AttributesPtr attrs(new Attributes());
    ASSERT_TRUE(attrs);
    attrs->add(Attribute::fromString(PW_USER_NAME, "user"));
    attrs->add(Attribute::fromString(PW_USER_PASSWORD, "secret password"));
    attrs->add(Attribute::fromInt(PW_NAS_PORT, 1));
    attrs->add(Attribute::fromIpAddr(PW_NAS_IP_ADDRESS,
                                      IOAddress("127.0.0.1")));

    // Create message (request).
    MessagePtr request;
    ASSERT_NO_THROW(request.reset(new Message(code, 0, auth, secret, attrs)));
    ASSERT_TRUE(request);
    // Identifier must be set explicitly.
    request->setIdentifier(id);

    // Encode request.
    vector<uint8_t> buffer;
    ASSERT_NO_THROW(buffer = request->encode());

    // Check buffer.
    uint16_t length = request->getLength();
    ASSERT_EQ(length, buffer.size());
    ASSERT_EQ(56, length);
    vector<uint8_t> got_buffer = request->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);

    // Verify buffer.
    vector<uint8_t> expected = {
        0x01,           // Code (Access-Request).
        0x67,           // Identifier (9x67)
        0x00, 0x38,     // Length (56).
        // Authenticator.
        0xa5, 0xc2, 0x74, 0x1f, 0xf6, 0xa9, 0xa2, 0x85,
        0x6e, 0xee, 0x10, 0xce, 0xf2, 0x41, 0x9e, 0x3f,
        // User-Name ("user").
        0x01, 0x06, 0x75, 0x73, 0x65, 0x72,
        // User-Password (hidden "secret password").
        0x02, 0x12,
        0x9b, 0xde, 0xc1, 0x69, 0x9f, 0xb8, 0xaf, 0xb3,
        0x5b, 0x2b, 0xeb, 0xc7, 0xba, 0xcf, 0x3e, 0x63,
        // NAS-Port (1).
        0x05, 0x06, 0x00, 0x00, 0x00, 0x01,
        // NAS-IP-Address (127.0.0.1).
        0x04, 0x06, 0x7f, 0x00, 0x00, 0x01
    };
    ASSERT_EQ(56, expected.size());
    EXPECT_TRUE(memcmp(&expected[0], &buffer[0], buffer.size()) == 0)
        << str::dumpAsHex(&buffer[0], 56) << "\n"
        << str::dumpAsHex(&expected[0], 56);

    // Create message (response).
    MessagePtr response;
    ASSERT_NO_THROW(response.reset(new Message(buffer, auth, secret)));
    ASSERT_TRUE(response);

    // Decode response.
    ASSERT_NO_THROW(response->decode());

    // Verify response.
    EXPECT_EQ(code, response->getCode());
    EXPECT_EQ(id, response->getIdentifier());
    EXPECT_EQ(length, response->getLength());
    vector<uint8_t> got_auth = response->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&auth[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    AttributesPtr got_attrs = response->getAttributes();
    ASSERT_TRUE(got_attrs);
    EXPECT_TRUE(compare(*got_attrs, *attrs))
        << got_attrs->toText() << "\n" << attrs->toText();
}

// Verifies Accept-Request with long User-Password processing.
TEST_F(MessageTest, longUserPassword) {
    MsgCode code = PW_ACCESS_REQUEST;
    uint8_t id = 0x67;
    vector<uint8_t> auth = {
        0xe0, 0xe9, 0xe8, 0x08, 0x53, 0xa0, 0x7c, 0x9d,
        0x1d, 0x8e, 0x03, 0x19, 0x90, 0x26, 0xc9, 0xfa
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, auth.size());
    string secret = "foo";
    AttributesPtr attrs(new Attributes());
    ASSERT_TRUE(attrs);
    attrs->add(Attribute::fromString(PW_USER_NAME, "user"));
    attrs->add(Attribute::fromString(PW_USER_PASSWORD,
                                     "long secret password"));
    attrs->add(Attribute::fromInt(PW_NAS_PORT, 1));
    attrs->add(Attribute::fromIpAddr(PW_NAS_IP_ADDRESS,
                                      IOAddress("127.0.0.1")));

    // Create message (request).
    MessagePtr request;
    ASSERT_NO_THROW(request.reset(new Message(code, 0, auth, secret, attrs)));
    ASSERT_TRUE(request);
    // Identifier must be set explicitly.
    request->setIdentifier(id);

    // Encode request.
    vector<uint8_t> buffer;
    ASSERT_NO_THROW(buffer = request->encode());

    // Check buffer.
    uint16_t length = request->getLength();
    ASSERT_EQ(length, buffer.size());
    ASSERT_EQ(72, length);
    vector<uint8_t> got_buffer = request->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);

    // Verify buffer.
    vector<uint8_t> expected = {
        0x01,           // Code (Access-Request).
        0x67,           // Identifier (9x67)
        0x00, 0x48,     // Length (72).
        // Authenticator.
        0xe0, 0xe9, 0xe8, 0x08, 0x53, 0xa0, 0x7c, 0x9d,
        0x1d, 0x8e, 0x03, 0x19, 0x90, 0x26, 0xc9, 0xfa,
        // User-Name ("user").
        0x01, 0x06, 0x75, 0x73, 0x65, 0x72,
        // User-Password (hidden "long secret password").
        0x02, 0x22,
        0xeb, 0x9c, 0x6e, 0xdb, 0x4e, 0x16, 0x6b, 0x07,
        0x05, 0xd2, 0x51, 0xd5, 0x75, 0xd4, 0xc7, 0x66,
        0x4b, 0x08, 0x7e, 0x83, 0x78, 0xbf, 0x19, 0xeb,
        0x7c, 0x7e, 0x37, 0xb0, 0xd7, 0xe7, 0xaa, 0x61,
        // NAS-Port (1).
        0x05, 0x06, 0x00, 0x00, 0x00, 0x01,
        // NAS-IP-Address (127.0.0.1).
        0x04, 0x06, 0x7f, 0x00, 0x00, 0x01
    };
    ASSERT_EQ(72, expected.size());
    EXPECT_TRUE(memcmp(&expected[0], &buffer[0], buffer.size()) == 0)
        << str::dumpAsHex(&buffer[0], 72) << "\n"
        << str::dumpAsHex(&expected[0], 72);

    // Create message (response).
    MessagePtr response;
    ASSERT_NO_THROW(response.reset(new Message(buffer, auth, secret)));
    ASSERT_TRUE(response);

    // Decode response.
    ASSERT_NO_THROW(response->decode());

    // Verify response.
    EXPECT_EQ(code, response->getCode());
    EXPECT_EQ(id, response->getIdentifier());
    EXPECT_EQ(length, response->getLength());
    vector<uint8_t> got_auth = response->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&auth[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    AttributesPtr got_attrs = response->getAttributes();
    ASSERT_TRUE(got_attrs);
    EXPECT_TRUE(compare(*got_attrs, *attrs))
        << got_attrs->toText() << "\n" << attrs->toText();
}

// Verifies encode error cases.
TEST_F(MessageTest, badEncode) {
    {
        SCOPED_TRACE("empty secret");
        MessagePtr message(new Message(PW_ACCESS_REJECT, AUTH_HDR_LEN,
                                       Message::ZERO_AUTH(), "",
                                       AttributesPtr()));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->encode(), InvalidOperation, "empty secret");
    }
    {
        SCOPED_TRACE("too large");
        AttributesPtr attrs(new Attributes());
        string msg = "too too too too too too too too too too  too too ";
        msg += "too too too too too too too too too too  too too ";
        msg += "too too too too too too too too too too  too too ";
        msg += "too too too too too too too too too too  too too ";
        msg += "too too too too too too too too too too  too too long!";
        // Hard limit is 253 so be close but lower...
        EXPECT_EQ(250, msg.size());
        AttributePtr rm_attr = Attribute::fromString(PW_REPLY_MESSAGE, msg);
        for (size_t i = 0; i < 17; ++i) {
            attrs->add(rm_attr);
        }
        MessagePtr message(new Message(PW_ACCESS_REJECT, 0,
                                       Message::ZERO_AUTH(), "foobar",
                                       attrs));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->encode(), BadValue,
                         "message becomes too large");
    }
    {
        SCOPED_TRACE("invalid User-Password");
        AttributesPtr attrs(new Attributes());
        // Create the User-Password attribute as an integer attribute.
        attrs->add(Attribute::fromInt(PW_USER_PASSWORD, 666));
        MessagePtr message(new Message(PW_ACCESS_REQUEST, 0,
                                       Message::ZERO_AUTH(), "foobar",
                                       attrs));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->encode(), Unexpected,
                         "can't encode User-Password");
    }
    {
        SCOPED_TRACE("Two Message-Authenticators");
        AttributesPtr attrs(new Attributes());
        // Create a Message-Authenticator.
        vector<uint8_t> zero(AUTH_VECTOR_LEN);
        attrs->add(Attribute::fromBinary(PW_MESSAGE_AUTHENTICATOR, zero));
        attrs->add(Attribute::fromBinary(PW_MESSAGE_AUTHENTICATOR, zero));
        MessagePtr message(new Message(PW_STATUS_SERVER, 0,
                                       Message::ZERO_AUTH(), "foobar",
                                       attrs));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->encode(), BadValue,
                         "2 Message-Authenticator attributes");
    }
    {
        SCOPED_TRACE("invalid Message-Authenticator");
        AttributesPtr attrs(new Attributes());
        // Create the Message-Authenticator attribute as an integer attribute.
        attrs->add(Attribute::fromInt(PW_MESSAGE_AUTHENTICATOR, 666));
        MessagePtr message(new Message(PW_STATUS_SERVER, 0,
                                       Message::ZERO_AUTH(), "foobar",
                                       attrs));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->encode(), BadValue,
                         "bad Message-Authenticator attribute");
    }
    {
        SCOPED_TRACE("short Message-Authenticator");
        AttributesPtr attrs(new Attributes());
        vector<uint8_t> zero(AUTH_VECTOR_LEN - 1);
        attrs->add(Attribute::fromBinary(PW_MESSAGE_AUTHENTICATOR, zero));
        MessagePtr message(new Message(PW_STATUS_SERVER, 0,
                                       Message::ZERO_AUTH(), "foobar",
                                       attrs));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->encode(), BadValue,
                         "bad Message-Authenticator attribute");
    }
}

// Verifies decode error cases.
TEST_F(MessageTest, badDecode) {
    {
        SCOPED_TRACE("empty secret");
        // Create an Access-Reject message.
        vector<uint8_t> buffer = { 0x03, 0x67, 0x00, 0x14 };
        for (size_t i = 0; i < AUTH_VECTOR_LEN; i++) {
            buffer.push_back(100 + i);
        }
        MessagePtr message(new Message(buffer, Message::ZERO_AUTH(), ""));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->decode(), InvalidOperation, "empty secret");
    }
    {
        SCOPED_TRACE("too short");
        // Create an Access-Reject message one octet too short.
        vector<uint8_t> buffer = { 0x03, 0x67, 0x00, 0x14 };
        for (size_t i = 0; i < AUTH_VECTOR_LEN; i++) {
            buffer.push_back(100 + i);
        }
        buffer.resize(AUTH_HDR_LEN - 1);
        MessagePtr message(new Message(buffer, Message::ZERO_AUTH(), "foo"));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->decode(), BadValue,
                         "message is too short 19 < 20");
    }
    {
        SCOPED_TRACE("bad authenticator");
        // Create an Access-Reject message.
        vector<uint8_t> buffer = { 0x03, 0x67, 0x00, 0x14 };
        for (size_t i = 0; i < AUTH_VECTOR_LEN; i++) {
            buffer.push_back(100 + i);
        }
        vector<uint8_t> auth(AUTH_VECTOR_LEN - 1, 66);
        MessagePtr message(new Message(buffer, auth, "foobar"));
        ASSERT_TRUE(message);
        // Must not be an Access-Request or Status-Server!
        ASSERT_NE(PW_ACCESS_REQUEST, message->getCode());
        ASSERT_NE(PW_STATUS_SERVER, message->getCode());
        EXPECT_THROW_MSG(message->decode(), InvalidOperation,
                         "bad authenticator");
    }
    {
        SCOPED_TRACE("truncated message");
        // Create an Access-Reject message with one octet larger length.
        vector<uint8_t> buffer = { 0x03, 0x67, 0x00, 0x15 };
        for (size_t i = 0; i < AUTH_VECTOR_LEN; i++) {
            buffer.push_back(100 + i);
        }
        MessagePtr message(new Message(buffer, Message::ZERO_AUTH(), "foo"));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->decode(), BadValue,
                         "truncated Access-Reject length 21, got 20");
    }
    {
        SCOPED_TRACE("2nd message too short");
        // Create an Access-Reject message one octet too short length.
        vector<uint8_t> buffer = { 0x03, 0x67, 0x00, 0x13 };
        for (size_t i = 0; i < AUTH_VECTOR_LEN; i++) {
            buffer.push_back(100 + i);
        }
        MessagePtr message(new Message(buffer, Message::ZERO_AUTH(), "foo"));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->decode(), BadValue,
                         "too short Access-Reject length 19 < 20");
    }
    {
        SCOPED_TRACE("too large");
        // Create an Access-Reject message with 4096 length.
        vector<uint8_t> buffer = { 0x03, 0x67, 0x10, 00 };
        for (size_t i = 0; i < AUTH_VECTOR_LEN; i++) {
            buffer.push_back(100 + i);
        }
        // Note that the RFC says 4095, not 4096, for the maximum length.
        // And what matters is the length in the header: if the buffer is
        // larger it will be resized down it the length.
        buffer.resize(PW_MAX_MSG_SIZE + 1);
        MessagePtr message(new Message(buffer, Message::ZERO_AUTH(), "foo"));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->decode(), BadValue,
                         "too large Access-Reject length 4096 > 4095");
    }
    {
        SCOPED_TRACE("authentication failed");
        // Copied values from accountingResponse.
        vector<uint8_t> buffer = {
            0x05, 0x67, 0x00, 0x14,
            0x88, 0xc4, 0x21, 0xc3, 0x25, 0xf3, 0xdc, 0x57,
            0x14, 0x01, 0x4c, 0xef, 0x78, 0x03, 0x64, 0xbe
        };
        vector<uint8_t> auth = {
            0x66, 0x13, 0x3a, 0x40, 0x31, 0x53, 0x61, 0xcd,
            0xf3, 0x29, 0xe2, 0xb5, 0x00, 0x5f, 0x4f, 0x74
        };
        // Correct secret is "bar" so change a bit in it.
        string secret = "Bar";
        MessagePtr message(new Message(buffer, auth, secret));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->decode(), BadValue,
                         "authentication for Accounting-Response failed");
        // Verify with the correct secret.
        secret = "bar";
        message.reset(new Message(buffer, auth, secret));
        ASSERT_TRUE(message);
        EXPECT_NO_THROW(message->decode());
    }
    {
        SCOPED_TRACE("trailing extra octet");
        // Easier with Access-Request.
        vector<uint8_t> buffer = { 0x01, 0x67, 0x00, 0x15 };
        for (size_t i = 0; i < AUTH_VECTOR_LEN + 1; i++) {
            buffer.push_back(100 + i);
        }
        ASSERT_EQ(AUTH_HDR_LEN + 1, buffer.size());
        MessagePtr message(new Message(buffer, Message::ZERO_AUTH(), "foo"));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->decode(), BadValue, "trailing octet");
    }
    {
        SCOPED_TRACE("trailing truncated attribute");
        // Easier with Access-Request.
        vector<uint8_t> buffer = { 0x01, 0x67, 0x00, 0x16 };
        for (size_t i = 0; i < AUTH_VECTOR_LEN; i++) {
            buffer.push_back(100 + i);
        }
        buffer.push_back(PW_USER_NAME);
        buffer.push_back(7);
        ASSERT_EQ(AUTH_HDR_LEN + 2, buffer.size());
        MessagePtr message(new Message(buffer, Message::ZERO_AUTH(), "foo"));
        ASSERT_TRUE(message);
        string expected = "trailing truncated User-Name (1): length 7, space 2";
        EXPECT_THROW_MSG(message->decode(), BadValue, expected);
    }
    {
        SCOPED_TRACE("too small attribute length");
        // Easier with Access-Request.
        vector<uint8_t> buffer = { 0x01, 0x67, 0x00, 0x16 };
        for (size_t i = 0; i < AUTH_VECTOR_LEN; i++) {
            buffer.push_back(100 + i);
        }
        buffer.push_back(PW_USER_NAME);
        buffer.push_back(2);
        ASSERT_EQ(AUTH_HDR_LEN + 2, buffer.size());
        MessagePtr message(new Message(buffer, Message::ZERO_AUTH(), "foo"));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->decode(), BadValue,
                         "too small attribute length 2 < 3");
    }
    {
        SCOPED_TRACE("bad User-Password");
        // Create an Access-Request (required) with not padded User-Password.
        vector<uint8_t> buffer = { 0x01, 0x67, 0x00, 0x1a };
        for (size_t i = 0; i < AUTH_VECTOR_LEN; i++) {
            buffer.push_back(100 + i);
        }
        buffer.push_back(PW_USER_PASSWORD);
        buffer.push_back(6);
        buffer.push_back(0x75); // 'u'
        buffer.push_back(0x73); // 's'
        buffer.push_back(0x65); // 'e'
        buffer.push_back(0x72); // 'r'
        ASSERT_EQ(AUTH_HDR_LEN + 6, buffer.size());
        MessagePtr message(new Message(buffer, Message::ZERO_AUTH(), "foo"));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->decode(), Unexpected,
                         "can't decode User-Password");
        // Note that other decodeUserPassword failure cases are not
        // available nor possible in the real world.
    }
    {
        SCOPED_TRACE("Two Message-Authenticators");
        // Easier with Status-Server.
        vector<uint8_t> buffer = { 0x0c, 0x67, 0x00, 0x38 };
        vector<uint8_t> auth;
        for (size_t i = 0; i < AUTH_VECTOR_LEN; i++) {
            buffer.push_back(10 + i);
            auth.push_back(10 + i);
        }
        buffer.push_back(PW_MESSAGE_AUTHENTICATOR);
        buffer.push_back(2 + AUTH_VECTOR_LEN);
        for (size_t i = 0; i < AUTH_VECTOR_LEN; i++) {
            buffer.push_back(20 + i);
        }
        buffer.push_back(PW_MESSAGE_AUTHENTICATOR);
        buffer.push_back(2 + AUTH_VECTOR_LEN);
        for (size_t i = 0; i < AUTH_VECTOR_LEN; i++) {
            buffer.push_back(20 + i);
        }
        ASSERT_EQ(AUTH_HDR_LEN + 2 * (2 + AUTH_VECTOR_LEN), buffer.size());
        MessagePtr message(new Message(buffer, auth, "foo"));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->decode(), BadValue,
                         "2 Message-Authenticator attributes");
    }
    {
        SCOPED_TRACE("too short Message-Authenticator");
        // Easier with Status-Server.
        vector<uint8_t> buffer = { 0x0c, 0x67, 0x00, 0x25 };
        vector<uint8_t> auth;
        for (size_t i = 0; i < AUTH_VECTOR_LEN; i++) {
            buffer.push_back(10 + i);
            auth.push_back(10 + i);
        }
        buffer.push_back(PW_MESSAGE_AUTHENTICATOR);
        buffer.push_back(1 + AUTH_VECTOR_LEN);
        for (size_t i = 0; i < AUTH_VECTOR_LEN - 1; i++) {
            buffer.push_back(20 + i);
        }
        ASSERT_EQ(AUTH_HDR_LEN + 1 + AUTH_VECTOR_LEN, buffer.size());
        MessagePtr message(new Message(buffer, auth, "foo"));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->decode(), BadValue,
                         "can't verify Message-Authenticator");
    }
    {
        SCOPED_TRACE("too long Message-Authenticator");
        // Easier with Status-Server.
        vector<uint8_t> buffer = { 0x0c, 0x67, 0x00, 0x27 };
        vector<uint8_t> auth;
        for (size_t i = 0; i < AUTH_VECTOR_LEN; i++) {
            buffer.push_back(10 + i);
            auth.push_back(10 + i);
        }
        buffer.push_back(PW_MESSAGE_AUTHENTICATOR);
        buffer.push_back(3 + AUTH_VECTOR_LEN);
        for (size_t i = 0; i < AUTH_VECTOR_LEN + 1; i++) {
            buffer.push_back(20 + i);
        }
        ASSERT_EQ(AUTH_HDR_LEN + 3 + AUTH_VECTOR_LEN, buffer.size());
        MessagePtr message(new Message(buffer, auth, "foo"));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->decode(), BadValue,
                         "can't verify Message-Authenticator");
    }
    {
        SCOPED_TRACE("bad Message-Authenticator");
        vector<uint8_t> buffer = {
            0x0c,           // Code (Status-Server).
            0xda,           // Identifier (0xda).
            0x00, 0x26,     // Length (38).
            // Authenticator.
            0x8a, 0x54, 0xf4, 0x68, 0x6f, 0xb3, 0x94, 0xc5,
            0x28, 0x66, 0xe3, 0x02, 0x18, 0x5d, 0x06, 0x23,
            // Message-Authenticator.
            0x50, 0x12,
            0x5a, 0x66, 0x5e, 0x2e, 0x1e, 0x84, 0x11, 0xf3,
            0xe2, 0x43, 0x82, 0x20, 0x97, 0xc8, 0x4f, 0xa3
        };
        ASSERT_EQ(AUTH_HDR_LEN + 2 + AUTH_VECTOR_LEN, buffer.size());
        vector<uint8_t> auth = {
            0x8a, 0x54, 0xf4, 0x68, 0x6f, 0xb3, 0x94, 0xc5,
            0x28, 0x66, 0xe3, 0x02, 0x18, 0x5d, 0x06, 0x23
        };
        ASSERT_EQ(AUTH_VECTOR_LEN, auth.size());
        // Correct password is "xyzzy5461".
        MessagePtr message(new Message(buffer, auth, "foobar"));
        ASSERT_TRUE(message);
        EXPECT_THROW_MSG(message->decode(), BadValue,
                         "bad Message-Authenticator signature");
    }
}

// Verify basic (no Message-Authentivator) Status-Server processing.
TEST_F(MessageTest, basicStatusServer) {
    MsgCode code = PW_STATUS_SERVER;
    uint8_t id = 0xda;
    vector<uint8_t> auth = {
        0x8a, 0x54, 0xf4, 0x68, 0x6f, 0xb3, 0x94, 0xc5,
        0x28, 0x66, 0xe3, 0x02, 0x18, 0x5d, 0x06, 0x23
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, auth.size());
    string secret = "xyzzy5461";
    AttributesPtr attrs(new Attributes());
    ASSERT_TRUE(attrs);

    // Create message.
    MessagePtr request;
    ASSERT_NO_THROW(request.reset(new Message(code, 0, auth, secret, attrs)));
    ASSERT_TRUE(request);
    // Identifier must be set explicitly.
    request->setIdentifier(id);

    // Encode request.
    vector<uint8_t> buffer;
    ASSERT_NO_THROW(buffer = request->encode());

    // Check buffer.
    uint16_t length = request->getLength();
    ASSERT_EQ(20, length);
    vector<uint8_t> got_buffer = request->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);

    // Verify buffer.
    vector<uint8_t> expected = {
        0x0c,           // Code (Status-Server).
        0xda,           // Identifier (0xda).
        0x00, 0x14,     // Length (20).
        // Authenticator.
        0x8a, 0x54, 0xf4, 0x68, 0x6f, 0xb3, 0x94, 0xc5,
        0x28, 0x66, 0xe3, 0x02, 0x18, 0x5d, 0x06, 0x23
    };
    ASSERT_EQ(20, expected.size());
    EXPECT_TRUE(memcmp(&expected[0], &buffer[0], buffer.size()) == 0)
        << str::dumpAsHex(&buffer[0], 20) << "\n"
        << str::dumpAsHex(&expected[0], 20);

    // Create message (response).
    MessagePtr response;
    ASSERT_NO_THROW(response.reset(new Message(buffer, auth, secret)));
    ASSERT_TRUE(response);

    // Decode response.
    ASSERT_NO_THROW(response->decode());

    // Verify response.
    EXPECT_EQ(code, response->getCode());
    EXPECT_EQ(id, response->getIdentifier());
    EXPECT_EQ(length, response->getLength());
    vector<uint8_t> got_auth = response->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&auth[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    AttributesPtr got_attrs = response->getAttributes();
    EXPECT_FALSE(got_attrs);
}

// Verify Status-Server with Message-Authenticator processing.
TEST_F(MessageTest, authStatusServer) {
    MsgCode code = PW_STATUS_SERVER;
    uint8_t id = 0xda;
    vector<uint8_t> auth = {
        0x8a, 0x54, 0xf4, 0x68, 0x6f, 0xb3, 0x94, 0xc5,
        0x28, 0x66, 0xe3, 0x02, 0x18, 0x5d, 0x06, 0x23
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, auth.size());
    string secret = "xyzzy5461";
    AttributesPtr attrs(new Attributes());
    vector<uint8_t> zero(AUTH_VECTOR_LEN);
    attrs->add(Attribute::fromBinary(PW_MESSAGE_AUTHENTICATOR, zero));

    // Create message.
    MessagePtr request;
    ASSERT_NO_THROW(request.reset(new Message(code, 0, auth, secret, attrs)));
    ASSERT_TRUE(request);
    // Identifier must be set explicitly.
    request->setIdentifier(id);

    // Encode request.
    vector<uint8_t> buffer;
    ASSERT_NO_THROW(buffer = request->encode());

    // Check buffer.
    uint16_t length = request->getLength();
    ASSERT_EQ(38, length);
    vector<uint8_t> got_buffer = request->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);

    // Verify buffer.
    vector<uint8_t> expected = {
        0x0c,           // Code (Status-Server).
        0xda,           // Identifier (0xda).
        0x00, 0x26,     // Length (38).
        // Authenticator.
        0x8a, 0x54, 0xf4, 0x68, 0x6f, 0xb3, 0x94, 0xc5,
        0x28, 0x66, 0xe3, 0x02, 0x18, 0x5d, 0x06, 0x23,
        // Message-Authenticator.
        0x50, 0x12,
        0x5a, 0x66, 0x5e, 0x2e, 0x1e, 0x84, 0x11, 0xf3,
        0xe2, 0x43, 0x82, 0x20, 0x97, 0xc8, 0x4f, 0xa3
    };
    ASSERT_EQ(38, expected.size());
    EXPECT_TRUE(memcmp(&expected[0], &buffer[0], buffer.size()) == 0)
        << str::dumpAsHex(&buffer[0], 38) << "\n"
        << str::dumpAsHex(&expected[0], 38);

    // Create message (response).
    MessagePtr response;
    ASSERT_NO_THROW(response.reset(new Message(buffer, auth, secret)));
    ASSERT_TRUE(response);

    // Decode response.
    ASSERT_NO_THROW(response->decode());

    // Verify response.
    EXPECT_EQ(code, response->getCode());
    EXPECT_EQ(id, response->getIdentifier());
    EXPECT_EQ(length, response->getLength());
    vector<uint8_t> got_auth = response->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&auth[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    AttributesPtr got_attrs = response->getAttributes();
    ASSERT_TRUE(got_attrs);
    AttributesPtr exp_attrs(new Attributes());
    ASSERT_TRUE(exp_attrs);
    vector<uint8_t> exp_ma = {
        0x5a, 0x66, 0x5e, 0x2e, 0x1e, 0x84, 0x11, 0xf3,
        0xe2, 0x43, 0x82, 0x20, 0x97, 0xc8, 0x4f, 0xa3
    };
    exp_attrs->add(Attribute::fromBinary(PW_MESSAGE_AUTHENTICATOR, exp_ma));
    EXPECT_TRUE(compare(*got_attrs, *exp_attrs))
        << got_attrs->toText() << "\n" << exp_attrs->toText();
}

// Verify Status-Server with Message-Authenticator processing.
TEST_F(MessageTest, acctStatusServer) {
    MsgCode code = PW_STATUS_SERVER;
    uint8_t id = 0xb3;
    vector<uint8_t> auth = {
        0x92, 0x5f, 0x6b, 0x66, 0xdd, 0x5f, 0xed, 0x57,
        0x1f, 0xcb, 0x1d, 0xb7, 0xad, 0x38, 0x82, 0x60
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, auth.size());
    string secret = "xyzzy5461";
    AttributesPtr attrs(new Attributes());
    vector<uint8_t> zero(AUTH_VECTOR_LEN);
    attrs->add(Attribute::fromBinary(PW_MESSAGE_AUTHENTICATOR, zero));

    // Create message.
    MessagePtr request;
    ASSERT_NO_THROW(request.reset(new Message(code, 0, auth, secret, attrs)));
    ASSERT_TRUE(request);
    // Identifier must be set explicitly.
    request->setIdentifier(id);

    // Encode request.
    vector<uint8_t> buffer;
    ASSERT_NO_THROW(buffer = request->encode());

    // Check buffer.
    uint16_t length = request->getLength();
    ASSERT_EQ(38, length);
    vector<uint8_t> got_buffer = request->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);

    // Verify buffer.
    vector<uint8_t> expected = {
        0x0c,           // Code (Status-Server).
        0xb3,           // Identifier (0xb3).
        0x00, 0x26,     // Length (38).
        // Authenticator.
        0x92, 0x5f, 0x6b, 0x66, 0xdd, 0x5f, 0xed, 0x57,
        0x1f, 0xcb, 0x1d, 0xb7, 0xad, 0x38, 0x82, 0x60,
        // Message-Authenticator.
        0x50, 0x12,
        0xe8, 0xd6, 0xea, 0xbd, 0xa9, 0x10, 0x87, 0x5c,
        0xd9, 0x1f, 0xda, 0xde, 0x26, 0x36, 0x78, 0x58
    };
    ASSERT_EQ(38, expected.size());
    EXPECT_TRUE(memcmp(&expected[0], &buffer[0], buffer.size()) == 0)
        << str::dumpAsHex(&buffer[0], 38) << "\n"
        << str::dumpAsHex(&expected[0], 38);

    // Create message (response).
    MessagePtr response;
    ASSERT_NO_THROW(response.reset(new Message(buffer, auth, secret)));
    ASSERT_TRUE(response);

    // Decode response.
    ASSERT_NO_THROW(response->decode());

    // Verify response.
    EXPECT_EQ(code, response->getCode());
    EXPECT_EQ(id, response->getIdentifier());
    EXPECT_EQ(length, response->getLength());
    vector<uint8_t> got_auth = response->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&auth[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    AttributesPtr got_attrs = response->getAttributes();
    ASSERT_TRUE(got_attrs);
    AttributesPtr exp_attrs(new Attributes());
    ASSERT_TRUE(exp_attrs);
    vector<uint8_t> exp_ma = {
        0xe8, 0xd6, 0xea, 0xbd, 0xa9, 0x10, 0x87, 0x5c,
        0xd9, 0x1f, 0xda, 0xde, 0x26, 0x36, 0x78, 0x58
    };
    exp_attrs->add(Attribute::fromBinary(PW_MESSAGE_AUTHENTICATOR, exp_ma));
    EXPECT_TRUE(compare(*got_attrs, *exp_attrs))
        << got_attrs->toText() << "\n" << exp_attrs->toText();
}

// Verify verbose Status-Server processing.
TEST_F(MessageTest, verboseStatusServer) {
    MsgCode code = PW_STATUS_SERVER;
    uint8_t id = 0x47;
    vector<uint8_t> auth = {
        0xbf, 0x58, 0xde, 0x56, 0xae, 0x40, 0x8a, 0xd3,
        0xb7, 0x0c, 0x85, 0x13, 0xf9, 0xb0, 0x3f, 0xbe
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, auth.size());
    string secret = "xyzzy5461";
    AttributesPtr attrs(new Attributes());
    IOAddress addr("192.0.2.16");
    attrs->add(Attribute::fromIpAddr(PW_NAS_IP_ADDRESS, addr));
    vector<uint8_t> zero(AUTH_VECTOR_LEN);
    attrs->add(Attribute::fromBinary(PW_MESSAGE_AUTHENTICATOR, zero));

    // Create message.
    MessagePtr request;
    ASSERT_NO_THROW(request.reset(new Message(code, 0, auth, secret, attrs)));
    ASSERT_TRUE(request);
    // Identifier must be set explicitly.
    request->setIdentifier(id);

    // Encode request.
    vector<uint8_t> buffer;
    ASSERT_NO_THROW(buffer = request->encode());

    // Check buffer.
    uint16_t length = request->getLength();
    ASSERT_EQ(44, length);
    vector<uint8_t> got_buffer = request->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);

    // Verify buffer.
    vector<uint8_t> expected = {
        0x0c,           // Code (Status-Server).
        0x47,           // Identifier (0x47).
        0x00, 0x2c,     // Length (44).
        // Authenticator.
        0xbf, 0x58, 0xde, 0x56, 0xae, 0x40, 0x8a, 0xd3,
        0xb7, 0x0c, 0x85, 0x13, 0xf9, 0xb0, 0x3f, 0xbe,
        // NAS-IP-Address.
        0x04, 0x06, 0xc0, 0x00, 0x02, 0x10,
        // Message-Authenticator.
        0x50, 0x12,
        0x85, 0x2d, 0x6f, 0xec, 0x61, 0xe7, 0xed, 0x74,
        0xb8, 0xe3, 0x2d, 0xac, 0x2f, 0x2a, 0x5f, 0xb2
    };
    ASSERT_EQ(44, expected.size());
    EXPECT_TRUE(memcmp(&expected[0], &buffer[0], buffer.size()) == 0)
        << str::dumpAsHex(&buffer[0], 44) << "\n"
        << str::dumpAsHex(&expected[0], 44);

    // Create message (response).
    MessagePtr response;
    ASSERT_NO_THROW(response.reset(new Message(buffer, auth, secret)));
    ASSERT_TRUE(response);

    // Decode response.
    ASSERT_NO_THROW(response->decode());

    // Verify response.
    EXPECT_EQ(code, response->getCode());
    EXPECT_EQ(id, response->getIdentifier());
    EXPECT_EQ(length, response->getLength());
    vector<uint8_t> got_auth = response->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&auth[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    AttributesPtr got_attrs = response->getAttributes();
    ASSERT_TRUE(got_attrs);
    AttributesPtr exp_attrs(new Attributes());
    ASSERT_TRUE(exp_attrs);
    vector<uint8_t> exp_ma = {
        0x85, 0x2d, 0x6f, 0xec, 0x61, 0xe7, 0xed, 0x74,
        0xb8, 0xe3, 0x2d, 0xac, 0x2f, 0x2a, 0x5f, 0xb2
    };
    exp_attrs->add(Attribute::fromIpAddr(PW_NAS_IP_ADDRESS, addr));
    exp_attrs->add(Attribute::fromBinary(PW_MESSAGE_AUTHENTICATOR, exp_ma));
    EXPECT_TRUE(compare(*got_attrs, *exp_attrs))
        << got_attrs->toText() << "\n" << exp_attrs->toText();
}

// Verify Access-Accept response to Status-Server.
TEST_F(MessageTest, basicStatusResponse) {
    MsgCode code = PW_ACCESS_ACCEPT;
    uint8_t id = 0xda;
    vector<uint8_t> auth = {
        0x8a, 0x54, 0xf4, 0x68, 0x6f, 0xb3, 0x94, 0xc5,
        0x28, 0x66, 0xe3, 0x02, 0x18, 0x5d, 0x06, 0x23
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, auth.size());
    string secret = "xyzzy5461";
    AttributesPtr attrs(new Attributes());
    ASSERT_TRUE(attrs);

    // Create message.
    MessagePtr request;
    ASSERT_NO_THROW(request.reset(new Message(code, 0, auth, secret, attrs)));
    ASSERT_TRUE(request);
    // Identifier must be set explicitly.
    request->setIdentifier(id);

    // Encode request.
    vector<uint8_t> buffer;
    ASSERT_NO_THROW(buffer = request->encode());

    // Check buffer.
    uint16_t length = request->getLength();
    ASSERT_EQ(20, length);
    vector<uint8_t> got_buffer = request->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);

    // Verify buffer.
    vector<uint8_t> expected = {
        0x02,           // Code (Access-Accept).
        0xda,           // Identifier (0xda).
        0x00, 0x14,     // Length (20).
        // Authenticator.
        0xef, 0x0d, 0x55, 0x2a, 0x4b, 0xf2, 0xd6, 0x93,
        0xec, 0x2b, 0x6f, 0xe8, 0xb5, 0x41, 0x1d, 0x66
    };
    ASSERT_EQ(20, expected.size());
    EXPECT_TRUE(memcmp(&expected[0], &buffer[0], buffer.size()) == 0)
        << str::dumpAsHex(&buffer[0], 20) << "\n"
        << str::dumpAsHex(&expected[0], 20);

    // Create message (response).
    MessagePtr response;
    ASSERT_NO_THROW(response.reset(new Message(buffer, auth, secret)));
    ASSERT_TRUE(response);

    // Decode response.
    ASSERT_NO_THROW(response->decode());

    // Verify response.
    EXPECT_EQ(code, response->getCode());
    EXPECT_EQ(id, response->getIdentifier());
    EXPECT_EQ(length, response->getLength());
    vector<uint8_t> got_auth = response->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&auth[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    vector<uint8_t> digest = {
        0xef, 0x0d, 0x55, 0x2a, 0x4b, 0xf2, 0xd6, 0x93,
        0xec, 0x2b, 0x6f, 0xe8, 0xb5, 0x41, 0x1d, 0x66
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, digest.size());
    memmove(&got_auth[0], &buffer[4], got_auth.size());
    EXPECT_TRUE(memcmp(&digest[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&digest[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    AttributesPtr got_attrs = response->getAttributes();
    EXPECT_FALSE(got_attrs);
}

// Verify Access-Accept response to Status-Server with Message-Authenticator.
TEST_F(MessageTest, authStatusResponse) {
    MsgCode code = PW_ACCESS_ACCEPT;
    uint8_t id = 0xda;
    vector<uint8_t> auth = {
        0x8a, 0x54, 0xf4, 0x68, 0x6f, 0xb3, 0x94, 0xc5,
        0x28, 0x66, 0xe3, 0x02, 0x18, 0x5d, 0x06, 0x23
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, auth.size());
    string secret = "xyzzy5461";
    AttributesPtr attrs(new Attributes());
    ASSERT_TRUE(attrs);
    vector<uint8_t> zero(AUTH_VECTOR_LEN);
    attrs->add(Attribute::fromBinary(PW_MESSAGE_AUTHENTICATOR, zero));

    // Create message.
    MessagePtr request;
    ASSERT_NO_THROW(request.reset(new Message(code, 0, auth, secret, attrs)));
    ASSERT_TRUE(request);
    // Identifier must be set explicitly.
    request->setIdentifier(id);

    // Encode request.
    vector<uint8_t> buffer;
    ASSERT_NO_THROW(buffer = request->encode());

    // Check buffer.
    uint16_t length = request->getLength();
    ASSERT_EQ(38, length);
    vector<uint8_t> got_buffer = request->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);

    // Verify buffer.
    vector<uint8_t> expected = {
        0x02,           // Code (Access-Accept).
        0xda,           // Identifier (0xda).
        0x00, 0x26,     // Length (38).
        // Authenticator.
        0x7e, 0x6d, 0x7a, 0x5f, 0x5d, 0xfa, 0x87, 0xb5,
        0x19, 0xbe, 0xf2, 0x60, 0xa6, 0xf1, 0x50, 0x81,
        // Message-Authenticator.
        0x50, 0x12,
        0x57, 0x56, 0x6a, 0x4a, 0x4a, 0x4c, 0x69, 0x0f,
        0x8e, 0x18, 0xb7, 0x3a, 0xe7, 0xa7, 0xf6, 0x5f
    };
    ASSERT_EQ(38, expected.size());
    EXPECT_TRUE(memcmp(&expected[0], &buffer[0], buffer.size()) == 0)
        << str::dumpAsHex(&buffer[0], 38) << "\n"
        << str::dumpAsHex(&expected[0], 38);

    // Create message (response).
    MessagePtr response;
    ASSERT_NO_THROW(response.reset(new Message(buffer, auth, secret)));
    ASSERT_TRUE(response);

    // Decode response.
    ASSERT_NO_THROW(response->decode());

    // Verify response.
    EXPECT_EQ(code, response->getCode());
    EXPECT_EQ(id, response->getIdentifier());
    EXPECT_EQ(length, response->getLength());
    vector<uint8_t> got_auth = response->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&auth[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    vector<uint8_t> digest = {
        0x7e, 0x6d, 0x7a, 0x5f, 0x5d, 0xfa, 0x87, 0xb5,
        0x19, 0xbe, 0xf2, 0x60, 0xa6, 0xf1, 0x50, 0x81
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, digest.size());
    memmove(&got_auth[0], &buffer[4], got_auth.size());
    EXPECT_TRUE(memcmp(&digest[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&digest[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    AttributesPtr got_attrs = response->getAttributes();
    ASSERT_TRUE(got_attrs);
    AttributesPtr exp_attrs(new Attributes());
    ASSERT_TRUE(exp_attrs);
    vector<uint8_t> exp_ma = {
        0x57, 0x56, 0x6a, 0x4a, 0x4a, 0x4c, 0x69, 0x0f,
        0x8e, 0x18, 0xb7, 0x3a, 0xe7, 0xa7, 0xf6, 0x5f
    };
    exp_attrs->add(Attribute::fromBinary(PW_MESSAGE_AUTHENTICATOR, exp_ma));
    EXPECT_TRUE(compare(*got_attrs, *exp_attrs))
        << got_attrs->toText() << "\n" << exp_attrs->toText();
}

// Verify Accounting-Response response to Status-Server.
TEST_F(MessageTest, acctStatusResponse) {
    MsgCode code = PW_ACCOUNTING_RESPONSE;
    uint8_t id = 0xb3;
    vector<uint8_t> auth = {
        0x92, 0x5f, 0x6b, 0x66, 0xdd, 0x5f, 0xed, 0x57,
        0x1f, 0xcb, 0x1d, 0xb7, 0xad, 0x38, 0x82, 0x60
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, auth.size());
    string secret = "xyzzy5461";
    AttributesPtr attrs(new Attributes());
    ASSERT_TRUE(attrs);

    // Create message.
    MessagePtr request;
    ASSERT_NO_THROW(request.reset(new Message(code, 0, auth, secret, attrs)));
    ASSERT_TRUE(request);
    // Identifier must be set explicitly.
    request->setIdentifier(id);

    // Encode request.
    vector<uint8_t> buffer;
    ASSERT_NO_THROW(buffer = request->encode());

    // Check buffer.
    uint16_t length = request->getLength();
    ASSERT_EQ(20, length);
    vector<uint8_t> got_buffer = request->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);

    // Verify buffer.
    vector<uint8_t> expected = {
        0x05,           // Code (Accounting-Response).
        0xb3,           // Identifier (0xv=b3).
        0x00, 0x14,     // Length (20).
        // Authenticator.
        0x0f, 0x6f, 0x92, 0x14, 0x5f, 0x10, 0x7e, 0x2f,
        0x50, 0x4e, 0x86, 0x0a, 0x48, 0x60, 0x66, 0x9c
    };
    ASSERT_EQ(20, expected.size());
    EXPECT_TRUE(memcmp(&expected[0], &buffer[0], buffer.size()) == 0)
        << str::dumpAsHex(&buffer[0], 20) << "\n"
        << str::dumpAsHex(&expected[0], 20);

    // Create message (response).
    MessagePtr response;
    ASSERT_NO_THROW(response.reset(new Message(buffer, auth, secret)));
    ASSERT_TRUE(response);

    // Decode response.
    ASSERT_NO_THROW(response->decode());

    // Verify response.
    EXPECT_EQ(code, response->getCode());
    EXPECT_EQ(id, response->getIdentifier());
    EXPECT_EQ(length, response->getLength());
    vector<uint8_t> got_auth = response->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&auth[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    vector<uint8_t> digest = {
        0x0f, 0x6f, 0x92, 0x14, 0x5f, 0x10, 0x7e, 0x2f,
        0x50, 0x4e, 0x86, 0x0a, 0x48, 0x60, 0x66, 0x9c
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, digest.size());
    memmove(&got_auth[0], &buffer[4], got_auth.size());
    EXPECT_TRUE(memcmp(&digest[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&digest[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    AttributesPtr got_attrs = response->getAttributes();
    EXPECT_FALSE(got_attrs);
}

// Verify verbose Access-Accept response to Status-Server.
TEST_F(MessageTest, verboseStatusResponse) {
    MsgCode code = PW_ACCESS_ACCEPT;
    uint8_t id = 0x47;
    vector<uint8_t> auth = {
        0xbf, 0x58, 0xde, 0x56, 0xae, 0x40, 0x8a, 0xd3,
        0xb7, 0x0c, 0x85, 0x13, 0xf9, 0xb0, 0x3f, 0xbe
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, auth.size());
    string secret = "xyzzy5461";
    AttributesPtr attrs(new Attributes());
    ASSERT_TRUE(attrs);
    string msg = "RADIUS Server up 2 days, 18:40";
    attrs->add(Attribute::fromString(PW_REPLY_MESSAGE, msg));

    // Create message.
    MessagePtr request;
    ASSERT_NO_THROW(request.reset(new Message(code, 0, auth, secret, attrs)));
    ASSERT_TRUE(request);
    // Identifier must be set explicitly.
    request->setIdentifier(id);

    // Encode request.
    vector<uint8_t> buffer;
    ASSERT_NO_THROW(buffer = request->encode());

    // Check buffer.
    uint16_t length = request->getLength();
    ASSERT_EQ(52, length);
    vector<uint8_t> got_buffer = request->getBuffer();
    ASSERT_EQ(buffer.size(), got_buffer.size());
    EXPECT_TRUE(memcmp(&buffer[0], &got_buffer[0], buffer.size()) == 0);

    // Verify buffer.
    vector<uint8_t> expected = {
        0x02,           // Code (Access-Accept).
        0x47,           // Identifier (0x47).
        0x00, 0x34,     // Length (52).
        // Authenticator.
        0x46, 0xf4, 0x3e, 0x62, 0xfd, 0x03, 0x54, 0x42,
        0x4c, 0xbb, 0xeb, 0xfd, 0x6d, 0x21, 0x4e, 0x06,
        // Reply-Message.
        0x12, 0x20,
        0x52, 0x41, 0x44, 0x49, 0x55, 0x53, 0x20, 0x53,
        0x65, 0x72, 0x76, 0x65, 0x72, 0x20, 0x75, 0x70,
        0x20, 0x32, 0x20, 0x64, 0x61, 0x79, 0x73, 0x2c,
        0x20, 0x31, 0x38, 0x3a, 0x34, 0x30
    };
    ASSERT_EQ(52, expected.size());
    EXPECT_TRUE(memcmp(&expected[0], &buffer[0], buffer.size()) == 0)
        << str::dumpAsHex(&buffer[0], 52) << "\n"
        << str::dumpAsHex(&expected[0], 52);

    // Create message (response).
    MessagePtr response;
    ASSERT_NO_THROW(response.reset(new Message(buffer, auth, secret)));
    ASSERT_TRUE(response);

    // Decode response.
    ASSERT_NO_THROW(response->decode());

    // Verify response.
    EXPECT_EQ(code, response->getCode());
    EXPECT_EQ(id, response->getIdentifier());
    EXPECT_EQ(length, response->getLength());
    vector<uint8_t> got_auth = response->getAuth();
    ASSERT_EQ(AUTH_VECTOR_LEN, got_auth.size());
    EXPECT_TRUE(memcmp(&auth[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&auth[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    vector<uint8_t> digest = {
        0x46, 0xf4, 0x3e, 0x62, 0xfd, 0x03, 0x54, 0x42,
        0x4c, 0xbb, 0xeb, 0xfd, 0x6d, 0x21, 0x4e, 0x06
    };
    ASSERT_EQ(AUTH_VECTOR_LEN, digest.size());
    memmove(&got_auth[0], &buffer[4], got_auth.size());
    EXPECT_TRUE(memcmp(&digest[0], &got_auth[0], AUTH_VECTOR_LEN) == 0)
        << str::dumpAsHex(&digest[0], AUTH_VECTOR_LEN) << "\n"
        << str::dumpAsHex(&got_auth[0], AUTH_VECTOR_LEN);
    AttributesPtr got_attrs = response->getAttributes();
    ASSERT_TRUE(got_attrs);
    AttributesPtr exp_attrs(new Attributes());
    ASSERT_TRUE(exp_attrs);
    exp_attrs->add(Attribute::fromString(PW_REPLY_MESSAGE, msg));
    EXPECT_TRUE(compare(*got_attrs, *exp_attrs))
        << got_attrs->toText() << "\n" << exp_attrs->toText();
}

} // end of anonymous namespace
