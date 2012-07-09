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

#include "util/memory_segment_local.h"
#include <gtest/gtest.h>
#include <memory>

using namespace std;
using namespace isc::util;

namespace {

TEST(MemorySegmentLocal, TestLocal) {
    auto_ptr<MemorySegment> segment(new MemorySegmentLocal());

    // By default, nothing is allocated.
    EXPECT_TRUE(segment->allMemoryDeallocated());

    void* ptr = segment->allocate(1024);

    // Now, we have an allocation:
    EXPECT_FALSE(segment->allMemoryDeallocated());

    void* ptr2 = segment->allocate(42);

    // Still:
    EXPECT_FALSE(segment->allMemoryDeallocated());

    // These should not fail, because the buffers have been allocated.
    EXPECT_NO_FATAL_FAILURE(memset(ptr, 0, 1024));
    EXPECT_NO_FATAL_FAILURE(memset(ptr, 0, 42));

    segment->deallocate(ptr, 1024);

    // Still:
    EXPECT_FALSE(segment->allMemoryDeallocated());

    segment->deallocate(ptr2, 42);

    // Now, we have an deallocated everything:
    EXPECT_TRUE(segment->allMemoryDeallocated());
}

} // anonymous namespace
