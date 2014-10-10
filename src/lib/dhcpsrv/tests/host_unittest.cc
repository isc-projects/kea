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

TEST(IPv6ResrvTest, constructorAddress) {
    IPv6Resrv resrv(IOAddress("2001:db8:1::cafe"));
    EXPECT_EQ("2001:db8:1::cafe", resrv.getAddress().toText());
    EXPECT_EQ(128, resrv.getPrefixLen());
    EXPECT_EQ(IPv6Resrv::TYPE_NA, resrv.getType());
}

TEST(IPv6ResrvTest, constructorPrefix) {
    IPv6Resrv resrv(IOAddress("2001:db8:1::"), 64);
    EXPECT_EQ("2001:db8:1::", resrv.getAddress().toText());
    EXPECT_EQ(64, resrv.getPrefixLen());
    EXPECT_EQ(IPv6Resrv::TYPE_PD, resrv.getType());
}

TEST(IPv6ResrvTest, setPrefix) {
    IPv6Resrv resrv(IOAddress("2001:db8:1::1"));
    ASSERT_EQ("2001:db8:1::1", resrv.getAddress().toText());
    ASSERT_EQ(128, resrv.getPrefixLen());
    ASSERT_EQ(IPv6Resrv::TYPE_NA, resrv.getType());

    ASSERT_NO_THROW(resrv.set(IOAddress("2001:db8::"), 48));
    EXPECT_EQ("2001:db8::", resrv.getAddress().toText());
    EXPECT_EQ(48, resrv.getPrefixLen());
    EXPECT_EQ(IPv6Resrv::TYPE_PD, resrv.getType());
}

TEST(HostTest, createFromHWAddrString) {
    boost::scoped_ptr<Host> host;
    ASSERT_NO_THROW(host.reset(new Host("01:02:03:04:05:06", "hw-address",
                                        SubnetID(1), SubnetID(2),
                                        IOAddress("192.0.2.3"),
                                        "somehost.example.org")));

    HWAddrPtr hwaddr = host->getHWAddress();
    ASSERT_TRUE(hwaddr);

    EXPECT_EQ("hwtype=1 01:02:03:04:05:06", hwaddr->toText());

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

TEST(HostTest, createFromDUIDString) {
    boost::scoped_ptr<Host> host;
    /*    ASSERT_NO_THROW(host.reset(new Host("a1:b2:c3:d4:e5:06", "duid",
                                        SubnetID(10), SubnetID(20),
                                        IOAddress("192.0.2.5"),
                                        "me.example.org"))); */

    try {
        host.reset(new Host("a1:b2:c3:d4:e5:06", "duid",
                                        SubnetID(10), SubnetID(20),
                                        IOAddress("192.0.2.5"),
                            "me.example.org"));
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    DuidPtr duid = host->getDuid();
    ASSERT_TRUE(duid);

    EXPECT_EQ("a1:b2:c3:d4:e5:06", duid->toText());

    /*    EXPECT_FALSE(host->getDuid());
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
                      isc::BadValue); */
}



} // end of anonymous namespace
