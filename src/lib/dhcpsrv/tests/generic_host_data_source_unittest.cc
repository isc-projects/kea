// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcpsrv/tests/generic_host_data_source_unittest.h>
#include <dhcpsrv/tests/test_utils.h>
#include <dhcpsrv/database_connection.h>
#include <asiolink/io_address.h>
#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc::asiolink;

namespace isc {
namespace dhcp {
namespace test {

GenericHostDataSourceTest::GenericHostDataSourceTest()
    :hdsptr_() {

}

GenericHostDataSourceTest::~GenericHostDataSourceTest() {
}

std::string
GenericHostDataSourceTest::generateHWAddr() {
    /// @todo: Consider moving this somewhere to lib/testutils.

    // Let's use something that is easily printable. That's convenient
    // if you need to enter MySQL queries by hand.
    static uint8_t hwaddr[] = {65, 66, 67, 68, 69, 70};

    stringstream tmp;
    for (int i = 0; i < sizeof(hwaddr); ++i) {
        if (i) {
            tmp << ":";
        }
        tmp << std::setw(2) << std::hex << std::setfill('0')
            << static_cast<unsigned int>(hwaddr[i]);
    }

    // Increase the address for the next time we use it.
    // This is primitive, but will work for 65k unique
    // addresses.
    hwaddr[sizeof(hwaddr) - 1]++;
    if (hwaddr[sizeof(hwaddr) - 1] == 0) {
        hwaddr[sizeof(hwaddr) - 2]++;
    }
    return (tmp.str());
}

std::string
GenericHostDataSourceTest::generateDuid() {
    /// @todo: Consider moving this somewhere to lib/testutils.

    // Let's use something that is easily printable. That's convenient
    // if you need to enter MySQL queries by hand.
    static uint8_t duid[] = { 65, 66, 67, 68, 69, 70, 71, 72, 73, 74 };

    stringstream tmp;
    for (int i = 0; i < sizeof(duid); ++i) {
        tmp << std::setw(2) << std::hex << std::setfill('0')
            << static_cast<unsigned int>(duid[i]);
    }

    // Increase the DUID for the next time we use it.
    // This is primitive, but will work for 65k unique
    // DUIDs.
    duid[sizeof(duid) - 1]++;
    if (duid[sizeof(duid) - 1] == 0) {
        duid[sizeof(duid) - 2]++;
    }
    return (tmp.str());
}

HostPtr GenericHostDataSourceTest::initializeHost4(std::string address,
                                                   bool hwaddr) {
    string ident;
    string ident_type;

    if (hwaddr) {
        ident = generateHWAddr();
        ident_type = "hw-address";
    } else {
        ident = generateDuid();
        ident_type = "duid";
    }

    // Let's create ever increasing subnet-ids. Let's keep those different,
    // so subnet4 != subnet6. Useful for catching cases if the code confuses
    // subnet4 with subnet6.
    static SubnetID subnet4 = 0;
    static SubnetID subnet6 = 100;
    subnet4++;
    subnet6++;

    IOAddress addr(address);
    HostPtr host(new Host(ident, ident_type, subnet4, subnet6, addr));

    return (host);
}

HostPtr GenericHostDataSourceTest::initializeHost6(std::string address,
                                                   Host::IdentifierType identifier,
                                                   bool prefix) {
    string ident;
    string ident_type;

    switch (identifier) {
    case Host::IDENT_HWADDR:
        ident = generateHWAddr();
        ident_type = "hw-address";
        break;
    case Host::IDENT_DUID:
        ident = generateDuid();
        ident_type = "duid";
        break;
    default:
        ADD_FAILURE() << "Unknown IdType: " << identifier;
        return HostPtr();
    }

    // Let's create ever increasing subnet-ids. Let's keep those different,
    // so subnet4 != subnet6. Useful for catching cases if the code confuses
    // subnet4 with subnet6.
    static SubnetID subnet4 = 0;
    static SubnetID subnet6 = 100;
    subnet4++;
    subnet6++;

    HostPtr host(new Host(ident, ident_type, subnet4, subnet6, IOAddress("0.0.0.0")));

    if (!prefix) {
        // Create IPv6 reservation (for an address)
        IPv6Resrv resv(IPv6Resrv::TYPE_NA, IOAddress(address), 128);
        host->addReservation(resv);
    } else {
        // Create IPv6 reservation for a /64 prefix
        IPv6Resrv resv(IPv6Resrv::TYPE_PD, IOAddress(address), 64);
        host->addReservation(resv);
    }
    return (host);
}

void
GenericHostDataSourceTest::compareHwaddrs(const ConstHostPtr& host1,
                                          const ConstHostPtr& host2,
                                          bool expect_match) {
    ASSERT_TRUE(host1);
    ASSERT_TRUE(host2);

    // Compare if both have or have not HWaddress set.
    if ((host1->getHWAddress() && !host2->getHWAddress()) ||
        (!host1->getHWAddress() && host2->getHWAddress())) {

        // One host has hardware address set while the other has not.
        // Let's see if it's a problem.
        if (expect_match) {
            ADD_FAILURE() << "Host comparison failed: host1 hwaddress="
                          << host1->getHWAddress() << ", host2 hwaddress="
                          << host2->getHWAddress();
        }
        return;
    }

    // Now we know that either both or neither have hw address set.
    // If host1 has it, we can proceed to value comparison.
    if (host1->getHWAddress()) {

        if (expect_match) {
            // Compare the actual address if they match.
            EXPECT_TRUE(*host1->getHWAddress() == *host2->getHWAddress());
        } else {
            EXPECT_FALSE(*host1->getHWAddress() == *host2->getHWAddress());
        }
        if (*host1->getHWAddress() != *host2->getHWAddress()) {
            cout << host1->getHWAddress()->toText(true) << endl;
            cout << host2->getHWAddress()->toText(true) << endl;
        }
    }
}

void
GenericHostDataSourceTest::compareDuids(const ConstHostPtr& host1,
                                        const ConstHostPtr& host2,
                                        bool expect_match) {
    ASSERT_TRUE(host1);
    ASSERT_TRUE(host2);

    // compare if both have or have not DUID set
    if ((host1->getDuid() && !host2->getDuid()) ||
        (!host1->getDuid() && host2->getDuid())) {

        // One host has a DUID and the other doesn't.
        // Let's see if it's a problem.
        if (expect_match) {
            ADD_FAILURE() << "DUID comparison failed: host1 duid="
                          << host1->getDuid() << ", host2 duid="
                          << host2->getDuid();
        }
        return;
    }

    // Now we know that either both or neither have DUID set.
    // If host1 has it, we can proceed to value comparison.
    if (host1->getDuid()) {

        if (expect_match) {
            EXPECT_TRUE(*host1->getDuid() == *host2->getDuid());
        } else {
            EXPECT_FALSE(*host1->getDuid() == *host2->getDuid());
        }
        if (*host1->getDuid() != *host2->getDuid()) {
            cout << host1->getDuid()->toText() << endl;
            cout << host2->getDuid()->toText() << endl;
        }
    }
}

void GenericHostDataSourceTest::compareHosts(const ConstHostPtr& host1,
                                             const ConstHostPtr& host2) {

    // Let's compare HW addresses and expect match.
    compareHwaddrs(host1, host2, true);

    // Now compare DUIDs
    compareDuids(host1, host2, true);

    // Now check that the identifiers returned as vectors are the same
    EXPECT_EQ(host1->getIdentifierType(), host2->getIdentifierType());
    EXPECT_TRUE(host1->getIdentifier() == host2->getIdentifier());

    // Check host parameters
    EXPECT_EQ(host1->getIPv4SubnetID(), host2->getIPv4SubnetID());
    EXPECT_EQ(host1->getIPv6SubnetID(), host2->getIPv6SubnetID());
    EXPECT_EQ(host1->getIPv4Reservation(), host2->getIPv4Reservation());
    EXPECT_EQ(host1->getHostname(), host2->getHostname());

    // Compare IPv6 reservations
    compareReservations6(host1->getIPv6Reservations(),
                         host2->getIPv6Reservations());

    // And compare client classification details
    compareClientClasses(host1->getClientClasses4(),
                         host2->getClientClasses4());

    compareClientClasses(host1->getClientClasses6(),
                         host2->getClientClasses6());
}

DuidPtr
GenericHostDataSourceTest::HWAddrToDuid(const HWAddrPtr& hwaddr) {
    if (!hwaddr) {
        return (DuidPtr());
    }

    return (DuidPtr(new DUID(hwaddr->hwaddr_)));
}

HWAddrPtr
GenericHostDataSourceTest::DuidToHWAddr(const DuidPtr& duid) {
    if (!duid) {
        return (HWAddrPtr());
    }

    return (HWAddrPtr(new HWAddr(duid->getDuid(), HTYPE_ETHER)));
}


void
GenericHostDataSourceTest::compareReservations6(IPv6ResrvRange resrv1,
                                                IPv6ResrvRange resrv2) {

    // Compare number of reservations for both hosts
    if (std::distance(resrv1.first, resrv1.second) !=
            std::distance(resrv2.first, resrv2.second)){
        ADD_FAILURE()<< "Reservation comparison failed, "
            "hosts got different number of reservations.";
        return;
    }

    // Iterate over the range of reservations to find a match in the
    // reference range.
    for (IPv6ResrvIterator r1 = resrv1.first; r1 != resrv1.second; ++r1) {
        IPv6ResrvIterator r2 = resrv2.first;
        for (; r2 != resrv2.second; ++r2) {
            // IPv6Resrv object implements equality operator.
            if (r1->second == r2->second) {
                break;
            }
        }
        // If r2 iterator reached the end of the range it means that there
        // is no match.
        if (r2 == resrv2.second) {
            ADD_FAILURE() << "No match found for reservation: "
                          << resrv1.first->second.getPrefix().toText();
        }
    }

    if (std::distance(resrv1.first, resrv1.second) > 0) {
        for (; resrv1.first != resrv1.second; resrv1.first++) {
            IPv6ResrvIterator iter = resrv2.first;
            while (iter != resrv2.second) {
                if((resrv1.first->second.getType() == iter->second.getType()) &&
                        (resrv1.first->second.getPrefixLen() == iter->second.getPrefixLen()) &&
                        (resrv1.first->second.getPrefix() == iter->second.getPrefix())) {
                    break;
                }
                iter++;
                if (iter == resrv2.second) {
                    ADD_FAILURE()<< "Reservation comparison failed, "
                    "no match for reservation: "
                    << resrv1.first->second.getPrefix().toText();
                }
            }
        }
    }
}

void
GenericHostDataSourceTest::compareClientClasses(const ClientClasses& /*classes1*/,
                                                const ClientClasses& /*classes2*/) {
    /// @todo: Implement client classes comparison.
    ///        This is part of the work for #4213.
}

void GenericHostDataSourceTest::testBasic4(bool hwaddr) {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservation.
    HostPtr host = initializeHost4("192.0.2.1", hwaddr);
    ASSERT_TRUE(host); // Make sure the host is generate properly.
    SubnetID subnet = host->getIPv4SubnetID();

    // Try to add it to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // This should not return anything
    ConstHostPtr from_hds = hdsptr_->get4(subnet, IOAddress("10.10.10.10"));
    ASSERT_FALSE(from_hds);

    // This time it should return a host
    from_hds = hdsptr_->get4(subnet, IOAddress("192.0.2.1"));
    ASSERT_TRUE(from_hds);

    // Finally, let's check if what we got makes any sense.
    compareHosts(host, from_hds);
}


void GenericHostDataSourceTest::testGetByIPv4(bool hwaddr) {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create a couple of hosts...
    HostPtr host1 = initializeHost4("192.0.2.1", hwaddr);
    HostPtr host2 = initializeHost4("192.0.2.2", hwaddr);
    HostPtr host3 = initializeHost4("192.0.2.3", hwaddr);
    HostPtr host4 = initializeHost4("192.0.2.4", hwaddr);

    // ... and add them to the data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));
    ASSERT_NO_THROW(hdsptr_->add(host3));
    ASSERT_NO_THROW(hdsptr_->add(host4));

    SubnetID subnet1 = host1->getIPv4SubnetID();
    SubnetID subnet2 = host2->getIPv4SubnetID();
    SubnetID subnet3 = host3->getIPv4SubnetID();
    SubnetID subnet4 = host4->getIPv4SubnetID();

    // And then try to retrieve them back.
    ConstHostPtr from_hds1 = hdsptr_->get4(subnet1, IOAddress("192.0.2.1"));
    ConstHostPtr from_hds2 = hdsptr_->get4(subnet2, IOAddress("192.0.2.2"));
    ConstHostPtr from_hds3 = hdsptr_->get4(subnet3, IOAddress("192.0.2.3"));
    ConstHostPtr from_hds4 = hdsptr_->get4(subnet4, IOAddress("192.0.2.4"));

    // Make sure we got something back.
    ASSERT_TRUE(from_hds1);
    ASSERT_TRUE(from_hds2);
    ASSERT_TRUE(from_hds3);
    ASSERT_TRUE(from_hds4);

    // Then let's check that what we got seems correct.
    compareHosts(host1, from_hds1);
    compareHosts(host2, from_hds2);
    compareHosts(host3, from_hds3);
    compareHosts(host4, from_hds4);

    // Ok, finally let's check that getting by a different address
    // will not work.
    EXPECT_FALSE(hdsptr_->get4(subnet1, IOAddress("192.0.1.5")));
}

void GenericHostDataSourceTest::testGet4ByHWAddr() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    HostPtr host1 = initializeHost4("192.0.2.1", true);
    HostPtr host2 = initializeHost4("192.0.2.2", true);

    // Sanity check: make sure the hosts have different HW addresses.
    ASSERT_TRUE(host1->getHWAddress());
    ASSERT_TRUE(host2->getHWAddress());
    compareHwaddrs(host1, host2, false);

    // Try to add both of them to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));

    SubnetID subnet1 = host1->getIPv4SubnetID();
    SubnetID subnet2 = host2->getIPv4SubnetID();

    ConstHostPtr from_hds1 = hdsptr_->get4(subnet1,
                                           Host::IDENT_HWADDR,
                                           &host1->getIdentifier()[0],
                                           host1->getIdentifier().size());
    ConstHostPtr from_hds2 = hdsptr_->get4(subnet2,
                                           Host::IDENT_HWADDR,
                                           &host2->getIdentifier()[0],
                                           host2->getIdentifier().size());

    // Now let's check if we got what we expected.
    ASSERT_TRUE(from_hds1);
    ASSERT_TRUE(from_hds2);
    compareHosts(host1, from_hds1);
    compareHosts(host2, from_hds2);
}

void GenericHostDataSourceTest::testGet4ByClientId() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    HostPtr host1 = initializeHost4("192.0.2.1", false);
    HostPtr host2 = initializeHost4("192.0.2.2", false);

    // Sanity check: make sure the hosts have different client-ids.
    ASSERT_TRUE(host1->getDuid());
    ASSERT_TRUE(host2->getDuid());
    compareDuids(host1, host2, false);

    // Try to add both of them to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));

    SubnetID subnet1 = host1->getIPv4SubnetID();
    SubnetID subnet2 = host2->getIPv4SubnetID();

    ConstHostPtr from_hds1 = hdsptr_->get4(subnet1,
                                           Host::IDENT_DUID,
                                           &host1->getIdentifier()[0],
                                           host1->getIdentifier().size());

    ConstHostPtr from_hds2 = hdsptr_->get4(subnet2,
                                           Host::IDENT_DUID,
                                           &host2->getIdentifier()[0],
                                           host2->getIdentifier().size());

    // Now let's check if we got what we expected.
    ASSERT_TRUE(from_hds1);
    ASSERT_TRUE(from_hds2);
    compareHosts(host1, from_hds1);
    compareHosts(host2, from_hds2);
}

void GenericHostDataSourceTest::testHWAddrNotClientId() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host with HW address
    HostPtr host = initializeHost4("192.0.2.1", true);
    ASSERT_TRUE(host->getHWAddress());
    ASSERT_FALSE(host->getDuid());

    // Try to add it to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host));

    SubnetID subnet = host->getIPv4SubnetID();

    DuidPtr duid = HWAddrToDuid(host->getHWAddress());

    // Get the host by HW address (should succeed)
    ConstHostPtr by_hwaddr = hdsptr_->get4(subnet, Host::IDENT_HWADDR,
                                           &host->getIdentifier()[0],
                                           host->getIdentifier().size());

    // Get the host by DUID (should fail)
    ConstHostPtr by_duid   = hdsptr_->get4(subnet, Host::IDENT_DUID,
                                           &host->getIdentifier()[0],
                                           host->getIdentifier().size());

    // Now let's check if we got what we expected.
    EXPECT_TRUE(by_hwaddr);
    EXPECT_FALSE(by_duid);
}

void GenericHostDataSourceTest::testClientIdNotHWAddr() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host with client-id
    HostPtr host = initializeHost4("192.0.2.1", false);
    ASSERT_FALSE(host->getHWAddress());
    ASSERT_TRUE(host->getDuid());

    // Try to add it to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host));

    SubnetID subnet = host->getIPv4SubnetID();

    HWAddrPtr hwaddr = DuidToHWAddr(host->getDuid());

    // Get the host by DUID (should succeed)
    ConstHostPtr by_duid   = hdsptr_->get4(subnet, Host::IDENT_DUID,
                                           &host->getIdentifier()[0],
                                           host->getIdentifier().size());


    // Get the host by HW address (should fail)
    ConstHostPtr by_hwaddr = hdsptr_->get4(subnet, Host::IDENT_HWADDR,
                                           &host->getIdentifier()[0],
                                           host->getIdentifier().size());

    // Now let's check if we got what we expected.
    EXPECT_TRUE(by_duid);
    EXPECT_FALSE(by_hwaddr);
}

void
GenericHostDataSourceTest::testHostname(std::string name, int num) {

    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Initialize the address to 192.0.2.0 (this will be bumped
    // up to 192.0.2.1 in the first iteration)
    IOAddress addr("192.0.2.0");

    vector<HostPtr> hosts;

    // Prepare a vector of hosts with unique hostnames
    for (int i = 0; i < num; ++i) {

        addr = IOAddress::increase(addr);

        HostPtr host = initializeHost4(addr.toText(), false);

        stringstream hostname;
        hostname.str("");
        if (num > 1) {
            hostname << i;
        }
        hostname << name;
        host->setHostname(hostname.str());

        hosts.push_back(host);
    }

    // Now add them all to the host data source.
    for (vector<HostPtr>::const_iterator it = hosts.begin();
         it != hosts.end(); ++it) {
        // Try to add both of the to the host data source.
        ASSERT_NO_THROW(hdsptr_->add(*it));
    }

    // And finally retrieve them one by one and check
    // if the hostname was preserved.
    for (vector<HostPtr>::const_iterator it = hosts.begin();
         it != hosts.end(); ++it) {

        ConstHostPtr from_hds;
        ASSERT_NO_THROW(from_hds = hdsptr_->get4(
                            (*it)->getIPv4SubnetID(),
                            (*it)->getIPv4Reservation()));
        ASSERT_TRUE(from_hds);

        EXPECT_EQ((*it)->getHostname(), from_hds->getHostname());
    }
}

void
GenericHostDataSourceTest::testMultipleSubnets(int subnets, bool hwaddr) {

    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    HostPtr host = initializeHost4("192.0.2.1", hwaddr);

    for (int i = 0; i < subnets; ++i) {
        host->setIPv4SubnetID(i + 1000);
        host->setIPv6SubnetID(i + 1000);

        // Check that the same host can have reservations in multiple subnets.
        EXPECT_NO_THROW(hdsptr_->add(host));
    }

    // Now check that the reservations can be retrieved by IPv4 address from
    // each subnet separately.
    for (int i = 0; i < subnets; ++i) {

        // Try to retrieve the host by IPv4 address.
        ConstHostPtr from_hds = hdsptr_->get4(i + 1000, host->getIPv4Reservation());

        ASSERT_TRUE(from_hds);
        EXPECT_EQ(i + 1000, from_hds->getIPv4SubnetID());

        // Try to retrieve the host by either HW address of client-id
        from_hds = hdsptr_->get4(i + 1000,
                                 hwaddr ? Host::IDENT_HWADDR : Host::IDENT_DUID,
                                 &host->getIdentifier()[0],
                                 host->getIdentifier().size());
        ASSERT_TRUE(from_hds);
        EXPECT_EQ(i + 1000, from_hds->getIPv4SubnetID());
    }

    // Now check that they can be retrieved all at once, by IPv4 address.
    ConstHostCollection all_by_addr = hdsptr_->getAll4(IOAddress("192.0.2.1"));
    ASSERT_EQ(subnets, all_by_addr.size());

    // Verify that the values returned are proper.
    int i = 0;
    for (ConstHostCollection::const_iterator it = all_by_addr.begin();
         it != all_by_addr.end(); ++it) {
        EXPECT_EQ(IOAddress("192.0.2.1"), (*it)->getIPv4Reservation());
        EXPECT_EQ(1000 + i++, (*it)->getIPv4SubnetID());
    }

    // Finally, check that the hosts can be retrived by HW address or DUID
    ConstHostCollection all_by_id =
        hdsptr_->getAll(hwaddr ? Host::IDENT_HWADDR : Host::IDENT_DUID,
                        &host->getIdentifier()[0],
                        host->getIdentifier().size());
    ASSERT_EQ(subnets, all_by_id.size());

    // Check that the returned values are as expected.
    i = 0;
    for (ConstHostCollection::const_iterator it = all_by_id.begin();
         it != all_by_id.end(); ++it) {
        EXPECT_EQ(IOAddress("192.0.2.1"), (*it)->getIPv4Reservation());
        EXPECT_EQ(1000 + i++, (*it)->getIPv4SubnetID());
    }
}

void GenericHostDataSourceTest::testGet6ByHWAddr() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservations.
    HostPtr host1 = initializeHost6("2001:db8::1", Host::IDENT_HWADDR, true);
    HostPtr host2 = initializeHost6("2001:db8::2", Host::IDENT_HWADDR, true);

    // Sanity check: make sure the hosts have different HW addresses.
    ASSERT_TRUE(host1->getHWAddress());
    ASSERT_TRUE(host2->getHWAddress());

    compareHwaddrs(host1, host2, false);

    // Try to add both of them to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));

    SubnetID subnet1 = host1->getIPv6SubnetID();
    SubnetID subnet2 = host2->getIPv6SubnetID();

    ConstHostPtr from_hds1 = hdsptr_->get6(subnet1, Host::IDENT_HWADDR,
                                           &host1->getIdentifier()[0],
                                           host1->getIdentifier().size());

    ConstHostPtr from_hds2 = hdsptr_->get6(subnet2, Host::IDENT_HWADDR,
                                           &host2->getIdentifier()[0],
                                           host2->getIdentifier().size());

    // Now let's check if we got what we expected.
    ASSERT_TRUE(from_hds1);
    ASSERT_TRUE(from_hds2);
    compareHosts(host1, from_hds1);
    compareHosts(host2, from_hds2);
}

void GenericHostDataSourceTest::testGet6ByClientId() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservations.
    HostPtr host1 = initializeHost6("2001:db8::1", Host::IDENT_DUID, true);
    HostPtr host2 = initializeHost6("2001:db8::2", Host::IDENT_DUID, true);

    // Sanity check: make sure the hosts have different HW addresses.
    ASSERT_TRUE(host1->getDuid());
    ASSERT_TRUE(host2->getDuid());

    compareDuids(host1, host2, false);

    // Try to add both of them to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));

    SubnetID subnet1 = host1->getIPv6SubnetID();
    SubnetID subnet2 = host2->getIPv6SubnetID();

    ConstHostPtr from_hds1 = hdsptr_->get6(subnet1, Host::IDENT_DUID,
                                           &host1->getIdentifier()[0],
                                           host1->getIdentifier().size());

    ConstHostPtr from_hds2 = hdsptr_->get6(subnet2, Host::IDENT_DUID,
                                           &host2->getIdentifier()[0],
                                           host2->getIdentifier().size());

    // Now let's check if we got what we expected.
    ASSERT_TRUE(from_hds1);
    ASSERT_TRUE(from_hds2);
    compareHosts(host1, from_hds1);
    compareHosts(host2, from_hds2);
}

void
GenericHostDataSourceTest::testSubnetId6(int subnets, Host::IdentifierType id) {

    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    HostPtr host = initializeHost6("2001:db8::0", id, true);

    for (int i = 0; i < subnets; ++i) {
        host->setIPv4SubnetID(i + 1000);
        host->setIPv6SubnetID(i + 1000);

        // Check that the same host can have reservations in multiple subnets.
        EXPECT_NO_THROW(hdsptr_->add(host));
    }

    // Check that the reservations can be retrieved from each subnet separately.
    for (int i = 0; i < subnets; ++i) {

        // Try to retrieve the host
        ConstHostPtr from_hds = hdsptr_->get6(i + 1000, host->getDuid(),
                                              host->getHWAddress());

        ASSERT_TRUE(from_hds);
        EXPECT_EQ(i + 1000, from_hds->getIPv6SubnetID());
    }

    // Check that the hosts can all be retrived by HW address or DUID
    ConstHostCollection all_by_id = hdsptr_->getAll(id, &host->getIdentifier()[0],
                                                    host->getIdentifier().size());
    ASSERT_EQ(subnets, all_by_id.size());

    // Check that the returned values are as expected.
    int i = 0;
    for (ConstHostCollection::const_iterator it = all_by_id.begin();
         it != all_by_id.end(); ++it) {
        EXPECT_EQ(IOAddress("0.0.0.0"), (*it)->getIPv4Reservation());
        EXPECT_EQ(1000 + i++, (*it)->getIPv6SubnetID());
    }
}

void GenericHostDataSourceTest::testGetByIPv6(Host::IdentifierType id,
                                              bool prefix) {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create a couple of hosts...
    HostPtr host1 = initializeHost6("2001:db8::1", id, prefix);
    HostPtr host2 = initializeHost6("2001:db8::2", id, prefix);
    HostPtr host3 = initializeHost6("2001:db8::3", id, prefix);
    HostPtr host4 = initializeHost6("2001:db8::4", id, prefix);

    // ... and add them to the data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));
    ASSERT_NO_THROW(hdsptr_->add(host3));
    ASSERT_NO_THROW(hdsptr_->add(host4));

    // Are we talking about addresses or prefixes?
    uint8_t len = prefix ? 64 : 128;

    // And then try to retrieve them back.
    ConstHostPtr from_hds1 = hdsptr_->get6(IOAddress("2001:db8::1"), len);
    ConstHostPtr from_hds2 = hdsptr_->get6(IOAddress("2001:db8::2"), len);
    ConstHostPtr from_hds3 = hdsptr_->get6(IOAddress("2001:db8::3"), len);
    ConstHostPtr from_hds4 = hdsptr_->get6(IOAddress("2001:db8::4"), len);

    // Make sure we got something back.
    ASSERT_TRUE(from_hds1);
    ASSERT_TRUE(from_hds2);
    ASSERT_TRUE(from_hds3);
    ASSERT_TRUE(from_hds4);

    // Then let's check that what we got seems correct.
    compareHosts(host1, from_hds1);
    compareHosts(host2, from_hds2);
    compareHosts(host3, from_hds3);
    compareHosts(host4, from_hds4);

    // Ok, finally let's check that getting by a different address
    // will not work.
    EXPECT_FALSE(hdsptr_->get6(IOAddress("2001:db8::5"), len));
}

void GenericHostDataSourceTest::testAddDuplicate6WithSameDUID() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservations.
    HostPtr host = initializeHost6("2001:db8::1", Host::IDENT_DUID, true);

    // Add this reservation once.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Then try to add it again, it should throw an exception.
    ASSERT_THROW(hdsptr_->add(host), DuplicateEntry);
}

void GenericHostDataSourceTest::testAddDuplicate6WithSameHWAddr() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservations.
    HostPtr host = initializeHost6("2001:db8::1", Host::IDENT_HWADDR, true);

    // Add this reservation once.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Then try to add it again, it should throw an exception.
    ASSERT_THROW(hdsptr_->add(host), DuplicateEntry);
}

void GenericHostDataSourceTest::testAddDuplicate4() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservations.
    HostPtr host = initializeHost4("192.0.2.1", false);

    // Add this reservation once.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Then try to add it again, it should throw an exception.
    ASSERT_THROW(hdsptr_->add(host), DuplicateEntry);

    // This time use a different host identifier and try again.
    // This update should be rejected because of duplicated
    // address.
    ASSERT_NO_THROW(host->setIdentifier("01:02:03:04:05:06", "hw-address"));
    ASSERT_THROW(hdsptr_->add(host), DuplicateEntry);

    // Modify address to avoid its duplication and make sure
    // we can now add the host.
    ASSERT_NO_THROW(host->setIPv4Reservation(IOAddress("192.0.2.3")));
    EXPECT_NO_THROW(hdsptr_->add(host));
}

void GenericHostDataSourceTest::testAddr6AndPrefix(){
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservations with prefix reservation (prefix = true)
    HostPtr host = initializeHost6("2001:db8::1", Host::IDENT_DUID, true);

    // Create IPv6 reservation (for an address) and add it to the host
    IPv6Resrv resv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::2"), 128);
    host->addReservation(resv);

    // Add this reservation
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Get this host by DUID
    ConstHostPtr from_hds = hdsptr_->get6(host->getIPv6SubnetID(),
                                          Host::IDENT_DUID,
                                          &host->getIdentifier()[0],
                                          host->getIdentifier().size());

    // Make sure we got something back
    ASSERT_TRUE(from_hds);

    // Check if reservations are the same
    compareReservations6(host->getIPv6Reservations(),
                         from_hds->getIPv6Reservations());
}

void GenericHostDataSourceTest::testMultipleReservations(){
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);
    uint8_t len = 128;

    HostPtr host = initializeHost6("2001:db8::1", Host::IDENT_DUID, false);

    // Add some reservations
    IPv6Resrv resv1(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::6"), len);
    IPv6Resrv resv2(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::7"), len);
    IPv6Resrv resv3(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::8"), len);
    IPv6Resrv resv4(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::9"), len);

    host->addReservation(resv1);
    host->addReservation(resv2);
    host->addReservation(resv3);
    host->addReservation(resv4);

    ASSERT_NO_THROW(hdsptr_->add(host));


    ConstHostPtr from_hds = hdsptr_->get6(IOAddress("2001:db8::1"), len);

    // Make sure we got something back
    ASSERT_TRUE(from_hds);

    // Check if hosts are the same
    compareHosts(host, from_hds);
}

void GenericHostDataSourceTest::testMultipleReservationsDifferentOrder(){
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);
    uint8_t len = 128;

    HostPtr host1 = initializeHost6("2001:db8::1", Host::IDENT_DUID, false);
    HostPtr host2 = initializeHost6("2001:db8::1", Host::IDENT_DUID, false);

    // Add some reservations
    IPv6Resrv resv1(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::6"), len);
    IPv6Resrv resv2(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::7"), len);
    IPv6Resrv resv3(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::8"), len);
    IPv6Resrv resv4(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::9"), len);

    host1->addReservation(resv1);
    host1->addReservation(resv2);
    host1->addReservation(resv3);
    host1->addReservation(resv4);

    host2->addReservation(resv4);
    host2->addReservation(resv3);
    host2->addReservation(resv2);
    host2->addReservation(resv1);

    // Check if reservations are the same
    compareReservations6(host1->getIPv6Reservations(), host2->getIPv6Reservations());

}

}; // namespace test
}; // namespace dhcp
}; // namespace isc
