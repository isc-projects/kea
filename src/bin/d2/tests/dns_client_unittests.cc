// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dns/opcode.h>
#include <asiodns/io_fetch.h>
#include <asiodns/logger.h>
#include <asiolink/interval_timer.h>
#include <dns/messagerenderer.h>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>
#include <nc_test_utils.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::asiodns;
using namespace isc::d2;

using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace {

const char* TEST_ADDRESS = "127.0.0.1";
const uint16_t TEST_PORT = 5301;
const size_t MAX_SIZE = 1024;
const long TEST_TIMEOUT = 5 * 1000;

// @brief Test Fixture class.
//
// This test fixture class implements DNSClient::Callback so as it can be
// installed as a completion callback for tests it implements. This callback
// is called when a DDNS transaction (send and receive) completes. This allows
// for the callback function to directly access class members. In particular,
// the callback function can access IOService on which run() was called and
// call stop() on it.
//
// Many of the tests defined here schedule execution of certain tasks and block
// until tasks are completed or a timeout is hit. However, if timeout is not
// properly handled a task may be hanging for a long time. In order to prevent
// it, the asiolink::IntervalTimer is used to break a running test if test
// timeout is hit. This will result in test failure.
class DNSClientTest : public virtual ::testing::Test, DNSClient::Callback {
public:
    IOService service_;
    D2UpdateMessagePtr response_;
    DNSClient::Status status_;
    uint8_t receive_buffer_[MAX_SIZE];
    DNSClientPtr dns_client_;
    bool corrupt_response_;
    bool expect_response_;
    asiolink::IntervalTimer test_timer_;
    int received_;
    int expected_;

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
          status_(DNSClient::SUCCESS),
          corrupt_response_(false),
          expect_response_(true),
          test_timer_(service_),
          received_(0), expected_(0) {
        asiodns::logger.setSeverity(isc::log::INFO);
        response_.reset();
        dns_client_.reset(new DNSClient(response_, this));

        // Set the test timeout to break any running tasks if they hang.
        test_timer_.setup(boost::bind(&DNSClientTest::testTimeoutHandler, this),
                          TEST_TIMEOUT);
    }

    // @brief Destructor.
    //
    // Sets the asiodns logging level back to DEBUG.
    virtual ~DNSClientTest() {
        asiodns::logger.setSeverity(isc::log::DEBUG);
    };

    // @brief Exchange completion callback.
    //
    // This callback is called when the exchange with the DNS server is
    // complete or an error occurred. This includes the occurrence of a timeout.
    //
    // @param status A status code returned by DNSClient.
    virtual void operator()(DNSClient::Status status) {
        status_ = status;
        if (!expected_ || (expected_ == ++received_))
        {
            service_.stop();
        }

        if (expect_response_) {
            if (!corrupt_response_) {
                // We should have received a response.
                EXPECT_EQ(DNSClient::SUCCESS, status_);

                ASSERT_TRUE(response_);
                EXPECT_EQ(D2UpdateMessage::RESPONSE, response_->getQRFlag());
                ASSERT_EQ(1,
                          response_->getRRCount(D2UpdateMessage::SECTION_ZONE));
                D2ZonePtr zone = response_->getZone();
                ASSERT_TRUE(zone);
                EXPECT_EQ("example.com.", zone->getName().toText());
                EXPECT_EQ(RRClass::IN().getCode(), zone->getClass().getCode());

            } else {
                EXPECT_EQ(DNSClient::INVALID_RESPONSE, status_);

            }
        // If we don't expect a response, the status should indicate a timeout.
        } else {
            EXPECT_EQ(DNSClient::TIMEOUT, status_);

        }
    }

    // @brief Handler invoked when test timeout is hit.
    //
    // This callback stops all running (hanging) tasks on IO service.
    void testTimeoutHandler() {
        service_.stop();
        FAIL() << "Test timeout hit.";
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
    // @param corrupt_response A bool value which indicates that the server's
    // response should be invalid (true) or valid (false)
    void udpReceiveHandler(udp::socket* socket, udp::endpoint* remote,
                           size_t receive_length, const bool corrupt_response) {
        // The easiest way to create a response message is to copy the entire
        // request.
        OutputBuffer response_buf(receive_length);
        response_buf.writeData(receive_buffer_, receive_length);
        // If a response is to be valid, we have to modify it slightly. If not,
        // we leave it as is.
        if (!corrupt_response) {
            // For a valid response the QR bit must be set. This bit
            // differentiates both types of messages. Note that the 3rd byte of
            // the message header comprises this bit in the front followed by
            // the message code and reserved zeros. Therefore, this byte
            // has the following value:
            //             10101000,
            // where a leading bit is a QR flag. The hexadecimal value is 0xA8.
            // Write it at message offset 2.
            response_buf.writeUint8At(0xA8, 2);
        }
        // A response message is now ready to send. Send it!
        socket->send_to(boost::asio::buffer(response_buf.getData(),
                                     response_buf.getLength()),
                        *remote);
    }

    // @brief Request handler for testing clients using TSIG
    //
    // This callback handler is installed when performing async read on a
    // socket to emulate reception of the DNS Update request with TSIG by a
    // server.  As a result, this handler will send an appropriate DNS Update
    // response message back to the address from which the request has come.
    //
    // @param socket A pointer to a socket used to receive a query and send a
    // response.
    // @param remote A pointer to an object which specifies the host (address
    // and port) from which a request has come.
    // @param receive_length A length (in bytes) of the received data.
    // @param corrupt_response A bool value which indicates that the server's
    // response should be invalid (true) or valid (false)
    // @param client_key TSIG key the server should use to verify the inbound
    // request.  If the pointer is NULL, the server will not attempt to
    // verify the request.
    // @param server_key TSIG key the server should use to sign the outbound
    // request. If the pointer is NULL, the server will not sign the outbound
    // response.  If the pointer is not NULL and not the same value as the
    // client_key, the server will use a new context to sign the response then
    // the one used to verify it.  This allows us to simulate the server
    // signing with the wrong key.
    void TSIGReceiveHandler(udp::socket* socket, udp::endpoint* remote,
                            size_t receive_length,
                            TSIGKeyPtr client_key,
                            TSIGKeyPtr server_key) {

        TSIGContextPtr context;
        if (client_key) {
            context.reset(new TSIGContext(*client_key));
        }

        isc::util::InputBuffer received_data_buffer(receive_buffer_,
                                                    receive_length);

        dns::Message request(Message::PARSE);
        request.fromWire(received_data_buffer);

        // If contex is not NULL, then we need to verify the message.
        if (context) {
            TSIGError error = context->verify(request.getTSIGRecord(),
                                              receive_buffer_, receive_length);
            if (error != TSIGError::NOERROR()) {
                isc_throw(TSIGVerifyError, "TSIG verification failed: "
                          << error.toText());
            }
        }

        dns::Message response(Message::RENDER);
        response.setOpcode(Opcode(Opcode::UPDATE_CODE));
        response.setHeaderFlag(dns::Message::HEADERFLAG_QR, true);
        response.setQid(request.getQid());
        response.setRcode(Rcode::NOERROR());
        dns::Question question(Name("example.com."),
                                    RRClass::IN(), RRType::SOA());
        response.addQuestion(question);

        MessageRenderer renderer;

        if (!server_key) {
            // don't sign the response.
            context.reset();
        } else if (server_key != client_key) {
            // use a different key to sign the response.
            context.reset(new TSIGContext(*server_key));
        }  // otherwise use the context based on client_key.

        response.toWire(renderer, context.get());
        // A response message is now ready to send. Send it!
        socket->send_to(boost::asio::buffer(renderer.getData(), renderer.getLength()),
                        *remote);
    }

    // This test verifies that when invalid response placeholder object is
    // passed to a constructor, constructor throws the appropriate exception.
    // It also verifies that the constructor will not throw if the supplied
    // callback object is NULL.
    void runConstructorTest() {
        EXPECT_NO_THROW(DNSClient(response_, NULL, DNSClient::UDP));

        // The TCP Transport is not supported right now. So, we return exception
        // if caller specified TCP as a preferred protocol. This test will be
        // removed once TCP is supported.
        EXPECT_THROW(DNSClient(response_, NULL, DNSClient::TCP),
                     isc::NotImplemented);
    }

    // This test verifies that it accepted timeout values belong to the range of
    // <0, DNSClient::getMaxTimeout()>.
    void runInvalidTimeoutTest() {

        expect_response_ = false;

        // Create outgoing message. Simply set the required message fields:
        // error code and Zone section. This is enough to create on-wire format
        // of this message and send it.
        D2UpdateMessage message(D2UpdateMessage::OUTBOUND);
        ASSERT_NO_THROW(message.setRcode(Rcode(Rcode::NOERROR_CODE)));
        ASSERT_NO_THROW(message.setZone(Name("example.com"), RRClass::IN()));

        // Start with a valid timeout equal to maximal allowed. This way we will
        // ensure that doUpdate doesn't throw an exception for valid timeouts.
        unsigned int timeout = DNSClient::getMaxTimeout();
        EXPECT_NO_THROW(dns_client_->doUpdate(service_, IOAddress(TEST_ADDRESS),
                                           TEST_PORT, message, timeout));

        // Cross the limit and expect that exception is thrown this time.
        timeout = DNSClient::getMaxTimeout() + 1;
        EXPECT_THROW(dns_client_->doUpdate(service_, IOAddress(TEST_ADDRESS),
                                           TEST_PORT, message, timeout),
                     isc::BadValue);
    }

    // This test verifies the DNSClient behavior when a server does not respond
    // do the DNS Update message. In such case, the callback function is
    // expected to be called and the TIME_OUT error code should be returned.
    void runSendNoReceiveTest() {
        // We expect no response from a server.
        expect_response_ = false;

        // Create outgoing message. Simply set the required message fields:
        // error code and Zone section. This is enough to create on-wire format
        // of this message and send it.
        D2UpdateMessage message(D2UpdateMessage::OUTBOUND);
        ASSERT_NO_THROW(message.setRcode(Rcode(Rcode::NOERROR_CODE)));
        ASSERT_NO_THROW(message.setZone(Name("example.com"), RRClass::IN()));

        /// @todo The timeout value could be set to 0 to trigger timeout
        /// instantly. However, it may lead to situations that the message sent
        /// in one test will not be dropped by the kernel by the time, the next
        /// test starts. This will lead to intermittent unit test errors as
        /// described in the ticket http://kea.isc.org/ticket/3265.
        /// Increasing the timeout to a non-zero value mitigates this problem.
        /// The proper way to solve this problem is to receive the packet
        /// on our own and drop it. Such a fix will need to be applied not only
        /// to this test but also for other tests that rely on arbitrary timeout
        /// values.
        const int timeout = 500;
        // The doUpdate() function starts asynchronous message exchange with DNS
        // server. When message exchange is done or timeout occurs, the
        // completion callback will be triggered. The doUpdate function returns
        // immediately.
        EXPECT_NO_THROW(dns_client_->doUpdate(service_, IOAddress(TEST_ADDRESS),
                                             TEST_PORT, message, timeout));

        // This starts the execution of tasks posted to IOService. run() blocks
        // until stop() is called in the completion callback function.
        service_.run();

    }

    // This test verifies that DNSClient can send DNS Update and receive a
    // corresponding response from a server.
    void runSendReceiveTest(const bool corrupt_response,
                            const bool two_sends) {
        corrupt_response_ = corrupt_response;

        // Create a request DNS Update message.
        D2UpdateMessage message(D2UpdateMessage::OUTBOUND);
        ASSERT_NO_THROW(message.setRcode(Rcode(Rcode::NOERROR_CODE)));
        ASSERT_NO_THROW(message.setZone(Name("example.com"), RRClass::IN()));

        // In order to perform the full test, when the client sends the request
        // and receives a response from the server, we have to emulate the
        // server's response in the test. A request will be sent via loopback
        // interface to 127.0.0.1 and known test port. Response must be sent
        // to 127.0.0.1 and a source port which has been used to send the
        // request. A new socket is created, specifically to handle sending
        // responses. The reuse address option is set so as both sockets can
        // use the same address. This new socket is bound to the test address
        // and port, where requests will be sent.
        udp::socket udp_socket(service_.get_io_service(), boost::asio::ip::udp::v4());
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
        udp_socket.async_receive_from(boost::asio::buffer(receive_buffer_,
                                                   sizeof(receive_buffer_)),
                                      remote,
                                      boost::bind(&DNSClientTest::udpReceiveHandler,
                                                  this, &udp_socket, &remote, _2,
                                                  corrupt_response));

        // The socket is now ready to receive the data. Let's post some request
        // message then. Set timeout to some reasonable value to make sure that
        // there is sufficient amount of time for the test to generate a
        // response.
        const int timeout = 500;
        expected_++;
        dns_client_->doUpdate(service_, IOAddress(TEST_ADDRESS), TEST_PORT,
                             message, timeout);

        // It is possible to request that two packets are sent concurrently.
        if (two_sends) {
            expected_++;
            dns_client_->doUpdate(service_, IOAddress(TEST_ADDRESS), TEST_PORT,
                                  message, timeout);

        }

        // Kick of the message exchange by actually running the scheduled
        // "send" and "receive" operations.
        service_.run();

        udp_socket.close();

        // Since the callback, operator(), calls stop() on the io_service,
        // we must reset it in order for subsequent calls to run() or
        // run_one() to work.
        service_.get_io_service().reset();
    }

    // Performs a single request-response exchange with or without TSIG
    //
    // @param client_key TSIG passed to dns_client and also used by the
    // ""server" to verify the request.
    // request.
    // @param server_key TSIG key the "server" should use to sign the response.
    // If this is NULL, then client_key is used.
    // @param should_pass indicates if the test should pass.
    void runTSIGTest(TSIGKeyPtr client_key, TSIGKeyPtr server_key,
                     bool should_pass = true) {
        // Tell operator() method if we expect an invalid response.
        corrupt_response_ = !should_pass;

        // Create a request DNS Update message.
        D2UpdateMessage message(D2UpdateMessage::OUTBOUND);
        ASSERT_NO_THROW(message.setRcode(Rcode(Rcode::NOERROR_CODE)));
        ASSERT_NO_THROW(message.setZone(Name("example.com"), RRClass::IN()));

        // Setup our "loopback" server.
        udp::socket udp_socket(service_.get_io_service(), boost::asio::ip::udp::v4());
        udp_socket.set_option(socket_base::reuse_address(true));
        udp_socket.bind(udp::endpoint(address::from_string(TEST_ADDRESS),
                                      TEST_PORT));
        udp::endpoint remote;
        udp_socket.async_receive_from(boost::asio::buffer(receive_buffer_,
                                                   sizeof(receive_buffer_)),
                                      remote,
                                      boost::bind(&DNSClientTest::
                                                  TSIGReceiveHandler, this,
                                                  &udp_socket, &remote, _2,
                                                  client_key, server_key));

        // The socket is now ready to receive the data. Let's post some request
        // message then. Set timeout to some reasonable value to make sure that
        // there is sufficient amount of time for the test to generate a
        // response.
        const int timeout = 500;
        expected_++;
        dns_client_->doUpdate(service_, IOAddress(TEST_ADDRESS), TEST_PORT,
                              message, timeout, client_key);

        // Kick of the message exchange by actually running the scheduled
        // "send" and "receive" operations.
        service_.run();

        udp_socket.close();

        // Since the callback, operator(), calls stop() on the io_service,
        // we must reset it in order for subsequent calls to run() or
        // run_one() to work.
        service_.get_io_service().reset();
    }
};

// Verify that the DNSClient object can be created if provided parameters are
// valid. Constructor should throw exceptions when parameters are invalid.
TEST_F(DNSClientTest, constructor) {
    runConstructorTest();
}

// This test verifies that the maximal allowed timeout value is maximal int
// value.
TEST_F(DNSClientTest, getMaxTimeout) {
    EXPECT_EQ(std::numeric_limits<int>::max(), DNSClient::getMaxTimeout());
}

// Verify that timeout is reported when no response is received from DNS.
TEST_F(DNSClientTest, timeout) {
    runSendNoReceiveTest();
}

// Verify that exception is thrown when invalid (too high) timeout value is
// specified for asynchronous DNS Update.
TEST_F(DNSClientTest, invalidTimeout) {
    runInvalidTimeoutTest();
}

// Verifies that TSIG can be used to sign requests and verify responses.
TEST_F(DNSClientTest, runTSIGTest) {
    std::string secret ("key number one");
    TSIGKeyPtr key_one;
    ASSERT_NO_THROW(key_one.reset(new
                                    TSIGKey(Name("one.com"),
                                            TSIGKey::HMACMD5_NAME(),
                                            secret.c_str(), secret.size())));
    secret = "key number two";
    TSIGKeyPtr key_two;
    ASSERT_NO_THROW(key_two.reset(new
                                    TSIGKey(Name("two.com"),
                                            TSIGKey::HMACMD5_NAME(),
                                            secret.c_str(), secret.size())));
    TSIGKeyPtr nokey;

    // Should be able to send and receive with no keys.
    // Neither client nor server will attempt to sign or verify.
    runTSIGTest(nokey, nokey);

    // Client signs the request, server verfies but doesn't sign.
    runTSIGTest(key_one, nokey, false);

    // Client and server use the same key to sign and verify.
    runTSIGTest(key_one, key_one);

    // Server uses different key to sign the response.
    runTSIGTest(key_one, key_two, false);

    // Client neither signs nor verifies, server responds with a signed answer
    // Since we are "liberal" in what we accept this should be ok.
    runTSIGTest(nokey, key_two);
}

// Verify that the DNSClient receives the response from DNS and the received
// buffer can be decoded as DNS Update Response.
TEST_F(DNSClientTest, sendReceive) {
    // false means that server response is not corrupted.
    runSendReceiveTest(false, false);
}

// Verify that the DNSClient reports an error when the response is received from
// a DNS and this response is corrupted.
TEST_F(DNSClientTest, sendReceiveCurrupted) {
    // true means that server's response is corrupted.
    runSendReceiveTest(true, false);
}

// Verify that it is possible to use the same DNSClient instance to
// perform the following sequence of message exchanges:
// 1. send
// 2. receive
// 3. send
// 4. receive
TEST_F(DNSClientTest, sendReceiveTwice) {
    runSendReceiveTest(false, false);
    runSendReceiveTest(false, false);
    EXPECT_EQ(2, received_);
}

// Verify that it is possible to use the DNSClient instance to perform the
// following  sequence of message exchanges:
// 1. send
// 2. send
// 3. receive
// 4. receive
// @todo  THIS Test does not function. The method runSendReceive only
// schedules one "server" receive.  In other words only one request is
// listened for and then received. Once it is received, the operator()
// method calls stop() on the io_service, which causes the second receive
// to be cancelled.  It is also unclear, what the asio layer does with a
// second receive on the same socket.
TEST_F(DNSClientTest, DISABLED_concurrentSendReceive) {
    runSendReceiveTest(false, true);
}

} // End of anonymous namespace
