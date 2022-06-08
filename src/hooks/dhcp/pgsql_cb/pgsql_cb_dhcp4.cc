// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <pgsql_cb_dhcp4.h>
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
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <dhcpsrv/network.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/timer_mgr.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <util/buffer.h>
#include <util/boost_time_utils.h>
#include <util/multi_threading_mgr.h>
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
class PgSqlConfigBackendDHCPv4Impl : public PgSqlConfigBackendImpl {
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
        GET_GLOBAL_PARAMETER4,
        GET_ALL_GLOBAL_PARAMETERS4,
        GET_MODIFIED_GLOBAL_PARAMETERS4,
        GET_SUBNET4_ID_NO_TAG,
        GET_SUBNET4_ID_ANY,
        GET_SUBNET4_ID_UNASSIGNED,
        GET_SUBNET4_PREFIX_NO_TAG,
        GET_SUBNET4_PREFIX_ANY,
        GET_SUBNET4_PREFIX_UNASSIGNED,
        GET_ALL_SUBNETS4,
        GET_ALL_SUBNETS4_UNASSIGNED,
        GET_MODIFIED_SUBNETS4,
        GET_MODIFIED_SUBNETS4_UNASSIGNED,
        GET_SHARED_NETWORK_SUBNETS4,
        GET_POOL4_RANGE,
        GET_POOL4_RANGE_ANY,
        GET_SHARED_NETWORK4_NAME_NO_TAG,
        GET_SHARED_NETWORK4_NAME_ANY,
        GET_SHARED_NETWORK4_NAME_UNASSIGNED,
        GET_ALL_SHARED_NETWORKS4,
        GET_ALL_SHARED_NETWORKS4_UNASSIGNED,
        GET_MODIFIED_SHARED_NETWORKS4,
        GET_MODIFIED_SHARED_NETWORKS4_UNASSIGNED,
        GET_OPTION_DEF4_CODE_SPACE,
        GET_ALL_OPTION_DEFS4,
        GET_MODIFIED_OPTION_DEFS4,
        GET_OPTION4_CODE_SPACE,
        GET_ALL_OPTIONS4,
        GET_MODIFIED_OPTIONS4,
        GET_OPTION4_SUBNET_ID_CODE_SPACE,
        GET_OPTION4_POOL_ID_CODE_SPACE,
        GET_OPTION4_SHARED_NETWORK_CODE_SPACE,
        GET_CLIENT_CLASS4_NAME,
        GET_ALL_CLIENT_CLASSES4,
        GET_ALL_CLIENT_CLASSES4_UNASSIGNED,
        GET_MODIFIED_CLIENT_CLASSES4,
        GET_MODIFIED_CLIENT_CLASSES4_UNASSIGNED,
        GET_AUDIT_ENTRIES4_TIME,
        GET_SERVER4,
        GET_ALL_SERVERS4,
        INSERT_GLOBAL_PARAMETER4,
        INSERT_GLOBAL_PARAMETER4_SERVER,
        INSERT_SUBNET4,
        INSERT_SUBNET4_SERVER,
        INSERT_POOL4,
        INSERT_SHARED_NETWORK4,
        INSERT_SHARED_NETWORK4_SERVER,
        INSERT_OPTION_DEF4,
        INSERT_OPTION_DEF4_CLIENT_CLASS,
        INSERT_OPTION_DEF4_SERVER,
        INSERT_OPTION4,
        INSERT_OPTION4_SERVER,
        INSERT_CLIENT_CLASS4,
        INSERT_CLIENT_CLASS4_SERVER,
        INSERT_CLIENT_CLASS4_DEPENDENCY,
        INSERT_SERVER4,
        UPDATE_GLOBAL_PARAMETER4,
        UPDATE_SUBNET4,
        UPDATE_SHARED_NETWORK4,
        UPDATE_OPTION_DEF4,
        UPDATE_OPTION_DEF4_CLIENT_CLASS,
        UPDATE_OPTION4,
        UPDATE_OPTION4_SUBNET_ID,
        UPDATE_OPTION4_POOL_ID,
        UPDATE_OPTION4_SHARED_NETWORK,
        UPDATE_OPTION4_CLIENT_CLASS,
        UPDATE_CLIENT_CLASS4,
        UPDATE_CLIENT_CLASS4_SAME_POSITION,
        UPDATE_SERVER4,
        DELETE_GLOBAL_PARAMETER4,
        DELETE_ALL_GLOBAL_PARAMETERS4,
        DELETE_ALL_GLOBAL_PARAMETERS4_UNASSIGNED,
        DELETE_SUBNET4_ID_WITH_TAG,
        DELETE_SUBNET4_ID_ANY,
        DELETE_SUBNET4_PREFIX_WITH_TAG,
        DELETE_SUBNET4_PREFIX_ANY,
        DELETE_ALL_SUBNETS4,
        DELETE_ALL_SUBNETS4_UNASSIGNED,
        DELETE_ALL_SUBNETS4_SHARED_NETWORK_NAME,
        DELETE_SUBNET4_SERVER,
        DELETE_POOLS4,
        DELETE_SHARED_NETWORK4_NAME_WITH_TAG,
        DELETE_SHARED_NETWORK4_NAME_ANY,
        DELETE_ALL_SHARED_NETWORKS4,
        DELETE_ALL_SHARED_NETWORKS4_UNASSIGNED,
        DELETE_SHARED_NETWORK4_SERVER,
        DELETE_OPTION_DEF4_CODE_NAME,
        DELETE_ALL_OPTION_DEFS4,
        DELETE_ALL_OPTION_DEFS4_UNASSIGNED,
        DELETE_OPTION_DEFS4_CLIENT_CLASS,
        DELETE_OPTION4,
        DELETE_ALL_GLOBAL_OPTIONS4_UNASSIGNED,
        DELETE_OPTION4_SUBNET_ID,
        DELETE_OPTION4_POOL_RANGE,
        DELETE_OPTION4_SHARED_NETWORK,
        DELETE_OPTIONS4_SUBNET_ID_PREFIX,
        DELETE_OPTIONS4_SHARED_NETWORK,
        DELETE_OPTIONS4_CLIENT_CLASS,
        DELETE_CLIENT_CLASS4_DEPENDENCY,
        DELETE_CLIENT_CLASS4_SERVER,
        DELETE_ALL_CLIENT_CLASSES4,
        DELETE_ALL_CLIENT_CLASSES4_UNASSIGNED,
        DELETE_CLIENT_CLASS4,
        DELETE_CLIENT_CLASS4_ANY,
        DELETE_SERVER4,
        DELETE_ALL_SERVERS4,
        GET_LAST_INSERT_ID4,
        NUM_STATEMENTS
    };

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    explicit PgSqlConfigBackendDHCPv4Impl(const DatabaseConnection::ParameterMap&
                                          parameters);

    /// @brief Destructor.
    ~PgSqlConfigBackendDHCPv4Impl();

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
    StampedValuePtr getGlobalParameter4(const ServerSelector& server_selector,
                                        const std::string& name) {
        StampedValueCollection parameters;

        auto const& tags = server_selector.getTags();
        for (auto const& tag : tags) {
            PsqlBindArray in_bindings;
            in_bindings.addTempString(tag.get());
            in_bindings.add(name);

            getGlobalParameters(GET_GLOBAL_PARAMETER4, in_bindings, parameters);
        }

        return (parameters.empty() ? StampedValuePtr() : *parameters.begin());
    }

    /// @brief Sends query to insert or update global parameter.
    ///
    /// @param server_selector Server selector.
    /// @param value StampedValue describing the parameter to create/update.
    void createUpdateGlobalParameter4(const db::ServerSelector& server_selector,
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
                                           PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                                           server_selector, "global parameter set",
                                           false);

        // Try to update the existing row.
        if (updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::UPDATE_GLOBAL_PARAMETER4,
                              in_bindings) == 0) {
            // No such parameter found, so let's insert it. We have to adjust the
            // bindings collection to match the prepared statement for insert.
            in_bindings.popBack();
            in_bindings.popBack();

            insertQuery(PgSqlConfigBackendDHCPv4Impl::INSERT_GLOBAL_PARAMETER4,
                        in_bindings);

            // Successfully inserted global parameter. Now, we have to associate it
            // with the server tag.
            PsqlBindArray attach_bindings;
            uint64_t pid = getLastInsertId("dhcp4_global_parameter", "id");
            attach_bindings.add(pid);   // id of newly inserted global.
            attach_bindings.addTimestamp(value->getModificationTime());
            attachElementToServers(PgSqlConfigBackendDHCPv4Impl::INSERT_GLOBAL_PARAMETER4_SERVER,
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
    void getSubnets4(const StatementIndex& index,
                     const ServerSelector& server_selector,
                     const PsqlBindArray& in_bindings,
                     Subnet4Collection& subnets) {
        uint64_t last_pool_id = 0;
        uint64_t last_pool_option_id = 0;
        uint64_t last_option_id = 0;
        Pool4Ptr last_pool;
        std::string last_tag;

        // Execute actual query.
        selectQuery(index, in_bindings,
                    [this, &subnets, &last_pool, &last_pool_id,
                     &last_pool_option_id, &last_option_id, &last_tag](PgSqlResult& r, int row) {
            // Create a convenience worker for the row.
            PgSqlResultRowWorker worker(r, row);

            // Get pointer to the last subnet in the collection.
            Subnet4Ptr last_subnet;
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
                last_pool_option_id = 0;
                last_option_id = 0;
                last_pool.reset();
                last_tag.clear();

                // Get subnet parameters required by the constructor first.

                // subnet_prefix at 1.
                std::string subnet_prefix = worker.getString(1);
                auto prefix_pair = Subnet4::parsePrefix(subnet_prefix);

                // renew_timer at 13.
                auto renew_timer = worker.getTriplet(13);

                // rebind_timer at 11.
                auto rebind_timer = worker.getTriplet(11);

                // valid_lifetime at 19.
                // min_valid_lifetime at 53.
                // max_valid_lifetime at 54.
                auto valid_lifetime = worker.getTriplet(19, 53, 54);

                // Create subnet with basic settings.
                last_subnet = Subnet4::create(prefix_pair.first, prefix_pair.second,
                                              renew_timer, rebind_timer,
                                              valid_lifetime, subnet_id);

                // Get other subnet parameters.
                // 4o6_interface at 2.
                if (!worker.isColumnNull(2)) {
                    last_subnet->get4o6().setIface4o6(worker.getString(2));
                }

                // 4o6_interface_id at 3.
                if (!worker.isColumnNull(3)) {
                    std::string dhcp4o6_interface_id = worker.getString(3);
                    OptionBuffer dhcp4o6_interface_id_buf(dhcp4o6_interface_id.begin(),
                                                          dhcp4o6_interface_id.end());
                    OptionPtr option_dhcp4o6_interface_id =
                        Option::create(Option::V6, D6O_INTERFACE_ID, dhcp4o6_interface_id_buf);
                    last_subnet->get4o6().setInterfaceId(option_dhcp4o6_interface_id);
                }

                // 4o6_subnet at 4.
                if (!worker.isColumnNull(4)) {
                    std::pair<IOAddress, uint8_t> dhcp4o6_subnet_prefix_pair =
                        Subnet6::parsePrefix(worker.getString(4));
                    last_subnet->get4o6().setSubnet4o6(dhcp4o6_subnet_prefix_pair.first,
                                                       dhcp4o6_subnet_prefix_pair.second);
                }

                // boot_file_name at 5.
                if (!worker.isColumnNull(5)) {
                    last_subnet->setFilename(worker.getString(5));
                }

                // client_class at 6.
                if (!worker.isColumnNull(6)) {
                    last_subnet->allowClientClass(worker.getString(6));
                }

                // interface at 7.
                if (!worker.isColumnNull(7)) {
                    last_subnet->setIface(worker.getString(7));
                }

                // match_client_id at 8.
                if (!worker.isColumnNull(8)) {
                    last_subnet->setMatchClientId(worker.getBool(8));
                }

                // modification_ts at 9.
                last_subnet->setModificationTime(worker.getTimestamp(9));

                // next_server at 10.
                if (!worker.isColumnNull(10)) {
                    last_subnet->setSiaddr(worker.getInet4(10));
                }

                // rebind_timer at 11 (fetched before subnet create).

                // Relay addresses at 12.
                setRelays(worker, 12, *last_subnet);

                // renew_timer at 13 (fetched before subnet create).

                // require_client_classes at 14.
                setRequiredClasses(worker, 14, [&last_subnet](const std::string& class_name) {
                    last_subnet->requireClientClass(class_name);
                });

                // reservations_global at 15.
                if (!worker.isColumnNull(15)) {
                    last_subnet->setReservationsGlobal(worker.getBool(15));
                }

                // server_hostname at 16.
                if (!worker.isColumnNull(16)) {
                    last_subnet->setSname(worker.getString(16));
                }

                // shared_network_name at 17.
                if (!worker.isColumnNull(17)) {
                    last_subnet->setSharedNetworkName(worker.getString(17));
                }

                // user_context at 18.
                if (!worker.isColumnNull(18)) {
                    ElementPtr user_context = worker.getJSON(18);
                    if (user_context) {
                        last_subnet->setContext(user_context);
                    }
                }

                // valid_lifetime at 19 (fetched before subnet create).

                // pool and option from 20 to 48.

                // calculate_tee_times at 49.
                if (!worker.isColumnNull(49)) {
                    last_subnet->setCalculateTeeTimes(worker.getBool(49));
                }

                // t1_percent at 50.
                if (!worker.isColumnNull(50)) {
                    last_subnet->setT1Percent(worker.getDouble(50));
                }

                // t2_percent at 51.
                if (!worker.isColumnNull(51)) {
                    last_subnet->setT2Percent(worker.getDouble(51));
                }

                // authoritative at 52.
                if (!worker.isColumnNull(52)) {
                    last_subnet->setAuthoritative(worker.getBool(52));
                }

                // min_valid_lifetime at 53 (fetched as part of triplet).
                // max_valid_lifetime at 54 (fetched as part of triplet).

                // pool client_class, require_client_classes and user_context
                // from 55 to 57.

                // ddns_send_updates at 58.
                if (!worker.isColumnNull(58)) {
                    last_subnet->setDdnsSendUpdates(worker.getBool(58));
                }

                // ddns_override_no_update at 59.
                if (!worker.isColumnNull(59)) {
                    last_subnet->setDdnsOverrideNoUpdate(worker.getBool(59));
                }

                // ddns_override_client_update at 60.
                if (!worker.isColumnNull(60)) {
                    last_subnet->setDdnsOverrideClientUpdate(worker.getBool(60));
                }

                // ddns_replace_client_name at 61.
                if (!worker.isColumnNull(61)) {
                    last_subnet->setDdnsReplaceClientNameMode(
                        static_cast<D2ClientConfig::ReplaceClientNameMode>(worker.getSmallInt(61)));
                }

                // ddns_generated_prefix at 62.
                if (!worker.isColumnNull(62)) {
                    last_subnet->setDdnsGeneratedPrefix(worker.getString(62));
                }

                // ddns_qualifying_suffix at 63.
                if (!worker.isColumnNull(63)) {
                    last_subnet->setDdnsQualifyingSuffix(worker.getString(63));
                }

                // reservations_in_subnet at 64.
                if (!worker.isColumnNull(64)) {
                    last_subnet->setReservationsInSubnet(worker.getBool(64));
                }

                // reservations_out_of_pool at 65.
                if (!worker.isColumnNull(65)) {
                    last_subnet->setReservationsOutOfPool(worker.getBool(65));
                }

                // cache_threshold at 66.
                if (!worker.isColumnNull(66)) {
                    last_subnet->setCacheThreshold(worker.getDouble(66));
                }

                // cache_max_age at 67.
                if (!worker.isColumnNull(67)) {
                    last_subnet->setCacheMaxAge(worker.getInt(67));
                }

                // server_tag at 68.

                // Subnet ready. Add it to the list.
                auto ret = subnets.insert(last_subnet);

                // subnets is a multi index container with unique indexes
                // but these indexes are unique too in the database,
                // so this is for sanity only.
                if (!ret.second) {
                    isc_throw(Unexpected, "add subnet failed");
                }
            }

            // Check for new server tags at 68.
            if (!worker.isColumnNull(68)) {
                std::string new_tag = worker.getString(68);
                if (last_tag != new_tag) {
                    if (!new_tag.empty() && !last_subnet->hasServerTag(ServerTag(new_tag))) {
                        last_subnet->setServerTag(new_tag);
                    }

                    last_tag = new_tag;
                }
            }

            // If the row contains information about the pool and it appears to be
            // new pool entry (checked by comparing pool id), let's create the new
            // pool and add it to the subnet.
            // pool id at 20.
            // pool start_address at 21.
            // pool end_address at 22.
            // pool subnet_id at 23 (ignored)
            // pool modification_ts at 24 (ignored)
            if (!worker.isColumnNull(20) &&
                (worker.getInet4(21) != 0) &&
                (worker.getInet4(22) != 0) &&
                (worker.getBigInt(20) > last_pool_id)) {
                last_pool_id = worker.getBigInt(20);
                last_pool = Pool4::create(IOAddress(worker.getInet4(21)),
                                          IOAddress(worker.getInet4(22)));

                // pool client_class at 55.
                if (!worker.isColumnNull(55)) {
                    last_pool->allowClientClass(worker.getString(55));
                }

                // pool require_client_classes at 56.
                setRequiredClasses(worker, 56, [&last_pool](const std::string& class_name) {
                    last_pool->requireClientClass(class_name);
                });

                // pool user_context at 57.
                if (!worker.isColumnNull(57)) {
                    ElementPtr user_context = worker.getJSON(57);
                    if (user_context) {
                        last_pool->setContext(user_context);
                    }
                }

                last_subnet->addPool(last_pool);
            }

            // Parse pool-specific option from 25 to 36.
            if (last_pool && !worker.isColumnNull(25) &&
                (last_pool_option_id < worker.getBigInt(25))) {
                last_pool_option_id = worker.getBigInt(25);

                OptionDescriptorPtr desc = processOptionRow(Option::V4, worker, 25);
                if (desc) {
                    last_pool->getCfgOption()->add(*desc, desc->space_name_);
                }
            }

            // Parse subnet-specific option from 37 to 48.
            if (!worker.isColumnNull(37) &&
                (last_option_id < worker.getBigInt(37))) {
                last_option_id = worker.getBigInt(37);

                OptionDescriptorPtr desc = processOptionRow(Option::V4, worker, 37);
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
    Subnet4Ptr getSubnet4(const ServerSelector& server_selector,
                          const SubnetID& subnet_id) {
        if (server_selector.hasMultipleTags()) {
            isc_throw(InvalidOperation, "expected one server tag to be specified"
                      " while fetching a subnet. Got: "
                      << getServerTagsAsText(server_selector));
        }

        PsqlBindArray in_bindings;
        in_bindings.add(subnet_id);

        auto index = GET_SUBNET4_ID_NO_TAG;
        if (server_selector.amUnassigned()) {
            index = GET_SUBNET4_ID_UNASSIGNED;
        } else if (server_selector.amAny()) {
            index = GET_SUBNET4_ID_ANY;
        }

        Subnet4Collection subnets;
        getSubnets4(index, server_selector, in_bindings, subnets);

        return (subnets.empty() ? Subnet4Ptr() : *subnets.begin());
    }

    /// @brief Sends query to retrieve single subnet by prefix.
    ///
    /// The prefix should be in the following format: "192.0.2.0/24".
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Pointer to the returned subnet or NULL if such subnet
    /// doesn't exist.
    Subnet4Ptr getSubnet4(const ServerSelector& server_selector,
                          const std::string& subnet_prefix) {
        if (server_selector.hasMultipleTags()) {
            isc_throw(InvalidOperation, "expected one server tag to be specified"
                      " while fetching a subnet. Got: "
                      << getServerTagsAsText(server_selector));
        }

        PsqlBindArray in_bindings;
        in_bindings.add(subnet_prefix);

        auto index = GET_SUBNET4_PREFIX_NO_TAG;
        if (server_selector.amUnassigned()) {
            index = GET_SUBNET4_PREFIX_UNASSIGNED;
        } else if (server_selector.amAny()) {
            index = GET_SUBNET4_PREFIX_ANY;
        }

        Subnet4Collection subnets;
        getSubnets4(index, server_selector, in_bindings, subnets);

        return (subnets.empty() ? Subnet4Ptr() : *subnets.begin());
    }

    /// @brief Sends query to retrieve all subnets.
    ///
    /// @param server_selector Server selector.
    /// @param [out] subnets Reference to the subnet collection structure where
    /// subnets should be inserted.
    void getAllSubnets4(const ServerSelector& server_selector,
                        Subnet4Collection& subnets) {
        if (server_selector.amAny()) {
            isc_throw(InvalidOperation, "fetching all subnets for ANY "
                      "server is not supported");
        }

        auto index = (server_selector.amUnassigned() ? GET_ALL_SUBNETS4_UNASSIGNED :
                      GET_ALL_SUBNETS4);
        PsqlBindArray in_bindings;
        getSubnets4(index, server_selector, in_bindings, subnets);
    }

    /// @brief Sends query to retrieve modified subnets.
    ///
    /// @param server_selector Server selector.
    /// @param modification_ts Lower bound modification timestamp.
    /// @param [out] subnets Reference to the subnet collection structure where
    /// subnets should be inserted.
    void getModifiedSubnets4(const ServerSelector& server_selector,
                             const boost::posix_time::ptime& modification_ts,
                             Subnet4Collection& subnets) {
        if (server_selector.amAny()) {
            isc_throw(InvalidOperation, "fetching modified subnets for ANY "
                      "server is not supported");
        }

        PsqlBindArray in_bindings;
        in_bindings.addTimestamp(modification_ts);

        auto index = (server_selector.amUnassigned() ? GET_MODIFIED_SUBNETS4_UNASSIGNED :
                      GET_MODIFIED_SUBNETS4);
        getSubnets4(index, server_selector, in_bindings, subnets);
    }

    /// @brief Sends query to retrieve all subnets belonging to a shared network.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of the shared network for which the
    /// subnets should be retrieved.
    /// @param [out] subnets Reference to the subnet collection structure where
    /// subnets should be inserted.
    void getSharedNetworkSubnets4(const ServerSelector& server_selector,
                                  const std::string& shared_network_name,
                                  Subnet4Collection& subnets) {
        PsqlBindArray in_bindings;
        in_bindings.add(shared_network_name);
        getSubnets4(GET_SHARED_NETWORK_SUBNETS4, server_selector, in_bindings, subnets);
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
        Pool4Ptr last_pool;

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

                last_pool = Pool4::create(worker.getInet4(1), worker.getInet4(2));

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

                OptionDescriptorPtr desc = processOptionRow(Option::V4, worker, 8);
                if (desc) {
                    last_pool->getCfgOption()->add(*desc, desc->space_name_);
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
    Pool4Ptr getPool4(const ServerSelector& server_selector,
                      const IOAddress& pool_start_address,
                      const IOAddress& pool_end_address,
                      uint64_t& pool_id) {
        PoolCollection pools;
        std::vector<uint64_t> pool_ids;

        if (server_selector.amAny()) {
            PsqlBindArray in_bindings;
            in_bindings.addInet4(pool_start_address);
            in_bindings.addInet4(pool_end_address);
            getPools(GET_POOL4_RANGE_ANY, in_bindings, pools, pool_ids);
        } else {
            auto const& tags = server_selector.getTags();
            for (auto const& tag : tags) {
                PsqlBindArray in_bindings;
                in_bindings.addTempString(tag.get());
                in_bindings.addInet4(pool_start_address);
                in_bindings.addInet4(pool_end_address);

                getPools(GET_POOL4_RANGE, in_bindings, pools, pool_ids);
                // Break if something is found?
            }
        }

        // Return upon the first pool found.
        if (!pools.empty()) {
            pool_id = pool_ids[0];
            return (boost::dynamic_pointer_cast<Pool4>(*pools.begin()));
        }

        pool_id = 0;

        return (Pool4Ptr());
    }

    /// @brief Sends query to insert or update subnet.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Pointer to the subnet to be inserted or updated.
    void createUpdateSubnet4(const ServerSelector& server_selector,
                             const Subnet4Ptr& subnet) {
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
        in_bindings.addOptional(subnet->get4o6().getIface4o6());

        // Convert DHCPv4o6 interface id to text.
        OptionPtr dhcp4o6_interface_id = subnet->get4o6().getInterfaceId();
        if (dhcp4o6_interface_id) {
            in_bindings.addTempString(std::string(dhcp4o6_interface_id->getData().begin(),
                                                  dhcp4o6_interface_id->getData().end()));

        } else {
            in_bindings.addNull();
        }

        // Convert DHCPv4o6 subnet to text.
        Optional<std::string> dhcp4o6_subnet;
        if (!subnet->get4o6().getSubnet4o6().unspecified() &&
            (!subnet->get4o6().getSubnet4o6().get().first.isV6Zero() ||
             (subnet->get4o6().getSubnet4o6().get().second != 128u))) {
            std::ostringstream s;
            s << subnet->get4o6().getSubnet4o6().get().first << "/"
              << static_cast<int>(subnet->get4o6().getSubnet4o6().get().second);
            dhcp4o6_subnet = s.str();
        }

        in_bindings.addOptional(dhcp4o6_subnet);

        in_bindings.addOptional(subnet->getFilename(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getClientClass(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getIface(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getMatchClientId(Network::Inheritance::NONE));
        in_bindings.addTimestamp(subnet->getModificationTime());
        in_bindings.addOptionalInet4(subnet->getSiaddr(Network::Inheritance::NONE));
        in_bindings.add(subnet->getT2(Network::Inheritance::NONE));
        addRelayBinding(in_bindings, subnet);
        in_bindings.add(subnet->getT1(Network::Inheritance::NONE));
        addRequiredClassesBinding(in_bindings, subnet);
        in_bindings.addOptional(subnet->getReservationsGlobal(Network::Inheritance::NONE));
        in_bindings.addOptional(subnet->getSname(Network::Inheritance::NONE));

        // Add shared network.
        SharedNetwork4Ptr shared_network;
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
        in_bindings.addOptional(subnet->getAuthoritative(Network::Inheritance::NONE));
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
                                           PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                                           server_selector, "subnet set", true);

        // Create a savepoint in case we are called as part of larger
        // transaction.
        conn_.createSavepoint("createUpdateSubnet4");

        try {

            insertQuery(PgSqlConfigBackendDHCPv4Impl::INSERT_SUBNET4, in_bindings);

        } catch (const DuplicateEntry&) {
            // It already exists, rollback to the savepoint to preserve
            // any prior work.
            conn_.rollbackToSavepoint("createUpdateSubnet4");

            // We're updating, so we need to remove any existing pools and options.
            deletePools4(subnet);
            deleteOptions4(ServerSelector::ANY(), subnet);

            // Now we need to add two more bindings for WHERE clause.
            in_bindings.add(subnet->getID());
            in_bindings.addTempString(subnet->toText());

            // Attempt the update.
            auto cnt = updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::UPDATE_SUBNET4,
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
            updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_SERVER,
                              server_bindings);
        }

        // Subnet was successfully created/updated.

        // Insert associations with the servers.
        PsqlBindArray attach_bindings;
        attach_bindings.add(subnet->getID());
        attach_bindings.addTimestamp(subnet->getModificationTime());
        attachElementToServers(PgSqlConfigBackendDHCPv4Impl::INSERT_SUBNET4_SERVER,
                               server_selector, attach_bindings);

        // (Re)create pools.
        for (auto pool : subnet->getPools(Lease::TYPE_V4)) {
            createPool4(server_selector, boost::dynamic_pointer_cast<Pool4>(pool),
                        subnet);
        }

        // (Re)create options.
        auto option_spaces = subnet->getCfgOption()->getOptionSpaceNames();
        for (auto option_space : option_spaces) {
            OptionContainerPtr options = subnet->getCfgOption()->getAll(option_space);
            for (auto desc = options->begin(); desc != options->end(); ++desc) {
                OptionDescriptorPtr desc_copy = OptionDescriptor::create(*desc);
                desc_copy->space_name_ = option_space;
                createUpdateOption4(server_selector, subnet->getID(), desc_copy,
                                    true);
            }
        }

        // Commit the work.
        transaction.commit();
    }

    /// @brief Inserts new IPv4 pool to the database.
    ///
    /// @param server_selector Server selector.
    /// @param pool Pointer to the pool to be inserted.
    /// @param subnet Pointer to the subnet that this pool belongs to.
    void createPool4(const ServerSelector& server_selector,
                     const Pool4Ptr& pool,
                     const Subnet4Ptr& subnet) {
        // Create the input bindings.
        PsqlBindArray in_bindings;
        in_bindings.addInet4(pool->getFirstAddress());
        in_bindings.addInet4(pool->getLastAddress());
        in_bindings.add(subnet->getID());
        in_bindings.addOptional(pool->getClientClass());
        addRequiredClassesBinding(in_bindings, pool);
        in_bindings.add(pool->getContext());
        in_bindings.addTimestamp(subnet->getModificationTime());

        // Attempt to INSERT the pool.
        insertQuery(PgSqlConfigBackendDHCPv4Impl::INSERT_POOL4, in_bindings);

        // Get the id of the newly inserted pool.
        uint64_t pool_id = getLastInsertId("dhcp4_pool", "id");

        // Add the pool's options.
        auto option_spaces = pool->getCfgOption()->getOptionSpaceNames();
        for (auto option_space : option_spaces) {
            OptionContainerPtr options = pool->getCfgOption()->getAll(option_space);
            for (auto desc = options->begin(); desc != options->end(); ++desc) {
                OptionDescriptorPtr desc_copy = OptionDescriptor::create(*desc);
                desc_copy->space_name_ = option_space;
                createUpdateOption4(server_selector, pool_id, desc_copy, true);
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
                           PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
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
    uint64_t deleteSubnet4(const ServerSelector& server_selector,
                           const SubnetID& subnet_id) {
        int index = (server_selector.amAny() ?
                     PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_ID_ANY :
                     PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_ID_WITH_TAG);
        return (deleteTransactional(index, server_selector,
                                    "deleting a subnet", "subnet deleted",
                                    true, static_cast<uint32_t>(subnet_id)));
    }

    /// @brief Sends query to delete subnet by id.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be deleted.
    /// @return Number of deleted subnets.
    uint64_t deleteSubnet4(const ServerSelector& server_selector,
                           const std::string& subnet_prefix) {
        int index = (server_selector.amAny() ?
                     PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_PREFIX_ANY :
                     PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_PREFIX_WITH_TAG);
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
    uint64_t deletePools4(const Subnet4Ptr& subnet) {
        PsqlBindArray in_bindings;
        in_bindings.add(subnet->getID());
        in_bindings.addTempString(subnet->toText());

        // Run DELETE.
        return (updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::DELETE_POOLS4,
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
    void getSharedNetworks4(const StatementIndex& index,
                            const ServerSelector& server_selector,
                            const PsqlBindArray& in_bindings,
                            SharedNetwork4Collection& shared_networks) {
        uint64_t last_network_id = 0;
        uint64_t last_option_id = 0;
        std::string last_tag;

        selectQuery(index, in_bindings,
                    [this, &shared_networks, &last_network_id, &last_option_id, &last_tag]
                    (PgSqlResult& r, int row) {
            // Create a convenience worker for the row.
            PgSqlResultRowWorker worker(r, row);

            SharedNetwork4Ptr last_network;
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
                last_network = SharedNetwork4::create(worker.getString(1));
                last_network->setId(last_network_id);

                // client_class at 2.
                if (!worker.isColumnNull(2)) {
                    last_network->allowClientClass(worker.getString(2));
                }

                // interface at 3.
                if (!worker.isColumnNull(3)) {
                    last_network->setIface(worker.getString(3));
                }

                // match_client_id at 4.
                if (!worker.isColumnNull(4)) {
                    last_network->setMatchClientId(worker.getBool(4));
                }

                // modification_ts at 5.
                last_network->setModificationTime(worker.getTimestamp(5));

                // rebind_timer at 6.
                if (!worker.isColumnNull(6)) {
                    last_network->setT2(worker.getTriplet(6));
                }

                // Relay addresses at 7.
                setRelays(worker, 7, *last_network);

                // renew_timer at 8.
                if (!worker.isColumnNull(8)) {
                    last_network->setT1(worker.getTriplet(8));
                }

                // require_client_classes at 9.
                setRequiredClasses(worker, 9, [&last_network](const std::string& class_name) {
                    last_network->requireClientClass(class_name);
                });

                // reservations_global at 10.
                if (!worker.isColumnNull(10)) {
                    last_network->setReservationsGlobal(worker.getBool(10));
                }

                // user_context at 11.
                if (!worker.isColumnNull(11)) {
                    ElementPtr user_context = worker.getJSON(11);
                    if (user_context) {
                        last_network->setContext(user_context);
                    }
                }

                // valid_lifetime at 12.
                // min_valid_lifetime at 32.
                // max_valid_lifetime at 33.
                if (!worker.isColumnNull(12)) {
                    last_network->setValid(worker.getTriplet(12, 32, 33));
                }

                // option from 13 to 24.

                // calculate_tee_times at 25.
                if (!worker.isColumnNull(25)) {
                    last_network->setCalculateTeeTimes(worker.getBool(25));
                }

                // t1_percent at 26.
                if (!worker.isColumnNull(26)) {
                    last_network->setT1Percent(worker.getDouble(26));
                }

                // t2_percent at 27.
                if (!worker.isColumnNull(27)) {
                    last_network->setT2Percent(worker.getDouble(27));
                }

                // authoritative at 28.
                if (!worker.isColumnNull(28)) {
                    last_network->setAuthoritative(worker.getBool(28));
                }

                // boot_file_name at 29.
                if (!worker.isColumnNull(29)) {
                    last_network->setFilename(worker.getString(29));
                }

                // next_server at 30.
                if (!worker.isColumnNull(30)) {
                    last_network->setSiaddr(worker.getInet4(30));
                }

                // server_hostname at 31.
                if (!worker.isColumnNull(31)) {
                    last_network->setSname(worker.getString(31));
                }

                // min_valid_lifetime at 32.
                // max_valid_lifetime at 33.

                // ddns_send_updates at 34.
                if (!worker.isColumnNull(34)) {
                    last_network->setDdnsSendUpdates(worker.getBool(34));
                }

                // ddns_override_no_update at 35.
                if (!worker.isColumnNull(35)) {
                    last_network->setDdnsOverrideNoUpdate(worker.getBool(35));
                }

                // ddns_override_client_update at 36.
                if (!worker.isColumnNull(36)) {
                    last_network->setDdnsOverrideClientUpdate(worker.getBool(36));
                }

                // ddns_replace_client_name at 37.
                if (!worker.isColumnNull(37)) {
                    last_network->setDdnsReplaceClientNameMode(
                        static_cast<D2ClientConfig::ReplaceClientNameMode>(worker.getSmallInt(37)));
                }

                // ddns_generated_prefix at 38.
                if (!worker.isColumnNull(38)) {
                    last_network->setDdnsGeneratedPrefix(worker.getString(38));
                }

                // ddns_qualifying_suffix at 39.
                if (!worker.isColumnNull(39)) {
                    last_network->setDdnsQualifyingSuffix(worker.getString(39));
                }

                // reservations_in_subnet at 40.
                if (!worker.isColumnNull(40)) {
                    last_network->setReservationsInSubnet(worker.getBool(40));
                }

                // reservations_in_subnet at 41.
                if (!worker.isColumnNull(41)) {
                    last_network->setReservationsOutOfPool(worker.getBool(41));
                }

                // cache_threshold at 42.
                if (!worker.isColumnNull(42)) {
                    last_network->setCacheThreshold(worker.getDouble(42));
                }

                // cache_max_age at 43.
                if (!worker.isColumnNull(43)) {
                    last_network->setCacheMaxAge(worker.getInt(43));
                }

                // server_tag at 44.

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
            if (!worker.isColumnNull(44)) {
                std::string new_tag = worker.getString(44);
                if (last_tag != new_tag) {
                    if (!new_tag.empty() && !last_network->hasServerTag(ServerTag(new_tag))) {
                        last_network->setServerTag(new_tag);
                    }

                    last_tag = new_tag;
                }
            }

            // Parse network-specific option from 13 to 24.
            if (!worker.isColumnNull(13) &&
                (last_option_id < worker.getBigInt(13))) {
                last_option_id = worker.getBigInt(13);

                OptionDescriptorPtr desc = processOptionRow(Option::V4, worker, 13);
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
    SharedNetwork4Ptr getSharedNetwork4(const ServerSelector& server_selector,
                                        const std::string& name) {
        if (server_selector.hasMultipleTags()) {
            isc_throw(InvalidOperation, "expected one server tag to be specified"
                      " while fetching a shared network. Got: "
                      << getServerTagsAsText(server_selector));
        }

        PsqlBindArray in_bindings;
        in_bindings.add(name);

        auto index = PgSqlConfigBackendDHCPv4Impl::GET_SHARED_NETWORK4_NAME_NO_TAG;
        if (server_selector.amUnassigned()) {
            index = PgSqlConfigBackendDHCPv4Impl::GET_SHARED_NETWORK4_NAME_UNASSIGNED;
        } else if (server_selector.amAny()) {
            index = PgSqlConfigBackendDHCPv4Impl::GET_SHARED_NETWORK4_NAME_ANY;
        }

        SharedNetwork4Collection shared_networks;
        getSharedNetworks4(index, server_selector, in_bindings, shared_networks);

        return (shared_networks.empty() ? SharedNetwork4Ptr() : *shared_networks.begin());
    }

    /// @brief Sends query to retrieve all shared networks.
    ///
    /// @param server_selector Server selector.
    /// @param [out] shared_networks Reference to the shared networks collection
    /// structure where shared networks should be inserted.
    void getAllSharedNetworks4(const ServerSelector& server_selector,
                               SharedNetwork4Collection& shared_networks) {
        if (server_selector.amAny()) {
            isc_throw(InvalidOperation, "fetching all shared networks for ANY "
                      "server is not supported");
        }

        auto index = (server_selector.amUnassigned() ?
                      PgSqlConfigBackendDHCPv4Impl::GET_ALL_SHARED_NETWORKS4_UNASSIGNED :
                      PgSqlConfigBackendDHCPv4Impl::GET_ALL_SHARED_NETWORKS4);

        PsqlBindArray in_bindings;
        getSharedNetworks4(index, server_selector, in_bindings, shared_networks);
    }

    /// @brief Sends query to retrieve modified shared networks.
    ///
    /// @param server_selector Server selector.
    /// @param modification_ts Lower bound modification timestamp.
    /// @param [out] shared_networks Reference to the shared networks collection
    /// structure where shared networks should be inserted.
    void getModifiedSharedNetworks4(const ServerSelector& server_selector,
                                    const boost::posix_time::ptime& modification_ts,
                                    SharedNetwork4Collection& shared_networks) {
        if (server_selector.amAny()) {
            isc_throw(InvalidOperation, "fetching modified shared networks for ANY "
                      "server is not supported");
        }

        PsqlBindArray in_bindings;
        in_bindings.addTimestamp(modification_ts);

        auto index = (server_selector.amUnassigned() ?
                      PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_SHARED_NETWORKS4_UNASSIGNED :
                      PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_SHARED_NETWORKS4);
        getSharedNetworks4(index, server_selector, in_bindings, shared_networks);
    }

    /// @brief Sends query to insert or update shared network.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Pointer to the shared network to be inserted or updated.
    void createUpdateSharedNetwork4(const ServerSelector& server_selector,
                                    const SharedNetwork4Ptr& shared_network) {
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
        in_bindings.addOptional(shared_network->getMatchClientId(Network::Inheritance::NONE));
        in_bindings.addTimestamp(shared_network->getModificationTime()),
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
        in_bindings.addOptional(shared_network->getAuthoritative(Network::Inheritance::NONE));
        in_bindings.addOptional(shared_network->getFilename(Network::Inheritance::NONE));
        in_bindings.addOptionalInet4(shared_network->getSiaddr(Network::Inheritance::NONE));
        in_bindings.addOptional(shared_network->getSname(Network::Inheritance::NONE));
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
                           PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                           server_selector, "shared network set", true);

        // Create a savepoint in case we are called as part of larger
        // transaction.
        conn_.createSavepoint("createUpdateSharedNetwork4");

        try {

            // Try to insert shared network. The shared network name must be unique,
            // so if inserting fails with DuplicateEntry exception we'll need to
            // update existing shared network entry.
            insertQuery(PgSqlConfigBackendDHCPv4Impl::INSERT_SHARED_NETWORK4,
                        in_bindings);

        } catch (const DuplicateEntry&) {
            // It already exists, rollback to the savepoint to preserve
            // any prior work.
            conn_.rollbackToSavepoint("createUpdateSharedNetwork4");

            // We're updating, so we need to remove any options.
            deleteOptions4(ServerSelector::ANY(), shared_network);

            // Need to add one more binding for WHERE clause.
            in_bindings.addTempString(shared_network->getName());

            // Try the update.
            updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::UPDATE_SHARED_NETWORK4,
                              in_bindings);

            // Remove existing server association.
            PsqlBindArray server_bindings;
            server_bindings.addTempString(shared_network->getName());
            updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::DELETE_SHARED_NETWORK4_SERVER,
                              server_bindings);
        }

        // Associate the shared network with the servers.
        PsqlBindArray attach_bindings;
        attach_bindings.addTempString(shared_network->getName());
        attach_bindings.addTimestamp(shared_network->getModificationTime());
        attachElementToServers(PgSqlConfigBackendDHCPv4Impl::INSERT_SHARED_NETWORK4_SERVER,
                               server_selector, attach_bindings);

        // (Re)create options.
        auto option_spaces = shared_network->getCfgOption()->getOptionSpaceNames();
        for (auto option_space : option_spaces) {
            OptionContainerPtr options = shared_network->getCfgOption()->getAll(option_space);
            for (auto desc = options->begin(); desc != options->end(); ++desc) {
                OptionDescriptorPtr desc_copy = OptionDescriptor::create(*desc);
                desc_copy->space_name_ = option_space;
                createUpdateOption4(server_selector, shared_network->getName(),
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
    void insertOption4(const ServerSelector& server_selector,
                       const PsqlBindArray& in_bindings,
                       const boost::posix_time::ptime& modification_ts) {
        // Attempt the insert.
        insertQuery(PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION4, in_bindings);

        // Fetch primary key value of the inserted option. We will use it in the
        // next INSERT statement to associate this option with the server.
        auto option_id = getLastInsertId("dhcp4_options", "option_id");

        PsqlBindArray attach_bindings;
        attach_bindings.add(option_id);   // id of newly inserted global.
        attach_bindings.addTimestamp(modification_ts);

        // Associate the option with the servers.
        attachElementToServers(PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION4_SERVER,
                               server_selector, attach_bindings);
    }

    /// @brief Sends query to insert or update global DHCP option.
    ///
    /// @param server_selector Server selector.
    /// @param option Pointer to the option descriptor encapsulating the option.
    void createUpdateOption4(const ServerSelector& server_selector,
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
                           PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                           server_selector, "global option set", false);

        // Try to update the option.
        if (updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION4,
                              in_bindings) == 0) {
            // The option doesn't exist, so we'll try to insert it.
            // Remove the update where clause bindings.
            while (in_bindings.size() > pre_where_size) {
                in_bindings.popBack();
            }

            // Try to insert the option.
            insertOption4(server_selector, in_bindings,
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
    void createUpdateOption4(const ServerSelector& server_selector,
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
                           PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                           server_selector, "subnet specific option set",
                           cascade_update);

        // Try to update the subnet option.
        if (updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_SUBNET_ID,
                              in_bindings) == 0) {
            // The option doesn't exist, so we'll try to insert it.
            // Remove the update where clause bindings.
            while (in_bindings.size() > pre_where_size) {
                in_bindings.popBack();
            }

            // Try to insert the option.
            insertOption4(server_selector, in_bindings,
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
    void createUpdateOption4(const ServerSelector& server_selector,
                             const IOAddress& pool_start_address,
                             const IOAddress& pool_end_address,
                             const OptionDescriptorPtr& option) {
        uint64_t pool_id = 0;
        Pool4Ptr pool = getPool4(server_selector, pool_start_address, pool_end_address,
                                 pool_id);
        if (!pool) {
            isc_throw(BadValue, "no pool found for range of "
                      << pool_start_address << " : "
                      << pool_end_address);
        }

        createUpdateOption4(server_selector, pool_id, option, false);
    }

    /// @brief Sends query to insert or update DHCP option in a pool.
    ///
    /// @param selector Server selector.
    /// @param pool_id Identifier of the pool the option belongs to.
    /// @param option Pointer to the option descriptor encapsulating the option.
    /// @param cascade_update Boolean value indicating whether the update is
    /// performed as part of the owning element, e.g. subnet.
    void createUpdateOption4(const ServerSelector& server_selector,
                             const uint64_t pool_id,
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
        in_bindings.add(5);
        in_bindings.add(option->getContext());
        in_bindings.addNull();
        in_bindings.add(pool_id);
        in_bindings.addTimestamp(option->getModificationTime());

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
        ScopedAuditRevision
            audit_revision(this,
                           PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                           server_selector, "pool specific option set",
                           cascade_update);

        // Try to update the option.
        if (updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_POOL_ID,
                              in_bindings) == 0) {
            // The option doesn't exist, so we'll try to insert it.
            // Remove the update where clause bindings.
            while (in_bindings.size() > pre_where_size) {
                in_bindings.popBack();
            }

            // Try to insert the option.
            insertOption4(server_selector, in_bindings,
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
    void createUpdateOption4(const ServerSelector& server_selector,
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
                           PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                           server_selector, "shared network specific option set",
                           cascade_update);

        // Try to update the option.
        if (updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_SHARED_NETWORK,
                              in_bindings) == 0) {
            // The option doesn't exist, so we'll try to insert it.
            // Remove the update where clause bindings.
            while (in_bindings.size() > pre_where_size) {
                in_bindings.popBack();
            }

            // Try to insert the option.
            insertOption4(server_selector, in_bindings,
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
    void createUpdateOption4(const ServerSelector& server_selector,
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
                           PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                           server_selector, "client class specific option set",
                           true);

        if (updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_CLIENT_CLASS,
                              in_bindings) == 0) {
            // The option doesn't exist, so we'll try to insert it.
            // Remove the update where clause bindings.
            while (in_bindings.size() > pre_where_size) {
                in_bindings.popBack();
            }

            insertOption4(server_selector, in_bindings,
                          option->getModificationTime());
        }
    }

    /// @brief Sends query to insert or update option definition.
    ///
    /// @param server_selector Server selector.
    /// @param option_def Pointer to the option definition to be inserted or updated.
    void createUpdateOptionDef4(const ServerSelector& server_selector,
                                const OptionDefinitionPtr& option_def) {
        createUpdateOptionDef(server_selector, Option::V4, option_def, DHCP4_OPTION_SPACE,
                              PgSqlConfigBackendDHCPv4Impl::GET_OPTION_DEF4_CODE_SPACE,
                              PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION_DEF4,
                              PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION_DEF4,
                              PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                              PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION_DEF4_SERVER);
    }

    /// @brief Sends query to insert or update option definition
    /// for a client class.
    ///
    /// @param server_selector Server selector.
    /// @param option_def Pointer to the option definition to be inserted or updated.
    /// @param client_class Client class name.
    void createUpdateOptionDef4(const ServerSelector& server_selector,
                                const OptionDefinitionPtr& option_def,
                                const std::string& client_class_name) {
        createUpdateOptionDef(server_selector, Option::V4, option_def, DHCP4_OPTION_SPACE,
                              PgSqlConfigBackendDHCPv4Impl::GET_OPTION_DEF4_CODE_SPACE,
                              PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION_DEF4_CLIENT_CLASS,
                              PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION_DEF4_CLIENT_CLASS,
                              PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                              PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION_DEF4_SERVER,
                              client_class_name);
    }

    /// @brief Sends query to delete option definition by code and
    /// option space name.
    ///
    /// @param server_selector Server selector.
    /// @param code Option code.
    /// @param name Option name.
    /// @return Number of deleted option definitions.
    uint64_t deleteOptionDef4(const ServerSelector& server_selector,
                              const uint16_t code,
                              const std::string& space) {
        PsqlBindArray in_bindings;
        in_bindings.add(code);
        in_bindings.add(space);

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION_DEF4_CODE_NAME,
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
    uint64_t deleteOptionDefs4(const ServerSelector& server_selector,
                               const ClientClassDefPtr& client_class) {
        PsqlBindArray in_bindings;
        in_bindings.addTempString(client_class->getName());

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION_DEFS4_CLIENT_CLASS,
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
    uint64_t deleteOption4(const ServerSelector& server_selector,
                           const uint16_t code,
                           const std::string& space) {
        PsqlBindArray in_bindings;
        in_bindings.add(code);
        in_bindings.add(space);

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION4,
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
    uint64_t deleteOption4(const ServerSelector& server_selector,
                           const SubnetID& subnet_id,
                           const uint16_t code,
                           const std::string& space) {
        PsqlBindArray in_bindings;
        in_bindings.add(subnet_id);
        in_bindings.add(code);
        in_bindings.add(space);

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION4_SUBNET_ID,
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
    uint64_t deleteOption4(const db::ServerSelector& server_selector,
                           const IOAddress& pool_start_address,
                           const IOAddress& pool_end_address,
                           const uint16_t code,
                           const std::string& space) {
        PsqlBindArray in_bindings;
        in_bindings.addInet4(pool_start_address);
        in_bindings.addInet4(pool_end_address);
        in_bindings.add(code);
        in_bindings.add(space);

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION4_POOL_RANGE,
                                    server_selector,
                                    "deleting option for a pool",
                                    "pool specific option deleted",
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
    uint64_t deleteOption4(const db::ServerSelector& server_selector,
                           const std::string& shared_network_name,
                           const uint16_t code,
                           const std::string& space) {
        PsqlBindArray in_bindings;
        in_bindings.add(shared_network_name);
        in_bindings.add(code);
        in_bindings.add(space);

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION4_SHARED_NETWORK,
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
    uint64_t deleteOptions4(const ServerSelector& server_selector,
                            const Subnet4Ptr& subnet) {
        PsqlBindArray in_bindings;
        in_bindings.add(subnet->getID());
        in_bindings.addTempString(subnet->toText());

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv4Impl::DELETE_OPTIONS4_SUBNET_ID_PREFIX,
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
    uint64_t deleteOptions4(const ServerSelector& server_selector,
                            const SharedNetwork4Ptr& shared_network) {
        PsqlBindArray in_bindings;
        in_bindings.addTempString(shared_network->getName());

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv4Impl::
                                    DELETE_OPTIONS4_SHARED_NETWORK, server_selector,
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
    uint64_t deleteOptions4(const ServerSelector& server_selector,
                            const ClientClassDefPtr& client_class) {
        PsqlBindArray in_bindings;
        in_bindings.addTempString(client_class->getName());

        // Run DELETE.
        return (deleteTransactional(PgSqlConfigBackendDHCPv4Impl::
                                    DELETE_OPTIONS4_CLIENT_CLASS, server_selector,
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
    void getClientClasses4(const StatementIndex& index,
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

                // next server
                if (!worker.isColumnNull(3)) {
                    last_client_class->setNextServer(worker.getInet4(3));
                }

                // sname
                if (!worker.isColumnNull(4)) {
                    last_client_class->setSname(worker.getString(4));
                }

                // filename
                if (!worker.isColumnNull(5)) {
                    last_client_class->setFilename(worker.getString(5));
                }

                // required
                if (!worker.isColumnNull(6)) {
                    last_client_class->setRequired(worker.getBool(6));
                }

                // valid lifetime: default, min, max
                last_client_class->setValid(worker.getTriplet(7, 8, 9));

                // depend on known directly or indirectly
                last_client_class->setDependOnKnown(worker.getBool(10) || worker.getBool(11));

                // modification_ts
                last_client_class->setModificationTime(worker.getTimestamp(12));

                // user_context at 13.
                if (!worker.isColumnNull(13)) {
                    ElementPtr user_context = worker.getJSON(13);
                    if (user_context) {
                        last_client_class->setContext(user_context);
                    }
                }

                class_list.push_back(last_client_class);
            }

            // Check for new server tags at 36.
            if (!worker.isColumnNull(36)) {
                std::string new_tag = worker.getString(36);
                if (last_tag != new_tag) {
                    if (!new_tag.empty() && !last_client_class->hasServerTag(ServerTag(new_tag))) {
                        last_client_class->setServerTag(new_tag);
                    }

                    last_tag = new_tag;
                }
            }

            // Parse client class specific option definition from 14 to 23.
            if (!worker.isColumnNull(14) &&
                (last_option_def_id < worker.getBigInt(14))) {
                last_option_def_id = worker.getBigInt(14);

                auto def = processOptionDefRow(worker, 14);
                if (def) {
                    last_client_class->getCfgOptionDef()->add(def);
                }
            }

            // Parse client class specific option from 24 to 35.
            if (!worker.isColumnNull(24) &&
                (last_option_id < worker.getBigInt(24))) {
                last_option_id = worker.getBigInt(24);

                OptionDescriptorPtr desc = processOptionRow(Option::V4, worker, 24);
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
    ClientClassDefPtr getClientClass4(const ServerSelector& server_selector,
                                      const std::string& name) {
        PsqlBindArray in_bindings;
        in_bindings.add(name);

        ClientClassDictionary client_classes;
        getClientClasses4(PgSqlConfigBackendDHCPv4Impl::GET_CLIENT_CLASS4_NAME,
                          server_selector, in_bindings, client_classes);
        return (client_classes.getClasses()->empty() ? ClientClassDefPtr() :
                (*client_classes.getClasses()->begin()));
    }

    /// @brief Sends query to retrieve all client classes.
    ///
    /// @param server_selector Server selector.
    /// @param [out] client_classes Reference to the client classes collection
    /// where retrieved classes will be stored.
    void getAllClientClasses4(const ServerSelector& server_selector,
                              ClientClassDictionary& client_classes) {
        PsqlBindArray in_bindings;
        getClientClasses4(server_selector.amUnassigned() ?
                          PgSqlConfigBackendDHCPv4Impl::GET_ALL_CLIENT_CLASSES4_UNASSIGNED :
                          PgSqlConfigBackendDHCPv4Impl::GET_ALL_CLIENT_CLASSES4,
                          server_selector, in_bindings, client_classes);
    }

    /// @brief Sends query to retrieve modified client classes.
    ///
    /// @param server_selector Server selector.
    /// @param modification_ts Lower bound modification timestamp.
    /// @param [out] client_classes Reference to the client classes collection
    /// where retrieved classes will be stored.
    void getModifiedClientClasses4(const ServerSelector& server_selector,
                                   const boost::posix_time::ptime& modification_ts,
                                   ClientClassDictionary& client_classes) {
        if (server_selector.amAny()) {
            isc_throw(InvalidOperation, "fetching modified client classes for ANY "
                      "server is not supported");
        }

        PsqlBindArray in_bindings;
        in_bindings.addTimestamp(modification_ts);
        getClientClasses4(server_selector.amUnassigned() ?
                          PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_CLIENT_CLASSES4_UNASSIGNED :
                          PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_CLIENT_CLASSES4,
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
    void createUpdateClientClass4(const ServerSelector& server_selector,
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
            parser.parse(expression, Element::create(client_class->getTest()), AF_INET,
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
        in_bindings.addInet4(client_class->getNextServer());
        in_bindings.addTempString(client_class->getSname());
        in_bindings.addTempString(client_class->getFilename());
        in_bindings.add(client_class->getRequired());
        in_bindings.add(client_class->getValid());
        in_bindings.add(client_class->getValid().getMin());
        in_bindings.add(client_class->getValid().getMax());
        in_bindings.add(depend_on_known);

        // follow-class-name (11)
        if (follow_class_name.empty()) {
            in_bindings.addNull();
        } else {
            in_bindings.add(follow_class_name);
        }

        in_bindings.addTimestamp(client_class->getModificationTime());
        in_bindings.add(client_class->getContext());

        PgSqlTransaction transaction(conn_);

        ScopedAuditRevision audit_revision(this, PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                                           server_selector, "client class set", true);

        // Create a savepoint in case we are called as part of larger
        // transaction.
        conn_.createSavepoint("createUpdateClass4");

        // Keeps track of whether the client class is inserted or updated.
        auto update = false;
        try {
            insertQuery(PgSqlConfigBackendDHCPv4Impl::INSERT_CLIENT_CLASS4, in_bindings);

        } catch (const DuplicateEntry&) {
            // It already exists, rollback to the savepoint to preserve
            // any prior work.
            conn_.rollbackToSavepoint("createUpdateClass4");

            // Delete options and option definitions. They will be re-created from the new class
            // instance.
            deleteOptions4(ServerSelector::ANY(), client_class);
            deleteOptionDefs4(ServerSelector::ANY(), client_class);

            // Note: follow_class_name is left in the bindings even though it is
            // not needed in both cases. This allows us to use one base query.

            // Add the class name for the where clause.
            in_bindings.add(class_name);
            if (follow_class_name.empty()) {
                // If position is not specified, leave the class at the same position.
                updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::UPDATE_CLIENT_CLASS4_SAME_POSITION,
                                  in_bindings);
            } else {
                // Update with follow_class_name specifying the position.
                updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::UPDATE_CLIENT_CLASS4,
                                  in_bindings);
            }

            // Delete class associations with the servers and dependencies. We will re-create
            // them according to the new class specification.
            PsqlBindArray in_assoc_bindings;
            in_assoc_bindings.add(class_name);
            updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::DELETE_CLIENT_CLASS4_DEPENDENCY,
                              in_assoc_bindings);
            updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::DELETE_CLIENT_CLASS4_SERVER,
                              in_assoc_bindings);
            update = true;
        }

        // Associate client class with the servers.
        PsqlBindArray attach_bindings;
        attach_bindings.add(class_name);
        attach_bindings.addTimestamp(client_class->getModificationTime());

        attachElementToServers(PgSqlConfigBackendDHCPv4Impl::INSERT_CLIENT_CLASS4_SERVER,
                               server_selector, attach_bindings);

        // Iterate over the captured dependencies and try to insert them into the database.
        for (auto dependency : dependencies) {
            try {
                PsqlBindArray in_dependency_bindings;
                in_dependency_bindings.add(class_name);
                in_dependency_bindings.add(dependency);

                // We deleted earlier dependencies, so we can simply insert new ones.
                insertQuery(PgSqlConfigBackendDHCPv4Impl::INSERT_CLIENT_CLASS4_DEPENDENCY,
                            in_dependency_bindings);
            } catch (const std::exception& ex) {
                isc_throw(InvalidOperation, "unmet dependency on client class: " << dependency);
            }
        }

        // If we performed client class update we also have to verify that its dependency
        // on KNOWN/UNKNOWN client classes hasn't changed.
        if (update) {
            PsqlBindArray in_check_bindings;
            insertQuery(PgSqlConfigBackendDHCPv4Impl::CHECK_CLIENT_CLASS_KNOWN_DEPENDENCY_CHANGE,
                              in_check_bindings);
        }

        // (Re)create option definitions.
        if (client_class->getCfgOptionDef()) {
            auto option_defs = client_class->getCfgOptionDef()->getContainer();
            auto option_spaces = option_defs.getOptionSpaceNames();
            for (auto option_space : option_spaces) {
                OptionDefContainerPtr defs = option_defs.getItems(option_space);
                for (auto def = defs->begin(); def != defs->end(); ++def) {
                    createUpdateOptionDef4(server_selector, *def, client_class->getName());
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
                createUpdateOption4(server_selector, client_class, desc_copy);
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
    uint64_t deleteClientClass4(const ServerSelector& server_selector,
                                const std::string& name) {
        int index = server_selector.amAny() ?
            PgSqlConfigBackendDHCPv4Impl::DELETE_CLIENT_CLASS4_ANY :
            PgSqlConfigBackendDHCPv4Impl::DELETE_CLIENT_CLASS4;

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
        multipleUpdateDeleteQueries(DELETE_ALL_GLOBAL_PARAMETERS4_UNASSIGNED,
                                    DELETE_ALL_GLOBAL_OPTIONS4_UNASSIGNED,
                                    DELETE_ALL_OPTION_DEFS4_UNASSIGNED);
    }

    /// @brief Attempts to delete a server having a given tag.
    ///
    /// @param server_tag Tag of the server to be deleted.
    /// @return Number of deleted servers.
    /// @throw isc::InvalidOperation when trying to delete the logical
    /// server 'all'.
    uint64_t deleteServer4(const data::ServerTag& server_tag) {
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
            audit_revision(this, PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                           ServerSelector::ALL(), "deleting a server", false);

        // Specify which server should be deleted.
        PsqlBindArray in_bindings;
        in_bindings.addTempString(server_tag.get());

        // Attempt to delete the server.
        auto count = updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::DELETE_SERVER4,
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
    uint64_t deleteAllServers4() {
        // Start transaction.
        PgSqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this, PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                           ServerSelector::ALL(), "deleting all servers",
                           false);

        // No arguments, hence empty input bindings.
        PsqlBindArray in_bindings;

        // Attempt to delete the servers.
        auto count = updateDeleteQuery(PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SERVERS4,
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
    /// @ref ConfigBackendDHCPv4Mgr.addBackend.
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
                if (ConfigBackendDHCPv4Mgr::instance().delBackend(parameters["type"], access, true)) {
                    ConfigBackendDHCPv4Mgr::instance().addBackend(db.getAccessString());
                }
            }

            reopened = true;
        } catch (const std::exception& ex) {
            LOG_ERROR(pgsql_cb_logger, PGSQL_CB_RECONNECT_ATTEMPT_FAILED4)
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
                LOG_ERROR(pgsql_cb_logger, PGSQL_CB_RECONNECT_FAILED4)
                        .arg(db_reconnect_ctl->maxRetries());

                // Cancel the timer.
                if (TimerMgr::instance()->isTimerRegistered(timer_name)) {
                    TimerMgr::instance()->unregisterTimer(timer_name);
                }

                // Invoke application layer connection failed callback.
                DatabaseConnection::invokeDbFailedCallback(db_reconnect_ctl);

                return (false);
            }

            LOG_INFO(pgsql_cb_logger, PGSQL_CB_RECONNECT_ATTEMPT_SCHEDULE4)
                    .arg(db_reconnect_ctl->maxRetries() - db_reconnect_ctl->retriesLeft() + 1)
                    .arg(db_reconnect_ctl->maxRetries())
                    .arg(db_reconnect_ctl->retryInterval());

            // Start the timer.
            if (!TimerMgr::instance()->isTimerRegistered(timer_name)) {
                TimerMgr::instance()->registerTimer(timer_name,
                    std::bind(&PgSqlConfigBackendDHCPv4Impl::dbReconnect, db_reconnect_ctl),
                              db_reconnect_ctl->retryInterval(),
                              asiolink::IntervalTimer::ONE_SHOT);
            }
            TimerMgr::instance()->setup(timer_name);
        }

        return (true);
    }

};

namespace {

/// @brief Array of tagged statements.
typedef std::array<PgSqlTaggedStatement, PgSqlConfigBackendDHCPv4Impl::NUM_STATEMENTS>
TaggedStatementArray;

/// @brief Prepared PgSQL statements used by the backend to insert and
/// retrieve data from the database. They must be in the same order as
/// PgSqlConfigBackendDHCPv4Impl::StatementIndex.  The statement is
/// the corresponding enum name.
TaggedStatementArray tagged_statements = { {
    {
        // PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
        4,
        {
            OID_TIMESTAMP,  // 1 audit_ts
            OID_VARCHAR,    // 2 server_tag
            OID_TEXT,       // 3 audit_log_message
            OID_BOOL        // 4 cascade_transaction
        },
        "CREATE_AUDIT_REVISION",
        "select createAuditRevisionDHCP4($1, $2, $3, $4)"
    },

    // Verify that dependency on KNOWN/UNKNOWN class has not changed.
    {
        // PgSqlConfigBackendDHCPv4Impl::CHECK_CLIENT_CLASS_KNOWN_DEPENDENCY_CHANGE,
        0,
        {
            OID_NONE
        },
        "CHECK_CLIENT_CLASS_KNOWN_DEPENDENCY_CHANGE",
        "select checkDHCPv4ClientClassKnownDependencyChange()"
    },

    // Select global parameter by name.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_GLOBAL_PARAMETER4,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_VARCHAR     // 2 name
        },
        "GET_GLOBAL_PARAMETER4",
        PGSQL_GET_GLOBAL_PARAMETER(dhcp4, AND g.name = $2)
    },

    // Select all global parameters.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_ALL_GLOBAL_PARAMETERS4,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "GET_ALL_GLOBAL_PARAMETERS4",
        PGSQL_GET_GLOBAL_PARAMETER(dhcp4)
    },

    // Select modified global parameters.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_GLOBAL_PARAMETERS4,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_TIMESTAMP   // 2 modification_ts
        },
        "GET_MODIFIED_GLOBAL_PARAMETERS4",
        PGSQL_GET_GLOBAL_PARAMETER(dhcp4, AND g.modification_ts >= $2)
    },

    // Select subnet by id.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_SUBNET4_ID_NO_TAG,
        1,
        {
            OID_INT8    // 1 subnet_id
        },
        "GET_SUBNET4_ID_NO_TAG",
        PGSQL_GET_SUBNET4_NO_TAG(WHERE s.subnet_id = $1)
    },

    // Select subnet by id without specifying server tags.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_SUBNET4_ID_ANY,
        1,
        {
            OID_INT8    // 1 subnet_id
        },
        "GET_SUBNET4_ID_ANY",
        PGSQL_GET_SUBNET4_ANY(WHERE s.subnet_id = $1)
    },

    // Select unassigned subnet by id.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_SUBNET4_ID_UNASSIGNED,
        1,
        {
            OID_INT8    // 1 subnet_id
        },
        "GET_SUBNET4_ID_UNASSIGNED",
        PGSQL_GET_SUBNET4_UNASSIGNED(AND s.subnet_id = $1)
    },

    // Select subnet by prefix.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_SUBNET4_PREFIX_NO_TAG,
        1,
        {
            OID_VARCHAR // 1 subnet_prefix
        },
        "GET_SUBNET4_PREFIX_NO_TAG",
        PGSQL_GET_SUBNET4_NO_TAG(WHERE s.subnet_prefix = $1)
    },

    // Select subnet by prefix without specifying server tags.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_SUBNET4_PREFIX_ANY,
        1,
        {
            OID_VARCHAR // 1 subnet_prefix
        },
        "GET_SUBNET4_PREFIX_ANY",
        PGSQL_GET_SUBNET4_ANY(WHERE s.subnet_prefix = $1)
    },

    // Select unassigned subnet by prefix.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_SUBNET4_PREFIX_UNASSIGNED,
        1,
        {
            OID_VARCHAR // 1 subnet_prefix
        },
        "GET_SUBNET4_PREFIX_UNASSIGNED",
        PGSQL_GET_SUBNET4_UNASSIGNED(AND s.subnet_prefix = $1)
    },

    // Select all subnets.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_ALL_SUBNETS4,
        0,
        {
            OID_NONE
        },
        "GET_ALL_SUBNETS4",
        PGSQL_GET_SUBNET4_NO_TAG()
    },

    // Select all unassigned subnets.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_ALL_SUBNETS4_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "GET_ALL_SUBNETS4_UNASSIGNED",
        PGSQL_GET_SUBNET4_UNASSIGNED()
    },

    // Select subnets having modification time later than X.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_SUBNETS4,
        1,
        {
            OID_TIMESTAMP // 1 modification_ts
        },
        "GET_MODIFIED_SUBNETS4",
        PGSQL_GET_SUBNET4_NO_TAG(WHERE s.modification_ts >= $1)
    },

    // Select modified and unassigned subnets.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_SUBNETS4_UNASSIGNED,
        1,
        {
            OID_TIMESTAMP // 1 modification_ts
        },
        "GET_MODIFIED_SUBNETS4_UNASSIGNED",
        PGSQL_GET_SUBNET4_UNASSIGNED(AND s.modification_ts >= $1)
    },

    // Select subnets belonging to a shared network.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_SHARED_NETWORK_SUBNETS4,
        1,
        {
            OID_VARCHAR // 1 share_network_name
        },
        "GET_SHARED_NETWORK_SUBNETS4",
        PGSQL_GET_SUBNET4_ANY(WHERE s.shared_network_name = $1)
    },

    // Select pool by address range for a server.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_POOL4_RANGE,
        3,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_TEXT,       // 2 start_address - cast as inet
            OID_TEXT        // 3 end_address - cast as inet
        },
        "GET_POOL4_RANGE",
        PGSQL_GET_POOL4_RANGE_WITH_TAG(WHERE (srv.tag = $1 OR srv.id = 1) \
                                       AND (p.start_address = cast($2 as inet)) \
                                       AND (p.end_address = cast($3 as inet)))
    },

    // Select pool by address range for any server.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_POOL4_RANGE_ANY,
        2,
        {
            OID_TEXT,       // 1 start_address - cast as inet
            OID_TEXT        // 2 end_address - cast as inet
        },
        "GET_POOL4_RANGE_ANY",
        PGSQL_GET_POOL4_RANGE_NO_TAG(WHERE (p.start_address = cast($1 as inet)) AND \
                                           (p.end_address = cast($2 as inet)))
    },

    // Select shared network by name.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_SHARED_NETWORK4_NAME_NO_TAG,
        1,
        {
            OID_VARCHAR // name of network
        },
        "GET_SHARED_NETWORK4_NAME_NO_TAG",
        PGSQL_GET_SHARED_NETWORK4_NO_TAG(WHERE n.name = $1)
    },

    // Select shared network by name without specifying server tags.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_SHARED_NETWORK4_NAME_ANY,
        1,
        {
            OID_VARCHAR // name of network
        },
        "GET_SHARED_NETWORK4_NAME_ANY",
        PGSQL_GET_SHARED_NETWORK4_ANY(WHERE n.name = $1)
    },

    // Select unassigned shared network by name.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_SHARED_NETWORK4_NAME_UNASSIGNED,
        1,
        {
            OID_VARCHAR // name of network
        },
        "GET_SHARED_NETWORK4_NAME_UNASSIGNED",
        PGSQL_GET_SHARED_NETWORK4_UNASSIGNED(AND n.name = $1)
    },

    // Select all shared networks.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_ALL_SHARED_NETWORKS4,
        0,
        {
            OID_NONE
        },
        "GET_ALL_SHARED_NETWORKS4",
        PGSQL_GET_SHARED_NETWORK4_NO_TAG()
    },

    // Select all unassigned shared networks.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_ALL_SHARED_NETWORKS4_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "GET_ALL_SHARED_NETWORKS4_UNASSIGNED",
        PGSQL_GET_SHARED_NETWORK4_UNASSIGNED()
    },

    // Select modified shared networks.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_SHARED_NETWORKS4,
        1,
        {
            OID_TIMESTAMP  // 1 modification_ts
        },
        "GET_MODIFIED_SHARED_NETWORKS4",
        PGSQL_GET_SHARED_NETWORK4_NO_TAG(WHERE n.modification_ts >= $1)
    },

    // Select modified and unassigned shared networks.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_SHARED_NETWORKS4_UNASSIGNED,
        1,
        {
            OID_TIMESTAMP  // 1 modification_ts
        },
        "GET_MODIFIED_SHARED_NETWORKS4_UNASSIGNED",
        PGSQL_GET_SHARED_NETWORK4_UNASSIGNED(AND n.modification_ts >= $1)
    },

    // Retrieves option definition by code and space.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_OPTION_DEF4_CODE_SPACE,
        3,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_INT2,       // 2 code
            OID_VARCHAR     // 3 space
        },
        "GET_OPTION_DEF4_CODE_SPACE",
        PGSQL_GET_OPTION_DEF(dhcp4, AND d.code = $2 AND d.space = $3)
    },

    // Retrieves all option definitions.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_ALL_OPTION_DEFS4,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "GET_ALL_OPTION_DEFS4",
        PGSQL_GET_OPTION_DEF(dhcp4)
    },

    // Retrieves modified option definitions.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_OPTION_DEFS4,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_TIMESTAMP   // 2 modification_ts
        },
        "GET_MODIFIED_OPTION_DEFS4",
        PGSQL_GET_OPTION_DEF(dhcp4, AND d.modification_ts >= $2)
    },

    // Retrieves global option by code and space.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_OPTION4_CODE_SPACE,
        3,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_INT2,       // 2 code
            OID_VARCHAR     // 3 space
        },
        "GET_OPTION4_CODE_SPACE",
        PGSQL_GET_OPTION4(AND o.scope_id = 0 AND o.code = $2 AND o.space = $3)
    },

    // Retrieves all global options.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_ALL_OPTIONS4,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "GET_ALL_OPTIONS4",
        PGSQL_GET_OPTION4(AND o.scope_id = 0)
    },

    // Retrieves modified options.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_OPTIONS4,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_TIMESTAMP   // 2 modification_ts
        },
        "GET_MODIFIED_OPTIONS4",
        PGSQL_GET_OPTION4(AND o.scope_id = 0 AND o.modification_ts >= $2)
    },

    // Retrieves an option for a given subnet, option code and space.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_OPTION4_SUBNET_ID_CODE_SPACE,
        4,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_INT8,       // 2 subnet_id
            OID_INT2,       // 3 code
            OID_VARCHAR     // 4 space
        },
        "GET_OPTION4_SUBNET_ID_CODE_SPACE",
        PGSQL_GET_OPTION4(AND o.scope_id = 1 AND o.dhcp4_subnet_id = $2 AND o.code = $3 AND o.space = $4)
    },

    // Retrieves an option for a given pool, option code and space.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_OPTION4_POOL_ID_CODE_SPACE,
        4,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_INT8,       // 2 pool_id
            OID_INT2,       // 3 code
            OID_VARCHAR     // 4 space
        },
        "GET_OPTION4_POOL_ID_CODE_SPACE",
        PGSQL_GET_OPTION4(AND o.scope_id = 5 AND o.pool_id = $2 AND o.code = $3 AND o.space = $4)
    },

    // Retrieves an option for a given shared network, option code and space.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_OPTION4_SHARED_NETWORK_CODE_SPACE,
        4,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_VARCHAR,    // 2 shared_network_name
            OID_INT2,       // 3 code
            OID_VARCHAR     // 4 space
        },
        "GET_OPTION4_SHARED_NETWORK_CODE_SPACE",
        PGSQL_GET_OPTION4(AND o.scope_id = 4 AND o.shared_network_name = $2 AND o.code = $3 AND o.space = $4)
    },

    // Select a client class by name.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_CLIENT_CLASS4_NAME,
        1,
        {
            OID_VARCHAR // name of class
        },
        "GET_CLIENT_CLASS4_NAME",
        PGSQL_GET_CLIENT_CLASS4_WITH_TAG(WHERE c.name = $1)
    },

    // Select all client classes.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_ALL_CLIENT_CLASSES4,
        0,
        {
            OID_NONE
        },
        "GET_ALL_CLIENT_CLASSES4",
        PGSQL_GET_CLIENT_CLASS4_WITH_TAG()
    },

    // Select all unassigned client classes.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_ALL_CLIENT_CLASSES4_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "GET_ALL_CLIENT_CLASSES4_UNASSIGNED",
        PGSQL_GET_CLIENT_CLASS4_UNASSIGNED()
    },

    // Select modified client classes.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_CLIENT_CLASSES4,
        1,
        {
            OID_TIMESTAMP // 1 modification_ts
        },
        "GET_MODIFIED_CLIENT_CLASSES4",
        PGSQL_GET_CLIENT_CLASS4_WITH_TAG(WHERE c.modification_ts >= $1)
    },

    // Select modified client classes.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_CLIENT_CLASSES4_UNASSIGNED,
        1,
        {
            OID_TIMESTAMP // 1 modification_ts
        },
        "GET_MODIFIED_CLIENT_CLASSES4_UNASSIGNED",
        PGSQL_GET_CLIENT_CLASS4_UNASSIGNED(AND c.modification_ts >= $1)
    },

    // Retrieves the most recent audit entries.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_AUDIT_ENTRIES4_TIME,
        3,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_TIMESTAMP,  // 2 modification_ts
            OID_INT8        // 3 revision id
        },
        "GET_AUDIT_ENTRIES4_TIME",
        PGSQL_GET_AUDIT_ENTRIES_TIME(dhcp4)
    },

    // Retrieves a server by tag.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_SERVER4,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "GET_SERVER4",
        PGSQL_GET_SERVER(dhcp4)
    },

    // Retrieves all servers.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_ALL_SERVERS4,
        0,
        {
            OID_NONE
        },
        "GET_ALL_SERVERS4",
        PGSQL_GET_ALL_SERVERS(dhcp4)
    },

    // Insert global parameter.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_GLOBAL_PARAMETER4,
        4,
        {
            OID_VARCHAR,    // 1 name
            OID_TEXT,       // 2 value
            OID_INT2,       // 3 parameter_type
            OID_TIMESTAMP   // 4 modification_ts
        },
        "INSERT_GLOBAL_PARAMETER4",
        PGSQL_INSERT_GLOBAL_PARAMETER(dhcp4)
    },

    // Insert association of the global parameter with a server.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_GLOBAL_PARAMETER4_SERVER,
        3,
        {
            OID_INT8,       // 1 parameter_id
            OID_TIMESTAMP,  // 2 modification_ts
            OID_VARCHAR     // 3 server_tag
        },
        "INSERT_GLOBAL_PARAMETER4_SERVER",
        PGSQL_INSERT_GLOBAL_PARAMETER_SERVER(dhcp4)
    },

    // Insert a subnet.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_SUBNET4,
        36,
        {
            OID_INT8,       //  1 subnet_id,
            OID_VARCHAR,    //  2 subnet_prefix
            OID_VARCHAR,    //  3 interface_4o6
            OID_VARCHAR,    //  4 interface_id_4o6
            OID_VARCHAR,    //  5 subnet_4o6
            OID_VARCHAR,    //  6 boot_file_name
            OID_VARCHAR,    //  7 client_class
            OID_VARCHAR,    //  8 interface
            OID_BOOL,       //  9 match_client_id
            OID_TIMESTAMP,  // 10 modification_ts
            OID_TEXT,       // 11 next_server - cast as inet
            OID_INT8,       // 12 rebind_timer
            OID_TEXT,       // 13 relay
            OID_INT8,       // 14 renew_timer
            OID_TEXT,       // 15 require_client_classes
            OID_BOOL,       // 16 reservations_global
            OID_VARCHAR,    // 17 server_hostname
            OID_VARCHAR,    // 18 shared_network_name
            OID_TEXT,       // 19 user_context
            OID_INT8,       // 20 valid_lifetime
            OID_INT8,       // 21 min_valid_lifetime
            OID_INT8,       // 22 max_valid_lifetime
            OID_BOOL,       // 23 calculate_tee_times
            OID_TEXT,       // 24 t1_percent - cast as float
            OID_TEXT,       // 25 t2_percent - cast as float
            OID_BOOL,       // 26 authoritative
            OID_BOOL,       // 27 ddns_send_updates
            OID_BOOL,       // 28 ddns_override_no_update
            OID_BOOL,       // 29 ddns_override_client_update
            OID_INT8,       // 30 ddns_replace_client_name
            OID_VARCHAR,    // 31 ddns_generated_prefix
            OID_VARCHAR,    // 32 ddns_qualifying_suffix
            OID_BOOL,       // 33 reservations_in_subnet
            OID_BOOL,       // 34 reservations_out_of_pool
            OID_TEXT,       // 35 cache_threshold - cast as float
            OID_INT8        // 36 cache_max_age"
        },
        "INSERT_SUBNET4",
        "INSERT INTO dhcp4_subnet("
        "  subnet_id,"
        "  subnet_prefix,"
        "  interface_4o6,"
        "  interface_id_4o6,"
        "  subnet_4o6,"
        "  boot_file_name,"
        "  client_class,"
        "  interface,"
        "  match_client_id,"
        "  modification_ts,"
        "  next_server,"
        "  rebind_timer,"
        "  relay,"
        "  renew_timer,"
        "  require_client_classes,"
        "  reservations_global,"
        "  server_hostname,"
        "  shared_network_name,"
        "  user_context,"
        "  valid_lifetime,"
        "  min_valid_lifetime,"
        "  max_valid_lifetime,"
        "  calculate_tee_times,"
        "  t1_percent,"
        "  t2_percent,"
        "  authoritative,"
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
            "$1, $2, $3, $4, $5, $6, $7, $8, $9, $10, "
            "cast($11 as inet), $12, $13, $14, $15, $16, $17, $18, cast($19 as json), $20, "
            "$21, $22, $23, cast($24 as float), cast($25 as float), $26, $27, $28, $29, $30, "
            "$31, $32, $33, $34, cast($35 as float), $36"
        ")"
    },

    // Insert association of the subnet with a server.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_SUBNET4_SERVER,
        3,
        {
            OID_INT8,       // 1 subnet_id
            OID_TIMESTAMP,  // 2 modification_ts
            OID_VARCHAR     // 3 server_tag
        },
        "INSERT_SUBNET4_SERVER",
        PGSQL_INSERT_SUBNET_SERVER(dhcp4)
    },

    // Insert pool for a subnet.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_POOL4,
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
        "INSERT_POOL4",
        PGSQL_INSERT_POOL(dhcp4)
    },

    // Insert a shared network.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_SHARED_NETWORK4,
        31,
        {
            OID_VARCHAR,    //  1 name,
            OID_VARCHAR,    //  2 client_class,
            OID_VARCHAR,    //  3 interface,
            OID_BOOL,       //  4 match_client_id,
            OID_TIMESTAMP,  //  5 modification_ts,
            OID_INT8,       //  6 rebind_timer,
            OID_TEXT,       //  7 relay,
            OID_INT8,       //  8 renew_timer,
            OID_TEXT,       //  9 require_client_classes,
            OID_BOOL,       // 10 reservations_global,
            OID_TEXT,       // 11 user_context,
            OID_INT8,       // 12 valid_lifetime,
            OID_INT8,       // 13 min_valid_lifetime,
            OID_INT8,       // 14 max_valid_lifetime,
            OID_BOOL,       // 15 calculate_tee_times,
            OID_TEXT,       // 16 t1_percent - cast as float
            OID_TEXT,       // 17 t2_percent - cast as float
            OID_BOOL,       // 18 authoritative,
            OID_VARCHAR,    // 19 boot_file_name,
            OID_TEXT,       // 20 next_server - cast as inet
            OID_VARCHAR,    // 21 server_hostname,
            OID_BOOL,       // 22 ddns_send_updates,
            OID_BOOL,       // 23 ddns_override_no_update,
            OID_BOOL,       // 24 ddns_override_client_update,
            OID_INT8,       // 25 ddns_replace_client_name,
            OID_VARCHAR,    // 26 ddns_generated_prefix,
            OID_VARCHAR,    // 27 ddns_qualifying_suffix,
            OID_BOOL,       // 28 reservations_in_subnet,
            OID_BOOL,       // 29 reservations_out_of_pool,
            OID_TEXT,       // 30 cache_threshold - cast as float
            OID_INT8        // 31 cache_max_age
        },
        "INSERT_SHARED_NETWORK4",
        "INSERT INTO dhcp4_shared_network("
        "  name,"
        "  client_class,"
        "  interface,"
        "  match_client_id,"
        "  modification_ts,"
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
        "  authoritative,"
        "  boot_file_name,"
        "  next_server,"
        "  server_hostname,"
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
            "$1, $2, $3, $4, $5, $6, $7, $8, $9, $10,"
            "cast($11 as json), $12, $13, $14, $15, "
            "cast($16 as float), cast($17 as float), $18, $19, cast($20 as inet), "
            "$21, $22, $23, $24, $25, $26, $27, $28, $29, cast($30 as float), $31"
        ")"
    },

    // Insert association of the shared network with a server.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_SHARED_NETWORK4_SERVER,
        3,
        {
            OID_VARCHAR,    // 1 shared_network_name
            OID_TIMESTAMP,  // 2 modification_ts
            OID_VARCHAR     // 3 server_tag
        },
        "INSERT_SHARED_NETWORK4_SERVER",
        PGSQL_INSERT_SHARED_NETWORK_SERVER(dhcp4)
    },

    // Insert option definition.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION_DEF4,
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
        "INSERT_OPTION_DEF4",
        PGSQL_INSERT_OPTION_DEF(dhcp4)
    },

    // Insert option definition for client class.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION_DEF4_CLIENT_CLASS,
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
        "INSERT_OPTION_DEF4_CLIENT_CLASS",
        PGSQL_INSERT_OPTION_DEF_CLIENT_CLASS(dhcp4)
    },

    // Insert association of the option definition with a server.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION_DEF4_SERVER,
        3,
        {
            OID_INT8,       // 1 option_def_id
            OID_TIMESTAMP,  // 2 modification_ts
            OID_VARCHAR     // 3 server_tag
        },
        "INSERT_OPTION_DEF4_SERVER",
        PGSQL_INSERT_OPTION_DEF_SERVER(dhcp4)
    },

    // Insert subnet specific option.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION4,
        12,
        {
            OID_INT2,       //  1 code
            OID_BYTEA,      //  2 value
            OID_TEXT,       //  3 formatted_value
            OID_VARCHAR,    //  4 space
            OID_BOOL,       //  5 persistent
            OID_VARCHAR,    //  6 dhcp_client_class
            OID_INT8,       //  7 dhcp4_subnet_id
            OID_INT2,       //  8 scope_id
            OID_TEXT,       //  9 user_context
            OID_VARCHAR,    // 10 shared_network_name
            OID_INT8,       // 11 pool_id
            OID_TIMESTAMP   // 12 modification_ts
        },
        "INSERT_OPTION4",
        PGSQL_INSERT_OPTION4()
    },

    // Insert association of the DHCP option with a server.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION4_SERVER,
        3,
        {
            OID_INT8,       // 1 option_id
            OID_TIMESTAMP,  // 2 modification_ts
            OID_VARCHAR     // 3 server_tag
        },
        "INSERT_OPTION4_SERVER",
        PGSQL_INSERT_OPTION_SERVER(dhcp4)
    },

    // Insert client class.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_CLIENT_CLASS4,
        13,
        {
            OID_VARCHAR,    //  1 name
            OID_TEXT,       //  2 test
            OID_TEXT,       //  3 next_server - cast as inet
            OID_VARCHAR,    //  4 server_hostname
            OID_VARCHAR,    //  5 boot_file_name
            OID_BOOL,       //  6 only_if_required
            OID_INT8,       //  7 valid_lifetime
            OID_INT8,       //  8 min_valid_lifetime
            OID_INT8,       //  9 max_valid_lifetime
            OID_BOOL,       // 10 depend_on_known_directly
            OID_VARCHAR,    // 11 follow_class_name
            OID_TIMESTAMP,  // 12 modification_ts
            OID_TEXT        // 13 user_context cast as JSON
        },
        "INSERT_CLIENT_CLASS4",
        "INSERT INTO dhcp4_client_class("
        "  name,"
        "  test,"
        "  next_server,"
        "  server_hostname,"
        "  boot_file_name,"
        "  only_if_required,"
        "  valid_lifetime,"
        "  min_valid_lifetime,"
        "  max_valid_lifetime,"
        "  depend_on_known_directly,"
        "  follow_class_name,"
        "  modification_ts, "
        "  user_context "
        ") VALUES ("
            "$1, $2, cast($3 as inet), $4, $5, $6, $7, $8, $9, $10, $11, $12, cast($13 as JSON)"
        ")"
    },

    // Insert association of a client class with a server.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_CLIENT_CLASS4_SERVER,
        3,
        {
            OID_VARCHAR,    // 1 class_name
            OID_TIMESTAMP,  // 2 modification_ts
            OID_VARCHAR     // 3 server_tag
        },
        "INSERT_CLIENT_CLASS4_SERVER",
        PGSQL_INSERT_CLIENT_CLASS_SERVER(dhcp4)
    },

    // Insert client class dependency.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_CLIENT_CLASS4_DEPENDENCY,
        2,
        {
            OID_VARCHAR,    // class name
            OID_VARCHAR     // dependency class name
        },
        "INSERT_CLIENT_CLASS4_DEPENDENCY",
        PGSQL_INSERT_CLIENT_CLASS_DEPENDENCY(dhcp4)
    },

    // Insert server with server tag and description.
    {
        // PgSqlConfigBackendDHCPv4Impl::INSERT_SERVER4,
        3,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_VARCHAR,    // 2 description
            OID_TIMESTAMP   // 3 modification_ts
        },
        "INSERT_SERVER4",
        PGSQL_INSERT_SERVER(dhcp4)
    },

    // Update existing global parameter.
    {
        // PgSqlConfigBackendDHCPv4Impl::UPDATE_GLOBAL_PARAMETER4,
        6,
        {
            OID_VARCHAR,    // 1 name
            OID_TEXT,       // 2 value
            OID_INT2,       // 3 parameter_type
            OID_TIMESTAMP,  // 4 modification_ts
            OID_VARCHAR,    // 5 server_tag
            OID_VARCHAR,    // 6 name (of global to update)
        },
        "UPDATE_GLOBAL_PARAMETER4",
        PGSQL_UPDATE_GLOBAL_PARAMETER(dhcp4)
    },

    // Update existing subnet.
    {
        // PgSqlConfigBackendDHCPv4Impl::UPDATE_SUBNET4,
        38,
        {
            OID_INT8,       //  1 subnet_id,
            OID_VARCHAR,    //  2 subnet_prefix
            OID_VARCHAR,    //  3 interface_4o6
            OID_VARCHAR,    //  4 interface_id_4o6
            OID_VARCHAR,    //  5 subnet_4o6
            OID_VARCHAR,    //  6 boot_file_name
            OID_VARCHAR,    //  7 client_class
            OID_VARCHAR,    //  8 interface
            OID_BOOL,       //  9 match_client_id
            OID_TIMESTAMP,  // 10 modification_ts
            OID_TEXT,       // 11 next_server - cast as inet
            OID_INT8,       // 12 rebind_timer
            OID_TEXT,       // 13 relay
            OID_INT8,       // 14 renew_timer
            OID_TEXT,       // 15 require_client_classes
            OID_BOOL,       // 16 reservations_global
            OID_VARCHAR,    // 17 server_hostname
            OID_VARCHAR,    // 18 shared_network_name
            OID_TEXT,       // 19 user_context
            OID_INT8,       // 20 valid_lifetime
            OID_INT8,       // 21 min_valid_lifetime
            OID_INT8,       // 22 max_valid_lifetime
            OID_BOOL,       // 23 calculate_tee_times
            OID_TEXT,       // 24 t1_percent - cast as float
            OID_TEXT,       // 25 t2_percent - cast as float
            OID_BOOL,       // 26 authoritative
            OID_BOOL,       // 27 ddns_send_updates
            OID_BOOL,       // 28 ddns_override_no_update
            OID_BOOL,       // 29 ddns_override_client_update
            OID_INT8,       // 30 ddns_replace_client_name
            OID_VARCHAR,    // 31 ddns_generated_prefix
            OID_VARCHAR,    // 32 ddns_qualifying_suffix
            OID_BOOL,       // 33 reservations_in_subnet
            OID_BOOL,       // 34 reservations_out_of_pool
            OID_TEXT,       // 35 cache_threshold - cast as float
            OID_INT8,       // 36 cache_max_age"
            OID_INT8,       // 37 subnet_id (of subnet to update)
            OID_VARCHAR     // 38 subnet_prefix (of subnet to update)
        },
        "UPDATE_SUBNET4,",
        "UPDATE dhcp4_subnet SET"
        "  subnet_id = $1,"
        "  subnet_prefix = $2,"
        "  interface_4o6 = $3,"
        "  interface_id_4o6 = $4,"
        "  subnet_4o6 = $5,"
        "  boot_file_name = $6,"
        "  client_class = $7,"
        "  interface = $8,"
        "  match_client_id = $9,"
        "  modification_ts = $10,"
        "  next_server = cast($11 as inet),"
        "  rebind_timer = $12,"
        "  relay = $13,"
        "  renew_timer = $14,"
        "  require_client_classes = $15,"
        "  reservations_global = $16,"
        "  server_hostname = $17,"
        "  shared_network_name = $18,"
        "  user_context = cast($19 as json),"
        "  valid_lifetime = $20,"
        "  min_valid_lifetime = $21,"
        "  max_valid_lifetime = $22,"
        "  calculate_tee_times = $23,"
        "  t1_percent = cast($24 as float),"
        "  t2_percent = cast($25 as float),"
        "  authoritative = $26,"
        "  ddns_send_updates = $27,"
        "  ddns_override_no_update = $28,"
        "  ddns_override_client_update = $29,"
        "  ddns_replace_client_name = $30,"
        "  ddns_generated_prefix = $31,"
        "  ddns_qualifying_suffix = $32,"
        "  reservations_in_subnet = $33,"
        "  reservations_out_of_pool = $34,"
        "  cache_threshold = cast($35 as float),"
        "  cache_max_age = $36 "
        "WHERE subnet_id = $37 OR subnet_prefix = $38"
    },

    // Update existing shared network.
    {
        // PgSqlConfigBackendDHCPv4Impl::UPDATE_SHARED_NETWORK4,
        32,
        {
            OID_VARCHAR,    //  1 name,
            OID_VARCHAR,    //  2 client_class,
            OID_VARCHAR,    //  3 interface,
            OID_BOOL,       //  4 match_client_id,
            OID_TIMESTAMP,  //  5 modification_ts,
            OID_INT8,       //  6 rebind_timer,
            OID_TEXT,       //  7 relay,
            OID_INT8,       //  8 renew_timer,
            OID_TEXT,       //  9 require_client_classes,
            OID_BOOL,       // 10 reservations_global,
            OID_TEXT,       // 11 user_context,
            OID_INT8,       // 12 valid_lifetime,
            OID_INT8,       // 13 min_valid_lifetime,
            OID_INT8,       // 14 max_valid_lifetime,
            OID_BOOL,       // 15 calculate_tee_times,
            OID_TEXT,       // 16 t1_percent - cast as float
            OID_TEXT,       // 17 t2_percent - cast as float
            OID_BOOL,       // 18 authoritative,
            OID_VARCHAR,    // 19 boot_file_name,
            OID_TEXT,       // 20 next_server - cast as inet
            OID_VARCHAR,    // 21 server_hostname,
            OID_BOOL,       // 22 ddns_send_updates,
            OID_BOOL,       // 23 ddns_override_no_update,
            OID_BOOL,       // 24 ddns_override_client_update,
            OID_INT8,       // 25 ddns_replace_client_name,
            OID_VARCHAR,    // 26 ddns_generated_prefix,
            OID_VARCHAR,    // 27 ddns_qualifying_suffix,
            OID_BOOL,       // 28 reservations_in_subnet,
            OID_BOOL,       // 29 reservations_out_of_pool,
            OID_TEXT,       // 30 cache_threshold - cast as float
            OID_INT8,       // 31 cache_max_age
            OID_VARCHAR     // 32 name (of network to update)
        },
        "UPDATE_SHARED_NETWORK4",
        "UPDATE dhcp4_shared_network SET"
        "  name = $1,"
        "  client_class = $2,"
        "  interface = $3,"
        "  match_client_id = $4,"
        "  modification_ts = $5,"
        "  rebind_timer = $6,"
        "  relay = $7,"
        "  renew_timer = $8,"
        "  require_client_classes = $9,"
        "  reservations_global = $10,"
        "  user_context = cast($11 as json),"
        "  valid_lifetime = $12,"
        "  min_valid_lifetime = $13,"
        "  max_valid_lifetime = $14,"
        "  calculate_tee_times = $15,"
        "  t1_percent = cast($16 as float),"
        "  t2_percent = cast($17 as float),"
        "  authoritative = $18,"
        "  boot_file_name = $19,"
        "  next_server = cast($20 as inet),"
        "  server_hostname = $21,"
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
        // PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION_DEF4,
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
        "UPDATE_OPTION_DEF4",
        PGSQL_UPDATE_OPTION_DEF(dhcp4)
    },

    // Update existing client class option definition.
    {
        // PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION_DEF4_CLIENT_CLASS,
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
        "UPDATE_OPTION_DEF4_CLIENT_CLASS",
        PGSQL_UPDATE_OPTION_DEF_CLIENT_CLASS(dhcp4)
    },

    // Update existing global option.
    {
        // PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION4,
        15,
        {
            OID_INT2,       //  1 code
            OID_BYTEA,      //  2 value
            OID_TEXT,       //  3 formatted_value
            OID_VARCHAR,    //  4 space
            OID_BOOL,       //  5 persistent
            OID_VARCHAR,    //  6 dhcp_client_class
            OID_INT8,       //  7 dhcp4_subnet_id
            OID_INT2,       //  8 scope_id
            OID_TEXT,       //  9 user_context
            OID_VARCHAR,    // 10 shared_network_name
            OID_INT8,       // 11 pool_id
            OID_TIMESTAMP,  // 12 modification_ts
            OID_VARCHAR,    // 13 server_tag
            OID_INT2,       // 14 code (of option to update)
            OID_VARCHAR,    // 15 space (of option to update)
        },
        "UPDATE_OPTION4",
        PGSQL_UPDATE_OPTION4_WITH_TAG(AND o.scope_id = 0 AND o.code = $14 AND o.space = $15)
    },

    // Update existing subnet level option.
    {
        // PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_SUBNET_ID,
        15,
        {
            OID_INT2,       //  1 code
            OID_BYTEA,      //  2 value
            OID_TEXT,       //  3 formatted_value
            OID_VARCHAR,    //  4 space
            OID_BOOL,       //  5 persistent
            OID_VARCHAR,    //  6 dhcp_client_class
            OID_INT8,       //  7 dhcp4_subnet_id
            OID_INT2,       //  8 scope_id
            OID_TEXT,       //  9 user_context
            OID_VARCHAR,    // 10 shared_network_name
            OID_INT8,       // 11 pool_id
            OID_TIMESTAMP,  // 12 modification_ts
            OID_INT8,       // 13 subnet_id (of option to update)
            OID_INT2,       // 14 code (of option to update)
            OID_VARCHAR     // 15 space (of option to update)
        },
        "UPDATE_OPTION4_SUBNET_ID",
        PGSQL_UPDATE_OPTION4_NO_TAG(o.scope_id = 1 AND o.dhcp4_subnet_id = $13 AND o.code = $14 AND o.space = $15)
    },

    // Update existing pool level option.
    {
        // PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_POOL_ID,
        15,
        {
            OID_INT2,       //  1 code
            OID_BYTEA,      //  2 value
            OID_TEXT,       //  3 formatted_value
            OID_VARCHAR,    //  4 space
            OID_BOOL,       //  5 persistent
            OID_VARCHAR,    //  6 dhcp_client_class
            OID_INT8,       //  7 dhcp4_subnet_id
            OID_INT2,       //  8 scope_id
            OID_TEXT,       //  9 user_context
            OID_VARCHAR,    // 10 shared_network_name
            OID_INT8,       // 11 pool_id
            OID_TIMESTAMP,  // 12 modification_ts
            OID_INT8,       // 13 pool_id (of option to update)
            OID_INT2,       // 14 code (of option to update)
            OID_VARCHAR     // 15 space (of option to update)
        },
        "UPDATE_OPTION4_POOL_ID",
        PGSQL_UPDATE_OPTION4_NO_TAG(o.scope_id = 5 AND o.pool_id = $13 AND o.code = $14 AND o.space = $15)
    },

    // Update existing shared network level option.
    {
        // PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_SHARED_NETWORK,
        15,
        {
            OID_INT2,       //  1 code
            OID_BYTEA,      //  2 value
            OID_TEXT,       //  3 formatted_value
            OID_VARCHAR,    //  4 space
            OID_BOOL,       //  5 persistent
            OID_VARCHAR,    //  6 dhcp_client_class
            OID_INT8,       //  7 dhcp4_subnet_id
            OID_INT2,       //  8 scope_id
            OID_TEXT,       //  9 user_context
            OID_VARCHAR,    // 10 shared_network_name
            OID_INT8,       // 11 pool_id
            OID_TIMESTAMP,  // 12 modification_ts
            OID_VARCHAR,    // 13 shared_network_name (of option to update)
            OID_INT2,       // 14 code (of option to update)
            OID_VARCHAR     // 15 space (of option to update)
        },
        "UPDATE_OPTION4_SHARED_NETWORK",
        PGSQL_UPDATE_OPTION4_NO_TAG(o.scope_id = 4 AND o.shared_network_name = $13 AND o.code = $14 AND o.space = $15)
    },

    // Update existing client class level option.
    {
        // PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_CLIENT_CLASS,
        15,
        {
            OID_INT2,       //  1 code
            OID_BYTEA,      //  2 value
            OID_TEXT,       //  3 formatted_value
            OID_VARCHAR,    //  4 space
            OID_BOOL,       //  5 persistent
            OID_VARCHAR,    //  6 dhcp_client_class
            OID_INT8,       //  7 dhcp4_subnet_id
            OID_INT2,       //  8 scope_id
            OID_TEXT,       //  9 user_context
            OID_VARCHAR,    // 10 shared_network_name
            OID_INT8,       // 11 pool_id
            OID_TIMESTAMP,  // 12 modification_ts
            OID_VARCHAR,    // 13 dhcp_client_class (of option to update)
            OID_INT2,       // 14 code (of option to update)
            OID_VARCHAR,    // 15 space (of option to update)
        },
        "UPDATE_OPTION4_CLIENT_CLASS",
        PGSQL_UPDATE_OPTION4_NO_TAG(o.scope_id = 2 AND o.dhcp_client_class = $13 AND o.code = $14 AND o.space = $15)
    },

    // Update existing client class with specifying its position.
    {
        // PgSqlConfigBackendDHCPv4Impl::UPDATE_CLIENT_CLASS4,
        14,
        {
            OID_VARCHAR,    //  1 name
            OID_TEXT,       //  2 test
            OID_TEXT,       //  3 next_server - cast as inet
            OID_VARCHAR,    //  4 server_hostname
            OID_VARCHAR,    //  5 boot_file_name
            OID_BOOL,       //  6 only_if_required
            OID_INT8,       //  7 valid_lifetime
            OID_INT8,       //  8 min_valid_lifetime
            OID_INT8,       //  9 max_valid_lifetime
            OID_BOOL,       // 10 depend_on_known_directly
            OID_VARCHAR,    // 11 follow_class_name
            OID_TIMESTAMP,  // 12 modification_ts
            OID_TEXT,       // 13 user_context cast as JSON
            OID_VARCHAR     // 14 name (of class to update)
        },
        "UPDATE_CLIENT_CLASS4",
        PGSQL_UPDATE_CLIENT_CLASS4("follow_class_name = $11,")
    },

    // Update existing client class without specifying its position.
    {
        // PgSqlConfigBackendDHCPv4Impl::UPDATE_CLIENT_CLASS4_SAME_POSITION,
        14,
        {
            OID_VARCHAR,    //  1 name
            OID_TEXT,       //  2 test
            OID_TEXT,       //  3 next_server - cast as inet
            OID_VARCHAR,    //  4 server_hostname
            OID_VARCHAR,    //  5 boot_file_name
            OID_BOOL,       //  6 only_if_required
            OID_INT8,       //  7 valid_lifetime
            OID_INT8,       //  8 min_valid_lifetime
            OID_INT8,       //  9 max_valid_lifetime
            OID_BOOL,       // 10 depend_on_known_directly
            OID_VARCHAR,    // 11 follow_class_name
            OID_TIMESTAMP,  // 12 modification_ts
            OID_TEXT,       // 13 user_context cast as JSON
            OID_VARCHAR     // 14 name (of class to update)
        },
        "UPDATE_CLIENT_CLASS4_SAME_POSITION",
        PGSQL_UPDATE_CLIENT_CLASS4("")
    },

    // Update existing server, e.g. server description.
    {
        // PgSqlConfigBackendDHCPv4Impl::UPDATE_SERVER4,
        4,
        {
            OID_VARCHAR,    // 1 tag
            OID_VARCHAR,    // 2 description
            OID_TIMESTAMP,  // 3 modification_ts
            OID_VARCHAR     // 4 tag (of server to update)
        },
        "UPDATE_SERVER4",
        PGSQL_UPDATE_SERVER(dhcp4)
    },

    // Delete global parameter by name.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_GLOBAL_PARAMETER4,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_VARCHAR     // 2 name of parameter
        },
        "DELETE_GLOBAL_PARAMETER4",
        PGSQL_DELETE_GLOBAL_PARAMETER(dhcp4, AND g.name = $2)
    },

    // Delete all global parameters.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_GLOBAL_PARAMETERS4,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "DELETE_ALL_GLOBAL_PARAMETERS4",
        PGSQL_DELETE_GLOBAL_PARAMETER(dhcp4)
    },

    // Delete all global parameters which are unassigned to any servers.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_GLOBAL_PARAMETERS4_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "DELETE_ALL_GLOBAL_PARAMETERS4_UNASSIGNED",
        PGSQL_DELETE_GLOBAL_PARAMETER_UNASSIGNED(dhcp4)
    },

    // Delete subnet by id with specifying server tag.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_ID_WITH_TAG,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_INT8        // 2 subnet_id
        },
        "DELETE_SUBNET4_ID_WITH_TAG",
        PGSQL_DELETE_SUBNET_WITH_TAG(dhcp4, AND s.subnet_id = $2)
    },

    // Delete subnet by id without specifying server tag.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_ID_ANY,
        1,
        {
            OID_INT8    // 1 subnet_id
        },
        "DELETE_SUBNET4_ID_ANY",
        PGSQL_DELETE_SUBNET_ANY(dhcp4, WHERE s.subnet_id = $1)
    },

    // Delete subnet by prefix with specifying server tag.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_PREFIX_WITH_TAG,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_VARCHAR     // 2 subnet_prefix
        },
        "DELETE_SUBNET4_PREFIX_WITH_TAG",
        PGSQL_DELETE_SUBNET_WITH_TAG(dhcp4, AND s.subnet_prefix = $2)
    },

    // Delete subnet by prefix without specifying server tag.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_PREFIX_ANY,
        1,
        {
            OID_VARCHAR // 1 subnet_prefix
        },
        "DELETE_SUBNET4_PREFIX_ANY",
        PGSQL_DELETE_SUBNET_ANY(dhcp4, WHERE s.subnet_prefix = $1)
    },

    // Delete all subnets.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "DELETE_ALL_SUBNETS4",
        PGSQL_DELETE_SUBNET_WITH_TAG(dhcp4)
    },

    // Delete all unassigned subnets.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "DELETE_ALL_SUBNETS4_UNASSIGNED",
        PGSQL_DELETE_SUBNET_UNASSIGNED(dhcp4)
    },

    // Delete all subnets for a shared network.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4_SHARED_NETWORK_NAME,
        1,
        {
            OID_VARCHAR // 1 shared_network_name
        },
        "DELETE_ALL_SUBNETS4_SHARED_NETWORK_NAME",
        PGSQL_DELETE_SUBNET_ANY(dhcp4, WHERE s.shared_network_name = $1)
    },

    // Delete associations of a subnet with server.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_SERVER,
        1,
        {
            OID_INT8    // 1 subnet_id
        },
        "DELETE_SUBNET4_SERVER",
        PGSQL_DELETE_SUBNET_SERVER(dhcp4),
    },

    // Delete pools for a subnet.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_POOLS4,
        2,
        {
            OID_INT8,   // 1 subnet_id
            OID_VARCHAR // 2 subnet_prefix
        },
        "DELETE_POOLS4",
        PGSQL_DELETE_POOLS(dhcp4)
    },

    // Delete shared network by name with specifying server tag.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_SHARED_NETWORK4_NAME_WITH_TAG,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_VARCHAR     // 2 shared_network_name
        },
        "DELETE_SHARED_NETWORK4_NAME_WITH_TAG",
        PGSQL_DELETE_SHARED_NETWORK_WITH_TAG(dhcp4, AND n.name = $2)
    },

    // Delete shared network by name without specifying server tag.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_SHARED_NETWORK4_NAME_ANY,
        1,
        {
            OID_VARCHAR // 1 shared_network_name
        },
        "DELETE_SHARED_NETWORK4_NAME_ANY",
        PGSQL_DELETE_SHARED_NETWORK_ANY(dhcp4, WHERE n.name = $1)
    },

    // Delete all shared networks.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SHARED_NETWORKS4,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "DELETE_ALL_SHARED_NETWORKS4",
        PGSQL_DELETE_SHARED_NETWORK_WITH_TAG(dhcp4)
    },

    // Delete all unassigned shared networks.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SHARED_NETWORKS4_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "DELETE_ALL_SHARED_NETWORKS4_UNASSIGNED",
        PGSQL_DELETE_SHARED_NETWORK_UNASSIGNED(dhcp4)
    },

    // Delete associations of a shared network with server.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_SHARED_NETWORK4_SERVER,
        1,
        {
            OID_VARCHAR // 1 shared_network_name
        },
        "DELETE_SHARED_NETWORK4_SERVER",
        PGSQL_DELETE_SHARED_NETWORK_SERVER(dhcp4)
    },

    // Delete option definition.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION_DEF4_CODE_NAME,
        3,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_INT2,       // 2 code
            OID_VARCHAR     // 3 space
        },
        "DELETE_OPTION_DEF4_CODE_NAME",
        PGSQL_DELETE_OPTION_DEF(dhcp4, AND code = $2 AND space = $3)
    },

    // Delete all option definitions.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_OPTION_DEFS4,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "DELETE_ALL_OPTION_DEFS4",
        PGSQL_DELETE_OPTION_DEF(dhcp4)
    },

    // Delete all option definitions which are assigned to no servers.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_OPTION_DEFS4_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "DELETE_ALL_OPTION_DEFS4_UNASSIGNED",
        PGSQL_DELETE_OPTION_DEF_UNASSIGNED(dhcp4)
    },

    // Delete client class specific option definitions.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION_DEFS4_CLIENT_CLASS,
        1,
        {
            OID_VARCHAR // 1 class name
        },
        "DELETE_OPTION_DEFS4_CLIENT_CLASS",
        PGSQL_DELETE_OPTION_DEFS_CLIENT_CLASS(dhcp4)
    },

    // Delete single global option.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION4,
        3,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_INT2,       // 2 code
            OID_VARCHAR     // 3 space
        },
        "DELETE_OPTION4",
        PGSQL_DELETE_OPTION_WITH_TAG(dhcp4, AND o.scope_id = 0 AND o.code = $2 AND o.space = $3)
    },

    // Delete all global options which are unassigned to any servers.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_GLOBAL_OPTIONS4_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "DELETE_ALL_GLOBAL_OPTIONS4_UNASSIGNED",
        PGSQL_DELETE_OPTION_UNASSIGNED(dhcp4, AND o.scope_id = 0)
    },

    // Delete single option from a subnet.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION4_SUBNET_ID,
        3,
        {
            OID_INT8,   // 1 subnet_id
            OID_INT2,   // 2 code
            OID_VARCHAR // 3 space
        },
        "DELETE_OPTION4_SUBNET_ID",
        PGSQL_DELETE_OPTION_NO_TAG(dhcp4,
            WHERE o.scope_id = 1 AND o.dhcp4_subnet_id = $1 AND o.code = $2 AND o.space = $3)
    },

    // Delete single option from a pool.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION4_POOL_RANGE,
        4,
        {
            OID_TEXT,   // 1 start_address - cast as inet
            OID_TEXT,   // 2 start_address - cast as inet
            OID_INT2,   // 3 code
            OID_VARCHAR // 4 space
        },
        "DELETE_OPTION4_POOL_RANGE",
        PGSQL_DELETE_OPTION_POOL_RANGE(dhcp4, o.scope_id = 5 AND o.code = $3 AND o.space = $4)
    },

    // Delete single option from a shared network.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION4_SHARED_NETWORK,
        3,
        {
            OID_VARCHAR,    // 1 shared_network_name
            OID_INT2,       // 2 code
            OID_VARCHAR     // 3 space
        },
        "DELETE_OPTION4_SHARED_NETWORK",
        PGSQL_DELETE_OPTION_NO_TAG(dhcp4,
            WHERE o.scope_id = 4 AND o.shared_network_name = $1 AND o.code = $2 AND o.space = $3)
    },

    // Delete options belonging to a subnet.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_OPTIONS4_SUBNET_ID_PREFIX,
        2,
        {
            OID_INT8,   // 1 subnet_id
            OID_VARCHAR // 2 subnet_prefix
        },
        "DELETE_OPTIONS4_SUBNET_ID_PREFIX",
        PGSQL_DELETE_OPTION_SUBNET_ID_PREFIX(dhcp4)
    },

    // Delete options belonging to a shared_network.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_OPTIONS4_SHARED_NETWORK,
        1,
        {
            OID_VARCHAR // shared_network_name
        },
        "DELETE_OPTIONS4_SHARED_NETWORK",
        PGSQL_DELETE_OPTION_NO_TAG(dhcp4, WHERE o.scope_id = 4 AND o.shared_network_name = $1)
    },

    // Delete options belonging to a client class.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_OPTIONS4_CLIENT_CLASS,
        1,
        {
            OID_VARCHAR // dhcp_client_class
        },
        "DELETE_OPTIONS4_CLIENT_CLASS",
        PGSQL_DELETE_OPTION_NO_TAG(dhcp4, WHERE o.scope_id = 2 AND o.dhcp_client_class = $1)
    },

    // Delete all dependencies of a client class.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_CLIENT_CLASS4_DEPENDENCY,
        1,
        {
            OID_VARCHAR, // 1 class name
        },
        "DELETE_CLIENT_CLASS4_DEPENDENCY",
        PGSQL_DELETE_CLIENT_CLASS_DEPENDENCY(dhcp4)
    },

    // Delete associations of a client class with server.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_CLIENT_CLASS4_SERVER,
        1,
        {
            OID_VARCHAR // 1 class name
        },
        "DELETE_CLIENT_CLASS4_SERVER",
        PGSQL_DELETE_CLIENT_CLASS_SERVER(dhcp4),
    },

    // Delete all client classes.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_CLIENT_CLASSES4,
        1,
        {
            OID_VARCHAR // 1 server_tag
        },
        "DELETE_ALL_CLIENT_CLASSES4",
        PGSQL_DELETE_CLIENT_CLASS_WITH_TAG(dhcp4)
    },

    // Delete all unassigned client classes.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_CLIENT_CLASSES4_UNASSIGNED,
        0,
        {
            OID_NONE
        },
        "DELETE_ALL_CLIENT_CLASSES4_UNASSIGNED",
        PGSQL_DELETE_CLIENT_CLASS_UNASSIGNED(dhcp4)
    },

    // Delete specified client class.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_CLIENT_CLASS4,
        2,
        {
            OID_VARCHAR,    // 1 server_tag
            OID_VARCHAR     // 2 name
        },
        "DELETE_CLIENT_CLASS4",
        PGSQL_DELETE_CLIENT_CLASS_WITH_TAG(dhcp4, AND name = $2)
    },

    // Delete any client class with a given name.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_CLIENT_CLASS4_ANY,
        1,
        {
            OID_VARCHAR     // 1 name
        },
        "DELETE_CLIENT_CLASS4_ANY",
        PGSQL_DELETE_CLIENT_CLASS_ANY(dhcp4, AND name = $1)
    },

    // Delete a server by tag.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_SERVER4,
        1,
        {
            OID_VARCHAR // server_tag
        },
        "DELETE_SERVER4",
        PGSQL_DELETE_SERVER(dhcp4)
    },

    // Deletes all servers except logical server 'all'.
    {
        // PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SERVERS4,
        0,
        {
            OID_NONE
        },
        "DELETE_ALL_SERVERS4",
        PGSQL_DELETE_ALL_SERVERS(dhcp4)
    },

    // Fetches the last sequence id for the given table and column.
    {
        // PgSqlConfigBackendDHCPv4Impl::GET_LAST_INSERT_ID4,
        // args are: table name, sequence column name
        2,
        {
            OID_VARCHAR,
            OID_VARCHAR
        },
        "GET_LAST_INSERT_ID4",
        "SELECT CURRVAL(PG_GET_SERIAL_SEQUENCE($1, $2))"
    }
}
};

} // end anonymous namespace

PgSqlConfigBackendDHCPv4Impl::PgSqlConfigBackendDHCPv4Impl(const DatabaseConnection::ParameterMap& parameters)
    : PgSqlConfigBackendImpl(parameters, &PgSqlConfigBackendDHCPv4Impl::dbReconnect,
      PgSqlConfigBackendDHCPv4Impl::GET_LAST_INSERT_ID4) {
    // Prepare query statements. Those are will be only used to retrieve
    // information from the database, so they can be used even if the
    // database is read only for the current user.
    conn_.prepareStatements(tagged_statements.begin(),
                            tagged_statements.end());
// @todo As part of enabling read-only CB access, statements need to
// be limited:
//                            tagged_statements.begin() + WRITE_STMTS_BEGIN);

    // Create unique timer name per instance.
    timer_name_ = "PgSqlConfigBackend4[";
    timer_name_ += boost::lexical_cast<std::string>(reinterpret_cast<uint64_t>(this));
    timer_name_ += "]DbReconnectTimer";

    // Create ReconnectCtl for this connection.
    conn_.makeReconnectCtl(timer_name_);
}

PgSqlConfigBackendDHCPv4Impl::~PgSqlConfigBackendDHCPv4Impl() {
}

PgSqlTaggedStatement&
PgSqlConfigBackendDHCPv4Impl::getStatement(size_t index) const {
    if (index >= tagged_statements.size()) {
        isc_throw(BadValue, "PgSqlConfigBackendDHCPv4Impl::getStatement index: "
                  << index << ", is invalid");
    }

    return(tagged_statements[index]);
}

PgSqlConfigBackendDHCPv4::PgSqlConfigBackendDHCPv4(const DatabaseConnection::ParameterMap& parameters)
    : impl_(new PgSqlConfigBackendDHCPv4Impl(parameters)), base_impl_(impl_) {
}

bool
PgSqlConfigBackendDHCPv4::isUnusable() {
    return (impl_->conn_.isUnusable());
}

DatabaseConnection::ParameterMap
PgSqlConfigBackendDHCPv4::getParameters() const {
    return (impl_->getParameters());
}

Subnet4Ptr
PgSqlConfigBackendDHCPv4::getSubnet4(const ServerSelector& server_selector,
                                     const std::string& subnet_prefix) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SUBNET4_BY_PREFIX)
        .arg(subnet_prefix);
    return (impl_->getSubnet4(server_selector, subnet_prefix));
}

Subnet4Ptr
PgSqlConfigBackendDHCPv4::getSubnet4(const ServerSelector& server_selector,
                                     const SubnetID& subnet_id) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SUBNET4_BY_SUBNET_ID)
        .arg(subnet_id);
    return (impl_->getSubnet4(server_selector, subnet_id));
}

Subnet4Collection
PgSqlConfigBackendDHCPv4::getAllSubnets4(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SUBNETS4);
    Subnet4Collection subnets;
    impl_->getAllSubnets4(server_selector, subnets);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SUBNETS4_RESULT)
        .arg(subnets.size());
    return (subnets);
}

Subnet4Collection
PgSqlConfigBackendDHCPv4::getModifiedSubnets4(const ServerSelector& server_selector,
                                              const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SUBNETS4)
        .arg(util::ptimeToText(modification_time));
    Subnet4Collection subnets;
    impl_->getModifiedSubnets4(server_selector, modification_time, subnets);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SUBNETS4_RESULT)
        .arg(subnets.size());
    return (subnets);
}

Subnet4Collection
PgSqlConfigBackendDHCPv4::getSharedNetworkSubnets4(const ServerSelector& /* server_selector */,
                                                   const std::string& shared_network_name) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SHARED_NETWORK_SUBNETS4)
        .arg(shared_network_name);
    Subnet4Collection subnets;
    impl_->getSharedNetworkSubnets4(ServerSelector::ANY(), shared_network_name, subnets);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SHARED_NETWORK_SUBNETS4_RESULT)
        .arg(subnets.size());
    return (subnets);
}

SharedNetwork4Ptr
PgSqlConfigBackendDHCPv4::getSharedNetwork4(const ServerSelector& server_selector,
                                            const std::string& name) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SHARED_NETWORK4)
        .arg(name);
    return (impl_->getSharedNetwork4(server_selector, name));
}

SharedNetwork4Collection
PgSqlConfigBackendDHCPv4::getAllSharedNetworks4(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SHARED_NETWORKS4);
    SharedNetwork4Collection shared_networks;
    impl_->getAllSharedNetworks4(server_selector, shared_networks);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SHARED_NETWORKS4_RESULT)
        .arg(shared_networks.size());
    return (shared_networks);
}

SharedNetwork4Collection
PgSqlConfigBackendDHCPv4::getModifiedSharedNetworks4(const ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS4)
        .arg(util::ptimeToText(modification_time));
    SharedNetwork4Collection shared_networks;
    impl_->getModifiedSharedNetworks4(server_selector, modification_time, shared_networks);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS4_RESULT)
        .arg(shared_networks.size());
    return (shared_networks);
}

OptionDefinitionPtr
PgSqlConfigBackendDHCPv4::getOptionDef4(const ServerSelector& server_selector,
                                        const uint16_t code,
                                        const std::string& space) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_OPTION_DEF4)
        .arg(code).arg(space);
    return (impl_->getOptionDef(PgSqlConfigBackendDHCPv4Impl::GET_OPTION_DEF4_CODE_SPACE,
                                server_selector, code, space));
}

OptionDefContainer
PgSqlConfigBackendDHCPv4::getAllOptionDefs4(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTION_DEFS4);
    OptionDefContainer option_defs;
    impl_->getAllOptionDefs(PgSqlConfigBackendDHCPv4Impl::GET_ALL_OPTION_DEFS4,
                            server_selector, option_defs);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTION_DEFS4_RESULT)
        .arg(option_defs.size());
    return (option_defs);
}

OptionDefContainer
PgSqlConfigBackendDHCPv4::getModifiedOptionDefs4(const ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTION_DEFS4)
        .arg(util::ptimeToText(modification_time));
    OptionDefContainer option_defs;
    impl_->getModifiedOptionDefs(PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_OPTION_DEFS4,
                                 server_selector, modification_time, option_defs);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTION_DEFS4_RESULT)
        .arg(option_defs.size());
    return (option_defs);
}

OptionDescriptorPtr
PgSqlConfigBackendDHCPv4::getOption4(const ServerSelector& server_selector,
                                     const uint16_t code,
                                     const std::string& space) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_OPTION4)
        .arg(code).arg(space);
    return (impl_->getOption(PgSqlConfigBackendDHCPv4Impl::GET_OPTION4_CODE_SPACE,
                             Option::V4, server_selector, code, space));
}

OptionContainer
PgSqlConfigBackendDHCPv4::getAllOptions4(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTIONS4);
    OptionContainer options = impl_->getAllOptions(PgSqlConfigBackendDHCPv4Impl::GET_ALL_OPTIONS4,
            Option::V4, server_selector);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTIONS4_RESULT)
        .arg(options.size());
    return (options);
}

OptionContainer
PgSqlConfigBackendDHCPv4::getModifiedOptions4(const ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTIONS4)
        .arg(util::ptimeToText(modification_time));
    OptionContainer options = impl_->getModifiedOptions(PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_OPTIONS4,
            Option::V4, server_selector, modification_time);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTIONS4_RESULT)
        .arg(options.size());
    return (options);
}

StampedValuePtr
PgSqlConfigBackendDHCPv4::getGlobalParameter4(const ServerSelector& server_selector,
                                              const std::string& name) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_GLOBAL_PARAMETER4)
        .arg(name);
    return (impl_->getGlobalParameter4(server_selector, name));
}

StampedValueCollection
PgSqlConfigBackendDHCPv4::getAllGlobalParameters4(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS4);
    StampedValueCollection parameters;
    auto const& tags = server_selector.getTags();
    for (auto const& tag : tags) {
        PsqlBindArray in_bindings;
        in_bindings.addTempString(tag.get());
        impl_->getGlobalParameters(PgSqlConfigBackendDHCPv4Impl::GET_ALL_GLOBAL_PARAMETERS4,
                                   in_bindings, parameters);
    }
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_GLOBAL_PARAMETERS4_RESULT)
        .arg(parameters.size());
    return (parameters);
}

StampedValueCollection
PgSqlConfigBackendDHCPv4::getModifiedGlobalParameters4(const db::ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS4)
        .arg(util::ptimeToText(modification_time));
    StampedValueCollection parameters;
    auto const& tags = server_selector.getTags();
    for (auto const& tag : tags) {
        PsqlBindArray in_bindings;
        in_bindings.addTempString(tag.get());
        in_bindings.addTimestamp(modification_time);

        impl_->getGlobalParameters(PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_GLOBAL_PARAMETERS4,
                                   in_bindings, parameters);
    }
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS4_RESULT)
        .arg(parameters.size());
    return (parameters);
}

ClientClassDefPtr
PgSqlConfigBackendDHCPv4::getClientClass4(const db::ServerSelector& server_selector,
                                          const std::string& name) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_CLIENT_CLASS4)
        .arg(name);
    return (impl_->getClientClass4(server_selector, name));
}

ClientClassDictionary
PgSqlConfigBackendDHCPv4::getAllClientClasses4(const db::ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_CLIENT_CLASSES4);
    ClientClassDictionary client_classes;
    impl_->getAllClientClasses4(server_selector, client_classes);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_CLIENT_CLASSES4_RESULT)
        .arg(client_classes.getClasses()->size());
    return (client_classes);
}

ClientClassDictionary
PgSqlConfigBackendDHCPv4::getModifiedClientClasses4(const db::ServerSelector& server_selector,
                                                    const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES4)
        .arg(util::ptimeToText(modification_time));
    ClientClassDictionary client_classes;
    impl_->getModifiedClientClasses4(server_selector, modification_time, client_classes);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_CLIENT_CLASSES4_RESULT)
        .arg(client_classes.getClasses()->size());
    return (client_classes);
}

AuditEntryCollection
PgSqlConfigBackendDHCPv4::getRecentAuditEntries(const db::ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time,
        const uint64_t& modification_id) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_RECENT_AUDIT_ENTRIES4)
      .arg(util::ptimeToText(modification_time))
      .arg(modification_id);
    AuditEntryCollection audit_entries;
    impl_->getRecentAuditEntries(PgSqlConfigBackendDHCPv4Impl::GET_AUDIT_ENTRIES4_TIME,
                                 server_selector, modification_time,
                                 modification_id, audit_entries);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_RECENT_AUDIT_ENTRIES4_RESULT)
        .arg(audit_entries.size());
    return (audit_entries);
}

ServerCollection
PgSqlConfigBackendDHCPv4::getAllServers4() const {
    ServerCollection servers;

    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SERVERS4);
    impl_->getAllServers(PgSqlConfigBackendDHCPv4Impl::GET_ALL_SERVERS4,
                         servers);

    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SERVERS4_RESULT)
        .arg(servers.size());
    return (servers);
}

ServerPtr
PgSqlConfigBackendDHCPv4::getServer4(const data::ServerTag& server_tag) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SERVER4)
        .arg(server_tag.get());
    return (impl_->getServer(PgSqlConfigBackendDHCPv4Impl::GET_SERVER4, server_tag));
}

void
PgSqlConfigBackendDHCPv4::createUpdateSubnet4(const ServerSelector& server_selector,
                                              const Subnet4Ptr& subnet) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SUBNET4)
        .arg(subnet);
    impl_->createUpdateSubnet4(server_selector, subnet);
}

void
PgSqlConfigBackendDHCPv4::createUpdateSharedNetwork4(const ServerSelector& server_selector,
                                                     const SharedNetwork4Ptr& shared_network) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK4)
        .arg(shared_network->getName());
    impl_->createUpdateSharedNetwork4(server_selector, shared_network);
}

void
PgSqlConfigBackendDHCPv4::createUpdateOptionDef4(const ServerSelector& server_selector,
                                                 const OptionDefinitionPtr& option_def) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_OPTION_DEF4)
        .arg(option_def->getName()).arg(option_def->getCode());
    impl_->createUpdateOptionDef4(server_selector, option_def);
}

void
PgSqlConfigBackendDHCPv4::createUpdateOption4(const ServerSelector& server_selector,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_OPTION4);
    impl_->createUpdateOption4(server_selector, option);
}

void
PgSqlConfigBackendDHCPv4::createUpdateOption4(const db::ServerSelector& server_selector,
                                              const std::string& shared_network_name,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION4)
        .arg(shared_network_name);
    impl_->createUpdateOption4(server_selector, shared_network_name, option, false);
}

void
PgSqlConfigBackendDHCPv4::createUpdateOption4(const ServerSelector& server_selector,
                                              const SubnetID& subnet_id,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION4)
        .arg(subnet_id);
    impl_->createUpdateOption4(server_selector, subnet_id, option, false);
}

void
PgSqlConfigBackendDHCPv4::createUpdateOption4(const ServerSelector& server_selector,
                                              const asiolink::IOAddress& pool_start_address,
                                              const asiolink::IOAddress& pool_end_address,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_BY_POOL_OPTION4)
        .arg(pool_start_address.toText()).arg(pool_end_address.toText());
    impl_->createUpdateOption4(server_selector, pool_start_address, pool_end_address,
                               option);
}

void
PgSqlConfigBackendDHCPv4::createUpdateGlobalParameter4(const ServerSelector& server_selector,
                                                       const StampedValuePtr& value) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER4)
        .arg(value->getName());
    impl_->createUpdateGlobalParameter4(server_selector, value);
}

void
PgSqlConfigBackendDHCPv4::createUpdateClientClass4(const db::ServerSelector& server_selector,
                                                   const ClientClassDefPtr& client_class,
                                                   const std::string& follow_class_name) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_CLIENT_CLASS4)
        .arg(client_class->getName());
    impl_->createUpdateClientClass4(server_selector, client_class, follow_class_name);
}

void
PgSqlConfigBackendDHCPv4::createUpdateServer4(const ServerPtr& server) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SERVER4)
        .arg(server->getServerTagAsText());
    impl_->createUpdateServer(PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                              PgSqlConfigBackendDHCPv4Impl::INSERT_SERVER4,
                              PgSqlConfigBackendDHCPv4Impl::UPDATE_SERVER4,
                              server);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteSubnet4(const ServerSelector& server_selector,
                                        const std::string& subnet_prefix) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_PREFIX_SUBNET4)
        .arg(subnet_prefix);
    uint64_t result = impl_->deleteSubnet4(server_selector, subnet_prefix);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_PREFIX_SUBNET4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteSubnet4(const ServerSelector& server_selector,
                                        const SubnetID& subnet_id) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET4)
        .arg(subnet_id);
    uint64_t result = impl_->deleteSubnet4(server_selector, subnet_id);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteAllSubnets4(const ServerSelector& server_selector) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SUBNETS4);

    int index = (server_selector.amUnassigned() ?
                 PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4_UNASSIGNED :
                 PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4);
    uint64_t result = impl_->deleteTransactional(index, server_selector, "deleting all subnets",
                                                 "deleted all subnets", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SUBNETS4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteSharedNetworkSubnets4(const db::ServerSelector& server_selector,
                                                      const std::string& shared_network_name) {
    if (!server_selector.amAny()) {
        isc_throw(InvalidOperation, "deleting all subnets from a shared "
                  "network requires using ANY server selector");
    }
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS4)
        .arg(shared_network_name);
    uint64_t result = impl_->deleteTransactional(PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4_SHARED_NETWORK_NAME,
                                                 server_selector,
                                                 "deleting all subnets for a shared network",
                                                 "deleted all subnets for a shared network",
                                                 true, shared_network_name);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteSharedNetwork4(const ServerSelector& server_selector,
                                               const std::string& name) {
    /// @todo Using UNASSIGNED selector is allowed by the CB API but we don't have
    /// dedicated query for this at the moment. The user should use ANY to delete
    /// the shared network by name.
    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "deleting an unassigned shared network requires "
                  "an explicit server tag or using ANY server. The UNASSIGNED server "
                  "selector is currently not supported");
    }

    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK4)
        .arg(name);

    int index = (server_selector.amAny() ?
                 PgSqlConfigBackendDHCPv4Impl::DELETE_SHARED_NETWORK4_NAME_ANY :
                 PgSqlConfigBackendDHCPv4Impl::DELETE_SHARED_NETWORK4_NAME_WITH_TAG);
    uint64_t result = impl_->deleteTransactional(index, server_selector,
                                                 "deleting a shared network",
                                                 "shared network deleted", true, name);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteAllSharedNetworks4(const ServerSelector& server_selector) {
    if (server_selector.amAny()) {
        isc_throw(InvalidOperation, "deleting all shared networks for ANY server is not"
                  " supported");
    }

    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SHARED_NETWORKS4);

    int index = (server_selector.amUnassigned() ?
                 PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SHARED_NETWORKS4_UNASSIGNED :
                 PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SHARED_NETWORKS4);
    uint64_t result = impl_->deleteTransactional(index, server_selector, "deleting all shared networks",
                                                 "deleted all shared networks", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SHARED_NETWORKS4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteOptionDef4(const ServerSelector& server_selector,
                                           const uint16_t code,
                                           const std::string& space) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION_DEF4)
        .arg(code).arg(space);
    uint64_t result = impl_->deleteOptionDef4(server_selector, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION_DEF4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteAllOptionDefs4(const ServerSelector& server_selector) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_OPTION_DEFS4);
    uint64_t result = impl_->deleteTransactional(PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_OPTION_DEFS4,
                                                 server_selector, "deleting all option definitions",
                                                 "deleted all option definitions", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_OPTION_DEFS4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& server_selector,
                                        const uint16_t code,
                                        const std::string& space) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION4)
        .arg(code).arg(space);
    uint64_t result = impl_->deleteOption4(server_selector, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& /* server_selector */,
                                        const std::string& shared_network_name,
                                        const uint16_t code,
                                        const std::string& space) {
    /// @todo In the future we might use the server selector to make sure that the
    /// option is only deleted if the pool belongs to a given server. For now, we
    /// just delete it when there is a match with the parent object.
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_OPTION4)
        .arg(shared_network_name).arg(code).arg(space);
    uint64_t result = impl_->deleteOption4(ServerSelector::ANY(), shared_network_name,
                                           code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_OPTION4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& /* server_selector */,
                                        const SubnetID& subnet_id,
                                        const uint16_t code,
                                        const std::string& space) {
    /// @todo In the future we might use the server selector to make sure that the
    /// option is only deleted if the pool belongs to a given server. For now, we
    /// just delete it when there is a match with the parent object.
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION4)
        .arg(subnet_id).arg(code).arg(space);
    uint64_t result = impl_->deleteOption4(ServerSelector::ANY(), subnet_id, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& /* server_selector */,
                                        const asiolink::IOAddress& pool_start_address,
                                        const asiolink::IOAddress& pool_end_address,
                                        const uint16_t code,
                                        const std::string& space) {
    /// @todo In the future we might use the server selector to make sure that the
    /// option is only deleted if the pool belongs to a given server. For now, we
    /// just delete it when there is a match with the parent object.
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_POOL_OPTION4)
        .arg(pool_start_address.toText()).arg(pool_end_address.toText()).arg(code).arg(space);
    uint64_t result = impl_->deleteOption4(ServerSelector::ANY(), pool_start_address,
                                           pool_end_address, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_POOL_OPTION4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteGlobalParameter4(const ServerSelector& server_selector,
                                                 const std::string& name) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_GLOBAL_PARAMETER4)
        .arg(name);
    uint64_t result = impl_->deleteTransactional(PgSqlConfigBackendDHCPv4Impl::DELETE_GLOBAL_PARAMETER4,
                                                 server_selector, "deleting global parameter",
                                                 "global parameter deleted", false, name);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_GLOBAL_PARAMETER4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteAllGlobalParameters4(const ServerSelector& server_selector) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS4);
    uint64_t result = impl_->deleteTransactional(PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_GLOBAL_PARAMETERS4,
                                                 server_selector, "deleting all global parameters",
                                                 "all global parameters deleted", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteClientClass4(const db::ServerSelector& server_selector,
                                             const std::string& name) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_CLIENT_CLASS4)
        .arg(name);
    auto result = impl_->deleteClientClass4(server_selector, name);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_CLIENT_CLASS4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteAllClientClasses4(const db::ServerSelector& server_selector) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_CLIENT_CLASSES4);

    int index = (server_selector.amUnassigned() ?
                 PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_CLIENT_CLASSES4_UNASSIGNED :
                 PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_CLIENT_CLASSES4);
    uint64_t result = impl_->deleteTransactional(index, server_selector, "deleting all client classes",
                                                 "deleted all client classes", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_CLIENT_CLASSES4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteServer4(const ServerTag& server_tag) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SERVER4)
        .arg(server_tag.get());
    uint64_t result = impl_->deleteServer4(server_tag);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SERVER4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteAllServers4() {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SERVERS4);
    uint64_t result = impl_->deleteAllServers4();
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SERVERS4_RESULT)
        .arg(result);
    return (result);
}

std::string
PgSqlConfigBackendDHCPv4::getType() const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_TYPE4);
    return (impl_->getType());
}

std::string
PgSqlConfigBackendDHCPv4::getHost() const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_HOST4);
    return (impl_->getHost());
}

uint16_t
PgSqlConfigBackendDHCPv4::getPort() const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_PORT4);
    return (impl_->getPort());
}

bool
PgSqlConfigBackendDHCPv4::registerBackendType() {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_REGISTER_BACKEND_TYPE4);
    return (
        dhcp::ConfigBackendDHCPv4Mgr::instance().registerBackendFactory("postgresql",
            [](const db::DatabaseConnection::ParameterMap& params) -> dhcp::ConfigBackendDHCPv4Ptr {
            return (dhcp::PgSqlConfigBackendDHCPv4Ptr(new dhcp::PgSqlConfigBackendDHCPv4(params)));
        })
    );
}

void
PgSqlConfigBackendDHCPv4::unregisterBackendType() {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_UNREGISTER_BACKEND_TYPE4);
    dhcp::ConfigBackendDHCPv4Mgr::instance().unregisterBackendFactory("postgresql");
}

} // end of namespace isc::dhcp
} // end of namespace isc
