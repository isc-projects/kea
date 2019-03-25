// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SLAAC_CONFIG_H
#define SLAAC_CONFIG_H

#include <process/d_cfg_mgr.h>


namespace isc {
namespace slaac {

class SlaacConfig;
/// @brief Pointer to a configuration context.
typedef boost::shared_ptr<SlaacConfig> SlaacConfigPtr;

/// @brief Control Agent Configuration Context.
///
/// Implement the storage container for configuration context.
/// It provides a single enclosure for the storage of configuration parameters
/// and any other Control Agent specific information that needs to be accessible
/// during configuration parsing as well as to the application as a whole.
/// It is derived from the context base class, ConfigBase.
class SlaacConfig : public process::ConfigBase {
public:

    /// @brief Default constructor
    SlaacConfig();

    /// @brief Creates a clone of this context object.
    ///
    /// Note this method does not do deep copy the information about control sockets.
    /// That data is stored as ConstElementPtr (a shared pointer) to the actual data.
    ///
    /// @return A pointer to the new clone.
    virtual process::ConfigPtr clone() {
        return (process::ConfigPtr(new SlaacConfig(*this)));
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


    void setHopLimit(uint8_t limit) {
        hop_limit_ = limit;
    }

    uint8_t getHopLimit() {
        return (hop_limit_);
    }

    void setManagedFlag(bool managed) {
        managed_flag_ = managed;
    }

    uint8_t getManagedFlag() {
        return (managed_flag_);
    }

    void setRouterLifetime(uint32_t lft) {
        router_lifetime_ = lft;
    }

    uint8_t getRouterLifetime() {
        return (router_lifetime_);
    }

    void setReachableTime(uint32_t lft) {
        reachable_time_ = lft;
    }

    uint8_t getRechableTime() {
        return (reachable_time_);
    }

    void setRetransTime(uint32_t lft) {
        retrans_time_ = lft;
    }

    uint8_t getRetransTime() {
        return (retrans_time_);
    }

private:

    /// @brief Private copy constructor
    ///
    /// It is private to forbid anyone outside of this class to make copies.
    /// The only legal way to copy a context is to call @ref clone().
    ///
    /// @param orig the original context to copy from
    SlaacConfig(const SlaacConfig& orig);

    /// @brief Private assignment operator to avoid potential for slicing.
    ///
    /// @param rhs Context to be assigned.
    SlaacConfig& operator=(const SlaacConfig& rhs);

    /// Socket information will be stored here (for all supported servers)
    std::map<std::string, isc::data::ConstElementPtr> ctrl_sockets_;
    
    uint8_t hop_limit_;

    bool managed_flag_;

    uint32_t router_lifetime_;

    uint32_t reachable_time_;

    uint32_t retrans_time_;
        
    /// @brief Configured hooks libraries.
    isc::hooks::HooksConfig hooks_config_;
};

};
};


#endif
