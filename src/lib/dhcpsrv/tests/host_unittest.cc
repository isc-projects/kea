// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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
    IPv6Resrv resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::cafe"));
    EXPECT_EQ("2001:db8:1::cafe", resrv.getPrefix().toText());
    EXPECT_EQ(128, resrv.getPrefixLen());
    EXPECT_EQ(IPv6Resrv::TYPE_NA, resrv.getType());
}

// This test verifies that it is possible to create IPv6 prefix
// reservation.
TEST(IPv6ResrvTest, constructorPrefix) {
    IPv6Resrv resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1::"), 64);
    EXPECT_EQ("2001:db8:1::", resrv.getPrefix().toText());
    EXPECT_EQ(64, resrv.getPrefixLen());
    EXPECT_EQ(IPv6Resrv::TYPE_PD, resrv.getType());
}

// This test verifies that the toText() function prints correctly.
TEST(IPv6ResrvTest, toText) {
    IPv6Resrv resrv_prefix(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1::"), 64);
    EXPECT_EQ("2001:db8:1::/64", resrv_prefix.toText());

    IPv6Resrv resrv_address(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:111::23"));
    EXPECT_EQ("2001:db8:111::23", resrv_address.toText());
}

// This test verifies that invalid prefix is rejected.
TEST(IPv6ResrvTest, constructorInvalidPrefix) {
    // IPv4 address is invalid for IPv6 reservation.
    EXPECT_THROW(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("10.0.0.1"), 128),
                 isc::BadValue);
    // Multicast address is invalid for IPv6 reservation.
    EXPECT_THROW(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("ff02:1::2"), 128),
                 isc::BadValue);
}

// This test verifies that invalid prefix length is rejected.
TEST(IPv6ResrvTest, constructiorInvalidPrefixLength) {
    ASSERT_NO_THROW(IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1::"),
                              128));
    EXPECT_THROW(IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1::"), 129),
                 isc::BadValue);
    EXPECT_THROW(IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1::"), 244),
                 isc::BadValue);
    EXPECT_THROW(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::"), 64),
                 isc::BadValue);
}

// This test verifies that it is possible to modify prefix and its
// length in an existing reservation.
TEST(IPv6ResrvTest, setPrefix) {
    // Create a reservation using an address and prefix length 128.
    IPv6Resrv resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::1"));
    ASSERT_EQ("2001:db8:1::1", resrv.getPrefix().toText());
    ASSERT_EQ(128, resrv.getPrefixLen());
    ASSERT_EQ(IPv6Resrv::TYPE_NA, resrv.getType());

    // Modify the reservation to use a prefix having a length of 48.
    ASSERT_NO_THROW(resrv.set(IPv6Resrv::TYPE_PD, IOAddress("2001:db8::"), 48));
    EXPECT_EQ("2001:db8::", resrv.getPrefix().toText());
    EXPECT_EQ(48, resrv.getPrefixLen());
    EXPECT_EQ(IPv6Resrv::TYPE_PD, resrv.getType());

    // IPv4 address is invalid for IPv6 reservation.
    EXPECT_THROW(resrv.set(IPv6Resrv::TYPE_NA, IOAddress("10.0.0.1"), 128),
                 isc::BadValue);
    // IPv6 multicast address is invalid for IPv6 reservation.
    EXPECT_THROW(resrv.set(IPv6Resrv::TYPE_NA, IOAddress("ff02::1:2"), 128),
                 isc::BadValue);
    // Prefix length greater than 128 is invalid.
    EXPECT_THROW(resrv.set(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1::"), 129),
                 isc::BadValue);
}

// This test checks that the equality operators work fine.
TEST(IPv6ResrvTest, equal) {
    EXPECT_TRUE(IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8::"), 64) ==
                IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8::"), 64));

    EXPECT_FALSE(IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8::"), 64) !=
                 IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8::"), 64));

    EXPECT_TRUE(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::1")) ==
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::1")));
    EXPECT_FALSE(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::1")) !=
                 IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::1")));

    EXPECT_FALSE(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::1")) ==
                 IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::2")));
    EXPECT_TRUE(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::1")) !=
                 IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::2")));

    EXPECT_FALSE(IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8::"), 64) ==
                 IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8::"), 48));
    EXPECT_TRUE(IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8::"), 64) !=
                IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8::"), 48));

    EXPECT_FALSE(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::1"), 128) ==
                 IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8::1"), 128));
    EXPECT_TRUE(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::1"), 128) !=
                IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8::1"), 128));

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

    EXPECT_FALSE(host->hasIPv6Reservation());

    // Add 4 reservations: 2 for NAs, 2 for PDs.
    ASSERT_NO_THROW(
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       IOAddress("2001:db8:1::cafe")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                       IOAddress("2001:db8:1:1::"), 64));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                       IOAddress("2001:db8:1:2::"), 64));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       IOAddress("2001:db8:1::1")));
    );

    EXPECT_TRUE(host->hasIPv6Reservation());

    // Check that reservations exist.
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                               IOAddress("2001:db8:1::cafe"))));
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                               IOAddress("2001:db8:1:1::"),
                                               64)));
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                               IOAddress("2001:db8:1:2::"),
                                               64)));
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                               IOAddress("2001:db8:1::1"))));

    // Get only NA reservations.
    IPv6ResrvRange addresses = host->getIPv6Reservations(IPv6Resrv::TYPE_NA);
    ASSERT_EQ(2, std::distance(addresses.first, addresses.second));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                            IOAddress("2001:db8:1::cafe")),
                                  addresses));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                            IOAddress("2001:db8:1::1")),
                                  addresses));


    // Get only PD reservations.
    IPv6ResrvRange prefixes = host->getIPv6Reservations(IPv6Resrv::TYPE_PD);
    ASSERT_EQ(2, std::distance(prefixes.first, prefixes.second));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                            IOAddress("2001:db8:1:1::"), 64),
                                  prefixes));
    EXPECT_TRUE(reservationExists(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                            IOAddress("2001:db8:1:2::"), 64),
                                  prefixes));
}

// This test checks that various modifiers may be used to replace the current
// values of the Host class.
TEST(HostTest, setValues) {
    boost::scoped_ptr<Host> host;
    ASSERT_NO_THROW(host.reset(new Host("01:02:03:04:05:06", "hw-address",
                                        SubnetID(1), SubnetID(2),
                                        IOAddress("192.0.2.3"),
                                        "some-host.example.org")));

    ASSERT_EQ(1, host->getIPv4SubnetID());
    ASSERT_EQ(2, host->getIPv6SubnetID());
    ASSERT_EQ("192.0.2.3", host->getIPv4Reservation().toText());
    ASSERT_EQ("some-host.example.org", host->getHostname());

    host->setIPv4SubnetID(SubnetID(123));
    host->setIPv6SubnetID(SubnetID(234));
    host->setIPv4Reservation(IOAddress("10.0.0.1"));
    host->setHostname("other-host.example.org");

    EXPECT_EQ(123, host->getIPv4SubnetID());
    EXPECT_EQ(234, host->getIPv6SubnetID());
    EXPECT_EQ("10.0.0.1", host->getIPv4Reservation().toText());
    EXPECT_EQ("other-host.example.org", host->getHostname());

    // Remove IPv4 reservation.
    host->removeIPv4Reservation();
    EXPECT_EQ(IOAddress::IPV4_ZERO_ADDRESS(), host->getIPv4Reservation());

    // An IPv6 address can't be used for IPv4 reservations.
    EXPECT_THROW(host->setIPv4Reservation(IOAddress("2001:db8:1::1")),
                 isc::BadValue);
    // Zero address can't be set, the removeIPv4Reservation should be
    // used intead.
    EXPECT_THROW(host->setIPv4Reservation(IOAddress::IPV4_ZERO_ADDRESS()),
                 isc::BadValue);
    // Broadcast address can't be set.
    EXPECT_THROW(host->setIPv4Reservation(IOAddress::IPV4_BCAST_ADDRESS()),
                 isc::BadValue);
}

// Test that Host constructors initialize client classes from string.
TEST(HostTest, clientClassesFromConstructor) {
    boost::scoped_ptr<Host> host;
    // Prepare the hardware address in binary format.
    const uint8_t hwaddr_data[] = {
        0xaa, 0xab, 0xca, 0xda, 0xbb, 0xee
    };

    // Try the "from binary" constructor.
    ASSERT_NO_THROW(host.reset(new Host(hwaddr_data,
                                        sizeof(hwaddr_data),
                                        Host::IDENT_HWADDR,
                                        SubnetID(1), SubnetID(2),
                                        IOAddress("192.0.2.3"),
                                        "somehost.example.org",
                                        "alpha, , beta",
                                        "gamma")));

    EXPECT_TRUE(host->getClientClasses4().contains("alpha"));
    EXPECT_TRUE(host->getClientClasses4().contains("beta"));
    EXPECT_FALSE(host->getClientClasses4().contains("gamma"));
    EXPECT_TRUE(host->getClientClasses6().contains("gamma"));
    EXPECT_FALSE(host->getClientClasses6().contains("alpha"));
    EXPECT_FALSE(host->getClientClasses6().contains("beta"));

    // Try the "from string" constructor.
    ASSERT_NO_THROW(host.reset(new Host("01:02:03:04:05:06", "hw-address",
                                        SubnetID(1), SubnetID(2),
                                        IOAddress("192.0.2.3"),
                                        "somehost.example.org",
                                        "alpha, beta, gamma",
                                        "beta, gamma")));

    EXPECT_TRUE(host->getClientClasses4().contains("alpha"));
    EXPECT_TRUE(host->getClientClasses4().contains("beta"));
    EXPECT_TRUE(host->getClientClasses4().contains("gamma"));
    EXPECT_FALSE(host->getClientClasses6().contains("alpha"));
    EXPECT_TRUE(host->getClientClasses6().contains("beta"));
    EXPECT_TRUE(host->getClientClasses6().contains("gamma"));
}

// Test that new client classes can be added for the Host.
TEST(HostTest, addClientClasses) {
    boost::scoped_ptr<Host> host;
    ASSERT_NO_THROW(host.reset(new Host("01:02:03:04:05:06", "hw-address",
                                        SubnetID(1), SubnetID(2),
                                        IOAddress("192.0.2.3"))));

    EXPECT_FALSE(host->getClientClasses4().contains("foo"));
    EXPECT_FALSE(host->getClientClasses6().contains("foo"));
    EXPECT_FALSE(host->getClientClasses4().contains("bar"));
    EXPECT_FALSE(host->getClientClasses6().contains("bar"));

    host->addClientClass4("foo");
    host->addClientClass6("bar");
    EXPECT_TRUE(host->getClientClasses4().contains("foo"));
    EXPECT_FALSE(host->getClientClasses6().contains("foo"));
    EXPECT_FALSE(host->getClientClasses4().contains("bar"));
    EXPECT_TRUE(host->getClientClasses6().contains("bar"));

    host->addClientClass4("bar");
    host->addClientClass6("foo");
    EXPECT_TRUE(host->getClientClasses4().contains("foo"));
    EXPECT_TRUE(host->getClientClasses6().contains("foo"));
    EXPECT_TRUE(host->getClientClasses4().contains("bar"));
    EXPECT_TRUE(host->getClientClasses6().contains("bar"));
}

TEST(HostTest, getIdentifierAsText) {
    Host host1("01:02:03:04:05:06", "hw-address",
               SubnetID(1), SubnetID(2),
               IOAddress("192.0.2.3"));
    EXPECT_EQ("hwaddr=01:02:03:04:05:06", host1.getIdentifierAsText());

    Host host2("0a:0b:0c:0d:0e:0f:ab:cd:ef", "duid",
               SubnetID(1), SubnetID(2),
               IOAddress("192.0.2.3"));
    EXPECT_EQ("duid=0a:0b:0c:0d:0e:0f:ab:cd:ef",
              host2.getIdentifierAsText());
}

// This test checks that Host object is correctly described in the
// textual format using the toText method.
TEST(HostTest, toText) {
    boost::scoped_ptr<Host> host;
    ASSERT_NO_THROW(host.reset(new Host("01:02:03:04:05:06", "hw-address",
                                        SubnetID(1), SubnetID(2),
                                        IOAddress("192.0.2.3"),
                                        "myhost.example.com")));

    // Add 4 reservations: 2 for NAs, 2 for PDs.
    ASSERT_NO_THROW(
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       IOAddress("2001:db8:1::cafe")));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                       IOAddress("2001:db8:1:1::"), 64));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                       IOAddress("2001:db8:1:2::"), 64));
        host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       IOAddress("2001:db8:1::1")));
    );

    // Make sure that the output is correct,
    EXPECT_EQ("hwaddr=01:02:03:04:05:06 ipv4_subnet_id=1 ipv6_subnet_id=2"
              " hostname=myhost.example.com"
              " ipv4_reservation=192.0.2.3"
              " ipv6_reservation0=2001:db8:1::cafe"
              " ipv6_reservation1=2001:db8:1::1"
              " ipv6_reservation2=2001:db8:1:1::/64"
              " ipv6_reservation3=2001:db8:1:2::/64",
              host->toText());

    // Reset some of the data and make sure that the output is affected.
    host->setHostname("");
    host->removeIPv4Reservation();
    host->setIPv4SubnetID(0);

    EXPECT_EQ("hwaddr=01:02:03:04:05:06 ipv6_subnet_id=2"
              " hostname=(empty) ipv4_reservation=(no)"
              " ipv6_reservation0=2001:db8:1::cafe"
              " ipv6_reservation1=2001:db8:1::1"
              " ipv6_reservation2=2001:db8:1:1::/64"
              " ipv6_reservation3=2001:db8:1:2::/64",
              host->toText());

    // Create host identified by DUID, instead of HWADDR, with a very
    // basic configuration.
    ASSERT_NO_THROW(host.reset(new Host("11:12:13:14:15", "duid",
                                        SubnetID(0), SubnetID(0),
                                        IOAddress::IPV4_ZERO_ADDRESS(),
                                        "myhost")));

    EXPECT_EQ("duid=11:12:13:14:15 hostname=myhost ipv4_reservation=(no)"
              " ipv6_reservations=(none)", host->toText());

    // Add some classes.
    host->addClientClass4("modem");
    host->addClientClass4("router");

    EXPECT_EQ("duid=11:12:13:14:15 hostname=myhost ipv4_reservation=(no)"
              " ipv6_reservations=(none)"
              " dhcp4_class0=modem dhcp4_class1=router",
              host->toText());

    host->addClientClass6("hub");
    host->addClientClass6("device");

    EXPECT_EQ("duid=11:12:13:14:15 hostname=myhost ipv4_reservation=(no)"
              " ipv6_reservations=(none)"
              " dhcp4_class0=modem dhcp4_class1=router"
              " dhcp6_class0=device dhcp6_class1=hub",
              host->toText());
}

} // end of anonymous namespace
