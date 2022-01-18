// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <command_creator.h>
#include <ha_log.h>
#include <ha_service.h>
#include <ha_service_states.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <config/timeouts.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <exceptions/exceptions.h>
#include <http/date_time.h>
#include <http/response_json.h>
#include <http/post_request_json.h>
#include <util/multi_threading_mgr.h>
#include <util/stopwatch.h>
#include <boost/pointer_cast.hpp>
#include <boost/make_shared.hpp>
#include <boost/weak_ptr.hpp>
#include <functional>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::http;
using namespace isc::log;
using namespace isc::util;
namespace ph = std::placeholders;

namespace {

/// @brief Exception thrown when command sent to the partner is unsupported.
class CommandUnsupportedError : public CtrlChannelError {
public:
    CommandUnsupportedError(const char* file, size_t line, const char* what) :
        CtrlChannelError(file, line, what) {}
};

}

namespace isc {
namespace ha {

const int HAService::HA_HEARTBEAT_COMPLETE_EVT;
const int HAService::HA_LEASE_UPDATES_COMPLETE_EVT;
const int HAService::HA_SYNCING_FAILED_EVT;
const int HAService::HA_SYNCING_SUCCEEDED_EVT;
const int HAService::HA_MAINTENANCE_NOTIFY_EVT;
const int HAService::HA_MAINTENANCE_START_EVT;
const int HAService::HA_MAINTENANCE_CANCEL_EVT;
const int HAService::HA_CONTROL_RESULT_MAINTENANCE_NOT_ALLOWED;
const int HAService::HA_SYNCED_PARTNER_UNAVAILABLE_EVT;

HAService::HAService(const IOServicePtr& io_service, const NetworkStatePtr& network_state,
                     const HAConfigPtr& config, const HAServerType& server_type)
    : io_service_(io_service), network_state_(network_state), config_(config),
      server_type_(server_type), client_(), listener_(), communication_state_(),
      query_filter_(config), mutex_(), pending_requests_(),
      lease_update_backlog_(config->getDelayedUpdatesLimit()),
      sync_complete_notified_(false) {

    if (server_type == HAServerType::DHCPv4) {
        communication_state_.reset(new CommunicationState4(io_service_, config));

    } else {
        communication_state_.reset(new CommunicationState6(io_service_, config));
    }

    network_state_->reset(NetworkState::Origin::HA_COMMAND);

    startModel(HA_WAITING_ST);

    // Create the client and(or) listener as appropriate.
    if (!config_->getEnableMultiThreading()) {
        // Not configured for multi-threading, start a client in ST mode.
        client_.reset(new HttpClient(*io_service_, 0));
    } else {
        // Create an MT-mode client.
        client_.reset(new HttpClient(*io_service_,
                      config_->getHttpClientThreads(), true));

        // If we're configured to use our own listener create and start it.
        if (config_->getHttpDedicatedListener()) {
            // Get the server address and port from this server's URL.
            auto my_url = config_->getThisServerConfig()->getUrl();
            IOAddress server_address(IOAddress::IPV4_ZERO_ADDRESS());
            try {
                // Since we do not currently support hostname resolution,
                // we need to make sure we have an IP address here.
                server_address = IOAddress(my_url.getStrippedHostname());
            } catch (const std::exception& ex) {
                isc_throw(Unexpected, "server Url:" << my_url.getStrippedHostname()
                          << " is not a valid IP address");
            }

            // Fetch how many threads the listener will use.
            uint32_t listener_threads = config_->getHttpListenerThreads();

            // Instantiate the listener.
            listener_.reset(new CmdHttpListener(server_address, my_url.getPort(),
                                                listener_threads));
        }
    }

    LOG_INFO(ha_logger, HA_SERVICE_STARTED)
        .arg(HAConfig::HAModeToString(config->getHAMode()))
        .arg(HAConfig::PeerConfig::roleToString(config->getThisServerConfig()->getRole()));
}

HAService::~HAService() {
    // Stop client and/or listener.
    stopClientAndListener();

    network_state_->reset(NetworkState::Origin::HA_COMMAND);
}

void
HAService::defineEvents() {
    StateModel::defineEvents();

    defineEvent(HA_HEARTBEAT_COMPLETE_EVT, "HA_HEARTBEAT_COMPLETE_EVT");
    defineEvent(HA_LEASE_UPDATES_COMPLETE_EVT, "HA_LEASE_UPDATES_COMPLETE_EVT");
    defineEvent(HA_SYNCING_FAILED_EVT, "HA_SYNCING_FAILED_EVT");
    defineEvent(HA_SYNCING_SUCCEEDED_EVT, "HA_SYNCING_SUCCEEDED_EVT");
    defineEvent(HA_MAINTENANCE_NOTIFY_EVT, "HA_MAINTENANCE_NOTIFY_EVT");
    defineEvent(HA_MAINTENANCE_START_EVT, "HA_MAINTENANCE_START_EVT");
    defineEvent(HA_MAINTENANCE_CANCEL_EVT, "HA_MAINTENANCE_CANCEL_EVT");
    defineEvent(HA_SYNCED_PARTNER_UNAVAILABLE_EVT, "HA_SYNCED_PARTNER_UNAVAILABLE_EVT");
}

void
HAService::verifyEvents() {
    StateModel::verifyEvents();

    getEvent(HA_HEARTBEAT_COMPLETE_EVT);
    getEvent(HA_LEASE_UPDATES_COMPLETE_EVT);
    getEvent(HA_SYNCING_FAILED_EVT);
    getEvent(HA_SYNCING_SUCCEEDED_EVT);
    getEvent(HA_MAINTENANCE_NOTIFY_EVT);
    getEvent(HA_MAINTENANCE_START_EVT);
    getEvent(HA_MAINTENANCE_CANCEL_EVT);
    getEvent(HA_SYNCED_PARTNER_UNAVAILABLE_EVT);
}

void
HAService::defineStates() {
    StateModel::defineStates();

    defineState(HA_BACKUP_ST, stateToString(HA_BACKUP_ST),
                std::bind(&HAService::backupStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_BACKUP_ST)->getPausing());

    defineState(HA_COMMUNICATION_RECOVERY_ST, stateToString(HA_COMMUNICATION_RECOVERY_ST),
                std::bind(&HAService::communicationRecoveryHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_COMMUNICATION_RECOVERY_ST)->getPausing());

    defineState(HA_HOT_STANDBY_ST, stateToString(HA_HOT_STANDBY_ST),
                std::bind(&HAService::normalStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_HOT_STANDBY_ST)->getPausing());

    defineState(HA_LOAD_BALANCING_ST, stateToString(HA_LOAD_BALANCING_ST),
                std::bind(&HAService::normalStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_LOAD_BALANCING_ST)->getPausing());

    defineState(HA_IN_MAINTENANCE_ST, stateToString(HA_IN_MAINTENANCE_ST),
                std::bind(&HAService::inMaintenanceStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_IN_MAINTENANCE_ST)->getPausing());

    defineState(HA_PARTNER_DOWN_ST, stateToString(HA_PARTNER_DOWN_ST),
                std::bind(&HAService::partnerDownStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_PARTNER_DOWN_ST)->getPausing());

    defineState(HA_PARTNER_IN_MAINTENANCE_ST, stateToString(HA_PARTNER_IN_MAINTENANCE_ST),
                std::bind(&HAService::partnerInMaintenanceStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_PARTNER_IN_MAINTENANCE_ST)->getPausing());

    defineState(HA_PASSIVE_BACKUP_ST, stateToString(HA_PASSIVE_BACKUP_ST),
                std::bind(&HAService::passiveBackupStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_PASSIVE_BACKUP_ST)->getPausing());

    defineState(HA_READY_ST, stateToString(HA_READY_ST),
                std::bind(&HAService::readyStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_READY_ST)->getPausing());

    defineState(HA_SYNCING_ST, stateToString(HA_SYNCING_ST),
                std::bind(&HAService::syncingStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_SYNCING_ST)->getPausing());

    defineState(HA_TERMINATED_ST, stateToString(HA_TERMINATED_ST),
                std::bind(&HAService::terminatedStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_TERMINATED_ST)->getPausing());

    defineState(HA_WAITING_ST, stateToString(HA_WAITING_ST),
                std::bind(&HAService::waitingStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_WAITING_ST)->getPausing());
}

void
HAService::backupStateHandler() {
    if (doOnEntry()) {
        query_filter_.serveNoScopes();
        adjustNetworkState();

        // Log if the state machine is paused.
        conditionalLogPausedState();
    }

    // There is nothing to do in that state. This server simply receives
    // lease updates from the partners.
    postNextEvent(NOP_EVT);
}

void
HAService::communicationRecoveryHandler() {
    if (doOnEntry()) {
        query_filter_.serveDefaultScopes();
        adjustNetworkState();

        // Log if the state machine is paused.
        conditionalLogPausedState();
    }

    scheduleHeartbeat();

    if (isMaintenanceCanceled() || isModelPaused()) {
        postNextEvent(NOP_EVT);

    // Check if the clock skew is still acceptable. If not, transition to
    // the terminated state.
    } else if (shouldTerminate()) {
        verboseTransition(HA_TERMINATED_ST);

    } else if (isPartnerStateInvalid()) {
        verboseTransition(HA_WAITING_ST);

    } else {

        // Transitions based on the partner's state.
        switch (communication_state_->getPartnerState()) {
        case HA_IN_MAINTENANCE_ST:
            verboseTransition(HA_PARTNER_IN_MAINTENANCE_ST);
            break;

        case HA_PARTNER_DOWN_ST:
            verboseTransition(HA_WAITING_ST);
            break;

        case HA_PARTNER_IN_MAINTENANCE_ST:
            verboseTransition(HA_IN_MAINTENANCE_ST);
            break;

        case HA_TERMINATED_ST:
            verboseTransition(HA_TERMINATED_ST);
            break;

        case HA_UNAVAILABLE_ST:
            if (shouldPartnerDown()) {
                verboseTransition(HA_PARTNER_DOWN_ST);

            } else {
                postNextEvent(NOP_EVT);
            }
            break;

        case HA_WAITING_ST:
        case HA_SYNCING_ST:
        case HA_READY_ST:
            // The partner seems to be waking up, perhaps after communication-recovery.
            // If our backlog queue is overflown we need to synchronize our lease database.
            // There is no need to send ha-reset to the partner because the partner is
            // already synchronizing its lease database.
            if (!communication_state_->isCommunicationInterrupted() &&
                lease_update_backlog_.wasOverflown()) {
                verboseTransition(HA_WAITING_ST);
            } else {
                // Backlog was not overflown, so there is no need to synchronize our
                // lease database. Let's wait until our partner completes synchronization
                // and transitions to the load-balancing state.
                postNextEvent(NOP_EVT);
            }
            break;

        default:
            // If the communication is still interrupted, let's continue sitting
            // in this state until it is resumed or until the transition to the
            // partner-down state, depending on what happens first.
            if (communication_state_->isCommunicationInterrupted()) {
                postNextEvent(NOP_EVT);
                break;
            }

            // The communication has been resumed. The partner server must be in a state
            // in which it can receive outstanding lease updates we collected. The number of
            // outstanding lease updates must not exceed the configured limit. Finally, the
            // lease updates must be successfully sent. If that all works, we will transition
            // to the normal operation.
            if ((communication_state_->getPartnerState() == getNormalState()) ||
                (communication_state_->getPartnerState() == HA_COMMUNICATION_RECOVERY_ST)) {
                if (lease_update_backlog_.wasOverflown() || !sendLeaseUpdatesFromBacklog()) {
                    // If our lease backlog was overflown or we were unable to send lease
                    // updates to the partner we should notify the partner that it should
                    // synchronize the lease database. We do it by sending ha-reset command.
                    if (sendHAReset()) {
                        verboseTransition(HA_WAITING_ST);
                    }
                    break;
                }
                // The backlog was not overflown and we successfully sent our lease updates.
                // We can now transition to the normal operation state. If the partner
                // fails to send his outstanding lease updates to us it should send the
                // ha-reset command to us.
                verboseTransition(getNormalState());
                break;
            }

            // The partner appears to be in unexpected state, we have exceeded the number
            // of lease updates in a backlog or an attempt to send lease updates failed.
            // In all these cases we follow plan B and transition to the waiting state.
            // The server will then attempt to synchronize the entire lease database.
            verboseTransition(HA_WAITING_ST);
        }
    }

    // When exiting this state we must ensure that lease updates backlog is cleared.
    if (doOnExit()) {
        lease_update_backlog_.clear();
    }
}

void
HAService::normalStateHandler() {
    // If we are transitioning from another state, we have to define new
    // serving scopes appropriate for the new state. We don't do it if
    // we remain in this state.
    if (doOnEntry()) {
        query_filter_.serveDefaultScopes();
        adjustNetworkState();

        // Log if the state machine is paused.
        conditionalLogPausedState();
    }

    scheduleHeartbeat();

    if (isMaintenanceCanceled() || isModelPaused()) {
        postNextEvent(NOP_EVT);
        return;
    }

    // Check if the clock skew is still acceptable. If not, transition to
    // the terminated state.
    if (shouldTerminate()) {
        verboseTransition(HA_TERMINATED_ST);
        return;
    }

    // Check if the partner state is valid per current configuration. If it is
    // in an invalid state let's transition to the waiting state and stay there
    // until the configuration is corrected.
    if (isPartnerStateInvalid()) {
        verboseTransition(HA_WAITING_ST);
        return;
    }

    switch (communication_state_->getPartnerState()) {
    case HA_IN_MAINTENANCE_ST:
        verboseTransition(HA_PARTNER_IN_MAINTENANCE_ST);
        break;

    case HA_PARTNER_DOWN_ST:
        verboseTransition(HA_WAITING_ST);
        break;

    case HA_PARTNER_IN_MAINTENANCE_ST:
        verboseTransition(HA_IN_MAINTENANCE_ST);
        break;

    case HA_TERMINATED_ST:
        verboseTransition(HA_TERMINATED_ST);
        break;

    case HA_UNAVAILABLE_ST:
        if (shouldPartnerDown()) {
            verboseTransition(HA_PARTNER_DOWN_ST);

        } else if (config_->amAllowingCommRecovery()) {
            verboseTransition(HA_COMMUNICATION_RECOVERY_ST);

        } else {
            postNextEvent(NOP_EVT);
        }
        break;

    default:
        postNextEvent(NOP_EVT);
    }

    if (doOnExit()) {
        // Do nothing here but doOnExit() call clears the "on exit" flag
        // when transitioning to the communication-recovery state. In that
        // state we need this flag to be cleared.
    }
}

void
HAService::inMaintenanceStateHandler() {
    // If we are transitioning from another state, we have to define new
    // serving scopes appropriate for the new state. We don't do it if
    // we remain in this state.
    if (doOnEntry()) {
        // In this state the server remains silent and waits for being
        // shutdown.
        query_filter_.serveNoScopes();
        adjustNetworkState();

        // Log if the state machine is paused.
        conditionalLogPausedState();

        LOG_INFO(ha_logger, HA_MAINTENANCE_SHUTDOWN_SAFE);
    }

    scheduleHeartbeat();

    // We don't transition out of this state unless explicitly mandated
    // by the administrator via a dedicated command which cancels
    // the maintenance.
    postNextEvent(NOP_EVT);
}

void
HAService::partnerDownStateHandler() {
    // If we are transitioning from another state, we have to define new
    // serving scopes appropriate for the new state. We don't do it if
    // we remain in this state.
    if (doOnEntry()) {

        bool maintenance = (getLastEvent() == HA_MAINTENANCE_START_EVT);

        // It may be administratively disabled to handle partner's scope
        // in case of failure. If this is the case we'll just handle our
        // default scope (or no scope at all). The user will need to
        // manually enable this server to handle partner's scope.
        // If we're in the maintenance mode we serve all scopes because
        // it is not a failover situation.
        if (maintenance || config_->getThisServerConfig()->isAutoFailover()) {
            query_filter_.serveFailoverScopes();
        } else {
            query_filter_.serveDefaultScopes();
        }
        adjustNetworkState();

        // Log if the state machine is paused.
        conditionalLogPausedState();

        if (maintenance) {
            // If we ended up in the partner-down state as a result of
            // receiving the ha-maintenance-start command let's log it.
            LOG_INFO(ha_logger, HA_MAINTENANCE_STARTED_IN_PARTNER_DOWN);
        }

    } else if (getLastEvent() == HA_SYNCED_PARTNER_UNAVAILABLE_EVT) {
        // Partner sent the ha-sync-complete-notify command to indicate that
        // it has successfully synchronized its lease database but this server
        // was unable to send heartbeat to this server. Enable the DHCP service
        // and continue serving the clients in the partner-down state until the
        // communication with the partner is fixed.
        adjustNetworkState();
    }

    scheduleHeartbeat();

    if (isMaintenanceCanceled() || isModelPaused()) {
        postNextEvent(NOP_EVT);
        return;
    }

    // Check if the clock skew is still acceptable. If not, transition to
    // the terminated state.
    if (shouldTerminate()) {
        verboseTransition(HA_TERMINATED_ST);
        return;
    }

    // Check if the partner state is valid per current configuration. If it is
    // in an invalid state let's transition to the waiting state and stay there
    // until the configuration is corrected.
    if (isPartnerStateInvalid()) {
        verboseTransition(HA_WAITING_ST);
        return;
    }

    switch (communication_state_->getPartnerState()) {
    case HA_COMMUNICATION_RECOVERY_ST:
    case HA_PARTNER_DOWN_ST:
    case HA_PARTNER_IN_MAINTENANCE_ST:
        verboseTransition(HA_WAITING_ST);
        break;

    case HA_READY_ST:
        // If partner allocated new leases for which it didn't send lease updates
        // to us we should synchronize our database.
        if (communication_state_->hasPartnerNewUnsentUpdates()) {
            verboseTransition(HA_WAITING_ST);
        } else {
            // We did not miss any lease updates. There is no need to synchronize
            // the database.
            verboseTransition(getNormalState());
        }
        break;

    case HA_TERMINATED_ST:
        verboseTransition(HA_TERMINATED_ST);
        break;

    default:
        postNextEvent(NOP_EVT);
    }
}

void
HAService::partnerInMaintenanceStateHandler() {
    // If we are transitioning from another state, we have to define new
    // serving scopes appropriate for the new state. We don't do it if
    // we remain in this state.
    if (doOnEntry()) {
        query_filter_.serveFailoverScopes();

        adjustNetworkState();

        // Log if the state machine is paused.
        conditionalLogPausedState();

        LOG_INFO(ha_logger, HA_MAINTENANCE_STARTED);
    }

    scheduleHeartbeat();

    if (isModelPaused()) {
        postNextEvent(NOP_EVT);
        return;
    }

    // Check if the clock skew is still acceptable. If not, transition to
    // the terminated state.
    if (shouldTerminate()) {
        verboseTransition(HA_TERMINATED_ST);
        return;
    }

    switch (communication_state_->getPartnerState()) {
    case HA_UNAVAILABLE_ST:
        verboseTransition(HA_PARTNER_DOWN_ST);
        break;
    default:
        postNextEvent(NOP_EVT);
    }
}

void
HAService::passiveBackupStateHandler() {
    // If we are transitioning from another state, we have to define new
    // serving scopes appropriate for the new state. We don't do it if
    // we remain in this state.
    if (doOnEntry()) {
        query_filter_.serveDefaultScopes();
        adjustNetworkState();

        // In the passive-backup state we don't send heartbeat.
        communication_state_->stopHeartbeat();

        // Log if the state machine is paused.
        conditionalLogPausedState();
    }
    postNextEvent(NOP_EVT);
}

void
HAService::readyStateHandler() {
    // If we are transitioning from another state, we have to define new
    // serving scopes appropriate for the new state. We don't do it if
    // we remain in this state.
    if (doOnEntry()) {
        query_filter_.serveNoScopes();
        adjustNetworkState();

        // Log if the state machine is paused.
        conditionalLogPausedState();
    }

    scheduleHeartbeat();

    if (isMaintenanceCanceled() || isModelPaused()) {
        postNextEvent(NOP_EVT);
        return;
    }

    // Check if the clock skew is still acceptable. If not, transition to
    // the terminated state.
    if (shouldTerminate()) {
        verboseTransition(HA_TERMINATED_ST);
        return;
    }

    // Check if the partner state is valid per current configuration. If it is
    // in an invalid state let's transition to the waiting state and stay there
    // until the configuration is corrected.
    if (isPartnerStateInvalid()) {
        verboseTransition(HA_WAITING_ST);
        return;
    }

    switch (communication_state_->getPartnerState()) {
    case HA_HOT_STANDBY_ST:
    case HA_LOAD_BALANCING_ST:
    case HA_COMMUNICATION_RECOVERY_ST:
        verboseTransition(getNormalState());
        break;

    case HA_IN_MAINTENANCE_ST:
        verboseTransition(HA_PARTNER_IN_MAINTENANCE_ST);
        break;

    case HA_PARTNER_IN_MAINTENANCE_ST:
        verboseTransition(HA_IN_MAINTENANCE_ST);
        break;

    case HA_READY_ST:
        // If both servers are ready, the primary server "wins" and is
        // transitioned first.
        if (config_->getThisServerConfig()->getRole() == HAConfig::PeerConfig::PRIMARY) {
            verboseTransition((config_->getHAMode() == HAConfig::LOAD_BALANCING ?
                       HA_LOAD_BALANCING_ST : HA_HOT_STANDBY_ST));
        } else {
            postNextEvent(NOP_EVT);
        }
        break;

    case HA_TERMINATED_ST:
        verboseTransition(HA_TERMINATED_ST);
        break;

    case HA_UNAVAILABLE_ST:
        if (shouldPartnerDown()) {
            verboseTransition(HA_PARTNER_DOWN_ST);

        } else {
            postNextEvent(NOP_EVT);
        }
        break;

    default:
        postNextEvent(NOP_EVT);
    }
}

void
HAService::syncingStateHandler() {
    // If we are transitioning from another state, we have to define new
    // serving scopes appropriate for the new state. We don't do it if
    // we remain in this state.
    if (doOnEntry()) {
        query_filter_.serveNoScopes();
        adjustNetworkState();

        // Log if the state machine is paused.
        conditionalLogPausedState();
    }

    if (isMaintenanceCanceled() || isModelPaused()) {
        postNextEvent(NOP_EVT);
        return;
    }

    // Check if the clock skew is still acceptable. If not, transition to
    // the terminated state.
    if (shouldTerminate()) {
        verboseTransition(HA_TERMINATED_ST);
        return;
    }

    // Check if the partner state is valid per current configuration. If it is
    // in an invalid state let's transition to the waiting state and stay there
    // until the configuration is corrected.
    if (isPartnerStateInvalid()) {
        verboseTransition(HA_WAITING_ST);
        return;
    }

    // We don't want to perform synchronous attempt to synchronize with
    // a partner until we know that the partner is responding. Therefore,
    // we wait for the heartbeat to complete successfully before we
    // initiate the synchronization.
    switch (communication_state_->getPartnerState()) {
    case HA_TERMINATED_ST:
        verboseTransition(HA_TERMINATED_ST);
        return;

    case HA_UNAVAILABLE_ST:
        // If the partner appears to be offline, let's transition to the partner
        // down state. Otherwise, we'd be stuck trying to synchronize with a
        // dead partner.
        if (shouldPartnerDown()) {
            verboseTransition(HA_PARTNER_DOWN_ST);

        } else {
            postNextEvent(NOP_EVT);
        }
        break;

    default:
        // We don't want the heartbeat to interfere with the synchronization,
        // so let's temporarily stop it.
        communication_state_->stopHeartbeat();

        // Timeout is configured in milliseconds. Need to convert to seconds.
        unsigned int dhcp_disable_timeout =
            static_cast<unsigned int>(config_->getSyncTimeout() / 1000);
        if (dhcp_disable_timeout == 0) {
            ++dhcp_disable_timeout;
        }

        // Perform synchronous leases update.
        std::string status_message;
        int sync_status = synchronize(status_message,
                                      config_->getFailoverPeerConfig()->getName(),
                                      dhcp_disable_timeout);

        // If the leases synchronization was successful, let's transition
        // to the ready state.
        if (sync_status == CONTROL_RESULT_SUCCESS) {
            verboseTransition(HA_READY_ST);

        } else {
            // If the synchronization was unsuccessful we're back to the
            // situation that the partner is unavailable and therefore
            // we stay in the syncing state.
            postNextEvent(NOP_EVT);
        }
    }

    // Make sure that the heartbeat is re-enabled.
    scheduleHeartbeat();
}

void
HAService::terminatedStateHandler() {
    // If we are transitioning from another state, we have to define new
    // serving scopes appropriate for the new state. We don't do it if
    // we remain in this state.
    if (doOnEntry()) {
        query_filter_.serveDefaultScopes();
        adjustNetworkState();

        // In the terminated state we don't send heartbeat.
        communication_state_->stopHeartbeat();

        // Log if the state machine is paused.
        conditionalLogPausedState();

        LOG_ERROR(ha_logger, HA_TERMINATED);
    }

    postNextEvent(NOP_EVT);
}

void
HAService::waitingStateHandler() {
    // If we are transitioning from another state, we have to define new
    // serving scopes appropriate for the new state. We don't do it if
    // we remain in this state.
    if (doOnEntry()) {
        query_filter_.serveNoScopes();
        adjustNetworkState();

        // Log if the state machine is paused.
        conditionalLogPausedState();
    }

    // Only schedule the heartbeat for non-backup servers.
    if ((config_->getHAMode() != HAConfig::PASSIVE_BACKUP) &&
        (config_->getThisServerConfig()->getRole() != HAConfig::PeerConfig::BACKUP)) {
        scheduleHeartbeat();
    }

    if (isMaintenanceCanceled() || isModelPaused()) {
        postNextEvent(NOP_EVT);
        return;
    }

    // Backup server must remain in its own state.
    if (config_->getThisServerConfig()->getRole() == HAConfig::PeerConfig::BACKUP) {
        verboseTransition(HA_BACKUP_ST);
        return;
    }

    // We're not a backup server, so we're either primary or secondary. If this is
    // a passive-backup mode of operation, we're primary and we should transition
    // to the passive-backup state.
    if (config_->getHAMode() == HAConfig::PASSIVE_BACKUP) {
        verboseTransition(HA_PASSIVE_BACKUP_ST);
        return;
    }

    // Check if the clock skew is still acceptable. If not, transition to
    // the terminated state.
    if (shouldTerminate()) {
        verboseTransition(HA_TERMINATED_ST);
        return;
    }

    // Check if the partner state is valid per current configuration. If it is
    // in an invalid state let's sit in the waiting state until the configuration
    // is corrected.
    if (isPartnerStateInvalid()) {
        postNextEvent(NOP_EVT);
        return;
    }

    switch (communication_state_->getPartnerState()) {
    case HA_COMMUNICATION_RECOVERY_ST:
    case HA_HOT_STANDBY_ST:
    case HA_LOAD_BALANCING_ST:
    case HA_IN_MAINTENANCE_ST:
    case HA_PARTNER_DOWN_ST:
    case HA_PARTNER_IN_MAINTENANCE_ST:
    case HA_READY_ST:
        // If we're configured to not synchronize lease database, proceed directly
        // to the "ready" state.
        verboseTransition(config_->amSyncingLeases() ? HA_SYNCING_ST : HA_READY_ST);
        break;

    case HA_SYNCING_ST:
        postNextEvent(NOP_EVT);
        break;

    case HA_TERMINATED_ST:
        // We have checked above whether the clock skew is exceeding the threshold
        // and we should terminate. If we're here, it means that the clock skew
        // is acceptable. The partner may be still in the terminated state because
        // it hasn't been restarted yet. Probably, this server is the first one
        // being restarted after syncing the clocks. Let's just sit in the waiting
        // state until the partner gets restarted.
        LOG_INFO(ha_logger, HA_TERMINATED_RESTART_PARTNER);
        postNextEvent(NOP_EVT);
        break;

    case HA_WAITING_ST:
        // If both servers are waiting, the primary server 'wins' and is
        // transitioned to the next state first.
        if (config_->getThisServerConfig()->getRole() == HAConfig::PeerConfig::PRIMARY) {
            // If we're configured to not synchronize lease database, proceed directly
            // to the "ready" state.
            verboseTransition(config_->amSyncingLeases() ? HA_SYNCING_ST : HA_READY_ST);

        } else {
            postNextEvent(NOP_EVT);
        }
        break;

    case HA_UNAVAILABLE_ST:
        if (shouldPartnerDown()) {
            verboseTransition(HA_PARTNER_DOWN_ST);

        } else {
            postNextEvent(NOP_EVT);
        }
        break;

    default:
        postNextEvent(NOP_EVT);
    }
}

void
HAService::verboseTransition(const unsigned state) {
    // Get current and new state name.
    std::string current_state_name = getStateLabel(getCurrState());
    std::string new_state_name = getStateLabel(state);

    // Turn them to upper case so as they are better visible in the logs.
    boost::to_upper(current_state_name);
    boost::to_upper(new_state_name);

    if (config_->getHAMode() != HAConfig::PASSIVE_BACKUP) {
        // If this is load-balancing or hot-standby mode we also want to log
        // partner's state.
        auto partner_state = communication_state_->getPartnerState();
        std::string partner_state_name = getStateLabel(partner_state);
        boost::to_upper(partner_state_name);

        // Log the transition.
        LOG_INFO(ha_logger, HA_STATE_TRANSITION)
            .arg(current_state_name)
            .arg(new_state_name)
            .arg(partner_state_name);

    } else {
        // In the passive-backup mode we don't know the partner's state.
        LOG_INFO(ha_logger, HA_STATE_TRANSITION_PASSIVE_BACKUP)
            .arg(current_state_name)
            .arg(new_state_name);
    }

    // If we're transitioning directly from the "waiting" to "ready"
    // state it indicates that the database synchronization is
    // administratively disabled. Let's remind the user about this
    // configuration setting.
    if ((state == HA_READY_ST) && (getCurrState() == HA_WAITING_ST)) {
        LOG_INFO(ha_logger, HA_CONFIG_LEASE_SYNCING_DISABLED_REMINDER);
    }

    // Do the actual transition.
    transition(state, getNextEvent());

    // Inform the administrator whether or not lease updates are generated.
    // Updates are never generated by a backup server so it doesn't make
    // sense to log anything for the backup server.
    if ((config_->getHAMode() != HAConfig::PASSIVE_BACKUP) &&
        (config_->getThisServerConfig()->getRole() != HAConfig::PeerConfig::BACKUP)) {
        if (shouldSendLeaseUpdates(config_->getFailoverPeerConfig())) {
            LOG_INFO(ha_logger, HA_LEASE_UPDATES_ENABLED)
                .arg(new_state_name);

        } else if (!config_->amSendingLeaseUpdates()) {
            // Lease updates are administratively disabled.
            LOG_INFO(ha_logger, HA_CONFIG_LEASE_UPDATES_DISABLED_REMINDER)
                .arg(new_state_name);

        } else {
            // Lease updates are not administratively disabled, but they
            // are not issued because this is the backup server or because
            // in this state the server should not generate lease updates.
            LOG_INFO(ha_logger, HA_LEASE_UPDATES_DISABLED)
                .arg(new_state_name);
        }
    }
}

int
HAService::getNormalState() const {
    if (config_->getThisServerConfig()->getRole() == HAConfig::PeerConfig::BACKUP) {
        return (HA_BACKUP_ST);
    }

    switch (config_->getHAMode()) {
    case HAConfig::LOAD_BALANCING:
        return (HA_LOAD_BALANCING_ST);
    case HAConfig::HOT_STANDBY:
        return (HA_HOT_STANDBY_ST);
    default:
        return (HA_PASSIVE_BACKUP_ST);
    }
}

bool
HAService::unpause() {
    if (isModelPaused()) {
        LOG_INFO(ha_logger, HA_STATE_MACHINE_CONTINUED);
        unpauseModel();
        return (true);
    }
    return (false);
}

void
HAService::conditionalLogPausedState() const {
    // Inform the administrator if the state machine is paused.
    if (isModelPaused()) {
        std::string state_name = stateToString(getCurrState());
        boost::to_upper(state_name);
        LOG_INFO(ha_logger, HA_STATE_MACHINE_PAUSED)
            .arg(state_name);
    }
}

void
HAService::serveDefaultScopes() {
    query_filter_.serveDefaultScopes();
}

bool
HAService::inScope(dhcp::Pkt4Ptr& query4) {
    return (inScopeInternal(query4));
}

bool
HAService::inScope(dhcp::Pkt6Ptr& query6) {
    return (inScopeInternal(query6));
}

template<typename QueryPtrType>
bool
HAService::inScopeInternal(QueryPtrType& query) {
    // Check if the query is in scope (should be processed by this server).
    std::string scope_class;
    const bool in_scope = query_filter_.inScope(query, scope_class);
    // Whether or not the query is going to be processed by this server,
    // we associate the query with the appropriate class.
    query->addClass(dhcp::ClientClass(scope_class));
    // The following is the part of the server failure detection algorithm.
    // If the query should be processed by the partner we need to check if
    // the partner responds. If the number of unanswered queries exceeds a
    // configured threshold, we will consider the partner to be offline.
    if (!in_scope && communication_state_->isCommunicationInterrupted()) {
        communication_state_->analyzeMessage(query);
    }
    // Indicate if the query is in scope.
    return (in_scope);
}

void
HAService::adjustNetworkState() {
    std::string current_state_name = getStateLabel(getCurrState());
    boost::to_upper(current_state_name);

    // DHCP service should be enabled in the following states.
    const bool should_enable = ((getCurrState() == HA_COMMUNICATION_RECOVERY_ST) ||
                                (getCurrState() == HA_LOAD_BALANCING_ST) ||
                                (getCurrState() == HA_HOT_STANDBY_ST) ||
                                (getCurrState() == HA_PARTNER_DOWN_ST) ||
                                (getCurrState() == HA_PARTNER_IN_MAINTENANCE_ST) ||
                                (getCurrState() == HA_PASSIVE_BACKUP_ST) ||
                                (getCurrState() == HA_TERMINATED_ST));

    if (!should_enable && network_state_->isServiceEnabled()) {
        std::string current_state_name = getStateLabel(getCurrState());
        boost::to_upper(current_state_name);
        LOG_INFO(ha_logger, HA_LOCAL_DHCP_DISABLE)
            .arg(config_->getThisServerName())
            .arg(current_state_name);
        network_state_->disableService(NetworkState::Origin::HA_COMMAND);

    } else if (should_enable && !network_state_->isServiceEnabled()) {
        std::string current_state_name = getStateLabel(getCurrState());
        boost::to_upper(current_state_name);
        LOG_INFO(ha_logger, HA_LOCAL_DHCP_ENABLE)
            .arg(config_->getThisServerName())
            .arg(current_state_name);
        network_state_->enableService(NetworkState::Origin::HA_COMMAND);
    }
}

bool
HAService::shouldPartnerDown() const {
    // Checking whether the communication with the partner is OK is the
    // first step towards verifying if the server is up.
    if (communication_state_->isCommunicationInterrupted()) {
        // If the communication is interrupted, we also have to check
        // whether the partner answers DHCP requests. The only cases
        // when we don't (can't) do it are: the hot standby configuration
        // in which this server is a primary and when the DHCP service is
        // disabled so we can't analyze incoming traffic. Note that the
        // primary server can't check delayed responses to the partner
        // because the partner doesn't respond to any queries in this
        // configuration.
        if (network_state_->isServiceEnabled() &&
            ((config_->getHAMode() == HAConfig::LOAD_BALANCING) ||
             (config_->getThisServerConfig()->getRole() == HAConfig::PeerConfig::STANDBY))) {
            return (communication_state_->failureDetected());
        }

        // Hot standby / primary case.
        return (true);
    }

    // Shouldn't transition to the partner down state.
    return (false);
}

bool
HAService::shouldTerminate() const {
    // Check if skew is fatally large.
    bool should_terminate = communication_state_->clockSkewShouldTerminate();

    // If not issue a warning if it's getting large.
    if (!should_terminate) {
        communication_state_->clockSkewShouldWarn();
    }

    return (should_terminate);
}

bool
HAService::isMaintenanceCanceled() const {
    return (getLastEvent() == HA_MAINTENANCE_CANCEL_EVT);
}

bool
HAService::isPartnerStateInvalid() const {
    switch (communication_state_->getPartnerState()) {
        case HA_COMMUNICATION_RECOVERY_ST:
            if (config_->getHAMode() != HAConfig::LOAD_BALANCING) {
                LOG_WARN(ha_logger, HA_INVALID_PARTNER_STATE_COMMUNICATION_RECOVERY);
                return (true);
            }
            break;

        case HA_HOT_STANDBY_ST:
            if (config_->getHAMode() != HAConfig::HOT_STANDBY) {
                LOG_WARN(ha_logger, HA_INVALID_PARTNER_STATE_HOT_STANDBY);
                return (true);
            }
            break;

        case HA_LOAD_BALANCING_ST:
            if (config_->getHAMode() != HAConfig::LOAD_BALANCING) {
                LOG_WARN(ha_logger, HA_INVALID_PARTNER_STATE_LOAD_BALANCING);
                return (true);
            }
            break;

       default:
           ;
    }
    return (false);
}

size_t
HAService::asyncSendLeaseUpdates(const dhcp::Pkt4Ptr& query,
                                 const dhcp::Lease4CollectionPtr& leases,
                                 const dhcp::Lease4CollectionPtr& deleted_leases,
                                 const hooks::ParkingLotHandlePtr& parking_lot) {

    // Get configurations of the peers. Exclude this instance.
    HAConfig::PeerConfigMap peers_configs = config_->getOtherServersConfig();

    size_t sent_num = 0;

    // Schedule sending lease updates to each peer.
    for (auto p = peers_configs.begin(); p != peers_configs.end(); ++p) {
        HAConfig::PeerConfigPtr conf = p->second;

        // Check if the lease updates should be queued. This is the case when the
        // server is in the communication-recovery state. Queued lease updates may
        // be sent when the communication is re-established.
        if (shouldQueueLeaseUpdates(conf)) {
            // Lease updates for deleted leases.
            for (auto l = deleted_leases->begin(); l != deleted_leases->end(); ++l) {
                lease_update_backlog_.push(LeaseUpdateBacklog::DELETE, *l);
            }

            // Lease updates for new allocations and updated leases.
            for (auto l = leases->begin(); l != leases->end(); ++l) {
                lease_update_backlog_.push(LeaseUpdateBacklog::ADD, *l);
            }

            continue;
        }

        // Check if the lease update should be sent to the server. If we're in
        // the partner-down state we don't send lease updates to the partner.
        if (!shouldSendLeaseUpdates(conf)) {
            // If we decide to not send the lease updates to an active partner, we
            // should make a record of it in the communication state. The partner
            // can check if there were any unsent lease updates when he determines
            // whether it should synchronize its database or not when it recovers
            // from the partner-down state.
            if (conf->getRole() != HAConfig::PeerConfig::BACKUP) {
                communication_state_->increaseUnsentUpdateCount();
            }
            continue;
        }

        // Lease updates for deleted leases.
        for (auto l = deleted_leases->begin(); l != deleted_leases->end(); ++l) {
            asyncSendLeaseUpdate(query, conf, CommandCreator::createLease4Delete(**l),
                                 parking_lot);
        }

        // Lease updates for new allocations and updated leases.
        for (auto l = leases->begin(); l != leases->end(); ++l) {
            asyncSendLeaseUpdate(query, conf, CommandCreator::createLease4Update(**l),
                                 parking_lot);
        }

        // If we're contacting a backup server from which we don't expect a
        // response prior to responding to the DHCP client we don't count
        // it.
        if ((config_->amWaitingBackupAck() || (conf->getRole() != HAConfig::PeerConfig::BACKUP))) {
            ++sent_num;
        }
    }

    return (sent_num);
}

size_t
HAService::asyncSendLeaseUpdates(const dhcp::Pkt6Ptr& query,
                                 const dhcp::Lease6CollectionPtr& leases,
                                 const dhcp::Lease6CollectionPtr& deleted_leases,
                                 const hooks::ParkingLotHandlePtr& parking_lot) {

    // Get configurations of the peers. Exclude this instance.
    HAConfig::PeerConfigMap peers_configs = config_->getOtherServersConfig();

    size_t sent_num = 0;

    // Schedule sending lease updates to each peer.
    for (auto p = peers_configs.begin(); p != peers_configs.end(); ++p) {
        HAConfig::PeerConfigPtr conf = p->second;

        // Check if the lease updates should be queued. This is the case when the
        // server is in the communication-recovery state. Queued lease updates may
        // be sent when the communication is re-established.
        if (shouldQueueLeaseUpdates(conf)) {
            for (auto l = deleted_leases->begin(); l != deleted_leases->end(); ++l) {
                lease_update_backlog_.push(LeaseUpdateBacklog::DELETE, *l);
            }

            // Lease updates for new allocations and updated leases.
            for (auto l = leases->begin(); l != leases->end(); ++l) {
                lease_update_backlog_.push(LeaseUpdateBacklog::ADD, *l);
            }

            continue;
        }

        // Check if the lease update should be sent to the server. If we're in
        // the partner-down state we don't send lease updates to the partner.
        if (!shouldSendLeaseUpdates(conf)) {
            // If we decide to not send the lease updates to an active partner, we
            // should make a record of it in the communication state. The partner
            // can check if there were any unsent lease updates when he determines
            // whether it should synchronize its database or not when it recovers
            // from the partner-down state.
            if (conf->getRole() != HAConfig::PeerConfig::BACKUP) {
                communication_state_->increaseUnsentUpdateCount();
            }
            continue;
        }

        // If we're contacting a backup server from which we don't expect a
        // response prior to responding to the DHCP client we don't count
        // it.
        if (config_->amWaitingBackupAck() || (conf->getRole() != HAConfig::PeerConfig::BACKUP)) {
            ++sent_num;
        }

        // Send new/updated leases and deleted leases in one command.
        asyncSendLeaseUpdate(query, conf, CommandCreator::createLease6BulkApply(leases, deleted_leases),
                             parking_lot);
    }

    return (sent_num);
}

template<typename QueryPtrType>
bool
HAService::leaseUpdateComplete(QueryPtrType& query,
                               const ParkingLotHandlePtr& parking_lot) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(mutex_);
        return (leaseUpdateCompleteInternal(query, parking_lot));
    } else {
        return (leaseUpdateCompleteInternal(query, parking_lot));
    }
}

template<typename QueryPtrType>
bool
HAService::leaseUpdateCompleteInternal(QueryPtrType& query,
                                       const ParkingLotHandlePtr& parking_lot) {
    auto it = pending_requests_.find(query);

    // If there are no more pending requests for this query, let's unpark
    // the DHCP packet.
    if (it == pending_requests_.end() || (--pending_requests_[query] <= 0)) {
        parking_lot->unpark(query);

        // If we have unparked the packet we can clear pending requests for
        // this query.
        if (it != pending_requests_.end()) {
            pending_requests_.erase(it);
        }
        return (true);
    }
    return (false);
}

template<typename QueryPtrType>
void
HAService::updatePendingRequest(QueryPtrType& query) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(mutex_);
        updatePendingRequestInternal(query);
    } else {
        updatePendingRequestInternal(query);
    }
}

template<typename QueryPtrType>
void
HAService::updatePendingRequestInternal(QueryPtrType& query) {
    if (pending_requests_.count(query) == 0) {
        pending_requests_[query] = 1;
    } else {
        ++pending_requests_[query];
    }
}

template<typename QueryPtrType>
void
HAService::asyncSendLeaseUpdate(const QueryPtrType& query,
                                const HAConfig::PeerConfigPtr& config,
                                const ConstElementPtr& command,
                                const ParkingLotHandlePtr& parking_lot) {
    // Create HTTP/1.1 request including our command.
    PostHttpRequestJsonPtr request = boost::make_shared<PostHttpRequestJson>
        (HttpRequest::Method::HTTP_POST, "/", HttpVersion::HTTP_11(),
         HostHttpHeader(config->getUrl().getStrippedHostname()));
    config->addBasicAuthHttpHeader(request);
    request->setBodyAsJson(command);
    request->finalize();

    // Response object should also be created because the HTTP client needs
    // to know the type of the expected response.
    HttpResponseJsonPtr response = boost::make_shared<HttpResponseJson>();

    // When possible we prefer to pass weak pointers to the queries, rather
    // than shared pointers, to avoid memory leaks in case cross reference
    // between the pointers.
    boost::weak_ptr<typename QueryPtrType::element_type> weak_query(query);

    // Schedule asynchronous HTTP request.
    client_->asyncSendRequest(config->getUrl(), config->getTlsContext(),
                              request, response,
        [this, weak_query, parking_lot, config]
            (const boost::system::error_code& ec,
             const HttpResponsePtr& response,
             const std::string& error_str) {
            // Get the shared pointer of the query. The server should keep the
            // pointer to the query and then park it. Therefore, we don't really
            // expect it to be null. If it is null, something is really wrong.
            QueryPtrType query = weak_query.lock();
            if (!query) {
                isc_throw(Unexpected, "query is null while receiving response from"
                          " HA peer. This is programmatic error");
            }

            // There are three possible groups of errors during the lease update.
            // One is the IO error causing issues in communication with the peer.
            // Another one is an HTTP parsing error. The last type of error is
            // when non-success error code is returned in the response carried
            // in the HTTP message or if the JSON response is otherwise broken.

            bool lease_update_success = true;

            // Handle first two groups of errors.
            if (ec || !error_str.empty()) {
                LOG_WARN(ha_logger, HA_LEASE_UPDATE_COMMUNICATIONS_FAILED)
                    .arg(query->getLabel())
                    .arg(config->getLogLabel())
                    .arg(ec ? ec.message() : error_str);

                // Communication error, so let's drop parked packet. The DHCP
                // response will not be sent.
                lease_update_success = false;

            } else {

                // Handle third group of errors.
                try {
                    int rcode = 0;
                    auto args = verifyAsyncResponse(response, rcode);
                    // In the v6 case the server may return a list of failed lease
                    // updates and we should log them.
                    logFailedLeaseUpdates(query, args);

                } catch (const std::exception& ex) {
                    LOG_WARN(ha_logger, HA_LEASE_UPDATE_FAILED)
                        .arg(query->getLabel())
                        .arg(config->getLogLabel())
                        .arg(ex.what());

                    // Error while doing an update. The DHCP response will not be sent.
                    lease_update_success = false;
                }
            }

            // We don't care about the result of the lease update to the backup server.
            // It is a best effort update.
            if ((config->getRole() != HAConfig::PeerConfig::BACKUP) && !lease_update_success) {
                // If we were unable to communicate with the partner we set partner's
                // state as unavailable.
                communication_state_->setPartnerState("unavailable");
            }

            // It is possible to configure the server to not wait for a response from
            // the backup server before we unpark the packet and respond to the client.
            // Here we check if we're dealing with such situation.
            if (config_->amWaitingBackupAck() || (config->getRole() != HAConfig::PeerConfig::BACKUP)) {
                // We're expecting a response from the backup server or it is not
                // a backup server and the lease update was unsuccessful. In such
                // case the DHCP exchange fails.
                if (!lease_update_success) {
                    parking_lot->drop(query);
                }
            } else {
                // This was a response from the backup server and we're configured to
                // not wait for their acknowledgments, so there is nothing more to do.
                return;
            }

            if (leaseUpdateComplete(query, parking_lot)) {
                // If we have finished sending the lease updates we need to run the
                // state machine until the state machine finds that additional events
                // are required, such as next heartbeat or a lease update. The runModel()
                // may transition to another state, schedule asynchronous tasks etc.
                // Then it returns control to the DHCP server.
                runModel(HA_LEASE_UPDATES_COMPLETE_EVT);
            }
        },
        HttpClient::RequestTimeout(TIMEOUT_DEFAULT_HTTP_CLIENT_REQUEST),
        std::bind(&HAService::clientConnectHandler, this, ph::_1, ph::_2),
        std::bind(&HAService::clientHandshakeHandler, this, ph::_1),
        std::bind(&HAService::clientCloseHandler, this, ph::_1)
    );

    // The number of pending requests is the number of requests for which we
    // expect an acknowledgment prior to responding to the DHCP clients. If
    // we're configured to wait for the acks from the backups or it is not
    // a backup increase the number of pending requests.
    if (config_->amWaitingBackupAck() || (config->getRole() != HAConfig::PeerConfig::BACKUP)) {
        // Request scheduled, so update the request counters for the query.
        updatePendingRequest(query);
    }
}

bool
HAService::shouldSendLeaseUpdates(const HAConfig::PeerConfigPtr& peer_config) const {
    // Never send lease updates if they are administratively disabled.
    if (!config_->amSendingLeaseUpdates()) {
        return (false);
    }

    // Always send updates to the backup server.
    if (peer_config->getRole() == HAConfig::PeerConfig::BACKUP) {
        return (true);
    }

    // Never send updates if this is a backup server.
    if (config_->getThisServerConfig()->getRole() == HAConfig::PeerConfig::BACKUP) {
        return (false);
    }

    // In other case, whether we send lease updates or not depends on our
    // state.
    switch (getCurrState()) {
    case HA_HOT_STANDBY_ST:
    case HA_LOAD_BALANCING_ST:
    case HA_PARTNER_IN_MAINTENANCE_ST:
        return (true);

    default:
        ;
    }

    return (false);
}

bool
HAService::shouldQueueLeaseUpdates(const HAConfig::PeerConfigPtr& peer_config) const {
    if (!config_->amSendingLeaseUpdates()) {
        return (false);
    }

    if (peer_config->getRole() == HAConfig::PeerConfig::BACKUP) {
        return (false);
    }

    return (getCurrState() == HA_COMMUNICATION_RECOVERY_ST);
}

void
HAService::logFailedLeaseUpdates(const PktPtr& query,
                                 const ConstElementPtr& args) const {
    // If there are no arguments, it means that the update was successful.
    if (!args || (args->getType() != Element::map)) {
        return;
    }

    // Instead of duplicating the code between the failed-deleted-leases and
    // failed-leases, let's just have one function that does it for both.
    auto log_proc = [](const PktPtr query, const ConstElementPtr& args,
                       const std::string& param_name, const log::MessageID& mesid) {

        // Check if there are any failed leases.
        auto failed_leases = args->get(param_name);

        // The failed leases must be a list.
        if (failed_leases && (failed_leases->getType() == Element::list)) {
            // Go over the failed leases and log each of them.
            for (int i = 0; i < failed_leases->size(); ++i) {
                auto lease = failed_leases->get(i);
                if (lease->getType() == Element::map) {

                    // ip-address
                    auto ip_address = lease->get("ip-address");

                    // lease type
                    auto lease_type = lease->get("type");

                    // error-message
                    auto error_message = lease->get("error-message");

                    LOG_INFO(ha_logger, mesid)
                        .arg(query->getLabel())
                        .arg(lease_type && (lease_type->getType() == Element::string) ?
                             lease_type->stringValue() : "(unknown)")
                        .arg(ip_address && (ip_address->getType() == Element::string) ?
                             ip_address->stringValue() : "(unknown)")
                        .arg(error_message && (error_message->getType() == Element::string) ?
                             error_message->stringValue() : "(unknown)");
                }
            }
        }
    };

    // Process "failed-deleted-leases"
    log_proc(query, args, "failed-deleted-leases", HA_LEASE_UPDATE_DELETE_FAILED_ON_PEER);

    // Process "failed-leases".
    log_proc(query, args, "failed-leases", HA_LEASE_UPDATE_CREATE_UPDATE_FAILED_ON_PEER);
}

ConstElementPtr
HAService::processStatusGet() const {
    ElementPtr ha_servers = Element::createMap();

    // Local part
    ElementPtr local = Element::createMap();
    HAConfig::PeerConfig::Role role;
    role = config_->getThisServerConfig()->getRole();
    std::string role_txt = HAConfig::PeerConfig::roleToString(role);
    local->set("role", Element::create(role_txt));
    int state = getCurrState();
    try {
        local->set("state", Element::create(stateToString(state)));

    } catch (...) {
        // Empty string on error.
        local->set("state", Element::create(std::string()));
    }
    std::set<std::string> scopes = query_filter_.getServedScopes();
    ElementPtr list = Element::createList();
    for (std::string scope : scopes) {
        list->add(Element::create(scope));
    }
    local->set("scopes", list);
    ha_servers->set("local", local);

    // Do not include remote server information if this is a backup server or
    // we're in the passive-backup mode.
    if ((config_->getHAMode() == HAConfig::PASSIVE_BACKUP) ||
        (config_->getThisServerConfig()->getRole() == HAConfig::PeerConfig::BACKUP)) {
        return (ha_servers);
    }

    // Remote part
    ElementPtr remote = communication_state_->getReport();

    try {
        role = config_->getFailoverPeerConfig()->getRole();
        std::string role_txt = HAConfig::PeerConfig::roleToString(role);
        remote->set("role", Element::create(role_txt));

    } catch (...) {
        remote->set("role", Element::create(std::string()));
    }
    ha_servers->set("remote", remote);

    return (ha_servers);
}

ConstElementPtr
HAService::processHeartbeat() {
    ElementPtr arguments = Element::createMap();
    std::string state_label = getState(getCurrState())->getLabel();
    arguments->set("state", Element::create(state_label));

    std::string date_time = HttpDateTime().rfc1123Format();
    arguments->set("date-time", Element::create(date_time));

    auto scopes = query_filter_.getServedScopes();
    ElementPtr scopes_list = Element::createList();
    for (auto scope : scopes) {
        scopes_list->add(Element::create(scope));
    }
    arguments->set("scopes", scopes_list);

    arguments->set("unsent-update-count",
                   Element::create(static_cast<int64_t>(communication_state_->getUnsentUpdateCount())));

    return (createAnswer(CONTROL_RESULT_SUCCESS, "HA peer status returned.",
                         arguments));
}

ConstElementPtr
HAService::processHAReset() {
    if (getCurrState() == HA_WAITING_ST) {
        return (createAnswer(CONTROL_RESULT_SUCCESS, "HA state machine already in WAITING state."));
    }
    verboseTransition(HA_WAITING_ST);
    runModel(NOP_EVT);
    return (createAnswer(CONTROL_RESULT_SUCCESS, "HA state machine reset."));
}

void
HAService::asyncSendHeartbeat() {
    HAConfig::PeerConfigPtr partner_config = config_->getFailoverPeerConfig();

    // If the sync_complete_notified_ is true it means that the partner
    // notified us that it had completed lease database synchronization.
    // We confirm that the partner is operational by sending the heartbeat
    // to it. Regardless if the partner responds to our heartbeats or not,
    // we should clear this flag. But, since we need the current value in
    // the async call handler, we save it in the local variable before
    // clearing it.
    bool sync_complete_notified = sync_complete_notified_;
    sync_complete_notified_ = false;

    // Create HTTP/1.1 request including our command.
    PostHttpRequestJsonPtr request = boost::make_shared<PostHttpRequestJson>
        (HttpRequest::Method::HTTP_POST, "/", HttpVersion::HTTP_11(),
         HostHttpHeader(partner_config->getUrl().getStrippedHostname()));
    partner_config->addBasicAuthHttpHeader(request);
    request->setBodyAsJson(CommandCreator::createHeartbeat(server_type_));
    request->finalize();

    // Response object should also be created because the HTTP client needs
    // to know the type of the expected response.
    HttpResponseJsonPtr response = boost::make_shared<HttpResponseJson>();

    // Schedule asynchronous HTTP request.
    client_->asyncSendRequest(partner_config->getUrl(),
                              partner_config->getTlsContext(),
                              request, response,
        [this, partner_config, sync_complete_notified]
            (const boost::system::error_code& ec,
             const HttpResponsePtr& response,
             const std::string& error_str) {

            // There are three possible groups of errors during the heartbeat.
            // One is the IO error causing issues in communication with the peer.
            // Another one is an HTTP parsing error. The last type of error is
            // when non-success error code is returned in the response carried
            // in the HTTP message or if the JSON response is otherwise broken.

            bool heartbeat_success = true;

            // Handle first two groups of errors.
            if (ec || !error_str.empty()) {
                LOG_WARN(ha_logger, HA_HEARTBEAT_COMMUNICATIONS_FAILED)
                    .arg(partner_config->getLogLabel())
                    .arg(ec ? ec.message() : error_str);
                heartbeat_success = false;

            } else {

                // Handle third group of errors.
                try {
                    // Response must contain arguments and the arguments must
                    // be a map.
                    int rcode = 0;
                    ConstElementPtr args = verifyAsyncResponse(response, rcode);
                    if (!args || args->getType() != Element::map) {
                        isc_throw(CtrlChannelError, "returned arguments in the response"
                                  " must be a map");
                    }
                    // Response must include partner's state.
                    ConstElementPtr state = args->get("state");
                    if (!state || state->getType() != Element::string) {
                        isc_throw(CtrlChannelError, "server state not returned in response"
                                  " to a ha-heartbeat command or it is not a string");
                    }
                    // Remember the partner's state. This may throw if the returned
                    // state is invalid.
                    communication_state_->setPartnerState(state->stringValue());

                    ConstElementPtr date_time = args->get("date-time");
                    if (!date_time || date_time->getType() != Element::string) {
                        isc_throw(CtrlChannelError, "date-time not returned in response"
                                  " to a ha-heartbeat command or it is not a string");
                    }
                    // Note the time returned by the partner to calculate the clock skew.
                    communication_state_->setPartnerTime(date_time->stringValue());

                    // Remember the scopes served by the partner.
                    try {
                        auto scopes = args->get("scopes");
                        communication_state_->setPartnerScopes(scopes);

                    } catch (...) {
                        // We don't want to fail if the scopes are missing because
                        // this would be incompatible with old HA hook library
                        // versions. We may make it mandatory one day, but during
                        // upgrades of existing HA setup it would be a real issue
                        // if we failed here.
                    }

                    // unsent-update-count was not present in earlier HA versions.
                    // Let's check if the partner has sent the parameter. We initialized
                    // the counter to 0, and it remains 0 if the partner doesn't send it.
                    // It effectively means that we don't track partner's unsent updates
                    // as in the earlier HA versions.
                    auto unsent_update_count = args->get("unsent-update-count");
                    if (unsent_update_count) {
                        if (unsent_update_count->getType() != Element::integer) {
                            isc_throw(CtrlChannelError, "unsent-update-count returned in"
                                      " the ha-heartbeat response is not an integer");
                        }
                        communication_state_->setPartnerUnsentUpdateCount(static_cast<uint64_t>
                                                                          (unsent_update_count->intValue()));
                    }

                } catch (const std::exception& ex) {
                    LOG_WARN(ha_logger, HA_HEARTBEAT_FAILED)
                        .arg(partner_config->getLogLabel())
                        .arg(ex.what());
                    heartbeat_success = false;
                }
            }

            // If heartbeat was successful, let's mark the connection with the
            // peer as healthy.
            if (heartbeat_success) {
                communication_state_->poke();

            } else {
                // We were unable to retrieve partner's state, so let's mark it
                // as unavailable.
                communication_state_->setPartnerState("unavailable");
                // Log if the communication is interrupted.
                if (communication_state_->isCommunicationInterrupted()) {
                    LOG_WARN(ha_logger, HA_COMMUNICATION_INTERRUPTED)
                        .arg(partner_config->getName());
                }
            }

            startHeartbeat();
            // Even though the partner notified us about the synchronization completion,
            // we still can't communicate with the partner. Let's continue serving
            // the clients until the link is fixed.
            if (sync_complete_notified && !heartbeat_success) {
                postNextEvent(HA_SYNCED_PARTNER_UNAVAILABLE_EVT);
            }
            // Whatever the result of the heartbeat was, the state machine needs
            // to react to this. Let's run the state machine until the state machine
            // finds that some new events are required, i.e. next heartbeat or
            // lease update.  The runModel() may transition to another state, schedule
            // asynchronous tasks etc. Then it returns control to the DHCP server.
            runModel(HA_HEARTBEAT_COMPLETE_EVT);
        },
        HttpClient::RequestTimeout(TIMEOUT_DEFAULT_HTTP_CLIENT_REQUEST),
        std::bind(&HAService::clientConnectHandler, this, ph::_1, ph::_2),
        std::bind(&HAService::clientHandshakeHandler, this, ph::_1),
        std::bind(&HAService::clientCloseHandler, this, ph::_1)
    );
}

void
HAService::scheduleHeartbeat() {
    if (!communication_state_->isHeartbeatRunning()) {
        startHeartbeat();
    }
}

void
HAService::startHeartbeat() {
    if (config_->getHeartbeatDelay() > 0) {
        communication_state_->startHeartbeat(config_->getHeartbeatDelay(),
                                             std::bind(&HAService::asyncSendHeartbeat,
                                                       this));
    }
}

void
HAService::asyncDisableDHCPService(HttpClient& http_client,
                                   const std::string& server_name,
                                   const unsigned int max_period,
                                   PostRequestCallback post_request_action) {
    HAConfig::PeerConfigPtr remote_config = config_->getPeerConfig(server_name);

    // Create HTTP/1.1 request including our command.
    PostHttpRequestJsonPtr request = boost::make_shared<PostHttpRequestJson>
        (HttpRequest::Method::HTTP_POST, "/", HttpVersion::HTTP_11(),
         HostHttpHeader(remote_config->getUrl().getStrippedHostname()));

    remote_config->addBasicAuthHttpHeader(request);
    request->setBodyAsJson(CommandCreator::createDHCPDisable(max_period,
                                                             server_type_));
    request->finalize();

    // Response object should also be created because the HTTP client needs
    // to know the type of the expected response.
    HttpResponseJsonPtr response = boost::make_shared<HttpResponseJson>();

    // Schedule asynchronous HTTP request.
    http_client.asyncSendRequest(remote_config->getUrl(),
                                 remote_config->getTlsContext(),
                                 request, response,
        [this, remote_config, post_request_action]
            (const boost::system::error_code& ec,
             const HttpResponsePtr& response,
             const std::string& error_str) {

             // There are three possible groups of errors during the heartbeat.
             // One is the IO error causing issues in communication with the peer.
             // Another one is an HTTP parsing error. The last type of error is
             // when non-success error code is returned in the response carried
             // in the HTTP message or if the JSON response is otherwise broken.

             int rcode = 0;
             std::string error_message;

             // Handle first two groups of errors.
             if (ec || !error_str.empty()) {
                 error_message = (ec ? ec.message() : error_str);
                 LOG_ERROR(ha_logger, HA_DHCP_DISABLE_COMMUNICATIONS_FAILED)
                     .arg(remote_config->getLogLabel())
                     .arg(error_message);

             } else {

                 // Handle third group of errors.
                 try {
                     static_cast<void>(verifyAsyncResponse(response, rcode));

                 } catch (const std::exception& ex) {
                     error_message = ex.what();
                     LOG_ERROR(ha_logger, HA_DHCP_DISABLE_FAILED)
                         .arg(remote_config->getLogLabel())
                         .arg(error_message);
                 }
             }

             // If there was an error communicating with the partner, mark the
             // partner as unavailable.
             if (!error_message.empty()) {
                 communication_state_->setPartnerState("unavailable");
             }

             // Invoke post request action if it was specified.
             if (post_request_action) {
                 post_request_action(error_message.empty(),
                                     error_message,
                                     rcode);
             }
        },
        HttpClient::RequestTimeout(TIMEOUT_DEFAULT_HTTP_CLIENT_REQUEST),
        std::bind(&HAService::clientConnectHandler, this, ph::_1, ph::_2),
        std::bind(&HAService::clientHandshakeHandler, this, ph::_1),
        std::bind(&HAService::clientCloseHandler, this, ph::_1)
    );
}

void
HAService::asyncEnableDHCPService(HttpClient& http_client,
                                  const std::string& server_name,
                                  PostRequestCallback post_request_action) {
    HAConfig::PeerConfigPtr remote_config = config_->getPeerConfig(server_name);

    // Create HTTP/1.1 request including our command.
    PostHttpRequestJsonPtr request = boost::make_shared<PostHttpRequestJson>
        (HttpRequest::Method::HTTP_POST, "/", HttpVersion::HTTP_11(),
         HostHttpHeader(remote_config->getUrl().getStrippedHostname()));
    remote_config->addBasicAuthHttpHeader(request);
    request->setBodyAsJson(CommandCreator::createDHCPEnable(server_type_));
    request->finalize();

    // Response object should also be created because the HTTP client needs
    // to know the type of the expected response.
    HttpResponseJsonPtr response = boost::make_shared<HttpResponseJson>();

    // Schedule asynchronous HTTP request.
    http_client.asyncSendRequest(remote_config->getUrl(),
                                 remote_config->getTlsContext(),
                                 request, response,
        [this, remote_config, post_request_action]
            (const boost::system::error_code& ec,
             const HttpResponsePtr& response,
             const std::string& error_str) {

             // There are three possible groups of errors during the heartbeat.
             // One is the IO error causing issues in communication with the peer.
             // Another one is an HTTP parsing error. The last type of error is
             // when non-success error code is returned in the response carried
             // in the HTTP message or if the JSON response is otherwise broken.

             int rcode = 0;
             std::string error_message;

             // Handle first two groups of errors.
             if (ec || !error_str.empty()) {
                 error_message = (ec ? ec.message() : error_str);
                 LOG_ERROR(ha_logger, HA_DHCP_ENABLE_COMMUNICATIONS_FAILED)
                     .arg(remote_config->getLogLabel())
                     .arg(error_message);

             } else {

                 // Handle third group of errors.
                 try {
                     static_cast<void>(verifyAsyncResponse(response, rcode));

                 } catch (const std::exception& ex) {
                     error_message = ex.what();
                     LOG_ERROR(ha_logger, HA_DHCP_ENABLE_FAILED)
                         .arg(remote_config->getLogLabel())
                         .arg(error_message);
                 }
             }

             // If there was an error communicating with the partner, mark the
             // partner as unavailable.
             if (!error_message.empty()) {
                 communication_state_->setPartnerState("unavailable");
             }

             // Invoke post request action if it was specified.
             if (post_request_action) {
                 post_request_action(error_message.empty(),
                                     error_message,
                                     rcode);
             }
        },
        HttpClient::RequestTimeout(TIMEOUT_DEFAULT_HTTP_CLIENT_REQUEST),
        std::bind(&HAService::clientConnectHandler, this, ph::_1, ph::_2),
        std::bind(&HAService::clientHandshakeHandler, this, ph::_1),
        std::bind(&HAService::clientCloseHandler, this, ph::_1)
    );
}

void
HAService::localDisableDHCPService() {
    network_state_->disableService(NetworkState::Origin::HA_COMMAND);
}

void
HAService::localEnableDHCPService() {
    network_state_->enableService(NetworkState::Origin::HA_COMMAND);
}

void
HAService::asyncSyncLeases() {
    PostSyncCallback null_action;

    // Timeout is configured in milliseconds. Need to convert to seconds.
    unsigned int dhcp_disable_timeout =
        static_cast<unsigned int>(config_->getSyncTimeout() / 1000);
    if (dhcp_disable_timeout == 0) {
        // Ensure that we always use at least 1 second timeout.
        dhcp_disable_timeout = 1;
    }

    asyncSyncLeases(*client_, config_->getFailoverPeerConfig()->getName(),
                    dhcp_disable_timeout, LeasePtr(), null_action);
}

void
HAService::asyncSyncLeases(http::HttpClient& http_client,
                           const std::string& server_name,
                           const unsigned int max_period,
                           const dhcp::LeasePtr& last_lease,
                           PostSyncCallback post_sync_action,
                           const bool dhcp_disabled) {
    // Synchronization starts with a command to disable DHCP service of the
    // peer from which we're fetching leases. We don't want the other server
    // to allocate new leases while we fetch from it. The DHCP service will
    // be disabled for a certain amount of time and will be automatically
    // re-enabled if we die during the synchronization.
    asyncDisableDHCPService(http_client, server_name, max_period,
                            [this, &http_client, server_name, max_period, last_lease,
                             post_sync_action, dhcp_disabled]
                            (const bool success, const std::string& error_message, const int) {

        // If we have successfully disabled the DHCP service on the peer,
        // we can start fetching the leases.
        if (success) {
            // The last argument indicates that disabling the DHCP
            // service on the partner server was successful.
            asyncSyncLeasesInternal(http_client, server_name, max_period,
                                    last_lease, post_sync_action, true);

        } else {
            post_sync_action(success, error_message, dhcp_disabled);
        }
    });
}

void
HAService::asyncSyncLeasesInternal(http::HttpClient& http_client,
                                   const std::string& server_name,
                                   const unsigned int max_period,
                                   const dhcp::LeasePtr& last_lease,
                                   PostSyncCallback post_sync_action,
                                   const bool dhcp_disabled) {

    HAConfig::PeerConfigPtr partner_config = config_->getFailoverPeerConfig();

    // Create HTTP/1.1 request including our command.
    PostHttpRequestJsonPtr request = boost::make_shared<PostHttpRequestJson>
        (HttpRequest::Method::HTTP_POST, "/", HttpVersion::HTTP_11(),
         HostHttpHeader(partner_config->getUrl().getStrippedHostname()));
    partner_config->addBasicAuthHttpHeader(request);
    if (server_type_ == HAServerType::DHCPv4) {
        request->setBodyAsJson(CommandCreator::createLease4GetPage(
            boost::dynamic_pointer_cast<Lease4>(last_lease), config_->getSyncPageLimit()));

    } else {
        request->setBodyAsJson(CommandCreator::createLease6GetPage(
            boost::dynamic_pointer_cast<Lease6>(last_lease), config_->getSyncPageLimit()));
    }
    request->finalize();

    // Response object should also be created because the HTTP client needs
    // to know the type of the expected response.
    HttpResponseJsonPtr response = boost::make_shared<HttpResponseJson>();

    // Schedule asynchronous HTTP request.
    http_client.asyncSendRequest(partner_config->getUrl(),
                                 partner_config->getTlsContext(),
                                 request, response,
        [this, partner_config, post_sync_action, &http_client, server_name,
         max_period, dhcp_disabled]
            (const boost::system::error_code& ec,
             const HttpResponsePtr& response,
             const std::string& error_str) {

             // Holds last lease received on the page of leases. If the last
             // page was hit, this value remains null.
             LeasePtr last_lease;

            // There are three possible groups of errors during the heartbeat.
            // One is the IO error causing issues in communication with the peer.
            // Another one is an HTTP parsing error. The last type of error is
            // when non-success error code is returned in the response carried
            // in the HTTP message or if the JSON response is otherwise broken.

            std::string error_message;

            // Handle first two groups of errors.
            if (ec || !error_str.empty()) {
                error_message = (ec ? ec.message() : error_str);
                LOG_ERROR(ha_logger, HA_LEASES_SYNC_COMMUNICATIONS_FAILED)
                    .arg(partner_config->getLogLabel())
                    .arg(error_message);

            } else {
                // Handle third group of errors.
                try {
                    int rcode = 0;
                    ConstElementPtr args = verifyAsyncResponse(response, rcode);

                    // Arguments must be a map.
                    if (args && (args->getType() != Element::map)) {
                        isc_throw(CtrlChannelError,
                                  "arguments in the received response must be a map");
                    }

                    ConstElementPtr leases = args->get("leases");
                    if (!leases || (leases->getType() != Element::list)) {
                        isc_throw(CtrlChannelError,
                                  "server response does not contain leases argument or this"
                                  " argument is not a list");
                    }

                    // Iterate over the leases and update the database as appropriate.
                    const auto& leases_element = leases->listValue();

                    LOG_INFO(ha_logger, HA_LEASES_SYNC_LEASE_PAGE_RECEIVED)
                        .arg(leases_element.size())
                        .arg(server_name);

                    for (auto l = leases_element.begin(); l != leases_element.end(); ++l) {
                        try {

                            if (server_type_ == HAServerType::DHCPv4) {
                                Lease4Ptr lease = Lease4::fromElement(*l);

                                // Check if there is such lease in the database already.
                                Lease4Ptr existing_lease = LeaseMgrFactory::instance().getLease4(lease->addr_);
                                if (!existing_lease) {
                                    // There is no such lease, so let's add it.
                                    LeaseMgrFactory::instance().addLease(lease);

                                } else if (existing_lease->cltt_ < lease->cltt_) {
                                    // If the existing lease is older than the fetched lease, update
                                    // the lease in our local database.
                                    // Update lease current expiration time with value received from the
                                    // database. Some database backends reject operations on the lease if
                                    // the current expiration time value does not match what is stored.
                                    Lease::syncCurrentExpirationTime(*existing_lease, *lease);
                                    LeaseMgrFactory::instance().updateLease4(lease);

                                } else {
                                    LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC, HA_LEASE_SYNC_STALE_LEASE4_SKIP)
                                        .arg(lease->addr_.toText())
                                        .arg(lease->subnet_id_);
                                }

                                // If we're not on the last page and we're processing final lease on
                                // this page, let's record the lease as input to the next
                                // lease4-get-page command.
                                if ((leases_element.size() >= config_->getSyncPageLimit()) &&
                                    (l + 1 == leases_element.end())) {
                                    last_lease = boost::dynamic_pointer_cast<Lease>(lease);
                                }

                            } else {
                                Lease6Ptr lease = Lease6::fromElement(*l);

                                // Check if there is such lease in the database already.
                                Lease6Ptr existing_lease = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                                                                 lease->addr_);
                                if (!existing_lease) {
                                    // There is no such lease, so let's add it.
                                    LeaseMgrFactory::instance().addLease(lease);

                                } else if (existing_lease->cltt_ < lease->cltt_) {
                                    // If the existing lease is older than the fetched lease, update
                                    // the lease in our local database.
                                    // Update lease current expiration time with value received from the
                                    // database. Some database backends reject operations on the lease if
                                    // the current expiration time value does not match what is stored.
                                    Lease::syncCurrentExpirationTime(*existing_lease, *lease);
                                    LeaseMgrFactory::instance().updateLease6(lease);

                                } else {
                                    LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC, HA_LEASE_SYNC_STALE_LEASE6_SKIP)
                                        .arg(lease->addr_.toText())
                                        .arg(lease->subnet_id_);
                                }

                                // If we're not on the last page and we're processing final lease on
                                // this page, let's record the lease as input to the next
                                // lease6-get-page command.
                                if ((leases_element.size() >= config_->getSyncPageLimit()) &&
                                    (l + 1 == leases_element.end())) {
                                    last_lease = boost::dynamic_pointer_cast<Lease>(lease);
                                }
                            }

                        } catch (const std::exception& ex) {
                            LOG_WARN(ha_logger, HA_LEASE_SYNC_FAILED)
                                .arg((*l)->str())
                                .arg(ex.what());
                        }
                    }

                } catch (const std::exception& ex) {
                    error_message = ex.what();
                    LOG_ERROR(ha_logger, HA_LEASES_SYNC_FAILED)
                        .arg(partner_config->getLogLabel())
                        .arg(error_message);
                }
            }

             // If there was an error communicating with the partner, mark the
             // partner as unavailable.
             if (!error_message.empty()) {
                 communication_state_->setPartnerState("unavailable");

             } else if (last_lease) {
                 // This indicates that there are more leases to be fetched.
                 // Therefore, we have to send another leaseX-get-page command.
                 asyncSyncLeases(http_client, server_name, max_period, last_lease,
                                 post_sync_action, dhcp_disabled);
                 return;
             }

            // Invoke post synchronization action if it was specified.
            if (post_sync_action) {
                post_sync_action(error_message.empty(),
                                 error_message,
                                 dhcp_disabled);
            }
        },
        HttpClient::RequestTimeout(config_->getSyncTimeout()),
        std::bind(&HAService::clientConnectHandler, this, ph::_1, ph::_2),
        std::bind(&HAService::clientHandshakeHandler, this, ph::_1),
        std::bind(&HAService::clientCloseHandler, this, ph::_1)
    );

}

ConstElementPtr
HAService::processSynchronize(const std::string& server_name,
                              const unsigned int max_period) {
    std::string answer_message;
    int sync_status = synchronize(answer_message, server_name, max_period);
    return (createAnswer(sync_status, answer_message));
}

int
HAService::synchronize(std::string& status_message, const std::string& server_name,
                       const unsigned int max_period) {
    IOService io_service;
    HttpClient client(io_service);

    asyncSyncLeases(client, server_name, max_period, Lease4Ptr(),
                    [&](const bool success, const std::string& error_message,
                        const bool dhcp_disabled) {
        // If there was a fatal error while fetching the leases, let's
        // log an error message so as it can be included in the response
        // to the controlling client.
        if (!success) {
            status_message = error_message;
        }

        // Whether or not there was an error while fetching the leases,
        // we need to re-enable the DHCP service on the peer if the
        // DHCP service was disabled in the course of synchronization.
        if (dhcp_disabled) {
            // If the synchronization was completed successfully let's
            // try to send the ha-sync-complete-notify command to the
            // partner.
            if (success) {
                asyncSyncCompleteNotify(client, server_name,
                                        [&](const bool success,
                                            const std::string& error_message,
                                            const int rcode) {
                    // This command may not be supported by the partner when it
                    // runs an older Kea version. In that case, send the dhcp-enable
                    // command as in previous Kea version.
                    if (rcode == CONTROL_RESULT_COMMAND_UNSUPPORTED) {
                        asyncEnableDHCPService(client, server_name,
                                               [&](const bool success,
                                                   const std::string& error_message,
                                                   const int) {
                            // It is possible that we have already recorded an error
                            // message while synchronizing the lease database. Don't
                            // override the existing error message.
                            if (!success && status_message.empty()) {
                                status_message = error_message;
                            }

                            // The synchronization process is completed, so let's break
                            // the IO service so as we can return the response to the
                            // controlling client.
                            io_service.stop();
                        });

                    } else {
                        // ha-sync-complete-notify command was delivered to the partner.
                        // The synchronization process ends here.
                        if (!success && status_message.empty()) {
                            status_message = error_message;
                        }

                        io_service.stop();
                    }
                });

            } else {
                // Synchronization was unsuccessful. Send the dhcp-enable command to
                //  re-enable the DHCP service. Note, that we don't send the
                // ha-sync-complete-notify command in this case. It is only sent in
                // the case when synchronization ends successfully.
                asyncEnableDHCPService(client, server_name,
                                       [&](const bool success,
                                           const std::string& error_message,
                                           const int) {
                    if (!success && status_message.empty()) {
                        status_message = error_message;
                    }

                    // The synchronization process is completed, so let's break
                    // the IO service so as we can return the response to the
                    // controlling client.
                    io_service.stop();

                });
            }

        } else {
            // Also stop IO service if there is no need to enable DHCP
            // service.
            io_service.stop();
        }
    });

    LOG_INFO(ha_logger, HA_SYNC_START).arg(server_name);

    // Measure duration of the synchronization.
    Stopwatch stopwatch;

    // Run the IO service until it is stopped by any of the callbacks. This
    // makes it synchronous.
    io_service.run();

    // End measuring duration.
    stopwatch.stop();

    // If an error message has been recorded, return an error to the controlling
    // client.
    if (!status_message.empty()) {
        postNextEvent(HA_SYNCING_FAILED_EVT);

        LOG_ERROR(ha_logger, HA_SYNC_FAILED)
            .arg(server_name)
            .arg(status_message);

        return (CONTROL_RESULT_ERROR);

    }

    // Everything was fine, so let's return a success.
    status_message = "Lease database synchronization complete.";
    postNextEvent(HA_SYNCING_SUCCEEDED_EVT);

    LOG_INFO(ha_logger, HA_SYNC_SUCCESSFUL)
        .arg(server_name)
        .arg(stopwatch.logFormatLastDuration());

    return (CONTROL_RESULT_SUCCESS);
}

void
HAService::asyncSendLeaseUpdatesFromBacklog(HttpClient& http_client,
                                            const HAConfig::PeerConfigPtr& config,
                                            PostRequestCallback post_request_action) {
    if (lease_update_backlog_.size() == 0) {
        post_request_action(true, "", CONTROL_RESULT_SUCCESS);
        return;
    }

    ConstElementPtr command;
    if (server_type_ == HAServerType::DHCPv4) {
        LeaseUpdateBacklog::OpType op_type;
        Lease4Ptr lease = boost::dynamic_pointer_cast<Lease4>(lease_update_backlog_.pop(op_type));
        if (op_type == LeaseUpdateBacklog::ADD) {
            command = CommandCreator::createLease4Update(*lease);
        } else {
            command = CommandCreator::createLease4Delete(*lease);
        }

    } else {
        command = CommandCreator::createLease6BulkApply(lease_update_backlog_);
    }

    // Create HTTP/1.1 request including our command.
    PostHttpRequestJsonPtr request = boost::make_shared<PostHttpRequestJson>
        (HttpRequest::Method::HTTP_POST, "/", HttpVersion::HTTP_11(),
         HostHttpHeader(config->getUrl().getStrippedHostname()));
    config->addBasicAuthHttpHeader(request);
    request->setBodyAsJson(command);
    request->finalize();

    // Response object should also be created because the HTTP client needs
    // to know the type of the expected response.
    HttpResponseJsonPtr response = boost::make_shared<HttpResponseJson>();

    http_client.asyncSendRequest(config->getUrl(), config->getTlsContext(),
                                 request, response,
        [this, &http_client, config, post_request_action]
            (const boost::system::error_code& ec,
             const HttpResponsePtr& response,
             const std::string& error_str) {

             int rcode = 0;
             std::string error_message;

             if (ec || !error_str.empty()) {
                 error_message = (ec ? ec.message() : error_str);
                 LOG_WARN(ha_logger, HA_LEASES_BACKLOG_COMMUNICATIONS_FAILED)
                     .arg(config->getLogLabel())
                     .arg(ec ? ec.message() : error_str);

             } else {
                 // Handle third group of errors.
                 try {
                    auto args = verifyAsyncResponse(response, rcode);
                 } catch (const std::exception& ex) {
                     error_message = ex.what();
                     LOG_WARN(ha_logger, HA_LEASES_BACKLOG_FAILED)
                         .arg(config->getLogLabel())
                         .arg(ex.what());
                 }
             }

             // Recursively send all outstanding lease updates or break when an
             // error occurs. In DHCPv6, this is a single iteration because we use
             // lease6-bulk-apply, which combines many lease updates in a single
             // transaction. In the case of DHCPv4, each update is sent in its own
             // transaction.
             if (error_message.empty()) {
                 asyncSendLeaseUpdatesFromBacklog(http_client, config, post_request_action);
             } else {
                 post_request_action(error_message.empty(), error_message, rcode);
             }
   });
}

bool
HAService::sendLeaseUpdatesFromBacklog() {
    auto num_updates = lease_update_backlog_.size();
    if (num_updates == 0) {
        LOG_INFO(ha_logger, HA_LEASES_BACKLOG_NOTHING_TO_SEND);
        return (true);
    }

    IOService io_service;
    HttpClient client(io_service);
    auto remote_config = config_->getFailoverPeerConfig();
    bool updates_successful = true;

    LOG_INFO(ha_logger, HA_LEASES_BACKLOG_START)
        .arg(num_updates)
        .arg(remote_config->getName());

    asyncSendLeaseUpdatesFromBacklog(client, remote_config,
                                     [&](const bool success, const std::string&, const int) {
        io_service.stop();
        updates_successful = success;
    });

    // Measure duration of the updates.
    Stopwatch stopwatch;

    // Run the IO service until it is stopped by the callback. This makes it synchronous.
    io_service.run();

    // End measuring duration.
    stopwatch.stop();

    if (updates_successful) {
        LOG_INFO(ha_logger, HA_LEASES_BACKLOG_SUCCESS)
            .arg(remote_config->getName())
            .arg(stopwatch.logFormatLastDuration());
    }

    return (updates_successful);
}

void
HAService::asyncSendHAReset(HttpClient& http_client,
                            const HAConfig::PeerConfigPtr& config,
                            PostRequestCallback post_request_action) {
    ConstElementPtr command = CommandCreator::createHAReset(server_type_);

    // Create HTTP/1.1 request including our command.
    PostHttpRequestJsonPtr request = boost::make_shared<PostHttpRequestJson>
        (HttpRequest::Method::HTTP_POST, "/", HttpVersion::HTTP_11(),
         HostHttpHeader(config->getUrl().getStrippedHostname()));
    config->addBasicAuthHttpHeader(request);
    request->setBodyAsJson(command);
    request->finalize();

    // Response object should also be created because the HTTP client needs
    // to know the type of the expected response.
    HttpResponseJsonPtr response = boost::make_shared<HttpResponseJson>();

    http_client.asyncSendRequest(config->getUrl(), config->getTlsContext(),
                                 request, response,
        [this, config, post_request_action]
            (const boost::system::error_code& ec,
             const HttpResponsePtr& response,
             const std::string& error_str) {

             int rcode = 0;
             std::string error_message;

             if (ec || !error_str.empty()) {
                 error_message = (ec ? ec.message() : error_str);
                 LOG_WARN(ha_logger, HA_RESET_COMMUNICATIONS_FAILED)
                     .arg(config->getLogLabel())
                     .arg(ec ? ec.message() : error_str);

             } else {
                 // Handle third group of errors.
                 try {
                    auto args = verifyAsyncResponse(response, rcode);
                 } catch (const std::exception& ex) {
                     error_message = ex.what();
                     LOG_WARN(ha_logger, HA_RESET_FAILED)
                         .arg(config->getLogLabel())
                         .arg(ex.what());
                 }
             }

             post_request_action(error_message.empty(), error_message, rcode);
   });
}

bool
HAService::sendHAReset() {
    IOService io_service;
    HttpClient client(io_service);
    auto remote_config = config_->getFailoverPeerConfig();
    bool reset_successful = true;

    asyncSendHAReset(client, remote_config,
                     [&](const bool success, const std::string&, const int) {
        io_service.stop();
        reset_successful = success;
    });

    // Run the IO service until it is stopped by the callback. This makes it synchronous.
    io_service.run();

    return (reset_successful);
}

ConstElementPtr
HAService::processScopes(const std::vector<std::string>& scopes) {
    try {
        query_filter_.serveScopes(scopes);
        adjustNetworkState();

    } catch (const std::exception& ex) {
        return (createAnswer(CONTROL_RESULT_ERROR, ex.what()));
    }

    return (createAnswer(CONTROL_RESULT_SUCCESS, "New HA scopes configured."));
}

ConstElementPtr
HAService::processContinue() {
    if (unpause()) {
        return (createAnswer(CONTROL_RESULT_SUCCESS, "HA state machine continues."));
    }
    return (createAnswer(CONTROL_RESULT_SUCCESS, "HA state machine is not paused."));
}

ConstElementPtr
HAService::processMaintenanceNotify(const bool cancel) {
    if (cancel) {
        if (getCurrState() != HA_IN_MAINTENANCE_ST) {
            return (createAnswer(CONTROL_RESULT_ERROR, "Unable to cancel the"
                                 " maintenance for the server not in the"
                                 " in-maintenance state."));
        }

        postNextEvent(HA_MAINTENANCE_CANCEL_EVT);
        verboseTransition(getPrevState());
        runModel(NOP_EVT);
        return (createAnswer(CONTROL_RESULT_SUCCESS, "Server maintenance canceled."));
    }

    switch (getCurrState()) {
    case HA_BACKUP_ST:
    case HA_PARTNER_IN_MAINTENANCE_ST:
    case HA_TERMINATED_ST:
        // The reason why we don't return an error result here is that we have to
        // have a way to distinguish between the errors caused by the communication
        // issues and the cases when there is no communication error but the server
        // is not allowed to enter the in-maintenance state. In the former case, the
        // partner would go to partner-down. In the case signaled by the special
        // result code entering the maintenance state is not allowed.
        return (createAnswer(HA_CONTROL_RESULT_MAINTENANCE_NOT_ALLOWED,
                             "Unable to transition the server from the "
                             + stateToString(getCurrState()) + " to"
                             " in-maintenance state."));
    default:
        verboseTransition(HA_IN_MAINTENANCE_ST);
        runModel(HA_MAINTENANCE_NOTIFY_EVT);
    }
    return (createAnswer(CONTROL_RESULT_SUCCESS, "Server is in-maintenance state."));
}

ConstElementPtr
HAService::processMaintenanceStart() {
    switch (getCurrState()) {
    case HA_BACKUP_ST:
    case HA_IN_MAINTENANCE_ST:
    case HA_PARTNER_IN_MAINTENANCE_ST:
    case HA_TERMINATED_ST:
        return (createAnswer(CONTROL_RESULT_ERROR, "Unable to transition the server from"
                             " the " + stateToString(getCurrState()) + " to"
                             " partner-in-maintenance state."));
    default:
        ;
    }

    HAConfig::PeerConfigPtr remote_config = config_->getFailoverPeerConfig();

    // Create HTTP/1.1 request including ha-maintenance-notify command
    // with the cancel flag set to false.
    PostHttpRequestJsonPtr request = boost::make_shared<PostHttpRequestJson>
        (HttpRequest::Method::HTTP_POST, "/", HttpVersion::HTTP_11(),
         HostHttpHeader(remote_config->getUrl().getStrippedHostname()));
    remote_config->addBasicAuthHttpHeader(request);
    request->setBodyAsJson(CommandCreator::createMaintenanceNotify(false, server_type_));
    request->finalize();

    // Response object should also be created because the HTTP client needs
    // to know the type of the expected response.
    HttpResponseJsonPtr response = boost::make_shared<HttpResponseJson>();

    IOService io_service;
    HttpClient client(io_service);

    boost::system::error_code captured_ec;
    std::string captured_error_message;
    int captured_rcode = 0;

    // Schedule asynchronous HTTP request.
    client.asyncSendRequest(remote_config->getUrl(),
                            remote_config->getTlsContext(),
                            request, response,
        [this, remote_config, &io_service, &captured_ec, &captured_error_message,
         &captured_rcode]
            (const boost::system::error_code& ec,
             const HttpResponsePtr& response,
             const std::string& error_str) {

             io_service.stop();

             // There are three possible groups of errors. One is the IO error
             // causing issues in communication with the peer. Another one is
             // an HTTP parsing error. The last type of error is when non-success
             // error code is returned in the response carried in the HTTP message
             // or if the JSON response is otherwise broken.

             std::string error_message;

             // Handle first two groups of errors.
             if (ec || !error_str.empty()) {
                 error_message = (ec ? ec.message() : error_str);
                 LOG_ERROR(ha_logger, HA_MAINTENANCE_NOTIFY_COMMUNICATIONS_FAILED)
                     .arg(remote_config->getLogLabel())
                     .arg(error_message);

             } else {

                 // Handle third group of errors.
                 try {
                     static_cast<void>(verifyAsyncResponse(response, captured_rcode));

                 } catch (const std::exception& ex) {
                     error_message = ex.what();
                     LOG_ERROR(ha_logger, HA_MAINTENANCE_NOTIFY_FAILED)
                         .arg(remote_config->getLogLabel())
                         .arg(error_message);
                 }
             }

             // If there was an error communicating with the partner, mark the
             // partner as unavailable.
             if (!error_message.empty()) {
                 communication_state_->setPartnerState("unavailable");
             }

             captured_ec = ec;
             captured_error_message = error_message;
        },
        HttpClient::RequestTimeout(TIMEOUT_DEFAULT_HTTP_CLIENT_REQUEST),
        std::bind(&HAService::clientConnectHandler, this, ph::_1, ph::_2),
        std::bind(&HAService::clientHandshakeHandler, this, ph::_1),
        std::bind(&HAService::clientCloseHandler, this, ph::_1)
    );

    // Run the IO service until it is stopped by any of the callbacks. This
    // makes it synchronous.
    io_service.run();

    // If there was a communication problem with the partner we assume that
    // the partner is already down while we receive this command.
    if (captured_ec || (captured_rcode == CONTROL_RESULT_ERROR)) {
        postNextEvent(HA_MAINTENANCE_START_EVT);
        verboseTransition(HA_PARTNER_DOWN_ST);
        runModel(NOP_EVT);
        return (createAnswer(CONTROL_RESULT_SUCCESS,
                             "Server is now in the partner-down state as its"
                             " partner appears to be offline for maintenance."));

    } else if (captured_rcode == CONTROL_RESULT_SUCCESS) {
        // If the partner responded indicating no error it means that the
        // partner has been transitioned to the in-maintenance state. In that
        // case we transition to the partner-in-maintenance state.
        postNextEvent(HA_MAINTENANCE_START_EVT);
        verboseTransition(HA_PARTNER_IN_MAINTENANCE_ST);
        runModel(NOP_EVT);

    } else {
        // Partner server returned a special status code which means that it can't
        // transition to the partner-in-maintenance state.
        return (createAnswer(CONTROL_RESULT_ERROR, "Unable to transition to the"
                             " partner-in-maintenance state. The partner server responded"
                             " with the following message to the ha-maintenance-notify"
                             " command: " + captured_error_message + "."));

    }

    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "Server is now in the partner-in-maintenance state"
                         " and its partner is in-maintenance state. The partner"
                         " can be now safely shut down."));
}

ConstElementPtr
HAService::processMaintenanceCancel() {
    if (getCurrState() != HA_PARTNER_IN_MAINTENANCE_ST) {
        return (createAnswer(CONTROL_RESULT_ERROR, "Unable to cancel maintenance"
                             " request because the server is not in the"
                             " partner-in-maintenance state."));
    }

    HAConfig::PeerConfigPtr remote_config = config_->getFailoverPeerConfig();

    // Create HTTP/1.1 request including ha-maintenance-notify command
    // with the cancel flag set to true.
    PostHttpRequestJsonPtr request = boost::make_shared<PostHttpRequestJson>
        (HttpRequest::Method::HTTP_POST, "/", HttpVersion::HTTP_11(),
         HostHttpHeader(remote_config->getUrl().getStrippedHostname()));
    remote_config->addBasicAuthHttpHeader(request);
    request->setBodyAsJson(CommandCreator::createMaintenanceNotify(true, server_type_));
    request->finalize();

    // Response object should also be created because the HTTP client needs
    // to know the type of the expected response.
    HttpResponseJsonPtr response = boost::make_shared<HttpResponseJson>();

    IOService io_service;
    HttpClient client(io_service);

    std::string error_message;

    // Schedule asynchronous HTTP request.
    client.asyncSendRequest(remote_config->getUrl(),
                            remote_config->getTlsContext(),
                            request, response,
        [this, remote_config, &io_service, &error_message]
            (const boost::system::error_code& ec,
             const HttpResponsePtr& response,
             const std::string& error_str) {

             io_service.stop();

             // Handle first two groups of errors.
             if (ec || !error_str.empty()) {
                 error_message = (ec ? ec.message() : error_str);
                 LOG_ERROR(ha_logger, HA_MAINTENANCE_NOTIFY_CANCEL_COMMUNICATIONS_FAILED)
                     .arg(remote_config->getLogLabel())
                     .arg(error_message);

             } else {

                 // Handle third group of errors.
                 try {
                     int rcode = 0;
                     static_cast<void>(verifyAsyncResponse(response, rcode));

                 } catch (const std::exception& ex) {
                     error_message = ex.what();
                     LOG_ERROR(ha_logger, HA_MAINTENANCE_NOTIFY_CANCEL_FAILED)
                         .arg(remote_config->getLogLabel())
                         .arg(error_message);
                 }
             }

             // If there was an error communicating with the partner, mark the
             // partner as unavailable.
             if (!error_message.empty()) {
                 communication_state_->setPartnerState("unavailable");
             }
        },
        HttpClient::RequestTimeout(TIMEOUT_DEFAULT_HTTP_CLIENT_REQUEST),
        std::bind(&HAService::clientConnectHandler, this, ph::_1, ph::_2),
        std::bind(&HAService::clientHandshakeHandler, this, ph::_1),
        std::bind(&HAService::clientCloseHandler, this, ph::_1)
    );

    // Run the IO service until it is stopped by any of the callbacks. This
    // makes it synchronous.
    io_service.run();

    // There was an error in communication with the partner or the
    // partner was unable to revert its state.
    if (!error_message.empty()) {
        return (createAnswer(CONTROL_RESULT_ERROR,
                             "Unable to cancel maintenance. The partner server responded"
                             " with the following message to the ha-maintenance-notify"
                             " command: " + error_message + "."));
    }

    // Successfully reverted partner's state. Let's also revert our state to the
    // previous one.
    postNextEvent(HA_MAINTENANCE_CANCEL_EVT);
    verboseTransition(getPrevState());
    runModel(NOP_EVT);

    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "Server maintenance successfully canceled."));
}

void
HAService::asyncSyncCompleteNotify(HttpClient& http_client,
                                   const std::string& server_name,
                                   PostRequestCallback post_request_action) {
    HAConfig::PeerConfigPtr remote_config = config_->getPeerConfig(server_name);

    // Create HTTP/1.1 request including our command.
    PostHttpRequestJsonPtr request = boost::make_shared<PostHttpRequestJson>
        (HttpRequest::Method::HTTP_POST, "/", HttpVersion::HTTP_11(),
         HostHttpHeader(remote_config->getUrl().getStrippedHostname()));

    remote_config->addBasicAuthHttpHeader(request);
    request->setBodyAsJson(CommandCreator::createSyncCompleteNotify(server_type_));
    request->finalize();

    // Response object should also be created because the HTTP client needs
    // to know the type of the expected response.
    HttpResponseJsonPtr response = boost::make_shared<HttpResponseJson>();

    // Schedule asynchronous HTTP request.
    http_client.asyncSendRequest(remote_config->getUrl(),
                                 remote_config->getTlsContext(),
                                 request, response,
        [this, remote_config, post_request_action]
            (const boost::system::error_code& ec,
             const HttpResponsePtr& response,
             const std::string& error_str) {

             // There are three possible groups of errors. One is the IO error
             // causing issues in communication with the peer. Another one is an
             // HTTP parsing error. The last type of error is when non-success
             // error code is returned in the response carried in the HTTP message
             // or if the JSON response is otherwise broken.

             int rcode = 0;
             std::string error_message;

             // Handle first two groups of errors.
             if (ec || !error_str.empty()) {
                 error_message = (ec ? ec.message() : error_str);
                 LOG_ERROR(ha_logger, HA_SYNC_COMPLETE_NOTIFY_COMMUNICATIONS_FAILED)
                     .arg(remote_config->getLogLabel())
                     .arg(error_message);

             } else {

                 // Handle third group of errors.
                 try {
                     static_cast<void>(verifyAsyncResponse(response, rcode));

                 } catch (const CommandUnsupportedError& ex) {
                     rcode = CONTROL_RESULT_COMMAND_UNSUPPORTED;

                 } catch (const std::exception& ex) {
                     error_message = ex.what();
                     LOG_ERROR(ha_logger, HA_SYNC_COMPLETE_NOTIFY_FAILED)
                         .arg(remote_config->getLogLabel())
                         .arg(error_message);
                 }
             }

             // If there was an error communicating with the partner, mark the
             // partner as unavailable.
             if (!error_message.empty()) {
                 communication_state_->setPartnerState("unavailable");
             }

             // Invoke post request action if it was specified.
             if (post_request_action) {
                 post_request_action(error_message.empty(),
                                     error_message,
                                     rcode);
             }
        },
        HttpClient::RequestTimeout(TIMEOUT_DEFAULT_HTTP_CLIENT_REQUEST),
        std::bind(&HAService::clientConnectHandler, this, ph::_1, ph::_2),
        std::bind(&HAService::clientHandshakeHandler, this, ph::_1),
        std::bind(&HAService::clientCloseHandler, this, ph::_1)
    );
}

ConstElementPtr
HAService::processSyncCompleteNotify() {
    if (getCurrState() == HA_PARTNER_DOWN_ST) {
        sync_complete_notified_ = true;
    } else {
        localEnableDHCPService();
    }
    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "Server successfully notified about the synchronization completion."));
}

ConstElementPtr
HAService::verifyAsyncResponse(const HttpResponsePtr& response, int& rcode) {
    // Set the return code to error in case of early throw.
    rcode = CONTROL_RESULT_ERROR;
    // The response must cast to JSON type.
    HttpResponseJsonPtr json_response =
        boost::dynamic_pointer_cast<HttpResponseJson>(response);
    if (!json_response) {
        isc_throw(CtrlChannelError, "no valid HTTP response found");
    }

    // Body holds the response to our command.
    ConstElementPtr body = json_response->getBodyAsJson();
    if (!body) {
        isc_throw(CtrlChannelError, "no body found in the response");
    }

    // Body should contain a list of responses from multiple servers.
    if (body->getType() != Element::list) {
        // Some control agent errors are returned as a map.
        if (body->getType() == Element::map) {
            ElementPtr list = Element::createList();
            ElementPtr answer = Element::createMap();
            answer->set(CONTROL_RESULT, Element::create(rcode));
            ConstElementPtr text = body->get(CONTROL_TEXT);
            if (text) {
                answer->set(CONTROL_TEXT, text);
            }
            list->add(answer);
            body = list;
        } else {
            isc_throw(CtrlChannelError, "body of the response must be a list");
        }
    }

    // There must be at least one response.
    if (body->empty()) {
        isc_throw(CtrlChannelError, "list of responses must not be empty");
    }

    // Check if the status code of the first response. We don't support multiple
    // at this time, because we always send a request to a single location.
    ConstElementPtr args = parseAnswer(rcode, body->get(0));
    if ((rcode != CONTROL_RESULT_SUCCESS) &&
        (rcode != CONTROL_RESULT_EMPTY)) {
        std::ostringstream s;
        // Include an error text if available.
        if (args && args->getType() == Element::string) {
            s << args->stringValue() << ", ";
        }
        // Include an error code.
        s << "error code " << rcode;

        if (rcode == CONTROL_RESULT_COMMAND_UNSUPPORTED) {
            isc_throw(CommandUnsupportedError, s.str());
        } else {
            isc_throw(CtrlChannelError, s.str());
        }
    }

    return (args);
}

bool
HAService::clientConnectHandler(const boost::system::error_code& ec, int tcp_native_fd) {

    // If client is running it's own IOService we do NOT want to
    // register the socket with IfaceMgr.
    if (client_->getThreadIOService()) {
        return (true);
    }

    // If things look OK register the socket with Interface Manager. Note
    // we don't register if the FD is < 0 to avoid an exception throw.
    // It is unlikely that this will occur but we want to be liberal
    // and avoid issues.
    if ((!ec || (ec.value() == boost::asio::error::in_progress))
        && (tcp_native_fd >= 0)) {
        // External socket callback is a NOP. Ready events handlers are
        // run by an explicit call IOService ready in kea-dhcp<n> code.
        // We are registering the socket only to interrupt main-thread
        // select().
        IfaceMgr::instance().addExternalSocket(tcp_native_fd,
            std::bind(&HAService::socketReadyHandler, this, ph::_1)
        );
    }

    // If ec.value() == boost::asio::error::already_connected, we should already
    // be registered, so nothing to do.  If it is any other value, then connect
    // failed and Connection logic should handle that, not us, so no matter
    // what happens we're returning true.
    return (true);
}

void
HAService::socketReadyHandler(int tcp_native_fd) {
    // If the socket is ready but does not belong to one of our client's
    // ongoing transactions, we close it.  This will unregister it from
    // IfaceMgr and ensure the client starts over with a fresh connection
    // if it needs to do so.
    client_->closeIfOutOfBand(tcp_native_fd);
}

void
HAService::clientCloseHandler(int tcp_native_fd) {
    if (tcp_native_fd >= 0) {
        IfaceMgr::instance().deleteExternalSocket(tcp_native_fd);
    }
};

size_t
HAService::pendingRequestSize() {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(mutex_);
        return (pending_requests_.size());
    } else {
        return (pending_requests_.size());
    }
}

template<typename QueryPtrType>
int
HAService::getPendingRequest(const QueryPtrType& query) {
    if (MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(mutex_);
        return (getPendingRequestInternal(query));
    } else {
        return (getPendingRequestInternal(query));
    }
}

template<typename QueryPtrType>
int
HAService::getPendingRequestInternal(const QueryPtrType& query) {
    if (pending_requests_.count(query) == 0) {
        return (0);
    } else {
        return (pending_requests_[query]);
    }
}

void
HAService::checkPermissionsClientAndListener() {
    // Since this function is used as CS callback all exceptions must be
    // suppressed (except the @ref MultiThreadingInvalidOperation), unlikely
    // though they may be.
    // The @ref MultiThreadingInvalidOperation is propagated to the scope of the
    // @ref MultiThreadingCriticalSection constructor.
    try {
        if (client_) {
            client_->checkPermissions();
        }

        if (listener_) {
            listener_->checkPermissions();
        }
    } catch (const isc::MultiThreadingInvalidOperation& ex) {
        LOG_ERROR(ha_logger, HA_PAUSE_CLIENT_LISTENER_ILLEGAL)
                  .arg(ex.what());
        // The exception needs to be propagated to the caller of the
        // @ref MultiThreadingCriticalSection constructor.
        throw;
    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_PAUSE_CLIENT_LISTENER_FAILED)
                  .arg(ex.what());
    }
}

void
HAService::startClientAndListener() {
    // Add critical section callbacks.
    MultiThreadingMgr::instance().addCriticalSectionCallbacks("HA_MT",
        std::bind(&HAService::checkPermissionsClientAndListener, this),
        std::bind(&HAService::pauseClientAndListener, this),
        std::bind(&HAService::resumeClientAndListener, this));

    if (client_) {
        client_->start();
    }

    if (listener_) {
        listener_->start();
    }
}

void
HAService::pauseClientAndListener() {
    // Since this function is used as CS callback all exceptions must be
    // suppressed, unlikely though they may be.
    try {
        if (client_) {
            client_->pause();
        }

        if (listener_) {
            listener_->pause();
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_PAUSE_CLIENT_LISTENER_FAILED)
                  .arg(ex.what());
    }
}

void
HAService::resumeClientAndListener() {
    // Since this function is used as CS callback all exceptions must be
    // suppressed, unlikely though they may be.
    try {
        if (client_) {
            client_->resume();
        }

        if (listener_) {
            listener_->resume();
        }
    } catch (std::exception& ex) {
        LOG_ERROR(ha_logger, HA_RESUME_CLIENT_LISTENER_FAILED)
                  .arg(ex.what());
    }
}

void
HAService::stopClientAndListener() {
    // Remove critical section callbacks.
    MultiThreadingMgr::instance().removeCriticalSectionCallbacks("HA_MT");

    if (client_) {
        client_->stop();
    }

    if (listener_) {
        listener_->stop();
    }
}

// Explicit instantiations.
template int HAService::getPendingRequest(const Pkt4Ptr&);
template int HAService::getPendingRequest(const Pkt6Ptr&);

} // end of namespace isc::ha
} // end of namespace isc
