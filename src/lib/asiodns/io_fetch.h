// Copyright (C) 2010-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IO_FETCH_H
#define IO_FETCH_H 1

#include <config.h>

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

// We want to use coroutine.hpp from the system's boost headers if possible.
// However, very old Boost versions (provided by RHEL 7 or CentOS 7) didn't have
// this header. So we can resort to our bundled version, but only if necessary.
#ifdef HAVE_BOOST_ASIO_COROUTINE_HPP
#include <boost/asio/coroutine.hpp>
#else
#include <ext/coroutine/coroutine.hpp>
#endif

#include <boost/system/error_code.hpp>
#include <asiolink/io_address.h>
#include <asiolink/io_service.h>

#include <util/buffer.h>
#include <dns/question.h>
#include <dns/message.h>

namespace isc {
namespace asiodns {

// Forward declarations
struct IOFetchData;

/// \brief Upstream Fetch Processing
///
/// IOFetch is the class used to send upstream fetches and to handle responses.
///
/// \param E Endpoint type to use.

class IOFetch : public boost::asio::coroutine {
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
    /// \param protocol Fetch protocol, either IOFetch::TCP or IOFetch::UDP
    /// \param service I/O Service object to handle the asynchronous
    ///        operations.
    /// \param question DNS question to send to the upstream server.
    /// \param address IP address of upstream server
    /// \param port Port to which to connect on the upstream server
    /// \param buff Output buffer into which the response (in wire format)
    ///        is written (if a response is received).
    /// \param cb Callback object containing the callback to be called when we
    ///        terminate.  The caller is responsible for managing this object
    ///        and deleting it if necessary.
    /// \param wait Timeout for the fetch (in ms).  The default value of
    ///        -1 indicates no timeout.
    /// \param edns true if the request should be EDNS. The default value is
    ///        true.
    IOFetch(Protocol protocol, isc::asiolink::IOService& service,
            const isc::dns::Question& question,
            const isc::asiolink::IOAddress& address,
            uint16_t port, isc::util::OutputBufferPtr& buff, Callback* cb,
            int wait = -1,
            bool edns = true);

    /// \brief Constructor
    ///  This constructor has one parameter "query_message", which
    ///  is the shared_ptr to a full query message. It's different
    ///  with above constructor which has only question section. All
    ///  other parameters are same.
    ///
    /// \param protocol Fetch protocol, either IOFetch::TCP or IOFetch::UDP
    /// \param service I/O Service object to handle the asynchronous
    ///        operations.
    /// \param query_message the shared_ptr to a full query message
    ///        got from a query client.
    /// \param address IP address of upstream server
    /// \param port Port to which to connect on the upstream server
    /// \param buff Output buffer into which the response (in wire format)
    ///        is written (if a response is received).
    /// \param cb Callback object containing the callback to be called when we
    ///        terminate.  The caller is responsible for managing this object
    ///        and deleting it if necessary.
    /// \param wait Timeout for the fetch (in ms).  The default value of
    ///        -1 indicates no timeout.
    IOFetch(Protocol protocol, isc::asiolink::IOService& service,
            isc::dns::ConstMessagePtr query_message,
            const isc::asiolink::IOAddress& address,
            uint16_t port, isc::util::OutputBufferPtr& buff, Callback* cb,
            int wait = -1);

    /// \brief Constructor.
    ///
    /// Creates the object that will handle the upstream fetch.
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
    IOFetch(Protocol protocol, isc::asiolink::IOService& service,
            isc::util::OutputBufferPtr& outpkt,
            const isc::asiolink::IOAddress& address,
            uint16_t port, isc::util::OutputBufferPtr& buff, Callback* cb,
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
    void operator()(boost::system::error_code ec = boost::system::error_code(), size_t length = 0);

    /// \brief Terminate query
    ///
    /// This method can be called at any point.  It terminates the current
    /// query with the specified reason.
    ///
    /// \param reason Reason for terminating the query
    void stop(Result reason = STOPPED);

private:
    /// \brief IOFetch Initialization Function.
    /// All the parameters are same with the constructor, except
    /// parameter "query_message"
    /// \param query_message the message to be sent out.
    void initIOFetch(isc::dns::MessagePtr& query_message, Protocol protocol,
                     isc::asiolink::IOService& service,
                     const isc::dns::Question& question,
                     const isc::asiolink::IOAddress& address, uint16_t port,
                     isc::util::OutputBufferPtr& buff, Callback* cb, int wait,
                     bool edns = true);

    /// \brief Log I/O Failure
    ///
    /// Records an I/O failure to the log file
    ///
    /// \param ec ASIO error code
    void logIOFailure(boost::system::error_code ec);

    // Member variables.  All data is in a structure pointed to by a shared
    // pointer.  The IOFetch object is copied a number of times during its
    // life, and only requiring a pointer to be copied reduces overhead.
    boost::shared_ptr<IOFetchData> data_;   ///< Private data
};

/// \brief Defines a pointer to an IOFetch.
typedef boost::shared_ptr<IOFetch> IOFetchPtr;

} // namespace asiodns
} // namespace isc

#endif // IO_FETCH_H
