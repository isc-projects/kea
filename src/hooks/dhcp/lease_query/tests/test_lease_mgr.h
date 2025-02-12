// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains test lease managers.

#ifndef TEST_LEASE_MGR_H
#define TEST_LEASE_MGR_H

#include <exceptions/exceptions.h>

#ifdef HAVE_MYSQL
#include <mysql/testutils/mysql_schema.h>
#include <hooks/dhcp/mysql/mysql_lease_mgr.h>
#endif

#ifdef HAVE_PGSQL
#include <pgsql/testutils/pgsql_schema.h>
#include <hooks/dhcp/pgsql/pgsql_lease_mgr.h>
#endif

/// @brief Class of test lease manager.
class TestLeaseMgr {
public:
    /// @brief Destructor.
    virtual ~TestLeaseMgr() = default;

    /// @brief Return the database access string.
    virtual std::string& dbAccess() {
        isc_throw(isc::NotImplemented, "TestLeaseMgr direct use");
    }

    /// @brief Create database schema.
    virtual void createSchema() { }

    /// @brief Destroy database schema.
    virtual void destroySchema() { }
};

/// @brief Memfile database test lease manager.
///
/// Schema methods are left to their defaults i.e. do nothing.
class MemfileTestLeaseMgr : public TestLeaseMgr {
public:
    /// @brief Return the database access string.
    virtual std::string& dbAccess() {
        static std::string dbaccess = "type=memfile persist=false universe=4";
        return (dbaccess);
    }
};

#ifdef HAVE_MYSQL
/// @brief MySQL database test lease manager.
class MySQLTestLeaseMgr : public TestLeaseMgr {
public:
    /// @brief Return the database access string.
    virtual std::string& dbAccess() {
        static std::string dbaccess =
            isc::db::test::validMySQLConnectionString();
        return (dbaccess);
    }

    /// @brief Create database schema.
    virtual void createSchema() {
        isc::db::test::createMySQLSchema();
    }

    /// @brief Destroy database schema.
    virtual void destroySchema() {
        isc::db::test::destroyMySQLSchema();
    }

    /// @brief Initializer.
    isc::dhcp::MySqlLeaseMgrInit init_;
};
#endif

#ifdef HAVE_PGSQL
/// @brief PostgreSQL database test lease manager.
class PgSQLTestLeaseMgr : public TestLeaseMgr {
public:
    /// @brief Return the database access string.
    virtual std::string& dbAccess() {
        static std::string dbaccess =
            isc::db::test::validPgSQLConnectionString();
        return (dbaccess);
    }

    /// @brief Create database schema.
    virtual void createSchema() {
        isc::db::test::createPgSQLSchema();
    }

    /// @brief Destroy database schema.
    virtual void destroySchema() {
        isc::db::test::destroyPgSQLSchema();
    }

    /// @brief Initializer.
    isc::dhcp::PgSqlLeaseMgrInit init_;
};
#endif

#endif // TEST_LEASE_MGR_H
