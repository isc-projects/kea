// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Do not include this header directly: use crypto_tls.h instead.

#ifndef COMMON_TLS_H
#define COMMON_TLS_H

/// @file common_tls.h Common TLS API.

// Verify that this file was not directly included.
#ifndef CRYPTO_TLS_H
#error crypto_tls.h must be included in place of common_tls.h
#endif

#include <cryptolink/cryptolink.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <netinet/in.h>
#include <sys/socket.h>

namespace isc {
namespace asiolink {

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

/// @brief Forward declaration of OpenSSL TLS context.
class TlsContext;

/// @brief The type of shared pointers to TlsContext objects.
///
/// @note Not clear we need shared pointers but they covers more use cases...
typedef boost::shared_ptr<TlsContext> TlsContextPtr;

/// @brief TLS stream base class.
///
/// @tparam Callback The type of callbacks.
/// @tparam TlsStreamImpl The type of underlying TLS streams.
/// @tparam TlsCertificate The type of X509 certificates.
template <typename Callback, typename TlsStreamImpl, typename TlsCertificate>
class TlsStreamBase : public TlsStreamImpl {
public:

    /// @brief Constructor.
    ///
    /// @param service I/O Service object used to manage the stream.
    /// @param context Pointer to the TLS context.
    /// @note The caller must not provide a null pointer to the TLS context.
    TlsStreamBase(IOService& service, TlsContextPtr context);

    /// @brief Destructor.
    virtual ~TlsStreamBase() { }

    /// @brief Returns the role.
    TlsRole getRole() const {
        return (role_);
    }

    /// @brief TLS Handshake.
    ///
    /// @param callback Callback object.
    virtual void handshake(Callback& callback) = 0;

    /// @brief TLS shutdown.
    ///
    /// @param callback Callback object.
    virtual void shutdown(Callback& callback) = 0;

    /// @brief Clear the TLS state.
    virtual void clear() = 0;

    /// @brief Return the peer certificate.
    ///
    /// @note The native_handle() method is used so it can't be made const.
    /// @note Do not forget to free it when no longer used.
    virtual TlsCertificate* getPeerCert() = 0;

    /// @break Return the commonName part of the subjectName of
    /// the peer certificate.
    ///
    /// First commonName when there are more than one, in UTF-8.
    ///
    /// @return The commonName part of the subjectName or the empty string.
    virtual std::string getSubject() = 0;

    /// @break Return the commonName part of the issuerName of
    /// the peer certificate.
    ///
    /// First commonName when there are more than one, in UTF-8.
    ///
    /// @return The commonName part of the issuerName or the empty string.
    virtual std::string getIssuer() = 0;

    /// @brief The role i.e. client or server.
    TlsRole role_;
};

} // namespace asiolink
} // namespace isc

#endif // COMMON_TLS_H
