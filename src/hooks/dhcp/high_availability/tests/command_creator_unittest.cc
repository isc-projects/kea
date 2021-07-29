// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ha_server_type.h>
#include <lease_update_backlog.h>
#include <command_creator.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/lease.h>
#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>
#include <vector>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::ha;

namespace {

/// @brief Creates lease instance used in tests.
///
/// It creates a lease with an address of 192.1.2.3 and for the HW address
/// of 0b:0b:0b:0b:0b:0b.
///
/// @return Pointer to the created lease.
Lease4Ptr createLease4() {
    HWAddrPtr hwaddr(new HWAddr(std::vector<uint8_t>(6, 11), HTYPE_ETHER));
    Lease4Ptr lease4(new Lease4(IOAddress("192.1.2.3"), hwaddr,
                                static_cast<const uint8_t*>(0), 0,
                                60, 0, 1));
    return (lease4);
}

/// @brief Creates IPv6 lease instance used in tests.
///
/// It creates a lease with an address of 2001:db8:1::cafe and for the
/// DUID of 02:02:02:02:02:02:02:02.
///
/// @return Pointer to the created lease.
Lease6Ptr createLease6() {
    DuidPtr duid(new DUID(std::vector<uint8_t>(8, 02)));
    Lease6Ptr lease6(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::cafe"),
                                duid, 1234, 50, 60, 1));
    return (lease6);
}

/// @brief Returns JSON representation of the lease.
///
/// @param lease_ptr Pointer to the lease.
/// @return Pointer to the JSON representation of the lease.
ElementPtr leaseAsJson(const LeasePtr& lease_ptr) {
    ElementPtr lease = boost::const_pointer_cast<Element>(lease_ptr->toElement());
    // Replace cltt with expiration time as this is what the lease_cmds hooks
    // library expects.
    int64_t cltt = lease->get("cltt")->intValue();
    int64_t valid_lifetime = lease->get("valid-lft")->intValue();
    int64_t expire = cltt + valid_lifetime;
    lease->set("expire", Element::create(expire));
    lease->remove("cltt");
    return (lease);
}

/// @brief Performs basic checks on the command.
///
/// It tests whether the command name is correct, if it contains arguments
/// and if the arguments are held in a map.
///
/// @param command Pointer to the command to be tested.
/// @param expected_command Expected command name.
/// @param expected_service Expected service name.
/// @param [out] arguments Pointer to the arguments map extracted from the
/// provided command.
void
testCommandBasics(const ConstElementPtr& command,
                  const std::string& expected_command,
                  const std::string& expected_service,
                  ConstElementPtr& arguments) {
    ASSERT_TRUE(command);
    ASSERT_EQ(Element::map, command->getType());
    ConstElementPtr command_name = command->get("command");
    ASSERT_TRUE(command_name);

    // Make sure the command is a string.
    ASSERT_EQ(Element::string, command_name->getType());
    // Verify the command name.
    ASSERT_EQ(expected_command, command_name->stringValue());

    // Make sure that the service is present and includes a single
    // entry.
    ConstElementPtr service = command->get("service");
    ASSERT_TRUE(service);
    ASSERT_EQ(Element::list, service->getType());
    ASSERT_EQ(1, service->size());
    ASSERT_EQ(Element::string, service->get(0)->getType());
    EXPECT_EQ(expected_service, service->get(0)->stringValue());

    // Make sure that arguments are present.
    ConstElementPtr command_arguments = command->get("arguments");
    ASSERT_TRUE(command_arguments);
    // Make sure that arguments are held in a map.
    ASSERT_EQ(Element::map, command_arguments->getType());

    // Return extracted arguments.
    arguments = command_arguments;
}

/// @brief Performs basic checks on the command.
///
/// This variant of the function expects no arguments to be provided.
///
/// @param command Pointer to the command to be tested.
/// @param expected_command Expected command name.
/// @param expected_service Expected service name.
void
testCommandBasics(const ConstElementPtr& command,
                  const std::string& expected_command,
                  const std::string& expected_service) {
    ASSERT_TRUE(command);
    ASSERT_EQ(Element::map, command->getType());
    ConstElementPtr command_name = command->get("command");
    ASSERT_TRUE(command_name);

    // Make sure the command is a string.
    ASSERT_EQ(Element::string, command_name->getType());
    // Verify the command name.
    ASSERT_EQ(expected_command, command_name->stringValue());

    // Make sure that the service is present and includes a single
    // entry.
    ConstElementPtr service = command->get("service");
    ASSERT_TRUE(service);
    ASSERT_EQ(Element::list, service->getType());
    ASSERT_EQ(1, service->size());
    ASSERT_EQ(Element::string, service->get(0)->getType());
    EXPECT_EQ(expected_service, service->get(0)->stringValue());

    ConstElementPtr command_arguments = command->get("arguments");
    ASSERT_FALSE(command_arguments);
}

// This test verifies that the dhcp-disable command is correct.
TEST(CommandCreatorTest, createDHCPDisable4) {
    // Create command with max-period value set to 20.
    ConstElementPtr command = CommandCreator::createDHCPDisable(20, HAServerType::DHCPv4);
    ConstElementPtr arguments;
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "dhcp-disable", "dhcp4",
                                              arguments));
    ASSERT_EQ(2, arguments->size());
    ConstElementPtr max_period = arguments->get("max-period");
    ASSERT_TRUE(max_period);
    ASSERT_EQ(Element::integer, max_period->getType());
    EXPECT_EQ(20, max_period->intValue());
    ConstElementPtr origin = arguments->get("origin");
    ASSERT_TRUE(origin);
    ASSERT_EQ("ha-partner", origin->stringValue());

    // Repeat the test but this time the max-period is not specified.
    command = CommandCreator::createDHCPDisable(0, HAServerType::DHCPv4);
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "dhcp-disable", "dhcp4",
                                              arguments));
    ASSERT_EQ(1, arguments->size());
    origin = arguments->get("origin");
    ASSERT_TRUE(origin);
    ASSERT_EQ("ha-partner", origin->stringValue());
}

// This test verifies that the dhcp-enable command is correct.
TEST(CommandCreatorTest, createDHCPEnable4) {
    ConstElementPtr arguments;
    ConstElementPtr command = CommandCreator::createDHCPEnable(HAServerType::DHCPv4);
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "dhcp-enable", "dhcp4",
                                              arguments));
    ASSERT_EQ(1, arguments->size());
    ConstElementPtr origin = arguments->get("origin");
    ASSERT_TRUE(origin);
    ASSERT_EQ("ha-partner", origin->stringValue());
}

// This test verifies that the ha-reset command sent to DHCPv4 server is correct.
TEST(CommandCreatorTest, createHAReset4) {
    ConstElementPtr command = CommandCreator::createHAReset(HAServerType::DHCPv4);
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "ha-reset", "dhcp4"));
}

// This test verifies that the ha-heartbeat command is correct.
TEST(CommandCreatorTest, createHeartbeat4) {
    ConstElementPtr command = CommandCreator::createHeartbeat(HAServerType::DHCPv4);
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "ha-heartbeat", "dhcp4"));
}

// This test verifies that the command generated for the lease update
// is correct.
TEST(CommandCreatorTest, createLease4Update) {
    ConstElementPtr command = CommandCreator::createLease4Update(*createLease4());
    ConstElementPtr arguments;
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "lease4-update", "dhcp4",
                                              arguments));
    ElementPtr lease_as_json = leaseAsJson(createLease4());
    // The lease update must contain the "force-create" parameter indicating that
    // the lease must be created if it doesn't exist.
    lease_as_json->set("force-create", Element::create(true));
    EXPECT_EQ(lease_as_json->str(), arguments->str());
}

// This test verifies that the command generated for the lease deletion
// is correct.
TEST(CommandCreatorTest, createLease4Delete) {
    ConstElementPtr command = CommandCreator::createLease4Delete(*createLease4());
    ConstElementPtr arguments;
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "lease4-del", "dhcp4",
                                              arguments));
    ElementPtr lease_as_json = leaseAsJson(createLease4());
    EXPECT_EQ(lease_as_json->str(), arguments->str());
}

// This test verifies that the lease4-get-all command is correct.
TEST(CommandCreatorTest, createLease4GetAll) {
    ConstElementPtr command = CommandCreator::createLease4GetAll();
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "lease4-get-all", "dhcp4"));
}

// This test verifies that the lease4-get-page command is correct when
// first page is fetched.
TEST(CommandCreatorTest, createLease4GetPageStart) {
    Lease4Ptr lease4;
    ConstElementPtr command = CommandCreator::createLease4GetPage(lease4, 10);
    ConstElementPtr arguments;
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "lease4-get-page", "dhcp4",
                                              arguments));

    ConstElementPtr from = arguments->get("from");
    ASSERT_TRUE(from);
    EXPECT_EQ(Element::string, from->getType());
    EXPECT_EQ("start", from->stringValue());

    ConstElementPtr limit = arguments->get("limit");
    ASSERT_TRUE(limit);
    ASSERT_EQ(Element::integer, limit->getType());
    EXPECT_EQ(10, limit->intValue());
}

// This test verifies that the lease4-get-page command is correct when next
// page is fetched.
TEST(CommandCreatorTest, createLease4GetPageAddress) {
    Lease4Ptr lease4(new Lease4());
    lease4->addr_ = IOAddress("1.2.3.4");

    ConstElementPtr command = CommandCreator::createLease4GetPage(lease4, 15);
    ConstElementPtr arguments;
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "lease4-get-page", "dhcp4",
                                              arguments));

    ConstElementPtr from = arguments->get("from");
    ASSERT_TRUE(from);
    EXPECT_EQ(Element::string, from->getType());
    EXPECT_EQ("1.2.3.4", from->stringValue());

    ConstElementPtr limit = arguments->get("limit");
    ASSERT_TRUE(limit);
    ASSERT_EQ(Element::integer, limit->getType());
    EXPECT_EQ(15, limit->intValue());
}

// This test verifies that exception is thrown if limit is set to 0 while
// creating lease4-get-page command.
TEST(CommandCreatorTest, createLease4GetPageZeroLimit) {
    Lease4Ptr lease4;
    EXPECT_THROW(CommandCreator::createLease4GetPage(lease4, 0), BadValue);
}

// This test verifies that the dhcp-disable command (DHCPv6 case) is
// correct.
TEST(CommandCreatorTest, createDHCPDisable6) {
    // Create command with max-period value set to 20.
    ConstElementPtr command = CommandCreator::createDHCPDisable(20, HAServerType::DHCPv6);
    ConstElementPtr arguments;
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "dhcp-disable", "dhcp6",
                                              arguments));
    ASSERT_EQ(2, arguments->size());
    ConstElementPtr max_period = arguments->get("max-period");
    ASSERT_TRUE(max_period);
    ASSERT_EQ(Element::integer, max_period->getType());
    EXPECT_EQ(20, max_period->intValue());
    ConstElementPtr origin = arguments->get("origin");
    ASSERT_TRUE(origin);
    ASSERT_EQ("ha-partner", origin->stringValue());

    // Repeat the test but this time the max-period is not specified.
    command = CommandCreator::createDHCPDisable(0, HAServerType::DHCPv6);
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "dhcp-disable", "dhcp6",
                                              arguments));
    ASSERT_EQ(1, arguments->size());
    origin = arguments->get("origin");
    ASSERT_TRUE(origin);
    ASSERT_EQ("ha-partner", origin->stringValue());
}

// This test verifies that the dhcp-enable command (DHCPv6 case) is
// correct.
TEST(CommandCreatorTest, createDHCPEnable6) {
    ConstElementPtr arguments;
    ConstElementPtr command = CommandCreator::createDHCPEnable(HAServerType::DHCPv6);
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "dhcp-enable", "dhcp6",
                                              arguments));
    ASSERT_EQ(1, arguments->size());
    ConstElementPtr origin = arguments->get("origin");
    ASSERT_TRUE(origin);
    ASSERT_EQ("ha-partner", origin->stringValue());
}

// This test verifies that the ha-reset command sent to DHCPv6 server is correct.
TEST(CommandCreatorTest, createHAReset6) {
    ConstElementPtr command = CommandCreator::createHAReset(HAServerType::DHCPv6);
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "ha-reset", "dhcp6"));
}

// This test verifies that the command generated for the lease update
// is correct.
TEST(CommandCreatorTest, createLease6Update) {
    ConstElementPtr command = CommandCreator::createLease6Update(*createLease6());
    ConstElementPtr arguments;
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "lease6-update", "dhcp6",
                                              arguments));
    ElementPtr lease_as_json = leaseAsJson(createLease6());
    // The lease update must contain the "force-create" parameter indicating that
    // the lease must be created if it doesn't exist.
    lease_as_json->set("force-create", Element::create(true));
    EXPECT_EQ(lease_as_json->str(), arguments->str());
}

// This test verifies that the command generated for the lease deletion
// is correct.
TEST(CommandCreatorTest, createLease6Delete) {
    ConstElementPtr command = CommandCreator::createLease6Delete(*createLease6());
    ConstElementPtr arguments;
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "lease6-del", "dhcp6",
                                              arguments));
    ElementPtr lease_as_json = leaseAsJson(createLease6());
    EXPECT_EQ(lease_as_json->str(), arguments->str());
}

// This test verifies that the lease6-bulk-apply command is correct.
TEST(CommandCreatorTest, createLease6BulkApply) {
    Lease6Ptr lease = createLease6();
    Lease6Ptr deleted_lease = createLease6();

    Lease6CollectionPtr leases(new Lease6Collection());
    Lease6CollectionPtr deleted_leases(new Lease6Collection());

    leases->push_back(lease);
    deleted_leases->push_back(lease);

    ConstElementPtr command = CommandCreator::createLease6BulkApply(leases, deleted_leases);
    ConstElementPtr arguments;
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "lease6-bulk-apply",
                                              "dhcp6", arguments));

    // Verify deleted-leases.
    auto deleted_leases_json = arguments->get("deleted-leases");
    ASSERT_TRUE(deleted_leases_json);
    ASSERT_EQ(Element::list, deleted_leases_json->getType());
    ASSERT_EQ(1, deleted_leases_json->size());
    auto lease_as_json = deleted_leases_json->get(0);
    EXPECT_EQ(leaseAsJson(createLease6())->str(), lease_as_json->str());

    // Verify leases.
    auto leases_json = arguments->get("leases");
    ASSERT_TRUE(leases_json);
    ASSERT_EQ(Element::list, leases_json->getType());
    ASSERT_EQ(1, leases_json->size());
    lease_as_json = leases_json->get(0);
    EXPECT_EQ(leaseAsJson(createLease6())->str(), lease_as_json->str());
}

// This test verifies that the lease6-bulk-apply command can be created
// from DHCPv6 leases backlog.
TEST(CommandCreatorTest, createLease6BulkApplyFromBacklog) {
    Lease6Ptr lease = createLease6();
    Lease6Ptr deleted_lease = createLease6();

    LeaseUpdateBacklog backlog(100);
    backlog.push(LeaseUpdateBacklog::ADD, lease);
    backlog.push(LeaseUpdateBacklog::DELETE, deleted_lease);

    ConstElementPtr command = CommandCreator::createLease6BulkApply(backlog);
    ConstElementPtr arguments;
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "lease6-bulk-apply",
                                              "dhcp6", arguments));

    // Verify deleted-leases.
    auto deleted_leases_json = arguments->get("deleted-leases");
    ASSERT_TRUE(deleted_leases_json);
    ASSERT_EQ(Element::list, deleted_leases_json->getType());
    ASSERT_EQ(1, deleted_leases_json->size());
    auto lease_as_json = deleted_leases_json->get(0);
    EXPECT_EQ(leaseAsJson(createLease6())->str(), lease_as_json->str());

    // Verify leases.
    auto leases_json = arguments->get("leases");
    ASSERT_TRUE(leases_json);
    ASSERT_EQ(Element::list, leases_json->getType());
    ASSERT_EQ(1, leases_json->size());
    lease_as_json = leases_json->get(0);
    EXPECT_EQ(leaseAsJson(createLease6())->str(), lease_as_json->str());

    // Make sure the backlog is now empty.
    EXPECT_EQ(0, backlog.size());
}

// This test verifies that the lease6-get-all command is correct.
TEST(CommandCreatorTest, createLease6GetAll) {
    ConstElementPtr command = CommandCreator::createLease6GetAll();
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "lease6-get-all", "dhcp6"));
}


// This test verifies that the lease6-get-page command is correct when
// first page is fetched.
TEST(CommandCreatorTest, createLease6GetPageStart) {
    Lease6Ptr lease6;
    ConstElementPtr command = CommandCreator::createLease6GetPage(lease6, 10);
    ConstElementPtr arguments;
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "lease6-get-page", "dhcp6",
                                              arguments));

    ConstElementPtr from = arguments->get("from");
    ASSERT_TRUE(from);
    EXPECT_EQ(Element::string, from->getType());
    EXPECT_EQ("start", from->stringValue());

    ConstElementPtr limit = arguments->get("limit");
    ASSERT_TRUE(limit);
    ASSERT_EQ(Element::integer, limit->getType());
    EXPECT_EQ(10, limit->intValue());
}

// This test verifies that the lease6-get-page command is correct when next
// page is fetched.
TEST(CommandCreatorTest, createLease6GetPageAddress) {
    Lease6Ptr lease6(new Lease6());
    lease6->addr_ = IOAddress("2001:db8:1::1");

    ConstElementPtr command = CommandCreator::createLease6GetPage(lease6, 15);
    ConstElementPtr arguments;
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "lease6-get-page", "dhcp6",
                                              arguments));

    ConstElementPtr from = arguments->get("from");
    ASSERT_TRUE(from);
    EXPECT_EQ(Element::string, from->getType());
    EXPECT_EQ("2001:db8:1::1", from->stringValue());

    ConstElementPtr limit = arguments->get("limit");
    ASSERT_TRUE(limit);
    ASSERT_EQ(Element::integer, limit->getType());
    EXPECT_EQ(15, limit->intValue());
}

// This test verifies that exception is thrown if limit is set to 0 while
// creating lease6-get-page command.
TEST(CommandCreatorTest, createLease6GetPageZeroLimit) {
    Lease6Ptr lease6;
    EXPECT_THROW(CommandCreator::createLease6GetPage(lease6, 0), BadValue);
}

// This test verifies that the ha-maintenance-notify command is correct
// while being sent to the DHCPv4 server.
TEST(CommandCreatorTest, createMaintenanceNotify4) {
    ConstElementPtr command = CommandCreator::createMaintenanceNotify(true, HAServerType::DHCPv4);
    ConstElementPtr arguments;
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "ha-maintenance-notify", "dhcp4",
                                              arguments));

    auto cancel = arguments->get("cancel");
    ASSERT_TRUE(cancel);
    ASSERT_EQ(Element::boolean, cancel->getType());
    EXPECT_TRUE(cancel->boolValue());
}

// This test verifies that the ha-maintenance-notify command is correct
// while being sent to the DHCPv6 server.
TEST(CommandCreatorTest, createMaintenanceNotify6) {
    ConstElementPtr command = CommandCreator::createMaintenanceNotify(false, HAServerType::DHCPv6);
    ConstElementPtr arguments;
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "ha-maintenance-notify", "dhcp6",
                                              arguments));

    auto cancel = arguments->get("cancel");
    ASSERT_TRUE(cancel);
    ASSERT_EQ(Element::boolean, cancel->getType());
    EXPECT_FALSE(cancel->boolValue());
}

// This test verifies that the ha-sync-complete-notify command sent to a
// DHCPv4 server is correct.
TEST(CommandCreatorTest, createSyncCompleteNotify4) {
    ConstElementPtr command = CommandCreator::createSyncCompleteNotify(HAServerType::DHCPv4);
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "ha-sync-complete-notify", "dhcp4"));
}

// This test verifies that the ha-sync-complete-notify command sent to a
// DHCPv4 server is correct.
TEST(CommandCreatorTest, createSyncCompleteNotify6) {
    ConstElementPtr command = CommandCreator::createSyncCompleteNotify(HAServerType::DHCPv6);
    ConstElementPtr arguments;
    ASSERT_NO_FATAL_FAILURE(testCommandBasics(command, "ha-sync-complete-notify", "dhcp6"));
}

}
