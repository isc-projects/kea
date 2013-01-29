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


#include <datasrc/memory/rrset_collection.h>

#include "memory_segment_test.h"

#include <datasrc/memory/zone_data_loader.h>
#include <datasrc/memory/segment_object_holder.h>
#include <dns/rrttl.h>
#include <dns/rdataclass.h>

#include <gtest/gtest.h>

using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace std;
using namespace isc::datasrc;
using namespace isc::datasrc::memory;
using namespace isc::datasrc::memory::detail;

namespace {

// Note: This class uses loadZoneData() to construct a ZoneData object,
// which internally uses an RRsetCollection for validation. We assume
// that loadZoneData() works at this point and test the RRsetCollection
// around the ZoneData returned.
class RRsetCollectionTest : public ::testing::Test {
public:
    RRsetCollectionTest() :
        rrclass("IN"),
        origin("example.org"),
        zone_file(TEST_DATA_DIR "/rrset-collection.zone"),
        zone_data_holder(mem_sgmt,
                         loadZoneData(mem_sgmt, rrclass, origin, zone_file),
                         rrclass),
        collection(*zone_data_holder.get(), rrclass)
    {}

    const RRClass rrclass;
    const Name origin;
    std::string zone_file;
    test::MemorySegmentTest mem_sgmt;
    SegmentObjectHolder<ZoneData, RRClass> zone_data_holder;
    RRsetCollection collection;
};

TEST_F(RRsetCollectionTest, find) {
    const RRsetCollection& ccln = collection;
    ConstRRsetPtr rrset = ccln.find(Name("www.example.org"), rrclass,
                                    RRType::A());
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRTTL(3600), rrset->getTTL());
    EXPECT_EQ(RRClass("IN"), rrset->getClass());
    EXPECT_EQ(Name("www.example.org"), rrset->getName());

    // foo.example.org doesn't exist
    rrset = ccln.find(Name("foo.example.org"), rrclass, RRType::A());
    EXPECT_FALSE(rrset);

    // www.example.org exists, but not with MX
    rrset = ccln.find(Name("www.example.org"), rrclass, RRType::MX());
    EXPECT_FALSE(rrset);

    // www.example.org exists, with AAAA
    rrset = ccln.find(Name("www.example.org"), rrclass, RRType::AAAA());
    EXPECT_TRUE(rrset);

    // www.example.org with AAAA does not exist in RRClass::CH()
    rrset = ccln.find(Name("www.example.org"), RRClass::CH(),
                            RRType::AAAA());
    EXPECT_FALSE(rrset);
}

} // namespace
