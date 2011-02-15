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

#include <config.h>

#include <unistd.h>             // for some IPC/network system calls
#include <sys/socket.h>
#include <netinet/in.h>

#include <asio.hpp>
#include <asio/deadline_timer.hpp>
#include <asio/ip/address.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <log/dummylog.h>
#include <dns/opcode.h>
#include <dns/rcode.h>

#include <asiolink.h>
#include <coroutine.h>
#include <internal/udpdns.h>
#include <internal/tcpdns.h>
#include <internal/iofetch.h>

using namespace asio;
using asio::ip::udp;
using asio::ip::tcp;
using isc::log::dlog;

using namespace std;
using namespace isc::dns;

namespace asiolink {

// Constructor for the IOFetchData member

/// \brief Constructor
///
/// Just fills in the data members of the IOFetchData structure
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

IOFetch::IOFetchData::IOFetchData(IOService& io_service,
    const isc::dns::Question& query, const IOAddress& address, uint16_t port,
    isc::dns::OutputBufferPtr buff, Callback* cb, int wait, int protocol)
        :
    socket((protocol == IPPROTO_UDP) ?
        static_cast<IOSocket*>(new UDPSocket(io_service, address)) :
        static_cast<IOSocket*>(new TCPSocket(io_service, address))
    ),
    remote((protocol == IPPROTO_UDP) ?
        static_cast<IOEndpoint*>(new UDPEndpoint(address, port)) :
        static_cast<IOEndpoint*>(new TCPEndpoint(address, port))
    ),
    question(query),
    buffer(buff),
    msgbuf(new OutputBuffer(512)),         // TODO: Why this number?
    data(new char[IOFetch::MAX_LENGTH]),
    callback(cb),
    stopped(false),
    timer(io_service.get_io_service()),
    timeout(wait)
{
}



/// IOFetch Constructor - just initialize the private data
IOFetch::IOFetch(IOService& io_service, const Question& question,
    const IOAddress& address, uint16_t port, OutputBufferPtr buffer,
    Callback *callback, int timeout, int protocol) :
        data_(new IOFetch::IOFetchData(io_service, question, address, port,
            buffer, callback, timeout, protocol)
        )
{
}

/// The function operator is implemented with the "stackless coroutine"
/// pattern; see internal/coroutine.h for details.
void
IOFetch::operator()(error_code ec, size_t length) {
    if (ec || data_->stopped) {
        return;
    }

    CORO_REENTER (this) {
        /// Generate the upstream query and render it to wire format
        /// This is done in a different scope to allow inline variable
        /// declarations.
        {
            Message msg(Message::RENDER);
            
            // TODO: replace with boost::random or some other suitable PRNG
            msg.setQid(0);
            msg.setOpcode(Opcode::QUERY());
            msg.setRcode(Rcode::NOERROR());
            msg.setHeaderFlag(Message::HEADERFLAG_RD);
            msg.addQuestion(data_->question);
            MessageRenderer renderer(*data_->msgbuf);
            msg.toWire(renderer);
            dlog("Sending " + msg.toText() + " to " +
                data_->remote->getAddress().toText());
        }


        // If we timeout, we stop, which will shutdown everything and
        // cancel all other attempts to run inside the coroutine
        if (data_->timeout != -1) {
            data_->timer.expires_from_now(boost::posix_time::milliseconds(
                data_->timeout));
            data_->timer.async_wait(boost::bind(&IOFetch::stop, *this,
                TIME_OUT));
        }

        // Open a connection to the target system.  For speed, if the operation
        // was a no-op (i.e. UDP operation) we bypass the yield.
        bool do_yield = data_->socket->open(data->remote.get(), *this);
        if (do_yield) {
            CORO_YIELD;
        }

        // Begin an asynchronous send, and then yield.  When the
        // send completes, we will resume immediately after this point.
        CORO_YIELD data_->socket->async_send(data_->msgbuf->getData(),
            data_->msgbuf->getLength(), data_->remote.get(), *this);

        /// Allocate space for the response.  (XXX: This should be
        /// optimized by maintaining a free list of pre-allocated blocks)
        data_->data.reset(new char[MAX_LENGTH]);

        /// Begin an asynchronous receive, and yield.  When the receive
        /// completes, we will resume immediately after this point.
        CORO_YIELD data_->socket->async_receive(data_->data.get(),
            static_cast<size_t>(MAX_LENGTH), data_->remote.get(), *this);

        // The message is not rendered yet, so we can't print it easilly
        dlog("Received response from " + data_->remote->getAddress().toText());

        /// Copy the answer into the response buffer.  (TODO: If the
        /// OutputBuffer object were made to meet the requirements of
        /// a MutableBufferSequence, then it could be written to directly
        /// by async_receive_from() and this additional copy step would
        /// be unnecessary.)
        data_->buffer->writeData(data_->data.get(), length);

        // Finished with this socket, so close it.
        data_->socket->close();

        /// We are done
        stop(SUCCESS);
    }
}

// Function that stops the coroutine sequence.  It is called either when the
// query finishes or when the timer times out.  Either way, it sets the
// "stopped_" flag and cancels anything that is in progress.
//
// As the function may be entered multiple times as things wind down, the
// stopped_ flag checks if stop() has already been called.  If it has,
// subsequent calls are no-ops.
void
IOFetch::stop(Result result) {
    if (!data_->stopped) {
        switch (result) {
            case TIME_OUT:
                dlog("Query timed out");
                break;

            case STOPPED:
                dlog("Query stopped");
                break;

            default:
                ;
        }
        data_->stopped = true;
        data_->socket->cancel();    // Cancel outstanding I/O
        data_->socket->close();     // ... and close the socket
        data_->timer.cancel();      // Cancel timeout timer

        if (data_->callback) {
            (*(data_->callback))(result);   // Call callback
        }
    }
}

} // namespace asiolink
