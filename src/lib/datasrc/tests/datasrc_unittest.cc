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
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>

#include <cc/data.h>

#include <datasrc/query.h>
#include <datasrc/sqlite3_datasrc.h>
#include <datasrc/static_datasrc.h>

#include <dns/tests/unittest_util.h>
#include <datasrc/tests/test_datasrc.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc;
using namespace isc::data;

namespace {
ConstElementPtr SQLITE_DBFILE_EXAMPLE = Element::fromJSON(
    "{ \"database_file\": \"" TEST_DATA_DIR "/example.org.sqlite3\"}");

class DataSrcTest : public ::testing::Test {
protected:
    DataSrcTest() : obuffer(0), renderer(obuffer), msg(Message::PARSE) {
        DataSrcPtr sql3_source = DataSrcPtr(new Sqlite3DataSrc); 
        sql3_source->init(SQLITE_DBFILE_EXAMPLE);
        DataSrcPtr test_source = DataSrcPtr(new TestDataSrc);
        test_source->init();
        DataSrcPtr static_source = DataSrcPtr(new StaticDataSrc);
        meta_source.addDataSrc(test_source);
        meta_source.addDataSrc(sql3_source);
        meta_source.addDataSrc(static_source);
    }
    void QueryCommon(const RRClass& qclass);
    void createAndProcessQuery(const Name& qname, const RRClass& qclass,
                               const RRType& qtype);

    HotCache cache;
    MetaDataSrc meta_source;
    OutputBuffer obuffer;
    MessageRenderer renderer;
    Message msg;
};

void
performQuery(DataSrc& data_source, HotCache& cache, Message& message) {
    message.setHeaderFlag(MessageFlag::AA());
    message.setRcode(Rcode::NOERROR());
    Query q(message, cache, true);
    data_source.doQuery(q);
}

void
DataSrcTest::createAndProcessQuery(const Name& qname, const RRClass& qclass,
                                   const RRType& qtype)
{
    msg.makeResponse();
    msg.setOpcode(Opcode::QUERY());
    msg.addQuestion(Question(qname, qclass, qtype));
    msg.setHeaderFlag(MessageFlag::RD());
    performQuery(meta_source, cache, msg);
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

void
DataSrcTest::QueryCommon(const RRClass& qclass) {
    createAndProcessQuery(Name("www.example.com"), qclass, RRType::A());

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 2, 4, 6);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
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
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, Query) {
    QueryCommon(RRClass::IN());
}

// Query class doesn't match any of the data source classes.  The result
// should be the same as "NxZone".
TEST_F(DataSrcTest, QueryClassMismatch) {
    createAndProcessQuery(Name("www.example.com"), RRClass::CH(), RRType::A());
    headerCheck(msg, Rcode::REFUSED(), true, false, true, 0, 0, 0);

    EXPECT_EQ(Rcode::REFUSED(), msg.getRcode());
    EXPECT_TRUE(msg.getHeaderFlag(MessageFlag::QR()));
    EXPECT_FALSE(msg.getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(msg.getHeaderFlag(MessageFlag::RD()));
}

// Query class of any should match the first data source.
TEST_F(DataSrcTest, QueryClassAny) {
    QueryCommon(RRClass::ANY());
}

TEST_F(DataSrcTest, NSQuery) {
    createAndProcessQuery(Name("example.com"), RRClass::IN(),
                          RRType::NS());
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

// Make sure two successive queries have the same result
TEST_F(DataSrcTest, DuplicateQuery) {
    createAndProcessQuery(Name("example.com"), RRClass::IN(),
                          RRType::NS());
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

    msg.clear(Message::PARSE);
    createAndProcessQuery(Name("example.com"), RRClass::IN(),
                          RRType::NS());
    headerCheck(msg, Rcode::NOERROR(), true, true, true, 4, 0, 6);

    rit = msg.beginSection(Section::ANSWER());
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
}

TEST_F(DataSrcTest, DNSKEYQuery) {
    createAndProcessQuery(Name("example.com"), RRClass::IN(),
                          RRType::DNSKEY());
    headerCheck(msg, Rcode::NOERROR(), true, true, true, 4, 4, 6);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::DNSKEY(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
}

// Repeat the previous query to check that cache is working correctly.
// We query for a record at a zone cut to ensure the REFERRAL flag doesn't
// cause incorrect behavior.
TEST_F(DataSrcTest, DNSKEYDuplicateQuery) {
    createAndProcessQuery(Name("example.com"), RRClass::IN(),
                          RRType::DNSKEY());
    headerCheck(msg, Rcode::NOERROR(), true, true, true, 4, 4, 6);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::DNSKEY(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    msg.clear(Message::PARSE);
    createAndProcessQuery(Name("example.com"), RRClass::IN(),
                          RRType::DNSKEY());
    rit = msg.beginSection(Section::ANSWER());
    rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::DNSKEY(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
}

TEST_F(DataSrcTest, NxRRset) {
    createAndProcessQuery(Name("example.com"), RRClass::IN(),
                          RRType::PTR());

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 0, 4, 0);

    RRsetIterator rit = msg.beginSection(Section::AUTHORITY());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::SOA(), rrset->getType());
}

TEST_F(DataSrcTest, Nxdomain) {
    createAndProcessQuery(Name("glork.example.com"), RRClass::IN(),
                          RRType::A());

    headerCheck(msg, Rcode::NXDOMAIN(), true, true, true, 0, 6, 0);

    RRsetIterator rit = msg.beginSection(Section::AUTHORITY());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::SOA(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    // XXX: check for other authority section answers
}

TEST_F(DataSrcTest, NxZone) {
    createAndProcessQuery(Name("spork.example"), RRClass::IN(),
                          RRType::A());

    headerCheck(msg, Rcode::REFUSED(), true, false, true, 0, 0, 0);

    EXPECT_EQ(Rcode::REFUSED(), msg.getRcode());
    EXPECT_TRUE(msg.getHeaderFlag(MessageFlag::QR()));
    EXPECT_FALSE(msg.getHeaderFlag(MessageFlag::AA()));
    EXPECT_TRUE(msg.getHeaderFlag(MessageFlag::RD()));
}

TEST_F(DataSrcTest, Wildcard) {
    createAndProcessQuery(Name("www.wild.example.com"), RRClass::IN(),
                          RRType::A());

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 2, 6, 6);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.wild.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("192.0.2.2", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Section::AUTHORITY());
    rrset = *rit;
    EXPECT_EQ(Name("*.wild.example.com"), rrset->getName());
    EXPECT_EQ(RRType::NSEC(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    ++rit;
    ++rit;

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
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, WildcardNodata) {
    // Check that a query for a data type not covered by the wildcard
    // returns NOERROR
    createAndProcessQuery(Name("www.wild.example.com"), RRClass::IN(),
                          RRType::AAAA());
    headerCheck(msg, Rcode::NOERROR(), true, true, true, 0, 2, 0);
}

TEST_F(DataSrcTest, DISABLED_WildcardAgainstMultiLabel) {
    // this qname shouldn't match *.wild.com.com (because * can only match
    // a single label), and it should result in NXDOMAIN.
    createAndProcessQuery(Name("www.xxx.wild.example.com"), RRClass::IN(),
                          RRType::A());
    headerCheck(msg, Rcode::NXDOMAIN(), true, true, true, 0, 1, 0);
}

TEST_F(DataSrcTest, WildcardCname) {
    // Check that wildcard answers containing CNAMES are followed
    // correctly
    createAndProcessQuery(Name("www.wild2.example.com"), RRClass::IN(),
                          RRType::A());

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 4, 6, 6);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.wild2.example.com"), rrset->getName());
    EXPECT_EQ(RRType::CNAME(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("www.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    ++rit;
    ++rit;
    rrset = *rit;
    EXPECT_EQ(Name("www.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Section::AUTHORITY());
    rrset = *rit;
    EXPECT_EQ(Name("*.wild2.example.com"), rrset->getName());
    EXPECT_EQ(RRType::NSEC(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    ++rit;
    ++rit;

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
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, WildcardCnameNodata) {
    // A wildcard containing a CNAME whose target does not include
    // data of this type.
    createAndProcessQuery(Name("www.wild2.example.com"), RRClass::IN(),
                          RRType::AAAA());
    headerCheck(msg, Rcode::NOERROR(), true, true, true, 2, 4, 0);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.wild2.example.com"), rrset->getName());
    EXPECT_EQ(RRType::CNAME(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("www.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Section::AUTHORITY());
    rrset = *rit;
    EXPECT_EQ(Name("*.wild2.example.com"), rrset->getName());
    EXPECT_EQ(RRType::NSEC(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    ++rit;
    ++rit;

    rrset = *rit;
    EXPECT_EQ(Name("www.example.com"), rrset->getName());
    EXPECT_EQ(RRType::NSEC(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
}

TEST_F(DataSrcTest, WildcardCnameNxdomain) {
    // A wildcard containing a CNAME whose target does not exist
    createAndProcessQuery(Name("www.wild3.example.com"), RRClass::IN(),
                          RRType::A());
    headerCheck(msg, Rcode::NOERROR(), true, true, true, 2, 6, 0);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.wild3.example.com"), rrset->getName());
    EXPECT_EQ(RRType::CNAME(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("spork.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Section::AUTHORITY());
    rrset = *rit;
    EXPECT_EQ(Name("*.wild3.example.com"), rrset->getName());
    EXPECT_EQ(RRType::NSEC(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    ++rit;
    ++rit;

    rrset = *rit;
    EXPECT_EQ(Name("foo.example.com"), rrset->getName());
    EXPECT_EQ(RRType::NSEC(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    ++rit;
    ++rit;

    rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::NSEC(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
}
TEST_F(DataSrcTest, AuthDelegation) {
    createAndProcessQuery(Name("www.sql1.example.com"), RRClass::IN(),
                          RRType::A());

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 2, 4, 6);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.sql1.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ("192.0.2.2", it->getCurrent().toText());
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
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, Dname) {
    createAndProcessQuery(Name("www.dname.example.com"), RRClass::IN(),
                          RRType::A());

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
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, DnameExact) {
    // The example.org test zone has a DNAME RR for dname2.foo.example.org.
    // A query for that name with a different RR type than DNAME shouldn't
    // confuse delegation processing.
    createAndProcessQuery(Name("dname2.foo.example.org"), RRClass::IN(),
                          RRType::A());
    headerCheck(msg, Rcode::NOERROR(), true, true, true, 0, 1, 0);
}

TEST_F(DataSrcTest, Cname) {
    createAndProcessQuery(Name("foo.example.com"), RRClass::IN(),
                          RRType::A());

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
    createAndProcessQuery(Name("cname-int.example.com"), RRClass::IN(),
                          RRType::A());

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
    createAndProcessQuery(Name("cname-ext.example.com"), RRClass::IN(),
                          RRType::A());

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
    createAndProcessQuery(Name("www.subzone.example.com"), RRClass::IN(),
                          RRType::A());

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
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, NSDelegation) {
    createAndProcessQuery(Name("subzone.example.com"), RRClass::IN(),
                          RRType::NS());

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
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, ANYZonecut) {
    // An ANY query at a zone cut should behave the same as any other
    // delegation
    createAndProcessQuery(Name("subzone.example.com"), RRClass::IN(),
                          RRType::ANY());
}

TEST_F(DataSrcTest, NSECZonecut) {
    createAndProcessQuery(Name("subzone.example.com"), RRClass::IN(),
                          RRType::NSEC());

    headerCheck(msg, Rcode::NOERROR(), true, true, true, 2, 4, 6);

    RRsetIterator rit = msg.beginSection(Section::ANSWER());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("subzone.example.com."), rrset->getName());
    EXPECT_EQ(RRType::NSEC(), rrset->getType());
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

TEST_F(DataSrcTest, DNAMEZonecut) {
    createAndProcessQuery(Name("subzone.example.com"), RRClass::IN(),
                          RRType::DNAME());

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
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, DS) {
    createAndProcessQuery(Name("subzone.example.com"), RRClass::IN(),
                          RRType::DS());

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
    createAndProcessQuery(Name("one.loop.example"), RRClass::IN(),
                          RRType::A());
    EXPECT_EQ(Rcode::NOERROR(), msg.getRcode());

    // one.loop.example points to two.loop.example, which points back
    // to one.loop.example, so there should be exactly two CNAME records
    // in the answer.
    EXPECT_EQ(2, msg.getRRCount(Section::ANSWER()));
}

// NSEC query for the name of a zone cut for non-secure delegation.
// Should return normal referral.
TEST_F(DataSrcTest, NSECZonecutOfNonsecureZone) {
    createAndProcessQuery(Name("sub.example.org"), RRClass::IN(),
                          RRType::NSEC());

    headerCheck(msg, Rcode::NOERROR(), true, false, true, 0, 1, 1);

    RRsetIterator rit = msg.beginSection(Section::AUTHORITY());
    ConstRRsetPtr rrset = *rit;
    EXPECT_EQ(Name("sub.example.org."), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ(createRdata(RRType::NS(), RRClass::IN(),
                          "ns.sub.example.org.")->toText(),
              it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Section::ADDITIONAL());
    rrset = *rit;
    EXPECT_EQ(Name("ns.sub.example.org."), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    it->first();
    EXPECT_EQ(createRdata(RRType::A(), RRClass::IN(), "192.0.2.101")->toText(),
              it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, RootDSQuery) {
    EXPECT_NO_THROW(createAndProcessQuery(Name("."), RRClass::IN(),
                                          RRType::DS()));
    headerCheck(msg, Rcode::REFUSED(), true, false, true, 0, 0, 0);
}

// Non-existent name in the "static" data source.  The purpose of this test
// is to check a corner case behavior when atypical RRClass (CH in this case)
// is specified.
TEST_F(DataSrcTest, StaticNxDomain) {
    createAndProcessQuery(Name("www.version.bind"), RRClass::CH(),
                          RRType::TXT());
    headerCheck(msg, Rcode::NXDOMAIN(), true, true, true, 0, 1, 0);
    RRsetIterator rit = msg.beginSection(Section::AUTHORITY());
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("version.bind"), rrset->getName());
    EXPECT_EQ(RRType::SOA(), rrset->getType());
    EXPECT_EQ(RRClass::CH(), rrset->getClass());
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

TEST_F(DataSrcTest, noNSZone) {
    EXPECT_THROW(createAndProcessQuery(Name("www.nons.example"),
                                       RRClass::IN(), RRType::A()),
                 DataSourceError);
}

TEST_F(DataSrcTest, noNSButDnameZone) {
    EXPECT_THROW(createAndProcessQuery(Name("www.nons-dname.example"),
                                       RRClass::IN(), RRType::A()),
                 DataSourceError);
}

TEST_F(DataSrcTest, noSOAZone) {
    EXPECT_THROW(createAndProcessQuery(Name("notexist.nosoa.example"),
                                       RRClass::IN(), RRType::A()),
                 DataSourceError);
}

// currently fails
TEST_F(DataSrcTest, DISABLED_synthesizedCnameTooLong) {
    // qname has the possible max length (255 octets).  it matches a DNAME,
    // and the synthesized CNAME would exceed the valid length.
    createAndProcessQuery(
        Name("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcde."
             "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcde."
             "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcde."
             "0123456789abcdef0123456789abcdef0123456789a.dname.example.org."),
        RRClass::IN(), RRType::A());
}

// Tests of the DataSrcMatch class start here
class DataSrcMatchTest : public ::testing::Test {
protected:
    DataSrcMatchTest() {
        datasrc1.init();
    }
    // test data source serves example.com/IN.
    TestDataSrc datasrc1;
    // this data source is dummy.  Its content doesn't matter in the tests.
    TestDataSrc datasrc2;
};

TEST_F(DataSrcMatchTest, match) {
    DataSrcMatch match(Name("very.very.long.example.com"), RRClass::IN());
    datasrc1.findClosestEnclosure(match);
    EXPECT_EQ(Name("example.com"), *match.getEnclosingZone());
    EXPECT_EQ(&datasrc1, match.getDataSource());
}

TEST_F(DataSrcMatchTest, matchWithWrongClass) {
    DataSrcMatch match(Name("very.very.long.example.com"), RRClass::CH());
    datasrc1.findClosestEnclosure(match);
    // XXX: some deviant compilers seem to fail to recognize a NULL as a
    // pointer type.  This explicit cast works around such compilers.
    EXPECT_EQ(static_cast<void*>(NULL), match.getEnclosingZone());
    EXPECT_EQ(static_cast<void*>(NULL), match.getDataSource());
}

TEST_F(DataSrcMatchTest, matchWithAnyClass) {
    DataSrcMatch match(Name("very.very.long.example.com"), RRClass::ANY());
    datasrc1.findClosestEnclosure(match);
    EXPECT_EQ(Name("example.com"), *match.getEnclosingZone());
    EXPECT_EQ(&datasrc1, match.getDataSource());
}

TEST_F(DataSrcMatchTest, updateWithWrongClass) {
    DataSrcMatch match(Name("www.example.com"), RRClass::CH());

    EXPECT_EQ(RRClass::IN(), datasrc2.getClass());
    match.update(datasrc2, Name("com"));
    EXPECT_EQ(static_cast<void*>(NULL), match.getEnclosingZone());
    EXPECT_EQ(static_cast<void*>(NULL), match.getDataSource());

    EXPECT_EQ(RRClass::IN(), datasrc1.getClass());
    match.update(datasrc1, Name("example.com"));
    EXPECT_EQ(static_cast<void*>(NULL), match.getEnclosingZone());
    EXPECT_EQ(static_cast<void*>(NULL), match.getDataSource());
}

TEST_F(DataSrcMatchTest, updateAgainstAnyClass) {
    DataSrcMatch match(Name("www.example.com"), RRClass::ANY());
    match.update(datasrc2, Name("com"));
    EXPECT_EQ(Name("com"), *match.getEnclosingZone());
    EXPECT_EQ(&datasrc2, match.getDataSource());

    // the given class for search is ANY, so update should be okay.
    EXPECT_EQ(RRClass::IN(), datasrc1.getClass());
    match.update(datasrc1, Name("example.com"));
    EXPECT_EQ(Name("example.com"), *match.getEnclosingZone());
    EXPECT_EQ(&datasrc1, match.getDataSource());
}

TEST_F(DataSrcMatchTest, updateWithNoMatch) {
    DataSrcMatch match(Name("www.example.com"), RRClass::IN());
    match.update(datasrc1, Name("com"));
    EXPECT_EQ(Name("com"), *match.getEnclosingZone());
    EXPECT_EQ(&datasrc1, match.getDataSource());

    // An attempt of update with a name that doesn't match.  This attempt
    // should be ignored.
    match.update(datasrc2, Name("example.org"));
    EXPECT_EQ(Name("com"), *match.getEnclosingZone());
    EXPECT_EQ(&datasrc1, match.getDataSource());
}

TEST_F(DataSrcMatchTest, initialUpdateWithNoMatch) {
    DataSrcMatch match(Name("www.example.com"), RRClass::IN());

    // An initial attempt of update with a name that doesn't match.
    // Should be ignored.
    match.update(datasrc1, Name("example.org"));
    EXPECT_EQ(static_cast<void*>(NULL), match.getEnclosingZone());
    EXPECT_EQ(static_cast<void*>(NULL), match.getDataSource());
}

TEST_F(DataSrcMatchTest, updateWithShorterMatch) {
    DataSrcMatch match(Name("www.example.com"), RRClass::IN());

    match.update(datasrc1, Name("example.com"));
    EXPECT_EQ(Name("example.com"), *match.getEnclosingZone());
    EXPECT_EQ(&datasrc1, match.getDataSource());

    // An attempt of update with a name that gives a shorter match.
    // This attempt should be ignored.
    match.update(datasrc2, Name("com"));
    EXPECT_EQ(Name("example.com"), *match.getEnclosingZone());
    EXPECT_EQ(&datasrc1, match.getDataSource());
}

}
