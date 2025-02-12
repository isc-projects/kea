// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the cache features.

#include <config.h>

#include <host_cache.h>
#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_rng.h>
#include <database/db_exceptions.h>
#include <dhcpsrv/testutils/host_data_source_utils.h>
#include <dhcpsrv/testutils/generic_host_data_source_unittest.h>
#include <dhcpsrv/testutils/memory_host_data_source.h>

#include <gtest/gtest.h>

#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::host_cache;

namespace {

/// @brief Test version of the Host Cache class.
class TestHostCache : public HostCache {
public:

    /// @brief Constructor
    TestHostCache() : HostCache(), hits_(0), inserts_(0), conflicts_(0) {
    }

    /// @brief Destructor
    virtual ~TestHostCache() = default;

    /// @brief Cache an entry.
    ///
    /// @param host host to cache.
    void cache(const ConstHostPtr& host) {
        ++inserts_;
        conflicts_ += insert(host, true);
    }

    /// @brief Count a new hit
    void hit() {
        ++hits_;
    }

    /// @brief Host Cache hits.
    uint64_t hits_;

    /// @brief Host Cache inserts.
    uint64_t inserts_;

    /// @brief Host Cache conflicts.
    uint64_t conflicts_;
};

/// @brief TestHostCache pointer type
typedef boost::shared_ptr<TestHostCache> TestHostCachePtr;

/// @brief Test host data source class.
///
/// This data source has 3 parts:
///  - a host cache
///  - a memory host data source
///  - a fake manager exposing a base host data source interface:
///   * get's and del's are forwarded to the cache then the memory backend
///    when required
///   * responses from the memory backend are inserted to the cache
///   * add's (used by generic tests to setup state) are sent directly
///    to the memory backend.

class TestHostDataSource : public BaseHostDataSource {
public:

    /// @brief Constructor.
    TestHostDataSource() {
        hcptr_.reset(new TestHostCache());
        memptr_.reset(new MemHostDataSource());
    }

    /// @brief Destructor.
    virtual ~TestHostDataSource() = default;

    /// @brief Return all hosts connected to any subnet for which reservations
    /// have been made using a specified identifier.
    ///
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return Empty collection of const @c Host objects.
    virtual ConstHostCollection
    getAll(const Host::IdentifierType& identifier_type,
           const uint8_t* identifier_begin,
           const size_t identifier_len) const {
        // Bypass cache.
        return (memptr_->getAll(identifier_type, identifier_begin,
                                identifier_len));
    }

    /// @brief Return all hosts in a DHCPv4 specified subnet.
    ///
    /// @param subnet_id Subnet identifier.
    virtual ConstHostCollection
    getAll4(const SubnetID& subnet_id) const {
        // Bypass cache.
        return (memptr_->getAll4(subnet_id));
    }

    /// @brief Return all hosts in a DHCPv6 specified subnet.
    ///
    /// @param subnet_id Subnet identifier.
    virtual ConstHostCollection
    getAll6(const SubnetID& subnet_id) const {
        // Bypass cache.
        return (memptr_->getAll6(subnet_id));
    }

    /// @brief Return all hosts with a hostname.
    ///
    /// @param hostname The lower case hostname.
    virtual ConstHostCollection
    getAllbyHostname(const std::string& hostname) const {
        // Bypass cache.
        return (memptr_->getAllbyHostname(hostname));
    }

    /// @brief Return all hosts with a hostname in a DHCPv4 subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    virtual ConstHostCollection
    getAllbyHostname4(const std::string& hostname,
                      const SubnetID& subnet_id) const {
        // Bypass cache.
        return (memptr_->getAllbyHostname4(hostname, subnet_id));
    }

    /// @brief Return all hosts with a hostname in a DHCPv6 subnet.
    ///
    /// @param hostname The lower case hostname.
    /// @param subnet_id Subnet identifier.
    virtual ConstHostCollection
    getAllbyHostname6(const std::string& hostname,
                      const SubnetID& subnet_id) const {
        // Bypass cache.
        return (memptr_->getAllbyHostname6(hostname, subnet_id));
    }

    /// @brief Return range of hosts in a DHCPv4 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    virtual ConstHostCollection
    getPage4(const SubnetID& subnet_id,
             size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const {
        // Bypass cache.
        return (memptr_->getPage4(subnet_id, source_index,
                                  lower_host_id, page_size));
    }

    /// @brief Return range of hosts in a DHCPv6 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    virtual ConstHostCollection
    getPage6(const SubnetID& subnet_id,
             size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const {
        // Bypass cache.
        return (memptr_->getPage6(subnet_id, source_index,
                                  lower_host_id, page_size));
    }

    /// @brief Return range of hosts.
    ///
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    /// @return Collection of const @c Host objects (may be empty).
    virtual ConstHostCollection
    getPage4(size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const {
        // Bypass cache.
        return (memptr_->getPage4(source_index, lower_host_id, page_size));
    }

    /// @brief Return range of hosts.
    ///
    /// @param source_index Index of the source (unused).
    /// @param lower_host_id Host identifier used as lower bound for the
    /// returned range.
    /// @param page_size maximum size of the page returned.
    /// @return Collection of const @c Host objects (may be empty).
    virtual ConstHostCollection
    getPage6(size_t& source_index,
             uint64_t lower_host_id,
             const HostPageSize& page_size) const {
        // Bypass cache.
        return (memptr_->getPage6(source_index, lower_host_id, page_size));
    }

    /// @brief Returns a collection of hosts using the specified IPv4 address.
    ///
    /// @param address IPv4 address for which the @c Host object is searched.
    /// @return Empty collection of const @c Host objects.
    virtual ConstHostCollection
    getAll4(const asiolink::IOAddress& address) const {
        // Bypass cache.
        return (memptr_->getAll4(address));
    }

    /// @brief Returns a host connected to the IPv4 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
    virtual ConstHostPtr
    get4(const SubnetID& subnet_id,
         const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin,
         const size_t identifier_len) const {
        ConstHostPtr host = hcptr_->get4(subnet_id, identifier_type,
                                         identifier_begin, identifier_len);
        if (host) {
            hcptr_->hit();
        } else {
            host = memptr_->get4(subnet_id, identifier_type,
                                 identifier_begin, identifier_len);
            cache(host);
        }
        return (host);
    }

    /// @brief Returns a host connected to the IPv4 subnet and having
    /// a reservation for a specified IPv4 address.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address.
    /// @return Const @c Host object using a specified IPv4 address.
    virtual ConstHostPtr
    get4(const SubnetID& subnet_id,
         const asiolink::IOAddress& address) const {
        ConstHostPtr host = hcptr_->get4(subnet_id, address);
        if (host) {
            hcptr_->hit();
        } else {
            host = memptr_->get4(subnet_id, address);
            cache(host);
        }
        return (host);
    }

    /// @brief Returns all hosts connected to the IPv4 subnet and having
    /// a reservation for a specified address.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll4(const SubnetID& subnet_id,
            const asiolink::IOAddress& address) const {
        ConstHostCollection hosts;
        auto host = get4(subnet_id, address);
        if (host) {
            hosts.push_back(host);
        }
        return (hosts);
    }

    /// @brief Returns a host connected to the IPv6 subnet.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return Const @c Host object for which reservation has been made using
    /// the specified identifier.
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id,
         const Host::IdentifierType& identifier_type,
         const uint8_t* identifier_begin,
         const size_t identifier_len) const {
        ConstHostPtr host = hcptr_->get6(subnet_id, identifier_type,
                                         identifier_begin, identifier_len);
        if (host) {
            hcptr_->hit();
        } else {
            host = memptr_->get6(subnet_id, identifier_type,
                                 identifier_begin, identifier_len);
            cache(host);
        }
        return (host);
    }

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    /// @return Const @c Host object using a specified IPv6 prefix.
    virtual ConstHostPtr
    get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len) const {
        ConstHostPtr host = hcptr_->get6(prefix, prefix_len);
        if (host) {
            hcptr_->hit();
        } else {
            host = memptr_->get6(prefix, prefix_len);
            cache(host);
        }
        return (host);
    }

    /// @brief Returns a host connected to the IPv6 subnet and having
    /// a reservation for a specified IPv6 address or prefix.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv6 address/prefix.
    /// @return Const @c Host object using a specified IPv6 address/prefix.
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id, const asiolink::IOAddress& address) const {
        ConstHostPtr host = hcptr_->get6(subnet_id, address);
        if (host) {
            hcptr_->hit();
        } else {
            host = memptr_->get6(subnet_id, address);
            cache(host);
        }
        return (host);
    }

    /// @brief Returns all hosts connected to the IPv6 subnet and having
    /// a reservation for a specified address.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param address reserved IPv4 address
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll6(const SubnetID& subnet_id,
            const asiolink::IOAddress& address) const {
        ConstHostCollection hosts;
        auto host = get6(subnet_id, address);
        if (host) {
            hosts.push_back(host);
        }
        return (hosts);
    }

    /// @brief Returns all hosts having
    /// a reservation for a specified address.
    ///
    /// @param address reserved IPv4 address
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection getAll6(const IOAddress& address) const {
        // Bypass cache.
        return (memptr_->getAll6(address));
    }

    /// @brief Adds a new host to the collection.
    ///
    /// @param host Pointer to the new @c Host object being added.
    /// @return true if addition was successful.
    virtual void add(const HostPtr& host) {
        // Used for tests so send directly to the memory backend.
        // Take a copy as some tests modify the host
        HostPtr host_copy(new Host(*host));
        memptr_->add(host_copy);
    }

    /// @brief Attempts to delete a host by (subnet-id, address)
    ///
    /// @param subnet_id subnet identifier.
    /// @param addr specified address.
    /// @return true if deletion was successful, false if the host was not there.
    /// @throw various exceptions in case of errors
    virtual bool del(const SubnetID& subnet_id,
                     const asiolink::IOAddress& addr) {
        hcptr_->del(subnet_id, addr);
        return (memptr_->del(subnet_id, addr));
    }

    /// @brief Attempts to delete a host by (subnet-id4, identifier, identifier-type)
    ///
    /// @param subnet_id IPv4 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return true if deletion was successful, false if the host was not there.
    /// @throw various exceptions in case of errors
    virtual bool del4(const SubnetID& subnet_id,
                      const Host::IdentifierType& identifier_type,
                      const uint8_t* identifier_begin,
                      const size_t identifier_len) {
        hcptr_->del4(subnet_id, identifier_type, identifier_begin,
                     identifier_len);
        return (memptr_->del4(subnet_id, identifier_type,identifier_begin,
                              identifier_len));
    }

    /// @brief Attempts to delete a host by (subnet-id6, identifier, identifier-type)
    ///
    /// @param subnet_id IPv6 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return true if deletion was successful, false if the host was not there.
    /// @throw various exceptions in case of errors
    virtual bool del6(const SubnetID& subnet_id,
                      const Host::IdentifierType& identifier_type,
                      const uint8_t* identifier_begin,
                      const size_t identifier_len) {
        hcptr_->del6(subnet_id, identifier_type, identifier_begin,
                     identifier_len);
        return (memptr_->del6(subnet_id, identifier_type,identifier_begin,
                              identifier_len));
    }

    /// @brief Implements @ref BaseHostDataSource::update() for TestHostDataSource.
    ///
    /// Attempts to update an existing host entry.
    ///
    /// @param host the host up to date with the requested changes
    void update(HostPtr const& host) {
        HostPtr host_copy(new Host(*host));
        memptr_->update(host_copy);
    }

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "memfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const {
        return ("test");
    }

    /// @brief Controls whether IP reservations are unique or non-unique.
    ///
    /// In a typical case, the IP reservations are unique and backends verify
    /// prior to adding a host reservation to the database that the reservation
    /// for a given IP address/subnet does not exist. In some cases it may be
    /// required to allow non-unique IP reservations, e.g. in the case when a
    /// host has several interfaces and independently of which interface is used
    /// by this host to communicate with the DHCP server the same IP address
    /// should be assigned. In this case the @c unique value should be set to
    /// false to disable the checks for uniqueness on the backend side.
    ///
    /// @param unique boolean flag indicating if the IP reservations must be
    /// unique or can be non-unique.
    /// @return true if the new setting was accepted by the backend or false
    /// otherwise.
    virtual bool setIPReservationsUnique(const bool) {
        return (true);
    }

    /// @brief Cache a response from the memory backend.
    ///
    /// @param host host to cache.
    void cache(const ConstHostPtr& host) const {
        if (host) {
            hcptr_->cache(host);
        }
    }

    /// @brief Host Cache.
    TestHostCachePtr hcptr_;

    /// @brief Memory host data source.
    MemHostDataSourcePtr memptr_;
};

/// @brief TestHostDataSource pointer type
typedef boost::shared_ptr<TestHostDataSource> TestHostDataSourcePtr;

/// @brief Test fixture for testing cache features for the host-cache library
class CacheTest : public GenericHostDataSourceTest {
public:

    /// @brief Constructor
    CacheTest() {
        hdsptr_.reset(new TestHostDataSource());
    }

    /// @brief Destructor
    virtual ~CacheTest() = default;

    /// @brief Get Test host data source pointer
    TestHostDataSourcePtr testptr() const {
        TestHostDataSourcePtr testptr_ =
            boost::dynamic_pointer_cast<TestHostDataSource>(hdsptr_);
        if (!testptr_) {
            isc_throw(Unexpected, "Can't get testptr_???");
        }
        return (testptr_);
    }

    /// @brief Create 1000 hosts.
    HostCollection createHosts() {
        HostCollection hosts;
        IOAddress addr4("192.0.2.0");
        IOAddress addr6("2001:db8::");
        for (unsigned cnt = 0; cnt < 1000; ++cnt) {
            addr4 = IOAddress::increase(addr4);
            addr6 = IOAddress::increase(addr6);
            HostPtr host =
                HostDataSourceUtils::initializeHost4(addr4.toText(),
                                                     Host::IDENT_HWADDR);
            host->setIPv4SubnetID(4);
            host->setIPv6SubnetID(6);
            IPv6Resrv resv(IPv6Resrv::TYPE_NA, addr6, 128);
            host->addReservation(resv);
            hosts.push_back(host);
        }
        return (hosts);
    }

    /// @brief Get a random number between 0 and 999.
    size_t getRandom() {
        for (;;) {
            vector<uint8_t> v = cryptolink::random(2);
            if (v.size() != 2) {
                isc_throw(Unexpected, "cryptolink random failed");
            }
            uint16_t r = ((v[0] << 8) | v[1]) & 1023;
            // Uniform value
            if (r < 1000) {
                return (static_cast<size_t>(r));
            }
        }
        return (0);
    }

    /// @brief Test cache function.
    ///
    /// Tries a few time, last with hard failure.
    ///
    /// @param soft Soft or hard failure.
    /// @param[out] status Set to false when failed.
    /// @return true if succeed, false if not (and should be retried).
    void testCache(bool soft, bool& failed);
};

/// Host data source tests

// Test verifies if a host reservation can be added and later retrieved by IPv4
// address. Host uses hw address as identifier.
TEST_F(CacheTest, basic4HWAddr) {
    testBasic4(Host::IDENT_HWADDR);
}

// Test verifies if a host reservation can be added and later retrieved by IPv4
// address. Host uses client-id (DUID) as identifier.
TEST_F(CacheTest, basic4ClientId) {
    testBasic4(Host::IDENT_DUID);
}

// Test verifies that multiple hosts can be added and later retrieved by their
// reserved IPv4 address. This test uses HW addresses as identifiers.
TEST_F(CacheTest, getByIPv4HWaddr) {
    testGetByIPv4(Host::IDENT_HWADDR);
}

// Test verifies that multiple hosts can be added and later retrieved by their
// reserved IPv4 address. This test uses client-id (DUID) as identifiers.
TEST_F(CacheTest, getByIPv4ClientId) {
    testGetByIPv4(Host::IDENT_DUID);
}

// Test verifies if a host reservation can be added and later retrieved by
// hardware address.
TEST_F(CacheTest, get4ByHWaddr) {
    testGet4ByIdentifier(Host::IDENT_HWADDR);
}

// Test verifies if a host reservation can be added and later retrieved by
// DUID.
TEST_F(CacheTest, get4ByDUID) {
    testGet4ByIdentifier(Host::IDENT_DUID);
}

// Test verifies if a host reservation can be added and later retrieved by
// circuit id.
TEST_F(CacheTest, get4ByCircuitId) {
    testGet4ByIdentifier(Host::IDENT_CIRCUIT_ID);
}

// Test verifies if a host reservation can be added and later retrieved by
// client-id.
TEST_F(CacheTest, get4ByClientId) {
    testGet4ByIdentifier(Host::IDENT_CLIENT_ID);
}

// Test verifies if hardware address and client identifier are not confused.
TEST_F(CacheTest, hwaddrNotClientId1) {
    testHWAddrNotClientId();
}

// Test verifies if hardware address and client identifier are not confused.
TEST_F(CacheTest, hwaddrNotClientId2) {
    testClientIdNotHWAddr();
}

// Test verifies if a host with FQDN hostname can be stored and later retrieved.
TEST_F(CacheTest, hostnameFQDN) {
    testHostname("foo.example.org", 1);
}

// Test verifies if 100 hosts with unique FQDN hostnames can be stored and later
// retrieved.
TEST_F(CacheTest, hostnameFQDN100) {
    testHostname("foo.example.org", 100);
}

// Test verifies if a host without any hostname specified can be stored and
// later retrieved.
TEST_F(CacheTest, noHostname) {
    testHostname("", 1);
}

// Test verifies if a host with user context can be stored and later retrieved.
TEST_F(CacheTest, usercontext) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testUserContext(Element::fromJSON(comment));
}

// Test verifies that host with IPv6 prefix reservation can be retrieved
// by subnet id and prefix value.
TEST_F(CacheTest, get6SubnetPrefix) {
    testGetBySubnetIPv6();
}

// Test verifies if a host reservation can be added and later retrieved by
// hardware address.
TEST_F(CacheTest, get6ByHWaddr) {
    testGet6ByHWAddr();
}

// Test verifies if a host reservation can be added and later retrieved by
// client identifier.
TEST_F(CacheTest, get6ByClientId) {
    testGet6ByClientId();
}

// Test verifies if a host reservation can be stored with both IPv6 address and
// prefix.
TEST_F(CacheTest, addr6AndPrefix) {
    testAddr6AndPrefix();
}

// Check that delete(subnet-id, addr4) works.
TEST_F(CacheTest, deleteByAddr4) {
    testDeleteByAddr4();
}

// Check that delete(subnet4-id, identifier-type, identifier) works.
TEST_F(CacheTest, deleteById4) {
    testDeleteById4();
}

// Check that delete(subnet6-id, identifier-type, identifier) works.
TEST_F(CacheTest, deleteById6) {
    testDeleteById6();
}

/// Cache tests

// Check the cache works as a cache.

void
CacheTest::testCache(bool soft, bool& status) {
    hdsptr_.reset(new TestHostDataSource());
    ASSERT_TRUE(!!hdsptr_);

    HostCollection hosts = createHosts();
    for (auto const& host : hosts) {
        ASSERT_NO_THROW(hdsptr_->add(host));
    }
    EXPECT_EQ(0, testptr()->hcptr_->hits_);
    EXPECT_EQ(0, testptr()->hcptr_->inserts_);

    // First pass filling the cache.
    for (auto const& host : hosts) {
        ConstHostPtr entry = hdsptr_->get4(host->getIPv4SubnetID(),
                                           host->getIPv4Reservation());
        ASSERT_TRUE(entry);
        HostDataSourceUtils::compareHosts(entry, host);
    }
    EXPECT_EQ(0, testptr()->hcptr_->hits_);
    EXPECT_EQ(1000, testptr()->hcptr_->inserts_);

    // Second pass checking the cache.
    for (auto const& host : hosts) {
        ConstHostPtr entry = hdsptr_->get6(host->getIPv6SubnetID(),
                                           host->getIdentifierType(),
                                           &host->getIdentifier()[0],
                                           host->getIdentifier().size());
        ASSERT_TRUE(entry);
        HostDataSourceUtils::compareHosts(entry, host);
    }
    EXPECT_EQ(1000, testptr()->hcptr_->size());
    EXPECT_EQ(1000, testptr()->hcptr_->hits_);
    EXPECT_EQ(1000, testptr()->hcptr_->inserts_);

    // Try a 100 entry cache.
    testptr()->hcptr_->flush(testptr()->hcptr_->size() - 100);
    ASSERT_EQ(100, testptr()->hcptr_->size());
    testptr()->hcptr_->setMaximum(100);
    size_t hits100 = testptr()->hcptr_->hits_;
    size_t inserts100 = testptr()->hcptr_->inserts_;
    // Go for 100 rounds.
    for (unsigned cnt = 0; cnt < 100; ++cnt) {
        ConstHostPtr host = hosts[getRandom()];
        ConstHostPtr entry = hdsptr_->get6(host->getIPv6SubnetID(),
                                           host->getIdentifierType(),
                                           &host->getIdentifier()[0],
                                           host->getIdentifier().size());
        ASSERT_TRUE(entry);
    }
    size_t hits_delta = testptr()->hcptr_->hits_ - hits100;
    size_t inserts_delta = testptr()->hcptr_->inserts_ - inserts100;
    // 100 from and to cache.
    EXPECT_EQ(100, hits_delta + inserts_delta);
    cerr << "100 rounds with cache 100: " << hits_delta << endl;
    // Prob(hits_delta < 2) ~= 3.10^-4
    if (soft) {
        if (hits_delta < 2) {
            cerr << "failed: will retry" << endl;
            status = false;
        }
    } else {
        EXPECT_LT(2, hits_delta);
    }
    // Prob(hits_delta >= 22) ~= 3.10^-4
    if (soft) {
        if (hits_delta >= 22) {
            cerr << "failed: will retry" << endl;
            status = false;
        }
    } else {
        EXPECT_GE(22, hits_delta);
    }

    // Try a 10 entry cache.
    testptr()->hcptr_->flush(testptr()->hcptr_->size() - 10);
    testptr()->hcptr_->setMaximum(10);
    ASSERT_EQ(10, testptr()->hcptr_->size());
    size_t hits10 = testptr()->hcptr_->hits_;
    size_t inserts10 = testptr()->hcptr_->inserts_;
    // Go for 1000 rounds.
    for (unsigned cnt = 0; cnt < 1000; ++cnt) {
        ConstHostPtr host = hosts[getRandom()];
        ConstHostPtr entry = hdsptr_->get4(host->getIPv4SubnetID(),
                                           host->getIPv4Reservation());
        ASSERT_TRUE(entry);
    }
    hits_delta = testptr()->hcptr_->hits_ - hits10;
    inserts_delta = testptr()->hcptr_->inserts_ - inserts10;
    EXPECT_EQ(1000, hits_delta + inserts_delta);
    cerr << "1000 rounds with cache 10: " << hits_delta << endl;
    // Prob(hits_delta < 2) ~= 5.10-4
    if (soft) {
        if (hits_delta < 2) {
            cerr << "failed: will retry" << endl;
            status = false;
        }
    } else {
        EXPECT_LT(2, hits_delta);
    }
    // Prob(hits_delta > 22) ~= 3.10-4
    if (soft) {
        if (hits_delta > 22) {
            cerr << "failed: will retry" << endl;
            status = false;
        }
    } else {
        EXPECT_GT(22, hits_delta);
    }

    // Try a 5 entry cache.
    testptr()->hcptr_->flush(testptr()->hcptr_->size() - 5);
    testptr()->hcptr_->setMaximum(5);
    ASSERT_EQ(5, testptr()->hcptr_->size());
    size_t hits5 = testptr()->hcptr_->hits_;
    size_t inserts5 = testptr()->hcptr_->inserts_;
    // Go for 1000 rounds.
    for (unsigned cnt = 0; cnt < 1000; ++cnt) {
        ConstHostPtr host = hosts[getRandom()];
        ConstHostPtr entry = hdsptr_->get6(host->getIPv6SubnetID(),
                                           host->getIdentifierType(),
                                           &host->getIdentifier()[0],
                                           host->getIdentifier().size());
        ASSERT_TRUE(entry);
    }
    hits_delta = testptr()->hcptr_->hits_ - hits5;
    inserts_delta = testptr()->hcptr_->inserts_ - inserts5;
    EXPECT_EQ(1000, hits_delta + inserts_delta);
    cerr << "1000 rounds with cache 5: " << hits_delta << endl;
    // Prob(hits_delta >= 15) ~= 2.10-4
    if (soft) {
        if (hits_delta >= 15) {
            cerr << "failed: will retry" << endl;
            status = false;
        }
    } else {
        EXPECT_GE(15, hits_delta);
    }

    // Try a 2 entry cache.
    testptr()->hcptr_->flush(testptr()->hcptr_->size() - 2);
    testptr()->hcptr_->setMaximum(2);
    ASSERT_EQ(2, testptr()->hcptr_->size());
    size_t hits2 = testptr()->hcptr_->hits_;
    size_t inserts2 = testptr()->hcptr_->inserts_;
    // Go for 1000 rounds.
    for (unsigned cnt = 0; cnt < 1000; ++cnt) {
        ConstHostPtr host = hosts[getRandom()];
        ConstHostPtr entry = hdsptr_->get4(host->getIPv4SubnetID(),
                                           host->getIPv4Reservation());
        ASSERT_TRUE(entry);
    }
    hits_delta = testptr()->hcptr_->hits_ - hits2;
    inserts_delta = testptr()->hcptr_->inserts_ - inserts2;
    EXPECT_EQ(1000, hits_delta + inserts_delta);
    cerr << "1000 rounds with cache 2: " << hits_delta << endl;
    // Prob(hits_delta >= 9) ~= 2.10^-4
    if (soft) {
        if (hits_delta >= 9) {
            cerr << "failed: will retry" << endl;
            status = false;
        }
    } else {
        EXPECT_GE(9, hits_delta);
    }

    // And finish with an 1 entry cache.
    testptr()->hcptr_->flush(0);
    ASSERT_EQ(0, testptr()->hcptr_->size());
    testptr()->hcptr_->setMaximum(1);
    size_t hits1 = testptr()->hcptr_->hits_;
    size_t inserts1 = testptr()->hcptr_->inserts_;
    // Go for 8000 rounds.
    for (unsigned cnt = 0; cnt < 8000; ++cnt) {
        ConstHostPtr host = hosts[getRandom()];
        ConstHostPtr entry = hdsptr_->get4(host->getIPv4SubnetID(),
                                           host->getIPv4Reservation());
        ASSERT_TRUE(entry);
    }
    hits_delta = testptr()->hcptr_->hits_ - hits1;
    inserts_delta = testptr()->hcptr_->inserts_ - inserts1;
    EXPECT_EQ(8000, hits_delta + inserts_delta);
    cerr << "8000 rounds with cache 1: " << hits_delta << endl;
    // Prob(hits_delta == 0) ~= 5.10-4
    if (soft) {
        if (hits_delta == 0) {
            cerr << "failed: will retry" << endl;
            status = false;
        }
    } else {
        EXPECT_NE(0, hits_delta);
    }
}

TEST_F(CacheTest, cacheAll) {
    bool status = true;
    testCache(true, status);
    if (!status) {
        // Soft failure: retry with hard failure.
        testCache(false, status);
    }
}

/// Verifies remove behavior on copy.
TEST_F(CacheTest, remove) {
    hdsptr_.reset(new TestHostDataSource());
    ASSERT_TRUE(!!hdsptr_);

    HostCollection hosts = createHosts();
    for (auto const& host : hosts) {
        ASSERT_NO_THROW(hdsptr_->add(host));
    }

    // Fill the cache.
    for (auto const& host : hosts) {
        ConstHostPtr entry = hdsptr_->get4(host->getIPv4SubnetID(),
                                           host->getIPv4Reservation());
        ASSERT_TRUE(entry);
    }

    HostPtr copy(new Host(*hosts[0]));
    ASSERT_NO_THROW(testptr());
    ASSERT_TRUE(testptr()->hcptr_);
    // Remove does not work on a copy.
    EXPECT_FALSE(testptr()->hcptr_->remove(copy));
    // Remove does not work on the original value because a copy was stored.
    EXPECT_FALSE(testptr()->hcptr_->remove(hosts[0]));
    // Remove works on the value from cache.
    // Remove can't get a ConstHostPtr because the container uses HostPtr.
    ConstHostPtr entry = hdsptr_->get4(hosts[0]->getIPv4SubnetID(),
                                       hosts[0]->getIPv4Reservation());
    HostPtr entry_mutable = boost::const_pointer_cast<Host>(entry);
    EXPECT_TRUE(testptr()->hcptr_->remove(entry_mutable));
}

} // end of anonymous namespace
