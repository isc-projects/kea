// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
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

/// @file d2_upd_unittest.cc Unit tests for D2ClientMgr UDP communications.
/// Note these tests are not intended to verify the actual send and receive
/// across UDP sockets.  This level of testing is done in libdhcp-ddns.

#include <boost/asio.hpp>
#include <asiolink/io_service.h>
#include <config.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/d2_client_mgr.h>
#include <exceptions/exceptions.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <gtest/gtest.h>

#include <sys/select.h>

using namespace std;
using namespace isc::dhcp;
using namespace isc;

namespace {

/// @brief Test fixture for excerising D2ClientMgr send management
/// services.  It inherents from D2ClientMgr to allow overriding various
/// methods and accessing otherwise restricted member.  In particular it
/// overrides the NameChangeSender completion completion callback, allowing
/// the injection of send errors.
class D2ClientMgrTest : public D2ClientMgr, public ::testing::Test {
public:
    /// @brief If true simulates a send which completed with a failed status.
    bool simulate_send_failure_;
    /// @brief If true causes an exception throw in the client error handler.
    bool error_handler_throw_;
    /// @brief Tracks the number times the completion handler is called.
    int callback_count_;
    /// @brief Tracks the number of times the client error handler was called.
    int error_handler_count_;

    /// @brief Constructor
    D2ClientMgrTest() : simulate_send_failure_(false),
                       error_handler_throw_(false),
                       callback_count_(0), error_handler_count_(0) {
    }

    /// @brief virtual Destructor
    virtual ~D2ClientMgrTest(){
    }

    /// @brief Updates the D2ClientMgr's configuration to DDNS enabled.
    ///
    /// @param server_address IP address of kea-dhcp-ddns.
    /// @param server_port IP port number of kea-dhcp-ddns.
    /// @param protocol NCR protocol to use. (Currently only UDP is
    /// supported).
    void enableDdns(const std::string& server_address,
                    const size_t server_port,
                    const dhcp_ddns::NameChangeProtocol protocol) {
        // Update the configuration with one that is enabled.
        D2ClientConfigPtr new_cfg;

        isc::asiolink::IOAddress server_ip(server_address);
        isc::asiolink::IOAddress sender_ip(server_ip.isV4() ?
                                           D2ClientConfig::DFT_V4_SENDER_IP :
                                           D2ClientConfig::DFT_V6_SENDER_IP);

        ASSERT_NO_THROW(new_cfg.reset(new D2ClientConfig(true,
                                  server_ip, server_port,
                                  sender_ip, D2ClientConfig::DFT_SENDER_PORT,
                                  D2ClientConfig::DFT_MAX_QUEUE_SIZE,
                                  protocol, dhcp_ddns::FMT_JSON,
                                  true, true, true, true,
                                  "myhost", ".example.com.")));

        ASSERT_NO_THROW(setD2ClientConfig(new_cfg));
        ASSERT_TRUE(ddnsEnabled());
    }

    /// @brief Checks sender's select-fd against an expected state of readiness.
    ///
    /// Uses select() to determine if the sender's select_fd is marked as
    /// ready to read, and compares this against the expected state.  The
    /// select function is called with a timeout of 0.0 (non blocking).
    ///
    /// @param expect_ready Expected state of readiness (True if expecting
    /// a ready to ready result,  false if expecting otherwise).
    void selectCheck(bool expect_ready) {
        fd_set read_fds;
        int maxfd = 0;

        FD_ZERO(&read_fds);

        // cppcheck-suppress redundantAssignment
        int select_fd = -1;
        ASSERT_NO_THROW(
            // cppcheck-suppress redundantAssignment
            select_fd = getSelectFd()
        );

        FD_SET(select_fd,  &read_fds);
        maxfd = select_fd;

        struct timeval select_timeout;
        select_timeout.tv_sec = 0;
        select_timeout.tv_usec = 0;

        int result = (select(maxfd + 1, &read_fds, NULL, NULL,
                      &select_timeout));

        if (result < 0) {
            const char *errstr = strerror(errno);
            FAIL() << "select failed :" << errstr;
        }

        if (expect_ready) {
            ASSERT_TRUE(result > 0);
        } else {
            ASSERT_TRUE(result == 0);
        }
    }

    /// @brief Overrides base class completion callback.
    ///
    /// This method will be invoked each time a send completes. It allows
    /// intervention prior to calling the production implemenation in the
    /// base.  If simulate_send_failure_ is true, the base call impl will
    /// be called with an error status, otherwise it will be called with
    /// the result paramater given.
    ///
    /// @param result Result code of the send operation.
    /// @param ncr NameChangeRequest which failed to send.
    virtual void operator()(const dhcp_ddns::NameChangeSender::Result result,
                            dhcp_ddns::NameChangeRequestPtr& ncr) {
        ++callback_count_;
        if (simulate_send_failure_) {
            simulate_send_failure_ = false;
            D2ClientMgr::operator()(dhcp_ddns::NameChangeSender::ERROR, ncr);
        } else {
            D2ClientMgr::operator()(result, ncr);
        }
    }

    /// @brief Serves as the "application level" client error handler.
    ///
    /// This method is passed into calls to startSender as the client error
    /// handler.  It should be invoked whenever the completion callback is
    /// passed a result other than SUCCESS.  If error_handler_throw_
    /// is true it will throw an exception.
    ///
    /// @param result unused - Result code of the send operation.
    /// @param ncr unused -NameChangeRequest which failed to send.
    void error_handler(const dhcp_ddns::NameChangeSender::Result /*result*/,
                       dhcp_ddns::NameChangeRequestPtr& /*ncr*/) {
        if (error_handler_throw_) {
            error_handler_throw_ = false;
            isc_throw(isc::InvalidOperation, "Simulated client handler throw");
        }

        ++error_handler_count_;
    }

    /// @brief Returns D2ClientErroHandler bound to this::error_handler_.
    D2ClientErrorHandler getErrorHandler() {
        return (boost::bind(&D2ClientMgrTest::error_handler, this, _1, _2));
    }

    /// @brief Contructs a NameChangeRequest message from a fixed JSON string.
    dhcp_ddns::NameChangeRequestPtr buildTestNcr() {
        // Build an NCR from json string.
        const char* ncr_str =
            "{"
            " \"change_type\" : 0 , "
            " \"forward_change\" : true , "
            " \"reverse_change\" : false , "
            " \"fqdn\" : \"myhost.example.com.\" , "
            " \"ip_address\" : \"192.168.2.1\" , "
            " \"dhcid\" : \"010203040A7F8E3D\" , "
            " \"lease_expires_on\" : \"20140121132405\" , "
            " \"lease_length\" : 1300 "
            "}";

        return (dhcp_ddns::NameChangeRequest::fromJSON(ncr_str));
    }

    /// Expose restricted members.
    using D2ClientMgr::getSelectFd;
};


/// @brief Checks that D2ClientMgr disable and enable a UDP sender.
TEST_F(D2ClientMgrTest, udpSenderEnableDisable) {
    // Verify DDNS is disabled by default.
    ASSERT_FALSE(ddnsEnabled());

    // Verify we are not in send mode.
    ASSERT_FALSE(amSending());

    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    enableDdns("127.0.0.1", 530001, dhcp_ddns::NCR_UDP);
    ASSERT_FALSE(amSending());

    ASSERT_NO_THROW(startSender(getErrorHandler()));
    ASSERT_TRUE(amSending());

    // Verify that we take sender out of send mode.
    ASSERT_NO_THROW(stopSender());
    ASSERT_FALSE(amSending());
}

/// @brief Checks D2ClientMgr queuing methods with a UDP sender.
TEST_F(D2ClientMgrTest, udpSenderQueing) {
    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    enableDdns("127.0.0.1", 530001, dhcp_ddns::NCR_UDP);
    ASSERT_FALSE(amSending());

    // Queue should be empty.
    EXPECT_EQ(0, getQueueSize());

    // Trying to peek past the end of the queue should throw.
    EXPECT_THROW(peekAt(1), dhcp_ddns::NcrSenderError);

    // Trying to send a NCR when not in send mode should fail.
    dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
    EXPECT_THROW(sendRequest(ncr), D2ClientError);

    // Place sender in send mode.
    ASSERT_NO_THROW(startSender(getErrorHandler()));
    ASSERT_TRUE(amSending());

    // Send should succeed now.
    ASSERT_NO_THROW(sendRequest(ncr));

    // Queue should have 1 entry.
    EXPECT_EQ(1, getQueueSize());

    // Attempt to fetch the entry we just queued.
    dhcp_ddns::NameChangeRequestPtr ncr2;
    ASSERT_NO_THROW(ncr2 = peekAt(0));

    // Verify what we queued matches what we fetched.
    EXPECT_TRUE(*ncr == *ncr2);

    // Clearing the queue while in send mode should fail.
    ASSERT_THROW(clearQueue(), dhcp_ddns::NcrSenderError);

    // We should still have 1 in the queue.
    EXPECT_EQ(1, getQueueSize());

    // Get out of send mode.
    ASSERT_NO_THROW(stopSender());
    ASSERT_FALSE(amSending());

    // Clear queue should succeed now.
    ASSERT_NO_THROW(clearQueue());
    EXPECT_EQ(0, getQueueSize());
}

/// @brief Checks that D2ClientMgr can send with a UDP sender and
/// a private IOService.
TEST_F(D2ClientMgrTest, udpSend) {
    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    enableDdns("127.0.0.1", 530001, dhcp_ddns::NCR_UDP);

    // Trying to fetch the select-fd when not sending should fail.
    ASSERT_THROW(getSelectFd(), D2ClientError);

    // Place sender in send mode.
    ASSERT_NO_THROW(startSender(getErrorHandler()));

    // select_fd should evaluate to NOT ready to read.
    selectCheck(false);

    // Build a test request and send it.
    dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
    ASSERT_NO_THROW(sendRequest(ncr));

    // select_fd should evaluate to ready to read.
    selectCheck(true);

    // Call service handler.
    runReadyIO();

    // select_fd should evaluate to not ready to read.
    selectCheck(false);
}

/// @brief Checks that D2ClientMgr can send with a UDP sender and
/// an external IOService.
TEST_F(D2ClientMgrTest, udpSendExternalIOService) {
    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    enableDdns("127.0.0.1", 53001, dhcp_ddns::NCR_UDP);

    // Place sender in send mode using an external IO service.
    asiolink::IOService io_service;
    ASSERT_NO_THROW(startSender(getErrorHandler(), io_service));

    // select_fd should evaluate to NOT ready to read.
    selectCheck(false);

    // Build a test request and send it.
    dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
    ASSERT_NO_THROW(sendRequest(ncr));

    // select_fd should evaluate to ready to read.
    selectCheck(true);

    // Call service handler.
    runReadyIO();

    // select_fd should evaluate to not ready to read.
    selectCheck(false);

    // Explicitly stop the sender. This ensures the sender's
    // ASIO socket is closed prior to the local io_service
    // instance goes out of scope.
    ASSERT_NO_THROW(stopSender());
}

/// @brief Checks that D2ClientMgr can send with a UDP sender and
/// an external IOService.
TEST_F(D2ClientMgrTest, udpSendExternalIOService6) {
    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    enableDdns("::1", 53001, dhcp_ddns::NCR_UDP);

    // Place sender in send mode using an external IO service.
    asiolink::IOService io_service;
    ASSERT_NO_THROW(startSender(getErrorHandler(), io_service));

    // select_fd should evaluate to NOT ready to read.
    selectCheck(false);

    // Build a test request and send it.
    dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
    ASSERT_NO_THROW(sendRequest(ncr));

    // select_fd should evaluate to ready to read.
    selectCheck(true);

    // Call service handler.
    runReadyIO();

    // select_fd should evaluate to not ready to read.
    selectCheck(false);

    // Explicitly stop the sender. This ensures the sender's
    // ASIO socket is closed prior to the local io_service
    // instance goes out of scope.
    ASSERT_NO_THROW(stopSender());
}


/// @brief Checks that D2ClientMgr invokes the client error handler
/// when send errors occur.
TEST_F(D2ClientMgrTest, udpSendErrorHandler) {
    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    // Place sender in send mode.
    enableDdns("127.0.0.1", 530001, dhcp_ddns::NCR_UDP);
    ASSERT_NO_THROW(startSender(getErrorHandler()));

    // Simulate a failed response in the send call back. This should
    // cause the error handler to get invoked.
    simulate_send_failure_ = true;

    // Verify error count is zero.
    ASSERT_EQ(0, error_handler_count_);

    // Send a test request.
    dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
    ASSERT_NO_THROW(sendRequest(ncr));

    // Call the ready handler. This should complete the message with an error.
    ASSERT_NO_THROW(runReadyIO());

    // If we executed error handler properly, the error count should one.
    ASSERT_EQ(1, error_handler_count_);
}


/// @brief Checks that client error handler exceptions are handled gracefully.
TEST_F(D2ClientMgrTest, udpSendErrorHandlerThrow) {
    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    // Place sender in send mode.
    enableDdns("127.0.0.1", 530001, dhcp_ddns::NCR_UDP);
    ASSERT_NO_THROW(startSender(getErrorHandler()));

    // Simulate a failed response in the send call back and
    // force a throw in the error handler.
    simulate_send_failure_ = true;
    error_handler_throw_ = true;

    // Verify error count is zero.
    ASSERT_EQ(0, error_handler_count_);

    // Send a test request.
    dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
    ASSERT_NO_THROW(sendRequest(ncr));

    // Call the ready handler. This should complete the message with an error.
    // The handler should throw but the exception should not escape.
    ASSERT_NO_THROW(runReadyIO());

    // If throw flag is false, then we were in the error handler should
    // have thrown.
    ASSERT_FALSE(error_handler_throw_);

    // If error count is still zero, then we did throw.
    ASSERT_EQ(0, error_handler_count_);
}

/// @brief Tests that D2ClientMgr registers and unregisters with IfaceMgr.
TEST_F(D2ClientMgrTest, ifaceRegister) {
    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    enableDdns("127.0.0.1", 530001, dhcp_ddns::NCR_UDP);

    // Place sender in send mode.
    ASSERT_NO_THROW(startSender(getErrorHandler()));

    // Queue three messages.
    for (unsigned i = 0; i < 3; ++i) {
        dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
        ASSERT_NO_THROW(sendRequest(ncr));
    }

    // Make sure queue count is correct.
    EXPECT_EQ(3, getQueueSize());

    // select_fd should evaluate to ready to read.
    selectCheck(true);

    // Calling receive should complete the first message and start the second.
    IfaceMgr::instance().receive4(0, 0);

    // Verify the callback hander was invoked, no errors counted.
    EXPECT_EQ(2, getQueueSize());
    ASSERT_EQ(1, callback_count_);
    ASSERT_EQ(0, error_handler_count_);

    // Stop the sender.  This should complete the second message but leave
    // the third in the queue.
    ASSERT_NO_THROW(stopSender());
    EXPECT_EQ(1, getQueueSize());
    ASSERT_EQ(2, callback_count_);
    ASSERT_EQ(0, error_handler_count_);

    // Calling receive again should have no affect.
    IfaceMgr::instance().receive4(0, 0);
    EXPECT_EQ(1, getQueueSize());
    ASSERT_EQ(2, callback_count_);
    ASSERT_EQ(0, error_handler_count_);
}

/// @brief Checks that D2ClientMgr suspendUpdates works properly.
TEST_F(D2ClientMgrTest, udpSuspendUpdates) {
    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    // Place sender in send mode.
    enableDdns("127.0.0.1", 530001, dhcp_ddns::NCR_UDP);
    ASSERT_NO_THROW(startSender(getErrorHandler()));

    // Send a test request.
    for (unsigned i = 0; i < 3; ++i) {
        dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
        ASSERT_NO_THROW(sendRequest(ncr));
    }
    ASSERT_EQ(3, getQueueSize());

    // Call the ready handler. This should complete the first message
    // and initiate sending the second message.
    ASSERT_NO_THROW(runReadyIO());

    // Queue count should have gone down by 1.
    ASSERT_EQ(2, getQueueSize());

    // Suspend updates. This should disable updates and stop the sender.
    ASSERT_NO_THROW(suspendUpdates());

    EXPECT_FALSE(ddnsEnabled());
    EXPECT_FALSE(amSending());

    // Stopping the sender should have completed the second message's
    // in-progess send, so queue size should be 1.
    ASSERT_EQ(1, getQueueSize());
}

/// @brief Tests that invokeErrorHandler does not fail if there is no handler.
TEST_F(D2ClientMgrTest, missingErrorHandler) {
    // Ensure we aren't in send mode.
    ASSERT_FALSE(ddnsEnabled());
    ASSERT_FALSE(amSending());

    // There is no error handler at this point, so invoking should not throw.
    dhcp_ddns::NameChangeRequestPtr ncr;
    ASSERT_NO_THROW(invokeClientErrorHandler(dhcp_ddns::NameChangeSender::ERROR,
                                             ncr));

    // Verify we didn't invoke the error handler, error count is zero.
    ASSERT_EQ(0, error_handler_count_);
}

} // end of anonymous namespace
