// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify DHCPv4 LeaseQuery callouts.

#include <config.h>

#include <cc/data.h>
#include <lease_query_log.h>
#include <lease_query_impl_factory.h>
#include <dhcp/pkt4.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/cfgmgr.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <process/daemon.h>
#include <stats/stats_mgr.h>
#include <testutils/gtest_utils.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <test_lease_mgr.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::lease_query;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::util;
using namespace isc::stats;
using namespace isc::dhcp::test;

extern "C" {
extern int buffer4_receive(CalloutHandle& handle);
}

namespace {

/// @brief Test fixture for exercising buffer4_receive callout.
/// It fetches the CalloutManager and prepares stub packets that can be used in
/// tests.
template <typename TestLeaseMgrType>
class BaseLeaseQuery4Test : public ::testing::Test {
public:

    /// @brief Describes expected outcome of call to buffer4_receive().
    enum Outcome {
       OC_SKIP,  // query is not a lease query, callout unpacks only
       OC_REPLY, // query is a valid lease query to which callout replies
       OC_ERROR  // query cannot be unpacked, or fails to process
    };

    /// @brief Constructor.
    ///
    /// We create a minimum configuration of a single subnet with one
    /// pool, and a single active lease.
    BaseLeaseQuery4Test() : co_manager_(new CalloutManager(1)) {
        CfgMgr::instance().setFamily(AF_INET);
        process::Daemon::setProcName("kea-dhcp4");

        LeaseMgrFactory::destroy();
        TestLeaseMgrType test_lease_mgr;
        test_lease_mgr.createSchema();
        LeaseMgrFactory::create(test_lease_mgr.dbAccess());

        CfgMgr& cfg_mgr = CfgMgr::instance();
        CfgSubnets4Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets4();

        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 1200, 2400, 3600, 2));
        Pool4Ptr pool(new Pool4(IOAddress("192.0.2.100"), IOAddress("192.0.2.200")));
        subnet->addPool(pool);
        subnets->add(subnet);
        cfg_mgr.commit();

        HWAddrPtr hwaddr(new HWAddr(std::vector<uint8_t>{ 0x01,0x02,0x03,0x04,0x05,0x06 }, 1));
        Lease4Ptr lease(new Lease4(IOAddress("192.0.2.101"), hwaddr, ClientIdPtr(),
                                   subnet->getValid(), time(NULL), subnet->getID()));

        LeaseMgrFactory::instance().addLease(lease);

        createImpl();
        StatsMgr::instance().setValue("pkt4-receive-drop",
                                      static_cast<int64_t>(0));
        StatsMgr::instance().setValue("pkt4-lease-query-received",
                                      static_cast<int64_t>(0));
        StatsMgr::instance().setValue("pkt4-lease-query-response-unknown-sent",
                                      static_cast<int64_t>(0));
        StatsMgr::instance().setValue("pkt4-lease-query-response-unassigned-sent",
                                      static_cast<int64_t>(0));
        StatsMgr::instance().setValue("pkt4-lease-query-response-active-sent",
                                      static_cast<int64_t>(0));
    }

    /// @brief Constructs a DHCPLEASEQUERY for querying by IP address.
    ///
    /// @param giaddr ip address of the requester
    /// @param ciaddr ip address for which to query
    Pkt4Ptr makeLeaseQuery(const IOAddress& giaddr, const IOAddress& ciaddr) {
        Pkt4Ptr query(new Pkt4(DHCPLEASEQUERY, 12345));
        query->setGiaddr(giaddr);
        query->setCiaddr(ciaddr);
        HWAddrPtr hwaddr_empty(new HWAddr(std::vector<uint8_t>{}, 0));
        query->setHWAddr(hwaddr_empty);
        return (query);
    }

    /// @brief Destructor.
    virtual ~BaseLeaseQuery4Test() {
        destroyImpl();
        LeaseMgrFactory::destroy();
        CfgMgr::instance().clear();
        TestLeaseMgrType test_lease_mgr;
        test_lease_mgr.destroySchema();
    }

    // Create the LeaseQueryImpl singleton.
    void createImpl() {
        std::string json = "{ \"requesters\": [ \"192.0.2.1\" ] }";
        ConstElementPtr parameters;
        ASSERT_NO_THROW_LOG(parameters = Element::fromJSON(json));
        ASSERT_NO_THROW_LOG(LeaseQueryImplFactory::createImpl(AF_INET, parameters));
    }

    // Destroy the LeaseQueryImpl singleton.
    void destroyImpl() {
        LeaseQueryImplFactory::destroyImpl();
    }

    /// @brief Fetches the callout manager instance.
    boost::shared_ptr<CalloutManager>getCalloutManager() {
        return (co_manager_);
    }

    /// @brief Tests buffer4_receive callout.
    ///
    /// We are primarily testing the larger grained aspect of query
    /// handling. Detailed contents of replies are tested elsewhere.
    ///
    /// @param pkt The packet to submit.
    /// @param outcome expected outcome of callout: OC_SKIP, OC_REPLY,
    /// or OC_ERROR.
    /// @param reply_type message type of the reply. Only relevant
    /// when outcome = OC_REPLY
    /// @param iface interface name to send through.  Defaults to "eth0".
    void buffer4ReceiveCalloutCall(Pkt4Ptr& pkt, Outcome outcome,
                                   DHCPMessageType reply_type = DHCP_NOTYPE,
                                   const std::string& iface = "eth0",
                                   uint32_t ifindex = ETH0_INDEX) {
        // Get callout handle.
        CalloutHandle handle(getCalloutManager());

        // Get data so it becomes possible to reset it to unpacked state.
        ASSERT_NO_THROW(pkt->pack());
        const OutputBuffer& buffer = pkt->getBuffer();
        pkt.reset(new Pkt4(reinterpret_cast<const uint8_t*>(buffer.getData()),
                           buffer.getLength()));

        // Set the interface so packet send does not fall down.
        pkt->setIface(iface);
        pkt->setIndex(ifindex);

        // Set query.
        handle.setArgument("query4", pkt);

        // Execute buffer4_receive callout.
        int ret;
        ASSERT_NO_THROW(ret = buffer4_receive(handle));
        EXPECT_EQ(0, ret);

        switch(outcome) {
        case OC_SKIP:
            // Verify status (SKIP means it has been unpacked but not consumed).
            EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, handle.getStatus());
            checkStat("pkt4-lease-query-received", 0);
            checkStat("pkt4-receive-drop", 0);
            break;

        case OC_REPLY: {
            // DROP means it has been consumed.
            EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, handle.getStatus());
            checkStat("pkt4-lease-query-received", 1);
            // We don't count it as dropped because we replied.
            checkStat("pkt4-receive-drop", 0);

            // See if we sent the expected type.
            switch(reply_type) {
            case DHCPLEASEUNKNOWN:
                checkStat("pkt4-lease-query-response-unknown-sent", 1);
                checkStat("pkt4-lease-query-response-unassigned-sent", 0);
                checkStat("pkt4-lease-query-response-active-sent", 0);
                break;

            case DHCPLEASEUNASSIGNED:
                checkStat("pkt4-lease-query-response-unknown-sent", 0);
                checkStat("pkt4-lease-query-response-unassigned-sent", 1);
                checkStat("pkt4-lease-query-response-active-sent", 0);
                break;

            case DHCPLEASEACTIVE:
                checkStat("pkt4-lease-query-response-unknown-sent", 0);
                checkStat("pkt4-lease-query-response-unassigned-sent", 0);
                checkStat("pkt4-lease-query-response-active-sent", 1);
                break;

            default:
                break;
            }

            break;
        }

        case OC_ERROR:
            // DROP means it has been consumed.
            EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, handle.getStatus());
            checkStat("pkt4-lease-query-received", 1);
            checkStat("pkt4-receive-drop", 1);
            checkStat("pkt4-lease-query-response-unknown-sent", 0);
            checkStat("pkt4-lease-query-response-unassigned-sent", 0);
            checkStat("pkt4-lease-query-response-active-sent", 0);
            break;
        }
    }

    /// @brief Checks the value of a statistic
    /// @param name name of statistic to check
    /// @param expected value of statistic
    void checkStat(const std::string& name, uint64_t exp_value) {
        ObservationPtr obs = StatsMgr::instance().getObservation(name);
        ASSERT_TRUE(obs) << "no such stat: " << name;
        EXPECT_EQ(exp_value, obs->getInteger().first)
                  << name << " has wrong value ";
    }

    /// @brief Test not lease query.
    void testNotLeaseQuery();

    /// @brief Test processing fails.
    void testProcessingFails();

    /// @brief Test DHCP lease query unknown.
    void testDhcpLeaseQueryUnknown();

    /// @brietf Test DHCP lease query unassigned.
    void testDhcpLeaseQueryUnassigned();

    /// @brietf Test DHCP lease query active.
    void testDhcpLeaseQueryActive();

    /// @brief Callout manager accessed by this CalloutHandle.
    boost::shared_ptr<CalloutManager> co_manager_;
};

/// @brief Memfile test fixture.
class MemfileLeaseQuery4Test : public BaseLeaseQuery4Test<MemfileTestLeaseMgr> {
};

// Verifies that anything other than DHCPLEASEQUERY passes
// through unmodified.
template <typename TestLeaseMgrType> void
BaseLeaseQuery4Test<TestLeaseMgrType>::testNotLeaseQuery() {
    for (uint8_t msg_type = 0; msg_type < UINT8_MAX; ++msg_type) {
        SCOPED_TRACE(msg_type);
        Pkt4Ptr pkt;
        if (msg_type != DHCPLEASEQUERY) {
            try {
                pkt.reset(new Pkt4(msg_type, 12365));
            } catch (const OutOfRange&) {
                // Bypass the Pkt4 constructor's complaint.
                pkt.reset(new Pkt4(DHCPDISCOVER, 12365));
                pkt->setType(msg_type);
            }
            buffer4ReceiveCalloutCall(pkt, OC_SKIP);
        }
    }
}

TEST_F(MemfileLeaseQuery4Test, notLeaseQuery) {
    testNotLeaseQuery();
}

// Verifies that DHCPLEASEQUERY gets processed.
template <typename TestLeaseMgrType> void
BaseLeaseQuery4Test<TestLeaseMgrType>::testProcessingFails() {

    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr pkt(new Pkt4(DHCPLEASEQUERY, 12345));
    pkt->setGiaddr(IOAddress("192.0.2.255"));
    buffer4ReceiveCalloutCall(pkt, OC_ERROR);
}

TEST_F(MemfileLeaseQuery4Test, processingFails) {
    testProcessingFails();
}

// Verifies that a valid DHCPLEASEQUERY for an unknown address works.
// Verifies that DHCPLEASEQUERY gets processed.
template <typename TestLeaseMgrType> void
BaseLeaseQuery4Test<TestLeaseMgrType>::testDhcpLeaseQueryUnknown() {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr query = makeLeaseQuery(IOAddress("192.0.2.1"), IOAddress("192.0.5.1"));
    buffer4ReceiveCalloutCall(query, OC_REPLY, DHCPLEASEUNKNOWN);
}

TEST_F(MemfileLeaseQuery4Test, dhcpLeaseQueryUnknown) {
    testDhcpLeaseQueryUnknown();
}

// Verifies that a valid DHCPLEASEQUERY for an unassigned address works.
template <typename TestLeaseMgrType> void
BaseLeaseQuery4Test<TestLeaseMgrType>::testDhcpLeaseQueryUnassigned() {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr query = makeLeaseQuery(IOAddress("192.0.2.1"), IOAddress("192.0.2.100"));
    buffer4ReceiveCalloutCall(query, OC_REPLY, DHCPLEASEUNASSIGNED);
}

TEST_F(MemfileLeaseQuery4Test, dhcpLeaseQueryUnassigned) {
    testDhcpLeaseQueryUnassigned();
}

// Verifies that a valid DHCPLEASEQUERY for an active lease works.
template <typename TestLeaseMgrType> void
BaseLeaseQuery4Test<TestLeaseMgrType>::testDhcpLeaseQueryActive() {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr query = makeLeaseQuery(IOAddress("192.0.2.1"), IOAddress("192.0.2.101"));
    buffer4ReceiveCalloutCall(query, OC_REPLY, DHCPLEASEACTIVE);
}

TEST_F(MemfileLeaseQuery4Test, dhcpLeaseQueryActive) {
    testDhcpLeaseQueryActive();
}

#ifdef HAVE_MYSQL
/// @brief MySQL test fixture.
class MySQLLeaseQuery4Test : public BaseLeaseQuery4Test<MySQLTestLeaseMgr> {
};

TEST_F(MySQLLeaseQuery4Test, notLeaseQuery) {
    testNotLeaseQuery();
}

TEST_F(MySQLLeaseQuery4Test, processingFails) {
    testProcessingFails();
}

TEST_F(MySQLLeaseQuery4Test, dhcpLeaseQueryUnknown) {
    testDhcpLeaseQueryUnknown();
}

TEST_F(MySQLLeaseQuery4Test, dhcpLeaseQueryUnassigned) {
    testDhcpLeaseQueryUnassigned();
}

TEST_F(MySQLLeaseQuery4Test, dhcpLeaseQueryActive) {
    testDhcpLeaseQueryActive();
}
#endif

#ifdef HAVE_PGSQL
/// @brief PostgreSQL test fixture.
class PgSQLLeaseQuery4Test : public BaseLeaseQuery4Test<PgSQLTestLeaseMgr> {
};

TEST_F(PgSQLLeaseQuery4Test, notLeaseQuery) {
    testNotLeaseQuery();
}

TEST_F(PgSQLLeaseQuery4Test, processingFails) {
    testProcessingFails();
}

TEST_F(PgSQLLeaseQuery4Test, dhcpLeaseQueryUnknown) {
    testDhcpLeaseQueryUnknown();
}

TEST_F(PgSQLLeaseQuery4Test, dhcpLeaseQueryUnassigned) {
    testDhcpLeaseQueryUnassigned();
}

TEST_F(PgSQLLeaseQuery4Test, dhcpLeaseQueryActive) {
    testDhcpLeaseQueryActive();
}
#endif

} // end of anonymous namespace
