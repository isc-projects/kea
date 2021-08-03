// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HA_SERVICE_H
#define HA_SERVICE_H

#include <communication_state.h>
#include <ha_config.h>
#include <ha_server_type.h>
#include <lease_update_backlog.h>
#include <query_filter.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <asiolink/tls_socket.h>
#include <cc/data.h>
#include <config/cmd_http_listener.h>
#include <dhcp/pkt4.h>
#include <http/response.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/network_state.h>
#include <hooks/parking_lots.h>
#include <http/client.h>
#include <util/state_model.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <map>
#include <mutex>
#include <vector>

namespace isc {
namespace ha {

/// @brief High availability service.
///
/// This class derives from the @c util::StateModel and implements a
/// state machine for the high availability service in the Kea DHCP
/// server instance.
class HAService : public boost::noncopyable, public util::StateModel {
public:

    /// Finished heartbeat command.
    static const int HA_HEARTBEAT_COMPLETE_EVT = SM_DERIVED_EVENT_MIN + 1;

    /// Finished lease updates commands.
    static const int HA_LEASE_UPDATES_COMPLETE_EVT = SM_DERIVED_EVENT_MIN + 2;

    /// Lease database synchronization failed.
    static const int HA_SYNCING_FAILED_EVT = SM_DERIVED_EVENT_MIN + 3;

    /// Lease database synchronization succeeded.
    static const int HA_SYNCING_SUCCEEDED_EVT = SM_DERIVED_EVENT_MIN + 4;

    /// ha-maintenance-notify command received.
    static const int HA_MAINTENANCE_NOTIFY_EVT = SM_DERIVED_EVENT_MIN + 5;

    /// ha-maintenance-start command received.
    static const int HA_MAINTENANCE_START_EVT = SM_DERIVED_EVENT_MIN + 6;

    /// ha-maintenance-cancel command received.
    static const int HA_MAINTENANCE_CANCEL_EVT = SM_DERIVED_EVENT_MIN + 7;

    /// The heartbeat command failed after receiving ha-sync-complete-notify
    /// command from the partner.
    static const int HA_SYNCED_PARTNER_UNAVAILABLE_EVT = SM_DERIVED_EVENT_MIN + 8;

    /// Control result returned in response to ha-maintenance-notify.
    static const int HA_CONTROL_RESULT_MAINTENANCE_NOT_ALLOWED = 1001;

protected:

    /// @brief Callback invoked when request was sent and a response received
    /// or an error occurred.
    ///
    /// The first argument indicates if the operation passed (when true).
    /// The second argument holds error message.
    /// The third argument holds control status returned.
   typedef std::function<void(const bool, const std::string&, const int)> PostRequestCallback;

    /// @brief Callback invoked when lease database synchronization is complete.
    ///
    /// The first argument indicates if the operation passed (when true).
    /// The second argument holds error message.
    /// The third argument indicates whether the synchronization resulted in
    /// disabling DHCP service on the partner server and has to be
    /// re-enabled.
    typedef std::function<void(const bool, const std::string&, const bool)> PostSyncCallback;

public:

    /// @brief Constructor.
    ///
    /// It clears the DHCP state using origin HA internal command and starts the
    /// state model in waiting state.  Creates and starts the client and the
    /// listener (if one).
    ///
    /// @param io_service Pointer to the IO service used by the DHCP server.
    /// @param config Parsed HA hook library configuration.
    /// @param network_state Object holding state of the DHCP service
    /// (enabled/disabled).
    /// @param server_type Server type, i.e. DHCPv4 or DHCPv6 server.
    HAService(const asiolink::IOServicePtr& io_service,
              const dhcp::NetworkStatePtr& network_state,
              const HAConfigPtr& config,
              const HAServerType& server_type = HAServerType::DHCPv4);

    /// @brief Destructor.
    ///
    /// Stops the client and listener (if one). It clears the DHCP
    /// state using origin HA internal command.
    virtual ~HAService();

    /// @brief Returns HA server type used in object construction.
    HAServerType getServerType() const {
        return (server_type_);
    }

    /// @brief Defines events used by the HA service.
    virtual void defineEvents();

    /// @brief Verifies events used by the HA service.
    virtual void verifyEvents();

    /// @brief Defines states of the HA service.
    virtual void defineStates();

    /// @brief Handler for the "backup" state.
    ///
    /// This is the normal operation state for a backup server. Only
    /// the backup server can be transitioned to this state. The
    /// DHCP service is disabled in this state and the server merely
    /// receives lease updates from the active servers. The backup
    /// server may be manually instructed to enable DHCP service and
    /// serve selected scopes, e.g. when both primary and secondary
    /// (or standby) servers are down.
    ///
    /// This handler disables DHCP service on the first pass. It is
    /// no-op during all subsequent passes.
    void backupStateHandler();

    /// @brief Handler for the "communication-recovery" state.
    ///
    /// This is a handler invoked for the active servers running in
    /// the load-balancing mode. A primary or secondary server may
    /// transition into this state when it detects that the
    /// communication with its partner is failing.
    ///
    /// If the communication is resumed before the server transitions
    /// to the partner-down state, the server will transition back to
    /// the load-balancing state.
    ///
    /// In the communication-recovery state the server remains
    /// responsive to the DHCP clients but does not send lease updates
    /// to the partner. Instead, it collects the lease updates and
    /// tries to send them in bulk when it returns to the
    /// load-balancing state.
    ///
    /// Transitioning into this state is only enabled when delayed-updates-limit
    /// is non-zero.
    ///
    /// A server running in the hot-standby mode is never allowed to
    /// enter this state. In this mode, even a short communication failure
    /// may cause the primary server to transition to the partner-down
    /// state. Consequently, two servers would be responding to
    /// DHCP queries, possibly allocating the same addresses to two
    /// different clients. This doesn't occur in load-balancing mode
    /// because the address pools are required to be split.
    void communicationRecoveryHandler();

    /// @brief Handler for the "hot-standby" and "load-balancing"
    /// states.
    ///
    /// This is a handler invoked for the servers running in the
    /// hot-standby or load-balancing mode, both for the primary
    /// and the standby (or secondary) server.
    ///
    /// In the hot-standby mode, the primary server responds to all
    /// DHCP queries from the clients. The standby server receives
    /// lease updates from the primary, but it doesn't respond to any
    /// DHCP queries. Both servers exchange heartbeats to monitor
    /// each other states. If any of the servers detects a failure
    /// of its partner, it transitions to the "partner-down" state.
    ///
    /// In the load-balancing mode, both servers respond to the DHCP
    /// queries and exchange the heartbeats and lease updates.
    /// If any of the servers detects a failure of its partner,
    /// it transitions to the "partner-down" state.
    ///
    /// If any of the servers in the "hot-standby" or "load-balancing"
    /// state detects that its partner is in the "partner-down" state,
    /// the server transitions to the "waiting" state. Such situation
    /// may occur if the Control Agent of this server crashes but the
    /// DHCP daemon continues to run. The partner will transition to
    /// the "partner-down" state if the failure detection algorithm
    /// (based on "secs" field or "elapsed time" option monitoring)
    /// and this server is considered to be offline based solely on
    /// the fact that it doesn't respond to heartbeats.
    void normalStateHandler();

    /// @brief Handler for the "in-maintenance" state.
    ///
    /// This is a handler invoked when one of the servers detected that
    /// its partner is in the "partner-in-maintenance" state. The server
    /// in this state is awaiting the shutdown by the administrator.
    /// The administrator shuts down the server to perform some planned
    /// maintenance. Meanwhile, the partner in the "partner-in-maintenance"
    /// state responds to all DHCP queries. The server in the
    /// "in-maintenance" state responds to no DHCP queries.
    void inMaintenanceStateHandler();

    /// @brief Handler for "partner-down" state.
    ///
    /// This is a handler invoked for the server which detected a failure
    /// of its partner. The partner was not responding to heartbeats and
    /// did not respond to a number of DHCP queries directed to it. In
    /// some configurations, the server may transition to this state when
    /// the server is not responding to the heartbeats, without checking
    /// whether it responds to DHCP queries ("max-unacked-clients" parameter
    /// is set to 0).
    ///
    /// In the "partner-down" state the server responds to all DHCP queries,
    /// i.e. the queries it would normally respond to and to the queries
    /// to which its partner would respond.
    ///
    /// The backup server would never transition to this state.
    ///
    /// The server will transition from the "partner-down" state to the
    /// "load-balancing" or "hot-standby" state if its partner is in the
    /// "ready" state. In this state, the partner indicates that it has
    /// synchronized its database and is ready to enable its DHCP service.
    ///
    /// If this server finds that the partner is in an unexpected state,
    /// i.e. "load-balancing", "hot-standby" or "partner-down", it transitions
    /// to the "waiting" state to try to resolve the conflict with the partner.
    void partnerDownStateHandler();

    /// @brief Handler for "partner-in-maintenance" state.
    ///
    /// This is a handler invoked for the server which was administratively
    /// transitioned to the "partner-in-maintenance" state. This is the case
    /// when the partner needs to be shutdown for some planned maintenance.
    ///
    /// The server receiving ha-maintenance-start command transitions to this
    /// state. It sends the ha-maintenance-notify command to the partner to cause
    /// the partner to stop responding to the DHCP queries. Next, this server
    /// starts responding to all DHCP queries. This allows the server
    /// administrator to safely shutdown the partner as it is no longer
    /// responsible for any portion of the DHCP traffic.
    ///
    /// The server in the "partner-in-maintenance" state remains in this state
    /// until the first unsuccessful lease update, ha-heartbeat or any
    /// other command send to the partner due to the issues with communication.
    /// In that case the server assumes that the partner has been shutdown
    /// and transitions to the "partner-down" state in which it still responds
    /// to all DHCP queries but doesn't attempt to send lease updates to the
    /// offline partner.
    void partnerInMaintenanceStateHandler();

    /// @brief Handler for "passive-backup" state.
    ///
    /// This handler is invoked for the server entering the "passive-backup"
    /// state. The primary server enters this state in the "passive-backup"
    /// mode of operation in which there is one server responding to the
    /// DHCP queries and zero, one or more backup servers which receive
    /// lease updates from this server.
    void passiveBackupStateHandler();

    /// @brief Handler for "ready" state.
    ///
    /// This a handler invoked for the server which finished synchronizing
    /// its lease database with the partner and is indicating readiness to
    /// start normal operation, i.e. load balancing or hot standby. The
    /// partner in the "partner-down" state will transition to the
    /// "load-balancing" or "hot-standby" state. The "ready" server will
    /// also transition to one of these states following the transition
    /// of the partner.
    ///
    /// If both servers appear to be in the "ready" state, the primary
    /// server transitions to the "load-balancing" or "hot-standby" state
    /// first.
    ///
    /// The server in the "ready" state is not responding to the DHCP queries.
    void readyStateHandler();

    /// @brief Handler for "syncing" state.
    ///
    /// This is a handler invoked for the server in the "syncing" state.
    /// The server in this state is trying to retrieve leases from
    /// the partner's database and update its local database. Every
    /// primary, secondary and standby server must transition via this
    /// state to retrieve up to date lease information from the active
    /// partner. If the partner is offline the server will eventually
    /// transition to the "partner-down" state without synchronizing
    /// the lease database.
    ///
    /// The lease database synchronization is performed synchronously,
    /// i.e. the handler doesn't return until the synchronization completes
    /// or a communication failure occurs.
    ///
    /// The server in the "syncing" state is not responding to the DHCP queries.
    void syncingStateHandler();

    /// @brief Handler for "terminated" state.
    ///
    /// This is a handler invoked for the server in the "terminated" state.
    /// This indicates that the HA service is disabled, typically as a result
    /// of an unrecoverable error such as detecting that clocks skew between
    /// the active HA servers being too large. This situation requires
    /// manual intervention of an administrator. When the problem is corrected,
    /// the HA service needs to be restarted.
    ///
    /// @note Currently, restarting the HA service requires restarting the
    /// DHCP server. In the future, we will provide a command to restart
    /// the HA service.
    ///
    /// The server in the "terminated" state will respond to DHCP clients
    /// as if it was in a hot-standby or load-balancing state. However, it will
    /// neither send nor receive lease updates. It also won't send heartbeats
    /// to the partner.
    void terminatedStateHandler();

    /// @brief Handler for "waiting" state.
    ///
    /// This is a handler invoked for the server in the "waiting" state.
    /// This is the first state of every server after its startup. The
    /// server initiates a heartbeat to learn the state of its partner.
    /// If the partner is operating (e.g. is in the "partner-down" state),
    /// the server will transition to the "syncing" state to fetch
    /// lease information from the partner. If leases synchronization is
    /// administratively disabled with 'sync-leases' parameter, the server
    /// will transition directly to the "ready" state. If both servers are
    /// in the "waiting" state the primary transitions to the "syncing" or
    /// "ready" state first. If the partner is in the "syncing" state,
    /// this server will remain in the "waiting" state until the partner
    /// completes synchronization.
    ///
    /// If the server starts, but the partner appears to be offline, the
    /// server transitions to the "partner-down" state.
    ///
    /// A backup server transitions from the "waiting" to the "backup"
    /// state directly.
    ///
    /// The server in the "waiting" state is not responding to the DHCP
    /// queries.
    void waitingStateHandler();

    /// @brief Returns last known state of the partner.
    /// @ref CommunicationState::getPartnerState.
    int getPartnerState() const {
        return (communication_state_->getPartnerState());
    }

protected:

    /// @brief Transitions to a desired state and logs it.
    ///
    /// @param state the new value to assign to the current state.
    void verboseTransition(const unsigned state);

    /// @brief Returns normal operation state for the current configuration.
    ///
    /// @return "load-balancing" for active servers in load balancing mode,
    /// "hot-standby" for active servers in hot-standby mode, "backup" for
    /// backup servers and "passive-backup" for primary server in the
    /// "passive-backup" mode.
    int getNormalState() const;

public:

    /// @brief Unpauses the HA state machine with logging.
    ///
    /// It un-pauses the state machine if it is paused and logs an informational
    /// message. It doesn't log the message if the state machine is not paused.
    ///
    /// @return true if the state machine was unpaused, false if the state
    /// machine was not paused when this method was invoked.
    bool unpause();

protected:

    /// @brief Logs if the server is paused in the current state.
    ///
    /// This method is internally called by the state handlers upon
    /// entry to a new state.
    void conditionalLogPausedState() const;

public:

    /// @brief Instructs the HA service to serve default scopes.
    ///
    /// This method is mostly useful for unit testing. The scopes need to be
    /// enabled to test @c inScope methods invoked via @c HAImpl class.
    void serveDefaultScopes();

    /// @brief Checks if the DHCPv4 query should be processed by this server.
    ///
    /// It also associates the DHCPv4 query with required classes appropriate
    /// to the server that should process the packet and increments counters
    /// of unanswered DHCP queries when in communications interrupted state.
    ///
    /// @param [out] query4 pointer to the DHCPv4 query received. A client class
    /// will be appended to this query instance, appropriate for the server to
    /// process this query, e.g. "HA_server1" if the "server1" should process
    /// the query etc.
    ///
    /// @return true if DHCPv4 query should be processed by this server instance,
    /// false otherwise.
    bool inScope(dhcp::Pkt4Ptr& query4);

    /// @brief Checks if the DHCPv6 query should be processed by this server.
    ///
    /// It also associates the DHCPv6 query with required classes appropriate
    /// to the server that should process the packet and increments counters
    /// of unanswered DHCP queries when in communications interrupted state.
    ///
    /// @param [out] query6 pointer to the DHCPv6 query received. A client class
    /// will be appended to this query instance, appropriate for the server to
    /// process this query, e.g. "HA_server1" if the "server1" should process
    /// the query etc.
    ///
    /// @return true if DHCPv6 query should be processed by this server instance,
    /// false otherwise.
    bool inScope(dhcp::Pkt6Ptr& query6);

private:

    /// @brief Checks if the DHCP query should be processed by this server.
    ///
    /// This is a generic implementation of the public @c inScope method
    /// variants.
    ///
    /// @tparam QueryPtrType type of the pointer to the DHCP query.
    /// @param [out] query6 pointer to the DHCP query received. A client class
    /// will be appended to this query instance, appropriate for the server to
    /// process this query, e.g. "HA_server1" if the "server1" should process
    /// the query etc.
    ///
    /// @return true if DHCP query should be processed by this server instance,
    /// false otherwise.
    template<typename QueryPtrType>
    bool inScopeInternal(QueryPtrType& query);

public:

    /// @brief Enables or disables network state depending on the served scopes.
    ///
    /// This method is called in each HA state to enable/disable DHCP service
    /// as appropriate for that state.
    void adjustNetworkState();

protected:

    /// @brief Indicates if the server should transition to the partner down
    /// state.
    ///
    /// It indicates that the server should transition to the partner down
    /// state when the communications is interrupted (over the control channel)
    /// and the partner is not answering DHCP queries in the load balancing
    /// case and in the hot standby case, when this server is a secondary.
    ///
    /// In the hot standby case, when the server is primary, the communications
    /// interrupted is enough to transition to the partner down state.
    ///
    /// @return true if the server should transition to the partner down state,
    /// false otherwise.
    bool shouldPartnerDown() const;

    /// @brief Indicates if the server should transition to the terminated
    /// state as a result of high clock skew.
    ///
    /// It indicates that the server should transition to the terminated
    /// state because of the clock skew being too high. If the clock skew is
    /// is higher than 30 seconds but lower than 60 seconds this method
    /// only logs a warning. In case, the clock skew exceeds 60 seconds, this
    /// method logs a warning and returns true.
    ///
    /// @return true if the server should transition to the terminated state,
    /// false otherwise.
    bool shouldTerminate() const;

    /// @brief Convenience method checking if the current state is a result
    /// of canceling the maintenance.
    ///
    /// @return true if the maintenance was canceled, false otherwise.
    bool isMaintenanceCanceled() const;

    /// @brief Indicates if the partner's state is invalid.
    ///
    /// Partner's state is invalid from the local server's perspective when the
    /// remote server can't transition to this state if the configuration is
    /// consistent with the local server's configuration.
    ///
    /// The following cases are currently checked:
    /// - partner in communication-recovery state but this server not in the
    ///   load balancing mode,
    /// - partner in the hot-standby state but this server not in the hot standby
    ///   mode,
    /// - partner in the load-balancing state but this server not in the
    ///   load balancing mode.
    ///
    /// @return true if the partner's state is invalid, false otherwise.
    bool isPartnerStateInvalid() const;

public:

    /// @brief Schedules asynchronous IPv4 leases updates.
    ///
    /// This method schedules asynchronous lease updates as a result of the
    /// "leases4_committed" callout. The lease updates are transmitted over
    /// HTTP to the peers specified in the configuration (except self).
    /// If the server is in the partner-down state the lease updates are not
    /// sent to the partner but they are sent to all backup servers.
    /// In other states in which the server responds to DHCP queries, the
    /// lease updates are sent to all servers. The scheduled lease updates
    /// are performed after the callouts return. The server parks the
    /// processed DHCP packet and runs IO service shared between the server
    /// and the hook library.
    ////
    /// If the lease update to the partner (primary, secondary or standby)
    /// fails, the parked packet is dropped. If the lease update to any of
    /// the backup server fails, an error message is logged but the DHCP
    /// packet is not dropped.
    ///
    /// This method must be called only if there is at least one lease
    /// altered.
    ///
    /// @param query Pointer to the processed DHCP client message.
    /// @param leases Pointer to a collection of the newly allocated or
    /// updated leases.
    /// @param deleted_leases Pointer to a collection of the released leases.
    /// @param [out] parking_lot Pointer to the parking lot handle available
    /// for the "leases4_committed" hook point. This is where the DHCP client
    /// message is parked. This method calls @c unpark() on this object when
    /// the asynchronous updates are completed.
    ///
    /// @return Number of peers to whom lease updates have been scheduled
    /// to be sent and from which we expect a response prior to unparking
    /// the packet and sending a response to the DHCP client.
    size_t asyncSendLeaseUpdates(const dhcp::Pkt4Ptr& query,
                                 const dhcp::Lease4CollectionPtr& leases,
                                 const dhcp::Lease4CollectionPtr& deleted_leases,
                                 const hooks::ParkingLotHandlePtr& parking_lot);

    /// @brief Schedules asynchronous IPv6 lease updates.
    ///
    /// This method schedules asynchronous IPv6 lease updates as a result of the
    /// "leases6_committed" callout. It works analogously to the IPv4 version of
    /// this function.
    ///
    /// @param query Pointer to the processed DHCP client message.
    /// @param leases Pointer to a collection of the newly allocated or
    /// updated leases.
    /// @param deleted_leases Pointer to a collection of the released leases.
    /// @param [out] parking_lot Pointer to the parking lot handle available
    /// for the "leases6_committed" hook point. This is where the DHCP client
    /// message is parked. This method calls @c unpark() on this object when
    /// the asynchronous updates are completed.
    ///
    /// @return Number of peers to whom lease updates have been scheduled
    /// to be sent and from which we expect a response prior to unparking
    /// the packet and sending a response to the DHCP client.
    size_t asyncSendLeaseUpdates(const dhcp::Pkt6Ptr& query,
                                 const dhcp::Lease6CollectionPtr& leases,
                                 const dhcp::Lease6CollectionPtr& deleted_leases,
                                 const hooks::ParkingLotHandlePtr& parking_lot);

protected:

    /// @brief Asynchronously sends lease update to the peer.
    ///
    /// @param query Pointer to the DHCP client's query.
    /// @param config Pointer to the configuration of the server to which the
    /// command should be sent.
    /// @param command Pointer to the command to be sent.
    /// @param [out] parking_lot Parking lot where the query is parked.
    /// This method uses this handle to unpark the packet when all asynchronous
    /// requests have been completed.
    /// @tparam QueryPtrType Type of the pointer to the DHCP client's message,
    /// i.e. Pkt4Ptr or Pkt6Ptr.
    /// @throw Unexpected when an unexpected error occurs.
    template<typename QueryPtrType>
    void asyncSendLeaseUpdate(const QueryPtrType& query,
                              const HAConfig::PeerConfigPtr& config,
                              const data::ConstElementPtr& command,
                              const hooks::ParkingLotHandlePtr& parking_lot);

    /// @brief Log failed lease updates.
    ///
    /// Logs failed lease updates included in the "failed-deleted-leases"
    /// and/or "failed-leases" carried in the response to the
    /// @c lease6-bulk-apply command.
    ///
    /// @param query Pointer to the DHCP client's query.
    /// @param args Arguments of the response. It may be null, in which
    /// case the function simply returns.
    void logFailedLeaseUpdates(const dhcp::PktPtr& query,
                               const data::ConstElementPtr& args) const;

    /// @brief Checks if the lease updates should be sent as result of leases
    /// allocation or release.
    ///
    /// This method checks if the lease updates should be sent by the server
    /// while this server is in the given state. Note that the backup server
    /// will never send lease updates.
    ///
    /// @param peer_config pointer to the configuration of the peer to which
    /// the updates are to be sent.
    /// @return true if the server should send lease updates, false otherwise.
    bool shouldSendLeaseUpdates(const HAConfig::PeerConfigPtr& peer_config) const;

    /// @brief Checks if the lease updates should be queued.
    ///
    /// If lease updates should be sent to the partner but the server is in
    /// the communication-recovery state (temporarily unavailable) the lease
    /// updates should be queued and later sent when the communication is
    /// re-established. This function checks if the server is in the state
    /// in which lease updates should be queued.
    ///
    /// @param peer_config pointer to the configuration of the peer to which
    /// the updates are to be sent.
    /// @return true if the server should queue lease updates, false otherwise.
    bool shouldQueueLeaseUpdates(const HAConfig::PeerConfigPtr& peer_config) const;

public:

    /// @brief Processes ha-heartbeat command and returns a response.
    ///
    /// This method processes a ha-heartbeat command sent by a peer. This
    /// command is sent periodically to the server to detect its state. The
    /// servers use the heartbeat mechanism to detect peers' failures and to
    /// synchronize their operations when they start up after the failure or
    /// a restart.
    ///
    /// The ha-heartbeat command takes no arguments. The response contains
    /// a server state, served scopes and timestamp in the following format:
    ///
    /// @code
    /// {
    ///     "arguments": {
    ///         "date-time": "Thu, 01 Feb 2018 21:18:26 GMT",
    ///         "scopes": [ "server1" ],
    ///         "state": "waiting"
    ///     },
    ///     "result": 0,
    ///     "text": "HA peer status returned."
    /// }
    /// @endcode
    ///
    /// @return Pointer to the response to the heartbeat.
    data::ConstElementPtr processHeartbeat();

    /// @brief Processes status-get command and returns a response.
    ///
    /// @c HAImpl::commandProcessed calls this to add information about the
    /// HA servers status into the status-get response.
    data::ConstElementPtr processStatusGet() const;

    /// @brief Processes ha-reset command and returns a response.
    ///
    /// This method processes ha-reset command which instructs the server to
    /// transition to the waiting state. A partner may send this command when
    /// the communication is re-established between the servers in the
    /// communication-recovery state and full lease database synchronization is
    /// required. This command may also be sent by an operator if the server's
    /// state is invalid and the reset operation may help correct the situation.
    ///
    /// The ha-reset takes no arguments.
    ///
    /// @return Pointer to a response to the ha-reset command.
    data::ConstElementPtr processHAReset();

protected:

    /// @brief Starts asynchronous heartbeat to a peer.
    void asyncSendHeartbeat();

    /// @brief Schedules asynchronous heartbeat to a peer if it is not scheduled.
    ///
    /// The heartbeat will be sent according to the value of the heartbeat-delay
    /// setting in the HA configuration. This is one shot heartbeat. The callback
    /// will reschedule it.
    void scheduleHeartbeat();

    /// @brief Unconditionally starts one heartbeat to a peer.
    void startHeartbeat();

    /// @brief Schedules asynchronous "dhcp-disable" command to the specified
    /// server.
    ///
    /// @param http_client reference to the client to be used to communicate
    /// with the other server.
    /// @param server_name name of the server to which the command should be
    /// sent.
    /// @param max_period maximum number of seconds for which the DHCP service
    /// should be disabled.
    /// @param post_request_action pointer to the function to be executed when
    /// the request is completed.
    void asyncDisableDHCPService(http::HttpClient& http_client,
                                 const std::string& server_name,
                                 const unsigned int max_period,
                                 PostRequestCallback post_request_action);

    /// @brief Schedules asynchronous "dhcp-enable" command to the specified
    /// server.
    ///
    /// @param http_client reference to the client to be used to communicate
    /// with the other server.
    /// @param server_name name of the server to which the command should be
    /// sent.
    /// @param post_request_action pointer to the function to be executed when
    /// the request is completed.
    void asyncEnableDHCPService(http::HttpClient& http_client,
                                const std::string& server_name,
                                PostRequestCallback post_request_action);

    /// @brief Disables local DHCP service.
    void localDisableDHCPService();

    /// @brief Enables local DHCP service.
    void localEnableDHCPService();

    /// @brief Asynchronously reads leases from a peer and updates local
    /// lease database.
    ///
    /// This method asynchronously sends lease4-get-page command to fetch
    /// leases from the HA peer database. When the response is received, the
    /// callback function iterates over the returned leases and inserts those
    /// that are not present in the local database and replaces any existing
    /// leases if the fetched lease instance is newer (based on cltt) than
    /// the instance in the local lease database.
    ///
    /// If there is an error while inserting or updating any of the leases
    /// a warning message is logged and the process continues for the
    /// remaining leases.
    ///
    /// This method variant uses default HTTP client for communication.
    void asyncSyncLeases();

    /// @brief Asynchronously reads leases from a peer and updates local
    /// lease database using a provided client instance.
    ///
    /// This method first sends dhcp-disable command to the server from which
    /// it will be fetching leases to disable its DHCP function while database
    /// synchronization is in progress. If the command is successful, it then
    /// sends lease4-get-page command to fetch a page of leases from the
    /// partner's database. Depending on the configured page size, it may
    /// be required to send multiple lease4-get-page or lease6-get-page
    /// commands to fetch all leases. If the lease database is large,
    /// the database synchronization may even take several minutes.
    /// Therefore, dhcp-disable command is sent prior to fetching each page,
    /// in order to reset the timeout for automatic re-enabling of the
    /// DHCP service on the remote server. Such timeout must only occur
    /// if there was no communication from the synchronizing server for
    /// longer period of time. If the synchronization is progressing the
    /// timeout must be deferred.
    ///
    /// The @c asyncSyncLeases method calls itself (recurses) when the previous
    /// @c lease4-get-page or @c lease6-get-page command has completed
    /// successfully. If the last page of leases was fetched or if any
    /// error occurred, the synchronization is terminated and the
    /// @c post_sync_action callback is invoked.
    ///
    /// The last parameter passed to the @c post_sync_action callback indicates
    /// whether this server has successfully disabled DHCP service on
    /// the partner server at least once. If that's the case, the DHCP
    /// service must be re-enabled by sending dhcp-enable command. This
    /// is done in the @c HAService::synchronize method.
    ///
    /// If there is an error while inserting or updating any of the leases
    /// a warning message is logged and the process continues for the
    /// remaining leases.
    ///
    /// @param http_client reference to the client to be used to communicate
    /// with the other server.
    /// @param server_name name of the server to fetch leases from.
    /// @param max_period maximum number of seconds to disable DHCP service
    /// @param last_lease Pointer to the last lease returned on the previous
    /// page of leases. This lease is used to set the value of the "from"
    /// parameter in the @c lease4-get-page and @c lease6-get-page commands. If this
    /// command is sent to fetch the first page, the @c last_lease parameter
    /// should be set to null.
    /// @param post_sync_action pointer to the function to be executed when
    /// lease database synchronization is complete. If this is null, no
    /// post synchronization action is invoked.
    /// @param dhcp_disabled Boolean flag indicating if the remote DHCP
    /// server is disabled. This flag propagates down to the
    /// @c post_sync_action to indicate whether the DHCP service has to
    /// be enabled after the leases synchronization.
    void asyncSyncLeases(http::HttpClient& http_client,
                         const std::string& server_name,
                         const unsigned int max_period,
                         const dhcp::LeasePtr& last_lease,
                         PostSyncCallback post_sync_action,
                         const bool dhcp_disabled = false);

    /// @brief Implements fetching one page of leases during synchronization.
    ///
    /// This method implements the actual lease fetching from the partner
    /// and synchronization of the database. It excludes sending @c dhcp-disable
    /// command. This command is sent by @c HAService::asyncSyncLeases.
    ///
    /// When the page of leases is successfully synchronized, this method
    /// will call @c HAService::asyncSyncLeases to schedule synchronization of
    /// the next page of leases.
    ///
    /// @param http_client reference to the client to be used to communicate
    /// with the other server.
    /// @param server_name name of the server to fetch leases from.
    /// @param max_period maximum number of seconds to disable DHCP service
    /// @param last_lease Pointer to the last lease returned on the previous
    /// page of leases. This lease is used to set the value of the "from"
    /// parameter in the lease4-get-page and lease6-get-page commands. If this
    /// command is sent to fetch the first page, the @c last_lease parameter
    /// should be set to null.
    /// @param post_sync_action pointer to the function to be executed when
    /// lease database synchronization is complete. If this is null, no
    /// post synchronization action is invoked.
    /// @param dhcp_disabled Boolean flag indicating if the remote DHCP
    /// server is disabled. This flag propagates down to the
    /// @c post_sync_action to indicate whether the DHCP service has to
    /// be enabled after the leases synchronization.
    void asyncSyncLeasesInternal(http::HttpClient& http_client,
                                 const std::string& server_name,
                                 const unsigned int max_period,
                                 const dhcp::LeasePtr& last_lease,
                                 PostSyncCallback post_sync_action,
                                 const bool dhcp_disabled);

public:

    /// @brief Processes ha-sync command and returns a response.
    ///
    /// This method processes ha-sync command. It instructs the server
    /// to disable the DHCP service on the HA peer, fetch all leases from
    /// the peer and update the local lease database. Leases synchronization
    /// is usually performed automatically by the server which starts up for
    /// the first time or after a failure. However, the ha-sync command can
    /// also be triggered manually by the server administrator to force
    /// synchronization of the lease database in cases when manual recovery
    /// is required. One of the possible cases is when the lease database has
    /// to be recovered from the backup server, e.g. when both primary and
    /// secondary (or standby) servers have crashed.
    ///
    /// @param server_name name of the server to fetch leases from.
    /// @param max_period maximum number of seconds to disable DHCP service
    /// of the peer. This value is used in dhcp-disable command issued to
    /// the peer before the lease4-get-page command.
    ///
    /// @return Pointer to the response to the ha-sync command.
    data::ConstElementPtr processSynchronize(const std::string& server_name,
                                             const unsigned int max_period);

protected:

    /// @brief Synchronizes lease database with a partner.
    ///
    /// It instructs the server to disable the DHCP service on the HA peer,
    /// fetch all leases from the peer and update the local lease database.
    /// It sends ha-sync-complete-notify command to the partner when the
    /// synchronization completes successfully. If the partner does not
    /// support this command, it sends dhcp-enable command to enable
    /// the DHCP service on the partner.
    ///
    /// This method creates its own instances of the HttpClient and IOService and
    /// invokes IOService::run().
    ///
    /// @param [out] status_message status message in textual form.
    /// @param server_name name of the server to fetch leases from.
    /// @param max_period maximum number of seconds to disable DHCP service
    /// of the peer. This value is used in dhcp-disable command issued to
    /// the peer before the lease4-get-page command.
    ///
    /// @return Synchronization result according to the status codes returned
    /// in responses to control commands.
    int synchronize(std::string& status_message, const std::string& server_name,
                    const unsigned int max_period);

    /// @brief Sends lease updates from backlog to partner asynchronously.
    ///
    /// This method checks if there are any outstanding DHCPv4 or DHCPv6 leases
    /// in the backlog and schedules asynchronous sends of these leases. In
    /// DHCPv6 case it sends a single lease6-bulk-apply command with all
    /// outstanding leases. In DHCPv4 case, it sends lease4-update or lease4-delete
    /// commands recursively (when one lease update completes successfully it
    /// schedules sending next lease update).
    ///
    /// If there are no lease updates in the backlog it calls @c post_request_action
    /// callback.
    ///
    /// This method is called from @c sendLeaseUpdatesFromBacklog.
    ///
    /// @param http_client reference to the HTTP client to be used for communication.
    /// @param remote_config pointer to the remote server's configuration.
    /// @param post_request_action callback to be invoked when the operation
    /// completes. It can be used for handling errors.
    void asyncSendLeaseUpdatesFromBacklog(http::HttpClient& http_client,
                                          const HAConfig::PeerConfigPtr& remote_config,
                                          PostRequestCallback post_request_action);

    /// @brief Attempts to send all lease updates from the backlog synchronously.
    ///
    /// This method is called upon exiting communication-recovery state and before
    /// entering the load-balancing state. It ensures that all outstanding lease
    /// updates are sent to the partner before the server can continue normal
    /// operation in the load-balancing state. In order to prevent collisions
    /// between new allocations and outstanding updates this method is synchronous.
    ///
    /// This method creates its own instances of the HttpClient and IOService and
    /// invokes IOService::run().
    ///
    /// @return boolean value indicating that the lease updates were delivered
    /// successfully (when true) or unsuccessfully (when false).
    bool sendLeaseUpdatesFromBacklog();

    /// @brief Sends ha-reset command to partner asynchronously.
    ///
    /// @param http_client reference to the HTTP client to be used for communication.
    /// @param remote_config pointer to the remote server's configuration.
    /// @param post_request_action callback to be invoked when the operation
    /// completes. It can be used for handling errors.
    void asyncSendHAReset(http::HttpClient& http_client,
                          const HAConfig::PeerConfigPtr& remote_config,
                          PostRequestCallback post_request_action);

    /// @brief Sends ha-reset command to partner synchronously.
    ///
    /// This method attempts to send ha-reset command to the active partner
    /// synchronously. It may be invoked when the communication with the partner
    /// is re-established after temporary failure. It causes the partner to
    /// transition the partner to the waiting state. This effectively means that
    /// the partner will synchronize its lease database with this server.
    ///
    /// This method creates its own instances of the HttpClient and IOService and
    /// invokes IOService::run().
    ///
    /// @return true if the command was sent successfully, false otherwise.
    bool sendHAReset();

public:

    /// @brief Processes ha-scopes command and returns a response.
    ///
    /// @param scopes vector of scope names to be enabled.
    ///
    /// @return Pointer to the response to the ha-scopes command.
    data::ConstElementPtr processScopes(const std::vector<std::string>& scopes);

    /// @brief Processes ha-continue command and returns a response.
    ///
    /// @return Pointer to the response to the ha-continue command.
    data::ConstElementPtr processContinue();

    /// @brief Processes ha-maintenance-notify command and returns a response.
    ///
    /// This command attempts to transition the server to the in-maintenance state
    /// if the cancel flag is set to false. Such transition is not allowed if
    /// the server is currently in one of the following states:
    /// - backup: because maintenance is not supported for backup servers,
    /// - partner-in-maintenance: because only one server is in maintenance while
    ///   the partner must be in partner-in-maintenance state,
    /// - terminated: because the only way to resume HA service is by shutting
    ///   down the server, fixing the clock skew and restarting.
    ///
    /// If the cancel flag is set to true, the server will be transitioned from
    /// the in-maintenance state to the previous state it was in before entering
    /// the in-maintenance state.
    ///
    /// @param cancel boolean value indicating if the maintenance is being
    /// canceled with this operation. If it is set to false the maintenance
    /// is being started.
    ///
    /// @return Pointer to the response to the ha-maintenance-notify.
    data::ConstElementPtr processMaintenanceNotify(const bool cancel);

    /// @brief Processes ha-maintenance-start command and returns a response.
    ///
    /// The server receiving this command will try to send the
    /// ha-maintenance-notify command to the partner to instruct the partner
    /// to transition to the in-maintenance state. In this state the partner will
    /// not respond to any DHCP queries. Next, this server will transition to
    /// the partner-in-maintenance state and therefore will start responding
    /// to all DHCP queries. If the partner responds to the ha-maintenance-notify
    /// with an error, this server won't transition to the partner-in-maintenance
    /// state and signal an error to the caller. If the partner is unavailable,
    /// this server will directly transition to the partner-down state.
    ///
    /// This method creates its own instances of the HttpClient and IOService and
    /// invokes IOService::run().
    ///
    /// @return Pointer to the response to the ha-maintenance-start.
    data::ConstElementPtr processMaintenanceStart();

    /// @brief Processes ha-maintenance-cancel command and returns a response.
    ///
    /// The server receiving this command will try to revert the partner's
    /// state from the in-maintenance to the previous state, and also it will
    /// try to revert its own state from the partner-in-maintenance to the
    /// previous state. It effectively means canceling the request for
    /// maintenance signaled with the ha-maintenance-start command.
    ///
    /// In some cases canceling the maintenance is no longer possible, e.g.
    /// if the server has already got into the partner-down state. Generally,
    /// canceling the maintenance is only possible if this server is in the
    /// partner-in-maintenance state and the partner is in the in-maintenance
    /// state.
    ///
    /// @return Pointer to the response to the ha-maintenance-cancel.
    data::ConstElementPtr processMaintenanceCancel();

    /// @brief Check client and(or) listener current thread permissions to
    /// perform thread pool state transition.
    ///
    /// @throw MultiThreadingInvalidOperation if the state transition is done on
    /// any of the worker threads.
    void checkPermissionsClientAndListener();

protected:

    /// @brief Schedules asynchronous "ha-sync-complete-notify" command to the
    /// specified server.
    ///
    /// @param http_client reference to the client to be used to communicate
    /// with the other server.
    /// @param server_name name of the server to which the command should be
    /// sent.
    /// @param post_request_action pointer to the function to be executed when
    /// the request is completed.
    void asyncSyncCompleteNotify(http::HttpClient& http_client,
                                 const std::string& server_name,
                                 PostRequestCallback post_request_action);

public:

    /// @brief Process ha-sync-complete-notify command and returns a response.
    ///
    /// A server finishing a lease database synchronization may notify its
    /// partner about it with this command. This function implements reception
    /// and processing of the command.
    ///
    /// It enables DHCP service unless the server is in the partner-down state.
    /// In this state, the server will first have to check connectivity with
    /// the partner and transition to a state in which it will send lease updates.
    ///
    /// @return Pointer to the response to the ha-sync-complete-notify command.
    data::ConstElementPtr processSyncCompleteNotify();

    /// @brief Start the client and(or) listener instances.
    ///
    /// When HA+MT is enabled it starts the client's thread pool
    /// and the dedicated listener thread pool, if the listener exists.
    /// It registers pauseClientAndListener() and resumeClientAndListener()
    /// as the MultiThreading critical section entry and exit callbacks,
    /// respectively.
    void startClientAndListener();

    /// @brief Pauses client and(or) listener thread pool operations.
    ///
    /// Suspends the client and listener thread pool event processing.
    /// Has no effect in single-threaded mode or if thread pools are
    /// not currently running.  Serves as the MultiThreading critical
    /// section entry callback.
    void pauseClientAndListener();

    /// @brief Resumes client and(or) listener thread pool operations.
    ///
    /// Resumes the client and listener thread pool event processing.
    /// Has no effect in single-threaded mode or if thread pools are
    /// not currently paused. Serves as the MultiThreading critical
    /// section exit callback.
    void resumeClientAndListener();

    /// @brief Stop the client and(or) listener instances.
    ///
    /// It unregisters the MultiThreading critical section callbacks,
    /// closes all connections and stops the thread pools for the client
    /// and listener, if they exist.
    void stopClientAndListener();

protected:

    /// @brief Checks if the response is valid or contains an error.
    ///
    /// The response must be non-null, must contain a JSON body and must
    /// contain a success status code.
    ///
    /// @param response pointer to the received response.
    /// @param [out] rcode result found in the response.
    /// @return Pointer to the response arguments.
    /// @throw CtrlChannelError if response is invalid or contains an error.
    /// @throw CommandUnsupportedError if sent command is unsupported.
    data::ConstElementPtr verifyAsyncResponse(const http::HttpResponsePtr& response,
                                              int& rcode);

    /// @brief HttpClient connect callback handler
    ///
    /// Passed into HttpClient calls to allow registration of client's TCP socket
    /// with an external monitor (such as IfaceMgr's  main-thread select()).
    ///
    /// @param ec Error status of the ASIO connect
    /// @param tcp_native_fd socket descriptor to register
    /// @return always true. Registration cannot fail, and if ec indicates a real
    /// error we want Connection logic to process it.
    bool clientConnectHandler(const boost::system::error_code& ec, int tcp_native_fd);

    /// @brief HttpClient handshake callback handler
    ///
    /// Currently is never called and does nothing.
    ///
    /// @return always true.
    bool clientHandshakeHandler(const boost::system::error_code&) {
        return (true);
    }

    /// @brief IfaceMgr external socket ready callback handler
    ///
    /// IfaceMgr invokes this call back when a registered socket has been
    /// flagged as ready to read.   It is installed by the invocation to
    /// register the socket with IfaceMgr made in @ref clientConnectHandler.
    ///
    /// The handler calls @c http::HttpClient::closeIfOutOfBand() to catch
    /// and close any sockets that have gone ready outside of transactions.
    ///
    /// We do this in case the other peer closed the socket (e.g. idle timeout),
    /// as this will cause the socket to appear ready to read to the
    /// IfaceMgr::select(). If this happens while no transactions are
    /// in progress, we won't have anything to deal with the socket event.
    /// This causes IfaceMgr::select() to endlessly interrupt on the socket.
    ///
    /// @param tcp_native_fd socket descriptor of the ready socket
    void socketReadyHandler(int tcp_native_fd);

    /// @brief HttpClient close callback handler
    ///
    /// Passed into HttpClient calls to allow unregistration of client's
    /// TCP socket with an external monitor (such as IfaceMgr's
    /// main-thread select()).
    ///
    /// @param tcp_native_fd socket descriptor to register
    void clientCloseHandler(int tcp_native_fd);

    /// @brief Pointer to the IO service object shared between this hooks
    /// library and the DHCP server.
    asiolink::IOServicePtr io_service_;

    /// @brief Pointer to the state of the DHCP service (enabled/disabled).
    dhcp::NetworkStatePtr network_state_;

    /// @brief Pointer to the HA hooks library configuration.
    HAConfigPtr config_;

    /// @brief DHCP server type.
    HAServerType server_type_;

    /// @brief HTTP client instance used to send HA commands and lease updates.
    http::HttpClientPtr client_;

    /// @brief HTTP listener instance used to receive and respond to HA commands
    /// and lease updates.
    config::CmdHttpListenerPtr listener_;

    /// @brief Holds communication state with a peer.
    CommunicationStatePtr communication_state_;

    /// @brief Selects queries to be processed/dropped.
    QueryFilter query_filter_;

    /// @brief Handle last pending request for this query.
    ///
    /// Search if there are pending requests for this query:
    ///  - if there are decrement the count
    ///  - if there were at least two return false
    ///  - if there was none or one unpark the query
    ///  - if there was one remove the query from the map
    ///  - return true
    ///
    /// @tparam QueryPtrType Type of the pointer to the DHCP client's message,
    /// i.e. Pkt4Ptr or Pkt6Ptr.
    /// @param query Pointer to the DHCP client's query.
    /// @param [out] parking_lot Parking lot where the query is parked.
    /// This method uses this handle to unpark the packet when all asynchronous
    /// requests have been completed.
    /// @return When all lease updates are complete returns true, false otherwise.
    template<typename QueryPtrType>
    bool leaseUpdateComplete(QueryPtrType& query,
                             const hooks::ParkingLotHandlePtr& parking_lot);

    /// @brief Update pending request counter for this query.
    ///
    /// @tparam QueryPtrType Type of the pointer to the DHCP client's message,
    /// i.e. Pkt4Ptr or Pkt6Ptr.
    /// @param query Pointer to the DHCP client's query.
    template<typename QueryPtrType>
    void updatePendingRequest(QueryPtrType& query);

    /// @brief Get the number of entries in the pending request map.
    ///
    /// @note Currently for testing purposes only.
    /// @return Number of entries in the pending request map.
    size_t pendingRequestSize();

    /// @brief Get the number of scheduled requests for a given query.
    ///
    /// @note Currently for testing purposes only.
    ///
    /// If there is an entry in the pending request map for the given
    /// query the entry is returned else zero is returned.
    ///
    /// @param query Pointer to the DHCP client's query.
    /// @return Number of scheduled requests for the query or zero.
    template<typename QueryPtrType>
    int getPendingRequest(const QueryPtrType& query);

private:
    /// @brief Handle last pending request for this query.
    ///
    /// Search if there are pending requests for this query:
    ///  - if there are decrement the count
    ///  - if there were at least two return false
    ///  - if there was none or one unpark the query
    ///  - if there was one remove the query from the map
    ///  - return true
    ///
    /// Should be called in a thread safe context.
    ///
    /// @tparam QueryPtrType Type of the pointer to the DHCP client's message,
    /// i.e. Pkt4Ptr or Pkt6Ptr.
    /// @param query Pointer to the DHCP client's query.
    /// @param [out] parking_lot Parking lot where the query is parked.
    /// This method uses this handle to unpark the packet when all asynchronous
    /// requests have been completed.
    /// @return When all lease updates are complete returns true, false otherwise.
    template<typename QueryPtrType>
    bool leaseUpdateCompleteInternal(QueryPtrType& query,
                                     const hooks::ParkingLotHandlePtr& parking_lot);

    /// @brief Update pending request counter for this query.
    ///
    /// Should be called in a thread safe context.
    ///
    /// @tparam QueryPtrType Type of the pointer to the DHCP client's message,
    /// i.e. Pkt4Ptr or Pkt6Ptr.
    /// @param query Pointer to the DHCP client's query.
    template<typename QueryPtrType>
    void updatePendingRequestInternal(QueryPtrType& query);

    /// @brief Get the number of scheduled requests for a given query.
    /// @note Currently for testing purposes only.
    ///
    /// If there is an entry in the pending request map for the given
    /// query the entry is returned else zero is returned.
    ///
    /// Should be called in a thread safe context.
    ///
    /// @param query Pointer to the DHCP client's query.
    /// @return Number of scheduled requests for the query or zero.
    template<typename QueryPtrType>
    int getPendingRequestInternal(const QueryPtrType& query);

    /// @brief Mutex to protect the internal state.
    std::mutex mutex_;

    /// @brief Map holding a number of scheduled requests for a given packet.
    ///
    /// A single callout may send multiple requests at the same time, e.g.
    /// "leases4_committed" may provide multiple deleted leases and multiple
    /// newly allocated leases. The parked packet may be unparked when all
    /// requests have been delivered. Therefore, it is required to count
    /// the number of responses received so far and unpark the packet when
    /// all responses have been received. That's what this map is used for.
    std::map<boost::shared_ptr<dhcp::Pkt>, int> pending_requests_;

protected:

    /// @brief Backlog of DHCP lease updates.
    ///
    /// Unsent lease updates are stored in this queue when the server is in
    /// the communication-recovery state and is temporarily unable to send
    /// lease updates to the partner.
    LeaseUpdateBacklog lease_update_backlog_;

    /// @brief An indicator that a partner sent ha-sync-complete-notify command.
    ///
    /// This indicator is set when the partner finished synchronization. It blocks
    /// enabling DHCP service in the partner-down state. The server will first
    /// send heartbeat to the partner to ensure that the communication is
    /// re-established. If the communication remains broken, the server clears
    /// this flag and enables DHCP service to continue the service.
    bool sync_complete_notified_;
};

/// @brief Pointer to the @c HAService class.
typedef boost::shared_ptr<HAService> HAServicePtr;

} // end of namespace isc::ha
} // end of namespace isc

#endif
