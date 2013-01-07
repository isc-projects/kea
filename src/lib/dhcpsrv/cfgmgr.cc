// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_address.h>
#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfgmgr.h>

using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

CfgMgr&
CfgMgr::instance() {
    static CfgMgr cfg_mgr;
    return (cfg_mgr);
}

void
CfgMgr::addOptionDef(const OptionDefinitionPtr& def,
                     const std::string& option_space) {
    // @todo we need better validation of the provided option space name here.
    // This will be implemented when #2313 is merged.
    if (option_space.empty()) {
        isc_throw(BadValue, "option space name must not be empty");
    } else if (!def) {
        // Option definition must point to a valid object.
        isc_throw(MalformedOptionDefinition, "option definition must not be NULL");

    } else if (getOptionDef(option_space, def->getCode())) {
        // Option definition must not be overriden.
        isc_throw(DuplicateOptionDefinition, "option definition already added"
                  << " to option space " << option_space);

    } else if ((option_space == "dhcp4" &&
                LibDHCP::isStandardOption(Option::V4, def->getCode())) ||
               (option_space == "dhcp6" &&
                LibDHCP::isStandardOption(Option::V6, def->getCode()))) {
        // We must not override standard (assigned) option. The standard options
        // belong to dhcp4 or dhcp6 option space.
        isc_throw(BadValue, "unable to override definition of option '"
                  << def->getCode() << "' in standard option space '"
                  << option_space << "'.");

    }
    // Actually add the definition to the option space.
    option_def_spaces_[option_space].push_back(def);
}

const OptionDefContainer&
CfgMgr::getOptionDefs(const std::string& option_space) const {
    // @todo Validate the option space once the #2313 is implemented.

    // Get all option definitions for the particular option space.
    const OptionDefsMap::const_iterator& defs =
        option_def_spaces_.find(option_space);
    // If there are no option definitions for the particular option space
    // then return empty container.
    if (defs == option_def_spaces_.end()) {
        static OptionDefContainer empty_container;
        return (empty_container);
    }
    // If option definitions found, return them.
    return (defs->second);
}

OptionDefinitionPtr
CfgMgr::getOptionDef(const std::string& option_space,
                     const uint16_t option_code) const {
    // @todo Validate the option space once the #2313 is implemented.

    // Get a reference to option definitions for a particular option space.
    const OptionDefContainer& defs = getOptionDefs(option_space);
    // If there are no matching option definitions then return the empty pointer.
    if (defs.empty()) {
        return (OptionDefinitionPtr());
    }
    // If there are some option definitions for a particular option space
    // use an option code to get the one we want.
    const OptionDefContainerTypeIndex& idx = defs.get<1>();
    const OptionDefContainerTypeRange& range = idx.equal_range(option_code);
    // If there is no definition that matches option code, return empty pointer.
    if (std::distance(range.first, range.second) == 0) {
        return (OptionDefinitionPtr());
    }
    // If there is more than one definition matching an option code, return
    // the first one. This should not happen because we check for duplicates
    // when addOptionDef is called.
    return (*range.first);
}

Subnet6Ptr
CfgMgr::getSubnet6(const isc::asiolink::IOAddress& hint) {

    // If there's only one subnet configured, let's just use it
    // The idea is to keep small deployments easy. In a small network - one
    // router that also runs DHCPv6 server. Users specifies a single pool and
    // expects it to just work. Without this, the server would complain that it
    // doesn't have IP address on its interfaces that matches that
    // configuration. Such requirement makes sense in IPv4, but not in IPv6.
    // The server does not need to have a global address (using just link-local
    // is ok for DHCPv6 server) from the pool it serves.
    if ((subnets6_.size() == 1) && hint.getAddress().to_v6().is_link_local()) {
        return (subnets6_[0]);
    }

    // If there is more than one, we need to choose the proper one
    for (Subnet6Collection::iterator subnet = subnets6_.begin();
         subnet != subnets6_.end(); ++subnet) {
        if ((*subnet)->inRange(hint)) {
            return (*subnet);
        }
    }

    // sorry, we don't support that subnet
    return (Subnet6Ptr());
}

Subnet6Ptr CfgMgr::getSubnet6(OptionPtr /*interfaceId*/) {
    /// @todo: Implement get subnet6 by interface-id (for relayed traffic)
    isc_throw(NotImplemented, "Relayed DHCPv6 traffic is not supported yet.");
}

void CfgMgr::addSubnet6(const Subnet6Ptr& subnet) {
    /// @todo: Check that this new subnet does not cross boundaries of any
    /// other already defined subnet.
    subnets6_.push_back(subnet);
}

Subnet4Ptr
CfgMgr::getSubnet4(const isc::asiolink::IOAddress& hint) {

    // If there's only one subnet configured, let's just use it
    // The idea is to keep small deployments easy. In a small network - one
    // router that also runs DHCPv6 server. Users specifies a single pool and
    // expects it to just work. Without this, the server would complain that it
    // doesn't have IP address on its interfaces that matches that
    // configuration. Such requirement makes sense in IPv4, but not in IPv6.
    // The server does not need to have a global address (using just link-local
    // is ok for DHCPv6 server) from the pool it serves.
    if (subnets4_.size() == 1) {
        return (subnets4_[0]);
    }

    // If there is more than one, we need to choose the proper one
    for (Subnet4Collection::iterator subnet = subnets4_.begin();
         subnet != subnets4_.end(); ++subnet) {
        if ((*subnet)->inRange(hint)) {
            return (*subnet);
        }
    }

    // sorry, we don't support that subnet
    return (Subnet4Ptr());
}

void CfgMgr::addSubnet4(const Subnet4Ptr& subnet) {
    /// @todo: Check that this new subnet does not cross boundaries of any
    /// other already defined subnet.
    subnets4_.push_back(subnet);
}

void CfgMgr::deleteOptionDefs() {
    option_def_spaces_.clear();
}

void CfgMgr::deleteSubnets4() {
    subnets4_.clear();
}

void CfgMgr::deleteSubnets6() {
    subnets6_.clear();
}

CfgMgr::CfgMgr() {
}

CfgMgr::~CfgMgr() {
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
