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

// Simple test that checks the library really registers the commands.
TEST_F(LeaseCmdsTest, commands) {
    vector<string> cmds = {
        "lease4-add",               "lease6-add",
        "lease4-get",               "lease6-get",
        "lease4-get-all",           "lease6-get-all",
        "lease4-get-page",          "lease6-get-page",
        "lease4-get-by-hw-address",
        "lease4-get-by-client-id",  "lease6-get-by-duid",
        "lease4-get-by-hostname",   "lease6-get-by-hostname",
        "lease4-del",               "lease6-del",
        "lease4-update",            "lease6-update",
        "lease4-wipe",              "lease6-wipe",
        "lease4-resend-ddns",       "lease6-resend-ddns"
    };
    setFamily(AF_INET);
    testCommands(cmds);
}

void LeaseCmdsTest::testLeaseXDelBadUpdateDdnsParam() {
    string cmd =
        "{\n"
        "    \"command\": \"lease4-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"192.0.1.0\","
        "        \"update-ddns\": 77"
        "    }\n"
        "}";

    string exp_rsp = "'update-ddns' is not a boolean";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);

    cmd =
        "{\n"
        "    \"command\": \"lease6-del\",\n"
        "    \"arguments\": {"
        "        \"ip-address\": \"2001:db8:1::1\","
        "        \"update-ddns\": \"bogus\""
        "    }\n"
        "}";

    exp_rsp = "'update-ddns' is not a boolean";
    testCommand(cmd, CONTROL_RESULT_ERROR, exp_rsp);
}


// Check that the library can be loaded and unloaded multiple times.
TEST_F(LeaseCmdsTest, multipleLoads) {
    setFamily(AF_INET);
    testMultipleLoads();
}

TEST_F(LeaseCmdsTest, leaseXDelBadUpdateDdnsParam) {
    setFamily(AF_INET);
    testLeaseXDelBadUpdateDdnsParam();
}

TEST_F(LeaseCmdsTest, leaseXDelBadUpdateDdnsParamMultiThreading) {
    MultiThreadingTest mt(true);
    setFamily(AF_INET);
    testLeaseXDelBadUpdateDdnsParam();
}

} // end of anonymous namespace
