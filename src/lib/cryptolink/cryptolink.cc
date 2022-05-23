// Copyright (C) 2011-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_hash.h>
#include <cryptolink/crypto_hmac.h>

namespace isc {
namespace cryptolink {

CryptoLink&
CryptoLink::getCryptoLink() {
    static CryptoLink instance;
    return (instance);
}

Hash*
CryptoLink::createHash(const HashAlgorithm hash_algorithm) {
    return (new Hash(hash_algorithm));
}

HMAC*
CryptoLink::createHMAC(const void* secret, size_t secret_len,
                       const HashAlgorithm hash_algorithm) {
    return (new HMAC(secret, secret_len, hash_algorithm));
}

RNGPtr&
CryptoLink::getRNG() {
    return (rng_);
}

} // namespace cryptolink
} // namespace isc

