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

#include <acl/loader.h>

#include <string>
#include <gtest/gtest.h>

using namespace isc::acl;
using namespace std;
using isc::data::ConstElementPtr;

namespace {

// Just for convenience, create JSON objects from JSON string
ConstElementPtr el(const string& JSON) {
    return (isc::data::Element::fromJSON(JSON));
}

// We don't use the EXPECT_THROW macro, as it doesn't allow us
// to examine the exception. We want to check the element is stored
// there as well.
void testActionLoaderException(const string& JSON) {
    SCOPED_TRACE("Should throw with input: " + JSON);
    ConstElementPtr elem(el(JSON));
    try {
        defaultActionLoader(elem);
        FAIL() << "It did not throw";
    }
    catch (const LoaderError& error) {
        // Yes, comparing for pointer equality, that is enough, it
        // should return the exact instance of the JSON object
        EXPECT_EQ(elem, error.element());
    }
}

// Test the defaultActionLoader function
TEST(LoaderHelpers, DefaultActionLoader) {
    // First the three valid inputs
    EXPECT_EQ(ACCEPT, defaultActionLoader(el("\"ACCEPT\"")));
    EXPECT_EQ(REJECT, defaultActionLoader(el("\"REJECT\"")));
    EXPECT_EQ(DROP, defaultActionLoader(el("\"DROP\"")));
    // Now few invalid ones
    // String, but unknown one
    testActionLoaderException("\"UNKNOWN\"");
    testActionLoaderException("42");
    testActionLoaderException("true");
    testActionLoaderException("null");
    testActionLoaderException("[]");
    testActionLoaderException("{}");
}

Loader<bool> loader;

}
