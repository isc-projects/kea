// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cryptolink.h>
#include <cryptolink/crypto_hmac.h>

#include <boost/scoped_ptr.hpp>

#include <botan/version.h>
#include <botan/botan.h>
#include <botan/hmac.h>
#include <botan/hash.h>
#include <botan/types.h>

#include <cryptolink/botan_common.h>

#include <cstring>

namespace isc {
namespace cryptolink {

/// @brief Botan implementation of HMAC. Each method is the counterpart
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
        Botan::HashFunction* hash;
        try {
            hash = Botan::get_hash(btn::getHashAlgorithmName(hash_algorithm));
        } catch (const Botan::Algorithm_Not_Found&) {
            isc_throw(isc::cryptolink::UnsupportedAlgorithm,
                      "Unknown hash algorithm: " <<
                      static_cast<int>(hash_algorithm));
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError, exc.what());
        }

        hmac_.reset(new Botan::HMAC(hash));

        // If the key length is larger than the block size, we hash the
        // key itself first.
        try {
            // use a temp var so we don't have blocks spanning
            // preprocessor directives
#if BOTAN_VERSION_CODE >= BOTAN_VERSION_CODE_FOR(1,9,0)
            size_t block_length = hash->hash_block_size();
#elif BOTAN_VERSION_CODE >= BOTAN_VERSION_CODE_FOR(1,8,0)
            size_t block_length = hash->HASH_BLOCK_SIZE;
#else
#error "Unsupported Botan version (need 1.8 or higher)"
            // added to suppress irrelevant compiler errors
            size_t block_length = 0;
#endif
            if (secret_len > block_length) {
                Botan::SecureVector<Botan::byte> hashed_key =
                    hash->process(static_cast<const Botan::byte*>(secret),
                                  secret_len);
                hmac_->set_key(hashed_key.begin(), hashed_key.size());
            } else {
                // Botan 1.8 considers len 0 a bad key. 1.9 does not,
                // but we won't accept it anyway, and fail early
                if (secret_len == 0) {
                    isc_throw(BadKey, "Bad HMAC secret length: 0");
                }
                hmac_->set_key(static_cast<const Botan::byte*>(secret),
                               secret_len);
            }
        } catch (const Botan::Invalid_Key_Length& ikl) {
            isc_throw(BadKey, ikl.what());
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError, exc.what());
        }
    }

    /// @brief Destructor
    ~HMACImpl() {
    }

    /// @brief Returns the output size of the digest
    ///
    /// @return output size of the digest
    size_t getOutputLength() const {
#if BOTAN_VERSION_CODE >= BOTAN_VERSION_CODE_FOR(1,9,0)
        return (hmac_->output_length());
#elif BOTAN_VERSION_CODE >= BOTAN_VERSION_CODE_FOR(1,8,0)
        return (hmac_->OUTPUT_LENGTH);
#else
#error "Unsupported Botan version (need 1.8 or higher)"
        // added to suppress irrelevant compiler errors
        return 0;
#endif
    }

    /// @brief Add data to digest
    ///
    /// See @ref isc::cryptolink::HMAC::update() for details.
    void update(const void* data, const size_t len) {
        try {
            hmac_->update(static_cast<const Botan::byte*>(data), len);
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError, exc.what());
        }
    }

    /// @brief Calculate the final signature
    ///
    /// See @ref isc::cryptolink::HMAC::sign() for details.
    void sign(isc::util::OutputBuffer& result, size_t len) {
        try {
            Botan::SecureVector<Botan::byte> b_result(hmac_->final());

            if (len > b_result.size()) {
                len = b_result.size();
            }
            result.writeData(b_result.begin(), len);
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError, exc.what());
        }
    }

    /// @brief Calculate the final signature
    ///
    /// See @ref isc::cryptolink::HMAC::sign() for details.
    void sign(void* result, size_t len) {
        try {
            Botan::SecureVector<Botan::byte> b_result(hmac_->final());
            size_t output_size = getOutputLength();
            if (output_size > len) {
                output_size = len;
            }
            std::memcpy(result, b_result.begin(), output_size);
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError, exc.what());
        }
    }

    /// @brief Calculate the final signature
    ///
    /// See @ref isc::cryptolink::HMAC::sign() for details.
    std::vector<uint8_t> sign(size_t len) {
        try {
            Botan::SecureVector<Botan::byte> b_result(hmac_->final());
            if (len > b_result.size()) {
                return (std::vector<uint8_t>(b_result.begin(), b_result.end()));
            } else {
                return (std::vector<uint8_t>(b_result.begin(), &b_result[len]));
            }
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError, exc.what());
        }
    }


    /// @brief Verify an existing signature
    ///
    /// See @ref isc::cryptolink::HMAC::verify() for details.
    bool verify(const void* sig, size_t len) {
        /// @todo Botan's verify_mac checks if len matches the output_length,
        /// which causes it to fail for truncated signatures, so we do
        /// the check ourselves
        try {
            Botan::SecureVector<Botan::byte> our_mac = hmac_->final();
            size_t size = getOutputLength();
            if (len < 10 || len < size / 2) {
                return (false);
            }
            if (len > size) {
                len = size;
            }
            return (Botan::same_mem(&our_mac[0],
                                    static_cast<const unsigned char*>(sig),
                                    len));
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError, exc.what());
        }
    }

private:
    /// \brief The protected pointer to the Botan HMAC object
    boost::scoped_ptr<Botan::HMAC> hmac_;
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
