// Copyright (C) 2015-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_4OVER6_H
#define CFG_4OVER6_H

#include <asiolink/io_address.h>
#include <dhcp/option_data_types.h>
#include <cc/cfg_to_element.h>
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
    :enabled_(false), subnet4o6_(std::make_pair(asiolink::IOAddress("::"), 128u)) {
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
    std::string getIface4o6() const {
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
    std::pair<asiolink::IOAddress, uint8_t> getSubnet4o6() const {
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

    /// @brief Returns the offset for address plus port.
    /// @return the offset for address plus port
    uint8_t getPsidOffset() const {
        return (psid_offset_.asUint8());
    }

    /// @brief Sets the offset for address plus port
    /// @param offset the offset for address plus port
    void setPsidOffset(const uint8_t offset) {
        psid_offset_ = PSIDOffset(offset);
    }

    /// @brief Returns the psid-len for address plus port.
    /// @return the psid-len for address plus port
    uint8_t getPsidLen() const {
        return (psid_len_.asUint8());
    }

    /// @brief Sets the psid-len for address plus port
    /// @param psid_len the psid-len for address plus port
    void setPsidLen(const uint8_t psid_len) {
        psid_len_ = PSIDLen(psid_len);
    }

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

private:

    /// Specifies if 4o6 is enabled on this subnet.
    bool enabled_;

    /// Specifies the network interface used as v4 subnet selector.
    std::string iface4o6_;

    /// Specifies the IPv6 subnet used for v4 subnet selection.
    std::pair<asiolink::IOAddress, uint8_t> subnet4o6_;

    /// Specifies the v6 interface-id used for v4 subnet selection.
    OptionPtr interface_id_;

    /// Specifies offset.
    PSIDOffset psid_offset_;

    /// Specifies PSID len.
    PSIDLen psid_len_;
};

} // end of isc::dhcp namespace
} // end of isc namespace

#endif
