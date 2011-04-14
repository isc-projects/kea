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

#include <stdint.h>

#include <iostream>
#include <vector>
#include <string>

#include <gtest/gtest.h>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/question.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>

#include <cc/data.h>

#include <datasrc/query.h>
#include <datasrc/sqlite3_datasrc.h>
#include <datasrc/static_datasrc.h>

#include <testutils/dnsmessage_test.h>
#include <dns/tests/unittest_util.h>
#include <datasrc/tests/test_datasrc.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc;
using namespace isc::data;
using namespace isc::testutils;

namespace {
ConstElementPtr SQLITE_DBFILE_EXAMPLE = Element::fromJSON(
    "{ \"database_file\": \"" TEST_DATA_DIR "/example.org.sqlite3\"}");

class DataSrcTest : public ::testing::Test {
protected:
    DataSrcTest() : obuffer(0), renderer(obuffer), msg(Message::PARSE),
                    opcodeval(Opcode::QUERY().getCode()), qid(0)
    {
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
                               const RRType& qtype, bool need_dnssec);

    HotCache cache;
    MetaDataSrc meta_source;
    OutputBuffer obuffer;
    MessageRenderer renderer;
    Message msg;
    const uint16_t opcodeval;
    qid_t qid;
};

void
performQuery(DataSrc& data_source, HotCache& cache, Message& message,
             bool need_dnssec = true)
{
    message.setHeaderFlag(Message::HEADERFLAG_AA);
    message.setRcode(Rcode::NOERROR());
    Query q(message, cache, need_dnssec);
    data_source.doQuery(q);
}

void
DataSrcTest::createAndProcessQuery(const Name& qname, const RRClass& qclass,
                                   const RRType& qtype,
                                   bool need_dnssec = true)
{
    msg.makeResponse();
    msg.setOpcode(Opcode::QUERY());
    msg.addQuestion(Question(qname, qclass, qtype));
    msg.setHeaderFlag(Message::HEADERFLAG_RD);
    qid = msg.getQid();
    performQuery(meta_source, cache, msg, need_dnssec);
}

void
DataSrcTest::QueryCommon(const RRClass& qclass) {
    createAndProcessQuery(Name("www.example.com"), qclass, RRType::A());

    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 2, 4, 6);

    RRsetIterator rit = msg.beginSection(Message::SECTION_ANSWER);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    // XXX: also check ANSWER RRSIG

    rit = msg.beginSection(Message::SECTION_AUTHORITY);
    rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    EXPECT_EQ("dns01.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns02.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns03.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Message::SECTION_ADDITIONAL);
    rrset = *rit;
    EXPECT_EQ(Name("dns01.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
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
    headerCheck(msg, qid, Rcode::REFUSED(), opcodeval, QR_FLAG | RD_FLAG,
                1, 0, 0, 0);
}

// Query class of any should match the first data source.
TEST_F(DataSrcTest, QueryClassAny) {
    QueryCommon(RRClass::ANY());
}

TEST_F(DataSrcTest, queryClassAnyNegative) {
    // There was a bug where Class ANY query triggered a crash due to NULL
    // pointer dereference.  This test checks that condition.

    // NXDOMAIN case
    createAndProcessQuery(Name("notexistent.example.com"), RRClass::ANY(),
                          RRType::A());
    headerCheck(msg, qid, Rcode::NXDOMAIN(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 0, 6, 0);

    // NXRRSET case
    msg.clear(Message::PARSE);
    createAndProcessQuery(Name("www.example.com"), RRClass::ANY(),
                          RRType::TXT());
    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 0, 4, 0);
}

TEST_F(DataSrcTest, queryClassAnyDNAME) {
    // Class ANY query that would match a DNAME.  Everything including the
    // synthesized CNAME should be the same as the response to class IN query.
    createAndProcessQuery(Name("www.dname.example.com"), RRClass::ANY(),
                          RRType::A(), false);
    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 3, 3, 3);
    rrsetsCheck("dname.example.com. 3600 IN DNAME sql1.example.com.\n"
                "www.dname.example.com. 3600 IN CNAME www.sql1.example.com.\n"
                "www.sql1.example.com. 3600 IN A 192.0.2.2\n",
                msg.beginSection(Message::SECTION_ANSWER),
                msg.endSection(Message::SECTION_ANSWER));

    // Also check the case of explicit DNAME query.
    msg.clear(Message::PARSE);
    createAndProcessQuery(Name("dname.example.com"), RRClass::ANY(),
                          RRType::DNAME(), false);
    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 1, 3, 3);
    rrsetsCheck("dname.example.com. 3600 IN DNAME sql1.example.com.\n",
                msg.beginSection(Message::SECTION_ANSWER),
                msg.endSection(Message::SECTION_ANSWER));
}

TEST_F(DataSrcTest, queryClassAnyCNAME) {
    // Similar test for CNAME
    createAndProcessQuery(Name("foo.example.com"), RRClass::ANY(),
                          RRType::A(), false);
    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 1, 0, 0);
    rrsetsCheck("foo.example.com. 3600 IN CNAME cnametest.example.net.\n",
                msg.beginSection(Message::SECTION_ANSWER),
                msg.endSection(Message::SECTION_ANSWER));
}

TEST_F(DataSrcTest, NSQuery) {
    createAndProcessQuery(Name("example.com"), RRClass::IN(),
                          RRType::NS());
    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 4, 0, 6);

    RRsetIterator rit = msg.beginSection(Message::SECTION_ANSWER);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
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
    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 4, 0, 6);

    RRsetIterator rit = msg.beginSection(Message::SECTION_ANSWER);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
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
    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 4, 0, 6);

    rit = msg.beginSection(Message::SECTION_ANSWER);
    rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
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
    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 4, 4, 6);

    RRsetIterator rit = msg.beginSection(Message::SECTION_ANSWER);
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
    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 4, 4, 6);

    RRsetIterator rit = msg.beginSection(Message::SECTION_ANSWER);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::DNSKEY(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    msg.clear(Message::PARSE);
    createAndProcessQuery(Name("example.com"), RRClass::IN(),
                          RRType::DNSKEY());
    rit = msg.beginSection(Message::SECTION_ANSWER);
    rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::DNSKEY(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
}

TEST_F(DataSrcTest, NxRRset) {
    createAndProcessQuery(Name("example.com"), RRClass::IN(),
                          RRType::PTR());

    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 0, 4, 0);

    RRsetIterator rit = msg.beginSection(Message::SECTION_AUTHORITY);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::SOA(), rrset->getType());
}

TEST_F(DataSrcTest, Nxdomain) {
    createAndProcessQuery(Name("glork.example.com"), RRClass::IN(),
                          RRType::A());

    headerCheck(msg, qid, Rcode::NXDOMAIN(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 0, 6, 0);

    RRsetIterator rit = msg.beginSection(Message::SECTION_AUTHORITY);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::SOA(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    // XXX: check for other authority section answers
}

TEST_F(DataSrcTest, NxdomainAfterSOAQuery) {
    // There was a bug where once SOA RR is stored in the hot spot cache
    // subsequent negative search fails due to "missing SOA".  This test
    // checks that situation.

    // First, run the scenario with disabling the cache.
    cache.setEnabled(false);
    createAndProcessQuery(Name("example.com"), RRClass::IN(),
                          RRType::SOA());
    msg.clear(Message::PARSE);
    createAndProcessQuery(Name("notexistent.example.com"), RRClass::IN(),
                          RRType::A());
    {
        SCOPED_TRACE("NXDOMAIN after SOA, without hot spot cache");
        headerCheck(msg, qid, Rcode::NXDOMAIN(), opcodeval,
                    QR_FLAG | AA_FLAG | RD_FLAG, 1, 0, 6, 0);
    }

    // Then enable the cache and perform the same queries.  This should
    // produce the same result.
    cache.setEnabled(true);
    msg.clear(Message::PARSE);
    createAndProcessQuery(Name("example.com"), RRClass::IN(),
                          RRType::SOA());
    msg.clear(Message::PARSE);
    createAndProcessQuery(Name("notexistent.example.com"), RRClass::IN(),
                        RRType::A());
    {
        SCOPED_TRACE("NXDOMAIN after SOA, without hot spot cache");
        headerCheck(msg, qid, Rcode::NXDOMAIN(), opcodeval,
                    QR_FLAG | AA_FLAG | RD_FLAG, 1, 0, 6, 0);
    }
}

TEST_F(DataSrcTest, NxZone) {
    createAndProcessQuery(Name("spork.example"), RRClass::IN(),
                          RRType::A());

    headerCheck(msg, qid, Rcode::REFUSED(), opcodeval,
                QR_FLAG | RD_FLAG, 1, 0, 0, 0);

    EXPECT_EQ(Rcode::REFUSED(), msg.getRcode());
    EXPECT_TRUE(msg.getHeaderFlag(Message::HEADERFLAG_QR));
    EXPECT_FALSE(msg.getHeaderFlag(Message::HEADERFLAG_AA));
    EXPECT_TRUE(msg.getHeaderFlag(Message::HEADERFLAG_RD));
}

TEST_F(DataSrcTest, Wildcard) {
    createAndProcessQuery(Name("www.wild.example.com"), RRClass::IN(),
                          RRType::A());

    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 2, 6, 6);

    RRsetIterator rit = msg.beginSection(Message::SECTION_ANSWER);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.wild.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    EXPECT_EQ("192.0.2.2", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Message::SECTION_AUTHORITY);
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
    EXPECT_EQ("dns01.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns02.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns03.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Message::SECTION_ADDITIONAL);
    rrset = *rit;
    EXPECT_EQ(Name("dns01.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, WildcardNodata) {
    // Check that a query for a data type not covered by the wildcard
    // returns NOERROR
    createAndProcessQuery(Name("www.wild.example.com"), RRClass::IN(),
                          RRType::AAAA());
    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 0, 2, 0);
}

TEST_F(DataSrcTest, DISABLED_WildcardAgainstMultiLabel) {
    // this qname shouldn't match *.wild.com.com (because * can only match
    // a single label), and it should result in NXDOMAIN.
    createAndProcessQuery(Name("www.xxx.wild.example.com"), RRClass::IN(),
                          RRType::A());
    headerCheck(msg, qid, Rcode::NXDOMAIN(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 0, 1, 0);
}

TEST_F(DataSrcTest, WildcardCname) {
    // Check that wildcard answers containing CNAMES are followed
    // correctly.  It should result in the same response for both
    // class IN and ANY queries.
    const RRClass classes[2] = { RRClass::IN(), RRClass::ANY() };

    for (int i = 0; i < sizeof(classes) / sizeof(classes[0]); ++i) {
        SCOPED_TRACE("Wildcard + CNAME test for class " + classes[i].toText());

        msg.clear(Message::PARSE);

        createAndProcessQuery(Name("www.wild2.example.com"), classes[i],
                              RRType::A(), false);

        headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                    QR_FLAG | AA_FLAG | RD_FLAG, 1, 2, 3, 3);

        rrsetsCheck("www.wild2.example.com. 3600 IN CNAME www.example.com\n"
                    "www.example.com. 3600 IN A 192.0.2.1\n",
                    msg.beginSection(Message::SECTION_ANSWER),
                    msg.endSection(Message::SECTION_ANSWER));
        rrsetsCheck("example.com. 3600 IN NS dns01.example.com.\n"
                    "example.com. 3600 IN NS dns02.example.com.\n"
                    "example.com. 3600 IN NS dns03.example.com.",
                    msg.beginSection(Message::SECTION_AUTHORITY),
                    msg.endSection(Message::SECTION_AUTHORITY));
        rrsetsCheck("dns01.example.com. 3600 IN A 192.0.2.1\n"
                    "dns02.example.com. 3600 IN A 192.0.2.2\n"
                    "dns03.example.com. 3600 IN A 192.0.2.3",
                    msg.beginSection(Message::SECTION_ADDITIONAL),
                    msg.endSection(Message::SECTION_ADDITIONAL));
    }
}

TEST_F(DataSrcTest, WildcardCnameNodata) {
    // A wildcard containing a CNAME whose target does not include
    // data of this type.
    createAndProcessQuery(Name("www.wild2.example.com"), RRClass::IN(),
                          RRType::AAAA());
    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 2, 4, 0);

    RRsetIterator rit = msg.beginSection(Message::SECTION_ANSWER);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.wild2.example.com"), rrset->getName());
    EXPECT_EQ(RRType::CNAME(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    EXPECT_EQ("www.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Message::SECTION_AUTHORITY);
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
    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 2, 6, 0);

    RRsetIterator rit = msg.beginSection(Message::SECTION_ANSWER);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.wild3.example.com"), rrset->getName());
    EXPECT_EQ(RRType::CNAME(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    EXPECT_EQ("spork.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Message::SECTION_AUTHORITY);
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

    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 2, 4, 6);

    RRsetIterator rit = msg.beginSection(Message::SECTION_ANSWER);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("www.sql1.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    EXPECT_EQ("192.0.2.2", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Message::SECTION_AUTHORITY);
    rrset = *rit;
    EXPECT_EQ(Name("sql1.example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    EXPECT_EQ("dns01.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns02.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns03.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Message::SECTION_ADDITIONAL);
    rrset = *rit;
    EXPECT_EQ(Name("dns01.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, Dname) {
    createAndProcessQuery(Name("www.dname.example.com"), RRClass::IN(),
                          RRType::A());

    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 5, 4, 6);

    RRsetIterator rit = msg.beginSection(Message::SECTION_ANSWER);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("dname.example.com"), rrset->getName());
    EXPECT_EQ(RRType::DNAME(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    EXPECT_EQ("sql1.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    // XXX: check CNAME and A record too

    rit = msg.beginSection(Message::SECTION_AUTHORITY);
    rrset = *rit;
    EXPECT_EQ(Name("sql1.example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    EXPECT_EQ("dns01.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns02.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("dns03.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Message::SECTION_ADDITIONAL);
    rrset = *rit;
    EXPECT_EQ(Name("dns01.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
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
    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 0, 1, 0);
}

TEST_F(DataSrcTest, Cname) {
    createAndProcessQuery(Name("foo.example.com"), RRClass::IN(),
                          RRType::A());

    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 2, 0, 0);

    RRsetIterator rit = msg.beginSection(Message::SECTION_ANSWER);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("foo.example.com"), rrset->getName());
    EXPECT_EQ(RRType::CNAME(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    EXPECT_EQ("cnametest.example.net.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, CnameInt) {
    createAndProcessQuery(Name("cname-int.example.com"), RRClass::IN(),
                          RRType::A());

    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 4, 4, 6);

    RRsetIterator rit = msg.beginSection(Message::SECTION_ANSWER);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("cname-int.example.com"), rrset->getName());
    EXPECT_EQ(RRType::CNAME(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    EXPECT_EQ("www.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    // XXX: check a record as well

    rit = msg.beginSection(Message::SECTION_AUTHORITY);
    rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
}

TEST_F(DataSrcTest, CnameExt) {
    createAndProcessQuery(Name("cname-ext.example.com"), RRClass::IN(),
                          RRType::A());

    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 4, 4, 6);

    RRsetIterator rit = msg.beginSection(Message::SECTION_ANSWER);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("cname-ext.example.com"), rrset->getName());
    EXPECT_EQ(RRType::CNAME(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    EXPECT_EQ("www.sql1.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Message::SECTION_AUTHORITY);
    rrset = *rit;
    EXPECT_EQ(Name("sql1.example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
}

TEST_F(DataSrcTest, Delegation) {
    createAndProcessQuery(Name("www.subzone.example.com"), RRClass::IN(),
                          RRType::A());

    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | RD_FLAG, 1, 0, 5, 2);

    RRsetIterator rit = msg.beginSection(Message::SECTION_AUTHORITY);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("subzone.example.com."), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    EXPECT_EQ("ns1.subzone.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_FALSE(it->isLast());

    rit = msg.beginSection(Message::SECTION_ADDITIONAL);
    rrset = *rit;
    EXPECT_EQ(Name("ns1.subzone.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, NSDelegation) {
    createAndProcessQuery(Name("subzone.example.com"), RRClass::IN(),
                          RRType::NS());

    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | RD_FLAG, 1, 0, 5, 2);

    RRsetIterator rit = msg.beginSection(Message::SECTION_AUTHORITY);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("subzone.example.com."), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    EXPECT_EQ("ns1.subzone.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_FALSE(it->isLast());

    rit = msg.beginSection(Message::SECTION_ADDITIONAL);
    rrset = *rit;
    EXPECT_EQ(Name("ns1.subzone.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
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

    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 2, 4, 6);

    RRsetIterator rit = msg.beginSection(Message::SECTION_ANSWER);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("subzone.example.com."), rrset->getName());
    EXPECT_EQ(RRType::NSEC(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    rit = msg.beginSection(Message::SECTION_AUTHORITY);
    rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
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

    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | RD_FLAG, 1, 0, 5, 2);
    RRsetIterator rit = msg.beginSection(Message::SECTION_AUTHORITY);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("subzone.example.com."), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    EXPECT_EQ("ns1.subzone.example.com.", it->getCurrent().toText());
    it->next();
    EXPECT_FALSE(it->isLast());

    rit = msg.beginSection(Message::SECTION_ADDITIONAL);
    rrset = *rit;
    EXPECT_EQ(Name("ns1.subzone.example.com"), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(DataSrcTest, DS) {
    createAndProcessQuery(Name("subzone.example.com"), RRClass::IN(),
                          RRType::DS());

    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 3, 4, 6);

    RRsetIterator rit = msg.beginSection(Message::SECTION_ANSWER);
    RRsetPtr rrset = *rit;
    EXPECT_EQ(Name("subzone.example.com."), rrset->getName());
    EXPECT_EQ(RRType::DS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    rit = msg.beginSection(Message::SECTION_AUTHORITY);
    rrset = *rit;
    EXPECT_EQ(Name("example.com"), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
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
    EXPECT_EQ(2, msg.getRRCount(Message::SECTION_ANSWER));
}

// NSEC query for the name of a zone cut for non-secure delegation.
// Should return normal referral.
TEST_F(DataSrcTest, NSECZonecutOfNonsecureZone) {
    createAndProcessQuery(Name("sub.example.org"), RRClass::IN(),
                          RRType::NSEC());

    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | RD_FLAG, 1, 0, 1, 1);

    RRsetIterator rit = msg.beginSection(Message::SECTION_AUTHORITY);
    ConstRRsetPtr rrset = *rit;
    EXPECT_EQ(Name("sub.example.org."), rrset->getName());
    EXPECT_EQ(RRType::NS(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    RdataIteratorPtr it = rrset->getRdataIterator();
    EXPECT_EQ(createRdata(RRType::NS(), RRClass::IN(),
                          "ns.sub.example.org.")->toText(),
              it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    rit = msg.beginSection(Message::SECTION_ADDITIONAL);
    rrset = *rit;
    EXPECT_EQ(Name("ns.sub.example.org."), rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());

    it = rrset->getRdataIterator();
    EXPECT_EQ(createRdata(RRType::A(), RRClass::IN(), "192.0.2.101")->toText(),
              it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}

// Test sending a DS query to root (nonsense, but it should survive)
TEST_F(DataSrcTest, RootDSQuery1) {
    EXPECT_NO_THROW(createAndProcessQuery(Name("."), RRClass::IN(),
                                          RRType::DS()));
    headerCheck(msg, qid, Rcode::REFUSED(), opcodeval,
                QR_FLAG | RD_FLAG, 1, 0, 0, 0);
}

// The same, but when we have the root zone
// (which triggers rfc4035 section 3.1.4.1)
TEST_F(DataSrcTest, RootDSQuery2) {
    // The message
    msg.makeResponse();
    msg.setOpcode(Opcode::QUERY());
    msg.addQuestion(Question(Name("."), RRClass::IN(), RRType::DS()));
    msg.setHeaderFlag(Message::HEADERFLAG_RD);
    // Prepare the source
    DataSrcPtr sql3_source = DataSrcPtr(new Sqlite3DataSrc);
    ConstElementPtr sqlite_root = Element::fromJSON(
        "{ \"database_file\": \"" TEST_DATA_DIR "/test-root.sqlite3\"}");
    EXPECT_NO_THROW(sql3_source->init(sqlite_root));
    // Make the query
    EXPECT_NO_THROW(performQuery(*sql3_source, cache, msg));

    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 0, 1, 0);
}

TEST_F(DataSrcTest, DSQueryFromCache) {
    // explicitly enable hot spot cache
    cache.setEnabled(true);

    // The first query will create a negative cache for example.org/CNAME
    createAndProcessQuery(Name("example.org"), RRClass::IN(), RRType::SOA());

    // the cached CNAME shouldn't confuse subsequent query.
    // there may be several different possible cases that could trigger a bug,
    // but DS query is the only known example.
    msg.clear(Message::PARSE);
    createAndProcessQuery(Name("example.org"), RRClass::IN(), RRType::DS());

    // returning refused is probably a bad behavior, but it's a different
    // issue -- see Trac Ticket #306.
    headerCheck(msg, qid, Rcode::REFUSED(), opcodeval,
                QR_FLAG | RD_FLAG, 1, 0, 0, 0);
}

// Non-existent name in the "static" data source.  The purpose of this test
// is to check a corner case behavior when atypical RRClass (CH in this case)
// is specified.
TEST_F(DataSrcTest, StaticNxDomain) {
    createAndProcessQuery(Name("www.version.bind"), RRClass::CH(),
                          RRType::TXT());
    headerCheck(msg, qid, Rcode::NXDOMAIN(), opcodeval,
                QR_FLAG | AA_FLAG | RD_FLAG, 1, 0, 1, 0);
    RRsetIterator rit = msg.beginSection(Message::SECTION_AUTHORITY);
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

TEST_F(DataSrcTest, apexCNAMEZone) {
    // The query name doesn't exist in the best matching zone,
    // and there's a CNAME at the apex (which is bogus), so query handling
    // will fail due to missing SOA.
    EXPECT_THROW(createAndProcessQuery(Name("notexist.apexcname.example"),
                                       RRClass::IN(), RRType::A()),
                 DataSourceError);
}

TEST_F(DataSrcTest, incompleteGlue) {
    // One of the NS names belong to a different zone (which is still
    // authoritative), and the glue is missing in that zone.  We should
    // still return the existent glue.
    // (nons.example is also broken in that it doesn't have apex NS, but
    // that doesn't matter for this test)
    createAndProcessQuery(Name("www.incompletechild.nons.example"),
                          RRClass::IN(), RRType::A());
    headerCheck(msg, qid, Rcode::NOERROR(), opcodeval,
                QR_FLAG | RD_FLAG, 1, 0, 2, 1);
    rrsetsCheck("incompletechild.nons.example. 3600 IN NS ns.incompletechild.nons.example.\n"
                "incompletechild.nons.example. 3600 IN NS nx.nosoa.example.",
                msg.beginSection(Message::SECTION_AUTHORITY),
                msg.endSection(Message::SECTION_AUTHORITY));
    rrsetsCheck("ns.incompletechild.nons.example. 3600 IN A 192.0.2.1",
                msg.beginSection(Message::SECTION_ADDITIONAL),
                msg.endSection(Message::SECTION_ADDITIONAL));
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

TEST_F(DataSrcTest, cacheDataInNonexistentZone) {
    // This test emulates the situation where an RRset in some zone of some
    // data source is cached and then the zone is removed from the data source.
    // When there is such a substantial inconsistency between the cache and
    // the real data source, we should honor the latter.  More important,
    // the inconsistency shouldn't cause any disruption such as a crash.

    const Name qname("nosuchzone.example");
    RRsetPtr rrset(new RRset(qname, RRClass::IN(), RRType::A(), RRTTL(0)));
    cache.addPositive(rrset, DataSrc::REFERRAL);

    createAndProcessQuery(qname, RRClass::IN(), RRType::A(), false);
    headerCheck(msg, qid, Rcode::REFUSED(), opcodeval, QR_FLAG | RD_FLAG,
                1, 0, 0, 0);
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
