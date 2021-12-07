// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service.h>
#include <d2/simple_add.h>
#include <d2srv/d2_cfg_mgr.h>
#include <d2srv/testutils/nc_test_utils.h>
#include <dns/messagerenderer.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::d2;
using namespace isc::util;

namespace {

/// @brief Test class derived from SimpleAddTransaction to provide visibility
// to protected methods.
class SimpleAddStub : public SimpleAddTransaction {
public:
    SimpleAddStub(asiolink::IOServicePtr& io_service,
                  dhcp_ddns::NameChangeRequestPtr& ncr,
                  DdnsDomainPtr& forward_domain,
                  DdnsDomainPtr& reverse_domain,
                  D2CfgMgrPtr& cfg_mgr)
        : SimpleAddTransaction(io_service, ncr, forward_domain, reverse_domain,
                               cfg_mgr),
          simulate_send_exception_(false),
          simulate_build_request_exception_(false) {
    }

    virtual ~SimpleAddStub() {
    }

    /// @brief Simulates sending update requests to the DNS server
    ///
    /// This method simulates the initiation of an asynchronous send of
    /// a DNS update request. It overrides the actual sendUpdate method in
    /// the base class, thus avoiding an actual send, yet still increments
    /// the update attempt count and posts a next event of NOP_EVT.
    ///
    /// It will also simulate an exception-based failure of sendUpdate, if
    /// the simulate_send_exception_ flag is true.
    ///
    /// @param comment Parameter is unused, but present in base class method.
    ///
    virtual void sendUpdate(const std::string& /*comment*/) {
        if (simulate_send_exception_) {
            // Make the flag a one-shot by resetting it.
            simulate_send_exception_ = false;
            // Transition to failed.
            transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
            return;
        }

        // Update send attempt count and post a NOP_EVT.
        setUpdateAttempts(getUpdateAttempts() + 1);
        postNextEvent(StateModel::NOP_EVT);
    }

    /// @brief Prepares the initial D2UpdateMessage
    ///
    /// This method overrides the NameChangeTransaction implementation to
    /// provide the ability to simulate an exception throw in the build
    /// request logic.
    /// If the one-shot flag, simulate_build_request_exception_ is true,
    /// this method will throw an exception, otherwise it will invoke the
    /// base class method, providing normal functionality.
    ///
    /// For parameter description see the NameChangeTransaction implementation.
    virtual D2UpdateMessagePtr prepNewRequest(DdnsDomainPtr domain) {
        if (simulate_build_request_exception_) {
            simulate_build_request_exception_ = false;
            isc_throw (SimpleAddTransactionError,
                       "Simulated build requests exception");
        }

        return (NameChangeTransaction::prepNewRequest(domain));
    }

    /// @brief Simulates receiving a response
    ///
    /// This method simulates the completion of a DNSClient send.  This allows
    /// the state handler logic devoted to dealing with IO completion to be
    /// fully exercised without requiring any actual IO.  The two primary
    /// pieces of information gleaned from IO completion are the DNSClient
    /// status which indicates whether or not the IO exchange was successful
    /// and the rcode, which indicates the server's reaction to the request.
    ///
    /// This method updates the transaction's DNS status value to that of the
    /// given parameter, and then constructs and DNS update response message
    /// with the given rcode value.  To complete the simulation it then posts
    /// a next event of IO_COMPLETED_EVT.
    ///
    /// @param status simulated DNSClient status
    /// @param rcode  simulated server response code
    void fakeResponse(const DNSClient::Status& status,
                      const dns::Rcode& rcode) {
        // Set the DNS update status.  This is normally set in
        // DNSClient IO completion handler.
        setDnsUpdateStatus(status);

        // Construct an empty message with the given Rcode.
        D2UpdateMessagePtr msg(new D2UpdateMessage(D2UpdateMessage::OUTBOUND));
        msg->setRcode(rcode);

        // Set the update response to the message.
        setDnsUpdateResponse(msg);

        // Post the IO completion event.
        postNextEvent(NameChangeTransaction::IO_COMPLETED_EVT);
    }

    /// @brief Selects the first forward server.
    /// Some state handlers require a server to have been selected.
    /// This selects a server without going through the state
    /// transition(s) to do so.
    bool selectFwdServer() {
        if (getForwardDomain()) {
            initServerSelection(getForwardDomain());
            selectNextServer();
            return (getCurrentServer().get() != 0);
        }

        return (false);
    }

    /// @brief Selects the first reverse server.
    /// Some state handlers require a server to have been selected.
    /// This selects a server without going through the state
    /// transition(s) to do so.
    bool selectRevServer() {
        if (getReverseDomain()) {
            initServerSelection(getReverseDomain());
            selectNextServer();
            return (getCurrentServer().get() != 0);
        }

        return (false);
    }

    /// @brief One-shot flag which will simulate sendUpdate failure if true.
    bool simulate_send_exception_;

    /// @brief One-shot flag which will simulate an exception when sendUpdate
    /// failure if true.
    bool simulate_build_request_exception_;

    using StateModel::postNextEvent;
    using StateModel::setState;
    using StateModel::initDictionaries;
    using SimpleAddTransaction::defineEvents;
    using SimpleAddTransaction::verifyEvents;
    using SimpleAddTransaction::defineStates;
    using SimpleAddTransaction::verifyStates;
    using SimpleAddTransaction::readyHandler;
    using SimpleAddTransaction::selectingFwdServerHandler;
    using SimpleAddTransaction::getCurrentServer;
    using SimpleAddTransaction::setDnsUpdateStatus;
    using SimpleAddTransaction::replacingFwdAddrsHandler;
    using SimpleAddTransaction::selectingRevServerHandler;
    using SimpleAddTransaction::replacingRevPtrsHandler;
    using SimpleAddTransaction::processAddOkHandler;
    using SimpleAddTransaction::processAddFailedHandler;
    using SimpleAddTransaction::buildReplaceFwdAddressRequest;
    using SimpleAddTransaction::buildReplaceRevPtrsRequest;
};

typedef boost::shared_ptr<SimpleAddStub> SimpleAddStubPtr;

/// @brief Test fixture for testing SimpleAddTransaction
///
/// Note this class uses SimpleAddStub class to exercise non-public
/// aspects of SimpleAddTransaction.
class SimpleAddTransactionTest : public TransactionTest {
public:

    SimpleAddTransactionTest() {
    }

    virtual ~SimpleAddTransactionTest() {
    }

    /// @brief Creates a transaction which requests an IPv4 DNS update.
    ///
    /// The transaction is constructed around a predefined (i.e. "canned")
    /// IPv4 NameChangeRequest. The request has both forward and reverse DNS
    /// changes requested.  Based upon the change mask, the transaction
    /// will have either the forward, reverse, or both domains populated.
    ///
    /// @param change_mask determines which change directions are requested
    SimpleAddStubPtr makeTransaction4(int change_mask = FWD_AND_REV_CHG) {
        // Creates IPv4 remove request, forward, and reverse domains.
        setupForIPv4Transaction(dhcp_ddns::CHG_ADD, change_mask);

        // Now create the test transaction as would occur in update manager.
        return (SimpleAddStubPtr(new SimpleAddStub(io_service_, ncr_,
                                               forward_domain_,
                                               reverse_domain_, cfg_mgr_)));
    }

    /// @brief Creates a transaction which requests an IPv6 DNS update.
    ///
    /// The transaction is constructed around a predefined (i.e. "canned")
    /// IPv6 NameChangeRequest. The request has both forward and reverse DNS
    /// changes requested.  Based upon the change mask, the transaction
    /// will have either the forward, reverse, or both domains populated.
    ///
    /// @param change_mask determines which change directions are requested
    SimpleAddStubPtr makeTransaction6(int change_mask = FWD_AND_REV_CHG) {
        // Creates IPv6 remove request, forward, and reverse domains.
        setupForIPv6Transaction(dhcp_ddns::CHG_ADD, change_mask);

        // Now create the test transaction as would occur in update manager.
        return (SimpleAddStubPtr(new SimpleAddStub(io_service_, ncr_,
                                               forward_domain_,
                                               reverse_domain_,
                                               cfg_mgr_)));
    }

    /// @brief Create a test transaction at a known point in the state model.
    ///
    /// Method prepares a new test transaction and sets its state and next
    /// event values to those given.  This makes the transaction appear to
    /// be at that point in the state model without having to transition it
    /// through prerequisite states.   It also provides the ability to set
    /// which change directions are requested: forward change only, reverse
    /// change only, or both.
    ///
    /// @param state value to set as the current state
    /// @param event value to post as the next event
    /// @param change_mask determines which change directions are requested
    /// @param family selects between an IPv4 (AF_INET) and IPv6 (AF_INET6)
    /// transaction.
    SimpleAddStubPtr prepHandlerTest(unsigned int state, unsigned int event,
                                   unsigned int change_mask = FWD_AND_REV_CHG,
                                   short family = AF_INET) {
        SimpleAddStubPtr name_add =  (family == AF_INET ?
                                    makeTransaction4(change_mask) :
                                    makeTransaction6(change_mask));
        name_add->initDictionaries();
        name_add->postNextEvent(event);
        name_add->setState(state);
        return (name_add);
    }
};

/// @brief Tests SimpleAddTransaction construction.
/// This test verifies that:
/// 1. Construction with invalid type of request
/// 2. Valid construction functions properly
TEST(SimpleAddTransaction, construction) {
    asiolink::IOServicePtr io_service(new isc::asiolink::IOService());
    D2CfgMgrPtr cfg_mgr(new D2CfgMgr());

    const char* msg_str =
        "{"
        " \"change-type\" : 1 , "
        " \"forward-change\" : true , "
        " \"reverse-change\" : true , "
        " \"fqdn\" : \"example.com.\" , "
        " \"ip-address\" : \"192.168.2.1\" , "
        " \"dhcid\" : \"0102030405060708\" , "
        " \"lease-expires-on\" : \"20130121132405\" , "
        " \"lease-length\" : 1300, "
        " \"use-conflict-resolution\" : true "
        "}";

    dhcp_ddns::NameChangeRequestPtr ncr;
    DnsServerInfoStoragePtr servers;
    DdnsDomainPtr forward_domain;
    DdnsDomainPtr reverse_domain;
    DdnsDomainPtr empty_domain;

    ASSERT_NO_THROW(ncr = dhcp_ddns::NameChangeRequest::fromJSON(msg_str));
    ASSERT_NO_THROW(forward_domain.reset(new DdnsDomain("*", servers)));
    ASSERT_NO_THROW(reverse_domain.reset(new DdnsDomain("*", servers)));

    // Verify that construction with wrong change type fails.
    EXPECT_THROW(SimpleAddTransaction(io_service, ncr,
                                    forward_domain, reverse_domain, cfg_mgr),
                                    SimpleAddTransactionError);

    // Verify that a valid construction attempt works.
    ncr->setChangeType(isc::dhcp_ddns::CHG_ADD);
    EXPECT_NO_THROW(SimpleAddTransaction(io_service, ncr,
                                       forward_domain, reverse_domain,
                                       cfg_mgr));
}

/// @brief Tests event and state dictionary construction and verification.
TEST_F(SimpleAddTransactionTest, dictionaryCheck) {
    SimpleAddStubPtr name_add;
    ASSERT_NO_THROW(name_add = makeTransaction4());
    // Verify that the event and state dictionary validation fails prior
    // dictionary construction.
    ASSERT_THROW(name_add->verifyEvents(), StateModelError);
    ASSERT_THROW(name_add->verifyStates(), StateModelError);

    // Construct both dictionaries.
    ASSERT_NO_THROW(name_add->defineEvents());
    ASSERT_NO_THROW(name_add->defineStates());

    // Verify both event and state dictionaries now pass validation.
    ASSERT_NO_THROW(name_add->verifyEvents());
    ASSERT_NO_THROW(name_add->verifyStates());
}

/// @brief Tests construction of a DNS update request for replacing a forward
/// dns entry.
TEST_F(SimpleAddTransactionTest, buildReplaceFwdAddressRequest) {
    // Create a IPv4 forward replace transaction.
    // Verify the request builds without error.
    // and then verify the request contents.
    SimpleAddStubPtr name_add;
    ASSERT_NO_THROW(name_add = makeTransaction4());
    ASSERT_NO_THROW(name_add->buildReplaceFwdAddressRequest());
    checkSimpleReplaceFwdAddressRequest(*name_add);

    // Create a IPv6 forward replace transaction.
    // Verify the request builds without error.
    // and then verify the request contents.
    ASSERT_NO_THROW(name_add = makeTransaction6());
    ASSERT_NO_THROW(name_add->buildReplaceFwdAddressRequest());
    checkSimpleReplaceFwdAddressRequest(*name_add);
}

/// @brief Tests the construction of a DNS update request for replacing a
/// reverse dns entry.
TEST_F(SimpleAddTransactionTest, buildReplaceRevPtrsRequest) {
    // Create a IPv4 reverse replace transaction.
    // Verify the request builds without error.
    // and then verify the request contents.
    SimpleAddStubPtr name_add;
    ASSERT_NO_THROW(name_add = makeTransaction4());
    ASSERT_NO_THROW(name_add->buildReplaceRevPtrsRequest());
    checkReplaceRevPtrsRequest(*name_add);

    // Create a IPv6 reverse replace transaction.
    // Verify the request builds without error.
    // and then verify the request contents.
    ASSERT_NO_THROW(name_add = makeTransaction6());
    ASSERT_NO_THROW(name_add->buildReplaceRevPtrsRequest());
    checkReplaceRevPtrsRequest(*name_add);
}

// Tests the readyHandler functionality.
// It verifies behavior for the following scenarios:
//
// 1. Posted event is START_EVT and request includes only a forward change
// 2. Posted event is START_EVT and request includes both a forward and a
// reverse change
// 3. Posted event is START_EVT and request includes only a reverse change
// 4. Posted event is invalid
//
TEST_F(SimpleAddTransactionTest, readyHandler) {
    SimpleAddStubPtr name_add;

    // Create a transaction which includes only a forward change.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(NameChangeTransaction::READY_ST,
                                   StateModel::START_EVT, FORWARD_CHG)
    );

    // Run readyHandler.
    EXPECT_NO_THROW(name_add->readyHandler());

    // Verify that a request requiring only a forward change, transitions to
    // selecting a forward server.
    CHECK_CONTEXT(name_add, NameChangeTransaction::SELECTING_FWD_SERVER_ST,
                  NameChangeTransaction::SELECT_SERVER_EVT);

    // Create a transaction which includes both a forward and a reverse change.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(NameChangeTransaction::READY_ST,
                                   StateModel::START_EVT, FWD_AND_REV_CHG)
    );

    // Run readyHandler.
    EXPECT_NO_THROW(name_add->readyHandler());

    // Verify that a request requiring both forward and reverse, starts with
    // the forward change by transitioning to selecting a forward server.
    CHECK_CONTEXT(name_add, NameChangeTransaction::SELECTING_FWD_SERVER_ST,
                  NameChangeTransaction::SELECT_SERVER_EVT);

    // Create and prep a reverse only transaction.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(NameChangeTransaction::READY_ST,
                                   StateModel::START_EVT, REVERSE_CHG)
    );

    // Run readyHandler.
    EXPECT_NO_THROW(name_add->readyHandler());

    // Verify that a request requiring only a reverse change, transitions to
    // selecting a reverse server.
    CHECK_CONTEXT(name_add, NameChangeTransaction::SELECTING_REV_SERVER_ST,
                  NameChangeTransaction::SELECT_SERVER_EVT);

    // Create and prep transaction, poised to run the handler but with an
    // invalid event.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(NameChangeTransaction::READY_ST, StateModel::NOP_EVT)
    );

    // Running the readyHandler should throw.
    EXPECT_THROW(name_add->readyHandler(), SimpleAddTransactionError);
}

// Tests the selectingFwdServerHandler functionality.
// It verifies behavior for the following scenarios:
//
// 1. Posted event is SELECT_SERVER_EVT
// 2. Posted event is SERVER_IO_ERROR_EVT
// 3. Posted event is invalid
//
TEST_F(SimpleAddTransactionTest, selectingFwdServerHandler) {
    SimpleAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(NameChangeTransaction::SELECTING_FWD_SERVER_ST,
                                    NameChangeTransaction::SELECT_SERVER_EVT)
    );

    // Call selectingFwdServerHandler enough times to select all of the
    // servers in it's current domain.  The first time, it will be with
    // next event of SELECT_SERVER_EVT.  Thereafter it will be with a next
    // event of SERVER_IO_ERROR_EVT.
    int num_servers = name_add->getForwardDomain()->getServers()->size();
    for (int i = 0; i < num_servers; ++i) {
        SCOPED_TRACE(testing::Message() << " num_servers: " << num_servers
                     << " selections: " << i);
        // Run selectingFwdServerHandler.
        ASSERT_NO_THROW(name_add->selectingFwdServerHandler());

        // Verify that a server was selected.
        ASSERT_TRUE(name_add->getCurrentServer());

        // Verify that we transitioned correctly.
        CHECK_CONTEXT(name_add, SimpleAddTransaction::REPLACING_FWD_ADDRS_ST,
                      NameChangeTransaction::SERVER_SELECTED_EVT);

        // Post a server IO error event.  This simulates an IO error occurring
        // and a need to select the new server.
        ASSERT_NO_THROW(name_add->postNextEvent(NameChangeTransaction::
                                                SERVER_IO_ERROR_EVT));
    }

    // We should have exhausted the list of servers. Processing another
    // SERVER_IO_ERROR_EVT should transition us to failure.
    EXPECT_NO_THROW(name_add->selectingFwdServerHandler());
    CHECK_CONTEXT(name_add, NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
                  NameChangeTransaction::NO_MORE_SERVERS_EVT);

    // Create and prep transaction, poised to run the handler but with an
    // invalid event.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(NameChangeTransaction::SELECTING_FWD_SERVER_ST,
                                   StateModel::NOP_EVT)
    );

    // Running the handler should throw.
    EXPECT_THROW(name_add->selectingFwdServerHandler(),
                 SimpleAddTransactionError);
}

// ************************ replacingFwdAddrHandler Tests *****************

// Tests that replacingFwdAddrsHandler rejects invalid events.
TEST_F(SimpleAddTransactionTest, replacingFwdAddrsHandler_InvalidEvent) {
    SimpleAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler but with
    // an invalid event.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(SimpleAddTransaction::REPLACING_FWD_ADDRS_ST,
                                   NameChangeTransaction::StateModel::NOP_EVT)
    );

    // Running the handler should throw.
    EXPECT_THROW(name_add->replacingFwdAddrsHandler(), SimpleAddTransactionError);
}

// Tests replacingFwdAddrsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates successful update.
//
TEST_F(SimpleAddTransactionTest, replacingFwdAddrsHandler_FwdOnlyAddOK) {
    SimpleAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(SimpleAddTransaction::REPLACING_FWD_ADDRS_ST,
                                   SimpleAddTransaction::SERVER_SELECTED_EVT, FORWARD_CHG)
    );

    // Should not be an update message yet.
    D2UpdateMessagePtr update_msg = name_add->getDnsUpdateRequest();
    ASSERT_FALSE(update_msg);

    // At this point completion flags should be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Run replacingFwdAddrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

    // Verify that an update message was constructed properly.
    checkSimpleReplaceFwdAddressRequest(*name_add);

    // Verify that we are still in this state and next event is NOP_EVT.
    // This indicates we "sent" the message and are waiting for IO completion.
    CHECK_CONTEXT(name_add, SimpleAddTransaction::REPLACING_FWD_ADDRS_ST,
                  NameChangeTransaction::NOP_EVT);

    // Simulate receiving a successful update response.
    name_add->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NOERROR());

    // Run replacingFwdAddrsHandler again to process the response.
    EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

    // Forward completion should be true, reverse should be false.
    EXPECT_TRUE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since it is a forward only change, we should be done.
    // Verify that we transitioned correctly.
    CHECK_CONTEXT(name_add, NameChangeTransaction::PROCESS_TRANS_OK_ST,
                  NameChangeTransaction::UPDATE_OK_EVT);
}

// Tests replacingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  The update request is sent without error.
//  A server response is received which indicates the update was rejected.
//
TEST_F(SimpleAddTransactionTest, replacingFwdAddrsHandler_OtherRcode) {
    SimpleAddStubPtr name_add;
    // Create the transaction.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(SimpleAddTransaction::REPLACING_FWD_ADDRS_ST,
                                   SimpleAddTransaction::SERVER_SELECTED_EVT, FWD_AND_REV_CHG)
    );

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_add->selectFwdServer());

    // Run replacingFwdAddrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

    // Simulate receiving server rejection response. Per RFC, anything other
    // than no error or FQDN in use is failure.  Arbitrarily choosing refused.
    name_add->fakeResponse(DNSClient::SUCCESS, dns::Rcode::REFUSED());

    // Run replacingFwdAddrsHandler again to process the response.
    EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

    // Completion flags should still be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // We should have failed the transaction. Verify that we transitioned
    // correctly.
    CHECK_CONTEXT(name_add, NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
                  NameChangeTransaction::UPDATE_FAILED_EVT);
}

// Tests replacingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request send times out MAX_UPDATE_TRIES_PER_SERVER times.
//
TEST_F(SimpleAddTransactionTest, replacingFwdAddrsHandler_Timeout) {
    SimpleAddStubPtr name_add;

    // Create the transaction.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(SimpleAddTransaction::REPLACING_FWD_ADDRS_ST,
                                   SimpleAddTransaction::SERVER_SELECTED_EVT, FWD_AND_REV_CHG)
    );

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_add->selectFwdServer());


    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        // Run replacingFwdAddrsHandler to send the request.
        EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

        // Simulate a server IO timeout.
        name_add->setDnsUpdateStatus(DNSClient::TIMEOUT);
        name_add->postNextEvent(NameChangeTransaction::IO_COMPLETED_EVT);

        // Run replacingFwdAddrsHandler again to process the response.
        EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

        // Completion flags should be false.
        EXPECT_FALSE(name_add->getForwardChangeCompleted());
        EXPECT_FALSE(name_add->getReverseChangeCompleted());

        if (i < max_tries) {
            // We should be ready to try again.
            CHECK_CONTEXT(name_add, SimpleAddTransaction::REPLACING_FWD_ADDRS_ST,
                          NameChangeTransaction::SERVER_SELECTED_EVT);
        } else {
            // Server retries should be exhausted, time for a new server.
            CHECK_CONTEXT(name_add, SimpleAddTransaction::SELECTING_FWD_SERVER_ST,
                          NameChangeTransaction::SERVER_IO_ERROR_EVT);
        }
    }
}

// Tests replacingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent but a corrupt response is received, this occurs
//  MAX_UPDATE_TRIES_PER_SERVER times.
//
TEST_F(SimpleAddTransactionTest, replacingFwdAddrsHandler_CorruptResponse) {
    SimpleAddStubPtr name_add;

    // Create the transaction.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(SimpleAddTransaction::REPLACING_FWD_ADDRS_ST,
                                   SimpleAddTransaction::SERVER_SELECTED_EVT, FWD_AND_REV_CHG)
    );

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_add->selectFwdServer());

    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        // Run replacingFwdAddrsHandler to send the request.
        EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

        // Simulate a corrupt server response.
        name_add->setDnsUpdateStatus(DNSClient::INVALID_RESPONSE);
        name_add->postNextEvent(NameChangeTransaction::IO_COMPLETED_EVT);

        // Run replacingFwdAddrsHandler again to process the response.
        EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

        // Completion flags should be false.
        EXPECT_FALSE(name_add->getForwardChangeCompleted());
        EXPECT_FALSE(name_add->getReverseChangeCompleted());

        if (i < max_tries) {
            // We should be ready to try again.
            CHECK_CONTEXT(name_add, SimpleAddTransaction::REPLACING_FWD_ADDRS_ST,
                          NameChangeTransaction::SERVER_SELECTED_EVT);
        } else {
            // Server retries should be exhausted, time for a new server.
            CHECK_CONTEXT(name_add, SimpleAddTransaction::SELECTING_FWD_SERVER_ST,
                          NameChangeTransaction::SERVER_IO_ERROR_EVT);
        }
    }
}

// Tests the selectingRevServerHandler functionality.
// It verifies behavior for the following scenarios:
//
// 1. Posted event is SELECT_SERVER_EVT
// 2. Posted event is SERVER_IO_ERROR_EVT
// 3. Posted event is invalid
//
TEST_F(SimpleAddTransactionTest, selectingRevServerHandler) {
    SimpleAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(NameChangeTransaction::SELECTING_REV_SERVER_ST,
                                   NameChangeTransaction::SELECT_SERVER_EVT)
    );

    // Call selectingRevServerHandler enough times to select all of the
    // servers in it's current domain.  The first time, it will be with
    // next event of SELECT_SERVER_EVT.  Thereafter it will be with a next
    // event of SERVER_IO_ERROR_EVT.
    int num_servers = name_add->getReverseDomain()->getServers()->size();
    for (int i = 0; i < num_servers; ++i) {
        SCOPED_TRACE(testing::Message() << " num_servers: " << num_servers
                     << " selections: " << i);
        // Run selectingRevServerHandler.
        ASSERT_NO_THROW(name_add->selectingRevServerHandler());

        // Verify that a server was selected.
        ASSERT_TRUE(name_add->getCurrentServer());

        // Verify that we transitioned correctly.
        CHECK_CONTEXT(name_add, SimpleAddTransaction::REPLACING_REV_PTRS_ST,
                      NameChangeTransaction::SERVER_SELECTED_EVT);

        // Post a server IO error event.  This simulates an IO error occurring
        // and a need to select the new server.
        ASSERT_NO_THROW(name_add->postNextEvent(NameChangeTransaction::
                                                SERVER_IO_ERROR_EVT));
    }

    // We should have exhausted the list of servers. Processing another
    // SERVER_IO_ERROR_EVT should transition us to failure.
    EXPECT_NO_THROW(name_add->selectingRevServerHandler());
    CHECK_CONTEXT(name_add, NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
                  NameChangeTransaction::NO_MORE_SERVERS_EVT);

    // Create and prep transaction, poised to run the handler but with an
    // invalid event.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(NameChangeTransaction::SELECTING_REV_SERVER_ST,
                                   StateModel::NOP_EVT)
    );

    // Running the handler should throw.
    EXPECT_THROW(name_add->selectingRevServerHandler(),
                 SimpleAddTransactionError);
}

//************************** replacingRevPtrsHandler tests *****************

// Tests that replacingRevPtrsHandler rejects invalid events.
TEST_F(SimpleAddTransactionTest, replacingRevPtrsHandler_InvalidEvent) {
    SimpleAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler but with
    // an invalid event.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(SimpleAddTransaction::REPLACING_REV_PTRS_ST,
                                   NameChangeTransaction::StateModel::NOP_EVT)
    );

    // Running the handler should throw.
    EXPECT_THROW(name_add->replacingRevPtrsHandler(),
                 SimpleAddTransactionError);
}

// Tests replacingRevPtrsHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates successful update.
//
TEST_F(SimpleAddTransactionTest, replacingRevPtrsHandler_FwdOnlyAddOK) {
    SimpleAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(SimpleAddTransaction::REPLACING_REV_PTRS_ST,
                                   SimpleAddTransaction::SERVER_SELECTED_EVT, REVERSE_CHG)
    );

    // Should not be an update message yet.
    D2UpdateMessagePtr update_msg = name_add->getDnsUpdateRequest();
    ASSERT_FALSE(update_msg);

    // At this point completion flags should be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Run replacingRevPtrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_add->replacingRevPtrsHandler());

    // Verify that an update message was constructed properly.
    checkReplaceRevPtrsRequest(*name_add);

    // Verify that we are still in this state and next event is NOP_EVT.
    // This indicates we "sent" the message and are waiting for IO completion.
    CHECK_CONTEXT(name_add, SimpleAddTransaction::REPLACING_REV_PTRS_ST,
                  NameChangeTransaction::NOP_EVT);

    // Simulate receiving a successful update response.
    name_add->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NOERROR());

    // Run replacingRevPtrsHandler again to process the response.
    EXPECT_NO_THROW(name_add->replacingRevPtrsHandler());

    // Forward completion should be false, reverse should be true.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_TRUE(name_add->getReverseChangeCompleted());

    // Since it is a reverse change, we should be done.
    // Verify that we transitioned correctly.
    CHECK_CONTEXT(name_add, NameChangeTransaction::PROCESS_TRANS_OK_ST,
                  NameChangeTransaction::UPDATE_OK_EVT);
}

// Tests replacingRevPtrsHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates the update was rejected.
//
TEST_F(SimpleAddTransactionTest, replacingRevPtrsHandler_OtherRcode) {
    SimpleAddStubPtr name_add;
    // Create the transaction.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(SimpleAddTransaction::REPLACING_REV_PTRS_ST,
                                   SimpleAddTransaction::SERVER_SELECTED_EVT, REVERSE_CHG)
    );

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_add->selectRevServer());

    // Run replacingRevPtrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_add->replacingRevPtrsHandler());

    // Simulate receiving server rejection response. Per RFC, anything other
    // than no error is failure.  Arbitrarily choosing refused.
    name_add->fakeResponse(DNSClient::SUCCESS, dns::Rcode::REFUSED());

    // Run replacingRevPtrsHandler again to process the response.
    EXPECT_NO_THROW(name_add->replacingRevPtrsHandler());

    // Completion flags should still be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // We should have failed the transaction. Verify that we transitioned
    // correctly.
    CHECK_CONTEXT(name_add, NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
                  NameChangeTransaction::UPDATE_FAILED_EVT);
}

// Tests replacingRevPtrsHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request send times out MAX_UPDATE_TRIES_PER_SERVER times.
//
TEST_F(SimpleAddTransactionTest, replacingRevPtrsHandler_Timeout) {
    SimpleAddStubPtr name_add;
    // Create the transaction.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(SimpleAddTransaction::REPLACING_REV_PTRS_ST,
                                   SimpleAddTransaction::SERVER_SELECTED_EVT, REVERSE_CHG)
    );

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_add->selectRevServer());

    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        // Run replacingRevPtrsHandler to send the request.
        EXPECT_NO_THROW(name_add->replacingRevPtrsHandler());

        // Simulate a server IO timeout.
        name_add->setDnsUpdateStatus(DNSClient::TIMEOUT);
        name_add->postNextEvent(NameChangeTransaction::IO_COMPLETED_EVT);

        // Run replacingRevPtrsHandler again to process the response.
        EXPECT_NO_THROW(name_add->replacingRevPtrsHandler());

        // Completion flags should be false.
        EXPECT_FALSE(name_add->getForwardChangeCompleted());
        EXPECT_FALSE(name_add->getReverseChangeCompleted());

        if (i < max_tries) {
            // We should be ready to try again.
            CHECK_CONTEXT(name_add, SimpleAddTransaction::REPLACING_REV_PTRS_ST,
                          NameChangeTransaction::SERVER_SELECTED_EVT);
        } else {
            // Server retries should be exhausted, time for a new server.
            CHECK_CONTEXT(name_add, SimpleAddTransaction::SELECTING_REV_SERVER_ST,
                          NameChangeTransaction::SERVER_IO_ERROR_EVT);
        }
    }
}

// Tests replacingRevPtrsHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent but a corrupt response is received, this occurs
//  MAX_UPDATE_TRIES_PER_SERVER times.
//
TEST_F(SimpleAddTransactionTest, replacingRevPtrsHandler_CorruptResponse) {
    SimpleAddStubPtr name_add;
    // Create the transaction.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(SimpleAddTransaction::REPLACING_REV_PTRS_ST,
                                   SimpleAddTransaction::SERVER_SELECTED_EVT, REVERSE_CHG)
    );

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_add->selectRevServer());

    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        // Run replacingRevPtrsHandler to send the request.
        EXPECT_NO_THROW(name_add->replacingRevPtrsHandler());

        // Simulate a server corrupt response.
        name_add->setDnsUpdateStatus(DNSClient::INVALID_RESPONSE);
        name_add->postNextEvent(NameChangeTransaction::IO_COMPLETED_EVT);

        // Run replacingRevPtrsHandler again to process the response.
        EXPECT_NO_THROW(name_add->replacingRevPtrsHandler());

        // Completion flags should be false.
        EXPECT_FALSE(name_add->getForwardChangeCompleted());
        EXPECT_FALSE(name_add->getReverseChangeCompleted());

        if (i < max_tries) {
            // We should be ready to try again.
            CHECK_CONTEXT(name_add, SimpleAddTransaction::REPLACING_REV_PTRS_ST,
                          NameChangeTransaction::SERVER_SELECTED_EVT);
        } else {
            // Server retries should be exhausted, time for a new server.
            CHECK_CONTEXT(name_add, SimpleAddTransaction::SELECTING_REV_SERVER_ST,
                          NameChangeTransaction::SERVER_IO_ERROR_EVT);
        }
    }
}

// Tests the processAddOkHandler functionality.
// It verifies behavior for the following scenarios:
//
// 1. Posted event is UPDATE_OK_EVT
// 2. Posted event is invalid
//
TEST_F(SimpleAddTransactionTest, processAddOkHandler) {
    SimpleAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(NameChangeTransaction::PROCESS_TRANS_OK_ST,
                                   NameChangeTransaction::UPDATE_OK_EVT)
    );

    // Run processAddOkHandler.
    EXPECT_NO_THROW(name_add->processAddOkHandler());

    // Verify that a server was selected.
    EXPECT_EQ(dhcp_ddns::ST_COMPLETED, name_add->getNcrStatus());

    // Verify that the model has ended.
    CHECK_CONTEXT(name_add, StateModel::END_ST, StateModel::END_EVT);

    // Create and prep transaction, poised to run the handler but with an
    // invalid event.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(NameChangeTransaction::PROCESS_TRANS_OK_ST,
                                   StateModel::NOP_EVT)
    );

    // Running the handler should throw.
    EXPECT_THROW(name_add->processAddOkHandler(), SimpleAddTransactionError);
}

// Tests the processAddFailedHandler functionality.
// It verifies behavior for the following scenarios:
//
// 1. Posted event is UPDATE_FAILED_EVT
// 2. Posted event is invalid
//
TEST_F(SimpleAddTransactionTest, processAddFailedHandler) {
    SimpleAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
                                   NameChangeTransaction::UPDATE_FAILED_EVT)
    );

    // Run processAddFailedHandler.
    EXPECT_NO_THROW(name_add->processAddFailedHandler());

    // Verify that a server was selected.
    EXPECT_EQ(dhcp_ddns::ST_FAILED, name_add->getNcrStatus());

    // Verify that the model has ended. (Remember, the transaction failed NOT
    // the model.  The model should have ended normally.)
    CHECK_CONTEXT(name_add, StateModel::END_ST, StateModel::END_EVT);

    // Create and prep transaction, poised to run the handler but with an
    // invalid event.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
                                   StateModel::NOP_EVT)
    );

    // Running the handler should throw.
    EXPECT_THROW(name_add->processAddFailedHandler(), SimpleAddTransactionError);
}

// Tests the processAddFailedHandler functionality.
// It verifies behavior for posted event of NO_MORE_SERVERS_EVT.
TEST_F(SimpleAddTransactionTest, processAddFailedHandler_NoMoreServers) {
    SimpleAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
                                   NameChangeTransaction::NO_MORE_SERVERS_EVT)
    );

    // Run processAddFailedHandler.
    EXPECT_NO_THROW(name_add->processAddFailedHandler());

    // Verify that a server was selected.
    EXPECT_EQ(dhcp_ddns::ST_FAILED, name_add->getNcrStatus());

    // Verify that the model has ended. (Remember, the transaction failed NOT
    // the model.  The model should have ended normally.)
    CHECK_CONTEXT(name_add, StateModel::END_ST, StateModel::END_EVT);
}

// Tests replacingFwdAddrsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The send update request fails due to an unexpected exception.
//
TEST_F(SimpleAddTransactionTest, replacingFwdAddrsHandler_SendUpdateException) {
    SimpleAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(SimpleAddTransaction::REPLACING_FWD_ADDRS_ST,
                                   NameChangeTransaction::SERVER_SELECTED_EVT, FORWARD_CHG)
    );

    name_add->simulate_send_exception_ = true;

    // Run replacingFwdAddrsHandler to construct and send the request.
    ASSERT_NO_THROW(name_add->replacingFwdAddrsHandler());

    // Completion flags should be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since IO exceptions should be gracefully handled, any that occur
    // are unanticipated, and deemed unrecoverable, so the transaction should
    // be transitioned to failure.
    CHECK_CONTEXT(name_add, NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
                  NameChangeTransaction::UPDATE_FAILED_EVT);
}

// Tests replacingRevPtrHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The send update request fails due to an unexpected exception.
//
TEST_F(SimpleAddTransactionTest, replacingRevPtrsHandler_SendUpdateException) {
    SimpleAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(SimpleAddTransaction::REPLACING_REV_PTRS_ST,
                                   NameChangeTransaction::SERVER_SELECTED_EVT, REVERSE_CHG)
    );

    name_add->simulate_send_exception_ = true;

    // Run replacingRevPtrsHandler to construct and send the request.
    ASSERT_NO_THROW(name_add->replacingRevPtrsHandler());

    // Completion flags should be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since IO exceptions should be gracefully handled, any that occur
    // are unanticipated, and deemed unrecoverable, so the transaction should
    // be transitioned to failure.
    CHECK_CONTEXT(name_add, NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
                  NameChangeTransaction::UPDATE_FAILED_EVT);
}

// Tests replacingFwdAddrsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The request build fails due to an unexpected exception.
//
TEST_F(SimpleAddTransactionTest, replacingFwdAddrsHandler_BuildRequestException) {
    SimpleAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(SimpleAddTransaction::REPLACING_FWD_ADDRS_ST,
                                   NameChangeTransaction::SERVER_SELECTED_EVT, FORWARD_CHG)
    );

    // Set the one-shot exception simulation flag.
    name_add->simulate_build_request_exception_ = true;

    // Run replacingFwdAddrsHandler to construct and send the request.
    // This should fail with a build request throw which should be caught
    // in the state handler.
    ASSERT_NO_THROW(name_add->replacingFwdAddrsHandler());

    // Verify we did not attempt to send anything.
    EXPECT_EQ(0, name_add->getUpdateAttempts());

    // Completion flags should be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since IO exceptions should be gracefully handled, any that occur
    // are unanticipated, and deemed unrecoverable, so the transaction should
    // be transitioned to failure.
    CHECK_CONTEXT(name_add, NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
                  NameChangeTransaction::UPDATE_FAILED_EVT);
}

// Tests replacingRevPtrHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The request build fails due to an unexpected exception.
//
TEST_F(SimpleAddTransactionTest, replacingRevPtrsHandler_BuildRequestException) {
    SimpleAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(
        name_add = prepHandlerTest(SimpleAddTransaction::REPLACING_REV_PTRS_ST,
                                   NameChangeTransaction::SERVER_SELECTED_EVT, REVERSE_CHG)
    );

    // Set the one-shot exception simulation flag.
    name_add->simulate_build_request_exception_ = true;

    // Run replacingRevPtrsHandler to construct and send the request.
    // This should fail with a build request throw which should be caught
    // in the state handler.
    ASSERT_NO_THROW(name_add->replacingRevPtrsHandler());

    // Verify we did not attempt to send anything.
    EXPECT_EQ(0, name_add->getUpdateAttempts());

    // Completion flags should be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since IO exceptions should be gracefully handled, any that occur
    // are unanticipated, and deemed unrecoverable, so the transaction should
    // be transitioned to failure.
    CHECK_CONTEXT(name_add, NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
                  NameChangeTransaction::UPDATE_FAILED_EVT);
}

}
