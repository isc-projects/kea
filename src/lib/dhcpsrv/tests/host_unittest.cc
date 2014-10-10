// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <dhcpsrv/host.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace {

// This test verifies that it is possible to create IPv6 address
// reservation.
TEST(IPv6ResrvTest, constructorAddress) {
    IPv6Resrv resrv(IOAddress("2001:db8:1::cafe"));
    EXPECT_EQ("2001:db8:1::cafe", resrv.getPrefix().toText());
    EXPECT_EQ(128, resrv.getPrefixLen());
    EXPECT_EQ(IPv6Resrv::TYPE_NA, resrv.getType());
}

// This test verifies that it is possible to create IPv6 prefix
// reservation.
TEST(IPv6ResrvTest, constructorPrefix) {
    IPv6Resrv resrv(IOAddress("2001:db8:1::"), 64);
    EXPECT_EQ("2001:db8:1::", resrv.getPrefix().toText());
    EXPECT_EQ(64, resrv.getPrefixLen());
    EXPECT_EQ(IPv6Resrv::TYPE_PD, resrv.getType());
}

// This test verifies that it is possible to modify prefix and its
// length in an existing reservation.
TEST(IPv6ResrvTest, setPrefix) {
    // Create a reservation using an address and prefix length 128.
    IPv6Resrv resrv(IOAddress("2001:db8:1::1"));
    ASSERT_EQ("2001:db8:1::1", resrv.getPrefix().toText());
    ASSERT_EQ(128, resrv.getPrefixLen());
    ASSERT_EQ(IPv6Resrv::TYPE_NA, resrv.getType());

    // Modify the reservation to use a prefix having a length of 48.
    ASSERT_NO_THROW(resrv.set(IOAddress("2001:db8::"), 48));
    EXPECT_EQ("2001:db8::", resrv.getPrefix().toText());
    EXPECT_EQ(48, resrv.getPrefixLen());
    EXPECT_EQ(IPv6Resrv::TYPE_PD, resrv.getType());
}

// This test checks that the equality operators work fine.
TEST(IPv6ResrvTest, equal) {
    EXPECT_TRUE(IPv6Resrv(IOAddress("2001:db8::"), 64) ==
                IPv6Resrv(IOAddress("2001:db8::"), 64));

    EXPECT_FALSE(IPv6Resrv(IOAddress("2001:db8::"), 64) !=
                IPv6Resrv(IOAddress("2001:db8::"), 64));


    EXPECT_TRUE(IPv6Resrv(IOAddress("2001:db8::1")) ==
                IPv6Resrv(IOAddress("2001:db8::1")));
    EXPECT_FALSE(IPv6Resrv(IOAddress("2001:db8::1")) !=
                 IPv6Resrv(IOAddress("2001:db8::1")));


    EXPECT_FALSE(IPv6Resrv(IOAddress("2001:db8::1")) ==
                 IPv6Resrv(IOAddress("2001:db8::2")));
    EXPECT_TRUE(IPv6Resrv(IOAddress("2001:db8::1")) !=
                 IPv6Resrv(IOAddress("2001:db8::2")));

    EXPECT_FALSE(IPv6Resrv(IOAddress("2001:db8::"), 64) ==
                 IPv6Resrv(IOAddress("2001:db8::"), 48));
    EXPECT_TRUE(IPv6Resrv(IOAddress("2001:db8::"), 64) !=
                 IPv6Resrv(IOAddress("2001:db8::"), 48));

}

// This test verfies that it is possible to create a Host object
// using hardware address in the textual format.
TEST(HostTest, createFromHWAddrString) {
    boost::scoped_ptr<Host> host;
    ASSERT_NO_THROW(host.reset(new Host("01:02:03:04:05:06", "hw-address",
                                        SubnetID(1), SubnetID(2),
                                        IOAddress("192.0.2.3"),
                                        "somehost.example.org")));
    // The HW address should be set to non-null.
    HWAddrPtr hwaddr = host->getHWAddress();
    ASSERT_TRUE(hwaddr);

    EXPECT_EQ("hwtype=1 01:02:03:04:05:06", hwaddr->toText());

    // DUID should be null if hardware address is in use.
    EXPECT_FALSE(host->getDuid());
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ(2, host->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.3", host->getIPv4Reservation().toText());
    EXPECT_EQ("somehost.example.org", host->getHostname());

    // Use invalid identifier name
    EXPECT_THROW(Host("01:02:03:04:05:06", "bogus", SubnetID(1), SubnetID(2),
                      IOAddress("192.0.2.3"), "somehost.example.org"),
                 isc::BadValue);

    // Use invalid HW address.
    EXPECT_THROW(Host("010203040506", "hw-address", SubnetID(1), SubnetID(2),
                      IOAddress("192.0.2.3"), "somehost.example.org"),
                 isc::BadValue);
}

// This test verifies that it is possible to create Host object using
// a DUID in the textual format.
TEST(HostTest, createFromDUIDString) {
    boost::scoped_ptr<Host> host;
    ASSERT_NO_THROW(host.reset(new Host("a1:b2:c3:d4:e5:06", "duid",
                                        SubnetID(10), SubnetID(20),
                                        IOAddress("192.0.2.5"),
                                        "me.example.org")));

    // DUID should be set to non-null value.
    DuidPtr duid = host->getDuid();
    ASSERT_TRUE(duid);

    EXPECT_EQ("a1:b2:c3:d4:e5:06", duid->toText());

    // Hardware address must be null if DUID is in use.
    EXPECT_FALSE(host->getHWAddress());

    EXPECT_EQ(10, host->getIPv4SubnetID());
    EXPECT_EQ(20, host->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.5", host->getIPv4Reservation().toText());
    EXPECT_EQ("me.example.org", host->getHostname());

    // Use invalid DUID.
    EXPECT_THROW(Host("bogus", "duid", SubnetID(1), SubnetID(2),
                      IOAddress("192.0.2.3"), "somehost.example.org"),
                 isc::BadValue);

    // Empty DUID is also not allowed.
    try {
        Host("", "duid", SubnetID(1), SubnetID(2),
             IOAddress("192.0.2.3"), "somehost.example.org");
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    EXPECT_THROW(Host("", "duid", SubnetID(1), SubnetID(2),
                      IOAddress("192.0.2.3"), "somehost.example.org"),
                 isc::BadValue);
}

// This test verifies that it is possible to create Host object using
// hardware address in the binary format.
TEST(HostTest, createFromHWAddrBinary) {
    boost::scoped_ptr<Host> host;
    // Prepare the hardware address in binary format.
    const uint8_t hwaddr_data[] = {
        0xaa, 0xab, 0xca, 0xda, 0xbb, 0xee
    };
    ASSERT_NO_THROW(host.reset(new Host(hwaddr_data,
                                        sizeof(hwaddr_data),
                                        Host::IDENT_HWADDR,
                                        SubnetID(1), SubnetID(2),
                                        IOAddress("192.0.2.3"),
                                        "somehost.example.org")));
    // Hardware address should be non-null.
    HWAddrPtr hwaddr = host->getHWAddress();
    ASSERT_TRUE(hwaddr);

    EXPECT_EQ("hwtype=1 aa:ab:ca:da:bb:ee", hwaddr->toText());

    // DUID should be null if hardware address is in use.
    EXPECT_FALSE(host->getDuid());
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ(2, host->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.3", host->getIPv4Reservation().toText());
    EXPECT_EQ("somehost.example.org", host->getHostname());
}

// This test verifies that it is possible to create a Host object using
// DUID in the binary format.
TEST(HostTest, createFromDuidBinary) {
    boost::scoped_ptr<Host> host;
    // Prepare DUID binary.
    const uint8_t duid_data[] = {
        1, 2, 3, 4, 5, 6
    };
    ASSERT_NO_THROW(host.reset(new Host(duid_data,
                                        sizeof(duid_data),
                                        Host::IDENT_DUID,
                                        SubnetID(10), SubnetID(20),
                                        IOAddress("192.0.2.5"),
                                        "me.example.org")));
    // DUID should be non null.
    DuidPtr duid = host->getDuid();
    ASSERT_TRUE(duid);

    EXPECT_EQ("01:02:03:04:05:06", duid->toText());

    // Hardware address should be null if DUID is in use.
    EXPECT_FALSE(host->getHWAddress());
    EXPECT_EQ(10, host->getIPv4SubnetID());
    EXPECT_EQ(20, host->getIPv6SubnetID());
    EXPECT_EQ("192.0.2.5", host->getIPv4Reservation().toText());
    EXPECT_EQ("me.example.org", host->getHostname());
}

// Test that it is possible to replace an identifier for a particular
// Host instance (HW address -> DUID and vice versa) with a new
// indentifier in the textual format.
TEST(HostTest, setIdentifierString) {
    boost::scoped_ptr<Host> host;
    ASSERT_NO_THROW(host.reset(new Host("01:02:03:04:05:06", "hw-address",
                                        SubnetID(1), SubnetID(2),
                                        IOAddress("192.0.2.3"),
                                        "me.example.com")));
    // Initially, there should be a HW address, but not a DUID set.
    ASSERT_TRUE(host->getHWAddress());
    ASSERT_FALSE(host->getDuid());

    // Now, use a DUID as identifier.
    ASSERT_NO_THROW(host->setIdentifier("aabbccddee", "duid"));

    // Verify that the DUID is correct.
    DuidPtr duid = host->getDuid();
    ASSERT_TRUE(duid);
    EXPECT_EQ("aa:bb:cc:dd:ee", duid->toText());
    // HW address should be not set.
    EXPECT_FALSE(host->getHWAddress());

    // Now, let's do another way around.

    ASSERT_NO_THROW(host->setIdentifier("09:08:07:06:05:04", "hw-address"));

    // Verify that HW address is correct.
    HWAddrPtr hw_addr = host->getHWAddress();
    ASSERT_TRUE(hw_addr);
    EXPECT_EQ("hwtype=1 09:08:07:06:05:04", hw_addr->toText());
    // DUID should be not set.
    EXPECT_FALSE(host->getDuid());
}

// Test that it is possible to replace an identifier for a particular
// Host instance (HW address -> DUID and vice versa) with the new
// identifier in the binary format.
TEST(HostTest, setIdentifierBinary) {
    boost::scoped_ptr<Host> host;
    ASSERT_NO_THROW(host.reset(new Host("01:02:03:04:05:06", "hw-address",
                                        SubnetID(1), SubnetID(2),
                                        IOAddress("192.0.2.3"),
                                        "me.example.com")));
    // Initially, there should be a HW address, but not a DUID set.
    ASSERT_TRUE(host->getHWAddress());
    ASSERT_FALSE(host->getDuid());

    // Now, use a DUID as identifier.
    const uint8_t duid_data[] = {
        0xaa, 0xbb, 0xcc, 0xdd, 0xee
    };
    ASSERT_NO_THROW(host->setIdentifier(duid_data, sizeof(duid_data),
                                        Host::IDENT_DUID));

    // Verify that the DUID is correct.
    DuidPtr duid = host->getDuid();
    ASSERT_TRUE(duid);
    EXPECT_EQ("aa:bb:cc:dd:ee", duid->toText());
    // HW address should be not set.
    EXPECT_FALSE(host->getHWAddress());

    // Now, let's do another way around.

    const uint8_t hwaddr_data[] = {
        9, 8, 7, 6, 5, 4
    };
    ASSERT_NO_THROW(host->setIdentifier(hwaddr_data, sizeof(hwaddr_data),
                                        Host::IDENT_HWADDR));

    // Verify that HW address is correct.
    HWAddrPtr hw_addr = host->getHWAddress();
    ASSERT_TRUE(hw_addr);
    EXPECT_EQ("hwtype=1 09:08:07:06:05:04", hw_addr->toText());
    // DUID should be not set.
    EXPECT_FALSE(host->getDuid());
}

/// @brief Checks if the reservation is in the range of reservations.
///
/// @param resrv Reservation to be searched for.
/// @param range Range of reservations returned by the @c Host object
/// in which the reservation will be searched.
bool
reservationExists(const IPv6Resrv& resrv, const IPv6ResrvRange& range) {
    for (IPv6ResrvIterator it = range.first; it != range.second;
         ++it) {
        if (resrv == it->second) {
            return (true);
        }
    }
    return (false);
}

// This test verifies that the IPv6 reservations of a different type can
// be added for the host.
TEST(HostTest, addReservations) {
    boost::scoped_ptr<Host> host;
    ASSERT_NO_THROW(host.reset(new Host("01:02:03:04:05:06", "hw-address",
                                        SubnetID(1), SubnetID(2),
                                        IOAddress("192.0.2.3"))));

    // Add 4 reservations: 2 for NAs, 2 for PDs.
    ASSERT_NO_THROW(
        host->addReservation(IPv6Resrv(IOAddress("2001:db8:1::cafe")));
        host->addReservation(IPv6Resrv(IOAddress("2001:db8:1:1::"), 64));
        host->addReservation(IPv6Resrv(IOAddress("2001:db8:1:2::"), 64));
        host->addReservation(IPv6Resrv(IOAddress("2001:db8:1::1")));
    );

    // Get only NA reservations.
    IPv6ResrvRange addresses = host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
    ASSERT_EQ(2, std::distance(addresses.first, addresses.second));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IOAddress("2001:db8:1::cafe")),
                                  addresses));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IOAddress("2001:db8:1::1")),
                                  addresses));


    // Get only PD reservations.
    IPv6ResrvRange prefixes = host->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    ASSERT_EQ(2, std::distance(prefixes.first, prefixes.second));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IOAddress("2001:db8:1:1::"), 64),
                                  prefixes));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IOAddress("2001:db8:1:2::"), 64),
                                  prefixes));
}


} // end of anonymous namespace
