// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LIBDHCPSRV_TEST_UTILS_H
#define LIBDHCPSRV_TEST_UTILS_H

#include <dhcpsrv/lease_mgr.h>
#include <vector>

namespace isc {
namespace dhcp {
namespace test {

// @brief performs details comparison between two IPv6 leases
//
// @param first first lease to compare
// @param second second lease to compare
//
// This method is intended to be run from gtest tests as it
// uses gtest macros and possibly reports gtest failures.
void
detailCompareLease(const Lease6Ptr& first, const Lease6Ptr& second);

// @brief performs details comparison between two IPv4 leases
//
// @param first first lease to compare
// @param second second lease to compare
//
// This method is intended to be run from gtest tests as it
// uses gtest macros and possibly reports gtest failures.
void
detailCompareLease(const Lease4Ptr& first, const Lease4Ptr& second);

}; // namespace test
}; // namespace dhcp
}; // namespace isc

#endif
