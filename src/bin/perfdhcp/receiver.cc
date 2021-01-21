// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <perfdhcp/receiver.h>
#include <perfdhcp/command_options.h>

#include <dhcp/iface_mgr.h>

#include <functional>

using namespace std;
using namespace isc::dhcp;

namespace isc {
namespace perfdhcp {


void
Receiver::start() {
    if (single_threaded_) {
        return;
    }
    if (run_flag_.test_and_set()) {
        run_flag_.clear();
        isc_throw(isc::Unexpected, "run_flag_ should be false.");
    }
    recv_thread_.reset(new std::thread(std::bind(&Receiver::run, this)));
}

void
Receiver::stop() {
    if (single_threaded_) {
        return;
    }

    // If thread is running then...
    if (run_flag_.test_and_set()) {
        // Clear flags to order the thread to stop its main loop.
        run_flag_.clear();
        recv_thread_->join();
    }
}

Receiver::~Receiver() {
    if (single_threaded_) {
        return;
    }
    stop();
}


PktPtr
Receiver::getPkt() {
    if (single_threaded_) {
        // In single thread mode read packet directly from the socket and return it.
        return readPktFromSocket();
    } else {
        // In multi thread mode read packet from the queue which is feed by Receiver thread.
        std::lock_guard<std::mutex> lock(pkt_queue_mutex_);
        if (pkt_queue_.empty()) {
            if (ip_version_ == 4) {
                return Pkt4Ptr();
            } else {
                return Pkt6Ptr();
            }
        }
        auto pkt = pkt_queue_.front();
        pkt_queue_.pop();
        return pkt;
    }
}

void
Receiver::run() {
    if (single_threaded_) {
        isc_throw(isc::Unexpected, "run should not be invoked in single-thread mode.");
    }
    try {
        // If the flag is still true receive packets.
        while (run_flag_.test_and_set()) {
            receivePackets();
        }

        // Clear run flag so that subsequent call to stop will not try to stop again.
        run_flag_.clear();
    } catch (const exception& e) {
        cerr << "Something went wrong: " << e.what() << endl;
        usleep(1000);
    } catch (...) {
        cerr << "Something went wrong" << endl;
        usleep(1000);
    }
}

PktPtr
Receiver::readPktFromSocket() {
    PktPtr pkt;
    uint32_t timeout;
    if (single_threaded_) {
        // In case of single thread just check socket and if empty exit immediately
        // to not slow down sending part.
        timeout = 0;
    } else {
        // In case of multi thread wait for packets a little bit (1ms) as it is run
        // in separate thread and do not interfere with sending thread.
        timeout = 1000;
    }
    try {
        if (ip_version_ == 4) {
            pkt = socket_.receive4(0, timeout);
        } else {
            pkt = socket_.receive6(0, timeout);
        }
    } catch (const Exception& e) {
        cerr << "Failed to receive DHCP packet: " << e.what() << endl;
    }

    return (pkt);
}

void
Receiver::receivePackets() {
    while (true) {
        PktPtr pkt = readPktFromSocket();
        if (!pkt) {
            break;
        }

        // Drop the packet if not supported. Do not bother main thread about it.
        if (pkt->getType() == DHCPOFFER || pkt->getType() == DHCPACK ||
            pkt->getType() == DHCPV6_ADVERTISE || pkt->getType() == DHCPV6_REPLY) {
            // Otherwise push the packet to the queue, to main thread.
            std::lock_guard<std::mutex> lock(pkt_queue_mutex_);
            pkt_queue_.push(pkt);
        }
    }
}

}
}
