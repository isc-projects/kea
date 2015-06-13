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

#include <config.h>
#include <gtest/gtest.h>
#include <util/unittests/test_exceptions.h>

#include <exceptions/exceptions.h>

#include <asio.hpp>
#include <asiolink/asiolink.h>
#include <asiodns/asiodns.h>

#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <csignal>

#include <sys/types.h>
#include <sys/socket.h>

#include <unistd.h>
#include <netdb.h>

using namespace isc::asiolink;
using namespace isc::asiodns;
using boost::scoped_ptr;
using boost::lexical_cast;

namespace {
const char* const TEST_SERVER_PORT = "53535";
const char* const TEST_IPV6_ADDR = "::1";

// A simple lookup callback for DNS services.  It records the pointer value of
// to given output buffer each time the callback is called (up to two times)
// for the main tests.  At the end of the second callback it stops the server.
// The sender of the data doesn't expect to get a response, so it simply
// discards any received data.
class TestLookup : public DNSLookup {
public:
    TestLookup(isc::util::OutputBuffer** b1, isc::util::OutputBuffer** b2,
               IOService& io_service) :
        first_buffer_(b1), second_buffer_(b2), io_service_(io_service)
    {}
    void operator()(const IOMessage&, isc::dns::MessagePtr,
                    isc::dns::MessagePtr, isc::util::OutputBufferPtr buffer,
                    DNSServer* server) const
    {
        server->resume(false);
        if (*first_buffer_ == NULL) {
            *first_buffer_ = buffer.get();
        } else {
            assert(*second_buffer_ == NULL);
            *second_buffer_ = buffer.get();
            server->stop();
            io_service_.stop();
        }
    }
    isc::util::OutputBuffer** first_buffer_;
    isc::util::OutputBuffer** second_buffer_;
    IOService& io_service_;
};

// A test fixture to check creation of UDP servers from a socket FD, changing
// options.
class UDPDNSServiceTest : public::testing::Test {
private:
    static const unsigned int IO_SERVICE_TIME_OUT = 5;

protected:
    UDPDNSServiceTest() :
        first_buffer_(NULL), second_buffer_(NULL),
        lookup(&first_buffer_, &second_buffer_, io_service),
        dns_service(io_service, &lookup, NULL),
        client_socket(io_service.get_io_service(), asio::ip::udp::v6()),
        server_ep(asio::ip::address::from_string(TEST_IPV6_ADDR),
                  lexical_cast<uint16_t>(TEST_SERVER_PORT)),
        asio_service(io_service.get_io_service())
    {
        current_service = &io_service;
        // Content shouldn't matter for the tests, but initialize anyway
        memset(data, 1, sizeof(data));
    }

    ~UDPDNSServiceTest() {
        current_service = NULL;
    }

    void runService() {
        io_service_is_time_out = false;

        // Send two UDP packets, which will be passed to the TestLookup
        // callback.  They are not expected to be responded, so it simply
        // closes the socket right after that.
        client_socket.send_to(asio::buffer(data, sizeof(data)), server_ep);
        client_socket.send_to(asio::buffer(data, sizeof(data)), server_ep);
        client_socket.close();

        // set a signal-based alarm to prevent the test from hanging up
        // due to a bug.
        void (*prev_handler)(int) =
            std::signal(SIGALRM, UDPDNSServiceTest::stopIOService);
        current_service = &io_service;
        alarm(IO_SERVICE_TIME_OUT);
        io_service.run();
        io_service.get_io_service().reset();
        //cancel scheduled alarm
        alarm(0);
        std::signal(SIGALRM, prev_handler);
    }

    // last resort service stopper by signal
    static void stopIOService(int) {
        io_service_is_time_out = true;
        if (current_service != NULL) {
            current_service->stop();
        }
    }

    bool serverStopSucceed() const {
        return (!io_service_is_time_out);
    }

    isc::util::OutputBuffer* first_buffer_;
    isc::util::OutputBuffer* second_buffer_;
    IOService io_service;
    TestLookup lookup;
    DNSService dns_service;
private:
    asio::ip::udp::socket client_socket;
    const asio::ip::udp::endpoint server_ep;
    char data[4];

    // To access them in signal handle function, the following
    // variables have to be static.
    static IOService* current_service;
    static bool io_service_is_time_out;

    asio::io_service& asio_service;
};

// Need to define the non-const static members outside of the class
// declaration
IOService* UDPDNSServiceTest::current_service;
bool UDPDNSServiceTest::io_service_is_time_out;

// A helper socket FD creator for given address and port.  It's generally
// expected to succeed; on failure it simply throws an exception to make
// the test fail.
int
getSocketFD(int family, const char* const address, const char* const port) {
    struct addrinfo hints, *res = NULL;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = family;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    hints.ai_flags = AI_NUMERICHOST | AI_NUMERICSERV;
    int s = -1;
    int error = getaddrinfo(address, port, &hints, &res);
    if (error == 0) {
        // If getaddrinfo returns 0, res should be set to a non NULL valid
        // pointer, but some variants of cppcheck reportedly complains about
        // it, so we satisfy them here.
        if (res != NULL) {
            s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
            if (s >= 0) {
                error = bind(s, res->ai_addr, res->ai_addrlen);
            }
            freeaddrinfo(res);
        }
    }
    if (error != 0) {
        if (s >= 0) {
            close(s);
        }
        isc_throw(isc::Unexpected, "failed to open test socket");
    }
    return (s);
}

TEST_F(UDPDNSServiceTest, defaultUDPServerFromFD) {
    // If no option is explicitly specified, an asynchronous server should be
    // created.  So the two output buffers should be different.
    dns_service.addServerUDPFromFD(getSocketFD(AF_INET6, TEST_IPV6_ADDR,
                                               TEST_SERVER_PORT), AF_INET6);
    runService();
    EXPECT_TRUE(serverStopSucceed());
    EXPECT_NE(first_buffer_, second_buffer_);
}

TEST_F(UDPDNSServiceTest, explicitDefaultUDPServerFromFD) {
    // If "default" option is explicitly specified, the effect should be the
    // same as the previous case.
    dns_service.addServerUDPFromFD(getSocketFD(AF_INET6, TEST_IPV6_ADDR,
                                               TEST_SERVER_PORT),
                                   AF_INET6, DNSService::SERVER_DEFAULT);
    runService();
    EXPECT_TRUE(serverStopSucceed());
    EXPECT_NE(first_buffer_, second_buffer_);
}

TEST_F(UDPDNSServiceTest, syncUDPServerFromFD) {
    // If "SYNC_OK" option is specified, a synchronous server should be
    // created.  It will reuse the output buffer, so the recorded two pointer
    // should be identical.
    dns_service.addServerUDPFromFD(getSocketFD(AF_INET6, TEST_IPV6_ADDR,
                                               TEST_SERVER_PORT),
                                   AF_INET6, DNSService::SERVER_SYNC_OK);
    runService();
    EXPECT_TRUE(serverStopSucceed());
    EXPECT_EQ(first_buffer_, second_buffer_);
}

TEST_F(UDPDNSServiceTest, addUDPServerFromFDWithUnknownOption) {
    // Use of undefined/incompatible options should result in an exception.
    EXPECT_THROW_WITH(dns_service.addServerUDPFromFD(
                         getSocketFD(AF_INET6, TEST_IPV6_ADDR,
                                     TEST_SERVER_PORT),
                         AF_INET6,
                         static_cast<DNSService::ServerFlag>(2)),
                      isc::InvalidParameter,
                      "Invalid DNS/UDP server option: 2");
}

} // unnamed namespace
