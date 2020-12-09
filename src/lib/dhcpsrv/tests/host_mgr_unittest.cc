// Copyright (C) 2014-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/testutils/generic_host_data_source_unittest.h>

#include <gtest/gtest.h>
#include <vector>

using namespace isc;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::asiolink;

namespace {

// The tests in this file only address the in memory hosts.

// This test verifies that HostMgr returns all reservations for the
// specified HW address. The reservations are defined in the server's
// configuration.
TEST_F(HostMgrTest, getAll) {
    testGetAll(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that HostMgr returns all reservations for the
// specified DHCPv4 subnet. The reservations are defined in the server's
// configuration.
TEST_F(HostMgrTest, getAll4BySubnet) {
    testGetAll4BySubnet(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that HostMgr returns all reservations for the specified
// IPv4 subnet and reserved address. The reservations are specified in the
// server's configuration.
TEST_F(HostMgrTest, getAll4BySubnetIP) {
    testGetAll4BySubnetIP(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that HostMgr returns all reservations for the specified
// IPv6 subnet and reserved address. The reservations are specified in the
// server's configuration.
TEST_F(HostMgrTest, getAll6BySubnetIP) {
    testGetAll6BySubnetIP(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that HostMgr returns all reservations for the
// specified DHCPv6 subnet. The reservations are defined in the server's
// configuration.
TEST_F(HostMgrTest, getAll6BySubnet) {
    testGetAll6BySubnet(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that HostMgr returns all reservations for the specified
// hostname. The reservations are defined in the server's configuration.
TEST_F(HostMgrTest, getAllbyHostname) {
    testGetAllbyHostname(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that HostMgr returns all reservations for the specified
// hostname and DHCPv4 subnet. The reservations are defined in the server's
// configuration.
TEST_F(HostMgrTest, getAllbyHostnameSubnet4) {
    testGetAllbyHostnameSubnet4(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that HostMgr returns all reservations for the specified
// hostname and DHCPv6 subnet. The reservations are defined in the server's
// configuration.
TEST_F(HostMgrTest, getAllbyHostnameSubnet6) {
    testGetAllbyHostnameSubnet6(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that HostMgr returns all reservations for the specified
// hostname and DHCPv6 subnet. The reservations are defined in the server's
// configuration.
TEST_F(HostMgrTest, getAllbyHostname6) {
    testGetAllbyHostnameSubnet4(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that HostMgr returns all reservations for the
// specified DHCPv4 subnet by pages. The reservations are defined in
// the server's configuration.
TEST_F(HostMgrTest, getPage4) {
    testGetPage4(false);
}

// This test verifies that HostMgr returns all v4 reservations by pages.
// The reservations are defined in the server's configuration.
TEST_F(HostMgrTest, getPage4All) {
    testGetPage4All(false);
}

// This test verifies that HostMgr returns all reservations for the
// specified DHCPv6 subnet by pages. The reservations are defined in
// the server's configuration.
TEST_F(HostMgrTest, getPage6) {
    testGetPage6(false);
}

// This test verifies that HostMgr returns all v6 reservations by pages.
// The reservations are defined in the server's configuration.
TEST_F(HostMgrTest, getPage6All) {
    testGetPage6All(false);
}

// This test verifies that it is possible to gather all reservations for the
// specified IPv4 address from the HostMgr. The reservations are specified in
// the server's configuration.
TEST_F(HostMgrTest, getAll4) {
    testGetAll4(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that it is possible to retrieve a reservation for the
// particular host using HostMgr. The reservation is specified in the server's
// configuration.
TEST_F(HostMgrTest, get4) {
    testGet4(*getCfgHosts());
}

// This test verifies handling of negative caching by get4/get4Any.
TEST_F(HostMgrTest, get4Any) {
    testGet4Any();
}

// This test verifies that it is possible to retrieve IPv6 reservations for
// the particular host using HostMgr. The reservation is specified in the
// server's configuration.
TEST_F(HostMgrTest, get6) {
    testGet6(*getCfgHosts());
}

// This test verifies handling of negative caching by get4/get4Any.
TEST_F(HostMgrTest, get6Any) {
    testGet6Any();
}

// This test verifies that it is possible to retrieve the reservation of the
// particular IPv6 prefix using HostMgr.
TEST_F(HostMgrTest, get6ByPrefix) {
    testGet6ByPrefix(*getCfgHosts(), *getCfgHosts());
}

// This test verifies that without a host data source an exception is thrown.
TEST_F(HostMgrTest, addNoDataSource) {
    // Remove all configuration.
    CfgMgr::instance().clear();
    // Recreate HostMgr instance.
    HostMgr::create();

    HostPtr host(new Host(hwaddrs_[0]->toText(false), "hw-address",
                          SubnetID(1), SUBNET_ID_UNUSED, IOAddress("192.0.2.5")));
    EXPECT_THROW(HostMgr::instance().add(host), NoHostDataSourceManager);
}

}  // namespace
