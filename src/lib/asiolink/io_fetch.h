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

#ifndef __IOFETCH_H
#define __IOFETCH_H 1

#include <netinet/in.h>

#include <config.h>

#include <asio.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <asio/deadline_timer.hpp>

#include <dns/buffer.h>
#include <dns/question.h>

#include <asiolink/asiolink.h>
#include <asiolink/ioaddress.h>
#include <asiolink/iocompletioncb.h>
#include <asiolink/iocompletioncb.h>


#include <asiolink/iosocket.h>
#include <asiolink/ioendpoint.h>
#include <coroutine.h>



namespace asiolink {

/// \brief Upstream Fetch Processing
///
/// IOFetch is the class used to send upstream fetches and to handle responses.
/// It is a base class containing most of the logic, although the ASIO will
/// actually instantiate one of the derived classes TCPFetch or UDPFetch.
/// (These differ in the type of socket and endpoint.)
class IOFetch : public IOCompletionCallback  {
public:

    /// \brief Result of Upstream Fetch
    ///
    /// Note that this applies to the status of I/Os in the fetch - a fetch
    /// that resulted in a packet being received from the server is a SUCCESS,
    /// even if the contents of the packet indicate that some error occurred.
    enum Result {
        SUCCESS = 0,        ///< Success, fetch completed
        TIME_OUT,           ///< Failure, fetch timed out
        STOPPED             ///< Control code, fetch has been stopped
    };
    // The next enum is a "trick" to allow constants to be defined in a class
    // declaration.

    /// \brief Integer Constants
    enum {
        MAX_LENGTH = 4096   ///< Maximum size of receive buffer
    };
    /// \brief I/O Fetch Callback
    ///
    /// Callback object for when the fetch itself has completed.  Note that this
    /// is different to the IOCompletionCallback; that is used to signal the
    /// completion of an asynchronous I/O call.  The IOFetch::Callback is called
    /// when an upstream fetch - which may have involved several asynchronous
    /// I/O operations - has completed.
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

        /// \brief Callback method called when the fetch completes
        ///
        /// \brief result Result of the fetch
        virtual void operator()(Result result) = 0;
    };

    /// \brief IOFetch Data
    ///
    /// The data for IOFetch is held in a separate struct pointed to by a
    /// shared_ptr object.  This is because the IOFetch object will be copied
    /// often (it is used as a coroutine and passed as callback to many async_*()
    /// functions) and we want keep the same data).  Organising the data this
    /// way keeps copying to a minimum.
    struct IOFetchData {

        // The next two members are shared pointers to a base class because what
        // is actually instantiated depends on whether the fetch is over UDP or
        // TCP, which is not known until construction of the IOFetch.  Use of
        // a shared pointer here is merely to ensure deletion when the data
        // object is deleted.
        boost::shared_ptr<IOSocket> socket;     ///< Socket to use for I/O
        boost::shared_ptr<IOEndpoint> remote;   ///< Where the fetch was sent

        isc::dns::Question          question;   ///< Question to be asked
        isc::dns::OutputBufferPtr   buffer;     ///< Received data held here
        isc::dns::OutputBufferPtr   msgbuf;     ///< ... and here
        boost::shared_array<char>   data;       ///< Temporary array for the data
        Callback*                   callback;   ///< Called on I/O Completion
        bool                        stopped;    ///< Have we stopped running?
        asio::deadline_timer        timer;      ///< Timer to measure timeouts
        int                         timeout;    ///< Timeout in ms

        /// \brief Constructor
        ///
        /// Just fills in the data members of the IOFetchData structure
        ///
        /// \param io_service I/O Service object to handle the asynchronous
        ///     operations.
        /// \param query DNS question to send to the upstream server.
        /// \param address IP address of upstream server
        /// \param port Port to use for the query
        /// \param buff Output buffer into which the response (in wire format)
        ///     is written (if a response is received).
        /// \param cb Callback object containing the callback to be called
        ///     when we terminate.  The caller is responsible for managing this
        ///     object and deleting it if necessary.
        /// \param wait Timeout for the fetch (in ms).  The default value of
        ///     -1 indicates no timeout.
        /// \param protocol Protocol to use for the fetch.  The default is UDP

        IOFetchData(IOService& io_service, const isc::dns::Question& query,
            const IOAddress& address, uint16_t port,
            isc::dns::OutputBufferPtr buff, Callback* cb, int wait = -1,
            int protocol = IPPROTO_UDP);
    };

    /// \brief Constructor.
    ///
    /// Creates the object that will handle the upstream fetch.
    ///
    /// \param io_service I/O Service object to handle the asynchronous
    ///     operations.
    /// \param question DNS question to send to the upstream server.
    /// \param address IP address of upstream server
    /// \param port Port to use for the query
    /// \param buffer Output buffer into which the response (in wire format)
    ///     is written (if a response is received).
    /// \param callback Callback object containing the callback to be called
    ///     when we terminate.  The caller is responsible for managing this
    ///     object and deleting it if necessary.
    /// \param timeout Timeout for the fetch (in ms).  The default value of
    ///     -1 indicates no timeout.
    /// \param protocol Protocol to use for the fetch.  The default is UDP
    IOFetch(IOService& io_service, const isc::dns::Question& question,
        const IOAddress& address, uint16_t port,
        isc::dns::OutputBufferPtr buffer, Callback* callback,
        int timeout = -1, int protocol = IPPROTO_UDP);


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
    boost::shared_ptr<IOFetchData> data_;   ///< Private data
};

}


#endif // __IOFETCH_H
