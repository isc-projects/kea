// Copyright (C) 2014-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cryptolink.h>
#include <cryptolink/crypto_hash.h>

#include <boost/scoped_ptr.hpp>

#include <botan/lookup.h>

#include <cryptolink/botan_common.h>

namespace isc {
namespace cryptolink {

const std::string
btn::getHashAlgorithmName(HashAlgorithm algorithm) {
    switch (algorithm) {
    case isc::cryptolink::MD5:
        return ("MD5");
    case isc::cryptolink::SHA1:
        return ("SHA-1");
    case isc::cryptolink::SHA256:
        return ("SHA-256");
    case isc::cryptolink::SHA224:
        return ("SHA-224");
    case isc::cryptolink::SHA384:
        return ("SHA-384");
    case isc::cryptolink::SHA512:
        return ("SHA-512");
    case isc::cryptolink::UNKNOWN_HASH:
        return ("Unknown");
    }
    // compiler should have prevented us to reach this, since we have
    // no default. But we need a return value anyway
    return ("Unknown");
}

/// @brief Botan implementation of Hash. Each method is the counterpart
/// of the Hash corresponding method.
class HashImpl {
public:

    /// @brief Constructor for specific hash algorithm
    ///
    /// @param hash_algorithm The hash algorithm
    explicit HashImpl(const HashAlgorithm hash_algorithm)
    : hash_algorithm_(hash_algorithm), hash_() {
        Botan::HashFunction* hash;
        try {
            const std::string& name =
                btn::getHashAlgorithmName(hash_algorithm);
            hash = Botan::HashFunction::create(name).release();
        } catch (const Botan::Algorithm_Not_Found&) {
            isc_throw(isc::cryptolink::UnsupportedAlgorithm,
                      "Unknown hash algorithm: " <<
                      static_cast<int>(hash_algorithm));
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError,
                      "Botan error: " << exc.what());
        }

        hash_.reset(hash);
    }

    /// @brief Destructor
    ~HashImpl() { }

    /// @brief Returns the HashAlgorithm of the object
    HashAlgorithm getHashAlgorithm() const {
        return (hash_algorithm_);
    }

    /// @brief Returns the output size of the digest
    ///
    /// @return output size of the digest
    size_t getOutputLength() const {
        return (hash_->output_length());
    }

    /// @brief Adds data to the digest
    ///
    /// See @ref isc::cryptolink::Hash::update() for details.
    void update(const void* data, const size_t len) {
        try {
            hash_->update(static_cast<const Botan::byte*>(data), len);
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError,
                      "Botan error: " << exc.what());
        }
    }

    /// @brief Calculate the final digest
    ///
    /// See @ref isc::cryptolink::Hash::final() for details.
    void final(isc::util::OutputBuffer& result, size_t len) {
        try {
            Botan::secure_vector<Botan::byte> b_result(hash_->final());

            if (len > b_result.size()) {
                len = b_result.size();
            }
            result.writeData(&b_result[0], len);
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError,
                      "Botan error: " << exc.what());
        }
    }

    /// @brief Calculate the final digest
    ///
    /// See @ref isc::cryptolink::Hash::final() for details.
    void final(void* result, size_t len) {
        try {
            Botan::secure_vector<Botan::byte> b_result(hash_->final());
            size_t output_size = getOutputLength();
            if (output_size > len) {
                output_size = len;
            }
            std::memcpy(result, &b_result[0], output_size);
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError,
                      "Botan error: " << exc.what());
        }
    }

    /// @brief Calculate the final digest
    ///
    /// See @ref isc::cryptolink::Hash::final() for details.
    std::vector<uint8_t> final(size_t len) {
        try {
            Botan::secure_vector<Botan::byte> b_result(hash_->final());
            if (len > b_result.size()) {
                len = b_result.size();
            }
            // Return vector with content. Construct &b_result[len] attempts
            // to get an address of one element beyond the b_result. Replaced
            // with the address of first element + len
            return (std::vector<uint8_t>(&b_result[0], &b_result[0]+len));
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError,
                      "Botan error: " << exc.what());
        }
    }

private:
    /// @brief The hash algorithm
    HashAlgorithm hash_algorithm_;

    /// @brief The protected pointer to the Botan HashFunction object
    boost::scoped_ptr<Botan::HashFunction> hash_;
};

Hash::Hash(const HashAlgorithm hash_algorithm)
{
    impl_ = new HashImpl(hash_algorithm);
}

Hash::~Hash() {
    delete impl_;
}

HashAlgorithm
Hash::getHashAlgorithm() const {
    return (impl_->getHashAlgorithm());
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
