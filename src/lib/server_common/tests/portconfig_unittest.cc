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

#include <gtest/gtest.h>

#include <server_common/portconfig.h>
#include <testutils/socket_request.h>
#include <testutils/mockups.h>

#include <util/unittests/check_valgrind.h>
#include <util/unittests/resource.h>

#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <asiolink/asiolink.h>
#include <asiodns/asiodns.h>

#include <string>

using namespace isc::server_common::portconfig;
using namespace isc::server_common;
using namespace isc::data;
using namespace isc;
using namespace std;
using namespace isc::asiolink;
using namespace isc::asiodns;
using namespace isc::testutils;
using boost::lexical_cast;

namespace {

/// Testcase for parseAddresses call (struct, nobody cares about private here)
struct ParseAddresses : public ::testing::Test {
    AddressList result_;
    void empty(ElementPtr config, const string& name) {
        SCOPED_TRACE(name);
        EXPECT_NO_THROW(result_ = parseAddresses(config, "test"));
        EXPECT_TRUE(result_.empty());
    }
    template<class Exception>
    void invalidTest(const string& json, const string& name) {
        SCOPED_TRACE(name);
        ElementPtr config(Element::fromJSON(json));
        EXPECT_THROW(parseAddresses(config, "test"), Exception) <<
            "Should throw " << typeid(Exception).name();
    }
};

// Parse valid IPv4 address
TEST_F(ParseAddresses, ipv4) {
    ElementPtr config(Element::fromJSON("["
                                        "   {"
                                        "       \"address\": \"192.0.2.1\","
                                        "       \"port\": 53"
                                        "   }"
                                        "]"));
    EXPECT_NO_THROW(result_ = parseAddresses(config, "test"));
    ASSERT_EQ(1, result_.size());
    EXPECT_EQ("192.0.2.1", result_[0].first);
    EXPECT_EQ(53, result_[0].second);
}

// Parse valid IPv6 address
TEST_F(ParseAddresses, ipv6) {
    ElementPtr config(Element::fromJSON("["
                                        "   {"
                                        "       \"address\": \"2001:db8::1\","
                                        "       \"port\": 53"
                                        "   }"
                                        "]"));
    EXPECT_NO_THROW(result_ = parseAddresses(config, "test"));
    ASSERT_EQ(1, result_.size());
    EXPECT_EQ("2001:db8::1", result_[0].first);
    EXPECT_EQ(53, result_[0].second);
}

// Parse multiple addresses at once
// (even the ports are different to see they are not mistaken)
TEST_F(ParseAddresses, multi) {
    ElementPtr config(Element::fromJSON("["
                                        "   {"
                                        "       \"address\": \"2001:db8::1\","
                                        "       \"port\": 53"
                                        "   },"
                                        "   {"
                                        "       \"address\": \"192.0.2.1\","
                                        "       \"port\": 54"
                                        "   }"
                                        "]"));
    EXPECT_NO_THROW(result_ = parseAddresses(config, "test"));
    ASSERT_EQ(2, result_.size());
    EXPECT_EQ("2001:db8::1", result_[0].first);
    EXPECT_EQ(53, result_[0].second);
    EXPECT_EQ("192.0.2.1", result_[1].first);
    EXPECT_EQ(54, result_[1].second);
}

// Parse various versions of empty list
TEST_F(ParseAddresses, empty) {
    empty(Element::fromJSON("[]"), "Empty list");
    empty(ElementPtr(new NullElement), "Null element");
    empty(ElementPtr(), "Null pointer");
}

// Reject invalid configs
TEST_F(ParseAddresses, invalid) {
    invalidTest<TypeError>("{}", "Not a list");
    invalidTest<BadValue>("[{}]", "Empty element");
    invalidTest<TypeError>("[{"
                           "   \"port\": 1.5,"
                           "   \"address\": \"192.0.2.1\""
                           "}]", "Float port");
    invalidTest<BadValue>("[{"
                          "   \"port\": -5,"
                          "   \"address\": \"192.0.2.1\""
                          "}]", "Negative port");
    invalidTest<BadValue>("[{"
                          "   \"port\": 1000000,"
                          "   \"address\": \"192.0.2.1\""
                          "}]", "Port too big");
    invalidTest<IOError>("[{"
                         "   \"port\": 53,"
                         "   \"address\": \"bad_address\""
                         "}]", "Bad address");
}

// Test fixture for installListenAddresses
struct InstallListenAddresses : public ::testing::Test {
    InstallListenAddresses() :
        // The empty string is expected parameter of requestSocket,
        // not app_name - the request does not fall back to this, it
        // is checked to be the same.
        sock_requestor_(dnss_, store_, 5288, "")
    {
        valid_.push_back(AddressPair("127.0.0.1", 5288));
        valid_.push_back(AddressPair("::1", 5288));
        invalid_.push_back(AddressPair("127.0.0.1", 5288));
        invalid_.push_back(AddressPair("192.0.2.2", 1));
    }
    MockDNSService dnss_;
    AddressList store_;
    isc::testutils::TestSocketRequestor sock_requestor_;
    // We should be able to bind to these addresses
    AddressList valid_;
    // But this shouldn't work
    AddressList invalid_;
    // Check that the store_ addresses are the same as expected
    void checkAddresses(const AddressList& expected, const string& name) const
    {
        SCOPED_TRACE(name);

        ASSERT_EQ(expected.size(), store_.size()) <<
            "Different amount of elements, not checking content";
        // Run in parallel through the vectors
        for (AddressList::const_iterator ei(expected.begin()),
             si(store_.begin()); ei != expected.end(); ++ei, ++si) {
            EXPECT_EQ(ei->first, si->first);
            EXPECT_EQ(ei->second, si->second);
        }
    }
};

// Try switching valid addresses
// Check the sockets are correctly requested and returned
TEST_F(InstallListenAddresses, valid) {
    // First, bind to the valid addresses
    EXPECT_NO_THROW(installListenAddresses(valid_, store_, dnss_));
    checkAddresses(valid_, "Valid addresses");
    const char* tokens1[] = {
        "TCP:127.0.0.1:5288:1",
        "UDP:127.0.0.1:5288:2",
        "TCP:::1:5288:3",
        "UDP:::1:5288:4",
        NULL
    };
    const char* no_tokens[] = { NULL };
    sock_requestor_.checkTokens(tokens1, sock_requestor_.given_tokens_,
                                "Valid given tokens 1");
    sock_requestor_.checkTokens(no_tokens, sock_requestor_.released_tokens_,
                                "Valid no released tokens 1");
    // TODO Maybe some test to actually connect to them
    // Try setting it back to nothing
    sock_requestor_.given_tokens_.clear();
    EXPECT_NO_THROW(installListenAddresses(AddressList(), store_, dnss_));
    checkAddresses(AddressList(), "No addresses");
    sock_requestor_.checkTokens(no_tokens, sock_requestor_.given_tokens_,
                                "Valid no given tokens");
    sock_requestor_.checkTokens(tokens1, sock_requestor_.released_tokens_,
                                "Valid released tokens");
    // Try switching back again
    EXPECT_NO_THROW(installListenAddresses(valid_, store_, dnss_));
    checkAddresses(valid_, "Valid addresses");
    const char* tokens2[] = {
        "TCP:127.0.0.1:5288:5",
        "UDP:127.0.0.1:5288:6",
        "TCP:::1:5288:7",
        "UDP:::1:5288:8",
        NULL
    };
    sock_requestor_.checkTokens(tokens2, sock_requestor_.given_tokens_,
                                "Valid given tokens 2");
    sock_requestor_.checkTokens(tokens1, sock_requestor_.released_tokens_,
                                "Valid released tokens");
}

// Try if rollback works
TEST_F(InstallListenAddresses, rollback) {
    // Set some addresses
    EXPECT_NO_THROW(installListenAddresses(valid_, store_, dnss_));
    checkAddresses(valid_, "Before rollback");
    const char* tokens1[] = {
        "TCP:127.0.0.1:5288:1",
        "UDP:127.0.0.1:5288:2",
        "TCP:::1:5288:3",
        "UDP:::1:5288:4",
        NULL
    };
    const char* no_tokens[] = { NULL };
    sock_requestor_.checkTokens(tokens1, sock_requestor_.given_tokens_,
                                "Given before rollback");
    sock_requestor_.checkTokens(no_tokens, sock_requestor_.released_tokens_,
                                "Released before rollback");
    sock_requestor_.given_tokens_.clear();
    // This should not bind them, but should leave the original addresses
    EXPECT_THROW(installListenAddresses(invalid_, store_, dnss_),
                 SocketRequestor::SocketError);
    checkAddresses(valid_, "After rollback");
    // Now, it should have requested first pair of sockets from the invalids
    // and, as the second failed, it should have returned them right away.
    const char* released1[] = {
        "TCP:127.0.0.1:5288:1",
        "UDP:127.0.0.1:5288:2",
        "TCP:::1:5288:3",
        "UDP:::1:5288:4",
        "TCP:127.0.0.1:5288:5",
        "UDP:127.0.0.1:5288:6",
        NULL
    };
    // It should request the first pair of sockets, and then request the
    // complete set of valid addresses to rollback
    const char* tokens2[] = {
        "TCP:127.0.0.1:5288:5",
        "UDP:127.0.0.1:5288:6",
        "TCP:127.0.0.1:5288:7",
        "UDP:127.0.0.1:5288:8",
        "TCP:::1:5288:9",
        "UDP:::1:5288:10",
        NULL
    };
    sock_requestor_.checkTokens(tokens2, sock_requestor_.given_tokens_,
                                "Given after rollback");
    sock_requestor_.checkTokens(released1, sock_requestor_.released_tokens_,
                                "Released after rollback");
}

// Try it at least releases everything when even the rollback fails.
TEST_F(InstallListenAddresses, brokenRollback) {
    EXPECT_NO_THROW(installListenAddresses(valid_, store_, dnss_));
    checkAddresses(valid_, "Before rollback");
    // Don't check the tokens now, we already do it in rollback and valid tests
    sock_requestor_.given_tokens_.clear();
    sock_requestor_.break_rollback_ = true;
    EXPECT_THROW(installListenAddresses(invalid_, store_, dnss_),
                 SocketRequestor::NonFatalSocketError);
    // No addresses here
    EXPECT_TRUE(store_.empty());
    // The first pair should be requested in the first part of the failure to
    // bind and the second pair in the first part of rollback
    const char* tokens[] = {
        "TCP:127.0.0.1:5288:5",
        "UDP:127.0.0.1:5288:6",
        "TCP:127.0.0.1:5288:7",
        "UDP:127.0.0.1:5288:8",
        NULL
    };
    // The first set should be released, as well as all the ones we request now
    const char* released[] = {
        "TCP:127.0.0.1:5288:1",
        "UDP:127.0.0.1:5288:2",
        "TCP:::1:5288:3",
        "UDP:::1:5288:4",
        "TCP:127.0.0.1:5288:5",
        "UDP:127.0.0.1:5288:6",
        "TCP:127.0.0.1:5288:7",
        "UDP:127.0.0.1:5288:8",
        NULL
    };
    sock_requestor_.checkTokens(tokens, sock_requestor_.given_tokens_,
                                "given");
    sock_requestor_.checkTokens(released, sock_requestor_.released_tokens_,
                                "released");
}

// Make sure the death tests are filterable away.
typedef InstallListenAddresses InstallListenAddressesDeathTest;

// There are systems which don't have EXPECT_DEATH. We skip the tests there.
// We're lucky, EXPECT_DEATH is a macro, so we can test for its existence this
// easily.
#ifdef EXPECT_DEATH
// We make the socket requestor throw a "fatal" exception, one where we can't be
// sure the state between processes is consistent. So we abort in that case.
TEST_F(InstallListenAddressesDeathTest, inconsistent) {
    if (!isc::util::unittests::runningOnValgrind()) {
        AddressList deathAddresses;
        deathAddresses.push_back(AddressPair("192.0.2.3", 5288));
        // Make sure it actually kills the application (there should be an abort
        // in this case)
        EXPECT_DEATH({
            isc::util::unittests::dontCreateCoreDumps();

            try {
              installListenAddresses(deathAddresses, store_, dnss_);
            } catch (...) {
              // Prevent exceptions killing the application, we need
              // to make sure it dies the real hard way
            };
          }, "");
    }
}

// If we are unable to tell the boss we closed a socket, we abort, as we are
// not consistent with the boss most probably.
TEST_F(InstallListenAddressesDeathTest, cantClose) {
    if (!isc::util::unittests::runningOnValgrind()) {
        installListenAddresses(valid_, store_, dnss_);
        AddressList empty;
        // Instruct it to fail on close
        sock_requestor_.break_release_ = true;
        EXPECT_DEATH({
            isc::util::unittests::dontCreateCoreDumps();

            try {
              // Setting to empty will close all current sockets.
              // And thanks to the break_release_, the close will
              // throw, which will make it crash.
              installListenAddresses(empty, store_, dnss_);
            } catch (...) {
              // To make sure it is killed by abort, not by some
              // (unhandled) exception
            };
          }, "");
        // And reset it back, so it can safely clean up itself.
        sock_requestor_.break_release_ = false;
    }
}
#endif // EXPECT_DEATH

}
