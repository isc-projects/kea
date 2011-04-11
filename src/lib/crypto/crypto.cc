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

} // namespace crypto
} // namespace isc

