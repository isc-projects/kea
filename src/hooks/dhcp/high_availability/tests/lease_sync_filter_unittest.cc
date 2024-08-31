// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/hwaddr.h>
#include <dhcp/duid.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/subnet_id.h>
#include <ha_config.h>
#include <ha_server_type.h>
#include <ha_test.h>
#include <lease_sync_filter.h>
#include <boost/make_shared.hpp>
#include <gtest/gtest.h>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::ha;
using namespace isc::ha::test;

namespace {

/// @brief Test fixture class for testing @c LeaseSyncFilterTest.
class LeaseSyncFilterTest : public HATest {
public:

    /// @brief Constructor.
    ///
    /// Clears configuration in the configuration manager.
    LeaseSyncFilterTest() : HATest() {
        CfgMgr::instance().clear();
    };

    /// @brief Destructor.
    ///
    /// Clears configuration in the configuration manager.
    virtual ~LeaseSyncFilterTest() {
        CfgMgr::instance().clear();
    }
};

// This test verifies that lease sync filter correctly identifies that
// IPv4 leases belong to the configured subnets.
TEST_F(LeaseSyncFilterTest, explicitSubnets4) {
    for (auto i = 0; i < 10; ++i) {
        auto subnet = Subnet4::create(IOAddress(static_cast<uint32_t>(i << 24)), 24,
                                      30, 40, 50, SubnetID(i+1));
        auto context = Element::createMap();
        context->set("ha-server-name", i < 7 ? Element::create("server2") : Element::create("server5"));
        subnet->setContext(context);
        CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    }
    CfgMgr::instance().commit();

    auto config = createValidConfiguration(HAConfig::HOT_STANDBY);
    LeaseSyncFilter filter(HAServerType::DHCPv4, config);
    filter.apply();

    for (auto i = 0; i < 10; ++i) {
        auto lease = boost::make_shared<Lease4>(IOAddress("192.0.2.1"), HWAddrPtr(), ClientIdPtr(),
                                                100, 0, SubnetID(i+1));
        if (i < 7) {
            EXPECT_TRUE(filter.shouldSync(lease));
        } else {
            EXPECT_FALSE(filter.shouldSync(lease));
        }
    }
}

// This test verifies that lease sync filter correctly identifies that
// IPv6 leases belong to the configured subnets.
TEST_F(LeaseSyncFilterTest, explicitSubnets6) {
    for (auto i = 0; i < 10; ++i) {
        std::ostringstream s;
        s << i << "::";
        auto subnet = Subnet6::create(IOAddress(s.str()), 64,
                                      30, 40, 50, 60, SubnetID(i+1));
        auto context = Element::createMap();
        context->set("ha-server-name", i < 7 ? Element::create("server2") : Element::create("server5"));
        subnet->setContext(context);
        CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
    }
    CfgMgr::instance().commit();

    auto config = createValidConfiguration(HAConfig::HOT_STANDBY);
    LeaseSyncFilter filter(HAServerType::DHCPv6, config);
    filter.apply();

    for (auto i = 0; i < 10; ++i) {
        std::ostringstream s;
        s << i << "::";
        auto lease = boost::make_shared<Lease4>(IOAddress(s.str()), HWAddrPtr(), ClientIdPtr(),
                                                100, 0, SubnetID(i+1));
        if (i < 7) {
            EXPECT_TRUE(filter.shouldSync(lease));
        } else {
            EXPECT_FALSE(filter.shouldSync(lease));
        }
    }
}

// This test verifies that lease sync filter correctly identifies that
// leases belong to the configured subnets when the server name is
// specified at shared network level.
TEST_F(LeaseSyncFilterTest, explicitSharedNetworks) {
    for (auto i = 0; i < 10; ++i) {
        std::ostringstream s;
        s << "net" << i;
        auto shared_network = SharedNetwork4::create(s.str());
        auto subnet = Subnet4::create(IOAddress(static_cast<uint32_t>(i << 24)), 24,
                                      30, 40, 50, SubnetID(i+1));
        auto context = Element::createMap();
        context->set("ha-server-name", i < 7 ? Element::create("server2") : Element::create("server5"));
        shared_network->setContext(context);
        shared_network->add(subnet);
        CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4()->add(shared_network);
        CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    }
    CfgMgr::instance().commit();

    auto config = createValidConfiguration(HAConfig::HOT_STANDBY);
    LeaseSyncFilter filter(HAServerType::DHCPv4, config);
    filter.apply();

    for (auto i = 0; i < 10; ++i) {
        auto lease = boost::make_shared<Lease4>(IOAddress("192.0.2.1"), HWAddrPtr(), ClientIdPtr(),
                                                100, 0, SubnetID(i+1));
        if (i < 7) {
            EXPECT_TRUE(filter.shouldSync(lease));
        } else {
            EXPECT_FALSE(filter.shouldSync(lease));
        }
    }
}

// This test verifies that lease sync filter accepts all leases when no
// subnets have been specified in the configuration manager.
TEST_F(LeaseSyncFilterTest, noSubnets4) {
    auto config = createValidConfiguration(HAConfig::HOT_STANDBY);
    LeaseSyncFilter filter(HAServerType::DHCPv4, config);
    filter.apply();

    for (auto i = 0; i < 10; ++i) {
        auto lease = boost::make_shared<Lease4>(IOAddress("192.0.2.1"), HWAddrPtr(), ClientIdPtr(),
                                                100, 0, SubnetID(i));
        EXPECT_TRUE(filter.shouldSync(lease));
    }
}

// This test verifies that lease sync filter accepts all leases when
// there are no associations specified in the subnets.
TEST_F(LeaseSyncFilterTest, noAssociationsInSubnets4) {
    for (auto i = 0; i < 10; ++i) {
        auto subnet = Subnet4::create(IOAddress(static_cast<uint32_t>(i << 24)), 24,
                                      30, 40, 50, SubnetID(i+1));
        CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
    }
    CfgMgr::instance().commit();

    auto config = createValidConfiguration(HAConfig::HOT_STANDBY);
    LeaseSyncFilter filter(HAServerType::DHCPv4, config);
    filter.apply();

    for (auto i = 0; i < 10; ++i) {
        auto lease = boost::make_shared<Lease4>(IOAddress("192.0.2.1"), HWAddrPtr(), ClientIdPtr(),
                                                100, 0, SubnetID(i));
        EXPECT_TRUE(filter.shouldSync(lease));
    }
}


} // end of anonymous namespace
