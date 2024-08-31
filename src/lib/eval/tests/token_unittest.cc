// Copyright (C) 2015-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <fstream>
#include <eval/token.h>
#include <eval/eval_context.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option_vendor_class.h>
#include <log/logger_manager.h>
#include <log/logger_name.h>
#include <log/logger_support.h>
#include <testutils/log_utils.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <arpa/inet.h>

using namespace std;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::log;
using namespace isc::dhcp::test;

namespace {

/// @brief Test fixture for testing Tokens.
///
/// This class provides several convenience objects to be used during testing
/// of the Token family of classes.

class TokenTest : public LogContentTest {
public:

    /// @brief Initializes Pkt4, Pkt6 and options that can be useful for
    ///        evaluation tests.
    TokenTest() {
        pkt4_.reset(new Pkt4(DHCPDISCOVER, 12345));
        pkt6_.reset(new Pkt6(DHCPV6_SOLICIT, 12345));

        // Add options with easily identifiable strings in them
        option_str4_.reset(new OptionString(Option::V4, 100, "hundred4"));
        option_str6_.reset(new OptionString(Option::V6, 100, "hundred6"));

        pkt4_->addOption(option_str4_);
        pkt6_->addOption(option_str6_);

        // Change this to true if you need extra information about logging
        // checks to be printed.
        logCheckVerbose(false);
    }

    /// @brief Test evaluation.
    ///
    /// Check that evaluation does not fail and returns 0.
    ///
    /// @param token the pointer to the token to evaluate
    /// @param pkt the packet (*pkt4_ or *pkt6_)
    /// @param values the stack of values (values_)
    void testEvaluate(const TokenPtr& token, Pkt& pkt, ValueStack& values) {
        unsigned next(123);
        ASSERT_NO_THROW(next = token->evaluate(pkt, values));
        EXPECT_EQ(0, next);
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

    /// @brief Verify that the relay6 option evaluations work properly
    ///
    /// Given the nesting level and option code extract the option
    /// and compare it to the expected string.
    ///
    /// @param test_level The nesting level
    /// @param test_code The code of the option to extract
    /// @param result_addr The expected result of the address as a string
    void verifyRelay6Option(const int8_t test_level,
                            const uint16_t test_code,
                            const TokenOption::RepresentationType& test_rep,
                            const std::string& result_string) {
        // Create the token
        ASSERT_NO_THROW(t_.reset(new TokenRelay6Option(test_level,
                                                       test_code,
                                                       test_rep)));

        // We should be able to evaluate it
        testEvaluate(t_, *pkt6_, values_);

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
    void verifyRelay6Eval(const int8_t test_level,
                          const TokenRelay6Field::FieldType test_field,
                          const int result_len,
                          const uint8_t result_addr[]) {
        // Create the token
        ASSERT_NO_THROW(t_.reset(new TokenRelay6Field(test_level, test_field)));

        // We should be able to evaluate it
        testEvaluate(t_, *pkt6_, values_);

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
    /// @param token specifies if the convenience token should be removed or not
    void clearStack(bool token = true) {
        while (!values_.empty()) {
            values_.pop();
        }
        if (token) {
            t_.reset();
        }
    }

    /// @brief Aux. function that stores integer values as 4 byte string.
    ///
    /// @param value integer value to be stored
    /// @return 4 byte long string with encoded value.
    string encode(uint32_t value) {
        return EvalContext::fromUint32(value);
    }

    TokenPtr t_; ///< Just a convenience pointer

    ValueStack values_; ///< evaluated values will be stored here

    Pkt4Ptr pkt4_; ///< A stub DHCPv4 packet
    Pkt6Ptr pkt6_; ///< A stub DHCPv6 packet

    OptionPtr option_str4_; ///< A string option for DHCPv4
    OptionPtr option_str6_; ///< A string option for DHCPv6

    OptionVendorPtr vendor_; ///< Vendor option used during tests
    OptionVendorClassPtr vendor_class_; ///< Vendor class option used during tests

    /// @brief Verify that the substring eval works properly
    ///
    /// This function takes the parameters and sets up the value
    /// stack then executes the eval and checks the results.
    ///
    /// @param test_string The string to operate on
    /// @param test_start The position to start when getting a substring
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
            testEvaluate(t_, *pkt4_, values_);

            // verify results
            ASSERT_EQ(1, values_.size());
            EXPECT_EQ(result_string, values_.top());

            // remove result
            values_.pop();
        }
    }

    /// @brief Verify that the split eval works properly
    ///
    /// This function takes the parameters and sets up the value
    /// stack then executes the eval and checks the results.
    ///
    /// @param test_string The string to operate on
    /// @param test_delimiters The string of delimiter characters to split upon
    /// @param test_field The field number of the desired field
    /// @param result_string The expected result of the eval
    /// @param should_throw The eval will throw
    void verifySplitEval(const std::string& test_string,
                         const std::string& test_delimiters,
                         const std::string& test_field,
                         const std::string& result_string,
                         bool should_throw = false) {
        // create the token
        ASSERT_NO_THROW(t_.reset(new TokenSplit()));

        // push values on stack
        values_.push(test_string);
        values_.push(test_delimiters);
        values_.push(test_field);

        // evaluate the token
        if (should_throw) {
            EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalTypeError);
            ASSERT_EQ(0, values_.size());
        } else {
            testEvaluate(t_, *pkt4_, values_);

            // verify results
            ASSERT_EQ(1, values_.size());
            EXPECT_EQ(result_string, values_.top());

            // remove result
            values_.pop();
        }
    }

    /// @brief Creates vendor-option with specified value and adds it to packet
    ///
    /// This method creates specified vendor option, removes any existing
    /// vendor options and adds the new one to v4 or v6 packet.
    ///
    /// @param u universe (V4 or V6)
    /// @param vendor_id specifies enterprise-id value.
    void setVendorOption(Option::Universe u, uint32_t vendor_id) {
        vendor_.reset(new OptionVendor(u, vendor_id));
        switch (u) {
        case Option::V4:
            pkt4_->delOption(DHO_VIVSO_SUBOPTIONS);
            pkt4_->addOption(vendor_);
            break;
        case Option::V6:
            pkt6_->delOption(D6O_VENDOR_OPTS);
            pkt6_->addOption(vendor_);
            break;
        }
    }

    /// @brief Creates vendor-class option with specified values and adds it to packet
    ///
    /// This method creates specified vendor-class option, removes any existing
    /// vendor class options and adds the new one to v4 or v6 packet.
    /// It also creates data tuples with greek alphabet names.
    ///
    /// @param u universe (V4 or V6)
    /// @param vendor_id specifies enterprise-id value.
    /// @param tuples_size number of data tuples to create.
    void setVendorClassOption(Option::Universe u, uint32_t vendor_id,
                              size_t tuples_size = 0) {
        // Create the option first.
        vendor_class_.reset(new OptionVendorClass(u, vendor_id));

        // Now let's add specified number of data tuples
        OpaqueDataTuple::LengthFieldType len = (u == Option::V4?OpaqueDataTuple::LENGTH_1_BYTE:
                                                OpaqueDataTuple::LENGTH_2_BYTES);
        const char* content[] = { "alpha", "beta", "delta", "gamma", "epsilon",
                                  "zeta", "eta", "theta", "iota", "kappa" };
        const size_t nb_content = sizeof(content) / sizeof(char*);
        ASSERT_TRUE(tuples_size < nb_content);
        for (size_t i = 0; i < tuples_size; ++i) {
            OpaqueDataTuple tuple(len);
            tuple.assign(string(content[i]));
            if (u == Option::V4 && i == 0) {
                // vendor-class for v4 has a peculiar quirk. The first tuple is being
                // added, even if there's no data at all.
                vendor_class_->setTuple(0, tuple);
            } else {
                vendor_class_->addTuple(tuple);
            }
        }

        switch (u) {
        case Option::V4:
            pkt4_->delOption(DHO_VIVCO_SUBOPTIONS);
            pkt4_->addOption(vendor_class_);
            break;
        case Option::V6:
            pkt6_->delOption(D6O_VENDOR_CLASS);
            pkt6_->addOption(vendor_class_);
            break;
        }
    }

    /// @brief Auxiliary function that evaluates tokens and checks result
    ///
    /// Depending on the universe, either pkt4_ or pkt6_ are supposed to have
    /// all the necessary values and options set. The result is checked
    /// on the values_ stack.
    ///
    /// @param u universe (V4 or V6)
    /// @param expected_result text representation of the expected outcome
    void evaluate(Option::Universe u, std::string expected_result) {
        switch (u) {
        case Option::V4:
            testEvaluate(t_, *pkt4_, values_);
            break;
        case Option::V6:
            testEvaluate(t_, *pkt6_, values_);
            break;
        default:
            ADD_FAILURE() << "Invalid universe specified.";
        }
        ASSERT_EQ(1, values_.size());
        EXPECT_EQ(expected_result, values_.top());
    }

    /// @brief Tests if vendor token behaves properly.
    ///
    /// @param u universe (V4 or V6)
    /// @param token_vendor_id enterprise-id used in the token
    /// @param option_vendor_id enterprise-id used in option (0 means don't
    ///        create the option)
    /// @param expected_result text representation of the expected outcome
    void testVendorExists(Option::Universe u, uint32_t token_vendor_id,
                          uint32_t option_vendor_id,
                          const std::string& expected_result) {
        // Let's clear any old values, so we can run multiple cases in each test
        clearStack();

        // Create the token
        ASSERT_NO_THROW(t_.reset(new TokenVendor(u, token_vendor_id,
                                                 TokenOption::EXISTS)));

        // If specified option is non-zero, create it.
        if (option_vendor_id) {
            setVendorOption(u, option_vendor_id);
        }

        evaluate(u, expected_result);
    }

    /// @brief Tests if vendor token properly returns enterprise-id.
    ///
    /// @param u universe (V4 or V6)
    /// @param option_vendor_id enterprise-id used in option (0 means don't
    ///        create the option)
    /// @param expected_result text representation of the expected outcome
    void testVendorEnterprise(Option::Universe u, uint32_t option_vendor_id,
                              const std::string& expected_result) {
        // Let's clear any old values, so we can run multiple cases in each test
        clearStack();

        ASSERT_NO_THROW(t_.reset(new TokenVendor(u, 0, TokenVendor::ENTERPRISE_ID)));
        if (option_vendor_id) {
            setVendorOption(u, option_vendor_id);
        }

        evaluate(u, expected_result);
    }

    /// @brief Tests if vendor class token properly returns enterprise-id.
    ///
    /// @param u universe (V4 or V6)
    /// @param option_vendor_id enterprise-id used in option (0 means don't
    ///        create the option)
    /// @param expected_result text representation of the expected outcome
    void testVendorClassEnterprise(Option::Universe u, uint32_t option_vendor_id,
                                   const std::string& expected_result) {
        // Let's clear any old values, so we can run multiple cases in each test
        clearStack();

        ASSERT_NO_THROW(t_.reset(new TokenVendorClass(u, 0, TokenVendor::ENTERPRISE_ID)));
        if (option_vendor_id) {
            setVendorClassOption(u, option_vendor_id);
        }

        evaluate(u, expected_result);
    }

    /// @brief Tests if vendor class token can report existence properly.
    ///
    /// @param u universe (V4 or V6)
    /// @param token_vendor_id enterprise-id used in the token
    /// @param option_vendor_id enterprise-id used in option (0 means don't
    ///        create the option)
    /// @param expected_result text representation of the expected outcome
    void testVendorClassExists(Option::Universe u, uint32_t token_vendor_id,
                               uint32_t option_vendor_id,
                               const std::string& expected_result) {
        // Let's clear any old values, so we can run multiple cases in each test
        clearStack();

        ASSERT_NO_THROW(t_.reset(new TokenVendorClass(u, token_vendor_id,
                                                      TokenOption::EXISTS)));

        if (option_vendor_id) {
            setVendorClassOption(u, option_vendor_id);
        }

        evaluate(u, expected_result);
    }

    /// @brief Tests if vendor token can handle sub-options properly.
    ///
    /// @param u universe (V4 or V6)
    /// @param token_vendor_id enterprise-id used in the token
    /// @param token_option_code option code in the token
    /// @param option_vendor_id enterprise-id used in option (0 means don't
    ///        create the option)
    /// @param option_code sub-option code (0 means don't create suboption)
    /// @param repr representation (TokenOption::EXISTS or HEXADECIMAL)
    /// @param expected_result text representation of the expected outcome
    void testVendorSuboption(Option::Universe u,
                             uint32_t token_vendor_id, uint16_t token_option_code,
                             uint32_t option_vendor_id, uint16_t option_code,
                             TokenOption::RepresentationType repr,
                             const std::string& expected) {
        // Let's clear any old values, so we can run multiple cases in each test
        clearStack();

        ASSERT_NO_THROW(t_.reset(new TokenVendor(u, token_vendor_id, repr,
                                                 token_option_code)));
        if (option_vendor_id) {
            setVendorOption(u, option_vendor_id);
            if (option_code) {
                ASSERT_TRUE(vendor_);
                OptionPtr subopt(new OptionString(u, option_code, "alpha"));
                vendor_->addOption(subopt);
            }
        }

        evaluate(u, expected);
    }

    /// @brief Tests if vendor class token can handle data chunks properly.
    ///
    /// @param u universe (V4 or V6)
    /// @param token_vendor_id enterprise-id used in the token
    /// @param token_index data index used in the token
    /// @param option_vendor_id enterprise-id used in option (0 means don't
    ///        create the option)
    /// @param data_tuples number of data tuples in the option
    /// @param expected_result text representation of the expected outcome
    void testVendorClassData(Option::Universe u,
                             uint32_t token_vendor_id, uint16_t token_index,
                             uint32_t option_vendor_id, uint16_t data_tuples,
                             const std::string& expected) {
        // Let's clear any old values, so we can run multiple cases in each test
        clearStack();

        ASSERT_NO_THROW(t_.reset(new TokenVendorClass(u, token_vendor_id,
                                                      TokenVendor::DATA, token_index)));
        if (option_vendor_id) {
            setVendorClassOption(u, option_vendor_id, data_tuples);
        }

        evaluate(u, expected);
    }

    /// @brief Tests if TokenInteger evaluates to the proper value
    ///
    /// @param expected expected string representation on stack after evaluation
    /// @param value integer value passed to constructor
    void testInteger(const std::string& expected, uint32_t value) {

        clearStack();

        ASSERT_NO_THROW(t_.reset(new TokenInteger(value)));

        // The universe (v4 or v6) shouldn't have any impact on this,
        // but let's check it anyway.
        evaluate(Option::V4, expected);

        clearStack(false);
        evaluate(Option::V6, expected);

        clearStack(true);
    }

    /// @brief Tests if TokenMatch works as expected.
    ///
    /// @param reg_exp regular expression
    /// @param value value to match
    /// @param matched expected outcome of the match
    void testMatch(const std::string& reg_exp, const std::string& value,
                   bool matched) {
        clearStack();

        ASSERT_NO_THROW(t_.reset(new TokenMatch(reg_exp)));
        values_.push(value);
        // BTW not known easy way to get a runtime error with C++ regex.
        ASSERT_NO_THROW(evaluate(Option::V4, matched ? "true" : "false"));

        clearStack();
    }
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
    EXPECT_EQ(0, t_->getLabel());

    // Make sure that the token can be evaluated without exceptions.
    testEvaluate(t_, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("foo", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_STRING", "Pushing text string 'foo'", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This simple test checks that a TokenString, representing a constant string,
// can be used in Pkt4 evaluation. (The actual packet is not used)
TEST_F(TokenTest, string4Complex) {
    char data[] = "12345~!@#$%^&*()_+{}[];:<>/?\\67890\t \0\b\r\f'\""
                  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string data_str(data, sizeof(data) - 1);
    // Store constant string in the TokenString object.
    ASSERT_NO_THROW(t_.reset(new TokenString(data_str)));

    // Make sure that the token can be evaluated without exceptions.
    testEvaluate(t_, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ(data_str, values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    char expected[] = "Pushing text string '"
                      "12345~!@#$%^&*()_+{}[];:<>/?\\67890\t \0\b\r\f'\""
                      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'";
    string expected_str(expected, sizeof(expected) - 1);
    addString("EVAL_DEBUG_STRING", expected_str, pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This simple test checks that a TokenString, representing a constant string,
// can be used in Pkt6 evaluation. (The actual packet is not used)
TEST_F(TokenTest, string6) {

    // Store constant string "foo" in the TokenString object.
    ASSERT_NO_THROW(t_.reset(new TokenString("foo")));

    // Make sure that the token can be evaluated without exceptions.
    testEvaluate(t_, *pkt6_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("foo", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_STRING", "Pushing text string 'foo'", pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This simple test checks that a TokenString, representing a constant string,
// can be used in Pkt6 evaluation. (The actual packet is not used)
TEST_F(TokenTest, string6Complex) {
    char data[] = "12345~!@#$%^&*()_+{}[];:<>/?\\67890\t \0\b\r\f'\""
                  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string data_str(data, sizeof(data) - 1);
    // Store constant string in the TokenString object.
    ASSERT_NO_THROW(t_.reset(new TokenString(data_str)));

    // Make sure that the token can be evaluated without exceptions.
    testEvaluate(t_, *pkt6_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ(data_str, values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    char expected[] = "Pushing text string '"
                      "12345~!@#$%^&*()_+{}[];:<>/?\\67890\t \0\b\r\f'\""
                      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'";
    string expected_str(expected, sizeof(expected) - 1);
    addString("EVAL_DEBUG_STRING", expected_str, pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
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
    EXPECT_EQ(0, empty->getLabel());
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

    // Make sure that tokens can be evaluated without exceptions,
    // and verify the debug output
    testEvaluate(empty, *pkt4_, values_);
    testEvaluate(bad, *pkt4_, values_);
    testEvaluate(nodigit, *pkt4_, values_);
    testEvaluate(baddigit, *pkt4_, values_);
    testEvaluate(bell, *pkt4_, values_);
    testEvaluate(foo, *pkt4_, values_);
    testEvaluate(cookie, *pkt4_, values_);

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

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_HEXSTRING", "Pushing hex string 0x", pkt4_->getLabel());
    addString("EVAL_DEBUG_HEXSTRING", "Pushing hex string 0x", pkt4_->getLabel());
    addString("EVAL_DEBUG_HEXSTRING", "Pushing hex string 0x", pkt4_->getLabel());
    addString("EVAL_DEBUG_HEXSTRING", "Pushing hex string 0x", pkt4_->getLabel());
    addString("EVAL_DEBUG_HEXSTRING", "Pushing hex string 0x07", pkt4_->getLabel());
    addString("EVAL_DEBUG_HEXSTRING", "Pushing hex string 0x666F6F", pkt4_->getLabel());
    addString("EVAL_DEBUG_HEXSTRING", "Pushing hex string 0x63825363", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
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
    testEvaluate(empty, *pkt6_, values_);
    testEvaluate(bad, *pkt6_, values_);
    testEvaluate(nodigit, *pkt6_, values_);
    testEvaluate(baddigit, *pkt6_, values_);
    testEvaluate(bell, *pkt6_, values_);
    testEvaluate(foo, *pkt6_, values_);
    testEvaluate(cookie, *pkt6_, values_);

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

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_HEXSTRING", "Pushing hex string 0x", pkt6_->getLabel());
    addString("EVAL_DEBUG_HEXSTRING", "Pushing hex string 0x", pkt6_->getLabel());
    addString("EVAL_DEBUG_HEXSTRING", "Pushing hex string 0x", pkt6_->getLabel());
    addString("EVAL_DEBUG_HEXSTRING", "Pushing hex string 0x", pkt6_->getLabel());
    addString("EVAL_DEBUG_HEXSTRING", "Pushing hex string 0x07", pkt6_->getLabel());
    addString("EVAL_DEBUG_HEXSTRING", "Pushing hex string 0x666F6F", pkt6_->getLabel());
    addString("EVAL_DEBUG_HEXSTRING", "Pushing hex string 0x63825363", pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This simple test checks that a TokenLowerCase, representing a string
// converted to lower case, can be used in Pkt evaluation.  (The actual packet
// is not used)
TEST_F(TokenTest, lcase) {
    ASSERT_NO_THROW(t_.reset(new TokenLowerCase()));
    EXPECT_EQ(0, t_->getLabel());
    values_.push("LoWeR");

    // Make sure that the token can be evaluated without exceptions.
    testEvaluate(t_, *pkt6_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("lower", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_LCASE",
              "Popping string 'LoWeR' and pushing converted value to lower case 'lower'",
              pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This simple test checks that a TokenLowerCase, representing a complex string
// converted to lower case, can be used in Pkt evaluation.  (The actual packet
// is not used)
TEST_F(TokenTest, lcaseComplex) {
    ASSERT_NO_THROW(t_.reset(new TokenLowerCase()));
    char data[] = "12345~!@#$%^&*()_+LoWeR{}[];:<>/?\\67890\t \0\b\r\f";
    string data_str(data, sizeof(data) - 1);
    values_.push(data_str);

    // Make sure that the token can be evaluated without exceptions.
    testEvaluate(t_, *pkt6_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(1, values_.size());
    char expected_data[] = "12345~!@#$%^&*()_+lower{}[];:<>/?\\67890\t \0\b\r\f";
    string expected_data_str(expected_data, sizeof(expected_data) - 1);
    EXPECT_EQ(expected_data_str, values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    char expected[] = "Popping string '"
                      "12345~!@#$%^&*()_+LoWeR{}[];:<>/?\\67890\t \0\b\r\f' "
                      "and pushing converted value to lower case '"
                      "12345~!@#$%^&*()_+lower{}[];:<>/?\\67890\t \0\b\r\f'";
    string expected_str(expected, sizeof(expected) - 1);
    addString("EVAL_DEBUG_LCASE", expected_str, pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This simple test checks that a TokenUpperCase, representing a string
// converted to upper case, can be used in Pkt evaluation.  (The actual packet
// is not used)
TEST_F(TokenTest, ucase) {
    ASSERT_NO_THROW(t_.reset(new TokenUpperCase()));
    EXPECT_EQ(0, t_->getLabel());
    values_.push("uPpEr");

    // Make sure that the token can be evaluated without exceptions.
    testEvaluate(t_, *pkt6_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("UPPER", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_UCASE",
              "Popping string 'uPpEr' and pushing converted value to upper case 'UPPER'",
              pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This simple test checks that a TokenUpperCase, representing a complex string
// converted to upper case, can be used in Pkt evaluation.  (The actual packet
// is not used)
TEST_F(TokenTest, ucaseComplex) {
    ASSERT_NO_THROW(t_.reset(new TokenUpperCase()));
    char data[] = "12345~!@#$%^&*()_+uPpEr{}[];:<>/?\\67890\t \0\b\r\f";
    string data_str(data, sizeof(data) - 1);
    values_.push(data_str);

    // Make sure that the token can be evaluated without exceptions.
    testEvaluate(t_, *pkt6_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(1, values_.size());
    char expected_data[] = "12345~!@#$%^&*()_+UPPER{}[];:<>/?\\67890\t \0\b\r\f";
    string expected_data_str(expected_data, sizeof(expected_data) - 1);
    EXPECT_EQ(expected_data_str, values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    char expected[] = "Popping string '"
                      "12345~!@#$%^&*()_+uPpEr{}[];:<>/?\\67890\t \0\b\r\f' "
                      "and pushing converted value to upper case '"
                      "12345~!@#$%^&*()_+UPPER{}[];:<>/?\\67890\t \0\b\r\f'";
    string expected_str(expected, sizeof(expected) - 1);
    addString("EVAL_DEBUG_UCASE", expected_str, pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
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
    EXPECT_EQ(0, ip4->getLabel());
    ASSERT_NO_THROW(ip6.reset(new TokenIpAddress("2001:db8::1")));

    // Make sure that tokens can be evaluated without exceptions.
    testEvaluate(ip4, *pkt4_, values_);
    testEvaluate(ip6, *pkt6_, values_);
    testEvaluate(bad4, *pkt4_, values_);
    testEvaluate(bad6, *pkt6_, values_);

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

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_IPADDRESS", "Pushing IPAddress 0x0A000001", pkt4_->getLabel());
    addString("EVAL_DEBUG_IPADDRESS", "Pushing IPAddress 0x20010DB8000000000000000000000001",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_IPADDRESS", "Pushing IPAddress 0x", pkt4_->getLabel());
    addString("EVAL_DEBUG_IPADDRESS", "Pushing IPAddress 0x", pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks that a TokenIpAddressToText, representing an IP address as
// a string, can be used in Pkt4/Pkt6 evaluation.
// (The actual packet is not used)
TEST_F(TokenTest, addressToText) {
    TokenPtr address((new TokenIpAddressToText()));
    EXPECT_EQ(0, address->getLabel());
    std::vector<uint8_t> bytes;

    std::string value = "10.0.0.1";
    values_.push(value);

    // Invalid data size fails.
    EXPECT_THROW(address->evaluate(*pkt4_, values_), EvalTypeError);

    bytes = IOAddress(value).toBytes();
    values_.push(std::string(bytes.begin(), bytes.end()));

    testEvaluate(address, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(1, values_.size());

    value = "2001:db8::1";
    bytes = IOAddress(value).toBytes();
    values_.push(std::string(bytes.begin(), bytes.end()));

    testEvaluate(address, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(2, values_.size());

    values_.push(std::string());
    testEvaluate(address, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(3, values_.size());

    // Check empty data
    EXPECT_EQ(0, values_.top().size());
    EXPECT_EQ("", values_.top());
    values_.pop();

    // Check IPv6 address
    EXPECT_EQ(11, values_.top().size());
    EXPECT_EQ("2001:db8::1", values_.top());
    values_.pop();

    // Check IPv4 address
    EXPECT_EQ(8, values_.top().size());
    EXPECT_EQ("10.0.0.1", values_.top());
    values_.pop();

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_IPADDRESSTOTEXT", "Pushing IPAddress 10.0.0.1", pkt4_->getLabel());
    addString("EVAL_DEBUG_IPADDRESSTOTEXT", "Pushing IPAddress 2001:db8::1", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks that a TokenIntToText, representing an integer as a string,
// can be used in Pkt4/Pkt6 evaluation.
// (The actual packet is not used)
TEST_F(TokenTest, integerToText) {
    TokenPtr int8token((new TokenInt8ToText()));
    EXPECT_EQ(0, int8token->getLabel());
    TokenPtr int16token((new TokenInt16ToText()));
    EXPECT_EQ(0, int16token->getLabel());
    TokenPtr int32token((new TokenInt32ToText()));
    EXPECT_EQ(0, int32token->getLabel());
    TokenPtr uint8token((new TokenUInt8ToText()));
    EXPECT_EQ(0, uint8token->getLabel());
    TokenPtr uint16token((new TokenUInt16ToText()));
    EXPECT_EQ(0, uint16token->getLabel());
    TokenPtr uint32token((new TokenUInt32ToText()));
    EXPECT_EQ(0, uint32token->getLabel());

    std::vector<uint8_t> bytes;
    std::string value = "0123456789";

    // Invalid data size fails.
    values_.push(value);
    EXPECT_THROW(int8token->evaluate(*pkt4_, values_), EvalTypeError);
    values_.push(value);
    EXPECT_THROW(int16token->evaluate(*pkt4_, values_), EvalTypeError);
    values_.push(value);
    EXPECT_THROW(int32token->evaluate(*pkt4_, values_), EvalTypeError);
    values_.push(value);
    EXPECT_THROW(uint8token->evaluate(*pkt4_, values_), EvalTypeError);
    values_.push(value);
    EXPECT_THROW(uint16token->evaluate(*pkt4_, values_), EvalTypeError);
    values_.push(value);
    EXPECT_THROW(uint32token->evaluate(*pkt4_, values_), EvalTypeError);

    uint64_t data = -1;

    values_.push(
        std::string(const_cast<const char*>(reinterpret_cast<char*>(&data)), sizeof(int8_t)));

    testEvaluate(int8token, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(1, values_.size());

    int16_t i16 = 0;
    memcpy(&i16, &data, sizeof(int16_t));
    values_.push(
        std::string(const_cast<const char*>(reinterpret_cast<char*>(&i16)), sizeof(int16_t)));

    testEvaluate(int16token, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(2, values_.size());

    int32_t i32 = 0;
    memcpy(&i32, &data, sizeof(int32_t));
    values_.push(
        std::string(const_cast<const char*>(reinterpret_cast<char*>(&i32)), sizeof(int32_t)));

    testEvaluate(int32token, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(3, values_.size());

    values_.push(
        std::string(const_cast<const char*>(reinterpret_cast<char*>(&data)), sizeof(uint8_t)));

    testEvaluate(uint8token, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(4, values_.size());

    uint16_t ui16 = 0;
    memcpy(&ui16, &data, sizeof(uint16_t));
    values_.push(
        std::string(const_cast<const char*>(reinterpret_cast<char*>(&ui16)), sizeof(uint16_t)));

    testEvaluate(uint16token, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(5, values_.size());

    uint32_t ui32 = 0;
    memcpy(&ui32, &data, sizeof(uint32_t));
    values_.push(
        std::string(const_cast<const char*>(reinterpret_cast<char*>(&ui32)), sizeof(uint32_t)));

    testEvaluate(uint32token, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(6, values_.size());

    value = "";

    values_.push(value);
    testEvaluate(int8token, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(7, values_.size());

    values_.push(value);
    testEvaluate(int16token, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(8, values_.size());

    values_.push(value);
    testEvaluate(int32token, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(9, values_.size());

    values_.push(value);
    testEvaluate(uint8token, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(10, values_.size());

    values_.push(value);
    testEvaluate(uint16token, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(11, values_.size());

    values_.push(value);
    testEvaluate(uint32token, *pkt4_, values_);

    // Check that the evaluation put its value on the values stack.
    ASSERT_EQ(12, values_.size());

    // Check empty data
    EXPECT_EQ(0, values_.top().size());
    EXPECT_EQ("", values_.top());
    values_.pop();

    // Check empty data
    EXPECT_EQ(0, values_.top().size());
    EXPECT_EQ("", values_.top());
    values_.pop();

    // Check empty data
    EXPECT_EQ(0, values_.top().size());
    EXPECT_EQ("", values_.top());
    values_.pop();

    // Check empty data
    EXPECT_EQ(0, values_.top().size());
    EXPECT_EQ("", values_.top());
    values_.pop();

    // Check empty data
    EXPECT_EQ(0, values_.top().size());
    EXPECT_EQ("", values_.top());
    values_.pop();

    // Check empty data
    EXPECT_EQ(0, values_.top().size());
    EXPECT_EQ("", values_.top());
    values_.pop();

    // Check uint32
    EXPECT_EQ(10, values_.top().size());
    EXPECT_EQ("4294967295", values_.top());
    values_.pop();

    // Check uint16
    EXPECT_EQ(5, values_.top().size());
    EXPECT_EQ("65535", values_.top());
    values_.pop();

    // Check uint8
    EXPECT_EQ(3, values_.top().size());
    EXPECT_EQ("255", values_.top());
    values_.pop();

    // Check int32
    EXPECT_EQ(2, values_.top().size());
    EXPECT_EQ("-1", values_.top());
    values_.pop();

    // Check int16
    EXPECT_EQ(2, values_.top().size());
    EXPECT_EQ("-1", values_.top());
    values_.pop();

    // Check int8
    EXPECT_EQ(2, values_.top().size());
    EXPECT_EQ("-1", values_.top());
    values_.pop();

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_INT8TOTEXT", "Pushing Int8 -1", pkt4_->getLabel());
    addString("EVAL_DEBUG_INT16TOTEXT", "Pushing Int16 -1", pkt4_->getLabel());
    addString("EVAL_DEBUG_INT32TOTEXT", "Pushing Int32 -1", pkt4_->getLabel());
    addString("EVAL_DEBUG_UINT8TOTEXT", "Pushing UInt8 255", pkt4_->getLabel());
    addString("EVAL_DEBUG_UINT16TOTEXT", "Pushing UInt16 65535", pkt4_->getLabel());
    addString("EVAL_DEBUG_UINT32TOTEXT", "Pushing UInt32 4294967295", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks if a token representing an option value is able to extract
// the option from an IPv4 packet and properly store the option's value.
TEST_F(TokenTest, optionString4) {
    TokenPtr found;
    TokenPtr not_found;

    // The packets we use have option 100 with a string in them.
    ASSERT_NO_THROW(found.reset(new TokenOption(100, TokenOption::TEXTUAL)));
    EXPECT_EQ(0, found->getLabel());
    ASSERT_NO_THROW(not_found.reset(new TokenOption(101, TokenOption::TEXTUAL)));

    // This should evaluate to the content of the option 100 (i.e. "hundred4")
    testEvaluate(found, *pkt4_, values_);

    // This should evaluate to "" as there is no option 101.
    testEvaluate(not_found, *pkt4_, values_);

    // There should be 2 values evaluated.
    ASSERT_EQ(2, values_.size());

    // This is a stack, so the pop order is inversed. We should get the empty
    // string first.
    EXPECT_EQ("", values_.top());
    values_.pop();

    // Then the content of the option 100.
    EXPECT_EQ("hundred4", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_OPTION", "Pushing option 100 with value 'hundred4'", pkt4_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 101 with value ''", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
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
    testEvaluate(found, *pkt4_, values_);

    // This should evaluate to "" as there is no option 101.
    testEvaluate(not_found, *pkt4_, values_);

    // There should be 2 values evaluated.
    ASSERT_EQ(2, values_.size());

    // This is a stack, so the pop order is inversed. We should get the empty
    // string first.
    EXPECT_EQ("", values_.top());
    values_.pop();

    // Then the content of the option 100.
    EXPECT_EQ("hundred4", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_OPTION", "Pushing option 100 with value 0x68756E6472656434",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 101 with value 0x", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks if a token representing an option value is able to check
// the existence of the option from an IPv4 packet.
TEST_F(TokenTest, optionExistsString4) {
    TokenPtr found;
    TokenPtr not_found;

    // The packets we use have option 100 with a string in them.
    ASSERT_NO_THROW(found.reset(new TokenOption(100, TokenOption::EXISTS)));
    ASSERT_NO_THROW(not_found.reset(new TokenOption(101, TokenOption::EXISTS)));

    testEvaluate(found, *pkt4_, values_);
    testEvaluate(not_found, *pkt4_, values_);

    // There should be 2 values evaluated.
    ASSERT_EQ(2, values_.size());

    // This is a stack, so the pop order is inversed.
    EXPECT_EQ("false", values_.top());
    values_.pop();
    EXPECT_EQ("true", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_OPTION", "Pushing option 100 with value 'true'", pkt4_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 101 with value 'false'", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
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
    testEvaluate(found, *pkt6_, values_);

    // This should evaluate to "" as there is no option 101.
    testEvaluate(not_found, *pkt6_, values_);

    // There should be 2 values evaluated.
    ASSERT_EQ(2, values_.size());

    // This is a stack, so the pop order is inversed. We should get the empty
    // string first.
    EXPECT_EQ("", values_.top());
    values_.pop();

    // Then the content of the option 100.
    EXPECT_EQ("hundred6", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_OPTION", "Pushing option 100 with value 'hundred6'", pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 101 with value ''", pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
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
    testEvaluate(found, *pkt6_, values_);

    // This should evaluate to "" as there is no option 101.
    testEvaluate(not_found, *pkt6_, values_);

    // There should be 2 values evaluated.
    ASSERT_EQ(2, values_.size());

    // This is a stack, so the pop order is inversed. We should get the empty
    // string first.
    EXPECT_EQ("", values_.top());
    values_.pop();

    // Then the content of the option 100.
    EXPECT_EQ("hundred6", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_OPTION", "Pushing option 100 with value 0x68756E6472656436",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 101 with value 0x", pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks if a token representing an option value is able to check
// the existence of the option from an IPv6 packet.
TEST_F(TokenTest, optionExistsString6) {
    TokenPtr found;
    TokenPtr not_found;

    // The packets we use have option 100 with a string in them.
    ASSERT_NO_THROW(found.reset(new TokenOption(100, TokenOption::EXISTS)));
    ASSERT_NO_THROW(not_found.reset(new TokenOption(101, TokenOption::EXISTS)));

    testEvaluate(found, *pkt6_, values_);
    testEvaluate(not_found, *pkt6_, values_);

    // There should be 2 values evaluated.
    ASSERT_EQ(2, values_.size());

    // This is a stack, so the pop order is inversed.
    EXPECT_EQ("false", values_.top());
    values_.pop();
    EXPECT_EQ("true", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_OPTION", "Pushing option 100 with value 'true'", pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 101 with value 'false'", pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks that the existing relay4 option can be found.
TEST_F(TokenTest, relay4Option) {

    // Insert relay option with sub-options 1 and 13
    insertRelay4Option();

    // Creating the token should be safe.
    ASSERT_NO_THROW(t_.reset(new TokenRelay4Option(13, TokenOption::TEXTUAL)));

    // We should be able to evaluate it.
    testEvaluate(t_, *pkt4_, values_);

    // we should have one value on the stack
    ASSERT_EQ(1, values_.size());

    // The option should be found and relay4[13] should evaluate to the
    // content of that sub-option, i.e. "thirteen"
    EXPECT_EQ("thirteen", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_OPTION", "Pushing option 13 with value 'thirteen'", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks that the code properly handles cases when
// there is a RAI option, but there's no requested sub-option.
TEST_F(TokenTest, relay4OptionNoSuboption) {

    // Insert relay option with sub-options 1 and 13
    insertRelay4Option();

    // Creating the token should be safe.
    ASSERT_NO_THROW(t_.reset(new TokenRelay4Option(15, TokenOption::TEXTUAL)));
    EXPECT_EQ(0, t_->getLabel());

    // We should be able to evaluate it.
    testEvaluate(t_, *pkt4_, values_);

    // we should have one value on the stack
    ASSERT_EQ(1, values_.size());

    // The option should NOT be found (there is no sub-option 15),
    // so the expression should evaluate to ""
    EXPECT_EQ("", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_OPTION", "Pushing option 15 with value ''", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks that the code properly handles cases when
// there's no RAI option at all.
TEST_F(TokenTest, relay4OptionNoRai) {

    // We didn't call insertRelay4Option(), so there's no RAI option.

    // Creating the token should be safe.
    ASSERT_NO_THROW(t_.reset(new TokenRelay4Option(13, TokenOption::TEXTUAL)));

    // We should be able to evaluate it.
    testEvaluate(t_, *pkt4_, values_);

    // we should have one value on the stack
    ASSERT_EQ(1, values_.size());

    // The option should NOT be found (there is no sub-option 13),
    // so the expression should evaluate to ""
    EXPECT_EQ("", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_OPTION", "Pushing option 13 with value ''", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
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
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("thirteen", values_.top());

    // Try to get option 1. It should get the one from RAI
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenRelay4Option(1, TokenOption::TEXTUAL)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("one", values_.top());

    // Try to get option 70. It should fail, as there's no such
    // sub option in RAI.
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenRelay4Option(70, TokenOption::TEXTUAL)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("", values_.top());

    // Try to check option 1. It should return "true"
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenRelay4Option(1, TokenOption::EXISTS)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());

    // Try to check option 70. It should return "false"
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenRelay4Option(70, TokenOption::EXISTS)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_OPTION", "Pushing option 13 with value 'thirteen'", pkt4_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 1 with value 'one'", pkt4_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 70 with value ''", pkt4_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 1 with value 'true'", pkt4_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 70 with value 'false'", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
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

    // Level -1, the same as level 1
    verifyRelay6Option(-1, 100, TokenOption::TEXTUAL, "hundred.one");
    verifyRelay6Option(-1, 101, TokenOption::TEXTUAL, "");
    verifyRelay6Option(-1, 102, TokenOption::TEXTUAL, "hundredtwo.one");

    // Level -2, the same as level 0
    verifyRelay6Option(-2, 100, TokenOption::TEXTUAL, "hundred.zero");
    verifyRelay6Option(-2, 100, TokenOption::EXISTS, "true");
    verifyRelay6Option(-2, 101, TokenOption::TEXTUAL, "hundredone.zero");
    verifyRelay6Option(-2, 102, TokenOption::TEXTUAL, "");
    verifyRelay6Option(-2, 102, TokenOption::EXISTS, "false");

    // Level -3, no encapsulation so no options
    verifyRelay6Option(-3, 100, TokenOption::TEXTUAL, "");

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_OPTION", "Pushing option 100 with value 'hundred.zero'",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 100 with value 'true'", pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 101 with value 'hundredone.zero'",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 102 with value ''", pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 102 with value 'false'", pkt6_->getLabel());

    addString("EVAL_DEBUG_OPTION", "Pushing option 100 with value 'hundred.one'",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 101 with value ''", pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 102 with value 'hundredtwo.one'",
              pkt6_->getLabel());

    addString("EVAL_DEBUG_OPTION", "Pushing option 100 with value ''", pkt6_->getLabel());

    addString("EVAL_DEBUG_OPTION", "Pushing option 100 with value 'hundred.one'",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 101 with value ''", pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 102 with value 'hundredtwo.one'",
              pkt6_->getLabel());

    addString("EVAL_DEBUG_OPTION", "Pushing option 100 with value 'hundred.zero'",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 100 with value 'true'", pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 101 with value 'hundredone.zero'",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 102 with value ''", pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 102 with value 'false'", pkt6_->getLabel());

    addString("EVAL_DEBUG_OPTION", "Pushing option 100 with value ''", pkt6_->getLabel());

    EXPECT_TRUE(checkFile());
}

// Verifies that relay6 option requires DHCPv6
TEST_F(TokenTest, relay6OptionError) {
    // Create a relay6 option token
    ASSERT_NO_THROW(t_.reset(new TokenRelay6Option(0, 13, TokenOption::TEXTUAL)));
    EXPECT_EQ(0, t_->getLabel());

    // A DHCPv6 packet is required
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalTypeError);
}

// Verifies that DHCPv4 packet metadata can be extracted.
TEST_F(TokenTest, pkt4MetaData) {
    pkt4_->setIface("eth0");
    pkt4_->setLocalAddr(IOAddress("10.0.0.1"));
    pkt4_->setRemoteAddr(IOAddress("10.0.0.2"));

    // Check interface (expect eth0)
    ASSERT_NO_THROW(t_.reset(new TokenPkt(TokenPkt::IFACE)));
    EXPECT_EQ(0, t_->getLabel());
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    ASSERT_EQ("eth0", values_.top());

    // Check source (expect 10.0.0.2)
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt(TokenPkt::SRC)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    vector<uint8_t> a2 = IOAddress("10.0.0.2").toBytes();
    ASSERT_EQ(a2.size(), values_.top().size());
    EXPECT_EQ(0, memcmp(&a2[0], &values_.top()[0], a2.size()));

    // Check destination (expect 10.0.0.1)
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt(TokenPkt::DST)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    vector<uint8_t> a1 = IOAddress("10.0.0.1").toBytes();
    ASSERT_EQ(a1.size(), values_.top().size());
    EXPECT_EQ(0, memcmp(&a1[0], &values_.top()[0], a1.size()));

    // Check length (expect 249)
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt(TokenPkt::LEN)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    uint32_t length = htonl(static_cast<uint32_t>(pkt4_->len()));
    ASSERT_EQ(4, values_.top().size());
    EXPECT_EQ(0, memcmp(&length, &values_.top()[0], 4));

    // Unknown metadata type fails
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt(TokenPkt::MetadataType(100))));
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalTypeError);

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_PKT", "Pushing PKT meta data iface with value eth0", pkt4_->getLabel());
    addString("EVAL_DEBUG_PKT", "Pushing PKT meta data src with value 0x0A000002",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_PKT", "Pushing PKT meta data dst with value 0x0A000001",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_PKT", "Pushing PKT meta data len with value 0x000000F9",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Verifies that DHCPv6 packet metadata can be extracted.
TEST_F(TokenTest, pkt6MetaData) {
    pkt6_->setIface("eth0");
    pkt6_->setLocalAddr(IOAddress("ff02::1:2"));
    pkt6_->setRemoteAddr(IOAddress("fe80::1234"));

    // Check interface (expect eth0)
    ASSERT_NO_THROW(t_.reset(new TokenPkt(TokenPkt::IFACE)));
    testEvaluate(t_, *pkt6_, values_);
    ASSERT_EQ(1, values_.size());
    ASSERT_EQ("eth0", values_.top());

    // Check source (expect fe80::1234)
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt(TokenPkt::SRC)));
    testEvaluate(t_, *pkt6_, values_);
    ASSERT_EQ(1, values_.size());
    ASSERT_EQ(16, values_.top().size());
    EXPECT_EQ(0xfe, static_cast<uint8_t>(values_.top()[0]));
    EXPECT_EQ(0x80, static_cast<uint8_t>(values_.top()[1]));
    for (unsigned i = 2; i < 14; ++i) {
        EXPECT_EQ(0, values_.top()[i]);
    }
    EXPECT_EQ(0x12, values_.top()[14]);
    EXPECT_EQ(0x34, values_.top()[15]);

    // Check destination (expect ff02::1:2)
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt(TokenPkt::DST)));
    testEvaluate(t_, *pkt6_, values_);
    ASSERT_EQ(1, values_.size());
    vector<uint8_t> ma = IOAddress("ff02::1:2").toBytes();
    ASSERT_EQ(ma.size(), values_.top().size());
    EXPECT_EQ(0, memcmp(&ma[0], &values_.top()[0], ma.size()));

    // Check length (expect 16)
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt(TokenPkt::LEN)));
    testEvaluate(t_, *pkt6_, values_);
    ASSERT_EQ(1, values_.size());
    uint32_t length = htonl(static_cast<uint32_t>(pkt6_->len()));
    ASSERT_EQ(4, values_.top().size());
    EXPECT_EQ(0, memcmp(&length, &values_.top()[0], 4));

    // Unknown meta data type fails
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt(TokenPkt::MetadataType(100))));
    EXPECT_THROW(t_->evaluate(*pkt6_, values_), EvalTypeError);

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_PKT", "Pushing PKT meta data iface with value eth0", pkt6_->getLabel());
    addString("EVAL_DEBUG_PKT",
              "Pushing PKT meta data src with value 0xFE800000000000000000000000001234",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_PKT",
              "Pushing PKT meta data dst with value 0xFF020000000000000000000000010002",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_PKT", "Pushing PKT meta data len with value 0x00000010",
              pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Verifies if the DHCPv4 packet fields can be extracted.
TEST_F(TokenTest, pkt4Fields) {
    pkt4_->setGiaddr(IOAddress("192.0.2.1"));
    pkt4_->setCiaddr(IOAddress("192.0.2.2"));
    pkt4_->setYiaddr(IOAddress("192.0.2.3"));
    pkt4_->setSiaddr(IOAddress("192.0.2.4"));

    // We're setting hardware address to uncommon (7 bytes rather than 6 and
    // hardware type 123) HW address. We'll use it in hlen and htype checks.
    HWAddrPtr hw(new HWAddr(HWAddr::fromText("01:02:03:04:05:06:07", 123)));
    pkt4_->setHWAddr(hw);

    // Check hardware address field.
    ASSERT_NO_THROW(t_.reset(new TokenPkt4(TokenPkt4::CHADDR)));
    EXPECT_EQ(0, t_->getLabel());
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    uint8_t expected_hw[] = { 1, 2, 3, 4, 5, 6, 7 };
    ASSERT_EQ(7, values_.top().size());
    EXPECT_EQ(0, memcmp(expected_hw, &values_.top()[0], 7));

    // Check hlen value field.
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt4(TokenPkt4::HLEN)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    ASSERT_EQ(4, values_.top().size());
    uint32_t expected_hlen = htonl(7);
    EXPECT_EQ(0, memcmp(&expected_hlen, &values_.top()[0], 4));

    // Check htype value.
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt4(TokenPkt4::HTYPE)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    ASSERT_EQ(4, values_.top().size());
    uint32_t expected_htype = htonl(123);
    EXPECT_EQ(0, memcmp(&expected_htype, &values_.top()[0], 4));

    // Check giaddr value.
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt4(TokenPkt4::GIADDR)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    uint8_t expected_addr[] = { 192, 0, 2, 1 };
    ASSERT_EQ(4, values_.top().size());
    EXPECT_EQ(0, memcmp(expected_addr, &values_.top()[0], 4));

    // Check ciaddr value.
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt4(TokenPkt4::CIADDR)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    expected_addr[3] = 2;
    ASSERT_EQ(4, values_.top().size());
    EXPECT_EQ(0, memcmp(expected_addr, &values_.top()[0], 4));

    // Check yiaddr value.
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt4(TokenPkt4::YIADDR)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    expected_addr[3] = 3;
    ASSERT_EQ(4, values_.top().size());
    EXPECT_EQ(0, memcmp(expected_addr, &values_.top()[0], 4));

    // Check siaddr value.
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt4(TokenPkt4::SIADDR)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    expected_addr[3] = 4;
    ASSERT_EQ(4, values_.top().size());
    EXPECT_EQ(0, memcmp(expected_addr, &values_.top()[0], 4));

    // Check msgtype.
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt4(TokenPkt4::MSGTYPE)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    ASSERT_EQ(4, values_.top().size());
    string exp_msgtype = encode(DHCPDISCOVER);
    EXPECT_EQ(0, memcmp(&exp_msgtype[0], &values_.top()[0], 4));

    // Check transaction-id
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt4(TokenPkt4::TRANSID)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    ASSERT_EQ(4, values_.top().size());
    string exp_transid = encode(12345);
    EXPECT_EQ(0, memcmp(&exp_transid[0], &values_.top()[0], 4));

    // Check a DHCPv6 packet throws.
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt4(TokenPkt4::HLEN)));
    EXPECT_THROW(t_->evaluate(*pkt6_, values_), EvalTypeError);

    // Unknown field fails
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt4(static_cast<TokenPkt4::FieldType>(100))));
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalTypeError);

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_PKT4", "Pushing PKT4 field mac with value 0x01020304050607",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_PKT4", "Pushing PKT4 field hlen with value 0x00000007",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_PKT4", "Pushing PKT4 field htype with value 0x0000007B",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_PKT4", "Pushing PKT4 field giaddr with value 0xC0000201",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_PKT4", "Pushing PKT4 field ciaddr with value 0xC0000202",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_PKT4", "Pushing PKT4 field yiaddr with value 0xC0000203",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_PKT4", "Pushing PKT4 field siaddr with value 0xC0000204",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_PKT4", "Pushing PKT4 field msgtype with value 0x00000001",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_PKT4", "Pushing PKT4 field transid with value 0x00003039",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Verifies if the DHCPv6 packet fields can be extracted.
TEST_F(TokenTest, pkt6Fields) {
    // The default test creates a v6 DHCPV6_SOLICIT packet with a
    // transaction id of 12345.

    // Check the message type
    ASSERT_NO_THROW(t_.reset(new TokenPkt6(TokenPkt6::MSGTYPE)));
    EXPECT_EQ(0, t_->getLabel());
    testEvaluate(t_, *pkt6_, values_);
    ASSERT_EQ(1, values_.size());
    uint32_t expected = htonl(1);
    EXPECT_EQ(0, memcmp(&expected, &values_.top()[0], 4));

    // Check the transaction id field
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt6(TokenPkt6::TRANSID)));
    testEvaluate(t_, *pkt6_, values_);
    ASSERT_EQ(1, values_.size());
    expected = htonl(12345);
    EXPECT_EQ(0, memcmp(&expected, &values_.top()[0], 4));

    // Check that working with a v4 packet generates an error
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt6(TokenPkt6::TRANSID)));
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalTypeError);

    // Unknown field fails
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenPkt6(static_cast<TokenPkt6::FieldType>(100))));
    EXPECT_THROW(t_->evaluate(*pkt6_, values_), EvalTypeError);

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_PKT6", "Pushing PKT6 field msgtype with value 0x00000001",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_PKT6", "Pushing PKT6 field transid with value 0x00003039",
              pkt6_->getLabel());

    EXPECT_TRUE(checkFile());
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
    verifyRelay6Eval(0, TokenRelay6Field::LINKADDR, 16, zeroaddr);
    verifyRelay6Eval(0, TokenRelay6Field::PEERADDR, 16, zeroaddr);

    // Level 1 link and peer should have different non-zero addresses
    verifyRelay6Eval(1, TokenRelay6Field::LINKADDR, 16, linkaddr);
    verifyRelay6Eval(1, TokenRelay6Field::PEERADDR, 16, peeraddr);

    // Level 2 has no encapsulation so the address should be zero length
    verifyRelay6Eval(2, TokenRelay6Field::LINKADDR, 0, zeroaddr);

    // Level -1 is the same as level 1
    verifyRelay6Eval(-1, TokenRelay6Field::LINKADDR, 16, linkaddr);
    verifyRelay6Eval(-1, TokenRelay6Field::PEERADDR, 16, peeraddr);

    // Level -2 is the same as level 0
    verifyRelay6Eval(-2, TokenRelay6Field::LINKADDR, 16, zeroaddr);
    verifyRelay6Eval(-2, TokenRelay6Field::PEERADDR, 16, zeroaddr);

    // Level -3 has no encapsulation so the address should be zero length
    verifyRelay6Eval(-3, TokenRelay6Field::LINKADDR, 0, zeroaddr);

    // Lets check that the layout of the address returned by the
    // token matches that of the TokenIpAddress
    TokenPtr trelay;
    TokenPtr taddr;
    TokenPtr tequal;
    ASSERT_NO_THROW(trelay.reset(new TokenRelay6Field(1, TokenRelay6Field::LINKADDR)));
    EXPECT_EQ(0, trelay->getLabel());
    ASSERT_NO_THROW(taddr.reset(new TokenIpAddress("1::1")));
    ASSERT_NO_THROW(tequal.reset(new TokenEqual()));

    testEvaluate(trelay, *pkt6_, values_);
    testEvaluate(taddr, *pkt6_, values_);
    testEvaluate(tequal, *pkt6_, values_);

    // We should have a single value on the stack and it should be "true"
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());

    // be tidy
    clearStack();

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_RELAY6",
              "Pushing PKT6 relay field linkaddr nest 0 with value "
              "0x00000000000000000000000000000000",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_RELAY6",
              "Pushing PKT6 relay field peeraddr nest 0 with value "
              "0x00000000000000000000000000000000",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_RELAY6",
              "Pushing PKT6 relay field linkaddr nest 1 with value "
              "0x00010000000000000000000000000001",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_RELAY6",
              "Pushing PKT6 relay field peeraddr nest 1 with value "
              "0x00010000000000000000000000000002",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_RELAY6_RANGE", "Pushing PKT6 relay field linkaddr nest 2 with value 0x",
              pkt6_->getLabel());

    addString("EVAL_DEBUG_RELAY6",
              "Pushing PKT6 relay field linkaddr nest -1 with value "
              "0x00010000000000000000000000000001",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_RELAY6",
              "Pushing PKT6 relay field peeraddr nest -1 with value "
              "0x00010000000000000000000000000002",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_RELAY6",
              "Pushing PKT6 relay field linkaddr nest -2 with value "
              "0x00000000000000000000000000000000",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_RELAY6",
              "Pushing PKT6 relay field peeraddr nest -2 with value "
              "0x00000000000000000000000000000000",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_RELAY6_RANGE", "Pushing PKT6 relay field linkaddr nest -3 with value 0x",
              pkt6_->getLabel());

    addString("EVAL_DEBUG_RELAY6",
              "Pushing PKT6 relay field linkaddr nest 1 with value "
              "0x00010000000000000000000000000001",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_IPADDRESS", "Pushing IPAddress 0x00010000000000000000000000000001",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_EQUAL",
              "Popping 0x00010000000000000000000000000001 and 0x00010000000000000000000000000001 "
              "pushing result 'true'",
              pkt6_->getLabel());

    EXPECT_TRUE(checkFile());
}

// This test checks some error cases for a relay6 field token
TEST_F(TokenTest, relay6FieldError) {
    // Create a valid relay6 field token
    ASSERT_NO_THROW(t_.reset(new TokenRelay6Field(0, TokenRelay6Field::LINKADDR)));
    EXPECT_EQ(0, t_->getLabel());

    // a DHCPv6 packet is required
    ASSERT_THROW(t_->evaluate(*pkt4_, values_), EvalTypeError);

    // No test for unknown field as it is not (yet) checked?!
}

// This test checks if a token representing an == operator is able to
// compare two values (with incorrectly built stack).
TEST_F(TokenTest, optionEqualInvalid) {

    ASSERT_NO_THROW(t_.reset(new TokenEqual()));
    EXPECT_EQ(0, t_->getLabel());

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
    testEvaluate(t_, *pkt4_, values_);

    // After evaluation there should be a single value that represents
    // result of "foo" == "bar" comparison.
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_EQUAL", "Popping 0x626172 and 0x666F6F pushing result 'false'",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks if a token representing an == operator is able to
// compare two identical values.
TEST_F(TokenTest, optionEqualTrue) {

    ASSERT_NO_THROW(t_.reset(new TokenEqual()));

    values_.push("foo");
    values_.push("foo");
    testEvaluate(t_, *pkt4_, values_);

    // After evaluation there should be a single value that represents
    // result of "foo" == "foo" comparison.
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_EQUAL", "Popping 0x666F6F and 0x666F6F pushing result 'true'",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks if a token representing a substring request
// throws an exception if there aren't enough values on the stack.
// The stack from the top is: length, start, string.
// The actual packet is not used.
TEST_F(TokenTest, substringNotEnoughValues) {
    ASSERT_NO_THROW(t_.reset(new TokenSubstring()));
    EXPECT_EQ(0, t_->getLabel());

    // Substring requires three values on the stack, try
    // with 0, 1 and 2 all should throw an exception
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    values_.push("");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    values_.push("0");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    // Three should work
    values_.push("0");
    testEvaluate(t_, *pkt4_, values_);

    // As we had an empty string to start with we should have an empty
    // one after the evaluate
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_SUBSTRING_EMPTY",
              "Popping length 0, start 0, string 0x pushing result 0x", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
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

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 6, start 0, string 0x666F6F626172 pushing result 0x666F6F626172",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length all, start 0, string 0x666F6F626172 pushing result 0x666F6F626172",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 123456, start 0, string 0x666F6F626172 pushing result 0x666F6F626172",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length all, start -6, string 0x666F6F626172 pushing result 0x666F6F626172",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Test getting a suffix, in this case the last 3 characters
TEST_F(TokenTest, substringTrailer) {
    verifySubstringEval("foobar", "3", "3", "bar");
    verifySubstringEval("foobar", "3", "all", "bar");
    verifySubstringEval("foobar", "-3", "all", "bar");
    verifySubstringEval("foobar", "-3", "123", "bar");

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 3, start 3, string 0x666F6F626172 pushing result 0x626172",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length all, start 3, string 0x666F6F626172 pushing result 0x626172",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length all, start -3, string 0x666F6F626172 pushing result 0x626172",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 123, start -3, string 0x666F6F626172 pushing result 0x626172",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Test getting the middle of the string in different ways
TEST_F(TokenTest, substringMiddle) {
    verifySubstringEval("foobar", "1", "4", "ooba");
    verifySubstringEval("foobar", "-5", "4", "ooba");
    verifySubstringEval("foobar", "-1", "-4", "ooba");
    verifySubstringEval("foobar", "5", "-4", "ooba");

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 4, start 1, string 0x666F6F626172 pushing result 0x6F6F6261",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 4, start -5, string 0x666F6F626172 pushing result 0x6F6F6261",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length -4, start -1, string 0x666F6F626172 pushing result 0x6F6F6261",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length -4, start 5, string 0x666F6F626172 pushing result 0x6F6F6261",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Test getting the last letter in different ways
TEST_F(TokenTest, substringLastLetter) {
    verifySubstringEval("foobar", "5", "all", "r");
    verifySubstringEval("foobar", "5", "1", "r");
    verifySubstringEval("foobar", "5", "5", "r");
    verifySubstringEval("foobar", "-1", "all", "r");
    verifySubstringEval("foobar", "-1", "1", "r");
    verifySubstringEval("foobar", "-1", "5", "r");

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length all, start 5, string 0x666F6F626172 pushing result 0x72",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 1, start 5, string 0x666F6F626172 pushing result 0x72",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 5, start 5, string 0x666F6F626172 pushing result 0x72",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length all, start -1, string 0x666F6F626172 pushing result 0x72",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 1, start -1, string 0x666F6F626172 pushing result 0x72",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 5, start -1, string 0x666F6F626172 pushing result 0x72",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
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

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length -4, start 0, string 0x666F6F626172 pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length -4, start 1, string 0x666F6F626172 pushing result 0x66",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length -4, start 2, string 0x666F6F626172 pushing result 0x666F",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length -4, start 3, string 0x666F6F626172 pushing result 0x666F6F",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 4, start 3, string 0x666F6F626172 pushing result 0x626172",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 4, start 4, string 0x666F6F626172 pushing result 0x6172",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 4, start 5, string 0x666F6F626172 pushing result 0x72",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING_RANGE",
              "Popping length 4, start 6, string 0x666F6F626172 pushing result 0x",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Test that we get nothing if the starting position is out of the string
TEST_F(TokenTest, substringStartingPosition) {
    // Off the front
    verifySubstringEval("foobar", "-7", "1", "");
    verifySubstringEval("foobar", "-7", "-11", "");
    verifySubstringEval("foobar", "-7", "all", "");

    // and the back
    verifySubstringEval("foobar", "6", "1", "");
    verifySubstringEval("foobar", "6", "-11", "");
    verifySubstringEval("foobar", "6", "all", "");

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_SUBSTRING_RANGE",
              "Popping length 1, start -7, string 0x666F6F626172 pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING_RANGE",
              "Popping length -11, start -7, string 0x666F6F626172 pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING_RANGE",
              "Popping length all, start -7, string 0x666F6F626172 pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING_RANGE",
              "Popping length 1, start 6, string 0x666F6F626172 pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING_RANGE",
              "Popping length -11, start 6, string 0x666F6F626172 pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING_RANGE",
              "Popping length all, start 6, string 0x666F6F626172 pushing result 0x",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
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

    // These should result in a throw which should generate it's own
    // log entry
}

// lastly check that we don't get anything if the string is empty or
// we don't ask for any characters from it.
TEST_F(TokenTest, substringReturnEmpty) {
    verifySubstringEval("", "0", "all", "");
    verifySubstringEval("foobar", "0", "0", "");

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_SUBSTRING_EMPTY",
              "Popping length all, start 0, string 0x pushing result 0x", pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 0, start 0, string 0x666F6F626172 pushing result 0x",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Check if we can use the substring and equal tokens together
// We put the result on the stack first then the substring values
// then evaluate the substring which should leave the original
// result on the bottom with the substring result on next.
// Evaluating the equals should produce true for the first
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
    values_.push("foobar");
    values_.push("1");
    values_.push("4");
    testEvaluate(t_, *pkt4_, values_);

    // we should have two values on the stack
    ASSERT_EQ(2, values_.size());

    // next the equals eval
    testEvaluate(tequal, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());

    // get rid of the result
    values_.pop();

    // and try it again but with a bad final value
    // The final expected value
    values_.push("foob");

    // The substring values
    values_.push("foobar");
    values_.push("1");
    values_.push("4");
    testEvaluate(t_, *pkt4_, values_);

    // we should have two values on the stack
    ASSERT_EQ(2, values_.size());

    // next the equals eval
    testEvaluate(tequal, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 4, start 1, string 0x666F6F626172 pushing result 0x6F6F6261",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_EQUAL", "Popping 0x6F6F6261 and 0x6F6F6261 pushing result 'true'",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUBSTRING",
              "Popping length 4, start 1, string 0x666F6F626172 pushing result 0x6F6F6261",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_EQUAL", "Popping 0x6F6F6261 and 0x666F6F62 pushing result 'false'",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks if a token representing a concat request
// throws an exception if there aren't enough values on the stack.
// The actual packet is not used.
TEST_F(TokenTest, concat) {
    ASSERT_NO_THROW(t_.reset(new TokenConcat()));
    EXPECT_EQ(0, t_->getLabel());

    // Concat requires two values on the stack, try
    // with 0 and 1 both should throw an exception
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    values_.push("foo");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    // Two should work
    values_.push("bar");
    testEvaluate(t_, *pkt4_, values_);

    // Check the result
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("foobar", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_CONCAT", "Popping 0x626172 and 0x666F6F pushing 0x666F6F626172",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks if a token representing a hexstring request
// throws an exception if there aren't enough values on the stack.
// The actual packet is not used.
TEST_F(TokenTest, tohexstring) {
    ASSERT_NO_THROW(t_.reset(new TokenToHexString()));
    EXPECT_EQ(0, t_->getLabel());

    // Hexstring requires two values on the stack, try
    // with 0 and 1 both should throw an exception
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    values_.push("foo");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    // Two should work
    values_.push("-");
    testEvaluate(t_, *pkt4_, values_);

    // Check the result
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("66-6f-6f", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_TOHEXSTRING",
              "Popping binary value 0x666F6F and separator -, pushing result 66-6f-6f",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks if a token representing an ifelse is able
// to select the branch following the condition.
TEST_F(TokenTest, ifElse) {
    ASSERT_NO_THROW(t_.reset(new TokenIfElse()));
    EXPECT_EQ(0, t_->getLabel());

    // Ifelse requires three values on the stack, try
    // with 0, 1 and 2 all should throw an exception
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    values_.push("bar");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    values_.push("foo");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    // The condition must be a boolean
    values_.push("bar");
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalTypeError);

    // Check if what it returns
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenIfElse()));
    values_.push("true");
    values_.push("foo");
    values_.push("bar");
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("foo", values_.top());

    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenIfElse()));
    values_.push("false");
    values_.push("foo");
    values_.push("bar");
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("bar", values_.top());
}

// This test checks if a token representing a not is able to
// negate a boolean value (with incorrectly built stack).
TEST_F(TokenTest, operatorNotInvalid) {

    ASSERT_NO_THROW(t_.reset(new TokenNot()));
    EXPECT_EQ(0, t_->getLabel());

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
    testEvaluate(t_, *pkt4_, values_);

    // After evaluation there should be the negation of the value.
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());

    // Double negation is identity.
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_NOT", "Popping 'true' pushing 'false'", pkt4_->getLabel());
    addString("EVAL_DEBUG_NOT", "Popping 'false' pushing 'true'", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks if a token representing an and is able to
// conjugate two values (with incorrectly built stack).
TEST_F(TokenTest, operatorAndInvalid) {

    ASSERT_NO_THROW(t_.reset(new TokenAnd()));
    EXPECT_EQ(0, t_->getLabel());

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
    testEvaluate(t_, *pkt4_, values_);

    // After evaluation there should be a single "false" value
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());

    // After true and false, check false and true
    values_.push("true");
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());

    // And false and false
    values_.push("false");
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_AND", "Popping 'false' and 'true' pushing 'false'", pkt4_->getLabel());
    addString("EVAL_DEBUG_AND", "Popping 'true' and 'false' pushing 'false'", pkt4_->getLabel());
    addString("EVAL_DEBUG_AND", "Popping 'false' and 'false' pushing 'false'", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks if a token representing an and is able to
// conjugate two true values.
TEST_F(TokenTest, operatorAndTrue) {

    ASSERT_NO_THROW(t_.reset(new TokenAnd()));

    values_.push("true");
    values_.push("true");
    testEvaluate(t_, *pkt4_, values_);

    // After evaluation there should be a single "true" value
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_AND", "Popping 'true' and 'true' pushing 'true'", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks if a token representing an or is able to
// combine two values (with incorrectly built stack).
TEST_F(TokenTest, operatorOrInvalid) {

    ASSERT_NO_THROW(t_.reset(new TokenOr()));
    EXPECT_EQ(0, t_->getLabel());

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
    testEvaluate(t_, *pkt4_, values_);

    // After evaluation there should be a single "false" value
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_OR", "Popping 'false' and 'false' pushing 'false'", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks if a token representing an == operator is able to
// conjugate true with another logical
TEST_F(TokenTest, operatorOrTrue) {

    ASSERT_NO_THROW(t_.reset(new TokenOr()));

    values_.push("false");
    values_.push("true");
    testEvaluate(t_, *pkt4_, values_);

    // After evaluation there should be a single "true" value
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());

    // After false or true, checks true or false
    values_.push("false");
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());

    // And true or true
    values_.push("true");
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_OR", "Popping 'true' and 'false' pushing 'true'", pkt4_->getLabel());
    addString("EVAL_DEBUG_OR", "Popping 'false' and 'true' pushing 'true'", pkt4_->getLabel());
    addString("EVAL_DEBUG_OR", "Popping 'true' and 'true' pushing 'true'", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test verifies client class membership
TEST_F(TokenTest, member) {

    ASSERT_NO_THROW(t_.reset(new TokenMember("foo")));
    EXPECT_EQ(0, t_->getLabel());

    testEvaluate(t_, *pkt4_, values_);

    // the packet has no classes so false was left on the stack
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());
    values_.pop();

    // Add bar and retry
    pkt4_->addClass("bar");
    testEvaluate(t_, *pkt4_, values_);

    // the packet has a class but it is not foo
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());
    values_.pop();

    // Add foo and retry
    pkt4_->addClass("foo");
    testEvaluate(t_, *pkt4_, values_);

    // Now the packet is in the foo class
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());
}

// This test verifies if expression vendor[4491].exists works properly in DHCPv4.
TEST_F(TokenTest, vendor4SpecificVendorExists) {
    ASSERT_NO_THROW(t_.reset(new TokenVendor(Option::V4, 4491,
                                             TokenOption::EXISTS)));
    EXPECT_EQ(0, t_->getLabel());

    // Case 1: no option, should evaluate to false
    testVendorExists(Option::V4, 4491, 0, "false");

    // Case 2: option present, but uses different enterprise-id, should fail
    testVendorExists(Option::V4, 4491, 1234, "false");

    // Case 3: option present and has matching enterprise-id, should succeed
    testVendorExists(Option::V4, 4491, 4491, "true");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_NO_OPTION", "Option with code 125 missing, pushing result 'false'",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result 'false'", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_EXISTS",
              "Option with enterprise-id 4491 found, pushing result 'true'", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test verifies if expression vendor[4491].exists works properly in DHCPv6.
TEST_F(TokenTest, vendor6SpecificVendorExists) {
    // Case 1: no option, should evaluate to false
    testVendorExists(Option::V6, 4491, 0, "false");

    // Case 2: option present, but uses different enterprise-id, should fail
    testVendorExists(Option::V6, 4491, 1234, "false");

    // Case 3: option present and has matching enterprise-id, should succeed
    testVendorExists(Option::V6, 4491, 4491, "true");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_NO_OPTION", "Option with code 17 missing, pushing result 'false'",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result 'false'", pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_EXISTS",
              "Option with enterprise-id 4491 found, pushing result 'true'", pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

/// Test if expression vendor[*].exists works properly for DHCPv4.
TEST_F(TokenTest, vendor4AnyVendorExists) {
    // Case 1: no option, should evaluate to false
    testVendorExists(Option::V4, 0, 0, "false");

    // Case 2: option present with vendor-id 1234, should succeed
    testVendorExists(Option::V4, 0, 1234, "true");

    // Case 3: option present with vendor-id 4491, should succeed
    testVendorExists(Option::V4, 0, 4491, "true");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_NO_OPTION", "Option with code 125 missing, pushing result 'false'",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_EXISTS",
              "Option with enterprise-id 1234 found, pushing result 'true'", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_EXISTS",
              "Option with enterprise-id 4491 found, pushing result 'true'", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Test if expression vendor[*].exists works properly for DHCPv6.
TEST_F(TokenTest, vendor6AnyVendorExists) {
    // Case 1: no option, should evaluate to false
    testVendorExists(Option::V6, 0, 0, "false");

    // Case 2: option present with vendor-id 1234, should succeed
    testVendorExists(Option::V6, 0, 1234, "true");

    // Case 3: option present with vendor-id 4491, should succeed
    testVendorExists(Option::V6, 0, 4491, "true");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_NO_OPTION", "Option with code 17 missing, pushing result 'false'",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_EXISTS",
              "Option with enterprise-id 1234 found, pushing result 'true'", pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_EXISTS",
              "Option with enterprise-id 4491 found, pushing result 'true'", pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Test if expression vendor[*].enterprise works properly for DHCPv4.
TEST_F(TokenTest, vendor4enterprise) {
    // Case 1: No option present, should return empty string
    testVendorEnterprise(Option::V4, 0, "");

    // Case 2: Option with vendor-id 1234, should return "1234"
    testVendorEnterprise(Option::V4, 1234, encode(1234));

    // Case 3: Option with vendor-id set to maximum value, should still
    // be able to handle it
    testVendorEnterprise(Option::V4, 4294967295, encode(4294967295));

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_NO_OPTION", "Option with code 125 missing, pushing result ''",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_ENTERPRISE_ID", "Pushing enterprise-id 1234 as result 0x000004D2",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_ENTERPRISE_ID",
              "Pushing enterprise-id 4294967295 as result 0xFFFFFFFF", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Test if expression vendor[*].enterprise works properly for DHCPv6.
TEST_F(TokenTest, vendor6enterprise) {
    // Case 1: No option present, should return empty string
    testVendorEnterprise(Option::V6, 0, "");

    // Case 2: Option with vendor-id 1234, should return "1234"
    testVendorEnterprise(Option::V6, 1234, encode(1234));

    // Case 3: Option with vendor-id set to maximum value, should still
    // be able to handle it
    testVendorEnterprise(Option::V6, 4294967295, encode(4294967295));

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_NO_OPTION", "Option with code 17 missing, pushing result ''",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_ENTERPRISE_ID", "Pushing enterprise-id 1234 as result 0x000004D2",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_ENTERPRISE_ID",
              "Pushing enterprise-id 4294967295 as result 0xFFFFFFFF", pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This one tests "vendor[4491].option[1].exists" expression. There are so many
// wonderful ways in which this could fail: the option could not be there,
// it could have different enterprise-id, may not have suboption 1. Or may
// have the suboption with valid type, but enterprise may be different.
TEST_F(TokenTest, vendor4SuboptionExists) {
    // Case 1: expression vendor[4491].option[1].exists, no option present
    testVendorSuboption(Option::V4, 4491, 1, 0, 0, TokenOption::EXISTS, "false");

    // Case 2: expression vendor[4491].option[1].exists, option with vendor-id = 1234,
    // no suboptions, expected result "false"
    testVendorSuboption(Option::V4, 4491, 1, 1234, 0, TokenOption::EXISTS, "false");

    // Case 3: expression vendor[4491].option[1].exists, option with vendor-id = 1234,
    // suboption 1, expected result "false"
    testVendorSuboption(Option::V4, 4491, 1, 1234, 1, TokenOption::EXISTS, "false");

    // Case 4: expression vendor[4491].option[1].exists, option with vendor-id = 4491,
    // suboption 2, expected result "false"
    testVendorSuboption(Option::V4, 4491, 1, 4491, 2, TokenOption::EXISTS, "false");

    // Case 5: expression vendor[4491].option[1].exists, option with vendor-id = 4491,
    // suboption 1, expected result "true"
    testVendorSuboption(Option::V4, 4491, 1, 4491, 1, TokenOption::EXISTS, "true");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_NO_OPTION", "Option with code 125 missing, pushing result 'false'",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result 'false'", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result 'false'", pkt4_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 1 with value 'false'", pkt4_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 1 with value 'true'", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This is similar to the previous one, but tests vendor[4491].option[1].exists
// for DHCPv6.
TEST_F(TokenTest, vendor6SuboptionExists) {
    // Case 1: expression vendor[4491].option[1].exists, no option present
    testVendorSuboption(Option::V6, 4491, 1, 0, 0, TokenOption::EXISTS, "false");

    // Case 2: expression vendor[4491].option[1].exists, option with vendor-id = 1234,
    // no suboptions, expected result "false"
    testVendorSuboption(Option::V6, 4491, 1, 1234, 0, TokenOption::EXISTS, "false");

    // Case 3: expression vendor[4491].option[1].exists, option with vendor-id = 1234,
    // suboption 1, expected result "false"
    testVendorSuboption(Option::V6, 4491, 1, 1234, 1, TokenOption::EXISTS, "false");

    // Case 4: expression vendor[4491].option[1].exists, option with vendor-id = 4491,
    // suboption 2, expected result "false"
    testVendorSuboption(Option::V6, 4491, 1, 4491, 2, TokenOption::EXISTS, "false");

    // Case 5: expression vendor[4491].option[1].exists, option with vendor-id = 4491,
    // suboption 1, expected result "true"
    testVendorSuboption(Option::V6, 4491, 1, 4491, 1, TokenOption::EXISTS, "true");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_NO_OPTION", "Option with code 17 missing, pushing result 'false'",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result 'false'", pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result 'false'", pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 1 with value 'false'", pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 1 with value 'true'", pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test verifies if vendor[4491].option[1].hex expression properly returns
// value of said sub-option or empty string if desired option is not present.
// This test is for DHCPv4.
TEST_F(TokenTest, vendor4SuboptionHex) {
    // Case 1: no option present, should return empty string
    testVendorSuboption(Option::V4, 4491, 1, 0, 0, TokenOption::HEXADECIMAL, "");

    // Case 2: option with vendor-id = 1234, no suboptions, expected result ""
    testVendorSuboption(Option::V4, 4491, 1, 1234, 0, TokenOption::HEXADECIMAL, "");

    // Case 3: option with vendor-id = 1234, suboption 1, expected result ""
    testVendorSuboption(Option::V4, 4491, 1, 1234, 1, TokenOption::HEXADECIMAL, "");

    // Case 4: option with vendor-id = 4491, suboption 2, expected result ""
    testVendorSuboption(Option::V4, 4491, 1, 4491, 2, TokenOption::HEXADECIMAL, "");

    // Case 5: option with vendor-id = 4491, suboption 1, expected result content
    // of the option
    testVendorSuboption(Option::V4, 4491, 1, 4491, 1, TokenOption::HEXADECIMAL, "alpha");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_NO_OPTION", "Option with code 125 missing, pushing result ''",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result ''", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result ''", pkt4_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 1 with value 0x", pkt4_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 1 with value 0x616C706861", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test verifies if vendor[4491].option[1].hex expression properly returns
// value of said sub-option or empty string if desired option is not present.
// This test is for DHCPv4.
TEST_F(TokenTest, vendor6SuboptionHex) {
    // Case 1: no option present, should return empty string
    testVendorSuboption(Option::V6, 4491, 1, 0, 0, TokenOption::HEXADECIMAL, "");

    // Case 2: option with vendor-id = 1234, no suboptions, expected result ""
    testVendorSuboption(Option::V6, 4491, 1, 1234, 0, TokenOption::HEXADECIMAL, "");

    // Case 3: option with vendor-id = 1234, suboption 1, expected result ""
    testVendorSuboption(Option::V6, 4491, 1, 1234, 1, TokenOption::HEXADECIMAL, "");

    // Case 4: option with vendor-id = 4491, suboption 2, expected result ""
    testVendorSuboption(Option::V6, 4491, 1, 4491, 2, TokenOption::HEXADECIMAL, "");

    // Case 5: option with vendor-id = 4491, suboption 1, expected result content
    // of the option
    testVendorSuboption(Option::V6, 4491, 1, 4491, 1, TokenOption::HEXADECIMAL, "alpha");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_NO_OPTION", "Option with code 17 missing, pushing result ''",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result ''", pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result ''", pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 1 with value 0x", pkt6_->getLabel());
    addString("EVAL_DEBUG_OPTION", "Pushing option 1 with value 0x616C706861", pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test verifies that "vendor-class[4491].exists" expression can be used
// in DHCPv4.
TEST_F(TokenTest, vendorClass4SpecificVendorExists) {
    ASSERT_NO_THROW(t_.reset(new TokenVendorClass(Option::V4, 4491,
                                                  TokenVendor::ENTERPRISE_ID)));
    EXPECT_EQ(0, t_->getLabel());

    // Case 1: no option present, should fail
    testVendorClassExists(Option::V4, 4491, 0, "false");

    // Case 2: option exists, but has different vendor-id (1234), should fail
    testVendorClassExists(Option::V4, 4491, 1234, "false");

    // Case 3: option exists and has matching vendor-id, should succeed
    testVendorClassExists(Option::V4, 4491, 4491, "true");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_CLASS_NO_OPTION",
              "Option with code 124 missing, pushing result 'false'", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result 'false'", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_EXISTS",
              "Option with enterprise-id 4491 found, pushing result 'true'", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test verifies that "vendor-class[4491].exists" expression can be used
// in DHCPv6.
TEST_F(TokenTest, vendorClass6SpecificVendorExists) {
    // Case 1: no option present, should fail
    testVendorClassExists(Option::V6, 4491, 0, "false");

    // Case 2: option exists, but has different vendor-id (1234), should fail
    testVendorClassExists(Option::V6, 4491, 1234, "false");

    // Case 3: option exists and has matching vendor-id, should succeed
    testVendorClassExists(Option::V6, 4491, 4491, "true");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_CLASS_NO_OPTION",
              "Option with code 16 missing, pushing result 'false'", pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result 'false'", pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_EXISTS",
              "Option with enterprise-id 4491 found, pushing result 'true'", pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test verifies that "vendor-class[*].exists" can be used in DHCPv4
// and it matches a vendor class option with any vendor-id.
TEST_F(TokenTest, vendorClass4AnyVendorExists) {
    // Case 1: no option present, should fail
    testVendorClassExists(Option::V4, 0, 0, "false");

    // Case 2: option exists, should succeed, regardless of the vendor-id
    testVendorClassExists(Option::V4, 0, 1234, "true");

    // Case 3: option exists, should succeed, regardless of the vendor-id
    testVendorClassExists(Option::V4, 0, 4491, "true");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_CLASS_NO_OPTION",
              "Option with code 124 missing, pushing result 'false'", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_EXISTS",
              "Option with enterprise-id 1234 found, pushing result 'true'", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_EXISTS",
              "Option with enterprise-id 4491 found, pushing result 'true'", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test verifies that "vendor-class[*].exists" can be used in DHCPv6
// and it matches a vendor class option with any vendor-id.
TEST_F(TokenTest, vendorClass6AnyVendorExists) {
    // Case 1: no option present, should fail
    testVendorClassExists(Option::V6, 0, 0, "false");

    // Case 2: option exists, should succeed, regardless of the vendor-id
    testVendorClassExists(Option::V6, 0, 1234, "true");

    // Case 3: option exists, should succeed, regardless of the vendor-id
    testVendorClassExists(Option::V6, 0, 4491, "true");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_CLASS_NO_OPTION",
              "Option with code 16 missing, pushing result 'false'", pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_EXISTS",
              "Option with enterprise-id 1234 found, pushing result 'true'", pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_EXISTS",
              "Option with enterprise-id 4491 found, pushing result 'true'", pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Test if expression "vendor-class.enterprise" works properly for DHCPv4.
TEST_F(TokenTest, vendorClass4enterprise) {
    // Case 1: No option present, should return empty string
    testVendorClassEnterprise(Option::V4, 0, "");

    // Case 2: Option with vendor-id 1234, should return "1234"
    testVendorClassEnterprise(Option::V4, 1234, encode(1234));

    // Case 3: Option with vendor-id set to maximum value, should still
    // be able to handle it
    testVendorClassEnterprise(Option::V4, 4294967295, encode(4294967295));

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_CLASS_NO_OPTION",
              "Option with code 124 missing, pushing result ''", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID",
              "Pushing enterprise-id 1234 as result 0x000004D2", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID",
              "Pushing enterprise-id 4294967295 as result 0xFFFFFFFF", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Test if expression "vendor-class.enterprise" works properly for DHCPv6.
TEST_F(TokenTest, vendorClass6enterprise) {
    // Case 1: No option present, should return empty string
    testVendorClassEnterprise(Option::V6, 0, "");

    // Case 2: Option with vendor-id 1234, should return "1234"
    testVendorClassEnterprise(Option::V6, 1234, encode(1234));

    // Case 3: Option with vendor-id set to maximum value, should still
    // be able to handle it.
    testVendorClassEnterprise(Option::V6, 4294967295, encode(4294967295));

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_CLASS_NO_OPTION", "Option with code 16 missing, pushing result ''",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID",
              "Pushing enterprise-id 1234 as result 0x000004D2", pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID",
              "Pushing enterprise-id 4294967295 as result 0xFFFFFFFF", pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Test that expression "vendor-class[4491].data" is able to retrieve content
// of the first tuple of the vendor-class option in DHCPv4.
TEST_F(TokenTest, vendorClass4SpecificVendorData) {
    // Case 1: Expression looks for vendor-id 4491, data[0], there is no
    // vendor-class option at all, expected result is empty string.
    testVendorClassData(Option::V4, 4491, 0, 0, 0, "");

    // Case 2: Expression looks for vendor-id 4491, data[0], there is
    // vendor-class with vendor-id 1234 and no data, expected result is empty string.
    testVendorClassData(Option::V4, 4491, 0, 1234, 0, "");

    // Case 3: Expression looks for vendor-id 4491, data[0], there is
    // vendor-class with vendor-id 4491 and no data, expected result is empty string.
    // Note that vendor option in v4 always have at least one data chunk, even though
    // it may be empty. The OptionVendor code was told to not create any special
    // tuples, but it creates one empty on its own. So the code finds that one
    // tuple and extracts its content (an empty string).
    testVendorClassData(Option::V4, 4491, 0, 4491, 0, "");

    // Case 4: Expression looks for vendor-id 4491, data[0], there is
    // vendor-class with vendor-id 1234 and 1 data tuple, expected result is empty string
    testVendorClassData(Option::V4, 4491, 0, 1234, 1, "");

    // Case 5: Expression looks for vendor-id 4491, data[0], there is
    // vendor-class with vendor-id 4491 and 1 data tuple, expected result is
    // content of that data ("alpha")
    testVendorClassData(Option::V4, 4491, 0, 4491, 1, "alpha");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_CLASS_NO_OPTION",
              "Option with code 124 missing, pushing result ''", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result ''", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA",
              "Data 0 (out of 1 received) in vendor class found, pushing result ''",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result ''", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA",
              "Data 0 (out of 1 received) in vendor class found, pushing result 'alpha'",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Test that expression "vendor-class[4491].data" is able to retrieve content
// of the first tuple of the vendor-class option in DHCPv6.
TEST_F(TokenTest, vendorClass6SpecificVendorData) {
    // Case 1: Expression looks for vendor-id 4491, data[0], there is no
    // vendor-class option at all, expected result is empty string.
    testVendorClassData(Option::V6, 4491, 0, 0, 0, "");

    // Case 2: Expression looks for vendor-id 4491, data[0], there is
    // vendor-class with vendor-id 1234 and no data, expected result is empty string.
    testVendorClassData(Option::V6, 4491, 0, 1234, 0, "");

    // Case 3: Expression looks for vendor-id 4491, data[0], there is
    // vendor-class with vendor-id 4491 and no data, expected result is empty string
    testVendorClassData(Option::V6, 4491, 0, 4491, 0, "");

    // Case 4: Expression looks for vendor-id 4491, data[0], there is
    // vendor-class with vendor-id 1234 and 1 data tuple, expected result is empty string
    testVendorClassData(Option::V6, 4491, 0, 1234, 1, "");

    // Case 5: Expression looks for vendor-id 4491, data[0], there is
    // vendor-class with vendor-id 4491 and 1 data tuple, expected result is
    // content of that data ("alpha")
    testVendorClassData(Option::V6, 4491, 0, 4491, 1, "alpha");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_CLASS_NO_OPTION", "Option with code 16 missing, pushing result ''",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result ''", pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA_NOT_FOUND",
              "Requested data index 0, but option with enterprise-id 4491 has only 0 data "
              "tuple(s), pushing result ''",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result ''", pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA",
              "Data 0 (out of 1 received) in vendor class found, pushing result 'alpha'",
              pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Test that expression "vendor-class[*].data" is able to retrieve content
// of the first tuple of the vendor-class option in DHCPv4.
TEST_F(TokenTest, vendorClass4AnyVendorData) {
    // Case 1: Expression looks for any vendor-id (0), data[0], there is no
    // vendor-class option at all, expected result is empty string.
    testVendorClassData(Option::V4, 0, 0, 0, 0, "");

    // Case 2: Expression looks for any vendor-id (0), data[0], there is
    // vendor-class with vendor-id 1234 and no data (one empty tuple), expected
    // result is empty string.
    testVendorClassData(Option::V4, 0, 0, 1234, 0, "");

    // Case 3: Expression looks for any vendor-id (0), data[0], there is
    // vendor-class with vendor-id 4491 and no data (one empty tuple), expected
    // result is empty string.
    testVendorClassData(Option::V4, 0, 0, 4491, 0, "");

    // Case 4: Expression looks for any vendor-id (0), data[0], there is
    // vendor-class with vendor-id 1234 and 1 data tuple, expected result is
    // content of that data ("alpha")
    testVendorClassData(Option::V4, 0, 0, 1234, 1, "alpha");

    // Case 5: Expression looks for any vendor-id (0), data[0], there is
    // vendor-class with vendor-id 4491 and 1 data tuple, expected result is
    // content of that data ("alpha")
    testVendorClassData(Option::V4, 0, 0, 4491, 1, "alpha");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_CLASS_NO_OPTION",
              "Option with code 124 missing, pushing result ''", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA",
              "Data 0 (out of 1 received) in vendor class found, pushing result ''",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA",
              "Data 0 (out of 1 received) in vendor class found, pushing result ''",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA",
              "Data 0 (out of 1 received) in vendor class found, pushing result 'alpha'",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA",
              "Data 0 (out of 1 received) in vendor class found, pushing result 'alpha'",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Test that expression "vendor-class[*].data" is able to retrieve content
// of the first tuple of the vendor-class option in DHCPv6.
TEST_F(TokenTest, vendorClass6AnyVendorData) {
    // Case 1: Expression looks for any vendor-id (0), data[0], there is no
    // vendor-class option at all, expected result is empty string.
    testVendorClassData(Option::V6, 0, 0, 0, 0, "");

    // Case 2: Expression looks for any vendor-id (0), data[0], there is
    // vendor-class with vendor-id 1234 and no data, expected result is empty string.
    testVendorClassData(Option::V6, 0, 0, 1234, 0, "");

    // Case 3: Expression looks for any vendor-id (0), data[0], there is
    // vendor-class with vendor-id 4491 and no data, expected result is empty string
    testVendorClassData(Option::V6, 0, 0, 4491, 0, "");

    // Case 4: Expression looks for any vendor-id (0), data[0], there is
    // vendor-class with vendor-id 1234 and 1 data tuple, expected result is
    // content of that data ("alpha")
    testVendorClassData(Option::V6, 0, 0, 1234, 1, "alpha");

    // Case 5: Expression looks for any vendor-id (0), data[0], there is
    // vendor-class with vendor-id 4491 and 1 data tuple, expected result is
    // content of that data ("alpha")
    testVendorClassData(Option::V6, 0, 0, 4491, 1, "alpha");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_CLASS_NO_OPTION", "Option with code 16 missing, pushing result ''",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA_NOT_FOUND",
              "Requested data index 0, but option with enterprise-id 1234 has only 0 data "
              "tuple(s), pushing result ''",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA_NOT_FOUND",
              "Requested data index 0, but option with enterprise-id 4491 has only 0 data "
              "tuple(s), pushing result ''",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA",
              "Data 0 (out of 1 received) in vendor class found, pushing result 'alpha'",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA",
              "Data 0 (out of 1 received) in vendor class found, pushing result 'alpha'",
              pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test verifies if expression vendor-class[4491].data[3] is able to access
// the tuple specified by index. This is a DHCPv4 test.
TEST_F(TokenTest, vendorClass4DataIndex) {
    // Case 1: Expression looks for vendor-id 4491, data[3], there is no
    // vendor-class option at all, expected result is empty string.
    testVendorClassData(Option::V4, 4491, 3, 0, 0, "");

    // Case 2: Expression looks for vendor-id 4491, data[3], there is
    // vendor-class with vendor-id 1234 and no data, expected result is empty string.
    testVendorClassData(Option::V4, 4491, 3, 1234, 0, "");

    // Case 3: Expression looks for vendor-id 4491, data[3], there is
    // vendor-class with vendor-id 4491 and no data, expected result is empty string
    testVendorClassData(Option::V4, 4491, 3, 4491, 0, "");

    // Case 4: Expression looks for vendor-id 4491, data[3], there is
    // vendor-class with vendor-id 1234 and 1 data tuple, expected result is empty string.
    testVendorClassData(Option::V4, 4491, 3, 1234, 1, "");

    // Case 5: Expression looks for vendor-id 4491, data[3], there is
    // vendor-class with vendor-id 4491, but has only 3 data tuples, expected
    // result is empty string.
    testVendorClassData(Option::V4, 4491, 3, 4491, 3, "");

    // Case 6: Expression looks for vendor-id 4491, data[3], there is
    // vendor-class with vendor-id 4491 and 5 data tuples, expected result is
    // content of that tuple ("gamma")
    testVendorClassData(Option::V4, 4491, 3, 4491, 5, "gamma");

    // Case 6: Expression looks for vendor-id 4491, data[3], there is
    // vendor-class with vendor-id 1234 and 5 data tuples, expected result is
    // empty string, because vendor-id does not match.
    testVendorClassData(Option::V4, 4491, 3, 1234, 5, "");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_CLASS_NO_OPTION",
              "Option with code 124 missing, pushing result ''", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result ''", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA_NOT_FOUND",
              "Requested data index 3, but option with enterprise-id 4491 has only 1 data "
              "tuple(s), pushing result ''",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result ''", pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA_NOT_FOUND",
              "Requested data index 3, but option with enterprise-id 4491 has only 3 data "
              "tuple(s), pushing result ''",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA",
              "Data 3 (out of 5 received) in vendor class found, pushing result 'gamma'",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result ''", pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test verifies if expression vendor-class[4491].data[3] is able to access
// the tuple specified by index. This is a DHCPv6 test.
TEST_F(TokenTest, vendorClass6DataIndex) {
    // Case 1: Expression looks for vendor-id 4491, data[3], there is no
    // vendor-class option at all, expected result is empty string.
    testVendorClassData(Option::V6, 4491, 3, 0, 0, "");

    // Case 2: Expression looks for vendor-id 4491, data[3], there is
    // vendor-class with vendor-id 1234 and no data, expected result is empty string.
    testVendorClassData(Option::V6, 4491, 3, 1234, 0, "");

    // Case 3: Expression looks for vendor-id 4491, data[3], there is
    // vendor-class with vendor-id 4491 and no data, expected result is empty string
    testVendorClassData(Option::V6, 4491, 3, 4491, 0, "");

    // Case 4: Expression looks for vendor-id 4491, data[3], there is
    // vendor-class with vendor-id 1234 and 5 data tuples, expected result is empty string.
    testVendorClassData(Option::V6, 4491, 3, 1234, 5, "");

    // Case 5: Expression looks for vendor-id 4491, data[3], there is
    // vendor-class with vendor-id 4491, but has only 3 data tuples, expected
    // result is empty string.
    testVendorClassData(Option::V6, 4491, 3, 4491, 3, "");

    // Case 6: Expression looks for vendor-id 4491, data[3], there is
    // vendor-class with vendor-id 4491 and 5 data tuples, expected result is
    // content of that tuple ("gamma")
    testVendorClassData(Option::V6, 4491, 3, 4491, 5, "gamma");

    // Check if the logged messages are correct.
    addString("EVAL_DEBUG_VENDOR_CLASS_NO_OPTION", "Option with code 16 missing, pushing result ''",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result ''", pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA_NOT_FOUND",
              "Requested data index 3, but option with enterprise-id 4491 has only 0 data "
              "tuple(s), pushing result ''",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH",
              "Was looking for 4491, option had 1234, pushing result ''", pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA_NOT_FOUND",
              "Requested data index 3, but option with enterprise-id 4491 has only 3 data "
              "tuple(s), pushing result ''",
              pkt6_->getLabel());
    addString("EVAL_DEBUG_VENDOR_CLASS_DATA",
              "Data 3 (out of 5 received) in vendor class found, pushing result 'gamma'",
              pkt6_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks that the existing RAI -sunoption can be found.
TEST_F(TokenTest, subOption) {

    // Insert relay option with sub-options 1 and 13
    insertRelay4Option();

    // Creating the token should be safe.
    ASSERT_NO_THROW(t_.reset(new TokenSubOption(DHO_DHCP_AGENT_OPTIONS, 13, TokenOption::TEXTUAL)));
    EXPECT_EQ(0, t_->getLabel());

    // We should be able to evaluate it.
    testEvaluate(t_, *pkt4_, values_);

    // we should have one value on the stack
    ASSERT_EQ(1, values_.size());

    // The option should be found and option[82].option[13] should evaluate
    // to thecontent of that sub-option, i.e. "thirteen"
    EXPECT_EQ("thirteen", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_SUB_OPTION", "Pushing option 82 sub-option 13 with value 'thirteen'",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks that the code properly handles cases when
// there is a RAI option, but there's no requested sub-option.
TEST_F(TokenTest, subOptionNoSubOption) {

    // Insert relay option with sub-options 1 and 13
    insertRelay4Option();


    // Creating the token should be safe.
    ASSERT_NO_THROW(t_.reset(new TokenSubOption(DHO_DHCP_AGENT_OPTIONS, 15, TokenOption::TEXTUAL)));

    // We should be able to evaluate it.
    testEvaluate(t_, *pkt4_, values_);

    // we should have one value on the stack
    ASSERT_EQ(1, values_.size());

    // The option should NOT be found (there is no sub-option 15),
    // so the expression should evaluate to ""
    EXPECT_EQ("", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_SUB_OPTION", "Pushing option 82 sub-option 15 with value ''",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks that the code properly handles cases when
// there's no RAI option at all.
TEST_F(TokenTest, subOptionNoOption) {

    // We didn't call insertRelay4Option(), so there's no RAI option.

    // Creating the token should be safe.
    ASSERT_NO_THROW(t_.reset(new TokenSubOption(DHO_DHCP_AGENT_OPTIONS, 13, TokenOption::TEXTUAL)));

    // We should be able to evaluate it.
    testEvaluate(t_, *pkt4_, values_);

    // we should have one value on the stack
    ASSERT_EQ(1, values_.size());

    // The option should NOT be found (there is no option 82),
    // so the expression should evaluate to ""
    EXPECT_EQ("", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_SUB_OPTION_NO_OPTION",
              "Requested option 82 sub-option 13, but the parent option is not present, pushing "
              "result ''",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// This test checks that only the requested parent is searched for
// the requested sub-option.
TEST_F(TokenTest, subOptionOptionOnly) {

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
    ASSERT_NO_THROW(t_.reset(new TokenSubOption(DHO_DHCP_AGENT_OPTIONS, 13, TokenOption::TEXTUAL)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("thirteen", values_.top());

    // Try to get option 1. It should get the one from RAI
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenSubOption(DHO_DHCP_AGENT_OPTIONS, 1, TokenOption::TEXTUAL)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("one", values_.top());

    // Try to get option 70. It should fail, as there's no such
    // sub option in RAI.
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenSubOption(DHO_DHCP_AGENT_OPTIONS, 70, TokenOption::TEXTUAL)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("", values_.top());

    // Try to check option 1. It should return "true"
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenSubOption(DHO_DHCP_AGENT_OPTIONS, 1, TokenOption::EXISTS)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("true", values_.top());

    // Try to check option 70. It should return "false"
    clearStack();
    ASSERT_NO_THROW(t_.reset(new TokenSubOption(DHO_DHCP_AGENT_OPTIONS, 70, TokenOption::EXISTS)));
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_EQ(1, values_.size());
    EXPECT_EQ("false", values_.top());

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_SUB_OPTION", "Pushing option 82 sub-option 13 with value 'thirteen'",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUB_OPTION", "Pushing option 82 sub-option 1 with value 'one'",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUB_OPTION", "Pushing option 82 sub-option 70 with value ''",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUB_OPTION", "Pushing option 82 sub-option 1 with value 'true'",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SUB_OPTION", "Pushing option 82 sub-option 70 with value 'false'",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Checks if various values can be represented as integer tokens
TEST_F(TokenTest, integer) {
    ASSERT_NO_THROW(t_.reset(new TokenInteger(0)));
    EXPECT_EQ(0, t_->getLabel());

    testInteger(encode(0), 0);
    testInteger(encode(6), 6);
    testInteger(encode(255), 255);
    testInteger(encode(256), 256);
    testInteger(encode(1410), 1410);
    testInteger(encode(4294967295), 4294967295);
}

// Verify TokenSplit::eval, single delimiter.
TEST_F(TokenTest, split) {
    ASSERT_NO_THROW(t_.reset(new TokenSplit()));
    EXPECT_EQ(0, t_->getLabel());

    // Get the whole string
    std::string input(".two.three..five.");
    std::string delims(".");

    // Empty input string should yield empty result.
    verifySplitEval("", delims, "1", "");

    // Empty delimiters string should yield original string result.
    verifySplitEval(input, "", "1", input);

    // Field number less than one should yield empty result.
    verifySplitEval(input, delims, "0", "");

    // Now get each field in succession.
    verifySplitEval(input, delims, "1", "");
    verifySplitEval(input, delims, "2", "two");
    verifySplitEval(input, delims, "3", "three");
    verifySplitEval(input, delims, "4", "");
    verifySplitEval(input, delims, "5", "five");
    verifySplitEval(input, delims, "6", "");

    // Too large of a field should yield empty result.
    verifySplitEval(input, delims, "7", "");

    // A string without delimiters returns as field 1.
    verifySplitEval("just_one", delims, "1", "just_one");

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison
    addString("EVAL_DEBUG_SPLIT_EMPTY", "Popping field 1, delimiters ., string , pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT_DELIM_EMPTY",
              "Popping field 1, delimiters , string .two.three..five., pushing result "
              "0x2E74776F2E74687265652E2E666976652E",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT_FIELD_OUT_OF_RANGE",
              "Popping field 0, delimiters ., string .two.three..five., pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT",
              "Popping field 1, delimiters ., string .two.three..five., pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT",
              "Popping field 2, delimiters ., string .two.three..five., pushing result 0x74776F",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT",
              "Popping field 3, delimiters ., string .two.three..five., pushing result "
              "0x7468726565",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT",
              "Popping field 4, delimiters ., string .two.three..five., pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT",
              "Popping field 5, delimiters ., string .two.three..five., pushing result 0x66697665",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT",
              "Popping field 6, delimiters ., string .two.three..five., pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT_FIELD_OUT_OF_RANGE",
              "Popping field 7, delimiters ., string .two.three..five., pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT",
              "Popping field 1, delimiters ., string just_one, pushing result 0x6A7573745F6F6E65",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Verify TokenSplit::eval with more than one delimiter.
TEST_F(TokenTest, splitMultipleDelims) {
    // Get the whole string
    std::string input(".two:three.:five.");
    std::string delims(".:");

    // Empty input string should yield empty result.
    verifySplitEval("", delims, "1", "");

    // Too small of a field should yield empty result.
    verifySplitEval(input, delims, "0", "");

    // Now get each field in succession.
    verifySplitEval(input, delims, "1", "");
    verifySplitEval(input, delims, "2", "two");
    verifySplitEval(input, delims, "3", "three");
    verifySplitEval(input, delims, "4", "");
    verifySplitEval(input, delims, "5", "five");
    verifySplitEval(input, delims, "6", "");

    // Too large of a field should yield empty result.
    verifySplitEval(input, delims, "7", "");

    // A string without delimiters returns as field 1.
    verifySplitEval("just_one", delims, "1", "just_one");

    // Check that the debug output was correct.  Add the strings
    // to the test vector in the class and then call checkFile
    // for comparison

    addString("EVAL_DEBUG_SPLIT_EMPTY",
              "Popping field 1, delimiters .:, string , pushing result 0x", pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT_FIELD_OUT_OF_RANGE",
              "Popping field 0, delimiters .:, string .two:three.:five., pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT",
              "Popping field 1, delimiters .:, string .two:three.:five., pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT",
              "Popping field 2, delimiters .:, string .two:three.:five., pushing result 0x74776F",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT",
              "Popping field 3, delimiters .:, string .two:three.:five., pushing result "
              "0x7468726565",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT",
              "Popping field 4, delimiters .:, string .two:three.:five., pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT",
              "Popping field 5, delimiters .:, string .two:three.:five., pushing result 0x66697665",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT",
              "Popping field 6, delimiters .:, string .two:three.:five., pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT_FIELD_OUT_OF_RANGE",
              "Popping field 7, delimiters .:, string .two:three.:five., pushing result 0x",
              pkt4_->getLabel());
    addString("EVAL_DEBUG_SPLIT",
              "Popping field 1, delimiters .:, string just_one, pushing result 0x6A7573745F6F6E65",
              pkt4_->getLabel());
    EXPECT_TRUE(checkFile());
}

// Verify TokenMatch raises an error on invalid regular expression.
TEST_F(TokenTest, invalidRegEx) {
    try {
        TokenMatch t("[bad");
        ADD_FAILURE() << "expected exception, got none";
    } catch (const EvalParseError& ex) {
        string msg(ex.what());
        string expected = "invalid regular expression '[bad': ";
        EXPECT_EQ(expected, msg.substr(0, expected.size()))
            << "expected to start with " << expected
            << "\nbut got: " << msg;
    } catch (const exception& ex) {
        ADD_FAILURE() << "unexpected expection: " << ex.what();
    }
}

// Verify TokenMatch works as expected.
TEST_F(TokenTest, match) {
    ASSERT_NO_THROW(t_.reset(new TokenMatch("foo")));
    EXPECT_EQ(0, t_->getLabel());

    testMatch("foo", "foo", true);
    // Full match is required.
    testMatch("foo", "foobar", false);
    testMatch("^foo", "foo", true);
    testMatch("foo$", "foo", true);
    testMatch("^foo$", "foo", true);
    testMatch("foo.*", "foo", true);
    testMatch("foo.*", "foobar", true);
    // Case sensitive.
    testMatch("foo", "Foo", false);
    testMatch("Foo", "foo", false);
    // Contain is a subcase.
    testMatch(".*foo.*", "foo", true);
    testMatch(".*foo.*", "foobar", true);
    testMatch(".*foo.*", "barfoo", true);
    testMatch(".*foo.*", "foofoofoo", true);
    // Character range.
    testMatch("[fo]{3}", "foo", true);
    testMatch("[abfor]{6}", "foobar", true);
    testMatch("[abfo]{6}", "foobar", false);
    testMatch("[^xyz]+", "foobar", true);
    // Group.
    testMatch("f(.)\\1bar", "foobar", true);
    // Classes.
    testMatch("[[:alpha:]]{1,9}", "Foobar", true);
    testMatch("[[:alpha:]]{1,9}", "FoObar", true);
    testMatch("[[:alpha:]]{1,9}", "Fo0bar", false);
}

// Verify TokenLabel.
TEST_F(TokenTest, label) {
    // 0 is not a valid label.
    ASSERT_THROW(t_.reset(new TokenLabel(0)), EvalParseError);

    // Evaluation does and uses nothing.
    ASSERT_NO_THROW(t_.reset(new TokenLabel(123)));
    EXPECT_EQ(123, t_->getLabel());
    testEvaluate(t_, *pkt4_, values_);
    ASSERT_TRUE(values_.empty());
}

// Verify TokenBranch.
TEST_F(TokenTest, branch) {
    // 0 is not a valid branch.
    ASSERT_THROW(t_.reset(new TokenBranch(0)), EvalParseError);

    // Evaluation does and uses nothing.
    ASSERT_NO_THROW(t_.reset(new TokenBranch(123)));
    EXPECT_EQ(0, t_->getLabel());
    unsigned next(0);
    ASSERT_NO_THROW(next = t_->evaluate(*pkt4_, values_));
    EXPECT_EQ(123, next);
    ASSERT_TRUE(values_.empty());
}

// Verify TokenPopOrBranchTrue.
TEST_F(TokenTest, popOrBranchTrue) {
    // 0 is not a valid branch.
    ASSERT_THROW(t_.reset(new TokenPopOrBranchTrue(0)), EvalParseError);

    ASSERT_NO_THROW(t_.reset(new TokenPopOrBranchTrue(123)));
    EXPECT_EQ(0, t_->getLabel());

    // CASE 1: The stack is empty.
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    // CASE 2: The top value is not a boolen.
    values_.push("foo");
    EXPECT_THROW(t_->evaluate(*pkt6_, values_), EvalTypeError);

    // CASE 3: The top value is true.
    clearStack(false);
    values_.push("true");
    ASSERT_EQ(1, values_.size());
    unsigned next(0);
    ASSERT_NO_THROW(next = t_->evaluate(*pkt4_, values_));
    EXPECT_EQ(123, next);
    ASSERT_EQ(1, values_.size());
    string result = values_.top();
    EXPECT_EQ("true", result);

    // CASE 4: The top value is false.
    clearStack(false);
    values_.push("false");
    ASSERT_EQ(1, values_.size());
    testEvaluate(t_, *pkt6_, values_);
    EXPECT_TRUE(values_.empty());
}

// Verify TokenPopOrBranchFalse.
TEST_F(TokenTest, popOrBranchFalse) {
    // 0 is not a valid branch.
    ASSERT_THROW(t_.reset(new TokenPopOrBranchFalse(0)), EvalParseError);

    ASSERT_NO_THROW(t_.reset(new TokenPopOrBranchFalse(123)));
    EXPECT_EQ(0, t_->getLabel());

    // CASE 1: The stack is empty.
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    // CASE 2: The top value is not a boolen.
    values_.push("foo");
    EXPECT_THROW(t_->evaluate(*pkt6_, values_), EvalTypeError);

    // CASE 3: The top value is true.
    clearStack(false);
    values_.push("true");
    ASSERT_EQ(1, values_.size());
    testEvaluate(t_, *pkt6_, values_);
    EXPECT_TRUE(values_.empty());

    // CASE 4: The top value is false.
    clearStack(false);
    values_.push("false");
    ASSERT_EQ(1, values_.size());
    unsigned next(0);
    ASSERT_NO_THROW(next = t_->evaluate(*pkt4_, values_));
    EXPECT_EQ(123, next);
    ASSERT_EQ(1, values_.size());
    string result = values_.top();
    EXPECT_EQ("false", result);
}

// Verify TokenPopAndBranchFalse.
TEST_F(TokenTest, popAndBranchFalse) {
    // 0 is not a valid branch.
    ASSERT_THROW(t_.reset(new TokenPopAndBranchFalse(0)), EvalParseError);

    ASSERT_NO_THROW(t_.reset(new TokenPopAndBranchFalse(123)));
    EXPECT_EQ(0, t_->getLabel());

    // CASE 1: The stack is empty.
    EXPECT_THROW(t_->evaluate(*pkt4_, values_), EvalBadStack);

    // CASE 2: The top value is not a boolen.
    values_.push("foo");
    EXPECT_THROW(t_->evaluate(*pkt6_, values_), EvalTypeError);

    // CASE 3: The top value is true.
    clearStack(false);
    values_.push("true");
    ASSERT_EQ(1, values_.size());
    testEvaluate(t_, *pkt6_, values_);
    EXPECT_TRUE(values_.empty());

    // CASE 4: The top value is false.
    clearStack(false);
    values_.push("false");
    ASSERT_EQ(1, values_.size());
    unsigned next(0);
    ASSERT_NO_THROW(next = t_->evaluate(*pkt4_, values_));
    EXPECT_EQ(123, next);
    EXPECT_TRUE(values_.empty());
}

}
