// Copyright (C) 2013-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file   dhcp4_test_utils.h
///
/// @brief This file contains utility classes used for DHCPv4 server testing

#ifndef DHCP4_TEST_UTILS_H
#define DHCP4_TEST_UTILS_H

#include <gtest/gtest.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt_filter.h>
#include <dhcp/pkt_filter_inet.h>
#include <dhcpsrv/alloc_engine.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcp4/dhcp4_srv.h>
#include <dhcp4/parser_context.h>
#include <asiolink/io_address.h>
#include <cc/command_interpreter.h>
#include <util/multi_threading_mgr.h>
#include <list>

#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Dummy Packet Filtering class.
///
/// This class reports capability to respond directly to the client which
/// doesn't have address configured yet.
///
/// All packet and socket handling functions do nothing because they are not
/// used in unit tests.
class PktFilterTest : public PktFilter {
public:

    /// @brief Constructor.
    ///
    /// Sets the 'direct response' capability to true.
    PktFilterTest()
        : direct_resp_supported_(true) {
    }

    /// @brief Reports 'direct response' capability.
    ///
    /// @return always true.
    virtual bool isDirectResponseSupported() const {
        return (direct_resp_supported_);
    }

    /// Does nothing.
    virtual SocketInfo openSocket(Iface&,
                                  const isc::asiolink::IOAddress& addr,
                                  const uint16_t port, const bool, const bool) {
        return (SocketInfo(addr, port, 0));
    }

    /// Does nothing.
    virtual Pkt4Ptr receive(Iface&, const SocketInfo&) {
        return Pkt4Ptr();
    }

    /// Does nothing.
    virtual int send(const Iface&, uint16_t, const Pkt4Ptr&) {
        return (0);
    }

    /// @brief Holds a boolean value which indicates whether direct response
    /// capability is supported (true) or not (false).
    bool direct_resp_supported_;

};

typedef boost::shared_ptr<PktFilterTest> PktFilterTestPtr;

/// Forward definition for Dhcp4Client defined in dhcp4_client.h
/// dhcp4_client.h includes dhcp_test_utils.h (this file), so to avoid
/// circular dependencies, we need a forward class declaration.
class Dhcp4Client;

/// @brief "Naked" DHCPv4 server, exposes internal fields
class NakedDhcpv4Srv: public Dhcpv4Srv {
public:

    /// @brief Constructor.
    ///
    /// This constructor disables default modes of operation used by the
    /// Dhcpv4Srv class:
    /// - Send/receive broadcast messages through sockets on interfaces
    /// which support broadcast traffic.
    /// - Direct DHCPv4 traffic - communication with clients which do not
    /// have IP address assigned yet.
    ///
    /// Enabling these modes requires root privileges so they must be
    /// disabled for unit testing.
    ///
    /// Note, that disabling broadcast options on sockets does not impact
    /// the operation of these tests because they use local loopback
    /// interface which doesn't have broadcast capability anyway. It rather
    /// prevents setting broadcast options on other (broadcast capable)
    /// sockets which are opened on other interfaces in Dhcpv4Srv constructor.
    ///
    /// The Direct DHCPv4 Traffic capability can be disabled here because
    /// it is tested with PktFilterLPFTest unittest. The tests which belong
    /// to PktFilterLPFTest can be enabled on demand when root privileges can
    /// be guaranteed.
    ///
    /// @param port port number to listen on; the default value 0 indicates
    /// that sockets should not be opened.
    NakedDhcpv4Srv(uint16_t port = 0)
        : Dhcpv4Srv(port, false, false) {
        // Create a default lease database backend.
        std::string dbconfig = "type=memfile universe=4 persist=false";
        isc::dhcp::LeaseMgrFactory::create(dbconfig);
        // Create fixed server id.
        server_id_.reset(new Option4AddrLst(DHO_DHCP_SERVER_IDENTIFIER,
                                            asiolink::IOAddress("192.0.3.1")));
        LeaseMgr::setIOService(getIOService());
    }

    /// @brief Returns fixed server identifier assigned to the naked server
    /// instance.
    OptionPtr getServerID() const {
        return (server_id_);
    }

    /// @brief fakes packet reception
    /// @param timeout ignored
    ///
    /// The method receives all packets queued in receive queue, one after
    /// another. Once the queue is empty, it initiates the shutdown procedure.
    ///
    /// See fake_received_ field for description
    virtual Pkt4Ptr receivePacket(int /*timeout*/) {

        // If there is anything prepared as fake incoming traffic, use it
        if (!fake_received_.empty()) {
            Pkt4Ptr pkt = fake_received_.front();
            fake_received_.pop_front();
            return (pkt);
        }

        // Make sure the server processed all packets in MT.
        isc::util::MultiThreadingMgr::instance().getThreadPool().wait(3);

        // If not, just trigger shutdown and return immediately
        shutdown();
        return (Pkt4Ptr());
    }

    /// @brief fake packet sending
    ///
    /// Pretend to send a packet, but instead just store it in fake_send_ list
    /// where test can later inspect server's response.
    virtual void sendPacket(const Pkt4Ptr& pkt) {
        if (isc::util::MultiThreadingMgr::instance().getMode()) {
            std::lock_guard<std::mutex> lk(mutex_);
            fake_sent_.push_back(pkt);
        } else {
            fake_sent_.push_back(pkt);
        }
    }

    /// @brief fake receive packet from server
    ///
    /// The client uses this packet as a reply from the server.
    ///
    /// @return The received packet.
    Pkt4Ptr receiveOneMsg() {
        if (isc::util::MultiThreadingMgr::instance().getMode()) {
            std::lock_guard<std::mutex> lk(mutex_);
            return (receiveOneMsgInternal());
        } else {
            return (receiveOneMsgInternal());
        }
    }

    /// @brief fake receive packet from server
    ///
    /// The client uses this packet as a reply from the server.
    /// This function should be called in a thread safe context.
    ///
    /// @return The received packet.
    Pkt4Ptr receiveOneMsgInternal() {
        // Return empty pointer if server hasn't responded.
        if (fake_sent_.empty()) {
            return (Pkt4Ptr());
        }
        Pkt4Ptr msg = fake_sent_.front();
        fake_sent_.pop_front();
        return (msg);
    }

    /// @brief adds a packet to fake receive queue
    ///
    /// See fake_received_ field for description
    void fakeReceive(const Pkt4Ptr& pkt) {
        fake_received_.push_back(pkt);
    }

    virtual ~NakedDhcpv4Srv() {
    }

    /// @brief Runs processing DHCPDISCOVER.
    ///
    /// @param discover a message received from client
    /// @return DHCPOFFER message or null
    Pkt4Ptr processDiscover(Pkt4Ptr& discover) {
        AllocEngine::ClientContext4Ptr context(new AllocEngine::ClientContext4());
        earlyGHRLookup(discover, context);
        return (processDiscover(discover, context));
    }

    /// @brief Runs processing DHCPREQUEST.
    ///
    /// @param request a message received from client
    /// @return DHCPACK or DHCPNAK message
    Pkt4Ptr processRequest(Pkt4Ptr& request) {
        AllocEngine::ClientContext4Ptr context(new AllocEngine::ClientContext4());
        earlyGHRLookup(request, context);
        return (processRequest(request, context));
    }

    /// @brief Runs processing DHCPRELEASE.
    ///
    /// @param release message received from client
    void processRelease(Pkt4Ptr& release) {
        AllocEngine::ClientContext4Ptr context(new AllocEngine::ClientContext4());
        earlyGHRLookup(release, context);
        processRelease(release, context);
    }

    /// @brief Runs processing DHCPDECLINE.
    ///
    /// @param decline message received from client
    void processDecline(Pkt4Ptr& decline) {
        AllocEngine::ClientContext4Ptr context(new AllocEngine::ClientContext4());
        earlyGHRLookup(decline, context);
        processDecline(decline, context);
    }

    /// @brief Runs processing DHCPINFORM.
    ///
    /// @param inform a message received from client
    /// @return DHCPACK message
    Pkt4Ptr processInform(Pkt4Ptr& inform) {
        AllocEngine::ClientContext4Ptr context(new AllocEngine::ClientContext4());
        earlyGHRLookup(inform, context);
        return (processInform(inform, context));
    }

    /// @brief Dummy server identifier option used by various tests.
    OptionPtr server_id_;

    /// @brief packets we pretend to receive.
    ///
    /// Instead of setting up sockets on interfaces that change between OSes, it
    /// is much easier to fake packet reception. This is a list of packets that
    /// we pretend to have received. You can schedule new packets to be received
    /// using fakeReceive() and NakedDhcpv4Srv::receivePacket() methods.
    std::list<Pkt4Ptr> fake_received_;

    /// @brief packets we pretend to send.
    std::list<Pkt4Ptr> fake_sent_;

    using Dhcpv4Srv::adjustIfaceData;
    using Dhcpv4Srv::appendServerID;
    using Dhcpv4Srv::processDiscover;
    using Dhcpv4Srv::processRequest;
    using Dhcpv4Srv::processRelease;
    using Dhcpv4Srv::processDecline;
    using Dhcpv4Srv::processInform;
    using Dhcpv4Srv::processClientName;
    using Dhcpv4Srv::createNameChangeRequests;
    using Dhcpv4Srv::acceptServerId;
    using Dhcpv4Srv::sanityCheck;
    using Dhcpv4Srv::srvidToString;
    using Dhcpv4Srv::classifyPacket;
    using Dhcpv4Srv::deferredUnpack;
    using Dhcpv4Srv::accept;
    using Dhcpv4Srv::acceptMessageType;
    using Dhcpv4Srv::selectSubnet;
    using Dhcpv4Srv::setSendResponsesToSource;
    using Dhcpv4Srv::VENDOR_CLASS_PREFIX;
    using Dhcpv4Srv::shutdown_;
    using Dhcpv4Srv::alloc_engine_;
    using Dhcpv4Srv::server_port_;
    using Dhcpv4Srv::client_port_;

    /// @brief Mutex to protect the packet buffers.
    std::mutex mutex_;
};

// We need to pass one reference to the Dhcp4Client, which is defined in
// dhcp4_client.h. That header includes this file. To avoid circular
// dependencies, we use forward declaration here.
class Dhcp4Client;

/// @brief Base class for DHCPv4 server testing.
///
/// Currently it configures the test data path directory in
/// the @c CfgMgr. When the object is destroyed, the original
/// path is reverted.
class BaseServerTest : public ::testing::Test {
public:

    /// @brief Constructor.
    BaseServerTest();

    /// @brief Destructor.
    virtual ~BaseServerTest();

private:

    /// @brief Holds the original data directory.
    std::string original_datadir_;

};

class Dhcpv4SrvTest : public BaseServerTest {
public:

    enum ExpectedResult {
        SHOULD_PASS, // pass = accept decline, move lease to declined state.
        SHOULD_FAIL  // fail = reject the decline
    };

    class Dhcpv4SrvMTTestGuard {
    public:
        Dhcpv4SrvMTTestGuard(Dhcpv4SrvTest& test, bool mt_enabled) : test_(test) {
            test_.setMultiThreading(mt_enabled);
        }
        ~Dhcpv4SrvMTTestGuard() {
            test_.setMultiThreading(false);
        }
        Dhcpv4SrvTest& test_;
    };

    /// @brief Constructor
    ///
    /// Initializes common objects used in many tests.
    /// Also sets up initial configuration in CfgMgr.
    Dhcpv4SrvTest();

    /// @brief Destructor
    ///
    /// Removes existing configuration.
    virtual ~Dhcpv4SrvTest();

    /// @brief Add 'Parameter Request List' option to the packet.
    ///
    /// This function adds PRL option comprising the following option codes:
    /// - 5 - Name Server
    /// - 15 - Domain Name
    /// - 7 - Log Server
    /// - 8 - Quotes Server
    /// - 9 - LPR Server
    ///
    /// @param pkt packet to add PRL option to.
    void addPrlOption(Pkt4Ptr& pkt);

    /// @brief Configures options being requested in the PRL option.
    ///
    /// The lpr-servers option is NOT configured here although it is
    /// added to the 'Parameter Request List' option in the
    /// \ref addPrlOption. When requested option is not configured
    /// the server should not return it in its response. The goal
    /// of not configuring the requested option is to verify that
    /// the server will not return it.
    void configureRequestedOptions();

    /// @brief Configures server identifier at different levels.
    void configureServerIdentifier();

    /// @brief checks that the response matches request
    ///
    /// @param q query (client's message)
    /// @param a answer (server's message)
    void messageCheck(const Pkt4Ptr& q, const Pkt4Ptr& a);

    /// @brief Check that certain basic (always added when lease is acquired)
    /// are present in a message.
    ///
    /// @param pkt A message to be checked.
    /// @return Assertion result which indicates whether test passed or failed.
    ::testing::AssertionResult basicOptionsPresent(const Pkt4Ptr& pkt);

    /// @brief Check that certain basic (always added when lease is acquired)
    /// are not present.
    ///
    /// @param pkt A packet to be checked.
    /// @return Assertion result which indicates whether test passed or failed.
    ::testing::AssertionResult noBasicOptions(const Pkt4Ptr& pkt);

    /// @brief Check that certain requested options are present in the message.
    ///
    /// @param pkt A message to be checked.
    /// @return Assertion result which indicates whether test passed or failed.
    ::testing::AssertionResult requestedOptionsPresent(const Pkt4Ptr& pkt);

    /// @brief Check that certain options (requested with PRL option)
    /// are not present.
    ///
    /// @param pkt A packet to be checked.
    /// @return Assertion result which indicates whether test passed or failed.
    ::testing::AssertionResult noRequestedOptions(const Pkt4Ptr& pkt);

    /// @brief generates client-id option
    ///
    /// Generate client-id option of specified length
    /// Ids with different lengths are sufficient to generate
    /// unique ids. If more fine grained control is required,
    /// tests generate client-ids on their own.
    /// Sets client_id_ field.
    /// @param size size of the client-id to be generated
    OptionPtr generateClientId(size_t size = 4);

    /// @brief generate hardware address
    ///
    /// @param size size of the generated MAC address
    /// @param pointer to Hardware Address object
    HWAddrPtr generateHWAddr(size_t size = 6);

    /// @brief Convenience method for making a server identifier option instance.
    ///
    /// @param address IP address to add to the option
    ///
    /// @return Pointer to the newly constructed option.
    OptionCustomPtr makeServerIdOption(const isc::asiolink::IOAddress& address);

    /// @brief Convenience method for making a fqdn list option instance.
    ///
    /// @return Pointer to the newly constructed option.
    OptionPtr makeFqdnListOption();

    /// Check that address was returned from proper range, that its lease
    /// lifetime is correct, that T1 and T2 are returned properly
    /// @param rsp response to be checked
    /// @param subnet subnet that should be used to verify assigned address
    ///        and options
    /// @param t1_present check that t1 must be present (true) or must not be
    /// present (false)
    /// @param t2_present check that t2 must be present (true) or must not be
    /// present (false)
    /// @param expected_valid check that lease lifetime has the not-zero
    /// expected value (zero value means that do not check).
    void checkAddressParams(const Pkt4Ptr& rsp, const Subnet4Ptr subnet,
                            bool t1_present = false,
                            bool t2_present = false,
                            uint32_t expected_valid = 0);

    /// @brief Basic checks for generated response (message type and trans-id).
    ///
    /// @param rsp response packet to be validated
    /// @param expected_message_type expected message type
    /// @param expected_transid expected transaction-id
    void checkResponse(const Pkt4Ptr& rsp, int expected_message_type,
                       uint32_t expected_transid);

    /// @brief Checks if the lease sent to client is present in the database
    ///
    /// @param rsp response packet to be validated
    /// @param client_id expected client-identifier (or NULL)
    /// @param HWAddr expected hardware address (not used now)
    /// @param expected_addr expected address
    Lease4Ptr checkLease(const Pkt4Ptr& rsp, const OptionPtr& client_id,
                         const HWAddrPtr&,
                         const isc::asiolink::IOAddress& expected_addr);

    /// @brief Checks if server response (OFFER, ACK, NAK) includes proper server-id
    ///
    /// @param rsp response packet to be validated
    /// @param expected_srvid expected value of server-id
    void checkServerId(const Pkt4Ptr& rsp, const OptionPtr& expected_srvid);

    /// @brief Checks if server response (OFFER, ACK, NAK) includes proper client-id
    ///
    /// This method follows values reported by CfgMgr in echoClientId() method.
    /// Depending on its configuration, the client-id is either mandatory or
    /// forbidden to appear in the response.
    ///
    /// @param rsp response packet to be validated
    /// @param expected_clientid expected value of client-id
    void checkClientId(const Pkt4Ptr& rsp, const OptionPtr& expected_clientid);

    /// @brief Checks the value of the dhcp-server-identifier option in a packet
    ///
    /// @param packet packet to test
    /// @param expected_address IP address the packet's option should contain
    void checkServerIdOption(const Pkt4Ptr& packet, const isc::asiolink::IOAddress& expected_address);

    /// @brief Create packet from output buffer of another packet.
    ///
    /// This function creates a packet using an output buffer from another
    /// packet. This imitates reception of a packet from the wire. The
    /// unpack function is then called to parse packet contents and to
    /// create a collection of the options carried by this packet.
    ///
    /// This function is useful for unit tests which verify that the received
    /// packet is parsed correctly. In those cases it is usually inappropriate
    /// to create an instance of the packet, add options, set packet
    /// fields and use such packet as an input to processDiscover or
    /// processRequest function. This is because, such a packet has certain
    /// options already initialized and there is no way to verify that they
    /// have been initialized when packet instance was created or wire buffer
    /// processing. By creating a packet from the buffer we guarantee that the
    /// new packet is entirely initialized during wire data parsing.
    ///
    /// @param src_pkt A source packet, to be copied.
    /// @param [out] dst_pkt A destination packet.
    ///
    /// @return assertion result indicating if a function completed with
    /// success or failure.
    static ::testing::AssertionResult
    createPacketFromBuffer(const isc::dhcp::Pkt4Ptr& src_pkt,
                           isc::dhcp::Pkt4Ptr& dst_pkt);

    /// @brief Tests if Discover or Request message is processed correctly
    ///
    /// This test verifies that the Parameter Request List option is handled
    /// correctly, i.e. it checks that certain options are present in the
    /// server's response when they are requested and that they are not present
    /// when they are not requested or NAK occurs.
    ///
    /// @todo We need an additional test for PRL option using real traffic
    /// capture.
    ///
    /// @param msg_type DHCPDISCOVER or DHCPREQUEST
    void testDiscoverRequest(const uint8_t msg_type);

    /// @brief Create test which verifies server identifier.
    ///
    /// @param expected_server_id expected server identifier
    /// @param query the query used to get associated client classes
    /// @param requested the requested address
    /// @param server_id server identifier
    void buildCfgOptionTest(isc::asiolink::IOAddress expected_server_id,
                            Pkt4Ptr& query,
                            isc::asiolink::IOAddress requested,
                            isc::asiolink::IOAddress server_id);

    /// @brief Runs DHCPv4 configuration from the JSON string.
    ///
    /// @param config String holding server configuration in JSON format.
    /// @param commit A boolean flag indicating if the new configuration
    /// should be committed (if true), or not (if false).
    /// @param open_sockets A boolean flag indicating if sockets should
    /// be opened (if true), or not (if false).
    /// @param create_managers A boolean flag indicating if managers should be
    /// recreated.
    /// @param test A boolean flag which indicates if only testing config.
    void configure(const std::string& config,
                   const bool commit = true,
                   const bool open_sockets = true,
                   const bool create_managers = true,
                   const bool test = false);

    /// @brief Configure specified DHCP server using JSON string.
    ///
    /// @param config String holding server configuration in JSON format.
    /// @param srv Instance of the server to be configured.
    /// @param commit A boolean flag indicating if the new configuration
    /// should be committed (if true), or not (if false).
    /// @param open_sockets A boolean flag indicating if sockets should
    /// be opened (if true), or not (if false).
    /// @param create_managers A boolean flag indicating if managers should be
    /// recreated.
    /// @param test A boolean flag which indicates if only testing config.
    void configure(const std::string& config,
                   NakedDhcpv4Srv& srv,
                   const bool commit = true,
                   const bool open_sockets = true,
                   const bool create_managers = true,
                   const bool test = false);

    /// @brief Configure specified DHCP server using JSON string.
    ///
    /// @param config String holding server configuration in JSON format.
    /// @param srv Instance of the server to be configured.
    /// @param commit A boolean flag indicating if the new configuration
    /// should be committed (if true), or not (if false).
    /// @param exp_rcode expected status code (default = 0 (success))
    /// @return (a pair of status code and a string with result)
    std::pair<int, std::string>
    configureWithStatus(const std::string& config, NakedDhcpv4Srv& srv,
                        const bool commit = true, const int exp_rcode = 0);

    /// @brief Pretends a packet of specified type was received.
    ///
    /// Instantiates fake network interfaces, configures passed Dhcpv4Srv,
    /// then creates a message of specified type and sends it to the
    /// server and then checks whether expected statistics were set
    /// appropriately.
    ///
    /// @param srv the DHCPv4 server to be used
    /// @param config JSON configuration to be used
    /// @param pkt_type type of the packet to be faked
    /// @param stat_name name of the expected statistic
    void pretendReceivingPkt(NakedDhcpv4Srv& srv, const std::string& config,
                             uint8_t pkt_type, const std::string& stat_name);

    /// @brief Create @c Dhcpv4Exchange from client's query.
    Dhcpv4Exchange createExchange(const Pkt4Ptr& query);

    /// @brief Performs 4-way exchange to obtain new lease.
    ///
    /// This is used as a preparatory step for Decline operation.
    ///
    /// @param client Client to be used to obtain a lease.
    void acquireLease(Dhcp4Client& client);

    /// @brief Tests if the acquired lease is or is not declined.
    ///
    /// @param client Dhcp4Client instance
    /// @param hw_address_1 HW Address to be used to acquire the lease.
    /// @param client_id_1 Client id to be used to acquire the lease.
    /// @param hw_address_2 HW Address to be used to decline the lease.
    /// @param client_id_2 Client id to be used to decline the lease.
    /// @param expected_result SHOULD_PASS if the lease is expected to
    /// be successfully declined, or SHOULD_FAIL if the lease is expected
    /// to not be declined.
    void acquireAndDecline(Dhcp4Client& client,
                           const std::string& hw_address_1,
                           const std::string& client_id_1,
                           const std::string& hw_address_2,
                           const std::string& client_id_2,
                           ExpectedResult expected_result);

    /// @brief Checks if received relay agent info option is echoed back to the
    /// client.
    void relayAgentInfoEcho();

    /// @brief Checks if received bad relay agent info option is not echoed back
    /// to the client.
    void badRelayAgentInfoEcho();

    /// @brief Checks if client port can be overridden in packets being sent.
    void portsClientPort();

    /// @brief Checks if server port can be overridden in packets being sent.
    void portsServerPort();

    /// @brief Check if example files contain valid configuration.
    void checkConfigFiles();

    /// @brief Check if the server configuration stored in file is valid.
    ///
    /// @param path The path to the configuration file.
    void loadConfigFile(const std::string& path);

    /// @brief This function cleans up after the test.
    virtual void TearDown();

    /// @brief Set multi-threading mode.
    void setMultiThreading(bool enabled) {
        multi_threading_ = enabled;
    }

    /// @brief A subnet used in most tests.
    Subnet4Ptr subnet_;

    /// @brief A pool used in most tests.
    Pool4Ptr pool_;

    /// @brief A client-id used in most tests.
    ClientIdPtr client_id_;

    /// @brief Return code
    int rcode_;

    /// @brief Comment received from configuration.
    isc::data::ConstElementPtr comment_;

    /// @brief Server object under test.
    NakedDhcpv4Srv srv_;

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
    isc::dhcp::Parser4Context ctx;
    return (ctx.parseString(in, isc::dhcp::Parser4Context::PARSER_JSON));
}

/// @brief Runs parser in Dhcp4 mode
///
/// This is a simplified Dhcp4 mode, so no outer { } and "Dhcp4" is
/// needed. This format is used by most of the tests.
///
/// @param in string to be parsed
/// @param verbose display the exception message when it fails
/// @return ElementPtr structure representing parsed JSON
inline isc::data::ElementPtr
parseDHCP4(const std::string& in, bool verbose = false) {
    try {
        isc::dhcp::Parser4Context ctx;
        isc::data::ElementPtr json;
        json = ctx.parseString(in, isc::dhcp::Parser4Context::SUBPARSER_DHCP4);
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
        isc::dhcp::Parser4Context ctx;
        return (ctx.parseString(in, isc::dhcp::Parser4Context::PARSER_OPTION_DEFS));
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

#endif // DHCP4_TEST_UTILS_H
