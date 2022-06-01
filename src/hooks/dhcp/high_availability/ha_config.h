// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HA_CONFIG_H
#define HA_CONFIG_H

#include <asiolink/crypto_tls.h>
#include <exceptions/exceptions.h>
#include <http/basic_auth.h>
#include <http/post_request_json.h>
#include <http/url.h>
#include <util/optional.h>
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
    /// - load-balancing
    /// - hot-standby
    /// - passive-backup
    enum HAMode {
        LOAD_BALANCING,
        HOT_STANDBY,
        PASSIVE_BACKUP
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
        /// - primary - server taking part in load balancing, hot standby or
        ///   passive-backup setup, taking leadership over other servers.
        ///   There must be exactly one primary server.
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

        /// @brief Returns server's trust-anchor.
        util::Optional<std::string> getTrustAnchor() const {
            return (trust_anchor_);
        }

        /// @brief Sets server's trust-anchor.
        ///
        /// @param ca Trust anchor aka Certificate Authority.
        void setTrustAnchor(const util::Optional<std::string>& ca) {
            trust_anchor_ = ca;
        }

        /// @brief Returns server's cert-file.
        util::Optional<std::string> getCertFile() const {
            return (cert_file_);
        }

        /// @brief Sets server's cert-file.
        ///
        /// @param cert Certificate file name.
        void setCertFile(const util::Optional<std::string>& cert) {
            cert_file_ = cert;
        }

        /// @brief Returns server's key-file.
        util::Optional<std::string> getKeyFile() const {
            return (key_file_);
        }

        /// @brief Sets server's key-file.
        ///
        /// @param key Private key file name.
        void setKeyFile(const util::Optional<std::string>& key) {
            key_file_ = key;
        }

        /// @brief Returns a pointer to the server's TLS context.
        asiolink::TlsContextPtr getTlsContext() const {
            return (tls_context_);
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

        /// @brief Returns non-const basic HTTP authentication.
        http::BasicHttpAuthPtr& getBasicAuth() {
            return (basic_auth_);
        }

        /// @brief Returns const basic HTTP authentication.
        const http::BasicHttpAuthPtr& getBasicAuth() const {
            return (basic_auth_);
        }

        /// @brief Adds a basic HTTP authentication header to a request
        /// when credentials are specified.
        void addBasicAuthHttpHeader(http::PostHttpRequestJsonPtr request) const;

        /// @brief Server TLS context.
        ///
        /// @note: if you make it protected or private please make
        /// @ref validate a friend so it may configure it.
        asiolink::TlsContextPtr tls_context_;

    private:

        std::string name_;                          ///< Server name.
        http::Url url_;                             ///< Server URL.
        util::Optional<std::string> trust_anchor_;  ///< Server trust anchor.
        util::Optional<std::string> cert_file_;     ///< Server cert file.
        util::Optional<std::string> key_file_;      ///< Server key file.
        Role role_;                                 ///< Server role.
        bool auto_failover_;                        ///< Auto failover state.
        http::BasicHttpAuthPtr basic_auth_;         ///< Basic HTTP authentication.
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

        /// @brief Sets pausing mode for the given state.
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

        /// @brief Identifier of state for which configuration is held.
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
    /// @param sync_timeout new timeout for lease database synchronization.
    void setSyncTimeout(const uint32_t sync_timeout) {
        sync_timeout_ = sync_timeout;
    }

    /// @brief Returns maximum number of leases per page to be fetched
    /// during database synchronization.
    ///
    /// @return Maximum number of leases per page.
    uint32_t getSyncPageLimit() const {
        return (sync_page_limit_);
    }

    /// @brief Sets new page limit size for leases fetched from the partner
    /// during database synchronization.
    ///
    /// @param sync_page_limit New page limit value.
    void setSyncPageLimit(const uint32_t sync_page_limit) {
        sync_page_limit_ = sync_page_limit;
    }

    /// @brief Returns the maximum number of lease updates which can be held
    /// unsent in the communication-recovery state.
    ///
    /// If the server is in the communication-recovery state it is unable to
    /// send lease updates to the partner. Instead it keeps lease updates,
    /// hoping to send them when the communication is resumed. This value
    /// designates a limit of how many such updates can be held. If this
    /// number is exceeded the server continues to respond to the clients
    /// but will have to go through regular lease database synchronization
    /// when the communication is resumed.
    ///
    /// @return Limit of the lease backlog size in communication-recovery.
    uint32_t getDelayedUpdatesLimit() const {
        return (delayed_updates_limit_);
    }

    /// @brief Sets new limit for the number of lease updates to be held
    /// unsent in the communication-recovery state.
    ///
    /// If the server is in the communication-recovery state it is unable to
    /// send lease updates to the partner. Instead it keeps lease updates,
    /// hoping to send them when the communication is resumed. This value
    /// designates a limit of how many such updates can be held. If this
    /// number is exceeded the server continues to respond to the clients
    /// but will have to go through regular lease database synchronization
    /// when the communication is resumed.
    ///
    /// @param delayed_updates_limit new limit.
    void setDelayedUpdatesLimit(const uint32_t delayed_updates_limit) {
        delayed_updates_limit_ = delayed_updates_limit;
    }

    /// @brief Convenience function checking if communication recovery is allowed.
    ///
    /// Communication recovery is only allowed in load-balancing configurations.
    /// It is enabled by setting delayed-updates-limit to a value greater
    /// than 0.
    ///
    /// @return true if communication recovery is enabled, false otherwise.
    bool amAllowingCommRecovery() const {
        return (delayed_updates_limit_ > 0);
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

    /// @brief Configures the server to wait/not wait for the lease update
    /// acknowledgments from the backup servers.
    ///
    /// @param wait_backup_ack indicates that the server should wait for the
    /// lease update acknowledgments from the backup servers (if true) or
    /// that it should not (if false).
    void setWaitBackupAck(const bool wait_backup_ack) {
        wait_backup_ack_ = wait_backup_ack;
    }

    /// @brief Checks if the server is configured to wait for the acknowledgments
    /// to the lease updates from the backup server or not.
    ///
    /// @return true if the server is configured to wait for the acknowledgments
    /// or false otherwise.
    bool amWaitingBackupAck() const {
        return (wait_backup_ack_);
    }

    /// @brief Checks if the server is configured for multi-threaded operation.
    ///
    /// @return true if the server is configured for multi-threaded operation
    bool getEnableMultiThreading() {
        return (enable_multi_threading_);
    }

    /// @brief Sets whether or not server is configured for multi-threaded operation.
    ///
    /// @param enable_multi_threading boolean flag that enables multi-threaded operation
    /// when true.
    void setEnableMultiThreading(bool enable_multi_threading) {
        enable_multi_threading_ = enable_multi_threading;
    }

    /// @brief Checks if the server is configured to use its own HTTP listener.
    ///
    /// When this is true, the server should instantiate an HTTP listener instance
    /// which listens on this server's URL.  If false, this server will rely on
    /// a kea-control-agent.
    ///
    /// @return true if the server is configured to use its own HTTP listener.
    bool getHttpDedicatedListener() {
        return (http_dedicated_listener_);
    }

    /// @brief Sets whether or not the server is configured to use its own HTTP
    /// listener.
    ///
    /// @param http_dedicated_listener flag that enables the use of a dedicated
    /// listener when true.
    void setHttpDedicatedListener(bool http_dedicated_listener) {
        http_dedicated_listener_ = http_dedicated_listener;
    }

    /// @brief Fetches the number of threads the HTTP listener should use.
    ///
    /// @return number of threads the listener is configured to use.
    uint32_t getHttpListenerThreads() {
        return (http_listener_threads_);
    }

    /// @brief Sets the number of threads the HTTP listener should use.
    ///
    /// @param http_listener_threads number of threads the listener should use.
    void setHttpListenerThreads(uint32_t http_listener_threads) {
        http_listener_threads_ = http_listener_threads;
    }

    /// @brief Fetches the number of threads the HTTP client should use.
    ///
    /// @return number of threads the client is configured to use.
    uint32_t getHttpClientThreads() {
        return (http_client_threads_);
    }

    /// @brief Sets the number of threads the HTTP client should use.
    ///
    /// @param http_client_threads number of threads the client should use.
    void setHttpClientThreads(uint32_t http_client_threads) {
        http_client_threads_ = http_client_threads;
    }

    /// @brief Returns global trust-anchor.
    util::Optional<std::string> getTrustAnchor() const {
        return (trust_anchor_);
    }

    /// @brief Sets global trust-anchor.
    ///
    /// @param ca Trust anchor aka Certificate Authority.
    void setTrustAnchor(const util::Optional<std::string>& ca) {
        trust_anchor_ = ca;
    }

    /// @brief Returns global cert-file.
    util::Optional<std::string> getCertFile() const {
        return (cert_file_);
    }

    /// @brief Sets global cert-file.
    ///
    /// @param cert Certificate file name.
    void setCertFile(const util::Optional<std::string>& cert) {
        cert_file_ = cert;
    }

    /// @brief Returns global key-file.
    util::Optional<std::string> getKeyFile() const {
        return (key_file_);
    }

    /// @brief Sets global key-file.
    ///
    /// @param key Private key file name.
    void setKeyFile(const util::Optional<std::string>& key) {
        key_file_ = key;
    }

    /// @brief Returns require-client-certs.
    bool getRequireClientCerts() const {
        return (require_client_certs_);
    }

    /// @brief Sets require-client-certs.
    ///
    /// @param flag Require client certs flag value.
    void setRequireClientCerts(bool flag) {
        require_client_certs_ = flag;
    }

    /// @brief Returns restrict-commands.
    bool getRestrictCommands() const {
        return (restrict_commands_);
    }

    /// @brief Sets restrict-commands.
    ///
    /// @param flag Restrict commands to HA flag value.
    void setRestrictCommands(bool flag) {
        restrict_commands_ = flag;
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
    /// In addition to sanity checking the configuration, it will
    /// check HA+MT configuration against Core multi-threading
    /// configuration add adjust HA+MT values as follows:
    /// 1. If DHCP multi-threading is disabled, HA+MT will be disabled.
    /// 2. If http-listener-threads is 0, it will be replaced with
    /// the number of DHCP threads
    /// 3. If http-client-threads is 0, it will be replaced with
    /// the number of DHCP threads
    ///
    /// As a side effect it fills the TLS context of peers when TLS is enabled.
    ///
    /// @throw HAConfigValidationError if configuration is invalid.
    void validate();

    std::string this_server_name_;            ///< This server name.
    HAMode ha_mode_;                          ///< Mode of operation.
    bool send_lease_updates_;                 ///< Send lease updates to partner?
    bool sync_leases_;                        ///< Synchronize databases on startup?
    uint32_t sync_timeout_;                   ///< Timeout for syncing lease database (ms)
    uint32_t sync_page_limit_;                ///< Page size limit while
                                              ///< synchronizing leases.
    uint32_t delayed_updates_limit_;          ///< Maximum number of lease updates held
                                              ///< for later send in communication-recovery.
    uint32_t heartbeat_delay_;                ///< Heartbeat delay in milliseconds.
    uint32_t max_response_delay_;             ///< Max delay in response to heartbeats.
    uint32_t max_ack_delay_;                  ///< Maximum DHCP message ack delay.
    uint32_t max_unacked_clients_;            ///< Maximum number of unacked clients.
    bool wait_backup_ack_;                    ///< Wait for lease update ack from backup?
    bool enable_multi_threading_;             ///< Enable multi-threading.
    bool http_dedicated_listener_;            ///< Enable use of own HTTP listener.
    uint32_t http_listener_threads_;          ///< Number of HTTP listener threads.
    uint32_t http_client_threads_;            ///< Number of HTTP client threads.
    util::Optional<std::string> trust_anchor_; ///< Trust anchor.
    util::Optional<std::string> cert_file_;    ///< Certificate file.
    util::Optional<std::string> key_file_;     ///< Private key file.
    bool require_client_certs_;                ///< Require client certs flag.
    bool restrict_commands_;                   ///< Restrict commands to HA flag.
    PeerConfigMap peers_;                      ///< Map of peers' configurations.
    StateMachineConfigPtr state_machine_;      ///< State machine configuration.
};

/// @brief Pointer to the High Availability configuration structure.
typedef boost::shared_ptr<HAConfig> HAConfigPtr;

} // end of namespace isc::ha
} // end of namespace isc

#endif
