// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <stdint.h>

#include <functional>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <exceptions/exceptions.h>

#include <dns/tests/unittest_util.h>

#include <auth/asio_link.h>

#include <boost/date_time/posix_time/posix_time_types.hpp>

using isc::UnitTestUtil;
using namespace std;
using namespace asio_link;

namespace {
const char* const TEST_PORT = "53535";
const char* const TEST_IPV6_ADDR = "::1";
const char* const TEST_IPV4_ADDR = "127.0.0.1";
// This data is intended to be valid as a DNS/TCP-like message: the first
// two octets encode the length of the rest of the data.  This is crucial
// for the tests below.
const uint8_t test_data[] = {0, 4, 1, 2, 3, 4};
// TODO: Consider this mergin
const boost::posix_time::time_duration TIMER_MERGIN_MSEC =
    boost::posix_time::milliseconds(50);

TEST(IOAddressTest, fromText) {
    IOAddress io_address_v4("192.0.2.1");
    EXPECT_EQ("192.0.2.1", io_address_v4.toText());

    IOAddress io_address_v6("2001:db8::1234");
    EXPECT_EQ("2001:db8::1234", io_address_v6.toText());

    // bogus IPv4 address-like input
    EXPECT_THROW(IOAddress("192.0.2.2.1"), IOError);

    // bogus IPv6 address-like input
    EXPECT_THROW(IOAddress("2001:db8:::1234"), IOError);
}

TEST(IOEndpointTest, create) {
    const IOEndpoint* ep;
    ep = IOEndpoint::create(IPPROTO_UDP, IOAddress("192.0.2.1"), 5300);
    EXPECT_EQ("192.0.2.1", ep->getAddress().toText());
    delete ep;

    ep = IOEndpoint::create(IPPROTO_TCP, IOAddress("192.0.2.1"), 5300);
    EXPECT_EQ("192.0.2.1", ep->getAddress().toText());
    delete ep;

    ep = IOEndpoint::create(IPPROTO_UDP, IOAddress("2001:db8::1234"), 5300);
    EXPECT_EQ("2001:db8::1234", ep->getAddress().toText());
    delete ep;

    ep = IOEndpoint::create(IPPROTO_TCP, IOAddress("2001:db8::1234"), 5300);
    EXPECT_EQ("2001:db8::1234", ep->getAddress().toText());
    delete ep;

    EXPECT_THROW(IOEndpoint::create(IPPROTO_IP, IOAddress("192.0.2.1"),
                                    5300)->getAddress().toText(),
                 IOError);
}

TEST(IOSocketTest, dummySockets) {
    EXPECT_EQ(IPPROTO_UDP, IOSocket::getDummyUDPSocket().getProtocol());
    EXPECT_EQ(IPPROTO_TCP, IOSocket::getDummyTCPSocket().getProtocol());
    EXPECT_EQ(-1, IOSocket::getDummyUDPSocket().getNative());
    EXPECT_EQ(-1, IOSocket::getDummyTCPSocket().getNative());
}

TEST(IOServiceTest, badPort) {
    EXPECT_THROW(IOService(NULL, *"65536", true, false), IOError);
    EXPECT_THROW(IOService(NULL, *"5300.0", true, false), IOError);
    EXPECT_THROW(IOService(NULL, *"-1", true, false), IOError);
    EXPECT_THROW(IOService(NULL, *"domain", true, false), IOError);
}

TEST(IOServiceTest, badAddress) {
    EXPECT_THROW(IOService(NULL, *TEST_PORT, *"192.0.2.1.1"),
                 IOError);
    EXPECT_THROW(IOService(NULL, *TEST_PORT, *"2001:db8:::1"),
                 IOError);
    EXPECT_THROW(IOService(NULL, *TEST_PORT, *"localhost"),
                 IOError);
}

TEST(IOServiceTest, unavailableAddress) {
    // These addresses should generally be unavailable as a valid local
    // address, although there's no guarantee in theory.
    EXPECT_THROW(IOService(NULL, *TEST_PORT, *"255.255.0.0"), IOError);

    // Some OSes would simply reject binding attempt for an AF_INET6 socket
    // to an IPv4-mapped IPv6 address.  Even if those that allow it, since
    // the corresponding IPv4 address is the same as the one used in the
    // AF_INET socket case above, it should at least show the same result
    // as the previous one.
    EXPECT_THROW(IOService(NULL, *TEST_PORT, *"::ffff:255.255.0.0"), IOError);
}

TEST(IOServiceTest, duplicateBind) {
    // In each sub test case, second attempt should fail due to duplicate bind

    // IPv6, "any" address
    IOService* io_service = new IOService(NULL, *TEST_PORT, false, true);
    EXPECT_THROW(IOService(NULL, *TEST_PORT, false, true), IOError);
    delete io_service;

    // IPv6, specific address
    io_service = new IOService(NULL, *TEST_PORT, *TEST_IPV6_ADDR);
    EXPECT_THROW(IOService(NULL, *TEST_PORT, *TEST_IPV6_ADDR), IOError);
    delete io_service;

    // IPv4, "any" address
    io_service = new IOService(NULL, *TEST_PORT, true, false);
    EXPECT_THROW(IOService(NULL, *TEST_PORT, true, false), IOError);
    delete io_service;

    // IPv4, specific address
    io_service = new IOService(NULL, *TEST_PORT, *TEST_IPV4_ADDR);
    EXPECT_THROW(IOService(NULL, *TEST_PORT, *TEST_IPV4_ADDR), IOError);
    delete io_service;
}

struct addrinfo*
resolveAddress(const int family, const int sock_type, const int protocol) {
    const char* const addr = (family == AF_INET6) ?
        TEST_IPV6_ADDR : TEST_IPV4_ADDR;

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = family;
    hints.ai_socktype = sock_type;
    hints.ai_protocol = protocol;

    struct addrinfo* res;
    const int error = getaddrinfo(addr, TEST_PORT, &hints, &res);
    if (error != 0) {
        isc_throw(IOError, "getaddrinfo failed: " << gai_strerror(error));
    }

    return (res);
}

// This fixture is a framework for various types of network operations
// using the ASIO interfaces.  Each test case creates an IOService object,
// opens a local "client" socket for testing, sends data via the local socket
// to the service that would run in the IOService object.
// A mock callback function (an ASIOCallBack object) is registered with the
// IOService object, so the test code should be able to examine the data
// receives on the server side.  It then checks the received data matches
// expected parameters.
// If initialization parameters of the IOService should be modified, the test
// case can do it using the setIOService() method.
// Note: the set of tests in ASIOLinkTest use actual network services and may
// involve undesirable side effect such as blocking.
class ASIOLinkTest : public ::testing::Test {
protected:
    ASIOLinkTest();
    ~ASIOLinkTest() {
        if (res_ != NULL) {
            freeaddrinfo(res_);
        }
        if (sock_ != -1) {
            close(sock_);
        }
        delete io_service_;
    }
    void sendUDP(const int family) {
        res_ = resolveAddress(family, SOCK_DGRAM, IPPROTO_UDP);

        sock_ = socket(res_->ai_family, res_->ai_socktype, res_->ai_protocol);
        if (sock_ < 0) {
            isc_throw(IOError, "failed to open test socket");
        }
        const int cc = sendto(sock_, test_data, sizeof(test_data), 0,
                              res_->ai_addr, res_->ai_addrlen);
        if (cc != sizeof(test_data)) {
            isc_throw(IOError, "unexpected sendto result: " << cc);
        }
        io_service_->run();
    }
    void sendTCP(const int family) {
        res_ = resolveAddress(family, SOCK_STREAM, IPPROTO_TCP);

        sock_ = socket(res_->ai_family, res_->ai_socktype, res_->ai_protocol);
        if (sock_ < 0) {
            isc_throw(IOError, "failed to open test socket");
        }
        if (connect(sock_, res_->ai_addr, res_->ai_addrlen) < 0) {
            isc_throw(IOError, "failed to connect to the test server");
        }
        const int cc = send(sock_, test_data, sizeof(test_data), 0);
        if (cc != sizeof(test_data)) {
            isc_throw(IOError, "unexpected sendto result: " << cc);
        }
        io_service_->run();
    }
    void setIOService(const char& address) {
        delete io_service_;
        io_service_ = NULL;
        io_service_ = new IOService(NULL, *TEST_PORT, address);
        io_service_->setCallBack(ASIOCallBack(this));
    }
    void setIOService(const bool use_ipv4, const bool use_ipv6) {
        delete io_service_;
        io_service_ = NULL;
        io_service_ = new IOService(NULL, *TEST_PORT, use_ipv4, use_ipv6);
        io_service_->setCallBack(ASIOCallBack(this));
    }
    void doTest(const int family, const int protocol) {
        if (protocol == IPPROTO_UDP) {
            sendUDP(family);
        } else {
            sendTCP(family);
        }

        // There doesn't seem to be an effective test for the validity of
        // 'native'.
        // One thing we are sure is it must be different from our local socket.
        EXPECT_NE(sock_, callback_native_);
        EXPECT_EQ(protocol, callback_protocol_);
        EXPECT_EQ(family == AF_INET6 ? TEST_IPV6_ADDR : TEST_IPV4_ADDR,
                  callback_address_);

        const uint8_t* expected_data =
            protocol == IPPROTO_UDP ? test_data : test_data + 2;
        const size_t expected_datasize =
            protocol == IPPROTO_UDP ? sizeof(test_data) :
            sizeof(test_data) - 2;
        EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, &callback_data_[0],
                            callback_data_.size(),
                            expected_data, expected_datasize);
    }
    class TimerCallBack : public std::unary_function<void, void> {
    public:
        TimerCallBack(ASIOLinkTest* test_obj) : test_obj_(test_obj) {}
        void operator()() const {
            test_obj_->timer_called_ = true;
            test_obj_->io_service_->stop();
            return;
        }
    private:
        ASIOLinkTest* test_obj_;
    };
    class TimerCallBackCounter : public std::unary_function<void, void> {
    public:
        TimerCallBackCounter(ASIOLinkTest* test_obj) : test_obj_(test_obj) {
            counter_ = 0;
        }
        void operator()() {
            ++counter_;
            return;
        }
        int counter_;
    private:
        ASIOLinkTest* test_obj_;
    };
    class TimerCallBackCancelDeleter : public std::unary_function<void, void> {
    public:
        TimerCallBackCancelDeleter(ASIOLinkTest* test_obj,
                                   IntervalTimer* timer,
                                   TimerCallBackCounter& counter)
            : test_obj_(test_obj), timer_(timer), counter_(counter), count_(0)
        {}
        void operator()() {
            ++count_;
            if (count_ == 1) {
                // First time of call back.
                // Store the value of counter_.counter_.
                prev_counter_ = counter_.counter_;
                delete timer_;
            } else if (count_ == 2) {
                // Second time of call back.
                // Stop io_service to stop all timers.
                test_obj_->io_service_->stop();
                // Compare the value of counter_.counter_ with stored one.
                // If TimerCallBackCounter was not called (expected behavior),
                // they are same.
                if (counter_.counter_ == prev_counter_) {
                    test_obj_->timer_cancel_success_ = true;
                }
            }
            return;
        }
    private:
        ASIOLinkTest* test_obj_;
        IntervalTimer* timer_;
        TimerCallBackCounter& counter_;
        int count_;
        int prev_counter_;
    };
    class TimerCallBackOverwriter : public std::unary_function<void, void> {
    public:
        TimerCallBackOverwriter(ASIOLinkTest* test_obj,
                                IntervalTimer& timer)
            : test_obj_(test_obj), timer_(timer), count_(0)
        {}
        void operator()() {
            ++count_;
            if (count_ == 1) {
                // First time of call back.
                // Call setupTimer() to update callback function
                // to TimerCallBack.
                test_obj_->timer_called_ = false;
                timer_.setupTimer(IntervalTimer::Callback(
                                       TimerCallBack(test_obj_)), 1);
            } else if (count_ == 2) {
                // Second time of call back.
                // If it reaches here, re-setupTimer() is failed (unexpected).
                // We should stop here.
                test_obj_->io_service_->stop();
            }
            return;
        }
    private:
        ASIOLinkTest* test_obj_;
        IntervalTimer& timer_;
        int count_;
    };
private:
    class ASIOCallBack : public std::unary_function<IOMessage, void> {
    public:
        ASIOCallBack(ASIOLinkTest* test_obj) : test_obj_(test_obj) {}
        void operator()(const IOMessage& io_message) const {
            test_obj_->callBack(io_message);
        }
    private:
        ASIOLinkTest* test_obj_;
    };
    void callBack(const IOMessage& io_message) {
        callback_protocol_ = io_message.getSocket().getProtocol();
        callback_native_ = io_message.getSocket().getNative();
        callback_address_ =
            io_message.getRemoteEndpoint().getAddress().toText();
        callback_data_.assign(
            static_cast<const uint8_t*>(io_message.getData()),
            static_cast<const uint8_t*>(io_message.getData()) +
            io_message.getDataSize());
        io_service_->stop();
    }
protected:
    IOService* io_service_;
    int callback_protocol_;
    int callback_native_;
    string callback_address_;
    vector<uint8_t> callback_data_;
    bool timer_called_;
    bool timer_cancel_success_;
    int sock_;
private:
    struct addrinfo* res_;
};

ASIOLinkTest::ASIOLinkTest() :
    io_service_(NULL), sock_(-1), res_(NULL)
{
    setIOService(true, true);
}

TEST_F(ASIOLinkTest, v6UDPSend) {
    doTest(AF_INET6, IPPROTO_UDP);
}

TEST_F(ASIOLinkTest, v6TCPSend) {
    doTest(AF_INET6, IPPROTO_TCP);
}

TEST_F(ASIOLinkTest, v4UDPSend) {
    doTest(AF_INET, IPPROTO_UDP);
}

TEST_F(ASIOLinkTest, v4TCPSend) {
    doTest(AF_INET, IPPROTO_TCP);
}

TEST_F(ASIOLinkTest, v6UDPSendSpecific) {
    // Explicitly set a specific address to be bound to the socket.
    // The subsequent test does not directly ensures the underlying socket
    // is bound to the expected address, but the success of the tests should
    // reasonably suggest it works as intended.
    // Specifying an address also implicitly means the service runs in a
    // single address-family mode.  In tests using TCP we can confirm that
    // by trying to make a connection and seeing a failure.  In UDP, it'd be
    // more complicated because we need to use a connected socket and catch
    // an error on a subsequent read operation.  We could do it, but for
    // simplicity we only tests the easier cases for now.

    setIOService(*TEST_IPV6_ADDR);
    doTest(AF_INET6, IPPROTO_UDP);
}

TEST_F(ASIOLinkTest, v6TCPSendSpecific) {
    setIOService(*TEST_IPV6_ADDR);
    doTest(AF_INET6, IPPROTO_TCP);

    EXPECT_THROW(sendTCP(AF_INET), IOError);
}

TEST_F(ASIOLinkTest, v4UDPSendSpecific) {
    setIOService(*TEST_IPV4_ADDR);
    doTest(AF_INET, IPPROTO_UDP);
}

TEST_F(ASIOLinkTest, v4TCPSendSpecific) {
    setIOService(*TEST_IPV4_ADDR);
    doTest(AF_INET, IPPROTO_TCP);

    EXPECT_THROW(sendTCP(AF_INET6), IOError);
}

TEST_F(ASIOLinkTest, v6TCPOnly) {
    // Open only IPv6 TCP socket.  A subsequent attempt of establishing an
    // IPv4/TCP connection should fail.  See above for why we only test this
    // for TCP.
    setIOService(false, true);
    EXPECT_THROW(sendTCP(AF_INET), IOError);
}

TEST_F(ASIOLinkTest, v4TCPOnly) {
    setIOService(true, false);
    EXPECT_THROW(sendTCP(AF_INET6), IOError);
}

TEST_F(ASIOLinkTest, invalidArgumentToIntervalTimer) {
    // Create asio_link::IntervalTimer and setup.
    setIOService(false, false);
    IntervalTimer itimer(*io_service_);
    // expect throw if call back function is empty
    EXPECT_THROW(itimer.setupTimer(
                     IntervalTimer::Callback(), 1),
                     isc::InvalidParameter);
    // expect throw if interval is 0
    EXPECT_THROW(itimer.setupTimer(
                     IntervalTimer::Callback(TimerCallBack(this)), 0),
                     isc::BadValue);
}

TEST_F(ASIOLinkTest, startIntervalTimer) {
    // Create asio_link::IntervalTimer and setup.
    // Then run IOService and test if the callback function is called.
    setIOService(false, false);
    IntervalTimer itimer(*io_service_);
    timer_called_ = false;
    // store start time
    boost::posix_time::ptime start;
    start = boost::posix_time::microsec_clock::universal_time();
    // setup timer
    EXPECT_NO_THROW(itimer.setupTimer(
                        IntervalTimer::Callback(TimerCallBack(this)),
                        1));
    io_service_->run();
    // reaches here after timer expired
    // delta: difference between elapsed time and 1 second
    boost::posix_time::time_duration delta =
        (boost::posix_time::microsec_clock::universal_time() - start)
         - boost::posix_time::seconds(1);
    if (delta.is_negative()) {
        delta.invert_sign();
    }
    // expect call back is updated: TimerCallBack is called
    EXPECT_TRUE(timer_called_);
    // expect interval is 1 second +/- TIMER_MERGIN_MSEC.
    EXPECT_TRUE(delta < TIMER_MERGIN_MSEC);
}

TEST_F(ASIOLinkTest, destructIntervalTimer) {
    // The call back function will not be called
    // after the timer destucted.
    setIOService(false, false);
    // There are two timers:
    //  itimer_counter (A)
    //   (Calls TimerCallBackCounter)
    //     - increments internal counter in callback function
    //  itimer_canceller (B)
    //   (Calls TimerCallBackCancelDeleter)
    //     - first time of callback, it stores the counter value of
    //       callback_canceller and destructs itimer_counter
    //     - second time of callback, it compares the counter value of
    //       callback_canceller with stored value
    //       if they are same the timer was not called; expected result
    //       if they are different the timer was called after destructed
    //
    //     0  1  2  3  4  5  6 (s)
    // (A) i-----+--x
    //              ^
    //              |destruct itimer_counter
    // (B) i--------+--------s
    //                       ^stop io_service
    //                        and test itimer_counter have been stopped

    // itimer_counter will be deleted in
    // TimerCallBackCancelDeleter
    IntervalTimer* itimer_counter = NULL;
    ASSERT_NO_THROW(itimer_counter = new IntervalTimer(*io_service_));
    IntervalTimer itimer_canceller(*io_service_);
    timer_cancel_success_ = false;
    TimerCallBackCounter callback_canceller(this);
    itimer_counter->setupTimer(IntervalTimer::Callback(callback_canceller), 2);
    itimer_canceller.setupTimer(
        IntervalTimer::Callback(
            TimerCallBackCancelDeleter(this, itimer_counter,
                                       callback_canceller)),
        3);
    io_service_->run();
    EXPECT_TRUE(timer_cancel_success_);
}

TEST_F(ASIOLinkTest, overwriteIntervalTimer) {
    // Calling setupTimer() multiple times updates call back
    // function and interval.
    setIOService(false, false);
    // There are two timers:
    //  itimer (A)
    //   (Calls TimerCallBackCounter / TimerCallBack)
    //     - increments internal counter in callback function
    //       (TimerCallBackCounter)
    //       interval: 2 seconds
    //     - io_service_->stop() (TimerCallBack)
    //       interval: 1 second
    //  itimer_overwriter (B)
    //   (Calls TimerCallBackOverwriter)
    //     - first time of callback, it calls setupTimer() to change
    //       call back function and interval  of itimer to
    //       TimerCallBack / 1 second
    //       after 3 + 1 seconds from the beginning of this test,
    //       TimerCallBack() will be called and io_service_ stops.
    //     - second time of callback, it means the test fails.
    //
    //     0  1  2  3  4  5  6 (s)
    // (A) i-----+--C--s
    //              ^  ^stop io_service
    //              |change call back function
    // (B) i--------+--------S
    //                       ^(stop io_service on fail)

    IntervalTimer itimer(*io_service_);
    IntervalTimer itimer_overwriter(*io_service_);
    // store start time
    boost::posix_time::ptime start;
    start = boost::posix_time::microsec_clock::universal_time();
    itimer.setupTimer(IntervalTimer::Callback(TimerCallBackCounter(this)), 2);
    itimer_overwriter.setupTimer(
        IntervalTimer::Callback(TimerCallBackOverwriter(this, itimer)), 3);
    io_service_->run();
    // reaches here after timer expired
    // if interval is updated, it takes
    //   3 seconds for TimerCallBackOverwriter
    //   + 1 second for TimerCallBack (stop)
    //   = 4 seconds.
    // otherwise (test fails), it takes
    //   3 seconds for TimerCallBackOverwriter
    //   + 3 seconds for TimerCallBackOverwriter (stop)
    //   = 6 seconds.
    // delta: difference between elapsed time and 3 + 1 seconds
    boost::posix_time::time_duration delta =
        (boost::posix_time::microsec_clock::universal_time() - start)
         - boost::posix_time::seconds(3 + 1);
    if (delta.is_negative()) {
        delta.invert_sign();
    }
    // expect call back is updated: TimerCallBack is called
    EXPECT_TRUE(timer_called_);
    // expect interval is updated
    EXPECT_TRUE(delta < TIMER_MERGIN_MSEC);
}
}
