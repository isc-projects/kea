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

#ifndef __IO_FETCH_H
#define __IO_FETCH_H 1

#include <config.h>

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <coroutine.h>

#include <asio/error_code.hpp>

#include <dns/buffer.h>
#include <dns/question.h>

namespace asiolink {

// Forward declarations
class IOAddress;
class IOFetchData;
class IOService;

/// \brief Upstream Fetch Processing
///
/// IOFetch is the class used to send upstream fetches and to handle responses.
///
/// \param E Endpoint type to use.

class IOFetch : public coroutine {
public:
    /// \brief Protocol to use on the fetch
    enum Protocol {
        UDP = 0,
        TCP = 1
    };

    /// \brief Origin of Asynchronous I/O Call
    ///
    /// Indicates what initiated an asynchronous I/O call and used in deciding
    /// what error message to output if the I/O fails.
    enum Origin {
        NONE = 0,           ///< No asynchronous call outstanding
        OPEN = 1,
        SEND = 2,
        RECEIVE = 3,
        CLOSE = 4
    };

    /// \brief Result of Upstream Fetch
    ///
    /// Note that this applies to the status of I/Os in the fetch - a fetch
    /// that resulted in a packet being received from the server is a SUCCESS,
    /// even if the contents of the packet indicate that some error occurred.
    enum Result {
        SUCCESS = 0,        ///< Success, fetch completed
        TIME_OUT = 1,       ///< Failure, fetch timed out
        STOPPED = 2,        ///< Control code, fetch has been stopped
        NOTSET = 3          ///< For testing, indicates value not set
    };

    // The next enum is a "trick" to allow constants to be defined in a class
    // declaration.

    /// \brief Integer Constants
    enum {
        STAGING_LENGTH = 8192   ///< Size of staging buffer
    };

    /// \brief I/O Fetch Callback
    ///
    /// Class of callback object for when the fetch itself has completed - an
    /// object of this class is passed to the IOFetch constructor and its
    /// operator() method called when the fetch completes.
    ///
    /// Note the difference between the two operator() methods:
    /// - IOFetch::operator() callback is called when an asynchronous I/O has
    ///   completed.
    /// - IOFetch::Callback::operator() is called when an upstream fetch - which
    ///   may have involved several asynchronous I/O operations - has completed.
    ///
    /// This is an abstract class.
    class Callback {
    public:
        /// \brief Default Constructor
        Callback()
        {}

        /// \brief Virtual Destructor
        virtual ~Callback()
        {}

        /// \brief Callback method
        ///
        /// This is the method called when the fetch completes.
        ///
        /// \param result Result of the fetch
        virtual void operator()(Result result) = 0;
    };

    /// \brief Constructor.
    ///
    /// Creates the object that will handle the upstream fetch.
    ///
    /// TODO: Need to randomise the source port
    ///
    /// \param protocol Fetch protocol, either IOFetch::TCP or IOFetch::UDP
    /// \param service I/O Service object to handle the asynchronous
    ///     operations.
    /// \param question DNS question to send to the upstream server.
    /// \param buff Output buffer into which the response (in wire format)
    ///     is written (if a response is received).
    /// \param cb Callback object containing the callback to be called
    ///     when we terminate.  The caller is responsible for managing this
    ///     object and deleting it if necessary.
    /// \param address IP address of upstream server
    /// \param port Port to which to connect on the upstream server
    /// (default = 53)
    /// \param wait Timeout for the fetch (in ms).  The default value of
    ///     -1 indicates no timeout.
    IOFetch(Protocol protocol, IOService& service,
        const isc::dns::Question& question, const IOAddress& address,
        uint16_t port, isc::dns::OutputBufferPtr& buff, Callback* cb,
        int wait = -1);

    /// \brief Constructor.
    ///
    /// Creates the object that will handle the upstream fetch.
    ///
    /// TODO: Need to randomise the source port
    ///
    /// \param protocol Fetch protocol, either IOFetch::TCP or IOFetch::UDP
    /// \param service I/O Service object to handle the asynchronous
    ///     operations.
    /// \param outpkt Packet to send to upstream server.  Note that the
    ///     QID (first two bytes of the packet) may be altered in the sending.
    /// \param buff Output buffer into which the response (in wire format)
    ///     is written (if a response is received).
    /// \param cb Callback object containing the callback to be called
    ///     when we terminate.  The caller is responsible for managing this
    ///     object and deleting it if necessary.
    /// \param address IP address of upstream server
    /// \param port Port to which to connect on the upstream server
    /// (default = 53)
    /// \param wait Timeout for the fetch (in ms).  The default value of
    ///     -1 indicates no timeout.
    IOFetch(Protocol protocol, IOService& service,
        isc::dns::OutputBufferPtr& outpkt, const IOAddress& address,
        uint16_t port, isc::dns::OutputBufferPtr& buff, Callback* cb,
        int wait = -1);

    /// \brief Return Current Protocol
    ///
    /// \return Protocol associated with this IOFetch object.
    Protocol getProtocol() const;

    /// \brief Coroutine entry point
    ///
    /// The operator() method is the method in which the coroutine code enters
    /// this object when an operation has been completed.
    ///
    /// \param ec Error code, the result of the last asynchronous I/O operation.
    /// \param length Amount of data received on the last asynchronous read
    void operator()(asio::error_code ec = asio::error_code(), size_t length = 0);

    /// \brief Terminate query
    ///
    /// This method can be called at any point.  It terminates the current
    /// query with the specified reason.
    ///
    /// \param reason Reason for terminating the query
    void stop(Result reason = STOPPED);

private:
    /// \brief Log I/O Failure
    ///
    /// Records an I/O failure to the log file
    ///
    /// \param ec ASIO error code
    void logIOFailure(asio::error_code ec);

    // Member variables.  All data is in a structure pointed to by a shared
    // pointer.  The IOFetch object is copied a number of times during its
    // life, and only requiring a pointer to be copied reduces overhead.
    boost::shared_ptr<IOFetchData>  data_;   ///< Private data

};

} // namespace asiolink

#endif // __IO_FETCH_H
