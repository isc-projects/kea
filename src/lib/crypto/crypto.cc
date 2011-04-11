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

#include "crypto_botan.h"
#include <botan/botan.h>
#include <botan/hmac.h>
#include <botan/hash.h>
#include <botan/types.h>

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/tsigkey.h>
#include <dns/util/base64.h>

#include <string>

using namespace Botan;
using namespace std;
using namespace isc::dns;

namespace {
HashFunction* getHash(const Name& hash_name) {
    if (hash_name == TSIGKey::HMACMD5_NAME()) {
        return get_hash("MD5");
    } else if (hash_name == TSIGKey::HMACSHA1_NAME()) {
        return get_hash("SHA-1");
    } else if (hash_name == TSIGKey::HMACSHA256_NAME()) {
        return get_hash("SHA-256");
    } else {
        isc_throw(isc::crypto::UnsupportedAlgorithm,
                  "Unknown Hash type " + hash_name.toText());
    }
}

// Library needs to have been inited during the entire program
// should we make this a singleton? (for hsm we'll need more
// initialization, and dynamic loading)
LibraryInitializer init;

} // local namespace

namespace isc {
namespace crypto {

void
signHMAC(const OutputBuffer& data, TSIGKey key,
         isc::dns::OutputBuffer& result)
{
    // get algorithm from key, then 'translate' to Botan-specific algo
    HashFunction* hash = getHash(key.getAlgorithmName());
    HMAC::HMAC hmac(hash);

    // Take the 'secret' from the key
    // If the key length is larger than the block size, we hash the
    // key itself first.
    try {
        if (key.getSecretLength() > hash->HASH_BLOCK_SIZE) {
            SecureVector<byte> hashed_key =
                hash->process(static_cast<const byte*>(key.getSecret()),
                              key.getSecretLength());
            hmac.set_key(hashed_key.begin(), hashed_key.size());
        } else {
            hmac.set_key(static_cast<const byte*>(key.getSecret()),
                         key.getSecretLength());
        }
    } catch (Invalid_Key_Length ikl) {
        isc_throw(BadKey, ikl.what());
    }

    // update the data from whatever we get (probably as a buffer)
    hmac.update(static_cast<const byte*>(data.getData()),
                data.getLength());

    // And generate the mac
    SecureVector<byte> b_result(hmac.final());

    // write mac to result
    result.writeData(b_result.begin(), b_result.size());
}

bool
verifyHMAC(const OutputBuffer& data, TSIGKey key,
           const isc::dns::OutputBuffer& result)
{
    HashFunction* hash = getHash(key.getAlgorithmName());
    HMAC::HMAC hmac(hash);
    // If the key length is larger than the block size, we hash the
    // key itself first.
    try {
        if (key.getSecretLength() > hash->HASH_BLOCK_SIZE) {
            SecureVector<byte> hashed_key =
                hash->process(static_cast<const byte*>(key.getSecret()),
                              key.getSecretLength());
            hmac.set_key(hashed_key.begin(), hashed_key.size());
        } else {
            hmac.set_key(static_cast<const byte*>(key.getSecret()),
                         key.getSecretLength());
        }
    } catch (Invalid_Key_Length ikl) {
        isc_throw(BadKey, ikl.what());
    }

    hmac.update(static_cast<const byte*>(data.getData()),
                data.getLength());

    return hmac.verify_mac(static_cast<const byte*>(result.getData()),
                           result.getLength());
}

isc::dns::TSIGKey
TSIGKeyFromString(const std::string& str) {
    size_t pos = str.find(':');
    if (pos == 0 || pos == str.npos) {
        // error
        isc_throw(InvalidParameter, "Invalid TSIG key string");
    }
    try {
        Name key_name(str.substr(0, pos));
        Name algo_name("hmac-md5.sig-alg.reg.int");

        // optional algorithm part
        size_t pos2 = str.find(':', pos+1);
        if (pos2 != str.npos) {
            if (pos2 == pos + 1) {
                isc_throw(InvalidParameter, "Invalid TSIG key string");
            }
            algo_name = Name(str.substr(pos2+1));
        } else {
            pos2 = str.size() - pos;
        }

        std::string secret_str = str.substr(pos + 1, pos2 - pos - 1);
    
        vector<uint8_t> secret;
        decodeBase64(secret_str, secret);
        unsigned char secret_b[secret.size()];
        for (size_t i=0; i < secret.size(); ++i) {
            secret_b[i] = secret[i];
        }

        return isc::dns::TSIGKey(key_name, algo_name, secret_b, secret.size());
    } catch (Exception e) {
        // 'reduce' the several types of exceptions name parsing and
        // Base64 decoding can throw to just the InvalidParameter
        isc_throw(InvalidParameter, e.what());
    }
}

std::string
TSIGKeyToString(const isc::dns::TSIGKey& key) {
    const uint8_t* secret_b = static_cast<const uint8_t*>(key.getSecret());
    vector<uint8_t> secret_v;
    for (size_t i=0; i < key.getSecretLength(); ++i) {
        secret_v.push_back(secret_b[i]);
    }
    std::string secret_str = encodeBase64(secret_v);
    
    return key.getKeyName().toText() + ":" + secret_str + ":" + key.getAlgorithmName().toText();
}


} // namespace crypto
} // namespace isc

