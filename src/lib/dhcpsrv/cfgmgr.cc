// Copyright (C) 2012-2025 Internet Systems Consortium, Inc. ("ISC")
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
#include <sstream>
#include <string>

using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

CfgMgr::CfgMgr()
    : datadir_(DHCP_DATA_DIR, true), d2_client_mgr_(new D2ClientMgr()),
      configuration_(new SrvConfig()), family_(AF_INET) {
}

CfgMgr&
CfgMgr::instance() {
    static CfgMgr cfg_mgr;
    return (cfg_mgr);
}

Optional<std::string>
CfgMgr::getDataDir() const {
    return (datadir_);
}

void
CfgMgr::setDataDir(const std::string& datadir, bool unspecified) {
    datadir_ = Optional<std::string>(datadir, unspecified);
}

void
CfgMgr::setD2ClientConfig(D2ClientConfigPtr& new_config) {
    // Note that D2ClientMgr::setD2Config() actually attempts to apply the
    // configuration by stopping its sender and opening a new one and so
    // forth per the new configuration.
    d2_client_mgr_->setD2ClientConfig(new_config);

    // Manager will throw if the set fails, if it succeeds
    // we'll update our SrvConfig, configuration_, with the D2ClientConfig
    // used. This is largely bookkeeping in case we ever want to compare
    // configuration_ to another SrvConfig.
    configuration_->setD2ClientConfig(new_config);
}

bool
CfgMgr::ddnsEnabled() {
    return (d2_client_mgr_->ddnsEnabled());
}

const D2ClientConfigPtr&
CfgMgr::getD2ClientConfig() const {
    return (d2_client_mgr_->getD2ClientConfig());
}

D2ClientMgr&
CfgMgr::getD2ClientMgr() {
    return (*d2_client_mgr_);
}

void
CfgMgr::clear() {
    if (staging_configuration_) {
        staging_configuration_.reset();
    }
    if (configuration_) {
        configuration_->removeStatistics();
        configuration_.reset(new SrvConfig());
    }
    external_configs_.clear();
    D2ClientConfigPtr d2_default_conf(new D2ClientConfig());
    setD2ClientConfig(d2_default_conf);
}

void
CfgMgr::clearStagingConfiguration() {
    staging_configuration_.reset();
}

void
CfgMgr::commit() {
    // First we need to remove statistics. The new configuration can have fewer
    // subnets. Also, it may change subnet-ids. So we need to remove them all
    // and add them back.
    configuration_->removeStatistics();

    if (staging_configuration_ && !configuration_->sequenceEquals(*staging_configuration_)) {
        // Promote the staging configuration to the current configuration.
        configuration_ = staging_configuration_;
        staging_configuration_.reset();
    }

    // Set the last commit timestamp.
    auto now = boost::posix_time::second_clock::universal_time();
    configuration_->setLastCommitTime(now);

    // Now we need to set the statistics back.
    configuration_->updateStatistics();

    configuration_->configureLowerLevelLibraries();
}

SrvConfigPtr
CfgMgr::getCurrentCfg() {
    return (configuration_);
}

SrvConfigPtr
CfgMgr::getStagingCfg() {
    if (!staging_configuration_ || configuration_->sequenceEquals(*staging_configuration_)) {
        uint32_t sequence = configuration_->getSequence();
        staging_configuration_ = SrvConfigPtr(new SrvConfig(++sequence));
    }
    return (staging_configuration_);
}

SrvConfigPtr
CfgMgr::createExternalCfg() {
    uint32_t seq = 0;

    if (!external_configs_.empty()) {
        seq = external_configs_.rbegin()->second->getSequence() + 1;
    }

    SrvConfigPtr srv_config(new SrvConfig(seq));
    external_configs_[seq] = srv_config;
    return (srv_config);
}

void
CfgMgr::mergeIntoStagingCfg(const uint32_t seq) {
    mergeIntoCfg(getStagingCfg(), seq);
}

void
CfgMgr::mergeIntoCurrentCfg(const uint32_t seq) {
    try {
        // First we need to remove statistics.
        getCurrentCfg()->removeStatistics();
        mergeIntoCfg(getCurrentCfg(), seq);
        LibDHCP::setRuntimeOptionDefs(getCurrentCfg()->getCfgOptionDef()->getContainer());

    } catch (...) {
        // Make sure the statistics is updated even if the merge failed.
        getCurrentCfg()->updateStatistics();
        throw;
    }
    getCurrentCfg()->updateStatistics();
}

void
CfgMgr::mergeIntoCfg(const SrvConfigPtr& target_config, const uint32_t seq) {
    auto source_config = external_configs_.find(seq);
    if (source_config != external_configs_.end()) {
        target_config->merge(*source_config->second);
        external_configs_.erase(source_config);

    } else {
        isc_throw(BadValue, "the external configuration with the sequence number "
                  "of " << seq << " was not found");
    }
}

} // end of isc::dhcp namespace
} // end of isc namespace
