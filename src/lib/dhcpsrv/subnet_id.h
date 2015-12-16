// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SUBNET_ID_H
#define SUBNET_ID_H

#include <exceptions/exceptions.h>
#include <stdint.h>

namespace isc {
namespace dhcp {

/// @brief Defines unique IPv4 or IPv6 subnet identifier.
///
/// Each subnet for which the DHCP service has been configured is identifed
/// by the unique value called subnet id. Right now it is represented as
/// a simple unsigned integer. In the future it may be extended to more complex
/// type.
typedef uint32_t SubnetID;

/// @brief Exception thrown upon attempt to add subnet with an ID that belongs
/// to the subnet that already exists.
class DuplicateSubnetID : public Exception {
public:
    DuplicateSubnetID(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

}
}

#endif // SUBNET_ID_H
