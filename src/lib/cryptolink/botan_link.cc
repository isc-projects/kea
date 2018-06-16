// Copyright (C) 2011-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_hash.h>
#include <cryptolink/crypto_hmac.h>

#include <botan/exceptn.h>
#include <botan/version.h>

namespace isc {
namespace cryptolink {

// For Botan, we use the CryptoLink class object in RAII style
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
        } catch (const Botan::Exception& ex) {
            isc_throw(InitializationError, "Botan error: " << ex.what());
        }
    }
}

std::string
CryptoLink::getVersion() {
    return (Botan::version_string());
}

} // namespace cryptolink
} // namespace isc

