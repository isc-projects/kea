// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/iface_mgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <string>

using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

const size_t CfgMgr::CONFIG_LIST_SIZE = 10;

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
    spaces4_.insert(make_pair(space->getName(), space));
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
    spaces6_.insert(make_pair(space->getName(), space));
}

Subnet6Ptr
CfgMgr::getSubnet6(const std::string& iface,
                   const isc::dhcp::ClientClasses& classes) {

    if (!iface.length()) {
        return (Subnet6Ptr());
    }

    // If there is more than one, we need to choose the proper one
    for (Subnet6Collection::iterator subnet = subnets6_.begin();
         subnet != subnets6_.end(); ++subnet) {

        // If client is rejected because of not meeting client class criteria...
        if (!(*subnet)->clientSupported(classes)) {
            continue;
        }

        if (iface == (*subnet)->getIface()) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                      DHCPSRV_CFGMGR_SUBNET6_IFACE)
                .arg((*subnet)->toText()).arg(iface);
            return (*subnet);
        }
    }
    return (Subnet6Ptr());
}

Subnet6Ptr
CfgMgr::getSubnet6(const isc::asiolink::IOAddress& hint,
                   const isc::dhcp::ClientClasses& classes,
                   const bool relay) {

    // If there is more than one, we need to choose the proper one
    for (Subnet6Collection::iterator subnet = subnets6_.begin();
         subnet != subnets6_.end(); ++subnet) {

        // If client is rejected because of not meeting client class criteria...
        if (!(*subnet)->clientSupported(classes)) {
            continue;
        }

        // If the hint is a relay address, and there is relay info specified
        // for this subnet and those two match, then use this subnet.
        if (relay && ((*subnet)->getRelayInfo().addr_ == hint) ) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                      DHCPSRV_CFGMGR_SUBNET6_RELAY)
                .arg((*subnet)->toText()).arg(hint.toText());
            return (*subnet);
        }

        if ((*subnet)->inRange(hint)) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_SUBNET6)
                      .arg((*subnet)->toText()).arg(hint.toText());
            return (*subnet);
        }
    }

    // sorry, we don't support that subnet
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_NO_SUBNET6)
              .arg(hint.toText());
    return (Subnet6Ptr());
}

Subnet6Ptr CfgMgr::getSubnet6(OptionPtr iface_id_option,
                              const isc::dhcp::ClientClasses& classes) {
    if (!iface_id_option) {
        return (Subnet6Ptr());
    }

    // Let's iterate over all subnets and for those that have interface-id
    // defined, check if the interface-id is equal to what we are looking for
    for (Subnet6Collection::iterator subnet = subnets6_.begin();
         subnet != subnets6_.end(); ++subnet) {

        // If client is rejected because of not meeting client class criteria...
        if (!(*subnet)->clientSupported(classes)) {
            continue;
        }

        if ( (*subnet)->getInterfaceId() &&
             ((*subnet)->getInterfaceId()->equal(iface_id_option))) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                      DHCPSRV_CFGMGR_SUBNET6_IFACE_ID)
                .arg((*subnet)->toText());
            return (*subnet);
        }
    }
    return (Subnet6Ptr());
}

void CfgMgr::addSubnet6(const Subnet6Ptr& subnet) {
    /// @todo: Check that this new subnet does not cross boundaries of any
    /// other already defined subnet.
    /// @todo: Check that there is no subnet with the same interface-id
    if (isDuplicate(*subnet)) {
        isc_throw(isc::dhcp::DuplicateSubnetID, "ID of the new IPv6 subnet '"
                  << subnet->getID() << "' is already in use");
    }
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_ADD_SUBNET6)
              .arg(subnet->toText());
    subnets6_.push_back(subnet);
}

Subnet4Ptr
CfgMgr::getSubnet4(const isc::asiolink::IOAddress& hint,
                   const isc::dhcp::ClientClasses& classes,
                   bool relay) const {
    // Iterate over existing subnets to find a suitable one for the
    // given address.
    for (Subnet4Collection::const_iterator subnet = subnets4_.begin();
         subnet != subnets4_.end(); ++subnet) {

        // If client is rejected because of not meeting client class criteria...
        if (!(*subnet)->clientSupported(classes)) {
            continue;
        }

        // If the hint is a relay address, and there is relay info specified
        // for this subnet and those two match, then use this subnet.
        if (relay && ((*subnet)->getRelayInfo().addr_ == hint) ) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                      DHCPSRV_CFGMGR_SUBNET4_RELAY)
                .arg((*subnet)->toText()).arg(hint.toText());
            return (*subnet);
        }

        // Let's check if the client belongs to the given subnet
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

Subnet4Ptr
CfgMgr::getSubnet4(const std::string& iface_name,
                   const isc::dhcp::ClientClasses& classes) const {
    Iface* iface = IfaceMgr::instance().getIface(iface_name);
    // This should never happen in the real life. Hence we throw an exception.
    if (iface == NULL) {
        isc_throw(isc::BadValue, "interface " << iface_name <<
                  " doesn't exist and therefore it is impossible"
                  " to find a suitable subnet for its IPv4 address");
    }
    IOAddress addr("0.0.0.0");
    // If IPv4 address assigned to the interface exists, find a suitable
    // subnet for it, else return NULL pointer to indicate that no subnet
    // could be found.
    return (iface->getAddress4(addr) ? getSubnet4(addr, classes) : Subnet4Ptr());
}

void CfgMgr::addSubnet4(const Subnet4Ptr& subnet) {
    /// @todo: Check that this new subnet does not cross boundaries of any
    /// other already defined subnet.
    if (isDuplicate(*subnet)) {
        isc_throw(isc::dhcp::DuplicateSubnetID, "ID of the new IPv4 subnet '"
                  << subnet->getID() << "' is already in use");
    }
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_ADD_SUBNET4)
              .arg(subnet->toText());
    subnets4_.push_back(subnet);
}

void CfgMgr::deleteSubnets4() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_DELETE_SUBNET4);
    subnets4_.clear();
}

void CfgMgr::deleteSubnets6() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_DELETE_SUBNET6);
    subnets6_.clear();
}


std::string CfgMgr::getDataDir() {
    return (datadir_);
}

bool
CfgMgr::isDuplicate(const Subnet4& subnet) const {
    for (Subnet4Collection::const_iterator subnet_it = subnets4_.begin();
         subnet_it != subnets4_.end(); ++subnet_it) {
        if ((*subnet_it)->getID() == subnet.getID()) {
            return (true);
        }
    }
    return (false);
}

bool
CfgMgr::isDuplicate(const Subnet6& subnet) const {
    for (Subnet6Collection::const_iterator subnet_it = subnets6_.begin();
         subnet_it != subnets6_.end(); ++subnet_it) {
        if ((*subnet_it)->getID() == subnet.getID()) {
            return (true);
        }
    }
    return (false);
}


void
CfgMgr::setD2ClientConfig(D2ClientConfigPtr& new_config) {
    d2_client_mgr_.setD2ClientConfig(new_config);
}

bool
CfgMgr::ddnsEnabled() {
    return (d2_client_mgr_.ddnsEnabled());
}

const D2ClientConfigPtr&
CfgMgr::getD2ClientConfig() const {
    return (d2_client_mgr_.getD2ClientConfig());
}

D2ClientMgr&
CfgMgr::getD2ClientMgr() {
    return (d2_client_mgr_);
}

void
CfgMgr::ensureCurrentAllocated() {
    if (!configuration_ || configs_.empty()) {
        configuration_.reset(new SrvConfig());
        configs_.push_back(configuration_);
    }
}

void
CfgMgr::clear() {
    configs_.clear();
    ensureCurrentAllocated();
}

void
CfgMgr::commit() {
    ensureCurrentAllocated();
    if (!configs_.back()->sequenceEquals(*configuration_)) {
        configuration_ = configs_.back();
        // Keep track of the maximum size of the configs history. Before adding
        // new element, we have to remove the oldest one.
        if (configs_.size() > CONFIG_LIST_SIZE) {
            SrvConfigList::iterator it = configs_.begin();
            std::advance(it, configs_.size() - CONFIG_LIST_SIZE);
            configs_.erase(configs_.begin(), it);
        }
    }
}

void
CfgMgr::rollback() {
    ensureCurrentAllocated();
    if (!configuration_->sequenceEquals(*configs_.back())) {
        configs_.pop_back();
    }
}

void
CfgMgr::revert(const size_t index) {
    ensureCurrentAllocated();
    if (index == 0) {
        isc_throw(isc::OutOfRange, "invalid commit index 0 when reverting"
                  " to an old configuration");
    } else if (index > configs_.size() - 1) {
        isc_throw(isc::OutOfRange, "unable to revert to commit index '"
                  << index << "', only '" << configs_.size() - 1
                  << "' previous commits available");
    }

    // Let's rollback an existing configuration to make sure that the last
    // configuration on the list is the current one. Note that all remaining
    // operations in this function should be exception free so there shouldn't
    // be a problem that the revert operation fails and the staging
    // configuration is destroyed by this rollback.
    rollback();

    // Get the iterator to the current configuration and then advance to the
    // desired one.
    SrvConfigList::const_reverse_iterator it = configs_.rbegin();
    std::advance(it, index);

    // Copy the desired configuration to the new staging configuration. The
    // staging configuration is re-created here because we rolled back earlier
    // in this function.
    (*it)->copy(*getStagingCfg());

    // Make the staging configuration a current one.
    commit();
}

ConstSrvConfigPtr
CfgMgr::getCurrentCfg() {
    ensureCurrentAllocated();
    return (configuration_);
}

SrvConfigPtr
CfgMgr::getStagingCfg() {
    ensureCurrentAllocated();
    if (configuration_->sequenceEquals(*configs_.back())) {
        uint32_t sequence = configuration_->getSequence();
        configs_.push_back(SrvConfigPtr(new SrvConfig(++sequence)));
    }
    return (configs_.back());
}

CfgMgr::CfgMgr()
    : datadir_(DHCP_DATA_DIR), echo_v4_client_id_(true),
      d2_client_mgr_(), verbose_mode_(false) {
    // DHCP_DATA_DIR must be set set with -DDHCP_DATA_DIR="..." in Makefile.am
    // Note: the definition of DHCP_DATA_DIR needs to include quotation marks
    // See AM_CPPFLAGS definition in Makefile.am
}

CfgMgr::~CfgMgr() {
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
