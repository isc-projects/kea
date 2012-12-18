
// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include <dhcp4/dhcp4_srv.h>
#include <dhcp4/config_parser.h>
#include <config/ccsession.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/cfgmgr.h>
#include <boost/foreach.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::config;

namespace isc {
namespace dhcp {
extern Uint32Storage uint32_defaults;
}
}

namespace {

class Dhcp4ParserTest : public ::testing::Test {
public:
    Dhcp4ParserTest()
    :rcode_(-1) {
        // Open port 0 means to not do anything at all. We don't want to
        // deal with sockets here, just check if configuration handling
        // is sane.
        srv_ = new Dhcpv4Srv(0);
    }

    // Checks if global parameter of name have expected_value
    void checkGlobalUint32(string name, uint32_t expected_value) {
        Uint32Storage::const_iterator it = uint32_defaults.find(name);
        if (it == uint32_defaults.end()) {
            ADD_FAILURE() << "Expected uint32 with name " << name
                          << " not found";
            return;
        }
        EXPECT_EQ(expected_value, it->second);
    }

    // Checks if config_result (result of DHCP server configuration) has
    // expected code (0 for success, other for failures).
    // Also stores result in rcode_ and comment_.
    void checkResult(ConstElementPtr status, int expected_code) {
        ASSERT_TRUE(status);
        comment_ = parseAnswer(rcode_, status);
        EXPECT_EQ(expected_code, rcode_);
    }

    ~Dhcp4ParserTest() {
        resetConfiguration();
        delete srv_;
    };

    /// @brief Create the simple configuration with single option.
    ///
    /// This function allows to set one of the parameters that configure
    /// option value. These parameters are: "name", "code" and "data".
    ///
    /// @param param_value string holiding option parameter value to be
    /// injected into the configuration string.
    /// @param parameter name of the parameter to be configured with
    /// param value.
    std::string createConfigWithOption(const std::string& param_value,
                                       const std::string& parameter) {
        std::map<std::string, std::string> params;
        if (parameter == "name") {
            params["name"] = param_value;
            params["code"] = "56";
            params["data"] = "AB CDEF0105";
        } else if (parameter == "code") {
            params["name"] = "option_foo";
            params["code"] = param_value;
            params["data"] = "AB CDEF0105";
        } else if (parameter == "data") {
            params["name"] = "option_foo";
            params["code"] = "56";
            params["data"] = param_value;
        }
        return (createConfigWithOption(params));
    }

    std::string createConfigWithOption(const std::map<std::string, std::string>& params) {
        std::ostringstream stream;
        stream << "{ \"interface\": [ \"all\" ],"
            "\"rebind-timer\": 2000, "
            "\"renew-timer\": 1000, "
            "\"subnet4\": [ { "
            "    \"pool\": [ \"192.0.2.1 - 192.0.2.100\" ],"
            "    \"subnet\": \"192.0.2.0/24\", "
            "    \"option-data\": [ {";
        bool first = true;
        typedef std::pair<std::string, std::string> ParamPair;
        BOOST_FOREACH(ParamPair param, params) {
            if (!first) {
                stream << ", ";
            } else {
                first = false;
            }
            if (param.first == "name") {
                stream << "\"name\": \"" << param.second << "\"";
            } else if (param.first == "code") {
                stream << "\"code\": " << param.second << "";
            } else if (param.first == "data") {
                stream << "\"data\": \"" << param.second << "\"";
            }
        }
        stream <<
            "        } ]"
            " } ],"
            "\"valid-lifetime\": 4000 }";
        return (stream.str());
    }

    /// @brief Test invalid option parameter value.
    ///
    /// This test function constructs the simple configuration
    /// string and injects invalid option configuration into it.
    /// It expects that parser will fail with provided option code.
    ///
    /// @param param_value string holding invalid option parameter value
    /// to be injected into configuration string.
    /// @param parameter name of the parameter to be configured with
    /// param_value (can be any of "name", "code", "data")
    void testInvalidOptionParam(const std::string& param_value,
                                const std::string& parameter) {
        ConstElementPtr x;
        std::string config = createConfigWithOption(param_value, parameter);
        ElementPtr json = Element::fromJSON(config);
        EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
        ASSERT_TRUE(x);
        comment_ = parseAnswer(rcode_, x);
        ASSERT_EQ(1, rcode_);
    }

    /// @brief Test option against given code and data.
    ///
    /// @param option_desc option descriptor that carries the option to
    /// be tested.
    /// @param expected_code expected code of the option.
    /// @param expected_data expected data in the option.
    /// @param expected_data_len length of the reference data.
    /// @param extra_data if true extra data is allowed in an option
    /// after tested data.
    void testOption(const Subnet::OptionDescriptor& option_desc,
                    uint16_t expected_code, const uint8_t* expected_data,
                    size_t expected_data_len,
                    bool extra_data = false) {
        // Check if option descriptor contains valid option pointer.
        ASSERT_TRUE(option_desc.option);
        // Verify option type.
        EXPECT_EQ(expected_code, option_desc.option->getType());
        // We may have many different option types being created. Some of them
        // have dedicated classes derived from Option class. In such case if
        // we want to verify the option contents against expected_data we have
        // to prepare raw buffer with the contents of the option. The easiest
        // way is to call pack() which will prepare on-wire data.
        util::OutputBuffer buf(option_desc.option->getData().size());
        option_desc.option->pack(buf);
        if (extra_data) {
            // The length of the buffer must be at least equal to size of the
            // reference data but it can sometimes be greater than that. This is
            // because some options carry suboptions that increase the overall
            // length.
            ASSERT_GE(buf.getLength() - option_desc.option->getHeaderLen(),
                      expected_data_len);
        } else {
            ASSERT_EQ(buf.getLength() - option_desc.option->getHeaderLen(),
                      expected_data_len);
        }
        // Verify that the data is correct. However do not verify suboptions.
        const uint8_t* data = static_cast<const uint8_t*>(buf.getData());
        EXPECT_TRUE(memcmp(expected_data, data, expected_data_len));
    }

    /// @brief Reset configuration database.
    ///
    /// This function resets configuration data base by
    /// removing all subnets and option-data. Reset must
    /// be performed after each test to make sure that
    /// contents of the database do not affect result of
    /// subsequent tests.
    void resetConfiguration() {
        ConstElementPtr status;

        string config = "{ \"interface\": [ \"all\" ],"
            "\"rebind-timer\": 2000, "
            "\"renew-timer\": 1000, "
            "\"valid-lifetime\": 4000, "
            "\"subnet4\": [ ], "
            "\"option-data\": [ ] }";

        try {
            ElementPtr json = Element::fromJSON(config);
            status = configureDhcp4Server(*srv_, json);
        } catch (const std::exception& ex) {
            FAIL() << "Fatal error: unable to reset configuration database"
                   << " after the test. The following configuration was used"
                   << " to reset database: " << std::endl
                   << config << std::endl
                   << " and the following error message was returned:"
                   << ex.what() << std::endl;
        }


        // returned value should be 0 (configuration success)
        if (!status) {
            FAIL() << "Fatal error: unable to reset configuration database"
                   << " after the test. Configuration function returned"
                   << " NULL pointer" << std::endl;
        }
        comment_ = parseAnswer(rcode_, status);
        if (rcode_ != 0) {
            FAIL() << "Fatal error: unable to reset configuration database"
                   << " after the test. Configuration function returned"
                   << " error code " << rcode_ << std::endl;
        }
    }

    Dhcpv4Srv* srv_;

    int rcode_;
    ConstElementPtr comment_;
};

// Goal of this test is a verification if a very simple config update
// with just a bumped version number. That's the simplest possible
// config update.
TEST_F(Dhcp4ParserTest, version) {

    ConstElementPtr x;

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_,
                    Element::fromJSON("{\"version\": 0}")));

    // returned value must be 0 (configuration accepted)
    checkResult(x, 0);
}

/// The goal of this test is to verify that the code accepts only
/// valid commands and malformed or unsupported parameters are rejected.
TEST_F(Dhcp4ParserTest, bogusCommand) {

    ConstElementPtr x;

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_,
                    Element::fromJSON("{\"bogus\": 5}")));

    // returned value must be 1 (configuration parse error)
    checkResult(x, 1);
}

/// The goal of this test is to verify if wrongly defined subnet will
/// be rejected. Properly defined subnet must include at least one
/// pool definition.
TEST_F(Dhcp4ParserTest, emptySubnet) {

    ConstElementPtr status;

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_,
                    Element::fromJSON("{ \"interface\": [ \"all\" ],"
                                      "\"rebind-timer\": 2000, "
                                      "\"renew-timer\": 1000, "
                                      "\"subnet4\": [  ], "
                                      "\"valid-lifetime\": 4000 }")));

    // returned value should be 0 (success)
    checkResult(status, 0);

    checkGlobalUint32("rebind-timer", 2000);
    checkGlobalUint32("renew-timer", 1000);
    checkGlobalUint32("valid-lifetime", 4000);
}

/// The goal of this test is to verify if defined subnet uses global
/// parameter timer definitions.
TEST_F(Dhcp4ParserTest, subnetGlobalDefaults) {

    ConstElementPtr status;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pool\": [ \"192.0.2.1 - 192.0.2.100\" ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // check if returned status is OK
    checkResult(status, 0);

    // Now check if the configuration was indeed handled and we have
    // expected pool configured.
    Subnet4Ptr subnet = CfgMgr::instance().getSubnet4(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1000, subnet->getT1());
    EXPECT_EQ(2000, subnet->getT2());
    EXPECT_EQ(4000, subnet->getValid());
}

// This test checks if it is possible to override global values
// on a per subnet basis.
TEST_F(Dhcp4ParserTest, subnetLocal) {

    ConstElementPtr status;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pool\": [ \"192.0.2.1 - 192.0.2.100\" ],"
        "    \"renew-timer\": 1, "
        "    \"rebind-timer\": 2, "
        "    \"valid-lifetime\": 4,"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value should be 0 (configuration success)
    checkResult(status, 0);

    Subnet4Ptr subnet = CfgMgr::instance().getSubnet4(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1, subnet->getT1());
    EXPECT_EQ(2, subnet->getT2());
    EXPECT_EQ(4, subnet->getValid());
}

// Test verifies that a subnet with pool values that do not belong to that
// pool are rejected.
TEST_F(Dhcp4ParserTest, poolOutOfSubnet) {

    ConstElementPtr status;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pool\": [ \"192.0.4.0/28\" ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value must be 2 (values error)
    // as the pool does not belong to that subnet
    checkResult(status, 2);
}

// Goal of this test is to verify if pools can be defined
// using prefix/length notation. There is no separate test for min-max
// notation as it was tested in several previous tests.
TEST_F(Dhcp4ParserTest, poolPrefixLen) {

    ConstElementPtr status;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pool\": [ \"192.0.2.128/28\" ],"
        "    \"subnet\": \"192.0.2.0/24\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_, json));

    // returned value must be 0 (configuration accepted)
    checkResult(status, 0);

    Subnet4Ptr subnet = CfgMgr::instance().getSubnet4(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1000, subnet->getT1());
    EXPECT_EQ(2000, subnet->getT2());
    EXPECT_EQ(4000, subnet->getValid());
}

// Goal of this test is to verify that global option
// data is configured for the subnet if the subnet
// configuration does not include options configuration.
TEST_F(Dhcp4ParserTest, optionDataDefaults) {
    ConstElementPtr x;
    string config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"option_foo\","
        "    \"code\": 56,"
        "    \"data\": \"AB CDEF0105\""
        " },"
        " {"
        "    \"name\": \"option_foo2\","
        "    \"code\": 23,"
        "    \"data\": \"01\""
        " } ],"
        "\"subnet4\": [ { "
        "    \"pool\": [ \"192.0.2.1 - 192.0.2.100\" ],"
        "    \"subnet\": \"192.0.2.0/24\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);

    Subnet4Ptr subnet = CfgMgr::instance().getSubnet4(IOAddress("192.0.2.200"));
    ASSERT_TRUE(subnet);
    const Subnet::OptionContainer& options = subnet->getOptions();
    ASSERT_EQ(2, options.size());

    // Get the search index. Index #1 is to search using option code.
    const Subnet::OptionContainerTypeIndex& idx = options.get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<Subnet::OptionContainerTypeIndex::const_iterator,
              Subnet::OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(56);
    // Expect single option with the code equal to 56.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t foo_expected[] = {
        0xAB, 0xCD, 0xEF, 0x01, 0x05
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, 56, foo_expected, sizeof(foo_expected));

    range = idx.equal_range(23);
    ASSERT_EQ(1, std::distance(range.first, range.second));
    // Do another round of testing with second option.
    const uint8_t foo2_expected[] = {
        0x01
    };
    testOption(*range.first, 23, foo2_expected, sizeof(foo2_expected));
}

// Goal of this test is to verify options configuration
// for a single subnet. In particular this test checks
// that local options configuration overrides global
// option setting.
TEST_F(Dhcp4ParserTest, optionDataInSingleSubnet) {
    ConstElementPtr x;
    string config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-data\": [ {"
        "      \"name\": \"option_foo\","
        "      \"code\": 56,"
        "      \"data\": \"AB\""
        " } ],"
        "\"subnet4\": [ { "
        "    \"pool\": [ \"192.0.2.1 - 192.0.2.100\" ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"option-data\": [ {"
        "          \"name\": \"option_foo\","
        "          \"code\": 56,"
        "          \"data\": \"AB CDEF0105\""
        "        },"
        "        {"
        "          \"name\": \"option_foo2\","
        "          \"code\": 23,"
        "          \"data\": \"01\""
        "        } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);

    Subnet4Ptr subnet = CfgMgr::instance().getSubnet4(IOAddress("192.0.2.24"));
    ASSERT_TRUE(subnet);
    const Subnet::OptionContainer& options = subnet->getOptions();
    ASSERT_EQ(2, options.size());

    // Get the search index. Index #1 is to search using option code.
    const Subnet::OptionContainerTypeIndex& idx = options.get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<Subnet::OptionContainerTypeIndex::const_iterator,
              Subnet::OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(56);
    // Expect single option with the code equal to 100.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t foo_expected[] = {
        0xAB, 0xCD, 0xEF, 0x01, 0x05
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, 56, foo_expected, sizeof(foo_expected));

    range = idx.equal_range(23);
    ASSERT_EQ(1, std::distance(range.first, range.second));
    // Do another round of testing with second option.
    const uint8_t foo2_expected[] = {
        0x01
    };
    testOption(*range.first, 23, foo2_expected, sizeof(foo2_expected));
}

// Goal of this test is to verify options configuration
// for multiple subnets.
TEST_F(Dhcp4ParserTest, optionDataInMultipleSubnets) {
    ConstElementPtr x;
    string config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet4\": [ { "
        "    \"pool\": [ \"192.0.2.1 - 192.0.2.100\" ],"
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"option-data\": [ {"
        "          \"name\": \"option_foo\","
        "          \"code\": 56,"
        "          \"data\": \"0102030405060708090A\""
        "        } ]"
        " },"
        " {"
        "    \"pool\": [ \"192.0.3.101 - 192.0.3.150\" ],"
        "    \"subnet\": \"192.0.3.0/24\", "
        "    \"option-data\": [ {"
        "          \"name\": \"option_foo2\","
        "          \"code\": 23,"
        "          \"data\": \"FF\""
        "        } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);

    Subnet4Ptr subnet1 = CfgMgr::instance().getSubnet4(IOAddress("192.0.2.100"));
    ASSERT_TRUE(subnet1);
    const Subnet::OptionContainer& options1 = subnet1->getOptions();
    ASSERT_EQ(1, options1.size());

    // Get the search index. Index #1 is to search using option code.
    const Subnet::OptionContainerTypeIndex& idx1 = options1.get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<Subnet::OptionContainerTypeIndex::const_iterator,
              Subnet::OptionContainerTypeIndex::const_iterator> range1 =
        idx1.equal_range(56);
    // Expect single option with the code equal to 56.
    ASSERT_EQ(1, std::distance(range1.first, range1.second));
    const uint8_t foo_expected[] = {
        0x01, 0x02, 0x03, 0x04, 0x05,
        0x06, 0x07, 0x08, 0x09, 0x0A
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range1.first, 56, foo_expected, sizeof(foo_expected));

    // Test another subnet in the same way.
    Subnet4Ptr subnet2 = CfgMgr::instance().getSubnet4(IOAddress("192.0.3.102"));
    ASSERT_TRUE(subnet2);
    const Subnet::OptionContainer& options2 = subnet2->getOptions();
    ASSERT_EQ(1, options2.size());

    const Subnet::OptionContainerTypeIndex& idx2 = options2.get<1>();
    std::pair<Subnet::OptionContainerTypeIndex::const_iterator,
              Subnet::OptionContainerTypeIndex::const_iterator> range2 =
        idx2.equal_range(23);
    ASSERT_EQ(1, std::distance(range2.first, range2.second));

    const uint8_t foo2_expected[] = { 0xFF };
    testOption(*range2.first, 23, foo2_expected, sizeof(foo2_expected));
}

// Verify that empty option name is rejected in the configuration.
TEST_F(Dhcp4ParserTest, optionNameEmpty) {
    // Empty option names not allowed.
    testInvalidOptionParam("", "name");
}

// Verify that empty option name with spaces is rejected
// in the configuration.
TEST_F(Dhcp4ParserTest, optionNameSpaces) {
    // Spaces in option names not allowed.
    testInvalidOptionParam("option foo", "name");
}

// Verify that negative option code is rejected in the configuration.
TEST_F(Dhcp4ParserTest, optionCodeNegative) {
    // Check negative option code -4. This should fail too.
    testInvalidOptionParam("-4", "code");
}

// Verify that out of bounds option code is rejected in the configuration.
TEST_F(Dhcp4ParserTest, optionCodeNonUint8) {
    // The valid option codes are uint16_t values so passing
    // uint16_t maximum value incremented by 1 should result
    // in failure.
    testInvalidOptionParam("257", "code");
}

// Verify that zero option code is rejected in the configuration.
TEST_F(Dhcp4ParserTest, optionCodeZero) {
    // Option code 0 is reserved and should not be accepted
    // by configuration parser.
    testInvalidOptionParam("0", "code");
}

// Verify that option data which contains non hexadecimal characters
// is rejected by the configuration.
TEST_F(Dhcp4ParserTest, optionDataInvalidChar) {
    // Option code 0 is reserved and should not be accepted
    // by configuration parser.
    testInvalidOptionParam("01020R", "data");
}

// Verify that option data containins '0x' prefix is rejected
// by the configuration.
TEST_F(Dhcp4ParserTest, optionDataUnexpectedPrefix) {
    // Option code 0 is reserved and should not be accepted
    // by configuration parser.
    testInvalidOptionParam("0x0102", "data");
}

// Verify that option data consisting od an odd number of
// hexadecimal digits is rejected in the configuration.
TEST_F(Dhcp4ParserTest, optionDataOddLength) {
    // Option code 0 is reserved and should not be accepted
    // by configuration parser.
    testInvalidOptionParam("123", "data");
}

// Verify that either lower or upper case characters are allowed
// to specify the option data.
TEST_F(Dhcp4ParserTest, optionDataLowerCase) {
    ConstElementPtr x;
    std::string config = createConfigWithOption("0a0b0C0D", "data");
    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp4Server(*srv_, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);

    Subnet4Ptr subnet = CfgMgr::instance().getSubnet4(IOAddress("192.0.2.5"));
    ASSERT_TRUE(subnet);
    const Subnet::OptionContainer& options = subnet->getOptions();
    ASSERT_EQ(1, options.size());

    // Get the search index. Index #1 is to search using option code.
    const Subnet::OptionContainerTypeIndex& idx = options.get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<Subnet::OptionContainerTypeIndex::const_iterator,
              Subnet::OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(56);
    // Expect single option with the code equal to 100.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t foo_expected[] = {
        0x0A, 0x0B, 0x0C, 0x0D
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, 56, foo_expected, sizeof(foo_expected));
}

/// This test checks if Uint32Parser can really parse the whole range
/// and properly err of out of range values. As we can't call Uint32Parser
/// directly, we are exploiting the fact that it is used to parse global
/// parameter renew-timer and the results are stored in uint32_defaults.
TEST_F(Dhcp4ParserTest, DISABLED_Uint32Parser) {

    ConstElementPtr status;

    // CASE 1: 0 - minimum value, should work
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_,
                    Element::fromJSON("{\"version\": 0,"
                                      "\"renew-timer\": 0}")));

    // returned value must be ok (0 is a proper value)
    checkResult(status, 0);
    checkGlobalUint32("renew-timer", 0);

    // CASE 2: 4294967295U (UINT_MAX) should work as well
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_,
                    Element::fromJSON("{\"version\": 0,"
                                      "\"renew-timer\": 4294967295}")));

    // returned value must be ok (0 is a proper value)
    checkResult(status, 0);
    checkGlobalUint32("renew-timer", 4294967295U);

    // CASE 3: 4294967296U (UINT_MAX + 1) should not work
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_,
                    Element::fromJSON("{\"version\": 0,"
                                      "\"renew-timer\": 4294967296}")));

    // returned value must be rejected (1 configuration error)
    checkResult(status, 1);

    // CASE 4: -1 (UINT_MIN -1 ) should not work
    EXPECT_NO_THROW(status = configureDhcp4Server(*srv_,
                    Element::fromJSON("{\"version\": 0,"
                                      "\"renew-timer\": -1}")));

    // returned value must be rejected (1 configuration error)
    checkResult(status, 1);
}

};
