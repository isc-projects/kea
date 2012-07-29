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

#include <datasrc/zonetable.h>
// We use InMemoryZone to put something into the table
#include <datasrc/memory_datasrc.h>

#include <gtest/gtest.h>

using namespace isc::dns;
using namespace isc::datasrc;

namespace {
TEST(ZoneTest, init) {
    InMemoryZoneFinder zone(RRClass::IN(), Name("example.com"));
    EXPECT_EQ(Name("example.com"), zone.getOrigin());
    EXPECT_EQ(RRClass::IN(), zone.getClass());

    InMemoryZoneFinder ch_zone(RRClass::CH(), Name("example"));
    EXPECT_EQ(Name("example"), ch_zone.getOrigin());
    EXPECT_EQ(RRClass::CH(), ch_zone.getClass());
}

TEST(ZoneTest, find) {
    InMemoryZoneFinder zone(RRClass::IN(), Name("example.com"));
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              zone.find(Name("www.example.com"), RRType::A())->code);
}

class ZoneTableTest : public ::testing::Test {
protected:
    ZoneTableTest() : zone1(new InMemoryZoneFinder(RRClass::IN(),
                                                   Name("example.com"))),
                      zone2(new InMemoryZoneFinder(RRClass::IN(),
                                                   Name("example.net"))),
                      zone3(new InMemoryZoneFinder(RRClass::IN(),
                                                   Name("example"))),
                      zone_table(ZoneTable::create(mem_sgmt_))
    {}

    ~ZoneTableTest() {
        ZoneTable::destroy(mem_sgmt_, zone_table);
    }
    ZoneFinderPtr zone1, zone2, zone3;
    isc::util::MemorySegmentLocal mem_sgmt_;
    ZoneTable* zone_table;
};

TEST_F(ZoneTableTest, addZone) {
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zone1));
    EXPECT_EQ(result::EXIST, zone_table->addZone(mem_sgmt_, zone1));
    // names are compared in a case insensitive manner.
    EXPECT_EQ(result::EXIST, zone_table->addZone(
                  mem_sgmt_,
                  ZoneFinderPtr(new InMemoryZoneFinder(RRClass::IN(),
                                                       Name("EXAMPLE.COM")))));

    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zone2));
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zone3));

    // Zone table is indexed only by name.  Duplicate origin name with
    // different zone class isn't allowed.
    EXPECT_EQ(result::EXIST, zone_table->addZone(
                  mem_sgmt_,
                  ZoneFinderPtr(new InMemoryZoneFinder(RRClass::CH(),
                                                       Name("example.com")))));

    /// Bogus zone (NULL)
    EXPECT_THROW(zone_table->addZone(mem_sgmt_, ZoneFinderPtr()),
                 isc::InvalidParameter);
}

TEST_F(ZoneTableTest, DISABLED_removeZone) {
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zone1));
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zone2));
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zone3));

    EXPECT_EQ(result::SUCCESS, zone_table->removeZone(Name("example.net")));
    EXPECT_EQ(result::NOTFOUND, zone_table->removeZone(Name("example.net")));
}

TEST_F(ZoneTableTest, findZone) {
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zone1));
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zone2));
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zone3));

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
    ZoneFinderPtr zone_com(new InMemoryZoneFinder(RRClass::IN(), Name("com")));
    EXPECT_EQ(result::SUCCESS, zone_table->addZone(mem_sgmt_, zone_com));
    EXPECT_EQ(Name("example.com"),
              zone_table->findZone(Name("www.example.com")).zone->getOrigin());
}
}
