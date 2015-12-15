// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <util/tests/memory_segment_common_unittest.h>

#include <util/memory_segment_local.h>
#include <exceptions/exceptions.h>
#include <gtest/gtest.h>
#include <memory>
#include <limits.h>

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

/// @todo: disabled, see ticket #3510
TEST(MemorySegmentLocal, DISABLED_TestTooMuchMemory) {
    auto_ptr<MemorySegment> segment(new MemorySegmentLocal());

    // Although it should be perfectly fine to use the ULONG_MAX
    // instead of LONG_MAX as the size_t value should be unsigned,
    // Valgrind appears to be using the signed value and hence the
    // maximum positive value is LONG_MAX for Valgrind. But, this
    // should be sufficient to test the "too much memory" conditions.
    EXPECT_THROW(segment->allocate(LONG_MAX), bad_alloc);
}

TEST(MemorySegmentLocal, TestBadDeallocate) {
    auto_ptr<MemorySegment> segment(new MemorySegmentLocal());

    // By default, nothing is allocated.
    EXPECT_TRUE(segment->allMemoryDeallocated());

    void* ptr = segment->allocate(1024);

    // Now, we have an allocation:
    EXPECT_FALSE(segment->allMemoryDeallocated());

    // This should not throw
    EXPECT_NO_THROW(segment->deallocate(ptr, 1024));

    // Now, we have an deallocated everything:
    EXPECT_TRUE(segment->allMemoryDeallocated());

    ptr = segment->allocate(1024);

    // Now, we have another allocation:
    EXPECT_FALSE(segment->allMemoryDeallocated());

    // This should throw as the size passed to deallocate() is larger
    // than what was allocated.
    EXPECT_THROW(segment->deallocate(ptr, 2048), isc::OutOfRange);

    // This should not throw
    EXPECT_NO_THROW(segment->deallocate(ptr, 1024));

    // Now, we have an deallocated everything:
    EXPECT_TRUE(segment->allMemoryDeallocated());
}

TEST(MemorySegmentLocal, TestNullDeallocate) {
    auto_ptr<MemorySegment> segment(new MemorySegmentLocal());

    // By default, nothing is allocated.
    EXPECT_TRUE(segment->allMemoryDeallocated());

    // NULL deallocation is a no-op.
    EXPECT_NO_THROW(segment->deallocate(NULL, 1024));

    // This should still return true.
    EXPECT_TRUE(segment->allMemoryDeallocated());
}

TEST(MemorySegmentLocal, namedAddress) {
    MemorySegmentLocal segment;
    isc::util::test::checkSegmentNamedAddress(segment, true);
}

} // anonymous namespace
