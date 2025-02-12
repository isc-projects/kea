// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>

namespace isc {
namespace legal_log {

/// @brief Checks if legal logging is disabled for a subnet.
///
/// @param subnet pointer to a subnet (v4 or v6).
/// @tparam SubnetPtrType Type of the subnet pointer: @c Subnet4Ptr or @c Subnet6Ptr.
template<typename SubnetPtrType>
bool isLoggingDisabled(const SubnetPtrType& subnet) {
    if (subnet) {
        data::ConstElementPtr context = subnet->getContext();
        // Context must be a map if specified.
        if (context && (context->getType() == data::Element::map)) {
            data::ConstElementPtr do_legal_logging = context->get("legal-logging");
            // "legal-logging" parameter must be a boolean, if specified.
            if (do_legal_logging && (do_legal_logging->getType() == data::Element::boolean)) {
                return (!do_legal_logging->boolValue());
            }
        }
    }
    // legal-logging parameter not specified, so default to false.
    return (false);
}

} // end of namespace isc::dhcp
} // end of namespace isc
