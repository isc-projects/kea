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

#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcp_parsers.h>
#include <exceptions/exceptions.h>
#include <dhcp/dhcp6.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;
using namespace isc;

// don't import the entire boost namespace.  It will unexpectedly hide uint8_t
// for some systems.
using boost::scoped_ptr;

namespace {

// This test verifies that BooleanStorage functions properly.
TEST(ValueStorageTest, BooleanTesting) {
    BooleanStorage testStore;

    // Verify that we can add and retrieve parameters.
    testStore.setParam("firstBool", false);
    testStore.setParam("secondBool", true);

    EXPECT_FALSE(testStore.getParam("firstBool"));
    EXPECT_TRUE(testStore.getParam("secondBool"));

    // Verify that we can update parameters.
    testStore.setParam("firstBool", true);
    testStore.setParam("secondBool", false);

    EXPECT_TRUE(testStore.getParam("firstBool"));
    EXPECT_FALSE(testStore.getParam("secondBool"));

    // Verify that we can delete a parameter and it will no longer be found.
    testStore.delParam("firstBool");
    EXPECT_THROW(testStore.getParam("firstBool"), isc::dhcp::DhcpConfigError);

    // Verify that the delete was safe and the store still operates.
    EXPECT_FALSE(testStore.getParam("secondBool"));

    // Verify that looking for a parameter that never existed throws.
    ASSERT_THROW(testStore.getParam("bogusBool"), isc::dhcp::DhcpConfigError);

    // Verify that attempting to delete a parameter that never existed does not throw.
    EXPECT_NO_THROW(testStore.delParam("bogusBool"));

    // Verify that we can empty the list.
    testStore.clear();
    EXPECT_THROW(testStore.getParam("secondBool"), isc::dhcp::DhcpConfigError);

}

// This test verifies that Uint32Storage functions properly.
TEST(ValueStorageTest, Uint32Testing) {
    Uint32Storage testStore;

    uint32_t intOne = 77;
    uint32_t intTwo = 33;

    // Verify that we can add and retrieve parameters.
    testStore.setParam("firstInt", intOne);
    testStore.setParam("secondInt", intTwo);

    EXPECT_EQ(testStore.getParam("firstInt"), intOne);
    EXPECT_EQ(testStore.getParam("secondInt"), intTwo);

    // Verify that we can update parameters.
    testStore.setParam("firstInt", --intOne);
    testStore.setParam("secondInt", ++intTwo);

    EXPECT_EQ(testStore.getParam("firstInt"), intOne);
    EXPECT_EQ(testStore.getParam("secondInt"), intTwo);

    // Verify that we can delete a parameter and it will no longer be found.
    testStore.delParam("firstInt");
    EXPECT_THROW(testStore.getParam("firstInt"), isc::dhcp::DhcpConfigError);

    // Verify that the delete was safe and the store still operates.
    EXPECT_EQ(testStore.getParam("secondInt"), intTwo);

    // Verify that looking for a parameter that never existed throws.
    ASSERT_THROW(testStore.getParam("bogusInt"), isc::dhcp::DhcpConfigError);

    // Verify that attempting to delete a parameter that never existed does not throw.
    EXPECT_NO_THROW(testStore.delParam("bogusInt"));

    // Verify that we can empty the list.
    testStore.clear();
    EXPECT_THROW(testStore.getParam("secondInt"), isc::dhcp::DhcpConfigError);
}

// This test verifies that StringStorage functions properly.
TEST(ValueStorageTest, StringTesting) {
    StringStorage testStore;

    std::string stringOne = "seventy-seven";
    std::string stringTwo = "thirty-three";

    // Verify that we can add and retrieve parameters.
    testStore.setParam("firstString", stringOne);
    testStore.setParam("secondString", stringTwo);

    EXPECT_EQ(testStore.getParam("firstString"), stringOne);
    EXPECT_EQ(testStore.getParam("secondString"), stringTwo);

    // Verify that we can update parameters.
    stringOne.append("-boo");
    stringTwo.append("-boo");

    testStore.setParam("firstString", stringOne);
    testStore.setParam("secondString", stringTwo);

    EXPECT_EQ(testStore.getParam("firstString"), stringOne);
    EXPECT_EQ(testStore.getParam("secondString"), stringTwo);

    // Verify that we can delete a parameter and it will no longer be found.
    testStore.delParam("firstString");
    EXPECT_THROW(testStore.getParam("firstString"), isc::dhcp::DhcpConfigError);

    // Verify that the delete was safe and the store still operates.
    EXPECT_EQ(testStore.getParam("secondString"), stringTwo);

    // Verify that looking for a parameter that never existed throws.
    ASSERT_THROW(testStore.getParam("bogusString"), isc::dhcp::DhcpConfigError);

    // Verify that attempting to delete a parameter that never existed does not throw.
    EXPECT_NO_THROW(testStore.delParam("bogusString"));

    // Verify that we can empty the list.
    testStore.clear();
    EXPECT_THROW(testStore.getParam("secondString"), isc::dhcp::DhcpConfigError);
}



class CfgMgrTest : public ::testing::Test {
public:
    CfgMgrTest() {
        // make sure we start with a clean configuration
        CfgMgr::instance().deleteSubnets4();
        CfgMgr::instance().deleteSubnets6();
        CfgMgr::instance().deleteOptionDefs();
        CfgMgr::instance().deleteActiveIfaces();
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
        CfgMgr::instance().deleteSubnets4();
        CfgMgr::instance().deleteSubnets6();
        CfgMgr::instance().deleteOptionDefs();
    }
};

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

// This test verifies that the function that adds new option definition
// throws exceptions when arguments are invalid.
TEST_F(CfgMgrTest, addOptionDefNegative) {
    CfgMgr& cfg_mgr = CfgMgr::instance();
    // The option code 65 is reserved for standard options either in
    // DHCPv4 or DHCPv6. Thus we expect that adding an option to this
    // option space fails.
    OptionDefinitionPtr def(new OptionDefinition("option-foo", 65, "uint16"));

    // Try reserved option space names.
    ASSERT_THROW(cfg_mgr.addOptionDef(def, "dhcp4"), isc::BadValue);
    ASSERT_THROW(cfg_mgr.addOptionDef(def, "dhcp6"), isc::BadValue);
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
// valid leases
TEST_F(CfgMgrTest, subnet4) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3));

    // There shouldn't be any subnet configured at this stage
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.0")));

    cfg_mgr.addSubnet4(subnet1);

    // Now we have only one subnet, any request will be served from it
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet4(IOAddress("192.0.2.63")));

    // Now we add more subnets and check that both old and new subnets
    // are accessible.
    cfg_mgr.addSubnet4(subnet2);
    cfg_mgr.addSubnet4(subnet3);

    EXPECT_EQ(subnet3, cfg_mgr.getSubnet4(IOAddress("192.0.2.191")));
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet4(IOAddress("192.0.2.15")));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet4(IOAddress("192.0.2.85")));

    // Try to find an address that does not belong to any subnet
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.192")));

    // Check that deletion of the subnets works.
    cfg_mgr.deleteSubnets4();
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.191")));
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.15")));
    EXPECT_FALSE(cfg_mgr.getSubnet4(IOAddress("192.0.2.85")));
}

// This test verifies if the configuration manager is able to hold and return
// valid leases
TEST_F(CfgMgrTest, subnet6) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4));

    // There shouldn't be any subnet configured at this stage
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("2000::1")));

    cfg_mgr.addSubnet6(subnet1);

    // Now we have only one subnet, any request will be served from it
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet6(IOAddress("2000::1")));

    // If we have only a single subnet and the request came from a local
    // address, let's use that subnet
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet6(IOAddress("fe80::dead:beef")));

    cfg_mgr.addSubnet6(subnet2);
    cfg_mgr.addSubnet6(subnet3);

    EXPECT_EQ(subnet3, cfg_mgr.getSubnet6(IOAddress("4000::123")));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet6(IOAddress("3000::dead:beef")));
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("5000::1")));

    // Check that deletion of the subnets works.
    cfg_mgr.deleteSubnets6();
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("200::123")));
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("3000::123")));
    EXPECT_FALSE(cfg_mgr.getSubnet6(IOAddress("4000::123")));
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
    EXPECT_FALSE(cfg_mgr.getSubnet6("foo"));

    cfg_mgr.addSubnet6(subnet1);

    // Now we have only one subnet, any request will be served from it
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet6("foo"));

    // Check that the interface name is checked even when there is
    // only one subnet defined.
    EXPECT_FALSE(cfg_mgr.getSubnet6("bar"));

    // If we have only a single subnet and the request came from a local
    // address, let's use that subnet
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet6(IOAddress("fe80::dead:beef")));

    cfg_mgr.addSubnet6(subnet2);
    cfg_mgr.addSubnet6(subnet3);

    EXPECT_EQ(subnet3, cfg_mgr.getSubnet6("foobar"));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet6("bar"));
    EXPECT_FALSE(cfg_mgr.getSubnet6("xyzzy")); // no such interface

    // Check that deletion of the subnets works.
    cfg_mgr.deleteSubnets6();
    EXPECT_FALSE(cfg_mgr.getSubnet6("foo"));
    EXPECT_FALSE(cfg_mgr.getSubnet6("bar"));
    EXPECT_FALSE(cfg_mgr.getSubnet6("foobar"));
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
    EXPECT_FALSE(cfg_mgr.getSubnet6(ifaceid1));

    cfg_mgr.addSubnet6(subnet1);

    // If we have only a single subnet and the request came from a local
    // address, let's use that subnet
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet6(ifaceid1));
    EXPECT_FALSE(cfg_mgr.getSubnet6(ifaceid2));

    cfg_mgr.addSubnet6(subnet2);
    cfg_mgr.addSubnet6(subnet3);

    EXPECT_EQ(subnet3, cfg_mgr.getSubnet6(ifaceid3));
    EXPECT_EQ(subnet2, cfg_mgr.getSubnet6(ifaceid2));
    EXPECT_FALSE(cfg_mgr.getSubnet6(ifaceid_bogus));

    // Check that deletion of the subnets works.
    cfg_mgr.deleteSubnets6();
    EXPECT_FALSE(cfg_mgr.getSubnet6(ifaceid1));
    EXPECT_FALSE(cfg_mgr.getSubnet6(ifaceid2));
    EXPECT_FALSE(cfg_mgr.getSubnet6(ifaceid3));
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

    // @todo decode if a duplicate vendor space is allowed.
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

    // @todo decide if a duplicate vendor space is allowed.
}

// This test verifies that it is possible to specify interfaces that server
// should listen on.
TEST_F(CfgMgrTest, addActiveIface) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    EXPECT_NO_THROW(cfg_mgr.addActiveIface("eth0"));
    EXPECT_NO_THROW(cfg_mgr.addActiveIface("eth1"));

    EXPECT_TRUE(cfg_mgr.isActiveIface("eth0"));
    EXPECT_TRUE(cfg_mgr.isActiveIface("eth1"));
    EXPECT_FALSE(cfg_mgr.isActiveIface("eth2"));

    EXPECT_NO_THROW(cfg_mgr.deleteActiveIfaces());

    EXPECT_FALSE(cfg_mgr.isActiveIface("eth0"));
    EXPECT_FALSE(cfg_mgr.isActiveIface("eth1"));
    EXPECT_FALSE(cfg_mgr.isActiveIface("eth2"));
}


// This test verifies that it is possible to specify interfaces that server
// should listen on.
TEST_F(CfgMgrTest, addUnicastAddresses) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    EXPECT_NO_THROW(cfg_mgr.addActiveIface("eth1/2001:db8::1"));
    EXPECT_NO_THROW(cfg_mgr.addActiveIface("eth2/2001:db8::2"));
    EXPECT_NO_THROW(cfg_mgr.addActiveIface("eth3"));

    EXPECT_TRUE(cfg_mgr.isActiveIface("eth1"));
    EXPECT_TRUE(cfg_mgr.isActiveIface("eth2"));
    EXPECT_TRUE(cfg_mgr.isActiveIface("eth3"));
    EXPECT_FALSE(cfg_mgr.isActiveIface("eth4"));

    ASSERT_TRUE(cfg_mgr.getUnicast("eth1"));
    EXPECT_EQ("2001:db8::1", cfg_mgr.getUnicast("eth1")->toText());
    EXPECT_EQ("2001:db8::2", cfg_mgr.getUnicast("eth2")->toText());
    EXPECT_FALSE(cfg_mgr.getUnicast("eth3"));
    EXPECT_FALSE(cfg_mgr.getUnicast("eth4"));

    EXPECT_NO_THROW(cfg_mgr.deleteActiveIfaces());

    EXPECT_FALSE(cfg_mgr.isActiveIface("eth1"));
    EXPECT_FALSE(cfg_mgr.isActiveIface("eth2"));
    EXPECT_FALSE(cfg_mgr.isActiveIface("eth3"));
    EXPECT_FALSE(cfg_mgr.isActiveIface("eth4"));

    ASSERT_FALSE(cfg_mgr.getUnicast("eth1"));
    ASSERT_FALSE(cfg_mgr.getUnicast("eth2"));
    EXPECT_FALSE(cfg_mgr.getUnicast("eth3"));
    EXPECT_FALSE(cfg_mgr.getUnicast("eth4"));
}


// This test verifies that it is possible to set the flag which configures the
// server to listen on all interfaces.
TEST_F(CfgMgrTest, activateAllIfaces) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    cfg_mgr.addActiveIface("eth0");
    cfg_mgr.addActiveIface("eth1");

    ASSERT_TRUE(cfg_mgr.isActiveIface("eth0"));
    ASSERT_TRUE(cfg_mgr.isActiveIface("eth1"));
    ASSERT_FALSE(cfg_mgr.isActiveIface("eth2"));

    cfg_mgr.activateAllIfaces();

    EXPECT_TRUE(cfg_mgr.isActiveIface("eth0"));
    EXPECT_TRUE(cfg_mgr.isActiveIface("eth1"));
    EXPECT_TRUE(cfg_mgr.isActiveIface("eth2"));

    cfg_mgr.deleteActiveIfaces();

    EXPECT_FALSE(cfg_mgr.isActiveIface("eth0"));
    EXPECT_FALSE(cfg_mgr.isActiveIface("eth1"));
    EXPECT_FALSE(cfg_mgr.isActiveIface("eth2"));
}

// This test verifies that RFC6842 (echo client-id) compatibility may be
// configured.
TEST_F(CfgMgrTest, echoClientId) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    EXPECT_TRUE(cfg_mgr.echoClientId());

    cfg_mgr.echoClientId(false);

    EXPECT_FALSE(cfg_mgr.echoClientId());
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
