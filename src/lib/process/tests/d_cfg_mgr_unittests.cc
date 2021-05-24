// Copyright (C) 2013-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <exceptions/exceptions.h>
#include <process/testutils/d_test_stubs.h>
#include <process/d_cfg_mgr.h>
#include <process/redact_config.h>

#include <boost/foreach.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::config;
using namespace isc::process;
using namespace isc::data;
using namespace boost::posix_time;

namespace {

/// @brief Test Class for verifying that configuration context cannot be null
/// during construction.
class DCtorTestCfgMgr : public DCfgMgrBase {
public:
    /// @brief Constructor - Note that is passes in an empty configuration
    /// pointer to the base class constructor.
    DCtorTestCfgMgr() : DCfgMgrBase(ConfigPtr()) {
    }

    /// @brief Destructor
    virtual ~DCtorTestCfgMgr() {
    }

    /// @brief Dummy implementation as this method is abstract.
    virtual ConfigPtr createNewContext() {
        return (ConfigPtr());
    }

    /// @brief Returns summary of configuration in the textual format.
    virtual std::string getConfigSummary(const uint32_t) {
        return ("");
    }
};

/// @brief Test fixture class for testing DCfgMgrBase class.
/// It maintains an member instance of DStubCfgMgr and derives from
/// ConfigParseTest fixture, thus providing methods for converting JSON
/// strings to configuration element sets, checking parse results,
/// accessing the configuration context and trying to unparse.
class DStubCfgMgrTest : public ConfigParseTest {
public:

    /// @brief Constructor
    DStubCfgMgrTest():cfg_mgr_(new DStubCfgMgr) {
    }

    /// @brief Destructor
    ~DStubCfgMgrTest() {
    }

    /// @brief Convenience method which returns a DStubContextPtr to the
    /// configuration context.
    ///
    /// @return returns a DStubContextPtr.
    DStubContextPtr getStubContext() {
        return (boost::dynamic_pointer_cast<DStubContext>
                (cfg_mgr_->getContext()));
    }

    /// @brief Configuration manager instance.
    DStubCfgMgrPtr cfg_mgr_;
};

///@brief Tests basic construction/destruction of configuration manager.
/// Verifies that:
/// 1. Proper construction succeeds.
/// 2. Configuration context is initialized by construction.
/// 3. Destruction works properly.
/// 4. Construction with a null context is not allowed.
TEST(DCfgMgrBase, construction) {
    DCfgMgrBasePtr cfg_mgr;

    // Verify that configuration manager constructions without error.
    ASSERT_NO_THROW(cfg_mgr.reset(new DStubCfgMgr()));

    // Verify that the context can be retrieved and is not null.
    ConfigPtr context = cfg_mgr->getContext();
    EXPECT_TRUE(context);

    // Verify that the manager can be destructed without error.
    EXPECT_NO_THROW(cfg_mgr.reset());

    // Verify that an attempt to construct a manger with a null context fails.
    ASSERT_THROW(DCtorTestCfgMgr(), DCfgMgrBaseError);
}

///@brief Tests fundamental aspects of configuration parsing.
/// Verifies that:
/// 1. A correctly formed simple configuration parses without error.
/// 2. An error building the element is handled.
/// 3. An error committing the element is handled.
/// 4. An unknown element error is handled.
TEST_F(DStubCfgMgrTest, basicParseTest) {
    // Create a simple configuration.
    string config = "{ \"test-value\": [] } ";
    ASSERT_TRUE(fromJSON(config));

    // Verify that we can parse a simple configuration.
    answer_ = cfg_mgr_->simpleParseConfig(config_set_, false);
    EXPECT_TRUE(checkAnswer(0));

    // Verify that we can check a simple configuration.
    answer_ = cfg_mgr_->simpleParseConfig(config_set_, true);
    EXPECT_TRUE(checkAnswer(0));
}

/// @brief Tests that element ids supported by the base class as well as those
/// added by the derived class function properly.
/// This test verifies that:
/// 1. Boolean parameters can be parsed and retrieved.
/// 2. Uint32 parameters can be parsed and retrieved.
/// 3. String parameters can be parsed and retrieved.
/// 4. Map elements can be parsed and retrieved.
/// 5. List elements can be parsed and retrieved.
/// 6. Parsing a second configuration, updates the existing context values
/// correctly.
TEST_F(DStubCfgMgrTest, simpleTypesTest) {
    // Create a configuration with all of the parameters.
    string config = "{ \"bool_test\": true , "
                    "  \"uint32_test\": 77 , "
                    "  \"string_test\": \"hmmm chewy\" , "
                    "  \"map_test\" : {} , "
                    "  \"list_test\": [] }";
    ASSERT_TRUE(fromJSON(config));

    // Verify that the configuration parses without error.
    answer_ = cfg_mgr_->simpleParseConfig(config_set_, false);
    ASSERT_TRUE(checkAnswer(0));
    DStubContextPtr context = getStubContext();
    ASSERT_TRUE(context);

    // Create a configuration which "updates" all of the parameter values.
    string config2 = "{ \"bool_test\": false , "
                    "  \"uint32_test\": 88 , "
                    "  \"string_test\": \"ewww yuk!\" , "
                    "  \"map_test2\" : {} , "
                    "  \"list_test2\": [] }";
    ASSERT_TRUE(fromJSON(config2));

    // Verify that the configuration parses without error.
    answer_ = cfg_mgr_->simpleParseConfig(config_set_, false);
    EXPECT_TRUE(checkAnswer(0));
    context = getStubContext();
    ASSERT_TRUE(context);
}

/// @brief Tests that the configuration context is preserved after failure
/// during parsing causes a rollback.
/// 1. Verifies configuration context rollback.
TEST_F(DStubCfgMgrTest, rollBackTest) {
    // Create a configuration with all of the parameters.
    string config = "{ \"bool_test\": true , "
                    "  \"uint32_test\": 77 , "
                    "  \"string_test\": \"hmmm chewy\" , "
                    "  \"map_test\" : {} , "
                    "  \"list_test\": [] }";
    ASSERT_TRUE(fromJSON(config));

    // Verify that the configuration parses without error.
    answer_ = cfg_mgr_->simpleParseConfig(config_set_, false);
    EXPECT_TRUE(checkAnswer(0));
    DStubContextPtr context = getStubContext();
    ASSERT_TRUE(context);

    // Create a configuration which "updates" all of the parameter values
    // plus one unknown at the end.
    string config2 = "{ \"bool_test\": false , "
                    "  \"uint32_test\": 88 , "
                    "  \"string_test\": \"ewww yuk!\" , "
                    "  \"map_test2\" : {} , "
                    "  \"list_test2\": [] , "
                    "  \"zeta_unknown\": 33 } ";
    ASSERT_TRUE(fromJSON(config2));
}

/// @brief Tests that the configuration context is preserved during
/// check only  parsing.
TEST_F(DStubCfgMgrTest, checkOnly) {
    // Create a configuration with all of the parameters.
    string config = "{ \"bool_test\": true , "
                    "  \"uint32_test\": 77 , "
                    "  \"string_test\": \"hmmm chewy\" , "
                    "  \"map_test\" : {} , "
                    "  \"list_test\": [] }";
    ASSERT_TRUE(fromJSON(config));

    // Verify that the configuration parses without error.
    answer_ = cfg_mgr_->simpleParseConfig(config_set_, false);
    EXPECT_TRUE(checkAnswer(0));
    DStubContextPtr context = getStubContext();
    ASSERT_TRUE(context);


    // Create a configuration which "updates" all of the parameter values.
    string config2 = "{ \"bool_test\": false , "
                    "  \"uint32_test\": 88 , "
                    "  \"string_test\": \"ewww yuk!\" , "
                    "  \"map_test2\" : {} , "
                    "  \"list_test2\": [] }";
    ASSERT_TRUE(fromJSON(config2));

    answer_ = cfg_mgr_->simpleParseConfig(config_set_, true);
    EXPECT_TRUE(checkAnswer(0));
    context = getStubContext();
    ASSERT_TRUE(context);

}

// Tests that configuration element position is returned by getParam variants.
TEST_F(DStubCfgMgrTest, paramPosition) {
    // Create a configuration with one of each scalar types.  We end them
    // with line feeds so we can test position value.
    string config = "{ \"bool_test\": true , \n"
                    "  \"uint32_test\": 77 , \n"
                    "  \"string_test\": \"hmmm chewy\" }";
    ASSERT_TRUE(fromJSON(config));

    // Verify that the configuration parses without error.
    answer_ = cfg_mgr_->simpleParseConfig(config_set_, false);
    ASSERT_TRUE(checkAnswer(0));
    DStubContextPtr context = getStubContext();
    ASSERT_TRUE(context);

}

// This tests if some aspects of simpleParseConfig are behaving properly.
// Thorough testing is only possible for specific implementations. This
// is done for control agent (see CtrlAgentControllerTest tests in
// src/bin/agent/tests/ctrl_agent_controller_unittest.cc for example).
// Also, shell tests in src/bin/agent/ctrl_agent_process_tests.sh test
// the whole CA process that uses simpleParseConfig. The alternative
// would be to implement whole parser that would set the context
// properly. The ROI for this is not worth the effort.
TEST_F(DStubCfgMgrTest, simpleParseConfig) {
    using namespace isc::data;

    // Passing just null pointer should result in error return code
    answer_ = cfg_mgr_->simpleParseConfig(ConstElementPtr(), false);
    EXPECT_TRUE(checkAnswer(1));

    // Ok, now try with a dummy, but valid json code
    string config = "{ \"bool_test\": true , \n"
                    "  \"uint32_test\": 77 , \n"
                    "  \"string_test\": \"hmmm chewy\" }";
    ASSERT_NO_THROW(fromJSON(config));

    answer_ = cfg_mgr_->simpleParseConfig(config_set_, false);
    EXPECT_TRUE(checkAnswer(0));
}

// This test checks that the post configuration callback function is
// executed by the simpleParseConfig function.
TEST_F(DStubCfgMgrTest, simpleParseConfigWithCallback) {
    string config = "{ \"bool_test\": true , \n"
                    "  \"uint32_test\": 77 , \n"
                    "  \"string_test\": \"hmmm chewy\" }";
    ASSERT_NO_THROW(fromJSON(config));

    answer_ = cfg_mgr_->simpleParseConfig(config_set_, false,
                                          []() {
        isc_throw(Unexpected, "unexpected configuration error");
    });
    EXPECT_TRUE(checkAnswer(1));
}

// This test checks that redactConfig works as expected.
TEST_F(DStubCfgMgrTest, redactConfig) {
    // Basic case.
    string config = "{ \"foo\": 1 }";
    ConstElementPtr elem;
    ASSERT_NO_THROW(elem = Element::fromJSON(config));
    ConstElementPtr ret;
    ASSERT_NO_THROW(ret = redactConfig(elem));
    EXPECT_EQ(ret->str(), elem->str());

    // Verify redaction.
    config = "{ \"password\": \"foo\", \"secret\": \"bar\" }";
    ASSERT_NO_THROW(elem = Element::fromJSON(config));
    ASSERT_NO_THROW(ret = redactConfig(elem));
    string expected = "{ \"password\": \"*****\", \"secret\": \"*****\" }";
    EXPECT_EQ(expected, ret->str());

    // Verify that user context are skipped.
    config = "{ \"user-context\": { \"password\": \"foo\" } }";
    ASSERT_NO_THROW(elem = Element::fromJSON(config));
    ASSERT_NO_THROW(ret = redactConfig(elem));
    EXPECT_EQ(ret->str(), elem->str());

    // Verify that only given subtrees are handled.
    list<string> keys = { "foo" };
    config = "{ \"foo\": { \"password\": \"foo\" }, ";
    config += "\"next\": { \"secret\": \"bar\" } }";
    ASSERT_NO_THROW(elem = Element::fromJSON(config));
    ASSERT_NO_THROW(ret = redactConfig(elem, keys));
    expected = "{ \"foo\": { \"password\": \"*****\" }, ";
    expected += "\"next\": { \"secret\": \"bar\" } }";
    EXPECT_EQ(expected, ret->str());
}

// Test that user context is not touched when configuration is redacted.
TEST(RedactConfig, userContext) {
    ConstElementPtr const config(Element::fromJSON(R"(
        {
            "some-database": {
                "password": "sensitive",
                "secret": "sensitive",
                "user": "keatest",
                "nested-map": {
                    "password": "sensitive",
                    "secret": "sensitive",
                    "user": "keatest"
                }
            },
            "user-context": {
                "password": "keatest",
                "secret": "keatest",
                "user": "keatest",
                "nested-map": {
                    "password": "keatest",
                    "secret": "keatest",
                    "user": "keatest"
                }
            }
        }
    )"));
    ConstElementPtr const expected(Element::fromJSON(R"(
        {
            "some-database": {
                "password": "*****",
                "secret": "*****",
                "user": "keatest",
                "nested-map": {
                    "password": "*****",
                    "secret": "*****",
                    "user": "keatest"
                }
            },
            "user-context": {
                "password": "keatest",
                "secret": "keatest",
                "user": "keatest",
                "nested-map": {
                    "password": "keatest",
                    "secret": "keatest",
                    "user": "keatest"
                }
            }
        }
    )"));
    ConstElementPtr redacted(redactConfig(config));
    EXPECT_TRUE(isEquivalent(redacted, expected))
        << "Actual:\n" << prettyPrint(redacted) << "\n"
           "Expected:\n" << prettyPrint(expected);
}

} // end of anonymous namespace
