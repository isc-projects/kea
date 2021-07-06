// Copyright (C) 2014-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D2_CFG_MGR_H
#define D2_CFG_MGR_H

#include <asiolink/io_service.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <d2srv/d2_config.h>
#include <hooks/hooks_config.h>
#include <process/d_cfg_mgr.h>

#include <stdint.h>
#include <string>

namespace isc {
namespace d2 {

class D2CfgContext;
/// @brief Pointer to a configuration context.
typedef boost::shared_ptr<D2CfgContext> D2CfgContextPtr;

/// @brief  DHCP-DDNS Configuration Context
///
/// Implements the storage container for configuration context.
/// It provides a single enclosure for the storage of configuration parameters
/// and any other DHCP-DDNS specific information that needs to be accessible
/// during configuration parsing as well as to the application as a whole.
/// It is derived from the context base class, ConfigBase.
class D2CfgContext : public process::ConfigBase {
public:
    /// @brief Constructor
    D2CfgContext();

    /// @brief Destructor
    virtual ~D2CfgContext();

    /// @brief Creates a clone of this context object.
    ///
    /// @return returns a pointer to the new clone.
    virtual process::ConfigPtr clone() {
        return (process::ConfigPtr(new D2CfgContext(*this)));
    }

    /// @brief Fetches a reference to the D2Params
    D2ParamsPtr& getD2Params() {
        return (d2_params_);
    }

    /// @brief Fetches the forward DNS domain list manager.
    ///
    /// @return returns a pointer to the forward manager.
    DdnsDomainListMgrPtr getForwardMgr() {
        return (forward_mgr_);
    }

    /// @brief Sets the forward domain list manager
    /// @param forward_mgr pointer to the new forward manager
    void setForwardMgr(DdnsDomainListMgrPtr forward_mgr) {
        forward_mgr_ = forward_mgr;
    }

    /// @brief Fetches the reverse DNS domain list manager.
    ///
    /// @return returns a pointer to the reverse manager.
    DdnsDomainListMgrPtr getReverseMgr() {
        return (reverse_mgr_);
    }

    /// @brief Sets the reverse domain list manager
    /// @param reverse_mgr pointer to the new reverse manager
    void setReverseMgr(DdnsDomainListMgrPtr reverse_mgr) {
        reverse_mgr_ = reverse_mgr;
    }

    /// @brief Fetches the map of TSIG keys.
    ///
    /// @return returns a pointer to the key map.
    TSIGKeyInfoMapPtr getKeys() {
        return (keys_);
    }

    /// @brief Sets the map of TSIG keys
    ///
    /// @param keys pointer to the new TSIG key map
    void setKeys(const TSIGKeyInfoMapPtr& keys) {
        keys_ = keys;
    }

    /// @brief Returns information about control socket
    /// @return pointer to the Element that holds control-socket map
    const isc::data::ConstElementPtr getControlSocketInfo() const {
        return (control_socket_);
    }

    /// @brief Sets information about the control socket
    /// @param control_socket Element that holds control-socket map
    void setControlSocketInfo(const isc::data::ConstElementPtr& control_socket) {
        control_socket_ = control_socket;
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
    /// @return a pointer to a configuration
    virtual isc::data::ElementPtr toElement() const;

protected:
    /// @brief Copy constructor for use by derivations in clone().
    D2CfgContext(const D2CfgContext& rhs);

private:
    /// @brief Private assignment operator to avoid potential for slicing.
    D2CfgContext& operator=(const D2CfgContext& rhs);

    /// @brief Global level parameter storage
    D2ParamsPtr d2_params_;

    /// @brief Forward domain list manager.
    DdnsDomainListMgrPtr forward_mgr_;

    /// @brief Reverse domain list manager.
    DdnsDomainListMgrPtr reverse_mgr_;

    /// @brief Storage for the map of TSIGKeyInfos.
    TSIGKeyInfoMapPtr keys_;

    /// @brief Pointer to the control-socket information.
    isc::data::ConstElementPtr control_socket_;

    /// @brief Configured hooks libraries.
    isc::hooks::HooksConfig hooks_config_;
};

/// @brief Defines a pointer for DdnsDomain instances.
typedef boost::shared_ptr<DdnsDomainListMgr> DdnsDomainListMgrPtr;

/// @brief DHCP-DDNS Configuration Manager
///
/// Provides the mechanisms for managing the DHCP-DDNS application's
/// configuration.  This includes services for parsing sets of configuration
/// values, storing the parsed information in its converted form,
/// and retrieving the information on demand.
class D2CfgMgr : public process::DCfgMgrBase {
public:
    /// @brief Reverse zone suffix added to IPv4 addresses for reverse lookups
    /// @todo This should be configurable.
    static const char* IPV4_REV_ZONE_SUFFIX;

    /// @brief Reverse zone suffix added to IPv6 addresses for reverse lookups
    /// @todo This should be configurable.
    static const char* IPV6_REV_ZONE_SUFFIX;

    /// @brief Constructor
    D2CfgMgr();

    /// @brief Destructor
    virtual ~D2CfgMgr();

    /// @brief Convenience method that returns the D2 configuration context.
    ///
    /// @return returns a pointer to the configuration context.
    D2CfgContextPtr getD2CfgContext() {
        return (boost::dynamic_pointer_cast<D2CfgContext>(getContext()));
    }

    /// @brief Returns whether or not forward updates are enabled.
    ///
    /// This method currently uses the presence or absence of Forward DDNS
    /// Domains to determine if forward updates are enabled or disabled.
    /// @todo This could be expanded to include the check of a configurable
    /// boolean value.
    ///
    /// @return true if forward updates are enabled, false otherwise.
    bool forwardUpdatesEnabled();

    /// @brief Returns whether or not reverse updates are enabled.
    ///
    /// This method currently uses the presence or absence of Reverse DDNS
    /// Domains to determine if reverse updates are enabled or disabled.
    /// @todo This could be expanded to include the check of a configurable
    /// boolean value.
    ///
    /// @return true if reverse updates are enabled, false otherwise.
    bool reverseUpdatesEnabled();

    /// @brief Matches a given FQDN to a forward domain.
    ///
    /// This calls the matchDomain method of the forward domain manager to
    /// match the given FQDN to a forward domain.
    ///
    /// @param fqdn is the name for which to look.
    /// @param domain receives the matching domain. Note that it will be reset
    /// upon entry and only set if a match is subsequently found.
    ///
    /// @return returns true if a match is found, false otherwise.
    /// @throw throws D2CfgError if given an invalid fqdn.
    bool matchForward(const std::string& fqdn, DdnsDomainPtr& domain);

    /// @brief Matches a given IP address to a reverse domain.
    ///
    /// This calls the matchDomain method of the reverse domain manager to
    /// match the given IPv4 or IPv6 address to a reverse domain.
    ///
    /// @param ip_address is the name for which to look.
    /// @param domain receives the matching domain. Note that it will be reset
    /// upon entry and only set if a match is subsequently found.
    ///
    /// @return returns true if a match is found, false otherwise.
    /// @throw throws D2CfgError if given an invalid fqdn.
    bool matchReverse(const std::string& ip_address, DdnsDomainPtr& domain);

    /// @brief Generate a reverse order string for the given IP address
    ///
    /// This method creates a string containing the given IP address
    /// contents in reverse order.  This format is used for matching
    /// against reverse DDNS domains in DHCP_DDNS configuration.
    /// After reversing the syllables of the address, it appends the
    /// appropriate suffix.
    ///
    /// @param address string containing a valid IPv4 or IPv6 address.
    ///
    /// @return a std::string containing the reverse order address.
    ///
    /// @throw D2CfgError if given an invalid address.
    static std::string reverseIpAddress(const std::string& address);

    /// @brief Generate a reverse order string for the given IP address
    ///
    /// This method creates a string containing the given IP address
    /// contents in reverse order.  This format is used for matching
    /// against reverse DDNS domains in DHCP_DDNS configuration.
    /// After reversing the syllables of the address, it appends the
    /// appropriate suffix.
    ///
    /// Example:
    ///   input:  192.168.1.15
    ///  output:  15.1.168.192.in-addr.arpa.
    ///
    /// @param ioaddr is the IPv4 IOaddress to convert
    ///
    /// @return a std::string containing the reverse order address.
    ///
    /// @throw D2CfgError if not given an IPv4  address.
    static std::string reverseV4Address(const isc::asiolink::IOAddress& ioaddr);

    /// @brief Generate a reverse order string for the given IP address
    ///
    /// This method creates a string containing the given IPv6 address
    /// contents in reverse order.  This format is used for matching
    /// against reverse DDNS domains in DHCP_DDNS configuration.
    /// After reversing the syllables of the address, it appends the
    /// appropriate suffix.
    ///
    /// IPv6 example:
    /// input:  2001:db8:302:99::
    /// output:
    ///0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.9.9.0.0.2.0.3.0.8.B.D.0.1.0.0.2.ip6.arpa.
    ///
    /// @param ioaddr string containing a valid IPv6 address.
    ///
    /// @return a std::string containing the reverse order address.
    ///
    /// @throw D2CfgError if not given an IPv6 address.
    static std::string reverseV6Address(const isc::asiolink::IOAddress& ioaddr);

    /// @brief Convenience method fetches the D2Params from context
    /// @return reference to const D2ParamsPtr
    const D2ParamsPtr& getD2Params();

    /// @brief Convenience method fetches information about control socket
    /// from context
    /// @return pointer to the Element that holds control-socket map
    const isc::data::ConstElementPtr getControlSocketInfo();

    /// @brief Returns configuration summary in the textual format.
    ///
    /// @param selection Bitfield which describes the parts of the configuration
    /// to be returned. This parameter is ignored for the D2.
    ///
    /// @return Summary of the configuration in the textual format.
    virtual std::string getConfigSummary(const uint32_t selection) override;

    std::list<std::list<std::string>> jsonPathsToRedact() const final override;

protected:
    /// @brief Parses configuration of the D2.
    ///
    /// @param config Pointer to a configuration specified for D2.
    /// @param check_only Boolean flag indicating if this method should
    /// only verify correctness of the provided configuration.
    /// @return Pointer to a result of configuration parsing.
    virtual isc::data::ConstElementPtr
    parse(isc::data::ConstElementPtr config, bool check_only) override;

    /// @brief Adds default values to the given config
    ///
    /// Adds the D2 default values to the configuration Element map. This
    /// method is invoked by @c DCfgMgrBase::parseConfig().
    ///
    /// @param mutable_config - configuration to which defaults should be added
    virtual void setCfgDefaults(isc::data::ElementPtr mutable_config) override;

    /// @brief Creates an new, blank D2CfgContext context
    ///
    /// This method is used at the beginning of configuration process to
    /// create a fresh, empty copy of a D2CfgContext. This new context will
    /// be populated during the configuration process and will replace the
    /// existing context provided the configuration process completes without
    /// error.
    ///
    /// @return Returns a ConfigPtr to the new context instance.
    virtual process::ConfigPtr createNewContext() override;
};

/// @brief Defines a shared pointer to D2CfgMgr.
typedef boost::shared_ptr<D2CfgMgr> D2CfgMgrPtr;

} // end of isc::d2 namespace
} // end of isc namespace

#endif // D2_CFG_MGR_H
