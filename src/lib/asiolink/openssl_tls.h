// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Do not include this header directly: use crypto_tls.h instead.

#ifndef OPENSSL_TLS_H
#define OPENSSL_TLS_H

/// @file openssl_tls.h OpenSSL implementation of the TLS API.

#ifdef WITH_OPENSSL

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_asio_socket.h>
#include <asiolink/io_service.h>
#include <asiolink/common_tls.h>

#include <boost/asio/ssl.hpp>

namespace isc {
namespace asiolink {

/// @brief Translate TLS role into implementation.
inline boost::asio::ssl::stream_base::handshake_type roleToImpl(TlsRole role) {
    if (role == TlsRole::SERVER) {
        return (boost::asio::ssl::stream_base::server);
    } else {
        return (boost::asio::ssl::stream_base::client);
    }
}

/// @brief OpenSSL TLS context.
class TlsContext : public TlsContextBase {
public:

    /// @brief Destructor.
    virtual ~TlsContext() { }

    /// @brief Create a fresh context.
    ///
    /// @param role The TLS role client or server.
    explicit TlsContext(TlsRole role);

    /// @brief Return a reference to the underlying context.
    boost::asio::ssl::context& getContext();

    /// @brief Return the pointer to the SSL_CTX object.
    ///
    /// Currently used only for tests. Please note that since OpenSSL 1.1
    /// The SSL_CTX type is not fully publicly defined.
    ::SSL_CTX* getNativeContext();

    /// @brief Get the peer certificate requirement mode.
    ///
    /// @return True if peer certificates are required, false if they
    /// are optional.
    virtual bool getCertRequired() const;

    /// @brief Get the error message.
    ///
    /// @note Wrapper against OpenSSL 3.x not returning error messages
    /// from system errors.
    ///
    /// @param ec The Boost error code.
    /// @return The error message.
    static std::string getErrMsg(boost::system::error_code ec);

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

    /// @brief Cached cert_required value.
    bool cert_required_;

    /// @brief Boost ASIO SSL object.
    boost::asio::ssl::context context_;

    /// @brief Allow access to protected methods by the base class.
    friend class TlsContextBase;
};

/// @brief The type of underlying TLS streams.
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> TlsStreamImpl;

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

/// @brief OpenSSL TLS stream.
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
    virtual std::string getSubject() {
        ::X509* cert = ::SSL_get_peer_certificate(this->native_handle());
        if (!cert) {
            return ("");
        }
        ::X509_NAME *name = ::X509_get_subject_name(cert);
        int loc = ::X509_NAME_get_index_by_NID(name, NID_commonName, -1);
        ::X509_NAME_ENTRY* ne = ::X509_NAME_get_entry(name, loc);
        if (!ne) {
            ::X509_free(cert);
            return ("");
        }
        unsigned char* buf = 0;
        int len = ::ASN1_STRING_to_UTF8(&buf, ::X509_NAME_ENTRY_get_data(ne));
        if (len < 0) {
            ::X509_free(cert);
            return ("");
        }
        std::string ret(reinterpret_cast<char*>(buf), static_cast<size_t>(len));
        ::OPENSSL_free(buf);
        ::X509_free(cert);
        return (ret);
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
    virtual std::string getIssuer() {
        ::X509* cert = ::SSL_get_peer_certificate(this->native_handle());
        if (!cert) {
            return ("");
        }
        ::X509_NAME *name = ::X509_get_issuer_name(cert);
        int loc = ::X509_NAME_get_index_by_NID(name, NID_commonName, -1);
        ::X509_NAME_ENTRY* ne = ::X509_NAME_get_entry(name, loc);
        if (!ne) {
            ::X509_free(cert);
            return ("");
        }
        unsigned char* buf = 0;
        int len = ::ASN1_STRING_to_UTF8(&buf, ::X509_NAME_ENTRY_get_data(ne));
        if (len < 0) {
            ::X509_free(cert);
            return ("");
        }
        std::string ret(reinterpret_cast<char*>(buf), static_cast<size_t>(len));
        ::OPENSSL_free(buf);
        ::X509_free(cert);
        return (ret);
    }
};

// Stream truncated error code.
#ifdef HAVE_STREAM_TRUNCATED_ERROR
const int STREAM_TRUNCATED = boost::asio::ssl::error::stream_truncated;
#else
const int STREAM_TRUNCATED = ERR_PACK(ERR_LIB_SSL, 0, SSL_R_SHORT_READ);
#endif

} // namespace asiolink
} // namespace isc

#endif // WITH_OPENSSL

#endif // OPENSSL_TLS_H
