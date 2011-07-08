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

#include <sys/time.h>

#include <stdint.h>

#include <cassert>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <util/time_utilities.h>

#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/tsig.h>
#include <dns/tsigerror.h>
#include <dns/tsigkey.h>

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_hmac.h>

using namespace std;
using namespace isc::util;
using namespace isc::cryptolink;
using namespace isc::dns::rdata;

namespace isc {
namespace dns {
namespace {
typedef boost::shared_ptr<HMAC> HMACPtr;

// TSIG uses 48-bit unsigned integer to represent time signed.
// Since gettimeWrapper() returns a 64-bit *signed* integer, we
// make sure it's stored in an unsigned 64-bit integer variable and
// represents a value in the expected range.  (In reality, however,
// gettimeWrapper() will return a positive integer that will fit
// in 48 bits)
uint64_t
getTSIGTime() {
    return (detail::gettimeWrapper() & 0x0000ffffffffffffULL);
}
}

struct TSIGContext::TSIGContextImpl {
    TSIGContextImpl(const TSIGKey& key,
                    TSIGError error = TSIGError::NOERROR()) :
        state_(INIT), key_(key), error_(error),
        previous_timesigned_(0), digest_len_(0)
    {
        if (error == TSIGError::NOERROR()) {
            // In normal (NOERROR) case, the key should be valid, and we
            // should be able to pre-create a corresponding HMAC object,
            // which will be likely to be used for sign or verify later.
            // We do this in the constructor so that we can know the expected
            // digest length in advance.  The creation should normally succeed,
            // but the key information could be still broken, which could
            // trigger an exception inside the cryptolink module.  We ignore
            // it at this moment; a subsequent sign/verify operation will try
            // to create the HMAC, which would also fail.
            try {
                hmac_.reset(CryptoLink::getCryptoLink().createHMAC(
                                key_.getSecret(), key_.getSecretLength(),
                                key_.getAlgorithm()),
                            deleteHMAC);
            } catch (const Exception&) {
                return;
            }
            digest_len_ = hmac_->getOutputLength();
        }
    }

    // This helper method is used from verify().  It's expected to be called
    // just before verify() returns.  It updates internal state based on
    // the verification result and return the TSIGError to be returned to
    // the caller of verify(), so that verify() can call this method within
    // its 'return' statement.
    TSIGError postVerifyUpdate(TSIGError error, const void* digest,
                               uint16_t digest_len)
    {
        if (state_ == INIT) {
            state_ = RECEIVED_REQUEST;
        } else if (state_ == SENT_REQUEST && error == TSIGError::NOERROR()) {
            state_ = VERIFIED_RESPONSE;
        }
        if (digest != NULL) {
            previous_digest_.assign(static_cast<const uint8_t*>(digest),
                                    static_cast<const uint8_t*>(digest) +
                                    digest_len);
        }
        error_ = error;
        return (error);
    }

    // A shortcut method to create an HMAC object for sign/verify.  If one
    // has been successfully created in the constructor, return it; otherwise
    // create a new one and return it.
    HMACPtr getHMAC() {
        if (hmac_) {
            HMACPtr ret = HMACPtr();
            ret.swap(hmac_);
            return (ret);
        }
        return (HMACPtr(CryptoLink::getCryptoLink().createHMAC(
                            key_.getSecret(), key_.getSecretLength(),
                            key_.getAlgorithm()),
                        deleteHMAC));
    }

    // The following three are helper methods to compute the digest for
    // TSIG sign/verify in order to unify the common code logic for sign()
    // and verify() and to keep these callers concise.
    // These methods take an HMAC object, which will be updated with the
    // calculated digest.
    // Note: All methods construct a local OutputBuffer as a work space with a
    // fixed initial buffer size to avoid intermediate buffer extension.
    // This should be efficient enough, especially for fundamentally expensive
    // operation like cryptographic sign/verify, but if the creation of the
    // buffer in each helper method is still identified to be a severe
    // performance bottleneck, we could have this class a buffer as a member
    // variable and reuse it throughout the object's lifetime.  Right now,
    // we prefer keeping the scope for local things as small as possible.
    void digestPreviousMAC(HMACPtr hmac) const;
    void digestTSIGVariables(HMACPtr hmac, uint16_t rrclass, uint32_t rrttl,
                             uint64_t time_signed, uint16_t fudge,
                             uint16_t error, uint16_t otherlen,
                             const void* otherdata,
                             bool time_variables_only) const;
    void digestDNSMessage(HMACPtr hmac, uint16_t qid, const void* data,
                          size_t data_len) const;
    State state_;
    const TSIGKey key_;
    vector<uint8_t> previous_digest_;
    TSIGError error_;
    uint64_t previous_timesigned_; // only meaningful for response with BADTIME
    size_t digest_len_;
    HMACPtr hmac_;
};

void
TSIGContext::TSIGContextImpl::digestPreviousMAC(HMACPtr hmac) const {
    // We should have ensured the digest size fits 16 bits within this class
    // implementation.
    assert(previous_digest_.size() <= 0xffff);

    OutputBuffer buffer(sizeof(uint16_t) + previous_digest_.size());
    const uint16_t previous_digest_len(previous_digest_.size());
    buffer.writeUint16(previous_digest_len);
    if (previous_digest_len != 0) {
        buffer.writeData(&previous_digest_[0], previous_digest_len);
    }
    hmac->update(buffer.getData(), buffer.getLength());
}

void
TSIGContext::TSIGContextImpl::digestTSIGVariables(
    HMACPtr hmac, uint16_t rrclass, uint32_t rrttl, uint64_t time_signed,
    uint16_t fudge, uint16_t error, uint16_t otherlen, const void* otherdata,
    bool time_variables_only) const
{
    // It's bit complicated, but we can still predict the necessary size of
    // the data to be digested.  So we precompute it to avoid possible
    // reallocation inside OutputBuffer (not absolutely necessary, but this
    // is a bit more efficient)
    size_t data_size = 8;
    if (!time_variables_only) {
        data_size += 10 + key_.getKeyName().getLength() +
            key_.getAlgorithmName().getLength();
    }
    OutputBuffer buffer(data_size);

    if (!time_variables_only) {
        key_.getKeyName().toWire(buffer);
        buffer.writeUint16(rrclass);
        buffer.writeUint32(rrttl);
        key_.getAlgorithmName().toWire(buffer);
    }
    buffer.writeUint16(time_signed >> 32);
    buffer.writeUint32(time_signed & 0xffffffff);
    buffer.writeUint16(fudge);

    if (!time_variables_only) {
        buffer.writeUint16(error);
        buffer.writeUint16(otherlen);
    }

    hmac->update(buffer.getData(), buffer.getLength());
    if (!time_variables_only && otherlen > 0) {
        hmac->update(otherdata, otherlen);
    }
}

// In digestDNSMessage, we exploit some minimum knowledge of DNS message
// format:
// - the header section has a fixed length of 12 octets (MESSAGE_HEADER_LEN)
// - the offset in the header section to the ID field is 0
// - the offset in the header section to the ARCOUNT field is 10 (and the field
//   length is 2 octets)
// We could construct a separate Message object from the given data, adjust
// fields via the Message interfaces and then render it back to a separate
// buffer, but that would be overkilling.  The DNS message header has a
// fixed length and necessary modifications are quite straightforward, so
// we do the job using lower level interfaces.
namespace {
const size_t MESSAGE_HEADER_LEN = 12;
}
void
TSIGContext::TSIGContextImpl::digestDNSMessage(HMACPtr hmac,
                                               uint16_t qid, const void* data,
                                               size_t data_len) const
{
    OutputBuffer buffer(MESSAGE_HEADER_LEN);
    const uint8_t* msgptr = static_cast<const uint8_t*>(data);

    // Install the original ID
    buffer.writeUint16(qid);
    msgptr += sizeof(uint16_t);

    // Copy the rest of the header except the ARCOUNT field.
    buffer.writeData(msgptr, 8);
    msgptr += 8;

    // Install the adjusted ARCOUNT (we don't care even if the value is bogus
    // and it underflows; it would simply result in verification failure)
    buffer.writeUint16(InputBuffer(msgptr, sizeof(uint16_t)).readUint16() - 1);
    msgptr += 2;

    // Digest the header and the rest of the DNS message
    hmac->update(buffer.getData(), buffer.getLength());
    hmac->update(msgptr, data_len - MESSAGE_HEADER_LEN);
}

TSIGContext::TSIGContext(const TSIGKey& key) : impl_(new TSIGContextImpl(key))
{
}

TSIGContext::TSIGContext(const Name& key_name, const Name& algorithm_name,
                         const TSIGKeyRing& keyring) : impl_(NULL)
{
    const TSIGKeyRing::FindResult result(keyring.find(key_name,
                                                      algorithm_name));
    if (result.code == TSIGKeyRing::NOTFOUND) {
        // If not key is found, create a dummy key with the specified key
        // parameters and empty secret.  In the common scenario this will
        // be used in subsequent response with a TSIG indicating a BADKEY
        // error.
        impl_ = new TSIGContextImpl(TSIGKey(key_name, algorithm_name,
                                            NULL, 0), TSIGError::BAD_KEY());
    } else {
        impl_ = new TSIGContextImpl(*result.key);
    }
}

TSIGContext::~TSIGContext() {
    delete impl_;
}

TSIGContext::State
TSIGContext::getState() const {
    return (impl_->state_);
}

TSIGError
TSIGContext::getError() const {
    return (impl_->error_);
}

ConstTSIGRecordPtr
TSIGContext::sign(const uint16_t qid, const void* const data,
                  const size_t data_len)
{
    if (impl_->state_ == VERIFIED_RESPONSE) {
        isc_throw(TSIGContextError,
                  "TSIG sign attempt after verifying a response");
    }

    if (data == NULL || data_len == 0) {
        isc_throw(InvalidParameter, "TSIG sign error: empty data is given");
    }

    TSIGError error(TSIGError::NOERROR());
    const uint64_t now = getTSIGTime();

    // For responses adjust the error code.
    if (impl_->state_ == RECEIVED_REQUEST) {
        error = impl_->error_;
    }

    // For errors related to key or MAC, return an unsigned response as
    // specified in Section 4.3 of RFC2845.
    if (error == TSIGError::BAD_SIG() || error == TSIGError::BAD_KEY()) {
        ConstTSIGRecordPtr tsig(new TSIGRecord(
                                    impl_->key_.getKeyName(),
                                    any::TSIG(impl_->key_.getAlgorithmName(),
                                              now, DEFAULT_FUDGE, 0, NULL,
                                              qid, error.getCode(), 0, NULL)));
        impl_->previous_digest_.clear();
        impl_->state_ = SENT_RESPONSE;
        return (tsig);
    }

    HMACPtr hmac(impl_->getHMAC());

    // If the context has previous MAC (either the Request MAC or its own
    // previous MAC), digest it.
    if (impl_->state_ != INIT) {
        impl_->digestPreviousMAC(hmac);
    }

    // Digest the message (without TSIG)
    hmac->update(data, data_len);

    // Digest TSIG variables.
    // First, prepare some non constant variables.
    const uint64_t time_signed = (error == TSIGError::BAD_TIME()) ?
        impl_->previous_timesigned_ : now;
    // For BADTIME error, we include 6 bytes of other data.
    // (6 bytes = size of time signed value)
    const uint16_t otherlen = (error == TSIGError::BAD_TIME()) ? 6 : 0;
    OutputBuffer otherdatabuf(otherlen);
    if (error == TSIGError::BAD_TIME()) {
            otherdatabuf.writeUint16(now >> 32);
            otherdatabuf.writeUint32(now & 0xffffffff);
    }
    const void* const otherdata =
        (otherlen == 0) ? NULL : otherdatabuf.getData();
    // Then calculate the digest.  If state_ is SENT_RESPONSE we are sending
    // a continued message in the same TCP stream so skip digesting
    // variables except for time related variables (RFC2845 4.4).
    impl_->digestTSIGVariables(hmac, TSIGRecord::getClass().getCode(),
                               TSIGRecord::TSIG_TTL, time_signed,
                               DEFAULT_FUDGE, error.getCode(),
                               otherlen, otherdata,
                               impl_->state_ == SENT_RESPONSE);

    // Get the final digest, update internal state, then finish.
    vector<uint8_t> digest = hmac->sign();
    assert(digest.size() <= 0xffff); // cryptolink API should have ensured it.
    ConstTSIGRecordPtr tsig(new TSIGRecord(
                                impl_->key_.getKeyName(),
                                any::TSIG(impl_->key_.getAlgorithmName(),
                                          time_signed, DEFAULT_FUDGE,
                                          digest.size(), &digest[0],
                                          qid, error.getCode(), otherlen,
                                          otherdata)));
    // Exception free from now on.
    impl_->previous_digest_.swap(digest);
    impl_->state_ = (impl_->state_ == INIT) ? SENT_REQUEST : SENT_RESPONSE;
    return (tsig);
}

TSIGError
TSIGContext::verify(const TSIGRecord* const record, const void* const data,
                    const size_t data_len)
{
    if (impl_->state_ == SENT_RESPONSE) {
        isc_throw(TSIGContextError,
                  "TSIG verify attempt after sending a response");
    }

    // This case happens when we sent a signed request and have received an
    // unsigned response.  According to RFC2845 Section 4.6 this case should be
    // considered a "format error" (although the specific error code
    // wouldn't matter much for the caller).
    if (record == NULL) {
        return (impl_->postVerifyUpdate(TSIGError::FORMERR(), NULL, 0));
    }

    const any::TSIG& tsig_rdata = record->getRdata();

    // Reject some obviously invalid data
    if (data_len < MESSAGE_HEADER_LEN + record->getLength()) {
        isc_throw(InvalidParameter,
                  "TSIG verify: data length is invalid: " << data_len);
    }
    if (data == NULL) {
        isc_throw(InvalidParameter, "TSIG verify: empty data is invalid");
    }

    // Check key: whether we first verify it with a known key or we verify
    // it using the consistent key in the context.  If the check fails we are
    // done with BADKEY.
    if (impl_->state_ == INIT && impl_->error_ == TSIGError::BAD_KEY()) {
        return (impl_->postVerifyUpdate(TSIGError::BAD_KEY(), NULL, 0));
    }
    if (impl_->key_.getKeyName() != record->getName() ||
        impl_->key_.getAlgorithmName() != tsig_rdata.getAlgorithm()) {
        return (impl_->postVerifyUpdate(TSIGError::BAD_KEY(), NULL, 0));
    }

    // Check time: the current time must be in the range of
    // [time signed - fudge, time signed + fudge].  Otherwise verification
    // fails with BADTIME. (RFC2845 Section 4.6.2)
    // Note: for simplicity we don't explicitly catch the case of too small
    // current time causing underflow.  With the fact that fudge is quite
    // small and (for now) non configurable, it shouldn't be a real concern
    // in practice.
    const uint64_t now = getTSIGTime();
    if (tsig_rdata.getTimeSigned() + DEFAULT_FUDGE < now ||
        tsig_rdata.getTimeSigned() - DEFAULT_FUDGE > now) {
        const void* digest = NULL;
        size_t digest_len = 0;
        if (impl_->state_ == INIT) {
            digest = tsig_rdata.getMAC();
            digest_len = tsig_rdata.getMACSize();
            impl_->previous_timesigned_ = tsig_rdata.getTimeSigned();
        }
        return (impl_->postVerifyUpdate(TSIGError::BAD_TIME(), digest,
                                        digest_len));
    }

    // TODO: signature length check based on RFC4635
    // (Right now we enforce the standard signature length in libcryptolink)

    // Handling empty MAC.  While RFC2845 doesn't explicitly prohibit other
    // cases, it can only reasonably happen in a response with BADSIG or
    // BADKEY.  We reject other cases as if it were BADSIG to avoid unexpected
    // acceptance of a bogus signature.  This behavior follows the BIND 9
    // implementation.
    if (tsig_rdata.getMACSize() == 0) {
        TSIGError error = TSIGError(tsig_rdata.getError());
        if (error != TSIGError::BAD_SIG() && error != TSIGError::BAD_KEY()) {
            error = TSIGError::BAD_SIG();
        }
        return (impl_->postVerifyUpdate(error, NULL, 0));
    }

    HMACPtr hmac(impl_->getHMAC());

    // If the context has previous MAC (either the Request MAC or its own
    // previous MAC), digest it.
    if (impl_->state_ != INIT) {
        impl_->digestPreviousMAC(hmac);
    }

    //
    // Digest DNS message (excluding the trailing TSIG RR and adjusting the
    // QID and ARCOUNT header fields)
    //
    impl_->digestDNSMessage(hmac, tsig_rdata.getOriginalID(),
                            data, data_len - record->getLength());

    // Digest TSIG variables.  If state_ is VERIFIED_RESPONSE, it's a
    // continuation of the same TCP stream and skip digesting them except
    // for time related variables (RFC2845 4.4).
    // Note: we use the constant values for RR class and TTL specified
    // in RFC2845, not received values (we reject other values in constructing
    // the TSIGRecord).
    impl_->digestTSIGVariables(hmac, TSIGRecord::getClass().getCode(),
                               TSIGRecord::TSIG_TTL,
                               tsig_rdata.getTimeSigned(),
                               tsig_rdata.getFudge(), tsig_rdata.getError(),
                               tsig_rdata.getOtherLen(),
                               tsig_rdata.getOtherData(),
                               impl_->state_ == VERIFIED_RESPONSE);

    // Verify the digest with the received signature.
    if (hmac->verify(tsig_rdata.getMAC(), tsig_rdata.getMACSize())) {
        return (impl_->postVerifyUpdate(TSIGError::NOERROR(),
                                        tsig_rdata.getMAC(),
                                        tsig_rdata.getMACSize()));
    }

    return (impl_->postVerifyUpdate(TSIGError::BAD_SIG(), NULL, 0));
}

} // namespace dns
} // namespace isc
