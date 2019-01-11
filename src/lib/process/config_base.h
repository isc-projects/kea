// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CONFIG_BASE_H
#define CONFIG_BASE_H

#include <cc/cfg_to_element.h>
#include <cc/user_context.h>
#include <process/config_ctl_info.h>
#include <process/logging_info.h>

namespace isc {
namespace process {

/// @brief Base class for all configurations
///
/// This is a common base class that represents configurations.
/// SrvConfig, D2CfgContext, CtrlAgentCfgContext and possibly other
/// classes holding configurations are derived from this.
///
/// It should contain only those elements that are applicable to really
/// every daemon we may have. Before adding anything here, please consider
/// whether it would be usable by all of the following: DHCP servers,
/// DDNS update daemon, Control Agent, Netconf daemon, DHCP relay,
/// DHCP client.
///
/// This class currently holds information about common server configuration.
class ConfigBase : public isc::data::UserContext, public isc::data::CfgToElement {
public:
    /// @name Modifiers and accesors for the configuration objects.
    ///
    /// @warning References to the objects returned by accessors are only
    /// valid during the lifetime of the @c SrvConfig object which
    /// returned them.
    ///
    //@{
    /// @brief Returns logging specific configuration.
    const process::LoggingInfoStorage& getLoggingInfo() const {
        return (logging_info_);
    }

    /// @brief Sets logging specific configuration.
    ///
    /// @param logging_info New logging configuration.
    void addLoggingInfo(const process::LoggingInfo& logging_info) {
        logging_info_.push_back(logging_info);
    }

    /// @brief Apply logging configuration to log4cplus.
    void applyLoggingCfg() const;

    /// @brief Compares two configuration.
    ///
    /// @param other the other configuration to compare to
    bool equals(const ConfigBase& other) const;

    /// @brief Converts to Element representation
    ///
    /// This creates a Map element with the following content (expressed
    /// as JSON):
    /// {{{
    /// {
    ///     "Logging": {
    ///         :
    ///     }
    /// }
    /// }}}
    ///
    /// Note that it will not contain the configuration control information
    /// (i.e. "config-control"), as this is not a top-level element, rather
    /// it belongs within the configured process element.
    ///
    /// @return Element representation.
    virtual isc::data::ElementPtr toElement() const;

    /// @brief Fetches a read-only copy of the configuration control
    /// information
    /// @return pointer to the const ConfigControlInfo
    process::ConstConfigControlInfoPtr getConfigControlInfo() const {
        return (config_ctl_info_);
    }

    /// @brief Set the configuration control information
    ///
    /// Updates the internal pointer to the configuration control
    /// information with the given pointer value.  If the given pointer
    /// is empty, the internal pointer will be reset.
    ///
    /// @param config_ctl_info pointer to the configuration value
    /// to store.
    void setConfigControlInfo(const process::ConfigControlInfoPtr&
                              config_ctl_info) {
        config_ctl_info_ = config_ctl_info;
    }

protected:
    /// @brief Copies the current configuration to a new configuration.
    ///
    /// This method copies only the parameters defined in this class.
    /// Since derived classes are expected to provide their own
    /// copy methods, this one is protected and can be used only
    /// by descendant classes.
    ///
    /// @param new_config this configuration will be copied to new_config
    void copy(ConfigBase& new_config) const;

private:
    /// @brief Logging specific information.
    process::LoggingInfoStorage logging_info_;

    /// @brief Configuration control information.
    process::ConfigControlInfoPtr config_ctl_info_;
};

/// @brief Non-const pointer to the @c SrvConfig.
typedef boost::shared_ptr<ConfigBase> ConfigPtr;

};
};

#endif /* CONFIG_BASE_H */
