// Copyright (C) 2014, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <cryptolink.h>
#include <cryptolink/crypto_asym.h>

#include <openssl/evp.h>

#include <hooks/hooks_manager.h>
#include <hooks/callout_handle.h>
#include <cryptolink/openssl_common.h>
#include <cryptolink/openssl_rsa.h>

namespace {

///< index of "validate_certificate" hook point
int hook_point_validate_certificate =
    isc::hooks::HooksManager::registerHook("validate_certificate");

} // anonymous namespace

namespace isc {
namespace cryptolink {

Asym::Asym(const void* key, size_t key_len,
           const AsymAlgorithm asym_algorithm,
           const HashAlgorithm hash_algorithm,
           const AsymKeyKind key_kind,
           const AsymFormat key_format)
{
    switch (asym_algorithm) {
    case RSA_:
        impl_ = new RsaAsymImpl(key, key_len, hash_algorithm,
                                key_kind, key_format);
        return;
    default:
        isc_throw(UnsupportedAlgorithm,
                  "Unknown asym algorithm: " <<
                  static_cast<int>(asym_algorithm));
    }
}

Asym::Asym(const std::vector<uint8_t> key,
           const AsymAlgorithm asym_algorithm,
           const HashAlgorithm hash_algorithm,
           const AsymKeyKind key_kind,
           const AsymFormat key_format)
{
    switch (asym_algorithm) {
    case RSA_:
        impl_ = new RsaAsymImpl(&key[0], key.size(), hash_algorithm,
                                key_kind, key_format);
        return;
    default:
        isc_throw(UnsupportedAlgorithm,
                  "Unknown asym algorithm: " <<
                  static_cast<int>(asym_algorithm));
    }
}

Asym::Asym(const std::string& filename,
           const std::string& password,
           const AsymAlgorithm asym_algorithm,
           const HashAlgorithm hash_algorithm,
           const AsymKeyKind key_kind,
           const AsymFormat key_format)
{
    switch (asym_algorithm) {
    case RSA_:
        impl_ = new RsaAsymImpl(filename, password, hash_algorithm,
                                key_kind, key_format);
        return;
    default:
        isc_throw(UnsupportedAlgorithm,
                  "Unknown asym algorithm: " <<
                  static_cast<int>(asym_algorithm));
    }
}

Asym::~Asym() {
    delete impl_;
}

AsymAlgorithm
Asym::getAsymAlgorithm() const {
    return (impl_->getAsymAlgorithm());
}

HashAlgorithm
Asym::getHashAlgorithm() const {
    return (impl_->getHashAlgorithm());
}

AsymKeyKind
Asym::getAsymKeyKind() const {
    return (impl_->getAsymKeyKind());
}

size_t
Asym::getKeySize() const {
    return (impl_->getKeySize());
}

size_t
Asym::getSignatureLength(const AsymFormat sig_format) const {
    return (impl_->getSignatureLength(sig_format));
}

void
Asym::update(const void* data, const size_t len) {
    impl_->update(data, len);
}

void
Asym::sign(isc::util::OutputBuffer& result, size_t len,
           const AsymFormat sig_format) {
    impl_->sign(result, len, sig_format);
}

void
Asym::sign(void* result, size_t len, const AsymFormat sig_format) {
    impl_->sign(result, len, sig_format);
}

std::vector<uint8_t>
Asym::sign(size_t len, const AsymFormat sig_format) {
    return (impl_->sign(len, sig_format));
}

bool
Asym::verify(const void* sig, size_t len, const AsymFormat sig_format) {
    return (impl_->verify(sig, len, sig_format));
}

void
Asym::clear() {
    impl_->clear();
}

std::vector<uint8_t>
Asym::exportkey(const AsymKeyKind key_kind,
                const AsymFormat key_format) const {
    return (impl_->exportkey(key_kind, key_format));
}

void
Asym::exportkey(const std::string& filename,
                const std::string& password,
                const AsymKeyKind key_kind,
                const AsymFormat key_format) const {
    impl_->exportkey(filename, password, key_kind, key_format);
}

bool
Asym::validate() const {
    // Hook only certificate validation
    if (getAsymKeyKind() != CERT) {
        return (impl_->validate());
    }

    // Call the hook if available
    using namespace isc::hooks;
    if (HooksManager::calloutsPresent(hook_point_validate_certificate)) {
        // Callout handle
        CalloutHandlePtr callout_handle_ = HooksManager::createCalloutHandle();

        // Delete add previous arguments
        callout_handle_->deleteAllArguments();

        // Pass the certificate (der in a vector)
        callout_handle_->setArgument("certificate", exportkey(CERT, ASN1));

        // Call the callouts
        HooksManager::callCallouts(hook_point_validate_certificate,
                                   *callout_handle_);

        // Callouts decided to skip the action. This means that
        // validation failed, so return false.
        return (!callout_handle_->getSkip());
    }

    // No hooks
    return (impl_->validate());
}

bool
Asym::compare(const Asym* other, const AsymKeyKind key_kind) const {
    if (getAsymAlgorithm() != other->getAsymAlgorithm()) {
        return false;
    }
    if (getAsymAlgorithm() == RSA_) {
        const RsaAsymImpl* impl = dynamic_cast<const RsaAsymImpl*>(impl_);
        // Should not happen but to test is better than to crash
        if (!impl) {
            isc_throw(Unexpected, "dynamic_cast failed on RsaAsymImpl*");
        }
        const RsaAsymImpl* oimpl =
            dynamic_cast<const RsaAsymImpl*>(other->impl_);
        return (impl->compare(oimpl, key_kind));
    }
    isc_throw(UnsupportedAlgorithm, "compare");
}

} // namespace cryptolink
} // namespace isc
