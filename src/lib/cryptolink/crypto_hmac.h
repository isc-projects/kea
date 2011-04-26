// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/buffer.h>

#include <boost/noncopyable.hpp>

#include <cryptolink/cryptolink.h>

#ifndef _ISC_CRYPTO_HMAC_H
#define _ISC_CRYPTO_HMAC_H

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
    ///        result will be truncated. If this value is larger, or 0
    ///        (the default), it will be ignored
    void sign(isc::dns::OutputBuffer& result, size_t len = 0);

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

    /// \brief Calculate the final signatre
    ///
    /// The result will be returned as a std::vector<uint8_t>
    ///
    /// \exception LibraryError if there was any unexpected exception
    ///                         in the underlying library
    ///
    /// \param len The number of bytes from the result to copy. If this
    ///        value is smaller than the algorithms output size, the
    ///        result will be truncated. If this value is larger, or 0
    ///        (the default), it will be ignored
    /// \return a vector containing the signature
    std::vector<uint8_t> sign(size_t len = 0);

    /// \brief Verify an existing signature
    ///
    /// \exception LibraryError if there was any unexpected exception
    ///                         in the underlying library
    ///
    /// \param sig The signature to verify
    /// \param len The length of the signature. If this is non-zero,
    ///            and smaller than the output length of the algorithm,
    ///            only len bytes will be checked
    /// \return true if the signature is correct, false otherwise
    bool verify(const void* sig, size_t len);

private:
    HMACImpl* impl_;
};

/// \brief Create an HMAC signature for the given data
///
/// This is a convenience function that calculates the hmac signature,
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
/// \param len If this is non-zero and less than the output size,
///            the result will be truncated to len bytes
void signHMAC(const void* data,
              const size_t data_len,
              const void* secret,
              size_t secret_len,
              const HashAlgorithm hash_algorithm,
              isc::dns::OutputBuffer& result,
              size_t len = 0);

/// \brief Verify an HMAC signature for the given data
///
/// This is a convenience function that verifies an hmac signature,
/// given a fixed amount of data. Internally it does the same as
/// creating an HMAC object, feeding it the data, and checking the
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

#endif // __ISC_CRYPTO_HMAC

