// Copyright (C) 2014-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cryptolink.h>
#include <cryptolink/crypto_hmac.h>

#include <boost/scoped_ptr.hpp>

#include <openssl/evp.h>

#include <cryptolink/openssl_common.h>
#define KEA_HASH
#define KEA_HMAC
#include <cryptolink/openssl_compat.h>

#include <cstring>

namespace isc {
namespace cryptolink {

/// @brief OpenSSL implementation of HMAC. Each method is the counterpart
/// of the HMAC corresponding method.
class HMACImpl {
public:
    /// @brief Constructor from a secret and a hash algorithm
    ///
    /// See constructor of the @ref isc::cryptolink::HMAC class for details.
    ///
    /// @param secret The secret to sign with
    /// @param secret_len The length of the secret
    /// @param hash_algorithm The hash algorithm
    explicit HMACImpl(const void* secret, size_t secret_len,
                      const HashAlgorithm hash_algorithm)
        : hash_algorithm_(hash_algorithm), md_(), digest_() {
        const EVP_MD* algo = ossl::getHashAlgorithm(hash_algorithm);
        if (algo == 0) {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown hash algorithm: " <<
                      static_cast<int>(hash_algorithm));
        }
        if (secret_len == 0) {
            isc_throw(BadKey, "Bad HMAC secret length: 0");
        }

        md_ = EVP_MD_CTX_new();
        if (md_ == 0) {
            isc_throw(LibraryError, "OpenSSL EVP_MD_CTX_new() failed");
        }

        EVP_PKEY* pkey =
            EVP_PKEY_new_raw_private_key(EVP_PKEY_HMAC, NULL,
                                         reinterpret_cast<const unsigned char*>(secret),
                                         secret_len);

        if (pkey == 0) {
            isc_throw(LibraryError,
                      "OpenSSL EVP_PKEY_new_raw_private_key() failed");
        }

        if (!EVP_DigestSignInit(md_, NULL, algo, NULL, pkey)) {
            EVP_PKEY_free(pkey);
            isc_throw(LibraryError, "OpenSSL EVP_DigestSignInit() failed");
        }

        EVP_PKEY_free(pkey);
    }

    /// @brief Destructor
    ~HMACImpl() {
        if (md_) {
            EVP_MD_CTX_free(md_);
        }
        md_ = 0;
    }

    /// @brief Returns the HashAlgorithm of the object
    HashAlgorithm getHashAlgorithm() const {
        return (hash_algorithm_);
    }

    /// @brief Returns the output size of the digest
    ///
    /// @return output size of the digest
    size_t getOutputLength() const {
        return (EVP_MD_CTX_size(md_));
    }

    /// @brief Add data to digest
    ///
    /// See @ref isc::cryptolink::HMAC::update() for details.
    void update(const void* data, const size_t len) {
        if (len == 0) {
            return;
        }

        if (!EVP_DigestSignUpdate(md_, data, len)) {
            isc_throw(LibraryError, "OpenSSL EVP_DigestSignUpdate() failed");
        }
    }

    /// @brief Calculate the final signature
    ///
    /// See @ref isc::cryptolink::HMAC::sign() for details.
    void sign(isc::util::OutputBuffer& result, size_t len) {
        size_t size = getOutputLength();
        ossl::SecBuf<unsigned char> digest(size);
        size_t digest_len = size;
        if (!EVP_DigestSignFinal(md_, &digest[0], &digest_len)) {
            isc_throw(LibraryError, "OpenSSL EVP_DigestSignFinal() failed");
        }
        if (digest_len != size) {
            isc_throw(LibraryError, "OpenSSL partial EVP_DigestSignFinal()");
        }
        if (len > size) {
            len = size;
        }
        result.writeData(&digest[0], len);
    }

    /// @brief Calculate the final signature
    ///
    /// See @ref isc::cryptolink::HMAC::sign() for details.
    void sign(void* result, size_t len) {
        size_t size = getOutputLength();
        ossl::SecBuf<unsigned char> digest(size);
        size_t digest_len = size;
        if (!EVP_DigestSignFinal(md_, &digest[0], &digest_len)) {
            isc_throw(LibraryError, "OpenSSL EVP_DigestSignFinal() failed");
        }
        if (digest_len != size) {
            isc_throw(LibraryError, "OpenSSL partial EVP_DigestSignFinal()");
        }
        if (len > size) {
            len = size;
        }
        std::memcpy(result, &digest[0], len);
    }

    /// @brief Calculate the final signature
    ///
    /// See @ref isc::cryptolink::HMAC::sign() for details.
    std::vector<uint8_t> sign(size_t len) {
        size_t size = getOutputLength();
        ossl::SecBuf<unsigned char> digest(size);
        size_t digest_len = size;
        if (!EVP_DigestSignFinal(md_, &digest[0], &digest_len)) {
            isc_throw(LibraryError, "OpenSSL EVP_DigestSignFinal() failed");
        }
        if (digest_len != size) {
            isc_throw(LibraryError, "OpenSSL partial EVP_DigestSignFinal()");
        }
        if (len < size) {
            digest.resize(len);
        }
        return (std::vector<uint8_t>(digest.begin(), digest.end()));
    }

    /// @brief Verify an existing signature
    ///
    /// See @ref isc::cryptolink::HMAC::verify() for details.
    bool verify(const void* sig, size_t len) {
        // Check the length
        size_t size = getOutputLength();
        if (len < 10 || len < size / 2) {
            return (false);
        }
        if (digest_.size() == 0) {
            digest_.resize(size);
            size_t digest_len = size;
            if (!EVP_DigestSignFinal(md_, &digest_[0], &digest_len)) {
                isc_throw(LibraryError, "OpenSSL EVP_DigestSignFinal() failed");
            }
            if (digest_len != size) {
                isc_throw(LibraryError, "OpenSSL partial EVP_DigestSignFinal()");
            }
        }
        if (len > size) {
            len = size;
        }
        return (digest_.same(sig, len));
    }

private:
    /// @brief The hash algorithm
    HashAlgorithm hash_algorithm_;

    /// @brief The protected pointer to the OpenSSL EVP_MD_CTX structure
    EVP_MD_CTX* md_;

    /// @brief The digest cache for multiple verify
    ossl::SecBuf<unsigned char> digest_;
};

HMAC::HMAC(const void* secret, size_t secret_length,
           const HashAlgorithm hash_algorithm)
{
    impl_ = new HMACImpl(secret, secret_length, hash_algorithm);
}

HMAC::~HMAC() {
    delete impl_;
}

HashAlgorithm
HMAC::getHashAlgorithm() const {
    return (impl_->getHashAlgorithm());
}

size_t
HMAC::getOutputLength() const {
    return (impl_->getOutputLength());
}

void
HMAC::update(const void* data, const size_t len) {
    impl_->update(data, len);
}

void
HMAC::sign(isc::util::OutputBuffer& result, size_t len) {
    impl_->sign(result, len);
}

void
HMAC::sign(void* result, size_t len) {
    impl_->sign(result, len);
}

std::vector<uint8_t>
HMAC::sign(size_t len) {
    return impl_->sign(len);
}

bool
HMAC::verify(const void* sig, const size_t len) {
    return (impl_->verify(sig, len));
}

} // namespace cryptolink
} // namespace isc
