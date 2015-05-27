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
#include <cryptolink/crypto_hash.h>

#include <boost/scoped_ptr.hpp>

#include <botan/version.h>
#include <botan/botan.h>
#include <botan/hash.h>
#include <botan/types.h>

#include <cryptolink/botan_common.h>

#include <cstring>

namespace isc {
namespace cryptolink {

/// @brief Decode the HashAlgorithm enum into a name usable by Botan
///
/// @param algorithm algorithm to be converted
/// @return text representation of the algorithm name
const char*
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
            hash = Botan::get_hash(btn::getHashAlgorithmName(hash_algorithm));
        } catch (const Botan::Algorithm_Not_Found&) {
            isc_throw(isc::cryptolink::UnsupportedAlgorithm,
                      "Unknown hash algorithm: " <<
                      static_cast<int>(hash_algorithm));
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError, exc.what());
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
#if BOTAN_VERSION_CODE >= BOTAN_VERSION_CODE_FOR(1,9,0)
        return (hash_->output_length());
#elif BOTAN_VERSION_CODE >= BOTAN_VERSION_CODE_FOR(1,8,0)
        return (hash_->OUTPUT_LENGTH);
#else
#error "Unsupported Botan version (need 1.8 or higher)"
        // added to suppress irrelevant compiler errors
        return 0;
#endif
    }

    /// @brief Adds data to the digest
    ///
    /// See @ref isc::cryptolink::Hash::update() for details.
    void update(const void* data, const size_t len) {
        try {
            hash_->update(static_cast<const Botan::byte*>(data), len);
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError, exc.what());
        }
    }

    /// @brief Calculate the final digest
    ///
    /// See @ref isc::cryptolink::Hash::final() for details.
    void final(isc::util::OutputBuffer& result, size_t len) {
        try {
            Botan::SecureVector<Botan::byte> b_result(hash_->final());

            if (len > b_result.size()) {
                len = b_result.size();
            }
            result.writeData(b_result.begin(), len);
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError, exc.what());
        }
    }

    /// @brief Calculate the final digest
    ///
    /// See @ref isc::cryptolink::Hash::final() for details.
    void final(void* result, size_t len) {
        try {
            Botan::SecureVector<Botan::byte> b_result(hash_->final());
            size_t output_size = getOutputLength();
            if (output_size > len) {
                output_size = len;
            }
            std::memcpy(result, b_result.begin(), output_size);
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError, exc.what());
        }
    }

    /// @brief Calculate the final digest
    ///
    /// See @ref isc::cryptolink::Hash::final() for details.
    std::vector<uint8_t> final(size_t len) {
        try {
            Botan::SecureVector<Botan::byte> b_result(hash_->final());
            if (len > b_result.size()) {
                return (std::vector<uint8_t>(b_result.begin(), b_result.end()));
            } else {
                return (std::vector<uint8_t>(b_result.begin(), &b_result[len]));
            }
        } catch (const Botan::Exception& exc) {
            isc_throw(isc::cryptolink::LibraryError, exc.what());
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
Hash:getHashAlgorithm() const {
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
