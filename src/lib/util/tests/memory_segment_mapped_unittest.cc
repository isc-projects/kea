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

#include <util/memory_segment_mapped.h>

#include <gtest/gtest.h>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/scoped_ptr.hpp>

using namespace isc::util;
using boost::scoped_ptr;

namespace {

const char* const mapped_file = TEST_DATA_BUILDDIR "/test.mapped";
const size_t DEFAULT_INITIAL_SIZE = 32 * 1024; // intentionally hardcoded

class MemorySegmentMappedTest : public ::testing::Test {
protected:
    MemorySegmentMappedTest() {
        // Make sure the mapped file doesn't exist; actually it shouldn't
        // exist in normal cases so remove() should normally fail (returning
        // false), but we don't care.
        boost::interprocess::file_mapping::remove(mapped_file);

        // Create a new segment with a new file.  It also confirms the
        // behavior of this mode of constructor.
        segment_.reset(new MemorySegmentMapped(mapped_file, true));
    }

    ~MemorySegmentMappedTest() {
        segment_.reset();
        boost::interprocess::file_mapping::remove(mapped_file);
    }

    scoped_ptr<MemorySegmentMapped> segment_;
};

TEST_F(MemorySegmentMappedTest, createAndModify) {
    // We are going to do the same set of basic tests twice; one after creating
    // the mapped file, the other by re-opening the existing file in the
    // read-write mode.
    for (int i = 0; i < 2; ++i) {
        // It should have the default size (intentionally hardcoded)
        EXPECT_EQ(DEFAULT_INITIAL_SIZE, segment_->getSize());

        // By default, nothing is allocated.
        EXPECT_TRUE(segment_->allMemoryDeallocated());

        void* ptr = segment_->allocate(1024);
        EXPECT_NE(static_cast<void*>(0), ptr);

        // Now, we have an allocation:
        EXPECT_FALSE(segment_->allMemoryDeallocated());

        // deallocate it; it shouldn't cause disruption.
        segment_->deallocate(ptr, 1024);

        EXPECT_TRUE(segment_->allMemoryDeallocated());

        // re-open it.
        segment_.reset(new MemorySegmentMapped(mapped_file, false));
    }
}

TEST_F(MemorySegmentMappedTest, createWithSize) {
    boost::interprocess::file_mapping::remove(mapped_file);

    // Re-create the mapped file with a non-default initial size, and confirm
    // the size is actually the specified one.
    segment_.reset(new MemorySegmentMapped(mapped_file, true, 64 * 1024));
    EXPECT_NE(DEFAULT_INITIAL_SIZE, 64 * 1024);
    EXPECT_EQ(64 * 1024, segment_->getSize());
}

TEST_F(MemorySegmentMappedTest, openFail) {
    // The given file is directory
    EXPECT_THROW(MemorySegmentMapped("/", true), MemorySegmentOpenError);

    // file doesn't exist and directory isn't writable (we assume the root
    // directory is not writable for the user running the test).
    EXPECT_THROW(MemorySegmentMapped("/test.mapped", true),
                 MemorySegmentOpenError);

    // file doesn't exist and it's read-only (so open-only)
    EXPECT_THROW(MemorySegmentMapped(TEST_DATA_BUILDDIR "/nosuchfile.mapped"),
                 MemorySegmentOpenError);
    // Likewise.  read-write mode but creation is suppressed.
    EXPECT_THROW(MemorySegmentMapped(TEST_DATA_BUILDDIR "/nosuchfile.mapped",
                                     false),
                 MemorySegmentOpenError);
}

TEST_F(MemorySegmentMappedTest, allocate) {
    // Various case of allocation.  The simplest cases are covered above.

    // (Clearly) exceeding the available size, which should cause growing
    // the segment
    EXPECT_THROW(segment_->allocate(DEFAULT_INITIAL_SIZE + 1),
                 MemorySegmentGrown);
    // The size should have been doubled.
    EXPECT_EQ(DEFAULT_INITIAL_SIZE * 2,segment_->getSize());
    // In this case it should now succeed.
    void* ptr = segment_->allocate(DEFAULT_INITIAL_SIZE + 1);
    EXPECT_NE(static_cast<void*>(0), ptr);

    EXPECT_FALSE(segment_->allMemoryDeallocated());

    // Same set of checks, but for a larger size.
    EXPECT_THROW(segment_->allocate(DEFAULT_INITIAL_SIZE * 10),
                 MemorySegmentGrown);
    ptr = segment_->allocate(DEFAULT_INITIAL_SIZE * 10);
    EXPECT_NE(static_cast<void*>(0), ptr);
}

TEST_F(MemorySegmentMappedTest, DISABLED_basics) {
    MemorySegmentMapped segment(mapped_file);

    // By default, nothing is allocated.
    EXPECT_TRUE(segment.allMemoryDeallocated());

#if 0
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
#endif
}

/*
TEST(MemorySegmentLocal, TestTooMuchMemory) {
    auto_ptr<MemorySegment> segment(new MemorySegmentLocal());

    EXPECT_THROW(segment->allocate(ULONG_MAX), bad_alloc);
}
*/

/*
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
*/

/*
TEST(MemorySegmentLocal, TestNullDeallocate) {
    auto_ptr<MemorySegment> segment(new MemorySegmentLocal());

    // By default, nothing is allocated.
    EXPECT_TRUE(segment->allMemoryDeallocated());

    // NULL deallocation is a no-op.
    EXPECT_NO_THROW(segment->deallocate(NULL, 1024));

    // This should still return true.
    EXPECT_TRUE(segment->allMemoryDeallocated());
}
*/

}
