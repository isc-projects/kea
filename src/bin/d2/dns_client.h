// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef DNS_CLIENT_H
#define DNS_CLIENT_H

#include <d2/d2_update_message.h>

#include <asiolink/io_service.h>
#include <util/buffer.h>

#include <asiodns/io_fetch.h>

namespace isc {
namespace d2 {

class DNSClient;
typedef boost::shared_ptr<DNSClient> DNSClientPtr;

/// DNSClient class implementation.
class DNSClientImpl;

/// @brief The @c DNSClient class handles communication with the DNS server.
///
/// Communication with the DNS server is asynchronous. Caller must provide a
/// callback, which will be invoked when the response from the DNS server is
/// received, a timeout has occured or IO service has been stopped for any
/// reason. The caller-supplied callback is called by the internal callback
/// operator implemented by @c DNSClient. This callback is responsible for
/// initializing the @c D2UpdateMessage instance which encapsulates the response
/// from the DNS. This initialization does not take place if the response from
/// DNS is not received.
///
/// Caller must supply a pointer to the @c D2UpdateMessage object, which will
/// encapsulate DNS response, through class constructor. An exception will be
/// thrown if the pointer is not initialized by the caller.
class DNSClient {
public:

    /// @brief A status code of the DNSClient.
    enum Status {
        SUCCESS,           ///< Response received and is ok.
        TIMEOUT,           ///< No response, timeout.
        IO_STOPPED,        ///< IO was stopped.
        INVALID_RESPONSE,  ///< Response received but invalid.
        OTHER              ///< Other, unclassified error.
    };

    /// @brief Callback for the @c DNSClient class.
    ///
    /// This is is abstract class which represents the external callback for the
    /// @c DNSClient. Caller must implement this class and supply its instance
    /// in the @c DNSClient constructor to get callbacks when the DNS Update
    /// exchange is complete (@see @c DNSClient).
    class Callback {
    public:
        /// @brief Virtual destructor.
        virtual ~Callback() { }

        /// @brief Function operator implementing a callback.
        ///
        /// @param result an @c asiodns::IOFetch::Result object representing
        /// IO status code.
        virtual void operator()(DNSClient::Status status) = 0;
    };

    /// @brief Constructor.
    ///
    /// @param response_placeholder Pointer to an object which will hold a
    /// DNS server's response. Caller is responsible for allocating this object.
    /// @param callback Pointer to an object implementing @c DNSClient::Callback
    /// class. This object will be called when DNS message exchange completes or
    /// if an error occurs. NULL value disables callback invocation.
    DNSClient(D2UpdateMessagePtr& response_placeholder, Callback* callback);

    /// @brief Virtual destructor, does nothing.
    ~DNSClient();

    ///
    /// @name Copy constructor and assignment operator
    ///
    /// Copy constructor and assignment operator are private because
    /// @c DNSClient is a singleton class and its instance should not be copied.
    //@{
private:
    DNSClient(const DNSClient& source);
    DNSClient& operator=(const DNSClient& source);
    //@}

public:
    /// @brief Start asynchronous DNS Update.
    ///
    /// This function starts asynchronous DNS Update and returns. The DNS Update
    /// will be executed by the specified IO service. Once the message exchange
    /// with a DNS server is complete, timeout occurs or IO operation is
    /// interrupted, the caller-supplied callback function will be invoked.
    ///
    /// An address and port of the DNS server is specified through the function
    /// arguments so as the same instance of the @c DNSClient can be used to
    /// initiate multiple message exchanges.
    ///
    /// @param io_service IO service to be used to run the message exchange.
    /// @param ns_addr DNS server address.
    /// @param ns_port DNS server port.
    /// @param update A DNS Update message to be sent to the server.
    /// @param wait A timeout (in seconds) for the response. If a response is
    /// not received within the timeout, exchange is interrupted. A negative
    /// value disables timeout.
    void doUpdate(asiolink::IOService& io_service,
                  const asiolink::IOAddress& ns_addr,
                  const uint16_t ns_port,
                  D2UpdateMessage& update,
                  const int wait = -1);

private:
    DNSClientImpl* impl_;  ///< Pointer to DNSClient implementation.
};

} // namespace d2
} // namespace isc

#endif // DNS_CLIENT_H
