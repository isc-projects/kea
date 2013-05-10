// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <util/memory_segment_local.h>
#include <util/memory_segment_mapped.h>

#include <datasrc/memory/segment_object_holder.h>

#include <gtest/gtest.h>

using namespace isc::util;
using namespace isc::datasrc::memory;
using namespace isc::datasrc::memory::detail;

namespace {
const int TEST_ARG_VAL = 42;    // arbitrary chosen magic number
const char* const mapped_file = TEST_DATA_BUILDDIR "/test.mapped";

class TestObject {
public:
    static void destroy(MemorySegment& sgmt, TestObject* obj, int arg) {
        sgmt.deallocate(obj, sizeof(*obj));
        EXPECT_EQ(TEST_ARG_VAL, arg);
    }
};

void
useHolder(MemorySegment& sgmt, TestObject* obj, bool release) {
    // Create a holder object, check the return value of get(), and,
    // if requested, release the held object.  At the end of function
    // the holder is destructed, and if the object hasn't been released by
    // then, it should be deallocated.  Passed argument is checked in its
    // deallocate().

    typedef SegmentObjectHolder<TestObject, int> HolderType;
    HolderType holder(sgmt, obj, TEST_ARG_VAL);
    EXPECT_EQ(obj, holder.get());
    if (release) {
        EXPECT_EQ(obj, holder.release());
    }
}

TEST(SegmentObjectHolderTest, foo) {
    MemorySegmentLocal sgmt;
    void* p = sgmt.allocate(sizeof(TestObject));
    TestObject* obj = new(p) TestObject;

    // Use holder, and release the content.  The memory shouldn't be
    // deallocated.
    useHolder(sgmt, obj, true);
    EXPECT_FALSE(sgmt.allMemoryDeallocated());

    // Use holder, and let it deallocate the object.  The memory segment
    // should now be empty.
    useHolder(sgmt, obj, false);
    EXPECT_TRUE(sgmt.allMemoryDeallocated());
}

// Keep allocating bigger and bigger chunks of data until the allocation
// fails with growing the segment.
void
allocateUntilGrows(MemorySegment& segment, size_t& current_size) {
    // Create an object that will not be explicitly deallocated.
    // It must be deallocated by the segment holder and even in case
    // the position moved.
    void *object_memory = segment.allocate(sizeof(TestObject));
    TestObject* object = new(object_memory) TestObject;
    SegmentObjectHolder<TestObject, int> holder(segment, object, TEST_ARG_VAL);
    while (true) {
        void* data = segment.allocate(current_size);
        segment.deallocate(data, current_size);
        current_size *= 2;
    }
}

// Check that the segment thing releases stuff even in case it throws
// SegmentGrown exception and the thing moves address
TEST(SegmentObjectHolderTest, grow) {
    MemorySegmentMapped segment(mapped_file,
                                isc::util::MemorySegmentMapped::CREATE_ONLY);
    // Allocate a bit of memory, to get a unique address
    void* mark = segment.allocate(1);
    segment.setNamedAddress("mark", mark);
    // Try allocating bigger and bigger chunks of data until the segment
    // actually relocates
    size_t alloc_size = 1024;
    while (mark == segment.getNamedAddress("mark")) {
        EXPECT_THROW(allocateUntilGrows(segment, alloc_size),
                     MemorySegmentGrown);
    }
    mark = segment.getNamedAddress("mark");
    segment.clearNamedAddress("mark");
    segment.deallocate(mark, 1);
    EXPECT_TRUE(segment.allMemoryDeallocated());
    // Remove the file
    EXPECT_EQ(0, unlink(mapped_file));
}

}
