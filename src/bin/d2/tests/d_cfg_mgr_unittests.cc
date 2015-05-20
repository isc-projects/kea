// Copyright (C) 2013, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <config/command_interpreter.h>
#include <config/module_spec.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <d2/d_cfg_mgr.h>
#include <d_test_stubs.h>

#include <boost/foreach.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::config;
using namespace isc::d2;
using namespace boost::posix_time;

namespace {

/// @brief Test Class for verifying that configuration context cannot be null
/// during construction.
class DCtorTestCfgMgr : public DCfgMgrBase {
public:
    /// @brief Constructor - Note that is passes in an empty configuration
    /// pointer to the base class constructor.
    DCtorTestCfgMgr() : DCfgMgrBase(DCfgContextBasePtr()) {
    }

    /// @brief Destructor
    virtual ~DCtorTestCfgMgr() {
    }

    /// @brief Dummy implementation as this method is abstract.
    virtual DCfgContextBasePtr createNewContext() {
        return (DCfgContextBasePtr());
    }

    /// @brief Dummy implementation as this method is abstract.
    virtual isc::dhcp::ParserPtr
    createConfigParser(const std::string& /* element_id */,
                       const isc::data::Element::Position& /* pos */) {
        return (isc::dhcp::ParserPtr());
    }

    /// @brief Returns summary of configuration in the textual format.
    virtual std::string getConfigSummary(const uint32_t) {
        return ("");
    }
};

/// @brief Test fixture class for testing DCfgMgrBase class.
/// It maintains an member instance of DStubCfgMgr and derives from
/// ConfigParseTest fixture, thus providing methods for converting JSON
/// strings to configuration element sets, checking parse results, and
/// accessing the configuration context.
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
    DCfgContextBasePtr context = cfg_mgr->getContext();
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
    answer_ = cfg_mgr_->parseConfig(config_set_);
    EXPECT_TRUE(checkAnswer(0));

    // Verify that an error building the element is caught and returns a
    // failed parse result.
    SimFailure::set(SimFailure::ftElementBuild);
    answer_ = cfg_mgr_->parseConfig(config_set_);
    EXPECT_TRUE(checkAnswer(1));

    // Verify that an error committing the element is caught and returns a
    // failed parse result.
    SimFailure::set(SimFailure::ftElementCommit);
    answer_ = cfg_mgr_->parseConfig(config_set_);
    EXPECT_TRUE(checkAnswer(1));

    // Verify that an unknown element error is caught and returns a failed
    // parse result.
    SimFailure::set(SimFailure::ftElementUnknown);
    answer_ = cfg_mgr_->parseConfig(config_set_);
    EXPECT_TRUE(checkAnswer(1));
}

///@brief Tests ordered and non-ordered element parsing
/// This test verifies that:
/// 1. Non-ordered parsing parses elements in the order they are presented
/// by the configuration set (as-they-come).
/// 2. A parse order list with too few elements is detected.
/// 3. Ordered parsing parses the elements in the order specified by the
/// configuration manager's parse order list.
/// 4. A parse order list with too many elements is detected.
TEST_F(DStubCfgMgrTest, parseOrderTest) {
    // Element ids used for test.
    std::string charlie("charlie");
    std::string bravo("bravo");
    std::string alpha("alpha");
    std::string string_test("string_test");
    std::string uint32_test("uint32_test");
    std::string bool_test("bool_test");

    // Create the test configuration with the elements in "random" order.

    // NOTE that element sets produced by  isc::data::Element::fromJSON(),
    // are in lexical order by element_id. This means that iterating over
    // such an element set, will present the elements in lexical order. Should
    // this change, this test will need to be modified accordingly.
    string config = "{"
                    " \"string_test\": \"hoopla\", "
                    " \"bravo\": [],  "
                    " \"uint32_test\": 55, "
                    " \"alpha\": {},  "
                    " \"charlie\": [], "
                    " \"bool_test\": true "
                    "} ";

    ASSERT_TRUE(fromJSON(config));

    // Verify that non-ordered parsing, results in an as-they-come parse order.
    // Create an expected parse order.
    // (NOTE that iterating over Element sets produced by fromJSON() will
    // present the elements in lexical order.  Should this change, the expected
    // order list below would need to be changed accordingly).
    ElementIdList order_expected;

    // scalar params should be first and lexically
    order_expected.push_back(bool_test);
    order_expected.push_back(string_test);
    order_expected.push_back(uint32_test);

    // objects second and lexically
    order_expected.push_back(alpha);
    order_expected.push_back(bravo);
    order_expected.push_back(charlie);

    // Verify that the manager has an EMPTY parse order list. (Empty list
    // instructs the manager to parse them as-they-come.)
    EXPECT_EQ(0, cfg_mgr_->getParseOrder().size());

    // Parse the configuration, verify it parses without error.
    answer_ = cfg_mgr_->parseConfig(config_set_);
    EXPECT_TRUE(checkAnswer(0));

    // Verify that the parsed order matches what we expected.
    EXPECT_TRUE(cfg_mgr_->parsed_order_ ==  order_expected);

    // Clear the manager's parse order "memory".
    cfg_mgr_->parsed_order_.clear();

    // Create a parse order list that has too few entries.  Verify that
    // when parsing the test config, it fails.
    cfg_mgr_->addToParseOrder(charlie);
    // Verify the parse order list is the size we expect.
    EXPECT_EQ(1, cfg_mgr_->getParseOrder().size());

    // Verify the configuration fails.
    answer_ = cfg_mgr_->parseConfig(config_set_);
    EXPECT_TRUE(checkAnswer(1));

    // Verify that the configuration parses correctly, when the parse order
    // is correct.  Add the needed entries to the parse order
    cfg_mgr_->addToParseOrder(bravo);
    cfg_mgr_->addToParseOrder(alpha);

    // Verify the parse order list is the size we expect.
    EXPECT_EQ(3, cfg_mgr_->getParseOrder().size());

    // Clear the manager's parse order "memory".
    cfg_mgr_->parsed_order_.clear();

    // Verify the configuration parses without error.
    answer_ = cfg_mgr_->parseConfig(config_set_);
    EXPECT_TRUE(checkAnswer(0));

    // Build expected order
    // primitives should be first and lexically
    order_expected.clear();
    order_expected.push_back(bool_test);
    order_expected.push_back(string_test);
    order_expected.push_back(uint32_test);

    // objects second and by the parse order
    order_expected.push_back(charlie);
    order_expected.push_back(bravo);
    order_expected.push_back(alpha);

    // Verify that the parsed order is the order we configured.
    EXPECT_TRUE(cfg_mgr_->parsed_order_ ==  order_expected);

    // Create a parse order list that has too many entries.  Verify that
    // when parsing the test config, it fails.
    cfg_mgr_->addToParseOrder("delta");

    // Verify the parse order list is the size we expect.
    EXPECT_EQ(4, cfg_mgr_->getParseOrder().size());

    // Verify the configuration fails.
    answer_ = cfg_mgr_->parseConfig(config_set_);
    EXPECT_TRUE(checkAnswer(1));
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
    answer_ = cfg_mgr_->parseConfig(config_set_);
    ASSERT_TRUE(checkAnswer(0));
    DStubContextPtr context = getStubContext();
    ASSERT_TRUE(context);

    // Verify that the boolean parameter was parsed correctly by retrieving
    // its value from the context.
    bool actual_bool = false;
    EXPECT_NO_THROW(context->getParam("bool_test", actual_bool));
    EXPECT_EQ(true, actual_bool);

    // Verify that the uint32 parameter was parsed correctly by retrieving
    // its value from the context.
    uint32_t actual_uint32 = 0;
    EXPECT_NO_THROW(context->getParam("uint32_test", actual_uint32));
    EXPECT_EQ(77, actual_uint32);

    // Verify that the string parameter was parsed correctly by retrieving
    // its value from the context.
    std::string actual_string = "";
    EXPECT_NO_THROW(context->getParam("string_test", actual_string));
    EXPECT_EQ("hmmm chewy", actual_string);

    isc::data::ConstElementPtr object;
    EXPECT_NO_THROW(context->getObjectParam("map_test", object));
    EXPECT_TRUE(object);

    EXPECT_NO_THROW(context->getObjectParam("list_test", object));
    EXPECT_TRUE(object);

    // Create a configuration which "updates" all of the parameter values.
    string config2 = "{ \"bool_test\": false , "
                    "  \"uint32_test\": 88 , "
                    "  \"string_test\": \"ewww yuk!\" , "
                    "  \"map_test2\" : {} , "
                    "  \"list_test2\": [] }";
    ASSERT_TRUE(fromJSON(config2));

    // Verify that the configuration parses without error.
    answer_ = cfg_mgr_->parseConfig(config_set_);
    EXPECT_TRUE(checkAnswer(0));
    context = getStubContext();
    ASSERT_TRUE(context);

    // Verify that the boolean parameter was updated correctly by retrieving
    // its value from the context.
    actual_bool = true;
    EXPECT_NO_THROW(context->getParam("bool_test", actual_bool));
    EXPECT_FALSE(actual_bool);

    // Verify that the uint32 parameter was updated correctly by retrieving
    // its value from the context.
    actual_uint32 = 0;
    EXPECT_NO_THROW(context->getParam("uint32_test", actual_uint32));
    EXPECT_EQ(88, actual_uint32);

    // Verify that the string parameter was updated correctly by retrieving
    // its value from the context.
    actual_string = "";
    EXPECT_NO_THROW(context->getParam("string_test", actual_string));
    EXPECT_EQ("ewww yuk!", actual_string);

    // Verify previous objects are not there.
    EXPECT_THROW(context->getObjectParam("map_test", object),
                                         isc::dhcp::DhcpConfigError);
    EXPECT_THROW(context->getObjectParam("list_test", object),
                                         isc::dhcp::DhcpConfigError);

    // Verify new map object is there.
    EXPECT_NO_THROW(context->getObjectParam("map_test2", object));
    EXPECT_TRUE(object);

    // Verify new list object is there.
    EXPECT_NO_THROW(context->getObjectParam("list_test2", object));
    EXPECT_TRUE(object);
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
    answer_ = cfg_mgr_->parseConfig(config_set_);
    EXPECT_TRUE(checkAnswer(0));
    DStubContextPtr context = getStubContext();
    ASSERT_TRUE(context);

    // Verify that all of parameters have the expected values.
    bool actual_bool = false;
    EXPECT_NO_THROW(context->getParam("bool_test", actual_bool));
    EXPECT_EQ(true, actual_bool);

    uint32_t actual_uint32 = 0;
    EXPECT_NO_THROW(context->getParam("uint32_test", actual_uint32));
    EXPECT_EQ(77, actual_uint32);

    std::string actual_string = "";
    EXPECT_NO_THROW(context->getParam("string_test", actual_string));
    EXPECT_EQ("hmmm chewy", actual_string);

    isc::data::ConstElementPtr object;
    EXPECT_NO_THROW(context->getObjectParam("map_test", object));
    EXPECT_TRUE(object);

    EXPECT_NO_THROW(context->getObjectParam("list_test", object));
    EXPECT_TRUE(object);

    // Create a configuration which "updates" all of the parameter values
    // plus one unknown at the end.
    string config2 = "{ \"bool_test\": false , "
                    "  \"uint32_test\": 88 , "
                    "  \"string_test\": \"ewww yuk!\" , "
                    "  \"map_test2\" : {} , "
                    "  \"list_test2\": [] , "
                    "  \"zeta_unknown\": 33 } ";
    ASSERT_TRUE(fromJSON(config2));

    // Force a failure on the last element
    SimFailure::set(SimFailure::ftElementUnknown);
    answer_ = cfg_mgr_->parseConfig(config_set_);
    EXPECT_TRUE(checkAnswer(1));
    context = getStubContext();
    ASSERT_TRUE(context);

    // Verify that all of parameters have the original values.
    actual_bool = false;
    EXPECT_NO_THROW(context->getParam("bool_test", actual_bool));
    EXPECT_EQ(true, actual_bool);

    actual_uint32 = 0;
    EXPECT_NO_THROW(context->getParam("uint32_test", actual_uint32));
    EXPECT_EQ(77, actual_uint32);

    actual_string = "";
    EXPECT_NO_THROW(context->getParam("string_test", actual_string));
    EXPECT_EQ("hmmm chewy", actual_string);

    EXPECT_NO_THROW(context->getObjectParam("map_test", object));
    EXPECT_TRUE(object);

    EXPECT_NO_THROW(context->getObjectParam("list_test", object));
    EXPECT_TRUE(object);
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
    answer_ = cfg_mgr_->parseConfig(config_set_);
    ASSERT_TRUE(checkAnswer(0));
    DStubContextPtr context = getStubContext();
    ASSERT_TRUE(context);

    // Verify that the boolean parameter was parsed correctly by retrieving
    // its value from the context.
    bool actual_bool = false;
    isc::data::Element::Position pos;
    EXPECT_NO_THROW(pos = context->getParam("bool_test", actual_bool));
    EXPECT_EQ(true, actual_bool);
    EXPECT_EQ(1, pos.line_);

    // Verify that the uint32 parameter was parsed correctly by retrieving
    // its value from the context.
    uint32_t actual_uint32 = 0;
    EXPECT_NO_THROW(pos = context->getParam("uint32_test", actual_uint32));
    EXPECT_EQ(77, actual_uint32);
    EXPECT_EQ(2, pos.line_);

    // Verify that the string parameter was parsed correctly by retrieving
    // its value from the context.
    std::string actual_string = "";
    EXPECT_NO_THROW(pos = context->getParam("string_test", actual_string));
    EXPECT_EQ("hmmm chewy", actual_string);
    EXPECT_EQ(3, pos.line_);

    // Verify that an optional parameter that is not defined, returns the
    // zero position.
    pos = isc::data::Element::ZERO_POSITION();
    EXPECT_NO_THROW(pos = context->getParam("bogus_value",
                                            actual_string, true));
    EXPECT_EQ(pos.file_, isc::data::Element::ZERO_POSITION().file_);
}


} // end of anonymous namespace
