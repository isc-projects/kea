// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file openssl_tls.cc OpenSSL implementation of the TLS API.

#include <config.h>

#ifdef WITH_OPENSSL

#include <asiolink/asio_wrapper.h>
#include <asiolink/crypto_tls.h>

#include <sys/stat.h>

#include <openssl/opensslv.h>

using namespace boost::asio;
using namespace boost::asio::ssl;
using namespace boost::system;
using namespace isc::cryptolink;

namespace isc {
namespace asiolink {

// Enforce TLS 1.2 when the generic TLS method is not available (i.e.
// the boost version is older than 1.64.0).
TlsContext::TlsContext(TlsRole role)
    : TlsContextBase(role), cert_required_(true),
#ifdef HAVE_GENERIC_TLS_METHOD
      context_(context::method::tls)
#else
#ifdef HAVE_TLS_1_2_METHOD
      context_(context::method::tlsv12)
#else
      context_(context::method::tlsv1)
#endif
#endif
{
    // Not leave the verify mode to OpenSSL default.
    setCertRequired(true);
}

boost::asio::ssl::context&
TlsContext::getContext() {
    return (context_);
}

::SSL_CTX*
TlsContext::getNativeContext() {
    return (context_.native_handle());
}

void
TlsContext::setCertRequired(bool cert_required) {
    if (!cert_required && (getRole() == TlsRole::CLIENT)) {
        isc_throw(BadValue,
                  "'cert-required' parameter must be true for a TLS client");
    }
    cert_required_ = cert_required;
    error_code ec;
    int mode = verify_peer | verify_fail_if_no_peer_cert;
    if (!cert_required_) {
        mode = verify_none;
    }
    context_.set_verify_mode(mode, ec);
    if (ec) {
        isc_throw(LibraryError, ec.message());
    }
}

bool
TlsContext::getCertRequired() const {
    return (cert_required_);
}

void
TlsContext::loadCaFile(const std::string& ca_file) {
    error_code ec;
    context_.load_verify_file(ca_file, ec);
    if (ec) {
        isc_throw(LibraryError, ec.message());
    }
}

void
TlsContext::loadCaPath(const std::string& ca_path) {
    error_code ec;
    context_.add_verify_path(ca_path, ec);
    if (ec) {
        isc_throw(LibraryError, ec.message());
    }
}

void
TlsContext::loadCertFile(const std::string& cert_file) {
    error_code ec;
    context_.use_certificate_chain_file(cert_file, ec);
    if (ec) {
        isc_throw(LibraryError, ec.message());
    }
}

void
TlsContext::loadKeyFile(const std::string& key_file) {
    error_code ec;
    context_.use_private_key_file(key_file, context::file_format::pem, ec);
    if (ec) {
        isc_throw(LibraryError, ec.message());
    }
}

} // namespace asiolink
} // namespace isc

#endif // WITH_OPENSSL
