// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp_ddns/dhcp_ddns_log.h>
#include <dhcp_ddns/ncr_udp.h>

#include <boost/asio/ip/udp.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind.hpp>

namespace isc {
namespace dhcp_ddns {

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
UDPCallback::operator ()(const boost::system::error_code error_code,
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
                      const uint32_t port, const NameChangeFormat format,
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
    isc::asiolink::UDPEndpoint endpoint(ip_address_, port_);

    // Create the low level socket.
    try {
        asio_socket_.reset(new boost::asio::ip::udp::
                           socket(io_service.get_io_service(),
                                  (ip_address_.isV4() ? boost::asio::ip::udp::v4() :
                                   boost::asio::ip::udp::v6())));

        // Set the socket option to reuse addresses if it is enabled.
        if (reuse_address_) {
            asio_socket_->set_option(boost::asio::socket_base::reuse_address(true));
        }

        // Bind the low level socket to our endpoint.
        asio_socket_->bind(endpoint.getASIOEndpoint());
    } catch (boost::system::system_error& ex) {
        asio_socket_.reset();
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
    // Since we are managing our own socket, we need to close it ourselves.
    // NOTE that if there is a pending receive, it will be canceled, which
    // WILL generate an invocation of the callback with error code of
    // "operation aborted".
    if (asio_socket_) {
        if (asio_socket_->is_open()) {
            try {
                asio_socket_->close();
            } catch (boost::system::system_error& ex) {
                // It is really unlikely that this will occur.
                // If we do reopen later it will be with a new socket
                // instance. Repackage exception as one that is conformant
                // with the interface.
                isc_throw (NcrUDPError, ex.code().message());
            }
        }

        asio_socket_.reset();
    }

    socket_.reset();
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
            LOG_ERROR(dhcp_ddns_logger, DHCP_DDNS_INVALID_NCR).arg(ex.what());

            // Queue up the next receive.
            // NOTE: We must call the base class, NEVER doReceive
            receiveNext();
            return;
        }
    } else {
        boost::system::error_code error_code = callback->getErrorCode();
        if (error_code.value() == boost::asio::error::operation_aborted) {
            // A shutdown cancels all outstanding reads.  For this reason,
            // it can be an expected event, so log it as a debug message.
            LOG_DEBUG(dhcp_ddns_logger, DBGLVL_TRACE_BASIC,
                      DHCP_DDNS_NCR_UDP_RECV_CANCELED);
            result = STOPPED;
        } else {
            LOG_ERROR(dhcp_ddns_logger, DHCP_DDNS_NCR_UDP_RECV_ERROR)
                      .arg(error_code.message());
            result = ERROR;
        }
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
    isc::asiolink::UDPEndpoint endpoint(ip_address_, port_);

    // Create the low level socket.
    try {
        asio_socket_.reset(new boost::asio::ip::udp::
                           socket(io_service.get_io_service(),
                                  (ip_address_.isV4() ? boost::asio::ip::udp::v4() :
                                   boost::asio::ip::udp::v6())));

        // Set the socket option to reuse addresses if it is enabled.
        if (reuse_address_) {
            asio_socket_->set_option(boost::asio::socket_base::reuse_address(true));
        }

        // Bind the low leve socket to our endpoint.
        asio_socket_->bind(endpoint.getASIOEndpoint());
    } catch (boost::system::system_error& ex) {
        isc_throw (NcrUDPError, ex.code().message());
    }

    // Create the asiolink socket from the low level socket.
    socket_.reset(new NameChangeUDPSocket(*asio_socket_));

    // Create the server endpoint
    server_endpoint_.reset(new isc::asiolink::
                           UDPEndpoint(server_address_, server_port_));

    send_callback_->setDataSource(server_endpoint_);

    closeWatchSocket();
    watch_socket_.reset(new util::WatchSocket());
}

void
NameChangeUDPSender::close() {
    // Whether we think we are sending or not, make sure we aren't.
    // Since we are managing our own socket, we need to close it ourselves.
    // NOTE that if there is a pending send, it will be canceled, which
    // WILL generate an invocation of the callback with error code of
    // "operation aborted".
    if (asio_socket_) {
        if (asio_socket_->is_open()) {
            try {
                asio_socket_->close();
            } catch (boost::system::system_error& ex) {
                // It is really unlikely that this will occur.
                // If we do reopen later it will be with a new socket
                // instance. Repackage exception as one that is conformant
                // with the interface.
                isc_throw (NcrUDPError, ex.code().message());
            }
        }

        asio_socket_.reset();
    }

    socket_.reset();

    closeWatchSocket();
    watch_socket_.reset();
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

    // Set IO ready marker so sender activity is visible to select() or poll().
    // Note, if this call throws it will manifest itself as a throw from
    // from sendRequest() which the application calls directly and is documented
    // as throwing exceptions; or caught inside invokeSendHandler() which
    // will invoke the application's send_handler with an error status.
    watch_socket_->markReady();
}

void
NameChangeUDPSender::sendCompletionHandler(const bool successful,
                                           const UDPCallback *send_callback) {
    // Clear the IO ready marker.
    try {
        watch_socket_->clearReady();
    } catch (const std::exception& ex) {
        // This can only happen if the WatchSocket's select_fd has been
        // compromised which is a programmatic error. We'll log the error
        // here, then continue on and process the IO result we were given.
        // WatchSocket issue will resurface on the next send as a closed
        // fd in markReady().  This allows application's handler to deal
        // with watch errors more uniformly.
        LOG_ERROR(dhcp_ddns_logger, DHCP_DDNS_NCR_UDP_CLEAR_READY_ERROR)
                 .arg(ex.what());
    }

    Result result;
    if (successful) {
        result = SUCCESS;
    }
    else {
        // On a failure, log the error and set the result to ERROR.
        boost::system::error_code error_code = send_callback->getErrorCode();
        if (error_code.value() == boost::asio::error::operation_aborted) {
            LOG_ERROR(dhcp_ddns_logger, DHCP_DDNS_NCR_UDP_SEND_CANCELED)
                      .arg(error_code.message());
            result = STOPPED;
        } else {
            LOG_ERROR(dhcp_ddns_logger, DHCP_DDNS_NCR_UDP_SEND_ERROR)
                      .arg(error_code.message());
            result = ERROR;
        }
    }

    // Call the application's registered request send handler.
    invokeSendHandler(result);
}

int
NameChangeUDPSender::getSelectFd() {
    if (!amSending()) {
        isc_throw(NotImplemented, "NameChangeUDPSender::getSelectFd"
                                  " not in send mode");
    }

    return(watch_socket_->getSelectFd());
}

bool
NameChangeUDPSender::ioReady() {
    if (watch_socket_) {
        return (watch_socket_->isReady());
    }

    return (false);
}

void
NameChangeUDPSender::closeWatchSocket() {
    if (watch_socket_) {
        std::string error_string;
        watch_socket_->closeSocket(error_string);
        if (!error_string.empty()) {
            LOG_ERROR(dhcp_ddns_logger, DHCP_DDNS_UDP_SENDER_WATCH_SOCKET_CLOSE_ERROR)
                .arg(error_string);
        }
    }
}

}; // end of isc::dhcp_ddns namespace
}; // end of isc namespace
