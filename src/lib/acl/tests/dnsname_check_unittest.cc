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

#include <dns/name.h>

#include <acl/dnsname_check.h>

using namespace isc::dns;
using namespace isc::acl::dns;

// Provide a specialization of the DNSNameCheck::matches() method.
namespace isc  {
namespace acl {
namespace dns {
template <>
bool NameCheck<Name>::matches(const Name& name) const {
    return (name_ == name);
}
} // namespace dns
} // namespace acl
} // namespace isc

namespace {
TEST(DNSNameCheck, construct) {
    EXPECT_EQ(Name("example.com"),
              NameCheck<Name>(Name("example.com")).getName());

    // Construct the same check with an explicit trailing dot.  Should result
    // in the same result.
    EXPECT_EQ(Name("example.com"),
              NameCheck<Name>(Name("example.com.")).getName());
}

TEST(DNSNameCheck, match) {
    NameCheck<Name> check(Name("example.com"));
    EXPECT_TRUE(check.matches(Name("example.com")));
    EXPECT_FALSE(check.matches(Name("example.org")));

    // comparison is case insensitive
    EXPECT_TRUE(check.matches(Name("EXAMPLE.COM")));

    // this is exact match.  so super/sub domains don't match
    EXPECT_FALSE(check.matches(Name("com")));
    EXPECT_FALSE(check.matches(Name("www.example.com")));
}
} // Unnamed namespace
