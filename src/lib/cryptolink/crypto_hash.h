// Copyright (C) 2014-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <util/buffer.h>

#include <boost/noncopyable.hpp>

#include <cryptolink/cryptolink.h>

#ifndef ISC_CRYPTO_HASH_H
#define ISC_CRYPTO_HASH_H

namespace isc {
namespace cryptolink {

/// Forward declaration, pimpl style
class HashImpl;

/// \brief Hash support
///
/// This class is used to create Hash digests. Instances
/// can be created with CryptoLink::createHash()
///
class Hash : private boost::noncopyable {
private:
    /// \brief Constructor from a hash algorithm
    ///
    /// \exception UnsupportedAlgorithmException if the given algorithm
    ///            is unknown or not supported by the underlying library
    /// \exception LibraryError if there was any unexpected exception
    ///                         in the underlying library
    ///
    /// \param hash_algorithm The hash algorithm
    Hash(const HashAlgorithm hash_algorithm);

    friend Hash* CryptoLink::createHash(const HashAlgorithm);

public:
    /// \brief Destructor
    ~Hash();

    /// \brief Returns the HashAlgorithm of the object
    ///
    /// \return hash algorithm
    HashAlgorithm getHashAlgorithm() const;

    /// \brief Returns the output size of the digest
    ///
    /// \return output size of the digest
    size_t getOutputLength() const;

    /// \brief Add data to digest
    ///
    /// \exception LibraryError if there was any unexpected exception
    ///                         in the underlying library
    ///
    /// \param data The data to add
    /// \param len The size of the data
    void update(const void* data, const size_t len);

    /// \brief Calculate the final digest
    ///
    /// The result will be appended to the given outputbuffer
    ///
    /// \exception LibraryError if there was any unexpected exception
    ///                         in the underlying library
    ///
    /// \param result The OutputBuffer to append the result to
    /// \param len The number of bytes from the result to copy. If this
    ///        value is smaller than the algorithms output size, the
    ///        result will be truncated. If this value is larger,
    ///        only output size bytes will be copied
    void final(isc::util::OutputBuffer& result, size_t len);

    /// \brief Calculate the final digest
    ///
    /// len bytes of data from the result will be copied to *result
    /// If len is larger than the output size, only output_size bytes
    /// will be copied. If it is smaller, the output will be truncated
    ///
    /// \exception LibraryError if there was any unexpected exception
    ///                         in the underlying library
    ///
    /// At least len bytes of data must be available for writing at
    /// result.
    ///
    /// \param result The memory location the digest will be written to
    /// \param len Specifies the size of the result location available
    void final(void* result, size_t len);

    /// \brief Calculate the final digest
    ///
    /// The result will be returned as a std::vector<uint8_t>
    ///
    /// \exception LibraryError if there was any unexpected exception
    ///                         in the underlying library
    ///
    /// \param len The number of bytes from the result to copy. If this
    ///        value is smaller than the algorithms output size, the
    ///        result will be truncated. If this value is larger,
    ///        only output size bytes will be copied
    /// \return a vector containing the signature
    std::vector<uint8_t> final(size_t len);

private:
    HashImpl* impl_;
};

/// \brief Create an Hash digest for the given data
///
/// This is a convenience function that calculates the hash digest,
/// given a fixed amount of data. Internally it does the same as
/// creating an Hash object, feeding it the data, and calculating the
/// resulting digest.
///
/// \exception UnsupportedAlgorithm if the given algorithm is unknown
///            or not supported by the underlying library
/// \exception LibraryError if there was any unexpected exception
///                         in the underlying library
///
/// \param data The data to digest
/// \param data_len The length of the data
/// \param hash_algorithm The hash algorithm
/// \param result The digest will be appended to this buffer
/// \param len If this is non-zero and less than the output size, the result
///            will be truncated to len bytes. If greater than output size
///            (or equal to zero) only output size bytes are written
void digest(const void* data,
            const size_t data_len,
            const HashAlgorithm hash_algorithm,
            isc::util::OutputBuffer& result,
            size_t len = 0);

/// \brief Delete an Hash object
void deleteHash(Hash* hash);

} // namespace cryptolink
} // namespace isc

#endif // ISC_CRYPTO_HASH_H

