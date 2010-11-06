// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>

#include <dns/rrclass.h>

#include "../asiolink.h"
#include "../zone_entry.h"
#include "../address_request_callback.h"

#include "nsas_test.h"

using namespace asiolink;
using namespace std;
using namespace boost;
using namespace isc::dns;

namespace isc {
namespace nsas {

// String constants.  These should end in a dot.
static const std::string EXAMPLE_CO_UK("example.co.uk.");

/// \brief Test Fixture Class
class ZoneEntryTest : public ::testing::Test {
protected:

};

/// Tests of the default constructor
TEST_F(ZoneEntryTest, DefaultConstructor) {

    // Default constructor should not create any RRsets
    ZoneEntry alpha(EXAMPLE_CO_UK, RRClass::IN().getCode());
    EXPECT_EQ(EXAMPLE_CO_UK, alpha.getName());
    EXPECT_EQ(RRClass::IN().getCode(), alpha.getClass());
}

namespace {
// Just something that can be created and passed
class Callback : public AddressRequestCallback {
    public:
        void success(const asiolink::IOAddress&) { };
        void unreachable() { };
};
}

TEST_F(ZoneEntryTest, Callbacks) {
    const size_t count(3);
    shared_ptr<AddressRequestCallback> callbacks[count];

    ZoneEntry zone(EXAMPLE_CO_UK, RRClass::IN().getCode());
    EXPECT_FALSE(zone.hasCallbacks());
    for (size_t i(0); i < count; ++ i) {
        zone.addCallback(callbacks[i] = shared_ptr<AddressRequestCallback>(
            new Callback));
    }
    for (size_t i(0); i < count; ++ i) {
        ASSERT_TRUE(zone.hasCallbacks());
        EXPECT_EQ(callbacks[i], zone.popCallback());
    }
    EXPECT_FALSE(zone.hasCallbacks());
}

}   // namespace nsas
}   // namespace isc
