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
#include <dns/rrclass.h>

#include <datasrc/result.h>
#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/zone_table.h>
#include <datasrc/memory/segment_object_holder.h>

#include <datasrc/tests/memory/memory_segment_mock.h>

#include <gtest/gtest.h>

#include <new>                  // for bad_alloc

using namespace isc::dns;
using namespace isc::datasrc;
using namespace isc::datasrc::memory;
using namespace isc::datasrc::memory::detail;

namespace {
class ZoneTableTest : public ::testing::Test {
protected:
    ZoneTableTest() : zclass_(RRClass::IN()),
                      zname1(Name("example.com")),
                      zname2(Name("example.net")),
                      zname3(Name("example")),
                      zone_table(ZoneTable::create(mem_sgmt_, zclass_))
    {}
    ~ZoneTableTest() {
        if (zone_table != NULL) {
            ZoneTable::destroy(mem_sgmt_, zone_table);
        }
    }
    void TearDown() {
        ZoneTable::destroy(mem_sgmt_, zone_table);
        zone_table = NULL;
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated()); // catch any leak here.
    }
    const RRClass zclass_;
    const Name zname1, zname2, zname3;
    test::MemorySegmentMock mem_sgmt_;
    ZoneTable* zone_table;
};

TEST_F(ZoneTableTest, create) {
    // Test about creating a zone table.  Normal case covers through other
    // tests.  We only check exception safety by letting the test memory
    // segment throw.
    mem_sgmt_.setThrowCount(2);
    EXPECT_THROW(ZoneTable::create(mem_sgmt_, zclass_), std::bad_alloc);
    // This shouldn't cause memory leak (that would be caught in TearDown()).
}

TEST_F(ZoneTableTest, addZone) {
    // By default there's no zone contained.
    EXPECT_EQ(0, zone_table->getZoneCount());

    // It doesn't accept NULL as zone data
    EXPECT_THROW(zone_table->addZone(mem_sgmt_, zname1, NULL),
                 isc::InvalidParameter);
    EXPECT_EQ(0, zone_table->getZoneCount()); // count is still 0

    // or an empty zone data
    SegmentObjectHolder<ZoneData, RRClass> holder_empty(
        mem_sgmt_, zclass_);
    holder_empty.set(ZoneData::create(mem_sgmt_));
    EXPECT_THROW(zone_table->addZone(mem_sgmt_, zname1, holder_empty.get()),
                 isc::InvalidParameter);

    SegmentObjectHolder<ZoneData, RRClass> holder1(
        mem_sgmt_, zclass_);
    holder1.set(ZoneData::create(mem_sgmt_, zname1));
    const ZoneData* data1(holder1.get());
    // Normal successful case.
    const ZoneTable::AddResult result1(zone_table->addZone(mem_sgmt_, zname1,
                                                           holder1.release()));
    EXPECT_EQ(result::SUCCESS, result1.code);
    EXPECT_EQ(static_cast<const ZoneData*>(NULL), result1.zone_data);
    // It got released by it
    EXPECT_EQ(static_cast<const ZoneData*>(NULL), holder1.get());
    EXPECT_EQ(1, zone_table->getZoneCount()); // count is now incremented

    // Duplicate add replaces the existing data wit the newly added one.
    SegmentObjectHolder<ZoneData, RRClass> holder2(mem_sgmt_, zclass_);
    holder2.set(ZoneData::create(mem_sgmt_, zname1));
    const ZoneTable::AddResult result2(zone_table->addZone(mem_sgmt_, zname1,
                                                           holder2.release()));
    EXPECT_EQ(result::EXIST, result2.code);
    // The old one gets out
    EXPECT_EQ(data1, result2.zone_data);
    // It releases this one even when we replace the old zone
    EXPECT_EQ(static_cast<const ZoneData*>(NULL), holder2.get());
    // We need to release the old one manually
    ZoneData::destroy(mem_sgmt_, result2.zone_data, zclass_);
    EXPECT_EQ(1, zone_table->getZoneCount()); // count doesn't change.

    SegmentObjectHolder<ZoneData, RRClass> holder3(
        mem_sgmt_, zclass_);
    holder3.set(ZoneData::create(mem_sgmt_, Name("EXAMPLE.COM")));
    // names are compared in a case insensitive manner.
    const ZoneTable::AddResult result3(zone_table->addZone(mem_sgmt_,
                                                           Name("EXAMPLE.COM"),
                                                           holder3.release()));
    EXPECT_EQ(result::EXIST, result3.code);
    ZoneData::destroy(mem_sgmt_, result3.zone_data, zclass_);
    // Add some more different ones.  Should just succeed.
    SegmentObjectHolder<ZoneData, RRClass> holder4(
        mem_sgmt_, zclass_);
    holder4.set(ZoneData::create(mem_sgmt_, zname2));
    EXPECT_EQ(result::SUCCESS,
              zone_table->addZone(mem_sgmt_, zname2, holder4.release()).code);
    EXPECT_EQ(2, zone_table->getZoneCount());
    SegmentObjectHolder<ZoneData, RRClass> holder5(
        mem_sgmt_, zclass_);
    holder5.set(ZoneData::create(mem_sgmt_, zname3));
    EXPECT_EQ(result::SUCCESS,
              zone_table->addZone(mem_sgmt_, zname3, holder5.release()).code);
    EXPECT_EQ(3, zone_table->getZoneCount());

    // Have the memory segment throw an exception in extending the internal
    // tree.  We'll destroy it after that via SegmentObjectHolder.
    SegmentObjectHolder<ZoneData, RRClass> holder6(
        mem_sgmt_, zclass_);
    holder6.set(ZoneData::create(mem_sgmt_, Name("example.org")));
    mem_sgmt_.setThrowCount(1);
    EXPECT_THROW(zone_table->addZone(mem_sgmt_, Name("example.org"),
                                     holder6.get()),
                 std::bad_alloc);
}

TEST_F(ZoneTableTest, addEmptyZone) {
    // By default there's no zone contained.
    EXPECT_EQ(0, zone_table->getZoneCount());

    // Adding an empty zone.  It should succeed.
    const ZoneTable::AddResult result1 =
        zone_table->addEmptyZone(mem_sgmt_, zname1);
    EXPECT_EQ(result::SUCCESS, result1.code);
    EXPECT_EQ(static_cast<const ZoneData*>(NULL), result1.zone_data);
    EXPECT_EQ(1, zone_table->getZoneCount());

    // The empty zone can be "found", with the ZONE_EMPTY flag on, and the
    // returned ZoneData being NULL.
    const ZoneTable::FindResult fresult1 = zone_table->findZone(zname1);
    EXPECT_EQ(result::SUCCESS, fresult1.code);
    EXPECT_EQ(result::ZONE_EMPTY, fresult1.flags);
    EXPECT_EQ(static_cast<const ZoneData*>(NULL), fresult1.zone_data);

    // Replacing an empty zone with non-empty one.  Should be no problem, but
    // the empty zone data are not returned in the result structure; it's
    // internal to the ZoneTable implementation.
    SegmentObjectHolder<ZoneData, RRClass> holder2(mem_sgmt_, zclass_);
    holder2.set(ZoneData::create(mem_sgmt_, zname1));
    const ZoneTable::AddResult result2(zone_table->addZone(mem_sgmt_, zname1,
                                                           holder2.release()));
    EXPECT_EQ(result::EXIST, result2.code);
    EXPECT_EQ(static_cast<const ZoneData*>(NULL), result2.zone_data);
    EXPECT_EQ(1, zone_table->getZoneCount());

    // Replacing a non-empty zone with an empty one is also okay.  It's not
    // different from replacing with another non-empty one.
    const ZoneTable::AddResult result3 =
        zone_table->addEmptyZone(mem_sgmt_, zname1);
    EXPECT_EQ(result::EXIST, result3.code);
    EXPECT_NE(static_cast<const ZoneData*>(NULL), result3.zone_data);
    ZoneData::destroy(mem_sgmt_, result3.zone_data, zclass_);
    EXPECT_EQ(1, zone_table->getZoneCount());
}

TEST_F(ZoneTableTest, findZone) {
    SegmentObjectHolder<ZoneData, RRClass> holder1(
        mem_sgmt_, zclass_);
    holder1.set(ZoneData::create(mem_sgmt_, zname1));
    ZoneData* zone_data = holder1.get();
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zname1,
                                                   holder1.release()).code);
    SegmentObjectHolder<ZoneData, RRClass> holder2(
        mem_sgmt_, zclass_);
    holder2.set(ZoneData::create(mem_sgmt_, zname2));
    EXPECT_EQ(result::SUCCESS,
              zone_table->addZone(mem_sgmt_, zname2, holder2.release()).code);
    SegmentObjectHolder<ZoneData, RRClass> holder3(
        mem_sgmt_, zclass_);
    holder3.set(ZoneData::create(mem_sgmt_, zname3));
    EXPECT_EQ(result::SUCCESS,
              zone_table->addZone(mem_sgmt_, zname3, holder3.release()).code);

    const ZoneTable::FindResult find_result1 =
        zone_table->findZone(Name("example.com"));
    EXPECT_EQ(result::SUCCESS, find_result1.code);
    EXPECT_EQ(zone_data, find_result1.zone_data);

    EXPECT_EQ(result::NOTFOUND,
              zone_table->findZone(Name("example.org")).code);
    EXPECT_EQ(static_cast<ZoneData*>(NULL),
              zone_table->findZone(Name("example.org")).zone_data);

    // there's no exact match.  the result should be the longest match,
    // and the code should be PARTIALMATCH.
    EXPECT_EQ(result::PARTIALMATCH,
              zone_table->findZone(Name("www.example.com")).code);
    EXPECT_EQ(zone_data,
              zone_table->findZone(Name("www.example.com")).zone_data);

    // make sure the partial match is indeed the longest match by adding
    // a zone with a shorter origin and query again.
    SegmentObjectHolder<ZoneData, RRClass> holder4(
        mem_sgmt_, zclass_);
    holder4.set(ZoneData::create(mem_sgmt_, Name("com")));
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, Name("com"),
                                                   holder4.release()).code);
    EXPECT_EQ(zone_data,
              zone_table->findZone(Name("www.example.com")).zone_data);
}
}
