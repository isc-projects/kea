// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcp_parsers.h>
#include <exceptions/exceptions.h>
#include <dhcp/dhcp6.h>
#include <dhcp/tests/iface_mgr_test_config.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::util;
using namespace isc;

// don't import the entire boost namespace.  It will unexpectedly hide uint8_t
// for some systems.
using boost::scoped_ptr;

namespace {

template <typename Storage>
bool isZeroPosition(const Storage& storage, const std::string& param_name) {
    Element::Position position = storage.getPosition(param_name);
    return ((position.line_ == 0) && (position.pos_ == 0) &&
            (position.file_.empty()));
}

// This test verifies that BooleanStorage functions properly.
TEST(ValueStorageTest, BooleanTesting) {
    BooleanStorage testStore;

    // Verify that we can add and retrieve parameters.
    testStore.setParam("firstBool", false, Element::Position("kea.conf", 123, 234));
    testStore.setParam("secondBool", true, Element::Position("keax.conf", 10, 20));

    EXPECT_FALSE(testStore.getParam("firstBool"));
    EXPECT_TRUE(testStore.getParam("secondBool"));

    EXPECT_EQ(123, testStore.getPosition("firstBool").line_);
    EXPECT_EQ(234, testStore.getPosition("firstBool").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("firstBool").file_);

    EXPECT_EQ(10, testStore.getPosition("secondBool").line_);
    EXPECT_EQ(20, testStore.getPosition("secondBool").pos_);
    EXPECT_EQ("keax.conf", testStore.getPosition("secondBool").file_);

    // Verify that we can update parameters.
    testStore.setParam("firstBool", true, Element::Position("keax.conf", 555, 111));
    testStore.setParam("secondBool", false, Element::Position("kea.conf", 1, 3));

    EXPECT_TRUE(testStore.getParam("firstBool"));
    EXPECT_FALSE(testStore.getParam("secondBool"));

    EXPECT_EQ(555, testStore.getPosition("firstBool").line_);
    EXPECT_EQ(111, testStore.getPosition("firstBool").pos_);
    EXPECT_EQ("keax.conf", testStore.getPosition("firstBool").file_);

    EXPECT_EQ(1, testStore.getPosition("secondBool").line_);
    EXPECT_EQ(3, testStore.getPosition("secondBool").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("secondBool").file_);

    // Verify that we can delete a parameter and it will no longer be found.
    testStore.delParam("firstBool");
    EXPECT_THROW(testStore.getParam("firstBool"), isc::dhcp::DhcpConfigError);

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "firstBool"));

    // Verify that the delete was safe and the store still operates.
    EXPECT_FALSE(testStore.getParam("secondBool"));

    EXPECT_EQ(1, testStore.getPosition("secondBool").line_);
    EXPECT_EQ(3, testStore.getPosition("secondBool").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("secondBool").file_);

    // Verify that looking for a parameter that never existed throws.
    ASSERT_THROW(testStore.getParam("bogusBool"), isc::dhcp::DhcpConfigError);

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "bogusBool"));

    // Verify that attempting to delete a parameter that never existed does not throw.
    EXPECT_NO_THROW(testStore.delParam("bogusBool"));

    // Verify that we can empty the list.
    testStore.clear();
    EXPECT_THROW(testStore.getParam("secondBool"), isc::dhcp::DhcpConfigError);

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "secondBool"));
}

// This test verifies that Uint32Storage functions properly.
TEST(ValueStorageTest, Uint32Testing) {
    Uint32Storage testStore;

    uint32_t int_one = 77;
    uint32_t int_two = 33;

    // Verify that we can add and retrieve parameters.
    testStore.setParam("firstInt", int_one, Element::Position("kea.conf", 123, 234));
    testStore.setParam("secondInt", int_two, Element::Position("keax.conf", 10, 20));

    EXPECT_EQ(testStore.getParam("firstInt"), int_one);
    EXPECT_EQ(testStore.getParam("secondInt"), int_two);

    EXPECT_EQ(123, testStore.getPosition("firstInt").line_);
    EXPECT_EQ(234, testStore.getPosition("firstInt").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("firstInt").file_);

    EXPECT_EQ(10, testStore.getPosition("secondInt").line_);
    EXPECT_EQ(20, testStore.getPosition("secondInt").pos_);
    EXPECT_EQ("keax.conf", testStore.getPosition("secondInt").file_);

    // Verify that we can update parameters.
    testStore.setParam("firstInt", --int_one, Element::Position("keax.conf", 555, 111));
    testStore.setParam("secondInt", ++int_two, Element::Position("kea.conf", 1, 3));

    EXPECT_EQ(testStore.getParam("firstInt"), int_one);
    EXPECT_EQ(testStore.getParam("secondInt"), int_two);

    EXPECT_EQ(555, testStore.getPosition("firstInt").line_);
    EXPECT_EQ(111, testStore.getPosition("firstInt").pos_);
    EXPECT_EQ("keax.conf", testStore.getPosition("firstInt").file_);

    EXPECT_EQ(1, testStore.getPosition("secondInt").line_);
    EXPECT_EQ(3, testStore.getPosition("secondInt").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("secondInt").file_);

    // Verify that we can delete a parameter and it will no longer be found.
    testStore.delParam("firstInt");
    EXPECT_THROW(testStore.getParam("firstInt"), isc::dhcp::DhcpConfigError);

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "firstInt"));

    // Verify that the delete was safe and the store still operates.
    EXPECT_EQ(testStore.getParam("secondInt"), int_two);

    EXPECT_EQ(1, testStore.getPosition("secondInt").line_);
    EXPECT_EQ(3, testStore.getPosition("secondInt").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("secondInt").file_);

    // Verify that looking for a parameter that never existed throws.
    ASSERT_THROW(testStore.getParam("bogusInt"), isc::dhcp::DhcpConfigError);

    // Verify that attempting to delete a parameter that never existed does not throw.
    EXPECT_NO_THROW(testStore.delParam("bogusInt"));

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "bogusInt"));

    // Verify that we can empty the list.
    testStore.clear();
    EXPECT_THROW(testStore.getParam("secondInt"), isc::dhcp::DhcpConfigError);

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "secondInt"));
}

// This test verifies that StringStorage functions properly.
TEST(ValueStorageTest, StringTesting) {
    StringStorage testStore;

    std::string string_one = "seventy-seven";
    std::string string_two = "thirty-three";

    // Verify that we can add and retrieve parameters.
    testStore.setParam("firstString", string_one,
                       Element::Position("kea.conf", 123, 234));
    testStore.setParam("secondString", string_two,
                       Element::Position("keax.conf", 10, 20));

    EXPECT_EQ(testStore.getParam("firstString"), string_one);
    EXPECT_EQ(testStore.getParam("secondString"), string_two);

    EXPECT_EQ(123, testStore.getPosition("firstString").line_);
    EXPECT_EQ(234, testStore.getPosition("firstString").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("firstString").file_);

    EXPECT_EQ(10, testStore.getPosition("secondString").line_);
    EXPECT_EQ(20, testStore.getPosition("secondString").pos_);
    EXPECT_EQ("keax.conf", testStore.getPosition("secondString").file_);

    // Verify that we can update parameters.
    string_one.append("-boo");
    string_two.append("-boo");

    testStore.setParam("firstString", string_one,
                       Element::Position("kea.conf", 555, 111));
    testStore.setParam("secondString", string_two,
                       Element::Position("keax.conf", 1, 3));

    EXPECT_EQ(testStore.getParam("firstString"), string_one);
    EXPECT_EQ(testStore.getParam("secondString"), string_two);

    EXPECT_EQ(555, testStore.getPosition("firstString").line_);
    EXPECT_EQ(111, testStore.getPosition("firstString").pos_);
    EXPECT_EQ("kea.conf", testStore.getPosition("firstString").file_);

    EXPECT_EQ(1, testStore.getPosition("secondString").line_);
    EXPECT_EQ(3, testStore.getPosition("secondString").pos_);
    EXPECT_EQ("keax.conf", testStore.getPosition("secondString").file_);

    // Verify that we can delete a parameter and it will no longer be found.
    testStore.delParam("firstString");
    EXPECT_THROW(testStore.getParam("firstString"), isc::dhcp::DhcpConfigError);

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "firstString"));

    // Verify that the delete was safe and the store still operates.
    EXPECT_EQ(testStore.getParam("secondString"), string_two);

    EXPECT_EQ(1, testStore.getPosition("secondString").line_);
    EXPECT_EQ(3, testStore.getPosition("secondString").pos_);
    EXPECT_EQ("keax.conf", testStore.getPosition("secondString").file_);

    // Verify that looking for a parameter that never existed throws.
    ASSERT_THROW(testStore.getParam("bogusString"), isc::dhcp::DhcpConfigError);

    // Verify that attempting to delete a parameter that never existed does not throw.
    EXPECT_NO_THROW(testStore.delParam("bogusString"));

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "bogusString"));

    // Verify that we can empty the list.
    testStore.clear();
    EXPECT_THROW(testStore.getParam("secondString"), isc::dhcp::DhcpConfigError);

    // Verify that the "zero" position is returned when parameter doesn't exist.
    EXPECT_TRUE(isZeroPosition(testStore, "secondString"));
}



class CfgMgrTest : public ::testing::Test {
public:
    CfgMgrTest() {
        // make sure we start with a clean configuration
        clear();
    }

    /// @brief generates interface-id option based on provided text
    ///
    /// @param text content of the option to be created
    ///
    /// @return pointer to the option object created
    OptionPtr generateInterfaceId(const string& text) {
        OptionBuffer buffer(text.begin(), text.end());
        return OptionPtr(new Option(Option::V6, D6O_INTERFACE_ID, buffer));
    }

    ~CfgMgrTest() {
        // clean up after the test
        clear();
    }

    void clear() {
        CfgMgr::instance().deleteSubnets4();
        CfgMgr::instance().deleteSubnets6();
        CfgMgr::instance().deleteOptionDefs();
        CfgMgr::instance().clear();
    }

    /// used in client classification (or just empty container for other tests)
    isc::dhcp::ClientClasses classify_;
};

// Checks that there is a configuration structure available and that
// it is empty by default.
TEST_F(CfgMgrTest, configuration) {

    ConstConfigurationPtr configuration = CfgMgr::instance().getCurrentCfg();
    ASSERT_TRUE(configuration);
    EXPECT_TRUE(configuration->getLoggingInfo().empty());

    configuration = CfgMgr::instance().getStagingCfg();
    ASSERT_TRUE(configuration);
    EXPECT_TRUE(configuration->getLoggingInfo().empty());
}

// This test verifies that multiple option definitions can be added
// under different option spaces.
TEST_F(CfgMgrTest, getOptionDefs) {
    CfgMgr& cfg_mgr = CfgMgr::instance();
    // Create a set of option definitions with codes between 100 and 109.
    for (uint16_t code = 100; code < 110; ++code) {
        std::ostringstream option_name;
        // Option name is unique, e.g. option-100, option-101 etc.
        option_name << "option-" << code;
        OptionDefinitionPtr def(new OptionDefinition(option_name.str(), code,
                                                     "uint16"));
        // Add option definition to "isc" option space.
        // Option codes are not duplicated so expect no error
        // when adding them.
        ASSERT_NO_THROW(cfg_mgr.addOptionDef(def, "isc"));
    }

    // Create a set of option definitions with codes between 105 and 114 and
    // add them to the different option space.
    for (uint16_t code = 105; code < 115; ++code) {
        std::ostringstream option_name;
        option_name << "option-" << code;
        OptionDefinitionPtr def(new OptionDefinition(option_name.str(), code,
                                                     "uint16"));
        ASSERT_NO_THROW(cfg_mgr.addOptionDef(def, "abcde"));
    }

    // Sanity check that all 10 option definitions are there.
    OptionDefContainerPtr option_defs1 = cfg_mgr.getOptionDefs("isc");
    ASSERT_TRUE(option_defs1);
    ASSERT_EQ(10, option_defs1->size());

    // Iterate over all option definitions and check that they have
    // valid codes. Also, their order should be the same as they
    // were added (codes 100-109).
    uint16_t code = 100;
    for (OptionDefContainer::const_iterator it = option_defs1->begin();
         it != option_defs1->end(); ++it, ++code) {
        OptionDefinitionPtr def(*it);
        ASSERT_TRUE(def);
        EXPECT_EQ(code, def->getCode());
    }

    // Sanity check that all 10 option definitions are there.
    OptionDefContainerPtr option_defs2 = cfg_mgr.getOptionDefs("abcde");
    ASSERT_TRUE(option_defs2);
    ASSERT_EQ(10, option_defs2->size());

    // Check that the option codes are valid.
    code = 105;
    for (OptionDefContainer::const_iterator it = option_defs2->begin();
         it != option_defs2->end(); ++it, ++code) {
        OptionDefinitionPtr def(*it);
        ASSERT_TRUE(def);
        EXPECT_EQ(code, def->getCode());
    }

    // Let's make one more check that the empty set is returned when
    // invalid option space is used.
    OptionDefContainerPtr option_defs3 = cfg_mgr.getOptionDefs("non-existing");
    ASSERT_TRUE(option_defs3);
    EXPECT_TRUE(option_defs3->empty());
}

// This test verifies that single option definition is correctly
// returned with getOptionDef function.
TEST_F(CfgMgrTest, getOptionDef) {
    CfgMgr& cfg_mgr = CfgMgr::instance();
    // Create a set of option definitions with codes between 100 and 109.
    for (uint16_t code = 100; code < 110; ++code) {
        std::ostringstream option_name;
        // Option name is unique, e.g. option-100, option-101 etc.
        option_name << "option-" << code;
        OptionDefinitionPtr def(new OptionDefinition(option_name.str(), code,
                                                     "uint16"));
        // Add option definition to "isc" option space.
        // Option codes are not duplicated so expect no error
        // when adding them.
        ASSERT_NO_THROW(cfg_mgr.addOptionDef(def, "isc"));
    }

    // Create a set of option definitions with codes between 105 and 114 and
    // add them to the different option space.
    for (uint16_t code = 105; code < 115; ++code) {
        std::ostringstream option_name;
        option_name << "option-other-" << code;
        OptionDefinitionPtr def(new OptionDefinition(option_name.str(), code,
                                                     "uint16"));
        ASSERT_NO_THROW(cfg_mgr.addOptionDef(def, "abcde"));
    }

    // Try to get option definitions one by one using all codes
    // that we expect to be there.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionDefinitionPtr def = cfg_mgr.getOptionDef("isc", code);
        ASSERT_TRUE(def);
        // Check that the option name is in the format of 'option-[code]'.
        // That way we make sure that the options that have the same codes
        // within different option spaces are different.
        std::ostringstream option_name;
        option_name << "option-" << code;
        EXPECT_EQ(option_name.str(), def->getName());
        EXPECT_EQ(code, def->getCode());
    }

    // Check that the option codes are valid.
    for (uint16_t code = 105; code < 115; ++code) {
        OptionDefinitionPtr def = cfg_mgr.getOptionDef("abcde", code);
        ASSERT_TRUE(def);
        // Check that the option name is in the format of 'option-other-[code]'.
        // That way we make sure that the options that have the same codes
        // within different option spaces are different.
        std::ostringstream option_name;
        option_name << "option-other-" << code;
        EXPECT_EQ(option_name.str(), def->getName());

        EXPECT_EQ(code, def->getCode());
    }

    // Check that an option definition can be added to the standard
    // (dhcp4 and dhcp6) option spaces when the option code is not
    // reserved by the standard option.
    OptionDefinitionPtr def6(new OptionDefinition("option-foo", 79, "uint16"));
    EXPECT_NO_THROW(cfg_mgr.addOptionDef(def6, "dhcp6"));

    OptionDefinitionPtr def4(new OptionDefinition("option-foo", 222, "uint16"));
    EXPECT_NO_THROW(cfg_mgr.addOptionDef(def4, "dhcp4"));

    // Try to query the option definition from an non-existing
    // option space and expect NULL pointer.
    OptionDefinitionPtr def = cfg_mgr.getOptionDef("non-existing", 56);
    EXPECT_FALSE(def);

    // Try to get the non-existing option definition from an
    // existing option space.
    EXPECT_FALSE(cfg_mgr.getOptionDef("isc", 56));

}

// This test verifies that it is not allowed to override a definition of the
// standard option which has its definition defined in libdhcp++, but it is
// allowed to create a definition for the standard option which doesn't have
// its definition in libdhcp++.
TEST_F(CfgMgrTest, overrideStdOptionDef) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    OptionDefinitionPtr def;
    // There is a definition for routers option in libdhcp++, so an attempt
    // to add (override) another definition for this option should fail.
    def.reset(new OptionDefinition("routers", DHO_ROUTERS, "uint32"));
    EXPECT_THROW(cfg_mgr.addOptionDef(def, "dhcp4"), isc::BadValue);

    /// @todo There is no definition for the NIS Server Addr option in
    /// libdhcp++. Once it is implemented it should be not allowed to
    /// add a custom definition for it. At the moment, it should be ok
    /// to add a definition for this option (using configuration mechanism)
    /// because we haven't implemented the one in libdhcp++.
    def.reset(new OptionDefinition("nis-server-addr", 65, "uint16"));
    EXPECT_NO_THROW(cfg_mgr.addOptionDef(def, "dhcp4"));

    // It is not allowed to override the definition of the option which
    // has its definition in the libdhcp++.
    def.reset(new OptionDefinition("sntp-servers", D6O_SNTP_SERVERS,
                                   "ipv4-address"));
    EXPECT_THROW(cfg_mgr.addOptionDef(def, "dhcp6"), isc::BadValue);
    // There is no definition for option 59 in libdhcp++ yet, so it should
    // be possible provide a custom definition.
    def.reset(new OptionDefinition("bootfile-url", 59, "uint32"));
    EXPECT_NO_THROW(cfg_mgr.addOptionDef(def, "dhcp6"));

}

// This test verifies that the function that adds new option definition
// throws exceptions when arguments are invalid.
TEST_F(CfgMgrTest, addOptionDefNegative) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    OptionDefinitionPtr def(new OptionDefinition("option-foo", 1000, "uint16"));

    // Try empty option space name.
    ASSERT_THROW(cfg_mgr.addOptionDef(def, ""), isc::BadValue);
    // Try NULL option definition.
    ASSERT_THROW(cfg_mgr.addOptionDef(OptionDefinitionPtr(), "isc"),
                 isc::dhcp::MalformedOptionDefinition);
    // Try adding option definition twice and make sure that it
    // fails on the second attempt.
    ASSERT_NO_THROW(cfg_mgr.addOptionDef(def, "isc"));
    EXPECT_THROW(cfg_mgr.addOptionDef(def, "isc"), DuplicateOptionDefinition);
}

// This test verifies if the configuration manager is able to hold and return
// valid subnets.
TEST_F(CfgMgrTest, subnet4) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3));

    // There shouldn't be any subnet configured at this stage
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.0"), classify_));

    cfg_mgr.addSubnet4(subnet1);

    // Now we have only one subnet, any request will be served from it
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet4(IOAddress("192.0.2.63"),
                  classify_));

    // Now we add more subnets and check that both old and new subnets
    // are accessible.
    cfg_mgr.addSubnet4(subnet2);
    cfg_mgr.addSubnet4(subnet3);

    EXPECT_EQ(subnet3, cfg_mgr.getSubnet4(IOAddress("192.0.2.191"), classify_));
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet4(IOAddress("192.0.2.15"), classify_));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet4(IOAddress("192.0.2.85"), classify_));

    // Try to find an address that does not belong to any subnet
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.192"), classify_));

    // Check that deletion of the subnets works.
    cfg_mgr.deleteSubnets4();
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.191"), classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.15"), classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.85"), classify_));
}

// This test verifies if the configuration manager is able to hold subnets with
// their classifier information and return proper subnets, based on those
// classes.
TEST_F(CfgMgrTest, classifySubnet4) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    // Let's configure 3 subnets
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3));

    cfg_mgr.addSubnet4(subnet1);
    cfg_mgr.addSubnet4(subnet2);
    cfg_mgr.addSubnet4(subnet3);

    // Let's sanity check that we can use that configuration.
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet4(IOAddress("192.0.2.5"), classify_));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet4(IOAddress("192.0.2.70"), classify_));
    EXPECT_EQ(subnet3, cfg_mgr.getSubnet4(IOAddress("192.0.2.130"), classify_));

    // Client now belongs to bar class.
    classify_.insert("bar");

    // There are no class restrictions defined, so everything should work
    // as before
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet4(IOAddress("192.0.2.5"), classify_));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet4(IOAddress("192.0.2.70"), classify_));
    EXPECT_EQ(subnet3, cfg_mgr.getSubnet4(IOAddress("192.0.2.130"), classify_));

    // Now let's add client class restrictions.
    subnet1->allowClientClass("foo"); // Serve here only clients from foo class
    subnet2->allowClientClass("bar"); // Serve here only clients from bar class
    subnet3->allowClientClass("baz"); // Serve here only clients from baz class

    // The same check as above should result in client being served only in
    // bar class, i.e. subnet2
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.5"), classify_));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet4(IOAddress("192.0.2.70"), classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.130"), classify_));

    // Now let's check that client with wrong class is not supported
    classify_.clear();
    classify_.insert("some_other_class");
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.5"), classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.70"), classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.130"), classify_));

    // Finally, let's check that client without any classes is not supported
    classify_.clear();
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.5"), classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.70"), classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.130"), classify_));
}

// This test verifies if the configuration manager is able to hold v4 subnets
// with their relay address information and return proper subnets, based on
// those addresses.
TEST_F(CfgMgrTest, subnet4RelayOverride) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    // Let's configure 3 subnets
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3));

    cfg_mgr.addSubnet4(subnet1);
    cfg_mgr.addSubnet4(subnet2);
    cfg_mgr.addSubnet4(subnet3);

    // Check that without relay-info specified, subnets are not selected
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("10.0.0.1"), classify_, true));
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("10.0.0.2"), classify_, true));
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("10.0.0.3"), classify_, true));

    // Now specify relay info
    subnet1->setRelayInfo(IOAddress("10.0.0.1"));
    subnet2->setRelayInfo(IOAddress("10.0.0.2"));
    subnet3->setRelayInfo(IOAddress("10.0.0.3"));

    // And try again. This time relay-info is there and should match.
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet4(IOAddress("10.0.0.1"), classify_, true));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet4(IOAddress("10.0.0.2"), classify_, true));
    EXPECT_EQ(subnet3, cfg_mgr.getSubnet4(IOAddress("10.0.0.3"), classify_, true));

    // Finally, check that the relay works only if hint provided is relay address
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("10.0.0.1"), classify_, false));
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("10.0.0.2"), classify_, false));
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("10.0.0.3"), classify_, false));
}

// This test verifies if the configuration manager is able to hold v6 subnets
// with their relay address information and return proper subnets, based on
// those addresses.
TEST_F(CfgMgrTest, subnet6RelayOverride) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    // Let's configure 3 subnets
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:db8:3::"), 48, 1, 2, 3, 4));

    cfg_mgr.addSubnet6(subnet1);
    cfg_mgr.addSubnet6(subnet2);
    cfg_mgr.addSubnet6(subnet3);

    // Check that without relay-info specified, subnets are not selected
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("2001:db8:ff::1"), classify_, true));
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("2001:db8:ff::2"), classify_, true));
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("2001:db8:ff::3"), classify_, true));

    // Now specify relay info
    subnet1->setRelayInfo(IOAddress("2001:db8:ff::1"));
    subnet2->setRelayInfo(IOAddress("2001:db8:ff::2"));
    subnet3->setRelayInfo(IOAddress("2001:db8:ff::3"));

    // And try again. This time relay-info is there and should match.
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet6(IOAddress("2001:db8:ff::1"), classify_, true));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet6(IOAddress("2001:db8:ff::2"), classify_, true));
    EXPECT_EQ(subnet3, cfg_mgr.getSubnet6(IOAddress("2001:db8:ff::3"), classify_, true));

    // Finally, check that the relay works only if hint provided is relay address
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("2001:db8:ff::1"), classify_, false));
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("2001:db8:ff::2"), classify_, false));
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("2001:db8:ff::3"), classify_, false));
}


// This test verifies if the configuration manager is able to hold and return
// valid leases
TEST_F(CfgMgrTest, classifySubnet6) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    // Let's configure 3 subnets
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4));

    cfg_mgr.addSubnet6(subnet1);
    cfg_mgr.addSubnet6(subnet2);
    cfg_mgr.addSubnet6(subnet3);

    // Let's sanity check that we can use that configuration.
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet6(IOAddress("2000::123"), classify_));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet6(IOAddress("3000::345"), classify_));
    EXPECT_EQ(subnet3, cfg_mgr.getSubnet6(IOAddress("4000::567"), classify_));

    // Client now belongs to bar class.
    classify_.insert("bar");

    // There are no class restrictions defined, so everything should work
    // as before
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet6(IOAddress("2000::123"), classify_));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet6(IOAddress("3000::345"), classify_));
    EXPECT_EQ(subnet3, cfg_mgr.getSubnet6(IOAddress("4000::567"), classify_));

    // Now let's add client class restrictions.
    subnet1->allowClientClass("foo"); // Serve here only clients from foo class
    subnet2->allowClientClass("bar"); // Serve here only clients from bar class
    subnet3->allowClientClass("baz"); // Serve here only clients from baz class

    // The same check as above should result in client being served only in
    // bar class, i.e. subnet2
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("2000::123"), classify_));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet6(IOAddress("3000::345"), classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("4000::567"), classify_));

    // Now let's check that client with wrong class is not supported
    classify_.clear();
    classify_.insert("some_other_class");
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("2000::123"), classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("3000::345"), classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("4000::567"), classify_));

    // Finally, let's check that client without any classes is not supported
    classify_.clear();
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("2000::123"), classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("3000::345"), classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("4000::567"), classify_));
}

// This test verifies if the configuration manager is able to hold, select
// and return valid subnets, based on interface names along with client
// classification.
TEST_F(CfgMgrTest, classifySubnet6Interface) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    // Let's have an odd configuration: 3 shared subnets available on the
    // same direct link.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4));
    subnet1->setIface("foo");
    subnet2->setIface("foo");
    subnet3->setIface("foo");
    cfg_mgr.addSubnet6(subnet1);
    cfg_mgr.addSubnet6(subnet2);
    cfg_mgr.addSubnet6(subnet3);


    // Regular client should get the first subnet, because it meets all
    // criteria (matching interface name, no class restrictions.
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet6("foo", classify_));

    // Now let's add class requirements for subnet1
    subnet1->allowClientClass("alpha");

    // Client should now get the subnet2, because he no longer meets
    // requirements for subnet1 (belongs to wrong class)
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet6("foo", classify_));

    // Now let's add (not matching) classes to the other two subnets
    subnet2->allowClientClass("beta");
    subnet3->allowClientClass("gamma");

    // No subnets are suitable, so nothing will be selected
    EXPECT_FALSE(cfg_mgr.getSubnet6("foo", classify_));

    // Ok, let's add the client to gamme class, so he'll get a subnet
    classify_.insert("gamma");
    EXPECT_EQ(subnet3, cfg_mgr.getSubnet6("foo", classify_));
}

// This test verifies if the configuration manager is able to hold, select
// and return valid subnets, based on interface-id option inserted by relay,
// along with client classification.
TEST_F(CfgMgrTest, classifySubnet6InterfaceId) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    // Let's have an odd configuration: 3 shared subnets available via the
    // same remote relay with the same interface-id.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4));
    OptionPtr ifaceid = generateInterfaceId("relay1.eth0");
    subnet1->setInterfaceId(ifaceid);
    subnet2->setInterfaceId(ifaceid);
    subnet3->setInterfaceId(ifaceid);
    cfg_mgr.addSubnet6(subnet1);
    cfg_mgr.addSubnet6(subnet2);
    cfg_mgr.addSubnet6(subnet3);

    // Regular client should get the first subnet, because it meets all
    // criteria (matching interface name, no class restrictions.
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet6(ifaceid, classify_));

    // Now let's add class requirements for subnet1
    subnet1->allowClientClass("alpha");

    // Client should now get the subnet2, because he no longer meets
    // requirements for subnet1 (belongs to wrong class)
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet6(ifaceid, classify_));

    // Now let's add (not matching) classes to the other two subnets
    subnet2->allowClientClass("beta");
    subnet3->allowClientClass("gamma");

    // No subnets are suitable, so nothing will be selected
    EXPECT_FALSE(cfg_mgr.getSubnet6(ifaceid, classify_));

    // Ok, let's add the client to gamme class, so he'll get a subnet
    classify_.insert("gamma");
    EXPECT_EQ(subnet3, cfg_mgr.getSubnet6(ifaceid, classify_));
}

// This test verifies if the configuration manager is able to hold and return
// valid leases
TEST_F(CfgMgrTest, subnet6) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4));

    // There shouldn't be any subnet configured at this stage
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("2000::1"), classify_));

    cfg_mgr.addSubnet6(subnet1);

    // Now we have only one subnet, any request will be served from it
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet6(IOAddress("2000::1"), classify_));

    // We used to allow getting a sole subnet if there was only one subnet
    // configured. That is no longer true. The code should not return
    // a subnet.
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("fe80::dead:beef"), classify_));

    cfg_mgr.addSubnet6(subnet2);
    cfg_mgr.addSubnet6(subnet3);

    EXPECT_EQ(subnet3, cfg_mgr.getSubnet6(IOAddress("4000::123"), classify_));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet6(IOAddress("3000::dead:beef"),
                  classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("5000::1"), classify_));

    // Check that deletion of the subnets works.
    cfg_mgr.deleteSubnets6();
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("2000::123"), classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("3000::123"), classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("4000::123"), classify_));
}

// This test verifies if the configuration manager is able to hold, select
// and return valid subnets, based on interface names.
TEST_F(CfgMgrTest, subnet6Interface) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4));
    subnet1->setIface("foo");
    subnet2->setIface("bar");
    subnet3->setIface("foobar");

    // There shouldn't be any subnet configured at this stage
    EXPECT_FALSE(cfg_mgr.getSubnet6("foo", classify_));

    cfg_mgr.addSubnet6(subnet1);

    // Now we have only one subnet, any request will be served from it
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet6("foo", classify_));

    // Check that the interface name is checked even when there is
    // only one subnet defined.
    EXPECT_FALSE(cfg_mgr.getSubnet6("bar", classify_));

    // We used to allow getting a sole subnet if there was only one subnet
    // configured. That is no longer true. The code should not return
    // a subnet.
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("fe80::dead:beef"), classify_));

    cfg_mgr.addSubnet6(subnet2);
    cfg_mgr.addSubnet6(subnet3);

    EXPECT_EQ(subnet3, cfg_mgr.getSubnet6("foobar", classify_));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet6("bar", classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet6("xyzzy", classify_)); // no such interface

    // Check that deletion of the subnets works.
    cfg_mgr.deleteSubnets6();
    EXPECT_FALSE(cfg_mgr.getSubnet6("foo", classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet6("bar", classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet6("foobar", classify_));
}

// This test verifies if the configuration manager is able to hold, select
// and return valid leases, based on interface-id option values
TEST_F(CfgMgrTest, subnet6InterfaceId) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4));

    // interface-id options used in subnets 1,2, and 3
    OptionPtr ifaceid1 = generateInterfaceId("relay1.eth0");
    OptionPtr ifaceid2 = generateInterfaceId("VL32");
    // That's a strange interface-id, but this is a real life example
    OptionPtr ifaceid3 = generateInterfaceId("ISAM144|299|ipv6|nt:vp:1:110");

    // bogus interface-id
    OptionPtr ifaceid_bogus = generateInterfaceId("non-existent");

    subnet1->setInterfaceId(ifaceid1);
    subnet2->setInterfaceId(ifaceid2);
    subnet3->setInterfaceId(ifaceid3);

    // There shouldn't be any subnet configured at this stage
    EXPECT_FALSE(cfg_mgr.getSubnet6(ifaceid1, classify_));

    cfg_mgr.addSubnet6(subnet1);

    // If we have only a single subnet and the request came from a local
    // address, let's use that subnet
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet6(ifaceid1, classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet6(ifaceid2, classify_));

    cfg_mgr.addSubnet6(subnet2);
    cfg_mgr.addSubnet6(subnet3);

    EXPECT_EQ(subnet3, cfg_mgr.getSubnet6(ifaceid3, classify_));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet6(ifaceid2, classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet6(ifaceid_bogus, classify_));

    // Check that deletion of the subnets works.
    cfg_mgr.deleteSubnets6();
    EXPECT_FALSE(cfg_mgr.getSubnet6(ifaceid1, classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet6(ifaceid2, classify_));
    EXPECT_FALSE(cfg_mgr.getSubnet6(ifaceid3, classify_));
}


// This test verifies that new DHCPv4 option spaces can be added to
// the configuration manager and that duplicated option space is
// rejected.
TEST_F(CfgMgrTest, optionSpace4) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    // Create some option spaces.
    OptionSpacePtr space1(new OptionSpace("isc", false));
    OptionSpacePtr space2(new OptionSpace("xyz", true));

    // Add option spaces with different names and expect they
    // are accepted.
    ASSERT_NO_THROW(cfg_mgr.addOptionSpace4(space1));
    ASSERT_NO_THROW(cfg_mgr.addOptionSpace4(space2));

    // Validate that the option spaces have been added correctly.
    const OptionSpaceCollection& spaces = cfg_mgr.getOptionSpaces4();

    ASSERT_EQ(2, spaces.size());
    EXPECT_FALSE(spaces.find("isc") == spaces.end());
    EXPECT_FALSE(spaces.find("xyz") == spaces.end());

    // Create another option space with the name that duplicates
    // the existing option space.
    OptionSpacePtr space3(new OptionSpace("isc", true));
    // Expect that the duplicate option space is rejected.
    ASSERT_THROW(
        cfg_mgr.addOptionSpace4(space3), isc::dhcp::InvalidOptionSpace
    );

    /// @todo decode if a duplicate vendor space is allowed.
}

// This test verifies that new DHCPv6 option spaces can be added to
// the configuration manager and that duplicated option space is
// rejected.
TEST_F(CfgMgrTest, optionSpace6) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    // Create some option spaces.
    OptionSpacePtr space1(new OptionSpace("isc", false));
    OptionSpacePtr space2(new OptionSpace("xyz", true));

    // Add option spaces with different names and expect they
    // are accepted.
    ASSERT_NO_THROW(cfg_mgr.addOptionSpace6(space1));
    ASSERT_NO_THROW(cfg_mgr.addOptionSpace6(space2));

    // Validate that the option spaces have been added correctly.
    const OptionSpaceCollection& spaces = cfg_mgr.getOptionSpaces6();

    ASSERT_EQ(2, spaces.size());
    EXPECT_FALSE(spaces.find("isc") == spaces.end());
    EXPECT_FALSE(spaces.find("xyz") == spaces.end());

    // Create another option space with the name that duplicates
    // the existing option space.
    OptionSpacePtr space3(new OptionSpace("isc", true));
    // Expect that the duplicate option space is rejected.
    ASSERT_THROW(
        cfg_mgr.addOptionSpace6(space3), isc::dhcp::InvalidOptionSpace
    );

    /// @todo decide if a duplicate vendor space is allowed.
}

// This test verifies that RFC6842 (echo client-id) compatibility may be
// configured.
TEST_F(CfgMgrTest, echoClientId) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    // Check that the default is true
    EXPECT_TRUE(cfg_mgr.echoClientId());

    // Check that it can be modified to false
    cfg_mgr.echoClientId(false);
    EXPECT_FALSE(cfg_mgr.echoClientId());

    // Check that the default value can be restored
    cfg_mgr.echoClientId(true);
    EXPECT_TRUE(cfg_mgr.echoClientId());
}

// This test checks the D2ClientMgr wrapper methods.
TEST_F(CfgMgrTest, d2ClientConfig) {
    // After CfgMgr construction, D2ClientMgr member should be initialized
    // with a D2 configuration that is disabled.
    // Verify we can Fetch the mgr.
    D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
    EXPECT_FALSE(d2_mgr.ddnsEnabled());

    // Make sure the convenience method fetches the config correctly.
    D2ClientConfigPtr original_config = CfgMgr::instance().getD2ClientConfig();
    ASSERT_TRUE(original_config);
    EXPECT_FALSE(original_config->getEnableUpdates());

    // Verify that we cannot set the configuration to an empty pointer.
    D2ClientConfigPtr new_cfg;
    ASSERT_THROW(CfgMgr::instance().setD2ClientConfig(new_cfg), D2ClientError);

    // Create a new, enabled configuration.
    ASSERT_NO_THROW(new_cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 477,
                                  isc::asiolink::IOAddress("127.0.0.1"), 478,
                                  1024,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  true, true, true, true,
                                  "pre-fix", "suf-fix")));

    // Verify that we can assign a new, non-empty configuration.
    ASSERT_NO_THROW(CfgMgr::instance().setD2ClientConfig(new_cfg));

    // Verify that we can fetch the newly assigned configuration.
    D2ClientConfigPtr updated_config = CfgMgr::instance().getD2ClientConfig();
    ASSERT_TRUE(updated_config);
    EXPECT_TRUE(updated_config->getEnableUpdates());

    // Make sure convenience method agrees with updated configuration.
    EXPECT_TRUE(CfgMgr::instance().ddnsEnabled());

    // Make sure the configuration we fetched is the one we assigned,
    // and not the original configuration.
    EXPECT_EQ(*new_cfg, *updated_config);
    EXPECT_NE(*original_config, *updated_config);
}

// This test verfies that CfgMgr correctly determines that the address of the
// interface belongs to existing IPv4 subnet.
TEST_F(CfgMgrTest, getSubnet4ForInterface) {
    IfaceMgrTestConfig config(true);

    // Initially, there are no subnets configured, so none of the IPv4
    // addresses assigned to eth0 and eth1 can match with any subnet.
    EXPECT_FALSE(CfgMgr::instance().getSubnet4("eth0", classify_));
    EXPECT_FALSE(CfgMgr::instance().getSubnet4("eth1", classify_));

    // Configure first subnet which address on eth0 corresponds to.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("10.0.0.1"), 24, 1, 2, 3));
    CfgMgr::instance().addSubnet4(subnet1);

    // The address on eth0 should match the existing subnet.
    Subnet4Ptr subnet1_ret;
    subnet1_ret = CfgMgr::instance().getSubnet4("eth0", classify_);
    ASSERT_TRUE(subnet1_ret);
    EXPECT_EQ(subnet1->get().first, subnet1_ret->get().first);
    // There should still be no match for eth1.
    EXPECT_FALSE(CfgMgr::instance().getSubnet4("eth1", classify_));

    // Configure a second subnet.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.1"), 24, 1, 2, 3));
    CfgMgr::instance().addSubnet4(subnet2);

    // There should be match between eth0 and subnet1 and between eth1 and
    // subnet 2.
    subnet1_ret = CfgMgr::instance().getSubnet4("eth0", classify_);
    ASSERT_TRUE(subnet1_ret);
    EXPECT_EQ(subnet1->get().first, subnet1_ret->get().first);
    Subnet4Ptr subnet2_ret = CfgMgr::instance().getSubnet4("eth1", classify_);
    ASSERT_TRUE(subnet2_ret);
    EXPECT_EQ(subnet2->get().first, subnet2_ret->get().first);

    // This function throws an exception if the name of the interface is wrong.
    EXPECT_THROW(CfgMgr::instance().getSubnet4("bogus-interface", classify_),
                 isc::BadValue);

}

// Checks that detection of duplicated subnet IDs works as expected. It should
// not be possible to add two IPv4 subnets holding the same ID to the config
// manager.
TEST_F(CfgMgrTest, subnet4Duplication) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3, 123));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3, 124));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3, 123));

    ASSERT_NO_THROW(cfg_mgr.addSubnet4(subnet1));
    EXPECT_NO_THROW(cfg_mgr.addSubnet4(subnet2));
    // Subnet 3 has the same ID as subnet 1. It shouldn't be able to add it.
    EXPECT_THROW(cfg_mgr.addSubnet4(subnet3), isc::dhcp::DuplicateSubnetID);
}

// Checks that detection of duplicated subnet IDs works as expected. It should
// not be possible to add two IPv6 subnets holding the same ID to the config
// manager.
TEST_F(CfgMgrTest, subnet6Duplication) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:1::"), 64, 1, 2, 3,
                                   4, 123));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:2::"), 64, 1, 2, 3,
                                   4, 124));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("2001:db8:3::"), 64, 1, 2, 3,
                                   4, 123));

    ASSERT_NO_THROW(cfg_mgr.addSubnet6(subnet1));
    EXPECT_NO_THROW(cfg_mgr.addSubnet6(subnet2));
    // Subnet 3 has the same ID as subnet 1. It shouldn't be able to add it.
    EXPECT_THROW(cfg_mgr.addSubnet6(subnet3), isc::dhcp::DuplicateSubnetID);
}


// This test verifies that the configuration staging, commit and rollback works
// as expected.
TEST_F(CfgMgrTest, staging) {
    CfgMgr& cfg_mgr = CfgMgr::instance();
    // Initially, the current configuration is a default one. We are going
    // to get the current configuration a couple of times and make sure
    // that always the same instance is returned.
    ConstConfigurationPtr const_config;
    for (int i = 0; i < 5; ++i) {
        const_config = cfg_mgr.getCurrentCfg();
        ASSERT_TRUE(const_config) << "Returned NULL current configuration"
            " for iteration " << i;
        EXPECT_EQ(0, const_config->getSequence())
            << "Returned invalid sequence number "
            << const_config->getSequence() << " for iteration " << i;
    }

    // Try to get the new staging configuration. When getStagingCfg() is called
    // for the first time the new instance of the staging configuration is
    // returned. This instance is returned for every call to getStagingCfg()
    // until commit is called.
    ConfigurationPtr config;
    for (int i = 0; i < 5; ++i) {
        config = cfg_mgr.getStagingCfg();
        ASSERT_TRUE(config) << "Returned NULL staging configuration for"
            " iteration " << i;
        // The sequence id is 1 for staging because it is ahead of current
        // configuration having sequence number 0.
        EXPECT_EQ(1, config->getSequence()) << "Returned invalid sequence"
            " number " << config->getSequence() << " for iteration " << i;
    }

    // This should change the staging configuration so as it becomes a current
    // one.
    cfg_mgr.commit();
    const_config = cfg_mgr.getCurrentCfg();
    ASSERT_TRUE(const_config);
    // Sequence id equal to 1 indicates that the current configuration points
    // to the configuration that used to be a staging configuration previously.
    EXPECT_EQ(1, const_config->getSequence());

    // Create a new staging configuration. It should be assigned a new
    // sequence id.
    config = cfg_mgr.getStagingCfg();
    ASSERT_TRUE(config);
    EXPECT_EQ(2, config->getSequence());

    // Let's execute commit a couple of times. The first invocation to commit
    // changes the configuration having sequence 2 to current configuration.
    // Other commits are no-op.
    for (int i = 0; i < 5; ++i) {
        cfg_mgr.commit();
    }

    // The current configuration now have sequence number 2.
    const_config = cfg_mgr.getCurrentCfg();
    ASSERT_TRUE(const_config);
    EXPECT_EQ(2, const_config->getSequence());

    // Clear configuration along with a history.
    cfg_mgr.clear();

    // After clearing configuration we should successfully get the
    // new staging configuration.
    config = cfg_mgr.getStagingCfg();
    ASSERT_TRUE(config);
    EXPECT_EQ(1, config->getSequence());

    // Modify the staging configuration.
    config->addLoggingInfo(LoggingInfo());
    ASSERT_TRUE(config);
    // The modified staging configuration should have one logger configured.
    ASSERT_EQ(1, config->getLoggingInfo().size());

    // Rollback should remove a staging configuration, including the logger.
    ASSERT_NO_THROW(cfg_mgr.rollback());

    // Make sure that the logger is not set. This is an indication that the
    // rollback worked.
    config = cfg_mgr.getStagingCfg();
    ASSERT_TRUE(config);
    EXPECT_EQ(0, config->getLoggingInfo().size());
}

/// @todo Add unit-tests for testing:
/// - addActiveIface() with invalid interface name
/// - addActiveIface() with the same interface twice
/// - addActiveIface() with a bogus address
///
/// This is somewhat tricky. Care should be taken here, because it is rather
/// difficult to decide if interface name is valid or not. Some servers, e.g.
/// dibbler, allow to specify interface names that are not currently present in
/// the system. The server accepts them, but upon discovering that they are
/// yet available (for different definitions of not being available), adds
/// the to to-be-activated list.
///
/// Cases covered by dibbler are:
/// - missing interface (e.g. PPP connection that is not established yet)
/// - downed interface (no link local address, no way to open sockets)
/// - up, but not running interface (wifi up, but not associated)
/// - tentative addresses (interface up and running, but DAD procedure is
///   still in progress)
/// - weird interfaces without link-local addresses (don't ask, 6rd tunnels
///   look weird to me as well)

// No specific tests for getSubnet6. That method (2 overloaded versions) is tested
// in Dhcpv6SrvTest.selectSubnetAddr and Dhcpv6SrvTest.selectSubnetIface
// (see src/bin/dhcp6/tests/dhcp6_srv_unittest.cc)

} // end of anonymous namespace
