// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service.h>
#include <d2/d2_update_mgr.h>
#include <util/time_utilities.h>
#include <d_test_stubs.h>
#include <nc_test_utils.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <gtest/gtest.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

using namespace std;
using namespace isc;
using namespace isc::dhcp_ddns;
using namespace isc::d2;

namespace {

/// @brief Wrapper class for D2UpdateMgr providing access to non-public methods.
///
/// This class facilitates testing by making non-public methods accessible so
/// they can be invoked directly in test routines.
class D2UpdateMgrWrapper : public D2UpdateMgr {
public:
    /// @brief Constructor
    ///
    /// Parameters match those needed by D2UpdateMgr.
    D2UpdateMgrWrapper(D2QueueMgrPtr& queue_mgr, D2CfgMgrPtr& cfg_mgr,
                       asiolink::IOServicePtr& io_service,
                       const size_t max_transactions = MAX_TRANSACTIONS_DEFAULT)
        : D2UpdateMgr(queue_mgr, cfg_mgr, io_service, max_transactions) {
    }

    /// @brief Destructor
    virtual ~D2UpdateMgrWrapper() {
    }

    // Expose the protected methods to be tested.
    using D2UpdateMgr::checkFinishedTransactions;
    using D2UpdateMgr::pickNextJob;
    using D2UpdateMgr::makeTransaction;
};

/// @brief Defines a pointer to a D2UpdateMgr instance.
typedef boost::shared_ptr<D2UpdateMgrWrapper> D2UpdateMgrWrapperPtr;

/// @brief Test fixture for testing D2UpdateMgr.
///
/// Note this class uses D2UpdateMgrWrapper class to exercise non-public
/// aspects of D2UpdateMgr. D2UpdateMgr depends on both D2QueueMgr and
/// D2CfgMgr.  This fixture provides an instance of each, plus a canned,
/// valid DHCP_DDNS configuration sufficient to test D2UpdateMgr's basic
/// functions.
class D2UpdateMgrTest : public TimedIO, public ConfigParseTest {
public:
    D2QueueMgrPtr queue_mgr_;
    D2CfgMgrPtr cfg_mgr_;
    D2UpdateMgrWrapperPtr update_mgr_;
    std::vector<NameChangeRequestPtr> canned_ncrs_;
    size_t canned_count_;

    D2UpdateMgrTest() {
        queue_mgr_.reset(new D2QueueMgr(io_service_));
        cfg_mgr_.reset(new D2CfgMgr());
        update_mgr_.reset(new D2UpdateMgrWrapper(queue_mgr_, cfg_mgr_,
                                                 io_service_));
        makeCannedNcrs();
        makeCannedConfig();
    }

    ~D2UpdateMgrTest() {
    }

    /// @brief Creates a list of valid NameChangeRequest.
    ///
    /// This method builds a list of NameChangeRequests from a single
    /// JSON string request. Each request is assigned a unique DHCID.
    void makeCannedNcrs() {
        const char* msg_str =
        "{"
        " \"change-type\" : 0 , "
        " \"forward-change\" : true , "
        " \"reverse-change\" : false , "
        " \"fqdn\" : \"my.example.com.\" , "
        " \"ip-address\" : \"192.168.1.2\" , "
        " \"dhcid\" : \"0102030405060708\" , "
        " \"lease-expires-on\" : \"20130121132405\" , "
        " \"lease-length\" : 1300 "
        "}";

        const char* dhcids[] = { "111111", "222222", "333333", "444444"};
        canned_count_ = 4;
        for (int i = 0; i < canned_count_; i++) {
            dhcp_ddns::NameChangeRequestPtr ncr = NameChangeRequest::
                                                  fromJSON(msg_str);
            ncr->setDhcid(dhcids[i]);
            ncr->setChangeType(i % 2 == 0 ?
                               dhcp_ddns::CHG_ADD : dhcp_ddns::CHG_REMOVE);
            canned_ncrs_.push_back(ncr);
        }
    }

    /// @brief Seeds configuration manager with a valid DHCP_DDNS configuration.
    void makeCannedConfig() {
        std::string canned_config_ =
                 "{ "
                  "\"ip-address\" : \"192.168.1.33\" , "
                  "\"port\" : 88 , "
                  "\"tsig-keys\": [] ,"
                  "\"forward-ddns\" : {"
                  "\"ddns-domains\": [ "
                  "{ \"name\": \"example.com.\" , "
                  "  \"dns-servers\" : [ "
                  "  { \"ip-address\": \"127.0.0.1\", \"port\" : 5301  } "
                  "  ] },"
                  "{ \"name\": \"org.\" , "
                  "  \"dns-servers\" : [ "
                  "  { \"ip-address\": \"127.0.0.1\" } "
                  "  ] }, "
                  "] }, "
                  "\"reverse-ddns\" : { "
                  "\"ddns-domains\": [ "
                  "{ \"name\": \"1.168.192.in-addr.arpa.\" , "
                  "  \"dns-servers\" : [ "
                  "  { \"ip-address\": \"127.0.0.1\", \"port\" : 5301 } "
                  "  ] }, "
                  "{ \"name\": \"2.0.3.0.8.B.D.0.1.0.0.2.ip6.arpa.\" , "
                  "  \"dns-servers\" : [ "
                  "  { \"ip-address\": \"127.0.0.1\" } "
                  "  ] } "
                  "] } }";

        // If this configuration fails to parse most tests will fail.
        ASSERT_TRUE(fromJSON(canned_config_));
        answer_ = cfg_mgr_->parseConfig(config_set_);
        ASSERT_TRUE(checkAnswer(0));
    }

    /// @brief Fakes the completion of a given transaction.
    ///
    /// @param index index of the request from which the transaction was formed.
    /// @param status completion status to assign to the request
    void completeTransaction(const size_t index,
                             const dhcp_ddns::NameChangeStatus& status) {
        // add test on index
        if (index >= canned_count_) {
            ADD_FAILURE() << "request index is out of range: " << index;
        }

        const dhcp_ddns::D2Dhcid key = canned_ncrs_[index]->getDhcid();

        // locate the transaction based on the request DHCID
        TransactionList::iterator pos = update_mgr_->findTransaction(key);
        if (pos == update_mgr_->transactionListEnd()) {
            ADD_FAILURE() << "cannot find transaction for key: " << key.toStr();
        }

        NameChangeTransactionPtr trans = (*pos).second;
        // Update the status of the request
        trans->getNcr()->setStatus(status);
        // End the model.
        trans->endModel();
    }

    /// @brief Determines if any transactions are waiting for IO completion.
    ///
    /// @returns True if isModelWaiting() is true for at least one of the current
    /// transactions.
    bool anyoneWaiting() {
        TransactionList::iterator it = update_mgr_->transactionListBegin();
        while (it != update_mgr_->transactionListEnd()) {
            if (((*it).second)->isModelWaiting()) {
                return true;
            }
        }

        return false;
    }

    /// @brief Process events until all requests have been completed.
    ///
    /// This method iteratively calls D2UpdateMgr::sweep and executes
    /// IOService calls until both the request queue and transaction list
    /// are empty or a timeout occurs.  Note that in addition to the safety
    /// timer, the number of passes through the loop is also limited to
    /// a given number.  This is a failsafe to guard against an infinite loop
    /// in the test.
    void processAll(size_t max_passes = 100) {
        // Loop until all the transactions have been dequeued and run through to
        // completion.
        size_t passes = 0;
        size_t handlers = 0;

        // Set the timeout to slightly more than DNSClient timeout to allow
        // timeout processing to occur naturally.
        size_t timeout = cfg_mgr_->getD2Params()->getDnsServerTimeout() + 100;
        while (update_mgr_->getQueueCount() ||
            update_mgr_->getTransactionCount()) {
            ++passes;
            update_mgr_->sweep();
            // If any transactions are waiting on IO, run the service.
            if (anyoneWaiting()) {
                int cnt = runTimedIO(timeout);

                // If cnt is zero then the service stopped unexpectedly.
                if (cnt == 0) {
                    ADD_FAILURE()
                        << "processALL: IO service stopped unexpectedly,"
                        << " passes: " << passes << ", handlers executed: "
                        << handlers;
                }

                handlers += cnt;
            }

            // This is a last resort fail safe to ensure we don't go around
            // forever. We cut it off the number of passes at 100 (default
            // value).  This is roughly ten times the number for the longest
            // test (currently, multiTransactionTimeout).
            if (passes > max_passes) {
                ADD_FAILURE() << "processALL failed, too many passes: "
                    << passes <<  ", total handlers executed: " << handlers;
            }
        }
    }

};

/// @brief Tests the D2UpdateMgr construction.
/// This test verifies that:
/// 1. Construction with invalid queue manager is not allowed
/// 2. Construction with invalid configuration manager is not allowed
/// 3. Construction with max transactions of zero is not allowed
/// 4. Default construction works and max transactions is defaulted properly
/// 5. Construction with custom max transactions works properly
TEST(D2UpdateMgr, construction) {
    asiolink::IOServicePtr io_service(new isc::asiolink::IOService());
    D2QueueMgrPtr queue_mgr;
    D2CfgMgrPtr cfg_mgr;
    D2UpdateMgrPtr update_mgr;

    // Verify that constructor fails if given an invalid queue manager.
    ASSERT_NO_THROW(cfg_mgr.reset(new D2CfgMgr()));
    EXPECT_THROW(D2UpdateMgr(queue_mgr, cfg_mgr, io_service),
                 D2UpdateMgrError);

    // Verify that constructor fails if given an invalid config manager.
    ASSERT_NO_THROW(queue_mgr.reset(new D2QueueMgr(io_service)));
    ASSERT_NO_THROW(cfg_mgr.reset());
    EXPECT_THROW(D2UpdateMgr(queue_mgr, cfg_mgr, io_service),
                 D2UpdateMgrError);

    ASSERT_NO_THROW(cfg_mgr.reset(new D2CfgMgr()));

    // Verify that constructor fails with invalid io_service.
    io_service.reset();
    EXPECT_THROW(D2UpdateMgr(queue_mgr, cfg_mgr, io_service),
                 D2UpdateMgrError);
    io_service.reset(new isc::asiolink::IOService());

    // Verify that max transactions cannot be zero.
    EXPECT_THROW(D2UpdateMgr(queue_mgr, cfg_mgr, io_service, 0),
                 D2UpdateMgrError);

    // Verify that given valid values, constructor works.
    ASSERT_NO_THROW(update_mgr.reset(new D2UpdateMgr(queue_mgr, cfg_mgr,
                                                      io_service)));

    // Verify that max transactions defaults properly.
    EXPECT_EQ(D2UpdateMgr::MAX_TRANSACTIONS_DEFAULT,
              update_mgr->getMaxTransactions());


    // Verify that constructor permits custom  max transactions.
    ASSERT_NO_THROW(update_mgr.reset(new D2UpdateMgr(queue_mgr, cfg_mgr,
                                                     io_service, 100)));

    // Verify that max transactions is correct.
    EXPECT_EQ(100, update_mgr->getMaxTransactions());
}

/// @brief Tests the D2UpdateManager's transaction list services
/// This test verifies that:
/// 1. A transaction can be added to the list.
/// 2. Finding a transaction in the list by key works correctly.
/// 3. Looking for a non-existent transaction works properly.
/// 4. Attempting to add a transaction for a DHCID already in the list fails.
/// 5. Removing a transaction by key works properly.
/// 6. Attempting to remove an non-existent transaction does no harm.
TEST_F(D2UpdateMgrTest, transactionList) {
    // Grab a canned request for test purposes.
    NameChangeRequestPtr& ncr = canned_ncrs_[0];
    TransactionList::iterator pos;

    // Verify that we can add a transaction.
    EXPECT_NO_THROW(update_mgr_->makeTransaction(ncr));
    EXPECT_EQ(1, update_mgr_->getTransactionCount());

    // Verify that we can find a transaction by key.
    EXPECT_NO_THROW(pos = update_mgr_->findTransaction(ncr->getDhcid()));
    EXPECT_TRUE(pos != update_mgr_->transactionListEnd());

    // Verify that convenience method has same result.
    EXPECT_TRUE(update_mgr_->hasTransaction(ncr->getDhcid()));

    // Verify that we will not find a transaction that isn't there.
    dhcp_ddns::D2Dhcid bogus_id("FFFF");
    EXPECT_NO_THROW(pos = update_mgr_->findTransaction(bogus_id));
    EXPECT_TRUE(pos == update_mgr_->transactionListEnd());

    // Verify that convenience method has same result.
    EXPECT_FALSE(update_mgr_->hasTransaction(bogus_id));

    // Verify that adding a transaction for the same key fails.
    EXPECT_THROW(update_mgr_->makeTransaction(ncr), D2UpdateMgrError);
    EXPECT_EQ(1, update_mgr_->getTransactionCount());

    // Verify the we can remove a transaction by key.
    EXPECT_NO_THROW(update_mgr_->removeTransaction(ncr->getDhcid()));
    EXPECT_EQ(0, update_mgr_->getTransactionCount());

    // Verify the we can try to remove a non-existent transaction without harm.
    EXPECT_NO_THROW(update_mgr_->removeTransaction(ncr->getDhcid()));
}

/// @brief Checks transaction creation when both update directions are enabled.
/// Verifies that when both directions are enabled and servers are matched to
/// the request, that the transaction is created with both directions turned on.
TEST_F(D2UpdateMgrTest, bothEnabled) {
    // Grab a canned request for test purposes.
    NameChangeRequestPtr& ncr = canned_ncrs_[0];
    ncr->setReverseChange(true);

    // Verify we are requesting both directions.
    ASSERT_TRUE(ncr->isForwardChange());
    ASSERT_TRUE(ncr->isReverseChange());

    // Verify both both directions are enabled.
    ASSERT_TRUE(cfg_mgr_->forwardUpdatesEnabled());
    ASSERT_TRUE(cfg_mgr_->reverseUpdatesEnabled());

    // Attempt to make a transaction.
    ASSERT_NO_THROW(update_mgr_->makeTransaction(ncr));

    // Verify we create a transaction with both directions turned on.
    EXPECT_EQ(1, update_mgr_->getTransactionCount());
    EXPECT_TRUE(ncr->isForwardChange());
    EXPECT_TRUE(ncr->isReverseChange());
}

/// @brief Checks transaction creation when reverse updates are disabled.
/// Verifies that when reverse updates are disabled, and there matching forward
/// servers, that the transaction is still created but with only the forward
/// direction turned on.
TEST_F(D2UpdateMgrTest, reverseDisable) {
    // Make a NCR which requests both directions.
    NameChangeRequestPtr& ncr = canned_ncrs_[0];
    ncr->setReverseChange(true);

    // Wipe out forward domain list.
    DdnsDomainMapPtr emptyDomains(new DdnsDomainMap());
    cfg_mgr_->getD2CfgContext()->getReverseMgr()->setDomains(emptyDomains);

    // Verify enable methods are correct.
    ASSERT_TRUE(cfg_mgr_->forwardUpdatesEnabled());
    ASSERT_FALSE(cfg_mgr_->reverseUpdatesEnabled());

    // Attempt to make a transaction.
    ASSERT_NO_THROW(update_mgr_->makeTransaction(ncr));

    // Verify we create a transaction with only forward turned on.
    EXPECT_EQ(1, update_mgr_->getTransactionCount());
    EXPECT_TRUE(ncr->isForwardChange());
    EXPECT_FALSE(ncr->isReverseChange());
}

/// @brief Checks transaction creation when forward updates are disabled.
/// Verifies that when forward updates are disabled, and there matching reverse
/// servers, that the transaction is still created but with only the reverse
/// direction turned on.
TEST_F(D2UpdateMgrTest, forwardDisabled) {
    // Make a NCR which requests both directions.
    NameChangeRequestPtr& ncr = canned_ncrs_[0];
    ncr->setReverseChange(true);

    // Wipe out forward domain list.
    DdnsDomainMapPtr emptyDomains(new DdnsDomainMap());
    cfg_mgr_->getD2CfgContext()->getForwardMgr()->setDomains(emptyDomains);

    // Verify enable methods are correct.
    ASSERT_FALSE(cfg_mgr_->forwardUpdatesEnabled());
    ASSERT_TRUE(cfg_mgr_->reverseUpdatesEnabled());

    // Attempt to make a transaction.
    ASSERT_NO_THROW(update_mgr_->makeTransaction(ncr));

    // Verify we create a transaction with only reverse turned on.
    EXPECT_EQ(1, update_mgr_->getTransactionCount());
    EXPECT_FALSE(ncr->isForwardChange());
    EXPECT_TRUE(ncr->isReverseChange());
}


/// @brief Checks transaction creation when neither update direction is enabled.
/// Verifies that transactions are not created when both forward and reverse
/// directions are disabled.
TEST_F(D2UpdateMgrTest, bothDisabled) {
    // Grab a canned request for test purposes.
    NameChangeRequestPtr& ncr = canned_ncrs_[0];
    ncr->setReverseChange(true);
    TransactionList::iterator pos;

    // Wipe out both forward and reverse domain lists.
    DdnsDomainMapPtr emptyDomains(new DdnsDomainMap());
    cfg_mgr_->getD2CfgContext()->getForwardMgr()->setDomains(emptyDomains);
    cfg_mgr_->getD2CfgContext()->getReverseMgr()->setDomains(emptyDomains);

    // Verify enable methods are correct.
    EXPECT_FALSE(cfg_mgr_->forwardUpdatesEnabled());
    EXPECT_FALSE(cfg_mgr_->reverseUpdatesEnabled());

    // Attempt to make a transaction.
    ASSERT_NO_THROW(update_mgr_->makeTransaction(ncr));

    // Verify that do not create a transaction.
    EXPECT_EQ(0, update_mgr_->getTransactionCount());
}

/// @brief Tests D2UpdateManager's checkFinishedTransactions method.
/// This test verifies that:
/// 1. Completed transactions are removed from the transaction list.
/// 2. Failed transactions are removed from the transaction list.
/// @todo This test will need to expand if and when checkFinishedTransactions
/// method expands to do more than remove them from the list.
TEST_F(D2UpdateMgrTest, checkFinishedTransaction) {
    // Ensure we have at least 4 canned requests with which to work.
    ASSERT_TRUE(canned_count_ >= 4);

    // Create a transaction for each canned request.
    for (int i = 0; i < canned_count_; i++) {
        EXPECT_NO_THROW(update_mgr_->makeTransaction(canned_ncrs_[i]));
    }
    // Verify we have that the transaction count is correct.
    EXPECT_EQ(canned_count_, update_mgr_->getTransactionCount());

    // Verify that all four transactions have been started.
    TransactionList::iterator pos;
    EXPECT_NO_THROW(pos = update_mgr_->transactionListBegin());
    while (pos != update_mgr_->transactionListEnd()) {
        NameChangeTransactionPtr trans = (*pos).second;
        ASSERT_EQ(dhcp_ddns::ST_PENDING, trans->getNcrStatus());
        ASSERT_TRUE(trans->isModelRunning());
        ++pos;
    }

    // Verify that invoking checkFinishedTransactions does not throw.
    EXPECT_NO_THROW(update_mgr_->checkFinishedTransactions());

    // Since nothing is running IOService, the all four transactions should
    // still be in the list.
    EXPECT_EQ(canned_count_, update_mgr_->getTransactionCount());

    // Now "complete" two of the four.
    // Simulate a successful completion.
    completeTransaction(1, dhcp_ddns::ST_COMPLETED);

    // Simulate a failed completion.
    completeTransaction(3, dhcp_ddns::ST_FAILED);

    // Verify that invoking checkFinishedTransactions does not throw.
    EXPECT_NO_THROW(update_mgr_->checkFinishedTransactions());

    // Verify that the list of transactions has decreased by two.
    EXPECT_EQ(canned_count_ - 2, update_mgr_->getTransactionCount());

    // Vefity that the transaction list is correct.
    EXPECT_TRUE(update_mgr_->hasTransaction(canned_ncrs_[0]->getDhcid()));
    EXPECT_FALSE(update_mgr_->hasTransaction(canned_ncrs_[1]->getDhcid()));
    EXPECT_TRUE(update_mgr_->hasTransaction(canned_ncrs_[2]->getDhcid()));
    EXPECT_FALSE(update_mgr_->hasTransaction(canned_ncrs_[3]->getDhcid()));
}

/// @brief Tests D2UpdateManager's pickNextJob method.
/// This test verifies that:
/// 1. pickNextJob will select and make transactions from NCR queue.
/// 2. Requests are removed from the queue once selected
/// 3. Requests for DHCIDs with transactions already in progress are not
/// selected.
/// 4. Requests with no matching servers are removed from the queue and
/// discarded.
TEST_F(D2UpdateMgrTest, pickNextJob) {
    // Ensure we have at least 4 canned requests with which to work.
    ASSERT_TRUE(canned_count_ >= 4);

    // Put each transaction on the queue.
    for (int i = 0; i < canned_count_; i++) {
        ASSERT_NO_THROW(queue_mgr_->enqueue(canned_ncrs_[i]));
    }

    // Invoke pickNextJob canned_count_ times which should create a
    // transaction for each canned ncr.
    for (int i = 0; i < canned_count_; i++) {
        EXPECT_NO_THROW(update_mgr_->pickNextJob());
        EXPECT_EQ(i + 1, update_mgr_->getTransactionCount());
        EXPECT_TRUE(update_mgr_->hasTransaction(canned_ncrs_[i]->getDhcid()));
    }

    // Verify that the queue has been drained.
    EXPECT_EQ(0, update_mgr_->getQueueCount());

    // Now verify that a subsequent request for a DCHID  for which a
    // transaction is in progress, is not dequeued.
    // First add the "subsequent" request.
    dhcp_ddns::NameChangeRequestPtr
        subsequent_ncr(new dhcp_ddns::NameChangeRequest(*(canned_ncrs_[2])));
    EXPECT_NO_THROW(queue_mgr_->enqueue(subsequent_ncr));
    EXPECT_EQ(1, update_mgr_->getQueueCount());

    // Verify that invoking pickNextJob:
    // 1. Does not throw
    // 2. Does not make a new transaction
    // 3. Does not dequeue the entry
    EXPECT_NO_THROW(update_mgr_->pickNextJob());
    EXPECT_EQ(canned_count_, update_mgr_->getTransactionCount());
    EXPECT_EQ(1, update_mgr_->getQueueCount());

    // Clear out the queue and transaction list.
    queue_mgr_->clearQueue();
    update_mgr_->clearTransactionList();

    // Make a forward change NCR with an FQDN that has no forward match.
    dhcp_ddns::NameChangeRequestPtr
        bogus_ncr(new dhcp_ddns::NameChangeRequest(*(canned_ncrs_[0])));
    bogus_ncr->setForwardChange(true);
    bogus_ncr->setReverseChange(false);
    bogus_ncr->setFqdn("bogus.forward.domain.com");

    // Put it on the queue up
    ASSERT_NO_THROW(queue_mgr_->enqueue(bogus_ncr));

    // Verify that invoking pickNextJob:
    // 1. Does not throw
    // 2. Does not make a new transaction
    // 3. Does dequeue the entry
    EXPECT_NO_THROW(update_mgr_->pickNextJob());
    EXPECT_EQ(0, update_mgr_->getTransactionCount());
    EXPECT_EQ(0, update_mgr_->getQueueCount());

    // Make a reverse change NCR with an FQDN that has no reverse match.
    bogus_ncr.reset(new dhcp_ddns::NameChangeRequest(*(canned_ncrs_[0])));
    bogus_ncr->setForwardChange(false);
    bogus_ncr->setReverseChange(true);
    bogus_ncr->setIpAddress("77.77.77.77");

    // Verify that invoking pickNextJob:
    // 1. does not throw
    // 2. Does not make a new transaction
    // 3. Does dequeue the entry
    EXPECT_NO_THROW(update_mgr_->pickNextJob());
    EXPECT_EQ(0, update_mgr_->getTransactionCount());
    EXPECT_EQ(0, update_mgr_->getQueueCount());
}

/// @brief Tests D2UpdateManager's sweep method.
/// Since sweep is primarily a wrapper around checkFinishedTransactions and
/// pickNextJob, along with checks on maximum transaction limits, it mostly
/// verifies that these three pieces work together to move process jobs.
/// Most of what is tested here is tested above.
TEST_F(D2UpdateMgrTest, sweep) {
    // Ensure we have at least 4 canned requests with which to work.
    ASSERT_TRUE(canned_count_ >= 4);

    // Set max transactions to same as current transaction count.
    EXPECT_NO_THROW(update_mgr_->setMaxTransactions(canned_count_));
    EXPECT_EQ(canned_count_, update_mgr_->getMaxTransactions());

    // Put each transaction on the queue.
    for (int i = 0; i < canned_count_; i++) {
        EXPECT_NO_THROW(queue_mgr_->enqueue(canned_ncrs_[i]));
    }

    // Invoke sweep canned_count_ times which should create a
    // transaction for each canned ncr.
    for (int i = 0; i < canned_count_; i++) {
        EXPECT_NO_THROW(update_mgr_->sweep());
        EXPECT_EQ(i + 1, update_mgr_->getTransactionCount());
        EXPECT_TRUE(update_mgr_->hasTransaction(canned_ncrs_[i]->getDhcid()));
    }

    // Verify that the queue has been drained.
    EXPECT_EQ(0, update_mgr_->getQueueCount());

    // Verify max transactions can't be less than current transaction count.
    EXPECT_THROW(update_mgr_->setMaxTransactions(1), D2UpdateMgrError);

    // Queue up a request for a DHCID which has a transaction in progress.
    dhcp_ddns::NameChangeRequestPtr
        subsequent_ncr(new dhcp_ddns::NameChangeRequest(*(canned_ncrs_[2])));
    EXPECT_NO_THROW(queue_mgr_->enqueue(subsequent_ncr));
    EXPECT_EQ(1, update_mgr_->getQueueCount());

    // Verify that invoking sweep, does not dequeue the job nor make a
    // transaction for it.
    EXPECT_NO_THROW(update_mgr_->sweep());
    EXPECT_EQ(canned_count_, update_mgr_->getTransactionCount());
    EXPECT_EQ(1, update_mgr_->getQueueCount());

    // Mark the transaction complete.
    completeTransaction(2, dhcp_ddns::ST_COMPLETED);

    // Verify that invoking sweep, cleans up the completed transaction,
    // dequeues the queued job and adds its transaction to the list.
    EXPECT_NO_THROW(update_mgr_->sweep());
    EXPECT_EQ(canned_count_, update_mgr_->getTransactionCount());
    EXPECT_EQ(0, update_mgr_->getQueueCount());

    // Queue up a request from a new DHCID.
    dhcp_ddns::NameChangeRequestPtr
        another_ncr(new dhcp_ddns::NameChangeRequest(*(canned_ncrs_[0])));
    another_ncr->setDhcid("AABBCCDDEEFF");
    EXPECT_NO_THROW(queue_mgr_->enqueue(another_ncr));
    EXPECT_EQ(1, update_mgr_->getQueueCount());

    // Verify that sweep does not dequeue the new request as we are at
    // maximum transaction count.
    EXPECT_NO_THROW(update_mgr_->sweep());
    EXPECT_EQ(canned_count_, update_mgr_->getTransactionCount());
    EXPECT_EQ(1, update_mgr_->getQueueCount());

    // Set max transactions to same as current transaction count.
    EXPECT_NO_THROW(update_mgr_->setMaxTransactions(canned_count_ + 1));

    // Verify that invoking sweep, dequeues the request and creates
    // a transaction for it.
    EXPECT_NO_THROW(update_mgr_->sweep());
    EXPECT_EQ(canned_count_ + 1, update_mgr_->getTransactionCount());
    EXPECT_EQ(0, update_mgr_->getQueueCount());

    // Verify that clearing transaction list works.
    EXPECT_NO_THROW(update_mgr_->clearTransactionList());
    EXPECT_EQ(0, update_mgr_->getTransactionCount());
}

/// @brief Tests integration of NameAddTransaction
/// This test verifies that update manager can create and manage a
/// NameAddTransaction from start to finish.  It utilizes a fake server
/// which responds to all requests sent with NOERROR, simulating a
/// successful addition.  The transaction processes both forward and
/// reverse changes.
TEST_F(D2UpdateMgrTest, addTransaction) {
    // Put each transaction on the queue.
    canned_ncrs_[0]->setChangeType(dhcp_ddns::CHG_ADD);
    canned_ncrs_[0]->setReverseChange(true);
    ASSERT_NO_THROW(queue_mgr_->enqueue(canned_ncrs_[0]));

    // Call sweep once, this should:
    // 1. Dequeue the request
    // 2. Create the transaction
    // 3. Start the transaction
    ASSERT_NO_THROW(update_mgr_->sweep());

    // Get a copy of the transaction.
    TransactionList::iterator pos = update_mgr_->transactionListBegin();
    ASSERT_TRUE (pos != update_mgr_->transactionListEnd());
    NameChangeTransactionPtr trans = (*pos).second;
    ASSERT_TRUE(trans);

    // At this point the transaction should have constructed
    // and sent the DNS request.
    ASSERT_TRUE(trans->getCurrentServer());
    ASSERT_TRUE(trans->isModelRunning());
    ASSERT_EQ(1, trans->getUpdateAttempts());
    ASSERT_EQ(StateModel::NOP_EVT, trans->getNextEvent());

    // Create a server based on the transaction's current server, and
    // start it listening.
    FauxServer server(*io_service_, *(trans->getCurrentServer()));
    server.receive(FauxServer::USE_RCODE, dns::Rcode::NOERROR());

    // Run sweep and IO until everything is done.
    processAll();

    // Verify that model succeeded.
    EXPECT_FALSE(trans->didModelFail());

    // Both completion flags should be true.
    EXPECT_TRUE(trans->getForwardChangeCompleted());
    EXPECT_TRUE(trans->getReverseChangeCompleted());

    // Verify that we went through success state.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_OK_ST,
              trans->getPrevState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_OK_EVT,
              trans->getLastEvent());
}

/// @brief Tests integration of NameRemoveTransaction
/// This test verifies that update manager can create and manage a
/// NameRemoveTransaction from start to finish.  It utilizes a fake server
/// which responds to all requests sent with NOERROR, simulating a
/// successful addition.  The transaction processes both forward and
/// reverse changes.
TEST_F(D2UpdateMgrTest, removeTransaction) {
    // Put each transaction on the queue.
    canned_ncrs_[0]->setChangeType(dhcp_ddns::CHG_REMOVE);
    canned_ncrs_[0]->setReverseChange(true);
    ASSERT_NO_THROW(queue_mgr_->enqueue(canned_ncrs_[0]));

    // Call sweep once, this should:
    // 1. Dequeue the request
    // 2. Create the transaction
    // 3. Start the transaction
    ASSERT_NO_THROW(update_mgr_->sweep());

    // Get a copy of the transaction.
    TransactionList::iterator pos = update_mgr_->transactionListBegin();
    ASSERT_TRUE (pos != update_mgr_->transactionListEnd());
    NameChangeTransactionPtr trans = (*pos).second;
    ASSERT_TRUE(trans);

    // At this point the transaction should have constructed
    // and sent the DNS request.
    ASSERT_TRUE(trans->getCurrentServer());
    ASSERT_TRUE(trans->isModelRunning());
    ASSERT_EQ(1, trans->getUpdateAttempts());
    ASSERT_EQ(StateModel::NOP_EVT, trans->getNextEvent());

    // Create a server based on the transaction's current server,
    // and start it listening.
    FauxServer server(*io_service_, *(trans->getCurrentServer()));
    server.receive(FauxServer::USE_RCODE, dns::Rcode::NOERROR());

    // Run sweep and IO until everything is done.
    processAll();

    // Verify that model succeeded.
    EXPECT_FALSE(trans->didModelFail());

    // Both completion flags should be true.
    EXPECT_TRUE(trans->getForwardChangeCompleted());
    EXPECT_TRUE(trans->getReverseChangeCompleted());

    // Verify that we went through success state.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_OK_ST,
              trans->getPrevState());
    EXPECT_EQ(NameChangeTransaction::UPDATE_OK_EVT,
              trans->getLastEvent());
}


/// @brief Tests handling of a transaction which fails.
/// This test verifies that update manager correctly concludes a transaction
/// which fails to complete successfully.  The failure simulated is repeated
/// corrupt responses from the server, which causes an exhaustion of the
/// available servers.
TEST_F(D2UpdateMgrTest, errorTransaction) {
    // Put each transaction on the queue.
    ASSERT_NO_THROW(queue_mgr_->enqueue(canned_ncrs_[0]));

    // Call sweep once, this should:
    // 1. Dequeue the request
    // 2. Create the transaction
    // 3. Start the transaction
    ASSERT_NO_THROW(update_mgr_->sweep());

    // Get a copy of the transaction.
    TransactionList::iterator pos = update_mgr_->transactionListBegin();
    ASSERT_TRUE (pos != update_mgr_->transactionListEnd());
    NameChangeTransactionPtr trans = (*pos).second;
    ASSERT_TRUE(trans);

    ASSERT_TRUE(trans->isModelRunning());
    ASSERT_EQ(1, trans->getUpdateAttempts());
    ASSERT_EQ(StateModel::NOP_EVT, trans->getNextEvent());
    ASSERT_TRUE(trans->getCurrentServer());

    // Create a server and start it listening.
    FauxServer server(*io_service_, *(trans->getCurrentServer()));
    server.receive(FauxServer::CORRUPT_RESP);

    // Run sweep and IO until everything is done.
    processAll();

    // Verify that model succeeded.
    EXPECT_FALSE(trans->didModelFail());

    // Both completion flags should be false.
    EXPECT_FALSE(trans->getForwardChangeCompleted());
    EXPECT_FALSE(trans->getReverseChangeCompleted());

    // Verify that we went through success state.
    EXPECT_EQ(NameChangeTransaction::PROCESS_TRANS_FAILED_ST,
              trans->getPrevState());
    EXPECT_EQ(NameChangeTransaction::NO_MORE_SERVERS_EVT,
              trans->getLastEvent());


}

/// @brief Tests processing of multiple transactions.
/// This test verifies that update manager can create and manage a multiple
/// transactions, concurrently.  It uses a fake server that responds to all
/// requests sent with NOERROR, simulating successful DNS updates. The
/// transactions are a mix of both adds and removes.
TEST_F(D2UpdateMgrTest, multiTransaction) {
    // Queue up all the requests.
    int test_count = canned_count_;
    for (int i = test_count; i > 0; i--) {
        canned_ncrs_[i-1]->setReverseChange(true);
        ASSERT_NO_THROW(queue_mgr_->enqueue(canned_ncrs_[i-1]));
    }

    // Create a server and start it listening. Note this relies on the fact
    // that all of configured servers have the same address.
    // and start it listening.
    asiolink::IOAddress server_ip("127.0.0.1");
    FauxServer server(*io_service_, server_ip, 5301);
    server.receive(FauxServer::USE_RCODE, dns::Rcode::NOERROR());

    // Run sweep and IO until everything is done.
    processAll();

    for (int i = 0; i < test_count; i++) {
        EXPECT_EQ(dhcp_ddns::ST_COMPLETED, canned_ncrs_[i]->getStatus());
    }
}

/// @brief Tests processing of multiple transactions.
/// This test verifies that update manager can create and manage a multiple
/// transactions, concurrently.  It uses a fake server that responds to all
/// requests sent with NOERROR, simulating successful DNS updates. The
/// transactions are a mix of both adds and removes.
TEST_F(D2UpdateMgrTest, multiTransactionTimeout) {
    // Queue up all the requests.
    int test_count = canned_count_;
    for (int i = test_count; i > 0; i--) {
        canned_ncrs_[i-1]->setReverseChange(true);
        ASSERT_NO_THROW(queue_mgr_->enqueue(canned_ncrs_[i-1]));
    }

    // No server is running, so everything will time out.

    // Run sweep and IO until everything is done.
    processAll();

    for (int i = 0; i < test_count; i++) {
        EXPECT_EQ(dhcp_ddns::ST_FAILED, canned_ncrs_[i]->getStatus());
    }
}

}
