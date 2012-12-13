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

#include <dhcpsrv/cfgmgr.h>
#include <exceptions/exceptions.h>

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

class CfgMgrTest : public ::testing::Test {
public:
    CfgMgrTest() {
    }

    ~CfgMgrTest() {
        CfgMgr::instance().deleteSubnets6();
    }
};


// This test verifies if the configuration manager is able to hold and return
// valid leases
TEST_F(CfgMgrTest, subnet4) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 26, 1, 2, 3));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.64"), 26, 1, 2, 3));
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.2.128"), 26, 1, 2, 3));

    // there shouldn't be any subnet configured at this stage
    EXPECT_EQ( Subnet4Ptr(), cfg_mgr.getSubnet4(IOAddress("192.0.2.0")));

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
    EXPECT_EQ(Subnet4Ptr(), cfg_mgr.getSubnet4(IOAddress("192.0.2.192")));
}

// This test verifies if the configuration manager is able to hold and return
// valid leases

TEST_F(CfgMgrTest, subnet6) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4));

    // there shouldn't be any subnet configured at this stage
    EXPECT_EQ( Subnet6Ptr(), cfg_mgr.getSubnet6(IOAddress("2000::1")));

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
    EXPECT_EQ(Subnet6Ptr(), cfg_mgr.getSubnet6(IOAddress("5000::1")));

    cfg_mgr.deleteSubnets6();
    EXPECT_EQ(Subnet6Ptr(), cfg_mgr.getSubnet6(IOAddress("200::123")));
    EXPECT_EQ(Subnet6Ptr(), cfg_mgr.getSubnet6(IOAddress("3000::123")));
    EXPECT_EQ(Subnet6Ptr(), cfg_mgr.getSubnet6(IOAddress("4000::123")));
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

} // end of anonymous namespace
