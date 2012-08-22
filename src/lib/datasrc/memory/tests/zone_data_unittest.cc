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

#include "memory_segment_test.h"

#include <dns/rdataclass.h>

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <dns/labelsequence.h>
#include <dns/rrclass.h>

#include <datasrc/memory/rdata_encoder.h>
#include <datasrc/memory/rdataset.h>
#include <datasrc/memory/zone_data.h>

#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

#include <new>                  // for bad_alloc

using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc::memory;
using namespace isc::datasrc::memory::test;
using namespace isc::testutils;

namespace {

class ZoneDataTest : public ::testing::Test {
protected:
    ZoneDataTest() : zname_("example.com"),
                     zone_data_(ZoneData::create(mem_sgmt_, zname_))
    {}
    void TearDown() {
        if (zone_data_ != NULL) {
            ZoneData::destroy(mem_sgmt_, RRClass::IN(), zone_data_);
        }
        // detect any memory leak in the test memory segment
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated());
    }

    MemorySegmentTest mem_sgmt_;
    const Name zname_;
    ZoneData* zone_data_;
    RdataEncoder encoder_;
};

TEST_F(ZoneDataTest, getOriginNode) {
    EXPECT_EQ(LabelSequence(zname_), zone_data_->getOriginNode()->getLabels());
}

TEST_F(ZoneDataTest, throwOnCreate) {
    // Note: below, we use our knowledge of how memory allocation happens
    // within the zone data and the underlying domain tree implementation.

    // allocate() will throw on the insertion of the origin node.
    mem_sgmt_.setThrowCount(2);
    EXPECT_THROW(ZoneData::create(mem_sgmt_, zname_), std::bad_alloc);

    // allocate() will throw on creating the zone data.
    mem_sgmt_.setThrowCount(3);
    EXPECT_THROW(ZoneData::create(mem_sgmt_, zname_), std::bad_alloc);

    // These incomplete create() attempts shouldn't cause memory leak
    // (that would be caught in TearDown()).
}

TEST_F(ZoneDataTest, addRdataSets) {
    // Insert a name to the zone, and add a couple the data (RdataSet) objects
    // to the corresponding node.

    ConstRRsetPtr a_rrset_ =
        textToRRset("www.example.com. 3600 IN A 192.0.2.1");

    ZoneNode* node = NULL;
    zone_data_->insertName(mem_sgmt_, a_rrset_->getName(), &node);
    ASSERT_NE(static_cast<ZoneNode*>(NULL), node);
    EXPECT_TRUE(node->isEmpty()); // initially it should be empty

    RdataSet* rdataset_a =
        RdataSet::create(mem_sgmt_, encoder_, a_rrset_, ConstRRsetPtr());
    node->setData(rdataset_a);

    ConstRRsetPtr aaaa_rrset_ =
        textToRRset("www.example.com. 3600 IN AAAA 2001:db8::1");
    RdataSet* rdataset_aaaa =
        RdataSet::create(mem_sgmt_, encoder_, aaaa_rrset_, ConstRRsetPtr());
    // make a linked list and replace the list head
    rdataset_aaaa->next = rdataset_a;
    node->setData(rdataset_aaaa);

    // TearDown() will confirm there's no leak on destroy
}

class NSEC3DataTest : public ::testing::Test {
protected:
    NSEC3DataTest() : param_rdata_("1 0 12 aabbccdd")
    {}
    void TearDown() {
        // detect any memory leak in the test memory segment
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated());
    }

    MemorySegmentTest mem_sgmt_;
    NSEC3Data* nsec3_data_;
    const generic::NSEC3PARAM param_rdata_;
};

TEST_F(NSEC3DataTest, create) {
    nsec3_data_ = NSEC3Data::create(mem_sgmt_, param_rdata_);
    EXPECT_EQ(0, nsec3_data_->getNSEC3Tree()->getNodeCount());
    EXPECT_EQ(1, nsec3_data_->hashalg);
    EXPECT_EQ(0, nsec3_data_->flags);
    EXPECT_EQ(12, nsec3_data_->iterations);
    EXPECT_EQ(param_rdata_.getSalt().size(), nsec3_data_->getSaltLen());
    EXPECT_EQ(0, memcmp(&param_rdata_.getSalt()[0], nsec3_data_->getSaltData(),
                        param_rdata_.getSalt().size()));
    NSEC3Data::destroy(mem_sgmt_, nsec3_data_, RRClass::IN());
}
}
