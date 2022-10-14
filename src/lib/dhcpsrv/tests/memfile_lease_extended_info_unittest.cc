// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <testutils/gtest_utils.h>
#include <util/multi_threading_mgr.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::util;
using namespace std;

namespace {

/// @brief A derivation of the lease manager exposing protected methods.
class NakedMemfileLeaseMgr : public Memfile_LeaseMgr {
public:
    /// @brief Constructor.
    ///
    /// Creates anto create an instance of the lease manager.
    ///
    /// @param parameters Parameter map.
    NakedMemfileLeaseMgr(const DatabaseConnection::ParameterMap& parameters)
        : Memfile_LeaseMgr(parameters) {
    }

    /// @brief Destructor.
    virtual ~NakedMemfileLeaseMgr() {
    }

    /// @brief Exposes protected methods.
    using Memfile_LeaseMgr::deleteExtendedInfo6;
    using Memfile_LeaseMgr::addRelayId6;
    using Memfile_LeaseMgr::addRemoteId6;
    using Memfile_LeaseMgr::addLinkAddr6;
};

/// @brief Type of unique pointers to naked lease manager.
typedef unique_ptr<NakedMemfileLeaseMgr> NakedMemfileLeaseMgrPtr;

/// @brief Test fixture class for extended info tests.
class MemfileLeaseExtendedInfoTest : public ::testing::Test {
public:
    /// @brief Constructor.
    MemfileLeaseExtendedInfoTest() {
        pmap_.clear();
        lease_mgr_.reset();
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Destructor.
    ~MemfileLeaseExtendedInfoTest() {
        pmap_.clear();
        lease_mgr_.reset();
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Parameter map.
    DatabaseConnection::ParameterMap pmap_;

    /// @brief Lease manager.
    NakedMemfileLeaseMgrPtr lease_mgr_;
};

/// @brief Verifies that the lease manager can start in V4.
TEST_F(MemfileLeaseExtendedInfoTest, v4) {
    pmap_["universe"] = "4";
    pmap_["persist"] = "false";
    pmap_["extended-info-tables"] = "true";

    EXPECT_NO_THROW(lease_mgr_.reset(new NakedMemfileLeaseMgr(pmap_)));
    EXPECT_TRUE(lease_mgr_->getExtendedInfoEnabled());
}

/// @brief Verifies that the lease manager can start in V6.
TEST_F(MemfileLeaseExtendedInfoTest, v6) {
    pmap_["universe"] = "6";
    pmap_["persist"] = "false";
    pmap_["extended-info-tables"] = "true";

    EXPECT_NO_THROW(lease_mgr_.reset(new NakedMemfileLeaseMgr(pmap_)));
    EXPECT_TRUE(lease_mgr_->getExtendedInfoEnabled());
}

}  // namespace
