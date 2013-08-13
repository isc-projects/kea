// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef D2_UPDATE_MGR_H
#define D2_UPDATE_MGR_H

/// @file d2_update_mgr.h This file defines the class D2UpdateMgr.

#include <asiolink/io_service.h>
#include <exceptions/exceptions.h>
#include <d2/d2_log.h>
#include <d2/d2_queue_mgr.h>
#include <d2/d2_cfg_mgr.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <map>

namespace isc {
namespace d2 {

/// @brief Thrown if the update manager encounters a general error.
class D2UpdateMgrError : public isc::Exception {
public:
    D2UpdateMgrError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

//@{
/// @todo  This is a stub implementation of NameChangeTransaction that is here
/// strictly to facilitate development of D2UpdateMgr. It will move to its own
/// source file(s) once NameChangeTransaction class development begins.

/// @brief Defines the key for transactions.
typedef isc::dhcp_ddns::D2Dhcid TransactionKey;

class NameChangeTransaction {
public:
    NameChangeTransaction(isc::asiolink::IOService& io_service,
                          dhcp_ddns::NameChangeRequestPtr& ncr,
                          DdnsDomainPtr forward_domain,
                          DdnsDomainPtr reverse_domain)
    : io_service_(io_service), ncr_(ncr), forward_domain_(forward_domain),
      reverse_domain_(reverse_domain) {
    }

    ~NameChangeTransaction(){
    }

    const dhcp_ddns::NameChangeRequestPtr& getNcr() const {
        return (ncr_);
    }

    const TransactionKey& getTransactionKey() const {
        return (ncr_->getDhcid());
    }

    dhcp_ddns::NameChangeStatus getNcrStatus() const {
        return (ncr_->getStatus());
    }

private:
    isc::asiolink::IOService& io_service_;

    dhcp_ddns::NameChangeRequestPtr ncr_;

    DdnsDomainPtr forward_domain_;

    DdnsDomainPtr reverse_domain_;
};

/// @brief Defines a pointer to a NameChangeTransaction.
typedef boost::shared_ptr<NameChangeTransaction> NameChangeTransactionPtr;

//@}

/// @brief Defines a list of transactions.
typedef std::map<TransactionKey, NameChangeTransactionPtr> TransactionList;


/// @brief D2UpdateMgr creates and manages update transactions.
///
/// D2UpdateMgr is the DHCP_DDNS task master, instantiating and then supervising
/// transactions that execute the DNS updates needed to fulfill the requests
/// (NameChangeRequests) received from DHCP_DDNS clients (e.g. DHCP servers).
///
/// D2UpdateMgr uses the services of D2QueueMgr to monitor the queue of
/// NameChangeRequests and select and dequeue requests for processing.
/// When request is dequeued for processing it is removed from the queue and
/// wrapped in NameChangeTransaction and added to the D2UpdateMgr's list of
/// transactions.
///
/// As part of the process of forming transactions, D2UpdateMgr matches each
/// request with the appropriate list of DNS servers.  This matching is  based
/// upon request attributes, primarily the FQDN and update direction (forward
/// or reverse).  D2UpdateMgr uses the services of D2CfgMgr to match requests
/// to DNS server lists.
///
/// Once created, each transaction is responsible for carrying out the steps
/// required to fulfill its specific request.  These steps typically consist of
/// one or more DNS packet exchanges with the appropriate DNS server.  As
/// transactions complete,  D2UpdateMgr removes them from the transaction list,
/// replacing them with new transactions.
///
/// D2UpdateMgr carries out each of the above steps, from with a method called
/// sweep().  This method is intended to be called as IO events complete.
/// The upper layer(s) are responsible for calling sweep in a timely and cyclic
/// manner.
///
class D2UpdateMgr : public boost::noncopyable {
public:
    /// @brief Maximum number of concurrent transactions
    /// NOTE that 32 is an arbitrary choice picked for the initial
    /// implementation.
    static const size_t MAX_TRANSACTIONS_DEFAULT = 32;

    // @todo This structure is not yet used. It is here in anticipation of
    // enabled statistics capture.
    struct Stats {
        uint64_t start_time_;
        uint64_t stop_time_;
        uint64_t update_count_;
        uint64_t min_update_time_;
        uint64_t max_update_time_;
        uint64_t server_rejects_;
        uint64_t server_timeouts_;
    };

    /// @brief Constructor
    ///
    /// @param queue_mgr reference to the queue manager receiving requests
    /// @param cfg_mgr reference to the configuration manager
    /// @param io_service IO service used by the upper layer(s) to manage
    /// IO events
    /// @param max_transactions the maximum number of concurrent transactions
    ///
    /// @throw D2UpdateMgrError if either the queue manager or configuration
    /// managers are NULL, or max transactions is less than one.
    D2UpdateMgr(D2QueueMgrPtr& queue_mgr, D2CfgMgrPtr& cfg_mgr,
                isc::asiolink::IOService& io_service,
                const size_t max_transactions = MAX_TRANSACTIONS_DEFAULT);

    /// @brief Destructor
    virtual ~D2UpdateMgr();

    /// @brief Check current transactions; start transactions for new requests.
    ///
    /// This method is the primary public interface used by the upper layer. It
    /// should be called as IO events complete.  During each invocation it does
    /// the following:
    ///
    /// - Removes all completed transactions from the transaction list.
    ///
    /// - If the request queue is not empty and the number of transactions
    /// in the transaction list has not reached maximum allowed, then select
    /// a request from the queue.
    ///
    /// - If a request was selected, start a new transaction for it and
    /// add the transaction to the list of transactions.
    void sweep();

protected:
    /// @brief Performs post-completion cleanup on completed transactions.
    ///
    /// Iterates through the list of transactions and removes any that have
    /// reached completion.  This method may expand in complexity or even
    /// disappear altogether as the implementation matures.
    void checkFinishedTransactions();

    /// @brief Starts a transaction for the next eligible request in the queue.
    ///
    /// This method will scan the request queue for the next request to
    /// dequeue.  The current implementation starts at the front of the queue
    /// and looks for the first request for whose DHCID there is no current
    /// transaction in progress.
    ///
    /// If a request is selected, it is removed from the queue and transaction
    /// is constructed for it.
    ///
    /// It is possible that no such request exists, though this is likely to be
    /// rather rare unless a system is frequently seeing requests for the same
    /// clients in quick succession.
    void pickNextJob();

    /// @brief Create a new transaction for the given request.
    ///
    /// This method will attempt to match the request to a list of configured
    /// DNS servers.  If a list of servers is found, it will instantiate a
    /// transaction for it and add the transaction to the transaction list.
    ///
    /// If no servers are found that match the request, this constitutes a
    /// configuration error.  The error will be logged and the request will
    /// be discarded.
    ///
    /// @param ncr the NameChangeRequest for which to create a transaction.
    ///
    /// @throw D2UpdateMgrError if a transaction for this DHCID already
    /// exists. Note this would be programmatic error.
    void makeTransaction(isc::dhcp_ddns::NameChangeRequestPtr& ncr);

public:
    /// @brief Returns the maximum number of concurrent transactions.
    size_t getMaxTransactions() const {
        return (max_transactions_);
    }

    /// @brief Sets the maximum number of entries allowed in the queue.
    ///
    /// @param max_transactions is the new maximum number of transactions
    ///
    /// @throw Throws D2QueueMgrError if the new value is less than one or if
    /// the new value is less than the number of entries currently in the
    /// queue.
    void setMaxTransactions(const size_t max_transactions);

    /// @brief Search the transaction list for the given key.
    ///
    /// @param key the transaction key value for which to search.
    ///
    /// @return Iterator pointing to the entry found.  If no entry is
    /// it will point to the list end position.
    TransactionList::iterator findTransaction(const TransactionKey& key);

    /// @brief Returns the transaction list end position.
    TransactionList::iterator transactionListEnd();

    /// @brief Convenience method that checks transaction list for the given key
    ///
    /// @param key the transaction key value for which to search.
    ///
    /// @return Returns true if the key is found within the list, false
    /// otherwise.
    bool hasTransaction(const TransactionKey& key);

    /// @brief Removes the entry pointed to by key from the transaction list.
    ///
    /// Removes the entry referred to by key if it exists.  It has no effect
    /// if the entry is not found.
    ///
    /// @param key of the transaction to remove
    void removeTransaction(const TransactionKey& key);

    /// @brief Immediately discards all entries in the transaction list.
    ///
    /// @todo For now this just wipes them out. We might need something
    /// more elegant, that allows a cancel first.
    void clearTransactionList();

    /// @brief Convenience method that returns the number of requests queued.
    size_t getQueueCount() const;

    /// @brief Returns the current number of transactions.
    size_t getTransactionCount() const;

private:
    /// @brief Pointer to the queue manager.
    D2QueueMgrPtr queue_mgr_;

    /// @brief Pointer to the configuration manager.
    D2CfgMgrPtr cfg_mgr_;

    /// @brief Primary IOService instance.
    /// This is the IOService that the upper layer(s) use for IO events, such
    /// as shutdown and configuration commands.  It is the IOService that is
    /// passed into transactions to manager their IO events.
    /// (For future reference, multi-threaded transactions would each use their
    /// own IOService instance.)
    isc::asiolink::IOService& io_service_;

    /// @brief Maximum number of concurrent transactions.
    size_t max_transactions_;

    /// @brief List of transactions.
    TransactionList transaction_list_;
};

/// @brief Defines a pointer to a D2UpdateMgr instance.
typedef boost::shared_ptr<D2UpdateMgr> D2UpdateMgrPtr;


} // namespace isc::d2
} // namespace isc
#endif
