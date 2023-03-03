// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/subnet.h>
#include <exceptions/exceptions.h>

#include <boost/pointer_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>
#include <limits>

// don't import the entire boost namespace.  It will unexpectedly hide uint8_t
// for some systems.
using boost::scoped_ptr;

using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::util;

namespace {

TEST(Subnet4Test, constructor) {
    EXPECT_NO_THROW(Subnet4 subnet1(IOAddress("192.0.2.2"), 16,
                                    1, 2, 3, 10));

    EXPECT_THROW(Subnet4 subnet2(IOAddress("192.0.2.0"), 33, 1, 2, 3),
                BadValue); // invalid prefix length
    EXPECT_THROW(Subnet4 subnet3(IOAddress("2001:db8::1"), 24, 1, 2, 3),
                BadValue); // IPv6 addresses are not allowed in Subnet4
}

// This test verifies that the Subnet4 factory function creates a
// valid subnet instance.
TEST(Subnet4Test, create) {
    auto subnet = Subnet4::create(IOAddress("192.0.2.2"), 16,
                                  1, 2, 3, 10);
    ASSERT_TRUE(subnet);

    EXPECT_EQ("192.0.2.2/16", subnet->toText());
    EXPECT_EQ(1, subnet->getT1().get());
    EXPECT_EQ(2, subnet->getT2().get());
    EXPECT_EQ(3, subnet->getValid().get());
    EXPECT_EQ(10, subnet->getID());
}

// This test verifies the default values set for the subnets and verifies
// that the optional values are unspecified.
TEST(Subnet4Test, defaults) {
    Triplet<uint32_t> t1;
    Triplet<uint32_t> t2;
    Triplet<uint32_t> valid_lft;
    Subnet4 subnet(IOAddress("192.0.2.0"), 24, t1, t2, valid_lft);

    EXPECT_TRUE(subnet.getIface().unspecified());
    EXPECT_TRUE(subnet.getIface().empty());

    EXPECT_TRUE(subnet.getClientClass().unspecified());
    EXPECT_TRUE(subnet.getClientClass().empty());

    EXPECT_TRUE(subnet.getValid().unspecified());
    EXPECT_EQ(0, subnet.getValid().get());

    EXPECT_TRUE(subnet.getT1().unspecified());
    EXPECT_EQ(0, subnet.getT1().get());

    EXPECT_TRUE(subnet.getT2().unspecified());
    EXPECT_EQ(0, subnet.getT2().get());

    EXPECT_TRUE(subnet.getReservationsGlobal().unspecified());
    EXPECT_FALSE(subnet.getReservationsGlobal().get());

    EXPECT_TRUE(subnet.getReservationsInSubnet().unspecified());
    EXPECT_TRUE(subnet.getReservationsInSubnet().get());

    EXPECT_TRUE(subnet.getReservationsOutOfPool().unspecified());
    EXPECT_FALSE(subnet.getReservationsOutOfPool().get());

    EXPECT_TRUE(subnet.getCalculateTeeTimes().unspecified());
    EXPECT_FALSE(subnet.getCalculateTeeTimes().get());

    EXPECT_TRUE(subnet.getT1Percent().unspecified());
    EXPECT_EQ(0.0, subnet.getT1Percent().get());

    EXPECT_TRUE(subnet.getT2Percent().unspecified());
    EXPECT_EQ(0.0, subnet.getT2Percent().get());

    EXPECT_TRUE(subnet.getMatchClientId().unspecified());
    EXPECT_TRUE(subnet.getMatchClientId().get());

    EXPECT_TRUE(subnet.getAuthoritative().unspecified());
    EXPECT_FALSE(subnet.getAuthoritative().get());

    EXPECT_TRUE(subnet.getSiaddr().unspecified());
    EXPECT_TRUE(subnet.getSiaddr().get().isV4Zero());

    EXPECT_TRUE(subnet.getSname().unspecified());
    EXPECT_TRUE(subnet.getSname().empty());

    EXPECT_TRUE(subnet.getFilename().unspecified());
    EXPECT_TRUE(subnet.getFilename().empty());

    EXPECT_FALSE(subnet.get4o6().enabled());

    EXPECT_TRUE(subnet.get4o6().getIface4o6().unspecified());
    EXPECT_TRUE(subnet.get4o6().getIface4o6().empty());

    EXPECT_TRUE(subnet.get4o6().getSubnet4o6().unspecified());
    EXPECT_TRUE(subnet.get4o6().getSubnet4o6().get().first.isV6Zero());
    EXPECT_EQ(128, subnet.get4o6().getSubnet4o6().get().second);

    EXPECT_TRUE(subnet.getDdnsSendUpdates().unspecified());
    EXPECT_FALSE(subnet.getDdnsSendUpdates().get());

    EXPECT_TRUE(subnet.getDdnsOverrideNoUpdate().unspecified());
    EXPECT_FALSE(subnet.getDdnsOverrideNoUpdate().get());

    EXPECT_TRUE(subnet.getDdnsOverrideClientUpdate().unspecified());
    EXPECT_FALSE(subnet.getDdnsOverrideClientUpdate().get());

    EXPECT_TRUE(subnet.getDdnsReplaceClientNameMode().unspecified());
    EXPECT_EQ(D2ClientConfig::RCM_NEVER, subnet.getDdnsReplaceClientNameMode().get());

    EXPECT_TRUE(subnet.getDdnsGeneratedPrefix().unspecified());
    EXPECT_TRUE(subnet.getDdnsGeneratedPrefix().empty());

    EXPECT_TRUE(subnet.getDdnsQualifyingSuffix().unspecified());
    EXPECT_TRUE(subnet.getDdnsQualifyingSuffix().empty());

    EXPECT_TRUE(subnet.getHostnameCharSet().unspecified());
    EXPECT_TRUE(subnet.getHostnameCharSet().empty());

    EXPECT_TRUE(subnet.getHostnameCharReplacement().unspecified());
    EXPECT_TRUE(subnet.getHostnameCharReplacement().empty());

    EXPECT_TRUE(subnet.getDdnsUpdateOnRenew().unspecified());
    EXPECT_FALSE(subnet.getDdnsUpdateOnRenew().get());

    EXPECT_TRUE(subnet.getOfferLft().unspecified());
    EXPECT_EQ(0, subnet.getOfferLft().get());
}

// Checks that the subnet id can be either autogenerated or set to an
// arbitrary value through the constructor.
TEST(Subnet4Test, subnetID) {
    // Create subnet and don't specify id, so as it is autogenerated.
    auto subnet = Subnet4::create(IOAddress("192.0.2.0"), 24, 1000, 2000,
                                  3000);
    SubnetID id0 = subnet->getID();

    // Create another subnet and let id be autogenerated.
    subnet.reset(new Subnet4(IOAddress("192.0.3.0"), 24, 1000, 2000,
                             3000));
    SubnetID id1 = subnet->getID();

    // The autogenerated ids must not be equal.
    EXPECT_NE(id0, id1);

    // Create third subnet but this time select an arbitrary id. The id
    // we use the one of the second subnet. That way we ensure that the
    // subnet id we provide via constructor is used and it is not
    // autogenerated - if it was autogenerated we would get id other
    // than id1 because id1 has already been used.
    subnet = Subnet4::create(IOAddress("192.0.4.0"), 24, 1000, 2000, 3000, id1);
    EXPECT_EQ(id1, subnet->getID());
}

TEST(Subnet4Test, inRange) {
    Subnet4 subnet(IOAddress("192.0.2.1"), 24, 1000, 2000, 3000);

    EXPECT_EQ(1000, subnet.getT1().get());
    EXPECT_EQ(2000, subnet.getT2().get());
    EXPECT_EQ(3000, subnet.getValid().get());

    EXPECT_FALSE(subnet.hasRelays());

    EXPECT_FALSE(subnet.inRange(IOAddress("192.0.0.0")));
    EXPECT_TRUE(subnet.inRange(IOAddress("192.0.2.0")));
    EXPECT_TRUE(subnet.inRange(IOAddress("192.0.2.1")));
    EXPECT_TRUE(subnet.inRange(IOAddress("192.0.2.255")));
    EXPECT_FALSE(subnet.inRange(IOAddress("192.0.3.0")));
    EXPECT_FALSE(subnet.inRange(IOAddress("0.0.0.0")));
    EXPECT_FALSE(subnet.inRange(IOAddress("255.255.255.255")));
}

// Checks whether the relay list is empty by default
// and basic operations function
TEST(Subnet4Test, relay) {
    Subnet4 subnet(IOAddress("192.0.2.1"), 24, 1000, 2000, 3000);

    // Should be empty.
    EXPECT_FALSE(subnet.hasRelays());
    EXPECT_EQ(0, subnet.getRelayAddresses().size());

    // Matching should fail.
    EXPECT_FALSE(subnet.hasRelayAddress(IOAddress("192.0.123.45")));

    // Should be able to add them.
    subnet.addRelayAddress(IOAddress("192.0.123.45"));
    subnet.addRelayAddress(IOAddress("192.0.123.46"));

    // Should not be empty.
    EXPECT_TRUE(subnet.hasRelays());

    // Should be two in the list.
    EXPECT_EQ(2, subnet.getRelayAddresses().size());

    // Should be able to match them if they are there.
    EXPECT_TRUE(subnet.hasRelayAddress(IOAddress("192.0.123.45")));
    EXPECT_TRUE(subnet.hasRelayAddress(IOAddress("192.0.123.46")));

    // Should not match those that are not.
    EXPECT_FALSE(subnet.hasRelayAddress(IOAddress("192.0.123.47")));
}

// Checks whether siaddr field can be set and retrieved correctly.
TEST(Subnet4Test, siaddr) {
    Subnet4 subnet(IOAddress("192.0.2.1"), 24, 1000, 2000, 3000);

    // Check if the default is 0.0.0.0
    EXPECT_EQ("0.0.0.0", subnet.getSiaddr().get().toText());

    // Check that we can set it up
    EXPECT_NO_THROW(subnet.setSiaddr(IOAddress("1.2.3.4")));

    // Check that we can get it back
    EXPECT_EQ("1.2.3.4", subnet.getSiaddr().get().toText());

    // Check that only v4 addresses are supported
    EXPECT_THROW(subnet.setSiaddr(IOAddress("2001:db8::1")),
        BadValue);
}

// Checks whether server-hostname field can be set and retrieved correctly.
TEST(Subnet4Test, serverHostname) {
    Subnet4 subnet(IOAddress("192.0.2.1"), 24, 1000, 2000, 3000);

    // Check if the default is empty
    EXPECT_TRUE(subnet.getSname().empty());

    // Check that we can set it up
    EXPECT_NO_THROW(subnet.setSname("foobar"));

    // Check that we can get it back
    EXPECT_EQ("foobar", subnet.getSname().get());
}

// Checks whether boot-file-name field can be set and retrieved correctly.
TEST(Subnet4Test, bootFileName) {
    Subnet4 subnet(IOAddress("192.0.2.1"), 24, 1000, 2000, 3000);

    // Check if the default is empty
    EXPECT_TRUE(subnet.getFilename().empty());

    // Check that we can set it up
    EXPECT_NO_THROW(subnet.setFilename("foobar"));

    // Check that we can get it back
    EXPECT_EQ("foobar", subnet.getFilename().get());
}

// Checks if the match-client-id flag can be set and retrieved.
TEST(Subnet4Test, matchClientId) {
    Subnet4 subnet(IOAddress("192.0.2.1"), 24, 1000, 2000, 3000);

    // By default the flag should be set to true.
    EXPECT_TRUE(subnet.getMatchClientId());

    // Modify it and retrieve.
    subnet.setMatchClientId(false);
    EXPECT_FALSE(subnet.getMatchClientId());

    // Modify again.
    subnet.setMatchClientId(true);
    EXPECT_TRUE(subnet.getMatchClientId());
}

// Checks that it is possible to add and retrieve multiple pools.
TEST(Subnet4Test, pool4InSubnet4) {

    auto subnet = Subnet4::create(IOAddress("192.1.2.0"), 24, 1, 2, 3);

    PoolPtr pool1(new Pool4(IOAddress("192.1.2.0"), 25));
    PoolPtr pool2(new Pool4(IOAddress("192.1.2.128"), 26));
    PoolPtr pool3(new Pool4(IOAddress("192.1.2.192"), 30));
    pool3->allowClientClass("bar");
    PoolPtr pool4(new Pool4(IOAddress("192.1.2.200"), 30));

    // Add pools in reverse order to make sure that they get ordered by
    // first address.
    EXPECT_NO_THROW(subnet->addPool(pool4));

    // If there's only one pool, get that pool
    PoolPtr mypool = subnet->getAnyPool(Lease::TYPE_V4);
    EXPECT_EQ(mypool, pool4);

    EXPECT_NO_THROW(subnet->addPool(pool3));
    EXPECT_NO_THROW(subnet->addPool(pool2));
    EXPECT_NO_THROW(subnet->addPool(pool1));

    // If there are more than one pool and we didn't provide hint, we
    // should get the first pool
    EXPECT_NO_THROW(mypool = subnet->getAnyPool(Lease::TYPE_V4));

    EXPECT_EQ(mypool, pool1);

    // If we provide a hint, we should get a pool that this hint belongs to
    ASSERT_NO_THROW(mypool = subnet->getPool(Lease::TYPE_V4,
                                             IOAddress("192.1.2.201")));
    EXPECT_EQ(mypool, pool4);

    ASSERT_NO_THROW(mypool = subnet->getPool(Lease::TYPE_V4,
                                             IOAddress("192.1.2.129")));
    EXPECT_EQ(mypool, pool2);

    ASSERT_NO_THROW(mypool = subnet->getPool(Lease::TYPE_V4,
                                             IOAddress("192.1.2.64")));
    EXPECT_EQ(mypool, pool1);

    // Specify addresses which don't belong to any existing pools. The
    // third parameter prevents it from returning "any" available
    // pool if a good match is not found.
    ASSERT_NO_THROW(mypool = subnet->getPool(Lease::TYPE_V4,
                                             IOAddress("192.1.2.210"),
                                             false));
    EXPECT_FALSE(mypool);

    ASSERT_NO_THROW(mypool = subnet->getPool(Lease::TYPE_V4,
                                             IOAddress("192.1.1.254"),
                                             false));
    EXPECT_FALSE(mypool);

    // Now play with classes

    // This client does not belong to any class.
    isc::dhcp::ClientClasses no_class;

    // This client belongs to foo only.
    isc::dhcp::ClientClasses foo_class;
    foo_class.insert("foo");

    // This client belongs to bar only. I like that client.
    isc::dhcp::ClientClasses bar_class;
    bar_class.insert("bar");

    // This client belongs to foo, bar and baz classes.
    isc::dhcp::ClientClasses three_classes;
    three_classes.insert("foo");
    three_classes.insert("bar");
    three_classes.insert("baz");

    // If we provide a hint, we should get a pool that this hint belongs to
    ASSERT_NO_THROW(mypool = subnet->getPool(Lease::TYPE_V4, no_class,
                                             IOAddress("192.1.2.201")));
    EXPECT_EQ(mypool, pool4);

    ASSERT_NO_THROW(mypool = subnet->getPool(Lease::TYPE_V4, no_class,
                                             IOAddress("192.1.2.129")));
    EXPECT_EQ(mypool, pool2);

    ASSERT_NO_THROW(mypool = subnet->getPool(Lease::TYPE_V4, no_class,
                                             IOAddress("192.1.2.64")));
    EXPECT_EQ(mypool, pool1);

    // Specify addresses which don't belong to any existing pools.
    ASSERT_NO_THROW(mypool = subnet->getPool(Lease::TYPE_V4, three_classes,
                                             IOAddress("192.1.2.210")));
    EXPECT_FALSE(mypool);

    // Pool3 requires a member of bar
    ASSERT_NO_THROW(mypool = subnet->getPool(Lease::TYPE_V4, no_class,
                                             IOAddress("192.1.2.195")));
    EXPECT_FALSE(mypool);
    ASSERT_NO_THROW(mypool = subnet->getPool(Lease::TYPE_V4, foo_class,
                                             IOAddress("192.1.2.195")));
    EXPECT_FALSE(mypool);
    ASSERT_NO_THROW(mypool = subnet->getPool(Lease::TYPE_V4, bar_class,
                                             IOAddress("192.1.2.195")));
    EXPECT_EQ(mypool, pool3);
    ASSERT_NO_THROW(mypool = subnet->getPool(Lease::TYPE_V4, three_classes,
                                             IOAddress("192.1.2.195")));
    EXPECT_EQ(mypool, pool3);
}

// Check if it's possible to get specified number of possible leases for
// an IPv4 subnet.
TEST(Subnet4Test, getCapacity) {

    // There's one /24 pool.
    auto subnet = Subnet4::create(IOAddress("192.1.2.0"), 24, 1, 2, 3);

    // There are no pools defined, so the total number of available addrs is 0.
    EXPECT_EQ(0, subnet->getPoolCapacity(Lease::TYPE_V4));

    // Let's add a /25 pool. That's 128 addresses.
    PoolPtr pool1(new Pool4(IOAddress("192.1.2.0"), 25));
    subnet->addPool(pool1);
    EXPECT_EQ(128, subnet->getPoolCapacity(Lease::TYPE_V4));

    // Let's add another /26 pool. That's extra 64 addresses.
    PoolPtr pool2(new Pool4(IOAddress("192.1.2.128"), 26));
    subnet->addPool(pool2);
    EXPECT_EQ(192, subnet->getPoolCapacity(Lease::TYPE_V4));

    // Let's add a third pool /30. This one has 4 addresses.
    PoolPtr pool3(new Pool4(IOAddress("192.1.2.192"), 30));
    subnet->addPool(pool3);
    EXPECT_EQ(196, subnet->getPoolCapacity(Lease::TYPE_V4));

    // Let's add a forth pool /30. This one has 4 addresses.
    PoolPtr pool4(new Pool4(IOAddress("192.1.2.200"), 30));
    subnet->addPool(pool4);
    EXPECT_EQ(200, subnet->getPoolCapacity(Lease::TYPE_V4));

    // Now play with classes

    // This client does not belong to any class.
    isc::dhcp::ClientClasses no_class;

    // This client belongs to foo only.
    isc::dhcp::ClientClasses foo_class;
    foo_class.insert("foo");

    // This client belongs to bar only. I like that client.
    isc::dhcp::ClientClasses bar_class;
    bar_class.insert("bar");

    // This client belongs to foo, bar and baz classes.
    isc::dhcp::ClientClasses three_classes;
    three_classes.insert("foo");
    three_classes.insert("bar");
    three_classes.insert("baz");

    pool3->allowClientClass("bar");

    // Pool3 requires a member of bar
    EXPECT_EQ(196, subnet->getPoolCapacity(Lease::TYPE_V4, no_class));
    EXPECT_EQ(196, subnet->getPoolCapacity(Lease::TYPE_V4, foo_class));
    EXPECT_EQ(200, subnet->getPoolCapacity(Lease::TYPE_V4, bar_class));
    EXPECT_EQ(200, subnet->getPoolCapacity(Lease::TYPE_V4, three_classes));
}

// Checks that it is not allowed to add invalid pools.
TEST(Subnet4Test, pool4Checks) {

    auto subnet = Subnet4::create(IOAddress("192.0.2.0"), 8, 1, 2, 3);

    // this one is in subnet
    Pool4Ptr pool1(new Pool4(IOAddress("192.254.0.0"), 16));
    subnet->addPool(pool1);

    // this one is larger than the subnet!
    Pool4Ptr pool2(new Pool4(IOAddress("193.0.0.0"), 24));

    ASSERT_THROW(subnet->addPool(pool2), BadValue);

    // this one is totally out of blue
    Pool4Ptr pool3(new Pool4(IOAddress("1.2.0.0"), 16));
    ASSERT_THROW(subnet->addPool(pool3), BadValue);

    // This pool should be added just fine.
    Pool4Ptr pool4(new Pool4(IOAddress("192.0.2.10"),
                             IOAddress("192.0.2.20")));
    ASSERT_NO_THROW(subnet->addPool(pool4));

    // This one overlaps with the previous pool.
    Pool4Ptr pool5(new Pool4(IOAddress("192.0.2.1"),
                             IOAddress("192.0.2.15")));
    ASSERT_THROW(subnet->addPool(pool5), BadValue);

    // This one also overlaps.
    Pool4Ptr pool6(new Pool4(IOAddress("192.0.2.20"),
                             IOAddress("192.0.2.30")));
    ASSERT_THROW(subnet->addPool(pool6), BadValue);

    // This one "surrounds" the other pool.
    Pool4Ptr pool7(new Pool4(IOAddress("192.0.2.8"),
                             IOAddress("192.0.2.23")));
    ASSERT_THROW(subnet->addPool(pool7), BadValue);

    // This one does not overlap.
    Pool4Ptr pool8(new Pool4(IOAddress("192.0.2.30"),
                             IOAddress("192.0.2.40")));
    ASSERT_NO_THROW(subnet->addPool(pool8));

    // This one has a lower bound in the pool of 192.0.2.10-20.
    Pool4Ptr pool9(new Pool4(IOAddress("192.0.2.18"),
                             IOAddress("192.0.2.30")));
    ASSERT_THROW(subnet->addPool(pool9), BadValue);

    // This one has an upper bound in the pool of 192.0.2.30-40.
    Pool4Ptr pool10(new Pool4(IOAddress("192.0.2.25"),
                              IOAddress("192.0.2.32")));
    ASSERT_THROW(subnet->addPool(pool10), BadValue);

    // Add a pool with a single address.
    Pool4Ptr pool11(new Pool4(IOAddress("192.255.0.50"),
                              IOAddress("192.255.0.50")));
    ASSERT_NO_THROW(subnet->addPool(pool11));

    // Now we're going to add the same pool again. This is an interesting
    // case because we're checking if the code is properly using upper_bound
    // function, which returns a pool that has an address greater than the
    // specified one.
    ASSERT_THROW(subnet->addPool(pool11), BadValue);
}

// Tests whether Subnet4 object is able to store and process properly
// information about allowed client class (a single class).
TEST(Subnet4Test, clientClass) {
    // Create the V4 subnet.
    auto subnet = Subnet4::create(IOAddress("192.0.2.0"), 8, 1, 2, 3);

    // This client does not belong to any class.
    isc::dhcp::ClientClasses no_class;

    // This client belongs to foo only.
    isc::dhcp::ClientClasses foo_class;
    foo_class.insert("foo");

    // This client belongs to bar only. I like that client.
    isc::dhcp::ClientClasses bar_class;
    bar_class.insert("bar");

    // This client belongs to foo, bar and baz classes.
    isc::dhcp::ClientClasses three_classes;
    three_classes.insert("foo");
    three_classes.insert("bar");
    three_classes.insert("baz");

    // This client belongs to foo, bar, baz and network classes.
    isc::dhcp::ClientClasses four_classes;
    four_classes.insert("foo");
    four_classes.insert("bar");
    four_classes.insert("baz");
    four_classes.insert("network");

    // No class restrictions defined, any client should be supported
    EXPECT_TRUE(subnet->getClientClass().empty());
    EXPECT_TRUE(subnet->clientSupported(no_class));
    EXPECT_TRUE(subnet->clientSupported(foo_class));
    EXPECT_TRUE(subnet->clientSupported(bar_class));
    EXPECT_TRUE(subnet->clientSupported(three_classes));

    // Let's allow only clients belonging to "bar" class.
    subnet->allowClientClass("bar");
    EXPECT_EQ("bar", subnet->getClientClass().get());

    EXPECT_FALSE(subnet->clientSupported(no_class));
    EXPECT_FALSE(subnet->clientSupported(foo_class));
    EXPECT_TRUE(subnet->clientSupported(bar_class));
    EXPECT_TRUE(subnet->clientSupported(three_classes));

    // Add shared network which can only be selected when the client
    // class is "network".
    SharedNetwork4Ptr network(new SharedNetwork4("network"));
    network->allowClientClass("network");
    ASSERT_NO_THROW(network->add(subnet));

    // This time, if the client doesn't support network class,
    // the subnets from the shared network can't be selected.
    EXPECT_FALSE(subnet->clientSupported(bar_class));
    EXPECT_FALSE(subnet->clientSupported(three_classes));

    // If the classes include "network", the subnet is selected.
    EXPECT_TRUE(subnet->clientSupported(four_classes));
}

TEST(Subnet4Test, addInvalidOption) {
    // Create the V4 subnet.
    auto subnet = Subnet4::create(IOAddress("192.0.2.0"), 8, 1, 2, 3);

    // Create NULL pointer option. Attempt to add NULL option
    // should result in exception.
    OptionPtr option2;
    ASSERT_FALSE(option2);
    EXPECT_THROW(subnet->getCfgOption()->add(option2, false, false,
                                             DHCP4_OPTION_SPACE),
                 isc::BadValue);
}

// This test verifies that inRange() and inPool() methods work properly.
TEST(Subnet4Test, inRangeinPool) {
    auto subnet = Subnet4::create(IOAddress("192.0.0.0"), 8, 1, 2, 3);

    // this one is in subnet
    Pool4Ptr pool1(new Pool4(IOAddress("192.2.0.0"), 16));
    subnet->addPool(pool1);

    // 192.1.1.1 belongs to the subnet...
    EXPECT_TRUE(subnet->inRange(IOAddress("192.1.1.1")));

    // ... but it does not belong to any pool within
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_V4, IOAddress("192.1.1.1")));

    // the last address that is in range, but out of pool
    EXPECT_TRUE(subnet->inRange(IOAddress("192.1.255.255")));
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_V4, IOAddress("192.1.255.255")));

    // the first address that is in range, in pool
    EXPECT_TRUE(subnet->inRange(IOAddress("192.2.0.0")));
    EXPECT_TRUE(subnet->inPool(Lease::TYPE_V4, IOAddress("192.2.0.0")));

    // let's try something in the middle as well
    EXPECT_TRUE(subnet->inRange(IOAddress("192.2.3.4")));
    EXPECT_TRUE(subnet->inPool(Lease::TYPE_V4, IOAddress("192.2.3.4")));

    // the last address that is in range, in pool
    EXPECT_TRUE(subnet->inRange(IOAddress("192.2.255.255")));
    EXPECT_TRUE(subnet->inPool(Lease::TYPE_V4, IOAddress("192.2.255.255")));

    // the first address that is in range, but out of pool
    EXPECT_TRUE(subnet->inRange(IOAddress("192.3.0.0")));
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_V4, IOAddress("192.3.0.0")));

    // Add with classes
    pool1->allowClientClass("bar");
    EXPECT_TRUE(subnet->inPool(Lease::TYPE_V4, IOAddress("192.2.3.4")));

    // This client does not belong to any class.
    isc::dhcp::ClientClasses no_class;
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_V4, IOAddress("192.2.3.4"), no_class));

    // This client belongs to foo only
    isc::dhcp::ClientClasses foo_class;
    foo_class.insert("foo");
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_V4, IOAddress("192.2.3.4"), foo_class));

    // This client belongs to bar only. I like that client.
    isc::dhcp::ClientClasses bar_class;
    bar_class.insert("bar");
    EXPECT_TRUE(subnet->inPool(Lease::TYPE_V4, IOAddress("192.2.3.4"), bar_class));

    // This client belongs to foo, bar and baz classes.
    isc::dhcp::ClientClasses three_classes;
    three_classes.insert("foo");
    three_classes.insert("bar");
    three_classes.insert("baz");
    EXPECT_TRUE(subnet->inPool(Lease::TYPE_V4, IOAddress("192.2.3.4"), three_classes));
}

// This test checks if the toText() method returns text representation
TEST(Subnet4Test, toText) {
    auto subnet = Subnet4::create(IOAddress("192.0.2.0"), 24, 1, 2, 3);
    EXPECT_EQ("192.0.2.0/24", subnet->toText());
}

// This test verifies that the IPv4 prefix can be parsed into prefix/length pair.
TEST(Subnet4Test, parsePrefix) {
    std::pair<IOAddress, uint8_t> parsed =
        std::make_pair(IOAddress::IPV4_ZERO_ADDRESS(), 0);

    // Valid prefix.
    EXPECT_NO_THROW(parsed = Subnet4::parsePrefix("192.0.5.0/24"));
    EXPECT_EQ("192.0.5.0", parsed.first.toText());
    EXPECT_EQ(24, static_cast<int>(parsed.second));

    // Invalid IPv4 address.
    EXPECT_THROW(Subnet4::parsePrefix("192.0.2.322/24"), BadValue);

    // Invalid prefix length.
    EXPECT_THROW(Subnet4::parsePrefix("192.0.2.0/64"), BadValue);
    EXPECT_THROW(Subnet4::parsePrefix("192.0.2.0/0"), BadValue);

    // No IP address.
    EXPECT_THROW(Subnet4::parsePrefix(" /24"), BadValue);

    // No prefix length but slash present.
    EXPECT_THROW(Subnet4::parsePrefix("10.0.0.0/ "), BadValue);

    // No slash sign.
    EXPECT_THROW(Subnet4::parsePrefix("10.0.0.1"), BadValue);
   // IPv6 is not allowed here.
    EXPECT_THROW(Subnet4::parsePrefix("3000::/24"), BadValue);
}

// This test checks if the get() method returns proper parameters
TEST(Subnet4Test, get) {
    auto subnet = Subnet4::create(IOAddress("192.0.2.0"), 28, 1, 2, 3);
    EXPECT_EQ("192.0.2.0", subnet->get().first.toText());
    EXPECT_EQ(28, subnet->get().second);
}

// Checks if the V4 is the only allowed type for Pool4 and if getPool()
// is working properly.
TEST(Subnet4Test, PoolType) {

    auto subnet = Subnet4::create(IOAddress("192.2.0.0"), 16, 1, 2, 3);

    PoolPtr pool1(new Pool4(IOAddress("192.2.1.0"), 24));
    PoolPtr pool2(new Pool4(IOAddress("192.2.2.0"), 24));
    PoolPtr pool3(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:3::"), 64));
    PoolPtr pool4(new Pool6(Lease::TYPE_TA, IOAddress("2001:db8:1:4::"), 64));
    PoolPtr pool5(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1:1::"), 64));

    // There should be no pools of any type by default
    EXPECT_EQ(PoolPtr(), subnet->getAnyPool(Lease::TYPE_V4));

    // It should not be possible to ask for V6 pools in Subnet4
    EXPECT_THROW(subnet->getAnyPool(Lease::TYPE_NA), BadValue);
    EXPECT_THROW(subnet->getAnyPool(Lease::TYPE_TA), BadValue);
    EXPECT_THROW(subnet->getAnyPool(Lease::TYPE_PD), BadValue);

    // Let's add a single V4 pool and check that it can be retrieved
    EXPECT_NO_THROW(subnet->addPool(pool1));

    // If there's only one IA pool, get that pool (without and with hint)
    EXPECT_EQ(pool1, subnet->getAnyPool(Lease::TYPE_V4));
    EXPECT_EQ(pool1, subnet->getPool(Lease::TYPE_V4, IOAddress("192.0.1.167")));

    // Let's add additional V4 pool
    EXPECT_NO_THROW(subnet->addPool(pool2));

    // Try without hints
    EXPECT_EQ(pool1, subnet->getAnyPool(Lease::TYPE_V4));

    // Try with valid hints
    EXPECT_EQ(pool1, subnet->getPool(Lease::TYPE_V4, IOAddress("192.2.1.5")));
    EXPECT_EQ(pool2, subnet->getPool(Lease::TYPE_V4, IOAddress("192.2.2.254")));

    // Try with bogus hints (hints should be ignored)
    EXPECT_EQ(pool1, subnet->getPool(Lease::TYPE_V4, IOAddress("10.1.1.1")));

    // Trying to add Pool6 to Subnet4 is a big no,no!
    EXPECT_THROW(subnet->addPool(pool3), BadValue);
    EXPECT_THROW(subnet->addPool(pool4), BadValue);
    EXPECT_THROW(subnet->addPool(pool5), BadValue);
}

// Tests if correct value of server identifier is returned when getServerId is
// called.
TEST(Subnet4Test, getServerId) {
    // Initially, the subnet has no server identifier.
    Subnet4 subnet(IOAddress("192.2.0.0"), 16, 1, 2, 3);
    EXPECT_TRUE(subnet.getServerId().isV4Zero());

    // Add server identifier.
    OptionDefinitionPtr option_def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                                           DHO_DHCP_SERVER_IDENTIFIER);
    OptionCustomPtr option_server_id(new OptionCustom(*option_def, Option::V4));
    option_server_id->writeAddress(IOAddress("1.2.3.4"));

    CfgOptionPtr cfg_option = subnet.getCfgOption();
    cfg_option->add(option_server_id, false, false, DHCP4_OPTION_SPACE);

    // Verify that the server identifier returned by the Subnet4 object is
    // correct.
    OptionBuffer server_id_buf = { 1, 2, 3, 4 };
    EXPECT_EQ("1.2.3.4", subnet.getServerId().toText());
}

// Tests for Subnet6

TEST(Subnet6Test, constructor) {

    EXPECT_NO_THROW(Subnet6 subnet1(IOAddress("2001:db8:1::"), 64,
                                    1, 2, 3, 4));

    EXPECT_THROW(Subnet6 subnet2(IOAddress("2001:db8:1::"), 129, 1, 2, 3, 4),
                BadValue); // invalid prefix length
    EXPECT_THROW(Subnet6 subnet3(IOAddress("192.168.0.0"), 32, 1, 2, 3, 4),
                BadValue); // IPv4 addresses are not allowed in Subnet6
}

// This test verifies that the Subnet6 factory function creates a
// valid subnet instance.
TEST(Subnet6Test, create) {
    auto subnet = Subnet6::create(IOAddress("2001:db8:1::"), 64,
                                  1, 2, 3, 4, 10);
    ASSERT_TRUE(subnet);

    EXPECT_EQ("2001:db8:1::/64", subnet->toText());
    EXPECT_EQ(1, subnet->getT1().get());
    EXPECT_EQ(2, subnet->getT2().get());
    EXPECT_EQ(3, subnet->getPreferred().get());
    EXPECT_EQ(4, subnet->getValid().get());
    EXPECT_EQ(10, subnet->getID());
}

// This test verifies the default values set for the shared
// networks and verifies that the optional values are unspecified.
TEST(SharedNetwork6Test, defaults) {
    Triplet<uint32_t> t1;
    Triplet<uint32_t> t2;
    Triplet<uint32_t> preferred_lft;
    Triplet<uint32_t> valid_lft;
    Subnet6 subnet(IOAddress("2001:db8:1::"), 64, t1, t2, preferred_lft,
                   valid_lft);

    EXPECT_TRUE(subnet.getIface().unspecified());
    EXPECT_TRUE(subnet.getIface().empty());

    EXPECT_TRUE(subnet.getClientClass().unspecified());
    EXPECT_TRUE(subnet.getClientClass().empty());

    EXPECT_TRUE(subnet.getValid().unspecified());
    EXPECT_EQ(0, subnet.getValid().get());

    EXPECT_TRUE(subnet.getT1().unspecified());
    EXPECT_EQ(0, subnet.getT1().get());

    EXPECT_TRUE(subnet.getT2().unspecified());
    EXPECT_EQ(0, subnet.getT2().get());

    EXPECT_TRUE(subnet.getReservationsGlobal().unspecified());
    EXPECT_FALSE(subnet.getReservationsGlobal().get());

    EXPECT_TRUE(subnet.getReservationsInSubnet().unspecified());
    EXPECT_TRUE(subnet.getReservationsInSubnet().get());

    EXPECT_TRUE(subnet.getReservationsOutOfPool().unspecified());
    EXPECT_FALSE(subnet.getReservationsOutOfPool().get());

    EXPECT_TRUE(subnet.getCalculateTeeTimes().unspecified());
    EXPECT_FALSE(subnet.getCalculateTeeTimes().get());

    EXPECT_TRUE(subnet.getT1Percent().unspecified());
    EXPECT_EQ(0.0, subnet.getT1Percent().get());

    EXPECT_TRUE(subnet.getT2Percent().unspecified());
    EXPECT_EQ(0.0, subnet.getT2Percent().get());

    EXPECT_TRUE(subnet.getPreferred().unspecified());
    EXPECT_EQ(0, subnet.getPreferred().get());

    EXPECT_TRUE(subnet.getRapidCommit().unspecified());
    EXPECT_FALSE(subnet.getRapidCommit().get());

    EXPECT_TRUE(subnet.getDdnsSendUpdates().unspecified());
    EXPECT_FALSE(subnet.getDdnsSendUpdates().get());

    EXPECT_TRUE(subnet.getDdnsOverrideNoUpdate().unspecified());
    EXPECT_FALSE(subnet.getDdnsOverrideNoUpdate().get());

    EXPECT_TRUE(subnet.getDdnsOverrideClientUpdate().unspecified());
    EXPECT_FALSE(subnet.getDdnsOverrideClientUpdate().get());

    EXPECT_TRUE(subnet.getDdnsReplaceClientNameMode().unspecified());
    EXPECT_EQ(D2ClientConfig::RCM_NEVER, subnet.getDdnsReplaceClientNameMode().get());

    EXPECT_TRUE(subnet.getDdnsGeneratedPrefix().unspecified());
    EXPECT_TRUE(subnet.getDdnsGeneratedPrefix().empty());

    EXPECT_TRUE(subnet.getDdnsQualifyingSuffix().unspecified());
    EXPECT_TRUE(subnet.getDdnsQualifyingSuffix().empty());

    EXPECT_TRUE(subnet.getHostnameCharSet().unspecified());
    EXPECT_TRUE(subnet.getHostnameCharSet().empty());

    EXPECT_TRUE(subnet.getHostnameCharReplacement().unspecified());
    EXPECT_TRUE(subnet.getHostnameCharReplacement().empty());

    EXPECT_TRUE(subnet.getDdnsUpdateOnRenew().unspecified());
    EXPECT_FALSE(subnet.getDdnsUpdateOnRenew().get());
}

// Checks that the subnet id can be either autogenerated or set to an
// arbitrary value through the constructor.
TEST(Subnet6Test, subnetID) {
    // Create subnet and don't specify id, so as it is autogenerated.
    auto subnet = Subnet6::create(IOAddress("2001:db8:1::"), 64, 1000, 2000,
                                  3000, 4000);
    SubnetID id0 = subnet->getID();

    // Create another subnet and let id be autogenerated.
    subnet.reset(new Subnet6(IOAddress("2001:db8:2::"), 64, 1000, 2000,
                             3000, 4000));
    SubnetID id1 = subnet->getID();

    // The autogenerated ids must not be equal.
    EXPECT_NE(id0, id1);

    // Create third subnet but this time select an arbitrary id. The id
    // we use us the one of second subnet. That way we ensure that the
    // subnet id we provide via constructor is used and it is not
    // autogenerated - if it was autogenerated we would get id other
    // than id1 because id1 has already been used.
    subnet.reset(new Subnet6(IOAddress("2001:db8:3::"), 64, 1000, 2000,
                             3000, 4000, id1));
    EXPECT_EQ(id1, subnet->getID());
}

TEST(Subnet6Test, inRange) {
    Subnet6 subnet(IOAddress("2001:db8:1::"), 64, 1000, 2000, 3000, 4000);

    EXPECT_EQ(1000, subnet.getT1().get());
    EXPECT_EQ(2000, subnet.getT2().get());
    EXPECT_EQ(3000, subnet.getPreferred().get());
    EXPECT_EQ(4000, subnet.getValid().get());

    EXPECT_FALSE(subnet.inRange(IOAddress("2001:db8:0:ffff:ffff:ffff:ffff:ffff")));
    EXPECT_TRUE(subnet.inRange(IOAddress("2001:db8:1::0")));
    EXPECT_TRUE(subnet.inRange(IOAddress("2001:db8:1::1")));
    EXPECT_TRUE(subnet.inRange(IOAddress("2001:db8:1::ffff:ffff:ffff:ffff")));
    EXPECT_FALSE(subnet.inRange(IOAddress("2001:db8:1:1::")));
    EXPECT_FALSE(subnet.inRange(IOAddress("::")));
}

// Checks whether the relay list is empty by default
// and basic operations function
TEST(Subnet6Test, relay) {
    Subnet6 subnet(IOAddress("2001:db8:1::"), 64, 1000, 2000, 3000, 4000);

    // Should be empty.
    EXPECT_FALSE(subnet.hasRelays());
    EXPECT_EQ(0, subnet.getRelayAddresses().size());

    // Matching should fail.
    EXPECT_FALSE(subnet.hasRelayAddress(IOAddress("2001:ffff::45")));

    // Should be able to add them.
    subnet.addRelayAddress(IOAddress("2001:ffff::45"));
    subnet.addRelayAddress(IOAddress("2001:ffff::46"));

    // Should not be empty.
    EXPECT_TRUE(subnet.hasRelays());

    // Should be two in the list.
    EXPECT_EQ(2, subnet.getRelayAddresses().size());

    // Should be able to match them if they are there.
    EXPECT_TRUE(subnet.hasRelayAddress(IOAddress("2001:ffff::45")));
    EXPECT_TRUE(subnet.hasRelayAddress(IOAddress("2001:ffff::46")));

    // Should not match those that are not.
    EXPECT_FALSE(subnet.hasRelayAddress(IOAddress("2001:ffff::47")));
}

// Test checks whether the number of addresses available in the pools are
// calculated properly.
TEST(Subnet6Test, Pool6getCapacity) {

    auto subnet = Subnet6::create(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4);

    // There's 2^16 = 65536 addresses in this one.
    PoolPtr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:1::"), 112));

    // There's 2^32 = 4294967296 addresses in each of those.
    PoolPtr pool2(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:2::"), 96));
    PoolPtr pool3(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:3::"), 96));

    EXPECT_EQ(0, subnet->getPoolCapacity(Lease::TYPE_NA));
    EXPECT_EQ(0, subnet->getPoolCapacity(Lease::TYPE_TA));
    EXPECT_EQ(0, subnet->getPoolCapacity(Lease::TYPE_PD));

    subnet->addPool(pool1);
    EXPECT_EQ(65536, subnet->getPoolCapacity(Lease::TYPE_NA));

    subnet->addPool(pool2);
    EXPECT_EQ(uint64_t(4294967296ull + 65536), subnet->getPoolCapacity(Lease::TYPE_NA));

    subnet->addPool(pool3);
    EXPECT_EQ(uint64_t(4294967296ull + 4294967296ull + 65536),
              subnet->getPoolCapacity(Lease::TYPE_NA));

    // Now play with classes

    // This client does not belong to any class.
    isc::dhcp::ClientClasses no_class;

    // This client belongs to foo only.
    isc::dhcp::ClientClasses foo_class;
    foo_class.insert("foo");

    // This client belongs to bar only. I like that client.
    isc::dhcp::ClientClasses bar_class;
    bar_class.insert("bar");

    // This client belongs to foo, bar and baz classes.
    isc::dhcp::ClientClasses three_classes;
    three_classes.insert("foo");
    three_classes.insert("bar");
    three_classes.insert("baz");

    pool3->allowClientClass("bar");

    // Pool3 requires a member of bar
    EXPECT_EQ(uint64_t(4294967296ull + 65536),
              subnet->getPoolCapacity(Lease::TYPE_NA, no_class));
    EXPECT_EQ(uint64_t(4294967296ull + 65536),
              subnet->getPoolCapacity(Lease::TYPE_NA, foo_class));
    EXPECT_EQ(uint64_t(4294967296ull + 4294967296ull + 65536),
              subnet->getPoolCapacity(Lease::TYPE_NA, bar_class));
    EXPECT_EQ(uint64_t(4294967296ull + 4294967296ull + 65536),
              subnet->getPoolCapacity(Lease::TYPE_NA, three_classes));
}

// Test checks whether the number of prefixes available in the pools are
// calculated properly.
TEST(Subnet6Test, Pool6PdgetPoolCapacity) {

    auto subnet = Subnet6::create(IOAddress("2001:db8::"), 32, 1, 2, 3, 4);

    // There's 2^16 = 65536 addresses in this one.
    PoolPtr pool1(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1::"), 48, 64));

    // There's 2^32 = 4294967296 addresses in each of those.
    PoolPtr pool2(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:2::"), 48, 80));
    PoolPtr pool3(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:3::"), 48, 80));

    EXPECT_EQ(0, subnet->getPoolCapacity(Lease::TYPE_NA));
    EXPECT_EQ(0, subnet->getPoolCapacity(Lease::TYPE_TA));
    EXPECT_EQ(0, subnet->getPoolCapacity(Lease::TYPE_PD));

    subnet->addPool(pool1);
    EXPECT_EQ(65536, subnet->getPoolCapacity(Lease::TYPE_PD));

    subnet->addPool(pool2);
    EXPECT_EQ(uint64_t(4294967296ull + 65536), subnet->getPoolCapacity(Lease::TYPE_PD));

    subnet->addPool(pool3);
    EXPECT_EQ(uint64_t(4294967296ull + 4294967296ull + 65536),
              subnet->getPoolCapacity(Lease::TYPE_PD));

    // This is 2^64.
    PoolPtr pool4(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:4::"), 48, 112));
    subnet->addPool(pool4);
    EXPECT_EQ(std::numeric_limits<uint64_t>::max(),
              subnet->getPoolCapacity(Lease::TYPE_PD));

    PoolPtr pool5(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:5::"), 48, 112));
    subnet->addPool(pool5);
    EXPECT_EQ(std::numeric_limits<uint64_t>::max(),
              subnet->getPoolCapacity(Lease::TYPE_PD));
}

TEST(Subnet6Test, Pool6InSubnet6) {

    auto subnet = Subnet6::create(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4);

    PoolPtr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:1::"), 64));
    PoolPtr pool2(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:2::"), 64));
    PoolPtr pool3(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:3::"), 64));

    subnet->addPool(pool1);

    // If there's only one pool, get that pool
    PoolPtr mypool = subnet->getAnyPool(Lease::TYPE_NA);
    EXPECT_EQ(mypool, pool1);

    subnet->addPool(pool2);
    subnet->addPool(pool3);

    // If there are more than one pool and we didn't provide hint, we
    // should get the first pool
    mypool = subnet->getAnyPool(Lease::TYPE_NA);

    EXPECT_EQ(mypool, pool1);

    // If we provide a hint, we should get a pool that this hint belongs to
    mypool = subnet->getPool(Lease::TYPE_NA, IOAddress("2001:db8:1:3::dead:beef"));

    EXPECT_EQ(mypool, pool3);

    // Now play with classes

    // This client does not belong to any class.
    isc::dhcp::ClientClasses no_class;

    // This client belongs to foo only.
    isc::dhcp::ClientClasses foo_class;
    foo_class.insert("foo");

    // This client belongs to bar only. I like that client.
    isc::dhcp::ClientClasses bar_class;
    bar_class.insert("bar");

    // This client belongs to foo, bar and baz classes.
    isc::dhcp::ClientClasses three_classes;
    three_classes.insert("foo");
    three_classes.insert("bar");
    three_classes.insert("baz");

    pool3->allowClientClass("bar");

    // Pool3 requires a member of bar
    mypool = subnet->getPool(Lease::TYPE_NA, no_class,
                             IOAddress("2001:db8:1:3::dead:beef"));
    EXPECT_FALSE(mypool);
    mypool = subnet->getPool(Lease::TYPE_NA, foo_class,
                             IOAddress("2001:db8:1:3::dead:beef"));
    EXPECT_FALSE(mypool);
    mypool = subnet->getPool(Lease::TYPE_NA, bar_class,
                             IOAddress("2001:db8:1:3::dead:beef"));
    EXPECT_EQ(mypool, pool3);
    mypool = subnet->getPool(Lease::TYPE_NA, three_classes,
                             IOAddress("2001:db8:1:3::dead:beef"));
    EXPECT_EQ(mypool, pool3);
}

// Check if Subnet6 supports different types of pools properly.
TEST(Subnet6Test, poolTypes) {

    auto subnet = Subnet6::create(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4);

    PoolPtr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:1::"), 64));
    PoolPtr pool2(new Pool6(Lease::TYPE_TA, IOAddress("2001:db8:1:2::"), 64));
    PoolPtr pool3(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1:3::"), 64));
    PoolPtr pool4(new Pool6(Lease::TYPE_PD, IOAddress("3000:1::"), 64));

    PoolPtr pool5(new Pool4(IOAddress("192.0.2.0"), 24));

    // There should be no pools of any type by default
    EXPECT_EQ(PoolPtr(), subnet->getAnyPool(Lease::TYPE_NA));
    EXPECT_EQ(PoolPtr(), subnet->getAnyPool(Lease::TYPE_TA));
    EXPECT_EQ(PoolPtr(), subnet->getAnyPool(Lease::TYPE_PD));

    // Trying to get IPv4 pool from Subnet6 is not allowed
    EXPECT_THROW(subnet->getAnyPool(Lease::TYPE_V4), BadValue);

    // Let's add a single IA pool and check that it can be retrieved
    EXPECT_NO_THROW(subnet->addPool(pool1));

    // If there's only one IA pool, get that pool
    EXPECT_EQ(pool1, subnet->getAnyPool(Lease::TYPE_NA));
    EXPECT_EQ(pool1, subnet->getPool(Lease::TYPE_NA, IOAddress("2001:db8:1:1::1")));

    // Check if pools of different type are not returned
    EXPECT_EQ(PoolPtr(), subnet->getAnyPool(Lease::TYPE_TA));
    EXPECT_EQ(PoolPtr(), subnet->getAnyPool(Lease::TYPE_PD));

    // We ask with good hints, but wrong types, should return nothing
    EXPECT_EQ(PoolPtr(), subnet->getPool(Lease::TYPE_PD, IOAddress("2001:db8:1:2::1")));
    EXPECT_EQ(PoolPtr(), subnet->getPool(Lease::TYPE_TA, IOAddress("2001:db8:1:3::1")));

    // Let's add TA and PD pools
    EXPECT_NO_THROW(subnet->addPool(pool2));
    EXPECT_NO_THROW(subnet->addPool(pool3));

    // Try without hints
    EXPECT_EQ(pool1, subnet->getAnyPool(Lease::TYPE_NA));
    EXPECT_EQ(pool2, subnet->getAnyPool(Lease::TYPE_TA));
    EXPECT_EQ(pool3, subnet->getAnyPool(Lease::TYPE_PD));

    // Try with valid hints
    EXPECT_EQ(pool1, subnet->getPool(Lease::TYPE_NA, IOAddress("2001:db8:1:1::1")));
    EXPECT_EQ(pool2, subnet->getPool(Lease::TYPE_TA, IOAddress("2001:db8:1:2::1")));
    EXPECT_EQ(pool3, subnet->getPool(Lease::TYPE_PD, IOAddress("2001:db8:1:3::1")));

    // Try with bogus hints (hints should be ignored)
    EXPECT_EQ(pool1, subnet->getPool(Lease::TYPE_NA, IOAddress("2001:db8:1:7::1")));
    EXPECT_EQ(pool2, subnet->getPool(Lease::TYPE_TA, IOAddress("2001:db8:1:7::1")));
    EXPECT_EQ(pool3, subnet->getPool(Lease::TYPE_PD, IOAddress("2001:db8:1:7::1")));

    // Let's add a second PD pool
    EXPECT_NO_THROW(subnet->addPool(pool4));

    // Without hints, it should return the first pool
    EXPECT_EQ(pool3, subnet->getAnyPool(Lease::TYPE_PD));

    // With valid hint, it should return that hint
    EXPECT_EQ(pool3, subnet->getPool(Lease::TYPE_PD, IOAddress("2001:db8:1:3::1")));
    EXPECT_EQ(pool4, subnet->getPool(Lease::TYPE_PD, IOAddress("3000:1::")));

    // With invalid hint, it should return the first pool
    EXPECT_EQ(pool3, subnet->getPool(Lease::TYPE_PD, IOAddress("2001:db8::123")));

    // Adding Pool4 to Subnet6 is a big no, no!
    EXPECT_THROW(subnet->addPool(pool5), BadValue);
}

// Tests whether Subnet6 object is able to store and process properly
// information about allowed client class (a single class).
TEST(Subnet6Test, clientClass) {
    // Create the V6 subnet.
    auto subnet = Subnet6::create(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4);

    // This client does not belong to any class.
    isc::dhcp::ClientClasses no_class;

    // This client belongs to foo only.
    isc::dhcp::ClientClasses foo_class;
    foo_class.insert("foo");

    // This client belongs to bar only. I like that client.
    isc::dhcp::ClientClasses bar_class;
    bar_class.insert("bar");

    // This client belongs to foo, bar and baz classes.
    isc::dhcp::ClientClasses three_classes;
    three_classes.insert("foo");
    three_classes.insert("bar");
    three_classes.insert("baz");

    // This client belongs to foo, bar, baz and network classes.
    isc::dhcp::ClientClasses four_classes;
    four_classes.insert("foo");
    four_classes.insert("bar");
    four_classes.insert("baz");
    four_classes.insert("network");

    // No class restrictions defined, any client should be supported
    EXPECT_TRUE(subnet->getClientClass().empty());
    EXPECT_TRUE(subnet->clientSupported(no_class));
    EXPECT_TRUE(subnet->clientSupported(foo_class));
    EXPECT_TRUE(subnet->clientSupported(bar_class));
    EXPECT_TRUE(subnet->clientSupported(three_classes));

    // Let's allow only clients belonging to "bar" class.
    subnet->allowClientClass("bar");
    EXPECT_EQ("bar", subnet->getClientClass().get());

    EXPECT_FALSE(subnet->clientSupported(no_class));
    EXPECT_FALSE(subnet->clientSupported(foo_class));
    EXPECT_TRUE(subnet->clientSupported(bar_class));
    EXPECT_TRUE(subnet->clientSupported(three_classes));

    // Add shared network which can only be selected when the client
    // class is "network".
    SharedNetwork6Ptr network(new SharedNetwork6("network"));
    network->allowClientClass("network");
    ASSERT_NO_THROW(network->add(subnet));

    // This time, if the client doesn't support network class,
    // the subnets from the shared network can't be selected.
    EXPECT_FALSE(subnet->clientSupported(bar_class));
    EXPECT_FALSE(subnet->clientSupported(three_classes));

    // If the classes include "network", the subnet is selected.
    EXPECT_TRUE(subnet->clientSupported(four_classes));
}

// Checks that it is not allowed to add invalid pools.
TEST(Subnet6Test, pool6Checks) {

    auto subnet = Subnet6::create(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4);

    // this one is in subnet
    Pool6Ptr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:1::"), 64));
    ASSERT_NO_THROW(subnet->addPool(pool1));

    // this one is larger than the subnet!
    Pool6Ptr pool2(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8::"), 48));

    ASSERT_THROW(subnet->addPool(pool2), BadValue);

    // this one is totally out of blue
    Pool6Ptr pool3(new Pool6(Lease::TYPE_NA, IOAddress("3000::"), 16));
    ASSERT_THROW(subnet->addPool(pool3), BadValue);

    Pool6Ptr pool4(new Pool6(Lease::TYPE_NA, IOAddress("4001:db8:1::"), 80));
    ASSERT_THROW(subnet->addPool(pool4), BadValue);

    // This pool should be added just fine.
    Pool6Ptr pool5(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:2::100"),
                             IOAddress("2001:db8:1:2::200")));
    ASSERT_NO_THROW(subnet->addPool(pool5));

    // This pool overlaps with a previously added pool.
    Pool6Ptr pool6(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:2::1"),
                             IOAddress("2001:db8:1:2::150")));
    ASSERT_THROW(subnet->addPool(pool6), BadValue);

    // This pool also overlaps
    Pool6Ptr pool7(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:2::150"),
                             IOAddress("2001:db8:1:2::300")));
    ASSERT_THROW(subnet->addPool(pool7), BadValue);

    // This one "surrounds" the other pool.
    Pool6Ptr pool8(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:2::50"),
                             IOAddress("2001:db8:1:2::250")));
    ASSERT_THROW(subnet->addPool(pool8), BadValue);

    // This one does not overlap.
    Pool6Ptr pool9(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:2::300"),
                             IOAddress("2001:db8:1:2::400")));
    ASSERT_NO_THROW(subnet->addPool(pool9));

    // This one has a lower bound in the pool of 2001:db8:1::100-200.
    Pool6Ptr pool10(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:2::200"),
                              IOAddress("2001:db8:1:2::225")));
    ASSERT_THROW(subnet->addPool(pool10), BadValue);

    // This one has an upper bound in the pool of 2001:db8:1::300-400.
    Pool6Ptr pool11(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:2::250"),
                              IOAddress("2001:db8:1:2::300")));
    ASSERT_THROW(subnet->addPool(pool11), BadValue);

    // Add a pool with a single address.
    Pool6Ptr pool12(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1:3::250"),
                              IOAddress("2001:db8:1:3::250")));
    ASSERT_NO_THROW(subnet->addPool(pool12));

    // Now we're going to add the same pool again. This is an interesting
    // case because we're checking if the code is properly using upper_bound
    // function, which returns a pool that has an address greater than the
    // specified one.
    ASSERT_THROW(subnet->addPool(pool12), BadValue);

    // Prefix pool overlaps with the pool1. We can't hand out addresses and
    // prefixes from the same range.
    Pool6Ptr pool13(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1:1:2::"),
                              80, 96));
    ASSERT_THROW(subnet->addPool(pool13), BadValue);
}

TEST(Subnet6Test, addOptions) {
    // Create as subnet to add options to it.
    auto subnet = Subnet6::create(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4);

    // Differentiate options by their codes (100-109)
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(subnet->getCfgOption()->add(option, false, false,
                                                    DHCP6_OPTION_SPACE));
    }

    // Add 7 options to another option space. The option codes partially overlap
    // with option codes that we have added to dhcp6 option space.
    for (uint16_t code = 105; code < 112; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(subnet->getCfgOption()->add(option, false, false,
                                                    "isc"));
    }

    // Get options from the Subnet and check if all 10 are there.
    OptionContainerPtr options = subnet->getCfgOption()->getAll(DHCP6_OPTION_SPACE);
    ASSERT_TRUE(options);
    ASSERT_EQ(10, options->size());

    // Validate codes of options added to dhcp6 option space.
    uint16_t expected_code = 100;
    for (OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option_);
        EXPECT_EQ(expected_code, option_desc->option_->getType());
        ++expected_code;
    }

    options = subnet->getCfgOption()->getAll("isc");
    ASSERT_TRUE(options);
    ASSERT_EQ(7, options->size());

    // Validate codes of options added to isc option space.
    expected_code = 105;
    for (OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option_);
        EXPECT_EQ(expected_code, option_desc->option_->getType());
        ++expected_code;
    }

    // Try to get options from a non-existing option space.
    options = subnet->getCfgOption()->getAll("abcd");
    ASSERT_TRUE(options);
    EXPECT_TRUE(options->empty());
}

TEST(Subnet6Test, addNonUniqueOptions) {
    // Create as subnet to add options to it.
    auto subnet = Subnet6::create(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4);

    // Create a set of options with non-unique codes.
    for (int i = 0;  i < 2; ++i) {
        // In the inner loop we create options with unique codes (100-109).
        for (uint16_t code = 100; code < 110; ++code) {
            OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
            ASSERT_NO_THROW(subnet->getCfgOption()->add(option, false, false,
                                                        DHCP6_OPTION_SPACE));
        }
    }

    // Sanity check that all options are there.
    OptionContainerPtr options = subnet->getCfgOption()->getAll(DHCP6_OPTION_SPACE);
    ASSERT_EQ(20, options->size());

    // Use container index #1 to get the options by their codes.
    OptionContainerTypeIndex& idx = options->get<1>();
    // Look for the codes 100-109.
    for (uint16_t code = 100; code < 110; ++ code) {
        // For each code we should get two instances of options->
        OptionContainerTypeRange range = idx.equal_range(code);
        // Distance between iterators indicates how many options
        // have been returned for the particular code.
        ASSERT_EQ(2, distance(range.first, range.second));
        // Check that returned options actually have the expected option code.
        for (OptionContainerTypeIndex::const_iterator option_desc = range.first;
             option_desc != range.second; ++option_desc) {
            ASSERT_TRUE(option_desc->option_);
            EXPECT_EQ(code, option_desc->option_->getType());
        }
    }

    // Let's try to find some non-exiting option.
    const uint16_t non_existing_code = 150;
    OptionContainerTypeRange range = idx.equal_range(non_existing_code);
    // Empty set is expected.
    EXPECT_EQ(0, distance(range.first, range.second));
}

TEST(Subnet6Test, addPersistentOption) {
    // Create as subnet to add options to it.
    auto subnet = Subnet6::create(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4);

    // Add 10 options to the subnet with option codes 100 - 109.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        // We create 10 options and want some of them to be flagged
        // persistent and some non-persistent. Persistent options are
        // those that server sends to clients regardless if they ask
        // for them or not. We pick 3 out of 10 options and mark them
        // non-persistent and 7 other options persistent.
        // Code values: 102, 105 and 108 are divisible by 3
        // and options with these codes will be flagged non-persistent.
        // Options with other codes will be flagged persistent.
        bool persistent = (code % 3) ? true : false;
        ASSERT_NO_THROW(subnet->getCfgOption()->add(option, persistent,
                                                    false,
                                                    DHCP6_OPTION_SPACE));
    }

    // Get added options from the subnet.
    OptionContainerPtr options = subnet->getCfgOption()->getAll(DHCP6_OPTION_SPACE);

    // options->get<2> returns reference to container index #2. This
    // index is used to access options by the 'persistent' flag.
    OptionContainerPersistIndex& idx = options->get<2>();

    // Get all persistent options->
    OptionContainerPersistRange range_persistent = idx.equal_range(true);
    // 7 out of 10 options have been flagged persistent.
    ASSERT_EQ(7, distance(range_persistent.first, range_persistent.second));

    // Get all non-persistent options->
    OptionContainerPersistRange range_non_persistent = idx.equal_range(false);
    // 3 out of 10 options have been flagged not persistent.
    ASSERT_EQ(3, distance(range_non_persistent.first, range_non_persistent.second));
}

TEST(Subnet6Test, getOptions) {
    auto subnet = Subnet6::create(IOAddress("2001:db8::"), 56, 1, 2, 3, 4);

    // Add 10 options to a "dhcp6" option space in the subnet.
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(subnet->getCfgOption()->add(option, false, false,
                                                    DHCP6_OPTION_SPACE));
    }

    // Check that we can get each added option descriptor using
    // individually.
    for (uint16_t code = 100; code < 110; ++code) {
        std::ostringstream stream;
        // First, try the invalid option space name.
        OptionDescriptor desc = subnet->getCfgOption()->get("isc", code);
        // Returned descriptor should contain NULL option ptr.
        EXPECT_FALSE(desc.option_);
        // Now, try the valid option space.
        desc = subnet->getCfgOption()->get(DHCP6_OPTION_SPACE, code);
        // Test that the option code matches the expected code.
        ASSERT_TRUE(desc.option_);
        EXPECT_EQ(code, desc.option_->getType());
    }
}

TEST(Subnet6Test, addVendorOption) {

    // Create as subnet to add options to it.
    auto subnet = Subnet6::create(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4);

    // Differentiate options by their codes (100-109)
    for (uint16_t code = 100; code < 110; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(subnet->getCfgOption()->add(option, false, false,
                                                    "vendor-12345678"));
    }

    // Add 7 options to another option space. The option codes partially overlap
    // with option codes that we have added to dhcp6 option space.
    for (uint16_t code = 105; code < 112; ++code) {
        OptionPtr option(new Option(Option::V6, code, OptionBuffer(10, 0xFF)));
        ASSERT_NO_THROW(subnet->getCfgOption()->add(option, false, false,
                                                    "vendor-87654321"));
    }

    // Get options from the Subnet and check if all 10 are there.
    OptionContainerPtr options = subnet->getCfgOption()->getAll(12345678);
    ASSERT_TRUE(options);
    ASSERT_EQ(10, options->size());

    // Validate codes of options added to dhcp6 option space.
    uint16_t expected_code = 100;
    for (OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option_);
        EXPECT_EQ(expected_code, option_desc->option_->getType());
        ++expected_code;
    }

    options = subnet->getCfgOption()->getAll(87654321);
    ASSERT_TRUE(options);
    ASSERT_EQ(7, options->size());

    // Validate codes of options added to isc option space.
    expected_code = 105;
    for (OptionContainer::const_iterator option_desc = options->begin();
         option_desc != options->end(); ++option_desc) {
        ASSERT_TRUE(option_desc->option_);
        EXPECT_EQ(expected_code, option_desc->option_->getType());
        ++expected_code;
    }

    // Try to get options from a non-existing option space.
    options = subnet->getCfgOption()->getAll(1111111);
    ASSERT_TRUE(options);
    EXPECT_TRUE(options->empty());
}

// This test verifies that inRange() and inPool() methods work properly.
TEST(Subnet6Test, inRangeinPool) {
    auto subnet = Subnet6::create(IOAddress("2001:db8::"), 32, 1, 2, 3, 4);

    // this one is in subnet
    Pool6Ptr pool1(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8::10"),
                             IOAddress("2001:db8::20")));
    subnet->addPool(pool1);

    // 2001:db8::1 belongs to the subnet...
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::1")));
    // ... but it does not belong to any pool within
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::1")));

    // the last address that is in range, but out of pool
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::f")));
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::f")));

    // the first address that is in range, in pool
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::10")));
    EXPECT_TRUE(subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::10")));

    // let's try something in the middle as well
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::18")));
    EXPECT_TRUE(subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::18")));

    // the last address that is in range, in pool
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::20")));
    EXPECT_TRUE (subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::20")));

    // the first address that is in range, but out of pool
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::21")));
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::21")));

    // Add with classes
    pool1->allowClientClass("bar");
    EXPECT_TRUE(subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::18")));

    // This client does not belong to any class.
    isc::dhcp::ClientClasses no_class;
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::18"), no_class));

    // This client belongs to foo only
    isc::dhcp::ClientClasses foo_class;
    foo_class.insert("foo");
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::18"), foo_class));

    // This client belongs to bar only. I like that client.
    isc::dhcp::ClientClasses bar_class;
    bar_class.insert("bar");
    EXPECT_TRUE(subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::18"), bar_class));

    // This client belongs to foo, bar and baz classes.
    isc::dhcp::ClientClasses three_classes;
    three_classes.insert("foo");
    three_classes.insert("bar");
    three_classes.insert("baz");
    EXPECT_TRUE(subnet->inPool(Lease::TYPE_NA, IOAddress("2001:db8::18"), three_classes));
}

// This test verifies that inRange() and inPool() methods work properly
// for prefixes too.
TEST(Subnet6Test, PdinRangeinPool) {
    auto subnet = Subnet6::create(IOAddress("2001:db8::"), 64, 1, 2, 3, 4);

    // this one is in subnet
    Pool6Ptr pool1(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8::"),
                             96, 112));
    subnet->addPool(pool1);

    // this one is not in subnet
    Pool6Ptr pool2(new Pool6(Lease::TYPE_PD, IOAddress("2001:db8:1::"),
                             96, 112));
    subnet->addPool(pool2);

    // 2001:db8::1:0:0 belongs to the subnet...
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::1:0:0")));
    // ... but it does not belong to any pool within
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_PD, IOAddress("2001:db8::1:0:0")));

    // 2001:db8:1::1 does not belong to the subnet...
    EXPECT_FALSE(subnet->inRange(IOAddress("2001:db8:1::1")));
    // ... but it belongs to the second pool
    EXPECT_TRUE(subnet->inPool(Lease::TYPE_PD, IOAddress("2001:db8:1::1")));

    // 2001:db8::1 belongs to the subnet and to the first pool
    EXPECT_TRUE(subnet->inRange(IOAddress("2001:db8::1")));
    EXPECT_TRUE(subnet->inPool(Lease::TYPE_PD, IOAddress("2001:db8::1")));

    // 2001:db8:0:1:0:1:: does not belong to the subnet and any pool
    EXPECT_FALSE(subnet->inRange(IOAddress("2001:db8:0:1:0:1::")));
    EXPECT_FALSE(subnet->inPool(Lease::TYPE_PD, IOAddress("2001:db8:0:1:0:1::")));
}

// This test checks if the toText() method returns text representation
TEST(Subnet6Test, toText) {
    Subnet6 subnet(IOAddress("2001:db8::"), 32, 1, 2, 3, 4);
    EXPECT_EQ("2001:db8::/32", subnet.toText());
}

// This test verifies that the IPv6 prefix can be parsed into prefix/length pair.
TEST(Subnet6Test, parsePrefix) {
    std::pair<IOAddress, uint8_t> parsed =
        std::make_pair(IOAddress::IPV6_ZERO_ADDRESS(), 0);

    // Valid prefix.
    EXPECT_NO_THROW(parsed = Subnet6::parsePrefix("2001:db8:1::/64"));
    EXPECT_EQ("2001:db8:1::", parsed.first.toText());
    EXPECT_EQ(64, static_cast<int>(parsed.second));

    // Invalid IPv6 address.
    EXPECT_THROW(Subnet6::parsePrefix("2001:db8::1::/64"), BadValue);

    // Invalid prefix length.
    EXPECT_THROW(Subnet6::parsePrefix("2001:db8:1::/164"), BadValue);
    EXPECT_THROW(Subnet6::parsePrefix("2001:db8:1::/0"), BadValue);

    // No IP address.
    EXPECT_THROW(Subnet6::parsePrefix(" /64"), BadValue);

    // No prefix length but slash present.
    EXPECT_THROW(Subnet6::parsePrefix("3000::/ "), BadValue);

    // No slash sign.
    EXPECT_THROW(Subnet6::parsePrefix("3000::"), BadValue);

    // IPv4 is not allowed here.
    EXPECT_THROW(Subnet6::parsePrefix("192.0.2.0/24"), BadValue);
}

// This test checks if the get() method returns proper parameters
TEST(Subnet6Test, get) {
    Subnet6 subnet(IOAddress("2001:db8::"), 32, 1, 2, 3, 4);
    EXPECT_EQ("2001:db8::", subnet.get().first.toText());
    EXPECT_EQ(32, subnet.get().second);
}

// This trivial test checks if interface name is stored properly
// in Subnet6 objects.
TEST(Subnet6Test, iface) {
    Subnet6 subnet(IOAddress("2001:db8::"), 32, 1, 2, 3, 4);

    EXPECT_TRUE(subnet.getIface().empty());

    subnet.setIface("en1");
    EXPECT_EQ("en1", subnet.getIface().get());
}

// This trivial test checks if the interface-id option can be set and
// later retrieved for a subnet6 object.
TEST(Subnet6Test, interfaceId) {
    // Create as subnet to add options to it.
    auto subnet = Subnet6::create(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4);

    EXPECT_FALSE(subnet->getInterfaceId());

    OptionPtr option(new Option(Option::V6, D6O_INTERFACE_ID, OptionBuffer(10, 0xFF)));
    subnet->setInterfaceId(option);

    EXPECT_EQ(option, subnet->getInterfaceId());

}

// This test checks that the Rapid Commit support can be enabled or
// disabled for a subnet. It also checks that the Rapid Commit
// support is disabled by default.
TEST(Subnet6Test, rapidCommit) {
    Subnet6 subnet(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4);

    // By default, the RC should be disabled.
    EXPECT_FALSE(subnet.getRapidCommit());

    // Enable Rapid Commit.
    subnet.setRapidCommit(true);
    EXPECT_TRUE(subnet.getRapidCommit());

    // Disable again.
    subnet.setRapidCommit(false);
    EXPECT_FALSE(subnet.getRapidCommit());
}

// This test verifies that the IPv4 subnet can be fetched by id.
TEST(SubnetFetcherTest, getSubnet4ById) {
    Subnet4Collection collection;

    // Subnet hasn't been added to the collection. A null pointer should
    // be returned.
    auto subnet = SubnetFetcher4::get(collection, SubnetID(1024));
    EXPECT_FALSE(subnet);

    subnet.reset(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1024));
    EXPECT_NO_THROW(collection.insert(subnet));

    subnet.reset(new Subnet4(IOAddress("192.0.3.0"), 24, 1, 2, 3, 2048));
    EXPECT_NO_THROW(collection.insert(subnet));

    subnet = SubnetFetcher4::get(collection, SubnetID(1024));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1024, subnet->getID());
    EXPECT_EQ("192.0.2.0/24", subnet->toText());

    subnet = SubnetFetcher4::get(collection, SubnetID(2048));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(2048, subnet->getID());
    EXPECT_EQ("192.0.3.0/24", subnet->toText());
}

// This test verifies that the IPv6 subnet can be fetched by id.
TEST(SubnetFetcherTest, getSubnet6ById) {
    Subnet6Collection collection;

    // Subnet hasn't been added to the collection. A null pointer should
    // be returned.
    auto subnet = SubnetFetcher6::get(collection, SubnetID(1026));
    EXPECT_FALSE(subnet);

    subnet.reset(new Subnet6(IOAddress("2001:db8:1::"), 64, 1, 2, 3, 4, 1024));
    EXPECT_NO_THROW(collection.insert(subnet));

    subnet.reset(new Subnet6(IOAddress("2001:db8:2::"), 64, 1, 2, 3, 4, 2048));
    EXPECT_NO_THROW(collection.insert(subnet));

    subnet = SubnetFetcher6::get(collection, SubnetID(1024));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(1024, subnet->getID());
    EXPECT_EQ("2001:db8:1::/64", subnet->toText());

    subnet = SubnetFetcher6::get(collection, SubnetID(2048));
    ASSERT_TRUE(subnet);
    EXPECT_EQ(2048, subnet->getID());
    EXPECT_EQ("2001:db8:2::/64", subnet->toText());
}

};
