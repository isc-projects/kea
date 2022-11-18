// Copyright (C) 2014-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SUBNET_ID_H
#define SUBNET_ID_H

#include <exceptions/exceptions.h>
#include <stdint.h>
#include <typeinfo>
#include <limits>
#include <set>

namespace isc {
namespace dhcp {

/// @brief Defines unique IPv4 or IPv6 subnet identifier.
///
/// Each subnet for which the DHCP service has been configured is identified
/// by the unique value called subnet id. Right now it is represented as
/// a simple unsigned integer. In the future it may be extended to more complex
/// type.
typedef uint32_t SubnetID;

/// @brief Special value is used for storing/recognizing global host reservations.
static const SubnetID SUBNET_ID_GLOBAL = 0;
/// @brief The largest valid value for auto-generated subnet IDs.
static const SubnetID SUBNET_ID_MAX = std::numeric_limits<uint32_t>::max()-1;
/// @brief Special value used to signify that a SubnetID is "not set"
static const SubnetID SUBNET_ID_UNUSED = std::numeric_limits<uint32_t>::max();

/// @brief Exception thrown upon attempt to add subnet with an ID that belongs
/// to the subnet that already exists.
class DuplicateSubnetID : public Exception {
public:
    DuplicateSubnetID(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Ordered list aka set of subnetIDs.
typedef std::set<dhcp::SubnetID> SubnetIDSet;

}
}

#endif // SUBNET_ID_H
