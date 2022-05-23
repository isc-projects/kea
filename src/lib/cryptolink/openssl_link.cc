// Copyright (C) 2014-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_rng.h>
#include <cryptolink/crypto_hash.h>
#include <cryptolink/crypto_hmac.h>

#include <openssl/crypto.h>
#include <openssl/rand.h>

namespace isc {
namespace cryptolink {

// For OpenSSL, we use the CryptoLink class object in RAII style
class CryptoLinkImpl {
};

CryptoLink::~CryptoLink() {
}

/// \brief OpenSSL implementation of RNG.
class RNGImpl : public RNG {
public:
    RNGImpl() { }

    ~RNGImpl() { }

private:
    std::vector<uint8_t> random(size_t len) {
        std::vector<uint8_t> data;
        if (len > 0) {
            data.resize(len);
            if (RAND_bytes(&data[0], len) != 1) {
                isc_throw(isc::cryptolink::LibraryError,
                          "OpenSSL RAND_bytes() failed");
            }
        }
        return (data);
    }
};

void
CryptoLink::initialize(CryptoLink& c) {
    if (!c.impl_) {
        try {
            c.impl_.reset(new CryptoLinkImpl());
        } catch (const std::exception &ex) {
            // Should never happen
            isc_throw(InitializationError,
                      "Error during OpenSSL initialization:" << ex.what());
        } catch (...) {
            // Should never happen
            isc_throw(InitializationError,
                      "Error during OpenSSL initialization");
        }
    }
    if (!c.rng_) {
        try {
            c.rng_.reset(new RNGImpl());
        } catch (const std::exception &ex) {
            // Should never happen
            isc_throw(InitializationError,
                      "Error during OpenSSL RNG initialization:" << ex.what());
        } catch (...) {
            // Should never happen
            isc_throw(InitializationError,
                      "Error during OpenSSL RNG initialization");
        }
    }
}

std::string
CryptoLink::getVersion() {
    return (SSLeay_version(SSLEAY_VERSION));
}

} // namespace cryptolink
} // namespace isc
