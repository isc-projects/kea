// Copyright (C) 2014-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file d2_upd_unittest.cc Unit tests for D2ClientMgr UDP communications.
/// Note these tests are not intended to verify the actual send and receive
/// across UDP sockets.  This level of testing is done in libdhcp-ddns.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/d2_client_mgr.h>
#include <exceptions/exceptions.h>
#include <util/ready_check.h>

#include <gtest/gtest.h>

#include <functional>
#include <sys/select.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc;
namespace ph = std::placeholders;

namespace {

class D2ClientMgrTestSendHandler : public D2ClientMgr {
public:
    /// @brief Constructor
    D2ClientMgrTestSendHandler() : simulate_send_failure_(false), callback_count_(0) {
    }

    /// @brief Overrides base class completion callback.
    ///
    /// This method will be invoked each time a send completes. It allows
    /// intervention prior to calling the production implementation in the
    /// base.  If simulate_send_failure_ is true, the base call impl will
    /// be called with an error status, otherwise it will be called with
    /// the result parameter given.
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

    /// @brief If true simulates a send which completed with a failed status.
    bool simulate_send_failure_;

    /// @brief Tracks the number times the completion handler is called.
    int callback_count_;

    /// Expose restricted members.
    using D2ClientMgr::getSelectFd;
};

/// @brief Test fixture for exercising D2ClientMgr send management
/// services.  It inherits from D2ClientMgr to allow overriding various
/// methods and accessing otherwise restricted member.  In particular it
/// overrides the NameChangeSender completion completion callback, allowing
/// the injection of send errors.
class D2ClientMgrTest : public ::testing::Test {
public:
    boost::shared_ptr<D2ClientMgrTestSendHandler> handle_;

    /// @brief If true causes an exception throw in the client error handler.
    bool error_handler_throw_;

    /// @brief Tracks the number of times the client error handler was called.
    int error_handler_count_;

    /// @brief Constructor
    D2ClientMgrTest() : handle_(new D2ClientMgrTestSendHandler()),
                        error_handler_throw_(false),
                        error_handler_count_(0) {
    }

    /// @brief virtual Destructor
    virtual ~D2ClientMgrTest() {
        handle_->stop();
        handle_->stopSender();
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

        IOAddress server_ip(server_address);
        IOAddress sender_ip(server_ip.isV4() ? D2ClientConfig::DFT_V4_SENDER_IP :
                            D2ClientConfig::DFT_V6_SENDER_IP);

        ASSERT_NO_THROW(new_cfg.reset(new D2ClientConfig(true, server_ip, server_port,
                                                         sender_ip, D2ClientConfig::DFT_SENDER_PORT,
                                                         D2ClientConfig::DFT_MAX_QUEUE_SIZE,
                                                         protocol, dhcp_ddns::FMT_JSON)));

        ASSERT_NO_THROW(handle_->setD2ClientConfig(new_cfg));
        ASSERT_TRUE(handle_->ddnsEnabled());
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

        // cppcheck-suppress redundantAssignment
        int select_fd = -1;
        ASSERT_NO_THROW(
            // cppcheck-suppress redundantAssignment
            select_fd = handle_->getSelectFd()
        );

        int result = util::selectCheck(select_fd);

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
        return (std::bind(&D2ClientMgrTest::error_handler, this, ph::_1, ph::_2));
    }

    /// @brief Constructs a NameChangeRequest message from a fixed JSON string.
    dhcp_ddns::NameChangeRequestPtr buildTestNcr() {
        // Build an NCR from json string.
        const char* ncr_str =
            "{"
            " \"change-type\" : 0 , "
            " \"forward-change\" : true , "
            " \"reverse-change\" : false , "
            " \"fqdn\" : \"myhost.example.com.\" , "
            " \"ip-address\" : \"192.168.2.1\" , "
            " \"dhcid\" : \"010203040A7F8E3D\" , "
            " \"lease-expires-on\" : \"20140121132405\" , "
            " \"lease-length\" : 1300, "
            " \"conflict-resolution-mode\" : \"check-with-dhcid\""
            "}";

        return (dhcp_ddns::NameChangeRequest::fromJSON(ncr_str));
    }
};

/// @brief Checks that D2ClientMgr disable and enable a UDP sender.
TEST_F(D2ClientMgrTest, udpSenderEnableDisable) {
    // Verify DDNS is disabled by default.
    ASSERT_FALSE(handle_->ddnsEnabled());

    // Verify we are not in send mode.
    ASSERT_FALSE(handle_->amSending());

    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    enableDdns("127.0.0.1", 530001, dhcp_ddns::NCR_UDP);
    ASSERT_FALSE(handle_->amSending());

    ASSERT_NO_THROW(handle_->startSender(getErrorHandler()));
    ASSERT_TRUE(handle_->amSending());

    // Verify that we take sender out of send mode.
    ASSERT_NO_THROW(handle_->stopSender());
    ASSERT_FALSE(handle_->amSending());
}

/// @brief Checks D2ClientMgr queuing methods with a UDP sender.
TEST_F(D2ClientMgrTest, udpSenderQueing) {
    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    enableDdns("127.0.0.1", 530001, dhcp_ddns::NCR_UDP);
    ASSERT_FALSE(handle_->amSending());

    // Queue should be empty.
    EXPECT_EQ(0, handle_->getQueueSize());

    // Trying to peek past the end of the queue should throw.
    EXPECT_THROW(handle_->peekAt(1), dhcp_ddns::NcrSenderError);

    // Trying to send a NCR when not in send mode should fail.
    dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
    EXPECT_THROW(handle_->sendRequest(ncr), D2ClientError);

    // Place sender in send mode.
    ASSERT_NO_THROW(handle_->startSender(getErrorHandler()));
    ASSERT_TRUE(handle_->amSending());

    // Send should succeed now.
    ASSERT_NO_THROW(handle_->sendRequest(ncr));

    // Queue should have 1 entry.
    EXPECT_EQ(1, handle_->getQueueSize());

    // Attempt to fetch the entry we just queued.
    dhcp_ddns::NameChangeRequestPtr ncr2;
    ASSERT_NO_THROW(ncr2 = handle_->peekAt(0));

    // Verify what we queued matches what we fetched.
    EXPECT_TRUE(*ncr == *ncr2);

    // Clearing the queue while in send mode should fail.
    ASSERT_THROW(handle_->clearQueue(), dhcp_ddns::NcrSenderError);

    // We should still have 1 in the queue.
    EXPECT_EQ(1, handle_->getQueueSize());

    // Get out of send mode.
    ASSERT_NO_THROW(handle_->stopSender());
    ASSERT_FALSE(handle_->amSending());

    // Clear queue should succeed now.
    ASSERT_NO_THROW(handle_->clearQueue());
    EXPECT_EQ(0, handle_->getQueueSize());
}

/// @brief Checks that D2ClientMgr can send with a UDP sender and
/// a private IOService.
TEST_F(D2ClientMgrTest, udpSend) {
    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    enableDdns("127.0.0.1", 530001, dhcp_ddns::NCR_UDP);

    // Trying to fetch the select-fd when not sending should fail.
    ASSERT_THROW(handle_->getSelectFd(), D2ClientError);

    // Place sender in send mode.
    ASSERT_NO_THROW(handle_->startSender(getErrorHandler()));

    // select_fd should evaluate to NOT ready to read.
    selectCheck(false);

    // Build a test request and send it.
    dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
    ASSERT_NO_THROW(handle_->sendRequest(ncr));

    // select_fd should evaluate to ready to read.
    selectCheck(true);

    // Call service handler.
    handle_->runReadyIO();

    // select_fd should evaluate to not ready to read.
    selectCheck(false);
}

/// @brief Checks that D2ClientMgr can send with a UDP sender and
/// an external IOService.
TEST_F(D2ClientMgrTest, udpSendExternalIOService) {
    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    enableDdns("127.0.0.1", 53001, dhcp_ddns::NCR_UDP);

    // Place sender in send mode using an external IO service.
    asiolink::IOServicePtr io_service(new IOService());
    ASSERT_NO_THROW(handle_->startSender(getErrorHandler(), io_service));

    // select_fd should evaluate to NOT ready to read.
    selectCheck(false);

    // Build a test request and send it.
    dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
    ASSERT_NO_THROW(handle_->sendRequest(ncr));

    // select_fd should evaluate to ready to read.
    selectCheck(true);

    // Call service handler.
    handle_->runReadyIO();

    // select_fd should evaluate to not ready to read.
    selectCheck(false);

    // Explicitly stop the sender. This ensures the sender's
    // ASIO socket is closed prior to the local io_service
    // instance goes out of scope.
    ASSERT_NO_THROW(handle_->stopSender());
}

/// @brief Checks that D2ClientMgr can send with a UDP sender and
/// an external IOService.
TEST_F(D2ClientMgrTest, udpSendExternalIOService6) {
    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    enableDdns("::1", 53001, dhcp_ddns::NCR_UDP);

    // Place sender in send mode using an external IO service.
    asiolink::IOServicePtr io_service(new IOService());
    ASSERT_NO_THROW(handle_->startSender(getErrorHandler(), io_service));

    // select_fd should evaluate to NOT ready to read.
    selectCheck(false);

    // Build a test request and send it.
    dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
    ASSERT_NO_THROW(handle_->sendRequest(ncr));

    // select_fd should evaluate to ready to read.
    selectCheck(true);

    // Call service handler.
    handle_->runReadyIO();

    // select_fd should evaluate to not ready to read.
    selectCheck(false);

    // Explicitly stop the sender. This ensures the sender's
    // ASIO socket is closed prior to the local io_service
    // instance goes out of scope.
    ASSERT_NO_THROW(handle_->stopSender());
}

/// @brief Checks that D2ClientMgr invokes the client error handler
/// when send errors occur.
TEST_F(D2ClientMgrTest, udpSendErrorHandler) {
    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    // Place sender in send mode.
    enableDdns("127.0.0.1", 530001, dhcp_ddns::NCR_UDP);
    ASSERT_NO_THROW(handle_->startSender(getErrorHandler()));

    // Simulate a failed response in the send call back. This should
    // cause the error handler to get invoked.
    handle_->simulate_send_failure_ = true;

    // Verify error count is zero.
    ASSERT_EQ(0, error_handler_count_);

    // Send a test request.
    dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
    ASSERT_NO_THROW(handle_->sendRequest(ncr));

    // Call the ready handler. This should complete the message with an error.
    ASSERT_NO_THROW(handle_->runReadyIO());

    // If we executed error handler properly, the error count should one.
    ASSERT_EQ(1, error_handler_count_);
}

/// @brief Checks that client error handler exceptions are handled gracefully.
TEST_F(D2ClientMgrTest, udpSendErrorHandlerThrow) {
    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    // Place sender in send mode.
    enableDdns("127.0.0.1", 530001, dhcp_ddns::NCR_UDP);
    ASSERT_NO_THROW(handle_->startSender(getErrorHandler()));

    // Simulate a failed response in the send call back and
    // force a throw in the error handler.
    handle_->simulate_send_failure_ = true;
    error_handler_throw_ = true;

    // Verify error count is zero.
    ASSERT_EQ(0, error_handler_count_);

    // Send a test request.
    dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
    ASSERT_NO_THROW(handle_->sendRequest(ncr));

    // Call the ready handler. This should complete the message with an error.
    // The handler should throw but the exception should not escape.
    ASSERT_NO_THROW(handle_->runReadyIO());

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
    ASSERT_NO_THROW(handle_->startSender(getErrorHandler()));

    // Queue three messages.
    for (unsigned i = 0; i < 3; ++i) {
        dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
        ASSERT_NO_THROW(handle_->sendRequest(ncr));
    }

    // Make sure queue count is correct.
    EXPECT_EQ(3, handle_->getQueueSize());

    // select_fd should evaluate to ready to read.
    selectCheck(true);

    // Calling receive should complete the first message and start the second.
    IfaceMgr::instance().receive4(0, 0);

    // Verify the callback handler was invoked, no errors counted.
    EXPECT_EQ(2, handle_->getQueueSize());
    ASSERT_EQ(1, handle_->callback_count_);
    ASSERT_EQ(0, error_handler_count_);

    // Stop the sender.  This should complete the second message but leave
    // the third in the queue.
    ASSERT_NO_THROW(handle_->stopSender());
    EXPECT_EQ(1, handle_->getQueueSize());
    ASSERT_EQ(2, handle_->callback_count_);
    ASSERT_EQ(0, error_handler_count_);

    // Calling receive again should have no affect.
    IfaceMgr::instance().receive4(0, 0);
    EXPECT_EQ(1, handle_->getQueueSize());
    ASSERT_EQ(2, handle_->callback_count_);
    ASSERT_EQ(0, error_handler_count_);
}

/// @brief Checks that D2ClientMgr suspendUpdates works properly.
TEST_F(D2ClientMgrTest, udpSuspendUpdates) {
    // Enable DDNS with server at 127.0.0.1/prot 53001 via UDP.
    // Place sender in send mode.
    enableDdns("127.0.0.1", 530001, dhcp_ddns::NCR_UDP);
    ASSERT_NO_THROW(handle_->startSender(getErrorHandler()));

    // Send a test request.
    for (unsigned i = 0; i < 3; ++i) {
        dhcp_ddns::NameChangeRequestPtr ncr = buildTestNcr();
        ASSERT_NO_THROW(handle_->sendRequest(ncr));
    }
    ASSERT_EQ(3, handle_->getQueueSize());

    // Call the ready handler. This should complete the first message
    // and initiate sending the second message.
    ASSERT_NO_THROW(handle_->runReadyIO());

    // Queue count should have gone down by 1.
    ASSERT_EQ(2, handle_->getQueueSize());

    // Suspend updates. This should disable updates and stop the sender.
    ASSERT_NO_THROW(handle_->suspendUpdates());

    EXPECT_FALSE(handle_->ddnsEnabled());
    EXPECT_FALSE(handle_->amSending());

    // Stopping the sender should have completed the second message's
    // in-progress send, so queue size should be 1.
    ASSERT_EQ(1, handle_->getQueueSize());
}

/// @brief Tests that invokeErrorHandler does not fail if there is no handler.
TEST_F(D2ClientMgrTest, missingErrorHandler) {
    // Ensure we aren't in send mode.
    ASSERT_FALSE(handle_->ddnsEnabled());
    ASSERT_FALSE(handle_->amSending());

    // There is no error handler at this point, so invoking should not throw.
    dhcp_ddns::NameChangeRequestPtr ncr;
    ASSERT_NO_THROW(handle_->invokeClientErrorHandler(dhcp_ddns::NameChangeSender::ERROR,
                                                      ncr));

    // Verify we didn't invoke the error handler, error count is zero.
    ASSERT_EQ(0, error_handler_count_);
}

} // end of anonymous namespace
