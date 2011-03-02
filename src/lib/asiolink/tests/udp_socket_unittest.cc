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


/// \brief Test of UDPSocket
///
/// Tests the fuctionality of a UDPSocket by working through an open-send-
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
#include <asiolink/udp_endpoint.h>
#include <asiolink/udp_socket.h>

using namespace asio;
using namespace asiolink;
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

        asio::error_code    error_code_;    ///< Completion error code
        size_t              length_;        ///< Number of bytes transferred
        bool                called_;        ///< Set true when callback called
        std::string         name_;          ///< Which of the objects this is
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
    virtual void operator()(asio::error_code ec, size_t length = 0) {
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
        ptr_->error_code_ = asio::error_code(code, asio::error_code().category());
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

    // The server - with which the client communicates.  For convenience, we
    // use the same io_service, and use the endpoint object created for
    // the client to send to as the endpoint object in the constructor.
    asio::ip::udp::socket server(service.get_io_service(),
        server_endpoint.getASIOEndpoint());
    server.set_option(socket_base::reuse_address(true));

    // Assertion to ensure that the server buffer is large enough
    char data[UDPSocket<UDPCallback>::MAX_SIZE];
    ASSERT_GT(sizeof(data), sizeof(OUTBOUND_DATA));

    // Open the client socket - the operation should be synchronous
    EXPECT_FALSE(client.open(&server_endpoint, client_cb));

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

    // Expect the two callbacks to run
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

    // Finally, check that the receive received a complete buffer's worth of data.
    EXPECT_TRUE(client.receiveComplete(&data[0], client_cb.getLength(),
        client_cumulative));
    EXPECT_EQ(client_cb.getLength(), client_cumulative);

    // Close client and server.
    EXPECT_NO_THROW(client.close());
    EXPECT_NO_THROW(server.close());
}
