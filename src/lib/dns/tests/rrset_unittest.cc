// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rrset.h>

#include <dns/tests/unittest_util.h>
#include <util/unittests/wiredata.h>

#include <gtest/gtest.h>

#include <stdexcept>
#include <sstream>

using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
class RRsetTest : public ::testing::Test {
protected:
    RRsetTest() : buffer(0),
                  test_name("test.example.com"),
                  test_domain("example.com"),
                  test_nsname("ns.example.com"),
                  rrset_a(test_name, RRClass::IN(), RRType::A(), RRTTL(3600)),
                  rrset_a_empty(test_name, RRClass::IN(), RRType::A(),
                                RRTTL(3600)),
                  rrset_any_a_empty(test_name, RRClass::ANY(), RRType::A(),
                                    RRTTL(3600)),
                  rrset_none_a_empty(test_name, RRClass::NONE(), RRType::A(),
                                     RRTTL(3600)),
                  rrset_ns(test_domain, RRClass::IN(), RRType::NS(),
                           RRTTL(86400)),
                  rrset_ch_txt(test_domain, RRClass::CH(), RRType::TXT(),
                               RRTTL(0))
    {
        rrset_a.addRdata(in::A("192.0.2.1"));
        rrset_a.addRdata(in::A("192.0.2.2"));
    }

    OutputBuffer buffer;
    MessageRenderer renderer;
    Name test_name;
    Name test_domain;
    Name test_nsname;
    RRset rrset_a;
    RRset rrset_a_empty;
    RRset rrset_any_a_empty;
    RRset rrset_none_a_empty;
    RRset rrset_ns;
    RRset rrset_ch_txt;
    std::vector<unsigned char> wiredata;

    // max number of Rdata objects added to a test RRset object.
    // this is an arbitrary chosen limit, but should be sufficiently large
    // in practice and reasonable even as an extreme test case.
    static const int MAX_RDATA_COUNT = 100;
};

TEST_F(RRsetTest, getRdataCount) {
    for (int i = 0; i < MAX_RDATA_COUNT; ++i) {
        EXPECT_EQ(i, rrset_a_empty.getRdataCount());
        rrset_a_empty.addRdata(in::A("192.0.2.1"));
    }
}

TEST_F(RRsetTest, getName) {
    EXPECT_EQ(test_name, rrset_a.getName());
    EXPECT_EQ(test_domain, rrset_ns.getName());
}

TEST_F(RRsetTest, getClass) {
    EXPECT_EQ(RRClass("IN"), rrset_a.getClass());
    EXPECT_EQ(RRClass("CH"), rrset_ch_txt.getClass());
}

TEST_F(RRsetTest, getType) {
    EXPECT_EQ(RRType("A"), rrset_a.getType());
    EXPECT_EQ(RRType("NS"), rrset_ns.getType());
    EXPECT_EQ(RRType("TXT"), rrset_ch_txt.getType());
}

TEST_F(RRsetTest, getTTL) {
    EXPECT_EQ(RRTTL(3600), rrset_a.getTTL());
    EXPECT_EQ(RRTTL(86400), rrset_ns.getTTL());
    EXPECT_EQ(RRTTL(0), rrset_ch_txt.getTTL());
}

TEST_F(RRsetTest, setTTL) {
    rrset_a.setTTL(RRTTL(86400));
    EXPECT_EQ(RRTTL(86400), rrset_a.getTTL());
    rrset_a.setTTL(RRTTL(0));
    EXPECT_EQ(RRTTL(0), rrset_a.getTTL());
}

TEST_F(RRsetTest, isSameKind) {
    RRset rrset_w(test_name, RRClass::IN(), RRType::A(), RRTTL(3600));
    RRset rrset_x(test_name, RRClass::IN(), RRType::A(), RRTTL(3600));
    RRset rrset_y(test_name, RRClass::IN(), RRType::NS(), RRTTL(3600));
    RRset rrset_z(test_name, RRClass::CH(), RRType::A(), RRTTL(3600));
    RRset rrset_p(test_nsname, RRClass::IN(), RRType::A(), RRTTL(3600));

    EXPECT_TRUE(rrset_w.isSameKind(rrset_w));
    EXPECT_TRUE(rrset_w.isSameKind(rrset_x));
    EXPECT_FALSE(rrset_w.isSameKind(rrset_y));
    EXPECT_FALSE(rrset_w.isSameKind(rrset_z));
    EXPECT_FALSE(rrset_w.isSameKind(rrset_p));
}

void
addRdataTestCommon(const RRset& rrset) {
    ASSERT_EQ(2, rrset.getRdataCount());

    RdataIteratorPtr it = rrset.getRdataIterator(); // cursor is set to the 1st
    EXPECT_FALSE(it->isLast());
    EXPECT_EQ(0, it->getCurrent().compare(in::A("192.0.2.1")));
    it->next();
    EXPECT_FALSE(it->isLast());
    EXPECT_EQ(0, it->getCurrent().compare(in::A("192.0.2.2")));
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(RRsetTest, addRdata) {
    addRdataTestCommon(rrset_a);

    // Reference version of addRdata() doesn't allow to add a different
    // type of Rdata.
    EXPECT_THROW(rrset_a.addRdata(generic::NS(test_nsname)), std::bad_cast);
}

TEST_F(RRsetTest, addRdataPtr) {
    rrset_a_empty.addRdata(createRdata(rrset_a_empty.getType(),
                                       rrset_a_empty.getClass(),
                                       "192.0.2.1"));
    rrset_a_empty.addRdata(createRdata(rrset_a_empty.getType(),
                                       rrset_a_empty.getClass(),
                                       "192.0.2.2"));
    addRdataTestCommon(rrset_a_empty);
}

TEST_F(RRsetTest, addRdataPtrMismatched) {
    // Pointer version of addRdata() doesn't type check and does allow to
    //add a different type of Rdata as a result.

    // Type mismatch
    rrset_a_empty.addRdata(createRdata(RRType::NS(), RRClass::IN(),
                                       "ns.example.com."));
    EXPECT_EQ(1, rrset_a_empty.getRdataCount());

    // Class mismatch
    rrset_ch_txt.addRdata(createRdata(RRType::TXT(), RRClass::IN(),
                                      "Test String"));
    EXPECT_EQ(1, rrset_ch_txt.getRdataCount());
}

TEST_F(RRsetTest, addRdataString) {
    rrset_a_empty.addRdata("192.0.2.1");
    rrset_a_empty.addRdata("192.0.2.2");

    addRdataTestCommon(rrset_a_empty);

    // String version of addRdata() will throw for bad RDATA for
    // RRType::A().
    EXPECT_THROW(rrset_a_empty.addRdata("ns.example.com."), InvalidRdataText);
    addRdataTestCommon(rrset_a_empty);
}

TEST_F(RRsetTest, iterator) {
    // Iterator for an empty RRset.
    RdataIteratorPtr it = rrset_a_empty.getRdataIterator();
    EXPECT_TRUE(it->isLast());

    // Normal case (already tested, but do it again just in case)
    rrset_a_empty.addRdata(in::A("192.0.2.1"));
    rrset_a_empty.addRdata(in::A("192.0.2.2"));
    addRdataTestCommon(rrset_a_empty);

    // Rewind test: should be repeat the iteration by calling first().
    for (int i = 0; i < 2; ++i) {
        it = rrset_a_empty.getRdataIterator();
        it->first();
        EXPECT_FALSE(it->isLast());
        it->next();
        EXPECT_FALSE(it->isLast());
        it->next();
        EXPECT_TRUE(it->isLast());
    }
}

TEST_F(RRsetTest, toText) {
    EXPECT_EQ("test.example.com. 3600 IN A 192.0.2.1\n"
              "test.example.com. 3600 IN A 192.0.2.2\n",
              rrset_a.toText());

    // toText() cannot be performed for an empty RRset
    EXPECT_THROW(rrset_a_empty.toText(), EmptyRRset);

    // Unless it is type ANY or NONE
    EXPECT_EQ("test.example.com. 3600 ANY A\n",
              rrset_any_a_empty.toText());
    EXPECT_EQ("test.example.com. 3600 NONE A\n",
              rrset_none_a_empty.toText());
}

TEST_F(RRsetTest, getLength) {
    // Empty RRset should throw
    EXPECT_THROW(rrset_a_empty.getLength(), EmptyRRset);

    // Unless it is type ANY or NONE:
    // test.example.com = 1 + 4 + 1 + 7 + 1 + 3 + 1 = 18 octets
    // TYPE field = 2 octets
    // CLASS field = 2 octets
    // TTL field = 4 octets
    // RDLENGTH field = 2 octets
    // Total = 18 + 2 + 2 + 4 + 2 = 28 octets
    EXPECT_EQ(28, rrset_any_a_empty.getLength());
    EXPECT_EQ(28, rrset_none_a_empty.getLength());

    // RRset with single RDATA
    // 28 (above) + 4 octets (A RDATA) = 32 octets
    rrset_a_empty.addRdata(in::A("192.0.2.1"));
    EXPECT_EQ(32, rrset_a_empty.getLength());

    // 2 A RRs
    rrset_a_empty.addRdata(in::A("192.0.2.2"));
    EXPECT_EQ(32 + 32, rrset_a_empty.getLength());
}

TEST_F(RRsetTest, toWireBuffer) {
    rrset_a.toWire(buffer);

    UnitTestUtil::readWireData("rrset_toWire1", wiredata);
    matchWireData(&wiredata[0], wiredata.size(),
                  buffer.getData(), buffer.getLength());

    // toWire() cannot be performed for an empty RRset except when
    // class=ANY or class=NONE.
    buffer.clear();
    EXPECT_THROW(rrset_a_empty.toWire(buffer), EmptyRRset);

    // When class=ANY or class=NONE, toWire() can also be performed for
    // an empty RRset.
    buffer.clear();
    rrset_any_a_empty.toWire(buffer);
    wiredata.clear();
    UnitTestUtil::readWireData("rrset_toWire3", wiredata);
    matchWireData(&wiredata[0], wiredata.size(),
                  buffer.getData(), buffer.getLength());

    buffer.clear();
    rrset_none_a_empty.toWire(buffer);
    wiredata.clear();
    UnitTestUtil::readWireData("rrset_toWire4", wiredata);
    matchWireData(&wiredata[0], wiredata.size(),
                  buffer.getData(), buffer.getLength());
}

TEST_F(RRsetTest, toWireRenderer) {
    rrset_ns.addRdata(generic::NS(test_nsname));

    rrset_a.toWire(renderer);
    rrset_ns.toWire(renderer);

    UnitTestUtil::readWireData("rrset_toWire2", wiredata);
    matchWireData(&wiredata[0], wiredata.size(),
                  renderer.getData(), renderer.getLength());

    // toWire() cannot be performed for an empty RRset except when
    // class=ANY or class=NONE.
    renderer.clear();
    EXPECT_THROW(rrset_a_empty.toWire(renderer), EmptyRRset);

    // When class=ANY or class=NONE, toWire() can also be performed for
    // an empty RRset.
    renderer.clear();
    rrset_any_a_empty.toWire(renderer);
    wiredata.clear();
    UnitTestUtil::readWireData("rrset_toWire3", wiredata);
    matchWireData(&wiredata[0], wiredata.size(),
                  renderer.getData(), renderer.getLength());

    renderer.clear();
    rrset_none_a_empty.toWire(renderer);
    wiredata.clear();
    UnitTestUtil::readWireData("rrset_toWire4", wiredata);
    matchWireData(&wiredata[0], wiredata.size(),
                  renderer.getData(), renderer.getLength());
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST_F(RRsetTest, LeftShiftOperator) {
    ostringstream oss;
    oss << rrset_a;
    EXPECT_EQ(rrset_a.toText(), oss.str());
}

class RRsetRRSIGTest : public ::testing::Test {
protected:
    RRsetRRSIGTest() : test_name("test.example.com")
    {
        rrset_a = RRsetPtr(new RRset(test_name, RRClass::IN(),
                                     RRType::A(), RRTTL(3600)));
        rrset_a->addRdata(in::A("192.0.2.1"));
        rrset_a->addRdata(in::A("192.0.2.2"));

        rrset_aaaa = RRsetPtr(new RRset(test_name, RRClass::IN(),
                                        RRType::AAAA(), RRTTL(3600)));
        rrset_aaaa->addRdata(in::AAAA("2001:db8::1234"));

        rrset_rrsig = RRsetPtr(new RRset(test_name, RRClass::IN(),
                                         RRType::RRSIG(), RRTTL(3600)));
        rrset_rrsig->addRdata(generic::RRSIG("AAAA 5 3 7200 20100322084538 "
                                             "20100220084538 1 example.com. "
                                             "FAKEFAKEFAKEFAKE"));
        rrset_aaaa->addRRsig(rrset_rrsig);
    }

    const Name test_name;
    RRsetPtr rrset_a;           // A RRset with two RDATAs
    RRsetPtr rrset_aaaa;        // AAAA RRset with one RDATA with RRSIG
    RRsetPtr rrset_rrsig;       // RRSIG for the AAAA RRset
};

TEST_F(RRsetRRSIGTest, getRRsig) {
    RRsetPtr sp = rrset_a->getRRsig();
    EXPECT_EQ(static_cast<void*>(NULL), sp.get());

    sp = rrset_aaaa->getRRsig();
    EXPECT_NE(static_cast<void*>(NULL), sp.get());
}

TEST_F(RRsetRRSIGTest, addRRsig) {
    RRsetPtr sp = rrset_a->getRRsig();
    EXPECT_EQ(static_cast<void*>(NULL), sp.get());

    rrset_rrsig = RRsetPtr(new RRset(test_name, RRClass::IN(),
                                     RRType::RRSIG(), RRTTL(3600)));
    // one signature algorithm (5 = RSA/SHA-1)
    rrset_rrsig->addRdata(generic::RRSIG("A 5 3 3600 "
                                         "20000101000000 20000201000000 "
                                         "12345 example.com. FAKEFAKEFAKE"));
    // another signature algorithm (3 = DSA/SHA-1)
    rrset_rrsig->addRdata(generic::RRSIG("A 3 3 3600 "
                                         "20000101000000 20000201000000 "
                                         "12345 example.com. FAKEFAKEFAKE"));
    rrset_a->addRRsig(rrset_rrsig);

    sp = rrset_a->getRRsig();
    EXPECT_NE(static_cast<void*>(NULL), sp.get());
    EXPECT_EQ(2, sp->getRdataCount());

    // add to existing RRSIG
    rrset_rrsig = RRsetPtr(new RRset(test_name, RRClass::IN(),
                                     RRType::RRSIG(), RRTTL(3600)));
    // another signature algorithm (4 = ECC)
    rrset_rrsig->addRdata(generic::RRSIG("A 4 3 3600 "
                                         "20000101000000 20000201000000 "
                                         "12345 example.com. FAKEFAKEFAKE"));
    rrset_a->addRRsig(rrset_rrsig);
    EXPECT_EQ(3, sp->getRdataCount());
}

TEST_F(RRsetRRSIGTest, getRRsigDataCount) {
    EXPECT_EQ(1, rrset_aaaa->getRRsigDataCount());
    EXPECT_EQ(0, rrset_a->getRRsigDataCount());

    rrset_rrsig = RRsetPtr(new RRset(test_name, RRClass::IN(),
                                     RRType::RRSIG(), RRTTL(3600)));
    // one signature algorithm (5 = RSA/SHA-1)
    rrset_rrsig->addRdata(generic::RRSIG("A 5 3 3600 "
                                         "20000101000000 20000201000000 "
                                         "12345 example.com. FAKEFAKEFAKE"));
    // another signature algorithm (3 = DSA/SHA-1)
    rrset_rrsig->addRdata(generic::RRSIG("A 3 3 3600 "
                                         "20000101000000 20000201000000 "
                                         "12345 example.com. FAKEFAKEFAKE"));
    rrset_a->addRRsig(rrset_rrsig);
    EXPECT_EQ(2, rrset_a->getRRsigDataCount());

    rrset_a->removeRRsig();
    EXPECT_EQ(0, rrset_a->getRRsigDataCount());
}

TEST_F(RRsetRRSIGTest, toText) {
    // toText() should also return the associated RRSIG.
    EXPECT_EQ("test.example.com. 3600 IN AAAA 2001:db8::1234\n"
              "test.example.com. 3600 IN RRSIG AAAA 5 3 7200 "
              "20100322084538 20100220084538 1 example.com. FAKEFAKEFAKEFAKE\n",
              rrset_aaaa->toText());
}

TEST_F(RRsetRRSIGTest, getLength) {
    // A RR
    // test.example.com = 1 + 4 + 1 + 7 + 1 + 3 + 1 = 18 octets
    // TYPE field = 2 octets
    // CLASS field = 2 octets
    // TTL field = 4 octets
    // RDLENGTH field = 2 octets
    // A RDATA = 4 octets
    // Total = 18 + 2 + 2 + 4 + 2 + 4 = 32 octets

    // 2 A RRs
    EXPECT_EQ(32 + 32, rrset_a->getLength());

    // RRSIG
    // test.example.com = 1 + 4 + 1 + 7 + 1 + 3 + 1 = 18 octets
    // TYPE field = 2 octets
    // CLASS field = 2 octets
    // TTL field = 4 octets
    // RDLENGTH field = 2 octets
    // RRSIG RDATA = 40 octets
    // Total = 18 + 2 + 2 + 4 + 2 + 40 = 68 octets
    RRsetPtr my_rrsig(new RRset(test_name, RRClass::IN(),
                                RRType::RRSIG(), RRTTL(3600)));
    my_rrsig->addRdata(generic::RRSIG("A 4 3 3600 "
                                      "20000101000000 20000201000000 "
                                      "12345 example.com. FAKEFAKEFAKE"));
    EXPECT_EQ(68, my_rrsig->getLength());

    // RRset with attached RRSIG
    rrset_a->addRRsig(my_rrsig);

    EXPECT_EQ(32 + 32 + 68, rrset_a->getLength());
}
}
