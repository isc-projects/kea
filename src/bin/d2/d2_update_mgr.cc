// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <d2/d2_update_mgr.h>
#include <d2/nc_add.h>
#include <d2/nc_remove.h>

#include <sstream>
#include <iostream>
#include <vector>

namespace isc {
namespace d2 {

const size_t D2UpdateMgr::MAX_TRANSACTIONS_DEFAULT;

D2UpdateMgr::D2UpdateMgr(D2QueueMgrPtr& queue_mgr, D2CfgMgrPtr& cfg_mgr,
                         asiolink::IOServicePtr& io_service,
                         const size_t max_transactions)
    :queue_mgr_(queue_mgr), cfg_mgr_(cfg_mgr), io_service_(io_service) {
    if (!queue_mgr_) {
        isc_throw(D2UpdateMgrError, "D2UpdateMgr queue manager cannot be null");
    }

    if (!cfg_mgr_) {
        isc_throw(D2UpdateMgrError,
                  "D2UpdateMgr configuration manager cannot be null");
    }

    if (!io_service_) {
        isc_throw(D2UpdateMgrError, "IOServicePtr cannot be null");
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
            LOG_DEBUG(dhcp_to_d2_logger, DBGLVL_TRACE_DETAIL_DATA,
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
    // NOTE: One must use postfix increments of the iterator on the calls
    // to erase.  This replaces the old iterator which becomes invalid by the
    // erase with a the next valid iterator.  Prefix incrementing will not
    // work.
    TransactionList::iterator it = transaction_list_.begin();
    while (it != transaction_list_.end()) {
        NameChangeTransactionPtr trans = (*it).second;
        if (trans->isModelDone()) {
            // @todo  Addtional actions based on NCR status could be
            // performed here.
            transaction_list_.erase(it++);
        } else {
            ++it;
        }
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
    for (size_t index = 0; index < queue_count; ++index) {
        dhcp_ddns::NameChangeRequestPtr found_ncr = queue_mgr_->peekAt(index);
        if (!hasTransaction(found_ncr->getDhcid())) {
            queue_mgr_->dequeueAt(index);
            makeTransaction(found_ncr);
            return;
        }
    }

    // There were no eligible jobs. All of the current DHCIDs already have
    // transactions pending.
    LOG_DEBUG(dhcp_to_d2_logger, DBGLVL_TRACE_DETAIL_DATA, DHCP_DDNS_NO_ELIGIBLE_JOBS)
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

    int direction_count = 0;
    // If forward change is enabled, match to forward servers.
    DdnsDomainPtr forward_domain;
    if (next_ncr->isForwardChange()) {
        if (!cfg_mgr_->forwardUpdatesEnabled()) {
            next_ncr->setForwardChange(false);
            LOG_DEBUG(dhcp_to_d2_logger, DBGLVL_TRACE_DETAIL_DATA,
                      DHCP_DDNS_FWD_REQUEST_IGNORED)
                      .arg(next_ncr->getRequestId())
                      .arg(next_ncr->toText());
        } else {
            bool matched = cfg_mgr_->matchForward(next_ncr->getFqdn(),
                                                  forward_domain);
            // Could not find a match for forward DNS server. Log it and get
            // out. This has the net affect of dropping the request on the
            // floor.
            if (!matched) {
                LOG_ERROR(dhcp_to_d2_logger, DHCP_DDNS_NO_FWD_MATCH_ERROR)
                          .arg(next_ncr->getRequestId())
                          .arg(next_ncr->toText());
                return;
            }

            ++direction_count;
        }
    }

    // If reverse change is enabled, match to reverse servers.
    DdnsDomainPtr reverse_domain;
    if (next_ncr->isReverseChange()) {
        if (!cfg_mgr_->reverseUpdatesEnabled()) {
            next_ncr->setReverseChange(false);
            LOG_DEBUG(dhcp_to_d2_logger, DBGLVL_TRACE_DETAIL_DATA,
                      DHCP_DDNS_REV_REQUEST_IGNORED)
                      .arg(next_ncr->getRequestId())
                      .arg(next_ncr->toText());
        } else {
            bool matched = cfg_mgr_->matchReverse(next_ncr->getIpAddress(),
                                                  reverse_domain);
            // Could not find a match for reverse DNS server. Log it and get
            // out. This has the net affect of dropping the request on the
            // floor.
            if (!matched) {
                LOG_ERROR(dhcp_to_d2_logger, DHCP_DDNS_NO_REV_MATCH_ERROR)
                          .arg(next_ncr->getRequestId())
                          .arg(next_ncr->toText());
                return;
            }

            ++direction_count;
        }
    }

    // If there is nothing to actually do, then the request falls on the floor.
    // Should we log this?
    if (!direction_count) {
        LOG_DEBUG(dhcp_to_d2_logger, DBGLVL_TRACE_DETAIL_DATA,
                  DHCP_DDNS_REQUEST_DROPPED)
                  .arg(next_ncr->getRequestId())
                  .arg(next_ncr->toText());
        return;
    }

    // We matched to the required servers, so construct the transaction.
    // @todo If multi-threading is implemented, one would pass in an
    // empty IOServicePtr, rather than our instance value.  This would cause
    // the transaction to instantiate its own, separate IOService to handle
    // the transaction's IO.
    NameChangeTransactionPtr trans;
    if (next_ncr->getChangeType() == dhcp_ddns::CHG_ADD) {
        trans.reset(new NameAddTransaction(io_service_, next_ncr,
                                           forward_domain, reverse_domain,
                                           cfg_mgr_));
    } else {
        trans.reset(new NameRemoveTransaction(io_service_, next_ncr,
                                              forward_domain, reverse_domain,
                                              cfg_mgr_));
    }

    // Add the new transaction to the list.
    transaction_list_[key] = trans;

    // Start it.
    trans->startTransaction();
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
D2UpdateMgr::transactionListBegin() {
    return (transaction_list_.begin());
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
D2UpdateMgr::getQueueCount() const {
    return (queue_mgr_->getQueueSize());
}

size_t
D2UpdateMgr::getTransactionCount() const {
    return (transaction_list_.size());
}


} // namespace isc::d2
} // namespace isc
