// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_hash.h>
#include <cryptolink/crypto_hmac.h>

#include <openssl/crypto.h>

namespace isc {
namespace cryptolink {

// For OpenSSL, we use the CryptoLink class object in RAII style
class CryptoLinkImpl {
    // empty class
};

CryptoLink::~CryptoLink() {
    delete impl_;
}

void
CryptoLink::initialize() {
    CryptoLink& c = getCryptoLinkInternal();
    if (c.impl_ == NULL) {
        try {
            c.impl_ = new CryptoLinkImpl();
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
}

std::string
CryptoLink::getVersion() {
    return (SSLeay_version(SSLEAY_VERSION));
}

} // namespace cryptolink
} // namespace isc

