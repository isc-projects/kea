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
#include <boost/scoped_ptr.hpp>
#include <boost/interprocess/file_mapping.hpp>

#include <sys/stat.h>

using namespace isc::dns;
using namespace isc::datasrc::memory;
using namespace isc::data;
using namespace isc::util;
using namespace isc::util::random;
using namespace std;
using boost::scoped_ptr;

namespace {

const char* mapped_file = TEST_DATA_BUILDDIR "/test.mapped";

class ZoneTableSegmentMappedTest : public ::testing::Test {
protected:
    ZoneTableSegmentMappedTest() :
        ztable_segment_(
            ZoneTableSegment::create(RRClass::IN(), "mapped")),
        config_params_(
            Element::fromJSON(
                "{\"mapped-file\": \"" + std::string(mapped_file) + "\"}"))
    {
        EXPECT_NE(static_cast<void*>(NULL), ztable_segment_);
        // Verify that a ZoneTableSegmentMapped is created.
        ZoneTableSegmentMapped* mapped_segment =
            dynamic_cast<ZoneTableSegmentMapped*>(ztable_segment_);
        EXPECT_NE(static_cast<void*>(NULL), mapped_segment);
    }

    ~ZoneTableSegmentMappedTest() {
        ZoneTableSegment::destroy(ztable_segment_);
        boost::interprocess::file_mapping::remove(mapped_file);
    }

    ZoneTableSegment* ztable_segment_;
    const ConstElementPtr config_params_;
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
createData(MemorySegment& segment) {
    // For purposes of this test, we assume that the following
    // allocations do not resize the mapped segment. For this, we have
    // to keep the size of test data reasonably small.
    UniformRandomIntegerGenerator gen(0, INT_MAX, getpid());
    for (int i = 0; i < 256; ++i) {
        string name("name");
        name += i;
        const int value = gen();
        void* ptr = segment.allocate(sizeof (int));
        ASSERT_TRUE(ptr);
        *static_cast<int*>(ptr) = value;
        const bool grew = segment.setNamedAddress(name.c_str(), ptr);
        ASSERT_FALSE(grew);
    }
}

bool
verifyData(const MemorySegment& segment) {
    UniformRandomIntegerGenerator gen(0, INT_MAX, getpid());
    for (int i = 0; i < 256; ++i) {
        string name("name");
        name += i;
        const int value = gen();
        const MemorySegment::NamedAddressResult result =
            segment.getNamedAddress(name.c_str());
        if (!result.first) {
             return (false);
        }
        if (*static_cast<int*>(result.second) != value) {
             return (false);
        }
    }

    return (true);
}


TEST_F(ZoneTableSegmentMappedTest, getHeaderUninitialized) {
    // This should throw as we haven't called reset() yet.
    EXPECT_THROW(ztable_segment_->getHeader(), isc::InvalidOperation);
}

TEST_F(ZoneTableSegmentMappedTest, getMemorySegmentUninitialized) {
    // This should throw as we haven't called reset() yet.
    EXPECT_THROW(ztable_segment_->getMemorySegment(), isc::InvalidOperation);
}

TEST_F(ZoneTableSegmentMappedTest, isWritableUninitialized) {
    // isWritable() must return false by default, when the segment has
    // not been reset() yet.
    EXPECT_FALSE(ztable_segment_->isWritable());
}

TEST_F(ZoneTableSegmentMappedTest, resetBadConfig) {
    // NULL is passed in config params
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::CREATE,
                               ConstElementPtr());
    }, isc::InvalidParameter);

    // Not a map
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::CREATE,
                               Element::fromJSON("42"));
    }, isc::InvalidParameter);

    // Empty map
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::CREATE,
                               Element::fromJSON("{}"));
    }, isc::InvalidParameter);

    // No "mapped-file" key
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::CREATE,
                               Element::fromJSON("{\"foo\": \"bar\"}"));
    }, isc::InvalidParameter);

    // Value of "mapped-file" key is not a string
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::CREATE,
                               Element::fromJSON("{\"mapped-file\": 42}"));
    }, isc::InvalidParameter);

    // The following should still throw, unaffected by the failed opens.
    EXPECT_THROW(ztable_segment_->getHeader(), isc::InvalidOperation);
    EXPECT_THROW(ztable_segment_->getMemorySegment(), isc::InvalidOperation);

    // isWritable() must still return false, because the segment has not
    // been successfully reset() yet.
    EXPECT_FALSE(ztable_segment_->isWritable());
}

TEST_F(ZoneTableSegmentMappedTest, reset) {
    // By default, the mapped file doesn't exist, so we cannot open it
    // in READ_ONLY mode (which does not create the file).
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::READ_ONLY,
                               config_params_);
    }, MemorySegmentOpenError);

    // The following should still throw, unaffected by the failed open.
    EXPECT_THROW(ztable_segment_->getHeader(), isc::InvalidOperation);
    EXPECT_THROW(ztable_segment_->getMemorySegment(), isc::InvalidOperation);

    // isWritable() must still return false, because the segment has not
    // been successfully reset() yet.
    EXPECT_FALSE(ztable_segment_->isWritable());

    // READ_WRITE mode must create the mapped file if it doesn't exist
    // (and must not result in an exception).
    ztable_segment_->reset(ZoneTableSegment::READ_WRITE,
                           config_params_);
    // This must not throw now.
    EXPECT_TRUE(ztable_segment_->isWritable());

    // The following method calls should no longer throw:
    EXPECT_NO_THROW(ztable_segment_->getHeader());
    EXPECT_NO_THROW(ztable_segment_->getMemorySegment());

    // Let's try to re-open the mapped file in READ_ONLY mode. It should
    // not fail now.
    ztable_segment_->reset(ZoneTableSegment::READ_ONLY,
                           config_params_);
    EXPECT_FALSE(ztable_segment_->isWritable());

    // Re-creating the mapped file should erase old data and should not
    // trigger any exceptions inside reset() due to old data (such as
    // named addresses).
    ztable_segment_->reset(ZoneTableSegment::CREATE,
                           config_params_);
    EXPECT_TRUE(ztable_segment_->isWritable());

    // When we reset() with an invalid paramter and it fails, then the
    // segment should still be usable.
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::CREATE,
                               Element::fromJSON("{}"));
    }, isc::InvalidParameter);
    EXPECT_TRUE(ztable_segment_->isWritable());
    // The following should not throw.
    EXPECT_NO_THROW(ztable_segment_->getHeader());
    EXPECT_NO_THROW(ztable_segment_->getMemorySegment());

    // READ_WRITE with an existing map file ought to work too. This
    // would use existing named addresses. This actually re-opens the
    // currently open map.
    ztable_segment_->reset(ZoneTableSegment::READ_WRITE,
                           config_params_);
    EXPECT_TRUE(ztable_segment_->isWritable());
}

TEST_F(ZoneTableSegmentMappedTest, resetCreate) {
    // At this point, the underlying file must not exist.
    ASSERT_FALSE(fileExists(mapped_file));

    // Open the underlying mapped file in create mode.
    ztable_segment_->reset(ZoneTableSegment::CREATE, config_params_);

    ASSERT_TRUE(ztable_segment_->isWritable());

    // Create the data.
    createData(ztable_segment_->getMemorySegment());
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

    ASSERT_TRUE(ztable_segment_->isWritable());

    // Create the data.
    createData(ztable_segment_->getMemorySegment());
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

    ASSERT_TRUE(ztable_segment_->isWritable());

    // Create the data.
    createData(ztable_segment_->getMemorySegment());
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
    EXPECT_THROW(createData(ztable_segment_->getMemorySegment()),
                 MemorySegmentError);
}

TEST_F(ZoneTableSegmentMappedTest, clear) {
    // First, open an underlying mapped file in read+write mode (doesn't
    // exist yet)
    ztable_segment_->reset(ZoneTableSegment::READ_WRITE,
                           config_params_);

    EXPECT_TRUE(ztable_segment_->isWritable());
    // The following method calls should no longer throw:
    EXPECT_NO_THROW(ztable_segment_->getHeader());
    EXPECT_NO_THROW(ztable_segment_->getMemorySegment());

    // Now, clear the segment.
    ztable_segment_->clear();

    EXPECT_FALSE(ztable_segment_->isWritable());
    // The following method calls should now throw.
    EXPECT_THROW(ztable_segment_->getHeader(), isc::InvalidOperation);
    EXPECT_THROW(ztable_segment_->getMemorySegment(), isc::InvalidOperation);
}

} // anonymous namespace
