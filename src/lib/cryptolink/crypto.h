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

#ifndef _ISC_CRYPTO_H
#define _ISC_CRYPTO_H

#include <string>
#include <dns/buffer.h>
#include <exceptions/exceptions.h>

#include <boost/noncopyable.hpp>

#include <cryptolink/crypto_hmac.h>


namespace isc {
namespace cryptolink {

/// General exception class that is the base for all crypto-related
/// exceptions
class CryptoLinkError : public Exception {
public:
    CryptoLinkError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// This exception is thrown if there was a problem initializing the
/// crypto library
class InitializationError : public CryptoLinkError {
public:
    InitializationError(const char* file, size_t line, const char* what) :
        CryptoLinkError(file, line, what) {}
};

/// This exception is thrown when a cryptographic action is requested
/// for an algorithm that is not supported by the underlying algorithm.
class UnsupportedAlgorithm : public CryptoLinkError {
public:
    UnsupportedAlgorithm(const char* file, size_t line, const char* what) :
        CryptoLinkError(file, line, what) {}
};

/// This exception is thrown when the underlying library could not
/// handle this key
class BadKey : public CryptoLinkError {
public:
    BadKey(const char* file, size_t line, const char* what) :
        CryptoLinkError(file, line, what) {}
};

class CryptoLinkImpl;

/// \brief 
///
/// This is singleton class that serves as the entry point to
/// the underlying cryptography library, and as a factory for objects
/// within the cryptolink library.
///
/// There is only one way to access it, through getCryptoLink(), which
/// returns a reference to the initialized library. On the first call,
/// it will be initialized automatically. You can however initialize it
/// manually through a call to the initalize(). Any subsequent call to
/// initialize() will be a noop.
///
/// All other classes within cryptolink should have private
/// constructors, and should have a factory function from this class.
///
// Internal note: we can use this class later to initialize and manage
// dynamic (PKCS#11) libs
class CryptoLink : private boost::noncopyable {
public:
    /// \brief Returns a reference to the singleton instance
    ///
    /// If the library has not been initialized yet, it will be
    /// initialized with some default values.
    static CryptoLink& getCryptoLink();

    /// \brief Initialize the library manually
    ///
    /// \note A call to initialize() is not strictly necessary with
    /// the current implementation.
    static void initialize();

    /// \brief Factory function for HMAC objects
    ///
    /// CryptoLink objects cannot be constructed directly. This
    /// function creates a new HMAC object usable for signing or
    /// verification.
    ///
    /// The caller is responsible for deleting the object later, and
    /// it is therefore highly recommended to place the return value
    /// of this function in a scoped_ptr or shared_ptr.
    HMAC* createHMAC(const void* secret, size_t secret_len,
                     const HMAC::HashAlgorithm hash_algorithm);

private:
    // To enable us to use an optional explicit initialization call,
    // the 'real' instance getter is private
    static CryptoLink& getCryptoLinkInternal();

    // To prevent people constructing their own, we make the constructor
    // private too.
    CryptoLink() : impl_(NULL) {};
    ~CryptoLink();

    CryptoLinkImpl* impl_;
};

/// Entry point for the API
/// If the library has not been initialized, this will automatically
/// initialize it with default values

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

} // namespace cryptolink
} // namespace isc

#endif // _ISC_CRYPTO_H
