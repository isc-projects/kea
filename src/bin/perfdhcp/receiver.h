// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PERFDHCP_RECEIVER_H
#define PERFDHCP_RECEIVER_H

#include <perfdhcp/perf_socket.h>
#include <perfdhcp/command_options.h>

#include <dhcp/pkt.h>

#include <queue>
#include <thread>
#include <mutex>
#include <atomic>

namespace isc {
namespace perfdhcp {

/// \brief A receviving DHCP packets class.
///
/// Receiver can be used in two modes: single-thread and multi-thread.
///
/// In single-thread mode the class directly reads packets from socket
/// and returns them to consumer using getPkt method.
///
/// In case of multi-thread mode the class starts a thread in backgroud.
/// The thread reads the packets and pushes them to pkt_queue_. Then
/// in main thread packets can be consumed from the queue using getPkt
/// method.
class Receiver {
private:
    /// \brief Flag indicating if thread should run (true) or not (false).
    std::atomic_flag run_flag_;

    /// \brief Thread for receiving packets.
    std::unique_ptr<std::thread> recv_thread_;

    /// \brief Queue for passing packets from receiver thread to main thread.
    std::queue<dhcp::PktPtr> pkt_queue_;

    /// \brief Mutex for controlling access to the queue.
    std::mutex pkt_queue_mutex_;

    BasePerfSocket &socket_;

    /// \brief Single- or thread-mode indicator.
    bool single_threaded_;

    uint8_t ip_version_;

public:
    /// \brief Receiver constructor.
    ///
    /// \param socket A socket for receiving packets.
    /// \param single_threaded A flag indicating running mode.
    /// \param ip_version An IP version: 4 or 6
    Receiver(BasePerfSocket &socket, bool single_threaded, uint8_t ip_version) :
        socket_(socket),
        single_threaded_(single_threaded),
        ip_version_(ip_version) {
        run_flag_.clear();
    }

    /// \brief Destructor.
    ~Receiver();

    /// \brief Start a receiving thread in multi-thread mode.
    ///
    /// In single-thread mode it does nothing.
    void start();

    /// \brief Stop a receiving thread in multi-thread mode.
    ///
    /// In single-thread mode it does nothing.
    void stop();

    /// \brief Get DHCP packet.
    ///
    /// In single-thread mode it reads directly from the socket.
    /// In multi-thread mode it reads packets from the queue.
    dhcp::PktPtr getPkt();

private:
    /// \brief Receiving thread main function.
    void run();

    /// \brief Receive packets from sockets and pushes them to the queue.
    ///
    /// It runs in a loop until socket is empty.
    void receivePackets();

    /// \brief Read a packet directly from the socket.
    dhcp::PktPtr readPktFromSocket();
};

}
}

#endif /* PERFDHCP_RECEIVER_H */
