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

// @brief Names of test backends
enum Names { FOOBAR, FOO, BAR };

// @brief Convert a name to a string
string toString(Names name) {
    switch (name) {
    case FOOBAR:
        return ("foobar");
    case FOO:
        return ("foo");
    default:
        return ("bar");
    }
}

// A host data source
template <Names NAME>
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

    virtual bool add(const HostPtr&) {
        return (false);
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
        return (toString(NAME));
    }
};

// @brief Factory function template
template <Names NAME>
BaseHostDataSource*
factory(const DatabaseConnection::ParameterMap& parameters) {
    return (new FakeHostDataSource<NAME>(parameters));
}

// @brief Register factory template
template <Names NAME>
bool registerFactory() {
    return (HostDataSourceFactory::registerFactory(toString(NAME),
                                                   factory<NAME>));
}

// @brief Factory function returning 0
BaseHostDataSource* factory0(const DatabaseConnection::ParameterMap&) {
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
        sources_.clear();
        HostDataSourceFactory::deregisterFactory("foobar");
        HostDataSourceFactory::deregisterFactory("foo");
        HostDataSourceFactory::deregisterFactory("bar");
    }
public:
    HostDataSourceList sources_;
};

// Verify a factory can be registered and only once.
TEST_F(HostDataSourceFactoryTest, registerFactory) {
    EXPECT_TRUE(registerFactory<Names::FOOBAR>());

    // Only once
    EXPECT_FALSE(registerFactory<Names::FOOBAR>());
}

// Verify a factory can be registered and deregistered
TEST_F(HostDataSourceFactoryTest, deregisterFactory) {
    // Does not exist at the beginning
    EXPECT_FALSE(HostDataSourceFactory::deregisterFactory("foobar"));

    // Register and deregister
    EXPECT_TRUE(registerFactory<Names::FOOBAR>());
    EXPECT_TRUE(HostDataSourceFactory::deregisterFactory("foobar"));

    // No longer exists
    EXPECT_FALSE(HostDataSourceFactory::deregisterFactory("foobar"));
}

// Verify a registered factory can be called
TEST_F(HostDataSourceFactoryTest, add) {
    EXPECT_TRUE(registerFactory<Names::FOOBAR>());
    EXPECT_NO_THROW(HostDataSourceFactory::add(sources_, "type=foobar"));
    ASSERT_EQ(1, sources_.size());
    EXPECT_EQ("foobar", sources_[0]->getType());
}

// Verify that type is required
TEST_F(HostDataSourceFactoryTest, notype) {
    EXPECT_THROW(HostDataSourceFactory::add(sources_, "tp=foobar"),
                 InvalidParameter);
    EXPECT_THROW(HostDataSourceFactory::add(sources_, "type=foobar"),
                 InvalidType);
}

// Verify that factory must not return NULL
TEST_F(HostDataSourceFactoryTest, null) {
    EXPECT_TRUE(HostDataSourceFactory::registerFactory("foobar", factory0));
    EXPECT_THROW(HostDataSourceFactory::add(sources_, "type=foobar"),
                 Unexpected);
}

// Verify del class method
TEST_F(HostDataSourceFactoryTest, del) {
    // No sources at the beginning
    EXPECT_FALSE(HostDataSourceFactory::del(sources_, "foobar"));

    // Add foobar
    EXPECT_TRUE(registerFactory<Names::FOOBAR>());
    EXPECT_NO_THROW(HostDataSourceFactory::add(sources_, "type=foobar"));
    ASSERT_EQ(1, sources_.size());

    // Delete another
    EXPECT_FALSE(HostDataSourceFactory::del(sources_, "another"));

    // Delete foobar
    EXPECT_TRUE(HostDataSourceFactory::del(sources_, "foobar"));

    // No longer foobar in sources
    EXPECT_FALSE(HostDataSourceFactory::del(sources_, "foobar"));
}

// Verify add and del class method on multiple backends
TEST_F(HostDataSourceFactoryTest, multiple) {
    // Add foo twice
    EXPECT_TRUE(registerFactory<Names::FOO>());
    EXPECT_NO_THROW(HostDataSourceFactory::add(sources_, "type=foo"));
    EXPECT_NO_THROW(HostDataSourceFactory::add(sources_, "type=foo"));

    // Add bar once
    EXPECT_TRUE(registerFactory<Names::BAR>());
    EXPECT_NO_THROW(HostDataSourceFactory::add(sources_, "type=bar"));

    // Delete them
    EXPECT_TRUE(HostDataSourceFactory::del(sources_, "foo"));
    EXPECT_TRUE(HostDataSourceFactory::del(sources_, "bar"));
    // Second instance of foo
    EXPECT_TRUE(HostDataSourceFactory::del(sources_, "foo"));

    // No more sources
    EXPECT_EQ(0, sources_.size());
    EXPECT_FALSE(HostDataSourceFactory::del(sources_, "foo"));
    EXPECT_FALSE(HostDataSourceFactory::del(sources_, "bar"));
}

}; // end of anonymous namespace
