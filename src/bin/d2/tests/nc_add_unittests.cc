// Copyright (C) 2013-2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_service.h>
#include <d2/d2_cfg_mgr.h>
#include <d2/d2_cfg_mgr.h>
#include <d2/nc_add.h>
#include <dns/messagerenderer.h>
#include <nc_test_utils.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::d2;

namespace {

/// @brief Test class derived from NameAddTransaction to provide visiblity
// to protected methods.
class NameAddStub : public NameAddTransaction {
public:
    NameAddStub(asiolink::IOServicePtr& io_service,
                dhcp_ddns::NameChangeRequestPtr& ncr,
                DdnsDomainPtr& forward_domain,
                DdnsDomainPtr& reverse_domain,
                D2CfgMgrPtr& cfg_mgr)
        : NameAddTransaction(io_service, ncr, forward_domain, reverse_domain,
                             cfg_mgr),
          simulate_send_exception_(false),
          simulate_build_request_exception_(false) {
    }

    virtual ~NameAddStub() {
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
    /// This method overrides the NameChangeTransactio implementation to
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
            isc_throw (NameAddTransactionError,
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
    using NameAddTransaction::defineEvents;
    using NameAddTransaction::verifyEvents;
    using NameAddTransaction::defineStates;
    using NameAddTransaction::verifyStates;
    using NameAddTransaction::readyHandler;
    using NameAddTransaction::selectingFwdServerHandler;
    using NameAddTransaction::getCurrentServer;
    using NameAddTransaction::addingFwdAddrsHandler;
    using NameAddTransaction::setDnsUpdateStatus;
    using NameAddTransaction::replacingFwdAddrsHandler;
    using NameAddTransaction::selectingRevServerHandler;
    using NameAddTransaction::replacingRevPtrsHandler;
    using NameAddTransaction::processAddOkHandler;
    using NameAddTransaction::processAddFailedHandler;
    using NameAddTransaction::buildAddFwdAddressRequest;
    using NameAddTransaction::buildReplaceFwdAddressRequest;
    using NameAddTransaction::buildReplaceRevPtrsRequest;
};

typedef boost::shared_ptr<NameAddStub> NameAddStubPtr;

/// @brief Test fixture for testing NameAddTransaction
///
/// Note this class uses NameAddStub class to exercise non-public
/// aspects of NameAddTransaction.
class NameAddTransactionTest : public TransactionTest {
public:

    NameAddTransactionTest() {
    }

    virtual ~NameAddTransactionTest() {
    }

    /// @brief Creates a transaction which requests an IPv4 DNS update.
    ///
    /// The transaction is constructed around a predefined (i.e. "canned")
    /// IPv4 NameChangeRequest. The request has both forward and reverse DNS
    /// changes requested.  Based upon the change mask, the transaction
    /// will have either the forward, reverse, or both domains populated.
    ///
    /// @param change_mask determines which change directions are requested
    NameAddStubPtr makeTransaction4(int change_mask = FWD_AND_REV_CHG) {
        // Creates IPv4 remove request, forward, and reverse domains.
        setupForIPv4Transaction(dhcp_ddns::CHG_ADD, change_mask);

        // Now create the test transaction as would occur in update manager.
        return (NameAddStubPtr(new NameAddStub(io_service_, ncr_,
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
    NameAddStubPtr makeTransaction6(int change_mask = FWD_AND_REV_CHG) {
        // Creates IPv6 remove request, forward, and reverse domains.
        setupForIPv6Transaction(dhcp_ddns::CHG_ADD, change_mask);

        // Now create the test transaction as would occur in update manager.
        return (NameAddStubPtr(new NameAddStub(io_service_, ncr_,
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
    NameAddStubPtr prepHandlerTest(unsigned int state, unsigned int event,
                                   unsigned int change_mask = FWD_AND_REV_CHG,
                                   short family = AF_INET) {
        NameAddStubPtr name_add =  (family == AF_INET ?
                                    makeTransaction4(change_mask) :
                                    makeTransaction4(change_mask));
        name_add->initDictionaries();
        name_add->postNextEvent(event);
        name_add->setState(state);
        return (name_add);
    }
};

/// @brief Tests NameAddTransaction construction.
/// This test verifies that:
/// 1. Construction with invalid type of request
/// 2. Valid construction functions properly
TEST(NameAddTransaction, construction) {
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
        " \"lease-length\" : 1300 "
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
    EXPECT_THROW(NameAddTransaction(io_service, ncr,
                                    forward_domain, reverse_domain, cfg_mgr),
                                    NameAddTransactionError);

    // Verify that a valid construction attempt works.
    ncr->setChangeType(isc::dhcp_ddns::CHG_ADD);
    EXPECT_NO_THROW(NameAddTransaction(io_service, ncr,
                                       forward_domain, reverse_domain,
                                       cfg_mgr));
}

/// @brief Tests event and state dictionary construction and verification.
TEST_F(NameAddTransactionTest, dictionaryCheck) {
    NameAddStubPtr name_add;
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

/// @brief Tests construction of a DNS update request for adding a forward
/// dns entry.
TEST_F(NameAddTransactionTest, buildForwardAdd) {
    // Create a IPv4 forward add transaction.
    // Verify the request builds without error.
    // and then verify the request contents.
    NameAddStubPtr name_add;
    ASSERT_NO_THROW(name_add = makeTransaction4());
    ASSERT_NO_THROW(name_add->buildAddFwdAddressRequest());
    checkAddFwdAddressRequest(*name_add);

    // Create a IPv6 forward add transaction.
    // Verify the request builds without error.
    // and then verify the request contents.
    ASSERT_NO_THROW(name_add = makeTransaction6());
    ASSERT_NO_THROW(name_add->buildAddFwdAddressRequest());
    checkAddFwdAddressRequest(*name_add);
}

/// @brief Tests construction of a DNS update request for replacing a forward
/// dns entry.
TEST_F(NameAddTransactionTest, buildReplaceFwdAddressRequest) {
    // Create a IPv4 forward replace transaction.
    // Verify the request builds without error.
    // and then verify the request contents.
    NameAddStubPtr name_add;
    ASSERT_NO_THROW(name_add = makeTransaction4());
    ASSERT_NO_THROW(name_add->buildReplaceFwdAddressRequest());
    checkReplaceFwdAddressRequest(*name_add);

    // Create a IPv6 forward replace transaction.
    // Verify the request builds without error.
    // and then verify the request contents.
    ASSERT_NO_THROW(name_add = makeTransaction6());
    ASSERT_NO_THROW(name_add->buildReplaceFwdAddressRequest());
    checkReplaceFwdAddressRequest(*name_add);
}

/// @brief Tests the construction of a DNS update request for replacing a
/// reverse dns entry.
TEST_F(NameAddTransactionTest, buildReplaceRevPtrsRequest) {
    // Create a IPv4 reverse replace transaction.
    // Verify the request builds without error.
    // and then verify the request contents.
    NameAddStubPtr name_add;
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
TEST_F(NameAddTransactionTest, readyHandler) {
    NameAddStubPtr name_add;

    // Create a transaction which includes only a forward change.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameChangeTransaction::READY_ST,
                                    StateModel::START_EVT, FORWARD_CHG));
    // Run readyHandler.
    EXPECT_NO_THROW(name_add->readyHandler());

    // Verify that a request requiring only a forward change, transitions to
    // selecting a forward server.
    EXPECT_EQ(NameChangeTransaction::SELECTING_FWD_SERVER_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::SELECT_SERVER_EVT,
              name_add->getNextEvent());


    // Create a transaction which includes both a forward and a reverse change.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameChangeTransaction::READY_ST,
                                    StateModel::START_EVT, FWD_AND_REV_CHG));
    // Run readyHandler.
    EXPECT_NO_THROW(name_add->readyHandler());

    // Verify that a request requiring both forward and reverse, starts with
    // the forward change by transitioning to selecting a forward server.
    EXPECT_EQ(NameChangeTransaction::SELECTING_FWD_SERVER_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::SELECT_SERVER_EVT,
              name_add->getNextEvent());


    // Create and prep a reverse only transaction.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameChangeTransaction::READY_ST,
                                    StateModel::START_EVT, REVERSE_CHG));
    // Run readyHandler.
    EXPECT_NO_THROW(name_add->readyHandler());

    // Verify that a request requiring only a reverse change, transitions to
    // selecting a reverse server.
    EXPECT_EQ(NameChangeTransaction::SELECTING_REV_SERVER_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::SELECT_SERVER_EVT,
              name_add->getNextEvent());


    // Create and prep transaction, poised to run the handler but with an
    // invalid event.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameChangeTransaction::READY_ST,
                                    StateModel::NOP_EVT));

    // Running the readyHandler should throw.
    EXPECT_THROW(name_add->readyHandler(), NameAddTransactionError);
}

// Tests the selectingFwdServerHandler functionality.
// It verifies behavior for the following scenarios:
//
// 1. Posted event is SELECT_SERVER_EVT
// 2. Posted event is SERVER_IO_ERROR_EVT
// 3. Posted event is invalid
//
TEST_F(NameAddTransactionTest, selectingFwdServerHandler) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameChangeTransaction::
                                    SELECTING_FWD_SERVER_ST,
                                    NameChangeTransaction::SELECT_SERVER_EVT));

    // Call selectingFwdServerHandler enough times to select all of the
    // servers in it's current domain.  The first time, it will be with
    // next event of SELECT_SERVER_EVT.  Thereafter it will be with a next
    // event of SERVER_IO_ERROR_EVT.
    int num_servers = name_add->getForwardDomain()->getServers()->size();
    for (int i = 0; i < num_servers; ++i) {
        // Run selectingFwdServerHandler.
        ASSERT_NO_THROW(name_add->selectingFwdServerHandler())
                        << " num_servers: " << num_servers
                        << " selections: " << i;

        // Verify that a server was selected.
        ASSERT_TRUE(name_add->getCurrentServer())
                    << " num_servers: " << num_servers << " selections: " << i;

        // Verify that we transitioned correctly.
        ASSERT_EQ(NameAddTransaction::ADDING_FWD_ADDRS_ST,
                  name_add->getCurrState())
                  << " num_servers: " << num_servers << " selections: " << i;
        ASSERT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                  name_add->getNextEvent())
                  << " num_servers: " << num_servers << " selections: " << i;

        // Post a server IO error event.  This simulates an IO error occuring
        // and a need to select the new server.
        ASSERT_NO_THROW(name_add->postNextEvent(NameChangeTransaction::
                                                SERVER_IO_ERROR_EVT))
                        << " num_servers: " << num_servers
                        << " selections: " << i;
    }

    // We should have exhausted the list of servers. Processing another
    // SERVER_IO_ERROR_EVT should transition us to failure.
    EXPECT_NO_THROW(name_add->selectingFwdServerHandler());
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::NO_MORE_SERVERS_EVT,
              name_add->getNextEvent());

    // Create and prep transaction, poised to run the handler but with an
    // invalid event.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameChangeTransaction::
                                    SELECTING_FWD_SERVER_ST,
                                    StateModel::NOP_EVT));

    // Running the handler should throw.
    EXPECT_THROW(name_add->selectingFwdServerHandler(),
                 NameAddTransactionError);
}

// ************************ addingFwdAddrHandler Tests *****************

// Tests that addingFwdAddrsHandler rejects invalid events.
TEST_F(NameAddTransactionTest, addingFwdAddrsHandler_InvalidEvent) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler but with
    // an invalid event.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::ADDING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    StateModel::NOP_EVT));

    // Running the handler should throw.
    EXPECT_THROW(name_add->addingFwdAddrsHandler(),
                 NameAddTransactionError);
}

// Tests addingFwdAddrsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates successful update
//
TEST_F(NameAddTransactionTest, addingFwdAddrsHandler_FwdOnlyAddOK) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::ADDING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, FORWARD_CHG));

    // Should not be an update message yet.
    D2UpdateMessagePtr update_msg = name_add->getDnsUpdateRequest();
    ASSERT_FALSE(update_msg);

    // At this point completion flags should be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Run addingFwdAddrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_add->addingFwdAddrsHandler());

    // Verify that an update message was constructed properly.
    checkAddFwdAddressRequest(*name_add);

    // Verify that we are still in this state and next event is NOP_EVT.
    // This indicates we "sent" the message and are waiting for IO completion.
    EXPECT_EQ(NameAddTransaction::ADDING_FWD_ADDRS_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::NOP_EVT,
              name_add->getNextEvent());

    // Simulate receiving a successful update response.
    name_add->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NOERROR());

    // Run addingFwdAddrsHandler again to process the response.
    EXPECT_NO_THROW(name_add->addingFwdAddrsHandler());

    // Forward completion should be true, reverse should be false.
    EXPECT_TRUE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since it is a forward only change, we should be done.
    // Verify that we transitioned correctly.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_OK_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_OK_EVT,
              name_add->getNextEvent());
}

// Tests addingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates successful update.
//
TEST_F(NameAddTransactionTest, addingFwdAddrsHandler_fwdAndRevAddOK) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::ADDING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, FWD_AND_REV_CHG));

    // Run addingFwdAddrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_add->addingFwdAddrsHandler());

    // Simulate receiving a successful update response.
    name_add->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NOERROR());

    // Run addingFwdAddrsHandler again  to process the response.
    EXPECT_NO_THROW(name_add->addingFwdAddrsHandler());

    // Forward change completion should be true, reverse flag should be false.
    EXPECT_TRUE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since the request also includes a reverse change we should
    // be poised to start it. Verify that we transitioned correctly.
    EXPECT_EQ(NameChangeTransaction::SELECTING_REV_SERVER_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::SELECT_SERVER_EVT,
              name_add->getNextEvent());
}

// Tests addingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates the FQDN is in use.
//
TEST_F(NameAddTransactionTest, addingFwdAddrsHandler_FqdnInUse) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::ADDING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT));

    // Run addingFwdAddrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_add->addingFwdAddrsHandler());

    // Simulate receiving a FQDN in use response.
    name_add->fakeResponse(DNSClient::SUCCESS, dns::Rcode::YXDOMAIN());

    // Run addingFwdAddrsHandler again to process the response.
    EXPECT_NO_THROW(name_add->addingFwdAddrsHandler());

    // Completion flags should still be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since the FQDN is in use, per the RFC we must attempt to replace it.
    // Verify that we transitioned correctly.
    EXPECT_EQ(NameAddTransaction::REPLACING_FWD_ADDRS_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameAddTransaction::FQDN_IN_USE_EVT,
              name_add->getNextEvent());
}

// Tests addingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates the update was rejected.
//
TEST_F(NameAddTransactionTest, addingFwdAddrsHandler_OtherRcode) {
    NameAddStubPtr name_add;

    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::ADDING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_add->selectFwdServer());

    // Run addingFwdAddrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_add->addingFwdAddrsHandler());

    // Simulate receiving server rejection response. Per RFC, anything other
    // than no error or FQDN in use is failure.  Arbitrarily choosing refused.
    name_add->fakeResponse(DNSClient::SUCCESS, dns::Rcode::REFUSED());

    // Run addingFwdAddrsHandler again to process the response.
    EXPECT_NO_THROW(name_add->addingFwdAddrsHandler());

    // Completion flags should still be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // We should have failed the transaction. Verify that we transitioned
    // correctly.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_add->getNextEvent());
}

// Tests addingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request send times out MAX_UPDATE_TRIES_PER_SERVER times.
//
TEST_F(NameAddTransactionTest, addingFwdAddrsHandler_Timeout) {
    NameAddStubPtr name_add;

    // Create and prep a transaction, poised to run the handler.
    // The log message issued when this test succeeds, displays the
    // selected server, so we need to select a server before running this
    // test.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::ADDING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_add->selectFwdServer());

    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        const D2UpdateMessagePtr prev_msg = name_add->getDnsUpdateRequest();

        // Run addingFwdAddrsHandler to send the request.
        EXPECT_NO_THROW(name_add->addingFwdAddrsHandler());

        const D2UpdateMessagePtr curr_msg = name_add->getDnsUpdateRequest();
        if (i == 1) {
            // First time out we should build the message.
            EXPECT_FALSE(prev_msg);
            EXPECT_TRUE(curr_msg);
        } else {
            // Subsequent passes should reuse the request. We are only
            // looking to check that we have not replaced the pointer value
            // with a new pointer.  This tests the on_entry() logic which
            // clears the request ONLY upon initial entry into the state.
            EXPECT_TRUE(prev_msg == curr_msg);
        }

        // Simulate a server IO timeout.
        name_add->setDnsUpdateStatus(DNSClient::TIMEOUT);
        name_add->postNextEvent(NameChangeTransaction::IO_COMPLETED_EVT);

        // Run addingFwdAddrsHandler again to process the response.
        EXPECT_NO_THROW(name_add->addingFwdAddrsHandler());

        // Completion flags should be false.
        EXPECT_FALSE(name_add->getForwardChangeCompleted());
        EXPECT_FALSE(name_add->getReverseChangeCompleted());

        if (i < max_tries) {
            // We should be ready to try again.
            EXPECT_EQ(NameAddTransaction::ADDING_FWD_ADDRS_ST,
                      name_add->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                    name_add->getNextEvent());
        } else {
            // Server retries should be exhausted, time for a new server.
            EXPECT_EQ(NameAddTransaction::SELECTING_FWD_SERVER_ST,
                      name_add->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_IO_ERROR_EVT,
                    name_add->getNextEvent());
        }
    }
}

// Tests addingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent but a corrupt response is received, this occurs
//  MAX_UPDATE_TRIES_PER_SERVER times.
//
TEST_F(NameAddTransactionTest, addingFwdAddrsHandler_InvalidResponse) {
    NameAddStubPtr name_add;

    // Create and prep a transaction, poised to run the handler.
    // The log message issued when this test succeeds, displays the
    // selected server, so we need to select a server before running this
    // test.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::ADDING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_add->selectFwdServer());

    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        // Run addingFwdAddrsHandler to construct send the request.
        EXPECT_NO_THROW(name_add->addingFwdAddrsHandler());

        // Simulate a corrupt server response.
        name_add->setDnsUpdateStatus(DNSClient::INVALID_RESPONSE);
        name_add->postNextEvent(NameChangeTransaction::IO_COMPLETED_EVT);

        // Run addingFwdAddrsHandler again to process the response.
        EXPECT_NO_THROW(name_add->addingFwdAddrsHandler());

        // Completion flags should be false.
        EXPECT_FALSE(name_add->getForwardChangeCompleted());
        EXPECT_FALSE(name_add->getReverseChangeCompleted());

        if (i < max_tries) {
            // We should be ready to try again.
            EXPECT_EQ(NameAddTransaction::ADDING_FWD_ADDRS_ST,
                      name_add->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                    name_add->getNextEvent());
        } else {
            // Server retries should be exhausted, time for a new server.
            EXPECT_EQ(NameAddTransaction::SELECTING_FWD_SERVER_ST,
                      name_add->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_IO_ERROR_EVT,
                    name_add->getNextEvent());
        }
    }

}

// ************************ replacingFwdAddrHandler Tests *****************

// Tests that replacingFwdAddrsHandler rejects invalid events.
TEST_F(NameAddTransactionTest, replacingFwdAddrsHandler_InvalidEvent) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler but with
    // an invalid event.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    StateModel::NOP_EVT));

    // Running the handler should throw.
    EXPECT_THROW(name_add->replacingFwdAddrsHandler(),
                 NameAddTransactionError);
}

// Tests replacingFwdAddrsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is FQDN_IN_USE_EVT.
//  The update request is sent without error.
//  A server response is received which indicates successful update.
//
TEST_F(NameAddTransactionTest, replacingFwdAddrsHandler_FwdOnlyAddOK) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_FWD_ADDRS_ST,
                                    NameAddTransaction::
                                    FQDN_IN_USE_EVT, FORWARD_CHG));

    // Should not be an update message yet.
    D2UpdateMessagePtr update_msg = name_add->getDnsUpdateRequest();
    ASSERT_FALSE(update_msg);

    // At this point completion flags should be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Run replacingFwdAddrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

    // Verify that an update message was constructed properly.
    checkReplaceFwdAddressRequest(*name_add);

    // Verify that we are still in this state and next event is NOP_EVT.
    // This indicates we "sent" the message and are waiting for IO completion.
    EXPECT_EQ(NameAddTransaction::REPLACING_FWD_ADDRS_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::NOP_EVT,
              name_add->getNextEvent());

    // Simulate receiving a successful update response.
    name_add->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NOERROR());

    // Run replacingFwdAddrsHandler again to process the response.
    EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

    // Forward completion should be true, reverse should be false.
    EXPECT_TRUE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since it is a forward only change, we should be done.
    // Verify that we transitioned correctly.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_OK_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_OK_EVT,
              name_add->getNextEvent());
}

// Tests replacingFwdAddrsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates successful update.
//
TEST_F(NameAddTransactionTest, replacingFwdAddrsHandler_FwdOnlyAddOK2) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, FORWARD_CHG));

    // Run replacingFwdAddrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

    // Simulate receiving a successful update response.
    name_add->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NOERROR());

    // Run replacingFwdAddrsHandler again to process the response.
    EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

    // Forward completion should be true, reverse should be false.
    EXPECT_TRUE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since it is a forward only change, we should be done.
    // Verify that we transitioned correctly.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_OK_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_OK_EVT,
              name_add->getNextEvent());
}

// Tests replacingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is FQDN_IN_USE_EVT.
//  The update request is sent without error.
//  A server response is received which indicates successful update.
//
TEST_F(NameAddTransactionTest, replacingFwdAddrsHandler_FwdAndRevAddOK) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_FWD_ADDRS_ST,
                                    NameAddTransaction::
                                    FQDN_IN_USE_EVT, FWD_AND_REV_CHG));

    // Run replacingFwdAddrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

    // Simulate receiving a successful update response.
    name_add->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NOERROR());

    // Run replacingFwdAddrsHandler again  to process the response.
    EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

    // Forward change completion should be true, reverse flag should be false.
    EXPECT_TRUE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since the request also includes a reverse change we should
    // be poised to start it. Verify that we transitioned correctly.
    EXPECT_EQ(NameChangeTransaction::SELECTING_REV_SERVER_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::SELECT_SERVER_EVT,
              name_add->getNextEvent());
}


// Tests replacingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is FQDN_IN_USE_EVT.
//  The update request is sent without error.
//  A server response is received which indicates the FQDN is NOT in use.
//
TEST_F(NameAddTransactionTest, replacingFwdAddrsHandler_FqdnNotInUse) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_FWD_ADDRS_ST,
                                    NameAddTransaction::
                                    FQDN_IN_USE_EVT, FWD_AND_REV_CHG));

    // Run replacingFwdAddrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

    // Simulate receiving a FQDN not in use response.
    name_add->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NXDOMAIN());

    // Run replacingFwdAddrsHandler again to process the response.
    EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

    // Completion flags should still be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since the FQDN is no longer in use, per the RFC, try to add it.
    // Verify that we transitioned correctly.
    EXPECT_EQ(NameAddTransaction::ADDING_FWD_ADDRS_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
              name_add->getNextEvent());
}


// Tests replacingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  The update request is sent without error.
//  A server response is received which indicates the update was rejected.
//
TEST_F(NameAddTransactionTest, replacingFwdAddrsHandler_OtherRcode) {
    NameAddStubPtr name_add;
    // Create the transaction.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_FWD_ADDRS_ST,
                                    NameAddTransaction::
                                    FQDN_IN_USE_EVT, FWD_AND_REV_CHG));

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

    // We should have failed the transaction. Verifiy that we transitioned
    // correctly.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_add->getNextEvent());
}

// Tests replacingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is FQDN_IN_USE_EVT.
//  The update request send times out MAX_UPDATE_TRIES_PER_SERVER times.
//
TEST_F(NameAddTransactionTest, replacingFwdAddrsHandler_Timeout) {
    NameAddStubPtr name_add;

    // Create the transaction.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_FWD_ADDRS_ST,
                                    NameAddTransaction::
                                    FQDN_IN_USE_EVT, FWD_AND_REV_CHG));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_add->selectFwdServer());


    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        const D2UpdateMessagePtr prev_msg = name_add->getDnsUpdateRequest();

        // Run replacingFwdAddrsHandler to send the request.
        EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

        const D2UpdateMessagePtr curr_msg = name_add->getDnsUpdateRequest();
        if (i == 1) {
            // First time out we should build the message.
            EXPECT_FALSE(prev_msg);
            EXPECT_TRUE(curr_msg);
        } else {
            // Subsequent passes should reuse the request. We are only
            // looking to check that we have not replaced the pointer value
            // with a new pointer.  This tests the on_entry() logic which
            // clears the request ONLY upon initial entry into the state.
            EXPECT_TRUE(prev_msg == curr_msg);
        }

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
            EXPECT_EQ(NameAddTransaction::REPLACING_FWD_ADDRS_ST,
                      name_add->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                    name_add->getNextEvent());
        } else {
            // Server retries should be exhausted, time for a new server.
            EXPECT_EQ(NameAddTransaction::SELECTING_FWD_SERVER_ST,
                      name_add->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_IO_ERROR_EVT,
                    name_add->getNextEvent());
        }
    }
}

// Tests replacingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is FQDN_IN_USE_EVT.
//  The update request is sent but a corrupt response is received, this occurs
//  MAX_UPDATE_TRIES_PER_SERVER times.
//
TEST_F(NameAddTransactionTest, replacingFwdAddrsHandler_CorruptResponse) {
    NameAddStubPtr name_add;

    // Create the transaction.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_FWD_ADDRS_ST,
                                    NameAddTransaction::
                                    FQDN_IN_USE_EVT, FWD_AND_REV_CHG));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_add->selectFwdServer());

    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        const D2UpdateMessagePtr prev_msg = name_add->getDnsUpdateRequest();

        // Run replacingFwdAddrsHandler to send the request.
        EXPECT_NO_THROW(name_add->replacingFwdAddrsHandler());

        const D2UpdateMessagePtr curr_msg = name_add->getDnsUpdateRequest();
        if (i == 1) {
            // First time out we should build the message.
            EXPECT_FALSE(prev_msg);
            EXPECT_TRUE(curr_msg);
        } else {
            // Subsequent passes should reuse the request. We are only
            // looking to check that we have not replaced the pointer value
            // with a new pointer.  This tests the on_entry() logic which
            // clears the request ONLY upon initial entry into the state.
            EXPECT_TRUE(prev_msg == curr_msg);
        }

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
            EXPECT_EQ(NameAddTransaction::REPLACING_FWD_ADDRS_ST,
                      name_add->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                    name_add->getNextEvent());
        } else {
            // Server retries should be exhausted, time for a new server.
            EXPECT_EQ(NameAddTransaction::SELECTING_FWD_SERVER_ST,
                      name_add->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_IO_ERROR_EVT,
                    name_add->getNextEvent());
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
TEST_F(NameAddTransactionTest, selectingRevServerHandler) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameChangeTransaction::
                                    SELECTING_REV_SERVER_ST,
                                    NameChangeTransaction::SELECT_SERVER_EVT));

    // Call selectingRevServerHandler enough times to select all of the
    // servers in it's current domain.  The first time, it will be with
    // next event of SELECT_SERVER_EVT.  Thereafter it will be with a next
    // event of SERVER_IO_ERROR_EVT.
    int num_servers = name_add->getReverseDomain()->getServers()->size();
    for (int i = 0; i < num_servers; ++i) {
        // Run selectingRevServerHandler.
        ASSERT_NO_THROW(name_add->selectingRevServerHandler())
                        << " num_servers: " << num_servers
                        << " selections: " << i;

        // Verify that a server was selected.
        ASSERT_TRUE(name_add->getCurrentServer())
                    << " num_servers: " << num_servers
                    << " selections: " << i;

        // Verify that we transitioned correctly.
        ASSERT_EQ(NameAddTransaction::REPLACING_REV_PTRS_ST,
                  name_add->getCurrState())
                  << " num_servers: " << num_servers << " selections: " << i;
        ASSERT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                  name_add->getNextEvent())
                  << " num_servers: " << num_servers << " selections: " << i;

        // Post a server IO error event.  This simulates an IO error occuring
        // and a need to select the new server.
        ASSERT_NO_THROW(name_add->postNextEvent(NameChangeTransaction::
                                                SERVER_IO_ERROR_EVT))
                        << " num_servers: " << num_servers
                        << " selections: " << i;
    }

    // We should have exhausted the list of servers. Processing another
    // SERVER_IO_ERROR_EVT should transition us to failure.
    EXPECT_NO_THROW(name_add->selectingRevServerHandler());
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::NO_MORE_SERVERS_EVT,
              name_add->getNextEvent());

    // Create and prep transaction, poised to run the handler but with an
    // invalid event.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameChangeTransaction::
                                    SELECTING_REV_SERVER_ST,
                                    StateModel::NOP_EVT));

    // Running the handler should throw.
    EXPECT_THROW(name_add->selectingRevServerHandler(),
                 NameAddTransactionError);
}

//************************** replacingRevPtrsHandler tests *****************

// Tests that replacingRevPtrsHandler rejects invalid events.
TEST_F(NameAddTransactionTest, replacingRevPtrsHandler_InvalidEvent) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler but with
    // an invalid event.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_REV_PTRS_ST,
                                    NameChangeTransaction::
                                    StateModel::NOP_EVT));

    // Running the handler should throw.
    EXPECT_THROW(name_add->replacingRevPtrsHandler(),
                 NameAddTransactionError);
}

// Tests replacingRevPtrsHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates successful update.
//
TEST_F(NameAddTransactionTest, replacingRevPtrsHandler_FwdOnlyAddOK) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_REV_PTRS_ST,
                                    NameAddTransaction::
                                    SERVER_SELECTED_EVT, REVERSE_CHG));

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
    EXPECT_EQ(NameAddTransaction::REPLACING_REV_PTRS_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::NOP_EVT,
              name_add->getNextEvent());

    // Simulate receiving a successful update response.
    name_add->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NOERROR());

    // Run replacingRevPtrsHandler again to process the response.
    EXPECT_NO_THROW(name_add->replacingRevPtrsHandler());

    // Forward completion should be false, reverse should be true.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_TRUE(name_add->getReverseChangeCompleted());

    // Since it is a reverse change, we should be done.
    // Verify that we transitioned correctly.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_OK_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_OK_EVT,
              name_add->getNextEvent());
}

// Tests replacingRevPtrsHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates the update was rejected.
//
TEST_F(NameAddTransactionTest, replacingRevPtrsHandler_OtherRcode) {
    NameAddStubPtr name_add;
    // Create the transaction.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_REV_PTRS_ST,
                                    NameAddTransaction::
                                    SERVER_SELECTED_EVT, REVERSE_CHG));

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
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_add->getNextEvent());
}

// Tests replacingRevPtrsHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request send times out MAX_UPDATE_TRIES_PER_SERVER times.
//
TEST_F(NameAddTransactionTest, replacingRevPtrsHandler_Timeout) {
    NameAddStubPtr name_add;
    // Create the transaction.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_REV_PTRS_ST,
                                    NameAddTransaction::
                                    SERVER_SELECTED_EVT, REVERSE_CHG));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_add->selectRevServer());

    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        const D2UpdateMessagePtr prev_msg = name_add->getDnsUpdateRequest();

        // Run replacingRevPtrsHandler to send the request.
        EXPECT_NO_THROW(name_add->replacingRevPtrsHandler());

        const D2UpdateMessagePtr curr_msg = name_add->getDnsUpdateRequest();
        if (i == 1) {
            // First time out we should build the message.
            EXPECT_FALSE(prev_msg);
            EXPECT_TRUE(curr_msg);
        } else {
            // Subsequent passes should reuse the request. We are only
            // looking to check that we have not replaced the pointer value
            // with a new pointer.  This tests the on_entry() logic which
            // clears the request ONLY upon initial entry into the state.
            EXPECT_TRUE(prev_msg == curr_msg);
        }

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
            EXPECT_EQ(NameAddTransaction::REPLACING_REV_PTRS_ST,
                      name_add->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                    name_add->getNextEvent());
        } else {
            // Server retries should be exhausted, time for a new server.
            EXPECT_EQ(NameAddTransaction::SELECTING_REV_SERVER_ST,
                      name_add->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_IO_ERROR_EVT,
                    name_add->getNextEvent());
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
TEST_F(NameAddTransactionTest, replacingRevPtrsHandler_CorruptResponse) {
    NameAddStubPtr name_add;
    // Create the transaction.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_REV_PTRS_ST,
                                    NameAddTransaction::
                                    SERVER_SELECTED_EVT, REVERSE_CHG));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_add->selectRevServer());

    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        const D2UpdateMessagePtr prev_msg = name_add->getDnsUpdateRequest();

        // Run replacingRevPtrsHandler to send the request.
        EXPECT_NO_THROW(name_add->replacingRevPtrsHandler());

        const D2UpdateMessagePtr curr_msg = name_add->getDnsUpdateRequest();
        if (i == 1) {
            // First time out we should build the message.
            EXPECT_FALSE(prev_msg);
            EXPECT_TRUE(curr_msg);
        } else {
            // Subsequent passes should reuse the request. We are only
            // looking to check that we have not replaced the pointer value
            // with a new pointer.  This tests the on_entry() logic which
            // clears the request ONLY upon initial entry into the state.
            EXPECT_TRUE(prev_msg == curr_msg);
        }

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
            EXPECT_EQ(NameAddTransaction::REPLACING_REV_PTRS_ST,
                      name_add->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                    name_add->getNextEvent());
        } else {
            // Server retries should be exhausted, time for a new server.
            EXPECT_EQ(NameAddTransaction::SELECTING_REV_SERVER_ST,
                      name_add->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_IO_ERROR_EVT,
                    name_add->getNextEvent());
        }
    }
}

// Tests the processAddOkHandler functionality.
// It verifies behavior for the following scenarios:
//
// 1. Posted event is UPDATE_OK_EVT
// 2. Posted event is invalid
//
TEST_F(NameAddTransactionTest, processAddOkHandler) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameChangeTransaction::PROCESS_TRANS_OK_ST,
                                    NameChangeTransaction::UPDATE_OK_EVT));
    // Run processAddOkHandler.
    EXPECT_NO_THROW(name_add->processAddOkHandler());

    // Verify that a server was selected.
    EXPECT_EQ(dhcp_ddns::ST_COMPLETED, name_add->getNcrStatus());

    // Verify that the model has ended.
    EXPECT_EQ(StateModel::END_ST, name_add->getCurrState());
    EXPECT_EQ(StateModel::END_EVT, name_add->getNextEvent());


    // Create and prep transaction, poised to run the handler but with an
    // invalid event.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameChangeTransaction::PROCESS_TRANS_OK_ST,
                                    StateModel::NOP_EVT));
    // Running the handler should throw.
    EXPECT_THROW(name_add->processAddOkHandler(), NameAddTransactionError);
}

// Tests the processAddFailedHandler functionality.
// It verifies behavior for the following scenarios:
//
// 1. Posted event is UPDATE_FAILED_EVT
// 2. Posted event is invalid
//
TEST_F(NameAddTransactionTest, processAddFailedHandler) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameChangeTransaction::
                                    PROCESS_TRANS_FAILED_ST,
                                    NameChangeTransaction::UPDATE_FAILED_EVT));
    // Run processAddFailedHandler.
    EXPECT_NO_THROW(name_add->processAddFailedHandler());

    // Verify that a server was selected.
    EXPECT_EQ(dhcp_ddns::ST_FAILED, name_add->getNcrStatus());

    // Verify that the model has ended. (Remember, the transaction failed NOT
    // the model.  The model should have ended normally.)
    EXPECT_EQ(StateModel::END_ST, name_add->getCurrState());
    EXPECT_EQ(StateModel::END_EVT, name_add->getNextEvent());


    // Create and prep transaction, poised to run the handler but with an
    // invalid event.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameChangeTransaction::
                                    PROCESS_TRANS_FAILED_ST,
                                    StateModel::NOP_EVT));
    // Running the handler should throw.
    EXPECT_THROW(name_add->processAddFailedHandler(), NameAddTransactionError);
}

// Tests the processAddFailedHandler functionality.
// It verifies behavior for posted event of NO_MORE_SERVERS_EVT.
TEST_F(NameAddTransactionTest, processAddFailedHandler_NoMoreServers) {
    NameAddStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameChangeTransaction::
                                    PROCESS_TRANS_FAILED_ST,
                                    NameChangeTransaction::
                                    NO_MORE_SERVERS_EVT));

    // Run processAddFailedHandler.
    EXPECT_NO_THROW(name_remove->processAddFailedHandler());

    // Verify that a server was selected.
    EXPECT_EQ(dhcp_ddns::ST_FAILED, name_remove->getNcrStatus());

    // Verify that the model has ended. (Remember, the transaction failed NOT
    // the model.  The model should have ended normally.)
    EXPECT_EQ(StateModel::END_ST, name_remove->getCurrState());
    EXPECT_EQ(StateModel::END_EVT, name_remove->getNextEvent());
}

// Tests addingFwdAddrsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The send update request fails due to an unexpected exception.
//
TEST_F(NameAddTransactionTest, addingFwdAddrsHandler_sendUpdateException) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::ADDING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, FORWARD_CHG));

    name_add->simulate_send_exception_ = true;

    // Run replacingFwdAddrsHandler to construct and send the request.
    ASSERT_NO_THROW(name_add->addingFwdAddrsHandler());

    // Completion flags should be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since IO exceptions should be gracefully handled, any that occur
    // are unanticipated, and deemed unrecoverable, so the transaction should
    // be transitioned to failure.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_add->getNextEvent());
}

// Tests replacingFwdAddrsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The send update request fails due to an unexpected exception.
//
TEST_F(NameAddTransactionTest, replacingFwdAddrsHandler_SendUpdateException) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, FORWARD_CHG));

    name_add->simulate_send_exception_ = true;

    // Run replacingFwdAddrsHandler to construct and send the request.
    ASSERT_NO_THROW(name_add->replacingFwdAddrsHandler());

    // Completion flags should be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since IO exceptions should be gracefully handled, any that occur
    // are unanticipated, and deemed unrecoverable, so the transaction should
    // be transitioned to failure.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_add->getNextEvent());
}

// Tests replacingRevPtrHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The send update request fails due to an unexpected exception.
//
TEST_F(NameAddTransactionTest, replacingRevPtrsHandler_SendUpdateException) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_REV_PTRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, REVERSE_CHG));

    name_add->simulate_send_exception_ = true;

    // Run replacingRevPtrsHandler to construct and send the request.
    ASSERT_NO_THROW(name_add->replacingRevPtrsHandler());

    // Completion flags should be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since IO exceptions should be gracefully handled, any that occur
    // are unanticipated, and deemed unrecoverable, so the transaction should
    // be transitioned to failure.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_add->getNextEvent());
}

// Tests addingFwdAddrsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The request build fails due to an unexpected exception.
//
TEST_F(NameAddTransactionTest, addingFwdAddrsHandler_BuildRequestException) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::ADDING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, FORWARD_CHG));

    // Set the one-shot exception simulation flag.
    name_add->simulate_build_request_exception_ = true;

    // Run replacingRevPtrsHandler to construct and send the request.
    // This should fail with a build request throw which should be caught
    // in the state handler.
    ASSERT_NO_THROW(name_add->addingFwdAddrsHandler());

    // Verify we did not attempt to send anything.
    EXPECT_EQ(0, name_add->getUpdateAttempts());

    // Completion flags should be false.
    EXPECT_FALSE(name_add->getForwardChangeCompleted());
    EXPECT_FALSE(name_add->getReverseChangeCompleted());

    // Since IO exceptions should be gracefully handled, any that occur
    // are unanticipated, and deemed unrecoverable, so the transaction should
    // be transitioned to failure.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_add->getNextEvent());
}

// Tests replacingFwdAddrsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The request build fails due to an unexpected exception.
//
TEST_F(NameAddTransactionTest, replacingFwdAddrsHandler_BuildRequestException) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, FORWARD_CHG));

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
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_add->getNextEvent());
}


// Tests replacingRevPtrHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The request build fails due to an unexpected exception.
//
TEST_F(NameAddTransactionTest, replacingRevPtrsHandler_BuildRequestException) {
    NameAddStubPtr name_add;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_add =
                    prepHandlerTest(NameAddTransaction::REPLACING_REV_PTRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, REVERSE_CHG));

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
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_add->getNextEvent());
}


}
