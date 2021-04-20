// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file botan_tls.cc Botan fake implementation of the TLS API.

#include <config.h>

#if defined(WITH_BOTAN) && !defined(WITH_BOTAN_BOOST)

#include <asiolink/asio_wrapper.h>
#include <asiolink/crypto_tls.h>

namespace isc {
namespace asiolink {

TlsContext::TlsContext(TlsRole role)
    : TlsContextBase(role), cert_required_(true) {
}

void
TlsContext::setCertRequired(bool cert_required) {
    if (!cert_required && (getRole() == TlsRole::CLIENT)) {
        isc_throw(BadValue,
                  "'cert-required' parameter must be true for a TLS client");
    }
    cert_required_ = cert_required;
}

bool
TlsContext::getCertRequired() const {
    return (cert_required_);
}

void
TlsContext::loadCaFile(const std::string&) {
    isc_throw(NotImplemented, "Botan TLS is not yet supported");
}

void
TlsContext::loadCaPath(const std::string&) {
    isc_throw(NotImplemented, "loadCaPath is not implemented by Botan");
}

void
TlsContext::loadCertFile(const std::string&) {
    isc_throw(NotImplemented, "Botan TLS is not yet supported");
}

void
TlsContext::loadKeyFile(const std::string&) {
    isc_throw(NotImplemented, "Botan TLS is not yet supported");
}

} // namespace asiolink
} // namespace isc

#endif // WITH_BOTAN && !WITH_BOTAN_BOOST
