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

#include <d2/d2_asio.h>
#include <d2/d2_update_mgr.h>
#include <util/time_utilities.h>
#include <d_test_stubs.h>

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

/// @brief Wrapper class for D2UpdateMgr to provide acces non-public methods.
///
/// This class faciliates testing by making non-public methods accessible so
/// they can be invoked directly in test routines.
class D2UpdateMgrWrapper : public D2UpdateMgr {
public:
    /// @brief Constructor
    ///
    /// Parameters match those needed by D2UpdateMgr.
    D2UpdateMgrWrapper(D2QueueMgrPtr& queue_mgr, D2CfgMgrPtr& cfg_mgr,
                       IOServicePtr& io_service,
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
class D2UpdateMgrTest : public ConfigParseTest {
public:
    IOServicePtr io_service_;
    D2QueueMgrPtr queue_mgr_;
    D2CfgMgrPtr cfg_mgr_;
    //D2UpdateMgrPtr update_mgr_;
    D2UpdateMgrWrapperPtr update_mgr_;
    std::vector<NameChangeRequestPtr> canned_ncrs_;
    size_t canned_count_;

    D2UpdateMgrTest() {
        io_service_.reset(new isc::asiolink::IOService());
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
        " \"change_type\" : 0 , "
        " \"forward_change\" : true , "
        " \"reverse_change\" : false , "
        " \"fqdn\" : \"walah.walah.org.\" , "
        " \"ip_address\" : \"192.168.2.1\" , "
        " \"dhcid\" : \"0102030405060708\" , "
        " \"lease_expires_on\" : \"20130121132405\" , "
        " \"lease_length\" : 1300 "
        "}";

        const char* dhcids[] = { "111111", "222222", "333333", "444444"};
        canned_count_ = 4;
        for (int i = 0; i < canned_count_; i++) {
            dhcp_ddns::NameChangeRequestPtr ncr = NameChangeRequest::
                                                  fromJSON(msg_str);
            ncr->setDhcid(dhcids[i]);
            canned_ncrs_.push_back(ncr);
        }
    }

    /// @brief Seeds configuration manager with a valid DHCP_DDNS configuration.
    void makeCannedConfig() {
        std::string canned_config_ =
                 "{ "
                  "\"interface\" : \"eth1\" , "
                  "\"ip_address\" : \"192.168.1.33\" , "
                  "\"port\" : 88 , "
                  "\"tsig_keys\": [] ,"
                  "\"forward_ddns\" : {"
                  "\"ddns_domains\": [ "
                  "{ \"name\": \"two.three.org.\" , "
                  "  \"dns_servers\" : [ "
                  "  { \"ip_address\": \"127.0.0.1\" } "
                  "  ] },"
                  "{ \"name\": \"org.\" , "
                  "  \"dns_servers\" : [ "
                  "  { \"ip_address\": \"127.0.0.1\" } "
                  "  ] }, "
                  "] }, "
                  "\"reverse_ddns\" : { "
                  "\"ddns_domains\": [ "
                  "{ \"name\": \"1.168.192.in-addr.arpa.\" , "
                  "  \"dns_servers\" : [ "
                  "  { \"ip_address\": \"127.0.0.1\" } "
                  "  ] }, "
                  "{ \"name\": \"2.0.3.0.8.B.D.0.1.0.0.2.ip6.arpa.\" , "
                  "  \"dns_servers\" : [ "
                  "  { \"ip_address\": \"127.0.0.1\" } "
                  "  ] } "
                  "] } }";

        // If this configuration fails to parse most tests will fail.
        ASSERT_TRUE(fromJSON(canned_config_));
        answer_ = cfg_mgr_->parseConfig(config_set_);
        ASSERT_TRUE(checkAnswer(0));
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
    IOServicePtr io_service(new isc::asiolink::IOService());
    D2QueueMgrPtr queue_mgr;
    D2CfgMgrPtr cfg_mgr;
    D2UpdateMgrPtr update_mgr;

    // Verify that constrctor fails if given an invalid queue manager.
    ASSERT_NO_THROW(cfg_mgr.reset(new D2CfgMgr()));
    EXPECT_THROW(D2UpdateMgr(queue_mgr, cfg_mgr, io_service),
                 D2UpdateMgrError);

    // Verify that constrctor fails if given an invalid config manager.
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
/// 3. Looking for a non-existant transaction works properly.
/// 4. Attempting to add a transaction for a DHCID already in the list fails.
/// 5. Removing a transaction by key works properly.
/// 6. Attempting to remove an non-existant transaction does no harm.
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

    // Verify the we can try to remove a non-existant transaction without harm.
    EXPECT_NO_THROW(update_mgr_->removeTransaction(ncr->getDhcid()));
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
    // Verfiy we have that the transaçtion count is correct.
    EXPECT_EQ(canned_count_, update_mgr_->getTransactionCount());

    // Set two of the transactions to finished states.
    (canned_ncrs_[1])->setStatus(dhcp_ddns::ST_COMPLETED);
    (canned_ncrs_[3])->setStatus(dhcp_ddns::ST_FAILED);

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
    // 1. does not throw
    // 2. does not make a new transaction
    // 3. does not dequeu the entry
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
    // 1. does not throw
    // 2. does not make a new transaction
    // 3. does dequeue the entry
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
    // 2. does not make a new transaction
    // 3. does dequeue the entry
    EXPECT_NO_THROW(update_mgr_->pickNextJob());
    EXPECT_EQ(0, update_mgr_->getTransactionCount());
    EXPECT_EQ(0, update_mgr_->getQueueCount());
}

/// @brief Tests D2UpdateManager's sweep method.
/// Since sweep is primarly a wrapper around chechFinishedTransactions and
/// pickNextJob, along with checks on maximum transaction limits, it mostly
/// verifies that these three pieces work togther to move process jobs.
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

    // Queue up a request for a DCHID which has a transaction in progress.
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
    (canned_ncrs_[2])->setStatus(dhcp_ddns::ST_COMPLETED);

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
    // transaction count.
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

}
