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

#include <stdint.h>

#include <algorithm>
#include <vector>
#include <string>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

#include <cc/data.h>
#include <acl/dns.h>
#include <acl/loader.h>
#include <acl/check.h>
#include <acl/ip_check.h>

#include "sockaddr.h"

#include <gtest/gtest.h>

using namespace std;
using boost::scoped_ptr;
using namespace isc::data;
using namespace isc::acl;
using isc::acl::LoaderError;

namespace {

// Tests that the getLoader actually returns something, returns the same every
// time and the returned value can be used to anything. It is not much of a
// test, but the getLoader is not much of a function.
TEST(DNSACL, getLoader) {
    dns::RequestLoader* l(&dns::getLoader());
    ASSERT_TRUE(l != NULL);
    EXPECT_EQ(l, &dns::getLoader());
    EXPECT_NO_THROW(l->load(Element::fromJSON("[{\"action\": \"DROP\"}]")));

    // Test check rules registered by default, i.e. RequestCheck
    EXPECT_NO_THROW(l->load(Element::fromJSON("[{\"action\": \"DROP\","
                                              "  \"from\": \"192.0.2.1\"}]")));
}

class RequestCheckCreatorTest : public ::testing::Test {
protected:
    dns::internal::RequestCheckCreator creator_;

    typedef boost::shared_ptr<const dns::RequestCheck> ConstRequestCheckPtr;
    ConstRequestCheckPtr check_;
};

TEST_F(RequestCheckCreatorTest, names) {
    ASSERT_EQ(1, creator_.names().size());
    EXPECT_EQ("from", creator_.names()[0]);
}

TEST_F(RequestCheckCreatorTest, allowListAbbreviation) {
    EXPECT_FALSE(creator_.allowListAbbreviation());
}

// The following two tests check the creator for the form of
// 'from: "IP prefix"'.  We don't test many variants of prefixes, which
// are done in the tests for IPCheck.
TEST_F(RequestCheckCreatorTest, createIPv4Check) {
    check_ = creator_.create("from", Element::fromJSON("\"192.0.2.1\""),
                             dns::getLoader());
    const dns::internal::RequestIPCheck& ipcheck_ =
        dynamic_cast<const dns::internal::RequestIPCheck&>(*check_);
    EXPECT_EQ(AF_INET, ipcheck_.getFamily());
    EXPECT_EQ(32, ipcheck_.getPrefixlen());
    const vector<uint8_t> check_address(ipcheck_.getAddress());
    ASSERT_EQ(4, check_address.size());
    const uint8_t expected_address[] = { 192, 0, 2, 1 };
    EXPECT_TRUE(equal(check_address.begin(), check_address.end(),
                      expected_address));
}

TEST_F(RequestCheckCreatorTest, createIPv6Check) {
    check_ = creator_.create("from",
                             Element::fromJSON("\"2001:db8::5300/120\""),
                             dns::getLoader());
    const dns::internal::RequestIPCheck& ipcheck_ =
        dynamic_cast<const dns::internal::RequestIPCheck&>(*check_);
    EXPECT_EQ(AF_INET6, ipcheck_.getFamily());
    EXPECT_EQ(120, ipcheck_.getPrefixlen());
    const vector<uint8_t> check_address(ipcheck_.getAddress());
    ASSERT_EQ(16, check_address.size());
    const uint8_t expected_address[] = { 0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x53, 0x00 };
    EXPECT_TRUE(equal(check_address.begin(), check_address.end(),
                      expected_address));
}

TEST_F(RequestCheckCreatorTest, badCreate) {
    // Invalid name
    EXPECT_THROW(creator_.create("bad", Element::fromJSON("\"192.0.2.1\""),
                                 dns::getLoader()), LoaderError);

    // Invalid type of parameter
    EXPECT_THROW(creator_.create("from", Element::fromJSON("4"),
                                 dns::getLoader()),
                 isc::data::TypeError);
    EXPECT_THROW(creator_.create("from", Element::fromJSON("[]"),
                                 dns::getLoader()),
                 isc::data::TypeError);

    // Syntax error for IPCheck
    EXPECT_THROW(creator_.create("from", Element::fromJSON("\"bad\""),
                                 dns::getLoader()),
                 isc::InvalidParameter);

    // NULL pointer
    EXPECT_THROW(creator_.create("from", ConstElementPtr(), dns::getLoader()),
                 LoaderError);
}

class RequestCheckTest : public ::testing::Test {
protected:
    typedef boost::shared_ptr<const dns::RequestCheck> ConstRequestCheckPtr;

    // A helper shortcut to create a single IP check for the given prefix.
    ConstRequestCheckPtr createIPCheck(const string& prefix) {
        return (creator_.create("from", Element::fromJSON(
                                    string("\"") + prefix + string("\"")),
                                dns::getLoader()));
    }

    // create a one time request context for a specific test.  Note that
    // getSockaddr() uses a static storage, so it cannot be called more than
    // once in a single test.
    const dns::RequestContext& getRequest4() {
        ipaddr.reset(new IPAddress(tests::getSockAddr("192.0.2.1")));
        request.reset(new dns::RequestContext(*ipaddr));
        return (*request);
    }
    const dns::RequestContext& getRequest6() {
        ipaddr.reset(new IPAddress(tests::getSockAddr("2001:db8::1")));
        request.reset(new dns::RequestContext(*ipaddr));
        return (*request);
    }

private:
    scoped_ptr<IPAddress> ipaddr;
    scoped_ptr<dns::RequestContext> request;
    dns::internal::RequestCheckCreator creator_;
};

TEST_F(RequestCheckTest, checkIPv4) {
    // Exact match
    EXPECT_TRUE(createIPCheck("192.0.2.1")->matches(getRequest4()));
    // Exact match (negative)
    EXPECT_FALSE(createIPCheck("192.0.2.53")->matches(getRequest4()));
    // Prefix match
    EXPECT_TRUE(createIPCheck("192.0.2.0/24")->matches(getRequest4()));
    // Prefix match (negative)
    EXPECT_FALSE(createIPCheck("192.0.1.0/24")->matches(getRequest4()));
    // Address family mismatch (the first 4 bytes of the IPv6 address has the
    // same binary representation as the client's IPv4 address, which
    // shouldn't confuse the match logic)
    EXPECT_FALSE(createIPCheck("c000:0201::")->matches(getRequest4()));
}

TEST_F(RequestCheckTest, checkIPv6) {
    // The following are a set of tests of the same concept as checkIPv4
    EXPECT_TRUE(createIPCheck("2001:db8::1")->matches(getRequest6()));
    EXPECT_FALSE(createIPCheck("2001:db8::53")->matches(getRequest6()));
    EXPECT_TRUE(createIPCheck("2001:db8::/64")->matches(getRequest6()));
    EXPECT_FALSE(createIPCheck("2001:db8:1::/64")->matches(getRequest6()));
    EXPECT_FALSE(createIPCheck("32.1.13.184")->matches(getRequest6()));
}

}
