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


#include <util/ipc.h>

#include <gtest/gtest.h>

using namespace isc::util;


namespace {

/// @brief A test fixture class for BaseIPC.
class IPCTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ///
    /// It initializes 2 BaseIPC objects.
    IPCTest() :
        ipc1("test_ipc_2to1", "test_ipc_1to2"),
        ipc2("test_ipc_1to2", "test_ipc_2to1")
    {
    }
protected:
    /// BaseIPC objects for testing.
    BaseIPC ipc1, ipc2;
};

// Test BaseIPC constructor
TEST_F(IPCTest, constructor) {
	EXPECT_EQ(-1, ipc1.getSocket());
}


// Test openSocket function
TEST_F(IPCTest, openSocket) {
	int fd;
	EXPECT_NO_THROW(
    	fd = ipc1.open();
    );
	
	EXPECT_EQ(fd, ipc1.getSocket());
}

// Test BaseIPC bidirectional data sending and receiving
TEST_F(IPCTest, bidirectionalTransmission) {
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
    	ipc1.open();
    );
	EXPECT_NO_THROW(
    	ipc2.open();
    );
      
	OutputBuffer sendbuf1(LEN1), sendbuf2(LEN2);
	sendbuf1.writeData((void*)data1, LEN1);
	sendbuf2.writeData((void*)data2, LEN2);
	EXPECT_NO_THROW(
	    ipc1.send(sendbuf1);
	);
	EXPECT_NO_THROW(
    	ipc2.send(sendbuf2);
    );
	
	InputBuffer recvbuf1(0, 0), recvbuf2(0, 0);
	EXPECT_NO_THROW(
        recvbuf1 = ipc1.recv();
    );
    EXPECT_NO_THROW(
        recvbuf2 = ipc2.recv();
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
TEST_F(IPCTest, exceptions) {
    EXPECT_THROW(
        ipc1.recv(),
        IPCRecvError
    );
    EXPECT_THROW(
        ipc1.send(OutputBuffer(10)),
        IPCSendError
    );
    EXPECT_NO_THROW(
        ipc1.open();
        ipc2.open();
    );
    EXPECT_NO_THROW(
        ipc1.send(OutputBuffer(10))
    );
}

}

