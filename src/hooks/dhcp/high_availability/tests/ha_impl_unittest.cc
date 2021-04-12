// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/lease.h>
#include <dhcpsrv/network_state.h>
#include <hooks/hooks_manager.h>
#include <testutils/gtest_utils.h>
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

namespace {

/// @brief Structure that holds registered hook indexes.
///
/// This allows us to park packets.
struct TestHooks {
    /// @brief Index of leases4_committed callout.
    int hook_index_leases4_committed_;

    /// @brief Index of leases6_committed callout.
    int hook_index_leases6_committed_;

    /// @brief Constructor
    ///
    /// The constructor registers hook points for callout tests.
    TestHooks() {
        hook_index_leases4_committed_ =
            HooksManager::registerHook("leases4_committed");
        hook_index_leases6_committed_ =
            HooksManager::registerHook("leases6_committed");
    }
};

TestHooks test_hooks;

/// @brief Derivation of the @c HAImpl which provides access to protected
/// methods and members.
class TestHAImpl : public HAImpl {
public:

    using HAImpl::config_;
    using HAImpl::service_;
};

/// @brief Test fixture class for @c HAImpl.
class HAImplTest : public HATest {
public:

    /// @brief Tests handler of a ha-sync command.
    ///
    /// It always expects that the error result is returned. The expected
    /// error text should be provided as function argument.
    ///
    /// @param ha_sync_command command provided as text.
    /// @param expected_response expected text response.
    void testSynchronizeHandler(const std::string& ha_sync_command,
                                const std::string& expected_response) {
        HAImpl ha_impl;
        ASSERT_NO_THROW(ha_impl.configure(createValidJsonConfiguration()));

        // Starting the service is required prior to running any callouts.
        NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv4));
        ASSERT_NO_THROW(ha_impl.startService(io_service_, network_state,
                                             HAServerType::DHCPv4));

        ConstElementPtr command = Element::fromJSON(ha_sync_command);

        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("command", command);

        ASSERT_NO_THROW(ha_impl.synchronizeHandler(*callout_handle));

        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);

        checkAnswer(response, CONTROL_RESULT_ERROR, expected_response);
    }
};

// Tests that HAService object is created for DHCPv4 service.
TEST_F(HAImplTest, startService) {
    // Valid configuration must be provided prior to starting the service.
    TestHAImpl ha_impl;
    ASSERT_NO_THROW(ha_impl.configure(createValidJsonConfiguration()));

    // Network state is also required.
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv4));

    // Start the service for DHCPv4 server.
    ASSERT_NO_THROW(ha_impl.startService(io_service_, network_state,
                                         HAServerType::DHCPv4));

    // Make sure that the HA service has been created for the requested
    // server type.
    ASSERT_TRUE(ha_impl.service_);
    EXPECT_EQ(HAServerType::DHCPv4, ha_impl.service_->getServerType());
}

// Tests that HAService object is created for DHCPv6 service.
TEST_F(HAImplTest, startService6) {
    // Valid configuration must be provided prior to starting the service.
    TestHAImpl ha_impl;
    ASSERT_NO_THROW(ha_impl.configure(createValidJsonConfiguration()));

    // Network state is also required.
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv6));

    // Start the service for DHCPv4 server.
    ASSERT_NO_THROW(ha_impl.startService(io_service_, network_state,
                                         HAServerType::DHCPv6));

    // Make sure that the HA service has been created for the requested
    // server type.
    ASSERT_TRUE(ha_impl.service_);
    EXPECT_EQ(HAServerType::DHCPv6, ha_impl.service_->getServerType());
}

// Tests for buffer4_receive callout implementation.
TEST_F(HAImplTest, buffer4Receive) {
    // Use hot-standby mode to make sure that this server instance is selected
    // to process each received query. This is going to give predictable results.
    ConstElementPtr ha_config = createValidJsonConfiguration(HAConfig::HOT_STANDBY);

    // Create implementation object and configure it.
    TestHAImpl ha_impl;
    ASSERT_NO_THROW(ha_impl.configure(ha_config));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv4));
    ASSERT_NO_THROW(ha_impl.startService(io_service_, network_state,
                                         HAServerType::DHCPv4));

    // Initially the HA service is in the waiting state and serves no scopes.
    // We need to explicitly enable the scope to be served.
    ha_impl.service_->serveDefaultScopes();

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
    ASSERT_NO_THROW(ha_impl.buffer4Receive(*callout_handle));

    // The BOOTP messages are not supported so trying to unpack the message
    // should trigger an error. The callout should set the next step to
    // DROP treating the message as malformed.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());
    // Malformed message should not be classified.
    EXPECT_TRUE(query4->getClasses().empty());

    // Turn this into the DHCP message by appending a magic cookie and the
    // options.
    std::vector<uint8_t> magic_cookie = {
        99, 130, 83, 99
    };

    // Provide DHCP message type option, truncated vendor option and domain name.
    // Parsing this message should be successful but domain name following the
    // truncated vendor option should be skipped.
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
    ASSERT_NO_THROW(ha_impl.buffer4Receive(*callout_handle));

    // This time the callout should set the next step to SKIP to indicate to
    // the DHCP server that the message has been already parsed.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, callout_handle->getStatus());

    // The client class should be assigned to the message to indicate that the
    // server1 should process this message.
    ASSERT_EQ(2, query4->getClasses().size());
    EXPECT_TRUE(query4->inClass("ALL"));
    EXPECT_TRUE(query4->inClass("HA_server1"));

    // Check that the message has been parsed. The DHCP message type should
    // be set in this case.
    EXPECT_EQ(DHCPDISCOVER, static_cast<int>(query4->getType()));
    // Domain name should be skipped because the vendor option was truncated.
    EXPECT_FALSE(query4->getOption(DHO_DOMAIN_NAME));
}

// Tests for buffer6_receive callout implementation.
TEST_F(HAImplTest, buffer6Receive) {
    // Use hot-standby mode to make sure that this server instance is selected
    // to process each received query. This is going to give predictable results.
    ConstElementPtr ha_config = createValidJsonConfiguration(HAConfig::HOT_STANDBY);

    // Create implementation object and configure it.
    TestHAImpl ha_impl;
    ASSERT_NO_THROW(ha_impl.configure(ha_config));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv6));
    ASSERT_NO_THROW(ha_impl.startService(io_service_, network_state,
                                         HAServerType::DHCPv6));

    // Initially the HA service is in the waiting state and serves no scopes.
    // We need to explicitly enable the scope to be served.
    ha_impl.service_->serveDefaultScopes();

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
    ASSERT_NO_THROW(ha_impl.buffer6Receive(*callout_handle));

    // Our DHCP messages contains no transaction id so it should cause
    // parsing error. The next step is set to DROP for malformed messages.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_DROP, callout_handle->getStatus());
    // Malformed message should not be classified.
    EXPECT_TRUE(query6->getClasses().empty());

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
    ASSERT_NO_THROW(ha_impl.buffer6Receive(*callout_handle));

    // This time the callout should set the next step to SKIP to indicate to
    // the DHCP server that the message has been already parsed.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, callout_handle->getStatus());

    // The client class should be assigned to the message to indicate that the
    // server1 should process this message.
    ASSERT_EQ(2, query6->getClasses().size());
    EXPECT_TRUE(query6->inClass("ALL"));
    EXPECT_TRUE(query6->inClass("HA_server1"));

    // Check that the message has been parsed. The DHCP message type should
    // be set in this case.
    EXPECT_EQ(DHCPV6_SOLICIT, static_cast<int>(query6->getType()));
    // Domain name should be skipped because the vendor option was truncated.
    EXPECT_FALSE(query6->getOption(D6O_NIS_DOMAIN_NAME));
}

// Tests leases4_committed callout implementation.
TEST_F(HAImplTest, leases4Committed) {
    // Create implementation object and configure it.
    TestHAImpl ha_impl;
    ASSERT_NO_THROW(ha_impl.configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv4));
    ASSERT_NO_THROW(ha_impl.startService(io_service_, network_state,
                                         HAServerType::DHCPv4));

    // Make sure we wait for the acks from the backup server to be able to
    // test the case of sending lease updates even though the service is
    // in the state in which the lease updates are normally not sent.
    ha_impl.config_->setWaitBackupAck(true);

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
    ASSERT_NO_THROW(ha_impl.leases4Committed(*callout_handle));

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

    ha_impl.config_->setSendLeaseUpdates(false);

    // Park the packet.
    HooksManager::park("leases4_committed", query4, []{});

    // Run the callout again.
    ASSERT_NO_THROW(ha_impl.leases4Committed(*callout_handle));

    // No updates are generated so the default status should not be modified.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query4));

    // Enable updates and retry.
    ha_impl.config_->setSendLeaseUpdates(true);
    callout_handle->setArgument("leases4", leases4);

    // Park the packet.
    HooksManager::park("leases4_committed", query4, []{});

    // Run the callout again.
    ASSERT_NO_THROW(ha_impl.leases4Committed(*callout_handle));

    // This time the lease update should be generated and the status should
    // be set to "park".
    EXPECT_EQ(CalloutHandle::NEXT_STEP_PARK, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query4));
}

// Tests leases6_committed callout implementation.
TEST_F(HAImplTest, leases6Committed) {
    // Create implementation object and configure it.
    TestHAImpl ha_impl;
    ASSERT_NO_THROW(ha_impl.configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv6));
    ASSERT_NO_THROW(ha_impl.startService(io_service_, network_state,
                                         HAServerType::DHCPv6));

    // Make sure we wait for the acks from the backup server to be able to
    // test the case of sending lease updates even though the service is
    // in the state in which the lease updates are normally not sent.
    ha_impl.config_->setWaitBackupAck(true);

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
    ASSERT_NO_THROW(ha_impl.leases6Committed(*callout_handle));

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

    ha_impl.config_->setSendLeaseUpdates(false);

    // Park the packet.
    HooksManager::park("leases6_committed", query6, []{});

    // Run the callout again.
    ASSERT_NO_THROW(ha_impl.leases6Committed(*callout_handle));

    // No updates are generated so the default status should not be modified.
    EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query6));

    // Enable updates and retry.
    ha_impl.config_->setSendLeaseUpdates(true);
    callout_handle->setArgument("leases6", leases6);

    // Park the packet.
    HooksManager::park("leases6_committed", query6, []{});

    // Run the callout again.
    ASSERT_NO_THROW(ha_impl.leases6Committed(*callout_handle));

    // This time the lease update should be generated and the status should
    // be set to "park".
    EXPECT_EQ(CalloutHandle::NEXT_STEP_PARK, callout_handle->getStatus());
    EXPECT_TRUE(callout_handle->getParkingLotHandlePtr()->drop(query6));
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

}

// Tests ha-continue command handler.
TEST_F(HAImplTest, continueHandler) {
    HAImpl ha_impl;
    ASSERT_NO_THROW(ha_impl.configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv4));
    ASSERT_NO_THROW(ha_impl.startService(io_service_, network_state,
                                         HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON("{ \"command\": \"ha-continue\" }");

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl.continueHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS, "HA state machine is not paused.");
}

// Tests status-get command processed handler.
TEST_F(HAImplTest, statusGet) {
    HAImpl ha_impl;
    ASSERT_NO_THROW(ha_impl.configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv4));
    ASSERT_NO_THROW(ha_impl.startService(io_service_, network_state,
                                         HAServerType::DHCPv4));

    std::string name = "status-get";
    ConstElementPtr response =
        Element::fromJSON("{ \"arguments\": { \"pid\": 1 }, \"result\": 0 }");

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    callout_handle->setArgument("name", name);
    callout_handle->setArgument("response", response);

    ASSERT_NO_THROW(ha_impl.commandProcessed(*callout_handle));

    ConstElementPtr got;
    callout_handle->getArgument("response", got);
    ASSERT_TRUE(got);

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
        "                        \"state\": \"waiting\""
        "                    },"
        "                    \"remote\": {"
        "                        \"age\": 0,"
        "                        \"in-touch\": false,"
        "                        \"last-scopes\": [ ],"
        "                        \"last-state\": \"\","
        "                        \"role\": \"secondary\","
        "                        \"communication-interrupted\": false,"
        "                        \"connecting-clients\": 0,"
        "                        \"unacked-clients\": 0,"
        "                        \"unacked-clients-left\": 0,"
        "                        \"analyzed-packets\": 0"
        "                    }"
        "                }"
        "            }"
        "        ],"
        "        \"pid\": 1"
        "    },"
        "    \"result\": 0"
        "}";
    EXPECT_TRUE(isEquivalent(got, Element::fromJSON(expected)));
}

// Tests status-get command processed handler for backup server.
TEST_F(HAImplTest, statusGetBackupServer) {
    TestHAImpl ha_impl;
    ASSERT_NO_THROW(ha_impl.configure(createValidJsonConfiguration()));
    ha_impl.config_->setThisServerName("server3");

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv4));
    ASSERT_NO_THROW(ha_impl.startService(io_service_, network_state,
                                         HAServerType::DHCPv4));

    std::string name = "status-get";
    ConstElementPtr response =
        Element::fromJSON("{ \"arguments\": { \"pid\": 1 }, \"result\": 0 }");

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    callout_handle->setArgument("name", name);
    callout_handle->setArgument("response", response);

    ASSERT_NO_THROW(ha_impl.commandProcessed(*callout_handle));

    ConstElementPtr got;
    callout_handle->getArgument("response", got);
    ASSERT_TRUE(got);

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
        "                        \"state\": \"backup\""
        "                    }"
        "                }"
        "            }"
        "        ],"
        "        \"pid\": 1"
        "    },"
        "    \"result\": 0"
        "}";
    EXPECT_TRUE(isEquivalent(got, Element::fromJSON(expected)));
}

// Tests status-get command processed handler for primary server being in the
// passive-backup state.
TEST_F(HAImplTest, statusGetPassiveBackup) {
    TestHAImpl ha_impl;
    ASSERT_NO_THROW(ha_impl.configure(createValidPassiveBackupJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv4));
    ASSERT_NO_THROW(ha_impl.startService(io_service_, network_state,
                                         HAServerType::DHCPv4));

    std::string name = "status-get";
    ConstElementPtr response =
        Element::fromJSON("{ \"arguments\": { \"pid\": 1 }, \"result\": 0 }");

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    callout_handle->setArgument("name", name);
    callout_handle->setArgument("response", response);

    ASSERT_NO_THROW(ha_impl.commandProcessed(*callout_handle));

    ConstElementPtr got;
    callout_handle->getArgument("response", got);
    ASSERT_TRUE(got);

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
        "                        \"state\": \"passive-backup\""
        "                    }"
        "                }"
        "            }"
        "        ],"
        "        \"pid\": 1"
        "    },"
        "    \"result\": 0"
        "}";
    EXPECT_TRUE(isEquivalent(got, Element::fromJSON(expected)));
}

// Test ha-maintenance-notify command handler.
TEST_F(HAImplTest, maintenanceNotify) {
    HAImpl ha_impl;
    ASSERT_NO_THROW(ha_impl.configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv4));
    ASSERT_NO_THROW(ha_impl.startService(io_service_, network_state,
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

    ASSERT_NO_THROW(ha_impl.maintenanceNotifyHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS, "Server is in-maintenance state.");
}

// Test ha-reset command handler.
TEST_F(HAImplTest, haReset) {
    HAImpl ha_impl;
    ASSERT_NO_THROW(ha_impl.configure(createValidJsonConfiguration()));

    // Starting the service is required prior to running any callouts.
    NetworkStatePtr network_state(new NetworkState(NetworkState::DHCPv4));
    ASSERT_NO_THROW(ha_impl.startService(io_service_, network_state,
                                         HAServerType::DHCPv4));

    ConstElementPtr command = Element::fromJSON(
        "{"
        "    \"command\": \"ha-reset\""
        "}"
    );

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("command", command);

    ASSERT_NO_THROW(ha_impl.haResetHandler(*callout_handle));

    ConstElementPtr response;
    callout_handle->getArgument("response", response);
    ASSERT_TRUE(response);

    checkAnswer(response, CONTROL_RESULT_SUCCESS, "HA state machine already in WAITING state.");
}

}
