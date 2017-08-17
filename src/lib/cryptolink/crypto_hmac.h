// Copyright (C) 2011-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <util/buffer.h>

#include <boost/noncopyable.hpp>

#include <cryptolink/cryptolink.h>

#ifndef ISC_CRYPTO_HMAC_H
#define ISC_CRYPTO_HMAC_H

namespace isc {
namespace cryptolink {

/// Forward declaration, pimpl style
class HMACImpl;

/// \brief HMAC support
///
/// This class is used to create and verify HMAC signatures. Instances
/// can be created with CryptoLink::createHMAC()
///
class HMAC : private boost::noncopyable {
private:
    /// \brief Constructor from a secret and a hash algorithm
    ///
    /// \exception UnsupportedAlgorithmException if the given algorithm
    ///            is unknown or not supported by the underlying library
    /// \exception InvalidKeyLength if the given key secret_len is bad
    /// \exception LibraryError if there was any unexpected exception
    ///                         in the underlying library
    ///
    /// Notes: if the secret is longer than the block size of its
    /// algorithm, the constructor will run it through the hash
    /// algorithm, and use the digest as the secret for this HMAC
    /// operation
    ///
    /// \param secret The secret to sign with
    /// \param len The length of the secret
    /// \param hash_algorithm The hash algorithm
    HMAC(const void* secret, size_t secret_len,
         const HashAlgorithm hash_algorithm);

    friend HMAC* CryptoLink::createHMAC(const void*, size_t,
                                        const HashAlgorithm);

public:
    /// \brief Destructor
    ~HMAC();

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

    /// \brief Calculate the final signature
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
    void sign(isc::util::OutputBuffer& result, size_t len);

    /// \brief Calculate the final signature
    ///
    /// len bytes of data from the result will be copied to *result
    /// If len is larger than the output size, only output_size bytes
    /// will be copied. If it is smaller, the output will be truncated
    ///
    /// \exception LibraryError if there was any unexpected exception
    ///                         in the underlying library
    ///
    /// At least len bytes of data must be available for writing at
    /// result
    void sign(void* result, size_t len);

    /// \brief Calculate the final signature
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
    std::vector<uint8_t> sign(size_t len);

    /// \brief Verify an existing signature
    ///
    /// \exception LibraryError if there was any unexpected exception
    ///                         in the underlying library
    ///
    /// \param sig The signature to verify
    /// \param len The length of the signature. If this is smaller
    ///            than the output length of the algorithm,
    ///            only len bytes will be checked. If this is
    ///            larger than the output length of the algorithm,
    ///            only output size bytes will be checked
    /// \return true if the signature is correct, false otherwise
    ///
    /// \note verify() does not destroy its context so it can be
    /// called multiple times with different signatures.
    bool verify(const void* sig, size_t len);

private:
    HMACImpl* impl_;
};

/// \brief Create an HMAC signature for the given data
///
/// This is a convenience function that calculates the HMAC signature,
/// given a fixed amount of data. Internally it does the same as
/// creating an HMAC object, feeding it the data, and calculating the
/// resulting signature.
///
/// \exception UnsupportedAlgorithm if the given algorithm is unknown
///            or not supported by the underlying library
/// \exception BadKey if the given key secret_len is bad
/// \exception LibraryError if there was any unexpected exception
///                         in the underlying library
///
/// Notes: if the secret is longer than the block size of its
/// algorithm, the constructor will run it through the hash
/// algorithm, and use the digest as the secret for this HMAC
/// operation
///
/// \param data The data to sign
/// \param data_len The length of the data
/// \param secret The secret to sign with
/// \param secret_len The length of the secret
/// \param hash_algorithm The hash algorithm
/// \param result The signature will be appended to this buffer
/// \param len If this is non-zero and less than the output size, the result
///            will be truncated to len bytes. If greater than output size
///            (or equal to zero) only output size bytes are written
void signHMAC(const void* data,
              const size_t data_len,
              const void* secret,
              size_t secret_len,
              const HashAlgorithm hash_algorithm,
              isc::util::OutputBuffer& result,
              size_t len = 0);

/// \brief Verify an HMAC signature for the given data
///
/// This is a convenience function that verifies an hmac signature,
/// given a fixed amount of data. Internally it does the same as
/// creating an HMAC object, feeding it the data, and checking the
/// resulting signature at the exception a zero sig_len is
/// internally replaced by the output size.
///
/// \exception UnsupportedAlgorithm if the given algorithm is unknown
///            or not supported by the underlying library
/// \exception BadKey if the given key secret_len is bad
/// \exception LibraryError if there was any unexpected exception
///                         in the underlying library
///
/// Notes: if the secret is longer than the block size of its
/// algorithm, the constructor will run it through the hash
/// algorithm, and use the digest as the secret for this HMAC
/// operation
///
/// \param data The data to verify
/// \param data_len The length of the data
/// \param secret The secret to sign with
/// \param secret_len The length of the secret
/// \param hash_algorithm The hash algorithm
/// \param sig The signature to verify
/// \param sig_len The length of the signature
/// \return True if the signature verifies, false if not
bool verifyHMAC(const void* data,
                const size_t data_len,
                const void* secret,
                size_t secret_len,
                const HashAlgorithm hash_algorithm,
                const void* sig,
                const size_t sig_len);

/// \brief Delete an HMAC object
void deleteHMAC(HMAC* hmac);

} // namespace cryptolink
} // namespace isc

#endif // ISC_CRYPTO_HMAC_H

