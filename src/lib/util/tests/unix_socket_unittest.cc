// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
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


#include <util/unix_socket.h>

#include <gtest/gtest.h>

using namespace isc::util;

namespace {

const char* TEST_FILE1 = "test_unix_socket_1";
const char* TEST_FILE2 = "test_unix_socket_2";

/// @brief A test fixture class for @c UnixSocket.
class UnixSocketTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ///
    /// It initializes 2 unix sockets.
    UnixSocketTest() :
        sock1_(absolutePath(TEST_FILE1), absolutePath(TEST_FILE2)),
        sock2_(absolutePath(TEST_FILE2), absolutePath(TEST_FILE1))
    {
    }

    /// @brief Prepends the absolute path to the file specified
    /// as an argument.
    ///
    /// @param filename Name of the file.
    /// @return Absolute path to the test file.
    std::string absolutePath(const std::string& filename);

    /// UnixSocket objects for testing.
    UnixSocket sock1_, sock2_;
};

std::string
UnixSocketTest::absolutePath(const std::string& filename) {
    std::ostringstream s;
    s << TEST_DATA_BUILDDIR << "/" << filename;
    return (s.str());
}

// Test UnixSocket constructor
TEST_F(UnixSocketTest, constructor) {
    EXPECT_EQ(-1, sock1_.get());
    EXPECT_EQ(-1, sock2_.get());

    // The local and remote sockets must not be bound to the same file.
    EXPECT_THROW(UnixSocket(absolutePath(TEST_FILE1), absolutePath(TEST_FILE1)),
                 UnixSocketInvalidName);
    // The socket path must not be empty.
    EXPECT_THROW(UnixSocket("", absolutePath(TEST_FILE1)),
                 UnixSocketInvalidName);
    EXPECT_THROW(UnixSocket(absolutePath(TEST_FILE1), ""),
                 UnixSocketInvalidName);

}

// Test open() function which opens a unix socket.
TEST_F(UnixSocketTest, open) {
    ASSERT_NO_THROW(sock1_.open());
    EXPECT_GE(sock1_.get(), 0);
    // Second attempt open socket should fail.
    ASSERT_THROW(sock1_.open(), UnixSocketOpenError);
    // Close the opened socket and check then we can re-open.
    sock1_.closeFd();
    EXPECT_NO_THROW(sock1_.open());
}

// Test bidirectional data sending and receiving.
TEST_F(UnixSocketTest, bidirectionalTransmission) {
    const int LEN1 = 100;
    const int LEN2 = 200;

    // Prepare data to be sent over the unix sockets from both directions.
    uint8_t data1[LEN2];
    uint8_t data2[LEN2];
    for (int i = 0; i < LEN2; ++i) {
        data1[i] = i;
        // Make sure that the data is different for the other side of the
        // communication channel so as the socket doesn't receive its own
        // data.
        data2[i] = i % 2;
    }
    // Make sure that the sockets can be opened on both ends.
    ASSERT_NO_THROW(sock1_.open());
    ASSERT_NO_THROW(sock2_.open());

    // Prepare send buffers. Differentiate their lengths so we can verify
    // that the lengths of the received data are correct.
    OutputBuffer sendbuf1(LEN1);
    OutputBuffer sendbuf2(LEN2);
    sendbuf1.writeData((void*)data1, LEN1);
    sendbuf2.writeData((void*)data2, LEN2);
    // Send data over the sockets in both directions.
    ASSERT_NO_THROW(sock1_.send(sendbuf1));
    ASSERT_NO_THROW(sock2_.send(sendbuf2));

    // Receive the data from both directions.
    int recvlen1, recvlen2;
    ASSERT_NO_THROW(recvlen1 = sock1_.receive());
    ASSERT_NO_THROW(recvlen2 = sock2_.receive());

    // Sanity check the lengths.
    ASSERT_EQ(recvlen1, LEN2);
    ASSERT_EQ(recvlen2, LEN1);

    // Make sure we can create InputBuffers from the received data.
    InputBuffer recvbuf1(sock1_.getReceiveBuffer(), recvlen1);
    InputBuffer recvbuf2(sock2_.getReceiveBuffer(), recvlen2);

    // Verify that the received data is correct.
    for (int i = 0; i < recvlen1; ++i) {
        EXPECT_EQ(recvbuf1.readUint8(), data2[i]);
    }
    for (int i = 0; i < recvlen2; ++i) {
        EXPECT_EQ(recvbuf2.readUint8(), data1[i]);
    }
}

// Test that send and receive throw for close sockets.
TEST_F(UnixSocketTest, exceptions) {
    EXPECT_THROW(sock1_.receive(), UnixSocketRecvError);
    EXPECT_THROW(sock1_.send(OutputBuffer(10)), UnixSocketSendError);
    ASSERT_NO_THROW(sock1_.open());
    ASSERT_NO_THROW(sock2_.open());
    EXPECT_NO_THROW(sock1_.send(OutputBuffer(10)));
}

}
