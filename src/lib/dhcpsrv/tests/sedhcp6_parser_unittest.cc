// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/sedhcp6_parser.h>
#include <cryptolink/crypto_asym.h>
#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::cryptolink;

namespace {

/// @brief Test fixture class for @c SeDhcp6Parser
class SeDhcp6ParserTest : public ::testing::Test {
protected:

    /// @brief Setup for each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void SetUp();

    /// @brief Cleans up after each test.
    ///
    /// Clears the configuration in the @c CfgMgr.
    virtual void TearDown();

};

void
SeDhcp6ParserTest::SetUp() {
    CfgMgr::instance().clear();
}

void
SeDhcp6ParserTest::TearDown() {
    CfgMgr::instance().clear();
}

// This test checks the parser on a basic input
TEST_F(SeDhcp6ParserTest, dhcpv6Universe) {
    std::string config = "{ \"sign-answers\": false }";

    ElementPtr config_element = Element::fromJSON(config);

    SeDhcp6Parser parser("secure-dhcp6", Option::V6);
    EXPECT_NO_THROW(parser.build(config_element));
}

// This test checks the parser requires DHCPv6 context
TEST_F(SeDhcp6ParserTest, dhcpv4Universe) {
    std::string config = "{ \"sign-answers\": false }";

    ElementPtr config_element = Element::fromJSON(config);

    SeDhcp6Parser parser("secure-dhcp6", Option::V4);
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test checks unknown parameters
TEST_F(SeDhcp6ParserTest, unknownParameters) {
    std::string config = "{ \"unknown-boolean\": true }";

    ElementPtr config_element = Element::fromJSON(config);

    SeDhcp6Parser parser("secure-dhcp6", Option::V6);
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);

    config = "{ \"unknown-string\": \"foobar\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);

    config = "{ \"unknown-integer\": 1234 }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test checks the boolean parameters
TEST_F(SeDhcp6ParserTest, booleanParameters) {
    std::string config = "{ \"sign-answers\": false }";

    ElementPtr config_element = Element::fromJSON(config);

    SeDhcp6Parser parser("secure-dhcp6", Option::V6);
    EXPECT_NO_THROW(parser.build(config_element));

    config = "{ \"sign-answers\": \"foo\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), TypeError);

    config = "{ \"timestamp-answers\": true }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_NO_THROW(parser.build(config_element));

    config = "{ \"timestamp-answers\": \"foobar\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), TypeError);

    config = "{ \"check-authorizations\": true }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_NO_THROW(parser.build(config_element));

    config = "{ \"check-authorizations\": \"foobar\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), TypeError);

    config = "{ \"check-signatures\": true }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_NO_THROW(parser.build(config_element));

    config = "{ \"check-signatures\": \"foobar\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), TypeError);

    config = "{ \"check-timestamps\": true }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_NO_THROW(parser.build(config_element));

    config = "{ \"check-timestamps\": \"foobar\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), TypeError);
}

// This test checks string parameters
TEST_F(SeDhcp6ParserTest, stringParameters) {
    std::string config = "{ \"public-key\": \"my-public-key\","
        " \"private-key\": \"my-private-key\" }";

    ElementPtr config_element = Element::fromJSON(config);

    SeDhcp6Parser parser("secure-dhcp6", Option::V6);
    EXPECT_NO_THROW(parser.build(config_element));

    config = "{ \"public-key\": true,"
        " \"private-key\": \"my-private-key\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), TypeError);

    config = "{ \"public-key\": \"my-public-key\","
        " \"private-key\": true }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), TypeError);

    config = "{ \"certificate\": \"foobar\","
        " \"private-key\": \"my-private-key\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_NO_THROW(parser.build(config_element));

    config = "{ \"certificate\": false,"
        " \"private-key\": \"my-private-key\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), TypeError);

    // other string parameters have constrainted values
}

// This test checks algorithm values
TEST_F(SeDhcp6ParserTest, algorithms) {
    std::string config = "{ \"signature-algorithm\": \"RSA\" }";

    ElementPtr config_element = Element::fromJSON(config);

    SeDhcp6Parser parser("secure-dhcp6", Option::V6);
    EXPECT_NO_THROW(parser.build(config_element));

    config = "{ \"signature-algorithm\": \"DSA\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);

    config = "{ \"hash-algorithm\": \"SHA-256\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_NO_THROW(parser.build(config_element));

    config = "{ \"hash-algorithm\": \"SHA-512\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_NO_THROW(parser.build(config_element));

    config = "{ \"hash-algorithm\": \"MD5\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test checks enabled signing of answers
TEST_F(SeDhcp6ParserTest, signing) {
    std::string config = "{ \"sign-answers\": false }";

    ElementPtr config_element = Element::fromJSON(config);

    SeDhcp6Parser parser("secure-dhcp6", Option::V6);
    EXPECT_NO_THROW(parser.build(config_element));

    // Not public key and certificate at the same time
    config = "{ \"public-key\": \"" SEDHCP6_DATA_DIR "/pub.pem\","
        " \"certificate\": \"" SEDHCP6_DATA_DIR "/cert.pem\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);

    // Private key is required when signing is enabled
    config = "{  \"sign-answers\": true,"
        " \"certificate\": \"" SEDHCP6_DATA_DIR "/cert.pem\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);

    // Either public key or certificate are required when signing is enabled
    config = "{  \"sign-answers\": true,"
        " \"private-key\": \"" SEDHCP6_DATA_DIR "/priv.pem\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);

    config = "{  \"sign-answers\": true,"
        " \"public-key\": \"" SEDHCP6_DATA_DIR "/pub.pem\","
        " \"private-key\": \"" SEDHCP6_DATA_DIR "/priv.pem\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_NO_THROW(parser.build(config_element));

    config = "{  \"sign-answers\": true,"
        " \"certificate\": \"" SEDHCP6_DATA_DIR "/cert.pem\","
        " \"private-key\": \"" SEDHCP6_DATA_DIR "/priv.pem\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_NO_THROW(parser.build(config_element));
}

// This test checks the parsing of validation policy syntax
TEST_F(SeDhcp6ParserTest, validationPolicy) {
    std::string config = "{ \"validation-policy\": \"offline\" }";

    ElementPtr config_element = Element::fromJSON(config);

    SeDhcp6Parser parser("secure-dhcp6", Option::V6);
    EXPECT_NO_THROW(parser.build(config_element));

    config = "{ \"validation-policy\": \"online\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_NO_THROW(parser.build(config_element));

    config = "{ \"validation-policy\": \"forever\" }";
    config_element = Element::fromJSON(config);
    parser.clear();
    EXPECT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test checks the parsing of a full config using a public key
TEST_F(SeDhcp6ParserTest, fullWithPublicKey) {
    std::string config = "{ \"sign-answers\": true,"
        " \"private-key\": \"" SEDHCP6_DATA_DIR "/priv.pem\","
        " \"public-key\": \"" SEDHCP6_DATA_DIR "/pub.pem\" }";

    ElementPtr config_element = Element::fromJSON(config);

    SeDhcp6Parser parser("secure-dhcp6", Option::V6);
    ASSERT_NO_THROW(parser.build(config_element));
    ASSERT_NO_THROW(parser.commit());

    CfgSeDhcp6Ptr state = CfgMgr::instance().getStagingCfg()->getCfgSeDhcp6();
    ASSERT_TRUE(state);

    EXPECT_TRUE(state->getSignAnswers());
    EXPECT_FALSE(state->getTimestampAnswers());
    EXPECT_FALSE(state->getCheckSignatures());
    EXPECT_FALSE(state->getCheckAuthorizations());
    EXPECT_FALSE(state->getCheckTimestamps());
    EXPECT_FALSE(state->getOnlineValidation());

    CfgSeDhcp6::AsymPtr priv_key(state->getPrivateKey());
    ASSERT_TRUE(priv_key);
    EXPECT_EQ(priv_key->getAsymAlgorithm(), RSA_);
    EXPECT_EQ(priv_key->getHashAlgorithm(), SHA256);
    EXPECT_EQ(priv_key->getAsymKeyKind(), PRIVATE);

    CfgSeDhcp6::AsymPtr pub_key(state->getCredential());
    ASSERT_TRUE(pub_key);
    EXPECT_EQ(pub_key->getAsymAlgorithm(), RSA_);
    EXPECT_EQ(pub_key->getHashAlgorithm(), SHA256);
    EXPECT_EQ(pub_key->getAsymKeyKind(), PUBLIC);
}

// This test checks a public key config with signing disabled
TEST_F(SeDhcp6ParserTest, fullPubKeyNoSign) {
    std::string config = "{ \"sign-answers\": false,"
        " \"check-signatures\": true,"
        " \"check-authorizations\": true,"
        " \"check-timestamps\": true,"
        " \"private-key\": \"" SEDHCP6_DATA_DIR "/priv.pem\","
        " \"public-key\": \"" SEDHCP6_DATA_DIR "/pub.pem\" }";

    ElementPtr config_element = Element::fromJSON(config);

    SeDhcp6Parser parser("secure-dhcp6", Option::V6);
    ASSERT_NO_THROW(parser.build(config_element));
    ASSERT_NO_THROW(parser.commit());

    CfgSeDhcp6Ptr state = CfgMgr::instance().getStagingCfg()->getCfgSeDhcp6();
    ASSERT_TRUE(state);

    EXPECT_FALSE(state->getSignAnswers());
    EXPECT_FALSE(state->getTimestampAnswers());
    EXPECT_TRUE(state->getCheckSignatures());
    EXPECT_TRUE(state->getCheckAuthorizations());
    EXPECT_TRUE(state->getCheckTimestamps());
    EXPECT_FALSE(state->getOnlineValidation());

    CfgSeDhcp6::AsymPtr priv_key(state->getPrivateKey());
    ASSERT_FALSE(priv_key);

    CfgSeDhcp6::AsymPtr pub_key(state->getCredential());
    ASSERT_FALSE(pub_key);
}

// This test checks a public key config with SHA-512
TEST_F(SeDhcp6ParserTest, fullPubKeySha512) {
    std::string config = "{ \"sign-answers\": true,"
        " \"hash-algorithm\": \"SHA-512\","
        " \"private-key\": \"" SEDHCP6_DATA_DIR "/priv.pem\","
        " \"public-key\": \"" SEDHCP6_DATA_DIR "/pub.pem\" }";

    ElementPtr config_element = Element::fromJSON(config);

    SeDhcp6Parser parser("secure-dhcp6", Option::V6);
    ASSERT_NO_THROW(parser.build(config_element));
    ASSERT_NO_THROW(parser.commit());

    CfgSeDhcp6Ptr state = CfgMgr::instance().getStagingCfg()->getCfgSeDhcp6();
    ASSERT_TRUE(state);

    EXPECT_TRUE(state->getSignAnswers());
    EXPECT_FALSE(state->getTimestampAnswers());
    EXPECT_FALSE(state->getCheckSignatures());
    EXPECT_FALSE(state->getCheckAuthorizations());
    EXPECT_FALSE(state->getCheckTimestamps());
    EXPECT_FALSE(state->getOnlineValidation());

    CfgSeDhcp6::AsymPtr priv_key(state->getPrivateKey());
    ASSERT_TRUE(priv_key);
    EXPECT_EQ(priv_key->getAsymAlgorithm(), RSA_);
    EXPECT_EQ(priv_key->getHashAlgorithm(), SHA512);
    EXPECT_EQ(priv_key->getAsymKeyKind(), PRIVATE);

    CfgSeDhcp6::AsymPtr pub_key(state->getCredential());
    ASSERT_TRUE(pub_key);
    EXPECT_EQ(pub_key->getAsymAlgorithm(), RSA_);
    EXPECT_EQ(pub_key->getHashAlgorithm(), SHA512);
    EXPECT_EQ(pub_key->getAsymKeyKind(), PUBLIC);
}

// This test checks the parsing of a full config using a certificate
TEST_F(SeDhcp6ParserTest, fullWithCertificate) {
    std::string config = "{ \"sign-answers\": true,"
        " \"private-key\": \"" SEDHCP6_DATA_DIR "/priv.pem\","
        " \"certificate\": \"" SEDHCP6_DATA_DIR "/cert.pem\" }";

    ElementPtr config_element = Element::fromJSON(config);

    SeDhcp6Parser parser("secure-dhcp6", Option::V6);
    ASSERT_NO_THROW(parser.build(config_element));
    ASSERT_NO_THROW(parser.commit());

    CfgSeDhcp6Ptr state = CfgMgr::instance().getStagingCfg()->getCfgSeDhcp6();
    ASSERT_TRUE(state);

    EXPECT_TRUE(state->getSignAnswers());
    EXPECT_FALSE(state->getTimestampAnswers());
    EXPECT_FALSE(state->getCheckSignatures());
    EXPECT_FALSE(state->getCheckAuthorizations());
    EXPECT_FALSE(state->getCheckTimestamps());
    EXPECT_FALSE(state->getOnlineValidation());

    CfgSeDhcp6::AsymPtr priv_key(state->getPrivateKey());
    ASSERT_TRUE(priv_key);
    EXPECT_EQ(priv_key->getAsymAlgorithm(), RSA_);
    EXPECT_EQ(priv_key->getHashAlgorithm(), SHA256);
    EXPECT_EQ(priv_key->getAsymKeyKind(), PRIVATE);

    CfgSeDhcp6::AsymPtr cert(state->getCredential());
    ASSERT_TRUE(cert);
    EXPECT_EQ(cert->getAsymAlgorithm(), RSA_);
    EXPECT_EQ(cert->getHashAlgorithm(), SHA256);
    EXPECT_EQ(cert->getAsymKeyKind(), CERT);
}

// This test checks a certificate config with signing disabled
TEST_F(SeDhcp6ParserTest, fullCertNoSign) {
    std::string config = "{ \"sign-answers\": false,"
        " \"check-signatures\": true,"
        " \"check-authorizations\": true,"
        " \"check-timestamps\": true,"
        " \"private-key\": \"" SEDHCP6_DATA_DIR "/priv.pem\","
        " \"certificate\": \"" SEDHCP6_DATA_DIR "/cert.pem\" }";

    ElementPtr config_element = Element::fromJSON(config);

    SeDhcp6Parser parser("secure-dhcp6", Option::V6);
    ASSERT_NO_THROW(parser.build(config_element));
    ASSERT_NO_THROW(parser.commit());

    CfgSeDhcp6Ptr state = CfgMgr::instance().getStagingCfg()->getCfgSeDhcp6();
    ASSERT_TRUE(state);

    EXPECT_FALSE(state->getSignAnswers());
    EXPECT_FALSE(state->getTimestampAnswers());
    EXPECT_TRUE(state->getCheckSignatures());
    EXPECT_TRUE(state->getCheckAuthorizations());
    EXPECT_TRUE(state->getCheckTimestamps());
    EXPECT_FALSE(state->getOnlineValidation());

    CfgSeDhcp6::AsymPtr priv_key(state->getPrivateKey());
    ASSERT_FALSE(priv_key);

    CfgSeDhcp6::AsymPtr cert(state->getCredential());
    ASSERT_FALSE(cert);
}

// This test checks a certificate config with SHA-512
TEST_F(SeDhcp6ParserTest, fullCertSha512) {
    std::string config = "{ \"sign-answers\": true,"
        " \"hash-algorithm\": \"SHA-512\","
        " \"private-key\": \"" SEDHCP6_DATA_DIR "/priv.pem\","
        " \"certificate\": \"" SEDHCP6_DATA_DIR "/cert.pem\" }";

    ElementPtr config_element = Element::fromJSON(config);

    SeDhcp6Parser parser("secure-dhcp6", Option::V6);
    ASSERT_NO_THROW(parser.build(config_element));

    // The hash algorithm in the signatureAlgorithm will mismatch
    EXPECT_THROW(parser.commit(), DhcpConfigError);
}


} // end of anonymous namespace
