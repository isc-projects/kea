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
/// for an algorithm that is not supported by the underlying library.
class UnsupportedAlgorithm : public CryptoLinkError {
public:
    UnsupportedAlgorithm(const char* file, size_t line, const char* what) :
        CryptoLinkError(file, line, what) {}
};

/// This exception is thrown when the underlying library could not
/// handle the key data.
class BadKey : public CryptoLinkError {
public:
    BadKey(const char* file, size_t line, const char* what) :
        CryptoLinkError(file, line, what) {}
};

/// This exception is raised when a general error that was not
/// specifically caught is thrown by the underlying library. It
/// is replaced by this one so as not have 'external' exceptions
/// bubbling up
class LibraryError : public CryptoLinkError {
public:
    LibraryError(const char* file, size_t line, const char* what) :
        CryptoLinkError(file, line, what) {}
};

/// Forward declaration for pimpl
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
/// manually through a call to the initalize(), before your first call
/// to getCryptoLink. Any subsequent call to initialize() will be a
/// noop.
///
/// \note All other classes within cryptolink should have private
/// constructors as well, and should have a factory function from this
/// class.
///
// Internal note: we can use this class later to initialize and manage
// dynamic (PKCS#11) libs
class CryptoLink : private boost::noncopyable {
public:
    /// \brief Returns a reference to the singleton instance
    ///
    /// If the library has not been initialized yet, it will be
    /// initialized with some default values.
    ///
    /// Since this class is noncopyable, you must use the return
    /// value directly, or store it in a reference variable.
    ///
    /// \exception InitializationError if initialization fails
    ///
    /// \return Reference to the singleton instance
    static CryptoLink& getCryptoLink();

    /// \brief Initialize the library manually
    ///
    /// If the library has already been initialized (either by a call
    /// to initialize() or automatically in getCryptoLink()), this
    /// function does nothing.
    ///
    /// \note A call to initialize() is not strictly necessary with
    /// the current implementation.
    ///
    /// \exception InitializationError if initialization fails
    ///
    static void initialize();

    /// \brief Factory function for HMAC objects
    ///
    /// CryptoLink objects cannot be constructed directly. This
    /// function creates a new HMAC object usable for signing or
    /// verification.
    ///
    /// The caller is responsible for deleting the object, and it is
    /// therefore highly recommended to place the return value of this
    /// function in a scoped_ptr or shared_ptr.
    ///
    /// Notes: if the secret is longer than the block size of its
    /// algorithm, the constructor will run it through the hash
    /// algorithm, and use the digest as the secret for this HMAC
    /// operation
    ///
    /// \exception UnsupportedAlgorithmException if the given algorithm
    ///            is unknown or not supported by the underlying library
    /// \exception InvalidKeyLength if the given key secret_len is bad
    /// \exception LibraryError if there was any unexpected exception
    ///                         in the underlying library
    ///
    /// \param secret The secret to sign with
    /// \param secret_len The length of the secret
    /// \param hash_algorithm The hash algorithm
    HMAC* createHMAC(const void* secret, size_t secret_len,
                     const HMAC::HashAlgorithm hash_algorithm);

private:
    // To enable us to use an optional explicit initialization call,
    // the 'real' instance getter is private
    static CryptoLink& getCryptoLinkInternal();

    // To prevent people constructing their own, we make the constructor
    // private too.
    CryptoLink() : impl_(NULL) {}
    ~CryptoLink();

    CryptoLinkImpl* impl_;
};

} // namespace cryptolink
} // namespace isc

#endif // _ISC_CRYPTO_H
