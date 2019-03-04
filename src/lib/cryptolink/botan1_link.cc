// Copyright (C) 2011-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_hash.h>
#include <cryptolink/crypto_hmac.h>
#include <cryptolink/crypto_rng.h>

#include <botan/botan.h>
#include <botan/init.h>
#include <botan/auto_rng.h>

namespace isc {
namespace cryptolink {

// For Botan, we use the CryptoLink class object in RAII style
class CryptoLinkImpl {
private:
    Botan::LibraryInitializer botan_init_;
};

CryptoLink::~CryptoLink() {
    rng_.reset();
    delete impl_;
}

/// \brief Botan implementation of RNG.
class RNGImpl : public RNG {
public:
    RNGImpl() {
        rng.reset(new Botan::AutoSeeded_RNG());
    }

    ~RNGImpl() {
    }

private:
    std::vector<uint8_t> random(size_t len) {
        std::vector<uint8_t> data;
        if (len > 0) {
            data.resize(len);
            try {
                rng->randomize(&data[0], len);
            } catch (const Botan::Exception& ex) {
                isc_throw(isc::cryptolink::LibraryError,
                          "Botan error: " << ex.what());
            }
        }
        return (data);
    }

    boost::shared_ptr<Botan::RandomNumberGenerator> rng;
};

void
CryptoLink::initialize() {
    CryptoLink& c = getCryptoLinkInternal();
    if (!c.impl_) {
        try {
            c.impl_ = new CryptoLinkImpl();
        } catch (const Botan::Exception& ex) {
            isc_throw(InitializationError, "Botan error: " << ex.what());
        }
    }
    if (!c.rng_) {
        try {
            c.rng_.reset(new RNGImpl());
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

