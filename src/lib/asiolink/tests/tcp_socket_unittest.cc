// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

/// \brief Test of TCPSocket
///
/// Tests the fuctionality of a TCPSocket by working through an open-send-
/// receive-close sequence and checking that the asynchronous notifications
/// work.

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

#include <asio.hpp>

#include <asiolink/io_service.h>
#include <asiolink/tcp_endpoint.h>
#include <asiolink/tcp_socket.h>

using namespace asio;
using namespace asio::ip;
using namespace asiolink;
using namespace std;

namespace {

const char SERVER_ADDRESS[] = "127.0.0.1";
const unsigned short SERVER_PORT = 5303;

// TODO: Shouldn't we send something that is real message?
const char OUTBOUND_DATA[] = "Data sent from client to server";
const char INBOUND_DATA[] = "Returned data from server to client";
}

///
/// An instance of this object is passed to the asynchronous I/O functions
/// and the operator() method is called when when an asynchronous I/O
/// completes.  The arguments to the completion callback are stored for later
/// retrieval.
class TCPCallback {
public:
    /// \brief Operations the server is doing
    enum Operation {
        ACCEPT = 0,     ///< accept() was issued
        OPEN = 1,       /// Client connected to server
        READ = 2,       ///< Asynchronous read completed
        WRITE = 3,      ///< Asynchronous write completed
        NONE = 4        ///< "Not set" state
    };

    /// \brief Minimim size of buffers
    enum {
        MIN_SIZE = 4096
    };

    struct PrivateData {
        PrivateData() :
            error_code_(), length_(0), name_(""), queued_(NONE), called_(NONE)
        {}

        asio::error_code    error_code_;    ///< Completion error code
        size_t              length_;        ///< Number of bytes transferred
        std::string         name_;          ///< Which of the objects this is
        Operation           queued_;        ///< Queued operation
        Operation           called_;        ///< Which callback called
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
    TCPCallback(std::string which) : ptr_(new PrivateData())
    {
        setName(which);
    }

    /// \brief Destructor
    ///
    /// No code needed, destroying the shared pointer destroys the private data.
    virtual ~TCPCallback()
    {}

    /// \brief Client Callback Function
    ///
    /// Called when an asynchronous connect is completed by the client, this
    /// stores the origin of the operation in the client_called_ data member.
    ///
    /// \param ec I/O completion error code passed to callback function.
    /// \param length Number of bytes transferred
    void operator()(asio::error_code ec = asio::error_code(),
                            size_t length = 0)
    {
        setCode(ec.value());
        setCalled(getQueued());
        setLength(length);
    }

    /// \brief Get I/O completion error code
    int getCode() {
        return (ptr_->error_code_.value());
    }

    /// \brief Set I/O completion code
    ///
    /// \param code New value of completion code
    void setCode(int code) {
        ptr_->error_code_ = asio::error_code(code, asio::error_code().category());
    }

    /// \brief Get number of bytes transferred in I/O
    size_t getLength() {
        return (ptr_->length_);
    }

    /// \brief Set number of bytes transferred in I/O
    ///
    /// \param length New value of length parameter
    void setLength(size_t length) {
        ptr_->length_ = length;
    }

    /// \brief Get flag to say what was queued
    Operation getQueued() {
        return (ptr_->queued_);
    }

    /// \brief Set flag to say what is being queued
    ///
    /// \param called New value of queued parameter
    void setQueued(Operation queued) {
        ptr_->queued_ = queued;
    }

    /// \brief Get flag to say when callback was called
    Operation getCalled() {
        return (ptr_->called_);
    }

    /// \brief Set flag to say when callback was called
    ///
    /// \param called New value of called parameter
    void setCalled(Operation called) {
        ptr_->called_ = called;
    }

    /// \brief Return instance of callback name
    std::string getName() {
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

// TODO: Need to add a test to check the cancel() method

// Tests the operation of a TCPSocket by opening it, sending an asynchronous
// message to a server, receiving an asynchronous message from the server and
// closing.
TEST(TCPSocket, SequenceTest) {

    // Common objects.
    IOService   service;                    // Service object for async control

    // Server
    IOAddress   server_address(SERVER_ADDRESS);
                                            // Address of target server
    TCPCallback server_cb("Server");        // Server callback
    TCPEndpoint server_endpoint(server_address, SERVER_PORT);
                                            // Endpoint describing server
    TCPEndpoint server_remote_endpoint;     // Address where server received message from
    tcp::socket server_socket(service.get_io_service());
                                            // Socket used for server
    char        server_data[TCPCallback::MIN_SIZE];
                                            // Data received by server
    ASSERT_GT(sizeof(server_data), sizeof(OUTBOUND_DATA));
                                            // Make sure it's large enough

    // The client - the TCPSocket being tested
    TCPSocket<TCPCallback>  client(service);// Socket under test
    TCPCallback client_cb("Client");        // Async I/O callback function
    TCPEndpoint client_remote_endpoint;     // Where client receives message from
    char        client_data[TCPCallback::MIN_SIZE];
                                            // Data received by client
    ASSERT_GT(sizeof(client_data), sizeof(OUTBOUND_DATA));
                                            // Make sure it's large enough
    //size_t      client_cumulative = 0;    // Cumulative data received

    // The server - with which the client communicates.  For convenience, we
    // use the same io_service, and use the endpoint object created for
    // the client to send to as the endpoint object in the constructor.

    std::cerr << "Setting up acceptor\n";
    // Set up the server to accept incoming connections.
    server_cb.setQueued(TCPCallback::ACCEPT);
    server_cb.setCalled(TCPCallback::NONE);
    server_cb.setCode(42);  // Some error
    tcp::acceptor acceptor(service.get_io_service(),
                            tcp::endpoint(tcp::v4(), SERVER_PORT));
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    acceptor.async_accept(server_socket, server_cb);

        std::cerr << "Setting up client\n";
    // Open the client socket - the operation should be asynchronous
    client_cb.setQueued(TCPCallback::OPEN);
    client_cb.setCalled(TCPCallback::NONE);
    client_cb.setCode(43);  // Some error
    EXPECT_FALSE(client.isOpenSynchronous());
    client.open(&server_endpoint, client_cb);
    
    // Run the open and the accept callback and check that they ran.
    service.run_one();
    service.run_one();
    
    EXPECT_EQ(TCPCallback::ACCEPT, server_cb.getCalled());
    EXPECT_EQ(0, server_cb.getCode());
    EXPECT_EQ(TCPCallback::OPEN, client_cb.getCalled());
    EXPECT_EQ(0, client_cb.getCode());

    // Write something to the server using the client and read it on ther server.
    server_cb.setCalled(TCPCallback::NONE);
    server_cb.setQueued(TCPCallback::READ);
    server_cb.setCode(142);  // Arbitrary number
    server_cb.setLength(0);
    server_socket.async_receive(buffer(server_data, sizeof(server_data)), server_cb);

    client_cb.setCalled(TCPCallback::NONE);
    client_cb.setQueued(TCPCallback::WRITE);
    client_cb.setCode(143);  // Arbitrary number
    client_cb.setLength(0);
    client.asyncSend(OUTBOUND_DATA, sizeof(OUTBOUND_DATA), &server_endpoint, client_cb);

    // Run the write and read callback and check they ran
    service.run_one();
    service.run_one();

    // Check lengths.  As the client wrote the buffer, currently two bytes
    // will be prepended by the client containing the length.
    EXPECT_EQ(TCPCallback::READ, server_cb.getCalled());
    EXPECT_EQ(0, server_cb.getCode());
    EXPECT_EQ(sizeof(OUTBOUND_DATA) + 2, server_cb.getLength());

    EXPECT_EQ(TCPCallback::WRITE, client_cb.getCalled());
    EXPECT_EQ(0, client_cb.getCode());
    EXPECT_EQ(sizeof(OUTBOUND_DATA) + 2, client_cb.getLength());

    // Check that the first two bytes of the buffer are in fact the remaining
    // length of the buffer (code copied from isc::dns::buffer.h)
    uint16_t count = ((unsigned int)(server_data[0])) << 8;
    count |= ((unsigned int)(server_data[1]));
    EXPECT_EQ(sizeof(OUTBOUND_DATA), count);

    // ... and check data received by server is what we expect
    EXPECT_TRUE(equal(&server_data[2], &server_data[server_cb.getLength() - 1],
                      OUTBOUND_DATA));

    // TODO: Complete this server test
    // TODO: Add in loop for server to read data - read 2 bytes, then as much as needed
    
    /*
    // Now return data from the server to the client.  Issue the read on the
    // client.
    client_cb.setCalled(TCPCallback::NONE);
    client_cb.setQueued(TCPCallback::READ);
    client_cb.setCode(143);  // Arbitrary number
    client_cb.setLength(0);
    client.asyncReceive(OUTBOUND_DATA, sizeof(OUTBOUND_DATA), &server_endpoint, client_cb);

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

    // Expect two callbacks to run
    service.get_io_service().poll();
    //service.run_one();

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

    // Finally, check that the receive received a complete buffer's worth of data.
    EXPECT_TRUE(client.receiveComplete(&data[0], client_cb.getLength(),
        client_cumulative));
    EXPECT_EQ(client_cb.getLength(), client_cumulative);

    // Close client and server.
    EXPECT_NO_THROW(client.close());
    EXPECT_NO_THROW(server.close());
     * */
}
