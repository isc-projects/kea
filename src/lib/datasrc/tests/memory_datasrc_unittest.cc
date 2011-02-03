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
#include <dns/masterload.h>

#include <datasrc/memory_datasrc.h>

#include <gtest/gtest.h>

using namespace isc::dns;
using namespace isc::datasrc;

namespace {
// Commonly used result codes (Who should write the prefix all the time)
using result::SUCCESS;
using result::EXIST;

class MemoryDataSrcTest : public ::testing::Test {
protected:
    MemoryDataSrcTest() : rrclass(RRClass::IN())
    {}
    RRClass rrclass;
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

TEST_F(MemoryDataSrcTest, getZoneCount) {
    EXPECT_EQ(0, memory_datasrc.getZoneCount());
    memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(rrclass, Name("example.com"))));
    EXPECT_EQ(1, memory_datasrc.getZoneCount());

    // duplicate add.  counter shouldn't change
    memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(rrclass, Name("example.com"))));
    EXPECT_EQ(1, memory_datasrc.getZoneCount());

    // add one more
    memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(rrclass, Name("example.org"))));
    EXPECT_EQ(2, memory_datasrc.getZoneCount());
}

/// \brief Test fixture for the MemoryZone class
class MemoryZoneTest : public ::testing::Test {
public:
    MemoryZoneTest() :
        class_(RRClass::IN()),
        origin_("example.org"),
        ns_name_("ns.example.org"),
        child_ns_name_("child.example.org"),
        child_glue_name_("ns.child.example.org"),
        grandchild_ns_name_("grand.child.example.org"),
        grandchild_glue_name_("ns.grand.child.example.org"),
        zone_(class_, origin_),
        rr_out_(new RRset(Name("example.com"), class_, RRType::A(),
            RRTTL(300))),
        rr_ns_(new RRset(origin_, class_, RRType::NS(), RRTTL(300))),
        rr_ns_a_(new RRset(ns_name_, class_, RRType::A(), RRTTL(300))),
        rr_ns_aaaa_(new RRset(ns_name_, class_, RRType::AAAA(), RRTTL(300))),
        rr_a_(new RRset(origin_, class_, RRType::A(), RRTTL(300))),
        rr_child_ns_(new RRset(child_ns_name_, class_, RRType::NS(),
                               RRTTL(300))),
        rr_child_glue_(new RRset(child_glue_name_, class_, RRType::A(),
                              RRTTL(300))),
        rr_grandchild_ns_(new RRset(grandchild_ns_name_, class_, RRType::NS(),
                                    RRTTL(300))),
        rr_grandchild_glue_(new RRset(grandchild_glue_name_, class_,
                                      RRType::AAAA(), RRTTL(300)))
    {
    }
    // Some data to test with
    const RRClass class_;
    const Name origin_, ns_name_, child_ns_name_, child_glue_name_,
        grandchild_ns_name_, grandchild_glue_name_;
    // The zone to torture by tests
    MemoryZone zone_;

    /*
     * Some RRsets to put inside the zone.
     * They are empty, but the MemoryZone does not have a reason to look
     * inside anyway. We will check it finds them and does not change
     * the pointer.
     */
    ConstRRsetPtr
        // Out of zone RRset
        rr_out_,
        // NS of example.org
        rr_ns_,
        // A of ns.example.org
        rr_ns_a_,
        // AAAA of ns.example.org
        rr_ns_aaaa_,
        // A of example.org
        rr_a_;
    ConstRRsetPtr rr_child_ns_; // NS of a child domain (for delegation)
    ConstRRsetPtr rr_child_glue_; // glue RR of the child domain
    ConstRRsetPtr rr_grandchild_ns_; // NS below a zone cut (unusual)
    ConstRRsetPtr rr_grandchild_glue_; // glue RR below a deeper zone cut

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
     * \param check_answer Should a check against equality of the answer be
     *     done?
     * \param answer The expected rrset, if any should be returned.
     * \param zone Check different MemoryZone object than zone_ (if NULL,
     *     uses zone_)
     */
    void findTest(const Name& name, const RRType& rrtype, Zone::Result result,
                  bool check_answer = true,
                  const ConstRRsetPtr& answer = ConstRRsetPtr(),
                  MemoryZone *zone = NULL,
                  Zone::FindOptions options = Zone::FIND_DEFAULT)
    {
        if (!zone) {
            zone = &zone_;
        }
        // The whole block is inside, because we need to check the result and
        // we can't assign to FindResult
        EXPECT_NO_THROW({
                Zone::FindResult find_result(zone->find(name, rrtype,
                                                        options));
                // Check it returns correct answers
                EXPECT_EQ(result, find_result.code);
                if (check_answer) {
                    EXPECT_EQ(answer, find_result.rrset);
                }
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

    // Now put all the data we have there. It should throw nothing
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_a_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_aaaa_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_a_)));

    // Try putting there something twice, it should be rejected
    EXPECT_NO_THROW(EXPECT_EQ(EXIST, zone_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(EXIST, zone_.add(rr_ns_a_)));
}

// Test adding child zones and zone cut handling
TEST_F(MemoryZoneTest, delegationNS) {
    // add in-zone data
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_)));

    // install a zone cut
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_child_ns_)));

    // below the zone cut
    findTest(Name("www.child.example.org"), RRType::A(), Zone::DELEGATION,
             true, rr_child_ns_);

    // at the zone cut
    findTest(Name("child.example.org"), RRType::A(), Zone::DELEGATION,
             true, rr_child_ns_);
    findTest(Name("child.example.org"), RRType::NS(), Zone::DELEGATION,
             true, rr_child_ns_);

    // finding NS for the apex (origin) node.  This must not be confused
    // with delegation due to the existence of an NS RR.
    findTest(origin_, RRType::NS(), Zone::SUCCESS, true, rr_ns_);

    // unusual case of "nested delegation": the highest cut should be used.
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_grandchild_ns_)));
    findTest(Name("www.grand.child.example.org"), RRType::A(),
             Zone::DELEGATION, true, rr_child_ns_); // note: !rr_grandchild_ns_
}

TEST_F(MemoryZoneTest, glue) {
    // install zone data:
    // a zone cut
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_child_ns_)));
    // glue for this cut
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_child_glue_)));
    // a nested zone cut (unusual)
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_grandchild_ns_)));
    // glue under the deeper zone cut
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_grandchild_glue_)));

    // by default glue is hidden due to the zone cut
    findTest(child_glue_name_, RRType::A(), Zone::DELEGATION, true,
             rr_child_ns_);


    // If we do it in the "glue OK" mode, we should find the exact match.
    findTest(child_glue_name_, RRType::A(), Zone::SUCCESS, true,
             rr_child_glue_, NULL, Zone::FIND_GLUE_OK);

    // glue OK + NXRRSET case
    findTest(child_glue_name_, RRType::AAAA(), Zone::NXRRSET, true,
             ConstRRsetPtr(), NULL, Zone::FIND_GLUE_OK);

    // glue OK + NXDOMAIN case
    findTest(Name("www.child.example.org"), RRType::A(), Zone::DELEGATION,
             true, rr_child_ns_, NULL, Zone::FIND_GLUE_OK);

    // TODO:
    // glue name would match a wildcard under a zone cut: wildcard match
    // shouldn't happen under a cut and result must be PARTIALMATCH
    // (This case cannot be tested yet)

    // nested cut case.  The glue should be found.
    findTest(grandchild_glue_name_, RRType::AAAA(), Zone::SUCCESS,
             true, rr_grandchild_glue_, NULL, Zone::FIND_GLUE_OK);    

    // A non-existent name in nested cut.  This should result in delegation
    // at the highest zone cut.
    findTest(Name("www.grand.child.example.org"), RRType::TXT(),
             Zone::DELEGATION, true, rr_child_ns_, NULL, Zone::FIND_GLUE_OK);
}

// Test adding DNAMEs and resulting delegation handling
// Listing ideas only for now
TEST_F(MemoryZoneTest, delegationDNAME) {
    // apex DNAME: allowed by spec.  No DNAME delegation at the apex;
    // descendants are subject to delegation.

    // Other cases of NS and DNAME mixture are prohibited.
    // BIND 9 doesn't reject such cases at load time, however.

    // DNAME and ordinary types (allowed by spec)
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
    // Now put all the data we have there. It should throw nothing
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_a_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_aaaa_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_a_)));

    // These two should be successful
    findTest(origin_, RRType::NS(), Zone::SUCCESS, true, rr_ns_);
    findTest(ns_name_, RRType::A(), Zone::SUCCESS, true, rr_ns_a_);

    // These domain exist but don't have the provided RRType
    findTest(origin_, RRType::AAAA(), Zone::NXRRSET);
    findTest(ns_name_, RRType::NS(), Zone::NXRRSET);

    // These domains don't exist (and one is out of the zone)
    findTest(Name("nothere.example.org"), RRType::A(), Zone::NXDOMAIN);
    findTest(Name("example.net"), RRType::A(), Zone::NXDOMAIN);
}

TEST_F(MemoryZoneTest, emptyNode) {
    /*
     * The backend RBTree for this test should look like as follows:
     *          example.org
     *               |
     *              baz (empty; easy case)
     *            /  |  \
     *          bar  |  x.foo ('foo' part is empty; a bit trickier)
     *              bbb
     *             /
     *           aaa
     */

    // Construct the test zone
    const char* const names[] = {
        "bar.example.org", "x.foo.example.org", "aaa.baz.example.org",
        "bbb.baz.example.org.", NULL};
    for (int i = 0; names[i] != NULL; ++i) {
        ConstRRsetPtr rrset(new RRset(Name(names[i]), class_, RRType::A(),
                                      RRTTL(300)));
        EXPECT_EQ(SUCCESS, zone_.add(rrset));
    }

    // empty node matching, easy case: the node for 'baz' exists with
    // no data.
    findTest(Name("baz.example.org"), RRType::A(), Zone::NXRRSET);

    // empty node matching, a trickier case: the node for 'foo' is part of
    // "x.foo", which should be considered an empty node.
    findTest(Name("foo.example.org"), RRType::A(), Zone::NXRRSET);

    // "org" is contained in "example.org", but it shouldn't be treated as
    // NXRRSET because it's out of zone.
    // Note: basically we don't expect such a query to be performed (the common
    // operation is to identify the best matching zone first then perform
    // search it), but we shouldn't be confused even in the unexpected case.
    findTest(Name("org"), RRType::A(), Zone::NXDOMAIN);
}

TEST_F(MemoryZoneTest, load) {
    // Put some data inside the zone
    EXPECT_NO_THROW(EXPECT_EQ(result::SUCCESS, zone_.add(rr_ns_)));
    // Loading with different origin should fail
    EXPECT_THROW(zone_.load(TEST_DATA_DIR "/root.zone"), MasterLoadError);
    // See the original data is still there, survived the exception
    findTest(origin_, RRType::NS(), Zone::SUCCESS, true, rr_ns_);
    // Create correct zone
    MemoryZone rootzone(class_, Name("."));
    // Try putting something inside
    EXPECT_NO_THROW(EXPECT_EQ(result::SUCCESS, rootzone.add(rr_ns_aaaa_)));
    // Load the zone. It should overwrite/remove the above RRset
    EXPECT_NO_THROW(rootzone.load(TEST_DATA_DIR "/root.zone"));

    // Now see there are some rrsets (we don't look inside, though)
    findTest(Name("."), RRType::SOA(), Zone::SUCCESS, false, ConstRRsetPtr(),
        &rootzone);
    findTest(Name("."), RRType::NS(), Zone::SUCCESS, false, ConstRRsetPtr(),
        &rootzone);
    findTest(Name("a.root-servers.net."), RRType::A(), Zone::SUCCESS, false,
        ConstRRsetPtr(), &rootzone);
    // But this should no longer be here
    findTest(ns_name_, RRType::AAAA(), Zone::NXDOMAIN, true, ConstRRsetPtr(),
        &rootzone);

    // Try loading zone that is wrong in a different way
    EXPECT_THROW(zone_.load(TEST_DATA_DIR "/duplicate_rrset.zone"),
        MasterLoadError);
}

TEST_F(MemoryZoneTest, swap) {
    // build one zone with some data
    MemoryZone zone1(class_, origin_);
    EXPECT_EQ(result::SUCCESS, zone1.add(rr_ns_));
    EXPECT_EQ(result::SUCCESS, zone1.add(rr_ns_aaaa_));

    // build another zone of a different RR class with some other data
    const Name other_origin("version.bind");
    ASSERT_NE(origin_, other_origin); // make sure these two are different
    MemoryZone zone2(RRClass::CH(), other_origin);
    EXPECT_EQ(result::SUCCESS,
              zone2.add(RRsetPtr(new RRset(Name("version.bind"),
                                           RRClass::CH(), RRType::TXT(),
                                           RRTTL(0)))));

    zone1.swap(zone2);
    EXPECT_EQ(other_origin, zone1.getOrigin());
    EXPECT_EQ(origin_, zone2.getOrigin());
    EXPECT_EQ(RRClass::CH(), zone1.getClass());
    EXPECT_EQ(RRClass::IN(), zone2.getClass());
    // make sure the zone data is swapped, too
    findTest(origin_, RRType::NS(), Zone::NXDOMAIN, false, ConstRRsetPtr(),
             &zone1);
    findTest(other_origin, RRType::TXT(), Zone::SUCCESS, false,
             ConstRRsetPtr(), &zone1);
    findTest(origin_, RRType::NS(), Zone::SUCCESS, false, ConstRRsetPtr(),
             &zone2);
    findTest(other_origin, RRType::TXT(), Zone::NXDOMAIN, false,
             ConstRRsetPtr(), &zone2);
}

TEST_F(MemoryZoneTest, getFileName) {
    // for an empty zone the file name should also be empty.
    EXPECT_TRUE(zone_.getFileName().empty());

    // if loading a zone fails the file name shouldn't be set.
    EXPECT_THROW(zone_.load(TEST_DATA_DIR "/root.zone"), MasterLoadError);
    EXPECT_TRUE(zone_.getFileName().empty());

    // after a successful load, the specified file name should be set
    MemoryZone rootzone(class_, Name("."));
    EXPECT_NO_THROW(rootzone.load(TEST_DATA_DIR "/root.zone"));
    EXPECT_EQ(TEST_DATA_DIR "/root.zone", rootzone.getFileName());
    // overriding load, which will fail
    EXPECT_THROW(rootzone.load(TEST_DATA_DIR "/duplicate_rrset.zone"),
                 MasterLoadError);
    // the file name should be intact.
    EXPECT_EQ(TEST_DATA_DIR "/root.zone", rootzone.getFileName());

    // After swap, file names should also be swapped.
    zone_.swap(rootzone);
    EXPECT_EQ(TEST_DATA_DIR "/root.zone", zone_.getFileName());
    EXPECT_TRUE(rootzone.getFileName().empty());
}
}
