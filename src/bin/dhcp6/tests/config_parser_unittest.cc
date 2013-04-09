// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <config/ccsession.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_ia.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int.h>
#include <dhcp6/config_parser.h>
#include <dhcp6/dhcp6_srv.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/subnet.h>

#include <boost/foreach.hpp>
#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::config;

namespace {

class Dhcp6ParserTest : public ::testing::Test {
public:
    Dhcp6ParserTest() :rcode_(-1), srv_(0) {
        // srv_(0) means to not open any sockets. We don't want to
        // deal with sockets here, just check if configuration handling
        // is sane.

        const IfaceMgr::IfaceCollection& ifaces = IfaceMgr::instance().getIfaces();

        // There must be some interface detected
        if (ifaces.empty()) {
            // We can't use ASSERT in constructor
            ADD_FAILURE() << "No interfaces detected.";
        }

        valid_iface_ = ifaces.begin()->getName();
        bogus_iface_ = "nonexisting0";

        if (IfaceMgr::instance().getIface(bogus_iface_)) {
            ADD_FAILURE() << "The '" << bogus_iface_ << "' exists on this system"
                          << " while the test assumes that it doesn't, to execute"
                          << " some negative scenarios. Can't continue this test.";
        }
    }

    ~Dhcp6ParserTest() {
        // Reset configuration database after each test.
        resetConfiguration();
    };

    // Checks if config_result (result of DHCP server configuration) has
    // expected code (0 for success, other for failures).
    // Also stores result in rcode_ and comment_.
    void checkResult(ConstElementPtr status, int expected_code) {
        ASSERT_TRUE(status);
        comment_ = parseAnswer(rcode_, status);
        EXPECT_EQ(expected_code, rcode_);
    }

    /// @brief Create the simple configuration with single option.
    ///
    /// This function allows to set one of the parameters that configure
    /// option value. These parameters are: "name", "code", "data" and
    /// "csv-format".
    ///
    /// @param param_value string holding option parameter value to be
    /// injected into the configuration string.
    /// @param parameter name of the parameter to be configured with
    /// param value.
    std::string createConfigWithOption(const std::string& param_value,
                                       const std::string& parameter) {
        std::map<std::string, std::string> params;
        if (parameter == "name") {
            params["name"] = param_value;
            params["space"] = "dhcp6";
            params["code"] = "38";
            params["data"] = "AB CDEF0105";
            params["csv-format"] = "False";
        } else if (parameter == "space") {
            params["name"] = "subscriber-id";
            params["space"] = param_value;
            params["code"] = "38";
            params["data"] = "AB CDEF0105";
            params["csv-format"] = "False";
        } else if (parameter == "code") {
            params["name"] = "subscriber-id";
            params["space"] = "dhcp6";
            params["code"] = param_value;
            params["data"] = "AB CDEF0105";
            params["csv-format"] = "False";
        } else if (parameter == "data") {
            params["name"] = "subscriber-id";
            params["space"] = "dhcp6";
            params["code"] = "38";
            params["data"] = param_value;
            params["csv-format"] = "False";
        } else if (parameter == "csv-format") {
            params["name"] = "subscriber-id";
            params["space"] = "dhcp6";
            params["code"] = "38";
            params["data"] = "AB CDEF0105";
            params["csv-format"] = param_value;
        }
        return (createConfigWithOption(params));
    }

    std::string createConfigWithOption(const std::map<std::string,
                                       std::string>& params)
    {
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
                // cppcheck-suppress unreadVariable
                first = false;
            }
            if (param.first == "name") {
                stream << "\"name\": \"" << param.second << "\"";
            } else if (param.first == "space") {
                stream << "\"space\": \"" << param.second << "\"";
            } else if (param.first == "code") {
                stream << "\"code\": " << param.second;;
            } else if (param.first == "data") {
                stream << "\"data\": \"" << param.second << "\"";
            } else if (param.first == "csv-format") {
                stream << "\"csv-format\": " << param.second;
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
            "\"option-def\": [ ], "
            "\"option-data\": [ ] }";

        try {
            ElementPtr json = Element::fromJSON(config);
            status = configureDhcp6Server(srv_, json);
        } catch (const std::exception& ex) {
            FAIL() << "Fatal error: unable to reset configuration database"
                   << " after the test. The following configuration was used"
                   << " to reset database: " << std::endl
                   << config << std::endl
                   << " and the following error message was returned:"
                   << ex.what() << std::endl;
        }

        // status object must not be NULL
        if (!status) {
            FAIL() << "Fatal error: unable to reset configuration database"
                   << " after the test. Configuration function returned"
                   << " NULL pointer" << std::endl;
        }
        comment_ = parseAnswer(rcode_, status);
        // returned value should be 0 (configuration success)
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
        EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
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
        // Verify that the data is correct. Do not verify suboptions and a header.
        const uint8_t* data = static_cast<const uint8_t*>(buf.getData());
        EXPECT_EQ(0, memcmp(expected_data, data + option_desc.option->getHeaderLen(),
                            expected_data_len));
    }

    int rcode_;
    Dhcpv6Srv srv_;

    ConstElementPtr comment_;

    string valid_iface_;
    string bogus_iface_;
};

// Goal of this test is a verification if a very simple config update
// with just a bumped version number. That's the simplest possible
// config update.
TEST_F(Dhcp6ParserTest, version) {

    ConstElementPtr x;

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_,
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

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_,
                    Element::fromJSON("{\"bogus\": 5}")));

    // returned value must be 1 (configuration parse error)
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    EXPECT_EQ(1, rcode_);
}

/// The goal of this test is to verify if configuration without any
/// subnets defined can be accepted.
TEST_F(Dhcp6ParserTest, emptySubnet) {

    ConstElementPtr status;

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_,
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

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

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

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

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

// This test checks if it is possible to define a subnet with an
// interface defined.
TEST_F(Dhcp6ParserTest, subnetInterface) {

    ConstElementPtr status;

    // There should be at least one interface

    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::1 - 2001:db8:1::ffff\" ],"
        "    \"interface\": \"" + valid_iface_ + "\","
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // returned value should be 0 (configuration success)
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    EXPECT_EQ(0, rcode_);

    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(valid_iface_, subnet->getIface());
}

// This test checks if invalid interface name will be rejected in
// Subnet6 definition.
TEST_F(Dhcp6ParserTest, subnetInterfaceBogus) {

    ConstElementPtr status;

    // There should be at least one interface

    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::1 - 2001:db8:1::ffff\" ],"
        "    \"interface\": \"" + bogus_iface_ + "\","
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // returned value should be 1 (configuration error)
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    EXPECT_EQ(1, rcode_);

    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
    EXPECT_FALSE(subnet);
}


// This test checks if it is not allowed to define global interface
// parameter.
TEST_F(Dhcp6ParserTest, interfaceGlobal) {

    ConstElementPtr status;

    string config = "{ \"interface\": [ \"all\" ],"
        "\"preferred-lifetime\": 3000,"
        "\"rebind-timer\": 2000, "
        "\"renew-timer\": 1000, "
        "\"interface\": \"" + valid_iface_ + "\"," // Not valid. Can be defined in subnet only
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::1 - 2001:db8:1::ffff\" ],"
        "    \"subnet\": \"2001:db8:1::/64\" } ],"
        "\"valid-lifetime\": 4000 }";
    cout << config << endl;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // returned value should be 1 (parse error)
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    EXPECT_EQ(1, rcode_);
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


    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));

    // returned value must be 1 (values error)
    // as the pool does not belong to that subnet
    ASSERT_TRUE(status);
    comment_ = parseAnswer(rcode_, status);
    EXPECT_EQ(1, rcode_);
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

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));

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

// The goal of this test is to check whether an option definition
// that defines an option carrying an IPv6 address can be created.
TEST_F(Dhcp6ParserTest, optionDefIpv6Address) {

    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"ipv6-address\","
        "      \"array\": False,"
        "      \"record-types\": \"\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    // Make sure that the particular option definition does not exist.
    OptionDefinitionPtr def = CfgMgr::instance().getOptionDef("isc", 100);
    ASSERT_FALSE(def);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);

    // The option definition should now be available in the CfgMgr.
    def = CfgMgr::instance().getOptionDef("isc", 100);
    ASSERT_TRUE(def);

    // Verify that the option definition data is valid.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(100, def->getCode());
    EXPECT_FALSE(def->getArrayType());
    EXPECT_EQ(OPT_IPV6_ADDRESS_TYPE, def->getType());
}

// The goal of this test is to check whether an option definition
// that defines an option carrying a record of data fields can
// be created.
TEST_F(Dhcp6ParserTest, optionDefRecord) {

    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"record\","
        "      \"array\": False,"
        "      \"record-types\": \"uint16, ipv4-address, ipv6-address, string\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    // Make sure that the particular option definition does not exist.
    OptionDefinitionPtr def = CfgMgr::instance().getOptionDef("isc", 100);
    ASSERT_FALSE(def);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // The option definition should now be available in the CfgMgr.
    def = CfgMgr::instance().getOptionDef("isc", 100);
    ASSERT_TRUE(def);

    // Check the option data.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(100, def->getCode());
    EXPECT_EQ(OPT_RECORD_TYPE, def->getType());
    EXPECT_FALSE(def->getArrayType());

    // The option comprises the record of data fields. Verify that all
    // fields are present and they are of the expected types.
    const OptionDefinition::RecordFieldsCollection& record_fields =
        def->getRecordFields();
    ASSERT_EQ(4, record_fields.size());
    EXPECT_EQ(OPT_UINT16_TYPE, record_fields[0]);
    EXPECT_EQ(OPT_IPV4_ADDRESS_TYPE, record_fields[1]);
    EXPECT_EQ(OPT_IPV6_ADDRESS_TYPE, record_fields[2]);
    EXPECT_EQ(OPT_STRING_TYPE, record_fields[3]);
}

// The goal of this test is to verify that multiple option definitions
// can be created.
TEST_F(Dhcp6ParserTest, optionDefMultiple) {
    // Configuration string.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"array\": False,"
        "      \"record-types\": \"\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"\""
        "  },"
        "  {"
        "      \"name\": \"foo-2\","
        "      \"code\": 101,"
        "      \"type\": \"ipv4-address\","
        "      \"array\": False,"
        "      \"record-types\": \"\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    // Make sure that the option definitions do not exist yet.
    ASSERT_FALSE(CfgMgr::instance().getOptionDef("isc", 100));
    ASSERT_FALSE(CfgMgr::instance().getOptionDef("isc", 101));

    // Use the configuration string to create new option definitions.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // Check the first definition we have created.
    OptionDefinitionPtr def1 = CfgMgr::instance().getOptionDef("isc", 100);
    ASSERT_TRUE(def1);

    // Check the option data.
    EXPECT_EQ("foo", def1->getName());
    EXPECT_EQ(100, def1->getCode());
    EXPECT_EQ(OPT_UINT32_TYPE, def1->getType());
    EXPECT_FALSE(def1->getArrayType());

    // Check the second option definition we have created.
    OptionDefinitionPtr def2 = CfgMgr::instance().getOptionDef("isc", 101);
    ASSERT_TRUE(def2);

    // Check the option data.
    EXPECT_EQ("foo-2", def2->getName());
    EXPECT_EQ(101, def2->getCode());
    EXPECT_EQ(OPT_IPV4_ADDRESS_TYPE, def2->getType());
    EXPECT_FALSE(def2->getArrayType());
}

// The goal of this test is to verify that the duplicated option
// definition is not accepted.
TEST_F(Dhcp6ParserTest, optionDefDuplicate) {

    // Configuration string. Both option definitions have
    // the same code and belong to the same option space.
    // This configuration should not be accepted.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"array\": False,"
        "      \"record-types\": \"\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"\""
        "  },"
        "  {"
        "      \"name\": \"foo-2\","
        "      \"code\": 100,"
        "      \"type\": \"ipv4-address\","
        "      \"array\": False,"
        "      \"record-types\": \"\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    // Make sure that the option definition does not exist yet.
    ASSERT_FALSE(CfgMgr::instance().getOptionDef("isc", 100));

    // Use the configuration string to create new option definitions.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 1);
}

// The goal of this test is to verify that the option definition
// comprising an array of uint32 values can be created.
TEST_F(Dhcp6ParserTest, optionDefArray) {

    // Configuration string. Created option definition should
    // comprise an array of uint32 values.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"array\": True,"
        "      \"record-types\": \"\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    // Make sure that the particular option definition does not exist.
    OptionDefinitionPtr def = CfgMgr::instance().getOptionDef("isc", 100);
    ASSERT_FALSE(def);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // The option definition should now be available in the CfgMgr.
    def = CfgMgr::instance().getOptionDef("isc", 100);
    ASSERT_TRUE(def);

    // Check the option data.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(100, def->getCode());
    EXPECT_EQ(OPT_UINT32_TYPE, def->getType());
    EXPECT_TRUE(def->getArrayType());
}

// The purpose of this test to verify that encapsulated option
// space name may be specified.
TEST_F(Dhcp6ParserTest, optionDefEncapsulate) {

    // Configuration string. Included the encapsulated
    // option space name.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"array\": False,"
        "      \"record-types\": \"\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"sub-opts-space\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    // Make sure that the particular option definition does not exist.
    OptionDefinitionPtr def = CfgMgr::instance().getOptionDef("isc", 100);
    ASSERT_FALSE(def);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // The option definition should now be available in the CfgMgr.
    def = CfgMgr::instance().getOptionDef("isc", 100);
    ASSERT_TRUE(def);

    // Check the option data.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(100, def->getCode());
    EXPECT_EQ(OPT_UINT32_TYPE, def->getType());
    EXPECT_FALSE(def->getArrayType());
    EXPECT_EQ("sub-opts-space", def->getEncapsulatedSpace());
}

/// The purpose of this test is to verify that the option definition
/// with invalid name is not accepted.
TEST_F(Dhcp6ParserTest, optionDefInvalidName) {
    // Configuration string. The option name is invalid as it
    // contains the % character.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"invalid%name\","
        "      \"code\": 100,"
        "      \"type\": \"string\","
        "      \"array\": False,"
        "      \"record-types\": \"\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
}

/// The purpose of this test is to verify that the option definition
/// with invalid type is not accepted.
TEST_F(Dhcp6ParserTest, optionDefInvalidType) {
    // Configuration string. The option type is invalid. It is
    // "sting" instead of "string".
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"sting\","
        "      \"array\": False,"
        "      \"record-types\": \"\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
}

/// The purpose of this test is to verify that the option definition
/// with invalid type is not accepted.
TEST_F(Dhcp6ParserTest, optionDefInvalidRecordType) {
    // Configuration string. The third of the record fields
    // is invalid. It is "sting" instead of "string".
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"record\","
        "      \"array\": False,"
        "      \"record-types\": \"uint32,uint8,sting\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
}

/// The goal of this test is to verify that the invalid encapsulated
/// option space name is not accepted.
TEST_F(Dhcp6ParserTest, optionDefInvalidEncapsulatedSpace) {
    // Configuration string. The encapsulated option space
    // name is invalid (% character is not allowed).
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"array\": False,"
        "      \"record-types\": \"\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"invalid%space%name\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
}

/// The goal of this test is to verify that the encapsulated
/// option space name can't be specified for the option that
/// comprises an array of data fields.
TEST_F(Dhcp6ParserTest, optionDefEncapsulatedSpaceAndArray) {
    // Configuration string. The encapsulated option space
    // name is set to non-empty value and the array flag
    // is set.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"array\": True,"
        "      \"record-types\": \"\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"valid-space-name\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
}

/// The goal of this test is to verify that the option may not
/// encapsulate option space it belongs to.
TEST_F(Dhcp6ParserTest, optionDefEncapsulateOwnSpace) {
    // Configuration string. Option is set to encapsulate
    // option space it belongs to.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"uint32\","
        "      \"array\": False,"
        "      \"record-types\": \"\","
        "      \"space\": \"isc\","
        "      \"encapsulate\": \"isc\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
}

/// The purpose of this test is to verify that it is not allowed
/// to override the standard option (that belongs to dhcp6 option
/// space) and that it is allowed to define option in the dhcp6
/// option space that has a code which is not used by any of the
/// standard options.
TEST_F(Dhcp6ParserTest, optionStandardDefOverride) {

    // Configuration string. The option code 100 is unassigned
    // so it can be used for a custom option definition in
    // dhcp6 option space.
    std::string config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 100,"
        "      \"type\": \"string\","
        "      \"array\": False,"
        "      \"record-types\": \"\","
        "      \"space\": \"dhcp6\","
        "      \"encapsulate\": \"\""
        "  } ]"
        "}";
    ElementPtr json = Element::fromJSON(config);

    OptionDefinitionPtr def = CfgMgr::instance().getOptionDef("dhcp6", 100);
    ASSERT_FALSE(def);

    // Use the configuration string to create new option definition.
    ConstElementPtr status;
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // The option definition should now be available in the CfgMgr.
    def = CfgMgr::instance().getOptionDef("dhcp6", 100);
    ASSERT_TRUE(def);

    // Check the option data.
    EXPECT_EQ("foo", def->getName());
    EXPECT_EQ(100, def->getCode());
    EXPECT_EQ(OPT_STRING_TYPE, def->getType());
    EXPECT_FALSE(def->getArrayType());

    // The combination of option space and code is
    // invalid. The 'dhcp6' option space groups
    // standard options and the code 3 is reserved
    // for one of them.
    config =
        "{ \"option-def\": [ {"
        "      \"name\": \"foo\","
        "      \"code\": 3,"
        "      \"type\": \"string\","
        "      \"array\": False,"
        "      \"record-types\": \"\","
        "      \"space\": \"dhcp6\","
        "      \"encapsulate\": \"\""
        "  } ]"
        "}";
    json = Element::fromJSON(config);

    // Use the configuration string to create new option definition.
    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    // Expecting parsing error (error code 1).
    checkResult(status, 1);
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
        "    \"name\": \"subscriber-id\","
        "    \"space\": \"dhcp6\","
        "    \"code\": 38,"
        "    \"data\": \"AB CDEF0105\","
        "    \"csv-format\": False"
        " },"
        " {"
        "    \"name\": \"preference\","
        "    \"space\": \"dhcp6\","
        "    \"code\": 7,"
        "    \"data\": \"01\","
        "    \"csv-format\": True"
        " } ],"
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::/80\" ],"
        "    \"subnet\": \"2001:db8:1::/64\""
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);

    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(subnet);
    Subnet::OptionContainerPtr options = subnet->getOptionDescriptors("dhcp6");
    ASSERT_EQ(2, options->size());

    // Get the search index. Index #1 is to search using option code.
    const Subnet::OptionContainerTypeIndex& idx = options->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<Subnet::OptionContainerTypeIndex::const_iterator,
              Subnet::OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(D6O_SUBSCRIBER_ID);
    // Expect single option with the code equal to 38.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t subid_expected[] = {
        0xAB, 0xCD, 0xEF, 0x01, 0x05
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, D6O_SUBSCRIBER_ID, subid_expected,
               sizeof(subid_expected));

    range = idx.equal_range(D6O_PREFERENCE);
    ASSERT_EQ(1, std::distance(range.first, range.second));
    // Do another round of testing with second option.
    const uint8_t pref_expected[] = {
        0x01
    };
    testOption(*range.first, D6O_PREFERENCE, pref_expected,
               sizeof(pref_expected));

    // Check that options with other option codes are not returned.
    for (uint16_t code = 47; code < 57; ++code) {
        range = idx.equal_range(code);
        EXPECT_EQ(0, std::distance(range.first, range.second));
    }
}

/// The goal of this test is to verify that two options having the same
/// option code can be added to different option spaces.
TEST_F(Dhcp6ParserTest, optionDataTwoSpaces) {

    // This configuration string is to configure two options
    // sharing the code 56 and having different definitions
    // and belonging to the different option spaces.
    // The option definition must be provided for the
    // option that belongs to the 'isc' option space.
    // The definition is not required for the option that
    // belongs to the 'dhcp6' option space as it is the
    // standard option.
    string config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"subscriber-id\","
        "    \"space\": \"dhcp6\","
        "    \"code\": 38,"
        "    \"data\": \"AB CDEF0105\","
        "    \"csv-format\": False"
        " },"
        " {"
        "    \"name\": \"foo\","
        "    \"space\": \"isc\","
        "    \"code\": 38,"
        "    \"data\": \"1234\","
        "    \"csv-format\": True"
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"foo\","
        "    \"code\": 38,"
        "    \"type\": \"uint32\","
        "    \"array\": False,"
        "    \"record-types\": \"\","
        "    \"space\": \"isc\","
        "    \"encapsulate\": \"\""
        " } ],"
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::/80\" ],"
        "    \"subnet\": \"2001:db8:1::/64\""
        " } ]"
        "}";

    ConstElementPtr status;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // Options should be now available for the subnet.
    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(subnet);
    // Try to get the option from the space dhcp6.
    Subnet::OptionDescriptor desc1 = subnet->getOptionDescriptor("dhcp6", 38);
    ASSERT_TRUE(desc1.option);
    EXPECT_EQ(38, desc1.option->getType());
    // Try to get the option from the space isc.
    Subnet::OptionDescriptor desc2 = subnet->getOptionDescriptor("isc", 38);
    ASSERT_TRUE(desc2.option);
    EXPECT_EQ(38, desc1.option->getType());
    // Try to get the non-existing option from the non-existing
    // option space and  expect that option is not returned.
    Subnet::OptionDescriptor desc3 = subnet->getOptionDescriptor("non-existing", 38);
    ASSERT_FALSE(desc3.option);
}

// The goal of this test is to verify that it is possible to
// encapsulate option space containing some options with
// another option. In this test we create base option that
// encapsulates option space 'isc' that comprises two other
// options. Also, for all options their definitions are
// created.
TEST_F(Dhcp6ParserTest, optionDataEncapsulate) {

    // @todo DHCP configurations has many dependencies between
    // parameters. First of all, configuration for subnet is
    // inherited from the global values. Thus subnet has to be
    // configured when all global values have been configured.
    // Also, an option can encapsulate another option only
    // if the latter has been configured. For this reason in this
    // test we created two-stage configuration where first we
    // created options that belong to encapsulated option space.
    // In the second stage we add the base option. Also, the Subnet
    // object is configured in the second stage so it is created
    // at the very end (when all other parameters are configured).

    // Starting stage 1. Configure sub-options and their definitions.
    string config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"foo\","
        "    \"space\": \"isc\","
        "    \"code\": 110,"
        "    \"data\": \"1234\","
        "    \"csv-format\": True"
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"space\": \"isc\","
        "    \"code\": 111,"
        "    \"data\": \"192.168.2.1\","
        "    \"csv-format\": True"
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"foo\","
        "    \"code\": 110,"
        "    \"type\": \"uint32\","
        "    \"array\": False,"
        "    \"record-types\": \"\","
        "    \"space\": \"isc\","
        "    \"encapsulate\": \"\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"code\": 111,"
        "    \"type\": \"ipv4-address\","
        "    \"array\": False,"
        "    \"record-types\": \"\","
        "    \"space\": \"isc\","
        "    \"encapsulate\": \"\""
        " } ]"
        "}";

    ConstElementPtr status;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // Stage 2. Configure base option and a subnet. Please note that
    // the configuration from the stage 2 is repeated because BIND
    // configuration manager sends whole configuration for the lists
    // where at least one element is being modified or added.
    config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"base-option\","
        "    \"space\": \"dhcp6\","
        "    \"code\": 100,"
        "    \"data\": \"11\","
        "    \"csv-format\": True"
        " },"
        " {"
        "    \"name\": \"foo\","
        "    \"space\": \"isc\","
        "    \"code\": 110,"
        "    \"data\": \"1234\","
        "    \"csv-format\": True"
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"space\": \"isc\","
        "    \"code\": 111,"
        "    \"data\": \"192.168.2.1\","
        "    \"csv-format\": True"
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"base-option\","
        "    \"code\": 100,"
        "    \"type\": \"uint8\","
        "    \"array\": False,"
        "    \"record-types\": \"\","
        "    \"space\": \"dhcp6\","
        "    \"encapsulate\": \"isc\""
        "},"
        "{"
        "    \"name\": \"foo\","
        "    \"code\": 110,"
        "    \"type\": \"uint32\","
        "    \"array\": False,"
        "    \"record-types\": \"\","
        "    \"space\": \"isc\","
        "    \"encapsulate\": \"\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"code\": 111,"
        "    \"type\": \"ipv4-address\","
        "    \"array\": False,"
        "    \"record-types\": \"\","
        "    \"space\": \"isc\","
        "    \"encapsulate\": \"\""
        " } ],"
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::/80\" ],"
        "    \"subnet\": \"2001:db8:1::/64\""
        " } ]"
        "}";


    json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // Get the subnet.
    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(subnet);

    // We should have one option available.
    Subnet::OptionContainerPtr options = subnet->getOptionDescriptors("dhcp6");
    ASSERT_TRUE(options);
    ASSERT_EQ(1, options->size());

    // Get the option.
    Subnet::OptionDescriptor desc = subnet->getOptionDescriptor("dhcp6", 100);
    EXPECT_TRUE(desc.option);
    EXPECT_EQ(100, desc.option->getType());

    // This opton should comprise two sub-options.
    // Onf of them is 'foo' with code 110.
    OptionPtr option_foo = desc.option->getOption(110);
    ASSERT_TRUE(option_foo);
    EXPECT_EQ(110, option_foo->getType());

    // ...another one 'foo2' with code 111.
    OptionPtr option_foo2 = desc.option->getOption(111);
    ASSERT_TRUE(option_foo2);
    EXPECT_EQ(111, option_foo2->getType());
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
        "          \"name\": \"subscriber-id\","
        "          \"space\": \"dhcp6\","
        "          \"code\": 38,"
        "          \"data\": \"0102030405060708090A\","
        "          \"csv-format\": False"
        "        } ]"
        " },"
        " {"
        "    \"pool\": [ \"2001:db8:2::/80\" ],"
        "    \"subnet\": \"2001:db8:2::/64\", "
        "    \"option-data\": [ {"
        "          \"name\": \"user-class\","
        "          \"space\": \"dhcp6\","
        "          \"code\": 15,"
        "          \"data\": \"FFFEFDFCFB\","
        "          \"csv-format\": False"
        "        } ]"
        " } ],"
        "\"valid-lifetime\": 4000 }";

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);

    Subnet6Ptr subnet1 = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(subnet1);
    Subnet::OptionContainerPtr options1 = subnet1->getOptionDescriptors("dhcp6");
    ASSERT_EQ(1, options1->size());

    // Get the search index. Index #1 is to search using option code.
    const Subnet::OptionContainerTypeIndex& idx1 = options1->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<Subnet::OptionContainerTypeIndex::const_iterator,
              Subnet::OptionContainerTypeIndex::const_iterator> range1 =
        idx1.equal_range(D6O_SUBSCRIBER_ID);
    // Expect single option with the code equal to 38.
    ASSERT_EQ(1, std::distance(range1.first, range1.second));
    const uint8_t subid_expected[] = {
        0x01, 0x02, 0x03, 0x04, 0x05,
        0x06, 0x07, 0x08, 0x09, 0x0A
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range1.first, D6O_SUBSCRIBER_ID, subid_expected,
               sizeof(subid_expected));

    // Test another subnet in the same way.
    Subnet6Ptr subnet2 = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:2::4"));
    ASSERT_TRUE(subnet2);
    Subnet::OptionContainerPtr options2 = subnet2->getOptionDescriptors("dhcp6");
    ASSERT_EQ(1, options2->size());

    const Subnet::OptionContainerTypeIndex& idx2 = options2->get<1>();
    std::pair<Subnet::OptionContainerTypeIndex::const_iterator,
              Subnet::OptionContainerTypeIndex::const_iterator> range2 =
        idx2.equal_range(D6O_USER_CLASS);
    ASSERT_EQ(1, std::distance(range2.first, range2.second));

    const uint8_t user_class_expected[] = {
        0xFF, 0xFE, 0xFD, 0xFC, 0xFB
    };
    testOption(*range2.first, D6O_USER_CLASS, user_class_expected,
               sizeof(user_class_expected));
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

// Verify that option data containing '0x' prefix is rejected
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

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);

    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(subnet);
    Subnet::OptionContainerPtr options = subnet->getOptionDescriptors("dhcp6");
    ASSERT_EQ(1, options->size());

    // Get the search index. Index #1 is to search using option code.
    const Subnet::OptionContainerTypeIndex& idx = options->get<1>();

    // Get the options for specified index. Expecting one option to be
    // returned but in theory we may have multiple options with the same
    // code so we get the range.
    std::pair<Subnet::OptionContainerTypeIndex::const_iterator,
              Subnet::OptionContainerTypeIndex::const_iterator> range =
        idx.equal_range(D6O_SUBSCRIBER_ID);
    // Expect single option with the code equal to 38.
    ASSERT_EQ(1, std::distance(range.first, range.second));
    const uint8_t subid_expected[] = {
        0x0A, 0x0B, 0x0C, 0x0D
    };
    // Check if option is valid in terms of code and carried data.
    testOption(*range.first, D6O_SUBSCRIBER_ID, subid_expected,
               sizeof(subid_expected));
}

// Verify that specific option object is returned for standard
// option which has dedicated option class derived from Option.
TEST_F(Dhcp6ParserTest, stdOptionData) {
    ConstElementPtr x;
    std::map<std::string, std::string> params;
    params["name"] = "ia-na";
    params["space"] = "dhcp6";
    // Option code 3 means OPTION_IA_NA.
    params["code"] = "3";
    params["data"] = "12345, 6789, 1516";
    params["csv-format"] = "True";

    std::string config = createConfigWithOption(params);
    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(x = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(x);
    comment_ = parseAnswer(rcode_, x);
    ASSERT_EQ(0, rcode_);

    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(subnet);
    Subnet::OptionContainerPtr options = subnet->getOptionDescriptors("dhcp6");
    ASSERT_EQ(1, options->size());

    // Get the search index. Index #1 is to search using option code.
    const Subnet::OptionContainerTypeIndex& idx = options->get<1>();

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
    // different type than Option6IA. This is wrong.
    ASSERT_TRUE(optionIA);
    // If cast was successful we may use accessors exposed by
    // Option6IA to validate that the content of this option
    // has been set correctly.
    EXPECT_EQ(12345, optionIA->getIAID());
    EXPECT_EQ(6789, optionIA->getT1());
    EXPECT_EQ(1516, optionIA->getT2());
}

// The goal of this test is to verify that the standard option can
// be configured to encapsulate multiple other options.
TEST_F(Dhcp6ParserTest, stdOptionDataEncapsulate) {

    // The configuration is two stage process in this test.
    // In the first stahe we create definitions of suboptions
    // that we will add to the base option.
    // Let's create some dummy options: foo and foo2.
    string config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"foo\","
        "    \"space\": \"vendor-opts-space\","
        "    \"code\": 110,"
        "    \"data\": \"1234\","
        "    \"csv-format\": True"
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"space\": \"vendor-opts-space\","
        "    \"code\": 111,"
        "    \"data\": \"192.168.2.1\","
        "    \"csv-format\": True"
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"foo\","
        "    \"code\": 110,"
        "    \"type\": \"uint32\","
        "    \"array\": False,"
        "    \"record-types\": \"\","
        "    \"space\": \"vendor-opts-space\","
        "    \"encapsulate\": \"\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"code\": 111,"
        "    \"type\": \"ipv4-address\","
        "    \"array\": False,"
        "    \"record-types\": \"\","
        "    \"space\": \"vendor-opts-space\","
        "    \"encapsulate\": \"\""
        " } ]"
        "}";

    ConstElementPtr status;

    ElementPtr json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // Once the definitions have been added we can configure the
    // standard option #17. This option comprises an enterprise
    // number and sub options. By convention (introduced in
    // std_option_defs.h) option named 'vendor-opts'
    // encapsulates the option space named 'vendor-opts-space'.
    // We add our dummy options to this option space and thus
    // they should be included as sub-options in the 'vendor-opts'
    // option.
    config = "{ \"interface\": [ \"all\" ],"
        "\"rebind-timer\": 2000,"
        "\"renew-timer\": 1000,"
        "\"option-data\": [ {"
        "    \"name\": \"vendor-opts\","
        "    \"space\": \"dhcp6\","
        "    \"code\": 17,"
        "    \"data\": \"1234\","
        "    \"csv-format\": True"
        " },"
        " {"
        "    \"name\": \"foo\","
        "    \"space\": \"vendor-opts-space\","
        "    \"code\": 110,"
        "    \"data\": \"1234\","
        "    \"csv-format\": True"
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"space\": \"vendor-opts-space\","
        "    \"code\": 111,"
        "    \"data\": \"192.168.2.1\","
        "    \"csv-format\": True"
        " } ],"
        "\"option-def\": [ {"
        "    \"name\": \"foo\","
        "    \"code\": 110,"
        "    \"type\": \"uint32\","
        "    \"array\": False,"
        "    \"record-types\": \"\","
        "    \"space\": \"vendor-opts-space\","
        "    \"encapsulate\": \"\""
        " },"
        " {"
        "    \"name\": \"foo2\","
        "    \"code\": 111,"
        "    \"type\": \"ipv4-address\","
        "    \"array\": False,"
        "    \"record-types\": \"\","
        "    \"space\": \"vendor-opts-space\","
        "    \"encapsulate\": \"\""
        " } ],"
        "\"subnet6\": [ { "
        "    \"pool\": [ \"2001:db8:1::/80\" ],"
        "    \"subnet\": \"2001:db8:1::/64\""
        " } ]"
        "}";


    json = Element::fromJSON(config);

    EXPECT_NO_THROW(status = configureDhcp6Server(srv_, json));
    ASSERT_TRUE(status);
    checkResult(status, 0);

    // Get the subnet.
    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(subnet);

    // We should have one option available.
    Subnet::OptionContainerPtr options = subnet->getOptionDescriptors("dhcp6");
    ASSERT_TRUE(options);
    ASSERT_EQ(1, options->size());

    // Get the option.
    Subnet::OptionDescriptor desc =
        subnet->getOptionDescriptor("dhcp6", D6O_VENDOR_OPTS);
    EXPECT_TRUE(desc.option);
    EXPECT_EQ(D6O_VENDOR_OPTS, desc.option->getType());

    // Option with the code 110 should be added as a sub-option.
    OptionPtr option_foo = desc.option->getOption(110);
    ASSERT_TRUE(option_foo);
    EXPECT_EQ(110, option_foo->getType());
    // This option comprises a single uint32_t value thus it is
    // represented by OptionInt<uint32_t> class. Let's get the
    // object of this type.
    boost::shared_ptr<OptionInt<uint32_t> > option_foo_uint32 =
        boost::dynamic_pointer_cast<OptionInt<uint32_t> >(option_foo);
    ASSERT_TRUE(option_foo_uint32);
    // Validate the value according to the configuration.
    EXPECT_EQ(1234, option_foo_uint32->getValue());

    // Option with the code 111 should be added as a sub-option.
    OptionPtr option_foo2 = desc.option->getOption(111);
    ASSERT_TRUE(option_foo2);
    EXPECT_EQ(111, option_foo2->getType());
    // This option comprises the IPV4 address. Such option is
    // represented by OptionCustom object.
    OptionCustomPtr option_foo2_v4 =
        boost::dynamic_pointer_cast<OptionCustom>(option_foo2);
    ASSERT_TRUE(option_foo2_v4);
    // Get the IP address carried by this option and validate it.
    EXPECT_EQ("192.168.2.1", option_foo2_v4->readAddress().toText());

    // Option with the code 112 should not be added.
    EXPECT_FALSE(desc.option->getOption(112));
}

};
