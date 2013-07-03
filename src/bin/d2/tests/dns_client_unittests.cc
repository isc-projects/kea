// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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
#include <d2/dns_client.h>
#include <asiodns/io_fetch.h>
#include <asiodns/logger.h>
#include <dns/rcode.h>
#include <dns/rrclass.h>
#include <asio/ip/udp.hpp>
#include <asio/socket_base.hpp>
#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::asiodns;
using namespace isc::d2;

using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace asio;
using namespace asio::ip;

namespace {

const char* TEST_ADDRESS = "127.0.0.1";
const uint16_t TEST_PORT = 5301;
const size_t MAX_SIZE = 1024;

// @brief Test Fixture class.
//
// This test fixture class implements DNSClient::Callback so as it can be
// installed as a completion callback for tests it implements. This callback
// is called when a DDNS transaction (send and receive) completes. This allows
// for the callback function to direcetly access class members. In particular,
// the callback function can access IOService on which run() was called and
// call stop() on it.
class DNSClientTest : public virtual ::testing::Test, DNSClient::Callback {
public:
    IOService service_;
    D2UpdateMessagePtr response_;
    DNSClient::Status status_;
    uint8_t receive_buffer_[MAX_SIZE];

    // @brief Constructor.
    //
    // This constructor overrides the default logging level of asiodns logger to
    // prevent it from emitting debug messages from IOFetch class. Such an error
    // message can be emitted if timeout occurs when DNSClient class is
    // waiting for a response. Some of the tests are checking DNSClient behavior
    // in case when response from the server is not received. Tests output would
    // become messy if such errors were logged.
    DNSClientTest()
        : service_(),
          status_(DNSClient::SUCCESS) {
        asiodns::logger.setSeverity(log::INFO);
        response_.reset(new D2UpdateMessage(D2UpdateMessage::INBOUND));
    }

    // @brief Destructor.
    //
    // Sets the asiodns logging level back to DEBUG.
    virtual ~DNSClientTest() {
        asiodns::logger.setSeverity(log::DEBUG);
    };

    // @brief Exchange completion calback.
    //
    // This callback is called when the exchange with the DNS server is
    // complete or an error occured. This includes the occurence of a timeout.
    //
    // @param status A status code returned by DNSClient.
    virtual void operator()(DNSClient::Status status) {
        status_ = status;
        service_.stop();
    }

    // @brief Handler invoked when test request is received.
    //
    // This callback handler is installed when performing async read on a
    // socket to emulate reception of the DNS Update request by a server.
    // As a result, this handler will send an appropriate DNS Update response
    // message back to the address from which the request has come.
    //
    // @param socket A pointer to a socket used to receive a query and send a
    // response.
    // @param remote A pointer to an object which specifies the host (address
    // and port) from which a request has come.
    // @param receive_length A length (in bytes) of the received data.
    void udpReceiveHandler(udp::socket* socket, udp::endpoint* remote,
                           size_t receive_length) {
        // The easiest way to create a response message is to copy the entire
        // request.
        OutputBuffer response_buf(receive_length);
        response_buf.writeData(receive_buffer_, receive_length);

        // What must be different between a request and response is the QR
        // flag bit. This bit differentiates both types of messages. We have
        // to set this bit to 1. Note that the 3rd byte of the message header
        // comprises this bit in the front followed by the message code and
        // reserved zeros. Therefore, this byte comprises:
        //             10101000,
        // where a leading bit is a QR flag. The hexadecimal value is 0xA8.
        // Write it at message offset 2.
        response_buf.writeUint8At(0xA8, 2);
        // A response message is now ready to send. Send it!
        socket->send_to(asio::buffer(response_buf.getData(),
                                     response_buf.getLength()),
                        *remote);
    }

    // This test verifies that when invalid response placeholder object is
    // passed to a constructor, constructor throws the appropriate exception.
    // It also verifies that the constructor will not throw if the supplied
    // callback object is NULL.
    void runConstructorTest() {
        D2UpdateMessagePtr null_response;
        EXPECT_THROW(DNSClient(null_response, this), isc::BadValue);
        EXPECT_NO_THROW(DNSClient(response_, NULL));
    }

    // This test verifies the DNSClient behavior when a server does not respond
    // do the DNS Update message. In such case, the callback function is
    // expected to be called and the TIME_OUT error code should be returned.
    void runSendNoReceiveTest() {
        // Create outgoing message. Simply set the required message fields:
        // error code and Zone section. This is enough to create on-wire format
        // of this message and send it.
        D2UpdateMessage message(D2UpdateMessage::OUTBOUND);
        ASSERT_NO_THROW(message.setRcode(Rcode(Rcode::NOERROR_CODE)));
        ASSERT_NO_THROW(message.setZone(Name("example.com"), RRClass::IN()));

        // Use scoped pointer so as we can declare dns_client in the function
        // scope.
        boost::scoped_ptr<DNSClient> dns_client;
        // Constructor may throw if the response placehoder is NULL.
        ASSERT_NO_THROW(dns_client.reset(new DNSClient(response_, this)));

        // Set the response wait time to 0 so as our test is not hanging. This
        // should cause instant timeout.
        const int timeout = 0;
        // The doUpdate() function starts asynchronous message exchange with DNS
        // server. When message exchange is done or timeout occurs, the
        // completion callback will be triggered. The doUpdate function returns
        // immediately.
        EXPECT_NO_THROW(dns_client->doUpdate(service_, IOAddress(TEST_ADDRESS),
                                             TEST_PORT, message, timeout));

        // This starts the execution of tasks posted to IOService. run() blocks
        // until stop() is called in the completion callback function.
        service_.run();

        // If callback function was called it should have modified the default
        // value of status_ with the TIMEOUT error code.
        EXPECT_EQ(DNSClient::TIMEOUT, status_);
    }

    // This test verifies that DNSClient can send DNS Update and receive a
    // corresponding response from a server.
    void runSendReceiveTest() {
        // Create a request DNS Update message.
        D2UpdateMessage message(D2UpdateMessage::OUTBOUND);
        ASSERT_NO_THROW(message.setRcode(Rcode(Rcode::NOERROR_CODE)));
        ASSERT_NO_THROW(message.setZone(Name("example.com"), RRClass::IN()));

        // Create an instance of the DNSClient. Constructor may throw an
        // exception, so we guard it with EXPECT_NO_THROW.
        boost::scoped_ptr<DNSClient> dns_client;
        EXPECT_NO_THROW(dns_client.reset(new DNSClient(response_, this)));

        // In order to perform the full test, when the client sends the request
        // and receives a response from the server, we have to emulate the
        // server's response in the test. A request will be sent via loopback
        // interface to 127.0.0.1 and known test port. Response must be sent
        // to 127.0.0.1 and a source port which has been used to send the
        // request. A new socket is created, specifically to handle sending
        // responses. The reuse address option is set so as both sockets can
        // use the same address. This new socket is bound to the test address
        // and port, where requests will be sent.
        udp::socket udp_socket(service_.get_io_service(), asio::ip::udp::v4());
        udp_socket.set_option(socket_base::reuse_address(true));
        udp_socket.bind(udp::endpoint(address::from_string(TEST_ADDRESS),
                                      TEST_PORT));
        // Once socket is created, we can post an IO request to receive some
        // a packet from this socket. This is asynchronous operation and
        // nothing is received until another IO request to send a query is
        // posted and the run() is invoked on this IO. A callback function is
        // attached to this asynchronous read. This callback function requires
        // that a socket object used to receive the request is passed to it,
        // because the same socket will be used by the callback function to send
        // a response. Also, the remote object is passed to the callback,
        // because it holds a source address and port where request originated.
        // Callback function will send a response to this address and port.
        // The last parameter holds a length of the received request. It is
        // required to construct a response.
        udp::endpoint remote;
        udp_socket.async_receive_from(asio::buffer(receive_buffer_,
                                                   sizeof(receive_buffer_)),
                                      remote,
                                      boost::bind(&DNSClientTest::udpReceiveHandler,
                                                  this, &udp_socket, &remote, _2));

        // The socket is now ready to receive the data. Let's post some request
        // message then.
        const int timeout = 5;
        dns_client->doUpdate(service_, IOAddress(TEST_ADDRESS), TEST_PORT,
                             message, timeout);

        // Kick of the message exchange by actually running the scheduled
        // "send" and "receive" operations.
        service_.run();

        udp_socket.close();

        // We should have received a response.
        EXPECT_EQ(DNSClient::SUCCESS, status_);

        ASSERT_TRUE(response_);
        EXPECT_EQ(D2UpdateMessage::RESPONSE, response_->getQRFlag());
        ASSERT_EQ(1, response_->getRRCount(D2UpdateMessage::SECTION_ZONE));
        D2ZonePtr zone = response_->getZone();
        ASSERT_TRUE(zone);
        EXPECT_EQ("example.com.", zone->getName().toText());
        EXPECT_EQ(RRClass::IN().getCode(), zone->getClass().getCode());
    }
};

TEST_F(DNSClientTest, constructor) {
    runConstructorTest();
}

TEST_F(DNSClientTest, timeout) {
    runSendNoReceiveTest();
}

TEST_F(DNSClientTest, sendReceive) {
    runSendReceiveTest();
}

} // End of anonymous namespace
