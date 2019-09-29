// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
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
using namespace isc::db;
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
    size_t insert(const ConstHostPtr& host, bool overwrite) {
        if (overwrite) {
            ++inserts_;
        } else {
            ++adds_;
        }
        HostPtr host_copy(new Host(*host));
        store_.push_back(host_copy);
        return (0);
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
    void flush(size_t) {
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
    // entry has no IP reservation when inserted by the host manager.
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

/// @brief Test one backend class.
///
/// This class has one entry which is returned to any lookup.
class TestOneBackend : public BaseHostDataSource {
public:

    /// Constructor
    TestOneBackend() : value_() { }

    /// Destructor
    virtual ~TestOneBackend() { }

    ConstHostCollection getAll(const Host::IdentifierType&, const uint8_t*,
                               const size_t) const {
        return (getCollection());
    }

    ConstHostCollection getAll4(const SubnetID&) const {
        return (getCollection());
    }

    ConstHostCollection getAll6(const SubnetID&) const {
        return (getCollection());
    }

    ConstHostCollection getAllbyHostname(const std::string&) const {
        return (getCollection());
    }

    ConstHostCollection getAllbyHostname4(const std::string&,
                                          const SubnetID&) const {
        return (getCollection());
    }

    ConstHostCollection getAllbyHostname6(const std::string&,
                                          const SubnetID&) const {
        return (getCollection());
    }

    ConstHostCollection getPage4(const SubnetID&, size_t&, uint64_t,
                                 const HostPageSize&) const {
        return (getCollection());
    }

    ConstHostCollection getPage6(const SubnetID&, size_t&, uint64_t,
                                 const HostPageSize&) const {
        return (getCollection());
    }

    ConstHostCollection getAll4(const IOAddress&) const {
        return (getCollection());
    }

    ConstHostPtr get4(const SubnetID&, const Host::IdentifierType&,
                      const uint8_t*, const size_t) const {
        return (getOne());
    }

    ConstHostPtr get4(const SubnetID&, const IOAddress&) const {
        return (getOne());
    }

    ConstHostPtr get6(const SubnetID&, const Host::IdentifierType&,
                      const uint8_t*, const size_t) const {
        return (getOne());
    }

    ConstHostPtr get6(const IOAddress&, const uint8_t) const {
        return (getOne());
    }

    ConstHostPtr get6(const SubnetID&, const IOAddress&) const {
        return (getOne());
    }

    void add(const HostPtr&) {
    }

    bool del(const SubnetID&, const IOAddress&) {
        return (false);
    }

    bool del4(const SubnetID&, const Host::IdentifierType&,
              const uint8_t*, const size_t) {
        return (false);
    }

    bool del6(const SubnetID&, const Host::IdentifierType&,
              const uint8_t*, const size_t) {
        return (false);
    }

    std::string getType() const {
        return ("one");
    }

    /// Specific methods

    /// @brief Set the entry
    void setValue(const HostPtr& value) {
        value_ = value;
    }

protected:
    /// @brief Return collection
    ConstHostCollection getCollection() const {
        ConstHostCollection hosts;
        hosts.push_back(value_);
        return (hosts);
    }

    /// @brief Return one entry
    ConstHostPtr getOne() const {
        return(value_);
    }

    /// #brief The value
    HostPtr value_;
};

/// @brief TestOneBackend pointer type
typedef boost::shared_ptr<TestOneBackend> TestOneBackendPtr;

/// @brief Test no cache class.
///
/// This class looks like a cache but throws when insert() is called.
class TestNoCache : public MemHostDataSource, public CacheHostDataSource {
public:

    /// Destructor
    virtual ~TestNoCache() { }

    /// Override add
    void add(const HostPtr& host) {
        isc_throw(NotImplemented,
                  "add is not implemented: " << host->toText());
    }

    /// Insert throws
    size_t insert(const ConstHostPtr& host, bool overwrite) {
        isc_throw(NotImplemented,
                  "insert is not implemented: " << host->toText()
                  << " with overwrite: " << overwrite);
    }

    /// Remove throws
    bool remove(const HostPtr& host) {
        isc_throw(NotImplemented,
                  "remove is not implemented: " << host->toText());
    }

    /// Flush
    void flush(size_t) {
        isc_throw(NotImplemented, "flush is not implemented");
    }

    /// Size
    size_t size() const {
        return (0);
    }

    /// Capacity
    size_t capacity() const {
        return (0);
    }

    /// Type
    string getType() const {
        return ("nocache");
    }
};

/// @brief TestNoCache pointer type
typedef boost::shared_ptr<TestNoCache> TestNoCachePtr;

/// @brief Test fixture for testing generic negative cache handling.
class NegativeCacheTest : public ::testing::Test {
public:

    /// @brief Constructor.
    NegativeCacheTest() {
        HostMgr::create();

        // No cache.
        ncptr_.reset(new TestNoCache());
        auto nocacheFactory = [this](const DatabaseConnection::ParameterMap&) {
            return (ncptr_);
        };
        HostDataSourceFactory::registerFactory("nocache", nocacheFactory);
        HostMgr::addBackend("type=nocache");

        // One backend.
        obptr_.reset(new TestOneBackend());
        auto oneFactory = [this](const DatabaseConnection::ParameterMap&) {
            return (obptr_);
        };
        HostDataSourceFactory::registerFactory("one", oneFactory);
        HostMgr::addBackend("type=one");
    }

    /// @brief Destructor.
    virtual ~NegativeCacheTest() {
        HostDataSourceFactory::deregisterFactory("one");
        HostDataSourceFactory::deregisterFactory("nocache");
    }

    /// @brief Test one backend.
    TestOneBackendPtr obptr_;

    /// @brief Test no cache.
    TestNoCachePtr ncptr_;

    /// Test methods

    /// @brief Set negative caching.
    void setNegativeCaching() {
        ASSERT_TRUE(HostMgr::instance().checkCacheBackend());
        ASSERT_FALSE(HostMgr::instance().getNegativeCaching());
        HostMgr::instance().setNegativeCaching(true);
        ASSERT_TRUE(HostMgr::instance().getNegativeCaching());
    }

    void testGetAll();
    void testGet4();
    void testGet6();
};

/// Verify that getAll* methods ignore negative caching.
void NegativeCacheTest::testGetAll() {
    // Create a host reservation.
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.1",
                                                        Host::IDENT_HWADDR);
    ASSERT_TRUE(host);
    ASSERT_TRUE(host->getHWAddress());
    ASSERT_EQ("192.0.2.1", host->getIPv4Reservation().toText());

    // Make it a negative cached entry.
    host->setNegative(true);
    ASSERT_TRUE(host->getNegative());

    // Set the backend with it.
    obptr_->setValue(host);

    // Verifies getAll* return a collection with it.
    ConstHostCollection hosts;
    ASSERT_NO_THROW(hosts =
        HostMgr::instance().getAll(host->getIdentifierType(),
                                   &host->getIdentifier()[0],
                                   host->getIdentifier().size()));
    ASSERT_EQ(1, hosts.size());
    EXPECT_EQ(host, hosts[0]);

    ASSERT_NO_THROW(hosts =
                    HostMgr::instance().getAll4(host->getIPv4Reservation()));
    ASSERT_EQ(1, hosts.size());
    EXPECT_EQ(host, hosts[0]);
}

/// Verify that get4* methods handle negative caching.
void NegativeCacheTest::testGet4() {
    // Create a host reservation.
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.1",
                                                        Host::IDENT_HWADDR);
    ASSERT_TRUE(host);
    ASSERT_TRUE(host->getHWAddress());
    ASSERT_EQ("192.0.2.1", host->getIPv4Reservation().toText());

    // Make it a negative cached entry.
    host->setNegative(true);
    ASSERT_TRUE(host->getNegative());

    // Set the backend with it.
    obptr_->setValue(host);

    // Verifies get4 overloads return a null pointer.
    ConstHostPtr got;
    ASSERT_NO_THROW(got =
        HostMgr::instance().get4(host->getIPv4SubnetID(),
                                 host->getIdentifierType(),
                                 &host->getIdentifier()[0],
                                 host->getIdentifier().size()));
    EXPECT_FALSE(got);

    ASSERT_NO_THROW(got =
                    HostMgr::instance().get4(host->getIPv4SubnetID(),
                                             host->getIPv4Reservation()));
    EXPECT_FALSE(got);

    // Only getAny returns the negative cached entry.
    ASSERT_NO_THROW(got =
                    HostMgr::instance().get4Any(host->getIPv4SubnetID(),
                                                host->getIdentifierType(),
                                                &host->getIdentifier()[0],
                                                host->getIdentifier().size()));
    EXPECT_TRUE(got);
    EXPECT_EQ(host, got);
}

/// Verify that get6* methods handle negative caching.
void NegativeCacheTest::testGet6() {
    // Create a host reservation.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8::1",
                                                        Host::IDENT_DUID,
                                                        false);
    ASSERT_TRUE(host);
    ASSERT_TRUE(host->getDuid());

    // Get the address.
    IPv6ResrvRange resrvs = host->getIPv6Reservations();
    ASSERT_EQ(1, std::distance(resrvs.first, resrvs.second));
    const IOAddress& address = resrvs.first->second.getPrefix();
    ASSERT_EQ("2001:db8::1", address.toText());

    // Make it a negative cached entry.
    host->setNegative(true);
    ASSERT_TRUE(host->getNegative());

    // Set the backend with it.
    obptr_->setValue(host);

    // Verifies get6 overloads return a null pointer.
    ConstHostPtr got;
    ASSERT_NO_THROW(got =
                    HostMgr::instance().get6(host->getIPv6SubnetID(),
                                             host->getIdentifierType(),
                                             &host->getIdentifier()[0],
                                             host->getIdentifier().size()));
    EXPECT_FALSE(got);

    ASSERT_NO_THROW(got = HostMgr::instance().get6(address, 128));
    EXPECT_FALSE(got);

    ASSERT_NO_THROW(got =
                    HostMgr::instance().get6(host->getIPv6SubnetID(),
                                             address));
    EXPECT_FALSE(got);

    // Only getAny returns the negative cached entry.
    ASSERT_NO_THROW(got =
                    HostMgr::instance().get6Any(host->getIPv6SubnetID(),
                                                host->getIdentifierType(),
                                                &host->getIdentifier()[0],
                                                host->getIdentifier().size()));
    EXPECT_TRUE(got);
    EXPECT_EQ(host, got);
}

/// Verify that getAll* methods ignore negative caching.
TEST_F(NegativeCacheTest, getAll) {
    testGetAll();
}

/// Verify that get4* methods handle negative caching.
TEST_F(NegativeCacheTest, get4) {
    testGet4();
}

/// Verify that get6* methods handle negative caching.
TEST_F(NegativeCacheTest, get6) {
    testGet6();
}

/// Verify that getAll* methods behavior does not change with
/// host manager negative caching.
TEST_F(NegativeCacheTest, getAllwithNegativeCaching) {
    setNegativeCaching();
    testGetAll();
}

/// Verify that get4* methods behavior does not change with
/// host manager negative caching.
TEST_F(NegativeCacheTest, get4withNegativeCaching) {
    setNegativeCaching();
    testGet4();
}

/// Verify that get6* methods behavior does not change with
/// host manager negative caching.
TEST_F(NegativeCacheTest, get6withNegativeCaching) {
    setNegativeCaching();
    testGet6();
}

}; // end of anonymous namespace
