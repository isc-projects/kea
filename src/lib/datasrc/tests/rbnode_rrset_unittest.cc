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

#include <stdexcept>

#include <exceptions/exceptions.h>
#include <dns/rdataclass.h>
#include <datasrc/rbnode_rrset.h>
#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>

using isc::UnitTestUtil;

using namespace isc;
using namespace isc::datasrc;
using namespace isc::datasrc::internal;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::testutils;
using namespace isc::util;
using namespace std;

// These tests are very similar to those for RRset - indeed, this file was
// created from those tests.  However, the significant difference in behaviour
// between RRset and RBNodeRRset - that the "set" methods in the latter mostly
// result in exceptions being thrown - preclude use of full type
// parameterisation of the tests.

namespace {
const char* const RRSIG_TXT =
    "A 5 4 43200 20100223214617 20100222214617 8496 isc.org. "
    "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
    "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
    "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
    "f49t+sXKPzbipN9g+s1ZPiIyofc=";

class RBNodeRRsetTest : public ::testing::Test {
protected:
    RBNodeRRsetTest() :
        test_name("test.example.com"),
        test_domain("example.com"),
        test_nsname("ns.example.com"),
        rrset_a(ConstRRsetPtr(new RRset(
                test_name, RRClass::IN(), RRType::A(), RRTTL(3600)))),
        rrset_a_empty(ConstRRsetPtr(new RRset(
                      test_name, RRClass::IN(), RRType::A(), RRTTL(3600)))),
        rrset_ns(ConstRRsetPtr(new RRset(
                 test_domain, RRClass::IN(), RRType::NS(), RRTTL(86400)))),
        rrset_ch_txt(ConstRRsetPtr(new RRset(
                     test_domain, RRClass::CH(), RRType::TXT(), RRTTL(0)))),
        rrset_siga(new RRset(test_name, RRClass::IN(), RRType::RRSIG(),
                   RRTTL(3600)))

    {
        // Add a couple of Rdata elements to the A RRset.  The easiest way to
        // do this is to override the "const" restrictions.  As this is a test,
        // we don't feel too bad about doing so.
        AbstractRRset* a_rrset =
            const_cast<AbstractRRset*>(rrset_a.getUnderlyingRRset().get());
        a_rrset->addRdata(in::A("192.0.2.1"));
        a_rrset->addRdata(in::A("192.0.2.2"));

        // Create the RRSIG corresponding to the rrset_a record.  The RDATA
        // won't match the A record it covers, although it is internally
        // self-consistent.
        AbstractRRset* sig_rrset =
            const_cast<AbstractRRset*>(rrset_siga.get());
        sig_rrset->addRdata(generic::RRSIG(RRSIG_TXT));
    }

    const Name test_name;
    const Name test_domain;
    const Name test_nsname;

    RBNodeRRset rrset_a;
    RBNodeRRset rrset_a_empty;
    const RBNodeRRset rrset_ns;
    const RBNodeRRset rrset_ch_txt;

    ConstRRsetPtr rrset_siga;
};

TEST_F(RBNodeRRsetTest, getRdataCount) {
    EXPECT_EQ(0, rrset_a_empty.getRdataCount());
    EXPECT_EQ(2, rrset_a.getRdataCount());
}

TEST_F(RBNodeRRsetTest, getName) {
    EXPECT_EQ(test_name, rrset_a.getName());
    EXPECT_EQ(test_domain, rrset_ns.getName());
}

TEST_F(RBNodeRRsetTest, getClass) {
    EXPECT_EQ(RRClass("IN"), rrset_a.getClass());
    EXPECT_EQ(RRClass("CH"), rrset_ch_txt.getClass());
}

TEST_F(RBNodeRRsetTest, getType) {
    EXPECT_EQ(RRType("A"), rrset_a.getType());
    EXPECT_EQ(RRType("NS"), rrset_ns.getType());
    EXPECT_EQ(RRType("TXT"), rrset_ch_txt.getType());
}

TEST_F(RBNodeRRsetTest, getTTL) {
    EXPECT_EQ(RRTTL(3600), rrset_a.getTTL());
    EXPECT_EQ(RRTTL(86400), rrset_ns.getTTL());
    EXPECT_EQ(RRTTL(0), rrset_ch_txt.getTTL());
}

TEST_F(RBNodeRRsetTest, setName) {
    EXPECT_THROW(rrset_a.setName(test_nsname), NotImplemented);
}

TEST_F(RBNodeRRsetTest, setTTL) {
    EXPECT_THROW(rrset_a.setTTL(RRTTL(86400)), NotImplemented);
}

TEST_F(RBNodeRRsetTest, toText) {
    EXPECT_EQ("test.example.com. 3600 IN A 192.0.2.1\n"
              "test.example.com. 3600 IN A 192.0.2.2\n",
              rrset_a.toText());

    // toText() cannot be performed for an empty RRset.
    EXPECT_THROW(rrset_a_empty.toText(), EmptyRRset);
}

// Note: although the next two tests are essentially the same and used common
// test code, they use different test data: the MessageRenderer produces
// compressed wire data whereas the OutputBuffer does not.

template <typename T>
void
performToWireTest(T& dataHolder, const RBNodeRRset& rrset,
                  const RBNodeRRset& rrset_empty, const char* testdata)
{
    rrset.toWire(dataHolder);

    std::vector<unsigned char> wiredata;
    UnitTestUtil::readWireData(testdata, wiredata);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, dataHolder.getData(),
                        dataHolder.getLength(), &wiredata[0], wiredata.size());

    // toWire() cannot be performed for an empty RRset.
    dataHolder.clear();
    EXPECT_THROW(rrset_empty.toWire(dataHolder), EmptyRRset);
}

TEST_F(RBNodeRRsetTest, toWireRenderer) {
    MessageRenderer renderer;
    performToWireTest(renderer, rrset_a, rrset_a_empty, "rrset_toWire2");
}

TEST_F(RBNodeRRsetTest, toWireBuffer) {
    OutputBuffer buffer(0);
    performToWireTest(buffer, rrset_a, rrset_a_empty, "rrset_toWire1");
}

TEST_F(RBNodeRRsetTest, addRdata) {
    EXPECT_THROW(rrset_a.addRdata(in::A("192.0.2.3")), NotImplemented);

    // Check the same goes for trying to add the wrong type of data
    EXPECT_THROW(rrset_a.addRdata(generic::NS(test_nsname)), NotImplemented);
}

TEST_F(RBNodeRRsetTest, addRdataPtr) {
    EXPECT_THROW(rrset_a_empty.addRdata(createRdata(rrset_a_empty.getType(),
                                                    rrset_a_empty.getClass(),
                                                    "192.0.2.1")),
                 NotImplemented);
}

TEST_F(RBNodeRRsetTest, getRDataIterator) {
    RdataIteratorPtr it = rrset_a.getRdataIterator();
    for (int i = 0; i < 2; ++i) {
        ASSERT_FALSE(it->isLast());
        ASSERT_EQ(0, it->getCurrent().compare(in::A("192.0.2.1")));

        it->next();
        ASSERT_FALSE(it->isLast());
        ASSERT_EQ(0, it->getCurrent().compare(in::A("192.0.2.2")));

        it->next();
        ASSERT_TRUE(it->isLast());

        // Should be able repeat the iteration by calling first().
        it->first();
    }
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST_F(RBNodeRRsetTest, LeftShiftOperator) {
    ostringstream oss;
    oss << rrset_a;
    EXPECT_EQ("test.example.com. 3600 IN A 192.0.2.1\n"
              "test.example.com. 3600 IN A 192.0.2.2\n", oss.str());
}

// addRRSIG tests.
TEST_F(RBNodeRRsetTest, addRRsigConstRdataPointer) {
    EXPECT_FALSE(rrset_a.getRRsig());
    ConstRdataPtr data = createRdata(rrset_siga->getType(),
                                     rrset_siga->getClass(), RRSIG_TXT);
    rrset_a.addRRsig(data);
    rrsetCheck(rrset_siga, rrset_a.getRRsig());
}

TEST_F(RBNodeRRsetTest, addRRsigRdataPointer) {
    EXPECT_FALSE(rrset_a.getRRsig());
    RdataPtr data = createRdata(rrset_siga->getType(), rrset_siga->getClass(),
                                RRSIG_TXT);
    rrset_a.addRRsig(data);
    rrsetCheck(rrset_siga, rrset_a.getRRsig());
}

TEST_F(RBNodeRRsetTest, addRRsigAbstractRRset) {
    EXPECT_FALSE(rrset_a.getRRsig());
    rrset_a.addRRsig(*(rrset_siga.get()));
    rrsetCheck(rrset_siga, rrset_a.getRRsig());
}

TEST_F(RBNodeRRsetTest, addRRsigConstantRRsetPointer) {
    EXPECT_FALSE(rrset_a.getRRsig());
    rrset_a.addRRsig(rrset_siga);
    rrsetCheck(rrset_siga, rrset_a.getRRsig());
}

TEST_F(RBNodeRRsetTest, addRRsigRRsetPointer) {
    EXPECT_FALSE(rrset_a.getRRsig());
    RRsetPtr rrsig(new RRset(test_name, RRClass::IN(), RRType::RRSIG(),
                   RRTTL(3600)));
    rrsig->addRdata(generic::RRSIG(RRSIG_TXT));
    rrset_a.addRRsig(rrsig);
    rrsetCheck(rrset_siga, rrset_a.getRRsig());
}

TEST_F(RBNodeRRsetTest, removeRRsig) {
    EXPECT_FALSE(rrset_a.getRRsig());
    rrset_a.addRRsig(*(rrset_siga.get()));
    EXPECT_TRUE(rrset_a.getRRsig());
    rrset_a.removeRRsig();
    EXPECT_FALSE(rrset_a.getRRsig());
}

}   // Anonymous namespace
