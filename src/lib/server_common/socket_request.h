// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef SOCKET_REQUEST_H
#define SOCKET_REQUEST_H 1

#include <exceptions/exceptions.h>

#include <boost/noncopyable.hpp>
#include <utility>
#include <string>
#include <stdint.h>

namespace isc {

namespace cc {
class AbstractSession;
};

namespace server_common {

/// \brief A singleton class for requesting sockets
///
/// This class allows requesting sockets from the socket creator.
///
/// It is considered to be a singleton - a class which is instantiated
/// at most once in the whole application. This is because it makes no
/// sense to have two of them.
///
/// This is actually an abstract base class. There'll be one with
/// hidden implementation and we expect the tests to create its own
/// subclass when needed.
///
/// \see socketRequestor function to access the object of this class.
class SocketRequestor : boost::noncopyable {
protected:
    /// \brief Protected constructor
    ///
    /// The constructor is protected so this class is not created by accident
    /// (which it can't anyway, as it has pure virtual methods, but just to
    /// be sure).
    SocketRequestor() {}

public:
    /// \brief virtual destructor
    ///
    /// A virtual destructor, as we have virtual methods, to make sure it is
    /// destroyed by the destructor of the subclass. This shouldn't matter, as
    /// a singleton class wouldn't get destroyed, but just to be sure.
    virtual ~ SocketRequestor() {}

    /// \brief A representation of received socket
    ///
    /// The pair holds two parts. The OS-level file descriptor acting as the
    /// socket (you might want to use it directly with functions like recv,
    /// or fill it into an asio socket). The other part is the token
    /// representing the socket, which allows it to be given up again.
    typedef std::pair<int, std::string> SocketID;

    /// \brief The protocol of requested socket
    ///
    /// This describes which protocol the socket should have when created.
    enum Protocol {
        UDP,
        TCP
    };

    /// \brief The share mode of the requested socket
    ///
    /// The socket creator is able to "borrow" the same socket to multiple
    /// applications at once. However, it isn't always what is required. This
    /// describes the restrains we want to have on our socket regarding the
    /// sharing. Union of restriction of all requests on the given socket
    /// is taken (so you still don't have to get your socket even if you
    /// say SHARE_ANY, because someone else might already asked for the socket
    /// with DONT_SHARE).
    enum ShareMode {
        DONT_SHARE, //< Request an exclusive ownership of the socket.
        SHARE_SAME, //< It is possible to share the socket with anybody who
                    //< provided the same share_name.
        SHARE_ANY   //< Any sharing is allowed.
    };

    /// \brief Exception when we can't manipulate a socket
    ///
    /// This is thrown if the other side doesn't want to comply to our
    /// requests, like when we ask for a socket already held by someone
    /// else or ask for nonsense (releasing a socket we don't own).
    class SocketError : public Exception {
    public:
        SocketError(const char* file, size_t line, const char* what) :
            Exception(file, line, what)
        { }
    };

    /// \brief Exception when we can't return a requested socket, but we're
    ///     sure we could return others
    ///
    /// This is thrown if the requested socket can't be granted, but it is only
    /// that one socket, not that the system would be broken or anything. This
    /// exception is a common base class for the concrete exceptions actually
    /// thrown. You can safely keep using the SocketRequestor after this
    /// exception (or anything derived from it) is thrown.
    ///
    /// \see ShareError
    /// \see SocketAllocateError
    class NonFatalSocketError : public SocketError {
    public:
        NonFatalSocketError(const char* file, size_t line, const char* what) :
            SocketError(file, line, what)
        { }
    };

    /// \brief Exception when the socket is allocated by other bind10 module
    ///    and it doesn't want to share it.
    ///
    /// This is thrown if a socket is requested and the socket is already
    /// allocated by bind10, but other bind10 module(s) is using it and
    /// the sharing parameters are incompatible (the socket can't be shared
    /// between the module and our module).
    class ShareError : public NonFatalSocketError {
    public:
        ShareError(const char* file, size_t line, const char* what) :
            NonFatalSocketError(file, line, what)
        { }
    };

    /// \brief Exception when the operating system doesn't allow us to create
    ///    the requested socket.
    ///
    /// This happens when the socket() or bind() call fails in the socket
    /// creator. This can happen when the address/port pair is already taken
    /// by a different application, the socket creator doesn't have enough
    /// privileges, or for some kind of similar reason.
    class SocketAllocateError : public NonFatalSocketError {
    public:
        SocketAllocateError(const char* file, size_t line, const char* what) :
            NonFatalSocketError(file, line, what)
        { }
    };

    /// \brief Ask for a socket
    ///
    /// Asks the socket creator to give us a socket. The socket will be bound
    /// to the given address and port.
    ///
    /// \param protocol specifies the protocol of the socket.  This must be
    /// either UDP or TCP.
    /// \param address to which the socket should be bound.
    /// \param port the port to which the socket should be bound (native endian,
    ///     not network byte order).
    /// \param share_mode how the socket can be shared with other requests.
    ///     This must be one of the defined values of ShareMode..
    /// \param share_name the name of sharing group, relevant for SHARE_SAME
    ///     (specified by us or someone else). If left empty (the default),
    ///     the app_name parameter of initSocketRequestor is used. If that one
    ///     is empty as well, it is accepted, but not recommended, as such
    ///     a non-descriptive name has a high chance of collisions between
    ///     applications. Note that you should provide a name (by share_name
    ///     or app_name) even when you set it to DONT_SHARE (for logs and
    ///     debugging) and you need to provide one with SHARE_SAME (to know
    ///     what is same) and SHARE_ANY (someone else might want SHARE_SAME,
    ///     so it would check against this)
    /// \return the socket, as a file descriptor and token representing it on
    ///     the socket creator side.
    ///
    /// To understand the modes better:
    /// - If mode is DONT_SHARE, it succeeds if no one else has opened an FD
    ///   for requested protocol, address and port.
    /// - If mode is SHARE_SAME, it succeeds if all applications who opened an
    ///   FD for the requested protocol, address and port provided the same
    ///   share_name as this one and none of them had mode DONT_SHARE.
    /// - If mode is SHARE_ANY, it succeeds if no applications who requested
    ///   the same potocol, address and port provided DONT_SHARE and all the
    ///   applications who provided SHARE_SAME also provided the same
    ///   share_name as this process did.
    ///
    /// \throw InvalidParameter protocol or share_mode is invalid
    /// \throw CCSessionError when we have a problem talking over the CC
    ///     session.
    /// \throw SocketError in case we have some other problems receiving the
    ///     socket (eg. inconsistency in the protocol, the socket got stuck
    ///     in the transport, etc). If the exception is not of the following
    ///     derived ones, it usualy means something serious happened.
    /// \throw SocketAllocateError if the other side can't create the socket.
    /// \throw ShareError if the socket is used by other bind10 module and
    ///     that one doesn't want to share it with us.
    virtual SocketID requestSocket(Protocol protocol,
                                   const std::string& address,
                                   uint16_t port, ShareMode share_mode,
                                   const std::string& share_name = "") = 0;

    /// \brief Tell the socket creator we no longer need the socket
    ///
    /// Releases the identified socket. This must be called *after*
    /// the file descriptor was closed on our side. This will allow
    /// the remote side to either give it to some other application
    /// or close it, depending on the situation.
    ///
    /// \param token the token representing the socket, as received
    ///     in the second part of the requestSocket result.
    /// \throw CCSessionError when we have a problem talking over the CC
    ///     session.
    /// \throw SocketError in case the other side doesn't like the
    ///     release (like we're trying to release a socket that doesn't
    ///     belong to us or exist at all).
    virtual void releaseSocket(const std::string& token) = 0;
};

/// \brief Access the requestor object.
///
/// This returns the singleton object for the Requestor.
///
/// \return the active socket requestor object.
/// \throw InvalidOperation if the object was not yet initialized.
/// \see SocketRequestor::init to initialize the object.
SocketRequestor& socketRequestor();

/// \brief Initialize the singleton object
///
/// This creates the object that will be used to request sockets.
/// It can be called only once per the life of application.
///
/// \param session the CC session that'll be used to talk to the
///                socket creator.
/// \param app_name default share name if one is not provided with
///                 requestSocket. You can leave this as empty string,
///                 but then you should provide a reasonably descriptive
///                 name to requestSocket. Empty names work like any others,
///                 but have a high chance of collisions, so it is recommended
///                 to avoid them and provide the name of the application
///                 here.
/// \throw InvalidOperation when it is called more than once
void initSocketRequestor(cc::AbstractSession& session,
                         const std::string& app_name);

/// \brief Initialization for tests
///
/// This is to support different subclasses in tests. It replaces
/// the object used by socketRequestor() function by this one provided
/// as parameter. The ownership is not taken, eg. it's up to the caller
/// to delete it when necessary.
///
/// This is not to be used in production applications. It is meant as
/// an replacement of init.
///
/// This never throws.
///
/// \param requestor the object to be used. It can be NULL to reset to
///     an "virgin" state (which acts as if initTest or init was never
///     called before).
void initTestSocketRequestor(SocketRequestor* requestor);

/// \brief Destroy the singleton instance
///
/// Calling this function is not strictly necessary; the socket
/// requestor is a singleton anyway. However, for some tests it
/// is useful to destroy and recreate it, as well as for programs
/// that want to be completely clean on exit.
/// After this function has been called, all operations except init
/// will fail.
void cleanupSocketRequestor();

}
}

#endif  // SOCKET_REQUEST_H
