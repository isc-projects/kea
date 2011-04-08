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

#ifndef _ISC_CRYPTO_H
#define _ISC_CRYPTO_H

void doHMAC(const isc::dns::OutputBuffer& data, char* key, isc::dns::OutputBuffer& result);
bool verifyHMAC(const isc::dns::OutputBuffer& data, char* key, const isc::dns::OutputBuffer& mac);

namespace isc {
namespace crypto {

class Crypto {
    static Crypto& getInstance();
    virtual void init() = 0;
    virtual void cleanup() = 0;
};

class TSIGKeyImpl;

class TSIGKey {
public:
    enum algorithms {
        TSIG_HMAC_MD5 = 1,
        TSIG_HMAC_SHA256 = 2
    };

    TSIGKey(const std::string& str);
    ~TSIGKey();
    algorithms getAlgorithm();
    const char* getSecret();
    size_t getSecretLength();
    
private:
    TSIGKeyImpl* impl_;
};

class Context {
    virtual ~Context();
    
    virtual void update(void *data, size_t length) = 0;
    virtual void signTSIG(void *result, TSIGKey* key) = 0;
    virtual void verifyTSIG(void *signature, TSIGKey* key) = 0;
    virtual void digest(void *result) = 0;
};

} // namespace crypto
} // namespace isc

#endif // _ISC_CRYPTO_H
