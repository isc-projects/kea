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

/// @brief A test fixture class for UnixSocket.
class UnixSocketTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ///
    /// It initializes 2 unix sockets.
    UnixSocketTest() :
        sock1_("test_ipc_2to1", "test_ipc_1to2"),
        sock2_("test_ipc_1to2", "test_ipc_2to1")
    {
    }
protected:
    /// UnixSocket objects for testing.
    UnixSocket sock1_, sock2_;
};

// Test UnixSocket constructor
TEST_F(UnixSocketTest, constructor) {
	EXPECT_EQ(-1, sock1_.getSocket());
}


// Test openSocket function
TEST_F(UnixSocketTest, openSocket) {
	int fd;
	EXPECT_NO_THROW(
    	fd = sock1_.open();
    );
	
	EXPECT_EQ(fd, sock1_.getSocket());
}

// Test bidirectional data sending and receiving.
TEST_F(UnixSocketTest, bidirectionalTransmission) {
	const int LEN1 = 100;
	const int LEN2 = 200;
	uint8_t data1[LEN2];
	uint8_t data2[LEN2];
	uint8_t data3[LEN2];
	uint8_t data4[LEN2];
	for (int i = 0; i < LEN2; ++i) {
	    data1[i] = i;
	    data2[i] = -i;
	}
	EXPECT_NO_THROW(
    	sock1_.open();
    );
	EXPECT_NO_THROW(
    	sock2_.open();
    );
      
	OutputBuffer sendbuf1(LEN1), sendbuf2(LEN2);
	sendbuf1.writeData((void*)data1, LEN1);
	sendbuf2.writeData((void*)data2, LEN2);
	EXPECT_NO_THROW(
	    sock1_.send(sendbuf1);
	);
	EXPECT_NO_THROW(
    	sock2_.send(sendbuf2);
    );
	
	InputBuffer recvbuf1(0, 0), recvbuf2(0, 0);
	EXPECT_NO_THROW(
        recvbuf1 = sock1_.recv();
    );
    EXPECT_NO_THROW(
        recvbuf2 = sock2_.recv();
    );
    
    size_t len1 = recvbuf1.getLength();
    size_t len2 = recvbuf2.getLength();
    recvbuf1.readData((void*)data3, len1);
    recvbuf2.readData((void*)data4, len2);
	
	//check out length.
	ASSERT_EQ(LEN2, len1);
	ASSERT_EQ(LEN1, len2);
	
	for (int i = 0; i < len1; i++) {
		EXPECT_EQ(data2[i], data3[i]);
	}
	for (int i = 0; i < len2; i++) {
		EXPECT_EQ(data1[i], data4[i]);
	}
}

// Test exceptions
TEST_F(UnixSocketTest, exceptions) {
    EXPECT_THROW(
        sock1_.recv(),
        UnixSocketRecvError
    );
    EXPECT_THROW(
        sock1_.send(OutputBuffer(10)),
        UnixSocketSendError
    );
    EXPECT_NO_THROW(
        sock1_.open();
        sock2_.open();
    );
    EXPECT_NO_THROW(
        sock1_.send(OutputBuffer(10))
    );
}

}

