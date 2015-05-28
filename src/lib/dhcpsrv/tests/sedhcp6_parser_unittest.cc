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
#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::dhcp;

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

    ParserContextPtr parser_context(new ParserContext(Option::V6));

    SeDhcp6Parser parser("secure-Dhcp6", *parser_context);
    ASSERT_NO_THROW(parser.build(config_element));
}

// This test checks the parser requires DHCPv6 context
TEST_F(SeDhcp6ParserTest, dhcpv4Universe) {
    std::string config = "{ \"sign-answers\": false }";

    ElementPtr config_element = Element::fromJSON(config);

    ParserContextPtr parser_context(new ParserContext(Option::V4));

    SeDhcp6Parser parser("secure-Dhcp6", *parser_context);
    ASSERT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test checks unknown parameters
TEST_F(SeDhcp6ParserTest, unknownParameters) {
    std::string config = "{ \"unknown-boolean\": true }";

    ElementPtr config_element = Element::fromJSON(config);

    ParserContextPtr parser_context(new ParserContext(Option::V6));

    SeDhcp6Parser parser("secure-Dhcp6", *parser_context);
    ASSERT_THROW(parser.build(config_element), DhcpConfigError);

    config = "{ \"unknown-string\": \"foobar\" }";
    ASSERT_THROW(parser.build(config_element), DhcpConfigError);

    config = "{ \"unknown-integer\": 1234 }";
    ASSERT_THROW(parser.build(config_element), DhcpConfigError);
}

// This test checks the boolean parameters
TEST_F(SeDhcp6ParserTest, booleanParameters) {
    std::string config = "{ \"sign-answers\": false }";

    ElementPtr config_element = Element::fromJSON(config);

    ParserContextPtr parser_context(new ParserContext(Option::V6));

    SeDhcp6Parser parser("secure-Dhcp6", *parser_context);
    ASSERT_NO_THROW(parser.build(config_element));

    config = "{ \"sign-answers\": \"foo\" }";
    config_element = Element::fromJSON(config);
    ASSERT_THROW(parser.build(config_element), TypeError);

    config = "{ \"timestamp-answers\": true }";
    config_element = Element::fromJSON(config);
    ASSERT_NO_THROW(parser.build(config_element));

    config = "{ \"timestamp-answers\": \"foobar\" }";
    config_element = Element::fromJSON(config);
    ASSERT_THROW(parser.build(config_element), TypeError);

    config = "{ \"check-authorizations\": true }";
    config_element = Element::fromJSON(config);
    ASSERT_NO_THROW(parser.build(config_element));

    config = "{ \"check-authorizations\": \"foobar\" }";
    config_element = Element::fromJSON(config);
    ASSERT_THROW(parser.build(config_element), TypeError);

    config = "{ \"check-signatures\": true }";
    config_element = Element::fromJSON(config);
    ASSERT_NO_THROW(parser.build(config_element));

    config = "{ \"check-signatures\": \"foobar\" }";
    config_element = Element::fromJSON(config);
    ASSERT_THROW(parser.build(config_element), TypeError);

    config = "{ \"check-timestamps\": true }";
    config_element = Element::fromJSON(config);
    ASSERT_NO_THROW(parser.build(config_element));

    config = "{ \"check-timestamps\": \"foobar\" }";
    config_element = Element::fromJSON(config);
    ASSERT_THROW(parser.build(config_element), TypeError);
}

// This test checks string parameters
TEST_F(SeDhcp6ParserTest, stringParameters) {
    std::string config = "{ \"public-key\": \"foobar\" }";

    ElementPtr config_element = Element::fromJSON(config);

    ParserContextPtr parser_context(new ParserContext(Option::V6));

    SeDhcp6Parser parser("secure-Dhcp6", *parser_context);
    ASSERT_NO_THROW(parser.build(config_element));

    config = "{ \"public-key\": true }";
    config_element = Element::fromJSON(config);
    ASSERT_THROW(parser.build(config_element), TypeError);

    config = "{ \"certificate\": \"foobar\" }";
    config_element = Element::fromJSON(config);
    SeDhcp6Parser parser2("secure-Dhcp6", *parser_context);
    ASSERT_NO_THROW(parser2.build(config_element));

    config = "{ \"certificate\": false }";
    config_element = Element::fromJSON(config);
    ASSERT_THROW(parser2.build(config_element), TypeError);

    // other string parameters have constrainted values
}

// This test checks algorithm values
TEST_F(SeDhcp6ParserTest, algorithms) {
    std::string config = "{ \"signature-algorithm\": \"RSA\" }";

    ElementPtr config_element = Element::fromJSON(config);

    ParserContextPtr parser_context(new ParserContext(Option::V6));

    SeDhcp6Parser parser("secure-Dhcp6", *parser_context);
    ASSERT_NO_THROW(parser.build(config_element));

    config = "{ \"signature-algorithm\": \"DSA\" }";
    config_element = Element::fromJSON(config);
    ASSERT_THROW(parser.build(config_element), DhcpConfigError);

    config = "{ \"hash-algorithm\": \"SHA-256\" }";
    config_element = Element::fromJSON(config);
    ASSERT_NO_THROW(parser.build(config_element));

    config = "{ \"hash-algorithm\": \"SHA-512\" }";
    config_element = Element::fromJSON(config);
    ASSERT_NO_THROW(parser.build(config_element));

    config = "{ \"hash-algorithm\": \"MD5\" }";
    config_element = Element::fromJSON(config);
    ASSERT_THROW(parser.build(config_element), DhcpConfigError);

    // Verify the default
}

// This test checks enabled signing of answers
TEST_F(SeDhcp6ParserTest, signing) {
    std::string config = "{ \"sign-answers\": false }";

    ElementPtr config_element = Element::fromJSON(config);

    ParserContextPtr parser_context(new ParserContext(Option::V6));

    SeDhcp6Parser parser("secure-Dhcp6", *parser_context);
    ASSERT_NO_THROW(parser.build(config_element));

    // Not public key and certificate at the same time
    // Need real files!
    config = "{ \"public-key\": \"my-pub-key\","
        " \"certificate\": \"my-certificate\" }";
    config_element = Element::fromJSON(config);
    ASSERT_THROW(parser.build(config_element), DhcpConfigError);

    // Either public key or certificate when signing is enabled
    config = "{  \"sign-answers\": true }";
    config_element = Element::fromJSON(config);
    SeDhcp6Parser parser2("secure-Dhcp6", *parser_context);
    ASSERT_THROW(parser2.build(config_element), DhcpConfigError);

    config = "{  \"sign-answers\": true,"
        " \"public-key\": \"my-pub-key\" }";
    config_element = Element::fromJSON(config);
    ASSERT_NO_THROW(parser2.build(config_element));

    config = "{  \"sign-answers\": true,"
        " \"certificate\": \"my-certificate\" }";
    config_element = Element::fromJSON(config);
    SeDhcp6Parser parser3("secure-Dhcp6", *parser_context);
    ASSERT_NO_THROW(parser3.build(config_element));
}

// This test checks the parsing of validation policy syntax
TEST_F(SeDhcp6ParserTest, validationPolicy) {
    std::string config = "{ \"validation-policy\": \"offline\" }";

    ElementPtr config_element = Element::fromJSON(config);

    ParserContextPtr parser_context(new ParserContext(Option::V6));

    SeDhcp6Parser parser("secure-Dhcp6", *parser_context);
    ASSERT_NO_THROW(parser.build(config_element));

    config = "{ \"validation-policy\": \"online\" }";
    config_element = Element::fromJSON(config);
    ASSERT_NO_THROW(parser.build(config_element));

    config = "{ \"validation-policy\": \"forever\" }";
    config_element = Element::fromJSON(config);
    ASSERT_THROW(parser.build(config_element), DhcpConfigError);
}

} // end of anonymous namespace
