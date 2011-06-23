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

#include <acl/dns.h>
#include <gtest/gtest.h>

using namespace isc::acl::dns;

namespace {

// Tests that the getLoader actually returns something, returns the same every
// time and the returned value can be used to anything. It is not much of a
// test, but the getLoader is not much of a function.
TEST(DNSACL, getLoader) {
    Loader* l(&getLoader());
    ASSERT_TRUE(l != NULL);
    EXPECT_EQ(l, &getLoader());
    EXPECT_NO_THROW(l->load(isc::data::Element::fromJSON(
        "[{\"action\": \"DROP\"}]")));
    // TODO Test that the things we should register by default, like IP based
    // check, are loaded.
}

}
