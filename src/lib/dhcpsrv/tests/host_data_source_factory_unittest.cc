// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/host_data_source_factory.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::dhcp;

namespace {

// A host data source
class FakeHostDataSource : public BaseHostDataSource {
public:
    // @brief Constructor
    FakeHostDataSource(const DatabaseConnection::ParameterMap&) { }

    virtual ~FakeHostDataSource() { }

    // The base class is abstract so we need to define methods

    virtual ConstHostCollection
    getAll(const HWAddrPtr&, const DuidPtr&) const {
        return (ConstHostCollection());
    }

    virtual ConstHostCollection
    getAll(const Host::IdentifierType&, const uint8_t*, const size_t) const {
        return (ConstHostCollection());
    }

    virtual ConstHostCollection
    getAll4(const asiolink::IOAddress&) const {
        return (ConstHostCollection());
    }

    virtual ConstHostPtr
    get4(const SubnetID&, const HWAddrPtr&, const DuidPtr&) const {
        return (ConstHostPtr());
    }

    virtual ConstHostPtr
    get4(const SubnetID&, const Host::IdentifierType&,
         const uint8_t*, const size_t) const {
        return (ConstHostPtr());
    }

    virtual ConstHostPtr
    get4(const SubnetID&, const asiolink::IOAddress&) const {
        return (ConstHostPtr());
    }

    virtual ConstHostPtr
    get6(const SubnetID&, const DuidPtr&, const HWAddrPtr&) const {
        return (ConstHostPtr());
    }

    virtual ConstHostPtr
    get6(const SubnetID&, const Host::IdentifierType&,
         const uint8_t*, const size_t) const {
        return (ConstHostPtr());
    }

    virtual ConstHostPtr
    get6(const asiolink::IOAddress&, const uint8_t) const {
        return (ConstHostPtr());
    }

    virtual ConstHostPtr
    get6(const SubnetID&, const asiolink::IOAddress&) const {
        return (ConstHostPtr());
    }

    virtual void add(const HostPtr&) {
    }

    virtual bool del(const SubnetID&, const asiolink::IOAddress&) {
        return (false);
    }

    virtual bool del4(const SubnetID&, const Host::IdentifierType&,
                      const uint8_t*, const size_t) {
        return (false);
    }

    virtual bool del6(const SubnetID&, const Host::IdentifierType&,
                      const uint8_t*, const size_t) {
        return (false);
    }

    virtual string getType() const {
        return ("fake");
    }
};

// @brief Factory function
FakeHostDataSource* factory(const DatabaseConnection::ParameterMap& parameters) {
    return (new FakeHostDataSource(parameters));
}

// @brief Factory function returning 0
FakeHostDataSource* factory0(const DatabaseConnection::ParameterMap&) {
    return (0);
}

// @brief Test fixture class
class HostDataSourceFactoryTest : public ::testing::Test {
private:
    // @brief Prepares the class for a test.
    virtual void SetUp() {
    }

    // @brief Cleans up after the test.
    virtual void TearDown() {
        HostDataSourceFactory::destroy();
        HostDataSourceFactory::deregisterFactory("foobar");
    }
};

// Verify a factory can be registered and only once.
TEST_F(HostDataSourceFactoryTest, registerFactory) {
    EXPECT_TRUE(HostDataSourceFactory::registerFactory("foobar", factory));

    // Only once
    EXPECT_FALSE(HostDataSourceFactory::registerFactory("foobar", factory));
}

// Verify a factory can be registered and deregistered
TEST_F(HostDataSourceFactoryTest, deregisterFactory) {
    // Does not exist at the beginning
    EXPECT_FALSE(HostDataSourceFactory::deregisterFactory("foobar"));

    // Register and deregister
    EXPECT_TRUE(HostDataSourceFactory::registerFactory("foobar", factory));
    EXPECT_TRUE(HostDataSourceFactory::deregisterFactory("foobar"));

    // No longer exists
    EXPECT_FALSE(HostDataSourceFactory::deregisterFactory("foobar"));
}

// Verify a registered factory can be called
TEST_F(HostDataSourceFactoryTest, create) {
    EXPECT_TRUE(HostDataSourceFactory::registerFactory("foobar", factory));
    EXPECT_NO_THROW(HostDataSourceFactory::create("type=foobar"));
    HostDataSourcePtr& source = HostDataSourceFactory::getHostDataSourcePtr();
    ASSERT_TRUE(source);
    EXPECT_EQ("fake", source->getType());

    // Already tested?
    EXPECT_NO_THROW(HostDataSourceFactory::destroy());
    EXPECT_FALSE(source);
}

// Verify that type is required
TEST_F(HostDataSourceFactoryTest, notype) {
    EXPECT_THROW(HostDataSourceFactory::create("tp=foobar"), InvalidParameter);
    EXPECT_THROW(HostDataSourceFactory::create("type=foobar"), InvalidType);
}

// Verify that factory must not return NULL
TEST_F(HostDataSourceFactoryTest, null) {
    EXPECT_TRUE(HostDataSourceFactory::registerFactory("foobar", factory0));
    EXPECT_THROW(HostDataSourceFactory::create("type=foobar"), Unexpected);
}

}; // end of anonymous namespace
