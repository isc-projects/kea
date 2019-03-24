// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SLAAC_CFG_MGR_H
#define SLAAC_CFG_MGR_H

#include <cc/data.h>
#include <hooks/hooks_config.h>
#include <process/d_cfg_mgr.h>
#include <slaac/slaac_config.h>
#include <boost/pointer_cast.hpp>
#include <map>
#include <string>

namespace isc {
namespace slaac {

/// @brief Ctrl Agent Configuration Manager.
///
/// Provides the mechanisms for managing the Control Agent application's
/// configuration.
class SlaacCfgMgr : public process::DCfgMgrBase {
public:

    /// @brief Constructor.
    SlaacCfgMgr();

    /// @brief Destructor
    virtual ~SlaacCfgMgr();

    /// @brief Convenience method that returns the Control Agent configuration
    /// context.
    ///
    /// @return returns a pointer to the configuration context.
    SlaacConfigPtr getSlaacConfig() {
        return (boost::dynamic_pointer_cast<SlaacConfig>(getContext()));
    }

    /// @brief Returns configuration summary in the textual format.
    ///
    /// @param selection Bitfield which describes the parts of the configuration
    /// to be returned. This parameter is ignored for the Control Agent.
    ///
    /// @return Summary of the configuration in the textual format.
    virtual std::string getConfigSummary(const uint32_t selection);

protected:

    /// @brief Parses configuration of the Control Agent.
    ///
    /// @param config Pointer to a configuration specified for the agent.
    /// @param check_only Boolean flag indicating if this method should
    /// only verify correctness of the provided configuration.
    /// @return Pointer to a result of configuration parsing.
    virtual isc::data::ConstElementPtr
    parse(isc::data::ConstElementPtr config, bool check_only);

    /// @brief Creates a new, blank SlaacConfig context.
    ///
    ///
    /// This method is used at the beginning of configuration process to
    /// create a fresh, empty copy of a SlaacConfig . This new context
    /// will be populated during the configuration process and will replace the
    /// existing context provided the configuration process completes without
    /// error.
    ///
    /// @return Returns a ConfigPtr to the new context instance.
    virtual process::ConfigPtr createNewContext();
};

/// @brief Defines a shared pointer to SlaacConfigMgr.
typedef boost::shared_ptr<SlaacCfgMgr> SlaacCfgMgrPtr;

} // namespace isc::agent
} // namespace isc

#endif // CTRL_AGENT_CFG_MGR_H
