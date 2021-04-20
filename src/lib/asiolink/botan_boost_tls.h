// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Do not include this header directly: use crypto_tls.h instead.

#ifndef BOTAN_BOOST_TLS_H
#define BOTAN_BOOST_TLS_H

/// @file botan_boost_tls.h Botan boost ASIO implementation of the TLS API.

#if defined(WITH_BOTAN) && defined(WITH_BOTAN_BOOST)

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_asio_socket.h>
#include <asiolink/io_service.h>
#include <asiolink/common_tls.h>
#include <exceptions/exceptions.h>

#include <asiolink/botan_boost_wrapper.h>
#include <botan/asio_stream.h>

namespace isc {
namespace asiolink {

/// @brief Translate TLS role into implementation.
inline Botan::TLS::Connection_Side roleToImpl(TlsRole role) {
    if (role == TlsRole::SERVER) {
        return (Botan::TLS::Connection_Side::SERVER);
    } else {
        return (Botan::TLS::Connection_Side::CLIENT);
    }
}

/// @brief Forward declaration of Botan TLS context.
class TlsContextImpl;

/// @brief Botan boost ASIO TLS context.
class TlsContext : public TlsContextBase {
public:

    /// @brief Destructor.
    ///
    /// @note The destructor can't be defined here because  a unique
    /// pointer to an incomplete type is used.
    virtual ~TlsContext();

    /// @brief Create a fresh context.
    ///
    /// @param role The TLS role client or server.
    explicit TlsContext(TlsRole role);

    /// @brief Return the underlying context.
    Botan::TLS::Context& getContext();

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
    virtual void loadCaFile(const std::string& ca_file);

    /// @brief Load the trust anchor aka certification authority.
    ///
    /// @param ca_path The certificate directory name.
    virtual void loadCaPath(const std::string& ca_path);

    /// @brief Load the certificate file.
    ///
    /// @param cert_file The certificate file name.
    virtual void loadCertFile(const std::string& cert_file);

    /// @brief Load the private key from a file.
    ///
    /// @param key_file The private key file name.
    virtual void loadKeyFile(const std::string& key_file);

    /// @brief Botan TLS context.
    std::unique_ptr<TlsContextImpl> impl_;

    /// @brief Allow access to protected methods by the base class.
    friend class TlsContextBase;
};

/// @brief The type of underlying TLS streams.
typedef Botan::TLS::Stream<boost::asio::ip::tcp::socket> TlsStreamImpl;

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
    : TlsStreamImpl(service.get_io_service(), context->getContext()),
      role_(context->getRole()) {
}

/// @brief Botan boost ASIO TLS stream.
///
/// @tparam callback The callback.
template <typename Callback>
class TlsStream : public TlsStreamBase<Callback, TlsStreamImpl>
{
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
    ///
    /// @param callback Callback object.
    virtual void handshake(Callback& callback) {
        Base::async_handshake(roleToImpl(Base::getRole()), callback);
    }

    /// @brief TLS shutdown.
    ///
    /// @param callback Callback object.
    virtual void shutdown(Callback& callback) {
        Base::async_shutdown(callback);
    }

    /// @brief Clear the TLS object.
    ///
    /// @note The idea to reuse a TCP connection for a fresh TLS is at
    /// least arguable. Currently it does nothing so the socket is
    /// **not** reusable.
    virtual void clear() {
    }

    /// @brief Return the commonName part of the subjectName of
    /// the peer certificate.
    ///
    /// First commonName when there are more than one, in UTF-8.
    /// RFC 3280 provides as a commonName example "Susan Housley",
    /// to idea to give access to this come from the Role Based
    /// Access Control experiment.
    ///
    /// @return The commonName part of the subjectName or the empty string.
    virtual std::string getSubject() {
        const std::vector<Botan::X509_Certificate>& cert_chain =
            Base::native_handle()->peer_cert_chain();
        if (cert_chain.empty()) {
            return ("");
        }
        const Botan::X509_DN& subject = cert_chain[0].subject_dn();
        return (subject.get_first_attribute("CommonName"));
    }

    /// @brief Return the commonName part of the issuerName of
    /// the peer certificate.
    ///
    /// First commonName when there are more than one, in UTF-8.
    /// The issuerName is the subjectName of the signing certificate
    /// (the issue in PKIX terms). The idea is to encode a group as
    /// members of an intermediate certification authority.
    ///
    /// @return The commonName part of the issuerName or the empty string.
    virtual std::string getIssuer() {
        const std::vector<Botan::X509_Certificate>& cert_chain =
            Base::native_handle()->peer_cert_chain();
        if (cert_chain.empty()) {
            return ("");
        }
        const Botan::X509_DN& issuer = cert_chain[0].issuer_dn();
        return (issuer.get_first_attribute("CommonName"));
    }
};

// Stream truncated error code.
const int STREAM_TRUNCATED = Botan::TLS::StreamError::StreamTruncated;

} // namespace asiolink
} // namespace isc

#endif // WITH_BOTAN && WITH_BOTAN_BOOST

#endif // BOTAN_BOOST_TLS_H
