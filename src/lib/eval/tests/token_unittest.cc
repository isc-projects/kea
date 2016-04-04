// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <eval/token.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_string.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <arpa/inet.h>

using namespace std;
using namespace isc::dhcp;

namespace {

/// @brief Test fixture for testing Tokens.
///
/// This class provides several convenience objects to be used during testing
/// of the Token family of classes.
class TokenTest : public ::testing::Test {
public:

    /// @brief Initializes Pkt4,Pkt6 and options that can be useful for
    ///        evaluation tests.
    TokenTest() {
        pkt4_.reset(new Pkt4(DHCPDISCOVER, 12345));
        pkt6_.reset(new Pkt6(DHCPV6_SOLICIT, 12345));

        // Add options with easily identifiable strings in them
        option_str4_.reset(new OptionString(Option::V4, 100, "hundred4"));
        option_str6_.reset(new OptionString(Option::V6, 100, "hundred6"));

        pkt4_->addOption(option_str4_);
        pkt6_->addOption(option_str6_);
    }

    /// @brief Inserts RAI option with several suboptions
    ///
    /// The structure inserted is:
    ///  - RAI (option 82)
    ///      - option 1 (containing string "one")
    ///      - option 13 (containing string "thirteen")
    void insertRelay4Option() {

        // RAI (Relay Agent Information) option
        OptionPtr rai(new Option(Option::V4, DHO_DHCP_AGENT_OPTIONS));
        OptionPtr sub1(new OptionString(Option::V4, 1, "one"));
        OptionPtr sub13(new OptionString(Option::V4, 13, "thirteen"));

        rai->addOption(sub1);
        rai->addOption(sub13);
        pkt4_->addOption(rai);
    }

    /// @brief Adds relay encapsulations with some suboptions
    ///
    /// This will add 2 relay encapsulations all will have
    /// msg_type of RELAY_FORW
    /// Relay 0 (closest to server) will have
    /// linkaddr = peeraddr = 0, hop-count = 1
    /// option 100 "hundred.zero", option 101 "hundredone.zero"
    /// Relay 1 (closest to client) will have
    /// linkaddr 1::1= peeraddr = 1::2, hop-count = 0
    /// option 100 "hundred.one", option 102 "hundredtwo.one"
    void addRelay6Encapsulations() {
        // First relay
        Pkt6::RelayInfo relay0;
        relay0.msg_type_ = DHCPV6_RELAY_FORW;
        relay0.hop_count_ = 1;
        relay0.linkaddr_ = isc::asiolink::IOAddress("::");
        relay0.peeraddr_ = isc::asiolink::IOAddress("::");
        OptionPtr optRelay01(new OptionString(Option::V6, 100,
                                              "hundred.zero"));
        OptionPtr optRelay02(new OptionString(Option::V6, 101,
                                              "hundredone.zero"));

        relay0.options_.insert(make_pair(optRelay01->getType(), optRelay01));
        relay0.options_.insert(make_pair(optRelay02->getType(), optRelay02));

        pkt6_->addRelayInfo(relay0);
        // Second relay
        Pkt6::RelayInfo relay1;
        relay1.msg_type_ = DHCPV6_RELAY_FORW;
        relay1.hop_count_ = 0;
        relay1.linkaddr_ = isc::asiolink::IOAddress("1::1");
        relay1.peeraddr_ = isc::asiolink::IOAddress("1::2");
        OptionPtr optRelay11(new OptionString(Option::V6, 100,
                                              "hundred.one"));
        OptionPtr optRelay12(new OptionString(Option::V6, 102,
                                              "hundredtwo.one"));

        relay1.options_.insert(make_pair(optRelay11->getType(), optRelay11));
        relay1.options_.insert(make_pair(optRelay12->getType(), optRelay12));
        pkt6_->addRelayInfo(relay1);
    }

    /// @brief Verify that the relay6 option evaluatiosn work properly
    ///
    /// Given the nesting level and option code extract the option
    /// and compare it to the expected string.
    ///
    /// @param test_level The nesting level
    /// @param test_code The code of the option to extract
    /// @param result_addr The expected result of the address as a string
    void verifyRelay6Option(const uint8_t test_level,
                            const uint16_t test_code,
                       	    const TokenOption::RepresentationType& test_rep,
                            const std::string& result_string) {
        // Create the token
        ASSERT_NO_THROW(t_.reset(new TokenRelay6Option(test_level,
                                                       test_code,
                                                       test_rep)));

        // We should be able to evaluate it
        EXPECT_NO_THROW(t_->evaluate(*pkt6_, values_));

        // We should have one value on the stack
        ASSERT_EQ(1, values_.size());

        // And it should match the expected result
        // Invalid nesting levels result in a 0 length string
        EXPECT_EQ(result_string, values_.top());

        // Then we clear the stack
        clearStack();
    }

    /// @brief Verify that the relay6 field evaluations work properly
    ///
    /// Given the nesting level, the field to extract and the expected
    /// address create a token and evaluate it then compare the addresses
    ///
    /// @param test_level The nesting level
    /// @param test_field The type of the field to extract
    /// @param result_addr The expected result of the address as a string
    void verifyRelay6Eval(const uint8_t test_level,
                          const TokenRelay6::FieldType test_field,
                          const int result_len,
                          const uint8_t result_addr[]) {
        // Create the token
        ASSERT_NO_THROW(t_.reset(new TokenRelay6(test_level, test_field)));

        // We should be able to evaluate it
        EXPECT_NO_THROW(t_->evaluate(*pkt6_, values_));

        // We should have one value on the stack
        ASSERT_EQ(1, values_.size());

        // And it should match the expected result
        // Invalid nesting levels result in a 0 length string
        EXPECT_EQ(result_len, values_.top().size());
        if (result_len != 0) {
            EXPECT_EQ(0, memcmp(result_addr, &values_.top()[0], result_len));
        }

        // Then we clear the stack
        clearStack();
    }

    /// @brief Convenience function. Removes token and values stacks.
    void clearStack() {
        while (!values_.empty()) {
            values_.pop();
        }

        t_.reset();
    }

    TokenPtr t_; ///< Just a convenience pointer

    ValueStack values_; ///< evaluated values will be stored here

    Pkt4Ptr pkt4_; ///< A stub DHCPv4 packet
    Pkt6Ptr pkt6_; ///< A stub DHCPv6 packet

    OptionPtr option_str4_; ///< A string option for DHCPv4
    OptionPtr option_str6_; ///< A string option for DHCPv6


    /// @brief Verify that the substring eval works properly
    ///
    /// This function takes the parameters and sets up the value
    /// stack then executes the eval and checks the results.
    ///
    /// @param test_string The string to operate on
    /// @param test_start The postion to start when getting a substring
    /// @param test_length The length of the substring to get
    /// @param result_string The expected result of the eval
    /// @param should_throw The eval will throw
    void verifySubstringEval(const std::string& test_string,
                             const std::string& test_start,
                             const std::string& test_length,
                             const std::string& result_string,
                             bool should_throw = false) {

        // create the token
        ASSERT_NO_THROW(t_.reset(new TokenSubstring()));

        // push values on stack
        values_.push(test_string);
        values_.push(test_start);
        values_.push(test_length);

        // evaluate the token
        if (should_throw) {
            EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalTypeError);
            ASSERT_EQ(0, values_.size());
        } else {
            EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));

            // verify results
            ASSERT_EQ(1, values_.size());
            EXPECT_EQ(result_string, values_.top());

            // remove result
            values_.pop();
        }
    }

    /// @todo: Add more option types here
};

// This tests the toBool() conversions
TEST_F(TokenTest, toBool) {

    ASSERT_NO_THROW(Token::toBool("true"));
    EXPECT_TRUE(Token::toBool("true"));
    ASSERT_NO_THROW(Token::toBool("false"));
    EXPECT_FALSE(Token::toBool("false"));

    // Token::toBool() is case-sensitive
    EXPECT_THROW(Token::toBool("True"), EvalTypeError);
    EXPECT_THROW(Token::toBool("TRUE"), EvalTypeError);

    // Proposed aliases
    EXPECT_THROW(Token::toBool("1"), EvalTypeError);
    EXPECT_THROW(Token::toBool("0"), EvalTypeError);
    EXPECT_THROW(Token::toBool(""), EvalTypeError);
}

// This simple test checks that a TokenString, representing a constant string,
// can be used in Pkt4 evaluation. (The actual packet is not used)
TEST_F(TokenTest, string4) {

    // Store constant string "foo" in the TokenString object.
    ASSERT_NO_THROW(t_.reset(new TokenString("foo")));

    // Make sure that the token can be evaluated without exceptions.
    ASSERT_NO_THROW(t_->evaluate(*pkt4_, values_));

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("foo", values_.top());
}

// This simple test checks that a TokenString, representing a constant string,
// can be used in Pkt6 evaluation. (The actual packet is not used)
TEST_F(TokenTest, string6) {

    // Store constant string "foo" in the TokenString object.
    ASSERT_NO_THROW(t_.reset(new TokenString("foo")));

    // Make sure that the token can be evaluated without exceptions.
    ASSERT_NO_THROW(t_->evaluate(*pkt6_, values_));

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("foo", values_.top());
}

// This simple test checks that a TokenHexString, representing a constant
// string coded in hexadecimal, can be used in Pkt4 evaluation.
// (The actual packet is not used)
TEST_F(TokenTest, hexstring4) {
    TokenPtr empty;
    TokenPtr bad;
    TokenPtr nodigit;
    TokenPtr baddigit;
    TokenPtr bell;
    TokenPtr foo;
    TokenPtr cookie;

    // Store constant empty hexstring "" ("") in the TokenHexString object.
    ASSERT_NO_THROW(empty.reset(new TokenHexString("")));
    // Store bad encoded hexstring "0abc" ("").
    ASSERT_NO_THROW(bad.reset(new TokenHexString("0abc")));
    // Store hexstring with no digits "0x" ("").
    ASSERT_NO_THROW(nodigit.reset(new TokenHexString("0x")));
    // Store hexstring with a bad hexdigit "0xxabc" ("").
    ASSERT_NO_THROW(baddigit.reset(new TokenHexString("0xxabc")));
    // Store hexstring with an odd number of hexdigits "0x7" ("\a").
    ASSERT_NO_THROW(bell.reset(new TokenHexString("0x7")));
    // Store constant hexstring "0x666f6f" ("foo").
    ASSERT_NO_THROW(foo.reset(new TokenHexString("0x666f6f")));
    // Store constant hexstring "0x63825363" (DHCP_OPTIONS_COOKIE).
    ASSERT_NO_THROW(cookie.reset(new TokenHexString("0x63825363")));

    // Make sure that tokens can be evaluated without exceptions.
    ASSERT_NO_THROW(empty->evaluate(*pkt4_, values_));
    ASSERT_NO_THROW(bad->evaluate(*pkt4_, values_));
    ASSERT_NO_THROW(nodigit->evaluate(*pkt4_, values_));
    ASSERT_NO_THROW(baddigit->evaluate(*pkt4_, values_));
    ASSERT_NO_THROW(bell->evaluate(*pkt4_, values_));
    ASSERT_NO_THROW(foo->evaluate(*pkt4_, values_));
    ASSERT_NO_THROW(cookie->evaluate(*pkt4_, values_));

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(7, values_.size());
    uint32_t expected = htonl(DHCP_OPTIONS_COOKIE);
    EXPECT_EQ(4, values_.top().size());
    EXPECT_EQ(0, memcmp(&expected, &values_.top()[0], 4));
    values_.pop();
    EXPECT_EQ("foo", values_.top());
    values_.pop();
    EXPECT_EQ("\a", values_.top());
    values_.pop();
    EXPECT_EQ("", values_.top());
    values_.pop();
    EXPECT_EQ("", values_.top());
    values_.pop();
    EXPECT_EQ("", values_.top());
    values_.pop();
    EXPECT_EQ("", values_.top());
}

// This simple test checks that a TokenHexString, representing a constant
// string coded in hexadecimal, can be used in Pkt6 evaluation.
// (The actual packet is not used)
TEST_F(TokenTest, hexstring6) {
    TokenPtr empty;
    TokenPtr bad;
    TokenPtr nodigit;
    TokenPtr baddigit;
    TokenPtr bell;
    TokenPtr foo;
    TokenPtr cookie;

    // Store constant empty hexstring "" ("") in the TokenHexString object.
    ASSERT_NO_THROW(empty.reset(new TokenHexString("")));
    // Store bad encoded hexstring "0abc" ("").
    ASSERT_NO_THROW(bad.reset(new TokenHexString("0abc")));
    // Store hexstring with no digits "0x" ("").
    ASSERT_NO_THROW(nodigit.reset(new TokenHexString("0x")));
    // Store hexstring with a bad hexdigit "0xxabc" ("").
    ASSERT_NO_THROW(baddigit.reset(new TokenHexString("0xxabc")));
    // Store hexstring with an odd number of hexdigits "0x7" ("\a").
    ASSERT_NO_THROW(bell.reset(new TokenHexString("0x7")));
    // Store constant hexstring "0x666f6f" ("foo").
    ASSERT_NO_THROW(foo.reset(new TokenHexString("0x666f6f")));
    // Store constant hexstring "0x63825363" (DHCP_OPTIONS_COOKIE).
    ASSERT_NO_THROW(cookie.reset(new TokenHexString("0x63825363")));

    // Make sure that tokens can be evaluated without exceptions.
    ASSERT_NO_THROW(empty->evaluate(*pkt6_, values_));
    ASSERT_NO_THROW(bad->evaluate(*pkt6_, values_));
    ASSERT_NO_THROW(nodigit->evaluate(*pkt6_, values_));
    ASSERT_NO_THROW(baddigit->evaluate(*pkt6_, values_));
    ASSERT_NO_THROW(bell->evaluate(*pkt6_, values_));
    ASSERT_NO_THROW(foo->evaluate(*pkt6_, values_));
    ASSERT_NO_THROW(cookie->evaluate(*pkt6_, values_));

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(7, values_.size());
    uint32_t expected = htonl(DHCP_OPTIONS_COOKIE);
    EXPECT_EQ(4, values_.top().size());
    EXPECT_EQ(0, memcmp(&expected, &values_.top()[0], 4));
    values_.pop();
    EXPECT_EQ("foo", values_.top());
    values_.pop();
    EXPECT_EQ("\a", values_.top());
    values_.pop();
    EXPECT_EQ("", values_.top());
    values_.pop();
    EXPECT_EQ("", values_.top());
    values_.pop();
    EXPECT_EQ("", values_.top());
    values_.pop();
    EXPECT_EQ("", values_.top());
}

// This test checks that a TokenIpAddress, representing an IP address as
// a constant string, can be used in Pkt4/Pkt6 evaluation.
// (The actual packet is not used)
TEST_F(TokenTest, ipaddress) {
    TokenPtr bad4;
    TokenPtr bad6;
    TokenPtr ip4;
    TokenPtr ip6;

    // Bad IP addresses
    ASSERT_NO_THROW(bad4.reset(new TokenIpAddress("10.0.0.0.1")));
    ASSERT_NO_THROW(bad6.reset(new TokenIpAddress(":::")));

    // IP addresses
    ASSERT_NO_THROW(ip4.reset(new TokenIpAddress("10.0.0.1")));
    ASSERT_NO_THROW(ip6.reset(new TokenIpAddress("2001:db8::1")));

    // Make sure that tokens can be evaluated without exceptions.
    ASSERT_NO_THROW(ip4->evaluate(*pkt4_, values_));
    ASSERT_NO_THROW(ip6->evaluate(*pkt6_, values_));
    ASSERT_NO_THROW(bad4->evaluate(*pkt4_, values_));
    ASSERT_NO_THROW(bad6->evaluate(*pkt6_, values_));

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(4, values_.size());

    // Check bad addresses (they pushed '' on the value stack)
    EXPECT_EQ(0, values_.top().size());
    values_.pop();
    EXPECT_EQ(0, values_.top().size());
    values_.pop();

    // Check IPv6 address
    uint8_t expected6[] = { 0x20, 1, 0xd, 0xb8, 0, 0, 0, 0,
                            0, 0, 0, 0, 0, 0, 0, 1 };
    EXPECT_EQ(16, values_.top().size());
    EXPECT_EQ(0, memcmp(expected6, &values_.top()[0], 16));
    values_.pop();

    // Check IPv4 address
    uint8_t expected4[] = { 10, 0, 0, 1 };
    EXPECT_EQ(4, values_.top().size());
    EXPECT_EQ(0, memcmp(expected4, &values_.top()[0], 4));
}

// This test checks if a token representing an option value is able to extract
// the option from an IPv4 packet and properly store the option's value.
TEST_F(TokenTest, optionString4) {
    TokenPtr found;
    TokenPtr not_found;

    // The packets we use have option 100 with a string in them.
    ASSERT_NO_THROW(found.reset(new TokenOption(100, TokenOption::TEXTUAL)));
    ASSERT_NO_THROW(not_found.reset(new TokenOption(101, TokenOption::TEXTUAL)));

    // This should evaluate to the content of the option 100 (i.e. "hundred4")
    ASSERT_NO_THROW(found->evaluate(*pkt4_, values_));

    // This should evaluate to "" as there is no option 101.
    ASSERT_NO_THROW(not_found->evaluate(*pkt4_, values_));

    // There should be 2 values evaluated.
    ASSERT_EQ(2, values_.size());

    // This is a stack, so the pop order is inversed. We should get the empty
    // string first.
    EXPECT_EQ("", values_.top());
    values_.pop();

    // Then the content of the option 100.
    EXPECT_EQ("hundred4", values_.top());
}

// This test checks if a token representing option value is able to extract
// the option from an IPv4 packet and properly store its value in a
// hexadecimal format.
TEST_F(TokenTest, optionHexString4) {
    TokenPtr found;
    TokenPtr not_found;

    // The packets we use have option 100 with a string in them.
    ASSERT_NO_THROW(found.reset(new TokenOption(100, TokenOption::HEXADECIMAL)));
    ASSERT_NO_THROW(not_found.reset(new TokenOption(101, TokenOption::HEXADECIMAL)));

    // This should evaluate to the content of the option 100 (i.e. "hundred4")
    ASSERT_NO_THROW(found->evaluate(*pkt4_, values_));

    // This should evaluate to "" as there is no option 101.
    ASSERT_NO_THROW(not_found->evaluate(*pkt4_, values_));

    // There should be 2 values evaluated.
    ASSERT_EQ(2, values_.size());

    // This is a stack, so the pop order is inversed. We should get the empty
    // string first.
    EXPECT_EQ("", values_.top());
    values_.pop();

    // Then the content of the option 100.
    EXPECT_EQ("hundred4", values_.top());
}

// This test checks if a token representing an option value is able to check
// the existence of the option from an IPv4 packet.
TEST_F(TokenTest, optionExistsString4) {
    TokenPtr found;
    TokenPtr not_found;

    // The packets we use have option 100 with a string in them.
    ASSERT_NO_THROW(found.reset(new TokenOption(100, TokenOption::EXISTS)));
    ASSERT_NO_THROW(not_found.reset(new TokenOption(101, TokenOption::EXISTS)));

    ASSERT_NO_THROW(found->evaluate(*pkt4_, values_));
    ASSERT_NO_THROW(not_found->evaluate(*pkt4_, values_));

    // There should be 2 values evaluated.
    ASSERT_EQ(2, values_.size());

    // This is a stack, so the pop order is inversed.
    EXPECT_EQ("false", values_.top());
    values_.pop();
    EXPECT_EQ("true", values_.top());
}

// This test checks if a token representing an option value is able to extract
// the option from an IPv6 packet and properly store the option's value.
TEST_F(TokenTest, optionString6) {
    TokenPtr found;
    TokenPtr not_found;

    // The packets we use have option 100 with a string in them.
    ASSERT_NO_THROW(found.reset(new TokenOption(100, TokenOption::TEXTUAL)));
    ASSERT_NO_THROW(not_found.reset(new TokenOption(101, TokenOption::TEXTUAL)));

    // This should evaluate to the content of the option 100 (i.e. "hundred6")
    ASSERT_NO_THROW(found->evaluate(*pkt6_, values_));

    // This should evaluate to "" as there is no option 101.
    ASSERT_NO_THROW(not_found->evaluate(*pkt6_, values_));

    // There should be 2 values evaluated.
    ASSERT_EQ(2, values_.size());

    // This is a stack, so the pop order is inversed. We should get the empty
    // string first.
    EXPECT_EQ("", values_.top());
    values_.pop();

    // Then the content of the option 100.
    EXPECT_EQ("hundred6", values_.top());
}

// This test checks if a token representing an option value is able to extract
// the option from an IPv6 packet and properly store its value in hexadecimal
// format.
TEST_F(TokenTest, optionHexString6) {
    TokenPtr found;
    TokenPtr not_found;

    // The packets we use have option 100 with a string in them.
    ASSERT_NO_THROW(found.reset(new TokenOption(100, TokenOption::HEXADECIMAL)));
    ASSERT_NO_THROW(not_found.reset(new TokenOption(101, TokenOption::HEXADECIMAL)));

    // This should evaluate to the content of the option 100 (i.e. "hundred6")
    ASSERT_NO_THROW(found->evaluate(*pkt6_, values_));

    // This should evaluate to "" as there is no option 101.
    ASSERT_NO_THROW(not_found->evaluate(*pkt6_, values_));

    // There should be 2 values evaluated.
    ASSERT_EQ(2, values_.size());

    // This is a stack, so the pop order is inversed. We should get the empty
    // string first.
    EXPECT_EQ("", values_.top());
    values_.pop();

    // Then the content of the option 100.
    EXPECT_EQ("hundred6", values_.top());
}

// This test checks if a token representing an option value is able to check
// the existence of the option from an IPv6 packet.
TEST_F(TokenTest, optionExistsString6) {
    TokenPtr found;
    TokenPtr not_found;

    // The packets we use have option 100 with a string in them.
    ASSERT_NO_THROW(found.reset(new TokenOption(100, TokenOption::EXISTS)));
    ASSERT_NO_THROW(not_found.reset(new TokenOption(101, TokenOption::EXISTS)));

    ASSERT_NO_THROW(found->evaluate(*pkt6_, values_));
    ASSERT_NO_THROW(not_found->evaluate(*pkt6_, values_));

    // There should be 2 values evaluated.
    ASSERT_EQ(2, values_.size());

    // This is a stack, so the pop order is inversed.
    EXPECT_EQ("false", values_.top());
    values_.pop();
    EXPECT_EQ("true", values_.top());
}

// This test checks that the existing relay4 option can be found.
TEST_F(TokenTest, relay4Option) {

    // Insert relay option with sub-options 1 and 13
    insertRelay4Option();

    // Creating the token should be safe.
    ASSERT_NO_THROW(t_.reset(new TokenRelay4Option(13, TokenOption::TEXTUAL)));

    // We should be able to evaluate it.
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));

    // we should have one value on the stack
    ASSERT_EQ(1, values_.size());

    // The option should be found and relay4[13] should evaluate to the
    // content of that sub-option, i.e. "thirteen"
    EXPECT_EQ("thirteen", values_.top());
}

// This test checks that the code properly handles cases when
// there is a RAI option, but there's no requested sub-option.
TEST_F(TokenTest, relay4OptionNoSuboption) {

    // Insert relay option with sub-options 1 and 13
    insertRelay4Option();

    // Creating the token should be safe.
    ASSERT_NO_THROW(t_.reset(new TokenRelay4Option(15, TokenOption::TEXTUAL)));

    // We should be able to evaluate it.
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));

    // we should have one value on the stack
    ASSERT_EQ(1, values_.size());

    // The option should NOT be found (there is no sub-option 15),
    // so the expression should evaluate to ""
    EXPECT_EQ("", values_.top());
}

// This test checks that the code properly handles cases when
// there's no RAI option at all.
TEST_F(TokenTest, relay4OptionNoRai) {

    // We didn't call insertRelay4Option(), so there's no RAI option.

    // Creating the token should be safe.
    ASSERT_NO_THROW(t_.reset(new TokenRelay4Option(13, TokenOption::TEXTUAL)));

    // We should be able to evaluate it.
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));

    // we should have one value on the stack
    ASSERT_EQ(1, values_.size());

    // The option should NOT be found (there is no sub-option 13),
    // so the expression should evaluate to ""
    EXPECT_EQ("", values_.top());
}

// This test checks that only the RAI is searched for the requested
// sub-option.
TEST_F(TokenTest, relay4RAIOnly) {

    // Insert relay option with sub-options 1 and 13
    insertRelay4Option();

    // Add options 13 and 70 to the packet.
    OptionPtr opt13(new OptionString(Option::V4, 13, "THIRTEEN"));
    OptionPtr opt70(new OptionString(Option::V4, 70, "SEVENTY"));
    pkt4_->addOption(opt13);
    pkt4_->addOption(opt70);

    // The situation is as follows:
    // Packet:
    //  - option 13 (containing "THIRTEEN")
    //  - option 82 (rai)
    //      - option 1 (containing "one")
    //      - option 13 (containing "thirteen")

    // Let's try to get option 13. It should get the one from RAI
    ASSERT_NO_THROW(t_.reset(new TokenRelay4Option(13, TokenOption::TEXTUAL)));
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("thirteen", values_.top());

    // Try to get option 1. It should get the one from RAI
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenRelay4Option(1, TokenOption::TEXTUAL)));
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("one", values_.top());

    // Try to get option 70. It should fail, as there's no such
    // sub option in RAI.
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenRelay4Option(70, TokenOption::TEXTUAL)));
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("", values_.top());

    // Try to check option 1. It should return "true"
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenRelay4Option(1, TokenOption::EXISTS)));
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());

    // Try to check option 70. It should return "false"
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenRelay4Option(70, TokenOption::EXISTS)));
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());
}

// This test checks if a token representing an == operator is able to
// compare two values (with incorrectly built stack).
TEST_F(TokenTest, optionEqualInvalid) {

    ASSERT_NO_THROW(t_.reset(new TokenEqual()));

    // CASE 1: There's not enough values on the stack. == is an operator that
    // takes two parameters. There are 0 on the stack.
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    // CASE 2: One value is still not enough.
    values_.push("foo");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);
}

// This test checks if a token representing an == operator is able to
// compare two different values.
TEST_F(TokenTest, optionEqualFalse) {

    ASSERT_NO_THROW(t_.reset(new TokenEqual()));

    values_.push("foo");
    values_.push("bar");
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));

    // After evaluation there should be a single value that represents
    // result of "foo" == "bar" comparision.
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());
}

// This test checks if a token representing an == operator is able to
// compare two identical values.
TEST_F(TokenTest, optionEqualTrue) {

    ASSERT_NO_THROW(t_.reset(new TokenEqual()));

    values_.push("foo");
    values_.push("foo");
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));

    // After evaluation there should be a single value that represents
    // result of "foo" == "foo" comparision.
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());
}

// This test checks if a token representing a not is able to
// negate a boolean value (with incorrectly built stack).
TEST_F(TokenTest, operatorNotInvalid) {

    ASSERT_NO_THROW(t_.reset(new TokenNot()));

    // CASE 1: The stack is empty.
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    // CASE 2: The top value is not a boolean
    values_.push("foo");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalTypeError);
}

// This test checks if a token representing a not operator is able to
// negate a boolean value.
TEST_F(TokenTest, operatorNot) {

    ASSERT_NO_THROW(t_.reset(new TokenNot()));

    values_.push("true");
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));

    // After evaluation there should be the negation of the value.
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());

    // Double negation is identity.
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());
}

// This test checks if a token representing an and is able to
// conjugate two values (with incorrectly built stack).
TEST_F(TokenTest, operatorAndInvalid) {

    ASSERT_NO_THROW(t_.reset(new TokenAnd()));

    // CASE 1: There's not enough values on the stack. and is an operator that
    // takes two parameters. There are 0 on the stack.
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    // CASE 2: One value is still not enough.
    values_.push("foo");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    // CASE 3: The two values must be logical
    values_.push("true");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalTypeError);

    // Swap the 2 values
    values_.push("true");
    values_.push("foo");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalTypeError);
}

// This test checks if a token representing an and operator is able to
// conjugate false with another logical
TEST_F(TokenTest, operatorAndFalse) {

    ASSERT_NO_THROW(t_.reset(new TokenAnd()));

    values_.push("true");
    values_.push("false");
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));

    // After evaluation there should be a single "false" value
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());

    // After true and false, checks false and true
    values_.push("true");
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());

    // And false and false
    values_.push("false");
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());
}

// This test checks if a token representing an and is able to
// conjugate two true values.
TEST_F(TokenTest, operatorAndTrue) {

    ASSERT_NO_THROW(t_.reset(new TokenAnd()));

    values_.push("true");
    values_.push("true");
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));

    // After evaluation there should be a single "true" value
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());
}

// This test checks if a token representing an or is able to
// combinate two values (with incorrectly built stack).
TEST_F(TokenTest, operatorOrInvalid) {

    ASSERT_NO_THROW(t_.reset(new TokenOr()));

    // CASE 1: There's not enough values on the stack. or is an operator that
    // takes two parameters. There are 0 on the stack.
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    // CASE 2: One value is still not enough.
    values_.push("foo");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    // CASE 3: The two values must be logical
    values_.push("true");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalTypeError);

    // Swap the 2 values
    values_.push("true");
    values_.push("foo");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalTypeError);
}

// This test checks if a token representing an or is able to
// conjugate two false values.
TEST_F(TokenTest, operatorOrFalse) {

    ASSERT_NO_THROW(t_.reset(new TokenOr()));

    values_.push("false");
    values_.push("false");
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));

    // After evaluation there should be a single "false" value
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());
}

// This test checks if a token representing an == operator is able to
// conjugate true with another logical
TEST_F(TokenTest, operatorOrTrue) {

    ASSERT_NO_THROW(t_.reset(new TokenOr()));

    values_.push("false");
    values_.push("true");
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));

    // After evaluation there should be a single "true" value
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());

    // After false or true, checks true or false
    values_.push("false");
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());

    // And true or true
    values_.push("true");
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());
}

};

// This test checks if a token representing a substring request
// throws an exception if there aren't enough values on the stack.
// The stack from the top is: length, start, string.
// The actual packet is not used.
TEST_F(TokenTest, substringNotEnoughValues) {
    ASSERT_NO_THROW(t_.reset(new TokenSubstring()));

    // Subsring requires three values on the stack, try
    // with 0, 1 and 2 all should throw an exception
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    values_.push("");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    values_.push("0");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    // Three should work
    values_.push("0");
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));

    // As we had an empty string to start with we should have an empty
    // one after the evaluate
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("", values_.top());
}

// Test getting the whole string in different ways
TEST_F(TokenTest, substringWholeString) {
    // Get the whole string
    verifySubstringEval("foobar", "0", "6", "foobar");

    // Get the whole string with "all"
    verifySubstringEval("foobar", "0", "all", "foobar");

    // Get the whole string with an extra long number
    verifySubstringEval("foobar", "0", "123456", "foobar");

    // Get the whole string counting from the back
    verifySubstringEval("foobar", "-6", "all", "foobar");
}

// Test getting a suffix, in this case the last 3 characters
TEST_F(TokenTest, substringTrailer) {
    verifySubstringEval("foobar", "3", "3", "bar");
    verifySubstringEval("foobar", "3", "all", "bar");
    verifySubstringEval("foobar", "-3", "all", "bar");
    verifySubstringEval("foobar", "-3", "123", "bar");
}

// Test getting the middle of the string in different ways
TEST_F(TokenTest, substringMiddle) {
    verifySubstringEval("foobar", "1", "4", "ooba");
    verifySubstringEval("foobar", "-5", "4", "ooba");
    verifySubstringEval("foobar", "-1", "-4", "ooba");
    verifySubstringEval("foobar", "5", "-4", "ooba");
}

// Test getting the last letter in different ways
TEST_F(TokenTest, substringLastLetter) {
    verifySubstringEval("foobar", "5", "all", "r");
    verifySubstringEval("foobar", "5", "1", "r");
    verifySubstringEval("foobar", "5", "5", "r");
    verifySubstringEval("foobar", "-1", "all", "r");
    verifySubstringEval("foobar", "-1", "1", "r");
    verifySubstringEval("foobar", "-1", "5", "r");
}

// Test we get only what is available if we ask for a longer string
TEST_F(TokenTest, substringLength) {
    // Test off the front
    verifySubstringEval("foobar", "0", "-4", "");
    verifySubstringEval("foobar", "1", "-4", "f");
    verifySubstringEval("foobar", "2", "-4", "fo");
    verifySubstringEval("foobar", "3", "-4", "foo");

    // and the back
    verifySubstringEval("foobar", "3", "4", "bar");
    verifySubstringEval("foobar", "4", "4", "ar");
    verifySubstringEval("foobar", "5", "4", "r");
    verifySubstringEval("foobar", "6", "4", "");
}

// Test that we get nothing if the starting postion is out of the string
TEST_F(TokenTest, substringStartingPosition) {
    // Off the front
    verifySubstringEval("foobar", "-7", "1", "");
    verifySubstringEval("foobar", "-7", "-11", "");
    verifySubstringEval("foobar", "-7", "all", "");

    // and the back
    verifySubstringEval("foobar", "6", "1", "");
    verifySubstringEval("foobar", "6", "-11", "");
    verifySubstringEval("foobar", "6", "all", "");
}

// Check what happens if we use strings that aren't numbers for start or length
// We should return the empty string
TEST_F(TokenTest, substringBadParams) {
    verifySubstringEval("foobar", "0ick", "all", "", true);
    verifySubstringEval("foobar", "ick0", "all", "", true);
    verifySubstringEval("foobar", "ick", "all", "", true);
    verifySubstringEval("foobar", "0", "ick", "", true);
    verifySubstringEval("foobar", "0", "0ick", "", true);
    verifySubstringEval("foobar", "0", "ick0", "", true);
    verifySubstringEval("foobar", "0", "allaboard", "", true);
}

// lastly check that we don't get anything if the string is empty or
// we don't ask for any characters from it.
TEST_F(TokenTest, substringReturnEmpty) {
    verifySubstringEval("", "0", "all", "");
    verifySubstringEval("foobar", "0", "0", "");
}

// Check if we can use the substring and equal tokens together
// We put the result on the stack first then the substring values
// then evaluate the substring which should leave the original
// result on the bottom with the substring result on next.
// Evaulating the equals should produce true for the first
// and false for the second.
// throws an exception if there aren't enough values on the stack.
// The stack from the top is: length, start, string.
// The actual packet is not used.
TEST_F(TokenTest, substringEquals) {
    TokenPtr tequal;

    ASSERT_NO_THROW(t_.reset(new TokenSubstring()));
    ASSERT_NO_THROW(tequal.reset(new TokenEqual()));

    // The final expected value
    values_.push("ooba");

    // The substring values
    // Subsring requires three values on the stack, try
    // with 0, 1 and 2 all should throw an exception
    values_.push("foobar");
    values_.push("1");
    values_.push("4");
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));

    // we should have two values on the stack
    ASSERT_EQ(2, values_.size());

    // next the equals eval
    EXPECT_NO_THROW(tequal->evaluate(*pkt4_, values_));
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());

    // get rid of the result
    values_.pop();

    // and try it again but with a bad final value
    // The final expected value
    values_.push("foob");

    // The substring values
    // Subsring requires three values on the stack, try
    // with 0, 1 and 2 all should throw an exception
    values_.push("foobar");
    values_.push("1");
    values_.push("4");
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));

    // we should have two values on the stack
    ASSERT_EQ(2, values_.size());

    // next the equals eval
    EXPECT_NO_THROW(tequal->evaluate(*pkt4_, values_));
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());

}

// This test checks if a token representing a concat request
// throws an exception if there aren't enough values on the stack.
// The actual packet is not used.
TEST_F(TokenTest, concat) {
    ASSERT_NO_THROW(t_.reset(new TokenConcat()));

    // Concat requires two values on the stack, try
    // with 0 and 1 both should throw an exception
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    values_.push("foo");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    // Two should work
    values_.push("bar");
    EXPECT_NO_THROW(t_->evaluate(*pkt4_, values_));

    // Check the result
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("foobar", values_.top());
}

// This test checks if we can properly extract the link and peer
// address fields from relay encapsulations.  Our packet has
// two relay encapsulations.  We attempt to extract the two
// fields from both of the encapsulations and compare them.
// We also try to extract one of the fields from an encapsulation
// that doesn't exist (level 2), this should result in an empty
// string.
TEST_F(TokenTest, relay6Field) {
    // Values for the address results
    uint8_t zeroaddr[] = { 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0 };
    uint8_t linkaddr[] = { 0, 1, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 1 };
    uint8_t peeraddr[] = { 0, 1, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 2 };

    // We start by adding a set of relay encapsulations to the
    // basic v6 packet.
    addRelay6Encapsulations();

    // Then we work our way through the set of choices
    // Level 0 both link and peer address should be 0::0
    verifyRelay6Eval(0, TokenRelay6::LINKADDR, 16, zeroaddr);
    verifyRelay6Eval(0, TokenRelay6::PEERADDR, 16, zeroaddr);

    // Level 1 link and peer should have different non-zero addresses
    verifyRelay6Eval(1, TokenRelay6::LINKADDR, 16, linkaddr);
    verifyRelay6Eval(1, TokenRelay6::PEERADDR, 16, peeraddr);

    // Level 2 has no encapsulation so the address should be zero length
    verifyRelay6Eval(2, TokenRelay6::LINKADDR, 0, zeroaddr);

    // Lets check that the layout of the address returned by the
    // token matches that of the TokenIpAddress
    TokenPtr trelay;
    TokenPtr taddr;
    TokenPtr tequal;
    ASSERT_NO_THROW(trelay.reset(new TokenRelay6(1, TokenRelay6::LINKADDR)));
    ASSERT_NO_THROW(taddr.reset(new TokenIpAddress("1::1")));
    ASSERT_NO_THROW(tequal.reset(new TokenEqual()));

    EXPECT_NO_THROW(trelay->evaluate(*pkt6_, values_));
    EXPECT_NO_THROW(taddr->evaluate(*pkt6_, values_));
    EXPECT_NO_THROW(tequal->evaluate(*pkt6_, values_));

    // We should have a single value on the stack and it should be "true"
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());

    // be tidy
    clearStack();
}

// This test checks if we can properly extract an option
// from relay encapsulations.  Our packet has two relay
// encapsulations.  Both include a common option with the
// original message (option 100) and both include their
// own option (101 and 102).  We attempt to extract the
// options and compare them to expected values.  We also
// try to extract an option from an encapsulation
// that doesn't exist (level 2), this should result in an empty
// string.
TEST_F(TokenTest, relay6Option) {
    // We start by adding a set of relay encapsulations to the
    // basic v6 packet.
    addRelay6Encapsulations();

    // Then we work our way through the set of choices
    // Level 0 both options it has and the check that
    // the checking for an option it doesn't have results
    // in an empty string.
    verifyRelay6Option(0, 100, TokenOption::TEXTUAL, "hundred.zero");
    verifyRelay6Option(0, 100, TokenOption::EXISTS, "true");
    verifyRelay6Option(0, 101, TokenOption::TEXTUAL, "hundredone.zero");
    verifyRelay6Option(0, 102, TokenOption::TEXTUAL, "");
    verifyRelay6Option(0, 102, TokenOption::EXISTS, "false");

    // Level 1, again both options it has and the one for level 0
    verifyRelay6Option(1, 100, TokenOption::TEXTUAL, "hundred.one");
    verifyRelay6Option(1, 101, TokenOption::TEXTUAL, "");
    verifyRelay6Option(1, 102, TokenOption::TEXTUAL, "hundredtwo.one");

    // Level 2, no encapsulation so no options
    verifyRelay6Option(2, 100, TokenOption::TEXTUAL, "");
}
