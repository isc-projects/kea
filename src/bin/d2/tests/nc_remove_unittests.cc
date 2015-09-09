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

#include <asiolink/io_service.h>
#include <d2/d2_cfg_mgr.h>
#include <d2/d2_cfg_mgr.h>
#include <d2/nc_remove.h>
#include <dns/messagerenderer.h>
#include <nc_test_utils.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::d2;

namespace {

/// @brief Test class derived from NameRemoveTransaction to provide visiblity
// to protected methods.
class NameRemoveStub : public NameRemoveTransaction {
public:
    NameRemoveStub(asiolink::IOServicePtr& io_service,
                   dhcp_ddns::NameChangeRequestPtr& ncr,
                   DdnsDomainPtr& forward_domain,
                   DdnsDomainPtr& reverse_domain,
                   D2CfgMgrPtr& cfg_mgr)
        : NameRemoveTransaction(io_service, ncr, forward_domain,
                                reverse_domain, cfg_mgr),
          simulate_send_exception_(false),
          simulate_build_request_exception_(false) {
    }

    virtual ~NameRemoveStub() {
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
    /// @param comment Parameter is unused, but present in base class method
    ///
    virtual void sendUpdate(const std::string& /* comment */) {
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
            isc_throw (NameRemoveTransactionError,
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
    using NameRemoveTransaction::defineEvents;
    using NameRemoveTransaction::verifyEvents;
    using NameRemoveTransaction::defineStates;
    using NameRemoveTransaction::verifyStates;
    using NameRemoveTransaction::readyHandler;
    using NameRemoveTransaction::selectingFwdServerHandler;
    using NameRemoveTransaction::getCurrentServer;
    using NameRemoveTransaction::removingFwdAddrsHandler;
    using NameRemoveTransaction::setDnsUpdateStatus;
    using NameRemoveTransaction::removingFwdRRsHandler;
    using NameRemoveTransaction::selectingRevServerHandler;
    using NameRemoveTransaction::removingRevPtrsHandler;
    using NameRemoveTransaction::processRemoveOkHandler;
    using NameRemoveTransaction::processRemoveFailedHandler;
    using NameRemoveTransaction::buildRemoveFwdAddressRequest;
    using NameRemoveTransaction::buildRemoveFwdRRsRequest;
    using NameRemoveTransaction::buildRemoveRevPtrsRequest;
};

typedef boost::shared_ptr<NameRemoveStub> NameRemoveStubPtr;

/// @brief Test fixture for testing NameRemoveTransaction
///
/// Note this class uses NameRemoveStub class to exercise non-public
/// aspects of NameRemoveTransaction.
class NameRemoveTransactionTest : public TransactionTest {
public:
    NameRemoveTransactionTest() {
    }

    virtual ~NameRemoveTransactionTest() {
    }

    /// @brief Creates a transaction which requests an IPv4 DNS update.
    ///
    /// The transaction is constructed around a predefined (i.e. "canned")
    /// IPv4 NameChangeRequest. The request has both forward and reverse DNS
    /// changes requested.  Based upon the change mask, the transaction
    /// will have either the forward, reverse, or both domains populated.
    ///
    /// @param change_mask determines which change directions are requested
    NameRemoveStubPtr makeTransaction4(int change_mask) {
        // Creates IPv4 remove request, forward, and reverse domains.
        setupForIPv4Transaction(dhcp_ddns::CHG_REMOVE, change_mask);

        // Now create the test transaction as would occur in update manager.
        return (NameRemoveStubPtr(new NameRemoveStub(io_service_, ncr_,
                                                     forward_domain_,
                                                     reverse_domain_,
                                                     cfg_mgr_)));
    }

    /// @brief Creates a transaction which requests an IPv6 DNS update.
    ///
    /// The transaction is constructed around a predefined (i.e. "canned")
    /// IPv6 NameChangeRequest. The request has both forward and reverse DNS
    /// changes requested.  Based upon the change mask, the transaction
    /// will have either the forward, reverse, or both domains populated.
    ///
    /// @param change_mask determines which change directions are requested
    NameRemoveStubPtr makeTransaction6(int change_mask) {
        // Creates IPv6 remove request, forward, and reverse domains.
        setupForIPv6Transaction(dhcp_ddns::CHG_REMOVE, change_mask);

        // Now create the test transaction as would occur in update manager.
        return (NameRemoveStubPtr(new NameRemoveStub(io_service_, ncr_,
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
    NameRemoveStubPtr prepHandlerTest(unsigned int state, unsigned int event,
                                      unsigned int change_mask
                                      = FWD_AND_REV_CHG,
                                      short family = AF_INET) {
        NameRemoveStubPtr name_remove = (family == AF_INET ?
                                         makeTransaction4(change_mask) :
                                         makeTransaction6(change_mask));
        name_remove->initDictionaries();
        name_remove->postNextEvent(event);
        name_remove->setState(state);
        return (name_remove);
    }

};

/// @brief Tests NameRemoveTransaction construction.
/// This test verifies that:
/// 1. Construction with invalid type of request
/// 2. Valid construction functions properly
TEST(NameRemoveTransaction, construction) {
    asiolink::IOServicePtr io_service(new isc::asiolink::IOService());
    D2CfgMgrPtr cfg_mgr(new D2CfgMgr());

    const char* msg_str =
        "{"
        " \"change_type\" : 0 , "
        " \"forward_change\" : true , "
        " \"reverse_change\" : true , "
        " \"fqdn\" : \"example.com.\" , "
        " \"ip_address\" : \"192.168.2.1\" , "
        " \"dhcid\" : \"0102030405060708\" , "
        " \"lease_expires_on\" : \"20130121132405\" , "
        " \"lease_length\" : 1300 "
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
    EXPECT_THROW(NameRemoveTransaction(io_service, ncr,
                                       forward_domain, reverse_domain, cfg_mgr),
                                       NameRemoveTransactionError);

    // Verify that a valid construction attempt works.
    ncr->setChangeType(isc::dhcp_ddns::CHG_REMOVE);
    EXPECT_NO_THROW(NameRemoveTransaction(io_service, ncr,
                                          forward_domain, reverse_domain,
                                          cfg_mgr));
}

/// @brief Tests event and state dictionary construction and verification.
TEST_F(NameRemoveTransactionTest, dictionaryCheck) {
    NameRemoveStubPtr name_remove;
    ASSERT_NO_THROW(name_remove = makeTransaction4(FWD_AND_REV_CHG));
    // Verify that the event and state dictionary validation fails prior
    // dictionary construction.
    ASSERT_THROW(name_remove->verifyEvents(), StateModelError);
    ASSERT_THROW(name_remove->verifyStates(), StateModelError);

    // Construct both dictionaries.
    ASSERT_NO_THROW(name_remove->defineEvents());
    ASSERT_NO_THROW(name_remove->defineStates());

    // Verify both event and state dictionaries now pass validation.
    ASSERT_NO_THROW(name_remove->verifyEvents());
    ASSERT_NO_THROW(name_remove->verifyStates());
}


/// @brief Tests construction of a DNS update request for removing forward
/// DNS address RRs.
TEST_F(NameRemoveTransactionTest, buildRemoveFwdAddressRequest) {
    // Create a IPv4 forward add transaction.
    // Verify the request builds without error.
    // and then verify the request contents.
    NameRemoveStubPtr name_remove;
    ASSERT_NO_THROW(name_remove = makeTransaction4(FORWARD_CHG));
    ASSERT_NO_THROW(name_remove->buildRemoveFwdAddressRequest());
    checkRemoveFwdAddressRequest(*name_remove);

    // Create a IPv6 forward add transaction.
    // Verify the request builds without error.
    // and then verify the request contents.
    ASSERT_NO_THROW(name_remove = makeTransaction6(FORWARD_CHG));
    ASSERT_NO_THROW(name_remove->buildRemoveFwdAddressRequest());
    checkRemoveFwdAddressRequest(*name_remove);
}

/// @brief Tests construction of a DNS update request for removing forward
/// dns RR entries.
TEST_F(NameRemoveTransactionTest, buildRemoveFwdRRsRequest) {
    // Create a IPv4 forward replace transaction.
    // Verify the request builds without error.
    // and then verify the request contents.
    NameRemoveStubPtr name_remove;
    ASSERT_NO_THROW(name_remove = makeTransaction4(FORWARD_CHG));
    ASSERT_NO_THROW(name_remove->buildRemoveFwdRRsRequest());
    checkRemoveFwdRRsRequest(*name_remove);

    // Create a IPv6 forward replace transaction.
    // Verify the request builds without error.
    // and then verify the request contents.
    ASSERT_NO_THROW(name_remove = makeTransaction6(FORWARD_CHG));
    ASSERT_NO_THROW(name_remove->buildRemoveFwdRRsRequest());
    checkRemoveFwdRRsRequest(*name_remove);
}

/// @brief Tests the construction of a DNS update request for removing a
/// reverse dns entry.
TEST_F(NameRemoveTransactionTest, buildRemoveRevPtrsRequest) {
    // Create a IPv4 reverse replace transaction.
    // Verify the request builds without error.
    // and then verify the request contents.
    NameRemoveStubPtr name_remove;
    ASSERT_NO_THROW(name_remove = makeTransaction4(REVERSE_CHG));
    ASSERT_NO_THROW(name_remove->buildRemoveRevPtrsRequest());
    checkRemoveRevPtrsRequest(*name_remove);

    // Create a IPv6 reverse replace transaction.
    // Verify the request builds without error.
    // and then verify the request contents.
    ASSERT_NO_THROW(name_remove = makeTransaction6(REVERSE_CHG));
    ASSERT_NO_THROW(name_remove->buildRemoveRevPtrsRequest());
    checkRemoveRevPtrsRequest(*name_remove);
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
TEST_F(NameRemoveTransactionTest, readyHandler) {
    NameRemoveStubPtr name_remove;

    // Create a transaction which includes only a forward change.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameChangeTransaction::READY_ST,
                                    StateModel::START_EVT, FORWARD_CHG));
    // Run readyHandler.
    EXPECT_NO_THROW(name_remove->readyHandler());

    // Verify that a request requiring only a forward change, transitions to
    // selecting a forward server.
    EXPECT_EQ(NameChangeTransaction::SELECTING_FWD_SERVER_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::SELECT_SERVER_EVT,
              name_remove->getNextEvent());

    // Create a transaction which includes both a forward and a reverse change.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameChangeTransaction::READY_ST,
                                    StateModel::START_EVT, FWD_AND_REV_CHG));
    // Run readyHandler.
    EXPECT_NO_THROW(name_remove->readyHandler());

    // Verify that a request requiring both forward and reverse, starts with
    // the forward change by transitioning to selecting a forward server.
    EXPECT_EQ(NameChangeTransaction::SELECTING_FWD_SERVER_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::SELECT_SERVER_EVT,
              name_remove->getNextEvent());

    // Create and prep a reverse only transaction.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameChangeTransaction::READY_ST,
                                    StateModel::START_EVT, REVERSE_CHG));
    // Run readyHandler.
    EXPECT_NO_THROW(name_remove->readyHandler());

    // Verify that a request requiring only a reverse change, transitions to
    // selecting a reverse server.
    EXPECT_EQ(NameChangeTransaction::SELECTING_REV_SERVER_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::SELECT_SERVER_EVT,
              name_remove->getNextEvent());

    // Create and prep transaction, poised to run the handler but with an
    // invalid event.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameChangeTransaction::READY_ST,
                                    StateModel::NOP_EVT));

    // Running the readyHandler should throw.
    EXPECT_THROW(name_remove->readyHandler(), NameRemoveTransactionError);
}


// Tests the selectingFwdServerHandler functionality.
// It verifies behavior for the following scenarios:
//
// 1. Posted event is SELECT_SERVER_EVT
// 2. Posted event is SERVER_IO_ERROR_EVT
// 3. Posted event is invalid
//
TEST_F(NameRemoveTransactionTest, selectingFwdServerHandler) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameChangeTransaction::
                                    SELECTING_FWD_SERVER_ST,
                                    NameChangeTransaction::SELECT_SERVER_EVT));

    // Call selectingFwdServerHandler enough times to select all of the
    // servers in it's current domain.  The first time, it will be with
    // next event of SELECT_SERVER_EVT.  Thereafter it will be with a next
    // event of SERVER_IO_ERROR_EVT.
    int num_servers = name_remove->getForwardDomain()->getServers()->size();
    for (int i = 0; i < num_servers; ++i) {
        // Run selectingFwdServerHandler.
        ASSERT_NO_THROW(name_remove->selectingFwdServerHandler())
                        << " num_servers: " << num_servers
                        << " selections: " << i;

        // Verify that a server was selected.
        ASSERT_TRUE(name_remove->getCurrentServer())
                    << " num_servers: " << num_servers << " selections: " << i;

        // Verify that we transitioned correctly.
        ASSERT_EQ(NameRemoveTransaction::REMOVING_FWD_ADDRS_ST,
                  name_remove->getCurrState())
                  << " num_servers: " << num_servers << " selections: " << i;
        ASSERT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                  name_remove->getNextEvent())
                  << " num_servers: " << num_servers << " selections: " << i;

        // Post a server IO error event.  This simulates an IO error occuring
        // and a need to select the new server.
        ASSERT_NO_THROW(name_remove->postNextEvent(NameChangeTransaction::
                                                   SERVER_IO_ERROR_EVT))
                        << " num_servers: " << num_servers
                        << " selections: " << i;
    }

    // We should have exhausted the list of servers. Processing another
    // SERVER_IO_ERROR_EVT should transition us to failure.
    EXPECT_NO_THROW(name_remove->selectingFwdServerHandler());
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::NO_MORE_SERVERS_EVT,
              name_remove->getNextEvent());

    // Create and prep transaction, poised to run the handler but with an
    // invalid event.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameChangeTransaction::
                                    SELECTING_FWD_SERVER_ST,
                                    StateModel::NOP_EVT));

    // Running the handler should throw.
    EXPECT_THROW(name_remove->selectingFwdServerHandler(),
                 NameRemoveTransactionError);
}

// ************************ addingFwdAddrHandler Tests *****************

// Tests that removingFwdAddrsHandler rejects invalid events.
TEST_F(NameRemoveTransactionTest, removingFwdAddrsHandler_InvalidEvent) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler but with
    // an invalid event.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_ADDRS_ST,
                                    StateModel::NOP_EVT));

    // Running the handler should throw.
    EXPECT_THROW(name_remove->removingFwdAddrsHandler(),
                 NameRemoveTransactionError);
}


// Tests addingFwdAddrsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates successful update
//
TEST_F(NameRemoveTransactionTest, removingFwdAddrsHandler_FwdOnlyOK) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, FORWARD_CHG));

    // Should not be an update message yet.
    D2UpdateMessagePtr update_msg = name_remove->getDnsUpdateRequest();
    ASSERT_FALSE(update_msg);

    // At this point completion flags should be false.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // Run removingFwdAddrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_remove->removingFwdAddrsHandler());

    // Verify that an update message was constructed properly.
    checkRemoveFwdAddressRequest(*name_remove);

    // Verify that we are still in this state and next event is NOP_EVT.
    // This indicates we "sent" the message and are waiting for IO completion.
    EXPECT_EQ(NameRemoveTransaction::REMOVING_FWD_ADDRS_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::NOP_EVT,
              name_remove->getNextEvent());

    // Simulate receiving a successful update response.
    name_remove->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NOERROR());

    // Run removingFwdAddrsHandler again to process the response.
    EXPECT_NO_THROW(name_remove->removingFwdAddrsHandler());

    // Completion flags should both still be false, as we are only partly
    // done with forward updates.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // Since we succeeded, we should now attempt to remove any remaining
    // forward RRs.
    // Verify that we transitioned correctly.
    EXPECT_EQ(NameRemoveTransaction::REMOVING_FWD_RRS_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameRemoveTransaction::UPDATE_OK_EVT,
              name_remove->getNextEvent());
}

// Tests addingFwdAddrsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates FQDN is not in use.
//
TEST_F(NameRemoveTransactionTest, removingFwdAddrsHandler_FqdnNotInUse) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, FORWARD_CHG));

    // Run removingFwdAddrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_remove->removingFwdAddrsHandler());

    // Simulate receiving a RRSET does not exist.
    name_remove->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NXRRSET());

    // Run removingFwdAddrsHandler again to process the response.
    EXPECT_NO_THROW(name_remove->removingFwdAddrsHandler());

    // Completion flags should both still be false, as we are only partly
    // done with forward updates.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // There was no address RR to remove, but we will still make sure there
    // are no other RRs for this FQDN.
    // Verify that we transitioned correctly.
    EXPECT_EQ(NameRemoveTransaction::REMOVING_FWD_RRS_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameRemoveTransaction::UPDATE_OK_EVT,
              name_remove->getNextEvent());
}


// Tests removingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates the update was rejected.
//
TEST_F(NameRemoveTransactionTest, removingFwdAddrsHandler_OtherRcode) {
    NameRemoveStubPtr name_remove;

    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_remove->selectFwdServer());

    // Run removingFwdAddrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_remove->removingFwdAddrsHandler());

    // Simulate receiving server rejection response. Per RFC, anything other
    // than no error or FQDN not in use is failure. Arbitrarily choosing
    // refused.
    name_remove->fakeResponse(DNSClient::SUCCESS, dns::Rcode::REFUSED());

    // Run removingFwdAddrsHandler again to process the response.
    EXPECT_NO_THROW(name_remove->removingFwdAddrsHandler());

    // Completion flags should still be false.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // We should have failed the transaction. Verify that we transitioned
    // correctly.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_remove->getNextEvent());
}


// Tests removingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request send times out MAX_UPDATE_TRIES_PER_SERVER times.
//
TEST_F(NameRemoveTransactionTest, removingFwdAddrsHandler_Timeout) {
    NameRemoveStubPtr name_remove;

    // Create and prep a transaction, poised to run the handler.
    // The log message issued when this test succeeds, displays the
    // selected server, so we need to select a server before running this
    // test.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_remove->selectFwdServer());

    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        const D2UpdateMessagePtr prev_msg = name_remove->getDnsUpdateRequest();

        // Run removingFwdAddrsHandler to send the request.
        EXPECT_NO_THROW(name_remove->removingFwdAddrsHandler());

        const D2UpdateMessagePtr curr_msg = name_remove->getDnsUpdateRequest();
        if (i == 1) {
            // First time around we should build the message.
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
        name_remove->setDnsUpdateStatus(DNSClient::TIMEOUT);
        name_remove->postNextEvent(NameChangeTransaction::IO_COMPLETED_EVT);

        // Run removingFwdAddrsHandler again to process the response.
        EXPECT_NO_THROW(name_remove->removingFwdAddrsHandler());

        // Completion flags should be false.
        EXPECT_FALSE(name_remove->getForwardChangeCompleted());
        EXPECT_FALSE(name_remove->getReverseChangeCompleted());

        if (i < max_tries) {
            // We should be ready to try again.
            EXPECT_EQ(NameRemoveTransaction::REMOVING_FWD_ADDRS_ST,
                      name_remove->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                    name_remove->getNextEvent());
        } else {
            // Server retries should be exhausted, time for a new server.
            EXPECT_EQ(NameRemoveTransaction::SELECTING_FWD_SERVER_ST,
                      name_remove->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_IO_ERROR_EVT,
                    name_remove->getNextEvent());
        }
    }
}

// Tests removingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent but a corrupt response is received, this occurs
//  MAX_UPDATE_TRIES_PER_SERVER times.
//
TEST_F(NameRemoveTransactionTest, removingFwdAddrsHandler_InvalidResponse) {
    NameRemoveStubPtr name_remove;

    // Create and prep a transaction, poised to run the handler.
    // The log message issued when this test succeeds, displays the
    // selected server, so we need to select a server before running this
    // test.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_remove->selectFwdServer());

    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        // Run removingFwdAddrsHandler to construct send the request.
        EXPECT_NO_THROW(name_remove->removingFwdAddrsHandler());

        // Simulate a corrupt server response.
        name_remove->setDnsUpdateStatus(DNSClient::INVALID_RESPONSE);
        name_remove->postNextEvent(NameChangeTransaction::IO_COMPLETED_EVT);

        // Run removingFwdAddrsHandler again to process the response.
        EXPECT_NO_THROW(name_remove->removingFwdAddrsHandler());

        // Completion flags should be false.
        EXPECT_FALSE(name_remove->getForwardChangeCompleted());
        EXPECT_FALSE(name_remove->getReverseChangeCompleted());

        if (i < max_tries) {
            // We should be ready to try again.
            EXPECT_EQ(NameRemoveTransaction::REMOVING_FWD_ADDRS_ST,
                      name_remove->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                    name_remove->getNextEvent());
        } else {
            // Server retries should be exhausted, time for a new server.
            EXPECT_EQ(NameRemoveTransaction::SELECTING_FWD_SERVER_ST,
                      name_remove->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_IO_ERROR_EVT,
                    name_remove->getNextEvent());
        }
    }

}

// ************************ removingFwdRRsHandler Tests *****************

// Tests that removingFwdRRsHandler rejects invalid events.
TEST_F(NameRemoveTransactionTest, removingFwdRRsHandler_InvalidEvent) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler but with
    // an invalid event.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_RRS_ST,
                                    StateModel::NOP_EVT));

    // Running the handler should throw.
    EXPECT_THROW(name_remove->removingFwdRRsHandler(),
                 NameRemoveTransactionError);
}

// Tests removingFwdRRsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is UPDATE_OK_EVT.
//  The update request is sent without error.
//  A server response is received which indicates successful update.
//
TEST_F(NameRemoveTransactionTest, removingFwdRRsHandler_FwdOnlyOK) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    UPDATE_OK_EVT, FORWARD_CHG));

    // Should not be an update message yet.
    D2UpdateMessagePtr update_msg = name_remove->getDnsUpdateRequest();
    ASSERT_FALSE(update_msg);

    // At this point completion flags should be false.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // Run removingFwdRRsHandler to construct and send the request.
    EXPECT_NO_THROW(name_remove->removingFwdRRsHandler());

    // Verify that an update message was constructed properly.
    checkRemoveFwdRRsRequest(*name_remove);

    // Verify that we are still in this state and next event is NOP_EVT.
    // This indicates we "sent" the message and are waiting for IO completion.
    EXPECT_EQ(NameRemoveTransaction::REMOVING_FWD_ADDRS_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::NOP_EVT,
              name_remove->getNextEvent());

    // Simulate receiving a successful update response.
    name_remove->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NOERROR());

    // Run removingFwdRRsHandler again to process the response.
    EXPECT_NO_THROW(name_remove->removingFwdRRsHandler());

    // Forward completion should be true, reverse should be false.
    EXPECT_TRUE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // Since it is a forward only change, we should be done.
    // Verify that we transitioned correctly.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_OK_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_OK_EVT,
              name_remove->getNextEvent());
}

// Tests removingFwdRRsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates successful update.
//
TEST_F(NameRemoveTransactionTest, removingFwdRRsHandler_FwdOnlyOK2) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, FORWARD_CHG));

    // Run removingFwdRRsHandler to construct and send the request.
    EXPECT_NO_THROW(name_remove->removingFwdRRsHandler());

    // Simulate receiving a successful update response.
    name_remove->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NOERROR());

    // Run removingFwdRRsHandler again to process the response.
    EXPECT_NO_THROW(name_remove->removingFwdRRsHandler());

    // Forward completion should be true, reverse should be false.
    EXPECT_TRUE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // Since it is a forward only change, we should be done.
    // Verify that we transitioned correctly.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_OK_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_OK_EVT,
              name_remove->getNextEvent());
}


// Tests removingFwdRRsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is UPDATE_OK_EVT.
//  The update request is sent without error.
//  A server response is received which indicates successful update.
//
TEST_F(NameRemoveTransactionTest, removingFwdRRsHandler_FwdAndRevOK) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    UPDATE_OK_EVT, FWD_AND_REV_CHG));

    // Run removingFwdRRsHandler to construct and send the request.
    EXPECT_NO_THROW(name_remove->removingFwdRRsHandler());

    // Simulate receiving a successful update response.
    name_remove->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NOERROR());

    // Run removingFwdRRsHandler again  to process the response.
    EXPECT_NO_THROW(name_remove->removingFwdRRsHandler());

    // Forward change completion should be true, reverse flag should be false.
    EXPECT_TRUE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // Since the request also includes a reverse change we should
    // be poised to start it. Verify that we transitioned correctly.
    EXPECT_EQ(NameChangeTransaction::SELECTING_REV_SERVER_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::SELECT_SERVER_EVT,
              name_remove->getNextEvent());
}

// Tests removingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is UPDATE_OK_EVT.
//  The update request is sent without error.
//  A server response is received which indicates the FQDN is NOT in use.
//
TEST_F(NameRemoveTransactionTest, removingFwdRRsHandler_FqdnNotInUse) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    UPDATE_OK_EVT, FORWARD_CHG));

    // Run removingFwdRRsHandler to construct and send the request.
    EXPECT_NO_THROW(name_remove->removingFwdRRsHandler());

    // Simulate receiving a RRSET does not exist response.
    name_remove->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NXRRSET());

    // Run removingFwdRRsHandler again to process the response.
    EXPECT_NO_THROW(name_remove->removingFwdRRsHandler());

    // Forwad completion flag should be true, reverse should still be false.
    EXPECT_TRUE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // The FQDN is no longer in use, RFC is unclear about this,
    // but we will treat this as success.
    // Since it is a forward only change, we should be done.
    // Verify that we transitioned correctly.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_OK_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_OK_EVT,
              name_remove->getNextEvent());
}

// Tests removingFwdRRsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  The update request is sent without error.
//  A server response is received which indicates the update was rejected.
//
TEST_F(NameRemoveTransactionTest, removingFwdRRsHandler_OtherRcode) {
    NameRemoveStubPtr name_remove;
    // Create the transaction.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    UPDATE_OK_EVT, FWD_AND_REV_CHG));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_remove->selectFwdServer());

    // Run removingFwdRRsHandler to construct and send the request.
    EXPECT_NO_THROW(name_remove->removingFwdRRsHandler());

    // Simulate receiving server rejection response. Per RFC, anything other
    // than no error is failure (we are also treating FQDN not in use is
    // success). Arbitrarily choosing refused.
    name_remove->fakeResponse(DNSClient::SUCCESS, dns::Rcode::REFUSED());

    // Run removingFwdRRsHandler again to process the response.
    EXPECT_NO_THROW(name_remove->removingFwdRRsHandler());

    // Completion flags should still be false.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // We should have failed the transaction. Verifiy that we transitioned
    // correctly.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_remove->getNextEvent());
}

// Tests removingFwdRRsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is UPDATE_OK_EVT.
//  The update request send times out MAX_UPDATE_TRIES_PER_SERVER times.
//
TEST_F(NameRemoveTransactionTest, removingFwdRRsHandler_Timeout) {
    NameRemoveStubPtr name_remove;

    // Create the transaction.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_RRS_ST,
                                    NameChangeTransaction::
                                    UPDATE_OK_EVT, FWD_AND_REV_CHG));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_remove->selectFwdServer());

    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        const D2UpdateMessagePtr prev_msg = name_remove->getDnsUpdateRequest();

        // Run removingFwdRRsHandler to send the request.
        EXPECT_NO_THROW(name_remove->removingFwdRRsHandler());

        const D2UpdateMessagePtr curr_msg = name_remove->getDnsUpdateRequest();
        if (i == 1) {
            // First time around we should build the message.
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
        name_remove->setDnsUpdateStatus(DNSClient::TIMEOUT);
        name_remove->postNextEvent(NameChangeTransaction::IO_COMPLETED_EVT);

        // Run removingFwdRRsHandler again to process the response.
        EXPECT_NO_THROW(name_remove->removingFwdRRsHandler());

        // Completion flags should be false.
        EXPECT_FALSE(name_remove->getForwardChangeCompleted());
        EXPECT_FALSE(name_remove->getReverseChangeCompleted());

        if (i < max_tries) {
            // We should be ready to try again.
            EXPECT_EQ(NameRemoveTransaction::REMOVING_FWD_RRS_ST,
                      name_remove->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                    name_remove->getNextEvent());
        } else {
            // Server retries should be exhausted.
            // We should abandon the transaction.
            EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
                      name_remove->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_IO_ERROR_EVT,
                    name_remove->getNextEvent());
        }
    }
}

// Tests removingFwdRRsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is UPDATE_OK_EVT.
//  The update request is sent but a corrupt response is received, this occurs
//  MAX_UPDATE_TRIES_PER_SERVER times.
//
TEST_F(NameRemoveTransactionTest, removingFwdRRsHandler_InvalidResponse) {
    NameRemoveStubPtr name_remove;

    // Create the transaction.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_RRS_ST,
                                    NameChangeTransaction::
                                    UPDATE_OK_EVT, FWD_AND_REV_CHG));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_remove->selectFwdServer());

    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        const D2UpdateMessagePtr prev_msg = name_remove->getDnsUpdateRequest();

        // Run removingFwdRRsHandler to send the request.
        EXPECT_NO_THROW(name_remove->removingFwdRRsHandler());

        const D2UpdateMessagePtr curr_msg = name_remove->getDnsUpdateRequest();
        if (i == 1) {
            // First time around we should build the message.
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
        name_remove->setDnsUpdateStatus(DNSClient::INVALID_RESPONSE);
        name_remove->postNextEvent(NameChangeTransaction::IO_COMPLETED_EVT);

        // Run removingFwdRRsHandler again to process the response.
        EXPECT_NO_THROW(name_remove->removingFwdRRsHandler());

        // Completion flags should be false.
        EXPECT_FALSE(name_remove->getForwardChangeCompleted());
        EXPECT_FALSE(name_remove->getReverseChangeCompleted());

        if (i < max_tries) {
            // We should be ready to try again.
            EXPECT_EQ(NameRemoveTransaction::REMOVING_FWD_RRS_ST,
                      name_remove->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                    name_remove->getNextEvent());
        } else {
            // Server retries should be exhausted.
            // We should abandon the transaction.
            EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
                      name_remove->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_IO_ERROR_EVT,
                    name_remove->getNextEvent());
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
TEST_F(NameRemoveTransactionTest, selectingRevServerHandler) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameChangeTransaction::
                                    SELECTING_REV_SERVER_ST,
                                    NameChangeTransaction::SELECT_SERVER_EVT));

    // Call selectingRevServerHandler enough times to select all of the
    // servers in it's current domain.  The first time, it will be with
    // next event of SELECT_SERVER_EVT.  Thereafter it will be with a next
    // event of SERVER_IO_ERROR_EVT.
    int num_servers = name_remove->getReverseDomain()->getServers()->size();
    for (int i = 0; i < num_servers; ++i) {
        // Run selectingRevServerHandler.
        ASSERT_NO_THROW(name_remove->selectingRevServerHandler())
                        << " num_servers: " << num_servers
                        << " selections: " << i;

        // Verify that a server was selected.
        ASSERT_TRUE(name_remove->getCurrentServer())
                    << " num_servers: " << num_servers
                    << " selections: " << i;

        // Verify that we transitioned correctly.
        ASSERT_EQ(NameRemoveTransaction::REMOVING_REV_PTRS_ST,
                  name_remove->getCurrState())
                  << " num_servers: " << num_servers << " selections: " << i;
        ASSERT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                  name_remove->getNextEvent())
                  << " num_servers: " << num_servers << " selections: " << i;

        // Post a server IO error event.  This simulates an IO error occuring
        // and a need to select the new server.
        ASSERT_NO_THROW(name_remove->postNextEvent(NameChangeTransaction::
                                                SERVER_IO_ERROR_EVT))
                        << " num_servers: " << num_servers
                        << " selections: " << i;
    }

    // We should have exhausted the list of servers. Processing another
    // SERVER_IO_ERROR_EVT should transition us to failure.
    EXPECT_NO_THROW(name_remove->selectingRevServerHandler());
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::NO_MORE_SERVERS_EVT,
              name_remove->getNextEvent());

    // Create and prep transaction, poised to run the handler but with an
    // invalid event.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameChangeTransaction::
                                    SELECTING_REV_SERVER_ST,
                                    StateModel::NOP_EVT));

    // Running the handler should throw.
    EXPECT_THROW(name_remove->selectingRevServerHandler(),
                 NameRemoveTransactionError);
}

//************************** removingRevPtrsHandler tests *****************

// Tests that removingRevPtrsHandler rejects invalid events.
TEST_F(NameRemoveTransactionTest, removingRevPtrsHandler_InvalidEvent) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler but with
    // an invalid event.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_REV_PTRS_ST,
                                    StateModel::NOP_EVT));

    // Running the handler should throw.
    EXPECT_THROW(name_remove->removingRevPtrsHandler(),
                 NameRemoveTransactionError);
}

// Tests removingRevPtrsHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates successful update.
//
TEST_F(NameRemoveTransactionTest, removingRevPtrsHandler_RevOnlyOK) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_REV_PTRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, REVERSE_CHG));

    // Should not be an update message yet.
    D2UpdateMessagePtr update_msg = name_remove->getDnsUpdateRequest();
    ASSERT_FALSE(update_msg);

    // At this point completion flags should be false.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // Run removingRevPtrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_remove->removingRevPtrsHandler());

    // Verify that an update message was constructed properly.
    checkRemoveRevPtrsRequest(*name_remove);

    // Verify that we are still in this state and next event is NOP_EVT.
    // This indicates we "sent" the message and are waiting for IO completion.
    EXPECT_EQ(NameRemoveTransaction::REMOVING_REV_PTRS_ST,
              name_remove->getCurrState());
    EXPECT_EQ(StateModel::NOP_EVT,
              name_remove->getNextEvent());

    // Simulate receiving a successful update response.
    name_remove->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NOERROR());

    // Run removingRevPtrsHandler again to process the response.
    EXPECT_NO_THROW(name_remove->removingRevPtrsHandler());

    // Forward completion should be false, reverse should be true.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_TRUE(name_remove->getReverseChangeCompleted());

    // Since it is a reverse change, we should be done.
    // Verify that we transitioned correctly.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_OK_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_OK_EVT,
              name_remove->getNextEvent());
}

// Tests removingRevPtrsHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates FQDN is NOT in use.
//
TEST_F(NameRemoveTransactionTest, removingRevPtrsHandler_FqdnNotInUse) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_REV_PTRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, REVERSE_CHG));

    // Should not be an update message yet.
    D2UpdateMessagePtr update_msg = name_remove->getDnsUpdateRequest();
    ASSERT_FALSE(update_msg);

    // At this point completion flags should be false.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // Run removingRevPtrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_remove->removingRevPtrsHandler());

    // Verify that an update message was constructed properly.
    checkRemoveRevPtrsRequest(*name_remove);

    // Verify that we are still in this state and next event is NOP_EVT.
    // This indicates we "sent" the message and are waiting for IO completion.
    EXPECT_EQ(NameRemoveTransaction::REMOVING_REV_PTRS_ST,
              name_remove->getCurrState());
    EXPECT_EQ(StateModel::NOP_EVT,
              name_remove->getNextEvent());

    // Simulate receiving a RRSET does not exist.
    name_remove->fakeResponse(DNSClient::SUCCESS, dns::Rcode::NXRRSET());

    // Run removingRevPtrsHandler again to process the response.
    EXPECT_NO_THROW(name_remove->removingRevPtrsHandler());

    // Forward completion should be false, reverse should be true.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_TRUE(name_remove->getReverseChangeCompleted());

    // Since it is a reverse change, we should be done.
    // Verify that we transitioned correctly.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_OK_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_OK_EVT,
              name_remove->getNextEvent());
}

// Tests removingRevPtrsHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent without error.
//  A server response is received which indicates the update was rejected.
//
TEST_F(NameRemoveTransactionTest, removingRevPtrsHandler_OtherRcode) {
    NameRemoveStubPtr name_remove;
    // Create the transaction.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_REV_PTRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, REVERSE_CHG));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_remove->selectRevServer());

    // Run removingRevPtrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_remove->removingRevPtrsHandler());

    // Simulate receiving server rejection response. Per RFC, anything other
    // than no error is failure.  Arbitrarily choosing refused.
    name_remove->fakeResponse(DNSClient::SUCCESS, dns::Rcode::REFUSED());

    // Run removingRevPtrsHandler again to process the response.
    EXPECT_NO_THROW(name_remove->removingRevPtrsHandler());

    // Completion flags should still be false.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // We should have failed the transaction. Verify that we transitioned
    // correctly.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_remove->getNextEvent());
}

// Tests removingRevPtrsHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request send times out MAX_UPDATE_TRIES_PER_SERVER times.
//
TEST_F(NameRemoveTransactionTest, removingRevPtrsHandler_Timeout) {
    NameRemoveStubPtr name_remove;
    // Create the transaction.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_REV_PTRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, REVERSE_CHG));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_remove->selectRevServer());

    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        const D2UpdateMessagePtr prev_msg = name_remove->getDnsUpdateRequest();

        // Run removingRevPtrsHandler to send the request.
        EXPECT_NO_THROW(name_remove->removingRevPtrsHandler());

        const D2UpdateMessagePtr curr_msg = name_remove->getDnsUpdateRequest();
        if (i == 1) {
            // First time around we should build the message.
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
        name_remove->setDnsUpdateStatus(DNSClient::TIMEOUT);
        name_remove->postNextEvent(NameChangeTransaction::IO_COMPLETED_EVT);

        // Run removingRevPtrsHandler again to process the response.
        EXPECT_NO_THROW(name_remove->removingRevPtrsHandler());

        // Completion flags should be false.
        EXPECT_FALSE(name_remove->getForwardChangeCompleted());
        EXPECT_FALSE(name_remove->getReverseChangeCompleted());

        if (i < max_tries) {
            // We should be ready to try again.
            EXPECT_EQ(NameRemoveTransaction::REMOVING_REV_PTRS_ST,
                      name_remove->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                      name_remove->getNextEvent());
        } else {
            // Server retries should be exhausted, time for a new server.
            EXPECT_EQ(NameChangeTransaction::SELECTING_REV_SERVER_ST,
                      name_remove->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_IO_ERROR_EVT,
                      name_remove->getNextEvent());
        }
    }
}


// Tests removingRevPtrsHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The update request is sent but a corrupt response is received, this occurs
//  MAX_UPDATE_TRIES_PER_SERVER times.
//
TEST_F(NameRemoveTransactionTest, removingRevPtrsHandler_CorruptResponse) {
    NameRemoveStubPtr name_remove;
    // Create the transaction.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_REV_PTRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, REVERSE_CHG));

    // Select a server to satisfy log statements.
    ASSERT_TRUE(name_remove->selectRevServer());

    // Verify that we can make maximum number of update attempts permitted
    // and then transition to selecting a new server.
    int max_tries = NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;
    for (int i = 1; i <= max_tries; ++i) {
        const D2UpdateMessagePtr prev_msg = name_remove->getDnsUpdateRequest();

        // Run removingRevPtrsHandler to send the request.
        EXPECT_NO_THROW(name_remove->removingRevPtrsHandler());

        const D2UpdateMessagePtr curr_msg = name_remove->getDnsUpdateRequest();
        if (i == 1) {
            // First time around we should build the message.
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
        name_remove->setDnsUpdateStatus(DNSClient::INVALID_RESPONSE);
        name_remove->postNextEvent(NameChangeTransaction::IO_COMPLETED_EVT);

        // Run removingRevPtrsHandler again to process the response.
        EXPECT_NO_THROW(name_remove->removingRevPtrsHandler());

        // Completion flags should be false.
        EXPECT_FALSE(name_remove->getForwardChangeCompleted());
        EXPECT_FALSE(name_remove->getReverseChangeCompleted());

        if (i < max_tries) {
            // We should be ready to try again.
            EXPECT_EQ(NameRemoveTransaction::REMOVING_REV_PTRS_ST,
                      name_remove->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
                      name_remove->getNextEvent());
        } else {
            // Server retries should be exhausted, time for a new server.
            EXPECT_EQ(NameChangeTransaction::SELECTING_REV_SERVER_ST,
                      name_remove->getCurrState());
            EXPECT_EQ(NameChangeTransaction::SERVER_IO_ERROR_EVT,
                      name_remove->getNextEvent());
        }
    }
}

// Tests the processRemoveOkHandler functionality.
// It verifies behavior for the following scenarios:
//
// 1. Posted event is UPDATE_OK_EVT
// 2. Posted event is invalid
//
TEST_F(NameRemoveTransactionTest, processRemoveOkHandler) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameChangeTransaction::PROCESS_TRANS_OK_ST,
                                    NameChangeTransaction::UPDATE_OK_EVT));
    // Run processRemoveOkHandler.
    EXPECT_NO_THROW(name_remove->processRemoveOkHandler());

    // Verify that a server was selected.
    EXPECT_EQ(dhcp_ddns::ST_COMPLETED, name_remove->getNcrStatus());

    // Verify that the model has ended.
    EXPECT_EQ(StateModel::END_ST, name_remove->getCurrState());
    EXPECT_EQ(StateModel::END_EVT, name_remove->getNextEvent());


    // Create and prep transaction, poised to run the handler but with an
    // invalid event.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameChangeTransaction::PROCESS_TRANS_OK_ST,
                                    StateModel::NOP_EVT));
    // Running the handler should throw.
    EXPECT_THROW(name_remove->processRemoveOkHandler(),
                 NameRemoveTransactionError);
}

// Tests the processRemoveFailedHandler functionality.
// It verifies behavior for the following scenarios:
//
// 1. Posted event is UPDATE_FAILED_EVT
// 2. Posted event is invalid
//
TEST_F(NameRemoveTransactionTest, processRemoveFailedHandler) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameChangeTransaction::
                                    PROCESS_TRANS_FAILED_ST,
                                    NameChangeTransaction::UPDATE_FAILED_EVT));
    // Run processRemoveFailedHandler.
    EXPECT_NO_THROW(name_remove->processRemoveFailedHandler());

    // Verify that a server was selected.
    EXPECT_EQ(dhcp_ddns::ST_FAILED, name_remove->getNcrStatus());

    // Verify that the model has ended. (Remember, the transaction failed NOT
    // the model.  The model should have ended normally.)
    EXPECT_EQ(StateModel::END_ST, name_remove->getCurrState());
    EXPECT_EQ(StateModel::END_EVT, name_remove->getNextEvent());


    // Create and prep transaction, poised to run the handler but with an
    // invalid event.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameChangeTransaction::
                                    PROCESS_TRANS_FAILED_ST,
                                    StateModel::NOP_EVT));
    // Running the handler should throw.
    EXPECT_THROW(name_remove->processRemoveFailedHandler(),
                 NameRemoveTransactionError);
}

// Tests the processRemoveFailedHandler functionality.
// It verifies behavior for posted event of NO_MORE_SERVERS_EVT.
TEST_F(NameRemoveTransactionTest, processRemoveFailedHandler_NoMoreServers) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameChangeTransaction::
                                    PROCESS_TRANS_FAILED_ST,
                                    NameChangeTransaction::
                                    NO_MORE_SERVERS_EVT));

    // Run processRemoveFailedHandler.
    EXPECT_NO_THROW(name_remove->processRemoveFailedHandler());

    // Verify that a server was selected.
    EXPECT_EQ(dhcp_ddns::ST_FAILED, name_remove->getNcrStatus());

    // Verify that the model has ended. (Remember, the transaction failed NOT
    // the model.  The model should have ended normally.)
    EXPECT_EQ(StateModel::END_ST, name_remove->getCurrState());
    EXPECT_EQ(StateModel::END_EVT, name_remove->getNextEvent());
}

// Tests the processRemoveFailedHandler functionality.
// It verifies behavior for posted event of SERVER_IO_ERROR_EVT.
TEST_F(NameRemoveTransactionTest, processRemoveFailedHandler_ServerIOError) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameChangeTransaction::
                                    PROCESS_TRANS_FAILED_ST,
                                    NameChangeTransaction::
                                    SERVER_IO_ERROR_EVT));

    // Run processRemoveFailedHandler.
    EXPECT_NO_THROW(name_remove->processRemoveFailedHandler());

    // Verify that a server was selected.
    EXPECT_EQ(dhcp_ddns::ST_FAILED, name_remove->getNcrStatus());

    // Verify that the model has ended. (Remember, the transaction failed NOT
    // the model.  The model should have ended normally.)
    EXPECT_EQ(StateModel::END_ST, name_remove->getCurrState());
    EXPECT_EQ(StateModel::END_EVT, name_remove->getNextEvent());
}

// Tests removingFwdAddrsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The send update request fails due to an unexpected exception.
//
TEST_F(NameRemoveTransactionTest, removingFwdAddrsHandler_sendUpdateException) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, FORWARD_CHG));

    name_remove->simulate_send_exception_ = true;

    // Run removingFwdAddrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_remove->removingFwdAddrsHandler());

    // Completion flags should be false.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // Since IO exceptions should be gracefully handled, any that occur
    // are unanticipated, and deemed unrecoverable, so the transaction should
    // be transitioned to failure.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_remove->getNextEvent());
}


// Tests removingFwdRRsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The send update request fails due to an unexpected exception.
//
TEST_F(NameRemoveTransactionTest, removingFwdRRsHandler_SendUpdateException) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_RRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, FORWARD_CHG));

    name_remove->simulate_send_exception_ = true;

    // Run removingFwdRRsHandler to construct and send the request.
    EXPECT_NO_THROW(name_remove->removingFwdRRsHandler());

    // Completion flags should be false.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // Since IO exceptions should be gracefully handled, any that occur
    // are unanticipated, and deemed unrecoverable, so the transaction should
    // be transitioned to failure.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_remove->getNextEvent());
}

// Tests removingRevPtrHandler with the following scenario:
//
//  The request includes only a reverse change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The send update request fails due to an unexpected exception.
//
TEST_F(NameRemoveTransactionTest, removingRevPtrsHandler_SendUpdateException) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_REV_PTRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, REVERSE_CHG));

    name_remove->simulate_send_exception_ = true;

    // Run removingRevPtrsHandler to construct and send the request.
    EXPECT_NO_THROW(name_remove->removingRevPtrsHandler());

    // Completion flags should be false.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // Since IO exceptions should be gracefully handled, any that occur
    // are unanticipated, and deemed unrecoverable, so the transaction should
    // be transitioned to failure.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_remove->getNextEvent());
}

// Tests removingFwdAddrsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The request build fails due to an unexpected exception.
//
TEST_F(NameRemoveTransactionTest,
       removingFwdAddrsHandler_BuildRequestException) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_ADDRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, FORWARD_CHG));

    // Set the one-shot exception simulation flag.
    name_remove->simulate_build_request_exception_ = true;

    // Run removingFwdAddrsHandler to construct and send the request.
    // This should fail with a build request throw which should be caught
    // in the state handler.
    ASSERT_NO_THROW(name_remove->removingFwdAddrsHandler());

    // Verify we did not attempt to send anything.
    EXPECT_EQ(0, name_remove->getUpdateAttempts());

    // Completion flags should be false.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // Since IO exceptions should be gracefully handled, any that occur
    // are unanticipated, and deemed unrecoverable, so the transaction should
    // be transitioned to failure.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_remove->getNextEvent());
}

// Tests removingFwdRRsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The request build fails due to an unexpected exception.
//
TEST_F(NameRemoveTransactionTest,
       removingFwdRRsHandler_BuildRequestException) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_FWD_RRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, FORWARD_CHG));

    // Set the one-shot exception simulation flag.
    name_remove->simulate_build_request_exception_ = true;

    // Run removingFwdRRsHandler to construct and send the request.
    // This should fail with a build request throw which should be caught
    // in the state handler.
    ASSERT_NO_THROW(name_remove->removingFwdRRsHandler());

    // Verify we did not attempt to send anything.
    EXPECT_EQ(0, name_remove->getUpdateAttempts());

    // Completion flags should be false.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // Since IO exceptions should be gracefully handled, any that occur
    // are unanticipated, and deemed unrecoverable, so the transaction should
    // be transitioned to failure.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_remove->getNextEvent());
}

// Tests removingRevPTRsHandler with the following scenario:
//
//  The request includes only a forward change.
//  Initial posted event is SERVER_SELECTED_EVT.
//  The request build fails due to an unexpected exception.
//
TEST_F(NameRemoveTransactionTest,
       removingRevPTRsHandler_BuildRequestException) {
    NameRemoveStubPtr name_remove;
    // Create and prep a transaction, poised to run the handler.
    ASSERT_NO_THROW(name_remove =
                    prepHandlerTest(NameRemoveTransaction::
                                    REMOVING_REV_PTRS_ST,
                                    NameChangeTransaction::
                                    SERVER_SELECTED_EVT, FORWARD_CHG));

    // Set the one-shot exception simulation flag.
    name_remove->simulate_build_request_exception_ = true;

    // Run removingRevPtrsHandler to construct and send the request.
    // This should fail with a build request throw which should be caught
    // in the state handler.
    ASSERT_NO_THROW(name_remove->removingRevPtrsHandler());

    // Verify we did not attempt to send anything.
    EXPECT_EQ(0, name_remove->getUpdateAttempts());

    // Completion flags should be false.
    EXPECT_FALSE(name_remove->getForwardChangeCompleted());
    EXPECT_FALSE(name_remove->getReverseChangeCompleted());

    // Since IO exceptions should be gracefully handled, any that occur
    // are unanticipated, and deemed unrecoverable, so the transaction should
    // be transitioned to failure.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_remove->getCurrState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_remove->getNextEvent());
}

}
