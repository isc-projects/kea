// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/iface_mgr.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/dhcpsrv_log.h>

using namespace isc::asiolink;

namespace {

/// @brief Returns @c IOAddress object set to "0.0.0.0".
const IOAddress& ZERO_ADDRESS() {
    static IOAddress address("0.0.0.0");
    return (address);
}

/// @brief Returns @c IOAddress object holding broadcast address.
const IOAddress& BCAST_ADDRESS() {
    static IOAddress address("255.255.255.255");
    return (address);
}

} // end of anonymous namespace

namespace isc {
namespace dhcp {

CfgSubnets4::Selector::Selector()
    : ciaddr_(ZERO_ADDRESS()), giaddr_(ZERO_ADDRESS()),
      local_address_(ZERO_ADDRESS()), remote_address_(ZERO_ADDRESS()),
      client_classes_(ClientClasses()), iface_name_(std::string()) {
}

void
CfgSubnets4::add(const Subnet4Ptr& subnet) {
    /// @todo: Check that this new subnet does not cross boundaries of any
    /// other already defined subnet.
    if (isDuplicate(*subnet)) {
        isc_throw(isc::dhcp::DuplicateSubnet4ID, "ID of the new IPv4 subnet '"
                  << subnet->getID() << "' is already in use");
    }
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_ADD_SUBNET4)
              .arg(subnet->toText());
    subnets_.push_back(subnet);
}

Subnet4Ptr
CfgSubnets4::get(const Selector& selector) const {
    // If relayed message has been received, try to match the giaddr with the
    // relay address specified for a subnet. It is also possible that the relay
    // address will not match with any of the relay addresses accross all
    // subnets, but we need to verify that for all subnets before we can try
    // to use the giaddr to match with the subnet prefix.
    if (selector.giaddr_ != ZERO_ADDRESS()) {
        for (Subnet4Collection::const_iterator subnet = subnets_.begin();
             subnet != subnets_.end(); ++subnet) {
            // Eliminate those subnets that do not meet client class criteria.
            if (!(*subnet)->clientSupported(selector.client_classes_)) {
                continue;
            }

            // Check if the giaddr is equal to the one defined for the subnet.
            if (selector.giaddr_ == (*subnet)->getRelayInfo().addr_) {
                return (*subnet);
            }
        }
    }

    // If we got to this point it means that we were not able to match the
    // giaddr with any of the addresses specified for subnets. Let's determine
    // what address from the client's packet to use to match with the
    // subnets' prefixes.

    IOAddress address = ZERO_ADDRESS();
    // If there is a giaddr, use it for subnet selection.
    if (selector.giaddr_ != ZERO_ADDRESS()) {
        address = selector.giaddr_;

    // If it is a Renew or Rebind, use the ciaddr.
    } else if ((selector.ciaddr_ != ZERO_ADDRESS()) &&
               (selector.local_address_ != BCAST_ADDRESS())) {
        address = selector.ciaddr_;

    // If ciaddr is not specified, use the source address.
    } else if ((selector.remote_address_ != ZERO_ADDRESS()) &&
               (selector.local_address_ != BCAST_ADDRESS())) {
        address = selector.remote_address_;

    // If local interface name is known, use the local address on this
    // interface.
    } else if (!selector.iface_name_.empty()) {
        Iface* iface = IfaceMgr::instance().getIface(selector.iface_name_);
        // This should never happen in the real life. Hence we throw an
        // exception.
        if (iface == NULL) {
            isc_throw(isc::BadValue, "interface " << selector.iface_name_
                      << " doesn't exist and therefore it is impossible"
                      " to find a suitable subnet for its IPv4 address");
        }
        iface->getAddress4(address);
    }

    // Unable to find a suitable address to use for subnet selection.
    if (address == ZERO_ADDRESS()) {
        return (Subnet4Ptr());
    }

    // We have identified an address in the client's packet that can be
    // used for subnet selection. Match this packet with the subnets. 
    return (get(address, selector.client_classes_));
}

Subnet4Ptr
CfgSubnets4::get(const IOAddress& address,
                 const ClientClasses& client_classes) const {
    for (Subnet4Collection::const_iterator subnet = subnets_.begin();
         subnet != subnets_.end(); ++subnet) {

        // Eliminate those subnets that do not meet client class criteria.
        if (!(*subnet)->clientSupported(client_classes)) {
            continue;
        }

        // Address is in range for the subnet prefix, so return it.
        if ((*subnet)->inRange(address)) {
            return (*subnet);
        }
    }

    // Failed to find a subnet.
    return (Subnet4Ptr());
}

bool
CfgSubnets4::isDuplicate(const Subnet4& subnet) const {
    for (Subnet4Collection::const_iterator subnet_it = subnets_.begin();
         subnet_it != subnets_.end(); ++subnet_it) {
        if ((*subnet_it)->getID() == subnet.getID()) {
            return (true);
        }
    }
    return (false);
}




} // end of namespace isc::dhcp
} // end of namespace isc
