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

#include <d2/d2_log.h>
#include <d2/ncr_udp.h>

#include <asio/ip/udp.hpp>
#include <asio/error_code.hpp>
#include <boost/bind.hpp>

namespace isc {
namespace d2 {

//*************************** UDPCallback ***********************
UDPCallback::UDPCallback (RawBufferPtr& buffer, const size_t buf_size,
                          UDPEndpointPtr& data_source,
                          const UDPCompletionHandler& handler)
    : handler_(handler), data_(new Data(buffer, buf_size, data_source)) {
    if (handler.empty()) {
        isc_throw(NcrUDPError, "UDPCallback - handler can't be null");
    }

    if (!buffer) {
        isc_throw(NcrUDPError, "UDPCallback - buffer can't be null");
    }
}

void
UDPCallback::operator ()(const asio::error_code error_code,
                         const size_t bytes_transferred) {

    // Save the result state and number of bytes transferred.
    setErrorCode(error_code);
    setBytesTransferred(bytes_transferred);

    // Invoke the NameChangeRequest layer completion handler.
    // First argument is a boolean indicating success or failure.
    // The second is a pointer to "this" callback object. By passing
    // ourself in, we make all of the service related data available
    // to the completion handler.
    handler_(!error_code, this);
}

void
UDPCallback::putData(const uint8_t* src, size_t len) {
    if (!src) {
        isc_throw(NcrUDPError, "UDPCallback putData, data source is NULL");
    }

    if (len > data_->buf_size_) {
        isc_throw(NcrUDPError, "UDPCallback putData, data length too large");
    }

    memcpy (data_->buffer_.get(), src, len);
    data_->put_len_ = len;
}


//*************************** NameChangeUDPListener ***********************
NameChangeUDPListener::
NameChangeUDPListener(const isc::asiolink::IOAddress& ip_address,
                      const uint32_t port, NameChangeFormat format,
                      RequestReceiveHandler& ncr_recv_handler,
                      const bool reuse_address)
    : NameChangeListener(ncr_recv_handler), ip_address_(ip_address),
      port_(port), format_(format), reuse_address_(reuse_address) {
    // Instantiate the receive callback.  This gets passed into each receive.
    // Note that the callback constructor is passed an instance method
    // pointer to our completion handler method, receiveCompletionHandler.
    RawBufferPtr buffer(new uint8_t[RECV_BUF_MAX]);
    UDPEndpointPtr data_source(new asiolink::UDPEndpoint());
    recv_callback_.reset(new
                         UDPCallback(buffer, RECV_BUF_MAX, data_source,
                                     boost::bind(&NameChangeUDPListener::
                                     receiveCompletionHandler, this, _1, _2)));
}

NameChangeUDPListener::~NameChangeUDPListener() {
    // Clean up.
    stopListening();
}

void
NameChangeUDPListener::open(isc::asiolink::IOService& io_service) {
    // create our endpoint and bind the the low level socket to it.
    isc::asiolink::UDPEndpoint endpoint(ip_address_.getAddress(), port_);

    // Create the low level socket.
    try {
        asio_socket_.reset(new asio::ip::udp::
                           socket(io_service.get_io_service(),
                                  (ip_address_.isV4() ? asio::ip::udp::v4() :
                                   asio::ip::udp::v6())));

        // Set the socket option to reuse addresses if it is enabled.
        if (reuse_address_) {
            asio_socket_->set_option(asio::socket_base::reuse_address(true));
        }

        // Bind the low level socket to our endpoint.
        asio_socket_->bind(endpoint.getASIOEndpoint());
    } catch (asio::system_error& ex) {
        isc_throw (NcrUDPError, ex.code().message());
    }

    // Create the asiolink socket from the low level socket.
    socket_.reset(new NameChangeUDPSocket(*asio_socket_));
}


void
NameChangeUDPListener::doReceive() {
    // Call the socket's asychronous receiving, passing ourself in as callback.
    RawBufferPtr recv_buffer = recv_callback_->getBuffer();
    socket_->asyncReceive(recv_buffer.get(), recv_callback_->getBufferSize(),
                          0, recv_callback_->getDataSource().get(),
                          *recv_callback_);
}

void
NameChangeUDPListener::close() {
    // Whether we think we are listening or not, make sure we aren't.
    // Since we are managing our own socket, we need to cancel and close
    // it ourselves.
    if (asio_socket_) {
        try {
            asio_socket_->cancel();
            asio_socket_->close();
        } catch (asio::system_error& ex) {
            // It is really unlikely that this will occur.
            // If we do reopen later it will be with a new socket instance.
            // Repackage exception as one that is conformant with the interface.
            isc_throw (NcrUDPError, ex.code().message());
        }
    }
}

void
NameChangeUDPListener::receiveCompletionHandler(const bool successful,
                                                const UDPCallback *callback) {
    NameChangeRequestPtr ncr;
    Result result = SUCCESS;

    if (successful) {
        // Make an InputBuffer from our internal array
        isc::util::InputBuffer input_buffer(callback->getData(),
                                            callback->getBytesTransferred());

        try {
            ncr = NameChangeRequest::fromFormat(format_, input_buffer);
        } catch (const NcrMessageError& ex) {
            // log it and go back to listening
            LOG_ERROR(dctl_logger, DHCP_DDNS_INVALID_NCR).arg(ex.what());

            // Queue up the next recieve.
            doReceive();
            return;
        }
    } else {
        asio::error_code error_code = callback->getErrorCode();
        LOG_ERROR(dctl_logger, DHCP_DDNS_NCR_UDP_RECV_ERROR)
                  .arg(error_code.message());
        result = ERROR;
    }

    // Call the application's registered request receive handler.
    invokeRecvHandler(result, ncr);
}


//*************************** NameChangeUDPSender ***********************

NameChangeUDPSender::
NameChangeUDPSender(const isc::asiolink::IOAddress& ip_address,
                    const uint32_t port,
                    const isc::asiolink::IOAddress& server_address,
                    const uint32_t server_port, const NameChangeFormat format,
                    RequestSendHandler& ncr_send_handler,
                    const size_t send_que_max, const bool reuse_address)
    : NameChangeSender(ncr_send_handler, send_que_max),
      ip_address_(ip_address), port_(port), server_address_(server_address),
      server_port_(server_port), format_(format),
      reuse_address_(reuse_address) {
    // Instantiate the send callback.  This gets passed into each send.
    // Note that the callback constructor is passed the an instance method
    // pointer to our completion handler, sendCompletionHandler.
    RawBufferPtr buffer(new uint8_t[SEND_BUF_MAX]);
    UDPEndpointPtr data_source(new asiolink::UDPEndpoint());
    send_callback_.reset(new UDPCallback(buffer, SEND_BUF_MAX, data_source,
                                         boost::bind(&NameChangeUDPSender::
                                         sendCompletionHandler, this,
                                         _1, _2)));
}

NameChangeUDPSender::~NameChangeUDPSender() {
    // Clean up.
    stopSending();
}

void
NameChangeUDPSender::open(isc::asiolink::IOService& io_service) {
    // create our endpoint and bind the the low level socket to it.
    isc::asiolink::UDPEndpoint endpoint(ip_address_.getAddress(), port_);

    // Create the low level socket.
    try {
        asio_socket_.reset(new asio::ip::udp::
                           socket(io_service.get_io_service(),
                                  (ip_address_.isV4() ? asio::ip::udp::v4() :
                                   asio::ip::udp::v6())));

        // Set the socket option to reuse addresses if it is enabled.
        if (reuse_address_) {
            asio_socket_->set_option(asio::socket_base::reuse_address(true));
        }

        // Bind the low leve socket to our endpoint.
        asio_socket_->bind(endpoint.getASIOEndpoint());
    } catch (asio::system_error& ex) {
        isc_throw (NcrUDPError, ex.code().message());
    }

    // Create the asiolink socket from the low level socket.
    socket_.reset(new NameChangeUDPSocket(*asio_socket_));

    // Create the server endpoint
    server_endpoint_.reset(new isc::asiolink::
                           UDPEndpoint(server_address_.getAddress(),
                                       server_port_));

    send_callback_->setDataSource(server_endpoint_);
}

void
NameChangeUDPSender::close() {
    // Whether we think we are sending or not, make sure we aren't.
    // Since we are managing our own socket, we need to cancel and close
    // it ourselves.
    if (asio_socket_) {
        try {
            asio_socket_->cancel();
            asio_socket_->close();
        } catch (asio::system_error& ex) {
            // It is really unlikely that this will occur.
            // If we do reopen later it will be with a new socket instance.
            // Repackage exception as one that is conformant with the interface.
            isc_throw (NcrUDPError, ex.code().message());
        }
    }
}

void
NameChangeUDPSender::doSend(NameChangeRequestPtr& ncr) {
    // Now use the NCR to write JSON to an output buffer.
    isc::util::OutputBuffer ncr_buffer(SEND_BUF_MAX);
    ncr->toFormat(format_, ncr_buffer);

    // Copy the wire-ized request to callback.  This way we know after
    // send completes what we sent (or attempted to send).
    send_callback_->putData(static_cast<const uint8_t*>(ncr_buffer.getData()),
                            ncr_buffer.getLength());

    // Call the socket's asychronous send, passing our callback
    socket_->asyncSend(send_callback_->getData(), send_callback_->getPutLen(),
                       send_callback_->getDataSource().get(), *send_callback_);
}

void
NameChangeUDPSender::sendCompletionHandler(const bool successful,
                                           const UDPCallback *send_callback) {
    Result result;
    if (successful) {
        result = SUCCESS;
    }
    else {
        // On a failure, log the error and set the result to ERROR.
        asio::error_code error_code = send_callback->getErrorCode();
        LOG_ERROR(dctl_logger, DHCP_DDNS_NCR_UDP_RECV_ERROR)
                  .arg(error_code.message());

        result = ERROR;
    }

    // Call the application's registered request send handler.
    invokeSendHandler(result);
}
}; // end of isc::d2 namespace
}; // end of isc namespace
