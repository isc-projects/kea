// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the ddns[46]_update callouts
/// installed by the ddns tuning hook library. In order to test the callouts
/// one must be able to pass to the load function its hook library parameters
/// because the only way to populate these parameters is by actually loading
/// the library via HooksManager::loadLibraries().

#include <config.h>

#include <asiolink/io_address.h>
#include <callout_unittests.h>
#include <database/audit_entry.h>
#include <ddns_tuning.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp/option_string.h>
#include <dhcpsrv/cfgmgr.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <hooks/hooks_manager.h>
#include <process/daemon.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>
#include <errno.h>

using namespace std;
using namespace isc;
using namespace isc::db;
using namespace isc::ddns_tuning;
using namespace isc::asiolink;
using namespace isc::hooks;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::process;
using namespace isc::test;
using namespace isc::ddns_tuning::test;

namespace isc {
namespace ddns_tuning {
namespace test {

// Baseclass mnemonic constants.
const std::string CalloutTest::empty_expr("");
const std::string CalloutTest::no_expr("<null>");
const std::string CalloutTest::no_suffix("");

void
CalloutTest::setSubnetExpression(SubnetPtr subnet, const std::string expression_str) {
    ASSERT_TRUE(subnet);
    ElementPtr user_context = Element::createMap();
    if (expression_str != no_expr) {
        ElementPtr ddns_tuning = Element::createMap();
        ddns_tuning->set("hostname-expr", Element::create(expression_str));
        user_context->set("ddns-tuning", ddns_tuning);
    }

    subnet->setContext(user_context);
}

void
CalloutTest::callDhcpSrvConfigured(SrvConfigPtr srv_config,
                                   CalloutHandle::CalloutNextStep expected_status) {
    // Make sure the callout is present.
    ASSERT_TRUE(HooksManager::calloutsPresent(hook_index_dhcp_srv_configured_));

    CalloutHandlePtr handle = HooksManager::createCalloutHandle();
    handle->setArgument("server_config", srv_config);

    // Execute the callout.
    ASSERT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_dhcp_srv_configured_, *handle));
    ASSERT_EQ(expected_status, handle->getStatus());
}

void
CalloutTest::callCbUpdated(SubnetPtr subnet) {
    // Make sure the callout is present.
    ASSERT_TRUE(HooksManager::calloutsPresent(hook_index_cb_updated_));

    // Get and setup the callout handle.
    CalloutHandlePtr handle = HooksManager::createCalloutHandle();
    AuditEntryCollectionPtr audit_entries(new AuditEntryCollection());
    if (subnet) {
        AuditEntryPtr audit_entry(new AuditEntry(subnet_obj_type_,
                                                 subnet->getId(),
                                                 AuditEntry::ModificationType::CREATE,
                                                 subnet->getModificationTime(),
                                                 1, "added audit entry"));
        audit_entries->insert(audit_entry);
    }

    // Add the audit_entries to the callout arguments.
    handle->setArgument("audit_entries", audit_entries);

    // Execute the callout.
    ASSERT_NO_THROW_LOG(HooksManager::callCallouts(hook_index_cb_updated_, *handle));
    ASSERT_EQ(0, handle->getStatus());
}

} // end of namespace isc::ddns_tuning::test
} // end of namespace isc::ddns_tuning
} // end of namespace isc
