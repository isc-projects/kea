// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <d2/dns_client.h>
#include <dns/messagerenderer.h>

namespace isc {
namespace d2 {

namespace {

// OutputBuffer objects are pre-allocated before data is written to them.
// This is a default number of bytes for the buffers we create within
// DNSClient class.
const size_t DEFAULT_BUFFER_SIZE = 128;

}

using namespace isc::util;
using namespace isc::asiolink;
using namespace isc::asiodns;

DNSClient::DNSClient(D2UpdateMessagePtr& response_placeholder,
                     Callback* callback)
    : in_buf_(new OutputBuffer(DEFAULT_BUFFER_SIZE)),
      response_(response_placeholder), callback_(callback) {
    if (!response_) {
        isc_throw(BadValue, "a pointer to an object to encapsulate the DNS"
                  " server must be provided; found NULL value");
    }
}

void
DNSClient::operator()(IOFetch::Result result) {
    // @todo More sanity checks here. Also, there is a question, what happens if
    // the exception is thrown here.

    if (result == IOFetch::SUCCESS) {
        InputBuffer response_buf(in_buf_->getData(), in_buf_->getLength());
        response_->fromWire(response_buf);
    }

    // Once we are done with internal business, let's call a callback supplied
    // by a caller.
    if (callback_ != NULL) {
        (*callback_)(result);
    }
}

void
DNSClient::doUpdate(IOService& io_service,
                    const IOAddress& ns_addr,
                    const uint16_t ns_port,
                    D2UpdateMessage& update,
                    const int wait) {
    // A renderer is used by the toWire function which creates the on-wire data
    // from the DNS Update message. A renderer has its internal buffer where it
    // renders data by default. However, this buffer can't be directly accessed.
    // Fortunately, the renderer's API accepts user-supplied buffers. So, let's
    // create our own buffer and pass it to the renderer so as the message is
    // rendered to this buffer. Finally, we pass this buffer to IOFetch.
    dns::MessageRenderer renderer;
    OutputBufferPtr msg_buf(new OutputBuffer(DEFAULT_BUFFER_SIZE));
    renderer.setBuffer(msg_buf.get());

    // Render DNS Update message. This may throw a bunch of exceptions if
    // invalid message object is given.
    update.toWire(renderer);

    // IOFetch has all the mechanisms that we need to perform asynchronous
    // communication with the DNS server. The last but one argument points to
    // this object as a completion callback for the message exchange. As a
    // result operator()(IOFetch::Result) will be called.
    IOFetch io_fetch(IOFetch::UDP, io_service, msg_buf, ns_addr, ns_port,
                     in_buf_, this, wait);
    // Post the task to the task queue in the IO service. Caller will actually
    // run these tasks by executing IOService::run.
    io_service.post(io_fetch);
}


} // namespace d2
} // namespace isc

