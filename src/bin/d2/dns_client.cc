// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <d2/dns_client.h>
#include <d2/d2_log.h>
#include <dns/messagerenderer.h>
#include <limits>

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
using namespace isc::dns;

// This class provides the implementation for the DNSClient. This allows for
// the separation of the DNSClient interface from the implementation details.
// Currently, implementation uses IOFetch object to handle asynchronous
// communication with the DNS. This design may be revisited in the future. If
// implementation is changed, the DNSClient API will remain unchanged thanks
// to this separation.
class DNSClientImpl : public asiodns::IOFetch::Callback {
public:
    // A buffer holding response from a DNS.
    util::OutputBufferPtr in_buf_;
    // A caller-supplied object which will hold the parsed response from DNS.
    // The response object is (or descends from) isc::dns::Message and is
    // populated using Message::fromWire().  This method may only be called
    // once in the lifetime of a Message instance.  Therefore, response_ is a
    // pointer reference thus allowing this class to replace the object
    // pointed to with a new Message instance each time a message is
    // received. This allows a single DNSClientImpl instance to be used for
    // multiple, sequential IOFetch calls. (@todo Trac# 3286 has been opened
    // against dns::Message::fromWire.  Should the behavior of fromWire change
    // the behavior here with could be rexamined).
    D2UpdateMessagePtr& response_;
    // A caller-supplied external callback which is invoked when DNS message
    // exchange is complete or interrupted.
    DNSClient::Callback* callback_;
    // A Transport Layer protocol used to communicate with a DNS.
    DNSClient::Protocol proto_;
    // TSIG context used to sign outbound and verify inbound messages.
    dns::TSIGContextPtr tsig_context_;

    // Constructor and Destructor
    DNSClientImpl(D2UpdateMessagePtr& response_placeholder,
                  DNSClient::Callback* callback,
                  const DNSClient::Protocol proto);
    virtual ~DNSClientImpl();

    // This internal callback is called when the DNS update message exchange is
    // complete. It further invokes the external callback provided by a caller.
    // Before external callback is invoked, an object of the D2UpdateMessage
    // type, representing a response from the server is set.
    virtual void operator()(asiodns::IOFetch::Result result);

    // Starts asynchronous DNS Update using TSIG.
    void doUpdate(asiolink::IOService& io_service,
                  const asiolink::IOAddress& ns_addr,
                  const uint16_t ns_port,
                  D2UpdateMessage& update,
                  const unsigned int wait,
                  const dns::TSIGKeyPtr& tsig_key);

    // This function maps the IO error to the DNSClient error.
    DNSClient::Status getStatus(const asiodns::IOFetch::Result);
};

DNSClientImpl::DNSClientImpl(D2UpdateMessagePtr& response_placeholder,
                             DNSClient::Callback* callback,
                             const DNSClient::Protocol proto)
    : in_buf_(new OutputBuffer(DEFAULT_BUFFER_SIZE)),
      response_(response_placeholder), callback_(callback), proto_(proto) {

    // Response should be an empty pointer. It gets populated by the
    // operator() method.
    if (response_) {
        isc_throw(isc::BadValue, "Response buffer pointer should be null");
    }

    // @todo Currently we only support UDP. The support for TCP is planned for
    // the future release.
    if (proto_ == DNSClient::TCP) {
        isc_throw(isc::NotImplemented, "TCP is currently not supported as a"
                  << " Transport protocol for DNS Updates; please use UDP");
    }

    // Given that we already eliminated the possibility that TCP is used, it
    // would be sufficient  to check that (proto != DNSClient::UDP). But, once
    // support TCP is added the check above will disappear and the extra check
    // will be needed here anyway.
    // Note that cascaded check is used here instead of:
    //   if (proto_ != DNSClient::TCP && proto_ != DNSClient::UDP)..
    // because some versions of GCC compiler complain that check above would
    // be always 'false' due to limited range of enumeration. In fact, it is
    // possible to pass out of range integral value through enum and it should
    // be caught here.
    if (proto_ != DNSClient::TCP) {
        if (proto_ != DNSClient::UDP) {
            isc_throw(isc::NotImplemented, "invalid transport protocol type '"
                      << proto_ << "' specified for DNS Updates");
        }
    }
}

DNSClientImpl::~DNSClientImpl() {
}

void
DNSClientImpl::operator()(asiodns::IOFetch::Result result) {
    // Get the status from IO. If no success, we just call user's callback
    // and pass the status code.
    DNSClient::Status status = getStatus(result);
    if (status == DNSClient::SUCCESS) {
        // Allocate a new response message. (Note that Message::fromWire
        // may only be run once per message, so we need to start fresh
        // each time.)
        response_.reset(new D2UpdateMessage(D2UpdateMessage::INBOUND));

        // Server's response may be corrupted. In such case, fromWire will
        // throw an exception. We want to catch this exception to return
        // appropriate status code to the caller and log this event.
        try {
            response_->fromWire(in_buf_->getData(), in_buf_->getLength(),
                                tsig_context_.get());
        } catch (const isc::Exception& ex) {
            status = DNSClient::INVALID_RESPONSE;
            LOG_DEBUG(d2_to_dns_logger, DBGLVL_TRACE_DETAIL,
                      DHCP_DDNS_INVALID_RESPONSE).arg(ex.what());

        }

        if (tsig_context_) {
            // Context is a one-shot deal, get rid of it.
            tsig_context_.reset();
        }
    }

    // Once we are done with internal business, let's call a callback supplied
    // by a caller.
    if (callback_ != NULL) {
        (*callback_)(status);
    }
}

DNSClient::Status
DNSClientImpl::getStatus(const asiodns::IOFetch::Result result) {
    switch (result) {
    case IOFetch::SUCCESS:
        return (DNSClient::SUCCESS);

    case IOFetch::TIME_OUT:
        return (DNSClient::TIMEOUT);

    case IOFetch::STOPPED:
        return (DNSClient::IO_STOPPED);

    default:
        ;
    }
    return (DNSClient::OTHER);
}
void
DNSClientImpl::doUpdate(asiolink::IOService& io_service,
                        const IOAddress& ns_addr,
                        const uint16_t ns_port,
                        D2UpdateMessage& update,
                        const unsigned int wait,
                        const dns::TSIGKeyPtr& tsig_key) {
    // The underlying implementation which we use to send DNS Updates uses
    // signed integers for timeout. If we want to avoid overflows we need to
    // respect this limitation here.
    if (wait > DNSClient::getMaxTimeout()) {
        isc_throw(isc::BadValue, "A timeout value for DNS Update request must"
                  " not exceed " << DNSClient::getMaxTimeout()
                  << ". Provided timeout value is '" << wait << "'");
    }

    // Create a TSIG context if we have a key, otherwise clear the context
    // pointer.  Message marshalling uses non-null context is the indicator
    // that TSIG should be used.
    if (tsig_key) {
        tsig_context_.reset(new TSIGContext(*tsig_key));
    } else {
        tsig_context_.reset();
    }

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
    update.toWire(renderer, tsig_context_.get());

    // IOFetch has all the mechanisms that we need to perform asynchronous
    // communication with the DNS server. The last but one argument points to
    // this object as a completion callback for the message exchange. As a
    // result operator()(Status) will be called.

    // Timeout value is explicitly cast to the int type to avoid warnings about
    // overflows when doing implicit cast. It should have been checked by the
    // caller that the unsigned timeout value will fit into int.
    IOFetch io_fetch(IOFetch::UDP, io_service, msg_buf, ns_addr, ns_port,
                     in_buf_, this, static_cast<int>(wait));

    // Post the task to the task queue in the IO service. Caller will actually
    // run these tasks by executing IOService::run.
    io_service.post(io_fetch);
}

DNSClient::DNSClient(D2UpdateMessagePtr& response_placeholder,
                     Callback* callback, const DNSClient::Protocol proto)
    : impl_(new DNSClientImpl(response_placeholder, callback, proto)) {
}

DNSClient::~DNSClient() {
    delete (impl_);
}

unsigned int
DNSClient::getMaxTimeout() {
    static const unsigned int max_timeout = std::numeric_limits<int>::max();
    return (max_timeout);
}

void
DNSClient::doUpdate(asiolink::IOService& io_service,
                    const IOAddress& ns_addr,
                    const uint16_t ns_port,
                    D2UpdateMessage& update,
                    const unsigned int wait,
                    const dns::TSIGKeyPtr& tsig_key) {
    impl_->doUpdate(io_service, ns_addr, ns_port, update, wait, tsig_key);
}

} // namespace d2
} // namespace isc
