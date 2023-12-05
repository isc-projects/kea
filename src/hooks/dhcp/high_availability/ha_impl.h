// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HA_IMPL_H
#define HA_IMPL_H

#include <ha_config.h>
#include <ha_service.h>
#include <asiolink/io_service.h>
#include <cc/data.h>
#include <dhcpsrv/network_state.h>
#include <hooks/hooks.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>


namespace isc {
namespace ha {

/// @brief High Availability hooks library implementation.
///
/// This object provides an interface between the HA hook library callouts
/// and the HA state model implemented in the @c HAService. Callouts invoke
/// respective methods of the @c HAImpl to configure the service, generate
/// lease updates etc. The @c HAImpl retrieves and validates the arguments
/// provided within @c CalloutHandle object and then invokes appropriate
/// methods of the @c HAService class.
class HAImpl : public boost::noncopyable {
public:

    /// @brief Constructor.
    HAImpl();

    /// @brief Parses configuration.
    ///
    /// @param input_config Configuration specified for the hooks library.
    /// @throw ConfigError when configuration fails.
    void configure(const data::ConstElementPtr& input_config);

    /// @brief Creates high availability services using current configuration.
    ///
    /// The caller must ensure that the HA configuration is valid before
    /// calling this function.
    ///
    /// @param io_service IO service object provided by the DHCP server.
    /// @param network_state pointer to the object holding a state of the
    /// DHCP service (enabled/disabled).
    /// @param server_type DHCP server type for which the HA service should
    /// be created.
    void startServices(const asiolink::IOServicePtr& io_service,
                       const dhcp::NetworkStatePtr& network_state,
                       const HAServerType& server_type);

    /// @brief Destructor.
    ~HAImpl();

    /// @brief Returns a configuration for the first relationship.
    ///
    /// This function is held here for historical reasons and it is currently
    /// only used in the unit tests for a single-relationship test cases. The
    /// production code should use the other variant of this function that
    /// includes a partner name as a parameter. It coveres both the cases when
    /// there is only one relationship and the hub-and-spoke case.
    ///
    /// @return Configuration for the relationship to which the partner belongs.
    /// @throw InvalidOperation when there are no relationships.
    HAConfigPtr getConfig() const {
        return (config_->get());
    }

    /// @brief Returns parsed configuration by partner name.
    ///
    /// @param partner_name name of a partner belonging to the relationship for
    /// which the configuration should be retrieved.
    /// @return Configuration for the relationship to which the partner belongs.
    HAConfigPtr getConfig(const std::string& partner_name) const {
        return (config_->get(partner_name));
    }

    /// @brief Implementation of the "buffer4_receive" callout.
    ///
    /// This callout uses HA service to check if the query should be processed
    /// by this server or a partner. If the partner should process the query,
    /// this callout sets the status to @c CalloutHandle::NEXT_STEP_DROP to
    /// cause the server to drop the packet. Therefore it is important to note
    /// that, if multiple hook libraries implementing @c buffer4_receive hook are
    /// loaded, the order of loading the libraries may matter. If this library
    /// sets the status to @c CalloutHandle::NEXT_STEP_DROP and the other library
    /// overrides this status, the query will be processed by the server instead
    /// of being dropped. This problem may be mitigated by loading the HA library
    /// last, i.e. placing the library at the end of the "hooks-libraries"
    /// list within a Kea configuration file.
    ///
    /// If the received query is to be processed by this server instance, the
    /// @c CalloutHabndle::NEXT_STEP_SKIP status is set to prevent the server
    /// from unpacking the query because the query is unpacked by the callout.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void buffer4Receive(hooks::CalloutHandle& callout_handle);

    /// @brief Implementation of the "subnet4_select" callout.
    void subnet4Select(hooks::CalloutHandle& callout_handle);

    /// @brief Implementation of the "leases4_committed" callout.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void leases4Committed(hooks::CalloutHandle& callout_handle);

    /// @brief Implementation of the "lease4_server_decline" callout.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void lease4ServerDecline(hooks::CalloutHandle& callout_handle);

    /// @brief Implementation of the "buffer6_receive" callout.
    ///
    /// This callout uses HA service to check if the query should be processed
    /// by this server or a partner. If the partner should process the query,
    /// this callout sets the status to @c CalloutHandle::NEXT_STEP_DROP to
    /// cause the server to drop the packet. Therefore it is important to note
    /// that, if multiple hook libraries implementing @c buffer6_receive hook are
    /// loaded, the order of loading the libraries may matter. If this library
    /// sets the status to @c CalloutHandle::NEXT_STEP_DROP and the other library
    /// overrides this status, the query will be processed by the server instead
    /// of being dropped. This problem may be mitigated by loading the HA library
    /// last, i.e. placing the library at the end of the "hooks-libraries"
    /// list within a Kea configuration file.
    ///
    /// If the received query is to be processed by this server instance, the
    /// @c CalloutHabndle::NEXT_STEP_SKIP status is set to prevent the server
    /// from unpacking the query because the query is unpacked by the callout.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void buffer6Receive(hooks::CalloutHandle& callout_handle);


    /// @brief Implementation of the "subnet6_select" callout.
    void subnet6Select(hooks::CalloutHandle& callout_handle);

    /// @brief Implementation of the "leases6_committed" callout.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void leases6Committed(hooks::CalloutHandle& callout_handle);

    /// @brief Implementation of the "command_processed" callout.
    ///
    /// It adds the HA servers information to "status-get" command responses by
    /// calling @c HAService::commandProcessed.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void commandProcessed(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handle for the heartbeat command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void heartbeatHandler(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for the ha-sync command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void synchronizeHandler(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for the ha-scopes command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void scopesHandler(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for the ha-continue command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void continueHandler(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for the ha-maintenance-notify command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void maintenanceNotifyHandler(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for the ha-maintenance-start command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void maintenanceStartHandler(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for the ha-maintenance-cancel command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void maintenanceCancelHandler(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for the ha-reset command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void haResetHandler(hooks::CalloutHandle& callout_handle);

    /// @brief Implements handler for the ha-sync-complete-notify command.
    ///
    /// @param callout_handle Callout handle provided to the callout.
    void syncCompleteNotifyHandler(hooks::CalloutHandle& callout_handle);

    /// @brief Attempts to get an @c HAService by server name.
    ///
    /// The function expects that the arguments contain the "server-name"
    /// parameter. If the parameter is not specified, a default @c HAService
    /// name is returned.
    ///
    /// @param command_name command name (used for logging purposes only).
    /// @param args command arguments or null.
    /// @return Pointer to an @c HAService instance.
    /// @throw BadValue if the specified server-name doesn't exist or if the
    /// server-name wasn't specified and more than one @c HAService exists.
    HAServicePtr getHAServiceByServerName(const std::string& command_name,
                                          data::ConstElementPtr args) const;

protected:

    /// @brief Holds parsed configuration.
    HAConfigMapperPtr config_;

    /// @brief Pointer to the high availability services (state machines).
    HAServiceMapperPtr services_;

};

/// @brief Pointer to the High Availability hooks library implementation.
typedef boost::shared_ptr<HAImpl> HAImplPtr;

} // end of namespace isc::ha
} // end of namespace isc

#endif
