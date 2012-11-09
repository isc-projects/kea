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

#include <testutils/dnsmessage_test.h>

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>

#include <datasrc/memory/rdataset.h>
#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/zone_data_updater.h>

#include "memory_segment_test.h"

#include <gtest/gtest.h>

using isc::testutils::textToRRset;
using namespace isc::dns;
using namespace isc::datasrc::memory;

namespace {

class ZoneDataUpdaterTest : public ::testing::Test {
protected:
    ZoneDataUpdaterTest() :
        zname_("example.org"), zclass_(RRClass::IN()),
        zone_data_(ZoneData::create(mem_sgmt_, zname_)),
        updater_(mem_sgmt_, zclass_, zname_, *zone_data_)
    {}
    ~ZoneDataUpdaterTest() {
        // Make sure zone data is destroyed even if a test results in exception
        if (zone_data_ != NULL) {
            ZoneData::destroy(mem_sgmt_, zone_data_, zclass_);
        }
    }

    void TearDown() {
        if (zone_data_ != NULL) {
            ZoneData::destroy(mem_sgmt_, zone_data_, zclass_);
            zone_data_ = NULL;
        }
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated()); // catch any leak here.
    }
    const Name zname_;
    const RRClass zclass_;
    test::MemorySegmentTest mem_sgmt_;
    ZoneData* zone_data_;
    ZoneDataUpdater updater_;
};

TEST_F(ZoneDataUpdaterTest, bothNull) {
    // At least either covered RRset or RRSIG must be non NULL.
    EXPECT_THROW(updater_.add(ConstRRsetPtr(), ConstRRsetPtr()),
                 ZoneDataUpdater::NullRRset);
}

ZoneNode*
getNode(isc::util::MemorySegment& mem_sgmt, const Name& name,
        ZoneData* zone_data)
{
    ZoneNode* node = NULL;
    zone_data->insertName(mem_sgmt, name, &node);
    EXPECT_NE(static_cast<ZoneNode*>(NULL), node);
    return (node);
}

TEST_F(ZoneDataUpdaterTest, rrisgOnly) {
    // RRSIG that doesn't have covered RRset can be added.  The resulting
    // rdataset won't have "normal" RDATA but sig RDATA.
    updater_.add(ConstRRsetPtr(), textToRRset(
                     "www.example.org. 3600 IN RRSIG A 5 3 3600 20150420235959"
                     " 20051021000000 1 example.org. FAKE"));
    ZoneNode* node = getNode(mem_sgmt_, Name("www.example.org"), zone_data_);
    const RdataSet* rdset = node->getData();
    ASSERT_NE(static_cast<RdataSet*>(NULL), rdset);
    rdset = RdataSet::find(rdset, RRType::A());
    ASSERT_NE(static_cast<RdataSet*>(NULL), rdset);
    EXPECT_EQ(0, rdset->getRdataCount());
    EXPECT_EQ(1, rdset->getSigRdataCount());

    // The RRSIG covering A prohibits an actual A RRset from being added.
    // This should be loosened in future version, but we check the current
    // behavior.
    EXPECT_THROW(updater_.add(
                     textToRRset("www.example.org. 3600 IN A 192.0.2.1"),
                     ConstRRsetPtr()), ZoneDataUpdater::AddError);

    // The special "wildcarding" node mark should be added for the RRSIG-only
    // case, too.
    updater_.add(ConstRRsetPtr(), textToRRset(
                     "*.wild.example.org. 3600 IN RRSIG A 5 3 3600 "
                     "20150420235959 20051021000000 1 example.org. FAKE"));
    node = getNode(mem_sgmt_, Name("wild.example.org"), zone_data_);
    EXPECT_TRUE(node->getFlag(ZoneData::WILDCARD_NODE));

    // Simply adding RRSIG covering (delegating NS) shouldn't enable callback
    // in search.
    updater_.add(ConstRRsetPtr(), textToRRset(
                     "child.example.org. 3600 IN RRSIG NS 5 3 3600 "
                     "20150420235959 20051021000000 1 example.org. FAKE"));
    node = getNode(mem_sgmt_, Name("child.example.org"), zone_data_);
    EXPECT_FALSE(node->getFlag(ZoneNode::FLAG_CALLBACK));

    // Same for DNAME
    updater_.add(ConstRRsetPtr(), textToRRset(
                     "dname.example.org. 3600 IN RRSIG DNAME 5 3 3600 "
                     "20150420235959 20051021000000 1 example.org. FAKE"));
    node = getNode(mem_sgmt_, Name("dname.example.org"), zone_data_);
    EXPECT_FALSE(node->getFlag(ZoneNode::FLAG_CALLBACK));

    // Likewise, RRSIG for NSEC3PARAM alone shouldn't make the zone
    // "NSEC3-signed".
    updater_.add(ConstRRsetPtr(), textToRRset(
                     "example.org. 3600 IN RRSIG NSEC3PARAM 5 3 3600 "
                     "20150420235959 20051021000000 1 example.org. FAKE"));
    EXPECT_FALSE(zone_data_->isNSEC3Signed());

    // And same for (RRSIG for) NSEC and "is signed".
    updater_.add(ConstRRsetPtr(), textToRRset(
                     "example.org. 3600 IN RRSIG NSEC 5 3 3600 "
                     "20150420235959 20051021000000 1 example.org. FAKE"));
    EXPECT_FALSE(zone_data_->isSigned());
}

}
