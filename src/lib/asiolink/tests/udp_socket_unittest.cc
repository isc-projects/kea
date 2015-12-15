// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// \brief Test of UDPSocket
///
/// Tests the functionality of a UDPSocket by working through an open-send-
/// receive-close sequence and checking that the asynchronous notifications
/// work.

#include <config.h>

#include <string>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <algorithm>
#include <cstdlib>
#include <cstddef>
#include <vector>

#include <gtest/gtest.h>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <util/buffer.h>
#include <util/io_utilities.h>

#include <boost/asio.hpp>

#include <asiolink/io_service.h>
#include <asiolink/udp_endpoint.h>
#include <asiolink/udp_socket.h>

using namespace boost::asio;
using namespace isc::util;
using namespace isc::asiolink;
using namespace std;

namespace {

const char SERVER_ADDRESS[] = "127.0.0.1";
const unsigned short SERVER_PORT = 5301;

// TODO: Shouldn't we send something that is real message?
const char OUTBOUND_DATA[] = "Data sent from client to server";
const char INBOUND_DATA[] = "Returned data from server to client";
}

///
/// An instance of this object is passed to the asynchronous I/O functions
/// and the operator() method is called when when an asynchronous I/O
/// completes.  The arguments to the completion callback are stored for later
/// retrieval.
class UDPCallback {
public:

    struct PrivateData {
        PrivateData() :
            error_code_(), length_(0), called_(false), name_("")
        {}

        boost::system::error_code  error_code_;    ///< Completion error code
        size_t                     length_;        ///< Number of bytes transferred
        bool                       called_;        ///< Set true when callback called
        std::string                name_;          ///< Which of the objects this is
    };

    /// \brief Constructor
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
    /// \param which Which of the two callback objects this is
    UDPCallback(std::string which) : ptr_(new PrivateData())
    {
        setName(which);
    }

    /// \brief Destructor
    ///
    /// No code needed, destroying the shared pointer destroys the private data.
    virtual ~UDPCallback()
    {}

    /// \brief Callback Function
    ///
    /// Called when an asynchronous I/O completes, this stores the
    /// completion error code and the number of bytes transferred.
    ///
    /// \param ec I/O completion error code passed to callback function.
    /// \param length Number of bytes transferred
    virtual void operator()(boost::system::error_code ec, size_t length = 0) {
        ptr_->error_code_ = ec;
        setLength(length);
        setCalled(true);
    }

    /// \brief Get I/O completion error code
    int getCode() {
        return (ptr_->error_code_.value());
    }

    /// \brief Set I/O completion code
    ///
    /// \param code New value of completion code
    void setCode(int code) {
        ptr_->error_code_ = boost::system::error_code(code, boost::system::error_code().category());
    }

    /// \brief Get number of bytes transferred in I/O
    size_t getLength() const {
        return (ptr_->length_);
    }

    /// \brief Set number of bytes transferred in I/O
    ///
    /// \param length New value of length parameter
    void setLength(size_t length) {
        ptr_->length_ = length;
    }

    /// \brief Get flag to say when callback was called
    bool getCalled() const {
        return (ptr_->called_);
    }

    /// \brief Set flag to say when callback was called
    ///
    /// \param called New value of called parameter
    void setCalled(bool called) {
        ptr_->called_ = called;
    }

    /// \brief Return instance of callback name
    std::string getName() const {
        return (ptr_->name_);
    }

    /// \brief Set callback name
    ///
    /// \param name New value of the callback name
    void setName(const std::string& name) {
        ptr_->name_ = name;
    }

private:
    boost::shared_ptr<PrivateData>  ptr_;   ///< Pointer to private data
};

// Receive complete method should return true regardless of what is in the first
// two bytes of a buffer.

TEST(UDPSocket, processReceivedData) {
    IOService               service;        // Used to instantiate socket
    UDPSocket<UDPCallback>  test(service);  // Socket under test
    uint8_t                 inbuff[32];     // Buffer to check
    OutputBufferPtr         outbuff(new OutputBuffer(16));
                                            // Where data is put
                                            // cppcheck-suppress variableScope
    size_t                  expected;       // Expected amount of data
                                            // cppcheck-suppress variableScope    
    size_t                  offset;         // Where to put next data
                                            // cppcheck-suppress variableScope
    size_t                  cumulative;     // Cumulative data received

    // Set some dummy values in the buffer to check
    for (uint8_t i = 0; i < sizeof(inbuff); ++i) {
        inbuff[i] = i;
    }

    // Expect that the value is true whatever number is written in the first
    // two bytes of the buffer.
    uint16_t count = 0;
    for (uint32_t i = 0; i < (2 << 16); ++i, ++count) {
        writeUint16(count, inbuff, sizeof(inbuff));

        // Set some random values
        cumulative = 5;
        offset = 10;
        expected = 15;
        outbuff->clear();

        bool completed = test.processReceivedData(inbuff, sizeof(inbuff),
                                                  cumulative, offset, expected,
                                                  outbuff);
        EXPECT_TRUE(completed);
        EXPECT_EQ(sizeof(inbuff), cumulative);
        EXPECT_EQ(0, offset);
        EXPECT_EQ(sizeof(inbuff), expected);

        const uint8_t* dataptr = static_cast<const uint8_t*>(outbuff->getData());
        EXPECT_TRUE(equal(inbuff, inbuff + sizeof(inbuff) - 1, dataptr));
    }
}

// TODO: Need to add a test to check the cancel() method

// Tests the operation of a UDPSocket by opening it, sending an asynchronous
// message to a server, receiving an asynchronous message from the server and
// closing.
TEST(UDPSocket, SequenceTest) {

    // Common objects.
    IOService   service;                    // Service object for async control

    // Server
    IOAddress   server_address(SERVER_ADDRESS); // Address of target server
    UDPCallback server_cb("Server");        // Server callback
    UDPEndpoint server_endpoint(            // Endpoint describing server
        server_address, SERVER_PORT);
    UDPEndpoint server_remote_endpoint;     // Address where server received message from

    // The client - the UDPSocket being tested
    UDPSocket<UDPCallback>  client(service);// Socket under test
    UDPCallback client_cb("Client");        // Async I/O callback function
    UDPEndpoint client_remote_endpoint;     // Where client receives message from
    size_t      client_cumulative = 0;      // Cumulative data received
    size_t      client_offset = 0;          // Offset into buffer where data is put
    size_t      client_expected = 0;        // Expected amount of data
    OutputBufferPtr client_buffer(new OutputBuffer(16));
                                            // Where data is put

    // The server - with which the client communicates.  For convenience, we
    // use the same io_service, and use the endpoint object created for
    // the client to send to as the endpoint object in the constructor.
    boost::asio::ip::udp::socket server(service.get_io_service(),
        server_endpoint.getASIOEndpoint());
    server.set_option(socket_base::reuse_address(true));

    // Assertion to ensure that the server buffer is large enough
    char data[UDPSocket<UDPCallback>::MIN_SIZE];
    ASSERT_GT(sizeof(data), sizeof(OUTBOUND_DATA));

    // Open the client socket - the operation should be synchronous
    EXPECT_TRUE(client.isOpenSynchronous());
    client.open(&server_endpoint, client_cb);

    // Issue read on the server.  Completion callback should not have run.
    server_cb.setCalled(false);
    server_cb.setCode(42); // Answer to Life, the Universe and Everything!
    server.async_receive_from(buffer(data, sizeof(data)),
        server_remote_endpoint.getASIOEndpoint(), server_cb);
    EXPECT_FALSE(server_cb.getCalled());

    // Write something to the server using the client - the callback should not
    // be called until we call the io_service.run() method.
    client_cb.setCalled(false);
    client_cb.setCode(7);  // Arbitrary number
    client.asyncSend(OUTBOUND_DATA, sizeof(OUTBOUND_DATA), &server_endpoint, client_cb);
    EXPECT_FALSE(client_cb.getCalled());

    // Execute the two callbacks.
    service.run_one();
    service.run_one();

    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_EQ(0, client_cb.getCode());
    EXPECT_EQ(sizeof(OUTBOUND_DATA), client_cb.getLength());

    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_EQ(0, server_cb.getCode());
    EXPECT_EQ(sizeof(OUTBOUND_DATA), server_cb.getLength());

    EXPECT_TRUE(equal(&data[0], &data[server_cb.getLength() - 1], OUTBOUND_DATA));

    // Now return data from the server to the client.  Issue the read on the
    // client.
    client_cb.setLength(12345);             // Arbitrary number
    client_cb.setCalled(false);
    client_cb.setCode(32);                  // Arbitrary number
    client.asyncReceive(data, sizeof(data), client_cumulative,
        &client_remote_endpoint, client_cb);

    // Issue the write on the server side to the source of the data it received.
    server_cb.setLength(22345);             // Arbitrary number
    server_cb.setCalled(false);
    server_cb.setCode(232);                 // Arbitrary number
    server.async_send_to(buffer(INBOUND_DATA, sizeof(INBOUND_DATA)),
        server_remote_endpoint.getASIOEndpoint(), server_cb);

    // Expect two callbacks to run.
    service.run_one();
    service.run_one();

    EXPECT_TRUE(client_cb.getCalled());
    EXPECT_EQ(0, client_cb.getCode());
    EXPECT_EQ(sizeof(INBOUND_DATA), client_cb.getLength());

    EXPECT_TRUE(server_cb.getCalled());
    EXPECT_EQ(0, server_cb.getCode());
    EXPECT_EQ(sizeof(INBOUND_DATA), server_cb.getLength());

    EXPECT_TRUE(equal(&data[0], &data[server_cb.getLength() - 1], INBOUND_DATA));

    // Check that the address/port received by the client corresponds to the
    // address and port the server is listening on.
    EXPECT_TRUE(server_address == client_remote_endpoint.getAddress());
    EXPECT_EQ(SERVER_PORT, client_remote_endpoint.getPort());

    // Check that the receive received a complete buffer's worth of data.
    EXPECT_TRUE(client.processReceivedData(&data[0], client_cb.getLength(),
                                           client_cumulative, client_offset,
                                           client_expected, client_buffer));

    EXPECT_EQ(client_cb.getLength(), client_cumulative);
    EXPECT_EQ(0, client_offset);
    EXPECT_EQ(client_cb.getLength(), client_expected);
    EXPECT_EQ(client_cb.getLength(), client_buffer->getLength());

    // ...and check that the data was copied to the output client buffer.
    const char* client_char_data = static_cast<const char*>(client_buffer->getData());
    EXPECT_TRUE(equal(&data[0], &data[client_cb.getLength() - 1], client_char_data));

    // Close client and server.
    EXPECT_NO_THROW(client.close());
    EXPECT_NO_THROW(server.close());
}
