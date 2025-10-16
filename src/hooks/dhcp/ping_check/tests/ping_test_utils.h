// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PING_TEST_UTILS_H
#define PING_TEST_UTILS_H

#include <ping_channel.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <asiolink/io_address.h>
#include <testutils/gtest_utils.h>
#include <asiolink/io_service_thread_pool.h>
#include <util/multi_threading_mgr.h>
#include <mutex>

#include <gtest/gtest.h>
#include <queue>
#include <list>
#include <thread>
#include <map>

namespace isc {
namespace ping_check {

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Maps IOAddresses to sequence numbers.
///
/// Outbound requests are assigned a unique id and sequence
/// number.  This map is used to track the request's destination
/// address by its sequence number.  The channel can then substitute
/// the loopback address, 127.0.0.1, as the destination address.
/// Upon response receipt,  the original destination can be found by
/// the sequence number sent back in the response.
class LoopbackMap {
public:
    /// @brief Constructor.
    LoopbackMap() : map_(), mutex_(new std::mutex) {
    }

    /// @brief Destructor.
    ~LoopbackMap() = default;

    /// @brief Find and IOAddress associated with a sequence number.
    ///
    /// @param sequence sequence number to search by
    ///
    /// @return address found or IPV4_ZERO_ADDRESS.
    asiolink::IOAddress find(uint16_t sequence) {
        util::MultiThreadingLock lock(*mutex_);
        auto const& iter = map_.find(sequence);
        if (iter == map_.end()) {
            return (asiolink::IOAddress::IPV4_ZERO_ADDRESS());
        }

        return (iter->second);
    }

    /// @brief Adds an entry for a sequence number and address
    ///
    /// @param sequence sequence number associated with the address
    /// @param address  address to add to the map
    ///
    /// @return true if the entry was added, false otherwise.
    bool add(uint16_t sequence, const asiolink::IOAddress& address) {
        util::MultiThreadingLock lock(*mutex_);
        if (map_.count(sequence)) {
            return (false);
        }

        map_.emplace(sequence, address);
        return (true);
    };

    /// @brief Map of addresses by sequence number.
    std::map<uint16_t, asiolink::IOAddress> map_;

    /// @brief Mutex to protect the map during operations.
    const boost::scoped_ptr<std::mutex> mutex_;
};

/// @brief Testable derivation of PingChannel
///
/// Overrides read and write functions to inject IO errors.
class TestablePingChannel : public PingChannel {
public:
    /// @brief Constructor
    ///
    /// Instantiates the channel with its socket closed.
    ///
    /// @param io_service pointer to the IOService instance that will manage
    /// the channel's IO. Must not be empty
    /// @param next_to_send_cb callback to invoke to fetch the next IOAddress
    /// to ping
    /// @param echo_sent_cb callback to invoke when an ECHO send has completed
    /// @param reply_received_cb callback to invoke when an ICMP reply has been
    /// received.  This callback is passed all inbound ICMP messages (e.g. ECHO
    /// REPLY, UNREACHABLE, etc...)
    /// @param shutdown_cb callback to invoke when the channel has shutdown due
    /// to an error
    ///
    /// @throw BadValue if io_service is empty.
    TestablePingChannel(asiolink::IOServicePtr& io_service,
                        NextToSendCallback next_to_send_cb,
                        UpdateToSendCallback update_to_send_cb,
                        EchoSentCallback echo_sent_cb,
                        ReplyReceivedCallback reply_received_cb,
                        ShutdownCallback shutdown_cb = ShutdownCallback())
        : PingChannel(io_service, next_to_send_cb, update_to_send_cb, echo_sent_cb, reply_received_cb, shutdown_cb),
          read_number_(0), throw_on_read_number_(0), ec_on_read_number_(0), read_error_ec_(),
          write_number_(0), throw_on_write_number_(0), ec_on_write_number_(0), write_error_ec_(),
          route_loopback_(true), loopback_map_(), stopped_(false) {
    }

    /// @brief Virtual destructor
    virtual ~TestablePingChannel() {
        stopped_ = true;
    }

    // @brief Schedules the next send.
    //
    // If the socket is not currently sending it posts a call to @c sendNext()
    // to the channel's IOService.
    virtual void startSend() {
        if (stopped_) {
            return;
        }
        PingChannel::startSend();
    }

    /// @brief Perform asynchronous read or feign a read error
    ///
    /// This virtual function is provided as means to inject errors during
    /// read operations to facilitate testing.  It tracks the number of
    /// reads that have occurred since channel open and instigates an
    /// error trigger on the trigger read number if a trigger has been set.
    ///
    /// @param data buffer to receive incoming message
    /// @param length length of the data buffer
    /// @param offset offset into buffer where data is to be put
    /// @param endpoint source of the communication
    /// @param callback callback object
    virtual void asyncReceive(void* data, size_t length, size_t offset,
                              asiolink::IOEndpoint* endpoint, SocketCallback& callback) {
        if (stopped_) {
            return;
        }
        ++read_number_;

        // If we're set to fail with an exception, do so.
        if (throw_on_read_number_ && (read_number_ == throw_on_read_number_)) {
            isc_throw(Unexpected, "Injected read error");
        }

        // If we're set to fail via the callback, post a call with the
        // desired error code.
        if (ec_on_read_number_ && read_number_ == ec_on_read_number_) {
            getIOService()->post([this]() { socketReadCallback(read_error_ec_, 0); });
            return;
        }

        // No scheduled error, proceed with normal read.
        PingChannel::asyncReceive(data, length, offset, endpoint, callback);
    }

    /// @brief Perform asynchronous write or feign a write error
    ///
    /// This virtual function is provided as means to inject errors during
    /// write operations to facilitate testing.  It tracks the number of
    /// writes that have occurred since channel open and instigates an
    /// error trigger on the trigger write number if a trigger has been set.
    ///
    /// @param data buffer of data to write
    /// @param length length of the data buffer
    /// @param endpoint destination of the communication
    /// @param callback callback object
    virtual void asyncSend(void* data, size_t length, asiolink::IOEndpoint* endpoint,
                           SocketCallback& callback) {
        if (stopped_) {
            return;
        }
        ++write_number_;
        if (throw_on_write_number_ && (write_number_ == throw_on_write_number_)) {
            isc_throw(Unexpected, "Injected write error");
        }

        if (ec_on_write_number_ && write_number_ == ec_on_write_number_) {
            ICMPMsgPtr fake_echo(new ICMPMsg());
            fake_echo->setType(ICMPMsg::ECHO_REQUEST);
            fake_echo->setDestination(endpoint->getAddress());
            getIOService()->post([this, fake_echo]() { socketWriteCallback(fake_echo, write_error_ec_, 0); });
            return;
        }

        // In order to make testing more predictable, we need slow writes down a bit.
        usleep(5000);

        // If loopback routing is enabled, store the destination address by
        // sequence number in the loopback map, then replace the destination
        // endpoint with 127.0.0.1 and send it there.
        if (route_loopback_) {
            struct icmp* reply = (struct icmp*)(data);
            auto sequence = (ntohs(reply->icmp_hun.ih_idseq.icd_seq));
            loopback_map_.add(sequence, endpoint->getAddress());
            ICMPEndpoint lo_endpoint(asiolink::IOAddress("127.0.0.1"));
            PingChannel::asyncSend(data, length, &lo_endpoint, callback);
            return;
        }

        PingChannel::asyncSend(data, length, endpoint, callback);
    }

    /// @brief Fetches the PingSocket.
    ///
    /// @return pointer to the PingSocket instance.
    PingSocketPtr getPingSocket() {
        return (socket_);
    }

    /// @brief Checks if channel was opened in single-threaded mode.
    ///
    /// @return True if channel is single-threaded.
    bool getSingleThreaded() const {
        return (single_threaded_);
    }

    /// @brief Fetch the WatchSocket instance.
    ///
    /// @return pointer to the WatchSocket.
    util::WatchSocketPtr getWatchSocket() const {
        return (watch_socket_);
    }

    /// @brief The "write-ready" socket descriptor registered IfaceMgr.
    ///
    /// @return registered socket descriptor.
    int getRegisteredWriteFd() const {
        return (registered_write_fd_);
    }

    /// @brief The "read-ready" socket descriptor registered IfaceMgr.
    ///
    /// @return registered socket descriptor.
    int getRegisteredReadFd() const {
        return (registered_read_fd_);
    }

    /// @brief Tracks the number of reads since the channel was created
    size_t read_number_;

    /// @brief Read number on which to thrown an exception from asyncReceive()
    size_t throw_on_read_number_;

    /// @brief Read number on which to inject a socketReadCallback with an error code
    size_t ec_on_read_number_;

    /// @brief Error code to inject on read error trigger
    boost::system::error_code read_error_ec_;

    /// @brief Tracks the number of writes since the channel was created
    size_t write_number_;

    /// @brief Write number on which to thrown an exception from asyncSend()
    size_t throw_on_write_number_;

    /// @brief Error code to inject on write error trigger
    size_t ec_on_write_number_;

    /// @brief Error code to inject on write error trigger
    boost::system::error_code write_error_ec_;

    /// @brief Enables routing of 127.0.0.x by to 127.0.0.1 via sequence number.
    bool route_loopback_;

    /// @brief Maps loopback addresses to sequence numbers when loopback routing
    /// is enabled.
    LoopbackMap loopback_map_;

    /// @brief Flag which indicates that the manager has been stopped.
    bool stopped_;
};

/// @brief Defines a pointer to a TestablePingChannel
typedef boost::shared_ptr<TestablePingChannel> TestablePingChannelPtr;

/// @brief Defines a callback type for test completion check functions.
typedef std::function<bool()> TestDoneCallback;

/// @brief Test fixture class which uses an IOService for time management and/or IO
class IOServiceTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ///
    /// Starts test timer which detects timeouts.
    IOServiceTest()
        : test_io_service_(new asiolink::IOService()),
          test_timer_(test_io_service_),
          run_io_service_timer_(test_io_service_),
          test_done_cb_() {
        test_timer_.setup(std::bind(&IOServiceTest::timeoutHandler, this, true),
                          TEST_TIMEOUT,
                          asiolink::IntervalTimer::ONE_SHOT);
    }

    /// @brief Indicates if current user is not root
    ///
    /// @return True if neither the uid or the effective
    /// uid is root.
    static bool notRoot() {
        return (getuid() != 0 && geteuid() != 0);
    }

    /// @brief Destructor.
    ///
    /// Removes active clients.
    virtual ~IOServiceTest() {
        test_timer_.cancel();
        run_io_service_timer_.cancel();
        test_io_service_->stopAndPoll();
    }

    /// @brief Callback function invoke upon test timeout.
    ///
    /// It stops the IO service and reports test timeout.
    ///
    /// @param fail_on_timeout Specifies if test failure should be reported.
    void timeoutHandler(const bool fail_on_timeout) {
        if (fail_on_timeout) {
            ADD_FAILURE() << "Timeout occurred while running the test!";
        }

        test_io_service_->stop();
    }

    /// @brief Stops the IOService if criteria for test completion has been met.
    ///
    /// Stops the IOService If there either no test completion callback or the
    /// call back returns true.
    void stopIfDone() {
        // If there is no done test callback or it returns true, stop the service.
        if (!test_done_cb_ || (test_done_cb_)()) {
            test_io_service_->stop();
        }
    }

    /// @brief Posts a call to stop the io service to the io service.
    ///
    /// This should be used when stopping the service from callbacks on
    /// thread pool threads.
    void stopTestService() {
        if (!test_io_service_->stopped()) {
            test_io_service_->post([&]() { test_io_service_->stop(); });
        }
    }

    /// @brief Runs IO service with optional timeout.
    ///
    /// @param timeout number of milliseconds to run the io service. Defaults to
    /// zero which means run forever.
    void runIOService(long timeout = 0) {
        test_io_service_->stop();
        test_io_service_->restart();

        if (timeout > 0) {
            run_io_service_timer_.setup(std::bind(&IOServiceTest::timeoutHandler,
                                                  this, false),
                                        timeout,
                                        asiolink::IntervalTimer::ONE_SHOT);
        }

        test_io_service_->run();
        test_io_service_->stopAndPoll();
    }

    /// @brief IO service used in the tests.
    asiolink::IOServicePtr test_io_service_;

    /// @brief Asynchronous timer service to detect timeouts.
    asiolink::IntervalTimer test_timer_;

    /// @brief Asynchronous timer for running IO service for a specified amount
    /// of time.
    asiolink::IntervalTimer run_io_service_timer_;

    /// @brief Callback function which event handlers can use to check if service
    /// run should stop.
    TestDoneCallback test_done_cb_;
};

} // end of namespace ping_check
} // end of namespace isc

#endif
