// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

/// @file   dhcp6_test_utils.h
///
/// @brief  This file contains utility classes used for DHCPv6 server testing

#ifndef DHCP6_TEST_UTILS_H
#define DHCP6_TEST_UTILS_H

#include <gtest/gtest.h>

#include <dhcp/pkt6.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_custom.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcp6/dhcp6_srv.h>
#include <hooks/hooks_manager.h>
#include <config/ccsession.h>

#include <list>

using namespace isc::dhcp;
using namespace isc::config;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::asiolink;
using namespace isc::util;
using namespace isc::hooks;

namespace isc {
namespace test {

/// @brief "naked" Dhcpv6Srv class that exposes internal members
class NakedDhcpv6Srv: public isc::dhcp::Dhcpv6Srv {
public:
    NakedDhcpv6Srv(uint16_t port) : Dhcpv6Srv(port) {
        // Open the "memfile" database for leases
        std::string memfile = "type=memfile";
        LeaseMgrFactory::create(memfile);
    }

    /// @brief fakes packet reception
    /// @param timeout ignored
    ///
    /// The method receives all packets queued in receive
    /// queue, one after another. Once the queue is empty,
    /// it initiates the shutdown procedure.
    ///
    /// See fake_received_ field for description
    virtual isc::dhcp::Pkt6Ptr receivePacket(int /*timeout*/) {

        // If there is anything prepared as fake incoming
        // traffic, use it
        if (!fake_received_.empty()) {
            Pkt6Ptr pkt = fake_received_.front();
            fake_received_.pop_front();
            return (pkt);
        }

        // If not, just trigger shutdown and
        // return immediately
        shutdown();
        return (Pkt6Ptr());
    }

    /// @brief fake packet sending
    ///
    /// Pretend to send a packet, but instead just store
    /// it in fake_send_ list where test can later inspect
    /// server's response.
    virtual void sendPacket(const Pkt6Ptr& pkt) {
        fake_sent_.push_back(pkt);
    }

    /// @brief adds a packet to fake receive queue
    ///
    /// See fake_received_ field for description
    void fakeReceive(const Pkt6Ptr& pkt) {
        fake_received_.push_back(pkt);
    }

    virtual ~NakedDhcpv6Srv() {
        // Close the lease database
        LeaseMgrFactory::destroy();
    }

    using Dhcpv6Srv::processSolicit;
    using Dhcpv6Srv::processRequest;
    using Dhcpv6Srv::processRenew;
    using Dhcpv6Srv::processRelease;
    using Dhcpv6Srv::processClientFqdn;
    using Dhcpv6Srv::createNameChangeRequests;
    using Dhcpv6Srv::createRemovalNameChangeRequest;
    using Dhcpv6Srv::createStatusCode;
    using Dhcpv6Srv::selectSubnet;
    using Dhcpv6Srv::sanityCheck;
    using Dhcpv6Srv::loadServerID;
    using Dhcpv6Srv::writeServerID;
    using Dhcpv6Srv::name_change_reqs_;

    /// @brief packets we pretend to receive
    ///
    /// Instead of setting up sockets on interfaces that change between OSes, it
    /// is much easier to fake packet reception. This is a list of packets that
    /// we pretend to have received. You can schedule new packets to be received
    /// using fakeReceive() and NakedDhcpv6Srv::receivePacket() methods.
    std::list<Pkt6Ptr> fake_received_;

    std::list<Pkt6Ptr> fake_sent_;
};

static const char* DUID_FILE = "server-id-test.txt";

// test fixture for any tests requiring blank/empty configuration
// serves as base class for additional tests
class NakedDhcpv6SrvTest : public ::testing::Test {
public:

    NakedDhcpv6SrvTest() : rcode_(-1) {
        // it's ok if that fails. There should not be such a file anyway
        unlink(DUID_FILE);

        const IfaceMgr::IfaceCollection& ifaces = IfaceMgr::instance().getIfaces();

        // There must be some interface detected
        if (ifaces.empty()) {
            // We can't use ASSERT in constructor
            ADD_FAILURE() << "No interfaces detected.";
        }

        valid_iface_ = ifaces.begin()->getName();
    }

    // Generate IA_NA or IA_PD option with specified parameters
    boost::shared_ptr<Option6IA> generateIA(uint16_t type, uint32_t iaid,
                                            uint32_t t1, uint32_t t2);

    /// @brief generates interface-id option, based on text
    ///
    /// @param iface_id textual representation of the interface-id content
    ///
    /// @return pointer to the option object
    OptionPtr generateInterfaceId(const std::string& iface_id) {
        OptionBuffer tmp(iface_id.begin(), iface_id.end());
        return OptionPtr(new Option(Option::V6, D6O_INTERFACE_ID, tmp));
    }

    // Generate client-id option
    OptionPtr generateClientId(size_t duid_size = 32) {

        OptionBuffer clnt_duid(duid_size);
        for (int i = 0; i < duid_size; i++) {
            clnt_duid[i] = 100 + i;
        }

        duid_ = DuidPtr(new DUID(clnt_duid));

        return (OptionPtr(new Option(Option::V6, D6O_CLIENTID,
                                     clnt_duid.begin(),
                                     clnt_duid.begin() + duid_size)));
    }

    // Checks if server response (ADVERTISE or REPLY) includes proper server-id.
    void checkServerId(const Pkt6Ptr& rsp, const OptionPtr& expected_srvid) {
        // check that server included its server-id
        OptionPtr tmp = rsp->getOption(D6O_SERVERID);
        EXPECT_EQ(tmp->getType(), expected_srvid->getType() );
        ASSERT_EQ(tmp->len(), expected_srvid->len() );
        EXPECT_TRUE(tmp->getData() == expected_srvid->getData());
    }

    // Checks if server response (ADVERTISE or REPLY) includes proper client-id.
    void checkClientId(const Pkt6Ptr& rsp, const OptionPtr& expected_clientid) {
        // check that server included our own client-id
        OptionPtr tmp = rsp->getOption(D6O_CLIENTID);
        ASSERT_TRUE(tmp);
        EXPECT_EQ(expected_clientid->getType(), tmp->getType());
        ASSERT_EQ(expected_clientid->len(), tmp->len());

        // check that returned client-id is valid
        EXPECT_TRUE(expected_clientid->getData() == tmp->getData());
    }

    // Checks if server response is a NAK
    void checkNakResponse(const Pkt6Ptr& rsp, uint8_t expected_message_type,
                          uint32_t expected_transid,
                          uint16_t expected_status_code) {
        // Check if we get response at all
        checkResponse(rsp, expected_message_type, expected_transid);

        // Check that IA_NA was returned
        OptionPtr option_ia_na = rsp->getOption(D6O_IA_NA);
        ASSERT_TRUE(option_ia_na);

        // check that the status is no address available
        boost::shared_ptr<Option6IA> ia = boost::dynamic_pointer_cast<Option6IA>(option_ia_na);
        ASSERT_TRUE(ia);

        checkIA_NAStatusCode(ia, expected_status_code);
    }

    // Checks that server rejected IA_NA, i.e. that it has no addresses and
    // that expected status code really appears there. In some limited cases
    // (reply to RELEASE) it may be used to verify positive case, where
    // IA_NA response is expected to not include address.
    //
    // Status code indicates type of error encountered (in theory it can also
    // indicate success, but servers typically don't send success status
    // as this is the default result and it saves bandwidth)
    void checkIA_NAStatusCode(const boost::shared_ptr<Option6IA>& ia,
                            uint16_t expected_status_code) {
        // Make sure there is no address assigned.
        EXPECT_FALSE(ia->getOption(D6O_IAADDR));

        // T1, T2 should be zeroed
        EXPECT_EQ(0, ia->getT1());
        EXPECT_EQ(0, ia->getT2());

        OptionCustomPtr status =
            boost::dynamic_pointer_cast<OptionCustom>(ia->getOption(D6O_STATUS_CODE));

        // It is ok to not include status success as this is the default behavior
        if (expected_status_code == STATUS_Success && !status) {
            return;
        }

        EXPECT_TRUE(status);

        if (status) {
            // We don't have dedicated class for status code, so let's just interpret
            // first 2 bytes as status. Remainder of the status code option content is
            // just a text explanation what went wrong.
            EXPECT_EQ(static_cast<uint16_t>(expected_status_code),
                      status->readInteger<uint16_t>(0));
        }
    }

    void checkMsgStatusCode(const Pkt6Ptr& msg, uint16_t expected_status) {
        OptionCustomPtr status =
            boost::dynamic_pointer_cast<OptionCustom>(msg->getOption(D6O_STATUS_CODE));

        // It is ok to not include status success as this is the default behavior
        if (expected_status == STATUS_Success && !status) {
            return;
        }

        EXPECT_TRUE(status);
        if (status) {
            // We don't have dedicated class for status code, so let's just interpret
            // first 2 bytes as status. Remainder of the status code option content is
            // just a text explanation what went wrong.
            EXPECT_EQ(static_cast<uint16_t>(expected_status),
                      status->readInteger<uint16_t>(0));
        }
    }

    // Basic checks for generated response (message type and transaction-id).
    void checkResponse(const Pkt6Ptr& rsp, uint8_t expected_message_type,
                       uint32_t expected_transid) {
        ASSERT_TRUE(rsp);
        EXPECT_EQ(expected_message_type, rsp->getType());
        EXPECT_EQ(expected_transid, rsp->getTransid());
    }

    virtual ~NakedDhcpv6SrvTest() {
        // Let's clean up if there is such a file.
        unlink(DUID_FILE);
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts(
                                                 "buffer6_receive");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts(
                                                 "buffer6_send");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts(
                                                 "lease6_renew");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts(
                                                 "lease6_release");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts(
                                                 "pkt6_receive");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts(
                                                 "pkt6_send");
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts(
                                                 "subnet6_select");

    };

    // A DUID used in most tests (typically as client-id)
    DuidPtr duid_;

    int rcode_;
    ConstElementPtr comment_;

    // Name of a valid network interface
    std::string valid_iface_;
};

// Provides suport for tests against a preconfigured subnet6
// extends upon NakedDhcp6SrvTest
class Dhcpv6SrvTest : public NakedDhcpv6SrvTest {
public:
    /// Name of the server-id file (used in server-id tests)

    // these are empty for now, but let's keep them around
    Dhcpv6SrvTest() {
        subnet_ = Subnet6Ptr(new Subnet6(IOAddress("2001:db8:1::"), 48, 1000,
                                         2000, 3000, 4000));
        pool_ = Pool6Ptr(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:1::"), 64));
        subnet_->addPool(pool_);

        CfgMgr::instance().deleteSubnets6();
        CfgMgr::instance().addSubnet6(subnet_);

        // configure PD pool
        pd_pool_ = Pool6Ptr(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1:2::"), 64, 80));
        subnet_->addPool(pd_pool_);
    }

    /// @brief Checks that server response (ADVERTISE or REPLY) contains proper
    ///        IA_NA option
    ///
    /// @param rsp server's response
    /// @param expected_iaid expected IAID value
    /// @param expected_t1 expected T1 value
    /// @param expected_t2 expected T2 value
    /// @return IAADDR option for easy chaining with checkIAAddr method
    boost::shared_ptr<Option6IAAddr>
        checkIA_NA(const Pkt6Ptr& rsp, uint32_t expected_iaid,
                   uint32_t expected_t1, uint32_t expected_t2);

    /// @brief Checks that server response (ADVERTISE or REPLY) contains proper
    ///        IA_PD option
    ///
    /// @param rsp server's response
    /// @param expected_iaid expected IAID value
    /// @param expected_t1 expected T1 value
    /// @param expected_t2 expected T2 value
    /// @return IAPREFIX option for easy chaining with checkIAAddr method
    boost::shared_ptr<Option6IAPrefix>
    checkIA_PD(const Pkt6Ptr& rsp, uint32_t expected_iaid,
               uint32_t expected_t1, uint32_t expected_t2);

    // Check that generated IAADDR option contains expected address
    // and lifetime values match the configured subnet
    void checkIAAddr(const boost::shared_ptr<Option6IAAddr>& addr,
                     const IOAddress& expected_addr,
                     Lease::Type type) {

        // Check that the assigned address is indeed from the configured pool.
        // Note that when comparing addresses, we compare the textual
        // representation. IOAddress does not support being streamed to
        // an ostream, which means it can't be used in EXPECT_EQ.
        EXPECT_TRUE(subnet_->inPool(type, addr->getAddress()));
        EXPECT_EQ(expected_addr.toText(), addr->getAddress().toText());
        EXPECT_EQ(addr->getPreferred(), subnet_->getPreferred());
        EXPECT_EQ(addr->getValid(), subnet_->getValid());
    }

    // Checks if the lease sent to client is present in the database
    // and is valid when checked agasint the configured subnet
    Lease6Ptr checkLease(const DuidPtr& duid, const OptionPtr& ia_na,
                         boost::shared_ptr<Option6IAAddr> addr);

    /// @brief Verifies received IAPrefix option
    ///
    /// Verifies if received IAPrefix option matches the lease in database
    /// @param duid client's DUID
    /// @param ia_pd IA_PD option that contains the IAPRefix option
    /// @param prefix pointer to the IAPREFIX option
    /// @return corresponding IPv6 lease (if found)
    Lease6Ptr checkPdLease(const DuidPtr& duid, const OptionPtr& ia_pd,
                           boost::shared_ptr<Option6IAPrefix> prefix);

    /// @brief Creates a message with specified IA
    ///
    /// An utility function that creates a message of specified type with
    /// specified container (IA_NA or IA_PD) and an address or prefix
    /// inside it.
    ///
    /// @param message_type type of the message (e.g. DHCPV6_SOLICIT)
    /// @param lease_type type of a lease (TYPE_NA or TYPE_PD)
    /// @param addr address or prefix to use in IADDRESS or IAPREFIX options
    /// @param prefix_len length of the prefix (used for prefixes only)
    /// @param iaid IA identifier (used in IA_XX option)
    /// @return created message
    Pkt6Ptr
    createMessage(uint8_t message_type, Lease::Type lease_type,
                  const IOAddress& addr, const uint8_t prefix_len,
                  uint32_t iaid);

    /// @brief Performs basic (positive) RENEW test
    ///
    /// See renewBasic and pdRenewBasic tests for detailed explanation.
    /// In essence the test attempts to perform a successful RENEW scenario.
    ///
    /// This method does not throw, but uses gtest macros to signify failures.
    ///
    /// @param type type (TYPE_NA or TYPE_PD)
    /// @param existing_addr address to be preinserted into the database
    /// @param renew_addr address being sent in RENEW
    void
    testRenewBasic(Lease::Type type, const std::string& existing_addr,
                   const std::string& renew_addr);

    /// @brief Performs negative RENEW test
    ///
    /// See renewReject and pdRenewReject tests for detailed explanation.
    /// In essence the test attempts to perform a successful RENEW scenario.
    ///
    /// This method does not throw, but uses gtest macros to signify failures.
    ///
    /// @param type type (TYPE_NA or TYPE_PD)
    /// @param addr address being sent in RENEW
    void
    testRenewReject(Lease::Type type, const IOAddress& addr);

    /// @brief Performs basic (positive) RELEASE test
    ///
    /// See releaseBasic and pdReleaseBasic tests for detailed explanation.
    /// In essence the test attempts to perform a successful RELEASE scenario.
    ///
    /// This method does not throw, but uses gtest macros to signify failures.
    ///
    /// @param type type (TYPE_NA or TYPE_PD)
    /// @param existing address to be preinserted into the database
    /// @param release_addr address being sent in RELEASE
    void
    testReleaseBasic(Lease::Type type, const IOAddress& existing,
                     const IOAddress& release_addr);

    ~Dhcpv6SrvTest() {
        CfgMgr::instance().deleteSubnets6();
    };

    /// A subnet used in most tests
    Subnet6Ptr subnet_;

    /// A normal, non-temporary pool used in most tests
    Pool6Ptr pool_;

    /// A prefix pool used in most tests
    Pool6Ptr pd_pool_;
};

}; // end of isc::test namespace
}; // end of isc namespace

#endif // DHCP6_TEST_UTILS_H
