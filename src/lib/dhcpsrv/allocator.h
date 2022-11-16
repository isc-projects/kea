// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
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

    /// @brief Constructor
    ///
    /// Specifies which type of leases this allocator will assign.
    ///
    /// @param type specifies pool type (addresses, temporary addresses
    /// or prefixes).
    /// @param subnet weak pointer to the subnet owning the allocator.
    Allocator(Lease::Type type, const WeakSubnetPtr& subnet)
        : pool_type_(type),
          subnet_(subnet) {
    }

    /// @brief Virtual destructor
    virtual ~Allocator() = default;

    /// @brief Picks an address or a delegated prefix.
    ///
    /// This method returns one address from the available pools in the
    /// specified subnet. It should not check if the address is used or
    /// reserved - AllocEngine will check that and will call pickAddress
    /// again if necessary. The number of times this method is called will
    /// increase as the number of available leases will decrease.
    ///
    /// This method can also be used to pick a prefix. We should not rename
    /// it to pickLease(), because at this early stage there is no concept
    /// of a lease yet. Here it is a matter of selecting one address or
    /// prefix from the defined pool, without going into details who it is
    /// for or who uses it. I thought that pickAddress() is less confusing
    /// than pickResource(), because nobody would immediately know what the
    /// resource means in this context.
    ///
    /// Pools which are not allowed for client classes are skipped.
    ///
    /// @param client_classes list of classes client belongs to
    /// @param duid Client's DUID
    /// @param hint Client's hint
    ///
    /// @return the next address.
    virtual isc::asiolink::IOAddress
    pickAddress(const ClientClasses& client_classes,
                const DuidPtr& duid,
                const asiolink::IOAddress& hint) {
        util::MultiThreadingLock lock(mutex_);
        return (pickAddressInternal(client_classes, duid, hint));
    }

private:

    /// @brief Picks an address or delegated prefix.
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
                        const DuidPtr& duid,
                        const isc::asiolink::IOAddress& hint) = 0;

protected:

    /// @brief Defines pool type allocation
    Lease::Type pool_type_;

    /// @brief Weak pointer to the subnet owning the allocator.
    WeakSubnetPtr subnet_;

private:

    /// @brief The mutex to protect the allocated lease.
    std::mutex mutex_;
};

/// Defines a pointer to an allocator.
typedef boost::shared_ptr<Allocator> AllocatorPtr;

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // ALLOCATOR_H
