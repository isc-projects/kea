// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cryptolink.h>
#include <cryptolink/crypto_hash.h>

#include <boost/scoped_ptr.hpp>

#include <openssl/evp.h>

#include <cryptolink/openssl_common.h>

#include <cstring>

namespace isc {
namespace cryptolink {

/// @brief Decode the HashAlgorithm enum into an EVP_MD pointer (or 0)
///
/// EVP_MD pointer is a OpenSSL's way of identifying hash algorithms
/// @param algorithm algorithm to be converted
/// @return pointer to EVP_MD which identifies the algorithm
const EVP_MD*
ossl::getHashAlgorithm(HashAlgorithm algorithm) {
    switch (algorithm) {
    case isc::cryptolink::MD5:
        return (EVP_md5());
    case isc::cryptolink::SHA1:
        return (EVP_sha1());
    case isc::cryptolink::SHA256:
        return (EVP_sha256());
    case isc::cryptolink::SHA224:
        return (EVP_sha224());
    case isc::cryptolink::SHA384:
        return (EVP_sha384());
    case isc::cryptolink::SHA512:
        return (EVP_sha512());
    case isc::cryptolink::UNKNOWN_HASH:
        return (0);
    }
    // compiler should have prevented us to reach this, since we have
    // no default. But we need a return value anyway
    return (0);
}

/// \brief OpenSSL implementation of Hash. Each method is the counterpart
/// of the Hash corresponding method.
class HashImpl {
public:

    /// @brief Constructor for specific hash algorithm
    ///
    /// @param hash_algorithm The hash algorithm
    explicit HashImpl(const HashAlgorithm hash_algorithm) {
        const EVP_MD* algo = ossl::getHashAlgorithm(hash_algorithm);
        if (algo == 0) {
            isc_throw(isc::cryptolink::UnsupportedAlgorithm,
                      "Unknown hash algorithm: " <<
                      static_cast<int>(hash_algorithm));
        }

        md_.reset(new EVP_MD_CTX);

        EVP_MD_CTX_init(md_.get());

        EVP_DigestInit_ex(md_.get(), algo, NULL);
    }

    /// @brief Destructor
    ~HashImpl() {
        if (md_) {
            EVP_MD_CTX_cleanup(md_.get());
        }
    }

    /// @brief Returns the output size of the digest
    ///
    /// @return output size of the digest
    size_t getOutputLength() const {
        return (EVP_MD_CTX_size(md_.get()));
    }

    /// @brief Adds data to the digest
    ///
    /// See @ref isc::cryptolink::Hash::update() for details.
    void update(const void* data, const size_t len) {
        EVP_DigestUpdate(md_.get(), data, len);
    }

    /// @brief Calculate the final digest
    ///
    /// See @ref isc::cryptolink::Hash::final() for details.
    void final(isc::util::OutputBuffer& result, size_t len) {
        size_t size = getOutputLength();
        std::vector<unsigned char> digest(size);
        EVP_DigestFinal_ex(md_.get(), &digest[0], NULL);
        if (len > size) {
             len = size;
        }
        result.writeData(&digest[0], len);
    }

    /// @brief Calculate the final digest
    ///
    /// See @ref isc::cryptolink::Hash::final() for details.
    void final(void* result, size_t len) {
        size_t size = getOutputLength();
        std::vector<unsigned char> digest(size);
        EVP_DigestFinal_ex(md_.get(), &digest[0], NULL);
        if (len > size) {
             len = size;
        }
        std::memcpy(result, &digest[0], len);
    }

    /// @brief Calculate the final digest
    ///
    /// See @ref isc::cryptolink::Hash::final() for details.
    std::vector<uint8_t> final(size_t len) {
        size_t size = getOutputLength();
        std::vector<unsigned char> digest(size);
        EVP_DigestFinal_ex(md_.get(), &digest[0], NULL);
        if (len < size) {
            digest.resize(len);
        }
        return (std::vector<uint8_t>(digest.begin(), digest.end()));
    }

private:
    /// @brief The protected pointer to the OpenSSL EVP_MD_CTX structure
    boost::scoped_ptr<EVP_MD_CTX> md_;
};

Hash::Hash(const HashAlgorithm hash_algorithm)
{
    impl_ = new HashImpl(hash_algorithm);
}

Hash::~Hash() {
    delete impl_;
}

size_t
Hash::getOutputLength() const {
    return (impl_->getOutputLength());
}

void
Hash::update(const void* data, const size_t len) {
    impl_->update(data, len);
}

void
Hash::final(isc::util::OutputBuffer& result, size_t len) {
    impl_->final(result, len);
}

void
Hash::final(void* result, size_t len) {
    impl_->final(result, len);
}

std::vector<uint8_t>
Hash::final(size_t len) {
    return impl_->final(len);
}

} // namespace cryptolink
} // namespace isc
