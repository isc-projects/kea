// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_HOSTS_UTIL_H
#define CFG_HOSTS_UTIL_H

#include <cc/data.h>
#include <dhcpsrv/subnet_id.h>

namespace isc {
namespace dhcp {

/// @brief Utility class to represent host reservation configurations
/// internally as a map keyed by subnet IDs, externally as a list Element.
class CfgHostsList {
public:

    /// The type of the internal map
    typedef std::map<SubnetID, isc::data::ElementPtr> CfgHostsMap;

    /// @brief Internalize a list Element
    ///
    /// This method gets a list Element and builds the internal map from it.
    ///
    /// @param list the list Element
    void internalize(isc::data::ConstElementPtr list);

    /// @brief Externalize the map to a list Element
    ///
    /// @return a list Element representing all host reservations
    isc::data::ElementPtr externalize() const;

    /// @brief Add a host reservation to the map
    void add(SubnetID id, isc::data::ElementPtr resv);

    /// @brief Return the host reservations for a subnet ID
    ///
    /// @param id the subnet ID
    /// @return a list Element with host reservations
    isc::data::ConstElementPtr get(SubnetID id) const;

private:
    /// @brief The internal map
    CfgHostsMap map_;
};

}
}

#endif // CFG_HOSTS_UTIL_H
