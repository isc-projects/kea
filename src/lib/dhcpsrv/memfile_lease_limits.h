// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MEMFILE_LEASE_LIMITS_H
#define MEMFILE_LEASE_LIMITS_H

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/classify.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet_id.h>
#include <stats/stats_mgr.h>

#include <unordered_map>

namespace isc {
namespace dhcp {

/// @brief Container that maintains counts of leases per class and lease type.
///
/// For methods on this class which accept the lease type as a parameter the value
/// is one of the following Lease::TYPE_V4, Lease::TYPE_NA, Lease::TYPE_PD.  Kea
/// does not support Lease::TYPE_TA leases and this value is treated as invalid.
/// Note that for simplicity and performance an instance of container is assumed
/// to be used either only for DHCPv4 processing or DHCPv6 processing but not both
/// concurrently.
class ClassLeaseCounter {
public:
    /// @brief Defines ClassCountMap as an unordered map of counts.
    typedef std::unordered_map<ClientClass, size_t> ClassCountMap;

    /// @brief Constructor
    ClassLeaseCounter() = default;

    /// @brief Destructor
    ~ClassLeaseCounter() = default;

    /// @brief Fetches the lease count for the given class and lease type.
    ///
    /// @param client_class class for which the count is desired
    /// @param ltype lease type for which the count is desired, defaults to
    /// Lease::TYPE_V4
    ///
    /// @return Number of leases for the class and lease type.  If there is no
    /// entry found for the class and lease type, a value of zero is returned.
    size_t getClassCount(const ClientClass& client_class,
                         const Lease::Type& ltype = Lease::TYPE_V4) const;

    /// @brief Sets the lease count for the given class and lease type to a value.
    ///
    /// @param client_class class for which the count is desired
    /// @param count new count value for the class and lease type.
    /// @param ltype lease type for which the count is desired, defaults
    /// to Lease::TYPE_V4
    void setClassCount(const ClientClass& client_class, size_t count,
                       const Lease::Type& ltype = Lease::TYPE_V4);

    /// @brief Adjust the count for a given class and lease type by a signed offset.
    ///
    /// If no entry exists in container for the class and type, a new one is created.
    ///
    /// @param client_class client class to adjust
    /// @param offset signed amount to add to the current count
    /// @param ltype lease type for which the count is desired, defaults
    /// to Lease::TYPE_V4
    void adjustClassCount(const ClientClass& client_class, int offset,
                          const Lease::Type& ltype = Lease::TYPE_V4);

    /// @brief Adjust the count for a list of classes for a lease type by
    /// a signed offset.
    ///
    /// @param classes list of classes to adjust
    /// @param offset signed amount to add the current count
    /// @param ltype lease type for which the count is desired, defaults
    /// to Lease::TYPE_V4
    void adjustClassCounts(data::ConstElementPtr classes, int offset,
                           const Lease::Type& ltype = Lease::TYPE_V4);

    /// @brief Increment the counts for all of a lease's classes by one
    ///
    /// Function is intended to be whenever a new lease is being added.
    ///
    /// @param lease lease whose classes are to be incremented
    void addLease(LeasePtr lease);

    /// @brief Adjust class lease counts given a new and old version of a lease
    ///
    /// Function is intended to be used whenever an existing lease is being updated.
    /// If, upon comparison of the two leases, either the lease states or the class
    /// lists are different then:
    ///
    /// -# Decrement the counts for the old class list if the old lease state
    /// is Lease::STATE_DEFAULT
    /// -# Increment the counts for the new class list if the new lease state
    /// is Lease::STATE_DEFAULT
    ///
    /// @param new_lease new version of the lease
    /// @param old_lease old version of the lease
    void updateLease(LeasePtr new_lease, LeasePtr old_lease);

    /// @brief Decrement the counts for all of a lease's classes by one
    ///
    /// Function is intended to be whenever an existing lease is being deleted.
    ///
    /// @param lease lease whose classes are to be decremented
    void removeLease(LeasePtr lease);

    /// @brief Remove all entries.
    void clear() {
        addresses_by_class_.clear();
        pds_by_class_.clear();
    }

    /// @brief Get the number of entries for a given lease type
    ///
    /// @param ltype type of lease for which the number of entries is desired,
    /// defaults to Lease::TYPE_V4
    ///
    /// @return Number of entries for the lease type
    size_t size(const Lease::Type& ltype = Lease::TYPE_V4) const {
        return (getConstCountMap(ltype).size());
    }

    /// @brief Fetches the list of classes from the lease's user-context
    ///
    /// @param lease lease from which to fetch classes
    /// @return ElementPtr to an Element::List containing the client classes or an
    /// empty List.
    static data::ConstElementPtr getLeaseClientClasses(LeasePtr lease);

private:
    /// @brief Fetches the map used to count the given lease type.
    ///
    /// @param ltype type of lease of for which the map is desired,
    /// defaults to Lease::TYPE_V4
    ///
    /// @return Reference to the map for the lease type
    ClassCountMap& getCountMap(const Lease::Type& ltype = Lease::TYPE_V4) {
        return (ltype == Lease::TYPE_PD ? pds_by_class_ : addresses_by_class_);
    }

    const ClassCountMap& getConstCountMap(const Lease::Type& ltype = Lease::TYPE_V4) const {
        return (ltype == Lease::TYPE_PD ? pds_by_class_ : addresses_by_class_);
    }

    /// @brief Contains counts for classes for addresses.  This map is used
    /// to house either Lease::TYPE_V4 when used for V4 or Lease::TYPE_NA
    /// when used for V6.
    ClassCountMap addresses_by_class_;

    /// @brief Contains counts for classes for Lease::TYPE_PD.  Applicable
    /// only for V6 use.
    ClassCountMap pds_by_class_;
};

}  // namespace dhcp
}  // namespace isc

#endif // MEMFILE_LEASE_LIMITS_H
