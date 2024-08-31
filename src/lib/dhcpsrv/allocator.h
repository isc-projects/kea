// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <asiolink/io_address.h>
#include <dhcp/classify.h>
#include <dhcp/duid.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/pool.h>
#include <util/multi_threading_mgr.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <mutex>

namespace isc {
namespace dhcp {

/// @brief Forward declaration of a @c Subnet.
///
/// We don't include the subnet header because it would cause a
/// circular dependency.
class Subnet;

/// @brief Weak pointer to the @c Subnet.
typedef boost::weak_ptr<Subnet> WeakSubnetPtr;

/// An exception that is thrown when allocation module fails (e.g. due to
/// lack of available addresses)
class AllocFailed : public Exception {
public:

    /// @brief Constructor
    ///
    /// @param file name of the file, where exception occurred
    /// @param line line of the file, where exception occurred
    /// @param what text description of the issue that caused exception
    AllocFailed(const char* file, size_t line, const char* what)
        : Exception(file, line, what) {}
};

/// @brief Base class for all address/prefix allocation algorithms.
///
/// This is an abstract class that should not be used directly, but rather
/// specialized implementations should be used instead.
///
/// This class holds a weak pointer to the subnet owning it because
/// it must not exist without the subnet. Also, it can't hold a shared
/// pointer to the subnet because it would cause a circular dependency
/// between the two.
class Allocator {
public:

    /// @brief Type of preferred PD-pool prefix length selection criteria
    enum PrefixLenMatchType {
        PREFIX_LEN_EQUAL,      // select PD-pools with specific prefix length
        PREFIX_LEN_LOWER,      // select PD-pools with lower prefix length
        PREFIX_LEN_HIGHER      // select PD-pools with higher prefix length
    };

    /// @brief Constructor
    ///
    /// Specifies which type of leases this allocator will assign.
    ///
    /// @param type specifies pool type (addresses, temporary addresses
    /// or prefixes).
    /// @param subnet weak pointer to the subnet owning the allocator.
    Allocator(Lease::Type type, const WeakSubnetPtr& subnet);

    /// @brief Virtual destructor.
    ///
    /// Removes all LeaseMgr callbacks it installed.
    virtual ~Allocator();

    /// @brief Returns allocator type string.
    ///
    /// @return allocator-specific type string.
    virtual std::string getType() const = 0;

    /// @brief Picks an address.
    ///
    /// This method returns one address from the available pools in the
    /// specified subnet. It should not check if the address is used or
    /// reserved - AllocEngine will check that and will call pickAddress
    /// again if necessary. The number of times this method is called will
    /// increase as the number of available leases will decrease.
    ///
    /// Pools which are not allowed for client classes are skipped.
    ///
    /// @param client_classes list of classes client belongs to.
    /// @param duid Client's DUID.
    /// @param hint Client's hint.
    ///
    /// @return the next address.
    virtual isc::asiolink::IOAddress
    pickAddress(const ClientClasses& client_classes,
                const IdentifierBaseTypePtr& duid,
                const asiolink::IOAddress& hint) {
        util::MultiThreadingLock lock(mutex_);
        return (pickAddressInternal(client_classes, duid, hint));
    }

    /// @brief Picks a delegated prefix.
    ///
    /// This method returns one prefix from the available pools in the
    /// specified subnet. It should not check if the prefix is used or
    /// reserved - AllocEngine will check that and will call pickPrefix
    /// again if necessary. The number of times this method is called will
    /// increase as the number of available leases will decrease.
    ///
    /// Pools which are not allowed for client classes are skipped.
    ///
    /// @param client_classes list of classes client belongs to.
    /// @param pool the selected pool satisfying all required conditions.
    /// @param duid Client's DUID.
    /// @param prefix_length_match type which indicates the selection criteria
    ///        for the pools relative to the provided hint prefix length.
    /// @param hint Client's hint.
    /// @param hint_prefix_length the hint prefix length that the client
    ///        provided. The 0 value means that there is no hint and that any
    ///        pool will suffice.
    ///
    /// @return the next prefix.
    virtual isc::asiolink::IOAddress
    pickPrefix(const ClientClasses& client_classes,
               Pool6Ptr& pool,
               const IdentifierBaseTypePtr& duid,
               PrefixLenMatchType prefix_length_match,
               const asiolink::IOAddress& hint,
               uint8_t hint_prefix_length) {
        util::MultiThreadingLock lock(mutex_);
        return (pickPrefixInternal(client_classes, pool, duid,
                                   prefix_length_match, hint,
                                   hint_prefix_length));
    }

    /// @brief Check if the pool matches the selection criteria relative to the
    /// provided hint prefix length.
    ///
    /// @param prefix_length_match type which indicates the selection criteria
    ///        for the pools relative to the provided hint prefix length.
    /// @param pool the pool checked for restricted delegated prefix length
    ///        value.
    /// @param hint_prefix_length The hint prefix length that the client
    ///        provided. The 0 value means that there is no hint and that any
    ///        pool will suffice.
    static bool isValidPrefixPool(Allocator::PrefixLenMatchType prefix_length_match,
                                  PoolPtr pool, uint8_t hint_prefix_length);

    /// @brief Performs allocator initialization after server's reconfiguration.
    ///
    /// Some allocators install callbacks in the lease manager to keep track of
    /// the lease allocations. These callbacks may only be installed when the
    /// lease manager instance is available (i.e., when the server finishes the
    /// reconfiguration). Such callbacks can be installed in this function.
    ///
    /// In this function, the allocators can also re-build their allocation states.
    void initAfterConfigure();

protected:

    /// @brief Allocator-specific initialization function.
    ///
    /// It is called by the @c initAfterConfigure and can be overridden in the
    /// derived allocators.
    virtual void initAfterConfigureInternal() {};

private:

    /// @brief Picks an address.
    ///
    /// Internal thread-unsafe implementation of the @c pickAddress.
    /// Derived classes must provide their specific implementations of
    /// this function.
    ///
    /// @param client_classes list of classes client belongs to
    /// @param duid Client's DUID
    /// @param hint Client's hint
    ///
    /// @return the next address.
    virtual isc::asiolink::IOAddress
    pickAddressInternal(const ClientClasses& client_classes,
                        const IdentifierBaseTypePtr& duid,
                        const isc::asiolink::IOAddress& hint) = 0;

    /// @brief Picks a delegated prefix.
    ///
    /// Internal thread-unsafe implementation of the @c pickPrefix.
    /// Derived classes must provide their specific implementations of
    /// this function.
    ///
    /// @param client_classes list of classes client belongs to.
    /// @param pool the selected pool satisfying all required conditions.
    /// @param duid Client's DUID.
    /// @param prefix_length_match type which indicates the selection criteria
    ///        for the pools relative to the provided hint prefix length.
    /// @param hint Client's hint.
    /// @param hint_prefix_length the hint prefix length that the client
    ///        provided. The 0 value means that there is no hint and that any
    ///        pool will suffice.
    ///
    /// @return the next prefix.
    virtual isc::asiolink::IOAddress
    pickPrefixInternal(const ClientClasses& client_classes,
                       Pool6Ptr& pool,
                       const IdentifierBaseTypePtr& duid,
                       PrefixLenMatchType prefix_length_match,
                       const isc::asiolink::IOAddress& hint,
                       uint8_t hint_prefix_length) = 0;

protected:

    /// @brief Indicates if the allocator has been initialized.
    ///
    /// It is set to true when @c initAfterConfigure has been called.
    /// It prevents initializing the allocator several times.
    bool inited_;

    /// @brief Defines pool type allocation
    Lease::Type pool_type_;

    /// @brief ID of a subnet to which the allocator belongs.
    SubnetID subnet_id_;

    /// @brief Weak pointer to the subnet owning the allocator.
    WeakSubnetPtr subnet_;

    /// @brief The mutex to protect the allocated lease.
    std::mutex mutex_;
};

/// Defines a pointer to an allocator.
typedef boost::shared_ptr<Allocator> AllocatorPtr;

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // ALLOCATOR_H
