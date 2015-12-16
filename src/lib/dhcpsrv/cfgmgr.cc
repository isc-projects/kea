// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/subnet_id.h>
#include <stats/stats_mgr.h>
#include <sstream>
#include <string>

using namespace isc::asiolink;
using namespace isc::util;
using namespace isc::stats;

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


std::string CfgMgr::getDataDir() const {
    return (datadir_);
}

void
CfgMgr::setDataDir(const std::string& datadir) {
    datadir_ = datadir;
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
    if (configuration_) {
        configuration_->removeStatistics();
    }
    configs_.clear();
    ensureCurrentAllocated();
}

void
CfgMgr::commit() {


    ensureCurrentAllocated();

    // First we need to remove statistics. The new configuration can have fewer
    // subnets. Also, it may change subnet-ids. So we need to remove them all
    // and add it back.
    configuration_->removeStatistics();

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

    // Now we need to set the statistics back.
    configuration_->updateStatistics();
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
