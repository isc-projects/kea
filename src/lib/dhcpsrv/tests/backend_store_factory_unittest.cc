// Copyright (C) 2012-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <database/database_connection.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/backend_store_factory.h>
#include <dhcpsrv/backend_store.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::db;
using namespace isc::dhcp;

// This set of tests only check the parsing functions of BackendStoreFactory.
// Tests of the BackendStore create/instance/destroy are implicitly carried out
// in the tests for the BackendStore.

namespace {

class DummyBackendStore : public BackendStore {
public:

    /// @brief Constructor.
    DummyBackendStore(const string& type, DatabaseConnection::ParameterMap parameters) :
        BackendStore(parameters), type_(type) {
    }

    /// @brief Opens the store.
    virtual void open() {
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
    /// @throw BackendStoreError if the write fails
    virtual void writeln(const string& /* text */, const string& /* addr */) {
    }

private:

    /// @brief The BackendStore type.
    string type_;
};

BackendStorePtr
dummyFactory(const DatabaseConnection::ParameterMap& parameters) {
    return (BackendStorePtr(new DummyBackendStore(string("dummy"), parameters)));
}

// @brief Register dummyFactory
bool registerFactory() {
    static auto db_version = []() -> string {
        return (string("version 1"));
    };
    return (BackendStoreFactory::registerBackendFactory(string("dummy"), dummyFactory, false, db_version));
}

// @brief Derive dummy1 class
class Dummy1BackendStore : public DummyBackendStore {
public:
    Dummy1BackendStore(const DatabaseConnection::ParameterMap& parameters) :
        DummyBackendStore(string("dummy1"), parameters) {
    }
    virtual ~Dummy1BackendStore() = default;
};

// @brief Factory of dummy1
BackendStorePtr
dummy1Factory(const DatabaseConnection::ParameterMap& parameters) {
    return (BackendStorePtr(new Dummy1BackendStore(parameters)));
}

// @brief Register dummy1Factory
bool registerFactory1() {
    return (BackendStoreFactory::registerBackendFactory(string("dummy1"), dummy1Factory));
}

// @brief Derive dummy2 class
class Dummy2BackendStore : public DummyBackendStore {
public:
    Dummy2BackendStore(const DatabaseConnection::ParameterMap& parameters) :
        DummyBackendStore(string("dummy2"), parameters) {
    }
    virtual ~Dummy2BackendStore() = default;
};

// @brief Factory of dummy2
BackendStorePtr
dummy2Factory(const DatabaseConnection::ParameterMap& parameters) {
    return (BackendStorePtr(new Dummy2BackendStore(parameters)));
}

// @brief Register dummy2Factory
bool registerFactory2() {
    static auto db_version = []() -> string {
        return (string("version 2"));
    };
    return (BackendStoreFactory::registerBackendFactory(string("dummy2"), dummy2Factory, false, db_version));
}

// @brief Factory function returning 0
BackendStorePtr
factory0(const DatabaseConnection::ParameterMap&) {
    return (BackendStorePtr());
}

// @brief Test fixture class
class BackendStoreFactoryTest : public ::testing::Test {
public:
    /// @brief Constructor
    BackendStoreFactoryTest() = default;

    /// @brief Destructor
    virtual ~BackendStoreFactoryTest() = default;

private:
    // @brief Prepares the class for a test.
    virtual void SetUp() {
        BackendStoreFactory::delAllBackends();
    }

    // @brief Cleans up after the test.
    virtual void TearDown() {
        BackendStoreFactory::delAllBackends();
        BackendStoreFactory::unregisterBackendFactory(string("dummy"));
        BackendStoreFactory::unregisterBackendFactory(string("dummy1"));
        BackendStoreFactory::unregisterBackendFactory(string("dummy2"));
    }
};

// Verify a factory can be registered and only once.
TEST_F(BackendStoreFactoryTest, registerFactory) {
    EXPECT_TRUE(registerFactory());

    // Only once
    EXPECT_FALSE(registerFactory());
}

// Verify a factory registration can be checked.
TEST_F(BackendStoreFactoryTest, registeredFactory) {
    // Not yet registered
    EXPECT_FALSE(BackendStoreFactory::registeredFactory(string("dummy")));
    EXPECT_FALSE(BackendStoreFactory::registeredFactory(string("dummy1")));

    // Register dummy
    EXPECT_TRUE(registerFactory());

    // Now dummy is registered but not dummy1
    EXPECT_TRUE(BackendStoreFactory::registeredFactory(string("dummy")));
    EXPECT_FALSE(BackendStoreFactory::registeredFactory(string("dummy1")));
}

// Verify a factory can be registered and deregistered
TEST_F(BackendStoreFactoryTest, deregisterFactory) {
    // Does not exist at the beginning
    EXPECT_FALSE(BackendStoreFactory::unregisterBackendFactory(string("dummy")));

    // Register and deregister
    EXPECT_TRUE(registerFactory());
    EXPECT_TRUE(BackendStoreFactory::unregisterBackendFactory(string("dummy")));
    EXPECT_FALSE(BackendStoreFactory::registeredFactory(string("dummy")));

    // No longer exists
    EXPECT_FALSE(BackendStoreFactory::unregisterBackendFactory(string("dummy")));
}

// Verify a registered factory can be called
TEST_F(BackendStoreFactoryTest, create) {
    EXPECT_TRUE(registerFactory());
    DatabaseConnection::ParameterMap parameters;
    parameters["type"] = "dummy";
    EXPECT_NO_THROW(BackendStoreFactory::addBackend(parameters));
    EXPECT_TRUE(BackendStoreFactory::haveInstance(string("dummy")));
}

// Verify that type is required
TEST_F(BackendStoreFactoryTest, notype) {
    DatabaseConnection::ParameterMap parameters;
    EXPECT_THROW(BackendStoreFactory::addBackend(parameters),
                 InvalidParameter);
    EXPECT_FALSE(BackendStoreFactory::haveInstance(string("dummy")));
    parameters["type"] = "dummy";
    EXPECT_THROW(BackendStoreFactory::addBackend(parameters),
                 InvalidType);
    EXPECT_FALSE(BackendStoreFactory::haveInstance(string("dummy")));
}

// Verify that factory must not return null
TEST_F(BackendStoreFactoryTest, null) {
    EXPECT_TRUE(BackendStoreFactory::registerBackendFactory(string("dummy"), factory0));
    DatabaseConnection::ParameterMap parameters;
    parameters["type"] = "dummy";
    EXPECT_THROW(BackendStoreFactory::addBackend(parameters),
                 Unexpected);
    EXPECT_FALSE(BackendStoreFactory::haveInstance(string("dummy")));
}

// Verify destroy class method
TEST_F(BackendStoreFactoryTest, destroy) {
    DatabaseConnection::ParameterMap parameters;
    parameters["type"] = "dummy";
    // No sources at the beginning
    EXPECT_FALSE(BackendStoreFactory::haveInstance(string("dummy")));
    EXPECT_NO_THROW(BackendStoreFactory::delBackend(string("dummy"), parameters));
    EXPECT_FALSE(BackendStoreFactory::haveInstance(string("dummy")));

    // Add dummy
    EXPECT_TRUE(registerFactory());
    EXPECT_NO_THROW(BackendStoreFactory::addBackend(parameters));
    EXPECT_TRUE(BackendStoreFactory::haveInstance(string("dummy")));

    EXPECT_NO_THROW(BackendStoreFactory::delBackend(string("dummy"), parameters));
    EXPECT_FALSE(BackendStoreFactory::haveInstance(string("dummy")));
}

// Verify create and destroy class method on multiple backends
TEST_F(BackendStoreFactoryTest, multiple) {
    CfgMgr::instance().setFamily(AF_INET);
    // Add foo twice
    EXPECT_TRUE(registerFactory1());
    DatabaseConnection::ParameterMap parameters;
    parameters["type"] = "dummy1";
    EXPECT_NO_THROW(BackendStoreFactory::addBackend(parameters));
    EXPECT_NO_THROW(BackendStoreFactory::addBackend(parameters));
    EXPECT_TRUE(BackendStoreFactory::haveInstance(string("dummy1")));

    // Add dummy2 once
    EXPECT_TRUE(registerFactory2());
    parameters["type"] = "dummy2";
    EXPECT_NO_THROW(BackendStoreFactory::addBackend(parameters, 1));
    EXPECT_TRUE(BackendStoreFactory::haveInstance(string("dummy2")));

    list<string> expected;
    expected.push_back("version 2");
    EXPECT_EQ(expected, BackendStoreFactory::getDBVersions());

    EXPECT_TRUE(registerFactory());

    expected.clear();
    expected.push_back("version 1");
    expected.push_back("version 2");
    EXPECT_EQ(expected, BackendStoreFactory::getDBVersions());

    // Delete them
    EXPECT_NO_THROW(BackendStoreFactory::delAllBackends());
    EXPECT_FALSE(BackendStoreFactory::haveInstance(string("dummy")));
}

} // end of anonymous namespace
