// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CTRL_AGENT_CFG_MGR_H
#define CTRL_AGENT_CFG_MGR_H

#include <process/d_cfg_mgr.h>
#include <boost/pointer_cast.hpp>

namespace isc {
namespace agent {

class CtrlAgentCfgContext;
/// @brief Pointer to a configuration context.
typedef boost::shared_ptr<CtrlAgentCfgContext> CtrlAgentCfgContextPtr;

/// @brief Control Agent Configuration Context.
///
/// Implement the storage container for configuration context.
/// It provides a single enclosure for the storage of configuration parameters
/// and any other Control Agent specific information that needs to be accessible
/// during configuration parsing as well as to the application as a whole.
/// It is derived from the context base class, DCfgContextBase.
class CtrlAgentCfgContext : public process::DCfgContextBase {
public:
    /// @brief Creates a clone of this context object.
    ///
    /// @return A pointer to the new clone.
    virtual process::DCfgContextBasePtr clone() {
        return (process::DCfgContextBasePtr(new CtrlAgentCfgContext(*this)));
    }

private:
    /// @brief Private assignment operator to avoid potential for slicing.
    CtrlAgentCfgContext& operator=(const CtrlAgentCfgContext& rhs);
};

/// @brief Ctrl Agent Configuration Manager.
///
/// Provides the mechanisms for managing the Control Agent application's
/// configuration.
class CtrlAgentCfgMgr : public process::DCfgMgrBase {
public:

    /// @brief Constructor.
    CtrlAgentCfgMgr();

    /// @brief Destructor
    virtual ~CtrlAgentCfgMgr();

    /// @brief Convenience method that returns the Control Agent configuration
    /// context.
    ///
    /// @return returns a pointer to the configuration context.
    CtrlAgentCfgContextPtr getCtrlAgentCfgContext() {
        return (boost::dynamic_pointer_cast<CtrlAgentCfgContext>(getContext()));
    }

    /// @brief Returns configuration summary in the textual format.
    ///
    /// @param selection Bitfield which describes the parts of the configuration
    /// to be returned. This parameter is ignored for the Control Agent.
    ///
    /// @return Summary of the configuration in the textual format.
    virtual std::string getConfigSummary(const uint32_t selection);

protected:

    /// @brief  Create a parser instance based on an element id.
    ///
    /// Given an element_id returns an instance of the appropriate parser.
    ///
    /// @param element_id is the string name of the element as it will appear
    /// in the configuration set.
    /// @param pos position within the configuration text (or file) of element
    /// to be parsed.  This is passed for error messaging.
    ///
    /// @return returns a ParserPtr to the parser instance.
    virtual isc::dhcp::ParserPtr
    createConfigParser(const std::string& element_id,
                       const isc::data::Element::Position& pos
                       = isc::data::Element::ZERO_POSITION());

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

/// @brief Defines a shared pointer to CtrlAgentCfgMgr.
typedef boost::shared_ptr<CtrlAgentCfgMgr> CtrlAgentCfgMgrPtr;

} // namespace isc::agent
} // namespace isc

#endif // CTRL_AGENT_CFG_MGR_H
