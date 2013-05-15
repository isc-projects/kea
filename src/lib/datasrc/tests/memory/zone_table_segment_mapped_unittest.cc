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

#include <datasrc/memory/zone_writer.h>
#include <datasrc/memory/zone_table_segment_mapped.h>
#include <util/random/random_number_generator.h>
#include <util/unittests/check_valgrind.h>

#include <gtest/gtest.h>
#include <boost/format.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/interprocess/file_mapping.hpp>

#include <memory>
#include <cerrno>

#include <sys/stat.h>

using namespace isc::dns;
using namespace isc::datasrc::memory;
using namespace isc::data;
using namespace isc::util;
using namespace isc::util::random;
using namespace std;
using boost::scoped_ptr;

namespace {

const char* const mapped_file  = TEST_DATA_BUILDDIR "/test.mapped";
const char* const mapped_file2 = TEST_DATA_BUILDDIR "/test2.mapped";

class ZoneTableSegmentMappedTest : public ::testing::Test {
protected:
    ZoneTableSegmentMappedTest() :
        ztable_segment_(
            ZoneTableSegment::create(RRClass::IN(), "mapped")),
        config_params_(
            Element::fromJSON(
                "{\"mapped-file\": \"" + std::string(mapped_file) + "\"}")),
        config_params2_(
            Element::fromJSON(
                "{\"mapped-file\": \"" + std::string(mapped_file2) + "\"}"))
    {
        EXPECT_NE(static_cast<void*>(NULL), ztable_segment_.get());
        // Verify that a ZoneTableSegmentMapped is created.
        ZoneTableSegmentMapped* mapped_segment =
            dynamic_cast<ZoneTableSegmentMapped*>(ztable_segment_.get());
        EXPECT_NE(static_cast<void*>(NULL), mapped_segment);

        createTestData();
    }

    ~ZoneTableSegmentMappedTest() {
        ZoneTableSegment::destroy(ztable_segment_.release());
        boost::interprocess::file_mapping::remove(mapped_file);
        boost::interprocess::file_mapping::remove(mapped_file2);
    }

    typedef std::pair<std::string, int> TestDataElement;

    void createTestData() {
        UniformRandomIntegerGenerator gen(0, INT_MAX);
        for (int i = 0; i < 256; ++i) {
            const string name(boost::str(boost::format("name%d") % i));
            const int value = gen();
            test_data_.push_back(TestDataElement(name, value));
        }
    }

    void setupMappedFiles();
    void addData(MemorySegment& segment);
    bool verifyData(const MemorySegment& segment);

    // Ideally, this should be something similar to a
    // SegmentObjectHolder, not an auto_ptr.
    std::auto_ptr<ZoneTableSegment> ztable_segment_;
    const ConstElementPtr config_params_;
    const ConstElementPtr config_params2_;
    std::vector<TestDataElement> test_data_;
};

bool
fileExists(const char* path) {
    struct stat sb;
    const int status = stat(path, &sb);
    if (status != 0) {
        EXPECT_EQ(ENOENT, errno);
        return (false);
    }
    return (true);
}

void
deleteChecksum(MemorySegment& segment) {
    segment.clearNamedAddress("zone_table_checksum");
}

void
corruptChecksum(MemorySegment& segment) {
    const MemorySegment::NamedAddressResult result =
        segment.getNamedAddress("zone_table_checksum");
    ASSERT_TRUE(result.first);

    size_t checksum = *static_cast<size_t*>(result.second);
    ++checksum;
    *static_cast<size_t*>(result.second) = checksum;
}

void
deleteHeader(MemorySegment& segment) {
    segment.clearNamedAddress("zone_table_header");
}

void
ZoneTableSegmentMappedTest::addData(MemorySegment& segment) {
    // For purposes of this test, we assume that the following
    // allocations do not resize the mapped segment. For this, we have
    // to keep the size of test data reasonably small in
    // createTestData().

    // One by one, add all the elements in test_data_.
    for (int i = 0; i < test_data_.size(); ++i) {
        void* ptr = segment.allocate(sizeof(int));
        ASSERT_TRUE(ptr);
        *static_cast<int*>(ptr) = test_data_[i].second;
        const bool grew = segment.setNamedAddress(test_data_[i].first.c_str(),
                                                  ptr);
        ASSERT_FALSE(grew);
    }
}

bool
ZoneTableSegmentMappedTest::verifyData(const MemorySegment& segment) {
    // One by one, verify all the elements in test_data_ exist and have
    // the expected values.
    for (int i = 0; i < test_data_.size(); ++i) {
        const MemorySegment::NamedAddressResult result =
            segment.getNamedAddress(test_data_[i].first.c_str());
        if (!result.first) {
            return (false);
        }
        if (*static_cast<int*>(result.second) != test_data_[i].second) {
            return (false);
        }
    }

    return (true);
}

void
ZoneTableSegmentMappedTest::setupMappedFiles() {
    ztable_segment_->reset(ZoneTableSegment::CREATE, config_params_);
    addData(ztable_segment_->getMemorySegment());
    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));

    ztable_segment_->reset(ZoneTableSegment::CREATE, config_params2_);
    addData(ztable_segment_->getMemorySegment());
    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));

    // Now, clear the segment, closing the underlying mapped file.
    ztable_segment_->clear();
}

TEST_F(ZoneTableSegmentMappedTest, getImplType) {
    EXPECT_EQ("mapped", ztable_segment_->getImplType());
}

TEST_F(ZoneTableSegmentMappedTest, getHeaderUninitialized) {
    // This should throw as we haven't called reset() yet.
    EXPECT_THROW(ztable_segment_->getHeader(), isc::InvalidOperation);
}

TEST_F(ZoneTableSegmentMappedTest, getMemorySegmentUninitialized) {
    // This should throw as we haven't called reset() yet.
    EXPECT_THROW(ztable_segment_->getMemorySegment(), isc::InvalidOperation);
}

TEST_F(ZoneTableSegmentMappedTest, isUsableUninitialized) {
    // isUsable() must return false by default, when the segment has not
    // been reset() yet.
    EXPECT_FALSE(ztable_segment_->isUsable());
}

TEST_F(ZoneTableSegmentMappedTest, isWritableUninitialized) {
    // isWritable() must return false by default, when the segment has
    // not been reset() yet.
    EXPECT_FALSE(ztable_segment_->isWritable());
}

TEST_F(ZoneTableSegmentMappedTest, resetBadConfig) {
    // Open a mapped file in create mode.
    ztable_segment_->reset(ZoneTableSegment::CREATE, config_params_);

    // Populate it with some data.
    addData(ztable_segment_->getMemorySegment());
    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));

    // All the following resets() with invalid configuration must
    // provide a strong exception guarantee that the segment is still
    // usable as before.

    // NULL is passed in config params
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::CREATE,
                               ConstElementPtr());
    }, isc::InvalidParameter);

    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));

    // Not a map
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::CREATE,
                               Element::fromJSON("42"));
    }, isc::InvalidParameter);

    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));

    // Empty map
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::CREATE,
                               Element::fromJSON("{}"));
    }, isc::InvalidParameter);

    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));

    // No "mapped-file" key
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::CREATE,
                               Element::fromJSON("{\"foo\": \"bar\"}"));
    }, isc::InvalidParameter);

    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));

    // Value of "mapped-file" key is not a string
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::CREATE,
                               Element::fromJSON("{\"mapped-file\": 42}"));
    }, isc::InvalidParameter);

    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));
}

TEST_F(ZoneTableSegmentMappedTest, reset) {
    // By default, the mapped file doesn't exist, so we cannot open it
    // in READ_ONLY mode (which does not create the file).
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::READ_ONLY, config_params_);
    }, MemorySegmentOpenError);

    // The following should still throw, unaffected by the failed open.
    EXPECT_THROW(ztable_segment_->getHeader(), isc::InvalidOperation);
    EXPECT_THROW(ztable_segment_->getMemorySegment(), isc::InvalidOperation);

    // isUsable() and isWritable() must still return false, because the
    // segment has not been successfully reset() yet.
    EXPECT_FALSE(ztable_segment_->isUsable());
    EXPECT_FALSE(ztable_segment_->isWritable());

    // If a Python binding passes an invalid integer as the mode,
    // reset() should reject it.
    EXPECT_THROW({
        ztable_segment_->reset
            (static_cast<ZoneTableSegment::MemorySegmentOpenMode>(1234),
             config_params_);
    }, isc::InvalidParameter);

    // READ_WRITE mode must create the mapped file if it doesn't exist
    // (and must not result in an exception).
    ztable_segment_->reset(ZoneTableSegment::READ_WRITE, config_params_);
    EXPECT_TRUE(ztable_segment_->isUsable());
    EXPECT_TRUE(ztable_segment_->isWritable());

    // The following method calls should no longer throw:
    EXPECT_NO_THROW(ztable_segment_->getHeader());
    EXPECT_NO_THROW(ztable_segment_->getMemorySegment());

    // Let's try to re-open the mapped file in READ_ONLY mode. It should
    // not fail now.
    ztable_segment_->reset(ZoneTableSegment::READ_ONLY, config_params_);
    EXPECT_TRUE(ztable_segment_->isUsable());
    EXPECT_FALSE(ztable_segment_->isWritable());

    // Re-creating the mapped file should erase old data and should not
    // trigger any exceptions inside reset() due to old data (such as
    // named addresses).
    ztable_segment_->reset(ZoneTableSegment::CREATE, config_params_);
    EXPECT_TRUE(ztable_segment_->isUsable());
    EXPECT_TRUE(ztable_segment_->isWritable());

    // When we reset() with an invalid paramter and it fails, then the
    // segment should still be usable.
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::CREATE,
                               Element::fromJSON("{}"));
    }, isc::InvalidParameter);
    EXPECT_TRUE(ztable_segment_->isUsable());
    EXPECT_TRUE(ztable_segment_->isWritable());
    // The following should not throw.
    EXPECT_NO_THROW(ztable_segment_->getHeader());
    EXPECT_NO_THROW(ztable_segment_->getMemorySegment());

    // READ_WRITE with an existing map file ought to work too. This
    // would use existing named addresses. This actually re-opens the
    // currently open map.
    ztable_segment_->reset(ZoneTableSegment::READ_WRITE, config_params_);
    EXPECT_TRUE(ztable_segment_->isUsable());
    EXPECT_TRUE(ztable_segment_->isWritable());
}

TEST_F(ZoneTableSegmentMappedTest, resetCreate) {
    // At this point, the underlying file must not exist.
    ASSERT_FALSE(fileExists(mapped_file));

    // Open the underlying mapped file in create mode.
    ztable_segment_->reset(ZoneTableSegment::CREATE, config_params_);

    ASSERT_TRUE(ztable_segment_->isUsable());
    ASSERT_TRUE(ztable_segment_->isWritable());

    // Add the data.
    addData(ztable_segment_->getMemorySegment());
    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));

    // Close the segment.
    ztable_segment_->clear();

    // At this point, the underlying file must still exist.
    ASSERT_TRUE(fileExists(mapped_file));

    // Open the underlying mapped file in create mode again.
    ztable_segment_->reset(ZoneTableSegment::CREATE, config_params_);

    // The old data should be gone.
    EXPECT_FALSE(verifyData(ztable_segment_->getMemorySegment()));
}

TEST_F(ZoneTableSegmentMappedTest, resetReadWrite) {
    // At this point, the underlying file must not exist.
    ASSERT_FALSE(fileExists(mapped_file));

    // Open the underlying mapped file in read+write mode.
    ztable_segment_->reset(ZoneTableSegment::READ_WRITE, config_params_);

    ASSERT_TRUE(ztable_segment_->isUsable());
    ASSERT_TRUE(ztable_segment_->isWritable());

    // Add the data.
    addData(ztable_segment_->getMemorySegment());
    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));

    // Close the segment.
    ztable_segment_->clear();

    // At this point, the underlying file must still exist.
    ASSERT_TRUE(fileExists(mapped_file));

    // Open the underlying mapped file in read+write mode again.
    ztable_segment_->reset(ZoneTableSegment::READ_WRITE, config_params_);

    // The old data should still be available.
    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));
}

TEST_F(ZoneTableSegmentMappedTest, resetReadOnly) {
    // At this point, the underlying file must not exist.
    ASSERT_FALSE(fileExists(mapped_file));

    // Open the underlying mapped file in read+write mode.
    ztable_segment_->reset(ZoneTableSegment::READ_WRITE, config_params_);

    ASSERT_TRUE(ztable_segment_->isUsable());
    ASSERT_TRUE(ztable_segment_->isWritable());

    // Add the data.
    addData(ztable_segment_->getMemorySegment());
    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));

    // Close the segment.
    ztable_segment_->clear();

    // At this point, the underlying file must still exist.
    ASSERT_TRUE(fileExists(mapped_file));

    // Open the underlying mapped file in read-only mode again.
    ztable_segment_->reset(ZoneTableSegment::READ_ONLY, config_params_);

    // The old data should still be available.
    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));

    // But trying to allocate new data should result in an exception as
    // the segment is read-only!
    EXPECT_THROW(addData(ztable_segment_->getMemorySegment()),
                 MemorySegmentError);
}

TEST_F(ZoneTableSegmentMappedTest, clearUninitialized) {
    // Clearing a segment that has not been reset() is a nop, as clear()
    // returns it to a fresh uninitialized state anyway.
    EXPECT_NO_THROW(ztable_segment_->clear());

    // The following should still throw, because the segment has not
    // been successfully reset() yet.
    EXPECT_THROW(ztable_segment_->getHeader(), isc::InvalidOperation);
    EXPECT_THROW(ztable_segment_->getMemorySegment(), isc::InvalidOperation);

    // isWritable() must still return false, because the segment has not
    // been successfully reset() yet.
    EXPECT_FALSE(ztable_segment_->isUsable());
    EXPECT_FALSE(ztable_segment_->isWritable());
}

TEST_F(ZoneTableSegmentMappedTest, clear) {
    // First, open an underlying mapped file in read+write mode (doesn't
    // exist yet)
    ztable_segment_->reset(ZoneTableSegment::READ_WRITE, config_params_);

    EXPECT_TRUE(ztable_segment_->isUsable());
    EXPECT_TRUE(ztable_segment_->isWritable());
    // The following method calls should no longer throw:
    EXPECT_NO_THROW(ztable_segment_->getHeader());
    EXPECT_NO_THROW(ztable_segment_->getMemorySegment());

    // Now, clear the segment.
    ztable_segment_->clear();

    EXPECT_FALSE(ztable_segment_->isUsable());
    EXPECT_FALSE(ztable_segment_->isWritable());
    // The following method calls should now throw.
    EXPECT_THROW(ztable_segment_->getHeader(), isc::InvalidOperation);
    EXPECT_THROW(ztable_segment_->getMemorySegment(), isc::InvalidOperation);
}

TEST_F(ZoneTableSegmentMappedTest, resetFailedCorruptedChecksum) {
    setupMappedFiles();

    // Open mapped file 1 in read-write mode
    ztable_segment_->reset(ZoneTableSegment::READ_WRITE, config_params_);

    // Corrupt mapped file 2.
    scoped_ptr<MemorySegmentMapped> segment
        (new MemorySegmentMapped(mapped_file2,
                                 MemorySegmentMapped::OPEN_OR_CREATE));
    EXPECT_TRUE(verifyData(*segment));
    corruptChecksum(*segment);
    segment.reset();

    // Resetting to mapped file 2 in read-write mode should fail
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::READ_WRITE, config_params2_);
    }, ResetFailed);

    EXPECT_TRUE(ztable_segment_->isUsable());
    EXPECT_TRUE(ztable_segment_->isWritable());
    // Check for the old data in the segment to make sure it is still
    // available and correct.
    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));
}

TEST_F(ZoneTableSegmentMappedTest, resetFailedMissingChecksum) {
    setupMappedFiles();

    // Open mapped file 1 in read-write mode
    ztable_segment_->reset(ZoneTableSegment::READ_WRITE, config_params_);

    // Corrupt mapped file 2.
    scoped_ptr<MemorySegmentMapped> segment
        (new MemorySegmentMapped(mapped_file2,
                                 MemorySegmentMapped::OPEN_OR_CREATE));
    EXPECT_TRUE(verifyData(*segment));
    deleteChecksum(*segment);
    segment.reset();

    // Resetting to mapped file 2 in read-only mode should fail
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::READ_ONLY, config_params2_);
    }, ResetFailed);

    EXPECT_TRUE(ztable_segment_->isUsable());
    EXPECT_TRUE(ztable_segment_->isWritable());
    // Check for the old data in the segment to make sure it is still
    // available and correct.
    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));
}

TEST_F(ZoneTableSegmentMappedTest, resetFailedMissingHeader) {
    setupMappedFiles();

    // Open mapped file 1 in read-write mode
    ztable_segment_->reset(ZoneTableSegment::READ_WRITE, config_params_);

    // Corrupt mapped file 2.
    scoped_ptr<MemorySegmentMapped> segment
        (new MemorySegmentMapped(mapped_file2,
                                 MemorySegmentMapped::OPEN_OR_CREATE));
    EXPECT_TRUE(verifyData(*segment));
    deleteHeader(*segment);
    segment.reset();

    // Resetting to mapped file 2 in read-only mode should fail
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::READ_ONLY, config_params2_);
    }, ResetFailed);

    EXPECT_TRUE(ztable_segment_->isUsable());
    EXPECT_TRUE(ztable_segment_->isWritable());
    // Check for the old data in the segment to make sure it is still
    // available and correct.
    EXPECT_TRUE(verifyData(ztable_segment_->getMemorySegment()));
}

TEST_F(ZoneTableSegmentMappedTest, resetCreateOverCorruptedFile) {
    setupMappedFiles();

    // Corrupt mapped file 1.
    scoped_ptr<MemorySegmentMapped> segment
        (new MemorySegmentMapped(mapped_file,
                                 MemorySegmentMapped::OPEN_OR_CREATE));
    EXPECT_TRUE(verifyData(*segment));
    corruptChecksum(*segment);
    segment.reset();

    // Resetting to mapped file 1 in CREATE mode over a corrupted file
    // should pass.
    EXPECT_NO_THROW(ztable_segment_->reset(ZoneTableSegment::CREATE,
                                           config_params_));

    EXPECT_TRUE(ztable_segment_->isUsable());
    EXPECT_TRUE(ztable_segment_->isWritable());
    // Check for the old data in the segment. It should not be present
    // (as we opened the segment in CREATE mode).
    EXPECT_FALSE(verifyData(ztable_segment_->getMemorySegment()));

    // Now try the same with missing checksum.
    setupMappedFiles();

    // Corrupt mapped file 1.
    segment.reset(new MemorySegmentMapped(mapped_file,
                                          MemorySegmentMapped::OPEN_OR_CREATE));
    EXPECT_TRUE(verifyData(*segment));
    deleteChecksum(*segment);
    segment.reset();

    // Resetting to mapped file 1 in CREATE mode over a file missing
    // checksum should pass.
    EXPECT_NO_THROW(ztable_segment_->reset(ZoneTableSegment::CREATE,
                                           config_params_));

    EXPECT_TRUE(ztable_segment_->isUsable());
    EXPECT_TRUE(ztable_segment_->isWritable());
    // Check for the old data in the segment. It should not be present
    // (as we opened the segment in CREATE mode).
    EXPECT_FALSE(verifyData(ztable_segment_->getMemorySegment()));
}

TEST_F(ZoneTableSegmentMappedTest, resetHeaderUninitialized) {
    // This should throw as we haven't called reset() yet.
    EXPECT_THROW(ztable_segment_->resetHeader(), isc::InvalidOperation);
}

TEST_F(ZoneTableSegmentMappedTest, resetHeader) {
    // First, open an underlying mapped file in read+write mode (doesn't
    // exist yet)
    ztable_segment_->reset(ZoneTableSegment::READ_WRITE, config_params_);

    // Check if a valid ZoneTable is found.
    {
        const ZoneTableHeader& header = ztable_segment_->getHeader();
        const ZoneTable* table = header.getTable();
        EXPECT_EQ(0, table->getZoneCount());
    }

    // Grow the segment by allocating something large.
    EXPECT_THROW(ztable_segment_->getMemorySegment().allocate(1<<16),
                 MemorySegmentGrown);

    // Reset the header address. This should not throw now.
    EXPECT_NO_THROW(ztable_segment_->resetHeader());

    // Check if a valid ZoneTable is found.
    {
        const ZoneTableHeader& header = ztable_segment_->getHeader();
        const ZoneTable* table = header.getTable();
        EXPECT_EQ(0, table->getZoneCount());
    }
}

} // anonymous namespace
