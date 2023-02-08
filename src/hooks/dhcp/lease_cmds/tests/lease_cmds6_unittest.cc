// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <hooks/hooks_manager.h>
#include <config/command_mgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/ncr_generator.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/resource_handler.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <lease_cmds_unittest.h>
#include <stats/stats_mgr.h>
#include <testutils/user_context_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>

#include <errno.h>
#include <set>

using namespace std;
using namespace isc;
using namespace isc::hooks;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp_ddns;
using namespace isc::asiolink;
using namespace isc::stats;
using namespace isc::test;

namespace {

/// @brief Class dedicated to testing v6 part of lease_cmds library.
///
/// Provides convenience methods for loading, testing all commands and
/// unloading the lease_cmds library.
class Lease6CmdsTest : public LeaseCmdsTest {
public:
    /// @brief Constructor.
    Lease6CmdsTest() {
        setFamily(AF_INET6);
    }

    /// @brief Checks if specified response contains IPv6 lease
    ///
    /// @param lease Element tree that represents a lease
    /// @param ip expected IP address (or prefix)
    /// @param prefixlen prefix length (0 = expect address)
    /// @param subnet_id expected subnet-id
    /// @param duid expected value of DUID
    /// @param hwaddr_required true if hwaddr is expected
    void checkLease6(isc::data::ConstElementPtr l, std::string ip,
                     uint8_t prefixlen,
                     uint32_t subnet_id, std::string duid,
                     bool hwaddr_required) {
        ASSERT_TRUE(l);

        // If the element is a list we need to retrieve the lease that
        // we're interested in.
        if (l->getType() == isc::data::Element::list) {
            std::vector<isc::data::ElementPtr> e = l->listValue();
            for (auto it = e.begin(); it != e.end(); ++it) {
                isc::data::ConstElementPtr ip_address = (*it)->get("ip-address");
                if (ip_address && ip_address->stringValue() == ip) {
                    l = (*it);
                    break;
                }
            }

            ASSERT_TRUE(l);
        }

        ASSERT_TRUE(l->contains("ip-address"));
        EXPECT_EQ(ip, l->get("ip-address")->stringValue());
        if (prefixlen != 0) {
            ASSERT_TRUE(l->get("prefix-len"));
            EXPECT_EQ(prefixlen, l->get("prefix-len")->intValue());
        }

        ASSERT_TRUE(l->contains("subnet-id"));
        EXPECT_EQ(subnet_id, l->get("subnet-id")->intValue());

        ASSERT_TRUE(l->contains("duid"));
        EXPECT_EQ(duid, l->get("duid")->stringValue());

        // hwaddr may or may not appear
        if (hwaddr_required) {
            EXPECT_TRUE(l->get("hwaddr"));
        }

        // Check that there are expected fields
        ASSERT_TRUE(l->contains("preferred-lft"));
        ASSERT_TRUE(l->contains("valid-lft"));
        ASSERT_TRUE(l->contains("cltt"));
        ASSERT_TRUE(l->contains("subnet-id"));
        ASSERT_TRUE(l->contains("fqdn-fwd"));
        ASSERT_TRUE(l->contains("fqdn-rev"));
        ASSERT_TRUE(l->contains("hostname"));
        ASSERT_TRUE(l->contains("state"));

        // Check that there are no v4 specific fields.
        ASSERT_FALSE(l->contains("client-id"));

        // Assuming that these values were used to create the lease.
        // If we ever want to test different values they will need to
        // be added as parameters to this function.
        EXPECT_EQ(HIGH_VALID_LIFETIME,
                  static_cast<uint32_t>(l->get("valid-lft")->intValue()));
        EXPECT_EQ(DEC_2030_TIME, l->get("cltt")->intValue());
    }

    /// @brief Check lease6 statistics.
    ///
    /// @param id Subnet id of the stats to check.
    /// @assigned_nas The expected value of assigned nas addresses in subnet.
    /// @declined The expected value of declined addresses in subnet.
    /// @assigned_pds The expected value of assigned pds addresses in subnet.
    void checkLease6Stats(isc::dhcp::SubnetID id, int32_t assigned_nas,
                          int32_t declined, int32_t assigned_pds) {
        ASSERT_EQ(isc::stats::StatsMgr::instance().getObservation(
                isc::stats::StatsMgr::generateName("subnet", id,
                          "assigned-nas"))->getInteger().first, assigned_nas);

        ASSERT_EQ(isc::stats::StatsMgr::instance().getObservation(
                isc::stats::StatsMgr::generateName("subnet", id,
                          "declined-addresses"))->getInteger().first, declined);

        ASSERT_EQ(isc::stats::StatsMgr::instance().getObservation(
                isc::stats::StatsMgr::generateName("subnet", id,
                          "assigned-pds"))->getInteger().first, assigned_pds);
    }

    /// @brief Check that lease6-add with missing parameters will fail.
    void testLease6AddMissingParams();

    /// @brief Verify that lease6-add can be rejected if parameters are
    /// specified, but have incorrect values.
    void testLease6AddBadParams();

    /// @brief Check that a simple, well formed lease6 can be added.
    void testLease6Add();

    /// @brief Check that a simple, well formed lease6 can be added.
    void testLease6AddDeclinedLeases();

    /// @brief Check that a lease6 is not added when it already exists.
    void testLease6AddExisting();

    /// @brief Check that subnet-id is optional. If not specified, Kea should
    /// select it on its own.
    void testLease6AddSubnetIdMissing();

    /// @brief Check that subnet-id is optional. If not specified, Kea should
    /// select it on its own.
    void testLease6AddSubnetIdMissingDeclinedLeases();

    /// @brief Check that subnet-id is optional. If not specified, Kea should
    /// select it on its own, but if there's no subnet for address being added,
    /// it should fail.
    void testLease6AddSubnetIdMissingBadAddr();

    /// @brief Check that the lease with negative expiration time is rejected.
    void testLease6AddNegativeExpireTime();

    /// @brief Check that the lease with negative cltt is rejected.
    void testLease6AddNegativeCltt();

    /// @brief Check that a simple, well formed prefix lease can be added.
    void testLease6AddPrefix();

    /// @brief Check that a well formed lease6 with tons of parameters can be
    /// added.
    void testLease6AddFullAddr();

    /// @brief Check that a well formed lease6 with a comment can be added.
    void testLease6AddComment();

    /// @brief Check that lease6-get can handle a situation when the query is
    /// broken (some required parameters are missing).
    void testLease6GetMissingParams();

    /// @brief Check that lease6-get sanitizes its input.
    void testLease6GetByAddrBadParam();

    /// @brief Check that lease6-get can handle a situation when the query is
    /// correctly formed, but the lease is not there.
    void testLease6GetByAddrNotFound();

    /// @brief Check that lease6-get can return a lease by address.
    void testLease6GetByAddr();

    /// @brief Check that lease6-get can return a lease by prefix.
    void testLease6GetByAddrPrefix();

    /// @bfief Check that lease6-get rejects queries by client-id.
    void testLease6GetByClientIdInvalidType();

    /// @brief Check that lease6-get can handle a situation when the query is
    /// correctly formed, but the lease is not there.
    void testLease6GetByDuidNotFound();

    /// @bfief Check that lease6-get can find a lease by duid.
    void testLease6GetByDuid();

    /// @brief Check that lease6-get-all returns all leases.
    void testLease6GetAll();

    /// @brief Check that lease6-get-all returns empty set if no leases are
    /// found.
    void testLease6GetAllNoLeases();

    /// @brief Check that lease6-get-all returns all leases for a subnet.
    void testLease6GetAllBySubnetId();

    /// @brief Check that lease6-get-all returns empty set when no leases are
    /// found.
    void testLease6GetAllBySubnetIdNoLeases();

    /// @brief Check that lease6-get-all returns leases from multiple subnets.
    void testLease6GetAllByMultipleSubnetIds();

    /// @brief Check that lease6-get-all checks its input arguments.
    void testLease6GetBySubnetIdInvalidArguments();

    /// @brief Check that multiple calls to lease6-get-page return all leases.
    void testLease6GetPaged();

    /// @brief Verifies that first page of IPv6 leases can be retrieved by
    /// specifying zero IPv6 address.
    void testLease6GetPagedZeroAddress();

    /// @brief Verifies that IPv4 address as a start address is rejected.
    void testLease6GetPagedIPv4Address();

    /// @brief Verifies that value of 'from' parameter other than 'start' or an
    /// IPv6 address is rejected.
    void testLease6GetPagedInvalidFrom();

    /// @brief Verifies that limit is mandatory.
    void testLease6GetPagedNoLimit();

    /// @brief Verifies that the limit must be a number.
    void testLease6GetPagedLimitNotNumber();

    /// @brief Verifies that the limit of 0 is rejected.
    void testLease6GetPagedLimitIsZero();

    /// @brief Check that lease6-get-by-duid can handle a situation when the
    /// query is broken (required parameter is missing).
    void testLease6GetByDuidParams();

    /// @brief Check that lease6-get-by-duid works as expected (find no lease).
    void testLease6GetByDuidFind0();

    /// @brief Check that lease6-get-by-duid works as expected (find two
    /// leases).
    void testLease6GetByDuidFind2();

    /// @brief Check that lease6-get-by-hostname can handle a situation when
    /// the query is broken (required parameter is missing).
    void testLease6GetByHostnameParams();

    /// @brief Check that lease6-get-by-hostname works as expected (find no
    /// lease).
    void testLease6GetByHostnameFind0();

    /// @brief Check that lease6-get-by-hostname works as expected (find two
    /// leases).
    void testLease6GetByHostnameFind2();

    /// @brief Test checks if lease6-update handler refuses calls with missing
    /// parameters.
    void testLease6UpdateMissingParams();

    /// @brief Verify that lease6-update can be rejected if parameters are
    /// specified, but have incorrect values.
    void testLease6UpdateBadParams();

    /// @brief Check that lease6-update correctly handles case when there is no
    /// lease to be updated.
    void testLease6UpdateNoLease();

    /// @brief Check that a lease6 can be updated. We're changing hw-address,
    /// hostname and extended info.
    void testLease6UpdateExtendedInfo();

    /// @brief Check that a lease6 can be updated. We're changing hw-address and
    /// a hostname.
    void testLease6Update();

    /// @brief Check that a lease6 can be updated. We're changing hw-address and
    /// a hostname.
    void testLease6UpdateDeclinedLeases();

    /// @brief Check that a lease6 can be updated. We're changing hw-address and
    /// a hostname. The subnet-id is not specified.
    void testLease6UpdateNoSubnetId();

    /// @brief Check that a lease6 can be updated. We're changing hw-address and
    /// a hostname. The subnet-id is not specified.
    void testLease6UpdateNoSubnetIdDeclinedLeases();

    /// @brief Check that a lease6 is created if it doesn't exist during the
    /// update. To trigger this behavior 'force-create' boolean parameter must
    /// be included in the command.
    void testLease6UpdateForceCreate();

    /// @brief Check that a lease6 is created if it doesn't exist during the
    /// update. To trigger this behavior 'force-create' boolean parameter must
    /// be included in the command. The subnet-id is not specified, Kea will
    /// figure it out.
    void testLease6UpdateForceCreateNoSubnetId();

    /// @brief Check that lease6-update correctly handles case when the
    /// 'force-create' parameter is explicitly set to false.
    void testLease6UpdateDoNotForceCreate();

    /// @brief Check that a lease6 can be updated. We're adding a comment and an
    /// user context.
    void testLease6UpdateComment();

    /// @brief Check that lease6-del can handle a situation when the query is
    /// broken (some required parameters are missing).
    void testLease6DelMissingParams();

    /// @brief Check that lease6-del(subnet-id, addr6) can handle a situation
    /// when the query is correctly formed, but the lease is not there.
    void testLease6DelByAddrNotFound();

    /// @brief Check that lease6-del sanitizes its input.
    void testLease6DelByAddrBadParam();

    /// @brief Check that lease6-del(subnet-id, addr6) can handle a situation
    /// when the query is correctly formed and the lease is deleted.
    void testLease6DelByAddr();

    /// @brief Check that lease6-del(subnet-id, addr6) can handle a situation
    /// when the query is correctly formed and the lease is deleted.
    void testLease6DelByAddrDeclinedLeases();

    /// @brief Check that lease6-del(type, addr6) can handle a
    /// situation when the query is correctly formed and the lease is deleted.
    void testLease6DelByAddrPrefix();

    /// @brief Check that lease6-del(subnet-id, addr) can handle a situation
    /// when the query is correctly formed, but the lease is not there.
    void testLease6DelByDuidNotFound();

    /// @brief Check that lease6-del(subnet-id, iaid, identifier-type,
    /// identifier) can find and delete a lease by duid.
    void testLease6DelByDuid();

    /// @brief Check that lease6-wipe can remove leases.
    void testLease6Wipe();

    /// @brief Check that lease6-wipe can remove leases from all subnets at
    /// once.
    void testLease6WipeAll();

    /// @brief Check that lease6-wipe can remove leases from all subnets at
    /// once (when no parameters are specified).
    void testLease6WipeAllNoArgs();

    /// @brief Check that lease6-wipe properly reports when no leases were
    /// deleted.
    void testLease6WipeNoLeases();

    /// @brief Check that lease6-wipe properly reports when no leases were
    /// deleted.
    void testLease6WipeNoLeasesAll();

    /// @brief Check that an attempt to update a lease (set incorrect
    /// subnet-id) will fail.
    void testLease6BrokenUpdate();

    /// @brief This test verifies that it is possible to add two leases and
    /// delete two leases as a result of the single lease6-bulk-apply command.
    void testLease6BulkApply();

    /// @brief This test verifies that the lease parameters are checked when
    /// adding new leases only with the lease6-bulk-apply.
    void testLease6BulkApplyAddsOnlyBadParam();

    /// @brief This test verifies that it is possible to send new leases only
    /// with the lease6-bulk-apply.
    void testLease6BulkApplyAddsOnly();

    /// @brief This test verifies that the lease parameters are checked when
    /// updating leases only with the lease6-bulk-apply.
    void testLease6BulkApplyUpdatesOnlyBadParam();

    /// @brief This test verifies that it is possible to update leases with the
    /// lease6-bulk-apply.
    void testLease6BulkApplyUpdatesOnly();

    /// @brief This test verifies that it is possible to update leases with
    /// extended info with the lease6-bulk-apply.
    void testLease6BulkApplyUpdatesOnlyExtendedInfo();

    /// @brief This test verifies that it is possible to only delete leases with
    /// the lease6-bulk-apply.
    void testLease6BulkApplyDeletesOnly();

    /// @brief This test verifies that deleting non existing leases returns an
    /// 'empty' result.
    void testLease6BulkApplyDeleteNonExiting();

    /// @brief Check that changes for other leases are not applied if one of the
    /// leases is malformed.
    void testLease6BulkApplyRollback();

    /// @brief Check that lease6-resend-ddns sanitizes its input.
    void testLease6ResendDdnsBadParam();

    /// @brief Check that lease6-resend-ddns does not generate an NCR for given
    /// lease when DDNS updating is disabled.
    void testLease6ResendDdnsDisabled();

    /// @brief Check that lease6-resend-ddns does not generate an NCR for when
    /// there is no matching lease.
    void testLease6ResendDdnsNoLease();

    /// @brief Check that lease6-resend-ddns does not generate an NCR for given
    /// lease when updates are enabled but Lease::hostname_ is blank.
    void testLease6ResendNoHostname();

    /// @brief Check that lease6-resend-ddns does not generate an NCR for given
    /// lease when updates are enabled, Lease::hostname_ is not blank, but both
    /// Lease::fqdn_fwd_ and fdqn_rev_ are false.
    void testLease6ResendNoDirectionsEnabled();

    /// @brief Check that lease6-resend-ddns can generate an NCR for given
    /// lease when updates are enabled, Lease::hostname_ is not blank, and at
    /// least one of Lease::fqdn_fwd_ or fdqn_rev_ are true.
    void testLease6ResendDdnsEnabled();

    /// @brief Check that lease6-del does (or does not) generate an NCR to
    /// remove DNS for a given lease based on lease content when DDNS updates
    /// are enabled.
    void testLease6DnsRemoveD2Enabled();

    /// @brief Check that lease6-del does not generate an NCR to remove DNS for
    /// a given lease based on lease content when DDNS updates are disabled.
    void testLease6DnsRemoveD2Disabled();

    /// @brief Verify that v6 lease add handles conflict as expected.
    void testLease6ConflictingAdd();

    /// @brief Verify that v6 lease update handles conflict as expected.
    void testLease6ConflictingUpdate();

    /// @brief Verify that v6 lease bulk update handles conflict as expected.
    void testLease6ConflictingBulkApplyAdd();

    /// @brief Check that lease6-write works as expected.
    void testLease6Write();
};

void Lease6CmdsTest::testLease6AddMissingParams() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Everything missing. What sort of nonsense is that?
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just ip is not enough (subnet-id and duid missing, but subnet-id
    // can now be figured out by kea)
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::3\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'duid' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just subnet-id and ip is not enough (duid missing).
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::3\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'duid' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just subnet-id and duid is not enough (ip, iaid missing).
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just subnet-id, duid and iaid is not enough (ip missing).
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Close, but no cigars. Still missing iaid.
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"ip-address\": \"2001:db8:1::3\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'iaid' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6AddBadParams() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // All params are there, but there's no subnet-id 123 configured.
    // (initLeaseMgr initialized subnet-id 44 for v4 and subnet-id 66 for v6).
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "Invalid subnet-id: No IPv6 subnet with subnet-id=123 currently configured.";
    testCommand(txt, CONTROL_RESULT_CONFLICT, exp_rsp);

    // This time the IP address does not belong to the subnet.
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"3000::3\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "The address 3000::3 does not belong to subnet 2001:db8:1::/48, subnet-id=66";
    testCommand(txt, CONTROL_RESULT_CONFLICT, exp_rsp);

    // v4? You're a time traveler from early 80s or what?
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "Non-IPv6 address specified: 192.0.2.1";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Invalid state: the only supported values are 0,1,2.
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n,"
        "        \"state\": 123\n"
        "    }\n"
        "}";
    exp_rsp = "Invalid state value: 123, supported values are: 0 (default), 1 "
        "(declined) and 2 (expired-reclaimed)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Bad user context: not a map.
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n,"
        "        \"user-context\": \"bad value\"\n"
        "    }\n"
        "}";
    exp_rsp = "Invalid user context '\"bad value\"' is not a JSON map.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Duplicated comment.
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n,"
        "        \"user-context\": { \"comment\": \"in user context\" },\n"
        "        \"comment\": \"direct\"\n"
        "    }\n"
        "}";
    exp_rsp = "Duplicated comment entry '\"direct\"' in user context "
        "'{ \"comment\": \"in user context\" }'";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Negative expiration time.
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n,"
        "        \"user-context\": { \"comment\": \"in user context\" },\n"
        "        \"expire\": -6218189367\n"
        "    }\n"
        "}";
    exp_rsp = "expiration time must be positive for address 2001:db8:1::1";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Negative cltt
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n,"
        "        \"user-context\": { \"comment\": \"in user context\" },\n"
        "        \"expire\": 123456,\n"
        "        \"valid-lft\": 123457"
        "    }\n"
        "}";
    exp_rsp = "expiration time must be greater than valid lifetime for address "
        "2001:db8:1::1";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Invalid declined state (1) for PD prefix.
    txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"prefix-len\": 48,\n"
        "        \"type\": \"IA_PD\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234,\n"
        "        \"state\": 1"
        "    }\n"
        "}";
    exp_rsp = "Invalid declined state for PD prefix.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6Add() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 2001:db8:1::3, subnet-id 66 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(l);
    EXPECT_EQ("", l->hostname_);
    EXPECT_FALSE(l->getContext());

    // Test execution is fast. The cltt should be set to now. In some rare
    // cases we could have the seconds counter to tick, so having a value off
    // by one is ok.
    EXPECT_LE(abs(l->cltt_ - time(NULL)), 1);
    EXPECT_EQ(0, l->state_);
}

void Lease6CmdsTest::testLease6AddDeclinedLeases() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"state\": 1,\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 2001:db8:1::3, subnet-id 66 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 1, 1, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(l);
    EXPECT_EQ("", l->hostname_);
    EXPECT_FALSE(l->getContext());

    // Test execution is fast. The cltt should be set to now. In some rare
    // cases we could have the seconds counter to tick, so having a value off
    // by one is ok.
    EXPECT_LE(abs(l->cltt_ - time(NULL)), 1);
    EXPECT_EQ(1, l->state_);
}

void Lease6CmdsTest::testLease6AddExisting() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease already exists.";
    testCommand(txt, CONTROL_RESULT_CONFLICT, exp_rsp);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);
}

void Lease6CmdsTest::testLease6AddSubnetIdMissing() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command (without subnet-id)
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 2001:db8:1::3, subnet-id 66 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease is really there and has correct subnet-id.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(l);
    EXPECT_EQ(66, l->subnet_id_);
}

void Lease6CmdsTest::testLease6AddSubnetIdMissingDeclinedLeases() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command (without subnet-id)
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"state\": 1,\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 2001:db8:1::3, subnet-id 66 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 1, 1, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease is really there and has correct subnet-id.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(l);
    EXPECT_EQ(66, l->subnet_id_);
}

void Lease6CmdsTest::testLease6AddSubnetIdMissingBadAddr() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command (without subnet-id)
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:ffff::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "subnet-id not specified and failed to find a subnet for "
                     "address 2001:ffff::1";
    testCommand(txt, CONTROL_RESULT_CONFLICT, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease was not added.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:ffff::1"));
    ASSERT_FALSE(l);
}

void Lease6CmdsTest::testLease6AddNegativeExpireTime() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Add a lease with negative expiration time.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234,\n"
        "        \"expire\": -6218189367\n"
        "    }\n"
        "}";
    string exp_rsp = "expiration time must be positive for address 2001:db8:1::3";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease was not added.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_FALSE(l);
}

void Lease6CmdsTest::testLease6AddNegativeCltt() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Add a lease with negative cltt (expiration time - valid lifetime)
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"expire\": 123456,\n"
        "        \"iaid\": 1234,\n"
        "        \"valid-lft\": 123457"
        "    }\n"
        "}";
    string exp_rsp = "expiration time must be greater than valid lifetime for "
        "address 2001:db8:1::3";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease was not added.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_FALSE(l);
}

void Lease6CmdsTest::testLease6AddPrefix() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:abcd::\",\n"
        "        \"prefix-len\": 48,\n"
        "        \"type\": \"IA_PD\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for prefix 2001:db8:abcd::/48, subnet-id 66 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 0, 0, 1);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_PD, IOAddress("2001:db8:abcd::"));
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::TYPE_PD, l->type_);
    EXPECT_EQ(48, l->prefixlen_);
    EXPECT_EQ("", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

void Lease6CmdsTest::testLease6AddFullAddr() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"duid\": \"01:02:03:04:05:06:07:08\",\n"
        "        \"iaid\": 1234,\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"preferred-lft\": 500,\n"
        "        \"valid-lft\": 1000,\n"
        "        \"expire\": 6218189367,\n"
        "        \"fqdn-fwd\": true,\n"
        "        \"fqdn-rev\": true,\n"
        "        \"hostname\": \"urania.example.org\",\n"
        "        \"user-context\": { \"foobar\": true }\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 2001:db8:1::3, subnet-id 66 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(l);
    EXPECT_EQ(Lease::TYPE_NA, l->type_);
    EXPECT_EQ("2001:db8:1::3", l->addr_.toText());
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    ASSERT_TRUE(l->duid_);
    EXPECT_EQ("01:02:03:04:05:06:07:08", l->duid_->toText());
    // expire (6218189367) - valid_lft(1000)
    EXPECT_EQ(static_cast<time_t>(6218189367 - 1000), l->cltt_);
    EXPECT_EQ(true, l->fqdn_fwd_);
    EXPECT_EQ(true, l->fqdn_rev_);
    EXPECT_EQ("urania.example.org", l->hostname_);
    ASSERT_TRUE(l->getContext());
    EXPECT_EQ("{ \"foobar\": true }", l->getContext()->str());
}

void Lease6CmdsTest::testLease6AddComment() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::3\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234,\n"
        "        \"comment\": \"a comment\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 2001:db8:1::3, subnet-id 66 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::3"));
    ASSERT_TRUE(l);

    // Make sure the lease have proper value set.
    ASSERT_TRUE(l->getContext());
    EXPECT_EQ("{ \"comment\": \"a comment\" }", l->getContext()->str());
}

void Lease6CmdsTest::testLease6GetByAddrNotFound() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"ip-address\": \"2001:db8:1::10\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease not found.";

    // Note the status expected is empty. The query completed correctly,
    // just didn't found the lease.
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

void Lease6CmdsTest::testLease6GetByClientIdInvalidType() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // client-id query is allowed in v4 only.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"client-id\","
        "        \"identifier\": \"01:02:03:04\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "Query by client-id is not allowed in v6.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6GetByDuidNotFound() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"identifier-type\": \"duid\","
        "        \"identifier\": \"00:01:02:03:04:05:06:07\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease not found.";

    // Note the status expected is empty. The query completed correctly,
    // just didn't found the lease.
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

void Lease6CmdsTest::testLease6GetByAddr() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"2001:db8:1::1\"\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease found.";

    // The status expected is success. The lease should be returned.
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);

    ConstElementPtr lease = rsp->get("arguments");
    ASSERT_TRUE(lease);

    // Now check that the lease was indeed returned.
    checkLease6(lease, "2001:db8:1::1", 0, 66, "42:42:42:42:42:42:42:42", false);
}

void Lease6CmdsTest::testLease6GetMissingParams() {
    // No parameters whatsoever. You want just a lease, any lease?
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Just the subnet-id won't cut it, either.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // We can't identify your laptop by color. Sorry, buddy.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"color\",\n"
        "        \"identifier\": \"blue\"\n"
        "    }\n"
        "}";
    exp_rsp = "Incorrect identifier type: color, the only supported values are: "
        "address, hw-address, duid";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Query by hw-address is not supported in v6. Sorry.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"hw-address\",\n"
        "        \"identifier\": \"01:01:01:01:01:01\"\n"
        "    }\n"
        "}";
    exp_rsp = "Query by hw-address is not allowed in v6.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Identifier value is missing.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"duid\"\n"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Identifier-type is missing.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier\": \"01:02:03:04:05\"\n"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6GetByAddrBadParam() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Invalid family
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\""
        "    }\n"
        "}";
    string exp_rsp = "Invalid IPv6 address specified: 192.0.2.1";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // This is way off
    cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"221B Baker St.\""
        "    }\n"
        "}";
    exp_rsp = "Failed to convert string to address '221B Baker St.': Invalid argument";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6GetByAddrPrefix() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // We need to get a prefix lease. We need to create it by hand.
    // Let's start with regular address lease and make it a prefix lease.
    Lease6Ptr l = createLease6("2001:db8:1::1", 66, 0x77);
    l->addr_ = IOAddress("2001:db8:1234:ab::");
    l->type_ = Lease::TYPE_PD;
    l->prefixlen_ = 56;
    lmptr_->addLease(l);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"type\": \"IA_PD\","
        "        \"ip-address\": \"2001:db8:1234:ab::\""
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease found.";

    // The status expected is success. The lease should be returned.
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);

    ConstElementPtr lease = rsp->get("arguments");
    ASSERT_TRUE(lease);

    // Now check that the lease was indeed returned.
    checkLease6(lease, "2001:db8:1234:ab::", 56, 66, "77:77:77:77:77:77:77:77", false);
}

void Lease6CmdsTest::testLease6GetByDuid() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"iaid\": 42,"
        "        \"identifier-type\": \"duid\","
        "        \"identifier\": \"42:42:42:42:42:42:42:42\"\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease found.";

    // The status expected is success. The lease should be returned.
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
    ASSERT_TRUE(rsp);

    ConstElementPtr lease = rsp->get("arguments");
    ASSERT_TRUE(lease);

    // Now check that the lease was indeed returned.
    checkLease6(lease, "2001:db8:1::1", 0, 66, "42:42:42:42:42:42:42:42", false);
}

void Lease6CmdsTest::testLease6GetAll() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Query for all leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\"\n"
        "}";
    string exp_rsp = "4 IPv6 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);

    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    ConstElementPtr leases = args->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());

    // Let's check if the response contains desired leases.
    checkLease6(leases, "2001:db8:1::1", 0, 66, "42:42:42:42:42:42:42:42", false);
    checkLease6(leases, "2001:db8:1::2", 0, 66, "56:56:56:56:56:56:56:56", false);
    checkLease6(leases, "2001:db8:2::1", 0, 99, "42:42:42:42:42:42:42:42", false);
    checkLease6(leases, "2001:db8:2::2", 0, 99, "56:56:56:56:56:56:56:56", false);
}

void Lease6CmdsTest::testLease6GetAllNoLeases() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Query for all leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\"\n"
        "}";
    string exp_rsp = "0 IPv6 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);

    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    ConstElementPtr leases = args->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());

    EXPECT_EQ(0, leases->size());
}

void Lease6CmdsTest::testLease6GetAllBySubnetId() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Query for leases from subnet 66. Subnet 127 will be ignored because
    // it doesn't contain any leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\",\n"
        "    \"arguments\": {\n"
        "        \"subnets\": [ 66, 127 ]"
        "    }\n"
        "}";
    string exp_rsp = "2 IPv6 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);

    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    ConstElementPtr leases = args->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());

    // Let's check if the response contains desired leases.
    checkLease6(leases, "2001:db8:1::1", 0, 66, "42:42:42:42:42:42:42:42", false);
    checkLease6(leases, "2001:db8:1::2", 0, 66, "56:56:56:56:56:56:56:56", false);
}

void Lease6CmdsTest::testLease6GetAllBySubnetIdNoLeases() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Query for leases from subnet 66. Subnet 127 will be ignored because
    // it doesn't contain any leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\",\n"
        "    \"arguments\": {\n"
        "        \"subnets\": [ 66, 127 ]"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv6 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);

    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    ConstElementPtr leases = args->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());

    EXPECT_EQ(0, leases->size());
}

void Lease6CmdsTest::testLease6GetAllByMultipleSubnetIds() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Query for leases from subnet 66 and 99.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\",\n"
        "    \"arguments\": {\n"
        "        \"subnets\": [ 66, 99 ]"
        "    }\n"
        "}";
    string exp_rsp = "4 IPv6 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);

    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    ConstElementPtr leases = args->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());

    // Let's check if the response contains desired leases.
    checkLease6(leases, "2001:db8:1::1", 0, 66, "42:42:42:42:42:42:42:42", false);
    checkLease6(leases, "2001:db8:1::2", 0, 66, "56:56:56:56:56:56:56:56", false);
    checkLease6(leases, "2001:db8:2::1", 0, 99, "42:42:42:42:42:42:42:42", false);
    checkLease6(leases, "2001:db8:2::2", 0, 99, "56:56:56:56:56:56:56:56", false);
}

void Lease6CmdsTest::testLease6GetBySubnetIdInvalidArguments() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Subnets not specified in arguments.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\",\n"
        "    \"arguments\": {"
        "        \"foo\": 1\n"
        "    }\n"
        "}";
    string exp_rsp = "'subnets' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Subnets are not a list.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnets\": 1\n"
        "    }\n"
        "}";
    exp_rsp = "'subnets' parameter must be a list";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Subnets list must contain numbers.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnets\": [ \"x\", \"y\" ]\n"
        "    }\n"
        "}";
    exp_rsp = "listed subnet identifiers must be numbers";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6GetPaged() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Gather all returned addresses to verify that all were returned.
    std::set<std::string> lease_addresses;

    // Keyword start indicates that we want to retrieve the first page.
    std::string last_address = "start";

    // There are 4 leases in the database, so the first two pages should
    // include leases and the 3 page should be empty.
    for (auto i = 0; i < 3; ++i) {
        // Query for a page of leases.
        string cmd =
            "{\n"
            "    \"command\": \"lease6-get-page\",\n"
            "    \"arguments\": {"
            "        \"from\": \"" + last_address + "\","
            "        \"limit\": 2"
            "    }"
            "}";

        // For the first two pages we should get success. For the last
        // one an empty status code.
        ConstElementPtr rsp;
        if (i < 2) {
            string exp_rsp = "2 IPv6 lease(s) found.";
            rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

        } else {
            string exp_rsp = "0 IPv6 lease(s) found.";
            rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

        }

        // Now check that the lease parameters were indeed returned.
        ASSERT_TRUE(rsp);

        // Arguments must exist.
        ConstElementPtr args = rsp->get("arguments");
        ASSERT_TRUE(args);
        ASSERT_EQ(Element::map, args->getType());

        // For convenience, we return the number of returned leases,
        // so as the client can check whether there was anything returned
        // before parsing the leases structure.
        ConstElementPtr page_count = args->get("count");
        ASSERT_TRUE(page_count);
        ASSERT_EQ(Element::integer, page_count->getType());

        // leases must exist, but may be empty.
        ConstElementPtr leases = args->get("leases");
        ASSERT_TRUE(leases);
        ASSERT_EQ(Element::list, leases->getType());

        if (!leases->empty()) {
            EXPECT_EQ(2, page_count->intValue());

            // Go over each lease and verify its correctness.
            for (ConstElementPtr lease : leases->listValue()) {
                ASSERT_EQ(Element::map, lease->getType());
                ASSERT_TRUE(lease->contains("ip-address"));
                ConstElementPtr ip_address = lease->get("ip-address");
                ASSERT_EQ(Element::string, ip_address->getType());
                last_address = ip_address->stringValue();

                lease_addresses.insert(last_address);

                // The easiest way to retrieve the subnet id and HW address is to
                // ask the Lease Manager.
                Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                                           IOAddress(last_address));
                ASSERT_TRUE(from_mgr);
                checkLease6(leases, last_address, 0, from_mgr->subnet_id_,
                            from_mgr->duid_->toText(), false);
            }

        } else {
            // In the third iteration the page should be empty.
            EXPECT_EQ(0, page_count->intValue());
        }
    }

    // Check if all addresses were returned.
    EXPECT_EQ(1, lease_addresses.count("2001:db8:1::1"));
    EXPECT_EQ(1, lease_addresses.count("2001:db8:1::2"));
    EXPECT_EQ(1, lease_addresses.count("2001:db8:2::1"));
    EXPECT_EQ(1, lease_addresses.count("2001:db8:2::2"));
}

void Lease6CmdsTest::testLease6GetPagedZeroAddress() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"::\","
        "        \"limit\": 2"
        "    }"
        "}";

    string exp_rsp = "2 IPv6 lease(s) found.";
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

void Lease6CmdsTest::testLease6GetPagedIPv4Address() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"192.0.2.3\","
        "        \"limit\": 2"
        "    }"
        "}";

    string exp_rsp = "'from' parameter value 192.0.2.3 is not an IPv6 address";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6GetPagedInvalidFrom() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"foo\","
        "        \"limit\": 2"
        "    }"
        "}";

    string exp_rsp = "'from' parameter value is neither 'start' keyword "
        "nor a valid IPv6 address";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6GetPagedNoLimit() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"start\""
        "    }"
        "}";

    string exp_rsp = "'limit' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6GetPagedLimitNotNumber() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"start\","
        "        \"limit\": false"
        "    }"
        "}";

    string exp_rsp = "'limit' parameter must be a number";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6GetPagedLimitIsZero() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"start\","
        "        \"limit\": 0"
        "    }"
        "}";

    string exp_rsp = "page size of retrieved leases must not be 0";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6GetByDuidParams() {
    // No parameters whatsoever.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-duid\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "'duid' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // duid must be a string.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-duid\",\n"
        "    \"arguments\": {"
        "        \"duid\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "'duid' parameter must be a string";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Simply bad value.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-duid\",\n"
        "    \"arguments\": {"
        "        \"duid\": \"00::01:00:bc:0d:67\"\n"
        "    }\n"
        "}";
    exp_rsp = "two consecutive separators (':') specified in a decoded string";
    exp_rsp += " '00::01:00:bc:0d:67'";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6GetByDuidFind0() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // No such lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-duid\",\n"
        "    \"arguments\": {"
        "        \"duid\": \"00:01:02:03:04:05:06:07\"\n"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv6 lease(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

void Lease6CmdsTest::testLease6GetByDuidFind2() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Get the lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-duid\",\n"
        "    \"arguments\": {"
        "        \"duid\": \"42:42:42:42:42:42:42:42\"\n"
        "    }\n"
        "}";
    string exp_rsp = "2 IPv6 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr map = rsp->get("arguments");
    ASSERT_TRUE(map);
    ASSERT_EQ(Element::map, map->getType());
    ConstElementPtr leases = map->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());
    ASSERT_EQ(2, leases->size());

    // Let's check if the response makes any sense.
    ConstElementPtr lease = leases->get(0);
    ASSERT_TRUE(lease);
    checkLease6(lease, "2001:db8:1::1", 0, 66, "42:42:42:42:42:42:42:42", false);
    lease = leases->get(1);
    ASSERT_TRUE(lease);
    checkLease6(lease, "2001:db8:2::1", 0, 99, "42:42:42:42:42:42:42:42", false);
}

void Lease6CmdsTest::testLease6GetByHostnameParams() {
    // No parameters whatsoever.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-hostname\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "'hostname' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // hostname must be a string.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "'hostname' parameter must be a string";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // hostname must be not empty.
    cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"\"\n"
        "    }\n"
        "}";
    exp_rsp = "'hostname' parameter is empty";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6GetByHostnameFind0() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // No such lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"foo.bar\"\n"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv6 lease(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

void Lease6CmdsTest::testLease6GetByHostnameFind2() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Get the lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"Myhost.Example.Com.\"\n"
        "    }\n"
        "}";
    string exp_rsp = "4 IPv6 lease(s) found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr map = rsp->get("arguments");
    ASSERT_TRUE(map);
    ASSERT_EQ(Element::map, map->getType());
    ConstElementPtr leases = map->get("leases");
    ASSERT_TRUE(leases);
    ASSERT_EQ(Element::list, leases->getType());
    ASSERT_EQ(4, leases->size());

    // Let's check if the response makes any sense.
    ConstElementPtr lease = leases->get(0);
    ASSERT_TRUE(lease);
    checkLease6(lease, "2001:db8:1::1", 0, 66, "42:42:42:42:42:42:42:42", false);
    lease = leases->get(2);
    ASSERT_TRUE(lease);
    checkLease6(lease, "2001:db8:2::1", 0, 99, "42:42:42:42:42:42:42:42", false);
}

void Lease6CmdsTest::testLease6UpdateMissingParams() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Everything missing. What sort of crap is that?
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just ip is not enough (subnet-id and duid missing, although
    // kea should be able to figure out the subnet-id on its own.
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "            \"ip-address\": \"2001:db8:1::1\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'duid' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Better, but still no luck. (duid missing).
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "            \"subnet-id\": 66,\n"
        "            \"ip-address\": \"2001:db8:1::1\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'duid' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // ip-address and identifier-type missing.
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "            \"subnet-id\": 66,\n"
        "            \"duid\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just subnet-id, duid and iaid is not enough (ip missing).
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Close, but no cigars. Still missing iaid.
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"ip-address\": \"2001:db8:1::1\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'iaid' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6UpdateBadParams() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // All params are there, but there's no subnet-id 123 configured.
    // (initLeaseMgr initialized subnet-id 44 for v4 and subnet-id 66 for v6).
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Invalid subnet-id: No IPv6 subnet with subnet-id=123 currently configured.";
    testCommand(txt, CONTROL_RESULT_CONFLICT, exp_rsp);

    // This time the new IP address does not belong to the subnet.
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"3000::1\",\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\"\n"
        "    }\n"
        "}";
    exp_rsp = "The address 3000::1 does not belong to subnet 2001:db8:1::/48, subnet-id=66";
    testCommand(txt, CONTROL_RESULT_CONFLICT, exp_rsp);

    // Nope, can't do v4 address in v6 lease.
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\"\n"
        "    }\n"
        "}";
    exp_rsp = "Non-IPv6 address specified: 192.0.2.1";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Bad user context: not a map.
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n,"
        "        \"user-context\": \"bad value\"\n"
        "    }\n"
        "}";
    exp_rsp = "Invalid user context '\"bad value\"' is not a JSON map.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Duplicated comment.
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234\n,"
        "        \"user-context\": { \"comment\": \"in user context\" },\n"
        "        \"comment\": \"direct\"\n"
        "    }\n"
        "}";
    exp_rsp = "Duplicated comment entry '\"direct\"' in user context "
        "'{ \"comment\": \"in user context\" }'";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Invalid declined state (1) for PD prefix.
    txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"prefix-len\": 48,\n"
        "        \"type\": \"IA_PD\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234,\n"
        "        \"state\": 1"
        "    }\n"
        "}";
    exp_rsp = "Invalid declined state for PD prefix.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6Update() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 7654321,\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(l);

    // Make sure the lease has been updated.
    ASSERT_TRUE(l->duid_);
    EXPECT_EQ("88:88:88:88:88:88:88:88", l->duid_->toText());
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_EQ(7654321, l->iaid_);
    EXPECT_FALSE(l->getContext());
}

void Lease6CmdsTest::testLease6UpdateExtendedInfo() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    Lease6Collection leases;
    vector<uint8_t> remote_id = { 1, 2, 3, 4, 5, 6 };
    leases = lmptr_->getLeases6ByRemoteId(remote_id,
                                          IOAddress::IPV6_ZERO_ADDRESS(),
                                          0,
                                          IOAddress::IPV6_ZERO_ADDRESS(),
                                          LeasePageSize(10));
    EXPECT_TRUE(leases.empty());
    vector<uint8_t> relay_bin(8, 0x64);
    DuidPtr relay_id(new DUID(relay_bin));
    leases = lmptr_->getLeases6ByRelayId(*relay_id,
                                         IOAddress::IPV6_ZERO_ADDRESS(),
                                         0,
                                         IOAddress::IPV6_ZERO_ADDRESS(),
                                         LeasePageSize(10));
    EXPECT_TRUE(leases.empty());

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 7654321,\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\",\n"
        "        \"hostname\": \"newhostname.example.org\",\n"
        "        \"user-context\": { \"ISC\": { \"relay-info\": [ {\n"
        "          \"remote-id\": \"010203040506\",\n"
        "          \"relay-id\": \"6464646464646464\" } ] } }\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(l);

    // Make sure the lease has been updated.
    ASSERT_TRUE(l->duid_);
    EXPECT_EQ("88:88:88:88:88:88:88:88", l->duid_->toText());
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_EQ(7654321, l->iaid_);

    // Check the user context / extended info too.
    ConstElementPtr ctx = l->getContext();
    ASSERT_TRUE(ctx);
    string expected = "{ \"ISC\": { \"relay-info\": ";
    expected += "[ { \"relay-id\": \"6464646464646464\", ";
    expected += "\"remote-id\": \"010203040506\" } ] } }";
    EXPECT_EQ(expected, ctx->str());

    // Check that BLQ tables were updated.
    leases = lmptr_->getLeases6ByRemoteId(remote_id,
                                          IOAddress::IPV6_ZERO_ADDRESS(),
                                          0,
                                          IOAddress::IPV6_ZERO_ADDRESS(),
                                          LeasePageSize(10));
    // The lease must be retrieved from the remote id table.
    ASSERT_EQ(1, leases.size());
    Lease6Ptr lx = leases[0];
    ASSERT_TRUE(lx);
    EXPECT_EQ(IOAddress("2001:db8:1::1"), lx->addr_);
    EXPECT_EQ(*l, *lx);

    // The lease must be retrieved from the relay id table.
    leases = lmptr_->getLeases6ByRelayId(*relay_id,
                                         IOAddress::IPV6_ZERO_ADDRESS(),
                                         0,
                                         IOAddress::IPV6_ZERO_ADDRESS(),
                                         LeasePageSize(10));
    ASSERT_EQ(1, leases.size());
    lx = leases[0];
    ASSERT_TRUE(lx);
    EXPECT_EQ(IOAddress("2001:db8:1::1"), lx->addr_);
    EXPECT_EQ(*l, *lx);
}

void Lease6CmdsTest::testLease6UpdateDeclinedLeases() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true, true);

    checkLease6Stats(66, 2, 2, 0);

    checkLease6Stats(99, 2, 2, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 7654321,\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 2, 1, 0);

    checkLease6Stats(99, 2, 2, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(l);

    // Make sure the lease has been updated.
    ASSERT_TRUE(l->duid_);
    EXPECT_EQ("88:88:88:88:88:88:88:88", l->duid_->toText());
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_EQ(7654321, l->iaid_);
    EXPECT_FALSE(l->getContext());
}

void Lease6CmdsTest::testLease6UpdateNoSubnetId() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 7654321,\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(l);

    // Make sure the subnet-id is correct.
    EXPECT_EQ(66, l->subnet_id_);

    // Make sure the lease has been updated.
    ASSERT_TRUE(l->duid_);
    EXPECT_EQ("88:88:88:88:88:88:88:88", l->duid_->toText());
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_EQ(7654321, l->iaid_);
    EXPECT_FALSE(l->getContext());
}

void Lease6CmdsTest::testLease6UpdateNoSubnetIdDeclinedLeases() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true, true);

    checkLease6Stats(66, 2, 2, 0);

    checkLease6Stats(99, 2, 2, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 7654321,\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 2, 1, 0);

    checkLease6Stats(99, 2, 2, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(l);

    // Make sure the subnet-id is correct.
    EXPECT_EQ(66, l->subnet_id_);

    // Make sure the lease has been updated.
    ASSERT_TRUE(l->duid_);
    EXPECT_EQ("88:88:88:88:88:88:88:88", l->duid_->toText());
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_EQ(7654321, l->iaid_);
    EXPECT_FALSE(l->getContext());
}

void Lease6CmdsTest::testLease6UpdateComment() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 42,\n"
        "        \"duid\": \"42:42:42:42:42:42:42:42\",\n"
        "        \"comment\": \"a comment\",\n"
        "        \"user-context\": { \"foobar\": true }\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(l);

    // Make sure the lease has been updated.
    ASSERT_TRUE(l->duid_);

    // Check user context.
    ConstElementPtr ctx = l->getContext();
    ASSERT_TRUE(ctx);
    EXPECT_EQ(2, ctx->size());
    ASSERT_TRUE(ctx->contains("comment"));
    EXPECT_EQ("\"a comment\"", ctx->get("comment")->str());
    ASSERT_TRUE(ctx->contains("foobar"));
    EXPECT_EQ("true", ctx->get("foobar")->str());
}

void Lease6CmdsTest::testLease6UpdateNoLease() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 7654321,\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "failed to update the lease with address 2001:db8:1::1 "
        "either because the lease has been deleted or it has changed in the "
        "database, in both cases a retry might succeed";
    testCommand(txt, CONTROL_RESULT_CONFLICT, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);
}

void Lease6CmdsTest::testLease6UpdateForceCreate() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 7654321,\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\",\n"
        "        \"hostname\": \"newhostname.example.org\","
        "        \"force-create\": true"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(l);

    // Make sure the lease is correct.
    ASSERT_TRUE(l->duid_);
    EXPECT_EQ("88:88:88:88:88:88:88:88", l->duid_->toText());
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_EQ(7654321, l->iaid_);
    EXPECT_FALSE(l->getContext());
}

void Lease6CmdsTest::testLease6UpdateForceCreateNoSubnetId() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 7654321,\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\",\n"
        "        \"hostname\": \"newhostname.example.org\","
        "        \"force-create\": true"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now check that the lease is really there.
    Lease6Ptr l = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(l);

    // Make sure the subnet-id is figured out correctly.
    EXPECT_EQ(66, l->subnet_id_);

    // Make sure the lease is correct.
    ASSERT_TRUE(l->duid_);
    EXPECT_EQ("88:88:88:88:88:88:88:88", l->duid_->toText());
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_EQ(7654321, l->iaid_);
    EXPECT_FALSE(l->getContext());
}

void Lease6CmdsTest::testLease6UpdateDoNotForceCreate() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"iaid\": 7654321,\n"
        "        \"duid\": \"88:88:88:88:88:88:88:88\",\n"
        "        \"hostname\": \"newhostname.example.org\","
        "        \"force-create\": false"
        "    }\n"
        "}";
    string exp_rsp = "failed to update the lease with address 2001:db8:1::1 "
        "either because the lease has been deleted or it has changed in the "
        "database, in both cases a retry might succeed";
    testCommand(txt, CONTROL_RESULT_CONFLICT, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);
}

void Lease6CmdsTest::testLease6DelMissingParams() {
    // No parameters whatsoever. You want just a lease, any lease?
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Just the subnet-id won't cut it, either.
    cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // We can't identify your laptop by color. Sorry, buddy.
    cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"color\",\n"
        "        \"identifier\": \"blue\"\n"
        "    }\n"
        "}";
    exp_rsp = "Incorrect identifier type: color, the only supported values are: "
        "address, hw-address, duid";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Query by hw-address is not supported in v6. Sorry.
    cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"hw-address\",\n"
        "        \"identifier\": \"01:01:01:01:01:01\"\n"
        "    }\n"
        "}";
    exp_rsp = "Delete by hw-address is not allowed in v6.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Identifier value is missing.
    cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"hw-address\"\n"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Identifier-type is missing.
    cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier\": \"01:02:03:04:05\"\n"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6DelByAddrNotFound() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"ip-address\": \"2001:db8:1::10\"\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease not found.";

    // Note the status expected is empty. The query completed correctly,
    // just didn't found the lease.
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);
}

void Lease6CmdsTest::testLease6DelByDuidNotFound() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 1,\n"
        "        \"identifier-type\": \"duid\","
        "        \"identifier\": \"00:01:02:03:04:05:06:07\"\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease not found.";

    // Note the status expected is empty. The query completed correctly,
    // just didn't found the lease.
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Make sure the lease is still there.
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
}

void Lease6CmdsTest::testLease6DelByAddr() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\""
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease deleted.";

    // The status expected is success. The lease should be deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
}

void Lease6CmdsTest::testLease6DelByAddrDeclinedLeases() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true, true);

    checkLease6Stats(66, 2, 2, 0);

    checkLease6Stats(99, 2, 2, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\""
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease deleted.";

    // The status expected is success. The lease should be deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 1, 1, 0);

    checkLease6Stats(99, 2, 2, 0);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
}

void Lease6CmdsTest::testLease6DelByAddrBadParam() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Invalid family
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\""
        "    }\n"
        "}";
    string exp_rsp = "Invalid IPv6 address specified: 192.0.2.1";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // This is way off
    cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"221B Baker St.\""
        "    }\n"
        "}";
    exp_rsp = "Failed to convert string to address '221B Baker St.': Invalid argument";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6DelByAddrPrefix() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Let's start with regular address lease and make it a prefix lease.
    Lease6Ptr l = createLease6("2001:db8:1::1", 66, 0x77);
    l->addr_ = IOAddress("2001:db8:1234:ab::");
    l->type_ = Lease::TYPE_PD;
    l->prefixlen_ = 56;
    lmptr_->addLease(l);

    StatsMgr::instance().setValue(StatsMgr::generateName("subnet", 66,
                                                         "assigned-pds" ),
                                  int64_t(1));

    checkLease6Stats(66, 0, 0, 1);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"type\": \"IA_PD\","
        "        \"ip-address\": \"2001:db8:1234:ab::\""
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease deleted.";

    // The status expected is success. The lease should be deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_PD, IOAddress("2001:db8:1234:ab::")));
}

void Lease6CmdsTest::testLease6DelByDuid() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"iaid\": 42,"
        "        \"identifier-type\": \"duid\","
        "        \"identifier\": \"42:42:42:42:42:42:42:42\"\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv6 lease deleted.";

    // The status expected is success. The lease should be deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
}

void Lease6CmdsTest::testLease6Wipe() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66\n"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 2 IPv6 lease(s) from subnet(s) 66";

    // The status expected is success. The lease should be deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Make sure the leases in subnet 66 are really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));

    // Make sure the leases from subnet 99 are still there.
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::1")));
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::2")));
}

void Lease6CmdsTest::testLease6WipeAll() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0\n"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 4 IPv6 lease(s) from subnet(s) 66 99";

    // The status expected is success. The lease should be deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Make sure the leases in subnet 66 are really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));

    // Make sure the leases from subnet 99 are gone, too.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::2")));
}

void Lease6CmdsTest::testLease6WipeAllNoArgs() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-wipe\"\n"
        "}";
    string exp_rsp = "Deleted 4 IPv6 lease(s) from subnet(s) 66 99";

    // The status expected is success. The lease should be deleted.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Make sure the leases in subnet 66 are really gone.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));

    // Make sure the leases from subnet 99 are gone, too.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::2")));
}

void Lease6CmdsTest::testLease6WipeNoLeases() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 0 IPv6 lease(s) from subnet(s) 66";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);
}

void Lease6CmdsTest::testLease6WipeNoLeasesAll() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 0 IPv6 lease(s) from subnet(s) 66 99";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);
}

void Lease6CmdsTest::testLease6BrokenUpdate() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Set the sanity checks level.
    CfgMgr::instance().getCurrentCfg()->getConsistency()
        ->setLeaseSanityCheck(CfgConsistency::LEASE_CHECK_FIX);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 444,\n"
        "        \"ip-address\": \"2001:db8:1::23\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"force-create\": true\n"
        "    }\n"
        "}";
    string exp_rsp = "Invalid subnet-id: No IPv6 subnet with "
                     "subnet-id=444 currently configured.";
    testCommand(txt, CONTROL_RESULT_CONFLICT, exp_rsp);
}

void Lease6CmdsTest::testLease6BulkApply() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"deleted-leases\": ["
        "            {"
        "                \"ip-address\": \"2001:db8:1::1\","
        "                \"type\": \"IA_NA\""
        "            },"
        "            {"
        "                \"ip-address\": \"2001:db8:1::2\","
        "                \"type\": \"IA_NA\""
        "            }"
        "        ],"
        "        \"leases\": ["
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::123\",\n"
        "                \"duid\": \"11:11:11:11:11:11\",\n"
        "                \"iaid\": 1234\n"
        "            },"
        "            {"
        "                \"subnet-id\": 99,\n"
        "                \"ip-address\": \"2001:db8:2::123\",\n"
        "                \"duid\": \"22:22:22:22:22:22\",\n"
        "                \"iaid\": 1234\n"
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Bulk apply of 4 IPv6 leases completed.";

    // The status expected is success.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 3, 0, 0);

    //  Check that the leases we inserted are stored.
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::123")));
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::123")));

    // Check that the leases we deleted are gone,
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));
}

void Lease6CmdsTest::testLease6BulkApplyAddsOnlyBadParam() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Now send the command. The command uses an invalid state declined (1) for
    // PD prefix.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"leases\": ["
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::123\",\n"
        "                \"prefix-len\": 48,\n"
        "                \"type\": \"IA_PD\",\n"
        "                \"duid\": \"11:11:11:11:11:11\",\n"
        "                \"iaid\": 1234,\n"
        "                \"state\": 1"
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Invalid declined state for PD prefix.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Check that the lease was not inserted.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::123")));
}

void Lease6CmdsTest::testLease6BulkApplyAddsOnly() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 0, 0, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"leases\": ["
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::123\",\n"
        "                \"duid\": \"11:11:11:11:11:11\",\n"
        "                \"iaid\": 1234\n"
        "            },"
        "            {"
        "                \"subnet-id\": 99,\n"
        "                \"ip-address\": \"2001:db8:2::123\",\n"
        "                \"duid\": \"22:22:22:22:22:22\",\n"
        "                \"iaid\": 1234\n"
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Bulk apply of 2 IPv6 leases completed.";

    // The status expected is success.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 1, 0, 0);

    checkLease6Stats(99, 1, 0, 0);

    //  Check that the leases we inserted are stored.
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::123")));
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::123")));
}

void Lease6CmdsTest::testLease6BulkApplyUpdatesOnlyBadParam() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Let's start with regular address lease and make it a prefix lease.
    Lease6Ptr l = createLease6("2001:db8:1::1", 66, 0x77);
    l->addr_ = IOAddress("2001:db8:1234:ab::");
    l->type_ = Lease::TYPE_PD;
    l->prefixlen_ = 56;
    lmptr_->addLease(l);

    // Now send the command. The command uses an invalid state declined (1) for
    // PD prefix.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"leases\": ["
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1234:ab::\",\n"
        "                \"prefix-len\": 56,\n"
        "                \"type\": \"IA_PD\",\n"
        "                \"duid\": \"77:77:77:77:77:77\",\n"
        "                \"iaid\": 1234,\n"
        "                \"state\": 1"
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Invalid declined state for PD prefix.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Check that the lease we inserted is stored.
    Lease6Ptr lease1 = lmptr_->getLease6(Lease::TYPE_PD, IOAddress("2001:db8:1234:ab::"));
    ASSERT_TRUE(lease1);

    // The IAID should have not been updated for the existing lease.
    EXPECT_EQ(42, lease1->iaid_);
}

void Lease6CmdsTest::testLease6BulkApplyUpdatesOnly() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"leases\": ["
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::1\",\n"
        "                \"duid\": \"11:11:11:11:11:11\",\n"
        "                \"iaid\": 1234\n"
        "            },"
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::2\",\n"
        "                \"duid\": \"22:22:22:22:22:22\",\n"
        "                \"iaid\": 1234\n"
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Bulk apply of 2 IPv6 leases completed.";

    // The status expected is success.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    //  Check that the leases we inserted are stored.
    Lease6Ptr lease1 = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    Lease6Ptr lease2 = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2"));
    ASSERT_TRUE(lease1);
    ASSERT_TRUE(lease2);

    // The IAIDs should have been updated for the existing leases.
    EXPECT_EQ(1234, lease1->iaid_);
    EXPECT_EQ(1234, lease2->iaid_);
}

void Lease6CmdsTest::testLease6BulkApplyUpdatesOnlyExtendedInfo() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    Lease6Collection leases;
    vector<uint8_t> remote_id = { 1, 2, 3, 4, 5, 6 };
    leases = lmptr_->getLeases6ByRemoteId(remote_id,
                                          IOAddress::IPV6_ZERO_ADDRESS(),
                                         0,
                                         IOAddress::IPV6_ZERO_ADDRESS(),
                                         LeasePageSize(10));
    EXPECT_TRUE(leases.empty());
    vector<uint8_t> relay_bin(8, 0x64);
    DuidPtr relay_id(new DUID(relay_bin));
    leases = lmptr_->getLeases6ByRelayId(*relay_id,
                                         IOAddress::IPV6_ZERO_ADDRESS(),
                                         0,
                                         IOAddress::IPV6_ZERO_ADDRESS(),
                                         LeasePageSize(10));
    EXPECT_TRUE(leases.empty());

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"leases\": ["
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::1\",\n"
        "                \"duid\": \"11:11:11:11:11:11\",\n"
        "                \"iaid\": 1234\n"
        "            },"
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::2\",\n"
        "                \"duid\": \"22:22:22:22:22:22\",\n"
        "                \"iaid\": 1234\n,"
        "                \"user-context\": { \"ISC\": { \"relay-info\": [ {\n"
        "                  \"remote-id\": \"010203040506\",\n"
        "                  \"relay-id\": \"6464646464646464\" } ] } }\n"
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Bulk apply of 2 IPv6 leases completed.";

    // The status expected is success.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    //  Check that the leases we inserted are stored.
    Lease6Ptr lease1 = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    Lease6Ptr lease2 = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2"));
    ASSERT_TRUE(lease1);
    ASSERT_TRUE(lease2);

    // The IAIDs should have been updated for the existing leases.
    EXPECT_EQ(1234, lease1->iaid_);
    EXPECT_EQ(1234, lease2->iaid_);

    // The user context have been updated too.
    EXPECT_FALSE(lease1->getContext());
    ConstElementPtr ctx = lease2->getContext();
    ASSERT_TRUE(ctx);
    string expected = "{ \"ISC\": { \"relay-info\": ";
    expected += "[ { \"relay-id\": \"6464646464646464\", ";
    expected += "\"remote-id\": \"010203040506\" } ] } }";
    EXPECT_EQ(expected, ctx->str());

    // Check that BLQ tables were updated.
    leases = lmptr_->getLeases6ByRemoteId(remote_id,
                                          IOAddress::IPV6_ZERO_ADDRESS(),
                                          0,
                                          IOAddress::IPV6_ZERO_ADDRESS(),
                                          LeasePageSize(10));
    ASSERT_EQ(1, leases.size());
    Lease6Ptr lx = leases[0];
    ASSERT_TRUE(lx);
    EXPECT_EQ(IOAddress("2001:db8:1::2"), lx->addr_);
    EXPECT_EQ(*lease2, *lx);
    leases = lmptr_->getLeases6ByRelayId(*relay_id,
                                         IOAddress::IPV6_ZERO_ADDRESS(),
                                         0,
                                         IOAddress::IPV6_ZERO_ADDRESS(),
                                         LeasePageSize(10));
    ASSERT_EQ(1, leases.size());
    lx = leases[0];
    ASSERT_TRUE(lx);
    EXPECT_EQ(IOAddress("2001:db8:1::2"), lx->addr_);
    EXPECT_EQ(*lease2, *lx);
}

void Lease6CmdsTest::testLease6BulkApplyDeletesOnly() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"deleted-leases\": ["
        "            {"
        "                \"ip-address\": \"2001:db8:1::1\","
        "                \"type\": \"IA_NA\""
        "            },"
        "            {"
        "                \"ip-address\": \"2001:db8:1::2\","
        "                \"type\": \"IA_NA\""
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Bulk apply of 2 IPv6 leases completed.";

    // The status expected is success.
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 0, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Check that the leases we deleted are gone,
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));
}

void Lease6CmdsTest::testLease6BulkApplyDeleteNonExiting() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"deleted-leases\": ["
        "            {"
        "                \"ip-address\": \"2001:db8:1::123\","
        "                \"type\": \"IA_NA\""
        "            },"
        "            {"
        "                \"ip-address\": \"2001:db8:1::234\","
        "                \"type\": \"IA_NA\""
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Bulk apply of 0 IPv6 leases completed.";

    // The status expected is success.
    auto resp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
    ASSERT_TRUE(resp);
    ASSERT_EQ(Element::map, resp->getType());

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    auto args = resp->get("arguments");
    ASSERT_TRUE(args);
    ASSERT_EQ(Element::map, args->getType());

    auto failed_deleted_leases = args->get("failed-deleted-leases");
    ASSERT_TRUE(failed_deleted_leases);
    ASSERT_EQ(Element::list, failed_deleted_leases->getType());
    ASSERT_EQ(2, failed_deleted_leases->size());

    {
        SCOPED_TRACE("lease address 2001:db8:1::123");
        checkFailedLease(failed_deleted_leases, "IA_NA", "2001:db8:1::123",
                         CONTROL_RESULT_EMPTY, "lease not found");
    }

    {
        SCOPED_TRACE("lease address 2001:db8:1::234");
        checkFailedLease(failed_deleted_leases, "IA_NA", "2001:db8:1::234",
                         CONTROL_RESULT_EMPTY, "lease not found");
    }
}

void Lease6CmdsTest::testLease6BulkApplyRollback() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"deleted-leases\": ["
        "            {"
        "                \"ip-address\": \"2001:db8:1::1\","
        "                \"type\": \"IA_NA\""
        "            },"
        "            {"
        "                \"ip-address\": \"2001:db8:1::2\","
        "                \"type\": \"IA_NA\""
        "            }"
        "        ],"
        "        \"leases\": ["
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::123\","
        "                \"duid\": \"11:11:11:11:11:11\","
        "                \"iaid\": 1234\n"
        "            },"
        "            {"
        "                \"subnet-id\": -1,"
        "                \"ip-address\": \"2001:db8:2::123\","
        "                \"duid\": \"22:22:22:22:22:22\","
        "                \"iaid\": 1234"
        "            }"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "out of range value (-1) specified for parameter 'subnet-id' (<string>:5:57)";

    // The status expected is success.
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease6Stats(66, 2, 0, 0);

    checkLease6Stats(99, 2, 0, 0);

    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::123")));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:2::123")));

    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1")));
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::2")));
}

void Lease6CmdsTest::testLease6ResendDdnsBadParam() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Missing address parameter.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "    }\n"
        "}\n";

    string exp_rsp = "'ip-address' parameter is missing.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Invalid address family.
    cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"192.0.2.1\"\n"
        "    }\n"
        "}\n";

    exp_rsp = "Invalid IPv6 address specified: 192.0.2.1";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // ip-address is not an address at all.
    cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"221B Baker St.\"\n"
        "    }\n"
        "}\n";

    exp_rsp = "'221B Baker St.' is not a valid IP address.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease6CmdsTest::testLease6ResendDdnsDisabled() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Disable DDNS updating.
    disableD2();

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001::dead:beef\"\n"
        "    }\n"
        "}";

    string exp_rsp = "DDNS updating is not enabled";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_CONFLICT, exp_rsp);
    // With D2 disabled there is no queue, size should come back as -1.
    EXPECT_EQ(ncrQueueSize(), -1);
}

void Lease6CmdsTest::testLease6ResendDdnsNoLease() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Invalid
    string cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"2001::dead:beef\"\n"
        "    }\n"
        "}\n";
    string exp_rsp = "No lease found for: 2001::dead:beef";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

void Lease6CmdsTest::testLease6ResendNoHostname() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // NCR sender queue should be empty.
    ASSERT_EQ(ncrQueueSize(), 0);

    // Fetch the lease so we can replace the hostname with "".
    Lease6Ptr lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(lease);
    lease->hostname_ = "";
    lmptr_->updateLease6(lease);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\""
        "    }\n"
        "}";

    string exp_rsp = "Lease for: 2001:db8:1::1, has no hostname, nothing to update";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_CONFLICT, exp_rsp);

    // There should not any NCRs queued.
    EXPECT_EQ(ncrQueueSize(), 0);
}

void Lease6CmdsTest::testLease6ResendNoDirectionsEnabled() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // NCR sender queue should be empty.
    ASSERT_EQ(ncrQueueSize(), 0);

    // Fetch the lease so we can replace the hostname with "".
    Lease6Ptr lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_TRUE(lease);
    lease->fqdn_fwd_ = false;
    lease->fqdn_rev_ = false;
    lmptr_->updateLease6(lease);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\""
        "    }\n"
        "}";

    string exp_rsp = "Neither forward nor reverse updates enabled for lease for: 2001:db8:1::1";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_CONFLICT, exp_rsp);

    // There should not any NCRs queued.
    EXPECT_EQ(ncrQueueSize(), 0);
}

void Lease6CmdsTest::testLease6ResendDdnsEnabled() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Structure detailing a test scenario.
    struct Scenario {
        std::string description_;
        bool fqdn_fwd_;
        bool fqdn_rev_;
    };

    // Three test scenarios to verify each combination of true flags.
    std::vector<Scenario> scenarios = {
       { "fwd_only", true,  false },
       { "rev_only", false, true},
       { "both",     true,  true},
    };

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\""
        "    }\n"
        "}";

    // Expected response string.
    string exp_rsp = "NCR generated for: 2001:db8:1::1, hostname: myhost.example.com.";

    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Fetch the lease so we can update the DDNS direction flags.
        Lease6Ptr lease = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"));
        ASSERT_TRUE(lease);
        lease->fqdn_rev_ = scenario.fqdn_rev_;
        lease->fqdn_fwd_ = scenario.fqdn_fwd_;
        lmptr_->updateLease6(lease);

        // Queue should be empty.
        ASSERT_EQ(ncrQueueSize(), 0);
        ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

        // We should have one entry in the queue.
        ASSERT_EQ(ncrQueueSize(), 1);
        verifyNameChangeRequest(CHG_ADD, scenario.fqdn_rev_, scenario.fqdn_fwd_,
                                "2001:db8:1::1", "myhost.example.com.");
    }
}

void Lease6CmdsTest::testLease6DnsRemoveD2Enabled() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Structure detailing a test scenario.
    struct Scenario {
        std::string description_;
        std::string hostname_;
        bool fqdn_fwd_;
        bool fqdn_rev_;
        std::string update_ddns_;
        bool exp_ncr_;
    };

    bool fwd = true;
    bool rev = true;
    bool ncr = true;

    // Three test scenarios to verify each combination of true flags.
    std::vector<Scenario> scenarios = {
        {
            "no_host",
            "",
            fwd, rev,
            "\"update-ddns\": true",
            !ncr
        },
        {
            "no directions",
            "myhost.example.com.",
            !fwd, !rev,
            "\"update-ddns\": true",
            !ncr
        },
        {
            "fwd_only",
            "myhost.example.com.",
            fwd, !rev,
            "\"update-ddns\": true",
            ncr
        },
        {
            "rev_only",
            "myhost.example.com.",
            !fwd, rev,
            "\"update-ddns\": true",
            ncr
        },
        {
            "both directions",
            "myhost.example.com.",
            fwd, rev,
            "\"update-ddns\": true",
            ncr
        },
        {
            "default update-ddns",
            "myhost.example.com.",
            fwd, rev,
            "",
            !ncr
        },
        {
            "update-ddns = false",
            "myhost.example.com.",
            fwd, rev,
            "\"update-ddns\": false",
            !ncr
        },
    };

    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Let's create a lease with scenario attributes.
        Lease6Ptr lease = createLease6("2001:db8:1::8", 66, 0x77);
        lease->hostname_ = scenario.hostname_;
        lease->fqdn_rev_ = scenario.fqdn_rev_;
        lease->fqdn_fwd_ = scenario.fqdn_fwd_;
        ASSERT_TRUE(lmptr_->addLease(lease));

        // NCR Queue should be empty.
        ASSERT_EQ(ncrQueueSize(), 0);

        // Build the command
        std::stringstream cmd;
        cmd <<
            "{"
            "    \"command\": \"lease6-del\","
            "    \"arguments\": {"
            "        \"ip-address\": \"2001:db8:1::8\"\n";

        if (!scenario.update_ddns_.empty()) {
            cmd << "," << scenario.update_ddns_;
        }

        cmd << "}}";

        // Execute the delete command.
        static_cast<void>(testCommand(cmd.str(), CONTROL_RESULT_SUCCESS, "IPv6 lease deleted."));

        if (!scenario.exp_ncr_) {
            // Should not have an ncr.
            ASSERT_EQ(ncrQueueSize(), 0);
        } else {
            // We should have an ncr, verify it.
            ASSERT_EQ(ncrQueueSize(), 1);
            verifyNameChangeRequest(CHG_REMOVE, scenario.fqdn_rev_, scenario.fqdn_fwd_,
                                    lease->addr_.toText(), lease->hostname_);
        }

        // Lease should have been deleted.
        lease = lmptr_->getLease6(Lease::TYPE_NA, lease->addr_);
        ASSERT_FALSE(lease);
    }
}

void Lease6CmdsTest::testLease6DnsRemoveD2Disabled() {
    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    disableD2();

    // Delete for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"2001:db8:1::8\",\n"
        "        \"update-ddns\": true\n"
        "    }\n"
        "}";

    // Let's create a lease with scenario attributes.
    Lease6Ptr lease = createLease6("2001:db8:1::8", 66, 0x77);
    lease->hostname_ = "myhost.example.com.";
    lease->fqdn_rev_ = true;
    lease->fqdn_fwd_ = true;
    ASSERT_TRUE(lmptr_->addLease(lease));

    // NCR Queue is not enabled.
    ASSERT_EQ(ncrQueueSize(), -1);

    // Execute the delete command.
    static_cast<void>(testCommand(cmd, CONTROL_RESULT_SUCCESS, "IPv6 lease deleted."));

    // NCR Queue is not enabled.
    ASSERT_EQ(ncrQueueSize(), -1);

    // Lease should have been deleted.
    lease = lmptr_->getLease6(Lease::TYPE_NA, lease->addr_);
    ASSERT_FALSE(lease);
}

void Lease6CmdsTest::testLease6ConflictingAdd() {
    MultiThreadingTest mt(true);

    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Make sure the lease doesn't exist.
    IOAddress addr("2001:db8:1::1");
    Lease6Ptr lease = lmptr_->getLease6(Lease::TYPE_NA, addr);
    ASSERT_FALSE(lease);

    // Verify stats show no leases.
    checkLease6Stats(66, 0, 0, 0);

    // Lock the address.
    ResourceHandler resource_handler;
    ASSERT_TRUE(resource_handler.tryLock(Lease::TYPE_NA, addr));

    // Now let's try to add the lease.
    string txt =
        "{\n"
        "    \"command\": \"lease6-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"iaid\": 1234,\n"
        "        \"comment\": \"a comment\"\n"
        "    }\n"
        "}";

    string exp_rsp = "ResourceBusy: IP address:2001:db8:1::1 could not be added.";
    testCommand(txt, CONTROL_RESULT_CONFLICT, exp_rsp);

    // Lease should not have been added.
    lease = lmptr_->getLease6(Lease::TYPE_NA, addr);
    ASSERT_FALSE(lease);

    // Stats should not have changed.
    checkLease6Stats(66, 0, 0, 0);
}

void Lease6CmdsTest::testLease6ConflictingUpdate() {
    MultiThreadingTest mt(true);

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, true);

    // Verify lease stats show leases.
    checkLease6Stats(66, 2, 0, 0);

    // Make sure the lease exists.
    IOAddress addr("2001:db8:1::1");
    Lease6Ptr lease = lmptr_->getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(lease);
    // Save a copy of the original lease.
    Lease6 original_lease = *lease;

    // Lock the address.
    ResourceHandler resource_handler;
    ASSERT_TRUE(resource_handler.tryLock(Lease::TYPE_NA, addr));

    // Now let's try to update the lease.
    string txt =
        "{\n"
        "    \"command\": \"lease6-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 66,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"duid\": \"2a:2b:2c:2d:2e:2f\",\n"
        "        \"iaid\": 1234,\n"
        "        \"comment\": \"a comment\"\n"
        "    }\n"
        "}";

    string exp_rsp = "ResourceBusy: IP address:2001:db8:1::1 could not be updated.";
    testCommand(txt, CONTROL_RESULT_CONFLICT, exp_rsp);

    // Fetch the lease again.
    lease = lmptr_->getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(lease);

    // Lease should not have been changed.
    EXPECT_EQ(original_lease, *lease);
}

void Lease6CmdsTest::testLease6ConflictingBulkApplyAdd() {
    MultiThreadingTest mt(true);

    // Initialize lease manager (true = v6, true = add leases)
    initLeaseMgr(true, false);

    checkLease6Stats(66, 0, 0, 0);
    checkLease6Stats(99, 0, 0, 0);

    // Lock the address.
    IOAddress locked_addr("2001:db8:2::77");
    ResourceHandler resource_handler;
    ASSERT_TRUE(resource_handler.tryLock(Lease::TYPE_NA, locked_addr));

    // Now send the command.
    string cmd =
        "{\n"
        "    \"command\": \"lease6-bulk-apply\",\n"
        "    \"arguments\": {"
        "        \"leases\": ["
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::123\",\n"
        "                \"duid\": \"11:11:11:11:11:11\",\n"
        "                \"iaid\": 1234\n"
        "            },"
        "            {"
        "                \"subnet-id\": 99,\n"
        "                \"ip-address\": \"2001:db8:2::77\",\n"
        "                \"duid\": \"22:22:22:22:22:22\",\n"
        "                \"iaid\": 1234\n"
        "            },"
        "            {"
        "                \"subnet-id\": 66,\n"
        "                \"ip-address\": \"2001:db8:1::124\",\n"
        "                \"duid\": \"33:33:33:33:33:33\",\n"
        "                \"iaid\": 1234\n"
        "            },"
        "        ]"
        "    }"
        "}";
    string exp_rsp = "Bulk apply of 2 IPv6 leases completed.";

    // The status expected is success.
    auto rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease6Stats(66, 2, 0, 0);
    checkLease6Stats(99, 0, 0, 0);

    //  Check that the leases we inserted are stored.
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::123")));
    EXPECT_TRUE(lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::124")));

    // Check that the lease for locked address was not added.
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, locked_addr));

    auto args = rsp->get("arguments");
    auto failed_leases = args->get("failed-leases");
    ASSERT_TRUE(failed_leases);
    ASSERT_EQ(Element::list, failed_leases->getType());
    ASSERT_EQ(1, failed_leases->size());
    checkFailedLease(failed_leases, "IA_NA", locked_addr.toText(),
                     CONTROL_RESULT_CONFLICT,
                     "ResourceBusy: IP address:2001:db8:2::77 could not be updated.");
}

void Lease6CmdsTest::testLease6Write() {
    // Initialize lease manager (true = v6, false = don't add leases)
    initLeaseMgr(true, false);

    // Parameter is missing.
    string txt =
        "{\n"
        "    \"command\": \"lease6-write\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "'filename' parameter not specified";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Filename must be a string.
    txt =
        "{\n"
        "    \"command\": \"lease6-write\",\n"
        "    \"arguments\": {"
        "        \"filename\": 0\n"
        "    }\n"
        "}";
    exp_rsp = "'filename' parameter must be a string";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Filename must be not empty.
    txt =
        "{\n"
        "    \"command\": \"lease6-write\",\n"
        "    \"arguments\": {"
        "        \"filename\": \"\"\n"
        "    }\n"
        "}";
    exp_rsp = "'filename' parameter is empty";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

TEST_F(Lease6CmdsTest, lease6AddMissingParams) {
    testLease6AddMissingParams();
}

TEST_F(Lease6CmdsTest, lease6AddMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddMissingParams();
}

TEST_F(Lease6CmdsTest, lease6AddBadParams) {
    testLease6AddBadParams();
}

TEST_F(Lease6CmdsTest, lease6AddBadParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddBadParams();
}

TEST_F(Lease6CmdsTest, lease6Add) {
    testLease6Add();
}

TEST_F(Lease6CmdsTest, lease6AddMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6Add();
}

TEST_F(Lease6CmdsTest, lease6AddDeclinedLeases) {
    testLease6AddDeclinedLeases();
}

TEST_F(Lease6CmdsTest, lease6AddDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddDeclinedLeases();
}

TEST_F(Lease6CmdsTest, lease6AddExisting) {
    testLease6AddExisting();
}

TEST_F(Lease6CmdsTest, lease6AddExistingMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddExisting();
}

TEST_F(Lease6CmdsTest, lease6AddSubnetIdMissing) {
    testLease6AddSubnetIdMissing();
}

TEST_F(Lease6CmdsTest, lease6AddSubnetIdMissingMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddSubnetIdMissing();
}

TEST_F(Lease6CmdsTest, lease6AddSubnetIdMissingDeclinedLeases) {
    testLease6AddSubnetIdMissingDeclinedLeases();
}

TEST_F(Lease6CmdsTest, lease6AddSubnetIdMissingDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddSubnetIdMissingDeclinedLeases();
}

TEST_F(Lease6CmdsTest, lease6AddSubnetIdMissingBadAddr) {
    testLease6AddSubnetIdMissingBadAddr();
}

TEST_F(Lease6CmdsTest, lease6AddSubnetIdMissingBadAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddSubnetIdMissingBadAddr();
}

TEST_F(Lease6CmdsTest, lease6AddNegativeExpireTime) {
    testLease6AddNegativeExpireTime();
}

TEST_F(Lease6CmdsTest, lease6AddNegativeExpireTimeMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddNegativeExpireTime();
}

TEST_F(Lease6CmdsTest, lease6AddNegativeCltt) {
    testLease6AddNegativeCltt();
}

TEST_F(Lease6CmdsTest, lease6AddNegativeClttMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddNegativeCltt();
}

TEST_F(Lease6CmdsTest, lease6AddPrefix) {
    testLease6AddPrefix();
}

TEST_F(Lease6CmdsTest, lease6AddPrefixMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddPrefix();
}

TEST_F(Lease6CmdsTest, lease6AddFullAddr) {
    testLease6AddFullAddr();
}

TEST_F(Lease6CmdsTest, lease6AddFullAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddFullAddr();
}

TEST_F(Lease6CmdsTest, lease6AddComment) {
    testLease6AddComment();
}

TEST_F(Lease6CmdsTest, lease6AddCommentMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6AddComment();
}

TEST_F(Lease6CmdsTest, lease6GetByAddrNotFound) {
    testLease6GetByAddrNotFound();
}

TEST_F(Lease6CmdsTest, lease6GetByAddrNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByAddrNotFound();
}

TEST_F(Lease6CmdsTest, lease6GetByClientIdInvalidType) {
    testLease6GetByClientIdInvalidType();
}

TEST_F(Lease6CmdsTest, lease6GetByClientIdInvalidTypeMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByClientIdInvalidType();
}

TEST_F(Lease6CmdsTest, lease6GetByDuidNotFound) {
    testLease6GetByDuidNotFound();
}

TEST_F(Lease6CmdsTest, lease6GetByDuidNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByDuidNotFound();
}

TEST_F(Lease6CmdsTest, lease6GetByAddr) {
    testLease6GetByAddr();
}

TEST_F(Lease6CmdsTest, lease6GetByAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByAddr();
}

TEST_F(Lease6CmdsTest, lease6GetMissingParams) {
    testLease6GetMissingParams();
}

TEST_F(Lease6CmdsTest, lease6GetMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetMissingParams();
}

TEST_F(Lease6CmdsTest, lease6GetByAddrBadParam) {
    testLease6GetByAddrBadParam();
}

TEST_F(Lease6CmdsTest, lease6GetByAddrBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByAddrBadParam();
}

TEST_F(Lease6CmdsTest, lease6GetByAddrPrefix) {
    testLease6GetByAddrPrefix();
}

TEST_F(Lease6CmdsTest, lease6GetByAddrPrefixMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByAddrPrefix();
}

TEST_F(Lease6CmdsTest, lease6GetByDuid) {
    testLease6GetByDuid();
}

TEST_F(Lease6CmdsTest, lease6GetByDuidMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByDuid();
}

TEST_F(Lease6CmdsTest, lease6GetAll) {
    testLease6GetAll();
}

TEST_F(Lease6CmdsTest, lease6GetAllMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetAll();
}

TEST_F(Lease6CmdsTest, lease6GetAllNoLeases) {
    testLease6GetAllNoLeases();
}

TEST_F(Lease6CmdsTest, lease6GetAllNoLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetAllNoLeases();
}

TEST_F(Lease6CmdsTest, lease6GetAllBySubnetId) {
    testLease6GetAllBySubnetId();
}

TEST_F(Lease6CmdsTest, lease6GetAllBySubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetAllBySubnetId();
}

TEST_F(Lease6CmdsTest, lease6GetAllBySubnetIdNoLeases) {
    testLease6GetAllBySubnetIdNoLeases();
}

TEST_F(Lease6CmdsTest, lease6GetAllBySubnetIdNoLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetAllBySubnetIdNoLeases();
}

TEST_F(Lease6CmdsTest, lease6GetAllByMultipleSubnetIds) {
    testLease6GetAllByMultipleSubnetIds();
}

TEST_F(Lease6CmdsTest, lease6GetAllByMultipleSubnetIdsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetAllByMultipleSubnetIds();
}

TEST_F(Lease6CmdsTest, lease6GetBySubnetIdInvalidArguments) {
    testLease6GetBySubnetIdInvalidArguments();
}

TEST_F(Lease6CmdsTest, lease6GetBySubnetIdInvalidArgumentsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetBySubnetIdInvalidArguments();
}

TEST_F(Lease6CmdsTest, lease6GetPaged) {
    testLease6GetPaged();
}

TEST_F(Lease6CmdsTest, lease6GetPagedMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetPaged();
}

TEST_F(Lease6CmdsTest, lease6GetPagedZeroAddress) {
    testLease6GetPagedZeroAddress();
}

TEST_F(Lease6CmdsTest, lease6GetPagedZeroAddressMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetPagedZeroAddress();
}

TEST_F(Lease6CmdsTest, lease6GetPagedIPv4Address) {
    testLease6GetPagedIPv4Address();
}

TEST_F(Lease6CmdsTest, lease6GetPagedIPv4AddressMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetPagedIPv4Address();
}

TEST_F(Lease6CmdsTest, lease6GetPagedInvalidFrom) {
    testLease6GetPagedInvalidFrom();
}

TEST_F(Lease6CmdsTest, lease6GetPagedInvalidFromMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetPagedInvalidFrom();
}

TEST_F(Lease6CmdsTest, lease6GetPagedNoLimit) {
    testLease6GetPagedNoLimit();
}

TEST_F(Lease6CmdsTest, lease6GetPagedNoLimitMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetPagedNoLimit();
}

TEST_F(Lease6CmdsTest, lease6GetPagedLimitNotNumber) {
    testLease6GetPagedLimitNotNumber();
}

TEST_F(Lease6CmdsTest, lease6GetPagedLimitNotNumberMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetPagedLimitNotNumber();
}

TEST_F(Lease6CmdsTest, lease6GetPagedLimitIsZero) {
    testLease6GetPagedLimitIsZero();
}

TEST_F(Lease6CmdsTest, lease6GetPagedLimitIsZeroMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetPagedLimitIsZero();
}

TEST_F(Lease6CmdsTest, lease6GetByDuidParams) {
    testLease6GetByDuidParams();
}

TEST_F(Lease6CmdsTest, lease6GetByDuidParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByDuidParams();
}

TEST_F(Lease6CmdsTest, lease6GetByDuidFind0) {
    testLease6GetByDuidFind0();
}

TEST_F(Lease6CmdsTest, lease6GetByDuidFind0MultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByDuidFind0();
}

TEST_F(Lease6CmdsTest, lease6GetByDuidFind2) {
    testLease6GetByDuidFind2();
}

TEST_F(Lease6CmdsTest, lease6GetByDuidFind2MultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByDuidFind2();
}

TEST_F(Lease6CmdsTest, lease6GetByHostnameParams) {
    testLease6GetByHostnameParams();
}

TEST_F(Lease6CmdsTest, lease6GetByHostnameParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByHostnameParams();
}

TEST_F(Lease6CmdsTest, lease6GetByHostnameFind0) {
    testLease6GetByHostnameFind0();
}

TEST_F(Lease6CmdsTest, lease6GetByHostnameFind0MultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByHostnameFind0();
}

TEST_F(Lease6CmdsTest, lease6GetByHostnameFind2) {
    testLease6GetByHostnameFind2();
}

TEST_F(Lease6CmdsTest, lease6GetByHostnameFind2MultiThreading) {
    MultiThreadingTest mt(true);
    testLease6GetByHostnameFind2();
}

TEST_F(Lease6CmdsTest, lease6UpdateMissingParams) {
    testLease6UpdateMissingParams();
}

TEST_F(Lease6CmdsTest, lease6UpdateMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateMissingParams();
}

TEST_F(Lease6CmdsTest, lease6UpdateBadParams) {
    testLease6UpdateBadParams();
}

TEST_F(Lease6CmdsTest, lease6UpdateBadParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateBadParams();
}

TEST_F(Lease6CmdsTest, lease6Update) {
    testLease6Update();
}

TEST_F(Lease6CmdsTest, lease6UpdateExtendedInfo) {
    testLease6UpdateExtendedInfo();
}

TEST_F(Lease6CmdsTest, lease6UpdateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6Update();
}

TEST_F(Lease6CmdsTest, lease6UpdateDeclinedLeases) {
    testLease6UpdateDeclinedLeases();
}

TEST_F(Lease6CmdsTest, lease6UpdateDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateDeclinedLeases();
}

TEST_F(Lease6CmdsTest, lease6UpdateNoSubnetId) {
    testLease6UpdateNoSubnetId();
}

TEST_F(Lease6CmdsTest, lease6UpdateNoSubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateNoSubnetId();
}

TEST_F(Lease6CmdsTest, lease6UpdateNoSubnetIdDeclinedLeases) {
    testLease6UpdateNoSubnetIdDeclinedLeases();
}

TEST_F(Lease6CmdsTest, lease6UpdateNoSubnetIdDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateNoSubnetIdDeclinedLeases();
}

TEST_F(Lease6CmdsTest, lease6UpdateComment) {
    testLease6UpdateComment();
}

TEST_F(Lease6CmdsTest, lease6UpdateCommentMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateComment();
}

TEST_F(Lease6CmdsTest, lease6UpdateNoLease) {
    testLease6UpdateNoLease();
}

TEST_F(Lease6CmdsTest, lease6UpdateNoLeaseMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateNoLease();
}

TEST_F(Lease6CmdsTest, lease6UpdateForceCreate) {
    testLease6UpdateForceCreate();
}

TEST_F(Lease6CmdsTest, lease6UpdateForceCreateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateForceCreate();
}

TEST_F(Lease6CmdsTest, lease6UpdateForceCreateNoSubnetId) {
    testLease6UpdateForceCreateNoSubnetId();
}

TEST_F(Lease6CmdsTest, lease6UpdateForceCreateNoSubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateForceCreateNoSubnetId();
}

TEST_F(Lease6CmdsTest, lease6UpdateDoNotForceCreate) {
    testLease6UpdateDoNotForceCreate();
}

TEST_F(Lease6CmdsTest, lease6UpdateDoNotForceCreateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6UpdateDoNotForceCreate();
}

TEST_F(Lease6CmdsTest, lease6DelMissingParams) {
    testLease6DelMissingParams();
}

TEST_F(Lease6CmdsTest, lease6DelMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelMissingParams();
}

TEST_F(Lease6CmdsTest, lease6DelByAddrNotFound) {
    testLease6DelByAddrNotFound();
}

TEST_F(Lease6CmdsTest, lease6DelByAddrNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelByAddrNotFound();
}

TEST_F(Lease6CmdsTest, lease6DelByDuidNotFound) {
    testLease6DelByDuidNotFound();
}

TEST_F(Lease6CmdsTest, lease6DelByDuidNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelByDuidNotFound();
}

TEST_F(Lease6CmdsTest, lease6DelByAddr) {
    testLease6DelByAddr();
}

TEST_F(Lease6CmdsTest, lease6DelByAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelByAddr();
}

TEST_F(Lease6CmdsTest, lease6DelByAddrDeclinedLeases) {
    testLease6DelByAddrDeclinedLeases();
}

TEST_F(Lease6CmdsTest, lease6DelByAddrDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelByAddrDeclinedLeases();
}

TEST_F(Lease6CmdsTest, lease6DelByAddrBadParam) {
    testLease6DelByAddrBadParam();
}

TEST_F(Lease6CmdsTest, lease6DelByAddrBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelByAddrBadParam();
}

TEST_F(Lease6CmdsTest, lease6DelByAddrPrefix) {
    testLease6DelByAddrPrefix();
}

TEST_F(Lease6CmdsTest, lease6DelByAddrPrefixMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelByAddrPrefix();
}

TEST_F(Lease6CmdsTest, lease6DelByDuid) {
    testLease6DelByDuid();
}

TEST_F(Lease6CmdsTest, lease6DelByDuidMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DelByDuid();
}

TEST_F(Lease6CmdsTest, lease6Wipe) {
    testLease6Wipe();
}

TEST_F(Lease6CmdsTest, lease6WipeMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6Wipe();
}

TEST_F(Lease6CmdsTest, lease6WipeAll) {
    testLease6WipeAll();
}

TEST_F(Lease6CmdsTest, lease6WipeAllMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6WipeAll();
}

TEST_F(Lease6CmdsTest, lease6WipeAllNoArgs) {
    testLease6WipeAllNoArgs();
}

TEST_F(Lease6CmdsTest, lease6WipeAllNoArgsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6WipeAllNoArgs();
}

TEST_F(Lease6CmdsTest, lease6WipeNoLeases) {
    testLease6WipeNoLeases();
}

TEST_F(Lease6CmdsTest, lease6WipeNoLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6WipeNoLeases();
}

TEST_F(Lease6CmdsTest, lease6WipeNoLeasesAll) {
    testLease6WipeNoLeasesAll();
}

TEST_F(Lease6CmdsTest, lease6WipeNoLeasesAllMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6WipeNoLeasesAll();
}

TEST_F(Lease6CmdsTest, lease6BrokenUpdate) {
    testLease6BrokenUpdate();
}

TEST_F(Lease6CmdsTest, lease6BrokenUpdateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BrokenUpdate();
}

TEST_F(Lease6CmdsTest, lease6BulkApply) {
    testLease6BulkApply();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApply();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyAddsOnlyBadParam) {
    testLease6BulkApplyAddsOnlyBadParam();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyAddsOnlyBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApplyAddsOnlyBadParam();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyAddsOnly) {
    testLease6BulkApplyAddsOnly();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyAddsOnlyMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApplyAddsOnly();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyUpdatesOnlyBadParam) {
    testLease6BulkApplyUpdatesOnlyBadParam();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyUpdatesOnlyBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApplyUpdatesOnlyBadParam();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyUpdatesOnly) {
    testLease6BulkApplyUpdatesOnly();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyUpdatesOnlyExtendedInfo) {
    testLease6BulkApplyUpdatesOnlyExtendedInfo();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyUpdatesOnlyMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApplyUpdatesOnly();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyDeletesOnly) {
    testLease6BulkApplyDeletesOnly();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyDeletesOnlyMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApplyDeletesOnly();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyDeleteNonExiting) {
    testLease6BulkApplyDeleteNonExiting();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyDeleteNonExitingMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApplyDeleteNonExiting();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyRollback) {
    testLease6BulkApplyRollback();
}

TEST_F(Lease6CmdsTest, lease6BulkApplyRollbackMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6BulkApplyRollback();
}

TEST_F(Lease6CmdsTest, lease6ResendDdnsBadParam) {
    testLease6ResendDdnsBadParam();
}

TEST_F(Lease6CmdsTest, lease6ResendDdnsBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6ResendDdnsBadParam();
}

TEST_F(Lease6CmdsTest, lease6ResendDdnsDisabled) {
    testLease6ResendDdnsDisabled();
}

TEST_F(Lease6CmdsTest, lease6ResendDdnsDisabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6ResendDdnsDisabled();
}

TEST_F(Lease6CmdsTest, lease6ResendDdnsNoLease) {
    testLease6ResendDdnsNoLease();
}

TEST_F(Lease6CmdsTest, lease6ResendDdnsNoLeaseMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6ResendDdnsNoLease();
}

TEST_F(Lease6CmdsTest, lease6ResendNoHostname) {
    testLease6ResendNoHostname();
}

TEST_F(Lease6CmdsTest, lease6ResendNoHostnameMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6ResendNoHostname();
}

TEST_F(Lease6CmdsTest, lease6ResendNoDirectionsEnabled) {
    testLease6ResendNoDirectionsEnabled();
}

TEST_F(Lease6CmdsTest, lease6ResendNoDirectionsEnabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6ResendNoDirectionsEnabled();
}

TEST_F(Lease6CmdsTest, lease6ResendDdnsEnabled) {
    testLease6ResendDdnsEnabled();
}

TEST_F(Lease6CmdsTest, lease6ResendDdnsEnabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6ResendDdnsEnabled();
}

TEST_F(Lease6CmdsTest, lease6DnsRemoveD2Enabled) {
    testLease6DnsRemoveD2Enabled();
}

TEST_F(Lease6CmdsTest, lease6DnsRemoveD2EnabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DnsRemoveD2Enabled();
}

TEST_F(Lease6CmdsTest, lease6DnsRemoveD2Disabled) {
    testLease6DnsRemoveD2Disabled();
}

TEST_F(Lease6CmdsTest, lease6DnsRemoveD2DisabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6DnsRemoveD2Disabled();
}

TEST_F(Lease6CmdsTest, lease6ConflictingAddMultiThreading) {
    testLease6ConflictingAdd();
}

TEST_F(Lease6CmdsTest, lease6ConflictingUpdateMultiThreading) {
    testLease6ConflictingUpdate();
}

TEST_F(Lease6CmdsTest, lease6ConflictingBulkApplyAddMultiThreading) {
    testLease6ConflictingBulkApplyAdd();
}

TEST_F(Lease6CmdsTest, lease6Write) {
    testLease6Write();
}

TEST_F(Lease6CmdsTest, lease6WriteMultiThreading) {
    MultiThreadingTest mt(true);
    testLease6Write();
}

} // end of anonymous namespace
