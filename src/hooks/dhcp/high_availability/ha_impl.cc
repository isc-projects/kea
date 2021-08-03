// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
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
#include <stats/stats_mgr.h>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::log;

namespace isc {
namespace ha {

HAImpl::HAImpl()
    : config_(new HAConfig()) {
}

void
HAImpl::configure(const ConstElementPtr& input_config) {
    HAConfigParser parser;
    parser.parse(config_, input_config);
}

void
HAImpl::startService(const IOServicePtr& io_service,
                     const NetworkStatePtr& network_state,
                     const HAServerType& server_type) {
    // Create the HA service and crank up the state machine.
    service_ = boost::make_shared<HAService>(io_service, network_state,
                                             config_, server_type);
    // Schedule a start of the services. This ensures we begin after
    // the dust has settled and Kea MT mode has been firmly established.
    io_service->post([&]() { service_->startClientAndListener(); } );
}

HAImpl::~HAImpl() {
    if (service_) {
        // Shut down the services explicitly, we need finer control
        // than relying on destruction order.
        service_->stopClientAndListener();
    }
}

void
HAImpl::buffer4Receive(hooks::CalloutHandle& callout_handle) {
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
        isc::stats::StatsMgr::instance().addValue("pkt4-parse-failed",
                                                  static_cast<int64_t>(1));
        isc::stats::StatsMgr::instance().addValue("pkt4-receive-drop",
                                                  static_cast<int64_t>(1));


        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return;
    }

    // Check if we should process this query. If not, drop it.
    if (!service_->inScope(query4)) {
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
HAImpl::leases4Committed(CalloutHandle& callout_handle) {
    // If the hook library is configured to not send lease updates to the
    // partner, there is nothing to do because this whole callout is
    // currently about sending lease updates.
    if (!config_->amSendingLeaseUpdates()) {
        // No need to log it, because it was already logged when configuration
        // was applied.
        return;
    }

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
        if (service_->asyncSendLeaseUpdates(query4, leases4, deleted_leases4, parking_lot) == 0) {
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
HAImpl::buffer6Receive(hooks::CalloutHandle& callout_handle) {
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
        isc::stats::StatsMgr::instance().addValue("pkt6-parse-failed",
                                                  static_cast<int64_t>(1));
        isc::stats::StatsMgr::instance().addValue("pkt6-receive-drop",
                                                  static_cast<int64_t>(1));


        callout_handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return;
    }

    // Check if we should process this query. If not, drop it.
    if (!service_->inScope(query6)) {
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
HAImpl::leases6Committed(CalloutHandle& callout_handle) {
    // If the hook library is configured to not send lease updates to the
    // partner, there is nothing to do because this whole callout is
    // currently about sending lease updates.
    if (!config_->amSendingLeaseUpdates()) {
        // No need to log it, because it was already logged when configuration
        // was applied.
        return;
    }

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
        if (service_->asyncSendLeaseUpdates(query6, leases6, deleted_leases6, parking_lot) == 0) {
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

        /// @todo Today we support only one HA relationship per Kea server.
        /// In the future there will be more of them. Therefore we enclose
        /// our sole relationship in a list.
        auto ha_relationships = Element::createList();
        auto ha_relationship = Element::createMap();
        ConstElementPtr ha_servers = service_->processStatusGet();
        ha_relationship->set("ha-servers", ha_servers);
        ha_relationship->set("ha-mode", Element::create(HAConfig::HAModeToString(config_->getHAMode())));
        ha_relationships->add(ha_relationship);
        mutable_resp_args->set("high-availability", ha_relationships);
    }
}

void
HAImpl::heartbeatHandler(CalloutHandle& callout_handle) {
    ConstElementPtr response = service_->processHeartbeat();
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

    } catch (const std::exception& ex) {
        // There was an error while parsing command arguments. Return an error status
        // code to notify the user.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        callout_handle.setArgument("response", response);
        return;
    }

    // Command parsing was successful, so let's process the command.
    ConstElementPtr response = service_->processSynchronize(server_name->stringValue(),
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

    } catch (const std::exception& ex) {
        // There was an error while parsing command arguments. Return an error status
        // code to notify the user.
        ConstElementPtr response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        callout_handle.setArgument("response", response);
        return;
    }

    // Command parsing was successful, so let's process the command.
    ConstElementPtr response = service_->processScopes(scopes_vector);
    callout_handle.setArgument("response", response);
}

void
HAImpl::continueHandler(hooks::CalloutHandle& callout_handle) {
    ConstElementPtr response = service_->processContinue();
    callout_handle.setArgument("response", response);
}

void
HAImpl::maintenanceNotifyHandler(hooks::CalloutHandle& callout_handle) {
    // Command must always be provided.
    ConstElementPtr command;
    callout_handle.getArgument("command", command);

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

    ConstElementPtr response = service_->processMaintenanceNotify(cancel_op->boolValue());
    callout_handle.setArgument("response", response);
}

void
HAImpl::maintenanceStartHandler(hooks::CalloutHandle& callout_handle) {
    ConstElementPtr response = service_->processMaintenanceStart();
    callout_handle.setArgument("response", response);
}

void
HAImpl::maintenanceCancelHandler(hooks::CalloutHandle& callout_handle) {
    ConstElementPtr response = service_->processMaintenanceCancel();
    callout_handle.setArgument("response", response);
}

void
HAImpl::haResetHandler(hooks::CalloutHandle& callout_handle) {
    ConstElementPtr response = service_->processHAReset();
    callout_handle.setArgument("response", response);
}

void
HAImpl::syncCompleteNotifyHandler(hooks::CalloutHandle& callout_handle) {
    ConstElementPtr response = service_->processSyncCompleteNotify();
    callout_handle.setArgument("response", response);
}

} // end of namespace isc::ha
} // end of namespace isc
