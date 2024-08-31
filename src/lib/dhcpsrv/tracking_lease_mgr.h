// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TRACKING_LEASE_MGR_H
#define TRACKING_LEASE_MGR_H

#include <asiolink/io_address.h>
#include <dhcpsrv/lease_mgr.h>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <string>
#include <unordered_set>

namespace isc {
namespace dhcp {

/// @brief Introduces callbacks into the @c LeaseMgr.
///
/// The LeaseMgr is a central point of lease management and is aware of all
/// lease changes within the server instance. Thus, it is a good opportunity
/// to allow installing callbacks in the @c LeaseMgr to track all lease
/// changes. An allocator maintaining a list of free leases (FLQ allocator)
/// can benefit from it by/ installing the callbacks that add or remove
/// free leases from this list, depending on the lease manager's activity.
/// The callbacks are invoked regardless if the lease changes result from a
/// normal lease allocation or a control command. The callbacks can also be
/// useful for maintaining a log of lease changes. Such a log could be made
/// available externally and consumed by another application (e.g., Stork).
///
/// The lease manager can track three types of calls: new lease insertion
/// (add), an existing lease update, and lease deletion. Even though the
/// lease reclamation is similar to deleting a lease because it becomes free,
/// it is a lease update from the lease manager's standpoint. Currently,
/// the lease manager cannot track the deletion of the reclaimed leases
/// (i.e., the leases in the expired-reclaimed state).
///
/// The lease backends should call the suitable tracking functions:
/// @c trackAddLease, @c trackUpdateLease, and @c trackDeleteLease.
/// However, the backends must ensure that there are no race conditions
/// between modifying the lease in the database and running the callbacks.
/// Suppose that two threads modify the same lease. Thread A inserts the
/// lease in the database, and thread B removes it. The callback for
/// thread A should be invoked before the callback for thread B. If they
/// are invoked in reverse order, it can result in an inconsistent state
/// in the free lease queue allocator because the allocator should record
/// the lease as available after the thread B callback. The reverse
/// invocation order would result in marking the lease as unavailable for
/// allocation after both callbacks.
///
/// The race condition does not occur for the Memfile backend because it
/// guards entire functions with a mutex. However, the SQL backends rely
/// on the database to guard against concurrent writes. In these cases,
/// the backend must protect against the reverse order of callbacks. They
/// should use the lease locking mechanism introduced in the
/// @c TrackingLeaseMgr.
///
/// The lease locking is modeled on an @c unordered_set container holding
/// the leases with the ongoing allocations. The leases are inserted into
/// this container by the @c tryLock function. If another thread has already
/// locked the lease, this function returns @c false to indicate an
/// unsuccessful attempt. In this case, the thread should resign from updating
/// the lease and return early. It can result in a lease allocation failure,
/// but two concurrent threads extremely rarely work on allocating a lease for
/// the same client. A passive wait could be another option here, but it is a
/// much more complicated solution for a bit of gain.
class TrackingLeaseMgr : public LeaseMgr {
public:

    /// The @c LeaseMgrFactory manages the @c LeaseMgr instances and has
    /// to be able to move installed callbacks between them. No other external
    /// class can have access to the callbacks container. Thus, we can't make
    /// the container public. The friend declaration deals with it cleanly.
    friend class LeaseMgrFactory;

    /// @brief An enumeration differentiating between lease write operations.
    typedef enum {
        TRACK_ADD_LEASE,
        TRACK_UPDATE_LEASE,
        TRACK_DELETE_LEASE
    } CallbackType;

    /// @brief Type of a callback function invoked upon a lease insertion,
    /// update or deletion.
    ///
    /// The first argument is a pointer to the lease for which the callback
    /// is invoked.
    typedef std::function<void(LeasePtr)> CallbackFn;

    /// @brief A structure representing a registered callback.
    ///
    /// It associates the callback with a type, its owner, subnet
    /// identifier, and a lease type. The owner is a string specified
    /// by the registration function caller. There must be at most one
    /// callback registered for the particular owner, subnet identifier
    /// and the lease type.
    typedef struct {
        /// @brief Callback type (i.e., lease add, update, delete).
        CallbackType type;

        /// @brief An entity owning callback registration (e.g., FLQ allocator).
        std::string owner;

        /// Subnet identifier associated with the callback.
        SubnetID subnet_id;

        /// @brief Lease types for which the callback should be invoked.
        Lease::Type lease_type;

        /// @brief Callback function.
        CallbackFn fn;
    } Callback;

protected:

    /// @brief A multi-index container holding registered callbacks.
    ///
    /// The callbacks are accessible via two indexes. The first composite index
    /// filters the callbacks by the callback type (i.e., lease add, update or delete)
    /// and the subnet id. The second index filters the callbacks by the subnet id
    /// and the lease type.
    typedef boost::multi_index_container<
        Callback,
        boost::multi_index::indexed_by<
            boost::multi_index::ordered_non_unique<
                boost::multi_index::composite_key<
                    Callback,
                    boost::multi_index::member<Callback, CallbackType, &Callback::type>,
                    boost::multi_index::member<Callback, SubnetID, &Callback::subnet_id>,
                    boost::multi_index::member<Callback, Lease::Type, &Callback::lease_type>
                >
            >,
            boost::multi_index::ordered_non_unique<
                boost::multi_index::composite_key<
                    Callback,
                    boost::multi_index::member<Callback, SubnetID, &Callback::subnet_id>,
                    boost::multi_index::member<Callback, Lease::Type, &Callback::lease_type>
                >
            >
        >
    > CallbackContainer;

    /// @brief Pointer to the callback container.
    typedef boost::shared_ptr<CallbackContainer> CallbackContainerPtr;

    /// @brief Constructor.
    TrackingLeaseMgr();

    /// @brief Attempts to lock a lease.
    ///
    /// If a lease is successfully locked, no other thread can lock it. It protects
    /// against running the callbacks out of order when two threads modify the same
    /// lease. Such a locking should only be used when the lease allocation followed by
    /// the callbacks invocation are not protected by some other synchronization
    /// mechanism. In particular, the Memfile backend uses a mutex for locking in the
    /// lease allocation functions. In this case, it is unnecessary to apply a lock at the
    /// lease level. The SQL backends rely on the database locking mechanisms to prevent
    /// the concurrent updates of the same lease. These backends must use the lease locking
    /// to ensure the correct callbacks invocation order.
    ///
    /// This function is not thread-safe and must be invoked in a thread-safe context.
    ///
    /// @param lease a lease instance for which the lock should be attempted.
    /// @return true when locking was successful, false otherwise. In the latter case,
    /// the thread should stop a lease allocation or deallocation attempt.
    bool tryLock(const LeasePtr& lease);

    /// @brief Attempts to unlock a lease.
    ///
    /// This function is not thread-safe and must be invoked in a thread-safe context.
    ///
    /// @param lease a lease instance for which unlocking should be attempted.
    void unlock(const LeasePtr& lease);

public:

    /// @brief Checks if the lease is locked.
    ///
    /// This function is useful in the unit tests.
    ///
    /// @return true if the lease is locked, false otherwise.
    bool isLocked(const LeasePtr& lease);

protected:

    /// @brief Invokes the callbacks when a new lease is added.
    ///
    /// It executes all callbacks of the @c TRACK_ADD_LEASE type for a subnet id of 0
    /// and the subnet id associated with the lease.
    ///
    /// The callbacks execution order is not guaranteed.
    ///
    /// @param lease new lease instance.
    void trackAddLease(const LeasePtr& lease);

    /// @brief Invokes the callbacks when a lease is updated.
    ///
    /// It executes all callbacks of the @c TRACK_UPDATE_LEASE type for a subnet id of 0
    /// and the subnet id associated with the lease.
    ///
    /// The callbacks execution order is not guaranteed.
    ///
    /// @param lease updated lease instance.
    void trackUpdateLease(const LeasePtr& lease);

    /// @brief Invokes the callbacks when a lease is deleted.
    ///
    /// It executes all callbacks of the @c TRACK_DELETE_LEASE type for a subnet id of 0
    /// and the subnet id associated with the lease.
    ///
    /// The callbacks execution order is not guaranteed.
    ///
    /// @param lease deleted lease instance.
    void trackDeleteLease(const LeasePtr& lease);

public:

    /// @brief Registers a callback function for a subnet.
    ///
    /// @param type callback type.
    /// @param owner callback owner identifier.
    /// @param subnet_id subnet identifier; it can be set to 0 if the callback should be
    /// called for all subnets.
    /// @param lease_type a lease type.
    /// @param callback_fn callback function instance.
    /// @throw InvalidOperation when the callback has been already registered for the given owner and
    /// the subnet identifier.
    void registerCallback(CallbackType type, std::string owner, SubnetID subnet_id,
                          Lease::Type lease_type, CallbackFn callback_fn);

    /// @brief Registers a callback function for all subnets.
    ///
    /// @param type callback type.
    /// @param owner callback owner identifier.
    /// @param lease_type a lease type.
    /// @param callback_fn callback function instance.
    /// @throw InvalidOperation when the callback has been already registered for the given owner and
    /// all subnets.
    void registerCallback(CallbackType type, std::string owner, Lease::Type lease_type,
                          CallbackFn callback_fn);

    /// @brief Unregisters all callbacks for a given subnet identifier.
    ///
    /// @param subnet_id a subnet identifier.
    /// @param lease_type a lease type.
    void unregisterCallbacks(SubnetID subnet_id, Lease::Type lease_type);

    /// @brief Unregisters all callbacks.
    void unregisterAllCallbacks();

    /// @brief Checks if any callbacks have been registered.
    ///
    /// It is a quick check to be performed by the backends whether or not
    /// the callbacks mechanism is used.
    ///
    /// @return true if any callbacks have been registered.
    bool hasCallbacks() const;

protected:

    /// @brief Converts callback type to string for logging purposes.
    ///
    /// @param type callback type.
    /// @return callback type name or the 'unknown' string.
    static std::string callbackTypeToString(CallbackType type);

    /// @brief Runs registered callbacks of the particular type.
    ///
    /// The specified lease instance contains the subnet identifier used to
    /// filter the callbacks to be invoked.
    ///
    /// @param type callback type.
    /// @param lease lease instance for which the callbacks are invoked.
    void runCallbacks(CallbackType type, const LeasePtr& lease);

    /// @brief Runs registered callbacks of the particular type for a subnet id.
    ///
    /// It is called internally by the @c runCallbacks function.
    ///
    /// @param type callback type.
    /// @param subnet_id subnet identifier for which the callbacks are invoked.
    /// @param lease lease instance for which the callbacks are invoked.
    void runCallbacksForSubnetID(CallbackType type, SubnetID subnet_id,
                                 const LeasePtr& lease);

    /// @brief The multi-index container holding registered callbacks.
    CallbackContainerPtr callbacks_;

    /// @brief A set of locked leases.
    ///
    /// It is empty if locking is not used (e.g. Memfile backend) or when there
    /// are no ongoing allocations.
    std::unordered_set<asiolink::IOAddress, asiolink::IOAddress::Hash> locked_leases_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // TRACKING_LEASE_MGR_H
