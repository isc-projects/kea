// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DHCPSRV_CONFIG_H
#define DHCPSRV_CONFIG_H

#include <dhcpsrv/cfg_hosts.h>
#include <dhcpsrv/cfg_iface.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfg_option_def.h>
#include <dhcpsrv/cfg_rsoo.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/cfg_mac_source.h>
#include <dhcpsrv/logging_info.h>
#include <cc/data.h>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <stdint.h>

namespace isc {
namespace dhcp {

class CfgMgr;


/// @brief Specifies current DHCP configuration
///
/// @todo Migrate all other configuration parameters from cfgmgr.h here
class SrvConfig {
public:
    /// @name Constants for selection of parameters returned by @c getConfigSummary
    ///
    //@{
    /// Nothing selected
    static const uint32_t CFGSEL_NONE    = 0x00000000;
    /// Number of IPv4 subnets
    static const uint32_t CFGSEL_SUBNET4 = 0x00000001;
    /// Number of IPv6 subnets
    static const uint32_t CFGSEL_SUBNET6 = 0x00000002;
    /// Number of enabled ifaces
    static const uint32_t CFGSEL_IFACE4  = 0x00000004;
    /// Number of v6 ifaces
    static const uint32_t CFGSEL_IFACE6  = 0x00000008;
    /// DDNS enabled/disabled
    static const uint32_t CFGSEL_DDNS    = 0x00000010;
    /// Number of all subnets
    static const uint32_t CFGSEL_SUBNET  = 0x00000003;
    /// IPv4 related config
    static const uint32_t CFGSEL_ALL4    = 0x00000015;
    /// IPv6 related config
    static const uint32_t CFGSEL_ALL6    = 0x0000001A;
    /// Whole config
    static const uint32_t CFGSEL_ALL     = 0xFFFFFFFF;
    //@}

    /// @brief Default constructor.
    ///
    /// This constructor sets configuration sequence number to 0.
    SrvConfig();

    /// @brief Constructor.
    ///
    /// Sets arbitrary configuration sequence number.
    SrvConfig(const uint32_t sequence);

    /// @brief Returns summary of the configuration in the textual format.
    ///
    /// This method returns the brief text describing the current configuration.
    /// It may be used for logging purposes, e.g. when the new configuration is
    /// committed to notify a user about the changes in configuration.
    ///
    /// @todo Currently this method uses @c CfgMgr accessors to get the
    /// configuration parameters. Once these parameters are migrated from the
    /// @c CfgMgr this method will have to be modified accordingly.
    ///
    /// @todo Implement reporting a summary of interfaces being used for
    /// receiving and sending DHCP messages. This will be implemented with
    /// ticket #3512.
    ///
    /// @param selection Is a bitfield which describes the parts of the
    /// configuration to be returned.
    ///
    /// @return Summary of the configuration in the textual format.
    std::string getConfigSummary(const uint32_t selection) const;

    /// @brief Returns configuration sequence number.
    uint32_t getSequence() const {
        return (sequence_);
    }

    /// @brief Compares configuration sequence with other sequence.
    ///
    /// This method compares sequence numbers of two configurations for
    /// equality. The sequence numbers are meant to be unique, so if
    /// they are equal it means that they point to the same configuration.
    ///
    /// @param other Configuration which sequence number should be
    /// compared with the sequence number of this configuration.
    ///
    /// @return true if sequence numbers are equal.
    bool sequenceEquals(const SrvConfig& other);

    /// @name Modifiers and accesors for the configuration objects.
    ///
    /// @warning References to the objects returned by accessors are only
    /// valid during the lifetime of the @c SrvConfig object which
    /// returned them.
    ///
    //@{
    /// @brief Returns logging specific configuration.
    const LoggingInfoStorage& getLoggingInfo() const {
        return (logging_info_);
    }

    /// @brief Sets logging specific configuration.
    ///
    /// @param logging_info New logging configuration.
    void addLoggingInfo(const LoggingInfo& logging_info) {
        logging_info_.push_back(logging_info);
    }

    /// @brief Returns non-const pointer to interface configuration.
    ///
    /// This function returns a non-const pointer to the interface
    /// configuration.
    ///
    /// @return Object representing configuration of interfaces.
    CfgIfacePtr getCfgIface() {
        return (cfg_iface_);
    }

    /// @brief Returns const pointer to interface configuration.
    ///
    /// This function returns a const pointer to the interface
    /// configuration.
    ///
    /// @return Object representing configuration of interfaces.
    ConstCfgIfacePtr getCfgIface() const {
        return (cfg_iface_);
    }

    /// @brief Return pointer to non-const object representing user-defined
    /// option definitions.
    ///
    /// This function returns a pointer to the object which represents the
    /// user defined option definitions grouped by option space name.
    ///
    /// @return Pointer to an object holding option definitions.
    CfgOptionDefPtr getCfgOptionDef() {
        return (cfg_option_def_);
    }

    /// @brief Returns pointer to the const object representing user-defined
    /// option definitions.
    ///
    /// This function returns a pointer to the object which represents the
    /// user defined option definitions grouped by option space name.
    ///
    /// @return Pointer to an object holding option definitions.
    ConstCfgOptionDefPtr getCfgOptionDef() const {
        return (cfg_option_def_);
    }

    /// @brief Returns pointer to the non-const object holding options.
    ///
    /// This method returns a pointer to the object which holds instances
    /// of the options to be returned to the clients belonging to any subnet.
    ///
    /// @return Pointer to the object holding options.
    CfgOptionPtr getCfgOption() {
        return (cfg_option_);
    }

    /// @brief Returns pointer to the const object holding options.
    ///
    /// This method returns a pointer to the object which holds instances
    /// of the options to be returned to the clients belonging to any subnet.
    ///
    /// @return Pointer to the object holding options.
    const ConstCfgOptionPtr getCfgOption() const {
        return (cfg_option_);
    }

    /// @brief Returns pointer to non-const object holding subnets configuration
    /// for DHCPv4.
    ///
    /// @return Pointer to the object holding subnets configuration for DHCPv4.
    CfgSubnets4Ptr getCfgSubnets4() {
        return (cfg_subnets4_);
    }

    /// @brief Returns pointer to const object holding subnets configuration for
    /// DHCPv4.
    ///
    /// @return Pointer to the object holding subnets configuration for DHCPv4.
    ConstCfgSubnets4Ptr getCfgSubnets4() const {
        return (cfg_subnets4_);
    }

    /// @brief Returns pointer to non-const object holding subnets configuration
    /// for DHCPv6.
    ///
    /// @return Pointer to the object holding subnets configuration for DHCPv6.
    CfgSubnets6Ptr getCfgSubnets6() {
        return (cfg_subnets6_);
    }

    /// @brief Returns pointer to const object holding subnets configuration for
    /// DHCPv6.
    ///
    /// @return Pointer to the object holding subnets configuration for DHCPv6.
    ConstCfgSubnets6Ptr getCfgSubnets6() const {
        return (cfg_subnets6_);
    }

    /// @brief Returns pointer to the non-const objects representing host
    /// reservations for different IPv4 and IPv6 subnets.
    ///
    /// @return Pointer to the non-const object holding host reservations.
    CfgHostsPtr getCfgHosts() {
        return (cfg_hosts_);
    }

    /// @brief Returns pointer to the const objects representing host
    /// reservations for different IPv4 and IPv6 subnets.
    ///
    /// @return Pointer to the const object holding host reservations.
    ConstCfgHostsPtr getCfgHosts() const {
        return (cfg_hosts_);
    }

    /// @brief Returns pointer to the non-const object representing
    /// set of RSOO-enabled options.
    ///
    /// @return Pointer to the non-const object holding RSOO-enabled
    /// options.
    CfgRSOOPtr getCfgRSOO() {
        return (cfg_rsoo_);
    }

    /// @brief Returns pointer to the const object representing set
    /// of RSOO-enabled options.
    ///
    /// @return Pointer to the const object holding RSOO-enabled
    /// options.
    ConstCfgRSOOPtr getCfgRSOO() const {
        return (cfg_rsoo_);
    }

    //@}

    /// @brief Returns non-const reference to an array that stores
    ///        MAC/hardware address sources.
    ///
    /// @return non-const reference to MAC/hardware address sources
    CfgMACSource& getMACSources() {
        return (cfg_mac_source_);
    }

    /// @brief Returns const reference to an array that stores
    ///        MAC/hardware address sources.
    ///
    /// @return const reference to MAC/hardware address sources
    const CfgMACSource& getMACSources() const {
        return (cfg_mac_source_);
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

    /// @brief Copies the currnet configuration to a new configuration.
    ///
    /// This method copies the parameters stored in the configuration to
    /// an object passed as parameter. The configuration sequence is not
    /// copied.
    ///
    /// @warning Some of the configuration objects are not copied at
    /// this point, e.g. subnets. This is because they contain quite complex
    /// data structures and they make use of pointers, so in many cases
    /// the default copy constructors can't be used. Implementing this
    /// requires quite a lot of time so this is left as is for now.
    /// The lack of ability to copy the entire configuration makes
    /// revert function of the @c CfgMgr unsuable.
    ///
    /// @param [out] new_config An object to which the configuration will
    /// be copied.
    void copy(SrvConfig& new_config) const;

    /// @brief Apply logging configuration to log4cplus.
    void applyLoggingCfg() const;

    /// @name Methods and operators used to compare configurations.
    ///
    //@{
    ///
    /// @brief Compares two objects for equality.
    ///
    /// It ignores the configuration sequence number when checking for
    /// equality of objects.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if two objects are equal, false otherwise.
    bool equals(const SrvConfig& other) const;

    /// @brief Compares two objects for inequality.
    ///
    /// It ignores the configuration sequence number when checking for
    /// inequality of objects.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if two objects are not equal, false otherwise.
    bool nequals(const SrvConfig& other) const {
        return (!equals(other));
    }

    /// @brief Equality operator.
    ///
    /// It ignores the configuration sequence number when checking for
    /// equality of objects.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if two objects are equal, false otherwise.
    bool operator==(const SrvConfig& other) const {
        return (equals(other));
    }

    /// @param other An object to be compared with this object.
    ///
    /// It ignores the configuration sequence number when checking for
    /// inequality of objects.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if two objects are not equal, false otherwise.
    bool operator!=(const SrvConfig& other) const {
        return (nequals(other));
    }

    //@}

    /// @brief Updates statistics.
    ///
    /// This method calls appropriate methods in child objects that update
    /// related statistics. See @ref CfgSubnets4::updateStatistics and
    /// @ref CfgSubnets6::updateStatistics for details.
    void updateStatistics();

    /// @brief Removes statistics.
    ///
    /// This method calls appropriate methods in child objects that remove
    /// related statistics. See @ref CfgSubnets4::removeStatistics and
    /// @ref CfgSubnets6::removeStatistics for details.
    void removeStatistics();

    /// @brief Sets decline probation-period
    ///
    /// Probation-period is the timer, expressed, in seconds, that specifies how
    /// long a lease is unavailable after reported as declined.
    ///
    /// @param decline_timer number of seconds after declined lease is restored
    void setDeclinePeriod(const uint32_t decline_timer) {
        decline_timer_ = decline_timer;
    }

    /// @brief Returns probation-period
    ///
    /// See @ref setDeclinePeriod for brief discussion.
    /// @return value of probation-period, expressed in seconds
    uint32_t getDeclinePeriod() const {
        return (decline_timer_);
    }

private:

    /// @brief Sequence number identifying the configuration.
    uint32_t sequence_;

    /// @brief Logging specific information.
    LoggingInfoStorage logging_info_;

    /// @brief Interface configuration.
    ///
    /// Used to select interfaces on which the DHCP server will listen to
    /// queries.
    CfgIfacePtr cfg_iface_;

    /// @brief Pointer to option definitions configuration.
    ///
    /// This object holds the user-defined option definitions grouped
    /// by option space name.
    CfgOptionDefPtr cfg_option_def_;

    /// @brief Pointer to options (data) configuration.
    ///
    /// This object holds the instances of the options to be sent to clients
    /// connected to any subnet.
    CfgOptionPtr cfg_option_;

    /// @brief Pointer to subnets configuration for IPv4.
    CfgSubnets4Ptr cfg_subnets4_;

    /// @brief Pointer to subnets configuration for IPv6.
    CfgSubnets6Ptr cfg_subnets6_;

    /// @brief Pointer to the configuration for hosts reservation.
    ///
    /// This object holds a list of @c Host objects representing host
    /// reservations for different IPv4 and IPv6 subnets.
    CfgHostsPtr cfg_hosts_;

    /// @brief A list of configured MAC sources.
    CfgMACSource cfg_mac_source_;

    /// @brief Pointer to the configuration for RSOO-enabled options.
    ///
    /// This object holds a set of RSOO-enabled options. See
    /// RFC 6422 for the definition of the RSOO-enabled option.
    CfgRSOOPtr cfg_rsoo_;

    /// @brief Pointer to the control-socket information
    isc::data::ConstElementPtr control_socket_;

    /// @brief Decline Period time
    ///
    /// This timer specifies decline probation period, the time after a declined
    /// lease is recovered back to available state. Expressed in seconds.
    uint32_t decline_timer_;
};

/// @name Pointers to the @c SrvConfig object.
///
//@{
/// @brief Non-const pointer to the @c SrvConfig.
typedef boost::shared_ptr<SrvConfig> SrvConfigPtr;

/// @brief Const pointer to the @c SrvConfig.
typedef boost::shared_ptr<const SrvConfig> ConstSrvConfigPtr;
//@}

} // namespace isc::dhcp
} // namespace isc

#endif // DHCPSRV_CONFIG_H
