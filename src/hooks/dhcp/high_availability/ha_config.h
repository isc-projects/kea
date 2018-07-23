// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HA_CONFIG_H
#define HA_CONFIG_H

#include <exceptions/exceptions.h>
#include <http/url.h>
#include <util/state_model.h>
#include <boost/shared_ptr.hpp>
#include <cstdint>
#include <map>
#include <string>

namespace isc {
namespace ha {

/// @brief Exception thrown when configuration validation fails.
class HAConfigValidationError : public Exception {
public:
    HAConfigValidationError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Storage for High Availability configuration.
class HAConfig {
public:

    /// @brief Mode of operation.
    ///
    /// Currently supported modes are:
    /// - load balancing
    /// - hot standby
    enum HAMode {
        LOAD_BALANCING,
        HOT_STANDBY,
    };

    /// @brief HA peer configuration.
    ///
    /// It holds configuration of one of the servers participating in the
    /// high availability configuration. It may represent configuration of
    /// this server or its partner.
    class PeerConfig {
    public:

        /// @brief Server's role in the High Availability setup.
        ///
        /// The following roles are supported:
        /// - primary - server taking part in load balancing or hot standby setup,
        ///   taking leadership over other servers. There must be exactly one primary
        ///   server.
        /// - secondary - server taking part in the load balancing setup. It is a slave
        ///   server to primary. There must be exactly one secondary server in the
        ///   load balancing setup.
        /// - standby - standby server taking part in the hot standby operation. It
        ///   doesn't run DHCP function until primary server crashes. There must be
        ///   exactly one standby server in the hot standby setup.
        /// - backup server - server receiving updates from other servers, but not
        ///   performing any DHCP function until explicitly enabled to do so.
        enum Role {
            PRIMARY,
            SECONDARY,
            STANDBY,
            BACKUP
        };

        /// @brief Constructor.
        PeerConfig();

        /// @brief Returns server name.
        std::string getName() const {
            return (name_);
        }

        /// @brief Sets server name.
        ///
        /// @param name Server name.
        /// @throw BadValue if the server name is empty.
        void setName(const std::string& name);

        /// @brief Returns URL of the server's control channel.
        http::Url getUrl() const {
            return (url_);
        }

        /// @brief Sets server's URL.
        ///
        /// @param url URL value.
        void setUrl(const http::Url& url) {
            url_ = url;
        }

        /// @brief Returns a string identifying a server used in logging.
        ///
        /// The label is constructed from server name and server URL.
        ///
        /// @return String identifying a server.
        std::string getLogLabel() const;

        /// @brief Returns server's role.
        Role getRole() const {
            return (role_);
        }

        /// @brief Sets servers role.
        ///
        /// The following are the supported roles in the textual form:
        /// - primary,
        /// - secondary,
        /// - standby
        /// - backup
        ///
        /// @param role Server role in the textual form.
        void setRole(const std::string& role);

        /// @brief Decodes role provided as a string.
        ///
        /// @param role Role as string.
        /// @return Server role converted from string.
        /// @throw BadValue if the specified role is unsupported.
        static Role stringToRole(const std::string& role);

        /// @brief Returns role name.
        ///
        /// @param role Role which name should be returned.
        /// @return Role name.
        static std::string roleToString(const HAConfig::PeerConfig::Role& role);

        /// @brief Checks if the auto-failover function is enabled for the
        /// server.
        ///
        /// @return true if auto failover function has been enabled for the server.
        bool isAutoFailover() const {
            return (auto_failover_);
        }

        /// @brief Enables/disables auto-failover function for the server.
        ///
        /// @param auto_failover Boolean value indicating if auto-failover function
        /// should be enabled/disabled for the server.
        void setAutoFailover(const bool auto_failover) {
            auto_failover_ = auto_failover;
        }

    private:

        std::string name_;   ///< Server name.
        http::Url url_;      ///< Server URL.
        Role role_;          ///< Server role.
        bool auto_failover_; ///< Auto failover state.

    };

    /// @brief Pointer to the server's configuration.
    typedef boost::shared_ptr<PeerConfig> PeerConfigPtr;

    /// @brief Map of the servers' configurations.
    typedef std::map<std::string, PeerConfigPtr> PeerConfigMap;


    /// @brief Configuration specific to a single HA state.
    class StateConfig {
    public:

        /// @brief Constructor.
        ///
        /// @param state state identifier.
        explicit StateConfig(const int state);

        /// @brief Returns identifier of the state.
        int getState() const {
            return (state_);
        }

        /// @brief Returns pausing mode for the given state.
        util::StatePausing getPausing() const {
            return (pausing_);
        }

        /// @brief Sets pausing mode for the gievn state.
        ///
        /// @param pausing new pausing mode in the textual form. Supported
        /// values are: always, never, once.
        void setPausing(const std::string& pausing);

        /// @brief Converts pausing mode from the textual form.
        ///
        /// @param pausing pausing mode in the textual form. Supported
        /// values are: always, never, once.
        static util::StatePausing stringToPausing(const std::string& pausing);

        /// @brief Returns pausing mode in the textual form.
        ///
        /// @param pausing pausing mode.
        static std::string pausingToString(const util::StatePausing& pausing);

    private:

        /// @brief Idenitifier of state for which configuration is held.
        int state_;

        /// @brief Pausing mode in the given state.
        util::StatePausing pausing_;
    };

    /// @brief Pointer to the state configuration.
    typedef boost::shared_ptr<StateConfig> StateConfigPtr;

    /// @brief State machine configuration information.
    ///
    /// Currently it merely contains a collection of states specific
    /// configurations. In the future it may also contain global
    /// state machine configuration parameters.
    class StateMachineConfig {
    public:

        /// @brief Constructor.
        StateMachineConfig()
            :  states_() {
        }

        /// @brief Returns pointer to the state specific configuration.
        ///
        /// If requested configuration doesn't exist yet, it is created.
        ///
        /// @param state identifier of the state for which configuration
        /// object should be returned.
        ///
        /// @return Pointer to the state configuration.
        StateConfigPtr getStateConfig(const int state);

    private:

        /// @brief Map of configuration for supported states.
        std::map<int, StateConfigPtr> states_;
    };

    /// @brief Pointer to a state machine configuration.
    typedef boost::shared_ptr<StateMachineConfig> StateMachineConfigPtr;

    /// @brief Constructor.
    HAConfig();

    /// @brief Creates and returns pointer to the new peer's configuration.
    ///
    /// This method is called during peers configuration parsing, when the
    /// parser starts reading configuration of the next peer on the list.
    /// It will store parsed values into this object.
    ///
    /// @param name Name of the server for which new configuration should be
    /// created.
    /// @throw BadValue if there is already a configuration for the given
    /// server name.
    PeerConfigPtr selectNextPeerConfig(const std::string& name);

    /// @brief Returns name of this server.
    std::string getThisServerName() const {
        return (this_server_name_);
    }

    /// @brief Sets name of this server.
    ///
    /// @param this_server_name This server name.
    /// @throw BadValue If the provided server name is empty.
    void setThisServerName(const std::string& this_server_name);

    /// @brief Returns mode of operation.
    HAMode getHAMode() const {
        return (ha_mode_);
    }

    /// @brief Sets new mode of operation.
    ///
    /// The following modes of operation are supported:
    /// - load-balancing
    /// - hot-standby
    ///
    /// @param ha_mode High Availability mode operation in textual form.
    /// @throw BadValue if non-supported mode of operation has been specified.
    void setHAMode(const std::string& ha_mode);

    /// @brief Decodes HA mode provided as string.
    ///
    /// @param ha_mode HA mode as string.
    /// @return HA mode converted from string.
    /// @throw BadValue if specified HA mode name is unsupported.
    static HAMode stringToHAMode(const std::string& ha_mode);

    /// @brief Returns HA mode name.
    ///
    /// @param ha_mode HA mode which name should be returned.
    /// @return HA mode name.
    static std::string HAModeToString(const HAMode& ha_mode);

    /// @brief Returns boolean flag indicating whether lease updates
    /// should be sent to the partner.
    bool amSendingLeaseUpdates() const {
        return (send_lease_updates_);
    }

    /// @brief Sets boolean flag indicating whether lease updates should be
    /// sent to the partner.
    ///
    /// Disabling lease updates is useful in cases when lease database
    /// replication is enabled, e.g. MySQL database replication. The database
    /// itself takes care of updating the backup database with new data.
    /// Sending lease updates is enabled by default.
    ///
    /// @param send_lease_updates new value for the flag.
    void setSendLeaseUpdates(const bool send_lease_updates) {
        send_lease_updates_ = send_lease_updates;
    }

    /// @brief Returns boolean flag indicating whether the active servers
    /// should synchronize their lease databases upon startup.
    bool amSyncingLeases() const {
        return (sync_leases_);
    }

    /// @brief Sets boolean flag indicating whether the active servers should
    /// synchronize their lease databases upon startup.
    ///
    /// Disabling lease database synchronization is useful in cases when lease
    /// database replication is enabled. See the description of the
    /// @c setSendLeaseUpdates. Lease database synchronization is enabled by
    /// default on active HA servers.
    ///
    /// @param sync_leases new value for the flag.
    void setSyncLeases(const bool sync_leases) {
        sync_leases_ = sync_leases;
    }

    /// @brief Returns timeout for lease database synchronization.
    ///
    /// @return Timeout in milliseconds.
    uint32_t getSyncTimeout() const {
        return (sync_timeout_);
    }

    /// @brief Sets new lease database syncing timeout in milliseconds.
    ///
    /// @param sync_timeout new timeout for lease database synchornization.
    void setSyncTimeout(const uint32_t sync_timeout) {
        sync_timeout_ = sync_timeout;
    }

    /// @brief Returns heartbeat delay in milliseconds.
    ///
    /// This value indicates the delay in sending a heartbeat command after
    /// last heartbeat or some other command to the partner. A value of zero
    /// disables the heartbeat.
    ///
    /// @return Heartbeat delay in milliseconds.
    uint32_t getHeartbeatDelay() const {
        return (heartbeat_delay_);
    }

    /// @brief Sets new heartbeat delay in milliseconds.
    ///
    /// This value indicates the delay in sending a heartbeat command after
    /// last heartbeat or some other command to the partner. A value of zero
    /// disables the heartbeat.
    ///
    /// @param heartbeat_delay new heartbeat delay value.
    void setHeartbeatDelay(const uint32_t heartbeat_delay) {
        heartbeat_delay_ = heartbeat_delay;
    }

    /// @brief Returns max response delay.
    ///
    /// Max response delay is the maximum time that the server is waiting for
    /// its partner to respond to the heartbeats (and lease updates) before it
    /// assumes the communications interrupted state.
    uint32_t getMaxResponseDelay() const {
        return (max_response_delay_);
    }

    /// @brief Sets new max response delay.
    ///
    /// Max response delay is the maximum time that the server is waiting for
    /// its partner to respond to the heartbeats (and lease updates) before it
    /// assumes the communications interrupted state.
    ///
    /// @param max_response_delay
    void setMaxResponseDelay(const uint32_t max_response_delay) {
        max_response_delay_ = max_response_delay;
    }

    /// @brief Returns maximum time for a client trying to communicate with
    /// DHCP server to complete the transaction.
    ///
    /// @return Maximum delay in milliseconds.
    uint32_t getMaxAckDelay() const {
        return (max_ack_delay_);
    }

    /// @brief Sets maximum time for a client trying to communicate with
    /// DHCP server to completed the transaction.
    ///
    /// @param max_ack_delay maximum time in milliseconds.
    void setMaxAckDelay(const uint32_t max_ack_delay) {
        max_ack_delay_ = max_ack_delay;
    }

    /// @brief Returns maximum number of clients which may fail to communicate
    /// with the DHCP server before entering partner down state.
    ///
    /// @return Maximum number of clients.
    uint32_t getMaxUnackedClients() const {
        return (max_unacked_clients_);
    }

    /// @brief Set maximum number of clients which may fail to communicate
    /// with the DHCP server before entering partner down state.
    ///
    /// @param max_unacked_clients maximum number of clients.
    void setMaxUnackedClients(const uint32_t max_unacked_clients) {
        max_unacked_clients_ = max_unacked_clients;
    }

    /// @brief Returns configuration of the specified server.
    ///
    /// @param name Server name.
    ///
    /// @return Pointer to the partner's configuration.
    /// @throw InvalidOperation if there is no suitable configuration found.
    PeerConfigPtr getPeerConfig(const std::string& name) const;

    /// @brief Returns configuration of the partner which takes part in
    /// failover.
    ///
    /// The server for which the configuration is returned is a "primary",
    /// "secondary" or "standby". This method is typically used to locate
    /// the configuration of the server to which heartbeat command is to
    /// be sent.
    ///
    /// @return Pointer to the partner's configuration.
    /// @throw InvalidOperation if there is no suitable configuration found.
    PeerConfigPtr getFailoverPeerConfig() const;

    /// @brief Returns configuration of this server.
    ///
    /// @return Pointer to the configuration of this server.
    PeerConfigPtr getThisServerConfig() const;

    /// @brief Returns configuration of other servers.
    ///
    /// Returns a map of pointers to the configuration of all servers except
    /// this.
    ///
    /// @return Map of pointers to the servers' configurations.
    PeerConfigMap getOtherServersConfig() const;

    /// @brief Returns configurations of all servers.
    ///
    /// @return Map of pointers to the servers' configurations.
    PeerConfigMap getAllServersConfig() const {
        return (peers_);
    }

    /// @brief Returns state machine configuration.
    ///
    /// @return Pointer to the state machine configuration.
    StateMachineConfigPtr getStateMachineConfig() const {
        return (state_machine_);
    }

    /// @brief Validates configuration.
    ///
    /// @throw HAConfigValidationError if configuration is invalid.
    void validate() const;

    std::string this_server_name_;        ///< This server name.
    HAMode ha_mode_;                      ///< Mode of operation.
    bool send_lease_updates_;             ///< Send lease updates to partner?
    bool sync_leases_;                    ///< Synchronize databases on startup?
    uint32_t sync_timeout_;               ///< Timeout for syncing lease database (ms)
    uint32_t heartbeat_delay_;            ///< Heartbeat delay in milliseconds.
    uint32_t max_response_delay_;         ///< Max delay in response to heartbeats.
    uint32_t max_ack_delay_;              ///< Maximum DHCP message ack delay.
    uint32_t max_unacked_clients_;        ///< Maximum number of unacked clients.
    PeerConfigMap peers_;                 ///< Map of peers' configurations.
    StateMachineConfigPtr state_machine_; ///< State machine configuration.
};

/// @brief Pointer to the High Availability configuration structure.
typedef boost::shared_ptr<HAConfig> HAConfigPtr;

} // end of namespace isc::ha
} // end of namespace isc

#endif
