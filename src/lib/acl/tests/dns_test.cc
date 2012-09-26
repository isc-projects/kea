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

#include <dns/name.h>
#include <dns/tsigkey.h>
#include <dns/tsigrecord.h>
#include <dns/rdataclass.h>

#include <cc/data.h>
#include <acl/dns.h>
#include <acl/loader.h>
#include <acl/check.h>
#include <acl/ip_check.h>

#include "sockaddr.h"

#include <gtest/gtest.h>

using namespace std;
using boost::scoped_ptr;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::data;
using namespace isc::acl;
using namespace isc::acl::dns;
using isc::acl::LoaderError;

namespace {

TEST(DNSACL, getRequestLoader) {
    dns::RequestLoader* l(&getRequestLoader());
    ASSERT_TRUE(l != NULL);
    EXPECT_EQ(l, &getRequestLoader());
    EXPECT_NO_THROW(l->load(Element::fromJSON("[{\"action\": \"DROP\"}]")));

    // Confirm it can load the ACl syntax acceptable to a default creator.
    // Tests to see whether the loaded rules work correctly will be in
    // other dedicated tests below.
    EXPECT_NO_THROW(l->load(Element::fromJSON("[{\"action\": \"DROP\","
                                              "  \"from\": \"192.0.2.1\"}]")));
}

// Check we can abbreviate the IP address lists and TSIG keys
TEST(DNSACL, abbreviated) {
    dns::RequestLoader* l(&getRequestLoader());

    EXPECT_NO_THROW(l->load(Element::fromJSON("[{\"action\": \"DROP\","
                                              "  \"from\": [\"127.0.0.1\","
                                              "             \"::1\"]}]")));
    EXPECT_NO_THROW(l->load(Element::fromJSON("[{\"action\": \"DROP\","
                                              "  \"key\": [\"key.example.\","
                                              "            \"other.\"]}]")));
}

class RequestCheckCreatorTest : public ::testing::Test {
protected:
    dns::internal::RequestCheckCreator creator_;

    typedef boost::shared_ptr<const dns::RequestCheck> ConstRequestCheckPtr;
    ConstRequestCheckPtr check_;
};

TEST_F(RequestCheckCreatorTest, names) {
    const vector<string> names = creator_.names();
    EXPECT_EQ(2, names.size());
    EXPECT_TRUE(find(names.begin(), names.end(), "from") != names.end());
    EXPECT_TRUE(find(names.begin(), names.end(), "key") != names.end());
}

TEST_F(RequestCheckCreatorTest, allowListAbbreviation) {
    EXPECT_TRUE(creator_.allowListAbbreviation());
}

// The following two tests check the creator for the form of
// 'from: "IP prefix"'.  We don't test many variants of prefixes, which
// are done in the tests for IPCheck.
TEST_F(RequestCheckCreatorTest, createIPv4Check) {
    check_ = creator_.create("from", Element::fromJSON("\"192.0.2.1\""),
                             getRequestLoader());
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
                             getRequestLoader());
    const dns::internal::RequestIPCheck& ipcheck =
        dynamic_cast<const dns::internal::RequestIPCheck&>(*check_);
    EXPECT_EQ(AF_INET6, ipcheck.getFamily());
    EXPECT_EQ(120, ipcheck.getPrefixlen());
    const vector<uint8_t> check_address(ipcheck.getAddress());
    ASSERT_EQ(16, check_address.size());
    const uint8_t expected_address[] = { 0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x53, 0x00 };
    EXPECT_TRUE(equal(check_address.begin(), check_address.end(),
                      expected_address));
}

TEST_F(RequestCheckCreatorTest, createTSIGKeyCheck) {
    check_ = creator_.create("key", Element::fromJSON("\"key.example.com\""),
                             getRequestLoader());
    const dns::internal::RequestKeyCheck& keycheck =
        dynamic_cast<const dns::internal::RequestKeyCheck&>(*check_);
    EXPECT_EQ(Name("key.example.com"), keycheck.getName());
}

TEST_F(RequestCheckCreatorTest, badCreate) {
    // Invalid name
    EXPECT_THROW(creator_.create("bad", Element::fromJSON("\"192.0.2.1\""),
                                 getRequestLoader()), LoaderError);

    // Invalid type of parameter
    EXPECT_THROW(creator_.create("from", Element::fromJSON("4"),
                                 getRequestLoader()),
                 isc::data::TypeError);
    EXPECT_THROW(creator_.create("from", Element::fromJSON("[]"),
                                 getRequestLoader()),
                 isc::data::TypeError);
    EXPECT_THROW(creator_.create("key", Element::fromJSON("1"),
                                 getRequestLoader()),
                 isc::data::TypeError);
    EXPECT_THROW(creator_.create("key", Element::fromJSON("{}"),
                                 getRequestLoader()),
                 isc::data::TypeError);

    // Syntax error for IPCheck
    EXPECT_THROW(creator_.create("from", Element::fromJSON("\"bad\""),
                                 getRequestLoader()),
                 isc::InvalidParameter);

    // Syntax error for Name (key) Check
    EXPECT_THROW(creator_.create("key", Element::fromJSON("\"bad..name\""),
                                 getRequestLoader()),
                 EmptyLabel);

    // NULL pointer
    EXPECT_THROW(creator_.create("from", ConstElementPtr(), getRequestLoader()),
                 LoaderError);
}

class RequestCheckTest : public ::testing::Test {
protected:
    typedef boost::shared_ptr<const dns::RequestCheck> ConstRequestCheckPtr;

    // A helper shortcut to create a single IP check for the given prefix.
    ConstRequestCheckPtr createIPCheck(const string& prefix) {
        return (creator_.create("from", Element::fromJSON(
                                    string("\"") + prefix + string("\"")),
                                getRequestLoader()));
    }

    // A helper shortcut to create a single Name (key) check for the given
    // name.
    ConstRequestCheckPtr createKeyCheck(const string& key_name) {
        return (creator_.create("key", Element::fromJSON(
                                    string("\"") + key_name + string("\"")),
                                getRequestLoader()));
    }

    // create a one time request context for a specific test.  Note that
    // getSockaddr() uses a static storage, so it cannot be called more than
    // once in a single test.
    const dns::RequestContext& getRequest4(const TSIGRecord* tsig = NULL) {
        ipaddr.reset(new IPAddress(tests::getSockAddr("192.0.2.1")));
        request.reset(new dns::RequestContext(*ipaddr, tsig));
        return (*request);
    }
    const dns::RequestContext& getRequest6(const TSIGRecord* tsig = NULL) {
        ipaddr.reset(new IPAddress(tests::getSockAddr("2001:db8::1")));
        request.reset(new dns::RequestContext(*ipaddr, tsig));
        return (*request);
    }

    // create a one time TSIG Record for a specific test.  The only parameter
    // of the record that matters is the key name; others are hardcoded with
    // arbitrarily chosen values.
    const TSIGRecord* getTSIGRecord(const string& key_name) {
        tsig_rdata.reset(new any::TSIG(TSIGKey::HMACMD5_NAME(), 0, 0, 0, NULL,
                                       0, 0, 0, NULL));
        tsig.reset(new TSIGRecord(Name(key_name), *tsig_rdata));
        return (tsig.get());
    }

private:
    scoped_ptr<IPAddress> ipaddr;
    scoped_ptr<dns::RequestContext> request;
    scoped_ptr<any::TSIG> tsig_rdata;
    scoped_ptr<TSIGRecord> tsig;
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

TEST_F(RequestCheckTest, checkTSIGKey) {
    EXPECT_TRUE(createKeyCheck("key.example.com")->matches(
                    getRequest4(getTSIGRecord("key.example.com"))));
    EXPECT_FALSE(createKeyCheck("key.example.com")->matches(
                     getRequest4(getTSIGRecord("badkey.example.com"))));

    // Same for IPv6 (which shouldn't matter)
    EXPECT_TRUE(createKeyCheck("key.example.com")->matches(
                    getRequest6(getTSIGRecord("key.example.com"))));
    EXPECT_FALSE(createKeyCheck("key.example.com")->matches(
                     getRequest6(getTSIGRecord("badkey.example.com"))));

    // by default the test request doesn't have a TSIG key, which shouldn't
    // match any key checks.
    EXPECT_FALSE(createKeyCheck("key.example.com")->matches(getRequest4()));
    EXPECT_FALSE(createKeyCheck("key.example.com")->matches(getRequest6()));
}

// The following tests test only the creators are registered, they are tested
// elsewhere

TEST(DNSACL, notLoad) {
    EXPECT_NO_THROW(getRequestLoader().loadCheck(isc::data::Element::fromJSON(
        "{\"NOT\": {\"from\": \"192.0.2.1\"}}")));
}

TEST(DNSACL, allLoad) {
    EXPECT_NO_THROW(getRequestLoader().loadCheck(isc::data::Element::fromJSON(
        "{\"ALL\": [{\"from\": \"192.0.2.1\"}]}")));
}

TEST(DNSACL, anyLoad) {
    EXPECT_NO_THROW(getRequestLoader().loadCheck(isc::data::Element::fromJSON(
        "{\"ANY\": [{\"from\": \"192.0.2.1\"}]}")));
}

}
