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
#include <string>

using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc::memory;
using namespace isc::datasrc::memory::test;
using namespace isc::testutils;

namespace {

// With this single fixture we'll test both NSEC3Data and ZoneData
class ZoneDataTest : public ::testing::Test {
protected:
    ZoneDataTest() :
        nsec3_data_(NULL), param_rdata_("1 0 12 aabbccdd"),
        param_rdata_nosalt_("1 1 10 -"),
        param_rdata_largesalt_("2 0 5 " + std::string(255 * 2, 'a')),
        nsec3_rdata_("1 0 12 aabbccdd TDK23RP6 SOA"),
        nsec3_rdata_nosalt_("1 1 10 - TDK23RP6 SOA"),
        nsec3_rdata_largesalt_("2 0 5 " + std::string(255 * 2, 'a') +
                               " TDK23RP6 SOA"),
        zname_("example.com"),
        zone_data_(ZoneData::create(mem_sgmt_, zname_)),
        a_rrset_(textToRRset("www.example.com. 3600 IN A 192.0.2.1")),
        aaaa_rrset_(textToRRset("www.example.com. 3600 IN AAAA 2001:db8::1")),
        nsec3_rrset_(textToRRset("TDK23RP6.example.com. 3600 IN NSEC3 "
                                 "1 0 12 aabbccdd TDK23RP6 SOA"))
    {}
    void TearDown() {
        if (nsec3_data_ != NULL) {
            NSEC3Data::destroy(mem_sgmt_, nsec3_data_, RRClass::IN());
        }
        if (zone_data_ != NULL) {
            ZoneData::destroy(mem_sgmt_, RRClass::IN(), zone_data_);
        }
        // detect any memory leak in the test memory segment
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated());
    }

    MemorySegmentTest mem_sgmt_;
    NSEC3Data* nsec3_data_;
    const generic::NSEC3PARAM param_rdata_, param_rdata_nosalt_,
        param_rdata_largesalt_;
    const generic::NSEC3 nsec3_rdata_, nsec3_rdata_nosalt_,
        nsec3_rdata_largesalt_;
    const Name zname_;
    ZoneData* zone_data_;
    const ConstRRsetPtr a_rrset_, aaaa_rrset_, nsec3_rrset_;
    RdataEncoder encoder_;
};

// Shared by both test cases using NSEC3 and NSEC3PARAM Rdata
template <typename RdataType>
void
checkNSEC3Data(MemorySegmentTest& mem_sgmt, const RdataType& expect_rdata) {
    NSEC3Data* nsec3_data = NSEC3Data::create(mem_sgmt, expect_rdata);

    // Internal tree should be created and empty.
    EXPECT_EQ(0, nsec3_data->getNSEC3Tree()->getNodeCount());

    EXPECT_EQ(expect_rdata.getHashalg(), nsec3_data->hashalg);
    EXPECT_EQ(expect_rdata.getFlags(), nsec3_data->flags);
    EXPECT_EQ(expect_rdata.getIterations(), nsec3_data->iterations);
    EXPECT_EQ(expect_rdata.getSalt().size(), nsec3_data->getSaltLen());
    if (expect_rdata.getSalt().size() > 0) {
        EXPECT_EQ(0, memcmp(&expect_rdata.getSalt()[0],
                            nsec3_data->getSaltData(),
                            expect_rdata.getSalt().size()));
    }

    NSEC3Data::destroy(mem_sgmt, nsec3_data, RRClass::IN());
}

void
checkFindRdataSet(const ZoneTree* tree, const Name& name, RRType type,
                  const RdataSet* expected_set)
{
    ZoneNode* node = NULL;
    tree->find(name, &node);
    ASSERT_NE(static_cast<ZoneNode*>(NULL), node);
    EXPECT_EQ(expected_set, findRdataSetOfType(node->getData(), type));
}

TEST_F(ZoneDataTest, createNSEC3Data) {
    // Create an NSEC3Data object from various types of RDATA (of NSEC3PARAM
    // and of NSEC3), check if the resulting parameters match.
    checkNSEC3Data(mem_sgmt_, param_rdata_); // one 'usual' form of params
    checkNSEC3Data(mem_sgmt_, param_rdata_nosalt_); // empty salt
    checkNSEC3Data(mem_sgmt_, param_rdata_largesalt_); // max-len salt

    // Same concepts of the tests, using NSEC3 RDATA.
    checkNSEC3Data(mem_sgmt_, nsec3_rdata_);
    checkNSEC3Data(mem_sgmt_, nsec3_rdata_nosalt_);
    checkNSEC3Data(mem_sgmt_, nsec3_rdata_largesalt_);
}

TEST_F(ZoneDataTest, addNSEC3) {
    nsec3_data_ = NSEC3Data::create(mem_sgmt_, param_rdata_);

    ZoneNode* node = NULL;
    nsec3_data_->insertName(mem_sgmt_, nsec3_rrset_->getName(), &node);
    ASSERT_NE(static_cast<ZoneNode*>(NULL), node);
    EXPECT_TRUE(node->isEmpty()); // initially it should be empty

    RdataSet* rdataset_nsec3 =
        RdataSet::create(mem_sgmt_, encoder_, nsec3_rrset_, ConstRRsetPtr());
    node->setData(rdataset_nsec3);

    // Confirm we can find the added ones from the zone data.
    checkFindRdataSet(nsec3_data_->getNSEC3Tree(), nsec3_rrset_->getName(),
                      RRType::NSEC3(), rdataset_nsec3);

    // TearDown() will confirm there's no leak on destroy
}

TEST_F(ZoneDataTest, getOriginNode) {
    EXPECT_EQ(LabelSequence(zname_), zone_data_->getOriginNode()->getLabels());
}

TEST_F(ZoneDataTest, throwOnCreate) {
    // Note: below, we use our knowledge of how memory allocation happens
    // within the NSEC3Data, the zone data and the underlying domain tree
    // implementation.

    // Creating internal NSEC3 tree will succeed, but allocation of NSEC3Data
    // will fail due to bad_alloc.  It shouldn't cause memory leak
    // (that would be caught in TearDown()).
    mem_sgmt_.setThrowCount(2);
    EXPECT_THROW(NSEC3Data::create(mem_sgmt_, param_rdata_), std::bad_alloc);

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

    ZoneNode* node = NULL;
    zone_data_->insertName(mem_sgmt_, a_rrset_->getName(), &node);
    ASSERT_NE(static_cast<ZoneNode*>(NULL), node);
    EXPECT_TRUE(node->isEmpty()); // initially it should be empty

    RdataSet* rdataset_a =
        RdataSet::create(mem_sgmt_, encoder_, a_rrset_, ConstRRsetPtr());
    node->setData(rdataset_a);

    RdataSet* rdataset_aaaa =
        RdataSet::create(mem_sgmt_, encoder_, aaaa_rrset_, ConstRRsetPtr());
    // make a linked list and replace the list head
    rdataset_aaaa->next = rdataset_a;
    node->setData(rdataset_aaaa);

    // Confirm we can find the added ones from the zone data.
    checkFindRdataSet(zone_data_->getZoneTree(), a_rrset_->getName(),
                      RRType::A(), rdataset_a);
    checkFindRdataSet(zone_data_->getZoneTree(), a_rrset_->getName(),
                      RRType::AAAA(), rdataset_aaaa);
    // There's no NS (or anything other than AAAA or A) RdataSet in the list
    checkFindRdataSet(zone_data_->getZoneTree(), a_rrset_->getName(),
                      RRType::NS(), NULL);

    // TearDown() will confirm there's no leak on destroy
}

TEST_F(ZoneDataTest, getSetNSEC3Data) {
    // Initially there's no NSEC3 data
    EXPECT_EQ(static_cast<NSEC3Data*>(NULL), zone_data_->getNSEC3Data());

    // Set a new one.  The set method should return NULL.  The get method
    // should return the new one.
    NSEC3Data* nsec3_data = NSEC3Data::create(mem_sgmt_, param_rdata_);
    NSEC3Data* old_nsec3_data = zone_data_->setNSEC3Data(nsec3_data);
    EXPECT_EQ(static_cast<NSEC3Data*>(NULL), old_nsec3_data);
    EXPECT_EQ(nsec3_data, zone_data_->getNSEC3Data());

    // Replace an existing one with a yet another one.
    // We're responsible for destroying the old one.
    NSEC3Data* nsec3_data2 = NSEC3Data::create(mem_sgmt_, nsec3_rdata_);
    old_nsec3_data = zone_data_->setNSEC3Data(nsec3_data2);
    EXPECT_EQ(nsec3_data, old_nsec3_data);
    EXPECT_EQ(nsec3_data2, zone_data_->getNSEC3Data());
    NSEC3Data::destroy(mem_sgmt_, old_nsec3_data, RRClass::IN());

    // Setting NULL clears any existing one.
    old_nsec3_data = zone_data_->setNSEC3Data(NULL);
    EXPECT_EQ(nsec3_data2, old_nsec3_data);
    EXPECT_EQ(static_cast<NSEC3Data*>(NULL), zone_data_->getNSEC3Data());

    // Then set it again.  The zone data should destroy it on its own
    // destruction.
    zone_data_->setNSEC3Data(old_nsec3_data);
}
}
