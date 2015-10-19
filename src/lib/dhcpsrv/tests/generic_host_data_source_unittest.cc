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
    /// @todo: Make this code return different hwaddress every time.
    return ("01:02:03:04:05:06");
}

std::string
GenericHostDataSourceTest::generateDuid() {
    /// @todo: Make this code return different duid every time.
    return ("010203040506abcd");
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

void GenericHostDataSourceTest::compareHosts(const ConstHostPtr& host1,
                                             const ConstHostPtr& host2) {
    ASSERT_TRUE(host1);
    ASSERT_TRUE(host2);

    // Compare if both have or have not HWaddress set.
    ASSERT_EQ(host1->getHWAddress(), host2->getHWAddress());
    if (host1->getHWAddress()) {
        // Compare the actual address if they match.
        EXPECT_EQ(*host1->getHWAddress(), *host2->getHWAddress());
    }

    /// @todo: Compare other fields
}

void GenericHostDataSourceTest::testBasic4() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservation.
    HostPtr host = initializeHost4("192.0.2.1", true);
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

}; // namespace test
}; // namespace dhcp
}; // namespace isc
