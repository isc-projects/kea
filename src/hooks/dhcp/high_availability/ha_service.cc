// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <http/date_time.h>
#include <http/response_json.h>
#include <http/post_request_json.h>
#include <util/stopwatch.h>
#include <boost/pointer_cast.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <boost/weak_ptr.hpp>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::http;
using namespace isc::log;
using namespace isc::util;

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

HAService::HAService(const IOServicePtr& io_service, const NetworkStatePtr& network_state,
                     const HAConfigPtr& config, const HAServerType& server_type)
    : io_service_(io_service), network_state_(network_state), config_(config),
      server_type_(server_type), client_(*io_service), communication_state_(),
      query_filter_(config), pending_requests_() {

    if (server_type == HAServerType::DHCPv4) {
        communication_state_.reset(new CommunicationState4(io_service_, config));

    } else {
        communication_state_.reset(new CommunicationState6(io_service_, config));
    }

    startModel(HA_WAITING_ST);

    LOG_INFO(ha_logger, HA_SERVICE_STARTED)
        .arg(HAConfig::HAModeToString(config->getHAMode()))
        .arg(HAConfig::PeerConfig::roleToString(config->getThisServerConfig()->getRole()));
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
}

void
HAService::defineStates() {
    StateModel::defineStates();

    defineState(HA_BACKUP_ST, stateToString(HA_BACKUP_ST),
                boost::bind(&HAService::backupStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_BACKUP_ST)->getPausing());

    defineState(HA_HOT_STANDBY_ST, stateToString(HA_HOT_STANDBY_ST),
                boost::bind(&HAService::normalStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_HOT_STANDBY_ST)->getPausing());

    defineState(HA_LOAD_BALANCING_ST, stateToString(HA_LOAD_BALANCING_ST),
                boost::bind(&HAService::normalStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_LOAD_BALANCING_ST)->getPausing());

    defineState(HA_IN_MAINTENANCE_ST, stateToString(HA_IN_MAINTENANCE_ST),
                boost::bind(&HAService::inMaintenanceStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_IN_MAINTENANCE_ST)->getPausing());

    defineState(HA_PARTNER_DOWN_ST, stateToString(HA_PARTNER_DOWN_ST),
                boost::bind(&HAService::partnerDownStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_PARTNER_DOWN_ST)->getPausing());

    defineState(HA_PARTNER_IN_MAINTENANCE_ST, stateToString(HA_PARTNER_IN_MAINTENANCE_ST),
                boost::bind(&HAService::partnerInMaintenanceStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_PARTNER_IN_MAINTENANCE_ST)->getPausing());

    defineState(HA_READY_ST, stateToString(HA_READY_ST),
                boost::bind(&HAService::readyStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_READY_ST)->getPausing());

    defineState(HA_SYNCING_ST, stateToString(HA_SYNCING_ST),
                boost::bind(&HAService::syncingStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_SYNCING_ST)->getPausing());

    defineState(HA_TERMINATED_ST, stateToString(HA_TERMINATED_ST),
                boost::bind(&HAService::terminatedStateHandler, this),
                config_->getStateMachineConfig()->getStateConfig(HA_TERMINATED_ST)->getPausing());

    defineState(HA_WAITING_ST, stateToString(HA_WAITING_ST),
                boost::bind(&HAService::waitingStateHandler, this),
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

    default:
        postNextEvent(NOP_EVT);
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

    switch (communication_state_->getPartnerState()) {
    case HA_HOT_STANDBY_ST:
    case HA_LOAD_BALANCING_ST:
    case HA_PARTNER_DOWN_ST:
    case HA_PARTNER_IN_MAINTENANCE_ST:
        verboseTransition(HA_WAITING_ST);
        break;

    case HA_READY_ST:
        verboseTransition((config_->getHAMode() == HAConfig::LOAD_BALANCING ?
                    HA_LOAD_BALANCING_ST : HA_HOT_STANDBY_ST));
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

    default:
        postNextEvent(NOP_EVT);
    }
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

    switch (communication_state_->getPartnerState()) {
    case HA_HOT_STANDBY_ST:
        verboseTransition(HA_HOT_STANDBY_ST);
        break;

    case HA_LOAD_BALANCING_ST:
        verboseTransition(HA_LOAD_BALANCING_ST);
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
    if (config_->getThisServerConfig()->getRole() != HAConfig::PeerConfig::BACKUP) {
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

    // Check if the clock skew is still acceptable. If not, transition to
    // the terminated state.
    if (shouldTerminate()) {
        verboseTransition(HA_TERMINATED_ST);
        return;
    }

    switch (communication_state_->getPartnerState()) {
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
        verboseTransition(HA_TERMINATED_ST);
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
    auto partner_state = communication_state_->getPartnerState();

    // Get current and new state name.
    std::string current_state_name = getStateLabel(getCurrState());
    std::string new_state_name = getStateLabel(state);
    std::string partner_state_name = getStateLabel(partner_state);

    // Turn them to upper case so as they are better visible in the logs.
    boost::to_upper(current_state_name);
    boost::to_upper(new_state_name);
    boost::to_upper(partner_state_name);

    // Log the transition.
    LOG_INFO(ha_logger, HA_STATE_TRANSITION)
        .arg(current_state_name)
        .arg(new_state_name)
        .arg(partner_state_name);

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
    if (config_->getThisServerConfig()->getRole() != HAConfig::PeerConfig::BACKUP) {
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
    const bool should_enable = ((getCurrState() == HA_LOAD_BALANCING_ST) ||
                                (getCurrState() == HA_HOT_STANDBY_ST) ||
                                (getCurrState() == HA_PARTNER_DOWN_ST) ||
                                (getCurrState() == HA_PARTNER_IN_MAINTENANCE_ST) ||
                                (getCurrState() == HA_TERMINATED_ST));

    if (!should_enable && network_state_->isServiceEnabled()) {
        std::string current_state_name = getStateLabel(getCurrState());
        boost::to_upper(current_state_name);
        LOG_INFO(ha_logger, HA_LOCAL_DHCP_DISABLE)
            .arg(config_->getThisServerName())
            .arg(current_state_name);
        network_state_->disableService();

    } else if (should_enable && !network_state_->isServiceEnabled()) {
        std::string current_state_name = getStateLabel(getCurrState());
        boost::to_upper(current_state_name);
        LOG_INFO(ha_logger, HA_LOCAL_DHCP_ENABLE)
            .arg(config_->getThisServerName())
            .arg(current_state_name);
        network_state_->enableService();
    }
}

bool
HAService::shouldPartnerDown() const {
    // Checking whether the communication with the partner is ok is the
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
    if (communication_state_->clockSkewShouldTerminate()) {
        LOG_ERROR(ha_logger, HA_HIGH_CLOCK_SKEW_CAUSES_TERMINATION)
            .arg(communication_state_->logFormatClockSkew());
        return (true);

    } else if (communication_state_->clockSkewShouldWarn()) {
        LOG_WARN(ha_logger, HA_HIGH_CLOCK_SKEW)
            .arg(communication_state_->logFormatClockSkew());
    }

    return (false);
}

bool
HAService::isMaintenanceCanceled() const {
    return (getLastEvent() == HA_MAINTENANCE_CANCEL_EVT);
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

        // Check if the lease update should be sent to the server. If we're in
        // the partner-down state we don't send lease updates to the partner.
        if (!shouldSendLeaseUpdates(conf)) {
            continue;
        }

        // Count contacted servers.
        ++sent_num;

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

        // Check if the lease update should be sent to the server. If we're in
        // the partner-down state we don't send lease updates to the partner.
        if (!shouldSendLeaseUpdates(conf)) {
            continue;
        }

        // Count contacted servers.
        ++sent_num;

        // Send new/updated leases and deleted leases in one command.
        asyncSendLeaseUpdate(query, conf, CommandCreator::createLease6BulkApply(leases, deleted_leases),
                             parking_lot);
    }

    return (sent_num);
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
         HostHttpHeader(config->getUrl().getHostname()));
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
    client_.asyncSendRequest(config->getUrl(), request, response,
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
            if (config->getRole() != HAConfig::PeerConfig::BACKUP) {
                if (lease_update_success) {
                    // If the lease update was successful and we have sent it to the server
                    // to which we also send heartbeats (primary, secondary or standby) we
                    // can assume that the server is online and we can defer next heartbeat.
                    communication_state_->poke();

                } else {
                    // Lease update was unsuccessful, so drop the parked DHCP packet.
                    parking_lot->drop(query);
                    communication_state_->setPartnerState("unavailable");
                }
            }

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

                // If we have finished sending the lease updates we need to run the
                // state machine until the state machine finds that additional events
                // are required, such as next heartbeat or a lease update. The runModel()
                // may transition to another state, schedule asynchronous tasks etc.
                // Then it returns control to the DHCP server.
                runModel(HA_LEASE_UPDATES_COMPLETE_EVT);
            }
        },
        HttpClient::RequestTimeout(TIMEOUT_DEFAULT_HTTP_CLIENT_REQUEST),
        boost::bind(&HAService::clientConnectHandler, this, _1, _2),
        boost::bind(&HAService::clientCloseHandler, this, _1)
    );

    // Request scheduled, so update the request counters for the query.
    if (pending_requests_.count(query) == 0) {
        pending_requests_[query] = 1;

    } else {
        ++pending_requests_[query];
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
                             lease_type->stringValue() : "(uknown)")
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

    // Remote part
    ElementPtr remote = Element::createMap();

    // Add the in-touch boolean flag to indicate whether there was any
    // communication between the HA peers. Based on that, the user
    // may determine if the status returned for the peer is based on
    // the heartbeat or is to be determined.
    auto in_touch = (communication_state_->getPartnerState() > 0);
    remote->set("in-touch", Element::create(in_touch));

    auto age = in_touch ?
        static_cast<long long int>(communication_state_->getDurationInMillisecs() / 1000) : 0;
    remote->set("age", Element::create(age));

    try {
        role = config_->getFailoverPeerConfig()->getRole();
        std::string role_txt = HAConfig::PeerConfig::roleToString(role);
        remote->set("role", Element::create(role_txt));

    } catch (...) {
        remote->set("role", Element::create(std::string()));
    }

    try {
        state = getPartnerState();
        remote->set("last-state", Element::create(stateToString(state)));

    } catch (...) {
        remote->set("last-state", Element::create(std::string()));
    }

    // Remote server's scopes.
    scopes = communication_state_->getPartnerScopes();
    list = Element::createList();
    for (auto scope : scopes) {
        list->add(Element::create(scope));
    }
    remote->set("last-scopes", list);
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

    return (createAnswer(CONTROL_RESULT_SUCCESS, "HA peer status returned.",
                         arguments));
}

void
HAService::asyncSendHeartbeat() {
    HAConfig::PeerConfigPtr partner_config = config_->getFailoverPeerConfig();

    // Create HTTP/1.1 request including our command.
    PostHttpRequestJsonPtr request = boost::make_shared<PostHttpRequestJson>
        (HttpRequest::Method::HTTP_POST, "/", HttpVersion::HTTP_11(),
         HostHttpHeader(partner_config->getUrl().getHostname()));
    request->setBodyAsJson(CommandCreator::createHeartbeat(server_type_));
    request->finalize();

    // Response object should also be created because the HTTP client needs
    // to know the type of the expected response.
    HttpResponseJsonPtr response = boost::make_shared<HttpResponseJson>();

    // Schedule asynchronous HTTP request.
    client_.asyncSendRequest(partner_config->getUrl(), request, response,
        [this, partner_config]
            (const boost::system::error_code& ec,
             const HttpResponsePtr& response,
             const std::string& error_str) {

            // There are three possible groups of errors during the heartneat.
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
            }

            // Whatever the result of the heartbeat was, the state machine needs
            // to react to this. Let's run the state machine until the state machine
            // finds that some new events are required, i.e. next heartbeat or
            // lease update.  The runModel() may transition to another state, schedule
            // asynchronous tasks etc. Then it returns control to the DHCP server.
            startHeartbeat();
            runModel(HA_HEARTBEAT_COMPLETE_EVT);
        },
        HttpClient::RequestTimeout(TIMEOUT_DEFAULT_HTTP_CLIENT_REQUEST),
        boost::bind(&HAService::clientConnectHandler, this, _1, _2),
        boost::bind(&HAService::clientCloseHandler, this, _1)
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
                                             boost::bind(&HAService::asyncSendHeartbeat,
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
         HostHttpHeader(remote_config->getUrl().getHostname()));

    request->setBodyAsJson(CommandCreator::createDHCPDisable(max_period,
                                                             server_type_));
    request->finalize();

    // Response object should also be created because the HTTP client needs
    // to know the type of the expected response.
    HttpResponseJsonPtr response = boost::make_shared<HttpResponseJson>();

    // Schedule asynchronous HTTP request.
    http_client.asyncSendRequest(remote_config->getUrl(), request, response,
        [this, remote_config, post_request_action]
            (const boost::system::error_code& ec,
             const HttpResponsePtr& response,
             const std::string& error_str) {

             // There are three possible groups of errors during the heartneat.
             // One is the IO error causing issues in communication with the peer.
             // Another one is an HTTP parsing error. The last type of error is
             // when non-success error code is returned in the response carried
             // in the HTTP message or if the JSON response is otherwise broken.

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
                     int rcode = 0;
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
                                     error_message);
             }
        },
        HttpClient::RequestTimeout(TIMEOUT_DEFAULT_HTTP_CLIENT_REQUEST),
        boost::bind(&HAService::clientConnectHandler, this, _1, _2),
        boost::bind(&HAService::clientCloseHandler, this, _1)
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
         HostHttpHeader(remote_config->getUrl().getHostname()));
    request->setBodyAsJson(CommandCreator::createDHCPEnable(server_type_));
    request->finalize();

    // Response object should also be created because the HTTP client needs
    // to know the type of the expected response.
    HttpResponseJsonPtr response = boost::make_shared<HttpResponseJson>();

    // Schedule asynchronous HTTP request.
    http_client.asyncSendRequest(remote_config->getUrl(), request, response,
        [this, remote_config, post_request_action]
            (const boost::system::error_code& ec,
             const HttpResponsePtr& response,
             const std::string& error_str) {

             // There are three possible groups of errors during the heartneat.
             // One is the IO error causing issues in communication with the peer.
             // Another one is an HTTP parsing error. The last type of error is
             // when non-success error code is returned in the response carried
             // in the HTTP message or if the JSON response is otherwise broken.

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
                     int rcode = 0;
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
                                     error_message);
             }
        },
        HttpClient::RequestTimeout(TIMEOUT_DEFAULT_HTTP_CLIENT_REQUEST),
        boost::bind(&HAService::clientConnectHandler, this, _1, _2),
        boost::bind(&HAService::clientCloseHandler, this, _1)
    );
}

void
HAService::localDisableDHCPService() {
    network_state_->disableService();
}

void
HAService::localEnableDHCPService() {
    network_state_->enableService();
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

    asyncSyncLeases(client_, config_->getFailoverPeerConfig()->getName(),
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
                            (const bool success, const std::string& error_message) {

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
         HostHttpHeader(partner_config->getUrl().getHostname()));
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
    http_client.asyncSendRequest(partner_config->getUrl(), request, response,
        [this, partner_config, post_sync_action, &http_client, server_name,
         max_period, dhcp_disabled]
            (const boost::system::error_code& ec,
             const HttpResponsePtr& response,
             const std::string& error_str) {

             // Holds last lease received on the page of leases. If the last
             // page was hit, this value remains null.
             LeasePtr last_lease;

            // There are three possible groups of errors during the heartneat.
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
        boost::bind(&HAService::clientConnectHandler, this, _1, _2),
        boost::bind(&HAService::clientCloseHandler, this, _1)
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
            asyncEnableDHCPService(client, server_name,
                                   [&](const bool success,
                                       const std::string& error_message) {
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
        // parter would go to partner-down. In the case signaled by the special
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
         HostHttpHeader(remote_config->getUrl().getHostname()));
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
    client.asyncSendRequest(remote_config->getUrl(), request, response,
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
        boost::bind(&HAService::clientConnectHandler, this, _1, _2),
        boost::bind(&HAService::clientCloseHandler, this, _1)
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
                             " commmand: " + captured_error_message + "."));

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
         HostHttpHeader(remote_config->getUrl().getHostname()));
    request->setBodyAsJson(CommandCreator::createMaintenanceNotify(true, server_type_));
    request->finalize();

    // Response object should also be created because the HTTP client needs
    // to know the type of the expected response.
    HttpResponseJsonPtr response = boost::make_shared<HttpResponseJson>();

    IOService io_service;
    HttpClient client(io_service);

    std::string error_message;

    // Schedule asynchronous HTTP request.
    client.asyncSendRequest(remote_config->getUrl(), request, response,
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
        boost::bind(&HAService::clientConnectHandler, this, _1, _2),
        boost::bind(&HAService::clientCloseHandler, this, _1)
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
                             " commmand: " + error_message + "."));
    }

    // Successfully reverted partner's state. Let's also revert our state to the
    // previous one.
    postNextEvent(HA_MAINTENANCE_CANCEL_EVT);
    verboseTransition(getPrevState());
    runModel(NOP_EVT);

    return (createAnswer(CONTROL_RESULT_SUCCESS,
                         "Server maintenance successfully canceled."));
}

ConstElementPtr
HAService::verifyAsyncResponse(const HttpResponsePtr& response, int& rcode) {
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

    // Body must contain a list of responses form multiple servers.
    if (body->getType() != Element::list) {
        isc_throw(CtrlChannelError, "body of the response must be a list");
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
        isc_throw(CtrlChannelError, s.str());
    }

    return (args);
}

bool
HAService::clientConnectHandler(const boost::system::error_code& ec, int tcp_native_fd) {

    // If things look ok register the socket with Interface Manager. Note
    // we don't register if the FD is < 0 to avoid an expection throw.
    // It is unlikely that this will occur but we want to be liberal
    // and avoid issues.
    if ((!ec || (ec.value() == boost::asio::error::in_progress))
        && (tcp_native_fd >= 0)) {
        // External socket callback is a NOP. Ready events handlers are
        // run by an explicit call IOService ready in kea-dhcp<n> code.
        // We are registerin the socket only to interrupt main-thread
        // select().
        IfaceMgr::instance().addExternalSocket(tcp_native_fd,
            boost::bind(&HAService::socketReadyHandler, this, _1)
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
    client_.closeIfOutOfBandwidth(tcp_native_fd);
}

void
HAService::clientCloseHandler(int tcp_native_fd) {
    if (tcp_native_fd >= 0) {
        IfaceMgr::instance().deleteExternalSocket(tcp_native_fd);
    }
};

} // end of namespace isc::ha
} // end of namespace isc
