// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/time_utils.h>
#include <dns/tsig.h>

#include <gss_tsig_api.h>
#include <gss_tsig_api_utils.h>
#include <testutils/gtest_utils.h>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::dns::rdata::generic;
using namespace isc::gss_tsig;
using namespace isc::gss_tsig::test;
using namespace isc::util;

namespace {

/// @brief Test fixture for testing the GSS-API with Kerberos 5.
class TKeyTest : public GssApiBaseTest {
public:
    /// @brief Constructor.
    TKeyTest() : GssApiBaseTest(), msg_() {
    }

    /// @brief Build a TKEY message.
    ///
    /// @param query True if query, false if response.
    /// @param qid Message ID.
    /// @param key_name DNS name of the key.
    /// @param token GSS-API token.
    /// @return The output buffer with the TKEY message.
    OutputBufferPtr buildTKey(bool query, qid_t qid, const Name& key_name,
                              GssApiBuffer& token);

    /// @brief Decode a TKEY message.
    ///
    /// @param input Input buffer.
    /// @param[out] query True if query, false if response.
    /// @param[out] qid Message ID.
    /// @param[out] key_name DNS name of the key.
    /// @param[out] token Pointer to GSS-API token.
    void decodeTKey(const vector<uint8_t>& input, bool& query, qid_t& qid,
                    Name& key_name, GssApiBufferPtr& token);

    /// @brief Pointer to the current message.
    MessagePtr msg_;
};

OutputBufferPtr
TKeyTest::buildTKey(bool query, qid_t qid, const Name& key_name,
                    GssApiBuffer& token) {
    msg_.reset(new Message(Message::RENDER));
    msg_->setHeaderFlag(Message::HEADERFLAG_QR, query);
    msg_->setQid(qid);
    msg_->setRcode(Rcode::NOERROR());
    msg_->setOpcode(Opcode(Opcode::QUERY_CODE));
    Question question(key_name, RRClass::ANY(), RRType::TKEY());
    msg_->addQuestion(question);
    RRsetPtr rrset(new RRset(key_name, RRClass::ANY(), RRType::TKEY(),
                             RRTTL(0)));
    Name algorithm("gss-tsig.");
    uint32_t inception = timeFromText32("20210501120000");
    uint32_t expire = timeFromText32("20210501130000");
    uint16_t mode = TKEY::GSS_API_MODE;
    uint16_t error = Rcode::NOERROR().getCode();
    uint16_t key_len = static_cast<uint16_t>(token.getLength());
    ConstRdataPtr rdata(new TKEY(algorithm, inception, expire,
                                 mode, error, key_len,
                                 token.getValue(), 0, 0));
    rrset->addRdata(rdata);
    msg_->addRRset(Message::SECTION_ADDITIONAL, rrset);
    MessageRenderer renderer;
    OutputBufferPtr buf(new OutputBuffer(4096));
    renderer.setBuffer(buf.get());
    EXPECT_NO_THROW(msg_->toWire(renderer));
    return (buf);
}

void
TKeyTest::decodeTKey(const vector<uint8_t>& input, bool& query, qid_t& qid,
                     Name& key_name, GssApiBufferPtr& token) {
    msg_.reset(new Message(Message::PARSE));
    ASSERT_FALSE(input.empty());
    InputBuffer buf(&input[0], input.size());
    EXPECT_NO_THROW(msg_->fromWire(buf));
    query = msg_->getHeaderFlag(Message::HEADERFLAG_QR);
    qid = msg_->getQid();
    EXPECT_EQ(Rcode::NOERROR(), msg_->getRcode());
    EXPECT_EQ(Opcode(Opcode::QUERY_CODE), msg_->getOpcode());
    ASSERT_EQ(1, msg_->getRRCount(Message::SECTION_QUESTION));
    QuestionPtr question = *msg_->beginQuestion();
    ASSERT_TRUE(question);
    key_name = question->getName();
    EXPECT_EQ(RRClass::ANY(), question->getClass());
    EXPECT_EQ(RRType::TKEY(), question->getType());
    EXPECT_EQ(0, msg_->getRRCount(Message::SECTION_ANSWER));
    EXPECT_EQ(0, msg_->getRRCount(Message::SECTION_AUTHORITY));
    ASSERT_EQ(1, msg_->getRRCount(Message::SECTION_ADDITIONAL));
    RRsetPtr rrset = *msg_->beginSection(Message::SECTION_ADDITIONAL);
    ASSERT_TRUE(rrset);
    EXPECT_EQ(key_name, rrset->getName());
    EXPECT_EQ(RRClass::ANY(), rrset->getClass());
    ASSERT_EQ(RRType::TKEY(), rrset->getType());
    EXPECT_EQ(RRTTL(0), rrset->getTTL());
    ASSERT_EQ(1, rrset->getRdataCount());
    auto rdata_it = rrset->getRdataIterator();
    try {
        const TKEY& tkey =
            dynamic_cast<const TKEY&>(rdata_it->getCurrent());
        EXPECT_EQ(Name("gss-tsig."), tkey.getAlgorithm());
        EXPECT_EQ("20210501120000", tkey.getInceptionDate());
        EXPECT_EQ("20210501130000", tkey.getExpireDate());
        EXPECT_EQ(TKEY::GSS_API_MODE, tkey.getMode());
        EXPECT_EQ(Rcode::NOERROR().getCode(), tkey.getError());
        token.reset(new GssApiBuffer(tkey.getKeyLen(), tkey.getKey()));
        EXPECT_EQ(0, tkey.getOtherLen());
        EXPECT_FALSE(tkey.getOtherData());
    } catch (const exception& ex) {
        FAIL() << ex.what();
    }
}

/// @brief Check TKEY message build.
TEST_F(TKeyTest, build) {
    Name key_name("1234.sig-blu.example.nil.");
    qid_t qid = 0x4567;
    GssApiBuffer token("foobar");
    OutputBufferPtr output;
    msg_.reset();
    ASSERT_NO_THROW(output = buildTKey(true, qid, key_name, token));
    ASSERT_TRUE(msg_);
    ASSERT_NE(0, output->getLength());
}

/// @brief Check TKEY message decode.
TEST_F(TKeyTest, decode) {
    Name key_name("1234.sig-blu.example.nil.");
    qid_t qid = 0x4567;
    GssApiBuffer token("foobar");
    OutputBufferPtr output;
    ASSERT_NO_THROW(output = buildTKey(true, qid, key_name, token));
    ASSERT_NE(0, output->getLength());

    const vector<uint8_t>& input = output->getVector();
    bool query = false;
    qid_t qid2 = 0;
    Name key_name2("foo");
    GssApiBufferPtr token2;
    msg_.reset();
    EXPECT_NO_THROW(decodeTKey(input, query, qid2, key_name2, token2));
    ASSERT_TRUE(msg_);
    EXPECT_TRUE(query);
    EXPECT_EQ(qid, qid2);
    EXPECT_EQ(key_name, key_name2);
    ASSERT_TRUE(token2);
    EXPECT_EQ("foobar", token2->getString());
}

}
