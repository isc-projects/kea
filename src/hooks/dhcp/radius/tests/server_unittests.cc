// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the attribute,
/// attribute collection and config attribute collection classes.

#include <config.h>

#include <client_server.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>
#include <attribute_test.h>
#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <limits>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::radius;
using namespace isc::test;
using namespace std;
using namespace std::chrono;

namespace {

/// Verify Server::getAddress.
TEST(ServerClassTest, getAddress) {
    boost::scoped_ptr<IOAddress> addr;
    string bad = "does-not-exist.isc.org";
    EXPECT_THROW(addr.reset(new IOAddress(Server::getAddress(bad))), BadValue);
    EXPECT_FALSE(addr);

    string good = "www.isc.org";
    EXPECT_NO_THROW(addr.reset(new IOAddress(Server::getAddress(good))));
    EXPECT_TRUE(addr);
}

/// Verify Server::getSrcAddress.
TEST(ServerClassTest, getSrcAddress) {
    boost::scoped_ptr<IOAddress> addr;

    // 127.0.0.1.
    IOAddress addr4("127.0.0.1");
    EXPECT_NO_THROW(addr.reset(new IOAddress(Server::getSrcAddress(addr4))));
    ASSERT_TRUE(addr);
    EXPECT_EQ(AF_INET, addr->getFamily());
    EXPECT_EQ(addr4.toText(), addr->toText());
    addr.reset();

    // ::1.
    IOAddress addr6("::1");
    EXPECT_NO_THROW(addr.reset(new IOAddress(Server::getSrcAddress(addr6))));
    ASSERT_TRUE(addr);
    EXPECT_EQ(AF_INET6, addr->getFamily());
    EXPECT_EQ(addr6.toText(), addr->toText());
}

/// Test fixture for testing code of server class.
class ServerTest : public radius::test::AttributeTest {
};

// Verify constructor.
TEST_F(ServerTest, basic) {
    ServerPtr server;

    // Address mismatch.
    IOAddress addr4("192.0.2.1");
    IOAddress addr6("2001:db8::1235");
    string expected = "address family mismatch: peer ";
    expected += addr4.toText() + ", local " + addr6.toText();
    EXPECT_THROW_MSG(server.reset(new Server(addr4, 1234, addr6,
                                             "foo", 10, 0)),
                     BadValue, expected);
    expected = "address family mismatch: peer ";
    expected += addr6.toText() + ", local " + addr4.toText();
    EXPECT_THROW_MSG(server.reset(new Server(addr6, 1234, addr4,
                                             "foo", 10, 0)),
                     BadValue, expected);

    // Empty secret.
    EXPECT_THROW_MSG(server.reset(new Server(addr4, 1234, addr4, "", 10, 0)),
                     BadValue, "empty secret");

    // IPv4.
    ASSERT_NO_THROW(server.reset(new Server(addr4, 1234, addr4, "foo", 10, 0)));
    ASSERT_TRUE(server);
    EXPECT_EQ(addr4, server->getPeerAddress());
    EXPECT_EQ(1234, server->getPeerPort());
    EXPECT_NO_THROW(server->setPeerPort(2345));
    EXPECT_EQ(2345, server->getPeerPort());
    EXPECT_EQ(addr4, server->getLocalAddress());
    expected = "address family mismatch: peer ";
    expected += addr4.toText() + ", local " + addr6.toText();
    EXPECT_THROW_MSG(server->setLocalAddress(addr6), BadValue, expected);
    IOAddress addr4b("192.0.2.2");
    EXPECT_NO_THROW(server->setLocalAddress(addr4b));
    EXPECT_EQ(addr4b, server->getLocalAddress());
    EXPECT_EQ("foo", server->getSecret());
    EXPECT_THROW_MSG(server->setSecret(""), BadValue, "empty secret");
    EXPECT_NO_THROW(server->setSecret("bar"));
    EXPECT_EQ("bar", server->getSecret());
    EXPECT_EQ(10, server->getTimeout());
    // Zero timeout is rounded to 1.
    EXPECT_NO_THROW(server->setTimeout(0));
    EXPECT_EQ(1, server->getTimeout());
    if (numeric_limits<unsigned>::max() > numeric_limits<long>::max() / 1000) {
        auto div1000 = numeric_limits<long>::max() / 1000;
        unsigned large = static_cast<unsigned>(div1000 + 1);
        ostringstream ss;
        ss << "too large timeout " << large << " > " << div1000;
        EXPECT_THROW_MSG(server->setTimeout(large), OutOfRange, ss.str());
        cerr << ss.str() << "\n";
    }
    EXPECT_EQ(0, server->getDeadtime());
    EXPECT_NO_THROW(server->setDeadtime(60));
    EXPECT_EQ(60, server->getDeadtime());
    steady_clock::time_point now = steady_clock::now();
    EXPECT_TRUE(server->getDeadtimeEnd() <= now);
    steady_clock::time_point later = now + seconds(10);
    EXPECT_TRUE(server->getDeadtimeEnd() < later);

    // IPv6.
    EXPECT_NO_THROW(server.reset(new Server(addr6, 1234, addr6, "foo", 10, 0)));
    ASSERT_TRUE(server);
    EXPECT_EQ(addr6, server->getPeerAddress());
    EXPECT_EQ(addr6, server->getLocalAddress());
    expected = "address family mismatch: peer ";
    expected += addr6.toText() + ", local " + addr4.toText();
    EXPECT_THROW_MSG(server->setLocalAddress(addr4), BadValue, expected);
    IOAddress addr6b("2001:db8::2346");
    EXPECT_NO_THROW(server->setLocalAddress(addr6b));
    EXPECT_EQ(addr6b, server->getLocalAddress());

    // toElement.
    expected = "{ ";
    expected += "\"peer-address\": \"2001:db8::1235\", ";
    expected += "\"peer-port\": 1234, ";
    expected += "\"local-address\": \"2001:db8::2346\", ";
    expected += "\"secret\": \"foo\", ";
    expected += "\"timeout\": 10, ";
    expected += "\"deadtime\": 0 }";
    runToElementTest<Server>(expected, *server);

    // deadtime-end.
    now = steady_clock::now();
    EXPECT_NO_THROW(server.reset(new Server(addr6, 1234, addr6,
                                            "foo", 10, 60)));
    ASSERT_TRUE(server);
    ConstElementPtr map = server->toElement();
    ASSERT_TRUE(map);
    ASSERT_EQ(map->getType(), Element::map);
    ConstElementPtr deadtime_end = map->get("deadtime-end");
    ASSERT_TRUE(deadtime_end);
    ASSERT_EQ(deadtime_end->getType(), Element::integer);
    int64_t delta = deadtime_end->intValue();
    EXPECT_LE(0, delta) << "delta is " << delta;
    EXPECT_GT(10, delta) << "delta is " << delta;
}

} // end of anonymous namespace
