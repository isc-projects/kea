// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Do not include this header directly: use crypto_tls.h instead.

#ifndef BOTAN_TLS_H
#define BOTAN_TLS_H

/// @file botan_tls.h Botan fake implementation of the TLS API.

#if defined(WITH_BOTAN) && !defined(WITH_BOTAN_BOOST)

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_asio_socket.h>
#include <asiolink/io_service.h>
#include <asiolink/common_tls.h>

#include <exceptions/exceptions.h>

namespace isc {
namespace asiolink {

/// @brief Botan TLS context.
class TlsContext : public TlsContextBase {
public:

    /// @brief Destructor.
    virtual ~TlsContext() { }

    /// @brief Create a fresh context.
    ///
    /// @param role The TLS role client or server.
    explicit TlsContext(TlsRole role);

    /// @brief Get the peer certificate requirement mode.
    ///
    /// @return True if peer certificates are required, false if they
    /// are optional.
    virtual bool getCertRequired() const;

protected:
    /// @brief Set the peer certificate requirement mode.
    ///
    /// @param cert_required True if peer certificates are required,
    /// false if they are optional.
    virtual void setCertRequired(bool cert_required);

    /// @brief Load the trust anchor aka certification authority.
    ///
    /// @param ca_file The certificate file name.
    /// @throw isc::cryptolink::LibraryError on various errors as
    /// file not found, bad format, etc.
    virtual void loadCaFile(const std::string& ca_file);

    /// @brief Load the trust anchor aka certification authority.
    ///
    /// @param ca_path The certificate directory name.
    /// @throw isc::cryptolink::LibraryError on various errors as
    /// file not found, bad format, etc.
    virtual void loadCaPath(const std::string& ca_path);

    /// @brief Load the certificate file.
    ///
    /// @param cert_file The certificate file name.
    /// @throw isc::cryptolink::LibraryError on various errors as
    /// file not found, bad format, etc.
    virtual void loadCertFile(const std::string& cert_file);

    /// @brief Load the private key from a file.
    ///
    /// @param key_file The private key file name.
    /// @throw isc::cryptolink::LibraryError on various errors as
    /// file not found, bad format, etc.
    virtual void loadKeyFile(const std::string& key_file);

    /// @brief Cached cert_required value.
    bool cert_required_;

    /// @brief Allow access to protected methods by the base class.
    friend class TlsContextBase;
};

/// @brief The type of Botan TLS streams (in fact pure TCP streams).
typedef boost::asio::ip::tcp::socket TlsStreamImpl;

/// @brief TlsStreamBase constructor.
///
/// @tparam Callback The type of callbacks.
/// @tparam TlsStreamImpl The type of underlying TLS streams.
/// @param service I/O Service object used to manage the stream.
/// @param context Pointer to the TLS context.
/// @note The caller must not provide a null pointer to the TLS context.
template <typename Callback, typename TlsStreamImpl>
TlsStreamBase<Callback, TlsStreamImpl>::
TlsStreamBase(IOService& service, TlsContextPtr context)
    : TlsStreamImpl(service.get_io_service()), role_(context->getRole()) {
}

/// @brief Botan fake TLS stream.
///
/// @tparam callback The callback.
template <typename Callback>
class TlsStream : public TlsStreamBase<Callback, TlsStreamImpl> {
public:

    /// @brief Type of the base.
    typedef TlsStreamBase<Callback, TlsStreamImpl> Base;

    /// @brief Constructor.
    ///
    /// @param service I/O Service object used to manage the stream.
    /// @param context Pointer to the TLS context.
    /// @note The caller must not provide a null pointer to the TLS context.
    TlsStream(IOService& service, TlsContextPtr context)
        : Base(service, context) {
    }

    /// @brief Destructor.
    virtual ~TlsStream() { }

    /// @brief TLS Handshake.
    virtual void handshake(Callback&) {
        isc_throw(NotImplemented, "Botan TLS is not yet supported");
    }

    /// @brief TLS shutdown.
    virtual void shutdown(Callback&) {
        isc_throw(NotImplemented, "Botan TLS is not yet supported");
    }

    /// @brief Return the commonName part of the subjectName of
    /// the peer certificate.
    ///
    /// First commonName when there are more than one, in UTF-8.
    /// RFC 3280 provides as a commonName example "Susan Housley",
    /// to idea to give access to this come from the Role Based
    /// Access Control experiment.
    ///
    ///
    /// @return The commonName part of the subjectName or the empty string.
    std::string getSubject() {
        return ("");
    }

    /// @brief Return the commonName part of the issuerName of
    /// the peer certificate.
    ///
    /// First commonName when there are more than one, in UTF-8.
    /// The issuerName is the subjectName of the signing certificate
    /// (the issue in PKIX terms). The idea is to encode a group as
    /// members of an intermediate certification authority.
    ///
    ///
    /// @return The commonName part of the issuerName or the empty string.
    std::string getIssuer() {
        return ("");
    }
};

} // namespace asiolink
} // namespace isc

#endif // WITH_BOTAN && !WITH_BOTAN_BOOST

#endif // BOTAN_TLS_H
