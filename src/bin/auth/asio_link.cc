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

// $Id$

#include <config.h>

#include <unistd.h>             // for some IPC/network system calls
#include <sys/socket.h>
#include <netinet/in.h>

#include <asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include <boost/shared_ptr.hpp>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <asio_link.h>

#include <auth/auth_srv.h>
#include <auth/common.h>

using namespace asio;
using asio::ip::udp;
using asio::ip::tcp;

using namespace std;
using namespace isc::dns;

namespace asio_link {
IOAddress::IOAddress(const string& address_str)
    // XXX: we cannot simply construct the address in the initialization list
    // because we'd like to throw our own exception on failure.
{
    error_code err;
    asio_address_ = ip::address::from_string(address_str, err);
    if (err) {
        isc_throw(IOError, "Failed to convert string to address '"
                  << address_str << "': " << err.message());
    }
}

IOAddress::IOAddress(const ip::address& asio_address) :
    asio_address_(asio_address)
{}

string
IOAddress::toText() const {
    return (asio_address_.to_string());
}

/// \brief The \c TCPEndpoint class is a concrete derived class of
/// \c IOEndpoint that represents an endpoint of a TCP connection.
///
/// In the current implementation, an object of this class is always
/// instantiated within the wrapper routines.  Applications are expected to
/// get access to the object via the abstract base class, \c IOEndpoint.
/// This design may be changed when we generalize the wrapper interface.
///
/// Note: this implementation is optimized for the case where this object
/// is created from an ASIO endpoint object in a receiving code path
/// by avoiding to make a copy of the base endpoint.  For TCP it may not be
/// a big deal, but when we receive UDP packets at a high rate, the copy
/// overhead might be significant.
class TCPEndpoint : public IOEndpoint {
public:
    ///
    /// \name Constructors and Destructor
    ///
    //@{
    /// \brief Constructor from a pair of address and port.
    ///
    /// \param address The IP address of the endpoint.
    /// \param port The TCP port number of the endpoint.
    TCPEndpoint(const IOAddress& address, const unsigned short port) :
        asio_endpoint_placeholder_(
            new tcp::endpoint(ip::address::from_string(address.toText()),
                              port)),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}

    /// \brief Constructor from an ASIO TCP endpoint.
    ///
    /// This constructor is designed to be an efficient wrapper for the
    /// corresponding ASIO class, \c tcp::endpoint.
    ///
    /// \param asio_endpoint The ASIO representation of the TCP endpoint.
    TCPEndpoint(const tcp::endpoint& asio_endpoint) :
        asio_endpoint_placeholder_(NULL), asio_endpoint_(asio_endpoint)
    {}

    /// \brief The destructor.        
    ~TCPEndpoint() { delete asio_endpoint_placeholder_; }
    //@}

    virtual IOAddress getAddress() const {
        return (asio_endpoint_.address());
    }
private:
    const tcp::endpoint* asio_endpoint_placeholder_;
    const tcp::endpoint& asio_endpoint_;
};

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
            new udp::endpoint(ip::address::from_string(address.toText()),
                              port)),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}

    /// \brief Constructor from an ASIO UDP endpoint.
    ///
    /// This constructor is designed to be an efficient wrapper for the
    /// corresponding ASIO class, \c udp::endpoint.
    ///
    /// \param asio_endpoint The ASIO representation of the UDP endpoint.
    UDPEndpoint(const udp::endpoint& asio_endpoint) :
        asio_endpoint_placeholder_(NULL), asio_endpoint_(asio_endpoint)
    {}

    /// \brief The destructor.
    ~UDPEndpoint() { delete asio_endpoint_placeholder_; }
    //@}

    virtual IOAddress getAddress() const {
        return (asio_endpoint_.address());
    }
private:
    const udp::endpoint* asio_endpoint_placeholder_;
    const udp::endpoint& asio_endpoint_;
};

const IOEndpoint*
IOEndpoint::create(const int protocol, const IOAddress& address,
                   const unsigned short port)
{
    if (protocol == IPPROTO_UDP) {
        return (new UDPEndpoint(address, port));
    } else if (protocol == IPPROTO_TCP) {
        return (new TCPEndpoint(address, port));
    }
    isc_throw(IOError,
              "IOEndpoint creation attempt for unsupported protocol: " <<
              protocol);
}

/// \brief The \c TCPSocket class is a concrete derived class of
/// \c IOSocket that represents a TCP socket.
///
/// In the current implementation, an object of this class is always
/// instantiated within the wrapper routines.  Applications are expected to
/// get access to the object via the abstract base class, \c IOSocket.
/// This design may be changed when we generalize the wrapper interface.
class TCPSocket : public IOSocket {
private:
    TCPSocket(const TCPSocket& source);
    TCPSocket& operator=(const TCPSocket& source);
public:
    /// \brief Constructor from an ASIO TCP socket.
    ///
    /// \param socket The ASIO representation of the TCP socket.
    TCPSocket(tcp::socket& socket) : socket_(socket) {}

    virtual int getNative() const { return (socket_.native()); }
    virtual int getProtocol() const { return (IPPROTO_TCP); }
private:
    tcp::socket& socket_;
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
    UDPSocket(udp::socket& socket) : socket_(socket) {}

    virtual int getNative() const { return (socket_.native()); }
    virtual int getProtocol() const { return (IPPROTO_UDP); }
private:
    udp::socket& socket_;
};

/// \brief The \c DummySocket class is a concrete derived class of
/// \c IOSocket that is not associated with any real socket.
///
/// This main purpose of this class is tests, where it may be desirable to
/// instantiate an \c IOSocket object without involving system resource
/// allocation such as real network sockets.
class DummySocket : public IOSocket {
private:
    DummySocket(const DummySocket& source);
    DummySocket& operator=(const DummySocket& source);
public:
    /// \brief Constructor from the protocol number.
    ///
    /// The protocol must validly identify a standard network protocol.
    /// For example, to specify TCP \c protocol must be \c IPPROTO_TCP.
    ///
    /// \param protocol The network protocol number for the socket.
    DummySocket(const int protocol) : protocol_(protocol) {}

    /// \brief A dummy derived method of \c IOSocket::getNative().
    ///
    /// This version of method always returns -1 as the object is not
    /// associated with a real (native) socket.
    virtual int getNative() const { return (-1); }

    virtual int getProtocol() const { return (protocol_); }
private:
    const int protocol_;
};

IOSocket&
IOSocket::getDummyUDPSocket() {
    static DummySocket socket(IPPROTO_UDP);
    return (socket);
}

IOSocket&
IOSocket::getDummyTCPSocket() {
    static DummySocket socket(IPPROTO_TCP);
    return (socket);
}

IOMessage::IOMessage(const void* data, const size_t data_size,
                     IOSocket& io_socket, const IOEndpoint& remote_endpoint) :
    data_(data), data_size_(data_size), io_socket_(io_socket),
    remote_endpoint_(remote_endpoint)
{}

//
// Helper classes for asynchronous I/O using asio
//
class TCPClient {
public:
    TCPClient(AuthSrv* auth_server, io_service& io_service) :
        auth_server_(auth_server),
        socket_(io_service),
        io_socket_(socket_),
        response_buffer_(0),
        responselen_buffer_(TCP_MESSAGE_LENGTHSIZE),
        response_renderer_(response_buffer_),
        dns_message_(Message::PARSE),
        custom_callback_(NULL)
    {}

    void start() {
        // Check for queued configuration commands
        if (auth_server_ != NULL &&
            auth_server_->getConfigSession()->hasQueuedMsgs()) {
            auth_server_->getConfigSession()->checkCommand();
        }
        async_read(socket_, asio::buffer(data_, TCP_MESSAGE_LENGTHSIZE),
                   boost::bind(&TCPClient::headerRead, this,
                               placeholders::error,
                               placeholders::bytes_transferred));
    }

    tcp::socket& getSocket() { return (socket_); }

    void headerRead(const asio::error_code& error,
                    size_t bytes_transferred)
    {
        if (!error) {
            InputBuffer dnsbuffer(data_, bytes_transferred);

            uint16_t msglen = dnsbuffer.readUint16();
            async_read(socket_, asio::buffer(data_, msglen),
                       boost::bind(&TCPClient::requestRead, this,
                                   placeholders::error,
                                   placeholders::bytes_transferred));
        } else {
            delete this;
        }
    }

    void requestRead(const asio::error_code& error,
                     size_t bytes_transferred)
    {
        if (!error) {
            const TCPEndpoint remote_endpoint(socket_.remote_endpoint());
            const IOMessage io_message(data_, bytes_transferred, io_socket_,
                                       remote_endpoint);
            // currently, for testing purpose only
            if (custom_callback_ != NULL) {
                (*custom_callback_)(io_message);
                start();
                return;
            }

            if (auth_server_->processMessage(io_message, dns_message_,
                                             response_renderer_)) {
                responselen_buffer_.writeUint16(
                    response_buffer_.getLength());
                async_write(socket_,
                            asio::buffer(
                                responselen_buffer_.getData(),
                                responselen_buffer_.getLength()),
                            boost::bind(&TCPClient::responseWrite, this,
                                        placeholders::error));
            } else {
                delete this;
            }
        } else {
            delete this;
        }
    }

    void responseWrite(const asio::error_code& error) {
        if (!error) {
                async_write(socket_,
                            asio::buffer(response_buffer_.getData(),
                                         response_buffer_.getLength()),
                            boost::bind(&TCPClient::handleWrite, this,
                                        placeholders::error));
        } else {
            delete this;
        }
    }

    void handleWrite(const asio::error_code& error) {
        if (!error) {
            start();            // handle next request, if any.
      } else {
            delete this;
      }
    }

    // Currently this is for tests only
    void setCallBack(const IOService::IOCallBack* callback) {
        custom_callback_ = callback;
    }

private:
    AuthSrv* auth_server_;
    tcp::socket socket_;
    TCPSocket io_socket_;
    OutputBuffer response_buffer_;
    OutputBuffer responselen_buffer_;
    MessageRenderer response_renderer_;
    Message dns_message_;
    enum { MAX_LENGTH = 65535 };
    static const size_t TCP_MESSAGE_LENGTHSIZE = 2;
    char data_[MAX_LENGTH];

    // currently, for testing purpose only.
    const IOService::IOCallBack* custom_callback_;
};

class TCPServer {
public:
    TCPServer(AuthSrv* auth_server, io_service& io_service,
              const ip::address& addr, const uint16_t port) :
        auth_server_(auth_server), io_service_(io_service),
        acceptor_(io_service_), listening_(new TCPClient(auth_server_,
                                                         io_service_)),
        custom_callback_(NULL)
    {
        tcp::endpoint endpoint(addr, port);
        acceptor_.open(endpoint.protocol());
        // Set v6-only (we use a different instantiation for v4,
        // otherwise asio will bind to both v4 and v6
        if (addr.is_v6()) {
            acceptor_.set_option(ip::v6_only(true));
        }
        acceptor_.set_option(tcp::acceptor::reuse_address(true));
        acceptor_.bind(endpoint);
        acceptor_.listen();
        acceptor_.async_accept(listening_->getSocket(),
                               boost::bind(&TCPServer::handleAccept, this,
                                           listening_, placeholders::error));
    }

    ~TCPServer() { delete listening_; }

    void handleAccept(TCPClient* new_client,
                      const asio::error_code& error)
    {
        if (!error) {
            assert(new_client == listening_);
            new_client->setCallBack(custom_callback_);
            new_client->start();
            listening_ = new TCPClient(auth_server_, io_service_);
            acceptor_.async_accept(listening_->getSocket(),
                                   boost::bind(&TCPServer::handleAccept,
                                               this, listening_,
                                               placeholders::error));
        } else {
            delete new_client;
        }
    }

    // Currently this is for tests only
    void setCallBack(const IOService::IOCallBack* callback) {
        custom_callback_ = callback;
    }

private:
    AuthSrv* auth_server_;
    io_service& io_service_;
    tcp::acceptor acceptor_;
    TCPClient* listening_;

    // currently, for testing purpose only.
    const IOService::IOCallBack* custom_callback_;
};

class UDPServer {
public:
    UDPServer(AuthSrv* auth_server, io_service& io_service,
              const ip::address& addr, const uint16_t port) :
        auth_server_(auth_server),
        io_service_(io_service),
        socket_(io_service, addr.is_v6() ? udp::v6() : udp::v4()),
        io_socket_(socket_),
        response_buffer_(0),
        response_renderer_(response_buffer_),
        dns_message_(Message::PARSE),
        custom_callback_(NULL)
    {
        socket_.set_option(socket_base::reuse_address(true));
        // Set v6-only (we use a different instantiation for v4,
        // otherwise asio will bind to both v4 and v6
        if (addr.is_v6()) {
            socket_.set_option(asio::ip::v6_only(true));
            socket_.bind(udp::endpoint(addr, port));
        } else {
            socket_.bind(udp::endpoint(addr, port));
        }
        startReceive();
    }

    void handleRequest(const asio::error_code& error,
                       size_t bytes_recvd)
    {
        // Check for queued configuration commands
        if (auth_server_ != NULL &&
            auth_server_->getConfigSession()->hasQueuedMsgs()) {
            auth_server_->getConfigSession()->checkCommand();
        }
        if (!error && bytes_recvd > 0) {
            const UDPEndpoint remote_endpoint(sender_endpoint_);
            const IOMessage io_message(data_, bytes_recvd, io_socket_,
                                       remote_endpoint);
            // currently, for testing purpose only
            if (custom_callback_ != NULL) {
                (*custom_callback_)(io_message);
                startReceive();
                return;
            }

            dns_message_.clear(Message::PARSE);
            response_renderer_.clear();
            if (auth_server_->processMessage(io_message, dns_message_,
                                             response_renderer_)) {
                socket_.async_send_to(
                    asio::buffer(response_buffer_.getData(),
                                        response_buffer_.getLength()),
                    sender_endpoint_,
                    boost::bind(&UDPServer::sendCompleted,
                                this,
                                placeholders::error,
                                placeholders::bytes_transferred));
            } else {
                startReceive();
            }
        } else {
            startReceive();
        }
    }

    void sendCompleted(const asio::error_code&, size_t) {
        // Even if error occurred there's nothing to do.  Simply handle
        // the next request.
        startReceive();
    }

    // Currently this is for tests only
    void setCallBack(const IOService::IOCallBack* callback) {
        custom_callback_ = callback;
    }
private:
    void startReceive() {
        socket_.async_receive_from(
            asio::buffer(data_, MAX_LENGTH), sender_endpoint_,
            boost::bind(&UDPServer::handleRequest, this,
                        placeholders::error,
                        placeholders::bytes_transferred));
    }

private:
    AuthSrv* auth_server_;
    io_service& io_service_;
    udp::socket socket_;
    UDPSocket io_socket_;
    OutputBuffer response_buffer_;
    MessageRenderer response_renderer_;
    Message dns_message_;
    udp::endpoint sender_endpoint_;
    enum { MAX_LENGTH = 4096 };
    char data_[MAX_LENGTH];

    // currently, for testing purpose only.
    const IOService::IOCallBack* custom_callback_;
};

class IOServiceImpl {
public:
    IOServiceImpl(AuthSrv* auth_server, const char& port,
                  const ip::address* v4addr, const ip::address* v6addr);
    asio::io_service io_service_;
    AuthSrv* auth_server_;

    typedef boost::shared_ptr<UDPServer> UDPServerPtr;
    typedef boost::shared_ptr<TCPServer> TCPServerPtr;
    UDPServerPtr udp4_server_;
    UDPServerPtr udp6_server_;
    TCPServerPtr tcp4_server_;
    TCPServerPtr tcp6_server_;

    // This member is used only for testing at the moment.
    IOService::IOCallBack callback_;
};

IOServiceImpl::IOServiceImpl(AuthSrv* auth_server, const char& port,
                             const ip::address* const v4addr,
                             const ip::address* const v6addr) :
    auth_server_(auth_server),
    udp4_server_(UDPServerPtr()), udp6_server_(UDPServerPtr()),
    tcp4_server_(TCPServerPtr()), tcp6_server_(TCPServerPtr())
{
    uint16_t portnum;

    try {
        // XXX: SunStudio with stlport4 doesn't reject some invalid
        // representation such as "-1" by lexical_cast<uint16_t>, so
        // we convert it into a signed integer of a larger size and perform
        // range check ourselves.
        const int32_t portnum32 = boost::lexical_cast<int32_t>(&port);
        if (portnum32 < 0 || portnum32 > 65535) {
            isc_throw(IOError, "Invalid port number '" << &port);
        }
        portnum = portnum32;
    } catch (const boost::bad_lexical_cast& ex) {
        isc_throw(IOError, "Invalid port number '" << &port << "': " <<
                  ex.what());
    }

    try {
        if (v4addr != NULL) {
            udp4_server_ = UDPServerPtr(new UDPServer(auth_server, io_service_,
                                                      *v4addr, portnum));
            tcp4_server_ = TCPServerPtr(new TCPServer(auth_server, io_service_,
                                                      *v4addr, portnum));
        }
        if (v6addr != NULL) {
            udp6_server_ = UDPServerPtr(new UDPServer(auth_server, io_service_,
                                                      *v6addr, portnum));
            tcp6_server_ = TCPServerPtr(new TCPServer(auth_server, io_service_,
                                                      *v6addr, portnum));
        }
    } catch (const asio::system_error& err) {
        // We need to catch and convert any ASIO level exceptions.
        // This can happen for unavailable address, binding a privilege port
        // without the privilege, etc.
        isc_throw(IOError, "Failed to initialize network servers: " <<
                  err.what());
    }
}

IOService::IOService(AuthSrv* auth_server, const char& port,
                     const char& address) :
    impl_(NULL)
{
    error_code err;
    const ip::address addr = ip::address::from_string(&address, err);
    if (err) {
        isc_throw(IOError, "Invalid IP address '" << &address << "': "
                  << err.message());
    }

    impl_ = new IOServiceImpl(auth_server, port,
                              addr.is_v4() ? &addr : NULL,
                              addr.is_v6() ? &addr : NULL);
}

IOService::IOService(AuthSrv* auth_server, const char& port,
                     const bool use_ipv4, const bool use_ipv6) :
    impl_(NULL)
{
    const ip::address v4addr_any = ip::address(ip::address_v4::any());
    const ip::address* const v4addrp = use_ipv4 ? &v4addr_any : NULL; 
    const ip::address v6addr_any = ip::address(ip::address_v6::any());
    const ip::address* const v6addrp = use_ipv6 ? &v6addr_any : NULL;
    impl_ = new IOServiceImpl(auth_server, port, v4addrp, v6addrp);
}

IOService::~IOService() {
    delete impl_;
}

void
IOService::run() {
    impl_->io_service_.run();
}

void
IOService::stop() {
    impl_->io_service_.stop();
}

asio::io_service&
IOService::get_io_service() {
    return (impl_->io_service_);
}

void
IOService::setCallBack(const IOCallBack callback) {
    impl_->callback_ = callback;
    if (impl_->udp4_server_ != NULL) {
        impl_->udp4_server_->setCallBack(&impl_->callback_);
    }
    if (impl_->udp6_server_ != NULL) {
        impl_->udp6_server_->setCallBack(&impl_->callback_);
    }
    if (impl_->tcp4_server_ != NULL) {
        impl_->tcp4_server_->setCallBack(&impl_->callback_);
    }
    if (impl_->tcp6_server_ != NULL) {
        impl_->tcp6_server_->setCallBack(&impl_->callback_);
    }
}

class IntervalTimerImpl {
private:
    // prohibit copy
    IntervalTimerImpl(const IntervalTimerImpl& source);
    IntervalTimerImpl& operator=(const IntervalTimerImpl& source);
public:
    IntervalTimerImpl(IOService& io_service);
    ~IntervalTimerImpl();
    void setupTimer(const IntervalTimer::Callback& cbfunc,
                    const uint32_t interval);
    void callback(const asio::error_code& error);
private:
    // a function to update timer_ when it expires
    void updateTimer();
    // a function to call back when timer_ expires
    IntervalTimer::Callback cbfunc_;
    // interval in seconds
    uint32_t interval_;
    // asio timer
    asio::deadline_timer timer_;
};

IntervalTimerImpl::IntervalTimerImpl(IOService& io_service) :
    timer_(io_service.get_io_service())
{}

IntervalTimerImpl::~IntervalTimerImpl()
{}

void
IntervalTimerImpl::setupTimer(const IntervalTimer::Callback& cbfunc,
                              const uint32_t interval)
{
    // Interval should not be 0.
    if (interval == 0) {
        isc_throw(isc::BadValue, "Interval should not be 0");
    }
    // Call back function should not be empty.
    if (cbfunc.empty()) {
        isc_throw(isc::InvalidParameter, "Callback function is empty");
    }
    cbfunc_ = cbfunc;
    interval_ = interval;
    // Set initial expire time.
    // At this point the timer is not running yet and will not expire.
    // After calling IOService::run(), the timer will expire.
    updateTimer();
    return;
}

void
IntervalTimerImpl::updateTimer() {
    // Update expire time to (current time + interval_).
    timer_.expires_from_now(boost::posix_time::seconds(interval_));
    // Reset timer.
    timer_.async_wait(boost::bind(&IntervalTimerImpl::callback, this, _1));
}

void
IntervalTimerImpl::callback(const asio::error_code& cancelled) {
    // Do not call cbfunc_ in case the timer was cancelled.
    // The timer will be canelled in the destructor of asio::deadline_timer.
    if (!cancelled) {
        cbfunc_();
        // Set next expire time.
        updateTimer();
    }
}

IntervalTimer::IntervalTimer(IOService& io_service) {
    impl_ = new IntervalTimerImpl(io_service);
}

IntervalTimer::~IntervalTimer() {
    delete impl_;
}

void
IntervalTimer::setupTimer(const Callback& cbfunc, const uint32_t interval) {
    return (impl_->setupTimer(cbfunc, interval));
}
}
