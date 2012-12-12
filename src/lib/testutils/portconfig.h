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

#ifndef ISC_TESTUTILS_PORTCONFIG_H
#define ISC_TESTUTILS_PORTCONFIG_H

#include <gtest/gtest.h>
#include <cc/data.h>
#include <server_common/portconfig.h>

namespace isc {
namespace testutils {
/**
 * \brief Bits of tests for server port configuration.
 *
 * These are bits of tests that can be reused by server classes to check if
 * configuration of the listening addresses work.
 *
 * You can put any of these functions into a TEST_F test and pass the server
 * to it.
 *
 * \todo There's quite a lot of common code in the basic server handling.
 *     We should refactor it, so both Resolver server and Auth server have
 *     a common base class. When this is done, the common parts would be put
 *     there and the tests would be at the base class, not here.
 */
namespace portconfig {

/**
 * \brief Check setting of the listening addresses directly (as a list) works.
 *
 * \param server The server to test against.
 */
template<class Server>
void
listenAddresses(Server& server) {
    using namespace isc::server_common::portconfig;
    // In this test we assume the address list is originally empty.
    EXPECT_TRUE(server.getListenAddresses().empty());

    // Try putting there some addresses
    AddressList addresses;
    addresses.push_back(AddressPair("127.0.0.1", 53210));
    addresses.push_back(AddressPair("::1", 53210));
    server.setListenAddresses(addresses);
    EXPECT_EQ(2, server.getListenAddresses().size());
    EXPECT_EQ("::1", server.getListenAddresses()[1].first);

    // Is it independent from what we do with the vector later?
    addresses.clear();
    EXPECT_EQ(2, server.getListenAddresses().size());

    // If we set to an empty list next, the server configuration should
    // become empty, too.
    server.setListenAddresses(addresses);
    EXPECT_TRUE(server.getListenAddresses().empty());
}

/**
 * \brief Check setting of the addresses by config value.
 *
 * This passes an listen_on element to the server's updateConfig function.
 * It tries little bit of switching around. It tries both setting a presumably
 * valid addresses and then setting something that cant be bound, rolling back
 * back to original.
 *
 * \param server The server object to test against.
 */
template<class Server>
void
listenAddressConfig(Server& server) {
    using namespace isc::data;
    // Try putting there some address
    ElementPtr config(Element::fromJSON("{"
                                        "\"listen_on\": ["
                                        "   {"
                                        "       \"address\": \"127.0.0.1\","
                                        "       \"port\": 53210"
                                        "   }"
                                        "]"
                                        "}"));
    ConstElementPtr result(server.updateConfig(config));
    EXPECT_EQ(result->toWire(), isc::config::createAnswer()->toWire());
    ASSERT_EQ(1, server.getListenAddresses().size());
    EXPECT_EQ("127.0.0.1", server.getListenAddresses()[0].first);
    EXPECT_EQ(53210, server.getListenAddresses()[0].second);

    // This address is rejected by the test socket requestor
    config = Element::fromJSON("{"
                               "\"listen_on\": ["
                               "   {"
                               "       \"address\": \"192.0.2.2\","
                               "       \"port\": 53210"
                               "   }"
                               "]"
                               "}");
    result = server.updateConfig(config);
    EXPECT_FALSE(result->equals(*isc::config::createAnswer()));
    ASSERT_EQ(1, server.getListenAddresses().size());
    EXPECT_EQ("127.0.0.1", server.getListenAddresses()[0].first);
    EXPECT_EQ(53210, server.getListenAddresses()[0].second);

}

/**
 * \brief Check that given config is rejected.
 *
 * Try if given config is considered invalid by the server and is rejected.
 * The value is converted from JSON to the data elements and passed to server's
 * updateConfig method. It should not crash, but return a negative answer.
 *
 * It is used internally by invalidListenAddressConfig, but you can use it
 * to test any other invalid configs.
 *
 * \todo It might be better to put it to some other namespace, as this is more
 *     generic. But right now it is used only here, so until something else
 *     needs it, it might as well stay here.
 * \param server The server to test against.
 * \param JSON Config to use.
 * \param name It is used in the output if the test fails.
 */
template<class Server>
void
configRejected(Server& server, const std::string& JSON,
               const std::string& name)
{
    SCOPED_TRACE(name);

    using namespace isc::data;
    ElementPtr config(Element::fromJSON(JSON));
    EXPECT_FALSE(server.updateConfig(config)->
                 equals(*isc::config::createAnswer())) <<
        "Accepted invalid config " << JSON;
}

/**
 * \brief Check some invalid address configs.
 *
 * It tries a series of invalid listen_on configs against the server and checks
 * it is rejected.
 * \param server The server to check against.
 */
template<class Server>
void
invalidListenAddressConfig(Server& server) {
    configRejected(server, "{"
                   "\"listen_on\": \"error\""
                   "}", "Wrong element type");
    configRejected(server, "{"
                   "\"listen_on\": [{}]"
                   "}", "Empty address element");
    configRejected(server, "{"
                   "\"listen_on\": [{"
                   "   \"port\": 1.5,"
                   "   \"address\": \"192.0.2.1\""
                   "}]}", "Float port");
    configRejected(server, "{"
                   "\"listen_on\": [{"
                   "   \"port\": -5,"
                   "   \"address\": \"192.0.2.1\""
                   "}]}", "Negative port");
    configRejected(server, "{"
                   "\"listen_on\": [{"
                   "   \"port\": 1000000,"
                   "   \"address\": \"192.0.2.1\""
                   "}]}", "Huge port");
    configRejected(server, "{"
                   "\"listen_on\": [{"
                   "   \"port\": 53,"
                   "   \"address\": \"bad_address\""
                   "}]}", "Bad address");
}

}
}
}

#endif  // ISC_TESTUTILS_PORTCONFIG_H
