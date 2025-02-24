// Copyright (C) 2012-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <database/database_connection.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <dhcpsrv/tracking_lease_mgr.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::db;
using namespace isc::dhcp;

// This set of tests only check the parsing functions of LeaseMgrFactory.
// Tests of the LeaseMgr create/instance/destroy are implicitly carried out
// in the tests for the different concrete lease managers (e.g. MySqlLeaseMgr).

namespace {

TrackingLeaseMgrPtr
memFactory(const DatabaseConnection::ParameterMap& parameters) {
    return (TrackingLeaseMgrPtr(new Memfile_LeaseMgr(parameters)));
}

// @brief Register memFactory
bool registerFactory() {
    static auto db_version = []() -> std::string {
        return (std::string("version 1"));
    };
    return (LeaseMgrFactory::registerFactory("mem", memFactory, false, db_version));
}

// @brief Derive mem1 class
class Mem1LeaseMgr : public Memfile_LeaseMgr {
public:
    Mem1LeaseMgr(const DatabaseConnection::ParameterMap& parameters) :
        Memfile_LeaseMgr(parameters) {
    }
    virtual ~Mem1LeaseMgr() = default;
    virtual string getType() const {
        return ("mem1");
    }
};

// @brief Factory of mem1
TrackingLeaseMgrPtr
mem1Factory(const DatabaseConnection::ParameterMap& parameters) {
    return (TrackingLeaseMgrPtr(new Mem1LeaseMgr(parameters)));
}

// @brief Register mem1Factory
bool registerFactory1() {
    return (LeaseMgrFactory::registerFactory("mem1", mem1Factory));
}

// @brief Derive mem2 class
class Mem2LeaseMgr : public Memfile_LeaseMgr {
public:
    Mem2LeaseMgr(const DatabaseConnection::ParameterMap& parameters) :
        Memfile_LeaseMgr(parameters) {
    }
    virtual ~Mem2LeaseMgr() = default;
    virtual string getType() const {
        return ("mem2");
    }
};

// @brief Factory of mem2
TrackingLeaseMgrPtr
mem2Factory(const DatabaseConnection::ParameterMap& parameters) {
    return (TrackingLeaseMgrPtr(new Mem2LeaseMgr(parameters)));
}

// @brief Register mem2Factory
bool registerFactory2() {
    static auto db_version = []() -> std::string {
        return (std::string("version 2"));
    };
    return (LeaseMgrFactory::registerFactory("mem2", mem2Factory, false, db_version));
}

// @brief Factory function returning 0
TrackingLeaseMgrPtr
factory0(const DatabaseConnection::ParameterMap&) {
    return (TrackingLeaseMgrPtr());
}

// @brief Test fixture class
class LeaseMgrFactoryTest : public ::testing::Test {
public:
    /// @brief Constructor
    LeaseMgrFactoryTest() = default;

    /// @brief Destructor
    virtual ~LeaseMgrFactoryTest() = default;

private:
    // @brief Prepares the class for a test.
    virtual void SetUp() {
        LeaseMgrFactory::destroy();
    }

    // @brief Cleans up after the test.
    virtual void TearDown() {
        LeaseMgrFactory::destroy();
        LeaseMgrFactory::deregisterFactory("mem");
        LeaseMgrFactory::deregisterFactory("mem1");
        LeaseMgrFactory::deregisterFactory("mem2");
    }
};

// Verify a factory can be registered and only once.
TEST_F(LeaseMgrFactoryTest, registerFactory) {
    EXPECT_TRUE(registerFactory());

    // Only once
    EXPECT_FALSE(registerFactory());
}

// Verify a factory registration can be checked.
TEST_F(LeaseMgrFactoryTest, registeredFactory) {
    // Not yet registered
    EXPECT_FALSE(LeaseMgrFactory::registeredFactory("mem"));
    EXPECT_FALSE(LeaseMgrFactory::registeredFactory("mem1"));

    // Register mem
    EXPECT_TRUE(registerFactory());

    // Now mem is registered but not mem1
    EXPECT_TRUE(LeaseMgrFactory::registeredFactory("mem"));
    EXPECT_FALSE(LeaseMgrFactory::registeredFactory("mem1"));
}

// Verify a factory can be registered and deregistered
TEST_F(LeaseMgrFactoryTest, deregisterFactory) {
    // Does not exist at the beginning
    EXPECT_FALSE(LeaseMgrFactory::deregisterFactory("mem"));

    // Register and deregister
    EXPECT_TRUE(registerFactory());
    EXPECT_TRUE(LeaseMgrFactory::deregisterFactory("mem"));
    EXPECT_FALSE(LeaseMgrFactory::registeredFactory("mem"));

    // No longer exists
    EXPECT_FALSE(LeaseMgrFactory::deregisterFactory("mem"));
}

// Verify a registered factory can be called
TEST_F(LeaseMgrFactoryTest, create) {
    EXPECT_TRUE(registerFactory());
    EXPECT_NO_THROW(LeaseMgrFactory::create("type=mem persist=false universe=4"));
    EXPECT_TRUE(LeaseMgrFactory::haveInstance());
    EXPECT_EQ(LeaseMgrFactory::instance().getType(), "memfile");
}

// Verify that type is required
TEST_F(LeaseMgrFactoryTest, notype) {
    EXPECT_THROW(LeaseMgrFactory::create("tp=mem"),
                 InvalidParameter);
    EXPECT_FALSE(LeaseMgrFactory::haveInstance());
    EXPECT_THROW(LeaseMgrFactory::create("type=mem"),
                 InvalidType);
    EXPECT_FALSE(LeaseMgrFactory::haveInstance());
}

// Verify that factory must not return null
TEST_F(LeaseMgrFactoryTest, null) {
    EXPECT_TRUE(LeaseMgrFactory::registerFactory("mem", factory0));
    EXPECT_THROW(LeaseMgrFactory::create("type=mem"),
                 Unexpected);
    EXPECT_FALSE(LeaseMgrFactory::haveInstance());
}

// Verify destroy class method
TEST_F(LeaseMgrFactoryTest, destroy) {
    // No sources at the beginning
    EXPECT_FALSE(LeaseMgrFactory::haveInstance());
    EXPECT_NO_THROW(LeaseMgrFactory::destroy());
    EXPECT_FALSE(LeaseMgrFactory::haveInstance());

    // Add mem
    EXPECT_TRUE(registerFactory());
    EXPECT_NO_THROW(LeaseMgrFactory::create("type=mem persist=false universe=6"));
    EXPECT_TRUE(LeaseMgrFactory::haveInstance());

    EXPECT_NO_THROW(LeaseMgrFactory::destroy());
    EXPECT_FALSE(LeaseMgrFactory::haveInstance());
}

// Verify create and destroy class method on multiple backends
TEST_F(LeaseMgrFactoryTest, multipleV4) {
    CfgMgr::instance().setFamily(AF_INET);
    // Add foo twice
    EXPECT_TRUE(registerFactory1());
    EXPECT_NO_THROW(LeaseMgrFactory::create("type=mem1 persist=false universe=4"));
    EXPECT_NO_THROW(LeaseMgrFactory::create("type=mem1 persist=false universe=6"));
    EXPECT_TRUE(LeaseMgrFactory::haveInstance());
    EXPECT_EQ(LeaseMgrFactory::instance().getType(), "mem1");

    // Add mem2 once
    EXPECT_TRUE(registerFactory2());
    EXPECT_NO_THROW(LeaseMgrFactory::create("type=mem2 persist=false universe=6"));
    EXPECT_TRUE(LeaseMgrFactory::haveInstance());
    EXPECT_EQ(LeaseMgrFactory::instance().getType(), "mem2");

    std::list<std::string> expected;
    expected.push_back("version 2");
    expected.push_back("Memfile backend 3.0");
    EXPECT_EQ(expected, LeaseMgrFactory::getDBVersions());

    EXPECT_TRUE(registerFactory());

    expected.clear();
    expected.push_back("version 1");
    expected.push_back("version 2");
    expected.push_back("Memfile backend 3.0");
    EXPECT_EQ(expected, LeaseMgrFactory::getDBVersions());

    // Delete them
    EXPECT_NO_THROW(LeaseMgrFactory::destroy());
    EXPECT_FALSE(LeaseMgrFactory::haveInstance());
}

// Verify create and destroy class method on multiple backends
TEST_F(LeaseMgrFactoryTest, multipleV6) {
    CfgMgr::instance().setFamily(AF_INET6);
    // Add foo twice
    EXPECT_TRUE(registerFactory1());
    EXPECT_NO_THROW(LeaseMgrFactory::create("type=mem1 persist=false universe=4"));
    EXPECT_NO_THROW(LeaseMgrFactory::create("type=mem1 persist=false universe=6"));
    EXPECT_TRUE(LeaseMgrFactory::haveInstance());
    EXPECT_EQ(LeaseMgrFactory::instance().getType(), "mem1");

    // Add mem2 once
    EXPECT_TRUE(registerFactory2());
    EXPECT_NO_THROW(LeaseMgrFactory::create("type=mem2 persist=false universe=6"));
    EXPECT_TRUE(LeaseMgrFactory::haveInstance());
    EXPECT_EQ(LeaseMgrFactory::instance().getType(), "mem2");

    std::list<std::string> expected;
    expected.push_back("version 2");
    expected.push_back("Memfile backend 5.0");
    EXPECT_EQ(expected, LeaseMgrFactory::getDBVersions());

    EXPECT_TRUE(registerFactory());

    expected.clear();
    expected.push_back("version 1");
    expected.push_back("version 2");
    expected.push_back("Memfile backend 5.0");
    EXPECT_EQ(expected, LeaseMgrFactory::getDBVersions());

    // Delete them
    EXPECT_NO_THROW(LeaseMgrFactory::destroy());
    EXPECT_FALSE(LeaseMgrFactory::haveInstance());
}

} // end of anonymous namespace
