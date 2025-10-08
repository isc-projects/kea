// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_LIMITS_RATE_LIMIT_MANAGER_H
#define ISC_LIMITS_RATE_LIMIT_MANAGER_H

#include <database/audit_entry.h>
#include <dhcp/classify.h>
#include <dhcp/pkt_template.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/srv_config.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_id.h>
#include <hooks/hooks.h>
#include <limits/configuration.h>
#include <limits/limits_logger.h>
#include <stats/stats_mgr.h>
#include <util/dhcp_space.h>
#include <util/multi_threading_mgr.h>

#include <boost/circular_buffer.hpp>

#include <chrono>
#include <unordered_map>
#include <vector>

namespace isc {
namespace limits {

/// @brief a point in time
using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

/// @brief Holds a number of time points, used in limiting by a single criterion.
/// It is important to use a data structure that ensures O(1) deletion.
using TimeSeries = boost::circular_buffer<TimePoint>;

/// @brief Holds a number of time points, used in limiting by a single criterion, and a mutex to
/// protect concurrent reads and writes.
struct ProtectedTimeSeries {
    /// @brief Protects against races on the time points which can be edited at each hook callout.
    std::mutex mutex_;

    /// @brief Holds the actual time points.
    TimeSeries time_points_;
};

/// @brief Defines a smart pointer to a ProtectedTimeSeries.
typedef std::shared_ptr<ProtectedTimeSeries> ProtectedTimeSeriesPtr;

/// @brief Provides the capability to limit the number of leases or the response rate.
struct LimitManager {
    /// @brief singleton access function
    ///
    /// @return the singleton
    static LimitManager& instance();

    /// @brief Clears the time series circular buffers in order to start over rate limiting.
    void clear();

    /// @brief Reinitialize data structures required for limiting
    ///
    /// First clears the time series circular buffers, then proceeds to parse
    /// the relevant configuration.
    ///
    /// @param config the configuration to be parsed - usually current or staging
    void initialize(isc::dhcp::SrvConfigPtr const& config);

    /// @brief Fetches limits from the given Kea configuration.
    ///
    /// Searches the Kea configuration for any limits in user contexts, then
    /// sets the new capacities on the buffers.
    ///
    /// @param config the configuration to be parsed - usually current or staging
    void parse(isc::dhcp::SrvConfigPtr const& config);

    /// @brief cbX_updated hook point
    ///
    /// If changes are detected for any client classes or subnets, the whole limits
    /// configuration is updated. Time points are not reset, because there might be a significant
    /// amount of client classes and subnets that remain the same. On top of that, the ones who
    /// changed might still match clients that have been limited with the same client class or
    /// subnet prior to the CB update, so there is some relevancy to the current calculation.
    ///
    /// @tparam D DHCP space
    /// @param handle callout handle used for retrieving audit entries
    ///
    /// @return always 0 meaning success
    template <isc::util::DhcpSpace D>
    int cb_updated(isc::hooks::CalloutHandle& handle) {
        isc::hooks::CalloutHandle::CalloutNextStep const status(handle.getStatus());
        if (status == isc::hooks::CalloutHandle::NEXT_STEP_DROP ||
            status == isc::hooks::CalloutHandle::NEXT_STEP_SKIP) {
            return (0);
        }

        isc::db::AuditEntryCollectionPtr audit_entries;
        handle.getArgument("audit_entries", audit_entries);
        if (!audit_entries) {
            isc_throw(Unexpected, "null audit_entries in LimitManager::cb_updated");
        }

        auto const& object_type_index(audit_entries->get<isc::db::AuditEntryObjectTypeTag>());
        auto const& client_class_range(object_type_index.equal_range(
            isc::util::formatDhcpSpace<D>("dhcp{}_client_class")));
        auto const& subnet_range(object_type_index.equal_range(
            isc::util::formatDhcpSpace<D>("dhcp{}_subnet")));

        // If any client classes or subnets changed, reparse the entire configuration.
        if (std::distance(client_class_range.first, client_class_range.second) ||
            std::distance(subnet_range.first, subnet_range.second)) {
            LimitManager::instance().parse(isc::dhcp::CfgMgr::instance().getCurrentCfg());
        }

        return (0);
    }

    /// @brief dhcpX_srv_configured hook point
    ///
    /// Reconfigures limits with the given configuration and recounts leases.
    ///
    /// @tparam D DHCP space
    /// @param handle callout handle used for retrieving audit entries
    ///
    /// @return 0 if configuration is successful, 1 otherwise
    template <isc::util::DhcpSpace D>
    int dhcp_srv_configured(isc::hooks::CalloutHandle& handle) {
        isc::hooks::CalloutHandle::CalloutNextStep const status(handle.getStatus());
        if (status == isc::hooks::CalloutHandle::NEXT_STEP_DROP ||
            status == isc::hooks::CalloutHandle::NEXT_STEP_SKIP) {
            return (0);
        }

        if (isc::dhcp::LeaseMgrFactory::haveInstance()) {
            // If lease limiting is used, make sure the database has JSON support.
            if (!isc::dhcp::LeaseMgrFactory::instance().isJsonSupported()) {
                const std::string error("The lease database you have configured "
                    "does not support JSON operations which are required for lease "
                    "limiting.");
                handle.setArgument("error", error);
                handle.setStatus(isc::hooks::CalloutHandle::NEXT_STEP_DROP);
                return (1);
            }

            // Recount the leases by class.
            recountClassLeases<D>();
        } else {
            std::string const lease_db_access_string(isc::dhcp::CfgMgr::instance()
                                                         .getStagingCfg()
                                                         ->getCfgDbAccess()
                                                         ->getLeaseDbAccessString());
            if (lease_db_access_string.find("retry-on-startup=true") &&
                (lease_db_access_string.find("type=mysql") ||
                 lease_db_access_string.find("type=postgresql"))) {
                LOG_WARN(limits_logger, LIMITS_CONFIGURATION_LEASE_BACKEND_NOT_AVAILABLE);
            } else {
                LOG_ERROR(limits_logger,
                          LIMITS_CONFIGURATION_LEASE_BACKEND_SHOULD_HAVE_BEEN_AVAILABLE);
            }
        }

        return (0);
    }

    /// @brief pktX_receive hook point
    ///
    /// Handles per-client-class rate limits. For every packet, remove all expired counted packets
    /// from the buffer, check if the limit is reached i.e. if the buffer is full, and finally count
    /// the current packet toward the limit if there is still room in the buffer.
    ///
    /// @tparam D DHCP space
    /// @param handle callout handle used for the subnet ID
    ///
    /// @return always 0 meaning success
    template <isc::util::DhcpSpace D>
    int pkt_receive(isc::hooks::CalloutHandle& handle) {
        isc::hooks::CalloutHandle::CalloutNextStep const status(handle.getStatus());
        if (status == isc::hooks::CalloutHandle::NEXT_STEP_DROP ||
            status == isc::hooks::CalloutHandle::NEXT_STEP_SKIP) {
            return (0);
        }

        // Get the client classes.
        isc::dhcp::PktTPtr<D> packet;
        handle.getArgument(isc::util::formatDhcpSpace<D>("query{}"), packet);
        if (!packet) {
            isc_throw(Unexpected, "null packet in LimitManager::pkt_receive");
        }
        auto const& classes(packet->getClasses());

        // To be able to iterate over client classes and template classes, all
        // regular classes must be added to a SubClassContainer with subclass
        // name set to the same value as template class name.
        auto const& relations = packet->getSubClassesRelations();

        // Get the current time.
        TimePoint const now(std::chrono::system_clock::now());

        // Should contain client classes that are both in the packet and that are limited.
        std::vector<isc::dhcp::ClientClass> common_client_classes;

        // Lock a global-wide mutex for all client classes. It's not a necessary condition, but it's
        // sufficient. Locking per client class, similarly to how it happens for subnet IDs would
        // have been more efficient in a more heterogeneous class-to-packet distribution, but that
        // situation is not guaranteed.
        isc::util::MultiThreadingLock lock(mutex_);

        // Check if the rate limit is respected.
        for (auto const& c : relations) {
            auto const& class_def = isc::dhcp::CfgMgr::instance().getCurrentCfg()->getClientClassDictionary()->findClass(c.class_def_);
            if (!class_def) {
                continue;
            }

            auto const &limit_cfg = rate_limit_configuration_.parseUserContext(class_def->getContext());

            if (!limit_cfg) {
                continue;
            }

            // Get the limit.
            RateLimit const& limit(limit_cfg->stringValue());

            // Get the time series. Create a list on this class if not already added to the map.
            TimeSeries& time_series(clocked_in_times_by_class_[c.class_]);

            time_series.set_capacity(limit.allowed_packets_);

            // Remove all expired times.
            while (!time_series.empty()) {
                if (time_series.back() + limit.time_unit_ < now) {
                    time_series.pop_back();
                } else {
                    // This is an optimization. Job is finished at the first time point that is not
                    // expired. The rest are sorted and higher in value, thus not expired.
                    break;
                }
            }

            // Effectively check the limit.
            if (time_series.size() == limit.allowed_packets_) {
                // Drop the packet.
                handle.setStatus(isc::hooks::CalloutHandle::NEXT_STEP_DROP);

                LOG_DEBUG(limits_logger, isc::log::DBGLVL_TRACE_BASIC,
                          LIMITS_PACKET_WITH_CLIENT_CLASSES_RATE_LIMIT_DROPPED)
                    .arg(classes.toText())
                    .arg(limit.text_)
                    .arg(c.class_);

                // No need to check other client classes since packet is dropped.
                break;
            }

            // Cache the set of client classes that are both in the packet and limited. If packet is
            // not dropped, they will be iterated through one more time further below. As such, the
            // configuration lookup for each client class at the beginning of this loop will no
            // longer be required.
            common_client_classes.push_back(c.class_);
        }

        if (handle.getStatus() == isc::hooks::CalloutHandle::NEXT_STEP_DROP) {
            isc::stats::StatsMgr& stats_mgr = isc::stats::StatsMgr::instance();
            if (D == isc::util::DhcpSpace::DHCPv4) {
                stats_mgr.addValue("pkt4-limit-exceeded",
                                   static_cast<int64_t>(1));
                stats_mgr.addValue("pkt4-receive-drop",
                                   static_cast<int64_t>(1));
            } else {
                stats_mgr.addValue("pkt6-limit-exceeded",
                                   static_cast<int64_t>(1));
                stats_mgr.addValue("pkt6-receive-drop",
                                   static_cast<int64_t>(1));
            }
        } else {
            // Honor the packet and keep track of it.
            for (auto const& c : common_client_classes) {
                TimeSeries& time_series(clocked_in_times_by_class_.at(c));
                time_series.push_front(now);
            }

            // Only log that the packet is within the limit if this packet is being rate limited.
            if (!common_client_classes.empty()) {
                LOG_DEBUG(limits_logger, isc::log::DBGLVL_TRACE_DETAIL_DATA,
                          LIMITS_PACKET_WITH_CLIENT_CLASSES_RATE_LIMIT_HONORED)
                    .arg(classes.toText());
            }
        }

        return (0);
    }

    /// @brief subnetX_select hook point
    ///
    /// Handles per-subnet rate limits. For every packet, remove all expired counted packets from
    /// the buffer, check if the limit is reached i.e. if the buffer is full, and finally count the
    /// current packet toward the limit if there is still room in the buffer. This function also
    /// checks if subnets were updated through subnet commands, or any other method that
    /// circumvented reconfiguration, and updates the limits accordingly.
    ///
    /// @tparam D DHCP space
    /// @param handle callout handle used for the subnet ID
    ///
    /// @return always 0 meaning success
    template <isc::util::DhcpSpace D>
    int subnet_select(isc::hooks::CalloutHandle& handle) {
        isc::hooks::CalloutHandle::CalloutNextStep const status(handle.getStatus());
        if (status == isc::hooks::CalloutHandle::NEXT_STEP_DROP ||
            status == isc::hooks::CalloutHandle::NEXT_STEP_SKIP) {
            return (0);
        }

        // Get the subnet ID.
        isc::dhcp::ConstSubnetTPtr<D> subnet;
        handle.getArgument(isc::util::formatDhcpSpace<D>("subnet{}"), subnet);
        if (!subnet) {
            LOG_DEBUG(limits_logger, isc::log::DBGLVL_TRACE_DETAIL_DATA,
                      LIMITS_PACKET_WIIH_SUBNET_ID_RATE_NO_SUBNET);
            return (0);
        }
        isc::dhcp::SubnetID const subnet_id(subnet->getID());

        RateLimit limit;
        auto const& limit_cfg = subnetRateLimit<D>(subnet_id);
        if (limit_cfg) {
            // Get the limit.
            limit = RateLimit(limit_cfg->stringValue());
        } else {
            return (0);
        }

        ProtectedTimeSeriesPtr time_series;

        // Lock a global-wide mutex while configuration can be read-to and written-from.
        {
            isc::util::MultiThreadingLock lock(mutex_);

            // Create a time series on this subnet ID if not already added to the map.
            ProtectedTimeSeriesPtr& time_series_ref(clocked_in_times_by_subnet_id_[subnet_id]);
            if (!time_series_ref) {
                time_series_ref = std::make_shared<ProtectedTimeSeries>();
            }
            time_series = time_series_ref;
        }

        // Get the current time.
        TimePoint const now(std::chrono::system_clock::now());

        // Lock the mutex on this subnet ID.
        isc::util::MultiThreadingLock lock(time_series->mutex_);

        time_series->time_points_.set_capacity(limit.allowed_packets_);

        // Remove all expired times.
        while (!time_series->time_points_.empty()) {
            if (time_series->time_points_.back() + limit.time_unit_ < now) {
                time_series->time_points_.pop_back();
            } else {
                // This is an optimization. Job is finished at the first time point that is not
                // expired. The rest are sorted and higher in value, thus not expired.
                break;
            }
        }

        // Check the limit.
        if (time_series->time_points_.size() < limit.allowed_packets_) {
            // Honor the packet and keep track of it.
            time_series->time_points_.push_front(now);
        } else {
            // Drop the packet.
            handle.setStatus(isc::hooks::CalloutHandle::NEXT_STEP_DROP);

            LOG_DEBUG(limits_logger, isc::log::DBGLVL_TRACE_BASIC,
                      LIMITS_PACKET_WITH_SUBNET_ID_RATE_LIMIT_DROPPED)
                .arg(subnet_id)
                .arg(limit.text_);

            isc::stats::StatsMgr& stats_mgr = isc::stats::StatsMgr::instance();
            if (D == isc::util::DhcpSpace::DHCPv4) {
                stats_mgr.addValue("pkt4-limit-exceeded",
                                   static_cast<int64_t>(1));
                stats_mgr.addValue("pkt4-receive-drop",
                                   static_cast<int64_t>(1));
            } else {
                stats_mgr.addValue("pkt6-limit-exceeded",
                                   static_cast<int64_t>(1));
                stats_mgr.addValue("pkt6-receive-drop",
                                   static_cast<int64_t>(1));
            }

            return (0);
        }

        LOG_DEBUG(limits_logger, isc::log::DBGLVL_TRACE_DETAIL_DATA,
                  LIMITS_PACKET_WITH_SUBNET_ID_RATE_LIMIT_HONORED)
            .arg(subnet_id)
            .arg(limit.text_);

        return (0);
    }

    /// @brief leaseX_select hook point
    ///
    /// Handles all lease limits.
    ///
    /// 1. Adds client classes to the lease context.
    /// 2. Creates a JSON with the applicable limits from the configuration.
    /// 3. Checks lease limits by passing the JSON to a function of the lease manager.
    /// 4. Logs if limit is exceeded or not.
    /// 5. Sets the SKIP callout if the limit is being exceeded so that the lease is not assigned.
    ///
    /// @tparam D DHCP space
    /// @param handle callout handle used for the subnet ID
    /// @param lease_update true if the lease is being updated, false if it is a new lease
    ///
    /// @return always 0 meaning success
    template <isc::util::DhcpSpace D>
    int lease_callout(isc::hooks::CalloutHandle& handle, bool lease_update = false) {
        isc::hooks::CalloutHandle::CalloutNextStep const status(handle.getStatus());
        if (status == isc::hooks::CalloutHandle::NEXT_STEP_DROP ||
            status == isc::hooks::CalloutHandle::NEXT_STEP_SKIP) {
            return (0);
        }

        // Get the lease.
        isc::dhcp::LeaseTPtr<D> lease;
        handle.getArgument(isc::util::formatDhcpSpace<D>("lease{}"), lease);
        if (!lease) {
            isc_throw(Unexpected, "null lease in LimitManager::lease_callout");
        }
        isc::dhcp::SubnetID const subnet_id(lease->subnet_id_);

        // Get the client classes.
        isc::dhcp::PktTPtr<D> packet;
        handle.getArgument(isc::util::formatDhcpSpace<D>("query{}"), packet);
        if (!packet) {
            isc_throw(Unexpected, "null packet in LimitManager::lease_callout");
        }
        auto const& classes(packet->getClasses());

        // Add client classes to the lease context.
        addClientClassesToLeaseContext(classes, lease);

        // Don't check limits for lease renewals.
        if (lease_update) {
            return (0);
        }

        // To be able to iterate over client classes and template classes, all
        // regular classes must be added to a SubClassContainer with subclass
        // name set to the same value as template class name.
        auto const& relations(packet->getSubClassesRelations());

        // Create parts of the limits context.
        // Add client class limits to the context.
        isc::data::ElementPtr client_class_limits = clientClassLimitsToElement<D>(relations, lease->getType());
        // Add subnet limits to the context.
        isc::data::ElementPtr subnet_limit = subnetLimitToElement<D>(subnet_id, lease->getType());

        // Tie the limits together into an "ISC" context.
        isc::data::ElementPtr limits(isc::data::Element::createMap());
        if (!client_class_limits->empty()) {
            limits->set("client-classes", client_class_limits);
        }
        if (!subnet_limit->empty()) {
            limits->set("subnet", subnet_limit);
        }
        if (limits->empty()) {
            // No limits means we let the lease through by default. Exit here so that we don't check
            // lease limits for nothing and so that we don't log details on non-limited leases.
            return (0);
        }
        isc::data::ElementPtr ISC(isc::data::Element::createMap());
        ISC->set("limits", limits);
        isc::data::ElementPtr context(isc::data::Element::createMap());
        context->set("ISC", ISC);

        // Check lease limits.
        std::string const limit_exceeded_text(checkLeaseLimits<D>(context));
        if (limit_exceeded_text.empty()) {
            LOG_DEBUG(limits_logger, isc::log::DBGLVL_TRACE_BASIC, LIMITS_LEASE_WITHIN_LIMITS)
                .arg(lease->addr_);
        } else {
            // Prevent the lease from being allocated.
            handle.setStatus(isc::hooks::CalloutHandle::NEXT_STEP_SKIP);

            LOG_DEBUG(limits_logger, isc::log::DBGLVL_TRACE_BASIC, LIMITS_LEASE_LIMIT_EXCEEDED)
                .arg(limit_exceeded_text);
        }

        return (0);
    }

private:
    /// @brief Add the packet's client classes to the lease's user context.
    ///
    /// @param classes the client classes being added to the user context
    /// @param lease the lease whose user context needs to be to be amended
    void addClientClassesToLeaseContext(isc::dhcp::ClientClasses const& classes,
                                        isc::dhcp::LeasePtr const& lease);

    /// @brief Returns all lease limits for client classes that are common with the given class
    /// names as an ElementPtr of type ListElement.
    ///
    /// The list contains elements that look like the following:
    /// { "name" : <string>, "address-limit": <integer>, "prefix-limit": <integer> }
    ///
    /// @tparam D DHCP space
    /// @param classes the classes that we want the limits for
    /// @param lease_type the lease type to fetch limits for
    ///
    /// @return the list of limits
    template <isc::util::DhcpSpace D>
    isc::data::ElementPtr clientClassLimitsToElement(isc::dhcp::SubClassRelationContainer const& classes,
                                                     isc::dhcp::Lease::Type const& lease_type);

    /// @brief Returns all lease limits for the given subnet ID as an ElementPtr of type MapElement.
    ///
    /// The map has the following format:
    /// { "id" : <integer>, "address-limit": <integer>, "prefix-limit": <integer> }
    ///
    /// @tparam D DHCP space
    /// @param subnet_id the subnet ID that we want the limits for
    /// @param lease_type the lease type to fetch limits for
    ///
    /// @return the map of limits
    template <isc::util::DhcpSpace D>
    isc::data::ElementPtr subnetLimitToElement(isc::dhcp::SubnetID const subnet_id,
                                               isc::dhcp::Lease::Type const& lease_type);

    /// @brief Returns specific limits for the given subnet ID as an ElementPtr.
    ///
    /// @tparam D DHCP space
    /// @param subnet_id the subnet ID that we want the limits for
    /// @param lease_type the lease type to fetch limits for
    ///
    /// @return the specific limits
    template <isc::util::DhcpSpace D>
    isc::data::ConstElementPtr subnetRateLimit(isc::dhcp::SubnetID const subnet_id);

    /// @brief Template wrapper over LeaseMgr::checkLimits functions
    ///
    /// @tparam D DHCP space
    /// @param user_context all or part of the lease's user context which, for the intents and
    /// purposes of lease limiting should have the following format
    /// (not all nodes are mandatory and values are given only as examples):
    /// { "ISC": { "limits": { "client-classes": [ { "name": "foo", "address-limit": 2 } ],
    ///                        "subnet": { "id": 1, "address-limit": 2 } } } }
    ///
    /// @return a string describing a limit that is being exceeded, or an empty
    /// string if no limits are exceeded
    template <isc::util::DhcpSpace D>
    std::string checkLeaseLimits(isc::data::ConstElementPtr const& context) const;

    /// @brief Recounts leases by class if a memfile backend is used for leases.
    ///
    /// @tparam D DHCP space
    template <isc::util::DhcpSpace D>
    void recountClassLeases() const;

    /// @brief arrival times of packets for a time span equal to the configured
    /// time unit indexed by client class
    std::unordered_map<isc::dhcp::ClientClass, TimeSeries> clocked_in_times_by_class_;

    /// @brief arrival times of packets for a time span equal to the configured
    /// time unit indexed by subnet ID
    std::unordered_map<isc::dhcp::SubnetID, ProtectedTimeSeriesPtr> clocked_in_times_by_subnet_id_;

    /// @brief A mutex used to protect read and write access to all the client
    /// classes' time points and to all the limits configuration.
    std::mutex mutex_;

    /// @brief Holds the configured address limits.
    AddressLimitConfiguration address_limit_configuration_;

    /// @brief Holds the configured prefix limits.
    PrefixLimitConfiguration prefix_limit_configuration_;

    /// @brief Holds the configured rate limits.
    RateLimitConfiguration rate_limit_configuration_;

    /// @brief non-copyable singleton
    /// @{
    LimitManager() = default;
    LimitManager(LimitManager const&) = delete;
    LimitManager& operator=(LimitManager const&) = delete;
    /// @}
};

}  // namespace limits
}  // namespace isc

#endif  // ISC_LIMITS_RATE_LIMIT_MANAGER_H
