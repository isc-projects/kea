// Copyright (C) 2013-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file   dhcp6_test_utils.h
///
/// @brief This file contains utility classes used for DHCPv6 server testing

#ifndef DHCP6_TEST_UTILS_H
#define DHCP6_TEST_UTILS_H

#include <gtest/gtest.h>

#include <dhcp6/dhcp6_srv.h>
#include <dhcp6/parser_context.h>
#include <dhcp/pkt6.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/option6_status_code.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_custom.h>
#include <dhcp/option.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <hooks/hooks_manager.h>
#include <util/multi_threading_mgr.h>

#include <list>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Generic wrapper to provide strongly typed values.
///
/// In many cases, the test fixture class methods require providing many
/// parameters, of which some are optional. Some of the parameters may also
/// be implicitly converted to other types. Non-careful test implementer
/// may often "shift by one" or swap two values on the arguments list, which
/// will be accepted by the compiler but will result in troubles running the
/// function. Sometimes it takes non trivial amount of debugging to find out
/// why the particular function fails until we find that the arguments were
/// swapped or shifted. In addition, the use of classes wrapping simple types
/// results in better readability of the test code.
///
/// @tparam ValueType Type of the wrapped value.
template<typename ValueType>
struct SpecializedTypeWrapper {

    /// @brief Constructor
    ///
    /// @param value Wrapped value
    explicit SpecializedTypeWrapper(const ValueType& value)
        : value_(value) { }

    /// @brief Operator returning a wrapped value.
    operator ValueType () const {
        return (value_);
    }

    /// @brief Wrapped value.
    ValueType value_;
};

/// @brief Class representing strongly typed IAID.
struct IAID : public SpecializedTypeWrapper<uint32_t> {
    /// @brief Constructor
    ///
    /// @param iaid IAID.
    explicit IAID(const uint32_t iaid)
        : SpecializedTypeWrapper<uint32_t>(iaid) { }
};

/// @brief Class representing strongly typed value for strict IAID checks.
///
/// Strict IAID checks are used to verify that the particular address has been
/// assign to a specific IA. In many cases we don't check that because it may
/// not be possible to predict to which IA the specific lease will be assigned.
struct StrictIAIDChecking : public SpecializedTypeWrapper<bool> {
    /// @brief Constructor.
    ///
    /// @param strict_check Boolean value indicating if strict checking should
    /// be performed.
    explicit StrictIAIDChecking(const bool strict_check)
        : SpecializedTypeWrapper<bool>(strict_check) { }

    /// @brief Convenience function returning an object indicating that strict
    /// checks should be performed.
    static const StrictIAIDChecking YES() {
        static StrictIAIDChecking strict_check(true);
        return (strict_check);
    }

    /// @brief Convenience function returning an object indicating that strict
    /// checks should not be performed.
    static StrictIAIDChecking NO() {
        static StrictIAIDChecking strict_check(false);
        return (strict_check);
    }
};

/// @brief Base class for DHCPv6 server testing.
///
/// Currently it configures the test data path directory in
/// the @c CfgMgr. When the object is destroyed, the original
/// path is reverted.
class BaseServerTest : public ::testing::Test {
public:

    /// @brief Location of a test DUID file
    static const char* DUID_FILE;

    /// @brief Constructor.
    BaseServerTest();

    /// @brief Destructor.
    virtual ~BaseServerTest();

private:

    /// @brief Holds the original data directory.
    std::string original_datadir_;
};

/// @brief "naked" Dhcpv6Srv class that exposes internal members
class NakedDhcpv6Srv: public isc::dhcp::Dhcpv6Srv {
public:
    NakedDhcpv6Srv(uint16_t port) : isc::dhcp::Dhcpv6Srv(port) {
        // Open the "memfile" database for leases
        std::string memfile = "type=memfile universe=6 persist=false";
        isc::dhcp::LeaseMgrFactory::create(memfile);
        LeaseMgr::setIOService(getIOService());
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
            isc::dhcp::Pkt6Ptr pkt = fake_received_.front();
            fake_received_.pop_front();
            return (pkt);
        }

        // Make sure the server processed all packets in MT.
        isc::util::MultiThreadingMgr::instance().getThreadPool().wait(3);

        // If not, just trigger shutdown and
        // return immediately
        shutdown();
        return (isc::dhcp::Pkt6Ptr());
    }

    /// @brief fake packet sending
    ///
    /// Pretend to send a packet, but instead just store
    /// it in fake_send_ list where test can later inspect
    /// server's response.
    virtual void sendPacket(const isc::dhcp::Pkt6Ptr& pkt) {
        isc::util::MultiThreadingLock lock(mutex_);
        fake_sent_.push_back(pkt);
    }

    /// @brief fake receive packet from server
    ///
    /// The client uses this packet as a reply from the server.
    ///
    /// @return The received packet.
    Pkt6Ptr receiveOneMsg() {
        // Make sure the server processed all packets.
        isc::util::MultiThreadingMgr::instance().getThreadPool().wait(2);

        // Lock the mutex for the rest of the function.
        isc::util::MultiThreadingLock lock(mutex_);

        // Return empty pointer if server hasn't responded.
        if (fake_sent_.empty()) {
            return (Pkt6Ptr());
        }

        Pkt6Ptr msg = fake_sent_.front();
        fake_sent_.pop_front();
        return (msg);
    }

    /// @brief adds a packet to fake receive queue
    ///
    /// See fake_received_ field for description
    void fakeReceive(const isc::dhcp::Pkt6Ptr& pkt) {
        fake_received_.push_back(pkt);
    }

    virtual ~NakedDhcpv6Srv() {
        // Close the lease database
        isc::dhcp::LeaseMgrFactory::destroy();
    }

    /// @brief Processes incoming Solicit message.
    ///
    /// @param request a message received from client
    /// @return REPLY message or null
    Pkt6Ptr processSolicit(const Pkt6Ptr& solicit) {
        AllocEngine::ClientContext6 ctx;
        bool drop = !earlyGHRLookup(solicit, ctx);
        initContext(solicit, ctx, drop);
        if (drop) {
            return (Pkt6Ptr());
        }
        return (processSolicit(ctx));
    }

    /// @brief Processes incoming Request message.
    ///
    /// @param request a message received from client
    /// @return REPLY message or null
    Pkt6Ptr processRequest(const Pkt6Ptr& request) {
        AllocEngine::ClientContext6 ctx;
        bool drop = !earlyGHRLookup(request, ctx);
        initContext(request, ctx, drop);
        if (drop) {
            return (Pkt6Ptr());
        }
        return (processRequest(ctx));
    }

    /// @brief Processes incoming Renew message.
    ///
    /// @param renew a message received from client
    /// @return REPLY message or null
    Pkt6Ptr processRenew(const Pkt6Ptr& renew) {
        AllocEngine::ClientContext6 ctx;
        bool drop = !earlyGHRLookup(renew, ctx);
        initContext(renew, ctx, drop);
        if (drop) {
            return (Pkt6Ptr());
        }
        return (processRenew(ctx));
    }

    /// @brief Processes incoming Rebind message.
    ///
    /// @param rebind a message received from client
    /// @return REPLY message or null
    Pkt6Ptr processRebind(const Pkt6Ptr& rebind) {
        AllocEngine::ClientContext6 ctx;
        bool drop = !earlyGHRLookup(rebind, ctx);
        initContext(rebind, ctx, drop);
        if (drop) {
            return (Pkt6Ptr());
        }
        return (processRebind(ctx));
    }

    /// @brief Processes incoming Release message.
    ///
    /// @param release a message received from client
    /// @return REPLY message or null
    Pkt6Ptr processRelease(const Pkt6Ptr& release) {
        AllocEngine::ClientContext6 ctx;
        bool drop = !earlyGHRLookup(release, ctx);
        initContext(release, ctx, drop);
        if (drop) {
            return (Pkt6Ptr());
        }
        return (processRelease(ctx));
    }

    /// @brief Processes incoming Decline message.
    ///
    /// @param decline a message received from client
    /// @return REPLY message or null
    Pkt6Ptr processDecline(const Pkt6Ptr& decline) {
        AllocEngine::ClientContext6 ctx;
        bool drop = !earlyGHRLookup(decline, ctx);
        initContext(decline, ctx, drop);
        if (drop) {
            return (Pkt6Ptr());
        }
        return (processDecline(ctx));
    }

    using Dhcpv6Srv::processSolicit;
    using Dhcpv6Srv::processRequest;
    using Dhcpv6Srv::processRenew;
    using Dhcpv6Srv::processRebind;
    using Dhcpv6Srv::processConfirm;
    using Dhcpv6Srv::processRelease;
    using Dhcpv6Srv::processDecline;
    using Dhcpv6Srv::processInfRequest;
    using Dhcpv6Srv::processClientFqdn;
    using Dhcpv6Srv::createNameChangeRequests;
    using Dhcpv6Srv::selectSubnet;
    using Dhcpv6Srv::testServerID;
    using Dhcpv6Srv::testUnicast;
    using Dhcpv6Srv::sanityCheck;
    using Dhcpv6Srv::classifyPacket;
    using Dhcpv6Srv::shutdown_;
    using Dhcpv6Srv::name_change_reqs_;
    using Dhcpv6Srv::VENDOR_CLASS_PREFIX;
    using Dhcpv6Srv::earlyGHRLookup;
    using Dhcpv6Srv::initContext;
    using Dhcpv6Srv::server_port_;
    using Dhcpv6Srv::client_port_;

    /// @brief packets we pretend to receive.
    ///
    /// Instead of setting up sockets on interfaces that change between
    /// OSes, it is much easier to fake packet reception. This is a list
    /// of packets that we pretend to have received. You can schedule
    /// new packets to be received using fakeReceive() and
    /// NakedDhcpv6Srv::receivePacket() methods.
    std::list<isc::dhcp::Pkt6Ptr> fake_received_;

    /// @brief packets we pretend to send.
    std::list<isc::dhcp::Pkt6Ptr> fake_sent_;

    /// @brief Mutex to protect the packet buffers.
    std::mutex mutex_;
};

/// @brief Test fixture for any tests requiring blank/empty configuration
///        serves as base class for additional tests
class NakedDhcpv6SrvTest : public BaseServerTest {
public:

    /// @brief Constructor
    NakedDhcpv6SrvTest();

    /// @brief Generate IA_NA or IA_PD option with specified parameters
    ///
    /// @param type The option type (usually 4 for IA_NA, 25 for IA_PD)
    /// @param iaid The identity association identifier (id of IA)
    /// @param t1 The T1 time
    /// @param t2 The t2 time
    /// @return The generated option
    boost::shared_ptr<isc::dhcp::Option6IA> generateIA(uint16_t type,
                                                       uint32_t iaid,
                                                       uint32_t t1,
                                                       uint32_t t2);

    /// @brief generates interface-id option, based on text
    ///
    /// @param iface_id textual representation of the interface-id content
    ///
    /// @return pointer to the option object
    isc::dhcp::OptionPtr generateInterfaceId(const std::string& iface_id) {
        isc::dhcp::OptionBuffer tmp(iface_id.begin(), iface_id.end());
        return (isc::dhcp::OptionPtr(new isc::dhcp::Option(isc::dhcp::Option::V6,
                                                           D6O_INTERFACE_ID, tmp)));
    }

    /// @brief Generate binary data option
    ///
    /// Creates an Option in the V6 space with the given type and binary data
    /// of the given number of bytes. The data is initialized to the values
    /// 100 to 100 + n, where n is the desired number of bytes.
    ///
    /// @param type option type for the new option
    /// @param data_size number of bytes of data to generate
    ///
    /// @return Pointer to the new option
    isc::dhcp::OptionPtr generateBinaryOption(const DHCPv6OptionType type,
                                              size_t data_size) {
        if (data_size == 0) {
            return (isc::dhcp::OptionPtr
                    (new isc::dhcp::Option(isc::dhcp::Option::V6, type)));

        }

        isc::dhcp::OptionBuffer data_data(data_size);
        for (size_t i = 0; i < data_size; i++) {
            data_data[i] = 100 + i;
        }

        return (isc::dhcp::OptionPtr
                (new isc::dhcp::Option(isc::dhcp::Option::V6, type,
                                       data_data.begin(),
                                       data_data.begin() + data_size)));
    }

    // Generate client-id option
    isc::dhcp::OptionPtr generateClientId(size_t duid_size = 32) {
        isc::dhcp::OptionPtr opt = generateBinaryOption(D6O_CLIENTID, duid_size);
        duid_ = isc::dhcp::DuidPtr(new isc::dhcp::DUID(opt->getData()));
        return (opt);
    }

    /// Generate server-id option
    /// @param duid_size size of the duid
    isc::dhcp::OptionPtr generateServerId(size_t duid_size = 32) {
        isc::dhcp::OptionPtr opt = generateBinaryOption(D6O_SERVERID, duid_size);
        duid_ = isc::dhcp::DuidPtr(new isc::dhcp::DUID(opt->getData()));
        return (opt);
    }

    // Checks if server response (ADVERTISE or REPLY) includes proper
    // server-id.
    void checkServerId(const isc::dhcp::Pkt6Ptr& rsp,
                       const isc::dhcp::OptionPtr& expected_srvid) {
        // check that server included its server-id
        isc::dhcp::OptionPtr tmp = rsp->getOption(D6O_SERVERID);
        EXPECT_EQ(tmp->getType(), expected_srvid->getType() );
        ASSERT_EQ(tmp->len(), expected_srvid->len() );
        EXPECT_TRUE(tmp->getData() == expected_srvid->getData());
    }

    // Checks if server response (ADVERTISE or REPLY) includes proper
    // client-id.
    void checkClientId(const isc::dhcp::Pkt6Ptr& rsp,
                       const isc::dhcp::OptionPtr& expected_clientid) {
        // check that server included our own client-id
        isc::dhcp::OptionPtr tmp = rsp->getOption(D6O_CLIENTID);
        ASSERT_TRUE(tmp);
        EXPECT_EQ(expected_clientid->getType(), tmp->getType());
        ASSERT_EQ(expected_clientid->len(), tmp->len());

        // check that returned client-id is valid
        EXPECT_TRUE(expected_clientid->getData() == tmp->getData());
    }

    // Checks if server response is a NAK
    void checkNakResponse(const isc::dhcp::Pkt6Ptr& rsp,
                          uint8_t expected_message_type,
                          uint32_t expected_transid,
                          uint16_t expected_status_code,
                          uint32_t expected_t1, uint32_t expected_t2) {
        // Check if we get response at all
        checkResponse(rsp, expected_message_type, expected_transid);

        // Check that IA_NA was returned
        isc::dhcp::OptionPtr option_ia_na = rsp->getOption(D6O_IA_NA);
        ASSERT_TRUE(option_ia_na);

        // check that the status is no address available
        boost::shared_ptr<isc::dhcp::Option6IA> ia =
            boost::dynamic_pointer_cast<isc::dhcp::Option6IA>(option_ia_na);
        ASSERT_TRUE(ia);

        checkIA_NAStatusCode(ia, expected_status_code, expected_t1,
                             expected_t2);
    }

    /// @brief Checks that the server inserted expected status code in IA_NA
    ///
    /// Check that the server used status code as expected, i.e. that it has
    /// no addresses (if status code is non-zero) and that expected status
    /// code really appears there. In some limited cases (reply to RELEASE)
    /// it may be used to verify positive case, where IA_NA response is
    /// expected to not include address.
    ///
    /// Status code indicates type of error encountered (in theory it can also
    /// indicate success, but servers typically don't send success status
    /// as this is the default result and it saves bandwidth)
    /// @param ia IA_NA container to be checked
    /// @param expected_status_code expected value in status-code option
    /// @param expected_t1 expected T1 in IA_NA option
    /// @param expected_t2 expected T2 in IA_NA option
    /// @param check_addr whether to check for address with 0 lifetimes
    void checkIA_NAStatusCode(const boost::shared_ptr<isc::dhcp::Option6IA>& ia,
                              uint16_t expected_status_code,
                              uint32_t expected_t1,
                              uint32_t expected_t2,
                              bool check_addr = true);

    void checkMsgStatusCode(const isc::dhcp::Pkt6Ptr& msg,
                            uint16_t expected_status) {
        isc::dhcp::Option6StatusCodePtr status =
            boost::dynamic_pointer_cast<isc::dhcp::Option6StatusCode>
                (msg->getOption(D6O_STATUS_CODE));

        // It is ok to not include status success as this is the default
        // behavior
        if (expected_status == STATUS_Success && !status) {
            return;
        }

        EXPECT_TRUE(status);
        if (status) {
            // We don't have dedicated class for status code, so let's
            // just interpret first 2 bytes as status. Remainder of the
            // status code option content is just a text explanation
            // what went wrong.
            EXPECT_EQ(static_cast<uint16_t>(expected_status),
                      status->getStatusCode());
        }
    }

    // Basic checks for generated response (message type and transaction-id).
    void checkResponse(const isc::dhcp::Pkt6Ptr& rsp,
                       uint8_t expected_message_type,
                       uint32_t expected_transid) {
        ASSERT_TRUE(rsp);
        EXPECT_EQ(expected_message_type, rsp->getType());
        EXPECT_EQ(expected_transid, rsp->getTransid());
    }

    virtual ~NakedDhcpv6SrvTest();

    // A DUID used in most tests (typically as client-id)
    isc::dhcp::DuidPtr duid_;

    int rcode_;
    isc::data::ConstElementPtr comment_;

    // Name of a valid network interface
    std::string valid_iface_;

    // Index of a valid network interface
    uint32_t valid_ifindex_;
};

// We need to pass one reference to the Dhcp6Client, which is defined in
// dhcp6_client.h. That header includes this file. To avoid circular
// dependencies, we use forward declaration here.
class Dhcp6Client;

// Provides support for tests against a preconfigured subnet6
// extends upon NakedDhcp6SrvTest
class Dhcpv6SrvTest : public NakedDhcpv6SrvTest {
public:
    /// @brief Specifies expected outcome
    enum ExpectedResult {
        SHOULD_PASS, // pass = accept decline, move lease to declined state.
        SHOULD_FAIL  // fail = reject the decline
    };

    /// @brief Specifies what address should the client include in its Decline
    enum AddressInclusion {
        VALID_ADDR, // Client will include its own, valid address
        BOGUS_ADDR, // Client will include an address it doesn't own
        NO_ADDR,    // Client will send empty IA_NA (without address)
        NO_IA       // Client will not send IA_NA at all
    };

    /// @brief Specifies if lease affinity is enabled or disabled
    enum LeaseAffinity {
        LEASE_AFFINITY_ENABLED,
        LEASE_AFFINITY_DISABLED
    };

    class Dhcpv6SrvMTTestGuard {
    public:
        Dhcpv6SrvMTTestGuard(Dhcpv6SrvTest& test, bool mt_enabled) : test_(test) {
            test_.setMultiThreading(mt_enabled);
        }
        ~Dhcpv6SrvMTTestGuard() {
            test_.setMultiThreading(false);
        }
        Dhcpv6SrvTest& test_;
    };

    /// @brief Constructor that initializes a simple default configuration
    ///
    /// Sets up a single subnet6 with one pool for addresses and second
    /// pool for prefixes.
    Dhcpv6SrvTest();

    /// @brief Destructor
    ///
    /// Removes existing configuration.
    ~Dhcpv6SrvTest();

    /// @brief Used to configure a server for tests.
    ///
    /// A wrapper over configureDhcp6Server() to which any other
    /// simulations of production code are added.
    ///
    /// @brief server the server being tested
    /// @brief config the configuration the server is configured with
    ///
    /// @return a JSON-formatted status of the reconfiguration
    static ConstElementPtr configure(Dhcpv6Srv& server, isc::data::ConstElementPtr config);

    /// @brief Runs DHCPv6 configuration from the JSON string.
    ///
    /// @param config String holding server configuration in JSON format.
    /// @param commit A boolean flag indicating if the new configuration
    /// should be committed (if true), or not (if false).
    /// @param open_sockets A boolean flag indicating if sockets should
    /// be opened (if true), or not (if false).
    /// @param create_managers A boolean flag indicating if managers should be
    /// recreated.
    /// @param test A boolean flag which indicates if only testing config.
    /// @param lease_affinity A flag which indicates if lease affinity should
    /// be enabled or disabled.
    void configure(const std::string& config,
                   const bool commit = true,
                   const bool open_sockets = false,
                   const bool create_managers = true,
                   const bool test = false,
                   const LeaseAffinity lease_affinity = LEASE_AFFINITY_DISABLED);

    /// @brief Configure the DHCPv6 server using the JSON string.
    ///
    /// @param config String holding server configuration in JSON format.
    /// @param srv Server to be configured.
    /// @param commit A boolean flag indicating if the new configuration
    /// should be committed (if true), or not (if false).
    /// @param open_sockets A boolean flag indicating if sockets should
    /// be opened (if true), or not (if false).
    /// @param create_managers A boolean flag indicating if managers should be
    /// recreated.
    /// @param test A boolean flag which indicates if only testing config.
    /// @param lease_affinity A flag which indicates if lease affinity should
    /// be enabled or disabled.
    void configure(const std::string& config,
                   NakedDhcpv6Srv& srv,
                   const bool commit = true,
                   const bool open_sockets = false,
                   const bool create_managers = true,
                   const bool test = false,
                   const LeaseAffinity lease_affinity = LEASE_AFFINITY_DISABLED);

    /// @brief Checks that server response (ADVERTISE or REPLY) contains proper
    ///        IA_NA option
    ///
    /// @param rsp server's response
    /// @param expected_iaid expected IAID value
    /// @param expected_t1 expected T1 value
    /// @param expected_t2 expected T2 value
    /// @return IAADDR option for easy chaining with checkIAAddr method
    boost::shared_ptr<isc::dhcp::Option6IAAddr>
    checkIA_NA(const isc::dhcp::Pkt6Ptr& rsp, uint32_t expected_iaid,
               uint32_t expected_t1, uint32_t expected_t2);

    /// @brief Checks that server response (ADVERTISE or REPLY) contains proper
    ///        IA_PD option
    ///
    /// @param rsp server's response
    /// @param expected_iaid expected IAID value
    /// @param expected_t1 expected T1 value
    /// @param expected_t2 expected T2 value
    /// @return IAPREFIX option for easy chaining with checkIAAddr method
    boost::shared_ptr<isc::dhcp::Option6IAPrefix>
    checkIA_PD(const isc::dhcp::Pkt6Ptr& rsp, uint32_t expected_iaid,
               uint32_t expected_t1, uint32_t expected_t2);

    // Check that generated IAADDR option contains expected address
    // and lifetime values match the configured subnet
    /// @param expected_pref check that lease preferedlifetime has the not-zero
    /// expected value (zero value means that do not check).
    /// @param expected_valid check that lease valid lifetime has the not-zero
    /// expected value (zero value means that do not check).
    void checkIAAddr(const boost::shared_ptr<isc::dhcp::Option6IAAddr>& addr,
                     const isc::asiolink::IOAddress& expected_addr,
                     isc::dhcp::Lease::Type type,
                     uint32_t expected_pref = 0,
                     uint32_t expected_valid = 0) {

        // Check that the assigned address is indeed from the configured pool.
        // Note that when comparing addresses, we compare the textual
        // representation. IOAddress does not support being streamed to
        // an ostream, which means it can't be used in EXPECT_EQ.
        EXPECT_TRUE(subnet_->inPool(type, addr->getAddress()));
        EXPECT_EQ(expected_addr.toText(), addr->getAddress().toText());
        if (subnet_->getPreferred().getMin() != subnet_->getPreferred().getMax()) {
            EXPECT_LE(subnet_->getPreferred().getMin(), addr->getPreferred());
            EXPECT_GE(subnet_->getPreferred().getMax(), addr->getPreferred());
        } else {
            EXPECT_EQ(subnet_->getPreferred(), addr->getPreferred());
        }
        if (subnet_->getValid().getMin() != subnet_->getValid().getMax()) {
            EXPECT_LE(subnet_->getValid().getMin(), addr->getValid());
            EXPECT_GE(subnet_->getValid().getMax(), addr->getValid());
        } else {
            EXPECT_EQ(subnet_->getValid(), addr->getValid());
        }
        if (expected_pref) {
            EXPECT_EQ(expected_pref, addr->getPreferred());
        }
        if (expected_valid) {
            EXPECT_EQ(expected_valid, addr->getValid());
        }
    }

    // Checks if the lease sent to client is present in the database
    // and is valid when checked against the configured subnet
    isc::dhcp::Lease6Ptr
    checkLease(const isc::dhcp::DuidPtr& duid,
               const isc::dhcp::OptionPtr& ia_na,
               boost::shared_ptr<isc::dhcp::Option6IAAddr> addr);

    /// @brief Check if the specified lease is present in the data base.
    ///
    /// @param lease Lease to be searched in the database.
    /// @return Pointer to the lease in the database.
    isc::dhcp::Lease6Ptr checkLease(const isc::dhcp::Lease6& lease);

    /// @brief Verifies received IAPrefix option
    ///
    /// Verifies if the received IAPrefix option matches the lease in the
    /// database.
    ///
    /// @param duid client's DUID
    /// @param ia_pd IA_PD option that contains the IAPRefix option
    /// @param prefix pointer to the IAPREFIX option
    /// @return corresponding IPv6 lease (if found)
    isc::dhcp::Lease6Ptr
    checkPdLease(const isc::dhcp::DuidPtr& duid,
                 const isc::dhcp::OptionPtr& ia_pd,
                 boost::shared_ptr<isc::dhcp::Option6IAPrefix> prefix);

    /// @brief Creates a message with specified IA
    ///
    /// A utility function that creates a message of the specified type with
    /// a specified container (IA_NA or IA_PD) and an address or prefix
    /// inside it.
    ///
    /// @param message_type type of the message (e.g. DHCPV6_SOLICIT)
    /// @param lease_type type of a lease (TYPE_NA or TYPE_PD)
    /// @param addr address or prefix to use in IADDRESS or IAPREFIX options
    /// @param prefix_len length of the prefix (used for prefixes only)
    /// @param iaid IA identifier (used in IA_XX option)
    /// @return created message
    isc::dhcp::Pkt6Ptr
    createMessage(uint8_t message_type, isc::dhcp::Lease::Type lease_type,
                  const isc::asiolink::IOAddress& addr,
                  const uint8_t prefix_len, const uint32_t iaid);

    /// @brief Creates instance of IA option holding single address or prefix.
    ///
    /// Utility function that creates an IA option instance with a single
    /// IPv6 address or prefix. This function is internally called by the
    /// @c createMessage function. It may be also used to add additional
    /// IA options to the message generated by @c createMessage (which adds
    /// a single IA option by itself.).
    ///
    /// @param lease_type type of the lease (TYPE_NA or TYPE_PD).
    /// @param addr address or prefix to use in IADDRESS or IAPREFIX options.
    /// @param prefix_len length of the prefix (used for PD, ignored for NA).
    /// @param iaid IA identifier.
    ///
    /// @return Created instance of the IA option.
    isc::dhcp::Option6IAPtr
    createIA(isc::dhcp::Lease::Type lease_type,
             const isc::asiolink::IOAddress& addr,
             const uint8_t prefix_len, const uint32_t iaid);

    /// @brief Compare options
    ///
    /// This method compares whether options content is identical. It writes
    /// both options to a buffer and then compares the buffers. Comparing
    /// two different instances of an option that has identical content
    /// will return true.
    ///
    /// It is safe to pass null pointers. Two null pointers are equal.
    /// null pointer and non-null pointers are obviously non-equal.
    ///
    /// @param option1 pointer to the first option
    /// @param option2
    /// @return true, if content is identical
    bool compareOptions(const isc::dhcp::OptionPtr& option1,
                        const isc::dhcp::OptionPtr& option2);

    /// @brief Tests if the acquired lease is or is not declined.
    ///
    /// @param client Dhcp6Client instance
    /// @param duid1 DUID used during lease acquisition
    /// @param iaid1 IAID used during lease acquisition
    /// @param duid2 DUID used during Decline exchange
    /// @param iaid2 IAID used during Decline exchange
    /// @param addr_type specify what sort of address the client should
    ///        include (its own, a bogus one or no address at all)
    /// @param expected_result SHOULD_PASS if the lease is expected to
    /// be successfully declined, or SHOULD_FAIL if the lease is expected
    /// to not be declined.
    void acquireAndDecline(Dhcp6Client& client,
                           const std::string& duid1,
                           const uint32_t iaid1,
                           const std::string& duid2,
                           const uint32_t iaid2,
                           AddressInclusion addr_type,
                           ExpectedResult expected_result);

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
    /// @param prefix_len length of the prefix (128 for addresses)
    /// @param insert_before_renew should the lease be inserted into the database
    ///        before we try renewal?
    /// @param expire_before_renew should the lease be expired before we try
    ///        renewal?
    /// @param hint_pref preferred lifetime hint (default is 300)
    /// @param hint_valid valid lifetime hint (default is 500)
    /// @param expected_pref expected preferred lifetime (zero means not check)
    /// @param expected_valid expected valid lifetime (zero means not check)
    void
    testRenewBasic(isc::dhcp::Lease::Type type,
                   const std::string& existing_addr,
                   const std::string& renew_addr, const uint8_t prefix_len,
                   bool insert_before_renew = true,
                   bool expire_before_renew = false,
                   uint32_t hint_pref = 300, uint32_t hint_valid = 500,
                   uint32_t expected_pref = 0, uint32_t expected_valid = 0);

    /// @brief Checks if RENEW with invalid IAID is processed correctly.
    ///
    /// @param type lease type (currently only IA_NA is supported)
    /// @param addr address to be renewed
    void
    testRenewWrongIAID(isc::dhcp::Lease::Type type,
                       const asiolink::IOAddress& addr);

    /// @brief Checks if client A can renew address used by client B
    ///
    /// @param type lease type (currently only IA_NA is supported)
    /// @param addr address to be renewed
    void
    testRenewSomeoneElsesLease(isc::dhcp::Lease::Type type,
                               const asiolink::IOAddress& addr);

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
    /// @param lease_affinity A flag which indicates if lease affinity should
    /// be enabled or disabled.
    void
    testReleaseBasic(isc::dhcp::Lease::Type type,
                     const isc::asiolink::IOAddress& existing,
                     const isc::asiolink::IOAddress& release_addr,
                     const LeaseAffinity lease_affinity);

    /// @brief Checks that reassignement of a released-expired lease
    /// does not lead to zero lifetimes.
    ///
    /// This method does not throw, but uses gtest macros to signify failures.
    ///
    /// @param type lease type (TYPE_NA or TYPE_PD).
    /// @param addr lease address.
    /// @param qtype query type.
    void
    testReleaseNoDelete(isc::dhcp::Lease::Type type,
                        const isc::asiolink::IOAddress& addr,
                        uint8_t qtype);

    /// @brief Performs negative RELEASE test
    ///
    /// See releaseReject and pdReleaseReject tests for detailed
    /// explanation. In essence the test attempts to perform couple
    /// failed RELEASE scenarios.
    ///
    /// This method does not throw, but uses gtest macros to signify failures.
    ///
    /// @param type type (TYPE_NA or TYPE_PD)
    /// @param addr address being sent in RELEASE
    void
    testReleaseReject(isc::dhcp::Lease::Type type,
                      const isc::asiolink::IOAddress& addr);

    /// @brief simulates reception of a packet of specified type and checks statistic
    ///
    /// @param pkt_type reception of a packet of this type will be simulated
    /// @param stat_name this statistic is expected to be set to 1
    void testReceiveStats(uint8_t pkt_type, const std::string& stat_name);

    /// @brief Set multi-threading mode.
    void setMultiThreading(bool enabled) {
        multi_threading_ = enabled;
    }

    /// @brief Check if example files contain valid configuration.
    void checkConfigFiles();

    /// @brief Check if the server configuration stored in file is valid.
    ///
    /// @param path The path to the configuration file.
    void loadConfigFile(const std::string& path);

    /// A subnet used in most tests.
    isc::dhcp::Subnet6Ptr subnet_;

    /// A normal, non-temporary pool used in most tests.
    isc::dhcp::Pool6Ptr pool_;

    /// A prefix pool used in most tests.
    isc::dhcp::Pool6Ptr pd_pool_;

    /// @brief Server object under test.
    NakedDhcpv6Srv srv_;

    /// @brief The multi-threading flag.
    bool multi_threading_;
};

/// @brief Patch the server config to add interface-config/re-detect=false
/// @param json the server config
inline void
disableIfacesReDetect(isc::data::ConstElementPtr json) {
    isc::data::ConstElementPtr ifaces_cfg = json->get("interfaces-config");
    if (ifaces_cfg) {
        isc::data::ElementPtr mutable_cfg =
            boost::const_pointer_cast<isc::data::Element>(ifaces_cfg);
        mutable_cfg->set("re-detect", isc::data::Element::create(false));
    }
}

/// @brief Patch the server config to add multi-threading/enable-multi-threading
/// @param json the server config
inline void
configureMultiThreading(bool enabled, isc::data::ConstElementPtr json) {
    isc::data::ConstElementPtr multi_threading = json->get("multi-threading");
    if (!multi_threading) {
        isc::data::ElementPtr mutable_cfg =
                boost::const_pointer_cast<isc::data::Element>(json);
        multi_threading = isc::data::Element::createMap();
        mutable_cfg->set("multi-threading", multi_threading);
    }

    isc::data::ElementPtr mutable_cfg =
        boost::const_pointer_cast<isc::data::Element>(multi_threading);
    if (enabled) {
        mutable_cfg->set("enable-multi-threading", isc::data::Element::create(true));
        mutable_cfg->set("thread-pool-size", isc::data::Element::create(4));
        mutable_cfg->set("packet-queue-size", isc::data::Element::create(4));
    } else {
        mutable_cfg->set("enable-multi-threading", isc::data::Element::create(false));
    }
}

/// @brief Runs parser in JSON mode, useful for parser testing
///
/// @param in string to be parsed
/// @return ElementPtr structure representing parsed JSON
inline isc::data::ElementPtr
parseJSON(const std::string& in) {
    isc::dhcp::Parser6Context ctx;
    return (ctx.parseString(in, isc::dhcp::Parser6Context::PARSER_JSON));
}

/// @brief Runs parser in Dhcp6 mode
///
/// This is a simplified Dhcp6 mode, so no outer { } and "Dhcp6" is
/// needed. This format is used by most of the tests.
///
/// @param in string to be parsed
/// @param verbose display the exception message when it fails
/// @return ElementPtr structure representing parsed JSON
inline isc::data::ElementPtr
parseDHCP6(const std::string& in, bool verbose = false) {
    try {
        isc::dhcp::Parser6Context ctx;
        isc::data::ElementPtr json;
        json = ctx.parseString(in, isc::dhcp::Parser6Context::SUBPARSER_DHCP6);
        disableIfacesReDetect(json);
        return (json);
    }
    catch (const std::exception& ex) {
        if (verbose) {
            std::cout << "EXCEPTION: " << ex.what() << std::endl;
        }
        throw;
    }
}

/// @brief Runs parser in option definition mode
///
/// This function parses specified text as JSON that defines option definitions.
///
/// @param in string to be parsed
/// @param verbose display the exception message when it fails
/// @return ElementPtr structure representing parsed JSON
inline isc::data::ElementPtr
parseOPTION_DEFS(const std::string& in, bool verbose = false) {
    try {
        isc::dhcp::Parser6Context ctx;
        return (ctx.parseString(in, isc::dhcp::Parser6Context::PARSER_OPTION_DEFS));
    }
    catch (const std::exception& ex) {
        if (verbose) {
            std::cout << "EXCEPTION: " << ex.what() << std::endl;
        }
        throw;
    }
}

} // end of isc::dhcp::test namespace
} // end of isc::dhcp namespace
} // end of isc namespace

#endif // DHCP6_TEST_UTILS_H
