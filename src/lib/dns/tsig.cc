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

#include <cassert>              // for the tentative verifyTentative()
#include <vector>

#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

#include <util/buffer.h>

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

// Borrowed from dnssectime.cc.  This trick should be unified somewhere.
namespace tsig {
namespace detail {
int64_t (*gettimeFunction)() = NULL;
}
}

namespace {
int64_t
gettimeofdayWrapper() {
    using namespace tsig::detail;
    if (gettimeFunction != NULL) {
        return (gettimeFunction());
    }

    struct timeval now;
    gettimeofday(&now, NULL);

    return (static_cast<int64_t>(now.tv_sec));
}
}

namespace {
typedef boost::shared_ptr<HMAC> HMACPtr;
}

const RRClass&
TSIGRecord::getClass() {
    return (RRClass::ANY());
}

struct TSIGContext::TSIGContextImpl {
    TSIGContextImpl(const TSIGKey& key) :
        state_(INIT), key_(key), error_(Rcode::NOERROR()),
        previous_timesigned_(0)
    {}
    State state_;
    TSIGKey key_;
    vector<uint8_t> previous_digest_;
    TSIGError error_;
    uint64_t previous_timesigned_; // only meaningful for response with BADTIME
};

TSIGContext::TSIGContext(const TSIGKey& key) : impl_(new TSIGContextImpl(key))
{
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
    if (data == NULL || data_len == 0) {
        isc_throw(InvalidParameter, "TSIG sign error: empty data is given");
    }

    TSIGError error(TSIGError::NOERROR());
    const uint64_t now = (gettimeofdayWrapper() & 0x0000ffffffffffffULL);

    // For responses adjust the error code.
    if (impl_->state_ == CHECKED) {
        error = impl_->error_;
    }

    // For errors related to key or MAC, return an unsigned response as
    // specified in Section 4.3 of RFC2845.
    if (error == TSIGError::BAD_SIG() || error == TSIGError::BAD_KEY()) {
        ConstTSIGRecordPtr tsig(new TSIGRecord(
                                    any::TSIG(impl_->key_.getAlgorithmName(),
                                              now, DEFAULT_FUDGE, NULL, 0,
                                              qid, error.getCode(), 0, NULL)));
        impl_->previous_digest_.clear();
        impl_->state_ = SIGNED;
        return (tsig);
    }

    OutputBuffer variables(0);
    HMACPtr hmac(CryptoLink::getCryptoLink().createHMAC(
                     impl_->key_.getSecret(),
                     impl_->key_.getSecretLength(),
                     impl_->key_.getCryptoAlgorithm()),
                 deleteHMAC);

    // If the context has previous MAC (either the Request MAC or its own
    // previous MAC), digest it.
    if (impl_->state_ != INIT) {
        const uint16_t previous_digest_len(impl_->previous_digest_.size());
        variables.writeUint16(previous_digest_len);
        if (previous_digest_len != 0) {
            variables.writeData(&impl_->previous_digest_[0],
                                previous_digest_len);
        }
        hmac->update(variables.getData(), variables.getLength());
    }

    // Digest the message (without TSIG)
    hmac->update(data, data_len);

    //
    // Digest TSIG variables.  If state_ is SIGNED we skip digesting them
    // except for time related variables (RFC2845 4.4).
    //
    variables.clear();
    if (impl_->state_ != SIGNED) {
        impl_->key_.getKeyName().toWire(variables);
        TSIGRecord::getClass().toWire(variables);
        variables.writeUint32(TSIGRecord::TSIG_TTL);
        impl_->key_.getAlgorithmName().toWire(variables);
    }
    const uint64_t time_signed = (error == TSIGError::BAD_TIME()) ?
        impl_->previous_timesigned_ : now;
    variables.writeUint16(time_signed >> 32);
    variables.writeUint32(time_signed & 0xffffffff);
    variables.writeUint16(DEFAULT_FUDGE);
    hmac->update(variables.getData(), variables.getLength());
    variables.clear();

    if (impl_->state_ != SIGNED) {
        variables.writeUint16(error.getCode());

        // For BADTIME error, digest 6 bytes of other data.
        // (6 bytes = size of time signed value)
        variables.writeUint16((error == TSIGError::BAD_TIME()) ? 6 : 0);
        hmac->update(variables.getData(), variables.getLength());

        variables.clear();
        if (error == TSIGError::BAD_TIME()) {
            variables.writeUint16(now >> 32);
            variables.writeUint32(now & 0xffffffff);
            hmac->update(variables.getData(), variables.getLength());
        }
    }
    const uint16_t otherlen = variables.getLength();

    // Get the final digest, update internal state, then finish.
    vector<uint8_t> digest = hmac->sign();
    ConstTSIGRecordPtr tsig(new TSIGRecord(
                                any::TSIG(impl_->key_.getAlgorithmName(),
                                          time_signed, DEFAULT_FUDGE,
                                          digest.size(), &digest[0],
                                          qid, error.getCode(), otherlen,
                                          otherlen == 0 ?
                                          NULL : variables.getData())));
    // Exception free from now on.
    impl_->previous_digest_.swap(digest);
    impl_->state_ = SIGNED;
    return (tsig);
}

void
TSIGContext::verifyTentative(ConstTSIGRecordPtr tsig, TSIGError error) {
    const any::TSIG tsig_rdata = tsig->getRdata();

    impl_->error_ = error;
    if (error == TSIGError::BAD_TIME()) {
        impl_->previous_timesigned_ = tsig_rdata.getTimeSigned();
    }

    // For simplicity we assume non empty digests.
    assert(tsig_rdata.getMACSize() != 0);
    impl_->previous_digest_.assign(
        static_cast<const uint8_t*>(tsig_rdata.getMAC()),
        static_cast<const uint8_t*>(tsig_rdata.getMAC()) +
        tsig_rdata.getMACSize());

    impl_->state_ = CHECKED;
}
} // namespace dns
} // namespace isc
