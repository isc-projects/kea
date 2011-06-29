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

#include <exceptions/exceptions.h>

#include <cc/data.h>
#include <acl/dns.h>
#include <acl/loader.h>
#include <acl/check.h>
#include <acl/ip_check.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::data;
using namespace isc::acl::dns;
using isc::acl::LoaderError;

namespace {

// Tests that the getLoader actually returns something, returns the same every
// time and the returned value can be used to anything. It is not much of a
// test, but the getLoader is not much of a function.
TEST(DNSACL, getLoader) {
    RequestLoader* l(&getLoader());
    ASSERT_TRUE(l != NULL);
    EXPECT_EQ(l, &getLoader());
    EXPECT_NO_THROW(l->load(Element::fromJSON("[{\"action\": \"DROP\"}]")));

    // Test check rules registered by default, i.e. RequestCheck
    EXPECT_NO_THROW(l->load(Element::fromJSON("[{\"action\": \"DROP\","
                                              "  \"from\": \"192.0.2.1\"}]")));
}

class RequestCheckCreatorTest : public ::testing::Test {
protected:
    internal::RequestCheckCreator creator_;

    typedef boost::shared_ptr<const RequestCheck> ConstRequestCheckPtr;
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
                             getLoader());
    const internal::RequestIPCheck& ipcheck_ =
        dynamic_cast<const internal::RequestIPCheck&>(*check_);
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
                             getLoader());
    const internal::RequestIPCheck& ipcheck_ =
        dynamic_cast<const internal::RequestIPCheck&>(*check_);
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
                                 getLoader()), LoaderError);

    // Invalid type of parameter
    EXPECT_THROW(creator_.create("from", Element::fromJSON("4"), getLoader()),
                 isc::data::TypeError);
    EXPECT_THROW(creator_.create("from", Element::fromJSON("[]"), getLoader()),
                 isc::data::TypeError);

    // Syntax error for IPCheck
    EXPECT_THROW(creator_.create("from", Element::fromJSON("\"bad\""),
                                 getLoader()),
                 isc::InvalidParameter);

    // NULL pointer
    EXPECT_THROW(creator_.create("from", ConstElementPtr(), getLoader()),
                 LoaderError);
}

}
