// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dns/name.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <gss_tsig_context.h>
#include <gss_tsig_api_utils.h>
#include <testutils/gtest_utils.h>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::cryptolink;
using namespace isc::dns;
using namespace isc::dns::rdata::any;
using namespace isc::gss_tsig;
using namespace isc::gss_tsig::test;
using namespace isc::util;

/// @todo this is defined as class static constants, but some compilers
/// seemingly cannot find the symbol when used in the EXPECT_xxx macros.
const uint16_t TSIGContext::DEFAULT_FUDGE;

namespace {

/// @brief Test fixture for testing the GSS-TSIG key.
class GssTsigContextTest : public GssApiBaseTest {
public:
    /// @brief Constructor.
    GssTsigContextTest() : GssApiBaseTest(), message_(Message::RENDER) {
    }

    /// @brief Destructor.
    ~GssTsigContextTest() {
    }

    /// @brief The message used for signing.
    Message message_;
};

/// @brief Check the constructor builds what is expected.
TEST_F(GssTsigContextTest, basic) {
    GssTsigKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(key);
    GssTsigContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*key)));
    ASSERT_TRUE(ctx);

    // Verify context.
    EXPECT_EQ(TSIGContext::INIT, ctx->getState());
    EXPECT_EQ(TSIGError::NOERROR(), ctx->getError());
    // Length is 26 + 26 + 10 + 128 + 0 = 190.
    EXPECT_EQ(190, ctx->getTSIGLength());
}

/// @brief Check sign direct errors.
TEST_F(GssTsigContextTest, signError) {
    GssTsigKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(key);
    GssTsigContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*key)));
    ASSERT_TRUE(ctx);

    // VERIFIED_RESPONSE state is not allowed.
    ctx->setState(TSIGContext::VERIFIED_RESPONSE);
    EXPECT_EQ(TSIGContext::VERIFIED_RESPONSE, ctx->getState());
    EXPECT_THROW_MSG(ctx->sign(0x1234, 0, 0), TSIGContextError,
                     "TSIG sign attempt after verifying a response");

    // Data must not be empty.
    ctx->setState(TSIGContext::INIT);
    EXPECT_THROW_MSG(ctx->sign(0x1234, 0, 100), InvalidParameter,
                     "TSIG sign error: empty data is given");
    EXPECT_THROW_MSG(ctx->sign(0x1234, &name[0], 0), InvalidParameter,
                     "TSIG sign error: empty data is given");
}

/// @brief Check verify direct errors.
TEST_F(GssTsigContextTest, verifyError) {
    GssTsigKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(key);
    GssTsigContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*key)));
    ASSERT_TRUE(ctx);

    // SENT_RESPONSE state is not allowed.
    ctx->setState(TSIGContext::SENT_RESPONSE);
    EXPECT_EQ(TSIGContext::SENT_RESPONSE, ctx->getState());
    EXPECT_THROW_MSG(ctx->verify(0, 0, 0), TSIGContextError,
                     "TSIG verify attempt after sending a response");
}

/// @brief Check lastHadSignature requires some history.
TEST_F(GssTsigContextTest, lastHadSignature) {
    GssTsigKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(key);
    GssTsigContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*key)));
    ASSERT_TRUE(ctx);

    EXPECT_THROW_MSG(ctx->lastHadSignature(), TSIGContextError,
                     "No message was verified yet");
}

/// @brief Check unsigned response.
TEST_F(GssTsigContextTest, unsigned) {
    GssTsigKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(key);
    GssTsigContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*key)));
    ASSERT_TRUE(ctx);

    // BAD_SIG gives an unsigned response.
    ctx->setError(TSIGError::BAD_SIG());
    ctx->setState(TSIGContext::RECEIVED_REQUEST);
    EXPECT_EQ(TSIGError::BAD_SIG(), ctx->getError());
    ConstTSIGRecordPtr tsig;
    const string& dummy = "dummy";
    uint64_t before = static_cast<uint64_t>(time(0));
    ASSERT_NO_THROW(tsig = ctx->sign(0x1234, dummy.c_str(), dummy.size()));
    uint64_t after = static_cast<uint64_t>(time(0));
    ASSERT_TRUE(tsig);
    EXPECT_EQ(Name(name), tsig->getName());
    EXPECT_EQ(RRClass::ANY(), tsig->getClass());
    EXPECT_EQ(0, tsig->getTTL().getValue());
    // Length is 26 + 26 + 10 = 62.
    EXPECT_EQ(62, tsig->getLength());
    const TSIG& rdata = tsig->getRdata();
    EXPECT_EQ(Name("gss-tsig."), rdata.getAlgorithm());
    EXPECT_LE(before, rdata.getTimeSigned());
    EXPECT_GE(after, rdata.getTimeSigned());
    EXPECT_EQ(TSIGContext::DEFAULT_FUDGE, rdata.getFudge());
    EXPECT_EQ(0, rdata.getMACSize());
    EXPECT_FALSE(rdata.getMAC());
    EXPECT_EQ(0x1234, rdata.getOriginalID());
    EXPECT_EQ(TSIGError::BAD_SIG_CODE, rdata.getError());
    EXPECT_EQ(0, rdata.getOtherLen());
    EXPECT_FALSE(rdata.getOtherData());
    EXPECT_EQ(TSIGContext::SENT_RESPONSE, ctx->getState());
    EXPECT_EQ(TSIGError::BAD_SIG(), ctx->getError());

    // Reset the context.
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*key)));
    ASSERT_TRUE(ctx);

    // BAD_KEY also gives an unsigned response.
    ctx->setError(TSIGError::BAD_KEY());
    ctx->setState(TSIGContext::RECEIVED_REQUEST);
    EXPECT_EQ(TSIGError::BAD_KEY(), ctx->getError());
    before = static_cast<uint64_t>(time(0));
    ASSERT_NO_THROW(tsig = ctx->sign(0x1234, dummy.c_str(), dummy.size()));
    after = static_cast<uint64_t>(time(0));
    ASSERT_TRUE(tsig);
    EXPECT_EQ(Name(name), tsig->getName());
    EXPECT_EQ(RRClass::ANY(), tsig->getClass());
    EXPECT_EQ(0, tsig->getTTL().getValue());
    // Length is 26 + 26 + 10 = 62.
    EXPECT_EQ(62, tsig->getLength());
    const TSIG& rdata2 = tsig->getRdata();
    EXPECT_EQ(Name("gss-tsig."), rdata2.getAlgorithm());
    EXPECT_LE(before, rdata2.getTimeSigned());
    EXPECT_GE(after, rdata2.getTimeSigned());
    EXPECT_EQ(TSIGContext::DEFAULT_FUDGE, rdata2.getFudge());
    EXPECT_EQ(0, rdata2.getMACSize());
    EXPECT_FALSE(rdata2.getMAC());
    EXPECT_EQ(0x1234, rdata2.getOriginalID());
    EXPECT_EQ(TSIGError::BAD_KEY_CODE, rdata2.getError());
    EXPECT_EQ(0, rdata2.getOtherLen());
    EXPECT_FALSE(rdata2.getOtherData());
    EXPECT_EQ(TSIGContext::SENT_RESPONSE, ctx->getState());
    EXPECT_EQ(TSIGError::BAD_KEY(), ctx->getError());
}

/// @brief Check that a security context is required to sign.
TEST_F(GssTsigContextTest, signNoSecCtx) {
    GssTsigKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(key);
    GssTsigContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*key)));
    ASSERT_TRUE(ctx);

    const string& dummy = "dummy";
    EXPECT_THROW_MSG(ctx->sign(0x1234, dummy.c_str(), dummy.size()),
                     Unexpected,
                     "sign called with null security context");
}

/// @brief Check that verify no TSIG record is only for continuation.
TEST_F(GssTsigContextTest, verifyNoRecord) {
    GssTsigKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(key);
    GssTsigContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*key)));
    ASSERT_TRUE(ctx);

    const string& dummy = "dummy";
    TSIGError error = TSIGError::NOERROR();
    EXPECT_NO_THROW(error = ctx->verify(0, dummy.c_str(), dummy.size()));
    EXPECT_EQ(TSIGError::FORMERR(), error);
    EXPECT_EQ(TSIGContext::RECEIVED_REQUEST, ctx->getState());
    EXPECT_EQ(TSIGError::FORMERR(), ctx->getError());
}

/// @brief Check that verify rejects too short data.
TEST_F(GssTsigContextTest, verifyBadData) {
    GssTsigKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(key);
    GssTsigContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*key)));
    ASSERT_TRUE(ctx);

    const uint64_t now = static_cast<uint64_t>(time(0));
    ConstTSIGRecordPtr tsig(new
        TSIGRecord(key->getKeyName(),
                   TSIG(key->getAlgorithmName(),
                        now, TSIGContext::DEFAULT_FUDGE, 0, 0,
                        0x1234, 0, 0, 0)));

    const size_t MESSAGE_HEADER_LEN = 12;
    size_t len = MESSAGE_HEADER_LEN + tsig->getLength();
    // len is 12 + 26 + 26 + 10 = 74.
    EXPECT_EQ(74, len);
    EXPECT_THROW_MSG(ctx->verify(tsig.get(), 0, len - 1), InvalidParameter,
                     "TSIG verify: data length is invalid: 73");
    EXPECT_THROW_MSG(ctx->verify(tsig.get(), 0, len), InvalidParameter,
                     "TSIG verify: empty data is invalid");
}

/// @brief Check that a security context is required to verify.
TEST_F(GssTsigContextTest, verifyNoSecCtx) {
    GssTsigKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(key);
    GssTsigContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*key)));
    ASSERT_TRUE(ctx);

    const uint64_t now = static_cast<uint64_t>(time(0));
    ConstTSIGRecordPtr tsig(new
        TSIGRecord(key->getKeyName(),
                   TSIG(key->getAlgorithmName(),
                        now, TSIGContext::DEFAULT_FUDGE, 0, 0,
                        0x1234, 0, 0, 0)));

    const size_t MESSAGE_HEADER_LEN = 12;
    size_t len = MESSAGE_HEADER_LEN + tsig->getLength();
    string dummy(len, ' ');
    EXPECT_THROW_MSG(ctx->verify(tsig.get(), dummy.c_str(), len), Unexpected,
                     "verify called with null security context");
}

/// @brief Check that sign works as expected.
TEST_F(GssTsigContextTest, sign) {
    GssTsigKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(key);

    setKeytab();
    setAdministratorCCache();

    // Server.
    GssApiName srv_name("DNS/blu.example.nil@EXAMPLE.NIL");
    OM_uint32 lifetime = 0;
    GssApiCredPtr srv_cred(new GssApiCred(srv_name, GSS_C_ACCEPT, lifetime));
    GssApiSecCtx srv_ctx(GSS_C_NO_CONTEXT);

    // Client.
    GssApiName clnt_name;
    GssApiCredPtr cred;
    EXPECT_FALSE(key->getSecCtx().get());
    OM_uint32 flags = GSS_C_REPLAY_FLAG | GSS_C_MUTUAL_FLAG | GSS_C_INTEG_FLAG;
    bool ret = false;

    // Exchanges.
    GssApiBuffer intoken0;
    GssApiBuffer outtoken0;
    ASSERT_NO_THROW(ret = key->getSecCtx().init(cred, srv_name, flags,
                                                intoken0, outtoken0,
                                                lifetime));
    ASSERT_FALSE(outtoken0.empty());
    GssApiBuffer outtoken1;
    ASSERT_NO_THROW(ret = srv_ctx.accept(*srv_cred, outtoken0, clnt_name,
                                         outtoken1));
    EXPECT_TRUE(ret);
    GssApiBuffer outtoken2;
    ASSERT_NO_THROW(ret = key->getSecCtx().init(cred, srv_name, flags,
                                                outtoken1, outtoken2,
                                                lifetime));
    ASSERT_TRUE(ret);
    EXPECT_TRUE(outtoken2.empty());

    // Build the message to sign.
    message_.clear(Message::RENDER);
    message_.setQid(0x1234);
    message_.setOpcode(Opcode::QUERY());
    message_.setRcode(Rcode::NOERROR());
    message_.setHeaderFlag(Message::HEADERFLAG_QR);
    Name qname("foo.example.nil.");
    message_.addQuestion(Question(qname, RRClass::IN(), RRType::A()));
    MessageRenderer renderer;
    OutputBuffer buf(1024);
    renderer.setBuffer(&buf);
    EXPECT_NO_THROW(message_.toWire(renderer));
    // len is 12 + 17 + 4 = 33
    ASSERT_TRUE(buf.getData());
    EXPECT_EQ(33, buf.getLength());

    // Sign.
    GssTsigContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*key)));
    ASSERT_TRUE(ctx);
    ConstTSIGRecordPtr tsig;
    uint64_t before = static_cast<uint64_t>(time(0));
    EXPECT_NO_THROW(tsig = ctx->sign(0x4321, buf.getData(), buf.getLength()));
    uint64_t after = static_cast<uint64_t>(time(0));
    ASSERT_TRUE(tsig);
    EXPECT_EQ(Name(name), tsig->getName());
    EXPECT_EQ(RRClass::ANY(), tsig->getClass());
    EXPECT_EQ(0, tsig->getTTL().getValue());
    EXPECT_LT(62, tsig->getLength());
    const TSIG& rdata = tsig->getRdata();
    EXPECT_EQ(Name("gss-tsig."), rdata.getAlgorithm());
    EXPECT_LE(before, rdata.getTimeSigned());
    EXPECT_GE(after, rdata.getTimeSigned());
    EXPECT_EQ(TSIGContext::DEFAULT_FUDGE, rdata.getFudge());
    EXPECT_EQ(tsig->getLength() - 62, rdata.getMACSize());
    EXPECT_TRUE(rdata.getMAC());
    EXPECT_EQ(0x4321, rdata.getOriginalID());
    EXPECT_EQ(0, rdata.getError());
    EXPECT_EQ(0, rdata.getOtherLen());
    EXPECT_FALSE(rdata.getOtherData());
    EXPECT_EQ(TSIGContext::SENT_REQUEST, ctx->getState());
    EXPECT_EQ(TSIGError::NOERROR(), ctx->getError());

    // Depend on setup.
    EXPECT_EQ(28, rdata.getMACSize());
}

/// @brief Check that toWire with sign works as expected.
TEST_F(GssTsigContextTest, signToWire) {
    GssTsigKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(key);

    setKeytab();
    setAdministratorCCache();

    // Server.
    GssApiName srv_name("DNS/blu.example.nil@EXAMPLE.NIL");
    OM_uint32 lifetime = 0;
    GssApiCredPtr srv_cred(new GssApiCred(srv_name, GSS_C_ACCEPT, lifetime));
    GssApiSecCtx srv_ctx(GSS_C_NO_CONTEXT);

    // Client.
    GssApiName clnt_name;
    GssApiCredPtr cred;
    EXPECT_FALSE(key->getSecCtx().get());
    OM_uint32 flags = GSS_C_REPLAY_FLAG | GSS_C_MUTUAL_FLAG | GSS_C_INTEG_FLAG;
    bool ret = false;

    // Exchanges.
    GssApiBuffer intoken0;
    GssApiBuffer outtoken0;
    ASSERT_NO_THROW(ret = key->getSecCtx().init(cred, srv_name, flags,
                                                intoken0, outtoken0,
                                                lifetime));
    ASSERT_FALSE(outtoken0.empty());
    GssApiBuffer outtoken1;
    ASSERT_NO_THROW(ret = srv_ctx.accept(*srv_cred, outtoken0, clnt_name,
                                         outtoken1));
    EXPECT_TRUE(ret);
    GssApiBuffer outtoken2;
    ASSERT_NO_THROW(ret = key->getSecCtx().init(cred, srv_name, flags,
                                                outtoken1, outtoken2,
                                                lifetime));
    ASSERT_TRUE(ret);
    EXPECT_TRUE(outtoken2.empty());

    // Build the message to sign.
    message_.clear(Message::RENDER);
    message_.setQid(0x1234);
    message_.setOpcode(Opcode::QUERY());
    message_.setRcode(Rcode::NOERROR());
    message_.setHeaderFlag(Message::HEADERFLAG_QR);
    Name qname("foo.example.nil.");
    message_.addQuestion(Question(qname, RRClass::IN(), RRType::A()));
    MessageRenderer renderer;
    OutputBuffer obuf(1024);
    renderer.setBuffer(&obuf);

    // Sign.
    GssTsigContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*key)));
    ASSERT_TRUE(ctx);
    uint64_t before = static_cast<uint64_t>(time(0));
    EXPECT_NO_THROW(message_.toWire(renderer, ctx.get()));
    uint64_t after = static_cast<uint64_t>(time(0));
    // len is 33 + 62 + 28 = 123.
    ASSERT_TRUE(obuf.getData());
    EXPECT_EQ(123, obuf.getLength());

    // Check the TSIG RR.
    message_.clear(Message::PARSE);
    InputBuffer ibuf(obuf.getData(), obuf.getLength());
    EXPECT_NO_THROW(message_.fromWire(ibuf));
    const TSIGRecord* tsig = message_.getTSIGRecord();
    ASSERT_TRUE(tsig);
    EXPECT_EQ(Name(name), tsig->getName());
    EXPECT_EQ(RRClass::ANY(), tsig->getClass());
    EXPECT_EQ(0, tsig->getTTL().getValue());
    EXPECT_LT(62, tsig->getLength());
    const TSIG& rdata = tsig->getRdata();
    EXPECT_EQ(Name("gss-tsig."), rdata.getAlgorithm());
    EXPECT_LE(before, rdata.getTimeSigned());
    EXPECT_GE(after, rdata.getTimeSigned());
    EXPECT_EQ(TSIGContext::DEFAULT_FUDGE, rdata.getFudge());
    EXPECT_EQ(tsig->getLength() - 62, rdata.getMACSize());
    EXPECT_TRUE(rdata.getMAC());
    EXPECT_EQ(0x1234, rdata.getOriginalID());
    EXPECT_EQ(0, rdata.getError());
    EXPECT_EQ(0, rdata.getOtherLen());
    EXPECT_FALSE(rdata.getOtherData());
    EXPECT_EQ(TSIGContext::SENT_REQUEST, ctx->getState());
    EXPECT_EQ(TSIGError::NOERROR(), ctx->getError());

    // Depend on setup.
    EXPECT_EQ(28, rdata.getMACSize());
}

/// @brief Check that sign and verify work as expected.
TEST_F(GssTsigContextTest, signVerify) {
    GssTsigKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(key);

    setKeytab();
    setAdministratorCCache();

    // Server.
    GssTsigKeyPtr srv_key;
    ASSERT_NO_THROW(srv_key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(srv_key);
    EXPECT_FALSE(srv_key->getSecCtx().get());
    GssApiName srv_name("DNS/blu.example.nil@EXAMPLE.NIL");
    OM_uint32 lifetime = 0;
    GssApiCredPtr srv_cred(new GssApiCred(srv_name, GSS_C_ACCEPT, lifetime));

    // Client.
    GssApiName clnt_name;
    GssApiCredPtr cred;
    EXPECT_FALSE(key->getSecCtx().get());
    OM_uint32 flags = GSS_C_REPLAY_FLAG | GSS_C_MUTUAL_FLAG | GSS_C_INTEG_FLAG;
    bool ret = false;

    // Exchanges.
    GssApiBuffer intoken0;
    GssApiBuffer outtoken0;
    ASSERT_NO_THROW(ret = key->getSecCtx().init(cred, srv_name, flags,
                                                intoken0, outtoken0,
                                                lifetime));
    ASSERT_FALSE(outtoken0.empty());
    GssApiBuffer outtoken1;
    ASSERT_NO_THROW(ret = srv_key->getSecCtx().accept(*srv_cred, outtoken0,
                                                      clnt_name, outtoken1));
    EXPECT_TRUE(ret);
    GssApiBuffer outtoken2;
    ASSERT_NO_THROW(ret = key->getSecCtx().init(cred, srv_name, flags,
                                                outtoken1, outtoken2,
                                                lifetime));
    ASSERT_TRUE(ret);
    EXPECT_TRUE(outtoken2.empty());

    // Build the message to sign.
    message_.clear(Message::RENDER);
    message_.setQid(0x1234);
    message_.setOpcode(Opcode::QUERY());
    message_.setRcode(Rcode::NOERROR());
    message_.setHeaderFlag(Message::HEADERFLAG_QR);
    Name qname("foo.example.nil.");
    message_.addQuestion(Question(qname, RRClass::IN(), RRType::A()));
    MessageRenderer renderer;
    OutputBuffer obuf(1024);
    renderer.setBuffer(&obuf);

    // Sign.
    GssTsigContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*key)));
    ASSERT_TRUE(ctx);
    EXPECT_NO_THROW(message_.toWire(renderer, ctx.get()));
    // len is 33 + 62 + 28 = 123.
    ASSERT_TRUE(obuf.getData());
    EXPECT_EQ(123, obuf.getLength());

    // Check the TSIG RR.
    message_.clear(Message::PARSE);
    InputBuffer ibuf(obuf.getData(), obuf.getLength());
    EXPECT_NO_THROW(message_.fromWire(ibuf));
    const TSIGRecord* tsig = message_.getTSIGRecord();
    ASSERT_TRUE(tsig);

    // Verify.
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*srv_key)));
    ASSERT_TRUE(ctx);
    TSIGError error = TSIGError::NOERROR();
    EXPECT_NO_THROW(error = ctx->verify(tsig, obuf.getData(),
                                        obuf.getLength()));
    EXPECT_EQ(TSIGError::NOERROR(), error);
    EXPECT_TRUE(ctx->lastHadSignature());
    EXPECT_EQ(TSIGError::NOERROR(), ctx->getError());
    EXPECT_EQ(TSIGContext::RECEIVED_REQUEST, ctx->getState());

    // Only once.
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*srv_key)));
    ASSERT_TRUE(ctx);
    EXPECT_NO_THROW(error = ctx->verify(tsig, obuf.getData(),
                                        obuf.getLength()));
    // Error message is 'The token was a duplicate of an earlier token'.
    EXPECT_EQ(TSIGError::BAD_SIG(), error);
    EXPECT_EQ(TSIGError::BAD_SIG(), ctx->getError());
    EXPECT_EQ(TSIGContext::RECEIVED_REQUEST, ctx->getState());
    EXPECT_EQ(GSS_S_DUPLICATE_TOKEN, srv_key->getSecCtx().getLastError());

    // Bad key is persistent.
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*srv_key)));
    ASSERT_TRUE(ctx);
    ctx->setError(TSIGError::BAD_KEY());
    EXPECT_NO_THROW(error = ctx->verify(tsig, obuf.getData(),
                                        obuf.getLength()));
    // No message: the error is raised before crypto.
    EXPECT_EQ(TSIGError::BAD_KEY(), error);
    EXPECT_EQ(TSIGError::BAD_KEY(), ctx->getError());
    EXPECT_EQ(TSIGContext::RECEIVED_REQUEST, ctx->getState());
}

/// @brief Check that sign and verify fail on modified signature.
TEST_F(GssTsigContextTest, signBadVerify) {
    GssTsigKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(key);

    setKeytab();
    setAdministratorCCache();

    // Server.
    GssTsigKeyPtr srv_key;
    ASSERT_NO_THROW(srv_key.reset(new GssTsigKey(name)));
    ASSERT_TRUE(srv_key);
    EXPECT_FALSE(srv_key->getSecCtx().get());
    GssApiName srv_name("DNS/blu.example.nil@EXAMPLE.NIL");
    OM_uint32 lifetime = 0;
    GssApiCredPtr srv_cred(new GssApiCred(srv_name, GSS_C_ACCEPT, lifetime));

    // Client.
    GssApiName clnt_name;
    GssApiCredPtr cred;
    EXPECT_FALSE(key->getSecCtx().get());
    OM_uint32 flags = GSS_C_REPLAY_FLAG | GSS_C_MUTUAL_FLAG | GSS_C_INTEG_FLAG;
    bool ret = false;

    // Exchanges.
    GssApiBuffer intoken0;
    GssApiBuffer outtoken0;
    ASSERT_NO_THROW(ret = key->getSecCtx().init(cred, srv_name, flags,
                                                intoken0, outtoken0,
                                                lifetime));
    ASSERT_FALSE(outtoken0.empty());
    GssApiBuffer outtoken1;
    ASSERT_NO_THROW(ret = srv_key->getSecCtx().accept(*srv_cred, outtoken0,
                                                      clnt_name, outtoken1));
    EXPECT_TRUE(ret);
    GssApiBuffer outtoken2;
    ASSERT_NO_THROW(ret = key->getSecCtx().init(cred, srv_name, flags,
                                                outtoken1, outtoken2,
                                                lifetime));
    ASSERT_TRUE(ret);
    EXPECT_TRUE(outtoken2.empty());

    // Build the message to sign.
    message_.clear(Message::RENDER);
    message_.setQid(0x1234);
    message_.setOpcode(Opcode::QUERY());
    message_.setRcode(Rcode::NOERROR());
    message_.setHeaderFlag(Message::HEADERFLAG_QR);
    Name qname("foo.example.nil.");
    message_.addQuestion(Question(qname, RRClass::IN(), RRType::A()));
    MessageRenderer renderer;
    OutputBuffer obuf(1024);
    renderer.setBuffer(&obuf);

    // Sign.
    GssTsigContextPtr ctx;
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*key)));
    ASSERT_TRUE(ctx);
    EXPECT_NO_THROW(message_.toWire(renderer, ctx.get()));
    // len is 33 + 62 + 28 = 123.
    ASSERT_TRUE(obuf.getData());
    EXPECT_EQ(123, obuf.getLength());

    // Check the TSIG RR.
    message_.clear(Message::PARSE);
    InputBuffer ibuf(obuf.getData(), obuf.getLength());
    // Change the signature at 93..121.
    ASSERT_EQ(123, obuf.getLength());
    const uint8_t* ptr = obuf.getData();
    obuf.writeUint8At(ptr[120] ^ 1, 120);
    EXPECT_NO_THROW(message_.fromWire(ibuf));
    const TSIGRecord* tsig = message_.getTSIGRecord();
    ASSERT_TRUE(tsig);

    // Bad verify.
    ASSERT_NO_THROW(ctx.reset(new GssTsigContext(*srv_key)));
    ASSERT_TRUE(ctx);
    TSIGError error = TSIGError::NOERROR();
    EXPECT_NO_THROW(error = ctx->verify(tsig, obuf.getData(),
                                        obuf.getLength()));
    // Error message is 'A token had an invalid Message Integrity Check (MIC)'.
    EXPECT_EQ(TSIGError::BAD_SIG(), error);
    EXPECT_EQ(TSIGError::BAD_SIG(), ctx->getError());
    EXPECT_EQ(TSIGContext::RECEIVED_REQUEST, ctx->getState());
    EXPECT_EQ(GSS_S_BAD_SIG, srv_key->getSecCtx().getLastError());
}

}
