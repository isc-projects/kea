// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/testutils/memory_host_data_source.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

// @brief Register memFactory 
bool registerFactory() {
    return (HostDataSourceFactory::registerFactory("mem", memFactory));
}

// @brief Derive mem1 class
class Mem1HostDataSource : public MemHostDataSource {
public:
    virtual string getType() const {
        return ("mem1");
    }
};

// @brief Factory of mem1
HostDataSourcePtr
mem1Factory(const DatabaseConnection::ParameterMap&) {
    return (HostDataSourcePtr(new Mem1HostDataSource()));
}

// @brief Register mem1Factory
bool registerFactory1() {
    return (HostDataSourceFactory::registerFactory("mem1", mem1Factory));
}

// @brief Derive mem2 class
class Mem2HostDataSource : public MemHostDataSource {
public:
    virtual string getType() const {
        return ("mem2");
    }
};

// @brief Factory of mem2
HostDataSourcePtr
mem2Factory(const DatabaseConnection::ParameterMap&) {
    return (HostDataSourcePtr(new Mem2HostDataSource()));
}

// @brief Register mem2Factory
bool registerFactory2() {
    return (HostDataSourceFactory::registerFactory("mem2", mem2Factory));
}

// @brief Factory function returning 0
HostDataSourcePtr
factory0(const DatabaseConnection::ParameterMap&) {
    return (HostDataSourcePtr());
}

// @brief Test fixture class
class HostDataSourceFactoryTest : public ::testing::Test {
public:
    /// @brief Constructor
    HostDataSourceFactoryTest() = default;

    /// @brief Destructor
    virtual ~HostDataSourceFactoryTest() = default;

private:
    // @brief Prepares the class for a test.
    virtual void SetUp() {
    }

    // @brief Cleans up after the test.
    virtual void TearDown() {
        sources_.clear();
        HostDataSourceFactory::deregisterFactory("mem");
        HostDataSourceFactory::deregisterFactory("mem1");
        HostDataSourceFactory::deregisterFactory("mem2");
    }
public:
    HostDataSourceList sources_;
};

// Verify a factory can be registered and only once.
TEST_F(HostDataSourceFactoryTest, registerFactory) {
    EXPECT_TRUE(registerFactory());

    // Only once
    EXPECT_FALSE(registerFactory());
}

// Verify a factory registration can be checked.
TEST_F(HostDataSourceFactoryTest, registeredFactory) {
    // Not yet registered
    EXPECT_FALSE(HostDataSourceFactory::registeredFactory("mem"));
    EXPECT_FALSE(HostDataSourceFactory::registeredFactory("mem1"));

    // Register mem
    EXPECT_TRUE(registerFactory());

    // Now mem is registered but not mem1
    EXPECT_TRUE(HostDataSourceFactory::registeredFactory("mem"));
    EXPECT_FALSE(HostDataSourceFactory::registeredFactory("mem1"));
}

// Verify a factory can be registered and deregistered
TEST_F(HostDataSourceFactoryTest, deregisterFactory) {
    // Does not exist at the beginning
    EXPECT_FALSE(HostDataSourceFactory::deregisterFactory("mem"));

    // Register and deregister
    EXPECT_TRUE(registerFactory());
    EXPECT_TRUE(HostDataSourceFactory::deregisterFactory("mem"));
    EXPECT_FALSE(HostDataSourceFactory::registeredFactory("mem"));

    // No longer exists
    EXPECT_FALSE(HostDataSourceFactory::deregisterFactory("mem"));
}

// Verify a registered factory can be called
TEST_F(HostDataSourceFactoryTest, add) {
    EXPECT_TRUE(registerFactory());
    EXPECT_NO_THROW(HostDataSourceFactory::add(sources_, "type=mem"));
    ASSERT_EQ(1, sources_.size());
    EXPECT_EQ("mem", sources_[0]->getType());
}

// Verify that type is required
TEST_F(HostDataSourceFactoryTest, notype) {
    EXPECT_THROW(HostDataSourceFactory::add(sources_, "tp=mem"),
                 InvalidParameter);
    EXPECT_THROW(HostDataSourceFactory::add(sources_, "type=mem"),
                 InvalidType);
}

// Verify that factory must not return NULL
TEST_F(HostDataSourceFactoryTest, null) {
    EXPECT_TRUE(HostDataSourceFactory::registerFactory("mem", factory0));
    EXPECT_THROW(HostDataSourceFactory::add(sources_, "type=mem"),
                 Unexpected);
}

// Verify del class method
TEST_F(HostDataSourceFactoryTest, del) {
    // No sources at the beginning
    EXPECT_FALSE(HostDataSourceFactory::del(sources_, "mem"));

    // Add mem
    EXPECT_TRUE(registerFactory());
    EXPECT_NO_THROW(HostDataSourceFactory::add(sources_, "type=mem"));
    ASSERT_EQ(1, sources_.size());

    // Delete another
    EXPECT_FALSE(HostDataSourceFactory::del(sources_, "another"));

    // Delete mem
    EXPECT_TRUE(HostDataSourceFactory::del(sources_, "mem"));

    // No longer mem in sources
    EXPECT_FALSE(HostDataSourceFactory::del(sources_, "mem"));
}

// Verify add and del class method on multiple backends
TEST_F(HostDataSourceFactoryTest, multiple) {
    // Add foo twice
    EXPECT_TRUE(registerFactory1());
    EXPECT_NO_THROW(HostDataSourceFactory::add(sources_, "type=mem1"));
    EXPECT_NO_THROW(HostDataSourceFactory::add(sources_, "type=mem1"));

    // Add mem2 once
    EXPECT_TRUE(registerFactory2());
    EXPECT_NO_THROW(HostDataSourceFactory::add(sources_, "type=mem2"));

    // Delete them
    EXPECT_TRUE(HostDataSourceFactory::del(sources_, "mem1"));
    EXPECT_TRUE(HostDataSourceFactory::del(sources_, "mem2"));
    // Second instance of mem1
    EXPECT_TRUE(HostDataSourceFactory::del(sources_, "mem1"));

    // No more sources
    EXPECT_EQ(0, sources_.size());
    EXPECT_FALSE(HostDataSourceFactory::del(sources_, "mem1"));
    EXPECT_FALSE(HostDataSourceFactory::del(sources_, "mem2"));
}

}; // end of anonymous namespace
