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
#include <sstream>
#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <dhcp/cfgmgr.h>
#include <exceptions/exceptions.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;
using namespace isc;

// don't import the entire boost namespace.  It will unexpectedly hide uint8_t
// for some systems.
using boost::scoped_ptr;

namespace {

// This test verifies if the configuration manager is able to hold and return
// valid leases
TEST(CfgMgrTest, subnet4) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    ASSERT_TRUE(&cfg_mgr != 0);

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
TEST(CfgMgrTest, subnet6) {
    CfgMgr& cfg_mgr = CfgMgr::instance();

    ASSERT_TRUE(&cfg_mgr != 0);

    Subnet6Ptr subnet1(new Subnet6(IOAddress("2000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("3000::"), 48, 1, 2, 3, 4));
    Subnet6Ptr subnet3(new Subnet6(IOAddress("4000::"), 48, 1, 2, 3, 4));

    // there shouldn't be any subnet configured at this stage
    EXPECT_EQ( Subnet6Ptr(), cfg_mgr.getSubnet6(IOAddress("2000::1")));

    cfg_mgr.addSubnet6(subnet1);

    // Now we have only one subnet, any request will be served from it
    EXPECT_EQ(subnet1, cfg_mgr.getSubnet6(IOAddress("2001:db8::1")));

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

} // end of anonymous namespace
