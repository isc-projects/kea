// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file gss_tsig_context.h Implements a TSIGContext derived class which
/// can be used as the value of TSIGContext pointers so with minimal or
/// update to the DNS++ library. The constructor takes a GSS-TSIG key
/// to share the associated GSS-API security context.

#ifndef GSS_TSIG_CONTEXT_H
#define GSS_TSIG_CONTEXT_H

#include <dns/tsig.h>
#include <gss_tsig_key.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace gss_tsig {

/// @brief GSS-TSIG overwrite of the DNS TSIGContext class.
///
/// src/lib/dns/tsig.h includes a description of TSIGContext API.
///
/// The last TKEY response is signed but this is outside the state
/// transitions which are:
///
/// client side:
///   - INIT
///   - send a signed request
///   - SENT_REQUEST
///   - receive a signed response
///   - VERIFIED_RESPONSE
///
/// server side:
///   - INIT
///   - receive a signed request
///   - RECEIVED_REQUEST
///   - send a signed response
///
/// For TKEY on the reception of the last signed response:
///   - use the payload to finish the GSS-API security context establishment
///   - check the presence of a TSIG
///   - create a GssTsigContext object
///   - set its state to SENT_REQUEST
///   - verify the response using a pointer to the GssTsigContext object
///
/// For each exchange a different TSIGContext is required (no clear operation).
class GssTsigContext : public dns::TSIGContext {
public:
    /// @brief Constructor.
    ///
    /// @param key GSS-TSIG key.
    explicit GssTsigContext(GssTsigKey& key);

    /// @brief Destructor.
    virtual ~GssTsigContext();

    /// @brief Sign a DNS message.
    ///
    /// See @c isc::dns::TSIGContext::sign().
    ///
    /// @param qid The QID to be as the value of the original ID field of
    /// the resulting TSIG record.
    /// @param data The wire-format data to be signed.
    /// @param data_len The length of @c data in bytes.
    /// @return A TSIG record for the given data along with the context.
    virtual dns::ConstTSIGRecordPtr
    sign(const uint16_t qid, const void* const data,
         const size_t data_len) override;

    /// @brief a DNS message.
    ///
    /// See @c isc::dns::TSIGContext::verify().
    ///
    virtual dns::TSIGError
    verify(const dns::TSIGRecord* const record, const void* const data,
           const size_t data_len) override;

    /// @brief Check whether the last verified message was signed.
    ///
    /// See @c isc::dns::TSIGContext::lastHadSignature().
    ///
    /// @return If the last message was signed or not.
    /// @exception TSIGContextError if no message was verified yet.
    virtual bool lastHadSignature() const override;

    /// @brief Return the expected length of TSIG RR after @c sign().
    ///
    /// See @c isc::dns::TSIGContext::getTSIGLength().
    ///
    /// @note: use the fixed constant of 128 from bind9.
    ///
    /// @return The expected TSIG RR length in bytes.
    virtual size_t getTSIGLength() const override;

    /// @brief Return the current state of the context.
    ///
    /// See @c isc::dns::TSIGContext::getState().
    ///
    /// @exception None.
    virtual State getState() const override {
        return (state_);
    }

    /// @brief Set the current state of the context.
    ///
    /// @note: to be used for the last TKEY response.
    ///
    /// @param state New state.
    virtual void setState(State state) {
        state_ = state;
    }

    /// @brief Return the TSIG error as a result of the latest verification.
    ///
    /// See @c isc::dns::TSIGContext::getError().
    ///
    /// @exception None.
    virtual dns::TSIGError getError() const override {
        return (error_);
    }

    /// @brief Set the TSIG error.
    ///
    /// @note: to be used for the last TKEY response.
    ///
    /// @param error New error.
    virtual void setError(dns::TSIGError error) {
        error_ = error;
    }

private:
    /// @brief State.
    State state_;

    /// @brief GSS-TSIG key.
    GssTsigKey& key_;

    /// @brief Previous digest.
    std::vector<uint8_t> previous_digest_;

    /// @brief TSIG error.
    dns::TSIGError error_;

    /// @brief Previous time signed.
    ///
    /// @note: only meaningful for response with BADTIME.
    uint64_t previous_timesigned_;

    /// @brief Distance from the last verified signed message.
    ///
    /// @note: Value of 0 means the last message was signed.
    /// Special value -1 means there was no signed message yet.
    int last_sig_dist_;

    /// @brief To be signed (or verified) buffer.
    util::OutputBuffer tbs_;

protected:
    /// @brief Update internal MAC state by more data.
    /// This is used mostly internally, when we need to verify a message without
    /// TSIG signature in the middle of signed TCP stream. However, it is also
    /// used in tests, so it's protected instead of private, to allow tests
    /// in.
    ///
    /// It doesn't contain sanity checks, and it is not tested directly. But
    /// we may want to add these one day to allow generating the skipped TSIG
    /// messages too. Until then, do not use this method.
    ///
    /// @param data Points to the wire-format data.
    /// @param len The length of @c data in bytes.
    void update(const void* const data, size_t len);
};

/// @brief Type of pointer to a GSS-TSIG context.
typedef boost::shared_ptr<GssTsigContext> GssTsigContextPtr;

} // end of namespace isc::gss_tsig
} // end of namespace isc

#endif // GSS_TSIG_CONTEXT_H
