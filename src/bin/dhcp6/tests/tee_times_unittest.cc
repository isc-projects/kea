// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/option_string.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/tests/dhcp6_message_test.h>
#include <dhcpsrv/utils.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Set of JSON configurations used throughout the Rebind tests.
///
/// - Configuration 0:
///   - only addresses (no prefixes)
///   - 2 subnets with 2001:db8:1::/64 and 2001:db8:2::/64
///   - 1 subnet for eth0 and 1 subnet for eth1
///
const char* TEE_CONFIGS[] = {
    // Configuration 0, Timers explicitly set
    "{ \n" 
    "   \"interfaces-config\": { \n"
    "       \"interfaces\": [ \"*\" ] \n"
    "   }, \n"
    "   \"renew-timer\": 1000, \n"
    "   \"rebind-timer\": 2000, \n"
    "   \"preferred-lifetime\": 3000, \n"
    "   \"valid-lifetime\": 4000, \n"
    "   \"subnet6\": [ { \n"
    "       \"interface\": \"eth0\", \n"
    "       \"subnet\": \"2001:db8:1::/48\", \n"
    "       \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], \n"
    "       \"pd-pools\": [ \n"
    "       { \n"
    "           \"prefix\": \"3000::\", \n "
    "           \"prefix-len\": 72, \n"
    "           \"delegated-len\": 80 \n"
    "       }] \n"
    "   }] \n"
    "} \n"
    , // Configuration 1, Calculate default timers
    "{ \n" 
    "   \"interfaces-config\": { \n"
    "       \"interfaces\": [ \"*\" ] \n"
    "   }, \n"
    "   \"calculate-tee-times\": true, \n"
    "   \"preferred-lifetime\": 3000, \n"
    "   \"valid-lifetime\": 4000, \n"
    "   \"subnet6\": [ { \n"
    "       \"interface\": \"eth0\", \n"
    "       \"subnet\": \"2001:db8:1::/48\", \n"
    "       \"pools\": [ { \"pool\": \"2001:db8:1::/64\" } ], \n"
    "       \"pd-pools\": [ \n"
    "       { \n"
    "           \"prefix\": \"3000::\", \n "
    "           \"prefix-len\": 72, \n"
    "           \"delegated-len\": 80 \n"
    "       }] \n"
    "   }] \n"
    "} \n"
};

/// @brief Test fixture class for testing Rebind.
class TeeTest : public Dhcpv6MessageTest {
public:

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    TeeTest()
        : Dhcpv6MessageTest() {
    }

    void genRequest(const std::string& config, Dhcp6Client& client, 
                    uint32_t exp_leases) {
        // Configure the server.
        ASSERT_NO_THROW(configure(config, *client.getServer()));

        // Do the actual 4-way exchange.
        ASSERT_NO_THROW(client.doSARR());

        // Make sure that we go the expectec number of leases.
        ASSERT_EQ(exp_leases, client.getLeaseNum());

        // Simulate aging of leases, by moving their cltt_ back by 1000s.
        client.fastFwdTime(1000);
    }
};

TEST_F(TeeTest, explicitTimers) {
    Dhcp6Client client;

    uint32_t na_iaid = 2222;
    client.requestAddress(na_iaid);

    uint32_t pd_iaid = 3333;
    client.requestPrefix(pd_iaid);

    uint32_t exp_leases = 2;

    // Configure client to request IA_NA.
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(genRequest(TEE_CONFIGS[0], client, exp_leases));

    // Make sure the timers are right for both IAs
    uint32_t actual_t1;
    uint32_t actual_t2;

    ASSERT_TRUE(client.getTeeTimes(na_iaid, actual_t1, actual_t2));
    EXPECT_EQ(1000, actual_t1);
    EXPECT_EQ(2000, actual_t2);

    ASSERT_TRUE(client.getTeeTimes(pd_iaid, actual_t1, actual_t2));
    EXPECT_EQ(1000, actual_t1);
    EXPECT_EQ(2000, actual_t2);

    // Let's renew the leases.
    ASSERT_NO_THROW(client.doRenew());

    // Now check the timers again.
    ASSERT_TRUE(client.getTeeTimes(na_iaid, actual_t1, actual_t2));
    EXPECT_EQ(1000, actual_t1);
    EXPECT_EQ(2000, actual_t2);

    ASSERT_TRUE(client.getTeeTimes(pd_iaid, actual_t1, actual_t2));
    EXPECT_EQ(1000, actual_t1);
    EXPECT_EQ(2000, actual_t2);
}

TEST_F(TeeTest, calculateTimers) {
    Dhcp6Client client;

    uint32_t na_iaid = 2222;
    client.requestAddress(na_iaid);

    uint32_t pd_iaid = 3333;
    client.requestPrefix(pd_iaid);

    uint32_t exp_leases = 2;

    // Configure client to request IA_NA.
    // Make 4-way exchange to get the lease.
    ASSERT_NO_FATAL_FAILURE(genRequest(TEE_CONFIGS[1], client, exp_leases));

    // Make sure the timers are right for both IAs
    uint32_t actual_t1;
    uint32_t actual_t2;

    ASSERT_TRUE(client.getTeeTimes(na_iaid, actual_t1, actual_t2));
    EXPECT_EQ(2000, actual_t1);
    EXPECT_EQ(3200, actual_t2);

    ASSERT_TRUE(client.getTeeTimes(pd_iaid, actual_t1, actual_t2));
    EXPECT_EQ(2000, actual_t1);
    EXPECT_EQ(3200, actual_t2);

    // Let's renew the leases.
    ASSERT_NO_THROW(client.doRenew());

    // Now check the timers again.
    ASSERT_TRUE(client.getTeeTimes(na_iaid, actual_t1, actual_t2));
    EXPECT_EQ(2000, actual_t1);
    EXPECT_EQ(3200, actual_t2);

    ASSERT_TRUE(client.getTeeTimes(pd_iaid, actual_t1, actual_t2));
    EXPECT_EQ(2000, actual_t1);
    EXPECT_EQ(3200, actual_t2);
}


} // end of anonymous namespace
