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

#include <dns/name.h>
#include <dns/rrclass.h>

#include <datasrc/memory/rdataset.h>
#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/zone_data_updater.h>
#include <datasrc/memory/zone_data_loader.h>

#include "memory_segment_test.h"

#include <gtest/gtest.h>

using namespace isc::dns;
using namespace isc::datasrc::memory;

namespace {

class ZoneDataLoaderTest : public ::testing::Test {
protected:
    ZoneDataLoaderTest() : zclass_(RRClass::IN()), zone_data_(NULL) {}
    void TearDown() {
        if (zone_data_ != NULL) {
            ZoneData::destroy(mem_sgmt_, zone_data_, zclass_);
        }
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated()); // catch any leak here.
    }
    const RRClass zclass_;
    test::MemorySegmentTest mem_sgmt_;
    ZoneData* zone_data_;
};

TEST_F(ZoneDataLoaderTest, loadRRSIGFollowsNothing) {
    // This causes the situation where an RRSIG is added without a covered
    // RRset.  It will be accepted, and corresponding "sig-only" rdata will
    // be created.
    zone_data_ = loadZoneData(mem_sgmt_, zclass_, Name("example.org"),
                              TEST_DATA_DIR
                              "/example.org-rrsig-follows-nothing.zone");
    ZoneNode* node = NULL;
    zone_data_->insertName(mem_sgmt_, Name("ns1.example.org"), &node);
    ASSERT_NE(static_cast<ZoneNode*>(NULL), node);
    const RdataSet* rdset = node->getData();
    ASSERT_NE(static_cast<RdataSet*>(NULL), rdset);
    EXPECT_EQ(RRType::A(), rdset->type); // there should be only 1 data here
    EXPECT_EQ(0, rdset->getRdataCount()); // no RDATA
    EXPECT_EQ(1, rdset->getSigRdataCount()); // but 1 SIG

    // Teardown checks for memory segment leaks
}

}
