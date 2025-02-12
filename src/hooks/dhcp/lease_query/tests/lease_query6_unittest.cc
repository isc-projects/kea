// Copyright (C) 2020-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify DHCPv6 LeaseQuery processing.

#include <config.h>
#include <lease_query_log.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt6.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <stats/stats_mgr.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::lease_query;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::util;
using namespace isc::stats;

extern "C" {
extern int buffer6_receive(CalloutHandle& handle);
}

namespace {

/// @brief Test fixture for exercising buffer6_receive callout.
/// It fetches the CalloutManager and prepares stub packets that can be used in
/// tests.
class LeaseQuery6Test : public ::testing::Test {
public:

    /// @brief Constructor.
    LeaseQuery6Test() : co_manager_(new CalloutManager(1)) {
        StatsMgr::instance().setValue("pkt6-lease-query-received",
                                      static_cast<int64_t>(0));
    }

    /// @brief Destructor.
    virtual ~LeaseQuery6Test() {
    }

    /// @brief Fetches the callout manager instance.
    boost::shared_ptr<CalloutManager>getCalloutManager() {
        return (co_manager_);
    }

    /// @brief Tests buffer6_receive callout.
    ///
    /// @param pkt The packet to submit.
    /// @param processed True if the packet must be processed, false otherwise.
    void buffer6ReceiveCalloutCall(Pkt6Ptr& pkt, bool processed) {
        // Get callout handle.
        CalloutHandle handle(getCalloutManager());

        // Get data so it becomes possible to reset it to unpacked state.
        ASSERT_NO_THROW(pkt->pack());
        const OutputBuffer& buffer = pkt->getBuffer();
        pkt.reset(new Pkt6(reinterpret_cast<const uint8_t*>(buffer.getData()),
                           buffer.getLength()));

        // Set query.
        handle.setArgument("query6", pkt);

        // Execute buffer6_receive callout.
        int ret;
        ASSERT_NO_THROW(ret = buffer6_receive(handle));
        EXPECT_EQ(0, ret);

        if (processed) {
            // DROP means it has been consumed.
            EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, handle.getStatus());
            checkStat("pkt6-lease-query-received", 1);
        } else {
            // Verify status (SKIP means it has been unpacked but not consumed).
            EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, handle.getStatus());
            checkStat("pkt6-lease-query-received", 0);
        }
    }

    void checkStat(const std::string& name, uint64_t exp_value) {
        ObservationPtr obs = StatsMgr::instance().getObservation(name);
        ASSERT_TRUE(obs) << "no such stat: " << name;
        EXPECT_EQ(exp_value, obs->getInteger().first);
    }

    /// @brief Callout manager accessed by this CalloutHandle.
    boost::shared_ptr<CalloutManager> co_manager_;
};

// Verifies that anything other than DHCPV6_LEASE_QUERY passes
// through unmodified.
TEST_F(LeaseQuery6Test, notLeaseQuery) {
    for (uint8_t msg_type = 0; msg_type < UINT8_MAX; ++msg_type) {
        if (msg_type != DHCPV6_LEASEQUERY) {
            Pkt6Ptr pkt(new Pkt6(msg_type, 12365));
            buffer6ReceiveCalloutCall(pkt, false);
        }
    }
}

// Verifies that DHCPV6_LEASEQUERY gets processed.
TEST_F(LeaseQuery6Test, dhcpv6LeaseQuery) {
    Pkt6Ptr pkt(new Pkt6(DHCPV6_LEASEQUERY, 12365));

    uint8_t duid[] = { 0, 3, 0, 11, 0xa, 0xb, 0xc, 0xd, 0xe, 0xff };
    OptionPtr client_id(new Option(Option::V6, D6O_CLIENTID, OptionBuffer(
                                   duid, duid + sizeof(duid))));
    pkt->addOption(client_id);
    buffer6ReceiveCalloutCall(pkt, true);
}

} // end of anonymous namespace
