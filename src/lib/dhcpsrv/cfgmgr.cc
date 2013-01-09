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
#include <dhcpsrv/dhcpsrv_log.h>

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
CfgMgr::addOptionSpace4(const OptionSpacePtr& space) {
    if (!space) {
        isc_throw(InvalidOptionSpace,
                  "provided option space object is NULL.");
    }
    OptionSpaceCollection::iterator it = spaces4_.find(space->getName());
    if (it != spaces4_.end()) {
        isc_throw(InvalidOptionSpace, "option space " << space->getName()
                  << " already added.");
    }
    spaces4_.insert(std::pair<std::string,
                              OptionSpacePtr>(space->getName(), space));
}

void
CfgMgr::addOptionSpace6(const OptionSpacePtr& space) {
    if (!space) {
        isc_throw(InvalidOptionSpace,
                  "provided option space object is NULL.");
    }
    OptionSpaceCollection::iterator it = spaces6_.find(space->getName());
    if (it != spaces6_.end()) {
        isc_throw(InvalidOptionSpace, "option space " << space->getName()
                  << " already added.");
    }
    spaces6_.insert(std::pair<std::string,
                              OptionSpacePtr>(space->getName(), space));
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
    // Get existing option definitions for the option space.
    OptionDefContainerPtr defs = getOptionDefs(option_space);
    // getOptionDefs always returns a valid pointer to
    // the container. Let's make an assert to make sure.
    assert(defs);
    // Actually add the new definition.
    defs->push_back(def);
    option_def_spaces_[option_space] = defs;
}

OptionDefContainerPtr
CfgMgr::getOptionDefs(const std::string& option_space) const {
    // @todo Validate the option space once the #2313 is implemented.

    // Get all option definitions for the particular option space.
    const OptionDefsMap::const_iterator& defs =
        option_def_spaces_.find(option_space);
    // If there are no option definitions for the particular option space
    // then return empty container.
    if (defs == option_def_spaces_.end()) {
        return (OptionDefContainerPtr(new OptionDefContainer()));
    }
    // If option definitions found, return them.
    return (defs->second);
}

OptionDefinitionPtr
CfgMgr::getOptionDef(const std::string& option_space,
                     const uint16_t option_code) const {
    // @todo Validate the option space once the #2313 is implemented.

    // Get a reference to option definitions for a particular option space.
    OptionDefContainerPtr defs = getOptionDefs(option_space);
    // If there are no matching option definitions then return the empty pointer.
    if (!defs || defs->empty()) {
        return (OptionDefinitionPtr());
    }
    // If there are some option definitions for a particular option space
    // use an option code to get the one we want.
    const OptionDefContainerTypeIndex& idx = defs->get<1>();
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
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                  DHCPSRV_CFGMGR_ONLY_SUBNET6)
                  .arg(subnets6_[0]->toText()).arg(hint.toText());
        return (subnets6_[0]);
    }

    // If there is more than one, we need to choose the proper one
    for (Subnet6Collection::iterator subnet = subnets6_.begin();
         subnet != subnets6_.end(); ++subnet) {
        if ((*subnet)->inRange(hint)) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                      DHCPSRV_CFGMGR_SUBNET6)
                      .arg((*subnet)->toText()).arg(hint.toText());
            return (*subnet);
        }
    }

    // sorry, we don't support that subnet
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_NO_SUBNET6)
              .arg(hint.toText());
    return (Subnet6Ptr());
}

Subnet6Ptr CfgMgr::getSubnet6(OptionPtr /*interfaceId*/) {
    /// @todo: Implement get subnet6 by interface-id (for relayed traffic)
    isc_throw(NotImplemented, "Relayed DHCPv6 traffic is not supported yet.");
}

void CfgMgr::addSubnet6(const Subnet6Ptr& subnet) {
    /// @todo: Check that this new subnet does not cross boundaries of any
    /// other already defined subnet.
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_ADD_SUBNET6)
              .arg(subnet->toText());
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
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                  DHCPSRV_CFGMGR_ONLY_SUBNET4)
                  .arg(subnets4_[0]->toText()).arg(hint.toText());
        return (subnets4_[0]);
    }

    // If there is more than one, we need to choose the proper one
    for (Subnet4Collection::iterator subnet = subnets4_.begin();
         subnet != subnets4_.end(); ++subnet) {
        if ((*subnet)->inRange(hint)) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                      DHCPSRV_CFGMGR_SUBNET4)
                      .arg((*subnet)->toText()).arg(hint.toText());
            return (*subnet);
        }
    }

    // sorry, we don't support that subnet
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_NO_SUBNET4)
              .arg(hint.toText());
    return (Subnet4Ptr());
}

void CfgMgr::addSubnet4(const Subnet4Ptr& subnet) {
    /// @todo: Check that this new subnet does not cross boundaries of any
    /// other already defined subnet.
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_ADD_SUBNET4)
              .arg(subnet->toText());
    subnets4_.push_back(subnet);
}

void CfgMgr::deleteOptionDefs() {
    option_def_spaces_.clear();
}

void CfgMgr::deleteSubnets4() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_DELETE_SUBNET4);
    subnets4_.clear();
}

void CfgMgr::deleteSubnets6() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_DELETE_SUBNET6);
    subnets6_.clear();
}

CfgMgr::CfgMgr() {
}

CfgMgr::~CfgMgr() {
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
