// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <database/database_connection.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/legal_log_mgr_factory.h>
#include <dhcpsrv/legal_log_mgr.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::db;
using namespace isc::dhcp;

// This set of tests only check the parsing functions of LegalLogMgrFactory.
// Tests of the LegalLogMgr create/instance/destroy are implicitly carried out
// in the tests for the LegalLogMgr.

namespace {

class DummyLegalLogMgr : public LegalLogMgr {
public:

    /// @brief Constructor.
    DummyLegalLogMgr(const string& type, DatabaseConnection::ParameterMap parameters) :
        LegalLogMgr(parameters), type_(type) {
    }

    /// @brief Opens the store.
    virtual void open(ManagerID) {
    }

    /// @brief Closes the store.
    virtual void close() {
    }

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "logfile" etc.)
    ///
    /// @return Type of the backend.
    virtual string getType() const {
        return (type_);
    }

    /// @brief Appends a string to the store with a timestamp and address.
    ///
    /// @param text String to append
    /// @param addr Address or prefix
    /// @throw LegalLogMgrError if the write fails
    virtual void writeln(const string& /* text */, const string& /* addr */) {
    }

private:

    /// @brief The LegalLogMgr type.
    string type_;
};

LegalLogMgrPtr
dummyFactory(const DatabaseConnection::ParameterMap& parameters) {
    return (LegalLogMgrPtr(new DummyLegalLogMgr(string("dummy"), parameters)));
}

// @brief Register dummyFactory
bool registerFactory() {
    static auto db_version = []() -> string {
        return (string("version 1"));
    };
    return (LegalLogMgrFactory::registerBackendFactory(string("dummy"), dummyFactory, false, db_version));
}

// @brief Derive dummy1 class
class Dummy1LegalLogMgr : public DummyLegalLogMgr {
public:
    Dummy1LegalLogMgr(const DatabaseConnection::ParameterMap& parameters) :
        DummyLegalLogMgr(string("dummy1"), parameters) {
    }
    virtual ~Dummy1LegalLogMgr() = default;
};

// @brief Factory of dummy1
LegalLogMgrPtr
dummy1Factory(const DatabaseConnection::ParameterMap& parameters) {
    return (LegalLogMgrPtr(new Dummy1LegalLogMgr(parameters)));
}

// @brief Register dummy1Factory
bool registerFactory1() {
    return (LegalLogMgrFactory::registerBackendFactory(string("dummy1"), dummy1Factory));
}

// @brief Derive dummy2 class
class Dummy2LegalLogMgr : public DummyLegalLogMgr {
public:
    Dummy2LegalLogMgr(const DatabaseConnection::ParameterMap& parameters) :
        DummyLegalLogMgr(string("dummy2"), parameters) {
    }
    virtual ~Dummy2LegalLogMgr() = default;
};

// @brief Factory of dummy2
LegalLogMgrPtr
dummy2Factory(const DatabaseConnection::ParameterMap& parameters) {
    return (LegalLogMgrPtr(new Dummy2LegalLogMgr(parameters)));
}

// @brief Register dummy2Factory
bool registerFactory2() {
    static auto db_version = []() -> string {
        return (string("version 2"));
    };
    return (LegalLogMgrFactory::registerBackendFactory(string("dummy2"), dummy2Factory, false, db_version));
}

// @brief Factory function returning 0
LegalLogMgrPtr
factory0(const DatabaseConnection::ParameterMap&) {
    return (LegalLogMgrPtr());
}

// @brief Test fixture class
class LegalLogMgrFactoryTest : public ::testing::Test {
public:
    /// @brief Constructor
    LegalLogMgrFactoryTest() = default;

    /// @brief Destructor
    virtual ~LegalLogMgrFactoryTest() = default;

private:
    // @brief Prepares the class for a test.
    virtual void SetUp() {
        LegalLogMgrFactory::delAllBackends();
    }

    // @brief Cleans up after the test.
    virtual void TearDown() {
        LegalLogMgrFactory::delAllBackends();
        LegalLogMgrFactory::unregisterBackendFactory(string("dummy"));
        LegalLogMgrFactory::unregisterBackendFactory(string("dummy1"));
        LegalLogMgrFactory::unregisterBackendFactory(string("dummy2"));
    }
};

// Verify a factory can be registered and only once.
TEST_F(LegalLogMgrFactoryTest, registerFactory) {
    EXPECT_TRUE(registerFactory());

    // Only once
    EXPECT_FALSE(registerFactory());
}

// Verify a factory registration can be checked.
TEST_F(LegalLogMgrFactoryTest, registeredFactory) {
    // Not yet registered
    EXPECT_FALSE(LegalLogMgrFactory::registeredFactory(string("dummy")));
    EXPECT_FALSE(LegalLogMgrFactory::registeredFactory(string("dummy1")));

    // Register dummy
    EXPECT_TRUE(registerFactory());

    // Now dummy is registered but not dummy1
    EXPECT_TRUE(LegalLogMgrFactory::registeredFactory(string("dummy")));
    EXPECT_FALSE(LegalLogMgrFactory::registeredFactory(string("dummy1")));
}

// Verify a factory can be registered and deregistered
TEST_F(LegalLogMgrFactoryTest, deregisterFactory) {
    // Does not exist at the beginning
    EXPECT_FALSE(LegalLogMgrFactory::unregisterBackendFactory(string("dummy")));

    // Register and deregister
    EXPECT_TRUE(registerFactory());
    EXPECT_TRUE(LegalLogMgrFactory::unregisterBackendFactory(string("dummy")));
    EXPECT_FALSE(LegalLogMgrFactory::registeredFactory(string("dummy")));

    // No longer exists
    EXPECT_FALSE(LegalLogMgrFactory::unregisterBackendFactory(string("dummy")));
}

// Verify a registered factory can be called
TEST_F(LegalLogMgrFactoryTest, create) {
    EXPECT_TRUE(registerFactory());
    DatabaseConnection::ParameterMap parameters;
    parameters["type"] = "dummy";
    EXPECT_NO_THROW(LegalLogMgrFactory::addBackend(parameters));
    EXPECT_TRUE(LegalLogMgrFactory::haveInstance(string("dummy")));
}

// Verify that type is required
TEST_F(LegalLogMgrFactoryTest, notype) {
    DatabaseConnection::ParameterMap parameters;
    EXPECT_THROW(LegalLogMgrFactory::addBackend(parameters),
                 InvalidParameter);
    EXPECT_FALSE(LegalLogMgrFactory::haveInstance(string("dummy")));
    parameters["type"] = "dummy";
    EXPECT_THROW(LegalLogMgrFactory::addBackend(parameters),
                 InvalidType);
    EXPECT_FALSE(LegalLogMgrFactory::haveInstance(string("dummy")));
}

// Verify that factory must not return null
TEST_F(LegalLogMgrFactoryTest, null) {
    EXPECT_TRUE(LegalLogMgrFactory::registerBackendFactory(string("dummy"), factory0));
    DatabaseConnection::ParameterMap parameters;
    parameters["type"] = "dummy";
    EXPECT_THROW(LegalLogMgrFactory::addBackend(parameters),
                 Unexpected);
    EXPECT_FALSE(LegalLogMgrFactory::haveInstance(string("dummy")));
}

// Verify destroy class method
TEST_F(LegalLogMgrFactoryTest, destroy) {
    DatabaseConnection::ParameterMap parameters;
    parameters["type"] = "dummy";
    // No sources at the beginning
    EXPECT_FALSE(LegalLogMgrFactory::haveInstance(string("dummy")));
    EXPECT_NO_THROW(LegalLogMgrFactory::delBackend(string("dummy"), parameters));
    EXPECT_FALSE(LegalLogMgrFactory::haveInstance(string("dummy")));

    // Add dummy
    EXPECT_TRUE(registerFactory());
    EXPECT_NO_THROW(LegalLogMgrFactory::addBackend(parameters));
    EXPECT_TRUE(LegalLogMgrFactory::haveInstance(string("dummy")));

    EXPECT_NO_THROW(LegalLogMgrFactory::delBackend(string("dummy"), parameters));
    EXPECT_FALSE(LegalLogMgrFactory::haveInstance(string("dummy")));
}

// Verify create and destroy class method on multiple backends
TEST_F(LegalLogMgrFactoryTest, multiple) {
    CfgMgr::instance().setFamily(AF_INET);
    // Add foo twice
    EXPECT_TRUE(registerFactory1());
    DatabaseConnection::ParameterMap parameters;
    parameters["type"] = "dummy1";
    EXPECT_NO_THROW(LegalLogMgrFactory::addBackend(parameters));
    EXPECT_NO_THROW(LegalLogMgrFactory::addBackend(parameters));
    EXPECT_TRUE(LegalLogMgrFactory::haveInstance(string("dummy1")));

    // Add dummy2 once
    EXPECT_TRUE(registerFactory2());
    parameters["type"] = "dummy2";
    EXPECT_NO_THROW(LegalLogMgrFactory::addBackend(parameters, 1));
    EXPECT_TRUE(LegalLogMgrFactory::haveInstance(string("dummy2")));

    list<string> expected;
    expected.push_back("version 2");
    EXPECT_EQ(expected, LegalLogMgrFactory::getDBVersions());

    EXPECT_TRUE(registerFactory());

    expected.clear();
    expected.push_back("version 1");
    expected.push_back("version 2");
    EXPECT_EQ(expected, LegalLogMgrFactory::getDBVersions());

    // Delete them
    EXPECT_NO_THROW(LegalLogMgrFactory::delAllBackends());
    EXPECT_FALSE(LegalLogMgrFactory::haveInstance(string("dummy")));
}

} // end of anonymous namespace
