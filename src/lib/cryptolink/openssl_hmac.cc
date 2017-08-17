// Copyright (C) 2014-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cryptolink.h>
#include <cryptolink/crypto_hmac.h>

#include <boost/scoped_ptr.hpp>

#include <openssl/hmac.h>

#include <cryptolink/openssl_common.h>
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
    : hash_algorithm_(hash_algorithm), md_() {
        const EVP_MD* algo = ossl::getHashAlgorithm(hash_algorithm);
        if (algo == 0) {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown hash algorithm: " <<
                      static_cast<int>(hash_algorithm));
        }
        if (secret_len == 0) {
            isc_throw(BadKey, "Bad HMAC secret length: 0");
        }

        md_ = HMAC_CTX_new();
        if (md_ == 0) {
            isc_throw(LibraryError, "OpenSSL HMAC_CTX_new() failed");
        }

        if (!HMAC_Init_ex(md_, secret,
                          static_cast<int>(secret_len),
                          algo, NULL)) {
            isc_throw(LibraryError, "OpenSSL HMAC_Init_ex() failed");
        }
    }

    /// @brief Destructor
    ~HMACImpl() {
        if (md_) {
            HMAC_CTX_free(md_);
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
        int size = HMAC_size(md_);
        if (size < 0) {
            isc_throw(LibraryError, "OpenSSL HMAC_size() failed");
        }
        return (static_cast<size_t>(size));
    }

    /// @brief Add data to digest
    ///
    /// See @ref isc::cryptolink::HMAC::update() for details.
    void update(const void* data, const size_t len) {
        if (!HMAC_Update(md_,
                         static_cast<const unsigned char*>(data),
                         len)) {
            isc_throw(LibraryError, "OpenSSLHMAC_Update() failed");
        }
    }

    /// @brief Calculate the final signature
    ///
    /// See @ref isc::cryptolink::HMAC::sign() for details.
    void sign(isc::util::OutputBuffer& result, size_t len) {
        size_t size = getOutputLength();
        ossl::SecBuf<unsigned char> digest(size);
        if (!HMAC_Final(md_, &digest[0], NULL)) {
            isc_throw(LibraryError, "OpenSSL HMAC_Final() failed");
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
        if (!HMAC_Final(md_, &digest[0], NULL)) {
            isc_throw(LibraryError, "OpenSSL HMAC_Final() failed");
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
        if (!HMAC_Final(md_, &digest[0], NULL)) {
            isc_throw(LibraryError, "OpenSSL HMAC_Final() failed");
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
        // Get the digest from a copy of the context
        HMAC_CTX* tmp = HMAC_CTX_new();
        if (tmp == 0) {
            isc_throw(LibraryError, "OpenSSL HMAC_CTX_new() failed");
        }
        if (!HMAC_CTX_copy(tmp, md_)) {
            HMAC_CTX_free(tmp);
            isc_throw(LibraryError, "OpenSSL HMAC_CTX_copy() failed");
        }
        ossl::SecBuf<unsigned char> digest(size);
        if (!HMAC_Final(tmp, &digest[0], NULL)) {
            HMAC_CTX_free(tmp);
            isc_throw(LibraryError, "OpenSSL HMAC_Final() failed");
        }
        HMAC_CTX_free(tmp);
        if (len > size) {
            len = size;
        }
        return (digest.same(sig, len));
    }

private:
    /// @brief The hash algorithm
    HashAlgorithm hash_algorithm_;

    /// @brief The protected pointer to the OpenSSL HMAC_CTX structure
    HMAC_CTX* md_;
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
