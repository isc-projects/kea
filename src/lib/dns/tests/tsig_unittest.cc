// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
#include <util/unittests/wiredata.h>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

// @note: blocks and SCOPED_TRACE can make buggy cppchecks raise
// a spurious syntax error...

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

// Thin wrapper around TSIGContext to allow access to the
// update method.
class TestTSIGContext : public TSIGContext {
public:
    TestTSIGContext(const TSIGKey& key) :
        TSIGContext(key)
    {}
    TestTSIGContext(const Name& key_name, const Name& algorithm_name,
                    const TSIGKeyRing& keyring) :
        TSIGContext(key_name, algorithm_name, keyring)
    {}
    void update(const void* const data, size_t len) {
        TSIGContext::update(data, len);
    }
};

class TSIGTest : public ::testing::Test {
protected:
    TSIGTest() :
        tsig_ctx(NULL), qid(0x2d65), test_name("www.example.com"),
        badkey_name("badkey.example.com"), test_class(RRClass::IN()),
        test_ttl(86400), message(Message::RENDER),
        dummy_data(1024, 0xdd),  // should be sufficiently large for all tests
        dummy_record(badkey_name, any::TSIG(TSIGKey::HMACMD5_NAME(),
                                            0x4da8877a,
                                            TSIGContext::DEFAULT_FUDGE,
                                            0, NULL, qid, 0, 0, NULL))
    {
        // Make sure we use the system time by default so that we won't be
        // confused due to other tests that tweak the time.
        isc::util::detail::gettimeFunction = NULL;

        decodeBase64("SFuWd/q99SzF8Yzd1QbB9g==", secret);
        tsig_ctx.reset(new TestTSIGContext(TSIGKey(test_name,
                                                   TSIGKey::HMACMD5_NAME(),
                                                   &secret[0],
                                                   secret.size())));
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

    void createMessageFromFile(const char* datafile);

    // bit-wise constant flags to configure DNS header flags for test
    // messages.
    static const unsigned int QR_FLAG = 0x1;
    static const unsigned int AA_FLAG = 0x2;
    static const unsigned int RD_FLAG = 0x4;

    boost::scoped_ptr<TestTSIGContext> tsig_ctx;
    boost::scoped_ptr<TSIGContext> tsig_verify_ctx;
    TSIGKeyRing keyring;
    const uint16_t qid;
    const Name test_name;
    const Name badkey_name;
    const RRClass test_class;
    const RRTTL test_ttl;
    Message message;
    MessageRenderer renderer;
    vector<uint8_t> secret;
    vector<uint8_t> dummy_data;
    const TSIGRecord dummy_record;
    vector<uint8_t> received_data;
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

    TSIGContext::State expected_new_state =
        (ctx->getState() == TSIGContext::INIT) ?
        TSIGContext::SENT_REQUEST : TSIGContext::SENT_RESPONSE;

    message.toWire(renderer, ctx);

    message.clear(Message::PARSE);
    InputBuffer buffer(renderer.getData(), renderer.getLength());
    message.fromWire(buffer);

    EXPECT_EQ(expected_new_state, ctx->getState());

    return (ConstTSIGRecordPtr(new TSIGRecord(*message.getTSIGRecord())));
}

void
TSIGTest::createMessageFromFile(const char* datafile) {
    message.clear(Message::PARSE);
    received_data.clear();
    UnitTestUtil::readWireData(datafile, received_data);
    InputBuffer buffer(&received_data[0], received_data.size());
    message.fromWire(buffer);
}

void
commonSignChecks(ConstTSIGRecordPtr tsig, uint16_t expected_qid,
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
    matchWireData(expected_mac, expected_maclen,
                  tsig_rdata.getMAC(), tsig_rdata.getMACSize());

    EXPECT_EQ(expected_qid, tsig_rdata.getOriginalID());
    EXPECT_EQ(expected_error, tsig_rdata.getError());
    EXPECT_EQ(expected_otherlen, tsig_rdata.getOtherLen());
    matchWireData(expected_otherdata, expected_otherlen,
                  tsig_rdata.getOtherData(), tsig_rdata.getOtherLen());
}

void
commonVerifyChecks(TSIGContext& ctx, const TSIGRecord* record,
                   const void* data, size_t data_len, TSIGError expected_error,
                   TSIGContext::State expected_new_state =
                   TSIGContext::VERIFIED_RESPONSE,
                   bool last_should_throw = false)
{
    EXPECT_EQ(expected_error, ctx.verify(record, data, data_len));
    EXPECT_EQ(expected_error, ctx.getError());
    EXPECT_EQ(expected_new_state, ctx.getState());
    if (last_should_throw) {
        EXPECT_THROW(ctx.lastHadSignature(), TSIGContextError);
    } else {
        EXPECT_EQ(record != NULL, ctx.lastHadSignature());
    }
}

TEST_F(TSIGTest, initialState) {
    // Until signing or verifying, the state should be INIT
    EXPECT_EQ(TSIGContext::INIT, tsig_ctx->getState());

    // And there should be no error code.
    EXPECT_EQ(TSIGError(Rcode::NOERROR()), tsig_ctx->getError());

    // Nothing verified yet
    EXPECT_THROW(tsig_ctx->lastHadSignature(), TSIGContextError);
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

    // "Unknown" algorithm name will result in BADKEY, too.
    TSIGContext ctx5(test_name, Name("unknown.algorithm"), keyring);
    EXPECT_EQ(TSIGContext::INIT, ctx5.getState());
    EXPECT_EQ(TSIGError::BAD_KEY(), ctx5.getError());
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
        commonSignChecks(createMessageAndSign(qid, test_name, tsig_ctx.get()),
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
        commonSignChecks(createMessageAndSign(qid, test_name, &cap_ctx), qid,
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
        commonSignChecks(createMessageAndSign(qid, test_name, &cap_ctx), qid,
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

TEST_F(TSIGTest, verifyBadData) {
    // the data must at least hold the DNS message header and the specified
    // TSIG.
    EXPECT_THROW(tsig_ctx->verify(&dummy_record, &dummy_data[0],
                                  12 + dummy_record.getLength() - 1),
                 InvalidParameter);

    // Still nothing verified
    EXPECT_THROW(tsig_ctx->lastHadSignature(), TSIGContextError);

    // And the data must not be NULL.
    EXPECT_THROW(tsig_ctx->verify(&dummy_record, NULL,
                                  12 + dummy_record.getLength()),
                 InvalidParameter);

    // Still nothing verified
    EXPECT_THROW(tsig_ctx->lastHadSignature(), TSIGContextError);

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

    commonVerifyChecks(*tsig_verify_ctx, &dummy_record, &dummy_data[0],
                       dummy_data.size(), TSIGError::BAD_KEY(),
                       TSIGContext::RECEIVED_REQUEST);

    try {
        int dummydata;
        isc::util::unittests::force_throw_on_new = true;
        isc::util::unittests::throw_size_on_new = sizeof(TSIGRecord);
        tsig_verify_ctx->sign(0, &dummydata, sizeof(dummydata));
        isc::util::unittests::force_throw_on_new = false;
        ASSERT_FALSE(true) << "Expected throw on new, but it didn't happen";
    } catch (const std::bad_alloc&) {
        isc::util::unittests::force_throw_on_new = false;

        // sign() threw, so the state should still be RECEIVED_REQUEST
        EXPECT_EQ(TSIGContext::RECEIVED_REQUEST, tsig_verify_ctx->getState());
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
        commonSignChecks(createMessageAndSign(sha1_qid, test_name, &sha1_ctx),
                         sha1_qid, 0x4dae7d5f, expected_mac,
                         sizeof(expected_mac), 0, 0, NULL,
                         TSIGKey::HMACSHA1_NAME());
    }
}

TEST_F(TSIGTest, signUsingHMACSHA224) {
    isc::util::detail::gettimeFunction = testGetTime<0x4dae7d5f>;

    secret.clear();
    decodeBase64("MA+QDhXbyqUak+qnMFyTyEirzng=", secret);
    TSIGContext sha1_ctx(TSIGKey(test_name, TSIGKey::HMACSHA224_NAME(),
                                 &secret[0], secret.size()));

    const uint16_t sha1_qid = 0x0967;
    const uint8_t expected_mac[] = {
        0x3b, 0x93, 0xd3, 0xc5, 0xf9, 0x64, 0xb9, 0xc5, 0x00, 0x35, 
        0x02, 0x69, 0x9f, 0xfc, 0x44, 0xd6, 0xe2, 0x66, 0xf4, 0x08, 
        0xef, 0x33, 0xa2, 0xda, 0xa1, 0x48, 0x71, 0xd3
    };
    {
        SCOPED_TRACE("Sign test using HMAC-SHA224");
        commonSignChecks(createMessageAndSign(sha1_qid, test_name, &sha1_ctx),
                         sha1_qid, 0x4dae7d5f, expected_mac,
                         sizeof(expected_mac), 0, 0, NULL,
                         TSIGKey::HMACSHA224_NAME());
    }
}

// The first part of this test checks verifying the signed query used for
// the "sign" test.
// The second part of this test generates a signed response to the signed
// query as follows:
// Answer: www.example.com. 86400 IN A 192.0.2.1
// MAC: 8fcda66a7cd1a3b9948eb1869d384a9f
TEST_F(TSIGTest, verifyThenSignResponse) {
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    // This test data for the message test has the same wire format data
    // as the message used in the "sign" test.
    createMessageFromFile("message_toWire2.wire");
    {
        SCOPED_TRACE("Verify test for request");
        commonVerifyChecks(*tsig_verify_ctx, message.getTSIGRecord(),
                           &received_data[0], received_data.size(),
                           TSIGError::NOERROR(), TSIGContext::RECEIVED_REQUEST);
    }

    // Transform the original message to a response, then sign the response
    // with the context of "verified state".
    ConstTSIGRecordPtr tsig = createMessageAndSign(qid, test_name,
                                                   tsig_verify_ctx.get(),
                                                   QR_FLAG|AA_FLAG|RD_FLAG,
                                                   RRType::A(), "192.0.2.1");
    const uint8_t expected_mac[] = {
        0x8f, 0xcd, 0xa6, 0x6a, 0x7c, 0xd1, 0xa3, 0xb9,
        0x94, 0x8e, 0xb1, 0x86, 0x9d, 0x38, 0x4a, 0x9f
    };
    {
        SCOPED_TRACE("Sign test for response");
        commonSignChecks(tsig, qid, 0x4da8877a, expected_mac,
                         sizeof(expected_mac));
    }
}

TEST_F(TSIGTest, verifyUpperCaseNames) {
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    // This test data for the message test has the same wire format data
    // as the message used in the "sign" test.
    createMessageFromFile("tsig_verify9.wire");
    {
        SCOPED_TRACE("Verify test for request");
        commonVerifyChecks(*tsig_verify_ctx, message.getTSIGRecord(),
                           &received_data[0], received_data.size(),
                           TSIGError::NOERROR(), TSIGContext::RECEIVED_REQUEST);
    }
}

TEST_F(TSIGTest, verifyForwardedMessage) {
    // Similar to the first part of the previous test, but this test emulates
    // the "forward" case, where the ID of the Header and the original ID in
    // TSIG is different.
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    createMessageFromFile("tsig_verify6.wire");
    {
        SCOPED_TRACE("Verify test for forwarded request");
        commonVerifyChecks(*tsig_verify_ctx, message.getTSIGRecord(),
                           &received_data[0], received_data.size(),
                           TSIGError::NOERROR(), TSIGContext::RECEIVED_REQUEST);
    }
}

// Example of signing multiple messages in a single TCP stream,
// taken from data using BIND 9's "one-answer" transfer-format.
// Request:
//   QID: 0x3410, flags (none)
//   Question: example.com/IN/AXFR
//   Time Signed: 0x4da8e951
//   MAC: 35b2fd08268781634400c7c8a5533b13
// First message:
//   QID: 0x3410, flags QR, AA
//   Question: example.com/IN/AXFR
//   Answer: example.com. 86400 IN SOA ns.example.com. root.example.com. (
//                          2011041503 7200 3600 2592000 1200)
//   MAC: bdd612cd2c7f9e0648bd6dc23713e83c
// Second message:
//   Answer: example.com. 86400 IN NS ns.example.com.
//   MAC: 102458f7f62ddd7d638d746034130968
TEST_F(TSIGTest, signContinuation) {
    isc::util::detail::gettimeFunction = testGetTime<0x4da8e951>;

    const uint16_t axfr_qid = 0x3410;
    const Name zone_name("example.com");

    // Create and sign the AXFR request
    ConstTSIGRecordPtr tsig = createMessageAndSign(axfr_qid, zone_name,
                                                   tsig_ctx.get(), 0,
                                                   RRType::AXFR());
    // Then verify it (the wire format test data should contain the same
    // message data, and verification should succeed).
    received_data.clear();
    UnitTestUtil::readWireData("tsig_verify1.wire", received_data);
    {
        SCOPED_TRACE("Verify AXFR query");
        commonVerifyChecks(*tsig_verify_ctx, tsig.get(), &received_data[0],
                           received_data.size(), TSIGError::NOERROR(),
                           TSIGContext::RECEIVED_REQUEST);
    }

    // Create and sign the first response message
    tsig = createMessageAndSign(axfr_qid, zone_name, tsig_verify_ctx.get(),
                                AA_FLAG|QR_FLAG, RRType::AXFR(),
                                "ns.example.com. root.example.com. "
                                "2011041503 7200 3600 2592000 1200",
                                &RRType::SOA());

    // Then verify it at the requester side.
    received_data.clear();
    UnitTestUtil::readWireData("tsig_verify2.wire", received_data);
    {
        SCOPED_TRACE("Verify first AXFR response");
        commonVerifyChecks(*tsig_ctx, tsig.get(), &received_data[0],
                           received_data.size(), TSIGError::NOERROR());
    }

    // Create and sign the second response message
    const uint8_t expected_mac[] = {
        0x10, 0x24, 0x58, 0xf7, 0xf6, 0x2d, 0xdd, 0x7d,
        0x63, 0x8d, 0x74, 0x60, 0x34, 0x13, 0x09, 0x68
    };
    {
        SCOPED_TRACE("Sign test for continued response in TCP stream");
        tsig = createMessageAndSign(axfr_qid, zone_name, tsig_verify_ctx.get(),
                                    AA_FLAG|QR_FLAG, RRType::AXFR(),
                                    "ns.example.com.", &RRType::NS(), false);
        commonSignChecks(tsig, axfr_qid, 0x4da8e951, expected_mac,
                         sizeof(expected_mac));
    }

    // Then verify it at the requester side.
    received_data.clear();
    UnitTestUtil::readWireData("tsig_verify3.wire", received_data);
    {
        SCOPED_TRACE("Verify second AXFR response");
        commonVerifyChecks(*tsig_ctx, tsig.get(), &received_data[0],
                           received_data.size(), TSIGError::NOERROR());
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
    isc::util::detail::gettimeFunction = testGetTime<0x4da8be86>;
    {
        SCOPED_TRACE("Verify resulting in BADTIME due to expired SIG");
        commonVerifyChecks(*tsig_verify_ctx, tsig.get(), &dummy_data[0],
                           dummy_data.size(), TSIGError::BAD_TIME(),
                           TSIGContext::RECEIVED_REQUEST);
    }

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
        commonSignChecks(tsig, message.getQid(), 0x4da8b9d6,
                         expected_mac, sizeof(expected_mac),
                         18,     // error: BADTIME
                         sizeof(expected_otherdata),
                         expected_otherdata);
    }
}

TEST_F(TSIGTest, badtimeResponse2) {
    isc::util::detail::gettimeFunction = testGetTime<0x4da8b9d6>;

    ConstTSIGRecordPtr tsig = createMessageAndSign(qid, test_name,
                                                   tsig_ctx.get(), 0,
                                                   RRType::SOA());

    // "rewind the clock" and try validating, which should fail due to BADTIME
    isc::util::detail::gettimeFunction = testGetTime<0x4da8b9d6 - 600>;
    {
        SCOPED_TRACE("Verify resulting in BADTIME due to too future SIG");
        commonVerifyChecks(*tsig_verify_ctx, tsig.get(), &dummy_data[0],
                           dummy_data.size(), TSIGError::BAD_TIME(),
                           TSIGContext::RECEIVED_REQUEST);
    }
}

TEST_F(TSIGTest, badtimeBoundaries) {
    isc::util::detail::gettimeFunction = testGetTime<0x4da8b9d6>;

    // Test various boundary conditions.  We intentionally use the magic
    // number of 300 instead of the constant variable for testing.
    // In the okay cases, signature is not correct, but it's sufficient to
    // check the error code isn't BADTIME for the purpose of this test.
    ConstTSIGRecordPtr tsig = createMessageAndSign(qid, test_name,
                                                   tsig_ctx.get(), 0,
                                                   RRType::SOA());
    isc::util::detail::gettimeFunction = testGetTime<0x4da8b9d6 + 301>;
    EXPECT_EQ(TSIGError::BAD_TIME(),
              tsig_verify_ctx->verify(tsig.get(), &dummy_data[0],
                                      dummy_data.size()));
    isc::util::detail::gettimeFunction = testGetTime<0x4da8b9d6 + 300>;
    EXPECT_NE(TSIGError::BAD_TIME(),
              tsig_verify_ctx->verify(tsig.get(), &dummy_data[0],
                                      dummy_data.size()));
    isc::util::detail::gettimeFunction = testGetTime<0x4da8b9d6 - 301>;
    EXPECT_EQ(TSIGError::BAD_TIME(),
              tsig_verify_ctx->verify(tsig.get(), &dummy_data[0],
                                      dummy_data.size()));
    isc::util::detail::gettimeFunction = testGetTime<0x4da8b9d6 - 300>;
    EXPECT_NE(TSIGError::BAD_TIME(),
              tsig_verify_ctx->verify(tsig.get(), &dummy_data[0],
                                      dummy_data.size()));
}

TEST_F(TSIGTest, badtimeOverflow) {
    isc::util::detail::gettimeFunction = testGetTime<200>;
    ConstTSIGRecordPtr tsig = createMessageAndSign(qid, test_name,
                                                   tsig_ctx.get(), 0,
                                                   RRType::SOA());

    // This should be in the okay range, but since "200 - fudge" overflows
    // and we compare them as 64-bit unsigned integers, it results in a false
    // positive (we intentionally accept that).
    isc::util::detail::gettimeFunction = testGetTime<100>;
    EXPECT_EQ(TSIGError::BAD_TIME(),
              tsig_verify_ctx->verify(tsig.get(), &dummy_data[0],
                                      dummy_data.size()));
}

TEST_F(TSIGTest, badsigResponse) {
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    // Try to sign a simple message with bogus secret.  It should fail
    // with BADSIG.
    createMessageFromFile("message_toWire2.wire");
    TSIGContext bad_ctx(TSIGKey(test_name, TSIGKey::HMACMD5_NAME(),
                                &dummy_data[0], dummy_data.size()));
    {
        SCOPED_TRACE("Verify resulting in BADSIG");
        commonVerifyChecks(bad_ctx, message.getTSIGRecord(),
                           &received_data[0], received_data.size(),
                           TSIGError::BAD_SIG(), TSIGContext::RECEIVED_REQUEST);
    }

    // Sign the same message (which doesn't matter for this test) with the
    // context of "checked state".
    {
        SCOPED_TRACE("Sign test for response with BADSIG error");
        commonSignChecks(createMessageAndSign(qid, test_name, &bad_ctx),
                         message.getQid(), 0x4da8877a, NULL, 0,
                         16);   // 16: BADSIG
    }
}

TEST_F(TSIGTest, badkeyResponse) {
    // A similar test as badsigResponse but for BADKEY
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;
    tsig_ctx.reset(new TestTSIGContext(badkey_name, TSIGKey::HMACMD5_NAME(),
                                       keyring));
    {
        SCOPED_TRACE("Verify resulting in BADKEY");
        commonVerifyChecks(*tsig_ctx, &dummy_record, &dummy_data[0],
                           dummy_data.size(), TSIGError::BAD_KEY(),
                           TSIGContext::RECEIVED_REQUEST);
    }

    {
        SCOPED_TRACE("Sign test for response with BADKEY error");
        ConstTSIGRecordPtr sig = createMessageAndSign(qid, test_name,
                                                      tsig_ctx.get());
        EXPECT_EQ(badkey_name, sig->getName());
        commonSignChecks(sig, qid, 0x4da8877a, NULL, 0, 17);   // 17: BADKEY
    }
}

TEST_F(TSIGTest, badkeyForResponse) {
    // "BADKEY" case for a response to a signed message
    createMessageAndSign(qid, test_name, tsig_ctx.get());
    {
        SCOPED_TRACE("Verify a response resulting in BADKEY");
        commonVerifyChecks(*tsig_ctx, &dummy_record, &dummy_data[0],
                           dummy_data.size(), TSIGError::BAD_KEY(),
                           TSIGContext::SENT_REQUEST);
    }

    // A similar case with a different algorithm
    const TSIGRecord dummy_record2(test_name,
                                  any::TSIG(TSIGKey::HMACSHA1_NAME(),
                                            0x4da8877a,
                                            TSIGContext::DEFAULT_FUDGE,
                                            0, NULL, qid, 0, 0, NULL));
    {
        SCOPED_TRACE("Verify a response resulting in BADKEY due to bad alg");
        commonVerifyChecks(*tsig_ctx, &dummy_record2, &dummy_data[0],
                           dummy_data.size(), TSIGError::BAD_KEY(),
                           TSIGContext::SENT_REQUEST);
    }
}

TEST_F(TSIGTest, badsigThenValidate) {
    // According to RFC2845 4.6, if TSIG verification fails the client
    // should discard that message and wait for another signed response.
    // This test emulates that situation.

    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    createMessageAndSign(qid, test_name, tsig_ctx.get());

    createMessageFromFile("tsig_verify4.wire");
    {
        SCOPED_TRACE("Verify a response that should fail due to BADSIG");
        commonVerifyChecks(*tsig_ctx, message.getTSIGRecord(),
                           &received_data[0], received_data.size(),
                           TSIGError::BAD_SIG(), TSIGContext::SENT_REQUEST);
    }

    createMessageFromFile("tsig_verify5.wire");
    {
        SCOPED_TRACE("Verify a response after a BADSIG failure");
        commonVerifyChecks(*tsig_ctx, message.getTSIGRecord(),
                           &received_data[0], received_data.size(),
                           TSIGError::NOERROR(),
                           TSIGContext::VERIFIED_RESPONSE);
    }
}

TEST_F(TSIGTest, nosigThenValidate) {
    // Similar to the previous test, but the first response doesn't contain
    // TSIG.
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    createMessageAndSign(qid, test_name, tsig_ctx.get());

    {
        SCOPED_TRACE("Verify a response without TSIG that should exist");
        commonVerifyChecks(*tsig_ctx, NULL, &dummy_data[0],
                           dummy_data.size(), TSIGError::FORMERR(),
                           TSIGContext::SENT_REQUEST, true);
    }

    createMessageFromFile("tsig_verify5.wire");
    {
        SCOPED_TRACE("Verify a response after a FORMERR failure");
        commonVerifyChecks(*tsig_ctx, message.getTSIGRecord(),
                           &received_data[0], received_data.size(),
                           TSIGError::NOERROR(),
                           TSIGContext::VERIFIED_RESPONSE);
    }
}

TEST_F(TSIGTest, badtimeThenValidate) {
    // Similar to the previous test, but the first response results in BADTIME.
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    ConstTSIGRecordPtr tsig = createMessageAndSign(qid, test_name,
                                                   tsig_ctx.get());

    // "advance the clock" and try validating, which should fail due to BADTIME
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a + 600>;
    {
        SCOPED_TRACE("Verify resulting in BADTIME due to expired SIG");
        commonVerifyChecks(*tsig_ctx, tsig.get(), &dummy_data[0],
                           dummy_data.size(), TSIGError::BAD_TIME(),
                           TSIGContext::SENT_REQUEST);
    }

    // revert the clock again.
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;
    createMessageFromFile("tsig_verify5.wire");
    {
        SCOPED_TRACE("Verify a response after a BADTIME failure");
        commonVerifyChecks(*tsig_ctx, message.getTSIGRecord(),
                           &received_data[0], received_data.size(),
                           TSIGError::NOERROR(),
                           TSIGContext::VERIFIED_RESPONSE);
    }
}

TEST_F(TSIGTest, emptyMAC) {
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    // We don't allow empty MAC unless the TSIG error is BADSIG or BADKEY.
    createMessageFromFile("tsig_verify7.wire");
    {
        SCOPED_TRACE("Verify test for request");
        commonVerifyChecks(*tsig_verify_ctx, message.getTSIGRecord(),
                           &received_data[0], received_data.size(),
                           TSIGError::BAD_SIG(), TSIGContext::RECEIVED_REQUEST);
    }

    // If the empty MAC comes with a BADKEY error, the error is passed
    // transparently.
    createMessageFromFile("tsig_verify8.wire");
    {
        SCOPED_TRACE("Verify test for request");
        commonVerifyChecks(*tsig_verify_ctx, message.getTSIGRecord(),
                           &received_data[0], received_data.size(),
                           TSIGError::BAD_KEY(), TSIGContext::RECEIVED_REQUEST);
    }
}

TEST_F(TSIGTest, verifyAfterSendResponse) {
    // Once the context is used for sending a signed response, it shouldn't
    // be used for further verification.

    // The following are essentially the same as what verifyThenSignResponse
    // does with simplification.
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;
    createMessageFromFile("message_toWire2.wire");
    tsig_verify_ctx->verify(message.getTSIGRecord(), &received_data[0],
                            received_data.size());
    EXPECT_EQ(TSIGContext::RECEIVED_REQUEST, tsig_verify_ctx->getState());
    createMessageAndSign(qid, test_name, tsig_verify_ctx.get(),
                         QR_FLAG|AA_FLAG|RD_FLAG, RRType::A(), "192.0.2.1");
    EXPECT_EQ(TSIGContext::SENT_RESPONSE, tsig_verify_ctx->getState());

    // Now trying further verification.
    createMessageFromFile("message_toWire2.wire");
    EXPECT_THROW(tsig_verify_ctx->verify(message.getTSIGRecord(),
                                         &received_data[0],
                                         received_data.size()),
                 TSIGContextError);
}

TEST_F(TSIGTest, signAfterVerified) {
    // Likewise, once the context verifies a response, it shouldn't for
    // signing any more.

    // The following are borrowed from badsigThenValidate (without the
    // intermediate failure)
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;
    createMessageAndSign(qid, test_name, tsig_ctx.get());
    createMessageFromFile("tsig_verify5.wire");
    tsig_ctx->verify(message.getTSIGRecord(), &received_data[0],
                     received_data.size());
    EXPECT_EQ(TSIGContext::VERIFIED_RESPONSE, tsig_ctx->getState());

    // Now trying further signing.
    EXPECT_THROW(createMessageAndSign(qid, test_name, tsig_ctx.get()),
                 TSIGContextError);
}

TEST_F(TSIGTest, tooShortMAC) {
    // Too short MAC should be rejected.

    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;
    createMessageFromFile("tsig_verify10.wire");
    {
        SCOPED_TRACE("Verify test for request");
        commonVerifyChecks(*tsig_verify_ctx, message.getTSIGRecord(),
                           &received_data[0], received_data.size(),
                           TSIGError::FORMERR(), TSIGContext::RECEIVED_REQUEST);
    }
}

TEST_F(TSIGTest, truncatedMAC) {
    // Check truncated MAC support with HMAC-SHA512-256
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    secret.clear();
    decodeBase64("jI/Pa4qRu96t76Pns5Z/Ndxbn3QCkwcxLOgt9vgvnJw5wqTRvNyk3FtD6yIMd1dWVlqZ+Y4fe6Uasc0ckctEmg==", secret);
    TSIGContext sha_ctx(TSIGKey(test_name, TSIGKey::HMACSHA512_NAME(),
                                &secret[0], secret.size(), 256));

    createMessageFromFile("tsig_verify11.wire");
    {
        SCOPED_TRACE("Verify test for request");
        commonVerifyChecks(sha_ctx, message.getTSIGRecord(),
                           &received_data[0], received_data.size(),
                           TSIGError::NOERROR(), TSIGContext::RECEIVED_REQUEST);
    }

    // Try with HMAC-SHA512-264 (should fail)
    TSIGContext bad_sha_ctx(TSIGKey(test_name, TSIGKey::HMACSHA512_NAME(),
                                    &secret[0], secret.size(), 264));
    {
        SCOPED_TRACE("Verify test for request");
        commonVerifyChecks(bad_sha_ctx, message.getTSIGRecord(),
                           &received_data[0], received_data.size(),
                           TSIGError::BAD_TRUNC(), TSIGContext::RECEIVED_REQUEST);
    }
}

TEST_F(TSIGTest, getTSIGLength) {
    // Check for the most common case with various algorithms
    // See the comment in TSIGContext::getTSIGLength() for calculation and
    // parameter notation.
    // The key name (www.example.com) is the same for most cases, where n1=17

    // hmac-md5.sig-alg.reg.int.: n2=26, x=16
    EXPECT_EQ(85, tsig_ctx->getTSIGLength());

    // hmac-md5-80: n2=26, x=10
    tsig_ctx.reset(new TestTSIGContext(TSIGKey(test_name,
                                               TSIGKey::HMACMD5_NAME(),
                                               &dummy_data[0], 10, 80)));
    EXPECT_EQ(79, tsig_ctx->getTSIGLength());

    // hmac-sha1: n2=11, x=20
    tsig_ctx.reset(new TestTSIGContext(TSIGKey(test_name,
                                               TSIGKey::HMACSHA1_NAME(),
                                               &dummy_data[0], 20)));
    EXPECT_EQ(74, tsig_ctx->getTSIGLength());

    // hmac-sha256: n2=13, x=32
    tsig_ctx.reset(new TestTSIGContext(TSIGKey(test_name,
                                               TSIGKey::HMACSHA256_NAME(),
                                               &dummy_data[0], 32)));
    EXPECT_EQ(88, tsig_ctx->getTSIGLength());

    // hmac-sha224: n2=13, x=28
    tsig_ctx.reset(new TestTSIGContext(TSIGKey(test_name,
                                               TSIGKey::HMACSHA224_NAME(),
                                               &dummy_data[0], 28)));
    EXPECT_EQ(84, tsig_ctx->getTSIGLength());

    // hmac-sha384: n2=13, x=48
    tsig_ctx.reset(new TestTSIGContext(TSIGKey(test_name,
                                               TSIGKey::HMACSHA384_NAME(),
                                               &dummy_data[0], 48)));
    EXPECT_EQ(104, tsig_ctx->getTSIGLength());

    // hmac-sha512: n2=13, x=64
    tsig_ctx.reset(new TestTSIGContext(TSIGKey(test_name,
                                               TSIGKey::HMACSHA512_NAME(),
                                               &dummy_data[0], 64)));
    EXPECT_EQ(120, tsig_ctx->getTSIGLength());

    // hmac-sha512-256: n2=13, x=32
    tsig_ctx.reset(new TestTSIGContext(TSIGKey(test_name,
                                               TSIGKey::HMACSHA512_NAME(),
                                               &dummy_data[0], 32, 256)));
    EXPECT_EQ(88, tsig_ctx->getTSIGLength());

    // bad key case: n1=len(badkey.example.com)=20, n2=26, x=0
    tsig_ctx.reset(new TestTSIGContext(badkey_name, TSIGKey::HMACMD5_NAME(),
                                       keyring));
    EXPECT_EQ(72, tsig_ctx->getTSIGLength());

    // bad sig case: n1=17, n2=26, x=0
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;
    createMessageFromFile("message_toWire2.wire");
    tsig_ctx.reset(new TestTSIGContext(TSIGKey(test_name,
                                               TSIGKey::HMACMD5_NAME(),
                                               &dummy_data[0],
                                               dummy_data.size())));
    {
        SCOPED_TRACE("Verify resulting in BADSIG");
        commonVerifyChecks(*tsig_ctx, message.getTSIGRecord(),
                           &received_data[0], received_data.size(),
                           TSIGError::BAD_SIG(), TSIGContext::RECEIVED_REQUEST);
    }
    EXPECT_EQ(69, tsig_ctx->getTSIGLength());

    // bad time case: n1=17, n2=26, x=16, y=6
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a - 1000>;
    tsig_ctx.reset(new TestTSIGContext(TSIGKey(test_name,
                                               TSIGKey::HMACMD5_NAME(),
                                               &dummy_data[0],
                                               dummy_data.size())));
    {
        SCOPED_TRACE("Verify resulting in BADTIME");
        commonVerifyChecks(*tsig_ctx, message.getTSIGRecord(),
                           &received_data[0], received_data.size(),
                           TSIGError::BAD_TIME(),
                           TSIGContext::RECEIVED_REQUEST);
    }
    EXPECT_EQ(91, tsig_ctx->getTSIGLength());
}

// Verify a stream of multiple messages. Some of them have a signature omitted.
//
// We have two contexts, one that signs, another that verifies.
TEST_F(TSIGTest, verifyMulti) {
    isc::util::detail::gettimeFunction = testGetTime<0x4da8877a>;

    // First, send query from the verify one to the normal one, so
    // we initialize something like AXFR
    {
        SCOPED_TRACE("Query");
        ConstTSIGRecordPtr tsig = createMessageAndSign(1234, test_name,
                                                       tsig_verify_ctx.get());
        commonVerifyChecks(*tsig_ctx, tsig.get(),
                           renderer.getData(), renderer.getLength(),
                           TSIGError(Rcode::NOERROR()),
                           TSIGContext::RECEIVED_REQUEST);
    }

    {
        SCOPED_TRACE("First message");
        ConstTSIGRecordPtr tsig = createMessageAndSign(1234, test_name,
                                                       tsig_ctx.get());
        commonVerifyChecks(*tsig_verify_ctx, tsig.get(),
                           renderer.getData(), renderer.getLength(),
                           TSIGError(Rcode::NOERROR()),
                           TSIGContext::VERIFIED_RESPONSE);
        EXPECT_TRUE(tsig_verify_ctx->lastHadSignature());
    }

    {
        SCOPED_TRACE("Second message");
        ConstTSIGRecordPtr tsig = createMessageAndSign(1234, test_name,
                                                       tsig_ctx.get());
        commonVerifyChecks(*tsig_verify_ctx, tsig.get(),
                           renderer.getData(), renderer.getLength(),
                           TSIGError(Rcode::NOERROR()),
                           TSIGContext::VERIFIED_RESPONSE);
        EXPECT_TRUE(tsig_verify_ctx->lastHadSignature());
    }

    {
        SCOPED_TRACE("Third message. Unsigned.");
        // Another message does not carry the TSIG on it. But it should
        // be OK, it's in the middle of stream.
        message.clear(Message::RENDER);
        message.setQid(1234);
        message.setOpcode(Opcode::QUERY());
        message.setRcode(Rcode::NOERROR());
        RRsetPtr answer_rrset(new RRset(test_name, test_class, RRType::A(),
                                        test_ttl));
        answer_rrset->addRdata(createRdata(RRType::A(), test_class,
                                           "192.0.2.1"));
        message.addRRset(Message::SECTION_ANSWER, answer_rrset);
        message.toWire(renderer);
        // Update the internal state. We abuse the knowledge of
        // internals here a little bit to generate correct test data
        tsig_ctx->update(renderer.getData(), renderer.getLength());

        commonVerifyChecks(*tsig_verify_ctx, NULL,
                           renderer.getData(), renderer.getLength(),
                           TSIGError(Rcode::NOERROR()),
                           TSIGContext::VERIFIED_RESPONSE);

        EXPECT_FALSE(tsig_verify_ctx->lastHadSignature());
    }

    {
        SCOPED_TRACE("Fourth message. Signed again.");
        ConstTSIGRecordPtr tsig = createMessageAndSign(1234, test_name,
                                                       tsig_ctx.get());
        commonVerifyChecks(*tsig_verify_ctx, tsig.get(),
                           renderer.getData(), renderer.getLength(),
                           TSIGError(Rcode::NOERROR()),
                           TSIGContext::VERIFIED_RESPONSE);
        EXPECT_TRUE(tsig_verify_ctx->lastHadSignature());
    }

    {
        SCOPED_TRACE("Filling in bunch of unsigned messages");
        for (size_t i = 0; i < 100; ++i) {
            SCOPED_TRACE(i);
            // Another message does not carry the TSIG on it. But it should
            // be OK, it's in the middle of stream.
            message.clear(Message::RENDER);
            message.setQid(1234);
            message.setOpcode(Opcode::QUERY());
            message.setRcode(Rcode::NOERROR());
            RRsetPtr answer_rrset(new RRset(test_name, test_class, RRType::A(),
                                            test_ttl));
            answer_rrset->addRdata(createRdata(RRType::A(), test_class,
                                               "192.0.2.1"));
            message.addRRset(Message::SECTION_ANSWER, answer_rrset);
            message.toWire(renderer);
            // Update the internal state. We abuse the knowledge of
            // internals here a little bit to generate correct test data
            tsig_ctx->update(renderer.getData(), renderer.getLength());

            // 99 unsigned messages is OK. But the 100th must be signed, according
            // to the RFC2845, section 4.4
            commonVerifyChecks(*tsig_verify_ctx, NULL,
                               renderer.getData(), renderer.getLength(),
                               i == 99 ? TSIGError::FORMERR() :
                                   TSIGError(Rcode::NOERROR()),
                               TSIGContext::VERIFIED_RESPONSE);

            EXPECT_FALSE(tsig_verify_ctx->lastHadSignature());
        }
    }
}

} // end namespace
