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

#include <util/tests/memory_segment_common_unittest.h>
#include <util/unittests/check_valgrind.h>

#include <util/memory_segment_mapped.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/scoped_ptr.hpp>

#include <stdint.h>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <fstream>
#include <string>

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
        boost::interprocess::file_mapping::remove(mapped_file);
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

    // Close the segment, break the file with bogus data, and try to reopen.
    // It should fail with exception whether in the read-only or read-write,
    // or "create if not exist" mode.
    segment_.reset();
    std::ofstream ofs(mapped_file, std::ios::trunc);
    ofs << std::string(1024, 'x');
    ofs.close();
    EXPECT_THROW(MemorySegmentMapped sgmt(mapped_file), MemorySegmentOpenError);
    EXPECT_THROW(MemorySegmentMapped sgmt(mapped_file, false),
                 MemorySegmentOpenError);
    EXPECT_THROW(MemorySegmentMapped sgmt(mapped_file, true),
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
    if (!isc::util::unittests::runningOnValgrind()) {
        EXPECT_DEATH_IF_SUPPORTED({segment_->deallocate(ptr, 4);}, "");
        resetSegment();   // the segment is possibly broken; reset it.
    }

    // Deallocating at an invalid address; this would result in crash (the
    // behavior may not be portable enough; if so we should disable it by
    // default).
    if (!isc::util::unittests::runningOnValgrind()) {
        ptr = segment_->allocate(4);
        EXPECT_NE(static_cast<void*>(0), ptr);
        EXPECT_DEATH_IF_SUPPORTED({
                segment_->deallocate(static_cast<char*>(ptr) + 1, 3);
            }, "");
        resetSegment();
    }

    // Invalid size; this implementation doesn't detect such errors.
    ptr = segment_->allocate(4);
    EXPECT_NE(static_cast<void*>(0), ptr);
    segment_->deallocate(ptr, 8);
    EXPECT_TRUE(segment_->allMemoryDeallocated());
}

TEST_F(MemorySegmentMappedTest, namedAddress) {
    // common test cases
    isc::util::test::checkSegmentNamedAddress(*segment_, false);

    // Set it again and read it in the read-only mode.
    void* ptr16 = segment_->allocate(sizeof(uint16_t));
    const uint16_t test_val16 = 42000;
    std::memcpy(ptr16, &test_val16, sizeof(test_val16));
    EXPECT_FALSE(segment_->setNamedAddress("test address", ptr16));
    MemorySegmentMapped segment_ro(mapped_file);
    EXPECT_TRUE(segment_ro.getNamedAddress("test address"));
    EXPECT_EQ(test_val16, *static_cast<const uint16_t*>(
                  segment_ro.getNamedAddress("test address")));

    // try to set an unusually long name.  We re-create the file so the
    // creating the name would cause allocation failure and trigger internal
    // segment extension.
    segment_.reset();
    boost::interprocess::file_mapping::remove(mapped_file);
    segment_.reset(new MemorySegmentMapped(mapped_file, true, 1024));
    const std::string long_name(1025, 'x'); // definitely larger than segment
    // setNamedAddress should return true, indicating segment has grown.
    EXPECT_TRUE(segment_->setNamedAddress(long_name.c_str(), 0));
    EXPECT_EQ(static_cast<void*>(0),
              segment_->getNamedAddress(long_name.c_str()));
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

TEST_F(MemorySegmentMappedTest, violateReadOnly) {
    // If the segment is opened in the read only mode, modification attempts
    // are prohibited.  when detectable it's result in an exception;
    // an attempt of not directly through the segment class will result in
    // crash.
    EXPECT_THROW(MemorySegmentMapped(mapped_file).allocate(16),
                 isc::InvalidOperation);
    // allocation that would otherwise require growing the segment; permission
    // check should be performed before that.
    EXPECT_THROW(MemorySegmentMapped(mapped_file).
                 allocate(DEFAULT_INITIAL_SIZE * 2),
                 isc::InvalidOperation);
    EXPECT_THROW(MemorySegmentMapped(mapped_file).setNamedAddress("test", 0),
                 isc::InvalidOperation);
    EXPECT_THROW(MemorySegmentMapped(mapped_file).clearNamedAddress("test"),
                 isc::InvalidOperation);
    EXPECT_THROW(MemorySegmentMapped(mapped_file).shrinkToFit(),
                 isc::InvalidOperation);

    void* ptr = segment_->allocate(sizeof(uint32_t));
    segment_->setNamedAddress("test address", ptr);

    if (!isc::util::unittests::runningOnValgrind()) {
        EXPECT_DEATH_IF_SUPPORTED({
                MemorySegmentMapped segment_ro(mapped_file);
                EXPECT_TRUE(segment_ro.getNamedAddress("test address"));
                *static_cast<uint32_t*>(
                    segment_ro.getNamedAddress("test address")) = 0;
            }, "");
    }

    EXPECT_THROW(MemorySegmentMapped(mapped_file).deallocate(ptr, 4),
                 isc::InvalidOperation);
}

TEST_F(MemorySegmentMappedTest, getCheckSum) {
    const size_t old_cksum = segment_->getCheckSum();

    // We assume the initial segment size is sufficiently larger than the
    // page size.  We'll allocate memory of the page size, and increment all
    // bytes in that region by one.  It will increase our simple checksum value
    // by one, too.
    const size_t page_sz = boost::interprocess::mapped_region::get_page_size();
    uint8_t* cp0 = static_cast<uint8_t*>(segment_->allocate(page_sz));
    for (uint8_t* cp = cp0; cp < cp0 + page_sz; ++cp) {
        ++*cp;
    }

    EXPECT_EQ(old_cksum + 1, segment_->getCheckSum());
}

}
