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

#include <config.h>

#include <util/memory_segment_local.h>
#include <util/memory_segment_mapped.h>

#include <datasrc/memory/segment_object_holder.h>

#ifdef USE_SHARED_MEMORY
#include <boost/interprocess/managed_mapped_file.hpp>
#endif

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
        EXPECT_TRUE(obj);
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
    HolderType holder(sgmt, TEST_ARG_VAL);
    holder.set(obj);
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

// Test nothing bad happens if the holder is not set before it is destroyed
TEST(SegmentObjectHolderTest, destroyNotSet) {
    MemorySegmentLocal sgmt;
    {
        typedef SegmentObjectHolder<TestObject, int> HolderType;
        HolderType holder(sgmt, TEST_ARG_VAL);
    }
    EXPECT_TRUE(sgmt.allMemoryDeallocated());
}

#ifdef USE_SHARED_MEMORY
// Keep allocating bigger and bigger chunks of data until the allocation
// fails with growing the segment.
void
allocateUntilGrows(MemorySegment& segment, size_t& current_size) {
    // Create an object that will not be explicitly deallocated.
    // It must be deallocated by the segment holder and even in case
    // the position moved.
    void *object_memory = segment.allocate(sizeof(TestObject));
    TestObject* object = new(object_memory) TestObject;
    SegmentObjectHolder<TestObject, int> holder(segment, TEST_ARG_VAL);
    holder.set(object);
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

    // We'd like to cause 'mark' will be mapped at a different address on
    // MemorySegmentGrown; there doesn't seem to be a reliable and safe way
    // to cause this situation, but opening another mapped region seems to
    // often work in practice.  We use Boost managed_mapped_file directly
    // to ignore the imposed file lock with MemorySegmentMapped.
    using boost::interprocess::managed_mapped_file;
    using boost::interprocess::open_only;
    managed_mapped_file mapped_sgmt(open_only, mapped_file);

    // Try allocating bigger and bigger chunks of data until the segment
    // actually relocates
    size_t alloc_size = 1024;
    EXPECT_THROW(allocateUntilGrows(segment, alloc_size), MemorySegmentGrown);
    // Confirm it's now mapped at a different address.
    EXPECT_NE(mark, segment.getNamedAddress("mark").second)
        << "portability assumption for the test doesn't hold; "
        "disable the test by setting env variable GTEST_FILTER to "
        "'-SegmentObjectHolderTest.grow'";
    mark = segment.getNamedAddress("mark").second;
    segment.clearNamedAddress("mark");
    segment.deallocate(mark, 1);
    EXPECT_TRUE(segment.allMemoryDeallocated());
    // Remove the file
    EXPECT_EQ(0, unlink(mapped_file));
}
#endif

}
