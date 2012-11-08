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
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/foreach.hpp>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include <dhcp6/dhcp6_srv.h>
#include <dhcp6/config_parser.h>
#include <config/ccsession.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/subnet.h>
#include <dhcp/cfgmgr.h>
#include <dhcp/option6_ia.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::config;

namespace {

class Dhcp6ParserTest : public ::testing::Test {
public:
    Dhcp6ParserTest()
    :rcode_(-1) {
        // Open port 0 means to not do anything at all. We don't want to
        // deal with sockets here, just check if configuration handling
        // is sane.
        srv_ = new Dhcpv6Srv(0);
        // Create instances of option definitions and put them into storage.
        // This is normally initialized by the server when calling run()
        // run() function.
        LibDHCP::initStdOptionDefs(Option::V6);
    }

    ~Dhcp6ParserTest() {
        // Reset configuration database after each test.
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
            params["code"] = "80";
            params["data"] = "AB CDEF0105";
        } else if (parameter == "code") {
            params["name"] = "option_foo";
            params["code"] = param_value;
            params["data"] = "AB CDEF0105";
        } else if (parameter == "data") {
            params["name"] = "option_foo";
            params["code"] = "80";
            params["data"] = param_value;
        }
        return (createConfigWithOption(params));
    }

    std::string createConfigWithOption(const std::map<std::string, std::string>& params) {
        std::ostringstream stream;
        stream << "{ \"interface\": [ \"all\" ],"
            "\"preferred-lifetime\": 3000,"
            "\"rebind-timer\": 2000, "
            "\"renew-timer\": 1000, "
            "\"subnet6\": [ { "
            "    \"pool\": [ \"2001:db8:1::/80\" ],"
            "    \"subnet\": \"2001:db8:1::/64\", "
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
            "\"preferred-lifetime\": 3000,"
            "\"rebind-timer\": 2000, "
            "\"renew-timer\": 1000, "
            "\"valid-lifetime\": 4000, "
            "\"subnet6\": [ ], "
            "\"option-data\": [ ] }";

        try {
            ElementPtr json = Element::fromJSON(config);
            status = configureDhcp6Server(*srv_, json);
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
        EXPECT_NO_THROW(x = configureDhcp6Server(*srv_, json));
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

    Dhcpv6Srv* srv_;

    int rcode_;
    ConstElementPtr comment_;
};

// Goal of this test is a verification if a very simple config update
// with just a bumped version number. That's the simplest possible
// config update.
TEST_F(Dhcp6ParserTest, version) {

    ConstElementPtr x;

    EXPECT_NO_THROW(x = configureDhcp6Server(*srv_,
                    Element::fromJSON("{\"version\": 0}")));

    // returned value must be 0 (configuration accepted)
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    EXPECT_EQ(0, rcode_);
}

/// The goal of this test is to verify that the code accepts only
/// valid commands and malformed or unsupported parameters are rejected.
TEST_F(Dhcp6ParserTest, bogusCommand) {

    ConstElementPtr x;

    EXPECT_NO_THROW(x = configureDhcp6Server(*srv_,
                    Element::fromJSON("{\"bogus\": 5}")));

    // returned value must be 1 (configuration parse error)
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    EXPECT_EQ(1, rcode_);
}

/// The goal of this test is to verify if wrongly defined subnet will
/// be rejected. Properly defined subnet must include at least one
/// pool definition.
TEST_F(Dhcp6ParserTest, emptySubnet) {

    ConstElementPtr status;

    EXPECT_NO_THROW(status = configureDhcp6Server(*srv_,
                    Element::fromJSON("{ \"interface\": [ \"all\" ],"
                                      "\"preferred-lifetime\": 3000,"
                                      "\"rebind-timer\": 2000, "
                                      "\"renew-timer\": 1000, "
                                      "\"subnet6\": [  ], "
                                      "\"valid-lifetime\": 4000 }")));

    // returned value should be 0 (success)
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    EXPECT_EQ(0, rcode_);
}

/// The goal of this test is to verify if defined subnet uses global
/// parameter timer definitions.
TEST_F(Dhcp6ParserTest, subnetGlobalDefaults) {

    ConstElementPtr status;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::1 - 2001:db8:1::ffff\" ],"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(*srv_, json));

    // check if returned status is OK
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    EXPECT_EQ(0, rcode_);

    // Now check if the configuration was indeed handled and we have
    // expected pool configured.
    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1000, subnet->getT1());
    EXPECT_EQ(2000, subnet->getT2());
    EXPECT_EQ(3000, subnet->getPreferred());
    EXPECT_EQ(4000, subnet->getValid());
}

// This test checks if it is possible to override global values
// on a per subnet basis.
TEST_F(Dhcp6ParserTest, subnetLocal) {

    ConstElementPtr status;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::1 - 2001:db8:1::ffff\" ],"
        "    \"renew-timer\": 1, "
        "    \"rebind-timer\": 2, "
        "    \"preferred-lifetime\": 3,"
        "    \"valid-lifetime\": 4,"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(*srv_, json));

    // returned value should be 0 (configuration success)
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    EXPECT_EQ(0, rcode_);

    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1, subnet->getT1());
    EXPECT_EQ(2, subnet->getT2());
    EXPECT_EQ(3, subnet->getPreferred());
    EXPECT_EQ(4, subnet->getValid());
}

// Test verifies that a subnet with pool values that do not belong to that
// pool are rejected.
TEST_F(Dhcp6ParserTest, poolOutOfSubnet) {

    ConstElementPtr status;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"4001:db8:1::/80\" ],"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(*srv_, json));

    // returned value must be 2 (values error)
    // as the pool does not belong to that subnet
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    EXPECT_EQ(2, rcode_);
}

// Goal of this test is to verify if pools can be defined
// using prefix/length notation. There is no separate test for min-max
// notation as it was tested in several previous tests.
TEST_F(Dhcp6ParserTest, poolPrefixLen) {

    ConstElementPtr x;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::/80\" ],"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(*srv_, json));

    // returned value must be 1 (configuration parse error)
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    EXPECT_EQ(0, rcode_);

    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1000, subnet->getT1());
    EXPECT_EQ(2000, subnet->getT2());
    EXPECT_EQ(3000, subnet->getPreferred());
    EXPECT_EQ(4000, subnet->getValid());
}

// Goal of this test is to verify that global option
// data is configured for the subnet if the subnet
// configuration does not include options configuration.
TEST_F(Dhcp6ParserTest, optionDataDefaults) {
    ConstElementPtr x;
    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"option_foo\","
        "    \"code\": 100,"
        "    \"data\": \"AB CDEF0105\""
        " },"
        " {"
        "    \"name\": \"option_foo2\","
        "    \"code\": 101,"
        "    \"data\": \"01\""
        " } ],"
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::/80\" ],"
        "    \"subnet\": \"2001:db8:1::/64\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(*srv_, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);

    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
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
        idx.equal_range(100);
    // Expect single option with the code equal to 100.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t foo_expected[] = {
        0xAB, 0xCD, 0xEF, 0x01, 0x05
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, 100, foo_expected, sizeof(foo_expected));

    range = idx.equal_range(101);
    ASSERT_EQ(1, std::distance(range.first, range.second));
    // Do another round of testing with second option.
    const uint8_t foo2_expected[] = {
        0x01
    };
    testOption(*range.first, 101, foo2_expected, sizeof(foo2_expected));

    // Check that options with other option codes are not returned.
    for (uint16_t code = 102; code < 110; ++code) {
        range = idx.equal_range(code);
        EXPECT_EQ(0, std::distance(range.first, range.second));
    }
}

// Goal of this test is to verify options configuration
// for a single subnet. In particular this test checks
// that local options configuration overrides global
// option setting.
TEST_F(Dhcp6ParserTest, optionDataInSingleSubnet) {
    ConstElementPtr x;
    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"option-data\": [ {"
        "      \"name\": \"option_foo\","
        "      \"code\": 100,"
        "      \"data\": \"AB\""
        " } ],"
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::/80\" ],"
        "    \"subnet\": \"2001:db8:1::/64\", "
        "    \"option-data\": [ {"
        "          \"name\": \"option_foo\","
        "          \"code\": 100,"
        "          \"data\": \"AB CDEF0105\""
        "        },"
        "        {"
        "          \"name\": \"option_foo2\","
        "          \"code\": 101,"
        "          \"data\": \"01\""
        "        } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(*srv_, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);

    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
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
        idx.equal_range(100);
    // Expect single option with the code equal to 100.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t foo_expected[] = {
        0xAB, 0xCD, 0xEF, 0x01, 0x05
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, 100, foo_expected, sizeof(foo_expected));

    range = idx.equal_range(101);
    ASSERT_EQ(1, std::distance(range.first, range.second));
    // Do another round of testing with second option.
    const uint8_t foo2_expected[] = {
        0x01
    };
    testOption(*range.first, 101, foo2_expected, sizeof(foo2_expected));
}

// Goal of this test is to verify options configuration
// for multiple subnets.
TEST_F(Dhcp6ParserTest, optionDataInMultipleSubnets) {
    ConstElementPtr x;
    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::/80\" ],"
        "    \"subnet\": \"2001:db8:1::/64\", "
        "    \"option-data\": [ {"
        "          \"name\": \"option_foo\","
        "          \"code\": 100,"
        "          \"data\": \"0102030405060708090A\""
        "        } ]"
        " },"
        " {"
        "    \"pool\": [ \"2001:db8:2::/80\" ],"
        "    \"subnet\": \"2001:db8:2::/64\", "
        "    \"option-data\": [ {"
        "          \"name\": \"option_foo2\","
        "          \"code\": 101,"
        "          \"data\": \"FFFEFDFCFB\""
        "        } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(*srv_, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);

    Subnet6Ptr subnet1 = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
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
        idx1.equal_range(100);
    // Expect single option with the code equal to 100.
    ASSERT_EQ(1, std::distance(range1.first, range1.second));
    const uint8_t foo_expected[] = {
        0x01, 0x02, 0x03, 0x04, 0x05,
        0x06, 0x07, 0x08, 0x09, 0x0A
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range1.first, 100, foo_expected, sizeof(foo_expected));

    // Test another subnet in the same way.
    Subnet6Ptr subnet2 = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:2::4"));
    ASSERT_TRUE(subnet2);
    const Subnet::OptionContainer& options2 = subnet2->getOptions();
    ASSERT_EQ(1, options2.size());

    const Subnet::OptionContainerTypeIndex& idx2 = options2.get<1>();
    std::pair<Subnet::OptionContainerTypeIndex::const_iterator,
              Subnet::OptionContainerTypeIndex::const_iterator> range2 =
        idx2.equal_range(101);
    ASSERT_EQ(1, std::distance(range2.first, range2.second));

    const uint8_t foo2_expected[] = {
        0xFF, 0xFE, 0xFD, 0xFC, 0xFB
    };
    testOption(*range2.first, 101, foo2_expected, sizeof(foo2_expected));
}

// Verify that empty option name is rejected in the configuration.
TEST_F(Dhcp6ParserTest, optionNameEmpty) {
    // Empty option names not allowed.
    testInvalidOptionParam("", "name");
}

// Verify that empty option name with spaces is rejected
// in the configuration.
TEST_F(Dhcp6ParserTest, optionNameSpaces) {
    // Spaces in option names not allowed.
    testInvalidOptionParam("option foo", "name");
}

// Verify that negative option code is rejected in the configuration.
TEST_F(Dhcp6ParserTest, optionCodeNegative) {
    // Check negative option code -4. This should fail too.
    testInvalidOptionParam("-4", "code");
}

// Verify that out of bounds option code is rejected in the configuration.
TEST_F(Dhcp6ParserTest, optionCodeNonUint16) {
    // The valid option codes are uint16_t values so passing
    // uint16_t maximum value incremented by 1 should result
    // in failure.
    testInvalidOptionParam("65536", "code");
}

// Verify that out of bounds option code is rejected in the configuration.
TEST_F(Dhcp6ParserTest, optionCodeHighNonUint16) {
    // Another check for uint16_t overflow but this time
    // let's pass even greater option code value.
    testInvalidOptionParam("70000", "code");
}

// Verify that zero option code is rejected in the configuration.
TEST_F(Dhcp6ParserTest, optionCodeZero) {
    // Option code 0 is reserved and should not be accepted
    // by configuration parser.
    testInvalidOptionParam("0", "code");
}

// Verify that option data which contains non hexadecimal characters
// is rejected by the configuration.
TEST_F(Dhcp6ParserTest, optionDataInvalidChar) {
    // Option code 0 is reserved and should not be accepted
    // by configuration parser.
    testInvalidOptionParam("01020R", "data");
}

// Verify that option data containins '0x' prefix is rejected
// by the configuration.
TEST_F(Dhcp6ParserTest, optionDataUnexpectedPrefix) {
    // Option code 0 is reserved and should not be accepted
    // by configuration parser.
    testInvalidOptionParam("0x0102", "data");
}

// Verify that option data consisting od an odd number of
// hexadecimal digits is rejected in the configuration.
TEST_F(Dhcp6ParserTest, optionDataOddLength) {
    // Option code 0 is reserved and should not be accepted
    // by configuration parser.
    testInvalidOptionParam("123", "data");
}

// Verify that either lower or upper case characters are allowed
// to specify the option data.
TEST_F(Dhcp6ParserTest, optionDataLowerCase) {
    ConstElementPtr x;
    std::string config = createConfigWithOption("0a0b0C0D", "data");
    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(*srv_, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);

    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
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
        idx.equal_range(80);
    // Expect single option with the code equal to 100.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t foo_expected[] = {
        0x0A, 0x0B, 0x0C, 0x0D
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, 80, foo_expected, sizeof(foo_expected));
}

// Verify that specific option object is returned for standard
// option which has dedicated option class derived from Option.
TEST_F(Dhcp6ParserTest, stdOptionData) {
    ConstElementPtr x;
    std::map<std::string, std::string> params;
    params["name"] = "OPTION_IA_NA";
    // Option code 3 means OPTION_IA_NA.
    params["code"] = "3";
    params["data"] = "ABCDEF01 02030405 06070809";

    std::string config = createConfigWithOption(params);
    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(*srv_, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);

    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
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
        idx.equal_range(D6O_IA_NA);
    // Expect single option with the code equal to IA_NA option code.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    // The actual pointer to the option is held in the option field
    // in the structure returned.
    OptionPtr option = range.first->option;
    ASSERT_TRUE(option);
    // Option object returned for here is expected to be Option6IA
    // which is derived from Option. This class is dedicated to
    // represent standard option IA_NA.
    boost::shared_ptr<Option6IA> optionIA =
        boost::dynamic_pointer_cast<Option6IA>(option);
    // If cast is unsuccessful than option returned was of a
    // differnt type than Option6IA. This is wrong.
    ASSERT_TRUE(optionIA);
    // If cast was successful we may use accessors exposed by
    // Option6IA to validate that the content of this option
    // has been set correctly.
    EXPECT_EQ(0xABCDEF01, optionIA->getIAID());
    EXPECT_EQ(0x02030405, optionIA->getT1());
    EXPECT_EQ(0x06070809, optionIA->getT2());
}

};
