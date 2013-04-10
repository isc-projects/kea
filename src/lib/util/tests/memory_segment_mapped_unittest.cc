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
#include <util/tests/interprocess_util.h>

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
#include <vector>
#include <map>

#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

using namespace isc::util;
using boost::scoped_ptr;
using isc::util::test::parentReadState;

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

        // re-open it in read-write mode, but don't try to create it
        // this time.
        segment_.reset(new MemorySegmentMapped(mapped_file, false));
    }
}

TEST_F(MemorySegmentMappedTest, createWithSize) {
    boost::interprocess::file_mapping::remove(mapped_file);

    // Re-create the mapped file with a non-default initial size, and confirm
    // the size is actually the specified one.
    const size_t new_size = 64 * 1024;
    EXPECT_NE(new_size, segment_->getSize());
    segment_.reset(new MemorySegmentMapped(mapped_file, true, new_size));
    EXPECT_EQ(new_size, segment_->getSize());
}

TEST_F(MemorySegmentMappedTest, openFail) {
    // The given file is directory
    EXPECT_THROW(MemorySegmentMapped("/", true), MemorySegmentOpenError);

    // file doesn't exist and directory isn't writable (we assume the
    // following path is not writable for the user running the test).
    EXPECT_THROW(MemorySegmentMapped("/random-glkwjer098/test.mapped", true),
                 MemorySegmentOpenError);

    // It should fail when file doesn't exist and it's read-only (so
    // open-only).
    EXPECT_THROW(MemorySegmentMapped(TEST_DATA_BUILDDIR "/nosuchfile.mapped"),
                 MemorySegmentOpenError);
    // Likewise, it should fail in read-write mode when creation is
    // suppressed.
    EXPECT_THROW(MemorySegmentMapped(TEST_DATA_BUILDDIR "/nosuchfile.mapped",
                                     false),
                 MemorySegmentOpenError);

    // Close the existing segment, break its file with bogus data, and
    // try to reopen.  It should fail with exception whether in the
    // read-only or read-write, or "create if not exist" mode.
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

    // Initially, nothing is allocated.
    EXPECT_TRUE(segment_->allMemoryDeallocated());

    // (Clearly) exceeding the available size, which should cause growing
    // the segment
    const size_t prev_size = segment_->getSize();
    EXPECT_THROW(segment_->allocate(prev_size + 1), MemorySegmentGrown);
    // The size should have been doubled.
    EXPECT_EQ(prev_size * 2, segment_->getSize());
    // But nothing should have been allocated.
    EXPECT_TRUE(segment_->allMemoryDeallocated());

    // Now, the allocation should now succeed.
    void* ptr = segment_->allocate(prev_size + 1);
    EXPECT_NE(static_cast<void*>(NULL), ptr);
    EXPECT_FALSE(segment_->allMemoryDeallocated());

    // Same set of checks, but for a larger size.
    EXPECT_THROW(segment_->allocate(prev_size * 10), MemorySegmentGrown);
    // the segment should have grown to the minimum power-of-2 size that
    // could allocate the given size of memory.
    EXPECT_EQ(prev_size * 16, segment_->getSize());
    // And allocate() should now succeed.
    ptr = segment_->allocate(prev_size * 10);
    EXPECT_NE(static_cast<void*>(NULL), ptr);

    // (we'll left the regions created in the file there; the entire file
    // will be removed at the end of the test)
}

TEST_F(MemorySegmentMappedTest, badAllocate) {
    // Make the mapped file non-writable; managed_mapped_file::grow() will
    // fail, resulting in std::bad_alloc
    const int ret = chmod(mapped_file, 0444);
    ASSERT_EQ(0, ret);

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
    EXPECT_NE(static_cast<void*>(NULL), ptr);

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
        EXPECT_NE(static_cast<void*>(NULL), ptr);
        EXPECT_DEATH_IF_SUPPORTED({
                segment_->deallocate(static_cast<char*>(ptr) + 1, 3);
            }, "");
        resetSegment();
    }

    // Invalid size; this implementation doesn't detect such errors.
    ptr = segment_->allocate(4);
    EXPECT_NE(static_cast<void*>(NULL), ptr);
    segment_->deallocate(ptr, 8);
    EXPECT_TRUE(segment_->allMemoryDeallocated());
}

// A helper of namedAddress.
void
checkNamedData(const std::string& name, const std::vector<uint8_t>& data,
               MemorySegment& sgmt, bool delete_after_check = false)
{
    void* dp = sgmt.getNamedAddress(name.c_str());
    ASSERT_TRUE(dp);
    EXPECT_EQ(0, std::memcmp(dp, &data[0], data.size()));

    // Open a separate read-only segment and checks the same named data
    // Since the mapped space should be different, the resulting bare address
    // from getNamedAddress should also be different, but it should actually
    // point to the same data.
    // Note: it's mostly violation of the API assumption to open read-only
    // and read-write segments at the same time, but unless we modify the
    // segment throughout the lifetime of the read-only segment, it should
    // work.
    scoped_ptr<MemorySegmentMapped> segment_ro(
        new MemorySegmentMapped(mapped_file));
    void* dp2 = segment_ro->getNamedAddress(name.c_str());
    ASSERT_TRUE(dp2);
    EXPECT_NE(dp, dp2);
    EXPECT_EQ(0, std::memcmp(dp2, &data[0], data.size()));
    segment_ro.reset();

    if (delete_after_check) {
        sgmt.deallocate(dp, data.size());
    }
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
    EXPECT_NE(static_cast<void*>(NULL),
              segment_ro.getNamedAddress("test address"));
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
    EXPECT_TRUE(segment_->setNamedAddress(long_name.c_str(), NULL));
    EXPECT_EQ(static_cast<void*>(NULL),
              segment_->getNamedAddress(long_name.c_str()));

    // Check contents pointed by named addresses survive growing and
    // shrinking segment.
    segment_.reset();
    boost::interprocess::file_mapping::remove(mapped_file);
    segment_.reset(new MemorySegmentMapped(mapped_file, true));
    std::map<std::string, std::vector<uint8_t> > data_list;
    data_list["data1"] =
        std::vector<uint8_t>(80); // arbitrarily chosen small data
    data_list["data2"] =
        std::vector<uint8_t>(5000); // larger than usual segment sz
    data_list["data3"] =
        std::vector<uint8_t>(65535); // bigger than most usual data
    bool grown = false;

    // Allocate memory and store data
    for (std::map<std::string, std::vector<uint8_t> >::iterator it
             = data_list.begin();
         it != data_list.end();
         ++it)
    {
        std::vector<uint8_t>& data = it->second;
        for (int i = 0; i < data.size(); ++i) {
            data[i] = i;
        }
        void *dp = NULL;
        while (!dp) {
            try {
                dp = segment_->allocate(data.size());
                std::memcpy(dp, &data[0], data.size());
                segment_->setNamedAddress(it->first.c_str(), dp);
            } catch (const MemorySegmentGrown&) {
                grown = true;
            }
        }
    }
    // Confirm there's at least one segment extension
    EXPECT_TRUE(grown);
    // Check named data are still valid
    for (std::map<std::string, std::vector<uint8_t> >::iterator it
             = data_list.begin();
         it != data_list.end();
         ++it)
    {
        checkNamedData(it->first, it->second, *segment_);
    }
    // Confirm they are still valid, while we shrink the segment
    const char* const names[] = { "data3", "data2", "data1", NULL };
    for (int i = 0; names[i]; ++i) {
        checkNamedData(names[i], data_list[names[i]], *segment_, true);
        segment_->shrinkToFit();
    }
}

TEST_F(MemorySegmentMappedTest, multiProcess) {
    // Test using fork() doesn't work well on valgrind
    if (isc::util::unittests::runningOnValgrind()) {
        return;
    }

    // allocate some data and name its address
    void* ptr = segment_->allocate(sizeof(uint32_t));
    *static_cast<uint32_t*>(ptr) = 424242;
    segment_->setNamedAddress("test address", ptr);

    // reopen it in read-only.  our intended use case is to have one or
    // more reader process or at most one exclusive writer process.  so we
    // don't mix reader and writer.
    segment_.reset();
    segment_.reset(new MemorySegmentMapped(mapped_file));
    ptr = segment_->getNamedAddress("test address");
    ASSERT_TRUE(ptr);
    EXPECT_EQ(424242, *static_cast<const uint32_t*>(ptr));

    // Spawn another process and have it open and read the same data
    int pipes[2];
    EXPECT_EQ(0, pipe(pipes));
    const pid_t child_pid = fork();
    ASSERT_NE(-1, child_pid);
    if (child_pid == 0) {       // child
        close(pipes[0]);
        MemorySegmentMapped sgmt(mapped_file);
        void* ptr_child = segment_->getNamedAddress("test address");
        EXPECT_TRUE(ptr_child);
        if (ptr_child) {
            const uint32_t val = *static_cast<const uint32_t*>(ptr_child);
            EXPECT_EQ(424242, val);
            if (val == 424242) {
                // tell the parent it succeeded using a result code other
                // than 255.
                const char ok = 0;
                EXPECT_EQ(1, write(pipes[1], &ok, sizeof(ok)));
            }
        }
        close(pipes[1]);
        exit(0);
    }
    // parent: wait for the completion of the child and checks the result.
    close(pipes[1]);
    EXPECT_EQ(0, parentReadState(pipes[0]));
}

TEST_F(MemorySegmentMappedTest, nullDeallocate) {
    // NULL deallocation is a no-op.
    EXPECT_NO_THROW(segment_->deallocate(0, 1024));
    EXPECT_TRUE(segment_->allMemoryDeallocated());
}

TEST_F(MemorySegmentMappedTest, shrink) {
    segment_->shrinkToFit();
    // Normally we should be able to expect that the resulting size is
    // smaller than the initial default size. But it's not really
    // guaranteed by the API, so we may have to disable this check (or
    // use EXPECT_GE).
    const size_t shrinked_size = segment_->getSize();
    EXPECT_GT(DEFAULT_INITIAL_SIZE, shrinked_size);

    // Another shrink shouldn't cause disruption, and the size shouldn't
    // change.
    segment_->shrinkToFit();
    EXPECT_EQ(shrinked_size, segment_->getSize());

    // Check that the segment is still usable after shrink.
    void* p = segment_->allocate(sizeof(uint32_t));
    segment_->deallocate(p, sizeof(uint32_t));
}

TEST_F(MemorySegmentMappedTest, violateReadOnly) {
    // If the segment is opened in the read-only mode, modification
    // attempts are prohibited. When detectable it must result in an
    // exception.
    EXPECT_THROW(MemorySegmentMapped(mapped_file).allocate(16),
                 MemorySegmentError);
    // allocation that would otherwise require growing the segment; permission
    // check should be performed before that.
    EXPECT_THROW(MemorySegmentMapped(mapped_file).
                 allocate(DEFAULT_INITIAL_SIZE * 2), MemorySegmentError);
    EXPECT_THROW(MemorySegmentMapped(mapped_file).setNamedAddress("test",
                                                                  NULL),
                 MemorySegmentError);
    EXPECT_THROW(MemorySegmentMapped(mapped_file).clearNamedAddress("test"),
                 MemorySegmentError);
    EXPECT_THROW(MemorySegmentMapped(mapped_file).shrinkToFit(),
                 MemorySegmentError);

    void* ptr = segment_->allocate(sizeof(uint32_t));
    segment_->setNamedAddress("test address", ptr);

    // Attempts to modify memory from the read-only segment directly
    // will result in a crash.
    if (!isc::util::unittests::runningOnValgrind()) {
        EXPECT_DEATH_IF_SUPPORTED({
                MemorySegmentMapped segment_ro(mapped_file);
                EXPECT_TRUE(segment_ro.getNamedAddress("test address"));
                *static_cast<uint32_t*>(
                    segment_ro.getNamedAddress("test address")) = 0;
            }, "");
    }

    EXPECT_THROW(MemorySegmentMapped(mapped_file).deallocate(ptr, 4),
                 MemorySegmentError);
}

TEST_F(MemorySegmentMappedTest, getCheckSum) {
    const size_t old_cksum = segment_->getCheckSum();

    // We assume the initial segment size is sufficiently larger than
    // the page size.  We'll allocate memory of the page size, and
    // increment all bytes in that page by one.  It will increase our
    // simple checksum value (which just uses the first byte of each
    // page) by one, too.
    const size_t page_sz = boost::interprocess::mapped_region::get_page_size();
    uint8_t* cp0 = static_cast<uint8_t*>(segment_->allocate(page_sz));
    for (uint8_t* cp = cp0; cp < cp0 + page_sz; ++cp) {
        ++*cp;
    }

    EXPECT_EQ(old_cksum + 1, segment_->getCheckSum());
}

}
