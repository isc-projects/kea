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

#include <config.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/errno.h>

#include <unistd.h>
#include <stdint.h>
#include <cstring>
#include <netdb.h>

#include <iostream>
#include <vector>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <exceptions/exceptions.h>

#include <bench/benchmark.h>
#include <bench/benchmark_util.h>

using namespace std;
using namespace isc;
using namespace isc::bench;

using namespace boost::asio;
using ip::udp;
namespace {
class NativeSocketBenchMark {
public:
    NativeSocketBenchMark(const int af, const char* const portstr,
                   const size_t packet_size) :
        fd_(-1), packet_size_(packet_size), s_data_(packet_size),
        r_data_(packet_size)
    {
        struct addrinfo hints;

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = af;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_protocol = IPPROTO_UDP;
        int error = getaddrinfo(af == AF_INET6 ? "::1" : "127.0.0.1",
                                portstr, &hints, &res_);
        if (error) {
            isc_throw(Exception, "getaddrinfo failed: " << gai_strerror(error));
        }
        // XXX: for brevity the following part is intentionally exception
        // unsafe.
        fd_ = socket(res_->ai_family, res_->ai_socktype, res_->ai_protocol);
        if (fd_ < 0) {
            isc_throw(Exception, "failed to open test socket: "
                      << strerror(errno));
        }
        if (bind(fd_, res_->ai_addr, res_->ai_addrlen) != 0) {
            isc_throw(Exception, "failed to bind test socket: "
                      << strerror(errno));
        }
        maxfd_ = fd_ + 1;
        FD_ZERO(&readfds_);
        FD_SET(fd_, &readfds_);
    }
    ~NativeSocketBenchMark() {
        if (fd_ >= 0) {
            close(fd_);
        }
        freeaddrinfo(res_);
    }
    void closeSocket() {
        if (fd_ >= 0) {
            close(fd_);
        }
        fd_ = -1;
    }
    unsigned int run() {
        const int cc_s = sendto(fd_, &s_data_[0], s_data_.size(), 0,
                                res_->ai_addr, res_->ai_addrlen);
        if (cc_s != packet_size_) {
            isc_throw(Exception, "sendto failed, return value=" << cc_s);
        }
        fd_set readfds = readfds_;
        const int n = select(maxfd_, &readfds, NULL, NULL, NULL);
        if (n != 1 || !FD_ISSET(fd_, &readfds)) {
            isc_throw(Exception, "unexpected result from select, return value="
                      << n);
        }

        struct sockaddr* from = reinterpret_cast<struct sockaddr*>(&ss_);
        socklen_t from_len = sizeof(ss_);
        r_data_.clear();
        const int cc_r = recvfrom(fd_, &r_data_[0], r_data_.capacity(), 0, from,
                                  &from_len);
        if (cc_r != packet_size_) {
            isc_throw(Exception, "recvfrom failed, return value=" << cc_r);
        }

        return (1);
    }
private:
    int fd_;
    int maxfd_;
    const size_t packet_size_;
    struct addrinfo* res_;
    vector<uint8_t> s_data_;
    vector<uint8_t> r_data_;
    fd_set readfds_;
    struct sockaddr_storage ss_;
};

class ASIOBenchMark {
public:
    ASIOBenchMark(io_service& io_service, const int af, const uint16_t portnum,
                  const size_t packet_size) :
        packet_size_(packet_size),
        io_service_(io_service),
        socket_(io_service, af == AF_INET6 ? udp::v6() : udp::v4()),
        s_data_(packet_size), r_data_(packet_size),
        endpoint_(af == AF_INET6 ? udp::v6() : udp::v4(), portnum)
    {
        endpoint_.address(ip::address::from_string(
                              af == AF_INET6 ? "::1" : "127.0.0.1"));
        socket_.bind(endpoint_);
    }
    unsigned int run() {
        isc_throw(Exception, "test is performed for a base class");
    }
    void cleanup() {
        socket_.close();
        io_service_.reset();
    }
protected:
    const size_t packet_size_;
    io_service& io_service_;
    udp::socket socket_;
    vector<uint8_t> s_data_;
    vector<uint8_t> r_data_;
    udp::endpoint endpoint_;
    udp::endpoint sender_endpoint_;
    boost::system::error_code serror_;
};

class ASIOSyncBenchMark : public ASIOBenchMark {
public:
    ASIOSyncBenchMark(io_service& io_service, const int af,
                      const uint16_t portnum, const size_t packet_size) :
        ASIOBenchMark(io_service, af, portnum, packet_size),
        fd_(socket_.native()), maxfd_(fd_ + 1)
    {
        FD_ZERO(&readfds_);
        FD_SET(fd_, &readfds_);
    }
    unsigned int run() {
        const size_t cc_s = socket_.send_to(
            boost::asio::buffer(&s_data_[0], s_data_.size()),
            endpoint_, 0, serror_);
        if (cc_s != packet_size_ || serror_) {
            isc_throw(Exception, "asio::send_to failed, return value="
                      << cc_s);
        }

        // add the overhead of select for fair comparison
        fd_set readfds = readfds_;
        const int n = select(maxfd_, &readfds, NULL, NULL, NULL);
        if (n != 1 || !FD_ISSET(fd_, &readfds)) {
            isc_throw(Exception, "unexpected result from select, return value="
                      << n);
        }

        r_data_.clear();
        const size_t cc_r = socket_.receive_from(
            boost::asio::buffer(&r_data_[0], r_data_.capacity()),
            sender_endpoint_);
        if (cc_r != packet_size_) {
            isc_throw(Exception, "asio::receive_from failed, return value="
                      << cc_r);
        }

        return (1);
    }
private:
    const int fd_;
    const int maxfd_;
    fd_set readfds_;
};

class ASIOAsyncBenchMark : public ASIOBenchMark {
public:
    ASIOAsyncBenchMark(io_service& io_service, const int af,
                       const uint16_t portnum, const size_t packet_size,
                       const unsigned int iteration, const bool async_send) :
        ASIOBenchMark(io_service, af, portnum, packet_size),
        iteration_(iteration), n_received_(0), async_send_(async_send)
    {}
    unsigned int run() {
        if (!async_send_) {
            startReceive();
        }
        sendTo();
        io_service_.run();
        return (iteration_);
    }
private:
    void sendTo() {
        if (async_send_) {
            socket_.async_send_to(
                boost::asio::buffer(&s_data_[0], s_data_.size()),
                endpoint_,
                boost::bind(&ASIOAsyncBenchMark::sendCompleted, this,
                            placeholders::error,
                            placeholders::bytes_transferred));
        } else {
            const size_t cc_s = socket_.send_to(
                boost::asio::buffer(&s_data_[0], s_data_.size()),
                endpoint_, 0, serror_);
            if (cc_s != packet_size_ || serror_) {
                isc_throw(Exception, "asio::send_to failed, return value="
                          << cc_s);
            }
        }
    }
    void handleReceive(const boost::system::error_code& error,
                       size_t bytes_recvd)
    {
        if (error || bytes_recvd != packet_size_) {
            isc_throw(Exception, "asio::asyncronous receive failed: "
                      << error << ", #received=" << bytes_recvd);
        }
        if (++n_received_ == iteration_) {
            io_service_.stop();
        } else {
            sendTo();
            if (!async_send_) {
                startReceive();
            }
        }
    }
    void startReceive() {
        socket_.async_receive_from(
            boost::asio::buffer(&r_data_[0], r_data_.capacity()),
            sender_endpoint_,
            boost::bind(&ASIOAsyncBenchMark::handleReceive, this,
                        placeholders::error,
                        placeholders::bytes_transferred));
    }
    void sendCompleted(const boost::system::error_code& error UNUSED_PARAM,
                       size_t bytes_sent UNUSED_PARAM)
    {
        // ignore possible errors and just keep receiving.
        startReceive();
    }
private:
    const unsigned int iteration_;
    unsigned int n_received_;
    const bool async_send_;
};
}

namespace isc {
namespace bench {
template<>
void
BenchMark<NativeSocketBenchMark>::tearDown() {
    target_.closeSocket();
}

template<>
void
BenchMark<ASIOSyncBenchMark>::tearDown() {
    target_.cleanup();
}

template<>
void
BenchMark<ASIOAsyncBenchMark>::tearDown() {
    target_.cleanup();
}
}
}

namespace {
const int DEFAULT_PACKET_SIZE = 250; // arbitrary choice
const int DEFAULT_ITERATION = 10000;
const char* const DEFAULT_PORTSTR = "53530";

void
usage() {
    cerr << "Usage: netio_bench [-n iterations] [-p port] [-s packet_size]"
        << endl;
    exit (1);
}
}

int
main(int argc, char* argv[]) {
    int ch;
    int iteration = DEFAULT_ITERATION;
    int packet_size = DEFAULT_PACKET_SIZE;

    const char* portstr = DEFAULT_PORTSTR;

    while ((ch = getopt(argc, argv, "n:p:s:")) != -1) {
        switch (ch) {
        case 'n':
            iteration = atoi(optarg);
            break;
        case 'p':
            portstr = optarg;
            break;
        case 's':
            packet_size = atoi(optarg);
            break;
        case '?':
        default:
            usage();
        }
    }
    argc -= optind;
    argv += optind;
    if (argc > 0) {
        usage();
    }

    boost::asio::io_service io_service;
    const uint16_t portnum = static_cast<uint16_t>(atoi(portstr));

    cout << "Socket I/O benchmark using native socket API (IPv4)" << endl;
    NativeSocketBenchMark io_bench1(AF_INET, portstr, packet_size);
    BenchMark<NativeSocketBenchMark> bench1(iteration, io_bench1);
    bench1.run();

    cout << "Socket I/O benchmark using native socket API (IPv6)" << endl;
    NativeSocketBenchMark io_bench2(AF_INET6, portstr, packet_size);
    BenchMark<NativeSocketBenchMark> bench2(iteration, io_bench2);
    bench2.run();

    cout << "ASIO benchmark using synchronous I/O (IPv4)" << endl;
    ASIOSyncBenchMark io_bench3(io_service, AF_INET, portnum, packet_size);
    BenchMark<ASIOSyncBenchMark> bench3(iteration, io_bench3);
    bench3.run();

    cout << "ASIO benchmark using synchronous I/O (IPv6)" << endl;
    ASIOSyncBenchMark io_bench4(io_service, AF_INET6, portnum, packet_size);
    BenchMark<ASIOSyncBenchMark> bench4(iteration, io_bench4);
    bench4.run();

    cout << "ASIO benchmark using asynchronous receive I/O (IPv4)" << endl;
    ASIOAsyncBenchMark io_bench5(io_service, AF_INET, portnum, packet_size,
                                 iteration, false);
    BenchMark<ASIOAsyncBenchMark> bench5(1, io_bench5);
    bench5.run();

    cout << "ASIO benchmark using asynchronous receive I/O (IPv6)" << endl;
    ASIOAsyncBenchMark io_bench6(io_service, AF_INET6, portnum, packet_size,
                                 iteration, false);
    BenchMark<ASIOAsyncBenchMark> bench6(1, io_bench6);
    bench6.run();

    cout << "ASIO benchmark using asynchronous send/receive I/O (IPv4)" << endl;
    ASIOAsyncBenchMark io_bench7(io_service, AF_INET, portnum, packet_size,
                                 iteration, true);
    BenchMark<ASIOAsyncBenchMark> bench7(1, io_bench7);
    bench7.run();

    cout << "ASIO benchmark using asynchronous send/receive I/O (IPv6)" << endl;
    ASIOAsyncBenchMark io_bench8(io_service, AF_INET6, portnum, packet_size,
                                 iteration, true);
    BenchMark<ASIOAsyncBenchMark> bench8(1, io_bench8);
    bench8.run();

    return (0);
}
