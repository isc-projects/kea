// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#include <gtest/gtest.h>

using namespace isc::dns;
using namespace isc::datasrc;
using namespace isc::datasrc::memory;

namespace {
class ZoneTableTest : public ::testing::Test {
protected:
    ZoneTableTest() : zname1(Name("example.com")),
                      zname2(Name("example.net")),
                      zname3(Name("example")),
                      zone1(new ZoneData(RRClass::IN(), zname1)),
                      zone2(new ZoneData(RRClass::IN(), zname2)),
                      zone3(new ZoneData(RRClass::IN(), zname3)),
                      zone_table(ZoneTable::create(mem_sgmt_))
    {}

    ~ZoneTableTest() {
        ZoneTable::destroy(mem_sgmt_, zone_table);
    }
    const Name zname1, zname2, zname3;
    ZoneData* zone1;
    ZoneData* zone2;
    ZoneData* zone3;
    isc::util::MemorySegmentLocal mem_sgmt_;
    ZoneTable* zone_table;
};

TEST_F(ZoneTableTest, addZone) {
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zname1, zone1));
    EXPECT_EQ(result::EXIST, zone_table->addZone(mem_sgmt_, zname1, zone1));
    // names are compared in a case insensitive manner.
    EXPECT_EQ(result::EXIST, zone_table->addZone(
                  mem_sgmt_, Name("EXAMPLE.COM"),
                  new ZoneData(RRClass::IN(), Name("EXAMPLE.COM"))));

    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zname2, zone2));
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zname3, zone3));

    // Zone table is indexed only by name.  Duplicate origin name with
    // different zone class isn't allowed.
    EXPECT_EQ(result::EXIST, zone_table->addZone(
                  mem_sgmt_, Name("example.com"),
                  new ZoneData(RRClass::CH(), Name("example.com"))));

    /// Bogus zone (NULL)
    EXPECT_THROW(zone_table->addZone(mem_sgmt_, zname1, NULL),
                 isc::InvalidParameter);
}

TEST_F(ZoneTableTest, DISABLED_removeZone) {
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zname1, zone1));
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zname2, zone2));
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zname3, zone3));

    EXPECT_EQ(result::SUCCESS, zone_table->removeZone(Name("example.net")));
    EXPECT_EQ(result::NOTFOUND, zone_table->removeZone(Name("example.net")));
}

TEST_F(ZoneTableTest, DISABLED_findZone) {
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zname1, zone1));
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zname2, zone2));
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zname3, zone3));

    EXPECT_EQ(result::SUCCESS, zone_table->findZone(Name("example.com")).code);
    EXPECT_EQ(Name("example.com"),
              zone_table->findZone(Name("example.com")).zone->getOrigin());

    EXPECT_EQ(result::NOTFOUND,
              zone_table->findZone(Name("example.org")).code);
    EXPECT_EQ(ConstZoneFinderPtr(),
              zone_table->findZone(Name("example.org")).zone);

    // there's no exact match.  the result should be the longest match,
    // and the code should be PARTIALMATCH.
    EXPECT_EQ(result::PARTIALMATCH,
              zone_table->findZone(Name("www.example.com")).code);
    EXPECT_EQ(Name("example.com"),
              zone_table->findZone(Name("www.example.com")).zone->getOrigin());

    // make sure the partial match is indeed the longest match by adding
    // a zone with a shorter origin and query again.
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_,
                                                   Name("com"),
                                                   new ZoneData(RRClass::IN(),
                                                                Name("com"))));
    EXPECT_EQ(Name("example.com"),
              zone_table->findZone(Name("www.example.com")).zone->getOrigin());
}
}
