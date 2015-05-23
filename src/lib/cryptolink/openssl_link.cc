// Copyright (C) 2014, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_hash.h>
#include <cryptolink/crypto_hmac.h>

#include <openssl/crypto.h>

#include <openssl/evp.h>

namespace isc {
namespace cryptolink {

// For OpenSSL, we use the CryptoLink class object in RAII style
class CryptoLinkImpl {
    // empty class
};

CryptoLink::~CryptoLink() {
    EVP_cleanup();
    delete impl_;
}

void
CryptoLink::initialize() {
    CryptoLink& c = getCryptoLinkInternal();
    if (c.impl_ == NULL) {
        try {
            c.impl_ = new CryptoLinkImpl();
            OpenSSL_add_all_algorithms();
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

