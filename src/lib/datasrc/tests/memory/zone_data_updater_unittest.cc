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

#include <config.h>

#include <datasrc/memory/zone_data_updater.h>
#include <datasrc/memory/rdataset.h>
#include <datasrc/memory/zone_data.h>

#include <testutils/dnsmessage_test.h>

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>

#include <util/memory_segment_local.h>
#include <util/memory_segment_mapped.h>
#include <datasrc/tests/memory/memory_segment_mock.h>

#include <gtest/gtest.h>

#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <cassert>

using isc::testutils::textToRRset;
using namespace isc::dns;
using namespace isc::datasrc::memory;

namespace {

const char* const mapped_file = TEST_DATA_BUILDDIR "/test.mapped";

// An abstract factory class for the segments. We want fresh segment for each
// test, so we have different factories for them.
class SegmentCreator {
public:
    virtual ~SegmentCreator() {}
    typedef boost::shared_ptr<isc::util::MemorySegment> SegmentPtr;
    // Create the segment.
    virtual SegmentPtr create() const = 0;
    // Clean-up after the test. Most of them will be just NOP (the default),
    // but the file-mapped one needs to remove the file.
    virtual void cleanup() const {}
};

ZoneNode*
getNode(isc::util::MemorySegment& mem_sgmt, const Name& name,
        ZoneData* zone_data)
{
    ZoneNode* node = NULL;
    zone_data->insertName(mem_sgmt, name, &node);
    EXPECT_NE(static_cast<ZoneNode*>(NULL), node);
    return (node);
}

class ZoneDataUpdaterTest : public ::testing::TestWithParam<SegmentCreator*> {
protected:
    ZoneDataUpdaterTest() :
        zname_("example.org"), zclass_(RRClass::IN()),
        mem_sgmt_(GetParam()->create())
    {
        ZoneData* data = ZoneData::create(*mem_sgmt_, zname_);
        mem_sgmt_->setNamedAddress("Test zone data", data);
        updater_.reset(new ZoneDataUpdater(*mem_sgmt_, zclass_, zname_,
                                           *data));
    }

    ~ZoneDataUpdaterTest() {
        assert(updater_);
        ZoneData::destroy(*mem_sgmt_, getZoneData(), zclass_);
        // Release the updater, so it frees all memory inside the segment too
        updater_.reset();
        mem_sgmt_->clearNamedAddress("Test zone data");
        if (!mem_sgmt_->allMemoryDeallocated()) {
            ADD_FAILURE() << "Memory leak detected";
        }
        GetParam()->cleanup();
    }

    void clearZoneData() {
        assert(updater_);
        ZoneData::destroy(*mem_sgmt_, getZoneData(), zclass_);
        mem_sgmt_->clearNamedAddress("Test zone data");
        updater_.reset();
        ZoneData* data = ZoneData::create(*mem_sgmt_, zname_);
        mem_sgmt_->setNamedAddress("Test zone data", data);
        updater_.reset(new ZoneDataUpdater(*mem_sgmt_, zclass_, zname_,
                                           *data));
    }

    ZoneData* getZoneData() {
        return (static_cast<ZoneData*>(
            mem_sgmt_->getNamedAddress("Test zone data").second));
    }

    const Name zname_;
    const RRClass zclass_;
    boost::shared_ptr<isc::util::MemorySegment> mem_sgmt_;
    boost::scoped_ptr<ZoneDataUpdater> updater_;
};

class TestSegmentCreator : public SegmentCreator {
public:
    virtual SegmentPtr create() const {
        return (SegmentPtr(new test::MemorySegmentMock));
    }
};

TestSegmentCreator test_segment_creator;

INSTANTIATE_TEST_CASE_P(TestSegment, ZoneDataUpdaterTest,
                        ::testing::Values(static_cast<SegmentCreator*>(
                            &test_segment_creator)));

class MemorySegmentCreator : public SegmentCreator {
public:
    virtual SegmentPtr create() const {
        // We are not really supposed to create the segment directly in real
        // code, but it should be OK inside tests.
        return (SegmentPtr(new isc::util::MemorySegmentLocal));
    }
};

MemorySegmentCreator memory_segment_creator;

INSTANTIATE_TEST_CASE_P(LocalSegment, ZoneDataUpdaterTest,
                        ::testing::Values(static_cast<SegmentCreator*>(
                            &memory_segment_creator)));

#ifdef USE_SHARED_MEMORY
class MappedSegmentCreator : public SegmentCreator {
public:
    MappedSegmentCreator(size_t initial_size =
                         isc::util::MemorySegmentMapped::INITIAL_SIZE) :
        initial_size_(initial_size)
    {}
    virtual SegmentPtr create() const {
        return (SegmentPtr(new isc::util::MemorySegmentMapped(
                               mapped_file,
                               isc::util::MemorySegmentMapped::CREATE_ONLY,
                               initial_size_)));
    }
    virtual void cleanup() const {
        EXPECT_EQ(0, unlink(mapped_file));
    }
private:
    const size_t initial_size_;
};

// There should be no initialization fiasco there. We only set int value inside
// and don't use it until the create() is called.
MappedSegmentCreator small_creator(4092), default_creator;

INSTANTIATE_TEST_CASE_P(MappedSegment, ZoneDataUpdaterTest, ::testing::Values(
                            static_cast<SegmentCreator*>(&small_creator),
                            static_cast<SegmentCreator*>(&default_creator)));
#endif

TEST_P(ZoneDataUpdaterTest, bothNull) {
    // At least either covered RRset or RRSIG must be non NULL.
    EXPECT_THROW(updater_->add(ConstRRsetPtr(), ConstRRsetPtr()),
                 ZoneDataUpdater::NullRRset);
}

TEST_P(ZoneDataUpdaterTest, zoneMinTTL) {
    // If we add SOA, zone's min TTL will be updated.
    updater_->add(textToRRset(
                      "example.org. 3600 IN SOA . . 0 0 0 0 1200",
                      zclass_, zname_),
                  ConstRRsetPtr());
    isc::util::InputBuffer b(getZoneData()->getMinTTLData(), sizeof(uint32_t));
    EXPECT_EQ(RRTTL(1200), RRTTL(b));
}

TEST_P(ZoneDataUpdaterTest, rrsigOnly) {
    // RRSIG that doesn't have covered RRset can be added.  The resulting
    // rdataset won't have "normal" RDATA but sig RDATA.
    updater_->add(ConstRRsetPtr(), textToRRset(
                      "www.example.org. 3600 IN RRSIG A 5 3 3600 "
                      "20150420235959 20051021000000 1 example.org. FAKE"));
    ZoneNode* node = getNode(*mem_sgmt_, Name("www.example.org"),
                             getZoneData());
    const RdataSet* rdset = node->getData();
    ASSERT_NE(static_cast<RdataSet*>(NULL), rdset);
    rdset = RdataSet::find(rdset, RRType::A(), true);
    ASSERT_NE(static_cast<RdataSet*>(NULL), rdset);
    EXPECT_EQ(0, rdset->getRdataCount());
    EXPECT_EQ(1, rdset->getSigRdataCount());

    // The RRSIG covering A must not prohibit an actual A RRset from
    // being added later.
    updater_->add(textToRRset("www.example.org. 3600 IN A 192.0.2.1"),
                  ConstRRsetPtr());

    // The special "wildcarding" node mark should be added for the RRSIG-only
    // case, too.
    updater_->add(ConstRRsetPtr(), textToRRset(
                      "*.wild.example.org. 3600 IN RRSIG A 5 3 3600 "
                      "20150420235959 20051021000000 1 example.org. FAKE"));
    node = getNode(*mem_sgmt_, Name("wild.example.org"), getZoneData());
    EXPECT_TRUE(node->getFlag(ZoneData::WILDCARD_NODE));

    // Simply adding RRSIG covering (delegating NS) shouldn't enable callback
    // in search.
    updater_->add(ConstRRsetPtr(), textToRRset(
                      "child.example.org. 3600 IN RRSIG NS 5 3 3600 "
                      "20150420235959 20051021000000 1 example.org. FAKE"));
    node = getNode(*mem_sgmt_, Name("child.example.org"), getZoneData());
    EXPECT_FALSE(node->getFlag(ZoneNode::FLAG_CALLBACK));

    // Same for DNAME
    updater_->add(ConstRRsetPtr(), textToRRset(
                      "dname.example.org. 3600 IN RRSIG DNAME 5 3 3600 "
                      "20150420235959 20051021000000 1 example.org. FAKE"));
    node = getNode(*mem_sgmt_, Name("dname.example.org"), getZoneData());
    EXPECT_FALSE(node->getFlag(ZoneNode::FLAG_CALLBACK));

    // Likewise, RRSIG for NSEC3PARAM alone shouldn't make the zone
    // "NSEC3-signed".
    updater_->add(ConstRRsetPtr(), textToRRset(
                      "example.org. 3600 IN RRSIG NSEC3PARAM 5 3 3600 "
                      "20150420235959 20051021000000 1 example.org. FAKE"));
    EXPECT_FALSE(getZoneData()->isNSEC3Signed());

    // And same for (RRSIG for) NSEC and "is signed".
    updater_->add(ConstRRsetPtr(), textToRRset(
                      "example.org. 3600 IN RRSIG NSEC 5 3 3600 "
                      "20150420235959 20051021000000 1 example.org. FAKE"));
    EXPECT_FALSE(getZoneData()->isSigned());
}

// Commonly used checks for rrsigForNSEC3Only
void
checkNSEC3Rdata(isc::util::MemorySegment& mem_sgmt, const Name& name,
                ZoneData* zone_data)
{
    ZoneNode* node = NULL;
    zone_data->getNSEC3Data()->insertName(mem_sgmt, name, &node);
    ASSERT_NE(static_cast<ZoneNode*>(NULL), node);
    const RdataSet* rdset = node->getData();
    ASSERT_NE(static_cast<RdataSet*>(NULL), rdset);
    ASSERT_EQ(RRType::NSEC3(), rdset->type);
    EXPECT_EQ(0, rdset->getRdataCount());
    EXPECT_EQ(1, rdset->getSigRdataCount());
}

TEST_P(ZoneDataUpdaterTest, rrsigForNSEC3Only) {
    // Adding only RRSIG covering NSEC3 is tricky.  It should go to the
    // separate NSEC3 tree, but the separate space is only created when
    // NSEC3 or NSEC3PARAM is added.  So, in many cases RRSIG-only is allowed,
    // but if no NSEC3 or NSEC3PARAM has been added it will be rejected.

    // Below we use abnormal owner names and RDATA for NSEC3s for brevity,
    // but that doesn't matter for this test.

    // Add NSEC3PARAM, then RRSIG-only, which is okay.
    updater_->add(textToRRset(
                      "example.org. 3600 IN NSEC3PARAM 1 0 12 AABBCCDD"),
                  textToRRset(
                      "example.org. 3600 IN RRSIG NSEC3PARAM 5 3 3600 "
                      "20150420235959 20051021000000 1 example.org. FAKE"));
    EXPECT_TRUE(getZoneData()->isNSEC3Signed());
    updater_->add(ConstRRsetPtr(),
                  textToRRset(
                      "09GM.example.org. 3600 IN RRSIG NSEC3 5 3 3600 "
                      "20150420235959 20051021000000 1 example.org. FAKE"));
    checkNSEC3Rdata(*mem_sgmt_, Name("09GM.example.org"), getZoneData());

    // Clear the current content of zone, then add NSEC3
    clearZoneData();
    updater_->add(textToRRset(
                      "AABB.example.org. 3600 IN NSEC3 1 0 10 AA 00000000 A"),
                  textToRRset(
                      "AABB.example.org. 3600 IN RRSIG NSEC3 5 3 3600 "
                      "20150420235959 20051021000000 1 example.org. FAKE"));
    updater_->add(ConstRRsetPtr(),
                  textToRRset(
                      "09GM.example.org. 3600 IN RRSIG NSEC3 5 3 3600 "
                      "20150420235959 20051021000000 1 example.org. FAKE"));
    checkNSEC3Rdata(*mem_sgmt_, Name("09GM.example.org"), getZoneData());

    // If we add only RRSIG without any NSEC3 related data beforehand,
    // it will be rejected; it's a limitation of the current implementation.
    clearZoneData();
    EXPECT_THROW(updater_->add(
                     ConstRRsetPtr(),
                     textToRRset(
                         "09GM.example.org. 3600 IN RRSIG NSEC3 5 3 3600 "
                         "20150420235959 20051021000000 1 example.org. FAKE")),
                 isc::NotImplemented);
}

// Generate many small RRsets. This tests that the underlying memory segment
// can grow during the execution and that the updater handles that well.
//
// Some of the grows will happen inserting the RRSIG, some with the TXT. Or,
// at least we hope so.
TEST_P(ZoneDataUpdaterTest, manySmallRRsets) {
    for (size_t i = 0; i < 32768; ++i) {
        const std::string name(boost::lexical_cast<std::string>(i) +
                               ".example.org.");
        updater_->add(textToRRset(name + " 3600 IN TXT " +
                                  std::string(30, 'X')),
                      textToRRset(name + " 3600 IN RRSIG TXT 5 3 3600 "
                                  "20150420235959 20051021000000 1 "
                                  "example.org. FAKE"));
        ZoneNode* node = getNode(*mem_sgmt_,
                                 Name(boost::lexical_cast<std::string>(i) +
                                      ".example.org"), getZoneData());
        const RdataSet* rdset = node->getData();
        ASSERT_NE(static_cast<RdataSet*>(NULL), rdset);
        rdset = RdataSet::find(rdset, RRType::TXT(), true);
        ASSERT_NE(static_cast<RdataSet*>(NULL), rdset);
        EXPECT_EQ(1, rdset->getRdataCount());
        EXPECT_EQ(1, rdset->getSigRdataCount());
    }
}

TEST_P(ZoneDataUpdaterTest, updaterCollision) {
    ZoneData* zone_data = ZoneData::create(*mem_sgmt_,
                                           Name("another.example.com."));
    EXPECT_THROW(ZoneDataUpdater(*mem_sgmt_, RRClass::IN(),
                                 Name("another.example.com."), *zone_data),
                 isc::InvalidOperation);
    ZoneData::destroy(*mem_sgmt_, zone_data, RRClass::IN());
}

}
