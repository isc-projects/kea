// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TKEY_EXCHANGE_H
#define TKEY_EXCHANGE_H

#include <asiodns/io_fetch.h>
#include <asiolink/io_service.h>
#include <gss_tsig_cfg.h>
#include <gss_tsig_key.h>
#include <util/buffer.h>
#include <memory>

namespace isc {
namespace gss_tsig {

class TKeyExchange;
typedef boost::shared_ptr<TKeyExchange> TKeyExchangePtr;

/// GssTKeyExchange class implementation.
class TKeyExchangeImpl;

/// @brief The @c TKeyExchange class handles communication with the DNS server.
///
/// Communication with the DNS server is asynchronous. Caller must provide a
/// callback, which will be invoked when the response from the DNS server is
/// received, a timeout has occurred or IO service has been stopped for any
/// reason. The caller-supplied callback is called by the internal callback
/// operator implemented by @c TKeyExchange. This callback is responsible for
/// initializing the @c GssTsigContext instance which encapsulates the response
/// from the DNS. This initialization does not take place if the response from
/// DNS is not received.
class TKeyExchange : boost::noncopyable {
public:
    /// @brief A status code of the TKeyExchange.
    enum Status {
        SUCCESS,           ///< Response received and is ok.
        TIMEOUT,           ///< No response, timeout.
        IO_STOPPED,        ///< IO was stopped.
        INVALID_RESPONSE,  ///< Response received but invalid.
        UNSIGNED_RESPONSE, ///< Response received but not signed.
        BAD_CREDENTIALS,   ///< Bad client credentials.
        OTHER              ///< Other, unclassified error.
    };

    /// @brief Convert a status to its textual form.
    static std::string statusToText(Status status);

    /// @brief Callback for the @c TKeyExchange class.
    ///
    /// This is an abstract class which represents the external callback for the
    /// @c TKeyExchange. Caller must implement this class and supply its instance
    /// in the @c TKeyExchange constructor to get callbacks when the TKEY
    /// exchange is complete (@see @c TKeyExchange).
    class Callback {
    public:
        /// @brief Virtual destructor.
        virtual ~Callback() { }

        /// @brief Function operator implementing a callback.
        ///
        /// @param status a @c TKeyExchange::Status enum representing status code
        /// of TKeyExchange operation.
        virtual void operator()(TKeyExchange::Status status) = 0;
    };

    /// @brief Constructor.
    ///
    /// @param io_service The IOService which handles IO operations.
    /// @param server The server for which the TKEY exchange is performed.
    /// @param key The TKEY being updated.
    /// @param callback Pointer to an object implementing
    /// @c TKeyExchange::Callback class. This object will be called when DNS
    /// message exchange completes or if an error occurs. NULL value disables
    /// callback invocation.
    /// @param timeout The timeout for the IO operations.
    /// @param flags The flags used for the TKEY exchange.
    /// @throw BadValue if io_service is null.
    /// @throw BadValue if key's security context has already been used.
    TKeyExchange(const isc::asiolink::IOServicePtr& io_service,
                 const DnsServerPtr& server, const GssTsigKeyPtr& key,
                 Callback* callback, uint32_t timeout = TKEY_EXCHANGE_IO_TIMEOUT,
                 OM_uint32 flags = TKEY_EXCHANGE_FLAGS);

    /// @brief Virtual destructor, does nothing.
    virtual ~TKeyExchange();

    /// @brief This function handles the repeated communication with the DNS
    /// server trying to complete the TKEY exchange.
    void doExchange();

    /// @brief This function cancels the in-flight TKEY exchange.
    void cancel();

    /// @brief Gets IO service.
    ///
    /// @return IOService object, used for all ASIO operations.
    isc::asiolink::IOServicePtr getIOService();

    /// @brief Sets IO service.
    ///
    /// @param io_service IOService object, used for all ASIO operations.
    void setIOService(const isc::asiolink::IOServicePtr io_service);

    /// @brief The default TKEY exchange flags.
    ///
    /// The default flags consist in:
    /// - GSS_C_MUTUAL_FLAG: A flag that requires both of initiator and acceptor
    ///   to be authenticated.
    /// - GSS_C_REPLAY_FLAG: A flag that detects repeated messages.
    /// - GSS_C_INTEG_FLAG: A flag that makes integrity services (that is,
    ///   cryptographic signatures) available for transferred messages.
    /// Note the GSS_C_SEQUENCE_FLAG is not set by default.
    static const OM_uint32 TKEY_EXCHANGE_FLAGS;

    /// @brief The default IO timeout used for IO operations (in milliseconds)
    /// set to 3000 (3 seconds).
    static const uint32_t TKEY_EXCHANGE_IO_TIMEOUT;

private:
    /// @brief Smart pointer to TKeyExchange implementation.
    std::unique_ptr<TKeyExchangeImpl> impl_;
};

} // namespace isc
} // namespace gss_tsig

#endif // TKEY_EXCHANGE_H
