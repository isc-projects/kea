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

#include <string>
#include <dns/buffer.h>
#include <exceptions/exceptions.h>

#include <boost/noncopyable.hpp>

#ifndef _ISC_CRYPTO_H
#define _ISC_CRYPTO_H

namespace isc {
namespace crypto {

/// General exception class that is the base for all crypto-related
/// exceptions
class CryptoError : public Exception {
public:
    CryptoError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// This exception is thrown if there was a problem initializing the
/// crypto library
class InitializationError : public CryptoError {
public:
    InitializationError(const char* file, size_t line, const char* what) :
        CryptoError(file, line, what) {}
};

/// This exception is thrown when a cryptographic action is requested
/// for an algorithm that is not supported by the underlying algorithm.
class UnsupportedAlgorithm : public CryptoError {
public:
    UnsupportedAlgorithm(const char* file, size_t line, const char* what) :
        CryptoError(file, line, what) {}
};

/// This exception is thrown when the underlying library could not
/// handle this key
class BadKey : public CryptoError {
public:
    BadKey(const char* file, size_t line, const char* what) :
        CryptoError(file, line, what) {}
};

class CryptoImpl;

/// \brief Initializer object
///
/// This object represents 'global' state for the backend crypto
/// library, and must be initialized before any cryptographic calls
/// are made. It may not be destroyed until all cryptographic objects
/// are.
/// Preferably, this object is created in the program's main() function
// Internal note: we can use this class later to initialize and manage
// dynamic (PKCS#11) libs
class Crypto {
public:
    Crypto();
    ~Crypto();
private:
    CryptoImpl* impl_;
};

/// Forward declaration, pimpl style
class HMACImpl;

/// \brief HMAC support
///
/// This class is used to create and verify HMAC signatures
///
class HMAC : private boost::noncopyable {
public:
    enum HashAlgorithm {
        MD5 = 0,            ///< MD5
        SHA1 = 1,           ///< SHA-1
        SHA256 = 2,         ///< SHA-256
        UNKNOWN = 3         ///< This value can be used in conversion
                            ///  functions, to be returned when the
                            ///  input is unknown (but a value MUST be
                            ///  returned), for instance when the input
                            ///  is a Name or a string, and the return
                            ///  value is a HashAlgorithm.
    };

    /// \brief Constructor from a secret and a hash algorithm
    ///
    /// \exception UnsupportedAlgorithmException if the given algorithm
    ///            is unknown or not supported by the underlying library
    /// \exception InvalidKeyLength if the given key secret_len is bad
    ///
    /// Notes: if the secret is longer than the block size of its
    /// algorithm, the constructor will run it through the hash
    /// algorithm, and use the digest as the secret for this HMAC
    /// operation
    ///
    /// \param secret The secret to sign with
    /// \param len The length of the secret
    /// \param hash_algorithm The hash algorithm
    explicit HMAC(const void* secret, size_t secret_len,
                  const HashAlgorithm hash_algorithm);

    /// \brief Destructor
    ~HMAC();

    /// \brief Returns the output size of the digest
    ///
    /// \return output size of the digest
    size_t getOutputLength() const;

    /// \brief Add data to digest
    ///
    /// \param data The data to add
    /// \param len The size of the data
    void update(const void* data, const size_t len);

    /// \brief Calculate the final signature
    ///
    /// The result will be appended to the given outputbuffer
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
    /// At least len bytes of data must be available for writing at
    /// result
    void sign(void* result, size_t len);

    /// \brief Calculate the final signatre
    ///
    /// The result will be returned as a std::vector<uint8_t>
    ///
    /// \param len The number of bytes from the result to copy. If this
    ///        value is smaller than the algorithms output size, the
    ///        result will be truncated. If this value is larger, or 0
    ///        (the default), it will be ignored
    /// \return a vector containing the signature
    std::vector<uint8_t> sign(size_t len = 0);

    /// \brief Verify an existing signature
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
              const HMAC::HashAlgorithm hash_algorithm,
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
                const HMAC::HashAlgorithm hash_algorithm,
                const void* sig,
                const size_t sig_len);

} // namespace crypto
} // namespace isc

#endif // _ISC_CRYPTO_H
