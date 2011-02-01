// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __UDPDNS_H
#define __UDPDNS_H 1

#include <config.h>

#include <asio.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <asiolink/asiolink.h>
#include <asiolink/internal/coroutine.h>

// This file contains UDP-specific implementations of generic classes 
// defined in asiolink.h.  It is *not* intended to be part of the public
// API.

namespace asiolink {
/// \brief The \c UDPEndpoint class is a concrete derived class of
/// \c IOEndpoint that represents an endpoint of a UDP packet.
///
/// Other notes about \c TCPEndpoint applies to this class, too.
class UDPEndpoint : public IOEndpoint {
public:
    ///
    /// \name Constructors and Destructor.
    ///
    //@{
    /// \brief Constructor from a pair of address and port.
    ///
    /// \param address The IP address of the endpoint.
    /// \param port The UDP port number of the endpoint.
    UDPEndpoint(const IOAddress& address, const unsigned short port) :
        asio_endpoint_placeholder_(
            new asio::ip::udp::endpoint(asio::ip::address::from_string(address.toText()),
                              port)),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}

    /// \brief Constructor from an ASIO UDP endpoint.
    ///
    /// This constructor is designed to be an efficient wrapper for the
    /// corresponding ASIO class, \c udp::endpoint.
    ///
    /// \param asio_endpoint The ASIO representation of the UDP endpoint.
    UDPEndpoint(const asio::ip::udp::endpoint& asio_endpoint) :
        asio_endpoint_placeholder_(NULL), asio_endpoint_(asio_endpoint)
    {}

    /// \brief The destructor.
    ~UDPEndpoint() { delete asio_endpoint_placeholder_; }
    //@}

    inline IOAddress getAddress() const {
        return (asio_endpoint_.address());
    }

    inline uint16_t getPort() const {
        return (asio_endpoint_.port());
    }

    inline short getProtocol() const {
        return (asio_endpoint_.protocol().protocol());
    }

    inline short getFamily() const {
        return (asio_endpoint_.protocol().family());
    }

    // This is not part of the exosed IOEndpoint API but allows
    // direct access to the ASIO implementation of the endpoint
    inline const asio::ip::udp::endpoint& getASIOEndpoint() const {
        return (asio_endpoint_);
    }

private:
    const asio::ip::udp::endpoint* asio_endpoint_placeholder_;
    const asio::ip::udp::endpoint& asio_endpoint_;
};

/// \brief The \c UDPSocket class is a concrete derived class of
/// \c IOSocket that represents a UDP socket.
///
/// Other notes about \c TCPSocket applies to this class, too.
class UDPSocket : public IOSocket {
private:
    UDPSocket(const UDPSocket& source);
    UDPSocket& operator=(const UDPSocket& source);
public:
    /// \brief Constructor from an ASIO UDP socket.
    ///
    /// \param socket The ASIO representation of the UDP socket.
    UDPSocket(asio::ip::udp::socket& socket) : socket_(socket) {}

    virtual int getNative() const { return (socket_.native()); }
    virtual int getProtocol() const { return (IPPROTO_UDP); }

private:
    asio::ip::udp::socket& socket_;
};

//
// Asynchronous UDP server coroutine
//
///
/// \brief This class implements the coroutine to handle UDP
///        DNS query event. As such, it is both a \c DNSServer and
///        a \c coroutine
///
class UDPServer : public virtual DNSServer, public virtual coroutine {
public:
    /// \brief Constructor
    /// \param io_service the asio::io_service to work with
    /// \param addr the IP address to listen for queries on
    /// \param port the port to listen for queries on
    /// \param checkin the callbackprovider for non-DNS events
    /// \param lookup the callbackprovider for DNS lookup events
    /// \param answer the callbackprovider for DNS answer events
    explicit UDPServer(asio::io_service& io_service,
                       const asio::ip::address& addr, const uint16_t port,
                       SimpleCallback* checkin = NULL,
                       DNSLookup* lookup = NULL,
                       DNSAnswer* answer = NULL);

    /// \brief The function operator
    void operator()(asio::error_code ec = asio::error_code(),
                    size_t length = 0);

    /// \brief Calls the lookup callback
    void asyncLookup();

    /// \brief Resume operation
    ///
    /// \param done Set this to true if the lookup action is done and
    ///        we have an answer
    void resume(const bool done);

    /// \brief Check if we have an answer
    ///
    /// \return true if we have an answer
    bool hasAnswer();

    /// \brief Returns the coroutine state value
    ///
    /// \return the coroutine state value
    int value() { return (get_value()); }

    /// \brief Clones the object
    ///
    /// \return a newly allocated copy of this object
    DNSServer* clone() {
        UDPServer* s = new UDPServer(*this);
        return (s);
    }

private:
    enum { MAX_LENGTH = 4096 };

    /**
     * \brief Internal state and data.
     *
     * We use the pimple design pattern, but not because we need to hide
     * internal data. This class and whole header is for private use anyway.
     * It turned out that UDPServer is copied a lot, because it is a coroutine.
     * This way the overhead of copying is lower, we copy only one shared
     * pointer instead of about 10 of them.
     */
    class Data;
    boost::shared_ptr<Data> data_;
};

//
// Asynchronous UDP coroutine for upstream queries
//
class UDPQuery : public coroutine {
public:
    // TODO Maybe this should be more generic than just for UDPQuery?
    ///
    /// \brief Result of the query
    ///
    /// This is related only to contacting the remote server. If the answer
    ///indicates error, it is still counted as SUCCESS here, if it comes back.
    ///
    enum Result {
        SUCCESS,
        TIME_OUT,
        STOPPED
    };
    /// Abstract callback for the UDPQuery.
    class Callback {
    public:
        virtual ~Callback() {}

        /// This will be called when the UDPQuery is completed
        virtual void operator()(Result result) = 0;
    };
    ///
    /// \brief Constructor.
    ///
    /// It creates the query.
    /// @param callback will be called when we terminate. It is your task to
    ///        delete it if allocated on heap.
    ///@param timeout in ms.
    ///
    explicit UDPQuery(asio::io_service& io_service,
                      const isc::dns::Question& q,
                      const IOAddress& addr, uint16_t port,
                      isc::dns::OutputBufferPtr buffer,
                      Callback* callback, int timeout = -1);
    void operator()(asio::error_code ec = asio::error_code(),
                    size_t length = 0);
    /// Terminate the query.
    void stop(Result reason = STOPPED);
private:
    enum { MAX_LENGTH = 4096 };

    ///
    /// \short Private data
    ///
    /// They are not private because of stability of the
    /// interface (this is private class anyway), but because this class
    /// will be copyed often (it is used as a coroutine and passed as callback
    /// to many async_*() functions) and we want keep the same data. Some of
    /// the data is not copyable too.
    ///
    struct PrivateData;
    boost::shared_ptr<PrivateData> data_;
};
}


#endif // __UDPDNS_H

// Local Variables: 
// mode: c++
// End: 
