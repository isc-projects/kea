// Copyright (C) 2025-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/pkt4.h>
#include <dhcp/tests/pkt_filter_iface_test_utils.h>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {
namespace test {

const uint8_t MARKER = 0;

PktFilterIfaceSocketTest::PktFilterIfaceSocketTest(bool ready_on_send, bool clear_on_read)
    : ready_on_send_(ready_on_send),
      clear_on_read_(clear_on_read) {
}

PktFilterIfaceSocketTest::~PktFilterIfaceSocketTest() {
    for (auto it = socket_fds_.begin(); it != socket_fds_.end(); ++it) {
        close(it->first);
        close(it->second);
    }
}

SocketInfo
PktFilterIfaceSocketTest::openSocketCommon(Iface& /* iface */, const isc::asiolink::IOAddress& addr,
                                           const uint16_t) {
    int pipe_fds[2];
    if (pipe(pipe_fds) < 0) {
        isc_throw(Unexpected, "failed to open test pipe: " << strerror(errno));
    }
    if (fcntl(pipe_fds[0], F_SETFL, O_NONBLOCK) < 0) {
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        isc_throw(Unexpected, "fcntl " << strerror(errno));
    }
    if (fcntl(pipe_fds[1], F_SETFL, O_NONBLOCK) < 0) {
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        isc_throw(Unexpected, "fcntl " << strerror(errno));
    }
    std::unique_lock<std::mutex> lk(mutex_);
    socket_fds_[pipe_fds[0]] = pipe_fds[1];
    return (SocketInfo(addr, 9999, pipe_fds[0]));
}

PktPtr
PktFilterIfaceSocketTest::receiveCommon(const SocketInfo& s) {
    std::unique_lock<std::mutex> lk(mutex_);
    auto it = socket_fds_.find(s.sockfd_);
    if (it == socket_fds_.end()) {
        std::cout << "receive no such socket: " << s.sockfd_ << std::endl;
        return (PktPtr());
    }
    PktPtr result = pkts_[s.sockfd_];
    if (clear_on_read_) {
        uint8_t data;
        for (size_t count = -1; count; count = read(s.sockfd_, &data, sizeof(data)));
    }
    return (result);
}

int
PktFilterIfaceSocketTest::sendCommon(const Iface& /* iface */, uint16_t sockfd, const PktPtr& pkt) {
    std::unique_lock<std::mutex> lk(mutex_);
    auto it = socket_fds_.find(sockfd);
    if (it == socket_fds_.end()) {
        std::cout << "send no such socket: " << sockfd << std::endl;
        return (-1);
    }
    pkts_[sockfd] = pkt;
    if (ready_on_send_) {
        uint8_t data = MARKER;
        uint8_t count = 0;
        do {
            count = write(it->second, &data, sizeof(data));
        } while (!count);
    }
    return (0);
}

PktFilter4IfaceSocketTest::PktFilter4IfaceSocketTest(bool ready_on_send, bool clear_on_read)
    : PktFilterIfaceSocketTest(ready_on_send, clear_on_read) {
}

bool
PktFilter4IfaceSocketTest::isDirectResponseSupported() const {
    return (true);
}

bool
PktFilter4IfaceSocketTest::isSocketReceivedTimeSupported() const {
    return (true);
}

SocketInfo
PktFilter4IfaceSocketTest::openSocket(Iface& iface,
                                      const isc::asiolink::IOAddress& addr,
                                      const uint16_t port, const bool, const bool) {
    return (PktFilterIfaceSocketTest::openSocketCommon(iface, addr, port));
}

Pkt4Ptr
PktFilter4IfaceSocketTest::receive(Iface& /* iface */, const SocketInfo& s) {
    return (boost::dynamic_pointer_cast<Pkt4>(PktFilterIfaceSocketTest::receiveCommon(s)));
}

int
PktFilter4IfaceSocketTest::send(const Iface& iface, uint16_t sockfd, const Pkt4Ptr& pkt) {
    return (PktFilterIfaceSocketTest::sendCommon(iface, sockfd, pkt));
}

PktFilter6IfaceSocketTest::PktFilter6IfaceSocketTest(bool ready_on_send, bool clear_on_read)
    : PktFilterIfaceSocketTest(ready_on_send, clear_on_read) {
}

SocketInfo
PktFilter6IfaceSocketTest::openSocket(Iface& iface,
                                      const isc::asiolink::IOAddress& addr,
                                      const uint16_t port, const bool) {
    return (PktFilterIfaceSocketTest::openSocketCommon(iface, addr, port));
}

Pkt6Ptr
PktFilter6IfaceSocketTest::receive(const SocketInfo& s) {
    return (boost::dynamic_pointer_cast<Pkt6>(PktFilterIfaceSocketTest::receiveCommon(s)));
}

int
PktFilter6IfaceSocketTest::send(const Iface& iface, uint16_t sockfd, const Pkt6Ptr& pkt) {
    return (PktFilterIfaceSocketTest::sendCommon(iface, sockfd, pkt));
}

} // end of isc::dhcp::test namespace
} // end of isc::dhcp namespace
} // end of isc namespace
