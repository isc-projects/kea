// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify control command legal file entry
/// generation and callout: command_processed.
/// These tests assume the legal log library is linked in, not loaded.
/// This allows a great deal more flexibility in testing, such as overriding
/// and accessing the BackendStore::instance().
/// The load and unload callouts are exercised in ../libloadtests, which
/// actually uses the HooksManager to load and unload the library.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/subnet.h>
#include <exceptions/exceptions.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <test_utils.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace config;
using namespace data;
using namespace hooks;
using namespace legal_log;

extern "C" {
extern bool getOptionalString(ConstElementPtr& arguments, const string& name,
                              string& value);
extern bool getOptionalInt(ConstElementPtr& arguments, const string& name,
                           int64_t& value);
extern bool isPrefix(ConstElementPtr arguments);
extern int command_processed(CalloutHandle& handle);
extern void addDuration(ostringstream& os, ConstElementPtr& arguments);
extern void addContext(ostringstream& os, ConstElementPtr& arguments);
}

/// @brief Describes command name, arguments, and expected log string
struct ValidTest {
    const char* name;
    const char* arguments;
    const char* expected;
};

/// @brief A list of valid command/argument tuples which should produce log entries
ValidTest valid_tests[] =
{
    {
    "lease4-add",
    "{\"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\" }",
    "Administrator added a lease of address: 192.0.2.202 to a device with hardware address:"
    " 1a:1b:1c:1d:1e:1f"
    },
    {
    "lease4-add",
    "{\"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\","
    " \"client-id\": \"1234567890\" }",
    "Administrator added a lease of address: 192.0.2.202 to a device with hardware address:"
    " 1a:1b:1c:1d:1e:1f, client-id: 1234567890"
    },
    {
    "lease4-add",
    "{\"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\","
    " \"valid-lft\": 86400 }",
    "Administrator added a lease of address: 192.0.2.202 to a device with hardware address:"
    " 1a:1b:1c:1d:1e:1f for 1 days 0 hrs 0 mins 0 secs"
    },
    {
    "lease4-add",
    "{\"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\","
    " \"user-context\": { \"foo\": \"bar\" } }",
    "Administrator added a lease of address: 192.0.2.202 to a device with hardware address:"
    " 1a:1b:1c:1d:1e:1f, context: { \"foo\": \"bar\" }"
    },
    {
    "lease6-add",
    "{\"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234}",
    "Administrator added a lease of address: 2001:db8::3 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24"
    },
    {
    "lease6-add",
    "{\"subnet-id\": 66, \"type\": \"IA_PD\", \"ip-address\": \"2001:db8:abcd::\","
    " \"prefix-len\": 48, \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234}",
    "Administrator added a lease of prefix: 2001:db8:abcd::/48 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24"
    },
    {
    "lease6-add",
    "{\"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234,"
    " \"valid-lft\": 86400 }",
    "Administrator added a lease of address: 2001:db8::3 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24 for 1 days 0 hrs 0 mins 0 secs"
    },
    {
    "lease6-add",
    "{\"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234,"
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\"}",
    "Administrator added a lease of address: 2001:db8::3 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24, hardware address: 1a:1b:1c:1d:1e:1f"
    },
    {
    "lease6-add",
    "{\"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234,"
    " \"user-context\": { \"foo\": \"bar\" } }",
    "Administrator added a lease of address: 2001:db8::3 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24, context: { \"foo\": \"bar\" }"
    },
    {
    "lease4-del",
    "{\"subnet-id\": 44, \"ip-address\": \"192.0.2.202\"}",
    "Administrator deleted the lease for address: 192.0.2.202"
    },
    {
    "lease4-del",
    "{\"subnet-id\": 44, \"identifier-type\": \"hw-address\","
    " \"identifier\": \"1a:1b:1c:1d:1e:1f\"}",
    "Administrator deleted a lease for a device identified by: hw-address of 1a:1b:1c:1d:1e:1f"
    },
    {
    "lease6-del",
    "{\"subnet-id\": 66, \"ip-address\": \"2001:db8::3\"}",
    "Administrator deleted the lease for address: 2001:db8::3"
    },
    {
    "lease6-del",
    "{\"subnet-id\": 66, \"identifier-type\": \"duid\","
    " \"identifier\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\"}",
    "Administrator deleted a lease for a device identified by:"
    " duid of 1a:1b:1c:1d:1e:1f:20:21:22:23:24"
    },
    {
    "lease4-update",
    "{\"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\" }",
    "Administrator updated information on the lease of address:"
    " 192.0.2.202 to a device with hardware address: 1a:1b:1c:1d:1e:1f"
    },
    {
    "lease4-update",
    "{\"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\","
    " \"client-id\": \"686f776479\" }",
    "Administrator updated information on the lease of address:"
    " 192.0.2.202 to a device with hardware address:"
    " 1a:1b:1c:1d:1e:1f, client-id: 686f776479 (howdy)"
    },
    {
    "lease4-update",
    "{\"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\","
    " \"valid-lft\": 86400 }",
    "Administrator updated information on the lease of address:"
    " 192.0.2.202 to a device with hardware address:"
    " 1a:1b:1c:1d:1e:1f for 1 days 0 hrs 0 mins 0 secs"
    },
    {
    "lease4-update",
    "{\"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\","
    " \"comment\": \"Fred's box\" }",
    "Administrator updated information on the lease of address:"
    " 192.0.2.202 to a device with hardware address: 1a:1b:1c:1d:1e:1f,"
    " context: { \"comment\": \"Fred's box\" }"
    },
    {
    "lease6-update",
    "{\"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234}",
    "Administrator updated information on the lease of address:"
    " 2001:db8::3 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24"
    },
    {
    "lease6-update",
    "{\"subnet-id\": 66, \"type\": \"IA_PD\", \"ip-address\": \"2001:db8:abcd::\","
    " \"prefix-len\": 48, \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234}",
    "Administrator updated information on the lease of prefix:"
    " 2001:db8:abcd::/48 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24"
    },
    {
    "lease6-update",
    "{\"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"68:6f:77:64:79\", \"iaid\": 1234,"
    " \"valid-lft\": 86400 }",
    "Administrator updated information on the lease of address:"
    " 2001:db8::3 to a device with DUID:"
    " 68:6f:77:64:79 for 1 days 0 hrs 0 mins 0 secs"
    },
    {
    "lease6-update",
    "{\"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234,"
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\"}",
    "Administrator updated information on the lease of address:"
    " 2001:db8::3 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24, hardware address: 1a:1b:1c:1d:1e:1f"
    },
    {
    "lease6-update",
    "{\"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234,"
    " \"comment\": \"Fred's box\" }",
    "Administrator updated information on the lease of address:"
    " 2001:db8::3 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24,"
    " context: { \"comment\": \"Fred's box\" }"
    },
    {
    "lease4-del",
    "{\"ip-address\": \"192.0.2.202\"}",
    "Administrator deleted the lease for address: 192.0.2.202"
    },
    {
    "lease4-del",
    "{\"identifier-type\": \"hw-address\","
    " \"identifier\": \"1a:1b:1c:1d:1e:1f\"}",
    "Administrator deleted a lease for a device identified by: hw-address of 1a:1b:1c:1d:1e:1f"
    },
    {
    "lease6-del",
    "{\"ip-address\": \"2001:db8::3\"}",
    "Administrator deleted the lease for address: 2001:db8::3"
    },
    {
    "lease6-del",
    "{\"identifier-type\": \"duid\","
    " \"identifier\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\"}",
    "Administrator deleted a lease for a device identified by:"
    " duid of 1a:1b:1c:1d:1e:1f:20:21:22:23:24"
    },
    {
    "lease6-bulk-apply",
    "{\"leases\": [{\"subnet-id\": 66, \"ip-address\": \"2001:db8:1::1\","
    " \"duid\": \"11:11:11:11:11:11\", \"iaid\": 1234}]}",
    "Administrator updated information on the lease of address: 2001:db8:1::1 to a device with DUID: 11:11:11:11:11:11"
    },
    {
    "lease6-bulk-apply",
    "{\"deleted-leases\": [{\"ip-address\": \"2001:db8:1::3\", \"type\": \"IA_NA\"}]}",
    "Administrator deleted the lease for address: 2001:db8:1::3"
    },
    {
    "lease6-bulk-apply",
    "{\"leases\": [{\"subnet-id\": 66,\"ip-address\": \"2001:db8:1::1\","
    " \"duid\": \"11:11:11:11:11:11\", \"iaid\": 1234},"
    "{\"subnet-id\": 66, \"ip-address\": \"2001:db8:1::2\","
    " \"duid\": \"22:22:22:22:22:22\", \"iaid\": 1234,"
    " \"user-context\": {\"ISC\": {\"relay-info\": [{"
    " \"remote-id\": \"010203040506\", \"relay-id\": \"6464646464646464\"}]}}}]}",
    "Administrator updated information on the lease of address: 2001:db8:1::1 to a device with DUID: 11:11:11:11:11:11\n"
    "Administrator updated information on the lease of address: 2001:db8:1::2 to a device with DUID: 22:22:22:22:22:22, context: { \"ISC\": { \"relay-info\": [ { \"relay-id\": \"6464646464646464\", \"remote-id\": \"010203040506\" } ] } }"
    },
    {
    "lease6-bulk-apply",
    "{\"deleted-leases\": [{\"ip-address\": \"2001:db8:1::3\", \"type\": \"IA_NA\"},"
    "{\"ip-address\": \"2001:db8:1::4\", \"type\": \"IA_NA\"}]}",
    "Administrator deleted the lease for address: 2001:db8:1::3\n"
    "Administrator deleted the lease for address: 2001:db8:1::4"
    },
    {
    "lease6-bulk-apply",
    "{\"leases\": [{\"subnet-id\": 66,\"ip-address\": \"2001:db8:1::1\","
    " \"duid\": \"11:11:11:11:11:11\", \"iaid\": 1234},"
    "{\"subnet-id\": 66, \"ip-address\": \"2001:db8:1::2\","
    " \"duid\": \"22:22:22:22:22:22\", \"iaid\": 1234,"
    " \"user-context\": {\"ISC\": {\"relay-info\": [{"
    " \"remote-id\": \"010203040506\", \"relay-id\": \"6464646464646464\"}]}}}],"
    " \"deleted-leases\": [{\"ip-address\": \"2001:db8:1::3\", \"type\": \"IA_NA\"},"
    "{\"ip-address\": \"2001:db8:1::4\", \"type\": \"IA_NA\"}]}",
    "Administrator deleted the lease for address: 2001:db8:1::3\n"
    "Administrator deleted the lease for address: 2001:db8:1::4\n"
    "Administrator updated information on the lease of address: 2001:db8:1::1 to a device with DUID: 11:11:11:11:11:11\n"
    "Administrator updated information on the lease of address: 2001:db8:1::2 to a device with DUID: 22:22:22:22:22:22, context: { \"ISC\": { \"relay-info\": [ { \"relay-id\": \"6464646464646464\", \"remote-id\": \"010203040506\" } ] } }"
    },
    {
    "lease4-add",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\" }",
    "HA partner added a lease of address: 192.0.2.202 to a device with hardware address:"
    " 1a:1b:1c:1d:1e:1f"
    },
    {
    "lease4-add",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\","
    " \"client-id\": \"1234567890\" }",
    "HA partner added a lease of address: 192.0.2.202 to a device with hardware address:"
    " 1a:1b:1c:1d:1e:1f, client-id: 1234567890"
    },
    {
    "lease4-add",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\","
    " \"valid-lft\": 86400 }",
    "HA partner added a lease of address: 192.0.2.202 to a device with hardware address:"
    " 1a:1b:1c:1d:1e:1f for 1 days 0 hrs 0 mins 0 secs"
    },
    {
    "lease4-add",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\","
    " \"user-context\": { \"foo\": \"bar\" } }",
    "HA partner added a lease of address: 192.0.2.202 to a device with hardware address:"
    " 1a:1b:1c:1d:1e:1f, context: { \"foo\": \"bar\" }"
    },
    {
    "lease6-add",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234}",
    "HA partner added a lease of address: 2001:db8::3 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24"
    },
    {
    "lease6-add",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 66, \"type\": \"IA_PD\", \"ip-address\": \"2001:db8:abcd::\","
    " \"prefix-len\": 48, \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234}",
    "HA partner added a lease of prefix: 2001:db8:abcd::/48 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24"
    },
    {
    "lease6-add",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234,"
    " \"valid-lft\": 86400 }",
    "HA partner added a lease of address: 2001:db8::3 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24 for 1 days 0 hrs 0 mins 0 secs"
    },
    {
    "lease6-add",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234,"
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\"}",
    "HA partner added a lease of address: 2001:db8::3 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24, hardware address: 1a:1b:1c:1d:1e:1f"
    },
    {
    "lease6-add",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234,"
    " \"user-context\": { \"foo\": \"bar\" } }",
    "HA partner added a lease of address: 2001:db8::3 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24, context: { \"foo\": \"bar\" }"
    },
    {
    "lease4-del",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 44, \"ip-address\": \"192.0.2.202\"}",
    "HA partner deleted the lease for address: 192.0.2.202"
    },
    {
    "lease4-del",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 44, \"identifier-type\": \"hw-address\","
    " \"identifier\": \"1a:1b:1c:1d:1e:1f\"}",
    "HA partner deleted a lease for a device identified by: hw-address of 1a:1b:1c:1d:1e:1f"
    },
    {
    "lease6-del",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 66, \"ip-address\": \"2001:db8::3\"}",
    "HA partner deleted the lease for address: 2001:db8::3"
    },
    {
    "lease6-del",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 66, \"identifier-type\": \"duid\","
    " \"identifier\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\"}",
    "HA partner deleted a lease for a device identified by:"
    " duid of 1a:1b:1c:1d:1e:1f:20:21:22:23:24"
    },
    {
    "lease4-update",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\" }",
    "HA partner updated information on the lease of address:"
    " 192.0.2.202 to a device with hardware address: 1a:1b:1c:1d:1e:1f"
    },
    {
    "lease4-update",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\","
    " \"client-id\": \"686f776479\" }",
    "HA partner updated information on the lease of address:"
    " 192.0.2.202 to a device with hardware address:"
    " 1a:1b:1c:1d:1e:1f, client-id: 686f776479 (howdy)"
    },
    {
    "lease4-update",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\","
    " \"valid-lft\": 86400 }",
    "HA partner updated information on the lease of address:"
    " 192.0.2.202 to a device with hardware address:"
    " 1a:1b:1c:1d:1e:1f for 1 days 0 hrs 0 mins 0 secs"
    },
    {
    "lease4-update",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 44, \"ip-address\": \"192.0.2.202\","
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\","
    " \"comment\": \"Fred's box\" }",
    "HA partner updated information on the lease of address:"
    " 192.0.2.202 to a device with hardware address: 1a:1b:1c:1d:1e:1f,"
    " context: { \"comment\": \"Fred's box\" }"
    },
    {
    "lease6-update",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234}",
    "HA partner updated information on the lease of address:"
    " 2001:db8::3 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24"
    },
    {
    "lease6-update",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 66, \"type\": \"IA_PD\", \"ip-address\": \"2001:db8:abcd::\","
    " \"prefix-len\": 48, \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234}",
    "HA partner updated information on the lease of prefix:"
    " 2001:db8:abcd::/48 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24"
    },
    {
    "lease6-update",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"68:6f:77:64:79\", \"iaid\": 1234,"
    " \"valid-lft\": 86400 }",
    "HA partner updated information on the lease of address:"
    " 2001:db8::3 to a device with DUID:"
    " 68:6f:77:64:79 for 1 days 0 hrs 0 mins 0 secs"
    },
    {
    "lease6-update",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234,"
    " \"hw-address\": \"1a:1b:1c:1d:1e:1f\"}",
    "HA partner updated information on the lease of address:"
    " 2001:db8::3 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24, hardware address: 1a:1b:1c:1d:1e:1f"
    },
    {
    "lease6-update",
    "{\"origin\": \"ha-partner\", \"subnet-id\": 66, \"ip-address\": \"2001:db8::3\","
    " \"duid\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\", \"iaid\": 1234,"
    " \"comment\": \"Fred's box\" }",
    "HA partner updated information on the lease of address:"
    " 2001:db8::3 to a device with DUID:"
    " 1a:1b:1c:1d:1e:1f:20:21:22:23:24,"
    " context: { \"comment\": \"Fred's box\" }"
    },
    {
    "lease4-del",
    "{\"origin\": \"ha-partner\", \"ip-address\": \"192.0.2.202\"}",
    "HA partner deleted the lease for address: 192.0.2.202"
    },
    {
    "lease4-del",
    "{\"origin\": \"ha-partner\", \"identifier-type\": \"hw-address\","
    " \"identifier\": \"1a:1b:1c:1d:1e:1f\"}",
    "HA partner deleted a lease for a device identified by: hw-address of 1a:1b:1c:1d:1e:1f"
    },
    {
    "lease6-del",
    "{\"origin\": \"ha-partner\", \"ip-address\": \"2001:db8::3\"}",
    "HA partner deleted the lease for address: 2001:db8::3"
    },
    {
    "lease6-del",
    "{\"origin\": \"ha-partner\", \"identifier-type\": \"duid\","
    " \"identifier\": \"1a:1b:1c:1d:1e:1f:20:21:22:23:24\"}",
    "HA partner deleted a lease for a device identified by:"
    " duid of 1a:1b:1c:1d:1e:1f:20:21:22:23:24"
    },
    {
    "lease6-bulk-apply",
    "{\"origin\": \"ha-partner\", \"leases\": [{\"subnet-id\": 66, \"ip-address\": \"2001:db8:1::1\","
    " \"duid\": \"11:11:11:11:11:11\", \"iaid\": 1234}]}",
    "HA partner updated information on the lease of address: 2001:db8:1::1 to a device with DUID: 11:11:11:11:11:11"
    },
    {
    "lease6-bulk-apply",
    "{\"origin\": \"ha-partner\", \"deleted-leases\": [{\"ip-address\": \"2001:db8:1::3\", \"type\": \"IA_NA\"}]}",
    "HA partner deleted the lease for address: 2001:db8:1::3"
    },
    {
    "lease6-bulk-apply",
    "{\"origin\": \"ha-partner\", \"leases\": [{\"subnet-id\": 66,\"ip-address\": \"2001:db8:1::1\","
    " \"duid\": \"11:11:11:11:11:11\", \"iaid\": 1234},"
    "{\"subnet-id\": 66, \"ip-address\": \"2001:db8:1::2\","
    " \"duid\": \"22:22:22:22:22:22\", \"iaid\": 1234,"
    " \"user-context\": {\"ISC\": {\"relay-info\": [{"
    " \"remote-id\": \"010203040506\", \"relay-id\": \"6464646464646464\"}]}}}]}",
    "HA partner updated information on the lease of address: 2001:db8:1::1 to a device with DUID: 11:11:11:11:11:11\n"
    "HA partner updated information on the lease of address: 2001:db8:1::2 to a device with DUID: 22:22:22:22:22:22, context: { \"ISC\": { \"relay-info\": [ { \"relay-id\": \"6464646464646464\", \"remote-id\": \"010203040506\" } ] } }"
    },
    {
    "lease6-bulk-apply",
    "{\"origin\": \"ha-partner\", \"deleted-leases\": [{\"ip-address\": \"2001:db8:1::3\", \"type\": \"IA_NA\"},"
    "{\"ip-address\": \"2001:db8:1::4\", \"type\": \"IA_NA\"}]}",
    "HA partner deleted the lease for address: 2001:db8:1::3\n"
    "HA partner deleted the lease for address: 2001:db8:1::4"
    },
    {
    "lease6-bulk-apply",
    "{\"origin\": \"ha-partner\", \"leases\": [{\"subnet-id\": 66,\"ip-address\": \"2001:db8:1::1\","
    " \"duid\": \"11:11:11:11:11:11\", \"iaid\": 1234},"
    "{\"subnet-id\": 66, \"ip-address\": \"2001:db8:1::2\","
    " \"duid\": \"22:22:22:22:22:22\", \"iaid\": 1234,"
    " \"user-context\": {\"ISC\": {\"relay-info\": [{"
    " \"remote-id\": \"010203040506\", \"relay-id\": \"6464646464646464\"}]}}}],"
    " \"deleted-leases\": [{\"ip-address\": \"2001:db8:1::3\", \"type\": \"IA_NA\"},"
    "{\"ip-address\": \"2001:db8:1::4\", \"type\": \"IA_NA\"}]}",
    "HA partner deleted the lease for address: 2001:db8:1::3\n"
    "HA partner deleted the lease for address: 2001:db8:1::4\n"
    "HA partner updated information on the lease of address: 2001:db8:1::1 to a device with DUID: 11:11:11:11:11:11\n"
    "HA partner updated information on the lease of address: 2001:db8:1::2 to a device with DUID: 22:22:22:22:22:22, context: { \"ISC\": { \"relay-info\": [ { \"relay-id\": \"6464646464646464\", \"remote-id\": \"010203040506\" } ] } }"
    },
    {NULL,NULL,NULL}
};

namespace {

// Exercises the getOptionString() function
TEST(CommandCalloutFuncs, getOptionalStringTest) {
    ConstElementPtr arguments;
    ASSERT_NO_THROW(arguments = Element::fromJSON("{ \"foo\": \"bar\", \"num\" : 3 }"));

    string value;
    bool ret = false;

    // Should find the value "bar" for "foo"
    ASSERT_NO_THROW(ret = getOptionalString(arguments, "foo", value));
    EXPECT_TRUE(ret);
    EXPECT_EQ("bar", value);

    // Should not find a value for "not-there"
    ASSERT_NO_THROW(ret = getOptionalString(arguments, "not-there", value));
    EXPECT_FALSE(ret);
    EXPECT_EQ("", value);

    // Should not find a string when it is an integer"
    ASSERT_NO_THROW(ret = getOptionalString(arguments, "num", value));
    EXPECT_FALSE(ret);
    EXPECT_EQ("", value);

}

// Exercises the getOptionInt() function
TEST(CommandCalloutFuncs, getOptionalIntTest) {
    ConstElementPtr arguments;
    ASSERT_NO_THROW(arguments = Element::fromJSON("{ \"foo\": \"bar\", \"num\" : 3 }"));

    int64_t value;
    bool ret = false;

    // Should find the value 3 for "num"
    ASSERT_NO_THROW(ret = getOptionalInt(arguments, "num", value));
    EXPECT_TRUE(ret);
    EXPECT_EQ(3, value);

    // Should not an integer for "foo"
    ASSERT_NO_THROW(ret = getOptionalInt(arguments, "foo", value));
    EXPECT_FALSE(ret);
    EXPECT_EQ(0, value);

    // Should not an integer for "not-there"
    ASSERT_NO_THROW(ret = getOptionalInt(arguments, "not-there", value));
    EXPECT_FALSE(ret);
    EXPECT_EQ(0, value);

}

// Exercises the isPrefix() function
TEST(CommandCalloutFuncs, isPrefixTest) {
    ConstElementPtr arguments;
    bool ret = false;

    // Should not be a prefix if type isn't there
    ASSERT_NO_THROW(arguments = Element::fromJSON("{ \"foo\": \"bar\" }"));
    ASSERT_NO_THROW(ret = isPrefix(arguments));
    EXPECT_FALSE(ret);

    // Should not be a prefix if type is there but isn't "IA_PD"
    ASSERT_NO_THROW(arguments = Element::fromJSON("{ \"type\": \"monkey\" }"));
    ASSERT_NO_THROW(ret = isPrefix(arguments));
    EXPECT_FALSE(ret);

    // Should be a prefix if type is there and is "IA_PD"
    ASSERT_NO_THROW(arguments = Element::fromJSON("{ \"type\": \"IA_PD\" }"));
    ASSERT_NO_THROW(ret = isPrefix(arguments));
    EXPECT_TRUE(ret);

    // Should be a prefix if type is there and is "2"
    ASSERT_NO_THROW(arguments = Element::fromJSON("{ \"type\": \"2\" }"));
    ASSERT_NO_THROW(ret = isPrefix(arguments));
    EXPECT_TRUE(ret);
}

// Exercises the addDuration() function
TEST_F(CalloutTest, addDurationTest) {
    ASSERT_NO_THROW(BackendStore::instance().reset(new TestableRotatingFile(time_)));

    // Should generate duration text of 1 day based on valid-lft
    ConstElementPtr arguments;
    ASSERT_NO_THROW(arguments = Element::fromJSON("{ \"valid-lft\": 86400 }"));
    ostringstream os;
    ASSERT_NO_THROW(addDuration(os, arguments));
    EXPECT_EQ(os.str(), " for 1 days 0 hrs 0 mins 0 secs");

    // Clear the stream
    os.str("");

    // Should not generate duration text.
    ASSERT_NO_THROW(arguments = Element::fromJSON("{ \"some-other\": 86400 }"));
    ASSERT_NO_THROW(addDuration(os, arguments));
    EXPECT_EQ(os.str(), "");

    // Should have a duration of 2 days based on expire timestamp.
    int64_t expire = BackendStore::instance()->now().tv_sec + 172800;
    os.str("");
    os << "{ \"expire\":" << expire << "}";
    ASSERT_NO_THROW(arguments = Element::fromJSON(os.str()));

    os.str("");
    ASSERT_NO_THROW(addDuration(os, arguments));
    EXPECT_EQ(os.str(), " for 2 days 0 hrs 0 mins 0 secs");
}

// Exercises the addContext() function
TEST_F(CalloutTest, addContext) {
    ASSERT_NO_THROW(BackendStore::instance().reset(new TestableRotatingFile(time_)));

    // Should not generate user context text.
    string args = "{ \"some-other\": 86400 }";
    ConstElementPtr arguments;
    ASSERT_NO_THROW(arguments = Element::fromJSON(args));
    ostringstream os;
    ASSERT_NO_THROW(addContext(os, arguments));
    EXPECT_EQ(os.str(), "");

    // Should generate user context text.
    args = "{ \"user-context\": { \"foobar\": 1234 } }";
    ASSERT_NO_THROW(arguments = Element::fromJSON(args));
    ASSERT_NO_THROW(addContext(os, arguments));
    EXPECT_EQ(os.str(), ", context: { \"foobar\": 1234 }");

    // Should generate comment text.
    args = "{ \"comment\": \"a comment\" }";
    ASSERT_NO_THROW(arguments = Element::fromJSON(args));
    os.str("");
    ASSERT_NO_THROW(addContext(os, arguments));
    EXPECT_EQ(os.str(), ", context: { \"comment\": \"a comment\" }");

    // Should generate user context and comment text.
    args = "{ \"user-context\": { \"foobar\": 1234 }, "
        "\"comment\": \"a comment\" }";
    ASSERT_NO_THROW(arguments = Element::fromJSON(args));
    os.str("");
    ASSERT_NO_THROW(addContext(os, arguments));
    EXPECT_EQ(os.str(),
              ", context: { \"comment\": \"a comment\", \"foobar\": 1234 }");
}

// Iterates over a list of valid command/argument combinations and verifies that
// each produces the expected log in the log file
TEST_F(CalloutTest, validCommandEntries) {
    ASSERT_NO_THROW(BackendStore::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandle handle(getCalloutManager());

    ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS, "it works!");

    vector<string>lines;

    ValidTest *test = valid_tests;
    int test_cnt = 1;
    while (test && test->name) {
        // Populate the callout context as the hookpoint should
        handle.setArgument("name", string(test->name));

        ConstElementPtr arguments;
        ASSERT_NO_THROW(arguments = Element::fromJSON(test->arguments));
        handle.setArgument("arguments", arguments);

        handle.setArgument("response", response);

        // Callout should succeed and generate an entry
        int ret;
        ASSERT_NO_THROW(ret = command_processed(handle));
        ASSERT_EQ(0, ret) << "test#:" << test_cnt << " "
                          << test->name << " : " << test->arguments;

        // Add the expected lines to the list
        istringstream expected_lines(test->expected);
        string line;
        while (getline(expected_lines, line)) {
            lines.push_back(line);
        }
        ++test;
        ++test_cnt;
    }

    // Close it to flush any unwritten data
    BackendStore::instance()->close();

    // Verify that the file content is correct.
    string today_now_string = BackendStore::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Iterates over a list of valid command/argument combinations and verifies that
// each produces the expected log in the log file
TEST_F(CalloutTest, responseWithErrorsLease6BulkApplyCommandEntries) {
    ASSERT_NO_THROW(BackendStore::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandle handle(getCalloutManager());

    vector<string>lines;

    vector<string> responses = {
    "{ \"failed-leases\": [{ \"ip-address\": \"2001:db8:1::1\","
    " \"type\": \"IA_NA\", \"result\": 3,"
    " \"error-mesage\": \"It's Friday and we don't do Fridays!\"}]}",
    "{ \"failed-deleted-leases\": [{ \"ip-address\": \"2001:db8:1::3\","
    " \"type\": \"IA_NA\", \"result\": 3,"
    " \"error-mesage\": \"It's Friday and we don't do Fridays!\"}]}",
    "{ \"failed-leases\": [{ \"ip-address\": \"2001:db8:1::1\","
    " \"type\": \"IA_NA\", \"result\": 3,"
    " \"error-mesage\": \"It's Friday and we don't do Fridays!\"}]}",
    "{ \"failed-deleted-leases\": [{ \"ip-address\": \"2001:db8:1::3\","
    " \"type\": \"IA_NA\", \"result\": 3,"
    " \"error-mesage\": \"It's Friday and we don't do Fridays!\"}]}",
    "{ \"failed-leases\": [{ \"ip-address\": \"2001:db8:1::1\","
    " \"type\": \"IA_NA\", \"result\": 3,"
    " \"error-mesage\": \"It's Friday and we don't do Fridays!\"}],"
    " \"failed-deleted-leases\": [{ \"ip-address\": \"2001:db8:1::3\","
    " \"type\": \"IA_NA\", \"result\": 3,"
    " \"error-mesage\": \"It's Friday and we don't do Fridays!\"}]}",
    "{ \"failed-leases\": [{ \"ip-address\": \"2001:db8:1::1\","
    " \"type\": \"IA_NA\", \"result\": 3,"
    " \"error-mesage\": \"It's Friday and we don't do Fridays!\"}]}",
    "{ \"failed-deleted-leases\": [{ \"ip-address\": \"2001:db8:1::3\","
    " \"type\": \"IA_NA\", \"result\": 3,"
    " \"error-mesage\": \"It's Friday and we don't do Fridays!\"}]}",
    "{ \"failed-leases\": [{ \"ip-address\": \"2001:db8:1::1\","
    " \"type\": \"IA_NA\", \"result\": 3,"
    " \"error-mesage\": \"It's Friday and we don't do Fridays!\"}]}",
    "{ \"failed-deleted-leases\": [{ \"ip-address\": \"2001:db8:1::3\","
    " \"type\": \"IA_NA\", \"result\": 3,"
    " \"error-mesage\": \"It's Friday and we don't do Fridays!\"}]}",
    "{ \"failed-leases\": [{ \"ip-address\": \"2001:db8:1::1\","
    " \"type\": \"IA_NA\", \"result\": 3,"
    " \"error-mesage\": \"It's Friday and we don't do Fridays!\"}],"
    " \"failed-deleted-leases\": [{ \"ip-address\": \"2001:db8:1::3\","
    " \"type\": \"IA_NA\", \"result\": 3,"
    " \"error-mesage\": \"It's Friday and we don't do Fridays!\"}]}"
    };

    vector<string> expected = {
    "",
    "",
    "Administrator updated information on the lease of address: 2001:db8:1::2 "
    "to a device with DUID: 22:22:22:22:22:22, context: { \"ISC\": { \"relay-info\": "
    "[ { \"relay-id\": \"6464646464646464\", \"remote-id\": \"010203040506\" } ] } }",
    "Administrator deleted the lease for address: 2001:db8:1::4",
    "Administrator deleted the lease for address: 2001:db8:1::4\n"
    "Administrator updated information on the lease of address: 2001:db8:1::2 "
    "to a device with DUID: 22:22:22:22:22:22, context: { \"ISC\": { \"relay-info\": "
    "[ { \"relay-id\": \"6464646464646464\", \"remote-id\": \"010203040506\" } ] } }",
    "",
    "",
    "HA partner updated information on the lease of address: 2001:db8:1::2 "
    "to a device with DUID: 22:22:22:22:22:22, context: { \"ISC\": { \"relay-info\": "
    "[ { \"relay-id\": \"6464646464646464\", \"remote-id\": \"010203040506\" } ] } }",
    "HA partner deleted the lease for address: 2001:db8:1::4",
    "HA partner deleted the lease for address: 2001:db8:1::4\n"
    "HA partner updated information on the lease of address: 2001:db8:1::2 "
    "to a device with DUID: 22:22:22:22:22:22, context: { \"ISC\": { \"relay-info\": "
    "[ { \"relay-id\": \"6464646464646464\", \"remote-id\": \"010203040506\" } ] } }"
    };

    ValidTest *test = valid_tests;
    int test_cnt = 1;
    while (test && test->name) {
        if (string(test->name).find("bulk-apply") != string::npos) {
            ElementPtr args = Element::fromJSON(responses[test_cnt - 1]);
            ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS, "", args);
            handle.setArgument("response", response);
            // Populate the callout context as the hookpoint should
            handle.setArgument("name", string(test->name));

            ConstElementPtr arguments;
            ASSERT_NO_THROW(arguments = Element::fromJSON(test->arguments));
            handle.setArgument("arguments", arguments);

            // Callout should succeed and generate an entry
            int ret;
            ASSERT_NO_THROW(ret = command_processed(handle));
            ASSERT_EQ(0, ret) << "test#:" << test_cnt << " "
                              << test->name << " : " << test->arguments;

            // Add the expected lines to the list
            istringstream expected_lines(expected[test_cnt - 1]);
            string line;
            while (getline(expected_lines, line)) {
                lines.push_back(line);
            }
            ++test_cnt;
        }
        ++test;
    }

    // Close it to flush any unwritten data
    BackendStore::instance()->close();

    // Verify that the file content is correct.
    string today_now_string = BackendStore::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// This test verifies that it is possible to disable logging for selected IPv4
// subnets.
TEST_F(CalloutTest, disableLoggingForSubnet4) {
    ASSERT_NO_THROW(BackendStore::instance().reset(new TestableRotatingFile(time_)));

    // Create a subnet with user context disabling legal logging.
    Subnet4Ptr subnet4(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 50,
                                   SubnetID(44)));
    ElementPtr ctx4 = Element::createMap();
    ctx4->set("legal-logging", Element::create(false));
    subnet4->setContext(ctx4);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet4);

    // Explicitly enable legal logging for the other subnet.
    Subnet6Ptr subnet6(new Subnet6(IOAddress("2001:db8::"), 48, 30, 40, 50, 60,
                                   SubnetID(66)));
    ElementPtr ctx6 = Element::createMap();
    ctx6->set("legal-logging", Element::create(true));
    subnet6->setContext(ctx6);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet6);

    CfgMgr::instance().commit();

    // Make a callout handle
    CalloutHandle handle(getCalloutManager());

    ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS, "it works!");

    vector<string>lines;

    ValidTest *test = valid_tests;
    int test_cnt = 1;
    while (test && test->name) {
        if (string(test->name).find("bulk-apply") == string::npos) {
            // Populate the callout context as the hookpoint should
            handle.setArgument("name", string(test->name));

            ConstElementPtr arguments;
            ASSERT_NO_THROW(arguments = Element::fromJSON(test->arguments));
            handle.setArgument("arguments", arguments);

            handle.setArgument("response", response);

            // Callout should succeed and generate an entry
            int ret;
            ASSERT_NO_THROW(ret = command_processed(handle));
            ASSERT_EQ(0, ret) << "test#:" << test_cnt << " "
                              << test->name << " : " << test->arguments;

            // Only add log entry for non-v4 leases and for those commands which lack
            // subnet identifier.
            if ((string(test->name).find("lease4-") == string::npos) ||
                (string(test->arguments).find("subnet-id") == string::npos)) {
                // Add the expected lines to the list
                istringstream expected_lines(test->expected);
                string line;
                while (getline(expected_lines, line)) {
                    lines.push_back(line);
                }
            }
            ++test_cnt;
        }

        ++test;

    }

    // Close it to flush any unwritten data
    BackendStore::instance()->close();

    // Verify that the file content is correct.
    string today_now_string = BackendStore::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// This test verifies that it is possible to disable logging for selected IPv6
// subnets.
TEST_F(CalloutTest, disableLoggingForSubnet6) {
    ASSERT_NO_THROW(BackendStore::instance().reset(new TestableRotatingFile(time_)));

    // Create a subnet with user context disabling legal logging.
    Subnet6Ptr subnet6(new Subnet6(IOAddress("2001:db8::"), 48, 30, 40, 50, 60,
                                   SubnetID(66)));
    ElementPtr ctx6 = Element::createMap();
    ctx6->set("legal-logging", Element::create(false));
    subnet6->setContext(ctx6);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet6);

    // Explicitly enable legal logging for the other subnet.
    Subnet4Ptr subnet4(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 50,
                                   SubnetID(44)));
    ElementPtr ctx4 = Element::createMap();
    ctx4->set("legal-logging", Element::create(true));
    subnet4->setContext(ctx4);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet4);

    CfgMgr::instance().commit();

    // Make a callout handle
    CalloutHandle handle(getCalloutManager());

    ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS, "it works!");

    vector<string>lines;

    ValidTest *test = valid_tests;
    int test_cnt = 1;
    while (test && test->name) {
        if (string(test->name).find("bulk-apply") == string::npos) {
            // Populate the callout context as the hookpoint should
            handle.setArgument("name", string(test->name));

            ConstElementPtr arguments;
            ASSERT_NO_THROW(arguments = Element::fromJSON(test->arguments));
            handle.setArgument("arguments", arguments);

            handle.setArgument("response", response);

            // Callout should succeed and generate an entry
            int ret;
            ASSERT_NO_THROW(ret = command_processed(handle));
            ASSERT_EQ(0, ret) << "test#:" << test_cnt << " "
                              << test->name << " : " << test->arguments;

            // Only add log entry for non-v6 leases and for those commands which lack
            // subnet identifier.
            if ((string(test->name).find("lease6-") == string::npos) ||
                (string(test->arguments).find("subnet-id") == string::npos)) {
                // Add the expected lines to the list
                istringstream expected_lines(test->expected);
                string line;
                while (getline(expected_lines, line)) {
                    lines.push_back(line);
                }
            }
            ++test_cnt;
        }
        ++test;
    }

    // Close it to flush any unwritten data
    BackendStore::instance()->close();

    // Verify that the file content is correct.
    string today_now_string = BackendStore::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

// Tests that a command with a failed result code does not generate a log entry
TEST_F(CalloutTest, failedCommand) {
    ASSERT_NO_THROW(BackendStore::instance().reset(new TestableRotatingFile(time_)));

    // Make a callout handle
    CalloutHandle handle(getCalloutManager());

    // First we use a known good command and success to generate
    // an entry (otherwise rotate file won't get created
    handle.setArgument("name", string(valid_tests[0].name));

    ConstElementPtr arguments;
    ASSERT_NO_THROW(arguments = Element::fromJSON(valid_tests[0].arguments));
    handle.setArgument("arguments", arguments);

    ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS, "command success!");
    handle.setArgument("response", response);

    // Callout should succeed and generate an entry
    int ret;
    ASSERT_NO_THROW(ret = command_processed(handle));
    ASSERT_EQ(0, ret);

    vector<string>lines;
    lines.push_back(valid_tests[0].expected);

    // Now replace the response with a failure result and try again
    response = createAnswer(777, "command failed!");
    handle.setArgument("response", response);

    // Callout should succeed and but not generate an entry
    ASSERT_NO_THROW(ret = command_processed(handle));
    ASSERT_EQ(0, ret);

    // Close it to flush any unwritten data
    BackendStore::instance()->close();

    // Verify that the file content has only the one expected line.
    string today_now_string = BackendStore::instance()->getNowString();
    checkFileLines(genName(today()), today_now_string, lines);
}

} // end of anonymous namespace
