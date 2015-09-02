// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
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
/// Tests the functionality of a TCPSocket by working through an open-send-
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
#include <asiolink/tcp_endpoint.h>
#include <asiolink/tcp_socket.h>

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace isc::util;
using namespace isc::asiolink;
using namespace std;

namespace {

const char SERVER_ADDRESS[] = "127.0.0.1";
const unsigned short SERVER_PORT = 5303;

// TODO: Shouldn't we send something that is real message?
const char OUTBOUND_DATA[] = "Data sent from client to server";
const char INBOUND_DATA[] = "Returned data from server to client";
}

/// An instance of this object is passed to the asynchronous I/O functions
/// and the operator() method is called when when an asynchronous I/O completes.
/// The arguments to the completion callback are stored for later retrieval.
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
        MIN_SIZE = (64 * 1024 + 2)          ///< 64kB + two bytes for a count
    };

    struct PrivateData {
        PrivateData() :
            error_code_(), length_(0), cumulative_(0), expected_(0), offset_(0),
            name_(""), queued_(NONE), called_(NONE), data_(MIN_SIZE, 0)
        {}

        boost::system::error_code  error_code_;    ///< Completion error code
        size_t                     length_;        ///< Bytes transferred in this I/O
        size_t                     cumulative_;    ///< Cumulative bytes transferred
        size_t                     expected_;      ///< Expected amount of data
        size_t                     offset_;        ///< Where to put data in buffer
        std::string                name_;          ///< Which of the objects this is
        Operation                  queued_;        ///< Queued operation
        Operation                  called_;        ///< Which callback called
        std::vector<uint8_t>       data_;          ///< Receive buffer
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
        ptr_->name_ = which;
    }

    /// \brief Destructor
    ///
    /// No code needed, destroying the shared pointer destroys the private data.
    virtual ~TCPCallback()
    {}

    /// \brief Client Callback Function
    ///
    /// Called when an asynchronous operation is completed by the client, this
    /// stores the origin of the operation in the client_called_ data member.
    ///
    /// \param ec I/O completion error code passed to callback function.
    /// \param length Number of bytes transferred
    void operator()(boost::system::error_code ec = boost::system::error_code(),
                            size_t length = 0)
    {
        setCode(ec.value());
        ptr_->called_ = ptr_->queued_;
        ptr_->length_ = length;
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
    size_t& length() {
        return (ptr_->length_);
    }

    /// \brief Get cumulative number of bytes transferred in I/O
    size_t& cumulative() {
        return (ptr_->cumulative_);
    }

    /// \brief Get expected amount of data
    size_t& expected() {
        return (ptr_->expected_);
    }

    /// \brief Get offset intodData
    size_t& offset() {
        return (ptr_->offset_);
    }

    /// \brief Get data member
    uint8_t* data() {
        return (&ptr_->data_[0]);
    }

    /// \brief Get flag to say what was queued
    Operation& queued() {
        return (ptr_->queued_);
    }

    /// \brief Get flag to say when callback was called
    Operation& called() {
        return (ptr_->called_);
    }

    /// \brief Return instance of callback name
    std::string& name() {
        return (ptr_->name_);
    }

private:
    boost::shared_ptr<PrivateData>  ptr_;   ///< Pointer to private data
};


// Read Server Data
//
// Called in the part of the test that has the client send a message to the
// server, this loops until all the data has been read (synchronously) by the
// server.
//
// "All the data read" means that the server has received a message that is
// preceded by a two-byte count field and that the total amount of data received
// from the remote end is equal to the value in the count field plus two bytes
// for the count field itself.
//
// \param socket Socket on which the server is reading data
// \param server_cb Structure in which server data is held.
void
serverRead(tcp::socket& socket, TCPCallback& server_cb) {

    // As we may need to read multiple times, keep a count of the cumulative
    // amount of data read and do successive reads into the appropriate part
    // of the buffer.
    //
    // Note that there are no checks for buffer overflow - this is a test
    // program and we have sized the buffer to be large enough for the test.
    server_cb.cumulative() = 0;

    bool complete = false;
    while (!complete) {

        // Read block of data and update cumulative amount of data received.
        server_cb.length() = socket.receive(
            boost::asio::buffer(server_cb.data() + server_cb.cumulative(),
                TCPCallback::MIN_SIZE - server_cb.cumulative()));
        server_cb.cumulative() += server_cb.length();

        // If we have read at least two bytes, we can work out how much we
        // should be reading.
        if (server_cb.cumulative() >= 2) {
            server_cb.expected() = readUint16(server_cb.data(), server_cb.length());
            if ((server_cb.expected() + 2) == server_cb.cumulative()) {

                // Amount of data read from socket equals the size of the
                // message (as indicated in the first two bytes of the message)
                // plus the size of the count field.  Therefore we have received
                // all the data.
                complete = true;
            }
        }
    }
}

// Receive complete method should return true only if the count in the first
// two bytes is equal to the size of the rest if the buffer.

TEST(TCPSocket, processReceivedData) {
    const uint16_t PACKET_SIZE = 16382;     // Amount of "real" data in the buffer

    IOService               service;        // Used to instantiate socket
    TCPSocket<TCPCallback>  test(service);  // Socket under test
    uint8_t                 inbuff[PACKET_SIZE + 2];   // Buffer to check
    OutputBufferPtr         outbuff(new OutputBuffer(16));
                                            // Where data is put
    size_t                  expected;       // Expected amount of data
    size_t                  offset;         // Where to put next data
    size_t                  cumulative;     // Cumulative data received

    // Set some dummy values in the buffer to check
    for (size_t i = 0; i < sizeof(inbuff); ++i) {
        inbuff[i] = i % 256;
    }

    // Check that the method will handle various receive sizes.
    writeUint16(PACKET_SIZE, inbuff, sizeof(inbuff));

    cumulative = 0;
    offset = 0;
    expected = 0;
    outbuff->clear();
    bool complete = test.processReceivedData(inbuff, 1, cumulative, offset,
                                             expected, outbuff);
    EXPECT_FALSE(complete);
    EXPECT_EQ(1, cumulative);
    EXPECT_EQ(1, offset);
    EXPECT_EQ(0, expected);
    EXPECT_EQ(0, outbuff->getLength());

    // Now pretend that we've received one more byte.
    complete = test.processReceivedData(inbuff, 1, cumulative, offset, expected,
                                        outbuff);
    EXPECT_FALSE(complete);
    EXPECT_EQ(2, cumulative);
    EXPECT_EQ(0, offset);
    EXPECT_EQ(PACKET_SIZE, expected);
    EXPECT_EQ(0, outbuff->getLength());

    // Add another two bytes.  However, this time note that we have to offset
    // in the input buffer because it is expected that the next chunk of data
    // from the connection will be read into the start of the buffer.
    complete = test.processReceivedData(inbuff + cumulative, 2, cumulative,
                                        offset, expected, outbuff);
    EXPECT_FALSE(complete);
    EXPECT_EQ(4, cumulative);
    EXPECT_EQ(0, offset);
    EXPECT_EQ(PACKET_SIZE, expected);
    EXPECT_EQ(2, outbuff->getLength());

    const uint8_t* dataptr = static_cast<const uint8_t*>(outbuff->getData());
    EXPECT_TRUE(equal(inbuff + 2, inbuff + cumulative, dataptr));

    // And add the remaining data.  Remember that "inbuff" is "PACKET_SIZE + 2"
    // long.
    complete = test.processReceivedData(inbuff + cumulative,
                                        PACKET_SIZE + 2 - cumulative,
                                        cumulative, offset, expected, outbuff);
    EXPECT_TRUE(complete);
    EXPECT_EQ(PACKET_SIZE + 2, cumulative);
    EXPECT_EQ(0, offset);
    EXPECT_EQ(PACKET_SIZE, expected);
    EXPECT_EQ(PACKET_SIZE, outbuff->getLength());
    dataptr = static_cast<const uint8_t*>(outbuff->getData());
    EXPECT_TRUE(equal(inbuff + 2, inbuff + cumulative, dataptr));
}

// TODO: Need to add a test to check the cancel() method

// Tests the operation of a TCPSocket by opening it, sending an asynchronous
// message to a server, receiving an asynchronous message from the server and
// closing.
TEST(TCPSocket, sequenceTest) {

    // Common objects.
    IOService   service;                    // Service object for async control

    // The client - the TCPSocket being tested
    TCPSocket<TCPCallback>  client(service);// Socket under test
    TCPCallback client_cb("Client");        // Async I/O callback function
    TCPEndpoint client_remote_endpoint;     // Where client receives message from
    OutputBufferPtr client_buffer(new OutputBuffer(128));
                                            // Received data is put here

    // The server - with which the client communicates.
    IOAddress   server_address(SERVER_ADDRESS);
                                            // Address of target server
    TCPCallback server_cb("Server");        // Server callback
    TCPEndpoint server_endpoint(server_address, SERVER_PORT);
                                            // Endpoint describing server
    TCPEndpoint server_remote_endpoint;     // Address where server received message from
    tcp::socket server_socket(service.get_io_service());
                                            // Socket used for server

    // Step 1.  Create the connection between the client and the server.  Set
    // up the server to accept incoming connections and have the client open
    // a channel to it.

    // Set up server - open socket and queue an accept.
    server_cb.queued() = TCPCallback::ACCEPT;
    server_cb.called() = TCPCallback::NONE;
    server_cb.setCode(42);  // Some error
    tcp::acceptor acceptor(service.get_io_service(),
                            tcp::endpoint(tcp::v4(), SERVER_PORT));
    acceptor.set_option(tcp::acceptor::reuse_address(true));
    acceptor.async_accept(server_socket, server_cb);

    // Set up client - connect to the server.
    client_cb.queued() = TCPCallback::OPEN;
    client_cb.called() = TCPCallback::NONE;
    client_cb.setCode(43);  // Some error
    EXPECT_FALSE(client.isOpenSynchronous());
    client.open(&server_endpoint, client_cb);

    // Run the open and the accept callback and check that they ran.
    service.run_one();
    service.run_one();

    EXPECT_EQ(TCPCallback::ACCEPT, server_cb.called());
    EXPECT_EQ(0, server_cb.getCode());

    EXPECT_EQ(TCPCallback::OPEN, client_cb.called());
    EXPECT_EQ(0, client_cb.getCode());

    // Step 2.  Get the client to write to the server asynchronously.  The
    // server will loop reading the data synchronously.

    // Write asynchronously to the server.
    client_cb.called() = TCPCallback::NONE;
    client_cb.queued() = TCPCallback::WRITE;
    client_cb.setCode(143);  // Arbitrary number
    client_cb.length() = 0;
    client.asyncSend(OUTBOUND_DATA, sizeof(OUTBOUND_DATA), &server_endpoint, client_cb);

    // Wait for the client callback to complete. (Must do this first on
    // Solaris: if we do the synchronous read first, the test hangs.)
    service.run_one();

    // Synchronously read the data from the server.;
    serverRead(server_socket, server_cb);

    // Check the client state
    EXPECT_EQ(TCPCallback::WRITE, client_cb.called());
    EXPECT_EQ(0, client_cb.getCode());
    EXPECT_EQ(sizeof(OUTBOUND_DATA) + 2, client_cb.length());

    // ... and check what the server received.
    EXPECT_EQ(sizeof(OUTBOUND_DATA) + 2, server_cb.cumulative());
    EXPECT_TRUE(equal(OUTBOUND_DATA,
                (OUTBOUND_DATA + (sizeof(OUTBOUND_DATA) - 1)),
                (server_cb.data() + 2)));

    // Step 3.  Get the server to write all the data asynchronously and have the
    // client loop (asynchronously) reading the data.  Note that we copy the
    // data into the server's internal buffer in order to precede it with a two-
    // byte count field.

    // Have the server write asynchronously to the client.
    server_cb.called() = TCPCallback::NONE;
    server_cb.queued() = TCPCallback::WRITE;
    server_cb.length() = 0;
    server_cb.cumulative() = 0;

    writeUint16(sizeof(INBOUND_DATA), server_cb.data(), TCPCallback::MIN_SIZE);
    copy(INBOUND_DATA, (INBOUND_DATA + sizeof(INBOUND_DATA) - 1),
        (server_cb.data() + 2));
    server_socket.async_send(boost::asio::buffer(server_cb.data(),
                                          (sizeof(INBOUND_DATA) + 2)),
                             server_cb);

    // Have the client read asynchronously.
    client_cb.called() = TCPCallback::NONE;
    client_cb.queued() = TCPCallback::READ;
    client_cb.length() = 0;
    client_cb.cumulative() = 0;
    client_cb.expected() = 0;
    client_cb.offset() = 0;

    client.asyncReceive(client_cb.data(), TCPCallback::MIN_SIZE,
                        client_cb.offset(), &client_remote_endpoint,
                        client_cb);

    // Run the callbacks. Several options are possible depending on how ASIO
    // is implemented and whether the message gets fragmented:
    //
    // 1) The send handler may complete immediately, regardess of whether the
    // data has been read by the client.  (This is the most likely.)
    // 2) The send handler may only run after all the data has been read by
    // the client. (This could happen if the client's TCP buffers were too
    // small so the data was not transferred to the "remote" system until the
    // remote buffer has been emptied one or more times.)
    // 3) The client handler may be run a number of times to handle the message
    // fragments and the server handler may run between calls of the client
    // handler.
    //
    // So loop, running one handler at a time until we are certain that all the
    // handlers have run.

    bool server_complete = false;
    bool client_complete = false;
    while (!server_complete || !client_complete) {
        service.run_one();

        // Has the server run?
        if (!server_complete) {
            if (server_cb.called() == server_cb.queued()) {

                // Yes.  Check that the send completed successfully and that
                // all the data that was expected to have been sent was in fact
                // sent.
                EXPECT_EQ(0, server_cb.getCode());
                EXPECT_EQ((sizeof(INBOUND_DATA) + 2), server_cb.length());
                server_complete = true;
                continue;
            }
        }

        if (!client_complete) {

            // Client callback must have run.  Check that it ran OK.
            EXPECT_EQ(TCPCallback::READ, client_cb.called());
            EXPECT_EQ(0, client_cb.getCode());

            // Check if we need to queue another read, copying the data into
            // the output buffer as we do so.
            client_complete = client.processReceivedData(client_cb.data(),
                                                         client_cb.length(),
                                                         client_cb.cumulative(),
                                                         client_cb.offset(),
                                                         client_cb.expected(),
                                                         client_buffer);

            // If the data is not complete, queue another read.
            if (! client_complete) {
                client_cb.called() = TCPCallback::NONE;
                client_cb.queued() = TCPCallback::READ;
                client_cb.length() = 0;
                client.asyncReceive(client_cb.data(), TCPCallback::MIN_SIZE ,
                                    client_cb.offset(), &client_remote_endpoint,
                                    client_cb);
            }
        }
    }

    // Both the send and the receive have completed.  Check that the received
    // is what was sent.

    // Check the client state
    EXPECT_EQ(TCPCallback::READ, client_cb.called());
    EXPECT_EQ(0, client_cb.getCode());
    EXPECT_EQ(sizeof(INBOUND_DATA) + 2, client_cb.cumulative());
    EXPECT_EQ(sizeof(INBOUND_DATA), client_buffer->getLength());

    // ... and check what the server sent.
    EXPECT_EQ(TCPCallback::WRITE, server_cb.called());
    EXPECT_EQ(0, server_cb.getCode());
    EXPECT_EQ(sizeof(INBOUND_DATA) + 2, server_cb.length());

    // ... and that what was sent is what was received.
    const uint8_t* received = static_cast<const uint8_t*>(client_buffer->getData());
    EXPECT_TRUE(equal(INBOUND_DATA, (INBOUND_DATA + (sizeof(INBOUND_DATA) - 1)),
                      received));

    // Close client and server.
    EXPECT_NO_THROW(client.close());
    EXPECT_NO_THROW(server_socket.close());
}
