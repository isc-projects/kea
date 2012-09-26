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

#include <datasrc/memory/segment_object_holder.h>

#include <gtest/gtest.h>

using namespace isc::util;
using namespace isc::datasrc::memory;
using namespace isc::datasrc::memory::detail;

namespace {
const int TEST_ARG_VAL = 42;    // arbitrary chosen magic number

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
}
