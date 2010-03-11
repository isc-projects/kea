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

#include <auth/query.h>
#include "unittest_util.h"
#include "test_datasrc.h"

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::auth;

namespace {
TestDataSrc ds;

class DataSrcTest : public ::testing::Test {
protected:
    DataSrcTest() : obuffer(0), renderer(obuffer), msg(Message::PARSE) {
        ds.init();
    }
    OutputBuffer obuffer;
    MessageRenderer renderer;
    Message msg;
};

void
performQuery(Message& message) {
    message.setHeaderFlag(MessageFlag::AA());
    message.setRcode(Rcode::NOERROR());
    Query q(message, true);
    ds.doQuery(q);
}

void
readAndProcessQuery(Message& message, const char* datafile) {
    std::vector<unsigned char> data;
    UnitTestUtil::readWireData(datafile, data);

    InputBuffer buffer(&data[0], data.size());
    message.fromWire(buffer);

    message.makeResponse();
    performQuery(message);
}

void
createAndProcessQuery(Message& message, const Name& qname,
                      const RRClass& qclass, const RRType& qtype)
{
    message.makeResponse();
    message.setOpcode(Opcode::QUERY());
    message.addQuestion(Question(qname, qclass, qtype));
    message.setHeaderFlag(MessageFlag::RD());
    performQuery(message);
}

void
headerCheck(const Message& message, const Rcode& rcode, const bool qrflag,
            const bool aaflag, const bool rdflag, const unsigned int ancount,
            const unsigned int nscount, const unsigned int arcount)
{
    EXPECT_EQ(rcode, message.getRcode());
    EXPECT_EQ(qrflag, message.getHeaderFlag(MessageFlag::QR()));
    EXPECT_EQ(aaflag, message.getHeaderFlag(MessageFlag::AA()));
    EXPECT_EQ(rdflag, message.getHeaderFlag(MessageFlag::RD()));

    EXPECT_EQ(ancount, message.getRRCount(Section::ANSWER()));
    EXPECT_EQ(nscount, message.getRRCount(Section::AUTHORITY()));
    EXPECT_EQ(arcount, message.getRRCount(Section::ADDITIONAL()));
    
}

TEST_F(DataSrcTest, Query) {
    readAndProcessQuery(msg, "testdata/q_www");

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 2, 4, 6);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
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

    rit = msg.beginSection(Section::AUTHORITY());
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

    rit = msg.beginSection(Section::ADDITIONAL());
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
    readAndProcessQuery(msg, "testdata/q_example_ns");

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 4, 0, 6);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
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
    readAndProcessQuery(msg, "testdata/q_example_ptr");

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 0, 4, 0);

    RRsetIterator rit = msg.beginSection(Section::AUTHORITY());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::SOA(), rrset->getType());
}

TEST_F(DataSrcTest, Nxdomain) {
    readAndProcessQuery(msg, "testdata/q_glork");

    headerCheck(msg, Rcode::NXDOMAIN(), true, true, true, 0, 6, 0);

    RRsetIterator rit = msg.beginSection(Section::AUTHORITY());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::SOA(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    // XXX: check for other authority section answers
}

TEST_F(DataSrcTest, NxZone) {
    readAndProcessQuery(msg, "testdata/q_spork");

    headerCheck(msg, Rcode::REFUSED(), true, false, true, 0, 0, 0);

    EXPECT_EQ(Rcode::REFUSED(), msg.getRcode());
    EXPECT_TRUE(msg.getHeaderFlag(MessageFlag::QR()));
    EXPECT_FALSE(msg.getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(msg.getHeaderFlag(MessageFlag::RD()));

}

TEST_F(DataSrcTest, Wildcard) {
    readAndProcessQuery(msg, "testdata/q_wild");

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 2, 4, 6);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.wild.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("192.168.3.2", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Section::AUTHORITY());
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

    rit = msg.beginSection(Section::ADDITIONAL());
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

TEST_F(DataSrcTest, WildcardNodata) {

    // Check that a query for a data type not covered by the wildcard
    // returns NOERROR
    readAndProcessQuery(msg, "testdata/q_wild2");
    headerCheck(msg, Rcode::NOERROR(), true, true, true, 0, 2, 0);
}

TEST_F(DataSrcTest, AuthDelegation) {
    readAndProcessQuery(msg, "testdata/q_sql1");

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 2, 4, 6);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.sql1.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("192.168.2.2", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Section::AUTHORITY());
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

    rit = msg.beginSection(Section::ADDITIONAL());
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
    readAndProcessQuery(msg, "testdata/q_dname");

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 5, 4, 6);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
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

    rit = msg.beginSection(Section::AUTHORITY());
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

    rit = msg.beginSection(Section::ADDITIONAL());
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
    readAndProcessQuery(msg, "testdata/q_cname");

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 2, 0, 0);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
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
    readAndProcessQuery(msg, "testdata/q_cname_int");

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 4, 4, 6);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
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

    rit = msg.beginSection(Section::AUTHORITY());
    rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
}

TEST_F(DataSrcTest, CnameExt) {
    readAndProcessQuery(msg, "testdata/q_cname_ext");

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 4, 4, 6);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("cname-ext.example.com"), rrset->getName());
    EXPECT_EQ(RRType::CNAME(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("www.sql1.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Section::AUTHORITY());
    rrset = *rit;
    EXPECT_EQ(Name("sql1.example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
}

TEST_F(DataSrcTest, Delegation) {
    readAndProcessQuery(msg, "testdata/q_subzone");

    headerCheck(msg, Rcode::NOERROR(), true, false, true, 0, 5, 2);

    RRsetIterator rit = msg.beginSection(Section::AUTHORITY());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("subzone.example.com."), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("ns1.subzone.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_FALSE(it->isLast());

    rit = msg.beginSection(Section::ADDITIONAL());
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
    readAndProcessQuery(msg, "testdata/q_subzone_ds");

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 3, 4, 6);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("subzone.example.com."), rrset->getName());
    EXPECT_EQ(RRType::DS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    rit = msg.beginSection(Section::AUTHORITY());
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

TEST_F(DataSrcTest, CNAMELoop) {
    createAndProcessQuery(msg, Name("loop1.example.com"), RRClass::IN(),
                          RRType::A());
}

TEST_F(DataSrcTest, Nsec3Hash) {
    vector<uint8_t> salt;
    salt.push_back(0xfe);
    salt.push_back(0xed);
    salt.push_back(0xab);
    salt.push_back(0xee);
    Nsec3Param nsec3(1, 0, 10, salt);
    EXPECT_EQ("VIR9KJAPN2FHRLS6EP0JBQ89MBLUE296", nsec3.getHash(Name("test1")));
    EXPECT_EQ("FHA27EURONFH5640SFJQ8MJAKMCVB7UJ", nsec3.getHash(Name("test2")));
    EXPECT_EQ("A4M93LR7A60IDDQMO6TCVUPCC60CU38A", nsec3.getHash(Name("test3")));
}

TEST_F(DataSrcTest, AddRemoveDataSrc) {
    MetaDataSrc ds;
    ConstDataSrcPtr tsp = ConstDataSrcPtr(new TestDataSrc);
    EXPECT_EQ(0, ds.dataSrcCount());
    ds.addDataSrc(tsp);
    EXPECT_EQ(1, ds.dataSrcCount());
    ds.removeDataSrc(tsp);
    EXPECT_EQ(0, ds.dataSrcCount());
}
}

