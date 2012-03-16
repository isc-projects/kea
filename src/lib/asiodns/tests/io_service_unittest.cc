// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
#include <gtest/gtest.h>

#include <asio.hpp>
#include <asiolink/asiolink.h>
#include <asiodns/asiodns.h>

#include <boost/scoped_ptr.hpp>

using namespace isc::asiolink;
using namespace isc::asiodns;
using boost::scoped_ptr;

const char* const TEST_SERVER_PORT = "53535";
const char* const TEST_CLIENT_PORT = "53536";
const char* const TEST_IPV6_ADDR = "::1";
const char* const TEST_IPV4_ADDR = "127.0.0.1";

TEST(IOServiceTest, badPort) {
    IOService io_service;
    EXPECT_THROW(DNSService(io_service, *"65536", true, false, NULL, NULL, NULL), IOError);
    EXPECT_THROW(DNSService(io_service, *"53210.0", true, false, NULL, NULL, NULL), IOError);
    EXPECT_THROW(DNSService(io_service, *"-1", true, false, NULL, NULL, NULL), IOError);
    EXPECT_THROW(DNSService(io_service, *"domain", true, false, NULL, NULL, NULL), IOError);
}

TEST(IOServiceTest, badAddress) {
    IOService io_service;
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *"192.0.2.1.1", NULL, NULL, NULL), IOError);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *"2001:db8:::1", NULL, NULL, NULL), IOError);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *"localhost", NULL, NULL, NULL), IOError);
}

TEST(IOServiceTest, unavailableAddress) {
    IOService io_service;
    // These addresses should generally be unavailable as a valid local
    // address, although there's no guarantee in theory.
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *"192.0.2.0", NULL, NULL, NULL), IOError);

    // Some OSes would simply reject binding attempt for an AF_INET6 socket
    // to an IPv4-mapped IPv6 address.  Even if those that allow it, since
    // the corresponding IPv4 address is the same as the one used in the
    // AF_INET socket case above, it should at least show the same result
    // as the previous one.
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *"::ffff:192.0.2.0", NULL, NULL, NULL), IOError);
}

TEST(IOServiceTest, duplicateBind_v6) {
    // In each sub test case, second attempt should fail due to duplicate bind
    IOService io_service;

    // IPv6, "any" address
    DNSService* dns_service = new DNSService(io_service, *TEST_SERVER_PORT, false, true, NULL, NULL, NULL);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, false, true, NULL, NULL, NULL), IOError);
    delete dns_service;

}

TEST(IOServiceTest, duplicateBind_v6_address) {
    // In each sub test case, second attempt should fail due to duplicate bind
    IOService io_service;

    // IPv6, specific address
    DNSService* dns_service = new DNSService(io_service, *TEST_SERVER_PORT, *TEST_IPV6_ADDR, NULL, NULL, NULL);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *TEST_IPV6_ADDR, NULL, NULL, NULL), IOError);
    delete dns_service;

}

TEST(IOServiceTest, duplicateBind_v4) {
    // In each sub test case, second attempt should fail due to duplicate bind
    IOService io_service;

    // IPv4, "any" address
    DNSService* dns_service = new DNSService(io_service, *TEST_SERVER_PORT, true, false, NULL, NULL, NULL);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, true, false, NULL, NULL, NULL), IOError);
    delete dns_service;

}

TEST(IOServiceTest, duplicateBind_v4_address) {
    // In each sub test case, second attempt should fail due to duplicate bind
    IOService io_service;

    // IPv4, specific address
    DNSService* dns_service = new DNSService(io_service, *TEST_SERVER_PORT, *TEST_IPV4_ADDR, NULL, NULL, NULL);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *TEST_IPV4_ADDR, NULL, NULL, NULL), IOError);
    delete dns_service;
}

// Disabled because IPv4-mapped addresses don't seem to be working with
// the IOService constructor
TEST(IOServiceTest, DISABLED_IPv4MappedDuplicateBind) {
    IOService io_service;
    // Duplicate bind on IPv4-mapped IPv6 address
    DNSService* dns_service = new DNSService(io_service, *TEST_SERVER_PORT, *"127.0.0.1", NULL, NULL, NULL);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *"::ffff:127.0.0.1", NULL, NULL, NULL), IOError);
    delete dns_service;

    // XXX:
    // Currently, this throws an "invalid argument" exception.  I have
    // not been able to get IPv4-mapped addresses to work.
    dns_service = new DNSService(io_service, *TEST_SERVER_PORT, *"::ffff:127.0.0.1", NULL, NULL, NULL);
    EXPECT_THROW(DNSService(io_service, *TEST_SERVER_PORT, *"127.0.0.1", NULL, NULL, NULL), IOError);
    delete dns_service;
}

TEST(IOServiceTest, BadUdpServerVersion) {
    IOService io_service;
    scoped_ptr<DNSService> dns_service(new DNSService(io_service, NULL, NULL,
                                                      NULL));
    EXPECT_THROW(dns_service->addServerUDPFromFD(42, AF_INET6,
                                                 UDPVersion(3)), IOError);
}
