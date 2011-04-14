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

#include "crypto.h"

#include <iostream>
#include <iomanip>

#include <botan/botan.h>
#include <botan/hmac.h>
#include <botan/hash.h>
#include <botan/types.h>

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/tsigkey.h>
#include <dns/util/base64.h>

#include <string>

using namespace std;
using namespace isc::dns;

namespace {
Botan::HashFunction* getHash(const Name& hash_name) {
    if (hash_name == TSIGKey::HMACMD5_NAME()) {
        return Botan::get_hash("MD5");
    } else if (hash_name == TSIGKey::HMACSHA1_NAME()) {
        return Botan::get_hash("SHA-1");
    } else if (hash_name == TSIGKey::HMACSHA256_NAME()) {
        return Botan::get_hash("SHA-256");
    } else {
        isc_throw(isc::crypto::UnsupportedAlgorithm,
                  "Unknown Hash type " + hash_name.toText());
    }
}

// Library needs to have been inited during the entire program
// should we make this a singleton? (for hsm we'll need more
// initialization, and dynamic loading)
Botan::LibraryInitializer init;

} // local namespace

namespace isc {
namespace crypto {

class HMACImpl {
public:
    explicit HMACImpl(const TSIGKey& key) {
        Botan::HashFunction* hash = getHash(key.getAlgorithmName());
        hmac_ = new Botan::HMAC::HMAC(hash);

        // Take the 'secret' from the key
        // If the key length is larger than the block size, we hash the
        // key itself first.
        try {
            if (key.getSecretLength() > hash->HASH_BLOCK_SIZE) {
                Botan::SecureVector<Botan::byte> hashed_key =
                    hash->process(static_cast<const Botan::byte*>(key.getSecret()),
                                  key.getSecretLength());
                hmac_->set_key(hashed_key.begin(), hashed_key.size());
            } else {
                hmac_->set_key(static_cast<const Botan::byte*>(key.getSecret()),
                             key.getSecretLength());
            }
        } catch (Botan::Invalid_Key_Length ikl) {
            isc_throw(BadKey, ikl.what());
        }
    }

    ~HMACImpl() { delete hmac_; }

    void update(const void* data, const size_t len) {
        // update the data from whatever we get (probably as a buffer)
        hmac_->update(static_cast<const Botan::byte*>(data), len);
    }

    void sign(isc::dns::OutputBuffer& result) const {
        // And generate the mac
        Botan::SecureVector<Botan::byte> b_result(hmac_->final());
    
        // write mac to result
        result.writeData(b_result.begin(), b_result.size());
    }
    
    bool verify(const void* sig, const size_t len) const {
        return (hmac_->verify_mac(static_cast<const Botan::byte*>(sig), len));
    }

private:
    Botan::HMAC* hmac_;
};

HMAC::HMAC(const TSIGKey& key) {
    impl_ = new HMACImpl(key);
}

HMAC::~HMAC() {
    delete impl_;
}

void
HMAC::update(const void* data, const size_t len) {
    impl_->update(data, len);
}

void
HMAC::sign(isc::dns::OutputBuffer& result) const {
    impl_->sign(result);
}

bool
HMAC::verify(const void* sig, const size_t len) const {
    return (impl_->verify(sig, len));
}

void
signHMAC(const void* data, size_t data_len, const TSIGKey& key,
         isc::dns::OutputBuffer& result)
{
    HMAC hmac(key);
    hmac.update(data, data_len);
    hmac.sign(result);
}


bool
verifyHMAC(const void* data, const size_t data_len, const TSIGKey& key,
           const void* sig, const size_t sig_len)
{
    HMAC hmac(key);
    hmac.update(data, data_len);
    return (hmac.verify(sig, sig_len));
}

} // namespace crypto
} // namespace isc

