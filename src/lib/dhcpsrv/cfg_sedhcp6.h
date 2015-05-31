// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef CFG_SEDHCP6_H
#define CFG_SEDHCP6_H

#include <cryptolink/cryptolink.h>

#include <boost/shared_ptr.hpp>
#include <stdint.h>
#include <set>

namespace isc {
namespace dhcp {

/// @brief Represents configuration of secure DHCPv6 for the DHCP server.
///
/// This class holds the secure DHCPv6 state for the DHCPv6 server.
class CfgSeDhcp6 {
public:

    /// @brief Pointer to constant asym crypto objet
    typedef boost::shared_ptr<isc::cryptolink::Asym> AsymPtr;

    /// @brief Constructor.
    CfgSeDhcp6(bool sign_answers = false,
               bool timestamp_answers = false,
               bool check_signatures = false,
               bool check_authorizations = false,
               bool check_timestamps = false,
               bool online_validation = false,
               AsymPtr private_key = AsymPtr(),
               AsymPtr credential = AsymPtr());

    /// @brief Returns the sign-answers flag
    bool getSignAnswers() const;

    /// @brief Returns the timestamp-answers flag
    bool getTimestampAnswers() const;

    /// @brief Returns the check-signatures flag
    bool getCheckSignatures() const;

    /// @brief Returns the check-authorizations flag
    bool getCheckAuthorizations() const;

    /// @brief Returns the check-timestamps flag
    bool getCheckTimestamps() const;

    /// @brief Returns the online-validation flag
    bool getOnlineValidation() const;

    /// @brief Returns a pointer to the private key object
    AsymPtr getPrivateKey() const;

    /// @brief Returns a pointer to the credential (public key or
    /// certificate) object
    AsymPtr getCredential() const;

private:
    /// @brief sign-answers flag
    bool sign_answers_;

    /// @brief timestamp-answers flag
    bool timestamp_answers_;

    /// @brief check-signatures flag
    bool check_signatures_;

    /// @brief check-authorizations flag
    bool check_authorizations_;

    /// @brief check-timestamps flag
    bool check_timestamps_;

    /// @brief online-validation flag
    bool online_validation_;

    /// @brief private key object
    AsymPtr private_key_;

    /// @brief credential (public key or certificate) objet
    AsymPtr credential_;
};

/// @name Pointers to the @c CfgSeDhcp6 objects.
//@{
/// @brief Pointer to the Non-const object.
typedef boost::shared_ptr<CfgSeDhcp6> CfgSeDhcp6Ptr;

/// @brief Pointer to the const object.
typedef boost::shared_ptr<const CfgSeDhcp6> ConstCfgSeDhcp6Ptr;

//@}

}
}

#endif // CFG_SEDHCP6_H
