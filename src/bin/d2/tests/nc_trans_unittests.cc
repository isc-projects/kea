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

#include <d2/nc_trans.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::d2;

namespace {

/// @brief Test derivation of NameChangeTransaction for exercising state
/// model mechanics.
///
/// This class facilitates testing by making non-public methods accessible so
/// they can be invoked directly in test routines.  It implements a very
/// rudimentary state model, sufficient to test the state model mechanics
/// supplied by the base class.
class NameChangeStub : public NameChangeTransaction {
public:

    // NameChangeStub states
    static const int DUMMY_ST = DERIVED_STATES + 1;

    static const int DO_WORK_ST = DERIVED_STATES + 2;


    // NameChangeStub events
    static const int START_WORK_EVT = DERIVED_EVENTS + 1;

    /// @brief Constructor
    ///
    /// Parameters match those needed by NameChangeTransaction.
    NameChangeStub(isc::asiolink::IOService& io_service,
                   dhcp_ddns::NameChangeRequestPtr& ncr,
                   DdnsDomainPtr forward_domain,
                   DdnsDomainPtr reverse_domain)
        : NameChangeTransaction(io_service, ncr, forward_domain,
                                reverse_domain), dummy_called_(false) {
    }

    /// @brief Destructor
    virtual ~NameChangeStub() {
    }

    bool getDummyCalled() {
        return (dummy_called_);
    }

    void clearDummyCalled() {
        dummy_called_ = false;
    }

    void dummyHandler() {
       dummy_called_ = true;
    }

    /// @brief State handler for the READY_ST.
    ///
    /// Serves as the starting state handler, it consumes the
    /// START_TRANSACTION_EVT "transitioning" to the state, DO_WORK_ST and
    /// sets the next event to START_WORK_EVT.
    void readyHandler() {
        switch(getNextEvent()) {
        case START_TRANSACTION_EVT:
            setState(DO_WORK_ST);
            setNextEvent(START_WORK_EVT);
            break;
        default:
            // its bogus
            isc_throw(NameChangeTransactionError, "invalid event: "
                      << getNextEvent() << " for state: " << getState());
        }
    }

    /// @brief State handler for the DO_WORK_ST.
    ///
    /// Simulates a state that starts some form of asynchronous work.
    /// When next event is START_WORK_EVT it sets the status to pending
    /// and signals the state model must "wait" for an event by setting
    /// next event to NOP_EVT.
    ///
    /// When next event is IO_COMPLETED_EVT, it transitions to the state,
    /// DONE_ST, and sets the next event to ALL_DONE_EVT.
    void doWorkHandler() {
        switch(getNextEvent()) {
        case START_WORK_EVT:
            setNcrStatus(dhcp_ddns::ST_PENDING);
            setNextEvent(NOP_EVT);
            break;
        //case WORK_DONE_EVT:
        case IO_COMPLETED_EVT:
            setState(DONE_ST);
            setNextEvent(ALL_DONE_EVT);
            break;
        default:
            // its bogus
            isc_throw(NameChangeTransactionError, "invalid event: "
                      << getNextEvent() << " for state: " << getState());
        }
    }

    /// @brief State handler for the DONE_ST.
    ///
    /// This is the last state in the model.  Note that it sets the
    /// status to completed and next event to NOP_EVT.
    void doneHandler() {
        switch(getNextEvent()) {
        case ALL_DONE_EVT:
            setNcrStatus(dhcp_ddns::ST_COMPLETED);
            setNextEvent(NOP_EVT);
            break;
        default:
            // its bogus
            isc_throw(NameChangeTransactionError, "invalid event: "
                      << getNextEvent() << " for state: " << getState());
        }
    }

    /// @brief Initializes the state handler map.
    void initStateHandlerMap() {
        addToMap(READY_ST,
            boost::bind(&NameChangeStub::readyHandler, this));

        addToMap(DO_WORK_ST,
            boost::bind(&NameChangeStub::doWorkHandler, this));

        addToMap(DONE_ST,
            boost::bind(&NameChangeStub::doneHandler, this));
    }

    void verifyStateHandlerMap() {
        getStateHandler(READY_ST);
        getStateHandler(DO_WORK_ST);
        getStateHandler(DONE_ST);
    }

    // Expose the protected methods to be tested.
    using NameChangeTransaction::addToMap;
    using NameChangeTransaction::getStateHandler;
    using NameChangeTransaction::initStateHandlerMap;
    using NameChangeTransaction::runStateModel;
    using NameChangeTransaction::setState;
    using NameChangeTransaction::setNextEvent;
    using NameChangeTransaction::initServerSelection;
    using NameChangeTransaction::selectNextServer;
    using NameChangeTransaction::getCurrentServer;
    using NameChangeTransaction::getDNSClient;
    using NameChangeTransaction::setNcrStatus;
    using NameChangeTransaction::setDnsUpdateStatus;
    using NameChangeTransaction::getDnsUpdateResponse;
    using NameChangeTransaction::getForwardChangeCompleted;
    using NameChangeTransaction::getReverseChangeCompleted;
    using NameChangeTransaction::setForwardChangeCompleted;
    using NameChangeTransaction::setReverseChangeCompleted;

    bool dummy_called_;
};

const int NameChangeStub::DO_WORK_ST;
const int NameChangeStub::START_WORK_EVT;

/// @brief Defines a pointer to a D2UpdateMgr instance.
typedef boost::shared_ptr<NameChangeStub> NameChangeStubPtr;

/// @brief Test fixture for testing NameChangeTransaction
///
/// Note this class uses NameChangeStub class to exercise non-public
/// aspects of NameChangeTransaction.
class NameChangeTransactionTest : public ::testing::Test {
public:
    isc::asiolink::IOService io_service_;
    DdnsDomainPtr forward_domain_;
    DdnsDomainPtr reverse_domain_;

    virtual ~NameChangeTransactionTest() {
    }

    /// @brief Instantiates a NameChangeStub built around a canned
    /// NameChangeRequest.
    NameChangeStubPtr makeCannedTransaction() {
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

        DnsServerInfoStoragePtr servers(new DnsServerInfoStorage());
        DnsServerInfoPtr server;

        ncr = dhcp_ddns::NameChangeRequest::fromJSON(msg_str);

        // make forward server list
        server.reset(new DnsServerInfo("forward.example.com",
                                       isc::asiolink::IOAddress("1.1.1.1")));
        servers->push_back(server);
        forward_domain_.reset(new DdnsDomain("*", "", servers));

        // make reverse server list
        servers->clear();
        server.reset(new DnsServerInfo("reverse.example.com",
                                       isc::asiolink::IOAddress("2.2.2.2")));
        servers->push_back(server);
        reverse_domain_.reset(new DdnsDomain("*", "", servers));
        return (NameChangeStubPtr(new NameChangeStub(io_service_, ncr,
                                  forward_domain_, reverse_domain_)));

    }

};

/// @brief Tests NameChangeTransaction construction.
/// This test verifies that:
/// 1. Construction with null NameChangeRequest
/// 2. Construction with null forward domain is not allowed when the request
/// requires forward change.
/// 3. Construction with null reverse domain is not allowed when the request
/// requires reverse change.
/// 4. Valid construction functions properly
TEST(NameChangeTransaction, construction) {
    isc::asiolink::IOService io_service;

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

    dhcp_ddns::NameChangeRequestPtr empty_ncr;
    DnsServerInfoStoragePtr servers;
    DdnsDomainPtr forward_domain;
    DdnsDomainPtr reverse_domain;
    DdnsDomainPtr empty_domain;

    ASSERT_NO_THROW(ncr = dhcp_ddns::NameChangeRequest::fromJSON(msg_str));
    ASSERT_NO_THROW(forward_domain.reset(new DdnsDomain("*", "", servers)));
    ASSERT_NO_THROW(reverse_domain.reset(new DdnsDomain("*", "", servers)));

    // Verify that construction with an empty NameChangeRequest throws.
    EXPECT_THROW(NameChangeTransaction(io_service, empty_ncr,
                                       forward_domain, reverse_domain),
                                        NameChangeTransactionError);

    // Verify that construction with an empty forward domain when the
    // NameChangeRequest calls for a forward change throws.
    EXPECT_THROW(NameChangeTransaction(io_service, ncr,
                                       empty_domain, reverse_domain),
                                       NameChangeTransactionError);

    // Verify that construction with an empty reverse domain when the
    // NameChangeRequest calls for a reverse change throws.
    EXPECT_THROW(NameChangeTransaction(io_service, ncr,
                                       forward_domain, empty_domain),
                                       NameChangeTransactionError);

    // Verify that a valid construction attempt works.
    EXPECT_NO_THROW(NameChangeTransaction(io_service, ncr,
                                          forward_domain, reverse_domain));

    // Verify that an empty forward domain is allowed when the requests does
    // not include a forward change.
    ncr->setForwardChange(false);
    ncr->setReverseChange(true);
    EXPECT_NO_THROW(NameChangeTransaction(io_service, ncr,
                                          empty_domain, reverse_domain));

    // Verify that an empty reverse domain is allowed when the requests does
    // not include a reverse change.
    ncr->setForwardChange(true);
    ncr->setReverseChange(false);
    EXPECT_NO_THROW(NameChangeTransaction(io_service, ncr,
                                          forward_domain, empty_domain));
}

/// @brief General testing of member accessors.
/// Most if not all of these are also tested as a byproduct off larger tests.
TEST_F(NameChangeTransactionTest, accessors) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Verify that fetching the NameChangeRequest works.
    dhcp_ddns::NameChangeRequestPtr ncr = name_change->getNcr();
    ASSERT_TRUE(ncr);

    // Verify that getTransactionKey works.
    EXPECT_EQ(ncr->getDhcid(), name_change->getTransactionKey());

    // Verify that NcrStatus can be set and retrieved.
    EXPECT_NO_THROW(name_change->setNcrStatus(dhcp_ddns::ST_FAILED));
    EXPECT_EQ(dhcp_ddns::ST_FAILED, ncr->getStatus());

    // Verify that the forward domain can be retrieved.
    ASSERT_TRUE(name_change->getForwardDomain());
    EXPECT_EQ(forward_domain_, name_change->getForwardDomain());

    // Verify that the reverse domain can be retrieved.
    ASSERT_TRUE(name_change->getReverseDomain());
    EXPECT_EQ(reverse_domain_, name_change->getReverseDomain());

    // Neither of these have direct setters, but are tested under server
    // selection.
    EXPECT_FALSE(name_change->getDNSClient());
    EXPECT_FALSE(name_change->getCurrentServer());

    // Previous state should be set by setState.
    EXPECT_NO_THROW(name_change->setState(NameChangeTransaction::READY_ST));
    EXPECT_NO_THROW(name_change->setState(NameChangeStub::DO_WORK_ST));
    EXPECT_EQ(NameChangeTransaction::READY_ST, name_change->getPrevState());
    EXPECT_EQ(NameChangeStub::DO_WORK_ST, name_change->getState());

    // Last event should be set by setNextEvent.
    EXPECT_NO_THROW(name_change->setNextEvent(NameChangeStub::
                                              START_WORK_EVT));
    EXPECT_NO_THROW(name_change->setNextEvent(NameChangeTransaction::
                                              IO_COMPLETED_EVT));
    EXPECT_EQ(NameChangeStub::START_WORK_EVT, name_change->getLastEvent());
    EXPECT_EQ(NameChangeTransaction::IO_COMPLETED_EVT,
              name_change->getNextEvent());

    // Verify that DNS update status can be set and retrieved.
    EXPECT_NO_THROW(name_change->setDnsUpdateStatus(DNSClient::TIMEOUT));
    EXPECT_EQ(DNSClient::TIMEOUT, name_change->getDnsUpdateStatus());

    // Verify that the DNS update response can be retrieved. 
    EXPECT_FALSE(name_change->getDnsUpdateResponse());

    // Verify that the forward change complete flag can be set and fetched.
    EXPECT_NO_THROW(name_change->setForwardChangeCompleted(true));
    EXPECT_TRUE(name_change->getForwardChangeCompleted());

    // Verify that the reverse change complete flag can be set and fetched.
    EXPECT_NO_THROW(name_change->setReverseChangeCompleted(true));
    EXPECT_TRUE(name_change->getReverseChangeCompleted());
}

/// @brief Tests the fundamental methods used for state handler mapping.
/// Verifies the ability to search for and add entries in the state handler map.
TEST_F(NameChangeTransactionTest, basicStateMapping) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Verify that getStateHandler will throw when, state cannot be found.
    EXPECT_THROW(name_change->getStateHandler(NameChangeTransaction::READY_ST),
                 NameChangeTransactionError);

    // Verify that we can add a handler to the map.
    ASSERT_NO_THROW(name_change->addToMap(NameChangeTransaction::READY_ST,
                                          boost::bind(&NameChangeStub::
                                                      dummyHandler,
                                                      name_change.get())));

    // Verify that we can find the handler by its state.
    StateHandler retreived_handler;
    EXPECT_NO_THROW(retreived_handler =
                    name_change->getStateHandler(NameChangeTransaction::
                                                 READY_ST));

    // Verify that retrieved handler executes the correct method.
    name_change->clearDummyCalled();

    ASSERT_NO_THROW((retreived_handler)());
    EXPECT_TRUE(name_change->getDummyCalled());

    // Verify that we cannot add a duplicate.
    EXPECT_THROW(name_change->addToMap(NameChangeTransaction::READY_ST,
                                       boost::bind(&NameChangeStub::
                                                   readyHandler,
                                                   name_change.get())),
                 NameChangeTransactionError);

    // Verify that we can still find the handler by its state.
    EXPECT_NO_THROW(name_change->getStateHandler(NameChangeTransaction::
                                                 READY_ST));
}

/// @brief Tests state map initialization and validation.
/// This tests the basic concept of state map initialization and verification
/// by manually invoking the map methods normally called by startTransaction.
TEST_F(NameChangeTransactionTest, stubStateMapInit) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Verify that the map validation throws prior to the map being
    // initialized.
    ASSERT_THROW(name_change->verifyStateHandlerMap(),
                 NameChangeTransactionError);

    // Call initStateHandlerMap to initialize the state map.
    ASSERT_NO_THROW(name_change->initStateHandlerMap());

    // Verify that the map validation succeeds now that the map is initialized.
    ASSERT_NO_THROW(name_change->verifyStateHandlerMap());
}

/// @brief Tests that invalid states are handled gracefully.
/// This test verifies that attempting to execute a state which has no handler
/// results in a failed transaction.
TEST_F(NameChangeTransactionTest, invalidState) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Verfiy that to running the model with a state that has no handler,
    // will result in failed transaction (status of ST_FAILED).
    // First, verify state is NEW_ST and that NEW_ST has no handler.
    // that the transaction failed:
    ASSERT_EQ(NameChangeTransaction::NEW_ST, name_change->getState());
    ASSERT_THROW(name_change->getStateHandler(NameChangeTransaction::NEW_ST),
                 NameChangeTransactionError);

    // Now call runStateModel() which should not throw.
    EXPECT_NO_THROW(name_change->runStateModel(NameChangeTransaction::
                                               START_TRANSACTION_EVT));

    // Verify that the transaction has failed.
    EXPECT_EQ(dhcp_ddns::ST_FAILED, name_change->getNcrStatus());
}

/// @brief Tests that invalid events are handled gracefully.
/// This test verifies that submitting an invalid event to the state machine
/// results in a failed transaction.
TEST_F(NameChangeTransactionTest, invalidEvent) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // First, lets execute the state model to a known valid point, by
    // calling startTransaction.
    ASSERT_NO_THROW(name_change->startTransaction());

    // Verify we are in the state of DO_WORK_ST.
    EXPECT_EQ(NameChangeStub::DO_WORK_ST, name_change->getState());

    // Verity that submitting an invalid event to a valid state, results
    // in a failed transaction without a throw (Current state is DO_WORK_ST,
    // during which START_TRANSACTION_EVT, is invalid).
    EXPECT_NO_THROW(name_change->runStateModel(NameChangeTransaction::
                                               START_TRANSACTION_EVT));

    // Verify that the transaction has failed.
    EXPECT_EQ(dhcp_ddns::ST_FAILED, name_change->getNcrStatus());
}

/// @brief Test the basic mechanics of state model execution.
/// This test exercises the ability to execute state model from state to
/// finish, including the handling of a asynchronous IO operation.
TEST_F(NameChangeTransactionTest, stateModelTest) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Launch the transaction by calling startTransaction.  The state model
    // should run up until the "IO" operation is initiated in DO_WORK_ST.

    ASSERT_NO_THROW(name_change->startTransaction());

    // Verify that we are now in state of DO_WORK_ST, the last event was
    // START_WORK_EVT, the next event is NOP_EVT, and NCR status is ST_PENDING.
    EXPECT_EQ(NameChangeStub::DO_WORK_ST, name_change->getState());
    EXPECT_EQ(NameChangeStub::START_WORK_EVT, name_change->getLastEvent());
    EXPECT_EQ(NameChangeTransaction::NOP_EVT, name_change->getNextEvent());
    EXPECT_EQ(dhcp_ddns::ST_PENDING, name_change->getNcrStatus());

    // Simulate completion of DNSClient exchange by invoking the callback, as
    // DNSClient would.  This should cause the state model to progress through
    // completion.
    EXPECT_NO_THROW((*name_change)(DNSClient::SUCCESS));

    // Verify that the state model has progressed through to completion:
    // it is in the DONE_ST, the status is ST_COMPLETED, and the next event
    // is NOP_EVT.
    EXPECT_EQ(NameChangeTransaction::DONE_ST, name_change->getState());
    EXPECT_EQ(dhcp_ddns::ST_COMPLETED, name_change->getNcrStatus());
    EXPECT_EQ(NameChangeTransaction::NOP_EVT, name_change->getNextEvent());
}

/// @brief Tests server selection methods.
/// Each transaction has a list of one or more servers for each DNS direction
/// it is required to update.  The transaction must be able to start at the
/// beginning of a server list and cycle through them one at time, as needed,
/// when a DNS exchange fails due to an IO error.  This test verifies the
/// ability to iteratively select a server from the list as the current server.
TEST_F(NameChangeTransactionTest, serverSelectionTest) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Verify that the forward domain and its list of servers can be retrieved.
    DdnsDomainPtr& domain = name_change->getForwardDomain();
    ASSERT_TRUE(domain);
    DnsServerInfoStoragePtr servers = domain->getServers();
    ASSERT_TRUE(servers);

    // Get the number of entries in the server list.
    int num_servers = servers->size();
    ASSERT_TRUE(num_servers > 0);

    // Verify that we can initialize server selection.  This "resets" the
    // selection process to start over using the list of servers in the
    // given domain.
    ASSERT_NO_THROW(name_change->initServerSelection(domain));

    // The server selection process determines the current server,
    // instantiates a new DNSClient, and a DNS response message buffer.
    //  We need to save the values before each selection, so we can verify
    // they are correct after each selection.
    DnsServerInfoPtr prev_server = name_change->getCurrentServer();
    DNSClientPtr prev_client = name_change->getDNSClient();
    D2UpdateMessagePtr prev_response = name_change->getDnsUpdateResponse();

    // Iteratively select through the list of servers.
    int passes = 0;
    while (name_change->selectNextServer()) {
        // Get the new values after the selection has been made.
        DnsServerInfoPtr server = name_change->getCurrentServer();
        DNSClientPtr client = name_change->getDNSClient();
        D2UpdateMessagePtr response = name_change->getDnsUpdateResponse();

        // Verify that the new values are not empty.
        EXPECT_TRUE(server);
        EXPECT_TRUE(client);
        EXPECT_TRUE(response);

        // Verify that the new values are indeed new.
        EXPECT_NE(server, prev_server);
        EXPECT_NE(client, prev_client);
        EXPECT_NE(response, prev_response);

        // Remember the selected values for the next pass.
        prev_server = server;
        prev_client = client;
        prev_response = response;

        ++passes;
    }

    // Verify that the number of passes made equal the number of servers.
    EXPECT_EQ (passes, num_servers);

    // Repeat the same test using the reverse domain.
    // Verify that the reverse domain and its list of servers can be retrieved.
    domain = name_change->getReverseDomain();
    ASSERT_TRUE(domain);
    servers = domain->getServers();
    ASSERT_TRUE(servers);

    // Get the number of entries in the server list.
    num_servers = servers->size();
    ASSERT_TRUE(num_servers > 0);

    // Verify that we can initialize server selection.  This "resets" the
    // selection process to start over using the list of servers in the
    // given domain.
    ASSERT_NO_THROW(name_change->initServerSelection(domain));

    // The server selection process determines the current server,
    // instantiates a new DNSClient, and a DNS response message buffer.
    // We need to save the values before each selection, so we can verify
    // they are correct after each selection.
    prev_server = name_change->getCurrentServer();
    prev_client = name_change->getDNSClient();
    prev_response = name_change->getDnsUpdateResponse();

    // Iteratively select through the list of servers.
    passes = 0;
    while (name_change->selectNextServer()) {
        // Get the new values after the selection has been made.
        DnsServerInfoPtr server = name_change->getCurrentServer();
        DNSClientPtr client = name_change->getDNSClient();
        D2UpdateMessagePtr response = name_change->getDnsUpdateResponse();

        // Verify that the new values are not empty.
        EXPECT_TRUE(server);
        EXPECT_TRUE(client);
        EXPECT_TRUE(response);

        // Verify that the new values are indeed new.
        EXPECT_NE(server, prev_server);
        EXPECT_NE(client, prev_client);
        EXPECT_NE(response, prev_response);

        // Remember the selected values for the next pass.
        prev_server = server;
        prev_client = client;
        prev_response = response;

        ++passes;
    }

    // Verify that the number of passes made equal the number of servers.
    EXPECT_EQ (passes, num_servers);
}

}
