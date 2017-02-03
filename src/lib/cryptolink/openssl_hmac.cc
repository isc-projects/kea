// Copyright (C) 2014-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cryptolink.h>
#include <cryptolink/crypto_hmac.h>

#include <boost/move/unique_ptr.hpp>

#include <openssl/hmac.h>

#include <cryptolink/openssl_common.h>

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

        md_.reset(HMAC_CTX_new());
        if (!HMAC_Init_ex(md_.get(), secret,
                          static_cast<int>(secret_len),
                          algo, NULL)) {
            isc_throw(LibraryError, "HMAC_Init_ex");
        }
    }

    /// @brief Returns the HashAlgorithm of the object
    HashAlgorithm getHashAlgorithm() const {
        return (hash_algorithm_);
    }

    /// @brief Returns the output size of the digest
    ///
    /// @return output size of the digest
    size_t getOutputLength() const {
        int size = HMAC_size(md_.get());
        if (size < 0) {
            isc_throw(LibraryError, "HMAC_size");
        }
        return (static_cast<size_t>(size));
    }

    /// @brief Add data to digest
    ///
    /// See @ref isc::cryptolink::HMAC::update() for details.
    void update(const void* data, const size_t len) {
        if (!HMAC_Update(md_.get(),
                         static_cast<const unsigned char*>(data),
                         len)) {
            isc_throw(LibraryError, "HMAC_Update");
        }
    }

    /// @brief Calculate the final signature
    ///
    /// See @ref isc::cryptolink::HMAC::sign() for details.
    void sign(isc::util::OutputBuffer& result, size_t len) {
        size_t size = getOutputLength();
        ossl::SecBuf<unsigned char> digest(size);
        if (!HMAC_Final(md_.get(), &digest[0], NULL)) {
            isc_throw(LibraryError, "HMAC_Final");
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
        if (!HMAC_Final(md_.get(), &digest[0], NULL)) {
            isc_throw(LibraryError, "HMAC_Final");
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
        if (!HMAC_Final(md_.get(), &digest[0], NULL)) {
            isc_throw(LibraryError, "HMAC_Final");
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
        HMAC_CTX tmp;
        HMAC_CTX_init(&tmp);
        if (!HMAC_CTX_copy(&tmp, md_.get())) {
            isc_throw(LibraryError, "HMAC_CTX_copy");
        }
        ossl::SecBuf<unsigned char> digest(size);
        if (!HMAC_Final(&tmp, &digest[0], NULL)) {
            HMAC_CTX_cleanup(&tmp);
            isc_throw(LibraryError, "HMAC_Final");
        }
        HMAC_CTX_cleanup(&tmp);
        if (len > size) {
            len = size;
        }
        return (digest.same(sig, len));
    }

private:
    class HMAC_Deleter {
    public:
        void operator()(HMAC_CTX *ptr) { HMAC_CTX_free(ptr); }
    };

#if OPENSSL_VERSION_NUMBER < 0x10100000L
    static HMAC_CTX* HMAC_CTX_new() {
        HMAC_CTX *ptr = new HMAC_CTX;
        HMAC_CTX_init(ptr);
        return ptr;
    }
    static void HMAC_CTX_free(HMAC_CTX *ptr) {
        HMAC_CTX_cleanup(ptr);
        delete ptr;
    }
#endif

    /// @brief The hash algorithm
    HashAlgorithm hash_algorithm_;

    /// @brief The protected pointer to the OpenSSL HMAC_CTX structure
    boost::movelib::unique_ptr<HMAC_CTX, HMAC_Deleter> md_;
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
