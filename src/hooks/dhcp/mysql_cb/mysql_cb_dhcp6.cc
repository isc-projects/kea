// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/addr_utilities.h>
#include <mysql_cb_dhcp6.h>
#include <mysql_cb_impl.h>
#include <mysql_query_macros_dhcp.h>
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
#include <util/dhcp_space.h>
#include <util/multi_threading_mgr.h>
#include <util/triplet.h>
#include <mysql/mysql_connection.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <mysql.h>
#include <mysqld_error.h>
#include <array>
#include <sstream>
#include <utility>
#include <vector>

using namespace isc::cb;
using namespace isc::db;
using namespace isc::data;
using namespace isc::asiolink;
using namespace isc::log;
using namespace isc::util;

namespace isc {
namespace dhcp {

/// @brief Implementation of the MySQL Configuration Backend.
class MySqlConfigBackendDHCPv6Impl : public MySqlConfigBackendImpl {
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
        NUM_STATEMENTS
    };

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    explicit MySqlConfigBackendDHCPv6Impl(const DatabaseConnection::ParameterMap&
                                          parameters);

    /// @brief Destructor.
    ~MySqlConfigBackendDHCPv6Impl();

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
            MySqlBindingCollection in_bindings = {
                MySqlBinding::createString(tag.get()),
                MySqlBinding::createString(name)
            };

            getGlobalParameters(GET_GLOBAL_PARAMETER6, in_bindings, parameters);
        }

        return (parameters.empty() ? StampedValuePtr() : *parameters.begin());
    }

    /// @brief Sends query to insert or update global parameter.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the global parameter.
    /// @param value Value of the global parameter.
    void createUpdateGlobalParameter6(const db::ServerSelector& server_selector,
                                      const StampedValuePtr& value) {
        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        auto tag = getServerTag(server_selector, "creating or updating global parameter");

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(value->getName()),
            MySqlBinding::createString(value->getValue()),
            MySqlBinding::createInteger<uint8_t>(value->getType()),
            MySqlBinding::createTimestamp(value->getModificationTime()),
            MySqlBinding::createString(tag),
            MySqlBinding::createString(value->getName())
        };

        MySqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this, MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           server_selector, "global parameter set", false);

        // Try to update the existing row.
        if (conn_.updateDeleteQuery(MySqlConfigBackendDHCPv6Impl::UPDATE_GLOBAL_PARAMETER6,
                                    in_bindings) == 0) {
            // No such parameter found, so let's insert it. We have to adjust the
            // bindings collection to match the prepared statement for insert.
            in_bindings.pop_back();
            in_bindings.pop_back();
            conn_.insertQuery(MySqlConfigBackendDHCPv6Impl::INSERT_GLOBAL_PARAMETER6,
                              in_bindings);

            // Successfully inserted global parameter. Now, we have to associate it
            // with the server tag.

            // Let's first get the primary key of the global parameter.
            uint64_t id = mysql_insert_id(conn_.mysql_);

            // Successfully inserted global parameter. Now, we have to associate it
            // with the server tag.
            attachElementToServers(MySqlConfigBackendDHCPv6Impl::INSERT_GLOBAL_PARAMETER6_SERVER,
                                   server_selector,
                                   MySqlBinding::createInteger<uint64_t>(id),
                                   MySqlBinding::createTimestamp(value->getModificationTime()));
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
                     const MySqlBindingCollection& in_bindings,
                     Subnet6Collection& subnets) {
        // Create output bindings. The order must match that in the prepared
        // statement. Please put comments only at the end of line so
        // line counting and indexing match.
        // The server tag must be the last field.
        MySqlBindingCollection out_bindings = {
            MySqlBinding::createInteger<uint32_t>(), // subnet_id
            MySqlBinding::createString(SUBNET6_PREFIX_BUF_LENGTH), // subnet_prefix
            MySqlBinding::createString(CLIENT_CLASS_BUF_LENGTH), // client_class
            MySqlBinding::createString(INTERFACE_BUF_LENGTH), // interface
            MySqlBinding::createTimestamp(), // modification_ts
            MySqlBinding::createInteger<uint32_t>(), // preferred_lifetime
            MySqlBinding::createInteger<uint8_t>(), // rapid_commit
            MySqlBinding::createInteger<uint32_t>(), // rebind_timer
            MySqlBinding::createString(RELAY_BUF_LENGTH), // relay
            MySqlBinding::createInteger<uint32_t>(), // renew_timer
            MySqlBinding::createString(REQUIRE_CLIENT_CLASSES_BUF_LENGTH), // require_client_classes
            MySqlBinding::createInteger<uint8_t>(), // reservations_global
            MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // shared_network_name
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // user_context
            MySqlBinding::createInteger<uint32_t>(), // valid_lifetime
            MySqlBinding::createInteger<uint64_t>(), // pool: id
            MySqlBinding::createString(POOL_ADDRESS6_BUF_LENGTH), // pool: start_address
            MySqlBinding::createString(POOL_ADDRESS6_BUF_LENGTH), // pool: end_address
            MySqlBinding::createInteger<uint32_t>(), // pool: subnet_id
            MySqlBinding::createTimestamp(), // pool: modification_ts
            MySqlBinding::createInteger<uint64_t>(), // pd pool: id
            MySqlBinding::createString(POOL_ADDRESS6_BUF_LENGTH), // pd pool: prefix
            MySqlBinding::createInteger<uint8_t>(), // pd pool: prefix_length
            MySqlBinding::createInteger<uint8_t>(), // pd pool: delegated_prefix_length
            MySqlBinding::createInteger<uint32_t>(), // pd pool: subnet_id
            MySqlBinding::createTimestamp(), // pd pool: modification_ts
            MySqlBinding::createInteger<uint64_t>(), // pool option: option_id
            MySqlBinding::createInteger<uint16_t>(), // pool option: code
            MySqlBinding::createBlob(OPTION_VALUE_BUF_LENGTH), // pool option: value
            MySqlBinding::createString(FORMATTED_OPTION_VALUE_BUF_LENGTH), // pool option: formatted_value
            MySqlBinding::createString(OPTION_SPACE_BUF_LENGTH), // pool option: space
            MySqlBinding::createInteger<uint8_t>(), // pool option: persistent
            MySqlBinding::createInteger<uint8_t>(), // pool option: cancelled
            MySqlBinding::createInteger<uint32_t>(), // pool option: dhcp6_subnet_id
            MySqlBinding::createInteger<uint8_t>(), // pool option: scope_id
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // pool option: user_context
            MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // pool option: shared_network_name
            MySqlBinding::createInteger<uint64_t>(), // pool option: pool_id
            MySqlBinding::createTimestamp(), // pool option: modification_ts
            MySqlBinding::createInteger<uint64_t>(), // pool option: pd_pool_id
            MySqlBinding::createInteger<uint64_t>(), // pd pool option: option_id
            MySqlBinding::createInteger<uint16_t>(), // pd pool option: code
            MySqlBinding::createBlob(OPTION_VALUE_BUF_LENGTH), // pd pool option: value
            MySqlBinding::createString(FORMATTED_OPTION_VALUE_BUF_LENGTH), // pd pool option: formatted_value
            MySqlBinding::createString(OPTION_SPACE_BUF_LENGTH), // pd pool option: space
            MySqlBinding::createInteger<uint8_t>(), // pd pool option: persistent
            MySqlBinding::createInteger<uint8_t>(), // pd pool option: cancelled
            MySqlBinding::createInteger<uint32_t>(), // pd pool option: dhcp6_subnet_id
            MySqlBinding::createInteger<uint8_t>(), // pd pool option: scope_id
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // pd pool option: user_context
            MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // pd pool option: shared_network_name
            MySqlBinding::createInteger<uint64_t>(), // pd pool option: pool_id
            MySqlBinding::createTimestamp(), // pd pool option: modification_ts
            MySqlBinding::createInteger<uint64_t>(), // pd pool option: pd_pool_id
            MySqlBinding::createInteger<uint64_t>(), // option: option_id
            MySqlBinding::createInteger<uint16_t>(), // option: code
            MySqlBinding::createBlob(OPTION_VALUE_BUF_LENGTH), // option: value
            MySqlBinding::createString(FORMATTED_OPTION_VALUE_BUF_LENGTH), // option: formatted_value
            MySqlBinding::createString(OPTION_SPACE_BUF_LENGTH), // option: space
            MySqlBinding::createInteger<uint8_t>(), // option: persistent
            MySqlBinding::createInteger<uint8_t>(), // option: cancelled
            MySqlBinding::createInteger<uint32_t>(), // option: dhcp6_subnet_id
            MySqlBinding::createInteger<uint8_t>(), // option: scope_id
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // option: user_context
            MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // option: shared_network_name
            MySqlBinding::createInteger<uint64_t>(), // option: pool_id
            MySqlBinding::createTimestamp(), // option: modification_ts
            MySqlBinding::createInteger<uint64_t>(), // option: pd_pool_id
            MySqlBinding::createInteger<uint8_t>(), // calculate_tee_times
            MySqlBinding::createInteger<float>(), // t1_percent
            MySqlBinding::createInteger<float>(), // t2_percent
            MySqlBinding::createBlob(INTERFACE_ID_BUF_LENGTH), // interface_id
            MySqlBinding::createInteger<uint32_t>(), // min_preferred_lifetime
            MySqlBinding::createInteger<uint32_t>(), // max_preferred_lifetime
            MySqlBinding::createInteger<uint32_t>(), // min_valid_lifetime
            MySqlBinding::createInteger<uint32_t>(), // max_valid_lifetime
            MySqlBinding::createString(CLIENT_CLASS_BUF_LENGTH), // pool: client_class
            MySqlBinding::createString(REQUIRE_CLIENT_CLASSES_BUF_LENGTH), // pool: require_client_classes
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // pool: user_context
            MySqlBinding::createString(POOL_ADDRESS6_BUF_LENGTH), // pd pool: excluded_prefix
            MySqlBinding::createInteger<uint8_t>(), // pd pool: excluded_prefix_length
            MySqlBinding::createString(CLIENT_CLASS_BUF_LENGTH), // pd pool: client_class
            MySqlBinding::createString(REQUIRE_CLIENT_CLASSES_BUF_LENGTH), // pd pool: require_client_classes
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // pd pool: user_context
            MySqlBinding::createInteger<uint8_t>(), // ddns_send_updates
            MySqlBinding::createInteger<uint8_t>(), // ddns_override_no_update
            MySqlBinding::createInteger<uint8_t>(), // ddns_override_client_update
            MySqlBinding::createInteger<uint8_t>(), // ddns_replace_client_name
            MySqlBinding::createString(DNS_NAME_BUF_LENGTH), // ddns_generated_prefix
            MySqlBinding::createString(DNS_NAME_BUF_LENGTH), // ddns_qualifying_suffix
            MySqlBinding::createInteger<uint8_t>(), // reservations_in_subnet
            MySqlBinding::createInteger<uint8_t>(), // reservations_out_of_pool
            MySqlBinding::createInteger<float>(), // cache_threshold
            MySqlBinding::createInteger<uint32_t>(), // cache_max_age
            MySqlBinding::createString(ALLOCATOR_TYPE_BUF_LENGTH), // allocator
            MySqlBinding::createString(ALLOCATOR_TYPE_BUF_LENGTH), // pd_allocator
            MySqlBinding::createString(SERVER_TAG_BUF_LENGTH) // server_tag
        };

        uint64_t last_pool_id = 0;
        uint64_t last_pd_pool_id = 0;
        uint64_t last_pool_option_id = 0;
        uint64_t last_pd_pool_option_id = 0;
        uint64_t last_option_id = 0;
        Pool6Ptr last_pool;
        Pool6Ptr last_pd_pool;
        std::string last_tag;

        // Execute actual query.
        conn_.selectQuery(index, in_bindings, out_bindings,
                          [this, &subnets, &last_pool,  &last_pd_pool,
                           &last_pool_id, &last_pd_pool_id,
                           &last_pool_option_id, &last_pd_pool_option_id,
                           &last_option_id, &last_tag]
                          (MySqlBindingCollection& out_bindings) {
            // Get pointer to the last subnet in the collection.
            Subnet6Ptr last_subnet;
            if (!subnets.empty()) {
                last_subnet = *subnets.rbegin();
            }

            // Subnet has been returned. Assuming that subnets are ordered by
            // subnet identifier, if the subnet identifier of the current row
            // is different than the subnet identifier of the previously returned
            // row, it means that we have to construct new subnet object.
            if (!last_subnet || (last_subnet->getID() != out_bindings[0]->getInteger<uint32_t>())) {
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

                // subnet_id (0)
                SubnetID subnet_id(out_bindings[0]->getInteger<uint32_t>());

                // subnet_prefix (1)
                std::string subnet_prefix = out_bindings[1]->getString();
                auto prefix_pair = Subnet6::parsePrefix(subnet_prefix);

                // preferred_lifetime (5)
                // min_preferred_lifetime (72)
                // max_preferred_lifetime (73)
                auto preferred_lifetime = createTriplet(out_bindings[5],
                                                        out_bindings[72],
                                                        out_bindings[73]);

                // renew_timer (9)
                auto renew_timer = createTriplet(out_bindings[9]);

                // rebind_timer (7)
                auto rebind_timer = createTriplet(out_bindings[7]);

                // valid_lifetime (14)
                // min_valid_lifetime (74)
                // max_valid_lifetime (75)
                auto valid_lifetime = createTriplet(out_bindings[14],
                                                    out_bindings[74],
                                                    out_bindings[75]);

                // Create subnet with basic settings.
                last_subnet = Subnet6::create(prefix_pair.first, prefix_pair.second,
                                              renew_timer, rebind_timer,
                                              preferred_lifetime,
                                              valid_lifetime, subnet_id);

                // 0 and 1 are subnet_id and subnet_prefix

                // client_class (2)
                if (!out_bindings[2]->amNull()) {
                    last_subnet->allowClientClass(out_bindings[2]->getString());
                }

                // interface (3)
                if (!out_bindings[3]->amNull()) {
                    last_subnet->setIface(out_bindings[3]->getString());
                }

                // modification_ts (4)
                last_subnet->setModificationTime(out_bindings[4]->getTimestamp());
                // 5 is preferred_lifetime

                // rapid_commit (6)
                if (!out_bindings[6]->amNull()) {
                    last_subnet->setRapidCommit(out_bindings[6]->getBool());
                }

                // 7 is rebind_timer

                // relay (8)
                ElementPtr relay_element = out_bindings[8]->getJSON();
                if (relay_element) {
                    if (relay_element->getType() != Element::list) {
                        isc_throw(BadValue, "invalid relay value "
                                  << out_bindings[8]->getString());
                    }
                    for (auto i = 0; i < relay_element->size(); ++i) {
                        auto relay_address_element = relay_element->get(i);
                        if (relay_address_element->getType() != Element::string) {
                            isc_throw(BadValue, "relay address must be a string");
                        }
                        last_subnet->addRelayAddress(IOAddress(relay_element->get(i)->stringValue()));
                    }
                }

                // 9 is renew_timer

                // require_client_classes (10)
                ElementPtr require_element = out_bindings[10]->getJSON();
                if (require_element) {
                    if (require_element->getType() != Element::list) {
                        isc_throw(BadValue, "invalid require_client_classes value "
                                  << out_bindings[10]->getString());
                    }
                    for (auto i = 0; i < require_element->size(); ++i) {
                        auto require_item = require_element->get(i);
                        if (require_item->getType() != Element::string) {
                            isc_throw(BadValue, "elements of require_client_classes list must"
                                      "be valid strings");
                        }
                        last_subnet->requireClientClass(require_item->stringValue());
                    }
                }

                // reservations_global (11)
                if (!out_bindings[11]->amNull()) {
                    last_subnet->setReservationsGlobal(out_bindings[11]->getBool());
                }

                // shared_network_name (12)
                if (!out_bindings[12]->amNull()) {
                    last_subnet->setSharedNetworkName(out_bindings[12]->getString());
                }

                // user_context (13)
                ElementPtr user_context = out_bindings[13]->getJSON();
                if (user_context) {
                    last_subnet->setContext(user_context);
                }

                // 14 is valid_lifetime

                // 15 to 19 are pool
                // 20 to 25 are pd pool
                // 26 to 39 are pool option
                // 40 to 53 are pd pool option
                // 54 to 67 are option

                // calculate_tee_times (68)
                if (!out_bindings[68]->amNull()) {
                    last_subnet->setCalculateTeeTimes(out_bindings[68]->getBool());
                }

                // t1_percent (69)
                if (!out_bindings[69]->amNull()) {
                    last_subnet->setT1Percent(out_bindings[69]->getFloat());
                }

                // t2_percent (70)
                if (!out_bindings[70]->amNull()) {
                    last_subnet->setT2Percent(out_bindings[70]->getFloat());
                }

                // interface_id (71)
                if (!out_bindings[71]->amNull()) {
                    auto iface_id_data = out_bindings[71]->getBlob();
                    if (!iface_id_data.empty()) {
                        OptionPtr opt_iface_id(new Option(Option::V6, D6O_INTERFACE_ID,
                                                          iface_id_data));
                        last_subnet->setInterfaceId(opt_iface_id);
                    }
                }

                // 72 and 73 are {min,max}_preferred_lifetime

                // 74 and 75 are {min,max}_valid_lifetime

                // 76 is pool client_class
                // 77 is pool require_client_classes
                // 78 is pool user_context
                // 79 is pd pool excluded_prefix
                // 80 is pd pool excluded_prefix_length
                // 81 is pd pool client_class
                // 82 is pd pool require_client_classes
                // 83 is pd pool user_context

                // ddns_send_updates (84)
                if (!out_bindings[84]->amNull()) {
                    last_subnet->setDdnsSendUpdates(out_bindings[84]->getBool());
                }

                // ddns_override_no_update (85)
                if (!out_bindings[85]->amNull()) {
                    last_subnet->setDdnsOverrideNoUpdate(out_bindings[85]->getBool());
                }

                // ddns_override_client_update (86)
                if (!out_bindings[86]->amNull()) {
                    last_subnet->setDdnsOverrideClientUpdate(out_bindings[86]->getBool());
                }

                // ddns_replace_client_name (87)
                if (!out_bindings[87]->amNull()) {
                    last_subnet->setDdnsReplaceClientNameMode(static_cast<D2ClientConfig::ReplaceClientNameMode>
                        (out_bindings[87]->getInteger<uint8_t>()));
                }

                // ddns_generated_prefix (88)
                if (!out_bindings[88]->amNull()) {
                    last_subnet->setDdnsGeneratedPrefix(out_bindings[88]->getString());
                }

                // ddns_qualifying_suffix (89)
                if (!out_bindings[89]->amNull()) {
                    last_subnet->setDdnsQualifyingSuffix(out_bindings[89]->getString());
                }

                // reservations_in_subnet (90)
                if (!out_bindings[90]->amNull()) {
                    last_subnet->setReservationsInSubnet(out_bindings[90]->getBool());
                }

                // reservations_out_of_pool (91)
                if (!out_bindings[91]->amNull()) {
                    last_subnet->setReservationsOutOfPool(out_bindings[91]->getBool());
                }

                // cache_threshold (92)
                if (!out_bindings[92]->amNull()) {
                    last_subnet->setCacheThreshold(out_bindings[92]->getFloat());
                }

                // cache_max_age (93)
                if (!out_bindings[93]->amNull()) {
                    last_subnet->setCacheMaxAge(out_bindings[93]->getInteger<uint32_t>());
                }

                // allocator (94)
                if (!out_bindings[94]->amNull()) {
                    last_subnet->setAllocatorType(out_bindings[94]->getString());
                }

                // pd_allocator (95)
                if (!out_bindings[95]->amNull()) {
                    last_subnet->setPdAllocatorType(out_bindings[95]->getString());
                }

                // server_tag (96 / last)

                // Subnet ready. Add it to the list.
                auto ret = subnets.insert(last_subnet);

                // subnets is a multi index container with unique indexes
                // but these indexes are unique too in the database,
                // so this is for sanity only.
                if (!ret.second) {
                    isc_throw(Unexpected, "add subnet failed");
                }
            }

            // Check for new server tags.
            if (!out_bindings[96]->amNull() &&
                (last_tag != out_bindings[96]->getString())) {
                last_tag = out_bindings[96]->getString();
                if (!last_tag.empty() && !last_subnet->hasServerTag(ServerTag(last_tag))) {
                    last_subnet->setServerTag(last_tag);
                }
            }

            // Pool is between 15 and 19 with extra between 76 and 78

            // If the row contains information about the pool and it
            // appears to be new pool entry (checked by comparing pool
            // id), let's create the new pool and add it to the
            // subnet.
            // pool id (15)
            // pool start_address (16)
            // pool end_address (17)
            if (!out_bindings[15]->amNull() &&
                !out_bindings[16]->getString().empty() &&
                !out_bindings[17]->getString().empty() &&
                (out_bindings[15]->getInteger<uint64_t>() > last_pool_id)) {
                last_pool_id = out_bindings[15]->getInteger<uint64_t>();
                last_pool = Pool6::create(Lease::TYPE_NA,
                                          IOAddress(out_bindings[16]->getString()),
                                          IOAddress(out_bindings[17]->getString()));

                // 18 is pool subnet_id (ignored)
                // 19 is pool modification_ts (ignored)

                // pool client_class (76)
                if (!out_bindings[76]->amNull()) {
                    last_pool->allowClientClass(out_bindings[76]->getString());
                }

                // pool require_client_classes (77)
                ElementPtr require_element = out_bindings[77]->getJSON();
                if (require_element) {
                    if (require_element->getType() != Element::list) {
                        isc_throw(BadValue, "invalid pool require_client_classes value "
                                  << out_bindings[77]->getString());
                    }
                    for (auto i = 0; i < require_element->size(); ++i) {
                        auto require_item = require_element->get(i);
                        if (require_item->getType() != Element::string) {
                            isc_throw(BadValue, "elements of pool require_client_classes list must"
                                      "be valid strings");
                        }
                        last_pool->requireClientClass(require_item->stringValue());
                    }
                }

                // pool user_context (78)
                ElementPtr user_context = out_bindings[78]->getJSON();
                if (user_context) {
                    last_pool->setContext(user_context);
                }

                last_subnet->addPool(last_pool);
            }

            // Pd Pool is between 20 and 25 with extra between 79 and 83

            // If the row contains information about the pd pool and
            // it appears to be new pd pool entry (checked by
            // comparing pd pool id), let's create the new pd pool and
            // add it to the subnet.
            // pd pool id (20)
            // pd pool prefix (21)
            // pd pool prefix_length (22)
            // pd pool delegated_prefix_length (23)
            if (!out_bindings[20]->amNull() &&
                !out_bindings[21]->getString().empty() &&
                (out_bindings[22]->getInteger<uint8_t>() != 0) &&
                (out_bindings[23]->getInteger<uint8_t>() != 0) &&
                (out_bindings[20]->getInteger<uint64_t>() > last_pd_pool_id)) {
                last_pd_pool_id = out_bindings[20]->getInteger<uint64_t>();

                // 24 is pd pool subnet_id (ignored)
                // 25 is pd pool modification_ts (ignored)

                // excluded_prefix (79) and excluded_prefix_length (80)
                IOAddress excluded_prefix = IOAddress::IPV6_ZERO_ADDRESS();
                if (!out_bindings[79]->amNull()) {
                    excluded_prefix = IOAddress(out_bindings[79]->getString());
                }
                last_pd_pool = Pool6::create(IOAddress(out_bindings[21]->getString()),
                                             out_bindings[22]->getInteger<uint8_t>(),
                                             out_bindings[23]->getInteger<uint8_t>(),
                                             excluded_prefix,
                                             out_bindings[80]->getInteger<uint8_t>());

                // pd pool client_class (81)
                if (!out_bindings[81]->amNull()) {
                    last_pd_pool->allowClientClass(out_bindings[81]->getString());
                }

                // pd pool require_client_classes (82)
                ElementPtr require_element = out_bindings[82]->getJSON();
                if (require_element) {
                    if (require_element->getType() != Element::list) {
                        isc_throw(BadValue, "invalid pd pool require_client_classes value "
                                  << out_bindings[82]->getString());
                    }
                    for (auto i = 0; i < require_element->size(); ++i) {
                        auto require_item = require_element->get(i);
                        if (require_item->getType() != Element::string) {
                            isc_throw(BadValue, "elements of pd pool require_client_classes list must"
                                      "be valid strings");
                        }
                        last_pd_pool->requireClientClass(require_item->stringValue());
                    }
                }

                // pd pool user_context (83)
                ElementPtr user_context = out_bindings[83]->getJSON();
                if (user_context) {
                    last_pd_pool->setContext(user_context);
                }

                last_subnet->addPool(last_pd_pool);
            }

            // Parse pool specific option between 26 and 39
            if (last_pool && !out_bindings[26]->amNull() &&
                (last_pool_option_id < out_bindings[26]->getInteger<uint64_t>())) {
                last_pool_option_id = out_bindings[26]->getInteger<uint64_t>();

                OptionDescriptorPtr desc = processOptionRow(Option::V6, out_bindings.begin() + 26);
                if (desc) {
                    last_pool->getCfgOption()->add(*desc, desc->space_name_);
                }
            }

            // Parse pd pool specific option between 40 and 53
            if (last_pd_pool && !out_bindings[40]->amNull() &&
                (last_pd_pool_option_id < out_bindings[40]->getInteger<uint64_t>())) {
                last_pd_pool_option_id = out_bindings[40]->getInteger<uint64_t>();

                OptionDescriptorPtr desc = processOptionRow(Option::V6, out_bindings.begin() + 40);
                if (desc) {
                    last_pd_pool->getCfgOption()->add(*desc, desc->space_name_);
                }
            }

            // Parse subnet specific option between 54 and 67
            if (!out_bindings[54]->amNull() &&
                (last_option_id < out_bindings[54]->getInteger<uint64_t>())) {
                last_option_id = out_bindings[54]->getInteger<uint64_t>();

                OptionDescriptorPtr desc = processOptionRow(Option::V6, out_bindings.begin() + 54);
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

        MySqlBindingCollection in_bindings = { MySqlBinding::createInteger<uint32_t>(subnet_id) };

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

        MySqlBindingCollection in_bindings = { MySqlBinding::createString(subnet_prefix) };

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
        MySqlBindingCollection in_bindings;
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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createTimestamp(modification_ts)
        };

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
        MySqlBindingCollection in_bindings = { MySqlBinding::createString(shared_network_name) };
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
                  const MySqlBindingCollection& in_bindings,
                  PoolCollection& pools,
                  std::vector<uint64_t>& pool_ids) {
        MySqlBindingCollection out_bindings = {
            MySqlBinding::createInteger<uint64_t>(), // pool: id
            MySqlBinding::createString(POOL_ADDRESS6_BUF_LENGTH), // pool: start_address
            MySqlBinding::createString(POOL_ADDRESS6_BUF_LENGTH), // pool: end_address
            MySqlBinding::createInteger<uint32_t>(), // pool: subnet_id
            MySqlBinding::createString(CLIENT_CLASS_BUF_LENGTH), // pool: client_class
            MySqlBinding::createString(REQUIRE_CLIENT_CLASSES_BUF_LENGTH), // pool: require_client_classes
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // pool: user_context
            MySqlBinding::createTimestamp(), // pool: modification_ts
            MySqlBinding::createInteger<uint64_t>(), // pool option: option_id
            MySqlBinding::createInteger<uint16_t>(), // pool option: code
            MySqlBinding::createBlob(OPTION_VALUE_BUF_LENGTH), // pool option: value
            MySqlBinding::createString(FORMATTED_OPTION_VALUE_BUF_LENGTH), // pool option: formatted_value
            MySqlBinding::createString(OPTION_SPACE_BUF_LENGTH), // pool option: space
            MySqlBinding::createInteger<uint8_t>(), // pool option: persistent
            MySqlBinding::createInteger<uint8_t>(), // pool option: cancelled
            MySqlBinding::createInteger<uint32_t>(), // pool option: dhcp6_subnet_id
            MySqlBinding::createInteger<uint8_t>(), // pool option: scope_id
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // pool option: user_context
            MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // pool option: shared_network_name
            MySqlBinding::createInteger<uint64_t>(), // pool option: pool_id
            MySqlBinding::createTimestamp(), //pool option: modification_ts
            MySqlBinding::createInteger<uint64_t>(), // pool option: pd_pool_id
        };

        uint64_t last_pool_id = 0;
        uint64_t last_pool_option_id = 0;
        Pool6Ptr last_pool;

        conn_.selectQuery(index, in_bindings, out_bindings,
                          [this, &last_pool_id, &last_pool_option_id, &last_pool,
                           &pools, &pool_ids]
                          (MySqlBindingCollection& out_bindings) {
            if (out_bindings[0]->getInteger<uint64_t>() > last_pool_id) {
                // pool id (0)
                last_pool_id = out_bindings[0]->getInteger<uint64_t>();

                // pool start_address (1)
                // pool end_address (2)
                last_pool = Pool6::create(Lease::TYPE_NA,
                                          IOAddress(out_bindings[1]->getString()),
                                          IOAddress(out_bindings[2]->getString()));

                // pool subnet_id (3) (ignored)

                // pool client_class (4)
                if (!out_bindings[4]->amNull()) {
                    last_pool->allowClientClass(out_bindings[4]->getString());
                }

                // pool require_client_classes (5)
                ElementPtr require_element = out_bindings[5]->getJSON();
                if (require_element) {
                    if (require_element->getType() != Element::list) {
                        isc_throw(BadValue, "invalid pool require_client_classes value "
                                  << out_bindings[5]->getString());
                    }
                    for (auto i = 0; i < require_element->size(); ++i) {
                        auto require_item = require_element->get(i);
                        if (require_item->getType() != Element::string) {
                            isc_throw(BadValue, "elements of pool require_client_classes list must"
                                      "be valid strings");
                        }
                        last_pool->requireClientClass(require_item->stringValue());
                    }
                }

                // pool user_context (6)
                ElementPtr user_context = out_bindings[6]->getJSON();
                if (user_context) {
                    last_pool->setContext(user_context);
                }

                // pool: modification_ts (7) (ignored)

                pools.push_back(last_pool);
                pool_ids.push_back(last_pool_id);
            }

            // Parse pool specific option (8).
            if (last_pool && !out_bindings[8]->amNull() &&
                (last_pool_option_id < out_bindings[8]->getInteger<uint64_t>())) {
                last_pool_option_id = out_bindings[8]->getInteger<uint64_t>();

                OptionDescriptorPtr desc = processOptionRow(Option::V6, out_bindings.begin() + 8);
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
                    const MySqlBindingCollection& in_bindings,
                    PoolCollection& pd_pools,
                    std::vector<uint64_t>& pd_pool_ids) {
        MySqlBindingCollection out_bindings = {
            MySqlBinding::createInteger<uint64_t>(), // pd pool: id
            MySqlBinding::createString(POOL_ADDRESS6_BUF_LENGTH), // pd pool: prefix
            MySqlBinding::createInteger<uint8_t>(), // pd pool: prefix_length
            MySqlBinding::createInteger<uint8_t>(), // pd pool: delegated_prefix_length
            MySqlBinding::createInteger<uint32_t>(), // pd pool: subnet_id
            MySqlBinding::createString(POOL_ADDRESS6_BUF_LENGTH), // pd pool: excluded_prefix
            MySqlBinding::createInteger<uint8_t>(), // pd pool: excluded_prefix_length
            MySqlBinding::createString(CLIENT_CLASS_BUF_LENGTH), // pd pool: client_class
            MySqlBinding::createString(REQUIRE_CLIENT_CLASSES_BUF_LENGTH), // pd pool: require_client_classes
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // pd pool: user_context
            MySqlBinding::createTimestamp(), // pd pool: modification_ts
            MySqlBinding::createInteger<uint64_t>(), // pd pool option: option_id
            MySqlBinding::createInteger<uint16_t>(), // pd pool option: code
            MySqlBinding::createBlob(OPTION_VALUE_BUF_LENGTH), // pd pool option: value
            MySqlBinding::createString(FORMATTED_OPTION_VALUE_BUF_LENGTH), // pd pool option: formatted_value
            MySqlBinding::createString(OPTION_SPACE_BUF_LENGTH), // pd pool option: space
            MySqlBinding::createInteger<uint8_t>(), // pd pool option: persistent
            MySqlBinding::createInteger<uint8_t>(), // pd pool option: cancelled
            MySqlBinding::createInteger<uint32_t>(), // pd pool option: dhcp6_subnet_id
            MySqlBinding::createInteger<uint8_t>(), // pd pool option: scope_id
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // pd pool option: user_context
            MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // pd pool option: shared_network_name
            MySqlBinding::createInteger<uint64_t>(), // pd pool option: pool_id
            MySqlBinding::createTimestamp(), // pd pool option: modification_ts
            MySqlBinding::createInteger<uint64_t>() // pd pool option: pd_pool_id
        };

        uint64_t last_pd_pool_id = 0;
        uint64_t last_pd_pool_option_id = 0;
        Pool6Ptr last_pd_pool;

        conn_.selectQuery(index, in_bindings, out_bindings,
                          [this, &last_pd_pool_id, &last_pd_pool_option_id,
                           &last_pd_pool, &pd_pools, &pd_pool_ids]
                          (MySqlBindingCollection& out_bindings) {
            if (out_bindings[0]->getInteger<uint64_t>() > last_pd_pool_id) {
                // pd pool id (0)
                last_pd_pool_id = out_bindings[0]->getInteger<uint64_t>();

                // pd pool prefix (1)
                // pd pool prefix_length (2)
                // pd pool delegated_prefix_length (3)

                // pd pool subnet_id (4 / ignored)

                // excluded_prefix (5) and excluded_prefix_length (6)
                IOAddress excluded_prefix = IOAddress::IPV6_ZERO_ADDRESS();
                if (!out_bindings[5]->amNull()) {
                    excluded_prefix = IOAddress(out_bindings[5]->getString());
                }

                last_pd_pool = Pool6::create(IOAddress(out_bindings[1]->getString()),
                                             out_bindings[2]->getInteger<uint8_t>(),
                                             out_bindings[3]->getInteger<uint8_t>(),
                                             excluded_prefix,
                                             out_bindings[6]->getInteger<uint8_t>());

                // pd pool client_class (7)
                if (!out_bindings[7]->amNull()) {
                    last_pd_pool->allowClientClass(out_bindings[7]->getString());
                }

                // pd pool require_client_classes (8)
                ElementPtr require_element = out_bindings[8]->getJSON();
                if (require_element) {
                    if (require_element->getType() != Element::list) {
                        isc_throw(BadValue, "invalid pd pool require_client_classes value "
                                  << out_bindings[8]->getString());
                    }
                    for (auto i = 0; i < require_element->size(); ++i) {
                        auto require_item = require_element->get(i);
                        if (require_item->getType() != Element::string) {
                            isc_throw(BadValue, "elements of pd pool require_client_classes list must"
                                      "be valid strings");
                        }
                        last_pd_pool->requireClientClass(require_item->stringValue());
                    }
                }

                // pd pool user_context (9)
                ElementPtr user_context = out_bindings[9]->getJSON();
                if (user_context) {
                    last_pd_pool->setContext(user_context);
                }

                // pd pool modification_ts (10)

                pd_pools.push_back(last_pd_pool);
                pd_pool_ids.push_back(last_pd_pool_id);
            }

            // Parse pd pool specific option between 11 and 25
            if (last_pd_pool && !out_bindings[11]->amNull() &&
                (last_pd_pool_option_id < out_bindings[11]->getInteger<uint64_t>())) {
                last_pd_pool_option_id = out_bindings[11]->getInteger<uint64_t>();

                OptionDescriptorPtr desc = processOptionRow(Option::V6, out_bindings.begin() + 11);
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
            MySqlBindingCollection in_bindings = {
                    MySqlBinding::createString(pool_start_address.toText()),
                    MySqlBinding::createString(pool_end_address.toText())
            };
            getPools(GET_POOL6_RANGE_ANY, in_bindings, pools, pool_ids);
        } else {
            auto const& tags = server_selector.getTags();
            for (auto const& tag : tags) {
                MySqlBindingCollection in_bindings = {
                    MySqlBinding::createString(tag.get()),
                    MySqlBinding::createString(pool_start_address.toText()),
                    MySqlBinding::createString(pool_end_address.toText())
                };
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
            MySqlBindingCollection in_bindings = {
                MySqlBinding::createString(pd_pool_prefix.toText()),
                MySqlBinding::createInteger<uint8_t>(pd_pool_prefix_length)
            };
            getPdPools(GET_PD_POOL_ANY, in_bindings, pd_pools, pd_pool_ids);
        } else {
            auto const& tags = server_selector.getTags();
            for (auto const& tag : tags) {
                MySqlBindingCollection in_bindings = {
                    MySqlBinding::createString(tag.get()),
                    MySqlBinding::createString(pd_pool_prefix.toText()),
                    MySqlBinding::createInteger<uint8_t>(pd_pool_prefix_length)
                };
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

        // Create JSON list of required classes.
        ElementPtr required_classes_element = Element::createList();
        auto const& required_classes = subnet->getRequiredClasses();
        for (auto const& required_class : required_classes) {
            required_classes_element->add(Element::create(required_class));
        }

        // Create binding for DDNS replace client name mode.
        MySqlBindingPtr ddns_rcn_mode_binding;
        auto ddns_rcn_mode = subnet->getDdnsReplaceClientNameMode(Network::Inheritance::NONE);
        if (!ddns_rcn_mode.unspecified()) {
            ddns_rcn_mode_binding = MySqlBinding::createInteger<uint8_t>(static_cast<uint8_t>
                                                                         (ddns_rcn_mode.get()));
        } else {
            ddns_rcn_mode_binding = MySqlBinding::createNull();
        }

        // Create binding with shared network name if the subnet belongs to a
        // shared network.
        MySqlBindingPtr shared_network_binding;

        SharedNetwork6Ptr shared_network;
        subnet->getSharedNetwork(shared_network);

        // Check if the subnet is associated with a shared network instance.
        // If it is, create the binding using the name of the shared network.
        if (shared_network) {
            shared_network_binding = MySqlBinding::createString(shared_network->getName());

        // If the subnet is associated with a shared network by name (no
        // shared network instance), use this name to create the binding.
        // This may be the case if the subnet is added as a result of
        // receiving a control command that merely specifies shared
        // network name. In that case, it is expected that the shared
        // network data is already stored in the database.
        } else if (!subnet->getSharedNetworkName().empty()) {
            shared_network_binding = MySqlBinding::createString(subnet->getSharedNetworkName());

        // If the subnet is not associated with a shared network, create
        // null binding.
        } else {
             shared_network_binding = MySqlBinding::createNull();
        }

        // Create the binding holding interface_id.
        MySqlBindingPtr interface_id_binding = MySqlBinding::createNull();
        auto opt_iface_id = subnet->getInterfaceId(Network::Inheritance::NONE);
        if (opt_iface_id) {
            auto iface_id_data = opt_iface_id->getData();
            if (!iface_id_data.empty()) {
                interface_id_binding = MySqlBinding::createBlob(iface_id_data.begin(),
                                                                iface_id_data.end());
            }
        }

        // Create input bindings.
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint32_t>(subnet->getID()),
            MySqlBinding::createString(subnet->toText()),
            MySqlBinding::condCreateString(subnet->getClientClass(Network::Inheritance::NONE)),
            MySqlBinding::condCreateString(subnet->getIface(Network::Inheritance::NONE)),
            MySqlBinding::createTimestamp(subnet->getModificationTime()),
            createBinding(subnet->getPreferred(Network::Inheritance::NONE)),
            createMinBinding(subnet->getPreferred(Network::Inheritance::NONE)),
            createMaxBinding(subnet->getPreferred(Network::Inheritance::NONE)),
            MySqlBinding::condCreateBool(subnet->getRapidCommit(Network::Inheritance::NONE)),
            createBinding(subnet->getT2(Network::Inheritance::NONE)),
            createInputRelayBinding(subnet),
            createBinding(subnet->getT1(Network::Inheritance::NONE)),
            createInputRequiredClassesBinding(subnet),
            MySqlBinding::condCreateBool(subnet->getReservationsGlobal(Network::Inheritance::NONE)),
            shared_network_binding,
            createInputContextBinding(subnet),
            createBinding(subnet->getValid(Network::Inheritance::NONE)),
            createMinBinding(subnet->getValid(Network::Inheritance::NONE)),
            createMaxBinding(subnet->getValid(Network::Inheritance::NONE)),
            MySqlBinding::condCreateBool(subnet->getCalculateTeeTimes(Network::Inheritance::NONE)),
            MySqlBinding::condCreateFloat(subnet->getT1Percent(Network::Inheritance::NONE)),
            MySqlBinding::condCreateFloat(subnet->getT2Percent(Network::Inheritance::NONE)),
            interface_id_binding,
            MySqlBinding::condCreateBool(subnet->getDdnsSendUpdates(Network::Inheritance::NONE)),
            MySqlBinding::condCreateBool(subnet->getDdnsOverrideNoUpdate(Network::Inheritance::NONE)),
            MySqlBinding::condCreateBool(subnet->getDdnsOverrideClientUpdate(Network::Inheritance::NONE)),
            ddns_rcn_mode_binding,
            MySqlBinding::condCreateString(subnet->getDdnsGeneratedPrefix(Network::Inheritance::NONE)),
            MySqlBinding::condCreateString(subnet->getDdnsQualifyingSuffix(Network::Inheritance::NONE)),
            MySqlBinding::condCreateBool(subnet->getReservationsInSubnet(Network::Inheritance::NONE)),
            MySqlBinding::condCreateBool(subnet->getReservationsOutOfPool(Network::Inheritance::NONE)),
            MySqlBinding::condCreateFloat(subnet->getCacheThreshold(Network::Inheritance::NONE)),
            condCreateInteger<uint32_t>(subnet->getCacheMaxAge(Network::Inheritance::NONE)),
            MySqlBinding::condCreateString(subnet->getAllocatorType(Network::Inheritance::NONE)),
            MySqlBinding::condCreateString(subnet->getPdAllocatorType(Network::Inheritance::NONE))
        };

        MySqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision audit_revision(this,
                                           MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                                           server_selector, "subnet set", true);

        try {

            // Try to insert subnet. If this duplicates unique key, i.e. this
            // subnet already exists it will throw DuplicateEntry exception in
            // which case we'll try an update.
            conn_.insertQuery(MySqlConfigBackendDHCPv6Impl::INSERT_SUBNET6,
                              in_bindings);

        } catch (const DuplicateEntry&) {
            deletePools6(subnet);
            deletePdPools6(subnet);
            deleteOptions6(ServerSelector::ANY(), subnet);

            // Need to add two more bindings for WHERE clause.
            in_bindings.push_back(MySqlBinding::createInteger<uint32_t>(subnet->getID()));
            in_bindings.push_back(MySqlBinding::createString(subnet->toText()));
            conn_.updateDeleteQuery(MySqlConfigBackendDHCPv6Impl::UPDATE_SUBNET6,
                                    in_bindings);

            MySqlBindingCollection in_server_bindings = {
                MySqlBinding::createInteger<uint32_t>(subnet->getID())
            };
            conn_.updateDeleteQuery(MySqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_SERVER,
                                    in_server_bindings);
        }

        // Insert associations with the servers.
        attachElementToServers(MySqlConfigBackendDHCPv6Impl::INSERT_SUBNET6_SERVER,
                               server_selector,
                               MySqlBinding::createInteger<uint32_t>(subnet->getID()),
                               MySqlBinding::createTimestamp(subnet->getModificationTime()));

        // (Re)create pools.
        for (auto const& pool : subnet->getPools(Lease::TYPE_NA)) {
            createPool6(server_selector, boost::dynamic_pointer_cast<Pool6>(pool),
                        subnet);
        }

        // (Re)create pd pools.
        for (auto const& pd_pool : subnet->getPools(Lease::TYPE_PD)) {
            createPdPool6(server_selector, boost::dynamic_pointer_cast<Pool6>(pd_pool),
                          subnet);
        }

        // (Re)create options.
        auto option_spaces = subnet->getCfgOption()->getOptionSpaceNames();
        for (auto const& option_space : option_spaces) {
            OptionContainerPtr options = subnet->getCfgOption()->getAll(option_space);
            for (auto const& desc : *options) {
                OptionDescriptorPtr desc_copy = OptionDescriptor::create(desc);
                desc_copy->space_name_ = option_space;
                createUpdateOption6(server_selector, subnet->getID(), desc_copy,
                                    true);
            }
        }

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
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(pool->getFirstAddress().toText()),
            MySqlBinding::createString(pool->getLastAddress().toText()),
            MySqlBinding::createInteger<uint32_t>(static_cast<uint32_t>(subnet->getID())),
            MySqlBinding::condCreateString(pool->getClientClass()),
            createInputRequiredClassesBinding(pool),
            createInputContextBinding(pool),
            MySqlBinding::createTimestamp(subnet->getModificationTime())
        };

        // Run INSERT.
        conn_.insertQuery(INSERT_POOL6, in_bindings);

        uint64_t pool_id = mysql_insert_id(conn_.mysql_);
        auto option_spaces = pool->getCfgOption()->getOptionSpaceNames();
        for (auto const& option_space : option_spaces) {
            OptionContainerPtr options = pool->getCfgOption()->getAll(option_space);
            for (auto const& desc : *options) {
                OptionDescriptorPtr desc_copy = OptionDescriptor::create(desc);
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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(pd_pool->getFirstAddress().toText()),
            MySqlBinding::createInteger<uint8_t>(static_cast<uint8_t>(plen)),
            MySqlBinding::createInteger<uint8_t>(pd_pool->getLength()),
            MySqlBinding::createInteger<uint32_t>(static_cast<uint32_t>(subnet->getID())),
            MySqlBinding::condCreateString(xprefix_txt),
            MySqlBinding::createInteger<uint8_t>(xlen),
            MySqlBinding::condCreateString(pd_pool->getClientClass()),
            createInputRequiredClassesBinding(pd_pool),
            createInputContextBinding(pd_pool),
            MySqlBinding::createTimestamp(subnet->getModificationTime())
        };

        // Run INSERT.
        conn_.insertQuery(INSERT_PD_POOL, in_bindings);

        uint64_t pd_pool_id = mysql_insert_id(conn_.mysql_);
        auto option_spaces = pd_pool->getCfgOption()->getOptionSpaceNames();
        for (auto const& option_space : option_spaces) {
            OptionContainerPtr options = pd_pool->getCfgOption()->getAll(option_space);
            for (auto const& desc : *options) {
                OptionDescriptorPtr desc_copy = OptionDescriptor::create(desc);
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
        MySqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
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
                     MySqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_ID_ANY :
                     MySqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_ID_WITH_TAG);
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
                     MySqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_PREFIX_ANY :
                     MySqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_PREFIX_WITH_TAG);
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
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint32_t>(subnet->getID()),
            MySqlBinding::createString(subnet->toText())
        };

        // Run DELETE.
        return (conn_.updateDeleteQuery(DELETE_POOLS6, in_bindings));
    }

    /// @brief Deletes prefix delegation pools belonging to a subnet from
    /// the database.
    ///
    /// The query deletes all pd pools associated with the subnet's
    /// identifier or prefix.
    /// @param subnet Pointer to the subnet for which pd pools should be
    /// deleted.
    uint64_t deletePdPools6(const Subnet6Ptr& subnet) {
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint32_t>(subnet->getID()),
            MySqlBinding::createString(subnet->toText())
        };

        // Run DELETE.
        return (conn_.updateDeleteQuery(DELETE_PD_POOLS, in_bindings));
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
                            const MySqlBindingCollection& in_bindings,
                            SharedNetwork6Collection& shared_networks) {
        // Create output bindings. The order must match that in the prepared
        // statement. Please put comments only at the end of line so
        // line counting and indexing match.
        // The server tag must be the last field.
        MySqlBindingCollection out_bindings = {
            MySqlBinding::createInteger<uint64_t>(), // id
            MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // name
            MySqlBinding::createString(CLIENT_CLASS_BUF_LENGTH), // client_class
            MySqlBinding::createString(INTERFACE_BUF_LENGTH), // interface
            MySqlBinding::createTimestamp(), // modification_ts
            MySqlBinding::createInteger<uint32_t>(), // preferred_lifetime
            MySqlBinding::createInteger<uint8_t>(), // rapid_commit
            MySqlBinding::createInteger<uint32_t>(), // rebind_timer
            MySqlBinding::createString(RELAY_BUF_LENGTH), // relay
            MySqlBinding::createInteger<uint32_t>(), // renew_timer
            MySqlBinding::createString(REQUIRE_CLIENT_CLASSES_BUF_LENGTH), // require_client_classes
            MySqlBinding::createInteger<uint8_t>(), // reservations_global
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // user_context
            MySqlBinding::createInteger<uint32_t>(), // valid_lifetime
            MySqlBinding::createInteger<uint64_t>(), // option: option_id
            MySqlBinding::createInteger<uint16_t>(), // option: code
            MySqlBinding::createBlob(OPTION_VALUE_BUF_LENGTH), // option: value
            MySqlBinding::createString(FORMATTED_OPTION_VALUE_BUF_LENGTH), // option: formatted_value
            MySqlBinding::createString(OPTION_SPACE_BUF_LENGTH), // option: space
            MySqlBinding::createInteger<uint8_t>(), // option: persistent
            MySqlBinding::createInteger<uint8_t>(), // option: cancelled
            MySqlBinding::createInteger<uint32_t>(), // option: dhcp6_subnet_id
            MySqlBinding::createInteger<uint8_t>(), // option: scope_id
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // option: user_context
            MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // option: shared_network_name
            MySqlBinding::createInteger<uint64_t>(), // option: pool_id
            MySqlBinding::createTimestamp(), // option: modification_ts
            MySqlBinding::createInteger<uint64_t>(), // option: pd_pool_id
            MySqlBinding::createInteger<uint8_t>(), // calculate_tee_times
            MySqlBinding::createInteger<float>(), // t1_percent
            MySqlBinding::createInteger<float>(), // t2_percent
            MySqlBinding::createBlob(INTERFACE_ID_BUF_LENGTH), // interface_id
            MySqlBinding::createInteger<uint32_t>(), // min_preferred_lifetime
            MySqlBinding::createInteger<uint32_t>(), // max_preferred_lifetime
            MySqlBinding::createInteger<uint32_t>(), // min_valid_lifetime
            MySqlBinding::createInteger<uint32_t>(), // max_valid_lifetime
            MySqlBinding::createInteger<uint8_t>(), // ddns_send_updates
            MySqlBinding::createInteger<uint8_t>(), // ddns_override_no_update
            MySqlBinding::createInteger<uint8_t>(), // ddns_override_client_update
            MySqlBinding::createInteger<uint8_t>(), // ddns_replace_client_name
            MySqlBinding::createString(DNS_NAME_BUF_LENGTH), // ddns_generated_prefix
            MySqlBinding::createString(DNS_NAME_BUF_LENGTH), // ddns_qualifying_suffix
            MySqlBinding::createInteger<uint8_t>(), // reservations_in_subnet
            MySqlBinding::createInteger<uint8_t>(), // reservations_out_of_pool
            MySqlBinding::createInteger<float>(), // cache_threshold
            MySqlBinding::createInteger<uint32_t>(), // cache_max_age
            MySqlBinding::createString(ALLOCATOR_TYPE_BUF_LENGTH), // allocator
            MySqlBinding::createString(ALLOCATOR_TYPE_BUF_LENGTH), // pd_allocator
            MySqlBinding::createString(SERVER_TAG_BUF_LENGTH) // server_tag
        };

        uint64_t last_network_id = 0;
        uint64_t last_option_id = 0;
        std::string last_tag;

        conn_.selectQuery(index, in_bindings, out_bindings,
                          [this, &shared_networks, &last_network_id, &last_option_id,
                           &last_tag]
                          (MySqlBindingCollection& out_bindings) {
            SharedNetwork6Ptr last_network;
            if (!shared_networks.empty()) {
                last_network = *shared_networks.rbegin();
            }

            // If this is the first shared network or the shared network id in this
            // row points to the next shared network we use the data in the
            // row to create the new shared network instance.
            if (last_network_id != out_bindings[0]->getInteger<uint64_t>()) {
                // Reset per shared network component tracking and server tag because
                // we're now starting to process a new shared network.
                last_option_id = 0;
                last_tag.clear();

                // id at 0.
                last_network_id = out_bindings[0]->getInteger<uint64_t>();

                // name at 1.
                last_network = SharedNetwork6::create(out_bindings[1]->getString());
                last_network->setId(last_network_id);

                // client_class at 2.
                if (!out_bindings[2]->amNull()) {
                    last_network->allowClientClass(out_bindings[2]->getString());
                }

                // interface at 3.
                if (!out_bindings[3]->amNull()) {
                    last_network->setIface(out_bindings[3]->getString());
                }

                // modification_ts at 4.
                last_network->setModificationTime(out_bindings[4]->getTimestamp());

                // preferred_lifetime at 5.
                // min_preferred_lifetime at 32.
                // max_preferred_lifetime at 33.
                if (!out_bindings[5]->amNull()) {
                    last_network->setPreferred(createTriplet(out_bindings[5],
                                                             out_bindings[32],
                                                             out_bindings[33]));
                }

                // rapid_commit at 6.
                if (!out_bindings[6]->amNull()) {
                    last_network->setRapidCommit(out_bindings[6]->getBool());
                }

                // rebind_timer at 7.
                if (!out_bindings[7]->amNull()) {
                    last_network->setT2(createTriplet(out_bindings[7]));
                }

                // relay at 8.
                ElementPtr relay_element = out_bindings[8]->getJSON();
                if (relay_element) {
                    if (relay_element->getType() != Element::list) {
                        isc_throw(BadValue, "invalid relay value "
                                  << out_bindings[8]->getString());
                    }
                    for (auto i = 0; i < relay_element->size(); ++i) {
                        auto relay_address_element = relay_element->get(i);
                        if (relay_address_element->getType() != Element::string) {
                            isc_throw(BadValue, "relay address must be a string");
                        }
                        last_network->addRelayAddress(IOAddress(relay_element->get(i)->stringValue()));
                    }
                }

                // renew_timer at 9.
                if (!out_bindings[9]->amNull()) {
                    last_network->setT1(createTriplet(out_bindings[9]));
                }

                // require_client_classes at 10.
                ElementPtr require_element = out_bindings[10]->getJSON();
                if (require_element) {
                    if (require_element->getType() != Element::list) {
                        isc_throw(BadValue, "invalid require_client_classes value "
                              << out_bindings[10]->getString());
                    }
                    for (auto i = 0; i < require_element->size(); ++i) {
                        auto require_item = require_element->get(i);
                        if (require_item->getType() != Element::string) {
                            isc_throw(BadValue, "elements of require_client_classes list must"
                                      "be valid strings");
                        }
                        last_network->requireClientClass(require_item->stringValue());
                    }
                }

                // reservations_global at 11.
                if (!out_bindings[11]->amNull()) {
                    last_network->setReservationsGlobal(out_bindings[11]->getBool());
                }

                // user_context at 12.
                ElementPtr user_context = out_bindings[12]->getJSON();
                if (user_context) {
                    last_network->setContext(user_context);
                }

                // valid_lifetime at 13.
                // min_valid_lifetime at 34.
                // max_valid_lifetime at 35.
                if (!out_bindings[13]->amNull()) {
                    last_network->setValid(createTriplet(out_bindings[13],
                                                         out_bindings[34],
                                                         out_bindings[35]));
                }

                // 14 to 27 are option.

                // calculate_tee_times at 28.
                if (!out_bindings[28]->amNull()) {
                    last_network->setCalculateTeeTimes(out_bindings[28]->getBool());
                }

                // t1_percent at 29.
                if (!out_bindings[29]->amNull()) {
                    last_network->setT1Percent(out_bindings[29]->getFloat());
                }

                // t2_percent at 30.
                if (!out_bindings[30]->amNull()) {
                    last_network->setT2Percent(out_bindings[30]->getFloat());
                }

                // interface_id at 31.
                if (!out_bindings[31]->amNull()) {
                    auto iface_id_data = out_bindings[31]->getBlob();
                    if (!iface_id_data.empty()) {
                        OptionPtr opt_iface_id(new Option(Option::V6, D6O_INTERFACE_ID,
                                                          iface_id_data));
                        last_network->setInterfaceId(opt_iface_id);
                    }
                }

                // min_preferred_lifetime at 32.
                // max_preferred_lifetime at 33.
                // min_valid_lifetime at 34.
                // max_valid_lifetime at 35.

                // ddns_send_updates at 36.
                if (!out_bindings[36]->amNull()) {
                    last_network->setDdnsSendUpdates(out_bindings[36]->getBool());
                }

                // ddns_override_no_update at 37.
                if (!out_bindings[37]->amNull()) {
                    last_network->setDdnsOverrideNoUpdate(out_bindings[37]->getBool());
                }

                // ddns_override_client_update at 38.
                if (!out_bindings[38]->amNull()) {
                    last_network->setDdnsOverrideClientUpdate(out_bindings[38]->getBool());
                }

                // ddns_replace_client_name at 39.
                if (!out_bindings[39]->amNull()) {
                    last_network->setDdnsReplaceClientNameMode(static_cast<D2ClientConfig::ReplaceClientNameMode>
                        (out_bindings[39]->getInteger<uint8_t>()));
                }

                // ddns_generated_prefix at 40.
                if (!out_bindings[40]->amNull()) {
                    last_network->setDdnsGeneratedPrefix(out_bindings[40]->getString());
                }

                // ddns_qualifying_suffix at 41.
                if (!out_bindings[41]->amNull()) {
                    last_network->setDdnsQualifyingSuffix(out_bindings[41]->getString());
                }

                // reservations_in_subnet at 42.
                if (!out_bindings[42]->amNull()) {
                    last_network->setReservationsInSubnet(out_bindings[42]->getBool());
                }

                // reservations_in_subnet at 43.
                if (!out_bindings[43]->amNull()) {
                    last_network->setReservationsOutOfPool(out_bindings[43]->getBool());
                }

                // cache_threshold at 44.
                if (!out_bindings[44]->amNull()) {
                    last_network->setCacheThreshold(out_bindings[44]->getFloat());
                }

                // cache_max_age at 45.
                if (!out_bindings[45]->amNull()) {
                    last_network->setCacheMaxAge(out_bindings[45]->getInteger<uint32_t>());
                }

                // allocator at 46.
                if (!out_bindings[46]->amNull()) {
                    last_network->setAllocatorType(out_bindings[46]->getString());
                }

                // pd_allocator at 47.
                if (!out_bindings[47]->amNull()) {
                    last_network->setPdAllocatorType(out_bindings[47]->getString());
                }

                // server_tag at 48.

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
            if (!out_bindings[48]->amNull() &&
                (last_tag != out_bindings[48]->getString())) {
                last_tag = out_bindings[48]->getString();
                if (!last_tag.empty() && !last_network->hasServerTag(ServerTag(last_tag))) {
                    last_network->setServerTag(last_tag);
                }
            }

            // Parse option from 14 to 27.
            if (!out_bindings[14]->amNull() &&
                (last_option_id < out_bindings[14]->getInteger<uint64_t>())) {
                last_option_id = out_bindings[14]->getInteger<uint64_t>();

                OptionDescriptorPtr desc = processOptionRow(Option::V6, out_bindings.begin() + 14);
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

        MySqlBindingCollection in_bindings = { MySqlBinding::createString(name) };

        auto index = GET_SHARED_NETWORK6_NAME_NO_TAG;
        if (server_selector.amUnassigned()) {
            index = GET_SHARED_NETWORK6_NAME_UNASSIGNED;
        } else if (server_selector.amAny()) {
            index = GET_SHARED_NETWORK6_NAME_ANY;
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

        auto index = (server_selector.amUnassigned() ? GET_ALL_SHARED_NETWORKS6_UNASSIGNED :
                      GET_ALL_SHARED_NETWORKS6);
        MySqlBindingCollection in_bindings;
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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createTimestamp(modification_ts)
        };

        auto index = (server_selector.amUnassigned() ? GET_MODIFIED_SHARED_NETWORKS6_UNASSIGNED :
                      GET_MODIFIED_SHARED_NETWORKS6);
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

        // Create the binding holding interface_id.
        MySqlBindingPtr interface_id_binding = MySqlBinding::createNull();
        auto opt_iface_id = shared_network->getInterfaceId(Network::Inheritance::NONE);
        if (opt_iface_id) {
            auto iface_id_data = opt_iface_id->getData();
            if (!iface_id_data.empty()) {
                interface_id_binding = MySqlBinding::createBlob(iface_id_data.begin(),
                                                                iface_id_data.end());
            }
        }

        // Create binding for DDNS replace client name mode.
        MySqlBindingPtr ddns_rcn_mode_binding;
        auto ddns_rcn_mode = shared_network->getDdnsReplaceClientNameMode(Network::Inheritance::NONE);
        if (!ddns_rcn_mode.unspecified()) {
            ddns_rcn_mode_binding = MySqlBinding::createInteger<uint8_t>(static_cast<uint8_t>
                                                                         (ddns_rcn_mode.get()));
        } else {
            ddns_rcn_mode_binding = MySqlBinding::createNull();
        }

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(shared_network->getName()),
            MySqlBinding::condCreateString(shared_network->getClientClass(Network::Inheritance::NONE)),
            MySqlBinding::condCreateString(shared_network->getIface(Network::Inheritance::NONE)),
            MySqlBinding::createTimestamp(shared_network->getModificationTime()),
            createBinding(shared_network->getPreferred(Network::Inheritance::NONE)),
            createMinBinding(shared_network->getPreferred(Network::Inheritance::NONE)),
            createMaxBinding(shared_network->getPreferred(Network::Inheritance::NONE)),
            MySqlBinding::condCreateBool(shared_network->getRapidCommit(Network::Inheritance::NONE)),
            createBinding(shared_network->getT2(Network::Inheritance::NONE)),
            createInputRelayBinding(shared_network),
            createBinding(shared_network->getT1(Network::Inheritance::NONE)),
            createInputRequiredClassesBinding(shared_network),
            MySqlBinding::condCreateBool(shared_network->getReservationsGlobal(Network::Inheritance::NONE)),
            createInputContextBinding(shared_network),
            createBinding(shared_network->getValid(Network::Inheritance::NONE)),
            createMinBinding(shared_network->getValid(Network::Inheritance::NONE)),
            createMaxBinding(shared_network->getValid(Network::Inheritance::NONE)),
            MySqlBinding::condCreateBool(shared_network->getCalculateTeeTimes(Network::Inheritance::NONE)),
            MySqlBinding::condCreateFloat(shared_network->getT1Percent(Network::Inheritance::NONE)),
            MySqlBinding::condCreateFloat(shared_network->getT2Percent(Network::Inheritance::NONE)),
            interface_id_binding,
            MySqlBinding::condCreateBool(shared_network->getDdnsSendUpdates(Network::Inheritance::NONE)),
            MySqlBinding::condCreateBool(shared_network->getDdnsOverrideNoUpdate(Network::Inheritance::NONE)),
            MySqlBinding::condCreateBool(shared_network->getDdnsOverrideClientUpdate(Network::Inheritance::NONE)),
            ddns_rcn_mode_binding,
            MySqlBinding::condCreateString(shared_network->getDdnsGeneratedPrefix(Network::Inheritance::NONE)),
            MySqlBinding::condCreateString(shared_network->getDdnsQualifyingSuffix(Network::Inheritance::NONE)),
            MySqlBinding::condCreateBool(shared_network->getReservationsInSubnet(Network::Inheritance::NONE)),
            MySqlBinding::condCreateBool(shared_network->getReservationsOutOfPool(Network::Inheritance::NONE)),
            MySqlBinding::condCreateFloat(shared_network->getCacheThreshold(Network::Inheritance::NONE)),
            condCreateInteger<uint32_t>(shared_network->getCacheMaxAge(Network::Inheritance::NONE)),
            MySqlBinding::condCreateString(shared_network->getAllocatorType(Network::Inheritance::NONE)),
            MySqlBinding::condCreateString(shared_network->getPdAllocatorType(Network::Inheritance::NONE))
        };

        MySqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           server_selector, "shared network set", true);

        try {

            // Try to insert shared network. The shared network name must be unique,
            // so if inserting fails with DuplicateEntry exception we'll need to
            // update existing shared network entry.
            conn_.insertQuery(MySqlConfigBackendDHCPv6Impl::INSERT_SHARED_NETWORK6,
                              in_bindings);

        } catch (const DuplicateEntry&) {
            deleteOptions6(ServerSelector::ANY(), shared_network);

            // Need to add one more binding for WHERE clause.
            in_bindings.push_back(MySqlBinding::createString(shared_network->getName()));
            conn_.updateDeleteQuery(MySqlConfigBackendDHCPv6Impl::UPDATE_SHARED_NETWORK6,
                                    in_bindings);

            MySqlBindingCollection in_server_bindings = {
                MySqlBinding::createString(shared_network->getName())
            };
            conn_.updateDeleteQuery(MySqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_SERVER,
                                    in_server_bindings);
        }

        // Associate the shared network with the servers.
        attachElementToServers(MySqlConfigBackendDHCPv6Impl::INSERT_SHARED_NETWORK6_SERVER,
                               server_selector,
                               MySqlBinding::createString(shared_network->getName()),
                               MySqlBinding::createTimestamp(shared_network->getModificationTime()));

        // (Re)create options.
        auto option_spaces = shared_network->getCfgOption()->getOptionSpaceNames();
        for (auto const& option_space : option_spaces) {
            OptionContainerPtr options = shared_network->getCfgOption()->getAll(option_space);
            for (auto const& desc : *options) {
                OptionDescriptorPtr desc_copy = OptionDescriptor::create(desc);
                desc_copy->space_name_ = option_space;
                createUpdateOption6(server_selector, shared_network->getName(),
                                    desc_copy, true);
            }
        }

        transaction.commit();
    }

    /// @brief Sends query to insert DHCP option.
    ///
    /// This method expects that the server selector contains exactly one
    /// server tag.
    ///
    /// @param server_selector Server selector.
    /// @param in_bindings Collection of bindings representing an option.
    void insertOption6(const ServerSelector& server_selector,
                       const MySqlBindingCollection& in_bindings) {
        conn_.insertQuery(MySqlConfigBackendDHCPv6Impl::INSERT_OPTION6,
                          in_bindings);

        // Fetch primary key value of the inserted option. We will use it in the
        // next INSERT statement to associate this option with the server.
        auto option_id = mysql_insert_id(conn_.mysql_);

        // Timestamp is expected to be in this input binding.
        auto timestamp_binding = in_bindings[12];

        // Associate the option with the servers.
        attachElementToServers(MySqlConfigBackendDHCPv6Impl::INSERT_OPTION6_SERVER,
                               server_selector,
                               MySqlBinding::createInteger<uint64_t>(option_id),
                               timestamp_binding);
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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint16_t>(option->option_->getType()),
            createOptionValueBinding(option),
            MySqlBinding::condCreateString(option->formatted_value_),
            MySqlBinding::condCreateString(option->space_name_),
            MySqlBinding::createBool(option->persistent_),
            MySqlBinding::createBool(option->cancelled_),
            MySqlBinding::createNull(),
            MySqlBinding::createNull(),
            MySqlBinding::createInteger<uint8_t>(0),
            createInputContextBinding(option),
            MySqlBinding::createNull(),
            MySqlBinding::createNull(),
            MySqlBinding::createTimestamp(option->getModificationTime()),
            MySqlBinding::createNull(),
            MySqlBinding::createString(tag),
            MySqlBinding::createInteger<uint8_t>(option->option_->getType()),
            MySqlBinding::condCreateString(option->space_name_)
        };

        MySqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           server_selector, "global option set", false);

        if (conn_.updateDeleteQuery(MySqlConfigBackendDHCPv6Impl::UPDATE_OPTION6,
                                    in_bindings) == 0) {
            // Remove the 3 bindings used only in case of update.
            in_bindings.resize(in_bindings.size() - 3);
            insertOption6(server_selector, in_bindings);
        }

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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint16_t>(option->option_->getType()),
            createOptionValueBinding(option),
            MySqlBinding::condCreateString(option->formatted_value_),
            MySqlBinding::condCreateString(option->space_name_),
            MySqlBinding::createBool(option->persistent_),
            MySqlBinding::createBool(option->cancelled_),
            MySqlBinding::createNull(),
            MySqlBinding::createInteger<uint32_t>(static_cast<uint32_t>(subnet_id)),
            MySqlBinding::createInteger<uint8_t>(1),
            createInputContextBinding(option),
            MySqlBinding::createNull(),
            MySqlBinding::createNull(),
            MySqlBinding::createTimestamp(option->getModificationTime()),
            MySqlBinding::createNull(),
            MySqlBinding::createInteger<uint32_t>(static_cast<uint32_t>(subnet_id)),
            MySqlBinding::createInteger<uint16_t>(option->option_->getType()),
            MySqlBinding::condCreateString(option->space_name_)
        };

        boost::scoped_ptr<MySqlTransaction> transaction;
        // Only start new transaction if specified to do so. This function may
        // be called from within an existing transaction in which case we
        // don't start the new one.
        if (!cascade_update) {
            transaction.reset(new MySqlTransaction(conn_));
        }

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           server_selector, "subnet specific option set",
                           cascade_update);

        if (conn_.updateDeleteQuery(MySqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_SUBNET_ID,
                                    in_bindings) == 0) {
            // Remove the 3 bindings used only in case of update.
            in_bindings.resize(in_bindings.size() - 3);
            insertOption6(server_selector, in_bindings);
        }

        if (transaction) {
            transaction->commit();
        }
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

        MySqlBindingCollection in_bindings;
        // code
        in_bindings.push_back(MySqlBinding::createInteger<uint16_t>(option->option_->getType()));
        // value
        in_bindings.push_back(createOptionValueBinding(option));
        // formatted_value
        in_bindings.push_back(MySqlBinding::condCreateString(option->formatted_value_));
        // space
        in_bindings.push_back(MySqlBinding::condCreateString(option->space_name_));
        // persistent
        in_bindings.push_back(MySqlBinding::createBool(option->persistent_));
        // cancelled
        in_bindings.push_back(MySqlBinding::createBool(option->cancelled_));
        // dhcp_client_class
        in_bindings.push_back(MySqlBinding::createNull());
        // dhcp[46]_subnet_id
        in_bindings.push_back(MySqlBinding::createNull());
        // scope_id
        if (pool_type == Lease::TYPE_NA) {
            in_bindings.push_back(MySqlBinding::createInteger<uint8_t>(5));
        } else {
            in_bindings.push_back(MySqlBinding::createInteger<uint8_t>(6));
        }
        // user_context
        in_bindings.push_back(createInputContextBinding(option));
        // shared_network_name
        in_bindings.push_back(MySqlBinding::createNull());
        // pool_id
        if (pool_type == Lease::TYPE_NA) {
            in_bindings.push_back(MySqlBinding::createInteger<uint64_t>(pool_id));
        } else {
            in_bindings.push_back(MySqlBinding::createNull());
        }
        // modification_ts
        in_bindings.push_back(MySqlBinding::createTimestamp(option->getModificationTime()));
        // pd_pool_id
        if (pool_type == Lease::TYPE_PD) {
            in_bindings.push_back(MySqlBinding::createInteger<uint64_t>(pool_id));
        } else {
            in_bindings.push_back(MySqlBinding::createNull());
        }

        // Insert bindings used only during the update.
        in_bindings.push_back(MySqlBinding::createInteger<uint64_t>(pool_id));
        in_bindings.push_back(MySqlBinding::createInteger<uint16_t>(option->option_->getType()));
        in_bindings.push_back(MySqlBinding::condCreateString(option->space_name_));

        MySqlTransaction transaction(conn_);

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
                           MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           server_selector, msg, cascade_update);

        auto index = (pool_type == Lease::TYPE_NA ?
                      MySqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_POOL_ID :
                      MySqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_PD_POOL_ID);
        if (conn_.updateDeleteQuery(index, in_bindings) == 0) {
            // Remove the 3 bindings used only in case of update.
            in_bindings.resize(in_bindings.size() - 3);
            insertOption6(server_selector, in_bindings);
        }

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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint16_t>(option->option_->getType()),
            createOptionValueBinding(option),
            MySqlBinding::condCreateString(option->formatted_value_),
            MySqlBinding::condCreateString(option->space_name_),
            MySqlBinding::createBool(option->persistent_),
            MySqlBinding::createBool(option->cancelled_),
            MySqlBinding::createNull(),
            MySqlBinding::createNull(),
            MySqlBinding::createInteger<uint8_t>(4),
            createInputContextBinding(option),
            MySqlBinding::createString(shared_network_name),
            MySqlBinding::createNull(),
            MySqlBinding::createTimestamp(option->getModificationTime()),
            MySqlBinding::createNull(),
            MySqlBinding::createString(shared_network_name),
            MySqlBinding::createInteger<uint16_t>(option->option_->getType()),
            MySqlBinding::condCreateString(option->space_name_)
        };

        boost::scoped_ptr<MySqlTransaction> transaction;
        // Only start new transaction if specified to do so. This function may
        // be called from within an existing transaction in which case we
        // don't start the new one.
        if (!cascade_update) {
            transaction.reset(new MySqlTransaction(conn_));
        }

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           server_selector, "shared network specific option set",
                           cascade_update);

        if (conn_.updateDeleteQuery(MySqlConfigBackendDHCPv6Impl::
                                    UPDATE_OPTION6_SHARED_NETWORK,
                                    in_bindings) == 0) {
            // Remove the 3 bindings used only in case of update.
            in_bindings.resize(in_bindings.size() - 3);
            insertOption6(server_selector, in_bindings);
        }

        if (transaction) {
            transaction->commit();
        }
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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint16_t>(option->option_->getType()),
            createOptionValueBinding(option),
            MySqlBinding::condCreateString(option->formatted_value_),
            MySqlBinding::condCreateString(option->space_name_),
            MySqlBinding::createBool(option->persistent_),
            MySqlBinding::createBool(option->cancelled_),
            MySqlBinding::createString(client_class->getName()),
            MySqlBinding::createNull(),
            MySqlBinding::createInteger<uint8_t>(2),
            createInputContextBinding(option),
            MySqlBinding::createNull(),
            MySqlBinding::createNull(),
            MySqlBinding::createTimestamp(option->getModificationTime()),
            MySqlBinding::createNull(),
            MySqlBinding::createString(client_class->getName()),
            MySqlBinding::createInteger<uint8_t>(option->option_->getType()),
            MySqlBinding::condCreateString(option->space_name_)
        };

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           server_selector, "client class specific option set",
                           true);

        if (conn_.updateDeleteQuery(MySqlConfigBackendDHCPv6Impl::
                                    UPDATE_OPTION6_CLIENT_CLASS,
                                    in_bindings) == 0) {
            // Remove the 3 bindings used only in case of update.
            in_bindings.resize(in_bindings.size() - 3);
            insertOption6(server_selector, in_bindings);
        }
    }

    /// @brief Sends query to insert or update option definition.
    ///
    /// @param server_selector Server selector.
    /// @param option_def Pointer to the option definition to be inserted or updated.
    void createUpdateOptionDef6(const ServerSelector& server_selector,
                                const OptionDefinitionPtr& option_def) {
        createUpdateOptionDef(server_selector, option_def, DHCP6_OPTION_SPACE,
                              MySqlConfigBackendDHCPv6Impl::GET_OPTION_DEF6_CODE_SPACE,
                              MySqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6,
                              MySqlConfigBackendDHCPv6Impl::UPDATE_OPTION_DEF6,
                              MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                              MySqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6_SERVER);
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
        createUpdateOptionDef(server_selector, option_def, DHCP6_OPTION_SPACE,
                              MySqlConfigBackendDHCPv6Impl::GET_OPTION_DEF6_CODE_SPACE,
                              MySqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6_CLIENT_CLASS,
                              MySqlConfigBackendDHCPv6Impl::UPDATE_OPTION_DEF6_CLIENT_CLASS,
                              MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                              MySqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6_SERVER,
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
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint16_t>(code),
            MySqlBinding::createString(space)
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTION_DEF6_CODE_NAME, server_selector,
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
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(client_class->getName())
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTION_DEFS6_CLIENT_CLASS, server_selector,
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
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint16_t>(code),
            MySqlBinding::createString(space)
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTION6, server_selector,
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
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint32_t>(static_cast<uint32_t>(subnet_id)),
            MySqlBinding::createInteger<uint16_t>(code),
            MySqlBinding::createString(space)
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTION6_SUBNET_ID, server_selector,
                                    "deleting option for a subnet",
                                    "subnet specific option deleted",
                                    false,
                                    in_bindings));
    }

    /// @brief Deletes pool level option.
    ///
    /// @param server_selector Server selector.
    /// @param pool_start_address Lower bound pool address.
    /// @param pool_end_address Upper bound pool address.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    uint64_t deleteOption6(const db::ServerSelector& server_selector,
                           const IOAddress& pool_start_address,
                           const IOAddress& pool_end_address,
                           const uint16_t code,
                           const std::string& space) {
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint16_t>(code),
            MySqlBinding::createString(space),
            MySqlBinding::createString(pool_start_address.toText()),
            MySqlBinding::createString(pool_end_address.toText())
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTION6_POOL_RANGE, server_selector,
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
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint16_t>(code),
            MySqlBinding::createString(space),
            MySqlBinding::createString(pd_pool_prefix.toText()),
            MySqlBinding::createInteger<uint8_t>(pd_pool_prefix_length)
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTION6_PD_POOL, server_selector,
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
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(shared_network_name),
            MySqlBinding::createInteger<uint16_t>(code),
            MySqlBinding::createString(space)
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTION6_SHARED_NETWORK, server_selector,
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
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint32_t>(subnet->getID()),
            MySqlBinding::createString(subnet->toText())
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTIONS6_SUBNET_ID_PREFIX, server_selector,
                                    "deleting options for a subnet",
                                    "subnet specific options deleted",
                                    true,
                                    in_bindings));
    }

    /// @brief Deletes options belonging to a shared network from the database.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Pointer to the subnet for which options should be
    /// deleted.
    /// @return Number of deleted options.
    uint64_t deleteOptions6(const ServerSelector& server_selector,
                            const SharedNetwork6Ptr& shared_network) {
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(shared_network->getName())
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTIONS6_SHARED_NETWORK, server_selector,
                                    "deleting options for a shared network",
                                    "shared network specific options deleted",
                                    true,
                                    in_bindings));
    }

    /// @brief Deletes options belonging to a client class from the database.
    ///
    /// @param server_selector Server selector.
    /// @param client_class Pointer to the client class for which options
    /// should be deleted.
    /// @return Number of deleted options.
    uint64_t deleteOptions6(const ServerSelector& server_selector,
                            const ClientClassDefPtr& client_class) {
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(client_class->getName())
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTIONS6_CLIENT_CLASS, server_selector,
                                    "deleting options for a client class",
                                    "client class specific options deleted",
                                    true,
                                    in_bindings));
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
                           const MySqlBindingCollection& in_bindings,
                           ClientClassDictionary& client_classes) {
        MySqlBindingCollection out_bindings = {
            MySqlBinding::createInteger<uint64_t>(), // id
            MySqlBinding::createString(CLIENT_CLASS_NAME_BUF_LENGTH), // name
            MySqlBinding::createString(CLIENT_CLASS_TEST_BUF_LENGTH), // test
            MySqlBinding::createInteger<uint8_t>(), // required
            MySqlBinding::createInteger<uint32_t>(), // valid lifetime
            MySqlBinding::createInteger<uint32_t>(), // min valid lifetime
            MySqlBinding::createInteger<uint32_t>(), // max valid lifetime
            MySqlBinding::createInteger<uint8_t>(), // depend on known directly
            MySqlBinding::createInteger<uint8_t>(), // depend on known indirectly
            MySqlBinding::createTimestamp(), // modification_ts
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // user_context
            MySqlBinding::createInteger<uint64_t>(), // option def: id
            MySqlBinding::createInteger<uint16_t>(), // option def: code
            MySqlBinding::createString(OPTION_NAME_BUF_LENGTH), // option def: name
            MySqlBinding::createString(OPTION_SPACE_BUF_LENGTH), // option def: space
            MySqlBinding::createInteger<uint8_t>(), // option def: type
            MySqlBinding::createTimestamp(), // option def: modification_ts
            MySqlBinding::createInteger<uint8_t>(), // option def: array
            MySqlBinding::createString(OPTION_ENCAPSULATE_BUF_LENGTH), // option def: encapsulate
            MySqlBinding::createString(OPTION_RECORD_TYPES_BUF_LENGTH), // option def: record_types
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // option def: user_context
            MySqlBinding::createInteger<uint64_t>(), // option: option_id
            MySqlBinding::createInteger<uint16_t>(), // option: code
            MySqlBinding::createBlob(OPTION_VALUE_BUF_LENGTH), // option: value
            MySqlBinding::createString(FORMATTED_OPTION_VALUE_BUF_LENGTH), // option: formatted_value
            MySqlBinding::createString(OPTION_SPACE_BUF_LENGTH), // option: space
            MySqlBinding::createInteger<uint8_t>(), // option: persistent
            MySqlBinding::createInteger<uint8_t>(), // option: cancelled
            MySqlBinding::createInteger<uint32_t>(), // option: dhcp6_subnet_id
            MySqlBinding::createInteger<uint8_t>(), // option: scope_id
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // option: user_context
            MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // option: shared_network_name
            MySqlBinding::createInteger<uint64_t>(), // option: pool_id
            MySqlBinding::createTimestamp(), // option: modification_ts
            MySqlBinding::createString(SERVER_TAG_BUF_LENGTH),// server tag
            MySqlBinding::createInteger<uint32_t>(), // preferred lifetime
            MySqlBinding::createInteger<uint32_t>(), // min preferred lifetime
            MySqlBinding::createInteger<uint32_t>() // max preferred lifetime
        };

        std::list<ClientClassDefPtr> class_list;
        uint64_t last_option_id = 0;
        uint64_t last_option_def_id = 0;
        std::string last_tag;

        conn_.selectQuery(index,
                          in_bindings, out_bindings,
                          [this, &class_list, &last_option_id, &last_option_def_id, &last_tag]
                          (MySqlBindingCollection& out_bindings) {
            ClientClassDefPtr last_client_class;
            if (!class_list.empty()) {
                last_client_class = *class_list.rbegin();
            }

            if (!last_client_class || (last_client_class->getId() != out_bindings[0]->getInteger<uint64_t>())) {
                last_option_id = 0;
                last_option_def_id = 0;
                last_tag.clear();

                auto options = boost::make_shared<CfgOption>();
                auto option_defs = boost::make_shared<CfgOptionDef>();

                last_client_class = boost::make_shared<ClientClassDef>(out_bindings[1]->getString(),
                                                                       ExpressionPtr(), options);
                last_client_class->setCfgOptionDef(option_defs);

                // id
                last_client_class->setId(out_bindings[0]->getInteger<uint64_t>());

                // name
                last_client_class->setName(out_bindings[1]->getString());

                // test
                if (!out_bindings[2]->amNull()) {
                    last_client_class->setTest(out_bindings[2]->getString());
                }

                // required
                if (!out_bindings[3]->amNull()) {
                    last_client_class->setRequired(out_bindings[3]->getBool());
                }

                // valid lifetime: default, min, max
                last_client_class->setValid(createTriplet(out_bindings[4], out_bindings[5], out_bindings[6]));

                // depend on known directly or indirectly
                last_client_class->setDependOnKnown(out_bindings[7]->getBool() || out_bindings[8]->getBool());

                // modification_ts
                last_client_class->setModificationTime(out_bindings[9]->getTimestamp());

                // user_context
                ElementPtr user_context = out_bindings[10]->getJSON();
                if (user_context) {
                    last_client_class->setContext(user_context);
                }

                // preferred lifetime: default, min, max
                last_client_class->setPreferred(createTriplet(out_bindings[35],
                                                              out_bindings[36],
                                                              out_bindings[37]));

                class_list.push_back(last_client_class);
            }

            // server tag
            if (!out_bindings[34]->amNull() &&
                (last_tag != out_bindings[34]->getString())) {
                last_tag = out_bindings[34]->getString();
                if (!last_tag.empty() && !last_client_class->hasServerTag(ServerTag(last_tag))) {
                    last_client_class->setServerTag(last_tag);
                }
            }

            // Parse client class specific option definition from 11 to 20.
            if (!out_bindings[11]->amNull() &&
                (last_option_def_id < out_bindings[11]->getInteger<uint64_t>())) {
                last_option_def_id = out_bindings[11]->getInteger<uint64_t>();

                auto def = processOptionDefRow(out_bindings.begin() + 11);
                if (def) {
                    last_client_class->getCfgOptionDef()->add(def);
                }
            }

            // Parse client class specific option from 21 to 33.
            if (!out_bindings[21]->amNull() &&
                (last_option_id < out_bindings[21]->getInteger<uint64_t>())) {
                last_option_id = out_bindings[21]->getInteger<uint64_t>();

                OptionDescriptorPtr desc = processOptionRow(Option::V6, out_bindings.begin() + 21);
                if (desc) {
                    last_client_class->getCfgOption()->add(*desc, desc->space_name_);
                }
            }
        });

        tossNonMatchingElements(server_selector, class_list);

        for (auto const& c : class_list) {
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
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(name)
        };
        ClientClassDictionary client_classes;
        getClientClasses6(MySqlConfigBackendDHCPv6Impl::GET_CLIENT_CLASS6_NAME,
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
        MySqlBindingCollection in_bindings;
        getClientClasses6(server_selector.amUnassigned() ?
                          MySqlConfigBackendDHCPv6Impl::GET_ALL_CLIENT_CLASSES6_UNASSIGNED :
                          MySqlConfigBackendDHCPv6Impl::GET_ALL_CLIENT_CLASSES6,
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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createTimestamp(modification_ts)
        };
        getClientClasses6(server_selector.amUnassigned() ?
                          GET_MODIFIED_CLIENT_CLASSES6_UNASSIGNED :
                          GET_MODIFIED_CLIENT_CLASSES6,
                          server_selector,
                          in_bindings,
                          client_classes);
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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(client_class->getName()),
            MySqlBinding::createString(client_class->getTest()),
            MySqlBinding::createBool(client_class->getRequired()),
            createBinding(client_class->getValid()),
            createMinBinding(client_class->getValid()),
            createMaxBinding(client_class->getValid()),
            MySqlBinding::createBool(depend_on_known),
            (follow_class_name.empty() ? MySqlBinding::createNull() :
             MySqlBinding::createString(follow_class_name)),
            createBinding(client_class->getPreferred()),
            createMinBinding(client_class->getPreferred()),
            createMaxBinding(client_class->getPreferred()),
            MySqlBinding::createTimestamp(client_class->getModificationTime()),
            createInputContextBinding(client_class)
        };

        MySqlTransaction transaction(conn_);

        ScopedAuditRevision audit_revision(this, MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                                           server_selector, "client class set", true);
        // Keeps track of whether the client class is inserted or updated.
        auto update = false;
        try {
            conn_.insertQuery(MySqlConfigBackendDHCPv6Impl::INSERT_CLIENT_CLASS6, in_bindings);

        } catch (const DuplicateEntry&) {
            // Such class already exists.

            // Delete options and option definitions. They will be re-created from the new class
            // instance.
            deleteOptions6(ServerSelector::ANY(), client_class);
            deleteOptionDefs6(ServerSelector::ANY(), client_class);

            // Try to update the class.
            in_bindings.push_back(MySqlBinding::createString(client_class->getName()));
            if (follow_class_name.empty()) {
                // If position is not specified, leave the class at the same position.
                // Remove the binding which specifies the position and use different
                // query.
                in_bindings.erase(in_bindings.begin() + 7, in_bindings.begin() + 8);
                conn_.updateDeleteQuery(MySqlConfigBackendDHCPv6Impl::UPDATE_CLIENT_CLASS6_SAME_POSITION,
                                        in_bindings);
            } else {
                // Update with specifying the position.
                conn_.updateDeleteQuery(MySqlConfigBackendDHCPv6Impl::UPDATE_CLIENT_CLASS6,
                                        in_bindings);
            }

            // Delete class associations with the servers and dependencies. We will re-create
            // them according to the new class specification.
            MySqlBindingCollection in_assoc_bindings = {
                MySqlBinding::createString(client_class->getName())
            };
            conn_.updateDeleteQuery(MySqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6_DEPENDENCY,
                                    in_assoc_bindings);
            conn_.updateDeleteQuery(MySqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6_SERVER,
                                    in_assoc_bindings);
            update = true;
        }

        // Associate client class with the servers.
        attachElementToServers(MySqlConfigBackendDHCPv6Impl::INSERT_CLIENT_CLASS6_SERVER,
                               server_selector,
                               MySqlBinding::createString(client_class->getName()),
                               MySqlBinding::createTimestamp(client_class->getModificationTime()));

        // Iterate over the captured dependencies and try to insert them into the database.
        for (auto const& dependency : dependencies) {
            try {
                MySqlBindingCollection in_dependency_bindings = {
                    MySqlBinding::createString(client_class->getName()),
                    MySqlBinding::createString(dependency)
                };
                // We deleted earlier dependencies, so we can simply insert new ones.
                conn_.insertQuery(MySqlConfigBackendDHCPv6Impl::INSERT_CLIENT_CLASS6_DEPENDENCY,
                                  in_dependency_bindings);
            } catch (const std::exception& ex) {
                isc_throw(InvalidOperation, "unmet dependency on client class: " << dependency);
            }
        }

        // If we performed client class update we also have to verify that its dependency
        // on KNOWN/UNKNOWN client classes hasn't changed.
        if (update) {
            MySqlBindingCollection in_check_bindings;
            conn_.insertQuery(MySqlConfigBackendDHCPv6Impl::CHECK_CLIENT_CLASS_KNOWN_DEPENDENCY_CHANGE,
                              in_check_bindings);
        }

        // (Re)create option definitions.
        if (client_class->getCfgOptionDef()) {
            auto option_defs = client_class->getCfgOptionDef()->getContainer();
            auto option_spaces = option_defs.getOptionSpaceNames();
            for (auto const& option_space : option_spaces) {
                OptionDefContainerPtr defs = option_defs.getItems(option_space);
                for (auto const& def : *defs) {
                    createUpdateOptionDef6(server_selector, def, client_class->getName());
                }
            }
        }

        // (Re)create options.
        auto option_spaces = client_class->getCfgOption()->getOptionSpaceNames();
        for (auto const& option_space : option_spaces) {
            OptionContainerPtr options = client_class->getCfgOption()->getAll(option_space);
            for (auto const& desc : *options) {
                OptionDescriptorPtr desc_copy = OptionDescriptor::create(desc);
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
            MySqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6_ANY :
            MySqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6;

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

        MySqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this, MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           ServerSelector::ALL(), "deleting a server", false);

        // Specify which server should be deleted.
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(server_tag.get())
        };

        // Attempt to delete the server.
        auto count = conn_.updateDeleteQuery(MySqlConfigBackendDHCPv6Impl::DELETE_SERVER6,
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
        MySqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this, MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                           ServerSelector::ALL(), "deleting all servers",
                           false);

        MySqlBindingCollection in_bindings;

        // Attempt to delete the servers.
        auto count = conn_.updateDeleteQuery(MySqlConfigBackendDHCPv6Impl::DELETE_ALL_SERVERS6,
                                             in_bindings);

        // If we have deleted any servers we have to remove any dangling global
        // parameters, options and option definitions.
        if (count > 0) {
            purgeUnassignedConfig();
        }

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
        bool do_exit = false;

        const std::string timer_name = db_reconnect_ctl->timerName();
        bool check = db_reconnect_ctl->checkRetries();

        // At least one connection was lost.
        try {
            auto srv_cfg = CfgMgr::instance().getCurrentCfg();
            auto config_ctl = srv_cfg->getConfigControlInfo();

            // Something is definitely wrong. Did the configuration change
            // somehow and there is no configuration for CB?
            if (!config_ctl) {
                do_exit = true;
                isc_throw(Unexpected, "No CB configuration found!");
            }

            // Iterate over the configured DBs and instantiate them.
            for (auto const& db : config_ctl->getConfigDatabases()) {
                const std::string& access = db.getAccessString();
                auto parameters = db.getParameters();
                if (ConfigBackendDHCPv6Mgr::instance().delBackend(parameters["type"], access, true)) {
                    ConfigBackendDHCPv6Mgr::instance().addBackend(db.getAccessString());
                }
            }

            reopened = true;
        } catch (const std::exception& ex) {
            LOG_ERROR(mysql_cb_logger, MYSQL_CB_RECONNECT_ATTEMPT_FAILED6)
                    .arg(ex.what());
            if (do_exit) {
                return (true);
            }
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
            if (!check) {
                // We're out of retries, log it and initiate shutdown.
                LOG_ERROR(mysql_cb_logger, MYSQL_CB_RECONNECT_FAILED6)
                        .arg(db_reconnect_ctl->maxRetries());

                // Cancel the timer.
                if (TimerMgr::instance()->isTimerRegistered(timer_name)) {
                    TimerMgr::instance()->unregisterTimer(timer_name);
                }

                // Invoke application layer connection failed callback.
                DatabaseConnection::invokeDbFailedCallback(db_reconnect_ctl);

                return (false);
            }

            LOG_INFO(mysql_cb_logger, MYSQL_CB_RECONNECT_ATTEMPT_SCHEDULE6)
                    .arg(db_reconnect_ctl->maxRetries() - db_reconnect_ctl->retriesLeft() + 1)
                    .arg(db_reconnect_ctl->maxRetries())
                    .arg(db_reconnect_ctl->retryInterval());

            // Start the timer.
            if (!TimerMgr::instance()->isTimerRegistered(timer_name)) {
                TimerMgr::instance()->registerTimer(timer_name,
                    std::bind(&MySqlConfigBackendDHCPv6Impl::dbReconnect, db_reconnect_ctl),
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
typedef std::array<TaggedStatement, MySqlConfigBackendDHCPv6Impl::NUM_STATEMENTS>
TaggedStatementArray;

/// @brief Prepared MySQL statements used by the backend to insert and
/// retrieve data from the database.
TaggedStatementArray tagged_statements = { {
    { MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
      "CALL createAuditRevisionDHCP6(?, ?, ?, ?)"
    },

    // Verify that dependency on KNOWN/UNKNOWN class has not changed.
    { MySqlConfigBackendDHCPv6Impl::CHECK_CLIENT_CLASS_KNOWN_DEPENDENCY_CHANGE,
      "CALL checkDHCPv6ClientClassKnownDependencyChange()"
    },

    // Select global parameter by name.
    { MySqlConfigBackendDHCPv6Impl::GET_GLOBAL_PARAMETER6,
      MYSQL_GET_GLOBAL_PARAMETER(dhcp6, AND g.name = ?)
    },

    // Select all global parameters.
    { MySqlConfigBackendDHCPv6Impl::GET_ALL_GLOBAL_PARAMETERS6,
      MYSQL_GET_GLOBAL_PARAMETER(dhcp6)
    },

    // Select modified global parameters.
    { MySqlConfigBackendDHCPv6Impl::GET_MODIFIED_GLOBAL_PARAMETERS6,
      MYSQL_GET_GLOBAL_PARAMETER(dhcp6, AND g.modification_ts >= ?)
    },

    // Select subnet by id.
    { MySqlConfigBackendDHCPv6Impl::GET_SUBNET6_ID_NO_TAG,
      MYSQL_GET_SUBNET6_NO_TAG(WHERE s.subnet_id = ?)
    },

    // Select subnet by id without specifying server tags.
    { MySqlConfigBackendDHCPv6Impl::GET_SUBNET6_ID_ANY,
      MYSQL_GET_SUBNET6_ANY(WHERE s.subnet_id = ?)
    },

    // Select unassigned subnet by id.
    { MySqlConfigBackendDHCPv6Impl::GET_SUBNET6_ID_UNASSIGNED,
      MYSQL_GET_SUBNET6_UNASSIGNED(AND s.subnet_id = ?)
    },

    // Select subnet by prefix.
    { MySqlConfigBackendDHCPv6Impl::GET_SUBNET6_PREFIX_NO_TAG,
      MYSQL_GET_SUBNET6_NO_TAG(WHERE s.subnet_prefix = ?)
    },

    // Select subnet by prefix without specifying server tags.
    { MySqlConfigBackendDHCPv6Impl::GET_SUBNET6_PREFIX_ANY,
      MYSQL_GET_SUBNET6_ANY(WHERE s.subnet_prefix = ?)
    },

    // Select unassigned subnet by prefix.
    { MySqlConfigBackendDHCPv6Impl::GET_SUBNET6_PREFIX_UNASSIGNED,
      MYSQL_GET_SUBNET6_UNASSIGNED(AND s.subnet_prefix = ?)
    },

    // Select all subnets.
    { MySqlConfigBackendDHCPv6Impl::GET_ALL_SUBNETS6,
      MYSQL_GET_SUBNET6_NO_TAG()
    },

    // Select all unassigned subnets.
    { MySqlConfigBackendDHCPv6Impl::GET_ALL_SUBNETS6_UNASSIGNED,
      MYSQL_GET_SUBNET6_UNASSIGNED()
    },

    // Select subnets having modification time later than X.
    { MySqlConfigBackendDHCPv6Impl::GET_MODIFIED_SUBNETS6,
      MYSQL_GET_SUBNET6_NO_TAG(WHERE s.modification_ts >= ?)
    },

    // Select modified and unassigned subnets.
    { MySqlConfigBackendDHCPv6Impl::GET_MODIFIED_SUBNETS6_UNASSIGNED,
      MYSQL_GET_SUBNET6_UNASSIGNED(AND s.modification_ts >= ?)
    },

    // Select subnets belonging to a shared network.
    { MySqlConfigBackendDHCPv6Impl::GET_SHARED_NETWORK_SUBNETS6,
      MYSQL_GET_SUBNET6_ANY(WHERE s.shared_network_name = ?)
    },

    // Select pool by address range for a server.
    { MySqlConfigBackendDHCPv6Impl::GET_POOL6_RANGE,
      MYSQL_GET_POOL6_RANGE_WITH_TAG(WHERE (srv.tag = ? OR srv.id = 1) AND p.start_address = ? \
                                     AND p.end_address = ?)
    },

    // Select pool by address range for any server.
    { MySqlConfigBackendDHCPv6Impl::GET_POOL6_RANGE_ANY,
      MYSQL_GET_POOL6_RANGE_NO_TAG(WHERE p.start_address = ? AND p.end_address = ?)
    },

    // Select prefix delegation pool for a server.
    { MySqlConfigBackendDHCPv6Impl::GET_PD_POOL,
      MYSQL_GET_PD_POOL_WITH_TAG(WHERE (srv.tag = ? OR srv.id = 1) \
                                 AND p.prefix = ? AND p.prefix_length = ?)
    },

    // Select prefix delegation pool for any server.
    { MySqlConfigBackendDHCPv6Impl::GET_PD_POOL_ANY,
      MYSQL_GET_PD_POOL_NO_TAG(WHERE p.prefix = ? AND p.prefix_length = ?)
    },

    // Select shared network by name.
    { MySqlConfigBackendDHCPv6Impl::GET_SHARED_NETWORK6_NAME_NO_TAG,
      MYSQL_GET_SHARED_NETWORK6_NO_TAG(WHERE n.name = ?)
    },

    // Select shared network by name without specifying server tags.
    { MySqlConfigBackendDHCPv6Impl::GET_SHARED_NETWORK6_NAME_ANY,
      MYSQL_GET_SHARED_NETWORK6_ANY(WHERE n.name = ?)
    },

    // Select unassigned shared network by name.
    { MySqlConfigBackendDHCPv6Impl::GET_SHARED_NETWORK6_NAME_UNASSIGNED,
      MYSQL_GET_SHARED_NETWORK6_UNASSIGNED(AND n.name = ?)
    },

    // Select all shared networks.
    { MySqlConfigBackendDHCPv6Impl::GET_ALL_SHARED_NETWORKS6,
      MYSQL_GET_SHARED_NETWORK6_NO_TAG()
    },

    // Select all unassigned shared networks.
    { MySqlConfigBackendDHCPv6Impl::GET_ALL_SHARED_NETWORKS6_UNASSIGNED,
      MYSQL_GET_SHARED_NETWORK6_UNASSIGNED()
    },

    // Select modified shared networks.
    { MySqlConfigBackendDHCPv6Impl::GET_MODIFIED_SHARED_NETWORKS6,
      MYSQL_GET_SHARED_NETWORK6_NO_TAG(WHERE n.modification_ts >= ?)
    },

    // Select modified and unassigned shared networks.
    { MySqlConfigBackendDHCPv6Impl::GET_MODIFIED_SHARED_NETWORKS6_UNASSIGNED,
      MYSQL_GET_SHARED_NETWORK6_UNASSIGNED(AND n.modification_ts >= ?)
    },

    // Retrieves option definition by code and space.
    { MySqlConfigBackendDHCPv6Impl::GET_OPTION_DEF6_CODE_SPACE,
      MYSQL_GET_OPTION_DEF(dhcp6, AND d.code = ? AND d.space = ?)
    },

    // Retrieves all option definitions.
    { MySqlConfigBackendDHCPv6Impl::GET_ALL_OPTION_DEFS6,
      MYSQL_GET_OPTION_DEF(dhcp6)
    },

    // Retrieves modified option definitions.
    { MySqlConfigBackendDHCPv6Impl::GET_MODIFIED_OPTION_DEFS6,
      MYSQL_GET_OPTION_DEF(dhcp6, AND d.modification_ts >= ?)
    },

    // Retrieves global option by code and space.
    { MySqlConfigBackendDHCPv6Impl::GET_OPTION6_CODE_SPACE,
      MYSQL_GET_OPTION6(AND o.scope_id = 0 AND o.code = ? AND o.space = ?)
    },

    // Retrieves all global options.
    { MySqlConfigBackendDHCPv6Impl::GET_ALL_OPTIONS6,
      MYSQL_GET_OPTION6(AND o.scope_id = 0)
    },

    // Retrieves modified options.
    { MySqlConfigBackendDHCPv6Impl::GET_MODIFIED_OPTIONS6,
      MYSQL_GET_OPTION6(AND o.scope_id = 0 AND o.modification_ts >= ?)
    },

    // Retrieves an option for a given subnet, option code and space.
    { MySqlConfigBackendDHCPv6Impl::GET_OPTION6_SUBNET_ID_CODE_SPACE,
      MYSQL_GET_OPTION6(AND o.scope_id = 1 AND o.dhcp6_subnet_id = ? AND o.code = ? AND o.space = ?)
    },

    // Retrieves an option for a given pool, option code and space.
    { MySqlConfigBackendDHCPv6Impl::GET_OPTION6_POOL_ID_CODE_SPACE,
      MYSQL_GET_OPTION6(AND o.scope_id = 5 AND o.pool_id = ? AND o.code = ? AND o.space = ?)
    },

    // Retrieves an option for a given pd pool, option code and space.
    { MySqlConfigBackendDHCPv6Impl::GET_OPTION6_PD_POOL_ID_CODE_SPACE,
      MYSQL_GET_OPTION6(AND o.scope_id = 6 AND o.pd_pool_id = ? AND o.code = ? AND o.space = ?)
    },

    // Retrieves an option for a given shared network, option code and space.
    { MySqlConfigBackendDHCPv6Impl::GET_OPTION6_SHARED_NETWORK_CODE_SPACE,
      MYSQL_GET_OPTION6(AND o.scope_id = 4 AND o.shared_network_name = ? AND o.code = ? AND o.space = ?)
    },

    // Select a client class by name.
    { MySqlConfigBackendDHCPv6Impl::GET_CLIENT_CLASS6_NAME,
      MYSQL_GET_CLIENT_CLASS6_WITH_TAG(WHERE c.name = ?)
    },

    // Select all client classes.
    { MySqlConfigBackendDHCPv6Impl::GET_ALL_CLIENT_CLASSES6,
      MYSQL_GET_CLIENT_CLASS6_WITH_TAG()
    },

    // Select all unassigned client classes.
    { MySqlConfigBackendDHCPv6Impl::GET_ALL_CLIENT_CLASSES6_UNASSIGNED,
      MYSQL_GET_CLIENT_CLASS6_UNASSIGNED()
    },

    // Select modified client classes.
    { MySqlConfigBackendDHCPv6Impl::GET_MODIFIED_CLIENT_CLASSES6,
      MYSQL_GET_CLIENT_CLASS6_WITH_TAG(WHERE c.modification_ts >= ?)
    },

    // Select modified client classes.
    { MySqlConfigBackendDHCPv6Impl::GET_MODIFIED_CLIENT_CLASSES6_UNASSIGNED,
      MYSQL_GET_CLIENT_CLASS6_UNASSIGNED(AND c.modification_ts >= ?)
    },

    // Retrieves the most recent audit entries.
    { MySqlConfigBackendDHCPv6Impl::GET_AUDIT_ENTRIES6_TIME,
      MYSQL_GET_AUDIT_ENTRIES_TIME(dhcp6)
    },

    // Retrieves a server by tag.
    { MySqlConfigBackendDHCPv6Impl::GET_SERVER6,
      MYSQL_GET_SERVER(dhcp6)
    },

    // Retrieves all servers.
    { MySqlConfigBackendDHCPv6Impl::GET_ALL_SERVERS6,
      MYSQL_GET_ALL_SERVERS(dhcp6)
    },

    // Insert global parameter.
    { MySqlConfigBackendDHCPv6Impl::INSERT_GLOBAL_PARAMETER6,
      MYSQL_INSERT_GLOBAL_PARAMETER(dhcp6)
    },

    // Insert association of the global parameter with a server.
    { MySqlConfigBackendDHCPv6Impl::INSERT_GLOBAL_PARAMETER6_SERVER,
      MYSQL_INSERT_GLOBAL_PARAMETER_SERVER(dhcp6)
    },

    // Insert a subnet.
    { MySqlConfigBackendDHCPv6Impl::INSERT_SUBNET6,
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
      "  cache_max_age,"
      "  allocator,"
      "  pd_allocator"
      ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
      " ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)" },

    // Insert association of the subnet with a server.
    { MySqlConfigBackendDHCPv6Impl::INSERT_SUBNET6_SERVER,
      MYSQL_INSERT_SUBNET_SERVER(dhcp6)
    },

    // Insert pool for a subnet.
    { MySqlConfigBackendDHCPv6Impl::INSERT_POOL6,
      MYSQL_INSERT_POOL(dhcp6)
    },

    // Insert pd pool for a subnet.
    { MySqlConfigBackendDHCPv6Impl::INSERT_PD_POOL,
      MYSQL_INSERT_PD_POOL()
    },

    // Insert a shared network.
    { MySqlConfigBackendDHCPv6Impl::INSERT_SHARED_NETWORK6,
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
      "  cache_max_age,"
      "  allocator,"
      "  pd_allocator"
      ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
      " ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)" },

    // Insert association of the shared network with a server.
    { MySqlConfigBackendDHCPv6Impl::INSERT_SHARED_NETWORK6_SERVER,
      MYSQL_INSERT_SHARED_NETWORK_SERVER(dhcp6)
    },

    // Insert option definition.
    { MySqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6,
      MYSQL_INSERT_OPTION_DEF(dhcp6)
    },

    // Insert option definition for client class.
    { MySqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6_CLIENT_CLASS,
      MYSQL_INSERT_OPTION_DEF_CLIENT_CLASS(dhcp6)
    },

    // Insert association of the option definition with a server.
    { MySqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6_SERVER,
      MYSQL_INSERT_OPTION_DEF_SERVER(dhcp6)
    },

    // Insert subnet specific option.
    { MySqlConfigBackendDHCPv6Impl::INSERT_OPTION6,
      MYSQL_INSERT_OPTION6()
    },

    // Insert association of the DHCP option with a server.
    { MySqlConfigBackendDHCPv6Impl::INSERT_OPTION6_SERVER,
      MYSQL_INSERT_OPTION_SERVER(dhcp6)
    },

    // Insert client class.
    { MySqlConfigBackendDHCPv6Impl::INSERT_CLIENT_CLASS6,
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
      "  modification_ts, "
      "  user_context "
      ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
    },

    // Insert association of a client class with a server.
    { MySqlConfigBackendDHCPv6Impl::INSERT_CLIENT_CLASS6_SERVER,
      MYSQL_INSERT_CLIENT_CLASS_SERVER(dhcp6)
    },

    // Insert client class dependency.
    { MySqlConfigBackendDHCPv6Impl::INSERT_CLIENT_CLASS6_DEPENDENCY,
      MYSQL_INSERT_CLIENT_CLASS_DEPENDENCY(dhcp6)
    },

    // Insert server with server tag and description.
    { MySqlConfigBackendDHCPv6Impl::INSERT_SERVER6,
      MYSQL_INSERT_SERVER(dhcp6)
    },

    // Update existing global parameter.
    { MySqlConfigBackendDHCPv6Impl::UPDATE_GLOBAL_PARAMETER6,
      MYSQL_UPDATE_GLOBAL_PARAMETER(dhcp6)
    },

    // Update existing subnet.
    { MySqlConfigBackendDHCPv6Impl::UPDATE_SUBNET6,
      "UPDATE dhcp6_subnet SET"
      "  subnet_id = ?,"
      "  subnet_prefix = ?,"
      "  client_class = ?,"
      "  interface = ?,"
      "  modification_ts = ?,"
      "  preferred_lifetime = ?,"
      "  min_preferred_lifetime = ?,"
      "  max_preferred_lifetime = ?,"
      "  rapid_commit = ?,"
      "  rebind_timer = ?,"
      "  relay = ?,"
      "  renew_timer = ?,"
      "  require_client_classes = ?,"
      "  reservations_global = ?,"
      "  shared_network_name = ?,"
      "  user_context = ?,"
      "  valid_lifetime = ?,"
      "  min_valid_lifetime = ?,"
      "  max_valid_lifetime = ?,"
      "  calculate_tee_times = ?,"
      "  t1_percent = ?,"
      "  t2_percent = ?,"
      "  interface_id = ?,"
      "  ddns_send_updates = ?,"
      "  ddns_override_no_update = ?,"
      "  ddns_override_client_update = ?,"
      "  ddns_replace_client_name = ?,"
      "  ddns_generated_prefix = ?,"
      "  ddns_qualifying_suffix = ?,"
      "  reservations_in_subnet = ?,"
      "  reservations_out_of_pool = ?,"
      "  cache_threshold = ?,"
      "  cache_max_age = ?,"
      "  allocator = ?,"
      "  pd_allocator = ? "
      "WHERE subnet_id = ? OR subnet_prefix = ?" },

    // Update existing shared network.
    { MySqlConfigBackendDHCPv6Impl::UPDATE_SHARED_NETWORK6,
      "UPDATE dhcp6_shared_network SET"
      "  name = ?,"
      "  client_class = ?,"
      "  interface = ?,"
      "  modification_ts = ?,"
      "  preferred_lifetime = ?,"
      "  min_preferred_lifetime = ?,"
      "  max_preferred_lifetime = ?,"
      "  rapid_commit = ?,"
      "  rebind_timer = ?,"
      "  relay = ?,"
      "  renew_timer = ?,"
      "  require_client_classes = ?,"
      "  reservations_global = ?,"
      "  user_context = ?,"
      "  valid_lifetime = ?,"
      "  min_valid_lifetime = ?,"
      "  max_valid_lifetime = ?,"
      "  calculate_tee_times = ?,"
      "  t1_percent = ?,"
      "  t2_percent = ?,"
      "  interface_id = ?,"
      "  ddns_send_updates = ?,"
      "  ddns_override_no_update = ?,"
      "  ddns_override_client_update = ?,"
      "  ddns_replace_client_name = ?,"
      "  ddns_generated_prefix = ?,"
      "  ddns_qualifying_suffix = ?,"
      "  reservations_in_subnet = ?,"
      "  reservations_out_of_pool = ?,"
      "  cache_threshold = ?,"
      "  cache_max_age = ?,"
      "  allocator = ?,"
      "  pd_allocator = ? "
      "WHERE name = ?" },

    // Update existing option definition.
    { MySqlConfigBackendDHCPv6Impl::UPDATE_OPTION_DEF6,
      MYSQL_UPDATE_OPTION_DEF(dhcp6)
    },

    // Update existing client class option definition.
    { MySqlConfigBackendDHCPv6Impl::UPDATE_OPTION_DEF6_CLIENT_CLASS,
      MYSQL_UPDATE_OPTION_DEF_CLIENT_CLASS(dhcp6)
    },

    // Update existing global option.
    { MySqlConfigBackendDHCPv6Impl::UPDATE_OPTION6,
      MYSQL_UPDATE_OPTION6_WITH_TAG(AND o.scope_id = 0 AND o.code = ? AND o.space = ?)
    },

    // Update existing subnet level option.
    { MySqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_SUBNET_ID,
      MYSQL_UPDATE_OPTION6_NO_TAG(o.scope_id = 1 AND o.dhcp6_subnet_id = ? AND o.code = ? AND o.space = ?)
    },

    // Update existing pool level option.
    { MySqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_POOL_ID,
      MYSQL_UPDATE_OPTION6_NO_TAG(o.scope_id = 5 AND o.pool_id = ? AND o.code = ? AND o.space = ?)
    },

    // Update existing pd pool level option.
    { MySqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_PD_POOL_ID,
      MYSQL_UPDATE_OPTION6_NO_TAG(o.scope_id = 6 AND o.pd_pool_id = ? AND o.code = ? AND o.space = ?)
    },

    // Update existing shared network level option.
    { MySqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_SHARED_NETWORK,
      MYSQL_UPDATE_OPTION6_NO_TAG(o.scope_id = 4 AND o.shared_network_name = ? AND o.code = ? AND o.space = ?)
    },

    // Update existing client class level option.
    { MySqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_CLIENT_CLASS,
      MYSQL_UPDATE_OPTION6_NO_TAG(o.scope_id = 2 AND o.dhcp_client_class = ? AND o.code = ? AND o.space = ?)
    },

    // Update existing client class with specifying its position.
    { MySqlConfigBackendDHCPv6Impl::UPDATE_CLIENT_CLASS6,
      MYSQL_UPDATE_CLIENT_CLASS6("follow_class_name = ?,")
    },

    // Update existing client class without specifying its position.
    { MySqlConfigBackendDHCPv6Impl::UPDATE_CLIENT_CLASS6_SAME_POSITION,
      MYSQL_UPDATE_CLIENT_CLASS6("")
    },

    // Update existing server, e.g. server description.
    { MySqlConfigBackendDHCPv6Impl::UPDATE_SERVER6,
      MYSQL_UPDATE_SERVER(dhcp6)
    },

    // Delete global parameter by name.
    { MySqlConfigBackendDHCPv6Impl::DELETE_GLOBAL_PARAMETER6,
      MYSQL_DELETE_GLOBAL_PARAMETER(dhcp6, AND g.name = ?)
    },

    // Delete all global parameters.
    { MySqlConfigBackendDHCPv6Impl::DELETE_ALL_GLOBAL_PARAMETERS6,
      MYSQL_DELETE_GLOBAL_PARAMETER(dhcp6)
    },

    // Delete all global parameters which are unassigned to any servers.
    { MySqlConfigBackendDHCPv6Impl::DELETE_ALL_GLOBAL_PARAMETERS6_UNASSIGNED,
      MYSQL_DELETE_GLOBAL_PARAMETER_UNASSIGNED(dhcp6)
    },

    // Delete subnet by id with specifying server tag.
    { MySqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_ID_WITH_TAG,
      MYSQL_DELETE_SUBNET_WITH_TAG(dhcp6, AND s.subnet_id = ?)
    },

    // Delete subnet by id without specifying server tag.
    { MySqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_ID_ANY,
      MYSQL_DELETE_SUBNET_ANY(dhcp6, WHERE s.subnet_id = ?)
    },

    // Delete subnet by prefix with specifying server tag.
    { MySqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_PREFIX_WITH_TAG,
      MYSQL_DELETE_SUBNET_WITH_TAG(dhcp6, AND s.subnet_prefix = ?)
    },

    // Delete subnet by prefix without specifying server tag.
    { MySqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_PREFIX_ANY,
      MYSQL_DELETE_SUBNET_ANY(dhcp6, WHERE s.subnet_prefix = ?)
    },

    // Delete all subnets.
    { MySqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6,
      MYSQL_DELETE_SUBNET_WITH_TAG(dhcp6)
    },

    // Delete all unassigned subnets.
    { MySqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6_UNASSIGNED,
      MYSQL_DELETE_SUBNET_UNASSIGNED(dhcp6)
    },

    // Delete all subnets for a shared network.
    { MySqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6_SHARED_NETWORK_NAME,
      MYSQL_DELETE_SUBNET_ANY(dhcp6, WHERE s.shared_network_name = ?)
    },

    // Delete associations of a subnet with server.
    { MySqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_SERVER,
      MYSQL_DELETE_SUBNET_SERVER(dhcp6),
    },

    // Delete pools for a subnet.
    { MySqlConfigBackendDHCPv6Impl::DELETE_POOLS6,
      MYSQL_DELETE_POOLS(dhcp6)
    },

    // Delete pd pools for a subnet.
    { MySqlConfigBackendDHCPv6Impl::DELETE_PD_POOLS,
      MYSQL_DELETE_PD_POOLS()
    },

    // Delete shared network by name with specifying server tag.
    { MySqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_NAME_WITH_TAG,
      MYSQL_DELETE_SHARED_NETWORK_WITH_TAG(dhcp6, AND n.name = ?)
    },

    // Delete shared network by name without specifying server tag.
    { MySqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_NAME_ANY,
      MYSQL_DELETE_SHARED_NETWORK_ANY(dhcp6, WHERE n.name = ?)
    },

    // Delete all shared networks.
    { MySqlConfigBackendDHCPv6Impl::DELETE_ALL_SHARED_NETWORKS6,
      MYSQL_DELETE_SHARED_NETWORK_WITH_TAG(dhcp6)
    },

    // Delete all unassigned shared networks.
    { MySqlConfigBackendDHCPv6Impl::DELETE_ALL_SHARED_NETWORKS6_UNASSIGNED,
      MYSQL_DELETE_SHARED_NETWORK_UNASSIGNED(dhcp6)
    },

    // Delete associations of a shared network with server.
    { MySqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_SERVER,
      MYSQL_DELETE_SHARED_NETWORK_SERVER(dhcp6)
    },

    // Delete option definition.
    { MySqlConfigBackendDHCPv6Impl::DELETE_OPTION_DEF6_CODE_NAME,
      MYSQL_DELETE_OPTION_DEF(dhcp6, AND code = ? AND space = ?)
    },

    // Delete all option definitions.
    { MySqlConfigBackendDHCPv6Impl::DELETE_ALL_OPTION_DEFS6,
      MYSQL_DELETE_OPTION_DEF(dhcp6)
    },

    // Delete all option definitions which are assigned to no servers.
    { MySqlConfigBackendDHCPv6Impl::DELETE_ALL_OPTION_DEFS6_UNASSIGNED,
      MYSQL_DELETE_OPTION_DEF_UNASSIGNED(dhcp6)
    },

    // Delete client class specific option definitions.
    { MySqlConfigBackendDHCPv6Impl::DELETE_OPTION_DEFS6_CLIENT_CLASS,
      MYSQL_DELETE_OPTION_DEFS_CLIENT_CLASS(dhcp6)
    },

    // Delete single global option.
    { MySqlConfigBackendDHCPv6Impl::DELETE_OPTION6,
      MYSQL_DELETE_OPTION_WITH_TAG(dhcp6, AND o.scope_id = 0 AND o.code = ? AND o.space = ?)
    },

    // Delete all global options which are unassigned to any servers.
    { MySqlConfigBackendDHCPv6Impl::DELETE_ALL_GLOBAL_OPTIONS6_UNASSIGNED,
      MYSQL_DELETE_OPTION_UNASSIGNED(dhcp6, AND o.scope_id = 0)
    },

    // Delete single option from a subnet.
    { MySqlConfigBackendDHCPv6Impl::DELETE_OPTION6_SUBNET_ID,
      MYSQL_DELETE_OPTION_NO_TAG(dhcp6,
                          WHERE o.scope_id = 1 AND o.dhcp6_subnet_id = ? AND o.code = ? AND o.space = ?)
    },

    // Delete single option from a pool.
    { MySqlConfigBackendDHCPv6Impl::DELETE_OPTION6_POOL_RANGE,
      MYSQL_DELETE_OPTION_POOL_RANGE(dhcp6, o.scope_id = 5 AND o.code = ? AND o.space = ?)
    },

    // Delete single option from a pd pool.
    { MySqlConfigBackendDHCPv6Impl::DELETE_OPTION6_PD_POOL,
      MYSQL_DELETE_OPTION_PD_POOL(o.scope_id = 6 AND o.code = ? AND o.space = ?)
    },

    // Delete single option from a shared network.
    { MySqlConfigBackendDHCPv6Impl::DELETE_OPTION6_SHARED_NETWORK,
      MYSQL_DELETE_OPTION_NO_TAG(dhcp6,
                          WHERE o.scope_id = 4 AND o.shared_network_name = ? AND o.code = ? AND o.space = ?)
    },

    // Delete options belonging to a subnet.
    { MySqlConfigBackendDHCPv6Impl::DELETE_OPTIONS6_SUBNET_ID_PREFIX,
      MYSQL_DELETE_OPTION_SUBNET_ID_PREFIX(dhcp6)
    },

    // Delete options belonging to a shared_network.
    { MySqlConfigBackendDHCPv6Impl::DELETE_OPTIONS6_SHARED_NETWORK,
      MYSQL_DELETE_OPTION_NO_TAG(dhcp6, WHERE o.scope_id = 4 AND o.shared_network_name = ?)
    },

    // Delete options belonging to a client class.
    { MySqlConfigBackendDHCPv6Impl::DELETE_OPTIONS6_CLIENT_CLASS,
      MYSQL_DELETE_OPTION_NO_TAG(dhcp6, WHERE o.scope_id = 2 AND o.dhcp_client_class = ?)
    },

    // Delete all dependencies of a client class.
    { MySqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6_DEPENDENCY,
      MYSQL_DELETE_CLIENT_CLASS_DEPENDENCY(dhcp6)
    },

    // Delete associations of a client class with server.
    { MySqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6_SERVER,
      MYSQL_DELETE_CLIENT_CLASS_SERVER(dhcp6),
    },

    // Delete all client classes.
    { MySqlConfigBackendDHCPv6Impl::DELETE_ALL_CLIENT_CLASSES6,
      MYSQL_DELETE_CLIENT_CLASS_WITH_TAG(dhcp6)
    },

    // Delete all unassigned client classes.
    { MySqlConfigBackendDHCPv6Impl::DELETE_ALL_CLIENT_CLASSES6_UNASSIGNED,
      MYSQL_DELETE_CLIENT_CLASS_UNASSIGNED(dhcp6)
    },

    // Delete specified client class.
    { MySqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6,
      MYSQL_DELETE_CLIENT_CLASS_WITH_TAG(dhcp6, AND name = ?)
    },

    // Delete any client class with a given name.
    { MySqlConfigBackendDHCPv6Impl::DELETE_CLIENT_CLASS6_ANY,
      MYSQL_DELETE_CLIENT_CLASS_ANY(dhcp6, AND name = ?)
    },

    // Delete a server by tag.
    { MySqlConfigBackendDHCPv6Impl::DELETE_SERVER6,
      MYSQL_DELETE_SERVER(dhcp6)
    },

    // Deletes all servers except logical server 'all'.
    { MySqlConfigBackendDHCPv6Impl::DELETE_ALL_SERVERS6,
      MYSQL_DELETE_ALL_SERVERS(dhcp6)
    }
}
};

} // end anonymous namespace

MySqlConfigBackendDHCPv6Impl::MySqlConfigBackendDHCPv6Impl(const DatabaseConnection::ParameterMap& parameters)
    : MySqlConfigBackendImpl(std::string(cStringDhcpSpace<DHCPv6>()), parameters,
                             &MySqlConfigBackendDHCPv6Impl::dbReconnect) {
    // Prepare query statements. Those are will be only used to retrieve
    // information from the database, so they can be used even if the
    // database is read only for the current user.
    conn_.prepareStatements(tagged_statements.begin(),
                            tagged_statements.end());
// @todo As part of enabling read-only CB access, statements need to
// be limited:
//                            tagged_statements.begin() + WRITE_STMTS_BEGIN);
}

MySqlConfigBackendDHCPv6Impl::~MySqlConfigBackendDHCPv6Impl() {
}

MySqlConfigBackendDHCPv6::MySqlConfigBackendDHCPv6(const DatabaseConnection::ParameterMap& parameters)
    : impl_(new MySqlConfigBackendDHCPv6Impl(parameters)), base_impl_(impl_) {
}

bool
MySqlConfigBackendDHCPv6::isUnusable() {
    return (impl_->conn_.isUnusable());
}

DatabaseConnection::ParameterMap
MySqlConfigBackendDHCPv6::getParameters() const {
    return (impl_->getParameters());
}

Subnet6Ptr
MySqlConfigBackendDHCPv6::getSubnet6(const ServerSelector& server_selector,
                                     const std::string& subnet_prefix) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_SUBNET6_BY_PREFIX)
        .arg(subnet_prefix);
    return (impl_->getSubnet6(server_selector, subnet_prefix));
}

Subnet6Ptr
MySqlConfigBackendDHCPv6::getSubnet6(const ServerSelector& server_selector,
                                     const SubnetID& subnet_id) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_SUBNET6_BY_SUBNET_ID)
        .arg(subnet_id);
    return (impl_->getSubnet6(server_selector, subnet_id));
}

Subnet6Collection
MySqlConfigBackendDHCPv6::getAllSubnets6(const ServerSelector& server_selector) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_ALL_SUBNETS6);
    Subnet6Collection subnets;
    impl_->getAllSubnets6(server_selector, subnets);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_ALL_SUBNETS6_RESULT)
        .arg(subnets.size());
    return (subnets);
}

Subnet6Collection
MySqlConfigBackendDHCPv6::getModifiedSubnets6(const ServerSelector& server_selector,
                                              const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_MODIFIED_SUBNETS6)
        .arg(util::ptimeToText(modification_time));
    Subnet6Collection subnets;
    impl_->getModifiedSubnets6(server_selector, modification_time, subnets);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_MODIFIED_SUBNETS6_RESULT)
        .arg(subnets.size());
    return (subnets);
}

Subnet6Collection
MySqlConfigBackendDHCPv6::getSharedNetworkSubnets6(const ServerSelector& /* server_selector */,
                                                   const std::string& shared_network_name) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_SHARED_NETWORK_SUBNETS6)
        .arg(shared_network_name);
    Subnet6Collection subnets;
    impl_->getSharedNetworkSubnets6(ServerSelector::ANY(), shared_network_name, subnets);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_SHARED_NETWORK_SUBNETS6_RESULT)
        .arg(subnets.size());
    return (subnets);
}

SharedNetwork6Ptr
MySqlConfigBackendDHCPv6::getSharedNetwork6(const ServerSelector& server_selector,
                                            const std::string& name) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_SHARED_NETWORK6)
        .arg(name);
    return (impl_->getSharedNetwork6(server_selector, name));
}

SharedNetwork6Collection
MySqlConfigBackendDHCPv6::getAllSharedNetworks6(const ServerSelector& server_selector) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_ALL_SHARED_NETWORKS6);
    SharedNetwork6Collection shared_networks;
    impl_->getAllSharedNetworks6(server_selector, shared_networks);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_ALL_SHARED_NETWORKS6_RESULT)
        .arg(shared_networks.size());
    return (shared_networks);
}

SharedNetwork6Collection
MySqlConfigBackendDHCPv6::getModifiedSharedNetworks6(const ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_MODIFIED_SHARED_NETWORKS6)
        .arg(util::ptimeToText(modification_time));
    SharedNetwork6Collection shared_networks;
    impl_->getModifiedSharedNetworks6(server_selector, modification_time, shared_networks);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_MODIFIED_SHARED_NETWORKS6_RESULT)
        .arg(shared_networks.size());
    return (shared_networks);
}

OptionDefinitionPtr
MySqlConfigBackendDHCPv6::getOptionDef6(const ServerSelector& server_selector,
                                        const uint16_t code,
                                        const std::string& space) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_OPTION_DEF6)
        .arg(code).arg(space);
    return (impl_->getOptionDef(MySqlConfigBackendDHCPv6Impl::GET_OPTION_DEF6_CODE_SPACE,
                                server_selector, code, space));
}

OptionDefContainer
MySqlConfigBackendDHCPv6::getAllOptionDefs6(const ServerSelector& server_selector) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_ALL_OPTION_DEFS6);
    OptionDefContainer option_defs;
    impl_->getAllOptionDefs(MySqlConfigBackendDHCPv6Impl::GET_ALL_OPTION_DEFS6,
                            server_selector, option_defs);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_ALL_OPTION_DEFS6_RESULT)
        .arg(option_defs.size());
    return (option_defs);
}

OptionDefContainer
MySqlConfigBackendDHCPv6::getModifiedOptionDefs6(const ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_MODIFIED_OPTION_DEFS6)
        .arg(util::ptimeToText(modification_time));
    OptionDefContainer option_defs;
    impl_->getModifiedOptionDefs(MySqlConfigBackendDHCPv6Impl::GET_MODIFIED_OPTION_DEFS6,
                                 server_selector, modification_time, option_defs);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_MODIFIED_OPTION_DEFS6_RESULT)
        .arg(option_defs.size());
    return (option_defs);
}

OptionDescriptorPtr
MySqlConfigBackendDHCPv6::getOption6(const ServerSelector& server_selector,
                                     const uint16_t code,
                                     const std::string& space) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_OPTION6)
        .arg(code).arg(space);
    return (impl_->getOption(MySqlConfigBackendDHCPv6Impl::GET_OPTION6_CODE_SPACE,
                             Option::V6, server_selector, code, space));
}

OptionContainer
MySqlConfigBackendDHCPv6::getAllOptions6(const ServerSelector& server_selector) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_ALL_OPTIONS6);
    OptionContainer options = impl_->getAllOptions(MySqlConfigBackendDHCPv6Impl::GET_ALL_OPTIONS6,
            Option::V6, server_selector);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_ALL_OPTIONS6_RESULT)
        .arg(options.size());
    return (options);
}

OptionContainer
MySqlConfigBackendDHCPv6::getModifiedOptions6(const ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_MODIFIED_OPTIONS6)
        .arg(util::ptimeToText(modification_time));
    OptionContainer options = impl_->getModifiedOptions(MySqlConfigBackendDHCPv6Impl::GET_MODIFIED_OPTIONS6,
            Option::V6, server_selector, modification_time);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_MODIFIED_OPTIONS6_RESULT)
        .arg(options.size());
    return (options);
}

StampedValuePtr
MySqlConfigBackendDHCPv6::getGlobalParameter6(const ServerSelector& server_selector,
                                              const std::string& name) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_GLOBAL_PARAMETER6)
        .arg(name);
    return (impl_->getGlobalParameter6(server_selector, name));
}

StampedValueCollection
MySqlConfigBackendDHCPv6::getAllGlobalParameters6(const ServerSelector& server_selector) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_ALL_GLOBAL_PARAMETERS6);
    StampedValueCollection parameters;
    auto const& tags = server_selector.getTags();
    for (auto const& tag : tags) {
        MySqlBindingCollection in_bindings = { MySqlBinding::createString(tag.get()) };
        impl_->getGlobalParameters(MySqlConfigBackendDHCPv6Impl::GET_ALL_GLOBAL_PARAMETERS6,
                                   in_bindings, parameters);
    }
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_ALL_GLOBAL_PARAMETERS6_RESULT)
        .arg(parameters.size());
    return (parameters);
}

StampedValueCollection
MySqlConfigBackendDHCPv6::getModifiedGlobalParameters6(const db::ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6)
        .arg(util::ptimeToText(modification_time));
    StampedValueCollection parameters;
    auto const& tags = server_selector.getTags();
    for (auto const& tag : tags) {
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(tag.get()),
            MySqlBinding::createTimestamp(modification_time)
        };
        impl_->getGlobalParameters(MySqlConfigBackendDHCPv6Impl::GET_MODIFIED_GLOBAL_PARAMETERS6,
                                   in_bindings, parameters);
    }
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_MODIFIED_GLOBAL_PARAMETERS6_RESULT)
        .arg(parameters.size());
    return (parameters);
}

ClientClassDefPtr
MySqlConfigBackendDHCPv6::getClientClass6(const db::ServerSelector& server_selector,
                                          const std::string& name) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_CLIENT_CLASS6)
        .arg(name);
    return (impl_->getClientClass6(server_selector, name));
}

ClientClassDictionary
MySqlConfigBackendDHCPv6::getAllClientClasses6(const db::ServerSelector& server_selector) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_ALL_CLIENT_CLASSES6);
    ClientClassDictionary client_classes;
    impl_->getAllClientClasses6(server_selector, client_classes);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_ALL_CLIENT_CLASSES6_RESULT)
        .arg(client_classes.getClasses()->size());
    return (client_classes);
}

ClientClassDictionary
MySqlConfigBackendDHCPv6::getModifiedClientClasses6(const db::ServerSelector& server_selector,
                                                    const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_MODIFIED_CLIENT_CLASSES6)
        .arg(util::ptimeToText(modification_time));
    ClientClassDictionary client_classes;
    impl_->getModifiedClientClasses6(server_selector, modification_time, client_classes);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_MODIFIED_CLIENT_CLASSES6_RESULT)
        .arg(client_classes.getClasses()->size());
    return (client_classes);
}

AuditEntryCollection
MySqlConfigBackendDHCPv6::getRecentAuditEntries(const db::ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time,
        const uint64_t& modification_id) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_RECENT_AUDIT_ENTRIES6)
      .arg(util::ptimeToText(modification_time))
      .arg(modification_id);
    AuditEntryCollection audit_entries;
    impl_->getRecentAuditEntries(MySqlConfigBackendDHCPv6Impl::GET_AUDIT_ENTRIES6_TIME,
                                 server_selector, modification_time,
                                 modification_id, audit_entries);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_RECENT_AUDIT_ENTRIES6_RESULT)
        .arg(audit_entries.size());
    return (audit_entries);
}

ServerCollection
MySqlConfigBackendDHCPv6::getAllServers6() const {
    ServerCollection servers;

    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_ALL_SERVERS6);
    impl_->getAllServers(MySqlConfigBackendDHCPv6Impl::GET_ALL_SERVERS6,
                         servers);

    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_ALL_SERVERS6_RESULT)
        .arg(servers.size());
    return (servers);
}

ServerPtr
MySqlConfigBackendDHCPv6::getServer6(const data::ServerTag& server_tag) const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_SERVER6)
        .arg(server_tag.get());
    return (impl_->getServer(MySqlConfigBackendDHCPv6Impl::GET_SERVER6, server_tag));
}

void
MySqlConfigBackendDHCPv6::createUpdateSubnet6(const ServerSelector& server_selector,
                                              const Subnet6Ptr& subnet) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_CREATE_UPDATE_SUBNET6)
        .arg(subnet);
    impl_->createUpdateSubnet6(server_selector, subnet);
}

void
MySqlConfigBackendDHCPv6::createUpdateSharedNetwork6(const ServerSelector& server_selector,
                                                     const SharedNetwork6Ptr& shared_network) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_CREATE_UPDATE_SHARED_NETWORK6)
        .arg(shared_network->getName());
    impl_->createUpdateSharedNetwork6(server_selector, shared_network);
}

void
MySqlConfigBackendDHCPv6::createUpdateOptionDef6(const ServerSelector& server_selector,
                                                 const OptionDefinitionPtr& option_def) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_CREATE_UPDATE_OPTION_DEF6)
        .arg(option_def->getName()).arg(option_def->getCode());
    impl_->createUpdateOptionDef6(server_selector, option_def);
}

void
MySqlConfigBackendDHCPv6::createUpdateOption6(const ServerSelector& server_selector,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_CREATE_UPDATE_OPTION6);
    impl_->createUpdateOption6(server_selector, option);
}

void
MySqlConfigBackendDHCPv6::createUpdateOption6(const db::ServerSelector& server_selector,
                                              const std::string& shared_network_name,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION6)
        .arg(shared_network_name);
    impl_->createUpdateOption6(server_selector, shared_network_name, option, false);
}

void
MySqlConfigBackendDHCPv6::createUpdateOption6(const ServerSelector& server_selector,
                                              const SubnetID& subnet_id,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION6)
        .arg(subnet_id);
    impl_->createUpdateOption6(server_selector, subnet_id, option, false);
}

void
MySqlConfigBackendDHCPv6::createUpdateOption6(const ServerSelector& server_selector,
                                              const asiolink::IOAddress& pool_start_address,
                                              const asiolink::IOAddress& pool_end_address,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_CREATE_UPDATE_BY_POOL_OPTION6)
        .arg(pool_start_address.toText()).arg(pool_end_address.toText());
    impl_->createUpdateOption6(server_selector, pool_start_address, pool_end_address,
                               option);
}

void
MySqlConfigBackendDHCPv6::createUpdateOption6(const ServerSelector& server_selector,
                                              const asiolink::IOAddress& pd_pool_prefix,
                                              const uint8_t pd_pool_prefix_length,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_CREATE_UPDATE_BY_PREFIX_OPTION6)
        .arg(pd_pool_prefix.toText()).arg(pd_pool_prefix_length);
    impl_->createUpdateOption6(server_selector, pd_pool_prefix,
                               pd_pool_prefix_length, option);
}

void
MySqlConfigBackendDHCPv6::createUpdateGlobalParameter6(const ServerSelector& server_selector,
                                                       const StampedValuePtr& value) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER6)
        .arg(value->getName());
    impl_->createUpdateGlobalParameter6(server_selector, value);
}

void
MySqlConfigBackendDHCPv6::createUpdateClientClass6(const db::ServerSelector& server_selector,
                                                   const ClientClassDefPtr& client_class,
                                                   const std::string& follow_class_name) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_CREATE_UPDATE_CLIENT_CLASS6)
        .arg(client_class->getName());
    impl_->createUpdateClientClass6(server_selector, client_class, follow_class_name);
}

void
MySqlConfigBackendDHCPv6::createUpdateServer6(const ServerPtr& server) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_CREATE_UPDATE_SERVER6)
        .arg(server->getServerTagAsText());
    impl_->createUpdateServer(MySqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                              MySqlConfigBackendDHCPv6Impl::INSERT_SERVER6,
                              MySqlConfigBackendDHCPv6Impl::UPDATE_SERVER6,
                              server);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteSubnet6(const ServerSelector& server_selector,
                                        const std::string& subnet_prefix) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_BY_PREFIX_SUBNET6)
        .arg(subnet_prefix);
    uint64_t result = impl_->deleteSubnet6(server_selector, subnet_prefix);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_BY_PREFIX_SUBNET6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteSubnet6(const ServerSelector& server_selector,
                                        const SubnetID& subnet_id) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_BY_SUBNET_ID_SUBNET6)
        .arg(subnet_id);
    uint64_t result = impl_->deleteSubnet6(server_selector, subnet_id);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_BY_SUBNET_ID_SUBNET6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteAllSubnets6(const ServerSelector& server_selector) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_ALL_SUBNETS6);

    int index = (server_selector.amUnassigned() ?
                 MySqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6_UNASSIGNED :
                 MySqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6);
    uint64_t result = impl_->deleteTransactional(index, server_selector, "deleting all subnets",
                                                 "deleted all subnets", true);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_ALL_SUBNETS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteSharedNetworkSubnets6(const db::ServerSelector& server_selector,
                                                      const std::string& shared_network_name) {
    if (!server_selector.amAny()) {
        isc_throw(InvalidOperation, "deleting all subnets from a shared "
                  "network requires using ANY server selector");
    }
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_SHARED_NETWORK_SUBNETS6)
        .arg(shared_network_name);
    uint64_t result = impl_->deleteTransactional(MySqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6_SHARED_NETWORK_NAME,
                                                 server_selector,
                                                 "deleting all subnets for a shared network",
                                                 "deleted all subnets for a shared network",
                                                 true, shared_network_name);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_SHARED_NETWORK_SUBNETS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteSharedNetwork6(const ServerSelector& server_selector,
                                               const std::string& name) {
    /// @todo Using UNASSIGNED selector is allowed by the CB API but we don't have
    /// dedicated query for this at the moment. The user should use ANY to delete
    /// the shared network by name.
    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "deleting an unassigned shared network requires "
                  "an explicit server tag or using ANY server. The UNASSIGNED server "
                  "selector is currently not supported");
    }

    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_SHARED_NETWORK6)
        .arg(name);

    int index = (server_selector.amAny() ?
                 MySqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_NAME_ANY :
                 MySqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_NAME_WITH_TAG);
    uint64_t result = impl_->deleteTransactional(index, server_selector,
                                                 "deleting a shared network",
                                                 "shared network deleted", true, name);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_SHARED_NETWORK6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteAllSharedNetworks6(const ServerSelector& server_selector) {
    if (server_selector.amAny()) {
        isc_throw(InvalidOperation, "deleting all shared networks for ANY server is not"
                  " supported");
    }

    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_ALL_SHARED_NETWORKS6);

    int index = (server_selector.amUnassigned() ?
                 MySqlConfigBackendDHCPv6Impl::DELETE_ALL_SHARED_NETWORKS6_UNASSIGNED :
                 MySqlConfigBackendDHCPv6Impl::DELETE_ALL_SHARED_NETWORKS6);
    uint64_t result = impl_->deleteTransactional(index, server_selector, "deleting all shared networks",
                                                 "deleted all shared networks", true);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_ALL_SHARED_NETWORKS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteOptionDef6(const ServerSelector& server_selector,
                                           const uint16_t code,
                                           const std::string& space) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_OPTION_DEF6)
        .arg(code).arg(space);
    uint64_t result = impl_->deleteOptionDef6(server_selector, code, space);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_OPTION_DEF6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteAllOptionDefs6(const ServerSelector& server_selector) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_ALL_OPTION_DEFS6);
    uint64_t result = impl_->deleteTransactional(MySqlConfigBackendDHCPv6Impl::DELETE_ALL_OPTION_DEFS6,
                                                 server_selector, "deleting all option definitions",
                                                 "deleted all option definitions", true);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_ALL_OPTION_DEFS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteOption6(const ServerSelector& server_selector,
                                        const uint16_t code,
                                        const std::string& space) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_OPTION6)
        .arg(code).arg(space);
    uint64_t result = impl_->deleteOption6(server_selector, code, space);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_OPTION6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteOption6(const ServerSelector& /* server_selector */,
                                        const std::string& shared_network_name,
                                        const uint16_t code,
                                        const std::string& space) {
    /// @todo In the future we might use the server selector to make sure that the
    /// option is only deleted if the pool belongs to a given server. For now, we
    /// just delete it when there is a match with the parent object.
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_SHARED_NETWORK_OPTION6)
        .arg(shared_network_name).arg(code).arg(space);
    uint64_t result = impl_->deleteOption6(ServerSelector::ANY(), shared_network_name,
                                           code, space);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_SHARED_NETWORK_OPTION6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteOption6(const ServerSelector& /* server_selector */,
                                        const SubnetID& subnet_id,
                                        const uint16_t code,
                                        const std::string& space) {
    /// @todo In the future we might use the server selector to make sure that the
    /// option is only deleted if the pool belongs to a given server. For now, we
    /// just delete it when there is a match with the parent object.
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_BY_SUBNET_ID_OPTION6)
        .arg(subnet_id).arg(code).arg(space);
    uint64_t result = impl_->deleteOption6(ServerSelector::ANY(), subnet_id, code, space);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_BY_SUBNET_ID_OPTION6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteOption6(const ServerSelector& /* server_selector */,
                                        const asiolink::IOAddress& pool_start_address,
                                        const asiolink::IOAddress& pool_end_address,
                                        const uint16_t code,
                                        const std::string& space) {
    /// @todo In the future we might use the server selector to make sure that the
    /// option is only deleted if the pool belongs to a given server. For now, we
    /// just delete it when there is a match with the parent object.
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_BY_POOL_OPTION6)
        .arg(pool_start_address.toText()).arg(pool_end_address.toText()).arg(code).arg(space);
    uint64_t result = impl_->deleteOption6(ServerSelector::ANY(), pool_start_address,
                                           pool_end_address, code, space);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_BY_POOL_OPTION6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteOption6(const ServerSelector& /* server_selector */,
                                        const asiolink::IOAddress& pd_pool_prefix,
                                        const uint8_t pd_pool_prefix_length,
                                        const uint16_t code,
                                        const std::string& space) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_BY_POOL_PREFIX_OPTION6)
        .arg(pd_pool_prefix.toText()).arg(pd_pool_prefix_length).arg(code).arg(space);
    uint64_t result = impl_->deleteOption6(ServerSelector::ANY(), pd_pool_prefix,
                                           pd_pool_prefix_length, code, space);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_BY_POOL_PREFIX_OPTION6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteGlobalParameter6(const ServerSelector& server_selector,
                                                 const std::string& name) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_GLOBAL_PARAMETER6)
        .arg(name);
    uint64_t result = impl_->deleteTransactional(MySqlConfigBackendDHCPv6Impl::DELETE_GLOBAL_PARAMETER6,
                                                 server_selector, "deleting global parameter",
                                                 "global parameter deleted", false, name);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_GLOBAL_PARAMETER6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteAllGlobalParameters6(const ServerSelector& server_selector) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS6);
    uint64_t result = impl_->deleteTransactional(MySqlConfigBackendDHCPv6Impl::DELETE_ALL_GLOBAL_PARAMETERS6,
                                                 server_selector, "deleting all global parameters",
                                                 "all global parameters deleted", true);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteClientClass6(const db::ServerSelector& server_selector,
                                             const std::string& name) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_CLIENT_CLASS6)
        .arg(name);
    auto result = impl_->deleteClientClass6(server_selector, name);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_CLIENT_CLASS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteAllClientClasses6(const db::ServerSelector& server_selector) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_ALL_CLIENT_CLASSES6);

    int index = (server_selector.amUnassigned() ?
                 MySqlConfigBackendDHCPv6Impl::DELETE_ALL_CLIENT_CLASSES6_UNASSIGNED :
                 MySqlConfigBackendDHCPv6Impl::DELETE_ALL_CLIENT_CLASSES6);
    uint64_t result = impl_->deleteTransactional(index, server_selector, "deleting all client classes",
                                                 "deleted all client classes", true);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_ALL_CLIENT_CLASSES6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteServer6(const ServerTag& server_tag) {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_SERVER6)
        .arg(server_tag.get());
    uint64_t result = impl_->deleteServer6(server_tag);
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_SERVER6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
MySqlConfigBackendDHCPv6::deleteAllServers6() {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_ALL_SERVERS6);
    uint64_t result = impl_->deleteAllServers6();
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_DELETE_ALL_SERVERS6_RESULT)
        .arg(result);
    return (result);
}

std::string
MySqlConfigBackendDHCPv6::getType() const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_TYPE6);
    return (impl_->getType());
}

std::string
MySqlConfigBackendDHCPv6::getHost() const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_HOST6);
    return (impl_->getHost());
}

uint16_t
MySqlConfigBackendDHCPv6::getPort() const {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_GET_PORT6);
    return (impl_->getPort());
}

bool
MySqlConfigBackendDHCPv6::registerBackendType() {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_REGISTER_BACKEND_TYPE6);
    return (
        dhcp::ConfigBackendDHCPv6Mgr::instance().registerBackendFactory("mysql",
            [](const db::DatabaseConnection::ParameterMap& params) -> dhcp::ConfigBackendDHCPv6Ptr {
            return (dhcp::MySqlConfigBackendDHCPv6Ptr(new dhcp::MySqlConfigBackendDHCPv6(params)));
        })
    );
}

void
MySqlConfigBackendDHCPv6::unregisterBackendType() {
    LOG_DEBUG(mysql_cb_logger, DBGLVL_TRACE_BASIC, MYSQL_CB_UNREGISTER_BACKEND_TYPE6);
    dhcp::ConfigBackendDHCPv6Mgr::instance().unregisterBackendFactory("mysql");
}

} // end of namespace isc::dhcp
} // end of namespace isc
