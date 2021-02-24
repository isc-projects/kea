// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#ifdef WITH_OPENSSL

#include <asiolink/asio_wrapper.h>
#include <asiolink/crypto_tls.h>
#include <asiolink/openssl_tls.h>

#include <sys/stat.h>

#include <openssl/opensslv.h>

using namespace boost::asio;
using namespace boost::asio::ssl;
using namespace boost::system;
using namespace isc::cryptolink;

namespace isc {
namespace asiolink {

TlsContext::TlsContext(TlsRole role)
    : TlsContextBase(role), cert_required_(true),
      context_(context::method::tls) {
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

namespace { // anonymous namespace

// C++17 has this function but Kea is still C++11 so provide it.
bool
isDir(const std::string& name) {
    struct stat stats;
    if (::stat(name.c_str(), &stats) < 0) {
        return (false);
    }
    return ((stats.st_mode & S_IFMT) == S_IFDIR);
}

} // end of namespace

void
TlsContext::configure(TlsContextPtr& context,
                      TlsRole role,
                      const std::string& ca_file,
                      const std::string& cert_file,
                      const std::string& key_file,
                      bool cert_required) {
    try {
        context.reset(new TlsContext(role));
        if (isDir(ca_file)) {
            context->loadCaPath(ca_file);
        } else {
            context->loadCaFile(ca_file);
        }
        context->loadCertFile(cert_file);
        context->loadKeyFile(key_file);
        context->setCertRequired(cert_required);
    } catch (...) {
        context.reset();
        throw;
    }
}

} // namespace asiolink
} // namespace isc

#endif // WITH_OPENSSL
