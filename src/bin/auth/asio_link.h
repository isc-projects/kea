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

// IMPORTANT NOTE: No ASIO header files can be included in this file.
// See the description of the namespace below.
#include <asio/ip/address.hpp>

#include <functional>
#include <string>

#include <boost/function.hpp>

#include <exceptions/exceptions.h>

namespace asio {
class io_service;
namespace ip {
class address;
}
}

class AuthSrv;

/// \namespace asio_link
/// \brief A wrapper interface for the ASIO library.
///
/// The \c asio_link namespace is used to define a set of wrapper interfaces
/// for the ASIO library.
/// BIND 10 uses non Boost version of ASIO because it's header only, i.e.
/// does not require a separate library object to be linked, and thus
/// lowers the bar for introduction.
/// But the advantage comes with its own costs: since the header only version
/// includes more definitions in public header files, it tends to trigger
/// more compiler warnings for our own sources, and, depending on the
/// compiler options, may make the build fail.
/// We also found it may be tricky to use ASIO and standard C++ libraries
/// in a single translation unit, i.e., a .cc file: depending on the order
/// of including header files ASIO may or may not work on some platforms.
/// This wrapper interfaces are intended to centralize points of these
/// problematic issues in a single sub module.  Other BIND 10 modules should
/// simply include \c asio_link.h and use the wrapper APIs instead of
/// including ASIO header files and using ASIO specific classes directly.
///
/// This wrapper may be used for other IO libraries if and when we want to
/// switch, but generality for that purpose is not the primary goal of
/// this module.  The resulting interfaces are thus straightforward mapping
/// to the ASIO counterparts.
///
/// Note: currently the wrapper interface is specific to the authoritative
/// server implementation.  But the plan is to generalize it and have
/// other modules use it.
///
/// Note: One obvious drawback of this approach is performance overhead
/// due to the additional layer.  We should eventually evaluate the cost
/// of the wrapper abstraction in benchmark tests.
///
/// Another drawback is that the wrapper interfaces don't provide all features
/// of ASIO (at least for the moment).  We should also re-evaluate the
/// maintenance overhead of providing necessary wrappers as we develop
/// more.

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

/// \brief DESCRIPTION
class IOEndpoint {
private:
    IOEndpoint(const IOEndpoint& source);
    IOEndpoint& operator=(const IOEndpoint& source);
protected:
    IOEndpoint() {}
public:
    virtual ~IOEndpoint() {}
    virtual IOAddress getAddress() const = 0;
    static const IOEndpoint* createFromAddress(int protocol,
                                               const IOAddress& address,
                                               unsigned short port);
};

/// \brief The \c IOSocket class is an abstract base class to represent
/// various types of network sockets.
///
/// This class is a wrapper for the ASIO socket classes such as
/// \c ip::tcp::socket and \c ip::udp::socket.
///
/// Derived class implementations are completely hidden with the
/// implementation.  User applications only get access to concrete
/// \c IOSocket objects via the abstract interfaces.
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
    /// can change the internal state of the socket (e.g. consider the
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

/// \brief The \c IOMessage class encapsulates a message exchanged via
/// the ASIO module.
///
/// An \c IOMessage object represents a tuple of a chunk of data
/// (a UDP packet or some segment of TCP stream), the socket over which the
/// data is passed, the information about the other end point of the
/// communication, and perhaps more.
///
/// The current design and interfaces of this class is tentative.
/// It only provides a minimal level of support that is necessary for
/// the current implementation of the authoritative server.
/// A future version of this class will definitely support more
/// Also, it may not be efficient, involving avoidable copies for example.
/// This should be revisited in the near future, too.
/// (e.g., we'll need a notion of "endpoint", both for generality and for
/// efficiency).
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
    /// \param remote_endpoint An ASIO address object represents the other
    /// endpoint of the socket.
    IOMessage(const void* data, size_t data_size, IOSocket& io_socket,
              const IOEndpoint& remote_endpoint);
    //@}
    const void* getData() const { return (data_); }
    size_t getDataSize() const { return (data_size_); }
    const IOSocket& getSocket() const { return (io_socket_); }
    const IOEndpoint& getRemoteEndpoint() const { return (remote_endpoint_); }
private:
    const void* data_;
    const size_t data_size_;
    IOSocket& io_socket_;
    const IOEndpoint& remote_endpoint_;
};

class IOService {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    IOService(const IOService& source);
    IOService& operator=(const IOService& source);
public:
    IOService(AuthSrv* auth_server, const char* port, bool use_ipv4,
              bool use_ipv6);
    /// \brief The destructor.
    ~IOService();
    //@}
    void run();
    void stop();
    asio::io_service& get_io_service();
    /// Right now this method is only for testing, but will eventually be
    /// generalized.
    typedef boost::function<void(const IOMessage& io_message)> IOCallBack;
    void setCallBack(IOCallBack callback);
private:
    IOServiceImpl* impl_;
};
}      // asio_link
#endif // __ASIO_LINK_H

// Local Variables: 
// mode: c++
// End: 
