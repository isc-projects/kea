// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file common_tls.cc Common part of implementations of the TLS API.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/crypto_tls.h>
#include <util/file_utilities.h>

using namespace isc::cryptolink;
using namespace isc::util;

namespace isc {
namespace asiolink {

void
TlsContextBase::configure(TlsContextPtr& context,
                          TlsRole role,
                          const std::string& ca_file,
                          const std::string& cert_file,
                          const std::string& key_file,
                          bool cert_required) {
    try {
        context.reset(new TlsContext(role));
        context->setCertRequired(cert_required);
        if (file::isDir(ca_file)) {
            try {
                context->loadCaPath(ca_file);
            } catch (const std::exception& ex) {
                isc_throw(isc::BadValue, "load of CA directory '"
                          << ca_file << "' failed: " << ex.what());
            }
        } else {
            try {
                context->loadCaFile(ca_file);
            } catch (const std::exception& ex) {
                isc_throw(isc::BadValue, "load of CA file '"
                          << ca_file << "' failed: " << ex.what());
            }
        }
        try {
            context->loadCertFile(cert_file);
        } catch (const std::exception& ex) {
            isc_throw(isc::BadValue, "load of cert file '"
                      << cert_file << "' failed: " << ex.what());
        }
        try {
            context->loadKeyFile(key_file);
        } catch (const std::exception& ex) {
            isc_throw(isc::BadValue, "load of private key file '"
                      << key_file << "' failed: " << ex.what());
        }
    } catch (...) {
        context.reset();
        throw;
    }
}

} // namespace asiolink
} // namespace isc
