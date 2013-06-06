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

#include <datasrc/memory/zone_writer.h>
#include <datasrc/memory/zone_table_segment_local.h>

#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

using namespace isc::dns;
using namespace isc::datasrc::memory;
using namespace isc::data;
using namespace isc::util;
using namespace std;
using boost::scoped_ptr;

namespace {

class ZoneTableSegmentTest : public ::testing::Test {
protected:
    ZoneTableSegmentTest() :
        ztable_segment_(ZoneTableSegment::create(RRClass::IN(), "local"))
    {}

    void TearDown() {
        ZoneTableSegment::destroy(ztable_segment_);
        ztable_segment_ = NULL;
    }

    ZoneTableSegment* ztable_segment_;
};

TEST_F(ZoneTableSegmentTest, getImplType) {
    EXPECT_EQ("local", ztable_segment_->getImplType());
}

TEST_F(ZoneTableSegmentTest, create) {
    // By default, a local zone table segment is created.
    EXPECT_NE(static_cast<void*>(NULL), ztable_segment_);

    // Unknown types of segment are rejected.
    EXPECT_THROW(ZoneTableSegment::create(RRClass::IN(), "unknown"),
                 UnknownSegmentType);
}

TEST_F(ZoneTableSegmentTest, reset) {
    // reset() should throw that it's not implemented so that any
    // accidental calls are found out.
    EXPECT_THROW({
        ztable_segment_->reset(ZoneTableSegment::CREATE,
                               Element::fromJSON("{}"));
    }, isc::NotImplemented);
}

TEST_F(ZoneTableSegmentTest, clear) {
    // clear() should throw that it's not implemented so that any
    // accidental calls are found out.
    EXPECT_THROW(ztable_segment_->clear(), isc::NotImplemented);
}

// Helper function to check const and non-const methods.
template <typename TS, typename TH, typename TT>
void
testGetHeader(ZoneTableSegment* ztable_segment) {
    TH& header = static_cast<TS*>(ztable_segment)->getHeader();

    // The zone table must be set.
    TT* table = header.getTable();
    EXPECT_NE(static_cast<void*>(NULL), table);
}

TEST_F(ZoneTableSegmentTest, getHeader) {
    // non-const version.
    testGetHeader<ZoneTableSegment, ZoneTableHeader, ZoneTable>
        (ztable_segment_);

    // const version.
    testGetHeader<const ZoneTableSegment, const ZoneTableHeader,
                  const ZoneTable>(ztable_segment_);
}

TEST_F(ZoneTableSegmentTest, getMemorySegment) {
    // This doesn't do anything fun except test the API.
    MemorySegment& mem_sgmt = ztable_segment_->getMemorySegment();
    mem_sgmt.allMemoryDeallocated(); // use mem_sgmt
}

TEST_F(ZoneTableSegmentTest, isUsable) {
    // Local segments are always usable.
    EXPECT_TRUE(ztable_segment_->isUsable());
}

TEST_F(ZoneTableSegmentTest, isWritable) {
    // Local segments are always writable.
    EXPECT_TRUE(ztable_segment_->isWritable());
}

} // anonymous namespace
