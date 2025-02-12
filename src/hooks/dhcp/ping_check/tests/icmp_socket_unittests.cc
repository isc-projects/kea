// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// \brief Test of ICMPSocket
///
/// Tests the functionality of a ICMPSocket by working through an open-send-
/// receive-close sequence and checking that the asynchronous notifications
/// work.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <icmp_socket.h>
#include <icmp_msg.h>
#include <exceptions/exceptions.h>
#include <util/buffer.h>
#include <testutils/gtest_utils.h>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

#include <string>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <algorithm>
#include <cstdlib>
#include <cstddef>
#include <list>
#include <vector>
#include <unistd.h>

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

using namespace isc;
using namespace boost::asio;
using namespace boost::posix_time;
using namespace isc::asiolink;
using namespace isc::ping_check;
using namespace isc::util;
using namespace std;

namespace ph = std::placeholders;

namespace {

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Type of the function implementing a callback invoked by the
/// @c SocketCallback functor.
typedef std::function<void(boost::system::error_code ec, size_t length)>
        SocketCallbackFunction;

/// @brief  Callback class for socket IO operations
///
/// An instance of this object is passed to the asynchronous I/O functions
/// and the operator() method is called when when an asynchronous I/O
/// completes.  The arguments to the completion callback are stored for later
/// retrieval.
class SocketCallback {
public:

    /// @brief Structure that houses callback invocation data.
    struct PrivateData {
        PrivateData() :
            error_code_(), length_(0), called_(false), name_("")
        {}

        boost::system::error_code  error_code_;    ///< Completion error code
        size_t                     length_;        ///< Number of bytes transferred
        bool                       called_;        ///< Set true when callback called
        std::string                name_;          ///< Which of the objects this is
    };

    /// @brief Constructor
    ///
    /// Constructs the object.  It also creates the data member pointed to by
    /// a shared pointer.  When used as a callback object, this is copied as it
    /// is passed into the asynchronous function.  This means that there are two
    /// objects and inspecting the one we passed in does not tell us anything.
    ///
    /// Therefore we use a boost::shared_ptr.  When the object is copied, the
    /// shared pointer is copied, which leaves both objects pointing to the same
    /// data.
    ///
    /// @param which Which of the two callback objects this is
    explicit SocketCallback(const std::string& which) : data_(new PrivateData())
    {
        setName(which);
    }

    /// @brief Destructor
    ///
    /// No code needed, destroying the shared pointer destroys the private data.
    virtual ~SocketCallback()
    {}

    /// @brief Clears the current values of invocation data members.
    void clear() {
        setCode(0);
        setLength(0);
        setCalled(false);
    }

    /// @brief Callback Function
    ///
    /// Called when an asynchronous I/O completes, this stores the
    /// completion error code and the number of bytes transferred.
    ///
    /// @param ec I/O completion error code passed to callback function.
    /// @param length Number of bytes transferred
    virtual void operator()(boost::system::error_code ec, size_t length = 0) {
        data_->error_code_ = ec;
        setLength(length);
        setCalled(true);
    }

    /// @brief Get I/O completion error code
    int getCode() {
        return (data_->error_code_.value());
    }

    /// @brief Set I/O completion code
    ///
    /// @param code New value of completion code
    void setCode(int code) {
        data_->error_code_ = boost::system::error_code(code, boost::system::error_code().category());
    }

    /// @brief Get number of bytes transferred in I/O
    size_t getLength() const {
        return (data_->length_);
    }

    /// @brief Set number of bytes transferred in I/O
    ///
    /// @param length New value of length parameter
    void setLength(size_t length) {
        data_->length_ = length;
    }

    /// @brief Get flag to say when callback was called
    bool getCalled() const {
        return (data_->called_);
    }

    /// @brief Set flag to say when callback was called
    ///
    /// @param called New value of called parameter
    void setCalled(bool called) {
        data_->called_ = called;
    }

    /// @brief Return instance of callback name
    std::string getName() const {
        return (data_->name_);
    }

    /// @brief Set callback name
    ///
    /// @param name New value of the callback name
    void setName(const std::string& name) {
        data_->name_ = name;
    }

private:
    boost::shared_ptr<PrivateData> data_;   ///< Pointer to private data
};

/// @brief Socket and pointer types for sending and receiving ICMP echos.
typedef ICMPSocket<SocketCallback> PingSocket;
typedef boost::shared_ptr<PingSocket> PingSocketPtr;

/// @brief Simple test fixture for testing  ICMPSocket.
class ICMPSocketTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ICMPSocketTest()
        : io_service_(new IOService()), test_timer_(io_service_) {
        test_timer_.setup(std::bind(&ICMPSocketTest::timeoutHandler, this, true),
                          TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
    }

    /// @brief Destructor.
    virtual ~ICMPSocketTest() {
        test_timer_.cancel();
        io_service_->stopAndPoll();
    }

    /// @brief Indicates if current user is not root
    ///
    /// @return True if neither the uid or the effective
    /// uid is root.
    static bool notRoot() {
        return (getuid() != 0 && geteuid() != 0);
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
        io_service_->stop();
    }

    /// @brief IOService instance used by thread pools.
    IOServicePtr io_service_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Returns pointer to the first byte of the input buffer.
    ///
    /// @throw InvalidOperation if called when the buffer is empty.
    uint8_t* getInputBufData() {
        if (input_buf_.empty()) {
            isc_throw(InvalidOperation, "TcpConnection::getInputBufData() - cannot access empty buffer");
       }

        return (input_buf_.data());
    }

    /// @brief Returns input buffer size.
    size_t getInputBufSize() const {
        return (input_buf_.size());
    }

    /// @brief Set the capacity of the input buffer
    ///
    /// @param buf_size maximum number of bytes allowed in the buffer
    void resizeInputBuf(size_t buf_size) {
        input_buf_.resize(buf_size);
    }

    /// @brief Buffer for a single socket read.
    std::vector<uint8_t> input_buf_;
};


// Verifies that an ICMP socket can be opened and closed.
TEST_F(ICMPSocketTest, openClose) {
    SKIP_IF(notRoot());

    // For open the endpoint is only used to determine protocol, the address is irrelevant.
    ICMPEndpoint ping_to_endpoint(IOAddress::IPV4_ZERO_ADDRESS());

    PingSocket socket(io_service_);
    SocketCallback socket_cb("open");

    // Verify the socket is closed.
    ASSERT_FALSE(socket.isOpen());

    // Open the socket.
    ASSERT_NO_THROW_LOG(socket.open(&ping_to_endpoint, socket_cb));

    // Verify the socket is open.
    ASSERT_TRUE(socket.isOpen());
    // Since open() is synchronous the callback should not have been invoked.
    ASSERT_FALSE(socket_cb.getCalled());

    // Opening an already open should be harmless.
    ASSERT_NO_THROW_LOG(socket.open(&ping_to_endpoint, socket_cb));
    ASSERT_TRUE(socket.isOpen());

    // Close the socket.
    ASSERT_NO_THROW_LOG(socket.close());
    ASSERT_FALSE(socket.isOpen());

    // Closing a closed socket should be harmless.
    ASSERT_NO_THROW_LOG(socket.close());
    ASSERT_FALSE(socket.isOpen());
}

// Verifies that an ICMP socket can send and receive ICMP messages.
TEST_F(ICMPSocketTest, sendReceive) {
    SKIP_IF(notRoot());

    PingSocket socket(io_service_);

    // For open the endpoint is only used to determine protocol, the address is irrelevant.
    ICMPEndpoint endpoint(IOAddress::IPV4_ZERO_ADDRESS());

    // Open the socket.
    SocketCallback open_cb("open");
    ASSERT_NO_THROW_LOG(socket.open(&endpoint, open_cb));

    // Build a ping.
    struct icmp echo;
    memset(&echo, 0, sizeof(echo));
    echo.icmp_type = ICMPMsg::ECHO_REQUEST;
    echo.icmp_id = htons(0x1122);
    echo.icmp_seq = htons(0x3344);
    echo.icmp_cksum = htons(~(socket.calcChecksum((const uint8_t*)&echo, sizeof(echo))));

    // Send it to the loopback.
    IOAddress ping_to_addr("127.0.0.1");
    SocketCallback send_cb("send");
    ICMPEndpoint ping_to_endpoint(ping_to_addr);
    ASSERT_NO_THROW_LOG(socket.asyncSend(&echo, sizeof(echo), &ping_to_endpoint, send_cb));

    // Run the send handler.
    io_service_->runOne();

    // Callback should have been invoked without an error code.
    ASSERT_TRUE(send_cb.getCalled());
    ASSERT_EQ(0, send_cb.getCode());
    // Verify we sent the whole message.
    ASSERT_EQ(send_cb.getLength(), sizeof(echo));

    // Call asyncReceive until we get our reply.
    resizeInputBuf(1500);
    ICMPEndpoint reply_endpoint;
    SocketCallback receive_cb("receive");

    // We need two receives when pinging loop back, only one with a real address.
    size_t pass = 0;
    do {
        receive_cb.clear();
        memset(getInputBufData(), 0x00, getInputBufSize());
        ASSERT_NO_THROW(socket.asyncReceive(static_cast<void*>(getInputBufData()),
                                           getInputBufSize(), 0, &reply_endpoint, receive_cb));

        // Run the read handler.
        io_service_->runOne();
    } while (++pass < 2 && (!receive_cb.getCalled()));

    // Callback should have been invoked without an error code.
    ASSERT_TRUE(receive_cb.getCalled());
    ASSERT_EQ(0, receive_cb.getCode());

    // Verify the reply came from the target address.
    EXPECT_EQ(ping_to_addr.toText(), reply_endpoint.getAddress().toText());

    // Verify we got at least enough data for an IP header.
    size_t bytes_received = receive_cb.getLength();
    ASSERT_GE(bytes_received, sizeof(struct ip));

    // Build the reply from data
    uint8_t* icbuf = getInputBufData();

    // Find the IP header length...
    struct ip* ip_header = (struct ip*)(icbuf);
    auto hlen = (ip_header->ip_hl << 2);

    // Make sure we received enough data.
    ASSERT_TRUE(bytes_received >= (hlen + sizeof(struct icmp)))
                << "received packet too short to be ICMP";

    // Verify the message type.
    struct icmp* reply = (struct icmp*)(icbuf + hlen);
    auto msg_type = reply->icmp_type;
    ASSERT_EQ(ICMPMsg::ECHO_REPLY, msg_type);

    // Verify the id and sequence values.
    auto id = ntohs(reply->icmp_hun.ih_idseq.icd_id);
    EXPECT_EQ(0x1122, id);

    auto sequence = ntohs(reply->icmp_hun.ih_idseq.icd_seq);
    EXPECT_EQ(0x3344, sequence);

    // Close the socket.
    ASSERT_NO_THROW_LOG(socket.close());
    ASSERT_FALSE(socket.isOpen());
}

}
