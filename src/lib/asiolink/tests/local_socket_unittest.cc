// Copyright (C) 2013, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/local_socket.h>
#include <asiolink/io_error.h>

#include <gtest/gtest.h>

#include <util/unittests/test_exceptions.h>

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/bind.hpp>

#include <csignal>
#include <cstring>
#include <vector>

#include <sys/socket.h>
#include <stdint.h>
#include <unistd.h>             // for alarm(3)

using namespace isc::asiolink;

namespace {

// duration (in seconds) until we break possible hangup; value is an
// arbitrary choice.
const unsigned IO_TIMEOUT = 10;

// A simple RAII wrapper for a file descriptor so test sockets are safely
// closed in each test.
class ScopedSocket : boost::noncopyable {
public:
    ScopedSocket() : fd_(-1) {}
    ~ScopedSocket() {
        if (fd_ >= 0) {
            EXPECT_EQ(0, ::close(fd_));
        }
    }
    void set(int fd) {
        assert(fd_ == -1);
        fd_ = fd;
    }
    int get() { return (fd_); }
    int release() {
        const int ret = fd_;
        fd_ = -1;
        return (ret);
    }
private:
    int fd_;
};

class LocalSocketTest : public ::testing::Test {
protected:
    LocalSocketTest() {
        int sock_pair[2];
        EXPECT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, sock_pair));
        sock_pair_[0].set(sock_pair[0]);
        sock_pair_[1].set(sock_pair[1]);

        // For tests using actual I/O we use a timer to prevent hangup
        // due to a bug.  Set up the signal handler for the timer here.
        g_io_service_ = &io_service_;
        prev_handler_ = std::signal(SIGALRM, stopIOService);
    }

    ~LocalSocketTest() {
        alarm(0);
        // reset the global to NULL to detect any invalid access to freed
        // io_service (this shouldn't happen, so we don't change stopIOService
        // itself)
        g_io_service_ = NULL;
        std::signal(SIGALRM, prev_handler_);
    }

    // Common set of tests for async read
    void checkAsyncRead(size_t data_len);

    IOService io_service_;
    ScopedSocket sock_pair_[2];
    std::vector<uint8_t> read_buf_;
private:
    static IOService* g_io_service_; // will be set to &io_service_
    void (*prev_handler_)(int);

    // SIGALRM handler to prevent hangup.  This must be a static method
    // so it can be passed to std::signal().
    static void stopIOService(int) {
        g_io_service_->stop();
    }
};

IOService* LocalSocketTest::g_io_service_ = NULL;

TEST_F(LocalSocketTest, construct) {
    const int fd = sock_pair_[0].release();
    LocalSocket sock(io_service_, fd);
    EXPECT_EQ(fd, sock.getNative());
    EXPECT_EQ(AF_UNIX, sock.getProtocol());
}

TEST_F(LocalSocketTest, constructError) {
    // try to construct a LocalSocket object with a closed socket.  It should
    // fail.
    const int fd = sock_pair_[0].release();
    EXPECT_EQ(0, close(fd));
    EXPECT_THROW_WITH(LocalSocket(io_service_, fd), IOError,
                      "failed to open local socket with FD " << fd
                      << " (local endpoint unknown): "
                      << strerror(ENOTSOCK));
}

TEST_F(LocalSocketTest, autoClose) {
    // Confirm that passed FD will be closed on destruction of LocalSocket
    const int fd = sock_pair_[0].release();
    {
        LocalSocket sock(io_service_, fd);
    }
    // fd should have been closed, so close() should fail (we assume there's
    // no other open() call since then)
    EXPECT_EQ(-1, ::close(fd));
}

void
callback(const std::string& error, IOService* io_service, bool* called,
         bool expect_error)
{
    if (expect_error) {
        EXPECT_NE("", error);
    } else {
        EXPECT_EQ("", error);
    }
    *called = true;
    io_service->stop();
}

void
LocalSocketTest::checkAsyncRead(size_t data_len) {
    LocalSocket sock(io_service_, sock_pair_[0].release());
    bool callback_called = false;
    read_buf_.resize(data_len);
    sock.asyncRead(boost::bind(&callback, _1, &io_service_, &callback_called,
                               false), &read_buf_[0], data_len);

    std::vector<uint8_t> expected_data(data_len);
    for (size_t i = 0; i < data_len; ++i) {
        expected_data[i] = i & 0xff;
    }
    alarm(IO_TIMEOUT);
    // If write blocks, it will eventually fail due to signal interruption.
    // Since io_service has been stopped already, run() would immediately
    // return and test should complete (with failure).  But to make very sure
    // it never cause hangup we rather return from the test at the point of
    // failure of write.  In either case it signals a failure and need for
    // a fix.
    ASSERT_EQ(data_len, write(sock_pair_[1].get(), &expected_data[0],
                              data_len));
    io_service_.run();
    EXPECT_TRUE(callback_called);
    EXPECT_EQ(0, std::memcmp(&expected_data[0], &read_buf_[0], data_len));
    
}

TEST_F(LocalSocketTest, asyncRead) {
    // A simple case of asynchronous read: wait for 1 byte and successfully
    // read it in the run() loop.
    checkAsyncRead(1);
}

TEST_F(LocalSocketTest, asyncLargeRead) {
    // Similar to the previous case, but for moderately larger data.
    // (for the moment) we don't expect to use this interface with much
    // larger data that could cause blocking write.
    checkAsyncRead(1024);
}

TEST_F(LocalSocketTest, asyncPartialRead) {
    alarm(IO_TIMEOUT);

    // specify reading 4 bytes of data, and send 3 bytes.  It shouldn't cause
    // callback.  while we actually don't use the buffer, we'll initialize it
    // to make valgrind happy.
    char recv_buf[4];
    std::memset(recv_buf, 0, sizeof(recv_buf));
    bool callback_called = false;
    LocalSocket sock(io_service_, sock_pair_[0].release());
    sock.asyncRead(boost::bind(&callback, _1, &io_service_, &callback_called,
                               false), recv_buf, sizeof(recv_buf));
    EXPECT_EQ(3, write(sock_pair_[1].get(), recv_buf, 3));

    // open another pair of sockets so we can stop the IO service after run.
    int socks[2];
    char ch = 0;
    EXPECT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, socks));
    ScopedSocket aux_sockpair[2];
    aux_sockpair[0].set(socks[0]);
    aux_sockpair[1].set(socks[1]);
    LocalSocket aux_sock(io_service_, aux_sockpair[0].get());
    aux_sockpair[0].release();  // on successful construction we should release
    bool aux_callback_called = false;
    aux_sock.asyncRead(boost::bind(&callback, _1, &io_service_,
                                   &aux_callback_called, false), &ch, 1);
    EXPECT_EQ(1, write(aux_sockpair[1].get(), &ch, 1));

    // run the IO service, it will soon be stopped via the auxiliary callback.
    // the main callback shouldn't be called.
    io_service_.run();
    EXPECT_FALSE(callback_called);
    EXPECT_TRUE(aux_callback_called);
}

TEST_F(LocalSocketTest, asyncReadError) {
    const int sock_fd = sock_pair_[0].release();
    LocalSocket sock(io_service_, sock_fd);
    bool callback_called = false;
    read_buf_.resize(1);
    read_buf_.at(0) = 53;       // dummy data to check it later
    const char ch = 35; // send different data to the read socket with data
    EXPECT_EQ(1, write(sock_pair_[1].get(), &ch, 1));
    close(sock_fd);             // invalidate the read socket
    // we'll get callback with an error (e.g. 'bad file descriptor)
    sock.asyncRead(boost::bind(&callback, _1, &io_service_, &callback_called,
                               true), &read_buf_[0], 1);

    io_service_.run();
    EXPECT_TRUE(callback_called);
    EXPECT_EQ(53, read_buf_.at(0));
}

TEST_F(LocalSocketTest, asyncReadThenDestroy) {
    // destroy the socket before running the IO service.  we'll still get
    // callback with an error.
    boost::scoped_ptr<LocalSocket> sock(
        new LocalSocket(io_service_, sock_pair_[0].release()));
    read_buf_.resize(1);
    bool callback_called = false;
    sock->asyncRead(boost::bind(&callback, _1, &io_service_, &callback_called,
                                true), &read_buf_[0], 1);
    sock.reset();

    io_service_.run();
    EXPECT_TRUE(callback_called);
}

}
