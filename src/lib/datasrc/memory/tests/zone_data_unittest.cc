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

#include <exceptions/exceptions.h>

#include <util/memory_segment_local.h>

#include <dns/name.h>
#include <dns/labelsequence.h>

#include <datasrc/memory/rdata_encoder.h>
#include <datasrc/memory/rdataset.h>
#include <datasrc/memory/zone_data.h>

#include <gtest/gtest.h>

using namespace isc::dns;
using namespace isc::datasrc::memory;

namespace {

class ZoneDataTest : public ::testing::Test {
protected:
    ZoneDataTest() : zname_("example.com") {}
    void TearDown() {
        // detect any memory leak in the test memory segment
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated());
    }

    const Name zname_;
    isc::util::MemorySegmentLocal mem_sgmt_;
    RdataEncoder encoder_;
};

TEST_F(ZoneDataTest, create) {
    ZoneData* zone_data = ZoneData::create(mem_sgmt_, zname_);
    EXPECT_EQ(LabelSequence(zname_), zone_data->getOriginNode()->getLabels());
    ZoneData::destroy(mem_sgmt_, zone_data);
}
}
