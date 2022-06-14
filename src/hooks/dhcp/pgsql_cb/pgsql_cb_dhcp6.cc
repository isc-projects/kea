// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/addr_utilities.h>
#include <pgsql_cb_dhcp6.h>
#include <pgsql_cb_impl.h>
#include <pgsql_query_macros_dhcp.h>
#include <cc/data.h>
#include <config_backend/constants.h>
#include <database/database_connection.h>
#include <database/db_exceptions.h>
#include <dhcp/classify.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_data_types.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/config_backend_dhcp6_mgr.h>
#include <dhcpsrv/network.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/timer_mgr.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <util/buffer.h>
#include <util/boost_time_utils.h>
#include <util/multi_threading_mgr.h>
#include <util/triplet.h>
#include <pgsql/pgsql_connection.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/scoped_ptr.hpp>

using namespace isc::cb;
using namespace isc::db;
using namespace isc::data;
using namespace isc::asiolink;
using namespace isc::log;
using namespace isc::util;

namespace isc {
namespace dhcp {

/// @brief Implementation of the PostgreSQL Configuration Backend.
class PgSqlConfigBackendDHCPv6Impl : public PgSqlConfigBackendImpl {
public:

    /// @brief Statement tags.
    ///
    /// The contents of the enum are indexes into the list of SQL statements.
    /// It is assumed that the order is such that the indices of statements
    /// reading the database are less than those of statements modifying the
    /// database.
    enum StatementIndex {
        CREATE_AUDIT_REVISION,
        CHECK_CLIENT_CLASS_KNOWN_DEPENDENCY_CHANGE,
        GET_GLOBAL_PARAMETER6,
        GET_ALL_GLOBAL_PARAMETERS6,
        GET_MODIFIED_GLOBAL_PARAMETERS6,
        GET_SUBNET6_ID_NO_TAG,
        GET_SUBNET6_ID_ANY,
        GET_SUBNET6_ID_UNASSIGNED,
        GET_SUBNET6_PREFIX_NO_TAG,
        GET_SUBNET6_PREFIX_ANY,
        GET_SUBNET6_PREFIX_UNASSIGNED,
        GET_ALL_SUBNETS6,
        GET_ALL_SUBNETS6_UNASSIGNED,
        GET_MODIFIED_SUBNETS6,
        GET_MODIFIED_SUBNETS6_UNASSIGNED,
        GET_SHARED_NETWORK_SUBNETS6,
        GET_POOL6_RANGE,
        GET_POOL6_RANGE_ANY,
        GET_PD_POOL,
        GET_PD_POOL_ANY,
        GET_SHARED_NETWORK6_NAME_NO_TAG,
        GET_SHARED_NETWORK6_NAME_ANY,
        GET_SHARED_NETWORK6_NAME_UNASSIGNED,
        GET_ALL_SHARED_NETWORKS6,
        GET_ALL_SHARED_NETWORKS6_UNASSIGNED,
        GET_MODIFIED_SHARED_NETWORKS6,
        GET_MODIFIED_SHARED_NETWORKS6_UNASSIGNED,
        GET_OPTION_DEF6_CODE_SPACE,
        GET_ALL_OPTION_DEFS6,
        GET_MODIFIED_OPTION_DEFS6,
        GET_OPTION6_CODE_SPACE,
        GET_ALL_OPTIONS6,
        GET_MODIFIED_OPTIONS6,
        GET_OPTION6_SUBNET_ID_CODE_SPACE,
        GET_OPTION6_POOL_ID_CODE_SPACE,
        GET_OPTION6_PD_POOL_ID_CODE_SPACE,
        GET_OPTION6_SHARED_NETWORK_CODE_SPACE,
        GET_CLIENT_CLASS6_NAME,
        GET_ALL_CLIENT_CLASSES6,
        GET_ALL_CLIENT_CLASSES6_UNASSIGNED,
        GET_MODIFIED_CLIENT_CLASSES6,
        GET_MODIFIED_CLIENT_CLASSES6_UNASSIGNED,
        GET_AUDIT_ENTRIES6_TIME,
        GET_SERVER6,
        GET_ALL_SERVERS6,
        INSERT_GLOBAL_PARAMETER6,
        INSERT_GLOBAL_PARAMETER6_SERVER,
        INSERT_SUBNET6,
        INSERT_SUBNET6_SERVER,
        INSERT_POOL6,
        INSERT_PD_POOL,
        INSERT_SHARED_NETWORK6,
        INSERT_SHARED_NETWORK6_SERVER,
        INSERT_OPTION_DEF6,
        INSERT_OPTION_DEF6_CLIENT_CLASS,
        INSERT_OPTION_DEF6_SERVER,
        INSERT_OPTION6,
        INSERT_OPTION6_SERVER,
        INSERT_CLIENT_CLASS6,
        INSERT_CLIENT_CLASS6_SERVER,
        INSERT_CLIENT_CLASS6_DEPENDENCY,
        INSERT_SERVER6,
        UPDATE_GLOBAL_PARAMETER6,
        UPDATE_SUBNET6,
        UPDATE_SHARED_NETWORK6,
        UPDATE_OPTION_DEF6,
        UPDATE_OPTION_DEF6_CLIENT_CLASS,
        UPDATE_OPTION6,
        UPDATE_OPTION6_SUBNET_ID,
        UPDATE_OPTION6_POOL_ID,
        UPDATE_OPTION6_PD_POOL_ID,
        UPDATE_OPTION6_SHARED_NETWORK,
        UPDATE_OPTION6_CLIENT_CLASS,
        UPDATE_CLIENT_CLASS6,
        UPDATE_CLIENT_CLASS6_SAME_POSITION,
        UPDATE_SERVER6,
        DELETE_GLOBAL_PARAMETER6,
        DELETE_ALL_GLOBAL_PARAMETERS6,
        DELETE_ALL_GLOBAL_PARAMETERS6_UNASSIGNED,
        DELETE_SUBNET6_ID_WITH_TAG,
        DELETE_SUBNET6_ID_ANY,
        DELETE_SUBNET6_PREFIX_WITH_TAG,
        DELETE_SUBNET6_PREFIX_ANY,
        DELETE_ALL_SUBNETS6,
        DELETE_ALL_SUBNETS6_UNASSIGNED,
        DELETE_ALL_SUBNETS6_SHARED_NETWORK_NAME,
        DELETE_SUBNET6_SERVER,
        DELETE_POOLS6,
        DELETE_PD_POOLS,
        DELETE_SHARED_NETWORK6_NAME_WITH_TAG,
        DELETE_SHARED_NETWORK6_NAME_ANY,
        DELETE_ALL_SHARED_NETWORKS6,
        DELETE_ALL_SHARED_NETWORKS6_UNASSIGNED,
        DELETE_SHARED_NETWORK6_SERVER,
        DELETE_OPTION_DEF6_CODE_NAME,
        DELETE_ALL_OPTION_DEFS6,
        DELETE_ALL_OPTION_DEFS6_UNASSIGNED,
        DELETE_OPTION_DEFS6_CLIENT_CLASS,
        DELETE_OPTION6,
        DELETE_ALL_GLOBAL_OPTIONS6_UNASSIGNED,
        DELETE_OPTION6_SUBNET_ID,
        DELETE_OPTION6_POOL_RANGE,
        DELETE_OPTION6_PD_POOL,
        DELETE_OPTION6_SHARED_NETWORK,
        DELETE_OPTIONS6_SUBNET_ID_PREFIX,
        DELETE_OPTIONS6_SHARED_NETWORK,
        DELETE_OPTIONS6_CLIENT_CLASS,
        DELETE_CLIENT_CLASS6_DEPENDENCY,
        DELETE_CLIENT_CLASS6_SERVER,
        DELETE_ALL_CLIENT_CLASSES6,
        DELETE_ALL_CLIENT_CLASSES6_UNASSIGNED,
        DELETE_CLIENT_CLASS6,
        DELETE_CLIENT_CLASS6_ANY,
        DELETE_SERVER6,
        DELETE_ALL_SERVERS6,
        GET_LAST_INSERT_ID6,
        NUM_STATEMENTS
    };

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    explicit PgSqlConfigBackendDHCPv6Impl(const DatabaseConnection::ParameterMap&
                                          parameters);

    /// @brief Destructor.
    ~PgSqlConfigBackendDHCPv6Impl();

    /// @brief Fetches the SQL statement for a given statement index.
    ///
    /// @param index index of the desired statement.
    /// @throw BadValue if there is no statement corresponding to
    /// the index.
    virtual PgSqlTaggedStatement& getStatement(size_t index) const;

    /// @brief Sends query to retrieve global parameter.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the parameter to be retrieved.
    ///
    /// @return Pointer to the retrieved value or null if such parameter
    /// doesn't exist.
    StampedValuePtr getGlobalParameter6(const ServerSelector& server_selector,
                                        const std::string& name) {
        StampedValueCollection parameters;

        auto const& tags = server_selector.getTags();
        for (auto const& tag : tags) {
            PsqlBindArray in_bindings;
            in_bindings.addTempString(tag.get());
            in_bindings.add(name);

            getGlobalParameters(GET_GLOBAL_PARAMETER6, in_bindings, parameters);
        }

        return (parameters.empty() ? StampedValuePtr() : *parameters.begin());
    }

    /// @brief Sends query to insert or update global parameter.
    ///
    /// @param server_selector Server selector.
    /// @param value StampedValue describing the parameter to create/update.
    void createUpdateGlobalParameter6(const db::ServerSelector& server_selector,
                                      const StampedValuePtr& value) {
        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        auto tag = getServerTag(server_selector, "creating or updating global parameter");

        PsqlBindArray in_bindings;
        in_bindings.addTempString(value->getName());
        in_bindings.addTempString(value->getValue());
        in_bindings.add(value->getType()),
        in_bindings.addTimestamp(value->getModificationTime()),
        in_bindings.addTempString(tag);
        in_bindings.addTempString(value->getName());

        PgSqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision audit_revision(this,
                                           PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                                           server_selector, "global parameter set",
                                           false);

        // Try to update the existing row.
        if (updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::UPDATE_GLOBAL_PARAMETER6,
                              in_bindings) == 0) {
            // No such parameter found, so let's insert it. We have to adjust the
            // bindings collection to match the prepared statement for insert.
            in_bindings.popBack();
            in_bindings.popBack();

            insertQuery(PgSqlConfigBackendDHCPv6Impl::INSERT_GLOBAL_PARAMETER6,
                        in_bindings);

            // Successfully inserted global parameter. Now, we have to associate it
            // with the server tag.
            PsqlBindArray attach_bindings;
            uint64_t pid = getLastInsertId("dhcp6_global_parameter", "id");
            attach_bindings.add(pid);   // id of newly inserted global.
            attach_bindings.addTimestamp(value->getModificationTime());
            attachElementToServers(PgSqlConfigBackendDHCPv6Impl::INSERT_GLOBAL_PARAMETER6_SERVER,
                                   server_selector, attach_bindings);
        }

        transaction.commit();
    }

    /// @brief Sends query to the database to retrieve multiple subnets.
    ///
    /// Query should order subnets by subnet_id.
    ///
    /// @param index Index of the query to be used.
    /// @param server_selector Server selector.
    /// @param in_bindings Input bindings specifying selection criteria. The
    /// size of the bindings collection must match the number of placeholders
    /// in the prepared statement. The input bindings collection must be empty
    /// if the query contains no WHERE clause.
    /// @param [out] subnets Reference to the container where fetched subnets
    /// will be inserted.
    void getSubnets6(const StatementIndex& index,
                     const ServerSelector& server_selector,
                     const PsqlBindArray& in_bindings,
                     Subnet6Collection& subnets) {
        uint64_t last_pool_id = 0;
        uint64_t last_pd_pool_id = 0;
        uint64_t last_pool_option_id = 0;
        uint64_t last_pd_pool_option_id = 0;
        uint64_t last_option_id = 0;
        Pool6Ptr last_pool;
        Pool6Ptr last_pd_pool;
        std::string last_tag;

        // Execute actual query.
        selectQuery(index, in_bindings,
                    [this, &subnets, &last_pool,  &last_pd_pool,
                     &last_pool_id, &last_pd_pool_id,
                     &last_pool_option_id, &last_pd_pool_option_id,
                     &last_option_id, &last_tag](PgSqlResult& r, int row) {
            // Create a convenience worker for the row.
            PgSqlResultRowWorker worker(r, row);

            // Get pointer to the last subnet in the collection.
            Subnet6Ptr last_subnet;
            if (!subnets.empty()) {
                last_subnet = *subnets.rbegin();
            }
            // Subnet_id is column 0.
            SubnetID subnet_id = worker.getInt(0) ;

            // Subnet has been returned. Assuming that subnets are ordered by
            // subnet identifier, if the subnet identifier of the current row
            // is different than the subnet identifier of the previously returned
            // row, it means that we have to construct new subnet object.
            if (!last_subnet || (last_subnet->getID() != subnet_id)) {
                // Reset per subnet component tracking and server tag because
                // we're now starting to process a new subnet.
                last_pool_id = 0;
                last_pd_pool_id = 0;
                last_pool_option_id = 0;
                last_pd_pool_option_id = 0;
                last_option_id = 0;
                last_pool.reset();
                last_pd_pool.reset();
                last_tag.clear();

                // Get subnet parameters required by the constructor first.

                // subnet_prefix at 1.
                std::string subnet_prefix = worker.getString(1);
                auto prefix_pair = Subnet6::parsePrefix(subnet_prefix);

                // preferred_lifetime (5)
                // min_preferred_lifetime (69)
                // max_preferred_lifetime (70)
                auto preferred_lifetime = worker.getTriplet(5, 69, 70);

                // renew_timer at 9.
                auto renew_timer = worker.getTriplet(9);

                // rebind_timer at 7.
                auto rebind_timer = worker.getTriplet(7);

                // valid_lifetime at 14.
                // min_valid_lifetime at 71.
                // max_valid_lifetime at 72.
                auto valid_lifetime = worker.getTriplet(14, 71, 72);

                // Create subnet with basic settings.
                last_subnet = Subnet6::create(prefix_pair.first, prefix_pair.second,
                                              renew_timer, rebind_timer,
                                              preferred_lifetime,
                                              valid_lifetime, subnet_id);

                // 0 and 1 are subnet_id and subnet_prefix

                // client_class at 2.
                if (!worker.isColumnNull(2)) {
                    last_subnet->allowClientClass(worker.getString(2));
                }

                // interface at 3.
                if (!worker.isColumnNull(3)) {
                    last_subnet->setIface(worker.getString(3));
                }

                // modification_ts at 4.
                last_subnet->setModificationTime(worker.getTimestamp(4));

                // preferred_lifetime is 5.

                if (!worker.isColumnNull(6)) {
                    last_subnet->setRapidCommit(worker.getBool(6));
                }

                // rebind_timer is 7.

                // Relay addresses at 8.
                setRelays(worker, 8, *last_subnet);

                // renew_timer is 9.

                // require_client_classes at 10.
                setRequiredClasses(worker, 10, [&last_subnet](const std::string& class_name) {
                    last_subnet->requireClientClass(class_name);
                });

                // reservations_global at 11.
                if (!worker.isColumnNull(11)) {
                    last_subnet->setReservationsGlobal(worker.getBool(11));
                }

                // shared_network_name at 12.
                if (!worker.isColumnNull(12)) {
                    last_subnet->setSharedNetworkName(worker.getString(12));
                }

                // user_context at 13.
                if (!worker.isColumnNull(13)) {
                    ElementPtr user_context = worker.getJSON(13);
                    if (user_context) {
                        last_subnet->setContext(user_context);
                    }
                }

                // valid_lifetime at 14.

                // 15 to 19 are pool
                // 20 to 25 are pd pool
                // 26 to 38 are pool option
                // 39 to 51 are pd pool option
                // 52 to 64 are option

                // calculate_tee_times at 65.
                if (!worker.isColumnNull(65)) {
                    last_subnet->setCalculateTeeTimes(worker.getBool(65));
                }

                // t1_percent at 66.
                if (!worker.isColumnNull(66)) {
                    last_subnet->setT1Percent(worker.getDouble(66));
                }

                // t2_percent at 67.
                if (!worker.isColumnNull(67)) {
                    last_subnet->setT2Percent(worker.getDouble(67));
                }

                // interface_id at 68.
                setInterfaceId(*last_subnet, worker, 68);

                // 69 and 70 are {min,max}_preferred_lifetime

                // 71 and 72 are {min,max}_valid_lifetime

                // 73 is pool client_class
                // 74 is pool require_client_classes
                // 75 is pool user_context
                // 76 is pd pool excluded_prefix
                // 77 is pd pool excluded_prefix_length
                // 78 is pd pool client_class
                // 79 is pd pool require_client_classes
                // 80 is pd pool user_context

                // ddns_send_updates at 81.
                if (!worker.isColumnNull(81)) {
                    last_subnet->setDdnsSendUpdates(worker.getBool(81));
                }

                // ddns_override_no_update at 82.
                if (!worker.isColumnNull(82)) {
                    last_subnet->setDdnsOverrideNoUpdate(worker.getBool(82));
                }

                // ddns_override_client_update at 83.
                if (!worker.isColumnNull(83)) {
                    last_subnet->setDdnsOverrideClientUpdate(worker.getBool(83));
                }

                // ddns_replace_client_name at 84.
                if (!worker.isColumnNull(84)) {
                    last_subnet->setDdnsReplaceClientNameMode(
                        static_cast<D2ClientConfig::ReplaceClientNameMode>(worker.getSmallInt(84)));
                }

                // ddns_generated_prefix at 85.
                if (!worker.isColumnNull(85)) {
                    last_subnet->setDdnsGeneratedPrefix(worker.getString(85));
                }

                // ddns_qualifying_suffix at 86.
                if (!worker.isColumnNull(86)) {
                    last_subnet->setDdnsQualifyingSuffix(worker.getString(86));
                }

                // reservations_in_subnet at 87.
                if (!worker.isColumnNull(87)) {
                    last_subnet->setReservationsInSubnet(worker.getBool(87));
                }

                // reservations_out_of_pool at 88.
                if (!worker.isColumnNull(88)) {
                    last_subnet->setReservationsOutOfPool(worker.getBool(88));
                }

                // cache_threshold at 89.
                if (!worker.isColumnNull(89)) {
                    last_subnet->setCacheThreshold(worker.getDouble(89));
                }

                // cache_max_age at 90.
                if (!worker.isColumnNull(90)) {
                    last_subnet->setCacheMaxAge(worker.getInt(90));
                }

                // server_tag at 91.

                // Subnet ready. Add it to the list.
                auto ret = subnets.insert(last_subnet);

                // subnets is a multi index container with unique indexes
                // but these indexes are unique too in the database,
                // so this is for sanity only.
                if (!ret.second) {
                    isc_throw(Unexpected, "add subnet failed");
                }
            }

            // Check for new server tags at 91.
            if (!worker.isColumnNull(91)) {
                std::string new_tag = worker.getString(91);
                if (last_tag != new_tag) {
                    if (!new_tag.empty() && !last_subnet->hasServerTag(ServerTag(new_tag))) {
                        last_subnet->setServerTag(new_tag);
                    }

                    last_tag = new_tag;
                }
            }

            // Pool is between 15 and 19 with extra between 73 and 75

            // If the row contains information about the pool and it
            // appears to be new pool entry (checked by comparing pool
            // id), let's create the new pool and add it to the
            // subnet.
            // pool id (15)
            // pool start_address (16)
            // pool end_address (17)
            if (!worker.isColumnNull(15) &&
                (worker.getInet6(16) != 0) &&
                (worker.getInet6(17) != 0) &&
                (worker.getBigInt(15) > last_pool_id)) {
                last_pool_id = worker.getBigInt(15);
                last_pool = Pool6::create(Lease::TYPE_NA,
                                          IOAddress(worker.getInet6(16)),
                                          IOAddress(worker.getInet6(17)));

                // pool subnet_id at 18 (ignored)
                // pool modification_ts at 19 (ignored)

                // pool client_class at 73.
                if (!worker.isColumnNull(73)) {
                    last_pool->allowClientClass(worker.getString(73));
                }

                // pool require_client_classes at 74.
                setRequiredClasses(worker, 74, [&last_pool](const std::string& class_name) {
                    last_pool->requireClientClass(class_name);
                });

                // pool user_context at 75.
                if (!worker.isColumnNull(75)) {
                    ElementPtr user_context = worker.getJSON(75);
                    if (user_context) {
                        last_pool->setContext(user_context);
                    }
                }

                last_subnet->addPool(last_pool);
            }

            // Pd Pool is between 20 and 25 with extra between 76 and 80

            // If the row contains information about the pd pool and
            // it appears to be new pd pool entry (checked by
            // comparing pd pool id), let's create the new pd pool and
            // add it to the subnet.
            // pd pool id (20)
            // pd pool prefix (21)
            // pd pool prefix_length (22)
            // pd pool delegated_prefix_length (23)
            if (!worker.isColumnNull(20) &&
                (!worker.getString(21).empty()) &&
                (worker.getSmallInt(22) != 0) &&
                (worker.getSmallInt(23) != 0) &&
                (worker.getBigInt(20) > last_pd_pool_id)) {

                // 24 is pd pool subnet_id (ignored)
                // 25 is pd pool modification_ts (ignored)

                // excluded_prefix (76) and excluded_prefix_length (77)
                IOAddress excluded_prefix = IOAddress::IPV6_ZERO_ADDRESS();
                if (!worker.isColumnNull(76)) {
                    excluded_prefix = worker.getInet6(76);
                }

                last_pd_pool_id = worker.getBigInt(20);
                last_pd_pool = Pool6::create(worker.getInet6(21),
                                             static_cast<uint8_t>(worker.getSmallInt(22)),
                                             static_cast<uint8_t>(worker.getSmallInt(23)),
                                             excluded_prefix,
                                             static_cast<uint8_t>(worker.getSmallInt(77)));

                // pd pool client_class (78)
                if (!worker.isColumnNull(78)) {
                    last_pd_pool->allowClientClass(worker.getString(78));
                }

                // pd pool require_client_classes at 79.
                setRequiredClasses(worker, 79, [&last_pd_pool](const std::string& class_name) {
                    last_pd_pool->requireClientClass(class_name);
                });

                // pd pool user_context at 80.
                if (!worker.isColumnNull(80)) {
                    ElementPtr user_context = worker.getJSON(80);
                    if (user_context) {
                        last_pd_pool->setContext(user_context);
                    }
                }

                last_subnet->addPool(last_pd_pool);
            }

            // Parse pool-specific option from 26 to 38.
            if (last_pool && !worker.isColumnNull(26) &&
                (last_pool_option_id < worker.getBigInt(26))) {
                last_pool_option_id = worker.getBigInt(26);

                OptionDescriptorPtr desc = processOptionRow(Option::V6, worker, 26);
                if (desc) {
                    last_pool->getCfgOption()->add(*desc, desc->space_name_);
                }
            }

            // Parse pd pool-specific option from 39 to 51.
            if (last_pd_pool && !worker.isColumnNull(39) &&
                (last_pd_pool_option_id < worker.getBigInt(39))) {
                last_pd_pool_option_id = worker.getBigInt(39);

                OptionDescriptorPtr desc = processOptionRow(Option::V6, worker, 39);
                if (desc) {
                    last_pd_pool->getCfgOption()->add(*desc, desc->space_name_);
                }
            }

            // Parse subnet-specific option from 52 to 64.
            if (!worker.isColumnNull(52) &&
                (last_option_id < worker.getBigInt(52))) {
                last_option_id = worker.getBigInt(52);

                OptionDescriptorPtr desc = processOptionRow(Option::V6, worker, 52);
                if (desc) {
                    last_subnet->getCfgOption()->add(*desc, desc->space_name_);
                }
            }
        });

        // Now that we're done fetching the whole subnet, we have to
        // check if it has matching server tags and toss it if it
        // doesn't. We skip matching the server tags if we're asking
        // for ANY subnet.
        auto& subnet_index = subnets.get<SubnetSubnetIdIndexTag>();
        tossNonMatchingElements(server_selector, subnet_index);
    }

    /// @brief Sends query to retrieve single subnet by id.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Pointer to the returned subnet or NULL if such subnet
    /// doesn't exist.
    Subnet6Ptr getSubnet6(const ServerSelector& server_selector,
                          const SubnetID& subnet_id) {
        if (server_selector.hasMultipleTags()) {
            isc_throw(InvalidOperation, "expected one server tag to be specified"
                      " while fetching a subnet. Got: "
                      << getServerTagsAsText(server_selector));
        }

        PsqlBindArray in_bindings;
        in_bindings.add(subnet_id);

        auto index = GET_SUBNET6_ID_NO_TAG;
        if (server_selector.amUnassigned()) {
            index = GET_SUBNET6_ID_UNASSIGNED;
        } else if (server_selector.amAny()) {
            index = GET_SUBNET6_ID_ANY;
        }

        Subnet6Collection subnets;
        getSubnets6(index, server_selector, in_bindings, subnets);

        return (subnets.empty() ? Subnet6Ptr() : *subnets.begin());
    }

    /// @brief Sends query to retrieve single subnet by prefix.
    ///
    /// The prefix should be in the following format: "2001:db8:1::/64".
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Pointer to the returned subnet or NULL if such subnet
    /// doesn't exist.
    Subnet6Ptr getSubnet6(const ServerSelector& server_selector,
                          const std::string& subnet_prefix) {
        if (server_selector.hasMultipleTags()) {
            isc_throw(InvalidOperation, "expected one server tag to be specified"
                      " while fetching a subnet. Got: "
                      << getServerTagsAsText(server_selector));
        }

        PsqlBindArray in_bindings;
        in_bindings.add(subnet_prefix);

        auto index = GET_SUBNET6_PREFIX_NO_TAG;
        if (server_selector.amUnassigned()) {
            index = GET_SUBNET6_PREFIX_UNASSIGNED;
        } else if (server_selector.amAny()) {
            index = GET_SUBNET6_PREFIX_ANY;
        }

        Subnet6Collection subnets;
        getSubnets6(index, server_selector, in_bindings, subnets);

        return (subnets.empty() ? Subnet6Ptr() : *subnets.begin());
    }

    /// @brief Sends query to retrieve all subnets.
    ///
    /// @param server_selector Server selector.
    /// @param [out] subnets Reference to the subnet collection structure where
    /// subnets should be inserted.
    void getAllSubnets6(const ServerSelector& server_selector,
                        Subnet6Collection& subnets) {
        if (server_selector.amAny()) {
            isc_throw(InvalidOperation, "fetching all subnets for ANY "
                      "server is not supported");
        }

        auto index = (server_selector.amUnassigned() ? GET_ALL_SUBNETS6_UNASSIGNED :
                      GET_ALL_SUBNETS6);
        PsqlBindArray in_bindings;
        getSubnets6(index, server_selector, in_bindings, subnets);
    }

    /// @brief Sends query to retrieve modified subnets.
    ///
    /// @param server_selector Server selector.
    /// @param modification_ts Lower bound modification timestamp.
    /// @param [out] subnets Reference to the subnet collection structure where
    /// subnets should be inserted.
    void getModifiedSubnets6(const ServerSelector& server_selector,
                             const boost::posix_time::ptime& modification_ts,
                             Subnet6Collection& subnets) {
        if (server_selector.amAny()) {
            isc_throw(InvalidOperation, "fetching modified subnets for ANY "
                      "server is not supported");
        }

        PsqlBindArray in_bindings;
        in_bindings.addTimestamp(modification_ts);

        auto index = (server_selector.amUnassigned() ? GET_MODIFIED_SUBNETS6_UNASSIGNED :
                      GET_MODIFIED_SUBNETS6);
        getSubnets6(index, server_selector, in_bindings, subnets);
    }

    /// @brief Sends query to retrieve all subnets belonging to a shared network.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of the shared network for which the
    /// subnets should be retrieved.
    /// @param [out] subnets Reference to the subnet collection structure where
    /// subnets should be inserted.
    void getSharedNetworkSubnets6(const ServerSelector& server_selector,
                                  const std::string& shared_network_name,
                                  Subnet6Collection& subnets) {
        PsqlBindArray in_bindings;
        in_bindings.add(shared_network_name);
        getSubnets6(GET_SHARED_NETWORK_SUBNETS6, server_selector, in_bindings, subnets);
    }

    /// @brief Sends query to retrieve multiple pools.
    ///
    /// Query should order pools by id.
    ///
    /// @param index Index of the query to be used.
    /// @param in_bindings Input bindings specifying selection criteria. The
    /// size of the bindings collection must match the number of placeholders
    /// in the prepared statement. The input bindings collection must be empty
    /// if the query contains no WHERE clause.
    /// @param [out] pools Reference to the container where fetched pools
    /// will be inserted.
    /// @param [out] pool_ids Identifiers of the pools returned in @c pools
    /// argument.
    void getPools(const StatementIndex& index,
                  const PsqlBindArray& in_bindings,
                  PoolCollection& pools,
                  std::vector<uint64_t>& pool_ids) {
        uint64_t last_pool_id = 0;
        uint64_t last_pool_option_id = 0;
        Pool6Ptr last_pool;

        selectQuery(index, in_bindings,
                    [this, &last_pool_id, &last_pool_option_id, &last_pool, &pools, &pool_ids]
                    (PgSqlResult& r, int row) {
            // Create a convenience worker for the row.
            PgSqlResultRowWorker worker(r, row);

            // Pool id is column 0.
            auto id = worker.getBigInt(0) ;
            if (id > last_pool_id) {
                // pool start_address (1)
                // pool end_address (2)
                last_pool_id = id;

                last_pool = Pool6::create(Lease::TYPE_NA, worker.getInet6(1), worker.getInet6(2));

                // pool subnet_id (3) (ignored)

                // pool client_class (4)
                if (!worker.isColumnNull(4)) {
                    last_pool->allowClientClass(worker.getString(4));
                }

                // pool require_client_classes (5)
                setRequiredClasses(worker, 5, [&last_pool](const std::string& class_name) {
                    last_pool->requireClientClass(class_name);
                });

                // pool user_context (6)
                if (!worker.isColumnNull(6)) {
                    ElementPtr user_context = worker.getJSON(6);
                    if (user_context) {
                        last_pool->setContext(user_context);
                    }
                }

                // pool: modification_ts (7) (ignored)

                pools.push_back(last_pool);
                pool_ids.push_back(last_pool_id);
            }

            // Parse pool specific option (8).
            if (last_pool && !worker.isColumnNull(8) &&
                (last_pool_option_id < worker.getBigInt(8))) {
                last_pool_option_id = worker.getBigInt(8);

                OptionDescriptorPtr desc = processOptionRow(Option::V6, worker, 8);
                if (desc) {
                    last_pool->getCfgOption()->add(*desc, desc->space_name_);
                }
            }
        });
    }

    /// @brief Sends query to retrieve multiple pd pools.
    ///
    /// Query should order pd pools by id.
    ///
    /// @param index Index of the query to be used.
    /// @param in_bindings Input bindings specifying selection criteria. The
    /// size of the bindings collection must match the number of placeholders
    /// in the prepared statement. The input bindings collection must be empty
    /// if the query contains no WHERE clause.
    /// @param [out] pd_pools Reference to the container where fetched pools
    /// will be inserted.
    /// @param [out] pd_pool_ids Identifiers of the pd pools returned in
    /// @c pd_pools argument.
    void getPdPools(const StatementIndex& index,
                    const PsqlBindArray& in_bindings,
                    PoolCollection& pd_pools,
                    std::vector<uint64_t>& pd_pool_ids) {
        uint64_t last_pd_pool_id = 0;
        uint64_t last_pd_pool_option_id = 0;
        Pool6Ptr last_pd_pool;

        selectQuery(index, in_bindings,
                    [this, &last_pd_pool_id, &last_pd_pool_option_id,
                     &last_pd_pool, &pd_pools, &pd_pool_ids]
                    (PgSqlResult& r, int row) {
            // Create a convenience worker for the row.
            PgSqlResultRowWorker worker(r, row);

            // Pool id is column 0.
            auto id = worker.getBigInt(0) ;
            if (id > last_pd_pool_id) {
                last_pd_pool_id = id;

                // pd pool prefix (1)
                // pd pool prefix_length (2)
                // pd pool delegated_prefix_length (3)

                // excluded_prefix (5) and excluded_prefix_length (6)
                IOAddress excluded_prefix = IOAddress::IPV6_ZERO_ADDRESS();
                if (!worker.isColumnNull(5)) {
                    excluded_prefix = worker.getInet6(5);
                }

                last_pd_pool = Pool6::create(worker.getInet6(1),
                                             static_cast<uint8_t>(worker.getSmallInt(2)),
                                             static_cast<uint8_t>(worker.getSmallInt(3)),
                                             excluded_prefix,
                                             static_cast<uint8_t>(worker.getSmallInt(6)));

                // pd pool subnet_id (4) (ignored)

                // pool client_class (7)
                if (!worker.isColumnNull(7)) {
                    last_pd_pool->allowClientClass(worker.getString(7));
                }

                // pool require_client_classes (8)
                setRequiredClasses(worker, 8, [&last_pd_pool](const std::string& class_name) {
                    last_pd_pool->requireClientClass(class_name);
                });

                // pd pool user_context (9)
                if (!worker.isColumnNull(9)) {
                    ElementPtr user_context = worker.getJSON(9);
                    if (user_context) {
                        last_pd_pool->setContext(user_context);
                    }
                }

                // pd pool modification_ts (10) (ignored)

                pd_pools.push_back(last_pd_pool);
                pd_pool_ids.push_back(last_pd_pool_id);
            }

            // Parse pd pool specific option between 11 and 24.
            if (last_pd_pool && !worker.isColumnNull(11) &&
                (last_pd_pool_option_id < worker.getBigInt(11))) {
                last_pd_pool_option_id = worker.getBigInt(11);

                OptionDescriptorPtr desc = processOptionRow(Option::V6, worker, 11);
                if (desc) {
                    last_pd_pool->getCfgOption()->add(*desc, desc->space_name_);
                }
            }
        });
    }

    /// @brief Sends query to retrieve single pool by address range.
    ///
    /// @param server_selector Server selector.
    /// @param pool_start_address Lower bound pool address.
    /// @param pool_end_address Upper bound pool address.
    /// @param pool_id Pool identifier for the returned pool.
    /// @return Pointer to the pool or null if no such pool found.
    Pool6Ptr getPool6(const ServerSelector& server_selector,
                      const IOAddress& pool_start_address,
                      const IOAddress& pool_end_address,
                      uint64_t& pool_id) {
        PoolCollection pools;
        std::vector<uint64_t> pool_ids;

        if (server_selector.amAny()) {
            PsqlBindArray in_bindings;
            in_bindings.addInet6(pool_start_address);
            in_bindings.addInet6(pool_end_address);
            getPools(GET_POOL6_RANGE_ANY, in_bindings, pools, pool_ids);
        } else {
            auto const& tags = server_selector.getTags();
            for (auto const& tag : tags) {
                PsqlBindArray in_bindings;
                in_bindings.addTempString(tag.get());
                in_bindings.addInet6(pool_start_address);
                in_bindings.addInet6(pool_end_address);

                getPools(GET_POOL6_RANGE, in_bindings, pools, pool_ids);
                // Break if something is found?
            }
        }

        // Return upon the first pool found.
        if (!pools.empty()) {
            pool_id = pool_ids[0];
            return (boost::dynamic_pointer_cast<Pool6>(*pools.begin()));
        }

        pool_id = 0;

        return (Pool6Ptr());
    }

    /// @brief Sends query to retrieve single pd pool.
    ///
    /// @param server_selector Server selector.
    /// @param pd_pool_prefix Address part of the pd pool prefix.
    /// @param pd_pool_prefix_length Length of the pd pool prefix.
    /// @param pd_pool_id Pool identifier for the returned pool.
    /// @return Pointer to the pool or null if no such pool found.
    Pool6Ptr getPdPool6(const ServerSelector& server_selector,
                        const asiolink::IOAddress& pd_pool_prefix,
                        const uint8_t pd_pool_prefix_length,
                        uint64_t& pd_pool_id) {
        PoolCollection pd_pools;
        std::vector<uint64_t> pd_pool_ids;

        if (server_selector.amAny()) {
            PsqlBindArray in_bindings;
            in_bindings.addTempString(pd_pool_prefix.toText());
            in_bindings.add(pd_pool_prefix_length);
            getPdPools(GET_PD_POOL_ANY, in_bindings, pd_pools, pd_pool_ids);
        } else {
            auto const& tags = server_selector.getTags();
            for (auto const& tag : tags) {
                PsqlBindArray in_bindings;
                in_bindings.addTempString(tag.get());
                in_bindings.addTempString(pd_pool_prefix.toText());
                in_bindings.add(pd_pool_prefix_length);
                getPdPools(GET_PD_POOL, in_bindings, pd_pools, pd_pool_ids);
            }
        }

        if (!pd_pools.empty()) {
            pd_pool_id = pd_pool_ids[0];
            return (boost::dynamic_pointer_cast<Pool6>(*pd_pools.begin()));
        }

        pd_pool_id = 0;

        return (Pool6Ptr());
    }

    /// @brief Sends query to insert or update subnet.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Pointer to the subnet to be inserted or updated.
    void createUpdateSubnet6(const ServerSelector& server_selector,
                             const Subnet6Ptr& subnet) {
        if (server_selector.amAny()) {
            isc_throw(InvalidOperation, "creating or updating a subnet for ANY"
                      " server is not supported");

        } else if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        // Create input bindings.
        PsqlBindArray in_bindings;
        in_bindings.add(subnet->getID());
        in_bindings.addTempString(subnet->toText());
        in_bindings.addOptional(subnet->getClientClass(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getIface(Network::Inheritance::NONE));
        in_bindings.addTimestamp(subnet->getModificationTime());
        in_bindings.add(subnet->getPreferred(Network::Inheritance::NONE));
        in_bindings.addMin(subnet->getPreferred(Network::Inheritance::NONE));
        in_bindings.addMax(subnet->getPreferred(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getRapidCommit(Network::Inheritance::NONE));
        in_bindings.add(subnet->getT2(Network::Inheritance::NONE));
        addRelayBinding(in_bindings, subnet);
        in_bindings.add(subnet->getT1(Network::Inheritance::NONE));
        addRequiredClassesBinding(in_bindings, subnet);
        in_bindings.addOptional(subnet->getReservationsGlobal(Network::Inheritance::NONE));

        // Add shared network.
        SharedNetwork6Ptr shared_network;
        subnet->getSharedNetwork(shared_network);

        // Check if the subnet is associated with a shared network instance.
        // If it is, create the binding using the name of the shared network.
        if (shared_network) {
            in_bindings.addTempString(shared_network->getName());

        // If the subnet is associated with a shared network by name (no
        // shared network instance), use this name to create the binding.
        // This may be the case if the subnet is added as a result of
        // receiving a control command that merely specifies shared
        // network name. In that case, it is expected that the shared
        // network data is already stored in the database.
        } else if (!subnet->getSharedNetworkName().empty()) {
            in_bindings.addTempString(subnet->getSharedNetworkName());

        // If the subnet is not associated with a shared network, create
        // null binding.
        } else {
             in_bindings.addNull();
        }

        in_bindings.add(subnet->getContext());
        in_bindings.add(subnet->getValid(Network::Inheritance::NONE));
        in_bindings.addMin(subnet->getValid(Network::Inheritance::NONE));
        in_bindings.addMax(subnet->getValid(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getCalculateTeeTimes(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getT1Percent(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getT2Percent(Network::Inheritance::NONE));
        addInterfaceIdBinding(in_bindings, *subnet);
        in_bindings.addOptional(subnet->getDdnsSendUpdates(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getDdnsOverrideNoUpdate(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getDdnsOverrideClientUpdate(Network::Inheritance::NONE));
        addDdnsReplaceClientNameBinding(in_bindings, subnet);
        in_bindings.addOptional(subnet->getDdnsGeneratedPrefix(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getDdnsQualifyingSuffix(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getReservationsInSubnet(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getReservationsOutOfPool(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getCacheThreshold(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getCacheMaxAge(Network::Inheritance::NONE));

        // Start transaction.
        PgSqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision audit_revision(this,
                                           PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                                           server_selector, "subnet set", true);

        // Create a savepoint in case we are called as part of larger
        // transaction.
        conn_.createSavepoint("createUpdateSubnet6");

        try {

            insertQuery(PgSqlConfigBackendDHCPv6Impl::INSERT_SUBNET6, in_bindings);

        } catch (const DuplicateEntry&) {
            // It already exists, rollback to the savepoint to preserve
            // any prior work.
            conn_.rollbackToSavepoint("createUpdateSubnet6");

            // We're updating, so we need to remove any existing pools and options.
            deletePools6(subnet);
            deletePdPools6(subnet);
            deleteOptions6(ServerSelector::ANY(), subnet);

            // Now we need to add two more bindings for WHERE clause.
            in_bindings.add(subnet->getID());
            in_bindings.addTempString(subnet->toText());

            // Attempt the update.
            auto cnt = updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::UPDATE_SUBNET6,
                                         in_bindings);
            if (!cnt) {
                // Possible only if someone deleted it since we tried to insert it
                // or the query is broken.
                isc_throw(Unexpected, "Update subnet failed to find subnet id: "
                          << subnet->getID() << ", prefix: " << subnet->toText());
            }

            // Remove existing server association.
            PsqlBindArray server_bindings;
            server_bindings.add(subnet->getID());
            updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_SERVER,
                              server_bindings);
        }

        // Subnet was successfully created/updated.

        // Insert associations with the servers.
        PsqlBindArray attach_bindings;
        attach_bindings.add(subnet->getID());
        attach_bindings.addTimestamp(subnet->getModificationTime());
        attachElementToServers(PgSqlConfigBackendDHCPv6Impl::INSERT_SUBNET6_SERVER,
                               server_selector, attach_bindings);

        // (Re)create pools.
        for (auto pool : subnet->getPools(Lease::TYPE_NA)) {
            createPool6(server_selector, boost::dynamic_pointer_cast<Pool6>(pool),
                        subnet);
        }

        // (Re)create pd pools.
        for (auto pd_pool : subnet->getPools(Lease::TYPE_PD)) {
            createPdPool6(server_selector, boost::dynamic_pointer_cast<Pool6>(pd_pool),
                          subnet);
        }

        // (Re)create options.
        auto option_spaces = subnet->getCfgOption()->getOptionSpaceNames();
        for (auto option_space : option_spaces) {
            OptionContainerPtr options = subnet->getCfgOption()->getAll(option_space);
            for (auto desc = options->begin(); desc != options->end(); ++desc) {
                OptionDescriptorPtr desc_copy = OptionDescriptor::create(*desc);
                desc_copy->space_name_ = option_space;
                createUpdateOption6(server_selector, subnet->getID(), desc_copy,
                                    true);
            }
        }

        // Commit the work.
        transaction.commit();
    }

    /// @brief Inserts new IPv6 pool to the database.
    ///
    /// @param server_selector Server selector.
    /// @param pool Pointer to the pool to be inserted.
    /// @param subnet Pointer to the subnet that this pool belongs to.
    void createPool6(const ServerSelector& server_selector,
                     const Pool6Ptr& pool,
                     const Subnet6Ptr& subnet) {
        // Create the input bindings.
        PsqlBindArray in_bindings;
        in_bindings.addInet6(pool->getFirstAddress());
        in_bindings.addInet6(pool->getLastAddress());
        in_bindings.add(subnet->getID());
        in_bindings.addOptional(pool->getClientClass());
        addRequiredClassesBinding(in_bindings, pool);
        in_bindings.add(pool->getContext());
        in_bindings.addTimestamp(subnet->getModificationTime());

        // Attempt to INSERT the pool.
        insertQuery(PgSqlConfigBackendDHCPv6Impl::INSERT_POOL6, in_bindings);

        // Get the id of the newly inserted pool.
        uint64_t pool_id = getLastInsertId("dhcp6_pool", "id");

        // Add the pool's options.
        auto option_spaces = pool->getCfgOption()->getOptionSpaceNames();
        for (auto option_space : option_spaces) {
            OptionContainerPtr options = pool->getCfgOption()->getAll(option_space);
            for (auto desc = options->begin(); desc != options->end(); ++desc) {
                OptionDescriptorPtr desc_copy = OptionDescriptor::create(*desc);
                desc_copy->space_name_ = option_space;
                createUpdateOption6(server_selector, Lease::TYPE_NA,
                                    pool_id, desc_copy, true);
            }
        }
    }

    /// @brief Inserts new IPv6 pd pool to the database.
    ///
    /// @param server_selector Server selector.
    /// @param pd_pool Pointer to the pd pool to be inserted.
    /// @param subnet Pointer to the subnet that this pd pool belongs to.
    void createPdPool6(const ServerSelector& server_selector,
                       const Pool6Ptr& pd_pool,
                       const Subnet6Ptr& subnet) {
        int plen = prefixLengthFromRange(pd_pool->getFirstAddress(),
                                         pd_pool->getLastAddress());

        // Extract excluded prefix components.
        Optional<std::string> xprefix_txt;
        uint8_t xlen = 0;
        const Option6PDExcludePtr& xopt = pd_pool->getPrefixExcludeOption();
        if (xopt) {
            const IOAddress& prefix = pd_pool->getFirstAddress();
            const IOAddress& xprefix = xopt->getExcludedPrefix(prefix, pd_pool->getLength());
            xprefix_txt = xprefix.toText();
            xlen = xopt->getExcludedPrefixLength();
        }

        // Create the input bindings.
        PsqlBindArray in_bindings;
        in_bindings.addInet6(pd_pool->getFirstAddress());
        in_bindings.add(plen);
        in_bindings.add(pd_pool->getLength());
        in_bindings.add(subnet->getID());
        in_bindings.addOptional(xprefix_txt);
        in_bindings.add(xlen);
        in_bindings.addOptional(pd_pool->getClientClass());
        addRequiredClassesBinding(in_bindings, pd_pool);
        in_bindings.add(pd_pool->getContext());
        in_bindings.addTimestamp(subnet->getModificationTime());

        // Attempt to INSERT the pool.
        insertQuery(PgSqlConfigBackendDHCPv6Impl::INSERT_PD_POOL, in_bindings);

        // Get the id of the newly inserted pool.
        uint64_t pd_pool_id = getLastInsertId("dhcp6_pd_pool", "id");

        // Add the pool's options.
        auto option_spaces = pd_pool->getCfgOption()->getOptionSpaceNames();
        for (auto option_space : option_spaces) {
            OptionContainerPtr options = pd_pool->getCfgOption()->getAll(option_space);
            for (auto desc = options->begin(); desc != options->end(); ++desc) {
                OptionDescriptorPtr desc_copy = OptionDescriptor::create(*desc);
                desc_copy->space_name_ = option_space;
                createUpdateOption6(server_selector, Lease::TYPE_PD,
                                    pd_pool_id, desc_copy, true);
            }
        }
    }

    /// @brief Sends a query to delete data from a table.
    ///
    /// If creates a new audit revision for this change if such audit
    /// revision doesn't exist yet (using ScopedAuditRevision mechanism).
    ///
    /// @tparam Args type of the arguments to be passed to one of the existing
    /// @c deleteFromTable methods.
    /// @param server_selector server selector.
    /// @param operation operation which results in calling this function. This is
    /// used for logging purposes.
    /// @param log_message log message to be associated with the audit revision.
    /// @param cascade_delete boolean flag indicating if we're performing
    /// cascade delete. If set to true, the audit entries for the child
    /// objects (e.g. DHCPoptions) won't be created.
    /// @param keys arguments to be passed to one of the existing
    /// @c deleteFromTable methods.
    ///
    /// @return Number of deleted entries.
    template<typename... Args>
    uint64_t deleteTransactional(const int index,
                                 const db::ServerSelector& server_selector,
                                 const std::string& operation,
                                 const std::string& log_message,
                                 const bool cascade_delete,
                                 Args&&... keys) {
        PgSqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           server_selector, log_message, cascade_delete);

        auto count = deleteFromTable(index, server_selector, operation, keys...);

        transaction.commit();

        return (count);
    }

    /// @brief Sends query to delete subnet by id.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of the subnet to be deleted.
    /// @return Number of deleted subnets.
    uint64_t deleteSubnet6(const ServerSelector& server_selector,
                           const SubnetID& subnet_id) {
        int index = (server_selector.amAny() ?
                     PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_ID_ANY :
                     PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_ID_WITH_TAG);
        return (deleteTransactional(index, server_selector,
                                    "deleting a subnet", "subnet deleted",
                                    true, static_cast<uint32_t>(subnet_id)));
    }

    /// @brief Sends query to delete subnet by id.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be deleted.
    /// @return Number of deleted subnets.
    uint64_t deleteSubnet6(const ServerSelector& server_selector,
                           const std::string& subnet_prefix) {
        int index = (server_selector.amAny() ?
                     PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_PREFIX_ANY :
                     PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_PREFIX_WITH_TAG);
        return (deleteTransactional(index, server_selector,
                                    "deleting a subnet", "subnet deleted",
                                    true, subnet_prefix));
    }

    /// @brief Deletes pools belonging to a subnet from the database.
    ///
    /// The query deletes all pools associated with the subnet's
    /// identifier or prefix.
    /// @param subnet Pointer to the subnet for which pools should be
    /// deleted.
    uint64_t deletePools6(const Subnet6Ptr& subnet) {
        PsqlBindArray in_bindings;
        in_bindings.add(subnet->getID());
        in_bindings.addTempString(subnet->toText());

        // Run DELETE.
        return (updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::DELETE_POOLS6,
                                  in_bindings));
    }

    /// @brief Deletes prefix delegation pools belonging to a subnet from
    /// the database.
    ///
    /// The query deletes all pd pools associated with the subnet's
    /// identifier or prefix.
    /// @param subnet Pointer to the subnet for which pd pools should be
    /// deleted.
    uint64_t deletePdPools6(const Subnet6Ptr& subnet) {
        PsqlBindArray in_bindings;
        in_bindings.add(subnet->getID());
        in_bindings.addTempString(subnet->toText());

        // Run DELETE.
        return (updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::DELETE_PD_POOLS,
                                  in_bindings));
    }

    /// @brief Sends query to the database to retrieve multiple shared
    /// networks.
    ///
    /// Query should order shared networks by id.
    ///
    /// @param index Index of the query to be used.
    /// @param server_selector Server selector.
    /// @param in_bindings Input bindings specifying selection criteria. The
    /// size of the bindings collection must match the number of placeholders
    /// in the prepared statement. The input bindings collection must be empty
    /// if the query contains no WHERE clause.
    /// @param [out] shared_networks Reference to the container where fetched
    /// shared networks will be inserted.
    void getSharedNetworks6(const StatementIndex& index,
                            const ServerSelector& server_selector,
                            const PsqlBindArray& in_bindings,
                            SharedNetwork6Collection& shared_networks) {
        uint64_t last_network_id = 0;
        uint64_t last_option_id = 0;
        std::string last_tag;

        selectQuery(index, in_bindings,
                    [this, &shared_networks, &last_network_id, &last_option_id, &last_tag]
                    (PgSqlResult& r, int row) {
            // Create a convenience worker for the row.
            PgSqlResultRowWorker worker(r, row);

            SharedNetwork6Ptr last_network;
            if (!shared_networks.empty()) {
                last_network = *shared_networks.rbegin();
            }

            // Network id is column 0.
            auto network_id = worker.getBigInt(0) ;

            // If this is the first shared network or the shared network id in this
            // row points to the next shared network we use the data in the
            // row to create the new shared network instance.
            if (last_network_id != network_id) {
                last_network_id = network_id;

                // Reset per shared network component tracking and server tag because
                // we're now starting to process a new shared network.
                last_option_id = 0;
                last_tag.clear();

                // name at 1.
                last_network = SharedNetwork6::create(worker.getString(1));
                last_network->setId(last_network_id);

                // client_class at 2.
                if (!worker.isColumnNull(2)) {
                    last_network->allowClientClass(worker.getString(2));
                }

                // interface at 3.
                if (!worker.isColumnNull(3)) {
                    last_network->setIface(worker.getString(3));
                }

                // modification_ts at 4.
                last_network->setModificationTime(worker.getTimestamp(4));

                // preferred_lifetime (5)
                // min_preferred_lifetime (31)
                // max_preferred_lifetime (32)
                last_network->setPreferred(worker.getTriplet(5, 31, 32));

                // rapid_commit at 6.
                if (!worker.isColumnNull(6)) {
                    last_network->setRapidCommit(worker.getBool(6));
                }

                // rebind_timer at 7.
                if (!worker.isColumnNull(7)) {
                    last_network->setT2(worker.getTriplet(7));
                }

                // Relay addresses at 8.
                setRelays(worker, 8, *last_network);

                // renew_timer at 9.
                if (!worker.isColumnNull(9)) {
                    last_network->setT1(worker.getTriplet(9));
                }

                // require_client_classes at 10.
                setRequiredClasses(worker, 10, [&last_network](const std::string& class_name) {
                    last_network->requireClientClass(class_name);
                });

                // reservations_global at 11.
                if (!worker.isColumnNull(11)) {
                    last_network->setReservationsGlobal(worker.getBool(11));
                }

                // user_context at 12.
                if (!worker.isColumnNull(12)) {
                    ElementPtr user_context = worker.getJSON(12);
                    if (user_context) {
                        last_network->setContext(user_context);
                    }
                }

                // valid_lifetime at 13.
                // min_valid_lifetime at 33.
                // max_valid_lifetime at 34.
                if (!worker.isColumnNull(13)) {
                    last_network->setValid(worker.getTriplet(13, 33, 34));
                }

                // option from 14 to 26.

                // calculate_tee_times at 27.
                if (!worker.isColumnNull(27)) {
                    last_network->setCalculateTeeTimes(worker.getBool(27));
                }

                // t1_percent at 28.
                if (!worker.isColumnNull(28)) {
                    last_network->setT1Percent(worker.getDouble(28));
                }

                // t2_percent at 29.
                if (!worker.isColumnNull(29)) {
                    last_network->setT2Percent(worker.getDouble(29));
                }

                // interface_id at 30.
                setInterfaceId(*last_network, worker, 30);

                // min_preferred_lifetime at 31.
                // max_preferred_lifetime at 32.
                // min_valid_lifetime at 33.
                // max_valid_lifetime at 34.

                // ddns_send_updates at 35.
                if (!worker.isColumnNull(35)) {
                    last_network->setDdnsSendUpdates(worker.getBool(35));
                }

                // ddns_override_no_update at 36.
                if (!worker.isColumnNull(36)) {
                    last_network->setDdnsOverrideNoUpdate(worker.getBool(36));
                }

                // ddns_override_client_update at 37.
                if (!worker.isColumnNull(37)) {
                    last_network->setDdnsOverrideClientUpdate(worker.getBool(37));
                }

                // ddns_replace_client_name at 38.
                if (!worker.isColumnNull(38)) {
                    last_network->setDdnsReplaceClientNameMode(
                        static_cast<D2ClientConfig::ReplaceClientNameMode>(worker.getSmallInt(38)));
                }

                // ddns_generated_prefix at 39.
                if (!worker.isColumnNull(39)) {
                    last_network->setDdnsGeneratedPrefix(worker.getString(39));
                }

                // ddns_qualifying_suffix at 40.
                if (!worker.isColumnNull(40)) {
                    last_network->setDdnsQualifyingSuffix(worker.getString(40));
                }

                // reservations_in_subnet at 41.
                if (!worker.isColumnNull(41)) {
                    last_network->setReservationsInSubnet(worker.getBool(41));
                }

                // reservations_in_subnet at 42.
                if (!worker.isColumnNull(42)) {
                    last_network->setReservationsOutOfPool(worker.getBool(42));
                }

                // cache_threshold at 43.
                if (!worker.isColumnNull(43)) {
                    last_network->setCacheThreshold(worker.getDouble(43));
                }

                // cache_max_age at 44.
                if (!worker.isColumnNull(44)) {
                    last_network->setCacheMaxAge(worker.getInt(44));
                }

                // server_tag at 45.

                // Add the shared network.
                auto ret = shared_networks.push_back(last_network);

                // shared_networks is a multi index container with an unique
                // index but this index is unique too in the database,
                // so this is for sanity only.
                if (!ret.second) {
                    isc_throw(Unexpected, "add shared network failed");
                }
            }

            // Check for new server tags.
            if (!worker.isColumnNull(45)) {
                std::string new_tag = worker.getString(45);
                if (last_tag != new_tag) {
                    if (!new_tag.empty() && !last_network->hasServerTag(ServerTag(new_tag))) {
                        last_network->setServerTag(new_tag);
                    }

                    last_tag = new_tag;
                }
            }

            // Parse network-specific option from 14 to 26.
            if (!worker.isColumnNull(14) &&
                (last_option_id < worker.getBigInt(14))) {
                last_option_id = worker.getBigInt(14);

                OptionDescriptorPtr desc = processOptionRow(Option::V6, worker, 14);
                if (desc) {
                    last_network->getCfgOption()->add(*desc, desc->space_name_);
                }
            }
        });

        // Now that we're done fetching the whole network, we have to
        // check if it has matching server tags and toss it if it
        // doesn't. We skip matching the server tags if we're asking
        // for ANY shared network.
        auto& sn_index = shared_networks.get<SharedNetworkRandomAccessIndexTag>();
        tossNonMatchingElements(server_selector, sn_index);
    }

    /// @brief Sends query to retrieve single shared network by name.
    ///
    /// @param server_selector Server selector.
    /// @param name Shared network name.
    ///
    /// @return Pointer to the returned shared network or NULL if such shared
    /// network doesn't exist.
    SharedNetwork6Ptr getSharedNetwork6(const ServerSelector& server_selector,
                                        const std::string& name) {
        if (server_selector.hasMultipleTags()) {
            isc_throw(InvalidOperation, "expected one server tag to be specified"
                      " while fetching a shared network. Got: "
                      << getServerTagsAsText(server_selector));
        }

        PsqlBindArray in_bindings;
        in_bindings.add(name);

        auto index = PgSqlConfigBackendDHCPv6Impl::GET_SHARED_NETWORK6_NAME_NO_TAG;
        if (server_selector.amUnassigned()) {
            index = PgSqlConfigBackendDHCPv6Impl::GET_SHARED_NETWORK6_NAME_UNASSIGNED;
        } else if (server_selector.amAny()) {
            index = PgSqlConfigBackendDHCPv6Impl::GET_SHARED_NETWORK6_NAME_ANY;
        }

        SharedNetwork6Collection shared_networks;
        getSharedNetworks6(index, server_selector, in_bindings, shared_networks);

        return (shared_networks.empty() ? SharedNetwork6Ptr() : *shared_networks.begin());
    }

    /// @brief Sends query to retrieve all shared networks.
    ///
    /// @param server_selector Server selector.
    /// @param [out] shared_networks Reference to the shared networks collection
    /// structure where shared networks should be inserted.
    void getAllSharedNetworks6(const ServerSelector& server_selector,
                               SharedNetwork6Collection& shared_networks) {
        if (server_selector.amAny()) {
            isc_throw(InvalidOperation, "fetching all shared networks for ANY "
                      "server is not supported");
        }

        auto index = (server_selector.amUnassigned() ?
                      PgSqlConfigBackendDHCPv6Impl::GET_ALL_SHARED_NETWORKS6_UNASSIGNED :
                      PgSqlConfigBackendDHCPv6Impl::GET_ALL_SHARED_NETWORKS6);

        PsqlBindArray in_bindings;
        getSharedNetworks6(index, server_selector, in_bindings, shared_networks);
    }

    /// @brief Sends query to retrieve modified shared networks.
    ///
    /// @param server_selector Server selector.
    /// @param modification_ts Lower bound modification timestamp.
    /// @param [out] shared_networks Reference to the shared networks collection
    /// structure where shared networks should be inserted.
    void getModifiedSharedNetworks6(const ServerSelector& server_selector,
                                    const boost::posix_time::ptime& modification_ts,
                                    SharedNetwork6Collection& shared_networks) {
        if (server_selector.amAny()) {
            isc_throw(InvalidOperation, "fetching modified shared networks for ANY "
                      "server is not supported");
        }

        PsqlBindArray in_bindings;
        in_bindings.addTimestamp(modification_ts);

        auto index = (server_selector.amUnassigned() ?
                      PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_SHARED_NETWORKS6_UNASSIGNED :
                      PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_SHARED_NETWORKS6);
        getSharedNetworks6(index, server_selector, in_bindings, shared_networks);
    }

    /// @brief Sends query to insert or update shared network.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Pointer to the shared network to be inserted or updated.
    void createUpdateSharedNetwork6(const ServerSelector& server_selector,
                                    const SharedNetwork6Ptr& shared_network) {
        if (server_selector.amAny()) {
            isc_throw(InvalidOperation, "creating or updating a shared network for ANY"
                      " server is not supported");

        } else if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        PsqlBindArray in_bindings;
        in_bindings.addTempString(shared_network->getName());
        in_bindings.addOptional(shared_network->getClientClass(Network::Inheritance::NONE));
        in_bindings.addOptional(shared_network->getIface(Network::Inheritance::NONE));
        in_bindings.addTimestamp(shared_network->getModificationTime());
        in_bindings.add(shared_network->getPreferred(Network::Inheritance::NONE));
        in_bindings.addMin(shared_network->getPreferred(Network::Inheritance::NONE));
        in_bindings.addMax(shared_network->getPreferred(Network::Inheritance::NONE));
        in_bindings.addOptional(shared_network->getRapidCommit(Network::Inheritance::NONE));
        in_bindings.add(shared_network->getT2(Network::Inheritance::NONE));
        addRelayBinding(in_bindings, shared_network);
        in_bindings.add(shared_network->getT1(Network::Inheritance::NONE));
        addRequiredClassesBinding(in_bindings, shared_network);
        in_bindings.addOptional(shared_network->getReservationsGlobal(Network::Inheritance::NONE));
        in_bindings.add(shared_network->getContext());
        in_bindings.add(shared_network->getValid(Network::Inheritance::NONE));
        in_bindings.addMin(shared_network->getValid(Network::Inheritance::NONE));
        in_bindings.addMax(shared_network->getValid(Network::Inheritance::NONE));
        in_bindings.addOptional(shared_network->getCalculateTeeTimes(Network::Inheritance::NONE));
        in_bindings.addOptional(shared_network->getT1Percent(Network::Inheritance::NONE));
        in_bindings.addOptional(shared_network->getT2Percent(Network::Inheritance::NONE));
        addInterfaceIdBinding(in_bindings, *shared_network);
        in_bindings.addOptional(shared_network->getDdnsSendUpdates(Network::Inheritance::NONE));
        in_bindings.addOptional(shared_network->getDdnsOverrideNoUpdate(Network::Inheritance::NONE));
        in_bindings.addOptional(shared_network->getDdnsOverrideClientUpdate(Network::Inheritance::NONE));
        addDdnsReplaceClientNameBinding(in_bindings, shared_network);
        in_bindings.addOptional(shared_network->getDdnsGeneratedPrefix(Network::Inheritance::NONE));
        in_bindings.addOptional(shared_network->getDdnsQualifyingSuffix(Network::Inheritance::NONE));
        in_bindings.addOptional(shared_network->getReservationsInSubnet(Network::Inheritance::NONE));
        in_bindings.addOptional(shared_network->getReservationsOutOfPool(Network::Inheritance::NONE));
        in_bindings.addOptional(shared_network->getCacheThreshold(Network::Inheritance::NONE));
        in_bindings.addOptional(shared_network->getCacheMaxAge(Network::Inheritance::NONE));

        // Start transaction.
        PgSqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           server_selector, "shared network set", true);

        // Create a savepoint in case we are called as part of larger
        // transaction.
        conn_.createSavepoint("createUpdateSharedNetwork6");

        try {

            // Try to insert shared network. The shared network name must be unique,
            // so if inserting fails with DuplicateEntry exception we'll need to
            // update existing shared network entry.
            insertQuery(PgSqlConfigBackendDHCPv6Impl::INSERT_SHARED_NETWORK6,
                        in_bindings);

        } catch (const DuplicateEntry&) {
            // It already exists, rollback to the savepoint to preserve
            // any prior work.
            conn_.rollbackToSavepoint("createUpdateSharedNetwork6");

            // We're updating, so we need to remove any options.
            deleteOptions6(ServerSelector::ANY(), shared_network);

            // Need to add one more binding for WHERE clause.
            in_bindings.addTempString(shared_network->getName());

            // Try the update.
            updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::UPDATE_SHARED_NETWORK6,
                              in_bindings);

            // Remove existing server association.
            PsqlBindArray server_bindings;
            server_bindings.addTempString(shared_network->getName());
            updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_SERVER,
                              server_bindings);
        }

        // Associate the shared network with the servers.
        PsqlBindArray attach_bindings;
        attach_bindings.addTempString(shared_network->getName());
        attach_bindings.addTimestamp(shared_network->getModificationTime());
        attachElementToServers(PgSqlConfigBackendDHCPv6Impl::INSERT_SHARED_NETWORK6_SERVER,
                               server_selector, attach_bindings);

        // (Re)create options.
        auto option_spaces = shared_network->getCfgOption()->getOptionSpaceNames();
        for (auto option_space : option_spaces) {
            OptionContainerPtr options = shared_network->getCfgOption()->getAll(option_space);
            for (auto desc = options->begin(); desc != options->end(); ++desc) {
                OptionDescriptorPtr desc_copy = OptionDescriptor::create(*desc);
                desc_copy->space_name_ = option_space;
                createUpdateOption6(server_selector, shared_network->getName(),
                                    desc_copy, true);
            }
        }

        // Commit the work.
        transaction.commit();
    }

    /// @brief Sends query to insert DHCP option.
    ///
    /// This method expects that the server selector contains exactly one
    /// server tag.  It is intended to be used within a transaction.
    ///
    /// @param server_selector Server selector.
    /// @param in_bindings Collection of bindings representing an option.
    /// @param modification_ts option's modification timestamp
    void insertOption6(const ServerSelector& server_selector,
                       const PsqlBindArray& in_bindings,
                       const boost::posix_time::ptime& modification_ts) {
        // Attempt the insert.
        insertQuery(PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION6, in_bindings);

        // Fetch primary key value of the inserted option. We will use it in the
        // next INSERT statement to associate this option with the server.
        auto option_id = getLastInsertId("dhcp6_options", "option_id");

        PsqlBindArray attach_bindings;
        attach_bindings.add(option_id);   // id of newly inserted global.
        attach_bindings.addTimestamp(modification_ts);

        // Associate the option with the servers.
        attachElementToServers(PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION6_SERVER,
                               server_selector, attach_bindings);
    }

    /// @brief Sends query to insert or update global DHCP option.
    ///
    /// @param server_selector Server selector.
    /// @param option Pointer to the option descriptor encapsulating the option.
    void createUpdateOption6(const ServerSelector& server_selector,
                             const OptionDescriptorPtr& option) {
        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        auto tag = getServerTag(server_selector, "creating or updating global option");

        // Create the input parameter bindings.
        PsqlBindArray in_bindings;
        in_bindings.add(option->option_->getType());
        addOptionValueBinding(in_bindings, option);
        in_bindings.addOptional(option->formatted_value_);
        in_bindings.addOptional(option->space_name_);
        in_bindings.add(option->persistent_);
        in_bindings.addNull();
        in_bindings.addNull();
        in_bindings.add(0);
        in_bindings.add(option->getContext());
        in_bindings.addNull();
        in_bindings.addNull();
        in_bindings.addTimestamp(option->getModificationTime());
        in_bindings.addNull();

        // Remember the size before we add where clause arguments.
        size_t pre_where_size = in_bindings.size();

        // Now we add the update where clause parameters
        in_bindings.add(tag);
        in_bindings.add(option->option_->getType());
        in_bindings.addOptional(option->space_name_);

        // Start transaction.
        PgSqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           server_selector, "global option set", false);

        // Try to update the option.
        if (updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6,
                              in_bindings) == 0) {
            // The option doesn't exist, so we'll try to insert it.
            // Remove the update where clause bindings.
            while (in_bindings.size() > pre_where_size) {
                in_bindings.popBack();
            }

            // Try to insert the option.
            insertOption6(server_selector, in_bindings,
                          option->getModificationTime());
        }

        // Commit the work.
        transaction.commit();
    }

    /// @brief Sends query to insert or update DHCP option in a subnet.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of the subnet the option belongs to.
    /// @param option Pointer to the option descriptor encapsulating the option.
    /// @param cascade_update Boolean value indicating whether the update is
    /// performed as part of the owning element, e.g. subnet.
    void createUpdateOption6(const ServerSelector& server_selector,
                             const SubnetID& subnet_id,
                             const OptionDescriptorPtr& option,
                             const bool cascade_update) {
        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        // Create input bindings.
        PsqlBindArray in_bindings;
        in_bindings.add(option->option_->getType());
        addOptionValueBinding(in_bindings, option);
        in_bindings.addOptional(option->formatted_value_);
        in_bindings.addOptional(option->space_name_);
        in_bindings.add(option->persistent_);
        in_bindings.addNull();
        in_bindings.add(subnet_id);
        in_bindings.add(1);
        in_bindings.add(option->getContext());
        in_bindings.addNull();
        in_bindings.addNull();
        in_bindings.addTimestamp(option->getModificationTime());
        in_bindings.addNull();

        // Remember the size before we add where clause arguments.
        size_t pre_where_size = in_bindings.size();

        // Now we add the update where clause parameters
        in_bindings.add(subnet_id);
        in_bindings.add(option->option_->getType());
        in_bindings.addOptional(option->space_name_);

        // Start transaction.
        PgSqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           server_selector, "subnet specific option set",
                           cascade_update);

        // Try to update the subnet option.
        if (updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_SUBNET_ID,
                              in_bindings) == 0) {
            // The option doesn't exist, so we'll try to insert it.
            // Remove the update where clause bindings.
            while (in_bindings.size() > pre_where_size) {
                in_bindings.popBack();
            }

            // Try to insert the option.
            insertOption6(server_selector, in_bindings,
                          option->getModificationTime());
        }

        // Commit the work.
        transaction.commit();
    }

    /// @brief Sends query to insert or update DHCP option in a pool.
    ///
    /// @param server_selector Server selector.
    /// @param pool_start_address Lower bound address of the pool.
    /// @param pool_end_address Upper bound address of the pool.
    /// @param option Pointer to the option descriptor encapsulating the option.
    void createUpdateOption6(const ServerSelector& server_selector,
                             const IOAddress& pool_start_address,
                             const IOAddress& pool_end_address,
                             const OptionDescriptorPtr& option) {
        uint64_t pool_id = 0;
        Pool6Ptr pool = getPool6(server_selector, pool_start_address, pool_end_address,
                                 pool_id);
        if (!pool) {
            isc_throw(BadValue, "no pool found for range of "
                      << pool_start_address << " : "
                      << pool_end_address);
        }

        createUpdateOption6(server_selector, Lease::TYPE_NA,
                            pool_id, option, false);
    }

    /// @brief Sends query to insert or update DHCP option in a pd pool.
    ///
    /// @param server_selector Server selector.
    /// @param pd_pool_prefix Address part of the pd pool prefix.
    /// @param pd_pool_prefix_length Length of the pd pool prefix.
    /// @param option Pointer to the option descriptor encapsulating the option.
    void createUpdateOption6(const ServerSelector& server_selector,
                             const asiolink::IOAddress& pd_pool_prefix,
                             const uint8_t pd_pool_prefix_length,
                             const OptionDescriptorPtr& option) {
        uint64_t pd_pool_id = 0;
        Pool6Ptr pd_pool = getPdPool6(server_selector,
                                      pd_pool_prefix,
                                      pd_pool_prefix_length,
                                      pd_pool_id);
        if (!pd_pool) {
            isc_throw(BadValue, "no prefix delegation pool found for prefix "
                      << "of " << pd_pool_prefix << "/"
                      << static_cast<unsigned>(pd_pool_prefix_length));
        }

        createUpdateOption6(server_selector, Lease::TYPE_PD,
                            pd_pool_id, option, false);
    }

    /// @brief Sends query to insert or update DHCP option in an address
    /// or prefix delegation pool.
    ///
    /// @param selector Server selector.
    /// @param pool_type Pool type (Lease::TYPE_NA or Lease::TYPE_PD).
    /// @param pool_id Identifier of the address or prefix delegation pool
    /// the option belongs to.
    /// @param option Pointer to the option descriptor encapsulating the option.
    /// @param cascade_update Boolean value indicating whether the update is
    /// performed as part of the owning element, e.g. subnet.
    void createUpdateOption6(const ServerSelector& server_selector,
                             const Lease::Type& pool_type,
                             const uint64_t pool_id,
                             const OptionDescriptorPtr& option,
                             const bool cascade_update) {
        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        std::string msg = "creating or updating ";
        if (pool_type == Lease::TYPE_PD) {
            msg += "prefix delegation";
        } else {
            msg += "address";
        }
        msg += " pool level option";

        PsqlBindArray in_bindings;

        in_bindings.add(option->option_->getType());
        addOptionValueBinding(in_bindings, option);
        in_bindings.addOptional(option->formatted_value_);
        in_bindings.addOptional(option->space_name_);
        in_bindings.add(option->persistent_);
        in_bindings.addNull();
        in_bindings.addNull();

        // scope_id
        if (pool_type == Lease::TYPE_NA) {
            in_bindings.add(5);
        } else {
            in_bindings.add(6);
        }

        in_bindings.add(option->getContext());
        in_bindings.addNull();

        // pool_id
        if (pool_type == Lease::TYPE_NA) {
            in_bindings.add(pool_id);
        } else {
            in_bindings.addNull();
        }

        in_bindings.addTimestamp(option->getModificationTime());

        // pd_pool_id
        if (pool_type == Lease::TYPE_PD) {
            in_bindings.add(pool_id);
        } else {
            in_bindings.addNull();
        }

        // Remember the size before we add where clause arguments.
        size_t pre_where_size = in_bindings.size();

        // Now we add the update where clause parameters
        in_bindings.add(pool_id);
        in_bindings.add(option->option_->getType());
        in_bindings.addOptional(option->space_name_);

        // Start transaction.
        PgSqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        if (pool_type == Lease::TYPE_PD) {
            msg = "prefix delegation";
        } else {
            msg = "address";
        }
        msg += " pool specific option set";
        ScopedAuditRevision
            audit_revision(this,
                           PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           server_selector, msg, cascade_update);

        auto index = (pool_type == Lease::TYPE_NA ?
                      PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_POOL_ID :
                      PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_PD_POOL_ID);

        // Try to update the option.
        if (updateDeleteQuery(index, in_bindings) == 0) {
            // The option doesn't exist, so we'll try to insert it.
            // Remove the update where clause bindings.
            while (in_bindings.size() > pre_where_size) {
                in_bindings.popBack();
            }

            // Try to insert the option.
            insertOption6(server_selector, in_bindings,
                          option->getModificationTime());
        }

        // Commit the work.
        transaction.commit();
    }

    /// @brief Sends query to insert or update DHCP option in a shared network.
    ///
    /// @param selector Server selector.
    /// @param shared_network_name Name of the shared network the option
    /// belongs to.
    /// @param option Pointer to the option descriptor encapsulating the option.
    /// @param cascade_update Boolean value indicating whether the update is
    /// performed as part of the owning element, e.g. shared network.
    void createUpdateOption6(const ServerSelector& server_selector,
                             const std::string& shared_network_name,
                             const OptionDescriptorPtr& option,
                             const bool cascade_update) {
        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        // Create input bindings.
        PsqlBindArray in_bindings;
        in_bindings.add(option->option_->getType());
        addOptionValueBinding(in_bindings, option);
        in_bindings.addOptional(option->formatted_value_);
        in_bindings.addOptional(option->space_name_);
        in_bindings.add(option->persistent_);
        in_bindings.addNull();
        in_bindings.addNull();
        in_bindings.add(4);
        in_bindings.add(option->getContext());
        in_bindings.add(shared_network_name);
        in_bindings.addNull();
        in_bindings.addTimestamp(option->getModificationTime());
        in_bindings.addNull();

        // Remember the size before we add where clause arguments.
        size_t pre_where_size = in_bindings.size();

        // Now we add the update where clause parameters
        in_bindings.add(shared_network_name);
        in_bindings.add(option->option_->getType());
        in_bindings.addOptional(option->space_name_);

        // Start transaction.
        PgSqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           server_selector, "shared network specific option set",
                           cascade_update);

        // Try to update the option.
        if (updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_SHARED_NETWORK,
                              in_bindings) == 0) {
            // The option doesn't exist, so we'll try to insert it.
            // Remove the update where clause bindings.
            while (in_bindings.size() > pre_where_size) {
                in_bindings.popBack();
            }

            // Try to insert the option.
            insertOption6(server_selector, in_bindings,
                          option->getModificationTime());
        }

        // Commit the work.
        transaction.commit();
    }

    /// @brief Sends query to insert or update DHCP option in a client class.
    ///
    /// @param selector Server selector.
    /// @param client_class Pointer to the client_class the option belongs to.
    /// @param option Pointer to the option descriptor encapsulating the option..
    void createUpdateOption6(const ServerSelector& server_selector,
                             const ClientClassDefPtr& client_class,
                             const OptionDescriptorPtr& option) {
        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        PsqlBindArray in_bindings;
        std::string class_name = client_class->getName();
        in_bindings.add(option->option_->getType());
        addOptionValueBinding(in_bindings, option);
        in_bindings.addOptional(option->formatted_value_);
        in_bindings.addOptional(option->space_name_);
        in_bindings.add(option->persistent_);
        in_bindings.add(class_name);
        in_bindings.addNull();
        in_bindings.add(2);
        in_bindings.add(option->getContext());
        in_bindings.addNull();
        in_bindings.addNull();
        in_bindings.addTimestamp(option->getModificationTime());
        in_bindings.addNull();

        // Remember the size before we add where clause arguments.
        size_t pre_where_size = in_bindings.size();

        // Now we add the update where clause parameters
        in_bindings.add(class_name);
        in_bindings.add(option->option_->getType());
        in_bindings.addOptional(option->space_name_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           server_selector, "client class specific option set",
                           true);

        if (updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_CLIENT_CLASS,
                              in_bindings) == 0) {
            // The option doesn't exist, so we'll try to insert it.
            // Remove the update where clause bindings.
            while (in_bindings.size() > pre_where_size) {
                in_bindings.popBack();
            }

            insertOption6(server_selector, in_bindings,
                          option->getModificationTime());
        }
    }

    /// @brief Sends query to insert or update option definition.
    ///
    /// @param server_selector Server selector.
    /// @param option_def Pointer to the option definition to be inserted or updated.
    void createUpdateOptionDef6(const ServerSelector& server_selector,
                                const OptionDefinitionPtr& option_def) {
        createUpdateOptionDef(server_selector, Option::V6, option_def, DHCP6_OPTION_SPACE,
                              PgSqlConfigBackendDHCPv6Impl::GET_OPTION_DEF6_CODE_SPACE,
                              PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6,
                              PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION_DEF6,
                              PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                              PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6_SERVER);
    }

    /// @brief Sends query to insert or update option definition
    /// for a client class.
    ///
    /// @param server_selector Server selector.
    /// @param option_def Pointer to the option definition to be inserted or updated.
    /// @param client_class Client class name.
    void createUpdateOptionDef6(const ServerSelector& server_selector,
                                const OptionDefinitionPtr& option_def,
                                const std::string& client_class_name) {
        createUpdateOptionDef(server_selector, Option::V6, option_def, DHCP6_OPTION_SPACE,
                              PgSqlConfigBackendDHCPv6Impl::GET_OPTION_DEF6_CODE_SPACE,
                              PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6_CLIENT_CLASS,
                              PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION_DEF6_CLIENT_CLASS,
                              PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                              PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6_SERVER,
                              client_class_name);
    }

    /// @brief Sends query to delete option definition by code and
    /// option space name.
    ///
    /// @param server_selector Server selector.
    /// @param code Option code.
    /// @param name Option name.
    /// @return Number of deleted option definitions.
    uint64_t deleteOptionDef6(const ServerSelector& server_selector,
                              const uint16_t code,
                              const std::string& space) {
        PsqlBindArray in_bindings;
        in_bindings.add(code);
        in_bindings.add(space);

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION_DEF6_CODE_NAME,
                                    server_selector,
                                    "deleting option definition",
                                    "option definition deleted",
                                    false,
                                    in_bindings));
    }

    /// @brief Sends query to delete option definitions for a client class.
    ///
    /// @param server_selector Server selector.
    /// @param client_class Pointer to the client class for which option
    /// definitions should be deleted.
    /// @return Number of deleted option definitions.
    uint64_t deleteOptionDefs6(const ServerSelector& server_selector,
                               const ClientClassDefPtr& client_class) {
        PsqlBindArray in_bindings;
        in_bindings.addTempString(client_class->getName());

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION_DEFS6_CLIENT_CLASS,
                                    server_selector,
                                    "deleting option definition for a client class",
                                    "option definition deleted",
                                    true,
                                    in_bindings));
    }

    /// @brief Deletes global option.
    ///
    /// @param server_selector Server selector.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    uint64_t deleteOption6(const ServerSelector& server_selector,
                           const uint16_t code,
                           const std::string& space) {
        PsqlBindArray in_bindings;
        in_bindings.add(code);
        in_bindings.add(space);

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION6,
                                    server_selector,
                                    "deleting global option",
                                    "global option deleted",
                                    false,
                                    in_bindings));
    }

    /// @brief Deletes subnet level option.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of the subnet to which deleted option
    /// belongs.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    uint64_t deleteOption6(const ServerSelector& server_selector,
                           const SubnetID& subnet_id,
                           const uint16_t code,
                           const std::string& space) {
        PsqlBindArray in_bindings;
        in_bindings.add(subnet_id);
        in_bindings.add(code);
        in_bindings.add(space);

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION6_SUBNET_ID,
                                    server_selector,
                                    "deleting option for a subnet",
                                    "subnet specific option deleted",
                                    false,
                                    in_bindings));
    }

    /// @brief Deletes pool level option.
    ///
    /// @param server_selector Server selector.
    /// @param pool_start_address Lower bound pool address.
    /// @param pool_end_address  Upper bound pool address.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    uint64_t deleteOption6(const db::ServerSelector& server_selector,
                           const IOAddress& pool_start_address,
                           const IOAddress& pool_end_address,
                           const uint16_t code,
                           const std::string& space) {
        PsqlBindArray in_bindings;
        in_bindings.addInet6(pool_start_address);
        in_bindings.addInet6(pool_end_address);
        in_bindings.add(code);
        in_bindings.add(space);

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION6_POOL_RANGE,
                                    server_selector,
                                    "deleting option for an address pool",
                                    "address pool specific option deleted",
                                    false,
                                    in_bindings));
    }

    /// @brief Deletes pd pool level option.
    ///
    /// @param server_selector Server selector.
    /// @param pd_pool_prefix Address part of the pd pool prefix.
    /// @param pd_pool_prefix_length Length of the pd pool prefix.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    uint64_t deleteOption6(const db::ServerSelector& server_selector,
                           const asiolink::IOAddress& pd_pool_prefix,
                           const uint8_t pd_pool_prefix_length,
                           const uint16_t code,
                           const std::string& space) {
        PsqlBindArray in_bindings;
        in_bindings.addTempString(pd_pool_prefix.toText());
        in_bindings.add(pd_pool_prefix_length);
        in_bindings.add(code);
        in_bindings.add(space);

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION6_PD_POOL,
                                    server_selector,
                                    "deleting option for a prefix delegation pool",
                                    "prefix delegation pool specific option deleted",
                                    false,
                                    in_bindings));
    }

    /// @brief Deletes shared network level option.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of the shared network which deleted
    /// option belongs to
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    uint64_t deleteOption6(const db::ServerSelector& server_selector,
                           const std::string& shared_network_name,
                           const uint16_t code,
                           const std::string& space) {
        PsqlBindArray in_bindings;
        in_bindings.add(shared_network_name);
        in_bindings.add(code);
        in_bindings.add(space);

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION6_SHARED_NETWORK,
                                    server_selector,
                                    "deleting option for a shared network",
                                    "shared network specific option deleted",
                                    false,
                                    in_bindings));
    }

    /// @brief Deletes options belonging to a subnet from the database.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Pointer to the subnet for which options should be
    /// deleted.
    /// @return Number of deleted options.
    uint64_t deleteOptions6(const ServerSelector& server_selector,
                            const Subnet6Ptr& subnet) {
        PsqlBindArray in_bindings;
        in_bindings.add(subnet->getID());
        in_bindings.addTempString(subnet->toText());

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_OPTIONS6_SUBNET_ID_PREFIX,
                                    server_selector,
                                    "deleting options for a subnet",
                                    "subnet specific options deleted",
                                    true, in_bindings));
    }

    /// @brief Deletes options belonging to a shared network from the database.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Pointer to the subnet for which options should be
    /// deleted.
    /// @return Number of deleted options.
    uint64_t deleteOptions6(const ServerSelector& server_selector,
                            const SharedNetwork6Ptr& shared_network) {
        PsqlBindArray in_bindings;
        in_bindings.addTempString(shared_network->getName());

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv6Impl::
                                    DELETE_OPTIONS6_SHARED_NETWORK, server_selector,
                                    "deleting options for a shared network",
                                    "shared network specific options deleted",
                                    true, in_bindings));
    }

    /// @brief Deletes options belonging to a client class from the database.
    ///
    /// @param server_selector Server selector.
    /// @param client_class Pointer to the client class for which options
    /// should be deleted.
    /// @return Number of deleted options.
    uint64_t deleteOptions6(const ServerSelector& server_selector,
                            const ClientClassDefPtr& client_class) {
        PsqlBindArray in_bindings;
        in_bindings.addTempString(client_class->getName());

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv6Impl::
                                    DELETE_OPTIONS6_CLIENT_CLASS, server_selector,
                                    "deleting options for a client class",
                                    "client class specific options deleted",
                                    true, in_bindings));
    }

    /// @brief Common function to retrieve client classes.
    ///
    /// @param index Index of the query to be used.
    /// @param server_selector Server selector.
    /// @param in_bindings Input bindings specifying selection criteria. The
    /// size of the bindings collection must match the number of placeholders
    /// in the prepared statement. The input bindings collection must be empty
    /// if the query contains no WHERE clause.
    /// @param [out] client_classes Reference to a container where fetched client
    /// classes will be inserted.
    void getClientClasses6(const StatementIndex& index,
                           const ServerSelector& server_selector,
                           const PsqlBindArray& in_bindings,
                           ClientClassDictionary& client_classes) {
        std::list<ClientClassDefPtr> class_list;
        uint64_t last_option_id = 0;
        uint64_t last_option_def_id = 0;
        std::string last_tag;

        selectQuery(index, in_bindings,
                    [this, &class_list, &last_option_id, &last_option_def_id, &last_tag]
                    (PgSqlResult& r, int row) {
            // Create a convenience worker for the row.
            PgSqlResultRowWorker worker(r, row);

            ClientClassDefPtr last_client_class;
            if (!class_list.empty()) {
                last_client_class = *class_list.rbegin();
            }

            // Class ID is column 0.
            uint64_t id = worker.getBigInt(0) ;

            if (!last_client_class || (last_client_class->getId() != id)) {
                last_option_id = 0;
                last_option_def_id = 0;
                last_tag.clear();

                auto options = boost::make_shared<CfgOption>();
                auto option_defs = boost::make_shared<CfgOptionDef>();

                last_client_class = boost::make_shared<ClientClassDef>(worker.getString(1),
                                                                       ExpressionPtr(), options);
                last_client_class->setCfgOptionDef(option_defs);

                // id
                last_client_class->setId(id);

                // name
                last_client_class->setName(worker.getString(1));

                // test
                if (!worker.isColumnNull(2)) {
                    last_client_class->setTest(worker.getString(2));
                }

                // required
                if (!worker.isColumnNull(3)) {
                    last_client_class->setRequired(worker.getBool(3));
                }

                // valid lifetime: default, min, max
                last_client_class->setValid(worker.getTriplet(4, 5, 6));

                // depend on known directly or indirectly
                last_client_class->setDependOnKnown(worker.getBool(7) || worker.getBool(8));

                // modification_ts
                last_client_class->setModificationTime(worker.getTimestamp(9));

                // user_context at 10.
                if (!worker.isColumnNull(10)) {
                    ElementPtr user_context = worker.getJSON(10);
                    if (user_context) {
                        last_client_class->setContext(user_context);
                    }
                }

                // class specific option definition from 11 to 20.
                // class specific option from 21 to 32.

                // preferred lifetime: default, min, max
                last_client_class->setPreferred(worker.getTriplet(34, 35, 36));

                class_list.push_back(last_client_class);
            }

            // Check for new server tags at 33.
            if (!worker.isColumnNull(33)) {
                std::string new_tag = worker.getString(33);
                if (last_tag != new_tag) {
                    if (!new_tag.empty() && !last_client_class->hasServerTag(ServerTag(new_tag))) {
                        last_client_class->setServerTag(new_tag);
                    }

                    last_tag = new_tag;
                }
            }

            // Parse client class specific option definition from 11 to 20.
            if (!worker.isColumnNull(11) &&
                (last_option_def_id < worker.getBigInt(11))) {
                last_option_def_id = worker.getBigInt(11);

                auto def = processOptionDefRow(worker, 11);
                if (def) {
                    last_client_class->getCfgOptionDef()->add(def);
                }
            }

            // Parse client class specific option from 21 to 32.
            if (!worker.isColumnNull(21) &&
                (last_option_id < worker.getBigInt(21))) {
                last_option_id = worker.getBigInt(21);

                OptionDescriptorPtr desc = processOptionRow(Option::V6, worker, 21);
                if (desc) {
                    last_client_class->getCfgOption()->add(*desc, desc->space_name_);
                }
            }
        });

        tossNonMatchingElements(server_selector, class_list);

        for (auto c : class_list) {
            client_classes.addClass(c);
        }
    }

    /// @brief Sends query to retrieve a client class by name.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the class to be retrieved.
    /// @return Pointer to the client class or null if the class is not found.
    ClientClassDefPtr getClientClass6(const ServerSelector& server_selector,
                                      const std::string& name) {
        PsqlBindArray in_bindings;
        in_bindings.add(name);

        ClientClassDictionary client_classes;
        getClientClasses6(PgSqlConfigBackendDHCPv6Impl::GET_CLIENT_CLASS6_NAME,
                          server_selector, in_bindings, client_classes);
        return (client_classes.getClasses()->empty() ? ClientClassDefPtr() :
                (*client_classes.getClasses()->begin()));
    }

    /// @brief Sends query to retrieve all client classes.
    ///
    /// @param server_selector Server selector.
    /// @param [out] client_classes Reference to the client classes collection
    /// where retrieved classes will be stored.
    void getAllClientClasses6(const ServerSelector& server_selector,
                              ClientClassDictionary& client_classes) {
        PsqlBindArray in_bindings;
        getClientClasses6(server_selector.amUnassigned() ?
                          PgSqlConfigBackendDHCPv6Impl::GET_ALL_CLIENT_CLASSES6_UNASSIGNED :
                          PgSqlConfigBackendDHCPv6Impl::GET_ALL_CLIENT_CLASSES6,
                          server_selector, in_bindings, client_classes);
    }

    /// @brief Sends query to retrieve modified client classes.
    ///
    /// @param server_selector Server selector.
    /// @param modification_ts Lower bound modification timestamp.
    /// @param [out] client_classes Reference to the client classes collection
    /// where retrieved classes will be stored.
    void getModifiedClientClasses6(const ServerSelector& server_selector,
                                   const boost::posix_time::ptime& modification_ts,
                                   ClientClassDictionary& client_classes) {
        if (server_selector.amAny()) {
            isc_throw(InvalidOperation, "fetching modified client classes for ANY "
                      "server is not supported");
        }

        PsqlBindArray in_bindings;
        in_bindings.addTimestamp(modification_ts);
        getClientClasses6(server_selector.amUnassigned() ?
                          PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_CLIENT_CLASSES6_UNASSIGNED :
                          PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_CLIENT_CLASSES6,
                          server_selector, in_bindings, client_classes);
    }

    /// @brief Upserts client class.
    ///
    /// @param server_selector Server selector.
    /// @param client_class Pointer to the upserted client class.
    /// @param follow_class_name name of the class after which the
    /// new or updated class should be positioned. An empty value
    /// causes the class to be appended at the end of the class
    /// hierarchy.
    void createUpdateClientClass6(const ServerSelector& server_selector,
                                  const ClientClassDefPtr& client_class,
                                  const std::string& follow_class_name) {
        // We need to evaluate class expression to see if it references any
        // other classes (dependencies). As part of this evaluation we will
        // also check if the client class depends on KNOWN/UNKNOWN built-in
        // classes.
        std::list<std::string> dependencies;
        auto depend_on_known = false;
        if (!client_class->getTest().empty()) {
            ExpressionPtr expression;
            ExpressionParser parser;
            // Parse the test expression. The callback function is normally used to
            // interrupt config file parsing when one of the classes refers to a
            // non-existing client class. It returns false in this case. Here,
            // we use the callback to capture client classes referenced by the
            // upserted client class and record whether this class depends on
            // KNOWN/UNKNOWN built-ins. The callback always returns true to avoid
            // reporting the parsing error. The dependency check is performed later
            // at the database level.
            parser.parse(expression, Element::create(client_class->getTest()), AF_INET6,
                         [&dependencies, &depend_on_known](const ClientClass& client_class) -> bool {
                if (isClientClassBuiltIn(client_class)) {
                    if ((client_class == "KNOWN") || (client_class == "UNKNOWN")) {
                        depend_on_known = true;
                    }
                } else {
                    dependencies.push_back(client_class);
                }
                return (true);
            });
        }

        PsqlBindArray in_bindings;
        std::string class_name = client_class->getName();
        in_bindings.add(class_name);
        in_bindings.addTempString(client_class->getTest());
        in_bindings.add(client_class->getRequired());
        in_bindings.add(client_class->getValid());
        in_bindings.add(client_class->getValid().getMin());
        in_bindings.add(client_class->getValid().getMax());
        in_bindings.add(depend_on_known);

        // follow-class-name (8)
        if (follow_class_name.empty()) {
            in_bindings.addNull();
        } else {
            in_bindings.add(follow_class_name);
        }

        in_bindings.add(client_class->getPreferred());
        in_bindings.add(client_class->getPreferred().getMin());
        in_bindings.add(client_class->getPreferred().getMax());
        in_bindings.addTimestamp(client_class->getModificationTime());
        in_bindings.add(client_class->getContext());

        PgSqlTransaction transaction(conn_);

        ScopedAuditRevision audit_revision(this, PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                                           server_selector, "client class set", true);

        // Create a savepoint in case we are called as part of larger
        // transaction.
        conn_.createSavepoint("createUpdateClass6");

        // Keeps track of whether the client class is inserted or updated.
        auto update = false;
        try {
            insertQuery(PgSqlConfigBackendDHCPv6Impl::INSERT_CLIENT_CLASS6, in_bindings);

        } catch (const DuplicateEntry&) {
            // It already exists, rollback to the savepoint to preserve
            // any prior work.
            conn_.rollbackToSavepoint("createUpdateClass6");

            // Delete options and option definitions. They will be re-created from the new class
            // instance.
            deleteOptions6(ServerSelector::ANY(), client_class);
            deleteOptionDefs6(ServerSelector::ANY(), client_class);

            // Note: follow_class_name is left in the bindings even though it is
            // not needed in both cases. This allows us to use one base query.

            // Add the class name for the where clause.
            in_bindings.add(class_name);
            if (follow_class_name.empty()) {
                // If position is not specified, leave the class at the same position.
                updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::UPDATE_CLIENT_CLASS6_SAME_POSITION,
                                  in_bindings);
            } else {
                // Update with follow_class_name specifying the position.
                updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::UPDATE_CLIENT_CLASS6,
                                  in_bindings);
            }

            // Delete class associations with the servers and dependencies. We will re-create
            // them according to the new class specification.
            PsqlBindArray in_assoc_bindings;
            in_assoc_bindings.add(class_name);
            updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6_DEPENDENCY,
                              in_assoc_bindings);
            updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6_SERVER,
                              in_assoc_bindings);
            update = true;
        }

        // Associate client class with the servers.
        PsqlBindArray attach_bindings;
        attach_bindings.add(class_name);
        attach_bindings.addTimestamp(client_class->getModificationTime());

        attachElementToServers(PgSqlConfigBackendDHCPv6Impl::INSERT_CLIENT_CLASS6_SERVER,
                               server_selector, attach_bindings);

        // Iterate over the captured dependencies and try to insert them into the database.
        for (auto dependency : dependencies) {
            try {
                PsqlBindArray in_dependency_bindings;
                in_dependency_bindings.add(class_name);
                in_dependency_bindings.add(dependency);

                // We deleted earlier dependencies, so we can simply insert new ones.
                insertQuery(PgSqlConfigBackendDHCPv6Impl::INSERT_CLIENT_CLASS6_DEPENDENCY,
                            in_dependency_bindings);
            } catch (const std::exception& ex) {
                isc_throw(InvalidOperation, "unmet dependency on client class: " << dependency);
            }
        }

        // If we performed client class update we also have to verify that its dependency
        // on KNOWN/UNKNOWN client classes hasn't changed.
        if (update) {
            PsqlBindArray in_check_bindings;
            insertQuery(PgSqlConfigBackendDHCPv6Impl::CHECK_CLIENT_CLASS_KNOWN_DEPENDENCY_CHANGE,
                              in_check_bindings);
        }

        // (Re)create option definitions.
        if (client_class->getCfgOptionDef()) {
            auto option_defs = client_class->getCfgOptionDef()->getContainer();
            auto option_spaces = option_defs.getOptionSpaceNames();
            for (auto option_space : option_spaces) {
                OptionDefContainerPtr defs = option_defs.getItems(option_space);
                for (auto def = defs->begin(); def != defs->end(); ++def) {
                    createUpdateOptionDef6(server_selector, *def, client_class->getName());
                }
            }
        }

        // (Re)create options.
        auto option_spaces = client_class->getCfgOption()->getOptionSpaceNames();
        for (auto option_space : option_spaces) {
            OptionContainerPtr options = client_class->getCfgOption()->getAll(option_space);
            for (auto desc = options->begin(); desc != options->end(); ++desc) {
                OptionDescriptorPtr desc_copy = OptionDescriptor::create(*desc);
                desc_copy->space_name_ = option_space;
                createUpdateOption6(server_selector, client_class, desc_copy);
            }
        }

        // All ok. Commit the transaction.
        transaction.commit();
    }

    /// @brief Removes client class by name.
    ///
    /// @param server_selector Server selector.
    /// @param name Removed client class name.
    /// @return Number of deleted client classes.
    uint64_t deleteClientClass6(const ServerSelector& server_selector,
                                const std::string& name) {
        int index = server_selector.amAny() ?
            PgSqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6_ANY :
            PgSqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6;

        uint64_t result = deleteTransactional(index, server_selector,
                                              "deleting client class",
                                              "client class deleted",
                                              true,
                                              name);
        return (result);
    }

    /// @brief Removes unassigned global parameters, global options and
    /// option definitions.
    ///
    /// This function is called when one or more servers are deleted and
    /// it is likely that there are some orphaned configuration elements
    /// left in the database. This method removes those elements.
    void purgeUnassignedConfig() {
        multipleUpdateDeleteQueries(DELETE_ALL_GLOBAL_PARAMETERS6_UNASSIGNED,
                                    DELETE_ALL_GLOBAL_OPTIONS6_UNASSIGNED,
                                    DELETE_ALL_OPTION_DEFS6_UNASSIGNED);
    }

    /// @brief Attempts to delete a server having a given tag.
    ///
    /// @param server_tag Tag of the server to be deleted.
    /// @return Number of deleted servers.
    /// @throw isc::InvalidOperation when trying to delete the logical
    /// server 'all'.
    uint64_t deleteServer6(const data::ServerTag& server_tag) {
        // It is not allowed to delete 'all' logical server.
        if (server_tag.amAll()) {
            isc_throw(InvalidOperation, "'all' is a name reserved for the server tag which"
                      " associates the configuration elements with all servers connecting"
                      " to the database and may not be deleted");
        }

        PgSqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this, PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           ServerSelector::ALL(), "deleting a server", false);

        // Specify which server should be deleted.
        PsqlBindArray in_bindings;
        in_bindings.addTempString(server_tag.get());

        // Attempt to delete the server.
        auto count = updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::DELETE_SERVER6,
                                       in_bindings);

        // If we have deleted any servers we have to remove any dangling global
        // parameters, options and option definitions.
        if (count > 0) {
            purgeUnassignedConfig();
        }

        transaction.commit();

        return (count);
    }

    /// @brief Attempts to delete all servers.
    ///
    /// This method deletes all servers added by the user. It does not
    /// delete the logical server 'all'.
    ///
    /// @return Number of deleted servers.
    uint64_t deleteAllServers6() {
        // Start transaction.
        PgSqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this, PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           ServerSelector::ALL(), "deleting all servers",
                           false);

        // No arguments, hence empty input bindings.
        PsqlBindArray in_bindings;

        // Attempt to delete the servers.
        auto count = updateDeleteQuery(PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SERVERS6,
                                       in_bindings);

        // If we have deleted any servers we have to remove any dangling global
        // parameters, options and option definitions.
        if (count > 0) {
            purgeUnassignedConfig();
        }

        // Commit the transaction.
        transaction.commit();

        return (count);
    }

    /// @brief Attempts to reconnect the server to the config DB backend manager.
    ///
    /// This is a self-rescheduling function that attempts to reconnect to the
    /// server's config DB backends after connectivity to one or more have been
    /// lost. Upon entry it will attempt to reconnect via
    /// @ref ConfigBackendDHCPv6Mgr.addBackend.
    /// If this is successful, DHCP servicing is re-enabled and server returns
    /// to normal operation.
    ///
    /// If reconnection fails and the maximum number of retries has not been
    /// exhausted, it will schedule a call to itself to occur at the
    /// configured retry interval. DHCP service remains disabled.
    ///
    /// If the maximum number of retries has been exhausted an error is logged
    /// and the server shuts down.
    ///
    /// @param db_reconnect_ctl pointer to the ReconnectCtl containing the
    /// configured reconnect parameters.
    /// @return true if connection has been recovered, false otherwise.
    static bool dbReconnect(ReconnectCtlPtr db_reconnect_ctl) {
        MultiThreadingCriticalSection cs;

        // Invoke application layer connection lost callback.
        if (!DatabaseConnection::invokeDbLostCallback(db_reconnect_ctl)) {
            return (false);
        }

        bool reopened = false;

        const std::string timer_name = db_reconnect_ctl->timerName();

        // At least one connection was lost.
        try {
            auto srv_cfg = CfgMgr::instance().getCurrentCfg();
            auto config_ctl = srv_cfg->getConfigControlInfo();
            // Iterate over the configured DBs and instantiate them.
            for (auto db : config_ctl->getConfigDatabases()) {
                const std::string& access = db.getAccessString();
                auto parameters = db.getParameters();
                if (ConfigBackendDHCPv6Mgr::instance().delBackend(parameters["type"], access, true)) {
                    ConfigBackendDHCPv6Mgr::instance().addBackend(db.getAccessString());
                }
            }

            reopened = true;
        } catch (const std::exception& ex) {
            LOG_ERROR(pgsql_cb_logger, PGSQL_CB_RECONNECT_ATTEMPT_FAILED6)
                    .arg(ex.what());
        }

        if (reopened) {
            // Cancel the timer.
            if (TimerMgr::instance()->isTimerRegistered(timer_name)) {
                TimerMgr::instance()->unregisterTimer(timer_name);
            }

            // Invoke application layer connection recovered callback.
            if (!DatabaseConnection::invokeDbRecoveredCallback(db_reconnect_ctl)) {
                return (false);
            }
        } else {
            if (!db_reconnect_ctl->checkRetries()) {
                // We're out of retries, log it and initiate shutdown.
                LOG_ERROR(pgsql_cb_logger, PGSQL_CB_RECONNECT_FAILED6)
                        .arg(db_reconnect_ctl->maxRetries());

                // Cancel the timer.
                if (TimerMgr::instance()->isTimerRegistered(timer_name)) {
                    TimerMgr::instance()->unregisterTimer(timer_name);
                }

                // Invoke application layer connection failed callback.
                DatabaseConnection::invokeDbFailedCallback(db_reconnect_ctl);

                return (false);
            }

            LOG_INFO(pgsql_cb_logger, PGSQL_CB_RECONNECT_ATTEMPT_SCHEDULE6)
                    .arg(db_reconnect_ctl->maxRetries() - db_reconnect_ctl->retriesLeft() + 1)
                    .arg(db_reconnect_ctl->maxRetries())
                    .arg(db_reconnect_ctl->retryInterval());

            // Start the timer.
            if (!TimerMgr::instance()->isTimerRegistered(timer_name)) {
                TimerMgr::instance()->registerTimer(timer_name,
                    std::bind(&PgSqlConfigBackendDHCPv6Impl::dbReconnect, db_reconnect_ctl),
                              db_reconnect_ctl->retryInterval(),
                              asiolink::IntervalTimer::ONE_SHOT);
            }
            TimerMgr::instance()->setup(timer_name);
        }

        return (true);
    }

    /// @brief Sets a Network6 interface ID from result set col.
    ///
    /// Sets the interface id of the Network6 to the value carried in the
    /// given column in a result set row.
    ///
    /// @param network shared network or subnet to receive the interface ID
    /// @param worker result set row worker contain the database row
    /// @param col column within the row from which to take the value
    void setInterfaceId(Network6& network, PgSqlResultRowWorker& worker, size_t col) {
        if (!worker.isColumnNull(col)) {
            std::vector<uint8_t> iface_id_data;
            worker.getBytes(col, iface_id_data);
            if (!iface_id_data.empty()) {
                OptionPtr opt_iface_id(new Option(Option::V6, D6O_INTERFACE_ID, iface_id_data));
                network.setInterfaceId(opt_iface_id);
            }
        }
    }

    /// @brief Adds network interface ID to a bind array.
    ///
    /// Adds the interface id to end of the given bind array as a vector of bytes.
    ///
    /// @param bindings PsqlBindArray to which the ID should be added.
    /// @param network Pointer to shared network or subnet for which ID binding
    /// should be created.
    void addInterfaceIdBinding(PsqlBindArray& bindings, const Network6& network) {
        auto opt_iface_id = network.getInterfaceId(Network::Inheritance::NONE);
        if (!opt_iface_id) {
            bindings.addNull();
        } else {
            auto iface_id_data = opt_iface_id->getData();
            if (iface_id_data.empty()) {
                bindings.addNull();
            } else {
                bindings.addTempBinary(iface_id_data);
            }
        }
    }

};

namespace {

/// @brief Array of tagged statements.
typedef std::array<PgSqlTaggedStatement, PgSqlConfigBackendDHCPv6Impl::NUM_STATEMENTS>
TaggedStatementArray;

/// @brief Prepared PgSQL statements used by the backend to insert and
/// retrieve data from the database. They must be in the same order as
/// PgSqlConfigBackendDHCPv6Impl::StatementIndex.  The statement is
/// the corresponding enum name.
TaggedStatementArray tagged_statements = { {
    {
        // PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
        4,
        {
            OID_TIMESTAMP,  // 1 audit_ts
            OID_VARCHAR,    // 2 server_tag
            OID_TEXT,       // 3 audit_log_message
            OID_BOOL        // 4 cascade_transaction
        },
        "CREATE_AUDIT_REVISION",
        "select createAuditRevisionDHCP6($1, $2, $3, $4)"
    },

    // Verify that dependency on KNOWN/UNKNOWN class has not changed.
    {
        // PgSqlConfigBackendDHCPv6Impl::CHECK_CLIENT_CLASS_KNOWN_DEPENDENCY_CHANGE,
        0,
        {
            OID_NONE
        },
        "CHECK_CLIENT_CLASS_KNOWN_DEPENDENCY_CHANGE",
        "select checkDHCPv6ClientClassKnownDependencyChange()"
    },

    // Select global parameter by name.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_GLOBAL_PARAMETER6,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_VARCHAR     // 2 name
        },
        "GET_GLOBAL_PARAMETER6",
        PGSQL_GET_GLOBAL_PARAMETER(dhcp6, AND g.name = $2)
    },

    // Select all global parameters.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_ALL_GLOBAL_PARAMETERS6,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "GET_ALL_GLOBAL_PARAMETERS6",
        PGSQL_GET_GLOBAL_PARAMETER(dhcp6)
    },

    // Select modified global parameters.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_GLOBAL_PARAMETERS6,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_TIMESTAMP   // 2 modification_ts
        },
        "GET_MODIFIED_GLOBAL_PARAMETERS6",
        PGSQL_GET_GLOBAL_PARAMETER(dhcp6, AND g.modification_ts >= $2)
    },

    // Select subnet by id.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_SUBNET6_ID_NO_TAG,
        1,
        {
            OID_INT8    // 1 subnet_id
        },
        "GET_SUBNET6_ID_NO_TAG",
        PGSQL_GET_SUBNET6_NO_TAG(WHERE s.subnet_id = $1)
    },

    // Select subnet by id without specifying server tags.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_SUBNET6_ID_ANY,
        1,
        {
            OID_INT8    // 1 subnet_id
        },
        "GET_SUBNET6_ID_ANY",
        PGSQL_GET_SUBNET6_ANY(WHERE s.subnet_id = $1)
    },

    // Select unassigned subnet by id.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_SUBNET6_ID_UNASSIGNED,
        1,
        {
            OID_INT8    // 1 subnet_id
        },
        "GET_SUBNET6_ID_UNASSIGNED",
        PGSQL_GET_SUBNET6_UNASSIGNED(AND s.subnet_id = $1)
    },

    // Select subnet by prefix.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_SUBNET6_PREFIX_NO_TAG,
        1,
        {
            OID_VARCHAR // 1 subnet_prefix
        },
        "GET_SUBNET6_PREFIX_NO_TAG",
        PGSQL_GET_SUBNET6_NO_TAG(WHERE s.subnet_prefix = $1)
    },

    // Select subnet by prefix without specifying server tags.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_SUBNET6_PREFIX_ANY,
        1,
        {
            OID_VARCHAR // 1 subnet_prefix
        },
        "GET_SUBNET6_PREFIX_ANY",
        PGSQL_GET_SUBNET6_ANY(WHERE s.subnet_prefix = $1)
    },

    // Select unassigned subnet by prefix.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_SUBNET6_PREFIX_UNASSIGNED,
        1,
        {
            OID_VARCHAR // 1 subnet_prefix
        },
        "GET_SUBNET6_PREFIX_UNASSIGNED",
        PGSQL_GET_SUBNET6_UNASSIGNED(AND s.subnet_prefix = $1)
    },

    // Select all subnets.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_ALL_SUBNETS6,
        0,
        {
            OID_NONE
        },
        "GET_ALL_SUBNETS6",
        PGSQL_GET_SUBNET6_NO_TAG()
    },

    // Select all unassigned subnets.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_ALL_SUBNETS6_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "GET_ALL_SUBNETS6_UNASSIGNED",
        PGSQL_GET_SUBNET6_UNASSIGNED()
    },

    // Select subnets having modification time later than X.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_SUBNETS6,
        1,
        {
            OID_TIMESTAMP // 1 modification_ts
        },
        "GET_MODIFIED_SUBNETS6",
        PGSQL_GET_SUBNET6_NO_TAG(WHERE s.modification_ts >= $1)
    },

    // Select modified and unassigned subnets.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_SUBNETS6_UNASSIGNED,
        1,
        {
            OID_TIMESTAMP // 1 modification_ts
        },
        "GET_MODIFIED_SUBNETS6_UNASSIGNED",
        PGSQL_GET_SUBNET6_UNASSIGNED(AND s.modification_ts >= $1)
    },

    // Select subnets belonging to a shared network.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_SHARED_NETWORK_SUBNETS6,
        1,
        {
            OID_VARCHAR // 1 share_network_name
        },
        "GET_SHARED_NETWORK_SUBNETS6",
        PGSQL_GET_SUBNET6_ANY(WHERE s.shared_network_name = $1)
    },

    // Select pool by address range for a server.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_POOL6_RANGE,
        3,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_TEXT,       // 2 start_address - cast as inet
            OID_TEXT        // 3 end_address - cast as inet
        },
        "GET_POOL6_RANGE",
        PGSQL_GET_POOL6_RANGE_WITH_TAG(WHERE (srv.tag = $1 OR srv.id = 1) \
                                       AND (p.start_address = cast($2 as inet)) \
                                       AND (p.end_address = cast($3 as inet)))
    },

    // Select pool by address range for any server.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_POOL6_RANGE_ANY,
        2,
        {
            OID_TEXT,       // 1 start_address - cast as inet
            OID_TEXT        // 2 end_address - cast as inet
        },
        "GET_POOL6_RANGE_ANY",
        PGSQL_GET_POOL6_RANGE_NO_TAG(WHERE (p.start_address = cast($1 as inet)) AND \
                                           (p.end_address = cast($2 as inet)))
    },

    // Select prefix delegation pool for a server.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_PD_POOL,
        3,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_VARCHAR,    // 2 pd pool prefix
            OID_INT2        // 3 prefix length
        },
        "GET_PD_POOL",
        PGSQL_GET_PD_POOL_WITH_TAG(WHERE (srv.tag = $1 OR srv.id = 1) AND p.prefix = $2 AND p.prefix_length = $3)
    },

    // Select prefix delegation pool for any server.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_PD_POOL_ANY,
        2,
        {
            OID_VARCHAR,    // 1 prefix
            OID_INT2        // 2 prefix length
        },
        "GET_PD_POOL_ANY",
        PGSQL_GET_PD_POOL_NO_TAG(WHERE p.prefix = $1 AND p.prefix_length = $2)
    },

    // Select shared network by name.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_SHARED_NETWORK6_NAME_NO_TAG,
        1,
        {
            OID_VARCHAR // name of network
        },
        "GET_SHARED_NETWORK6_NAME_NO_TAG",
        PGSQL_GET_SHARED_NETWORK6_NO_TAG(WHERE n.name = $1)
    },

    // Select shared network by name without specifying server tags.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_SHARED_NETWORK6_NAME_ANY,
        1,
        {
            OID_VARCHAR // name of network
        },
        "GET_SHARED_NETWORK6_NAME_ANY",
        PGSQL_GET_SHARED_NETWORK6_ANY(WHERE n.name = $1)
    },

    // Select unassigned shared network by name.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_SHARED_NETWORK6_NAME_UNASSIGNED,
        1,
        {
            OID_VARCHAR // name of network
        },
        "GET_SHARED_NETWORK6_NAME_UNASSIGNED",
        PGSQL_GET_SHARED_NETWORK6_UNASSIGNED(AND n.name = $1)
    },

    // Select all shared networks.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_ALL_SHARED_NETWORKS6,
        0,
        {
            OID_NONE
        },
        "GET_ALL_SHARED_NETWORKS6",
        PGSQL_GET_SHARED_NETWORK6_NO_TAG()
    },

    // Select all unassigned shared networks.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_ALL_SHARED_NETWORKS6_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "GET_ALL_SHARED_NETWORKS6_UNASSIGNED",
        PGSQL_GET_SHARED_NETWORK6_UNASSIGNED()
    },

    // Select modified shared networks.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_SHARED_NETWORKS6,
        1,
        {
            OID_TIMESTAMP  // 1 modification_ts
        },
        "GET_MODIFIED_SHARED_NETWORKS6",
        PGSQL_GET_SHARED_NETWORK6_NO_TAG(WHERE n.modification_ts >= $1)
    },

    // Select modified and unassigned shared networks.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_SHARED_NETWORKS6_UNASSIGNED,
        1,
        {
            OID_TIMESTAMP  // 1 modification_ts
        },
        "GET_MODIFIED_SHARED_NETWORKS6_UNASSIGNED",
        PGSQL_GET_SHARED_NETWORK6_UNASSIGNED(AND n.modification_ts >= $1)
    },

    // Retrieves option definition by code and space.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_OPTION_DEF6_CODE_SPACE,
        3,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_INT2,       // 2 code
            OID_VARCHAR     // 3 space
        },
        "GET_OPTION_DEF6_CODE_SPACE",
        PGSQL_GET_OPTION_DEF(dhcp6, AND d.code = $2 AND d.space = $3)
    },

    // Retrieves all option definitions.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_ALL_OPTION_DEFS6,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "GET_ALL_OPTION_DEFS6",
        PGSQL_GET_OPTION_DEF(dhcp6)
    },

    // Retrieves modified option definitions.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_OPTION_DEFS6,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_TIMESTAMP   // 2 modification_ts
        },
        "GET_MODIFIED_OPTION_DEFS6",
        PGSQL_GET_OPTION_DEF(dhcp6, AND d.modification_ts >= $2)
    },

    // Retrieves global option by code and space.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_OPTION6_CODE_SPACE,
        3,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_INT2,       // 2 code
            OID_VARCHAR     // 3 space
        },
        "GET_OPTION6_CODE_SPACE",
        PGSQL_GET_OPTION6(AND o.scope_id = 0 AND o.code = $2 AND o.space = $3)
    },

    // Retrieves all global options.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_ALL_OPTIONS6,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "GET_ALL_OPTIONS6",
        PGSQL_GET_OPTION6(AND o.scope_id = 0)
    },

    // Retrieves modified options.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_OPTIONS6,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_TIMESTAMP   // 2 modification_ts
        },
        "GET_MODIFIED_OPTIONS6",
        PGSQL_GET_OPTION6(AND o.scope_id = 0 AND o.modification_ts >= $2)
    },

    // Retrieves an option for a given subnet, option code and space.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_OPTION6_SUBNET_ID_CODE_SPACE,
        4,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_INT8,       // 2 subnet_id
            OID_INT2,       // 3 code
            OID_VARCHAR     // 4 space
        },
        "GET_OPTION6_SUBNET_ID_CODE_SPACE",
        PGSQL_GET_OPTION6(AND o.scope_id = 1 AND o.dhcp6_subnet_id = $2 AND o.code = $3 AND o.space = $4)
    },

    // Retrieves an option for a given pool, option code and space.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_OPTION6_POOL_ID_CODE_SPACE,
        4,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_INT8,       // 2 pool_id
            OID_INT2,       // 3 code
            OID_VARCHAR     // 4 space
        },
        "GET_OPTION6_POOL_ID_CODE_SPACE",
        PGSQL_GET_OPTION6(AND o.scope_id = 5 AND o.pool_id = $2 AND o.code = $3 AND o.space = $4)
    },

    // Retrieves an option for a given pd pool, option code and space.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_OPTION6_PD_POOL_ID_CODE_SPACE,
        4,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_INT8,       // 2 pd_pool_id
            OID_INT2,       // 3 code
            OID_VARCHAR     // 4 space
        },
        "GET_OPTION6_PD_POOL_ID_CODE_SPACE",
        PGSQL_GET_OPTION6(AND o.scope_id = 6 AND o.pd_pool_id = $2 AND o.code = $3 AND o.space = $4)
    },

    // Retrieves an option for a given shared network, option code and space.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_OPTION6_SHARED_NETWORK_CODE_SPACE,
        4,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_VARCHAR,    // 2 shared_network_name
            OID_INT2,       // 3 code
            OID_VARCHAR     // 4 space
        },
        "GET_OPTION6_SHARED_NETWORK_CODE_SPACE",
        PGSQL_GET_OPTION6(AND o.scope_id = 4 AND o.shared_network_name = $2 AND o.code = $3 AND o.space = $4)
    },

    // Select a client class by name.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_CLIENT_CLASS6_NAME,
        1,
        {
            OID_VARCHAR // name of class
        },
        "GET_CLIENT_CLASS6_NAME",
        PGSQL_GET_CLIENT_CLASS6_WITH_TAG(WHERE c.name = $1)
    },

    // Select all client classes.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_ALL_CLIENT_CLASSES6,
        0,
        {
            OID_NONE
        },
        "GET_ALL_CLIENT_CLASSES6",
        PGSQL_GET_CLIENT_CLASS6_WITH_TAG()
    },

    // Select all unassigned client classes.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_ALL_CLIENT_CLASSES6_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "GET_ALL_CLIENT_CLASSES6_UNASSIGNED",
        PGSQL_GET_CLIENT_CLASS6_UNASSIGNED()
    },

    // Select modified client classes.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_CLIENT_CLASSES6,
        1,
        {
            OID_TIMESTAMP // 1 modification_ts
        },
        "GET_MODIFIED_CLIENT_CLASSES6",
        PGSQL_GET_CLIENT_CLASS6_WITH_TAG(WHERE c.modification_ts >= $1)
    },

    // Select modified client classes.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_CLIENT_CLASSES6_UNASSIGNED,
        1,
        {
            OID_TIMESTAMP // 1 modification_ts
        },
        "GET_MODIFIED_CLIENT_CLASSES6_UNASSIGNED",
        PGSQL_GET_CLIENT_CLASS6_UNASSIGNED(AND c.modification_ts >= $1)
    },

    // Retrieves the most recent audit entries.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_AUDIT_ENTRIES6_TIME,
        3,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_TIMESTAMP,  // 2 modification_ts
            OID_INT8        // 3 revision id
        },
        "GET_AUDIT_ENTRIES6_TIME",
        PGSQL_GET_AUDIT_ENTRIES_TIME(dhcp6)
    },

    // Retrieves a server by tag.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_SERVER6,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "GET_SERVER6",
        PGSQL_GET_SERVER(dhcp6)
    },

    // Retrieves all servers.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_ALL_SERVERS6,
        0,
        {
            OID_NONE
        },
        "GET_ALL_SERVERS6",
        PGSQL_GET_ALL_SERVERS(dhcp6)
    },

    // Insert global parameter.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_GLOBAL_PARAMETER6,
        4,
        {
            OID_VARCHAR,    // 1 name
            OID_TEXT,       // 2 value
            OID_INT2,       // 3 parameter_type
            OID_TIMESTAMP   // 4 modification_ts
        },
        "INSERT_GLOBAL_PARAMETER6",
        PGSQL_INSERT_GLOBAL_PARAMETER(dhcp6)
    },

    // Insert association of the global parameter with a server.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_GLOBAL_PARAMETER6_SERVER,
        3,
        {
            OID_INT8,       // 1 parameter_id
            OID_TIMESTAMP,  // 2 modification_ts
            OID_VARCHAR     // 3 server_tag
        },
        "INSERT_GLOBAL_PARAMETER6_SERVER",
        PGSQL_INSERT_GLOBAL_PARAMETER_SERVER(dhcp6)
    },

    // Insert a subnet.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_SUBNET6,
        33,
        {
            OID_INT8,       //  1 subnet_id,
            OID_VARCHAR,    //  2 subnet_prefix
            OID_VARCHAR,    //  3 client_class
            OID_VARCHAR,    //  4 interface
            OID_TIMESTAMP,  //  5 modification_ts
            OID_INT8,       //  6 preferred_lifetime
            OID_INT8,       //  7 min_preferred_lifetime
            OID_INT8,       //  8 max_preferred_lifetime
            OID_BOOL,       //  9 rapid_commit
            OID_INT8,       // 10 rebind_timer
            OID_TEXT,       // 11 relay
            OID_INT8,       // 12 renew_timer
            OID_TEXT,       // 13 require_client_classes
            OID_BOOL,       // 14 reservations_global
            OID_VARCHAR,    // 15 shared_network_name
            OID_TEXT,       // 16 user_context - cast as json
            OID_INT8,       // 17 valid_lifetime
            OID_INT8,       // 18 min_valid_lifetime
            OID_INT8,       // 19 max_valid_lifetime
            OID_BOOL,       // 20 calculate_tee_times
            OID_TEXT,       // 21 t1_percent - cast as float
            OID_TEXT,       // 22 t2_percent - cast as float
            OID_BYTEA,      // 23 interface_id
            OID_BOOL,       // 24 ddns_send_updates
            OID_BOOL,       // 25 ddns_override_no_update
            OID_BOOL,       // 26 ddns_override_client_update
            OID_INT8,       // 27 ddns_replace_client_name
            OID_VARCHAR,    // 28 ddns_generated_prefix
            OID_VARCHAR,    // 29 ddns_qualifying_suffix
            OID_BOOL,       // 30 reservations_in_subnet
            OID_BOOL,       // 31 reservations_out_of_pool
            OID_TEXT,       // 32 cache_threshold - cast as float
            OID_INT8        // 33 cache_max_age"
        },
        "INSERT_SUBNET6",
        "INSERT INTO dhcp6_subnet("
        "  subnet_id,"
        "  subnet_prefix,"
        "  client_class,"
        "  interface,"
        "  modification_ts,"
        "  preferred_lifetime,"
        "  min_preferred_lifetime,"
        "  max_preferred_lifetime,"
        "  rapid_commit,"
        "  rebind_timer,"
        "  relay,"
        "  renew_timer,"
        "  require_client_classes,"
        "  reservations_global,"
        "  shared_network_name,"
        "  user_context,"
        "  valid_lifetime,"
        "  min_valid_lifetime,"
        "  max_valid_lifetime,"
        "  calculate_tee_times,"
        "  t1_percent,"
        "  t2_percent,"
        "  interface_id,"
        "  ddns_send_updates,"
        "  ddns_override_no_update,"
        "  ddns_override_client_update,"
        "  ddns_replace_client_name,"
        "  ddns_generated_prefix,"
        "  ddns_qualifying_suffix,"
        "  reservations_in_subnet,"
        "  reservations_out_of_pool,"
        "  cache_threshold,"
        "  cache_max_age"
        ") VALUES ("
        "   $1, $2, $3, $4, $5, $6, $7, $8, $9, $10, "
        "   $11, $12, $13, $14, $15, cast($16 as json), $17, $18, $19, $20, "
        "   cast($21 as float), cast($22 as float), $23, $24, $25, $26, $27, $28, $29, $30, "
        "   $31, cast($32 as float), $33"
        ")"
    },

    // Insert association of the subnet with a server.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_SUBNET6_SERVER,
        3,
        {
            OID_INT8,       // 1 subnet_id
            OID_TIMESTAMP,  // 2 modification_ts
            OID_VARCHAR     // 3 server_tag
        },
        "INSERT_SUBNET6_SERVER",
        PGSQL_INSERT_SUBNET_SERVER(dhcp6)
    },

    // Insert pool for a subnet.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_POOL6,
        7,
        {
            OID_TEXT,       // 1 start_address - cast as inet
            OID_TEXT,       // 2 end_address - cast as inet
            OID_INT8,       // 3 subnet_id
            OID_VARCHAR,    // 4 client_class
            OID_TEXT,       // 5 require_client_classes
            OID_TEXT,       // 6 user_context - cast as json
            OID_TIMESTAMP   // 7 modification_ts
        },
        "INSERT_POOL6",
        PGSQL_INSERT_POOL(dhcp6)
    },

    // Insert pd pool for a subnet.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_PD_POOL,
        10,
        {
            OID_VARCHAR,    //  1 prefix
            OID_INT2,       //  2 prefix_length
            OID_INT2,       //  3 delegated_prefix_length
            OID_INT8,       //  4 subnet_id
            OID_VARCHAR,    //  5 excluded_prefix
            OID_INT2,       //  6 excluded_prefix_length
            OID_VARCHAR,    //  7 client_class
            OID_TEXT,       //  8 require_client_classes
            OID_TEXT,       //  9 user_context - cast as json
            OID_TIMESTAMP,  // 10 modification_ts
        },
        "INSERT_PD_POOL",
        PGSQL_INSERT_PD_POOL()
    },

    // Insert a shared network.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_SHARED_NETWORK6,
        31,
        {
            OID_VARCHAR,    //  1 name
            OID_VARCHAR,    //  2 client_class
            OID_VARCHAR,    //  3 interface
            OID_TIMESTAMP,  //  4 modification_ts
            OID_INT8,       //  5 preferred_lifetime
            OID_INT8,       //  6 min_preferred_lifetime
            OID_INT8,       //  7 max_preferred_lifetime
            OID_BOOL,       //  8 rapid_commit
            OID_INT8,       //  9 rebind_timer
            OID_TEXT,       // 10 relay
            OID_INT8,       // 11 renew_timer
            OID_TEXT,       // 12 require_client_classes
            OID_BOOL,       // 13 reservations_global
            OID_TEXT,       // 14 user_context - cast as json
            OID_INT8,       // 15 valid_lifetime
            OID_INT8,       // 16 min_valid_lifetime
            OID_INT8,       // 17 max_valid_lifetime
            OID_BOOL,       // 18 calculate_tee_times
            OID_TEXT,       // 19 t1_percent - cast as float
            OID_TEXT,       // 20 t2_percent - cast as float
            OID_BYTEA,      // 21 interface-id
            OID_BOOL,       // 22 ddns_send_updates
            OID_BOOL,       // 23 ddns_override_no_update
            OID_BOOL,       // 24 ddns_override_client_update
            OID_INT8,       // 25 ddns_replace_client_name
            OID_VARCHAR,    // 26 ddns_generated_prefix
            OID_VARCHAR,    // 27 ddns_qualifying_suffix
            OID_BOOL,       // 28 reservations_in_subnet
            OID_BOOL,       // 29 reservations_out_of_pool
            OID_TEXT,       // 30 cache_threshold - cast as float
            OID_INT8        // 31 cache_max_age
        },
        "INSERT_SHARED_NETWORK6",
        "INSERT INTO dhcp6_shared_network("
        "  name,"
        "  client_class,"
        "  interface,"
        "  modification_ts,"
        "  preferred_lifetime,"
        "  min_preferred_lifetime,"
        "  max_preferred_lifetime,"
        "  rapid_commit,"
        "  rebind_timer,"
        "  relay,"
        "  renew_timer,"
        "  require_client_classes,"
        "  reservations_global,"
        "  user_context,"
        "  valid_lifetime,"
        "  min_valid_lifetime,"
        "  max_valid_lifetime,"
        "  calculate_tee_times,"
        "  t1_percent,"
        "  t2_percent,"
        "  interface_id,"
        "  ddns_send_updates,"
        "  ddns_override_no_update,"
        "  ddns_override_client_update,"
        "  ddns_replace_client_name,"
        "  ddns_generated_prefix,"
        "  ddns_qualifying_suffix,"
        "  reservations_in_subnet,"
        "  reservations_out_of_pool,"
        "  cache_threshold,"
        "  cache_max_age"
        ") VALUES ("
        "   $1, $2, $3, $4, $5, $6, $7, $8, $9, $10, "
        "   $11, $12, $13, cast($14 as json), $15, $16, $17, $18,"
        "   cast($19 as float), cast($20 as float), $21, $22, $23,"
        "   $24, $25, $26, $27, $28, $29, cast($30 as float), $31"
        ")"
    },

    // Insert association of the shared network with a server.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_SHARED_NETWORK6_SERVER,
        3,
        {
            OID_VARCHAR,    // 1 shared_network_name
            OID_TIMESTAMP,  // 2 modification_ts
            OID_VARCHAR     // 3 server_tag
        },
        "INSERT_SHARED_NETWORK6_SERVER",
        PGSQL_INSERT_SHARED_NETWORK_SERVER(dhcp6)
    },

    // Insert option definition.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6,
        10,
        {
            OID_INT2,       //  1 code
            OID_VARCHAR,    //  2 name
            OID_VARCHAR,    //  3 space
            OID_INT2,       //  4 type
            OID_TIMESTAMP,  //  5 modification_ts
            OID_BOOL,       //  6 is_array
            OID_VARCHAR,    //  7 encapsulate
            OID_VARCHAR,    //  8 record_types
            OID_VARCHAR,    //  9 user_context
            OID_INT8        // 10 class_id
        },
        "INSERT_OPTION_DEF6",
        PGSQL_INSERT_OPTION_DEF(dhcp6)
    },

    // Insert option definition for client class.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6_CLIENT_CLASS,
        10,
        {
            OID_INT2,       //  1 code
            OID_VARCHAR,    //  2 name
            OID_VARCHAR,    //  3 space
            OID_INT2,       //  4 type
            OID_TIMESTAMP,  //  5 modification_ts
            OID_BOOL,       //  6 is_array
            OID_VARCHAR,    //  7 encapsulate
            OID_VARCHAR,    //  8 record_types
            OID_VARCHAR,    //  9 user_context
            OID_VARCHAR     // 10 class name for where clause
        },
        "INSERT_OPTION_DEF6_CLIENT_CLASS",
        PGSQL_INSERT_OPTION_DEF_CLIENT_CLASS(dhcp6)
    },

    // Insert association of the option definition with a server.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6_SERVER,
        3,
        {
            OID_INT8,       // 1 option_def_id
            OID_TIMESTAMP,  // 2 modification_ts
            OID_VARCHAR     // 3 server_tag
        },
        "INSERT_OPTION_DEF6_SERVER",
        PGSQL_INSERT_OPTION_DEF_SERVER(dhcp6)
    },

    // Insert subnet specific option.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION6,
        13,
        {
            OID_INT2,       //  1 code
            OID_BYTEA,      //  2 value
            OID_TEXT,       //  3 formatted_value
            OID_VARCHAR,    //  4 space
            OID_BOOL,       //  5 persistent
            OID_VARCHAR,    //  6 dhcp_client_class
            OID_INT8,       //  7 dhcp6_subnet_id
            OID_INT2,       //  8 scope_id
            OID_TEXT,       //  9 user_context
            OID_VARCHAR,    // 10 shared_network_name
            OID_INT8,       // 11 pool_id
            OID_TIMESTAMP,  // 12 modification_ts
            OID_INT8        // 13 pd_pool_id
        },
        "INSERT_OPTION6",
        PGSQL_INSERT_OPTION6()
    },

    // Insert association of the DHCP option with a server.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION6_SERVER,
        3,
        {
            OID_INT8,       // 1 option_id
            OID_TIMESTAMP,  // 2 modification_ts
            OID_VARCHAR     // 3 server_tag
        },
        "INSERT_OPTION6_SERVER",
        PGSQL_INSERT_OPTION_SERVER(dhcp6)
    },

    // Insert client class.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_CLIENT_CLASS6,
        13,
        {
            OID_VARCHAR,    //  1 name
            OID_TEXT,       //  2 test
            OID_BOOL,       //  3 only_if_required
            OID_INT8,       //  4 valid_lifetime
            OID_INT8,       //  5 min_valid_lifetime
            OID_INT8,       //  6 max_valid_lifetime
            OID_BOOL,       //  7 depend_on_known_directly
            OID_VARCHAR,    //  8 follow_class_name
            OID_INT8,       //  9 preferred_lifetime
            OID_INT8,       // 10 min_preferred_lifetime
            OID_INT8,       // 11 max_preferred_lifetime
            OID_TIMESTAMP,  // 12 modification_ts
            OID_TEXT        // 13 user_context cast as JSON
        },
        "INSERT_CLIENT_CLASS6",
        "INSERT INTO dhcp6_client_class("
        "  name,"
        "  test,"
        "  only_if_required,"
        "  valid_lifetime,"
        "  min_valid_lifetime,"
        "  max_valid_lifetime,"
        "  depend_on_known_directly,"
        "  follow_class_name,"
        "  preferred_lifetime,"
        "  min_preferred_lifetime,"
        "  max_preferred_lifetime,"
        "  modification_ts,"
        "  user_context "
        ") VALUES ("
        "   $1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, cast($13 as JSON)"
        ")"
    },

    // Insert association of a client class with a server.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_CLIENT_CLASS6_SERVER,
        3,
        {
            OID_VARCHAR,    // 1 class_name
            OID_TIMESTAMP,  // 2 modification_ts
            OID_VARCHAR     // 3 server_tag
        },
        "INSERT_CLIENT_CLASS6_SERVER",
        PGSQL_INSERT_CLIENT_CLASS_SERVER(dhcp6)
    },

    // Insert client class dependency.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_CLIENT_CLASS6_DEPENDENCY,
        2,
        {
            OID_VARCHAR,    // class name
            OID_VARCHAR     // dependency class name
        },
        "INSERT_CLIENT_CLASS6_DEPENDENCY",
        PGSQL_INSERT_CLIENT_CLASS_DEPENDENCY(dhcp6)
    },

    // Insert server with server tag and description.
    {
        // PgSqlConfigBackendDHCPv6Impl::INSERT_SERVER6,
        3,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_VARCHAR,    // 2 description
            OID_TIMESTAMP   // 3 modification_ts
        },
        "INSERT_SERVER6",
        PGSQL_INSERT_SERVER(dhcp6)
    },

    // Update existing global parameter.
    {
        // PgSqlConfigBackendDHCPv6Impl::UPDATE_GLOBAL_PARAMETER6,
        6,
        {
            OID_VARCHAR,    // 1 name
            OID_TEXT,       // 2 value
            OID_INT2,       // 3 parameter_type
            OID_TIMESTAMP,  // 4 modification_ts
            OID_VARCHAR,    // 5 server_tag
            OID_VARCHAR,    // 6 name (of global to update)
        },
        "UPDATE_GLOBAL_PARAMETER6",
        PGSQL_UPDATE_GLOBAL_PARAMETER(dhcp6)
    },

    // Update existing subnet.
    {
        // PgSqlConfigBackendDHCPv6Impl::UPDATE_SUBNET6,
        35,
        {
            OID_INT8,       //  1 subnet_id,
            OID_VARCHAR,    //  2 subnet_prefix
            OID_VARCHAR,    //  3 client_class
            OID_VARCHAR,    //  4 interface
            OID_TIMESTAMP,  //  5 modification_ts
            OID_INT8,       //  6 preferred_lifetime
            OID_INT8,       //  7 min_preferred_lifetime
            OID_INT8,       //  8 max_preferred_lifetime
            OID_BOOL,       //  9 rapid_commit
            OID_INT8,       // 10 rebind_timer
            OID_TEXT,       // 11 relay
            OID_INT8,       // 12 renew_timer
            OID_TEXT,       // 13 require_client_classes
            OID_BOOL,       // 14 reservations_global
            OID_VARCHAR,    // 15 shared_network_name
            OID_TEXT,       // 16 user_context - cast as json
            OID_INT8,       // 17 valid_lifetime
            OID_INT8,       // 18 min_valid_lifetime
            OID_INT8,       // 19 max_valid_lifetime
            OID_BOOL,       // 20 calculate_tee_times
            OID_TEXT,       // 21 t1_percent - cast as float
            OID_TEXT,       // 22 t2_percent - cast as float
            OID_BYTEA,      // 23 interface_id
            OID_BOOL,       // 24 ddns_send_updates
            OID_BOOL,       // 25 ddns_override_no_update
            OID_BOOL,       // 26 ddns_override_client_update
            OID_INT8,       // 27 ddns_replace_client_name
            OID_VARCHAR,    // 28 ddns_generated_prefix
            OID_VARCHAR,    // 29 ddns_qualifying_suffix
            OID_BOOL,       // 30 reservations_in_subnet
            OID_BOOL,       // 31 reservations_out_of_pool
            OID_TEXT,       // 32 cache_threshold - cast as float
            OID_INT8        // 33 cache_max_age"
        },
        "UPDATE_SUBNET6",
        "UPDATE dhcp6_subnet SET"
        "  subnet_id = $1,"
        "  subnet_prefix = $2,"
        "  client_class = $3,"
        "  interface = $4,"
        "  modification_ts = $5,"
        "  preferred_lifetime = $6,"
        "  min_preferred_lifetime = $7,"
        "  max_preferred_lifetime = $8,"
        "  rapid_commit = $9,"
        "  rebind_timer = $10,"
        "  relay = $11,"
        "  renew_timer = $12,"
        "  require_client_classes = $13,"
        "  reservations_global = $14,"
        "  shared_network_name = $15,"
        "  user_context = cast($16 as json),"
        "  valid_lifetime = $17,"
        "  min_valid_lifetime = $18,"
        "  max_valid_lifetime = $19,"
        "  calculate_tee_times = $20,"
        "  t1_percent = cast($21 as float),"
        "  t2_percent = cast($22 as float),"
        "  interface_id = $23,"
        "  ddns_send_updates = $24,"
        "  ddns_override_no_update = $25,"
        "  ddns_override_client_update = $26,"
        "  ddns_replace_client_name = $27,"
        "  ddns_generated_prefix = $28,"
        "  ddns_qualifying_suffix = $29,"
        "  reservations_in_subnet = $30,"
        "  reservations_out_of_pool = $31,"
        "  cache_threshold = cast($32 as float),"
        "  cache_max_age =  $33"
        "WHERE subnet_id = $34 OR subnet_prefix = $35"
    },

    // Update existing shared network.
    {
        // PgSqlConfigBackendDHCPv6Impl::UPDATE_SHARED_NETWORK6,
        32,
        {
            OID_VARCHAR,    //  1 name
            OID_VARCHAR,    //  2 client_class
            OID_VARCHAR,    //  3 interface
            OID_TIMESTAMP,  //  4 modification_ts
            OID_INT8,       //  5 preferred_lifetime
            OID_INT8,       //  6 min_preferred_lifetime
            OID_INT8,       //  7 max_preferred_lifetime
            OID_BOOL,       //  8 rapid_commit
            OID_INT8,       //  9 rebind_timer
            OID_TEXT,       // 10 relay
            OID_INT8,       // 11 renew_timer
            OID_TEXT,       // 12 require_client_classes
            OID_BOOL,       // 13 reservations_global
            OID_TEXT,       // 14 user_context - cast as json
            OID_INT8,       // 15 valid_lifetime
            OID_INT8,       // 16 min_valid_lifetime
            OID_INT8,       // 17 max_valid_lifetime
            OID_BOOL,       // 18 calculate_tee_times
            OID_TEXT,       // 19 t1_percent - cast as float
            OID_TEXT,       // 20 t2_percent - cast as float
            OID_BYTEA,      // 21 interface-id
            OID_BOOL,       // 22 ddns_send_updates
            OID_BOOL,       // 23 ddns_override_no_update
            OID_BOOL,       // 24 ddns_override_client_update
            OID_INT8,       // 25 ddns_replace_client_name
            OID_VARCHAR,    // 26 ddns_generated_prefix
            OID_VARCHAR,    // 27 ddns_qualifying_suffix
            OID_BOOL,       // 28 reservations_in_subnet
            OID_BOOL,       // 29 reservations_out_of_pool
            OID_TEXT,       // 30 cache_threshold - cast as float
            OID_INT8        // 31 cache_max_age
        },
        "UPDATE_SHARED_NETWORK6",
        "UPDATE dhcp6_shared_network SET"
        "  name = $1,"
        "  client_class = $2,"
        "  interface = $3,"
        "  modification_ts = $4,"
        "  preferred_lifetime = $5,"
        "  min_preferred_lifetime = $6,"
        "  max_preferred_lifetime = $7,"
        "  rapid_commit = $8,"
        "  rebind_timer = $9,"
        "  relay = $10,"
        "  renew_timer = $11,"
        "  require_client_classes = $12,"
        "  reservations_global = $13,"
        "  user_context = cast($14 as json),"
        "  valid_lifetime = $15,"
        "  min_valid_lifetime = $16,"
        "  max_valid_lifetime = $17,"
        "  calculate_tee_times = $18,"
        "  t1_percent = cast($19 as float),"
        "  t2_percent = cast($20 as float),"
        "  interface_id = $21,"
        "  ddns_send_updates = $22,"
        "  ddns_override_no_update = $23,"
        "  ddns_override_client_update = $24,"
        "  ddns_replace_client_name = $25,"
        "  ddns_generated_prefix = $26,"
        "  ddns_qualifying_suffix = $27,"
        "  reservations_in_subnet = $28,"
        "  reservations_out_of_pool = $29,"
        "  cache_threshold = cast($30 as float),"
        "  cache_max_age = $31 "
        "WHERE name = $32"
    },

    // Update existing option definition.
    {
        // PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION_DEF6,
        13,
        {
            OID_INT2,       //  1 code
            OID_VARCHAR,    //  2 name
            OID_VARCHAR,    //  3 space
            OID_INT2,       //  4 type
            OID_TIMESTAMP,  //  5 modification_ts
            OID_BOOL,       //  6 is_array
            OID_VARCHAR,    //  7 encapsulate
            OID_VARCHAR,    //  8 record_types
            OID_TEXT,       //  9 user_context
            OID_INT2,       // 10 class_id
            OID_VARCHAR,    // 11 server_tag
            OID_INT2,       // 12 code (of option to update)
            OID_VARCHAR,    // 13 space (of option to update)
        },
        "UPDATE_OPTION_DEF6",
        PGSQL_UPDATE_OPTION_DEF(dhcp6)
    },

    // Update existing client class option definition.
    {
        // PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION_DEF6_CLIENT_CLASS,
        13,
        {
            OID_INT2,       //  1 code
            OID_VARCHAR,    //  2 name
            OID_VARCHAR,    //  3 space
            OID_INT2,       //  4 type
            OID_TIMESTAMP,  //  5 modification_ts
            OID_BOOL,       //  6 is_array
            OID_VARCHAR,    //  7 encapsulate
            OID_VARCHAR,    //  8 record_types
            OID_TEXT,       //  9 user_context
            OID_VARCHAR,    // 10 name (of class option belongs to)
            OID_VARCHAR,    // 11 server_tag
            OID_INT2,       // 12 code (of option to update)
            OID_VARCHAR,    // 13 space (of option to update)
        },
        "UPDATE_OPTION_DEF6_CLIENT_CLASS",
        PGSQL_UPDATE_OPTION_DEF_CLIENT_CLASS(dhcp6)
    },

    // Update existing global option.
    {
        // PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6,
        16,
        {
            OID_INT2,       //  1 code
            OID_BYTEA,      //  2 value
            OID_TEXT,       //  3 formatted_value
            OID_VARCHAR,    //  4 space
            OID_BOOL,       //  5 persistent
            OID_VARCHAR,    //  6 dhcp_client_class
            OID_INT8,       //  7 dhcp6_subnet_id
            OID_INT2,       //  8 scope_id
            OID_TEXT,       //  9 user_context
            OID_VARCHAR,    // 10 shared_network_name
            OID_INT8,       // 11 pool_id
            OID_TIMESTAMP,  // 12 modification_ts
            OID_INT8,       // 13 pd_pool_id
            OID_VARCHAR,    // 14 server_tag
            OID_INT2,       // 15 code (of option to update)
            OID_VARCHAR,    // 16 space (of option to update)
        },
        "UPDATE_OPTION6",
        PGSQL_UPDATE_OPTION6_WITH_TAG(AND o.scope_id = 0 AND o.code = $15 AND o.space = $16)
    },

    // Update existing subnet level option.
    {
        // PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_SUBNET_ID,
        16,
        {
            OID_INT2,       //  1 code
            OID_BYTEA,      //  2 value
            OID_TEXT,       //  3 formatted_value
            OID_VARCHAR,    //  4 space
            OID_BOOL,       //  5 persistent
            OID_VARCHAR,    //  6 dhcp_client_class
            OID_INT8,       //  7 dhcp6_subnet_id
            OID_INT2,       //  8 scope_id
            OID_TEXT,       //  9 user_context
            OID_VARCHAR,    // 10 shared_network_name
            OID_INT8,       // 11 pool_id
            OID_TIMESTAMP,  // 12 modification_ts
            OID_INT8,       // 13 pd_pool_id
            OID_INT8,       // 14 subnet_id (of option to update)
            OID_INT2,       // 15 code (of option to update)
            OID_VARCHAR     // 16 space (of option to update)
        },
        "UPDATE_OPTION6_SUBNET_ID",
        PGSQL_UPDATE_OPTION6_NO_TAG(o.scope_id = 1 AND o.dhcp6_subnet_id = $14 AND o.code = $15 AND o.space = $16)
    },

    // Update existing pool level option.
    {
        // PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_POOL_ID,
        16,
        {
            OID_INT2,       //  1 code
            OID_BYTEA,      //  2 value
            OID_TEXT,       //  3 formatted_value
            OID_VARCHAR,    //  4 space
            OID_BOOL,       //  5 persistent
            OID_VARCHAR,    //  6 dhcp_client_class
            OID_INT8,       //  7 dhcp6_subnet_id
            OID_INT2,       //  8 scope_id
            OID_TEXT,       //  9 user_context
            OID_VARCHAR,    // 10 shared_network_name
            OID_INT8,       // 11 pool_id
            OID_TIMESTAMP,  // 12 modification_ts
            OID_INT8,       // 13 pd_pool_id
            OID_INT8,       // 14 pool_id (of option to update)
            OID_INT2,       // 15 code (of option to update)
            OID_VARCHAR     // 16 space (of option to update)
        },
        "UPDATE_OPTION6_POOL_ID",
        PGSQL_UPDATE_OPTION6_NO_TAG(o.scope_id = 5 AND o.pool_id = $14 AND o.code = $15 AND o.space = $16)
    },

    // Update existing pd pool level option.
    {
        // PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_PD_POOL_ID,
        16,
        {
            OID_INT2,       //  1 code
            OID_BYTEA,      //  2 value
            OID_TEXT,       //  3 formatted_value
            OID_VARCHAR,    //  4 space
            OID_BOOL,       //  5 persistent
            OID_VARCHAR,    //  6 dhcp_client_class
            OID_INT8,       //  7 dhcp6_subnet_id
            OID_INT2,       //  8 scope_id
            OID_TEXT,       //  9 user_context
            OID_VARCHAR,    // 10 shared_network_name
            OID_INT8,       // 11 pool_id
            OID_TIMESTAMP,  // 12 modification_ts
            OID_INT8,       // 13 pd_pool_id
            OID_INT8,       // 14 pd_pool_id (of option to update)
            OID_INT2,       // 15 code (of option to update)
            OID_VARCHAR     // 16 space (of option to update)
        },
        "UPDATE_OPTION6_PD_POOL_ID",
        PGSQL_UPDATE_OPTION6_NO_TAG(o.scope_id = 6 AND o.pd_pool_id = $14 AND o.code = $15 AND o.space = $16)
    },

    // Update existing shared network level option.
    {
        // PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_SHARED_NETWORK,
        16,
        {
            OID_INT2,       //  1 code
            OID_BYTEA,      //  2 value
            OID_TEXT,       //  3 formatted_value
            OID_VARCHAR,    //  4 space
            OID_BOOL,       //  5 persistent
            OID_VARCHAR,    //  6 dhcp_client_class
            OID_INT8,       //  7 dhcp6_subnet_id
            OID_INT2,       //  8 scope_id
            OID_TEXT,       //  9 user_context
            OID_VARCHAR,    // 10 shared_network_name
            OID_INT8,       // 11 pool_id
            OID_TIMESTAMP,  // 12 modification_ts
            OID_INT8,       // 13 pd_pool_id
            OID_VARCHAR,    // 14 shared_network_name (of option to update)
            OID_INT2,       // 15 code (of option to update)
            OID_VARCHAR     // 16 space (of option to update)
        },
        "UPDATE_OPTION6_SHARED_NETWORK",
        PGSQL_UPDATE_OPTION6_NO_TAG(o.scope_id = 4 AND o.shared_network_name = $14 AND o.code = $15 AND o.space = $16)
    },

    // Update existing client class level option.
    {
        // PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_CLIENT_CLASS,
        16,
        {
            OID_INT2,       //  1 code
            OID_BYTEA,      //  2 value
            OID_TEXT,       //  3 formatted_value
            OID_VARCHAR,    //  4 space
            OID_BOOL,       //  5 persistent
            OID_VARCHAR,    //  6 dhcp_client_class
            OID_INT8,       //  7 dhcp6_subnet_id
            OID_INT2,       //  8 scope_id
            OID_TEXT,       //  9 user_context
            OID_VARCHAR,    // 10 shared_network_name
            OID_INT8,       // 11 pool_id
            OID_TIMESTAMP,  // 12 modification_ts
            OID_INT8,       // 13 pd_pool_id
            OID_VARCHAR,    // 14 client_class (of option to update)
            OID_INT2,       // 15 code (of option to update)
            OID_VARCHAR     // 16 space (of option to update)
        },
        "UPDATE_OPTION6_CLIENT_CLASS",
        PGSQL_UPDATE_OPTION6_NO_TAG(o.scope_id = 2 AND o.dhcp_client_class = $14 AND o.code = $15 AND o.space = $16)
    },

    // Update existing client class with specifying its position.
    {
        // PgSqlConfigBackendDHCPv6Impl::UPDATE_CLIENT_CLASS6,
        14,
        {
            OID_VARCHAR,    //  1 name
            OID_TEXT,       //  2 test
            OID_BOOL,       //  3 only_if_required
            OID_INT8,       //  4 valid_lifetime
            OID_INT8,       //  5 min_valid_lifetime
            OID_INT8,       //  6 max_valid_lifetime
            OID_BOOL,       //  7 depend_on_known_directly
            OID_VARCHAR,    //  8 follow_class_name
            OID_INT8,       //  9 preferred_lifetime
            OID_INT8,       // 10 min_preferred_lifetime
            OID_INT8,       // 11 max_preferred_lifetime
            OID_TIMESTAMP,  // 12 modification_ts
            OID_TEXT,       // 13 user_context
            OID_VARCHAR     // 14 name (of class to update)
        },
        "UPDATE_CLIENT_CLASS6",
        PGSQL_UPDATE_CLIENT_CLASS6("follow_class_name = $8,")
    },

    // Update existing client class without specifying its position.
    {
        // PgSqlConfigBackendDHCPv6Impl::UPDATE_CLIENT_CLASS6_SAME_POSITION,
        14,
        {
            OID_VARCHAR,    //  1 name
            OID_TEXT,       //  2 test
            OID_BOOL,       //  3 only_if_required
            OID_INT8,       //  4 valid_lifetime
            OID_INT8,       //  5 min_valid_lifetime
            OID_INT8,       //  6 max_valid_lifetime
            OID_BOOL,       //  7 depend_on_known_directly
            OID_VARCHAR,    //  8 follow_class_name
            OID_INT8,       //  9 preferred_lifetime
            OID_INT8,       // 10 min_preferred_lifetime
            OID_INT8,       // 11 max_preferred_lifetime
            OID_TIMESTAMP,  // 12 modification_ts
            OID_TEXT,       // 13 user_context
            OID_VARCHAR     // 14 name (of class to update)
        },
        "UPDATE_CLIENT_CLASS6_SAME_POSITION",
        PGSQL_UPDATE_CLIENT_CLASS6("")
    },

    // Update existing server, e.g. server description.
    {
        // PgSqlConfigBackendDHCPv6Impl::UPDATE_SERVER6,
        4,
        {
            OID_VARCHAR,    // 1 tag
            OID_VARCHAR,    // 2 description
            OID_TIMESTAMP,  // 3 modification_ts
            OID_VARCHAR     // 4 tag (of server to update)
        },
        "UPDATE_SERVER6",
        PGSQL_UPDATE_SERVER(dhcp6)
    },

    // Delete global parameter by name.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_GLOBAL_PARAMETER6,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_VARCHAR     // 2 name of parameter
        },
        "DELETE_GLOBAL_PARAMETER6",
        PGSQL_DELETE_GLOBAL_PARAMETER(dhcp6, AND g.name = $2)
    },

    // Delete all global parameters.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_GLOBAL_PARAMETERS6,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "DELETE_ALL_GLOBAL_PARAMETERS6",
        PGSQL_DELETE_GLOBAL_PARAMETER(dhcp6)
    },

    // Delete all global parameters which are unassigned to any servers.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_GLOBAL_PARAMETERS6_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "DELETE_ALL_GLOBAL_PARAMETERS6_UNASSIGNED",
        PGSQL_DELETE_GLOBAL_PARAMETER_UNASSIGNED(dhcp6)
    },

    // Delete subnet by id with specifying server tag.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_ID_WITH_TAG,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_INT8        // 2 subnet_id
        },
        "DELETE_SUBNET6_ID_WITH_TAG",
        PGSQL_DELETE_SUBNET_WITH_TAG(dhcp6, AND s.subnet_id = $2)
    },

    // Delete subnet by id without specifying server tag.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_ID_ANY,
        1,
        {
            OID_INT8    // 1 subnet_id
        },
        "DELETE_SUBNET6_ID_ANY",
        PGSQL_DELETE_SUBNET_ANY(dhcp6, WHERE s.subnet_id = $1)
    },

    // Delete subnet by prefix with specifying server tag.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_PREFIX_WITH_TAG,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_VARCHAR     // 2 subnet_prefix
        },
        "DELETE_SUBNET6_PREFIX_WITH_TAG",
        PGSQL_DELETE_SUBNET_WITH_TAG(dhcp6, AND s.subnet_prefix = $2)
    },

    // Delete subnet by prefix without specifying server tag.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_PREFIX_ANY,
        1,
        {
            OID_VARCHAR // 1 subnet_prefix
        },
        "DELETE_SUBNET6_PREFIX_ANY",
        PGSQL_DELETE_SUBNET_ANY(dhcp6, WHERE s.subnet_prefix = $1)
    },

    // Delete all subnets.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "DELETE_ALL_SUBNETS6",
        PGSQL_DELETE_SUBNET_WITH_TAG(dhcp6)
    },

    // Delete all unassigned subnets.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "DELETE_ALL_SUBNETS6_UNASSIGNED",
        PGSQL_DELETE_SUBNET_UNASSIGNED(dhcp6)
    },

    // Delete all subnets for a shared network.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6_SHARED_NETWORK_NAME,
        1,
        {
            OID_VARCHAR // 1 shared_network_name
        },
        "DELETE_ALL_SUBNETS6_SHARED_NETWORK_NAME",
        PGSQL_DELETE_SUBNET_ANY(dhcp6, WHERE s.shared_network_name = $1)
    },

    // Delete associations of a subnet with server.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_SERVER,
        1,
        {
            OID_INT8    // 1 subnet_id
        },
        "DELETE_SUBNET6_SERVER",
        PGSQL_DELETE_SUBNET_SERVER(dhcp6),
    },

    // Delete pools for a subnet.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_POOLS6,
        2,
        {
            OID_INT8,   // 1 subnet_id
            OID_VARCHAR // 2 subnet_prefix
        },
        "DELETE_POOLS6",
        PGSQL_DELETE_POOLS(dhcp6)
    },

    // Delete pd pools for a subnet.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_PD_POOLS,
        2,
        {
            OID_INT8,   // 1 subnet_id
            OID_VARCHAR // 2 subnet_prefix
        },
        "DELETE_PD_POOLS",
        PGSQL_DELETE_PD_POOLS()
    },

    // Delete shared network by name with specifying server tag.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_NAME_WITH_TAG,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_VARCHAR     // 2 shared_network_name
        },
        "DELETE_SHARED_NETWORK6_NAME_WITH_TAG",
        PGSQL_DELETE_SHARED_NETWORK_WITH_TAG(dhcp6, AND n.name = $2)
    },

    // Delete shared network by name without specifying server tag.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_NAME_ANY,
        1,
        {
            OID_VARCHAR // 1 shared_network_name
        },
        "DELETE_SHARED_NETWORK6_NAME_ANY",
        PGSQL_DELETE_SHARED_NETWORK_ANY(dhcp6, WHERE n.name = $1)
    },

    // Delete all shared networks.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SHARED_NETWORKS6,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "DELETE_ALL_SHARED_NETWORKS6",
        PGSQL_DELETE_SHARED_NETWORK_WITH_TAG(dhcp6)
    },

    // Delete all unassigned shared networks.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SHARED_NETWORKS6_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "DELETE_ALL_SHARED_NETWORKS6_UNASSIGNED",
        PGSQL_DELETE_SHARED_NETWORK_UNASSIGNED(dhcp6)
    },

    // Delete associations of a shared network with server.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_SERVER,
        1,
        {
            OID_VARCHAR // 1 shared_network_name
        },
        "DELETE_SHARED_NETWORK6_SERVER",
        PGSQL_DELETE_SHARED_NETWORK_SERVER(dhcp6)
    },

    // Delete option definition.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION_DEF6_CODE_NAME,
        3,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_INT2,       // 2 code
            OID_VARCHAR     // 3 space
        },
        "DELETE_OPTION_DEF6_CODE_NAME",
        PGSQL_DELETE_OPTION_DEF(dhcp6, AND code = $2 AND space = $3)
    },

    // Delete all option definitions.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_OPTION_DEFS6,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "DELETE_ALL_OPTION_DEFS6",
        PGSQL_DELETE_OPTION_DEF(dhcp6)
    },

    // Delete all option definitions which are assigned to no servers.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_OPTION_DEFS6_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "DELETE_ALL_OPTION_DEFS6_UNASSIGNED",
        PGSQL_DELETE_OPTION_DEF_UNASSIGNED(dhcp6)
    },

    // Delete client class specific option definitions.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION_DEFS6_CLIENT_CLASS,
        1,
        {
            OID_VARCHAR // 1 class name
        },
        "DELETE_OPTION_DEFS6_CLIENT_CLASS",
        PGSQL_DELETE_OPTION_DEFS_CLIENT_CLASS(dhcp6)
    },

    // Delete single global option.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION6,
        3,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_INT2,       // 2 code
            OID_VARCHAR     // 3 space
        },
        "DELETE_OPTION6",
        PGSQL_DELETE_OPTION_WITH_TAG(dhcp6, AND o.scope_id = 0 AND o.code = $2 AND o.space = $3)
    },

    // Delete all global options which are unassigned to any servers.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_GLOBAL_OPTIONS6_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "DELETE_ALL_GLOBAL_OPTIONS6_UNASSIGNED",
        PGSQL_DELETE_OPTION_UNASSIGNED(dhcp6, AND o.scope_id = 0)
    },

    // Delete single option from a subnet.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION6_SUBNET_ID,
        3,
        {
            OID_INT8,   // 1 subnet_id
            OID_INT2,   // 2 code
            OID_VARCHAR // 3 space
        },
        "DELETE_OPTION6_SUBNET_ID",
        PGSQL_DELETE_OPTION_NO_TAG(dhcp6,
            WHERE o.scope_id = 1 AND o.dhcp6_subnet_id = $1 AND o.code = $2 AND o.space = $3)
    },

    // Delete single option from a pool.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION6_POOL_RANGE,
        4,
        {
            OID_TEXT,   // 1 start_address - cast as inet
            OID_TEXT,   // 2 start_address - cast as inet
            OID_INT2,   // 3 code
            OID_VARCHAR // 4 space
        },
        "DELETE_OPTION6_POOL_RANGE",
        PGSQL_DELETE_OPTION_POOL_RANGE(dhcp6, o.scope_id = 5 AND o.code = $3 AND o.space = $4)
    },

    // Delete single option from a pd pool.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION6_PD_POOL,
        4,
        {
            OID_TEXT,   // 1 prefix
            OID_INT2,   // 2 prefix_length
            OID_INT2,   // 3 code
            OID_VARCHAR // 4 space
        },
        "DELETE_OPTION6_PD_POOL",
        PGSQL_DELETE_OPTION_PD_POOL(o.scope_id = 6 AND o.code = $3 AND o.space = $4)
    },

    // Delete single option from a shared network.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION6_SHARED_NETWORK,
        3,
        {
            OID_VARCHAR,    // 1 shared_network_name
            OID_INT2,       // 2 code
            OID_VARCHAR     // 3 space
        },
        "DELETE_OPTION6_SHARED_NETWORK",
        PGSQL_DELETE_OPTION_NO_TAG(dhcp6,
            WHERE o.scope_id = 4 AND o.shared_network_name = $1 AND o.code = $2 AND o.space = $3)
    },

    // Delete options belonging to a subnet.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_OPTIONS6_SUBNET_ID_PREFIX,
        2,
        {
            OID_INT8,   // 1 subnet_id
            OID_VARCHAR // 2 subnet_prefix
        },
        "DELETE_OPTIONS6_SUBNET_ID_PREFIX",
        PGSQL_DELETE_OPTION_SUBNET_ID_PREFIX(dhcp6)
    },

    // Delete options belonging to a shared_network.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_OPTIONS6_SHARED_NETWORK,
        1,
        {
            OID_VARCHAR // shared_network_name
        },
        "DELETE_OPTIONS6_SHARED_NETWORK",
        PGSQL_DELETE_OPTION_NO_TAG(dhcp6, WHERE o.scope_id = 4 AND o.shared_network_name = $1)
    },

    // Delete options belonging to a client class.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_OPTIONS6_CLIENT_CLASS,
        1,
        {
            OID_VARCHAR // dhcp_client_class
        },
        "DELETE_OPTIONS6_CLIENT_CLASS",
        PGSQL_DELETE_OPTION_NO_TAG(dhcp6, WHERE o.scope_id = 2 AND o.dhcp_client_class = $1)
    },

    // Delete all dependencies of a client class.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6_DEPENDENCY,
        1,
        {
            OID_VARCHAR, // 1 class name
        },
        "DELETE_CLIENT_CLASS6_DEPENDENCY",
        PGSQL_DELETE_CLIENT_CLASS_DEPENDENCY(dhcp6)
    },

    // Delete associations of a client class with server.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6_SERVER,
        1,
        {
            OID_VARCHAR // 1 class name
        },
        "DELETE_CLIENT_CLASS6_SERVER",
        PGSQL_DELETE_CLIENT_CLASS_SERVER(dhcp6),
    },

    // Delete all client classes.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_CLIENT_CLASSES6,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "DELETE_ALL_CLIENT_CLASSES6",
        PGSQL_DELETE_CLIENT_CLASS_WITH_TAG(dhcp6)
    },

    // Delete all unassigned client classes.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_CLIENT_CLASSES6_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "DELETE_ALL_CLIENT_CLASSES6_UNASSIGNED",
        PGSQL_DELETE_CLIENT_CLASS_UNASSIGNED(dhcp6)
    },

    // Delete specified client class.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_VARCHAR     // 2 name
        },
        "DELETE_CLIENT_CLASS6",
        PGSQL_DELETE_CLIENT_CLASS_WITH_TAG(dhcp6, AND name = $2)
    },

    // Delete any client class with a given name.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6_ANY,
        1,
        {
            OID_VARCHAR     // 1 name
        },
        "DELETE_CLIENT_CLASS6_ANY",
        PGSQL_DELETE_CLIENT_CLASS_ANY(dhcp6, AND name = $1)
    },

    // Delete a server by tag.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_SERVER6,
        1,
        {
            OID_VARCHAR // server_tag
        },
        "DELETE_SERVER6",
        PGSQL_DELETE_SERVER(dhcp6)
    },

    // Deletes all servers except logical server 'all'.
    {
        // PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SERVERS6,
        0,
        {
            OID_NONE
        },
        "DELETE_ALL_SERVERS6",
        PGSQL_DELETE_ALL_SERVERS(dhcp6)
    },

    // Fetches the last sequence id for the given table and column.
    {
        // PgSqlConfigBackendDHCPv6Impl::GET_LAST_INSERT_ID6,
        // args are: table name, sequence column name
        2,
        {
            OID_VARCHAR,
            OID_VARCHAR
        },
        "GET_LAST_INSERT_ID6",
        "SELECT CURRVAL(PG_GET_SERIAL_SEQUENCE($1, $2))"
    }
}
};

} // end anonymous namespace

PgSqlConfigBackendDHCPv6Impl::PgSqlConfigBackendDHCPv6Impl(const DatabaseConnection::ParameterMap& parameters)
    : PgSqlConfigBackendImpl(parameters, &PgSqlConfigBackendDHCPv6Impl::dbReconnect,
      PgSqlConfigBackendDHCPv6Impl::GET_LAST_INSERT_ID6) {
    // Prepare query statements. Those are will be only used to retrieve
    // information from the database, so they can be used even if the
    // database is read only for the current user.
    conn_.prepareStatements(tagged_statements.begin(),
                            tagged_statements.end());
// @todo As part of enabling read-only CB access, statements need to
// be limited:
//                            tagged_statements.begin() + WRITE_STMTS_BEGIN);

    // Create unique timer name per instance.
    timer_name_ = "PgSqlConfigBackend6[";
    timer_name_ += boost::lexical_cast<std::string>(reinterpret_cast<uint64_t>(this));
    timer_name_ += "]DbReconnectTimer";

    // Create ReconnectCtl for this connection.
    conn_.makeReconnectCtl(timer_name_);
}

PgSqlConfigBackendDHCPv6Impl::~PgSqlConfigBackendDHCPv6Impl() {
}

PgSqlTaggedStatement&
PgSqlConfigBackendDHCPv6Impl::getStatement(size_t index) const {
    if (index >= tagged_statements.size()) {
        isc_throw(BadValue, "PgSqlConfigBackendDHCPv6Impl::getStatement index: "
                  << index << ", is invalid");
    }

    return(tagged_statements[index]);
}

PgSqlConfigBackendDHCPv6::PgSqlConfigBackendDHCPv6(const DatabaseConnection::ParameterMap& parameters)
    : impl_(new PgSqlConfigBackendDHCPv6Impl(parameters)), base_impl_(impl_) {
}

bool
PgSqlConfigBackendDHCPv6::isUnusable() {
    return (impl_->conn_.isUnusable());
}

DatabaseConnection::ParameterMap
PgSqlConfigBackendDHCPv6::getParameters() const {
    return (impl_->getParameters());
}

Subnet6Ptr
PgSqlConfigBackendDHCPv6::getSubnet6(const ServerSelector& server_selector,
                                     const std::string& subnet_prefix) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SUBNET6_BY_PREFIX)
        .arg(subnet_prefix);
    return (impl_->getSubnet6(server_selector, subnet_prefix));
}

Subnet6Ptr
PgSqlConfigBackendDHCPv6::getSubnet6(const ServerSelector& server_selector,
                                     const SubnetID& subnet_id) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SUBNET6_BY_SUBNET_ID)
        .arg(subnet_id);
    return (impl_->getSubnet6(server_selector, subnet_id));
}

Subnet6Collection
PgSqlConfigBackendDHCPv6::getAllSubnets6(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SUBNETS6);
    Subnet6Collection subnets;
    impl_->getAllSubnets6(server_selector, subnets);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SUBNETS6_RESULT)
        .arg(subnets.size());
    return (subnets);
}

Subnet6Collection
PgSqlConfigBackendDHCPv6::getModifiedSubnets6(const ServerSelector& server_selector,
                                              const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SUBNETS6)
        .arg(util::ptimeToText(modification_time));
    Subnet6Collection subnets;
    impl_->getModifiedSubnets6(server_selector, modification_time, subnets);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SUBNETS6_RESULT)
        .arg(subnets.size());
    return (subnets);
}

Subnet6Collection
PgSqlConfigBackendDHCPv6::getSharedNetworkSubnets6(const ServerSelector& /* server_selector */,
                                                   const std::string& shared_network_name) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SHARED_NETWORK_SUBNETS6)
        .arg(shared_network_name);
    Subnet6Collection subnets;
    impl_->getSharedNetworkSubnets6(ServerSelector::ANY(), shared_network_name, subnets);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SHARED_NETWORK_SUBNETS6_RESULT)
        .arg(subnets.size());
    return (subnets);
}

SharedNetwork6Ptr
PgSqlConfigBackendDHCPv6::getSharedNetwork6(const ServerSelector& server_selector,
                                            const std::string& name) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SHARED_NETWORK6)
        .arg(name);
    return (impl_->getSharedNetwork6(server_selector, name));
}

SharedNetwork6Collection
PgSqlConfigBackendDHCPv6::getAllSharedNetworks6(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SHARED_NETWORKS6);
    SharedNetwork6Collection shared_networks;
    impl_->getAllSharedNetworks6(server_selector, shared_networks);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SHARED_NETWORKS6_RESULT)
        .arg(shared_networks.size());
    return (shared_networks);
}

SharedNetwork6Collection
PgSqlConfigBackendDHCPv6::getModifiedSharedNetworks6(const ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS6)
        .arg(util::ptimeToText(modification_time));
    SharedNetwork6Collection shared_networks;
    impl_->getModifiedSharedNetworks6(server_selector, modification_time, shared_networks);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS6_RESULT)
        .arg(shared_networks.size());
    return (shared_networks);
}

OptionDefinitionPtr
PgSqlConfigBackendDHCPv6::getOptionDef6(const ServerSelector& server_selector,
                                        const uint16_t code,
                                        const std::string& space) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_OPTION_DEF6)
        .arg(code).arg(space);
    return (impl_->getOptionDef(PgSqlConfigBackendDHCPv6Impl::GET_OPTION_DEF6_CODE_SPACE,
                                server_selector, code, space));
}

OptionDefContainer
PgSqlConfigBackendDHCPv6::getAllOptionDefs6(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTION_DEFS6);
    OptionDefContainer option_defs;
    impl_->getAllOptionDefs(PgSqlConfigBackendDHCPv6Impl::GET_ALL_OPTION_DEFS6,
                            server_selector, option_defs);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTION_DEFS6_RESULT)
        .arg(option_defs.size());
    return (option_defs);
}

OptionDefContainer
PgSqlConfigBackendDHCPv6::getModifiedOptionDefs6(const ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTION_DEFS6)
        .arg(util::ptimeToText(modification_time));
    OptionDefContainer option_defs;
    impl_->getModifiedOptionDefs(PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_OPTION_DEFS6,
                                 server_selector, modification_time, option_defs);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTION_DEFS6_RESULT)
        .arg(option_defs.size());
    return (option_defs);
}

OptionDescriptorPtr
PgSqlConfigBackendDHCPv6::getOption6(const ServerSelector& server_selector,
                                     const uint16_t code,
                                     const std::string& space) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_OPTION6)
        .arg(code).arg(space);
    return (impl_->getOption(PgSqlConfigBackendDHCPv6Impl::GET_OPTION6_CODE_SPACE,
                             Option::V6, server_selector, code, space));
}

OptionContainer
PgSqlConfigBackendDHCPv6::getAllOptions6(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTIONS6);
    OptionContainer options = impl_->getAllOptions(PgSqlConfigBackendDHCPv6Impl::GET_ALL_OPTIONS6,
            Option::V6, server_selector);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTIONS6_RESULT)
        .arg(options.size());
    return (options);
}

OptionContainer
PgSqlConfigBackendDHCPv6::getModifiedOptions6(const ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTIONS6)
        .arg(util::ptimeToText(modification_time));
    OptionContainer options = impl_->getModifiedOptions(PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_OPTIONS6,
            Option::V6, server_selector, modification_time);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTIONS6_RESULT)
        .arg(options.size());
    return (options);
}

StampedValuePtr
PgSqlConfigBackendDHCPv6::getGlobalParameter6(const ServerSelector& server_selector,
                                              const std::string& name) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_GLOBAL_PARAMETER6)
        .arg(name);
    return (impl_->getGlobalParameter6(server_selector, name));
}

StampedValueCollection
PgSqlConfigBackendDHCPv6::getAllGlobalParameters6(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS6);
    StampedValueCollection parameters;
    auto const& tags = server_selector.getTags();
    for (auto const& tag : tags) {
        PsqlBindArray in_bindings;
        in_bindings.addTempString(tag.get());
        impl_->getGlobalParameters(PgSqlConfigBackendDHCPv6Impl::GET_ALL_GLOBAL_PARAMETERS6,
                                   in_bindings, parameters);
    }
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS6_RESULT)
        .arg(parameters.size());
    return (parameters);
}

StampedValueCollection
PgSqlConfigBackendDHCPv6::getModifiedGlobalParameters6(const db::ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6)
        .arg(util::ptimeToText(modification_time));
    StampedValueCollection parameters;
    auto const& tags = server_selector.getTags();
    for (auto const& tag : tags) {
        PsqlBindArray in_bindings;
        in_bindings.addTempString(tag.get());
        in_bindings.addTimestamp(modification_time);

        impl_->getGlobalParameters(PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_GLOBAL_PARAMETERS6,
                                   in_bindings, parameters);
    }
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6_RESULT)
        .arg(parameters.size());
    return (parameters);
}

ClientClassDefPtr
PgSqlConfigBackendDHCPv6::getClientClass6(const db::ServerSelector& server_selector,
                                          const std::string& name) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_CLIENT_CLASS6)
        .arg(name);
    return (impl_->getClientClass6(server_selector, name));
}

ClientClassDictionary
PgSqlConfigBackendDHCPv6::getAllClientClasses6(const db::ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_CLIENT_CLASSES6);
    ClientClassDictionary client_classes;
    impl_->getAllClientClasses6(server_selector, client_classes);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_CLIENT_CLASSES6_RESULT)
        .arg(client_classes.getClasses()->size());
    return (client_classes);
}

ClientClassDictionary
PgSqlConfigBackendDHCPv6::getModifiedClientClasses6(const db::ServerSelector& server_selector,
                                                    const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES6)
        .arg(util::ptimeToText(modification_time));
    ClientClassDictionary client_classes;
    impl_->getModifiedClientClasses6(server_selector, modification_time, client_classes);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES6_RESULT)
        .arg(client_classes.getClasses()->size());
    return (client_classes);
}

AuditEntryCollection
PgSqlConfigBackendDHCPv6::getRecentAuditEntries(const db::ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time,
        const uint64_t& modification_id) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_RECENT_AUDIT_ENTRIES6)
      .arg(util::ptimeToText(modification_time))
      .arg(modification_id);
    AuditEntryCollection audit_entries;
    impl_->getRecentAuditEntries(PgSqlConfigBackendDHCPv6Impl::GET_AUDIT_ENTRIES6_TIME,
                                 server_selector, modification_time,
                                 modification_id, audit_entries);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_RECENT_AUDIT_ENTRIES6_RESULT)
        .arg(audit_entries.size());
    return (audit_entries);
}

ServerCollection
PgSqlConfigBackendDHCPv6::getAllServers6() const {
    ServerCollection servers;

    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SERVERS6);
    impl_->getAllServers(PgSqlConfigBackendDHCPv6Impl::GET_ALL_SERVERS6,
                         servers);

    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SERVERS6_RESULT)
        .arg(servers.size());
    return (servers);
}

ServerPtr
PgSqlConfigBackendDHCPv6::getServer6(const data::ServerTag& server_tag) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SERVER6)
        .arg(server_tag.get());
    return (impl_->getServer(PgSqlConfigBackendDHCPv6Impl::GET_SERVER6, server_tag));
}

void
PgSqlConfigBackendDHCPv6::createUpdateSubnet6(const ServerSelector& server_selector,
                                              const Subnet6Ptr& subnet) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SUBNET6)
        .arg(subnet);
    impl_->createUpdateSubnet6(server_selector, subnet);
}

void
PgSqlConfigBackendDHCPv6::createUpdateSharedNetwork6(const ServerSelector& server_selector,
                                                     const SharedNetwork6Ptr& shared_network) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK6)
        .arg(shared_network->getName());
    impl_->createUpdateSharedNetwork6(server_selector, shared_network);
}

void
PgSqlConfigBackendDHCPv6::createUpdateOptionDef6(const ServerSelector& server_selector,
                                                 const OptionDefinitionPtr& option_def) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_OPTION_DEF6)
        .arg(option_def->getName()).arg(option_def->getCode());
    impl_->createUpdateOptionDef6(server_selector, option_def);
}

void
PgSqlConfigBackendDHCPv6::createUpdateOption6(const ServerSelector& server_selector,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_OPTION6);
    impl_->createUpdateOption6(server_selector, option);
}

void
PgSqlConfigBackendDHCPv6::createUpdateOption6(const db::ServerSelector& server_selector,
                                              const std::string& shared_network_name,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION6)
        .arg(shared_network_name);
    impl_->createUpdateOption6(server_selector, shared_network_name, option, false);
}

void
PgSqlConfigBackendDHCPv6::createUpdateOption6(const ServerSelector& server_selector,
                                              const SubnetID& subnet_id,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION6)
        .arg(subnet_id);
    impl_->createUpdateOption6(server_selector, subnet_id, option, false);
}

void
PgSqlConfigBackendDHCPv6::createUpdateOption6(const ServerSelector& server_selector,
                                              const asiolink::IOAddress& pool_start_address,
                                              const asiolink::IOAddress& pool_end_address,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_BY_POOL_OPTION6)
        .arg(pool_start_address.toText()).arg(pool_end_address.toText());
    impl_->createUpdateOption6(server_selector, pool_start_address, pool_end_address,
                               option);
}

void
PgSqlConfigBackendDHCPv6::createUpdateOption6(const ServerSelector& server_selector,
                                              const asiolink::IOAddress& pd_pool_prefix,
                                              const uint8_t pd_pool_prefix_length,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_BY_PREFIX_OPTION6)
        .arg(pd_pool_prefix.toText()).arg(pd_pool_prefix_length);
    impl_->createUpdateOption6(server_selector, pd_pool_prefix,
                               pd_pool_prefix_length, option);
}

void
PgSqlConfigBackendDHCPv6::createUpdateGlobalParameter6(const ServerSelector& server_selector,
                                                       const StampedValuePtr& value) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER6)
        .arg(value->getName());
    impl_->createUpdateGlobalParameter6(server_selector, value);
}

void
PgSqlConfigBackendDHCPv6::createUpdateClientClass6(const db::ServerSelector& server_selector,
                                                   const ClientClassDefPtr& client_class,
                                                   const std::string& follow_class_name) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_CLIENT_CLASS6)
        .arg(client_class->getName());
    impl_->createUpdateClientClass6(server_selector, client_class, follow_class_name);
}

void
PgSqlConfigBackendDHCPv6::createUpdateServer6(const ServerPtr& server) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SERVER6)
        .arg(server->getServerTagAsText());
    impl_->createUpdateServer(PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                              PgSqlConfigBackendDHCPv6Impl::INSERT_SERVER6,
                              PgSqlConfigBackendDHCPv6Impl::UPDATE_SERVER6,
                              server);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteSubnet6(const ServerSelector& server_selector,
                                        const std::string& subnet_prefix) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_PREFIX_SUBNET6)
        .arg(subnet_prefix);
    uint64_t result = impl_->deleteSubnet6(server_selector, subnet_prefix);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_PREFIX_SUBNET6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteSubnet6(const ServerSelector& server_selector,
                                        const SubnetID& subnet_id) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET6)
        .arg(subnet_id);
    uint64_t result = impl_->deleteSubnet6(server_selector, subnet_id);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteAllSubnets6(const ServerSelector& server_selector) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SUBNETS6);

    int index = (server_selector.amUnassigned() ?
                 PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6_UNASSIGNED :
                 PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6);
    uint64_t result = impl_->deleteTransactional(index, server_selector, "deleting all subnets",
                                                 "deleted all subnets", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SUBNETS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteSharedNetworkSubnets6(const db::ServerSelector& server_selector,
                                                      const std::string& shared_network_name) {
    if (!server_selector.amAny()) {
        isc_throw(InvalidOperation, "deleting all subnets from a shared "
                  "network requires using ANY server selector");
    }
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS6)
        .arg(shared_network_name);
    uint64_t result = impl_->deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6_SHARED_NETWORK_NAME,
                                                 server_selector,
                                                 "deleting all subnets for a shared network",
                                                 "deleted all subnets for a shared network",
                                                 true, shared_network_name);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteSharedNetwork6(const ServerSelector& server_selector,
                                               const std::string& name) {
    /// @todo Using UNASSIGNED selector is allowed by the CB API but we don't have
    /// dedicated query for this at the moment. The user should use ANY to delete
    /// the shared network by name.
    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "deleting an unassigned shared network requires "
                  "an explicit server tag or using ANY server. The UNASSIGNED server "
                  "selector is currently not supported");
    }

    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK6)
        .arg(name);

    int index = (server_selector.amAny() ?
                 PgSqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_NAME_ANY :
                 PgSqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_NAME_WITH_TAG);
    uint64_t result = impl_->deleteTransactional(index, server_selector,
                                                 "deleting a shared network",
                                                 "shared network deleted", true, name);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteAllSharedNetworks6(const ServerSelector& server_selector) {
    if (server_selector.amAny()) {
        isc_throw(InvalidOperation, "deleting all shared networks for ANY server is not"
                  " supported");
    }

    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SHARED_NETWORKS6);

    int index = (server_selector.amUnassigned() ?
                 PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SHARED_NETWORKS6_UNASSIGNED :
                 PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SHARED_NETWORKS6);
    uint64_t result = impl_->deleteTransactional(index, server_selector, "deleting all shared networks",
                                                 "deleted all shared networks", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SHARED_NETWORKS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteOptionDef6(const ServerSelector& server_selector,
                                           const uint16_t code,
                                           const std::string& space) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION_DEF6)
        .arg(code).arg(space);
    uint64_t result = impl_->deleteOptionDef6(server_selector, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION_DEF6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteAllOptionDefs6(const ServerSelector& server_selector) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_OPTION_DEFS6);
    uint64_t result = impl_->deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_OPTION_DEFS6,
                                                 server_selector, "deleting all option definitions",
                                                 "deleted all option definitions", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_OPTION_DEFS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteOption6(const ServerSelector& server_selector,
                                        const uint16_t code,
                                        const std::string& space) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION6)
        .arg(code).arg(space);
    uint64_t result = impl_->deleteOption6(server_selector, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteOption6(const ServerSelector& /* server_selector */,
                                        const std::string& shared_network_name,
                                        const uint16_t code,
                                        const std::string& space) {
    /// @todo In the future we might use the server selector to make sure that the
    /// option is only deleted if the pool belongs to a given server. For now, we
    /// just delete it when there is a match with the parent object.
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_OPTION6)
        .arg(shared_network_name).arg(code).arg(space);
    uint64_t result = impl_->deleteOption6(ServerSelector::ANY(), shared_network_name,
                                           code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_OPTION6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteOption6(const ServerSelector& /* server_selector */,
                                        const SubnetID& subnet_id,
                                        const uint16_t code,
                                        const std::string& space) {
    /// @todo In the future we might use the server selector to make sure that the
    /// option is only deleted if the pool belongs to a given server. For now, we
    /// just delete it when there is a match with the parent object.
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION6)
        .arg(subnet_id).arg(code).arg(space);
    uint64_t result = impl_->deleteOption6(ServerSelector::ANY(), subnet_id, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteOption6(const ServerSelector& /* server_selector */,
                                        const asiolink::IOAddress& pool_start_address,
                                        const asiolink::IOAddress& pool_end_address,
                                        const uint16_t code,
                                        const std::string& space) {
    /// @todo In the future we might use the server selector to make sure that the
    /// option is only deleted if the pool belongs to a given server. For now, we
    /// just delete it when there is a match with the parent object.
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_POOL_OPTION6)
        .arg(pool_start_address.toText()).arg(pool_end_address.toText()).arg(code).arg(space);
    uint64_t result = impl_->deleteOption6(ServerSelector::ANY(), pool_start_address,
                                           pool_end_address, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_POOL_OPTION6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteOption6(const ServerSelector& /* server_selector */,
                                        const asiolink::IOAddress& pd_pool_prefix,
                                        const uint8_t pd_pool_prefix_length,
                                        const uint16_t code,
                                        const std::string& space) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_POOL_PREFIX_OPTION6)
        .arg(pd_pool_prefix.toText()).arg(pd_pool_prefix_length).arg(code).arg(space);
    uint64_t result = impl_->deleteOption6(ServerSelector::ANY(), pd_pool_prefix,
                                           pd_pool_prefix_length, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_POOL_PREFIX_OPTION6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteGlobalParameter6(const ServerSelector& server_selector,
                                                 const std::string& name) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_GLOBAL_PARAMETER6)
        .arg(name);
    uint64_t result = impl_->deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_GLOBAL_PARAMETER6,
                                                 server_selector, "deleting global parameter",
                                                 "global parameter deleted", false, name);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_GLOBAL_PARAMETER6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteAllGlobalParameters6(const ServerSelector& server_selector) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS6);
    uint64_t result = impl_->deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_GLOBAL_PARAMETERS6,
                                                 server_selector, "deleting all global parameters",
                                                 "all global parameters deleted", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteClientClass6(const db::ServerSelector& server_selector,
                                             const std::string& name) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_CLIENT_CLASS6)
        .arg(name);
    auto result = impl_->deleteClientClass6(server_selector, name);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_CLIENT_CLASS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteAllClientClasses6(const db::ServerSelector& server_selector) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_CLIENT_CLASSES6);

    int index = (server_selector.amUnassigned() ?
                 PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_CLIENT_CLASSES6_UNASSIGNED :
                 PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_CLIENT_CLASSES6);
    uint64_t result = impl_->deleteTransactional(index, server_selector, "deleting all client classes",
                                                 "deleted all client classes", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_CLIENT_CLASSES6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteServer6(const ServerTag& server_tag) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SERVER6)
        .arg(server_tag.get());
    uint64_t result = impl_->deleteServer6(server_tag);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SERVER6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteAllServers6() {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SERVERS6);
    uint64_t result = impl_->deleteAllServers6();
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SERVERS6_RESULT)
        .arg(result);
    return (result);
}

std::string
PgSqlConfigBackendDHCPv6::getType() const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_TYPE6);
    return (impl_->getType());
}

std::string
PgSqlConfigBackendDHCPv6::getHost() const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_HOST6);
    return (impl_->getHost());
}

uint16_t
PgSqlConfigBackendDHCPv6::getPort() const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_PORT6);
    return (impl_->getPort());
}

bool
PgSqlConfigBackendDHCPv6::registerBackendType() {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_REGISTER_BACKEND_TYPE6);
    return (
        dhcp::ConfigBackendDHCPv6Mgr::instance().registerBackendFactory("postgresql",
            [](const db::DatabaseConnection::ParameterMap& params) -> dhcp::ConfigBackendDHCPv6Ptr {
            return (dhcp::PgSqlConfigBackendDHCPv6Ptr(new dhcp::PgSqlConfigBackendDHCPv6(params)));
        })
    );
}

void
PgSqlConfigBackendDHCPv6::unregisterBackendType() {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_UNREGISTER_BACKEND_TYPE6);
    dhcp::ConfigBackendDHCPv6Mgr::instance().unregisterBackendFactory("postgresql");
}

} // end of namespace isc::dhcp
} // end of namespace isc
