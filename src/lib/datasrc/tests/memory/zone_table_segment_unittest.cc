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

#include <datasrc/memory/zone_table_segment.h>
#include <datasrc/memory/zone_writer.h>
#include <gtest/gtest.h>

#include <boost/scoped_ptr.hpp>

using boost::scoped_ptr;
using isc::dns::Name;
using isc::dns::RRClass;
using namespace isc::datasrc::memory;
using namespace isc::data;
using namespace isc::util;
using namespace std;

namespace {

class ZoneTableSegmentTest : public ::testing::Test {
protected:
    ZoneTableSegmentTest() :
        config_(Element::fromJSON("{}")),
        segment_(ZoneTableSegment::create((*config_.get())))
    {}

    ~ZoneTableSegmentTest() {
        if (segment_ != NULL) {
            ZoneTableSegment::destroy(segment_);
        }
    }

    void TearDown() {
        // Catch any future leaks here.
        const MemorySegment& mem_sgmt = segment_->getMemorySegment();
        EXPECT_TRUE(mem_sgmt.allMemoryDeallocated());

        ZoneTableSegment::destroy(segment_);
        segment_ = NULL;
    }

    const ElementPtr config_;
    ZoneTableSegment* segment_;
};


TEST_F(ZoneTableSegmentTest, create) {
    // By default, a local zone table segment is created.
    EXPECT_NE(static_cast<void*>(NULL), segment_);
}

// Helper function to check const and non-const methods.
template <typename TS, typename TH, typename TT>
void
testGetHeader(ZoneTableSegment* segment) {
    TH& header = static_cast<TS*>(segment)->getHeader();

    // The zone table is unset.
    TT* table = header.getTable();
    EXPECT_EQ(static_cast<void*>(NULL), table);
}

TEST_F(ZoneTableSegmentTest, getHeader) {
    // non-const version.
    testGetHeader<ZoneTableSegment, ZoneTableHeader, ZoneTable>(segment_);

    // const version.
    testGetHeader<const ZoneTableSegment, const ZoneTableHeader,
                  const ZoneTable>(segment_);
}

TEST_F(ZoneTableSegmentTest, getMemorySegment) {
    // This doesn't do anything fun except test the API.
    MemorySegment& mem_sgmt = segment_->getMemorySegment();
    EXPECT_TRUE(mem_sgmt.allMemoryDeallocated());
}

ZoneData*
load_action(MemorySegment&) {
    // The function won't be called, so this is OK
    return (NULL);
}

// Test we can get a writer.
TEST_F(ZoneTableSegmentTest, getZoneWriter) {
    scoped_ptr<ZoneWriter>
        writer(segment_->getZoneWriter(load_action, Name("example.org"),
                                       RRClass::IN()));
    // We have to get something
    EXPECT_NE(static_cast<void*>(NULL), writer.get());
    // And for now, it should be the local writer
    EXPECT_NE(static_cast<void*>(NULL),
              dynamic_cast<ZoneWriterLocal*>(writer.get()));
}

} // anonymous namespace
