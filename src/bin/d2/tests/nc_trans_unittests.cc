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
    static const int DOING_UPDATE_ST = NCT_STATE_MAX + 1;

    // NameChangeStub events
    static const int SEND_UPDATE_EVT = NCT_EVENT_MAX + 2;

    /// @brief Constructor
    ///
    /// Parameters match those needed by NameChangeTransaction.
    NameChangeStub(isc::asiolink::IOService& io_service,
                   dhcp_ddns::NameChangeRequestPtr& ncr,
                   DdnsDomainPtr forward_domain,
                   DdnsDomainPtr reverse_domain)
        : NameChangeTransaction(io_service, ncr, forward_domain,
                                reverse_domain) {
    }

    /// @brief Destructor
    virtual ~NameChangeStub() {
    }

    /// @brief Empty handler used to statisfy map verification.
    void dummyHandler() {
        isc_throw(NameChangeTransactionError,
                  "dummyHandler - invalid event: " << getContextStr());
    }

    /// @brief State handler for the READY_ST.
    ///
    /// Serves as the starting state handler, it consumes the
    /// START_EVT "transitioning" to the state, DOING_UPDATE_ST and
    /// sets the next event to SEND_UPDATE_EVT.
    void readyHandler() {
        switch(getNextEvent()) {
        case START_EVT:
            transition(DOING_UPDATE_ST, SEND_UPDATE_EVT);
            break;
        default:
            // its bogus
            isc_throw(NameChangeTransactionError,
                      "readyHandler - invalid event: " << getContextStr());
        }
    }

    /// @brief State handler for the DOING_UPDATE_ST.
    ///
    /// Simulates a state that starts some form of asynchronous work.
    /// When next event is SEND_UPDATE_EVT it sets the status to pending
    /// and signals the state model must "wait" for an event by setting
    /// next event to NOP_EVT.
    ///
    /// When next event is IO_COMPLETED_EVT, it transitions to the state,
    /// PROCESS_TRANS_OK_ST, and sets the next event to UPDATE_OK_EVT.
    void doingUpdateHandler() {
        switch(getNextEvent()) {
        case SEND_UPDATE_EVT:
            setNcrStatus(dhcp_ddns::ST_PENDING);
            postNextEvent(NOP_EVT);
            break;
        case IO_COMPLETED_EVT:
            if (getDnsUpdateStatus() == DNSClient::SUCCESS) {
                setForwardChangeCompleted(true);
                transition(PROCESS_TRANS_OK_ST, UPDATE_OK_EVT);
            } else {
                transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
            }
            break;
        default:
            // its bogus
            isc_throw(NameChangeTransactionError,
                      "doingUpdateHandler - invalid event: "
                      << getContextStr());
        }
    }

    /// @brief State handler for the PROCESS_TRANS_OK_ST.
    ///
    /// This is the last state in the model.  Note that it sets the
    /// status to completed and next event to NOP_EVT.
    void processTransDoneHandler() {
        switch(getNextEvent()) {
        case UPDATE_OK_EVT:
            setNcrStatus(dhcp_ddns::ST_COMPLETED);
            endModel();
            break;
        case UPDATE_FAILED_EVT:
            setNcrStatus(dhcp_ddns::ST_FAILED);
            endModel();
            break;
        default:
            // its bogus
            isc_throw(NameChangeTransactionError,
                      "processTransDoneHandler - invalid event: "
                      << getContextStr());
        }
    }

    /// @brief Construct the event dictionary.
    virtual void defineEvents() {
        // Invoke the base call implementation first.
        NameChangeTransaction::defineEvents();

        // Define our events.
        defineEvent(SEND_UPDATE_EVT, "SEND_UPDATE_EVT");
    }

    /// @brief Verify the event dictionary.
    virtual void verifyEvents() {
        // Invoke the base call implementation first.
        NameChangeTransaction::verifyEvents();

        // Define our events.
        getEvent(SEND_UPDATE_EVT);
    }

    /// @brief Construct the state dictionary.
    virtual void defineStates() {
        // Invoke the base call implementation first.
        NameChangeTransaction::defineStates();

        // Define our states.
        defineState(READY_ST, "READY_ST",
                             boost::bind(&NameChangeStub::readyHandler, this));

        defineState(SELECTING_FWD_SERVER_ST, "SELECTING_FWD_SERVER_ST",
                             boost::bind(&NameChangeStub::dummyHandler, this));

        defineState(SELECTING_REV_SERVER_ST, "SELECTING_REV_SERVER_ST",
                             boost::bind(&NameChangeStub::dummyHandler, this));

        defineState(DOING_UPDATE_ST, "DOING_UPDATE_ST",
                             boost::bind(&NameChangeStub::doingUpdateHandler,
                                         this));

        defineState(PROCESS_TRANS_OK_ST, "PROCESS_TRANS_OK_ST",
                             boost::bind(&NameChangeStub::
                                         processTransDoneHandler, this));

        defineState(PROCESS_TRANS_FAILED_ST, "PROCESS_TRANS_FAILED_ST",
                             boost::bind(&NameChangeStub::
                                         processTransDoneHandler, this));
    }

    /// @brief Verify the event dictionary.
    virtual void verifyStates() {
        // Invoke the base call implementation first.
        NameChangeTransaction::verifyStates();

        // Define our states.
        getState(DOING_UPDATE_ST);
    }

    // Expose the protected methods to be tested.
    using StateModel::runModel;
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
};

/// @brief Defines a pointer to a NameChangeStubPtr instance.
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

/// @brief Tests event and state dictionary construction and verification.
TEST_F(NameChangeTransactionTest, dictionaryCheck) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Verify that the event and state dictionary validation fails prior
    // dictionary construction.
    ASSERT_THROW(name_change->verifyEvents(), StateModelError);
    ASSERT_THROW(name_change->verifyStates(), StateModelError);

    // Construct both dictionaries.
    ASSERT_NO_THROW(name_change->defineEvents());
    ASSERT_NO_THROW(name_change->defineStates());

    // Verify both event and state dictionaries now pass validation.
    ASSERT_NO_THROW(name_change->verifyEvents());
    ASSERT_NO_THROW(name_change->verifyStates());
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

/// @brief Tests that the transaction will be "failed" upon model errors.
TEST_F(NameChangeTransactionTest, modelFailure) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Now call runModel() with an undefined event which should not throw,
    // but should result in a failed model and failed transaction.
    EXPECT_NO_THROW(name_change->runModel(9999));

    // Verify that the model reports are done but failed.
    EXPECT_TRUE(name_change->isModelDone());
    EXPECT_TRUE(name_change->didModelFail());

    // Verify that the transaction has failed.
    EXPECT_EQ(dhcp_ddns::ST_FAILED, name_change->getNcrStatus());
}

/// @brief Tests the ability to use startTransaction to initate the state
/// model execution, and DNSClient callback, operator(), to resume the
/// the model with a update successful outcome.
TEST_F(NameChangeTransactionTest, successfulUpdateTest) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    EXPECT_TRUE(name_change->isModelNew());
    EXPECT_FALSE(name_change->getForwardChangeCompleted());

    // Launch the transaction by calling startTransaction.  The state model
    // should run up until the "IO" operation is initiated in DOING_UPDATE_ST.
    ASSERT_NO_THROW(name_change->startTransaction());

    // Verify that the model is running but waiting, and that forward change
    // completion is still false.
    EXPECT_TRUE(name_change->isModelRunning());
    EXPECT_TRUE(name_change->isModelWaiting());
    EXPECT_FALSE(name_change->getForwardChangeCompleted());

    // Simulate completion of DNSClient exchange by invoking the callback, as
    // DNSClient would.  This should cause the state model to progress through
    // completion.
    EXPECT_NO_THROW((*name_change)(DNSClient::SUCCESS));

    // The model should have worked through to completion.
    // Verify that the model is done and not failed.
    EXPECT_TRUE(name_change->isModelDone());
    EXPECT_FALSE(name_change->didModelFail());

    // Verify that NCR status is completed, and that the forward change
    // was completed.
    EXPECT_EQ(dhcp_ddns::ST_COMPLETED, name_change->getNcrStatus());
    EXPECT_TRUE(name_change->getForwardChangeCompleted());
}

/// @brief Tests the ability to use startTransaction to initate the state
/// model execution, and DNSClient callback, operator(), to resume the
/// the model with a update failure outcome.
TEST_F(NameChangeTransactionTest, failedUpdateTest) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Launch the transaction by calling startTransaction.  The state model
    // should run up until the "IO" operation is initiated in DOING_UPDATE_ST.
    ASSERT_NO_THROW(name_change->startTransaction());

    // Vefity that the model is running but waiting, and that the forward
    // change has not been completed.
    EXPECT_TRUE(name_change->isModelRunning());
    EXPECT_TRUE(name_change->isModelWaiting());
    EXPECT_FALSE(name_change->getForwardChangeCompleted());

    // Simulate completion of DNSClient exchange by invoking the callback, as
    // DNSClient would.  This should cause the state model to progress through
    // to completion.
    EXPECT_NO_THROW((*name_change)(DNSClient::TIMEOUT));

    // The model should have worked through to completion.
    // Verify that the model is done and not failed.
    EXPECT_TRUE(name_change->isModelDone());
    EXPECT_FALSE(name_change->didModelFail());

    // Verify that the NCR status is failed and that the forward change
    // was not completed.
    EXPECT_EQ(dhcp_ddns::ST_FAILED, name_change->getNcrStatus());
    EXPECT_FALSE(name_change->getForwardChangeCompleted());
}

}
