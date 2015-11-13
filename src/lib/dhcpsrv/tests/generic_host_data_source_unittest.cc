// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

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
    :hdsptr_(NULL) {

}

GenericHostDataSourceTest::~GenericHostDataSourceTest() {
}

std::string
GenericHostDataSourceTest::generateHWAddr() {

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
                                                   bool hwaddr, bool prefix) {
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

    // comapre if both have or have not DUID set
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

    // Now we know that either both or neither have hw address set.
    // If host1 has it, we can proceed to value comparison.
    if (host1->getDuid()) {

        if (expect_match) {
            EXPECT_TRUE(*host1->getDuid() == *host1->getDuid());
        } else {
            EXPECT_FALSE(*host1->getDuid() == *host1->getDuid());
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
    EXPECT_EQ(host1->getIdentifier(), host2->getIdentifier());

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

void
GenericHostDataSourceTest::compareReservations6(IPv6ResrvRange /*a*/,
                                                IPv6ResrvRange /*b*/) {
    /// @todo: Implement client classes comparison
}

void
GenericHostDataSourceTest::compareClientClasses(const ClientClasses& /*classes1*/,
                                                const ClientClasses& /*classes2*/) {
    /// @todo: Implement client classes comparison
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

    // And then retrive it.
    ConstHostPtr from_hds = hdsptr_->get4(subnet, IOAddress("192.0.2.1"));

    // Make sure we got something back.
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

void GenericHostDataSourceTest::testGetByHWaddr() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    HostPtr host1 = initializeHost4("192.0.2.1", true);
    HostPtr host2 = initializeHost4("192.0.2.2", true);

    // Sanity check: make sure the hosts have different HW addresses.
    ASSERT_TRUE(host1->getHWAddress());
    ASSERT_TRUE(host2->getHWAddress());
    compareHwaddrs(host1, host2, false);

    // Try to add both of the to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));

    SubnetID subnet1 = host1->getIPv4SubnetID();
    SubnetID subnet2 = host2->getIPv4SubnetID();

    ConstHostPtr from_hds1 = hdsptr_->get4(subnet1, host1->getHWAddress());
    ConstHostPtr from_hds2 = hdsptr_->get4(subnet2, host2->getHWAddress());

    // Now let's check if we got what we expected.
    ASSERT_TRUE(from_hds1);
    ASSERT_TRUE(from_hds2);
    compareHosts(host1, from_hds1);
    compareHosts(host2, from_hds2);
}

void GenericHostDataSourceTest::testGetByClientId() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    HostPtr host1 = initializeHost4("192.0.2.1", false);
    HostPtr host2 = initializeHost4("192.0.2.2", false);

    // Sanity check: make sure the hosts have different client-ids.
    ASSERT_TRUE(host1->getDuid());
    ASSERT_TRUE(host2->getDuid());
    compareDuids(host1, host2, false);

    // Try to add both of the to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));

    SubnetID subnet1 = host1->getIPv4SubnetID();
    SubnetID subnet2 = host2->getIPv4SubnetID();

    ConstHostPtr from_hds1 = hdsptr_->get4(subnet1, HWAddrPtr(), host1->getDuid());
    ConstHostPtr from_hds2 = hdsptr_->get4(subnet2, HWAddrPtr(), host2->getDuid());

    // Now let's check if we got what we expected.
    ASSERT_TRUE(from_hds1);
    ASSERT_TRUE(from_hds2);
    compareHosts(host1, from_hds1);
    compareHosts(host2, from_hds2);
}

}; // namespace test
}; // namespace dhcp
}; // namespace isc
