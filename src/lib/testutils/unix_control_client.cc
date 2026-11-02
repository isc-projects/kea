// Copyright (C) 2015-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>
#include <asiolink/interval_timer.h>
#include <testutils/unix_control_client.h>
#include <util/ready_check.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <string.h>

using namespace isc::asiolink;
using namespace isc::util;

namespace ph = std::placeholders;

namespace isc {
namespace dhcp {
namespace test {

UnixControlClient::UnixControlClient(IOServicePtr io_service)
    : io_service_(io_service), socket_(io_service_) {
}

UnixControlClient::~UnixControlClient() {
    try {
        disconnectFromServer();
    } catch (...) {
        // Ignore all errors.
    }
}

    /// @brief Closes the Control Channel socket
void UnixControlClient::disconnectFromServer() {
    socket_.close();
    io_service_->stopAndPoll();
}

bool UnixControlClient::connectToServer(const std::string& socket_path) {
    bool result = true;
    bool done = false;
    socket_.asyncConnect(socket_path, [&done, &result](const boost::system::error_code& ec) {
        if (ec) {
            result = false;
        }
        done = true;
    });
    while (!done) {
        if (io_service_->stopped()) {
            io_service_->restart();
        }
        io_service_->runOne();
    }
    return (result);
}

bool UnixControlClient::sendCommand(const std::string& command) {
    size_t pos = 0;
    std::atomic<bool> done(false);
    std::atomic<bool> result(true);
    std::function<void(const boost::system::error_code&, size_t)> f =
        [&f, &command, &result, &done, &pos, this](const boost::system::error_code& ec,
                                                   size_t bytes_transferred) {
        if (ec) {
            result = false;
        } else {
            pos += bytes_transferred;
            if (pos < command.size()) {
                socket_.asyncSend(command.c_str() + pos, command.size() - pos, f);
                return;
            }
        }
        done = true;
    };
    socket_.asyncSend(command.c_str() + pos, command.size() - pos, f);
    while (!done) {
        if (io_service_->stopped()) {
            io_service_->restart();
        }
        io_service_->runOne();
    }

    return (result);
}

bool UnixControlClient::getResponse(std::string& response,
                                    const unsigned int timeout_sec) {
    std::atomic<bool> done(false);
    std::atomic<bool> result(true);
    std::array<char, 4096> buffer;
    std::mutex m;
    IntervalTimerPtr timer;
    if (timeout_sec) {
        timer.reset(new IntervalTimer(io_service_));
        timer->setup([&done, &result]() {
            done = true;
            result = false;
        }, timeout_sec * 1000, IntervalTimer::ONE_SHOT);
    }
    std::function<void(const boost::system::error_code&, size_t)> f =
        [&f, &response, &buffer, &result, &done, &m, this](const boost::system::error_code& ec,
                                                           size_t bytes_transferred) {
        if (!ec) {
            if (bytes_transferred) {
                std::scoped_lock<std::mutex> lk(m);
                response.append(buffer.data(), buffer.data() + bytes_transferred);
            }
            socket_.asyncReceive(buffer.data(), buffer.size(), f);
            return;
        } else if (ec != boost::asio::error::eof) {
            result = false;
        }
        done = true;
    };
    socket_.asyncReceive(buffer.data(), buffer.size(), f);
    while (!done) {
        if (io_service_->stopped()) {
            io_service_->restart();
        }
        io_service_->runOne();
    }
    if (timer) {
        timer->cancel();
        timer.reset();
    }

    return (result);
}

}
}
}
