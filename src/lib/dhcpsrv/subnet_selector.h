// Copyright (C) 2014-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SUBNET_SELECTOR_H
#define SUBNET_SELECTOR_H

#include <asiolink/io_address.h>
#include <dhcp/classify.h>
#include <dhcp/option.h>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Subnet selector used to specify parameters used to select a subnet.
///
/// This structure holds various parameters extracted from a packet sent
/// by a DHCP client used to select the subnet for the client. This selector
/// is common for IPv4 and IPv6 subnets.
struct SubnetSelector {
    /// @name DHCPv4 specific parameters.
    //@{
    /// @brief ciaddr from the client's message.
    asiolink::IOAddress ciaddr_;
    /// @brief giaddr from the client's message.
    asiolink::IOAddress giaddr_;
    /// @brief RAI link select or subnet select option
    asiolink::IOAddress option_select_;
    //@}

    /// @name DHCPv6 specific parameters.
    //@{
    /// @brief Interface id option.
    OptionPtr interface_id_;
    /// @brief First relay link address.
    asiolink::IOAddress first_relay_linkaddr_;
    //@}

    /// @brief Address on which the message was received.
    asiolink::IOAddress local_address_;
    /// @brief Source address of the message.
    asiolink::IOAddress remote_address_;
    /// @brief Classes that the client belongs to.
    ClientClasses client_classes_;
    /// @brief Name of the interface on which the message was received.
    std::string iface_name_;

    /// @brief Specifies if the packet is DHCP4o6
    bool dhcp4o6_;

    /// @brief Default constructor.
    ///
    /// Sets the default values for the @c Selector.
    SubnetSelector()
        : ciaddr_(asiolink::IOAddress("0.0.0.0")),
          giaddr_(asiolink::IOAddress("0.0.0.0")),
          option_select_(asiolink::IOAddress("0.0.0.0")),
          interface_id_(),
          first_relay_linkaddr_(asiolink::IOAddress("::")),
          local_address_(asiolink::IOAddress("0.0.0.0")),
          remote_address_(asiolink::IOAddress("0.0.0.0")),
          client_classes_(), iface_name_(std::string()),
          dhcp4o6_(false) {
    }
};


}
}

#endif // SUBNET_SELECTOR_H
