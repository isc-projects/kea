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
#include <dns/masterload.h>
#include <dns/nsec3hash.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrsetlist.h>
#include <dns/rrttl.h>
#include <dns/masterload.h>

#include <datasrc/result.h>
#include <datasrc/data_source.h>
#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/zone_table.h>
#include <datasrc/memory/memory_client.h>

#include <gtest/gtest.h>

#include <new>                  // for bad_alloc

using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc;
using namespace isc::datasrc::memory;

namespace {
// Memory segment specified for tests.  It normally behaves like a "local"
// memory segment.  If "throw count" is set to non 0 via setThrowCount(),
// it continues the normal behavior up to the specified number of calls to
// allocate(), and throws an exception at the next call.
class TestMemorySegment : public isc::util::MemorySegmentLocal {
public:
    TestMemorySegment() : throw_count_(0) {}
    virtual void* allocate(size_t size) {
        if (throw_count_ > 0) {
            if (--throw_count_ == 0) {
                throw std::bad_alloc();
            }
        }
        return (isc::util::MemorySegmentLocal::allocate(size));
    }
    void setThrowCount(size_t count) { throw_count_ = count; }

private:
    size_t throw_count_;
};

class MemoryClientTest : public ::testing::Test {
protected:
    MemoryClientTest() : zclass_(RRClass::IN()),
                         client_(new InMemoryClient(zclass_))
    {}
    ~MemoryClientTest() {
        if (client_ != NULL) {
            delete client_;
        }
    }
    void TearDown() {
        delete client_;
        client_ = NULL;
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated()); // catch any leak here.
    }
    const RRClass zclass_;
    TestMemorySegment mem_sgmt_;
    InMemoryClient* client_;
    memory::ZoneTable* zone_table;
};

TEST_F(MemoryClientTest, loadRRsetDoesntMatchOrigin) {
    // Attempting to load example.org to example.com zone should result
    // in an exception.
    EXPECT_THROW(client_->load(Name("example.com"),
                               TEST_DATA_DIR "/example.org-empty.zone"),
                 MasterLoadError);
}

TEST_F(MemoryClientTest, loadErrorsInParsingZoneMustNotLeak1) {
    // Attempting to load broken example.org zone should result in an
    // exception. This should not leak ZoneData and other such
    // allocations.
    EXPECT_THROW(client_->load(Name("example.org"),
                               TEST_DATA_DIR "/example.org-broken1.zone"),
                 MasterLoadError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadErrorsInParsingZoneMustNotLeak2) {
    // Attempting to load broken example.org zone should result in an
    // exception. This should not leak ZoneData and other such
    // allocations.
    EXPECT_THROW(client_->load(Name("example.org"),
                               TEST_DATA_DIR "/example.org-broken2.zone"),
                 MasterLoadError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadNonExistentZoneFile) {
    EXPECT_THROW(client_->load(Name("example.org"),
                               TEST_DATA_DIR "/somerandomfilename"),
                 MasterLoadError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadEmptyZoneFileThrows) {
    // When an empty zone file is loaded, the origin doesn't even have
    // an SOA RR. This condition should be avoided, and hence load()
    // should throw when an empty zone is loaded.

    EXPECT_EQ(0, client_->getZoneCount());

    EXPECT_THROW(client_->load(Name("."),
                               TEST_DATA_DIR "/empty.zone"),
                 InMemoryClient::EmptyZone);

    EXPECT_EQ(0, client_->getZoneCount());

    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, load) {
    // This is a simple load check for a "full" and correct zone that
    // should not result in any exceptions.
    client_->load(Name("example.org"),
                  TEST_DATA_DIR "/example.org.zone");
}

TEST_F(MemoryClientTest, loadNSEC3Signed) {
    client_->load(Name("example.org"),
                  TEST_DATA_DIR "/example.org-nsec3-signed.zone");
}

TEST_F(MemoryClientTest, loadNSEC3SignedNoParam) {
    client_->load(Name("example.org"),
                  TEST_DATA_DIR "/example.org-nsec3-signed-no-param.zone");
}

TEST_F(MemoryClientTest, loadReloadZone) {
    // Because we reload the same zone, also check that the zone count
    // doesn't increase.
    EXPECT_EQ(0, client_->getZoneCount());

    client_->load(Name("example.org"),
                  TEST_DATA_DIR "/example.org-empty.zone");
    EXPECT_EQ(1, client_->getZoneCount());

    // Reload zone with same data

    client_->load(Name("example.org"),
                  client_->getFileName(Name("example.org")));
    EXPECT_EQ(1, client_->getZoneCount());

    isc::datasrc::memory::ZoneTable::FindResult
        result(client_->findZone2(Name("example.org")));
    EXPECT_EQ(result::SUCCESS, result.code);
    EXPECT_NE(static_cast<ZoneData*>(NULL),
              result.zone_data);

    /* Check SOA */
    const ZoneNode* node = result.zone_data->getOriginNode();
    EXPECT_NE(static_cast<const ZoneNode*>(NULL), node);

    const RdataSet* set = node->getData();
    EXPECT_NE(static_cast<const RdataSet*>(NULL), set);
    EXPECT_EQ(RRType::SOA(), set->type);

    set = set->getNext();
    EXPECT_EQ(static_cast<const RdataSet*>(NULL), set);

    /* Check ns1.example.org */
    const ZoneTree& tree = result.zone_data->getZoneTree();
    ZoneTree::Result zresult(tree.find(Name("ns1.example.org"), &node));
    EXPECT_NE(ZoneTree::EXACTMATCH, zresult);

    // Reload zone with different data

    client_->load(Name("example.org"),
                  TEST_DATA_DIR "/example.org-rrsigs.zone");
    EXPECT_EQ(1, client_->getZoneCount());

    isc::datasrc::memory::ZoneTable::FindResult
        result2(client_->findZone2(Name("example.org")));
    EXPECT_EQ(result::SUCCESS, result2.code);
    EXPECT_NE(static_cast<ZoneData*>(NULL),
              result2.zone_data);

    /* Check SOA */
    node = result2.zone_data->getOriginNode();
    EXPECT_NE(static_cast<const ZoneNode*>(NULL), node);

    set = node->getData();
    EXPECT_NE(static_cast<const RdataSet*>(NULL), set);
    EXPECT_EQ(RRType::SOA(), set->type);

    set = set->getNext();
    EXPECT_EQ(static_cast<const RdataSet*>(NULL), set);

    /* Check ns1.example.org */
    const ZoneTree& tree2 = result2.zone_data->getZoneTree();
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
    // This should not result in any exceptions:
    client_->load(Name("example.org"),
                  TEST_DATA_DIR "/example.org-duplicate-type.zone");

    // This should throw:
    EXPECT_THROW(client_->load(Name("example.org"),
                               TEST_DATA_DIR
                               "/example.org-duplicate-type-bad.zone"),
                 InMemoryClient::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadMultipleCNAMEThrows) {
    // Multiple CNAME RRs should throw.
    EXPECT_THROW(client_->load(Name("example.org"),
                               TEST_DATA_DIR
                               "/example.org-multiple-cname.zone"),
                 InMemoryClient::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadMultipleDNAMEThrows) {
    // Multiple DNAME RRs should throw.
    EXPECT_THROW(client_->load(Name("example.org"),
                               TEST_DATA_DIR
                               "/example.org-multiple-dname.zone"),
                 InMemoryClient::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadMultipleNSEC3Throws) {
    // Multiple NSEC3 RRs should throw.
    EXPECT_THROW(client_->load(Name("example.org"),
                               TEST_DATA_DIR
                               "/example.org-multiple-nsec3.zone"),
                 InMemoryClient::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadMultipleNSEC3PARAMThrows) {
    // Multiple NSEC3PARAM RRs should throw.
    EXPECT_THROW(client_->load(Name("example.org"),
                               TEST_DATA_DIR
                               "/example.org-multiple-nsec3param.zone"),
                 InMemoryClient::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadOutOfZoneThrows) {
    // Out of zone names should throw.
    EXPECT_THROW(client_->load(Name("example.org"),
                               TEST_DATA_DIR
                               "/example.org-out-of-zone.zone"),
                 MasterLoadError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadRRSIGFollowsNothing) {
    EXPECT_THROW(client_->load(Name("example.org"),
                               TEST_DATA_DIR
                               "/example.org-rrsig-follows-nothing.zone"),
                 InMemoryClient::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadRRSIGNameUnmatched) {
    EXPECT_THROW(client_->load(Name("example.org"),
                               TEST_DATA_DIR
                               "/example.org-rrsig-name-unmatched.zone"),
                 InMemoryClient::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadRRSIGTypeUnmatched) {
    EXPECT_THROW(client_->load(Name("example.org"),
                               TEST_DATA_DIR
                               "/example.org-rrsig-type-unmatched.zone"),
                 InMemoryClient::AddError);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, loadRRSIGs) {
    client_->load(Name("example.org"),
                  TEST_DATA_DIR "/example.org-rrsigs.zone");
    EXPECT_EQ(1, client_->getZoneCount());
}

TEST_F(MemoryClientTest, loadRRSIGsRdataMixedCoveredTypes) {
    client_->load(Name("example.org"),
                  TEST_DATA_DIR "/example.org-rrsigs.zone");

    RRsetPtr rrset(new RRset(Name("example.org"),
                             RRClass::IN(), RRType::A(), RRTTL(3600)));
    rrset->addRdata(in::A("192.0.2.1"));
    rrset->addRdata(in::A("192.0.2.2"));

    RRsetPtr rrsig(new RRset(Name("example.org"), zclass_,
                             RRType::RRSIG(), RRTTL(300)));
    rrsig->addRdata(generic::RRSIG("A 5 3 3600 20000101000000 20000201000000 "
                                   "12345 example.org. FAKEFAKEFAKE"));
    rrsig->addRdata(generic::RRSIG("NS 5 3 3600 20000101000000 20000201000000 "
                                   "54321 example.org. FAKEFAKEFAKEFAKE"));
    rrset->addRRsig(rrsig);

    EXPECT_THROW(client_->add(Name("example.org"), rrset),
                 InMemoryClient::AddError);

    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, getZoneCount) {
    EXPECT_EQ(0, client_->getZoneCount());
    client_->load(Name("example.org"), TEST_DATA_DIR "/example.org-empty.zone");
    EXPECT_EQ(1, client_->getZoneCount());
}

TEST_F(MemoryClientTest, getFileNameForNonExistentZone) {
    // Zone "example.org." doesn't exist
    EXPECT_TRUE(client_->getFileName(Name("example.org.")).empty());
}

TEST_F(MemoryClientTest, getFileName) {
    client_->load(Name("example.org"), TEST_DATA_DIR "/example.org-empty.zone");
    EXPECT_EQ(TEST_DATA_DIR "/example.org-empty.zone",
              client_->getFileName(Name("example.org")));
}

TEST_F(MemoryClientTest, getIteratorForNonExistentZone) {
    // Zone "." doesn't exist
    EXPECT_THROW(client_->getIterator(Name(".")), DataSourceError);
}

TEST_F(MemoryClientTest, getIterator) {
    client_->load(Name("example.org"), TEST_DATA_DIR "/example.org-empty.zone");
    ZoneIteratorPtr iterator(client_->getIterator(Name("example.org")));

    // First we have the SOA
    ConstRRsetPtr rrset_soa(iterator->getNextRRset());
    EXPECT_TRUE(rrset_soa);
    EXPECT_EQ(RRType::SOA(), rrset_soa->getType());

    // There's nothing else in this zone
    EXPECT_EQ(ConstRRsetPtr(), iterator->getNextRRset());

    // Iterating past the end should result in an exception
    EXPECT_THROW(iterator->getNextRRset(), isc::Unexpected);
}

TEST_F(MemoryClientTest, getIteratorGetSOAThrowsNotImplemented) {
    client_->load(Name("example.org"), TEST_DATA_DIR "/example.org-empty.zone");
    ZoneIteratorPtr iterator(client_->getIterator(Name("example.org")));

    // This method is not implemented.
    EXPECT_THROW(iterator->getSOA(), isc::NotImplemented);
}

TEST_F(MemoryClientTest, addRRsetToNonExistentZoneThrows) {
    // The zone "example.org" doesn't exist, so we can't add an RRset to
    // it.
    RRsetPtr rrset_a(new RRset(Name("example.org"), RRClass::IN(), RRType::A(),
                               RRTTL(300)));
    rrset_a->addRdata(rdata::in::A("192.0.2.1"));
    EXPECT_THROW(client_->add(Name("example.org"), rrset_a), DataSourceError);
}

TEST_F(MemoryClientTest, addOutOfZoneThrows) {
    // Out of zone names should throw.
    client_->load(Name("example.org"),
                  TEST_DATA_DIR "/example.org-empty.zone");

    RRsetPtr rrset_a(new RRset(Name("a.example.com"),
                               RRClass::IN(), RRType::A(), RRTTL(300)));
    rrset_a->addRdata(rdata::in::A("192.0.2.1"));

    EXPECT_THROW(client_->add(Name("example.org"), rrset_a),
                 OutOfZone);
    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, addNullRRsetThrows) {
    client_->load(Name("example.org"),
                  TEST_DATA_DIR "/example.org-rrsigs.zone");

    EXPECT_THROW(client_->add(Name("example.org"), ConstRRsetPtr()),
                 InMemoryClient::NullRRset);

    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, addEmptyRRsetThrows) {
    client_->load(Name("example.org"),
                  TEST_DATA_DIR "/example.org-rrsigs.zone");

    RRsetPtr rrset_a(new RRset(Name("example.org"), RRClass::IN(), RRType::A(),
                               RRTTL(300)));
    EXPECT_THROW(client_->add(Name("example.org"), rrset_a),
                 InMemoryClient::AddError);

    // Teardown checks for memory segment leaks
}

TEST_F(MemoryClientTest, add) {
    client_->load(Name("example.org"), TEST_DATA_DIR "/example.org-empty.zone");

    // Add another RRset
    RRsetPtr rrset_a(new RRset(Name("example.org"), RRClass::IN(), RRType::A(),
                               RRTTL(300)));
    rrset_a->addRdata(rdata::in::A("192.0.2.1"));
    client_->add(Name("example.org"), rrset_a);

    ZoneIteratorPtr iterator(client_->getIterator(Name("example.org")));

    // First we have the SOA
    ConstRRsetPtr rrset(iterator->getNextRRset());
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::A(), rrset->getType());

    rrset = iterator->getNextRRset();
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::SOA(), rrset->getType());

    // There's nothing else in this zone
    EXPECT_EQ(ConstRRsetPtr(), iterator->getNextRRset());
}

TEST_F(MemoryClientTest, findZoneThrowsNotImplemented) {
    // This method is not implemented.
    EXPECT_THROW(client_->findZone(Name(".")),
                 isc::NotImplemented);
}

TEST_F(MemoryClientTest, findZone2) {
    client_->load(Name("example.org"),
                  TEST_DATA_DIR "/example.org-rrsigs.zone");

    isc::datasrc::memory::ZoneTable::FindResult
        result(client_->findZone2(Name("example.com")));
    EXPECT_EQ(result::NOTFOUND, result.code);
    EXPECT_EQ(static_cast<ZoneData*>(NULL),
              result.zone_data);

    isc::datasrc::memory::ZoneTable::FindResult
        result2(client_->findZone2(Name("example.org")));
    EXPECT_EQ(result::SUCCESS, result2.code);
    EXPECT_NE(static_cast<ZoneData*>(NULL),
              result2.zone_data);

    /* Check SOA */
    const ZoneNode* node = result2.zone_data->getOriginNode();
    EXPECT_NE(static_cast<const ZoneNode*>(NULL), node);

    const RdataSet* set = node->getData();
    EXPECT_NE(static_cast<const RdataSet*>(NULL), set);
    EXPECT_EQ(RRType::SOA(), set->type);

    set = set->getNext();
    EXPECT_EQ(static_cast<const RdataSet*>(NULL), set);

    /* Check ns1.example.org */
    const ZoneTree& tree = result2.zone_data->getZoneTree();
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

// TODO:
// Add test for add() with separate_rrs=true
// Add test for ZoneIterator variant of load()
// Add test for leaks during allocation failures using TestMemorySegment
// Iterate through an entire zone
}
