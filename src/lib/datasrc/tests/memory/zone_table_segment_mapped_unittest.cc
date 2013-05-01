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

#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <boost/interprocess/file_mapping.hpp>

using namespace isc::dns;
using namespace isc::datasrc::memory;
using namespace isc::data;
using namespace isc::util;
using namespace std;
using boost::scoped_ptr;

namespace {

const std::string mapped_file = TEST_DATA_BUILDDIR "/test.mapped";

class ZoneTableSegmentMappedTest : public ::testing::Test {
protected:
    ZoneTableSegmentMappedTest() :
        ztable_segment_(dynamic_cast<ZoneTableSegmentMapped*>(
            ZoneTableSegment::create(RRClass::IN(), "mapped"))),
        config_params_(
            Element::fromJSON("{\"mapped-file\": \"" + mapped_file + "\"}"))
    {
        // Verify that a ZoneTableSegmentMapped is created.
        EXPECT_NE(static_cast<void*>(NULL), ztable_segment_);
    }

    ~ZoneTableSegmentMappedTest() {
        boost::interprocess::file_mapping::remove(mapped_file.c_str());
    }

    void TearDown() {
        ZoneTableSegment::destroy(ztable_segment_);
        ztable_segment_ = NULL;
    }

    ZoneTableSegmentMapped* ztable_segment_;
    const ConstElementPtr config_params_;
};

TEST_F(ZoneTableSegmentMappedTest, getHeaderUninitialized) {
    // This should throw as we haven't called reset() yet.
    EXPECT_THROW(ztable_segment_->getHeader(), isc::Unexpected);
}

TEST_F(ZoneTableSegmentMappedTest, getMemorySegmentUninitialized) {
    // This should throw as we haven't called reset() yet.
    EXPECT_THROW(ztable_segment_->getMemorySegment(), isc::Unexpected);
}

TEST_F(ZoneTableSegmentMappedTest, isWritableUninitialized) {
    // This should throw as we haven't called reset() yet.
    EXPECT_THROW(ztable_segment_->isWritable(), isc::Unexpected);
}

ZoneData*
loadAction(MemorySegment&) {
    // The function won't be called, so this is OK
    return (NULL);
}

// Test we can get a writer.
TEST_F(ZoneTableSegmentMappedTest, getZoneWriterUninitialized) {
    // This should throw as we haven't called reset() yet.
    EXPECT_THROW({
        ztable_segment_->getZoneWriter(loadAction, Name("example.org"),
                                       RRClass::IN());
    }, isc::Unexpected);
}

TEST_F(ZoneTableSegmentMappedTest, resetBadConfig) {
    // Not a map
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegmentMapped::CREATE,
                               Element::fromJSON("42"));
    }, isc::InvalidParameter);

    // Empty map
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegmentMapped::CREATE,
                               Element::fromJSON("{}"));
    }, isc::InvalidParameter);

    // No "mapped-file" key
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegmentMapped::CREATE,
                               Element::fromJSON("{\"foo\": \"bar\"}"));
    }, isc::InvalidParameter);

    // Value of "mapped-file" key is not a string
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegmentMapped::CREATE,
                               Element::fromJSON("{\"mapped-file\": 42}"));
    }, isc::InvalidParameter);

    // The following should still throw, unaffected by the failed opens.
    EXPECT_THROW(ztable_segment_->getHeader(), isc::Unexpected);
    EXPECT_THROW(ztable_segment_->getMemorySegment(), isc::Unexpected);
    EXPECT_THROW(ztable_segment_->isWritable(), isc::Unexpected);
}

TEST_F(ZoneTableSegmentMappedTest, reset) {
    // By default, the mapped file doesn't exist, so we cannot open it
    // in READ_ONLY mode (which does not create the file).
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegmentMapped::READ_ONLY,
                               config_params_);
    }, MemorySegmentOpenError);

    // The following should still throw, unaffected by the failed open.
    EXPECT_THROW(ztable_segment_->getHeader(), isc::Unexpected);
    EXPECT_THROW(ztable_segment_->getMemorySegment(), isc::Unexpected);
    EXPECT_THROW(ztable_segment_->isWritable(), isc::Unexpected);

    // READ_WRITE mode must create the mapped file if it doesn't exist
    // (and must not result in an exception).
    ztable_segment_->reset(ZoneTableSegmentMapped::READ_WRITE,
                           config_params_);
    // This must not throw now.
    EXPECT_TRUE(ztable_segment_->isWritable());

    // The following method calls should no longer throw:
    EXPECT_NO_THROW(ztable_segment_->getHeader());
    EXPECT_NO_THROW(ztable_segment_->getMemorySegment());
    EXPECT_NO_THROW(ztable_segment_->isWritable());

    // Let's try to re-open the mapped file in READ_ONLY mode. It should
    // not fail now.
    ztable_segment_->reset(ZoneTableSegmentMapped::READ_ONLY,
                           config_params_);
    EXPECT_FALSE(ztable_segment_->isWritable());

    // Re-creating the mapped file should erase old data and should not
    // trigger any exceptions inside reset() due to old data (such as
    // named addresses).
    ztable_segment_->reset(ZoneTableSegmentMapped::CREATE,
                           config_params_);
    EXPECT_TRUE(ztable_segment_->isWritable());

    // When we reset() and it fails, then the segment should be
    // unusable.
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegmentMapped::CREATE,
                               Element::fromJSON("{}"));
    }, isc::InvalidParameter);
    // The following should throw now.
    EXPECT_THROW(ztable_segment_->getHeader(), isc::Unexpected);
    EXPECT_THROW(ztable_segment_->getMemorySegment(), isc::Unexpected);
    EXPECT_THROW(ztable_segment_->isWritable(), isc::Unexpected);

    // READ_WRITE with an existing map file ought to work too. This
    // would use existing named addresses.
    ztable_segment_->reset(ZoneTableSegmentMapped::READ_WRITE,
                           config_params_);
    EXPECT_TRUE(ztable_segment_->isWritable());
}

} // anonymous namespace
