// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CTRL_AGENT_CFG_MGR_H
#define CTRL_AGENT_CFG_MGR_H

#include <cc/data.h>
#include <hooks/hooks_config.h>
#include <process/d_cfg_mgr.h>
#include <boost/pointer_cast.hpp>
#include <map>
#include <string>

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

    /// @brief Default constructor
    CtrlAgentCfgContext();

    /// @brief Creates a clone of this context object.
    ///
    /// Note this method does not do deep copy the information about control sockets.
    /// That data is stored as ConstElementPtr (a shared pointer) to the actual data.
    ///
    /// @return A pointer to the new clone.
    virtual process::DCfgContextBasePtr clone() {
        return (process::DCfgContextBasePtr(new CtrlAgentCfgContext(*this)));
    }

    /// @brief Returns information about control socket
    ///
    /// This method returns Element tree structure that describes the control
    /// socket (or null pointer if the socket is not defined for a particular
    /// server type). This information is expected to be compatible with
    /// data passed to @ref isc::config::CommandMgr::openCommandSocket.
    ///
    /// @param service server being controlled
    /// @return pointer to the Element that holds control-socket map (or NULL)
    isc::data::ConstElementPtr
    getControlSocketInfo(const std::string& service) const;

    /// @brief Sets information about the control socket
    ///
    /// This method stores Element tree structure that describes the control
    /// socket. This information is expected to be compatible with
    /// data passed to @ref isc::config::CommandMgr::openCommandSocket.
    ///
    /// @param control_socket Element that holds control-socket map
    /// @param service server being controlled
    void setControlSocketInfo(const isc::data::ConstElementPtr& control_socket,
                              const std::string& service);

    /// @brief Returns socket configuration summary in a textual format.
    std::string getControlSocketInfoSummary() const;

    /// @brief Sets http-host parameter
    ///
    /// @param host Hostname or IP address where the agent's HTTP service
    /// will be available.
    void setHttpHost(const std::string& host) {
        http_host_ = host;
    }

    /// @brief Returns http-host parameter
    ///
    /// @return Hostname or IP address where the agent's HTTP service is
    /// available.
    std::string getHttpHost() const {
        return (http_host_);
    }

    /// @brief Sets http port
    ///
    /// @param port sets the TCP port the HTTP server will listen on
    void setHttpPort(const uint16_t port) {
        http_port_ = port;
    }

    /// @brief Returns the TCP post the HTTP server will listen on
    uint16_t getHttpPort() const {
        return (http_port_);
    }

    /// @brief Returns non-const reference to configured hooks libraries.
    ///
    /// @return non-const reference to configured hooks libraries.
    isc::hooks::HooksConfig& getHooksConfig() {
        return (hooks_config_);
    }

    /// @brief Returns const reference to configured hooks libraries.
    ///
    /// @return const reference to configured hooks libraries.
    const isc::hooks::HooksConfig& getHooksConfig() const {
        return (hooks_config_);
    }

    /// @brief Unparse a configuration object
    ///
    /// Returns an element which must parse into the same object, i.e.
    /// @code
    /// for all valid config C parse(parse(C)->toElement()) == parse(C)
    /// @endcode
    ///
    /// @return a pointer to a configuration which can be parsed into
    /// the initial configuration object
    virtual isc::data::ElementPtr toElement() const;

private:

    /// @brief Private copy constructor
    ///
    /// It is private to forbid anyone outside of this class to make copies.
    /// The only legal way to copy a context is to call @ref clone().
    ///
    /// @param orig the original context to copy from
    CtrlAgentCfgContext(const CtrlAgentCfgContext& orig);

    /// @brief Private assignment operator to avoid potential for slicing.
    ///
    /// @param rhs Context to be assigned.
    CtrlAgentCfgContext& operator=(const CtrlAgentCfgContext& rhs);

    /// Socket information will be stored here (for all supported servers)
    std::map<std::string, isc::data::ConstElementPtr> ctrl_sockets_;

    /// Hostname the CA should listen on.
    std::string http_host_;

    /// TCP port the CA should listen on.
    uint16_t http_port_;

    /// @brief Configured hooks libraries.
    isc::hooks::HooksConfig hooks_config_;
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

    /// @brief Parses configuration of the Control Agent.
    ///
    /// @param config Pointer to a configuration specified for the agent.
    /// @param check_only Boolean flag indicating if this method should
    /// only verify correctness of the provided configuration.
    /// @return Pointer to a result of configuration parsing.
    virtual isc::data::ConstElementPtr
    parse(isc::data::ConstElementPtr config, bool check_only);

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
