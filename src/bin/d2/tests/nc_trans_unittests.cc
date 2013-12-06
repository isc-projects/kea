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

#include <asiolink/interval_timer.h>
#include <d2/nc_trans.h>
#include <dns/opcode.h>
#include <dns/messagerenderer.h>
#include <log/logger_support.h>
#include <log/macros.h>
#include <util/buffer.h>
#include <nc_test_utils.h>

#include <asio/ip/udp.hpp>
#include <asio/socket_base.hpp>
#include <asio.hpp>
#include <asio/error_code.hpp>

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
    static const int DOING_UPDATE_ST = NCT_DERIVED_STATE_MIN + 1;

    // NameChangeStub events
    static const int SEND_UPDATE_EVT = NCT_DERIVED_EVENT_MIN + 2;

    bool use_stub_callback_;

    /// @brief Constructor
    ///
    /// Parameters match those needed by NameChangeTransaction.
    NameChangeStub(IOServicePtr& io_service,
                   dhcp_ddns::NameChangeRequestPtr& ncr,
                   DdnsDomainPtr forward_domain,
                   DdnsDomainPtr reverse_domain)
        : NameChangeTransaction(io_service, ncr, forward_domain,
                                reverse_domain),
                                use_stub_callback_(false) {
    }

    /// @brief Destructor
    virtual ~NameChangeStub() {
    }

    /// @brief DNSClient callback
    /// Overrides the callback in NameChangeTranscation to allow testing
    /// sendUpdate without incorporating exectution of the state model
    /// into the test.
    /// It sets the DNS status update and posts IO_COMPLETED_EVT as does
    /// the normal callback, but rather than invoking runModel it stops
    /// the IO service.  This allows tests to be constructed that consisted
    /// of generating a DNS request and invoking sendUpdate to post it and
    /// wait for response.
    virtual void operator()(DNSClient::Status status) {
        if (use_stub_callback_) {
            setDnsUpdateStatus(status);
            postNextEvent(IO_COMPLETED_EVT);
            getIOService()->stop();
        } else {
            // For tests which need to use the real callback.
            NameChangeTransaction::operator()(status);
        }
    }

    /// @brief Some tests require a server to be selected.  This method
    /// selects the first server in the forward domain without involving
    /// state model execution to do so.
    bool selectFwdServer() {
        if (getForwardDomain()) {
            initServerSelection(getForwardDomain());
            selectNextServer();
            return (getCurrentServer());
        }

        return (false);
    }

    /// @brief Empty handler used to satisfy map verification.
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

        // Check our states.
        getState(DOING_UPDATE_ST);
    }

    // Expose the protected methods to be tested.
    using StateModel::runModel;
    using StateModel::postNextEvent;
    using StateModel::setState;
    using StateModel::initDictionaries;
    using NameChangeTransaction::initServerSelection;
    using NameChangeTransaction::selectNextServer;
    using NameChangeTransaction::getCurrentServer;
    using NameChangeTransaction::getDNSClient;
    using NameChangeTransaction::setNcrStatus;
    using NameChangeTransaction::setDnsUpdateRequest;
    using NameChangeTransaction::clearDnsUpdateRequest;
    using NameChangeTransaction::setDnsUpdateStatus;
    using NameChangeTransaction::getDnsUpdateResponse;
    using NameChangeTransaction::setDnsUpdateResponse;
    using NameChangeTransaction::clearDnsUpdateResponse;
    using NameChangeTransaction::getForwardChangeCompleted;
    using NameChangeTransaction::getReverseChangeCompleted;
    using NameChangeTransaction::setForwardChangeCompleted;
    using NameChangeTransaction::setReverseChangeCompleted;
    using NameChangeTransaction::setUpdateAttempts;
    using NameChangeTransaction::transition;
    using NameChangeTransaction::retryTransition;
    using NameChangeTransaction::sendUpdate;
    using NameChangeTransaction::prepNewRequest;
    using NameChangeTransaction::addLeaseAddressRdata;
    using NameChangeTransaction::addDhcidRdata;
    using NameChangeTransaction::addPtrRdata;
};

// Declare them so Gtest can see them.
const int NameChangeStub::DOING_UPDATE_ST;
const int NameChangeStub::SEND_UPDATE_EVT;

/// @brief Defines a pointer to a NameChangeStubPtr instance.
typedef boost::shared_ptr<NameChangeStub> NameChangeStubPtr;

/// @brief Test fixture for testing NameChangeTransaction
///
/// Note this class uses NameChangeStub class to exercise non-public
/// aspects of NameChangeTransaction.
class NameChangeTransactionTest : public ::testing::Test {
public:
    IOServicePtr io_service_;
    DdnsDomainPtr forward_domain_;
    DdnsDomainPtr reverse_domain_;
    asiolink::IntervalTimer timer_;
    int run_time_;

    NameChangeTransactionTest()
        : io_service_(new isc::asiolink::IOService()), timer_(*io_service_),
         run_time_(0) {
    }

    virtual ~NameChangeTransactionTest() {
    }

    /// @brief Run the IO service for no more than a given amount of time.
    ///
    /// Uses an IntervalTimer to interrupt the invocation of IOService run(),
    /// after the given number of milliseconds elapse.  The timer executes
    /// the timesUp() method if it expires.
    ///
    /// @param run_time amount of time in milliseconds to allow run to execute.
    void runTimedIO(int run_time) {
        run_time_ = run_time;
        timer_.setup(boost::bind(&NameChangeTransactionTest::timesUp, this),
                     run_time_);
        io_service_->run();
    }

    /// @brief IO Timer expiration handler
    ///
    /// Stops the IOSerivce and fails the current test.
    void timesUp() {
        io_service_->stop();
        FAIL() << "Test Time: " << run_time_ << " expired";
    }

    /// @brief  Instantiates a NameChangeStub test transaction
    /// The transaction is constructed around a predefined (i.e "canned")
    /// NameChangeRequest. The request has both forward and reverse DNS
    /// changes requested, and both forward and reverse domains are populated.
    NameChangeStubPtr makeCannedTransaction() {
        // NCR in JSON form.
        const char* msg_str =
            "{"
            " \"change_type\" : 0 , "
            " \"forward_change\" : true , "
            " \"reverse_change\" : true , "
            " \"fqdn\" : \"my.example.com.\" , "
            " \"ip_address\" : \"192.168.2.1\" , "
            " \"dhcid\" : \"0102030405060708\" , "
            " \"lease_expires_on\" : \"20130121132405\" , "
            " \"lease_length\" : 1300 "
            "}";

        // Create the request from JSON.
        dhcp_ddns::NameChangeRequestPtr ncr = dhcp_ddns::NameChangeRequest::
                                              fromJSON(msg_str);

        // Make forward DdnsDomain with 2 forward servers.
        forward_domain_ = makeDomain("example.com.");
        addDomainServer(forward_domain_, "forward.example.com",
                        "127.0.0.1", 5301);
        addDomainServer(forward_domain_, "forward2.example.com",
                        "127.0.0.1", 5302);

        // Make reverse DdnsDomain with one reverse server.
        reverse_domain_ = makeDomain("2.168.192.in.addr.arpa.");
        addDomainServer(reverse_domain_, "reverse.example.com",
                        "127.0.0.1", 5301);

        // Instantiate the transaction as would be done by update manager.
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
    IOServicePtr io_service(new isc::asiolink::IOService());

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

    // Verify that construction with a null IOServicePtr fails.
    // @todo Subject to change if multi-threading is implemented.
    IOServicePtr empty;
    EXPECT_THROW(NameChangeTransaction(empty, ncr,
                                       forward_domain, reverse_domain),
                                       NameChangeTransactionError);

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

    // Verify that the forward change complete flag can be set and fetched.
    EXPECT_NO_THROW(name_change->setForwardChangeCompleted(true));
    EXPECT_TRUE(name_change->getForwardChangeCompleted());

    // Verify that the reverse change complete flag can be set and fetched.
    EXPECT_NO_THROW(name_change->setReverseChangeCompleted(true));
    EXPECT_TRUE(name_change->getReverseChangeCompleted());
}

/// @brief Tests DNS update request accessor methods.
TEST_F(NameChangeTransactionTest, dnsUpdateRequestAccessors) {
    // Create a transaction.
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Post transaction construction, there should not be an update request.
    EXPECT_FALSE(name_change->getDnsUpdateRequest());

    // Create a request.
    D2UpdateMessagePtr req;
    ASSERT_NO_THROW(req.reset(new D2UpdateMessage(D2UpdateMessage::OUTBOUND)));

    // Use the setter and then verify we can fetch the request.
    ASSERT_NO_THROW(name_change->setDnsUpdateRequest(req));

    // Post set, we should be able to fetch it.
    ASSERT_TRUE(name_change->getDnsUpdateRequest());

    // Should be able to clear it.
    ASSERT_NO_THROW(name_change->clearDnsUpdateRequest());

    // Should be empty again.
    EXPECT_FALSE(name_change->getDnsUpdateRequest());
}

/// @brief Tests DNS update request accessor methods.
TEST_F(NameChangeTransactionTest, dnsUpdateResponseAccessors) {
    // Create a transaction.
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Post transaction construction, there should not be an update response.
    EXPECT_FALSE(name_change->getDnsUpdateResponse());

    // Create a response.
    D2UpdateMessagePtr resp;
    ASSERT_NO_THROW(resp.reset(new D2UpdateMessage(D2UpdateMessage::INBOUND)));

    // Use the setter and then verify we can fetch the response.
    ASSERT_NO_THROW(name_change->setDnsUpdateResponse(resp));

    // Post set, we should be able to fetch it.
    EXPECT_TRUE(name_change->getDnsUpdateResponse());

    // Should be able to clear it.
    ASSERT_NO_THROW(name_change->clearDnsUpdateResponse());

    // Should be empty again.
    EXPECT_FALSE(name_change->getDnsUpdateResponse());
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

/// @brief Tests the ability to use startTransaction to initiate the state
/// model execution, and DNSClient callback, operator(), to resume the
/// model with a update successful outcome.
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
/// model with a update failure outcome.
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

/// @brief Tests update attempt accessors.
TEST_F(NameChangeTransactionTest, updateAttempts) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Post transaction construction, update attempts should be 0.
    EXPECT_EQ(0, name_change->getUpdateAttempts());

    // Set it to a known value.
    name_change->setUpdateAttempts(5);

    // Verify that the value is as expected.
    EXPECT_EQ(5, name_change->getUpdateAttempts());
}

/// @brief Tests retryTransition method
///
/// Verifies that while the maximum number of update attempts has not
/// been exceeded, the method will leave the state unchanged but post a
/// SERVER_SELECTED_EVT.  Once the maximum is exceeded, the method should
/// transition to the state given with a next event of SERVER_IO_ERROR_EVT.
TEST_F(NameChangeTransactionTest, retryTransition) {
    // Create the transaction.
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());

    // Define dictionaries.
    ASSERT_NO_THROW(name_change->initDictionaries());

    // Transition to a known spot.
    ASSERT_NO_THROW(name_change->transition(
                    NameChangeStub::DOING_UPDATE_ST,
                    NameChangeStub::SEND_UPDATE_EVT));

    // Verify we are at the known spot.
    ASSERT_EQ(NameChangeStub::DOING_UPDATE_ST,
              name_change->getCurrState());
    ASSERT_EQ(NameChangeStub::SEND_UPDATE_EVT,
              name_change->getNextEvent());

    // Verify that we have not exceeded maximum number of attempts.
    ASSERT_LT(name_change->getUpdateAttempts(),
              NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER);

    // Call retryTransition.
    ASSERT_NO_THROW(name_change->retryTransition(
                    NameChangeTransaction::PROCESS_TRANS_FAILED_ST));

    // Since the number of update attempts is less than the maximum allowed
    // we should remain in our current state but with next event of
    // SERVER_SELECTED_EVT posted.
    ASSERT_EQ(NameChangeStub::DOING_UPDATE_ST,
              name_change->getCurrState());
    ASSERT_EQ(NameChangeTransaction::SERVER_SELECTED_EVT,
              name_change->getNextEvent());

    // Now set the number of attempts to the maximum.
    name_change->setUpdateAttempts(NameChangeTransaction::
                                   MAX_UPDATE_TRIES_PER_SERVER);
    // Call retryTransition.
    ASSERT_NO_THROW(name_change->retryTransition(
                    NameChangeTransaction::PROCESS_TRANS_FAILED_ST));

    // Since we have exceeded maximum attempts, we should transition to
    // PROCESS_UPDATE_FAILED_ST with a next event of SERVER_IO_ERROR_EVT.
    ASSERT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_change->getCurrState());
    ASSERT_EQ(NameChangeTransaction::SERVER_IO_ERROR_EVT,
              name_change->getNextEvent());
}

/// @brief Tests sendUpdate method when underlying doUpdate throws.
///
/// DNSClient::doUpdate can throw for a variety of reasons. This tests
/// sendUpdate handling of such a throw by passing doUpdate a request
/// that will not render.
TEST_F(NameChangeTransactionTest, sendUpdateDoUpdateFailure) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());
    ASSERT_NO_THROW(name_change->initDictionaries());
    ASSERT_TRUE(name_change->selectFwdServer());

    // Set the transaction's request to an empty DNS update.
    D2UpdateMessagePtr req;
    ASSERT_NO_THROW(req.reset(new D2UpdateMessage(D2UpdateMessage::OUTBOUND)));
    ASSERT_NO_THROW(name_change->setDnsUpdateRequest(req));

    // Verify that sendUpdate does not throw, but it should fail because
    // the request won't render.
    ASSERT_NO_THROW(name_change->sendUpdate());

    // Verify that we transition to failed state and event.
    ASSERT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              name_change->getCurrState());
    ASSERT_EQ(NameChangeTransaction::UPDATE_FAILED_EVT,
              name_change->getNextEvent());
}

/// @brief Tests sendUpdate method when underlying doUpdate times out.
TEST_F(NameChangeTransactionTest, sendUpdateTimeout) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());
    ASSERT_NO_THROW(name_change->initDictionaries());
    ASSERT_TRUE(name_change->selectFwdServer());

    // Create a valid request.
    D2UpdateMessagePtr req;
    ASSERT_NO_THROW(req.reset(new D2UpdateMessage(D2UpdateMessage::OUTBOUND)));
    ASSERT_NO_THROW(name_change->setDnsUpdateRequest(req));
    req->setZone(dns::Name("request.example.com"), dns::RRClass::ANY());
    req->setRcode(dns::Rcode(dns::Rcode::NOERROR_CODE));

    // Set the flag to use the NameChangeStub's DNSClient callback.
    name_change->use_stub_callback_ = true;

    // Invoke sendUpdate.
    ASSERT_NO_THROW(name_change->sendUpdate());

    // Update attempt count should be 1, next event should be NOP_EVT.
    EXPECT_EQ(1, name_change->getUpdateAttempts());
    ASSERT_EQ(NameChangeTransaction::NOP_EVT,
              name_change->getNextEvent());

    // Run IO a bit longer than maximum allowed to permit timeout logic to
    // execute.
    runTimedIO(NameChangeTransaction::DNS_UPDATE_DEFAULT_TIMEOUT + 100);

    // Verify that next event is IO_COMPLETED_EVT and DNS status is TIMEOUT.
    ASSERT_EQ(NameChangeTransaction::IO_COMPLETED_EVT,
              name_change->getNextEvent());
    ASSERT_EQ(DNSClient::TIMEOUT, name_change->getDnsUpdateStatus());
}

/// @brief Tests sendUpdate method when it receives a corrupt response from
/// the server.
TEST_F(NameChangeTransactionTest, sendUpdateCorruptResponse) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());
    ASSERT_NO_THROW(name_change->initDictionaries());
    ASSERT_TRUE(name_change->selectFwdServer());

    // Create a server and start it listening.
    FauxServer server(*io_service_, *(name_change->getCurrentServer()));
    server.receive(FauxServer::CORRUPT_RESP);

    // Create a valid request for the transaction.
    D2UpdateMessagePtr req;
    ASSERT_NO_THROW(req.reset(new D2UpdateMessage(D2UpdateMessage::OUTBOUND)));
    ASSERT_NO_THROW(name_change->setDnsUpdateRequest(req));
    req->setZone(dns::Name("request.example.com"), dns::RRClass::ANY());
    req->setRcode(dns::Rcode(dns::Rcode::NOERROR_CODE));

    // Set the flag to use the NameChangeStub's DNSClient callback.
    name_change->use_stub_callback_ = true;

    // Invoke sendUpdate.
    ASSERT_NO_THROW(name_change->sendUpdate());

    // Update attempt count should be 1, next event should be NOP_EVT.
    EXPECT_EQ(1, name_change->getUpdateAttempts());
    ASSERT_EQ(NameChangeTransaction::NOP_EVT,
              name_change->getNextEvent());

    // Run the IO for 500 ms.  This should be more than enough time.
    runTimedIO(500);

    // Verify that next event is IO_COMPLETED_EVT and DNS status is INVALID.
    ASSERT_EQ(NameChangeTransaction::IO_COMPLETED_EVT,
              name_change->getNextEvent());
    ASSERT_EQ(DNSClient::INVALID_RESPONSE, name_change->getDnsUpdateStatus());
}

/// @brief Tests sendUpdate method when the exchange succeeds.
TEST_F(NameChangeTransactionTest, sendUpdate) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());
    ASSERT_NO_THROW(name_change->initDictionaries());
    ASSERT_TRUE(name_change->selectFwdServer());

    // Create a server and start it listening.
    FauxServer server(*io_service_, *(name_change->getCurrentServer()));
    server.receive (FauxServer::USE_RCODE, dns::Rcode::NOERROR());

    // Create a valid request for the transaction.
    D2UpdateMessagePtr req;
    ASSERT_NO_THROW(req.reset(new D2UpdateMessage(D2UpdateMessage::OUTBOUND)));
    ASSERT_NO_THROW(name_change->setDnsUpdateRequest(req));
    req->setZone(dns::Name("request.example.com"), dns::RRClass::ANY());
    req->setRcode(dns::Rcode(dns::Rcode::NOERROR_CODE));

    // Set the flag to use the NameChangeStub's DNSClient callback.
    name_change->use_stub_callback_ = true;

    // Invoke sendUpdate.
    ASSERT_NO_THROW(name_change->sendUpdate());

    // Update attempt count should be 1, next event should be NOP_EVT.
    EXPECT_EQ(1, name_change->getUpdateAttempts());
    ASSERT_EQ(NameChangeTransaction::NOP_EVT,
              name_change->getNextEvent());

    // Run the IO for 500 ms.  This should be more than enough time.
    runTimedIO(500);

    // Verify that next event is IO_COMPLETED_EVT and DNS status is SUCCESS.
    ASSERT_EQ(NameChangeTransaction::IO_COMPLETED_EVT,
              name_change->getNextEvent());
    ASSERT_EQ(DNSClient::SUCCESS, name_change->getDnsUpdateStatus());

    // Verify that we have a response and it's Rcode is NOERROR,
    // and the zone is as expected.
    D2UpdateMessagePtr response = name_change->getDnsUpdateResponse();
    ASSERT_TRUE(response);
    ASSERT_EQ(dns::Rcode::NOERROR().getCode(), response->getRcode().getCode());
    D2ZonePtr zone = response->getZone();
    EXPECT_TRUE(zone);
    EXPECT_EQ("response.example.com.", zone->getName().toText());
}

/// @brief Tests the prepNewRequest method
TEST_F(NameChangeTransactionTest, prepNewRequest) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());
    D2UpdateMessagePtr request;

    // prepNewRequest should fail on empty domain.
    ASSERT_THROW(request = name_change->prepNewRequest(DdnsDomainPtr()),
        NameChangeTransactionError);

    // Verify that prepNewRequest fails on invalid zone name.
    // @todo This test becomes obsolete if/when DdnsDomain enforces valid
    // names as is done in dns::Name.
    DdnsDomainPtr bsDomain = makeDomain(".badname","");
    ASSERT_THROW(request = name_change->prepNewRequest(bsDomain),
        NameChangeTransactionError);

    // Verify that prepNewRequest properly constructs a message given
    // valid input.
    ASSERT_NO_THROW(request = name_change->prepNewRequest(forward_domain_));
    checkZone(request, forward_domain_->getName());
}

/// @brief Tests the addLeaseAddressRData method
TEST_F(NameChangeTransactionTest, addLeaseAddressRData) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());
    dhcp_ddns::NameChangeRequestPtr ncr = name_change->getNcr();

    // Test a lease rdata add failure.
    // As you cannot stuff an invalid address into an NCR, the only failure
    // that can be induced is a mismatch between the RData and the RRset.
    // Attempt to add a lease address Rdata, this should fail.
    // Create an Any class/Any type RRset, they are not allowed to contain
    // rdata.
    dns::RRsetPtr rrset(new dns::RRset(dns::Name("bs"), dns::RRClass::ANY(),
                         dns::RRType::ANY(), dns::RRTTL(0)));
    ASSERT_THROW(name_change->addLeaseAddressRdata(rrset), std::exception);

    // Verify we can add a lease RData to an valid RRset.
    rrset.reset(new dns::RRset(dns::Name("bs"), dns::RRClass::IN(),
                               name_change->getAddressRRType(), dns::RRTTL(0)));
    ASSERT_NO_THROW(name_change->addLeaseAddressRdata(rrset));

    // Verify the Rdata was added and the value is correct.
    ASSERT_EQ(1, rrset->getRdataCount());
    dns::RdataIteratorPtr rdata_it = rrset->getRdataIterator();
    ASSERT_TRUE(rdata_it);
    EXPECT_EQ(ncr->getIpAddress(), rdata_it->getCurrent().toText());

}

/// @brief Tests the addDhcidRData method
TEST_F(NameChangeTransactionTest, addDhcidRdata) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());
    dhcp_ddns::NameChangeRequestPtr ncr = name_change->getNcr();

    // Test a DHCID rdata add failure.
    dns::RRsetPtr rrset(new dns::RRset(dns::Name("bs"), dns::RRClass::ANY(),
                         dns::RRType::ANY(), dns::RRTTL(0)));
    ASSERT_THROW(name_change->addDhcidRdata(rrset), std::exception);

    // Verify we can add a lease RData to an valid RRset.
    rrset.reset(new dns::RRset(dns::Name("bs"), dns::RRClass::IN(),
                               dns::RRType::DHCID(), dns::RRTTL(0)));
    ASSERT_NO_THROW(name_change->addDhcidRdata(rrset));

    // Verify the Rdata was added and the value is correct.
    ASSERT_EQ(1, rrset->getRdataCount());
    dns::RdataIteratorPtr rdata_it = rrset->getRdataIterator();
    ASSERT_TRUE(rdata_it);

    const std::vector<uint8_t>& ncr_dhcid = ncr->getDhcid().getBytes();
    util::InputBuffer buffer(ncr_dhcid.data(), ncr_dhcid.size());
    dns::rdata::in::DHCID rdata_ref(buffer, ncr_dhcid.size());
    EXPECT_EQ(0, rdata_ref.compare(rdata_it->getCurrent()));
}

/// @brief Tests the addPtrData method
TEST_F(NameChangeTransactionTest, addPtrRdata) {
    NameChangeStubPtr name_change;
    ASSERT_NO_THROW(name_change = makeCannedTransaction());
    dhcp_ddns::NameChangeRequestPtr ncr = name_change->getNcr();

    // Test a PTR rdata add failure.
    dns::RRsetPtr rrset(new dns::RRset(dns::Name("bs"), dns::RRClass::ANY(),
                         dns::RRType::ANY(), dns::RRTTL(0)));
    ASSERT_THROW(name_change->addPtrRdata(rrset), std::exception);

    // Verify we can add a PTR RData to an valid RRset.
    rrset.reset(new dns::RRset(dns::Name("bs"), dns::RRClass::IN(),
                               dns::RRType::PTR(), dns::RRTTL(0)));
    ASSERT_NO_THROW(name_change->addPtrRdata(rrset));

    // Verify the Rdata was added and the value is correct.
    ASSERT_EQ(1, rrset->getRdataCount());
    dns::RdataIteratorPtr rdata_it = rrset->getRdataIterator();
    ASSERT_TRUE(rdata_it);

    EXPECT_EQ(ncr->getFqdn(), rdata_it->getCurrent().toText());
}

}; // anonymous namespace
