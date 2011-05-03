// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <time.h>
#include <string>
#include <stdexcept>
#include <vector>

#include <boost/scoped_ptr.hpp>

#include <gtest/gtest.h>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <util/encode/base64.h>
#include <util/unittests/newhook.h>
#include <util/time_utilities.h>

#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/question.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/tsig.h>
#include <dns/tsigkey.h>
#include <dns/tsigrecord.h>

#include <dns/tests/unittest_util.h>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;

// See dnssectime.cc
namespace isc {
namespace util {
namespace detail {
extern int64_t (*gettimeFunction)();
}
}
}

namespace {
// See dnssectime_unittest.cc
template <int64_t NOW>
int64_t
testGetTime() {
    return (NOW);
}

class TSIGTest : public ::testing::Test {
protected:
    TSIGTest() :
        tsig_ctx(NULL), qid(0x2d65), test_name("www.example.com"),
        test_class(RRClass::IN()), test_ttl(86400), message(Message::RENDER),
        buffer(0), renderer(buffer)
    {
        // Make sure we use the system time by default so that we won't be
        // confused due to other tests that tweak the time.
        isc::util::detail::gettimeFunction = NULL;

        decodeBase64("SFuWd/q99SzF8Yzd1QbB9g==", secret);
        tsig_ctx.reset(new TSIGContext(TSIGKey(test_name,
                                               TSIGKey::HMACMD5_NAME(),
                                               &secret[0], secret.size())));
        tsig_verify_ctx.reset(new TSIGContext(TSIGKey(test_name,
                                                      TSIGKey::HMACMD5_NAME(),
                                                      &secret[0],
                                                      secret.size())));
    }
    ~TSIGTest() {
        isc::util::detail::gettimeFunction = NULL;
    }

    // Many of the tests below create some DNS message and sign it under
    // some specific TSIG context.  This helper method unifies the common
    // logic with slightly different parameters.
    ConstTSIGRecordPtr createMessageAndSign(uint16_t qid, const Name& qname,
                                            TSIGContext* ctx,
                                            unsigned int message_flags =
                                            RD_FLAG,
                                            RRType qtype = RRType::A(),
                                            const char* answer_data = NULL,
                                            const RRType* answer_type = NULL,
                                            bool add_question = true,
                                            Rcode rcode = Rcode::NOERROR());

    // bit-wise constant flags to configure DNS header flags for test
    // messages.
    static const unsigned int QR_FLAG = 0x1;
    static const unsigned int AA_FLAG = 0x2;
    static const unsigned int RD_FLAG = 0x4;

    boost::scoped_ptr<TSIGContext> tsig_ctx;
    boost::scoped_ptr<TSIGContext> tsig_verify_ctx;
    TSIGKeyRing keyring;
    const uint16_t qid;
    const Name test_name;
    const RRClass test_class;
    const RRTTL test_ttl;
    Message message;
    OutputBuffer buffer;
    MessageRenderer renderer;
    vector<uint8_t> secret;
};

ConstTSIGRecordPtr
TSIGTest::createMessageAndSign(uint16_t id, const Name& qname,
                               TSIGContext* ctx, unsigned int message_flags,
                               RRType qtype, const char* answer_data,
                               const RRType* answer_type, bool add_question,
                               Rcode rcode)
{
    message.clear(Message::RENDER);
    message.setQid(id);
    message.setOpcode(Opcode::QUERY());
    message.setRcode(rcode);
    if ((message_flags & QR_FLAG) != 0) {
        message.setHeaderFlag(Message::HEADERFLAG_QR);
    }
    if ((message_flags & AA_FLAG) != 0) {
        message.setHeaderFlag(Message::HEADERFLAG_AA);
    }
    if ((message_flags & RD_FLAG) != 0) {
        message.setHeaderFlag(Message::HEADERFLAG_RD);
    }
    if (add_question) {
        message.addQuestion(Question(qname, test_class, qtype));
    }
    if (answer_data != NULL) {
        if (answer_type == NULL) {
            answer_type = &qtype;
        }
        RRsetPtr answer_rrset(new RRset(qname, test_class, *answer_type,
                                        test_ttl));
        answer_rrset->addRdata(createRdata(*answer_type, test_class,
                                           answer_data));
        message.addRRset(Message::SECTION_ANSWER, answer_rrset);
    }
    renderer.clear();
    message.toWire(renderer);

    ConstTSIGRecordPtr tsig = ctx->sign(id, renderer.getData(),
                                        renderer.getLength());
    EXPECT_EQ(TSIGContext::SIGNED, ctx->getState());

    return (tsig);
}

void
commonTSIGChecks(ConstTSIGRecordPtr tsig, uint16_t expected_qid,
                 uint64_t expected_timesigned,
                 const uint8_t* expected_mac, size_t expected_maclen,
                 uint16_t expected_error = 0,
                 uint16_t expected_otherlen = 0,
                 const uint8_t* expected_otherdata = NULL,
                 const Name& expected_algorithm = TSIGKey::HMACMD5_NAME())
{
    ASSERT_TRUE(tsig != NULL);
    const any::TSIG& tsig_rdata = tsig->getRdata();

    EXPECT_EQ(expected_algorithm, tsig_rdata.getAlgorithm());
    EXPECT_EQ(expected_timesigned, tsig_rdata.getTimeSigned());
    EXPECT_EQ(300, tsig_rdata.getFudge());
    EXPECT_EQ(expected_maclen, tsig_rdata.getMACSize());
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        tsig_rdata.getMAC(), tsig_rdata.getMACSize(),
                        expected_mac, expected_maclen);
    EXPECT_EQ(expected_qid, tsig_rdata.getOriginalID());
    EXPECT_EQ(expected_error, tsig_rdata.getError());
    EXPECT_EQ(expected_otherlen, tsig_rdata.getOtherLen());
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        tsig_rdata.getOtherData(), tsig_rdata.getOtherLen(),
                        expected_otherdata, expected_otherlen);
}

TEST_F(TSIGTest, initialState) {
    // Until signing or verifying, the state should be INIT
    EXPECT_EQ(TSIGContext::INIT, tsig_ctx->getState());

    // And there should be no error code.
    EXPECT_EQ(TSIGError(Rcode::NOERROR()), tsig_ctx->getError());
}

TEST_F(TSIGTest, constructFromKeyRing) {
    // Construct a TSIG context with an empty key ring.  Key shouldn't be
    // found, and the BAD_KEY error should be recorded.
    TSIGContext ctx1(test_name, TSIGKey::HMACMD5_NAME(), keyring);
    EXPECT_EQ(TSIGContext::INIT, ctx1.getState());
    EXPECT_EQ(TSIGError::BAD_KEY(), ctx1.getError());

    // Add a matching key (we don't use the secret so leave it empty), and
    // construct it again.  This time it should be constructed with a valid
    // key.
    keyring.add(TSIGKey(test_name, TSIGKey::HMACMD5_NAME(), NULL, 0));
    TSIGContext ctx2(test_name, TSIGKey::HMACMD5_NAME(), keyring);
    EXPECT_EQ(TSIGContext::INIT, ctx2.getState());
    EXPECT_EQ(TSIGError::NOERROR(), ctx2.getError());

    // Similar to the first case except that the key ring isn't empty but
    // it doesn't contain a matching key.
    TSIGContext ctx3(test_name, TSIGKey::HMACSHA1_NAME(), keyring);
    EXPECT_EQ(TSIGContext::INIT, ctx3.getState());
    EXPECT_EQ(TSIGError::BAD_KEY(), ctx3.getError());

    TSIGContext ctx4(Name("different-key.example"), TSIGKey::HMACMD5_NAME(),
                     keyring);
    EXPECT_EQ(TSIGContext::INIT, ctx4.getState());
    EXPECT_EQ(TSIGError::BAD_KEY(), ctx4.getError());
}

// Example output generated by
// "dig -y www.example.com:SFuWd/q99SzF8Yzd1QbB9g== www.example.com
// QID: 0x2d65
// Time Signed: 0x00004da8877a
// MAC: 227026ad297beee721ce6c6fff1e9ef3
const uint8_t common_expected_mac[] = {
    0x22, 0x70, 0x26, 0xad, 0x29, 0x7b, 0xee, 0xe7,
    0x21, 0xce, 0x6c, 0x6f, 0xff, 0x1e, 0x9e, 0xf3
};
TEST_F(TSIGTest, sign) {
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    {
        SCOPED_TRACE("Sign test for query");
        commonTSIGChecks(createMessageAndSign(qid, test_name, tsig_ctx.get()),
                         qid, 0x4da8877a, common_expected_mac,
                         sizeof(common_expected_mac));
    }
}

// Same test as sign, but specifying the key name with upper-case (i.e.
// non canonical) characters.  The digest must be the same.  It should actually
// be ensured at the level of TSIGKey, but we confirm that at this level, too.
TEST_F(TSIGTest, signUsingUpperCasedKeyName) {
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    TSIGContext cap_ctx(TSIGKey(Name("WWW.EXAMPLE.COM"),
                                TSIGKey::HMACMD5_NAME(),
                                &secret[0], secret.size()));

    {
        SCOPED_TRACE("Sign test for query using non canonical key name");
        commonTSIGChecks(createMessageAndSign(qid, test_name, &cap_ctx), qid,
                         0x4da8877a, common_expected_mac,
                         sizeof(common_expected_mac));
    }
}

// Same as the previous test, but for the algorithm name.
TEST_F(TSIGTest, signUsingUpperCasedAlgorithmName) {
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    TSIGContext cap_ctx(TSIGKey(test_name,
                                Name("HMAC-md5.SIG-alg.REG.int"),
                                &secret[0], secret.size()));

    {
        SCOPED_TRACE("Sign test for query using non canonical algorithm name");
        commonTSIGChecks(createMessageAndSign(qid, test_name, &cap_ctx), qid,
                         0x4da8877a, common_expected_mac,
                         sizeof(common_expected_mac));
    }
}

TEST_F(TSIGTest, signAtActualTime) {
    // Sign the message using the actual time, and check the accuracy of it.
    // We cannot reasonably predict the expected MAC, so don't bother to
    // check it.
    const uint64_t now = static_cast<uint64_t>(time(NULL));

    {
        SCOPED_TRACE("Sign test for query at actual time");
        ConstTSIGRecordPtr tsig = createMessageAndSign(qid, test_name,
                                                       tsig_ctx.get());
        const any::TSIG& tsig_rdata = tsig->getRdata();

        // Check the resulted time signed is in the range of [now, now + 5]
        // (5 is an arbitrary choice).  Note that due to the order of the call
        // to time() and sign(), time signed must not be smaller than the
        // current time.
        EXPECT_LE(now, tsig_rdata.getTimeSigned());
        EXPECT_GE(now + 5, tsig_rdata.getTimeSigned());
    }
}

TEST_F(TSIGTest, signBadData) {
    // some specific bad data should be rejected proactively.
    const unsigned char dummy_data = 0;
    EXPECT_THROW(tsig_ctx->sign(0, NULL, 10), InvalidParameter);
    EXPECT_THROW(tsig_ctx->sign(0, &dummy_data, 0), InvalidParameter);
}

#ifdef ENABLE_CUSTOM_OPERATOR_NEW
// We enable this test only when we enable custom new/delete at build time
// We could enable/disable the test runtime using the gtest filter, but
// we'd basically like to minimize the number of disabled tests (they
// should generally be considered tests that temporarily fail and should
// be fixed).
TEST_F(TSIGTest, signExceptionSafety) {
    // Check sign() provides the strong exception guarantee for the simpler
    // case (with a key error and empty MAC).  The general case is more
    // complicated and involves more memory allocation, so the test result
    // won't be reliable.

    tsig_verify_ctx->verifyTentative(createMessageAndSign(qid, test_name,
                                                          tsig_ctx.get()),
                                     TSIGError::BAD_KEY());
    // At this point the state should be changed to "CHECKED"
    ASSERT_EQ(TSIGContext::CHECKED, tsig_verify_ctx->getState());
    try {
        int dummydata;
        isc::util::unittests::force_throw_on_new = true;
        isc::util::unittests::throw_size_on_new = sizeof(TSIGRecord);
        tsig_verify_ctx->sign(0, &dummydata, sizeof(dummydata));
        isc::util::unittests::force_throw_on_new = false;
        ASSERT_FALSE(true) << "Expected throw on new, but it didn't happen";
    } catch (const std::bad_alloc&) {
        isc::util::unittests::force_throw_on_new = false;

        // sign() threw, so the state should still be "CHECKED".
        EXPECT_EQ(TSIGContext::CHECKED, tsig_verify_ctx->getState());
    }
    isc::util::unittests::force_throw_on_new = false;
}
#endif  // ENABLE_CUSTOM_OPERATOR_NEW

// Same test as "sign" but use a different algorithm just to confirm we don't
// naively hardcode constants specific to a particular algorithm.
// Test data generated by
// "dig -y hmac-sha1:www.example.com:MA+QDhXbyqUak+qnMFyTyEirzng= www.example.com"
//   QID: 0x0967, RDflag
//   Current Time: 00004da8be86
//   Time Signed:  00004dae7d5f
//   HMAC Size: 20
//   HMAC: 415340c7daf824ed684ee586f7b5a67a2febc0d3
TEST_F(TSIGTest, signUsingHMACSHA1) {
    isc::util::detail::gettimeFunction = testGetTime<0x4dae7d5f>;

    secret.clear();
    decodeBase64("MA+QDhXbyqUak+qnMFyTyEirzng=", secret);
    TSIGContext sha1_ctx(TSIGKey(test_name, TSIGKey::HMACSHA1_NAME(),
                                 &secret[0], secret.size()));

    const uint16_t sha1_qid = 0x0967;
    const uint8_t expected_mac[] = {
        0x41, 0x53, 0x40, 0xc7, 0xda, 0xf8, 0x24, 0xed, 0x68, 0x4e,
        0xe5, 0x86, 0xf7, 0xb5, 0xa6, 0x7a, 0x2f, 0xeb, 0xc0, 0xd3
    };
    {
        SCOPED_TRACE("Sign test using HMAC-SHA1");
        commonTSIGChecks(createMessageAndSign(sha1_qid, test_name, &sha1_ctx),
                         sha1_qid, 0x4dae7d5f, expected_mac,
                         sizeof(expected_mac), 0, 0, NULL,
                         TSIGKey::HMACSHA1_NAME());
    }
}

// An example response to the signed query used for the "sign" test.
// Answer: www.example.com. 86400 IN A 192.0.2.1
// MAC: 8fcda66a7cd1a3b9948eb1869d384a9f
TEST_F(TSIGTest, signResponse) {
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    ConstTSIGRecordPtr tsig = createMessageAndSign(qid, test_name,
                                                   tsig_ctx.get());
    tsig_verify_ctx->verifyTentative(tsig);
    EXPECT_EQ(TSIGContext::CHECKED, tsig_verify_ctx->getState());

    // Transform the original message to a response, then sign the response
    // with the context of "verified state".
    tsig = createMessageAndSign(qid, test_name, tsig_verify_ctx.get(),
                                QR_FLAG|AA_FLAG|RD_FLAG,
                                RRType::A(), "192.0.2.1");
    const uint8_t expected_mac[] = {
        0x8f, 0xcd, 0xa6, 0x6a, 0x7c, 0xd1, 0xa3, 0xb9,
        0x94, 0x8e, 0xb1, 0x86, 0x9d, 0x38, 0x4a, 0x9f
    };
    {
        SCOPED_TRACE("Sign test for response");
        commonTSIGChecks(tsig, qid, 0x4da8877a,
                         expected_mac, sizeof(expected_mac));
    }
}

// Example of signing multiple messages in a single TCP stream,
// taken from data using BIND 9's "one-answer" transfer-format.
// First message:
//   QID: 0x3410, flags QR, AA
//   Question: example.com/IN/AXFR
//   Answer: example.com. 86400 IN SOA ns.example.com. root.example.com. (
//                          2011041503 7200 3600 2592000 1200)
//   Time Signed: 0x4da8e951
// Second message:
//    Answer: example.com. 86400 IN NS ns.example.com.
//    MAC: 102458f7f62ddd7d638d746034130968
TEST_F(TSIGTest, signContinuation) {
    isc::util::detail::gettimeFunction = testGetTime<0x4da8e951>;

    const uint16_t axfr_qid = 0x3410;
    const Name zone_name("example.com");

    // Create and sign the AXFR request, then verify it.
    tsig_verify_ctx->verifyTentative(createMessageAndSign(axfr_qid, zone_name,
                                                          tsig_ctx.get(), 0,
                                                          RRType::AXFR()));
    EXPECT_EQ(TSIGContext::CHECKED, tsig_verify_ctx->getState());

    // Create and sign the first response message (we don't need the result
    // for the purpose of this test)
    createMessageAndSign(axfr_qid, zone_name, tsig_verify_ctx.get(),
                         AA_FLAG|QR_FLAG, RRType::AXFR(),
                         "ns.example.com. root.example.com. "
                         "2011041503 7200 3600 2592000 1200",
                         &RRType::SOA());

    // Create and sign the second response message
    const uint8_t expected_mac[] = {
        0x10, 0x24, 0x58, 0xf7, 0xf6, 0x2d, 0xdd, 0x7d,
        0x63, 0x8d, 0x74, 0x60, 0x34, 0x13, 0x09, 0x68
    };
    {
        SCOPED_TRACE("Sign test for continued response in TCP stream");
        commonTSIGChecks(createMessageAndSign(axfr_qid, zone_name,
                                              tsig_verify_ctx.get(),
                                              AA_FLAG|QR_FLAG, RRType::AXFR(),
                                              "ns.example.com.", &RRType::NS(),
                                              false),
                         axfr_qid, 0x4da8e951,
                         expected_mac, sizeof(expected_mac));
    }
}

// BADTIME example, taken from data using specially hacked BIND 9's nsupdate
// Query:
//   QID: 0x1830, RD flag
//   Current Time: 00004da8be86
//   Time Signed:  00004da8b9d6
//   Question: www.example.com/IN/SOA
//(mac) 8406 7d50 b8e7 d054 3d50 5bd9 de2a bb68
// Response:
//   QRbit, RCODE=9(NOTAUTH)
//   Time Signed: 00004da8b9d6 (the one in the query)
//   MAC: d4b043f6f44495ec8a01260e39159d76
//   Error: 0x12 (BADTIME), Other Len: 6
//   Other data: 00004da8be86
TEST_F(TSIGTest, badtimeResponse) {
    isc::util::detail::gettimeFunction = testGetTime<0x4da8b9d6>;

    const uint16_t test_qid = 0x7fc4;
    ConstTSIGRecordPtr tsig = createMessageAndSign(test_qid, test_name,
                                                   tsig_ctx.get(), 0,
                                                   RRType::SOA());

    // "advance the clock" and try validating, which should fail due to BADTIME
    // (verifyTentative actually doesn't check the time, though)
    isc::util::detail::gettimeFunction = testGetTime<0x4da8be86>;
    tsig_verify_ctx->verifyTentative(tsig, TSIGError::BAD_TIME());
    EXPECT_EQ(TSIGError::BAD_TIME(), tsig_verify_ctx->getError());

    // make and sign a response in the context of TSIG error.
    tsig = createMessageAndSign(test_qid, test_name, tsig_verify_ctx.get(),
                                QR_FLAG, RRType::SOA(), NULL, NULL,
                                true, Rcode::NOTAUTH());
    const uint8_t expected_otherdata[] = { 0, 0, 0x4d, 0xa8, 0xbe, 0x86 };
    const uint8_t expected_mac[] = {
        0xd4, 0xb0, 0x43, 0xf6, 0xf4, 0x44, 0x95, 0xec,
        0x8a, 0x01, 0x26, 0x0e, 0x39, 0x15, 0x9d, 0x76
    };
    {
        SCOPED_TRACE("Sign test for response with BADTIME");
        commonTSIGChecks(tsig, message.getQid(), 0x4da8b9d6,
                         expected_mac, sizeof(expected_mac),
                         18,     // error: BADTIME
                         sizeof(expected_otherdata),
                         expected_otherdata);
    }
}

TEST_F(TSIGTest, badsigResponse) {
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    // Sign a simple message, and force the verification to fail with
    // BADSIG.
    tsig_verify_ctx->verifyTentative(createMessageAndSign(qid, test_name,
                                                          tsig_ctx.get()),
                                     TSIGError::BAD_SIG());

    // Sign the same message (which doesn't matter for this test) with the
    // context of "checked state".
    {
        SCOPED_TRACE("Sign test for response with BADSIG error");
        commonTSIGChecks(createMessageAndSign(qid, test_name,
                                              tsig_verify_ctx.get()),
                         message.getQid(), 0x4da8877a, NULL, 0,
                         16);   // 16: BADSIG
    }
}

TEST_F(TSIGTest, badkeyResponse) {
    // A similar test as badsigResponse but for BADKEY
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;
    tsig_verify_ctx->verifyTentative(createMessageAndSign(qid, test_name,
                                                          tsig_ctx.get()),
                                     TSIGError::BAD_KEY());
    {
        SCOPED_TRACE("Sign test for response with BADKEY error");
        commonTSIGChecks(createMessageAndSign(qid, test_name,
                                              tsig_verify_ctx.get()),
                         message.getQid(), 0x4da8877a, NULL, 0,
                         17);   // 17: BADKEYSIG
    }
}

} // end namespace
