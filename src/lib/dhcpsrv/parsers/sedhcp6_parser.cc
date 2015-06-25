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

#include <config.h>

#include <cryptolink/crypto_asym.h>
#include <dhcp/option.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/parsers/sedhcp6_parser.h>

#include <boost/foreach.hpp>

#include <map>
#include <string>
#include <sstream>
#include <utility>

using namespace std;
using namespace isc::data;
using namespace isc::cryptolink;
typedef isc::dhcp::CfgSeDhcp6::AsymPtr AsymPtr;

namespace isc {
namespace dhcp {

// Factory function to build the parser
SeDhcp6Parser::SeDhcp6Parser(const std::string& param_name,
                             Option::Universe universe)
    : values_(), universe_(universe)
{
    if (param_name != "secure-dhcp6") {
        isc_throw(BadValue,
                  "Internal error. Secure DHCPv6 configuration parser "
                  "called for the wrong parameter: " << param_name);
    }
}

// Parse the configuration and check that the various keywords are consistent.
void
SeDhcp6Parser::build(isc::data::ConstElementPtr config_value) {

    // DHCPv6 only
    if (universe_ != Option::V6) {
        isc_throw(DhcpConfigError,
                  "secure-dhcp6 makes sense only for DHCPv6");
    }

    // To cope with incremental updates, the strategy is:
    // 1. Take a copy of the stored keyword/value pairs.
    // 2. Update the copy with the passed keywords.
    // 3. Perform validation checks on the updated keyword/value pairs.
    // 4. If all is OK, update the stored keyword/value pairs.

    // 1. Take a copy of the stored keyword/value pairs.
    std::map<string, string> values_copy = values_;

    // 2. Update the copy with the passed keywords.
    BOOST_FOREACH(ConfigPair param, config_value->mapValue()) {
        bool found = false;
        try {
            // Booleans
            if ((param.first == "sign-answers") ||
                (param.first == "timestamp-answers") ||
                (param.first == "check-authorizations") ||
                (param.first == "check-signatures") ||
                (param.first == "check-timestamps")) {
                found = true;
                values_copy[param.first] = (param.second->boolValue() ?
                                            "true" : "false");
            } else if ((param.first == "signature-algorithm") ||
                       (param.first == "hash-algorithm") ||
                       (param.first == "public-key") ||
                       (param.first == "certificate") ||
                       (param.first == "private-key") ||
                       (param.first == "validation-policy")) {
                found = true;
                values_copy[param.first] = param.second->stringValue();
            }
        } catch (const isc::data::TypeError& ex) {
            // Append position of the element.
            isc_throw(isc::data::TypeError, ex.what() << " ("
                      << param.second->getPosition() << ")");
        }
        if (!found) {
            isc_throw(DhcpConfigError,
                      "secure-dhcp6 parameter not supported: "
                      << param.first << " ("
                      << param.second->getPosition() << ")");
        }
    }

    // 3. Perform validation checks on the updated set of keyword/values.
    //
    // a. Check if we sign
    bool sign_answers = false;
    StringPairMap::const_iterator sign_answers_ptr =
        values_copy.find("sign-answers");
    if ((sign_answers_ptr != values_copy.end()) &&
        (sign_answers_ptr->second == "true")) {
        sign_answers = true;
    }

    // b. Check if we can sign
    string public_key = "";
    StringPairMap::const_iterator public_key_ptr =
        values_copy.find("public-key");
    if (public_key_ptr != values_copy.end()) {
        public_key = public_key_ptr->second;
    }
    string certificate = "";
    StringPairMap::const_iterator certificate_ptr =
        values_copy.find("certificate");
    if (certificate_ptr != values_copy.end()) {
        certificate = certificate_ptr->second;
    }
    if (sign_answers && public_key.empty() && certificate.empty()) {
        isc_throw(DhcpConfigError,
                  "secure-dhcp6 requires a public-key or a certificate "
                  "when sign-answers is enabled");
    }
    if (!public_key.empty() && !certificate.empty()) {
        isc_throw(DhcpConfigError,
                  "public-key and certificate cannot be both defined");
    }
    string private_key = "";
    StringPairMap::const_iterator private_key_ptr =
        values_copy.find("private-key");
    if (private_key_ptr != values_copy.end()) {
        private_key = private_key_ptr->second;
    }
    if (sign_answers && private_key.empty()) {
        isc_throw(DhcpConfigError,
                  "secure-dhcp6 requires a private-key when "
                  "sign-answers is enabled");
    }

    // c. Check if the signature algorithm is known
    StringPairMap::const_iterator signature_algorithm_ptr =
        values_copy.find("signature-algorithm");
    if ((signature_algorithm_ptr != values_copy.end()) &&
        (signature_algorithm_ptr->second != "RSA")) {
        isc_throw(DhcpConfigError, "unknown signature-algorithm: "
                  << signature_algorithm_ptr->second);
    }

    // d. Check if the hash algorithm is known
    StringPairMap::const_iterator hash_algorithm_ptr =
        values_copy.find("hash-algorithm");
    if ((hash_algorithm_ptr != values_copy.end()) &&
        (hash_algorithm_ptr->second != "SHA-256") &&
        (hash_algorithm_ptr->second != "SHA-512")) {
        isc_throw(DhcpConfigError, "unknown hash-algorithm: "
                  << hash_algorithm_ptr->second);
    }

    // e. Check if the validation policy is known
    StringPairMap::const_iterator validation_policy_ptr =
        values_copy.find("validation-policy");
    if ((validation_policy_ptr != values_copy.end()) &&
        (validation_policy_ptr->second != "offline") &&
        (validation_policy_ptr->second != "online")) {
        isc_throw(DhcpConfigError, "unknown validation-policy: "
                  << validation_policy_ptr->second);
    }

    // 4. If all is OK, update the stored keyword/value pairs.  We do this by
    // swapping contents - values_copy is destroyed immediately after the
    // operation (when the method exits), so we are not interested in its new
    // value.
    values_.swap(values_copy);
}

// Create a new secure DHCPv6 state with new parameters
CfgSeDhcp6 SeDhcp6Parser::create() const {
    // Get booleans
    bool sign_answers = false;
    StringPairMap::const_iterator sign_answers_ptr =
        values_.find("sign-answers");
    if ((sign_answers_ptr != values_.end()) &&
        (sign_answers_ptr->second == "true")) {
        sign_answers = true;
    }
    bool timestamp_answers = false;
    StringPairMap::const_iterator timestamp_answers_ptr =
        values_.find("timestamp-answers");
    if ((timestamp_answers_ptr != values_.end()) &&
        (timestamp_answers_ptr->second == "true")) {
        timestamp_answers = true;
    }
    bool check_signatures = false;
    StringPairMap::const_iterator check_signatures_ptr =
        values_.find("check-signatures");
    if ((check_signatures_ptr != values_.end()) &&
        (check_signatures_ptr->second == "true")) {
        check_signatures = true;
    }
    bool check_authorizations = false;
    StringPairMap::const_iterator check_authorizations_ptr =
        values_.find("check-authorizations");
    if ((check_authorizations_ptr != values_.end()) &&
        (check_authorizations_ptr->second == "true")) {
        check_authorizations = true;
    }
    bool check_timestamps = false;
    StringPairMap::const_iterator check_timestamps_ptr =
        values_.find("check-timestamps");
    if ((check_timestamps_ptr != values_.end()) &&
        (check_timestamps_ptr->second == "true")) {
        check_timestamps = true;
    }
    bool online_validation = false;
    StringPairMap::const_iterator validation_policy_ptr =
        values_.find("validation-policy");
    if ((validation_policy_ptr != values_.end()) &&
        (validation_policy_ptr->second == "online")) {
        online_validation = true;
    }

    // When signing is disabled this is almost done
    if (!sign_answers) {
        try {
            return (CfgSeDhcp6(sign_answers,
                               timestamp_answers,
                               check_signatures,
                               check_authorizations,
                               check_timestamps,
                               online_validation));
        } catch (const std::exception& ex) {
            isc_throw(DhcpConfigError, "Failed to build the secure "
                      "DHCPv6 configuration state: " << ex.what());
        } catch (...) {
            isc_throw(DhcpConfigError, "Failed to build the secure "
                      "DHCPv6 configuration state");
        }
        // unreachable
    }

    // Signing is enabled, we need more

    // Get asym parameters
    AsymAlgorithm signature_algorithm = RSA_;
    HashAlgorithm hash_algorithm = SHA256;
    StringPairMap::const_iterator hash_algorithm_ptr =  
        values_.find("hash-algorithm");
    if ((hash_algorithm_ptr != values_.end()) &&
        (hash_algorithm_ptr->second == "SHA-512")) {
        hash_algorithm = SHA512;
    }

    // Get private key
    string private_key = "";
    StringPairMap::const_iterator private_key_ptr =
        values_.find("private-key");
    if (private_key_ptr != values_.end()) {
        private_key = private_key_ptr->second;
    }
    
    // Get credential
    string public_key = "";
    StringPairMap::const_iterator public_key_ptr =
        values_.find("public-key");
    if (public_key_ptr != values_.end()) {
        public_key = public_key_ptr->second;
    }
    string certificate = "";
    StringPairMap::const_iterator certificate_ptr =
        values_.find("certificate");
    if (certificate_ptr != values_.end()) {
        certificate = certificate_ptr->second;
    }
    string credential = public_key;
    AsymKeyKind credental_kind = PUBLIC;
    if (public_key.empty()) {
        credential = certificate;
        credental_kind = CERT;
    }

    // Build asym crypto objects and result
    CryptoLink& crypto = CryptoLink::getCryptoLink();
    std::ostringstream errmsg;
    try {
        errmsg << "Failed to get the private key from '";
        errmsg << private_key.c_str() << "'";
        AsymPtr priv_key(crypto.createAsym(private_key,
                                           "",
                                           signature_algorithm,
                                           hash_algorithm,
                                           PRIVATE,
                                           ASN1),
                         deleteAsym);

        errmsg.str("");
        errmsg << "Failed to get the ";
        errmsg << (public_key.empty() ? "certificate" : "public key")
               << " from '" << credential.c_str() << "'";
        AsymPtr cred(crypto.createAsym(credential,
                                       "",
                                       signature_algorithm,
                                       hash_algorithm,
                                       credental_kind,
                                       ASN1),
                     deleteAsym);

        errmsg.str("");
        errmsg << "Mismatch between the private key and the";
        errmsg << (public_key.empty() ? "certificate" : "public key");
        if (!priv_key->compare(cred.get(), PUBLIC)) {
            isc_throw(DhcpConfigError, errmsg.str());
        }

        errmsg.str("");
        errmsg << "Failed to build the secure DHCPv6 configuration state";
        return (CfgSeDhcp6(sign_answers,
                           timestamp_answers,
                           check_signatures,
                           check_authorizations,
                           check_timestamps,
                           online_validation,
                           priv_key,
                           cred));
    } catch (const DhcpConfigError&) {
        throw;
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, errmsg << ": " << ex.what());
    } catch (...) {
        isc_throw(DhcpConfigError, errmsg.str());
    }
    // unreachable
}

// Commit the changes from the new secure DHCPv6 state
void SeDhcp6Parser::commit() {
    CfgSeDhcp6Ptr cfg = CfgMgr::instance().getStagingCfg()->getCfgSeDhcp6();
    *cfg = create();
}

// For tests
void SeDhcp6Parser::clear() {
    values_.clear();
}

};  // namespace dhcp
};  // namespace isc
