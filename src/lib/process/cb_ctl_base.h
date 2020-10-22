// Copyright (C) 2019-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CB_CTL_BASE_H
#define CB_CTL_BASE_H

#include <database/audit_entry.h>
#include <database/backend_selector.h>
#include <database/server_selector.h>
#include <process/config_base.h>
#include <process/config_ctl_info.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <process/d_log.h>

namespace isc {
namespace process {


/// @brief Base class for implementing server specific mechanisms to control
/// the use of the Configuration Backends.
///
/// Every Kea server using Config Backend as a configuration repository
/// fetches configuration available for this server during startup and then
/// periodically while it is running. In both cases, the server has to
/// take into account that there is some existing configuration that the
/// server already knows, into which the configuration from the database
/// has to be merged.
///
/// When the server starts up, the existing configuration is the one that
/// the server reads from the configuration file. Usually, the configuration
/// fetched from the file will be disjointed with the configuration in the
/// database, e.g. all subnets should be specified either in the configuration
/// file or a database, not in both. However, there may be other cases when
/// option definitions are held in the configuration file, but the DHCP
/// options using them are stored in the database. The typical configuration
/// sequence upon the server startup will be to build the staging
/// configuration from the data stored in the configuration file and then
/// build another partial configuration from the data fetched from the
/// database. Finally, both configurations should be merged and committed
/// if they are deemed sane.
///
/// When the server is already running it may use "audit" (a.k.a. journal)
/// to periodically check if there are any pending configuration updates.
/// If changes are present, it will be fetched and used to create a new
/// configuration object (derived from the @c ConfigBase) holding this
/// partial configuration. This configuration has to be subsequently
/// merged into the current configuration that the server is using.
///
/// Note the difference between these two use cases is that in the first
/// case the fetched configuration is fetched into the staging configuration
/// and then committed, and in the second case it has to be directly merged
/// into the running configuration.
///
/// This class contains some common logic to facilitate both scenarios which
/// will be used by all server types. It also contains some pure virtual
/// methods to be implemented by specific servers. The common logic includes
/// the following operations:
/// - use the "config-control" specification to connect to the specified
///   databases via the configuration backends,
/// - fetch the audit trail to detect configuration updates,
/// - store the timestamp and id of the most recent audit entry fetched
///   from the database, so as next time it can fetch only the later updates.
///
/// The server specific part to be implemented in derived classes must
/// correctly interpret the audit entries and make appropriate API calls
/// to fetch the indicated configuration changes. It should also merge
/// the fetched configuration into the staging or current configuration.
/// Note that this class doesn't recognize whether it is a staging or
/// current configuration it is merging into. It simply uses the instance
/// provided by the caller.
///
/// @tparam ConfigBackendMgrType Type of the Config Backend Manager used
/// by the server implementing this class. For example, for the DHCPv4
/// server it will be @c ConfigBackendDHCPv4Mgr.
template<typename ConfigBackendMgrType>
class CBControlBase {
public:

    /// @brief Fetch mode used in invocations to @c databaseConfigFetch.
    ///
    /// One of the values indicates that the entire configuration should
    /// be fetched. The other one indicates that only configuration updates
    /// should be fetched.
    enum class FetchMode {
        FETCH_ALL,
        FETCH_UPDATE
    };

    /// @brief Constructor.
    ///
    /// Sets the time of the last fetched audit entry to Jan 1st, 2000,
    /// with id 0.
    CBControlBase()
        : last_audit_revision_time_(getInitialAuditRevisionTime()),
          last_audit_revision_id_(0) {
    }

    /// @brief Virtual destructor.
    ///
    /// It is always needed when there are virtual methods.
    virtual ~CBControlBase() {
        databaseConfigDisconnect();
    }

    /// @brief Resets the state of this object.
    ///
    /// Disconnects the configuration backends resets the recorded last
    /// audit revision time and id.
    void reset() {
        databaseConfigDisconnect();
        last_audit_revision_time_ = getInitialAuditRevisionTime();
        last_audit_revision_id_ = 0;
    }

    /// @brief (Re)connects to the specified configuration backends.
    ///
    /// This method disconnects from any existing configuration backends
    /// and then connects to those listed in the @c ConfigControlInfo
    /// structure within the @c srv_cfg argument. This method is called
    /// when the server starts up. It is not called when it merely
    /// fetches configuration updates.
    ///
    /// @param srv_cfg Pointer to the staging server configuration.
    ///
    /// @return true if the server found at least one backend to connect to,
    /// false if there are no backends available.
    bool databaseConfigConnect(const ConfigPtr& srv_cfg) {
        // We need to get rid of any existing backends.  These would be any
        // opened by previous configuration cycle.
        databaseConfigDisconnect();

        // Fetch the config-control info.
        ConstConfigControlInfoPtr config_ctl = srv_cfg->getConfigControlInfo();
        if (!config_ctl || config_ctl->getConfigDatabases().empty()) {
            // No config dbs, nothing to do.
            return (false);
        }

        // Iterate over the configured DBs and instantiate them.
        for (auto db : config_ctl->getConfigDatabases()) {
            LOG_INFO(dctl_logger, DCTL_OPEN_CONFIG_DB)
                .arg(db.redactedAccessString());
            getMgr().addBackend(db.getAccessString());
        }

        // Let the caller know we have opened DBs.
        return (true);
    }

    /// @brief Disconnects from the configuration backends.
    void databaseConfigDisconnect() {
        getMgr().delAllBackends();
    }

    /// @brief Fetches the entire or partial configuration from the database.
    ///
    /// This method is called by the starting up server to fetch and merge
    /// the entire configuration from the database or to fetch configuration
    /// updates periodically, e.g. as a result of triggering an interval
    /// timer callback.
    ///
    /// @param srv_cfg pointer to the staging configuration that should
    /// hold the config backends list and other partial configuration read
    /// from the file in case the method is called upon the server's start
    /// up. It is a pointer to the current server configuration if the
    /// method is called to fetch configuration updates.
    /// @param fetch_mode value indicating if the method is called upon the
    /// server start up or it is called to fetch configuration updates.
    virtual void databaseConfigFetch(const ConfigPtr& srv_cfg,
                                     const FetchMode& fetch_mode = FetchMode::FETCH_ALL) {
        // If the server starts up we need to connect to the database(s).
        // If there are no databases available simply do nothing.
        if ((fetch_mode == FetchMode::FETCH_ALL) && !databaseConfigConnect(srv_cfg)) {
            // There are no CB databases so we're done
            return;
        }

        LOG_INFO(dctl_logger, DCTL_CONFIG_FETCH);

        // For now we find data based on first backend that has it.
        db::BackendSelector backend_selector(db::BackendSelector::Type::UNSPEC);

        // Use the server_tag if set, otherwise use ALL.
        std::string server_tag = srv_cfg->getServerTag();
        db::ServerSelector server_selector =
            (server_tag.empty()? db::ServerSelector::ALL() : db::ServerSelector::ONE(server_tag));

        // This collection will hold the audit entries since the last update if
        // we're running this method to fetch the configuration updates.
        db::AuditEntryCollection audit_entries;

        // If we're fetching updates we need to retrieve audit entries to see
        // which objects have to be updated. If we're performing full reconfiguration
        // we also need audit entries to set the last_audit_revision_time_ to the
        // time of the most recent audit entry.

        /// @todo We need a separate API call for the latter case to only
        /// fetch the last audit entry rather than all of them.

        // Save the timestamp indicating last audit revision time.
        auto lb_modification_time = last_audit_revision_time_;
        // Save the identifier indicating last audit revision id.
        auto lb_modification_id = last_audit_revision_id_;

        audit_entries = getMgr().getPool()->getRecentAuditEntries(backend_selector,
                                                                  server_selector,
                                                                  lb_modification_time,
                                                                  lb_modification_id);
        // Store the last audit revision time. It should be set to the most recent
        // audit entry fetched. If returned audit is empty we don't update.
        updateLastAuditRevisionTimeId(audit_entries);

        // If this is full reconfiguration we don't need the audit entries anymore.
        // Let's remove them and proceed as if they don't exist.
        if (fetch_mode == FetchMode::FETCH_ALL) {
            audit_entries.clear();
        }

        // If we fetch the entire config or we're updating the config and there are
        // audit entries indicating that there are some pending updates, let's
        // execute the server specific function that fetches and merges the data
        // into the given configuration.
        if ((fetch_mode == FetchMode::FETCH_ALL) || !audit_entries.empty()) {
            try {
                databaseConfigApply(backend_selector, server_selector,
                                    lb_modification_time, audit_entries);
            } catch (...) {
                // Revert last audit revision time and id so as we can retry
                // from the last successful attempt.
                /// @todo Consider reverting to the initial value to reload
                /// the entire configuration if the update failed.
                last_audit_revision_time_ = lb_modification_time;
                last_audit_revision_id_ = lb_modification_id;
                throw;
            }
        }
    }

protected:

    /// @brief Returns audit entries for new or updated configuration
    /// elements of specific type to be fetched from the database.
    ///
    /// This is convenience method invoked from the implementations of the
    /// @c databaseConfigApply function. This method is invoked when the
    /// server should fetch the updates to the existing configuration.
    /// The collection of audit entries contains audit entries indicating
    /// the updates to be fetched. This method returns audit entries for
    /// updated configuration elements of the specific type the
    /// @c databaseConfigApply should fetch. The returned collection od
    /// audit entries contains CREATE or UPDATE entries of the specific type.
    ///
    /// @param audit_entries collection od audit entries to filter.
    /// @param object_type object type to filter with.
    /// @return audit entries collection with CREATE or UPDATE entries
    /// of the specific type be fetched from the database.
    db::AuditEntryCollection
    fetchConfigElement(const db::AuditEntryCollection& audit_entries,
                       const std::string& object_type) const {
        db::AuditEntryCollection result;
        const auto& index = audit_entries.get<db::AuditEntryObjectTypeTag>();
        auto range = index.equal_range(object_type);
        for (auto it = range.first; it != range.second; ++it) {
            if ((*it)->getModificationType() != db::AuditEntry::ModificationType::DELETE) {
                result.insert(*it);
            }
        }

        return (result);
    }

    /// @brief Server specific method to fetch and apply back end
    /// configuration into the local configuration.
    ///
    /// This pure virtual method must be implemented in the derived classes
    /// to provide server specific implementation of fetching and applying
    /// the configuration. The implementations should perform the following
    /// sequence of operations:
    /// - Check if any audit entries exist. If none exist, assume that this
    ///   is the case of full server (re)configuration, otherwise assume
    ///   that configuration update is being performed.
    /// - Select audit entries which indicate deletion of any configuration
    ///   elements. For each such audit entry delete the given object from
    ///   the local configuration.
    /// - If the server is performing full reconfiguration, fetch the entire
    ///   configuration for the server. If the server is merely updating
    ///   the server configuration, fetch only those objects for which
    ///   (create/update) audit entries exist.
    /// - Merge the fetched configuration into the local server's
    ///   configuration.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param lb_modification_time Lower bound modification time for the
    /// configuration elements to be fetched.
    /// @param audit_entries Audit entries fetched from the database since
    /// the last configuration update. This collection is empty if there
    /// were no updates.
    virtual void databaseConfigApply(const db::BackendSelector& backend_selector,
                                     const db::ServerSelector& server_selector,
                                     const boost::posix_time::ptime& lb_modification_time,
                                     const db::AuditEntryCollection& audit_entries) = 0;

    /// @brief Returns the instance of the Config Backend Manager used by
    /// this object.
    ///
    /// @return Reference to the CB Manager instance.
    ConfigBackendMgrType& getMgr() const {
        return (ConfigBackendMgrType::instance());
    }

    /// @brief Convenience method returning initial timestamp to set the
    /// @c last_audit_revision_time_ to.
    ///
    /// @return Returns 2000-Jan-01 00:00:00 in local time.
    static boost::posix_time::ptime getInitialAuditRevisionTime() {
        static boost::posix_time::ptime
            initial_time(boost::gregorian::date(2000, boost::gregorian::Jan, 1));
        return (initial_time);
    }

    /// @brief Updates timestamp of the most recent audit entry fetched from
    /// the database.
    ///
    /// If the collection of audit entries is empty, this method simply
    /// returns without updating the timestamp.
    ///
    /// @param audit_entries reference to the collection of the fetched audit entries.
    void updateLastAuditRevisionTimeId(const db::AuditEntryCollection& audit_entries) {
        // Do nothing if there are no audit entries. It is the case if
        // there were no updates to the configuration.
        if (audit_entries.empty()) {
            return;
        }

        // Get the audit entries sorted by modification time and id,
	// and pick the latest entry.
        const auto& index = audit_entries.get<db::AuditEntryModificationTimeIdTag>();
        last_audit_revision_time_ = (*index.rbegin())->getModificationTime();
        last_audit_revision_id_ = (*index.rbegin())->getRevisionId();
    }

    /// @brief Stores the most recent audit revision timestamp.
    boost::posix_time::ptime last_audit_revision_time_;

    /// @brief Stores the most recent audit revision identifier.
    ///
    /// The identifier is used when two (or more) audit entries have
    /// the same timestamp. It is not used by itself because timestamps
    /// are more user friendly. Unfortunately old versions of MySQL do not
    /// support millisecond timestamps.
    uint64_t last_audit_revision_id_;
};

/// @brief Checks if an object is in a collection od audit entries.
///
/// @param audit_entries collection od audit entries to search for.
/// @param object_id object identifier.
inline bool
hasObjectId(const db::AuditEntryCollection& audit_entries,
            const uint64_t& object_id) {
    const auto& object_id_idx = audit_entries.get<db::AuditEntryObjectIdTag>();
    return (object_id_idx.count(object_id) > 0);
}

} // end of namespace isc::process
} // end of namespace isc

#endif /* CB_CTL_BASE_H */
