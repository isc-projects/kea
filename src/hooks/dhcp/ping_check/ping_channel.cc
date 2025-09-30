// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <ping_channel.h>
#include <ping_check_log.h>
#include <dhcp/iface_mgr.h>
#include <exceptions/exceptions.h>
#include <util/multi_threading_mgr.h>
#include <iostream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;

namespace ph = std::placeholders;

namespace isc {
namespace ping_check {

uint32_t
PingChannel::nextEchoInstanceNum() {
    static uint32_t echo_instance_num = 0x00010000;
    if (echo_instance_num == UINT32_MAX) {
        echo_instance_num = 0x00010001;
    } else {
        ++echo_instance_num;
    }

    return (echo_instance_num);
}

PingChannel::PingChannel(IOServicePtr& io_service,
                         NextToSendCallback next_to_send_cb,
                         EchoSentCallback echo_sent_cb,
                         ReplyReceivedCallback reply_received_cb,
                         ShutdownCallback shutdown_cb)
    : io_service_(io_service),
      next_to_send_cb_(next_to_send_cb),
      echo_sent_cb_(echo_sent_cb),
      reply_received_cb_(reply_received_cb),
      shutdown_cb_(shutdown_cb),
      socket_(0), input_buf_(256),
      reading_(false), sending_(false), stopping_(false), mutex_(new std::mutex),
      single_threaded_(!MultiThreadingMgr::instance().getMode()),
      watch_socket_(0), registered_write_fd_(-1), registered_read_fd_(-1) {
    if (!io_service_) {
        isc_throw(BadValue,
                  "PingChannel ctor - io_service cannot be empty");
    }
}

PingChannel::~PingChannel() {
    close();
}

void
PingChannel::open() {
    try {
        MultiThreadingLock lock(*mutex_);
        if (socket_ && socket_->isOpen()) {
            return;
        }

        // For open(), the endpoint is only used to determine protocol,
        // the address is irrelevant.
        ICMPEndpoint ping_to_endpoint(IOAddress::IPV4_ZERO_ADDRESS());
        SocketCallback socket_cb(
            [](boost::system::error_code ec, size_t /*length */) {
                isc_throw(Unexpected, "ICMPSocket open is synchronous, should not invoke cb: "
                          << ec.message());
            }
        );

        socket_.reset(new PingSocket(io_service_));
        socket_->open(&ping_to_endpoint, socket_cb);
        reading_ = false;
        sending_ = false;
        stopping_ = false;

        if (single_threaded_) {
            // Open new watch socket.
            watch_socket_.reset(new util::WatchSocket());

            // Register the WatchSocket with IfaceMgr to signal data ready to write.
            registered_write_fd_ = watch_socket_->getSelectFd();
            IfaceMgr::instance().addExternalSocket(registered_write_fd_, IfaceMgr::SocketCallback());

            // Register ICMPSocket with IfaceMgr to signal data ready to read.
            registered_read_fd_ = socket_->getNative();
            IfaceMgr::instance().addExternalSocket(registered_read_fd_, IfaceMgr::SocketCallback());
        }

    } catch (const std::exception& ex) {
        isc_throw(Unexpected, "PingChannel::open failed:" << ex.what());
    }

    LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_BASIC, PING_CHECK_CHANNEL_SOCKET_OPENED);
}

bool
PingChannel::isOpen() const {
    MultiThreadingLock lock(*mutex_);
    return (socket_ && socket_->isOpen());
}

void
PingChannel::close() {
    try {
        MultiThreadingLock lock(*mutex_);

        if (single_threaded_) {
            // Unregister from IfaceMgr.
            if (registered_write_fd_ != -1) {
                IfaceMgr::instance().deleteExternalSocket(registered_write_fd_);
                registered_write_fd_ = -1;
            }

            if (registered_read_fd_ != -1) {
                IfaceMgr::instance().deleteExternalSocket(registered_read_fd_);
                registered_read_fd_ = -1;
            }

            // Close watch socket.
            if (watch_socket_) {
                std::string error_string;
                watch_socket_->closeSocket(error_string);
                if (!error_string.empty()) {
                    LOG_ERROR(ping_check_logger, PING_CHECK_CHANNEL_WATCH_SOCKET_CLOSE_ERROR)
                              .arg(error_string);
                }

                watch_socket_.reset();
            }
        }

        if (!socket_ || !socket_->isOpen()) {
            return;
        }

        socket_->close();
    } catch (const std::exception& ex) {
        // On close error, log but do not throw.
        LOG_ERROR(ping_check_logger, PING_CHECK_CHANNEL_SOCKET_CLOSE_ERROR)
                 .arg(ex.what());
    }

    LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_BASIC, PING_CHECK_CHANNEL_SOCKET_CLOSED);
}

void
PingChannel::stopChannel() {
    {
        MultiThreadingLock lock(*mutex_);
        if (stopping_) {
            return;
        }

        stopping_ = true;
    }

    LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_BASIC, PING_CHECK_CHANNEL_STOP);
    close();

    if (shutdown_cb_) {
        (shutdown_cb_)();
    }
}

void
PingChannel::asyncReceive(void* data, size_t length, size_t offset,
                          asiolink::IOEndpoint* endpoint, SocketCallback& callback) {
    socket_->asyncReceive(data, length, offset, endpoint, callback);
}

void
PingChannel::asyncSend(void* data, size_t length, asiolink::IOEndpoint* endpoint,
                       SocketCallback& callback) {
    socket_->asyncSend(data, length, endpoint, callback);

    if (single_threaded_) {
        // Set IO ready marker so sender activity is visible to select() or poll().
        watch_socket_->markReady();
    }
}

void
PingChannel::doRead() {
    try {
        MultiThreadingLock lock(*mutex_);
        if (!canRead()) {
            return;
        }

        reading_ = true;

        // Create instance of the callback. It is safe to pass the
        // local instance of the callback, because the underlying
        // std functions make copies as needed.
        SocketCallback cb(std::bind(&PingChannel::socketReadCallback,
                                    shared_from_this(),
                                    ph::_1,   // error
                                    ph::_2)); // bytes_transferred
        asyncReceive(static_cast<void*>(getInputBufData()), getInputBufSize(),
                                        0, &reply_endpoint_, cb);
    } catch (const std::exception& ex) {
        // Normal IO failures should be passed to the callback.  A failure here
        // indicates the call to asyncReceive() itself failed.
        LOG_ERROR(ping_check_logger, PING_CHECK_UNEXPECTED_READ_ERROR)
            .arg(ex.what());
        stopChannel();
    }
}

void
PingChannel::socketReadCallback(boost::system::error_code ec, size_t length) {
    {
        MultiThreadingLock lock(*mutex_);
        if (stopping_) {
            return;
        }
    }

    if (ec) {
        if (ec.value() == boost::asio::error::operation_aborted) {
            // IO service has been stopped and the connection is probably
            // going to be shutting down.
            return;
        } else if ((ec.value() == boost::asio::error::try_again) ||
                   (ec.value() == boost::asio::error::would_block)) {
            // We got EWOULDBLOCK or EAGAIN which indicates that we may be able to
            // read something from the socket on the next attempt. Just make sure
            // we don't try to read anything now in case there is any garbage
            // passed in length.
            length = 0;
        } else {
            // Anything else is fatal for the socket.
            LOG_ERROR(ping_check_logger, PING_CHECK_CHANNEL_SOCKET_READ_FAILED)
                .arg(ec.message());
            stopChannel();
            return;
        }
    }

    // Unpack the reply and pass it to the reply callback.
    ICMPMsgPtr reply;
    if (length > 0) {
        {
            try {
                MultiThreadingLock lock(*mutex_);
                reply = ICMPMsg::unpack(getInputBufData(), getInputBufSize());
                if (reply->getType() == ICMPMsg::ECHO_REPLY) {
                    LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_DETAIL,
                              PING_CHECK_CHANNEL_ECHO_REPLY_RECEIVED)
                        .arg(reply->getSource())
                        .arg(reply->getId())
                        .arg(reply->getSequence());
                }
            } catch (const std::exception& ex) {
                LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_BASIC,
                          PING_CHECK_CHANNEL_MALFORMED_PACKET_RECEIVED)
                          .arg(ex.what());
            }
        }
    }

    {
        MultiThreadingLock lock(*mutex_);
        reading_ = false;
    }

    if (reply) {
        (reply_received_cb_)(reply);
    }

    // Start the next read.
    doRead();
}

void
PingChannel::startSend() {
    MultiThreadingLock lock(*mutex_);
    if (canSend()) {
        // Post the call to sendNext to the IOService.
        // This ensures its carried out on a thread
        // associated with the channel's IOService
        // not the thread invoking this function.
        auto f = [](PingChannelPtr ptr) { ptr->sendNext(); };
        io_service_->post(std::bind(f, shared_from_this()));
    }
}

void
PingChannel::startRead() {
    MultiThreadingLock lock(*mutex_);
    if (canRead()) {
        // Post the call to doRead to the IOService.
        // This ensures its carried out on a thread
        // associated with the channel's IOService
        // not the thread invoking this function.
        auto f = [](PingChannelPtr ptr) { ptr->doRead(); };
        io_service_->post(std::bind(f, shared_from_this()));
    }
}

void
PingChannel::sendNext() {
    try {
        {
            MultiThreadingLock lock(*mutex_);
            if (!canSend()) {
            // Can't send right now, get out.
                return;
            }
        }

        // Fetch the next one to send.
        IOAddress target("0.0.0.0");
        if (!((next_to_send_cb_)(target))) {
            // Nothing to send.
            return;
        }

        // Have an target IP, build an ECHO REQUEST for it.
        ICMPMsgPtr next_echo(new ICMPMsg());
        {
            MultiThreadingLock lock(*mutex_);
            if (!canSend()) {
                return;
            }

            sending_ = true;
            next_echo->setType(ICMPMsg::ECHO_REQUEST);
            next_echo->setDestination(target);

            uint32_t instance_num = nextEchoInstanceNum();
            next_echo->setId(static_cast<uint16_t>(instance_num >> 16));
            next_echo->setSequence(static_cast<uint16_t>(instance_num & 0x0000FFFF));
        }

        // Get packed wire-form.
        ICMPPtr echo_icmp = next_echo->pack();

        // Create instance of the callback. It is safe to pass the
        // local instance of the callback, because the underlying
        // std functions make copies as needed.
        SocketCallback cb(std::bind(&PingChannel::socketWriteCallback,
                                    shared_from_this(),
                                    next_echo,
                                    ph::_1,   // error
                                    ph::_2)); // bytes_transferred

        ICMPEndpoint target_endpoint(target);
        asyncSend(echo_icmp.get(), sizeof(struct icmp), &target_endpoint, cb);
    } catch (const std::exception& ex) {
        // Normal IO failures should be passed to the callback.  A failure here
        // indicates the call to asyncSend() itself failed.
        LOG_ERROR(ping_check_logger, PING_CHECK_UNEXPECTED_WRITE_ERROR)
            .arg(ex.what());
        stopChannel();
        return;
    }
}

void
PingChannel::socketWriteCallback(ICMPMsgPtr echo, boost::system::error_code ec,
                                 size_t length) {
    {
        MultiThreadingLock lock(*mutex_);
        if (stopping_) {
            return;
        }
    }

    if (single_threaded_) {
        try {
            // Clear the IO ready marker.
            watch_socket_->clearReady();
        } catch (const std::exception& ex) {
            // This can only happen if the WatchSocket's select_fd has been
            // compromised which is a programmatic error. We'll log the error
            // here, then continue on and process the IO result we were given.
            // WatchSocket issue will resurface on the next send as a closed
            // fd in markReady() rather than fail out of this callback.
            LOG_ERROR(ping_check_logger, PING_CHECK_CHANNEL_WATCH_SOCKET_CLEAR_ERROR)
                     .arg(ex.what());
        }
    }

    // Handle an error. Note we can't use a case statement as some values
    // on some OSes are the same (e.g. try_again and would_block) which causes
    // duplicate case compilation errors.
    bool send_failed = false;
    if (ec) {
        auto error_value = ec.value();
        if (error_value == boost::asio::error::operation_aborted) {
            // IO service has been stopped and the connection is probably
            // going to be shutting down.
            return;
        } else if ((error_value == boost::asio::error::try_again) ||
                    (error_value == boost::asio::error::would_block)) {
            // We got EWOULDBLOCK or EAGAIN which indicates that we may be able to
            // write something from the socket on the next attempt.  Set the length
            // to zero so we skip the completion callback.
            length = 0;
        } else if ((error_value == boost::asio::error::network_unreachable) ||
                   (error_value == boost::asio::error::host_unreachable) ||
                   (error_value == boost::asio::error::network_down)) {
            // One of these implies an interface might be down, or there's no
            // way to ping this network. Other networks might be working OK.
            send_failed = true;
        } else if (error_value == boost::asio::error::no_buffer_space) {
            // Writing faster than the kernel will write them out.
            send_failed = true;
        } else if (error_value == boost::asio::error::access_denied) {
            // Means the address we tried to ping is not allowed. Most likey a broadcast
            // address.
            send_failed = true;
        } else {
            // Anything else is fatal for the socket.
            LOG_ERROR(ping_check_logger, PING_CHECK_CHANNEL_SOCKET_WRITE_FAILED)
                .arg(ec.message());
            stopChannel();
            return;
        }
    }

    {
        MultiThreadingLock lock(*mutex_);
        sending_ = false;
    }

    if (send_failed) {
        // Invoke the callback with send failed.  This instructs the manager
        // to treat the address as free to use.
        LOG_ERROR(ping_check_logger, PING_CHECK_CHANNEL_NETWORK_WRITE_ERROR)
                .arg(echo->getDestination())
                .arg(ec.message());
        // Invoke the send completed callback.
        (echo_sent_cb_)(echo, true);
    } else if (length > 0) {
        LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_DETAIL,
                  PING_CHECK_CHANNEL_ECHO_REQUEST_SENT)
            .arg(echo->getDestination())
            .arg(echo->getId())
            .arg(echo->getSequence());
        // Invoke the send completed callback.
        (echo_sent_cb_)(echo, false);
    }

    // Schedule the next send.
    sendNext();
}

size_t
PingChannel::getInputBufSize() const {
    return (input_buf_.size());
}

unsigned char*
PingChannel::getInputBufData() {
    if (input_buf_.empty()) {
        isc_throw(InvalidOperation,
                  "PingChannel::getInputBufData() - cannot access empty buffer");
    }

    return (input_buf_.data());
}

} // end of namespace ping_check
} // end of namespace isc
