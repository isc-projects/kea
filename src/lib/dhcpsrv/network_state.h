// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NETWORK_STATE_H
#define NETWORK_STATE_H

#include <cc/data.h>
#include <dhcpsrv/subnet_id.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <set>
#include <mutex>
#include <string>

namespace isc {
namespace dhcp {

class NetworkStateImpl;

/// @brief Holds information about DHCP service enabling status.
///
/// When the DHCP server receives a command to disable DHCP service entirely
/// or for specific networks, this has to be recorded to allow for re-enabling
/// DHCP service for these networks as a result of receiving a command from
/// the administrator or when the timeout for re-enabling the service occurs.
/// Currently there are two types of command originating either from user or
/// HA internal mechanism.
/// The global state can also be altered by the DB recovery mechanism which
/// disables the service on connection loss and re-enables it after the
/// connection is restored. Because the server supports recovery for multiple
/// connections, this is implemented using an internal counter.
/// Combining all the origins of the alteration of the network state, the
/// behavior is:
/// a) the network state is disabled if any of the originators explicitly set
///    the disabled flag.
/// b) the network state is restored only if all originators explicitly clear
///    the disabled flag.
/// In the future, it will be possible to specify "disabled" parameter for
/// a subnet (or network) in the configuration file to indicate that this subnet
/// should be excluded from the service. When a command is subsequently sent to
/// temporarily disable a service for some other subnets for a specified amount
/// of time, only these subnets should be re-enabled when the time elapses. This
/// class fulfills this requirement by recording the subnets disabled with a command
/// and re-enabling them when required. The subnets specified as "disabled" in
/// the configuration file should remain disabled until explicitly enabled with a
/// control command.
///
/// This class also allows for disabling the DHCP service globally. In this case
/// the server drops all received packets.
///
/// The "dhcp-disable" and "dhcp-enable" commands are used for globally disabling
/// and enabling the DHCP service. The "dhcp-disable-scopes" and "dhcp-enable-scopes"
/// commands are used to disable and enable DHCP service for subnets and networks.
/// In case of the "dhcp-disable" and "dhcp-disable-scopes" commands, it is possible
/// to specify "max-period" parameter which provides a timeout, after which the
/// settings are reverted (service is re-enabled globally and/or for specific
/// scopes).
///
/// Disabling DHCP service with a timeout is useful to guard against issues when
/// the controlling client dies after disabling the DHCP service on the server,
/// e.g. failover peers may instruct each other to disable the DHCP service while
/// database synchronization takes place. If the peer subsequently dies, the
/// surviving server must re-enable DHCP on its own.
///
/// @todo This class currently supports only the case of globally disabling
/// the DHCP service. Disabling per network/subnet will be added later.
class NetworkState {
public:

    /// @brief DHCP server type.
    enum ServerType {
        DHCPv4,
        DHCPv6
    };

    /// @brief Origin of the network state transition.
    ///
    /// The enumeration indicates the originator of the state transition of the
    /// network state: either user command, HA internal command or DB connection
    /// recovery mechanism.
    enum class Origin {
        /// @brief The network state is being altered by a user command.
        USER_COMMAND,
        /// @brief The network state is being altered by a HA internal command.
        HA_COMMAND,
        /// @brief The network state is being altered by the DB connection
        /// recovery mechanics.
        DB_CONNECTION
    };

    /// @brief Type of the container holding collection of subnet identifiers.
    typedef std::set<SubnetID> Subnets;

    /// @brief Type of the container holding collection of shared network names.
    typedef std::set<std::string> Networks;

    /// @brief Constructor.
    NetworkState(const ServerType& server_type);

    /// @brief Disable the DHCP service state for respective transition origin.
    ///
    /// @note If any of the user commands, HA internal commands or connection
    /// recovery processes disable the dhcp service, the service will remain
    /// disabled until all flags are cleared.
    ///
    /// @param origin The origin of the state transition.
    void disableService(const NetworkState::Origin& origin);

    /// @brief Enable the DHCP service state for respective transition origin.
    ///
    /// @note If any of the user commands, HA internal commands or connection
    /// recovery processes disable the dhcp service, the service will remain
    /// disabled until all flags are cleared.
    ///
    /// @param origin The origin of the state transition.
    void enableService(const NetworkState::Origin& origin);

    /// @brief Reset internal counters.
    ///
    /// Reset internal counters for a specific 'origin' after the server has
    /// been reconfigured or all the connections have been restored.
    ///
    /// @param type The origin for which the state flags need to be reset.
    void reset(const NetworkState::Origin& type);

    /// @brief Enables DHCP service globally and for scopes which have been
    /// disabled as a result of control command.
    ///
    /// @param origin The origin of the state transition.
    void enableAll(const NetworkState::Origin& origin);

    /// @brief Schedules enabling DHCP service in the future.
    ///
    /// @param seconds Number of seconds after which the service should be enabled
    /// unless @c enableAll is enabled before that time.
    /// @param origin The origin of the state transition.
    void delayedEnableAll(const unsigned int seconds,
                          const NetworkState::Origin& origin);

    /// @brief Checks if the DHCP service is globally enabled.
    ///
    /// @return true if the service is globally enabled, false otherwise.
    bool isServiceEnabled() const;

    /// @brief Checks if delayed enabling of DHCP services is scheduled.
    ///
    /// It indicates that the timer is present which counts the time until
    /// @c enableAll function will be called automatically.
    ///
    /// @return true if delayed enabling of the DHCP service is scheduled,
    /// false otherwise.
    bool isDelayedEnableAll() const;

    /// @name Selective disabling/enabling DHCP service per scopes
    //@{

    /// @brief Disable DHCP service for selected subnets.
    ///
    /// @param subnets Collection of subnet identifiers for which the service
    /// should be disabled.
    ///
    /// @throw isc::NotImplemented
    void selectiveDisable(const NetworkState::Subnets& subnets);

    /// @brief Disable DHCP service for selected networks.
    ///
    /// @param networks Collection of shared network names for which the service
    /// should be disabled.
    ///
    /// @throw isc::NotImplemented
    void selectiveDisable(const NetworkState::Networks& networks);

    /// @brief Enable DHCP service for selected subnets.
    ///
    /// @param subnets Collection of subnet identifiers for which the service
    /// should be disabled.
    ///
    /// @throw isc::NotImplemented
    void selectiveEnable(const NetworkState::Subnets& subnets);

    /// @brief Enable DHCP service for selected networks.
    ///
    /// @param networks Collection of shared network names for which the service
    /// should be enabled.
    ///
    /// @throw isc::NotImplemented
    void selectiveEnable(const NetworkState::Networks& networks);

    //@}

private:

    /// @brief Pointer to the @c NetworkState implementation.
    boost::shared_ptr<NetworkStateImpl> impl_;

    /// @brief The mutex used to protect internal state.
    const boost::scoped_ptr<std::mutex> mutex_;
};

/// @brief Pointer to the @c NetworkState object.
typedef boost::shared_ptr<NetworkState> NetworkStatePtr;

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // NETWORK_STATE_H
