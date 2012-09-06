# Copyright (C) 2011  Internet Systems Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

import base64, sys, time, unittest
from pydnspp import *
from testutil import *
from pyunittests_util import fix_current_time

# bit-wise constant flags to configure DNS header flags for test
# messages.
QR_FLAG = 0x1
AA_FLAG = 0x2
RD_FLAG = 0x4

COMMON_EXPECTED_MAC = b"\x22\x70\x26\xad\x29\x7b\xee\xe7\x21\xce\x6c\x6f\xff\x1e\x9e\xf3"
DUMMY_DATA = b"\xdd" * 100

class TSIGContextTest(unittest.TestCase):
    tsig_key = TSIGKey('www.example.com:SFuWd/q99SzF8Yzd1QbB9g==')

    def setUp(self):
        # make sure we don't use faked time unless explicitly do so in tests
        fix_current_time(None)
        self.qid = 0x2d65
        self.test_name = Name("www.example.com")
        self.tsig_ctx = TSIGContext(self.tsig_key)
        self.tsig_verify_ctx = TSIGContext(self.tsig_key)
        self.keyring = TSIGKeyRing()
        self.message = Message(Message.RENDER)
        self.renderer = MessageRenderer()
        self.test_class = RRClass.IN()
        self.test_ttl = RRTTL(86400)
        self.secret = base64.b64decode(b"SFuWd/q99SzF8Yzd1QbB9g==")
        self.tsig_ctx = TSIGContext(TSIGKey(self.test_name,
                                            TSIGKey.HMACMD5_NAME,
                                            self.secret))
        self.badkey_name = Name("badkey.example.com")
        self.dummy_record = TSIGRecord(self.badkey_name,
                                       TSIG("hmac-md5.sig-alg.reg.int. " + \
                                                "1302890362 300 0 11621 " + \
                                                "0 0"))

    def tearDown(self):
        # reset any faked current time setting (it would affect other tests)
        fix_current_time(None)

    # Note: intentionally use camelCase so that we can easily copy-paste
    # corresponding C++ tests.
    def createMessageAndSign(self, id, qname, ctx, message_flags=RD_FLAG,
                             qtype=RRType.A(), answer_data=None,
                             answer_type=None, add_question=True,
                             rcode=Rcode.NOERROR()):
        self.message.clear(Message.RENDER)
        self.message.set_qid(id)
        self.message.set_opcode(Opcode.QUERY())
        self.message.set_rcode(rcode)
        if (message_flags & QR_FLAG) != 0:
            self.message.set_header_flag(Message.HEADERFLAG_QR)
        if (message_flags & AA_FLAG) != 0:
            self.message.set_header_flag(Message.HEADERFLAG_AA)
        if (message_flags & RD_FLAG) != 0:
            self.message.set_header_flag(Message.HEADERFLAG_RD)
        if add_question:
            self.message.add_question(Question(qname, self.test_class, qtype))
        if answer_data is not None:
            if answer_type is None:
                answer_type = qtype
            answer_rrset = RRset(qname, self.test_class, answer_type,
                                 self.test_ttl)
            answer_rrset.add_rdata(Rdata(answer_type, self.test_class,
                                         answer_data))
            self.message.add_rrset(Message.SECTION_ANSWER, answer_rrset)
        self.renderer.clear()
        self.message.to_wire(self.renderer)

        if ctx.get_state() == TSIGContext.STATE_INIT:
            expected_new_state = TSIGContext.STATE_SENT_REQUEST
        else:
            expected_new_state = TSIGContext.STATE_SENT_RESPONSE
        tsig = ctx.sign(id, self.renderer.get_data())

        return tsig

    # Note: intentionally use camelCase so that we can easily copy-paste
    # corresponding C++ tests.
    def createMessageFromFile(self, file):
        self.message.clear(Message.PARSE)
        self.received_data = read_wire_data(file)
        self.message.from_wire(self.received_data)

    # Note: intentionally use camelCase so that we can easily copy-paste
    # corresponding C++ tests.
    def commonSignChecks(self, tsig, expected_qid, expected_timesigned,
                         expected_mac, expected_error=0,
                         expected_otherdata=None,
                         expected_algorithm=TSIGKey.HMACMD5_NAME):
        tsig_rdata = tsig.get_rdata()
        self.assertEqual(expected_algorithm, tsig_rdata.get_algorithm())
        self.assertEqual(expected_timesigned, tsig_rdata.get_timesigned())
        self.assertEqual(300, tsig_rdata.get_fudge())
        self.assertEqual(expected_mac, tsig_rdata.get_mac())
        self.assertEqual(expected_qid, tsig_rdata.get_original_id())
        self.assertEqual(expected_error, tsig_rdata.get_error())
        self.assertEqual(expected_otherdata, tsig_rdata.get_other_data())

    def test_initial_state(self):
        # Until signing or verifying, the state should be INIT
        self.assertEqual(TSIGContext.STATE_INIT, self.tsig_ctx.get_state())

        # And there should be no error code.
        self.assertEqual(TSIGError(Rcode.NOERROR()), self.tsig_ctx.get_error())

        # No message signed yet
        self.assertRaises(TSIGContextError, self.tsig_ctx.last_had_signature)

    # Note: intentionally use camelCase so that we can easily copy-paste
    # corresponding C++ tests.
    def commonVerifyChecks(self, ctx, record, data, expected_error,
                           expected_new_state=\
                               TSIGContext.STATE_VERIFIED_RESPONSE,
                           last_should_throw=False):
        self.assertEqual(expected_error, ctx.verify(record, data))
        self.assertEqual(expected_error, ctx.get_error())
        self.assertEqual(expected_new_state, ctx.get_state())
        if last_should_throw:
            self.assertRaises(TSIGContextError, ctx.last_had_signature)
        else:
            self.assertEqual(record is not None,
                             ctx.last_had_signature())
    def test_from_keyring(self):
        # Construct a TSIG context with an empty key ring.  Key shouldn't be
        # found, and the BAD_KEY error should be recorded.
        ctx = TSIGContext(self.test_name, TSIGKey.HMACMD5_NAME, self.keyring)
        self.assertEqual(TSIGContext.STATE_INIT, ctx.get_state())
        self.assertEqual(TSIGError.BAD_KEY, ctx.get_error())
        # check get_error() doesn't cause ref leak.  Note: we can't
        # realiably do this check for get_state(), as it returns an integer
        # object, which could have many references
        self.assertEqual(1, sys.getrefcount(ctx.get_error()))

        # Add a matching key (we don't use the secret so leave it empty), and
        # construct it again.  This time it should be constructed with a valid
        # key.
        self.keyring.add(TSIGKey(self.test_name, TSIGKey.HMACMD5_NAME, b""))
        ctx = TSIGContext(self.test_name, TSIGKey.HMACMD5_NAME, self.keyring)
        self.assertEqual(TSIGContext.STATE_INIT, ctx.get_state())
        self.assertEqual(TSIGError.NOERROR, ctx.get_error())

        # Similar to the first case except that the key ring isn't empty but
        # it doesn't contain a matching key.
        ctx = TSIGContext(self.test_name, TSIGKey.HMACSHA1_NAME, self.keyring)
        self.assertEqual(TSIGContext.STATE_INIT, ctx.get_state())
        self.assertEqual(TSIGError.BAD_KEY, ctx.get_error())

        ctx = TSIGContext(Name("different-key.example"),
                          TSIGKey.HMACMD5_NAME, self.keyring)
        self.assertEqual(TSIGContext.STATE_INIT, ctx.get_state())
        self.assertEqual(TSIGError.BAD_KEY, ctx.get_error())

        # "Unknown" algorithm name will result in BADKEY, too.
        ctx = TSIGContext(self.test_name, Name("unknown.algorithm"),
                          self.keyring)
        self.assertEqual(TSIGContext.STATE_INIT, ctx.get_state())
        self.assertEqual(TSIGError.BAD_KEY, ctx.get_error())

    def test_sign(self):
        fix_current_time(0x4da8877a)
        tsig = self.createMessageAndSign(self.qid, self.test_name,
                                         self.tsig_ctx)
        self.commonSignChecks(tsig, self.qid, 0x4da8877a, COMMON_EXPECTED_MAC)

    # Same test as sign, but specifying the key name with upper-case (i.e.
    # non canonical) characters.  The digest must be the same.  It should
    # actually be ensured at the level of TSIGKey, but we confirm that at
    # this level, too.
    def test_sign_using_uppercase_keyname(self):
        fix_current_time(0x4da8877a)
        cap_ctx = TSIGContext(TSIGKey(Name("WWW.EXAMPLE.COM"),
                                      TSIGKey.HMACMD5_NAME, self.secret))
        tsig = self.createMessageAndSign(self.qid, self.test_name, cap_ctx)
        self.commonSignChecks(tsig, self.qid, 0x4da8877a, COMMON_EXPECTED_MAC)

    # Same as the previous test, but for the algorithm name.
    def test_sign_using_uppercase_algorithm_name(self):
        fix_current_time(0x4da8877a)
        cap_ctx = TSIGContext(TSIGKey(self.test_name,
                                      Name("HMAC-md5.SIG-alg.REG.int"),
                                      self.secret))
        tsig = self.createMessageAndSign(self.qid, self.test_name, cap_ctx)
        self.commonSignChecks(tsig, self.qid, 0x4da8877a, COMMON_EXPECTED_MAC)

    # Sign the message using the actual time, and check the accuracy of it.
    # We cannot reasonably predict the expected MAC, so don't bother to
    # check it.
    def test_sign_at_actual_time(self):
        now = int(time.time())
        tsig = self.createMessageAndSign(self.qid, self.test_name,
                                         self.tsig_ctx)
        tsig_rdata = tsig.get_rdata()

        # Check the resulted time signed is in the range of [now, now + 5]
        self.assertTrue(now <= tsig_rdata.get_timesigned())
        self.assertTrue(now + 5 >= tsig_rdata.get_timesigned())

    def test_bad_data(self):
        self.assertRaises(TypeError, self.tsig_ctx.sign, None, 10)

    def test_verify_bad_data(self):
        # the data must at least hold the DNS message header and the specified
        # TSIG.
        bad_len = 12 + self.dummy_record.get_length() - 1
        self.assertRaises(InvalidParameter, self.tsig_ctx.verify,
                          self.dummy_record, DUMMY_DATA[:bad_len])

    def test_sign_using_hmacsha1(self):
        fix_current_time(0x4dae7d5f)

        secret = base64.b64decode(b"MA+QDhXbyqUak+qnMFyTyEirzng=")
        sha1_ctx = TSIGContext(TSIGKey(self.test_name, TSIGKey.HMACSHA1_NAME,
                                       secret))
        qid = 0x0967
        expected_mac = b"\x41\x53\x40\xc7\xda\xf8\x24\xed\x68\x4e\xe5\x86" + \
            b"\xf7\xb5\xa6\x7a\x2f\xeb\xc0\xd3"
        tsig = self.createMessageAndSign(qid, self.test_name, sha1_ctx)
        self.commonSignChecks(tsig, qid, 0x4dae7d5f, expected_mac,
                              0, None, TSIGKey.HMACSHA1_NAME)

    def test_verify_then_sign_response(self):
        fix_current_time(0x4da8877a)

        self.createMessageFromFile("message_toWire2.wire")
        self.commonVerifyChecks(self.tsig_verify_ctx,
                                self.message.get_tsig_record(),
                                self.received_data, TSIGError.NOERROR,
                                TSIGContext.STATE_RECEIVED_REQUEST)

        tsig = self.createMessageAndSign(self.qid, self.test_name,
                                         self.tsig_verify_ctx,
                                         QR_FLAG|AA_FLAG|RD_FLAG,
                                         RRType.A(), "192.0.2.1")

        expected_mac = b"\x8f\xcd\xa6\x6a\x7c\xd1\xa3\xb9\x94\x8e\xb1\x86" + \
            b"\x9d\x38\x4a\x9f"
        self.commonSignChecks(tsig, self.qid, 0x4da8877a, expected_mac)

    def test_verify_uppercase_names(self):
        fix_current_time(0x4da8877a)

        self.createMessageFromFile("tsig_verify9.wire")
        self.commonVerifyChecks(self.tsig_verify_ctx,
                                self.message.get_tsig_record(),
                                self.received_data, TSIGError.NOERROR,
                                TSIGContext.STATE_RECEIVED_REQUEST)

    def test_verify_forward_message(self):
        fix_current_time(0x4da8877a)

        self.createMessageFromFile("tsig_verify6.wire")
        self.commonVerifyChecks(self.tsig_verify_ctx,
                                self.message.get_tsig_record(),
                                self.received_data, TSIGError.NOERROR,
                                TSIGContext.STATE_RECEIVED_REQUEST)

    def test_sign_continuation(self):
        fix_current_time(0x4da8e951)

        axfr_qid = 0x3410
        zone_name = Name("example.com")

        tsig = self.createMessageAndSign(axfr_qid, zone_name, self.tsig_ctx,
                                         0, RRType.AXFR())

        received_data = read_wire_data("tsig_verify1.wire")
        self.commonVerifyChecks(self.tsig_verify_ctx, tsig, received_data,
                                TSIGError.NOERROR,
                                TSIGContext.STATE_RECEIVED_REQUEST)

        tsig = self.createMessageAndSign(axfr_qid, zone_name,
                                         self.tsig_verify_ctx,
                                         AA_FLAG|QR_FLAG, RRType.AXFR(),
                                         "ns.example.com. root.example.com." +\
                                         " 2011041503 7200 3600 2592000 1200",
                                         RRType.SOA())

        received_data = read_wire_data("tsig_verify2.wire")
        self.commonVerifyChecks(self.tsig_ctx, tsig, received_data,
                                TSIGError.NOERROR)

        expected_mac = b"\x10\x24\x58\xf7\xf6\x2d\xdd\x7d\x63\x8d\x74" +\
            b"\x60\x34\x13\x09\x68"
        tsig = self.createMessageAndSign(axfr_qid, zone_name,
                                         self.tsig_verify_ctx,
                                         AA_FLAG|QR_FLAG, RRType.AXFR(),
                                         "ns.example.com.", RRType.NS(),
                                         False)
        self.commonSignChecks(tsig, axfr_qid, 0x4da8e951, expected_mac)

        received_data = read_wire_data("tsig_verify3.wire")
        self.commonVerifyChecks(self.tsig_ctx, tsig, received_data,
                                TSIGError.NOERROR)

    def test_badtime_response(self):
        fix_current_time(0x4da8b9d6)

        test_qid = 0x7fc4
        tsig = self.createMessageAndSign(test_qid, self.test_name,
                                         self.tsig_ctx, 0, RRType.SOA())

        # "advance the clock" and try validating, which should fail due to
        # BADTIME
        fix_current_time(0x4da8be86)
        self.commonVerifyChecks(self.tsig_verify_ctx, tsig, DUMMY_DATA,
                                TSIGError.BAD_TIME,
                                TSIGContext.STATE_RECEIVED_REQUEST)

        # make and sign a response in the context of TSIG error.
        tsig = self.createMessageAndSign(test_qid, self.test_name,
                                         self.tsig_verify_ctx,
                                         QR_FLAG, RRType.SOA(), None, None,
                                         True, Rcode.NOTAUTH())

        expected_otherdata = b"\x00\x00\x4d\xa8\xbe\x86"
        expected_mac = b"\xd4\xb0\x43\xf6\xf4\x44\x95\xec\x8a\x01\x26" +\
            b"\x0e\x39\x15\x9d\x76"

        self.commonSignChecks(tsig, self.message.get_qid(), 0x4da8b9d6,
                              expected_mac,
                              18,     # error: BADTIME
                              expected_otherdata)

    def test_badtime_response2(self):
        fix_current_time(0x4da8b9d6)

        tsig = self.createMessageAndSign(self.qid, self.test_name,
                                         self.tsig_ctx, 0, RRType.SOA())

        # "rewind the clock" and try validating, which should fail due to
        # BADTIME
        fix_current_time(0x4da8b9d6 - 600)
        self.commonVerifyChecks(self.tsig_verify_ctx, tsig, DUMMY_DATA,
                           TSIGError.BAD_TIME,
                                TSIGContext.STATE_RECEIVED_REQUEST)

    # Test various boundary conditions.  We intentionally use the magic
    # number of 300 instead of the constant variable for testing.
    # In the okay cases, signature is not correct, but it's sufficient to
    # check the error code isn't BADTIME for the purpose of this test.
    def test_badtime_boundaries(self):
        fix_current_time(0x4da8b9d6)

        tsig = self.createMessageAndSign(self.qid, self.test_name,
                                         self.tsig_ctx, 0, RRType.SOA())

        fix_current_time(0x4da8b9d6 + 301)
        self.assertEqual(TSIGError.BAD_TIME,
                         self.tsig_verify_ctx.verify(tsig, DUMMY_DATA))

        fix_current_time(0x4da8b9d6 + 300)
        self.assertNotEqual(TSIGError.BAD_TIME,
                            self.tsig_verify_ctx.verify(tsig, DUMMY_DATA))

        fix_current_time(0x4da8b9d6 - 301)
        self.assertEqual(TSIGError.BAD_TIME,
                         self.tsig_verify_ctx.verify(tsig, DUMMY_DATA))

        fix_current_time(0x4da8b9d6 - 300)
        self.assertNotEqual(TSIGError.BAD_TIME,
                            self.tsig_verify_ctx.verify(tsig, DUMMY_DATA))

    def test_badtime_overflow(self):
        fix_current_time(200)
        tsig = self.createMessageAndSign(self.qid, self.test_name,
                                         self.tsig_ctx, 0, RRType.SOA())

        # This should be in the okay range, but since "200 - fudge" overflows
        # and we compare them as 64-bit unsigned integers, it results in a
        # false positive (we intentionally accept that).
        fix_current_time(100)
        self.assertEqual(TSIGError.BAD_TIME,
                         self.tsig_verify_ctx.verify(tsig, DUMMY_DATA))

    def test_badsig_response(self):
        fix_current_time(0x4da8877a)

        # Try to sign a simple message with bogus secret.  It should fail
        # with BADSIG.
        self.createMessageFromFile("message_toWire2.wire")
        bad_ctx = TSIGContext(TSIGKey(self.test_name, TSIGKey.HMACMD5_NAME,
                                      DUMMY_DATA))
        self.commonVerifyChecks(bad_ctx, self.message.get_tsig_record(),
                                self.received_data, TSIGError.BAD_SIG,
                                TSIGContext.STATE_RECEIVED_REQUEST)

        # Sign the same message (which doesn't matter for this test) with the
        # context of "checked state".
        tsig = self.createMessageAndSign(self.qid, self.test_name, bad_ctx)
        self.commonSignChecks(tsig, self.message.get_qid(), 0x4da8877a, None,
                              16)   # 16: BADSIG

    def test_badkey_response(self):
        # A similar test as badsigResponse but for BADKEY
        fix_current_time(0x4da8877a)
        tsig_ctx = TSIGContext(self.badkey_name, TSIGKey.HMACMD5_NAME,
                               self.keyring)
        self.commonVerifyChecks(tsig_ctx, self.dummy_record, DUMMY_DATA,
                                TSIGError.BAD_KEY,
                                TSIGContext.STATE_RECEIVED_REQUEST)

        sig = self.createMessageAndSign(self.qid, self.test_name, tsig_ctx)
        self.assertEqual(self.badkey_name, sig.get_name())
        self.commonSignChecks(sig, self.qid, 0x4da8877a, None, 17) # 17: BADKEY

    def test_badkey_for_response(self):
        # "BADKEY" case for a response to a signed message
        self.createMessageAndSign(self.qid, self.test_name, self.tsig_ctx)
        self.commonVerifyChecks(self.tsig_ctx, self.dummy_record, DUMMY_DATA,
                                TSIGError.BAD_KEY,
                                TSIGContext.STATE_SENT_REQUEST)

        # A similar case with a different algorithm
        dummy_record = TSIGRecord(self.test_name,
                                  TSIG("hmac-sha1. 1302890362 300 0 "
                                       "11621 0 0"))
        self.commonVerifyChecks(self.tsig_ctx, dummy_record, DUMMY_DATA,
                                TSIGError.BAD_KEY,
                                TSIGContext.STATE_SENT_REQUEST)

    # According to RFC2845 4.6, if TSIG verification fails the client
    # should discard that message and wait for another signed response.
    # This test emulates that situation.
    def test_badsig_then_validate(self):
        fix_current_time(0x4da8877a)

        self.createMessageAndSign(self.qid, self.test_name, self.tsig_ctx)
        self.createMessageFromFile("tsig_verify4.wire")

        self.commonVerifyChecks(self.tsig_ctx, self.message.get_tsig_record(),
                                self.received_data, TSIGError.BAD_SIG,
                                TSIGContext.STATE_SENT_REQUEST)

        self.createMessageFromFile("tsig_verify5.wire")
        self.commonVerifyChecks(self.tsig_ctx, self.message.get_tsig_record(),
                                self.received_data, TSIGError.NOERROR,
                                TSIGContext.STATE_VERIFIED_RESPONSE)

    # Similar to the previous test, but the first response doesn't contain
    # TSIG.
    def test_nosig_then_validate(self):
        fix_current_time(0x4da8877a)
        self.createMessageAndSign(self.qid, self.test_name, self.tsig_ctx)

        self.commonVerifyChecks(self.tsig_ctx, None, DUMMY_DATA,
                           TSIGError.FORMERR, TSIGContext.STATE_SENT_REQUEST,
                           True)

        self.createMessageFromFile("tsig_verify5.wire")
        self.commonVerifyChecks(self.tsig_ctx, self.message.get_tsig_record(),
                                self.received_data, TSIGError.NOERROR,
                                TSIGContext.STATE_VERIFIED_RESPONSE)

    # Similar to the previous test, but the first response results in BADTIME.
    def test_badtime_then_validate(self):
        fix_current_time(0x4da8877a)
        tsig = self.createMessageAndSign(self.qid, self.test_name,
                                         self.tsig_ctx)

        # "advance the clock" and try validating, which should fail due to
        # BADTIME
        fix_current_time(0x4da8877a + 600)
        self.commonVerifyChecks(self.tsig_ctx, tsig, DUMMY_DATA,
                           TSIGError.BAD_TIME, TSIGContext.STATE_SENT_REQUEST)

        # revert the clock again.
        fix_current_time(0x4da8877a)
        self.createMessageFromFile("tsig_verify5.wire")
        self.commonVerifyChecks(self.tsig_ctx, self.message.get_tsig_record(),
                                self.received_data, TSIGError.NOERROR,
                                TSIGContext.STATE_VERIFIED_RESPONSE)

    # We don't allow empty MAC unless the TSIG error is BADSIG or BADKEY.
    def test_empty_mac(self):
        fix_current_time(0x4da8877a)

        self.createMessageFromFile("tsig_verify7.wire")

        self.commonVerifyChecks(self.tsig_verify_ctx,
                                self.message.get_tsig_record(),
                                self.received_data,
                                TSIGError.BAD_SIG,
                                TSIGContext.STATE_RECEIVED_REQUEST)

        # If the empty MAC comes with a BADKEY error, the error is passed
        # transparently.
        self.createMessageFromFile("tsig_verify8.wire")
        self.commonVerifyChecks(self.tsig_verify_ctx,
                                self.message.get_tsig_record(),
                                self.received_data,
                                TSIGError.BAD_KEY,
                                TSIGContext.STATE_RECEIVED_REQUEST)

    # Once the context is used for sending a signed response, it shouldn't
    # be used for further verification.
    def test_verify_after_sendresponse(self):
        fix_current_time(0x4da8877a)

        self.createMessageFromFile("message_toWire2.wire")
        self.tsig_verify_ctx.verify(self.message.get_tsig_record(),
                                    self.received_data)
        self.assertEqual(TSIGContext.STATE_RECEIVED_REQUEST,
                         self.tsig_verify_ctx.get_state())
        self.createMessageAndSign(self.qid, self.test_name,
                                  self.tsig_verify_ctx,
                                  QR_FLAG|AA_FLAG|RD_FLAG, RRType.A(),
                                  "192.0.2.1")
        self.assertEqual(TSIGContext.STATE_SENT_RESPONSE,
                         self.tsig_verify_ctx.get_state())

        # Now trying further verification.
        self.createMessageFromFile("message_toWire2.wire")
        self.assertRaises(TSIGContextError, self.tsig_verify_ctx.verify,
                          self.message.get_tsig_record(), self.received_data)

    # Likewise, once the context verifies a response, it shouldn't for
    # signing any more.
    def test_sign_after_verified(self):
        fix_current_time(0x4da8877a)

        self.createMessageAndSign(self.qid, self.test_name, self.tsig_ctx)
        self.createMessageFromFile("tsig_verify5.wire")
        self.tsig_ctx.verify(self.message.get_tsig_record(),
                             self.received_data)
        self.assertEqual(TSIGContext.STATE_VERIFIED_RESPONSE,
                         self.tsig_ctx.get_state())

        # Now trying further signing.
        self.assertRaises(TSIGContextError, self.createMessageAndSign,
                          self.qid, self.test_name, self.tsig_ctx)

    # Too short MAC should be rejected.
    # Note: when we implement RFC4635-based checks, the error code will
    # (probably) be FORMERR.
    def test_too_short_mac(self):
        fix_current_time(0x4da8877a)
        self.createMessageFromFile("tsig_verify10.wire")
        self.commonVerifyChecks(self.tsig_verify_ctx,
                                self.message.get_tsig_record(),
                                self.received_data, TSIGError.BAD_SIG,
                                TSIGContext.STATE_RECEIVED_REQUEST)

if __name__ == '__main__':
    unittest.main()
