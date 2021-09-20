// Copyright (C) 2015-2021 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/mysql_host_data_source.h>
#include <dhcpsrv/timer_mgr.h>
#include <util/buffer.h>
#include <util/multi_threading_mgr.h>
#include <util/optional.h>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/array.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/static_assert.hpp>

#include <mysql.h>
#include <mysqld_error.h>
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

/// @brief Numeric value representing last supported identifier.
///
/// This value is used to validate whether the identifier type stored in
/// a database is within bounds. of supported identifiers.
const uint8_t MAX_IDENTIFIER_TYPE = static_cast<uint8_t>(Host::LAST_IDENTIFIER_TYPE);

/// @brief This class provides mechanisms for sending and retrieving
/// information from the 'hosts' table.
///
/// This class is used to insert and retrieve entries from the 'hosts' table.
/// The queries used with this class do not retrieve IPv6 reservations or
/// options associated with a host to minimize impact on performance. Other
/// classes derived from @ref MySqlHostExchange should be used to retrieve
/// information about IPv6 reservations and options.
///
/// Database schema contains several unique indexes to guard against adding
/// multiple hosts for the same client identifier in a single subnet and for
/// adding multiple hosts with a reservation for the same IPv4 address in a
/// single subnet. The exceptions that have to be taken into account are
/// listed below:
/// - zero or null IPv4 address indicates that there is no reservation for the
///   IPv4 address for the host,
/// - zero or null subnet identifier (either IPv4 or IPv6) indicates that
///   this subnet identifier must be ignored. Specifically, this is the case
///   when host reservation is for the DHCPv4 server, the IPv6 subnet id should
///   be ignored. Conversely, when host reservation is created for the DHCPv6 server,
///   the IPv4 subnet id should be ignored.
///
/// To exclude those special case values from the unique indexes, the MySQL
/// backend relies on the property of the unique indexes in MySQL, i.e. null
/// values are excluded from unique indexes. That means that there might be
/// multiple null values in a given column on which unique index is applied.
/// Therefore, the MySQL backend converts subnet identifiers and IPv4 addresses
/// of 0 to null before inserting a host to the database.
class MySqlHostExchange {
private:

    /// @brief Number of columns returned for SELECT queries sent by this class.
    static const size_t HOST_COLUMNS = 14;

public:

    /// @brief Constructor
    ///
    /// @param additional_columns_num This value is set by the derived classes
    /// to indicate how many additional columns will be returned by SELECT
    /// queries performed by the derived class. This constructor will allocate
    /// resources for these columns, e.g. binding table, error indicators.
    MySqlHostExchange(const size_t additional_columns_num = 0)
        : columns_num_(HOST_COLUMNS + additional_columns_num),
          bind_(columns_num_), columns_(columns_num_),
          error_(columns_num_, MLM_FALSE), host_id_(0),
          dhcp_identifier_length_(0), dhcp_identifier_type_(0),
          dhcp4_subnet_id_(SUBNET_ID_UNUSED),
          dhcp6_subnet_id_(SUBNET_ID_UNUSED), ipv4_address_(0),
          hostname_length_(0), dhcp4_client_classes_length_(0),
          dhcp6_client_classes_length_(0),
          user_context_length_(0),
          dhcp4_next_server_(0),
          dhcp4_server_hostname_length_(0),
          dhcp4_boot_file_name_length_(0),
          auth_key_length_(0),
          dhcp4_subnet_id_null_(MLM_FALSE),
          dhcp6_subnet_id_null_(MLM_FALSE),
          ipv4_address_null_(MLM_FALSE), hostname_null_(MLM_FALSE),
          dhcp4_client_classes_null_(MLM_FALSE),
          dhcp6_client_classes_null_(MLM_FALSE),
          user_context_null_(MLM_FALSE),
          dhcp4_next_server_null_(MLM_FALSE),
          dhcp4_server_hostname_null_(MLM_FALSE),
          dhcp4_boot_file_name_null_(MLM_FALSE),
          auth_key_null_(MLM_FALSE) {

        // Fill arrays with 0 so as they don't include any garbage.
        memset(dhcp_identifier_buffer_, 0, sizeof(dhcp_identifier_buffer_));
        memset(hostname_, 0, sizeof(hostname_));
        memset(dhcp4_client_classes_, 0, sizeof(dhcp4_client_classes_));
        memset(dhcp6_client_classes_, 0, sizeof(dhcp6_client_classes_));
        memset(user_context_, 0, sizeof(user_context_));
        memset(dhcp4_server_hostname_, 0, sizeof(dhcp4_server_hostname_));
        memset(dhcp4_boot_file_name_, 0, sizeof(dhcp4_boot_file_name_));
        memset(auth_key_, 0, sizeof(auth_key_));

        // Set the column names for use by this class. This only comprises
        // names used by the MySqlHostExchange class. Derived classes will
        // need to set names for the columns they use.
        columns_[0] = "host_id";
        columns_[1] = "dhcp_identifier";
        columns_[2] = "dhcp_identifier_type";
        columns_[3] = "dhcp4_subnet_id";
        columns_[4] = "dhcp6_subnet_id";
        columns_[5] = "ipv4_address";
        columns_[6] = "hostname";
        columns_[7] = "dhcp4_client_classes";
        columns_[8] = "dhcp6_client_classes";
        columns_[9] = "user_context";
        columns_[10] = "dhcp4_next_server";
        columns_[11] = "dhcp4_server_hostname";
        columns_[12] = "dhcp4_boot_file_name";
        columns_[13] = "auth_key";

        BOOST_STATIC_ASSERT(13 < HOST_COLUMNS);
    };

    /// @brief Virtual destructor.
    virtual ~MySqlHostExchange() {
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

    /// @brief Returns value of host id.
    ///
    /// This method is used by derived classes.
    uint64_t getHostId() const {
        return (host_id_);
    };

    /// @brief Set error indicators
    ///
    /// Sets the error indicator for each of the MYSQL_BIND elements. It points
    /// the "error" field within an element of the input array to the
    /// corresponding element of the passed error array.
    ///
    /// @param bind Array of BIND elements
    /// @param error Array of error elements.  If there is an error in getting
    ///        data associated with one of the "bind" elements, the
    ///        corresponding element in the error array is set to MLM_TRUE.
    static void setErrorIndicators(std::vector<MYSQL_BIND>& bind,
                                   std::vector<my_bools>& error) {
        for (size_t i = 0; i < error.size(); ++i) {
            error[i] = MLM_FALSE;
            bind[i].error = reinterpret_cast<my_bool*>(&error[i]);
        }
    };

    /// @brief Return columns in error
    ///
    /// If an error is returned from a fetch (in particular, a truncated
    /// status), this method can be called to get the names of the fields in
    /// error.  It returns a string comprising the names of the fields
    /// separated by commas.  In the case of there being no error indicators
    /// set, it returns the string "(None)".
    ///
    /// @param error Array of error elements.  An element is set to MLM_TRUE
    ///        if the corresponding column in the database is the source of
    ///        the error.
    /// @param names Array of column names, the same size as the error array.
    /// @param count Size of each of the arrays.
    static std::string getColumnsInError(std::vector<my_bools>& error,
                                         const std::vector<std::string>& names) {
        std::string result = "";

        // Accumulate list of column names
        for (size_t i = 0; i < names.size(); ++i) {
            if (error[i] == MLM_TRUE) {
                if (!result.empty()) {
                    result += ", ";
                }
                result += names[i];
            }
        }

        if (result.empty()) {
            result = "(None)";
        }

        return (result);
    };

    /// @brief Create MYSQL_BIND objects for Host Pointer
    ///
    /// Fills in the MYSQL_BIND array for sending data stored in the Host object
    /// to the database.
    ///
    /// @param host Host object to be added to the database.
    ///        None of the fields in the host reservation are modified -
    ///        the host data is only read.
    /// @param unique_ip boolean value indicating if multiple reservations for the
    ///        same IP address are allowed (false) or not (true).
    ///
    /// @return Vector of MySQL BIND objects representing the data to be added.
    std::vector<MYSQL_BIND> createBindForSend(const HostPtr& host, const bool unique_ip) {
        // Store host object to ensure it remains valid.
        host_ = host;

        // Initialize prior to constructing the array of MYSQL_BIND structures.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach.
        memset(&bind_[0], 0, sizeof(MYSQL_BIND) * bind_.size());

        // Set up the structures for the various components of the host structure.

        try {
            // host_id : INT UNSIGNED NOT NULL
            // The host_id is auto_incremented by MySQL database,
            // so we need to pass the NULL value
            host_id_ = 0;
            bind_[0].buffer_type = MYSQL_TYPE_LONG;
            bind_[0].buffer = reinterpret_cast<char*>(&host_id_);
            bind_[0].is_unsigned = MLM_TRUE;

            // dhcp_identifier : VARBINARY(128) NOT NULL
            dhcp_identifier_length_ = host->getIdentifier().size();
            memcpy(static_cast<void*>(dhcp_identifier_buffer_),
                   &(host->getIdentifier())[0],
                   host->getIdentifier().size());

            bind_[1].buffer_type = MYSQL_TYPE_BLOB;
            bind_[1].buffer = dhcp_identifier_buffer_;
            bind_[1].buffer_length = dhcp_identifier_length_;
            bind_[1].length = &dhcp_identifier_length_;

            // dhcp_identifier_type : TINYINT NOT NULL
            dhcp_identifier_type_ = static_cast<uint8_t>(host->getIdentifierType());
            bind_[2].buffer_type = MYSQL_TYPE_TINY;
            bind_[2].buffer = reinterpret_cast<char*>(&dhcp_identifier_type_);
            bind_[2].is_unsigned = MLM_TRUE;

            // dhcp4_subnet_id : INT UNSIGNED NULL
            // Can't take an address of intermediate object, so let's store it
            // in dhcp4_subnet_id_
            dhcp4_subnet_id_ = host->getIPv4SubnetID();
            dhcp4_subnet_id_null_ = host->getIPv4SubnetID() == SUBNET_ID_UNUSED ? MLM_TRUE : MLM_FALSE;
            bind_[3].buffer_type = MYSQL_TYPE_LONG;
            bind_[3].buffer = reinterpret_cast<char*>(&dhcp4_subnet_id_);
            bind_[3].is_unsigned = MLM_TRUE;
            bind_[3].is_null = &dhcp4_subnet_id_null_;

            // dhcp6_subnet_id : INT UNSIGNED NULL
            // Can't take an address of intermediate object, so let's store it
            // in dhcp6_subnet_id_
            dhcp6_subnet_id_ = host->getIPv6SubnetID();
            dhcp6_subnet_id_null_ = host->getIPv6SubnetID() == SUBNET_ID_UNUSED ? MLM_TRUE : MLM_FALSE;
            bind_[4].buffer_type = MYSQL_TYPE_LONG;
            bind_[4].buffer = reinterpret_cast<char*>(&dhcp6_subnet_id_);
            bind_[4].is_unsigned = MLM_TRUE;
            bind_[4].is_null = &dhcp6_subnet_id_null_;

            // ipv4_address : INT UNSIGNED NULL
            // The address in the Host structure is an IOAddress object.  Convert
            // this to an integer for storage.
            ipv4_address_ = host->getIPv4Reservation().toUint32();
            ipv4_address_null_ = ipv4_address_ == 0 ? MLM_TRUE : MLM_FALSE;
            bind_[5].buffer_type = MYSQL_TYPE_LONG;
            bind_[5].buffer = reinterpret_cast<char*>(&ipv4_address_);
            bind_[5].is_unsigned = MLM_TRUE;
            bind_[5].is_null = &ipv4_address_null_;

            // hostname : VARCHAR(255) NULL
            strncpy(hostname_, host->getHostname().c_str(), HOSTNAME_MAX_LEN - 1);
            hostname_length_ = host->getHostname().length();
            bind_[6].buffer_type = MYSQL_TYPE_STRING;
            bind_[6].buffer = reinterpret_cast<char*>(hostname_);
            bind_[6].buffer_length = hostname_length_;

            // dhcp4_client_classes : VARCHAR(255) NULL
            bind_[7].buffer_type = MYSQL_TYPE_STRING;
            // Override default separator to not include space after comma.
            string classes4_txt = host->getClientClasses4().toText(",");
            strncpy(dhcp4_client_classes_, classes4_txt.c_str(), CLIENT_CLASSES_MAX_LEN - 1);
            bind_[7].buffer = dhcp4_client_classes_;
            bind_[7].buffer_length = classes4_txt.length();

            // dhcp6_client_classes : VARCHAR(255) NULL
            bind_[8].buffer_type = MYSQL_TYPE_STRING;
            // Override default separator to not include space after comma.
            string classes6_txt = host->getClientClasses6().toText(",");
            strncpy(dhcp6_client_classes_, classes6_txt.c_str(), CLIENT_CLASSES_MAX_LEN - 1);
            bind_[8].buffer = dhcp6_client_classes_;
            bind_[8].buffer_length = classes6_txt.length();

            // user_context : TEXT NULL
            ConstElementPtr ctx = host->getContext();
            if (ctx) {
                bind_[9].buffer_type = MYSQL_TYPE_STRING;
                string ctx_txt = ctx->str();
                strncpy(user_context_, ctx_txt.c_str(), USER_CONTEXT_MAX_LEN - 1);
                bind_[9].buffer = user_context_;
                bind_[9].buffer_length = ctx_txt.length();
            } else {
                bind_[9].buffer_type = MYSQL_TYPE_NULL;
            }

            // ipv4_address : INT UNSIGNED NULL
            // The address in the Host structure is an IOAddress object.  Convert
            // this to an integer for storage.
            dhcp4_next_server_ = host->getNextServer().toUint32();
            bind_[10].buffer_type = MYSQL_TYPE_LONG;
            bind_[10].buffer = reinterpret_cast<char*>(&dhcp4_next_server_);
            bind_[10].is_unsigned = MLM_TRUE;
            // bind_[10].is_null = &MLM_FALSE; // commented out for performance
                                               // reasons, see memset() above

            // dhcp4_server_hostname
            bind_[11].buffer_type = MYSQL_TYPE_STRING;
            std::string server_hostname = host->getServerHostname();
            strncpy(dhcp4_server_hostname_, server_hostname.c_str(),
                    SERVER_HOSTNAME_MAX_LEN - 1);
            bind_[11].buffer = dhcp4_server_hostname_;
            bind_[11].buffer_length = server_hostname.length();

            // dhcp4_boot_file_name
            bind_[12].buffer_type = MYSQL_TYPE_STRING;
            std::string boot_file_name = host->getBootFileName();
            strncpy(dhcp4_boot_file_name_, boot_file_name.c_str(),
                    BOOT_FILE_NAME_MAX_LEN - 1);
            bind_[12].buffer = dhcp4_boot_file_name_;
            bind_[12].buffer_length = boot_file_name.length();

            // auth key
            bind_[13].buffer_type = MYSQL_TYPE_STRING;
            std::string auth_key = host->getKey().toText();
            std::strncpy(auth_key_, auth_key.c_str(), TEXT_AUTH_KEY_LEN - 1);
            auth_key_null_ =  auth_key.empty() ? MLM_TRUE : MLM_FALSE;
            bind_[13].buffer = auth_key_;
            bind_[13].buffer_length = auth_key.length();

        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from Host: "
                      << host->getHostname() << ", reason: " << ex.what());
        }

        // Add the data to the vector.
        std::vector<MYSQL_BIND> vec(bind_.begin(), bind_.begin() + HOST_COLUMNS);

        // When checking whether the IP is unique we need to bind the IPv4 address
        // at the end of the query as it has additional binding for the IPv4
        // address.
        if (unique_ip) {
            vec.push_back(bind_[5]); // ipv4_address
            vec.push_back(bind_[3]); // subnet_id
        }
        return (vec);
    };

    /// @brief Create BIND array to receive Host data.
    ///
    /// Creates a MYSQL_BIND array to receive Host data from the database.
    /// After data is successfully received, @ref retrieveHost can be called
    /// to retrieve the Host object.
    ///
    /// @return Vector of MYSQL_BIND objects representing data to be retrieved.
    virtual std::vector<MYSQL_BIND> createBindForReceive() {
        // Initialize MYSQL_BIND array.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        // This also takes care of setting bind_[X].is_null to MLM_FALSE.
        memset(&bind_[0], 0, sizeof(MYSQL_BIND) * bind_.size());

        // host_id : INT UNSIGNED NOT NULL
        bind_[0].buffer_type = MYSQL_TYPE_LONG;
        bind_[0].buffer = reinterpret_cast<char*>(&host_id_);
        bind_[0].is_unsigned = MLM_TRUE;

        // dhcp_identifier : VARBINARY(128) NOT NULL
        dhcp_identifier_length_ = sizeof(dhcp_identifier_buffer_);
        bind_[1].buffer_type = MYSQL_TYPE_BLOB;
        bind_[1].buffer = reinterpret_cast<char*>(dhcp_identifier_buffer_);
        bind_[1].buffer_length = dhcp_identifier_length_;
        bind_[1].length = &dhcp_identifier_length_;

        // dhcp_identifier_type : TINYINT NOT NULL
        bind_[2].buffer_type = MYSQL_TYPE_TINY;
        bind_[2].buffer = reinterpret_cast<char*>(&dhcp_identifier_type_);
        bind_[2].is_unsigned = MLM_TRUE;

        // dhcp4_subnet_id : INT UNSIGNED NULL
        dhcp4_subnet_id_null_ = MLM_FALSE;
        bind_[3].buffer_type = MYSQL_TYPE_LONG;
        bind_[3].buffer = reinterpret_cast<char*>(&dhcp4_subnet_id_);
        bind_[3].is_unsigned = MLM_TRUE;
        bind_[3].is_null = &dhcp4_subnet_id_null_;

        // dhcp6_subnet_id : INT UNSIGNED NULL
        dhcp6_subnet_id_null_ = MLM_FALSE;
        bind_[4].buffer_type = MYSQL_TYPE_LONG;
        bind_[4].buffer = reinterpret_cast<char*>(&dhcp6_subnet_id_);
        bind_[4].is_unsigned = MLM_TRUE;
        bind_[4].is_null = &dhcp6_subnet_id_null_;

        // ipv4_address : INT UNSIGNED NULL
        ipv4_address_null_ = MLM_FALSE;
        bind_[5].buffer_type = MYSQL_TYPE_LONG;
        bind_[5].buffer = reinterpret_cast<char*>(&ipv4_address_);
        bind_[5].is_unsigned = MLM_TRUE;
        bind_[5].is_null = &ipv4_address_null_;

        // hostname : VARCHAR(255) NULL
        hostname_null_ = MLM_FALSE;
        hostname_length_ = sizeof(hostname_);
        bind_[6].buffer_type = MYSQL_TYPE_STRING;
        bind_[6].buffer = reinterpret_cast<char*>(hostname_);
        bind_[6].buffer_length = hostname_length_;
        bind_[6].length = &hostname_length_;
        bind_[6].is_null = &hostname_null_;

        // dhcp4_client_classes : VARCHAR(255) NULL
        dhcp4_client_classes_null_ = MLM_FALSE;
        dhcp4_client_classes_length_ = sizeof(dhcp4_client_classes_);
        bind_[7].buffer_type = MYSQL_TYPE_STRING;
        bind_[7].buffer = reinterpret_cast<char*>(dhcp4_client_classes_);
        bind_[7].buffer_length = dhcp4_client_classes_length_;
        bind_[7].length = &dhcp4_client_classes_length_;
        bind_[7].is_null = &dhcp4_client_classes_null_;

        // dhcp6_client_classes : VARCHAR(255) NULL
        dhcp6_client_classes_null_ = MLM_FALSE;
        dhcp6_client_classes_length_ = sizeof(dhcp6_client_classes_);
        bind_[8].buffer_type = MYSQL_TYPE_STRING;
        bind_[8].buffer = reinterpret_cast<char*>(dhcp6_client_classes_);
        bind_[8].buffer_length = dhcp6_client_classes_length_;
        bind_[8].length = &dhcp6_client_classes_length_;
        bind_[8].is_null = &dhcp6_client_classes_null_;

        // user_context : TEXT NULL
        user_context_null_ = MLM_FALSE;
        user_context_length_ = sizeof(user_context_);
        bind_[9].buffer_type = MYSQL_TYPE_STRING;
        bind_[9].buffer = reinterpret_cast<char*>(user_context_);
        bind_[9].buffer_length = user_context_length_;
        bind_[9].length = &user_context_length_;
        bind_[9].is_null = &user_context_null_;

        // dhcp4_next_server
        dhcp4_next_server_null_ = MLM_FALSE;
        bind_[10].buffer_type = MYSQL_TYPE_LONG;
        bind_[10].buffer = reinterpret_cast<char*>(&dhcp4_next_server_);
        bind_[10].is_unsigned = MLM_TRUE;
        bind_[10].is_null = &dhcp4_next_server_null_;

        // dhcp4_server_hostname
        dhcp4_server_hostname_null_ = MLM_FALSE;
        dhcp4_server_hostname_length_ = sizeof(dhcp4_server_hostname_);
        bind_[11].buffer_type = MYSQL_TYPE_STRING;
        bind_[11].buffer = reinterpret_cast<char*>(dhcp4_server_hostname_);
        bind_[11].buffer_length = dhcp4_server_hostname_length_;
        bind_[11].length = &dhcp4_server_hostname_length_;
        bind_[11].is_null = &dhcp4_server_hostname_null_;

        // dhcp4_boot_file_name
        dhcp4_boot_file_name_null_ = MLM_FALSE;
        dhcp4_boot_file_name_length_ = sizeof(dhcp4_boot_file_name_);
        bind_[12].buffer_type = MYSQL_TYPE_STRING;
        bind_[12].buffer = reinterpret_cast<char*>(dhcp4_boot_file_name_);
        bind_[12].buffer_length = dhcp4_boot_file_name_length_;
        bind_[12].length = &dhcp4_boot_file_name_length_;
        bind_[12].is_null = &dhcp4_boot_file_name_null_;

        // auth_key_
        auth_key_null_ = MLM_FALSE;
        auth_key_length_ = sizeof(auth_key_);
        bind_[13].buffer_type = MYSQL_TYPE_STRING;
        bind_[13].buffer = reinterpret_cast<char*>(auth_key_);
        bind_[13].buffer_length = auth_key_length_;
        bind_[13].length = &auth_key_length_;
        bind_[13].is_null = &auth_key_null_;

        // Add the error flags
        setErrorIndicators(bind_, error_);

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return (bind_);
    };

    /// @brief Copy received data into Host object
    ///
    /// This function copies information about the host into a newly created
    /// @ref Host object. This method is called after @ref createBindForReceive.
    /// has been used.
    ///
    /// @return Host Pointer to a @ref HostPtr object holding a pointer to the
    /// @ref Host object returned.
    HostPtr retrieveHost() {
        // Check if the identifier stored in the database is correct.
        if (dhcp_identifier_type_ > MAX_IDENTIFIER_TYPE) {
            isc_throw(BadValue, "invalid dhcp identifier type returned: "
                      << static_cast<int>(dhcp_identifier_type_));
        }
        // Set the dhcp identifier type in a variable of the appropriate
        // data type.
        Host::IdentifierType type =
            static_cast<Host::IdentifierType>(dhcp_identifier_type_);

        // Set DHCPv4 subnet ID to the value returned. If NULL returned,
        // set to 0.
        SubnetID ipv4_subnet_id(SUBNET_ID_UNUSED);
        if (dhcp4_subnet_id_null_ == MLM_FALSE) {
            ipv4_subnet_id = static_cast<SubnetID>(dhcp4_subnet_id_);
        }

        // Set DHCPv6 subnet ID to the value returned. If NULL returned,
        // set to 0.
        SubnetID ipv6_subnet_id(SUBNET_ID_UNUSED);
        if (dhcp6_subnet_id_null_ == MLM_FALSE) {
            ipv6_subnet_id = static_cast<SubnetID>(dhcp6_subnet_id_);
        }

        // Set IPv4 address reservation if it was given, if not, set IPv4 zero
        // address
        asiolink::IOAddress ipv4_reservation = asiolink::IOAddress::IPV4_ZERO_ADDRESS();
        if (ipv4_address_null_ == MLM_FALSE) {
            ipv4_reservation = asiolink::IOAddress(ipv4_address_);
        }

        // Set hostname if non NULL value returned. Otherwise, leave an
        // empty string.
        std::string hostname;
        if (hostname_null_ == MLM_FALSE) {
            hostname = std::string(hostname_, hostname_length_);
        }

        // Set DHCPv4 client classes if non NULL value returned.
        std::string dhcp4_client_classes;
        if (dhcp4_client_classes_null_ == MLM_FALSE) {
            dhcp4_client_classes = std::string(dhcp4_client_classes_,
                                               dhcp4_client_classes_length_);
        }

        // Set DHCPv6 client classes if non NULL value returned.
        std::string dhcp6_client_classes;
        if (dhcp6_client_classes_null_ == MLM_FALSE) {
            dhcp6_client_classes = std::string(dhcp6_client_classes_,
                                               dhcp6_client_classes_length_);
        }

        // Convert user_context to string as well.
        std::string user_context;
        if (user_context_null_ == MLM_FALSE) {
            user_context_[user_context_length_] = '\0';
            user_context.assign(user_context_);
        }

        // Set next server value (siaddr) if non NULL value returned.
        asiolink::IOAddress next_server = asiolink::IOAddress::IPV4_ZERO_ADDRESS();
        if (dhcp4_next_server_null_ == MLM_FALSE) {
            next_server = asiolink::IOAddress(dhcp4_next_server_);
        }

        // Set server hostname (sname) if non NULL value returned.
        std::string dhcp4_server_hostname;
        if (dhcp4_server_hostname_null_ == MLM_FALSE) {
            dhcp4_server_hostname = std::string(dhcp4_server_hostname_,
                                                dhcp4_server_hostname_length_);
        }

        // Set boot file name (file) if non NULL value returned.
        std::string dhcp4_boot_file_name;
        if (dhcp4_boot_file_name_null_ == MLM_FALSE) {
            dhcp4_boot_file_name = std::string(dhcp4_boot_file_name_,
                                               dhcp4_boot_file_name_length_);
        }

        // Set the auth key if a non empty array is retrieved
        std::string auth_key;
        if (auth_key_null_ == MLM_FALSE) {
            auth_key = std::string(auth_key_, auth_key_length_);
        }

        // Create and return Host object from the data gathered.
        HostPtr h(new Host(dhcp_identifier_buffer_, dhcp_identifier_length_,
                           type, ipv4_subnet_id, ipv6_subnet_id, ipv4_reservation,
                           hostname, dhcp4_client_classes, dhcp6_client_classes,
                           next_server, dhcp4_server_hostname,
                           dhcp4_boot_file_name, AuthKey(auth_key)));
        h->setHostId(host_id_);

        // Set the user context if there is one.
        if (!user_context.empty()) {
            try {
                ConstElementPtr ctx = Element::fromJSON(user_context);
                if (!ctx || (ctx->getType() != Element::map)) {
                    isc_throw(BadValue, "user context '" << user_context
                              << "' is not a JSON map");
                }
                h->setContext(ctx);
            } catch (const isc::data::JSONError& ex) {
                isc_throw(BadValue, "user context '" << user_context
                          << "' is invalid JSON: " << ex.what());
            }
        }

        return (h);
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
    virtual void processFetchedData(ConstHostCollection& hosts) {
        HostPtr host;
        // Add new host only if there are no hosts yet or the host id of the
        // most recently added host is different than the host id of the
        // currently processed host.
        if (hosts.empty() || (hosts.back()->getHostId() != getHostId())) {
            // Create Host object from the fetched data and append it to the
            // collection.
            host = retrieveHost();
            hosts.push_back(host);
        }
    }

    /// @brief Return columns in error
    ///
    /// If an error is returned from a fetch (in particular, a truncated
    /// status), this method can be called to get the names of the fields in
    /// error.  It returns a string comprising the names of the fields
    /// separated by commas.  In the case of there being no error indicators
    /// set, it returns the string "(None)".
    ///
    /// @return Comma-separated list of columns in error, or the string
    ///         "(None)".
    std::string getErrorColumns() {
        return (getColumnsInError(error_, columns_));
    };

protected:

    /// Number of columns returned in queries.
    size_t columns_num_;

    /// Vector of MySQL bindings.
    std::vector<MYSQL_BIND> bind_;

    /// Column names.
    std::vector<std::string> columns_;

    /// Error array.
    std::vector<my_bools> error_;

    /// Pointer to Host object holding information to be inserted into
    /// Hosts table.
    HostPtr host_;

private:

    /// Host identifier (primary key in Hosts table).
    uint64_t host_id_;

    /// Buffer holding client's identifier (e.g. DUID, HW address)
    /// in the binary format.
    uint8_t dhcp_identifier_buffer_[DUID::MAX_DUID_LEN];

    /// Length of a data in the dhcp_identifier_buffer_.
    unsigned long dhcp_identifier_length_;

    /// Type of the identifier in the dhcp_identifier_buffer_. This
    /// value corresponds to the @ref Host::IdentifierType value.
    uint8_t dhcp_identifier_type_;

    /// DHCPv4 subnet identifier.
    uint32_t dhcp4_subnet_id_;

    /// DHCPv6 subnet identifier.
    uint32_t dhcp6_subnet_id_;

    /// Reserved IPv4 address.
    uint32_t ipv4_address_;

    /// Name reserved for the host.
    char hostname_[HOSTNAME_MAX_LEN];

    /// Hostname length.
    unsigned long hostname_length_;

    /// A string holding comma separated list of DHCPv4 client classes.
    char dhcp4_client_classes_[CLIENT_CLASSES_MAX_LEN];

    /// A length of the string holding comma separated list of DHCPv4
    /// client classes.
    unsigned long dhcp4_client_classes_length_;

    /// A string holding comma separated list of DHCPv6 client classes.
    char dhcp6_client_classes_[CLIENT_CLASSES_MAX_LEN];

    /// A length of the string holding comma separated list of DHCPv6
    /// client classes.
    unsigned long dhcp6_client_classes_length_;

    /// @brief Buffer holding textual user context.
    char user_context_[USER_CONTEXT_MAX_LEN];

    /// @brief User context length.
    unsigned long user_context_length_;

    /// Next server address (siaddr).
    uint32_t dhcp4_next_server_;

    /// Server hostname (sname).
    char dhcp4_server_hostname_[SERVER_HOSTNAME_MAX_LEN];

    /// A length of the string holding server hostname.
    unsigned long dhcp4_server_hostname_length_;

    /// Boot file name (file).
    char dhcp4_boot_file_name_[BOOT_FILE_NAME_MAX_LEN];

    /// A length of the string holding boot file name.
    unsigned long dhcp4_boot_file_name_length_;

    /// Authentication keys
    char auth_key_[TEXT_AUTH_KEY_LEN];

    /// The length of the string for holding keys
    unsigned long auth_key_length_;

    /// @name Boolean values indicating if values of specific columns in
    /// the database are NULL.
    //@{
    /// Boolean flag indicating if the value of the DHCPv4 subnet is NULL.
    my_bool dhcp4_subnet_id_null_;

    /// Boolean flag indicating if the value of the DHCPv6 subnet is NULL.
    my_bool dhcp6_subnet_id_null_;

    /// Boolean flag indicating if the value of IPv4 reservation is NULL.
    my_bool ipv4_address_null_;

    /// Boolean flag indicating if the value if hostname is NULL.
    my_bool hostname_null_;

    /// Boolean flag indicating if the value of DHCPv4 client classes is
    /// NULL.
    my_bool dhcp4_client_classes_null_;

    /// Boolean flag indicating if the value of DHCPv6 client classes is
    /// NULL.
    my_bool dhcp6_client_classes_null_;

    /// @brief Boolean flag indicating if the value of user context is NULL.
    my_bool user_context_null_;

    /// Boolean flag indicating if the value of next server is NULL.
    my_bool dhcp4_next_server_null_;

    /// Boolean flag indicating if the value of server hostname is NULL.
    my_bool dhcp4_server_hostname_null_;

    /// Boolean flag indicating if the value of boot file name is NULL.
    my_bool dhcp4_boot_file_name_null_;

    /// Boolean flag indicating if the value of string is NULL.
    my_bool auth_key_null_;

    //@}
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
class MySqlHostWithOptionsExchange : public MySqlHostExchange {
private:

    /// @brief Number of columns holding DHCPv4  or DHCPv6 option information.
    static const size_t OPTION_COLUMNS = 7;

    /// @brief Receives DHCPv4 or DHCPv6 options information from the
    /// dhcp4_options or dhcp6_options tables respectively.
    ///
    /// The MySqlHostWithOptionsExchange class holds two respective instances
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
          space_length_(0), persistent_(false), user_context_length_(0),
          option_id_null_(MLM_FALSE), code_null_(MLM_FALSE),
          value_null_(MLM_FALSE), formatted_value_null_(MLM_FALSE),
          space_null_(MLM_FALSE), user_context_null_(MLM_FALSE),
          option_id_index_(start_column), code_index_(start_column_ + 1),
          value_index_(start_column_ + 2),
          formatted_value_index_(start_column_ + 3),
          space_index_(start_column_ + 4),
          persistent_index_(start_column_ + 5),
          user_context_index_(start_column_ + 6),
          most_recent_option_id_(0) {

            memset(value_, 0, sizeof(value_));
            memset(formatted_value_, 0, sizeof(formatted_value_));
            memset(space_, 0, sizeof(space_));
            memset(user_context_, 0, sizeof(user_context_));
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

            // If empty or null space provided, use a default top level space.
            if (space.empty()) {
                space = (universe_ == Option::V4 ?
                         DHCP4_OPTION_SPACE : DHCP6_OPTION_SPACE);
            }

            // Convert formatted_value to string as well.
            std::string formatted_value;
            if (formatted_value_null_ == MLM_FALSE) {
                formatted_value_[formatted_value_length_] = '\0';
                formatted_value.assign(formatted_value_);
            }

            // Convert user_context to string as well.
            std::string user_context;
            if (user_context_null_ == MLM_FALSE) {
                user_context_[user_context_length_] = '\0';
                user_context.assign(user_context_);
            }

            // Options are held in a binary or textual format in the database.
            // This is similar to having an option specified in a server
            // configuration file. Such option is converted to appropriate C++
            // class, using option definition. Thus, we need to find the
            // option definition for this option code and option space.

            // Check if this is a standard option.
            OptionDefinitionPtr def = LibDHCP::getOptionDef(space, code_);

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

        /// @brief Initialize binding table fields for options.
        ///
        /// Resets most_recent_option_id_ to 0 and other exchange members to
        /// default values.
        ///
        /// @param [out] bind Binding table.
        void setBindFields(std::vector<MYSQL_BIND>& bind) {
            // This method is called just before making a new query, so we
            // reset the most_recent_option_id_ and other exchange members to
            // start over with options processing.
            most_recent_option_id_ = 0;

            option_id_ = 0;
            code_ = 0;
            persistent_ = false;
            option_id_null_ = MLM_FALSE;
            code_null_ = MLM_FALSE;
            value_null_ = MLM_FALSE;
            formatted_value_null_ = MLM_FALSE;
            space_null_ = MLM_FALSE;
            user_context_null_ = MLM_FALSE;

            memset(value_, 0, sizeof(value_));
            memset(formatted_value_, 0, sizeof(formatted_value_));
            memset(space_, 0, sizeof(space_));
            memset(user_context_, 0, sizeof(user_context_));

            // option_id : INT UNSIGNED NOT NULL AUTO_INCREMENT,
            bind[option_id_index_].buffer_type = MYSQL_TYPE_LONG;
            bind[option_id_index_].buffer = reinterpret_cast<char*>(&option_id_);
            bind[option_id_index_].is_unsigned = MLM_TRUE;
            bind[option_id_index_].is_null = &option_id_null_;

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

            // user_context : TEXT NULL
            user_context_length_ = sizeof(user_context_);
            bind[user_context_index_].buffer_type = MYSQL_TYPE_STRING;
            bind[user_context_index_].buffer = reinterpret_cast<char*>(user_context_);
            bind[user_context_index_].buffer_length = user_context_length_;
            bind[user_context_index_].length = &user_context_length_;
            bind[user_context_index_].is_null = &user_context_null_;
        }

    private:

        /// @brief Universe: V4 or V6.
        Option::Universe universe_;

        /// @brief Index of first column used by this class.
        size_t start_column_;

        /// @brief Option id.
        uint32_t option_id_;

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

        /// @brief Buffer holding textual user context of an option.
        char user_context_[USER_CONTEXT_MAX_LEN];

        /// @brief User context length.
        unsigned long user_context_length_;

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

        /// @brief Boolean flag indicating if the DHCPv4 option user context is NULL.
        my_bool user_context_null_;
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
        uint32_t most_recent_option_id_;
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
    MySqlHostWithOptionsExchange(const FetchedOptions& fetched_options,
                                 const size_t additional_columns_num = 0)
        : MySqlHostExchange(getRequiredColumnsNum(fetched_options)
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
        static_cast<void>(MySqlHostExchange::createBindForReceive());

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
/// This class extends the @ref MySqlHostWithOptionsExchange class with the
/// mechanisms to retrieve IPv6 reservations. This class is used in situations
/// when it is desired to retrieve DHCPv6 specific information about the host
/// (DHCPv6 options and reservations), or entire information about the host
/// (DHCPv4 options, DHCPv6 options and reservations). The following are the
/// queries used with this class:
/// - SELECT ? FROM hosts LEFT JOIN dhcp4_options LEFT JOIN dhcp6_options
///   LEFT JOIN ipv6_reservations ...
/// - SELECT ? FROM hosts LEFT JOIN dhcp6_options LEFT JOIN ipv6_reservations ..
class MySqlHostIPv6Exchange : public MySqlHostWithOptionsExchange {
private:

    /// @brief Number of columns holding IPv6 reservation information.
    static const size_t RESERVATION_COLUMNS = 5;

public:

    /// @brief Constructor.
    ///
    /// Apart from initializing the base class data structures it also
    /// initializes values representing IPv6 reservation information.
    MySqlHostIPv6Exchange(const FetchedOptions& fetched_options)
        : MySqlHostWithOptionsExchange(fetched_options, RESERVATION_COLUMNS),
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
    uint32_t getReservationId() const {
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
        MySqlHostWithOptionsExchange::processFetchedData(hosts);

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
        static_cast<void>(MySqlHostWithOptionsExchange::createBindForReceive());

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
    uint32_t reservation_id_;

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
    uint32_t iaid_;

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
    uint32_t most_recent_reservation_id_;
};

/// @brief This class is used for storing IPv6 reservations in a MySQL database.
///
/// This class is only used to insert IPv6 reservations into the
/// ipv6_reservations table. It is not used to retrieve IPv6 reservations. To
/// retrieve IPv6 reservation the @ref MySqlHostIPv6Exchange class should be
/// used instead.
///
/// When a new IPv6 reservation is inserted into the database, an appropriate
/// host must be defined in the hosts table. An attempt to insert IPv6
/// reservation for non-existing host will result in failure.
class MySqlIPv6ReservationExchange {
private:

    /// @brief Set number of columns for ipv6_reservation table.
    static const size_t RESRV_COLUMNS = 6;

public:

    /// @brief Constructor
    ///
    /// Initialize class members representing a single IPv6 reservation.
    MySqlIPv6ReservationExchange()
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
    /// @param unique_ip boolean value indicating if multiple reservations for the
    ///        same IP address are allowed (false) or not (true).
    ///
    /// @return Vector of MySQL BIND objects representing the data to be added.
    std::vector<MYSQL_BIND> createBindForSend(const IPv6Resrv& resv,
                                              const HostID& id,
                                              const bool unique_ip) {

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
        std::vector<MYSQL_BIND> vec(&bind_[0], &bind_[RESRV_COLUMNS-1]);

        // When checking whether the IP is unique we need to bind the IPv6 address
        // and prefix length at the end of the query as it has additional binding
        // for the IPv6 address and prefix length.
        if (unique_ip) {
            vec.push_back(bind_[0]); // address
            vec.push_back(bind_[1]); // prefix_len
        }

        return (vec);
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
class MySqlOptionExchange {
private:

    /// @brief Number of columns in the tables holding options.
    static const size_t OPTION_COLUMNS = 10;

public:

    /// @brief Constructor.
    MySqlOptionExchange()
        : type_(0), value_len_(0), formatted_value_len_(0), space_(),
          space_len_(0), persistent_(false), user_context_(),
          user_context_len_(0), subnet_id_(SUBNET_ID_UNUSED),
          host_id_(0), option_() {

        BOOST_STATIC_ASSERT(9 < OPTION_COLUMNS);
    }

    /// @brief Creates binding array to insert option data into database.
    ///
    /// @return Vector of MYSQL_BIND object representing an option.
    std::vector<MYSQL_BIND> createBindForSend(const OptionDescriptor& opt_desc,
                                              const std::string& opt_space,
                                              const Optional<SubnetID>& subnet_id,
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

            // user_context: TEST NULL,
            ConstElementPtr ctx = opt_desc.getContext();
            if (ctx) {
                user_context_ = ctx->str();
                user_context_len_ = user_context_.size();
                bind_[6].buffer_type = MYSQL_TYPE_STRING;
                bind_[6].buffer = const_cast<char*>(user_context_.c_str());
                bind_[6].buffer_length = user_context_len_;
                bind_[6].length = &user_context_len_;
            } else {
                bind_[6].buffer_type = MYSQL_TYPE_NULL;
            }

            // dhcp4_subnet_id: INT UNSIGNED NULL
            if (!subnet_id.unspecified()) {
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
    unsigned long value_len_;

    /// @brief Formatted option value length.
    unsigned long formatted_value_len_;

    /// @brief Option space name.
    std::string space_;

    /// @brief Option space name length.
    unsigned long space_len_;

    /// @brief Boolean flag indicating if the option is always returned to
    /// a client or only when requested.
    bool persistent_;

    /// @brief User context.
    std::string user_context_;

    /// @brief User context length.
    unsigned long user_context_len_;

    /// @brief Subnet identifier.
    uint32_t subnet_id_;

    /// @brief Host identifier.
    uint32_t host_id_;

    /// @brief Pointer to currently parsed option.
    OptionPtr option_;

    /// @brief Array of MYSQL_BIND elements representing inserted data.
    MYSQL_BIND bind_[OPTION_COLUMNS];
};

}  // namespace

namespace isc {
namespace dhcp {

/// @brief MySQL Host Context
///
/// This class stores the thread context for the manager pool.
/// The class is needed by all get/update/delete functions which must use one
/// or more exchanges to perform database operations.
/// Each context provides a set of such exchanges for each thread.
/// The context instances are lazy initialized by the requesting thread by using
/// the manager's createContext function and are destroyed when the manager's
/// pool instance is destroyed.
class MySqlHostContext {
public:

    /// @brief Constructor
    ///
    /// @param parameters See MySqlHostMgr constructor.
    /// @param io_service_accessor The IOService accessor function.
    /// @param db_reconnect_callback The connection recovery callback.
    MySqlHostContext(const DatabaseConnection::ParameterMap& parameters,
                     IOServiceAccessorPtr io_service_accessor,
                     db::DbCallback db_reconnect_callback);

    /// The exchange objects are used for transfer of data to/from the database.
    /// They are pointed-to objects as the contents may change in "const" calls,
    /// while the rest of this object does not.  (At alternative would be to
    /// declare them as "mutable".)

    /// @brief Pointer to an object representing an exchange which can
    /// be used to retrieve hosts and DHCPv4 options.
    boost::shared_ptr<MySqlHostWithOptionsExchange> host_ipv4_exchange_;

    /// @brief Pointer to an object representing an exchange which can
    /// be used to retrieve hosts, DHCPv6 options and IPv6 reservations.
    boost::shared_ptr<MySqlHostIPv6Exchange> host_ipv6_exchange_;

    /// @brief Pointer to an object representing an exchange which can
    /// be used to retrieve hosts, DHCPv4 and DHCPv6 options, and
    /// IPv6 reservations using a single query.
    boost::shared_ptr<MySqlHostIPv6Exchange> host_ipv46_exchange_;

    /// @brief Pointer to an object representing an exchange which can
    /// be used to insert new IPv6 reservation.
    boost::shared_ptr<MySqlIPv6ReservationExchange> host_ipv6_reservation_exchange_;

    /// @brief Pointer to an object representing an exchange which can
    /// be used to insert DHCPv4 or DHCPv6 option into dhcp4_options
    /// or dhcp6_options table.
    boost::shared_ptr<MySqlOptionExchange> host_option_exchange_;

    /// @brief MySQL connection
    MySqlConnection conn_;

    /// @brief Indicates if the database is opened in read only mode.
    bool is_readonly_;
};

/// @brief MySQL Host Context Pool
///
/// This class provides a pool of contexts.
/// The manager will use this class to handle available contexts.
/// There is only one ContextPool per manager per back-end, which is created
/// and destroyed by the respective manager factory class.
class MySqlHostContextPool {
public:

    /// @brief The vector of available contexts.
    std::vector<MySqlHostContextPtr> pool_;

    /// @brief The mutex to protect pool access.
    std::mutex mutex_;
};

/// @brief Type of pointers to context pools.
typedef boost::shared_ptr<MySqlHostContextPool> MySqlHostContextPoolPtr;

/// @brief Implementation of the @ref MySqlHostDataSource.
class MySqlHostDataSourceImpl {
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
    MySqlHostDataSourceImpl(const DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor.
    ~MySqlHostDataSourceImpl();

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
    MySqlHostContextPtr createContext() const;

    /// @brief Returns backend version.
    ///
    /// The method is called by the constructor before opening the database
    /// to verify that the schema version is correct.
    ///
    /// @return Version number stored in the database, as a pair of unsigned
    ///         integers. "first" is the major version number, "second" the
    ///         minor number.
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database
    ///        has failed.
    std::pair<uint32_t, uint32_t> getVersion() const;

    /// @brief Executes statements which inserts a row into one of the tables.
    ///
    /// @param ctx Context
    /// @param stindex Index of a statement being executed.
    /// @param bind Vector of MYSQL_BIND objects to be used when making the
    /// query.
    ///
    /// @throw isc::db::DuplicateEntry Database throws duplicate entry error
    void addStatement(MySqlHostContextPtr& ctx,
                      MySqlHostDataSourceImpl::StatementIndex stindex,
                      std::vector<MYSQL_BIND>& bind);

    /// @brief Executes statements that delete records.
    ///
    /// @param ctx Context
    /// @param stindex Index of a statement being executed.
    /// @param bind Vector of MYSQL_BIND objects to be used when making the
    /// query.
    ///
    /// @return true if any records were deleted, false otherwise
    bool delStatement(MySqlHostContextPtr& ctx,
                      StatementIndex stindex,
                      MYSQL_BIND* bind);

    /// @brief Inserts IPv6 Reservation into ipv6_reservation table.
    ///
    /// @param ctx Context
    /// @param resv IPv6 Reservation to be added
    /// @param id ID of a host owning this reservation
    void addResv(MySqlHostContextPtr& ctx,
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
    void addOption(MySqlHostContextPtr& ctx,
                   const MySqlHostDataSourceImpl::StatementIndex& stindex,
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
    /// @param host_id Host identifier retrieved using @c mysql_insert_id.
    void addOptions(MySqlHostContextPtr& ctx,
                    const StatementIndex& stindex,
                    const ConstCfgOptionPtr& options_cfg,
                    const uint64_t host_id);

    /// @brief Check Error and Throw Exception
    ///
    /// This method invokes @ref db::MySqlConnection::checkError.
    ///
    /// @param ctx Context
    /// @param status Status code: non-zero implies an error
    /// @param index Index of statement that caused the error
    /// @param what High-level description of the error
    ///
    /// @throw isc::dhcp::DbOperationError An operation on the open database has
    ///        failed.
    void checkError(MySqlHostContextPtr& ctx,
                    const int status,
                    const StatementIndex index,
                    const char* what) const;

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
    /// @param bind Pointer to an array of MySQL bindings.
    /// @param exchange Pointer to the exchange object used for the
    /// particular query.
    /// @param [out] result Reference to the collection of hosts returned.
    /// @param single A boolean value indicating if a single host is
    /// expected to be returned, or multiple hosts.
    void getHostCollection(MySqlHostContextPtr& ctx,
                           StatementIndex stindex,
                           MYSQL_BIND* bind,
                           boost::shared_ptr<MySqlHostExchange> exchange,
                           ConstHostCollection& result,
                           bool single) const;

    /// @brief Retrieves a host by subnet and client's unique identifier.
    ///
    /// This method is used by both MySqlHostDataSource::get4 and
    /// MySqlHOstDataSource::get6 methods.
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
    ConstHostPtr getHost(MySqlHostContextPtr& ctx,
                         const SubnetID& subnet_id,
                         const Host::IdentifierType& identifier_type,
                         const uint8_t* identifier_begin,
                         const size_t identifier_len,
                         StatementIndex stindex,
                         boost::shared_ptr<MySqlHostExchange> exchange) const;

    /// @brief Throws exception if database is read only.
    ///
    /// This method should be called by the methods which write to the
    /// database. If the backend is operating in read-only mode this
    /// method will throw exception.
    ///
    /// @param ctx Context
    ///
    /// @throw DbReadOnly if backend is operating in read only mode.
    void checkReadOnly(MySqlHostContextPtr& ctx) const;

    /// @brief The parameters
    DatabaseConnection::ParameterMap parameters_;

    /// @brief Holds the setting whether the IP reservations must be unique or
    /// may be non-unique.
    bool ip_reservations_unique_;

    /// @brief The pool of contexts
    MySqlHostContextPoolPtr pool_;

    /// @brief Indicates if there is at least one connection that can no longer
    /// be used for normal operations.
    bool unusable_;

    /// @brief Timer name used to register database reconnect timer.
    std::string timer_name_;
};

namespace {

/// @brief Array of tagged statements.
typedef boost::array<TaggedStatement, MySqlHostDataSourceImpl::NUM_STATEMENTS>
TaggedStatementArray;

/// @brief Prepared MySQL statements used by the backend to insert and
/// retrieve hosts from the database.
TaggedStatementArray tagged_statements = { {
    // Retrieves host information, IPv6 reservations and both DHCPv4 and
    // DHCPv6 options associated with the host. The LEFT JOIN clause is used
    // to retrieve information from 4 different tables using a single query.
    // Hence, this query returns multiple rows for a single host.
    {MySqlHostDataSourceImpl::GET_HOST_DHCPID,
            "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
                "h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, "
                "h.hostname, h.dhcp4_client_classes, h.dhcp6_client_classes, "
                "h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o4.option_id, o4.code, o4.value, o4.formatted_value, o4.space, "
                "o4.persistent, o4.user_context, "
                "o6.option_id, o6.code, o6.value, o6.formatted_value, o6.space, "
                "o6.persistent, o6.user_context, "
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

    // Retrieves host information along with the DHCPv4 options associated with
    // it. Left joining the dhcp4_options table results in multiple rows being
    // returned for the same host. The host is retrieved by IPv4 address.
    {MySqlHostDataSourceImpl::GET_HOST_ADDR,
            "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
                "h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, o.user_context "
            "FROM hosts AS h "
            "LEFT JOIN dhcp4_options AS o "
                "ON h.host_id = o.host_id "
            "WHERE ipv4_address = ? "
            "ORDER BY h.host_id, o.option_id"},

    // Retrieves host information and DHCPv4 options using subnet identifier
    // and client's identifier. Left joining the dhcp4_options table results in
    // multiple rows being returned for the same host.
    {MySqlHostDataSourceImpl::GET_HOST_SUBID4_DHCPID,
            "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
                "h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, o.user_context "
            "FROM hosts AS h "
            "LEFT JOIN dhcp4_options AS o "
                "ON h.host_id = o.host_id "
            "WHERE h.dhcp4_subnet_id = ? AND h.dhcp_identifier_type = ? "
                "AND h.dhcp_identifier = ? "
            "ORDER BY h.host_id, o.option_id"},

    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // associated with a host. The number of rows returned is a multiplication
    // of number of IPv6 reservations and DHCPv6 options.
    {MySqlHostDataSourceImpl::GET_HOST_SUBID6_DHCPID,
            "SELECT h.host_id, h.dhcp_identifier, "
                "h.dhcp_identifier_type, h.dhcp4_subnet_id, "
                "h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, o.user_context, "
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

    // Retrieves host information and DHCPv4 options for the host using subnet
    // identifier and IPv4 reservation. Left joining the dhcp4_options table
    // results in multiple rows being returned for the host. The number of
    // rows depends on the number of options defined for the host.
    {MySqlHostDataSourceImpl::GET_HOST_SUBID_ADDR,
            "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
                "h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, o.user_context "
            "FROM hosts AS h "
            "LEFT JOIN dhcp4_options AS o "
                "ON h.host_id = o.host_id "
            "WHERE h.dhcp4_subnet_id = ? AND h.ipv4_address = ? "
            "ORDER BY h.host_id, o.option_id"},

    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // associated with a host using prefix and prefix length. This query
    // returns host information for a single host. However, multiple rows
    // are returned due to left joining IPv6 reservations and DHCPv6 options.
    // The number of rows returned is multiplication of number of existing
    // IPv6 reservations and DHCPv6 options.
    {MySqlHostDataSourceImpl::GET_HOST_PREFIX,
            "SELECT h.host_id, h.dhcp_identifier, "
                "h.dhcp_identifier_type, h.dhcp4_subnet_id, "
                "h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, o.user_context,"
                "r.reservation_id, r.address, r.prefix_len, r.type, "
                "r.dhcp6_iaid "
            "FROM hosts AS h "
            "LEFT JOIN dhcp6_options AS o "
                "ON h.host_id = o.host_id "
            "LEFT JOIN ipv6_reservations AS r "
                "ON h.host_id = r.host_id "
            "WHERE h.host_id = "
                "( SELECT host_id FROM ipv6_reservations "
                    "WHERE address = ? AND prefix_len = ? ) "
            "ORDER BY h.host_id, o.option_id, r.reservation_id"},

    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // associated with a host using IPv6 subnet id and prefix. This query
    // returns host information for a single host. However, multiple rows
    // are returned due to left joining IPv6 reservations and DHCPv6 options.
    // The number of rows returned is multiplication of number of existing
    // IPv6 reservations and DHCPv6 options.
    {MySqlHostDataSourceImpl::GET_HOST_SUBID6_ADDR,
            "SELECT h.host_id, h.dhcp_identifier, "
                "h.dhcp_identifier_type, h.dhcp4_subnet_id, "
                "h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, o.user_context, "
                "r.reservation_id, r.address, r.prefix_len, r.type, "
                "r.dhcp6_iaid "
            "FROM hosts AS h "
            "LEFT JOIN dhcp6_options AS o "
                "ON h.host_id = o.host_id "
            "LEFT JOIN ipv6_reservations AS r "
                "ON h.host_id = r.host_id "
            "WHERE h.dhcp6_subnet_id = ? AND r.address = ? "
            "ORDER BY h.host_id, o.option_id, r.reservation_id"},

    // Retrieves host information along with the DHCPv4 options associated with
    // it. Left joining the dhcp4_options table results in multiple rows being
    // returned for the same host. Hosts are retrieved by IPv4 subnet id.
    {MySqlHostDataSourceImpl::GET_HOST_SUBID4,
            "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
                "h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, o.user_context "
            "FROM hosts AS h "
            "LEFT JOIN dhcp4_options AS o "
                "ON h.host_id = o.host_id "
            "WHERE h.dhcp4_subnet_id = ? "
            "ORDER BY h.host_id, o.option_id"},

    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // associated with a host. The number of rows returned is a multiplication
    // of number of IPv6 reservations and DHCPv6 options. Hosts are retrieved
    // by IPv6 subnet id.
    {MySqlHostDataSourceImpl::GET_HOST_SUBID6,
            "SELECT h.host_id, h.dhcp_identifier, "
                "h.dhcp_identifier_type, h.dhcp4_subnet_id, "
                "h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, o.user_context, "
                "r.reservation_id, r.address, r.prefix_len, r.type, "
                "r.dhcp6_iaid "
            "FROM hosts AS h "
            "LEFT JOIN dhcp6_options AS o "
                "ON h.host_id = o.host_id "
            "LEFT JOIN ipv6_reservations AS r "
                "ON h.host_id = r.host_id "
            "WHERE h.dhcp6_subnet_id = ? "
            "ORDER BY h.host_id, o.option_id, r.reservation_id"},

    // Retrieves host information, IPv6 reservations and both DHCPv4 and
    // DHCPv6 options associated with the host. The LEFT JOIN clause is used
    // to retrieve information from 4 different tables using a single query.
    // Hence, this query returns multiple rows for a single host.
    {MySqlHostDataSourceImpl::GET_HOST_HOSTNAME,
            "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
                "h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, "
                "h.hostname, h.dhcp4_client_classes, h.dhcp6_client_classes, "
                "h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o4.option_id, o4.code, o4.value, o4.formatted_value, o4.space, "
                "o4.persistent, o4.user_context, "
                "o6.option_id, o6.code, o6.value, o6.formatted_value, o6.space, "
                "o6.persistent, o6.user_context, "
                "r.reservation_id, r.address, r.prefix_len, r.type, "
                "r.dhcp6_iaid "
            "FROM hosts AS h "
            "LEFT JOIN dhcp4_options AS o4 "
                "ON h.host_id = o4.host_id "
            "LEFT JOIN dhcp6_options AS o6 "
                "ON h.host_id = o6.host_id "
            "LEFT JOIN ipv6_reservations AS r "
                "ON h.host_id = r.host_id "
            "WHERE h.hostname = ? "
            "ORDER BY h.host_id, o4.option_id, o6.option_id, r.reservation_id"},

    // Retrieves host information and DHCPv4 options using hostname and
    // subnet identifier. Left joining the dhcp4_options table results in
    // multiple rows being returned for the same host.
    {MySqlHostDataSourceImpl::GET_HOST_HOSTNAME_SUBID4,
            "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
                "h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, o.user_context "
            "FROM hosts AS h "
            "LEFT JOIN dhcp4_options AS o "
                "ON h.host_id = o.host_id "
            "WHERE h.hostname = ? AND h.dhcp4_subnet_id = ? "
            "ORDER BY h.host_id, o.option_id"},

    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // using hostname and subnet identifier. The number of rows returned
    // is a multiplication of number of IPv6 reservations and DHCPv6 options.
    {MySqlHostDataSourceImpl::GET_HOST_HOSTNAME_SUBID6,
            "SELECT h.host_id, h.dhcp_identifier, "
                "h.dhcp_identifier_type, h.dhcp4_subnet_id, "
                "h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, o.user_context, "
                "r.reservation_id, r.address, r.prefix_len, r.type, "
                "r.dhcp6_iaid "
            "FROM hosts AS h "
            "LEFT JOIN dhcp6_options AS o "
                "ON h.host_id = o.host_id "
            "LEFT JOIN ipv6_reservations AS r "
                "ON h.host_id = r.host_id "
            "WHERE h.hostname = ? AND h.dhcp6_subnet_id = ? "
            "ORDER BY h.host_id, o.option_id, r.reservation_id"},

    // Retrieves host information along with the DHCPv4 options associated with
    // it. Left joining the dhcp4_options table results in multiple rows being
    // returned for the same host. Hosts are retrieved by IPv4 subnet id
    // and with a host id greater than the start one.
    // The number of hosts returned is lower or equal to the limit.
    {MySqlHostDataSourceImpl::GET_HOST_SUBID4_PAGE,
            "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
                "h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, o.user_context "
            "FROM ( SELECT * FROM hosts AS h "
                    "WHERE h.dhcp4_subnet_id = ? AND h.host_id > ? "
                    "ORDER BY h.host_id "
                    "LIMIT ? ) AS h "
            "LEFT JOIN dhcp4_options AS o "
                "ON h.host_id = o.host_id "
            "ORDER BY h.host_id, o.option_id"},

    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // associated with a host. The number of rows returned is a multiplication
    // of number of IPv6 reservations and DHCPv6 options. Hosts are retrieved
    // by IPv6 subnet id and with a host id greater than the start one.
    // The number of hosts returned is lower or equal to the limit.
    {MySqlHostDataSourceImpl::GET_HOST_SUBID6_PAGE,
            "SELECT h.host_id, h.dhcp_identifier, "
                "h.dhcp_identifier_type, h.dhcp4_subnet_id, "
                "h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, o.user_context, "
                "r.reservation_id, r.address, r.prefix_len, r.type, "
                "r.dhcp6_iaid "
            "FROM ( SELECT * FROM hosts AS h "
                    "WHERE h.dhcp6_subnet_id = ? AND h.host_id > ? "
                    "ORDER BY h.host_id "
                    "LIMIT ? ) AS h "
            "LEFT JOIN dhcp6_options AS o "
                "ON h.host_id = o.host_id "
            "LEFT JOIN ipv6_reservations AS r "
                "ON h.host_id = r.host_id "
            "ORDER BY h.host_id, o.option_id, r.reservation_id"},

    // Retrieves host information along with the DHCPv4 options associated with
    // it. Left joining the dhcp4_options table results in multiple rows being
    // returned for the same host. Hosts are retrieved with a host id greater
    // than the start one.
    // The number of hosts returned is lower or equal to the limit.
    {MySqlHostDataSourceImpl::GET_HOST_PAGE4,
            "SELECT h.host_id, h.dhcp_identifier, h.dhcp_identifier_type, "
                "h.dhcp4_subnet_id, h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, o.user_context "
            "FROM ( SELECT * FROM hosts AS h "
                    "WHERE h.host_id > ? "
                    "ORDER BY h.host_id "
                    "LIMIT ? ) AS h "
            "LEFT JOIN dhcp4_options AS o "
                "ON h.host_id = o.host_id "
            "ORDER BY h.host_id, o.option_id"},

    // Retrieves host information, IPv6 reservations and DHCPv6 options
    // associated with a host. The number of rows returned is a multiplication
    // of number of IPv6 reservations and DHCPv6 options. Hosts are retrieved
    // with a host id greater than the start one.
    // The number of hosts returned is lower or equal to the limit.
    {MySqlHostDataSourceImpl::GET_HOST_PAGE6,
            "SELECT h.host_id, h.dhcp_identifier, "
                "h.dhcp_identifier_type, h.dhcp4_subnet_id, "
                "h.dhcp6_subnet_id, h.ipv4_address, h.hostname, "
                "h.dhcp4_client_classes, h.dhcp6_client_classes, h.user_context, "
                "h.dhcp4_next_server, h.dhcp4_server_hostname, "
                "h.dhcp4_boot_file_name, h.auth_key, "
                "o.option_id, o.code, o.value, o.formatted_value, o.space, "
                "o.persistent, o.user_context, "
                "r.reservation_id, r.address, r.prefix_len, r.type, "
                "r.dhcp6_iaid "
            "FROM ( SELECT * FROM hosts AS h "
                    "WHERE h.host_id > ? "
                    "ORDER BY h.host_id "
                    "LIMIT ? ) AS h "
            "LEFT JOIN dhcp6_options AS o "
                "ON h.host_id = o.host_id "
            "LEFT JOIN ipv6_reservations AS r "
                "ON h.host_id = r.host_id "
            "ORDER BY h.host_id, o.option_id, r.reservation_id"},

    // Inserts a host into the 'hosts' table without checking that there is
    // a reservation for the IP address.
    {MySqlHostDataSourceImpl::INSERT_HOST_NON_UNIQUE_IP,
            "INSERT INTO hosts(host_id, dhcp_identifier, dhcp_identifier_type, "
                "dhcp4_subnet_id, dhcp6_subnet_id, ipv4_address, hostname, "
                "dhcp4_client_classes, dhcp6_client_classes, "
                "user_context, dhcp4_next_server, "
                "dhcp4_server_hostname, dhcp4_boot_file_name, auth_key) "
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"},

    // Inserts a host into the 'hosts' table with checking that reserved IP
    // address is unique. The innermost query checks if there is at least
    // one host for the given IP/subnet combination. For checking whether
    // hosts exists or not it doesn't matter if we select actual columns,
    // thus SELECT 1 was used as an optimization to avoid selecting data
    // that will be ignored anyway. If the host does not exist the new
    // host is inserted. DUAL is a special MySQL table from which we can
    // select the values to be inserted. If the host with the given IP
    // address already exists the new host won't be inserted. The caller
    // can check the number of affected rows to detect that there was
    // a duplicate host in the database.
    {MySqlHostDataSourceImpl::INSERT_HOST_UNIQUE_IP,
            "INSERT INTO hosts(host_id, dhcp_identifier, dhcp_identifier_type, "
                "dhcp4_subnet_id, dhcp6_subnet_id, ipv4_address, hostname, "
                "dhcp4_client_classes, dhcp6_client_classes, "
                "user_context, dhcp4_next_server, "
                "dhcp4_server_hostname, dhcp4_boot_file_name, auth_key) "
                "SELECT ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? FROM DUAL "
                    "WHERE NOT EXISTS ("
                        "SELECT 1 FROM hosts "
                            "WHERE ipv4_address = ? AND dhcp4_subnet_id = ? "
                        "LIMIT 1"
                    ")"},

    // Inserts a single IPv6 reservation into 'reservations' table without
    // checking that the inserted reservation is unique.
    {MySqlHostDataSourceImpl::INSERT_V6_RESRV_NON_UNIQUE,
            "INSERT INTO ipv6_reservations(address, prefix_len, type, "
                "dhcp6_iaid, host_id) "
            "VALUES (?, ?, ?, ?, ?)"},

    // Inserts a single IPv6 reservation into 'reservations' table with
    // checking that the inserted reservation is unique.
    {MySqlHostDataSourceImpl::INSERT_V6_RESRV_UNIQUE,
            "INSERT INTO ipv6_reservations(address, prefix_len, type, "
                "dhcp6_iaid, host_id) "
                "SELECT ?, ?, ?, ?, ? FROM DUAL "
                    "WHERE NOT EXISTS ("
                        "SELECT 1 FROM ipv6_reservations "
                            "WHERE address = ? AND prefix_len = ? "
                        "LIMIT 1"
                    ")"},

    // Inserts a single DHCPv4 option into 'dhcp4_options' table.
    // Using fixed scope_id = 3, which associates an option with host.
    {MySqlHostDataSourceImpl::INSERT_V4_HOST_OPTION,
            "INSERT INTO dhcp4_options(option_id, code, value, formatted_value, space, "
                "persistent, user_context, dhcp4_subnet_id, host_id, scope_id) "
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, 3)"},

    // Inserts a single DHCPv6 option into 'dhcp6_options' table.
    // Using fixed scope_id = 3, which associates an option with host.
    {MySqlHostDataSourceImpl::INSERT_V6_HOST_OPTION,
            "INSERT INTO dhcp6_options(option_id, code, value, formatted_value, space, "
                "persistent, user_context, dhcp6_subnet_id, host_id, scope_id) "
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, 3)"},

    // Delete IPv4 reservations by subnet id and reserved address.
    {MySqlHostDataSourceImpl::DEL_HOST_ADDR4,
            "DELETE FROM hosts WHERE dhcp4_subnet_id = ? AND ipv4_address = ?"},

    // Delete IPv6 reservations by subnet id and reserved address/prefix.
    {MySqlHostDataSourceImpl::DEL_HOST_ADDR6,
            "DELETE h FROM hosts AS h "
            "INNER JOIN ipv6_reservations AS r "
                "ON h.host_id = r.host_id "
            "WHERE h.dhcp6_subnet_id = ? AND r.address = ?"},

    // Delete a single IPv4 reservation by subnet id and identifier.
    {MySqlHostDataSourceImpl::DEL_HOST_SUBID4_ID,
            "DELETE FROM hosts WHERE dhcp4_subnet_id = ? AND dhcp_identifier_type=? "
            "AND dhcp_identifier = ?"},

    // Delete a single IPv6 reservation by subnet id and identifier.
    {MySqlHostDataSourceImpl::DEL_HOST_SUBID6_ID,
            "DELETE FROM hosts WHERE dhcp6_subnet_id = ? AND dhcp_identifier_type=? "
            "AND dhcp_identifier = ?"}
    }
};

}  // namespace

// MySqlHostContext Constructor

MySqlHostContext::MySqlHostContext(const DatabaseConnection::ParameterMap& parameters,
                                   IOServiceAccessorPtr io_service_accessor,
                                   db::DbCallback db_reconnect_callback)
    : conn_(parameters, io_service_accessor, db_reconnect_callback),
      is_readonly_(true) {
}

// MySqlHostContextAlloc Constructor and Destructor

MySqlHostDataSource::MySqlHostContextAlloc::MySqlHostContextAlloc(
    MySqlHostDataSourceImpl& mgr) : ctx_(), mgr_(mgr) {

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
            isc_throw(Unexpected, "No available MySQL host context?!");
        }
        ctx_ = mgr_.pool_->pool_.back();
    }
}

MySqlHostDataSource::MySqlHostContextAlloc::~MySqlHostContextAlloc() {
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

MySqlHostDataSourceImpl::MySqlHostDataSourceImpl(const DatabaseConnection::ParameterMap& parameters)
    : parameters_(parameters), ip_reservations_unique_(true), unusable_(false),
      timer_name_("") {

    // Create unique timer name per instance.
    timer_name_ = "MySqlHostMgr[";
    timer_name_ += boost::lexical_cast<std::string>(reinterpret_cast<uint64_t>(this));
    timer_name_ += "]DbReconnectTimer";

    // Validate the schema version first.
    std::pair<uint32_t, uint32_t> code_version(MYSQL_SCHEMA_VERSION_MAJOR,
                                               MYSQL_SCHEMA_VERSION_MINOR);
    std::pair<uint32_t, uint32_t> db_version = getVersion();
    if (code_version != db_version) {
        isc_throw(DbOpenError,
                  "MySQL schema version mismatch: need version: "
                      << code_version.first << "." << code_version.second
                      << " found version: " << db_version.first << "."
                      << db_version.second);
    }

    // Create an initial context.
    pool_.reset(new MySqlHostContextPool());
    pool_->pool_.push_back(createContext());
}

// Create context.

MySqlHostContextPtr
MySqlHostDataSourceImpl::createContext() const {
    MySqlHostContextPtr ctx(new MySqlHostContext(parameters_,
        IOServiceAccessorPtr(new IOServiceAccessor(&HostMgr::getIOService)),
        &MySqlHostDataSourceImpl::dbReconnect));

    // Open the database.
    ctx->conn_.openDatabase();

    // Prepare query statements. Those are will be only used to retrieve
    // information from the database, so they can be used even if the
    // database is read only for the current user.
    ctx->conn_.prepareStatements(tagged_statements.begin(),
                                 tagged_statements.begin() + WRITE_STMTS_BEGIN);

    // Check if the backend is explicitly configured to operate with
    // read only access to the database.
    ctx->is_readonly_ = ctx->conn_.configuredReadOnly();

    // If we are using read-write mode for the database we also prepare
    // statements for INSERTS etc.
    if (!ctx->is_readonly_) {
        // Prepare statements for writing to the database, e.g. INSERT.
        ctx->conn_.prepareStatements(tagged_statements.begin() + WRITE_STMTS_BEGIN,
                                     tagged_statements.end());
    } else {
        LOG_INFO(dhcpsrv_logger, DHCPSRV_MYSQL_HOST_DB_READONLY);
    }

    // Create the exchange objects for use in exchanging data between the
    // program and the database.
    ctx->host_ipv4_exchange_.reset(new MySqlHostWithOptionsExchange(MySqlHostWithOptionsExchange::DHCP4_ONLY));
    ctx->host_ipv6_exchange_.reset(new MySqlHostIPv6Exchange(MySqlHostWithOptionsExchange::DHCP6_ONLY));
    ctx->host_ipv46_exchange_.reset(new MySqlHostIPv6Exchange(MySqlHostWithOptionsExchange::DHCP4_AND_DHCP6));
    ctx->host_ipv6_reservation_exchange_.reset(new MySqlIPv6ReservationExchange());
    ctx->host_option_exchange_.reset(new MySqlOptionExchange());

    // Create ReconnectCtl for this connection.
    ctx->conn_.makeReconnectCtl(timer_name_);

    return (ctx);
}

MySqlHostDataSourceImpl::~MySqlHostDataSourceImpl() {
}

bool
MySqlHostDataSourceImpl::dbReconnect(ReconnectCtlPtr db_reconnect_ctl) {
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
            if (HostMgr::delBackend("mysql", hds, true)) {
                HostMgr::addBackend(hds);
            }
        }
        reopened = true;
    } catch (const std::exception& ex) {
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_MYSQL_HOST_DB_RECONNECT_ATTEMPT_FAILED)
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
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_MYSQL_HOST_DB_RECONNECT_FAILED)
                    .arg(db_reconnect_ctl->maxRetries());

            // Cancel the timer.
            if (TimerMgr::instance()->isTimerRegistered(timer_name)) {
                TimerMgr::instance()->unregisterTimer(timer_name);
            }

            // Invoke application layer connection failed callback.
            DatabaseConnection::invokeDbFailedCallback(db_reconnect_ctl);
            return (false);
        }

        LOG_INFO(dhcpsrv_logger, DHCPSRV_MYSQL_HOST_DB_RECONNECT_ATTEMPT_SCHEDULE)
                .arg(db_reconnect_ctl->maxRetries() - db_reconnect_ctl->retriesLeft() + 1)
                .arg(db_reconnect_ctl->maxRetries())
                .arg(db_reconnect_ctl->retryInterval());

        // Start the timer.
        if (!TimerMgr::instance()->isTimerRegistered(timer_name)) {
            TimerMgr::instance()->registerTimer(timer_name,
                std::bind(&MySqlHostDataSourceImpl::dbReconnect, db_reconnect_ctl),
                          db_reconnect_ctl->retryInterval(),
                          asiolink::IntervalTimer::ONE_SHOT);
        }
        TimerMgr::instance()->setup(timer_name);
    }

    return (true);
}

std::pair<uint32_t, uint32_t>
MySqlHostDataSourceImpl::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_HOST_DB_GET_VERSION);

    return (MySqlConnection::getVersion(parameters_));
}

void
MySqlHostDataSourceImpl::addStatement(MySqlHostContextPtr& ctx,
                                      StatementIndex stindex,
                                      std::vector<MYSQL_BIND>& bind) {
    // Bind the parameters to the statement
    int status = mysql_stmt_bind_param(ctx->conn_.statements_[stindex], &bind[0]);
    checkError(ctx, status, stindex, "unable to bind parameters");

    // Execute the statement
    status = MysqlExecuteStatement(ctx->conn_.statements_[stindex]);

    if (status != 0) {
        // Failure: check for the special case of duplicate entry.
        if (mysql_errno(ctx->conn_.mysql_) == ER_DUP_ENTRY) {
            isc_throw(DuplicateEntry, "Database duplicate entry error");
        }
        checkError(ctx, status, stindex, "unable to execute");
    }

    // If the number of rows inserted is 0 it means that the query detected
    // an attempt to insert duplicated data for which there is no unique
    // index in the database. Unique indexes are not created in the database
    // when it may be sometimes allowed to insert duplicated records per
    // server's configuration.
    my_ulonglong numrows = mysql_stmt_affected_rows(ctx->conn_.statements_[stindex]);
    if (numrows == 0) {
        isc_throw(DuplicateEntry, "Database duplicate entry error");
    }
}

bool
MySqlHostDataSourceImpl::delStatement(MySqlHostContextPtr& ctx,
                                      StatementIndex stindex,
                                      MYSQL_BIND* bind) {
    // Bind the parameters to the statement
    int status = mysql_stmt_bind_param(ctx->conn_.statements_[stindex], &bind[0]);
    checkError(ctx, status, stindex, "unable to bind parameters");

    // Execute the statement
    status = MysqlExecuteStatement(ctx->conn_.statements_[stindex]);

    if (status != 0) {
        checkError(ctx, status, stindex, "unable to execute");
    }

    // Let's check how many hosts were deleted.
    my_ulonglong numrows = mysql_stmt_affected_rows(ctx->conn_.statements_[stindex]);

    return (numrows != 0);
}

void
MySqlHostDataSourceImpl::addResv(MySqlHostContextPtr& ctx,
                                 const IPv6Resrv& resv,
                                 const HostID& id) {
    std::vector<MYSQL_BIND> bind = ctx->host_ipv6_reservation_exchange_->
        createBindForSend(resv, id, ip_reservations_unique_);

    addStatement(ctx, ip_reservations_unique_ ? INSERT_V6_RESRV_UNIQUE : INSERT_V6_RESRV_NON_UNIQUE, bind);
}

void
MySqlHostDataSourceImpl::addOption(MySqlHostContextPtr& ctx,
                                   const StatementIndex& stindex,
                                   const OptionDescriptor& opt_desc,
                                   const std::string& opt_space,
                                   const Optional<SubnetID>& subnet_id,
                                   const HostID& id) {
    std::vector<MYSQL_BIND> bind = ctx->host_option_exchange_->createBindForSend(opt_desc, opt_space, subnet_id, id);

    addStatement(ctx, stindex, bind);
}

void
MySqlHostDataSourceImpl::addOptions(MySqlHostContextPtr& ctx,
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
MySqlHostDataSourceImpl::checkError(MySqlHostContextPtr& ctx,
                                    const int status,
                                    const StatementIndex index,
                                    const char* what) const {
    ctx->conn_.checkError(status, index, what);
}

void
MySqlHostDataSourceImpl::getHostCollection(MySqlHostContextPtr& ctx,
                                           StatementIndex stindex,
                                           MYSQL_BIND* bind,
                                           boost::shared_ptr<MySqlHostExchange> exchange,
                                           ConstHostCollection& result,
                                           bool single) const {

    // Bind the selection parameters to the statement
    int status = mysql_stmt_bind_param(ctx->conn_.statements_[stindex], bind);
    checkError(ctx, status, stindex, "unable to bind WHERE clause parameter");

    // Set up the MYSQL_BIND array for the data being returned and bind it to
    // the statement.
    std::vector<MYSQL_BIND> outbind = exchange->createBindForReceive();
    status = mysql_stmt_bind_result(ctx->conn_.statements_[stindex], &outbind[0]);
    checkError(ctx, status, stindex, "unable to bind SELECT clause parameters");

    // Execute the statement
    status = MysqlExecuteStatement(ctx->conn_.statements_[stindex]);
    checkError(ctx, status, stindex, "unable to execute");

    // Ensure that all the lease information is retrieved in one go to avoid
    // overhead of going back and forth between client and server.
    status = mysql_stmt_store_result(ctx->conn_.statements_[stindex]);
    checkError(ctx, status, stindex, "unable to set up for storing all results");

    // Set up the fetch "release" object to release resources associated
    // with the call to mysql_stmt_fetch when this method exits, then
    // retrieve the data. mysql_stmt_fetch return value equal to 0 represents
    // successful data fetch.
    MySqlFreeResult fetch_release(ctx->conn_.statements_[stindex]);
    while ((status = mysql_stmt_fetch(ctx->conn_.statements_[stindex])) ==
           MLM_MYSQL_FETCH_SUCCESS) {
        try {
            exchange->processFetchedData(result);

        } catch (const isc::BadValue& ex) {
            // Rethrow the exception with a bit more data.
            isc_throw(BadValue, ex.what() << ". Statement is <" <<
                      ctx->conn_.text_statements_[stindex] << ">");
        }

        if (single && (result.size() > 1)) {
            isc_throw(MultipleRecords, "multiple records were found in the "
                      "database where only one was expected for query "
                      << ctx->conn_.text_statements_[stindex]);
        }
    }

    // How did the fetch end?
    // If mysql_stmt_fetch return value is equal to 1 an error occurred.
    if (status == MLM_MYSQL_FETCH_FAILURE) {
        // Error - unable to fetch results
        checkError(ctx, status, stindex, "unable to fetch results");

    } else if (status == MYSQL_DATA_TRUNCATED) {
        // Data truncated - throw an exception indicating what was at fault
        isc_throw(DataTruncated, ctx->conn_.text_statements_[stindex]
                  << " returned truncated data: columns affected are "
                  << exchange->getErrorColumns());
    }
}

ConstHostPtr
MySqlHostDataSourceImpl::getHost(MySqlHostContextPtr& ctx,
                                 const SubnetID& subnet_id,
                                 const Host::IdentifierType& identifier_type,
                                 const uint8_t* identifier_begin,
                                 const size_t identifier_len,
                                 StatementIndex stindex,
                                 boost::shared_ptr<MySqlHostExchange> exchange) const {

    // Set up the WHERE clause value
    MYSQL_BIND inbind[3];
    memset(inbind, 0, sizeof(inbind));

    uint32_t subnet_buffer = static_cast<uint32_t>(subnet_id);
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet_buffer);
    inbind[0].is_unsigned = MLM_TRUE;

    // Identifier value.
    std::vector<char> identifier_vec(identifier_begin,
                                     identifier_begin + identifier_len);
    unsigned long length = identifier_vec.size();
    inbind[2].buffer_type = MYSQL_TYPE_BLOB;
    inbind[2].buffer = &identifier_vec[0];
    inbind[2].buffer_length = length;
    inbind[2].length = &length;

    // Identifier type.
    char identifier_type_copy = static_cast<char>(identifier_type);
    inbind[1].buffer_type = MYSQL_TYPE_TINY;
    inbind[1].buffer = reinterpret_cast<char*>(&identifier_type_copy);
    inbind[1].is_unsigned = MLM_TRUE;

    ConstHostCollection collection;
    getHostCollection(ctx, stindex, inbind, exchange, collection, true);

    // Return single record if present, else clear the host.
    ConstHostPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return (result);
}

void
MySqlHostDataSourceImpl::checkReadOnly(MySqlHostContextPtr& ctx) const {
    if (ctx->is_readonly_) {
        isc_throw(ReadOnlyDb, "MySQL host database backend is configured to"
                  " operate in read only mode");
    }
}

MySqlHostDataSource::MySqlHostDataSource(const DatabaseConnection::ParameterMap& parameters)
    : impl_(new MySqlHostDataSourceImpl(parameters)) {
}

MySqlHostDataSource::~MySqlHostDataSource() {
}

DatabaseConnection::ParameterMap
MySqlHostDataSource::getParameters() const {
    return (impl_->parameters_);
}

void
MySqlHostDataSource::add(const HostPtr& host) {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // If operating in read-only mode, throw exception.
    impl_->checkReadOnly(ctx);

    // Initiate MySQL transaction as we will have to make multiple queries
    // to insert host information into multiple tables. If that fails on
    // any stage, the transaction will be rolled back by the destructor of
    // the MySqlTransaction class.
    MySqlTransaction transaction(ctx->conn_);

    // If we're configured to check that an IP reservation within a given subnet
    // is unique, the IP reservation exists and the subnet is actually set
    // we will be using a special query that checks for uniqueness. Otherwise,
    // we will use a regular insert statement.
    bool unique_ip = impl_->ip_reservations_unique_ && !host->getIPv4Reservation().isV4Zero()
        && host->getIPv4SubnetID() != SUBNET_ID_UNUSED;

    // Create the MYSQL_BIND array for the host
    std::vector<MYSQL_BIND> bind = ctx->host_ipv4_exchange_->createBindForSend(host, unique_ip);

    // ... and insert the host.
    impl_->addStatement(ctx, unique_ip ? MySqlHostDataSourceImpl::INSERT_HOST_UNIQUE_IP :
                        MySqlHostDataSourceImpl::INSERT_HOST_NON_UNIQUE_IP, bind);

    // Gets the last inserted hosts id
    uint64_t host_id = mysql_insert_id(ctx->conn_.mysql_);

    // Insert DHCPv4 options.
    ConstCfgOptionPtr cfg_option4 = host->getCfgOption4();
    if (cfg_option4) {
        impl_->addOptions(ctx, MySqlHostDataSourceImpl::INSERT_V4_HOST_OPTION,
                          cfg_option4, host_id);
    }

    // Insert DHCPv6 options.
    ConstCfgOptionPtr cfg_option6 = host->getCfgOption6();
    if (cfg_option6) {
        impl_->addOptions(ctx, MySqlHostDataSourceImpl::INSERT_V6_HOST_OPTION,
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
MySqlHostDataSource::del(const SubnetID& subnet_id,
                         const asiolink::IOAddress& addr) {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // If operating in read-only mode, throw exception.
    impl_->checkReadOnly(ctx);

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];

    uint32_t subnet = subnet_id;
    memset(inbind, 0, sizeof(inbind));
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet);
    inbind[0].is_unsigned = MLM_TRUE;

    // v4
    if (addr.isV4()) {
        uint32_t addr4 = addr.toUint32();
        inbind[1].buffer_type = MYSQL_TYPE_LONG;
        inbind[1].buffer = reinterpret_cast<char*>(&addr4);
        inbind[1].is_unsigned = MLM_TRUE;

        return (impl_->delStatement(ctx, MySqlHostDataSourceImpl::DEL_HOST_ADDR4, inbind));
    }

    // v6
    std::string addr_str = addr.toText();
    unsigned long addr_len = addr_str.size();
    inbind[1].buffer_type = MYSQL_TYPE_BLOB;
    inbind[1].buffer = reinterpret_cast<char*>
                        (const_cast<char*>(addr_str.c_str()));
    inbind[1].length = &addr_len;
    inbind[1].buffer_length = addr_len;

    return (impl_->delStatement(ctx, MySqlHostDataSourceImpl::DEL_HOST_ADDR6, inbind));
}

bool
MySqlHostDataSource::del4(const SubnetID& subnet_id,
                          const Host::IdentifierType& identifier_type,
                          const uint8_t* identifier_begin,
                          const size_t identifier_len) {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // If operating in read-only mode, throw exception.
    impl_->checkReadOnly(ctx);

    // Set up the WHERE clause value
    MYSQL_BIND inbind[3];

    // subnet-id
    memset(inbind, 0, sizeof(inbind));
    uint32_t subnet = static_cast<uint32_t>(subnet_id);
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet);
    inbind[0].is_unsigned = MLM_TRUE;

    // identifier type
    char identifier_type_copy = static_cast<char>(identifier_type);
    inbind[1].buffer_type = MYSQL_TYPE_TINY;
    inbind[1].buffer = reinterpret_cast<char*>(&identifier_type_copy);
    inbind[1].is_unsigned = MLM_TRUE;

    // identifier value
    std::vector<char> identifier_vec(identifier_begin,
                                     identifier_begin + identifier_len);
    unsigned long length = identifier_vec.size();
    inbind[2].buffer_type = MYSQL_TYPE_BLOB;
    inbind[2].buffer = &identifier_vec[0];
    inbind[2].buffer_length = length;
    inbind[2].length = &length;

    ConstHostCollection collection;
    return (impl_->delStatement(ctx, MySqlHostDataSourceImpl::DEL_HOST_SUBID4_ID, inbind));
}

bool
MySqlHostDataSource::del6(const SubnetID& subnet_id,
                          const Host::IdentifierType& identifier_type,
                          const uint8_t* identifier_begin,
                          const size_t identifier_len) {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // If operating in read-only mode, throw exception.
    impl_->checkReadOnly(ctx);

    // Set up the WHERE clause value
    MYSQL_BIND inbind[3];

    // subnet-id
    memset(inbind, 0, sizeof(inbind));
    uint32_t subnet = static_cast<uint32_t>(subnet_id);
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet);
    inbind[0].is_unsigned = MLM_TRUE;

    // identifier type
    char identifier_type_copy = static_cast<char>(identifier_type);
    inbind[1].buffer_type = MYSQL_TYPE_TINY;
    inbind[1].buffer = reinterpret_cast<char*>(&identifier_type_copy);
    inbind[1].is_unsigned = MLM_TRUE;

    // identifier value
    std::vector<char> identifier_vec(identifier_begin,
                                     identifier_begin + identifier_len);
    unsigned long length = identifier_vec.size();
    inbind[2].buffer_type = MYSQL_TYPE_BLOB;
    inbind[2].buffer = &identifier_vec[0];
    inbind[2].buffer_length = length;
    inbind[2].length = &length;

    ConstHostCollection collection;
    return (impl_->delStatement(ctx, MySqlHostDataSourceImpl::DEL_HOST_SUBID6_ID, inbind));
}

ConstHostCollection
MySqlHostDataSource::getAll(const Host::IdentifierType& identifier_type,
                            const uint8_t* identifier_begin,
                            const size_t identifier_len) const {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    // Identifier type.
    char identifier_type_copy = static_cast<char>(identifier_type);
    inbind[1].buffer = &identifier_type_copy;
    inbind[1].buffer_type = MYSQL_TYPE_TINY;
    inbind[1].is_unsigned = MLM_TRUE;

    // Identifier value.
    std::vector<char> identifier_vec(identifier_begin,
                                     identifier_begin + identifier_len);
    unsigned long int length = identifier_vec.size();
    inbind[0].buffer_type = MYSQL_TYPE_BLOB;
    inbind[0].buffer = &identifier_vec[0];
    inbind[0].buffer_length = length;
    inbind[0].length = &length;

    ConstHostCollection result;
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_DHCPID, inbind,
                             ctx->host_ipv46_exchange_, result, false);

    return (result);
}

ConstHostCollection
MySqlHostDataSource::getAll4(const SubnetID& subnet_id) const {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));
    uint32_t subnet = subnet_id;
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet);
    inbind[0].is_unsigned = MLM_TRUE;

    ConstHostCollection result;
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_SUBID4, inbind,
                             ctx->host_ipv4_exchange_, result, false);

    return (result);
}

ConstHostCollection
MySqlHostDataSource::getAll6(const SubnetID& subnet_id) const {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));
    uint32_t subnet = subnet_id;
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet);
    inbind[0].is_unsigned = MLM_TRUE;

    ConstHostCollection result;
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_SUBID6, inbind,
                             ctx->host_ipv6_exchange_, result, false);

    return (result);
}

ConstHostCollection
MySqlHostDataSource::getAllbyHostname(const std::string& hostname) const {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    // Hostname
    char hostname_[HOSTNAME_MAX_LEN];
    strncpy(hostname_, hostname.c_str(), HOSTNAME_MAX_LEN - 1);
    unsigned long length = hostname.length();
    inbind[0].buffer_type = MYSQL_TYPE_STRING;
    inbind[0].buffer = reinterpret_cast<char*>(hostname_);
    inbind[0].buffer_length = length;
    inbind[0].length = &length;

    ConstHostCollection result;
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_HOSTNAME, inbind,
                             ctx->host_ipv46_exchange_, result, false);

    return (result);
}

ConstHostCollection
MySqlHostDataSource::getAllbyHostname4(const std::string& hostname,
                                       const SubnetID& subnet_id) const {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    // Hostname
    char hostname_[HOSTNAME_MAX_LEN];
    strncpy(hostname_, hostname.c_str(), HOSTNAME_MAX_LEN - 1);
    unsigned long length = hostname.length();
    inbind[0].buffer_type = MYSQL_TYPE_STRING;
    inbind[0].buffer = reinterpret_cast<char*>(hostname_);
    inbind[0].buffer_length = length;
    inbind[0].length = &length;

    // Subnet ID
    uint32_t subnet = subnet_id;
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&subnet);
    inbind[1].is_unsigned = MLM_TRUE;

    ConstHostCollection result;
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_HOSTNAME_SUBID4, inbind,
                             ctx->host_ipv4_exchange_, result, false);

    return (result);
}

ConstHostCollection
MySqlHostDataSource::getAllbyHostname6(const std::string& hostname,
                                       const SubnetID& subnet_id) const {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    // Hostname
    char hostname_[HOSTNAME_MAX_LEN];
    strncpy(hostname_, hostname.c_str(), HOSTNAME_MAX_LEN - 1);
    unsigned long length = hostname.length();
    inbind[0].buffer_type = MYSQL_TYPE_STRING;
    inbind[0].buffer = reinterpret_cast<char*>(hostname_);
    inbind[0].buffer_length = length;
    inbind[0].length = &length;

    // Subnet ID
    uint32_t subnet = subnet_id;
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&subnet);
    inbind[1].is_unsigned = MLM_TRUE;

    ConstHostCollection result;
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_HOSTNAME_SUBID6, inbind,
                             ctx->host_ipv6_exchange_, result, false);

    return (result);
}

ConstHostCollection
MySqlHostDataSource::getPage4(const SubnetID& subnet_id,
                              size_t& /*source_index*/,
                              uint64_t lower_host_id,
                              const HostPageSize& page_size) const {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    MYSQL_BIND inbind[3];
    memset(inbind, 0, sizeof(inbind));

    // Bind subnet id
    uint32_t subnet = subnet_id;
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet);
    inbind[0].is_unsigned = MLM_TRUE;

    // Bind lower host id
    uint32_t host_id = lower_host_id;
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&host_id);
    inbind[1].is_unsigned = MLM_TRUE;

    // Bind page size value
    uint32_t page_size_data = page_size.page_size_;
    inbind[2].buffer_type = MYSQL_TYPE_LONG;
    inbind[2].buffer = reinterpret_cast<char*>(&page_size_data);
    inbind[2].is_unsigned = MLM_TRUE;

    ConstHostCollection result;
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_SUBID4_PAGE, inbind,
                             ctx->host_ipv4_exchange_, result, false);

    return (result);
}

ConstHostCollection
MySqlHostDataSource::getPage6(const SubnetID& subnet_id,
                              size_t& /*source_index*/,
                              uint64_t lower_host_id,
                              const HostPageSize& page_size) const {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    MYSQL_BIND inbind[3];
    memset(inbind, 0, sizeof(inbind));

    // Bind subnet id
    uint32_t subnet = subnet_id;
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet);
    inbind[0].is_unsigned = MLM_TRUE;

    // Bind lower host id
    uint32_t host_id = lower_host_id;
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&host_id);
    inbind[1].is_unsigned = MLM_TRUE;

    // Bind page size value
    uint32_t page_size_data = page_size.page_size_;
    inbind[2].buffer_type = MYSQL_TYPE_LONG;
    inbind[2].buffer = reinterpret_cast<char*>(&page_size_data);
    inbind[2].is_unsigned = MLM_TRUE;

    ConstHostCollection result;
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_SUBID6_PAGE, inbind,
                             ctx->host_ipv6_exchange_, result, false);

    return (result);
}

ConstHostCollection
MySqlHostDataSource::getPage4(size_t& /*source_index*/,
                              uint64_t lower_host_id,
                              const HostPageSize& page_size) const {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    // Bind lower host id
    uint32_t host_id = lower_host_id;
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&host_id);
    inbind[0].is_unsigned = MLM_TRUE;

    // Bind page size value
    uint32_t page_size_data = page_size.page_size_;
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&page_size_data);
    inbind[1].is_unsigned = MLM_TRUE;

    ConstHostCollection result;
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_PAGE4, inbind,
                             ctx->host_ipv4_exchange_, result, false);

    return (result);
}

ConstHostCollection
MySqlHostDataSource::getPage6(size_t& /*source_index*/,
                              uint64_t lower_host_id,
                              const HostPageSize& page_size) const {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    // Bind lower host id
    uint32_t host_id = lower_host_id;
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&host_id);
    inbind[0].is_unsigned = MLM_TRUE;

    // Bind page size value
    uint32_t page_size_data = page_size.page_size_;
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&page_size_data);
    inbind[1].is_unsigned = MLM_TRUE;

    ConstHostCollection result;
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_PAGE6, inbind,
                             ctx->host_ipv6_exchange_, result, false);

    return (result);
}

ConstHostCollection
MySqlHostDataSource::getAll4(const asiolink::IOAddress& address) const {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    uint32_t addr4 = address.toUint32();
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&addr4);
    inbind[0].is_unsigned = MLM_TRUE;

    ConstHostCollection result;
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_ADDR, inbind,
                             ctx->host_ipv4_exchange_, result, false);

    return (result);
}

ConstHostPtr
MySqlHostDataSource::get4(const SubnetID& subnet_id,
                          const Host::IdentifierType& identifier_type,
                          const uint8_t* identifier_begin,
                          const size_t identifier_len) const {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    return (impl_->getHost(ctx, subnet_id, identifier_type, identifier_begin, identifier_len,
                           MySqlHostDataSourceImpl::GET_HOST_SUBID4_DHCPID,
                           ctx->host_ipv4_exchange_));
}

ConstHostPtr
MySqlHostDataSource::get4(const SubnetID& subnet_id,
                          const asiolink::IOAddress& address) const {
    if (!address.isV4()) {
        isc_throw(BadValue, "MySqlHostDataSource::get4(id, address): "
                  "wrong address type, address supplied is an IPv6 address");
    }

    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    uint32_t subnet = subnet_id;
    memset(inbind, 0, sizeof(inbind));
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet);
    inbind[0].is_unsigned = MLM_TRUE;

    uint32_t addr4 = address.toUint32();
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&addr4);
    inbind[1].is_unsigned = MLM_TRUE;

    ConstHostCollection collection;
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_SUBID_ADDR, inbind,
                             ctx->host_ipv4_exchange_, collection, true);

    // Return single record if present, else clear the host.
    ConstHostPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return (result);
}

ConstHostCollection
MySqlHostDataSource::getAll4(const SubnetID& subnet_id,
                             const asiolink::IOAddress& address) const {
    if (!address.isV4()) {
        isc_throw(BadValue, "MySqlHostDataSource::getAll4(id, address): "
                  "wrong address type, address supplied is an IPv6 address");
    }

    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    uint32_t subnet = subnet_id;
    memset(inbind, 0, sizeof(inbind));
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet);
    inbind[0].is_unsigned = MLM_TRUE;

    uint32_t addr4 = address.toUint32();
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&addr4);
    inbind[1].is_unsigned = MLM_TRUE;

    ConstHostCollection collection;
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_SUBID_ADDR, inbind,
                             ctx->host_ipv4_exchange_, collection, false);
    return (collection);
}

ConstHostPtr
MySqlHostDataSource::get6(const SubnetID& subnet_id,
                          const Host::IdentifierType& identifier_type,
                          const uint8_t* identifier_begin,
                          const size_t identifier_len) const {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    return (impl_->getHost(ctx, subnet_id, identifier_type, identifier_begin, identifier_len,
                           MySqlHostDataSourceImpl::GET_HOST_SUBID6_DHCPID,
                           ctx->host_ipv6_exchange_));
}

ConstHostPtr
MySqlHostDataSource::get6(const asiolink::IOAddress& prefix,
                          const uint8_t prefix_len) const {
    if (!prefix.isV6()) {
        isc_throw(BadValue, "MySqlHostDataSource::get6(prefix, prefix_len): "
                  "wrong address type, address supplied is an IPv4 address");
    }

    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

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
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_PREFIX, inbind,
                             ctx->host_ipv6_exchange_, collection, true);

    // Return single record if present, else clear the host.
    ConstHostPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return (result);
}

ConstHostPtr
MySqlHostDataSource::get6(const SubnetID& subnet_id,
                          const asiolink::IOAddress& address) const {
    if (!address.isV6()) {
        isc_throw(BadValue, "MySqlHostDataSource::get6(id, address): "
                  "wrong address type, address supplied is an IPv4 address");
    }

    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    uint32_t subnet_buffer = static_cast<uint32_t>(subnet_id);
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet_buffer);
    inbind[0].is_unsigned = MLM_TRUE;

    std::string addr6 = address.toText();
    unsigned long addr6_length = addr6.size();

    inbind[1].buffer_type = MYSQL_TYPE_BLOB;
    inbind[1].buffer = reinterpret_cast<char*>
                        (const_cast<char*>(addr6.c_str()));
    inbind[1].length = &addr6_length;
    inbind[1].buffer_length = addr6_length;

    ConstHostCollection collection;
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_SUBID6_ADDR, inbind,
                             ctx->host_ipv6_exchange_, collection, true);

    // Return single record if present, else clear the host.
    ConstHostPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return (result);
}

ConstHostCollection
MySqlHostDataSource::getAll6(const SubnetID& subnet_id,
                             const asiolink::IOAddress& address) const {
    if (!address.isV6()) {
        isc_throw(BadValue, "MySqlHostDataSource::getAll6(id, address): "
                  "wrong address type, address supplied is an IPv4 address");
    }

    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    uint32_t subnet_buffer = static_cast<uint32_t>(subnet_id);
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet_buffer);
    inbind[0].is_unsigned = MLM_TRUE;

    std::string addr6 = address.toText();
    unsigned long addr6_length = addr6.size();

    inbind[1].buffer_type = MYSQL_TYPE_BLOB;
    inbind[1].buffer = reinterpret_cast<char*>
                        (const_cast<char*>(addr6.c_str()));
    inbind[1].length = &addr6_length;
    inbind[1].buffer_length = addr6_length;

    ConstHostCollection collection;
    impl_->getHostCollection(ctx, MySqlHostDataSourceImpl::GET_HOST_SUBID6_ADDR, inbind,
                             ctx->host_ipv6_exchange_, collection, false);
    return (collection);
}

// Miscellaneous database methods.

std::string
MySqlHostDataSource::getName() const {
    std::string name = "";
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    try {
        name = ctx->conn_.getParameter("name");
    } catch (...) {
        // Return an empty name
    }
    return (name);
}

std::string
MySqlHostDataSource::getDescription() const {
    return (std::string("Host data source that stores host information"
                        "in MySQL database"));
}

std::pair<uint32_t, uint32_t>
MySqlHostDataSource::getVersion() const {
    return(impl_->getVersion());
}

void
MySqlHostDataSource::commit() {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // If operating in read-only mode, throw exception.
    impl_->checkReadOnly(ctx);
    if (ctx->conn_.isTransactionStarted()) {
        ctx->conn_.commit();
    }
}

void
MySqlHostDataSource::rollback() {
    // Get a context
    MySqlHostContextAlloc get_context(*impl_);
    MySqlHostContextPtr ctx = get_context.ctx_;

    // If operating in read-only mode, throw exception.
    impl_->checkReadOnly(ctx);
    if (ctx->conn_.isTransactionStarted()) {
        ctx->conn_.rollback();
    }
}

bool
MySqlHostDataSource::setIPReservationsUnique(const bool unique) {
    impl_->ip_reservations_unique_ = unique;
    return (true);
}

bool
MySqlHostDataSource::isUnusable() {
    return (impl_->unusable_);
}

}  // namespace dhcp
}  // namespace isc
