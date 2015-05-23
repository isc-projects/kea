// Copyright (C) 2011, 2014  Internet Systems Consortium, Inc. ("ISC")
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

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_hash.h>
#include <cryptolink/crypto_hmac.h>
#include <cryptolink/crypto_asym.h>

namespace isc {
namespace cryptolink {

CryptoLink&
CryptoLink::getCryptoLink() {
    CryptoLink& c = getCryptoLinkInternal();
    if (c.impl_ == NULL) {
        c.initialize();
    }
    return (c);
}

CryptoLink&
CryptoLink::getCryptoLinkInternal() {
    static CryptoLink instance;
    return (instance);
}

Hash*
CryptoLink::createHash(const HashAlgorithm hash_algorithm)
{
    return (new Hash(hash_algorithm));
}

HMAC*
CryptoLink::createHMAC(const void* secret, size_t secret_len,
                       const HashAlgorithm hash_algorithm)
{
    return (new HMAC(secret, secret_len, hash_algorithm));
}

Asym*
CryptoLink::createAsym(const void* key, size_t key_len,
		       const AsymAlgorithm asym_algorithm,
		       const HashAlgorithm hash_algorithm,
		       const AsymKeyKind key_kind,
		       const AsymFormat key_format)
{
    return (new Asym(key, key_len, asym_algorithm, hash_algorithm,
		     key_kind, key_format));
}

Asym*
CryptoLink::createAsym(const std::string& filename,
		       const std::string& password,
		       const AsymAlgorithm asym_algorithm,
		       const HashAlgorithm hash_algorithm,
		       const AsymKeyKind key_kind,
		       const AsymFormat file_format)
{
    return (new Asym(filename, password, asym_algorithm, hash_algorithm,
		     key_kind, file_format));
}

} // namespace cryptolink
} // namespace isc

