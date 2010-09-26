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

#ifndef __ASIO_LINK_H
#define __ASIO_LINK_H 1

// IMPORTANT NOTE: only very few ASIO headers files can be included in
// this file.  In particular, asio.hpp should never be included here.
// See the description of the namespace below.
#include <unistd.h>             // for some network system calls
#include <asio/ip/address.hpp>

#include <functional>
#include <string>

#include <boost/function.hpp>

#include <exceptions/exceptions.h>

namespace asio {
// forward declaration for IOService::get_io_service() below
class io_service;
}

class AuthSrv;

/// \namespace asio_link
/// \brief A wrapper interface for the ASIO library.
///
/// The \c asio_link namespace is used to define a set of wrapper interfaces
/// for the ASIO library.
///
/// BIND 10 uses the non-Boost version of ASIO because it's header-only,
/// i.e., does not require a separate library object to be linked, and thus
/// lowers the bar for introduction.
///
/// But the advantage comes with its own costs: since the header-only version
/// includes more definitions in public header files, it tends to trigger
/// more compiler warnings for our own sources, and, depending on the
/// compiler options, may make the build fail.
///
/// We also found it may be tricky to use ASIO and standard C++ libraries
/// in a single translation unit, i.e., a .cc file: depending on the order
/// of including header files, ASIO may or may not work on some platforms.
///
/// This wrapper interface is intended to centralize these
/// problematic issues in a single sub module.  Other BIND 10 modules should
/// simply include \c asio_link.h and use the wrapper API instead of
/// including ASIO header files and using ASIO-specific classes directly.
///
/// This wrapper may be used for other IO libraries if and when we want to
/// switch, but generality for that purpose is not the primary goal of
/// this module.  The resulting interfaces are thus straightforward mapping
/// to the ASIO counterparts.
///
/// Notes to developers:
/// Currently the wrapper interface is specific to the authoritative
/// server implementation.  But the plan is to generalize it and have
/// other modules use it.
///
/// One obvious drawback of this approach is performance overhead
/// due to the additional layer.  We should eventually evaluate the cost
/// of the wrapper abstraction in benchmark tests. Another drawback is
/// that the wrapper interfaces don't provide all features of ASIO
/// (at least for the moment).  We should also re-evaluate the
/// maintenance overhead of providing necessary wrappers as we develop
/// more.
///
/// On the other hand, we may be able to exploit the wrapper approach to
/// simplify the interfaces (by limiting the usage) and unify performance
/// optimization points.
///
/// As for optimization, we may want to provide a custom allocator for
/// the placeholder of callback handlers:
/// http://think-async.com/Asio/asio-1.3.1/doc/asio/reference/asio_handler_allocate.html

namespace asio_link {
struct IOServiceImpl;

/// \brief An exception that is thrown if an error occurs within the IO
/// module.  This is mainly intended to be a wrapper exception class for
/// ASIO specific exceptions.
class IOError : public isc::Exception {
public:
    IOError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// \brief The \c IOAddress class represents an IP addresses (version
/// agnostic)
///
/// This class is a wrapper for the ASIO \c ip::address class.
class IOAddress {
public:
    ///
    /// \name Constructors and Destructor
    ///
    /// This class is copyable.  We use default versions of copy constructor
    /// and the assignment operator.
    /// We use the default destructor.
    //@{
    /// \brief Constructor from string.
    ///
    /// This constructor converts a textual representation of IPv4 and IPv6
    /// addresses into an IOAddress object.
    /// If \c address_str is not a valid representation of any type of
    /// address, an exception of class \c IOError will be thrown.
    /// This constructor allocates memory for the object, and if that fails
    /// a corresponding standard exception will be thrown.
    ///
    /// \param address_str Textual representation of address.
    IOAddress(const std::string& address_str);

    /// \brief Constructor from an ASIO \c ip::address object.
    ///
    /// This constructor is intended to be used within the wrapper
    /// implementation; user applications of the wrapper API won't use it.
    ///
    /// This constructor never throws an exception.
    ///
    /// \param asio_address The ASIO \c ip::address to be converted.
    IOAddress(const asio::ip::address& asio_adress);
    //@}

    /// \brief Convert the address to a string.
    ///
    /// This method is basically expected to be exception free, but
    /// generating the string will involve resource allocation,
    /// and if it fails the corresponding standard exception will be thrown.
    ///
    /// \return A string representation of the address.
    std::string toText() const;
private:
    asio::ip::address asio_address_;
};

/// \brief The \c IOEndpoint class is an abstract base class to represent
/// a communication endpoint.
///
/// This class is a wrapper for the ASIO endpoint classes such as
/// \c ip::tcp::endpoint and \c ip::udp::endpoint.
///
/// Derived class implementations are completely hidden within the
/// implementation.  User applications only get access to concrete
/// \c IOEndpoint objects via the abstract interfaces.
class IOEndpoint {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    IOEndpoint(const IOEndpoint& source);
    IOEndpoint& operator=(const IOEndpoint& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class
    /// should never be instantiated (except as part of a derived class).
    IOEndpoint() {}
public:
    /// The destructor.
    virtual ~IOEndpoint() {}
    //@}

    /// \brief Returns the address of the endpoint.
    ///
    /// This method returns an IOAddress object corresponding to \c this
    /// endpoint.
    /// Note that the return value is a real object, not a reference or
    /// a pointer.
    /// This is aligned with the interface of the ASIO counterpart:
    /// the \c address() method of \c ip::xxx::endpoint classes returns
    /// an \c ip::address object.
    /// This also means handling the address of an endpoint using this method
    /// can be expensive.  If the address information is necessary in a
    /// performance sensitive context and there's a more efficient interface
    /// for that purpose, it's probably better to avoid using this method.
    ///
    /// This method never throws an exception.
    ///
    /// \return A copy of \c IOAddress object corresponding to the endpoint.
    virtual IOAddress getAddress() const = 0;

    /// \brief A polymorphic factory of endpoint from address and port.
    ///
    /// This method creates a new instance of (a derived class of)
    /// \c IOEndpoint object that identifies the pair of given address
    /// and port.
    /// The appropriate derived class is chosen based on the specified
    /// transport protocol.  If the \c protocol doesn't specify a protocol
    /// supported in this implementation, an exception of class \c IOError
    /// will be thrown.
    ///
    /// Memory for the created object will be dynamically allocated.  It's
    /// the caller's responsibility to \c delete it later.
    /// If resource allocation for the new object fails, a corresponding
    /// standard exception will be thrown.
    ///
    /// \param protocol The transport protocol used for the endpoint.
    /// Currently, only \c IPPROTO_UDP and \c IPPROTO_TCP can be specified.
    /// \param address The (IP) address of the endpoint.
    /// \param port The transport port number of the endpoint
    /// \return A pointer to a newly created \c IOEndpoint object.
    static const IOEndpoint* create(const int protocol,
                                    const IOAddress& address,
                                    const unsigned short port);
};

/// \brief The \c IOSocket class is an abstract base class to represent
/// various types of network sockets.
///
/// This class is a wrapper for the ASIO socket classes such as
/// \c ip::tcp::socket and \c ip::udp::socket.
///
/// Derived class implementations are completely hidden within the
/// implementation.  User applications only get access to concrete
/// \c IOSocket objects via the abstract interfaces.
/// We may revisit this decision when we generalize the wrapper and more
/// modules use it.  Also, at that point we may define a separate (visible)
/// derived class for testing purposes rather than providing factory methods
/// (i.e., getDummy variants below).
class IOSocket {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    IOSocket(const IOSocket& source);
    IOSocket& operator=(const IOSocket& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class
    /// should never be instantiated (except as part of a derived class).
    IOSocket() {}
public:
    /// The destructor.
    virtual ~IOSocket() {}
    //@}

    /// \brief Return the "native" representation of the socket.
    ///
    /// In practice, this is the file descriptor of the socket for
    /// UNIX-like systems so the current implementation simply uses
    /// \c int as the type of the return value.
    /// We may have to need revisit this decision later.
    ///
    /// In general, the application should avoid using this method;
    /// it essentially discloses an implementation specific "handle" that
    /// can change the internal state of the socket (consider the
    /// application closes it, for example).
    /// But we sometimes need to perform very low-level operations that
    /// requires the native representation.  Passing the file descriptor
    /// to a different process is one example.
    /// This method is provided as a necessary evil for such limited purposes.
    ///
    /// This method never throws an exception.
    ///
    /// \return The native representation of the socket.  This is the socket
    /// file descriptor for UNIX-like systems.
    virtual int getNative() const = 0;

    /// \brief Return the transport protocol of the socket.
    ///
    /// Currently, it returns \c IPPROTO_UDP for UDP sockets, and
    /// \c IPPROTO_TCP for TCP sockets.
    ///
    /// This method never throws an exception.
    ///
    /// \return IPPROTO_UDP for UDP sockets
    /// \return IPPROTO_TCP for TCP sockets
    virtual int getProtocol() const = 0;

    /// \brief Return a non-usable "dummy" UDP socket for testing.
    ///
    /// This is a class method that returns a "mock" of UDP socket.
    /// This is not associated with any actual socket, and its only
    /// responsibility is to return \c IPPROTO_UDP from \c getProtocol().
    /// The only feasible usage of this socket is for testing so that
    /// the test code can prepare some "UDP data" even without opening any
    /// actual socket.
    ///
    /// This method never throws an exception.
    ///
    /// \return A reference to an \c IOSocket object whose \c getProtocol()
    /// returns \c IPPROTO_UDP.
    static IOSocket& getDummyUDPSocket();

    /// \brief Return a non-usable "dummy" TCP socket for testing.
    ///
    /// See \c getDummyUDPSocket().  This method is its TCP version.
    ///
    /// \return A reference to an \c IOSocket object whose \c getProtocol()
    /// returns \c IPPROTO_TCP.
    static IOSocket& getDummyTCPSocket();
};

/// \brief The \c IOMessage class encapsulates an incoming message received
/// on a socket.
///
/// An \c IOMessage object represents a tuple of a chunk of data
/// (a UDP packet or some segment of TCP stream), the socket over which the
/// data is passed, the information about the other end point of the
/// communication, and perhaps more.
///
/// The current design and interfaces of this class is tentative.
/// It only provides a minimal level of support that is necessary for
/// the current implementation of the authoritative server.
/// A future version of this class will definitely support more.
class IOMessage {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    IOMessage(const IOMessage& source);
    IOMessage& operator=(const IOMessage& source);
public:
    /// \brief Constructor from message information.
    ///
    /// This constructor needs to handle the ASIO \c ip::address class,
    /// and is intended to be used within this wrapper implementation.
    /// Once the \c IOMessage object is created, the application can
    /// get access to the information via the wrapper interface such as
    /// \c getRemoteAddress().
    ///
    /// This constructor never throws an exception.
    ///
    /// \param data A pointer to the message data.
    /// \param data_size The size of the message data in bytes.
    /// \param io_socket The socket over which the data is given.
    /// \param remote_endpoint The other endpoint of the socket, that is,
    /// the sender of the message.
    IOMessage(const void* data, const size_t data_size, IOSocket& io_socket,
              const IOEndpoint& remote_endpoint);
    //@}

    /// \brief Returns a pointer to the received data.
    const void* getData() const { return (data_); }

    /// \brief Returns the size of the received data in bytes.
    size_t getDataSize() const { return (data_size_); }

    /// \brief Returns the socket on which the message arrives.
    const IOSocket& getSocket() const { return (io_socket_); }

    /// \brief Returns the endpoint that sends the message.
    const IOEndpoint& getRemoteEndpoint() const { return (remote_endpoint_); }
private:
    const void* data_;
    const size_t data_size_;
    IOSocket& io_socket_;
    const IOEndpoint& remote_endpoint_;
};

/// \brief The \c IOService class is a wrapper for the ASIO \c io_service
/// class.
///
/// Currently, the interface of this class is very specific to the
/// authoritative server implementation as indicated in the signature of
/// the constructor, but the plan is to generalize it so that other BIND 10
/// modules can use this interface, too.
class IOService {
    ///
    /// \name Constructors and Destructor
    ///
    /// These are currently very specific to the authoritative server
    /// implementation.
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    IOService(const IOService& source);
    IOService& operator=(const IOService& source);
public:
    /// \brief The constructor with a specific IP address and port on which
    /// the services listen on.
    IOService(AuthSrv* auth_server, const char& port, const char& address);
    /// \brief The constructor with a specific port on which the services
    /// listen on.
    ///
    /// It effectively listens on "any" IPv4 and/or IPv6 addresses.
    /// IPv4/IPv6 services will be available if and only if \c use_ipv4
    /// or \c use_ipv6 is \c true, respectively.
    IOService(AuthSrv* auth_server, const char& port,
              const bool use_ipv4, const bool use_ipv6);
    /// \brief The destructor.
    ~IOService();
    //@}

    /// \brief Start the underlying event loop.
    ///
    /// This method does not return control to the caller until
    /// the \c stop() method is called via some handler.
    void run();

    /// \brief Stop the underlying event loop.
    ///
    /// This will return the control to the caller of the \c run() method.
    void stop();

    /// \brief Return the native \c io_service object used in this wrapper.
    ///
    /// This is a short term work around to support other BIND 10 modules
    /// that share the same \c io_service with the authoritative server.
    /// It will eventually be removed once the wrapper interface is
    /// generalized.
    asio::io_service& get_io_service();

    /// \brief A functor(-like) class that specifies a custom call back
    /// invoked from the event loop instead of the embedded authoritative
    /// server callbacks.
    ///
    /// Currently, the callback is intended to be used only for testing
    /// purposes.  But we'll need a generic callback type like this to
    /// generalize the wrapper interface.
    typedef boost::function<void(const IOMessage& io_message)> IOCallBack;

    /// \brief Set the custom call back invoked from the event loop.
    ///
    /// Right now this method is only for testing, but will eventually be
    /// generalized.
    void setCallBack(IOCallBack callback);
private:
    IOServiceImpl* impl_;
};
}      // asio_link
#endif // __ASIO_LINK_H

// Local Variables: 
// mode: c++
// End: 
