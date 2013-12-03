// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <d2/nc_add.h>

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
    NameAddStub(IOServicePtr& io_service,
                dhcp_ddns::NameChangeRequestPtr& ncr,
                DdnsDomainPtr& forward_domain,
                DdnsDomainPtr& reverse_domain)
        : NameAddTransaction(io_service, ncr, forward_domain, reverse_domain){
    }

    virtual ~NameAddStub() {
    }

    /// @brief Simulates sending update requests to the DNS server
    /// Allows state handlers which conduct IO to be tested without a server.
    virtual void sendUpdate(bool /* use_tsig_ = false */) {
        setUpdateAttempts(getUpdateAttempts() + 1);
        postNextEvent(StateModel::NOP_EVT);
    }

    void fakeResponse(const DNSClient::Status& status,
                      const dns::Rcode& rcode) {
        D2UpdateMessagePtr msg(new D2UpdateMessage(D2UpdateMessage::OUTBOUND));
        setDnsUpdateStatus(status);
        msg->setRcode(rcode);
        setDnsUpdateResponse(msg);
        postNextEvent(NameChangeTransaction::IO_COMPLETED_EVT);
    }

    bool selectFwdServer() {
        if (getForwardDomain()) {
            initServerSelection(getForwardDomain());
            selectNextServer();
            return (getCurrentServer());
        }

        return (false);
    }

    bool selectRevServer() {
        if (getReverseDomain()) {
            initServerSelection(getReverseDomain());
            selectNextServer();
            return (getCurrentServer());
        }

        return (false);
    }


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
};

typedef boost::shared_ptr<NameAddStub> NameAddStubPtr;

/// @brief Test fixture for testing NameAddTransaction
///
/// Note this class uses NameAddStub class to exercise non-public
/// aspects of NameAddTransaction.
class NameAddTransactionTest : public ::testing::Test {
public:
    IOServicePtr io_service_;
    DdnsDomainPtr forward_domain_;
    DdnsDomainPtr reverse_domain_;

    NameAddTransactionTest() : io_service_(new isc::asiolink::IOService()) {
    }

    static const unsigned int FORWARD_CHG = 0x01;
    static const unsigned int REVERSE_CHG = 0x02;
    static const unsigned int FWD_AND_REV_CHG = REVERSE_CHG | FORWARD_CHG;

    virtual ~NameAddTransactionTest() {
    }

    /// @brief  Instantiates a NameAddStub test transaction
    /// The transaction is constructed around a predefined (i.e "canned")
    /// NameChangeRequest. The request has both forward and reverse DNS
    /// changes requested.  Based upon the change mask, the transaction
    /// will have either the forward, reverse, or both domains populated.
    ///
    /// @param change_mask determines which change directions are requested
    NameAddStubPtr makeCannedTransaction(int change_mask=FWD_AND_REV_CHG) {
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

        // Create NameChangeRequest from JSON string.
        dhcp_ddns::NameChangeRequestPtr ncr = dhcp_ddns::NameChangeRequest::
                                              fromJSON(msg_str);

        // If the change mask does not include a forward change clear the
        // forward domain; otherise create the domain and its servers.
        if (!(change_mask & FORWARD_CHG)) {
            ncr->setForwardChange(false);
            forward_domain_.reset();
        } else {
            // Create the forward domain and then its servers.
            DnsServerInfoStoragePtr servers(new DnsServerInfoStorage());
            DnsServerInfoPtr server(new DnsServerInfo("forward.example.com",
                                       isc::asiolink::IOAddress("1.1.1.1")));
            servers->push_back(server);
            server.reset(new DnsServerInfo("forward2.example.com",
                                       isc::asiolink::IOAddress("1.1.1.2")));
            servers->push_back(server);
            forward_domain_.reset(new DdnsDomain("example.com.", "", servers));
        }

        // If the change mask does not include a reverse change clear the
        // reverse domain; otherise create the domain and its servers.
        if (!(change_mask & REVERSE_CHG)) {
            ncr->setReverseChange(false);
            reverse_domain_.reset();
        } else {
            // Create the reverse domain and its server.
            DnsServerInfoStoragePtr servers(new DnsServerInfoStorage());
            DnsServerInfoPtr server(new DnsServerInfo("reverse.example.com",
                                                      isc::asiolink::
                                                      IOAddress("2.2.2.2")));
            servers->push_back(server);
            server.reset(new DnsServerInfo("reverse2.example.com",
                                           isc::asiolink::
                                           IOAddress("2.2.2.3")));
            servers->push_back(server);
            reverse_domain_.reset(new DdnsDomain("2.168.192.in.addr.arpa.",
                                                 "", servers));
        }

        // Now create the test transaction as would occur in update manager.
        return (NameAddStubPtr(new NameAddStub(io_service_, ncr,
                                      forward_domain_, reverse_domain_)));
    }

    /// @brief Create a test transaction at a known point in the state model.
    ///
    /// Method prepares a new test transaction and sets its state and next
    /// event values to those given.  This makes the transaction appear to
    /// be at that point in the state model without having to transition it
    /// through prerequiste states.   It also provides the ability to set
    /// which change directions are requested: forward change only, reverse
    /// change only, or both.
    ///
    /// @param state value to set as the current state
    /// @param event value to post as the next event
    /// @param change_mask determines which change directions are requested
    NameAddStubPtr prepHandlerTest(unsigned int state, unsigned int event,
                                   unsigned int change_mask = FWD_AND_REV_CHG) {
        NameAddStubPtr name_add = makeCannedTransaction(change_mask);
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
    IOServicePtr io_service(new isc::asiolink::IOService());

    const char* msg_str =
        "{"
        " \"change_type\" : 1 , "
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
    ASSERT_NO_THROW(forward_domain.reset(new DdnsDomain("*", "", servers)));
    ASSERT_NO_THROW(reverse_domain.reset(new DdnsDomain("*", "", servers)));

    // Verify that construction with wrong change type fails.
    EXPECT_THROW(NameAddTransaction(io_service, ncr,
                                    forward_domain, reverse_domain),
                                    NameAddTransactionError);

    // Verify that a valid construction attempt works.
    ncr->setChangeType(isc::dhcp_ddns::CHG_ADD);
    EXPECT_NO_THROW(NameAddTransaction(io_service, ncr,
                                       forward_domain, reverse_domain));
}

/// @brief Tests event and state dictionary construction and verification.
TEST_F(NameAddTransactionTest, dictionaryCheck) {
    NameAddStubPtr name_add;
    ASSERT_NO_THROW(name_add = makeCannedTransaction());
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

// Tests the readyHandler functionality.
// It verifies behavior for the following scenarios:
//
// 1. Posted event is START_EVT and request includes only a forward change
// 2. Posted event is START_EVT and request includes both a forward and a
// reverse change
// 3. Posted event is START_EVT and request includes only a reverse change
// 3. Posted event is invalid
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

    // Verify that an update message was constructed.
    update_msg = name_add->getDnsUpdateRequest();
    EXPECT_TRUE(update_msg);

    // Verify that we are still in this state and next event is NOP_EVT.
    // This indicates we "sent" the message and are waiting for IO completion.
    EXPECT_EQ(NameAddTransaction::ADDING_FWD_ADDRS_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::NOP_EVT,
              name_add->getNextEvent());

    // Simulate receiving a succussful update response.
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

    // Simulate receiving a succussful update response.
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

    // We should have failed the transaction. Verifiy that we transitioned
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

        // Simulate a server IO timeout.
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

    // Verify that an update message was constructed.
    update_msg = name_add->getDnsUpdateRequest();
    EXPECT_TRUE(update_msg);

    // Verify that we are still in this state and next event is NOP_EVT.
    // This indicates we "sent" the message and are waiting for IO completion.
    EXPECT_EQ(NameAddTransaction::REPLACING_FWD_ADDRS_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::NOP_EVT,
              name_add->getNextEvent());

    // Simulate receiving a succussful update response.
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

    // Simulate receiving a succussful update response.
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

    // Simulate receiving a succussful update response.
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


// Tests addingFwdAddrsHandler with the following scenario:
//
//  The request includes a forward and reverse change.
//  Initial posted event is FQDN_IN_USE_EVT.
//  The update request is sent without error.
//  A server response is received which indicates the FQDN is NOT in use.
//
TEST_F(NameAddTransactionTest, addingFwdAddrsHandler_FqdnNotInUse) {
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

        // Simulate a server corrupt response.
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

    // Verify that an update message was constructed.
    update_msg = name_add->getDnsUpdateRequest();
    EXPECT_TRUE(update_msg);

    // Verify that we are still in this state and next event is NOP_EVT.
    // This indicates we "sent" the message and are waiting for IO completion.
    EXPECT_EQ(NameAddTransaction::REPLACING_REV_PTRS_ST,
              name_add->getCurrState());
    EXPECT_EQ(NameChangeTransaction::NOP_EVT,
              name_add->getNextEvent());

    // Simulate receiving a succussful update response.
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
    //EXPECT_NO_THROW(name_add->replacingRevPtrsHandler());
    (name_add->replacingRevPtrsHandler());

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


}
