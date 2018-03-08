// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/cache_host_data_source.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/testutils/host_data_source_utils.h>
#include <dhcpsrv/testutils/memory_host_data_source.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Test dump cache class.
class TestHostCache : public MemHostDataSource, public CacheHostDataSource {
public:

    /// Constructor
    TestHostCache() : adds_(0), inserts_(0) { }

    /// Destructor
    virtual ~TestHostCache() { }

    /// Override add
    void add(const HostPtr& host) {
        isc_throw(NotImplemented,
                  "add is not implemented: " << host->toText());
    }

    /// Insert
    bool insert(const ConstHostPtr& host, int& overwrite) {
        if (overwrite < 0) {
            ++adds_;
        } else {
            ++inserts_;
        }
        HostPtr host_copy(new Host(*host));
        store_.push_back(host_copy);
        return (true);
    }

    /// Remove
    bool remove(const HostPtr& host) {
        for (auto h = store_.begin(); h != store_.end(); ++h) {
            if (*h == host) {
                store_.erase(h);
                return (true);
            }
        }
        return (false);
    }

    /// Flush
    void flush(size_t count) {
        isc_throw(NotImplemented, "flush is not implemented");
    }

    /// Size
    size_t size() const {
        return (store_.size());
    }

    /// Capacity
    size_t capacity() const {
        return (0);
    }

    /// Type
    string getType() const {
        return ("cache");
    }

    /// Add counter
    size_t adds_;

    /// Insert counter
    size_t inserts_;
};

/// @brief TestHostCache pointer type
typedef boost::shared_ptr<TestHostCache> TestHostCachePtr;

/// @brief Test data source class.
class TestHostDataSource : public MemHostDataSource {
public:

    /// Destructor
    virtual ~TestHostDataSource() { }

    /// Type
    string getType() const {
        return ("test");
    }
};

/// @brief TestHostDataSource pointer type
typedef boost::shared_ptr<TestHostDataSource> TestHostDataSourcePtr;

/// @brief Test fixture for testing cache feature.
class HostCacheTest : public ::testing::Test {
public:

    /// @brief Constructor.
    HostCacheTest() {
        HostMgr::create();

        // Host cache.
        hcptr_.reset(new TestHostCache());
        auto cacheFactory = [this](const DatabaseConnection::ParameterMap&) {
            return (hcptr_);
        };
        HostDataSourceFactory::registerFactory("cache", cacheFactory);
        HostMgr::addBackend("type=cache");

        // Host data source.
        memptr_.reset(new TestHostDataSource());
        auto testFactory = [this](const DatabaseConnection::ParameterMap&) {
            return (memptr_);
        };
        HostDataSourceFactory::registerFactory("test", testFactory);
        HostMgr::addBackend("type=test");
    }

    /// @brief Destructor.
    virtual ~HostCacheTest() {
        HostDataSourceFactory::deregisterFactory("test");
        HostDataSourceFactory::deregisterFactory("cache");
    }

    /// @brief Test host cache.
    TestHostCachePtr hcptr_;

    /// @brief Test host data source.
    TestHostDataSourcePtr memptr_;
};

// Check basic cache feature for IPv4.
TEST_F(HostCacheTest, identifier4) {
    // Check we have what we need.
    ASSERT_TRUE(hcptr_);
    EXPECT_TRUE(HostMgr::checkCacheBackend());
    EXPECT_EQ(0, hcptr_->size());
    EXPECT_EQ(0, hcptr_->inserts_);
    ASSERT_TRUE(memptr_);

    // Create a host reservation.
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.1",
                                                        Host::IDENT_HWADDR);
    ASSERT_TRUE(host);  // Make sure the host is generated properly.
    const IOAddress& address = host->getIPv4Reservation();

    // Try to add it to the host data source.
    ASSERT_NO_THROW(memptr_->add(host));

    // Try to get it cached.
    ConstHostPtr got = HostMgr::instance().get4(host->getIPv4SubnetID(),
                                                host->getIdentifierType(),
                                                &host->getIdentifier()[0],
                                                host->getIdentifier().size());
    ASSERT_TRUE(got);
    HostDataSourceUtils::compareHosts(got, host);

    // Verify it was cached.
    EXPECT_EQ(1, hcptr_->size());
    EXPECT_EQ(1, hcptr_->inserts_);

    // Remove it from test host data source.
    EXPECT_TRUE(memptr_->del(host->getIPv4SubnetID(), address));
    
    // It is cached so we can still get it.
    got = HostMgr::instance().get4(host->getIPv4SubnetID(),
                                   host->getIdentifierType(),
                                   &host->getIdentifier()[0],
                                   host->getIdentifier().size());
    ASSERT_TRUE(got);
    HostDataSourceUtils::compareHosts(got, host);
                                                
    // Even by address.
    got = HostMgr::instance().get4(host->getIPv4SubnetID(), address);
    ASSERT_TRUE(got);
    HostDataSourceUtils::compareHosts(got, host);

    // Verify cache status.
    EXPECT_EQ(1, hcptr_->size());
    EXPECT_EQ(1, hcptr_->inserts_);
}

// Check basic cache feature for IPv6.
TEST_F(HostCacheTest, identifier6) {
    // Check we have what we need.
    ASSERT_TRUE(hcptr_);
    EXPECT_TRUE(HostMgr::checkCacheBackend());
    EXPECT_EQ(0, hcptr_->size());
    EXPECT_EQ(0, hcptr_->inserts_);
    ASSERT_TRUE(memptr_);

    // Create a host reservation.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8::1",
                                                        Host::IDENT_DUID,
                                                        false);
    ASSERT_TRUE(host);  // Make sure the host is generated properly.
    
    // Get the address.
    IPv6ResrvRange resrvs = host->getIPv6Reservations();
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    const IOAddress& address = resrvs.first->second.getPrefix();
    ASSERT_EQ("2001:db8::1", address.toText());

    // Try to add it to the host data source.
    ASSERT_NO_THROW(memptr_->add(host));

    // Try to get it cached.
    ConstHostPtr got = HostMgr::instance().get6(host->getIPv6SubnetID(),
                                                host->getIdentifierType(),
                                                &host->getIdentifier()[0],
                                                host->getIdentifier().size());
    ASSERT_TRUE(got);
    HostDataSourceUtils::compareHosts(got, host);

    // Verify it was cached.
    EXPECT_EQ(1, hcptr_->size());
    EXPECT_EQ(1, hcptr_->inserts_);

    // Remove it from test host data source.
    EXPECT_TRUE(memptr_->del(host->getIPv6SubnetID(), address));
    
    // It is cached so we can still get it.
    got = HostMgr::instance().get6(host->getIPv6SubnetID(),
                                   host->getIdentifierType(),
                                   &host->getIdentifier()[0],
                                   host->getIdentifier().size());
    ASSERT_TRUE(got);
    HostDataSourceUtils::compareHosts(got, host);
                                                
    // Even by address.
    got = HostMgr::instance().get6(host->getIPv6SubnetID(), address);
    ASSERT_TRUE(got);
    HostDataSourceUtils::compareHosts(got, host);

    // Verify cache status.
    EXPECT_EQ(1, hcptr_->size());
    EXPECT_EQ(1, hcptr_->inserts_);
}

// Check by address caching for IPv4.
TEST_F(HostCacheTest, address4) {
    // Check we have what we need.
    ASSERT_TRUE(hcptr_);
    EXPECT_TRUE(HostMgr::checkCacheBackend());
    EXPECT_EQ(0, hcptr_->size());
    EXPECT_EQ(0, hcptr_->inserts_);
    ASSERT_TRUE(memptr_);

    // Create a host reservation.
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.1",
                                                        Host::IDENT_HWADDR);
    ASSERT_TRUE(host);  // Make sure the host is generated properly.
    const IOAddress& address = host->getIPv4Reservation();

    // Try to add it to the host data source.
    ASSERT_NO_THROW(memptr_->add(host));

    // Try to get it cached.
    ConstHostPtr got = HostMgr::instance().get4(host->getIPv4SubnetID(),
                                                address);
    ASSERT_TRUE(got);
    HostDataSourceUtils::compareHosts(got, host);

    // Verify it was cached.
    EXPECT_EQ(1, hcptr_->size());
    EXPECT_EQ(1, hcptr_->inserts_);

    // Remove it from test host data source.
    EXPECT_TRUE(memptr_->del(host->getIPv4SubnetID(), address));
    
    // It is cached so we can still get it.
    got = HostMgr::instance().get4(host->getIPv4SubnetID(), address);
    ASSERT_TRUE(got);
    HostDataSourceUtils::compareHosts(got, host);
                                                
    // Even by identifier.
    got = HostMgr::instance().get4(host->getIPv4SubnetID(),
                                   host->getIdentifierType(),
                                   &host->getIdentifier()[0],
                                   host->getIdentifier().size());
    ASSERT_TRUE(got);
    HostDataSourceUtils::compareHosts(got, host);

    // Verify cache status.
    EXPECT_EQ(1, hcptr_->size());
    EXPECT_EQ(1, hcptr_->inserts_);
}

// Check by address caching for IPv6.
TEST_F(HostCacheTest, address6) {
    // Check we have what we need.
    ASSERT_TRUE(hcptr_);
    EXPECT_TRUE(HostMgr::checkCacheBackend());
    EXPECT_EQ(0, hcptr_->size());
    EXPECT_EQ(0, hcptr_->inserts_);
    ASSERT_TRUE(memptr_);

    // Create a host reservation.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8::1",
                                                        Host::IDENT_DUID,
                                                        false);
    ASSERT_TRUE(host);  // Make sure the host is generated properly.
    
    // Get the address.
    IPv6ResrvRange resrvs = host->getIPv6Reservations();
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    const IOAddress& address = resrvs.first->second.getPrefix();
    ASSERT_EQ("2001:db8::1", address.toText());

    // Try to add it to the host data source.
    ASSERT_NO_THROW(memptr_->add(host));

    // Try to get it cached.
    ConstHostPtr got = HostMgr::instance().get6(host->getIPv6SubnetID(),
                                                address);
    ASSERT_TRUE(got);
    HostDataSourceUtils::compareHosts(got, host);

    // Verify it was cached.
    EXPECT_EQ(1, hcptr_->size());
    EXPECT_EQ(1, hcptr_->inserts_);

    // Remove it from test host data source.
    EXPECT_TRUE(memptr_->del(host->getIPv6SubnetID(), address));
    
    // It is cached so we can still get it.
    got = HostMgr::instance().get6(host->getIPv6SubnetID(), address);
    ASSERT_TRUE(got);
    HostDataSourceUtils::compareHosts(got, host);
                                                
    // Even by identifier.
    got = HostMgr::instance().get6(host->getIPv6SubnetID(),
                                   host->getIdentifierType(),
                                   &host->getIdentifier()[0],
                                   host->getIdentifier().size());
    ASSERT_TRUE(got);
    HostDataSourceUtils::compareHosts(got, host);

    // Verify cache status.
    EXPECT_EQ(1, hcptr_->size());
    EXPECT_EQ(1, hcptr_->inserts_);
}

// Check negative cache feature for IPv4.
TEST_F(HostCacheTest, negativeIdentifier4) {
    // Check we have what we need.
    ASSERT_TRUE(hcptr_);
    EXPECT_TRUE(HostMgr::checkCacheBackend());
    EXPECT_EQ(0, hcptr_->size());
    EXPECT_EQ(0, hcptr_->adds_);
    ASSERT_TRUE(memptr_);
    ASSERT_FALSE(HostMgr::instance().getNegativeCaching());

    // Create a host reservation.
    // We will not add it anywhere, just will use its values.
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.1", Host::IDENT_HWADDR);
    ASSERT_TRUE(host);

    // Try to get it cached.
    ConstHostPtr got = HostMgr::instance().get4(host->getIPv4SubnetID(),
                                                host->getIdentifierType(),
                                                &host->getIdentifier()[0],
                                                host->getIdentifier().size());
    ASSERT_FALSE(got);
    // Again to be sure it was not negatively cached.
    got = HostMgr::instance().get4Any(host->getIPv4SubnetID(),
                                      host->getIdentifierType(),
                                      &host->getIdentifier()[0],
                                      host->getIdentifier().size());
    ASSERT_FALSE(got);

    // Enable negative caching.
    HostMgr::instance().setNegativeCaching(true);
    ASSERT_TRUE(HostMgr::instance().getNegativeCaching());

    // Try it again. There is no such host, but this time negative cache is enabled,
    // so this negative response will be added to the cache.
    got = HostMgr::instance().get4(host->getIPv4SubnetID(),
                                   host->getIdentifierType(),
                                   &host->getIdentifier()[0],
                                   host->getIdentifier().size());
    ASSERT_FALSE(got);
    EXPECT_EQ(1, hcptr_->size());
    EXPECT_EQ(1, hcptr_->adds_);
    got = HostMgr::instance().get4Any(host->getIPv4SubnetID(),
                                      host->getIdentifierType(),
                                      &host->getIdentifier()[0],
                                      host->getIdentifier().size());
    ASSERT_TRUE(got);
    EXPECT_TRUE(got->getNegative());

    // Look at inside the negative cached value.
    EXPECT_EQ(host->getIPv4SubnetID(), got->getIPv4SubnetID());
    EXPECT_EQ(host->getIdentifierType(), got->getIdentifierType());
    ASSERT_EQ(host->getIdentifier().size(), got->getIdentifier().size());
    EXPECT_EQ(0, memcmp(&host->getIdentifier()[0],
                        &got->getIdentifier()[0],
                        host->getIdentifier().size()));
    EXPECT_EQ("0.0.0.0", got->getIPv4Reservation().toText());

    // get4() (vs get4Any()) does not return negative cached values.
    got = HostMgr::instance().get4(host->getIPv4SubnetID(),
                                   host->getIdentifierType(),
                                   &host->getIdentifier()[0],
                                   host->getIdentifier().size());
    EXPECT_FALSE(got);

    // Verify cache status.
    EXPECT_EQ(1, hcptr_->size());
    EXPECT_EQ(1, hcptr_->adds_);
    EXPECT_EQ(0, hcptr_->inserts_);

    // We can verify other overloads of get4() but the hwaddr/duid is
    // not implemented by the memory test backend and the negative cache
    // entry has no IP reservation simply because it was not known when
    // it is created. And there is no by address negative cache because
    // it is not allowed to create a host object, even a fake one, without
    // an identifier. Now for performance the by identifier negative cache
    // is critical, for by address it is better to optimize the out-of-
    // pools case...
}

// Check negative cache feature for IPv6.
TEST_F(HostCacheTest, negativeIdentifier6) {
    // Check we have what we need.
    ASSERT_TRUE(hcptr_);
    EXPECT_TRUE(HostMgr::checkCacheBackend());
    EXPECT_EQ(0, hcptr_->size());
    EXPECT_EQ(0, hcptr_->adds_);
    ASSERT_TRUE(memptr_);

    // Create a host reservation.
    // We will not add it anywhere, just will use its values.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8::1",
                                                        Host::IDENT_DUID,
                                                        false);
    ASSERT_TRUE(host);  // Make sure the host is generated properly.

    // Do not add it to the host data source.

    // Try to get it cached.
    ConstHostPtr got = HostMgr::instance().get6(host->getIPv6SubnetID(),
                                                host->getIdentifierType(),
                                                &host->getIdentifier()[0],
                                                host->getIdentifier().size());
    ASSERT_FALSE(got);
    // Again to be sure it was not negatively cached.
    got = HostMgr::instance().get6Any(host->getIPv6SubnetID(),
                                      host->getIdentifierType(),
                                      &host->getIdentifier()[0],
                                      host->getIdentifier().size());
    ASSERT_FALSE(got);

    // Enable negative caching.
    HostMgr::instance().setNegativeCaching(true);
    ASSERT_TRUE(HostMgr::instance().getNegativeCaching());

    // Try it but it will be cached only when get6 (vs get6Any) is called.
    got = HostMgr::instance().get6Any(host->getIPv6SubnetID(),
                                      host->getIdentifierType(),
                                      &host->getIdentifier()[0],
                                      host->getIdentifier().size());
    ASSERT_FALSE(got);
    EXPECT_EQ(0, hcptr_->size());
    EXPECT_EQ(0, hcptr_->adds_);

    got = HostMgr::instance().get6(host->getIPv6SubnetID(),
                                   host->getIdentifierType(),
                                   &host->getIdentifier()[0],
                                   host->getIdentifier().size());
    ASSERT_FALSE(got);

    // There is a negative cached value now.
    EXPECT_EQ(1, hcptr_->size());
    EXPECT_EQ(1, hcptr_->adds_);
    got = HostMgr::instance().get6Any(host->getIPv6SubnetID(),
                                      host->getIdentifierType(),
                                      &host->getIdentifier()[0],
                                      host->getIdentifier().size());
    ASSERT_TRUE(got);
    EXPECT_TRUE(got->getNegative());

    // Look at inside the negative cached value.
    EXPECT_EQ(host->getIPv6SubnetID(), got->getIPv6SubnetID());
    EXPECT_EQ(host->getIdentifierType(), got->getIdentifierType());
    ASSERT_EQ(host->getIdentifier().size(), got->getIdentifier().size());
    EXPECT_EQ(0, memcmp(&host->getIdentifier()[0],
                        &got->getIdentifier()[0],
                        host->getIdentifier().size()));
    EXPECT_FALSE(got->hasIPv6Reservation());

    // get6() (vs get6Any()) does not return negative cached values.
    got = HostMgr::instance().get6(host->getIPv6SubnetID(),
                                   host->getIdentifierType(),
                                   &host->getIdentifier()[0],
                                   host->getIdentifier().size());
    EXPECT_FALSE(got);

    // Verify cache status.
    EXPECT_EQ(1, hcptr_->size());
    EXPECT_EQ(1, hcptr_->adds_);
    EXPECT_EQ(0, hcptr_->inserts_);

    // No other tests, cf negativeIdentifier4 end comment.
}

// Check that negative caching by address is not done for IPv4.
TEST_F(HostCacheTest, negativeAddress4) {
    // Check we have what we need.
    ASSERT_TRUE(hcptr_);
    EXPECT_TRUE(HostMgr::checkCacheBackend());
    EXPECT_EQ(0, hcptr_->size());
    EXPECT_EQ(0, hcptr_->adds_);
    ASSERT_TRUE(memptr_);

    // Create a host reservation.
    // We will not add it anywhere, just will use its values.
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.1",
                                                        Host::IDENT_HWADDR);
    ASSERT_TRUE(host);  // Make sure the host is generated properly.
    const IOAddress& address = host->getIPv4Reservation();

    // Do not add it to the host data source.

    // Enable negative caching.
    HostMgr::instance().setNegativeCaching(true);
    ASSERT_TRUE(HostMgr::instance().getNegativeCaching());

    // Try to get it in negative cache.
    ConstHostPtr got = HostMgr::instance().get4(host->getIPv4SubnetID(),
                                                address);
    ASSERT_FALSE(got);
    EXPECT_EQ(0, hcptr_->size());
    EXPECT_EQ(0, hcptr_->adds_);
}

// Check that negative caching by address is not done for IPv6.
TEST_F(HostCacheTest, negativeAddress6) {
    // Check we have what we need.
    ASSERT_TRUE(hcptr_);
    EXPECT_TRUE(HostMgr::checkCacheBackend());
    EXPECT_EQ(0, hcptr_->size());
    EXPECT_EQ(0, hcptr_->adds_);
    ASSERT_TRUE(memptr_);

    // Create a host reservation.
    // We will not add it anywhere, just will use its values.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8::1",
                                                        Host::IDENT_DUID,
                                                        false);
    ASSERT_TRUE(host);  // Make sure the host is generated properly.
    
    // Get the address.
    IPv6ResrvRange resrvs = host->getIPv6Reservations();
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    const IOAddress& address = resrvs.first->second.getPrefix();
    ASSERT_EQ("2001:db8::1", address.toText());

    // Do not add it to the host data source.

    // Enable negative caching.
    HostMgr::instance().setNegativeCaching(true);
    ASSERT_TRUE(HostMgr::instance().getNegativeCaching());

    // Try to get it in negative cache.
    ConstHostPtr got = HostMgr::instance().get6(host->getIPv6SubnetID(),
                                                address);
    ASSERT_FALSE(got);
    EXPECT_EQ(0, hcptr_->size());
    EXPECT_EQ(0, hcptr_->adds_);
}

}; // end of anonymous namespace
