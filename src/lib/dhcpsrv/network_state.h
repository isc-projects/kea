// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
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

/// @brief Controls the DHCP service enabling status.
///
/// Sometimes, a DHCP server must pause responding to the DHCP queries.
/// Typical cases include a database connection loss when the server tries
/// to reconnect and various cases related to the High Availability operation.
/// It is also possible to explicitly turn the DHCP service on and off via the
/// control channel. This class receives calls from different origins to
/// disable and re-enable the DHCP service.
///
/// The general rule is that the DHCP service must be disabled when the class
/// receives at least one request to disable the service from any origin. The
/// service must be re-enabled when all requestors previously disabling the
/// service re-enabled it. This class also allows for specifying a timeout value
/// for each request, after which the service gets re-enabled automatically. It
/// is particularly useful in HA when there is no guarantee that the HA partner
/// will be able to re-enable the service because it may experience an unexpected
/// outage. In that case, the "max-period" parameter must accompany the "dhcp-disable"
/// command to ensure that the service will eventually be re-enabled.

/// The HA hook library may include several independent relationships. Each
/// relationship is treated as a separate origin by this class. If one relationship
/// disables the DHCP service, the service must remain disabled even when any other
/// relationship requests enabling it. The service is re-enabled after all
/// relationships requested re-enabling it (e.g., they all finished synchronizing
/// the lease database).
///
/// The HA service instances must have unique identifiers they use to specify the
/// origin. For example, an @c HAService with the identifier of 1 should request
/// disabling the local service like this:
///
/// @code
///     NetworkState state;
///     state.disableService(NetworkState::HA_LOCAL_COMMAND + 1);
/// @endcode
///
/// The DHCP state can also be altered by the database recovery mechanism, which
/// disables the service on connection loss and re-enables it after the connection
/// is restored. Unlike in HA, this is implemented using an internal counter. In
/// this case, there is one origin for all database connections. The requests for
/// the @c NetworkState::DB_CONNECTION are counted, and the DHCP service is
/// re-enabled when the counter reaches 0.
///
/// @todo We should consider migrating the database recovery to the same mechanism
///  we use for the HA. The reference counting works because the database connection
/// classes ensure that for each request to disable the DHCP service, there is a
/// corresponding request to enable the service. It prevents the situation that the
/// service remains disabled because there were more requests to disable than to
/// enable the service. It is hard to ensure the same consistency for the HA.
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

    /// @brief The network state is being altered by a user command.
    ///
    /// Specify unique origins for different commands by adding a number to this
    /// constant.
    static const unsigned int USER_COMMAND = 1;

    /// @brief The network state is being altered by an HA internal command.
    ///
    /// Specify HA service-specific origins by adding a unique local service
    /// identifier to this constant.
    static const unsigned int HA_LOCAL_COMMAND = 1000;

    /// @brief The network state is being altered by a "dhcp-disable" or "dhcp-enable"
    /// command sent by a HA partner.
    ///
    /// Specify HA service-specific origins by adding a unique remote service
    /// identifier to this constant.
    static const unsigned int HA_REMOTE_COMMAND = 2000;

    /// @brief The network state is being altered by the DB connection
    /// recovery mechanics.
    static const unsigned int DB_CONNECTION = 3000;

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
    void disableService(unsigned int origin);

    /// @brief Enable the DHCP service state for respective transition origin.
    ///
    /// @note If any of the user commands, HA internal commands or connection
    /// recovery processes disable the dhcp service, the service will remain
    /// disabled until all flags are cleared.
    ///
    /// @param origin The origin of the state transition.
    void enableService(unsigned int origin);

    /// @brief Reset internal counters.
    ///
    /// Reset internal counters for a specific 'origin' after the server has
    /// been reconfigured or all the connections have been restored.
    ///
    /// @param type The origin for which the state flags need to be reset.
    void reset(unsigned int type);

    /// @brief Enables DHCP service globally and for scopes which have been
    /// disabled as a result of control command.
    ///
    /// @param origin The origin of the state transition.
    void enableAll(unsigned int origin);

    /// @brief Schedules enabling DHCP service in the future.
    ///
    /// @param seconds Number of seconds after which the service should be enabled
    /// unless @c enableAll is enabled before that time.
    /// @param origin The origin of the state transition.
    void delayedEnableAll(const unsigned int seconds,
                          unsigned int origin);

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
