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

#include <dns/name.h>
#include <dns/rrclass.h>

#include <datasrc/memory_datasrc.h>

#include <gtest/gtest.h>

using namespace isc::dns;
using namespace isc::datasrc;

namespace {

class MemoryDataSrcTest : public ::testing::Test {
protected:
    MemoryDataSrcTest()
    {}
    MemoryDataSrc memory_datasrc;
};

TEST_F(MemoryDataSrcTest, add_find_Zone) {
    // test add zone
    // Bogus zone (NULL)
    EXPECT_THROW(memory_datasrc.addZone(ZonePtr()), isc::InvalidParameter);

    // add zones with different names one by one
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::IN(), Name("a")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::CH(), Name("b")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::IN(), Name("c")))));
    // add zones with the same name suffix
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::CH(),
                                         Name("x.d.e.f")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::CH(),
                                         Name("o.w.y.d.e.f")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::CH(),
                                         Name("p.w.y.d.e.f")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::IN(),
                                         Name("q.w.y.d.e.f")))));
    // add super zone and its subzone
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::CH(), Name("g.h")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::IN(), Name("i.g.h")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::IN(),
                                         Name("z.d.e.f")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::IN(),
                                         Name("j.z.d.e.f")))));

    // different zone class isn't allowed.
    EXPECT_EQ(result::EXIST, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::CH(),
                                         Name("q.w.y.d.e.f")))));

    // names are compared in a case insensitive manner.
    EXPECT_EQ(result::EXIST, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::IN(),
                                         Name("Q.W.Y.d.E.f")))));

    // test find zone
    EXPECT_EQ(result::SUCCESS, memory_datasrc.findZone(Name("a")).code);
    EXPECT_EQ(Name("a"),
              memory_datasrc.findZone(Name("a")).zone->getOrigin());

    EXPECT_EQ(result::SUCCESS,
              memory_datasrc.findZone(Name("j.z.d.e.f")).code);
    EXPECT_EQ(Name("j.z.d.e.f"),
              memory_datasrc.findZone(Name("j.z.d.e.f")).zone->getOrigin());

    // NOTFOUND
    EXPECT_EQ(result::NOTFOUND, memory_datasrc.findZone(Name("d.e.f")).code);
    EXPECT_EQ(ConstZonePtr(), memory_datasrc.findZone(Name("d.e.f")).zone);

    EXPECT_EQ(result::NOTFOUND,
              memory_datasrc.findZone(Name("w.y.d.e.f")).code);
    EXPECT_EQ(ConstZonePtr(),
              memory_datasrc.findZone(Name("w.y.d.e.f")).zone);

    // there's no exact match.  the result should be the longest match,
    // and the code should be PARTIALMATCH.
    EXPECT_EQ(result::PARTIALMATCH,
              memory_datasrc.findZone(Name("j.g.h")).code);
    EXPECT_EQ(Name("g.h"),
              memory_datasrc.findZone(Name("g.h")).zone->getOrigin());

    EXPECT_EQ(result::PARTIALMATCH,
              memory_datasrc.findZone(Name("z.i.g.h")).code);
    EXPECT_EQ(Name("i.g.h"),
              memory_datasrc.findZone(Name("z.i.g.h")).zone->getOrigin());
}
}
