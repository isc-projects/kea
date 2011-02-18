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

#include <boost/bind.hpp>

#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <log/dummylog.h>

#include <asio.hpp>
#include <asiolink/io_fetch.h>

using namespace asio;
using namespace isc::dns;
using namespace isc::log;
using namespace std;

namespace asiolink {

/// IOFetch Constructor - just initialize the private data

IOFetch::IOFetch(int protocol, IOService& service,
    const isc::dns::Question& question, const IOAddress& address, uint16_t port,
    isc::dns::OutputBufferPtr& buff, Callback* cb, int wait)
    :
    data_(new IOFetch::IOFetchData(protocol, service, question, address,
        port, buff, cb, wait))
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

            // As this is a new fetch, clear the amount of data received
            data_->cumulative = 0;

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
        // was completed synchronously (i.e. UDP operation) we bypass the yield.
        if (data_->socket->open(data_->remote.get(), *this)) {
            CORO_YIELD;
        }

        // Begin an asynchronous send, and then yield.  When the send completes
        // send completes, we will resume immediately after this point.
        CORO_YIELD data_->socket->asyncSend(data_->msgbuf->getData(),
            data_->msgbuf->getLength(), data_->remote.get(), *this);

        // Now receive the response.  Since TCP may not receive the entire
        // message in one operation, we need to loop until we have received
        // it. (This can't be done within the asyncReceive() method because
        // each I/O operation will be done asynchronously and between each one
        // we need to yield ... and we *really* don't want to set up another
        // coroutine within that method.)  So after each receive (and yield),
        // we check if the operation is complete and if not, loop to read again.
        do {
            CORO_YIELD data_->socket->asyncReceive(data_->data.get(),
                static_cast<size_t>(MAX_LENGTH), data_->cumulative,
                data_->remote.get(), *this);
        } while (!data_->socket->receiveComplete(data_->data.get(), length,
            data_->cumulative));

        // The message is not rendered yet, so we can't print it easily
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

        // Stop requested, cancel and I/O's on the socket and shut it down,
        // and cancel the timer.
        data_->socket->cancel();
        data_->socket->close();

        data_->timer.cancel();

        // Execute the I/O completion callback (if present).
        if (data_->callback) {
            (*(data_->callback))(result);
        }

        // Mark that stop() has now been called.
        data_->stopped = true;
    }
}

} // namespace asiolink

