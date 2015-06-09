// Copyright (C) 2013, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <util/memory_segment.h>

#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <util/unittests/test_exceptions.h>

#include <cstring>
#include <stdint.h>

namespace isc {
namespace util {
namespace test {

void
checkSegmentNamedAddress(MemorySegment& segment, bool out_of_segment_ok) {
    // NULL name is not allowed.
    EXPECT_THROW_WITH(segment.getNamedAddress(NULL), InvalidParameter,
                      "NULL is invalid for a name.");

    // If the name does not exist, false should be returned.
    EXPECT_FALSE(segment.getNamedAddress("test address").first);

    // Now set it
    void* ptr32 = segment.allocate(sizeof(uint32_t));
    const uint32_t test_val = 42;
    *static_cast<uint32_t*>(ptr32) = test_val;
    EXPECT_FALSE(segment.setNamedAddress("test address", ptr32));

    // NULL name isn't allowed.
    EXPECT_THROW_WITH(segment.setNamedAddress(NULL, ptr32), InvalidParameter,
                      "NULL is invalid for a name.");
    EXPECT_THROW_WITH(segment.getNamedAddress(NULL), InvalidParameter,
                      "NULL is invalid for a name.");
    EXPECT_THROW_WITH(segment.clearNamedAddress(NULL), InvalidParameter,
                      "NULL is invalid for a name.");

    // Empty names are not allowed.
    EXPECT_THROW_WITH(segment.setNamedAddress("", ptr32), InvalidParameter,
                      "Empty names are invalid.");
    EXPECT_THROW_WITH(segment.getNamedAddress(""), InvalidParameter,
                      "Empty names are invalid.");
    EXPECT_THROW_WITH(segment.clearNamedAddress(""), InvalidParameter,
                      "Empty names are invalid.");

    // Names beginning with _ are not allowed.
    EXPECT_THROW_WITH(segment.setNamedAddress("_foo", ptr32),
                      InvalidParameter, "Names beginning with '_' are "
                      "reserved for internal use only.");
    EXPECT_THROW_WITH(segment.getNamedAddress("_foo"), InvalidParameter,
                      "Names beginning with '_' are reserved for "
                      "internal use only.");
    EXPECT_THROW_WITH(segment.clearNamedAddress("_foo"), InvalidParameter,
                      "Names beginning with '_' are reserved for "
                      "internal use only.");

    // we can now get it; the stored value should be intact.
    MemorySegment::NamedAddressResult result =
        segment.getNamedAddress("test address");
    EXPECT_TRUE(result.first);
    EXPECT_EQ(test_val, *static_cast<const uint32_t*>(result.second));

    // Override it.
    void* ptr16 = segment.allocate(sizeof(uint16_t));
    const uint16_t test_val16 = 4200;
    *static_cast<uint16_t*>(ptr16) = test_val16;
    EXPECT_FALSE(segment.setNamedAddress("test address", ptr16));
    result = segment.getNamedAddress("test address");
    EXPECT_TRUE(result.first);
    EXPECT_EQ(test_val16, *static_cast<const uint16_t*>(result.second));

    // Clear it.  Then we won't be able to find it any more.
    EXPECT_TRUE(segment.clearNamedAddress("test address"));
    EXPECT_FALSE(segment.getNamedAddress("test address").first);

    // duplicate attempt of clear will result in false as it doesn't exist.
    EXPECT_FALSE(segment.clearNamedAddress("test address"));

    // Setting NULL is okay.
    EXPECT_FALSE(segment.setNamedAddress("null address", NULL));
    result = segment.getNamedAddress("null address");
    EXPECT_TRUE(result.first);
    EXPECT_FALSE(result.second);

    // If the underlying implementation performs explicit check against
    // out-of-segment address, confirm the behavior.
    if (!out_of_segment_ok) {
        uint8_t ch = 'A';
        EXPECT_THROW(segment.setNamedAddress("local address", &ch),
                     MemorySegmentError);
    }

    // clean them up all
    segment.deallocate(ptr32, sizeof(uint32_t));
    EXPECT_FALSE(segment.allMemoryDeallocated()); // not fully deallocated
    segment.deallocate(ptr16, sizeof(uint16_t));  // not yet
    EXPECT_FALSE(segment.allMemoryDeallocated());
    EXPECT_TRUE(segment.clearNamedAddress("null address"));
    // null name isn't allowed:
    EXPECT_THROW_WITH(segment.clearNamedAddress(NULL), InvalidParameter,
                      "NULL is invalid for a name.");
    EXPECT_TRUE(segment.allMemoryDeallocated()); // now everything is gone
}

}
}
}
