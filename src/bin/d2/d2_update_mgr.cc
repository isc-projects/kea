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

#include <d2/d2_update_mgr.h>

#include <sstream>
#include <iostream>
#include <vector>

namespace isc {
namespace d2 {

const size_t D2UpdateMgr::MAX_TRANSACTIONS_DEFAULT;

D2UpdateMgr::D2UpdateMgr(D2QueueMgrPtr& queue_mgr, D2CfgMgrPtr& cfg_mgr,
                         isc::asiolink::IOService& io_service,
                         const size_t max_transactions)
    :queue_mgr_(queue_mgr), cfg_mgr_(cfg_mgr), io_service_(io_service) {
    if (!queue_mgr_) {
        isc_throw(D2UpdateMgrError, "D2UpdateMgr queue manager cannot be null");
    }

    if (!cfg_mgr_) {
        isc_throw(D2UpdateMgrError,
                  "D2UpdateMgr configuration manager cannot be null");
    }

    // Use setter to do validation.
    setMaxTransactions(max_transactions);
}

D2UpdateMgr::~D2UpdateMgr() {
    transaction_list_.clear();
}

void D2UpdateMgr::sweep() {
    // cleanup finished transactions;
    checkFinishedTransactions();

    // if the queue isn't empty, find the next suitable job and
    // start a transaction for it.
    // @todo - Do we want to queue max transactions? The logic here will only
    // start one new transaction per invocation.  On the other hand a busy
    // system will generate many IO events and this method will be called
    // frequently.  It will likely achieve max transactions quickly on its own.
    if (getQueueCount() > 0)  {
        if (getTransactionCount() >= max_transactions_) {
            LOG_DEBUG(dctl_logger, DBGLVL_TRACE_DETAIL_DATA,
                      DHCP_DDNS_AT_MAX_TRANSACTIONS).arg(getQueueCount())
                      .arg(getMaxTransactions());

            return;
        }

        // We are not at maximum transactions, so pick and start the next job.
        pickNextJob();
    }
}

void
D2UpdateMgr::checkFinishedTransactions() {
    // Cycle through transaction list and do whatever needs to be done
    // for finished transactions.
    // At the moment all we do is remove them from the list. This is likely
    // to expand as DHCP_DDNS matures.
    TransactionList::iterator it = transaction_list_.begin();
    while (it != transaction_list_.end()) {
        NameChangeTransactionPtr trans = (*it).second;
        switch (trans->getNcrStatus())  {
        case dhcp_ddns::ST_COMPLETED:
            transaction_list_.erase(it);
            break;
        case dhcp_ddns::ST_FAILED:
            transaction_list_.erase(it);
            break;
        default:
            break;
        }

        ++it;
    }
}

void D2UpdateMgr::pickNextJob() {
    // Start at the front of the queue, looking for the first entry for
    // which no transaction is in progress.  If we find an eligible entry
    // remove it from the queue and  make a transaction for it.
    // Requests and transactions are associated by DHCID.  If a request has
    // the same DHCID as a transaction, they are presumed to be for the same
    // "end user".
    size_t queue_count = getQueueCount();
    for (size_t index = 0; index < queue_count; index++) {
        dhcp_ddns::NameChangeRequestPtr found_ncr = queue_mgr_->peekAt(index);
        if (!hasTransaction(found_ncr->getDhcid())) {
            queue_mgr_->dequeueAt(index);
            makeTransaction(found_ncr);
            return;
        }
    }

    // There were no eligible jobs. All of the current DHCIDs already have
    // transactions pending.
    LOG_DEBUG(dctl_logger, DBGLVL_TRACE_DETAIL_DATA, DHCP_DDNS_NO_ELIGIBLE_JOBS)
              .arg(getQueueCount()).arg(getTransactionCount());
}

void
D2UpdateMgr::makeTransaction(dhcp_ddns::NameChangeRequestPtr& next_ncr) {
    // First lets ensure there is not a transaction in progress for this
    // DHCID. (pickNextJob should ensure this, as it is the only real caller
    // but for safety's sake we'll check).
    const TransactionKey& key = next_ncr->getDhcid();
    if (findTransaction(key) != transactionListEnd()) {
        // This is programmatic error.  Caller(s) should be checking this.
        isc_throw(D2UpdateMgrError, "Transaction already in progress for: "
            << key.toStr());
    }

    // If forward change is enabled, match to forward servers.
    DdnsDomainPtr forward_domain;
    if (next_ncr->isForwardChange()) {
        bool matched = cfg_mgr_->matchForward(next_ncr->getFqdn(),
                                             forward_domain);
        // Could not find a match for forward DNS server. Log it and get out.
        // This has the net affect of dropping the request on the floor.
        if (!matched) {
            LOG_ERROR(dctl_logger, DHCP_DDNS_NO_FWD_MATCH_ERROR)
                      .arg(next_ncr->getFqdn());
            return;
        }
    }

    // If reverse change is enabled, match to reverse servers.
    DdnsDomainPtr reverse_domain;
    if (next_ncr->isReverseChange()) {
        bool matched = cfg_mgr_->matchReverse(next_ncr->getIpAddress(),
                                              reverse_domain);
        // Could not find a match for reverse DNS server. Log it and get out.
        // This has the net affect of dropping the request on the floor.
        if (!matched) {
            LOG_ERROR(dctl_logger, DHCP_DDNS_NO_REV_MATCH_ERROR)
                      .arg(next_ncr->getIpAddress());
            return;
        }
    }

    // We matched to the required servers, so construct the transaction.
    NameChangeTransactionPtr trans(new NameChangeTransaction(io_service_,
                                                             next_ncr,
                                                             forward_domain,
                                                             reverse_domain));
    // Add the new transaction to the list.
    transaction_list_[key] = trans;
}

TransactionList::iterator
D2UpdateMgr::findTransaction(const TransactionKey& key) {
    return (transaction_list_.find(key));
}

bool
D2UpdateMgr::hasTransaction(const TransactionKey& key) {
   return (findTransaction(key) != transactionListEnd());
}

void
D2UpdateMgr::removeTransaction(const TransactionKey& key) {
    TransactionList::iterator pos = findTransaction(key);
    if (pos != transactionListEnd()) {
        transaction_list_.erase(pos);
    }
}

TransactionList::iterator
D2UpdateMgr::transactionListEnd() {
    return (transaction_list_.end());
}

void
D2UpdateMgr::clearTransactionList() {
    // @todo for now this just wipes them out. We might need something
    // more elegant, that allows a cancel first.
    transaction_list_.clear();
}

void
D2UpdateMgr::setMaxTransactions(const size_t new_trans_max) {
    // Obviously we need at room for at least one transaction.
    if (new_trans_max < 1) {
        isc_throw(D2UpdateMgrError, "D2UpdateMgr"
                  " maximum transactions limit must be greater than zero");
    }

    // Do not allow the list maximum to be set to less then current list size.
    if (new_trans_max < getTransactionCount()) {
        isc_throw(D2UpdateMgrError, "D2UpdateMgr maximum transaction limit "
                  "cannot be less than the current transaction count :"
                  << getTransactionCount());
    }

    max_transactions_ = new_trans_max;
}

size_t
D2UpdateMgr::getQueueCount() {
    return (queue_mgr_->getQueueSize());
}

size_t
D2UpdateMgr::getTransactionCount() {
    return (transaction_list_.size());
}


} // namespace isc::d2
} // namespace isc
