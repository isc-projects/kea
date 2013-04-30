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
#include <boost/foreach.hpp>

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
// Shortcut to keep code shorter
const MemorySegmentMapped::OpenMode OPEN_FOR_WRITE =
    MemorySegmentMapped::OPEN_FOR_WRITE;
const MemorySegmentMapped::OpenMode OPEN_OR_CREATE =
    MemorySegmentMapped::OPEN_OR_CREATE;
const MemorySegmentMapped::OpenMode CREATE_ONLY =
    MemorySegmentMapped::CREATE_ONLY;

const char* const mapped_file = TEST_DATA_BUILDDIR "/test.mapped";
const size_t DEFAULT_INITIAL_SIZE = 32 * 1024; // intentionally hardcoded

// A simple RAII-style wrapper for a pipe.  Several tests in this file use
// pipes, so this helper will be useful.
class PipeHolder {
public:
    PipeHolder() {
        if (pipe(fds_) == -1) {
            isc_throw(isc::Unexpected, "pipe failed");
        }
    }
    ~PipeHolder() {
        close(fds_[0]);
        close(fds_[1]);
    }
    int getReadFD() const { return (fds_[0]); }
    int getWriteFD() const { return (fds_[1]); }
private:
    int fds_[2];
};

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
        segment_.reset(new MemorySegmentMapped(mapped_file, OPEN_OR_CREATE));
    }

    scoped_ptr<MemorySegmentMapped> segment_;
};

TEST(MemorySegmentMappedConstantTest, staticVariables) {
    // Attempt to take address of MemorySegmentMapped::INITIAL_SIZE.
    // It helps in case we accidentally remove the definition from the main
    // code.
    EXPECT_EQ(DEFAULT_INITIAL_SIZE, *(&MemorySegmentMapped::INITIAL_SIZE));
}

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
        EXPECT_NE(static_cast<void*>(NULL), ptr);

        // Now, we have an allocation:
        EXPECT_FALSE(segment_->allMemoryDeallocated());

        // deallocate it; it shouldn't cause disruption.
        segment_->deallocate(ptr, 1024);

        EXPECT_TRUE(segment_->allMemoryDeallocated());

        // re-open it in read-write mode, but don't try to create it
        // this time.
        segment_.reset();       // make sure close is first.
        segment_.reset(new MemorySegmentMapped(mapped_file, OPEN_FOR_WRITE));
    }
}

TEST_F(MemorySegmentMappedTest, createWithSize) {
    boost::interprocess::file_mapping::remove(mapped_file);

    // Re-create the mapped file with a non-default initial size, and confirm
    // the size is actually the specified one.
    const size_t new_size = 64 * 1024;
    EXPECT_NE(new_size, segment_->getSize());
    segment_.reset();
    segment_.reset(new MemorySegmentMapped(mapped_file, OPEN_OR_CREATE,
                                           new_size));
    EXPECT_EQ(new_size, segment_->getSize());
}

TEST_F(MemorySegmentMappedTest, createOnly) {
    // First, allocate some data in the existing segment
    EXPECT_TRUE(segment_->allocate(16));
    // Close it, and then open it again in the create-only mode.  the existing
    // file should be internally removed, and so the resulting segment
    // should be "empty" (all deallocated).
    segment_.reset();
    segment_.reset(new MemorySegmentMapped(mapped_file, CREATE_ONLY));
    EXPECT_TRUE(segment_->allMemoryDeallocated());
}

TEST_F(MemorySegmentMappedTest, openFail) {
    // The given file is directory
    EXPECT_THROW(MemorySegmentMapped("/", OPEN_OR_CREATE),
                 MemorySegmentOpenError);

    // file doesn't exist and directory isn't writable (we assume the
    // following path is not writable for the user running the test).
    EXPECT_THROW(MemorySegmentMapped("/random-glkwjer098/test.mapped",
                                     OPEN_OR_CREATE), MemorySegmentOpenError);

    // It should fail when file doesn't exist and it's read-only (so
    // open-only).
    EXPECT_THROW(MemorySegmentMapped(TEST_DATA_BUILDDIR "/nosuchfile.mapped"),
                 MemorySegmentOpenError);
    // Likewise, it should fail in read-write mode when creation is
    // suppressed.
    EXPECT_THROW(MemorySegmentMapped(TEST_DATA_BUILDDIR "/nosuchfile.mapped",
                                     OPEN_FOR_WRITE), MemorySegmentOpenError);

    // creating with a very small size fails (for sure about 0, and other
    // small values should also make it fail, but it's internal restriction
    // of Boost and cannot be predictable).
    EXPECT_THROW(MemorySegmentMapped(mapped_file, OPEN_OR_CREATE, 0),
                 MemorySegmentOpenError);

    // invalid read-write mode
    EXPECT_THROW(MemorySegmentMapped(
                     mapped_file,
                     static_cast<MemorySegmentMapped::OpenMode>(
                         static_cast<int>(CREATE_ONLY) + 1)),
                 isc::InvalidParameter);

    // Close the existing segment, break its file with bogus data, and
    // try to reopen.  It should fail with exception whether in the
    // read-only or read-write, or "create if not exist" mode.
    segment_.reset();
    std::ofstream ofs(mapped_file, std::ios::trunc);
    ofs << std::string(1024, 'x');
    ofs.close();
    EXPECT_THROW(MemorySegmentMapped sgmt(mapped_file), MemorySegmentOpenError);
    EXPECT_THROW(MemorySegmentMapped sgmt(mapped_file, OPEN_FOR_WRITE),
                 MemorySegmentOpenError);
    EXPECT_THROW(MemorySegmentMapped sgmt(mapped_file, OPEN_OR_CREATE),
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

    if (delete_after_check) {
        sgmt.deallocate(dp, data.size());
        sgmt.clearNamedAddress(name.c_str());
    }
}

TEST_F(MemorySegmentMappedTest, namedAddress) {
    // common test cases
    isc::util::test::checkSegmentNamedAddress(*segment_, false);

    // Set it again and read it in the read-only mode.
    void* ptr16 = segment_->allocate(sizeof(uint16_t));
    const uint16_t test_val16 = 42000;
    *static_cast<uint16_t*>(ptr16) = test_val16;
    EXPECT_FALSE(segment_->setNamedAddress("test address", ptr16));
    segment_.reset();           // close it before opening another one

    segment_.reset(new MemorySegmentMapped(mapped_file));
    EXPECT_NE(static_cast<void*>(NULL),
              segment_->getNamedAddress("test address"));
    EXPECT_EQ(test_val16, *static_cast<const uint16_t*>(
                  segment_->getNamedAddress("test address")));

    // try to set an unusually long name.  We re-create the file so
    // creating the name would cause allocation failure and trigger internal
    // segment extension.
    segment_.reset();
    boost::interprocess::file_mapping::remove(mapped_file);
    segment_.reset(new MemorySegmentMapped(mapped_file, OPEN_OR_CREATE, 1024));
    const std::string long_name(1025, 'x'); // definitely larger than segment
    // setNamedAddress should return true, indicating segment has grown.
    EXPECT_TRUE(segment_->setNamedAddress(long_name.c_str(), NULL));
    EXPECT_EQ(static_cast<void*>(NULL),
              segment_->getNamedAddress(long_name.c_str()));

    // Check contents pointed by named addresses survive growing and
    // shrinking segment.
    segment_.reset();
    boost::interprocess::file_mapping::remove(mapped_file);
    segment_.reset(new MemorySegmentMapped(mapped_file, OPEN_OR_CREATE));

    typedef std::map<std::string, std::vector<uint8_t> > TestData;

    TestData data_list;
    data_list["data1"] =
        std::vector<uint8_t>(80); // arbitrarily chosen small data
    data_list["data2"] =
        std::vector<uint8_t>(5000); // larger than usual segment size
    data_list["data3"] =
        std::vector<uint8_t>(65535); // bigger than most usual data
    bool grown = false;

    // Allocate memory and store data
    for (TestData::iterator it = data_list.begin(); it != data_list.end();
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
    for (TestData::iterator it = data_list.begin(); it != data_list.end();
         ++it)
    {
        checkNamedData(it->first, it->second, *segment_);
    }

    // Confirm they are still valid, while we shrink the segment.  We'll
    // intentionally delete bigger data first so it'll be more likely that
    // shrink has some real effect.
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

    // close the read-write segment at this point.  our intended use case is
    // to have one or more reader process or at most one exclusive writer
    // process.  so we don't mix reader and writer.
    segment_.reset();

    // Spawn another process and have it open and read the same data.
    PipeHolder pipe_to_child;
    PipeHolder pipe_to_parent;
    const pid_t child_pid = fork();
    ASSERT_NE(-1, child_pid);
    if (child_pid == 0) {
        // child: wait until the parent has opened the read-only segment.
        char from_parent;
        EXPECT_EQ(1, read(pipe_to_child.getReadFD(), &from_parent,
                          sizeof(from_parent)));
        EXPECT_EQ(0, from_parent);

        MemorySegmentMapped sgmt(mapped_file);
        void* ptr_child = sgmt.getNamedAddress("test address");
        EXPECT_TRUE(ptr_child);
        if (ptr_child) {
            const uint32_t val = *static_cast<const uint32_t*>(ptr_child);
            EXPECT_EQ(424242, val);
            // tell the parent whether it succeeded. 0 means it did,
            // 0xff means it failed.
            const char ok = (val == 424242) ? 0 : 0xff;
            EXPECT_EQ(1, write(pipe_to_parent.getWriteFD(), &ok, sizeof(ok)));
        }
        exit(0);
    }
    // parent: open another read-only segment, then tell the child to open
    // its own segment.
    segment_.reset(new MemorySegmentMapped(mapped_file));
    ptr = segment_->getNamedAddress("test address");
    ASSERT_TRUE(ptr);
    EXPECT_EQ(424242, *static_cast<const uint32_t*>(ptr));
    const char some_data = 0;
    EXPECT_EQ(1, write(pipe_to_child.getWriteFD(), &some_data,
                       sizeof(some_data)));

    // wait for the completion of the child and checks the result.
    EXPECT_EQ(0, parentReadState(pipe_to_parent.getReadFD()));
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

    // Another shrink shouldn't cause disruption.  We expect the size is
    // the same so we confirm it.  The underlying library doesn't guarantee
    // that, so we may have to change it to EXPECT_GE if the test fails
    // on that (MemorySegmentMapped class doesn't rely on this expectation,
    // so it's okay even if it does not always hold).
    segment_->shrinkToFit();
    EXPECT_EQ(shrinked_size, segment_->getSize());

    // Check that the segment is still usable after shrink.
    void* p = segment_->allocate(sizeof(uint32_t));
    segment_->deallocate(p, sizeof(uint32_t));
}

TEST_F(MemorySegmentMappedTest, violateReadOnly) {
    // Create a named address for the tests below, then reset the writer
    // segment so that it won't fail for different reason (i.e., read-write
    // conflict).
    void* ptr = segment_->allocate(sizeof(uint32_t));
    segment_->setNamedAddress("test address", ptr);
    segment_.reset();

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

    // If the segment is opened in the read-only mode, modification
    // attempts are prohibited. When detectable it must result in an
    // exception.
    MemorySegmentMapped segment_ro(mapped_file);
    ptr = segment_ro.getNamedAddress("test address");
    EXPECT_NE(static_cast<void*>(NULL), ptr);

    EXPECT_THROW(segment_ro.deallocate(ptr, 4), MemorySegmentError);

    EXPECT_THROW(segment_ro.allocate(16), MemorySegmentError);
    // allocation that would otherwise require growing the segment; permission
    // check should be performed before that.
    EXPECT_THROW(segment_ro.allocate(DEFAULT_INITIAL_SIZE * 2),
                 MemorySegmentError);
    EXPECT_THROW(segment_ro.setNamedAddress("test", NULL), MemorySegmentError);
    EXPECT_THROW(segment_ro.clearNamedAddress("test"), MemorySegmentError);
    EXPECT_THROW(segment_ro.shrinkToFit(), MemorySegmentError);
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

// Mode of opening segments in the tests below.
enum TestOpenMode {
    READER = 0,
    WRITER_FOR_WRITE,
    WRITER_OPEN_OR_CREATE,
    WRITER_CREATE_ONLY
};

// A shortcut to attempt to open a specified type of segment (generally
// expecting it to fail)
void
setSegment(TestOpenMode mode, scoped_ptr<MemorySegmentMapped>& sgmt_ptr) {
    switch (mode) {
    case READER:
        sgmt_ptr.reset(new MemorySegmentMapped(mapped_file));
        break;
    case WRITER_FOR_WRITE:
        sgmt_ptr.reset(new MemorySegmentMapped(mapped_file, OPEN_FOR_WRITE));
        break;
    case WRITER_OPEN_OR_CREATE:
        sgmt_ptr.reset(new MemorySegmentMapped(mapped_file, OPEN_OR_CREATE));
        break;
    case WRITER_CREATE_ONLY:
        sgmt_ptr.reset(new MemorySegmentMapped(mapped_file, CREATE_ONLY));
        break;
    }
}

// Common logic for conflictReaderWriter test.  The segment opened in the
// parent process will prevent the segment in the child from being used.
void
conflictCheck(TestOpenMode parent_mode, TestOpenMode child_mode) {
    PipeHolder pipe_to_child;
    PipeHolder pipe_to_parent;
    const pid_t child_pid = fork();
    ASSERT_NE(-1, child_pid);

    if (child_pid == 0) {
        char ch;
        EXPECT_EQ(1, read(pipe_to_child.getReadFD(), &ch, sizeof(ch)));

        ch = 0;                 // 0 = open success, 1 = fail
        try {
            scoped_ptr<MemorySegmentMapped> sgmt;
            setSegment(child_mode, sgmt);
            EXPECT_EQ(1, write(pipe_to_parent.getWriteFD(), &ch, sizeof(ch)));
        } catch (const MemorySegmentOpenError&) {
            ch = 1;
            EXPECT_EQ(1, write(pipe_to_parent.getWriteFD(), &ch, sizeof(ch)));
        }
        exit(0);
    }

    // parent: open a segment, then tell the child to open its own segment of
    // the specified type.
    scoped_ptr<MemorySegmentMapped> sgmt;
    setSegment(parent_mode, sgmt);
    const char some_data = 0;
    EXPECT_EQ(1, write(pipe_to_child.getWriteFD(), &some_data,
                       sizeof(some_data)));

    // wait for the completion of the child and checks the result.  open at
    // the child side should fail, so the parent should get the value of 1.
    EXPECT_EQ(1, parentReadState(pipe_to_parent.getReadFD()));
}

TEST_F(MemorySegmentMappedTest, conflictReaderWriter) {
    // Test using fork() doesn't work well on valgrind
    if (isc::util::unittests::runningOnValgrind()) {
        return;
    }

    // Below, we check all combinations of conflicts between reader and writer
    // will fail.  We first make sure there's no other reader or writer.
    segment_.reset();

    // reader opens segment, then writer (OPEN_FOR_WRITE) tries to open
    conflictCheck(READER, WRITER_FOR_WRITE);
    // reader opens segment, then writer (OPEN_OR_CREATE) tries to open
    conflictCheck(READER, WRITER_OPEN_OR_CREATE);
    // reader opens segment, then writer (CREATE_ONLY) tries to open
    conflictCheck(READER, WRITER_CREATE_ONLY);

    // writer (OPEN_FOR_WRITE) opens a segment, then reader tries to open
    conflictCheck(WRITER_FOR_WRITE, READER);
    // writer (OPEN_OR_CREATE) opens a segment, then reader tries to open
    conflictCheck(WRITER_OPEN_OR_CREATE, READER);
    // writer (CREATE_ONLY) opens a segment, then reader tries to open
    conflictCheck(WRITER_CREATE_ONLY, READER);

    // writer opens segment, then another writer (OPEN_FOR_WRITE) tries to open
    conflictCheck(WRITER_FOR_WRITE, WRITER_FOR_WRITE);
    // writer opens segment, then another writer (OPEN_OR_CREATE) tries to open
    conflictCheck(WRITER_FOR_WRITE, WRITER_OPEN_OR_CREATE);
    // writer opens segment, then another writer (CREATE_ONLY) tries to open
    conflictCheck(WRITER_FOR_WRITE, WRITER_CREATE_ONLY);
}

}
