// Copyright (C) 2018-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ha_test.h>
#include <ha_impl.h>
#include <asiolink/io_address.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/network_state.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/subnet.h>
#include <hooks/hooks_manager.h>
#include <stats/stats_mgr.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>

#include <boost/pointer_cast.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::ha;
using namespace isc::ha::test;
using namespace isc::hooks;
using namespace isc::stats;
using namespace isc::test;

namespace {

/// @brief Structure that holds registered hook indexes.
///
/// This allows us to park packets.
struct TestHooks {
    /// @brief Index of leases4_committed callout.
    int hook_index_leases4_committed_;

    /// @brief Index of leases6_committed callout.
    int hook_index_leases6_committed_;

    /// @brief Index of lease4_server_decline callout.
    int hook_index_lease4_server_decline_;

    /// @brief Constructor
    ///
    /// The constructor registers hook points for callout tests.
    TestHooks() {
        hook_index_leases4_committed_ =
            HooksManager::registerHook("leases4_committed");
        hook_index_leases6_committed_ =
            HooksManager::registerHook("leases6_committed");
        hook_index_lease4_server_decline_ =
            HooksManager::registerHook("lease4_server_decline");
    }
};

TestHooks test_hooks;

/// @brief Derivation of the @c HAImpl which provides access to protected
/// methods and members.
class TestHAImpl : public HAImpl {
public:

    using HAImpl::config_;
    using HAImpl::services_;

    /// @brief Constructor.
    TestHAImpl() :
        HAImpl(), should_reclaim_dhcpv4_lease_(true),
        should_reclaim_dhcpv6_lease_(true) { }

    /// @brief Mock function checking if the lease should be reclaimed by this server.
    ///
    /// @return true if the DHCPv4 lease should be reclaimed by this server instance,
    /// false otherwise.
    virtual bool shouldReclaim(const HAServicePtr& /*service*/, const Lease4Ptr& /*lease4*/) const {
        return (should_reclaim_dhcpv4_lease_);
    }

    /// @brief Mock function checking if the lease should be reclaimed by this server.
    ///
    /// @return true if the DHCPv6 lease should be reclaimed by this server instance,
    /// false otherwise.
    virtual bool shouldReclaim(const HAServicePtr& /*service*/, const Lease6Ptr& /*lease6*/) const {
        return (should_reclaim_dhcpv6_lease_);
    }

    /// @brief Custom value to be returned by the @c TestHAImpl::shouldReclaim function.
    bool should_reclaim_dhcpv4_lease_;

    /// @brief Custom value to be returned by the @c TestHAImpl::shouldReclaim function.
    bool should_reclaim_dhcpv6_lease_;
};

/// @brief Test fixture class for @c HAImpl.
class HAImplTest : public HATest {
public:
    /// @brief Constructor.
    HAImplTest() {
        // Clear statistics.
        StatsMgr::instance().removeAll();
        // Clear configuration.
        CfgMgr::instance().clear();
    }

    /// @brief Destructor.
    ~HAImplTest() {
        io_service_->stopAndPoll();
        ha_impl_.reset();
        test_ha_impl_.reset();
        io_service_->stopAndPoll();
        // Clear statistics.
        StatsMgr::instance().removeAll();
        // Clear configuration.
        CfgMgr::instance().clear();
    }

    /// @brief Fetches the current value of the given statistic.
    ///
    /// @param name name of the desired statistic.
    /// @return Current value of the statistic, or zero if the
    /// statistic is not found.
    uint64_t getStatistic(const std::string& name) {
        ObservationPtr stat = StatsMgr::instance().getObservation(name);
        if (!stat) {
            return (0);
        }

        return (stat->getInteger().first);
    }

    /// @brief Tests handler of a ha-sync command.
    ///
    /// It always expects that the error result is returned. The expected
    /// error text should be provided as function argument.
    ///
    /// @param ha_sync_command command provided as text.
    /// @param expected_response expected text response.
    void testSynchronizeHandler(const std::string& ha_sync_command,
                                const std::string& expected_response) {
        io_service_.reset(new IOService());
        ha_impl_.reset(new HAImpl());
        ha_impl_->setIOService(io_service_);
        ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

        // Starting the service is required prior to running any callouts.
        NetworkStatePtr network_state(new NetworkState());
        ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                                HAServerType::DHCPv4));

        ConstElementPtr command = Element::fromJSON(ha_sync_command);

        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("command", command);

        ASSERT_NO_THROW(ha_impl_->synchronizeHandler(*callout_handle));

        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);

        checkAnswer(response, CONTROL_RESULT_ERROR, expected_response);
        callout_handle.reset();

        io_service_->stopAndPoll();
        ha_impl_.reset();
        io_service_->stopAndPoll();
    }

    /// @brief HA Instance under test.
    boost::shared_ptr<TestHAImpl> test_ha_impl_;

    /// @brief HA Instance under test.
    boost::shared_ptr<HAImpl> ha_impl_;
};

// Tests that HAService object is created for DHCPv4 service.
TEST_F(HAImplTest, startServices) {
    // Valid configuration must be provided prior to starting the service.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(createValidJsonConfiguration()));

    // Network state is also required.
    NetworkStatePtr network_state(new NetworkState());

    // Start the service for DHCPv4 server.
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // Make sure that the HA service has been created for the requested
    // server type.
    ASSERT_TRUE(test_ha_impl_->services_);
    EXPECT_EQ(HAServerType::DHCPv4, test_ha_impl_->services_->get()->getServerType());
}

// Tests that HAService object is created for DHCPv6 service.
TEST_F(HAImplTest, startServices6) {
    // Valid configuration must be provided prior to starting the service.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(createValidJsonConfiguration()));

    // Network state is also required.
    NetworkStatePtr network_state(new NetworkState());

    // Start the service for DHCPv4 server.
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    // Make sure that the HA service has been created for the requested
    // server type.
    ASSERT_TRUE(test_ha_impl_->services_);
    EXPECT_EQ(HAServerType::DHCPv6, test_ha_impl_->services_->get()->getServerType());
}

// Tests for buffer4_receive callout implementation.
TEST_F(HAImplTest, buffer4Receive) {
    // Use hot-standby mode to make sure that this server instance is selected
    // to process each received query. This is going to give predictable results.
    ConstElementPtr ha_config = createValidJsonConfiguration(HAConfig::HOT_STANDBY);

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // Initially the HA service is in the waiting state and serves no scopes.
    // We need to explicitly enable the scope to be served.
    test_ha_impl_->services_->get()->serveDefaultScopes();

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);

    // Create the BOOTP message. We can use it for testing message parsing
    // failure case because BOOTP is not supported. We will later turn it
    // into the DHCP message to test successful parsing.
    std::vector<uint8_t> msg = {
        1, // BOOTREQUEST
        1, // ethernet
        6, // HW address length = 6
        0, // hops = 0
        1, 2, 3, 4, // xid
        0, 0, // secs = 0
        0, 0, // flags
        0, 0, 0, 0, // ciaddr = 0
        0, 0, 0, 0, // yiaddr = 0
        0, 0, 0, 0, // siaddr = 0
        0, 0, 0, 0, // giaddr = 0
        1, 2, 3, 4, 5, 6, // chaddr
    };

    // fill chaddr reminder, sname and file with zeros
    msg.insert(msg.end(), 10 + 128 + 64, 0);

    // Create DHCPv4 message object from the BOOTP message. This should be
    // successful because the message is not parsed yet.
    Pkt4Ptr query4(new Pkt4(&msg[0], msg.size()));

    // Set buffer4_receive callout arguments.
    callout_handle->setArgument("query4", query4);

    // Invoke the buffer4_receive callout.
    ASSERT_NO_THROW(test_ha_impl_->buffer4Receive(*callout_handle));

    // The BOOTP messages are not supported so trying to unpack the message
    // should trigger an error. The callout should set the next step to
    // DROP treating the message as malformed.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());
    // Malformed message should not be classified.
    EXPECT_TRUE(query4->getClasses().empty());

    // Drop statistics should have been increased.
    EXPECT_EQ(1, getStatistic("pkt4-receive-drop"));

    // Turn this into the DHCP message by appending a magic cookie and the
    // options.
    std::vector<uint8_t> magic_cookie = {
        99, 130, 83, 99
    };

    // Provide DHCP message type option, truncated vendor option and domain name.
    // Parsing this message should be successful but vendor option should be
    // skipped.
    std::vector<uint8_t> options = {
        53, 1, 1, // Message type = DHCPDISCOVER
        125, 6, // vendor options
            1, 2, 3, 4, // enterprise id
            8, 1, // data len 8 but the actual length is 1 (truncated options)
        15, 3, 'a', 'b', 'c' // Domain name = abc
    };

    // Append the magic cookie and the options to our BOOTP message.
    msg.insert(msg.end(), magic_cookie.begin(), magic_cookie.end());
    msg.insert(msg.end(), options.begin(), options.end());

    // Create new query and pass it to the callout.
    query4.reset(new Pkt4(&msg[0], msg.size()));
    callout_handle->setArgument("query4", query4);

    // Invoke the callout again.
    ASSERT_NO_THROW(test_ha_impl_->buffer4Receive(*callout_handle));

    // This time the callout should set the next step to SKIP to indicate to
    // the DHCP server that the message has been already parsed.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, callout_handle->getStatus());

    // The client class should be assigned to the message to indicate that the
    // server1 should process this message.
    ASSERT_EQ(1, query4->getClasses().size());
    EXPECT_TRUE(query4->inClass("HA_server1"));

    // Check that the message has been parsed. The DHCP message type should
    // be set in this case.
    EXPECT_EQ(DHCPDISCOVER, static_cast<int>(query4->getType()));
    // Vendor option should be skipped because it was truncated.
    EXPECT_FALSE(query4->getOption(DHO_VIVSO_SUBOPTIONS));
    // Domain name should not be skipped because the vendor option was truncated.
    EXPECT_TRUE(query4->getOption(DHO_DOMAIN_NAME));

    // Drop statistics should have been increased.
    EXPECT_EQ(1, getStatistic("pkt4-parse-failed"));
    EXPECT_EQ(1, getStatistic("pkt4-receive-drop"));
}

// Tests subnet4_select callout implementation when the server name
// is specified at the subnet level.
TEST_F(HAImplTest, subnet4Select) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // The hub is a standby server and by default serves no scopes. Explicitly
    // enable the failover scopes to make this server responsible for the
    // received packets.
    test_ha_impl_->services_->get("server2")->serveFailoverScopes();
    test_ha_impl_->services_->get("server4")->serveFailoverScopes();

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the query.
    Pkt4Ptr query4(new Pkt4(DHCPDISCOVER, 1234));
    callout_handle->setArgument("query4", query4);

    // Create the subnet and include the server name in the context.
    auto context = Element::createMap();
    context->set("ha-server-name", Element::create("server3"));
    auto s = Subnet4::create(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1);
    s->setContext(context);
    ConstSubnet4Ptr subnet4 = s;
    callout_handle->setArgument("subnet4", subnet4);

    // Invoke the subnet4_select callout.
    ASSERT_NO_THROW(test_ha_impl_->subnet4Select(*callout_handle));

    // Make sure that the request was not dropped.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // The ha-server-name should be propagated to the leases4_committed callout.
    std::string ha_server_name;
    callout_handle->getContext("ha-server-name", ha_server_name);
    EXPECT_EQ("server3", ha_server_name);

    // The client class should be assigned to the query indicating the relationship
    // to which the query belongs.
    ASSERT_EQ(1, query4->getClasses().size());
    EXPECT_TRUE(query4->inClass("HA_server3"));

    // Drop statistics should not increase.
    EXPECT_EQ(0, getStatistic("pkt4-not-for-use"));
    EXPECT_EQ(0, getStatistic("pkt4-receive-drop"));
}

// Tests subnet4_select callout implementation when the server name
// is specified at the shared network level.
TEST_F(HAImplTest, subnet4SelectSharedNetwork) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // The hub is a standby server and by default serves no scopes. Explicitly
    // enable the failover scopes to make this server responsible for the
    // received packets.
    test_ha_impl_->services_->get("server2")->serveFailoverScopes();
    test_ha_impl_->services_->get("server4")->serveFailoverScopes();

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the query.
    Pkt4Ptr query4(new Pkt4(DHCPDISCOVER, 1234));
    callout_handle->setArgument("query4", query4);

    // Create the subnet and the shared network. Specify the server name at
    // the shared network level.
    auto context = Element::createMap();
    context->set("ha-server-name", Element::create("server3"));
    auto s = Subnet4::create(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1);
    auto shared_network4 = SharedNetwork4::create("foo");
    shared_network4->setContext(context);
    shared_network4->add(s);
    ConstSubnet4Ptr subnet4 = s;
    callout_handle->setArgument("subnet4", subnet4);

    // Invoke the subnet4_select callout.
    ASSERT_NO_THROW(test_ha_impl_->subnet4Select(*callout_handle));

    // Make sure that the request was not dropped.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // The ha-server-name should be propagated to the leases4_committed callout.
    std::string ha_server_name;
    callout_handle->getContext("ha-server-name", ha_server_name);
    EXPECT_EQ("server3", ha_server_name);

    // The client class should be assigned to the query indicating the relationship
    // to which the query belongs.
    ASSERT_EQ(1, query4->getClasses().size());
    EXPECT_TRUE(query4->inClass("HA_server3"));

    // Drop statistics should not increase.
    EXPECT_EQ(0, getStatistic("pkt4-not-for-us"));
    EXPECT_EQ(0, getStatistic("pkt4-receive-drop"));
}

// Tests that subnet4_select callout returns when there is a single relationship.
TEST_F(HAImplTest, subnet4SelectSingleRelationship) {
    // Create a non-hub configuration including only one relationship.
    ConstElementPtr ha_config = createValidJsonConfiguration(HAConfig::HOT_STANDBY);

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the query.
    Pkt4Ptr query4(new Pkt4(DHCPDISCOVER, 1234));
    callout_handle->setArgument("query4", query4);

    // Create the subnet. Don't bother specifying server name. The callout should
    // return immediately regardless.
    ConstSubnet4Ptr subnet4 =
        Subnet4::create(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1);
    callout_handle->setArgument("subnet4", subnet4);

    // Invoke the subnet4_select callout.
    ASSERT_NO_THROW(test_ha_impl_->subnet4Select(*callout_handle));

    // The request should not be dropped and there should be no classes assigned
    // because the callout didn't call the HAService::inScope function.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
    EXPECT_TRUE(query4->getClasses().empty());

    // Drop statistics should not increase.
    EXPECT_EQ(0, getStatistic("pkt4-not-for-us"));
    EXPECT_EQ(0, getStatistic("pkt4-receive-drop"));
}

// Tests that the subnet4_select drops the packet when server name is not
// specified for a subnet.
TEST_F(HAImplTest, subnet4SelectDropNoServerName) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // The hub is a standby server and by default serves no scopes. Explicitly
    // enable the failover scopes to make this server responsible for the
    // received packets.
    test_ha_impl_->services_->get("server2")->serveFailoverScopes();
    test_ha_impl_->services_->get("server4")->serveFailoverScopes();

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the query.
    Pkt4Ptr query4(new Pkt4(DHCPDISCOVER, 1234));
    callout_handle->setArgument("query4", query4);

    // Create the subnet without a server name setting.
    ConstSubnet4Ptr subnet4 =
        Subnet4::create(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1);
    callout_handle->setArgument("subnet4", subnet4);

    // Invoke the subnet4_select callout.
    ASSERT_NO_THROW(test_ha_impl_->subnet4Select(*callout_handle));

    // The request should be dropped and no classes assigned to it.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());
    EXPECT_TRUE(query4->getClasses().empty());

    // Drop statistics should have been increased.
    EXPECT_EQ(1, getStatistic("pkt4-not-for-us"));
    EXPECT_EQ(1, getStatistic("pkt4-receive-drop"));
}

// Tests that the subnet4_select drops the packet when server name has
// an invalid data type.
TEST_F(HAImplTest, subnet4SelectDropInvalidServerNameType) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // The hub is a standby server and by default serves no scopes. Explicitly
    // enable the failover scopes to make this server responsible for the
    // received packets.
    test_ha_impl_->services_->get("server2")->serveFailoverScopes();
    test_ha_impl_->services_->get("server4")->serveFailoverScopes();

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the query.
    Pkt4Ptr query4(new Pkt4(DHCPDISCOVER, 1234));
    callout_handle->setArgument("query4", query4);

    // Create the subnet with an integer server name. The server name must
    // be a string, though.
    auto context = Element::createMap();
    context->set("ha-server-name", Element::create(25));
    auto s = Subnet4::create(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1);
    s->setContext(context);
    ConstSubnet4Ptr subnet4 = s;
    callout_handle->setArgument("subnet4", subnet4);

    // Invoke the subnet4_select callout.
    ASSERT_NO_THROW(test_ha_impl_->subnet4Select(*callout_handle));

    // The request should be dropped and no classes assigned to it.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());
    EXPECT_TRUE(query4->getClasses().empty());

    // Drop statistics should have been increased.
    EXPECT_EQ(0, getStatistic("pkt4-not-for-us"));
    EXPECT_EQ(1, getStatistic("pkt4-processing-failed"));
    EXPECT_EQ(1, getStatistic("pkt4-receive-drop"));
}

// Tests that the subnet4_select drops the packet when server name is valid
// but the server serves no scope in the selected relationship.
TEST_F(HAImplTest, subnet4SelectDropNotInScope) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // This server serves server1/server2 scopes but not server3/server4 scopes.
    // The request should be dropped because the subnet will be associated with
    // the server3.
    test_ha_impl_->services_->get("server2")->serveFailoverScopes();

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the query.
    Pkt4Ptr query4(new Pkt4(DHCPDISCOVER, 1234));
    callout_handle->setArgument("query4", query4);

    // Create the subnet with the server name pointing to the server3/server4
    // relationship.
    auto context = Element::createMap();
    context->set("ha-server-name", Element::create("server3"));
    auto s = Subnet4::create(IOAddress("192.0.2.0"), 24, 30, 40, 50, 1);
    s->setContext(context);
    ConstSubnet4Ptr subnet4 = s;
    callout_handle->setArgument("subnet4", subnet4);

    // Invoke the subnet4_select callout.
    ASSERT_NO_THROW(test_ha_impl_->subnet4Select(*callout_handle));

    // The request should be dropped because the server is not responsible for
    // this scope currently.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());

    // However, the class should be assigned after calling HAService::inScope.
    ASSERT_EQ(1, query4->getClasses().size());
    EXPECT_TRUE(query4->inClass("HA_server3"));

    // Drop statistics should have been increased.
    EXPECT_EQ(1, getStatistic("pkt4-not-for-us"));
    EXPECT_EQ(1, getStatistic("pkt4-receive-drop"));
}

// Tests that the subnet4_select drops a packet when no subnet has been selected.
TEST_F(HAImplTest, subnet4SelectNoSubnet) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    test_ha_impl_->services_->get("server2")->serveFailoverScopes();
    test_ha_impl_->services_->get("server4")->serveFailoverScopes();

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the query.
    Pkt4Ptr query4(new Pkt4(DHCPDISCOVER, 1234));
    callout_handle->setArgument("query4", query4);

    // Create null subnet.
    ConstSubnet4Ptr subnet4;
    callout_handle->setArgument("subnet4", subnet4);

    // Invoke the subnet4_select callout.
    ASSERT_NO_THROW(test_ha_impl_->subnet4Select(*callout_handle));

    // No subnet has been selected and we have multiple relationships. We
    // expect that the server drops the packet.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());

    // No HA-specific classes should be assigned.
    EXPECT_TRUE(query4->getClasses().empty());

    // Drop statistics should have been increased.
    EXPECT_EQ(1, getStatistic("pkt4-not-for-us"));
    EXPECT_EQ(1, getStatistic("pkt4-receive-drop"));
}

// Tests for buffer6_receive callout implementation.
TEST_F(HAImplTest, buffer6Receive) {
    // Use hot-standby mode to make sure that this server instance is selected
    // to process each received query. This is going to give predictable results.
    ConstElementPtr ha_config = createValidJsonConfiguration(HAConfig::HOT_STANDBY);

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    // Initially the HA service is in the waiting state and serves no scopes.
    // We need to explicitly enable the scope to be served.
    test_ha_impl_->services_->get()->serveDefaultScopes();

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);

    // Create DHCPv6 message. It initially has no transaction id so should be
    // considered malformed.
    std::vector<uint8_t> msg = {
        1, // Solicit
    };

    // Create DHCPv4 message object from the BOOTP message. This should be
    // successful because the message is not parsed yet.
    Pkt6Ptr query6(new Pkt6(&msg[0], msg.size()));

    // Set buffer6_receive callout arguments.
    callout_handle->setArgument("query6", query6);

    // Invoke the buffer6_receive callout.
    ASSERT_NO_THROW(test_ha_impl_->buffer6Receive(*callout_handle));

    // Our DHCP messages contains no transaction id so it should cause
    // parsing error. The next step is set to DROP for malformed messages.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());
    // Malformed message should not be classified.
    EXPECT_TRUE(query6->getClasses().empty());

    // Drop statistics should have been increased.
    EXPECT_EQ(1, getStatistic("pkt6-receive-drop"));

    // Append transaction id (3 bytes, each set to 1).
    msg.insert(msg.end(), 3, 1);

    // Include 3 options in the DHCPv6 message: ORO, truncated vendor option
    // and the NIS Domain Name option. This should be parsed correctly but the
    // last option should be skipped because of the preceding option being
    // truncated.
    std::vector<uint8_t> options = {
        0, 6, 0, 2, 0, 29, // option ORO requesting option 29
        0, 17, // vendor options
        0, 9, // option length = 10
            1, 2, 3, 4, // enterprise id
            0, 1, 0, 10, // code 1, (invalid) length = 10
            1, // ONLY 1 byte of data (truncated)
        0, 29, 0, 3, 'a', 'b', 'c' // NIS Domain Name = abc
    };

    msg.insert(msg.end(), options.begin(), options.end());

    // Create new query and pass it to the callout.
    query6.reset(new Pkt6(&msg[0], msg.size()));
    callout_handle->setArgument("query6", query6);

    // Invoke the callout again.
    ASSERT_NO_THROW(test_ha_impl_->buffer6Receive(*callout_handle));

    // This time the callout should set the next step to SKIP to indicate to
    // the DHCP server that the message has been already parsed.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, callout_handle->getStatus());

    // The client class should be assigned to the message to indicate that the
    // server1 should process this message.
    ASSERT_EQ(1, query6->getClasses().size());
    EXPECT_TRUE(query6->inClass("HA_server1"));

    // Check that the message has been parsed. The DHCP message type should
    // be set in this case.
    EXPECT_EQ(DHCPV6_SOLICIT, static_cast<int>(query6->getType()));
    // Domain name should be skipped because the vendor option was truncated.
    EXPECT_FALSE(query6->getOption(D6O_NIS_DOMAIN_NAME));

    // Drop statistics should have been increased.
    EXPECT_EQ(1, getStatistic("pkt6-parse-failed"));
    EXPECT_EQ(1, getStatistic("pkt6-receive-drop"));
}

// Tests subnet6_select callout implementation when the server name
// is specified at the subnet level.
TEST_F(HAImplTest, subnet6Select) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    // The hub is a standby server and by default serves no scopes. Explicitly
    // enable the failover scopes to make this server responsible for the
    // received packets.
    test_ha_impl_->services_->get("server2")->serveFailoverScopes();
    test_ha_impl_->services_->get("server4")->serveFailoverScopes();

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the query.
    Pkt6Ptr query6(new Pkt6(DHCPV6_SOLICIT, 1234));
    callout_handle->setArgument("query6", query6);

    // Create the subnet and include the server name in the context.
    auto context = Element::createMap();
    context->set("ha-server-name", Element::create("server3"));
    auto s = Subnet6::create(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1);
    s->setContext(context);
    ConstSubnet6Ptr subnet6 = s;
    callout_handle->setArgument("subnet6", subnet6);

    // Invoke the subnet6_select callout.
    ASSERT_NO_THROW(test_ha_impl_->subnet6Select(*callout_handle));

    // Make sure that the request was not dropped.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // The ha-server-name should be propagated to the leases4_committed callout.
    std::string ha_server_name;
    callout_handle->getContext("ha-server-name", ha_server_name);
    EXPECT_EQ("server3", ha_server_name);

    // The client class should be assigned to the query indicating the relationship
    // to which the query belongs.
    ASSERT_EQ(1, query6->getClasses().size());
    EXPECT_TRUE(query6->inClass("HA_server3"));

    // Drop statistics should not increase.
    EXPECT_EQ(0, getStatistic("pkt6-not-for-use"));
    EXPECT_EQ(0, getStatistic("pkt6-receive-drop"));
}

// Tests subnet6_select callout implementation when the server name
// is specified at the shared network level.
TEST_F(HAImplTest, subnet6SelectSharedNetwork) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    // The hub is a standby server and by default serves no scopes. Explicitly
    // enable the failover scopes to make this server responsible for the
    // received packets.
    test_ha_impl_->services_->get("server2")->serveFailoverScopes();
    test_ha_impl_->services_->get("server4")->serveFailoverScopes();

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the query.
    Pkt6Ptr query6(new Pkt6(DHCPV6_SOLICIT, 1234));
    callout_handle->setArgument("query6", query6);

    // Create the subnet and the shared network. Specify the server name at
    // the shared network level.
    auto context = Element::createMap();
    context->set("ha-server-name", Element::create("server3"));
    auto s = Subnet6::create(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1);
    auto shared_network6 = SharedNetwork6::create("foo");
    shared_network6->setContext(context);
    shared_network6->add(s);
    ConstSubnet6Ptr subnet6 = s;
    callout_handle->setArgument("subnet6", subnet6);

    // Invoke the subnet6_select callout.
    ASSERT_NO_THROW(test_ha_impl_->subnet6Select(*callout_handle));

    // Make sure that the request was not dropped.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // The ha-server-name should be propagated to the leases4_committed callout.
    std::string ha_server_name;
    callout_handle->getContext("ha-server-name", ha_server_name);
    EXPECT_EQ("server3", ha_server_name);

    // The client class should be assigned to the query indicating the relationship
    // to which the query belongs.
    ASSERT_EQ(1, query6->getClasses().size());
    EXPECT_TRUE(query6->inClass("HA_server3"));

    // Drop statistics should not increase.
    EXPECT_EQ(0, getStatistic("pkt6-not-for-us"));
    EXPECT_EQ(0, getStatistic("pkt6-receive-drop"));
}

// Tests that subnet6_select callout returns when there is a single relationship.
TEST_F(HAImplTest, subnet6SelectSingleRelationship) {
    // Create a non-hub configuration including only one relationship.
    ConstElementPtr ha_config = createValidJsonConfiguration(HAConfig::HOT_STANDBY);

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the query.
    Pkt6Ptr query6(new Pkt6(DHCPV6_SOLICIT, 1234));
    callout_handle->setArgument("query6", query6);

    // Create the subnet. Don't bother specifying server name. The callout should
    // return immediately regardless.
    ConstSubnet6Ptr subnet6 =
        Subnet6::create(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1);
    callout_handle->setArgument("subnet6", subnet6);

    // Invoke the subnet6_select callout.
    ASSERT_NO_THROW(test_ha_impl_->subnet6Select(*callout_handle));

    // The request should not be dropped and there should be no classes assigned
    // because the callout didn't call the HAService::inScope function.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
    EXPECT_TRUE(query6->getClasses().empty());

    // Drop statistics should not increase.
    EXPECT_EQ(0, getStatistic("pkt6-not-for-us"));
    EXPECT_EQ(0, getStatistic("pkt6-receive-drop"));
}

// Tests that the subnet6_select drops the packet when server name is not
// specified for a subnet.
TEST_F(HAImplTest, subnet6SelectDropNoServerName) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    // The hub is a standby server and by default serves no scopes. Explicitly
    // enable the failover scopes to make this server responsible for the
    // received packets.
    test_ha_impl_->services_->get("server2")->serveFailoverScopes();
    test_ha_impl_->services_->get("server4")->serveFailoverScopes();

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the query.
    Pkt6Ptr query6(new Pkt6(DHCPV6_SOLICIT, 1234));
    callout_handle->setArgument("query6", query6);

    // Create the subnet without a server name setting.
    ConstSubnet6Ptr subnet6 =
        Subnet6::create(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1);
    callout_handle->setArgument("subnet6", subnet6);

    // Invoke the subnet6_select callout.
    ASSERT_NO_THROW(test_ha_impl_->subnet6Select(*callout_handle));

    // The request should be dropped and no classes assigned to it.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());
    EXPECT_TRUE(query6->getClasses().empty());

    // Drop statistics should have been increased.
    EXPECT_EQ(1, getStatistic("pkt6-not-for-us"));
    EXPECT_EQ(1, getStatistic("pkt6-receive-drop"));
}

// Tests that the subnet6_select drops the packet when server name has
// an invalid data type.
TEST_F(HAImplTest, subnet6SelectDropInvalidServerNameType) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    // The hub is a standby server and by default serves no scopes. Explicitly
    // enable the failover scopes to make this server responsible for the
    // received packets.
    test_ha_impl_->services_->get("server2")->serveFailoverScopes();
    test_ha_impl_->services_->get("server4")->serveFailoverScopes();

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the query.
    Pkt6Ptr query6(new Pkt6(DHCPV6_SOLICIT, 1234));
    callout_handle->setArgument("query6", query6);

    // Create the subnet with an integer server name. The server name must
    // be a string, though.
    auto context = Element::createMap();
    context->set("ha-server-name", Element::create(25));
    auto s = Subnet6::create(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1);
    s->setContext(context);
    ConstSubnet6Ptr subnet6 = s;
    callout_handle->setArgument("subnet6", subnet6);

    // Invoke the subnet6_select callout.
    ASSERT_NO_THROW(test_ha_impl_->subnet6Select(*callout_handle));

    // The request should be dropped and no classes assigned to it.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());
    EXPECT_TRUE(query6->getClasses().empty());

    // Drop statistics should have been increased.
    EXPECT_EQ(0, getStatistic("pkt6-not-for-us"));
    EXPECT_EQ(1, getStatistic("pkt6-processing-failed"));
    EXPECT_EQ(1, getStatistic("pkt6-receive-drop"));
}

// Tests that the subnet6_select drops the packet when server name is valid
// but the server serves no scope in the selected relationship.
TEST_F(HAImplTest, subnet6SelectDropNotInScope) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    // This server serves server1/server2 scopes but not server3/server4 scopes.
    // The request should be dropped because the subnet will be associated with
    // the server3.
    test_ha_impl_->services_->get("server2")->serveFailoverScopes();

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the query.
    Pkt6Ptr query6(new Pkt6(DHCPV6_SOLICIT, 1234));
    callout_handle->setArgument("query6", query6);

    // Create the subnet with the server name pointing to the server3/server4
    // relationship.
    auto context = Element::createMap();
    context->set("ha-server-name", Element::create("server3"));
    auto s = Subnet6::create(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 1);
    s->setContext(context);
    ConstSubnet6Ptr subnet6 = s;
    callout_handle->setArgument("subnet6", subnet6);

    // Invoke the subnet6_select callout.
    ASSERT_NO_THROW(test_ha_impl_->subnet6Select(*callout_handle));

    // The request should be dropped because the server is not responsible for
    // this scope currently.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());

    // However, the class should be assigned after calling HAService::inScope.
    ASSERT_EQ(1, query6->getClasses().size());
    EXPECT_TRUE(query6->inClass("HA_server3"));

    // Drop statistics should have been increased.
    EXPECT_EQ(1, getStatistic("pkt6-not-for-us"));
    EXPECT_EQ(1, getStatistic("pkt6-receive-drop"));
}

// Tests that the subnet6_select drops a packet when no subnet has been selected.
TEST_F(HAImplTest, subnet6SelectNoSubnet) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    test_ha_impl_->services_->get("server2")->serveFailoverScopes();
    test_ha_impl_->services_->get("server4")->serveFailoverScopes();

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the query.
    Pkt6Ptr query6(new Pkt6(DHCPV6_SOLICIT, 1234));
    callout_handle->setArgument("query6", query6);

    // Create null subnet.
    ConstSubnet6Ptr subnet6;
    callout_handle->setArgument("subnet6", subnet6);

    // Invoke the subnet6_select callout.
    ASSERT_NO_THROW(test_ha_impl_->subnet6Select(*callout_handle));

    // No subnet has been selected and we have multiple relationships. We
    // expect that the server drops the packet.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());

    // No HA-specific classes should be assigned.
    EXPECT_TRUE(query6->getClasses().empty());

    // Drop statistics should have been increased.
    EXPECT_EQ(1, getStatistic("pkt6-not-for-us"));
    EXPECT_EQ(1, getStatistic("pkt6-receive-drop"));
}

// Tests leases4_committed callout implementation.
TEST_F(HAImplTest, leases4Committed) {
    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // Make sure we wait for the acks from the backup server to be able to
    // test the case of sending lease updates even though the service is
    // in the state in which the lease updates are normally not sent.
    test_ha_impl_->config_->get()->setWaitBackupAck(true);

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);

    // Set the hook index so we can park packets.
    callout_handle->setCurrentHook(test_hooks.hook_index_leases4_committed_);

    // query4
    Pkt4Ptr query4 = createMessage4(DHCPREQUEST, 1, 0, 0);
    callout_handle->setArgument("query4", query4);

    // leases4
    Lease4CollectionPtr leases4(new Lease4Collection());
    callout_handle->setArgument("leases4", leases4);

    // deleted_leases4
    Lease4CollectionPtr deleted_leases4(new Lease4Collection());
    callout_handle->setArgument("deleted_leases4", deleted_leases4);

    // Set initial status.
    callout_handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);

    // Park the packet.
    HooksManager::park("leases4_committed", query4, []{});

    // There are no leases so the callout should return.
    ASSERT_NO_THROW(test_ha_impl_->leases4Committed(*callout_handle));

    // No updates are generated so the default status should not be modified.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query4));

    // Create a lease and pass it to the callout, but temporarily disable lease
    // updates.
    HWAddrPtr hwaddr(new HWAddr(std::vector<uint8_t>(6, 1), HTYPE_ETHER));
    Lease4Ptr lease4(new Lease4(IOAddress("192.1.2.3"), hwaddr,
                                static_cast<const uint8_t*>(0), 0,
                                60, 0, 1));
    leases4->push_back(lease4);
    callout_handle->setArgument("leases4", leases4);

    test_ha_impl_->config_->get()->setSendLeaseUpdates(false);

    // Park the packet.
    HooksManager::park("leases4_committed", query4, []{});

    // Run the callout again.
    ASSERT_NO_THROW(test_ha_impl_->leases4Committed(*callout_handle));

    // No updates are generated so the default status should not be modified.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query4));

    // Enable updates and retry.
    test_ha_impl_->config_->get()->setSendLeaseUpdates(true);
    callout_handle->setArgument("leases4", leases4);

    // Park the packet.
    HooksManager::park("leases4_committed", query4, []{});

    // Run the callout again.
    ASSERT_NO_THROW(test_ha_impl_->leases4Committed(*callout_handle));

    // This time the lease update should be generated and the status should
    // be set to "park".
    EXPECT_EQ(CalloutHandle::NEXT_STEP_PARK, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query4));

    // Drop statistics should not increase.
    EXPECT_EQ(0, getStatistic("pkt4-not-for-us"));
    EXPECT_EQ(0, getStatistic("pkt4-receive-drop"));
}

// Tests leases4_committed callout implementation for multiple relationships.
TEST_F(HAImplTest, leases4CommittedMultipleRelationships) {
    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(createValidHubJsonConfiguration()));

    // Starting the service is required before running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // By enabling this setting we ensure that the lease updates are always
    // scheduled and the packet is parked because it is independent of a
    // server state.
    test_ha_impl_->config_->get("server2")->setWaitBackupAck(true);

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);

    // Set the hook index so we can park the packets.
    callout_handle->setCurrentHook(test_hooks.hook_index_leases4_committed_);

    // The server name is required to select HA relationship.
    callout_handle->setContext("ha-server-name", std::string("server1"));

    // DHCP query.
    Pkt4Ptr query4 = createMessage4(DHCPREQUEST, 1, 0, 0);
    callout_handle->setArgument("query4", query4);

    // Leases.
    HWAddrPtr hwaddr(new HWAddr(std::vector<uint8_t>(6, 1), HTYPE_ETHER));
    Lease4Ptr lease4(new Lease4(IOAddress("192.1.2.3"), hwaddr,
                                static_cast<const uint8_t*>(0), 0,
                                60, 0, 1));
    Lease4CollectionPtr leases4(new Lease4Collection());
    leases4->push_back(lease4);
    callout_handle->setArgument("leases4", leases4);

    Lease4CollectionPtr deleted_leases4(new Lease4Collection());
    callout_handle->setArgument("deleted_leases4", deleted_leases4);

    // Park the packet.
    HooksManager::park("leases4_committed", query4, []{});

    // Run the callout.
    ASSERT_NO_THROW(test_ha_impl_->leases4Committed(*callout_handle));

    // Make sure the callout completed successfully. The "park" status means
    // there was no error during the callout.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_PARK, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query4));

    // Drop statistics should not increase.
    EXPECT_EQ(0, getStatistic("pkt4-not-for-us"));
    EXPECT_EQ(0, getStatistic("pkt4-receive-drop"));
}

// Tests leases4_committed callout implementation for multiple relationships when
// the relationship is not found.
TEST_F(HAImplTest, leases4CommittedMultipleRelationshipsNoServerName) {
    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(createValidHubJsonConfiguration()));

    // Starting the service is required before running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // By enabling this setting we ensure that the lease updates are always
    // scheduled and the packet is parked because it is independent of a
    // server state.
    test_ha_impl_->config_->get("server2")->setWaitBackupAck(true);

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);

    // Set the hook index so we can park the packets.
    callout_handle->setCurrentHook(test_hooks.hook_index_leases4_committed_);

    // DHCP query.
    Pkt4Ptr query4 = createMessage4(DHCPREQUEST, 1, 0, 0);
    callout_handle->setArgument("query4", query4);

    // Leases.
    HWAddrPtr hwaddr(new HWAddr(std::vector<uint8_t>(6, 1), HTYPE_ETHER));
    Lease4Ptr lease4(new Lease4(IOAddress("192.1.2.3"), hwaddr,
                                static_cast<const uint8_t*>(0), 0,
                                60, 0, 1));
    Lease4CollectionPtr leases4(new Lease4Collection());
    leases4->push_back(lease4);
    callout_handle->setArgument("leases4", leases4);

    Lease4CollectionPtr deleted_leases4(new Lease4Collection());
    callout_handle->setArgument("deleted_leases4", deleted_leases4);

    // Park the packet.
    HooksManager::park("leases4_committed", query4, []{});

    // Run the callout.
    ASSERT_NO_THROW(test_ha_impl_->leases4Committed(*callout_handle));

    // The relationship was not found so the packet should be dropped.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query4));

    // Drop statistics should have been increased.
    EXPECT_EQ(1, getStatistic("pkt4-not-for-us"));
    EXPECT_EQ(1, getStatistic("pkt4-receive-drop"));
}

// Tests leases4_committed callout implementation for multiple relationships when
// the relationship name is invalid.
TEST_F(HAImplTest, leases4CommittedMultipleRelationshipsInvalidServerName) {
    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(createValidHubJsonConfiguration()));

    // Starting the service is required before running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // By enabling this setting we ensure that the lease updates are always
    // scheduled and the packet is parked because it is independent of a
    // server state.
    test_ha_impl_->config_->get("server2")->setWaitBackupAck(true);

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);

    // Set the hook index so we can park the packets.
    callout_handle->setCurrentHook(test_hooks.hook_index_leases4_committed_);

    // Set invalid relationship name. It should cause the packet drop.
    callout_handle->setContext("ha-server-name", std::string("serverX"));

    // DHCP query.
    Pkt4Ptr query4 = createMessage4(DHCPREQUEST, 1, 0, 0);
    callout_handle->setArgument("query4", query4);

    // Leases.
    HWAddrPtr hwaddr(new HWAddr(std::vector<uint8_t>(6, 1), HTYPE_ETHER));
    Lease4Ptr lease4(new Lease4(IOAddress("192.1.2.3"), hwaddr,
                                static_cast<const uint8_t*>(0), 0,
                                60, 0, 1));
    Lease4CollectionPtr leases4(new Lease4Collection());
    leases4->push_back(lease4);
    callout_handle->setArgument("leases4", leases4);

    Lease4CollectionPtr deleted_leases4(new Lease4Collection());
    callout_handle->setArgument("deleted_leases4", deleted_leases4);

    // Park the packet.
    HooksManager::park("leases4_committed", query4, []{});

    // Run the callout.
    ASSERT_NO_THROW(test_ha_impl_->leases4Committed(*callout_handle));

    // The relationship was not found so the packet should be dropped.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query4));

    // Drop statistics should have been increased.
    EXPECT_EQ(1, getStatistic("pkt4-not-for-us"));
    EXPECT_EQ(1, getStatistic("pkt4-receive-drop"));
}

// Tests leases6_committed callout implementation.
TEST_F(HAImplTest, leases6Committed) {
    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    // Make sure we wait for the acks from the backup server to be able to
    // test the case of sending lease updates even though the service is
    // in the state in which the lease updates are normally not sent.
    test_ha_impl_->config_->get()->setWaitBackupAck(true);

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);

    // Set the hook index so we can park packets.
    callout_handle->setCurrentHook(test_hooks.hook_index_leases6_committed_);

    // query6
    Pkt6Ptr query6 = createMessage6(DHCPV6_REQUEST, 1, 0);
    callout_handle->setArgument("query6", query6);

    // leases6
    Lease6CollectionPtr leases6(new Lease6Collection());
    callout_handle->setArgument("leases6", leases6);

    // deleted_leases6
    Lease6CollectionPtr deleted_leases6(new Lease6Collection());
    callout_handle->setArgument("deleted_leases6", deleted_leases6);

    // Set initial status.
    callout_handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);

    // Park the packet.
    HooksManager::park("leases6_committed", query6, []{});

    // There are no leases so the callout should return.
    ASSERT_NO_THROW(test_ha_impl_->leases6Committed(*callout_handle));

    // No updates are generated so the default status should not be modified.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query6));

    // Create a lease and pass it to the callout, but temporarily disable lease
    // updates.
    DuidPtr duid(new DUID(std::vector<uint8_t>(8, 2)));
    Lease6Ptr lease6(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::cafe"), duid,
                                1234, 50, 60, 1));
    leases6->push_back(lease6);
    callout_handle->setArgument("leases6", leases6);

    test_ha_impl_->config_->get()->setSendLeaseUpdates(false);

    // Park the packet.
    HooksManager::park("leases6_committed", query6, []{});

    // Run the callout again.
    ASSERT_NO_THROW(test_ha_impl_->leases6Committed(*callout_handle));

    // No updates are generated so the default status should not be modified.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query6));

    // Enable updates and retry.
    test_ha_impl_->config_->get()->setSendLeaseUpdates(true);
    callout_handle->setArgument("leases6", leases6);

    // Park the packet.
    HooksManager::park("leases6_committed", query6, []{});

    // Run the callout again.
    ASSERT_NO_THROW(test_ha_impl_->leases6Committed(*callout_handle));

    // This time the lease update should be generated and the status should
    // be set to "park".
    EXPECT_EQ(CalloutHandle::NEXT_STEP_PARK, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query6));

    // Drop statistics should not increase.
    EXPECT_EQ(0, getStatistic("pkt6-not-for-us"));
    EXPECT_EQ(0, getStatistic("pkt6-receive-drop"));
}

// Tests leases6_committed callout implementation for multiple relationships.
TEST_F(HAImplTest, leases6CommittedMultipleRelationships) {
    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(createValidHubJsonConfiguration()));

    // Starting the service is required before running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    // By enabling this setting we ensure that the lease updates are always
    // scheduled and the packet is parked because it is independent of a
    // server state.
    test_ha_impl_->config_->get("server2")->setWaitBackupAck(true);

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);

    // Set the hook index so we can park the packets.
    callout_handle->setCurrentHook(test_hooks.hook_index_leases6_committed_);

    // The server name is required to select HA relationship.
    callout_handle->setContext("ha-server-name", std::string("server1"));

    // DHCP query.
    Pkt6Ptr query6 = createMessage6(DHCPV6_REQUEST, 1, 0);
    callout_handle->setArgument("query6", query6);

    // Leases.
    DuidPtr duid(new DUID(std::vector<uint8_t>(8, 2)));
    Lease6Ptr lease6(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::cafe"), duid,
                                1234, 50, 60, 1));
    Lease6CollectionPtr leases6(new Lease6Collection());
    leases6->push_back(lease6);
    callout_handle->setArgument("leases6", leases6);

    Lease6CollectionPtr deleted_leases6(new Lease6Collection());
    callout_handle->setArgument("deleted_leases6", deleted_leases6);

    // Park the packet.
    HooksManager::park("leases6_committed", query6, []{});

    // Run the callout.
    ASSERT_NO_THROW(test_ha_impl_->leases6Committed(*callout_handle));

    // Make sure the callout completed successfully. The "park" status means
    // there was no error during the callout.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_PARK, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query6));

    // Drop statistics should not increase.
    EXPECT_EQ(0, getStatistic("pkt6-not-for-us"));
    EXPECT_EQ(0, getStatistic("pkt6-receive-drop"));
}

// Tests leases6_committed callout implementation for multiple relationships when
// the relationship is not found.
TEST_F(HAImplTest, leases6CommittedMultipleRelationshipsNoServerName) {
    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(createValidHubJsonConfiguration()));

    // Starting the service is required before running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    // By enabling this setting we ensure that the lease updates are always
    // scheduled and the packet is parked because it is independent of a
    // server state.
    test_ha_impl_->config_->get("server2")->setWaitBackupAck(true);

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);

    // Set the hook index so we can park the packets.
    callout_handle->setCurrentHook(test_hooks.hook_index_leases6_committed_);

    // DHCP query.
    Pkt6Ptr query6 = createMessage6(DHCPV6_REQUEST, 1, 0);
    callout_handle->setArgument("query6", query6);

    // Leases.
    DuidPtr duid(new DUID(std::vector<uint8_t>(8, 2)));
    Lease6Ptr lease6(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::cafe"), duid,
                                1234, 50, 60, 1));
    Lease6CollectionPtr leases6(new Lease6Collection());
    leases6->push_back(lease6);
    callout_handle->setArgument("leases6", leases6);

    Lease6CollectionPtr deleted_leases6(new Lease6Collection());
    callout_handle->setArgument("deleted_leases6", deleted_leases6);

    // Park the packet.
    HooksManager::park("leases6_committed", query6, []{});

    // Run the callout.
    ASSERT_NO_THROW(test_ha_impl_->leases6Committed(*callout_handle));

    // The relationship was not found so the packet should be dropped.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query6));

    // Drop statistics should have been increased.
    EXPECT_EQ(1, getStatistic("pkt6-not-for-us"));
    EXPECT_EQ(1, getStatistic("pkt6-receive-drop"));
}

// Tests leases6_committed callout implementation for multiple relationships when
// the relationship name is invalid.
TEST_F(HAImplTest, leases6CommittedMultipleRelationshipsInvalidServerName) {
    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(createValidHubJsonConfiguration()));

    // Starting the service is required before running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    // By enabling this setting we ensure that the lease updates are always
    // scheduled and the packet is parked because it is independent of a
    // server state.
    test_ha_impl_->config_->get("server2")->setWaitBackupAck(true);

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);

    // Set the hook index so we can park the packets.
    callout_handle->setCurrentHook(test_hooks.hook_index_leases6_committed_);

    // The server name is required to select HA relationship.
    callout_handle->setContext("ha-server-name", std::string("serverX"));

    // DHCP query.
    Pkt6Ptr query6 = createMessage6(DHCPV6_REQUEST, 1, 0);
    callout_handle->setArgument("query6", query6);

    // Leases.
    DuidPtr duid(new DUID(std::vector<uint8_t>(8, 2)));
    Lease6CollectionPtr leases6(new Lease6Collection());
    Lease6Ptr lease6(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::cafe"), duid,
                                1234, 50, 60, 1));
    leases6->push_back(lease6);
    callout_handle->setArgument("leases6", leases6);

    Lease6CollectionPtr deleted_leases6(new Lease6Collection());
    callout_handle->setArgument("deleted_leases6", deleted_leases6);

    // Park the packet.
    HooksManager::park("leases6_committed", query6, []{});

    // Run the callout.
    ASSERT_NO_THROW(test_ha_impl_->leases6Committed(*callout_handle));

    // The relationship was not found so the packet should be dropped.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query6));

    // Drop statistics should have been increased.
    EXPECT_EQ(1, getStatistic("pkt6-not-for-us"));
    EXPECT_EQ(1, getStatistic("pkt6-receive-drop"));
}

// Tests lease4_expire callout implementation when the server is a hub
// with multiple relationships.
TEST_F(HAImplTest, lease4ExpireHub) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the lease
    auto lease4 = createLease4(std::vector<uint8_t>(6, 1));
    lease4->addr_ = IOAddress("192.0.2.1");
    lease4->subnet_id_ = 7;
    callout_handle->setArgument("lease4", lease4);

    // Create the subnet and include the server name in the context.
    auto context = Element::createMap();
    context->set("ha-server-name", Element::create("server3"));
    auto subnet4 = Subnet4::create(IOAddress("192.0.2.0"), 24, 30, 40, 50, 7);
    subnet4->setContext(context);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet4);
    CfgMgr::instance().commit();

    // Invoke the lease4_expire callout and expect that the lease reclamation
    // will continue because the server is responsible for the lease.
    ASSERT_NO_THROW(test_ha_impl_->lease4Expire(*callout_handle));
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Mark the server not responsible for the lease. This time the reclamation
    // should be skipped.
    test_ha_impl_->should_reclaim_dhcpv4_lease_ = false;
    ASSERT_NO_THROW(test_ha_impl_->lease4Expire(*callout_handle));
    EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, callout_handle->getStatus());
}

// Tests lease4_expire callout implementation when the server is a hub
// with multiple relationships and no matching subnet has been configured.
TEST_F(HAImplTest, lease4ExpireHubNoSubnet) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the lease
    auto lease4 = createLease4(std::vector<uint8_t>(6, 1));
    lease4->addr_ = IOAddress("192.0.2.1");
    lease4->subnet_id_ = 7;
    callout_handle->setArgument("lease4", lease4);

    // Reclamation should continue because this server's jurisdiction is
    // indeterminate.
    test_ha_impl_->should_reclaim_dhcpv4_lease_ = false;
    ASSERT_NO_THROW(test_ha_impl_->lease4Expire(*callout_handle));
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
}

// Tests lease4_expire callout implementation when the server is a hub
// but the server name is empty.
TEST_F(HAImplTest, lease4ExpireHubEmptyServerName) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the lease
    auto lease4 = createLease4(std::vector<uint8_t>(6, 1));
    lease4->addr_ = IOAddress("192.0.2.1");
    lease4->subnet_id_ = 7;
    callout_handle->setArgument("lease4", lease4);

    // Create the subnet and include empty server name in the context.
    auto context = Element::createMap();
    context->set("ha-server-name", Element::create(""));
    auto subnet4 = Subnet4::create(IOAddress("192.0.2.0"), 24, 30, 40, 50, 7);
    subnet4->setContext(context);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet4);
    CfgMgr::instance().commit();

    // Even though we intruct the server to skip the reclamation, the returned
    // status should indicate otherwise because the callout returns early after
    // checking that the server name is empty.
    test_ha_impl_->should_reclaim_dhcpv4_lease_ = false;
    ASSERT_NO_THROW(test_ha_impl_->lease4Expire(*callout_handle));
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
}

// Tests lease4_expire callout implementation when the server is a hub
// but the server name has invalid type.
TEST_F(HAImplTest, lease4ExpireHubInvalidServerName) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the lease
    auto lease4 = createLease4(std::vector<uint8_t>(6, 1));
    lease4->addr_ = IOAddress("192.0.2.1");
    lease4->subnet_id_ = 7;
    callout_handle->setArgument("lease4", lease4);

    // Create the subnet and include the server name argument. It has an
    // invalid type.
    auto context = Element::createMap();
    context->set("ha-server-name", Element::create(123));
    auto subnet4 = Subnet4::create(IOAddress("192.0.2.0"), 24, 30, 40, 50, 7);
    subnet4->setContext(context);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet4);
    CfgMgr::instance().commit();

    // Even though we intruct the server to skip the reclamation, the returned
    // status should indicate otherwise because the callout returns early after
    // checking that the server name has invalid type.
    test_ha_impl_->should_reclaim_dhcpv4_lease_ = false;
    ASSERT_NO_THROW(test_ha_impl_->lease4Expire(*callout_handle));
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
}

// Tests lease4_expire callout implementation when the server is a hub
// with multiple relationships.
TEST_F(HAImplTest, lease4ExpireSingleService) {
    ConstElementPtr ha_config = createValidJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the lease
    auto lease4 = createLease4(std::vector<uint8_t>(6, 1));
    lease4->subnet_id_ = 7;
    lease4->addr_ = IOAddress("192.0.2.1");
    callout_handle->setArgument("lease4", lease4);

    // Invoke the lease4_expire callout and expect that the lease reclamation
    // will continue because the server is responsible for the lease.
    ASSERT_NO_THROW(test_ha_impl_->lease4Expire(*callout_handle));
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Mark the server not responsible for the lease. This time the reclamation
    // should be skipped.
    test_ha_impl_->should_reclaim_dhcpv4_lease_ = false;
    ASSERT_NO_THROW(test_ha_impl_->lease4Expire(*callout_handle));
    EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, callout_handle->getStatus());
}

// Tests lease4_expire callout implementation when the server is a hub
// with multiple relationships.
TEST_F(HAImplTest, lease6ExpireHub) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the lease
    auto lease6 = createLease6(std::vector<uint8_t>(8, 1));
    lease6->addr_ = IOAddress("2001:db8:1::1");
    lease6->subnet_id_ = 7;
    callout_handle->setArgument("lease6", lease6);

    // Create the subnet and include the server name in the context.
    auto context = Element::createMap();
    context->set("ha-server-name", Element::create("server3"));
    auto subnet6 = Subnet6::create(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 7);
    subnet6->setContext(context);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet6);
    CfgMgr::instance().commit();

    // Invoke the lease6_expire callout and expect that the lease reclamation
    // will continue because the server is responsible for the lease.
    ASSERT_NO_THROW(test_ha_impl_->lease6Expire(*callout_handle));
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Mark the server not responsible for the lease. This time the reclamation
    // should be skipped.
    test_ha_impl_->should_reclaim_dhcpv6_lease_ = false;
    ASSERT_NO_THROW(test_ha_impl_->lease6Expire(*callout_handle));
    EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, callout_handle->getStatus());
}

// Tests lease6_expire callout implementation when the server is a hub
// with multiple relationships and no matching subnet has been configured.
TEST_F(HAImplTest, lease6ExpireHubNoSubnet) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the lease
    auto lease6 = createLease6(std::vector<uint8_t>(8, 1));
    lease6->addr_ = IOAddress("2001:db8:1::1");
    lease6->subnet_id_ = 7;
    callout_handle->setArgument("lease6", lease6);

    test_ha_impl_->should_reclaim_dhcpv6_lease_ = false;
    ASSERT_NO_THROW(test_ha_impl_->lease6Expire(*callout_handle));
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
}

// Tests lease6_expire callout implementation when the server is a hub
// but the server name is empty.
TEST_F(HAImplTest, lease6ExpireHubEmptyServerName) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv6));

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the lease
    auto lease6 = createLease6(std::vector<uint8_t>(8, 1));
    lease6->addr_ = IOAddress("2001:db8:1::1");
    lease6->subnet_id_ = 7;
    callout_handle->setArgument("lease6", lease6);

    // Create the subnet and include the server name in the context.
    auto context = Element::createMap();
    context->set("ha-server-name", Element::create(""));
    auto subnet6 = Subnet6::create(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 7);
    subnet6->setContext(context);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet6);
    CfgMgr::instance().commit();

    // Even though we intruct the server to skip the reclamation, the returned
    // status should indicate otherwise because the callout returns early after
    // checking that the server name is empty.
    test_ha_impl_->should_reclaim_dhcpv6_lease_ = false;
    ASSERT_NO_THROW(test_ha_impl_->lease6Expire(*callout_handle));
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
}

// Tests lease4_expire callout implementation when the server is a hub
// but the server name has invalid type.
TEST_F(HAImplTest, lease6ExpireHubInvalidServerName) {
    ConstElementPtr ha_config = createValidHubJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the lease
    auto lease6 = createLease6(std::vector<uint8_t>(8, 1));
    lease6->addr_ = IOAddress("2001:db8:1::1");
    lease6->subnet_id_ = 7;
    callout_handle->setArgument("lease6", lease6);

    // Create the subnet and include the server name argument. It has an
    // invalid type.

    // Create the subnet and include the server name in the context.
    auto context = Element::createMap();
    context->set("ha-server-name", Element::create(123));
    auto subnet6 = Subnet6::create(IOAddress("2001:db8:1::"), 64, 30, 40, 50, 60, 7);
    subnet6->setContext(context);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet6);
    CfgMgr::instance().commit();

    // Even though we intruct the server to skip the reclamation, the returned
    // status should indicate otherwise because the callout returns early after
    // checking that the server name has invalid type.
    test_ha_impl_->should_reclaim_dhcpv6_lease_ = false;
    ASSERT_NO_THROW(test_ha_impl_->lease6Expire(*callout_handle));
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
}

// Tests lease4_expire callout implementation when the server is a hub
// with multiple relationships.
TEST_F(HAImplTest, lease6ExpireSingleService) {
    ConstElementPtr ha_config = createValidJsonConfiguration();

    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(ha_config));

    // Starting the service is required before any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);
    ASSERT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Create the lease
    auto lease6 = createLease6(std::vector<uint8_t>(8, 1));
    lease6->addr_ = IOAddress("2001:db8:1::1");
    lease6->subnet_id_ = 7;
    callout_handle->setArgument("lease6", lease6);

    // Invoke the lease6_expire callout and expect that the lease reclamation
    // will continue because the server is responsible for the lease.
    ASSERT_NO_THROW(test_ha_impl_->lease6Expire(*callout_handle));
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    // Mark the server not responsible for the lease. This time the reclamation
    // should be skipped.
    test_ha_impl_->should_reclaim_dhcpv6_lease_ = false;
    ASSERT_NO_THROW(test_ha_impl_->lease6Expire(*callout_handle));
    EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, callout_handle->getStatus());
}

// Tests ha-sync command handler with correct and incorrect arguments.
TEST_F(HAImplTest, synchronizeHandler) {
    {
        // This syntax is correct. The error returned is simply a result of
        // trying to connect to the server which is offline, which should
        // result in connection refused error.
        SCOPED_TRACE("Correct syntax");
        testSynchronizeHandler("{"
                               "    \"command\": \"ha-sync\","
                               "    \"arguments\": {"
                               "        \"server-name\": \"server2\""
                               "    }"
                               "}", "Connection refused");
    }

    {
        SCOPED_TRACE("No arguments");
        testSynchronizeHandler("{"
                               "    \"command\": \"ha-sync\""
                               "}", "arguments not found in the 'ha-sync' command");
    }

    {
        SCOPED_TRACE("No server name");
        testSynchronizeHandler("{"
                               "    \"command\": \"ha-sync\","
                               "    \"arguments\": {"
                               "        \"max-period\": 20"
                               "    }"
                               "}", "'server-name' is mandatory for the 'ha-sync' command");
    }

    {
        SCOPED_TRACE("Server name is not a string");
        testSynchronizeHandler("{"
                               "    \"command\": \"ha-sync\","
                               "    \"arguments\": {"
                               "        \"server-name\": 20"
                               "    }"
                               "}", "'server-name' must be a string in the 'ha-sync' command");
    }

    {
        SCOPED_TRACE("Max period is not a number");
        testSynchronizeHandler("{"
                               "    \"command\": \"ha-sync\","
                               "    \"arguments\": {"
                               "        \"server-name\": \"server2\","
                               "        \"max-period\": \"20\""
                               "    }"
                               "}", "'max-period' must be a positive integer in the 'ha-sync'"
                               " command");
    }

    {
        SCOPED_TRACE("Max period must be positive");
        testSynchronizeHandler("{"
                               "    \"command\": \"ha-sync\","
                               "    \"arguments\": {"
                               "        \"server-name\": \"server2\","
                               "        \"max-period\": \"20\""
                               "    }"
                               "}", "'max-period' must be a positive integer in the 'ha-sync'"
                               " command");
    }

    {
        SCOPED_TRACE("Server name must be valid");
        testSynchronizeHandler("{"
                               "    \"command\": \"ha-sync\","
                               "    \"arguments\": {"
                               "        \"server-name\": \"server5\","
                               "        \"max-period\": 20"
                               "    }"
                               "}", "server5 matches no configured 'server-name'");
    }

}

// Tests ha-continue command handler with a specified server name.
TEST_F(HAImplTest, continueHandler) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON("{"
        "\"command\": \"ha-continue\","
        "\"arguments\": {"
        "    \"server-name\": \"server1\""
        "}"
    "}");

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->continueHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS, "HA state machine is not paused.");
}

// Tests ha-continue command handler without a server name.
TEST_F(HAImplTest, continueHandlerWithNoServerName) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON("{ \"command\": \"ha-continue\" }");

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->continueHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS, "HA state machine is not paused.");
}

// Tests ha-continue command handler with wrong server name.
TEST_F(HAImplTest, continueHandlerWithWrongServerName) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON("{"
        "\"command\": \"ha-continue\","
        "\"arguments\": {"
        "    \"server-name\": \"server5\""
        "}"
    "}");

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->continueHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_ERROR, "server5 matches no configured 'server-name'");
}

// Tests status-get command processed handler.
TEST_F(HAImplTest, statusGet) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    std::string name = "status-get";
    ConstElementPtr response =
        Element::fromJSON("{ \"arguments\": { \"pid\": 1 }, \"result\": 0 }");

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    callout_handle->setArgument("name", name);
    callout_handle->setArgument("response", response);

    ASSERT_NO_THROW(ha_impl_->commandProcessed(*callout_handle));

    ConstElementPtr got;
    callout_handle->getArgument("response", got);
    ASSERT_TRUE(got);

    // Check that system-time exists and that format is parsable by ptime.
    // Do not check exact value because it can be time-sensitive.
    ConstElementPtr ha_servers(
        got->get("arguments")->get("high-availability")->get(0)->get("ha-servers"));
    EXPECT_TRUE(ha_servers);
    ElementPtr local(boost::const_pointer_cast<Element>(ha_servers->get("local")));
    ElementPtr remote(boost::const_pointer_cast<Element>(ha_servers->get("remote")));
    checkThatTimeIsParsable(local, /* null_expected = */ true);
    checkThatTimeIsParsable(remote, /* null_expected = */ true);

    std::string expected =
        "{"
        "    \"arguments\": {"
        "        \"high-availability\": ["
        "            {"
        "                \"ha-mode\": \"load-balancing\","
        "                \"ha-servers\": {"
        "                    \"local\": {"
        "                        \"role\": \"primary\","
        "                        \"scopes\": [  ],"
        "                        \"server-name\": \"server1\","
        "                        \"state\": \"waiting\""
        "                    },"
        "                    \"remote\": {"
        "                        \"server-name\": \"server2\","
        "                        \"age\": 0,"
        "                        \"in-touch\": false,"
        "                        \"last-scopes\": [ ],"
        "                        \"last-state\": \"\","
        "                        \"role\": \"secondary\","
        "                        \"communication-interrupted\": false,"
        "                        \"connecting-clients\": 0,"
        "                        \"unacked-clients\": 0,"
        "                        \"unacked-clients-left\": 0,"
        "                        \"analyzed-packets\": 0,"
        "                        \"clock-skew\": null"
        "                    }"
        "                }"
        "            }"
        "        ],"
        "        \"pid\": 1"
        "    },"
        "    \"result\": 0"
        "}";
    expectEqWithDiff(Element::fromJSON(expected), got);
}

// Tests status-get command processed handler for backup server.
TEST_F(HAImplTest, statusGetBackupServer) {
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(createValidJsonConfiguration()));
    test_ha_impl_->config_->get()->setThisServerName("server3");

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    std::string name = "status-get";
    ConstElementPtr response =
        Element::fromJSON("{ \"arguments\": { \"pid\": 1 }, \"result\": 0 }");

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    callout_handle->setArgument("name", name);
    callout_handle->setArgument("response", response);

    ASSERT_NO_THROW(test_ha_impl_->commandProcessed(*callout_handle));

    ConstElementPtr got;
    callout_handle->getArgument("response", got);
    ASSERT_TRUE(got);

    // Check that system-time exists and that format is parsable by ptime.
    // Do not check exact value because it can be time-sensitive.
    ConstElementPtr ha_servers(
        got->get("arguments")->get("high-availability")->get(0)->get("ha-servers"));
    EXPECT_TRUE(ha_servers);
    ElementPtr local(boost::const_pointer_cast<Element>(ha_servers->get("local")));
    checkThatTimeIsParsable(local, /* null_expected = */ true);

    std::string expected =
        "{"
        "    \"arguments\": {"
        "        \"high-availability\": ["
        "            {"
        "                \"ha-mode\": \"load-balancing\","
        "                \"ha-servers\": {"
        "                    \"local\": {"
        "                        \"role\": \"backup\","
        "                        \"scopes\": [  ],"
        "                        \"server-name\": \"server3\","
        "                        \"state\": \"backup\""
        "                    }"
        "                }"
        "            }"
        "        ],"
        "        \"pid\": 1"
        "    },"
        "    \"result\": 0"
        "}";
    expectEqWithDiff(Element::fromJSON(expected), got);
}

// Tests status-get command processed handler for primary server being in the
// passive-backup state.
TEST_F(HAImplTest, statusGetPassiveBackup) {
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(createValidPassiveBackupJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    std::string name = "status-get";
    ConstElementPtr response =
        Element::fromJSON("{ \"arguments\": { \"pid\": 1 }, \"result\": 0 }");

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    callout_handle->setArgument("name", name);
    callout_handle->setArgument("response", response);

    ASSERT_NO_THROW(test_ha_impl_->commandProcessed(*callout_handle));

    ConstElementPtr got;
    callout_handle->getArgument("response", got);
    ASSERT_TRUE(got);

    // Check that system-time exists and that format is parsable by ptime.
    // Do not check exact value because it can be time-sensitive.
    ConstElementPtr ha_servers(
        got->get("arguments")->get("high-availability")->get(0)->get("ha-servers"));
    EXPECT_TRUE(ha_servers);
    ElementPtr local(boost::const_pointer_cast<Element>(ha_servers->get("local")));
    checkThatTimeIsParsable(local, /* null_expected = */ true);

    std::string expected =
        "{"
        "    \"arguments\": {"
        "        \"high-availability\": ["
        "            {"
        "                \"ha-mode\": \"passive-backup\","
        "                \"ha-servers\": {"
        "                    \"local\": {"
        "                        \"role\": \"primary\","
        "                        \"scopes\": [ \"server1\" ],"
        "                        \"server-name\": \"server1\","
        "                        \"state\": \"passive-backup\""
        "                    }"
        "                }"
        "            }"
        "        ],"
        "        \"pid\": 1"
        "    },"
        "    \"result\": 0"
        "}";
    expectEqWithDiff(Element::fromJSON(expected), got);
}

// Tests status-get command processed handler for standby server in the
// hub-and-spoke mode.
TEST_F(HAImplTest, statusGetHubAndSpoke) {
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(createValidHubJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    std::string name = "status-get";
    ConstElementPtr response =
        Element::fromJSON("{ \"arguments\": { \"pid\": 1 }, \"result\": 0 }");

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    callout_handle->setArgument("name", name);
    callout_handle->setArgument("response", response);

    ASSERT_NO_THROW(test_ha_impl_->commandProcessed(*callout_handle));

    ConstElementPtr got;
    callout_handle->getArgument("response", got);
    ASSERT_TRUE(got);

    // Check that system-time exists and that format is parsable by ptime.
    // Do not check exact value because it can be time-sensitive.
    for (int i = 0; i < 2; ++i) {
        ConstElementPtr ha_servers(
            got->get("arguments")->get("high-availability")->get(i)->get("ha-servers"));
        EXPECT_TRUE(ha_servers);
        ElementPtr local(boost::const_pointer_cast<Element>(ha_servers->get("local")));
        ElementPtr remote(boost::const_pointer_cast<Element>(ha_servers->get("remote")));
        checkThatTimeIsParsable(local, /* null_expected = */ true);
        checkThatTimeIsParsable(remote, /* null_expected = */ true);
    }

    std::string expected =
        "{"
        "    \"arguments\": {"
        "        \"high-availability\": ["
        "            {"
        "                \"ha-mode\": \"hot-standby\","
        "                \"ha-servers\": {"
        "                    \"local\": {"
        "                        \"role\": \"standby\","
        "                        \"scopes\": [ ],"
        "                        \"server-name\": \"server2\","
        "                        \"state\": \"waiting\""
        "                    },"
        "                    \"remote\": {"
        "                        \"age\": 0,"
        "                        \"analyzed-packets\": 0,"
        "                        \"clock-skew\": null,"
        "                        \"communication-interrupted\": false,"
        "                        \"connecting-clients\": 0,"
        "                        \"in-touch\": false,"
        "                        \"last-scopes\": [ ],"
        "                        \"last-state\": \"\","
        "                        \"role\": \"primary\","
        "                        \"server-name\": \"server1\","
        "                        \"unacked-clients\": 0,"
        "                        \"unacked-clients-left\": 0"
        "                    }"
        "                }"
        "            },"
        "            {"
        "                \"ha-mode\": \"hot-standby\","
        "                \"ha-servers\": {"
        "                    \"local\": {"
        "                        \"role\": \"standby\","
        "                        \"scopes\": [ ],"
        "                        \"server-name\": \"server4\","
        "                        \"state\": \"waiting\""
        "                    },"
        "                    \"remote\": {"
        "                        \"age\": 0,"
        "                        \"analyzed-packets\": 0,"
        "                        \"clock-skew\": null,"
        "                        \"communication-interrupted\": false,"
        "                        \"connecting-clients\": 0,"
        "                        \"in-touch\": false,"
        "                        \"last-scopes\": [ ],"
        "                        \"last-state\": \"\","
        "                        \"role\": \"primary\","
        "                        \"server-name\": \"server3\","
        "                        \"unacked-clients\": 0,"
        "                        \"unacked-clients-left\": 0"
        "                    }"
        "                }"
        "            }"
        "        ],"
        "        \"pid\": 1"
        "    },"
        "    \"result\": 0"
        "}";
    expectEqWithDiff(Element::fromJSON(expected), got);
}

// Test ha-maintenance-notify command handler with server name.
TEST_F(HAImplTest, maintenanceNotify) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-maintenance-notify\","
        "    \"arguments\": {"
        "        \"cancel\": false,"
        "        \"server-name\": \"server1\""
        "    }"
         "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->maintenanceNotifyHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS, "Server is in-maintenance state.");
}

// Test ha-maintenance-notify command handler without server name.
TEST_F(HAImplTest, maintenanceNotifyNoServerName) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-maintenance-notify\","
        "    \"arguments\": {"
        "        \"cancel\": false"
        "    }"
         "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->maintenanceNotifyHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS, "Server is in-maintenance state.");
}

// Test ha-maintenance-notify command handler without server name.
TEST_F(HAImplTest, maintenanceNotifyBadServerName) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-maintenance-notify\","
        "    \"arguments\": {"
        "        \"cancel\": false,"
        "        \"server-name\": \"server5\""
        "    }"
         "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->maintenanceNotifyHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_ERROR, "server5 matches no configured 'server-name'");
}

// Test ha-maintenance-notify command handler with partner state.
TEST_F(HAImplTest, maintenanceNotifyPartnerState) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    // Start the maintenance.
    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-maintenance-notify\","
        "    \"arguments\": {"
        "        \"cancel\": false"
        "    }"
         "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->maintenanceNotifyHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS, "Server is in-maintenance state.");

    // Cancel the maintenance.
    command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-maintenance-notify\","
        "    \"arguments\": {"
        "        \"cancel\": true,"
        "        \"server-name\": \"server1\","
        "        \"state\": \"waiting\""
        "    }"
         "}"
    );

    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->maintenanceNotifyHandler(*callout_handle));

    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS, "Server maintenance canceled.");
}

// Test ha-reset command handler with a specified server name.
TEST_F(HAImplTest, haReset) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-reset\","
        "    \"arguments\": {"
        "        \"server-name\": \"server1\""
        "    }"
        "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->haResetHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS, "HA state machine already in WAITING state.");
}

// Test ha-reset command handler without a specified server name.
TEST_F(HAImplTest, haResetNoServerName) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-reset\""
        "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->haResetHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS, "HA state machine already in WAITING state.");
}

// Test ha-reset command handler with a wrong server name.
TEST_F(HAImplTest, haResetBadServerName) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-reset\","
        "    \"arguments\": {"
        "        \"server-name\": \"server5\""
        "    }"
        "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->haResetHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_ERROR, "server5 matches no configured 'server-name'");
}

// Test ha-heartbeat command handler with a specified server name.
TEST_F(HAImplTest, haHeartbeat) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-heartbeat\","
        "    \"arguments\": {"
        "        \"server-name\": \"server1\""
        "    }"
        "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->heartbeatHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS, "HA peer status returned.");
}

// Test ha-heartbeat command handler without a specified server name.
TEST_F(HAImplTest, haHeartbeatNoServerName) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-heartbeat\""
        "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->heartbeatHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS, "HA peer status returned.");
}

// Test ha-heartbeat command handler with a wrong server name.
TEST_F(HAImplTest, haHeartbeatBadServerName) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-heartbeat\","
        "    \"arguments\": {"
        "        \"server-name\": \"server5\""
        "    }"
        "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->heartbeatHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_ERROR, "server5 matches no configured 'server-name'");
}

// Test ha-sync-complete-notify command handler with a specified server name
// and origin-id.
TEST_F(HAImplTest, haSyncCompleteNotifyOriginId) {
    ha_impl_.reset(new TestHAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-sync-complete-notify\","
        "    \"arguments\": {"
        "        \"server-name\": \"server1\","
        "        \"origin-id\": 2002"
        "    }"
        "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    // Disable the DHCP service for origin of 2002. Running the command
    // handler should unlock it.
    network_state->disableService(NetworkState::HA_REMOTE_COMMAND + 2);

    ASSERT_NO_THROW(ha_impl_->syncCompleteNotifyHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS,
                "Server successfully notified about the synchronization completion.");

    // The command handler should keep the service disabled under the HA_LOCAL_COMMAND.
    // Let's try to enable it and see if it unlocks the DHCP service.
    EXPECT_FALSE(network_state->isServiceEnabled());
    network_state->enableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_TRUE(network_state->isServiceEnabled());
}

// Test ha-sync-complete-notify command handler with a specified server name
// and origin.
TEST_F(HAImplTest, haSyncCompleteNotifyOrigin) {
    ha_impl_.reset(new TestHAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-sync-complete-notify\","
        "    \"arguments\": {"
        "        \"server-name\": \"server1\","
        "        \"origin\": 2002"
        "    }"
        "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    // Disable the DHCP service for origin of 2002. Running the command
    // handler should unlock it.
    network_state->disableService(NetworkState::HA_REMOTE_COMMAND + 2);

    ASSERT_NO_THROW(ha_impl_->syncCompleteNotifyHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS,
                "Server successfully notified about the synchronization completion.");

    // The command handler should keep the service disabled under the HA_LOCAL_COMMAND.
    // Let's try to enable it and see if it unlocks the DHCP service.
    EXPECT_FALSE(network_state->isServiceEnabled());
    network_state->enableService(NetworkState::HA_LOCAL_COMMAND);
    EXPECT_TRUE(network_state->isServiceEnabled());
}

// Test ha-sync-complete-notify command handler without a specified server name.
TEST_F(HAImplTest, haSyncCompleteNotifyNoServerName) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-sync-complete-notify\""
        "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->syncCompleteNotifyHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS,
                "Server successfully notified about the synchronization completion.");
}

// Test ha-sync-complete-notify command handler with a wrong server name.
TEST_F(HAImplTest, haSyncCompleteNotifyBadServerName) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-sync-complete-notify\","
        "    \"arguments\": {"
        "        \"server-name\": \"server5\""
        "    }"
        "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->syncCompleteNotifyHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_ERROR, "server5 matches no configured 'server-name'");
}

// Test ha-scopes command handler with a specified server name.
TEST_F(HAImplTest, haScopes) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-scopes\","
        "    \"arguments\": {"
        "        \"scopes\": [ \"server1\", \"server2\" ],"
        "        \"server-name\": \"server1\""
        "    }"
        "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->scopesHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS, "New HA scopes configured.");
}

// Test ha-scopes command handler without a specified server name.
TEST_F(HAImplTest, haScopesNoServerName) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-scopes\","
        "    \"arguments\": {"
        "        \"scopes\": [ \"server1\", \"server2\" ]"
        "    }"
        "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->scopesHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS, "New HA scopes configured.");
}

// Test ha-scopes command handler with a wrong server name.
TEST_F(HAImplTest, haScopesBadServerName) {
    ha_impl_.reset(new HAImpl());
    ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(ha_impl_->startServices(network_state,
                                            HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-scopes\","
        "    \"arguments\": {"
        "        \"scopes\": [ \"server1\", \"server2\" ],"
        "        \"server-name\": \"server5\""
        "    }"
        "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl_->scopesHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_ERROR, "server5 matches no configured 'server-name'");
}

// Tests lease4_server_decline callout implementation.
TEST_F(HAImplTest, lease4ServerDecline) {
    // Create implementation object and configure it.
    test_ha_impl_.reset(new TestHAImpl());
    test_ha_impl_->setIOService(io_service_);
    ASSERT_NO_THROW(test_ha_impl_->configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState());
    ASSERT_NO_THROW(test_ha_impl_->startServices(network_state,
                                                 HAServerType::DHCPv4));

    // Make sure we wait for the acks from the backup server to be able to
    // test the case of sending lease updates even though the service is
    // in the state in which the lease updates are normally not sent.
    test_ha_impl_->config_->get()->setWaitBackupAck(true);

    // Create callout handle to be used for passing arguments to the
    // callout.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    ASSERT_TRUE(callout_handle);

    // Set the hook index so we can park packets.
    callout_handle->setCurrentHook(test_hooks.hook_index_lease4_server_decline_);

    // query4
    Pkt4Ptr query4 = createMessage4(DHCPDISCOVER, 1, 0, 0);
    callout_handle->setArgument("query4", query4);

    // Create a lease and pass it to the callout.
    HWAddrPtr hwaddr(new HWAddr(std::vector<uint8_t>(6, 1), HTYPE_ETHER));
    Lease4Ptr lease4(new Lease4(IOAddress("192.1.2.3"), hwaddr,
                                static_cast<const uint8_t*>(0), 0,
                                60, 0, 1));

    callout_handle->setArgument("lease4", lease4);

    // Set initial status.
    callout_handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);

    test_ha_impl_->config_->get()->setSendLeaseUpdates(false);

    // Run the callout.
    ASSERT_NO_THROW(test_ha_impl_->lease4ServerDecline(*callout_handle));

    // Status should be continue.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    size_t peers_to_update;
    ASSERT_NO_THROW_LOG(callout_handle->getArgument("peers_to_update", peers_to_update));
    EXPECT_EQ(peers_to_update, 0);

    // Enable updates and retry.
    test_ha_impl_->config_->get()->setSendLeaseUpdates(true);
    callout_handle->setArgument("lease4", lease4);

    // Run the callout again.
    ASSERT_NO_THROW(test_ha_impl_->lease4ServerDecline(*callout_handle));

    // Status should be continue.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());

    ASSERT_NO_THROW_LOG(callout_handle->getArgument("peers_to_update", peers_to_update));
    EXPECT_EQ(peers_to_update, 1);
}

}
