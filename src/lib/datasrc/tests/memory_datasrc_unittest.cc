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
#include <dns/rrttl.h>

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

/// \brief Test fixture for the MemoryZone class
class MemoryZoneTest : public ::testing::Test {
public:
    MemoryZoneTest() :
        class_(RRClass::IN()),
        origin_("example.org"),
        ns_name_("ns.example.org"),
        zone_(class_, origin_),
        rr_out_(new RRset(Name("example.com"), class_, RRType::A(),
            RRTTL(300))),
        rr_ns_(new RRset(origin_, class_, RRType::NS(), RRTTL(300))),
        rr_ns_a_(new RRset(ns_name_, class_, RRType::A(), RRTTL(300))),
        rr_ns_aaaa_(new RRset(ns_name_, class_, RRType::AAAA(), RRTTL(300))),
        rr_a_(new RRset(origin_, class_, RRType::A(), RRTTL(300))),
        rr_delegation_(new RRset(Name("subdomain.example.org"), class_,
            RRType::NS(), RRTTL(300)))
    {
    }
    // Some data to test with
    RRClass class_;
    Name origin_, ns_name_;
    // The zone to torture by tests
    MemoryZone zone_;

    /*
     * Some RRsets to put inside the zone.
     * They are empty, but the MemoryZone does not have a reason to look
     * inside anyway. We will check it finds them and does not change
     * the pointer.
     */
    RRsetPtr
        // Out of zone RRset
        rr_out_,
        // NS of example.org
        rr_ns_,
        // A of ns.example.org
        rr_ns_a_,
        // AAAA of ns.example.org
        rr_ns_aaaa_,
        // A of example.org
        rr_a_,
        // A subdomain.example.org NS, for delegation
        rr_delegation_;

    /**
     * \brief Test one find query to the zone.
     *
     * Asks a query to the zone and checks it does not throw and returns
     * expected results. It returns nothing, it just signals failures
     * to GTEST.
     *
     * \param name The name to ask for.
     * \param rrtype The RRType to ask of.
     * \param result The expected code of the result.
     * \param answer The expected rrset, if any should be returned.
     */
    void findTest(const Name& name, const RRType& rrtype, Zone::Result result,
        const ConstRRsetPtr& answer = ConstRRsetPtr())
    {
        // The whole block is inside, because we need to check the result and
        // we can't assign to FindResult
        EXPECT_NO_THROW({
            Zone::FindResult find_result(zone_.find(name, rrtype));
            // Check it returns correct answers
            EXPECT_EQ(result, find_result.code);
            EXPECT_EQ(answer, find_result.rrset);
        });
    }
};

/**
 * \brief Test MemoryZone::MemoryZone constructor.
 *
 * Takes the created zone and checks its properties they are the same
 * as passed parameters.
 */
TEST_F(MemoryZoneTest, constructor) {
    ASSERT_EQ(class_, zone_.getClass());
    ASSERT_EQ(origin_, zone_.getOrigin());
}

/**
 * \brief Test adding.
 *
 * We test that it throws at the correct moments and the correct exceptions.
 * And we test the return value.
 */
TEST_F(MemoryZoneTest, add) {
    // This one does not belong to this zone
    EXPECT_THROW(zone_.add(rr_out_), MemoryZone::OutOfZone);
    // Test null pointer
    EXPECT_THROW(zone_.add(ConstRRsetPtr()), MemoryZone::NullRRset);

    using namespace result; // Who should write the prefix all the time
    // Now put all the data we have there. It should throw nothing
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_a_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_aaaa_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_a_)));

    // Try putting there something twice, it should be rejected
    EXPECT_NO_THROW(EXPECT_EQ(EXIST, zone_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(EXIST, zone_.add(rr_ns_a_)));
}

/**
 * \brief Test searching.
 *
 * Check it finds or does not find correctly and does not throw exceptions.
 * \todo This doesn't do any kind of CNAME and so on. If it isn't
 *     directly there, it just tells it doesn't exist.
 */
TEST_F(MemoryZoneTest, find) {
    // Fill some data inside
    using namespace result; // Who should write the prefix all the time
    // Now put all the data we have there. It should throw nothing
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_a_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_aaaa_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_a_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_delegation_)));

    // These two should be successful
    findTest(origin_, RRType::NS(), Zone::SUCCESS, rr_ns_);
    findTest(ns_name_, RRType::A(), Zone::SUCCESS, rr_ns_a_);

    // These domain exist but don't have the provided RRType
    findTest(origin_, RRType::AAAA(), Zone::NXRRSET);
    findTest(ns_name_, RRType::NS(), Zone::NXRRSET);

    // These domains don't exist (and one is out of the zone)
    findTest(Name("nothere.example.org"), RRType::A(), Zone::NXDOMAIN);
    findTest(Name("example.net"), RRType::A(), Zone::NXDOMAIN);

    // This should delegate
    findTest(Name("a.subdomain.example.org"), RRType::MX(), Zone::DELEGATION,
        rr_delegation_);
}

}
