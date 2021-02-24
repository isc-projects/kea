// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CRYPTO_TLS_H
#define CRYPTO_TLS_H

#include <cryptolink/cryptolink.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <netinet/in.h>
#include <sys/socket.h>

namespace isc {
namespace asiolink {

/// @file crypto_tls.h Common TLS API.

/// @brief Client and server roles.
enum TlsRole { CLIENT, SERVER };

/// @brief TLS context base class.
class TlsContextBase : private boost::noncopyable {
public:
    /// @brief Destructor.
    virtual ~TlsContextBase() { }

    /// @brief Create a fresh context.
    ///
    /// @param role The TLS role client or server.
    explicit TlsContextBase(TlsRole role) : role_(role) { }

    /// @brief Returns the role.
    TlsRole getRole() const {
        return (role_);
    }

    /// @note No need for a role set method.

    /// @brief Set the peer certificate requirement mode.
    ///
    /// @param cert_required True if peer certificates are required,
    /// false if they are optional.
    virtual void setCertRequired(bool cert_required) = 0;

    /// @brief Get the peer certificate requirement mode.
    ///
    /// @return True if peer certificates are required, false if they
    /// are optional.
    virtual bool getCertRequired() const = 0;

    /// @brief Load the trust anchor aka certificate authority.
    ///
    /// @param ca_file The certificate file name.
    /// @throw isc::cryptolink::LibraryError on various errors as
    /// file not found, bad format, etc.
    virtual void loadCaFile(const std::string& ca_file) = 0;

    /// @brief Load the trust anchor aka certificate authority.
    ///
    /// @param ca_path The certificate directory name.
    /// @throw isc::cryptolink::LibraryError on various errors as
    /// file not found, bad format, etc.
    virtual void loadCaPath(const std::string& ca_path) = 0;

    /// @brief Load the certificate file.
    ///
    /// @param cert_file The certificate file name.
    /// @throw isc::cryptolink::LibraryError on various errors as
    /// file not found, bad format, etc.
    virtual void loadCertFile(const std::string& cert_file) = 0;

    /// @brief Load the private key file name.
    ///
    /// @param key_file The private key file name.
    /// @throw isc::cryptolink::LibraryError on various errors as
    /// file not found, bad format, etc.
    virtual void loadKeyFile(const std::string& key_file) = 0;

public:
    /// @brief The role i.e. client or server.
    TlsRole role_;
};

} // namespace asiolink
} // namespace isc

#endif // CRYPTO_TLS_H
