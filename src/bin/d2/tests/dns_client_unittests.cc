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
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::asiodns;
using namespace isc::d2;

using namespace isc;
using namespace isc::dns;

namespace {

const char* TEST_ADDRESS = "127.0.0.1";
const uint16_t TEST_PORT = 5301;

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
    IOFetch::Result result_;

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
          result_(IOFetch::SUCCESS) {
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
    // @param result An error code returned by an IO.
    virtual void operator()(IOFetch::Result result) {
        result_ = result;
        service_.stop();
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
        EXPECT_NO_THROW(dns_client.reset(new DNSClient(response_, this)));

        IOService io_service;
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
        // value of result_ with the TIME_OUT error code.
        EXPECT_EQ(IOFetch::TIME_OUT, result_);
    }
};

TEST_F(DNSClientTest, constructor) {
    runConstructorTest();
}

TEST_F(DNSClientTest, timeout) {
    runSendNoReceiveTest();
}

} // End of anonymous namespace
