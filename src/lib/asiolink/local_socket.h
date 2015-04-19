// Copyright (C) 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef LOCAL_SOCKET_H
#define LOCAL_SOCKET_H 1

#include <asiolink/api.h>
#include <asiolink/io_socket.h>
#include <asiolink/io_service.h>

#include <boost/noncopyable.hpp>

namespace isc {
namespace asiolink {

/// \brief A wrapper for ASIO stream socket in the local (AF_UNIX) domain.
///
/// This class provides a simple, limited set of wrapper interfaces to an
/// ASIO stream socket object in the local domain.  Unlike other concrete
/// derived classes of \c IOSocket, this class is intended to be instantiated
/// directly.  Right now it only provides read interface due to the limited
/// expected usage, but it can be extended as we see need for other operations
/// on this socket.
///
/// Note that in the initial implementation there's even no stop() or cancel()
/// method; for these cases users are expected to just destroy the socket
/// object (this may be extended in future, too).
class KEA_ASIOLINK_API LocalSocket : boost::noncopyable, public IOSocket {
public:
    /// \brief Constructor from a native file descriptor of AF_UNIX stream
    /// socket.
    ///
    /// Parameter \c fd must be an open stream-type socket of the AF_UNIX
    /// domain.  The constructor tries to detect some invalid cases, but
    /// it may not reject all invalid cases.  It's generally the
    /// responsibility of the caller.
    ///
    /// \throw IOError Failed to create the socket object, most likely because
    /// the given file descriptor is invalid.
    ///
    /// \param io_service The IO service object to handle events on this
    /// socket.
    /// \param fd File descriptor of an AF_UNIX socket.
    LocalSocket(IOService& io_service, int fd);

    /// \brief Destructor.
    ///
    /// \throw None.
    virtual ~LocalSocket();

    /// \brief Local socket version of getNative().
    ///
    /// \throw None.
    virtual int getNative() const;

    /// \brief Local socket version of getProtocol().
    ///
    /// It always returns \c AF_UNIX.
    ///
    /// \throw None.
    virtual int getProtocol() const;

    /// \brief The callback functor for the \c asyncRead method.
    ///
    /// The callback takes one parameter, \c error.  It will be set to
    /// non empty string if read operation fails and the string explains
    /// the reason for the failure.  On success \c error will be empty.
    typedef boost::function<void(const std::string& error)> ReadCallback;

    /// \brief Start asynchronous read on the socket.
    ///
    /// This method registers an interest on a new read event on the local
    /// socket for the specified length of data (\c buflen bytes).  This
    /// method returns immediately.   When the specified amount of data
    /// are available for read from the socket or an error happens, the
    /// specified callback will be called.  In the former case the data are
    /// copied into the given buffer (pointed to by \c buf); in the latter
    /// case, the \c error parameter of the callback will be set to a non
    /// empty string.
    ///
    /// In the case of error, this socket should be considered
    /// unusable anymore, because this class doesn't provide a feasible way
    /// to identify where in the input stream to restart reading.  So,
    /// in practice, the user of this socket should destroy this socket,
    /// and, if necessary to continue, create a new one.
    ///
    /// \c buf must point to a memory region that has at least \c buflen
    /// bytes of valid space.  That region must be kept valid until the
    /// callback is called or the \c IOService passed to the constructor
    /// is stopped.  This method and class do not check these conditions;
    /// it's the caller's responsibility to guarantee them.
    ///
    /// \note If asyncRead() has been called and hasn't been completed (with
    /// the callback being called), it's possible that the callback is called
    /// even after the \c LocalSocket object is destroyed.  So the caller
    /// has to make sure that either \c LocalSocket is valid until the
    /// callback is called or the callback does not depend on \c LocalSocket;
    /// alternatively, the caller can stop the \c IOService.  This will make
    /// sure the callback will not be called regardless of when and how
    /// the \c LocalSocket is destroyed.
    ///
    /// \throw None.
    ///
    /// \brief callback The callback functor to be called on the completion
    /// of read.
    /// \brief buf Buffer to read in data from the socket.
    /// \brief buflen Length of data to read.
    void asyncRead(const ReadCallback& callback, void* buf, size_t buflen);

private:
    class Impl;
    Impl* impl_;
};

} // namespace asiolink
} // namespace isc

#endif // LOCAL_SOCKET_H

// Local Variables:
// mode: c++
// End:
