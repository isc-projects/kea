// Copyright (C) 2018-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ha_config_parser.h>
#include <ha_impl.h>
#include <ha_log.h>
#include <asiolink/io_service.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/subnet.h>
#include <stats/stats_mgr.h>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::log;
using namespace isc::stats;

namespace isc {
namespace ha {

HAImpl::HAImpl()
    : io_service_(new IOService()), config_(), services_(new HAServiceMapper()) {
}

void
HAImpl::configure(const ConstElementPtr& input_config) {
    config_ = HAConfigParser::parse(input_config);
}

void
HAImpl::startServices(const NetworkStatePtr& network_state,
                      const HAServerType& server_type) {
    auto configs = config_->getAll();
    for (auto id = 0; id < configs.size(); ++id) {
        // Create the HA service and crank up the state machine.
        auto service = boost::make_shared<HAService>(id, io_service_, network_state,
                                                     configs[id], server_type);
        for (auto const& peer_config : configs[id]->getAllServersConfig()) {
            services_->map(peer_config.first, service);
        }
    }
    // Schedule a start of the services. This ensures we begin after
    // the dust has settled and Kea MT mode has been firmly established.
    io_service_->post([&]() {
        for (auto const& service : services_->getAll()) {
            service->startClientAndListener();
        }
    });
}

HAImpl::~HAImpl() {
    for (auto const& service : services_->getAll()) {
        // Shut down the services explicitly, we need finer control
        // than relying on destruction order.
        service->stopClientAndListener();
    }
    config_.reset();
    services_.reset(new HAServiceMapper());
    io_service_->stopAndPoll();
}

void
HAImpl::buffer4Receive(hooks::CalloutHandle& callout_handle) {
    // If there are multiple relationships, the HA-specific processing is
    // in the subnet4_select hook point.
    if (services_->hasMultiple()) {
        return;
    }

    Pkt4Ptr query4;
    callout_handle.getArgument("query4", query4);

    /// @todo Add unit tests to verify the behavior for different
    /// malformed packets.
    try {
        // We have to unpack the query to get access into HW address which is
        // used to load balance the packet.
        if (callout_handle.getStatus() != CalloutHandle::NEXT_STEP_SKIP) {
            query4->unpack();
        }

    } catch (const SkipRemainingOptionsError& ex) {
        // An option failed to unpack but we are to attempt to process it
        // anyway.  Log it and let's hope for the best.
        LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC,
                  HA_BUFFER4_RECEIVE_PACKET_OPTIONS_SKIPPED)
            .arg(ex.what());

    } catch (const std::exception& ex) {
        // Packet parsing failed. Drop the packet.
        LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC, HA_BUFFER4_RECEIVE_UNPACK_FAILED)
            .arg(query4->getRemoteAddr().toText())
            .arg(query4->getLocalAddr().toText())
            .arg(query4->getIface())
            .arg(ex.what());

        // Increase the statistics of parse failures and dropped packets.
        StatsMgr::instance().addValue("pkt4-parse-failed", static_cast<int64_t>(1));
        StatsMgr::instance().addValue("pkt4-receive-drop", static_cast<int64_t>(1));


        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return;
    }

    // Check if we should process this query. If not, drop it.
    if (!services_->get()->inScope(query4)) {
        LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC, HA_BUFFER4_RECEIVE_NOT_FOR_US)
            .arg(query4->getLabel());
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

    } else {
        // We have successfully parsed the query so we have to signal
        // to the server that it must not parse it.
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);
    }
}

void
HAImpl::subnet4Select(hooks::CalloutHandle& callout_handle) {
    // This callout only applies in the case of multiple relationships.
    // When there is only one relationship it has no effect because
    // the decision if we should process the packet has been made
    // in the buffer4_receive callout.
    if (!services_->hasMultiple()) {
        // Return silently. It is not an error.
        return;
    }

    Pkt4Ptr query4;
    callout_handle.getArgument("query4", query4);

    Subnet4Ptr subnet4;
    callout_handle.getArgument("subnet4", subnet4);

    // If the server failed to select the subnet this pointer is null.
    // There is nothing we can do with this packet because we don't know
    // which relationship it belongs to. We're even unable to check if the
    // server is responsible for this packet.
    if (!subnet4) {
        // Log at debug level because that's the level at which the server
        // logs the subnet selection failure.
        LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC, HA_SUBNET4_SELECT_NO_SUBNET_SELECTED)
            .arg(query4->getLabel());
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        StatsMgr::instance().addValue("pkt4-receive-drop", static_cast<int64_t>(1));
        return;
    }

    // The subnet configuration should contain a user context
    // and this context should contain a mapping of the subnet to a
    // relationship. If the context doesn't exist there is no way
    // to determine which relationship the packet belongs to.
    std::string server_name;
    try {
        server_name = HAConfig::getSubnetServerName(subnet4);
        if (server_name.empty()) {
            LOG_ERROR(ha_logger, HA_SUBNET4_SELECT_NO_RELATIONSHIP_SELECTOR_FOR_SUBNET)
                .arg(query4->getLabel())
                .arg(subnet4->toText());
            callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
            StatsMgr::instance().addValue("pkt4-receive-drop", static_cast<int64_t>(1));
            return;
        }

    } catch (...) {
        LOG_ERROR(ha_logger, HA_SUBNET4_SELECT_INVALID_HA_SERVER_NAME)
            .arg(query4->getLabel())
            .arg(subnet4->toText());
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        StatsMgr::instance().addValue("pkt4-receive-drop", static_cast<int64_t>(1));
        return;
    }

    // Try to find a relationship matching this server name.
    auto service = services_->get(server_name);
    if (!service) {
        LOG_ERROR(ha_logger, HA_SUBNET4_SELECT_NO_RELATIONSHIP_FOR_SUBNET)
            .arg(query4->getLabel())
            .arg(server_name);
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        StatsMgr::instance().addValue("pkt4-receive-drop", static_cast<int64_t>(1));
        return;
    }

    // We have found appropriate relationship. Let's see if we should
    // process the packet. We'll drop the packet if our partner is
    // operational and is responsible for this packet.
    if (!service->inScope(query4)) {
        LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC, HA_SUBNET4_SELECT_NOT_FOR_US)
            .arg(query4->getLabel())
            .arg(server_name);
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return;
    }

    // Remember the server name we retrieved from the subnet. We will
    // need it in a leases4_committed callout that doesn't have access
    // to the subnet object.
    callout_handle.setContext("ha-server-name", server_name);
}

void
HAImpl::leases4Committed(CalloutHandle& callout_handle) {
    Pkt4Ptr query4;
    Lease4CollectionPtr leases4;
    Lease4CollectionPtr deleted_leases4;

    // Get all arguments available for the leases4_committed hook point.
    // If any of these arguments is not available this is a programmatic
    // error. An exception will be thrown which will be caught by the
    // caller and logged.
    callout_handle.getArgument("query4", query4);

    callout_handle.getArgument("leases4", leases4);
    callout_handle.getArgument("deleted_leases4", deleted_leases4);

    // In some cases we may have no leases, e.g. DHCPNAK.
    if (leases4->empty() && deleted_leases4->empty()) {
        LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC, HA_LEASES4_COMMITTED_NOTHING_TO_UPDATE)
            .arg(query4->getLabel());
        return;
    }

    // Get default config and service instances.
    HAConfigPtr config = config_->get();
    HAServicePtr service = services_->get();

    // If we have multiple relationships we need to find the one that
    // matches our subnet.
    if (services_->hasMultiple()) {
        try {
            // Retrieve the server name from the context and the respective
            // config and service instances.
            std::string server_name;
            callout_handle.getContext("ha-server-name", server_name);
            config = config_->get(server_name);
            service = services_->get(server_name);

            // This is rather impossible but let's be safe.
            if (!config || !service) {
                isc_throw(Unexpected, "relationship not configured for server '" << server_name << "'");
            }

        } catch (const std::exception& ex) {
            LOG_ERROR(ha_logger, HA_LEASES4_COMMITTED_NO_RELATIONSHIP)
                .arg(query4->getLabel())
                .arg(ex.what());
            callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
            return;
        }
    }

    // If the hook library is configured to not send lease updates to the
    // partner, there is nothing to do because this whole callout is
    // currently about sending lease updates.
    if (!config->amSendingLeaseUpdates()) {
        // No need to log it, because it was already logged when configuration
        // was applied.
        return;
    }

    // Get the parking lot for this hook point. We're going to remember this
    // pointer until we unpark the packet.
    ParkingLotHandlePtr parking_lot = callout_handle.getParkingLotHandlePtr();

    // Create a reference to the parked packet. This signals that we have a
    // stake in unparking it.
    parking_lot->reference(query4);

    // Asynchronously send lease updates. In some cases no updates will be sent,
    // e.g. when this server is in the partner-down state and there are no backup
    // servers. In those cases we simply return without parking the DHCP query.
    // The response will be sent to the client immediately.
    try {
        if (service->asyncSendLeaseUpdates(query4, leases4, deleted_leases4, parking_lot) == 0) {
            // Dereference the parked packet.  This releases our stake in it.
            parking_lot->dereference(query4);
            return;
        }
    } catch (...) {
        // Make sure we dereference.
        parking_lot->dereference(query4);
        throw;
    }

    // The callout returns this status code to indicate to the server that it
    // should leave the packet parked.  It will be parked until each hook
    // library with a reference, unparks the packet.
    callout_handle.setStatus(CalloutHandle::NEXT_STEP_PARK);
}

void
HAImpl::lease4ServerDecline(CalloutHandle& callout_handle) {
    // Always return CONTINUE.
    callout_handle.setStatus(CalloutHandle::NEXT_STEP_CONTINUE);
    size_t peers_to_update = 0;

    // If the hook library is configured to not send lease updates to the
    // partner, there is nothing to do because this whole callout is
    // currently about sending lease updates.
    if (!config_->get()->amSendingLeaseUpdates()) {
        // No need to log it, because it was already logged when configuration
        // was applied.
        callout_handle.setArgument("peers_to_update", peers_to_update);
        return;
    }

    // Get all arguments available for the lease4_server_decline hook point.
    // If any of these arguments is not available this is a programmatic
    // error. An exception will be thrown which will be caught by the
    // caller and logged.
    Pkt4Ptr query4;
    callout_handle.getArgument("query4", query4);

    Lease4Ptr lease4;
    callout_handle.getArgument("lease4", lease4);

    // Asynchronously send the lease update. In some cases no updates will be sent,
    // e.g. when this server is in the partner-down state and there are no backup
    // servers.
    peers_to_update = services_->get()->asyncSendSingleLeaseUpdate(query4, lease4, 0);
    callout_handle.setArgument("peers_to_update", peers_to_update);
}

void
HAImpl::buffer6Receive(hooks::CalloutHandle& callout_handle) {
    // If there are multiple relationships, the HA-specific processing is
    // in the subnet6_select hook point.
    if (services_->hasMultiple()) {
        return;
    }

    Pkt6Ptr query6;
    callout_handle.getArgument("query6", query6);

    /// @todo Add unit tests to verify the behavior for different
    /// malformed packets.
    try {
        // We have to unpack the query to get access into DUID which is
        // used to load balance the packet.
        if (callout_handle.getStatus() != CalloutHandle::NEXT_STEP_SKIP) {
            query6->unpack();
        }

    } catch (const SkipRemainingOptionsError& ex) {
        // An option failed to unpack but we are to attempt to process it
        // anyway.  Log it and let's hope for the best.
        LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC,
                  HA_BUFFER6_RECEIVE_PACKET_OPTIONS_SKIPPED)
            .arg(ex.what());

    } catch (const std::exception& ex) {
        // Packet parsing failed. Drop the packet.
        LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC, HA_BUFFER6_RECEIVE_UNPACK_FAILED)
            .arg(query6->getRemoteAddr().toText())
            .arg(query6->getLocalAddr().toText())
            .arg(query6->getIface())
            .arg(ex.what());

        // Increase the statistics of parse failures and dropped packets.
        StatsMgr::instance().addValue("pkt6-parse-failed", static_cast<int64_t>(1));
        StatsMgr::instance().addValue("pkt6-receive-drop", static_cast<int64_t>(1));


        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return;
    }

    // Check if we should process this query. If not, drop it.
    if (!services_->get()->inScope(query6)) {
        LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC, HA_BUFFER6_RECEIVE_NOT_FOR_US)
            .arg(query6->getLabel());
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

    } else {
        // We have successfully parsed the query so we have to signal
        // to the server that it must not parse it.
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);
    }
}

void
HAImpl::subnet6Select(hooks::CalloutHandle& callout_handle) {
    // This callout only applies in the case of multiple relationships.
    // When there is only one relationship it has no effect because
    // the decision if we should process the packet has been made
    // in the buffer6_receive callout.
    if (!services_->hasMultiple()) {
        // Return silently. It is not an error.
        return;
    }

    Pkt6Ptr query6;
    callout_handle.getArgument("query6", query6);

    Subnet6Ptr subnet6;
    callout_handle.getArgument("subnet6", subnet6);

    // If the server failed to select the subnet this pointer is null.
    // There is nothing we can do with this packet because we don't know
    // which relationship it belongs to. We're even unable to check if the
    // server is responsible for this packet.
    if (!subnet6) {
        // Log at debug level because that's the level at which the server
        // logs the subnet selection failure.
        LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC, HA_SUBNET6_SELECT_NO_SUBNET_SELECTED)
            .arg(query6->getLabel());
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        StatsMgr::instance().addValue("pkt6-receive-drop", static_cast<int64_t>(1));
        return;
    }

    // The subnet configuration should contain a user context
    // and this context should contain a mapping of the subnet to a
    // relationship. If the context doesn't exist there is no way
    // to determine which relationship the packet belongs to.
    std::string server_name;
    try {
        server_name = HAConfig::getSubnetServerName(subnet6);
        if (server_name.empty()) {
            LOG_ERROR(ha_logger, HA_SUBNET6_SELECT_NO_RELATIONSHIP_SELECTOR_FOR_SUBNET)
                .arg(query6->getLabel())
                .arg(subnet6->toText());
            callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
            StatsMgr::instance().addValue("pkt6-receive-drop", static_cast<int64_t>(1));
            return;
        }

    } catch (...) {
        LOG_ERROR(ha_logger, HA_SUBNET6_SELECT_INVALID_HA_SERVER_NAME)
            .arg(query6->getLabel())
            .arg(subnet6->toText());
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        StatsMgr::instance().addValue("pkt6-receive-drop", static_cast<int64_t>(1));
        return;
    }

    // Try to find a relationship matching this server name.
    auto service = services_->get(server_name);
    if (!service) {
        LOG_ERROR(ha_logger, HA_SUBNET6_SELECT_NO_RELATIONSHIP_FOR_SUBNET)
            .arg(query6->getLabel())
            .arg(server_name);
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        StatsMgr::instance().addValue("pkt6-receive-drop", static_cast<int64_t>(1));
        return;
    }

    // We have found appropriate relationship. Let's see if we should
    // process the packet. We'll drop the packet if our partner is
    // operational and is responsible for this packet.
    if (!service->inScope(query6)) {
        LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC, HA_SUBNET6_SELECT_NOT_FOR_US)
            .arg(query6->getLabel())
            .arg(server_name);
        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return;
    }

    // Remember the server name we retrieved from the subnet. We will
    // need it in a leases4_committed callout that doesn't have access
    // to the subnet object.
    callout_handle.setContext("ha-server-name", server_name);
}

void
HAImpl::leases6Committed(CalloutHandle& callout_handle) {
    Pkt6Ptr query6;
    Lease6CollectionPtr leases6;
    Lease6CollectionPtr deleted_leases6;

    // Get all arguments available for the leases6_committed hook point.
    // If any of these arguments is not available this is a programmatic
    // error. An exception will be thrown which will be caught by the
    // caller and logged.
    callout_handle.getArgument("query6", query6);

    callout_handle.getArgument("leases6", leases6);
    callout_handle.getArgument("deleted_leases6", deleted_leases6);

    // In some cases we may have no leases.
    if (leases6->empty() && deleted_leases6->empty()) {
        LOG_DEBUG(ha_logger, DBGLVL_TRACE_BASIC, HA_LEASES6_COMMITTED_NOTHING_TO_UPDATE)
            .arg(query6->getLabel());
        return;
    }

    HAConfigPtr config = config_->get();
    HAServicePtr service = services_->get();
    if (services_->hasMultiple()) {
        try {
            std::string server_name;
            callout_handle.getContext("ha-server-name", server_name);
            config = config_->get(server_name);
            service = services_->get(server_name);

            if (!config || !service) {
                isc_throw(Unexpected, "relationship not found for the ha-server-name='" << server_name << "'");
            }

        } catch (const std::exception& ex) {
            LOG_ERROR(ha_logger, HA_LEASES6_COMMITTED_NO_RELATIONSHIP)
                .arg(query6->getLabel())
                .arg(ex.what());
            callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
            return;
        }
    }

    // If the hook library is configured to not send lease updates to the
    // partner, there is nothing to do because this whole callout is
    // currently about sending lease updates.
    if (!config->amSendingLeaseUpdates()) {
        // No need to log it, because it was already logged when configuration
        // was applied.
        return;
    }

    // Get the parking lot for this hook point. We're going to remember this
    // pointer until we unpark the packet.
    ParkingLotHandlePtr parking_lot = callout_handle.getParkingLotHandlePtr();

    // Create a reference to the parked packet. This signals that we have a
    // stake in unparking it.
    parking_lot->reference(query6);

    // Asynchronously send lease updates. In some cases no updates will be sent,
    // e.g. when this server is in the partner-down state and there are no backup
    // servers. In those cases we simply return without parking the DHCP query.
    // The response will be sent to the client immediately.
    try {
        if (service->asyncSendLeaseUpdates(query6, leases6, deleted_leases6, parking_lot) == 0) {
            // Dereference the parked packet.  This releases our stake in it.
            parking_lot->dereference(query6);
            return;
        }
    } catch (...) {
        // Make sure we dereference.
        parking_lot->dereference(query6);
        throw;
    }

    // The callout returns this status code to indicate to the server that it
    // should leave the packet parked.  It will be unparked until each hook
    // library with a reference, unparks the packet.
    callout_handle.setStatus(CalloutHandle::NEXT_STEP_PARK);
}

void
HAImpl::commandProcessed(hooks::CalloutHandle& callout_handle) {
    std::string command_name;
    callout_handle.getArgument("name", command_name);
    if (command_name == "status-get") {
        // Get the response.
        ConstElementPtr response;
        callout_handle.getArgument("response", response);
        if (!response || (response->getType() != Element::map)) {
            return;
        }
        // Get the arguments item from the response.
        ConstElementPtr resp_args = response->get("arguments");
        if (!resp_args || (resp_args->getType() != Element::map)) {
            return;
        }
        // Add the ha servers info to arguments.
        ElementPtr mutable_resp_args =
            boost::const_pointer_cast<Element>(resp_args);

        // Process the status get command for each HA service.
        auto ha_relationships = Element::createList();
        for (auto const& service : services_->getAll()) {
            auto ha_relationship = Element::createMap();
            ConstElementPtr ha_servers = service->processStatusGet();
            ha_relationship->set("ha-servers", ha_servers);
            ha_relationship->set("ha-mode", Element::create(HAConfig::HAModeToString(config_->get()->getHAMode())));
            ha_relationships->add(ha_relationship);
            mutable_resp_args->set("high-availability", ha_relationships);
        }
    }
}

void
HAImpl::heartbeatHandler(CalloutHandle& callout_handle) {
    // Command must always be provided.
    ConstElementPtr command;
    callout_handle.getArgument("command", command);

    // Retrieve arguments.
    ConstElementPtr args;
    static_cast<void>(parseCommand(args, command));

    HAServicePtr service;
    try {
        service = getHAServiceByServerName("ha-heartbeat", args);

    } catch (const std::exception& ex) {
        // There was an error while parsing command arguments. Return an error status
        // code to notify the user.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        callout_handle.setArgument("response", response);
        return;
    }

    // Command parsing was successful, so let's process the command.
    ConstElementPtr response = service->processHeartbeat();
    callout_handle.setArgument("response", response);
}

void
HAImpl::synchronizeHandler(hooks::CalloutHandle& callout_handle) {
    // Command must always be provided.
    ConstElementPtr command;
    callout_handle.getArgument("command", command);

    // Retrieve arguments.
    ConstElementPtr args;
    static_cast<void>(parseCommand(args, command));

    ConstElementPtr server_name;
    unsigned int max_period_value = 0;

    HAServicePtr service;
    try {
        // Arguments are required for the ha-sync command.
        if (!args) {
            isc_throw(BadValue, "arguments not found in the 'ha-sync' command");
        }

        // Arguments must be a map.
        if (args->getType() != Element::map) {
            isc_throw(BadValue, "arguments in the 'ha-sync' command are not a map");
        }

        // server-name is mandatory. Otherwise how can we know the server to
        // communicate with.
        server_name = args->get("server-name");
        if (!server_name) {
            isc_throw(BadValue, "'server-name' is mandatory for the 'ha-sync' command");
        }

        // server-name must obviously be a string.
        if (server_name->getType() != Element::string) {
            isc_throw(BadValue, "'server-name' must be a string in the 'ha-sync' command");
        }

        // max-period is optional. In fact it is optional for dhcp-disable command too.
        ConstElementPtr max_period = args->get("max-period");
        if (max_period) {
            // If it is specified, it must be a positive integer.
            if ((max_period->getType() != Element::integer) ||
                (max_period->intValue() <= 0)) {
                isc_throw(BadValue, "'max-period' must be a positive integer in the 'ha-sync' command");
            }

            max_period_value = static_cast<unsigned int>(max_period->intValue());
        }

        service = getHAServiceByServerName("ha-sync", args);

    } catch (const std::exception& ex) {
        // There was an error while parsing command arguments. Return an error status
        // code to notify the user.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        callout_handle.setArgument("response", response);
        return;
    }

    // Command parsing was successful, so let's process the command.
    ConstElementPtr response = service->processSynchronize(server_name->stringValue(),
                                                           max_period_value);
    callout_handle.setArgument("response", response);
}

void
HAImpl::scopesHandler(hooks::CalloutHandle& callout_handle) {
    // Command must always be provided.
    ConstElementPtr command;
    callout_handle.getArgument("command", command);

    // Retrieve arguments.
    ConstElementPtr args;
    static_cast<void>(parseCommand(args, command));

    HAServicePtr service;
    std::vector<std::string> scopes_vector;
    try {
        // Arguments must be present.
        if (!args) {
            isc_throw(BadValue, "arguments not found in the 'ha-scopes' command");
        }

        // Arguments must be a map.
        if (args->getType() != Element::map) {
            isc_throw(BadValue, "arguments in the 'ha-scopes' command are not a map");
        }

        // scopes argument is mandatory.
        ConstElementPtr scopes = args->get("scopes");
        if (!scopes) {
            isc_throw(BadValue, "'scopes' is mandatory for the 'ha-scopes' command");
        }

        // It contains a list of scope names.
        if (scopes->getType() != Element::list) {
            isc_throw(BadValue, "'scopes' must be a list in the 'ha-scopes' command");
        }

        // Retrieve scope names from this list. The list may be empty to clear the
        // scopes.
        for (size_t i = 0; i < scopes->size(); ++i) {
            ConstElementPtr scope = scopes->get(i);
            if (!scope || scope->getType() != Element::string) {
                isc_throw(BadValue, "scope name must be a string in the 'scopes' argument");
            }
            scopes_vector.push_back(scope->stringValue());
        }

        service = getHAServiceByServerName("ha-scopes", args);

    } catch (const std::exception& ex) {
        // There was an error while parsing command arguments. Return an error status
        // code to notify the user.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        callout_handle.setArgument("response", response);
        return;
    }

    // Command parsing was successful, so let's process the command.
    ConstElementPtr response = service->processScopes(scopes_vector);
    callout_handle.setArgument("response", response);
}

void
HAImpl::continueHandler(hooks::CalloutHandle& callout_handle) {
    // Command must always be provided.
    ConstElementPtr command;
    callout_handle.getArgument("command", command);

    // Retrieve arguments.
    ConstElementPtr args;
    static_cast<void>(parseCommand(args, command));

    HAServicePtr service;
    try {
        service = getHAServiceByServerName("ha-continue", args);

    } catch (const std::exception& ex) {
        // There was an error while parsing command arguments. Return an error status
        // code to notify the user.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        callout_handle.setArgument("response", response);
        return;
    }
    ConstElementPtr response = service->processContinue();
    callout_handle.setArgument("response", response);
}

void
HAImpl::maintenanceNotifyHandler(hooks::CalloutHandle& callout_handle) {
    // Command must always be provided.
    ConstElementPtr command;
    callout_handle.getArgument("command", command);

    HAServicePtr service;
    try {
        // Retrieve arguments.
        ConstElementPtr args;
        static_cast<void>(parseCommandWithArgs(args, command));

        ConstElementPtr cancel_op = args->get("cancel");
        if (!cancel_op) {
            isc_throw(BadValue, "'cancel' is mandatory for the 'ha-maintenance-notify' command");
        }

        if (cancel_op->getType() != Element::boolean) {
            isc_throw(BadValue, "'cancel' must be a boolean in the 'ha-maintenance-notify' command");
        }

        service = getHAServiceByServerName("ha-maintenance-notify", args);

        ConstElementPtr response = service->processMaintenanceNotify(cancel_op->boolValue());
        callout_handle.setArgument("response", response);

    } catch (const std::exception& ex) {
        // There was an error while parsing command arguments. Return an error status
        // code to notify the user.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        callout_handle.setArgument("response", response);
    }
}

void
HAImpl::maintenanceStartHandler(hooks::CalloutHandle& callout_handle) {
    ConstElementPtr response;
    for (auto const& service : services_->getAll()) {
        response = service->processMaintenanceStart();
        int rcode = CONTROL_RESULT_SUCCESS;
        static_cast<void>(parseAnswer(rcode, response));
        if (rcode != CONTROL_RESULT_SUCCESS) {
            break;
        }
    }
    callout_handle.setArgument("response", response);
}

void
HAImpl::maintenanceCancelHandler(hooks::CalloutHandle& callout_handle) {
    ConstElementPtr response;
    for (auto const& service : services_->getAll()) {
        response = service->processMaintenanceCancel();
    }
    callout_handle.setArgument("response", response);
}

void
HAImpl::haResetHandler(hooks::CalloutHandle& callout_handle) {
    // Command must always be provided.
    ConstElementPtr command;
    callout_handle.getArgument("command", command);

    // Retrieve arguments.
    ConstElementPtr args;
    static_cast<void>(parseCommand(args, command));

    HAServicePtr service;
    try {
        service = getHAServiceByServerName("ha-reset", args);

    } catch (const std::exception& ex) {
        // There was an error while parsing command arguments. Return an error status
        // code to notify the user.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        callout_handle.setArgument("response", response);
        return;
    }

    ConstElementPtr response = service->processHAReset();
    callout_handle.setArgument("response", response);
}

void
HAImpl::syncCompleteNotifyHandler(hooks::CalloutHandle& callout_handle) {
    // Command must always be provided.
    ConstElementPtr command;
    callout_handle.getArgument("command", command);

    // Retrieve arguments.
    ConstElementPtr args;
    static_cast<void>(parseCommand(args, command));

    HAServicePtr service;
    auto origin_id_value = NetworkState::HA_REMOTE_COMMAND+1;
    try {
        if (args) {
            auto origin_id = args->get("origin-id");
            auto origin = args->get("origin");
            // The origin-id is a new parameter replacing the origin. However, some versions
            // of Kea may still send the origin parameter instead.
            if (origin_id) {
                if (origin_id->getType() != Element::integer) {
                    isc_throw(BadValue, "'origin-id' must be an integer in the 'ha-sync-complete-notify' command");
                }
                origin_id_value = origin_id->intValue();

            } else if (origin) {
                if (origin->getType() != Element::integer) {
                    isc_throw(BadValue, "'origin' must be an integer in the 'ha-sync-complete-notify' command");
                }
                origin_id_value = origin->intValue();
            }
        }

        service = getHAServiceByServerName("ha-sync-complete-notify", args);

    } catch (const std::exception& ex) {
        // There was an error while parsing command arguments. Return an error status
        // code to notify the user.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        callout_handle.setArgument("response", response);
        return;
    }

    ConstElementPtr response = service->processSyncCompleteNotify(origin_id_value);
    callout_handle.setArgument("response", response);
}

HAServicePtr
HAImpl::getHAServiceByServerName(const std::string& command_name, ConstElementPtr args) const {
    HAServicePtr service;
    if (args) {
        // Arguments must be a map.
        if (args->getType() != Element::map) {
            isc_throw(BadValue, "arguments in the '" << command_name << "' command are not a map");
        }

        auto server_name = args->get("server-name");

        if (server_name) {
            if (server_name->getType() != Element::string) {
                isc_throw(BadValue, "'server-name' must be a string in the '" << command_name << "' command");
            }
            service = services_->get(server_name->stringValue());
            if (!service) {
                isc_throw(BadValue, server_name->stringValue() << " matches no configured"
                          << " 'server-name'");
            }
        }
    }

    if (!service) {
        service = services_->get();
    }

    return (service);
}

} // end of namespace isc::ha
} // end of namespace isc
