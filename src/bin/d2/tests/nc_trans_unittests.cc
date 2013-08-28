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
/// This class faciliates testing by making non-public methods accessible so
/// they can be invoked directly in test routines.  It implements a very
/// rudimentary state model, sufficient to test the state model mechanics
/// supplied by the base class.
class NameChangeStub : public NameChangeTransaction {
public:

    // NameChangeStub states
    static const int DO_WORK_ST = DERIVED_STATES + 1;

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
                                reverse_domain) {
    }

    /// @brief Destructor
    virtual ~NameChangeStub() {
    }

    /// @brief State handler for the READY_ST.
    ///
    /// Serves as the starting state handler, it consumes the
    /// START_TRANSACTION_EVT "transitioing" to the state, DO_WORK_ST and
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
    /// When next event is START_WROK_EVT it sets the status to pending
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
            " \"fqdn\" : \"walah.walah.org.\" , "
            " \"ip_address\" : \"192.168.2.1\" , "
            " \"dhcid\" : \"0102030405060708\" , "
            " \"lease_expires_on\" : \"20130121132405\" , "
            " \"lease_length\" : 1300 "
            "}";

        dhcp_ddns::NameChangeRequestPtr ncr;

        DnsServerInfoStoragePtr servers(new DnsServerInfoStorage());
        DnsServerInfoPtr server;

        DdnsDomainPtr forward_domain;
        DdnsDomainPtr reverse_domain;

        ncr = dhcp_ddns::NameChangeRequest::fromJSON(msg_str);

        // make forward server list
        server.reset(new DnsServerInfo("forward.server.org",
                                       isc::asiolink::IOAddress("1.1.1.1")));
        servers->push_back(server);
        forward_domain.reset(new DdnsDomain("*", "", servers));

        // make reverse server list
        servers->clear();
        server.reset(new DnsServerInfo("reverse.server.org",
                                       isc::asiolink::IOAddress("2.2.2.2")));
        servers->push_back(server);
        reverse_domain.reset(new DdnsDomain("*", "", servers));
        return (NameChangeStubPtr(new NameChangeStub(io_service_, ncr,
                                  forward_domain, reverse_domain)));

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
        " \"fqdn\" : \"walah.walah.org.\" , "
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
    // include a forward change.
    ncr->setForwardChange(false);
    EXPECT_NO_THROW(NameChangeTransaction(io_service, ncr,
                                          empty_domain, reverse_domain));

    // Verify that an empty reverse domain is allowed when the requests does
    // include a reverse change.
    ncr->setReverseChange(false);
    EXPECT_NO_THROW(NameChangeTransaction(io_service, ncr,
                                          empty_domain, empty_domain));
}

/// @brief Test the basic mechanics of state model execution.
/// It first verifies basic state handle map fucntionality, and then
/// runs the NameChangeStub state model through from start to finish.
TEST_F(NameChangeTransactionTest, stateModelTest) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Verify that getStateHandler will throw when, handler map is empty.
    EXPECT_THROW(name_change->getStateHandler(NameChangeTransaction::READY_ST),
                 NameChangeTransactionError);

    // Verify that we can add a handler to the map.
    ASSERT_NO_THROW(name_change->addToMap(NameChangeTransaction::READY_ST,
                           boost::bind(&NameChangeStub::readyHandler,
                                       name_change.get())));

    // Verify that we can find the handler by its state.
    EXPECT_NO_THROW(name_change->getStateHandler(NameChangeTransaction::
                                                 READY_ST));

    // Verify that we cannot add a duplicate.
    EXPECT_THROW(name_change->addToMap(NameChangeTransaction::READY_ST,
                           boost::bind(&NameChangeStub::readyHandler,
                                       name_change.get())),
                 NameChangeTransactionError);

    // Verify that we can still find the handler by its state.
    EXPECT_NO_THROW(name_change->getStateHandler(NameChangeTransaction::
                                                 READY_ST));


    // Get a fresh transaction.
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Manually call checkHandlerMap to ensure our test map populates.
    // This is the method startTranscation invokes.
    ASSERT_NO_THROW(name_change->initStateHandlerMap());

    // Verify that we can find all the handlers by their state.
    EXPECT_NO_THROW(name_change->getStateHandler(NameChangeTransaction::
                                                 READY_ST));
    EXPECT_NO_THROW(name_change->getStateHandler(NameChangeStub::DO_WORK_ST));
    EXPECT_NO_THROW(name_change->getStateHandler(NameChangeTransaction::
                                                 DONE_ST));


    // Default value for state is NEW_ST.  Attempting to run the model
    // with an invalid state will result in status of ST_FAILED.
    ASSERT_EQ(NameChangeTransaction::NEW_ST, name_change->getState());
    EXPECT_NO_THROW(name_change->runStateModel(NameChangeTransaction::
                                               START_TRANSACTION_EVT));

    EXPECT_EQ(dhcp_ddns::ST_FAILED, name_change->getNcrStatus());

    // Get a fresh transaction.
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Launch the transaction properly by calling startTranscation.
    // Verify that this transitions through to state of DO_WORK_ST,
    // last event is START_WORK_EVT, next event is NOP_EVT, and
    // NCR status is ST_PENDING.
    ASSERT_NO_THROW(name_change->startTransaction());

    EXPECT_EQ(NameChangeStub::DO_WORK_ST, name_change->getState());
    EXPECT_EQ(NameChangeStub::START_WORK_EVT, name_change->getLastEvent());
    EXPECT_EQ(NameChangeTransaction::NOP_EVT, name_change->getNextEvent());
    EXPECT_EQ(dhcp_ddns::ST_PENDING, name_change->getNcrStatus());

    // Simulate completion of DNSClient exchange by invoking the callback.
    EXPECT_NO_THROW((*name_change)(DNSClient::SUCCESS));

    // Verify that the state model has progressed through to completion:
    // it is in the DONE_ST, the status is ST_COMPLETED, and the next event
    // is NOP_EVT.
    EXPECT_EQ(NameChangeTransaction::DONE_ST, name_change->getState());
    EXPECT_EQ(dhcp_ddns::ST_COMPLETED, name_change->getNcrStatus());
    EXPECT_EQ(NameChangeTransaction::NOP_EVT, name_change->getNextEvent());
}

/// @brief Tests server selection methods
TEST_F(NameChangeTransactionTest, serverSelectionTest) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Verify that the forward domain and its servers can be retrieved.
    DdnsDomainPtr& domain = name_change->getForwardDomain();
    ASSERT_TRUE(domain);
    DnsServerInfoStoragePtr servers = domain->getServers();
    ASSERT_TRUE(servers);

    // Get the number of entries in the server list.
    int num_servers = servers->size();
    ASSERT_TRUE(num_servers > 0);

    ASSERT_NO_THROW(name_change->initServerSelection(domain));

    DNSClientPtr prev_client = name_change->getDNSClient();
    D2UpdateMessagePtr prev_response = name_change->getDnsUpdateResponse();
    DnsServerInfoPtr prev_server = name_change->getCurrentServer();

    // Iteratively select through the list of servers.
    int passes = 0;
    while (name_change->selectNextServer()) {
        DnsServerInfoPtr server = name_change->getCurrentServer();
        DNSClientPtr client = name_change->getDNSClient();
        D2UpdateMessagePtr response = name_change->getDnsUpdateResponse();
        EXPECT_TRUE(server);
        EXPECT_TRUE(client);
        EXPECT_TRUE(response);

        EXPECT_NE(server, prev_server);
        EXPECT_NE(client, prev_client);
        EXPECT_NE(response, prev_response);

        prev_server = server;
        prev_client = client;
        prev_response = response;

        passes++;
    }

    // Verify that the numer of passes made equal the number of servers.
    EXPECT_EQ (passes, num_servers);

    // Repeat the same test using the reverse domain.
    domain = name_change->getReverseDomain();
    ASSERT_TRUE(domain);

    servers = domain->getServers();
    ASSERT_TRUE(servers);

    num_servers = servers->size();
    ASSERT_TRUE(num_servers > 0);

    ASSERT_NO_THROW(name_change->initServerSelection(domain));

    prev_client = name_change->getDNSClient();
    prev_response = name_change->getDnsUpdateResponse();
    prev_server = name_change->getCurrentServer();

    passes = 0;
    while (name_change->selectNextServer()) {
        DnsServerInfoPtr server = name_change->getCurrentServer();
        DNSClientPtr client = name_change->getDNSClient();
        D2UpdateMessagePtr response = name_change->getDnsUpdateResponse();
        EXPECT_TRUE(server);
        EXPECT_TRUE(client);
        EXPECT_TRUE(response);

        EXPECT_NE(server, prev_server);
        EXPECT_NE(client, prev_client);
        EXPECT_NE(response, prev_response);

        prev_server = server;
        prev_client = client;
        prev_response = response;

        passes++;
    }

    EXPECT_EQ (passes, num_servers);
}

}
