// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
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
#include <cryptolink/crypto_hmac.h>

#include <boost/scoped_ptr.hpp>

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
                      const HashAlgorithm hash_algorithm) {
        const EVP_MD* algo = ossl::getHashAlgorithm(hash_algorithm);
        if (algo == 0) {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown hash algorithm: " <<
                      static_cast<int>(hash_algorithm));
        }
        if (secret_len == 0) {
            isc_throw(BadKey, "Bad HMAC secret length: 0");
        }

        md_.reset(new HMAC_CTX);
        HMAC_CTX_init(md_.get());

        HMAC_Init_ex(md_.get(), secret,
                     static_cast<int>(secret_len),
                     algo, NULL);
    }

    /// @brief Destructor
    ~HMACImpl() {
        if (md_) {
            HMAC_CTX_cleanup(md_.get());
        }
    }

    /// @brief Returns the output size of the digest
    ///
    /// @return output size of the digest
    size_t getOutputLength() const {
        int size = HMAC_size(md_.get());
        if (size < 0) {
            isc_throw(isc::cryptolink::LibraryError, "EVP_MD_CTX_size");
        }
        return (static_cast<size_t>(size));
    }

    /// @brief Add data to digest
    ///
    /// See @ref isc::cryptolink::HMAC::update() for details.
    void update(const void* data, const size_t len) {
        HMAC_Update(md_.get(), static_cast<const unsigned char*>(data), len);
    }

    /// @brief Calculate the final signature
    ///
    /// See @ref isc::cryptolink::HMAC::sign() for details.
    void sign(isc::util::OutputBuffer& result, size_t len) {
        size_t size = getOutputLength();
        ossl::SecBuf<unsigned char> digest(size);
        HMAC_Final(md_.get(), &digest[0], NULL);
        if (len == 0 || len > size) {
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
        HMAC_Final(md_.get(), &digest[0], NULL);
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
        HMAC_Final(md_.get(), &digest[0], NULL);
        if (len != 0 && len < size) {
            digest.resize(len);
        }
        return (std::vector<uint8_t>(digest.begin(), digest.end()));
    }

    /// @brief Verify an existing signature
    ///
    /// See @ref isc::cryptolink::HMAC::verify() for details.
    bool verify(const void* sig, size_t len) {
        size_t size = getOutputLength();
        if (len != 0 && (len < 10 || len < size / 2)) {
            return (false);
        }
        ossl::SecBuf<unsigned char> digest(size);
        HMAC_Final(md_.get(), &digest[0], NULL);
        if (len == 0 || len > size) {
            len = size;
        }
        return (digest.same(sig, len));
    }

private:

    /// @brief The protected pointer to the OpenSSL HMAC_CTX structure
    boost::scoped_ptr<HMAC_CTX> md_;
};

HMAC::HMAC(const void* secret, size_t secret_length,
           const HashAlgorithm hash_algorithm)
{
    impl_ = new HMACImpl(secret, secret_length, hash_algorithm);
}

HMAC::~HMAC() {
    delete impl_;
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
