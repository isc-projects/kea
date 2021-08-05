// Copyright (C) 2016-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service.h>
#include <database/db_exceptions.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/cfg_db_access.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/pgsql_host_data_source.h>
#include <dhcpsrv/timer_mgr.h>
#include <util/buffer.h>
#include <util/multi_threading_mgr.h>
#include <util/optional.h>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/array.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/static_assert.hpp>

#include <stdint.h>

#include <mutex>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::util;
using namespace isc::data;
using namespace std;

namespace {

/// @brief Maximum length of option value.
/// The maximum size of the raw option data that may be read from the
/// database.
const size_t OPTION_VALUE_MAX_LEN = 4096;

/// @brief Numeric value representing last supported identifier.
///
/// This value is used to validate whether the identifier type stored in
/// a database is within bounds. of supported identifiers.
const uint8_t MAX_IDENTIFIER_TYPE = static_cast<uint8_t>(Host::LAST_IDENTIFIER_TYPE);

/// @brief Maximum length of DHCP identifier value.
const size_t DHCP_IDENTIFIER_MAX_LEN = 128;

/// @brief This class provides mechanisms for sending and retrieving
/// information from the 'hosts' table.
///
/// This class is used to insert and retrieve entries from the 'hosts' table.
/// The queries used with this class do not retrieve IPv6 reservations or
/// options associated with a host to minimize impact on performance. Other
/// classes derived from @ref PgSqlHostExchange should be used to retrieve
/// information about IPv6 reservations and options.
///
/// Database schema contains several unique indexes to guard against adding
/// multiple hosts for the same client identifier in a single subnet and for
/// adding multiple hosts with a reservation for the same IPv4 address in a
/// single subnet. The exceptions that have to be taken into account are
/// listed below:
/// - zero or null IPv4 address indicates that there is no reservation for the
///   IPv4 address for the host,
/// - null subnet identifier (either IPv4 or IPv6) indicates that
///   this subnet identifier must be ignored. Specifically, this is the case
///   when host reservation is created for the DHCPv4 server, the IPv6 subnet id
///   should be ignored. Conversely, when host reservation is created for the
///   DHCPv6 server, the IPv4 subnet id should be ignored.
///   NOTE! Zero is the "global" subnet id as Kea 1.5.0
///
/// To exclude those special case values, the Postgres backend uses partial
/// indexes, i.e. the only values that are included in the index are those that
/// are non-zero and non-null.
class PgSqlHostExchange : public PgSqlExchange {
private:

    /// @brief Column numbers for each column in the hosts table.
    /// These are used for both retrieving data and for looking up
    /// column labels for logging.  Note that their numeric order
    /// MUST match that of the column order in the hosts table.
    static const int HOST_ID_COL = 0;
    static const int DHCP_IDENTIFIER_COL = 1;
    static const int DHCP_IDENTIFIER_TYPE_COL = 2;
    static const int DHCP4_SUBNET_ID_COL = 3;
    static const int DHCP6_SUBNET_ID_COL = 4;
    static const int IPV4_ADDRESS_COL = 5;
    static const int HOSTNAME_COL = 6;
    static const int DHCP4_CLIENT_CLASSES_COL = 7;
    static const int DHCP6_CLIENT_CLASSES_COL = 8;
    static const int USER_CONTEXT_COL = 9;
    static const int DHCP4_NEXT_SERVER_COL = 10;
    static const int DHCP4_SERVER_HOSTNAME_COL = 11;
    static const int DHCP4_BOOT_FILE_NAME_COL = 12;
    static const int AUTH_KEY_COL = 13;
    /// @brief Number of columns returned for SELECT queries sent by this class.
    static const size_t HOST_COLUMNS = 14;

public:

    /// @brief Constructor
    ///
    /// @param additional_columns_num This value is set by the derived classes
    /// to indicate how many additional columns will be returned by SELECT
    /// queries performed by the derived class. This constructor will allocate
    /// resources for these columns, e.g. binding table, error indicators.
    PgSqlHostExchange(const size_t additional_columns_num = 0)
        : PgSqlExchange(HOST_COLUMNS + additional_columns_num) {
        // Set the column names for use by this class. This only comprises
        // names used by the PgSqlHostExchange class. Derived classes will
        // need to set names for the columns they use.  Currently these are
        // only used for logging purposes.
        columns_[HOST_ID_COL] = "host_id";
        columns_[DHCP_IDENTIFIER_COL] = "dhcp_identifier";
        columns_[DHCP_IDENTIFIER_TYPE_COL] = "dhcp_identifier_type";
        columns_[DHCP4_SUBNET_ID_COL] = "dhcp4_subnet_id";
        columns_[DHCP6_SUBNET_ID_COL] = "dhcp6_subnet_id";
        columns_[IPV4_ADDRESS_COL] = "ipv4_address";
        columns_[HOSTNAME_COL] = "hostname";
        columns_[DHCP4_CLIENT_CLASSES_COL] = "dhcp4_client_classes";
        columns_[DHCP6_CLIENT_CLASSES_COL] = "dhcp6_client_classes";
        columns_[USER_CONTEXT_COL] = "user_context";
        columns_[DHCP4_NEXT_SERVER_COL] = "dhcp4_next_server";
        columns_[DHCP4_SERVER_HOSTNAME_COL] = "dhcp4_server_hostname";
        columns_[DHCP4_BOOT_FILE_NAME_COL] = "dhcp4_boot_file_name";
        columns_[AUTH_KEY_COL] = "auth_key";

        BOOST_STATIC_ASSERT(12 < HOST_COLUMNS);
    };

    /// @brief Virtual destructor.
    virtual ~PgSqlHostExchange() {
    }

    /// @brief Reinitializes state information
    ///
    /// This function should be called in between statement executions.
    /// Deriving classes should invoke this method as well as be reset
    /// all of their own stateful values.
    virtual void clear() {
        host_.reset();
    };

    /// @brief Returns index of the first uninitialized column name.
    ///
    /// This method is called by the derived classes to determine which
    /// column indexes are available for the derived classes within a
    /// binding array, error array and column names. This method
    /// determines the first available index by searching the first
    /// empty value within the columns_ vector. Previously we relied on
    /// the fixed values set for each class, but this was hard to maintain
    /// when new columns were added to the SELECT queries. It required
    /// modifying indexes in all derived classes.
    ///
    /// Derived classes must call this method in their constructors and
    /// use returned value as an index for the first column used by the
    /// derived class and increment this value for each subsequent column.
    size_t findAvailColumn() const {
        std::vector<std::string>::const_iterator empty_column =
            std::find(columns_.begin(), columns_.end(), std::string());
        return (std::distance(columns_.begin(), empty_column));
    }

    /// @brief Returns value of host id in the given row.
    ///
    /// This method is used to "look ahead" at the host_id in a row
    /// without having to call retrieveHost()
    HostID getHostId(const PgSqlResult& r, int row) {
        HostID host_id;
        getColumnValue(r, row, HOST_ID_COL, host_id);
        return (host_id);
    }

    /// @brief Populate a bind array from a host
    ///
    /// Constructs a PsqlBindArray for sending data stored in a Host object
    /// to the database.
    ///
    /// @param host Host object to be added to the database.
    ///        None of the fields in the host reservation are modified -
    ///        the host data is only read.
    /// @param unique_ip boolean value indicating if multiple reservations for the
    ///        same IP address are allowed (false) or not (true).
    ///
    /// @return pointer to newly constructed bind_array containing the
    /// bound values extracted from host
    ///
    /// @throw DbOperationError if bind_array cannot be populated.
    PsqlBindArrayPtr createBindForSend(const HostPtr& host, const bool unique_ip) {
        if (!host) {
            isc_throw(BadValue, "createBindForSend:: host object is NULL");
        }

        // Store the host to ensure bound values remain in scope
        host_ = host;

        // Bind the host data to the array
        PsqlBindArrayPtr bind_array(new PsqlBindArray());
        try {
            // host_id : is auto_incremented skip it

            // dhcp_identifier : BYTEA NOT NULL
            bind_array->add(host->getIdentifier());

            // dhcp_identifier_type : SMALLINT NOT NULL
            bind_array->add(host->getIdentifierType());

            // dhcp4_subnet_id : INT NULL
            if (host->getIPv4SubnetID() == SUBNET_ID_UNUSED) {
                bind_array->addNull();
            }
            else {
                bind_array->add(host->getIPv4SubnetID());
            }

            // dhcp6_subnet_id : INT NULL
            if (host->getIPv6SubnetID() == SUBNET_ID_UNUSED) {
                bind_array->addNull();
            }
            else {
                bind_array->add(host->getIPv6SubnetID());
            }

            // ipv4_address : BIGINT NULL
            bind_array->add((host->getIPv4Reservation()));

            // hostname : VARCHAR(255) NULL
            bind_array->add(host->getHostname());

            // dhcp4_client_classes : VARCHAR(255) NULL
            // Override default separator to not include space after comma.
            bind_array->addTempString(host->getClientClasses4().toText(","));

            // dhcp6_client_classes : VARCHAR(255) NULL
            bind_array->addTempString(host->getClientClasses6().toText(","));

            // user_context: TEXT NULL
            ConstElementPtr ctx = host->getContext();
            if (ctx) {
                std::string user_context_ = ctx->str();
                bind_array->addTempString(user_context_);
            } else {
                bind_array->addNull();
            }

            // dhcp4_next_server : BIGINT NULL
            bind_array->add((host->getNextServer()));

            // dhcp4_server_hostname : VARCHAR(64)
            bind_array->add(host->getServerHostname());

            // dhcp4_boot_file_name : VARCHAR(128)
            bind_array->add(host->getBootFileName());

            // add auth keys
            std::string key = host->getKey().toText();
            if (key.empty()) {
                bind_array->addNull();
            } else {
                bind_array->add(key);
            }

            // When checking whether the IP is unique we need to bind the IPv4 address
            // at the end of the query as it has additional binding for the IPv4
            // address.
            if (unique_ip) {
                bind_array->add(host->getIPv4Reservation()); // ipv4_address
                bind_array->add(host->getIPv4SubnetID()); // subnet_id
            }


        } catch (const std::exception& ex) {
            host_.reset();
            isc_throw(DbOperationError,
                      "Could not create bind array from Host: "
                      << host->getHostname() << ", reason: " << ex.what());
        }

        return (bind_array);
    };

    /// @brief Processes one row of data fetched from a database.
    ///
    /// The processed data must contain host id, which uniquely identifies a
    /// host. This method creates a host and inserts it to the hosts collection
    /// only if the last inserted host has a different host id. This prevents
    /// adding duplicated hosts to the collection, assuming that processed
    /// rows are primarily ordered by host id column.
    ///
    /// This method must be overridden in the derived classes to also
    /// retrieve IPv6 reservations and DHCP options associated with a host.
    ///
    /// @param [out] hosts Collection of hosts to which a new host created
    ///        from the processed data should be inserted.
    virtual void processRowData(ConstHostCollection& hosts,
                                const PgSqlResult& r, int row) {
        // Peek at the host id , so we can skip it if we already have it
        // This lets us avoid constructing a copy of host for each
        // of its sub-rows (options, etc...)
        HostID row_host_id = getHostId(r, row);

        // Add new host only if there are no hosts or the host id of the
        // most recently added host is different than the host id of the
        // currently processed host.
        if (hosts.empty() || row_host_id != hosts.back()->getHostId()) {
            HostPtr host = retrieveHost(r, row, row_host_id);
            hosts.push_back(host);
        }
    }

    /// @brief Creates a Host object from a given row in a result set.
    ///
    /// @param r result set containing one or more rows from the hosts table
    /// @param row index within the result set of the row to process
    /// @param peeked_host_id if the caller has peeked ahead at the row's
    /// host_id, it can be passed in here to avoid fetching it from the row
    /// a second time.
    ///
    /// @return HostPtr to the newly created Host object
    ///
    /// @throw DbOperationError if the host cannot be created.
    HostPtr retrieveHost(const PgSqlResult& r, int row,
                         const HostID& peeked_host_id = 0) {

        // If the caller peeked ahead at the host_id use that, otherwise
        // read it from the row.
        HostID host_id = (peeked_host_id ? peeked_host_id : getHostId(r,row));

        // dhcp_identifier : BYTEA NOT NULL
        uint8_t identifier_value[DHCP_IDENTIFIER_MAX_LEN];
        size_t identifier_len;
        convertFromBytea(r, row, DHCP_IDENTIFIER_COL, identifier_value,
                             sizeof(identifier_value), identifier_len);

        // dhcp_identifier_type : SMALLINT NOT NULL
        uint8_t type;
        getColumnValue(r, row, DHCP_IDENTIFIER_TYPE_COL, type);
        if (type > MAX_IDENTIFIER_TYPE) {
            isc_throw(BadValue, "invalid dhcp identifier type returned: "
                      << static_cast<int>(type));
        }

        Host::IdentifierType identifier_type =
            static_cast<Host::IdentifierType>(type);

        // dhcp4_subnet_id : INT NULL
        uint32_t subnet_id(SUBNET_ID_UNUSED);
        if (!isColumnNull(r, row, DHCP4_SUBNET_ID_COL)) {
            getColumnValue(r, row, DHCP4_SUBNET_ID_COL, subnet_id);
        }
        SubnetID dhcp4_subnet_id = static_cast<SubnetID>(subnet_id);

        // dhcp6_subnet_id : INT NULL
        subnet_id = SUBNET_ID_UNUSED;
        if (!isColumnNull(r, row, DHCP6_SUBNET_ID_COL)) {
            getColumnValue(r, row, DHCP6_SUBNET_ID_COL, subnet_id);
        }
        SubnetID dhcp6_subnet_id = static_cast<SubnetID>(subnet_id);

        // ipv4_address : BIGINT NULL
        uint32_t addr4(0);
        if (!isColumnNull(r, row, IPV4_ADDRESS_COL)) {
            getColumnValue(r, row, IPV4_ADDRESS_COL, addr4);
        }
        isc::asiolink::IOAddress ipv4_reservation(addr4);

        // hostname : VARCHAR(255) NULL
        std::string hostname;
        if (!isColumnNull(r, row, HOSTNAME_COL)) {
            getColumnValue(r, row, HOSTNAME_COL, hostname);
        }

        // dhcp4_client_classes : VARCHAR(255) NULL
        std::string dhcp4_client_classes;
        if (!isColumnNull(r, row, DHCP4_CLIENT_CLASSES_COL)) {
            getColumnValue(r, row, DHCP4_CLIENT_CLASSES_COL, dhcp4_client_classes);
        }

        // dhcp6_client_classes : VARCHAR(255) NULL
        std::string dhcp6_client_classes;
        if (!isColumnNull(r, row, DHCP6_CLIENT_CLASSES_COL)) {
            getColumnValue(r, row, DHCP6_CLIENT_CLASSES_COL, dhcp6_client_classes);
        }

        // user_context: TEXT
        std::string user_context;
        if (!isColumnNull(r, row, USER_CONTEXT_COL)) {
            getColumnValue(r, row, USER_CONTEXT_COL, user_context);
        }

        // dhcp4_next_server : BIGINT NULL
        uint32_t dhcp4_next_server_as_uint32(0);
        if (!isColumnNull(r, row, DHCP4_NEXT_SERVER_COL)) {
            getColumnValue(r, row, DHCP4_NEXT_SERVER_COL, dhcp4_next_server_as_uint32);
        }
        isc::asiolink::IOAddress dhcp4_next_server(dhcp4_next_server_as_uint32);

        // dhcp4_server_hostname : VARCHAR(64)
        std::string dhcp4_server_hostname;
        if (!isColumnNull(r, row, DHCP4_SERVER_HOSTNAME_COL)) {
            getColumnValue(r, row, DHCP4_SERVER_HOSTNAME_COL, dhcp4_server_hostname);
        }

        // dhcp4_boot_file_name : VARCHAR(128)
        std::string dhcp4_boot_file_name;
        if (!isColumnNull(r, row, DHCP4_BOOT_FILE_NAME_COL)) {
            getColumnValue(r, row, DHCP4_BOOT_FILE_NAME_COL, dhcp4_boot_file_name);
        }

        // auth_key : VARCHAR(16)
        std::string auth_key;
        if (!isColumnNull(r, row, AUTH_KEY_COL)) {
            getColumnValue(r, row, AUTH_KEY_COL, auth_key);
        }

        // Finally, attempt to create the new host.
        HostPtr host;
        try {
            host.reset(new Host(identifier_value, identifier_len,
                                identifier_type, dhcp4_subnet_id,
                                dhcp6_subnet_id, ipv4_reservation, hostname,
                                dhcp4_client_classes, dhcp6_client_classes,
                                dhcp4_next_server, dhcp4_server_hostname,
                                dhcp4_boot_file_name, AuthKey(auth_key)));

            // Set the user context if there is one.
            if (!user_context.empty()) {
                try {
                    ConstElementPtr ctx = Element::fromJSON(user_context);
                    if (!ctx || (ctx->getType() != Element::map)) {
                        isc_throw(BadValue, "user context '" << user_context
                                  << "' is not a JSON map");
                    }
                    host->setContext(ctx);
                } catch (const isc::data::JSONError& ex) {
                    isc_throw(BadValue, "user context '" << user_context
                              << "' is invalid JSON: " << ex.what());
                }
            }

            host->setHostId(host_id);
        } catch (const isc::Exception& ex) {
            isc_throw(DbOperationError, "Could not create host: " << ex.what());
        }

        return(host);
    };

protected:
    /// Pointer to Host object holding information to be inserted into
    /// Hosts table.  This is used to retain scope.
    HostPtr host_;
};

/// @brief Extends base exchange class with ability to retrieve DHCP options
/// from the 'dhcp4_options' and 'dhcp6_options' tables.
///
/// This class provides means to retrieve both DHCPv4 and DHCPv6 options
/// along with the host information. It is not used to retrieve IPv6
/// reservations. The following types of queries are supported:
/// - SELECT ? FROM hosts LEFT JOIN dhcp4_options LEFT JOIN dhcp6_options ...
/// - SELECT ? FROM hosts LEFT JOIN dhcp4_options ...
/// - SELECT ? FROM hosts LEFT JOIN dhcp6_options ...
class PgSqlHostWithOptionsExchange : public PgSqlHostExchange {
private:

    /// @brief Number of columns holding DHCPv4  or DHCPv6 option information.
    static const size_t OPTION_COLUMNS = 7;

    /// @brief Receives DHCPv4 or DHCPv6 options information from the
    /// dhcp4_options or dhcp6_options tables respectively.
    ///
    /// The PgSqlHostWithOptionsExchange class holds two respective instances
    /// of this class, one for receiving DHCPv4 options, one for receiving
    /// DHCPv6 options.
    ///
    /// The following are the basic functions of this class:
    /// - bind class members to specific columns in PgSQL binding tables,
    /// - set DHCP options specific column names,
    /// - create instances of options retrieved from the database.
    ///
    /// The reason for isolating those functions in a separate C++ class is
    /// to prevent code duplication for handling DHCPv4 and DHCPv6 options.
    class OptionProcessor {
    public:

        /// @brief Constructor.
        ///
        /// @param universe V4 or V6. The type of the options' instances
        /// created by this class depends on this parameter.
        /// @param start_column Index of the first column to be used by this
        /// class.
        OptionProcessor(const Option::Universe& universe,
                        const size_t start_column)
        : universe_(universe), start_column_(start_column),
          option_id_index_(start_column), code_index_(start_column_ + 1),
          value_index_(start_column_ + 2),
          formatted_value_index_(start_column_ + 3),
          space_index_(start_column_ + 4),
          persistent_index_(start_column_ + 5),
          user_context_index_(start_column_ + 6),
          most_recent_option_id_(0) {
        }

        /// @brief Reinitializes state information
        ///
        /// This function should be called prior to processing a fetched
        /// set of options.
        void clear() {
            most_recent_option_id_ = 0;
        }

        /// @brief Creates instance of the currently processed option.
        ///
        /// This method detects if the currently processed option is a new
        /// instance. It makes its determination by comparing the identifier
        /// of the currently processed option, with the most recently processed
        /// option. If the current value is greater than the id of the recently
        /// processed option it is assumed that the processed row holds new
        /// option information. In such case the option instance is created and
        /// inserted into the configuration passed as argument.
        ///
        /// This logic is necessary to deal with result sets made from multiple
        /// left joins which contain duplicated data.  For instance queries
        /// returning both v4 and v6 options for a host would generate result
        /// sets similar to this:
        /// @code
        ///
        /// row 0: host-1  v4-opt-1  v6-opt-1
        /// row 1: host-1  v4-opt-1  v6-opt-2
        /// row 2: host-1  v4-opt-1  v6-opt-3
        /// row 4: host-1  v4-opt-2  v6-opt-1
        /// row 5: host-1  v4-opt-2  v6-opt-2
        /// row 6: host-1  v4-opt-2  v6-opt-3
        /// row 7: host-2  v4-opt-1  v6-opt-1
        /// row 8: host-2  v4-opt-2  v6-opt-1
        ///  :
        /// @endcode
        ///
        /// @param cfg Pointer to the configuration object into which new
        /// option instances should be inserted.
        /// @param r result set containing one or more rows from a dhcp
        /// options table.
        /// @param row index within the result set of the row to process
        void retrieveOption(const CfgOptionPtr& cfg, const PgSqlResult& r,
                            int row) {
            // If the option id on this row is NULL, then there's no
            // option of this type (4/6) on this row to fetch, so bail.
            if (PgSqlExchange::isColumnNull(r, row, option_id_index_)) {
                return;
            }

            // option_id: INT
            uint64_t option_id;
            PgSqlExchange::getColumnValue(r, row, option_id_index_, option_id);

            // The row option id must be greater than id if the most recent
            // option because they are ordered by option id. Otherwise
            // we assume that we have already processed this option.
            if (most_recent_option_id_ >= option_id) {
                return;
            }

            // Remember current option id as the most recent processed one. We
            // will be comparing it with option ids in subsequent rows.
            most_recent_option_id_ = option_id;

            // code: SMALLINT NOT NULL
            uint16_t code;
            PgSqlExchange::getColumnValue(r, row, code_index_, code);

            // value: BYTEA
            uint8_t value[OPTION_VALUE_MAX_LEN];
            size_t value_len(0);
            if (!isColumnNull(r, row, value_index_)) {
                PgSqlExchange::convertFromBytea(r, row, value_index_, value,
                                                sizeof(value), value_len);
            }

            // formatted_value: TEXT
            std::string formatted_value;
            if (!isColumnNull(r, row, formatted_value_index_)) {
                PgSqlExchange::getColumnValue(r, row, formatted_value_index_,
                                              formatted_value);
            }

            // space: VARCHAR(128)
            std::string space;
            if (!isColumnNull(r, row, space_index_)) {
                PgSqlExchange::getColumnValue(r, row, space_index_, space);
            }

            // If empty or null space provided, use a default top level space.
            if (space.empty()) {
                space = (universe_ == Option::V4 ?
                         DHCP4_OPTION_SPACE : DHCP6_OPTION_SPACE);
            }

            // persistent: BOOL default false
            bool persistent;
            PgSqlExchange::getColumnValue(r, row, persistent_index_,
                                          persistent);

            // user_context: TEXT
            std::string user_context;
            if (!isColumnNull(r, row, user_context_index_)) {
                PgSqlExchange::getColumnValue(r, row, user_context_index_,
                                              user_context);
            }

            // Options are held in a binary or textual format in the database.
            // This is similar to having an option specified in a server
            // configuration file. Such option is converted to appropriate C++
            // class, using option definition. Thus, we need to find the
            // option definition for this option code and option space.

            // If the option space is a standard DHCPv4 or DHCPv6 option space,
            // this is most likely a standard option, for which we have a
            // definition created within libdhcp++.
            OptionDefinitionPtr def = LibDHCP::getOptionDef(space, code);

            // Otherwise, we may check if this an option encapsulated within the
            // vendor space.
            if (!def && (space != DHCP4_OPTION_SPACE) &&
                (space != DHCP6_OPTION_SPACE)) {
                uint32_t vendor_id = LibDHCP::optionSpaceToVendorId(space);
                if (vendor_id > 0) {
                    def = LibDHCP::getVendorOptionDef(universe_, vendor_id,
                                                      code);
                }
            }

            // In all other cases, we use runtime option definitions, which
            // should be also registered within the libdhcp++.
            if (!def) {
                def = LibDHCP::getRuntimeOptionDef(space, code);
            }

            OptionPtr option;

            if (!def) {
                // If no definition found, we use generic option type.
                OptionBuffer buf(value, value + value_len);
                option.reset(new Option(universe_, code, buf.begin(),
                                        buf.end()));
            } else {
                // The option value may be specified in textual or binary format
                // in the database. If formatted_value is empty, the binary
                // format is used. Depending on the format we use a different
                // variant of the optionFactory function.
                if (formatted_value.empty()) {
                    OptionBuffer buf(value, value + value_len);
                    option = def->optionFactory(universe_, code, buf.begin(),
                                                buf.end());
                } else {
                    // Spit the value specified in comma separated values
                    // format.
                    std::vector<std::string> split_vec;
                    boost::split(split_vec, formatted_value,
                                 boost::is_any_of(","));
                    option = def->optionFactory(universe_, code, split_vec);
                }
            }

            OptionDescriptor desc(option, persistent, formatted_value);

            // Set the user context if there is one into the option descriptor.
            if (!user_context.empty()) {
                try {
                    ConstElementPtr ctx = Element::fromJSON(user_context);
                    if (!ctx || (ctx->getType() != Element::map)) {
                        isc_throw(BadValue, "user context '" << user_context
                                  << "' is no a JSON map");
                    }
                    desc.setContext(ctx);
                } catch (const isc::data::JSONError& ex) {
                    isc_throw(BadValue, "user context '" << user_context
                              << "' is invalid JSON: " << ex.what());
                }
            }

            cfg->add(desc, space);
        }

        /// @brief Specify column names.
        ///
        /// @param [out] columns Reference to a vector holding names of option
        /// specific columns.
        void setColumnNames(std::vector<std::string>& columns) {
            columns[option_id_index_] = "option_id";
            columns[code_index_] = "code";
            columns[value_index_] = "value";
            columns[formatted_value_index_] = "formatted_value";
            columns[space_index_] = "space";
            columns[persistent_index_] = "persistent";
            columns[user_context_index_] = "user_context";
        }

    private:
        /// @brief Universe: V4 or V6.
        Option::Universe universe_;

        /// @brief Index of first column used by this class.
        size_t start_column_;

        //@}

        /// @name Indexes of the specific columns
        //@{
        /// @brief Option id
        size_t option_id_index_;

        /// @brief Code
        size_t code_index_;

        /// @brief Value
        size_t value_index_;

        /// @brief Formatted value
        size_t formatted_value_index_;

        /// @brief Space
        size_t space_index_;

        /// @brief Persistent
        size_t persistent_index_;
        //@}

        /// @brief User context
        size_t user_context_index_;

        /// @brief Option id for last processed row.
        uint64_t most_recent_option_id_;
    };

    /// @brief Pointer to the @ref OptionProcessor class.
    typedef boost::shared_ptr<OptionProcessor> OptionProcessorPtr;

public:

    /// @brief DHCP option types to be fetched from the database.
    ///
    /// Supported types are:
    /// - Only DHCPv4 options,
    /// - Only DHCPv6 options,
    /// - Both DHCPv4 and DHCPv6 options.
    enum FetchedOptions {
        DHCP4_ONLY,
        DHCP6_ONLY,
        DHCP4_AND_DHCP6
    };

    /// @brief Constructor.
    ///
    /// @param fetched_options Specifies if DHCPv4, DHCPv6 or both should
    /// be fetched from the database for a host.
    /// @param additional_columns_num Number of additional columns for which
    /// resources should be allocated, e.g. binding table, column names etc.
    /// This parameter should be set to a non zero value by derived classes to
    /// allocate resources for the columns supported by derived classes.
    PgSqlHostWithOptionsExchange(const FetchedOptions& fetched_options,
                                 const size_t additional_columns_num = 0)
        : PgSqlHostExchange(getRequiredColumnsNum(fetched_options)
                            + additional_columns_num),
          opt_proc4_(), opt_proc6_() {

        // Create option processor for DHCPv4 options, if required.
        if ((fetched_options == DHCP4_ONLY) ||
            (fetched_options == DHCP4_AND_DHCP6)) {
            opt_proc4_.reset(new OptionProcessor(Option::V4,
                                                 findAvailColumn()));
            opt_proc4_->setColumnNames(columns_);
        }

        // Create option processor for DHCPv6 options, if required.
        if ((fetched_options == DHCP6_ONLY) ||
            (fetched_options == DHCP4_AND_DHCP6)) {
            opt_proc6_.reset(new OptionProcessor(Option::V6,
                                                 findAvailColumn()));
            opt_proc6_->setColumnNames(columns_);
        }
    }

    /// @brief Clears state information
    ///
    /// This function should be called in between statement executions.
    /// Deriving classes should invoke this method as well as be reset
    /// all of their own stateful values.
    virtual void clear() {
        PgSqlHostExchange::clear();
        if (opt_proc4_) {
            opt_proc4_->clear();
        }

        if (opt_proc6_) {
            opt_proc6_->clear();
        }
    }

    /// @brief Processes the current row.
    ///
    /// The fetched row includes both host information and DHCP option
    /// information. Because the SELECT queries use one or more LEFT JOIN
    /// clauses, the result set may contain duplicated host or options
    /// entries. This method detects duplicated information and discards such
    /// entries.
    ///
    /// @param [out] hosts Container holding parsed hosts and options.
    virtual void processRowData(ConstHostCollection& hosts,
                                const PgSqlResult& r, int row) {
        HostPtr current_host;
        if (hosts.empty()) {
            // Must be the first one, fetch it.
            current_host = retrieveHost(r, row);
            hosts.push_back(current_host);
        } else {
            // Peek at the host id so we can skip it if we already have
            // this host.  This lets us avoid retrieving the host needlessly
            // for each of its sub-rows (options, etc...).
            HostID row_host_id = getHostId(r, row);
            current_host = boost::const_pointer_cast<Host>(hosts.back());

            // if the row's host id is greater than the one we've been
            // working on we're starting a new host, so fetch it.
            if (row_host_id > current_host->getHostId()) {
                current_host = retrieveHost(r, row, row_host_id);
                hosts.push_back(current_host);
            }
        }

        // Parse DHCPv4 options if required to do so.
        if (opt_proc4_) {
            CfgOptionPtr cfg = current_host->getCfgOption4();
            opt_proc4_->retrieveOption(cfg, r, row);
        }

        // Parse DHCPv6 options if required to do so.
        if (opt_proc6_) {
            CfgOptionPtr cfg = current_host->getCfgOption6();
            opt_proc6_->retrieveOption(cfg, r, row);
        }
    }

private:

    /// @brief Returns a number of columns required to retrieve option data.
    ///
    /// Depending if we need DHCPv4/DHCPv6 options only, or both DHCPv4 and
    /// DHCPv6 a different number of columns is required in the binding array.
    /// This method returns the number of required columns, according to the
    /// value of @c fetched_columns passed in the constructor.
    ///
    /// @param fetched_columns A value which specifies whether DHCPv4, DHCPv6 or
    /// both types of options should be retrieved.
    ///
    /// @return Number of required columns.
    static size_t getRequiredColumnsNum(const FetchedOptions& fetched_options) {
        return (fetched_options == DHCP4_AND_DHCP6 ? 2 * OPTION_COLUMNS :
                OPTION_COLUMNS);
    }

    /// @brief Pointer to DHCPv4 options processor.
    ///
    /// If this object is NULL, the DHCPv4 options are not fetched.
    OptionProcessorPtr opt_proc4_;

    /// @brief Pointer to DHCPv6 options processor.
    ///
    /// If this object is NULL, the DHCPv6 options are not fetched.
    OptionProcessorPtr opt_proc6_;
};

/// @brief This class provides mechanisms for sending and retrieving
/// host information, DHCPv4 options, DHCPv6 options and IPv6 reservations.
///
/// This class extends the @ref PgSqlHostWithOptionsExchange class with the
/// mechanisms to retrieve IPv6 reservations. This class is used in situations
/// when it is desired to retrieve DHCPv6 specific information about the host
/// (DHCPv6 options and reservations), or entire information about the host
/// (DHCPv4 options, DHCPv6 options and reservations). The following are the
/// queries used with this class:
/// - SELECT ? FROM hosts LEFT JOIN dhcp4_options LEFT JOIN dhcp6_options
///   LEFT JOIN ipv6_reservations ...
/// - SELECT ? FROM hosts LEFT JOIN dhcp6_options LEFT JOIN ipv6_reservations ..
class PgSqlHostIPv6Exchange : public PgSqlHostWithOptionsExchange {
private:

    /// @brief Number of columns holding IPv6 reservation information.
    static const size_t RESERVATION_COLUMNS = 5;

public:

    /// @brief Constructor.
    ///
    /// Apart from initializing the base class data structures it also
    /// initializes values representing IPv6 reservation information.
    PgSqlHostIPv6Exchange(const FetchedOptions& fetched_options)
        : PgSqlHostWithOptionsExchange(fetched_options, RESERVATION_COLUMNS),
          reservation_id_index_(findAvailColumn()),
          address_index_(reservation_id_index_ + 1),
          prefix_len_index_(reservation_id_index_ + 2),
          type_index_(reservation_id_index_ + 3),
          iaid_index_(reservation_id_index_ + 4),
          most_recent_reservation_id_(0) {

        // Provide names of additional columns returned by the queries.
        columns_[reservation_id_index_] = "reservation_id";
        columns_[address_index_] = "address";
        columns_[prefix_len_index_] = "prefix_len";
        columns_[type_index_] = "type";
        columns_[iaid_index_] = "dhcp6_iaid";

        BOOST_STATIC_ASSERT(4 < RESERVATION_COLUMNS);
    }

    /// @brief Reinitializes state information
    ///
    /// This function should be called in between statement executions.
    /// Deriving classes should invoke this method as well as be reset
    /// all of their own stateful values.
    void clear() {
        PgSqlHostWithOptionsExchange::clear();
        most_recent_reservation_id_ = 0;
    }

    /// @brief Returns reservation id from the row.
    ///
    /// @return Reservation id or 0 if no reservation data is fetched.
    uint64_t getReservationId(const PgSqlResult& r, int row) const {
        uint64_t resv_id = 0;
        if (!isColumnNull(r, row, reservation_id_index_)) {
            getColumnValue(r, row, reservation_id_index_, resv_id);
        }

        return (resv_id);
    };

    /// @brief Creates IPv6 reservation from the data contained in the
    /// currently processed row.
    ///
    /// @return IPv6Resrv object (containing IPv6 address or prefix reservation)
    IPv6Resrv retrieveReservation(const PgSqlResult& r, int row) {

        // type: SMALLINT NOT NULL
        uint16_t tmp;
        getColumnValue(r, row, type_index_, tmp);

        // Convert it to IPv6 Reservation type (0 = IA_NA, 2 = IA_PD)
        IPv6Resrv::Type resv_type;
        switch (tmp) {
        case 0:
            resv_type = IPv6Resrv::TYPE_NA;
            break;

        case 2:
            resv_type = IPv6Resrv::TYPE_PD;
            break;

        default:
            isc_throw(BadValue,
                      "invalid IPv6 reservation type returned: "
                      << tmp << ". Only 0 or 2 are allowed.");
        }

        // address VARCHAR(39) NOT NULL
        isc::asiolink::IOAddress address(getIPv6Value(r, row, address_index_));

        // prefix_len: SMALLINT NOT NULL
        uint16_t prefix_len;
        getColumnValue(r, row, prefix_len_index_, prefix_len);

        // @todo once we support populating iaid
        // iaid: INT
        // int iaid;
        // getColumnValue(r, row, iaid_index_, iaid);

        // Create the reservation.
        IPv6Resrv reservation(resv_type, IOAddress(address), prefix_len);
        return (reservation);
    };

    /// @brief Processes one row of data fetched from a database.
    ///
    /// The processed data must contain host id, which uniquely identifies a
    /// host. This method creates a host and inserts it to the hosts collection
    /// only if the last inserted host has a different host id. This prevents
    /// adding duplicated hosts to the collection, assuming that processed
    /// rows are primarily ordered by host id column.
    ///
    /// Depending on the value of the @c fetched_options specified in the
    /// constructor, this method also parses options returned as a result
    /// of SELECT queries.
    ///
    /// For any returned row which contains IPv6 reservation information it
    /// checks if the reservation is not a duplicate of previously parsed
    /// reservation and appends the IPv6Resrv object into the host object
    /// if the parsed row contains new reservation information.
    ///
    /// @param [out] hosts Collection of hosts to which a new host created
    ///        from the processed data should be inserted.
    /// @param r result set containing one or more rows of fetched data
    /// @param row index within the result set of the row to process
    virtual void processRowData(ConstHostCollection& hosts,
                                const PgSqlResult& r, int row) {
        // Call parent class to fetch host information and options.
        PgSqlHostWithOptionsExchange::processRowData(hosts, r, row);

        // Shouldn't happen but just in case
        if (hosts.empty()) {
            isc_throw(Unexpected, "no host information while retrieving"
                      " IPv6 reservation");
        }

        // If we have reservation id we haven't seen yet, retrieve the
        // the reservation, adding it to the current host
        uint64_t reservation_id = getReservationId(r, row);
        if (reservation_id && (reservation_id > most_recent_reservation_id_)) {
            HostPtr host = boost::const_pointer_cast<Host>(hosts.back());
            host->addReservation(retrieveReservation(r, row));
            most_recent_reservation_id_ = reservation_id;
        }
    }

private:
    /// @name Indexes of columns holding information about IPv6 reservations.
    //@{
    /// @brief Index of reservation_id column.
    size_t reservation_id_index_;

    /// @brief Index of address column.
    size_t address_index_;

    /// @brief Index of prefix_len column.
    size_t prefix_len_index_;

    /// @brief Index of type column.
    size_t type_index_;

    /// @brief Index of IAID column.
    size_t iaid_index_;

    //@}

    /// @brief Reservation id for last processed row.
    uint64_t most_recent_reservation_id_;
};

/// @brief This class is used for storing IPv6 reservations in a PgSQL database.
///
/// This class is only used to insert IPv6 reservations into the
/// ipv6_reservations table. It is not used to retrieve IPv6 reservations. To
/// retrieve IPv6 reservation the @ref PgSqlIPv6HostExchange class should be
/// used instead.
///
/// When a new IPv6 reservation is inserted into the database, an appropriate
/// host must be defined in the hosts table. An attempt to insert IPv6
/// reservation for non-existing host will result in failure.
class PgSqlIPv6ReservationExchange : public PgSqlExchange {
private:

    /// @brief Set number of columns for ipv6_reservation table.
    static const size_t RESRV_COLUMNS = 6;

public:

    /// @brief Constructor
    ///
    /// Initialize class members representing a single IPv6 reservation.
    PgSqlIPv6ReservationExchange()
        : PgSqlExchange(RESRV_COLUMNS),
          resv_(IPv6Resrv::TYPE_NA, asiolink::IOAddress("::"), 128) {
        // Set the column names (for error messages)
        columns_[0] = "host_id";
        columns_[1] = "address";
        columns_[2] = "prefix_len";
        columns_[3] = "type";
        columns_[4] = "dhcp6_iaid";
        BOOST_STATIC_ASSERT(5 < RESRV_COLUMNS);
    }

    /// @brief Populate a bind array representing an IPv6 reservation
    ///
    /// Constructs a PsqlBindArray for an IPv6 reservation to the database.
    ///
    /// @param resv The IPv6 reservation to be added to the database.
    ///        None of the fields in the reservation are modified -
    /// @param host_id ID of the host to which this reservation belongs.
    /// @param unique_ip boolean value indicating if multiple reservations for the
    ///        same IP address are allowed (false) or not (true).
    ///
    /// @return pointer to newly constructed bind_array containing the
    /// bound values extracted the IPv6 reservation
    ///
    /// @throw DbOperationError if bind_array cannot be populated.
    PsqlBindArrayPtr createBindForSend(const IPv6Resrv& resv,
                                       const HostID& host_id,
                                       const bool unique_ip) {
        // Store the values to ensure they remain valid.
        // Technically we don't need this, as currently all the values
        // are converted to strings and stored by the bind array.
        resv_ = resv;

        PsqlBindArrayPtr bind_array(new PsqlBindArray());

        try {
            // address VARCHAR(39) NOT NULL
            bind_array->add(resv.getPrefix());

            // prefix_len: SMALLINT NOT NULL
            bind_array->add(resv.getPrefixLen());

            // type: SMALLINT NOT NULL
            // See lease6_types table for values (0 = IA_NA, 2 = IA_PD)
            uint16_t type = resv.getType() == IPv6Resrv::TYPE_NA ? 0 : 2;
            bind_array->add(type);

            // dhcp6_iaid: INT UNSIGNED
            /// @todo: We don't support iaid in the IPv6Resrv yet.
            bind_array->addNull();

            // host_id: BIGINT NOT NULL
            bind_array->add(host_id);

            // When checking whether the IP is unique we need to bind the IPv6 address
            // and prefix length at the end of the query as it has additional binding
            // for the IPv6 address and prefix length.
            if (unique_ip) {
                bind_array->add(resv.getPrefix()); // address
                bind_array->add(resv.getPrefixLen()); // prefix_len
            }
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from IPv6 Reservation: "
                      << resv_.toText() << ", reason: " << ex.what());
        }

        return (bind_array);
    }

private:
    /// @brief Object holding reservation being sent to the database.
    IPv6Resrv resv_;
};

/// @brief This class is used for inserting options into a database.
///
/// This class supports inserting both DHCPv4 and DHCPv6 options.
class PgSqlOptionExchange : public PgSqlExchange {
private:

    static const int OPTION_ID_COL = 0;
    static const int CODE_COL = 1;
    static const int VALUE_COL = 2;
    static const int FORMATTED_VALUE_COL = 3;
    static const int SPACE_COL = 4;
    static const int PERSISTENT_COL = 5;
    static const int USER_CONTEXT_COL = 6;
    static const int DHCP_CLIENT_CLASS_COL = 7;
    static const int DHCP_SUBNET_ID_COL = 8;
    static const int HOST_ID_COL = 9;
    static const int SCOPE_ID_COL = 10;

    /// @brief Number of columns in the tables holding options.
    static const size_t OPTION_COLUMNS = 11;

public:

    /// @brief Constructor.
    PgSqlOptionExchange()
        : PgSqlExchange(OPTION_COLUMNS), value_(),
          value_len_(0), option_() {
        columns_[OPTION_ID_COL] = "option_id";
        columns_[CODE_COL] = "code";
        columns_[VALUE_COL] = "value";
        columns_[FORMATTED_VALUE_COL] = "formatted_value";
        columns_[SPACE_COL] = "space";
        columns_[PERSISTENT_COL] = "persistent";
        columns_[USER_CONTEXT_COL] = "user_context";
        columns_[DHCP_CLIENT_CLASS_COL] = "dhcp_client_class";
        columns_[DHCP_SUBNET_ID_COL] = "dhcp_subnet_id";
        columns_[HOST_ID_COL] = "host_id";
        columns_[SCOPE_ID_COL] = "scope_id";

        BOOST_STATIC_ASSERT(10 < OPTION_COLUMNS);
    }

    /// @brief Creates binding array to insert option data into database.
    ///
    /// @param opt_desc option descriptor of the option to write
    /// @param opt_space name of the option space to which the option belongs
    /// @param host_id host id of the host to which the option belongs
    ///
    /// @return pointer to newly constructed bind_array containing the
    /// bound values extracted from host
    PsqlBindArrayPtr createBindForSend(const OptionDescriptor& opt_desc,
                                       const std::string& opt_space,
                                       const HostID& host_id) {
        // Hold pointer to the option to make sure it remains valid until
        // we complete a query.
        option_ = opt_desc.option_;

        // Create the bind-array
        PsqlBindArrayPtr bind_array(new PsqlBindArray());

        try {
            // option_id: is auto_incremented so skip it

            // code: SMALLINT UNSIGNED NOT NULL
            bind_array->add(option_->getType());

            // value: BYTEA NULL
            if (opt_desc.formatted_value_.empty() &&
                (opt_desc.option_->len() > opt_desc.option_->getHeaderLen())) {
                // The formatted_value is empty and the option value is
                // non-empty so we need to prepare on-wire format for the
                // option and store it in the database as a BYTEA.
                OutputBuffer buf(opt_desc.option_->len());
                opt_desc.option_->pack(buf);
                const char* buf_ptr = static_cast<const char*>(buf.getData());
                value_.assign(buf_ptr + opt_desc.option_->getHeaderLen(),
                              buf_ptr + buf.getLength());
                value_len_ = value_.size();
                bind_array->add(value_);
            } else {
                // No value or formatted_value specified. In this case, the
                // value BYTEA should be NULL.
                bind_array->addNull(PsqlBindArray::BINARY_FMT);
            }

            // formatted_value: TEXT NULL,
            if (!opt_desc.formatted_value_.empty()) {
                bind_array->addTempString(opt_desc.formatted_value_);
            } else {
                bind_array->addNull();
            }

            // space: VARCHAR(128) NULL
            if (!opt_space.empty()) {
                bind_array->addTempString(opt_space);
            } else {
                bind_array->addNull();
            }

            // persistent: BOOLEAN DEFAULT false
            bind_array->add(opt_desc.persistent_);

            // user_context: TEXT NULL,
            ConstElementPtr ctx = opt_desc.getContext();
            if (ctx) {
                std::string user_context_ = ctx->str();
                bind_array->addTempString(user_context_);
            } else {
                bind_array->addNull();
            }

            // host_id: INT NULL
            if (!host_id) {
                isc_throw(BadValue, "host_id cannot be null");
            }
            bind_array->add(host_id);

        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array for inserting DHCP "
                      "host option: " << option_->toText() << ", reason: "
                      << ex.what());
        }

        return (bind_array);
    }

private:

    /// @brief Option value as binary.
    std::vector<uint8_t> value_;

    /// @brief Option value length.
    size_t value_len_;

    /// @brief Pointer to currently parsed option.
    OptionPtr option_;
};

}  // namespace

namespace isc {
namespace dhcp {

/// @brief PostgreSQL Host Context
///
/// This class stores the thread context for the manager pool.
/// The class is needed by all get/update/delete functions which must use one
/// or more exchanges to perform database operations.
/// Each context provides a set of such exchanges for each thread.
/// The context instances are lazy initialized by the requesting thread by using
/// the manager's createContext function and are destroyed when the manager's
/// pool instance is destroyed.
class PgSqlHostContext {
public:

    /// @brief Constructor
    ///
    /// @param parameters See PgSqlHostMgr constructor.
    /// @param io_service_accessor The IOService accessor function.
    /// @param db_reconnect_callback The connection recovery callback.
    PgSqlHostContext(const DatabaseConnection::ParameterMap& parameters,
                     IOServiceAccessorPtr io_service_accessor,
                     db::DbCallback db_reconnect_callback);

    /// The exchange objects are used for transfer of data to/from the database.
    /// They are pointed-to objects as the contents may change in "const" calls,
    /// while the rest of this object does not.  (At alternative would be to
    /// declare them as "mutable".)

    /// @brief Pointer to the object representing an exchange which
    /// can be used to retrieve hosts and DHCPv4 options.
    boost::shared_ptr<PgSqlHostWithOptionsExchange> host_ipv4_exchange_;

    /// @brief Pointer to an object representing an exchange which can
    /// be used to retrieve hosts, DHCPv6 options and IPv6 reservations.
    boost::shared_ptr<PgSqlHostIPv6Exchange> host_ipv6_exchange_;

    /// @brief Pointer to an object representing an exchange which can
    /// be used to retrieve hosts, DHCPv4 and DHCPv6 options, and
    /// IPv6 reservations using a single query.
    boost::shared_ptr<PgSqlHostIPv6Exchange> host_ipv46_exchange_;

    /// @brief Pointer to an object representing an exchange which can
    /// be used to insert new IPv6 reservation.
    boost::shared_ptr<PgSqlIPv6ReservationExchange> host_ipv6_reservation_exchange_;

    /// @brief Pointer to an object representing an exchange which can
    /// be used to insert DHCPv4 or DHCPv6 option into dhcp4_options
    /// or dhcp6_options table.
    boost::shared_ptr<PgSqlOptionExchange> host_option_exchange_;

    /// @brief PostgreSQL connection
    PgSqlConnection conn_;

    /// @brief Indicates if the database is opened in read only mode.
    bool is_readonly_;
};

/// @brief PostgreSQL Host Context Pool
///
/// This class provides a pool of contexts.
/// The manager will use this class to handle available contexts.
/// There is only one ContextPool per manager per back-end, which is created
/// and destroyed by the respective manager factory class.
class PgSqlHostContextPool {
public:

    /// @brief The vector of available contexts.
    std::vector<PgSqlHostContextPtr> pool_;

    /// @brief The mutex to protect pool access.
    std::mutex mutex_;
};

/// @brief Type of pointers to context pools.
typedef boost::shared_ptr<PgSqlHostContextPool> PgSqlHostContextPoolPtr;

/// @brief Implementation of the @ref PgSqlHostDataSource.
class PgSqlHostDataSourceImpl {
public:

    /// @brief Statement Tags
    ///
    /// The contents of the enum are indexes into the list of SQL statements.
    /// It is assumed that the order is such that the indices of statements
    /// reading the database are less than those of statements modifying the
    /// database.
    /// @note: please add new statements doing read only operations before
    /// the WRITE_STMTS_BEGIN position.
    enum StatementIndex {
        GET_HOST_DHCPID,           // Gets hosts by host identifier
        GET_HOST_ADDR,             // Gets hosts by IPv4 address
        GET_HOST_SUBID4_DHCPID,    // Gets host by IPv4 SubnetID, HW address/DUID
        GET_HOST_SUBID6_DHCPID,    // Gets host by IPv6 SubnetID, HW address/DUID
        GET_HOST_SUBID_ADDR,       // Gets host by IPv4 SubnetID and IPv4 address
        GET_HOST_PREFIX,           // Gets host by IPv6 prefix
        GET_HOST_SUBID6_ADDR,      // Gets host by IPv6 SubnetID and IPv6 prefix
        GET_HOST_SUBID4,           // Gets hosts by IPv4 SubnetID
        GET_HOST_SUBID6,           // Gets hosts by IPv6 SubnetID
        GET_HOST_HOSTNAME,         // Gets hosts by hostname
        GET_HOST_HOSTNAME_SUBID4,  // Gets hosts by hostname and IPv4 SubnetID
        GET_HOST_HOSTNAME_SUBID6,  // Gets hosts by hostname and IPv6 SubnetID
        GET_HOST_SUBID4_PAGE,      // Gets hosts by IPv4 SubnetID beginning by HID
        GET_HOST_SUBID6_PAGE,      // Gets hosts by IPv6 SubnetID beginning by HID
        GET_HOST_PAGE4,            // Gets v4 hosts beginning by HID
        GET_HOST_PAGE6,            // Gets v6 hosts beginning by HID
        INSERT_HOST_NON_UNIQUE_IP, // Insert new host to collection with allowing IP duplicates
        INSERT_HOST_UNIQUE_IP,     // Insert new host to collection with checking for IP duplicates
        INSERT_V6_RESRV_NON_UNIQUE,// Insert v6 reservation without checking that it is unique
        INSERT_V6_RESRV_UNIQUE,    // Insert v6 reservation with checking that it is unique
        INSERT_V4_HOST_OPTION,     // Insert DHCPv4 option
        INSERT_V6_HOST_OPTION,     // Insert DHCPv6 option
        DEL_HOST_ADDR4,            // Delete v4 host (subnet-id, addr4)
        DEL_HOST_ADDR6,            // Delete v6 host (subnet-id, addr6)
        DEL_HOST_SUBID4_ID,        // Delete v4 host (subnet-id, ident.type, identifier)
        DEL_HOST_SUBID6_ID,        // Delete v6 host (subnet-id, ident.type, identifier)
        NUM_STATEMENTS             // Number of statements
    };

    /// @brief Index of first statement performing write to the database.
    ///
    /// This value is used to mark border line between queries and other
    /// statements and statements performing write operation on the database,
    /// such as INSERT, DELETE, UPDATE.
    static const StatementIndex WRITE_STMTS_BEGIN = INSERT_HOST_NON_UNIQUE_IP;

    /// @brief Constructor.
    ///
    /// This constructor opens database connection and initializes prepared
    /// statements used in the queries.
    PgSqlHostDataSourceImpl(const DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor.
    ~PgSqlHostDataSourceImpl();

    /// @brief Attempts to reconnect the server to the host DB backend manager.
    ///
    /// This is a self-rescheduling function that attempts to reconnect to the
    /// server's host DB backends after connectivity to one or more have been
    /// lost. Upon entry it will attempt to reconnect via
    /// @ref HostDataSourceFactory::add.
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
    /// This function is passed to the connection recovery mechanism. It will be
    /// invoked when a connection loss is detected.
    ///
    /// @param db_reconnect_ctl pointer to the ReconnectCtl containing the
    /// configured reconnect parameters.
    /// @return true if connection has been recovered, false otherwise.
    static bool dbReconnect(ReconnectCtlPtr db_reconnect_ctl);

    /// @brief Create a new context.
    ///
    /// The database is opened with all the SQL commands pre-compiled.
    ///
    /// @return A new (never null) context.
    ///
    /// @throw isc::dhcp::NoDatabaseName Mandatory database name not given.
    /// @throw isc::db::DbOperationError An operation on the open database has
    /// failed.
    PgSqlHostContextPtr createContext() const;

    /// @brief Executes statements which insert a row into one of the tables.
    ///
    /// @param ctx Context
    /// @param stindex Index of a statement being executed.
    /// @param bind Vector of PgsqlBindArray objects to be used for the query
    /// @param return_last_id flag indicating whether or not the insert
    /// returns the primary key of from the row inserted via " RETURNING
    /// <primary key> as pid" clause on the INSERT statement.  The RETURNING
    /// clause causes the INSERT to return a result set that should consist
    /// of a single row with one column, the value of the primary key.
    /// Defaults to false.
    ///
    /// @return 0 if return_last_id is false, otherwise it returns the
    /// the value in the result set in the first col of the first row.
    ///
    /// @throw isc::db::DuplicateEntry Database throws duplicate entry error
    uint64_t addStatement(PgSqlHostContextPtr& ctx,
                          PgSqlHostDataSourceImpl::StatementIndex stindex,
                          PsqlBindArrayPtr& bind,
                          const bool return_last_id = false);

    /// @brief Executes statements that delete records.
    ///
    /// @param ctx Context
    /// @param stindex Index of a statement being executed.
    /// @param bind pointer to PsqlBindArray objects to be used for the query
    ///
    /// @return true if any records were deleted, false otherwise
    bool delStatement(PgSqlHostContextPtr& ctx,
                      PgSqlHostDataSourceImpl::StatementIndex stindex,
                      PsqlBindArrayPtr& bind);

    /// @brief Inserts IPv6 Reservation into ipv6_reservation table.
    ///
    /// @param ctx Context
    /// @param resv IPv6 Reservation to be added
    /// @param id ID of a host owning this reservation
    void addResv(PgSqlHostContextPtr& ctx,
                 const IPv6Resrv& resv,
                 const HostID& id);

    /// @brief Inserts a single DHCP option into the database.
    ///
    /// @param ctx Context
    /// @param stindex Index of a statement being executed.
    /// @param opt_desc Option descriptor holding information about an option
    /// to be inserted into the database.
    /// @param opt_space Option space name.
    /// @param subnet_id Subnet identifier.
    /// @param host_id Host identifier.
    void addOption(PgSqlHostContextPtr& ctx,
                   const PgSqlHostDataSourceImpl::StatementIndex& stindex,
                   const OptionDescriptor& opt_desc,
                   const std::string& opt_space,
                   const Optional<SubnetID>& subnet_id,
                   const HostID& host_id);

    /// @brief Inserts multiple options into the database.
    ///
    /// @param ctx Context
    /// @param stindex Index of a statement being executed.
    /// @param options_cfg An object holding a collection of options to be
    /// inserted into the database.
    /// @param host_id Host identifier retrieved using getColumnValue
    ///                in addStatement method
    void addOptions(PgSqlHostContextPtr& ctx,
                    const StatementIndex& stindex,
                    const ConstCfgOptionPtr& options_cfg,
                    const uint64_t host_id);

    /// @brief Creates collection of @ref Host objects with associated
    /// information such as IPv6 reservations and/or DHCP options.
    ///
    /// This method performs a query which returns host information from
    /// the 'hosts' table. The query may also use LEFT JOIN clause to
    /// retrieve information from other tables, e.g. ipv6_reservations,
    /// dhcp4_options and dhcp6_options.
    /// Whether IPv6 reservations and/or options are assigned to the
    /// @ref Host objects depends on the type of the exchange object.
    ///
    /// @param ctx Context
    /// @param stindex Statement index.
    /// @param bind Pointer to an array of PgSQL bindings.
    /// @param exchange Pointer to the exchange object used for the
    /// particular query.
    /// @param [out] result Reference to the collection of hosts returned.
    /// @param single A boolean value indicating if a single host is
    /// expected to be returned, or multiple hosts.
    void getHostCollection(PgSqlHostContextPtr& ctx,
                           StatementIndex stindex,
                           PsqlBindArrayPtr bind,
                           boost::shared_ptr<PgSqlHostExchange> exchange,
                           ConstHostCollection& result,
                           bool single) const;

    /// @brief Retrieves a host by subnet and client's unique identifier.
    ///
    /// This method is used by both PgSqlHostDataSource::get4 and
    /// PgSqlHostDataSource::get6 methods.
    ///
    /// @param ctx Context
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a beginning of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @param stindex Statement index.
    /// @param exchange Pointer to the exchange object used for the
    /// particular query.
    ///
    /// @return Pointer to const instance of Host or null pointer if
    /// no host found.
    ConstHostPtr getHost(PgSqlHostContextPtr& ctx,
                         const SubnetID& subnet_id,
                         const Host::IdentifierType& identifier_type,
                         const uint8_t* identifier_begin,
                         const size_t identifier_len,
                         StatementIndex stindex,
                         boost::shared_ptr<PgSqlHostExchange> exchange) const;

    /// @brief Throws exception if database is read only.
    ///
    /// This method should be called by the methods which write to the
    /// database. If the backend is operating in read-only mode this
    /// method will throw exception.
    ///
    /// @param ctx Context
    ///
    /// @throw DbReadOnly if backend is operating in read only mode.
    void checkReadOnly(PgSqlHostContextPtr& ctx) const;

    /// @brief Returns PostgreSQL schema version of the open database
    ///
    /// @return Version number stored in the database, as a pair of unsigned
    ///         integers. "first" is the major version number, "second" the
    ///         minor number.
    ///
    /// @throw isc::db::DbOperationError An operation on the open database
    ///        has failed.
    std::pair<uint32_t, uint32_t> getVersion() const;

    /// @brief The parameters
    DatabaseConnection::ParameterMap parameters_;

    /// @brief Holds the setting whether the IP reservations must be unique or
    /// may be non-unique.
    bool ip_reservations_unique_;

    /// @brief The pool of contexts
    PgSqlHostContextPoolPtr pool_;

    /// @brief Indicates if there is at least one connection that can no longer
    /// be used for normal operations.
    bool unusable_;

    /// @brief Timer name used to register database reconnect timer.
    std::string timer_name_;
};

namespace {

/// @brief Array of tagged statements.
typedef boost::array<PgSqlTaggedStatement, PgSqlHostDataSourceImpl::NUM_STATEMENTS>
TaggedStatementArray;

/// @brief Prepared PosgreSQL statements used by the backend to insert and
/// retrieve reservation data from the database.
TaggedStatementArray tagged_statements = { {
    // PgSqlHostDataSourceImpl::GET_HOST_DHCPID
    // Retrieves host information, IPv6 reservations and both DHCPv4 and
    // DHCPv6 options associated with the host. The LEFT JOIN clause is used
    // to retrieve information from 4 different tables using a single query.
    // Hence, this query returns multiple rows for a single host.
    {2,
     { OID_BYTEA, OID_INT2 },
     "get_host_dhcpid",
     "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
     "  h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, "
     "  h.hostname, h.dhcp4_client_classes, h.dhcp6_client_classes, "
     "  h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o4.option_id, o4.code, o4.value, o4.formatted_value, o4.space, "
     "  o4.persistent, o4.user_context, "
     "  o6.option_id, o6.code, o6.value, o6.formatted_value, o6.space, "
     "  o6.persistent, o6.user_context, "
     "  r.reservation_id, r.address, r.prefix_len, r.type, r.dhcp6_iaid "
     "FROM hosts AS h "
     "LEFT JOIN dhcp4_options AS o4 ON h.host_id = o4.host_id "
     "LEFT JOIN dhcp6_options AS o6 ON h.host_id = o6.host_id "
     "LEFT JOIN ipv6_reservations AS r ON h.host_id = r.host_id "
     "WHERE dhcp_identifier = $1 AND dhcp_identifier_type = $2 "
     "ORDER BY h.host_id, o4.option_id, o6.option_id, r.reservation_id"
    },

    // PgSqlHostDataSourceImpl::GET_HOST_ADDR
    // Retrieves host information along with the DHCPv4 options associated with
    // it. Left joining the dhcp4_options table results in multiple rows being
    // returned for the same host. The host is retrieved by IPv4 address.
    {1,
     { OID_INT8 },
     "get_host_addr",
     "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
     "  h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
     "  h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o.option_id, o.code, o.value, o.formatted_value, o.space, "
     "  o.persistent, o.user_context "
     "FROM hosts AS h "
     "LEFT JOIN dhcp4_options AS o ON h.host_id = o.host_id "
     "WHERE ipv4_address = $1 "
     "ORDER BY h.host_id, o.option_id"
    },

    // PgSqlHostDataSourceImpl::GET_HOST_SUBID4_DHCPID
    // Retrieves host information and DHCPv4 options using subnet identifier
    // and client's identifier. Left joining the dhcp4_options table results in
    // multiple rows being returned for the same host.
    {3,
     { OID_INT8, OID_INT2, OID_BYTEA },
     "get_host_subid4_dhcpid",
     "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
     "  h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
     "  h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o.option_id, o.code, o.value, o.formatted_value, o.space, "
     "  o.persistent, o.user_context "
     "FROM hosts AS h "
     "LEFT JOIN dhcp4_options AS o ON h.host_id = o.host_id "
     "WHERE h.dhcp4_subnet_id = $1 AND h.dhcp_identifier_type = $2 "
     "  AND h.dhcp_identifier = $3 "
     "ORDER BY h.host_id, o.option_id"
    },

    // PgSqlHostDataSourceImpl::GET_HOST_SUBID6_DHCPID
    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // associated with a host. The number of rows returned is a multiplication
    // of number of IPv6 reservations and DHCPv6 options.
    {3,
     { OID_INT8, OID_INT2, OID_BYTEA },
     "get_host_subid6_dhcpid",
     "SELECT h.host_id, h.dhcp_identifier, "
     "  h.dhcp_identifier_type, h.dhcp4_subnet_id, "
     "  h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
     "  h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o.option_id, o.code, o.value, o.formatted_value, o.space, "
     "  o.persistent, o.user_context, "
     "  r.reservation_id, r.address, r.prefix_len, r.type, r.dhcp6_iaid "
     "FROM hosts AS h "
     "LEFT JOIN dhcp6_options AS o ON h.host_id = o.host_id "
     "LEFT JOIN ipv6_reservations AS r ON h.host_id = r.host_id "
     "WHERE h.dhcp6_subnet_id = $1 AND h.dhcp_identifier_type = $2 "
     "  AND h.dhcp_identifier = $3 "
     "ORDER BY h.host_id, o.option_id, r.reservation_id"
    },

    // PgSqlHostDataSourceImpl::GET_HOST_SUBID_ADDR
    // Retrieves host information and DHCPv4 options for the host using subnet
    // identifier and IPv4 reservation. Left joining the dhcp4_options table
    // results in multiple rows being returned for the host. The number of
    // rows depends on the number of options defined for the host.
    {2,
     { OID_INT8, OID_INT8 },
     "get_host_subid_addr",
     "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
     "  h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
     "  h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o.option_id, o.code, o.value, o.formatted_value, o.space, "
     "  o.persistent, o.user_context "
     "FROM hosts AS h "
     "LEFT JOIN dhcp4_options AS o ON h.host_id = o.host_id "
     "WHERE h.dhcp4_subnet_id = $1 AND h.ipv4_address = $2 "
     "ORDER BY h.host_id, o.option_id"
    },

    // PgSqlHostDataSourceImpl::GET_HOST_PREFIX
    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // associated with a host using prefix and prefix length. This query
    // returns host information for a single host. However, multiple rows
    // are returned due to left joining IPv6 reservations and DHCPv6 options.
    // The number of rows returned is multiplication of number of existing
    // IPv6 reservations and DHCPv6 options.
    {2,
     { OID_VARCHAR, OID_INT2 },
     "get_host_prefix",
     "SELECT h.host_id, h.dhcp_identifier, "
     "  h.dhcp_identifier_type, h.dhcp4_subnet_id, "
     "  h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
     "  h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o.option_id, o.code, o.value, o.formatted_value, o.space, "
     "  o.persistent, o.user_context, "
     "  r.reservation_id, r.address, r.prefix_len, r.type, "
     "  r.dhcp6_iaid "
     "FROM hosts AS h "
     "LEFT JOIN dhcp6_options AS o ON h.host_id = o.host_id "
     "LEFT JOIN ipv6_reservations AS r ON h.host_id = r.host_id "
     "WHERE h.host_id = "
     "  (SELECT host_id FROM ipv6_reservations "
     "   WHERE address = $1 AND prefix_len = $2) "
     "ORDER BY h.host_id, o.option_id, r.reservation_id"
    },

    // PgSqlHostDataSourceImpl::GET_HOST_SUBID6_ADDR
    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // associated with a host using IPv6 subnet id and prefix. This query
    // returns host information for a single host. However, multiple rows
    // are returned due to left joining IPv6 reservations and DHCPv6 options.
    // The number of rows returned is multiplication of number of existing
    // IPv6 reservations and DHCPv6 options.
    {2,
     { OID_INT8, OID_VARCHAR },
     "get_host_subid6_addr",
     "SELECT h.host_id, h.dhcp_identifier, "
     "  h.dhcp_identifier_type, h.dhcp4_subnet_id, "
     "  h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
     "  h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o.option_id, o.code, o.value, o.formatted_value, o.space, "
     "  o.persistent, o.user_context, "
     "  r.reservation_id, r.address, r.prefix_len, r.type, "
     "  r.dhcp6_iaid "
     "FROM hosts AS h "
     "LEFT JOIN dhcp6_options AS o ON h.host_id = o.host_id "
     "LEFT JOIN ipv6_reservations AS r ON h.host_id = r.host_id "
     "WHERE h.dhcp6_subnet_id = $1 AND r.address = $2 "
     "ORDER BY h.host_id, o.option_id, r.reservation_id"
    },

    // PgSqlHostDataSourceImpl::GET_HOST_SUBID4
    //
    // Retrieves host information for all hosts in a subnet, along with the
    // DHCPv4 options associated with it. Left joining the dhcp4_options table
    // results in multiple rows being returned for the same host. The hosts are
    // retrieved by subnet id.
    {1,
     { OID_INT8 },
     "get_host_subid4",
     "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
     "  h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
     "  h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o.option_id, o.code, o.value, o.formatted_value, o.space, "
     "  o.persistent, o.user_context "
     "FROM hosts AS h "
     "LEFT JOIN dhcp4_options AS o ON h.host_id = o.host_id "
     "WHERE h.dhcp4_subnet_id = $1 "
     "ORDER BY h.host_id, o.option_id"
    },

    // PgSqlHostDataSourceImpl::GET_HOST_SUBID6
    //
    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // associated with all hosts using the IPv6 subnet id. This query returns
    // host information for many hosts. However, multiple rows are
    // returned due to left joining IPv6 reservations and DHCPv6 options.
    // The number of rows returned is multiplication of number of existing
    // IPv6 reservations and DHCPv6 options for each host in a subnet. There
    // are usually many hosts in a subnet. The amount of returned data may
    // be huge.
    {1,
     { OID_INT8 },
     "get_host_subid6",
     "SELECT h.host_id, h.dhcp_identifier, "
     "  h.dhcp_identifier_type, h.dhcp4_subnet_id, "
     "  h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
     "  h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o.option_id, o.code, o.value, o.formatted_value, o.space, "
     "  o.persistent, o.user_context, "
     "  r.reservation_id, r.address, r.prefix_len, r.type, r.dhcp6_iaid "
     "FROM hosts AS h "
     "LEFT JOIN dhcp6_options AS o ON h.host_id = o.host_id "
     "LEFT JOIN ipv6_reservations AS r ON h.host_id = r.host_id "
     "WHERE h.dhcp6_subnet_id = $1 "
     "ORDER BY h.host_id, o.option_id, r.reservation_id"
    },

    // PgSqlHostDataSourceImpl::GET_HOST_HOSTNAME
    // Retrieves host information, IPv6 reservations and both DHCPv4 and
    // DHCPv6 options associated with all hosts using the hostname.
    // The LEFT JOIN clause is used to retrieve information from 4 different
    // tables using a single query. Hence, this query returns multiple rows
    // for a single host.
    {1,
     { OID_VARCHAR },
     "get_host_hostname",
     "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
     "  h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, "
     "  h.hostname, h.dhcp4_client_classes, h.dhcp6_client_classes, "
     "  h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o4.option_id, o4.code, o4.value, o4.formatted_value, o4.space, "
     "  o4.persistent, o4.user_context, "
     "  o6.option_id, o6.code, o6.value, o6.formatted_value, o6.space, "
     "  o6.persistent, o6.user_context, "
     "  r.reservation_id, r.address, r.prefix_len, r.type, r.dhcp6_iaid "
     "FROM hosts AS h "
     "LEFT JOIN dhcp4_options AS o4 ON h.host_id = o4.host_id "
     "LEFT JOIN dhcp6_options AS o6 ON h.host_id = o6.host_id "
     "LEFT JOIN ipv6_reservations AS r ON h.host_id = r.host_id "
     "WHERE lower(h.hostname) = $1 "
     "ORDER BY h.host_id, o4.option_id, o6.option_id, r.reservation_id"
    },

    // PgSqlHostDataSourceImpl::GET_HOST_HOSTNAME_SUBID4
    // Retrieves host information for all hosts with a hostname in a subnet,
    // along with the DHCPv4 options associated with it. Left joining
    // the dhcp4_options table results in multiple rows being returned for
    // the same host.
    {2,
     { OID_VARCHAR, OID_INT8 },
     "get_host_hostname_subid4",
     "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
     "  h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
     "  h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o.option_id, o.code, o.value, o.formatted_value, o.space, "
     "  o.persistent, o.user_context "
     "FROM hosts AS h "
     "LEFT JOIN dhcp4_options AS o ON h.host_id = o.host_id "
     "WHERE lower(h.hostname) = $1 AND h.dhcp4_subnet_id = $2 "
     "ORDER BY h.host_id, o.option_id"
    },

    // PgSqlHostDataSourceImpl::GET_HOST_HOSTNAME_SUBID6
    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // associated with all hosts using the hostname and the IPv6 subnet id.
    // This query returns host information for many hosts. However, multiple
    // rows are returned due to left joining IPv6 reservations and DHCPv6
    // options. The number of rows returned is multiplication of number of
    // existing IPv6 reservations and DHCPv6 options for each host in a subnet.
    {2,
     { OID_VARCHAR, OID_INT8 },
     "get_host_hostname_subid6",
     "SELECT h.host_id, h.dhcp_identifier, "
     "  h.dhcp_identifier_type, h.dhcp4_subnet_id, "
     "  h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
     "  h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o.option_id, o.code, o.value, o.formatted_value, o.space, "
     "  o.persistent, o.user_context, "
     "  r.reservation_id, r.address, r.prefix_len, r.type, r.dhcp6_iaid "
     "FROM hosts AS h "
     "LEFT JOIN dhcp6_options AS o ON h.host_id = o.host_id "
     "LEFT JOIN ipv6_reservations AS r ON h.host_id = r.host_id "
     "WHERE lower(h.hostname) = $1 AND h.dhcp6_subnet_id = $2 "
     "ORDER BY h.host_id, o.option_id, r.reservation_id"
    },

    // PgSqlHostDataSourceImpl::GET_HOST_SUBID4_PAGE
    // Retrieves host information along with the DHCPv4 options associated with
    // it. Left joining the dhcp4_options table results in multiple rows being
    // returned for the same host. The hosts are retrieved by subnet id,
    // starting from specified host id. Specified number of hosts is returned.
    {3,
     { OID_INT8, OID_INT8, OID_INT8 },
     "get_host_subid4_page",
     "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
     "  h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
     "  h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o.option_id, o.code, o.value, o.formatted_value, o.space, "
     "  o.persistent, o.user_context "
     "FROM ( SELECT * FROM hosts AS h "
     "       WHERE h.dhcp4_subnet_id = $1 AND h.host_id > $2 "
     "       ORDER BY h.host_id "
     "       LIMIT $3 ) AS h "
     "LEFT JOIN dhcp4_options AS o ON h.host_id = o.host_id "
     "ORDER BY h.host_id, o.option_id"
    },

    // PgSqlHostDataSourceImpl::GET_HOST_SUBID6_PAGE
    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // associated with a host using IPv6 subnet id. This query returns
    // host information for a single host. However, multiple rows are
    // returned due to left joining IPv6 reservations and DHCPv6 options.
    // The number of rows returned is multiplication of number of existing
    // IPv6 reservations and DHCPv6 options.
    {3,
     { OID_INT8, OID_INT8, OID_INT8 },
     "get_host_subid6_page",
     "SELECT h.host_id, h.dhcp_identifier, "
     "  h.dhcp_identifier_type, h.dhcp4_subnet_id, "
     "  h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
     "  h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o.option_id, o.code, o.value, o.formatted_value, o.space, "
     "  o.persistent, o.user_context, "
     "  r.reservation_id, r.address, r.prefix_len, r.type, r.dhcp6_iaid "
     "FROM ( SELECT * FROM hosts AS h "
     "       WHERE h.dhcp6_subnet_id = $1 AND h.host_id > $2 "
     "       ORDER BY h.host_id "
     "       LIMIT $3 ) AS h "
     "LEFT JOIN dhcp6_options AS o ON h.host_id = o.host_id "
     "LEFT JOIN ipv6_reservations AS r ON h.host_id = r.host_id "
     "ORDER BY h.host_id, o.option_id, r.reservation_id"
    },

    // PgSqlHostDataSourceImpl::GET_HOST_PAGE4
    // Retrieves host information along with the DHCPv4 options associated with
    // it. Left joining the dhcp4_options table results in multiple rows being
    // returned for the same host. The hosts are retrieved starting from
    // specified host id. Specified number of hosts is returned.
    {2,
     { OID_INT8, OID_INT8 },
     "get_host_page4",
     "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
     "  h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
     "  h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o.option_id, o.code, o.value, o.formatted_value, o.space, "
     "  o.persistent, o.user_context "
     "FROM ( SELECT * FROM hosts AS h "
     "       WHERE h.host_id > $1 "
     "       ORDER BY h.host_id "
     "       LIMIT $2 ) AS h "
     "LEFT JOIN dhcp4_options AS o ON h.host_id = o.host_id "
     "ORDER BY h.host_id, o.option_id"
    },

    // PgSqlHostDataSourceImpl::GET_HOST_PAGE6
    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // associated with a host using IPv6 subnet id. This query returns
    // host information for a single host. However, multiple rows are
    // returned due to left joining IPv6 reservations and DHCPv6 options.
    // The number of rows returned is multiplication of number of existing
    // IPv6 reservations and DHCPv6 options.
    {2,
     { OID_INT8, OID_INT8 },
     "get_host_page6",
     "SELECT h.host_id, h.dhcp_identifier, "
     "  h.dhcp_identifier_type, h.dhcp4_subnet_id, "
     "  h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
     "  h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
     "  h.dhcp4_next_server, h.dhcp4_server_hostname, "
     "  h.dhcp4_boot_file_name, h.auth_key, "
     "  o.option_id, o.code, o.value, o.formatted_value, o.space, "
     "  o.persistent, o.user_context, "
     "  r.reservation_id, r.address, r.prefix_len, r.type, r.dhcp6_iaid "
     "FROM ( SELECT * FROM hosts AS h "
     "       WHERE h.host_id > $1 "
     "       ORDER BY h.host_id "
     "       LIMIT $2 ) AS h "
     "LEFT JOIN dhcp6_options AS o ON h.host_id = o.host_id "
     "LEFT JOIN ipv6_reservations AS r ON h.host_id = r.host_id "
     "ORDER BY h.host_id, o.option_id, r.reservation_id"
    },

    // PgSqlHostDataSourceImpl::INSERT_HOST_NON_UNIQUE_IP
    // Inserts a host into the 'hosts' table without checking that there is
    // a reservation for the IP address.
    {13,
     { OID_BYTEA, OID_INT2,
       OID_INT8, OID_INT8, OID_INT8, OID_VARCHAR,
       OID_VARCHAR, OID_VARCHAR, OID_TEXT,
       OID_INT8, OID_VARCHAR, OID_VARCHAR, OID_VARCHAR},
     "insert_host_non_unique_ip",
     "INSERT INTO hosts(dhcp_identifier, dhcp_identifier_type, "
     "  dhcp4_subnet_id, dhcp6_subnet_id, ipv4_address, hostname, "
     "  dhcp4_client_classes, dhcp6_client_classes, user_context, "
     "  dhcp4_next_server, dhcp4_server_hostname, dhcp4_boot_file_name, auth_key)"
     "VALUES ( $1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13 ) "
     "RETURNING host_id"
    },

    // PgSqlHostDataSourceImpl::INSERT_HOST_UNIQUE_IP
    // Inserts a host into the 'hosts' table with checking that reserved IP
    // address is unique. The innermost query checks if there is at least
    // one host for the given IP/subnet combination. For checking whether
    // hosts exists or not it doesn't matter if we select actual columns,
    // thus SELECT 1 was used as an optimization to avoid selecting data
    // that will be ignored anyway. If it does not exist the new host is
    // inserted. If the host with the given IP address already exists the
    // new host won't be inserted. The caller can check the number of
    // affected rows to detect that there was a duplicate host in the
    // database. Returns the inserted host id.
    {15,
     { OID_BYTEA, OID_INT2,
       OID_INT8, OID_INT8, OID_INT8, OID_VARCHAR,
       OID_VARCHAR, OID_VARCHAR, OID_TEXT,
       OID_INT8, OID_VARCHAR, OID_VARCHAR, OID_VARCHAR,
       OID_INT8, OID_INT8},
     "insert_host_unique_ip",
     "INSERT INTO hosts(dhcp_identifier, dhcp_identifier_type, "
     "  dhcp4_subnet_id, dhcp6_subnet_id, ipv4_address, hostname, "
     "  dhcp4_client_classes, dhcp6_client_classes, user_context, "
     "  dhcp4_next_server, dhcp4_server_hostname, dhcp4_boot_file_name, auth_key)"
     "  SELECT $1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13"
     "    WHERE NOT EXISTS ("
     "      SELECT 1 FROM hosts WHERE ipv4_address = $14 AND dhcp4_subnet_id = $15"
     "      LIMIT 1"
     "    ) "
     "RETURNING host_id"
    },

    // PgSqlHostDataSourceImpl::INSERT_V6_RESRV_NON_UNIQUE
    // Inserts a single IPv6 reservation into 'reservations' table without
    // checking that the inserted reservation is unique.
    {5,
     { OID_VARCHAR, OID_INT2, OID_INT4, OID_INT4, OID_INT4 },
     "insert_v6_resrv_non_unique",
     "INSERT INTO ipv6_reservations(address, prefix_len, type, "
     "  dhcp6_iaid, host_id) "
     "VALUES ($1, $2, $3, $4, $5)"
    },

    // PgSqlHostDataSourceImpl::INSERT_V6_RESRV_UNIQUE
    // Inserts a single IPv6 reservation into 'reservations' table with
    // checking that the inserted reservation is unique.
    {7,
     { OID_VARCHAR, OID_INT2, OID_INT4, OID_INT4, OID_INT4, OID_VARCHAR, OID_INT2 },
     "insert_v6_resrv_unique",
     "INSERT INTO ipv6_reservations(address, prefix_len, type, "
     "  dhcp6_iaid, host_id) "
     "SELECT $1, $2, $3, $4, $5 "
     "  WHERE NOT EXISTS ("
     "      SELECT 1 FROM ipv6_reservations"
     "          WHERE address = $6 AND prefix_len = $7"
     "      LIMIT 1"
     "  )"
    },

    // PgSqlHostDataSourceImpl::INSERT_V4_HOST_OPTION
    // Inserts a single DHCPv4 option into 'dhcp4_options' table.
    // Using fixed scope_id = 3, which associates an option with host.
    {7,
     { OID_INT2, OID_BYTEA, OID_TEXT,
       OID_VARCHAR, OID_BOOL, OID_TEXT, OID_INT8 },
     "insert_v4_host_option",
     "INSERT INTO dhcp4_options(code, value, formatted_value, space, "
     "  persistent, user_context, host_id, scope_id) "
     "VALUES ($1, $2, $3, $4, $5, $6, $7, 3)"
    },

    // PgSqlHostDataSourceImpl::INSERT_V6_HOST_OPTION
    // Inserts a single DHCPv6 option into 'dhcp6_options' table.
    // Using fixed scope_id = 3, which associates an option with host.
    {7,
     { OID_INT2, OID_BYTEA, OID_TEXT,
       OID_VARCHAR, OID_BOOL, OID_TEXT, OID_INT8 },
     "insert_v6_host_option",
     "INSERT INTO dhcp6_options(code, value, formatted_value, space, "
     "  persistent, user_context, host_id, scope_id) "
     "VALUES ($1, $2, $3, $4, $5, $6, $7, 3)"
    },

    // PgSqlHostDataSourceImpl::DEL_HOST_ADDR4
    // Deletes a v4 host that matches (subnet-id, addr4)
    {2,
     { OID_INT8, OID_INT8 },
     "del_host_addr4",
     "DELETE FROM hosts WHERE dhcp4_subnet_id = $1 AND ipv4_address = $2"
    },

    // PgSqlHostDataSourceImpl::DEL_HOST_ADDR6
    // Deletes a v6 host that matches (subnet-id, addr6)
    {2,
     { OID_INT8, OID_VARCHAR },
     "del_host_addr6",
     "DELETE FROM hosts USING ipv6_reservations "
     "  WHERE dhcp6_subnet_id = $1 AND ipv6_reservations.address = $2"
    },

    // PgSqlHostDataSourceImpl::DEL_HOST_SUBID4_ID
    // Deletes a v4 host that matches (subnet4-id, identifier-type, identifier)
    {3,
     { OID_INT8, OID_INT2, OID_BYTEA },
     "del_host_subid4_id",
     "DELETE FROM hosts WHERE dhcp4_subnet_id = $1 "
     "AND dhcp_identifier_type = $2 "
     "AND dhcp_identifier = $3"
    },

    // PgSqlHostDataSourceImpl::DEL_HOST_SUBID6_ID
    // Deletes a v6 host that matches (subnet6-id, identifier-type, identifier)
    {3,
     { OID_INT8, OID_INT2, OID_BYTEA },
     "del_host_subid6_id",
     "DELETE FROM hosts WHERE dhcp6_subnet_id = $1 "
     "AND dhcp_identifier_type = $2 "
     "AND dhcp_identifier = $3"
    }
}
};

}  // namespace

// PgSqlHostContext Constructor

PgSqlHostContext::PgSqlHostContext(const DatabaseConnection::ParameterMap& parameters,
                                   IOServiceAccessorPtr io_service_accessor,
                                   db::DbCallback db_reconnect_callback)
    : conn_(parameters, io_service_accessor, db_reconnect_callback),
      is_readonly_(true) {
}

// PgSqlHostContextAlloc Constructor and Destructor

PgSqlHostDataSource::PgSqlHostContextAlloc::PgSqlHostContextAlloc(
    PgSqlHostDataSourceImpl& mgr) : ctx_(), mgr_(mgr) {

    if (MultiThreadingMgr::instance().getMode()) {
        // multi-threaded
        {
            // we need to protect the whole pool_ operation, hence extra scope {}
            lock_guard<mutex> lock(mgr_.pool_->mutex_);
            if (!mgr_.pool_->pool_.empty()) {
                ctx_ = mgr_.pool_->pool_.back();
                mgr_.pool_->pool_.pop_back();
            }
        }
        if (!ctx_) {
            ctx_ = mgr_.createContext();
        }
    } else {
        // single-threaded
        if (mgr_.pool_->pool_.empty()) {
            isc_throw(Unexpected, "No available PostgreSQL host context?!");
        }
        ctx_ = mgr_.pool_->pool_.back();
    }
}

PgSqlHostDataSource::PgSqlHostContextAlloc::~PgSqlHostContextAlloc() {
    if (MultiThreadingMgr::instance().getMode()) {
        // multi-threaded
        lock_guard<mutex> lock(mgr_.pool_->mutex_);
        mgr_.pool_->pool_.push_back(ctx_);
        if (ctx_->conn_.isUnusable()) {
            mgr_.unusable_ = true;
        }
    } else if (ctx_->conn_.isUnusable()) {
        mgr_.unusable_ = true;
    }
}

PgSqlHostDataSourceImpl::PgSqlHostDataSourceImpl(const DatabaseConnection::ParameterMap& parameters)
    : parameters_(parameters), ip_reservations_unique_(true), unusable_(false),
      timer_name_("") {

    // Create unique timer name per instance.
    timer_name_ = "PgSqlHostMgr[";
    timer_name_ += boost::lexical_cast<std::string>(reinterpret_cast<uint64_t>(this));
    timer_name_ += "]DbReconnectTimer";

    // Validate the schema version first.
    std::pair<uint32_t, uint32_t> code_version(PG_SCHEMA_VERSION_MAJOR,
                                               PG_SCHEMA_VERSION_MINOR);
    std::pair<uint32_t, uint32_t> db_version = getVersion();
    if (code_version != db_version) {
        isc_throw(DbOpenError,
                  "PostgreSQL schema version mismatch: need version: "
                      << code_version.first << "." << code_version.second
                      << " found version: " << db_version.first << "."
                      << db_version.second);
    }

    // Create an initial context.
    pool_.reset(new PgSqlHostContextPool());
    pool_->pool_.push_back(createContext());
}

// Create context.

PgSqlHostContextPtr
PgSqlHostDataSourceImpl::createContext() const {
    PgSqlHostContextPtr ctx(new PgSqlHostContext(parameters_,
        IOServiceAccessorPtr(new IOServiceAccessor(&HostMgr::getIOService)),
        &PgSqlHostDataSourceImpl::dbReconnect));

    // Open the database.
    ctx->conn_.openDatabase();

    // Now prepare the SQL statements.
    ctx->conn_.prepareStatements(tagged_statements.begin(),
                                 tagged_statements.begin() + WRITE_STMTS_BEGIN);

    // Check if the backend is explicitly configured to operate with
    // read only access to the database.
    ctx->is_readonly_ = ctx->conn_.configuredReadOnly();

    // If we are using read-write mode for the database we also prepare
    // statements for INSERTS etc.
    if (!ctx->is_readonly_) {
        ctx->conn_.prepareStatements(tagged_statements.begin() + WRITE_STMTS_BEGIN,
                                     tagged_statements.end());
    } else {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_PGSQL_HOST_DB_READONLY);
    }

    ctx->host_ipv4_exchange_.reset(new PgSqlHostWithOptionsExchange(PgSqlHostWithOptionsExchange::DHCP4_ONLY));
    ctx->host_ipv6_exchange_.reset(new PgSqlHostIPv6Exchange(PgSqlHostWithOptionsExchange::DHCP6_ONLY));
    ctx->host_ipv46_exchange_.reset(new PgSqlHostIPv6Exchange(PgSqlHostWithOptionsExchange::DHCP4_AND_DHCP6));
    ctx->host_ipv6_reservation_exchange_.reset(new PgSqlIPv6ReservationExchange());
    ctx->host_option_exchange_.reset(new PgSqlOptionExchange());

    // Create ReconnectCtl for this connection.
    ctx->conn_.makeReconnectCtl(timer_name_);

    return (ctx);
}

PgSqlHostDataSourceImpl::~PgSqlHostDataSourceImpl() {
}

bool
PgSqlHostDataSourceImpl::dbReconnect(ReconnectCtlPtr db_reconnect_ctl) {
    MultiThreadingCriticalSection cs;

    // Invoke application layer connection lost callback.
    if (!DatabaseConnection::invokeDbLostCallback(db_reconnect_ctl)) {
        return (false);
    }

    bool reopened = false;

    const std::string timer_name = db_reconnect_ctl->timerName();

    // At least one connection was lost.
    try {
        CfgDbAccessPtr cfg_db = CfgMgr::instance().getCurrentCfg()->getCfgDbAccess();
        std::list<std::string> host_db_access_list = cfg_db->getHostDbAccessStringList();
        for (std::string& hds : host_db_access_list) {
            auto parameters = DatabaseConnection::parse(hds);
            if (HostMgr::delBackend("postgresql", hds, true)) {
                HostMgr::addBackend(hds);
            }
        }
        reopened = true;
    } catch (const std::exception& ex) {
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_PGSQL_HOST_DB_RECONNECT_ATTEMPT_FAILED)
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
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_PGSQL_HOST_DB_RECONNECT_FAILED)
                    .arg(db_reconnect_ctl->maxRetries());

            // Cancel the timer.
            if (TimerMgr::instance()->isTimerRegistered(timer_name)) {
                TimerMgr::instance()->unregisterTimer(timer_name);
            }

            // Invoke application layer connection failed callback.
            DatabaseConnection::invokeDbFailedCallback(db_reconnect_ctl);
            return (false);
        }

        LOG_INFO(dhcpsrv_logger, DHCPSRV_PGSQL_HOST_DB_RECONNECT_ATTEMPT_SCHEDULE)
                .arg(db_reconnect_ctl->maxRetries() - db_reconnect_ctl->retriesLeft() + 1)
                .arg(db_reconnect_ctl->maxRetries())
                .arg(db_reconnect_ctl->retryInterval());

        // Start the timer.
        if (!TimerMgr::instance()->isTimerRegistered(timer_name)) {
            TimerMgr::instance()->registerTimer(timer_name,
                std::bind(&PgSqlHostDataSourceImpl::dbReconnect, db_reconnect_ctl),
                          db_reconnect_ctl->retryInterval(),
                          asiolink::IntervalTimer::ONE_SHOT);
        }
        TimerMgr::instance()->setup(timer_name);
    }

    return (true);
}

uint64_t
PgSqlHostDataSourceImpl::addStatement(PgSqlHostContextPtr& ctx,
                                      StatementIndex stindex,
                                      PsqlBindArrayPtr& bind_array,
                                      const bool return_last_id) {
    uint64_t last_id = 0;
    PgSqlResult r(PQexecPrepared(ctx->conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array->values_[0],
                                 &bind_array->lengths_[0],
                                 &bind_array->formats_[0], 0));

    int s = PQresultStatus(r);

    if (s != PGRES_COMMAND_OK) {
        // Failure: check for the special case of duplicate entry.
        if (ctx->conn_.compareError(r, PgSqlConnection::DUPLICATE_KEY)) {
            isc_throw(DuplicateEntry, "Database duplicate entry error");
        }

        // Connection determines if the error is fatal or not, and
        // throws the appropriate exception
        ctx->conn_.checkStatementError(r, tagged_statements[stindex]);
    }

    // Get the number of affected rows.
    char* rows_affected = PQcmdTuples(r);
    if (!rows_affected) {
        isc_throw(DbOperationError,
                  "Could not retrieve the number of affected rows.");
    }

    // If the number of rows inserted is 0 it means that the query detected
    // an attempt to insert duplicated data for which there is no unique
    // index in the database. Unique indexes are not created in the database
    // when it may be sometimes allowed to insert duplicated records per
    // server's configuration.
    if (rows_affected[0] == '0') {
        isc_throw(DuplicateEntry, "Database duplicate entry error");
    }

    if (return_last_id) {
        PgSqlExchange::getColumnValue(r, 0, 0, last_id);
    }

    return (last_id);
}

bool
PgSqlHostDataSourceImpl::delStatement(PgSqlHostContextPtr& ctx,
                                      StatementIndex stindex,
                                      PsqlBindArrayPtr& bind_array) {
    PgSqlResult r(PQexecPrepared(ctx->conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array->values_[0],
                                 &bind_array->lengths_[0],
                                 &bind_array->formats_[0], 0));

    int s = PQresultStatus(r);

    if (s != PGRES_COMMAND_OK) {
        // Connection determines if the error is fatal or not, and
        // throws the appropriate exception
        ctx->conn_.checkStatementError(r, tagged_statements[stindex]);
    }

    // Now check how many rows (hosts) were deleted. This should be either
    // "0" or "1".
    char* rows_deleted = PQcmdTuples(r);
    if (!rows_deleted) {
        isc_throw(DbOperationError,
                  "Could not retrieve the number of deleted rows.");
    }
    return (rows_deleted[0] != '0');
}

void
PgSqlHostDataSourceImpl::addResv(PgSqlHostContextPtr& ctx,
                                 const IPv6Resrv& resv,
                                 const HostID& id) {
    PsqlBindArrayPtr bind_array = ctx->host_ipv6_reservation_exchange_->
        createBindForSend(resv, id, ip_reservations_unique_);

    addStatement(ctx,
                 ip_reservations_unique_ ? INSERT_V6_RESRV_UNIQUE : INSERT_V6_RESRV_NON_UNIQUE,
                 bind_array);
}

void
PgSqlHostDataSourceImpl::addOption(PgSqlHostContextPtr& ctx,
                                   const StatementIndex& stindex,
                                   const OptionDescriptor& opt_desc,
                                   const std::string& opt_space,
                                   const Optional<SubnetID>&,
                                   const HostID& id) {
    PsqlBindArrayPtr bind_array = ctx->host_option_exchange_->createBindForSend(opt_desc, opt_space, id);

    addStatement(ctx, stindex, bind_array);
}

void
PgSqlHostDataSourceImpl::addOptions(PgSqlHostContextPtr& ctx,
                                    const StatementIndex& stindex,
                                    const ConstCfgOptionPtr& options_cfg,
                                    const uint64_t host_id) {
    // Get option space names and vendor space names and combine them within a
    // single list.
    std::list<std::string> option_spaces = options_cfg->getOptionSpaceNames();
    std::list<std::string> vendor_spaces = options_cfg->getVendorIdsSpaceNames();
    option_spaces.insert(option_spaces.end(), vendor_spaces.begin(),
                         vendor_spaces.end());

    // For each option space retrieve all options and insert them into the
    // database.
    for (auto space = option_spaces.begin(); space != option_spaces.end(); ++space) {
        OptionContainerPtr options = options_cfg->getAll(*space);
        if (options && !options->empty()) {
            for (auto opt = options->begin(); opt != options->end(); ++opt) {
                addOption(ctx, stindex, *opt, *space, Optional<SubnetID>(), host_id);
            }
        }
    }
}

void
PgSqlHostDataSourceImpl::getHostCollection(PgSqlHostContextPtr& ctx,
                                           StatementIndex stindex,
                                           PsqlBindArrayPtr bind_array,
                                           boost::shared_ptr<PgSqlHostExchange> exchange,
                                           ConstHostCollection& result,
                                           bool single) const {

    exchange->clear();
    PgSqlResult r(PQexecPrepared(ctx->conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array->values_[0],
                                 &bind_array->lengths_[0],
                                 &bind_array->formats_[0], 0));

    ctx->conn_.checkStatementError(r, tagged_statements[stindex]);

    int rows = r.getRows();
    for (int row = 0; row < rows; ++row) {
        exchange->processRowData(result, r, row);

        if (single && result.size() > 1) {
            isc_throw(MultipleRecords, "multiple records were found in the "
                      "database where only one was expected for query "
                      << tagged_statements[stindex].name);
        }
    }
}

ConstHostPtr
PgSqlHostDataSourceImpl::getHost(PgSqlHostContextPtr& ctx,
                                 const SubnetID& subnet_id,
                                 const Host::IdentifierType& identifier_type,
                                 const uint8_t* identifier_begin,
                                 const size_t identifier_len,
                                 StatementIndex stindex,
                                 boost::shared_ptr<PgSqlHostExchange> exchange) const {

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the subnet id.
    bind_array->add(subnet_id);

    // Add the Identifier type.
    bind_array->add(static_cast<uint8_t>(identifier_type));

    // Add the identifier value.
    bind_array->add(identifier_begin, identifier_len);

    ConstHostCollection collection;
    getHostCollection(ctx, stindex, bind_array, exchange, collection, true);

    // Return single record if present, else clear the host.
    ConstHostPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return (result);
}

std::pair<uint32_t, uint32_t>
PgSqlHostDataSourceImpl::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_HOST_DB_GET_VERSION);
    return (PgSqlConnection::getVersion(parameters_));
}

void
PgSqlHostDataSourceImpl::checkReadOnly(PgSqlHostContextPtr& ctx) const {
    if (ctx->is_readonly_) {
        isc_throw(ReadOnlyDb, "PostgreSQL host database backend is configured"
                  " to operate in read only mode");
    }
}

/*********** PgSqlHostDataSource *********************/

PgSqlHostDataSource::PgSqlHostDataSource(const DatabaseConnection::ParameterMap& parameters)
    : impl_(new PgSqlHostDataSourceImpl(parameters)) {
}

PgSqlHostDataSource::~PgSqlHostDataSource() {
}

DatabaseConnection::ParameterMap
PgSqlHostDataSource::getParameters() const {
    return (impl_->parameters_);
}

void
PgSqlHostDataSource::add(const HostPtr& host) {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // If operating in read-only mode, throw exception.
    impl_->checkReadOnly(ctx);

    // Initiate PostgreSQL transaction as we will have to make multiple queries
    // to insert host information into multiple tables. If that fails on
    // any stage, the transaction will be rolled back by the destructor of
    // the PgSqlTransaction class.
    PgSqlTransaction transaction(ctx->conn_);

    // If we're configured to check that an IP reservation within a given subnet
    // is unique, the IP reservation exists and the subnet is actually set
    // we will be using a special query that checks for uniqueness. Otherwise,
    // we will use a regular insert statement.
    bool unique_ip = impl_->ip_reservations_unique_ && !host->getIPv4Reservation().isV4Zero()
        && host->getIPv4SubnetID() != SUBNET_ID_UNUSED;

    // Create the PgSQL Bind array for the host
    PsqlBindArrayPtr bind_array = ctx->host_ipv4_exchange_->createBindForSend(host, unique_ip);

    // ... and insert the host.
    uint32_t host_id = impl_->addStatement(ctx,
                                           unique_ip ? PgSqlHostDataSourceImpl::INSERT_HOST_UNIQUE_IP :
                                           PgSqlHostDataSourceImpl::INSERT_HOST_NON_UNIQUE_IP,
                                           bind_array, true);

    // Insert DHCPv4 options.
    ConstCfgOptionPtr cfg_option4 = host->getCfgOption4();
    if (cfg_option4) {
        impl_->addOptions(ctx, PgSqlHostDataSourceImpl::INSERT_V4_HOST_OPTION,
                          cfg_option4, host_id);
    }

    // Insert DHCPv6 options.
    ConstCfgOptionPtr cfg_option6 = host->getCfgOption6();
    if (cfg_option6) {
        impl_->addOptions(ctx, PgSqlHostDataSourceImpl::INSERT_V6_HOST_OPTION,
                          cfg_option6, host_id);
    }

    // Insert IPv6 reservations.
    IPv6ResrvRange v6resv = host->getIPv6Reservations();
    if (std::distance(v6resv.first, v6resv.second) > 0) {
        for (IPv6ResrvIterator resv = v6resv.first; resv != v6resv.second;
             ++resv) {
            impl_->addResv(ctx, resv->second, host_id);
        }
    }

    // Everything went fine, so explicitly commit the transaction.
    transaction.commit();
}

bool
PgSqlHostDataSource::del(const SubnetID& subnet_id,
                         const asiolink::IOAddress& addr) {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // If operating in read-only mode, throw exception.
    impl_->checkReadOnly(ctx);

    PsqlBindArrayPtr bind_array(new PsqlBindArray());
    bind_array->add(subnet_id);

    // v4
    if (addr.isV4()) {
        bind_array->add(addr);
        return (impl_->delStatement(ctx, PgSqlHostDataSourceImpl::DEL_HOST_ADDR4,
                                    bind_array));
    }

    // v6
    bind_array->add(addr.toText());

    return (impl_->delStatement(ctx, PgSqlHostDataSourceImpl::DEL_HOST_ADDR6,
                                bind_array));
}

bool
PgSqlHostDataSource::del4(const SubnetID& subnet_id,
                          const Host::IdentifierType& identifier_type,
                          const uint8_t* identifier_begin,
                          const size_t identifier_len) {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // If operating in read-only mode, throw exception.
    impl_->checkReadOnly(ctx);

    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Subnet-id
    bind_array->add(subnet_id);

    // identifier-type
    bind_array->add(static_cast<uint8_t>(identifier_type));

    // identifier
    bind_array->add(identifier_begin, identifier_len);

    return (impl_->delStatement(ctx, PgSqlHostDataSourceImpl::DEL_HOST_SUBID4_ID,
                                bind_array));
}

bool
PgSqlHostDataSource::del6(const SubnetID& subnet_id,
                          const Host::IdentifierType& identifier_type,
                          const uint8_t* identifier_begin,
                          const size_t identifier_len) {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // If operating in read-only mode, throw exception.
    impl_->checkReadOnly(ctx);

    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Subnet-id
    bind_array->add(subnet_id);

    // identifier-type
    bind_array->add(static_cast<uint8_t>(identifier_type));

    // identifier
    bind_array->add(identifier_begin, identifier_len);

    return (impl_->delStatement(ctx, PgSqlHostDataSourceImpl::DEL_HOST_SUBID6_ID,
                                bind_array));
}

ConstHostCollection
PgSqlHostDataSource::getAll(const Host::IdentifierType& identifier_type,
                            const uint8_t* identifier_begin,
                            const size_t identifier_len) const {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Identifier value.
    bind_array->add(identifier_begin, identifier_len);

    // Identifier type.
    bind_array->add(static_cast<uint8_t>(identifier_type));

    ConstHostCollection result;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_DHCPID,
                             bind_array, ctx->host_ipv46_exchange_, result, false);

    return (result);
}

ConstHostCollection
PgSqlHostDataSource::getAll4(const SubnetID& subnet_id) const {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the subnet id.
    bind_array->add(subnet_id);

    ConstHostCollection result;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_SUBID4,
                             bind_array, ctx->host_ipv4_exchange_, result, false);

    return (result);
}

ConstHostCollection
PgSqlHostDataSource::getAll6(const SubnetID& subnet_id) const {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the subnet id.
    bind_array->add(subnet_id);

    ConstHostCollection result;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_SUBID6,
                             bind_array, ctx->host_ipv6_exchange_, result, false);

    return (result);
}

ConstHostCollection
PgSqlHostDataSource::getAllbyHostname(const std::string& hostname) const {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the hostname.
    bind_array->add(hostname);

    ConstHostCollection result;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_HOSTNAME,
                             bind_array, ctx->host_ipv46_exchange_, result, false);

    return (result);
}

ConstHostCollection
PgSqlHostDataSource::getAllbyHostname4(const std::string& hostname,
                                       const SubnetID& subnet_id) const {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the hostname.
    bind_array->add(hostname);

    // Add the subnet id.
    bind_array->add(subnet_id);

    ConstHostCollection result;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_HOSTNAME_SUBID4,
                             bind_array, ctx->host_ipv4_exchange_, result, false);

    return (result);
}

ConstHostCollection
PgSqlHostDataSource::getAllbyHostname6(const std::string& hostname,
                                       const SubnetID& subnet_id) const {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the hostname.
    bind_array->add(hostname);

    // Add the subnet id.
    bind_array->add(subnet_id);

    ConstHostCollection result;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_HOSTNAME_SUBID6,
                             bind_array, ctx->host_ipv6_exchange_, result, false);

    return (result);
}

ConstHostCollection
PgSqlHostDataSource::getPage4(const SubnetID& subnet_id,
                              size_t& /*source_index*/,
                              uint64_t lower_host_id,
                              const HostPageSize& page_size) const {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the subnet id.
    bind_array->add(subnet_id);

    // Add the lower bound host id.
    bind_array->add(lower_host_id);

    // Add the page size value.
    string page_size_data =
        boost::lexical_cast<std::string>(page_size.page_size_);
    bind_array->add(page_size_data);

    ConstHostCollection result;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_SUBID4_PAGE,
                             bind_array, ctx->host_ipv4_exchange_, result, false);

    return (result);
}

ConstHostCollection
PgSqlHostDataSource::getPage6(const SubnetID& subnet_id,
                              size_t& /*source_index*/,
                              uint64_t lower_host_id,
                              const HostPageSize& page_size) const {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the subnet id.
    bind_array->add(subnet_id);

    // Add the lower bound host id.
    bind_array->add(lower_host_id);

    // Add the page size value.
    string page_size_data =
        boost::lexical_cast<std::string>(page_size.page_size_);
    bind_array->add(page_size_data);

    ConstHostCollection result;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_SUBID6_PAGE,
                             bind_array, ctx->host_ipv6_exchange_, result, false);

    return (result);
}

ConstHostCollection
PgSqlHostDataSource::getPage4(size_t& /*source_index*/,
                              uint64_t lower_host_id,
                              const HostPageSize& page_size) const {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the lower bound host id.
    bind_array->add(lower_host_id);

    // Add the page size value.
    string page_size_data =
        boost::lexical_cast<std::string>(page_size.page_size_);
    bind_array->add(page_size_data);

    ConstHostCollection result;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_PAGE4,
                             bind_array, ctx->host_ipv4_exchange_, result, false);

    return (result);
}

ConstHostCollection
PgSqlHostDataSource::getPage6(size_t& /*source_index*/,
                              uint64_t lower_host_id,
                              const HostPageSize& page_size) const {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the lower bound host id.
    bind_array->add(lower_host_id);

    // Add the page size value.
    string page_size_data =
        boost::lexical_cast<std::string>(page_size.page_size_);
    bind_array->add(page_size_data);

    ConstHostCollection result;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_PAGE6,
                             bind_array, ctx->host_ipv6_exchange_, result, false);

    return (result);
}

ConstHostCollection
PgSqlHostDataSource::getAll4(const asiolink::IOAddress& address) const {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // v4 Reservation address
    bind_array->add(address);

    ConstHostCollection result;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_ADDR,
                             bind_array, ctx->host_ipv4_exchange_, result, false);

    return (result);
}

ConstHostPtr
PgSqlHostDataSource::get4(const SubnetID& subnet_id,
                          const Host::IdentifierType& identifier_type,
                          const uint8_t* identifier_begin,
                          const size_t identifier_len) const {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    return (impl_->getHost(ctx, subnet_id, identifier_type, identifier_begin, identifier_len,
                           PgSqlHostDataSourceImpl::GET_HOST_SUBID4_DHCPID,
                           ctx->host_ipv4_exchange_));
}

ConstHostPtr
PgSqlHostDataSource::get4(const SubnetID& subnet_id,
                          const asiolink::IOAddress& address) const {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    if (!address.isV4()) {
        isc_throw(BadValue, "PgSqlHostDataSource::get4(id, address) - "
                  " wrong address type, address supplied is an IPv6 address");
    }

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the subnet id
    bind_array->add(subnet_id);

    // Add the address
    bind_array->add(address);

    ConstHostCollection collection;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_SUBID_ADDR,
                             bind_array, ctx->host_ipv4_exchange_, collection, true);

    // Return single record if present, else clear the host.
    ConstHostPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return (result);
}

ConstHostCollection
PgSqlHostDataSource::getAll4(const SubnetID& subnet_id,
                             const asiolink::IOAddress& address) const {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    if (!address.isV4()) {
        isc_throw(BadValue, "PgSqlHostDataSource::get4(id, address) - "
                  " wrong address type, address supplied is an IPv6 address");
    }

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the subnet id
    bind_array->add(subnet_id);

    // Add the address
    bind_array->add(address);

    ConstHostCollection collection;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_SUBID_ADDR,
                             bind_array, ctx->host_ipv4_exchange_, collection, false);
    return (collection);
}

ConstHostPtr
PgSqlHostDataSource::get6(const SubnetID& subnet_id,
                          const Host::IdentifierType& identifier_type,
                          const uint8_t* identifier_begin,
                          const size_t identifier_len) const {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    return (impl_->getHost(ctx, subnet_id, identifier_type, identifier_begin, identifier_len,
                           PgSqlHostDataSourceImpl::GET_HOST_SUBID6_DHCPID,
                           ctx->host_ipv6_exchange_));
}

ConstHostPtr
PgSqlHostDataSource::get6(const asiolink::IOAddress& prefix,
                          const uint8_t prefix_len) const {
    if (!prefix.isV6()) {
        isc_throw(BadValue, "PgSqlHostDataSource::get6(prefix, prefix_len): "
                  "wrong address type, address supplied is an IPv4 address");
    }

    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the prefix
    bind_array->add(prefix);

    // Add the prefix length
    bind_array->add(prefix_len);

    ConstHostCollection collection;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_PREFIX,
                             bind_array, ctx->host_ipv6_exchange_, collection, true);

    // Return single record if present, else clear the host.
    ConstHostPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return (result);
}

ConstHostPtr
PgSqlHostDataSource::get6(const SubnetID& subnet_id,
                          const asiolink::IOAddress& address) const {
    if (!address.isV6()) {
        isc_throw(BadValue, "PgSqlHostDataSource::get6(id, address): "
                  "wrong address type, address supplied is an IPv4 address");
    }

    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the subnet id
    bind_array->add(subnet_id);

    // Add the prefix
    bind_array->add(address);

    ConstHostCollection collection;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_SUBID6_ADDR,
                             bind_array, ctx->host_ipv6_exchange_, collection, true);

    // Return single record if present, else clear the host.
    ConstHostPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return (result);
}

ConstHostCollection
PgSqlHostDataSource::getAll6(const SubnetID& subnet_id,
                             const asiolink::IOAddress& address) const {
    if (!address.isV6()) {
        isc_throw(BadValue, "PgSqlHostDataSource::get6(id, address): "
                  "wrong address type, address supplied is an IPv4 address");
    }

    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the subnet id
    bind_array->add(subnet_id);

    // Add the prefix
    bind_array->add(address);

    ConstHostCollection collection;
    impl_->getHostCollection(ctx, PgSqlHostDataSourceImpl::GET_HOST_SUBID6_ADDR,
                             bind_array, ctx->host_ipv6_exchange_, collection, false);
    return (collection);
}


// Miscellaneous database methods.

std::string
PgSqlHostDataSource::getName() const {
    std::string name = "";
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    try {
        name = ctx->conn_.getParameter("name");
    } catch (...) {
        // Return an empty name
    }
    return (name);
}

std::string
PgSqlHostDataSource::getDescription() const {
    return (std::string("Host data source that stores host information"
                        "in PostgreSQL database"));
}

std::pair<uint32_t, uint32_t>
PgSqlHostDataSource::getVersion() const {
    return(impl_->getVersion());
}

void
PgSqlHostDataSource::commit() {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // If operating in read-only mode, throw exception.
    impl_->checkReadOnly(ctx);
    ctx->conn_.commit();
}

void
PgSqlHostDataSource::rollback() {
    // Get a context
    PgSqlHostContextAlloc get_context(*impl_);
    PgSqlHostContextPtr ctx = get_context.ctx_;

    // If operating in read-only mode, throw exception.
    impl_->checkReadOnly(ctx);
    ctx->conn_.rollback();
}

bool
PgSqlHostDataSource::setIPReservationsUnique(const bool unique) {
    impl_->ip_reservations_unique_ = unique;
    return (true);
}

bool
PgSqlHostDataSource::isUnusable() {
    return (impl_->unusable_);
}

}  // namespace dhcp
}  // namespace isc
