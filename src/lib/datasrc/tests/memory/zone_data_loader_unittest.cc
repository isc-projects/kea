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

#include <config.h>

#include <datasrc/memory/zone_data_loader.h>
#include <datasrc/memory/rdataset.h>
#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/zone_data_updater.h>
#include <datasrc/memory/segment_object_holder.h>
#include <datasrc/zone_iterator.h>

#include <util/buffer.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rdataclass.h>
#ifdef USE_SHARED_MEMORY
#include <util/memory_segment_mapped.h>
#endif
#include <util/memory_segment_local.h>

#include <datasrc/tests/memory/memory_segment_mock.h>

#include <gtest/gtest.h>

using namespace isc::dns;
using namespace isc::datasrc::memory;
#ifdef USE_SHARED_MEMORY
using isc::util::MemorySegmentMapped;
#endif
using isc::datasrc::memory::detail::SegmentObjectHolder;

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
    test::MemorySegmentMock mem_sgmt_;
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

TEST_F(ZoneDataLoaderTest, zoneMinTTL) {
    // This should hold outside of the loader class, but we do double check.
    zone_data_ = loadZoneData(mem_sgmt_, zclass_, Name("example.org"),
                              TEST_DATA_DIR
                              "/example.org-nsec3-signed.zone");
    isc::util::InputBuffer b(zone_data_->getMinTTLData(), sizeof(uint32_t));
    EXPECT_EQ(RRTTL(1200), RRTTL(b));
}

// Load bunch of small zones, hoping some of the relocation will happen
// during the memory creation, not only Rdata creation.
// Note: this doesn't even compile unless USE_SHARED_MEMORY is defined.
#ifdef USE_SHARED_MEMORY
TEST(ZoneDataLoaterTest, relocate) {
    const char* const mapped_file = TEST_DATA_BUILDDIR "/test.mapped";
    MemorySegmentMapped segment(mapped_file,
                                isc::util::MemorySegmentMapped::CREATE_ONLY,
                                4096);
    const size_t zone_count = 10000;
    typedef SegmentObjectHolder<ZoneData, RRClass> Holder;
    typedef boost::shared_ptr<Holder> HolderPtr;
    std::vector<HolderPtr> zones;
    for (size_t i = 0; i < zone_count; ++i) {
        // Load some zone
        ZoneData* data = loadZoneData(segment, RRClass::IN(),
                                      Name("example.org"),
                                      TEST_DATA_DIR
                                      "/example.org-nsec3-signed.zone");
        // Store it, so it is cleaned up later
        zones.push_back(HolderPtr(new Holder(segment, RRClass::IN())));
        zones.back()->set(data);

    }
    // Deallocate all the zones now.
    zones.clear();
    EXPECT_TRUE(segment.allMemoryDeallocated());
    EXPECT_EQ(0, unlink(mapped_file));
}
#endif

}
