// Copyright (C) 2011-2015,2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_hash.h>
#include <cryptolink/crypto_hmac.h>

#define BOTAN_NO_DEPRECATED_WARNINGS

#include <botan/botan.h>
#include <botan/init.h>

namespace isc {
namespace cryptolink {

// For Botan, we use the CryptoLink class object in RAII style
class CryptoLinkImpl {
private:
    Botan::LibraryInitializer botan_init_;
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

