// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
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

/// @brief Class dedicated to testing v4 part of lease_cmds library.
///
/// Provides convenience methods for loading, testing all commands and
/// unloading the lease_cmds library.
class Lease4CmdsTest : public LeaseCmdsTest {
public:
    /// @brief Checks if specified response contains IPv4 lease
    ///
    /// @param lease Element tree that represents a lease
    /// @param ip expected IP address
    /// @param subnet_id expected subnet-id
    /// @param hwaddr expected value of hardware address
    /// @param client_id_required true if client-id is expected
    void checkLease4(isc::data::ConstElementPtr l, std::string ip,
                     uint32_t subnet_id, std::string hwaddr,
                     bool client_id_required) {
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

        ASSERT_TRUE(l->get("ip-address"));
        EXPECT_EQ(ip, l->get("ip-address")->stringValue());

        ASSERT_TRUE(l->get("subnet-id"));
        EXPECT_EQ(subnet_id, l->get("subnet-id")->intValue());

        ASSERT_TRUE(l->get("hw-address"));
        EXPECT_EQ(hwaddr, l->get("hw-address")->stringValue());

        // client-id may or may not appear
        if (client_id_required) {
            EXPECT_TRUE(l->get("client-id"));
        }

        // Check that other parameters are there.
        ASSERT_TRUE(l->contains("valid-lft"));
        ASSERT_TRUE(l->contains("cltt"));
        ASSERT_TRUE(l->contains("subnet-id"));
        ASSERT_TRUE(l->contains("state"));
        ASSERT_TRUE(l->contains("fqdn-fwd"));
        ASSERT_TRUE(l->contains("fqdn-rev"));
        ASSERT_TRUE(l->contains("hostname"));
        ASSERT_TRUE(l->contains("state"));

        // Check that there are no v6 specific fields
        ASSERT_FALSE(l->contains("prefix"));
        ASSERT_FALSE(l->contains("duid"));
        ASSERT_FALSE(l->contains("preferred-lft"));

        // Assuming that these values were used to create the lease.
        // If we ever want to test different values they will need to
        // be added as parameters to this function.
        EXPECT_EQ(HIGH_VALID_LIFETIME,
                  static_cast<uint32_t>(l->get("valid-lft")->intValue()));
        EXPECT_EQ(DEC_2030_TIME, l->get("cltt")->intValue());
    }

    /// @brief Check lease4 statistics.
    ///
    /// @param id Subnet id of the stats to check.
    /// @assigned The expected value of assigned addresses in subnet.
    /// @declined The expected value of declined addresses in subnet.
    void checkLease4Stats(isc::dhcp::SubnetID id, int32_t assigned, int32_t declined) {
        ASSERT_EQ(isc::stats::StatsMgr::instance().getObservation(
                isc::stats::StatsMgr::generateName("subnet", id,
                          "assigned-addresses"))->getInteger().first, assigned);

        ASSERT_EQ(isc::stats::StatsMgr::instance().getObservation(
                isc::stats::StatsMgr::generateName("subnet", id,
                          "declined-addresses"))->getInteger().first, declined);
    }

    /// @brief Check that lease4-add with missing parameters will fail.
    void testLease4AddMissingParams();

    /// @brief Verify that lease4-add can be rejected if parameters are
    /// specified, but have incorrect values.
    void testLease4AddBadParams();

    /// @brief Check that a simple, well formed lease4 can be added.
    void testLease4Add();

    /// @brief Check that a simple, well formed lease4 can be added.
    void testLease4AddDeclinedLeases();

    /// @brief Check that a lease4 is not added when it already exists.
    void testLease4AddExisting();

    /// @brief Check that subnet-id is optional. If not specified, Kea should
    /// select it on its own.
    void testLease4AddSubnetIdMissing();

    /// @brief Check that subnet-id is optional. If not specified, Kea should
    /// select it on its own.
    void testLease4AddSubnetIdMissingDeclinedLeases();

    /// @brief Check that subnet-id is optional. If not specified, Kea should
    /// select it on its own, but if there's no subnet for address being added,
    /// it should fail.
    void testLease4AddSubnetIdMissingBadAddr();

    /// @brief Check that the lease with negative expiration time is rejected.
    void testLease4AddNegativeExpireTime();

    /// @brief Check that the lease with negative cltt is rejected.
    void testLease4AddNegativeCltt();

    /// @brief Check that a well formed lease4 with tons of parameters can be
    /// added.
    void testLease4AddFullAddr();

    /// @brief Check that a well formed lease4 with a comment can be added.
    void testLease4AddComment();

    /// @brief Check that lease4-get can handle a situation when the query is
    /// broken (some required parameters are missing).
    void testLease4GetMissingParams();

    /// @brief Check that lease4-get sanitizes its input.
    void testLease4GetByAddrBadParam();

    /// @brief Check that lease4-get can handle a situation when the query is
    /// correctly formed, but the lease is not there.
    void testLease4GetByAddrNotFound();

    /// @brief Check that lease4-get can return a lease by address.
    void testLease4GetByAddr();

    /// @brief Check that lease4-get can handle a situation when the query is
    /// correctly formed, but the lease is not there.
    void testLease4GetByHWAddrNotFound();

    /// @brief Check that lease4-get can find a lease by hardware address.
    void testLease4GetByHWAddr();

    /// @brief Check that lease4-get can handle a situation when the query is
    /// correctly formed, but the lease is not there.
    void testLease4GetByClientIdNotFound();

    /// @brief Check that lease4-get can find a lease by client identifier.
    void testLease4GetByClientId();

    /// @brief Check that lease4-get-all returns all leases.
    void testLease4GetAll();

    /// @brief Check that lease4-get-all returns empty set if no leases are
    /// found.
    void testLease4GetAllNoLeases();

    /// @brief Check that lease4-get-all returns all leases for a subnet.
    void testLease4GetAllBySubnetId();

    /// @brief Check that lease4-get-all returns empty set when no leases are
    /// found.
    void testLease4GetAllBySubnetIdNoLeases();

    /// @brief Check that lease4-get-all returns leases from multiple subnets.
    void testLease4GetAllByMultipleSubnetIds();

    /// @brief Check that lease4-get-all checks its input arguments.
    void testLease4GetBySubnetIdInvalidArguments();

    /// @brief Check that multiple calls to lease4-get-page return all leases.
    void testLease4GetPaged();

    /// @brief Verifies that first page of IPv4 leases can be retrieved by
    /// specifying zero IPv4 address.
    void testLease4GetPagedZeroAddress();

    /// @brief Verifies that IPv6 address as a start address is rejected.
    void testLease4GetPagedIPv6Address();

    /// @brief Verifies that value of 'from' parameter other than 'start' or an
    /// IPv4 address is rejected.
    void testLease4GetPagedInvalidFrom();

    /// @brief Verifies that limit is mandatory.
    void testLease4GetPagedNoLimit();

    /// @brief Verifies that the limit must be a number.
    void testLease4GetPagedLimitNotNumber();

    /// @brief Check that lease4-get-by-hw-address can handle a situation when
    /// the query is broken (required parameter is missing).
    void testLease4GetByHwAddressParams();

    /// @brief Check that lease4-get-by-hw-address works as expected (find no
    /// lease).
    void testLease4GetByHwAddressFind0();

    /// @brief Check that lease4-get-by-hw-address works as expected (find two
    /// leases).
    void testLease4GetByHwAddressFind2();

    /// @brief Check that lease4-get-by-client-id can handle a situation when
    /// the query is broken (required parameter is missing).
    void testLease4GetByClientIdParams();

    /// @brief Check that lease4-get-by-client-id works as expected (find no
    /// lease).
    void testLease4GetByClientIdFind0();

    /// @brief Check that lease4-get-by-client-id works as expected (find two
    /// leases).
    void testLease4GetByClientIdFind2();

    /// @brief Verifies that the limit of 0 is rejected.
    void testLease4GetPagedLimitIsZero();

    /// @brief Check that lease4-get-by-hostname can handle a situation when
    /// the query is broken (required parameter is missing).
    void testLease4GetByHostnameParams();

    /// @brief Check that lease4-get-by-hostname works as expected (find no
    /// lease).
    void testLease4GetByHostnameFind0();

    /// @brief Check that lease4-get-by-hostname works as expected (find two
    /// leases).
    void testLease4GetByHostnameFind2();

    /// @brief Test checks if lease4-update handler refuses calls with missing
    /// parameters.
    void testLease4UpdateMissingParams();

    /// @brief Verify that lease4-update can be rejected if parameters are
    /// specified, but have incorrect values.
    void testLease4UpdateBadParams();

    /// @brief Check that lease4-update correctly handles case when there is no
    /// lease to be updated.
    void testLease4UpdateNoLease();

    /// @brief Check that a lease4 can be updated. We're changing hw-address and
    /// a hostname.
    void testLease4Update();

    /// @brief Check that a lease4 can be updated. We're changing hw-address and
    /// a hostname.
    void testLease4UpdateDeclinedLeases();

    /// @brief Check that a lease4 can be updated. We're changing hw-address and
    /// a hostname. The subnet-id is not specified.
    void testLease4UpdateNoSubnetId();

    /// @brief Check that a lease4 can be updated. We're changing hw-address and
    /// a hostname. The subnet-id is not specified.
    void testLease4UpdateNoSubnetIdDeclinedLeases();

    /// @brief Check that a lease4 is created if it doesn't exist during the
    /// update. To trigger this behavior 'force-create' boolean parameter must
    /// be included in the command.
    void testLease4UpdateForceCreate();

    /// @brief Check that a lease4 is created if it doesn't exist during the
    /// update. To trigger this behavior 'force-create' boolean parameter must
    /// be included in the command. The subnet-id is not specified, Kea will
    /// figure it out.
    void testLease4UpdateForceCreateNoSubnetId();

    /// @brief Check that lease4-update correctly handles case when the
    /// 'force-create' parameter is explicitly set to false.
    void testLease4UpdateDoNotForceCreate();

    /// @brief Check that a lease4 can be updated. We're adding a comment and an
    /// user context.
    void testLease4UpdateComment();

    /// @brief Check that lease4-del can handle a situation when the query is
    /// broken (some required parameters are missing).
    void testLease4DelMissingParams();

    /// @brief Check that lease4-del can handle a situation when the query is
    /// valid, but the lease is not there.
    void testLease4DelByAddrNotFound();

    /// @brief Check that lease4-del sanitizes its input.
    void testLease4DelByAddrBadParam();

    /// @brief Check that lease4-del can handle a situation when the query is
    /// correctly formed and the lease is deleted.
    void testLease4DelByAddr();

    /// @brief Check that lease4-del can handle a situation when the query is
    /// correctly formed and the lease is deleted.
    void testLease4DelByAddrDeclinedLeases();

    /// @brief Check that lease4-del can handle a situation when the query is
    /// correctly formed, but the lease is not there.
    void testLease4DelByHWAddrNotFound();

    /// @brief Check that lease4-del can find and delete a lease by hardware
    /// address.
    void testLease4DelByHWAddr();

    /// @brief Check that lease4-del can handle a situation when the query is
    /// correctly formed, but the lease is not there.
    void testLease4DelByClientIdNotFound();

    /// @brief Check that lease4-del can find and delete a lease by client
    /// identifier.
    void testLease4DelByClientId();

    /// @brief Check that lease4-wipe can remove leases.
    void testLease4Wipe();

    /// @brief Check that lease4-wipe can remove leases from all subnets at
    /// once.
    void testLease4WipeAll();

    /// @brief Check that lease4-wipe can remove leases from all subnets at
    /// once (when no parameters are specified).
    void testLease4WipeAllNoArgs();

    /// @brief Check that lease4-wipe properly reports when no leases were
    /// deleted.
    void testLease4WipeNoLeases();

    /// @brief Check that lease4-wipe properly reports when no leases were
    /// deleted.
    void testLease4WipeNoLeasesAll();

    /// @brief Check that an attempt to update a lease (set incorrect
    /// subnet-id) will fail.
    void testLease4BrokenUpdate();

    /// @brief Check that lease4-resend-ddns sanitizes its input.
    void testLease4ResendDdnsBadParam();

    /// @brief Check that lease4-resend-ddns does not generate an NCR for given
    /// lease when DDNS updating is disabled.
    void testLease4ResendDdnsDisabled();

    /// @brief Check that lease4-resend-ddns does not generate an NCR for when
    /// there is no matching lease.
    void testLease4ResendDdnsNoLease();

    /// @brief Check that lease4-resend-ddns does not generate an NCR for given
    /// lease when updates are enabled but Lease::hostname_ is blank.
    void testLease4ResendNoHostname();

    /// @brief Check that lease4-resend-ddns does not generate an NCR for given
    /// lease when updates are enabled, Lease::hostname_ is not blank, but both
    /// Lease::fqdn_fwd_ and fdqn_rev_ are false.
    void testLease4ResendNoDirectionsEnabled();

    /// @brief Check that lease4-resend-ddns can generate an NCR for given
    /// lease when updates are enabled, Lease::hostname_ is not blank, and at
    /// least one of Lease::fqdn_fwd_ or fdqn_rev_ are true.
    void testLease4ResendDdnsEnabled();

    /// @brief Check that lease4-del does (or does not) generate an NCR to
    /// remove DNS for a given lease based on lease content when DDNS updates
    /// are enabled.
    void testLease4DnsRemoveD2Enabled();

    /// @brief Check that lease4-del does not generate an NCR to remove DNS for
    /// a given lease based on lease content when DDNS updates are disabled.
    void testLease4DnsRemoveD2Disabled();

    /// @brief Verify that v4 lease add handles conflict as expected.
    void testLease4ConflictingAdd();

    /// @brief Verify that v4 lease update handles conflict as expected.
    void testLease4ConflictingUpdate();
};

void Lease4CmdsTest::testLease4AddMissingParams() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Everything missing. What sort of crap is that?
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just ip is not enough (subnet-id and hwaddr missing, although
    // subnet-id can now be figured out by Kea code)
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "            \"ip-address\": \"192.0.2.123\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'hw-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Better, but still no luck. (hwaddr missing).
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "            \"subnet-id\": 44,\n"
        "            \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'hw-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Close, but no cigars. (ip-address missing).
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "            \"subnet-id\": 44,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4AddBadParams() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // All params are there, but there's no subnet-id 123 configured.
    // (initLeaseMgr initialized subnet-id 44 for v4 and subnet-id 66 for v6).
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Invalid subnet-id: No IPv4 subnet with subnet-id=123 currently configured.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // This time the IP address does not belong to the subnet.
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"10.0.0.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "The address 10.0.0.1 does not belong to subnet 192.0.2.0/24, subnet-id=44";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // We don't use any of that bleeding edge nonsense in this museum. v4 only.
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "Non-IPv4 address specified: 2001:db8:1::1";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // currently defined states are 0,1 and 2. 123 is junk.
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"state\": 123\n"
        "    }\n"
        "}";
    exp_rsp = "Invalid state value: 123, supported values are: 0 (default), 1 "
        "(declined) and 2 (expired-reclaimed)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Bad user context: not a map.
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"user-context\": \"bad value\"\n"
        "    }\n"
        "}";
    exp_rsp = "Invalid user context '\"bad value\"' is not a JSON map.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Duplicated comment.
    txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"user-context\": { \"comment\": \"in user context\" },\n"
        "        \"comment\": \"direct\"\n"
        "    }\n"
        "}";
    exp_rsp = "Duplicated comment entry '\"direct\"' in user context "
        "'{ \"comment\": \"in user context\" }'";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4Add() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 192.0.2.202, subnet-id 44 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);

    // Make sure the lease has proper value set.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ(3, l->valid_lft_); // taken from subnet configuration
    EXPECT_FALSE(l->fqdn_fwd_);
    EXPECT_FALSE(l->fqdn_rev_);
    EXPECT_EQ("", l->hostname_);
    EXPECT_FALSE(l->getContext());

    // Test execution is fast. The cltt should be set to now. In some rare
    // cases we could have the seconds counter to tick, so having a value off
    // by one is ok.
    EXPECT_LE(abs(l->cltt_ - time(NULL)), 1);
    EXPECT_EQ(0, l->state_);
}

void Lease4CmdsTest::testLease4AddDeclinedLeases() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"state\": 1,\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 192.0.2.202, subnet-id 44 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 1, 1);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);

    // Make sure the lease have proper value set.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ(3, l->valid_lft_); // taken from subnet configuration
    EXPECT_FALSE(l->fqdn_fwd_);
    EXPECT_FALSE(l->fqdn_rev_);
    EXPECT_EQ("", l->hostname_);
    EXPECT_FALSE(l->getContext());

    // Test execution is fast. The cltt should be set to now. In some rare
    // cases we could have the seconds counter to tick, so having a value off
    // by one is ok.
    EXPECT_LE(abs(l->cltt_ - time(NULL)), 1);
    EXPECT_EQ(1, l->state_);
}

void Lease4CmdsTest::testLease4AddExisting() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease already exists.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);
}

void Lease4CmdsTest::testLease4AddSubnetIdMissing() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now send the command without subnet-id. Kea should select
    // the subnet id on its own.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 192.0.2.202, subnet-id 44 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);
    EXPECT_EQ(44, l->subnet_id_);
}

void Lease4CmdsTest::testLease4AddSubnetIdMissingDeclinedLeases() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now send the command without subnet-id. Kea should select
    // the subnet id on its own.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"state\": 1,\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 192.0.2.202, subnet-id 44 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 1, 1);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);
    EXPECT_EQ(44, l->subnet_id_);
}

void Lease4CmdsTest::testLease4AddSubnetIdMissingBadAddr() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now send the command without subnet-id. Kea should select
    // the subnet id on its own.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.55.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "subnet-id not specified and failed to find a subnet for "
                     "address 192.0.55.1";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease was not added.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.55.1"));
    ASSERT_FALSE(l);
}

void Lease4CmdsTest::testLease4AddNegativeExpireTime() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Add a lease with negative expiration time.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"expire\": -6218189367\n"
        "    }\n"
        "}";
    string exp_rsp = "expiration time must be positive for address 192.0.2.202";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease was not added.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_FALSE(l);
}

void Lease4CmdsTest::testLease4AddNegativeCltt() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Add a lease with negative cltt (expiration time - valid lifetime)
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"expire\": 123456,\n"
        "        \"valid-lft\": 123457"
        "    }\n"
        "}";
    string exp_rsp = "expiration time must be greater than valid lifetime for "
        "address 192.0.2.202";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease was not added.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_FALSE(l);
}

void Lease4CmdsTest::testLease4AddFullAddr() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"client-id\": \"01:02:03:04:05:06:07:08\",\n"
        "        \"valid-lft\": 1000,\n"
        "        \"expire\": 6218189367,\n"
        "        \"fqdn-fwd\": true,\n"
        "        \"fqdn-rev\": true,\n"
        "        \"hostname\": \"urania.example.org\",\n"
        "        \"user-context\": { \"foobar\": true }\n"
        "    }\n"
        "}";
    string exp_rsp = "Lease for address 192.0.2.202, subnet-id 44 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);
    EXPECT_EQ("192.0.2.202", l->addr_.toText());
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    ASSERT_TRUE(l->client_id_);
    EXPECT_EQ("01:02:03:04:05:06:07:08", l->client_id_->toText());
    // expire (6218189367) - valid_lft(1000)
    EXPECT_EQ(static_cast<time_t>(6218189367 - 1000), l->cltt_);
    EXPECT_EQ(true, l->fqdn_fwd_);
    EXPECT_EQ(true, l->fqdn_rev_);
    EXPECT_EQ("urania.example.org", l->hostname_);
    ASSERT_TRUE(l->getContext());
    EXPECT_EQ("{ \"foobar\": true }", l->getContext()->str());
}

void Lease4CmdsTest::testLease4AddComment() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"comment\": \"a comment\"\n"
        "    }\n"
            "}";
    string exp_rsp = "Lease for address 192.0.2.202, subnet-id 44 added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease is really there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.202"));
    ASSERT_TRUE(l);

    // Make sure the lease have proper value set.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    ASSERT_TRUE(l->getContext());
    EXPECT_EQ("{ \"comment\": \"a comment\" }", l->getContext()->str());
}

void Lease4CmdsTest::testLease4GetMissingParams() {
    // No parameters whatsoever. You want just a lease, any lease?
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Just the subnet-id won't cut it, either.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // We can't identify your laptop by color. Sorry, buddy.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"color\",\n"
        "        \"identifier\": \"blue\"\n"
        "    }\n"
        "}";
    exp_rsp = "Incorrect identifier type: color, the only supported values are: "
        "address, hw-address, duid";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Query by DUID is not supported in v4. Sorry.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"duid\",\n"
        "        \"identifier\": \"01:01:01:01:01:01\"\n"
        "    }\n"
        "}";
    exp_rsp = "Query by duid is not allowed in v4.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Identifier value is missing.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
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
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier\": \"01:02:03:04:05\"\n"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4GetByAddrBadParam() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Invalid family
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\""
        "    }\n"
        "}";
    string exp_rsp = "Invalid IPv4 address specified: 2001:db8:1::1";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // This is way off
    cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"221B Baker St.\""
        "    }\n"
        "}";
    exp_rsp = "Failed to convert string to address '221B Baker St.': Invalid argument";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4GetByAddrNotFound() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Invalid
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.5\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "Lease not found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

void Lease4CmdsTest::testLease4GetByAddr() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\""
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr lease = rsp->get("arguments");
    ASSERT_TRUE(lease);

    // Let's check if the response makes any sense.
    checkLease4(lease, "192.0.2.1", 44, "08:08:08:08:08:08", true);
}

void Lease4CmdsTest::testLease4GetByHWAddrNotFound() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // No such lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"01:02:03:04:05:06\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "Lease not found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

void Lease4CmdsTest::testLease4GetByHWAddr() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Invalid
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"08:08:08:08:08:08\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr lease = rsp->get("arguments");
    ASSERT_TRUE(lease);

    // Let's check if the response makes any sense.
    checkLease4(lease, "192.0.2.1", 44, "08:08:08:08:08:08", false);
}

void Lease4CmdsTest::testLease4GetByClientIdNotFound() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // No such lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"client-id\","
        "        \"identifier\": \"01:02:03:04\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "Lease not found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

void Lease4CmdsTest::testLease4GetByClientId() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    string cmd =
        "{\n"
        "    \"command\": \"lease4-get\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"client-id\","
        "        \"identifier\": \"42:42:42:42:42:42:42:42\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    // Now check that the lease parameters were indeed returned.
    ASSERT_TRUE(rsp);
    ConstElementPtr lease = rsp->get("arguments");
    ASSERT_TRUE(lease);

    // Let's check if the response makes any sense.
    checkLease4(lease, "192.0.2.1", 44, "08:08:08:08:08:08", false);
}

void Lease4CmdsTest::testLease4GetAll() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Query for all leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\"\n"
        "}";
    string exp_rsp = "4 IPv4 lease(s) found.";
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
    checkLease4(leases, "192.0.2.1", 44, "08:08:08:08:08:08", true);
    checkLease4(leases, "192.0.2.2", 44, "09:09:09:09:09:09", true);
    checkLease4(leases, "192.0.3.1", 88, "08:08:08:08:08:08", true);
    checkLease4(leases, "192.0.3.2", 88, "09:09:09:09:09:09", true);
}

void Lease4CmdsTest::testLease4GetAllNoLeases() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Query for all leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\"\n"
        "}";
    string exp_rsp = "0 IPv4 lease(s) found.";
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

void Lease4CmdsTest::testLease4GetAllBySubnetId() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Query for leases from subnet 44. Subnet 127 will be ignored because
    // it doesn't contain any leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\",\n"
        "    \"arguments\": {\n"
        "        \"subnets\": [ 44, 127 ]"
        "    }\n"
        "}";
    string exp_rsp = "2 IPv4 lease(s) found.";
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
    checkLease4(leases, "192.0.2.1", 44, "08:08:08:08:08:08", true);
    checkLease4(leases, "192.0.2.2", 44, "09:09:09:09:09:09", true);
}

void Lease4CmdsTest::testLease4GetAllBySubnetIdNoLeases() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Query for leases from subnet 44. Subnet 127 will be ignored because
    // it doesn't contain any leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\",\n"
        "    \"arguments\": {\n"
        "        \"subnets\": [ 44, 127 ]"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv4 lease(s) found.";
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

void Lease4CmdsTest::testLease4GetAllByMultipleSubnetIds() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Query for leases from subnet 44 and 88.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\",\n"
        "    \"arguments\": {\n"
        "        \"subnets\": [ 44, 88 ]"
        "    }\n"
        "}";
    string exp_rsp = "4 IPv4 lease(s) found.";
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
    checkLease4(leases, "192.0.2.1", 44, "08:08:08:08:08:08", true);
    checkLease4(leases, "192.0.2.2", 44, "09:09:09:09:09:09", true);
    checkLease4(leases, "192.0.3.1", 88, "08:08:08:08:08:08", true);
    checkLease4(leases, "192.0.3.2", 88, "09:09:09:09:09:09", true);
}

void Lease4CmdsTest::testLease4GetBySubnetIdInvalidArguments() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Subnets not specified in arguments.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\",\n"
        "    \"arguments\": {"
        "        \"foo\": 1\n"
        "    }\n"
        "}";
    string exp_rsp = "'subnets' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Subnets are not a list.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnets\": 1\n"
        "    }\n"
        "}";
    exp_rsp = "'subnets' parameter must be a list";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Subnets list must contain numbers.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-all\",\n"
        "    \"arguments\": {"
        "        \"subnets\": [ \"x\", \"y\" ]\n"
        "    }\n"
        "}";
    exp_rsp = "listed subnet identifiers must be numbers";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4GetPaged() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

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
            "    \"command\": \"lease4-get-page\",\n"
            "    \"arguments\": {"
            "        \"from\": \"" + last_address + "\","
            "        \"limit\": 2"
            "    }"
            "}";

        // For the first two pages we should get success. For the last
        // one an empty status code.
        ConstElementPtr rsp;
        if (i < 2) {
            string exp_rsp = "2 IPv4 lease(s) found.";
            rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

        } else {
            string exp_rsp = "0 IPv4 lease(s) found.";
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
                Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(IOAddress(last_address));
                ASSERT_TRUE(from_mgr);
                checkLease4(leases, last_address, from_mgr->subnet_id_,
                            from_mgr->hwaddr_->toText(false), true);
            }

        } else {
            // In the third iteration the page should be empty.
            EXPECT_EQ(0, page_count->intValue());
        }
    }

    // Check if all addresses were returned.
    EXPECT_EQ(1, lease_addresses.count("192.0.2.1"));
    EXPECT_EQ(1, lease_addresses.count("192.0.2.2"));
    EXPECT_EQ(1, lease_addresses.count("192.0.3.1"));
    EXPECT_EQ(1, lease_addresses.count("192.0.3.2"));
}

void Lease4CmdsTest::testLease4GetPagedZeroAddress() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"0.0.0.0\","
        "        \"limit\": 2"
        "    }"
        "}";

    string exp_rsp = "2 IPv4 lease(s) found.";
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);
}

void Lease4CmdsTest::testLease4GetPagedIPv6Address() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"2001:db8::1\","
        "        \"limit\": 2"
        "    }"
        "}";

    string exp_rsp = "'from' parameter value 2001:db8::1 is not an IPv4 address";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4GetPagedInvalidFrom() {
    // Initialize lease manager (false = v6, true = add leases)
    initLeaseMgr(false, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"foo\","
        "        \"limit\": 2"
        "    }"
        "}";

    string exp_rsp = "'from' parameter value is neither 'start' keyword "
        "nor a valid IPv4 address";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4GetPagedNoLimit() {
    // Initialize lease manager (false = v6, true = add leases)
    initLeaseMgr(false, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"start\""
        "    }"
        "}";

    string exp_rsp = "'limit' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4GetPagedLimitNotNumber() {
    // Initialize lease manager (false = v6, true = add leases)
    initLeaseMgr(false, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"start\","
        "        \"limit\": false"
        "    }"
        "}";

    string exp_rsp = "'limit' parameter must be a number";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4GetPagedLimitIsZero() {
    // Initialize lease manager (false = v6, true = add leases)
    initLeaseMgr(false, true);

    // Query for a page of leases.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-page\",\n"
        "    \"arguments\": {"
        "        \"from\": \"start\","
        "        \"limit\": 0"
        "    }"
        "}";

    string exp_rsp = "page size of retrieved leases must not be 0";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4GetByHwAddressParams() {
    // No parameters whatsoever.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hw-address\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "'hw-address' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // hw-address must be a string.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hw-address\",\n"
        "    \"arguments\": {"
        "        \"hw-address\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "'hw-address' parameter must be a string";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Simply bad value.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hw-address\",\n"
        "    \"arguments\": {"
        "        \"hw-address\": \"00::01:00:bc:0d:67\"\n"
        "    }\n"
        "}";
    exp_rsp = "two consecutive separators (':') specified in a decoded string";
    exp_rsp += " '00::01:00:bc:0d:67'";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4GetByHwAddressFind0() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // No such lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hw-address\",\n"
        "    \"arguments\": {"
        "        \"hw-address\": \"01:02:03:04:05:06\"\n"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv4 lease(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

void Lease4CmdsTest::testLease4GetByHwAddressFind2() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Get the lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hw-address\",\n"
        "    \"arguments\": {"
        "        \"hw-address\": \"08:08:08:08:08:08\"\n"
        "    }\n"
        "}";
    string exp_rsp = "2 IPv4 lease(s) found.";
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
    checkLease4(lease, "192.0.2.1", 44, "08:08:08:08:08:08", false);
    lease = leases->get(1);
    ASSERT_TRUE(lease);
    checkLease4(lease, "192.0.3.1", 88, "08:08:08:08:08:08", false);
}

void Lease4CmdsTest::testLease4GetByClientIdParams() {
    // No parameters whatsoever.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-client-id\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "'client-id' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // client-id must be a string.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-client-id\",\n"
        "    \"arguments\": {"
        "        \"client-id\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "'client-id' parameter must be a string";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Simply bad value.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-client-id\",\n"
        "    \"arguments\": {"
        "        \"client-id\": \"00::01:00:bc:0d:67\"\n"
        "    }\n"
        "}";
    exp_rsp = "two consecutive separators (':') specified in a decoded string";
    exp_rsp += " '00::01:00:bc:0d:67'";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4GetByClientIdFind0() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // No such lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-client-id\",\n"
        "    \"arguments\": {"
        "        \"client-id\": \"01:02:03:04\"\n"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv4 lease(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

void Lease4CmdsTest::testLease4GetByClientIdFind2() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Get the lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-client-id\",\n"
        "    \"arguments\": {"
        "        \"client-id\": \"42:42:42:42:42:42:42:42\"\n"
        "    }\n"
        "}";
    string exp_rsp = "2 IPv4 lease(s) found.";
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
    checkLease4(lease, "192.0.2.1", 44, "08:08:08:08:08:08", false);
    lease = leases->get(1);
    ASSERT_TRUE(lease);
    checkLease4(lease, "192.0.3.1", 88, "08:08:08:08:08:08", false);
}

void Lease4CmdsTest::testLease4GetByHostnameParams() {
    // No parameters whatsoever.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hostname\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "'hostname' parameter not specified";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // hostname must be a string.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": 1234\n"
        "    }\n"
        "}";
    exp_rsp = "'hostname' parameter must be a string";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // hostname must be not empty.
    cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"\"\n"
        "    }\n"
        "}";
    exp_rsp = "'hostname' parameter is empty";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4GetByHostnameFind0() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // No such lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"foo.bar\"\n"
        "    }\n"
        "}";
    string exp_rsp = "0 IPv4 lease(s) found.";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

void Lease4CmdsTest::testLease4GetByHostnameFind2() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Get the lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-get-by-hostname\",\n"
        "    \"arguments\": {"
        "        \"hostname\": \"Myhost.Example.Com.\"\n"
        "    }\n"
        "}";
    string exp_rsp = "4 IPv4 lease(s) found.";
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
    checkLease4(lease, "192.0.2.1", 44, "08:08:08:08:08:08", false);
    lease = leases->get(2);
    ASSERT_TRUE(lease);
    checkLease4(lease, "192.0.3.1", 88, "08:08:08:08:08:08", false);
}

void Lease4CmdsTest::testLease4UpdateMissingParams() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Everything missing. What sort of crap is that?
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Just ip is not enough (subnet-id and hwaddr missing, although
    // Kea can now figure out subnet-id on its own).
    txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "            \"ip-address\": \"192.0.2.123\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'hw-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Better, but still no luck. (hwaddr missing).
    txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "            \"subnet-id\": 44,\n"
        "            \"ip-address\": \"192.0.2.202\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'hw-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Close, but no cigars. (ip-address missing).
    txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "            \"subnet-id\": 44,\n"
        "            \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "missing parameter 'ip-address' (<string>:3:19)";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4UpdateBadParams() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // All params are there, but there's no subnet-id 123 configured.
    // (initLeaseMgr initialized subnet-id 44 for v4 and subnet-id 66 for v6).
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    string exp_rsp = "Invalid subnet-id: No IPv4 subnet with subnet-id=123 currently configured.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // This time the new IP address does not belong to the subnet.
    txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"10.0.0.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "The address 10.0.0.1 does not belong to subnet 192.0.2.0/24, subnet-id=44";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // We don't use any of that bleeding edge nonsense in this museum. v4 only.
    txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"2001:db8:1::1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\"\n"
        "    }\n"
        "}";
    exp_rsp = "Non-IPv4 address specified: 2001:db8:1::1";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Bad user context: not a map.
    txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"user-context\": \"bad value\"\n"
        "    }\n"
        "}";
    exp_rsp = "Invalid user context '\"bad value\"' is not a JSON map.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Duplicated comment.
    txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"user-context\": { \"comment\": \"in user context\" },\n"
        "        \"comment\": \"direct\"\n"
        "    }\n"
        "}";
    exp_rsp = "Duplicated comment entry '\"direct\"' in user context "
        "'{ \"comment\": \"in user context\" }'";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4UpdateNoLease() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "failed to update the lease with address 192.0.2.1 "
        "either because the lease has been deleted or it has changed in the "
        "database, in both cases a retry might succeed";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4Update() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure it's been updated.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

void Lease4CmdsTest::testLease4UpdateDeclinedLeases() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true, true);

    checkLease4Stats(44, 2, 2);

    checkLease4Stats(88, 2, 2);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 2, 1);

    checkLease4Stats(88, 2, 2);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure it's been updated.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

void Lease4CmdsTest::testLease4UpdateNoSubnetId() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure it's been updated.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

void Lease4CmdsTest::testLease4UpdateNoSubnetIdDeclinedLeases() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true, true);

    checkLease4Stats(44, 2, 2);

    checkLease4Stats(88, 2, 2);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"hostname\": \"newhostname.example.org\""
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 2, 1);

    checkLease4Stats(88, 2, 2);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure it's been updated.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

void Lease4CmdsTest::testLease4UpdateForceCreate() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"hostname\": \"newhostname.example.org\","
        "        \"force-create\": true"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure it contains expected values..
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

void Lease4CmdsTest::testLease4UpdateForceCreateNoSubnetId() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"hostname\": \"newhostname.example.org\","
        "        \"force-create\": true"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease added.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 0, 0);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure the subnet-id is figured out correctly.
    EXPECT_EQ(44, l->subnet_id_);

    // Make sure it contains expected values..
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("1a:1b:1c:1d:1e:1f", l->hwaddr_->toText(false));
    EXPECT_EQ("newhostname.example.org", l->hostname_);
    EXPECT_FALSE(l->getContext());
}

void Lease4CmdsTest::testLease4UpdateDoNotForceCreate() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"hostname\": \"newhostname.example.org\","
        "        \"force-create\": false"
        "    }\n"
        "}";
    string exp_rsp = "failed to update the lease with address 192.0.2.1 "
        "either because the lease has been deleted or it has changed in the "
        "database, in both cases a retry might succeed";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);
}

void Lease4CmdsTest::testLease4UpdateComment() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"42:42:42:42:42:42:42:42\",\n"
        "        \"comment\": \"a comment\",\n"
        "        \"user-context\": { \"foobar\": true }\n"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease updated.";
    testCommand(txt, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Now check that the lease is still there.
    Lease4Ptr l = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(l);

    // Make sure it's been updated.
    ASSERT_TRUE(l->hwaddr_);
    EXPECT_EQ("42:42:42:42:42:42:42:42", l->hwaddr_->toText(false));

    // Check user context.
    ConstElementPtr ctx = l->getContext();
    ASSERT_TRUE(ctx);
    EXPECT_EQ(2, ctx->size());
    ASSERT_TRUE(ctx->contains("comment"));
    EXPECT_EQ("\"a comment\"", ctx->get("comment")->str());
    ASSERT_TRUE(ctx->contains("foobar"));
    EXPECT_EQ("true", ctx->get("foobar")->str());
}

void Lease4CmdsTest::testLease4DelMissingParams() {
    // No parameters whatsoever. You want just a lease, any lease?
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "    }\n"
        "}";
    string exp_rsp = "Mandatory 'subnet-id' parameter missing.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Just the subnet-id won't cut it, either.
    cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // We can't identify your laptop by color. Sorry, buddy.
    cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"color\",\n"
        "        \"identifier\": \"blue\"\n"
        "    }\n"
        "}";
    exp_rsp = "Incorrect identifier type: color, the only supported values are: "
        "address, hw-address, duid";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Query by DUID is not supported in v4. Sorry.
    cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier-type\": \"duid\",\n"
        "        \"identifier\": \"01:01:01:01:01:01\"\n"
        "    }\n"
        "}";
    exp_rsp = "Delete by duid is not allowed in v4.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Identifier value is missing.
    cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
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
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 123,\n"
        "        \"identifier\": \"01:02:03:04:05\"\n"
        "    }\n"
        "}";
    exp_rsp = "No 'ip-address' provided and 'identifier-type' is either missing or not a string.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4DelByAddrNotFound() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Invalid
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.5\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease not found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);
}

void Lease4CmdsTest::testLease4DelByAddr() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\""
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease deleted.";
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 2, 0);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

void Lease4CmdsTest::testLease4DelByAddrDeclinedLeases() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true, true);

    checkLease4Stats(44, 2, 2);

    checkLease4Stats(88, 2, 2);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\""
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease deleted.";
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 1, 1);

    checkLease4Stats(88, 2, 2);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

void Lease4CmdsTest::testLease4DelByAddrBadParam() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Invalid family
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\""
        "    }\n"
        "}";
    string exp_rsp = "Invalid IPv4 address specified: 2001:db8:1::1";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

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

void Lease4CmdsTest::testLease4DelByHWAddrNotFound() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // No such lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"01:02:03:04:05:06\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease not found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Make sure the lease is still there.
    EXPECT_TRUE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

void Lease4CmdsTest::testLease4DelByHWAddr() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Invalid
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"hw-address\","
        "        \"identifier\": \"08:08:08:08:08:08\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease deleted.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 2, 0);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

void Lease4CmdsTest::testLease4DelByClientIdNotFound() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // No such lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"client-id\","
        "        \"identifier\": \"01:02:03:04\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease not found.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Make sure the lease is still there.
    EXPECT_TRUE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

void Lease4CmdsTest::testLease4DelByClientId() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Invalid
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"identifier-type\": \"client-id\","
        "        \"identifier\": \"42:42:42:42:42:42:42:42\","
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "IPv4 lease deleted.";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 1, 0);

    checkLease4Stats(88, 2, 0);

    // Make sure the lease is really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
}

void Lease4CmdsTest::testLease4Wipe() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 2 IPv4 lease(s) from subnet(s) 44";
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 2, 0);

    // Make sure the leases in subnet 44 are really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.2")));

    // Make sure the leases from subnet 88 are still there.
    EXPECT_TRUE(lmptr_->getLease4(IOAddress("192.0.3.1")));
    EXPECT_TRUE(lmptr_->getLease4(IOAddress("192.0.3.2")));
}

void Lease4CmdsTest::testLease4WipeAll() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 4 IPv4 lease(s) from subnet(s) 44 88";
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Make sure the leases in subnet 44 are really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.2")));

    // Make sure the leases from subnet 88 are gone, too.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.3.1")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.3.2")));
}

void Lease4CmdsTest::testLease4WipeAllNoArgs() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    checkLease4Stats(44, 2, 0);

    checkLease4Stats(88, 2, 0);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-wipe\"\n"
        "}";
    string exp_rsp = "Deleted 4 IPv4 lease(s) from subnet(s) 44 88";
    testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Make sure the leases in subnet 44 are really gone.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.1")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.2.2")));

    // Make sure the leases from subnet 88 are gone, too.
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.3.1")));
    EXPECT_FALSE(lmptr_->getLease4(IOAddress("192.0.3.2")));
}

void Lease4CmdsTest::testLease4WipeNoLeases() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 0 IPv4 lease(s) from subnet(s) 44";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);
}

void Lease4CmdsTest::testLease4WipeNoLeasesAll() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-wipe\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 0"
        "    }\n"
        "}";
    string exp_rsp = "Deleted 0 IPv4 lease(s) from subnet(s) 44 88";
    testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);

    checkLease4Stats(44, 0, 0);

    checkLease4Stats(88, 0, 0);
}

void Lease4CmdsTest::testLease4BrokenUpdate() {
    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Set the sanity checks level.
    CfgMgr::instance().getCurrentCfg()->getConsistency()
        ->setLeaseSanityCheck(CfgConsistency::LEASE_CHECK_FIX);

    // Now send the command.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 444,\n"
        "        \"ip-address\": \"192.0.2.202\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"force-create\": true\n"
        "    }\n"
        "}";
    string exp_rsp = "Invalid subnet-id: No IPv4 subnet with "
                     "subnet-id=444 currently configured.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4ResendDdnsBadParam() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Missing address parameter.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "    }\n"
        "}\n";

    string exp_rsp = "'ip-address' parameter is missing.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // Invalid address family.
    cmd =
        "{\n"
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"2001:db8:1::1\"\n"
        "    }\n"
        "}\n";

    exp_rsp = "Invalid IPv4 address specified: 2001:db8:1::1";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // ip-address is not an address at all.
    cmd =
        "{\n"
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"221B Baker St.\"\n"
        "    }\n"
        "}\n";

    exp_rsp = "'221B Baker St.' is not a valid IP address.";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}

void Lease4CmdsTest::testLease4ResendDdnsDisabled() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    disableD2();

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.5\""
        "    }\n"
        "}";

    string exp_rsp = "DDNS updating is not enabled";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
    // With D2 disabled there is no queue, size should come back as -1.
    EXPECT_EQ(ncrQueueSize(), -1);
}

void Lease4CmdsTest::testLease4ResendDdnsNoLease() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Invalid
    string cmd =
        "{\n"
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"192.0.2.5\"\n"
        "    }\n"
        "}\n";
    string exp_rsp = "No lease found for: 192.0.2.5";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_EMPTY, exp_rsp);
}

void Lease4CmdsTest::testLease4ResendNoHostname() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // NCR sender queue should be empty.
    ASSERT_EQ(ncrQueueSize(), 0);

    // Fetch the lease so we can replace the hostname with "".
    Lease4Ptr lease = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(lease);
    lease->hostname_ = "";
    lmptr_->updateLease4(lease);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\""
        "    }\n"
        "}";

    string exp_rsp = "Lease for: 192.0.2.1, has no hostname, nothing to update";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // There should not any NCRs queued.
    EXPECT_EQ(ncrQueueSize(), 0);
}

void Lease4CmdsTest::testLease4ResendNoDirectionsEnabled() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // NCR sender queue should be empty.
    ASSERT_EQ(ncrQueueSize(), 0);

    // Fetch the lease so we can replace the hostname with "".
    Lease4Ptr lease = lmptr_->getLease4(IOAddress("192.0.2.1"));
    ASSERT_TRUE(lease);
    lease->fqdn_fwd_ = false;
    lease->fqdn_rev_ = false;
    lmptr_->updateLease4(lease);

    // Query for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\""
        "    }\n"
        "}";

    string exp_rsp = "Neither forward nor reverse updates enabled for lease for: 192.0.2.1";
    ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    // There should not any NCRs queued.
    EXPECT_EQ(ncrQueueSize(), 0);
}

void Lease4CmdsTest::testLease4ResendDdnsEnabled() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

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
        "    \"command\": \"lease4-resend-ddns\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.2.1\""
        "    }\n"
        "}";

    // Expected response string.
    string exp_rsp = "NCR generated for: 192.0.2.1, hostname: myhost.example.com.";

    for (auto scenario : scenarios) {
        SCOPED_TRACE(scenario.description_);

        // Fetch the lease so we can update the DDNS direction flags.
        Lease4Ptr lease = lmptr_->getLease4(IOAddress("192.0.2.1"));
        ASSERT_TRUE(lease);
        lease->fqdn_rev_ = scenario.fqdn_rev_;
        lease->fqdn_fwd_ = scenario.fqdn_fwd_;
        lmptr_->updateLease4(lease);

        // Queue should be empty.
        ASSERT_EQ(ncrQueueSize(), 0);
        ConstElementPtr rsp = testCommand(cmd, CONTROL_RESULT_SUCCESS, exp_rsp);

        // We should have one entry in the queue.
        ASSERT_EQ(ncrQueueSize(), 1);
        verifyNameChangeRequest(CHG_ADD, scenario.fqdn_rev_, scenario.fqdn_fwd_,
                                "192.0.2.1", "myhost.example.com.");
    }
}

void Lease4CmdsTest::testLease4DnsRemoveD2Enabled() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

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
        Lease4Ptr lease = createLease4("192.0.2.8", 44, 0x08, 0x42);
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
            "    \"command\": \"lease4-del\","
            "    \"arguments\": {"
            "        \"ip-address\": \"192.0.2.8\"";

        if (!scenario.update_ddns_.empty()) {
            cmd << "," << scenario.update_ddns_;
        }

        cmd << "}}";

        // Execute the delete command.
        static_cast<void>(testCommand(cmd.str(), CONTROL_RESULT_SUCCESS, "IPv4 lease deleted."));

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
        lease = lmptr_->getLease4(lease->addr_);
        ASSERT_FALSE(lease);
    }
}

void Lease4CmdsTest::testLease4DnsRemoveD2Disabled() {
    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    disableD2();

    // Delete for valid, existing lease.
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {\n"
        "        \"ip-address\": \"192.0.2.8\",\n"
        "        \"update-ddns\": true\n"
        "    }\n"
        "}";

    // Let's create a lease with scenario attributes.
    Lease4Ptr lease = createLease4("192.0.2.8", 44, 0x08, 0x42);
    lease->hostname_ = "myhost.example.com.";
    lease->fqdn_rev_ = true;
    lease->fqdn_fwd_ = true;
    ASSERT_TRUE(lmptr_->addLease(lease));

    // NCR Queue is not enabled.
    ASSERT_EQ(ncrQueueSize(), -1);

    // Execute the delete command.
    static_cast<void>(testCommand(cmd, CONTROL_RESULT_SUCCESS, "IPv4 lease deleted."));

    // NCR Queue is not enabled.
    ASSERT_EQ(ncrQueueSize(), -1);

    // Lease should have been deleted.
    lease = lmptr_->getLease4(lease->addr_);
    ASSERT_FALSE(lease);
}

// Verify that v4 lease add handles conflict as expected.
void Lease4CmdsTest::testLease4ConflictingAdd() {
    MultiThreadingTest mt(true);

    // Initialize lease manager (false = v4, false = don't add leases)
    initLeaseMgr(false, false);

    // Make sure the lease doesn't exist.
    IOAddress addr("192.0.2.1");
    Lease4Ptr lease = lmptr_->getLease4(addr);
    ASSERT_FALSE(lease);

    // Verify stats show no leases.
    checkLease4Stats(44, 0, 0);

    // Lock the address.
    ResourceHandler4 resource_handler;
    ASSERT_TRUE(resource_handler.tryLock4(addr));

    // Now let's try to add the lease.
    string txt =
        "{\n"
        "    \"command\": \"lease4-add\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"1a:1b:1c:1d:1e:1f\",\n"
        "        \"comment\": \"a comment\"\n"
        "    }\n"
        "}";

    string exp_rsp = "ResourceBusy: IP address:192.0.2.1 could not be added.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Lease should not have been added.
    lease = lmptr_->getLease4(addr);
    ASSERT_FALSE(lease);

    // Stats should not have changed.
    checkLease4Stats(44, 0, 0);
}

void Lease4CmdsTest::testLease4ConflictingUpdate() {
    MultiThreadingTest mt(true);

    // Initialize lease manager (false = v4, true = add leases)
    initLeaseMgr(false, true);

    // Verify stats show no leases.
    checkLease4Stats(44, 2, 0);

    // Make sure the lease exists.
    IOAddress addr("192.0.2.1");
    Lease4Ptr lease = lmptr_->getLease4(addr);
    ASSERT_TRUE(lease);
    // Save a copy of the original lease.
    Lease4 original_lease = *lease;

    // Lock the address.
    ResourceHandler4 resource_handler;
    ASSERT_TRUE(resource_handler.tryLock4(addr));

    // Now let's try to update the lease.
    string txt =
        "{\n"
        "    \"command\": \"lease4-update\",\n"
        "    \"arguments\": {"
        "        \"subnet-id\": 44,\n"
        "        \"ip-address\": \"192.0.2.1\",\n"
        "        \"hw-address\": \"2a:2b:2c:2d:2e:2f\",\n"
        "        \"comment\": \"a comment\"\n"
        "    }\n"
        "}";

    string exp_rsp = "ResourceBusy: IP address:192.0.2.1 could not be updated.";
    testCommand(txt, CONTROL_RESULT_ERROR, exp_rsp);

    // Fetch the lease again.
    lease = lmptr_->getLease4(addr);
    ASSERT_TRUE(lease);

    // Lease should not have been changed.
    EXPECT_EQ(original_lease, *lease);
}

TEST_F(Lease4CmdsTest, lease4AddMissingParams) {
    testLease4AddMissingParams();
}

TEST_F(Lease4CmdsTest, lease4AddMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddMissingParams();
}

TEST_F(Lease4CmdsTest, lease4AddBadParams) {
    testLease4AddBadParams();
}

TEST_F(Lease4CmdsTest, lease4AddBadParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddBadParams();
}

TEST_F(Lease4CmdsTest, lease4Add) {
    testLease4Add();
}

TEST_F(Lease4CmdsTest, lease4AddMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4Add();
}

TEST_F(Lease4CmdsTest, lease4AddDeclinedLeases) {
    testLease4AddDeclinedLeases();
}

TEST_F(Lease4CmdsTest, lease4AddDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddDeclinedLeases();
}

TEST_F(Lease4CmdsTest, lease4AddExisting) {
    testLease4AddExisting();
}

TEST_F(Lease4CmdsTest, lease4AddExistingMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddExisting();
}

TEST_F(Lease4CmdsTest, lease4AddSubnetIdMissing) {
    testLease4AddSubnetIdMissing();
}

TEST_F(Lease4CmdsTest, lease4AddSubnetIdMissingMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddSubnetIdMissing();
}

TEST_F(Lease4CmdsTest, lease4AddSubnetIdMissingDeclinedLeases) {
    testLease4AddSubnetIdMissingDeclinedLeases();
}

TEST_F(Lease4CmdsTest, lease4AddSubnetIdMissingDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddSubnetIdMissingDeclinedLeases();
}

TEST_F(Lease4CmdsTest, lease4AddSubnetIdMissingBadAddr) {
    testLease4AddSubnetIdMissingBadAddr();
}

TEST_F(Lease4CmdsTest, lease4AddSubnetIdMissingBadAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddSubnetIdMissingBadAddr();
}

TEST_F(Lease4CmdsTest, lease4AddNegativeExpireTime) {
    testLease4AddNegativeExpireTime();
}

TEST_F(Lease4CmdsTest, lease4AddNegativeExpireTimeMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddNegativeExpireTime();
}

TEST_F(Lease4CmdsTest, lease4AddNegativeCltt) {
    testLease4AddNegativeCltt();
}

TEST_F(Lease4CmdsTest, lease4AddNegativeClttMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddNegativeCltt();
}

TEST_F(Lease4CmdsTest, lease4AddFullAddr) {
    testLease4AddFullAddr();
}

TEST_F(Lease4CmdsTest, lease4AddFullAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddFullAddr();
}

TEST_F(Lease4CmdsTest, lease4AddComment) {
    testLease4AddComment();
}

TEST_F(Lease4CmdsTest, lease4AddCommentMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4AddComment();
}

TEST_F(Lease4CmdsTest, lease4GetMissingParams) {
    testLease4GetMissingParams();
}

TEST_F(Lease4CmdsTest, lease4GetMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetMissingParams();
}

TEST_F(Lease4CmdsTest, lease4GetByAddrBadParam) {
    testLease4GetByAddrBadParam();
}

TEST_F(Lease4CmdsTest, lease4GetByAddrBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByAddrBadParam();
}

TEST_F(Lease4CmdsTest, lease4GetByAddrNotFound) {
    testLease4GetByAddrNotFound();
}

TEST_F(Lease4CmdsTest, lease4GetByAddrNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByAddrNotFound();
}

TEST_F(Lease4CmdsTest, lease4GetByAddr) {
    testLease4GetByAddr();
}

TEST_F(Lease4CmdsTest, lease4GetByAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByAddr();
}

TEST_F(Lease4CmdsTest, lease4GetByHWAddrNotFound) {
    testLease4GetByHWAddrNotFound();
}

TEST_F(Lease4CmdsTest, lease4GetByHWAddrNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByHWAddrNotFound();
}

TEST_F(Lease4CmdsTest, lease4GetByHWAddr) {
    testLease4GetByHWAddr();
}

TEST_F(Lease4CmdsTest, lease4GetByHWAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByHWAddr();
}

TEST_F(Lease4CmdsTest, lease4GetByClientIdNotFound) {
    testLease4GetByClientIdNotFound();
}

TEST_F(Lease4CmdsTest, lease4GetByClientIdNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByClientIdNotFound();
}

TEST_F(Lease4CmdsTest, lease4GetByClientId) {
    testLease4GetByClientId();
}

TEST_F(Lease4CmdsTest, lease4GetByClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByClientId();
}

TEST_F(Lease4CmdsTest, lease4GetAll) {
    testLease4GetAll();
}

TEST_F(Lease4CmdsTest, lease4GetAllMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetAll();
}

TEST_F(Lease4CmdsTest, lease4GetAllNoLeases) {
    testLease4GetAllNoLeases();
}

TEST_F(Lease4CmdsTest, lease4GetAllNoLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetAllNoLeases();
}

TEST_F(Lease4CmdsTest, lease4GetAllBySubnetId) {
    testLease4GetAllBySubnetId();
}

TEST_F(Lease4CmdsTest, lease4GetAllBySubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetAllBySubnetId();
}

TEST_F(Lease4CmdsTest, lease4GetAllBySubnetIdNoLeases) {
    testLease4GetAllBySubnetIdNoLeases();
}

TEST_F(Lease4CmdsTest, lease4GetAllBySubnetIdNoLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetAllBySubnetIdNoLeases();
}

TEST_F(Lease4CmdsTest, lease4GetAllByMultipleSubnetIds) {
    testLease4GetAllByMultipleSubnetIds();
}

TEST_F(Lease4CmdsTest, lease4GetAllByMultipleSubnetIdsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetAllByMultipleSubnetIds();
}

TEST_F(Lease4CmdsTest, lease4GetBySubnetIdInvalidArguments) {
    testLease4GetBySubnetIdInvalidArguments();
}

TEST_F(Lease4CmdsTest, lease4GetBySubnetIdInvalidArgumentsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetBySubnetIdInvalidArguments();
}

TEST_F(Lease4CmdsTest, lease4GetPaged) {
    testLease4GetPaged();
}

TEST_F(Lease4CmdsTest, lease4GetPagedMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetPaged();
}

TEST_F(Lease4CmdsTest, lease4GetPagedZeroAddress) {
    testLease4GetPagedZeroAddress();
}

TEST_F(Lease4CmdsTest, lease4GetPagedZeroAddressMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetPagedZeroAddress();
}

TEST_F(Lease4CmdsTest, lease4GetPagedIPv6Address) {
    testLease4GetPagedIPv6Address();
}

TEST_F(Lease4CmdsTest, lease4GetPagedIPv6AddressMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetPagedIPv6Address();
}

TEST_F(Lease4CmdsTest, lease4GetPagedInvalidFrom) {
    testLease4GetPagedInvalidFrom();
}

TEST_F(Lease4CmdsTest, lease4GetPagedInvalidFromMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetPagedInvalidFrom();
}

TEST_F(Lease4CmdsTest, lease4GetPagedNoLimit) {
    testLease4GetPagedNoLimit();
}

TEST_F(Lease4CmdsTest, lease4GetPagedNoLimitMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetPagedNoLimit();
}

TEST_F(Lease4CmdsTest, lease4GetPagedLimitNotNumber) {
    testLease4GetPagedLimitNotNumber();
}

TEST_F(Lease4CmdsTest, lease4GetPagedLimitNotNumberMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetPagedLimitNotNumber();
}

TEST_F(Lease4CmdsTest, lease4GetPagedLimitIsZero) {
    testLease4GetPagedLimitIsZero();
}

TEST_F(Lease4CmdsTest, lease4GetPagedLimitIsZeroMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetPagedLimitIsZero();
}

TEST_F(Lease4CmdsTest, lease4GetByHwAddressParams) {
    testLease4GetByHwAddressParams();
}

TEST_F(Lease4CmdsTest, lease4GetByHwAddressParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByHwAddressParams();
}

TEST_F(Lease4CmdsTest, lease4GetByHwAddressFind0) {
    testLease4GetByHwAddressFind0();
}

TEST_F(Lease4CmdsTest, lease4GetByHwAddressFind0MultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByHwAddressFind0();
}

TEST_F(Lease4CmdsTest, lease4GetByHwAddressFind2) {
    testLease4GetByHwAddressFind2();
}

TEST_F(Lease4CmdsTest, lease4GetByHwAddressFind2MultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByHwAddressFind2();
}

TEST_F(Lease4CmdsTest, lease4GetByClientIdParams) {
    testLease4GetByClientIdParams();
}

TEST_F(Lease4CmdsTest, lease4GetByClientIdParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByClientIdParams();
}

TEST_F(Lease4CmdsTest, lease4GetByClientIdFind0) {
    testLease4GetByClientIdFind0();
}

TEST_F(Lease4CmdsTest, lease4GetByClientIdFind0MultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByClientIdFind0();
}

TEST_F(Lease4CmdsTest, lease4GetByClientIdFind2) {
    testLease4GetByClientIdFind2();
}

TEST_F(Lease4CmdsTest, lease4GetByClientIdFind2MultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByClientIdFind2();
}

TEST_F(Lease4CmdsTest, lease4GetByHostnameParams) {
    testLease4GetByHostnameParams();
}

TEST_F(Lease4CmdsTest, lease4GetByHostnameParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByHostnameParams();
}

TEST_F(Lease4CmdsTest, lease4GetByHostnameFind0) {
    testLease4GetByHostnameFind0();
}

TEST_F(Lease4CmdsTest, lease4GetByHostnameFind0MultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByHostnameFind0();
}

TEST_F(Lease4CmdsTest, lease4GetByHostnameFind2) {
    testLease4GetByHostnameFind2();
}

TEST_F(Lease4CmdsTest, lease4GetByHostnameFind2MultiThreading) {
    MultiThreadingTest mt(true);
    testLease4GetByHostnameFind2();
}

TEST_F(Lease4CmdsTest, lease4UpdateMissingParams) {
    testLease4UpdateMissingParams();
}

TEST_F(Lease4CmdsTest, lease4UpdateMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateMissingParams();
}

TEST_F(Lease4CmdsTest, lease4UpdateBadParams) {
    testLease4UpdateBadParams();
}

TEST_F(Lease4CmdsTest, lease4UpdateBadParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateBadParams();
}

TEST_F(Lease4CmdsTest, lease4UpdateNoLease) {
    testLease4UpdateNoLease();
}

TEST_F(Lease4CmdsTest, lease4UpdateNoLeaseMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateNoLease();
}

TEST_F(Lease4CmdsTest, lease4Update) {
    testLease4Update();
}

TEST_F(Lease4CmdsTest, lease4UpdateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4Update();
}

TEST_F(Lease4CmdsTest, lease4UpdateDeclinedLeases) {
    testLease4UpdateDeclinedLeases();
}

TEST_F(Lease4CmdsTest, lease4UpdateDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateDeclinedLeases();
}

TEST_F(Lease4CmdsTest, lease4UpdateNoSubnetId) {
    testLease4UpdateNoSubnetId();
}

TEST_F(Lease4CmdsTest, lease4UpdateNoSubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateNoSubnetId();
}

TEST_F(Lease4CmdsTest, lease4UpdateNoSubnetIdDeclinedLeases) {
    testLease4UpdateNoSubnetIdDeclinedLeases();
}

TEST_F(Lease4CmdsTest, lease4UpdateNoSubnetIdDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateNoSubnetIdDeclinedLeases();
}

TEST_F(Lease4CmdsTest, lease4UpdateForceCreate) {
    testLease4UpdateForceCreate();
}

TEST_F(Lease4CmdsTest, lease4UpdateForceCreateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateForceCreate();
}

TEST_F(Lease4CmdsTest, lease4UpdateForceCreateNoSubnetId) {
    testLease4UpdateForceCreateNoSubnetId();
}

TEST_F(Lease4CmdsTest, lease4UpdateForceCreateNoSubnetIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateForceCreateNoSubnetId();
}

TEST_F(Lease4CmdsTest, lease4UpdateDoNotForceCreate) {
    testLease4UpdateDoNotForceCreate();
}

TEST_F(Lease4CmdsTest, lease4UpdateDoNotForceCreateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateDoNotForceCreate();
}

TEST_F(Lease4CmdsTest, lease4UpdateComment) {
    testLease4UpdateComment();
}

TEST_F(Lease4CmdsTest, lease4UpdateCommentMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4UpdateComment();
}

TEST_F(Lease4CmdsTest, lease4DelMissingParams) {
    testLease4DelMissingParams();
}

TEST_F(Lease4CmdsTest, lease4DelMissingParamsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelMissingParams();
}

TEST_F(Lease4CmdsTest, lease4DelByAddrNotFound) {
    testLease4DelByAddrNotFound();
}

TEST_F(Lease4CmdsTest, lease4DelByAddrNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByAddrNotFound();
}

TEST_F(Lease4CmdsTest, lease4DelByAddr) {
    testLease4DelByAddr();
}

TEST_F(Lease4CmdsTest, lease4DelByAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByAddr();
}

TEST_F(Lease4CmdsTest, lease4DelByAddrDeclinedLeases) {
    testLease4DelByAddrDeclinedLeases();
}

TEST_F(Lease4CmdsTest, lease4DelByAddrDeclinedLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByAddrDeclinedLeases();
}

TEST_F(Lease4CmdsTest, lease4DelByAddrBadParam) {
    testLease4DelByAddrBadParam();
}

TEST_F(Lease4CmdsTest, lease4DelByAddrBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByAddrBadParam();
}

TEST_F(Lease4CmdsTest, lease4DelByHWAddrNotFound) {
    testLease4DelByHWAddrNotFound();
}

TEST_F(Lease4CmdsTest, lease4DelByHWAddrNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByHWAddrNotFound();
}

TEST_F(Lease4CmdsTest, lease4DelByHWAddr) {
    testLease4DelByHWAddr();
}

TEST_F(Lease4CmdsTest, lease4DelByHWAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByHWAddr();
}

TEST_F(Lease4CmdsTest, lease4DelByClientIdNotFound) {
    testLease4DelByClientIdNotFound();
}

TEST_F(Lease4CmdsTest, lease4DelByClientIdNotFoundMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByClientIdNotFound();
}

TEST_F(Lease4CmdsTest, lease4DelByClientId) {
    testLease4DelByClientId();
}

TEST_F(Lease4CmdsTest, lease4DelByClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DelByClientId();
}

TEST_F(Lease4CmdsTest, lease4Wipe) {
    testLease4Wipe();
}

TEST_F(Lease4CmdsTest, lease4WipeMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4Wipe();
}

TEST_F(Lease4CmdsTest, lease4WipeAll) {
    testLease4WipeAll();
}

TEST_F(Lease4CmdsTest, lease4WipeAllMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4WipeAll();
}

TEST_F(Lease4CmdsTest, lease4WipeAllNoArgs) {
    testLease4WipeAllNoArgs();
}

TEST_F(Lease4CmdsTest, lease4WipeAllNoArgsMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4WipeAllNoArgs();
}

TEST_F(Lease4CmdsTest, lease4WipeNoLeases) {
    testLease4WipeNoLeases();
}

TEST_F(Lease4CmdsTest, lease4WipeNoLeasesMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4WipeNoLeases();
}

TEST_F(Lease4CmdsTest, lease4WipeNoLeasesAll) {
    testLease4WipeNoLeasesAll();
}

TEST_F(Lease4CmdsTest, lease4WipeNoLeasesAllMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4WipeNoLeasesAll();
}


TEST_F(Lease4CmdsTest, lease4BrokenUpdate) {
    testLease4BrokenUpdate();
}

TEST_F(Lease4CmdsTest, lease4BrokenUpdateMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4BrokenUpdate();
}

TEST_F(Lease4CmdsTest, lease4ResendDdnsBadParam) {
    testLease4ResendDdnsBadParam();
}

TEST_F(Lease4CmdsTest, lease4ResendDdnsBadParamMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4ResendDdnsBadParam();
}

TEST_F(Lease4CmdsTest, lease4ResendDdnsDisabled) {
    testLease4ResendDdnsDisabled();
}

TEST_F(Lease4CmdsTest, lease4ResendDdnsDisabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4ResendDdnsDisabled();
}

TEST_F(Lease4CmdsTest, lease4ResendDdnsNoLease) {
    testLease4ResendDdnsNoLease();
}

TEST_F(Lease4CmdsTest, lease4ResendDdnsNoLeaseMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4ResendDdnsNoLease();
}

TEST_F(Lease4CmdsTest, lease4ResendNoHostname) {
    testLease4ResendNoHostname();
}

TEST_F(Lease4CmdsTest, lease4ResendNoHostnameMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4ResendNoHostname();
}

TEST_F(Lease4CmdsTest, lease4ResendNoDirectionsEnabled) {
    testLease4ResendNoDirectionsEnabled();
}

TEST_F(Lease4CmdsTest, lease4ResendNoDirectionsEnabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4ResendNoDirectionsEnabled();
}

TEST_F(Lease4CmdsTest, lease4ResendDdnsEnabled) {
    testLease4ResendDdnsEnabled();
}

TEST_F(Lease4CmdsTest, lease4ResendDdnsEnabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4ResendDdnsEnabled();
}

TEST_F(Lease4CmdsTest, lease4DnsRemoveD2Enabled) {
    testLease4DnsRemoveD2Enabled();
}

TEST_F(Lease4CmdsTest, lease4DnsRemoveD2EnabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DnsRemoveD2Enabled();
}

TEST_F(Lease4CmdsTest, lease4DnsRemoveD2Disabled) {
    testLease4DnsRemoveD2Disabled();
}

TEST_F(Lease4CmdsTest, lease4DnsRemoveD2DisabledMultiThreading) {
    MultiThreadingTest mt(true);
    testLease4DnsRemoveD2Disabled();
}

TEST_F(Lease4CmdsTest, lease4ConflictingAddMultiThreading) {
    testLease4ConflictingAdd();
}

TEST_F(Lease4CmdsTest, lease4ConflictingUpdateMultiThreading) {
    testLease4ConflictingUpdate();
}

} // end of anonymous namespace
