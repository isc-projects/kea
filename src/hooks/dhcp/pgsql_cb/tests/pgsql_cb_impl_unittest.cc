// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/testutils/pgsql_generic_backend_unittest.h>
#include <pgsql/testutils/pgsql_schema.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>
#include <pgsql_cb_impl.h>
#include <vector>

using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::util;

namespace {

class PgSqlConfigBackendTest : public PgSqlGenericBackendTest {
public:
    PgSqlConfigBackendTest() : PgSqlGenericBackendTest() {
        createFullSchema();
    }

    /// @brief Setup for each test.
    ///
    /// Creates the configuration backend impl.
    virtual void SetUp() {
        DatabaseConnection::ParameterMap params;
        params["name"] = "keatest";
        params["password"] = "keatest";
        params["user"] = "keatest";
        ASSERT_NO_THROW_LOG(cbptr_.reset(new PgSqlConfigBackendImpl(params, 0, 0)));
    }

    /// @brief Cleans up after each test.
    ///
    /// Destroys the configuration backend impl.
    virtual void TearDown() {
        ASSERT_NO_THROW_LOG(cbptr_.reset());
    }

    ~PgSqlConfigBackendTest() {
        destroyFullSchema();
    }

    /// @brief creates full schema (slow!)
    ///
    /// If possible, use simpler, faster alternative: @ref createDummySchema();
    /// Don't forget to tear it down with @ref destroyFullSchema();
    void createFullSchema() {
        // Create the actual full Kea schema.
        isc::db::test::createPgSQLSchema();
    }

    /// @brief destroys the full schema (slow!)
    ///
    /// Don't forget to call this method once you're done, if you used @ref createFullSchema().
    void destroyFullSchema() {
        // Clean up after ourselves.
        isc::db::test::destroyPgSQLSchema();
    }

    boost::shared_ptr<PgSqlConfigBackendImpl> cbptr_;
};

// Let's start with absolute basics.  This should construct a backend instance
// connected to the unit test schema.  The backend instance is created in
// Setup() and which will ASSERT on failures.
TEST_F(PgSqlConfigBackendTest, constructor) {
    //  Is this the right config backend type?
    EXPECT_EQ("postgresql", cbptr_->getType());
}

}  // namespace
