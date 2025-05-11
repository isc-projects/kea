// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the Host Cache
/// considered as a backend.

#include <config.h>

#include <asiolink/addr_utilities.h>
#include <host_cache.h>
#include <host_cache_impl.h>
#include <database/db_exceptions.h>
#include <dhcpsrv/testutils/host_data_source_utils.h>
#include <dhcpsrv/testutils/generic_host_data_source_unittest.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::host_cache;
using namespace isc::test;
using namespace isc::util;
using namespace std;

namespace {

/// @brief Test version of the Host Cache class.
class TestHostCache : public HostCache {
public:

    /// @brief Constructor
    ///
    /// Change defaults.
    TestHostCache() : HostCache() {
    }

    /// @brief Destructor
    virtual ~TestHostCache() { }

    /// Redefine some method here.

    /// @brief Attempts to delete a host by (subnet-id, address)
    ///
    /// This method supports both v4 and v6.
    ///
    /// @param subnet_id subnet identifier.
    /// @param addr specified address.
    /// @return true if deletion was successful, false if the host was not there.
    virtual bool del(const SubnetID& subnet_id, const IOAddress& addr) {
        if (addr.isV4()) {
            string txt = impl_->del4(subnet_id, addr);
            return (!txt.empty());
        } else if (addr.isV6()) {
            string txt = impl_->del6(subnet_id, addr);
            return (!txt.empty());
        }
        return (false);
    }

    /// @brief Attempts to delete a host by (subnet-id4, identifier, identifier-type)
    ///
    /// This method supports both v4 hosts only.
    ///
    /// @param subnet_id IPv4 Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @return true if deletion was successful, false if the host was not there.
    virtual bool del4(const SubnetID& subnet_id,
                      const Host::IdentifierType& identifier_type,
                      const uint8_t* identifier_begin,
                      const size_t identifier_len) {
        string txt = impl_->del4(subnet_id, identifier_type,
                                 identifier_begin, identifier_len);
        return (!txt.empty());
    }

    /// @brief Attempts to delete a host by (subnet-id6, identifier, identifier-type)
    ///
    /// This method supports both v6 hosts only.
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
        string txt = impl_->del6(subnet_id, identifier_type,
                                 identifier_begin, identifier_len);
        return (!txt.empty());
    }

    /// @brief Return backend type
    virtual std::string getType() const {
        return ("test-cache");
    }
};

/// @brief TestHostCache pointer type
typedef boost::shared_ptr<TestHostCache> TestHostCachePtr;

/// @brief Test fixture for testing host source data backend features
/// for the host-cache library
class HostDataSourceTest : public GenericHostDataSourceTest {
public:

    /// @brief Constructor
    HostDataSourceTest() {
        hdsptr_.reset(new TestHostCache());
        hdsptr_->setIPReservationsUnique(true);
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Destructor
    virtual ~HostDataSourceTest() {
        hdsptr_.reset();
    }

    /// @brief Get Test Host Cache pointer
    TestHostCachePtr hcptr() const {
        TestHostCachePtr hcptr_ =
            boost::dynamic_pointer_cast<TestHostCache>(hdsptr_);
        if (!hcptr_) {
            isc_throw(Unexpected, "Can't get hcptr_???");
        }
        return (hcptr_);
    }

    /// @brief Test inserts multiple reservations for the same host for different
    /// subnets and check that they can be retrieved properly.
    ///
    /// @param subnets number of subnets to test
    /// @param id Host identifier type.
    void hcMultipleSubnets(int subnets, const Host::IdentifierType& id);

    /// @brief Test if host reservations made for different IPv6 subnets
    ///        are handled correctly.
    ///
    /// @param subnets number of subnets to test
    /// @param id identifier type (IDENT_HWADDR or IDENT_DUID)
    void hcSubnetId6(int subnets, Host::IdentifierType id);

    /// @brief Test that DHCPv4 options can be inserted and retrieved from
    /// the database.
    ///
    /// @param formatted Boolean value indicating if the option values
    /// should be stored in the textual format in the database.
    /// @param user_context Optional user context.
    void hcOptionsReservations4(const bool formatted,
                                isc::data::ConstElementPtr user_context =
                                isc::data::ConstElementPtr());

    /// @brief Test that multiple client classes for IPv4 can be inserted and
    /// retrieved for a given host reservation.
    void hcMultipleClientClasses4();

    /// @brief Test that multiple client classes for IPv6 can be inserted and
    /// retrieved for a given host reservation.
    void hcMultipleClientClasses6();

    /// @brief Test that siaddr, sname, file fields can be retrieved
    /// from a database for a host.
    void hcMessageFields4();
};

/// Redefined tests

void
HostDataSourceTest::hcMultipleSubnets(int subnets,
                                      const Host::IdentifierType& id) {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.1", id);
    host->setIPv6SubnetID(SUBNET_ID_UNUSED);

    for (int i = 0; i < subnets; ++i) {
        host->setIPv4SubnetID(i);

        // Check that the same host can have reservations in multiple subnets.
        EXPECT_NO_THROW(hdsptr_->add(host));
    }

    // Now check that the reservations can be retrieved by IPv4 address from
    // each subnet separately.
    for (int i = 0; i < subnets; ++i) {
        // Try to retrieve the host by IPv4 address.
        ConstHostPtr from_hds =
            hdsptr_->get4(i, host->getIPv4Reservation());

        ASSERT_TRUE(from_hds);
        EXPECT_EQ(i, from_hds->getIPv4SubnetID());

        // Try to retrieve the host by either HW address of client-id
        from_hds = hdsptr_->get4(i, id, &host->getIdentifier()[0],
                                 host->getIdentifier().size());
        ASSERT_TRUE(from_hds);
        EXPECT_EQ(i, from_hds->getIPv4SubnetID());
    }

    /// Removed part
}

void
HostDataSourceTest::hcSubnetId6(int subnets, Host::IdentifierType id) {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    HostPtr host;
    IOAddress current_address("2001:db8::");
    ASSERT_LT(subnets, std::numeric_limits<uint16_t>::max()) << "Too many subnets. Broken test?";
    for (int i = 0; i < subnets; ++i) {
        // Last boolean value set to false indicates that the same identifier
        // must be used for each generated host.
        host = HostDataSourceUtils::initializeHost6(current_address.toText(),
                                                    id, true, false);

        host->setIPv4SubnetID(i);
        host->setIPv6SubnetID(i);

        // Check that the same host can have reservations in multiple subnets.
        EXPECT_NO_THROW(hdsptr_->add(host));

        // Increase address to make sure we don't assign the same address
        // in different subnets.
        current_address = offsetAddress(current_address, (uint128_t(1) << 80));
    }

    // Check that the reservations can be retrieved from each subnet separately.
    for (int i = 0; i < subnets; ++i) {
        // Try to retrieve the host
        ConstHostPtr from_hds = hdsptr_->get6(i, id, &host->getIdentifier()[0],
                                              host->getIdentifier().size());

        ASSERT_TRUE(from_hds) << "failed for i=" << i;
        EXPECT_EQ(i, from_hds->getIPv6SubnetID());
    }

    /// Removed part
}

void
HostDataSourceTest::hcOptionsReservations4(const bool formatted,
                                           ConstElementPtr user_context) {
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.5", Host::IDENT_HWADDR);
    // Add a bunch of DHCPv4 and DHCPv6 options for the host.
    ASSERT_NO_THROW(addTestOptions(host, formatted, DHCP4_ONLY, user_context));
    // Insert host and the options into respective tables.
    ASSERT_NO_THROW(hdsptr_->add(host));
    // Subnet id will be used in queries to the database.
    SubnetID subnet_id = host->getIPv4SubnetID();

    /// Removed part

    // get4(subnet_id, identifier_type, identifier, identifier_size)
    ConstHostPtr host_by_id =
        hdsptr_->get4(subnet_id, host->getIdentifierType(),
                      &host->getIdentifier()[0], host->getIdentifier().size());
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, host_by_id));

    // get4(subnet_id, address)
    ConstHostPtr host_by_addr =
        hdsptr_->get4(subnet_id, IOAddress("192.0.2.5"));
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, host_by_addr));
}

void
HostDataSourceTest::hcMultipleClientClasses4() {
    ASSERT_TRUE(hdsptr_);

    // Create the Host object.
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.5", Host::IDENT_HWADDR);

    // Add v4 classes to the host.
    for (int i = 0; i < 4; ++i) {
        std::ostringstream os;
        os << "class4_" << i;
        host->addClientClass4(os.str());
    }

    // Add the host.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Subnet id will be used in queries to the database.
    SubnetID subnet_id = host->getIPv4SubnetID();

    /// Removed part.

    // Fetch the host via
    // get4(const SubnetID& subnet_id, const Host::IdentifierType&
    // identifier_type,
    //     const uint8_t* identifier_begin, const size_t identifier_len) const;
    ConstHostPtr from_hds =
        hdsptr_->get4(subnet_id, host->getIdentifierType(),
                      &host->getIdentifier()[0], host->getIdentifier().size());
    ASSERT_TRUE(from_hds);
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, from_hds));

    // Fetch the host via:
    // get4(const SubnetID& subnet_id, const asiolink::IOAddress& address) const;
    from_hds = hdsptr_->get4(subnet_id, IOAddress("192.0.2.5"));
    ASSERT_TRUE(from_hds);
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, from_hds));
}

void
HostDataSourceTest::hcMultipleClientClasses6() {
    ASSERT_TRUE(hdsptr_);

    // Create the Host object.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8::1", Host::IDENT_HWADDR, false);

    // Add v6 classes to the host.
    for (int i = 0; i < 4; ++i) {
        std::ostringstream os;
        os << "class6_" << i;
        host->addClientClass6(os.str());
    }

    // Add the host.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Subnet id will be used in queries to the database.
    SubnetID subnet_id = host->getIPv6SubnetID();

    /// Removed part

    // Fetch the host via:
    // get6(const SubnetID& subnet_id, const Host::IdentifierType&
    // identifier_type,
    //     const uint8_t* identifier_begin, const size_t identifier_len) const;
    ConstHostPtr from_hds =
        hdsptr_->get6(subnet_id, Host::IDENT_HWADDR, &host->getIdentifier()[0],
                      host->getIdentifier().size());
    ASSERT_TRUE(from_hds);
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, from_hds));

    // Fetch the host via:
    // get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len) const;
    from_hds = hdsptr_->get6(IOAddress("2001:db8::1"), 128);
    ASSERT_TRUE(from_hds);
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, from_hds));
}

void
HostDataSourceTest::hcMessageFields4() {
    ASSERT_TRUE(hdsptr_);

    // Create the Host object.
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.5", Host::IDENT_HWADDR);
    // And assign values for DHCPv4 message fields.
    ASSERT_NO_THROW({
        host->setNextServer(IOAddress("10.1.1.1"));
        host->setServerHostname("server-name.example.org");
        host->setBootFileName("bootfile.efi");
    });

    // Add the host.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Subnet id will be used in queries to the database.
    SubnetID subnet_id = host->getIPv4SubnetID();

    /// Removed part

    // Fetch the host via
    // get4(const SubnetID& subnet_id, const Host::IdentifierType&
    // identifier_type,
    //     const uint8_t* identifier_begin, const size_t identifier_len) const;
    ConstHostPtr from_hds =
        hdsptr_->get4(subnet_id, host->getIdentifierType(),
                      &host->getIdentifier()[0], host->getIdentifier().size());
    ASSERT_TRUE(from_hds);
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, from_hds));

    // Fetch the host via:
    // get4(const SubnetID& subnet_id, const asiolink::IOAddress& address) const;
    from_hds = hdsptr_->get4(subnet_id, IOAddress("192.0.2.5"));
    ASSERT_TRUE(from_hds);
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, from_hds));
}

/// Tests from pgsql_host_data_source_unittest.cc

// Test verifies if a host reservation can be added and later retrieved by IPv4
// address. Host uses hw address as identifier.
TEST_F(HostDataSourceTest, basic4HWAddr) {
    testBasic4(Host::IDENT_HWADDR);
}

TEST_F(HostDataSourceTest, basic4HWAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testBasic4(Host::IDENT_HWADDR);
}

// Test verifies if a host reservation can be added and later retrieved by IPv4
// address. Host uses client-id (DUID) as identifier.
TEST_F(HostDataSourceTest, basic4ClientId) {
    testBasic4(Host::IDENT_DUID);
}

TEST_F(HostDataSourceTest, basic4ClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testBasic4(Host::IDENT_DUID);
}

// Test verifies that multiple hosts can be added and later retrieved by their
// reserved IPv4 address. This test uses HW addresses as identifiers.
TEST_F(HostDataSourceTest, getByIPv4HWaddr) {
    testGetByIPv4(Host::IDENT_HWADDR);
}

TEST_F(HostDataSourceTest, getByIPv4HWaddrMultiThreading) {
    MultiThreadingTest mt(true);
    testGetByIPv4(Host::IDENT_HWADDR);
}

// Test verifies that multiple hosts can be added and later retrieved by their
// reserved IPv4 address. This test uses client-id (DUID) as identifiers.
TEST_F(HostDataSourceTest, getByIPv4ClientId) {
    testGetByIPv4(Host::IDENT_DUID);
}

TEST_F(HostDataSourceTest, getByIPv4ClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGetByIPv4(Host::IDENT_DUID);
}

// Test verifies if a host reservation can be added and later retrieved by
// hardware address.
TEST_F(HostDataSourceTest, get4ByHWaddr) {
    testGet4ByIdentifier(Host::IDENT_HWADDR);
}

TEST_F(HostDataSourceTest, get4ByHWaddrMultiThreading) {
    MultiThreadingTest mt(true);
    testGet4ByIdentifier(Host::IDENT_HWADDR);
}

// Test verifies if a host reservation can be added and later retrieved by
// DUID.
TEST_F(HostDataSourceTest, get4ByDUID) {
    testGet4ByIdentifier(Host::IDENT_DUID);
}

TEST_F(HostDataSourceTest, get4ByDUIDMultiThreading) {
    MultiThreadingTest mt(true);
    testGet4ByIdentifier(Host::IDENT_DUID);
}

// Test verifies if a host reservation can be added and later retrieved by
// circuit id.
TEST_F(HostDataSourceTest, get4ByCircuitId) {
    testGet4ByIdentifier(Host::IDENT_CIRCUIT_ID);
}

TEST_F(HostDataSourceTest, get4ByCircuitIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGet4ByIdentifier(Host::IDENT_CIRCUIT_ID);
}

// Test verifies if a host reservation can be added and later retrieved by
// client-id.
TEST_F(HostDataSourceTest, get4ByClientId) {
    testGet4ByIdentifier(Host::IDENT_CLIENT_ID);
}

TEST_F(HostDataSourceTest, get4ByClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGet4ByIdentifier(Host::IDENT_CLIENT_ID);
}

// Test verifies if hardware address and client identifier are not confused.
TEST_F(HostDataSourceTest, hwaddrNotClientId1) {
    testHWAddrNotClientId();
}

TEST_F(HostDataSourceTest, hwaddrNotClientId1MultiThreading) {
    MultiThreadingTest mt(true);
    testHWAddrNotClientId();
}

// Test verifies if hardware address and client identifier are not confused.
TEST_F(HostDataSourceTest, hwaddrNotClientId2) {
    testClientIdNotHWAddr();
}

TEST_F(HostDataSourceTest, hwaddrNotClientId2MultiThreading) {
    MultiThreadingTest mt(true);
    testClientIdNotHWAddr();
}

// Test verifies if a host with FQDN hostname can be stored and later retrieved.
TEST_F(HostDataSourceTest, hostnameFQDN) {
    testHostname("foo.example.org", 1);
}

TEST_F(HostDataSourceTest, hostnameFQDNMultiThreading) {
    MultiThreadingTest mt(true);
    testHostname("foo.example.org", 1);
}

// Test verifies if 100 hosts with unique FQDN hostnames can be stored and later
// retrieved.
TEST_F(HostDataSourceTest, hostnameFQDN100) {
    testHostname("foo.example.org", 100);
}

TEST_F(HostDataSourceTest, hostnameFQDN100MultiThreading) {
    MultiThreadingTest mt(true);
    testHostname("foo.example.org", 100);
}

// Test verifies if a host without any hostname specified can be stored and
// later retrieved.
TEST_F(HostDataSourceTest, noHostname) {
    testHostname("", 1);
}

TEST_F(HostDataSourceTest, noHostnameMultiThreading) {
    MultiThreadingTest mt(true);
    testHostname("", 1);
}

// Test verifies if a host with user context can be stored and later retrieved.
TEST_F(HostDataSourceTest, usercontext) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testUserContext(Element::fromJSON(comment));
}

TEST_F(HostDataSourceTest, usercontextMultiThreading) {
    MultiThreadingTest mt(true);
    string comment = "{ \"comment\": \"a host reservation\" }";
    testUserContext(Element::fromJSON(comment));
}

// Test verifies that host with IPv6 address and DUID can be added and
// later retrieved by IPv6 address.
TEST_F(HostDataSourceTest, get6AddrWithDuid) {
    testGetByIPv6(Host::IDENT_DUID, false);
}

TEST_F(HostDataSourceTest, get6AddrWithDuidMultiThreading) {
    MultiThreadingTest mt(true);
    testGetByIPv6(Host::IDENT_DUID, false);
}

// Test verifies that host with IPv6 address and HWAddr can be added and
// later retrieved by IPv6 address.
TEST_F(HostDataSourceTest, get6AddrWithHWAddr) {
    testGetByIPv6(Host::IDENT_HWADDR, false);
}

TEST_F(HostDataSourceTest, get6AddrWithHWAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testGetByIPv6(Host::IDENT_HWADDR, false);
}

// Test verifies that host with IPv6 prefix and DUID can be added and
// later retrieved by IPv6 prefix.
TEST_F(HostDataSourceTest, get6PrefixWithDuid) {
    testGetByIPv6(Host::IDENT_DUID, true);
}

TEST_F(HostDataSourceTest, get6PrefixWithDuidMultiThreading) {
    MultiThreadingTest mt(true);
    testGetByIPv6(Host::IDENT_DUID, true);
}

// Test verifies that host with IPv6 prefix and HWAddr can be added and
// later retrieved by IPv6 prefix.
TEST_F(HostDataSourceTest, get6PrefixWithHWaddr) {
    testGetByIPv6(Host::IDENT_HWADDR, true);
}

TEST_F(HostDataSourceTest, get6PrefixWithHWaddrMultiThreading) {
    MultiThreadingTest mt(true);
    testGetByIPv6(Host::IDENT_HWADDR, true);
}

// Test verifies that host with IPv6 prefix reservation can be retrieved
// by subnet id and prefix value.
TEST_F(HostDataSourceTest, get6SubnetPrefix) {
    testGetBySubnetIPv6();
}

TEST_F(HostDataSourceTest, get6SubnetPrefixMultiThreading) {
    MultiThreadingTest mt(true);
    testGetBySubnetIPv6();
}

// Test verifies if a host reservation can be added and later retrieved by
// hardware address.
TEST_F(HostDataSourceTest, get6ByHWaddr) {
    testGet6ByHWAddr();
}

TEST_F(HostDataSourceTest, get6ByHWaddrMultiThreading) {
    MultiThreadingTest mt(true);
    testGet6ByHWAddr();
}

// Test verifies if a host reservation can be added and later retrieved by
// client identifier.
TEST_F(HostDataSourceTest, get6ByClientId) {
    testGet6ByClientId();
}

TEST_F(HostDataSourceTest, get6ByClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    testGet6ByClientId();
}

// Test verifies if a host reservation can be stored with both IPv6 address and
// prefix.
TEST_F(HostDataSourceTest, addr6AndPrefix) {
    testAddr6AndPrefix();
}

TEST_F(HostDataSourceTest, addr6AndPrefixMultiThreading) {
    MultiThreadingTest mt(true);
    testAddr6AndPrefix();
}

// Tests if host with multiple IPv6 reservations can be added and then
// retrieved correctly. Test checks reservations comparing.
TEST_F(HostDataSourceTest, multipleReservations){
    testMultipleReservations();
}

TEST_F(HostDataSourceTest, multipleReservationsMultiThreading){
    MultiThreadingTest mt(true);
    testMultipleReservations();
}

// Tests if compareIPv6Reservations() method treats same pool of reservations
// but added in different order as equal.
TEST_F(HostDataSourceTest, multipleReservationsDifferentOrder){
    testMultipleReservationsDifferentOrder();
}

TEST_F(HostDataSourceTest, multipleReservationsDifferentOrderMultiThreading){
    MultiThreadingTest mt(true);
    testMultipleReservationsDifferentOrder();
}

// Test that multiple client classes for IPv4 can be inserted and
// retrieved for a given host reservation.
TEST_F(HostDataSourceTest, multipleClientClasses4) {
    hcMultipleClientClasses4();
}

TEST_F(HostDataSourceTest, multipleClientClasses4MultiThreading) {
    MultiThreadingTest mt(true);
    hcMultipleClientClasses4();
}

// Test that multiple client classes for IPv6 can be inserted and
// retrieved for a given host reservation.
TEST_F(HostDataSourceTest, multipleClientClasses6) {
    hcMultipleClientClasses6();
}

TEST_F(HostDataSourceTest, multipleClientClasses6MultiThreading) {
    MultiThreadingTest mt(true);
    hcMultipleClientClasses6();
}

// Test that multiple client classes for both IPv4 and IPv6 can
// be inserted and retrieved for a given host reservation.
TEST_F(HostDataSourceTest, multipleClientClassesBoth) {
    testMultipleClientClassesBoth();
}

TEST_F(HostDataSourceTest, multipleClientClassesBothMultiThreading) {
    MultiThreadingTest mt(true);
    testMultipleClientClassesBoth();
}

// Test if the same host can have reservations in different subnets (with the
// same hardware address). The test logic is as follows:
// Insert 10 host reservations for a given physical host (the same
// hardware address), but for different subnets (different subnet-ids).
// Make sure that getAll() returns them all correctly.
TEST_F(HostDataSourceTest, multipleSubnetsHWAddr) {
    hcMultipleSubnets(10, Host::IDENT_HWADDR);
}

TEST_F(HostDataSourceTest, multipleSubnetsHWAddrMultiThreading) {
    MultiThreadingTest mt(true);
    hcMultipleSubnets(10, Host::IDENT_HWADDR);
}

// Test if the same host can have reservations in different subnets (with the
// same client identifier). The test logic is as follows:
//
// Insert 10 host reservations for a given physical host (the same
// client-identifier), but for different subnets (different subnet-ids).
// Make sure that getAll() returns them correctly.
TEST_F(HostDataSourceTest, multipleSubnetsClientId) {
    hcMultipleSubnets(10, Host::IDENT_DUID);
}

TEST_F(HostDataSourceTest, multipleSubnetsClientIdMultiThreading) {
    MultiThreadingTest mt(true);
    hcMultipleSubnets(10, Host::IDENT_DUID);
}

// Test if host reservations made for different IPv6 subnets are handled correctly.
// The test logic is as follows:
//
// Insert 10 host reservations for different subnets. Make sure that
// get6(subnet-id, ...) calls return correct reservation.
TEST_F(HostDataSourceTest, subnetId6) {
    hcSubnetId6(10, Host::IDENT_HWADDR);
}

TEST_F(HostDataSourceTest, subnetId6MultiThreading) {
    MultiThreadingTest mt(true);
    hcSubnetId6(10, Host::IDENT_HWADDR);
}

// Test if the duplicate host instances can't be inserted. The test logic is as
// follows: try to add multiple instances of the same host reservation and
// verify that the second and following attempts will throw exceptions.
// Hosts with same DUID.
TEST_F(HostDataSourceTest, addDuplicate6WithDUID) {
    testAddDuplicate6WithSameDUID();
}

TEST_F(HostDataSourceTest, addDuplicate6WithDUIDMultiThreading) {
    MultiThreadingTest mt(true);
    testAddDuplicate6WithSameDUID();
}

// Test if the duplicate host instances can't be inserted. The test logic is as
// follows: try to add multiple instances of the same host reservation and
// verify that the second and following attempts will throw exceptions.
// Hosts with same HWAddr.
TEST_F(HostDataSourceTest, addDuplicate6WithHWAddr) {
    testAddDuplicate6WithSameHWAddr();
}

TEST_F(HostDataSourceTest, addDuplicate6WithHWAddrMultiThreading) {
    MultiThreadingTest mt(true);
    testAddDuplicate6WithSameHWAddr();
}

// Test if the duplicate IPv4 host instances can't be inserted. The test logic is as
// follows: try to add multiple instances of the same host reservation and
// verify that the second and following attempts will throw exceptions.
TEST_F(HostDataSourceTest, addDuplicateIPv4) {
    testAddDuplicateIPv4();
}

TEST_F(HostDataSourceTest, addDuplicateIPv4MultiThreading) {
    MultiThreadingTest mt(true);
    testAddDuplicateIPv4();
}

// This test verifies that DHCPv4 options can be inserted in a binary format
/// and retrieved from the host cache store.
TEST_F(HostDataSourceTest, optionsReservations4) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    hcOptionsReservations4(false, Element::fromJSON(comment));
}

TEST_F(HostDataSourceTest, optionsReservations4MultiThreading) {
    MultiThreadingTest mt(true);
    string comment = "{ \"comment\": \"a host reservation\" }";
    hcOptionsReservations4(false, Element::fromJSON(comment));
}

// This test verifies that DHCPv6 options can be inserted in a binary format
/// and retrieved from the host cache store.
TEST_F(HostDataSourceTest, optionsReservations6) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations6(false, Element::fromJSON(comment));
}

TEST_F(HostDataSourceTest, optionsReservations6MultiThreading) {
    MultiThreadingTest mt(true);
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations6(false, Element::fromJSON(comment));
}

// This test verifies that DHCPv6 options can be inserted in a textual format
/// and retrieved from the host cache store.
TEST_F(HostDataSourceTest, formattedOptionsReservations6) {
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations6(true, Element::fromJSON(comment));
}

TEST_F(HostDataSourceTest, formattedOptionsReservations6MultiThreading) {
    MultiThreadingTest mt(true);
    string comment = "{ \"comment\": \"a host reservation\" }";
    testOptionsReservations6(true, Element::fromJSON(comment));
}

// This test checks that siaddr, sname, file fields can be retrieved
/// from a database for a host.
TEST_F(HostDataSourceTest, messageFields) {
    hcMessageFields4();
}

TEST_F(HostDataSourceTest, messageFieldsMultiThreading) {
    MultiThreadingTest mt(true);
    hcMessageFields4();
}

// Check that delete(subnet-id, addr4) works.
TEST_F(HostDataSourceTest, deleteByAddr4) {
    testDeleteByAddr4();
}

TEST_F(HostDataSourceTest, deleteByAddr4MultiThreading) {
    MultiThreadingTest mt(true);
    testDeleteByAddr4();
}

// Check that delete(subnet4-id, identifier-type, identifier) works.
TEST_F(HostDataSourceTest, deleteById4) {
    testDeleteById4();
}

TEST_F(HostDataSourceTest, deleteById4MultiThreading) {
    MultiThreadingTest mt(true);
    testDeleteById4();
}

// Check that delete(subnet6-id, identifier-type, identifier) works.
TEST_F(HostDataSourceTest, deleteById6) {
    testDeleteById6();
}

TEST_F(HostDataSourceTest, deleteById6MultiThreading) {
    MultiThreadingTest mt(true);
    testDeleteById6();
}

// Tests that multiple reservations without IPv4 addresses can be
// specified within a subnet.
TEST_F(HostDataSourceTest, testMultipleHostsNoAddress4) {
    testMultipleHostsNoAddress4();
}

TEST_F(HostDataSourceTest, testMultipleHostsNoAddress4MultiThreading) {
    MultiThreadingTest mt(true);
    testMultipleHostsNoAddress4();
}

// Tests that multiple hosts can be specified within an IPv6 subnet.
TEST_F(HostDataSourceTest, testMultipleHosts6) {
    testMultipleHosts6();
}

TEST_F(HostDataSourceTest, testMultipleHosts6MultiThreading) {
    MultiThreadingTest mt(true);
    testMultipleHosts6();
}

/// Verify that the host_cache backend does not support using non-unique
/// IP addresses between multiple reservations.
TEST_F(HostDataSourceTest, disallowDuplicateIP) {
    // The backend does not support switching to the mode in which multiple
    // reservations for the same address can be created.
    EXPECT_FALSE(hdsptr_->setIPReservationsUnique(false));

    // The default mode still can be used.
    EXPECT_TRUE(hdsptr_->setIPReservationsUnique(true));
}

// Verify that an attempt to get all hosts for a given IPv4 address and subnet
// returns empty set.
TEST_F(HostDataSourceTest, getAll4BySubnetAddress) {
    EXPECT_TRUE(hdsptr_->getAll4(SubnetID(1), IOAddress("192.0.2.0")).empty());
}

// Verify that an attempt to get all hosts for a given IPv6 address and subnet
// returns empty set.
TEST_F(HostDataSourceTest, getAll6BySubnetAddress) {
    EXPECT_TRUE(hdsptr_->getAll6(SubnetID(1), IOAddress("2001:db8:1::1")).empty());
}

} // end of anonymous namespace
