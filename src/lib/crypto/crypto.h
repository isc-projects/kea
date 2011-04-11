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

// This is an abstraction layer from an actual crypto implementation
// The abstraction works as follows; we provide abstract base classes,
// one general one for the entire library, one for a per-operation
// context, and one for 'keys', in all their forms as we need them
// for BIND10.
// Any implementation (we currently use Botan as a backend), should
// subclass all of these, and provide the necessary translations
// between our calls and the underlying library. This also includes
// translating between 'real' algorithm identifiers and ours.
//
// For future expansion, we may need to introduce a fourth type; sessions
//

#include <string>
#include <dns/buffer.h>
#include <dns/tsigkey.h>
#include <exceptions/exceptions.h>

#ifndef _ISC_CRYPTO_H
#define _ISC_CRYPTO_H

namespace isc {
namespace crypto {

class CryptoError : public Exception {
public:
    CryptoError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

class UnsupportedAlgorithm : public CryptoError {
public:
    UnsupportedAlgorithm(const char* file, size_t line, const char* what) :
        CryptoError(file, line, what) {}
};

// The underlying library could not handle this key
class BadKey : public CryptoError {
public:
    BadKey(const char* file, size_t line, const char* what) :
        CryptoError(file, line, what) {}
};

/// \brief Create an HMAC signature for the given data
///
/// Raises an UnsupportedAlgorithm if we do not support the given
/// algorithm. Raises a BadKey exception if the underlying library
/// cannot handle the given TSIGKey (for instance if it has a bad
/// length).
///
/// \param data The data to sign
/// \param key The TSIGKey to sign with
/// \param result The signature will be written to the end of this buffer
void signHMAC(const isc::dns::OutputBuffer& data,
              isc::dns::TSIGKey key,
              isc::dns::OutputBuffer& result);

/// \brief Verify an HMAC signature for the given data
///
/// Raises an UnsupportedAlgorithm if we do not support the given
/// algorithm. Raises a BadKey exception if the underlying library
/// cannot handle the given TSIGKey (for instance if it has a bad
/// length).
///
/// \param data The data to verify
/// \param key The TSIGKey to verify with
/// \param mac The signature to verify
/// \return True if the signature verifies, false if not
bool verifyHMAC(const isc::dns::OutputBuffer& data,
                isc::dns::TSIGKey key,
                const isc::dns::OutputBuffer& mac);

} // namespace crypto
} // namespace isc

#endif // _ISC_CRYPTO_H
