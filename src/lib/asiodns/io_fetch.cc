// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <unistd.h>             // for some IPC/network system calls
#include <netinet/in.h>
#include <stdint.h>
#include <sys/socket.h>

#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>

#include <asiolink/io_address.h>
#include <asiolink/io_asio_socket.h>
#include <asiolink/io_endpoint.h>
#include <asiolink/io_service.h>
#include <asiolink/tcp_endpoint.h>
#include <asiolink/tcp_socket.h>
#include <asiolink/udp_endpoint.h>
#include <asiolink/udp_socket.h>

#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/rcode.h>

#include <asiodns/io_fetch.h>

#include <util/buffer.h>
#include <util/random/qid_gen.h>

#include <asiodns/logger.h>

using namespace boost::asio;
using namespace isc::asiolink;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::util::random;
using namespace isc::log;
using namespace std;

namespace isc {
namespace asiodns {

// Log debug verbosity

const int DBG_IMPORTANT = DBGLVL_TRACE_BASIC;
const int DBG_COMMON = DBGLVL_TRACE_DETAIL;
const int DBG_ALL = DBGLVL_TRACE_DETAIL + 20;

/// \brief IOFetch Data
///
/// The data for IOFetch is held in a separate struct pointed to by a shared_ptr
/// object.  This is because the IOFetch object will be copied often (it is used
/// as a coroutine and passed as callback to many async_*() functions) and we
/// want keep the same data).  Organising the data in this way keeps copying to
/// a minimum.
struct IOFetchData {

    // The first two members are shared pointers to a base class because what is
    // actually instantiated depends on whether the fetch is over UDP or TCP,
    // which is not known until construction of the IOFetch.  Use of a shared
    // pointer here is merely to ensure deletion when the data object is deleted.
    boost::scoped_ptr<IOAsioSocket<IOFetch> > socket;
                                             ///< Socket to use for I/O
    boost::scoped_ptr<IOEndpoint> remote_snd;///< Where the fetch is sent
    boost::scoped_ptr<IOEndpoint> remote_rcv;///< Where the response came from
    OutputBufferPtr   msgbuf;      ///< Wire buffer for question
    OutputBufferPtr   received;    ///< Received data put here
    IOFetch::Callback*          callback;    ///< Called on I/O Completion
    boost::asio::deadline_timer timer;       ///< Timer to measure timeouts
    IOFetch::Protocol           protocol;    ///< Protocol being used
    size_t                      cumulative;  ///< Cumulative received amount
    size_t                      expected;    ///< Expected amount of data
    size_t                      offset;      ///< Offset to receive data
    bool                        stopped;     ///< Have we stopped running?
    int                         timeout;     ///< Timeout in ms
    bool                        packet;      ///< true if packet was supplied

    // In case we need to log an error, the origin of the last asynchronous
    // I/O is recorded.  To save time and simplify the code, this is recorded
    // as the ID of the error message that would be generated if the I/O failed.
    // This means that we must make sure that all possible "origins" take the
    // same arguments in their message in the same order.
    isc::log::MessageID         origin;     ///< Origin of last asynchronous I/O
    uint8_t                     staging[IOFetch::STAGING_LENGTH];
                                            ///< Temporary array for received data
    isc::dns::qid_t             qid;         ///< The QID set in the query

    /// \brief Constructor
    ///
    /// Just fills in the data members of the IOFetchData structure
    ///
    /// \param proto Either IOFetch::TCP or IOFetch::UDP.
    /// \param service I/O Service object to handle the asynchronous
    ///        operations.
    /// \param address IP address of upstream server
    /// \param port Port to use for the query
    /// \param buff Output buffer into which the response (in wire format)
    ///        is written (if a response is received).
    /// \param cb Callback object containing the callback to be called
    ///        when we terminate.  The caller is responsible for managing this
    ///        object and deleting it if necessary.
    /// \param wait Timeout for the fetch (in ms).
    ///
    /// TODO: May need to alter constructor (see comment 4 in Trac ticket #554)
    IOFetchData(IOFetch::Protocol proto, IOService& service,
        const IOAddress& address, uint16_t port, OutputBufferPtr& buff,
        IOFetch::Callback* cb, int wait)
        :
        socket((proto == IOFetch::UDP) ?
            static_cast<IOAsioSocket<IOFetch>*>(
                new UDPSocket<IOFetch>(service)) :
            static_cast<IOAsioSocket<IOFetch>*>(
                new TCPSocket<IOFetch>(service))
            ),
        remote_snd((proto == IOFetch::UDP) ?
            static_cast<IOEndpoint*>(new UDPEndpoint(address, port)) :
            static_cast<IOEndpoint*>(new TCPEndpoint(address, port))
            ),
        remote_rcv((proto == IOFetch::UDP) ?
            static_cast<IOEndpoint*>(new UDPEndpoint(address, port)) :
            static_cast<IOEndpoint*>(new TCPEndpoint(address, port))
            ),
        msgbuf(new OutputBuffer(512)),
        received(buff),
        callback(cb),
        timer(service.get_io_service()),
        protocol(proto),
        cumulative(0),
        expected(0),
        offset(0),
        stopped(false),
        timeout(wait),
        packet(false),
        origin(ASIODNS_UNKNOWN_ORIGIN),
        staging(),
        qid(QidGenerator::getInstance().generateQid())
    {}

    // Checks if the response we received was ok;
    // - data contains the buffer we read, as well as the address
    // we sent to and the address we received from.
    // length is provided by the operator() in IOFetch.
    // Addresses must match, number of octets read must be at least
    // 2, and the first two octets must match the qid of the message
    // we sent.
    bool responseOK() {
        return (*remote_snd == *remote_rcv && cumulative >= 2 &&
                readUint16(received->getData(), received->getLength()) == qid);
    }
};

/// IOFetch Constructor - just initialize the private data

IOFetch::IOFetch(Protocol protocol, IOService& service,
    const isc::dns::Question& question, const IOAddress& address,
    uint16_t port, OutputBufferPtr& buff, Callback* cb, int wait, bool edns)
{
    MessagePtr query_msg(new Message(Message::RENDER));
    initIOFetch(query_msg, protocol, service, question, address, port, buff,
                cb, wait, edns);
}

IOFetch::IOFetch(Protocol protocol, IOService& service,
    OutputBufferPtr& outpkt, const IOAddress& address, uint16_t port,
    OutputBufferPtr& buff, Callback* cb, int wait)
    :
    data_(new IOFetchData(protocol, service,
          address, port, buff, cb, wait))
{
    data_->msgbuf = outpkt;
    data_->packet = true;
}

IOFetch::IOFetch(Protocol protocol, IOService& service,
    ConstMessagePtr query_message, const IOAddress& address, uint16_t port,
    OutputBufferPtr& buff, Callback* cb, int wait)
{
    MessagePtr msg(new Message(Message::RENDER));

    msg->setHeaderFlag(Message::HEADERFLAG_RD,
                       query_message->getHeaderFlag(Message::HEADERFLAG_RD));
    msg->setHeaderFlag(Message::HEADERFLAG_CD,
                       query_message->getHeaderFlag(Message::HEADERFLAG_CD));

    initIOFetch(msg, protocol, service,
                **(query_message->beginQuestion()),
                address, port, buff, cb, wait);
}

void
IOFetch::initIOFetch(MessagePtr& query_msg, Protocol protocol,
                     IOService& service,
                     const isc::dns::Question& question,
                     const IOAddress& address, uint16_t port,
                     OutputBufferPtr& buff, Callback* cb, int wait, bool edns)
{
    data_ = boost::shared_ptr<IOFetchData>(new IOFetchData(
        protocol, service, address, port, buff, cb, wait));

    query_msg->setQid(data_->qid);
    query_msg->setOpcode(Opcode::QUERY());
    query_msg->setRcode(Rcode::NOERROR());
    query_msg->setHeaderFlag(Message::HEADERFLAG_RD);
    query_msg->addQuestion(question);

    if (edns) {
        EDNSPtr edns_query(new EDNS());
        edns_query->setUDPSize(Message::DEFAULT_MAX_EDNS0_UDPSIZE);
        query_msg->setEDNS(edns_query);
    }

    MessageRenderer renderer;
    renderer.setBuffer(data_->msgbuf.get());
    query_msg->toWire(renderer);
    renderer.setBuffer(NULL);
}

// Return protocol in use.

IOFetch::Protocol
IOFetch::getProtocol() const {
    return (data_->protocol);
}

/// The function operator is implemented with the "stackless coroutine"
/// pattern; see internal/coroutine.h for details.

void
IOFetch::operator()(boost::system::error_code ec, size_t length) {

    if (data_->stopped) {
        return;
    } else if (ec) {
        logIOFailure(ec);
        return;
    }

    CORO_REENTER (this) {

        /// Generate the upstream query and render it to wire format
        /// This is done in a different scope to allow inline variable
        /// declarations.
        {
            if (data_->packet) {
                // A packet was given, overwrite the QID (which is in the
                // first two bytes of the packet).
                data_->msgbuf->writeUint16At(data_->qid, 0);

            } 
        }

        // If we timeout, we stop, which will can cancel outstanding I/Os and
        // shutdown everything.
        if (data_->timeout != -1) {
            data_->timer.expires_from_now(boost::posix_time::milliseconds(
                data_->timeout));
            data_->timer.async_wait(boost::bind(&IOFetch::stop, *this,
                TIME_OUT));
        }

        // Open a connection to the target system.  For speed, if the operation
        // is synchronous (i.e. UDP operation) we bypass the yield.
        data_->origin = ASIODNS_OPEN_SOCKET;
        if (data_->socket->isOpenSynchronous()) {
            data_->socket->open(data_->remote_snd.get(), *this);
        } else {
            CORO_YIELD data_->socket->open(data_->remote_snd.get(), *this);
        }

        do {
            // Begin an asynchronous send, and then yield.  When the send completes,
            // we will resume immediately after this point.
            data_->origin = ASIODNS_SEND_DATA;
            CORO_YIELD data_->socket->asyncSend(data_->msgbuf->getData(),
                data_->msgbuf->getLength(), data_->remote_snd.get(), *this);
    
            // Now receive the response.  Since TCP may not receive the entire
            // message in one operation, we need to loop until we have received
            // it. (This can't be done within the asyncReceive() method because
            // each I/O operation will be done asynchronously and between each one
            // we need to yield ... and we *really* don't want to set up another
            // coroutine within that method.)  So after each receive (and yield),
            // we check if the operation is complete and if not, loop to read again.
            //
            // Another concession to TCP is that the amount of is contained in the
            // first two bytes.  This leads to two problems:
            //
            // a) We don't want those bytes in the return buffer.
            // b) They may not both arrive in the first I/O.
            //
            // So... we need to loop until we have at least two bytes, then store
            // the expected amount of data.  Then we need to loop until we have
            // received all the data before copying it back to the user's buffer.
            // And we want to minimise the amount of copying...
    
            data_->origin = ASIODNS_READ_DATA;
            data_->cumulative = 0;          // No data yet received
            data_->offset = 0;              // First data into start of buffer
            data_->received->clear();       // Clear the receive buffer
            do {
                CORO_YIELD data_->socket->asyncReceive(data_->staging,
                                                       static_cast<size_t>(STAGING_LENGTH),
                                                       data_->offset,
                                                       data_->remote_rcv.get(), *this);
            } while (!data_->socket->processReceivedData(data_->staging, length,
                                                         data_->cumulative, data_->offset,
                                                         data_->expected, data_->received));
        } while (!data_->responseOK());

        // Finished with this socket, so close it.  This will not generate an
        // I/O error, but reset the origin to unknown in case we change this.
        data_->origin = ASIODNS_UNKNOWN_ORIGIN;
        data_->socket->close();

        /// We are done
        stop(SUCCESS);
    }
}

// Function that stops the coroutine sequence.  It is called either when the
// query finishes or when the timer times out.  Either way, it sets the
// "stopped_" flag and cancels anything that is in progress.
//
// As the function may be entered multiple times as things wind down, it checks
// if the stopped_ flag is already set.  If it is, the call is a no-op.

void
IOFetch::stop(Result result) {

    if (!data_->stopped) {

        // Mark the fetch as stopped to prevent other completion callbacks
        // (invoked because of the calls to cancel()) from executing the
        // cancel calls again.
        //
        // In a single threaded environment, the callbacks won't be invoked
        // until this one completes. In a multi-threaded environment, they may
        // well be, in which case the testing (and setting) of the stopped_
        // variable should be done inside a mutex (and the stopped_ variable
        // declared as "volatile").
        //
        // TODO: Update testing of stopped_ if threads are used.
        data_->stopped = true;
        switch (result) {
            case TIME_OUT:
                LOG_DEBUG(logger, DBG_COMMON, ASIODNS_READ_TIMEOUT).
                    arg(data_->remote_snd->getAddress().toText()).
                    arg(data_->remote_snd->getPort());
                break;

            case SUCCESS:
                LOG_DEBUG(logger, DBG_ALL, ASIODNS_FETCH_COMPLETED).
                    arg(data_->remote_rcv->getAddress().toText()).
                    arg(data_->remote_rcv->getPort());
                break;

            case STOPPED:
                // Fetch has been stopped for some other reason.  This is
                // allowed but as it is unusual it is logged, but with a lower
                // debug level than a timeout (which is totally normal).
                LOG_DEBUG(logger, DBG_IMPORTANT, ASIODNS_FETCH_STOPPED).
                    arg(data_->remote_snd->getAddress().toText()).
                    arg(data_->remote_snd->getPort());
                break;

            default:
                LOG_ERROR(logger, ASIODNS_UNKNOWN_RESULT).
                    arg(data_->remote_snd->getAddress().toText()).
                    arg(data_->remote_snd->getPort());
        }

        // Stop requested, cancel and I/O's on the socket and shut it down,
        // and cancel the timer.
        data_->socket->cancel();
        data_->socket->close();

        data_->timer.cancel();

        // Execute the I/O completion callback (if present).
        if (data_->callback) {
            (*(data_->callback))(result);
        }
    }
}

// Log an error - called on I/O failure

void IOFetch::logIOFailure(boost::system::error_code ec) {

    // Should only get here with a known error code.
    assert((data_->origin == ASIODNS_OPEN_SOCKET) ||
           (data_->origin == ASIODNS_SEND_DATA) ||
           (data_->origin == ASIODNS_READ_DATA) ||
           (data_->origin == ASIODNS_UNKNOWN_ORIGIN));

    LOG_ERROR(logger, data_->origin).arg(ec.value()).
        arg((data_->remote_snd->getProtocol() == IPPROTO_TCP) ?
                     "TCP" : "UDP").
        arg(data_->remote_snd->getAddress().toText()).
        arg(data_->remote_snd->getPort());
}

} // namespace asiodns
} // namespace isc {
