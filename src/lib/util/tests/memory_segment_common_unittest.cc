// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <util/memory_segment.h>

#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <cstring>
#include <stdint.h>

namespace isc {
namespace util {
namespace test {

void
checkSegmentNamedAddress(MemorySegment& segment, bool out_of_segment_ok) {
    // NULL name is not allowed.
    EXPECT_THROW(segment.getNamedAddress(NULL), InvalidParameter);

    // If the name does not exist, false should be returned.
    EXPECT_FALSE(segment.getNamedAddress("test address").first);

    // Now set it
    void* ptr32 = segment.allocate(sizeof(uint32_t));
    const uint32_t test_val = 42;
    *static_cast<uint32_t*>(ptr32) = test_val;
    EXPECT_FALSE(segment.setNamedAddress("test address", ptr32));

    // NULL name isn't allowed.
    EXPECT_THROW(segment.setNamedAddress(NULL, ptr32), InvalidParameter);
    EXPECT_THROW(segment.getNamedAddress(NULL), InvalidParameter);
    EXPECT_THROW(segment.clearNamedAddress(NULL), InvalidParameter);

    // Empty names are not allowed.
    EXPECT_THROW(segment.setNamedAddress("", ptr32), InvalidParameter);
    EXPECT_THROW(segment.getNamedAddress(""), InvalidParameter);
    EXPECT_THROW(segment.clearNamedAddress(""), InvalidParameter);

    // Names beginning with _ are not allowed.
    EXPECT_THROW(segment.setNamedAddress("_foo", ptr32), InvalidParameter);
    EXPECT_THROW(segment.getNamedAddress("_foo"), InvalidParameter);
    EXPECT_THROW(segment.clearNamedAddress("_foo"), InvalidParameter);

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
    EXPECT_THROW(segment.clearNamedAddress(NULL), InvalidParameter);
    EXPECT_TRUE(segment.allMemoryDeallocated()); // now everything is gone
}

}
}
}
