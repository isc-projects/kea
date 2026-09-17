// Copyright (C) 2013-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <d2/d2_update_mgr.h>
#include <d2/nc_add.h>
#include <d2/nc_remove.h>
#include <d2/simple_add.h>
#include <d2/simple_remove.h>
#include <d2/check_exists_add.h>
#include <d2/check_exists_remove.h>
#include <d2/simple_add_without_dhcid.h>
#include <d2/simple_remove_without_dhcid.h>

#include <sstream>
#include <iostream>
#include <vector>

using namespace isc::dhcp_ddns;

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
    transaction_store_.clear();
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
    if (getQueueCount() > 0) {
        if (getTransactionCount() >= max_transactions_) {
            LOG_DEBUG(dhcp_to_d2_logger, isc::log::DBGLVL_TRACE_DETAIL_DATA,
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
    auto& sidx = transaction_store_.get<SequenceTag>();
    auto siter = sidx.begin();
    while (siter != sidx.end()) {
        if ((*siter)->isModelDone()) {
            siter = transaction_store_.get<SequenceTag>().erase(siter);
        } else {
            ++siter;
        }
    }
}

void D2UpdateMgr::pickNextJob() {
    // Start at the front of the queue, looking for the first request for
    // which no transaction is working the same FQDN or ip address. If a
    // request is currently ineligible we levae it on the queue, and try
    // the next one. If it is eligible wee remove it from the queue and
    // make a transaction for it. If the transaction creation fails try
    // the next request in the queue.
    size_t queue_count = getQueueCount();
    for (size_t index = 0; index < queue_count; ) {
        NameChangeRequestPtr queued_ncr = queue_mgr_->peekAt(index);
        if (hasTransaction(queued_ncr)) {
            // Leave it on the queue, move on to the next.
            ++index;
        } else {
            // Dequeue it and try to make transaction for it.
            queue_mgr_->dequeueAt(index);
            if (makeTransaction(queued_ncr)) {
                return;
            }

            // One less in the queue.
            --queue_count;
        }
    }

    // There were no eligible jobs. All of the current DHCIDs already have
    // transactions pending.
    LOG_DEBUG(dhcp_to_d2_logger, isc::log::DBGLVL_TRACE_DETAIL_DATA,
              DHCP_DDNS_NO_ELIGIBLE_JOBS)
        .arg(getQueueCount()).arg(getTransactionCount());
}

bool
D2UpdateMgr::makeTransaction(NameChangeRequestPtr& next_ncr) {
    int direction_count = 0;
    // If forward change is enabled, match to forward servers.
    DdnsDomainPtr forward_domain;
    if (next_ncr->isForwardChange()) {
        if (!cfg_mgr_->forwardUpdatesEnabled()) {
            next_ncr->setForwardChange(false);
            LOG_DEBUG(dhcp_to_d2_logger, isc::log::DBGLVL_TRACE_DETAIL_DATA,
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
                return (false);
            }

            ++direction_count;
        }
    }

    // If reverse change is enabled, match to reverse servers.
    DdnsDomainPtr reverse_domain;
    if (next_ncr->isReverseChange()) {
        if (!cfg_mgr_->reverseUpdatesEnabled()) {
            next_ncr->setReverseChange(false);
            LOG_DEBUG(dhcp_to_d2_logger, isc::log::DBGLVL_TRACE_DETAIL_DATA,
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
                return (false);
            }

            ++direction_count;
        }
    }

    // If there is nothing to actually do, then the request falls on the floor.
    // Should we log this?
    if (!direction_count) {
        LOG_DEBUG(dhcp_to_d2_logger, isc::log::DBGLVL_TRACE_DETAIL_DATA,
                  DHCP_DDNS_REQUEST_DROPPED)
                  .arg(next_ncr->getRequestId())
                  .arg(next_ncr->toText());
        return (false);
    }

    // We matched to the required servers, so construct the transaction.
    // @todo If multi-threading is implemented, one would pass in an
    // empty IOServicePtr, rather than our instance value.  This would cause
    // the transaction to instantiate its own, separate IOService to handle
    // the transaction's IO.
    NameChangeTransactionPtr trans;
    if (next_ncr->getChangeType() == CHG_ADD) {
        switch(next_ncr->getConflictResolutionMode()) {
        case CHECK_WITH_DHCID:
            trans.reset(new NameAddTransaction(io_service_, next_ncr,
                                               forward_domain, reverse_domain,
                                               cfg_mgr_));
            break;
        case CHECK_EXISTS_WITH_DHCID:
            trans.reset(new CheckExistsAddTransaction(io_service_, next_ncr,
                                                      forward_domain, reverse_domain,
                                                      cfg_mgr_));
            break;
        case NO_CHECK_WITHOUT_DHCID:
            trans.reset(new SimpleAddWithoutDHCIDTransaction(io_service_, next_ncr,
                                                             forward_domain, reverse_domain,
                                                             cfg_mgr_));
            break;
        default:
            // NO_CHECK_WITH_DHCID
            trans.reset(new SimpleAddTransaction(io_service_, next_ncr,
                                                 forward_domain, reverse_domain,
                                                 cfg_mgr_));
            break;
        }
    } else {
        switch(next_ncr->getConflictResolutionMode()) {
        case CHECK_WITH_DHCID:
            trans.reset(new NameRemoveTransaction(io_service_, next_ncr,
                                                  forward_domain, reverse_domain,
                                                  cfg_mgr_));
            break;
        case CHECK_EXISTS_WITH_DHCID:
            trans.reset(new CheckExistsRemoveTransaction(io_service_, next_ncr,
                                                         forward_domain, reverse_domain,
                                                         cfg_mgr_));
            break;
        case NO_CHECK_WITHOUT_DHCID:
            trans.reset(new SimpleRemoveWithoutDHCIDTransaction(io_service_, next_ncr,
                                                                forward_domain, reverse_domain,
                                                                cfg_mgr_));
            break;
        default:
            // NO_CHECK_WITH_DHCID
            trans.reset(new SimpleRemoveTransaction(io_service_, next_ncr,
                                                    forward_domain, reverse_domain,
                                                    cfg_mgr_));
            break;
        }
    }

    // Add the new transaction to the store
    auto ret = transaction_store_.push_back(trans);
    if (ret.second == false) {
        // Shouldn't happen, as pickNextJob() just checked.
        isc_throw(D2UpdateMgrError, "Transaction already in progress for FQDN "
            << trans->getFqdn() << " or address " << trans->getIOAddress());
    }

    // Start it.
    trans->startTransaction();
    return (true);
}

bool
D2UpdateMgr::hasTransaction(const dhcp_ddns::NameChangeRequestPtr& ncr) const {
    if (!ncr) {
        isc_throw(D2UpdateMgrError,
                  "D2UpdateMgr::hasTransaction() ncr cannot be null");
    }

    // Check for fqdn first.
    auto& fidx = transaction_store_.get<FqdnTag>();
    auto fiter = fidx.find(ncr->getFqdnLower());
    if (fiter != fidx.end()) {
        return (true);
    }

    // Check for fqdn first.
    auto& aidx = transaction_store_.get<AddressTag>();
    auto aiter = aidx.find(ncr->getIOAddress());
    if (aiter != aidx.end()) {
        return (true);
    }

    return (false);
}

void
D2UpdateMgr::clearTransactions() {
    // @todo for now this just wipes them out. We might need something
    // more elegant, that allows a cancel first.
    transaction_store_.clear();
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
    return (transaction_store_.size());
}

TransactionSequenceIndex::iterator
D2UpdateMgr::transactionSequenceBegin() {
    return (transaction_store_.get<SequenceTag>().begin());
}

TransactionSequenceIndex::iterator
D2UpdateMgr::transactionSequenceEnd() {
    return (transaction_store_.get<SequenceTag>().end());
}

TransactionFqdnIndex::iterator
D2UpdateMgr::findTransactionByFqdn(const std::string& fqdn) const {
    return (transaction_store_.get<FqdnTag>().find(fqdn));
}

TransactionFqdnIndex::iterator
D2UpdateMgr::transactionFqdnBegin() {
    return (transaction_store_.get<FqdnTag>().begin());
}

TransactionFqdnIndex::iterator
D2UpdateMgr::transactionFqdnEnd() {
    return (transaction_store_.get<FqdnTag>().end());
}

TransactionAddressIndex::iterator
D2UpdateMgr::findTransactionByAddress(const asiolink::IOAddress& address) const {
    return (transaction_store_.get<AddressTag>().find(address));
}

TransactionAddressIndex::iterator
D2UpdateMgr::transactionAddressBegin() {
    return (transaction_store_.get<AddressTag>().begin());
}

TransactionAddressIndex::iterator
D2UpdateMgr::transactionAddressEnd() {
    return (transaction_store_.get<AddressTag>().end());
}


} // namespace isc::d2
} // namespace isc
