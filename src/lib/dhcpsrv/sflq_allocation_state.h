// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SFLQ_ALLOCATION_STATE_H
#define SFLQ_ALLOCATION_STATE_H

#include <asiolink/io_address.h>
#include <dhcpsrv/allocation_state.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet.h>
#include <boost/shared_ptr.hpp>
#include <cstdint>
#include <map>

namespace isc {
namespace dhcp {

/// @brief Forward declaration of the @c SubnetSflqAllocationState.
class SubnetSflqAllocationState;

/// @brief Type of the pointer to the @c SubnetSflqAllocationState.
typedef boost::shared_ptr<SubnetSflqAllocationState> SubnetSflqAllocationStatePtr;

/// @brief Subnet allocation state used by the shared-flq allocator.
///
/// It exposes the base class mechanism to store the last allocation time
/// for various lease types. These times are used by the shared networks to
/// find the "preferred" subnet (i.e., a subnet from which the latest lease
/// was assigned).
class SubnetSflqAllocationState : public SubnetAllocationState {
public:

    /// @brief Constructor.
    SubnetSflqAllocationState();

    /// @brief Destructor.
    virtual ~SubnetSflqAllocationState() {};

    /// @brief Set last allocated time.
    ///
    /// @param last_time time of last allocation. If not specified
    /// it is set to the current time.
    void setLastAllocatedTime(boost::posix_time::ptime last_time =
                              boost::posix_time::not_a_date_time);
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // SFLQ_ALLOCATION_STATE_H
