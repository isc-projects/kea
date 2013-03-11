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

#include <cstdlib>
#include <cstring>
#include <limits>
#include <stdexcept>

using namespace isc::util;
using boost::scoped_ptr;

namespace {

const char* const mapped_file = TEST_DATA_BUILDDIR "/test.mapped";
const size_t DEFAULT_INITIAL_SIZE = 32 * 1024; // intentionally hardcoded

class MemorySegmentMappedTest : public ::testing::Test {
protected:
    MemorySegmentMappedTest() {
        resetSegment();
    }

    ~MemorySegmentMappedTest() {
        segment_.reset();
        //boost::interprocess::file_mapping::remove(mapped_file);
    }

    // For initialization and for tests after the segment possibly becomes
    // broken.
    void resetSegment() {
        segment_.reset();
        boost::interprocess::file_mapping::remove(mapped_file);
        segment_.reset(new MemorySegmentMapped(mapped_file, true));
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
    EXPECT_EQ(DEFAULT_INITIAL_SIZE * 2, segment_->getSize());
    // In this case it should now succeed.
    void* ptr = segment_->allocate(DEFAULT_INITIAL_SIZE + 1);
    EXPECT_NE(static_cast<void*>(0), ptr);

    EXPECT_FALSE(segment_->allMemoryDeallocated());

    // Same set of checks, but for a larger size.
    EXPECT_THROW(segment_->allocate(DEFAULT_INITIAL_SIZE * 10),
                 MemorySegmentGrown);
    // the segment should have grown to the minimum size that could allocate
    // the given size of memory.
    EXPECT_EQ(DEFAULT_INITIAL_SIZE * 16, segment_->getSize());
    // And allocate() should now succeed.
    ptr = segment_->allocate(DEFAULT_INITIAL_SIZE * 10);
    EXPECT_NE(static_cast<void*>(0), ptr);

    // (we'll left the regions created in the file there; the entire file
    // will be removed at the end of the test)
}

TEST_F(MemorySegmentMappedTest, badAllocate) {
    // Make the mapped file non-writable; managed_mapped_file::grow() will
    // fail, resulting in std::bad_alloc
    const std::string chmod_cmd = "chmod 444 " + std::string(mapped_file);
    std::system(chmod_cmd.c_str());
    EXPECT_THROW(segment_->allocate(DEFAULT_INITIAL_SIZE * 2), std::bad_alloc);
}

// XXX: this test can cause too strong side effect (creating a very large
// file), so we disable it by default
TEST_F(MemorySegmentMappedTest, DISABLED_allocateHuge) {
    EXPECT_THROW(segment_->allocate(std::numeric_limits<size_t>::max()),
                 std::bad_alloc);
}

TEST_F(MemorySegmentMappedTest, badDeallocate) {
    void* ptr = segment_->allocate(4);
    EXPECT_NE(static_cast<void*>(0), ptr);

    segment_->deallocate(ptr, 4); // this is okay
    // This is duplicate dealloc; should trigger assertion failure.
    EXPECT_DEATH_IF_SUPPORTED({segment_->deallocate(ptr, 4);}, "");
    resetSegment();             // the segment is possibly broken; reset it.

    // Deallocating at an invalid address; this would result in crash (the
    // behavior may not be portable enough; if so we should disable it by
    // default).
    ptr = segment_->allocate(4);
    EXPECT_NE(static_cast<void*>(0), ptr);
    EXPECT_DEATH_IF_SUPPORTED({
            segment_->deallocate(static_cast<char*>(ptr) + 1, 3);
        }, "");
    resetSegment();

    // Invalid size; this implementation doesn't detect such errors.
    ptr = segment_->allocate(4);
    EXPECT_NE(static_cast<void*>(0), ptr);
    segment_->deallocate(ptr, 8);
    EXPECT_TRUE(segment_->allMemoryDeallocated());
}

TEST_F(MemorySegmentMappedTest, namedAddress) {
    // If not exist, null pointer will be returned.
    EXPECT_EQ(static_cast<void*>(0), segment_->getNamedAddress("test address"));

    // Now set it
    void* ptr32 = segment_->allocate(sizeof(uint32_t));
    const uint32_t test_val = 42;
    std::memcpy(ptr32, &test_val, sizeof(test_val));
    segment_->setNamedAddress("test address", ptr32);

    // we can now get it; the stored value should be intact.
    EXPECT_EQ(ptr32, segment_->getNamedAddress("test address"));
    EXPECT_EQ(test_val, *static_cast<const uint32_t*>(ptr32));

    // Override it.
    void* ptr16 = segment_->allocate(sizeof(uint16_t));
    const uint16_t test_val16 = 4200;
    std::memcpy(ptr16, &test_val16, sizeof(test_val16));
    segment_->setNamedAddress("test address", ptr16);
    EXPECT_EQ(ptr16, segment_->getNamedAddress("test address"));
    EXPECT_EQ(test_val16, *static_cast<const uint16_t*>(ptr16));

    // Clear it.  Then we won't be able to find it any more.
    EXPECT_TRUE(segment_->clearNamedAddress("test address"));
    EXPECT_EQ(static_cast<void*>(0), segment_->getNamedAddress("test address"));

    // duplicate attempt of clear will result in false as it doesn't exist.
    EXPECT_FALSE(segment_->clearNamedAddress("test address"));

    // Setting NULL is okay.
    segment_->setNamedAddress("null address", 0);
    EXPECT_EQ(static_cast<void*>(0), segment_->getNamedAddress("null address"));

    // Setting or out-of-segment address is prohibited, and this implementation
    // detects and rejects it.
    uint8_t ch = 'A';
    EXPECT_THROW(segment_->setNamedAddress("local address", &ch),
                 MemorySegmentError);

    // Set it again and read it in the read-only mode.
    segment_->setNamedAddress("test address", ptr16);
    MemorySegmentMapped segment_ro(mapped_file);
    EXPECT_TRUE(segment_ro.getNamedAddress("test address"));
    EXPECT_EQ(test_val16, *static_cast<const uint16_t*>(
                  segment_ro.getNamedAddress("test address")));
    EXPECT_EQ(static_cast<void*>(0),
              segment_ro.getNamedAddress("null address"));

    // clean them up all
    segment_->deallocate(ptr32, sizeof(uint32_t));
    segment_->deallocate(ptr16, sizeof(uint32_t));
    EXPECT_TRUE(segment_->clearNamedAddress("test address"));
    EXPECT_TRUE(segment_->clearNamedAddress("null address"));
    EXPECT_TRUE(segment_->allMemoryDeallocated());
}

TEST_F(MemorySegmentMappedTest, violateReadOnly) {
    // If the segment is opened in the read only mode, modification attempt
    // will result in crash.
    EXPECT_DEATH_IF_SUPPORTED({
            MemorySegmentMapped segment_ro(mapped_file);
            segment_ro.allocate(16);
        }, "");
    EXPECT_DEATH_IF_SUPPORTED({
            MemorySegmentMapped segment_ro(mapped_file);
            segment_ro.setNamedAddress("test", 0);
        }, "");
    EXPECT_DEATH_IF_SUPPORTED({
            void* ptr = segment_->allocate(sizeof(uint32_t));
            segment_->setNamedAddress("test address", ptr);
            MemorySegmentMapped segment_ro(mapped_file);
            EXPECT_TRUE(segment_ro.getNamedAddress("test address"));
            *static_cast<uint32_t*>(
                segment_ro.getNamedAddress("test address")) = 0;
        }, "");
}

TEST_F(MemorySegmentMappedTest, nullDeallocate) {
    // NULL deallocation is a no-op.
    EXPECT_NO_THROW(segment_->deallocate(0, 1024));
    EXPECT_TRUE(segment_->allMemoryDeallocated());
}

TEST_F(MemorySegmentMappedTest, shrink) {
    segment_->shrinkToFit();
    // Normally we should be able to expect the resulting size is the smaller
    // than the initial default size.  It's not really guaranteed by the API,
    // however, so we may have to disable this check.
    const size_t shrinked_size = segment_->getSize();
    EXPECT_GT(DEFAULT_INITIAL_SIZE, shrinked_size);

    // Another shrink shouldn't cause disruption, and the size shouldn't change
    segment_->shrinkToFit();
    EXPECT_EQ(shrinked_size, segment_->getSize());

    // Check the segment is still usable after shrink.
    void* p = segment_->allocate(sizeof(uint32_t));
    segment_->deallocate(p, sizeof(uint32_t));
}

}
