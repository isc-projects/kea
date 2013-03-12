// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <gtest/gtest.h>

#include <cstring>
#include <stdint.h>

namespace isc {
namespace util {
namespace test {

void
checkSegmentNamedAddress(MemorySegment& segment, bool out_of_segment_ok) {
    // If not exist, null pointer will be returned.
    EXPECT_EQ(static_cast<void*>(0), segment.getNamedAddress("test address"));

    // Now set it
    void* ptr32 = segment.allocate(sizeof(uint32_t));
    const uint32_t test_val = 42;
    std::memcpy(ptr32, &test_val, sizeof(test_val));
    EXPECT_FALSE(segment.setNamedAddress("test address", ptr32));

    // we can now get it; the stored value should be intact.
    EXPECT_EQ(ptr32, segment.getNamedAddress("test address"));
    EXPECT_EQ(test_val, *static_cast<const uint32_t*>(ptr32));

    // Override it.
    void* ptr16 = segment.allocate(sizeof(uint16_t));
    const uint16_t test_val16 = 4200;
    std::memcpy(ptr16, &test_val16, sizeof(test_val16));
    EXPECT_FALSE(segment.setNamedAddress("test address", ptr16));
    EXPECT_EQ(ptr16, segment.getNamedAddress("test address"));
    EXPECT_EQ(test_val16, *static_cast<const uint16_t*>(ptr16));

    // Clear it.  Then we won't be able to find it any more.
    EXPECT_TRUE(segment.clearNamedAddress("test address"));
    EXPECT_EQ(static_cast<void*>(0), segment.getNamedAddress("test address"));

    // duplicate attempt of clear will result in false as it doesn't exist.
    EXPECT_FALSE(segment.clearNamedAddress("test address"));

    // Setting NULL is okay.
    EXPECT_FALSE(segment.setNamedAddress("null address", 0));
    EXPECT_EQ(static_cast<void*>(0), segment.getNamedAddress("null address"));

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
    EXPECT_TRUE(segment.allMemoryDeallocated()); // now everything is gone
}

}
}
}
