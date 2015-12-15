// Copyright (C) 2010-2013  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <fstream>

#include <boost/scoped_ptr.hpp>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <util/time_utilities.h>

#include <util/unittests/testdata.h>
#include <util/unittests/textdata.h>

#include <dns/edns.h>
#include <dns/exceptions.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/question.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>
#include <dns/tsig.h>
#include <dns/tsigkey.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <util/unittests/wiredata.h>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

//
// Note: we need more tests, including:
// parsing malformed headers
// more complete tests about parsing/rendering header flags, opcode, rcode, etc.
// tests for adding RRsets
// tests for RRset/Question iterators
// But, we'll ship with the current set of tests for now, partly because many
// of the above are covered as part of other tests, and partly due to time
// limitation.  We also expect to revisit the fundamental design of the Message
// class, at which point we'll also revise the tests including more cases.
//

const uint16_t Message::DEFAULT_MAX_UDPSIZE;

namespace isc {
namespace util {
namespace detail {
extern int64_t (*gettimeFunction)();
}
}
}

// XXX: this is defined as class static constants, but some compilers
// seemingly cannot find the symbol when used in the EXPECT_xxx macros.
const uint16_t TSIGContext::DEFAULT_FUDGE;

namespace {
class MessageTest : public ::testing::Test {
protected:
    MessageTest() : test_name("test.example.com"), obuffer(0),
                    message_parse(Message::PARSE),
                    message_render(Message::RENDER),
                    bogus_section(static_cast<Message::Section>(
                                      Message::SECTION_ADDITIONAL + 1)),
                    tsig_ctx(TSIGKey("www.example.com:"
                                     "SFuWd/q99SzF8Yzd1QbB9g=="))
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

    static Question factoryFromFile(const char* datafile);
    const Name test_name;
    OutputBuffer obuffer;
    MessageRenderer renderer;
    Message message_parse;
    Message message_render;
    const Message::Section bogus_section;
    RRsetPtr rrset_a;           // A RRset with two RDATAs
    RRsetPtr rrset_aaaa;        // AAAA RRset with one RDATA with RRSIG
    RRsetPtr rrset_rrsig;       // RRSIG for the AAAA RRset
    TSIGContext tsig_ctx;
    vector<unsigned char> received_data;
    vector<unsigned char> expected_data;

    void factoryFromFile(Message& message, const char* datafile,
                         Message::ParseOptions options =
                         Message::PARSE_DEFAULT);
};

void
MessageTest::factoryFromFile(Message& message, const char* datafile,
                             Message::ParseOptions options)
{
    received_data.clear();
    UnitTestUtil::readWireData(datafile, received_data);

    InputBuffer buffer(&received_data[0], received_data.size());
    message.fromWire(buffer, options);
}

TEST_F(MessageTest, headerFlag) {
    // by default no flag is set
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_QR));
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_AA));
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_TC));
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_RD));
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_RA));
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_AD));
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_CD));

    // set operation: by default it will be on
    message_render.setHeaderFlag(Message::HEADERFLAG_QR);
    EXPECT_TRUE(message_render.getHeaderFlag(Message::HEADERFLAG_QR));

    // it can be set to on explicitly, too
    message_render.setHeaderFlag(Message::HEADERFLAG_AA, true);
    EXPECT_TRUE(message_render.getHeaderFlag(Message::HEADERFLAG_AA));

    // the bit can also be cleared
    message_render.setHeaderFlag(Message::HEADERFLAG_AA, false);
    EXPECT_FALSE(message_render.getHeaderFlag(Message::HEADERFLAG_AA));

    // Invalid flag values
    EXPECT_THROW(message_render.setHeaderFlag(
                     static_cast<Message::HeaderFlag>(0)), InvalidParameter);
    EXPECT_THROW(message_render.setHeaderFlag(
                     static_cast<Message::HeaderFlag>(0x7000)),
                 InvalidParameter);
    EXPECT_THROW(message_render.setHeaderFlag(
                     static_cast<Message::HeaderFlag>(0x0800)),
                 InvalidParameter);
    EXPECT_THROW(message_render.setHeaderFlag(
                     static_cast<Message::HeaderFlag>(0x0040)),
                 InvalidParameter);
    EXPECT_THROW(message_render.setHeaderFlag(
                     static_cast<Message::HeaderFlag>(0x10000)),
                 InvalidParameter);
    EXPECT_THROW(message_render.setHeaderFlag(
                     static_cast<Message::HeaderFlag>(0x80000000)),
                 InvalidParameter);

    // set operation isn't allowed in the parse mode.
    EXPECT_THROW(message_parse.setHeaderFlag(Message::HEADERFLAG_QR),
                 InvalidMessageOperation);
}
TEST_F(MessageTest, getEDNS) {
    EXPECT_FALSE(message_parse.getEDNS()); // by default EDNS isn't set

    factoryFromFile(message_parse, "message_fromWire10.wire");
    EXPECT_TRUE(message_parse.getEDNS());
    EXPECT_EQ(0, message_parse.getEDNS()->getVersion());
    EXPECT_EQ(4096, message_parse.getEDNS()->getUDPSize());
    EXPECT_TRUE(message_parse.getEDNS()->getDNSSECAwareness());
}

TEST_F(MessageTest, setEDNS) {
    // setEDNS() isn't allowed in the parse mode
    EXPECT_THROW(message_parse.setEDNS(EDNSPtr(new EDNS())),
                 InvalidMessageOperation);

    EDNSPtr edns = EDNSPtr(new EDNS());
    message_render.setEDNS(edns);
    EXPECT_EQ(edns, message_render.getEDNS());
}

TEST_F(MessageTest, fromWireWithTSIG) {
    // Initially there should be no TSIG
    EXPECT_EQ(static_cast<void*>(NULL), message_parse.getTSIGRecord());

    // getTSIGRecord() is only valid in the parse mode.
    EXPECT_THROW(message_render.getTSIGRecord(), InvalidMessageOperation);

    factoryFromFile(message_parse, "message_toWire2.wire");
    const uint8_t expected_mac[] = {
        0x22, 0x70, 0x26, 0xad, 0x29, 0x7b, 0xee, 0xe7,
        0x21, 0xce, 0x6c, 0x6f, 0xff, 0x1e, 0x9e, 0xf3
    };
    const TSIGRecord* tsig_rr = message_parse.getTSIGRecord();
    ASSERT_NE(static_cast<void*>(NULL), tsig_rr);
    EXPECT_EQ(Name("www.example.com"), tsig_rr->getName());
    EXPECT_EQ(85, tsig_rr->getLength()); // see TSIGRecordTest.getLength
    EXPECT_EQ(TSIGKey::HMACMD5_NAME(), tsig_rr->getRdata().getAlgorithm());
    EXPECT_EQ(0x4da8877a, tsig_rr->getRdata().getTimeSigned());
    EXPECT_EQ(TSIGContext::DEFAULT_FUDGE, tsig_rr->getRdata().getFudge());
    matchWireData(expected_mac, sizeof(expected_mac),
                  tsig_rr->getRdata().getMAC(),
                  tsig_rr->getRdata().getMACSize());
    EXPECT_EQ(0, tsig_rr->getRdata().getError());
    EXPECT_EQ(0, tsig_rr->getRdata().getOtherLen());
    EXPECT_EQ(static_cast<void*>(NULL), tsig_rr->getRdata().getOtherData());

    // If we clear the message for reuse, the recorded TSIG will be cleared.
    message_parse.clear(Message::PARSE);
    EXPECT_EQ(static_cast<void*>(NULL), message_parse.getTSIGRecord());
}

TEST_F(MessageTest, fromWireWithTSIGCompressed) {
    // Mostly same as fromWireWithTSIG, but the TSIG owner name is compressed.
    factoryFromFile(message_parse, "message_fromWire12.wire");
    const TSIGRecord* tsig_rr = message_parse.getTSIGRecord();
    ASSERT_NE(static_cast<void*>(NULL), tsig_rr);
    EXPECT_EQ(Name("www.example.com"), tsig_rr->getName());
    // len(www.example.com) = 17, but when fully compressed, the length is
    // 2 bytes.  So the length of the record should be 15 bytes shorter.
    EXPECT_EQ(70, tsig_rr->getLength());
}

TEST_F(MessageTest, fromWireWithBadTSIG) {
    // Multiple TSIG RRs
    EXPECT_THROW(factoryFromFile(message_parse, "message_fromWire13.wire"),
                 DNSMessageFORMERR);
    message_parse.clear(Message::PARSE);

    // TSIG in the answer section (must be in additional)
    EXPECT_THROW(factoryFromFile(message_parse, "message_fromWire14.wire"),
                 DNSMessageFORMERR);
    message_parse.clear(Message::PARSE);

    // TSIG is not the last record.
    EXPECT_THROW(factoryFromFile(message_parse, "message_fromWire15.wire"),
                 DNSMessageFORMERR);
    message_parse.clear(Message::PARSE);

    // Unexpected RR Class (this will fail in constructing TSIGRecord)
    EXPECT_THROW(factoryFromFile(message_parse, "message_fromWire16.wire"),
                 DNSMessageFORMERR);
}

TEST_F(MessageTest, getRRCount) {
    // by default all counters should be 0
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_ADDITIONAL));

    message_render.addQuestion(Question(Name("test.example.com"),
                                        RRClass::IN(), RRType::A()));
    EXPECT_EQ(1, message_render.getRRCount(Message::SECTION_QUESTION));

    // rrset_a contains two RRs
    message_render.addRRset(Message::SECTION_ANSWER, rrset_a);
    EXPECT_EQ(2, message_render.getRRCount(Message::SECTION_ANSWER));

    // parse a message containing a Question and EDNS OPT RR.
    // OPT shouldn't be counted as normal RR, so result of getRRCount
    // shouldn't change.
    factoryFromFile(message_parse, "message_fromWire11.wire");
    EXPECT_EQ(1, message_render.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_ADDITIONAL));

    // out-of-band section ID
    EXPECT_THROW(message_parse.getRRCount(bogus_section), OutOfRange);
}

TEST_F(MessageTest, addRRset) {
    // initially, we have 0
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_ANSWER));

    // add two A RRs (unsigned)
    message_render.addRRset(Message::SECTION_ANSWER, rrset_a);
    EXPECT_EQ(rrset_a,
              *message_render.beginSection(Message::SECTION_ANSWER));
    EXPECT_EQ(2, message_render.getRRCount(Message::SECTION_ANSWER));

    message_render.clear(Message::RENDER);

    // add one AAAA RR (signed)
    message_render.addRRset(Message::SECTION_ANSWER, rrset_aaaa);
    EXPECT_EQ(rrset_aaaa,
              *message_render.beginSection(Message::SECTION_ANSWER));
    EXPECT_EQ(2, message_render.getRRCount(Message::SECTION_ANSWER));
}

TEST_F(MessageTest, badAddRRset) {
    // addRRset() isn't allowed in the parse mode.
    EXPECT_THROW(message_parse.addRRset(Message::SECTION_ANSWER,
                                        rrset_a), InvalidMessageOperation);
    // out-of-band section ID
    EXPECT_THROW(message_render.addRRset(bogus_section, rrset_a), OutOfRange);

    // NULL RRset
    EXPECT_THROW(message_render.addRRset(Message::SECTION_ANSWER, RRsetPtr()),
                 InvalidParameter);
}

TEST_F(MessageTest, hasRRset) {
    message_render.addRRset(Message::SECTION_ANSWER, rrset_a);
    EXPECT_TRUE(message_render.hasRRset(Message::SECTION_ANSWER, test_name,
                                        RRClass::IN(), RRType::A()));
    // section doesn't match
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ADDITIONAL, test_name,
                                         RRClass::IN(), RRType::A()));
    // name doesn't match
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ANSWER,
                                         Name("nomatch.example"),
                                         RRClass::IN(), RRType::A()));
    // RR class doesn't match
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ANSWER, test_name,
                                        RRClass::CH(), RRType::A()));
    // RR type doesn't match
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ANSWER, test_name,
                                        RRClass::IN(), RRType::AAAA()));

    // out-of-band section ID
    EXPECT_THROW(message_render.hasRRset(bogus_section, test_name,
                                         RRClass::IN(), RRType::A()),
                 OutOfRange);

    // Repeat the checks having created an RRset of the appropriate type.

    RRsetPtr rrs1(new RRset(test_name, RRClass::IN(), RRType::A(), RRTTL(60)));
    EXPECT_TRUE(message_render.hasRRset(Message::SECTION_ANSWER, rrs1));
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ADDITIONAL, rrs1));

    RRsetPtr rrs2(new RRset(Name("nomatch.example"), RRClass::IN(), RRType::A(),
        RRTTL(5)));
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ANSWER, rrs2));

    RRsetPtr rrs3(new RRset(test_name, RRClass::CH(), RRType::A(), RRTTL(60)));
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ANSWER, rrs3));

    RRsetPtr rrs4(new RRset(test_name, RRClass::IN(), RRType::AAAA(), RRTTL(5)));
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ANSWER, rrs4));

    RRsetPtr rrs5(new RRset(test_name, RRClass::IN(), RRType::AAAA(), RRTTL(5)));
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ANSWER, rrs4));

    EXPECT_THROW(message_render.hasRRset(bogus_section, rrs1), OutOfRange);
}

TEST_F(MessageTest, removeRRset) {
    message_render.addRRset(Message::SECTION_ANSWER, rrset_a);
    message_render.addRRset(Message::SECTION_ANSWER, rrset_aaaa);
    EXPECT_TRUE(message_render.hasRRset(Message::SECTION_ANSWER, test_name,
        RRClass::IN(), RRType::A()));
    EXPECT_TRUE(message_render.hasRRset(Message::SECTION_ANSWER, test_name,
        RRClass::IN(), RRType::AAAA()));
    EXPECT_EQ(4, message_render.getRRCount(Message::SECTION_ANSWER));

    // Locate the AAAA RRset and remove it and any associated RRSIGs
    RRsetIterator i = message_render.beginSection(Message::SECTION_ANSWER);
    if ((*i)->getType() == RRType::A()) {
        ++i;
    }
    EXPECT_EQ(RRType::AAAA(), (*i)->getType());
    message_render.removeRRset(Message::SECTION_ANSWER, i);

    EXPECT_TRUE(message_render.hasRRset(Message::SECTION_ANSWER, test_name,
        RRClass::IN(), RRType::A()));
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ANSWER, test_name,
        RRClass::IN(), RRType::AAAA()));
    EXPECT_EQ(2, message_render.getRRCount(Message::SECTION_ANSWER));
}

TEST_F(MessageTest, clearQuestionSection) {
    QuestionPtr q(new Question(Name("www.example.com"), RRClass::IN(),
                               RRType::A()));
    message_render.addQuestion(q);
    ASSERT_EQ(1, message_render.getRRCount(Message::SECTION_QUESTION));

    message_render.clearSection(Message::SECTION_QUESTION);
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_QUESTION));
    EXPECT_TRUE(message_render.beginQuestion() ==
                message_render.endQuestion());
}


TEST_F(MessageTest, clearAnswerSection) {
    // Add two RRsets, check they are present, clear the section,
    // check if they are gone.
    message_render.addRRset(Message::SECTION_ANSWER, rrset_a);
    message_render.addRRset(Message::SECTION_ANSWER, rrset_aaaa);
    ASSERT_TRUE(message_render.hasRRset(Message::SECTION_ANSWER, test_name,
        RRClass::IN(), RRType::A()));
    ASSERT_TRUE(message_render.hasRRset(Message::SECTION_ANSWER, test_name,
        RRClass::IN(), RRType::AAAA()));
    ASSERT_EQ(4, message_render.getRRCount(Message::SECTION_ANSWER));

    message_render.clearSection(Message::SECTION_ANSWER);
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ANSWER, test_name,
        RRClass::IN(), RRType::A()));
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ANSWER, test_name,
        RRClass::IN(), RRType::AAAA()));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_ANSWER));
}

TEST_F(MessageTest, clearAuthoritySection) {
    // Add two RRsets, check they are present, clear the section,
    // check if they are gone.
    message_render.addRRset(Message::SECTION_AUTHORITY, rrset_a);
    message_render.addRRset(Message::SECTION_AUTHORITY, rrset_aaaa);
    ASSERT_TRUE(message_render.hasRRset(Message::SECTION_AUTHORITY, test_name,
        RRClass::IN(), RRType::A()));
    ASSERT_TRUE(message_render.hasRRset(Message::SECTION_AUTHORITY, test_name,
        RRClass::IN(), RRType::AAAA()));
    ASSERT_EQ(4, message_render.getRRCount(Message::SECTION_AUTHORITY));

    message_render.clearSection(Message::SECTION_AUTHORITY);
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_AUTHORITY, test_name,
        RRClass::IN(), RRType::A()));
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_AUTHORITY, test_name,
        RRClass::IN(), RRType::AAAA()));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_AUTHORITY));
}

TEST_F(MessageTest, clearAdditionalSection) {
    // Add two RRsets, check they are present, clear the section,
    // check if they are gone.
    message_render.addRRset(Message::SECTION_ADDITIONAL, rrset_a);
    message_render.addRRset(Message::SECTION_ADDITIONAL, rrset_aaaa);
    ASSERT_TRUE(message_render.hasRRset(Message::SECTION_ADDITIONAL, test_name,
        RRClass::IN(), RRType::A()));
    ASSERT_TRUE(message_render.hasRRset(Message::SECTION_ADDITIONAL, test_name,
        RRClass::IN(), RRType::AAAA()));
    ASSERT_EQ(4, message_render.getRRCount(Message::SECTION_ADDITIONAL));

    message_render.clearSection(Message::SECTION_ADDITIONAL);
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ADDITIONAL, test_name,
        RRClass::IN(), RRType::A()));
    EXPECT_FALSE(message_render.hasRRset(Message::SECTION_ADDITIONAL, test_name,
        RRClass::IN(), RRType::AAAA()));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_ADDITIONAL));
}

TEST_F(MessageTest, badClearSection) {
    // attempt of clearing a message in the parse mode.
    EXPECT_THROW(message_parse.clearSection(Message::SECTION_QUESTION),
                 InvalidMessageOperation);
    // attempt of clearing out-of-range section
    EXPECT_THROW(message_render.clearSection(bogus_section), OutOfRange);
}

TEST_F(MessageTest, badBeginSection) {
    // valid cases are tested via other tests
    EXPECT_THROW(message_render.beginSection(Message::SECTION_QUESTION),
                 InvalidMessageSection);
    EXPECT_THROW(message_render.beginSection(bogus_section), OutOfRange);
}

TEST_F(MessageTest, badEndSection) {
    // valid cases are tested via other tests
    EXPECT_THROW(message_render.endSection(Message::SECTION_QUESTION),
                 InvalidMessageSection);
    EXPECT_THROW(message_render.endSection(bogus_section), OutOfRange);
}

TEST_F(MessageTest, appendSection) {
    Message target(Message::RENDER);

    // Section check
    EXPECT_THROW(target.appendSection(bogus_section, message_render),
                 OutOfRange);

    // Make sure nothing is copied if there is nothing to copy
    target.appendSection(Message::SECTION_QUESTION, message_render);
    EXPECT_EQ(0, target.getRRCount(Message::SECTION_QUESTION));
    target.appendSection(Message::SECTION_ANSWER, message_render);
    EXPECT_EQ(0, target.getRRCount(Message::SECTION_ANSWER));
    target.appendSection(Message::SECTION_AUTHORITY, message_render);
    EXPECT_EQ(0, target.getRRCount(Message::SECTION_AUTHORITY));
    target.appendSection(Message::SECTION_ADDITIONAL, message_render);
    EXPECT_EQ(0, target.getRRCount(Message::SECTION_ADDITIONAL));

    // Now add some data, copy again, and see if it got added
    message_render.addQuestion(Question(Name("test.example.com"),
                                        RRClass::IN(), RRType::A()));
    message_render.addRRset(Message::SECTION_ANSWER, rrset_a);
    message_render.addRRset(Message::SECTION_AUTHORITY, rrset_a);
    message_render.addRRset(Message::SECTION_ADDITIONAL, rrset_a);
    message_render.addRRset(Message::SECTION_ADDITIONAL, rrset_aaaa);

    target.appendSection(Message::SECTION_QUESTION, message_render);
    EXPECT_EQ(1, target.getRRCount(Message::SECTION_QUESTION));

    target.appendSection(Message::SECTION_ANSWER, message_render);
    EXPECT_EQ(2, target.getRRCount(Message::SECTION_ANSWER));
    EXPECT_TRUE(target.hasRRset(Message::SECTION_ANSWER, test_name,
        RRClass::IN(), RRType::A()));

    target.appendSection(Message::SECTION_AUTHORITY, message_render);
    EXPECT_EQ(2, target.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_TRUE(target.hasRRset(Message::SECTION_AUTHORITY, test_name,
        RRClass::IN(), RRType::A()));

    target.appendSection(Message::SECTION_ADDITIONAL, message_render);
    EXPECT_EQ(4, target.getRRCount(Message::SECTION_ADDITIONAL));
    EXPECT_TRUE(target.hasRRset(Message::SECTION_ADDITIONAL, test_name,
        RRClass::IN(), RRType::A()));
    EXPECT_TRUE(target.hasRRset(Message::SECTION_ADDITIONAL, test_name,
        RRClass::IN(), RRType::AAAA()));

    // One more test, test to see if the section gets added, not replaced
    Message source2(Message::RENDER);
    source2.addRRset(Message::SECTION_ANSWER, rrset_aaaa);
    target.appendSection(Message::SECTION_ANSWER, source2);
    EXPECT_EQ(4, target.getRRCount(Message::SECTION_ANSWER));
    EXPECT_TRUE(target.hasRRset(Message::SECTION_ANSWER, test_name,
        RRClass::IN(), RRType::A()));
    EXPECT_TRUE(target.hasRRset(Message::SECTION_ANSWER, test_name,
        RRClass::IN(), RRType::AAAA()));

}

TEST_F(MessageTest, parseHeader) {
    received_data.clear();
    UnitTestUtil::readWireData("message_fromWire1", received_data);

    // parseHeader() isn't allowed in the render mode.
    InputBuffer buffer(&received_data[0], received_data.size());
    EXPECT_THROW(message_render.parseHeader(buffer), InvalidMessageOperation);

    message_parse.parseHeader(buffer);
    EXPECT_EQ(0x1035, message_parse.getQid());
    EXPECT_EQ(Opcode::QUERY(), message_parse.getOpcode());
    EXPECT_EQ(Rcode::NOERROR(), message_parse.getRcode());
    EXPECT_TRUE(message_parse.getHeaderFlag(Message::HEADERFLAG_QR));
    EXPECT_TRUE(message_parse.getHeaderFlag(Message::HEADERFLAG_AA));
    EXPECT_FALSE(message_parse.getHeaderFlag(Message::HEADERFLAG_TC));
    EXPECT_TRUE(message_parse.getHeaderFlag(Message::HEADERFLAG_RD));
    EXPECT_FALSE(message_parse.getHeaderFlag(Message::HEADERFLAG_RA));
    EXPECT_FALSE(message_parse.getHeaderFlag(Message::HEADERFLAG_AD));
    EXPECT_FALSE(message_parse.getHeaderFlag(Message::HEADERFLAG_CD));
    EXPECT_EQ(1, message_parse.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(2, message_parse.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, message_parse.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, message_parse.getRRCount(Message::SECTION_ADDITIONAL));

    // Only the header part should have been examined.
    EXPECT_EQ(12, buffer.getPosition()); // 12 = size of the header section
    EXPECT_TRUE(message_parse.beginQuestion() == message_parse.endQuestion());
    EXPECT_TRUE(message_parse.beginSection(Message::SECTION_ANSWER) ==
                message_parse.endSection(Message::SECTION_ANSWER));
    EXPECT_TRUE(message_parse.beginSection(Message::SECTION_AUTHORITY) ==
                message_parse.endSection(Message::SECTION_AUTHORITY));
    EXPECT_TRUE(message_parse.beginSection(Message::SECTION_ADDITIONAL) ==
                message_parse.endSection(Message::SECTION_ADDITIONAL));
}

void
checkMessageFromWire(const Message& message_parse,
                     const Name& test_name)
{
    EXPECT_EQ(0x1035, message_parse.getQid());
    EXPECT_EQ(Opcode::QUERY(), message_parse.getOpcode());
    EXPECT_EQ(Rcode::NOERROR(), message_parse.getRcode());
    EXPECT_TRUE(message_parse.getHeaderFlag(Message::HEADERFLAG_QR));
    EXPECT_TRUE(message_parse.getHeaderFlag(Message::HEADERFLAG_RD));
    EXPECT_TRUE(message_parse.getHeaderFlag(Message::HEADERFLAG_AA));

    QuestionPtr q = *message_parse.beginQuestion();
    EXPECT_EQ(test_name, q->getName());
    EXPECT_EQ(RRType::A(), q->getType());
    EXPECT_EQ(RRClass::IN(), q->getClass());
    EXPECT_EQ(1, message_parse.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(2, message_parse.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, message_parse.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, message_parse.getRRCount(Message::SECTION_ADDITIONAL));

    RRsetPtr rrset = *message_parse.beginSection(Message::SECTION_ANSWER);
    EXPECT_EQ(test_name, rrset->getName());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    // TTL should be 3600, even though that of the 2nd RR is 7200
    EXPECT_EQ(RRTTL(3600), rrset->getTTL());
    RdataIteratorPtr it = rrset->getRdataIterator();
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_EQ("192.0.2.2", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());
}


TEST_F(MessageTest, fromWire) {
    // fromWire() isn't allowed in the render mode.
    EXPECT_THROW(factoryFromFile(message_render, "message_fromWire1"),
                 InvalidMessageOperation);

    factoryFromFile(message_parse, "message_fromWire1");
    checkMessageFromWire(message_parse, test_name);
}

TEST_F(MessageTest, fromWireMultiple) {
    // Parse from wire multiple times.
    factoryFromFile(message_parse, "message_fromWire1");
    factoryFromFile(message_parse, "message_fromWire1");
    factoryFromFile(message_parse, "message_fromWire1");
    factoryFromFile(message_parse, "message_fromWire1");
    checkMessageFromWire(message_parse, test_name);

    // Calling parseHeader() directly before fromWire() should not cause
    // any problems.
    received_data.clear();
    UnitTestUtil::readWireData("message_fromWire1", received_data);

    InputBuffer buffer(&received_data[0], received_data.size());
    message_parse.parseHeader(buffer);
    message_parse.fromWire(buffer);
    message_parse.parseHeader(buffer);
    message_parse.fromWire(buffer);
    checkMessageFromWire(message_parse, test_name);
}

TEST_F(MessageTest, fromWireShortBuffer) {
    // We trim a valid message (ending with an SOA RR) for one byte.
    // fromWire() should throw an exception while parsing the trimmed RR.
    UnitTestUtil::readWireData("message_fromWire22.wire", received_data);
    InputBuffer buffer(&received_data[0], received_data.size() - 1);
    EXPECT_THROW(message_parse.fromWire(buffer), InvalidBufferPosition);
}

TEST_F(MessageTest, fromWireCombineRRs) {
    // This message contains 3 RRs in the answer section in the order of
    // A, AAAA, A types.  fromWire() should combine the two A RRs into a
    // single RRset by default.
    factoryFromFile(message_parse, "message_fromWire19.wire");

    RRsetIterator it = message_parse.beginSection(Message::SECTION_ANSWER);
    RRsetIterator it_end = message_parse.endSection(Message::SECTION_ANSWER);
    ASSERT_TRUE(it != it_end);
    EXPECT_EQ(RRType::A(), (*it)->getType());
    EXPECT_EQ(2, (*it)->getRdataCount());

    ++it;
    ASSERT_TRUE(it != it_end);
    EXPECT_EQ(RRType::AAAA(), (*it)->getType());
    EXPECT_EQ(1, (*it)->getRdataCount());
}

// A helper function for a test pattern commonly used in several tests below.
void
preserveRRCheck(const Message& message, Message::Section section) {
    RRsetIterator it = message.beginSection(section);
    RRsetIterator it_end = message.endSection(section);
    ASSERT_TRUE(it != it_end);
    EXPECT_EQ(RRType::A(), (*it)->getType());
    EXPECT_EQ(1, (*it)->getRdataCount());
    EXPECT_EQ("192.0.2.1", (*it)->getRdataIterator()->getCurrent().toText());

    ++it;
    ASSERT_TRUE(it != it_end);
    EXPECT_EQ(RRType::AAAA(), (*it)->getType());
    EXPECT_EQ(1, (*it)->getRdataCount());
    EXPECT_EQ("2001:db8::1", (*it)->getRdataIterator()->getCurrent().toText());

    ++it;
    ASSERT_TRUE(it != it_end);
    EXPECT_EQ(RRType::A(), (*it)->getType());
    EXPECT_EQ(1, (*it)->getRdataCount());
    EXPECT_EQ("192.0.2.2", (*it)->getRdataIterator()->getCurrent().toText());
}

TEST_F(MessageTest, fromWirePreserveAnswer) {
    // Using the same data as the previous test, but specify the PRESERVE_ORDER
    // option.  The received order of RRs should be preserved, and each RR
    // should be stored in a single RRset.
    factoryFromFile(message_parse, "message_fromWire19.wire",
                    Message::PRESERVE_ORDER);
    {
        SCOPED_TRACE("preserve answer RRs");
        preserveRRCheck(message_parse, Message::SECTION_ANSWER);
    }
}

TEST_F(MessageTest, fromWirePreserveAuthority) {
    // Same for the previous test, but for the authority section.
    factoryFromFile(message_parse, "message_fromWire20.wire",
                    Message::PRESERVE_ORDER);
    {
        SCOPED_TRACE("preserve authority RRs");
        preserveRRCheck(message_parse, Message::SECTION_AUTHORITY);
    }
}

TEST_F(MessageTest, fromWirePreserveAdditional) {
    // Same for the previous test, but for the additional section.
    factoryFromFile(message_parse, "message_fromWire21.wire",
                    Message::PRESERVE_ORDER);
    {
        SCOPED_TRACE("preserve additional RRs");
        preserveRRCheck(message_parse, Message::SECTION_ADDITIONAL);
    }
}

TEST_F(MessageTest, EDNS0ExtRcode) {
    // Extended Rcode = BADVERS
    factoryFromFile(message_parse, "message_fromWire10.wire");
    EXPECT_EQ(Rcode::BADVERS(), message_parse.getRcode());

    // Maximum extended Rcode
    message_parse.clear(Message::PARSE);
    factoryFromFile(message_parse, "message_fromWire11.wire");
    EXPECT_EQ(0xfff, message_parse.getRcode().getCode());
}

TEST_F(MessageTest, BadEDNS0) {
    // OPT RR in the answer section
    EXPECT_THROW(factoryFromFile(message_parse, "message_fromWire4"),
                 DNSMessageFORMERR);
    // multiple OPT RRs (in the additional section)
    message_parse.clear(Message::PARSE);
    EXPECT_THROW(factoryFromFile(message_parse, "message_fromWire5"),
                 DNSMessageFORMERR);
}

TEST_F(MessageTest, toWire) {
    message_render.setQid(0x1035);
    message_render.setOpcode(Opcode::QUERY());
    message_render.setRcode(Rcode::NOERROR());
    message_render.setHeaderFlag(Message::HEADERFLAG_QR, true);
    message_render.setHeaderFlag(Message::HEADERFLAG_RD, true);
    message_render.setHeaderFlag(Message::HEADERFLAG_AA, true);
    message_render.addQuestion(Question(Name("test.example.com"), RRClass::IN(),
                                        RRType::A()));
    message_render.addRRset(Message::SECTION_ANSWER, rrset_a);

    EXPECT_EQ(1, message_render.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(2, message_render.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_ADDITIONAL));

    message_render.toWire(renderer);
    vector<unsigned char> data;
    UnitTestUtil::readWireData("message_toWire1", data);
    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(MessageTest, toWireSigned) {
    message_render.setQid(0x75c1);
    message_render.setOpcode(Opcode::QUERY());
    message_render.setRcode(Rcode::NOERROR());
    message_render.setHeaderFlag(Message::HEADERFLAG_QR, true);
    message_render.setHeaderFlag(Message::HEADERFLAG_RD, true);
    message_render.setHeaderFlag(Message::HEADERFLAG_AA, true);
    message_render.addQuestion(Question(Name("test.example.com"), RRClass::IN(),
                                        RRType::A()));

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

    message_render.addRRset(Message::SECTION_ANSWER, rrset_a);

    EXPECT_EQ(1, message_render.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(4, message_render.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_ADDITIONAL));

    message_render.toWire(renderer);
    vector<unsigned char> data;
    UnitTestUtil::readWireData("message_toWire6", data);
    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(MessageTest, toWireSignedAndTruncated) {
    message_render.setQid(0x75c1);
    message_render.setOpcode(Opcode::QUERY());
    message_render.setRcode(Rcode::NOERROR());
    message_render.setHeaderFlag(Message::HEADERFLAG_QR, true);
    message_render.setHeaderFlag(Message::HEADERFLAG_RD, true);
    message_render.setHeaderFlag(Message::HEADERFLAG_AA, true);
    message_render.addQuestion(Question(Name("test.example.com"), RRClass::IN(),
                                        RRType::TXT()));

    RRsetPtr rrset_txt = RRsetPtr(new RRset(test_name, RRClass::IN(),
                                            RRType::TXT(), RRTTL(3600)));
    rrset_txt->addRdata(generic::TXT(string(255, 'a')));
    rrset_txt->addRdata(generic::TXT(string(255, 'b')));
    rrset_txt->addRdata(generic::TXT(string(255, 'c')));
    rrset_txt->addRdata(generic::TXT(string(255, 'd')));
    rrset_txt->addRdata(generic::TXT(string(255, 'e')));
    rrset_txt->addRdata(generic::TXT(string(255, 'f')));
    rrset_txt->addRdata(generic::TXT(string(255, 'g')));
    rrset_txt->addRdata(generic::TXT(string(255, 'h')));

    rrset_rrsig = RRsetPtr(new RRset(test_name, RRClass::IN(),
                                     RRType::RRSIG(), RRTTL(3600)));
    // one signature algorithm (5 = RSA/SHA-1)
    rrset_rrsig->addRdata(generic::RRSIG("TXT 5 3 3600 "
                                         "20000101000000 20000201000000 "
                                         "12345 example.com. FAKEFAKEFAKE"));
    rrset_txt->addRRsig(rrset_rrsig);
    EXPECT_EQ(1, rrset_txt->getRRsigDataCount());

    message_render.addRRset(Message::SECTION_ANSWER, rrset_txt);

    EXPECT_EQ(1, message_render.getRRCount(Message::SECTION_QUESTION));
    EXPECT_EQ(9, message_render.getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_AUTHORITY));
    EXPECT_EQ(0, message_render.getRRCount(Message::SECTION_ADDITIONAL));

    message_render.toWire(renderer);
    vector<unsigned char> data;
    UnitTestUtil::readWireData("message_toWire7", data);
    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(MessageTest, toWireInParseMode) {
    // toWire() isn't allowed in the parse mode.
    EXPECT_THROW(message_parse.toWire(renderer), InvalidMessageOperation);
}

// See dnssectime_unittest.cc
template <int64_t NOW>
int64_t
testGetTime() {
    return (NOW);
}

// bit-wise constant flags to configure DNS header flags for test
// messages.
const unsigned int QR_FLAG = 0x1;
const unsigned int AA_FLAG = 0x2;
const unsigned int RD_FLAG = 0x4;

void
commonTSIGToWireCheck(Message& message, MessageRenderer& renderer,
                      TSIGContext& tsig_ctx, const char* const expected_file,
                      unsigned int message_flags = RD_FLAG,
                      RRType qtype = RRType::A(),
                      const vector<const char*>* answer_data = NULL)
{
    message.setOpcode(Opcode::QUERY());
    message.setRcode(Rcode::NOERROR());
    if ((message_flags & QR_FLAG) != 0) {
        message.setHeaderFlag(Message::HEADERFLAG_QR);
    }
    if ((message_flags & AA_FLAG) != 0) {
        message.setHeaderFlag(Message::HEADERFLAG_AA);
    }
    if ((message_flags & RD_FLAG) != 0) {
        message.setHeaderFlag(Message::HEADERFLAG_RD);
    }
    message.addQuestion(Question(Name("www.example.com"), RRClass::IN(),
                                 qtype));

    if (answer_data != NULL) {
        RRsetPtr ans_rrset(new RRset(Name("www.example.com"), RRClass::IN(),
                                     qtype, RRTTL(86400)));
        for (vector<const char*>::const_iterator it = answer_data->begin();
             it != answer_data->end();
             ++it) {
            ans_rrset->addRdata(createRdata(qtype, RRClass::IN(), *it));
        }
        message.addRRset(Message::SECTION_ANSWER, ans_rrset);
    }

    message.toWire(renderer, &tsig_ctx);
    vector<unsigned char> expected_data;
    UnitTestUtil::readWireData(expected_file, expected_data);
    matchWireData(&expected_data[0], expected_data.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(MessageTest, toWireWithTSIG) {
    // Rendering a message with TSIG.  Various special cases specific to
    // TSIG are tested in the tsig tests.  We only check the message contains
    // a TSIG at the end and the ARCOUNT of the header is updated.

    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    message_render.setQid(0x2d65);

    {
        SCOPED_TRACE("Message sign with TSIG");
        commonTSIGToWireCheck(message_render, renderer, tsig_ctx,
                              "message_toWire2.wire");
    }
}

TEST_F(MessageTest, toWireWithEDNSAndTSIG) {
    // Similar to the previous test, but with an EDNS before TSIG.
    // The wire data check will confirm the ordering.
    isc::util::detail::gettimeFunction = testGetTime<0x4db60d1f>;

    message_render.setQid(0x6cd);

    EDNSPtr edns(new EDNS());
    edns->setUDPSize(4096);
    message_render.setEDNS(edns);

    {
        SCOPED_TRACE("Message sign with TSIG and EDNS");
        commonTSIGToWireCheck(message_render, renderer, tsig_ctx,
                              "message_toWire3.wire");
    }
}

// Some of the following tests involve truncation.  We use the query name
// "www.example.com" and some TXT question/answers.  The length of the
// header and question will be 33 bytes.  If we also try to include a
// TSIG of the same key name (not compressed) with HMAC-MD5, the TSIG RR
// will be 85 bytes.

// A long TXT RDATA.  With a fully compressed owner name, the corresponding
// RR will be 268 bytes.
const char* const long_txt1 = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcde";

// With a fully compressed owner name, the corresponding RR will be 212 bytes.
// It should result in truncation even without TSIG (33 + 268 + 212 = 513)
const char* const long_txt2 = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456";

// With a fully compressed owner name, the corresponding RR will be 127 bytes.
// So, it can fit in the standard 512 bytes with txt1 and without TSIG, but
// adding a TSIG would result in truncation (33 + 268 + 127 + 85 = 513)
const char* const long_txt3 = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef01";

// This is 1 byte shorter than txt3, which will result in a possible longest
// message containing answer RRs and TSIG.
const char* const long_txt4 = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0";

// Example output generated by
// "dig -y www.example.com:SFuWd/q99SzF8Yzd1QbB9g== www.example.com txt
// QID: 0x22c2
// Time Signed: 0x00004e179212
TEST_F(MessageTest, toWireTSIGTruncation) {
    isc::util::detail::gettimeFunction = testGetTime<0x4e179212>;

    // Verify a validly signed query so that we can use the TSIG context

    factoryFromFile(message_parse, "message_fromWire17.wire");
    EXPECT_EQ(TSIGError::NOERROR(),
              tsig_ctx.verify(message_parse.getTSIGRecord(),
                              &received_data[0], received_data.size()));

    message_render.setQid(0x22c2);
    vector<const char*> answer_data;
    answer_data.push_back(long_txt1);
    answer_data.push_back(long_txt2);
    {
        SCOPED_TRACE("Message sign with TSIG and TC bit on");
        commonTSIGToWireCheck(message_render, renderer, tsig_ctx,
                              "message_toWire4.wire",
                              QR_FLAG|AA_FLAG|RD_FLAG,
                              RRType::TXT(), &answer_data);
    }
}

TEST_F(MessageTest, toWireTSIGTruncation2) {
    // Similar to the previous test, but without TSIG it wouldn't cause
    // truncation.
    isc::util::detail::gettimeFunction = testGetTime<0x4e179212>;
    factoryFromFile(message_parse, "message_fromWire17.wire");
    EXPECT_EQ(TSIGError::NOERROR(),
              tsig_ctx.verify(message_parse.getTSIGRecord(),
                              &received_data[0], received_data.size()));

    message_render.setQid(0x22c2);
    vector<const char*> answer_data;
    answer_data.push_back(long_txt1);
    answer_data.push_back(long_txt3);
    {
        SCOPED_TRACE("Message sign with TSIG and TC bit on (2)");
        commonTSIGToWireCheck(message_render, renderer, tsig_ctx,
                              "message_toWire4.wire",
                              QR_FLAG|AA_FLAG|RD_FLAG,
                              RRType::TXT(), &answer_data);
    }
}

TEST_F(MessageTest, toWireTSIGTruncation3) {
    // Similar to previous ones, but truncation occurs due to too many
    // Questions (very unusual, but not necessarily illegal).

    // We are going to create a message starting with a standard
    // header (12 bytes) and multiple questions in the Question
    // section of the same owner name (changing the RRType, just so
    // that it would be the form that would be accepted by the BIND 9
    // parser).  The first Question is 21 bytes in length, and the subsequent
    // ones are 6 bytes.  We'll also use a TSIG whose size is 85 bytes.
    // Up to 66 questions can fit in the standard 512-byte buffer
    // (12 + 21 + 6 * 65 + 85 = 508).  If we try to add one more it would
    // result in truncation.
    message_render.setOpcode(Opcode::QUERY());
    message_render.setRcode(Rcode::NOERROR());
    for (int i = 1; i <= 67; ++i) {
        message_render.addQuestion(Question(Name("www.example.com"),
                                            RRClass::IN(), RRType(i)));
    }
    message_render.toWire(renderer, &tsig_ctx);

    // Check the rendered data by parsing it.  We only check it has the
    // TC bit on, has the correct number of questions, and has a TSIG RR.
    // Checking the signature wouldn't be necessary for this rare case
    // scenario.
    InputBuffer buffer(renderer.getData(), renderer.getLength());
    message_parse.fromWire(buffer);
    EXPECT_TRUE(message_parse.getHeaderFlag(Message::HEADERFLAG_TC));
    // Note that the number of questions are 66, not 67 as we tried to add.
    EXPECT_EQ(66, message_parse.getRRCount(Message::SECTION_QUESTION));
    EXPECT_TRUE(message_parse.getTSIGRecord() != NULL);
}

TEST_F(MessageTest, toWireTSIGNoTruncation) {
    // A boundary case that shouldn't cause truncation: the resulting
    // response message with a TSIG will be 512 bytes long.
    isc::util::detail::gettimeFunction = testGetTime<0x4e17b38d>;
    factoryFromFile(message_parse, "message_fromWire18.wire");
    EXPECT_EQ(TSIGError::NOERROR(),
              tsig_ctx.verify(message_parse.getTSIGRecord(),
                              &received_data[0], received_data.size()));

    message_render.setQid(0xd6e2);
    vector<const char*> answer_data;
    answer_data.push_back(long_txt1);
    answer_data.push_back(long_txt4);
    {
        SCOPED_TRACE("Message sign with TSIG, no truncation");
        commonTSIGToWireCheck(message_render, renderer, tsig_ctx,
                              "message_toWire5.wire",
                              QR_FLAG|AA_FLAG|RD_FLAG,
                              RRType::TXT(), &answer_data);
    }
}

// This is a buggy renderer for testing.  It behaves like the straightforward
// MessageRenderer, but once it has some data, its setLengthLimit() ignores
// the given parameter and resets the limit to the current length, making
// subsequent insertion result in truncation, which would make TSIG RR
// rendering fail unexpectedly in the test that follows.
class BadRenderer : public MessageRenderer {
public:
    virtual void setLengthLimit(size_t len) {
        if (getLength() > 0) {
            MessageRenderer::setLengthLimit(getLength());
        } else {
            MessageRenderer::setLengthLimit(len);
        }
    }
};

TEST_F(MessageTest, toWireTSIGLengthErrors) {
    // specify an unusual short limit that wouldn't be able to hold
    // the TSIG.
    renderer.setLengthLimit(tsig_ctx.getTSIGLength() - 1);
    // Use commonTSIGToWireCheck() only to call toWire() with otherwise valid
    // conditions.  The checks inside it don't matter because we expect an
    // exception before any of the checks.
    EXPECT_THROW(commonTSIGToWireCheck(message_render, renderer, tsig_ctx,
                                       "message_toWire2.wire"),
                 InvalidParameter);

    // This one is large enough for TSIG, but the remaining limit isn't
    // even enough for the Header section.
    renderer.clear();
    message_render.clear(Message::RENDER);
    renderer.setLengthLimit(tsig_ctx.getTSIGLength() + 1);
    EXPECT_THROW(commonTSIGToWireCheck(message_render, renderer, tsig_ctx,
                                       "message_toWire2.wire"),
                 InvalidParameter);

    // Trying to render a message with TSIG using a buggy renderer.
    BadRenderer bad_renderer;
    bad_renderer.setLengthLimit(512);
    message_render.clear(Message::RENDER);
    EXPECT_THROW(commonTSIGToWireCheck(message_render, bad_renderer, tsig_ctx,
                                       "message_toWire2.wire"),
                 Unexpected);
}

TEST_F(MessageTest, toWireWithoutOpcode) {
    message_render.setRcode(Rcode::NOERROR());
    EXPECT_THROW(message_render.toWire(renderer), InvalidMessageOperation);
}

TEST_F(MessageTest, toWireWithoutRcode) {
    message_render.setOpcode(Opcode::QUERY());
    EXPECT_THROW(message_render.toWire(renderer), InvalidMessageOperation);
}

TEST_F(MessageTest, toText) {
    // Check toText() output for a typical DNS response with records in
    // all sections

    factoryFromFile(message_parse, "message_toText1.wire");
    {
        SCOPED_TRACE("Message toText test (basic case)");
        ifstream ifs;
        unittests::openTestData("message_toText1.txt", ifs);
        unittests::matchTextData(ifs, message_parse.toText());
    }

    // Another example with EDNS.  The expected data was slightly modified
    // from the dig output (other than replacing tabs with a space): adding
    // a newline after the "OPT PSEUDOSECTION".  This is an intentional change
    // in our version for better readability.
    message_parse.clear(Message::PARSE);
    factoryFromFile(message_parse, "message_toText2.wire");
    {
        SCOPED_TRACE("Message toText test with EDNS");
        ifstream ifs;
        unittests::openTestData("message_toText2.txt", ifs);
        unittests::matchTextData(ifs, message_parse.toText());
    }

    // Another example with TSIG.  The expected data was slightly modified
    // from the dig output (other than replacing tabs with a space): removing
    // a redundant white space at the end of TSIG RDATA.  We'd rather consider
    // it a dig's defect than a feature.
    message_parse.clear(Message::PARSE);
    factoryFromFile(message_parse, "message_toText3.wire");
    {
        SCOPED_TRACE("Message toText test with TSIG");
        ifstream ifs;
        unittests::openTestData("message_toText3.txt", ifs);
        unittests::matchTextData(ifs, message_parse.toText());
    }
}

TEST_F(MessageTest, toTextWithoutOpcode) {
    message_render.setRcode(Rcode::NOERROR());
    EXPECT_THROW(message_render.toText(), InvalidMessageOperation);
}

TEST_F(MessageTest, toTextWithoutRcode) {
    message_render.setOpcode(Opcode::QUERY());
    EXPECT_THROW(message_render.toText(), InvalidMessageOperation);
}
}
