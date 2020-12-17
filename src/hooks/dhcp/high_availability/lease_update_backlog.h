// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HA_LEASE_BACKLOG_H
#define HA_LEASE_BACKLOG_H

#include <dhcpsrv/lease.h>
#include <deque>
#include <utility>

namespace isc {
namespace ha {

/// @brief Queue holding a backlog of unsent lease updates.
///
/// Lease updates are appended to this queue when the service is in the
/// communication-recovery state. In this state, the server temporarily
/// lost communication with the partner and can't send lease updates.
/// The server keeps responding to DHCP queries but it must store unsent
/// lease updates and later send them when the communication is resumed.
/// The lease updates are stored in this queue.
///
/// This queue has configurable size. If the number of leases appended
/// to the queue reaches the limit, no more updates can be added to it.
/// This prevents inifinite growth of the queue and excessive memory
/// consumption.
///
/// There are two types of lease updates: "Add" and "Delete". The type
/// is specified when the lease is appended to the queue.
///
/// @tparam LeaseTypePtr Type of the lease, i.e. @c Lease4Ptr or
/// @c Lease6Ptr.
template<typename LeaseTypePtr>
class LeaseUpdateBacklog {
public:

    /// @brief Type of the lease update (operation type).
    enum OpType {
        ADD,
        DELETE
    };

    /// @brief Constructor.
    ///
    /// @param limit specifies the maximum number of lease updates which
    /// can be stored in the queue.
    LeaseUpdateBacklog(const size_t limit)
        : limit_(limit), overflown_(false), outstanding_updates_() {
    }

    /// @brief Appends lease update to the queue.
    ///
    /// @param op_type type of the lease update (operation type).
    /// @param lease pointer to the lease being added, or deleted.
    /// @return boolean value indicating whether the lease was successfully
    /// appended to the queue (if true) or not (if false).
    bool push(const OpType op_type, const LeaseTypePtr& lease) {
        if (outstanding_updates_.size() >= limit_) {
            overflown_ = true;
            return (false);
        }
        outstanding_updates_.push_back(std::make_pair(op_type, lease));
        return (true);
    }

    /// @brief Returns the next lease update and removes it from the queue.
    ///
    /// @param [out] op_type reference to the value receiving lease update type.
    /// @return pointer to the next lease update in the queue or null pointer
    /// when the queue is empty.
    LeaseTypePtr pop(OpType& op_type) {
        if (outstanding_updates_.empty()) {
            return (LeaseTypePtr());
        }
        auto item = outstanding_updates_.front();
        outstanding_updates_.pop_front();
        op_type = item.first;
        return (item.second);
    }

    /// @brief Checks if the queue was overflown.
    ///
    /// This method returns true if the number of lease updates exceeded
    /// the queue size limit at any point. The HA service checks this
    /// flag when the communication with the partner is resumed to make
    /// decisions about lease synchronization. If the queue was not
    /// overflown, the server will send lease updates which are sitting
    /// in the queue. Otherwise, it will go over the fully blown lease
    /// database synchronization process.
    ///
    /// This flag is reset to false when @c clear is called.
    ///
    /// @return true if the queue was overflown, false otherwise.
    bool wasOverflown() const {
        return (overflown_);
    }

    /// @brief Removes all lease updates from the queue.
    ///
    /// It also resets the flag indicating that the queue was overflown.
    void clear() {
        outstanding_updates_.clear();
        overflown_ = false;
    }

    /// @brief Returns the current size of the queue.
    size_t size() const {
        return (outstanding_updates_.size());
    }

private:

    /// @brief Holds the queue size limit.
    size_t limit_;

    /// @brief Remebers whether the queue was overflown.
    bool overflown_;

    /// @brief Actual queue of lease updates and their types.
    std::deque<std::pair<OpType, LeaseTypePtr> > outstanding_updates_;
};

/// @brief Pointer to a backlog of DHCPv4 lease updates.
typedef LeaseUpdateBacklog<dhcp::Lease4Ptr> Lease4UpdateBacklog;

/// @brief Pointer to a backlog of DHCPv6 lease updates.
typedef LeaseUpdateBacklog<dhcp::Lease6Ptr> Lease6UpdateBacklog;

} // end of namespace isc::ha
} // end of namespace isc

#endif // HA_LEASE_BACKLOG_H
