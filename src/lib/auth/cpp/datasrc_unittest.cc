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

// $Id$

#include <stdint.h>

#include <iostream>
#include <vector>
#include <string>

#include <gtest/gtest.h>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/question.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>

#include "unittest_util.h"
#include "unittest_ds.h"

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::auth;

namespace {
class DataSrcTest : public ::testing::Test {
protected:
    DataSrcTest() : obuffer(0), renderer(obuffer), msg(Message::PARSE)
    {}
    TestDataSrc ds;
    OutputBuffer obuffer;
    MessageRenderer renderer;
    Message msg;
    static void msgFromFile(Message& message, const char* datafile);
};

void
DataSrcTest::msgFromFile(Message& message, const char* datafile)
{
    std::vector<unsigned char> data;
    UnitTestUtil::readWireData(datafile, data);

    InputBuffer buffer(&data[0], data.size());
    message.fromWire(buffer);
}

TEST_F(DataSrcTest, Query) {
    msgFromFile(msg, "testdata/q_www");
    msg.makeResponse();
    msg.setHeaderFlag(MessageFlag::AA());
    msg.setRcode(Rcode::NOERROR());
    Query q = Query(msg, false);
    ds.doQuery(q);
    Message* m = &(q.message());

    EXPECT_EQ(Rcode::NOERROR(), m->getRcode());
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::QR()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::RD()));

    EXPECT_EQ(2, m->getRRCount(Section::ANSWER()));
    EXPECT_EQ(4, m->getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(6, m->getRRCount(Section::ADDITIONAL()));

    RRsetIterator rit = m->beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("192.168.1.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    // XXX: also check ANSWER RRSIG

    rit = m->beginSection(Section::AUTHORITY());
    rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("dns01.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns02.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns03.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = m->beginSection(Section::ADDITIONAL());
    rrset = *rit;
    EXPECT_EQ(Name("dns01.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("192.168.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, NSQuery) {
    msgFromFile(msg, "testdata/q_example_ns");
    msg.makeResponse();
    msg.setHeaderFlag(MessageFlag::AA());
    msg.setRcode(Rcode::NOERROR());
    Query q = Query(msg, false);
    ds.doQuery(q);
    Message* m = &(q.message());

    EXPECT_EQ(Rcode::NOERROR(), m->getRcode());
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::QR()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::RD()));

    EXPECT_EQ(4, m->getRRCount(Section::ANSWER()));
    EXPECT_EQ(0, m->getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(6, m->getRRCount(Section::ADDITIONAL()));

    RRsetIterator rit = m->beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("dns01.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns02.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns03.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, NxRRset) {
    msgFromFile(msg, "testdata/q_example_ptr");
    msg.makeResponse();
    msg.setHeaderFlag(MessageFlag::AA());
    msg.setRcode(Rcode::NOERROR());
    Query q = Query(msg, false);
    ds.doQuery(q);
    Message* m = &(q.message());

    EXPECT_EQ(Rcode::NOERROR(), m->getRcode());
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::QR()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::RD()));

    EXPECT_EQ(0, m->getRRCount(Section::ANSWER()));
    EXPECT_EQ(4, m->getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(0, m->getRRCount(Section::ADDITIONAL()));

    RRsetIterator rit = m->beginSection(Section::AUTHORITY());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::SOA(), rrset->getType());
}

TEST_F(DataSrcTest, Nxdomain) {
    msgFromFile(msg, "testdata/q_glork");
    msg.makeResponse();
    msg.setHeaderFlag(MessageFlag::AA());
    msg.setRcode(Rcode::NOERROR());
    Query q = Query(msg, false);
    ds.doQuery(q);
    Message* m = &(q.message());

    EXPECT_EQ(Rcode::NXDOMAIN(), m->getRcode());
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::QR()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::RD()));

    EXPECT_EQ(0, m->getRRCount(Section::ANSWER()));
    EXPECT_EQ(6, m->getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(0, m->getRRCount(Section::ADDITIONAL()));

    RRsetIterator rit = m->beginSection(Section::AUTHORITY());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::NSEC(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    // XXX: check for other authority section answers
}

TEST_F(DataSrcTest, NxZone) {
    msgFromFile(msg, "testdata/q_spork");
    msg.makeResponse();
    msg.setHeaderFlag(MessageFlag::AA());
    msg.setRcode(Rcode::NOERROR());
    Query q = Query(msg, false);
    ds.doQuery(q);
    Message* m = &(q.message());

    EXPECT_EQ(Rcode::REFUSED(), m->getRcode());
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::QR()));
    EXPECT_FALSE(m->getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::RD()));

}

TEST_F(DataSrcTest, Wildcard) {
    msgFromFile(msg, "testdata/q_wild");
    msg.makeResponse();
    msg.setHeaderFlag(MessageFlag::AA());
    msg.setRcode(Rcode::NOERROR());
    Query q = Query(msg, false);
    ds.doQuery(q);
    Message* m = &(q.message());

    EXPECT_EQ(Rcode::NOERROR(), m->getRcode());
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::QR()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::RD()));

    EXPECT_EQ(2, m->getRRCount(Section::ANSWER()));
    EXPECT_EQ(4, m->getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(6, m->getRRCount(Section::ADDITIONAL()));

    RRsetIterator rit = m->beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.wild.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("192.168.3.2", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = m->beginSection(Section::AUTHORITY());
    rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("dns01.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns02.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns03.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = m->beginSection(Section::ADDITIONAL());
    rrset = *rit;
    EXPECT_EQ(Name("dns01.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("192.168.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, AuthDelegation) {
    msgFromFile(msg, "testdata/q_sql1");
    msg.makeResponse();
    msg.setHeaderFlag(MessageFlag::AA());
    msg.setRcode(Rcode::NOERROR());
    Query q = Query(msg, false);
    ds.doQuery(q);
    Message* m = &(q.message());

    EXPECT_EQ(Rcode::NOERROR(), m->getRcode());
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::QR()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::RD()));

    EXPECT_EQ(2, m->getRRCount(Section::ANSWER()));
    EXPECT_EQ(4, m->getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(6, m->getRRCount(Section::ADDITIONAL()));

    RRsetIterator rit = m->beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.sql1.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("192.168.2.2", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = m->beginSection(Section::AUTHORITY());
    rrset = *rit;
    EXPECT_EQ(Name("sql1.example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("dns01.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns02.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns03.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = m->beginSection(Section::ADDITIONAL());
    rrset = *rit;
    EXPECT_EQ(Name("dns01.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("192.168.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, Dname) {
    msgFromFile(msg, "testdata/q_dname");
    msg.makeResponse();
    msg.setHeaderFlag(MessageFlag::AA());
    msg.setRcode(Rcode::NOERROR());
    Query q = Query(msg, false);
    ds.doQuery(q);
    Message* m = &(q.message());

    EXPECT_EQ(Rcode::NOERROR(), m->getRcode());
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::QR()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::RD()));

    EXPECT_EQ(5, m->getRRCount(Section::ANSWER()));
    EXPECT_EQ(4, m->getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(6, m->getRRCount(Section::ADDITIONAL()));

    RRsetIterator rit = m->beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("dname.example.com"), rrset->getName());
    EXPECT_EQ(RRType::DNAME(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("sql1.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    // XXX: check CNAME and A record too

    rit = m->beginSection(Section::AUTHORITY());
    rrset = *rit;
    EXPECT_EQ(Name("sql1.example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("dns01.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns02.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns03.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = m->beginSection(Section::ADDITIONAL());
    rrset = *rit;
    EXPECT_EQ(Name("dns01.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("192.168.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, Cname) {
    msgFromFile(msg, "testdata/q_cname");
    msg.makeResponse();
    msg.setHeaderFlag(MessageFlag::AA());
    msg.setRcode(Rcode::NOERROR());
    Query q = Query(msg, false);
    ds.doQuery(q);
    Message* m = &(q.message());

    EXPECT_EQ(Rcode::NOERROR(), m->getRcode());
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::QR()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::RD()));

    EXPECT_EQ(2, m->getRRCount(Section::ANSWER()));
    EXPECT_EQ(0, m->getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(0, m->getRRCount(Section::ADDITIONAL()));

    RRsetIterator rit = m->beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("foo.example.com"), rrset->getName());
    EXPECT_EQ(RRType::CNAME(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("cnametest.flame.org.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, CnameInt) {
    msgFromFile(msg, "testdata/q_cname_int");
    msg.makeResponse();
    msg.setHeaderFlag(MessageFlag::AA());
    msg.setRcode(Rcode::NOERROR());
    Query q = Query(msg, false);
    ds.doQuery(q);
    Message* m = &(q.message());

    EXPECT_EQ(Rcode::NOERROR(), m->getRcode());
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::QR()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::RD()));

    EXPECT_EQ(4, m->getRRCount(Section::ANSWER()));
    EXPECT_EQ(4, m->getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(6, m->getRRCount(Section::ADDITIONAL()));

    RRsetIterator rit = m->beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("cname-int.example.com"), rrset->getName());
    EXPECT_EQ(RRType::CNAME(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("www.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    // XXX: check a record as well

    rit = m->beginSection(Section::AUTHORITY());
    rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
}

TEST_F(DataSrcTest, CnameExt) {
    msgFromFile(msg, "testdata/q_cname_ext");
    msg.makeResponse();
    msg.setHeaderFlag(MessageFlag::AA());
    msg.setRcode(Rcode::NOERROR());
    Query q = Query(msg, false);
    ds.doQuery(q);
    Message* m = &(q.message());

    EXPECT_EQ(Rcode::NOERROR(), m->getRcode());
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::QR()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::RD()));

    EXPECT_EQ(4, m->getRRCount(Section::ANSWER()));
    EXPECT_EQ(4, m->getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(6, m->getRRCount(Section::ADDITIONAL()));

    RRsetIterator rit = m->beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("cname-ext.example.com"), rrset->getName());
    EXPECT_EQ(RRType::CNAME(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("www.sql1.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = m->beginSection(Section::AUTHORITY());
    rrset = *rit;
    EXPECT_EQ(Name("sql1.example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
}

TEST_F(DataSrcTest, Delegation) {
    msgFromFile(msg, "testdata/q_subzone");
    msg.makeResponse();
    msg.setHeaderFlag(MessageFlag::AA());
    msg.setRcode(Rcode::NOERROR());
    Query q = Query(msg, false);
    ds.doQuery(q);
    Message* m = &(q.message());

    EXPECT_EQ(Rcode::NOERROR(), m->getRcode());
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::QR()));
    EXPECT_FALSE(m->getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::RD()));

    EXPECT_EQ(0, m->getRRCount(Section::ANSWER()));
    EXPECT_EQ(5, m->getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(2, m->getRRCount(Section::ADDITIONAL()));

    RRsetIterator rit = m->beginSection(Section::AUTHORITY());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("subzone.example.com."), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("ns1.subzone.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_FALSE(it->isLast());

    rit = m->beginSection(Section::ADDITIONAL());
    rrset = *rit;
    EXPECT_EQ(Name("ns1.subzone.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("192.168.3.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, DS) {
    msgFromFile(msg, "testdata/q_subzone_ds");
    msg.makeResponse();
    msg.setHeaderFlag(MessageFlag::AA());
    msg.setRcode(Rcode::NOERROR());
    Query q = Query(msg, false);
    ds.doQuery(q);
    Message* m = &(q.message());

    EXPECT_EQ(Rcode::NOERROR(), m->getRcode());
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::QR()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(m->getHeaderFlag(MessageFlag::RD()));

    EXPECT_EQ(3, m->getRRCount(Section::ANSWER()));
    EXPECT_EQ(4, m->getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(6, m->getRRCount(Section::ADDITIONAL()));

    RRsetIterator rit = m->beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("subzone.example.com."), rrset->getName());
    EXPECT_EQ(RRType::DS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    rit = m->beginSection(Section::AUTHORITY());
    rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("dns01.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns02.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns03.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

}

