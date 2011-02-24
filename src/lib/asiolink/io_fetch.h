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

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>             // for some IPC/network system calls

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <asio/deadline_timer.hpp>

#include <coroutine.h>

#include <dns/buffer.h>
#include <dns/question.h>

#include <asiolink/io_asio_socket.h>
#include <asiolink/io_endpoint.h>
#include <asiolink/io_service.h>
#include <asiolink/tcp_socket.h>
#include <asiolink/tcp_endpoint.h>
#include <asiolink/udp_socket.h>
#include <asiolink/udp_endpoint.h>


namespace asiolink {


/// \brief Upstream Fetch Processing
///
/// IOFetch is the class used to send upstream fetches and to handle responses.
///
/// \param E Endpoint type to use.

class IOFetch : public coroutine {
public:
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
        TIME_OUT,           ///< Failure, fetch timed out
        STOPPED,            ///< Control code, fetch has been stopped
        NOTSET              ///< For testing, indicates value not set
    };

    // The next enum is a "trick" to allow constants to be defined in a class
    // declaration.

    /// \brief Integer Constants
    enum {
        MAX_LENGTH = 4096   ///< Maximum size of receive buffer
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

        /// \brief Callback method called when the fetch completes   /// \brief Origin of Asynchronous I/O Call
    ///

    // The next enum is a "trick" to allow constants to be defined in a class
    // declaration.

        ///
        /// \brief result Result of the fetch
        virtual void operator()(Result result) = 0;
    };

    /// \brief IOFetch Data
    ///
    /// The data for IOFetch is held in a separate struct pointed to by a
    /// shared_ptr object.  This is because the IOFetch object will be copied
    /// often (it is used as a coroutine and passed as callback to many
    /// async_*() functions) and we want keep the same data).  Organising the
    /// data in this way keeps copying to a minimum.
    struct IOFetchData {

        // The next two members are shared pointers to a base class because what
        // is actually instantiated depends on whether the fetch is over UDP or
        // TCP, which is not known until construction of the IOFetch.  Use of
        // a shared pointer here is merely to ensure deletion when the data
        // object is deleted.
        boost::shared_ptr<IOAsioSocket<IOFetch> > socket;
                                                ///< Socket to use for I/O
        boost::shared_ptr<IOEndpoint> remote;   ///< Where the fetch was sent
        isc::dns::Question          question;   ///< Question to be asked
        isc::dns::OutputBufferPtr   msgbuf;     ///< Wire buffer for question
        isc::dns::OutputBufferPtr   buffer;     ///< Received data held here
        boost::shared_array<char>   data;       ///< Temporary array for data
        IOFetch::Callback*          callback;   ///< Called on I/O Completion
        size_t                      cumulative; ///< Cumulative received amount
        bool                        stopped;    ///< Have we stopped running?
        asio::deadline_timer        timer;      ///< Timer to measure timeouts
        int                         timeout;    ///< Timeout in ms
        Origin                      origin;     ///< Origin of last asynchronous I/O

        /// \brief Constructor
        ///
        /// Just fills in the data members of the IOFetchData structure
        ///
        /// \param proto either IPPROTO_UDP or IPPROTO_TCP
        /// \param service I/O Service object to handle the asynchronous
        ///     operations.
        /// \param query DNS question to send to the upstream server.
        /// \param address IP address of upstream server
        /// \param port Port to use for the query
        /// \param buff Output buffer into which the response (in wire format)
        ///     is written (if a response is received).
        /// \param cb Callback object containing the callback to be called
        ///     when we terminate.  The caller is responsible for managing this
        ///     object and deleting it if necessary.
        /// \param wait Timeout for the fetch (in ms).
        ///
        /// TODO: May need to alter constructor (see comment 4 in Trac ticket #554)
        IOFetchData(int proto, IOService& service,
            const isc::dns::Question& query, const IOAddress& address,
            uint16_t port, isc::dns::OutputBufferPtr& buff, Callback* cb,
            int wait)
            :
            socket((proto == IPPROTO_UDP) ?
                static_cast<IOAsioSocket<IOFetch>*>(
                    new UDPSocket<IOFetch>(service)) :
                static_cast<IOAsioSocket<IOFetch>*>(
                    new TCPSocket<IOFetch>(service))
                ),
            remote((proto == IPPROTO_UDP) ?
                static_cast<IOEndpoint*>(new UDPEndpoint(address, port)) :
                static_cast<IOEndpoint*>(new TCPEndpoint(address, port))
                ),
            question(query),
            msgbuf(new isc::dns::OutputBuffer(512)),
            buffer(buff),
            data(new char[IOFetch::MAX_LENGTH]),
            callback(cb),
            cumulative(0),
            stopped(false),
            timer(service.get_io_service()),
            timeout(wait),
            origin(NONE)
        {}
    };

    /// \brief Constructor.
    ///
    /// Creates the object that will handle the upstream fetch.
    ///
    /// TODO: Need to randomise the source port
    ///
    /// \param protocol Fetch protocol, either IPPROTO_UDP or IPPROTO_TCP
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
    IOFetch(int protocol, IOService& service,
        const isc::dns::Question& question, const IOAddress& address,
        uint16_t port, isc::dns::OutputBufferPtr& buff, Callback* cb,
        int wait = -1);
    
    /// \brief Coroutine entry point
    ///
    /// The operator() method is the method in which the coroutine code enters
    /// this object when an operation has been completed.
    ///
    /// \param ec Error code, the result of the last asynchronous I/O operation.
    /// \param length Amount of data received on the last asynchronous read
    void operator()(asio::error_code ec = asio::error_code(),
        size_t length = 0);

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
    void logIOFailure(asio::error_code& ec);

    boost::shared_ptr<IOFetchData>  data_;   ///< Private data

};

} // namespace asiolink

#endif // __IO_FETCH_H
