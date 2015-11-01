// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

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

    /// @name DHCPv4-over-DHCPv6 flag
    bool dhcp4o6_;

    /// @brief Address on which the message was received.
    asiolink::IOAddress local_address_;
    /// @brief Source address of the message.
    asiolink::IOAddress remote_address_;
    /// @brief Classes that the client belongs to.
    ClientClasses client_classes_;
    /// @brief Name of the interface on which the message was received.
    std::string iface_name_;

    /// @brief Default constructor.
    ///
    /// Sets the default values for the @c Selector.
    SubnetSelector()
        : ciaddr_(asiolink::IOAddress("0.0.0.0")),
          giaddr_(asiolink::IOAddress("0.0.0.0")),
          option_select_(asiolink::IOAddress("0.0.0.0")),
          interface_id_(),
          first_relay_linkaddr_(asiolink::IOAddress("::")),
          dhcp4o6_(false),
          local_address_(asiolink::IOAddress("0.0.0.0")),
          remote_address_(asiolink::IOAddress("0.0.0.0")),
          client_classes_(), iface_name_(std::string()) {
    }
};


}
}

#endif // SUBNET_SELECTOR_H
