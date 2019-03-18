// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <mysql_cb_dhcp4.h>
#include <mysql_cb_impl.h>
#include <mysql_query_macros_dhcp.h>
#include <cc/data.h>
#include <config_backend/constants.h>
#include <database/db_exceptions.h>
#include <dhcp/classify.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_data_types.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <dhcpsrv/network.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/lease.h>
#include <util/buffer.h>
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
using namespace isc::util;

namespace isc {
namespace dhcp {

/// @brief Implementation of the MySQL Configuration Backend.
class MySqlConfigBackendDHCPv4Impl : public MySqlConfigBackendImpl {
public:

    /// @brief Statement tags.
    ///
    /// The contents of the enum are indexes into the list of SQL statements.
    /// It is assumed that the order is such that the indices of statements
    /// reading the database are less than those of statements modifying the
    /// database.
    enum StatementIndex {
        CREATE_AUDIT_REVISION,
        GET_GLOBAL_PARAMETER4,
        GET_ALL_GLOBAL_PARAMETERS4,
        GET_MODIFIED_GLOBAL_PARAMETERS4,
        GET_SUBNET4_ID,
        GET_SUBNET4_PREFIX,
        GET_ALL_SUBNETS4,
        GET_MODIFIED_SUBNETS4,
        GET_SHARED_NETWORK_SUBNETS4,
        GET_POOL4_RANGE,
        GET_SHARED_NETWORK4_NAME,
        GET_ALL_SHARED_NETWORKS4,
        GET_MODIFIED_SHARED_NETWORKS4,
        GET_OPTION_DEF4_CODE_SPACE,
        GET_ALL_OPTION_DEFS4,
        GET_MODIFIED_OPTION_DEFS4,
        GET_OPTION4_CODE_SPACE,
        GET_ALL_OPTIONS4,
        GET_MODIFIED_OPTIONS4,
        GET_OPTION4_SUBNET_ID_CODE_SPACE,
        GET_OPTION4_POOL_ID_CODE_SPACE,
        GET_OPTION4_SHARED_NETWORK_CODE_SPACE,
        GET_AUDIT_ENTRIES4_TIME,
        INSERT_GLOBAL_PARAMETER4,
        INSERT_GLOBAL_PARAMETER4_SERVER,
        INSERT_SUBNET4,
        INSERT_SUBNET4_SERVER,
        INSERT_POOL4,
        INSERT_SHARED_NETWORK4,
        INSERT_SHARED_NETWORK4_SERVER,
        INSERT_OPTION_DEF4,
        INSERT_OPTION_DEF4_SERVER,
        INSERT_OPTION4,
        INSERT_OPTION4_SERVER,
        UPDATE_GLOBAL_PARAMETER4,
        UPDATE_SUBNET4,
        UPDATE_SHARED_NETWORK4,
        UPDATE_OPTION_DEF4,
        UPDATE_OPTION4,
        UPDATE_OPTION4_SUBNET_ID,
        UPDATE_OPTION4_POOL_ID,
        UPDATE_OPTION4_SHARED_NETWORK,
        DELETE_GLOBAL_PARAMETER4,
        DELETE_ALL_GLOBAL_PARAMETERS4,
        DELETE_SUBNET4_ID,
        DELETE_SUBNET4_PREFIX,
        DELETE_ALL_SUBNETS4,
        DELETE_ALL_SUBNETS4_SHARED_NETWORK_NAME,
        DELETE_POOLS4_SUBNET_ID,
        DELETE_SHARED_NETWORK4_NAME,
        DELETE_ALL_SHARED_NETWORKS4,
        DELETE_OPTION_DEF4_CODE_NAME,
        DELETE_ALL_OPTION_DEFS4,
        DELETE_OPTION4,
        DELETE_OPTION4_SUBNET_ID,
        DELETE_OPTION4_POOL_RANGE,
        DELETE_OPTION4_SHARED_NETWORK,
        DELETE_OPTIONS4_SUBNET_ID,
        DELETE_OPTIONS4_SHARED_NETWORK,
        NUM_STATEMENTS
    };

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    explicit MySqlConfigBackendDHCPv4Impl(const DatabaseConnection::ParameterMap&
                                          parameters);

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

        auto tags = getServerTags(server_selector);
        for (auto tag : tags) {
            MySqlBindingCollection in_bindings = {
                MySqlBinding::createString(tag),
                MySqlBinding::createString(name)
            };

            getGlobalParameters(GET_GLOBAL_PARAMETER4, in_bindings, parameters);
        }

        return (parameters.empty() ? StampedValuePtr() : *parameters.begin());
    }

    /// @brief Sends query to insert or update global parameter.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the global parameter.
    /// @param value Value of the global parameter.
    void createUpdateGlobalParameter4(const db::ServerSelector& server_selector,
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
            audit_revision(this, MySqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                           server_selector, "global parameter set", false);

        // Try to update the existing row.
        if (conn_.updateDeleteQuery(MySqlConfigBackendDHCPv4Impl::UPDATE_GLOBAL_PARAMETER4,
                                    in_bindings) == 0) {

            // No such parameter found, so let's insert it. We have to adjust the
            // bindings collection to match the prepared statement for insert.
            in_bindings.pop_back();
            in_bindings.pop_back();
            conn_.insertQuery(MySqlConfigBackendDHCPv4Impl::INSERT_GLOBAL_PARAMETER4,
                              in_bindings);

            // Successfully inserted global parameter. Now, we have to associate it
            // with the server tag.

            // Let's first get the primary key of the global parameter.
            uint64_t id = mysql_insert_id(conn_.mysql_);

            // Create bindings for inserting the association into
            // dhcp4_global_parameter_server table.
            MySqlBindingCollection in_server_bindings = {
                MySqlBinding::createInteger<uint64_t>(id), // parameter_id
                MySqlBinding::createString(tag), // tag used to obtain server_id
                MySqlBinding::createTimestamp(value->getModificationTime()), // modification_ts
            };

            // Insert association.
            conn_.insertQuery(MySqlConfigBackendDHCPv4Impl::INSERT_GLOBAL_PARAMETER4_SERVER,
                              in_server_bindings);

        }

        transaction.commit();
    }

    /// @brief Sends query to the database to retrieve multiple subnets.
    ///
    /// Query should order subnets by subnet_id.
    ///
    /// @param index Index of the query to be used.
    /// @param in_bindings Input bindings specifying selection criteria. The
    /// size of the bindings collection must match the number of placeholders
    /// in the prepared statement. The input bindings collection must be empty
    /// if the query contains no WHERE clause.
    /// @param [out] subnets Reference to the container where fetched subnets
    /// will be inserted.
    void getSubnets4(const StatementIndex& index,
                     const MySqlBindingCollection& in_bindings,
                     Subnet4Collection& subnets) {
        // Create output bindings. The order must match that in the prepared
        // statement.
        MySqlBindingCollection out_bindings = {
            MySqlBinding::createInteger<uint32_t>(), // subnet_id
            MySqlBinding::createString(SUBNET4_PREFIX_BUF_LENGTH), // subnet_prefix
            MySqlBinding::createString(DHCP4O6_INTERFACE_BUF_LENGTH), // 4o6_interface
            MySqlBinding::createString(DHCP4O6_INTERFACE_ID_BUF_LENGTH), // 4o6_interface_id
            MySqlBinding::createString(DHCP4O6_SUBNET_BUF_LENGTH), // 4o6_subnet
            MySqlBinding::createString(BOOT_FILE_NAME_BUF_LENGTH), // boot_file_name
            MySqlBinding::createString(CLIENT_CLASS_BUF_LENGTH), // client_class
            MySqlBinding::createString(INTERFACE_BUF_LENGTH), // interface
            MySqlBinding::createInteger<uint8_t>(), // match_client_id
            MySqlBinding::createTimestamp(), // modification_ts
            MySqlBinding::createInteger<uint32_t>(), // next_server
            MySqlBinding::createInteger<uint32_t>(), // rebind_timer
            MySqlBinding::createString(RELAY_BUF_LENGTH), // relay
            MySqlBinding::createInteger<uint32_t>(), // renew_timer
            MySqlBinding::createString(REQUIRE_CLIENT_CLASSES_BUF_LENGTH), // require_client_classes
            MySqlBinding::createInteger<uint8_t>(), // reservation_mode
            MySqlBinding::createString(SERVER_HOSTNAME_BUF_LENGTH), // server_hostname
            MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // shared_network_name
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // user_context
            MySqlBinding::createInteger<uint32_t>(), // valid_lifetime
            MySqlBinding::createInteger<uint64_t>(), // pool: id
            MySqlBinding::createInteger<uint32_t>(), // pool: start_address
            MySqlBinding::createInteger<uint32_t>(), // pool: end_address
            MySqlBinding::createInteger<uint32_t>(), // pool: subnet_id
            MySqlBinding::createTimestamp(), // pool: modification_ts
            MySqlBinding::createInteger<uint64_t>(), // pool option: option_id
            MySqlBinding::createInteger<uint8_t>(), // pool option: code
            MySqlBinding::createBlob(OPTION_VALUE_BUF_LENGTH), // pool option: value
            MySqlBinding::createString(FORMATTED_OPTION_VALUE_BUF_LENGTH), // pool option: formatted_value
            MySqlBinding::createString(OPTION_SPACE_BUF_LENGTH), // pool option: space
            MySqlBinding::createInteger<uint8_t>(), // pool option: persistent
            MySqlBinding::createInteger<uint32_t>(), // pool option: dhcp4_subnet_id
            MySqlBinding::createInteger<uint8_t>(), // pool option: scope_id
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // pool option: user_context
            MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // pool option: shared_network_name
            MySqlBinding::createInteger<uint64_t>(), // pool option: pool_id
            MySqlBinding::createTimestamp(), //pool option: modification_ts
            MySqlBinding::createInteger<uint64_t>(), // option: option_id
            MySqlBinding::createInteger<uint8_t>(), // option: code
            MySqlBinding::createBlob(OPTION_VALUE_BUF_LENGTH), // option: value
            MySqlBinding::createString(FORMATTED_OPTION_VALUE_BUF_LENGTH), // option: formatted_value
            MySqlBinding::createString(OPTION_SPACE_BUF_LENGTH), // option: space
            MySqlBinding::createInteger<uint8_t>(), // option: persistent
            MySqlBinding::createInteger<uint32_t>(), // option: dhcp4_subnet_id
            MySqlBinding::createInteger<uint8_t>(), // option: scope_id
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // option: user_context
            MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // option: shared_network_name
            MySqlBinding::createInteger<uint64_t>(), // option: pool_id
            MySqlBinding::createTimestamp(), //option: modification_ts
            MySqlBinding::createInteger<uint8_t>(), // calculate_tee_times
            MySqlBinding::createInteger<float>(), // t1_percent
            MySqlBinding::createInteger<float>(), // t2_percent
            MySqlBinding::createInteger<uint8_t>() // authoritative
        };

        uint64_t last_pool_id = 0;
        uint64_t last_pool_option_id = 0;
        uint64_t last_option_id = 0;

        Pool4Ptr last_pool;

        // Execute actual query.
        conn_.selectQuery(index, in_bindings, out_bindings,
                          [this, &subnets, &last_pool, &last_pool_id,
                           &last_pool_option_id, &last_option_id]
                          (MySqlBindingCollection& out_bindings) {
            // Get pointer to the last subnet in the collection.
            Subnet4Ptr last_subnet;
            if (!subnets.empty()) {
                last_subnet = *subnets.rbegin();
            }

            // Subnet has been returned. Assuming that subnets are ordered by
            // subnet identifier, if the subnet identifier of the current row
            // is different than the subnet identifier of the previously returned
            // row, it means that we have to construct new subnet object.
            if (!last_subnet || (last_subnet->getID() != out_bindings[0]->getInteger<uint32_t>())) {

                // Reset pool id, because current row defines new subnet. Subsequent
                // rows will contain pool information.
                last_pool_id = 0;

                // subnet_id
                SubnetID subnet_id(out_bindings[0]->getInteger<uint32_t>());
                // subnet_prefix
                std::string subnet_prefix = out_bindings[1]->getString();
                auto prefix_pair = Subnet4::parsePrefix(subnet_prefix);
                // renew_timer
                auto renew_timer = createTriplet(out_bindings[13]);
                // rebind_timer
                auto rebind_timer = createTriplet(out_bindings[11]);
                // valid_lifetime
                auto valid_lifetime = createTriplet(out_bindings[19]);

                // Create subnet with basic settings.
                last_subnet.reset(new Subnet4(prefix_pair.first, prefix_pair.second,
                                              renew_timer, rebind_timer,
                                              valid_lifetime, subnet_id));

                // 4o6_interface
                if (!out_bindings[2]->amNull()) {
                    last_subnet->get4o6().setIface4o6(out_bindings[2]->getString());
                }
                // 4o6_interface_id
                if (!out_bindings[3]->amNull()) {
                    std::string dhcp4o6_interface_id = out_bindings[3]->getString();
                    OptionBuffer dhcp4o6_interface_id_buf(dhcp4o6_interface_id.begin(),
                                                          dhcp4o6_interface_id.end());
                    OptionPtr option_dhcp4o6_interface_id(new Option(Option::V6, D6O_INTERFACE_ID,
                                                                     dhcp4o6_interface_id_buf));
                    last_subnet->get4o6().setInterfaceId(option_dhcp4o6_interface_id);
                }
                // 4o6_subnet
                if (!out_bindings[4]->amNull()) {
                    std::pair<IOAddress, uint8_t> dhcp4o6_subnet_prefix_pair =
                        Subnet6::parsePrefix(out_bindings[4]->getString());
                    last_subnet->get4o6().setSubnet4o6(dhcp4o6_subnet_prefix_pair.first,
                                                       dhcp4o6_subnet_prefix_pair.second);
                }
                // boot_file_name
                if (!out_bindings[5]->amNull()) {
                    last_subnet->setFilename(out_bindings[5]->getString());
                }

                // client_class
                if (!out_bindings[6]->amNull()) {
                    last_subnet->allowClientClass(out_bindings[6]->getString());
                }
                // interface
                if (!out_bindings[7]->amNull()) {
                    last_subnet->setIface(out_bindings[7]->getString());
                }

                // match_client_id
                if (!out_bindings[8]->amNull()) {
                    last_subnet->setMatchClientId(out_bindings[8]->getBool());
                }

                // modification_ts
                last_subnet->setModificationTime(out_bindings[9]->getTimestamp());

                // next_server
                if (!out_bindings[10]->amNull()) {
                    last_subnet->setSiaddr(IOAddress(out_bindings[10]->getInteger<uint32_t>()));
                }

                // relay
                ElementPtr relay_element = out_bindings[12]->getJSON();
                if (relay_element) {
                    if (relay_element->getType() != Element::list) {
                        isc_throw(BadValue, "invalid relay value "
                                  << out_bindings[12]->getString());
                    }
                    for (auto i = 0; i < relay_element->size(); ++i) {
                        auto relay_address_element = relay_element->get(i);
                        if (relay_address_element->getType() != Element::string) {
                            isc_throw(BadValue, "relay address must be a string");
                        }
                        last_subnet->addRelayAddress(IOAddress(relay_element->get(i)->stringValue()));
                    }
                }
                // require_client_classes
                ElementPtr require_element = out_bindings[14]->getJSON();
                if (require_element) {
                    if (require_element->getType() != Element::list) {
                        isc_throw(BadValue, "invalid require_client_classes value "
                                  << out_bindings[14]->getString());
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
                // reservation_mode
                if (!out_bindings[15]->amNull()) {
                    last_subnet->setHostReservationMode(static_cast<Subnet4::HRMode>
                        (out_bindings[15]->getInteger<uint8_t>()));
                }

                // server_hostname
                if (!out_bindings[16]->amNull()) {
                    last_subnet->setSname(out_bindings[16]->getString());
                }

                // shared_network_name
                if (!out_bindings[17]->amNull()) {
                    last_subnet->setSharedNetworkName(out_bindings[17]->getString());
                }

                // user_context
                ElementPtr user_context = out_bindings[18]->getJSON();
                if (user_context) {
                    last_subnet->setContext(user_context);
                }

                // calculate_tee_times
                if (!out_bindings[49]->amNull()) {
                    last_subnet->setCalculateTeeTimes(out_bindings[49]->getBool());
                }

                // t1_percent
                if (!out_bindings[50]->amNull()) {
                    last_subnet->setT1Percent(out_bindings[50]->getFloat());
                }

                // t2_percent
                if (!out_bindings[51]->amNull()) {
                    last_subnet->setT2Percent(out_bindings[51]->getFloat());
                }

                // authoritative
                if (!out_bindings[52]->amNull()) {
                    last_subnet->setAuthoritative(out_bindings[52]->getBool());
                }

                // Subnet ready. Add it to the list.
                subnets.push_back(last_subnet);
            }

            // If the row contains information about the pool and it appears to be
            // new pool entry (checked by comparing pool id), let's create the new
            // pool and add it to the subnet.
            if (!out_bindings[20]->amNull() &&
                (out_bindings[21]->getInteger<uint32_t>() != 0) &&
                (out_bindings[22]->getInteger<uint32_t>() != 0) &&
                (out_bindings[20]->getInteger<uint64_t>() > last_pool_id)) {
                last_pool_id = out_bindings[20]->getInteger<uint64_t>();
                last_pool.reset(new Pool4(IOAddress(out_bindings[21]->getInteger<uint32_t>()),
                                          IOAddress(out_bindings[22]->getInteger<uint32_t>())));
                last_subnet->addPool(last_pool);
            }

            // Parse pool specific option.
            if (last_pool && !out_bindings[25]->amNull() &&
                (last_pool_option_id < out_bindings[25]->getInteger<uint64_t>())) {
                last_pool_option_id = out_bindings[25]->getInteger<uint64_t>();

                OptionDescriptorPtr desc = processOptionRow(Option::V4, out_bindings.begin() + 25);
                if (desc) {
                    last_pool->getCfgOption()->add(*desc, desc->space_name_);
                }
            }

            // Parse subnet specific option.
            if (!out_bindings[37]->amNull() &&
                (last_option_id < out_bindings[37]->getInteger<uint64_t>())) {
                last_option_id = out_bindings[37]->getInteger<uint64_t>();

                OptionDescriptorPtr desc = processOptionRow(Option::V4, out_bindings.begin() + 37);
                if (desc) {
                    last_subnet->getCfgOption()->add(*desc, desc->space_name_);
                }
            }

        });
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
        Subnet4Collection subnets;

        auto tags = getServerTags(server_selector);
        for (auto tag : tags) {
            MySqlBindingCollection in_bindings = {
                MySqlBinding::createString(tag),
                MySqlBinding::createInteger<uint32_t>(subnet_id)
            };

            getSubnets4(GET_SUBNET4_ID, in_bindings, subnets);
        }

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
        Subnet4Collection subnets;

        auto tags = getServerTags(server_selector);
        for (auto tag : tags) {
            MySqlBindingCollection in_bindings = {
                MySqlBinding::createString(tag),
                MySqlBinding::createString(subnet_prefix)
            };

            getSubnets4(GET_SUBNET4_PREFIX, in_bindings, subnets);
        }

        return (subnets.empty() ? Subnet4Ptr() : *subnets.begin());
    }

    /// @brief Sends query to retrieve all subnets.
    ///
    /// @param server_selector Server selector.
    /// @param [out] subnets Reference to the subnet collection structure where
    /// subnets should be inserted.
    void getAllSubnets4(const ServerSelector& server_selector,
                        Subnet4Collection& subnets) {
        auto tags = getServerTags(server_selector);

        for (auto tag : tags) {
            MySqlBindingCollection in_bindings = {
                MySqlBinding::createString(tag)
            };

            getSubnets4(GET_ALL_SUBNETS4, in_bindings, subnets);
        }
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
        auto tags = getServerTags(server_selector);

        for (auto tag : tags) {
            MySqlBindingCollection in_bindings = {
                MySqlBinding::createString(tag),
                MySqlBinding::createTimestamp(modification_ts)
            };

            getSubnets4(GET_MODIFIED_SUBNETS4, in_bindings, subnets);
        }
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
        auto tags = getServerTags(server_selector);

        for (auto tag : tags) {
            MySqlBindingCollection in_bindings = {
                MySqlBinding::createString(tag),
                MySqlBinding::createString(shared_network_name)
            };

            getSubnets4(GET_SHARED_NETWORK_SUBNETS4, in_bindings, subnets);
        }
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
            MySqlBinding::createInteger<uint32_t>(), // pool: start_address
            MySqlBinding::createInteger<uint32_t>(), // pool: end_address
            MySqlBinding::createInteger<uint32_t>(), // pool: subnet_id
            MySqlBinding::createTimestamp(), // pool: modification_ts
            MySqlBinding::createInteger<uint64_t>(), // pool option: option_id
            MySqlBinding::createInteger<uint8_t>(), // pool option: code
            MySqlBinding::createBlob(OPTION_VALUE_BUF_LENGTH), // pool option: value
            MySqlBinding::createString(FORMATTED_OPTION_VALUE_BUF_LENGTH), // pool option: formatted_value
            MySqlBinding::createString(OPTION_SPACE_BUF_LENGTH), // pool option: space
            MySqlBinding::createInteger<uint8_t>(), // pool option: persistent
            MySqlBinding::createInteger<uint32_t>(), // pool option: dhcp4_subnet_id
            MySqlBinding::createInteger<uint8_t>(), // pool option: scope_id
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // pool option: user_context
            MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // pool option: shared_network_name
            MySqlBinding::createInteger<uint64_t>(), // pool option: pool_id
            MySqlBinding::createTimestamp(), //pool option: modification_ts
        };

        uint64_t last_pool_id = 0;
        uint64_t last_pool_option_id = 0;
        Pool4Ptr last_pool;

        conn_.selectQuery(index, in_bindings, out_bindings,
                          [this, &last_pool_id, &last_pool_option_id, &last_pool,
                           &pools, &pool_ids]
                          (MySqlBindingCollection& out_bindings) {
            if (out_bindings[0]->getInteger<uint64_t>() > last_pool_id) {

                last_pool_id = out_bindings[0]->getInteger<uint64_t>();

                last_pool.reset(new Pool4(IOAddress(out_bindings[1]->getInteger<uint32_t>()),
                                          IOAddress(out_bindings[2]->getInteger<uint32_t>())));
                pools.push_back(last_pool);
                pool_ids.push_back(last_pool_id);
            }

            // Parse pool specific option.
            if (last_pool && !out_bindings[5]->amNull() &&
                (last_pool_option_id < out_bindings[5]->getInteger<uint64_t>())) {
                last_pool_option_id = out_bindings[5]->getInteger<uint64_t>();

                OptionDescriptorPtr desc = processOptionRow(Option::V4, out_bindings.begin() + 5);
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
    Pool4Ptr getPool4(const ServerSelector& /* server_selector */,
                      const IOAddress& pool_start_address,
                      const IOAddress& pool_end_address,
                      uint64_t& pool_id) {
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint32_t>(pool_start_address.toUint32()),
            MySqlBinding::createInteger<uint32_t>(pool_end_address.toUint32())
        };

        PoolCollection pools;
        std::vector<uint64_t> pool_ids;
        getPools(GET_POOL4_RANGE, in_bindings, pools, pool_ids);

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

        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        auto tag = getServerTag(server_selector, "creating or updating subnet");

        // Convert DHCPv4o6 interface id to text.
        OptionPtr dhcp4o6_interface_id = subnet->get4o6().getInterfaceId();
        MySqlBindingPtr dhcp4o6_interface_id_binding;
        if (dhcp4o6_interface_id) {
            std::string dhcp4o6_interface_id_text(dhcp4o6_interface_id->getData().begin(),
                                                  dhcp4o6_interface_id->getData().end());
            dhcp4o6_interface_id_binding = MySqlBinding::createString(dhcp4o6_interface_id_text);

        } else {
            dhcp4o6_interface_id_binding = MySqlBinding::createNull();
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

        // Create JSON list of required classes.
        ElementPtr required_classes_element = Element::createList();
        const auto& required_classes = subnet->getRequiredClasses();
        for (auto required_class = required_classes.cbegin();
             required_class != required_classes.cend();
             ++required_class) {
            required_classes_element->add(Element::create(*required_class));
        }

        // Create binding for host reservation mode.
        MySqlBindingPtr hr_mode_binding;
        auto hr_mode = subnet->getHostReservationMode();
        if (!hr_mode.unspecified()) {
            hr_mode_binding = MySqlBinding::createInteger<uint8_t>(static_cast<uint8_t>
                                                                   (hr_mode.get()));
        } else {
            hr_mode_binding = MySqlBinding::createNull();
        }

        // Create binding with shared network name if the subnet belongs to a
        // shared network.
        MySqlBindingPtr shared_network_binding;

        SharedNetwork4Ptr shared_network;
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

        // Create input bindings.
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint32_t>(subnet->getID()),
            MySqlBinding::createString(subnet->toText()),
            MySqlBinding::condCreateString(subnet->get4o6().getIface4o6()),
            dhcp4o6_interface_id_binding,
            MySqlBinding::condCreateString(dhcp4o6_subnet),
            MySqlBinding::condCreateString(subnet->getFilename()),
            MySqlBinding::condCreateString(subnet->getClientClass()),
            MySqlBinding::condCreateString(subnet->getIface()),
            MySqlBinding::condCreateBool(subnet->getMatchClientId()),
            MySqlBinding::createTimestamp(subnet->getModificationTime()),
            MySqlBinding::condCreateIPv4Address(subnet->getSiaddr()),
            createBinding(subnet->getT2()),
            createInputRelayBinding(subnet),
            createBinding(subnet->getT1()),
            createInputRequiredClassesBinding(subnet),
            hr_mode_binding,
            MySqlBinding::condCreateString(subnet->getSname()),
            shared_network_binding,
            createInputContextBinding(subnet),
            createBinding(subnet->getValid()),
            MySqlBinding::condCreateBool(subnet->getCalculateTeeTimes()),
            MySqlBinding::condCreateFloat(subnet->getT1Percent()),
            MySqlBinding::condCreateFloat(subnet->getT2Percent()),
            MySqlBinding::condCreateBool(subnet->getAuthoritative())
        };

        MySqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision audit_revision(this,
                                           MySqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                                           server_selector, "subnet set", true);

        try {

            // Try to insert subnet. If this duplicates unique key, i.e. this
            // subnet already exists it will throw DuplicateEntry exception in
            // which case we'll try an update.
            conn_.insertQuery(MySqlConfigBackendDHCPv4Impl::INSERT_SUBNET4,
                              in_bindings);

            // Create bindings for inserting the association into
            // dhcp4_subnet_server table.
            MySqlBindingCollection in_server_bindings = {
                MySqlBinding::createInteger<uint32_t>(subnet->getID()), // subnet_id
                MySqlBinding::createString(tag), // tag used to obtain server_id
                MySqlBinding::createTimestamp(subnet->getModificationTime()), // modification_ts
            };

            // Insert association.
            conn_.insertQuery(MySqlConfigBackendDHCPv4Impl::INSERT_SUBNET4_SERVER,
                              in_server_bindings);


        } catch (const DuplicateEntry&) {
            deletePools4(subnet);
            deleteOptions4(server_selector, subnet);

            // Need to add two more bindings for WHERE clause.
            in_bindings.push_back(MySqlBinding::createInteger<uint32_t>(subnet->getID()));
            in_bindings.push_back(MySqlBinding::createString(subnet->toText()));
            conn_.updateDeleteQuery(MySqlConfigBackendDHCPv4Impl::UPDATE_SUBNET4,
                                    in_bindings);
        }

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
                OptionDescriptorPtr desc_copy(new OptionDescriptor(*desc));
                desc_copy->space_name_ = option_space;
                createUpdateOption4(server_selector, subnet->getID(), desc_copy,
                                    true);
            }
        }

        transaction.commit();
    }

    /// @brief Inserts new IPv4 pool to the database.
    ///
    /// @param server_selector Server selector.
    /// @param pool Pointer to the pool to be inserted.
    /// @param subnet Pointer to the subnet that this pool belongs to.
    void createPool4(const ServerSelector& server_selector, const Pool4Ptr& pool,
                     const Subnet4Ptr& subnet) {
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint32_t>(pool->getFirstAddress().toUint32()),
            MySqlBinding::createInteger<uint32_t>(pool->getLastAddress().toUint32()),
            MySqlBinding::createInteger<uint32_t>(static_cast<uint32_t>(subnet->getID())),
            MySqlBinding::createTimestamp(subnet->getModificationTime())
        };

        // Run INSERT.
        conn_.insertQuery(INSERT_POOL4, in_bindings);

        uint64_t pool_id = mysql_insert_id(conn_.mysql_);
        auto option_spaces = pool->getCfgOption()->getOptionSpaceNames();
        for (auto option_space : option_spaces) {
            OptionContainerPtr options = pool->getCfgOption()->getAll(option_space);
            for (auto desc = options->begin(); desc != options->end(); ++desc) {
                OptionDescriptorPtr desc_copy(new OptionDescriptor(*desc));
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

        MySqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           MySqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
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
        return (deleteTransactional(DELETE_SUBNET4_ID, server_selector,
                                    "deleting a subnet",
                                    "subnet deleted",
                                    true,
                                    static_cast<uint32_t>(subnet_id)));
    }

    /// @brief Deletes pools belonging to a subnet from the database.
    ///
    /// @param subnet Pointer to the subnet for which pools should be
    /// deleted.
    uint64_t deletePools4(const Subnet4Ptr& subnet) {
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint32_t>(subnet->getID())
        };

        // Run DELETE.
        return (conn_.updateDeleteQuery(DELETE_POOLS4_SUBNET_ID, in_bindings));
    }

    /// @brief Sends query to the database to retrieve multiple shared
    /// networks.
    ///
    /// Query should order shared networks by id.
    ///
    /// @param index Index of the query to be used.
    /// @param in_bindings Input bindings specifying selection criteria. The
    /// size of the bindings collection must match the number of placeholders
    /// in the prepared statement. The input bindings collection must be empty
    /// if the query contains no WHERE clause.
    /// @param [out] shared_networks Reference to the container where fetched
    /// shared networks will be inserted.
    void getSharedNetworks4(const StatementIndex& index,
                            const MySqlBindingCollection& in_bindings,
                            SharedNetwork4Collection& shared_networks) {
        // Create output bindings. The order must match that in the prepared
        // statement.
        MySqlBindingCollection out_bindings = {
            MySqlBinding::createInteger<uint64_t>(), // id
            MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // name
            MySqlBinding::createString(CLIENT_CLASS_BUF_LENGTH), // client_class
            MySqlBinding::createString(INTERFACE_BUF_LENGTH), // interface
            MySqlBinding::createInteger<uint8_t>(), // match_client_id
            MySqlBinding::createTimestamp(), // modification_ts
            MySqlBinding::createInteger<uint32_t>(), // rebind_timer
            MySqlBinding::createString(RELAY_BUF_LENGTH), // relay
            MySqlBinding::createInteger<uint32_t>(), // renew_timer
            MySqlBinding::createString(REQUIRE_CLIENT_CLASSES_BUF_LENGTH), // require_client_classes
            MySqlBinding::createInteger<uint8_t>(), // reservation_mode
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // user_context
            MySqlBinding::createInteger<uint32_t>(), // valid_lifetime
            MySqlBinding::createInteger<uint64_t>(), // option: option_id
            MySqlBinding::createInteger<uint8_t>(), // option: code
            MySqlBinding::createBlob(OPTION_VALUE_BUF_LENGTH), // option: value
            MySqlBinding::createString(FORMATTED_OPTION_VALUE_BUF_LENGTH), // option: formatted_value
            MySqlBinding::createString(OPTION_SPACE_BUF_LENGTH), // option: space
            MySqlBinding::createInteger<uint8_t>(), // option: persistent
            MySqlBinding::createInteger<uint32_t>(), // option: dhcp4_subnet_id
            MySqlBinding::createInteger<uint8_t>(), // option: scope_id
            MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // option: user_context
            MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // option: shared_network_name
            MySqlBinding::createInteger<uint64_t>(), // option: pool_id
            MySqlBinding::createTimestamp(), //option: modification_ts
            MySqlBinding::createInteger<uint8_t>(), // calculate_tee_times
            MySqlBinding::createInteger<float>(), // t1_percent
            MySqlBinding::createInteger<float>(), // t2_percent
            MySqlBinding::createInteger<uint8_t>(), // authoritative
            MySqlBinding::createString(BOOT_FILE_NAME_BUF_LENGTH), // boot_file_name
            MySqlBinding::createInteger<uint32_t>(), // next_server
            MySqlBinding::createString(SERVER_HOSTNAME_BUF_LENGTH) // server_hostname
        };

        uint64_t last_network_id = 0;
        uint64_t last_option_id = 0;

        conn_.selectQuery(index, in_bindings, out_bindings,
                          [this, &shared_networks, &last_network_id, &last_option_id]
                          (MySqlBindingCollection& out_bindings) {
            SharedNetwork4Ptr last_network;
            if (!shared_networks.empty()) {
                last_network = *shared_networks.rbegin();
            }

            // If this is the first shared network or the shared network id in this
            // row points to the next shared network we use the data in the
            // row to create the new shared network instance.
            if (last_network_id != out_bindings[0]->getInteger<uint64_t>()) {

                last_network_id = out_bindings[0]->getInteger<uint64_t>();
                last_network.reset(new SharedNetwork4(out_bindings[1]->getString()));

                // client_class
                if (!out_bindings[2]->amNull()) {
                    last_network->allowClientClass(out_bindings[2]->getString());
                }
                // interface
                if (!out_bindings[3]->amNull()) {
                    last_network->setIface(out_bindings[3]->getString());
                }

                // match_client_id
                if (!out_bindings[4]->amNull()) {
                    last_network->setMatchClientId(out_bindings[4]->getBool());
                }

                // modification_ts
                last_network->setModificationTime(out_bindings[5]->getTimestamp());

                // rebind_timer
                if (!out_bindings[6]->amNull()) {
                    last_network->setT2(createTriplet(out_bindings[6]));
                }

                // relay
                ElementPtr relay_element = out_bindings[7]->getJSON();
                if (relay_element) {
                    if (relay_element->getType() != Element::list) {
                        isc_throw(BadValue, "invalid relay value "
                                  << out_bindings[7]->getString());
                    }
                    for (auto i = 0; i < relay_element->size(); ++i) {
                        auto relay_address_element = relay_element->get(i);
                        if (relay_address_element->getType() != Element::string) {
                            isc_throw(BadValue, "relay address must be a string");
                        }
                        last_network->addRelayAddress(IOAddress(relay_element->get(i)->stringValue()));
                    }
                }

                // renew_timer
                if (!out_bindings[8]->amNull()) {
                    last_network->setT1(createTriplet(out_bindings[8]));
                }

                // require_client_classes
                ElementPtr require_element = out_bindings[9]->getJSON();
                if (require_element) {
                    if (require_element->getType() != Element::list) {
                        isc_throw(BadValue, "invalid require_client_classes value "
                              << out_bindings[9]->getString());
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

                // reservation_mode
                if (!out_bindings[10]->amNull()) {
                    last_network->setHostReservationMode(static_cast<Subnet4::HRMode>
                        (out_bindings[10]->getIntegerOrDefault<uint8_t>(Subnet4::HR_ALL)));
                }

                // user_context
                ElementPtr user_context = out_bindings[11]->getJSON();
                if (user_context) {
                    last_network->setContext(user_context);
                }

                // valid_lifetime
                if (!out_bindings[12]->amNull()) {
                    last_network->setValid(createTriplet(out_bindings[12]));
                }

                // calculate_tee_times
                if (!out_bindings[25]->amNull()) {
                    last_network->setCalculateTeeTimes(out_bindings[25]->getBool());
                }

                // t1_percent
                if (!out_bindings[26]->amNull()) {
                    last_network->setT1Percent(out_bindings[26]->getFloat());
                }

                // t2_percent
                if (!out_bindings[27]->amNull()) {
                    last_network->setT2Percent(out_bindings[27]->getFloat());
                }

                // authoritative
                if (!out_bindings[28]->amNull()) {
                    last_network->setAuthoritative(out_bindings[28]->getBool());
                }

                // boot_file_name
                if (!out_bindings[29]->amNull()) {
                    last_network->setFilename(out_bindings[29]->getString());
                }

                // next_server
                if (!out_bindings[30]->amNull()) {
                    last_network->setSiaddr(IOAddress(out_bindings[30]->getInteger<uint32_t>()));
                }

                // server_hostaname
                if (!out_bindings[31]->amNull()) {
                    last_network->setSname(out_bindings[31]->getString());
                }

                shared_networks.push_back(last_network);
            }

            // Parse option.
            if (!out_bindings[13]->amNull() &&
                (last_option_id < out_bindings[13]->getInteger<uint64_t>())) {
                last_option_id = out_bindings[13]->getInteger<uint64_t>();

                OptionDescriptorPtr desc = processOptionRow(Option::V4, out_bindings.begin() + 13);
                if (desc) {
                    last_network->getCfgOption()->add(*desc, desc->space_name_);
                }
            }
        });
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

        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        auto tag = getServerTag(server_selector, "fetching shared network");

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(tag),
            MySqlBinding::createString(name)
        };

        SharedNetwork4Collection shared_networks;
        getSharedNetworks4(GET_SHARED_NETWORK4_NAME, in_bindings, shared_networks);

        return (shared_networks.empty() ? SharedNetwork4Ptr() : *shared_networks.begin());
    }

    /// @brief Sends query to retrieve all shared networks.
    ///
    /// @param server_selector Server selector.
    /// @param [out] shared_networks Reference to the shared networks collection
    /// structure where shared networks should be inserted.
    void getAllSharedNetworks4(const ServerSelector& server_selector,
                               SharedNetwork4Collection& shared_networks) {
        auto tags = getServerTags(server_selector);

        for (auto tag : tags) {
            MySqlBindingCollection in_bindings = {
                MySqlBinding::createString(tag)
            };

            getSharedNetworks4(GET_ALL_SHARED_NETWORKS4, in_bindings, shared_networks);
        }
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
        auto tags = getServerTags(server_selector);

        for (auto tag : tags) {
            MySqlBindingCollection in_bindings = {
                MySqlBinding::createString(tag),
                MySqlBinding::createTimestamp(modification_ts)
            };

            getSharedNetworks4(GET_MODIFIED_SHARED_NETWORKS4, in_bindings,
                               shared_networks);
        }
    }

    /// @brief Sends query to insert or update shared network.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Pointer to the shared network to be inserted or updated.
    void createUpdateSharedNetwork4(const ServerSelector& server_selector,
                                    const SharedNetwork4Ptr& shared_network) {

        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        auto tag = getServerTag(server_selector, "creating or updating shared network");

        // Create binding for host reservation mode.
        MySqlBindingPtr hr_mode_binding;
        auto hr_mode = shared_network->getHostReservationMode();
        if (!hr_mode.unspecified()) {
            hr_mode_binding = MySqlBinding::createInteger<uint8_t>(static_cast<uint8_t>
                                                                   (hr_mode.get()));
        } else {
            hr_mode_binding = MySqlBinding::createNull();
        }

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(shared_network->getName()),
            MySqlBinding::condCreateString(shared_network->getClientClass()),
            MySqlBinding::condCreateString(shared_network->getIface()),
            MySqlBinding::condCreateBool(shared_network->getMatchClientId()),
            MySqlBinding::createTimestamp(shared_network->getModificationTime()),
            createBinding(shared_network->getT2()),
            createInputRelayBinding(shared_network),
            createBinding(shared_network->getT1()),
            createInputRequiredClassesBinding(shared_network),
            hr_mode_binding,
            createInputContextBinding(shared_network),
            createBinding(shared_network->getValid()),
            MySqlBinding::condCreateBool(shared_network->getCalculateTeeTimes()),
            MySqlBinding::condCreateFloat(shared_network->getT1Percent()),
            MySqlBinding::condCreateFloat(shared_network->getT2Percent()),
            MySqlBinding::condCreateBool(shared_network->getAuthoritative()),
            MySqlBinding::condCreateString(shared_network->getFilename()),
            MySqlBinding::condCreateIPv4Address(shared_network->getSiaddr()),
            MySqlBinding::condCreateString(shared_network->getSname())
        };

        MySqlTransaction transaction(conn_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           MySqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                           server_selector, "shared network set", true);

        try {

            // Try to insert shared network. The shared network name must be unique,
            // so if inserting fails with DuplicateEntry exception we'll need to
            // update existing shared network entry.
            conn_.insertQuery(MySqlConfigBackendDHCPv4Impl::INSERT_SHARED_NETWORK4,
                              in_bindings);

            // Create bindings for inserting association into dhcp4_shared_network_server
            // table.
            MySqlBindingCollection in_server_bindings = {
                MySqlBinding::createString(shared_network->getName()), // shared network name
                MySqlBinding::createString(tag), // server tag
                MySqlBinding::createTimestamp(shared_network->getModificationTime()), // modification_ts
            };

            // Insert association.
            conn_.insertQuery(MySqlConfigBackendDHCPv4Impl::INSERT_SHARED_NETWORK4_SERVER,
                              in_server_bindings);


        } catch (const DuplicateEntry&) {
            deleteOptions4(server_selector, shared_network);

            // Need to add one more binding for WHERE clause.
            in_bindings.push_back(MySqlBinding::createString(shared_network->getName()));
            conn_.updateDeleteQuery(MySqlConfigBackendDHCPv4Impl::UPDATE_SHARED_NETWORK4,
                                    in_bindings);
        }

        // (Re)create options.
        auto option_spaces = shared_network->getCfgOption()->getOptionSpaceNames();
        for (auto option_space : option_spaces) {
            OptionContainerPtr options = shared_network->getCfgOption()->getAll(option_space);
            for (auto desc = options->begin(); desc != options->end(); ++desc) {
                OptionDescriptorPtr desc_copy(new OptionDescriptor(*desc));
                desc_copy->space_name_ = option_space;
                createUpdateOption4(server_selector, shared_network->getName(),
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
    void insertOption4(const ServerSelector& server_selector,
                       const MySqlBindingCollection& in_bindings) {
        conn_.insertQuery(MySqlConfigBackendDHCPv4Impl::INSERT_OPTION4,
                          in_bindings);

        // Fetch unique identifier of the inserted option.
        uint64_t id = mysql_insert_id(conn_.mysql_);

        // Create bindings needed to insert association of that option with
        // a server into the dhcp4_options_server table.
        MySqlBindingCollection in_server_bindings = {
            MySqlBinding::createInteger<uint64_t>(id), // option_id
            MySqlBinding::createString(*getServerTags(server_selector).begin()), // server_tag
            in_bindings[11] // copy modification timestamp from option
        };

        conn_.insertQuery(MySqlConfigBackendDHCPv4Impl::INSERT_OPTION4_SERVER,
                          in_server_bindings);
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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint8_t>(option->option_->getType()),
            createOptionValueBinding(option),
            MySqlBinding::condCreateString(option->formatted_value_),
            MySqlBinding::condCreateString(option->space_name_),
            MySqlBinding::createBool(option->persistent_),
            MySqlBinding::createNull(),
            MySqlBinding::createNull(),
            MySqlBinding::createInteger<uint8_t>(0),
            createInputContextBinding(option),
            MySqlBinding::createNull(),
            MySqlBinding::createNull(),
            MySqlBinding::createTimestamp(option->getModificationTime())
        };

        MySqlTransaction transaction(conn_);
        OptionDescriptorPtr existing_option =
            getOption(GET_OPTION4_CODE_SPACE, Option::V4, server_selector,
                      option->option_->getType(), option->space_name_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           MySqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                           server_selector, "global option set", false);

        if (existing_option) {
            in_bindings.push_back(MySqlBinding::createString(tag));
            in_bindings.push_back(MySqlBinding::createInteger<uint8_t>(option->option_->getType()));
            in_bindings.push_back(MySqlBinding::condCreateString(option->space_name_));
            conn_.updateDeleteQuery(MySqlConfigBackendDHCPv4Impl::UPDATE_OPTION4,
                                    in_bindings);

        } else {
            insertOption4(server_selector, in_bindings);

        }

        transaction.commit();
    }

    /// @brief Sends query to insert or update DHCP option in a subnet.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of the subnet the option belongs to.
    /// @param option Pointer to the option descriptor encapsulating the option.
    /// @param cascade_update Boolean value indicating whether the update is
    /// performed as part of the ownining element, e.g. subnet.
    void createUpdateOption4(const ServerSelector& server_selector,
                             const SubnetID& subnet_id,
                             const OptionDescriptorPtr& option,
                             const bool cascade_update) {

        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        auto tag = getServerTag(server_selector,
                                "creating or updating subnet level option");

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint8_t>(option->option_->getType()),
            createOptionValueBinding(option),
            MySqlBinding::condCreateString(option->formatted_value_),
            MySqlBinding::condCreateString(option->space_name_),
            MySqlBinding::createBool(option->persistent_),
            MySqlBinding::createNull(),
            MySqlBinding::createInteger<uint32_t>(static_cast<uint32_t>(subnet_id)),
            MySqlBinding::createInteger<uint8_t>(1),
            createInputContextBinding(option),
            MySqlBinding::createNull(),
            MySqlBinding::createNull(),
            MySqlBinding::createTimestamp(option->getModificationTime())
        };


        boost::scoped_ptr<MySqlTransaction> transaction;
        // Only start new transaction if specified to do so. This function may
        // be called from within an existing transaction in which case we
        // don't start the new one.
        if (!cascade_update) {
            transaction.reset(new MySqlTransaction(conn_));
        }

        OptionDescriptorPtr existing_option =
            getOption(GET_OPTION4_SUBNET_ID_CODE_SPACE, Option::V4,
                      server_selector, subnet_id,
                      option->option_->getType(),
                      option->space_name_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           MySqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                           server_selector, "subnet specific option set",
                           cascade_update);

        if (existing_option) {
            in_bindings.push_back(MySqlBinding::createString(tag));
            in_bindings.push_back(MySqlBinding::createInteger<uint32_t>(static_cast<uint32_t>(subnet_id)));
            in_bindings.push_back(MySqlBinding::createInteger<uint8_t>(option->option_->getType()));
            in_bindings.push_back(MySqlBinding::condCreateString(option->space_name_));
            conn_.updateDeleteQuery(MySqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_SUBNET_ID,
                                    in_bindings);

        } else {
            insertOption4(server_selector, in_bindings);
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
    /// performed as part of the ownining element, e.g. subnet.
    void createUpdateOption4(const ServerSelector& server_selector,
                             const uint64_t pool_id,
                             const OptionDescriptorPtr& option,
                             const bool cascade_update) {

        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        auto tag = getServerTag(server_selector,
                                "creating or updating pool level option");

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint8_t>(option->option_->getType()),
            createOptionValueBinding(option),
            MySqlBinding::condCreateString(option->formatted_value_),
            MySqlBinding::condCreateString(option->space_name_),
            MySqlBinding::createBool(option->persistent_),
            MySqlBinding::createNull(),
            MySqlBinding::createNull(),
            MySqlBinding::createInteger<uint8_t>(5),
            createInputContextBinding(option),
            MySqlBinding::createNull(),
            MySqlBinding::createInteger<uint64_t>(pool_id),
            MySqlBinding::createTimestamp(option->getModificationTime())
        };

        MySqlTransaction transaction(conn_);

        OptionDescriptorPtr existing_option =
            getOption(GET_OPTION4_POOL_ID_CODE_SPACE,
                      server_selector, Lease::TYPE_V4, pool_id,
                      option->option_->getType(), option->space_name_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           MySqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                           server_selector, "pool specific option set",
                           cascade_update);

        if (existing_option) {
            in_bindings.push_back(MySqlBinding::createString(tag));
            in_bindings.push_back(MySqlBinding::createInteger<uint64_t>(pool_id));
            in_bindings.push_back(MySqlBinding::createInteger<uint8_t>(option->option_->getType()));
            in_bindings.push_back(MySqlBinding::condCreateString(option->space_name_));
            conn_.updateDeleteQuery(MySqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_POOL_ID,
                                    in_bindings);

        } else {
            insertOption4(server_selector, in_bindings);
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
    /// performed as part of the ownining element, e.g. shared network.
    void createUpdateOption4(const ServerSelector& server_selector,
                             const std::string& shared_network_name,
                             const OptionDescriptorPtr& option,
                             const bool cascade_update) {

        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        auto tag = getServerTag(server_selector, "creating or updating shared"
                                " network level option");

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint8_t>(option->option_->getType()),
            createOptionValueBinding(option),
            MySqlBinding::condCreateString(option->formatted_value_),
            MySqlBinding::condCreateString(option->space_name_),
            MySqlBinding::createBool(option->persistent_),
            MySqlBinding::createNull(),
            MySqlBinding::createNull(),
            MySqlBinding::createInteger<uint8_t>(4),
            createInputContextBinding(option),
            MySqlBinding::createString(shared_network_name),
            MySqlBinding::createNull(),
            MySqlBinding::createTimestamp(option->getModificationTime())
        };

        boost::scoped_ptr<MySqlTransaction> transaction;
        // Only start new transaction if specified to do so. This function may
        // be called from within an existing transaction in which case we
        // don't start the new one.
        if (!cascade_update) {
            transaction.reset(new MySqlTransaction(conn_));
        }

        OptionDescriptorPtr existing_option =
            getOption(GET_OPTION4_SHARED_NETWORK_CODE_SPACE, Option::V4,
                      server_selector, shared_network_name,
                      option->option_->getType(), option->space_name_);

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           MySqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                           server_selector, "shared network specific option set",
                           cascade_update);

        if (existing_option) {
            in_bindings.push_back(MySqlBinding::createString(tag));
            in_bindings.push_back(MySqlBinding::createString(shared_network_name));
            in_bindings.push_back(MySqlBinding::createInteger<uint8_t>(option->option_->getType()));
            in_bindings.push_back(MySqlBinding::condCreateString(option->space_name_));
            conn_.updateDeleteQuery(MySqlConfigBackendDHCPv4Impl::
                                    UPDATE_OPTION4_SHARED_NETWORK,
                                    in_bindings);
        } else {
            insertOption4(server_selector, in_bindings);
        }

        if (transaction) {
            transaction->commit();
        }
    }

    /// @brief Sends query to insert or update option definition.
    ///
    /// @param server_selector Server selector.
    /// @param option_def Pointer to the option definition to be inserted or updated.
    void createUpdateOptionDef4(const ServerSelector& server_selector,
                                const OptionDefinitionPtr& option_def) {

        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        auto tag = getServerTag(server_selector, "creating or updating option definition");

        ElementPtr record_types = Element::createList();
        for (auto field : option_def->getRecordFields()) {
            record_types->add(Element::create(static_cast<int>(field)));
        }
        MySqlBindingPtr record_types_binding = record_types->empty() ?
            MySqlBinding::createNull() : MySqlBinding::createString(record_types->str());

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint8_t>(static_cast<uint8_t>(option_def->getCode())),
            MySqlBinding::createString(option_def->getName()),
            MySqlBinding::createString(option_def->getOptionSpaceName().empty() ?
                                       "dhcp4" : option_def->getOptionSpaceName()),
            MySqlBinding::createInteger<uint8_t>(static_cast<uint8_t>(option_def->getType())),
            MySqlBinding::createTimestamp(option_def->getModificationTime()),
            MySqlBinding::createBool(option_def->getArrayType()),
            MySqlBinding::createString(option_def->getEncapsulatedSpace()),
            record_types_binding,
            createInputContextBinding(option_def)
        };

        MySqlTransaction transaction(conn_);

        // Need to check if this definition already exists. We can't follow
        // the same pattern as for shared networks and subnets, to try to insert
        // the definition first and fall back to update if the DuplicateEntry
        // exception is thrown, because the option code/space is not unique
        // within the dhcp4_option_def table. Inserting another option definition
        // with existing option code/name would not violate the key and the
        // option definition instance would be inserted successfully. Therefore,
        // we first fetch the option definition for the given server, code and
        // space name. If it exists, we simply update it.
        OptionDefinitionPtr existing_definition =
            getOptionDef(GET_OPTION_DEF4_CODE_SPACE,
                         server_selector,
                         option_def->getCode(),
                         option_def->getOptionSpaceName());

        // Create scoped audit revision. As long as this instance exists
        // no new audit revisions are created in any subsequent calls.
        ScopedAuditRevision
            audit_revision(this,
                           MySqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                           server_selector, "option definition set",
                           true);

        if (existing_definition) {
            // Need to add three more bindings for WHERE clause.
            in_bindings.push_back(MySqlBinding::createString(tag));
            in_bindings.push_back(MySqlBinding::createInteger<uint8_t>(existing_definition->getCode()));
            in_bindings.push_back(MySqlBinding::createString(existing_definition->getOptionSpaceName()));
            conn_.updateDeleteQuery(MySqlConfigBackendDHCPv4Impl::UPDATE_OPTION_DEF4,
                                    in_bindings);

        } else {
            // If the option definition doesn't exist, let's insert it.
            conn_.insertQuery(MySqlConfigBackendDHCPv4Impl::INSERT_OPTION_DEF4,
                              in_bindings);

            // Fetch unique identifier of the inserted option definition and use it
            // as input to the next query.
            uint64_t id = mysql_insert_id(conn_.mysql_);

            MySqlBindingCollection in_server_bindings = {
                MySqlBinding::createInteger<uint64_t>(id), // option_def_id
                MySqlBinding::createString(tag), // tag used to obtain server_id
                MySqlBinding::createTimestamp(option_def->getModificationTime()), // modification_ts
            };

            // Insert association.
            conn_.insertQuery(MySqlConfigBackendDHCPv4Impl::INSERT_OPTION_DEF4_SERVER,
                              in_server_bindings);
        }

        transaction.commit();
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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint16_t>(code),
            MySqlBinding::createString(space)
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTION_DEF4_CODE_NAME, server_selector,
                                    "deleting option definition",
                                    "option definition deleted",
                                    false,
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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint8_t>(code),
            MySqlBinding::createString(space)
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTION4, server_selector,
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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint32_t>(static_cast<uint32_t>(subnet_id)),
            MySqlBinding::createInteger<uint8_t>(code),
            MySqlBinding::createString(space)
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTION4_SUBNET_ID, server_selector,
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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint8_t>(code),
            MySqlBinding::createString(space),
            MySqlBinding::createInteger<uint32_t>(pool_start_address.toUint32()),
            MySqlBinding::createInteger<uint32_t>(pool_end_address.toUint32())
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTION4_POOL_RANGE, server_selector,
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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(shared_network_name),
            MySqlBinding::createInteger<uint8_t>(code),
            MySqlBinding::createString(space)
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTION4_SHARED_NETWORK, server_selector,
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

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint32_t>(subnet->getID())
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTIONS4_SUBNET_ID, server_selector,
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
    uint64_t deleteOptions4(const ServerSelector& server_selector,
                            const SharedNetwork4Ptr& shared_network) {

        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(shared_network->getName())
        };

        // Run DELETE.
        return (deleteTransactional(DELETE_OPTIONS4_SHARED_NETWORK, server_selector,
                                    "deleting options for a shared network",
                                    "shared network specific options deleted",
                                    true,
                                    in_bindings));
    }
};

namespace {

/// @brief Array of tagged statements.
typedef std::array<TaggedStatement, MySqlConfigBackendDHCPv4Impl::NUM_STATEMENTS>
TaggedStatementArray;

/// @brief Prepared MySQL statements used by the backend to insert and
/// retrieve data from the database.
TaggedStatementArray tagged_statements = { {
    { MySqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
      "CALL createAuditRevisionDHCP4(?, ?, ?, ?)"
    },

    // Select global parameter by name.
    { MySqlConfigBackendDHCPv4Impl::GET_GLOBAL_PARAMETER4,
      MYSQL_GET_GLOBAL_PARAMETER(dhcp4, AND g.name = ?)
    },

    // Select all global parameters.
    { MySqlConfigBackendDHCPv4Impl::GET_ALL_GLOBAL_PARAMETERS4,
      MYSQL_GET_GLOBAL_PARAMETER(dhcp4)
    },

    // Select modified global parameters.
    { MySqlConfigBackendDHCPv4Impl::GET_MODIFIED_GLOBAL_PARAMETERS4,
      MYSQL_GET_GLOBAL_PARAMETER(dhcp4, AND g.modification_ts > ?)
    },

    // Select subnet by id.
    { MySqlConfigBackendDHCPv4Impl::GET_SUBNET4_ID,
      MYSQL_GET_SUBNET4(AND s.subnet_id = ?)
    },

    // Select subnet by prefix.
    { MySqlConfigBackendDHCPv4Impl::GET_SUBNET4_PREFIX,
      MYSQL_GET_SUBNET4(AND s.subnet_prefix = ?)
    },

    // Select all subnets.
    { MySqlConfigBackendDHCPv4Impl::GET_ALL_SUBNETS4,
      MYSQL_GET_SUBNET4()
    },

    // Select subnets having modification time later than X.
    { MySqlConfigBackendDHCPv4Impl::GET_MODIFIED_SUBNETS4,
      MYSQL_GET_SUBNET4(AND s.modification_ts > ?)
    },

    // Select subnets belonging to a shared network.
    { MySqlConfigBackendDHCPv4Impl::GET_SHARED_NETWORK_SUBNETS4,
      MYSQL_GET_SUBNET4(AND s.shared_network_name = ?)
    },

    // Select pool by address range.
    { MySqlConfigBackendDHCPv4Impl::GET_POOL4_RANGE,
      "SELECT"
      "  p.id,"
      "  p.start_address,"
      "  p.end_address,"
      "  p.subnet_id,"
      "  p.modification_ts,"
      "  x.option_id,"
      "  x.code,"
      "  x.value,"
      "  x.formatted_value,"
      "  x.space,"
      "  x.persistent,"
      "  x.dhcp4_subnet_id,"
      "  x.scope_id,"
      "  x.user_context,"
      "  x.shared_network_name,"
      "  x.pool_id,"
      "  x.modification_ts "
      "FROM dhcp4_pool AS p "
      "LEFT JOIN dhcp4_options AS x ON x.scope_id = 5 AND p.id = x.pool_id "
      "WHERE p.start_address = ? AND p.end_address = ? "
      "ORDER BY p.id, x.option_id"
    },

    // Select shared network by name.
    { MySqlConfigBackendDHCPv4Impl::GET_SHARED_NETWORK4_NAME,
      MYSQL_GET_SHARED_NETWORK4(AND n.name = ?)
    },

    // Select all shared networks.
    { MySqlConfigBackendDHCPv4Impl::GET_ALL_SHARED_NETWORKS4,
      MYSQL_GET_SHARED_NETWORK4()
    },

    // Select modified shared networks.
    { MySqlConfigBackendDHCPv4Impl::GET_MODIFIED_SHARED_NETWORKS4,
      MYSQL_GET_SHARED_NETWORK4(AND n.modification_ts > ?)
    },

    // Retrieves option definition by code and space.
    { MySqlConfigBackendDHCPv4Impl::GET_OPTION_DEF4_CODE_SPACE,
      MYSQL_GET_OPTION_DEF(dhcp4, AND d.code = ? AND d.space = ?)
    },

    // Retrieves all option definitions.
    { MySqlConfigBackendDHCPv4Impl::GET_ALL_OPTION_DEFS4,
      MYSQL_GET_OPTION_DEF(dhcp4)
    },

    // Retrieves modified option definitions.
    { MySqlConfigBackendDHCPv4Impl::GET_MODIFIED_OPTION_DEFS4,
      MYSQL_GET_OPTION_DEF(dhcp4, AND d.modification_ts > ?)
    },

    // Retrieves global option by code and space.
    { MySqlConfigBackendDHCPv4Impl::GET_OPTION4_CODE_SPACE,
      MYSQL_GET_OPTION4(AND o.scope_id = 0 AND o.code = ? AND o.space = ?)
    },

    // Retrieves all global options.
    { MySqlConfigBackendDHCPv4Impl::GET_ALL_OPTIONS4,
      MYSQL_GET_OPTION4(AND o.scope_id = 0)
    },

    // Retrieves modified options.
    { MySqlConfigBackendDHCPv4Impl::GET_MODIFIED_OPTIONS4,
      MYSQL_GET_OPTION4(AND o.scope_id = 0 AND o.modification_ts > ?)
    },

    // Retrieves an option for a given subnet, option code and space.
    { MySqlConfigBackendDHCPv4Impl::GET_OPTION4_SUBNET_ID_CODE_SPACE,
      MYSQL_GET_OPTION4(AND o.scope_id = 1 AND o.dhcp4_subnet_id = ? AND o.code = ? AND o.space = ?)
    },

    // Retrieves an option for a given pool, option code and space.
    { MySqlConfigBackendDHCPv4Impl::GET_OPTION4_POOL_ID_CODE_SPACE,
      MYSQL_GET_OPTION4(AND o.scope_id = 5 AND o.pool_id = ? AND o.code = ? AND o.space = ?)
    },

    // Retrieves an option for a given shared network, option code and space.
    { MySqlConfigBackendDHCPv4Impl::GET_OPTION4_SHARED_NETWORK_CODE_SPACE,
      MYSQL_GET_OPTION4(AND o.scope_id = 4 AND o.shared_network_name = ? AND o.code = ? AND o.space = ?)
    },

    // Retrieves the most recent audit entries.
    { MySqlConfigBackendDHCPv4Impl::GET_AUDIT_ENTRIES4_TIME,
      MYSQL_GET_AUDIT_ENTRIES_TIME(dhcp4)
    },

    // Insert global parameter.
    { MySqlConfigBackendDHCPv4Impl::INSERT_GLOBAL_PARAMETER4,
      MYSQL_INSERT_GLOBAL_PARAMETER(dhcp4)
    },

    // Insert association of the global parameter with a server.
    { MySqlConfigBackendDHCPv4Impl::INSERT_GLOBAL_PARAMETER4_SERVER,
      MYSQL_INSERT_GLOBAL_PARAMETER_SERVER(dhcp4)
    },

    // Insert a subnet.
    { MySqlConfigBackendDHCPv4Impl::INSERT_SUBNET4,
      "INSERT INTO dhcp4_subnet("
      "  subnet_id,"
      "  subnet_prefix,"
      "  4o6_interface,"
      "  4o6_interface_id,"
      "  4o6_subnet,"
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
      "  reservation_mode,"
      "  server_hostname,"
      "  shared_network_name,"
      "  user_context,"
      "  valid_lifetime,"
      "  calculate_tee_times,"
      "  t1_percent,"
      "  t2_percent,"
      "  authoritative"
      ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
      "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)" },

    // Insert association of the subnet with a server.
    { MySqlConfigBackendDHCPv4Impl::INSERT_SUBNET4_SERVER,
      MYSQL_INSERT_SUBNET_SERVER(dhcp4)
    },

    // Insert pool for a subnet.
    { MySqlConfigBackendDHCPv4Impl::INSERT_POOL4,
      MYSQL_INSERT_POOL(dhcp4)
    },

    // Insert a shared network.
    { MySqlConfigBackendDHCPv4Impl::INSERT_SHARED_NETWORK4,
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
      "  reservation_mode,"
      "  user_context,"
      "  valid_lifetime,"
      "  calculate_tee_times,"
      "  t1_percent,"
      "  t2_percent,"
      "  authoritative,"
      "  boot_file_name,"
      "  next_server,"
      "  server_hostname"
      ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)" },

    // Insert association of the shared network with a server.
    { MySqlConfigBackendDHCPv4Impl::INSERT_SHARED_NETWORK4_SERVER,
      MYSQL_INSERT_SHARED_NETWORK_SERVER(dhcp4)
    },

    // Insert option definition.
    { MySqlConfigBackendDHCPv4Impl::INSERT_OPTION_DEF4,
      MYSQL_INSERT_OPTION_DEF(dhcp4)
    },

    // Insert association of the option definition with a server.
    { MySqlConfigBackendDHCPv4Impl::INSERT_OPTION_DEF4_SERVER,
      MYSQL_INSERT_OPTION_DEF_SERVER(dhcp4)
    },

    // Insert subnet specific option.
    { MySqlConfigBackendDHCPv4Impl::INSERT_OPTION4,
      MYSQL_INSERT_OPTION4()
    },

    // Insert association of the DHCP option with a server.
    { MySqlConfigBackendDHCPv4Impl::INSERT_OPTION4_SERVER,
      MYSQL_INSERT_OPTION_SERVER(dhcp4)
    },

    // Update existing global parameter.
    { MySqlConfigBackendDHCPv4Impl::UPDATE_GLOBAL_PARAMETER4,
      MYSQL_UPDATE_GLOBAL_PARAMETER(dhcp4)
    },

    // Update existing subnet.
    { MySqlConfigBackendDHCPv4Impl::UPDATE_SUBNET4,
      "UPDATE dhcp4_subnet SET"
      "  subnet_id = ?,"
      "  subnet_prefix = ?,"
      "  4o6_interface = ?,"
      "  4o6_interface_id = ?,"
      "  4o6_subnet = ?,"
      "  boot_file_name = ?,"
      "  client_class = ?,"
      "  interface = ?,"
      "  match_client_id = ?,"
      "  modification_ts = ?,"
      "  next_server = ?,"
      "  rebind_timer = ?,"
      "  relay = ?,"
      "  renew_timer = ?,"
      "  require_client_classes = ?,"
      "  reservation_mode = ?,"
      "  server_hostname = ?,"
      "  shared_network_name = ?,"
      "  user_context = ?,"
      "  valid_lifetime = ?,"
      "  calculate_tee_times = ?,"
      "  t1_percent = ?,"
      "  t2_percent = ?,"
      "  authoritative = ? "
      "WHERE subnet_id = ? OR subnet_prefix = ?" },

    // Update existing shared network.
    { MySqlConfigBackendDHCPv4Impl::UPDATE_SHARED_NETWORK4,
      "UPDATE dhcp4_shared_network SET"
      "  name = ?,"
      "  client_class = ?,"
      "  interface = ?,"
      "  match_client_id = ?,"
      "  modification_ts = ?,"
      "  rebind_timer = ?,"
      "  relay = ?,"
      "  renew_timer = ?,"
      "  require_client_classes = ?,"
      "  reservation_mode = ?,"
      "  user_context = ?,"
      "  valid_lifetime = ?,"
      "  calculate_tee_times = ?,"
      "  t1_percent = ?,"
      "  t2_percent = ?,"
      "  authoritative = ?,"
      "  boot_file_name = ?,"
      "  next_server = ?,"
      "  server_hostname = ? "
      "WHERE name = ?" },

    // Update existing option definition.
    { MySqlConfigBackendDHCPv4Impl::UPDATE_OPTION_DEF4,
      MYSQL_UPDATE_OPTION_DEF(dhcp4)
    },

    // Update existing global option.
    { MySqlConfigBackendDHCPv4Impl::UPDATE_OPTION4,
      MYSQL_UPDATE_OPTION4(AND o.scope_id = 0 AND o.code = ? AND o.space = ?)
    },

    // Update existing subnet level option.
    { MySqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_SUBNET_ID,
      MYSQL_UPDATE_OPTION4(AND o.scope_id = 1 AND o.dhcp4_subnet_id = ? AND o.code = ? AND o.space = ?)
    },

    // Update existing pool level option.
    { MySqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_POOL_ID,
      MYSQL_UPDATE_OPTION4(AND o.scope_id = 5 AND o.pool_id = ? AND o.code = ? AND o.space = ?)
    },

    // Update existing shared network level option.
    { MySqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_SHARED_NETWORK,
      MYSQL_UPDATE_OPTION4(AND o.scope_id = 4 AND o.shared_network_name = ? AND o.code = ? AND o.space = ?)
    },

    // Delete global parameter by name.
    { MySqlConfigBackendDHCPv4Impl::DELETE_GLOBAL_PARAMETER4,
      MYSQL_DELETE_GLOBAL_PARAMETER(dhcp4, AND g.name = ?)
    },

    // Delete all global parameters.
    { MySqlConfigBackendDHCPv4Impl::DELETE_ALL_GLOBAL_PARAMETERS4,
      MYSQL_DELETE_GLOBAL_PARAMETER(dhcp4)
    },

    // Delete subnet by id.
    { MySqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_ID,
      MYSQL_DELETE_SUBNET(dhcp4, AND s.subnet_id = ?)
    },

    // Delete subnet by prefix.
    { MySqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_PREFIX,
      MYSQL_DELETE_SUBNET(dhcp4, AND s.subnet_prefix = ?)
    },

    // Delete all subnets.
    { MySqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4,
      MYSQL_DELETE_SUBNET(dhcp4)
    },

    // Delete all subnets for a shared network.
    { MySqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4_SHARED_NETWORK_NAME,
      MYSQL_DELETE_SUBNET(dhcp4, AND s.shared_network_name = ?)
    },

    // Delete pools for a subnet.
    { MySqlConfigBackendDHCPv4Impl::DELETE_POOLS4_SUBNET_ID,
      MYSQL_DELETE_POOLS(dhcp4)
    },

    // Delete shared network by name.
    { MySqlConfigBackendDHCPv4Impl::DELETE_SHARED_NETWORK4_NAME,
      MYSQL_DELETE_SHARED_NETWORK(dhcp4, AND n.name = ?)
    },

    // Delete all shared networks.
    { MySqlConfigBackendDHCPv4Impl::DELETE_ALL_SHARED_NETWORKS4,
      MYSQL_DELETE_SHARED_NETWORK(dhcp4)
    },

    // Delete option definition.
    { MySqlConfigBackendDHCPv4Impl::DELETE_OPTION_DEF4_CODE_NAME,
      MYSQL_DELETE_OPTION_DEF(dhcp4, AND code = ? AND space = ?)
    },

    // Delete all option definitions.
    { MySqlConfigBackendDHCPv4Impl::DELETE_ALL_OPTION_DEFS4,
      MYSQL_DELETE_OPTION_DEF(dhcp4)
    },

    // Delete single global option.
    { MySqlConfigBackendDHCPv4Impl::DELETE_OPTION4,
      MYSQL_DELETE_OPTION(dhcp4, AND o.scope_id = 0  AND o.code = ? AND o.space = ?)
    },

    // Delete single option from a subnet.
    { MySqlConfigBackendDHCPv4Impl::DELETE_OPTION4_SUBNET_ID,
      MYSQL_DELETE_OPTION(dhcp4,
                          AND o.scope_id = 1 AND o.dhcp4_subnet_id = ? AND o.code = ? AND o.space = ?)
    },

    // Delete single option from a pool.
    { MySqlConfigBackendDHCPv4Impl::DELETE_OPTION4_POOL_RANGE,
      MYSQL_DELETE_OPTION_POOL_RANGE(dhcp4, AND o.scope_id = 5 AND o.code = ? AND o.space = ?)
    },

    // Delete single option from a shared network.
    { MySqlConfigBackendDHCPv4Impl::DELETE_OPTION4_SHARED_NETWORK,
      MYSQL_DELETE_OPTION(dhcp4,
                          AND o.scope_id = 4 AND o.shared_network_name = ? AND o.code = ? AND o.space = ?)
    },

    // Delete options belonging to a subnet.
    { MySqlConfigBackendDHCPv4Impl::DELETE_OPTIONS4_SUBNET_ID,
      MYSQL_DELETE_OPTION(dhcp4, AND o.scope_id = 1 AND o.dhcp4_subnet_id = ?)
    },

    // Delete options belonging to a shared_network.
    { MySqlConfigBackendDHCPv4Impl::DELETE_OPTIONS4_SHARED_NETWORK,
      MYSQL_DELETE_OPTION(dhcp4, AND o.scope_id = 4 AND o.shared_network_name = ?)
    }
}
};

}; // end anonymous namespace

MySqlConfigBackendDHCPv4Impl::
MySqlConfigBackendDHCPv4Impl(const DatabaseConnection::ParameterMap& parameters)
    : MySqlConfigBackendImpl(parameters) {
    // Prepare query statements. Those are will be only used to retrieve
    // information from the database, so they can be used even if the
    // database is read only for the current user.
    conn_.prepareStatements(tagged_statements.begin(),
                            tagged_statements.end());
//                            tagged_statements.begin() + WRITE_STMTS_BEGIN);
}

MySqlConfigBackendDHCPv4::
MySqlConfigBackendDHCPv4(const DatabaseConnection::ParameterMap& parameters)
    : impl_(new MySqlConfigBackendDHCPv4Impl(parameters)) {
}

Subnet4Ptr
MySqlConfigBackendDHCPv4::getSubnet4(const ServerSelector& server_selector,
                                     const std::string& subnet_prefix) const {
    return (impl_->getSubnet4(server_selector, subnet_prefix));
}

Subnet4Ptr
MySqlConfigBackendDHCPv4::getSubnet4(const ServerSelector& server_selector,
                                     const SubnetID& subnet_id) const {
    return (impl_->getSubnet4(server_selector, subnet_id));
}

Subnet4Collection
MySqlConfigBackendDHCPv4::getAllSubnets4(const ServerSelector& server_selector) const {
    Subnet4Collection subnets;
    impl_->getAllSubnets4(server_selector, subnets);
    return (subnets);
}

Subnet4Collection
MySqlConfigBackendDHCPv4::getModifiedSubnets4(const ServerSelector& server_selector,
                                              const boost::posix_time::ptime& modification_time) const {
    Subnet4Collection subnets;
    impl_->getModifiedSubnets4(server_selector, modification_time, subnets);
    return (subnets);
}

Subnet4Collection
MySqlConfigBackendDHCPv4::getSharedNetworkSubnets4(const ServerSelector& server_selector,
                                                   const std::string& shared_network_name) const {
    Subnet4Collection subnets;
    impl_->getSharedNetworkSubnets4(server_selector, shared_network_name, subnets);
    return (subnets);
}

SharedNetwork4Ptr
MySqlConfigBackendDHCPv4::getSharedNetwork4(const ServerSelector& server_selector,
                                            const std::string& name) const {
    return (impl_->getSharedNetwork4(server_selector, name));
}

SharedNetwork4Collection
MySqlConfigBackendDHCPv4::getAllSharedNetworks4(const ServerSelector& server_selector) const {
    SharedNetwork4Collection shared_networks;
    impl_->getAllSharedNetworks4(server_selector, shared_networks);
    return (shared_networks);
}

SharedNetwork4Collection
MySqlConfigBackendDHCPv4::
getModifiedSharedNetworks4(const ServerSelector& server_selector,
                           const boost::posix_time::ptime& modification_time) const {
    SharedNetwork4Collection shared_networks;
    impl_->getModifiedSharedNetworks4(server_selector, modification_time, shared_networks);
    return (shared_networks);
}

OptionDefinitionPtr
MySqlConfigBackendDHCPv4::getOptionDef4(const ServerSelector& server_selector,
                                        const uint16_t code,
                                        const std::string& space) const {
    return (impl_->getOptionDef(MySqlConfigBackendDHCPv4Impl::GET_OPTION_DEF4_CODE_SPACE,
                                server_selector, code, space));
}

OptionDefContainer
MySqlConfigBackendDHCPv4::getAllOptionDefs4(const ServerSelector& server_selector) const {
    OptionDefContainer option_defs;
    impl_->getAllOptionDefs(MySqlConfigBackendDHCPv4Impl::GET_ALL_OPTION_DEFS4,
                            server_selector, option_defs);
    return (option_defs);
}

OptionDefContainer
MySqlConfigBackendDHCPv4::
getModifiedOptionDefs4(const ServerSelector& server_selector,
                       const boost::posix_time::ptime& modification_time) const {
    OptionDefContainer option_defs;
    impl_->getModifiedOptionDefs(MySqlConfigBackendDHCPv4Impl::GET_MODIFIED_OPTION_DEFS4,
                                 server_selector, modification_time, option_defs);
    return (option_defs);
}

OptionDescriptorPtr
MySqlConfigBackendDHCPv4::getOption4(const ServerSelector& server_selector,
                                     const uint16_t code,
                                     const std::string& space) const {
    return (impl_->getOption(MySqlConfigBackendDHCPv4Impl::GET_OPTION4_CODE_SPACE,
                             Option::V4, server_selector, code, space));
}

OptionContainer
MySqlConfigBackendDHCPv4::getAllOptions4(const ServerSelector& server_selector) const {
    return (impl_->getAllOptions(MySqlConfigBackendDHCPv4Impl::GET_ALL_OPTIONS4,
                                 Option::V4, server_selector));
}

OptionContainer
MySqlConfigBackendDHCPv4::
getModifiedOptions4(const ServerSelector& server_selector,
                    const boost::posix_time::ptime& modification_time) const {
    return (impl_->getModifiedOptions(MySqlConfigBackendDHCPv4Impl::GET_MODIFIED_OPTIONS4,
                                      Option::V4, server_selector, modification_time));
}

StampedValuePtr
MySqlConfigBackendDHCPv4::getGlobalParameter4(const ServerSelector& server_selector,
                                              const std::string& name) const {
    return (impl_->getGlobalParameter4(server_selector, name));
}

StampedValueCollection
MySqlConfigBackendDHCPv4::getAllGlobalParameters4(const ServerSelector& server_selector) const {
    StampedValueCollection parameters;

    auto tags = impl_->getServerTags(server_selector);
    for (auto tag : tags) {
        MySqlBindingCollection in_bindings = { MySqlBinding::createString(tag) };
        impl_->getGlobalParameters(MySqlConfigBackendDHCPv4Impl::GET_ALL_GLOBAL_PARAMETERS4,
                                   in_bindings, parameters);
    }
    return (parameters);
}

StampedValueCollection
MySqlConfigBackendDHCPv4::
getModifiedGlobalParameters4(const db::ServerSelector& server_selector,
                             const boost::posix_time::ptime& modification_time) const {
    StampedValueCollection parameters;

    auto tags = impl_->getServerTags(server_selector);
    for (auto tag : tags) {
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(tag),
            MySqlBinding::createTimestamp(modification_time)
        };
        impl_->getGlobalParameters(MySqlConfigBackendDHCPv4Impl::GET_MODIFIED_GLOBAL_PARAMETERS4,
                                   in_bindings, parameters);
    }

    return (parameters);
}

AuditEntryCollection
MySqlConfigBackendDHCPv4::
getRecentAuditEntries(const db::ServerSelector& server_selector,
                      const boost::posix_time::ptime& modification_time) const {
    AuditEntryCollection audit_entries;
    impl_->getRecentAuditEntries(MySqlConfigBackendDHCPv4Impl::GET_AUDIT_ENTRIES4_TIME,
                                 server_selector, modification_time, audit_entries);

    return (audit_entries);
}

void
MySqlConfigBackendDHCPv4::createUpdateSubnet4(const ServerSelector& server_selector,
                                              const Subnet4Ptr& subnet) {
    impl_->createUpdateSubnet4(server_selector, subnet);
}

void
MySqlConfigBackendDHCPv4::createUpdateSharedNetwork4(const ServerSelector& server_selector,
                                                     const SharedNetwork4Ptr& shared_network) {
    impl_->createUpdateSharedNetwork4(server_selector, shared_network);
}

void
MySqlConfigBackendDHCPv4::createUpdateOptionDef4(const ServerSelector& server_selector,
                                                 const OptionDefinitionPtr& option_def) {
    impl_->createUpdateOptionDef4(server_selector, option_def);
}

void
MySqlConfigBackendDHCPv4::createUpdateOption4(const ServerSelector& server_selector,
                                              const OptionDescriptorPtr& option) {
    impl_->createUpdateOption4(server_selector, option);
}

void
MySqlConfigBackendDHCPv4::createUpdateOption4(const db::ServerSelector& server_selector,
                                              const std::string& shared_network_name,
                                              const OptionDescriptorPtr& option) {
    impl_->createUpdateOption4(server_selector, shared_network_name, option, false);
}

void
MySqlConfigBackendDHCPv4::createUpdateOption4(const ServerSelector& server_selector,
                                              const SubnetID& subnet_id,
                                              const OptionDescriptorPtr& option) {
    impl_->createUpdateOption4(server_selector, subnet_id, option, false);
}

void
MySqlConfigBackendDHCPv4::createUpdateOption4(const ServerSelector& server_selector,
                                              const asiolink::IOAddress& pool_start_address,
                                              const asiolink::IOAddress& pool_end_address,
                                              const OptionDescriptorPtr& option) {
    impl_->createUpdateOption4(server_selector, pool_start_address, pool_end_address,
                               option);
}

void
MySqlConfigBackendDHCPv4::createUpdateGlobalParameter4(const ServerSelector& server_selector,
                                                       const StampedValuePtr& value) {
    impl_->createUpdateGlobalParameter4(server_selector, value);
}

uint64_t
MySqlConfigBackendDHCPv4::deleteSubnet4(const ServerSelector& server_selector,
                                        const std::string& subnet_prefix) {
    return(impl_->deleteTransactional(MySqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_PREFIX,
                                      server_selector, "deleting a subnet by prefix",
                                      "subnet deleted", true,
                                      subnet_prefix));
}

uint64_t
MySqlConfigBackendDHCPv4::deleteSubnet4(const ServerSelector& server_selector,
                                        const SubnetID& subnet_id) {
    return (impl_->deleteSubnet4(server_selector, subnet_id));
}

uint64_t
MySqlConfigBackendDHCPv4::deleteAllSubnets4(const ServerSelector& server_selector) {
    return (impl_->deleteTransactional(MySqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4,
                                       server_selector, "deleting all subnets",
                                       "deleted all subnets", true));
}

uint64_t
MySqlConfigBackendDHCPv4::deleteSharedNetworkSubnets4(const db::ServerSelector& server_selector,
                                                      const std::string& shared_network_name) {
    return (impl_->deleteTransactional(MySqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4_SHARED_NETWORK_NAME,
                                       server_selector,
                                       "deleting all subnets for a shared network",
                                       "deleted all subnets for a shared network",
                                       true, shared_network_name));
}

uint64_t
MySqlConfigBackendDHCPv4::deleteSharedNetwork4(const ServerSelector& server_selector,
                                               const std::string& name) {
    return (impl_->deleteTransactional(MySqlConfigBackendDHCPv4Impl::DELETE_SHARED_NETWORK4_NAME,
                                       server_selector, "deleting a shared network",
                                       "shared network deleted", true,
                                       name));
}

uint64_t
MySqlConfigBackendDHCPv4::deleteAllSharedNetworks4(const ServerSelector& server_selector) {
    return (impl_->deleteTransactional(MySqlConfigBackendDHCPv4Impl::DELETE_ALL_SHARED_NETWORKS4,
                                       server_selector, "deleting all shared networks",
                                       "deleted all shared networks", true));
}

uint64_t
MySqlConfigBackendDHCPv4::deleteOptionDef4(const ServerSelector& server_selector,
                                           const uint16_t code,
                                           const std::string& space) {
    return (impl_->deleteOptionDef4(server_selector, code, space));
}

uint64_t
MySqlConfigBackendDHCPv4::deleteAllOptionDefs4(const ServerSelector& server_selector) {
    return (impl_->deleteTransactional(MySqlConfigBackendDHCPv4Impl::DELETE_ALL_OPTION_DEFS4,
                                       server_selector, "deleting all option definitions",
                                       "deleted all option definitions", true));
}

uint64_t
MySqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& server_selector,
                                        const uint16_t code,
                                        const std::string& space) {
    return (impl_->deleteOption4(server_selector, code, space));
}

uint64_t
MySqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& server_selector,
                                        const std::string& shared_network_name,
                                        const uint16_t code,
                                        const std::string& space) {
    return (impl_->deleteOption4(server_selector, shared_network_name,
                                 code, space));
}

uint64_t
MySqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& server_selector,
                                        const SubnetID& subnet_id,
                                        const uint16_t code,
                                        const std::string& space) {
    return (impl_->deleteOption4(server_selector, subnet_id, code, space));
}

uint64_t
MySqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& server_selector,
                                        const asiolink::IOAddress& pool_start_address,
                                        const asiolink::IOAddress& pool_end_address,
                                        const uint16_t code,
                                        const std::string& space) {
    return (impl_->deleteOption4(server_selector, pool_start_address, pool_end_address,
                                 code, space));
}

uint64_t
MySqlConfigBackendDHCPv4::deleteGlobalParameter4(const ServerSelector& server_selector,
                                                 const std::string& name) {
    return (impl_->deleteTransactional(MySqlConfigBackendDHCPv4Impl::DELETE_GLOBAL_PARAMETER4,
                                       server_selector, "deleting global parameter",
                                       "global parameter deleted", false,
                                       name));
}

uint64_t
MySqlConfigBackendDHCPv4::deleteAllGlobalParameters4(const ServerSelector& server_selector) {
    return (impl_->deleteTransactional(MySqlConfigBackendDHCPv4Impl::DELETE_ALL_GLOBAL_PARAMETERS4,
                                       server_selector, "deleting all global parameters",
                                       "all global parameters deleted", true));
}

std::string
MySqlConfigBackendDHCPv4::getType() const {
    return (impl_->getType());
}

std::string
MySqlConfigBackendDHCPv4::getHost() const {
    return (impl_->getHost());
}

uint16_t
MySqlConfigBackendDHCPv4::getPort() const {
    return (impl_->getPort());
}

bool
MySqlConfigBackendDHCPv4::registerBackendType() {
    return (
        dhcp::ConfigBackendDHCPv4Mgr::instance().registerBackendFactory("mysql",
            [](const db::DatabaseConnection::ParameterMap& params) -> dhcp::ConfigBackendDHCPv4Ptr {
            return (dhcp::MySqlConfigBackendDHCPv4Ptr(new dhcp::MySqlConfigBackendDHCPv4(params)));
        })
    );
}

void
MySqlConfigBackendDHCPv4::unregisterBackendType() {
    dhcp::ConfigBackendDHCPv4Mgr::instance().unregisterBackendFactory("mysql");
}

} // end of namespace isc::dhcp
} // end of namespace isc
