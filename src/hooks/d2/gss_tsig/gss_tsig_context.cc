// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dns/rrclass.h>
#include <gss_tsig_context.h>
#include <gss_tsig_log.h>
#include <gss_tsig_messages.h>
#include <util/io.h>

#include <limits>

using namespace isc;
using namespace isc::d2;
using namespace isc::dns;
using namespace isc::dns::rdata::any;
using namespace isc::gss_tsig;
using namespace isc::log;
using namespace isc::util;
using namespace std;

namespace {

/// @brief DNS message header length.
const size_t MESSAGE_HEADER_LEN = 12;

/// @brief GSS-TSIG digest length (from bind9 dst_key_sigsize).
const size_t DIGEST_LEN = 128;
static_assert(DIGEST_LEN <= numeric_limits<uint16_t>::max(),
              "DIGEST_LEN must fit in a uint16_t");

/// @brief Digest previous MAC.
///
/// @note: the previous MAC size always fits in 16 bits.
///
/// @param buffer Reference to the output buffer.
/// @param previous_digest Previous digest.
void
digestPreviousMAC(OutputBuffer& buffer, const vector<uint8_t>& previous_digest) {
    if (previous_digest.empty()) {
        // The previous digest was already used. We're in the middle of
        // TCP stream somewhere and we already pushed some unsigned message
        // into the MAC state.
        return;
    }

    const uint16_t previous_digest_len(previous_digest.size());
    buffer.writeUint16(previous_digest_len);
    buffer.writeData(&previous_digest[0], previous_digest_len);
}

/// @brief Digest TSIG variables.
///
/// @param buffer Reference to the output buffer.
/// @param key The GSS-TSIG key.
/// @param rrclass Resource Record class.
/// @param ttl Resource Record Time To Live.
/// @param time_signed Time signed.
/// @param fudge Fudge.
/// @param error DNS error.
/// @param otherlen Other data length.
/// @param otherdata Pointer to other data.
/// @param time_variables_only True if only time variables must be digested.
void
digestTSIGVariables(OutputBuffer& buffer, const GssTsigKey& key,
                    uint16_t rrclass, uint32_t rrttl,
                    uint64_t time_signed, uint16_t fudge, uint16_t error,
                    uint16_t otherlen, const void* otherdata,
                    bool time_variables_only) {
    if (!time_variables_only) {
        key.getKeyName().toWire(buffer);
        buffer.writeUint16(rrclass);
        buffer.writeUint32(rrttl);
        key.getAlgorithmName().toWire(buffer);
    }
    buffer.writeUint16(time_signed >> 32);
    buffer.writeUint32(time_signed & 0xffffffff);
    buffer.writeUint16(fudge);
    if (!time_variables_only) {
        buffer.writeUint16(error);
        buffer.writeUint16(otherlen);
        if (otherlen > 0) {
            buffer.writeData(otherdata, otherlen);
        }
    }
}

/// @brief Digest DNS message.
///
/// Here, we exploit some minimum knowledge of DNS message format:
/// - the header section has a fixed length of 12 octets (MESSAGE_HEADER_LEN)
/// - the offset in the header section to the ID field is 0
/// - the offset in the header section to the ARCOUNT field is 10
///   (and the field length is 2 octets)
/// We could construct a separate Message object from the given data, adjust
/// fields via the Message interfaces and then render it back to a separate
/// buffer, but that would be overkilling.  The DNS message header has a
/// fixed length and necessary modifications are quite straightforward, so
/// we do the job using lower level interfaces.
///
/// @param buffer Reference to the output buffer.
/// @param qid Original query ID.
/// @param data Points to the wire-format data (already checked for 0).
/// @param data_len The length of @c data in bytes (already checked to
/// be large enough).
void
digestDNSMessage(OutputBuffer& buffer, uint16_t qid, const void* data,
                 size_t data_len) {
    if (!data || (data_len < MESSAGE_HEADER_LEN)) {
        // Should not happen as it was already checked by the caller.
        isc_throw(Unexpected, "digestDNSMessage called with bad data");
    }
    OutputBuffer hdr(MESSAGE_HEADER_LEN);
    const uint8_t* msgptr = static_cast<const uint8_t*>(data);

    // Install the original ID.
    hdr.writeUint16(qid);
    msgptr += sizeof(uint16_t);

    // Copy the rest of the header except the ARCOUNT field.
    hdr.writeData(msgptr, 8);
    msgptr += 8;

    // Install the adjusted ARCOUNT (we don't care even if the value is bogus
    // and it underflows; it would simply result in verification failure).
    hdr.writeUint16(InputBuffer(msgptr, sizeof(uint16_t)).readUint16() - 1);
    msgptr += 2;

    // Digest the header and the rest of the DNS message.
    buffer.writeData(hdr.getData(), hdr.getLength());
    buffer.writeData(msgptr, data_len - MESSAGE_HEADER_LEN);
}

}

namespace isc {
namespace gss_tsig {

GssTsigContext::GssTsigContext(GssTsigKey& key)
    : TSIGContext(key), state_(INIT), key_(key), previous_digest_(),
      error_(TSIGError::NOERROR()), previous_timesigned_(0),
      last_sig_dist_(-1), tbs_(1024) {
}

GssTsigContext::~GssTsigContext() {
}

ConstTSIGRecordPtr
GssTsigContext::sign(const uint16_t qid, const void* const data,
                     const size_t data_len) {
    if (state_ == VERIFIED_RESPONSE) {
        isc_throw(TSIGContextError,
                  "TSIG sign attempt after verifying a response");
    }

    if (!data || (data_len == 0)) {
        isc_throw(InvalidParameter, "TSIG sign error: empty data is given");
    }

    TSIGError error(TSIGError::NOERROR());
    const uint64_t now = static_cast<uint64_t>(time(0));

    // For responses adjust the error code.
    if (state_ == RECEIVED_REQUEST) {
        error = error_;
    }

    // For errors related to key or MAC, return an unsigned response as
    // specified in Section 4.3 of RFC2845.
    if (error == TSIGError::BAD_SIG() || error == TSIGError::BAD_KEY()) {
        ConstTSIGRecordPtr
            tsig(new TSIGRecord(key_.getKeyName(),
                                TSIG(key_.getAlgorithmName(),
                                     now, DEFAULT_FUDGE, 0, 0,
                                     qid, error.getCode(), 0, 0)));
        previous_digest_.clear();
        state_ = SENT_RESPONSE;
        return (tsig);
    }

    if (!key_.getSecCtx().get()) {
        isc_throw(Unexpected, "sign called with null security context");
    }

    // If the context has previous MAC (either the Request MAC or its own
    // previous MAC), digest it.
    if (state_ != INIT) {
        digestPreviousMAC(tbs_, previous_digest_);
    }

    // Digest the message (without TSIG).
    tbs_.writeData(data, data_len);

    // Digest TSIG variables.
    // First, prepare some non constant variables.
    uint64_t time_signed = now;
    uint16_t otherlen = 0;
    OutputBuffer otherdata(otherlen);
    // For BADTIME error, we include 6 bytes of other data.
    // (6 bytes = size of time signed value).
    if (error == TSIGError::BAD_TIME()) {
        time_signed = previous_timesigned_;
        otherlen = 6;
        otherdata.writeUint16(now >> 32);
        otherdata.writeUint32(now & 0xffffffff);
    }
    // Then calculate the digest.  If state_ is SENT_RESPONSE we are sending
    // a continued message in the same TCP stream so skip digesting
    // variables except for time related variables (RFC2845 4.4).
    digestTSIGVariables(tbs_, key_,
                        TSIGRecord::getClass().getCode(),
                        TSIGRecord::TSIG_TTL, time_signed,
                        DEFAULT_FUDGE, error.getCode(),
                        otherlen, otherlen ? otherdata.getData() : 0,
                        state_ == SENT_RESPONSE);

    // Get the final digest, update internal state, then finish.
    GssApiBuffer gtbs(tbs_.getLength(), tbs_.getData());
    // Consume the to be signed buffer.
    tbs_.clear();
    GssApiBuffer gsign;
    key_.getSecCtx().sign(gtbs, gsign);
    if (gsign.getLength() > DIGEST_LEN) {
        isc_throw(OutOfRange, "internal error: digest is larger than "
                  << DIGEST_LEN);
    }
    ConstTSIGRecordPtr
        tsig(new TSIGRecord(key_.getKeyName(),
                            TSIG(key_.getAlgorithmName(),
                                 time_signed, DEFAULT_FUDGE,
                                 gsign.getLength(), gsign.getValue(),
                                 qid, error.getCode(), otherlen,
                                 otherlen ? otherdata.getData() : 0)));
    previous_digest_ = gsign.getContent();
    if (state_ == INIT) {
        state_ = SENT_REQUEST;
    } else {
        state_ = SENT_RESPONSE;
    }
    return (tsig);
}

TSIGError
GssTsigContext::verify(const dns::TSIGRecord* const record,
                       const void* const data, const size_t data_len) {
    if (state_ == SENT_RESPONSE) {
        isc_throw(TSIGContextError,
                  "TSIG verify attempt after sending a response");
    }

    // This helper method is used from verify().  It's expected to be called
    // just before verify() returns.  It updates internal state based on
    // the verification result and return the TSIGError to be returned to
    // the caller of verify(), so that verify() can call this method within
    // its 'return' statement.
    auto postVerifyUpdate = [&] (TSIGError error) -> TSIGError {
        if (state_ == INIT) {
            state_ = RECEIVED_REQUEST;
        } else if ((state_ == SENT_REQUEST) &&
                   (error == TSIGError::NOERROR())) {
            state_ = VERIFIED_RESPONSE;
        }
        error_ = error;
        return (error);
    };

    // This code supports an obsolete feature of TSIG removed by RFC 8945:
    // in a zone transfer it was allowed to not signed up to 99 consecutive
    // messages. Note that all modern DNS servers sign all messages.
    // Hopefully this code will be never used.
    if (!record) {
        if ((last_sig_dist_ >= 0) && (last_sig_dist_ < 99)) {
            // It is not signed, but in the middle of TCP stream. We just
            // update the MAC state and consider this message OK.
            update(data, data_len);
            // This one is not signed, the last signed is one message further
            // now.
            ++last_sig_dist_;
            // No digest to return now. Just say it's OK.
            return (postVerifyUpdate(TSIGError::NOERROR()));
        }
        // This case happens when we sent a signed request and have received an
        // unsigned response.  According to RFC2845 Section 4.6 this case should be
        // considered a "format error" (although the specific error code
        // wouldn't matter much for the caller).
        return (postVerifyUpdate(TSIGError::FORMERR()));
    }

    const TSIG& tsig_rdata = record->getRdata();

    if (data_len < MESSAGE_HEADER_LEN + record->getLength()) {
        isc_throw(InvalidParameter,
                  "TSIG verify: data length is invalid: " << data_len);
    }
    if (!data) {
        isc_throw(InvalidParameter, "TSIG verify: empty data is invalid");
    }

    if (!key_.getSecCtx().get()) {
        isc_throw(Unexpected, "verify called with null security context");
    }

    // This message is signed and we won't throw any more.
    last_sig_dist_ = 0;

    // Check key: whether we first verify it with a known key or we verify
    // it using the consistent key in the context.  If the check fails we are
    // done with BADKEY.
    if ((state_ == INIT) && (error_ == TSIGError::BAD_KEY())) {
        return (postVerifyUpdate(TSIGError::BAD_KEY()));
    }
    if ((key_.getKeyName() != record->getName()) ||
        (key_.getAlgorithmName() != tsig_rdata.getAlgorithm())) {
        return (postVerifyUpdate(TSIGError::BAD_KEY()));
    }

    // Check time: the current time must be in the range of
    // [time signed - fudge, time signed + fudge].  Otherwise verification
    // fails with BADTIME. (RFC2845 Section 4.6.2)
    // Note: for simplicity we don't explicitly catch the case of too small
    // current time causing underflow.  With the fact that fudge is quite
    // small and (for now) non configurable, it shouldn't be a real concern
    // in practice.
    const uint64_t now = static_cast<uint64_t>(time(0));
    if (tsig_rdata.getTimeSigned() + DEFAULT_FUDGE < now ||
        tsig_rdata.getTimeSigned() - DEFAULT_FUDGE > now) {
        if (state_ == INIT) {
            const uint8_t* digest =
                static_cast<const uint8_t*>(tsig_rdata.getMAC());
            if (digest) {
                previous_digest_.assign(digest,
                                        digest + tsig_rdata.getMACSize());
            }
            previous_timesigned_ = tsig_rdata.getTimeSigned();
        }
        return (postVerifyUpdate(TSIGError::BAD_TIME()));
    }

    // Handling empty MAC.  While RFC2845 doesn't explicitly prohibit other
    // cases, it can only reasonably happen in a response with BADSIG or
    // BADKEY.  We reject other cases as if it were BADSIG to avoid unexpected
    // acceptance of a bogus signature.  This behavior follows the BIND 9
    // implementation.
    if (tsig_rdata.getMACSize() == 0) {
        TSIGError error = TSIGError(tsig_rdata.getError());
        if ((error != TSIGError::BAD_SIG()) &&
            (error != TSIGError::BAD_KEY())) {
            error = TSIGError::BAD_SIG();
        }
        return (postVerifyUpdate(error));
    }

    // If the context has previous MAC (either the Request MAC or its own
    // previous MAC), digest it.
    if (state_ != INIT) {
        digestPreviousMAC(tbs_, previous_digest_);
    }

    // No signature length check with GSS-TSIG.

    //
    // Digest DNS message (excluding the trailing TSIG RR and adjusting the
    // QID and ARCOUNT header fields)
    //
    digestDNSMessage(tbs_, tsig_rdata.getOriginalID(),
                     data, data_len - record->getLength());

    // Digest TSIG variables.  If state_ is VERIFIED_RESPONSE, it's a
    // continuation of the same TCP stream and skip digesting them except
    // for time related variables (RFC2845 4.4).
    // Note: we use the constant values for RR class and TTL specified
    // in RFC2845, not received values (we reject other values in constructing
    // the TSIGRecord).
    digestTSIGVariables(tbs_, key_,
                        TSIGRecord::getClass().getCode(),
                        TSIGRecord::TSIG_TTL,
                        tsig_rdata.getTimeSigned(),
                        tsig_rdata.getFudge(), tsig_rdata.getError(),
                        tsig_rdata.getOtherLen(),
                        tsig_rdata.getOtherData(),
                        state_ == VERIFIED_RESPONSE);

    // Verify the digest with the received signature.
    try {
        GssApiBuffer gtbv(tbs_.getLength(), tbs_.getData());
        // Consume the to be verified buffer.
        tbs_.clear();
        GssApiBuffer gsign(tsig_rdata.getMACSize(), tsig_rdata.getMAC());
        key_.getSecCtx().verify(gtbv, gsign);
        LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, GSS_TSIG_VERIFIED);
        const uint8_t* digest =
            static_cast<const uint8_t*>(tsig_rdata.getMAC());
        previous_digest_.assign(digest, digest + tsig_rdata.getMACSize());
        return (postVerifyUpdate(TSIGError::NOERROR()));
    } catch (const Exception& ex) {
        LOG_INFO(gss_tsig_logger, GSS_TSIG_VERIFY_FAILED)
            .arg(ex.what());
    }
    return (postVerifyUpdate(TSIGError::BAD_SIG()));
}

bool
GssTsigContext::lastHadSignature() const {
    if (last_sig_dist_ == -1) {
        isc_throw(TSIGContextError, "No message was verified yet");
    }
    return (last_sig_dist_ == 0);
}

size_t
GssTsigContext::getTSIGLength() const {
    //
    // The space required for an TSIG record is:
    //
    //  n1 bytes for the (key) name
    //  2 bytes for the type
    //  2 bytes for the class
    //  4 bytes for the ttl
    //  2 bytes for the rdlength
    //  n2 bytes for the algorithm name
    //  6 bytes for the time signed
    //  2 bytes for the fudge
    //  2 bytes for the MAC size
    //  x bytes for the MAC
    //  2 bytes for the original id
    //  2 bytes for the error
    //  2 bytes for the other data length
    //  y bytes for the other data (at most)
    // ---------------------------------
    //     26 + n1 + n2 + x + y bytes
    //

    // Normally the digest length ("x") is the length of the underlying
    // hash output.  If a key related error occurred, however, the
    // corresponding TSIG will be "unsigned", and the digest length will be 0.
    size_t digest_len = DIGEST_LEN;
    if  (error_ == TSIGError::BAD_KEY() || error_ == TSIGError::BAD_SIG()) {
        digest_len = 0;
    }

    // Other Len ("y") is normally 0; if BAD_TIME error occurred, the
    // subsequent TSIG will contain 48 bits of the server current time.
    size_t other_len = 0;
    if (error_ == TSIGError::BAD_TIME()) {
        other_len = 6;
    }

    return (26 + key_.getKeyName().getLength() +
            key_.getAlgorithmName().getLength() +
            digest_len + other_len);
}

void
GssTsigContext::update(const void* const data, size_t len) {
    // Use the previous digest and never use it again.
    digestPreviousMAC(tbs_, previous_digest_);
    previous_digest_.clear();
    // Push the message there.
    tbs_.writeData(data, len);
}

} // end of namespace isc::gss_tsig
} // end of namespace isc
