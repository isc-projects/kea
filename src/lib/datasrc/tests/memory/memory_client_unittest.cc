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

#include <datasrc/tests/memory/zone_loader_util.h>

#include <exceptions/exceptions.h>

#include <util/memory_segment_local.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/masterload.h>
#include <dns/nsec3hash.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrttl.h>
#include <dns/masterload.h>

#include <datasrc/result.h>
#include <datasrc/exceptions.h>
#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/zone_table.h>
#include <datasrc/memory/zone_data_updater.h>
#include <datasrc/memory/zone_data_loader.h>
#include <datasrc/memory/memory_client.h>

#include <testutils/dnsmessage_test.h>

#include "memory_segment_test.h"
#include "zone_table_segment_test.h"

#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include <new>                  // for bad_alloc

using namespace isc::data;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc;
using namespace isc::datasrc::memory;
using namespace isc::testutils;
using boost::shared_ptr;
using std::vector;
using isc::datasrc::memory::test::loadZoneIntoTable;

namespace {

const char* rrset_data[] = {
    "example.org. 3600 IN SOA ns1.example.org. bugs.x.w.example.org. "
    "68 3600 300 3600000 3600",
    "example.org. 3600 IN NS ns1.example.org.",
    "a.example.org. 3600 IN A 192.168.0.1\n" // RRset containing 2 RRs
    "a.example.org. 3600 IN A 192.168.0.2",
    "a.example.org. 3600 IN RRSIG A 5 3 3600 20150420235959 20051021000000 "
    "40430 example.org. FAKEFAKE",
    "a.example.org. 3600 IN MX 10 mail.example.org.",
    "a.example.org. 3600 IN RRSIG MX 5 3 3600 20150420235959 20051021000000 "
    "40430 example.org. FAKEFAKEFAKE",
    NULL
};

// RRsets that emulate the "separate RRs" mode.
const char* rrset_data_separated[] = {
    "example.org. 3600 IN SOA ns1.example.org. bugs.x.w.example.org. "
    "68 3600 300 3600000 3600",
    "example.org. 3600 IN NS ns1.example.org.",
    "a.example.org. 3600 IN A 192.168.0.1", // these two belong to the same
    "a.example.org. 3600 IN A 192.168.0.2", // RRset, but are separated.
    NULL
};

// Similar to the previous one, but with separated RRSIGs
const char* rrset_data_sigseparated[] = {
    "example.org. 3600 IN SOA ns1.example.org. bugs.x.w.example.org. "
    "68 3600 300 3600000 3600",
    "example.org. 3600 IN NS ns1.example.org.",
    "a.example.org. 3600 IN A 192.168.0.1",
    "a.example.org. 3600 IN RRSIG A 5 3 3600 20150420235959 20051021000000 "
    "40430 example.org. FAKEFAKE",
    "a.example.org. 3600 IN RRSIG A 5 3 3600 20150420235959 20051021000000 "
    "53535 example.org. FAKEFAKE",
    NULL
};

class MockIterator : public ZoneIterator {
private:
    MockIterator(const char** rrset_data_ptr, bool pass_empty_rrsig) :
        rrset_data_ptr_(rrset_data_ptr),
        pass_empty_rrsig_(pass_empty_rrsig)
    {}

    const char** rrset_data_ptr_;
    // If true, emulate an unexpected bogus case where an RRSIG RRset is
    // returned without the RDATA.  For brevity allow tests tweak it directly.
    bool pass_empty_rrsig_;

public:
    virtual ConstRRsetPtr getNextRRset() {
        if (*rrset_data_ptr_ == NULL) {
             return (ConstRRsetPtr());
        }

        ConstRRsetPtr result(textToRRset(*rrset_data_ptr_,
                                         RRClass::IN(), Name("example.org")));
        if (pass_empty_rrsig_ && result->getType() == RRType::RRSIG()) {
            result.reset(new RRset(result->getName(), result->getClass(),
                                   result->getType(), result->getTTL()));
        }
        ++rrset_data_ptr_;

        return (result);
    }

    virtual ConstRRsetPtr getSOA() const {
        isc_throw(isc::NotImplemented, "Not implemented");
    }

    static ZoneIteratorPtr makeIterator(const char** rrset_data_ptr,
                                        bool pass_empty_rrsig = false)
    {
        return (ZoneIteratorPtr(new MockIterator(rrset_data_ptr,
                                                 pass_empty_rrsig)));
    }
};

class MockVectorIterator : public ZoneIterator {
private:
    MockVectorIterator(const vector<ConstRRsetPtr>& rrsets) :
        rrsets_(rrsets),
        counter_(0)
    {}

    const vector<ConstRRsetPtr> rrsets_;
    int counter_;

public:
    virtual ConstRRsetPtr getNextRRset() {
        if (counter_ >= rrsets_.size()) {
             return (ConstRRsetPtr());
        }

        return (rrsets_[counter_++]);
    }

    virtual ConstRRsetPtr getSOA() const {
        isc_throw(isc::NotImplemented, "Not implemented");
    }

    static ZoneIteratorPtr makeIterator(const vector<ConstRRsetPtr>& rrsets) {
        return (ZoneIteratorPtr(new MockVectorIterator(rrsets)));
    }
};

class MemoryClientTest : public ::testing::Test {
protected:
    MemoryClientTest() : zclass_(RRClass::IN()),
                         ztable_segment_(new test::ZoneTableSegmentTest(
                             zclass_, mem_sgmt_)),
                         client_(new InMemoryClient(ztable_segment_, zclass_))
    {}
    void TearDown() {
        client_.reset();
        ztable_segment_.reset();
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated()); // catch any leak here.
    }
    const RRClass zclass_;
    test::MemorySegmentTest mem_sgmt_;
    shared_ptr<ZoneTableSegment> ztable_segment_;
    boost::scoped_ptr<InMemoryClient> client_;
};

TEST_F(MemoryClientTest, loadRRsetDoesntMatchOrigin) {
    // Attempting to load example.org to example.com zone should result
    // in an exception.
    EXPECT_THROW(loadZoneData(mem_sgmt_, zclass_, Name("example.com"),
                              TEST_DATA_DIR "/example.org-empty.zone"),
                 ZoneLoaderException);
}

TEST_F(MemoryClientTest, loadErrorsInParsingZoneMustNotLeak1) {
    // Attempting to load broken example.org zone should result in an
    // exception. This should not leak ZoneData and other such
    // allocations.
    EXPECT_THROW(loadZoneData(mem_sgmt_, zclass_, Name("example.org"),
                              TEST_DATA_DIR "/example.org-broken1.zone"),
                 ZoneLoaderException);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadErrorsInParsingZoneMustNotLeak2) {
    // Attempting to load broken example.org zone should result in an
    // exception. This should not leak ZoneData and other such
    // allocations.
    EXPECT_THROW(loadZoneData(mem_sgmt_, zclass_, Name("example.org"),
                              TEST_DATA_DIR "/example.org-broken2.zone"),
                 ZoneLoaderException);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadNonExistentZoneFile) {
    EXPECT_THROW(loadZoneData(mem_sgmt_, zclass_, Name("example.org"),
                              TEST_DATA_DIR "/somerandomfilename"),
                 ZoneLoaderException);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadEmptyZoneFileThrows) {
    // When an empty zone file is loaded, the origin doesn't even have
    // an SOA RR. This condition should be avoided, and hence it results in
    // an exception.
    EXPECT_THROW(loadZoneData(mem_sgmt_, zclass_, Name("."),
                              TEST_DATA_DIR "/empty.zone"),
                 ZoneValidationError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, load) {
    // This is a simple load check for a "full" and correct zone that
    // should not result in any exceptions.
    ZoneData* zone_data = loadZoneData(mem_sgmt_, zclass_,
                                       Name("example.org"),
                                       TEST_DATA_DIR
                                       "/example.org.zone");
    ASSERT_NE(static_cast<const ZoneData*>(NULL), zone_data);
    EXPECT_FALSE(zone_data->isSigned());
    EXPECT_FALSE(zone_data->isNSEC3Signed());
    ZoneData::destroy(mem_sgmt_, zone_data, zclass_);
}

TEST_F(MemoryClientTest, loadFromIterator) {
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      *MockIterator::makeIterator(rrset_data));

    ZoneIteratorPtr iterator(client_->getIterator(Name("example.org")));

    // First we have the SOA
    ConstRRsetPtr rrset(iterator->getNextRRset());
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::SOA(), rrset->getType());

    // RRType::NS() RRset
    rrset = iterator->getNextRRset();
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::NS(), rrset->getType());

    // RRType::A() RRset
    rrset = iterator->getNextRRset();
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::MX(), rrset->getType());
    EXPECT_EQ(1, rrset->getRRsigDataCount()); // this RRset is signed

    // RRType::MX() RRset
    rrset = iterator->getNextRRset();
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(1, rrset->getRRsigDataCount()); // also signed

    // There's nothing else in this iterator
    EXPECT_EQ(ConstRRsetPtr(), iterator->getNextRRset());

    // Iterating past the end should result in an exception
    EXPECT_THROW(iterator->getNextRRset(), isc::Unexpected);

    // NOTE: The rest of the tests is not actually about InMemoryClient

    // Loading the zone with an iterator separating RRs of the same
    // RRset should not fail. It is acceptable to load RRs of the same
    // type again.
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      *MockIterator::makeIterator(rrset_data_separated));

    // Similar to the previous case, but with separated RRSIGs.
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      *MockIterator::makeIterator(rrset_data_sigseparated));

    // Emulating bogus iterator implementation that passes empty RRSIGs.
    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   *MockIterator::makeIterator(rrset_data,
                                                               true)),
                 isc::Unexpected);
}

TEST_F(MemoryClientTest, loadMemoryAllocationFailures) {
    // Just to check that things get cleaned up

    for (int i = 1; i < 16; i++) {
        SCOPED_TRACE("For throw count = " +
                     boost::lexical_cast<std::string>(i));
        mem_sgmt_.setThrowCount(i);
        EXPECT_THROW({
            shared_ptr<ZoneTableSegment> ztable_segment(
                new test::ZoneTableSegmentTest(
                    zclass_, mem_sgmt_));

            // Include the InMemoryClient construction too here. Now,
            // even allocations done from InMemoryClient constructor
            // fail (due to MemorySegmentTest throwing) and we check for
            // leaks when this happens.
            InMemoryClient client2(ztable_segment, zclass_);
            loadZoneIntoTable(*ztable_segment, Name("example.org"), zclass_,
                              TEST_DATA_DIR "/example.org.zone");
        }, std::bad_alloc);
    }
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadNSEC3Signed) {
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-nsec3-signed.zone");
    const ZoneData* zone_data =
        client_->findZoneData(Name("example.org"));
    ASSERT_NE(static_cast<const ZoneData*>(NULL), zone_data);
    EXPECT_TRUE(zone_data->isSigned());
    EXPECT_TRUE(zone_data->isNSEC3Signed());
}

TEST_F(MemoryClientTest, loadNSEC3EmptySalt) {
    // Load NSEC3 with empty ("-") salt. This should not throw or crash
    // or anything.
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-nsec3-empty-salt.zone");
    const ZoneData* zone_data =
        client_->findZoneData(Name("example.org"));
    ASSERT_NE(static_cast<const ZoneData*>(NULL), zone_data);
    EXPECT_TRUE(zone_data->isSigned());
    EXPECT_TRUE(zone_data->isNSEC3Signed());
}

TEST_F(MemoryClientTest, loadNSEC3SignedNoParam) {
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-nsec3-signed-no-param.zone");
    const ZoneData* zone_data =
        client_->findZoneData(Name("example.org"));
    ASSERT_NE(static_cast<const ZoneData*>(NULL), zone_data);
    EXPECT_TRUE(zone_data->isSigned());
    EXPECT_TRUE(zone_data->isNSEC3Signed());
}

TEST_F(MemoryClientTest, loadReloadZone) {
    // Because we reload the same zone, also check that the zone count
    // doesn't increase.
    EXPECT_EQ(0, client_->getZoneCount());

    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-empty.zone");
    EXPECT_EQ(1, client_->getZoneCount());

    // Reload zone with same data

    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-empty.zone");
    EXPECT_EQ(1, client_->getZoneCount());

    const ZoneData* zone_data =
        client_->findZoneData(Name("example.org"));
    EXPECT_NE(static_cast<const ZoneData*>(NULL), zone_data);

    /* Check SOA */
    const ZoneNode* node = zone_data->getOriginNode();
    EXPECT_NE(static_cast<const ZoneNode*>(NULL), node);

    const RdataSet* set = node->getData();
    EXPECT_NE(static_cast<const RdataSet*>(NULL), set);
    EXPECT_EQ(RRType::SOA(), set->type);

    set = set->getNext();
    EXPECT_NE(static_cast<const RdataSet*>(NULL), set);
    EXPECT_EQ(RRType::NS(), set->type);

    set = set->getNext();
    EXPECT_EQ(static_cast<const RdataSet*>(NULL), set);

    /* Check ns1.example.org */
    const ZoneTree& tree = zone_data->getZoneTree();
    ZoneTree::Result zresult(tree.find(Name("ns1.example.org"), &node));
    EXPECT_NE(ZoneTree::EXACTMATCH, zresult);

    // Reload zone with different data

    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-rrsigs.zone");
    EXPECT_EQ(1, client_->getZoneCount());

    zone_data = client_->findZoneData(Name("example.org"));
    EXPECT_NE(static_cast<const ZoneData*>(NULL), zone_data);

    /* Check SOA */
    node = zone_data->getOriginNode();
    EXPECT_NE(static_cast<const ZoneNode*>(NULL), node);

    set = node->getData();
    EXPECT_NE(static_cast<const RdataSet*>(NULL), set);
    EXPECT_EQ(RRType::SOA(), set->type);

    set = set->getNext();
    EXPECT_NE(static_cast<const RdataSet*>(NULL), set);
    EXPECT_EQ(RRType::NS(), set->type);

    set = set->getNext();
    EXPECT_EQ(static_cast<const RdataSet*>(NULL), set);

    /* Check ns1.example.org */
    const ZoneTree& tree2 = zone_data->getZoneTree();
    ZoneTree::Result zresult2(tree2.find(Name("ns1.example.org"), &node));
    EXPECT_EQ(ZoneTree::EXACTMATCH, zresult2);
    EXPECT_NE(static_cast<const ZoneNode*>(NULL), node);

    set = node->getData();
    EXPECT_NE(static_cast<const RdataSet*>(NULL), set);
    EXPECT_EQ(RRType::AAAA(), set->type);

    set = set->getNext();
    EXPECT_NE(static_cast<const RdataSet*>(NULL), set);
    EXPECT_EQ(RRType::A(), set->type);

    set = set->getNext();
    EXPECT_EQ(static_cast<const RdataSet*>(NULL), set);

    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadDuplicateType) {
    // This should not result in any exceptions (multiple records of the
    // same name, type are present, one after another in sequence).
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-duplicate-type.zone");

    // This should not result in any exceptions (multiple records of the
    // same name, type are present, but not one after another in
    // sequence).
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-duplicate-type-bad.zone");

    const ZoneData* zone_data =
        client_->findZoneData(Name("example.org"));
    EXPECT_NE(static_cast<const ZoneData*>(NULL), zone_data);

    /* Check ns1.example.org */
    const ZoneTree& tree = zone_data->getZoneTree();
    const ZoneNode* node;
    ZoneTree::Result zresult(tree.find(Name("ns1.example.org"), &node));
    EXPECT_EQ(ZoneTree::EXACTMATCH, zresult);

    const RdataSet* set = node->getData();
    EXPECT_NE(static_cast<const RdataSet*>(NULL), set);
    EXPECT_EQ(RRType::AAAA(), set->type);

    set = set->getNext();
    EXPECT_NE(static_cast<const RdataSet*>(NULL), set);
    EXPECT_EQ(RRType::A(), set->type);
    // 192.168.0.1 and 192.168.0.2
    EXPECT_EQ(2, set->getRdataCount());

    set = set->getNext();
    EXPECT_EQ(static_cast<const RdataSet*>(NULL), set);

    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadMultipleCNAMEThrows) {
    // Multiple CNAME RRs should throw.
    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   TEST_DATA_DIR
                                   "/example.org-multiple-cname.zone"),
                 ZoneDataUpdater::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadMultipleDNAMEThrows) {
    // Multiple DNAME RRs should throw.
    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   TEST_DATA_DIR
                                   "/example.org-multiple-dname.zone"),
                 ZoneDataUpdater::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadMultipleNSEC3Throws) {
    // Multiple NSEC3 RRs should throw.
    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   TEST_DATA_DIR
                                   "/example.org-multiple-nsec3.zone"),
                 ZoneDataUpdater::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadMultipleNSEC3PARAMThrows) {
    // Multiple NSEC3PARAM RRs should throw.
    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   TEST_DATA_DIR
                                   "/example.org-multiple-nsec3param.zone"),
                 ZoneDataUpdater::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadOutOfZoneThrows) {
    // Out of zone names should throw.
    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   TEST_DATA_DIR
                                   "/example.org-out-of-zone.zone"),
                 ZoneLoaderException);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadWildcardNSThrows) {
    // Wildcard NS names should throw
    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   TEST_DATA_DIR
                                   "/example.org-wildcard-ns.zone"),
                 ZoneDataUpdater::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadWildcardDNAMEThrows) {
    // Wildcard DNAME names should throw
    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   TEST_DATA_DIR
                                   "/example.org-wildcard-dname.zone"),
                 ZoneDataUpdater::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadWildcardNSEC3Throws) {
    // Wildcard NSEC3 names should throw
    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   TEST_DATA_DIR
                                   "/example.org-wildcard-nsec3.zone"),
                 ZoneDataUpdater::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadNSEC3WithFewerLabelsThrows) {
    // NSEC3 names with labels != (origin_labels + 1) should throw
    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   TEST_DATA_DIR
                                   "/example.org-nsec3-fewer-labels.zone"),
                 ZoneDataUpdater::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadNSEC3WithMoreLabelsThrows) {
    // NSEC3 names with labels != (origin_labels + 1) should throw
    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   TEST_DATA_DIR
                                   "/example.org-nsec3-more-labels.zone"),
                 ZoneDataUpdater::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadCNAMEAndNotNSECThrows) {
    // CNAME and not NSEC should throw
    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   TEST_DATA_DIR
                                   "/example.org-cname-and-not-nsec-1.zone"),
                 ZoneDataUpdater::AddError);

    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   TEST_DATA_DIR
                                   "/example.org-cname-and-not-nsec-2.zone"),
                 ZoneDataUpdater::AddError);

    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadDNAMEAndNSApex1) {
    // DNAME + NS (apex) is OK
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-dname-ns-apex-1.zone");
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadDNAMEAndNSApex2) {
    // DNAME + NS (apex) is OK (reverse order)
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-dname-ns-apex-2.zone");
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadDNAMEAndNSNonApex1) {
    // DNAME + NS (non-apex) must throw
    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   TEST_DATA_DIR
                                   "/example.org-dname-ns-nonapex-1.zone"),
                 ZoneDataUpdater::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadDNAMEAndNSNonApex2) {
    // DNAME + NS (non-apex) must throw (reverse order)
    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   TEST_DATA_DIR
                                   "/example.org-dname-ns-nonapex-2.zone"),
                 ZoneDataUpdater::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadRRSIGs) {
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-rrsigs.zone");
    EXPECT_EQ(1, client_->getZoneCount());
}

TEST_F(MemoryClientTest, loadRRSIGsRdataMixedCoveredTypes) {
    vector<ConstRRsetPtr> rrsets_vec;

    rrsets_vec.push_back(textToRRset("example.org. 3600 IN SOA "
                                     "ns1.example.org. bugs.x.w.example.org. "
                                     "2010012601 3600 300 3600000 1200",
                                     zclass_, Name("example.org")));
    RRsetPtr rrset(textToRRset("example.org. 3600 IN A 192.0.2.1\n"
                               "example.org. 3600 IN A 192.0.2.2\n"));
    RRsetPtr rrsig(textToRRset("example.org. 300 IN RRSIG "
                               "A 5 3 3600 20000101000000 20000201000000 "
                               "12345 example.org. FAKEFAKEFAKE"));
    // textToRRset (correctly) consider this RDATA belongs to a different
    // RRSIG, so we need to manually add it.
    rrsig->addRdata(generic::RRSIG("NS 5 3 3600 20000101000000 20000201000000 "
                                   "54321 example.org. FAKEFAKEFAKEFAKE"));
    rrset->addRRsig(rrsig);

    rrsets_vec.push_back(rrset);

    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   *MockVectorIterator::makeIterator(
                                       rrsets_vec)),
                 ZoneDataUpdater::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, getZoneCount) {
    EXPECT_EQ(0, client_->getZoneCount());
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-empty.zone");
    // We've updated the zone table already in the client, so the count
    // should also be incremented indirectly.
    EXPECT_EQ(1, client_->getZoneCount());
}

TEST_F(MemoryClientTest, getIteratorForNonExistentZone) {
    // Zone "." doesn't exist
    EXPECT_THROW(client_->getIterator(Name(".")), DataSourceError);
}

TEST_F(MemoryClientTest, getIterator) {
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-empty.zone");
    ZoneIteratorPtr iterator(client_->getIterator(Name("example.org")));

    // First we have the SOA
    ConstRRsetPtr rrset(iterator->getNextRRset());
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::SOA(), rrset->getType());

    // Then the NS
    rrset = iterator->getNextRRset();
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::NS(), rrset->getType());

    // There's nothing else in this iterator
    EXPECT_EQ(ConstRRsetPtr(), iterator->getNextRRset());

    // Iterating past the end should result in an exception
    EXPECT_THROW(iterator->getNextRRset(), isc::Unexpected);
}

TEST_F(MemoryClientTest, getIteratorSeparateRRs) {
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-multiple.zone");

    // separate_rrs = false
    ZoneIteratorPtr iterator(client_->getIterator(Name("example.org")));

    // First we have the SOA
    ConstRRsetPtr rrset(iterator->getNextRRset());
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::SOA(), rrset->getType());

    // Then, the NS
    rrset = iterator->getNextRRset();
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::NS(), rrset->getType());

    // Only one RRType::A() RRset
    rrset = iterator->getNextRRset();
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::A(), rrset->getType());

    // There's nothing else in this zone
    EXPECT_EQ(ConstRRsetPtr(), iterator->getNextRRset());

    // separate_rrs = true
    ZoneIteratorPtr iterator2(client_->getIterator(Name("example.org"), true));

    // First we have the SOA
    rrset = iterator2->getNextRRset();
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::SOA(), rrset->getType());

    // Then, the NS
    rrset = iterator2->getNextRRset();
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::NS(), rrset->getType());

    // First RRType::A() RRset
    rrset = iterator2->getNextRRset();
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::A(), rrset->getType());

    // Second RRType::A() RRset
    rrset = iterator2->getNextRRset();
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::A(), rrset->getType());

    // There's nothing else in this iterator
    EXPECT_EQ(ConstRRsetPtr(), iterator2->getNextRRset());
}

// Test we get RRSIGs and NSEC3s too for iterating with separate RRs
TEST_F(MemoryClientTest, getIteratorSeparateSigned) {
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-nsec3-signed.zone");
    ZoneIteratorPtr iterator(client_->getIterator(Name("example.org"), true));
    bool seen_rrsig = false, seen_nsec3 = false;
    for (ConstRRsetPtr rrset = iterator->getNextRRset();
         rrset != ConstRRsetPtr(); rrset = iterator->getNextRRset()) {
        if (rrset->getType() == RRType::RRSIG()) {
            seen_rrsig = true;
        } else if (rrset->getType() == RRType::NSEC3()) {
            seen_nsec3 = true;
        }
    }

    EXPECT_TRUE(seen_rrsig);
    EXPECT_TRUE(seen_nsec3);
}

TEST_F(MemoryClientTest, getIteratorGetSOAThrowsNotImplemented) {
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-empty.zone");
    ZoneIteratorPtr iterator(client_->getIterator(Name("example.org")));

    // This method is not implemented.
    EXPECT_THROW(iterator->getSOA(), isc::NotImplemented);
}

TEST_F(MemoryClientTest, addEmptyRRsetThrows) {
    vector<ConstRRsetPtr> rrsets_vec;
    rrsets_vec.push_back(textToRRset("example.org. 3600 IN SOA "
                                     "ns1.example.org. bugs.x.w.example.org. "
                                     "2010012601 3600 300 3600000 1200",
                                     zclass_, Name("example.org")));
    rrsets_vec.push_back(RRsetPtr(new RRset(Name("example.org"), zclass_,
                                            RRType::A(), RRTTL(3600))));

    EXPECT_THROW(loadZoneIntoTable(*ztable_segment_, Name("example.org"),
                                   zclass_,
                                   *MockVectorIterator::makeIterator(
                                       rrsets_vec)),
                 ZoneDataUpdater::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, findZoneData) {
    loadZoneIntoTable(*ztable_segment_, Name("example.org"), zclass_,
                      TEST_DATA_DIR "/example.org-rrsigs.zone");

    const ZoneData* zone_data = client_->findZoneData(Name("example.com"));
    EXPECT_EQ(static_cast<const ZoneData*>(NULL), zone_data);

    zone_data = client_->findZoneData(Name("example.org"));
    EXPECT_NE(static_cast<const ZoneData*>(NULL), zone_data);

    /* Check SOA */
    const ZoneNode* node = zone_data->getOriginNode();
    EXPECT_NE(static_cast<const ZoneNode*>(NULL), node);

    const RdataSet* set = node->getData();
    EXPECT_NE(static_cast<const RdataSet*>(NULL), set);
    EXPECT_EQ(RRType::SOA(), set->type);

    /* Check NS */
    set = set->getNext();
    EXPECT_NE(static_cast<const RdataSet*>(NULL), set);
    EXPECT_EQ(RRType::NS(), set->type);

    set = set->getNext();
    EXPECT_EQ(static_cast<const RdataSet*>(NULL), set);

    /* Check ns1.example.org */
    const ZoneTree& tree = zone_data->getZoneTree();
    ZoneTree::Result result3(tree.find(Name("ns1.example.org"), &node));
    EXPECT_EQ(ZoneTree::EXACTMATCH, result3);
    EXPECT_NE(static_cast<const ZoneNode*>(NULL), node);

    set = node->getData();
    EXPECT_NE(static_cast<const RdataSet*>(NULL), set);
    EXPECT_EQ(RRType::AAAA(), set->type);

    set = set->getNext();
    EXPECT_NE(static_cast<const RdataSet*>(NULL), set);
    EXPECT_EQ(RRType::A(), set->type);

    set = set->getNext();
    EXPECT_EQ(static_cast<const RdataSet*>(NULL), set);
}

TEST_F(MemoryClientTest, getUpdaterThrowsNotImplemented) {
    // This method is not implemented.
    EXPECT_THROW(client_->getUpdater(Name("."), false, false),
                 isc::NotImplemented);
}

TEST_F(MemoryClientTest, getJournalReaderNotImplemented) {
    // This method is not implemented.
    EXPECT_THROW(client_->getJournalReader(Name("."), 0, 0),
                 isc::NotImplemented);
}

}
