// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_4OVER6_H
#define CFG_4OVER6_H

#include <asiolink/io_address.h>
#include <cc/cfg_to_element.h>
#include <util/optional.h>
#include <string>

namespace isc {
namespace dhcp {

/// @brief This structure contains information about DHCP4o6 (RFC7341)
///
/// DHCP4o6 is completely optional. If it is not enabled, this structure
/// does not contain any information.
struct Cfg4o6 : public isc::data::CfgToElement {

    /// the default constructor.
    ///
    /// Initializes fields to their default value.
    Cfg4o6()
    :enabled_(false), subnet4o6_(std::make_pair(asiolink::IOAddress("::"), 128u), true) {
    }

    /// @brief Returns whether the DHCP4o6 is enabled or not.
    /// @return true if enabled
    bool enabled() const {
        return (enabled_);
    }

    /// @brief Sets the DHCP4o6 enabled status.
    /// @param enabled specifies if the DHCP4o6 should be enabled or not
    void enabled(bool enabled) {
        enabled_ = enabled;
    }

    /// @brief Returns the DHCP4o6 interface.
    /// @return value of the 4o6-interface parameter.
    util::Optional<std::string> getIface4o6() const {
        return (iface4o6_);
    }

    /// @brief Sets the 4o6-interface.
    /// @param iface name of the network interface the 4o6 traffic is received on
    void setIface4o6(const std::string& iface) {
        iface4o6_ = iface;
        enabled_ = true;
    }

    /// @brief Returns prefix/len for the IPv6 subnet.
    /// @return prefix/length pair
    util::Optional<std::pair<asiolink::IOAddress, uint8_t> > getSubnet4o6() const {
        return (subnet4o6_);
    }

    /// @brief Sets the prefix/length information (content of the 4o6-subnet).
    /// @param subnet IOAddress that represents a prefix
    /// @param prefix specifies prefix length
    void setSubnet4o6(const asiolink::IOAddress& subnet, uint8_t prefix) {
        subnet4o6_ = std::make_pair(subnet, prefix);
        enabled_ = true;
    }

    /// @brief Returns the interface-id.
    /// @return the option representing interface-id (or NULL)
    OptionPtr getInterfaceId() const {
        return (interface_id_);
    }

    /// @brief Sets the interface-id
    /// @param opt option to be used as interface-id match
    void setInterfaceId(const OptionPtr& opt) {
        interface_id_ = opt;
        enabled_ = true;
    }

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

private:

    /// Specifies if 4o6 is enabled on this subnet.
    bool enabled_;

    /// Specifies the network interface used as v4 subnet selector.
    util::Optional<std::string> iface4o6_;

    /// Specifies the IPv6 subnet used for v4 subnet selection.
    util::Optional<std::pair<asiolink::IOAddress, uint8_t> > subnet4o6_;

    /// Specifies the v6 interface-id used for v4 subnet selection.
    OptionPtr interface_id_;
};

} // end of isc::dhcp namespace
} // end of isc namespace

#endif
