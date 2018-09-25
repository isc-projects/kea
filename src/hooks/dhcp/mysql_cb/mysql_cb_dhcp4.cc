// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/data.h>
#include <database/db_exceptions.h>
#include <dhcp/classify.h>
#include <dhcp/dhcp6.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/lease.h>
#include <mysql_cb_dhcp4.h>
#include <mysql/mysql_connection.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/pointer_cast.hpp>
#include <mysql.h>
#include <mysqld_error.h>
#include <array>
#include <sstream>
#include <utility>
#include <vector>

using namespace isc::db;
using namespace isc::data;
using namespace isc::asiolink;

namespace isc {
namespace dhcp {

/// @brief Implementation of the MySQL Configuration Backend.
class MySqlConfigBackendDHCPv4Impl {
public:

    /// @brief Statement tags.
    ///
    /// The contents of the enum are indexes into the list of SQL statements.
    /// It is assumed that the order is such that the indices of statements
    /// reading the database are less than those of statements modifying the
    /// database.
    enum StatementIndex {
        GET_SUBNET4_ID,
        GET_SUBNET4_PREFIX,
        GET_ALL_SUBNETS4,
        GET_MODIFIED_SUBNETS4,
        INSERT_SUBNET4,
        INSERT_POOL4,
        UPDATE_SUBNET4,
        DELETE_POOLS4_SUBNET_ID,
        NUM_STATEMENTS
    };

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    MySqlConfigBackendDHCPv4Impl(const DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor.
    ~MySqlConfigBackendDHCPv4Impl();

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
            MySqlBinding::createString(32), // subnet_prefix
            MySqlBinding::createString(128), // 4o6_interface
            MySqlBinding::createString(128), // 4o6_interface_id
            MySqlBinding::createString(64), // 4o6_subnet
            MySqlBinding::createString(512), // boot_file_name
            MySqlBinding::createString(128), // client_class
            MySqlBinding::createString(128), // interface
            MySqlBinding::createInteger<uint8_t>(), // match_client_id
            MySqlBinding::createTimestamp(), // modification_ts
            MySqlBinding::createInteger<uint32_t>(), // next_server
            MySqlBinding::createInteger<uint32_t>(), // rebind_timer
            MySqlBinding::createString(65536), // relay
            MySqlBinding::createInteger<uint32_t>(), // renew_timer
            MySqlBinding::createString(65536), // require_client_classes
            MySqlBinding::createInteger<uint8_t>(), // reservation_mode
            MySqlBinding::createString(512), // server_hostname
            MySqlBinding::createString(128), // shared_network_name
            MySqlBinding::createString(65536), // user_context
            MySqlBinding::createInteger<uint32_t>(), // valid_lifetime
            MySqlBinding::createInteger<uint64_t>(), // pool: id
            MySqlBinding::createInteger<uint32_t>(), // pool: start_address
            MySqlBinding::createInteger<uint32_t>(), // pool: end_address
            MySqlBinding::createInteger<uint32_t>(), // pool: subnet_id
            MySqlBinding::createTimestamp() // pool: modification_ts
        };

        uint64_t last_pool_id = 0;

        // Execute actual query.
        conn_.selectQuery(index, in_bindings, out_bindings,
                          [&subnets, &last_pool_id]
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
                uint32_t renew_timer = out_bindings[13]->getIntegerOrDefault<uint32_t>(0);
                // rebind_timer
                uint32_t rebind_timer = out_bindings[11]->getIntegerOrDefault<uint32_t>(0);
                // valid_lifetime
                uint32_t valid_lifetime = out_bindings[19]->getIntegerOrDefault<uint32_t>(0);

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
                last_subnet->setFilename(out_bindings[5]->getStringOrDefault(""));
                // client_class
                if (!out_bindings[6]->amNull()) {
                    last_subnet->allowClientClass(out_bindings[6]->getString());
                }
                // interface
                last_subnet->setIface(out_bindings[7]->getStringOrDefault(""));
                // match_client_id
                last_subnet->setMatchClientId(static_cast<bool>
                                              (out_bindings[8]->getIntegerOrDefault<uint8_t>(1)));
                // next_server
                last_subnet->setSiaddr(IOAddress(out_bindings[10]->getIntegerOrDefault<uint32_t>(0)));
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
                last_subnet->setHostReservationMode(static_cast<Subnet4::HRMode>
                    (out_bindings[15]->getIntegerOrDefault<uint8_t>(Subnet4::HR_ALL)));
                // server_hostname
                last_subnet->setSname(out_bindings[16]->getStringOrDefault(""));
                // user_context
                ElementPtr user_context = out_bindings[18]->getJSON();
                if (user_context) {
                    last_subnet->setContext(user_context);
                }

                // Subnet ready. Add it to the list.
                subnets.push_back(last_subnet);
            }

            if (!out_bindings[20]->amNull() &&
                (out_bindings[21]->getInteger<uint32_t>() != 0) &&
                (out_bindings[22]->getInteger<uint32_t>() != 0) &&
                ((last_pool_id == 0) ||
                 (out_bindings[20]->getInteger<uint64_t>() != last_pool_id))) {
                last_pool_id = out_bindings[20]->getInteger<uint64_t>();
                Pool4Ptr pool(new Pool4(IOAddress(out_bindings[21]->getInteger<uint32_t>()),
                                        IOAddress(out_bindings[22]->getInteger<uint32_t>())));
                last_subnet->addPool(pool);
            }
        });
    }

    /// @brief Sends query to retrieve single subnet by id.
    ///
    /// @param selector Server selector.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Pointer to the returned subnet or NULL if such subnet
    /// doesn't exist.
    Subnet4Ptr getSubnet4(const ServerSelector& selector,
                          const SubnetID& subnet_id) {
        MySqlBindingCollection in_bindings;
        in_bindings.push_back(MySqlBinding::createInteger<uint32_t>(subnet_id));

        Subnet4Collection subnets;
        getSubnets4(GET_SUBNET4_ID, in_bindings, subnets);

        return (subnets.empty() ? Subnet4Ptr() : *subnets.begin());
    }

    /// @brief Sends query to retrieve single subnet by prefix.
    ///
    /// The prefix should be in the following format: "192.0.2.0/24".
    ///
    /// @param selector Server selector.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Pointer to the returned subnet or NULL if such subnet
    /// doesn't exist.
    Subnet4Ptr getSubnet4(const ServerSelector& selector,
                          const std::string& subnet_prefix) {
        MySqlBindingCollection in_bindings;
        in_bindings.push_back(MySqlBinding::createString(subnet_prefix));

        Subnet4Collection subnets;
        getSubnets4(GET_SUBNET4_PREFIX, in_bindings, subnets);

        return (subnets.empty() ? Subnet4Ptr() : *subnets.begin());
    }

    /// @brief Sends query to insert or update subnet.
    ///
    /// @param selector Server selector.
    /// @param subnet Pointer to the subnet to be inserted or updated.
    void createUpdateSubnet4(const ServerSelector& selector,
                             const Subnet4Ptr& subnet) {
        // Convert DHCPv4o6 interface id to text.
        OptionPtr dhcp4o6_interface_id = subnet->get4o6().getInterfaceId();
        std::string dhcp4o6_interface_id_text;
        if (dhcp4o6_interface_id) {
            dhcp4o6_interface_id_text.assign(dhcp4o6_interface_id->getData().begin(),
                                             dhcp4o6_interface_id->getData().end());
        }

        // Convert DHCPv4o6 subnet to text.
        std::string dhcp4o6_subnet;
        if (!subnet->get4o6().getSubnet4o6().first.isV6Zero() ||
            (subnet->get4o6().getSubnet4o6().second != 128u)) {
            std::ostringstream s;
            s << subnet->get4o6().getSubnet4o6().first << "/"
              << static_cast<int>(subnet->get4o6().getSubnet4o6().second);
            dhcp4o6_subnet = s.str();
        }

        // Create JSON list of relay addresses.
        ElementPtr relay_element = Element::createList();
        const auto& addresses = subnet->getRelayAddresses();
        if (!addresses.empty()) {
            for (const auto& address : addresses) {
                relay_element->add(Element::create(address.toText()));
            }
        }

        // Create JSON list of required classes.
        ElementPtr required_classes_element = Element::createList();
        const auto& required_classes = subnet->getRequiredClasses();
        for (auto required_class = required_classes.cbegin();
             required_class != required_classes.cend();
             ++required_class) {
            required_classes_element->add(Element::create(*required_class));
        }

        // Create binding with shared network name if the subnet belongs to a
        // shared network.
        SharedNetwork4Ptr shared_network;
        subnet->getSharedNetwork(shared_network);
        MySqlBindingPtr shared_network_binding =
            (shared_network ? MySqlBinding::createString(shared_network->getName()) :
             MySqlBinding::createNull());

        // Create user context binding if user context exists.
        auto context_element = subnet->getContext();
        MySqlBindingPtr context_binding =
            (context_element ? MySqlBinding::createString(context_element->str()) :
             MySqlBinding::createNull());

        // Create input bindings.
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint32_t>(subnet->getID()),
            MySqlBinding::createString(subnet->toText()),
            MySqlBinding::condCreateString(subnet->get4o6().getIface4o6()),
            MySqlBinding::condCreateString(dhcp4o6_interface_id_text),
            MySqlBinding::condCreateString(dhcp4o6_subnet),
            MySqlBinding::condCreateString(subnet->getFilename()),
            MySqlBinding::condCreateString(subnet->getClientClass()),
            MySqlBinding::condCreateString(subnet->getIface()),
            MySqlBinding::createInteger<uint8_t>(static_cast<uint8_t>(subnet->getMatchClientId())),
            MySqlBinding::createTimestamp(subnet->getModificationTime()),
            MySqlBinding::condCreateInteger<uint32_t>(subnet->getSiaddr().toUint32()),
            MySqlBinding::createInteger<uint32_t>(subnet->getT2()),
            MySqlBinding::condCreateString(relay_element->str()),
            MySqlBinding::createInteger<uint32_t>(subnet->getT1()),
            MySqlBinding::condCreateString(required_classes_element->str()),
            MySqlBinding::createInteger<uint8_t>(static_cast<uint8_t>(subnet->getHostReservationMode())),
            MySqlBinding::condCreateString(subnet->getSname()),
            shared_network_binding,
            context_binding,
            MySqlBinding::createInteger<uint32_t>(subnet->getValid())
        };

        // Check if the subnet already exists.
        Subnet4Ptr existing_subnet = getSubnet4(selector, subnet->getID());

        // If the subnet exists we are going to update this subnet.
        if (existing_subnet) {
            // Delete existing pools in case the updated subnet contains different
            // set of pools.
            deletePools4(existing_subnet);

            // Need to add one more binding for WHERE clause.
            in_bindings.push_back(MySqlBinding::createInteger<uint32_t>(existing_subnet->getID()));
            conn_.updateDeleteQuery(MySqlConfigBackendDHCPv4Impl::UPDATE_SUBNET4,
                                    in_bindings);

        } else {
            // If the subnet doesn't exist, let's insert it.
            conn_.insertQuery(MySqlConfigBackendDHCPv4Impl::INSERT_SUBNET4,
                              in_bindings);
        }

        // (Re)create pools.
        for (auto pool : subnet->getPools(Lease::TYPE_V4)) {
            createPool4(boost::dynamic_pointer_cast<Pool4>(pool), subnet);
        }
    }

    /// @brief Inserts new IPv4 pool to the database.
    ///
    /// @param pool Pointer to the pool to be inserted.
    /// @param subnet Pointer to the subnet that this pool belongs to.
    void createPool4(const Pool4Ptr& pool, const Subnet4Ptr& subnet) {
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint32_t>(pool->getFirstAddress().toUint32()),
            MySqlBinding::createInteger<uint32_t>(pool->getLastAddress().toUint32()),
            MySqlBinding::createInteger<uint32_t>(static_cast<uint32_t>(subnet->getID())),
            MySqlBinding::createTimestamp(subnet->getModificationTime())
        };

        // Run INSERT.
        conn_.insertQuery(INSERT_POOL4, in_bindings);
    }

    /// @brief Deletes pools belonging to a subnet from the database.
    ///
    /// @param subnet Pointer to the subnet for which pools should be
    /// deleted.
    void deletePools4(const Subnet4Ptr& subnet) {
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createInteger<uint32_t>(subnet->getID())
        };

        // Run DELETE.
        conn_.updateDeleteQuery(DELETE_POOLS4_SUBNET_ID, in_bindings);
    }

    /// @brief Represents connection to the MySQL database.
    MySqlConnection conn_;
};

/// @brief Array of tagged statements.
typedef std::array<TaggedStatement, MySqlConfigBackendDHCPv4Impl::NUM_STATEMENTS>
TaggedStatementArray;

/// @brief Prepared MySQL statements used by the backend to insert and
/// retrieve data from the database.
TaggedStatementArray tagged_statements = { {
    // Select subnet by id.
    { MySqlConfigBackendDHCPv4Impl::GET_SUBNET4_ID,
      "SELECT"
      "  s.subnet_id,"
      "  s.subnet_prefix,"
      "  s.4o6_interface,"
      "  s.4o6_interface_id,"
      "  s.4o6_subnet,"
      "  s.boot_file_name,"
      "  s.client_class,"
      "  s.interface,"
      "  s.match_client_id,"
      "  s.modification_ts,"
      "  s.next_server,"
      "  s.rebind_timer,"
      "  s.relay,"
      "  s.renew_timer,"
      "  s.require_client_classes,"
      "  s.reservation_mode,"
      "  s.server_hostname,"
      "  s.shared_network_name,"
      "  s.user_context,"
      "  s.valid_lifetime,"
      "  p.id,"
      "  p.start_address,"
      "  p.end_address,"
      "  p.subnet_id,"
      "  p.modification_ts "
      "FROM dhcp4_subnet AS s "
      "LEFT JOIN dhcp4_pool AS p ON s.subnet_id = p.subnet_id "
      "WHERE s.subnet_id = ? "
      "ORDER BY s.subnet_id, p.id" },

    // Select subnet by prefix.
    { MySqlConfigBackendDHCPv4Impl::GET_SUBNET4_PREFIX,
      "SELECT"
      "  s.subnet_id,"
      "  s.subnet_prefix,"
      "  s.4o6_interface,"
      "  s.4o6_interface_id,"
      "  s.4o6_subnet,"
      "  s.boot_file_name,"
      "  s.client_class,"
      "  s.interface,"
      "  s.match_client_id,"
      "  s.modification_ts,"
      "  s.next_server,"
      "  s.rebind_timer,"
      "  s.relay,"
      "  s.renew_timer,"
      "  s.require_client_classes,"
      "  s.reservation_mode,"
      "  s.server_hostname,"
      "  s.shared_network_name,"
      "  s.user_context,"
      "  s.valid_lifetime,"
      "  p.id,"
      "  p.start_address,"
      "  p.end_address,"
      "  p.subnet_id,"
      "  p.modification_ts "
      "FROM dhcp4_subnet AS s "
      "LEFT JOIN dhcp4_pool AS p ON s.subnet_id = p.subnet_id "
      "WHERE s.subnet_prefix = ? "
      "ORDER BY s.subnet_id, p.id" },

    // Select all subnets.
    { MySqlConfigBackendDHCPv4Impl::GET_ALL_SUBNETS4,
      "SELECT"
      "  s.subnet_id,"
      "  s.subnet_prefix,"
      "  s.4o6_interface,"
      "  s.4o6_interface_id,"
      "  s.4o6_subnet,"
      "  s.boot_file_name,"
      "  s.client_class,"
      "  s.interface,"
      "  s.match_client_id,"
      "  s.modification_ts,"
      "  s.next_server,"
      "  s.rebind_timer,"
      "  s.relay,"
      "  s.renew_timer,"
      "  s.require_client_classes,"
      "  s.reservation_mode,"
      "  s.server_hostname,"
      "  s.shared_network_name,"
      "  s.user_context,"
      "  s.valid_lifetime,"
      "  p.id,"
      "  p.start_address,"
      "  p.end_address,"
      "  p.subnet_id,"
      "  p.modification_ts "
      "FROM dhcp4_subnet AS s "
      "LEFT JOIN dhcp4_pool AS p ON s.subnet_id = p.subnet_id "
      "ORDER BY s.subnet_id" },

    // Select subnets having modification time later than X.
    { MySqlConfigBackendDHCPv4Impl::GET_MODIFIED_SUBNETS4,
      "SELECT"
      "  s.subnet_id,"
      "  s.subnet_prefix,"
      "  s.4o6_interface,"
      "  s.4o6_interface_id,"
      "  s.4o6_subnet,"
      "  s.boot_file_name,"
      "  s.client_class,"
      "  s.interface,"
      "  s.match_client_id,"
      "  s.modification_ts,"
      "  s.next_server,"
      "  s.rebind_timer,"
      "  s.relay,"
      "  s.renew_timer,"
      "  s.require_client_classes,"
      "  s.reservation_mode,"
      "  s.server_hostname,"
      "  s.shared_network_name,"
      "  s.user_context,"
      "  s.valid_lifetime,"
      "  p.id,"
      "  p.start_address,"
      "  p.end_address,"
      "  p.subnet_id,"
      "  p.modification_ts "
      "FROM dhcp4_subnet AS s "
      "LEFT JOIN dhcp4_pool AS p ON s.subnet_id = p.subnet_id "
      "WHERE s.modification_ts > ? "
      "ORDER BY s.subnet_id" },

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
      "  valid_lifetime"
      ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
      "?, ?, ?, ?, ?, ?, ?, ?)" },

    { MySqlConfigBackendDHCPv4Impl::INSERT_POOL4,
      "INSERT INTO dhcp4_pool("
      "  start_address,"
      "  end_address,"
      "  subnet_id,"
      "  modification_ts"
      ") VALUES (?, ?, ?, ?)" },

    // Update existing subnet.
    { MySqlConfigBackendDHCPv4Impl::UPDATE_SUBNET4,
      "UPDATE dhcp4_subnet SET "
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
      "  valid_lifetime = ? "
      "WHERE subnet_id = ?" },

    // Delete pools for a subnet.
    { MySqlConfigBackendDHCPv4Impl::DELETE_POOLS4_SUBNET_ID,
      "DELETE FROM dhcp4_pool "
      "WHERE subnet_id = ?" }
}
};

MySqlConfigBackendDHCPv4Impl::
MySqlConfigBackendDHCPv4Impl(const DatabaseConnection::ParameterMap& parameters)
    : conn_(parameters) {
    // Open the database.
    conn_.openDatabase();

    // Test schema version before we try to prepare statements.
    std::pair<uint32_t, uint32_t> code_version(MYSQL_SCHEMA_VERSION_MAJOR,
                                               MYSQL_SCHEMA_VERSION_MINOR);
/*    std::pair<uint32_t, uint32_t> db_version = getVersion();
    if (code_version != db_version) {
        isc_throw(DbOpenError, "MySQL schema version mismatch: need version: "
                  << code_version.first << "." << code_version.second
                  << " found version:  " << db_version.first << "."
                  << db_version.second);
    } */

    // Enable autocommit. In case transaction is explicitly used, this
    // setting will be overwritten for the transaction. However, there are
    // cases when lack of autocommit could cause transactions to hang
    // until commit or rollback is explicitly called. This already
    // caused issues for some unit tests which were unable to cleanup
    // the database after the test because of pending transactions.
    // Use of autocommit will eliminate this problem.
    my_bool result = mysql_autocommit(conn_.mysql_, 1);
    if (result != 0) {
        isc_throw(DbOperationError, mysql_error(conn_.mysql_));
    }

    // Prepare query statements. Those are will be only used to retrieve
    // information from the database, so they can be used even if the
    // database is read only for the current user.
    conn_.prepareStatements(tagged_statements.begin(),
                            tagged_statements.end());
//                            tagged_statements.begin() + WRITE_STMTS_BEGIN);
}

MySqlConfigBackendDHCPv4Impl::~MySqlConfigBackendDHCPv4Impl() {
    // Free up the prepared statements, ignoring errors. (What would we do
    // about them? We're destroying this object and are not really concerned
    // with errors on a database connection that is about to go away.)
    for (int i = 0; i < conn_.statements_.size(); ++i) {
        if (conn_.statements_[i] != NULL) {
            (void) mysql_stmt_close(conn_.statements_[i]);
            conn_.statements_[i] = NULL;
        }
    }
}

MySqlConfigBackendDHCPv4::
MySqlConfigBackendDHCPv4(const DatabaseConnection::ParameterMap& parameters)
    : impl_(new MySqlConfigBackendDHCPv4Impl(parameters)) {
}

Subnet4Ptr
MySqlConfigBackendDHCPv4::getSubnet4(const ServerSelector& selector,
                                     const std::string& subnet_prefix) const {
    return (impl_->getSubnet4(selector, subnet_prefix));
}

Subnet4Ptr
MySqlConfigBackendDHCPv4::getSubnet4(const ServerSelector& selector,
                                     const SubnetID& subnet_id) const {
    return (impl_->getSubnet4(selector, subnet_id));
}

Subnet4Collection
MySqlConfigBackendDHCPv4::getAllSubnets4(const ServerSelector& selector) const {
    Subnet4Collection subnets;
    MySqlBindingCollection in_bindings;
    impl_->getSubnets4(MySqlConfigBackendDHCPv4Impl::GET_ALL_SUBNETS4,
                      in_bindings, subnets);
    return (subnets);
}

Subnet4Collection
MySqlConfigBackendDHCPv4::getModifiedSubnets4(const ServerSelector& selector,
                                              const boost::posix_time::ptime& modification_time) const {
    Subnet4Collection subnets;
    MySqlBindingCollection in_bindings = {
        MySqlBinding::createTimestamp(modification_time)
    };
    impl_->getSubnets4(MySqlConfigBackendDHCPv4Impl::GET_MODIFIED_SUBNETS4,
                       in_bindings, subnets);
    return (subnets);
}

SharedNetwork4Ptr
MySqlConfigBackendDHCPv4::getSharedNetwork4(const ServerSelector& selector,
                                            const std::string& name) const {
    isc_throw(NotImplemented, "not implemented");
}

SharedNetwork4Collection
MySqlConfigBackendDHCPv4::getAllSharedNetworks4(const ServerSelector& selector) const {
    isc_throw(NotImplemented, "not implemented");
}

SharedNetwork4Collection
MySqlConfigBackendDHCPv4::
getModifiedSharedNetworks4(const ServerSelector& selector,
                           const boost::posix_time::ptime& modification_time) const {
    isc_throw(NotImplemented, "not implemented");
}

OptionDefinitionPtr
MySqlConfigBackendDHCPv4::getOptionDef4(const ServerSelector& selector,
                                        const uint16_t code,
                                        const std::string& space) const {
    isc_throw(NotImplemented, "not implemented");
}

OptionDefContainer
MySqlConfigBackendDHCPv4::getAllOptionDefs4(const ServerSelector& selector) const {
    isc_throw(NotImplemented, "not implemented");
}

OptionDefContainer
MySqlConfigBackendDHCPv4::
getModifiedOptionDefs4(const ServerSelector& selector,
                       const boost::posix_time::ptime& modification_time) const {
    isc_throw(NotImplemented, "not implemented");
}

util::OptionalValue<std::string>
MySqlConfigBackendDHCPv4::getGlobalStringParameter4(const ServerSelector& selector,
                                                    const std::string& name) const {
    isc_throw(NotImplemented, "not implemented");
}

util::OptionalValue<int64_t>
MySqlConfigBackendDHCPv4::getGlobalNumberParameter4(const ServerSelector& selector,
                                                    const std::string& name) const {
    isc_throw(NotImplemented, "not implemented");
}

std::map<std::string, std::string>
MySqlConfigBackendDHCPv4::getAllGlobalParameters4(const ServerSelector& selector) const {
    isc_throw(NotImplemented, "not implemented");
}

void
MySqlConfigBackendDHCPv4::createUpdateSubnet4(const ServerSelector& selector,
                                              const Subnet4Ptr& subnet) {
    impl_->createUpdateSubnet4(selector, subnet);
}

void
MySqlConfigBackendDHCPv4::createUpdateSharedNetwork4(const ServerSelector& selector,
                                                     const SharedNetwork4Ptr& shared_network) {
}

void
MySqlConfigBackendDHCPv4::createUpdateOptionDef4(const ServerSelector& selector,
                                                 const OptionDefinitionPtr& option_def) {
}

void
MySqlConfigBackendDHCPv4::createUpdateOption4(const ServerSelector& selector,
                                              const OptionPtr& option) {
}

void
MySqlConfigBackendDHCPv4::createUpdateOption4(const ServerSelector& selector,
                                              const SubnetID& subnet_id,
                                              const OptionPtr& option) {
}

void
MySqlConfigBackendDHCPv4::createUpdateOption4(const ServerSelector& selector,
                                              const asiolink::IOAddress& pool_start_address,
                                              const asiolink::IOAddress& pool_end_address,
                                              const OptionPtr& option) {
}

void
MySqlConfigBackendDHCPv4::createUpdateGlobalParameter4(const ServerSelector& selector,
                                                       const std::string& name,
                                                       const std::string& value) {
}

void
MySqlConfigBackendDHCPv4::createUpdateGlobalParameter4(const ServerSelector& selector,
                                                       const std::string& name,
                                                       const int64_t value) {
}

void
MySqlConfigBackendDHCPv4::deleteSubnet4(const ServerSelector& selector,
                                        const std::string& subnet_prefix) {
}

void
MySqlConfigBackendDHCPv4::deleteSubnet4(const ServerSelector& selector,
                                        const SubnetID& subnet_id) {
}

void
MySqlConfigBackendDHCPv4::deleteAllSubnets4(const ServerSelector& selector) {
}

void
MySqlConfigBackendDHCPv4::deleteSharedNetwork4(const ServerSelector& selector,
                                               const std::string& name) {
}

void
MySqlConfigBackendDHCPv4::deleteAllSharedNetworks4(const ServerSelector& selector) {
}

void
MySqlConfigBackendDHCPv4::deleteOptionDef4(const ServerSelector& selector,
                                           const uint16_t code,
                                           const std::string& space) {
}

void
MySqlConfigBackendDHCPv4::deleteAllOptionDefs4(const ServerSelector& selector) {
}

void
MySqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& selector,
                                        const uint16_t code,
                                        const std::string& space) {
}

void
MySqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& selector,
                                        const SubnetID& subnet_id,
                                        const uint16_t code,
                                        const std::string& space) {
}

void
MySqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& selector,
                                        const asiolink::IOAddress& pool_start_address,
                                        const asiolink::IOAddress& pool_end_address,
                                        const uint16_t code,
                                        const std::string& space) {
}

void
MySqlConfigBackendDHCPv4::deleteGlobalParameter4(const ServerSelector& selector,
                                                 const std::string& name) {
}

void
MySqlConfigBackendDHCPv4::deleteAllGlobalParameters4(const ServerSelector& selector) {
}

std::string
MySqlConfigBackendDHCPv4::getType() const {
    return ("mysql");
}

std::string
MySqlConfigBackendDHCPv4::getHost() const {
    return ("");
}

uint16_t
MySqlConfigBackendDHCPv4::getPort() const {
    return (0);
}

} // end of namespace isc::dhcp
} // end of namespace isc
