// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/mysql_host_data_source.h>
#include <dhcpsrv/mysql_connection.h>
#include <dhcpsrv/db_exceptions.h>
#include <dhcpsrv/host.h>

#include <boost/static_assert.hpp>
#include <mysqld_error.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace std;

namespace {
/// @brief Maximum length of classes stored in a dhcp4/6_client_classes field
///
const size_t CLIENT_CLASSES_MAX_LEN = 255;

/// @brief Maximum length of the hostname stored in DNS.
///
/// This length is restricted by the length of the domain-name carried
/// in the Client FQDN %Option (see RFC4702 and RFC4704).
const size_t HOSTNAME_MAX_LEN = 255;


TaggedStatement tagged_statements[] = {
    {MySqlHostDataSource::INSERT_HOST,
         "INSERT INTO hosts(host_id, dhcp_identifier, dhcp_identifier_type, "
            "dhcp4_subnet_id, dhcp6_subnet_id, ipv4_address, hostname, "
            "dhcp4_client_classes, dhcp6_client_classes) "
         "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)"},
    {MySqlHostDataSource::INSERT_V6_RESRV,
         "INSERT INTO ipv6_reservations(reservation_id, address, prefix_len, type, "
            "dhcp6_iaid, host_id) "
         "VALUES (?,?,?,?,?,?)"},
    {MySqlHostDataSource::GET_V6_RESRV,
         "SELECT reservation_id, address, prefix_len, type, dhcp6_iaid, host_id "
         "FROM ipv6_reservations "
         "WHERE host_id = ?"},
    {MySqlHostDataSource::GET_HOST_HWADDR_DUID,
            "SELECT host_id, dhcp_identifier, dhcp_identifier_type, "
                "dhcp4_subnet_id, dhcp6_subnet_id, ipv4_address, hostname, "
                "dhcp4_client_classes, dhcp6_client_classes "
            "FROM hosts "
            "WHERE dhcp_identifier = ? AND dhcp_identifier_type = ?"},
    {MySqlHostDataSource::GET_HOST_ADDR,
            "SELECT host_id, dhcp_identifier, dhcp_identifier_type, "
                "dhcp4_subnet_id, dhcp6_subnet_id, ipv4_address, hostname, "
                "dhcp4_client_classes, dhcp6_client_classes "
            "FROM hosts "
            "WHERE ipv4_address = ?"},
    {MySqlHostDataSource::GET_HOST_SUBID4_DHCPID,
            "SELECT host_id, dhcp_identifier, dhcp_identifier_type, "
                "dhcp4_subnet_id, dhcp6_subnet_id, ipv4_address, hostname, "
                "dhcp4_client_classes, dhcp6_client_classes "
            "FROM hosts "
            "WHERE dhcp4_subnet_id = ? AND dhcp_identifier_type = ? "
            "   AND dhcp_identifier = ?"},
    {MySqlHostDataSource::GET_HOST_SUBID6_DHCPID,
            "SELECT host_id, dhcp_identifier, dhcp_identifier_type, "
                "dhcp4_subnet_id, dhcp6_subnet_id, ipv4_address, hostname, "
                "dhcp4_client_classes, dhcp6_client_classes "
            "FROM hosts "
            "WHERE dhcp6_subnet_id = ? AND dhcp_identifier_type = ? "
            "   AND dhcp_identifier = ?"},
    {MySqlHostDataSource::GET_HOST_SUBID_ADDR,
            "SELECT host_id, dhcp_identifier, dhcp_identifier_type, "
                "dhcp4_subnet_id, dhcp6_subnet_id, ipv4_address, hostname, "
                "dhcp4_client_classes, dhcp6_client_classes "
            "FROM hosts "
            "WHERE dhcp4_subnet_id = ? AND ipv4_address = ?"},
    {MySqlHostDataSource::GET_HOST_PREFIX,
            "SELECT h.host_id, dhcp_identifier, dhcp_identifier_type, "
                "dhcp4_subnet_id, dhcp6_subnet_id, ipv4_address, hostname, "
                "dhcp4_client_classes, dhcp6_client_classes "
            "FROM hosts h, ipv6_reservations r "
            "WHERE h.host_id = r.host_id "
            "AND r.address = ? AND r.prefix_len = ?"},
    {MySqlHostDataSource::GET_VERSION,
            "SELECT version, minor FROM schema_version"},
    {MySqlHostDataSource::NUM_STATEMENTS, NULL}
};

};

namespace isc {
namespace dhcp {

/// @brief This class represents the exchanges related to hosts.
class MySqlHostReservationExchange {
    /// @brief Set number of database columns for this host structure
    static const size_t HOST_COLUMNS = 9;

public:

    /// @brief Constructor
    ///
    /// The initialization of the variables here is only to satisfy cppcheck -
    /// all variables are initialized/set in the methods before they are used.
    MySqlHostReservationExchange() : host_id_(0), dhcp_identifier_length_(0),
        dhcp_identifier_type_(0), dhcp4_subnet_id_(0), dhcp6_subnet_id_(0),
        ipv4_address_(0), hostname_length_(0), dhcp4_client_classes_length_(0),
        dhcp6_client_classes_length_(0), dhcp4_subnet_id_null_(MLM_FALSE),
        dhcp6_subnet_id_null_(MLM_FALSE), ipv4_address_null_(MLM_FALSE),
        hostname_null_(MLM_FALSE), dhcp4_client_classes_null_(MLM_FALSE),
        dhcp6_client_classes_null_(MLM_FALSE){

        memset(dhcp_identifier_buffer_, 0, sizeof(dhcp_identifier_buffer_));
        memset(hostname_, 0, sizeof(hostname_));
        memset(dhcp4_client_classes_, 0, sizeof(dhcp4_client_classes_));
        memset(dhcp6_client_classes_, 0, sizeof(dhcp6_client_classes_));
        std::fill(&error_[0], &error_[HOST_COLUMNS], MLM_FALSE);

        // Set the column names (for error messages)
        columns_[0] = "host_id";
        columns_[1] = "dhcp_identifier";
        columns_[2] = "dhcp_identifier_type";
        columns_[3] = "dhcp4_subnet_id";
        columns_[4] = "dhcp6_subnet_id";
        columns_[5] = "ipv4_address";
        columns_[6] = "hostname";
        columns_[7] = "dhcp4_client_classes";
        columns_[8] = "dhcp6_client_classes";
        BOOST_STATIC_ASSERT(8 < HOST_COLUMNS);
    }

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
    /// @param count Size of each of the arrays.
    static void setErrorIndicators(MYSQL_BIND* bind, my_bool* error,
                                   size_t count) {
        for (size_t i = 0; i < count; ++i) {
            error[i] = MLM_FALSE;
            bind[i].error = reinterpret_cast<char*>(&error[i]);
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
    /// @param error Array of error elements.  An element is set to MLM_TRUE
    ///        if the corresponding column in the database is the source of
    ///        the error.
    /// @param names Array of column names, the same size as the error array.
    /// @param count Size of each of the arrays.
    static std::string getColumnsInError(my_bool* error, std::string* names,
                                         size_t count) {
        std::string result = "";

        // Accumulate list of column names
        for (size_t i = 0; i < count; ++i) {
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
    }

    /// @brief Create MYSQL_BIND objects for Host Pointer
    ///
    /// Fills in the MYSQL_BIND array for sending data in the Host object to
    /// the database.
    ///
    /// @param host Host object to be added to the database.
    ///        None of the fields in the host reservation are modified -
    ///        the host data is only read.
    ///
    /// @return Vector of MySQL BIND objects representing the data to be added.
    std::vector<MYSQL_BIND> createBindForSend(const HostPtr& host) {

        // Store host object to ensure it remains valid.
        host_ = host;

        // Initialize prior to constructing the array of MYSQL_BIND structures.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        // This also takes care of seeeting bind_[X].is_null to MLM_FALSE.
        memset(bind_, 0, sizeof(bind_));

        // Set up the structures for the various components of the host structure.

        try {
            // host_id : INT UNSIGNED NOT NULL
            // The host_id is auto_incremented by MySQL database,
            // so we need to pass the NULL value
            host_id_ = static_cast<uint32_t>(NULL);
            bind_[0].buffer_type = MYSQL_TYPE_LONG;
            bind_[0].buffer = reinterpret_cast<char*>(&host_id_);
            bind_[0].is_unsigned = MLM_TRUE;

            // dhcp_identifier : VARBINARY(128) NOT NULL
            // Check which of the identifiers is used and set values accordingly
            if (host_->getDuid()) {
                dhcp_identifier_length_ = host_->getDuid()->getDuid().size();
                bind_[1].buffer_type = MYSQL_TYPE_BLOB;
                bind_[1].buffer = reinterpret_cast<char*>
                    (const_cast<uint8_t*>(&(host_->getDuid()->getDuid()[0])));
                bind_[1].buffer_length = dhcp_identifier_length_;
                bind_[1].length = &dhcp_identifier_length_;
            } else if (host_->getHWAddress()){
                dhcp_identifier_length_ = host_->getHWAddress()->hwaddr_.size();
                bind_[1].buffer_type = MYSQL_TYPE_BLOB;
                bind_[1].buffer = reinterpret_cast<char*>
                                    (&(host_->getHWAddress()->hwaddr_[0]));
                bind_[1].buffer_length = dhcp_identifier_length_;
                bind_[1].length = &dhcp_identifier_length_;
            }

            // dhcp_identifier_type : TINYINT NOT NULL
            // Check which of the identifier types is used and set values accordingly
            if (host_->getHWAddress()) {
                dhcp_identifier_type_ = BaseHostDataSource::ID_HWADDR; // 0
                bind_[2].buffer_type = MYSQL_TYPE_TINY;
                bind_[2].buffer = reinterpret_cast<char*>(&dhcp_identifier_type_);
                bind_[2].is_unsigned = MLM_TRUE;
            } else if (host_->getDuid()) {
                dhcp_identifier_type_ = BaseHostDataSource::ID_DUID; // 1
                bind_[2].buffer_type = MYSQL_TYPE_TINY;
                bind_[2].buffer = reinterpret_cast<char*>(&dhcp_identifier_type_);
                bind_[2].is_unsigned = MLM_TRUE;
            }

            // dhcp4_subnet_id : INT UNSIGNED NULL
            // Can't take an address of intermediate object, so let's store it
            // in dhcp4_subnet_id_
            dhcp4_subnet_id_ = host_->getIPv4SubnetID();
            bind_[3].buffer_type = MYSQL_TYPE_LONG;
            bind_[3].buffer = reinterpret_cast<char*>(&dhcp4_subnet_id_);
            bind_[3].is_unsigned = MLM_TRUE;

            // dhcp6_subnet_id : INT UNSIGNED NULL
            // Can't take an address of intermediate object, so let's store it
            // in dhcp6_subnet_id_
            dhcp6_subnet_id_ = host_->getIPv6SubnetID();
            bind_[4].buffer_type = MYSQL_TYPE_LONG;
            bind_[4].buffer = reinterpret_cast<char*>(&dhcp6_subnet_id_);
            bind_[4].is_unsigned = MLM_TRUE;

            // ipv4_address : INT UNSIGNED NULL
            // The address in the Host structure is an IOAddress object.  Convert
            // this to an integer for storage.
            ipv4_address_ = static_cast<uint32_t>(host_->getIPv4Reservation());
            bind_[5].buffer_type = MYSQL_TYPE_LONG;
            bind_[5].buffer = reinterpret_cast<char*>(&ipv4_address_);
            bind_[5].is_unsigned = MLM_TRUE;
            // bind_[5].is_null = &MLM_FALSE; // commented out for performance
                                              // reasons, see memset() above

            // hostname : VARCHAR(255) NULL
            strncpy(hostname_, host_->getHostname().c_str(), HOSTNAME_MAX_LEN - 1);
            hostname_length_ = host_->getHostname().length();
            bind_[6].buffer_type = MYSQL_TYPE_STRING;
            bind_[6].buffer = reinterpret_cast<char*>(hostname_);
            bind_[6].buffer_length = hostname_length_;

            // dhcp4_client_classes : VARCHAR(255) NULL
            bind_[7].buffer_type = MYSQL_TYPE_STRING;
            string classes4_txt = classesToString(host_->getClientClasses4());
            strncpy(dhcp4_client_classes_, classes4_txt.c_str(), CLIENT_CLASSES_MAX_LEN - 1);
            bind_[7].buffer = dhcp4_client_classes_;
            bind_[7].buffer_length = classes4_txt.length();

            // dhcp6_client_classes : VARCHAR(255) NULL
            bind_[8].buffer_type = MYSQL_TYPE_STRING;
            string classes6_txt = classesToString(host->getClientClasses6());
            strncpy(dhcp6_client_classes_, classes6_txt.c_str(), CLIENT_CLASSES_MAX_LEN - 1);
            bind_[8].buffer = dhcp6_client_classes_;
            bind_[8].buffer_length = classes6_txt.length();
            bind_[8].buffer_length = sizeof(host_->getClientClasses6());

        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from Host: "
                      << host_->getHostname() << ", reason: " << ex.what());
        }

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return (std::vector<MYSQL_BIND>(&bind_[0], &bind_[HOST_COLUMNS]));
    }

    /// @brief Create BIND array to receive data
    ///
    /// Creates a MYSQL_BIND array to receive Lease4 data from the database.
    /// After data is successfully received, getLeaseData() can be used to copy
    /// it to a Lease6 object.
    ///
    std::vector<MYSQL_BIND> createBindForReceive() {
        // Initialize MYSQL_BIND array.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        // This also takes care of seeeting bind_[X].is_null to MLM_FALSE.
        memset(bind_, 0, sizeof(bind_));

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

        // Add the error flags
        setErrorIndicators(bind_, error_, HOST_COLUMNS);

        // .. and check that we have the numbers correct at compile time.
        BOOST_STATIC_ASSERT(8 < HOST_COLUMNS);

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return(std::vector<MYSQL_BIND>(&bind_[0], &bind_[HOST_COLUMNS]));

    }

    /// @brief Copy Received Data into Host Object
    ///
    /// Called after the MYSQL_BIND array created by createBindForReceive()
    /// has been used, this copies data from the internal member variables
    /// into a Host objec.
    ///
    /// @return Host Pointer to a Lease6 object holding the relevant data.
    HostPtr getHostData(){

        // Set the dhcp identifier type in a variable of the appropriate data type,
        // which has been initialized with an arbitrary (but valid) value.
        Host::IdentifierType type = Host::IDENT_HWADDR;

        switch (dhcp_identifier_type_) {
            case 0:
                type = Host::IDENT_HWADDR;
                break;

            case 1:
                type = Host::IDENT_DUID;
                break;

            default:
                isc_throw(BadValue, "invalid dhcp identifier type returned: "
                        << static_cast<int>(dhcp_identifier_type_)
                        << ". Only 0 or 1 are allowed.");
        }

        // Set subnets ID's if they are given, if not, leave an empty object
        SubnetID ipv4_subnet_id(0);
        if (dhcp4_subnet_id_null_ == MLM_FALSE) {
            ipv4_subnet_id = static_cast<SubnetID>(dhcp4_subnet_id_);
        }

        SubnetID ipv6_subnet_id(0);
        if (dhcp6_subnet_id_null_ == MLM_FALSE) {
            ipv6_subnet_id = static_cast<SubnetID>(dhcp6_subnet_id_);
        }

        // Set IPv4 address reservation if it was given, if not, set IPv4 zero address
        asiolink::IOAddress ipv4_reservation = asiolink::IOAddress::IPV4_ZERO_ADDRESS();
        if (ipv4_address_null_ == MLM_FALSE) {
            ipv4_reservation = asiolink::IOAddress(ipv4_address_);
        }

        // Set hostname if it was given, if not lease empty string
        std::string hostname;
        if (hostname_null_ == MLM_FALSE) {
            hostname = std::string (hostname_, hostname_ + hostname_length_);
        }

        // Set client classes if they were given, if not, set empty client classes
        ClientClasses dhcp4_client_classes;
        if (dhcp4_client_classes_null_ == MLM_FALSE) {
            dhcp4_client_classes.insert(dhcp4_client_classes_);
        }

        ClientClasses dhcp6_client_classes;
        if (dhcp6_client_classes_null_ == MLM_FALSE) {
            dhcp6_client_classes.insert(dhcp6_client_classes_);
        }

        // Returning Host object with set fields
        HostPtr h(new Host(dhcp_identifier_buffer_, dhcp_identifier_length_,
                           type, ipv4_subnet_id, ipv6_subnet_id, ipv4_reservation,
                           hostname, dhcp4_client_classes_, dhcp6_client_classes_));
        h->setHostId(host_id_);

        return (h);
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
        return (getColumnsInError(error_, columns_, HOST_COLUMNS));
    }

    /// @brief Converts ClientClasses to a signgle string with coma separated values
    ///
    /// @param classes classes structure that contains zero or more classes
    /// @return a single string with coma separated values
    std::string classesToString(const ClientClasses& classes) {
        string txt;
        bool first = true;
        for (ClientClasses::const_iterator it = classes.begin();
             it != classes.end(); ++it) {
            if (!first) {
                txt += ",";
            }
            txt += (*it);

            first = false;
        }

        return (txt);
    }

private:
    uint64_t	host_id_;			/// Host unique identifier
    std::vector<uint8_t> dhcp_identifier_;      /// HW address (0) / DUID (1)
    uint8_t     dhcp_identifier_buffer_[DUID::MAX_DUID_LEN];
                                                /// Buffer for dhcp identifier
    size_t      dhcp_identifier_length_;        /// Length of dhcp identifier
    uint8_t     dhcp_identifier_type_;		/// Type of dhcp_identifier
    uint32_t    dhcp4_subnet_id_;		/// Subnet DHCPv4 identifier
    uint32_t    dhcp6_subnet_id_;		/// Subnet DHCPv6 identifier
    uint32_t    ipv4_address_;			/// Reserved IPv4 address.
    IPv6ResrvCollection ipv6_reservations_;	/// IPv6 reservations collection
    char        hostname_[HOSTNAME_MAX_LEN];    /// Name reserved for the host
    unsigned long hostname_length_;		/// hostname length
    char        dhcp4_client_classes_[CLIENT_CLASSES_MAX_LEN];
                                                /// DHCPv4 client classes
    unsigned long dhcp4_client_classes_length_; /// dhcp4_client_classes length
    char        dhcp6_client_classes_[CLIENT_CLASSES_MAX_LEN];
                                                /// DHCPv6 client classes
    unsigned long dhcp6_client_classes_length_; /// dhcp6_client_classes length
    HWAddrPtr   hw_address_;                    /// Pointer to hardware address
    DuidPtr     duid_;				/// Pointer to DUID

    // NULL flags for subnets id, ipv4 address, hostname and client classes
    my_bool     dhcp4_subnet_id_null_;
    my_bool     dhcp6_subnet_id_null_;
    my_bool     ipv4_address_null_;
    my_bool     hostname_null_;
    my_bool     dhcp4_client_classes_null_;
    my_bool     dhcp6_client_classes_null_;

    MYSQL_BIND  bind_[HOST_COLUMNS];
    std::string columns_[HOST_COLUMNS];	/// Column names
    my_bool     error_[HOST_COLUMNS];   /// Error array
    HostPtr     host_;			// Pointer to Host object
};

class MySqlIPv6ReservationExchange {
    /// @brief Set number of database columns for this reservation structure
    static const size_t RESRV_COLUMNS = 6;

public:

    /// @brief Constructor
    ///
    /// The initialization of the variables here is only to satisfy cppcheck -
    /// all variables are initialized/set in the methods before they are used.
    MySqlIPv6ReservationExchange()
        : host_id_(0), address_("::"), prefix_len_(0), type_(0),
          iaid_(0), resv_(IPv6Resrv::TYPE_NA, asiolink::IOAddress("::"), 128) {

        std::fill(&error_[0], &error_[RESRV_COLUMNS], MLM_FALSE);

        // Set the column names (for error messages)
        columns_[0] = "host_id";
        columns_[1] = "address";
        columns_[2] = "prefix_len";
        columns_[3] = "type";
        columns_[4] = "dhcp6_iaid";
        BOOST_STATIC_ASSERT(4 < RESRV_COLUMNS);
    }

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
    /// @param count Size of each of the arrays.
    static void setErrorIndicators(MYSQL_BIND* bind, my_bool* error,
                                   size_t count) {
        for (size_t i = 0; i < count; ++i) {
            error[i] = MLM_FALSE;
            bind[i].error = reinterpret_cast<char*>(&error[i]);
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
    /// @param error Array of error elements.  An element is set to MLM_TRUE
    ///        if the corresponding column in the database is the source of
    ///        the error.
    /// @param names Array of column names, the same size as the error array.
    /// @param count Size of each of the arrays.
    static std::string getColumnsInError(my_bool* error, std::string* names,
                                         size_t count) {
        std::string result = "";

        // Accumulate list of column names
        for (size_t i = 0; i < count; ++i) {
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
    }

    /// @brief Create MYSQL_BIND objects for IPv6 Reservation
    ///
    /// Fills in the MYSQL_BIND array for sending data in the IPv6 Reservation
    /// object to the database.
    ///
    /// @param resv IPv6 reservation object to be added to the database.
    ///        None of the fields in the reservation are modified -
    ///        the reservation data is only read.
    /// @param id ID of a host owning this reservation
    ///
    /// @return Vector of MySQL BIND objects representing the data to be added.
    std::vector<MYSQL_BIND> createBindForSend(const IPv6Resrv& resv, const HostID& id) {

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
            // reservation_id INT UNSIGNED NOT NULL
            // The host_id is auto_incremented by MySQL database,
            // so we need to pass the NULL value
            reservation_id_ = static_cast<uint32_t>(NULL);
            bind_[0].buffer_type = MYSQL_TYPE_LONG;
            bind_[0].buffer = reinterpret_cast<char*>(&reservation_id_);
            bind_[0].is_unsigned = MLM_TRUE;

            // address VARCHAR(39)
            address_ = resv.getPrefix().toText();
            address_len_ = address_.length();
            bind_[1].buffer_type = MYSQL_TYPE_BLOB;
            bind_[1].buffer = reinterpret_cast<char*>
                (const_cast<char*>(address_.c_str()));
            bind_[1].buffer_length = address_len_;
            bind_[1].length = &address_len_;

            // prefix_len tinyint
            prefix_len_ = resv.getPrefixLen();
            bind_[2].buffer_type = MYSQL_TYPE_TINY;
            bind_[2].buffer = reinterpret_cast<char*>(&prefix_len_);
            bind_[2].is_unsigned = MLM_TRUE;

            // type tinyint
            // See lease6_types for values (0 = IA_NA, 1 = IA_TA, 2 = IA_PD)
            type_ = resv.getType() == IPv6Resrv::TYPE_NA ? 0 : 2;
            bind_[3].buffer_type = MYSQL_TYPE_TINY;
            bind_[3].buffer = reinterpret_cast<char*>(&type_);
            bind_[3].is_unsigned = MLM_TRUE;

            // dhcp6_iaid INT UNSIGNED
            /// @todo: We don't support iaid in the IPv6Resrv yet.
            iaid_ = 0;
            bind_[4].buffer_type = MYSQL_TYPE_LONG;
            bind_[4].buffer = reinterpret_cast<char*>(&iaid_);
            bind_[4].is_unsigned = MLM_TRUE;

            // host_id INT UNSIGNED NOT NULL
            bind_[5].buffer_type = MYSQL_TYPE_LONG;
            bind_[5].buffer = reinterpret_cast<char*>(&host_id_);
            bind_[5].is_unsigned = MLM_TRUE;

        } catch (const std::exception& ex) {
            isc_throw(DbOperationError,
                      "Could not create bind array from IPv6 Reservation: "
                      << resv_.toText() << ", reason: " << ex.what());
        }

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return (std::vector<MYSQL_BIND>(&bind_[0], &bind_[RESRV_COLUMNS]));
    }


    /// @brief Create BIND array to receive data
    ///
    /// Creates a MYSQL_BIND array to receive Lease4 data from the database.
    /// After data is successfully received, getLeaseData() can be used to copy
    /// it to a Lease6 object.
    ///
    std::vector<MYSQL_BIND> createBindForReceive() {
        // Initialize MYSQL_BIND array.
        // It sets all fields, including is_null, to zero, so we need to set
        // is_null only if it should be true. This gives up minor performance
        // benefit while being safe approach. For improved readability, the
        // code that explicitly sets is_null is there, but is commented out.
        memset(bind_, 0, sizeof(bind_));

        // reservation_id INT UNSIGNED NOT NULL
        bind_[0].buffer_type = MYSQL_TYPE_LONG;
        bind_[0].buffer = reinterpret_cast<char*>(&reservation_id_);
        bind_[0].is_unsigned = MLM_TRUE;

        // address VARCHAR(39)
        bind_[1].buffer_type = MYSQL_TYPE_BLOB;
        bind_[1].buffer = reinterpret_cast<char*>
                            (const_cast<char*>(&address_[0]));
        bind_[1].buffer_length = address_len_;
        bind_[1].length = &address_len_;

        // prefix_len tinyint
        bind_[2].buffer_type = MYSQL_TYPE_TINY;
        bind_[2].buffer = reinterpret_cast<char*>(&prefix_len_);
        bind_[2].is_unsigned = MLM_TRUE;

        // type tinyint
        bind_[3].buffer_type = MYSQL_TYPE_TINY;
        bind_[3].buffer = reinterpret_cast<char*>(&type_);
        bind_[3].is_unsigned = MLM_TRUE;

        // dhcp6_iaid INT UNSIGNED
        bind_[4].buffer_type = MYSQL_TYPE_LONG;
        bind_[4].buffer = reinterpret_cast<char*>(&iaid_);
        bind_[4].is_unsigned = MLM_TRUE;

        // host_id INT UNSIGNED NOT NULL
        bind_[5].buffer_type = MYSQL_TYPE_LONG;
        bind_[5].buffer = reinterpret_cast<char*>(&host_id_);
        bind_[5].is_unsigned = MLM_TRUE;

        // Add the error flags
        setErrorIndicators(bind_, error_, RESRV_COLUMNS);

        // .. and check that we have the numbers correct at compile time.
        BOOST_STATIC_ASSERT(5 < RESRV_COLUMNS);

        // Add the data to the vector.  Note the end element is one after the
        // end of the array.
        return(std::vector<MYSQL_BIND>(&bind_[0], &bind_[RESRV_COLUMNS]));

    }

    /// @brief Copy Received Data into IPv6 reservation
    ///
    /// Called after the MYSQL_BIND array created by createBindForReceive()
    /// has been used, this copies data from the internal member variables
    /// into a IPv6Resrv object.
    ///
    /// @return IPv6Resrv object (containing IPv6 address or prefix reservation)
    IPv6Resrv getIPv6ReservData(){

        // Set the IPv6 Reservation type (0 = IA_NA, 1 = IA_TA, 2 = IA_PD)
        IPv6Resrv::Type type = IPv6Resrv::TYPE_NA;

        switch (type_) {
        case 0:
            type = IPv6Resrv::TYPE_NA;
            break;

        case 1:
            type = IPv6Resrv::TYPE_TA;
            break;

        case 2:
            type = IPv6Resrv::TYPE_PD;
            break;

        default:
            isc_throw(BadValue,
                    "invalid IPv6 reservation type returned: "
                    << static_cast<int>(type_)
                    << ". Only 0, 1 or 2 are allowed.");
        }

        IPv6Resrv r(type, IOAddress(address_), prefix_len_);
        return (r);
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
        return (getColumnsInError(error_, columns_, RESRV_COLUMNS));
    }

    /// @brief Converts ClientClasses to a signgle string with coma separated values
    ///
    /// @param classes classes structure that contains zero or more classes
    /// @return a single string with coma separated values
    std::string classesToString(const ClientClasses& classes) {
        string txt;
        bool first = true;
        for (ClientClasses::const_iterator it = classes.begin();
             it != classes.end(); ++it) {
            if (!first) {
                txt += ",";
            }
            txt += (*it);

            first = false;
        }

        return (txt);
    }

private:
    uint64_t	host_id_;        /// Host unique identifier
    uint64_t    reservation_id_; /// Host unique identifier
    size_t      host_id_length_; /// Length of the host unique ID
    std::string address_;        ///< Address (or prefix)
    size_t      address_len_;    ///< Length of the textual address representation
    uint8_t     prefix_len_;     ///< Length of the prefix (128 for addresses)
    uint8_t     type_;
    uint8_t     iaid_;

    uint64_t    host_id_len_;

    // NULL flags for subnets id, ipv4 address, hostname and client classes
    my_bool     host_id_null_;
    my_bool     address_null_;
    my_bool     prefix_len_null_;
    my_bool     iaid_null_;

    IPv6Resrv   resv_;

    MYSQL_BIND  bind_[RESRV_COLUMNS];
    std::string columns_[RESRV_COLUMNS]; /// Column names
    my_bool     error_[RESRV_COLUMNS];   /// Error array
    HostPtr     host_;			 /// Pointer to Host object
};

// MySqlHostDataSource Constructor and Destructor

MySqlHostDataSource::MySqlHostDataSource(
        const MySqlConnection::ParameterMap& parameters) : conn_(parameters) {

    // Open the database.
    conn_.openDatabase();

    // Enable autocommit.  To avoid a flush to disk on every commit, the global
    // parameter innodb_flush_log_at_trx_commit should be set to 2.  This will
    // cause the changes to be written to the log, but flushed to disk in the
    // background every second.  Setting the parameter to that value will speed
    // up the system, but at the risk of losing data if the system crashes.
    my_bool result = mysql_autocommit(conn_.mysql_, 1);
    if (result != 0) {
        isc_throw(DbOperationError, mysql_error(conn_.mysql_));
    }

    // Prepare all statements likely to be used.
    conn_.prepareStatements(tagged_statements,
            MySqlHostDataSource::NUM_STATEMENTS);

    // Create the exchange objects for use in exchanging data between the
    // program and the database.
    hostExchange_.reset(new MySqlHostReservationExchange());

    resvExchange_.reset(new MySqlIPv6ReservationExchange());
}

MySqlHostDataSource::~MySqlHostDataSource() {
    // Free up the prepared statements, ignoring errors. (What would we do
    // about them? We're destroying this object and are not really concerned
    // with errors on a database connection that is about to go away.)
    for (int i = 0; i < conn_.statements_.size(); ++i) {
        if (conn_.statements_[i] != NULL) {
            (void) mysql_stmt_close(conn_.statements_[i]);
            conn_.statements_[i] = NULL;
        }
    }

    // There is no need to close the database in this destructor: it is
    // closed in the destructor of the mysql_ member variable.
}

bool
MySqlHostDataSource::checkIfExists(const HostPtr& host){
    /// @todo: Implement this as a single query get(identifier_type, identifier)
    return (get4(host->getIPv4SubnetID(), host->getHWAddress(), host->getDuid()) ||
            get6(host->getIPv6SubnetID(), host->getDuid(), host->getHWAddress()));
}

void
MySqlHostDataSource::add(const HostPtr& host) {
    // Check if the host is not a duplicate
    if (checkIfExists(host)){
        isc_throw(DuplicateEntry, "Host with same parameters already exists.");
    } else {
        // Create the MYSQL_BIND array for the host
        std::vector<MYSQL_BIND> bind = hostExchange_->createBindForSend(host);

        // ... and call addHost() code.
        addQuery(INSERT_HOST, bind);

        IPv6ResrvRange v6resv = host->getIPv6Reservations();
        if (std::distance(v6resv.first, v6resv.second) == 0) {
            // If there are no v6 reservations, we're done here.
            return;
        }

        // Gets the last inserted hosts id
        uint64_t host_id = mysql_insert_id(conn_.mysql_);
        for (IPv6ResrvIterator resv = v6resv.first; resv != v6resv.second; ++resv) {
            addResv(resv->second, host_id);
        }
    }
}

void
MySqlHostDataSource::addResv(const IPv6Resrv& resv, HostID id) {
    std::vector<MYSQL_BIND> bind =
        resvExchange_->createBindForSend(resv, id);

    addQuery(INSERT_V6_RESRV, bind);
}

void
MySqlHostDataSource::addQuery(StatementIndex stindex,
                             std::vector<MYSQL_BIND>& bind) {

        // Bind the parameters to the statement
        int status = mysql_stmt_bind_param(conn_.statements_[stindex],
                                            &bind[0]);
        checkError(status, stindex, "unable to bind parameters");

        // Execute the statement
        status = mysql_stmt_execute(conn_.statements_[stindex]);
        if (status != 0) {
            // Failure: check for the special case of duplicate entry.
            if (mysql_errno(conn_.mysql_) == ER_DUP_ENTRY) {
                isc_throw(DuplicateEntry, "Database duplicate entry error");
            }
            checkError(status, stindex, "unable to execute");
        }
}

void
MySqlHostDataSource::getIPv6ReservationCollection(StatementIndex stindex,
        MYSQL_BIND* bind, boost::shared_ptr<MySqlIPv6ReservationExchange> exchange,
        IPv6ResrvCollection& result) const {

    // Bind the selection parameters to the statement
    int status = mysql_stmt_bind_param(conn_.statements_[stindex], bind);
    checkError(status, stindex, "unable to bind WHERE clause parameter");

    // Set up the MYSQL_BIND array for the data being returned and bind it to
    // the statement.
    std::vector<MYSQL_BIND> outbind = exchange->createBindForReceive();
    status = mysql_stmt_bind_result(conn_.statements_[stindex], &outbind[0]);
    checkError(status, stindex, "unable to bind SELECT clause parameters");

    // Execute the statement
    status = mysql_stmt_execute(conn_.statements_[stindex]);
    checkError(status, stindex, "unable to execute");

    // Ensure that all the lease information is retrieved in one go to avoid
    // overhead of going back and forth between client and server.
    status = mysql_stmt_store_result(conn_.statements_[stindex]);
    checkError(status, stindex, "unable to set up for storing all results");

    // Set up the fetch "release" object to release resources associated
    // with the call to mysql_stmt_fetch when this method exits, then
    // retrieve the data.
    MySqlFreeResult fetch_release(conn_.statements_[stindex]);
    while ((status = mysql_stmt_fetch(conn_.statements_[stindex])) == 0) {
        try {
            result.insert(IPv6ResrvTuple(exchange->getIPv6ReservData().getType(),
                                            exchange->getIPv6ReservData()));

        } catch (const isc::BadValue& ex) {
            // Rethrow the exception with a bit more data.
            isc_throw(BadValue, ex.what() << ". Statement is <" <<
                    conn_.text_statements_[stindex] << ">");
        }
    }

    // How did the fetch end?
    if (status == 1) {
        // Error - unable to fetch results
        checkError(status, stindex, "unable to fetch results");
    } else if (status == MYSQL_DATA_TRUNCATED) {
        // Data truncated - throw an exception indicating what was at fault
        isc_throw(DataTruncated, conn_.text_statements_[stindex]
                  << " returned truncated data: columns affected are "
                  << exchange->getErrorColumns());
    }
}

IPv6ResrvCollection
MySqlHostDataSource::getAllReservations(HostID host_id) const{

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    uint32_t id = static_cast<uint32_t>(host_id);
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&id);
    inbind[0].is_unsigned = MLM_TRUE;

    IPv6ResrvCollection result;
    getIPv6ReservationCollection(GET_V6_RESRV, inbind, resvExchange_, result);

    return (result);
}

void
MySqlHostDataSource::assignReservations(HostPtr& host) const {

    IPv6ResrvCollection reservations;
    reservations = getAllReservations(host->getHostId());

    for (IPv6ResrvIterator resv = reservations.begin(); resv != reservations.end(); ++resv){
        host->addReservation(resv->second);

    }
}

void
MySqlHostDataSource::getHostCollection(StatementIndex stindex, MYSQL_BIND* bind,
        boost::shared_ptr<MySqlHostReservationExchange> exchange,
        ConstHostCollection& result, bool single) const {

    // Bind the selection parameters to the statement
    int status = mysql_stmt_bind_param(conn_.statements_[stindex], bind);
    checkError(status, stindex, "unable to bind WHERE clause parameter");

    // Set up the MYSQL_BIND array for the data being returned and bind it to
    // the statement.
    std::vector<MYSQL_BIND> outbind = exchange->createBindForReceive();
    status = mysql_stmt_bind_result(conn_.statements_[stindex], &outbind[0]);
    checkError(status, stindex, "unable to bind SELECT clause parameters");

    // Execute the statement
    status = mysql_stmt_execute(conn_.statements_[stindex]);
    checkError(status, stindex, "unable to execute");

    // Ensure that all the lease information is retrieved in one go to avoid
    // overhead of going back and forth between client and server.
    status = mysql_stmt_store_result(conn_.statements_[stindex]);
    checkError(status, stindex, "unable to set up for storing all results");

    // Set up the fetch "release" object to release resources associated
    // with the call to mysql_stmt_fetch when this method exits, then
    // retrieve the data.
    MySqlFreeResult fetch_release(conn_.statements_[stindex]);
    int count = 0;
    HostPtr host;
    while ((status = mysql_stmt_fetch(conn_.statements_[stindex])) == 0) {
        try {
            host = exchange->getHostData();
            assignReservations(host);
            result.push_back(host);

        } catch (const isc::BadValue& ex) {
            // Rethrow the exception with a bit more data.
            isc_throw(BadValue, ex.what() << ". Statement is <" <<
                    conn_.text_statements_[stindex] << ">");
        }

        if (single && (++count > 1)) {
            isc_throw(MultipleRecords, "multiple records were found in the "
                      "database where only one was expected for query "
                      << conn_.text_statements_[stindex]);
        }
    }

    // How did the fetch end?
    if (status == 1) {
        // Error - unable to fetch results
        checkError(status, stindex, "unable to fetch results");
    } else if (status == MYSQL_DATA_TRUNCATED) {
        // Data truncated - throw an exception indicating what was at fault
        isc_throw(DataTruncated, conn_.text_statements_[stindex]
                  << " returned truncated data: columns affected are "
                  << exchange->getErrorColumns());
    }
}

ConstHostCollection
MySqlHostDataSource::getAll(const HWAddrPtr& hwaddr, const DuidPtr& duid) const {

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    memset(inbind, 0, sizeof(inbind));

    uint8_t dhcp_identifier_type = 0;
    long unsigned int length = 0;
    if (duid){
        // DUID
        // set proper dhcp_identifier_type
        dhcp_identifier_type = BaseHostDataSource::ID_DUID; // 1
        inbind[1].buffer = reinterpret_cast<char*>(&dhcp_identifier_type);

        const vector<uint8_t>& duid_vector = duid->getDuid();
        length = duid_vector.size();
        inbind[0].buffer_type = MYSQL_TYPE_BLOB;
        inbind[0].buffer = reinterpret_cast<char*>
            (const_cast<uint8_t*>(&duid_vector[0]));
        inbind[0].buffer_length = length;
        inbind[0].length = &length;
    } else if (hwaddr) {
        // HW Address
        dhcp_identifier_type = BaseHostDataSource::ID_HWADDR; // 0
        inbind[1].buffer = reinterpret_cast<char*>(&dhcp_identifier_type);

        const vector<uint8_t>& hwaddr_vector = hwaddr->hwaddr_;
        length = hwaddr_vector.size();
        inbind[0].buffer_type = MYSQL_TYPE_BLOB;
        inbind[0].buffer = reinterpret_cast<char*>
            (const_cast<uint8_t*>(&hwaddr_vector[0]));
        inbind[0].buffer_length = length;
        inbind[0].length = &length;
    }

    // dhcp identifier type
    inbind[1].buffer_type = MYSQL_TYPE_TINY;
    inbind[1].buffer = reinterpret_cast<char*>(&dhcp_identifier_type);
    inbind[1].is_unsigned = MLM_TRUE;

    ConstHostCollection result;
    getHostCollection(GET_HOST_HWADDR_DUID, inbind, hostExchange_, result, false);

    return (result);
}

ConstHostCollection
MySqlHostDataSource::getAll4(const asiolink::IOAddress& address) const {

    // Set up the WHERE clause value
    MYSQL_BIND inbind[1];
    memset(inbind, 0, sizeof(inbind));

    uint32_t addr4 = static_cast<uint32_t>(address);
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&addr4);
    inbind[0].is_unsigned = MLM_TRUE;

    ConstHostCollection result;
    getHostCollection(GET_HOST_ADDR, inbind, hostExchange_, result, false);

    return (result);
}

ConstHostPtr
MySqlHostDataSource::get4(const SubnetID& subnet_id, const HWAddrPtr& hwaddr,
                          const DuidPtr& duid) const {

    // Set up the WHERE clause value
    MYSQL_BIND inbind[3];
    memset(inbind, 0, sizeof(inbind));

    uint32_t subnet_buffer = static_cast<uint32_t>(subnet_id);
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet_buffer);
    inbind[0].is_unsigned = MLM_TRUE;

    /// @todo: Rethink the logic in BaseHostDataSource::get4(subnet, hwaddr, duid)
    if (hwaddr && duid) {
        isc_throw(BadValue, "MySQL host data source get4() called with both"
                  " hwaddr and duid, only one of them is allowed");
    }
    if (!hwaddr && !duid) {
        isc_throw(BadValue, "MySQL host data source get4() called with "
                  "neither hwaddr or duid specified, one of them is required");
    }

    unsigned long length = 0;
    uint8_t dhcp_identifier_type_ = 0;

    // Choosing one of the identifiers
    if (hwaddr) {
        // set identifier type
        dhcp_identifier_type_ = BaseHostDataSource::ID_HWADDR; // 0

        // set identifier value
        const vector<uint8_t>& hwaddr_vector = hwaddr->hwaddr_;
        length = hwaddr_vector.size();
        inbind[2].buffer_type = MYSQL_TYPE_BLOB;
        inbind[2].buffer = reinterpret_cast<char*>
            (const_cast<uint8_t*>(&hwaddr_vector[0]));
        inbind[2].buffer_length = length;
        inbind[2].length = &length;

    } else if (duid) {
        // set identifier type
        dhcp_identifier_type_ = BaseHostDataSource::ID_DUID; // 1

        // set identifier value
        const vector<uint8_t>& duid_vector = duid->getDuid();
        length = duid_vector.size();
        inbind[2].buffer_type = MYSQL_TYPE_BLOB;
        inbind[2].buffer = reinterpret_cast<char*>
            (const_cast<uint8_t*>(&duid_vector[0]));
        inbind[2].buffer_length = length;
        inbind[2].length = &length;
    }

    // dhcp identifier type
    inbind[1].buffer_type = MYSQL_TYPE_TINY;
    inbind[1].buffer = reinterpret_cast<char*>(&dhcp_identifier_type_);
    inbind[1].is_unsigned = MLM_TRUE;

    ConstHostCollection collection;
    getHostCollection(GET_HOST_SUBID4_DHCPID, inbind, hostExchange_,
                      collection, true);

    // Return single record if present, else clear the host.
    ConstHostPtr result;
    if (!collection.empty())
        result = *collection.begin();

    return (result);
}

ConstHostPtr
MySqlHostDataSource::get4(const SubnetID& subnet_id,
                          const asiolink::IOAddress& address) const {

    // Set up the WHERE clause value
    MYSQL_BIND inbind[2];
    uint32_t subnet = subnet_id;
    memset(inbind, 0, sizeof(inbind));
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet);
    inbind[0].is_unsigned = MLM_TRUE;

    uint32_t addr4 = static_cast<uint32_t>(address);
    inbind[1].buffer_type = MYSQL_TYPE_LONG;
    inbind[1].buffer = reinterpret_cast<char*>(&addr4);
    inbind[1].is_unsigned = MLM_TRUE;

    ConstHostCollection collection;
    getHostCollection(GET_HOST_SUBID_ADDR, inbind, hostExchange_,
                      collection, true);

    // Return single record if present, else clear the host.
    ConstHostPtr result;
    if (!collection.empty())
        result = *collection.begin();

    return (result);
}

ConstHostPtr
MySqlHostDataSource::get6(const SubnetID& subnet_id, const DuidPtr& duid,
                          const HWAddrPtr& hwaddr) const {

    // Set up the WHERE clause value
    MYSQL_BIND inbind[3];
    memset(inbind, 0, sizeof(inbind));

    uint32_t subnet_buffer = static_cast<uint32_t>(subnet_id);
    inbind[0].buffer_type = MYSQL_TYPE_LONG;
    inbind[0].buffer = reinterpret_cast<char*>(&subnet_buffer);
    inbind[0].is_unsigned = MLM_TRUE;

    /// @todo: Rethink the logic in BaseHostDataSource::get6(subnet, hwaddr, duid)
    if (hwaddr && duid) {
        isc_throw(BadValue, "MySQL host data source get6() called with both"
                  " hwaddr and duid, only one of them is allowed");
    }
    if (!hwaddr && !duid) {
        isc_throw(BadValue, "MySQL host data source get6() called with "
                  "neither hwaddr or duid specified, one of them is required");
    }

    unsigned long length = 0;
    uint8_t dhcp_identifier_type_ = 0;

    // Choosing one of the identifiers
    if (hwaddr) {
        // set identifier type
        dhcp_identifier_type_ = BaseHostDataSource::ID_HWADDR; // 0

        // set identifier value
        const vector<uint8_t>& hwaddr_vector = hwaddr->hwaddr_;
        length = hwaddr_vector.size();
        inbind[2].buffer_type = MYSQL_TYPE_BLOB;
        inbind[2].buffer = reinterpret_cast<char*>
            (const_cast<uint8_t*>(&hwaddr_vector[0]));
        inbind[2].buffer_length = length;
        inbind[2].length = &length;
    } else if (duid) {
        // set identifier type
        dhcp_identifier_type_ = BaseHostDataSource::ID_DUID; // 1

        // set identifier value
        const vector<uint8_t>& duid_vector = duid->getDuid();
        length = duid_vector.size();
        inbind[2].buffer_type = MYSQL_TYPE_BLOB;
        inbind[2].buffer = reinterpret_cast<char*>
            (const_cast<uint8_t*>(&duid_vector[0]));
        inbind[2].buffer_length = length;
        inbind[2].length = &length;
    }

    // dhcp identifier type
    inbind[1].buffer_type = MYSQL_TYPE_TINY;
    inbind[1].buffer = reinterpret_cast<char*>(&dhcp_identifier_type_);
    inbind[1].is_unsigned = MLM_TRUE;

    ConstHostCollection collection;
    getHostCollection(GET_HOST_SUBID6_DHCPID, inbind, hostExchange_,
                      collection, true);

    // Return single record if present, else clear the host.
    ConstHostPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return (result);
}

ConstHostPtr
MySqlHostDataSource::get6(const asiolink::IOAddress& prefix,
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
    getHostCollection(GET_HOST_PREFIX, inbind, hostExchange_,
                      collection, true);

    // Return single record if present, else clear the host.
    ConstHostPtr result;
    if (!collection.empty()) {
        result = *collection.begin();
    }

    return (result);
}

// Miscellaneous database methods.

std::string MySqlHostDataSource::getName() const {
    std::string name = "";
    try {
        name = conn_.getParameter("name");
    } catch (...) {
        // Return an empty name
    }
    return (name);
}

std::string MySqlHostDataSource::getDescription() const {
    return (std::string("Host data source that stores host information"
                        "in MySQL database"));
}

std::pair<uint32_t, uint32_t> MySqlHostDataSource::getVersion() const {
    const StatementIndex stindex = GET_VERSION;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_MYSQL_GET_VERSION);

    uint32_t major;      // Major version number
    uint32_t minor;      // Minor version number

    // Execute the prepared statement
    int status = mysql_stmt_execute(conn_.statements_[stindex]);
    if (status != 0) {
        isc_throw(DbOperationError, "unable to execute <"
                  << conn_.text_statements_[stindex]
                  << "> - reason: " << mysql_error(conn_.mysql_));
    }

    // Bind the output of the statement to the appropriate variables.
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].is_unsigned = 1;
    bind[0].buffer = &major;
    bind[0].buffer_length = sizeof(major);

    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].is_unsigned = 1;
    bind[1].buffer = &minor;
    bind[1].buffer_length = sizeof(minor);

    status = mysql_stmt_bind_result(conn_.statements_[stindex], bind);
    if (status != 0) {
        isc_throw(DbOperationError, "unable to bind result set: "
                  << mysql_error(conn_.mysql_));
    }

    // Fetch the data and set up the "release" object to release associated
    // resources when this method exits then retrieve the data.
    MySqlFreeResult fetch_release(conn_.statements_[stindex]);
    status = mysql_stmt_fetch(conn_.statements_[stindex]);
    if (status != 0) {
        isc_throw(DbOperationError, "unable to obtain result set: "
                  << mysql_error(conn_.mysql_));
    }

    return (std::make_pair(major, minor));
}

void
MySqlHostDataSource::commit() {
    conn_.commit();
}


void
MySqlHostDataSource::rollback() {
    conn_.rollback();
}


}; // end of isc::dhcp namespace
}; // end of isc namespace
