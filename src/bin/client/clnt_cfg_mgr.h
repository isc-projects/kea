// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLNT_CFG_MGR_H
#define CLNT_CFG_MGR_H

#include <client/clnt_config.h>
#include <cc/data.h>
#include <hooks/hooks_config.h>
#include <process/d_cfg_mgr.h>
#include <process/base_cfg_mgr.h>
#include <boost/pointer_cast.hpp>

namespace isc {
namespace client {

class ClntCfgMgr : public process::DCfgMgrBase {
public:

    /// @brief Constructor.
    ClntCfgMgr();

    /// @brief Destructor
    virtual ~ClntCfgMgr() { }

    /// @brief Convenience method that returns the Control Agent configuration
    /// context.
    ///
    /// @return returns a pointer to the configuration context.
    ClntConfigPtr getCtrlAgentCfgContext() {
        return (boost::dynamic_pointer_cast<ClntConfig>(getContext()));
    }

    /// @brief Returns configuration summary in the textual format.
    ///
    /// @param selection Bitfield which describes the parts of the configuration
    /// to be returned. This parameter is ignored for the Control Agent.
    ///
    /// @return Summary of the configuration in the textual format.
    virtual std::string getConfigSummary(const uint32_t selection);

protected:

    virtual void ensureCurrentAllocated();

    /// @brief Parses configuration of the Control Agent.
    ///
    /// @param config Pointer to a configuration specified for the agent.
    /// @param check_only Boolean flag indicating if this method should
    /// only verify correctness of the provided conifiguration.
    /// @return Pointer to a result of configuration parsing.
    virtual isc::data::ConstElementPtr
    parse(isc::data::ConstElementPtr config, bool check_only);

    /// @brief This is no longer used.
    ///
    /// @throw NotImplemented
    /// @return nothing, always throws
    virtual isc::dhcp::ParserPtr
    createConfigParser(const std::string&,
                       const isc::data::Element::Position& pos);

    /// @brief Creates a new, blank CtrlAgentCfgContext context.
    ///
    ///
    /// This method is used at the beginning of configuration process to
    /// create a fresh, empty copy of a CtrlAgentCfgContext. This new context
    /// will be populated during the configuration process and will replace the
    /// existing context provided the configuration process completes without
    /// error.
    ///
    /// @return Returns a DCfgContextBasePtr to the new context instance.
    virtual process::DCfgContextBasePtr createNewContext();
};

};
};

#endif
