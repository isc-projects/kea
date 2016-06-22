// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/pgsql_host_data_source.h>
#include <dhcpsrv/db_exceptions.h>
#include <util/buffer.h>
#include <util/optional_value.h>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/static_assert.hpp>

#include <stdint.h>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;
using namespace std;

namespace {

#if 0
/// @brief Maximum size of an IPv6 address represented as a text string.
///
/// This is 32 hexadecimal characters written in 8 groups of four, plus seven
/// colon separators.
const size_t ADDRESS6_TEXT_MAX_LEN = 39;

/// @brief Maximum length of classes stored in a dhcp4/6_client_classes
/// columns.
const size_t CLIENT_CLASSES_MAX_LEN = 255;

/// @brief Maximum length of the hostname stored in DNS.
///
/// This length is restricted by the length of the domain-name carried
/// in the Client FQDN %Option (see RFC4702 and RFC4704).
const size_t HOSTNAME_MAX_LEN = 255;

/// @brief Maximum length of option value.
const size_t OPTION_VALUE_MAX_LEN = 4096;

/// @brief Maximum length of option value specified in textual format.
const size_t OPTION_FORMATTED_VALUE_MAX_LEN = 8192;

/// @brief Maximum length of option space name.
const size_t OPTION_SPACE_MAX_LEN = 128;
#endif

/// @brief Numeric value representing last supported identifier.
///
/// This value is used to validate whether the identifier type stored in
/// a database is within bounds. of supported identifiers.
const uint8_t MAX_IDENTIFIER_TYPE = static_cast<uint8_t>(Host::IDENT_CIRCUIT_ID);

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
    /// @brief Number of columns returned for SELECT queries send by this class.
    static const size_t HOST_COLUMNS = 9;

public:

    /// @brief Constructor
    ///
    /// @param additional_columns_num This value is set by the derived classes
    /// to indicate how many additional columns will be returned by SELECT
    /// queries performed by the derived class. This constructor will allocate
    /// resources for these columns, e.g. binding table, error indicators.
    PgSqlHostExchange(const size_t additional_columns_num = 0)
        : columns_num_(HOST_COLUMNS + additional_columns_num),
          columns_(columns_num_), host_id_(0) {
        // Set the column names for use by this class. This only comprises
        // names used by the PgSqlHostExchange class. Derived classes will
        // need to set names for the columns they use.  Currenty these are
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

        BOOST_STATIC_ASSERT(8 < HOST_COLUMNS);
    };

    /// @brief Virtual destructor.
    virtual ~PgSqlHostExchange() {
    }

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

    /// @todo TKM Not certain this is actually needed ....
    /// @brief Returns value of host id.
    ///
    /// This method is used by derived classes.
    uint64_t getHostId() const {
        return (host_id_);
    };

    /// @brief Populate a bind array from a host
    ///
    /// Constructs a PsqlBindArray for sending data stored in a Host object
    /// to the database.
    ///
    /// @param host Host object to be added to the database.
    ///        None of the fields in the host reservation are modified -
    ///        the host data is only read.
    ///
    /// @return pointer to newly constructed bind_array containing the
    /// bound values extracted from host
    ///
    /// @throw DbOperationError if bind_array cannot be populated.
    PsqlBindArrayPtr
    createBindForSend(const HostPtr& host) {
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
            bind_array->add(host->getIPv4SubnetID());

            // dhcp6_subnet_id : INT NULL
            bind_array->add(host->getIPv6SubnetID());

            // ipv4_address : BIGINT NULL
            bind_array->add(host->getIPv4Reservation());

            // hostname : VARCHAR(255) NULL
            bind_array->bindString(host->getHostname());

            // dhcp4_client_classes : VARCHAR(255) NULL
            // Override default separator to not include space after comma.
            bind_array->bindString(host->getClientClasses4().toText(","));

            // dhcp6_client_classes : VARCHAR(255) NULL
            bind_array->bindString(host->getClientClasses6().toText(","));
        } catch (const std::exception& ex) {
            host_.reset();
            isc_throw(DbOperationError,
                      "Could not create bind array from Host: "
                      << host->getHostname() << ", reason: " << ex.what());
        }

        return (bind_array);
    };

    /// @brief Creates a Host object from a given row in a result set.
    ///
    /// @param r result set containing one or rows from the hosts table
    /// @param row row number within the result set from to create the Lease4
    /// object.
    ///
    /// @return HostPtr to the newly created Host object
    /// @throw DbOperationError if the host cannot be created.
    HostPtr convertFromDatabase(const PgSqlResult& r, int row) {

        // host_id INT NOT NULL
        // @todo going to have to deal with uint64_t versus INT etc...
        HostID host_id;
        getColumnValue(r, row, HOST_ID_COL, host_id);

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
        uint32_t subnet_id;
        getColumnValue(r, row, DHCP4_SUBNET_ID_COL, subnet_id);
        SubnetID dhcp4_subnet_id = static_cast<SubnetID>(subnet_id);

        // dhcp6_subnet_id : INT NULL
        getColumnValue(r, row, DHCP6_SUBNET_ID_COL, subnet_id);
        SubnetID dhcp6_subnet_id = static_cast<SubnetID>(subnet_id);

        // ipv4_address : BIGINT NULL
        uint32_t addr4;
        getColumnValue(r, row, IPV4_ADDRESS_COL, addr4);
        isc::asiolink::IOAddress ipv4_reservation(addr4);

        // hostname : VARCHAR(255) NULL
        std::string hostname;
        getColumnValue(r, row, HOSTNAME_COL, hostname);

        // dhcp4_client_classes : VARCHAR(255) NULL
        std::string dhcp4_client_classes;
        getColumnValue(r, row, DHCP4_CLIENT_CLASSES_COL, dhcp4_client_classes);

        // dhcp6_client_classes : VARCHAR(255) NULL
        std::string dhcp6_client_classes;
        getColumnValue(r, row, DHCP6_CLIENT_CLASSES_COL, dhcp6_client_classes);

        HostPtr host;
        try {
            host.reset(new Host(identifier_value, identifier_len,
                                identifier_type, dhcp4_subnet_id,
                                dhcp6_subnet_id, ipv4_reservation, hostname,
                                dhcp4_client_classes, dhcp6_client_classes));

            host->setHostId(host_id);
        } catch (const isc::Exception& ex) {
            isc_throw(DbOperationError, "Could not create host: " << ex.what());
        }

        return(host);
    };

protected:

    /// Number of columns returned in queries.
    size_t columns_num_;

    /// Column names.
    std::vector<std::string> columns_;

    /// Pointer to Host object holding information to be inserted into
    /// Hosts table.  This is used to retain scope.
    HostPtr host_;

private:

    /// Host identifier (primary key in Hosts table).
    uint64_t host_id_;
};

#if 0

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
    static const size_t OPTION_COLUMNS = 6;

    /// @brief Receives DHCPv4 or DHCPv6 options information from the
    /// dhcp4_options or dhcp6_options tables respectively.
    ///
    /// The PgSqlHostWithOptionsExchange class holds two respective instances
    /// of this class, one for receiving DHCPv4 options, one for receiving
    /// DHCPv6 options.
    ///
    /// The following are the basic functions of this class:
    /// - bind class members to specific columns in MySQL binding tables,
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
        : universe_(universe), start_column_(start_column), option_id_(0),
          code_(0), value_length_(0), formatted_value_length_(0),
          space_length_(0), persistent_(false), option_id_null_(MLM_FALSE),
          code_null_(MLM_FALSE), value_null_(MLM_FALSE),
          formatted_value_null_(MLM_FALSE), space_null_(MLM_FALSE),
          option_id_index_(start_column), code_index_(start_column_ + 1),
          value_index_(start_column_ + 2),
          formatted_value_index_(start_column_ + 3),
          space_index_(start_column_ + 4),
          persistent_index_(start_column_ + 5),
          most_recent_option_id_(0) {

            memset(value_, 0, sizeof(value_));
            memset(formatted_value_, 0, sizeof(formatted_value_));
            memset(space_, 0, sizeof(space_));
        }

        /// @brief Returns identifier of the currently processed option.
        uint64_t getOptionId() const {
            if (option_id_null_ == MLM_FALSE) {
                return (option_id_);
            }
            return (0);
        }

        /// @brief Creates instance of the currently processed option.
        ///
        /// This method detects if the currently processed option is a new
        /// instance. It makes it determination by comparing the identifier
        /// of the currently processed option, with the most recently processed
        /// option. If the current value is greater than the id of the recently
        /// processed option it is assumed that the processed row holds new
        /// option information. In such case the option instance is created and
        /// inserted into the configuration passed as argument.
        ///
        /// @param cfg Pointer to the configuration object into which new
        /// option instances should be inserted.
        void retrieveOption(const CfgOptionPtr& cfg) {
            // option_id may be NULL if dhcp4_options or dhcp6_options table
            // doesn't contain any options for the particular host. Also, the
            // current option id must be greater than id if the most recent
            // option because options are ordered by option id. Otherwise
            // we assume that this is already processed option.
            if ((option_id_null_ == MLM_TRUE) ||
                (most_recent_option_id_ >= option_id_)) {
                return;
            }

            // Remember current option id as the most recent processed one. We
            // will be comparing it with option ids in subsequent rows.
            most_recent_option_id_ = option_id_;

            // Convert it to string object for easier comparison.
            std::string space;
            if (space_null_ == MLM_FALSE) {
                // Typically, the string values returned by the database are not
                // NULL terminated.
                space_[space_length_] = '\0';
                space.assign(space_);
            }

            // Convert formatted_value to string as well.
            std::string formatted_value;
            if (formatted_value_null_ == MLM_FALSE) {
                formatted_value_[formatted_value_length_] = '\0';
                formatted_value.assign(formatted_value_);
            }

            // Options are held in a binary or textual format in the database.
            // This is similar to having an option specified in a server
            // configuration file. Such option is converted to appropriate C++
            // class, using option definition. Thus, we need to find the
            // option definition for this option code and option space.

            // If the option space is a standard DHCPv4 or DHCPv6 option space,
            // this is most likely a standard option, for which we have a
            // definition created within libdhcp++.
            OptionDefinitionPtr def;
            if ((space == DHCP4_OPTION_SPACE) || (space == DHCP6_OPTION_SPACE)) {
                def = LibDHCP::getOptionDef(universe_, code_);
            }

            // Otherwise, we may check if this an option encapsulated within the
            // vendor space.
            if (!def && (space != DHCP4_OPTION_SPACE) &&
                (space != DHCP6_OPTION_SPACE)) {
                uint32_t vendor_id = LibDHCP::optionSpaceToVendorId(space);
                if (vendor_id > 0) {
                    def = LibDHCP::getVendorOptionDef(universe_, vendor_id, code_);
                }
            }

            // In all other cases, we use runtime option definitions, which
            // should be also registered within the libdhcp++.
            if (!def) {
                def = LibDHCP::getRuntimeOptionDef(space, code_);
            }

            OptionPtr option;

            if (!def) {
                // If no definition found, we use generic option type.
                OptionBuffer buf(value_, value_ + value_length_);
                option.reset(new Option(universe_, code_, buf.begin(),
                                        buf.end()));
            } else {
                // The option value may be specified in textual or binary format
                // in the database. If formatted_value is empty, the binary
                // format is used. Depending on the format we use a different
                // variant of the optionFactory function.
                if (formatted_value.empty()) {
                    OptionBuffer buf(value_, value_ + value_length_);
                    option = def->optionFactory(universe_, code_, buf.begin(),
                                                buf.end());
                } else {
                    // Spit the value specified in comma separated values
                    // format.
                    std::vector<std::string> split_vec;
                    boost::split(split_vec, formatted_value, boost::is_any_of(","));
                    option = def->optionFactory(universe_, code_, split_vec);
                }
            }

            OptionDescriptor desc(option, persistent_, formatted_value);
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
        }

        /// @brief Initialize binding table fields for options.
        ///
        /// Resets most_recent_option_id_ value to 0.
        ///
        /// @param [out] bind Binding table.
        void setBindFields(std::vector<MYSQL_BIND>& bind) {
            // This method is called just before making a new query, so we
            // reset the most_recent_option_id_ to start over with options
            // processing.
            most_recent_option_id_ = 0;

            // option_id : INT UNSIGNED NOT NULL AUTO_INCREMENT,
            bind[option_id_index_].buffer_type = MYSQL_TYPE_LONG;
            bind[option_id_index_].buffer = reinterpret_cast<char*>(&option_id_);
            bind[option_id_index_].is_unsigned = MLM_TRUE;

            // code : TINYINT OR SHORT UNSIGNED NOT NULL
            bind[code_index_].buffer_type = MYSQL_TYPE_SHORT;
            bind[code_index_].buffer = reinterpret_cast<char*>(&code_);
            bind[code_index_].is_unsigned = MLM_TRUE;
            bind[code_index_].is_null = &code_null_;

            // value : BLOB NULL
            value_length_ = sizeof(value_);
            bind[value_index_].buffer_type = MYSQL_TYPE_BLOB;
            bind[value_index_].buffer = reinterpret_cast<char*>(value_);
            bind[value_index_].buffer_length = value_length_;
            bind[value_index_].length = &value_length_;
            bind[value_index_].is_null = &value_null_;

            // formatted_value : TEXT NULL
            formatted_value_length_ = sizeof(formatted_value_);
            bind[formatted_value_index_].buffer_type = MYSQL_TYPE_STRING;
            bind[formatted_value_index_].buffer = reinterpret_cast<char*>(formatted_value_);
            bind[formatted_value_index_].buffer_length = formatted_value_length_;
            bind[formatted_value_index_].length = &formatted_value_length_;
            bind[formatted_value_index_].is_null = &formatted_value_null_;

            // space : VARCHAR(128) NULL
            space_length_ = sizeof(space_);
            bind[space_index_].buffer_type = MYSQL_TYPE_STRING;
            bind[space_index_].buffer = reinterpret_cast<char*>(space_);
            bind[space_index_].buffer_length = space_length_;
            bind[space_index_].length = &space_length_;
            bind[space_index_].is_null = &space_null_;

            // persistent : TINYINT(1) NOT NULL DEFAULT 0
            bind[persistent_index_].buffer_type = MYSQL_TYPE_TINY;
            bind[persistent_index_].buffer = reinterpret_cast<char*>(&persistent_);
            bind[persistent_index_].is_unsigned = MLM_TRUE;
        }

    private:

        /// @brief Universe: V4 or V6.
        Option::Universe universe_;

        /// @brief Index of first column used by this class.
        size_t start_column_;

        /// @brief Option id.
        uint64_t option_id_;

        /// @brief Option code.
        uint16_t code_;

        /// @brief Buffer holding binary value of an option.
        uint8_t value_[OPTION_VALUE_MAX_LEN];

        /// @brief Option value length.
        unsigned long value_length_;

        /// @brief Buffer holding textual value of an option.
        char formatted_value_[OPTION_FORMATTED_VALUE_MAX_LEN];

        /// @brief Formatted option value length.
        unsigned long formatted_value_length_;

        /// @brief Buffer holding option space name.
        char space_[OPTION_SPACE_MAX_LEN];

        /// @brief Option space length.
        unsigned long space_length_;

        /// @brief Flag indicating if option is always sent or only if
        /// requested.
        bool persistent_;

        /// @name Boolean values indicating if values of specific columns in
        /// the database are NULL.
        //@{
        /// @brief Boolean flag indicating if the DHCPv4 option id is NULL.
        my_bool option_id_null_;

        /// @brief Boolean flag indicating if the DHCPv4 option code is NULL.
        my_bool code_null_;

        /// @brief Boolean flag indicating if the DHCPv4 option value is NULL.
        my_bool value_null_;

        /// @brief Boolean flag indicating if the DHCPv4 formatted option value
        /// is NULL.
        my_bool formatted_value_null_;

        /// @brief Boolean flag indicating if the DHCPv4 option space is NULL.
        my_bool space_null_;

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

    /// @brief Processes the current row.
    ///
    /// The processed row includes both host information and DHCP option
    /// information. Because used SELECT query use LEFT JOIN clause, the
    /// some rows contain duplicated host or options entries. This method
    /// detects duplicated information and discards such entries.
    ///
    /// @param [out] hosts Container holding parsed hosts and options.
    virtual void processFetchedData(ConstHostCollection& hosts) {
        // Holds pointer to the previously parsed host.
        HostPtr most_recent_host;
        if (!hosts.empty()) {
            // Const cast is not very elegant way to deal with it, but
            // there is a good reason to use it here. This method is called
            // to build a collection of const hosts to be returned to the
            // caller. If we wanted to use non-const collection we'd need
            // to copy the whole collection before returning it, which has
            // performance implications. Alternatively, we could store the
            // most recently added host in a class member but this would
            // make the code less readable.
            most_recent_host = boost::const_pointer_cast<Host>(hosts.back());
        }

        // If no host has been parsed yet or we're at the row holding next
        // host, we create a new host object and put it at the end of the
        // list.
        if (!most_recent_host || (most_recent_host->getHostId() < getHostId())) {
            HostPtr host = retrieveHost();
            hosts.push_back(host);
            most_recent_host = host;
        }

        // Parse DHCPv4 options if required to do so.
        if (opt_proc4_) {
            CfgOptionPtr cfg = most_recent_host->getCfgOption4();
            opt_proc4_->retrieveOption(cfg);
        }

        // Parse DHCPv6 options if required to do so.
        if (opt_proc6_) {
            CfgOptionPtr cfg = most_recent_host->getCfgOption6();
            opt_proc6_->retrieveOption(cfg);
        }
    }

    /// @brief Bind variables for receiving option data.
    ///
    /// @return Vector of MYSQL_BIND object representing data to be retrieved.
    virtual std::vector<MYSQL_BIND> createBindForReceive() {
        // The following call sets bind_ values between 0 and 8.
        static_cast<void>(PgSqlHostExchange::createBindForReceive());

        // Bind variables for DHCPv4 options.
        if (opt_proc4_) {
            opt_proc4_->setBindFields(bind_);
        }

        // Bind variables for DHCPv6 options.
        if (opt_proc6_) {
            opt_proc6_->setBindFields(bind_);
        }

        // Add the error flags
        setErrorIndicators(bind_, error_);

        return (bind_);
    };

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
/// mechanisms to retrieve IPv6 reservations. This class is used in sitations
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
          reservation_id_(0),
          reserv_type_(0), reserv_type_null_(MLM_FALSE),
          ipv6_address_buffer_len_(0), prefix_len_(0), iaid_(0),
          reservation_id_index_(findAvailColumn()),
          address_index_(reservation_id_index_ + 1),
          prefix_len_index_(reservation_id_index_ + 2),
          type_index_(reservation_id_index_ + 3),
          iaid_index_(reservation_id_index_ + 4),
          most_recent_reservation_id_(0) {

        memset(ipv6_address_buffer_, 0, sizeof(ipv6_address_buffer_));

        // Provide names of additional columns returned by the queries.
        columns_[reservation_id_index_] = "reservation_id";
        columns_[address_index_] = "address";
        columns_[prefix_len_index_] = "prefix_len";
        columns_[type_index_] = "type";
        columns_[iaid_index_] = "dhcp6_iaid";
    }

    /// @brief Returns last fetched reservation id.
    ///
    /// @return Reservation id or 0 if no reservation data is fetched.
    uint64_t getReservationId() const {
        if (reserv_type_null_ == MLM_FALSE) {
            return (reservation_id_);
        }
        return (0);
    };

    /// @brief Creates IPv6 reservation from the data contained in the
    /// currently processed row.
    ///
    /// Called after the MYSQL_BIND array created by createBindForReceive().
    ///
    /// @return IPv6Resrv object (containing IPv6 address or prefix reservation)
    IPv6Resrv retrieveReservation() {
        // Set the IPv6 Reservation type (0 = IA_NA, 2 = IA_PD)
        IPv6Resrv::Type type = IPv6Resrv::TYPE_NA;

        switch (reserv_type_) {
        case 0:
            type = IPv6Resrv::TYPE_NA;
            break;

        case 2:
            type = IPv6Resrv::TYPE_PD;
            break;

        default:
            isc_throw(BadValue,
                      "invalid IPv6 reservation type returned: "
                      << static_cast<int>(reserv_type_)
                      << ". Only 0 or 2 are allowed.");
        }

        ipv6_address_buffer_[ipv6_address_buffer_len_] = '\0';
        std::string address = ipv6_address_buffer_;
        IPv6Resrv r(type, IOAddress(address), prefix_len_);
        return (r);
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
    virtual void processFetchedData(ConstHostCollection& hosts) {

        // Call parent class to fetch host information and options.
        PgSqlHostWithOptionsExchange::processFetchedData(hosts);

        if (getReservationId() == 0) {
            return;
        }

        if (hosts.empty()) {
            isc_throw(Unexpected, "no host information while retrieving"
                      " IPv6 reservation");
        }
        HostPtr host = boost::const_pointer_cast<Host>(hosts.back());

        // If we're dealing with a new reservation, let's add it to the
        // host.
        if (getReservationId() > most_recent_reservation_id_) {
            most_recent_reservation_id_ = getReservationId();

            if (most_recent_reservation_id_ > 0) {
                host->addReservation(retrieveReservation());
            }
        }
    }

    /// @brief Create BIND array to receive Host data with IPv6 reservations.
    ///
    /// Creates a MYSQL_BIND array to receive Host data from the database.
    /// After data is successfully received, @ref processedFetchedData is
    /// called for each returned row to build collection of @ref Host
    /// objects with associated IPv6 reservations.
    ///
    /// @return Vector of MYSQL_BIND objects representing data to be retrieved.
    virtual std::vector<MYSQL_BIND> createBindForReceive() {
        // Reset most recent reservation id value because we're now making
        // a new SELECT query.
        most_recent_reservation_id_ = 0;

        // Bind values supported by parent classes.
        static_cast<void>(PgSqlHostWithOptionsExchange::createBindForReceive());

        // reservation_id : INT UNSIGNED NOT NULL AUTO_INCREMENT
        bind_[reservation_id_index_].buffer_type = MYSQL_TYPE_LONG;
        bind_[reservation_id_index_].buffer = reinterpret_cast<char*>(&reservation_id_);
        bind_[reservation_id_index_].is_unsigned = MLM_TRUE;

        // IPv6 address/prefix VARCHAR(39)
        ipv6_address_buffer_len_ = sizeof(ipv6_address_buffer_) - 1;
        bind_[address_index_].buffer_type = MYSQL_TYPE_STRING;
        bind_[address_index_].buffer = ipv6_address_buffer_;
        bind_[address_index_].buffer_length = ipv6_address_buffer_len_;
        bind_[address_index_].length = &ipv6_address_buffer_len_;

        // prefix_len : TINYINT
        bind_[prefix_len_index_].buffer_type = MYSQL_TYPE_TINY;
        bind_[prefix_len_index_].buffer = reinterpret_cast<char*>(&prefix_len_);
        bind_[prefix_len_index_].is_unsigned = MLM_TRUE;

        // (reservation) type : TINYINT
        reserv_type_null_ = MLM_FALSE;
        bind_[type_index_].buffer_type = MYSQL_TYPE_TINY;
        bind_[type_index_].buffer = reinterpret_cast<char*>(&reserv_type_);
        bind_[type_index_].is_unsigned = MLM_TRUE;
        bind_[type_index_].is_null = &reserv_type_null_;

        // dhcp6_iaid INT UNSIGNED
        bind_[iaid_index_].buffer_type = MYSQL_TYPE_LONG;
        bind_[iaid_index_].buffer = reinterpret_cast<char*>(&iaid_);
        bind_[iaid_index_].is_unsigned = MLM_TRUE;

        // Add the error flags
        setErrorIndicators(bind_, error_);

        return (bind_);
    };

private:

    /// @brief IPv6 reservation id.
    uint64_t reservation_id_;

    /// @brief IPv6 reservation type.
    uint8_t reserv_type_;

    /// @brief Boolean flag indicating if reservation type field is null.
    ///
    /// This flag is used by the class to determine if the returned row
    /// contains IPv6 reservation information.
    my_bool reserv_type_null_;

    /// @brief Buffer holding IPv6 address/prefix in textual format.
    char ipv6_address_buffer_[ADDRESS6_TEXT_MAX_LEN + 1];

    /// @brief Length of the textual address representation.
    unsigned long ipv6_address_buffer_len_;

    /// @brief Length of the prefix (128 for addresses)
    uint8_t prefix_len_;

    /// @brief IAID.
    uint8_t iaid_;

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

/// @brief This class is used for storing IPv6 reservations in a MySQL database.
///
/// This class is only used to insert IPv6 reservations into the
/// ipv6_reservations table. It is not used to retrieve IPv6 reservations. To
/// retrieve IPv6 reservation the @ref PgSqlIPv6HostExchange class should be
/// used instead.
///
/// When a new IPv6 reservation is inserted into the database, an appropriate
/// host must be defined in the hosts table. An attempt to insert IPv6
/// reservation for non-existing host will result in failure.
class PgSqlIPv6ReservationExchange {
private:

    /// @brief Set number of columns for ipv6_reservation table.
    static const size_t RESRV_COLUMNS = 6;

public:

    /// @brief Constructor
    ///
    /// Initialize class members representing a single IPv6 reservation.
    PgSqlIPv6ReservationExchange()
        : host_id_(0), address_("::"), address_len_(0), prefix_len_(0), type_(0),
          iaid_(0), resv_(IPv6Resrv::TYPE_NA, asiolink::IOAddress("::"), 128) {

        // Reset error table.
        std::fill(&error_[0], &error_[RESRV_COLUMNS], MLM_FALSE);

        // Set the column names (for error messages)
        columns_[0] = "host_id";
        columns_[1] = "address";
        columns_[2] = "prefix_len";
        columns_[3] = "type";
        columns_[4] = "dhcp6_iaid";
        BOOST_STATIC_ASSERT(4 < RESRV_COLUMNS);
    }

    /// @brief Create MYSQL_BIND objects for IPv6 Reservation.
    ///
    /// Fills in the MYSQL_BIND array for sending data in the IPv6 Reservation
    /// object to the database.
    ///
    /// @param resv An object representing IPv6 reservation which will be
    ///        sent to the database.
    ///        None of the fields in the reservation are modified -
    ///        the reservation data is only read.
    /// @param id ID of a host owning this reservation
    ///
    /// @return Vector of MySQL BIND objects representing the data to be added.
    std::vector<MYSQL_BIND> createBindForSend(const IPv6Resrv& resv,
                                              const HostID& id) {

        // Store the values to ensure they remain valid.
        resv_ = resv;
        host_id_ = id;

        // Initialize prior to constructing the array of MYSQL_BIND structures.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        memset(bind_, 0, sizeof(bind_));

        // Set up the structures for the various components of the host structure.

        try {
            // address VARCHAR(39)
            address_ = resv.getPrefix().toText();
            address_len_ = address_.length();
            bind_[0].buffer_type = MYSQL_TYPE_BLOB;
            bind_[0].buffer = reinterpret_cast<char*>
                (const_cast<char*>(address_.c_str()));
            bind_[0].buffer_length = address_len_;
            bind_[0].length = &address_len_;

            // prefix_len tinyint
            prefix_len_ = resv.getPrefixLen();
            bind_[1].buffer_type = MYSQL_TYPE_TINY;
            bind_[1].buffer = reinterpret_cast<char*>(&prefix_len_);
            bind_[1].is_unsigned = MLM_TRUE;

            // type tinyint
            // See lease6_types for values (0 = IA_NA, 1 = IA_TA, 2 = IA_PD)
            type_ = resv.getType() == IPv6Resrv::TYPE_NA ? 0 : 2;
            bind_[2].buffer_type = MYSQL_TYPE_TINY;
            bind_[2].buffer = reinterpret_cast<char*>(&type_);
            bind_[2].is_unsigned = MLM_TRUE;

            // dhcp6_iaid INT UNSIGNED
            /// @todo: We don't support iaid in the IPv6Resrv yet.
            iaid_ = 0;
            bind_[3].buffer_type = MYSQL_TYPE_LONG;
            bind_[3].buffer = reinterpret_cast<char*>(&iaid_);
            bind_[3].is_unsigned = MLM_TRUE;

            // host_id INT UNSIGNED NOT NULL
            bind_[4].buffer_type = MYSQL_TYPE_LONG;
            bind_[4].buffer = reinterpret_cast<char*>(&host_id_);
            bind_[4].is_unsigned = MLM_TRUE;

        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from IPv6 Reservation: "
                      << resv_.toText() << ", reason: " << ex.what());
        }

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        // RESRV_COLUMNS -1 as we do not set reservation_id.
        return (std::vector<MYSQL_BIND>(&bind_[0], &bind_[RESRV_COLUMNS-1]));
    }

private:

    /// @brief Host unique identifier.
    uint64_t host_id_;

    /// @brief Address (or prefix).
    std::string address_;

    /// @brief Length of the textual address representation.
    unsigned long address_len_;

     /// @brief Length of the prefix (128 for addresses).
    uint8_t prefix_len_;

    /// @brief Reservation type.
    uint8_t type_;

    /// @brief IAID.
    uint8_t iaid_;

    /// @brief Object holding reservation being sent to the database.
    IPv6Resrv resv_;

    /// @brief Array of MySQL bindings.
    MYSQL_BIND bind_[RESRV_COLUMNS];

    /// @brief Array of strings holding columns names.
    std::string columns_[RESRV_COLUMNS];

    /// @brief Array of boolean values indicating if error occurred
    /// for respective columns.
    my_bool error_[RESRV_COLUMNS];
};

/// @brief This class is used for inserting options into a database.
///
/// This class supports inserting both DHCPv4 and DHCPv6 options.
class PgSqlOptionExchange {
private:

    /// @brief Number of columns in the tables holding options.
    static const size_t OPTION_COLUMNS = 9;

public:

    /// @brief Constructor.
    PgSqlOptionExchange()
        : type_(0), value_len_(0), formatted_value_len_(0), space_(), space_len_(0),
          persistent_(false), client_class_(), client_class_len_(0),
          subnet_id_(0), host_id_(0), option_() {

        BOOST_STATIC_ASSERT(8 < OPTION_COLUMNS);
    }

    /// @brief Creates binding array to insert option data into database.
    ///
    /// @return Vector of MYSQL_BIND object representing an option.
    std::vector<MYSQL_BIND>
    createBindForSend(const OptionDescriptor& opt_desc,
                      const std::string& opt_space,
                      const OptionalValue<SubnetID>& subnet_id,
                      const HostID& host_id) {

        // Hold pointer to the option to make sure it remains valid until
        // we complete a query.
        option_ = opt_desc.option_;

        memset(bind_, 0, sizeof(bind_));

        try {
            // option_id: INT UNSIGNED NOT NULL
            // The option_id is auto_incremented, so we need to pass the NULL
            // value.
            bind_[0].buffer_type = MYSQL_TYPE_NULL;

            // code: SMALLINT UNSIGNED NOT NULL
            type_  = option_->getType();
            bind_[1].buffer_type = MYSQL_TYPE_SHORT;
            bind_[1].buffer = reinterpret_cast<char*>(&type_);
            bind_[1].is_unsigned = MLM_TRUE;

            // value: BLOB NULL
            if (opt_desc.formatted_value_.empty() &&
                (opt_desc.option_->len() > opt_desc.option_->getHeaderLen())) {
                // The formatted_value is empty and the option value is
                // non-empty so we need to prepare on-wire format for the
                // option and store it in the database as a blob.
                OutputBuffer buf(opt_desc.option_->len());
                opt_desc.option_->pack(buf);
                const char* buf_ptr = static_cast<const char*>(buf.getData());
                value_.assign(buf_ptr + opt_desc.option_->getHeaderLen(),
                              buf_ptr + buf.getLength());
                value_len_ = value_.size();
                bind_[2].buffer_type = MYSQL_TYPE_BLOB;
                bind_[2].buffer = &value_[0];
                bind_[2].buffer_length = value_len_;
                bind_[2].length = &value_len_;

            } else {
                // No value or formatted_value specified. In this case, the
                // value blob is NULL.
                value_.clear();
                bind_[2].buffer_type = MYSQL_TYPE_NULL;
            }

            // formatted_value: TEXT NULL,
            if (!opt_desc.formatted_value_.empty()) {
                formatted_value_len_ = opt_desc.formatted_value_.size();
                bind_[3].buffer_type = MYSQL_TYPE_STRING;
                bind_[3].buffer = const_cast<char*>(opt_desc.formatted_value_.c_str());
                bind_[3].buffer_length = formatted_value_len_;
                bind_[3].length = &formatted_value_len_;

            } else {
                bind_[3].buffer_type = MYSQL_TYPE_NULL;
            }

            // space: VARCHAR(128) NULL
            space_ = opt_space;
            space_len_ = space_.size();
            bind_[4].buffer_type = MYSQL_TYPE_STRING;
            bind_[4].buffer = const_cast<char*>(space_.c_str());
            bind_[4].buffer_length = space_len_;
            bind_[4].length = &space_len_;

            // persistent: TINYINT(1) NOT NULL DEFAULT 0
            persistent_ = opt_desc.persistent_;
            bind_[5].buffer_type = MYSQL_TYPE_TINY;
            bind_[5].buffer = reinterpret_cast<char*>(&persistent_);
            bind_[5].is_unsigned = MLM_TRUE;

            // dhcp_client_class: VARCHAR(128) NULL
            /// @todo Assign actual value to client class string.
            client_class_len_ = client_class_.size();
            bind_[6].buffer_type = MYSQL_TYPE_STRING;
            bind_[6].buffer = const_cast<char*>(client_class_.c_str());
            bind_[6].buffer_length = client_class_len_;
            bind_[6].length = &client_class_len_;

            // dhcp4_subnet_id: INT UNSIGNED NULL
            if (subnet_id.isSpecified()) {
                subnet_id_ = subnet_id;
                bind_[7].buffer_type = MYSQL_TYPE_LONG;
                bind_[7].buffer = reinterpret_cast<char*>(subnet_id_);
                bind_[7].is_unsigned = MLM_TRUE;

            } else {
                bind_[7].buffer_type = MYSQL_TYPE_NULL;
            }

            // host_id: INT UNSIGNED NOT NULL
            host_id_ = host_id;
            bind_[8].buffer_type = MYSQL_TYPE_LONG;
            bind_[8].buffer = reinterpret_cast<char*>(&host_id_);
            bind_[8].is_unsigned = MLM_TRUE;

        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array for inserting DHCP "
                      "option: " << option_->toText() << ", reason: "
                      << ex.what());
        }

        return (std::vector<MYSQL_BIND>(&bind_[0], &bind_[OPTION_COLUMNS]));
    }

private:

    /// @brief Option type.
    uint16_t type_;

    /// @brief Option value as binary.
    std::vector<uint8_t> value_;

    /// @brief Option value length.
    size_t value_len_;

    /// @brief Formatted option value length.
    unsigned long formatted_value_len_;

    /// @brief Option space name.
    std::string space_;

    /// @brief Option space name length.
    size_t space_len_;

    /// @brief Boolean flag indicating if the option is always returned to
    /// a client or only when requested.
    bool persistent_;

    /// @brief Client classes for the option.
    std::string client_class_;

    /// @brief Length of the string holding client classes for the option.
    size_t client_class_len_;

    /// @brief Subnet identifier.
    uint32_t subnet_id_;

    /// @brief Host identifier.
    uint32_t host_id_;

    /// @brief Pointer to currently parsed option.
    OptionPtr option_;

    /// @brief Array of MYSQL_BIND elements representing inserted data.
    MYSQL_BIND bind_[OPTION_COLUMNS];
};
#endif

} // end of anonymous namespace


namespace isc {
namespace dhcp {

/// @brief Implementation of the @ref PgSqlHostDataSource.
class PgSqlHostDataSourceImpl {
public:

    /// @brief Statement Tags
    ///
    /// The contents of the enum are indexes into the list of SQL statements
    enum StatementIndex {
        INSERT_HOST,            // Insert new host to collection
#if 0
        INSERT_V6_RESRV,        // Insert v6 reservation
        INSERT_V4_OPTION,       // Insert DHCPv4 option
        INSERT_V6_OPTION,       // Insert DHCPv6 option
        GET_HOST_DHCPID,        // Gets hosts by host identifier
#endif
        GET_HOST_ADDR,          // Gets hosts by IPv4 address
        GET_HOST_SUBID4_DHCPID, // Gets host by IPv4 SubnetID, HW address/DUID
#if 0
        GET_HOST_SUBID6_DHCPID, // Gets host by IPv6 SubnetID, HW address/DUID
#endif
        GET_HOST_SUBID_ADDR,    // Gets host by IPv4 SubnetID and IPv4 address
#if 0
        GET_HOST_PREFIX,        // Gets host by IPv6 prefix
#endif
        GET_VERSION,            // Obtain version number
        NUM_STATEMENTS          // Number of statements
    };

    /// @brief Constructor.
    ///
    /// This constructor opens database connection and initializes prepared
    /// statements used in the queries.
    PgSqlHostDataSourceImpl(const PgSqlConnection::ParameterMap& parameters);

    /// @brief Destructor.
    ~PgSqlHostDataSourceImpl();

    /// @brief Executes statements which insert a row into one of the tables.
    ///
    /// @param stindex Index of a statement being executed.
    /// @param bind Vector of MYSQL_BIND objects to be used when making the
    /// query.
    /// @param return_last_id flag indicating whether or not the insert
    /// returns the primary key of from the row inserted via " RETURNING
    /// <primary key> as pid" clause on the INSERT statement.  The RETURNING
    /// clause causes the INSERT to return a result set that should consist
    /// of a single row with one column, the value of the primary key.
    /// Defaults to false.
    ///
    /// @returns 0 if return_last_id is false, otherwise it returns the
    /// the value in the result set in the first col of the first row.
    ///
    /// @throw isc::dhcp::DuplicateEntry Database throws duplicate entry error
    uint64_t addStatement(PgSqlHostDataSourceImpl::StatementIndex stindex,
                          PsqlBindArrayPtr& bind,
                          const bool return_last_id = false);

#if 0
    /// @brief Inserts IPv6 Reservation into ipv6_reservation table.
    ///
    /// @param resv IPv6 Reservation to be added
    /// @param id ID of a host owning this reservation
    void addResv(const IPv6Resrv& resv, const HostID& id);

    /// @brief Inserts a single DHCP option into the database.
    ///
    /// @param stindex Index of a statement being executed.
    /// @param opt_desc Option descriptor holding information about an option
    /// to be inserted into the database.
    /// @param opt_space Option space name.
    /// @param subnet_id Subnet identifier.
    /// @param host_id Host identifier.
    void addOption(const PgSqlHostDataSourceImpl::StatementIndex& stindex,
                   const OptionDescriptor& opt_desc,
                   const std::string& opt_space,
                   const OptionalValue<SubnetID>& subnet_id,
                   const HostID& host_id);

    /// @brief Inserts multiple options into the database.
    ///
    /// @param stindex Index of a statement being executed.
    /// @param options_cfg An object holding a collection of options to be
    /// inserted into the database.
    /// @param host_id Host identifier retrieved using @c mysql_insert_id.
    void addOptions(const StatementIndex& stindex, const ConstCfgOptionPtr& options_cfg,
                    const uint64_t host_id);
#endif

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
    /// @param stindex Statement index.
    /// @param bind Pointer to an array of MySQL bindings.
    /// @param exchange Pointer to the exchange object used for the
    /// particular query.
    /// @param [out] result Reference to the collection of hosts returned.
    /// @param single A boolean value indicating if a single host is
    /// expected to be returned, or multiple hosts.
    void getHostCollection(StatementIndex stindex, PsqlBindArrayPtr bind,
                           boost::shared_ptr<PgSqlHostExchange> exchange,
                           ConstHostCollection& result, bool single) const;

    /// @brief Retrieves a host by subnet and client's unique identifier.
    ///
    /// This method is used by both PgSqlHostDataSource::get4 and
    /// PgSqlHOstDataSource::get6 methods.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param identifier_type Identifier type.
    /// @param identifier_begin Pointer to a begining of a buffer containing
    /// an identifier.
    /// @param identifier_len Identifier length.
    /// @param stindex Statement index.
    /// @param exchange Pointer to the exchange object used for the
    /// particular query.
    ///
    /// @return Pointer to const instance of Host or null pointer if
    /// no host found.
    ConstHostPtr getHost(const SubnetID& subnet_id,
                         const Host::IdentifierType& identifier_type,
                         const uint8_t* identifier_begin,
                         const size_t identifier_len,
                         StatementIndex stindex,
                         boost::shared_ptr<PgSqlHostExchange> exchange) const;


    /// @brief Returns PostgreSQL schema version of the open database
    ///
    /// @return Version number stored in the database, as a pair of unsigned
    ///         integers. "first" is the major version number, "second" the
    ///         minor number.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database
    ///        has failed.
    std::pair<uint32_t, uint32_t> getVersion() const;

#if 1
    // @todo TKM using plain host exchange for now
    boost::shared_ptr<PgSqlHostExchange> host_exchange_;
#else
    /// @brief Pointer to the object representing an exchange which
    /// can be used to retrieve hosts and DHCPv4 options.
    boost::shared_ptr<PgSqlHostWithOptionsExchange> host_exchange_;

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
#endif

    /// @brief MySQL connection
    PgSqlConnection conn_;

};

/// @brief Prepared MySQL statements used by the backend to insert and
/// retrieve hosts from the database.
PgSqlTaggedStatement tagged_statements[] = {
    // Inserts a host into the 'hosts' table. Returns the inserted host id.
    { 8, // PgSqlHostDataSourceImpl::INSERT_HOST,
     { OID_BYTEA, OID_INT2,
       OID_INT4, OID_INT4, OID_INT8, OID_VARCHAR,
       OID_VARCHAR, OID_VARCHAR }, "insert_host",
     "INSERT INTO hosts(dhcp_identifier, dhcp_identifier_type, "
        "dhcp4_subnet_id, dhcp6_subnet_id, ipv4_address, hostname, "
        "dhcp4_client_classes, dhcp6_client_classes) "
     "VALUES ($1, $2, $3, $4, $5, $6, $7, $8) RETURNING host_id"},

#if 0
    // Inserts a single IPv6 reservation into 'reservations' table.
    {PgSqlHostDataSourceImpl::INSERT_V6_RESRV,
         "INSERT INTO ipv6_reservations(address, prefix_len, type, "
            "dhcp6_iaid, host_id) "
         "VALUES (?,?,?,?,?)"},

    // Inserts a single DHCPv4 option into 'dhcp4_options' table.
    // Using fixed scope_id = 3, which associates an option with host.
    {PgSqlHostDataSourceImpl::INSERT_V4_OPTION,
         "INSERT INTO dhcp4_options(option_id, code, value, formatted_value, space, "
            "persistent, dhcp_client_class, dhcp4_subnet_id, host_id, scope_id) "
         " VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, 3)"},

    // Inserts a single DHCPv6 option into 'dhcp6_options' table.
    // Using fixed scope_id = 3, which associates an option with host.
    {PgSqlHostDataSourceImpl::INSERT_V6_OPTION,
         "INSERT INTO dhcp6_options(option_id, code, value, formatted_value, space, "
            "persistent, dhcp_client_class, dhcp6_subnet_id, host_id, scope_id) "
         " VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, 3)"},

    // Retrieves host information, IPv6 reservations and both DHCPv4 and
    // DHCPv6 options associated with the host. The LEFT JOIN clause is used
    // to retrieve information from 4 different tables using a single query.
    // Hence, this query returns multiple rows for a single host.
    {PgSqlHostDataSourceImpl::GET_HOST_DHCPID,
            "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
                "h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, "
                "h.hostname, h.dhcp4_client_classes, h.dhcp6_client_classes, "
                "o4.option_id, o4.code, o4.value, o4.formatted_value, o4.space, "
                "o4.persistent, "
                "o6.option_id, o6.code, o6.value, o6.formatted_value, o6.space, "
                "o6.persistent, "
                "r.reservation_id, r.address, r.prefix_len, r.type, "
                "r.dhcp6_iaid "
            "FROM hosts AS h "
            "LEFT JOIN dhcp4_options AS o4 "
                "ON h.host_id = o4.host_id "
            "LEFT JOIN dhcp6_options AS o6 "
                "ON h.host_id = o6.host_id "
            "LEFT JOIN ipv6_reservations AS r "
                "ON h.host_id = r.host_id "
            "WHERE dhcp_identifier = ? AND dhcp_identifier_type = ? "
            "ORDER BY h.host_id, o4.option_id, o6.option_id, r.reservation_id"},
#endif

    // Retrieves host information along with the DHCPv4 options associated with
    // it. Left joining the dhcp4_options table results in multiple rows being
    // returned for the same host. The host is retrieved by IPv4 address.
    { 1, // PgSqlHostDataSourceImpl::GET_HOST_ADDR,
     { OID_INT8 }, "get_host_addr",
     "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
            "h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
            "h.dhcp4_client_classes, h.dhcp6_client_classes, "
            "o.option_id, o.code, o.value, o.formatted_value, o.space, "
            "o.persistent "
      "FROM hosts AS h "
      "LEFT JOIN dhcp4_options AS o ON h.host_id = o.host_id "
      "WHERE ipv4_address = $1 "
      "ORDER BY h.host_id, o.option_id"},

    // Retrieves host information and DHCPv4 options using subnet identifier
    // and client's identifier. Left joining the dhcp4_options table results in
    // multiple rows being returned for the same host.
    { 3, //PgSqlHostDataSourceImpl::GET_HOST_SUBID4_DHCPID,
     { OID_INT4, OID_INT2, OID_BYTEA }, "get_host_subid4_dhcpid",
     "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
        "h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
        "h.dhcp4_client_classes, h.dhcp6_client_classes, "
        "o.option_id, o.code, o.value, o.formatted_value, o.space, "
        "o.persistent "
     "FROM hosts AS h "
     "LEFT JOIN dhcp4_options AS o ON h.host_id = o.host_id "
     "WHERE h.dhcp4_subnet_id = $1 AND h.dhcp_identifier_type = $2 "
     "   AND h.dhcp_identifier = $3 "
     "ORDER BY h.host_id, o.option_id"},

#if 0
    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // associated with a host. The number of rows returned is a multiplication
    // of number of IPv6 reservations and DHCPv6 options.
    {PgSqlHostDataSourceImpl::GET_HOST_SUBID6_DHCPID,
            "SELECT h.host_id, h.dhcp_identifier, "
                "h.dhcp_identifier_type, h.dhcp4_subnet_id, "
                "h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, "
                "r.reservation_id, r.address, r.prefix_len, r.type, "
                "r.dhcp6_iaid "
            "FROM hosts AS h "
            "LEFT JOIN dhcp6_options AS o "
                "ON h.host_id = o.host_id "
            "LEFT JOIN ipv6_reservations AS r "
                "ON h.host_id = r.host_id "
            "WHERE h.dhcp6_subnet_id = ? AND h.dhcp_identifier_type = ? "
                "AND h.dhcp_identifier = ? "
            "ORDER BY h.host_id, o.option_id, r.reservation_id"},
#endif

    // Retrieves host information and DHCPv4 options for the host using subnet
    // identifier and IPv4 reservation. Left joining the dhcp4_options table
    // results in multiple rows being returned for the host. The number of
    // rows depends on the number of options defined for the host.
    { 2,  //PgSqlHostDataSourceImpl::GET_HOST_SUBID_ADDR,
      { OID_INT4, OID_INT8 }, "get_host_subid_addr",
       "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
            "h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
            "h.dhcp4_client_classes, h.dhcp6_client_classes, "
            "o.option_id, o.code, o.value, o.formatted_value, o.space, "
            "o.persistent "
        "FROM hosts AS h "
        "LEFT JOIN dhcp4_options AS o ON h.host_id = o.host_id "
        "WHERE h.dhcp4_subnet_id = $1 AND h.ipv4_address = $2 "
        "ORDER BY h.host_id, o.option_id"},
#if 0

    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // associated with a host using prefix and prefix length. This query
    // returns host information for a single host. However, multiple rows
    // are returned due to left joining IPv6 reservations and DHCPv6 options.
    // The number of rows returned is multiplication of number of existing
    // IPv6 reservations and DHCPv6 options.
    {PgSqlHostDataSourceImpl::GET_HOST_PREFIX,
            "SELECT h.host_id, h.dhcp_identifier, "
                "h.dhcp_identifier_type, h.dhcp4_subnet_id, "
                "h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, "
                "r.reservation_id, r.address, r.prefix_len, r.type, "
                "r.dhcp6_iaid "
            "FROM hosts AS h "
            "LEFT JOIN dhcp6_options AS o "
                "ON h.host_id = o.host_id "
            "LEFT JOIN ipv6_reservations AS r "
                "ON h.host_id = r.host_id "
            "WHERE h.host_id = "
                "(SELECT host_id FROM ipv6_reservations "
                 "WHERE address = ? AND prefix_len = ?) "
            "ORDER BY h.host_id, o.option_id, r.reservation_id"},
#endif

    // Retrieves MySQL schema version.
    { 0, //PgSqlHostDataSourceImpl::GET_VERSION,
     { OID_NONE }, "get_version",
     "SELECT version, minor FROM schema_version"},

    // Marks the end of the statements table.
    {0, { 0 }, NULL, NULL}
};

PgSqlHostDataSourceImpl::
PgSqlHostDataSourceImpl(const PgSqlConnection::ParameterMap& parameters)
#if 1
    : host_exchange_(new PgSqlHostExchange()),
#else
    : host_exchange_(new PgSqlHostWithOptionsExchange(PgSqlHostWithOptionsExchange::DHCP4_ONLY)),
      host_ipv6_exchange_(new PgSqlHostIPv6Exchange(PgSqlHostWithOptionsExchange::DHCP6_ONLY)),
      host_ipv46_exchange_(new PgSqlHostIPv6Exchange(PgSqlHostWithOptionsExchange::
                                                     DHCP4_AND_DHCP6)),
      host_ipv6_reservation_exchange_(new PgSqlIPv6ReservationExchange()),
      host_option_exchange_(new PgSqlOptionExchange()),
#endif

      conn_(parameters) {

    // Open the database.
    conn_.openDatabase();

    int i = 0;
    for( ; tagged_statements[i].text != NULL ; ++i) {
        conn_.prepareStatement(tagged_statements[i]);
    }

    // Just in case somebody foo-barred things
    if (i != NUM_STATEMENTS) {
        isc_throw(DbOpenError, "Number of statements prepared: " << i
                  << " does not match expected count:" << NUM_STATEMENTS);
    }
}

PgSqlHostDataSourceImpl::~PgSqlHostDataSourceImpl() {
}

uint64_t
PgSqlHostDataSourceImpl::addStatement(StatementIndex stindex,
                                      PsqlBindArrayPtr& bind_array,
                                      const bool return_last_id) {
    uint64_t last_id = 0;
    PgSqlResult r(PQexecPrepared(conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array->values_[0],
                                 &bind_array->lengths_[0],
                                 &bind_array->formats_[0], 0));

    int s = PQresultStatus(r);

    if (s != PGRES_COMMAND_OK) {
        // Failure: check for the special case of duplicate entry.  If this is
        // the case, we return false to indicate that the row was not added.
        // Otherwise we throw an exception.
        if (conn_.compareError(r, PgSqlConnection::DUPLICATE_KEY)) {
            return (false);
        }

        conn_.checkStatementError(r, tagged_statements[stindex]);
    }

    // @todo - getColumnValue variants could be made static, if they use
    // PQfname for the column label, rather then columns_.  Then we wouldn't
    // need an instance here.
    if (return_last_id) {
        PgSqlExchange ex;
        ex.getColumnValue(r, 0, 0, last_id);
    }

    return (last_id);

}

#if 0
void
PgSqlHostDataSourceImpl::addResv(const IPv6Resrv& resv,
                                 const HostID& id) {
    std::vector<MYSQL_BIND> bind =
        host_ipv6_reservation_exchange_->createBindForSend(resv, id);

    addStatement(INSERT_V6_RESRV, bind);
}

void
PgSqlHostDataSourceImpl::addOption(const StatementIndex& stindex,
                                   const OptionDescriptor& opt_desc,
                                   const std::string& opt_space,
                                   const OptionalValue<SubnetID>& subnet_id,
                                   const HostID& id) {
    std::vector<MYSQL_BIND> bind =
        host_option_exchange_->createBindForSend(opt_desc, opt_space,
                                                 subnet_id, id);

    addStatement(stindex, bind);
}

void
PgSqlHostDataSourceImpl::addOptions(const StatementIndex& stindex,
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
    for (std::list<std::string>::const_iterator space = option_spaces.begin();
         space != option_spaces.end(); ++space) {
        OptionContainerPtr options = options_cfg->getAll(*space);
        if (options && !options->empty()) {
            for (OptionContainer::const_iterator opt = options->begin();
                 opt != options->end(); ++opt) {
                addOption(stindex, *opt, *space, OptionalValue<SubnetID>(),
                          host_id);
            }
        }
    }
}
#endif

void
PgSqlHostDataSourceImpl::
getHostCollection(StatementIndex stindex, PsqlBindArrayPtr bind_array,
                  boost::shared_ptr<PgSqlHostExchange> exchange,
                  ConstHostCollection& result, bool single) const {

    PgSqlResult r(PQexecPrepared(conn_, tagged_statements[stindex].name,
                                 tagged_statements[stindex].nbparams,
                                 &bind_array->values_[0],
                                 &bind_array->lengths_[0],
                                 &bind_array->formats_[0], 0));

    conn_.checkStatementError(r, tagged_statements[stindex]);

    int rows = PQntuples(r);
    if (single && rows > 1) {
        isc_throw(MultipleRecords, "multiple records were found in the "
                      "database where only one was expected for query "
                      << tagged_statements[stindex].name);
    }

    HostID prev_id = 0;
    for(int row = 0; row < rows; ++row) {
        HostPtr host = exchange->convertFromDatabase(r, row);
        // Add new host only if there are no hosts or the host id of the
        // most recently added host is different than the host id of the
        // currently processed host.
        if (host->getHostId() != prev_id) {
            result.push_back(host);
        }

        prev_id = host->getHostId();
    }
}

ConstHostPtr
PgSqlHostDataSourceImpl::
getHost(const SubnetID& subnet_id,
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
    getHostCollection(stindex, bind_array, exchange, collection, true);

    // Return single record if present, else clear the host.
    ConstHostPtr result;
    if (!collection.empty())
        result = *collection.begin();

    return (result);
}

std::pair<uint32_t, uint32_t> PgSqlHostDataSourceImpl::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_HOST_DB_GET_VERSION);

    PgSqlResult r(PQexecPrepared(conn_, "get_version", 0, NULL, NULL, NULL, 0));
    conn_.checkStatementError(r, tagged_statements[GET_VERSION]);

    istringstream tmp;
    uint32_t version;
    tmp.str(PQgetvalue(r, 0, 0));
    tmp >> version;
    tmp.str("");
    tmp.clear();

    uint32_t minor;
    tmp.str(PQgetvalue(r, 0, 1));
    tmp >> minor;

    return (std::make_pair<uint32_t, uint32_t>(version, minor));
}

/*********** PgSqlHostDataSource *********************/


PgSqlHostDataSource::
PgSqlHostDataSource(const PgSqlConnection::ParameterMap& parameters)
    : impl_(new PgSqlHostDataSourceImpl(parameters)) {
}

PgSqlHostDataSource::~PgSqlHostDataSource() {
    delete impl_;
}

void
PgSqlHostDataSource::add(const HostPtr& host) {
    // Initiate PostgreSQL transaction as we will have to make multiple queries
    // to insert host information into multiple tables. If that fails on
    // any stage, the transaction will be rolled back by the destructor of
    // the PgSqlTransaction class.
    PgSqlTransaction transaction(impl_->conn_);

    // Create the MYSQL_BIND array for the host
    PsqlBindArrayPtr bind_array = impl_->host_exchange_->createBindForSend(host);

    // ... and insert the host.
    uint32_t host_id = impl_->addStatement(PgSqlHostDataSourceImpl::INSERT_HOST,
                                           bind_array, true);

    // @todo TKM take this out
    std::cout << "id of new host: " << host_id << std::endl;

#if 0
    // Insert DHCPv4 options.
    ConstCfgOptionPtr cfg_option4 = host->getCfgOption4();
    if (cfg_option4) {
        impl_->addOptions(PgSqlHostDataSourceImpl::INSERT_V4_OPTION,
                          cfg_option4, host_id);
    }

    // Insert DHCPv6 options.
    ConstCfgOptionPtr cfg_option6 = host->getCfgOption6();
    if (cfg_option6) {
        impl_->addOptions(PgSqlHostDataSourceImpl::INSERT_V6_OPTION,
                          cfg_option6, host_id);
    }

    // Insert IPv6 reservations.
    IPv6ResrvRange v6resv = host->getIPv6Reservations();
    if (std::distance(v6resv.first, v6resv.second) > 0) {
        for (IPv6ResrvIterator resv = v6resv.first; resv != v6resv.second;
             ++resv) {
            impl_->addResv(resv->second, host_id);
        }
    }

#endif

    // Everything went fine, so explicitly commit the transaction.
    transaction.commit();
}

ConstHostCollection
PgSqlHostDataSource::getAll(const HWAddrPtr& hwaddr,
                            const DuidPtr& duid) const {

    if (duid){
        return (getAll(Host::IDENT_DUID, &duid->getDuid()[0],
                       duid->getDuid().size()));

    } else if (hwaddr) {
        return (getAll(Host::IDENT_HWADDR,
                       &hwaddr->hwaddr_[0],
                       hwaddr->hwaddr_.size()));
    }

    return (ConstHostCollection());
}

#if 1
ConstHostCollection
PgSqlHostDataSource::getAll(const Host::IdentifierType&,
                            const uint8_t*,
                            const size_t) const {
    ConstHostCollection result;
    return (result);
}
#else
ConstHostCollection
PgSqlHostDataSource::getAll(const Host::IdentifierType& identifier_type,
                            const uint8_t* identifier_begin,
                            const size_t identifier_len) const {
    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Identifier type.
    bind_array->add(static_cast<uint8_t>(identifier_type));

    // Identifier value.
    bind_array->add(identifier_begin, identifier_len);

    ConstHostCollection result;
    impl_->getHostCollection(PgSqlHostDataSourceImpl::GET_HOST_DHCPID,
                             bind_array, impl_->host_ipv46_exchange_,
                             result, false);
    return (result);
}
#endif

ConstHostCollection
PgSqlHostDataSource::getAll4(const asiolink::IOAddress& address) const {

    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    bind_array->add(address);

    ConstHostCollection result;
    impl_->getHostCollection(PgSqlHostDataSourceImpl::GET_HOST_ADDR, bind_array,
                             impl_->host_exchange_, result, false);

    return (result);
}

ConstHostPtr
PgSqlHostDataSource::get4(const SubnetID& subnet_id, const HWAddrPtr& hwaddr,
                          const DuidPtr& duid) const {

    /// @todo: Rethink the logic in BaseHostDataSource::get4(subnet, hwaddr, duid)
    if (hwaddr && duid) {
        isc_throw(BadValue, "MySQL host data source get4() called with both"
                  " hwaddr and duid, only one of them is allowed");
    }
    if (!hwaddr && !duid) {
        isc_throw(BadValue, "MySQL host data source get4() called with "
                  "neither hwaddr or duid specified, one of them is required");
    }

    // Choosing one of the identifiers
    if (hwaddr) {
        return (get4(subnet_id, Host::IDENT_HWADDR, &hwaddr->hwaddr_[0],
                     hwaddr->hwaddr_.size()));

    } else if (duid) {
        return (get4(subnet_id, Host::IDENT_DUID, &duid->getDuid()[0],
                     duid->getDuid().size()));
    }

    return (ConstHostPtr());
}

ConstHostPtr
PgSqlHostDataSource::get4(const SubnetID& subnet_id,
                          const Host::IdentifierType& identifier_type,
                          const uint8_t* identifier_begin,
                          const size_t identifier_len) const {

    return (impl_->getHost(subnet_id, identifier_type, identifier_begin,
                           identifier_len,
                           PgSqlHostDataSourceImpl::GET_HOST_SUBID4_DHCPID,
                           impl_->host_exchange_));
}

ConstHostPtr
PgSqlHostDataSource::get4(const SubnetID& subnet_id,
                          const asiolink::IOAddress& address) const {
    // Set up the WHERE clause value
    PsqlBindArrayPtr bind_array(new PsqlBindArray());

    // Add the subnet id
    bind_array->add(subnet_id);

    // Add the address
    bind_array->add(address);

    ConstHostCollection collection;
    impl_->getHostCollection(PgSqlHostDataSourceImpl::GET_HOST_SUBID_ADDR,
                             bind_array, impl_->host_exchange_, collection,
                             true);

    // Return single record if present, else clear the host.
    ConstHostPtr result;
    if (!collection.empty())
        result = *collection.begin();

    return (result);
}

#if 1
ConstHostPtr
PgSqlHostDataSource::get6(const SubnetID&, const DuidPtr&,
                          const HWAddrPtr&) const {
    return (HostPtr());
}
#else
ConstHostPtr
PgSqlHostDataSource::get6(const SubnetID& subnet_id, const DuidPtr& duid,
                          const HWAddrPtr& hwaddr) const {

    /// @todo: Rethink the logic in BaseHostDataSource::get6(subnet, hwaddr, duid)
    if (hwaddr && duid) {
        isc_throw(BadValue, "MySQL host data source get6() called with both"
                  " hwaddr and duid, only one of them is allowed");
    }
    if (!hwaddr && !duid) {
        isc_throw(BadValue, "MySQL host data source get6() called with "
                  "neither hwaddr or duid specified, one of them is required");
    }

    // Choosing one of the identifiers
    if (hwaddr) {
        return (get6(subnet_id, Host::IDENT_HWADDR, &hwaddr->hwaddr_[0],
                     hwaddr->hwaddr_.size()));
    } else if (duid) {
        return (get6(subnet_id, Host::IDENT_DUID, &duid->getDuid()[0],
                     duid->getDuid().size()));
    }

    return (ConstHostPtr());
}
#endif

#if 1
ConstHostPtr
PgSqlHostDataSource::get6(const SubnetID&,
                          const Host::IdentifierType&,
                          const uint8_t*,
                          const size_t) const {
    return (ConstHostPtr());
}
#else
ConstHostPtr
PgSqlHostDataSource::get6(const SubnetID& subnet_id,
                          const Host::IdentifierType& identifier_type,
                          const uint8_t* identifier_begin,
                          const size_t identifier_len) const {

    return (impl_->getHost(subnet_id, identifier_type, identifier_begin,
                   identifier_len, PgSqlHostDataSourceImpl::GET_HOST_SUBID6_DHCPID,
                   impl_->host_ipv6_exchange_));
}
#endif

#if 1
ConstHostPtr
PgSqlHostDataSource::get6(const asiolink::IOAddress&,
                          const uint8_t) const {

    ConstHostPtr result;
    return(result);
}
#else
ConstHostPtr
PgSqlHostDataSource::get6(const asiolink::IOAddress& prefix,
                          const uint8_t prefix_len) const {

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    std::string addr6 = prefix.toText();
    unsigned long addr6_length = addr6.size();

    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = reinterpret_cast<char*>
                        (const_cast<char*>(addr6.c_str()));
    inbind[0].length = &addr6_length;
    inbind[0].buffer_length = addr6_length;


    uint8_t tmp = prefix_len;
    inbind[1].buffer_type = MYSQL_TYPE_TINY;
    inbind[1].buffer = reinterpret_cast<char*>(&tmp);
    inbind[1].is_unsigned = MLM_TRUE;


    ConstHostCollection collection;
    impl_->getHostCollection(PgSqlHostDataSourceImpl::GET_HOST_PREFIX,
                             inbind, impl_->host_ipv6_exchange_,
                             collection, true);

    // Return single record if present, else clear the host.
    ConstHostPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return (result);
}
#endif

// Miscellaneous database methods.

std::string PgSqlHostDataSource::getName() const {
    std::string name = "";
    try {
        name = impl_->conn_.getParameter("name");
    } catch (...) {
        // Return an empty name
    }
    return (name);
}

std::string PgSqlHostDataSource::getDescription() const {
    return (std::string("Host data source that stores host information"
                        "in PostgreSQL database"));
}

std::pair<uint32_t, uint32_t> PgSqlHostDataSource::getVersion() const {
    return(impl_->getVersion());
}

#if 0
// Do we really need these ?
void
PgSqlHostDataSource::commit() {
    impl_->conn_.commit();
}


void
PgSqlHostDataSource::rollback() {
    impl_->conn_.rollback();
}
#endif


}; // end of isc::dhcp namespace
}; // end of isc namespace
