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

#include <asio.hpp>
#include <asio/deadline_timer.hpp>
#include <asio/ip/address.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <log/dummylog.h>
#include <dns/opcode.h>
#include <dns/rcode.h>

#include <asiolink.h>
#include <internal/coroutine.h>
#include <internal/udpdns.h>
#include <internal/tcpdns.h>
#include <internal/ioquery.h>

using namespace asio;
using asio::ip::udp;
using asio::ip::tcp;
using isc::log::dlog;

using namespace std;
using namespace isc::dns;

namespace asiolink {

// Private UDPQuery data (see internal/udpdns.h for reasons)
struct UDPQuery::PrivateData {
    // UDP Socket we send query to and expect reply from there
    udp::socket socket;
    // Where was the query sent
    udp::endpoint remote;
    // What we ask the server
    Question question;
    // We will store the answer here
    OutputBufferPtr buffer;
    OutputBufferPtr msgbuf;
    // Temporary buffer for answer
    boost::shared_array<char> data;
    // This will be called when the data arrive or timeouts
    Callback* callback;
    // Did we already stop operating (data arrived, we timed out, someone
    // called stop). This can be so when we are cleaning up/there are
    // still pointers to us.
    bool stopped;
    // Timer to measure timeouts.
    deadline_timer timer;
    // How many milliseconds are we willing to wait for answer?
    int timeout;

    PrivateData(io_service& service,
        const udp::socket::protocol_type& protocol, const Question &q,
        OutputBufferPtr b, Callback *c) :
        socket(service, protocol),
        question(q),
        buffer(b),
        msgbuf(new OutputBuffer(512)),
        callback(c),
        stopped(false),
        timer(service)
    { }
};

/// The following functions implement the \c UDPQuery class.
///
/// The constructor
UDPQuery::UDPQuery(io_service& io_service,
                   const Question& q, const IOAddress& addr, uint16_t port,
                   OutputBufferPtr buffer, Callback *callback, int timeout) :
    data_(new PrivateData(io_service,
        addr.getFamily() == AF_INET ? udp::v4() : udp::v6(), q, buffer,
        callback))
{
    data_->remote = UDPEndpoint(addr, port).getASIOEndpoint();
    data_->timeout = timeout;
}

/// The function operator is implemented with the "stackless coroutine"
/// pattern; see internal/coroutine.h for details.
void
UDPQuery::operator()(error_code ec, size_t length) {
    if (ec || data_->stopped) {
        return;
    }

    CORO_REENTER (this) {
        /// Generate the upstream query and render it to wire format
        /// This is done in a different scope to allow inline variable
        /// declarations.
        {
            Message msg(Message::RENDER);
            
            // XXX: replace with boost::random or some other suitable PRNG
            msg.setQid(0);
            msg.setOpcode(Opcode::QUERY());
            msg.setRcode(Rcode::NOERROR());
            msg.setHeaderFlag(Message::HEADERFLAG_RD);
            msg.addQuestion(data_->question);
            MessageRenderer renderer(*data_->msgbuf);
            msg.toWire(renderer);
            dlog("Sending " + msg.toText() + " to " +
                data_->remote.address().to_string());
        }


        // If we timeout, we stop, which will shutdown everything and
        // cancel all other attempts to run inside the coroutine
        if (data_->timeout != -1) {
            data_->timer.expires_from_now(boost::posix_time::milliseconds(
                data_->timeout));
            data_->timer.async_wait(boost::bind(&UDPQuery::stop, *this,
                TIME_OUT));
        }

        // Begin an asynchronous send, and then yield.  When the
        // send completes, we will resume immediately after this point.
        CORO_YIELD data_->socket.async_send_to(buffer(data_->msgbuf->getData(),
            data_->msgbuf->getLength()), data_->remote, *this);

        /// Allocate space for the response.  (XXX: This should be
        /// optimized by maintaining a free list of pre-allocated blocks)
        data_->data.reset(new char[MAX_LENGTH]);

        /// Begin an asynchronous receive, and yield.  When the receive
        /// completes, we will resume immediately after this point.
        CORO_YIELD data_->socket.async_receive_from(buffer(data_->data.get(),
            MAX_LENGTH), data_->remote, *this);
        // The message is not rendered yet, so we can't print it easilly
        dlog("Received response from " + data_->remote.address().to_string());

        /// Copy the answer into the response buffer.  (XXX: If the
        /// OutputBuffer object were made to meet the requirements of
        /// a MutableBufferSequence, then it could be written to directly
        /// by async_recieve_from() and this additional copy step would
        /// be unnecessary.)
        data_->buffer->writeData(data_->data.get(), length);

        /// We are done
        stop(SUCCESS);
    }
}

void
UDPQuery::stop(Result result) {
    if (!data_->stopped) {
        switch (result) {
            case TIME_OUT:
                dlog("Query timed out");
                break;
            case STOPPED:
                dlog("Query stopped");
                break;
            default:;
        }
        data_->stopped = true;
        data_->socket.cancel();
        data_->socket.close();
        data_->timer.cancel();
        if (data_->callback) {
            (*data_->callback)(result);
        }
    }
}

}
