// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SOCKETSESSION_H
#define SOCKETSESSION_H 1

#include <boost/noncopyable.hpp>

#include <exceptions/exceptions.h>

#include <string>

#include <sys/socket.h>

namespace isc {
namespace util {
namespace io {

/// \page SocketSessionUtility Socket session utility
///
/// This utility defines a set of classes that support forwarding a
/// "socket session" from one process to another.  A socket session is a
/// conceptual tuple of the following elements:
/// - A network socket
/// - The local and remote endpoints of a (IP) communication taking place on
///   the socket.  In practice an endpoint is a pair of an IP address and
///   TCP or UDP port number.
/// - Some amount of data sent from the remote endpoint and received on the
///   socket.  We call it (socket) session data in this documentation.
///
/// Note that this is a conceptual definition.  Depending on the underlying
/// implementation and/or the network protocol, some of the elements could be
/// part of others; for example, if it's an established TCP connection,
/// the local and remote endpoints would be able to be retrieved from the
/// socket using the standard \c getsockname() and \c getpeername() system
/// calls.  But in this definition we separate these to be more generic.
/// Also, as a matter of fact our intended usage includes non-connected UDP
/// communications, in which case at least the remote endpoint should be
/// provided separately from the socket.
///
/// In the actual implementation we represent a socket as a tuple of
/// socket's file descriptor, address family (e.g. \c AF_INET6),
/// socket type (e.g. \c SOCK_STREAM), and protocol (e.g. \c IPPROTO_TCP).
/// The latter three are included in the representation of a socket in order
/// to provide complete information of how the socket would be created
/// by the \c socket(2) system call.  More specifically in practice, these
/// parameters could be used to construct a Python socket object from the
/// file descriptor.
///
/// We use the standard \c sockaddr structure to represent endpoints.
///
/// Socket session data is an opaque memory region of an arbitrary length
/// (possibly with some reasonable upper limit).
///
/// To forward a socket session between processes, we use connected UNIX
/// domain sockets established between the processes.  The file descriptor
/// will be forwarded through the sockets as an ancillary data item of
/// type \c SCM_RIGHTS.  Other elements of the session will be transferred
/// as normal data over the connection.
///
/// We provide three classes to help applications forward socket sessions:
/// \c SocketSessionForwarder is the sender of the UNIX domain connection,
/// while \c SocketSessionReceiver is the receiver (this interface assumes
/// one direction of forwarding); \c SocketSession represents a single
/// socket session.
///
/// \c SocketSessionForwarder and \c SocketSessionReceiver objects use a
/// straightforward protocol to pass elements of socket sessions.
/// Once the connection is established, the forwarder object first forwards
/// the file descriptor with 1-byte dummy data.  It then forwards a
/// "(socket) session header", which contains all other elements of the session
/// except the file descriptor (already forwarded) and session data.
/// The wire format of the header is as follows:
/// - The length of the header (16-bit unsigned integer)
/// - Address family
/// - Socket type
/// - Protocol
/// - Size of the local endpoint in bytes
/// - Local endpoint (a copy of the memory image of the corresponding
///   \c sockaddr)
/// - Size of the remote endpoint in bytes
/// - Remote endpoint (same as local endpoint)
/// - Size of session data in bytes
///
/// The type of the fields is 32-bit unsigned integer unless explicitly
/// noted, and all fields are formatted in the network byte order.
///
/// The socket session data immediately follows the session header.
///
/// Note that the fields do not necessarily be in the network byte order
/// because they are expected to be exchanged on the same machine.  Likewise,
/// integer elements such as address family do not necessarily be represented
/// as an fixed-size value (i.e., 32-bit).  But fixed size fields are used
/// in order to ensure maximum portability in such a (rare) case where the
/// forwarder and the receiver are built with different compilers that have
/// different definitions of \c int.  Also, since \c sockaddr fields are
/// generally formatted in the network byte order, other fields are defined
/// so to be consistent.
///
/// One basic assumption in the API of this utility is socket sessions should
/// be forwarded without blocking, thus eliminating the need for incremental
/// read/write or blocking other important services such as responding to
/// requests from the application's clients.  This assumption should be held
/// as long as both the forwarder and receiver have sufficient resources
/// to handle the forwarding process since the communication is local.
/// But a forward attempt could still block if the receiver is busy (or even
/// hang up) and cannot keep up with the volume of incoming sessions.
///
/// So, in this implementation, the forwarder uses non blocking writes to
/// forward sessions.  If a write attempt could block, it immediately gives
/// up the operation with an exception.  The corresponding application is
/// expected to catch it, close the connection, and perform any necessary
/// recovery for that application (that would normally be re-establish the
/// connection with a new receiver, possibly after confirming the receiving
/// side is still alive).  On the other hand, the receiver implementation
/// assumes it's possible that it only receive incomplete elements of a
/// session (such as in the case where the forwarder writes part of the
/// entire session and gives up the connection).  The receiver implementation
/// throws an exception when it encounters an incomplete session.  Like the
/// case of the forwarder application, the receiver application is expected
/// to catch it, close the connection, and perform any necessary recovery
/// steps.
///
/// Note that the receiver implementation uses blocking read.  So it's
/// application's responsibility to ensure that there's at least some data
/// in the connection when the receiver object is requested to receive a
/// session (unless this operation can be blocking, e.g., by the use of
/// a separate thread).  Also, if the forwarder implementation or application
/// is malicious or extremely buggy and intentionally sends partial session
/// and keeps the connection, the receiver could block in receiving a session.
/// In general, we assume the forwarder doesn't do intentional blocking
/// as it's a local node and is generally a module of the same (Kea)
/// system.  The minimum requirement for the forwarder implementation (and
/// application) is to make sure the connection is closed once it detects
/// an error on it.  Even a naive implementation that simply dies due to
/// the exception will meet this requirement.

/// An exception indicating general errors that takes place in the
/// socket session related class objects.
///
/// In general the errors are unusual but possible failures such as unexpected
/// connection reset, and suggest the application to close the connection and
/// (if necessary) reestablish it.
class SocketSessionError: public Exception {
public:
    SocketSessionError(const char *file, size_t line, const char *what):
        isc::Exception(file, line, what) {}
};

/// The "base" class of \c SocketSessionForwarder
///
/// This class defines abstract interfaces of the \c SocketSessionForwarder
/// class.  Although \c SocketSessionForwarder is not intended to be used in
/// a polymorphic way, it's not easy to use in tests because it will require
/// various low level network operations.  So it would be useful if we
/// provide a framework for defining a fake or mock version of it.
/// An application that needs to use \c SocketSessionForwarder would actually
/// refer to this base class, and tests for the application would define
/// and use a fake version of the forwarder class.
///
/// Normal applications are not expected to define and use their own derived
/// version of this base class, while it's not prohibited at the API level.
///
/// See description of \c SocketSessionForwarder for the expected interface.
class BaseSocketSessionForwarder  {
protected:
    BaseSocketSessionForwarder() {}

public:
    virtual ~BaseSocketSessionForwarder() {}
    virtual void connectToReceiver() = 0;
    virtual void close() = 0;
    virtual void push(int sock, int family, int type, int protocol,
                      const struct sockaddr& local_end,
                      const struct sockaddr& remote_end,
                      const void* data, size_t data_len) = 0;
};

/// The forwarder of socket sessions
///
/// An object of this class maintains a UNIX domain socket (normally expected
/// to be connected to a \c SocketSessionReceiver object) and forwards
/// socket sessions to the receiver.
///
/// See the description of \ref SocketSessionUtility for other details of how
/// the session forwarding works.
class SocketSessionForwarder : boost::noncopyable,
                               public BaseSocketSessionForwarder
{
public:
    /// The constructor.
    ///
    /// It's constructed with path information of the intended receiver,
    /// but does not immediately establish a connection to the receiver;
    /// \c connectToReceiver() must be called to establish it.  These are
    /// separated so that an object of class can be initialized (possibly
    /// as an attribute of a higher level application class object) without
    /// knowing the receiver is ready for accepting new forwarders.  The
    /// separate connect interface allows the object to be reused when it
    /// detects connection failure and tries to re-establish it after closing
    /// the failed one.
    ///
    /// On construction, it also installs a signal filter for SIGPIPE to
    /// ignore it.  Since this class uses a stream-type connected UNIX domain
    /// socket, if the receiver (abruptly) closes the connection a subsequent
    /// write operation on the socket would trigger a SIGPIPE signal, which
    /// kills the caller process by default.   This behavior would be
    /// undesirable in many cases, so this implementation always disables
    /// the signal.
    ///
    /// This approach has some drawbacks, however; first, since signal handling
    /// is process (or thread) wide, ignoring it may not what the application
    /// wants.  On the other hand, if the application changes how the signal is
    /// handled after instantiating this class, the new behavior affects the
    /// class operation.  Secondly, even if ignoring the signal is the desired
    /// operation, it's a waste to set the filter every time this class object
    /// is constructed.  It's sufficient to do it once.  We still adopt this
    /// behavior based on the observation that in most cases applications would
    /// like to ignore SIGPIPE (or simply doesn't care about it) and that this
    /// class is not instantiated so often (so the wasteful setting overhead
    /// should be marginal).  On the other hand, doing it every time is
    /// beneficial if the application is threaded and different threads
    /// create different forwarder objects (and if signals work per thread).
    ///
    /// \exception SocketSessionError \c unix_file is invalid as a path name
    /// of a UNIX domain socket.
    /// \exception Unexpected Error in setting a filter for SIGPIPE (see above)
    /// \exception std::bad_alloc resource allocation failure
    ///
    /// \param unix_file Path name of the receiver.
    explicit SocketSessionForwarder(const std::string& unix_file);

    /// The destructor.
    ///
    /// If a connection has been established, it's automatically closed in
    /// the destructor.
    virtual ~SocketSessionForwarder();

    /// Establish a connection to the receiver.
    ///
    /// This method establishes a connection to the receiver at the path
    /// given on construction.  It makes the underlying UNIX domain socket
    /// non blocking, so this method (or subsequent \c push() calls) does not
    /// block.
    ///
    /// \exception BadValue The method is called while an already
    /// established connection is still active.
    /// \exception SocketSessionError A system error in socket operation.
    virtual void connectToReceiver();

    /// Close the connection to the receiver.
    ///
    /// The connection must have been established by \c connectToReceiver().
    /// As long as it's met this method is exception free.
    ///
    /// \exception BadValue The connection hasn't been established.
    virtual void close();

    /// Forward a socket session to the receiver.
    ///
    /// This method takes a set of parameters that represent a single socket
    /// session, renders them in the "wire" format according to the internal
    /// protocol (see \ref SocketSessionUtility) and forwards them to
    /// the receiver through the UNIX domain connection.
    ///
    /// The connection must have been established by \c connectToReceiver().
    ///
    /// For simplicity and for the convenience of detecting application
    /// errors, this method imposes some restrictions on the parameters:
    /// - Socket family must be either \c AF_INET or \c AF_INET6
    /// - The address family (\c sa_family) member of the local and remote
    ///   end points must be equal to the \c family parameter
    /// - Socket session data must not be empty (\c data_len must not be 0
    ///   and \c data must not be NULL)
    /// - Data length must not exceed 65535
    /// These are not architectural limitation, and might be loosened in
    /// future versions as we see the need for flexibility.
    ///
    /// Since the underlying UNIX domain socket is non blocking
    /// (see the description for the constructor), a call to this method
    /// should either return immediately or result in exception (in case of
    /// "would block").
    ///
    /// \exception BadValue The method is called before establishing a
    /// connection or given parameters are invalid.
    /// \exception SocketSessionError A system error in socket operation,
    /// including the case where the write operation would block.
    ///
    /// \param sock The socket file descriptor
    /// \param family The address family (such as AF_INET6) of the socket
    /// \param type The socket type (such as SOCK_DGRAM) of the socket
    /// \param protocol The transport protocol (such as IPPROTO_UDP) of the
    ///        socket
    /// \param local_end The local end point of the session in the form of
    ///        \c sockaddr.
    /// \param remote_end The remote end point of the session in the form of
    ///        \c sockaddr.
    /// \param data A pointer to the beginning of the memory region for the
    ///             session data
    /// \param data_len The size of the session data in bytes.
    virtual void push(int sock, int family, int type, int protocol,
                      const struct sockaddr& local_end,
                      const struct sockaddr& remote_end,
                      const void* data, size_t data_len);

private:
    struct ForwarderImpl;
    ForwarderImpl* impl_;
};

/// Socket session object.
///
/// The \c SocketSession class provides a convenient encapsulation
/// for the notion of a socket session.  It's instantiated with straightforward
/// parameters corresponding to a socket session, and provides read only
/// accessors to the parameters to ensure data integrity.
///
/// In the initial design and implementation it's only used as a return type
/// of \c SocketSessionReceiver::pop(), but it could also be used by
/// the \c SocketSessionForwarder class or for other purposes.
///
/// It is assumed that the original owner of a \c SocketSession object
/// (e.g. a class or a function that constructs it) is responsible for validity
/// of the data passed to the object.  See the description of
/// \c SocketSessionReceiver::pop() for the specific case of that usage.
class SocketSession {
public:
    /// The constructor.
    ///
    /// This is a trivial constructor, taking a straightforward representation
    /// of session parameters and storing them internally to ensure integrity.
    ///
    /// As long as the given parameters are valid it never throws an exception.
    ///
    /// \exception BadValue Given parameters don't meet the requirement
    /// (see the parameter descriptions).
    ///
    /// \param sock The socket file descriptor
    /// \param family The address family (such as AF_INET6) of the socket
    /// \param type The socket type (such as SOCK_DGRAM) of the socket
    /// \param protocol The transport protocol (such as IPPROTO_UDP) of the
    ///        socket.
    /// \param local_end The local end point of the session in the form of
    ///        \c sockaddr.  Must not be NULL.
    /// \param remote_end The remote end point of the session in the form of
    ///        \c sockaddr.  Must not be NULL.
    /// \param data A pointer to the beginning of the memory region for the
    /// session data.  Must not be NULL, and the subsequent \c data_len bytes
    /// must be valid.
    /// \param data_len The size of the session data in bytes.  Must not be 0.
    SocketSession(int sock, int family, int type, int protocol,
                  const sockaddr* local_end, const sockaddr* remote_end,
                  const void* data, size_t data_len);

    /// Return the socket file descriptor.
    int getSocket() const { return (sock_); }

    /// Return the address family (such as AF_INET6) of the socket.
    int getFamily() const { return (family_); }

    /// Return the socket type (such as SOCK_DGRAM) of the socket.
    int getType() const { return (type_); }

    /// Return the transport protocol (such as IPPROTO_UDP) of the socket.
    int getProtocol() const { return (protocol_); }

    /// Return the local end point of the session in the form of \c sockaddr.
    const sockaddr& getLocalEndpoint() const { return (*local_end_); }

    /// Return the remote end point of the session in the form of \c sockaddr.
    const sockaddr& getRemoteEndpoint() const { return (*remote_end_); }

    /// Return a pointer to the beginning of the memory region for the session
    /// data.
    ///
    /// In the current implementation it should never be NULL, and the region
    /// of the size returned by \c getDataLength() is expected to be valid.
    const void* getData() const { return (data_); }

    /// Return the size of the session data in bytes.
    ///
    /// In the current implementation it should be always larger than 0.
    size_t getDataLength() const { return (data_len_); }

private:
    const int sock_;
    const int family_;
    const int type_;
    const int protocol_;
    const sockaddr* local_end_;
    const sockaddr* remote_end_;
    const void* const data_;
    const size_t data_len_;
};

/// The receiver of socket sessions
///
/// An object of this class holds a UNIX domain socket for an
/// <em>established connection</em>, receives socket sessions from
/// the remote forwarder, and provides the session to the application
/// in the form of a \c SocketSession object.
///
/// Note that this class is instantiated with an already connected socket;
/// it's not a listening socket that is accepting connection requests from
/// forwarders.  It's application's responsibility to create the listening
/// socket, listen on it and accept connections.  Once the connection is
/// established, the application would construct a \c SocketSessionReceiver
/// object with the socket for the newly established connection.
/// This behavior is based on the design decision that the application should
/// decide when it performs (possibly) blocking operations (see \ref
/// SocketSessionUtility for more details).
///
/// See the description of \ref SocketSessionUtility for other details of how
/// the session forwarding works.
class SocketSessionReceiver : boost::noncopyable {
public:
    /// The constructor.
    ///
    /// \exception SocketSessionError Any error on an operation that is
    /// performed on the given socket as part of initialization.
    /// \exception std::bad_alloc Resource allocation failure
    ///
    /// \param fd A UNIX domain socket for an established connection with
    /// a forwarder.
    explicit SocketSessionReceiver(int fd);

    /// The destructor.
    ///
    /// The destructor does \c not close the socket given on construction.
    /// It's up to the application what to do with it (note that the
    /// application would have to maintain the socket itself for detecting
    /// the existence of a new socket session asynchronously).
    ~SocketSessionReceiver();

    /// Receive a socket session from the forwarder.
    ///
    /// This method receives wire-format data (see \ref SocketSessionUtility)
    /// for a socket session on the UNIX domain socket, performs some
    /// validation on the data, and returns the session information in the
    /// form of a \c SocketSession object.
    ///
    /// The returned SocketSession object is valid only until the next time
    /// this method is called or until the \c SocketSessionReceiver object is
    /// destroyed.
    ///
    /// The caller is responsible for closing the received socket (whose
    /// file descriptor is accessible via \c SocketSession::getSocket()).
    /// If the caller copies the returned \c SocketSession object, it's also
    /// responsible for making sure the descriptor is closed at most once.
    /// On the other hand, the caller is not responsible for freeing the
    /// socket session data (accessible via \c SocketSession::getData());
    /// the \c SocketSessionReceiver object will clean it up automatically.
    ///
    /// It ensures the following:
    /// - The address family is either \c AF_INET or \c AF_INET6
    /// - The address family (\c sa_family) member of the local and remote
    ///   end points must be equal to the \c family parameter
    /// - The socket session data is not empty and does not exceed 65535
    ///   bytes.
    /// If the validation fails or an unexpected system error happens
    /// (including a connection close in the meddle of reception), it throws
    /// an SocketSessionError exception.  When this happens, it's very
    /// unlikely that a subsequent call to this method succeeds, so in reality
    /// the application is expected to destruct it and close the socket in
    /// such a case.
    ///
    /// \exception SocketSessionError Invalid data is received or a system
    /// error on socket operation happens.
    /// \exception std::bad_alloc Resource allocation failure
    ///
    /// \return A \c SocketSession object corresponding to the extracted
    /// socket session.
    SocketSession pop();

private:
    struct ReceiverImpl;
    ReceiverImpl* impl_;
};

}
}
}

#endif  // SOCKETSESSION_H

// Local Variables:
// mode: c++
// End:
