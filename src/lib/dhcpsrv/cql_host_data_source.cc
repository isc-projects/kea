// Copyright (C) 2016 Deutsche Telekom AG.
//
// Author: Andrei Pavel <andrei.pavel@qualitance.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <config.h>

#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/option_definition.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cql_host_data_source.h>
#include <dhcpsrv/cql_lease_mgr.h>
#include <dhcpsrv/db_exceptions.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <util/buffer.h>
#include <util/optional_value.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>

#include <openssl/md5.h>

#include <list>
#include <vector>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

/// @brief Host identifier consisting of DUID or hardware address
typedef std::vector<uint8_t> HostIdentifier;

/// @brief Host identifier converted to Cassandra data type
typedef std::vector<cass_byte_t> CassHostIdentifier;

/// @brief Host identifier converted to Cassandra data type
typedef std::vector<cass_byte_t> CassOptionBuffer;

/// @brief key for HostMap containing objects which uniquely identify a
///     host: host identifier, host identifier type, subnets for IPv4 and IPv6
typedef boost::tuple<HostIdentifier,
                     Host::IdentifierType,
                     SubnetID,
                     SubnetID,
                     asiolink::IOAddress>
    HostKey;

/// @brief Map used to merge reservations and options into a single host on
///     retrieve from database
typedef boost::unordered_map<HostKey, HostPtr, boost::hash<HostKey> > HostMap;

/// @brief Maximum size of an IPv4 address represented as a text string. 12
///     digits plus 3 full stops (dots).
static const size_t ADDRESS4_TEXT_MAX_LENGTH = 15U;

/// @brief Maximum size of an IPv6 address represented as a text string. 32
///     hexadecimal characters written in 8 groups of four, plus 7 colon
///     separators.
static const size_t ADDRESS6_TEXT_MAX_LENGTH = 39U;

/// @brief Maximum length of classes stored in a host_ipv4/6_client_classes
///     column.
static const size_t CLIENT_CLASSES_MAX_LENGTH = 255U;

/// @brief Maximum length of the hostname stored in DNS. This length is
///     restricted by the length of the domain-name carried in the Client FQDN
///     Option (see RFC4702 and RFC4704).
static const size_t HOSTNAME_MAX_LENGTH = 255U;

/// @brief Maximum length of option value
static const size_t OPTION_VALUE_MAX_LENGTH = 4096U;

/// @brief Maximum length of option value specified in textual format
static const size_t OPTION_FORMATTED_VALUE_MAX_LENGTH = 8192U;

/// @brief Maximum length of option space name
static const size_t OPTION_SPACE_MAX_LENGTH = 128U;

/// @brief Numeric value representing the last supported identifier. This value
///     is used to validate whether the identifier type stored in a database is
///     within bounds of supported identifiers.
static const cass_int8_t MAX_IDENTIFIER_TYPE =
    static_cast<cass_int8_t>(Host::IDENT_CIRCUIT_ID);

/// @{
/// @brief Invalid values in the Cassandra database
static const char NULL_RESERVED_IPV6_PREFIX_ADDRESS[] = "";
static const cass_int32_t NULL_RESERVED_IPV6_PREFIX_LENGTH = 0;
static const cass_int32_t NULL_RESERVED_IPV6_PREFIX_ADDRESS_TYPE = -1;
static const cass_int32_t NULL_IAID = -1;
static const cass_int32_t NULL_OPTION_UNIVERSE = -1;
static const cass_int32_t NULL_OPTION_CODE = -1;
static const CassOptionBuffer NULL_OPTION_VALUE = CassOptionBuffer();
static const char NULL_OPTION_FORMATTED_VALUE[] = "";
static const char NULL_OPTION_SPACE[] = "";
static const cass_bool_t NULL_OPTION_IS_PERSISTENT = cass_false;
static const char NULL_OPTION_CLIENT_CLASS[] = "";
static const cass_int32_t NULL_OPTION_SUBNET_ID = -1;
/// @}

/// @brief Invalid reservation used to check for an invalid IPv6Resrv formed
///     from database values.
static const IPv6Resrv NULL_IPV6_RESERVATION =
    IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("::"), 128);

}  // anonymous namespace

namespace isc {
namespace dhcp {

/// @{
/// @brief Statement parameters
// INSERT_HOST
static const char* INSERT_HOST_PARAMS[] = {
    static_cast<const char*>("id"),
    static_cast<const char*>("host_identifier"),
    static_cast<const char*>("host_identifier_type"),
    static_cast<const char*>("host_ipv4_subnet_id"),
    static_cast<const char*>("host_ipv6_subnet_id"),
    static_cast<const char*>("host_ipv4_address"),
    static_cast<const char*>("hostname"),
    static_cast<const char*>("host_ipv4_client_classes"),
    static_cast<const char*>("host_ipv6_client_classes"),
    static_cast<const char*>("reserved_ipv6_prefix_address"),
    static_cast<const char*>("reserved_ipv6_prefix_length"),
    static_cast<const char*>("reserved_ipv6_prefix_address_type"),
    static_cast<const char*>("iaid"),
    static_cast<const char*>("option_universe"),
    static_cast<const char*>("option_code"),
    static_cast<const char*>("option_value"),
    static_cast<const char*>("option_formatted_value"),
    static_cast<const char*>("option_space"),
    static_cast<const char*>("option_is_persistent"),
    static_cast<const char*>("option_client_class"),
    static_cast<const char*>("option_subnet_id"),
    NULL};
// GET_HOST_BY_HOST_ID
static const char* GET_HOST_BY_HOST_ID_PARAMS[] = {
    static_cast<const char*>("host_identifier"),
    static_cast<const char*>("host_identifier_type"),
    NULL};
// GET_HOST_BY_IPV4_ADDRESS
static const char* GET_HOST_BY_IPV4_ADDRESS_PARAMS[] = {
    static_cast<const char*>("host_ipv4_address"),
    NULL};
// GET_HOST_BY_IPV4_SUBNET_ID_AND_HOST_ID
static const char* GET_HOST_BY_IPV4_SUBNET_ID_AND_HOST_ID_PARAMS[] = {
    static_cast<const char*>("host_ipv4_subnet_id"),
    static_cast<const char*>("host_identifier"),
    static_cast<const char*>("host_identifier_type"),
    NULL};
// GET_HOST_BY_IPV6_SUBNET_ID_AND_HOST_ID,
static const char* GET_HOST_BY_IPV6_SUBNET_ID_AND_HOST_ID_PARAMS[] = {
    static_cast<const char*>("host_ipv6_subnet_id"),
    static_cast<const char*>("host_identifier"),
    static_cast<const char*>("host_identifier_type"),
    NULL};
// GET_HOST_BY_IPV4_SUBNET_ID_AND_ADDRESS,
static const char* GET_HOST_BY_IPV4_SUBNET_ID_AND_ADDRESS_PARAMS[] = {
    static_cast<const char*>("host_ipv4_subnet_id"),
    static_cast<const char*>("host_ipv4_address"),
    NULL};
// GET_HOST_BY_IPV6_PREFIX
static const char* GET_HOST_BY_IPV6_PREFIX_PARAMS[] = {
    static_cast<const char*>("reserved_ipv6_prefix_address"),
    static_cast<const char*>("reserved_ipv6_prefix_length"),
    NULL};
// GET_HOST_BY_IPV6_SUBNET_ID_AND_ADDRESS
static const char* GET_HOST_BY_IPV6_SUBNET_ID_AND_ADDRESS_PARAMS[] = {
    static_cast<const char*>("host_ipv6_subnet_id"),
    static_cast<const char*>("reserved_ipv6_prefix_address"),
    NULL};
// GET_VERSION
static const char* GET_VERSION_PARAMS[] = {NULL};
/// @}

/// @brief Prepared CQL statements used by the backend to insert and retrieve
///     hosts from the database.
static CqlTaggedStatement tagged_statements[] = {
    // INSERT_HOST
    {INSERT_HOST_PARAMS, "INSERT_HOST",
     "INSERT INTO host_reservations ( "
     "id, "
     "host_identifier, "
     "host_identifier_type, "
     "host_ipv4_subnet_id, "
     "host_ipv6_subnet_id, "
     "host_ipv4_address, "
     "hostname, "
     "host_ipv4_client_classes, "
     "host_ipv6_client_classes, "
     "reserved_ipv6_prefix_address, "
     "reserved_ipv6_prefix_length, "
     "reserved_ipv6_prefix_address_type, "
     "iaid, "
     "option_universe, "
     "option_code, "
     "option_value, "
     "option_formatted_value, "
     "option_space, "
     "option_is_persistent, "
     "option_client_class, "
     "option_subnet_id "
     ") "
     "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?) "
     "IF NOT EXISTS "
    },

    // GET_HOST_BY_HOST_ID
    {GET_HOST_BY_HOST_ID_PARAMS, "GET_HOST_BY_HOST_ID",
     "SELECT "
     "id, "
     "host_identifier, "
     "host_identifier_type, "
     "host_ipv4_subnet_id, "
     "host_ipv6_subnet_id, "
     "host_ipv4_address, "
     "hostname, "
     "host_ipv4_client_classes, "
     "host_ipv6_client_classes, "
     "reserved_ipv6_prefix_address, "
     "reserved_ipv6_prefix_length, "
     "reserved_ipv6_prefix_address_type, "
     "iaid, "
     "option_universe, "
     "option_code, "
     "option_value, "
     "option_formatted_value, "
     "option_space, "
     "option_is_persistent, "
     "option_client_class, "
     "option_subnet_id "
     "FROM host_reservations "
     "WHERE host_identifier = ? "
     "AND host_identifier_type = ? "
     "ALLOW FILTERING "
    },

    // GET_HOST_BY_IPV4_ADDRESS
    {GET_HOST_BY_IPV4_ADDRESS_PARAMS, "GET_HOST_BY_IPV4_ADDRESS",
     "SELECT "
     "id, "
     "host_identifier, "
     "host_identifier_type, "
     "host_ipv4_subnet_id, "
     "host_ipv6_subnet_id, "
     "host_ipv4_address, "
     "hostname, "
     "host_ipv4_client_classes, "
     "host_ipv6_client_classes, "
     "reserved_ipv6_prefix_address, "
     "reserved_ipv6_prefix_length, "
     "reserved_ipv6_prefix_address_type, "
     "iaid, "
     "option_universe, "
     "option_code, "
     "option_value, "
     "option_formatted_value, "
     "option_space, "
     "option_is_persistent, "
     "option_client_class, "
     "option_subnet_id "
     "FROM host_reservations "
     "WHERE host_ipv4_address = ? "
     "ALLOW FILTERING "
    },

    // GET_HOST_BY_IPV4_SUBNET_ID_AND_HOST_ID
    {GET_HOST_BY_IPV4_SUBNET_ID_AND_HOST_ID_PARAMS,
     "GET_HOST_BY_IPV4_SUBNET_ID_AND_HOST_ID",
     "SELECT "
     "id, "
     "host_identifier, "
     "host_identifier_type, "
     "host_ipv4_subnet_id, "
     "host_ipv6_subnet_id, "
     "host_ipv4_address, "
     "hostname, "
     "host_ipv4_client_classes, "
     "host_ipv6_client_classes, "
     "reserved_ipv6_prefix_address, "
     "reserved_ipv6_prefix_length, "
     "reserved_ipv6_prefix_address_type, "
     "iaid, "
     "option_universe, "
     "option_code, "
     "option_value, "
     "option_formatted_value, "
     "option_space, "
     "option_is_persistent, "
     "option_client_class, "
     "option_subnet_id "
     "FROM host_reservations "
     "WHERE host_ipv4_subnet_id = ? "
     "AND host_identifier = ? "
     "AND host_identifier_type = ? "
     "ALLOW FILTERING "
    },

    // GET_HOST_BY_IPV6_SUBNET_ID_AND_HOST_ID
    {GET_HOST_BY_IPV6_SUBNET_ID_AND_HOST_ID_PARAMS,
     "GET_HOST_BY_IPV6_SUBNET_ID_AND_HOST_ID",
     "SELECT "
     "id, "
     "host_identifier, "
     "host_identifier_type, "
     "host_ipv4_subnet_id, "
     "host_ipv6_subnet_id, "
     "host_ipv4_address, "
     "hostname, "
     "host_ipv4_client_classes, "
     "host_ipv6_client_classes, "
     "reserved_ipv6_prefix_address, "
     "reserved_ipv6_prefix_length, "
     "reserved_ipv6_prefix_address_type, "
     "iaid, "
     "option_universe, "
     "option_code, "
     "option_value, "
     "option_formatted_value, "
     "option_space, "
     "option_is_persistent, "
     "option_client_class, "
     "option_subnet_id "
     "FROM host_reservations "
     "WHERE host_ipv6_subnet_id = ? "
     "AND host_identifier = ? "
     "AND host_identifier_type = ? "
     "ALLOW FILTERING "
    },

    // GET_HOST_BY_IPV4_SUBNET_ID_AND_ADDRESS
    {GET_HOST_BY_IPV4_SUBNET_ID_AND_ADDRESS_PARAMS,
     "GET_HOST_BY_IPV4_SUBNET_ID_AND_ADDRESS",
     "SELECT "
     "id, "
     "host_identifier, "
     "host_identifier_type, "
     "host_ipv4_subnet_id, "
     "host_ipv6_subnet_id, "
     "host_ipv4_address, "
     "hostname, "
     "host_ipv4_client_classes, "
     "host_ipv6_client_classes, "
     "reserved_ipv6_prefix_address, "
     "reserved_ipv6_prefix_length, "
     "reserved_ipv6_prefix_address_type, "
     "iaid, "
     "option_universe, "
     "option_code, "
     "option_value, "
     "option_formatted_value, "
     "option_space, "
     "option_is_persistent, "
     "option_client_class, "
     "option_subnet_id "
     "FROM host_reservations "
     "WHERE host_ipv4_subnet_id = ? "
     "AND host_ipv4_address = ? "
     "ALLOW FILTERING "
    },

    // GET_HOST_BY_IPV6_PREFIX
    {GET_HOST_BY_IPV6_PREFIX_PARAMS, "GET_HOST_BY_IPV6_PREFIX",
     "SELECT "
     "id, "
     "host_identifier, "
     "host_identifier_type, "
     "host_ipv4_subnet_id, "
     "host_ipv6_subnet_id, "
     "host_ipv4_address, "
     "hostname, "
     "host_ipv4_client_classes, "
     "host_ipv6_client_classes, "
     "reserved_ipv6_prefix_address, "
     "reserved_ipv6_prefix_length, "
     "reserved_ipv6_prefix_address_type, "
     "iaid, "
     "option_universe, "
     "option_code, "
     "option_value, "
     "option_formatted_value, "
     "option_space, "
     "option_is_persistent, "
     "option_client_class, "
     "option_subnet_id "
     "FROM host_reservations "
     "WHERE reserved_ipv6_prefix_address = ? "
     "AND reserved_ipv6_prefix_length = ? "
     "ALLOW FILTERING "
    },

    // GET_HOST_BY_IPV6_SUBNET_ID_AND_ADDRESS
    {GET_HOST_BY_IPV6_SUBNET_ID_AND_ADDRESS_PARAMS,
     "GET_HOST_BY_IPV6_SUBNET_ID_AND_ADDRESS",
     "SELECT "
     "id, "
     "host_identifier, "
     "host_identifier_type, "
     "host_ipv4_subnet_id, "
     "host_ipv6_subnet_id, "
     "host_ipv4_address, "
     "hostname, "
     "host_ipv4_client_classes, "
     "host_ipv6_client_classes, "
     "reserved_ipv6_prefix_address, "
     "reserved_ipv6_prefix_length, "
     "reserved_ipv6_prefix_address_type, "
     "iaid, "
     "option_universe, "
     "option_code, "
     "option_value, "
     "option_formatted_value, "
     "option_space, "
     "option_is_persistent, "
     "option_client_class, "
     "option_subnet_id "
     "FROM host_reservations "
     "WHERE host_ipv6_subnet_id = ? "
     "AND reserved_ipv6_prefix_address = ? "
     "ALLOW FILTERING "
    },

    // GET_VERSION
    {GET_VERSION_PARAMS, "GET_VERSION",
     "SELECT version, minor FROM schema_version"},

    // End of list sentinel
    {NULL, NULL, NULL}};  // tagged_statements

/// @brief Provides mechanisms for sending and retrieving data from the
///     host_reservations table.
class CqlHostExchange : public virtual CqlExchange {
public:
    /// @brief Statement Tags
    ///
    /// The contents of the enum are indexes into the list of CQL statements
    enum StatementIndex {
        // Inserts all options belonging to any reservation from a single host.
        INSERT_HOST,
        // Retrieves host information, IPv6 reservations and both IPv4 and IPv6
        // options associated with the host.
        GET_HOST_BY_HOST_ID,
        // Retrieves host information along with the IPv4 options associated
        // with it.
        GET_HOST_BY_IPV4_ADDRESS,
        // Retrieves host information and IPv4 options using subnet identifier
        // and client's identifier (i.e. hardware address or DUID).
        GET_HOST_BY_IPV4_SUBNET_ID_AND_HOST_ID,
        // Retrieves host information, IPv6 reservations and IPv6 options
        // associated with a host using subnet identifier and client's
        // identifier (i.e. hardware address or DUID).
        GET_HOST_BY_IPV6_SUBNET_ID_AND_HOST_ID,
        // Retrieves host information and IPv4 options for the host using subnet
        // identifier and IPv4 reservation.
        GET_HOST_BY_IPV4_SUBNET_ID_AND_ADDRESS,
        // Retrieves host information, IPv6 reservations and IPv6 options
        // associated with a host using prefix and prefix length. This query
        // returns host information for a single host. However, multiple rows
        // are returned due to left joining IPv6 reservations and IPv6 options.
        // The number of rows returned is multiplication of number of existing
        // IPv6 reservations and IPv6 options.
        GET_HOST_BY_IPV6_PREFIX,
        // Retrieves host information and IPv6 options for the host using subnet
        // identifier and IPv6 reservation.
        GET_HOST_BY_IPV6_SUBNET_ID_AND_ADDRESS,
        // Get CQL schema version.
        GET_VERSION,
        // Number of statements
        NUM_STATEMENTS
    };

    /// @brief Constructor
    ///
    /// Specifies table columns.
    CqlHostExchange();

    /// @brief Virtual destructor.
    virtual ~CqlHostExchange();

    /// @brief Binds member variables to data array to receive @ref Host data.
    ///
    /// Creates a bind array to receive @ref Host data from the Cassandra
    /// database. After data is successfully received, @ref retrieve() can be
    /// called to retrieve the @ref Host object. Called in @ref
    /// CqlExchange::executeRead().
    ///
    /// @param data array of objects representing data being retrieved
    /// @param statement_index prepared statement being executed; defaults to an
    ///     invalid statement
    virtual void createBindForReceive(CqlDataArray& data,
                                      const int statement_index = -1);

    /// @brief Binds @ref Host to data array to send data to the Cassandra
    ///     database.
    ///
    /// Fills in the bind array for sending data stored in the @ref Host object
    /// to the database.
    ///
    /// @param host @ref Host object being added to the Cassandra database
    /// @param subnet_id identifier of the subnet to which the host belongs
    /// @param reservation reservation belonging to the host
    /// @param option_space option space
    /// @param option_descriptor structure used to hold option information
    /// @param data array being filled with data from to the Host object
    void createBindForSend(const HostPtr& host,
                           const OptionalValue<SubnetID>& subnet_id,
                           const IPv6Resrv* const reservation,
                           const std::string& option_space,
                           const OptionDescriptor& option_descriptor,
                           CqlDataArray& data);

    /// @brief Create unique hash for storage in table id.
    ///
    /// Hash function used for creating a pseudo-unique hash from member
    /// values which uniquely determine an entry in the table. Uses OpenSSL's
    /// MD5 implementation.
    ///
    /// The primary key aggregates: host_ipv4_subnet_id, host_ipv6_subnet_id,
    /// host_ipv4_address, reserved_ipv6_prefix_address,
    /// reserved_ipv6_prefix_length, option_code, option_space.
    cass_int64_t hashIntoId() const;

    /// @brief Copy received data into Host object
    ///
    /// Copies information about the host into a newly created @ref Host object
    /// Called in @ref executeRead after @ref createBindForReceive().
    ///
    /// @return Host Pointer to a @ref HostPtr object holding a pointer to the
    /// @ref Host object returned.
    virtual void* retrieve();

    /// @brief Creates IPv6 reservation from the data contained in the
    /// currently processed row.
    ///
    /// Called after createBindForReceive().
    ///
    /// @return IPv6Resrv object (containing IPv6 address or prefix reservation)
    const IPv6Resrv retrieveReservation() const;

    /// @brief Retrieves option from members.
    OptionDescriptorPtr retrieveOption() const;

private:
    /// Pointer to Host object holding information being inserted into database.
    HostPtr host_;

    /// @brief Primary key. Aggregates: host_identifier, host_identifier_type,
    /// reserved_ipv6_prefix_address, reserved_ipv6_prefix_length, option_code,
    /// option_space.
    cass_int64_t id_;

    /// @brief Client's identifier (e.g. DUID, HW address) in binary format
    CassHostIdentifier host_identifier_;

    /// @brief Type of the identifier in the host_identifier_
    /// This value corresponds to the @ref Host::IdentifierType value.
    cass_int32_t host_identifier_type_;

    /// @brief IPv4 subnet identifier
    cass_int32_t host_ipv4_subnet_id_;

    /// @brief Ipv6 subnet identifier
    cass_int32_t host_ipv6_subnet_id_;

    /// @brief Reserved IPv4 address
    cass_int32_t host_ipv4_address_;

    /// @brief Name reserved for the host
    std::string hostname_;

    /// @brief A string holding comma separated list of IPv4 client classes
    std::string host_ipv4_client_classes_;

    /// @brief A string holding comma separated list of IPv6 client classes
    std::string host_ipv6_client_classes_;

    /// @brief Address belonging to the reserved IPv6 prefix
    std::string reserved_ipv6_prefix_address_;

    /// @brief Length of the reserved IPv6 prefix
    cass_int32_t reserved_ipv6_prefix_length_;

    /// @brief Reserver IPv6 prefix type
    /// This value corresponds to the @ref Host::IdentifierType value.
    cass_int32_t reserved_ipv6_prefix_address_type_;

    /// @brief The reservation's IAID
    cass_int32_t iaid_;

    /// @brief Version of DHCP (i.e. 0 for DHCPv4 and 1 for DHCPv6) to which the
    ///     option belongs.
    cass_int32_t option_universe_;

    /// @brief Option code
    cass_int32_t option_code_;

    /// @brief Option value
    CassOptionBuffer option_value_;

    /// @brief The textual value of an option
    std::string option_formatted_value_;

    /// @brief Option space name
    std::string option_space_;

    /// @brief Flag indicating if option is always sent or only on request
    cass_bool_t option_is_persistent_;

    /// @brief Option client class
    std::string option_client_class_;

    /// @brief Subnet identifier
    cass_int32_t option_subnet_id_;
};  // CqlHostExchange

CqlHostExchange::CqlHostExchange()
    : host_identifier_type_(0), host_ipv4_subnet_id_(0),
      host_ipv6_subnet_id_(0), host_ipv4_address_(0),
      reserved_ipv6_prefix_length_(0), reserved_ipv6_prefix_address_type_(0),
      iaid_(0), option_universe_(0), option_code_(0),
      option_is_persistent_(cass_false), option_subnet_id_(0) {
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "id", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_INT64)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "host_identifier", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_BYTES)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "host_identifier_type", parameters_.size(),
        EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "host_ipv4_subnet_id", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_INT32)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "host_ipv6_subnet_id", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_INT32)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "host_ipv4_address", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_INT32)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "hostname", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_STRING)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "host_ipv4_client_classes", parameters_.size(),
        EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_STRING)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "host_ipv6_client_classes", parameters_.size(),
        EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_STRING)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "reserved_ipv6_prefix_address", parameters_.size(),
        EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_STRING)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "reserved_ipv6_prefix_length", parameters_.size(),
        EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "reserved_ipv6_prefix_address_type", parameters_.size(),
        EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_INT32)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "iaid", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_INT32)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "option_universe", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_INT32)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "option_code", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_INT32)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "option_value", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_BYTES)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "option_formatted_value", parameters_.size(),
        EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_STRING)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "option_space", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_STRING)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "option_is_persistent", parameters_.size(),
        EXCHANGE_DATA_TYPE_IO_IN_OUT, EXCHANGE_DATA_TYPE_BOOL)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "option_client_class", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_STRING)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "option_subnet_id", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_INT32)));
    parameters_.push_back(ExchangeColumnInfoPtr(new ExchangeColumnInfo(
        "[applied]", parameters_.size(), EXCHANGE_DATA_TYPE_IO_IN_OUT,
        EXCHANGE_DATA_TYPE_BOOL)));
    BOOST_ASSERT(parameters_.size() == 22U);
}

CqlHostExchange::~CqlHostExchange() {
}

void
CqlHostExchange::createBindForReceive(CqlDataArray& data,
                                      const int /* statement_index = -1 */) {
    // Start with a fresh array.
    data.clear();
    // id: blob
    data.add(reinterpret_cast<void*>(&id_));
    // host_identifier: blob
    data.add(reinterpret_cast<void*>(&host_identifier_));
    // host_identifier_type: int
    data.add(reinterpret_cast<void*>(&host_identifier_type_));
    // host_ipv4_subnet_id: int
    data.add(reinterpret_cast<void*>(&host_ipv4_subnet_id_));
    // host_ipv6_subnet_id: int
    data.add(reinterpret_cast<void*>(&host_ipv6_subnet_id_));
    // host_ipv4_address: int
    data.add(reinterpret_cast<void*>(&host_ipv4_address_));
    // hostname: text
    data.add(reinterpret_cast<void*>(&hostname_));
    // host_ipv4_client_classes: text
    data.add(reinterpret_cast<void*>(&host_ipv4_client_classes_));
    // host_ipv6_client_classes: text
    data.add(reinterpret_cast<void*>(&host_ipv6_client_classes_));
    // reserved_ipv6_prefix_address: text
    data.add(reinterpret_cast<void*>(&reserved_ipv6_prefix_address_));
    // reserved_ipv6_prefix_length: int
    data.add(reinterpret_cast<void*>(&reserved_ipv6_prefix_length_));
    // reserved_ipv6_prefix_length: int
    data.add(reinterpret_cast<void*>(&reserved_ipv6_prefix_address_type_));
    // iaid: int
    data.add(reinterpret_cast<void*>(&iaid_));
    // option_universe: int
    data.add(reinterpret_cast<void*>(&option_universe_));
    // option_code: int
    data.add(reinterpret_cast<void*>(&option_code_));
    // option_value: blob
    data.add(reinterpret_cast<void*>(&option_value_));
    // option_formatted_value: text
    data.add(reinterpret_cast<void*>(&option_formatted_value_));
    // option_space: text
    data.add(reinterpret_cast<void*>(&option_space_));
    // option_is_persistent: boolean
    data.add(reinterpret_cast<void*>(&option_is_persistent_));
    // option_client_class: text
    data.add(reinterpret_cast<void*>(&option_client_class_));
    // option_subnet_id: int
    data.add(reinterpret_cast<void*>(&option_subnet_id_));
}

void
CqlHostExchange::createBindForSend(const HostPtr& host,
                                   const OptionalValue<SubnetID>& subnet_id,
                                   const IPv6Resrv* const reservation,
                                   const std::string& option_space,
                                   const OptionDescriptor& option_descriptor,
                                   CqlDataArray& data) {
    // Store host object to ensure it remains valid.
    host_ = host;

    // Set up the structures for the various components of the host
    // structure.
    try {
        // host_identifier: blob
        // Convert from std::vector<uint8_t> to std::vector<cass_byte_t>.
        HostIdentifier host_identifier = host->getIdentifier();
        host_identifier_ = CassHostIdentifier(host_identifier.begin(),
                                              host_identifier.end());
        if (host_identifier_.size() > DUID::MAX_DUID_LEN) {
            isc_throw(BadValue, "host identifier "
                                    << host_identifier_.data() << " of length "
                                    << host_identifier_.size()
                                    << " is greater than allowed of "
                                    << DUID::MAX_DUID_LEN);
        }

        // host_identifier_type: int
        host_identifier_type_ =
            static_cast<cass_int32_t>(host->getIdentifierType());
        if (host_identifier_type_ > MAX_IDENTIFIER_TYPE) {
            isc_throw(BadValue, "invalid host identifier type returned: "
                                    << host_identifier_type_);
        }

        // host_ipv4_subnet_id: int
        host_ipv4_subnet_id_ =
            static_cast<cass_int32_t>(host->getIPv4SubnetID());

        // host_ipv6_subnet_id: int
        host_ipv6_subnet_id_ =
            static_cast<cass_int32_t>(host->getIPv6SubnetID());

        // host_ipv4_address: int
        host_ipv4_address_ =
            static_cast<cass_int32_t>(host->getIPv4Reservation().toUint32());

        // hostname: text
        hostname_ = host->getHostname();
        if (hostname_.size() > HOSTNAME_MAX_LENGTH) {
            isc_throw(BadValue, "hostname " << hostname_ << " of length "
                                            << hostname_.size()
                                            << " is greater than allowed of "
                                            << HOSTNAME_MAX_LENGTH);
        }

        // host_ipv4_client_classes: text
        host_ipv4_client_classes_ = host->getClientClasses4().toText(",");
        if (host_ipv4_client_classes_.size() > CLIENT_CLASSES_MAX_LENGTH) {
            isc_throw(BadValue, "IPv4 client classes "
                                    << host_ipv4_client_classes_
                                    << " of length "
                                    << host_ipv4_client_classes_.size()
                                    << " is greater than allowed of "
                                    << CLIENT_CLASSES_MAX_LENGTH);
        }

        // host_ipv6_client_classes: text
        host_ipv6_client_classes_ = host->getClientClasses6().toText(",");
        if (host_ipv6_client_classes_.size() > CLIENT_CLASSES_MAX_LENGTH) {
            isc_throw(BadValue, "IPv6 client classes "
                                    << host_ipv6_client_classes_
                                    << " of length "
                                    << host_ipv6_client_classes_.size()
                                    << " is greater than allowed of "
                                    << CLIENT_CLASSES_MAX_LENGTH);
        }

        if (reservation == NULL) {
            reserved_ipv6_prefix_address_ = NULL_RESERVED_IPV6_PREFIX_ADDRESS;
            reserved_ipv6_prefix_length_ = NULL_RESERVED_IPV6_PREFIX_LENGTH;
            reserved_ipv6_prefix_address_type_ =
                NULL_RESERVED_IPV6_PREFIX_ADDRESS_TYPE;
            iaid_ = NULL_IAID;
        } else {
            // reserved_ipv6_prefix_address: text
            reserved_ipv6_prefix_address_ = reservation->getPrefix().toText();

            // reserved_ipv6_prefix_length: int
            reserved_ipv6_prefix_length_ =
                static_cast<cass_int32_t>(reservation->getPrefixLen());

            // reserved_ipv6_prefix_address: int
            reserved_ipv6_prefix_address_type_ =
                reservation->getType() == IPv6Resrv::TYPE_NA ? 0 : 2;

            // iaid: int
            /// @todo: We don't support iaid in the IPv6Resrv yet.
            iaid_ = 0;
        }

        if (option_descriptor.option_ == NULL) {
            option_universe_ = NULL_OPTION_UNIVERSE;
            option_code_ = NULL_OPTION_CODE;
            option_value_ = NULL_OPTION_VALUE;
            option_formatted_value_ = NULL_OPTION_FORMATTED_VALUE;
            option_space_ = NULL_OPTION_SPACE;
            option_is_persistent_ = NULL_OPTION_IS_PERSISTENT;
            option_client_class_ = NULL_OPTION_CLIENT_CLASS;
            option_subnet_id_ = NULL_OPTION_SUBNET_ID;
        } else {
            // option_universe: int
            option_universe_ = option_descriptor.option_->getUniverse();

            // option_code: int
            option_code_ = option_descriptor.option_->getType();

            // option_value: blob
            // option_formatted_value: text
            if (option_descriptor.formatted_value_.empty()) {
                if (option_descriptor.option_->len() >
                    option_descriptor.option_->getHeaderLen()) {
                    // The formatted_value is empty and the option value
                    // is not empty so we need to prepare on-wire format
                    // for the option and store it in the database as a
                    // blob.
                    OutputBuffer buffer(option_descriptor.option_->len());
                    option_descriptor.option_->pack(buffer);
                    const char* buffer_ptr =
                        static_cast<const char*>(buffer.getData());
                    option_value_.assign(
                        buffer_ptr + option_descriptor.option_->getHeaderLen(),
                        buffer_ptr + buffer.getLength());
                } else {
                    option_value_.clear();
                }
                option_formatted_value_.clear();
            } else {
                option_value_.clear();
                option_formatted_value_ = option_descriptor.formatted_value_;
            }

            // option_space: text
            option_space_ = option_space;

            // option_is_persistent: boolean
            option_is_persistent_ =
                option_descriptor.persistent_ ? cass_true : cass_false;

            // option_client_class: text
            /// @todo Assign actual value to client class string.
            option_client_class_.clear();

            // option_subnet_id: int
            if (subnet_id.isSpecified()) {
                option_subnet_id_ = subnet_id;
            } else {
                option_subnet_id_ = 0;
            }
        }

        // id: bigint
        id_ = hashIntoId();

        // Add all parameters to bind array.
        data.clear();
        data.add(reinterpret_cast<void*>(&id_));
        data.add(reinterpret_cast<void*>(&host_identifier_));
        data.add(reinterpret_cast<void*>(&host_identifier_type_));
        data.add(reinterpret_cast<void*>(&host_ipv4_subnet_id_));
        data.add(reinterpret_cast<void*>(&host_ipv6_subnet_id_));
        data.add(reinterpret_cast<void*>(&host_ipv4_address_));
        data.add(reinterpret_cast<void*>(&hostname_));
        data.add(reinterpret_cast<void*>(&host_ipv4_client_classes_));
        data.add(reinterpret_cast<void*>(&host_ipv6_client_classes_));
        data.add(reinterpret_cast<void*>(&reserved_ipv6_prefix_address_));
        data.add(reinterpret_cast<void*>(&reserved_ipv6_prefix_length_));
        data.add(reinterpret_cast<void*>(&reserved_ipv6_prefix_address_type_));
        data.add(reinterpret_cast<void*>(&iaid_));
        data.add(reinterpret_cast<void*>(&option_universe_));
        data.add(reinterpret_cast<void*>(&option_code_));
        data.add(reinterpret_cast<void*>(&option_value_));
        data.add(reinterpret_cast<void*>(&option_formatted_value_));
        data.add(reinterpret_cast<void*>(&option_space_));
        data.add(reinterpret_cast<void*>(&option_is_persistent_));
        data.add(reinterpret_cast<void*>(&option_client_class_));
        data.add(reinterpret_cast<void*>(&option_subnet_id_));
    } catch (const std::exception& ex) {
        isc_throw(DbOperationError, "could not create bind array from host "
                                        << host->getHostname()
                                        << ", reason: " << ex.what());
    }
}

uint64_t
md5Hash(const std::string& input) {
    // Prepare structures for MD5().
    const size_t word_size = MD5_DIGEST_LENGTH / sizeof(uint64_t);
    uint64_t hash[word_size];
    unsigned char* digest = reinterpret_cast<unsigned char*>(hash);
    unsigned char* string =
        reinterpret_cast<unsigned char*>(const_cast<char*>(input.c_str()));
    std::fill(hash, hash + word_size, 0);

    // Get MD5 hash value.
    MD5(string, input.size(), digest);

    // Return the first part of the hash value which still retains all
    // properties of the full hash value.
    return hash[0];
}

cass_int64_t
CqlHostExchange::hashIntoId() const {
    // Allocates a fixed maximum length in the stringstream for each
    // aggregated field to avoid collisions between distinct entries.

    // Get key.
    std::stringstream key_stream;
    key_stream << std::setw(10) << std::setfill('0') << host_ipv4_subnet_id_;
    key_stream << std::setw(10) << std::setfill('0') << host_ipv6_subnet_id_;
    key_stream << std::setw(ADDRESS4_TEXT_MAX_LENGTH) << host_ipv4_address_;
    key_stream << std::setw(ADDRESS6_TEXT_MAX_LENGTH)
               << reserved_ipv6_prefix_address_;
    key_stream << std::setw(4) << std::setfill('0')
               << reserved_ipv6_prefix_length_;
    key_stream << std::setw(4) << std::setfill('0') << option_code_;
    key_stream << std::setw(OPTION_SPACE_MAX_LENGTH) << option_space_;
    const std::string key = key_stream.str();

    const uint64_t md5 = md5Hash(key);

    return static_cast<cass_int64_t>(md5);
}

void*
CqlHostExchange::retrieve() {
    uint64_t id = static_cast<uint64_t>(id_);

    HostIdentifier host_identifier =
        HostIdentifier(host_identifier_.begin(), host_identifier_.end());

    // Set the host identifier type in a variable of the appropriate data type.
    Host::IdentifierType host_identifier_type =
        static_cast<Host::IdentifierType>(host_identifier_type_);

    // Set IPv4 subnet ID to the value returned.
    SubnetID ipv4_subnet_id = static_cast<SubnetID>(host_ipv4_subnet_id_);

    // Set IPv6 subnet ID to the value returned.
    SubnetID ipv6_subnet_id = static_cast<SubnetID>(host_ipv6_subnet_id_);

    // Set IPv4 address reservation.
    asiolink::IOAddress ipv4_reservation =
        asiolink::IOAddress(host_ipv4_address_);

    Host* host = new Host(host_identifier.data(), host_identifier.size(),
                          host_identifier_type, ipv4_subnet_id, ipv6_subnet_id,
                          ipv4_reservation, hostname_,
                          host_ipv4_client_classes_, host_ipv6_client_classes_);
    host->setHostId(id);

    const IPv6Resrv reservation = retrieveReservation();
    if (reservation != NULL_IPV6_RESERVATION &&
        !host->hasReservation(reservation)) {
        host->addReservation(reservation);
    }

    OptionDescriptorPtr option_descriptor_ptr = retrieveOption();
    if (option_descriptor_ptr) {
        if (option_descriptor_ptr->option_->getUniverse() == Option::V4) {
            host->getCfgOption4()->add(*option_descriptor_ptr, option_space_);
        } else if (option_descriptor_ptr->option_->getUniverse() ==
                   Option::V6) {
            host->getCfgOption6()->add(*option_descriptor_ptr, option_space_);
        }
    }

    return reinterpret_cast<void*>(host);
}

const IPv6Resrv
CqlHostExchange::retrieveReservation() const {
    // Set the IPv6 Reservation type (0 = IA_NA, 2 = IA_PD)
    IPv6Resrv::Type type;
    switch (reserved_ipv6_prefix_address_type_) {
    case 0:
        type = IPv6Resrv::TYPE_NA;
        break;
    case 2:
        type = IPv6Resrv::TYPE_PD;
        break;
    case NULL_RESERVED_IPV6_PREFIX_ADDRESS_TYPE:
        return NULL_IPV6_RESERVATION;
    default:
        isc_throw(BadValue,
                  "invalid IPv6 reservation type returned: "
                      << reserved_ipv6_prefix_address_type_
                      << ". Only 0 (IA_NA) or 2 (IA_PD) are allowed.");
    }

    return IPv6Resrv(type, IOAddress(reserved_ipv6_prefix_address_),
                     reserved_ipv6_prefix_length_);
}

OptionDescriptorPtr
CqlHostExchange::retrieveOption() const {
    // Options are held in a binary or textual format in the database.
    // This is similar to having an option specified in a server
    // configuration file. Such option is converted to appropriate C++
    // class, using option definition. Thus, we need to find the
    // option definition for this option code and option space.

    // If the option space is a standard DHCPv4 or DHCPv6 option space,
    // this is most likely a standard option, for which we have a
    // definition created within libdhcp++.
    if (option_space_.empty() || option_universe_ == NULL_OPTION_UNIVERSE) {
        return OptionDescriptorPtr();
    }

    OptionDefinitionPtr option_definition_ptr =
        LibDHCP::getOptionDef(option_space_, option_code_);

    // Otherwise, we may check if this an option encapsulated within the
    // vendor space.
    if (!option_definition_ptr && option_space_ != DHCP4_OPTION_SPACE &&
        option_space_ != DHCP6_OPTION_SPACE) {
        uint32_t vendor_id = LibDHCP::optionSpaceToVendorId(option_space_);
        if (vendor_id > 0) {
            option_definition_ptr = LibDHCP::getVendorOptionDef(
                static_cast<Option::Universe>(option_universe_), vendor_id,
                option_code_);
        }
    }

    // In all other cases, we use runtime option definitions, which
    // should be also registered within the libdhcp++.
    if (!option_definition_ptr) {
        option_definition_ptr =
            LibDHCP::getRuntimeOptionDef(option_space_, option_code_);
    }

    OptionPtr option;
    if (!option_definition_ptr) {
        // If no definition found, we use generic option type.
        OptionBuffer option_buffer(option_value_.begin(), option_value_.end());
        option.reset(new Option(static_cast<Option::Universe>(option_universe_),
                                static_cast<uint16_t>(option_code_),
                                option_buffer.begin(), option_buffer.end()));
    } else {
        // The option value may be specified in textual or binary format in the
        // database. If formatted_value is empty, the binary format is used.
        // Depending on the format we use a different variant of @ref
        // optionFactory().
        if (option_formatted_value_.empty()) {
            OptionBuffer option_buffer(option_value_.begin(),
                                       option_value_.end());
            option = option_definition_ptr->optionFactory(
                static_cast<Option::Universe>(option_universe_),
                static_cast<uint16_t>(option_code_), option_buffer.begin(),
                option_buffer.end());
        } else {
            // Spit the value specified in comma separated values format.
            std::vector<std::string> split_vector;
            boost::split(split_vector, option_formatted_value_,
                         boost::is_any_of(","));
            option = option_definition_ptr->optionFactory(
                static_cast<Option::Universe>(option_universe_),
                static_cast<uint16_t>(option_code_), split_vector);
        }
    }

    return OptionDescriptorPtr(new OptionDescriptor(
        option, option_is_persistent_, option_formatted_value_));
}

/// @brief Implementation of the @ref CqlHostDataSource.
class CqlHostDataSourceImpl {
public:
    /// @brief Constructor.
    ///
    /// This constructor opens database connection and initializes prepared
    /// statements used in the queries.
    explicit CqlHostDataSourceImpl(
        const CqlConnection::ParameterMap& parameters);

    /// @brief Destructor.
    virtual ~CqlHostDataSourceImpl();

    /// @brief Implementation of @ref CqlHostDataSource::add()
    virtual void add(const HostPtr& host);

    /// @brief Implementation of @ref CqlHostDataSource::get4()
    virtual ConstHostPtr get4(const SubnetID& subnet_id,
                              const asiolink::IOAddress& address) const;

    /// @brief Implementation of @ref CqlHostDataSource::get4()
    virtual ConstHostPtr get4(const SubnetID& subnet_id,
                              const HWAddrPtr& hwaddr,
                              const DuidPtr& duid = DuidPtr()) const;

    /// @brief Implementation of @ref CqlHostDataSource::get4()
    virtual ConstHostPtr get4(const SubnetID& subnet_id,
                              const Host::IdentifierType& identifier_type,
                              const uint8_t* identifier_begin,
                              const size_t identifier_len) const;

    /// @brief Implementation of @ref CqlHostDataSource::get6()
    virtual ConstHostPtr get6(const asiolink::IOAddress& prefix,
                              const uint8_t prefix_len) const;

    /// @brief Implementation of @ref CqlHostDataSource::get6()
    virtual ConstHostPtr get6(const SubnetID& subnet_id,
                              const DuidPtr& duid,
                              const HWAddrPtr& hwaddr = HWAddrPtr()) const;

    /// @brief Implementation of @ref CqlHostDataSource::get6()
    virtual ConstHostPtr get6(const SubnetID& subnet_id,
                              const Host::IdentifierType& identifier_type,
                              const uint8_t* identifier_begin,
                              const size_t identifier_len) const;

    /// @brief Implementation of @ref CqlHostDataSource::get6()
    virtual ConstHostPtr get6(const SubnetID& subnet_id,
                              const asiolink::IOAddress& address) const;

    /// @brief Implementation of @ref CqlHostDataSource::getAll
    virtual ConstHostCollection getAll(const HWAddrPtr& hwaddr,
                                       const DuidPtr& duid = DuidPtr()) const;

    /// @brief Implementation of @ref CqlHostDataSource::getAll()
    virtual ConstHostCollection
    getAll(const Host::IdentifierType& identifier_type,
           const uint8_t* identifier_begin,
           const size_t identifier_len) const;

    /// @brief Implementation of @ref CqlHostDataSource::getAll4()
    virtual ConstHostCollection
    getAll4(const asiolink::IOAddress& address) const;

    /// @brief Implementation of @ref CqlHostDataSource::getName()
    virtual std::string getName() const;

    /// @brief Implementation of @ref CqlHostDataSource::getVersion()
    virtual VersionPair getVersion() const;

    /// @brief Implementation of @ref CqlHostDataSource::commit()
    virtual void commit();

    /// @brief Implementation of @ref CqlHostDataSource::rollback()
    virtual void rollback();

protected:
    /// @brief Adds any options found in the @ref Host object to a separate
    ///     table entry.
    ///
    /// @param host @ref Host object from which options are retrieved and
    ///     inserted into the Cassandra database
    /// @param reservation reservation for the current denormalized table entry
    /// @param option_spaces list of option spaces to search for
    /// @param cfg_option option configuration used to match option spaces in
    ///     order to obtain actual options
    virtual void insertHostWithOptions(
        const HostPtr& host,
        const IPv6Resrv* const reservation = NULL,
        const std::list<std::string>& option_spaces = std::list<std::string>(),
        const ConstCfgOptionPtr cfg_option = ConstCfgOptionPtr());

    /// @brief Adds any reservations found in the @ref Host object to a separate
    ///     table entry.
    ///
    /// @param host @ref Host object from which reservations are retrieved and
    ///     inserted into the Cassandra database
    /// @param reservation reservation for the current denormalized table entry
    /// @param option_spaces4 list of option spaces for universe Option::V4 to
    ///     search in
    /// @param cfg_option4 option configuration for universe Option::V4 used to
    ///     match option spaces in order to obtain actual options
    /// @param option_spaces6 list of option spaces for universe Option::V6 to
    ///     search in
    /// @param cfg_option6 option configuration for universe Option::V6 used to
    ///     match option spaces in order to obtain actual options
    virtual void
    insertHostWithReservations(const HostPtr& host,
                               const IPv6Resrv* const reservation,
                               const std::list<std::string>& option_spaces4,
                               const ConstCfgOptionPtr cfg_option4,
                               const std::list<std::string>& option_spaces6,
                               const ConstCfgOptionPtr cfg_option6);

    /// @brief Retrieves a single host.
    ///
    /// Calls @ref getHostCollection() and checks if a single host was returned.
    ///
    /// @param where_values array of bound objects used to filter the results
    /// @param statement_index prepared statement being executed
    ///
    /// @return one host or a null pointer to a host
    ///
    /// @throw MultipleRecords exception if two or more hosts are returned
    virtual ConstHostPtr
    getHost(const CqlDataArray& where_values,
            const CqlHostExchange::StatementIndex statement_index) const;

    /// @brief Retrieves a collection of hosts.
    ///
    /// Calls @ref CqlExchange::executeRead().
    ///
    /// @param where_values array of bound objects used to filter the results
    /// @param statement_index prepared statement being executed
    ///
    /// @return a collection of hosts containing one or more hosts
    virtual ConstHostCollection getHostCollection(
        const CqlDataArray& where_values,
        const CqlHostExchange::StatementIndex statement_index) const;

    /// @brief Inserts a single host.
    ///
    /// All information is available here. Calls @ref
    /// CqlExchange::executeWrite().
    ///
    /// @param host @ref Host object from which options are retrieved and
    ///     inserted into the Cassandra database
    /// @param subnet_id identifier of the subnet to which the host belongs
    /// @param reservation reservation for the current denormalized table entry
    /// @param option_space option space for the current denormalized table
    ///     entry's option
    /// @param option_descriptor option descriptor containing information for
    ///     the current denormalized table entry's option
    virtual void insertHost(
        const HostPtr& host,
        const OptionalValue<SubnetID>& subnet_id = OptionalValue<SubnetID>(),
        const IPv6Resrv* const reservation = NULL,
        const std::string& option_space = NULL_OPTION_SPACE,
        const OptionDescriptor& option_descriptor = OptionDescriptor(false));

    /// @brief Merge denormalized table entries that belong to the same host
    /// into a single host, one by one.
    ///
    /// @param target_host host which can contain multiple reservations and
    ///     options to which other distinct reservations and options are added.
    /// @param source_host host that is being search for new reservations and
    ///     options that will be merged into the old host.
    virtual void mergeHosts(HostPtr& target_host,
                            const ConstHostPtr& source_host) const;

private:
    /// @brief pointer to the exchange responsible for trading host information
    boost::shared_ptr<CqlHostExchange> host_exchange_;
    /// @brief pointer to the exchange responsible for retrieving schema version
    boost::shared_ptr<CqlVersionExchange> version_exchange_;

    /// @brief CQL connection
    mutable CqlConnection dbconn_;
};  // class CqlHostDataSourceImpl


/// @brief hash function for HostMap
///
/// @param key being hashed
///
/// @return hash value
std::size_t
hash_value(const HostKey& key) {
    // Get key.
    std::stringstream key_stream;
    HostIdentifier host_identifier = key.get<0>();
    key_stream << std::setw(DUID::MAX_DUID_LEN) << std::setfill('0')
               << DUID(host_identifier).toText();
    key_stream << std::setw(2) << std::setfill('0') << key.get<1>();
    key_stream << std::setw(10) << std::setfill('0') << key.get<2>();
    key_stream << std::setw(10) << std::setfill('0') << key.get<3>();
    key_stream << std::setw(ADDRESS4_TEXT_MAX_LENGTH) << std::setfill('0')
               << key.get<4>();
    const std::string key_string = key_stream.str();

    const uint64_t md5 = md5Hash(key_string);

    return static_cast<std::size_t>(md5);
}

/// @brief equals operator for HostKey
///
/// @param key1 left hand side operand
/// @param key2 right hand side operand
///
/// @return true if keys are equal. Deep comparison is made.
bool
operator==(const HostKey& key1, const HostKey& key2) {
    return key1.get<0>() == key2.get<0>() && key1.get<1>() == key2.get<1>() &&
           key1.get<2>() == key2.get<2>() && key1.get<3>() == key2.get<3>() &&
           key1.get<4>() == key2.get<4>();
}

CqlHostDataSourceImpl::CqlHostDataSourceImpl(
    const CqlConnection::ParameterMap& parameters)
    : host_exchange_(new CqlHostExchange()),
      version_exchange_(new CqlVersionExchange()), dbconn_(parameters) {
    // Open the database.
    dbconn_.openDatabase();
    // Prepare all possible statements.
    dbconn_.prepareStatements(tagged_statements);
}

CqlHostDataSourceImpl::~CqlHostDataSourceImpl() {
    // There is no need to close the database in this destructor: it is
    // closed in the destructor of the dbconn_ member variable.
}

void
CqlHostDataSourceImpl::add(const HostPtr& host) {
    // Start transaction.
    CqlTransaction transaction(dbconn_);

    // Get option space names and vendor space names and combine them within a
    // single list.
    // For IPv4:
    ConstCfgOptionPtr cfg_option4 = host->getCfgOption4();
    std::list<std::string> option_spaces4 = cfg_option4->getOptionSpaceNames();
    std::list<std::string> vendor_spaces4 =
        cfg_option4->getVendorIdsSpaceNames();
    option_spaces4.insert(option_spaces4.end(), vendor_spaces4.begin(),
                          vendor_spaces4.end());

    // For IPv6:
    ConstCfgOptionPtr cfg_option6 = host->getCfgOption6();
    std::list<std::string> option_spaces6 = cfg_option6->getOptionSpaceNames();
    std::list<std::string> vendor_spaces6 =
        cfg_option6->getVendorIdsSpaceNames();
    option_spaces6.insert(option_spaces6.end(), vendor_spaces6.begin(),
                          vendor_spaces6.end());

    // For every IPv6 reservation, add each of their options to the database.
    IPv6ResrvRange reservations = host->getIPv6Reservations();
    if (std::distance(reservations.first, reservations.second) > 0) {
        for (IPv6ResrvIterator it = reservations.first;
             it != reservations.second; ++it) {
            insertHostWithReservations(host, &it->second, option_spaces4,
                                       cfg_option4, option_spaces6,
                                       cfg_option6);
        }
    } else {
        // If host has no reservation, add entries with null reservation.
        // Options could still be present.
        insertHostWithReservations(host, NULL, option_spaces4, cfg_option4,
                                   option_spaces6, cfg_option6);
    }
    transaction.commit();
}

ConstHostPtr
CqlHostDataSourceImpl::get4(const SubnetID& subnet_id,
                            const asiolink::IOAddress& address) const {
    if (!address.isV4()) {
        isc_throw(BadValue, "CqlHostDataSource::get4(2): wrong address type, "
                            "address supplied is not an IPv4 address");
    }

    // Convert to CQL data types.
    cass_int32_t host_ipv4_subnet_id = static_cast<cass_int32_t>(subnet_id);
    cass_int32_t host_ipv4_address =
        static_cast<cass_int32_t>(address.toUint32());

    // Bind to array.
    CqlDataArray where_values;
    where_values.add(reinterpret_cast<void*>(&host_ipv4_subnet_id));
    where_values.add(reinterpret_cast<void*>(&host_ipv4_address));

    // Run statement.
    return getHost(*const_cast<const CqlDataArray*>(&where_values),
                   CqlHostExchange::GET_HOST_BY_IPV4_SUBNET_ID_AND_ADDRESS);
}

ConstHostPtr
CqlHostDataSourceImpl::get4(const SubnetID& subnet_id,
                            const HWAddrPtr& hwaddr,
                            const DuidPtr& duid) const {
    /// @todo: Rethink the logic in BaseHostDataSource::get4(subnet, hwaddr,
    /// duid)
    if (hwaddr && duid) {
        isc_throw(BadValue, "CqlHostDataSource::get4(3) called with both "
                            "hwaddr and duid, only one of them is allowed");
    } else if (!hwaddr && !duid) {
        isc_throw(BadValue, "CqlHostDataSource::get4(3) called with neither "
                            "hwaddr or duid specified, one of them is "
                            "required");
    } else if (duid) {
        HostIdentifier duid_vector = duid->getDuid();
        // Delegate to get4(4).
        return get4(subnet_id, Host::IDENT_DUID, duid_vector.data(),
                    duid_vector.size());
    } else if (hwaddr) {
        // Delegate to get4(4).
        return get4(subnet_id, Host::IDENT_HWADDR, hwaddr->hwaddr_.data(),
                    hwaddr->hwaddr_.size());
    }
    return ConstHostPtr();
}

ConstHostPtr
CqlHostDataSourceImpl::get4(const SubnetID& subnet_id,
                            const Host::IdentifierType& identifier_type,
                            const uint8_t* identifier_begin,
                            const size_t identifier_len) const {
    // Convert to CQL data types.
    cass_int32_t host_ipv4_subnet_id = static_cast<cass_int32_t>(subnet_id);
    CassHostIdentifier host_identifier(identifier_begin,
                                       identifier_begin + identifier_len);
    cass_int32_t host_identifier_type =
        static_cast<cass_int32_t>(identifier_type);

    // Bind to array.
    CqlDataArray where_values;
    where_values.add(reinterpret_cast<void*>(&host_ipv4_subnet_id));
    where_values.add(reinterpret_cast<void*>(&host_identifier));
    where_values.add(reinterpret_cast<void*>(&host_identifier_type));

    // Run statement.
    return getHost(*const_cast<const CqlDataArray*>(&where_values),
                   CqlHostExchange::GET_HOST_BY_IPV4_SUBNET_ID_AND_HOST_ID);
}

ConstHostPtr
CqlHostDataSourceImpl::get6(const asiolink::IOAddress& prefix,
                            const uint8_t prefix_len) const {
    // Convert to CQL data types.
    std::string reserved_ipv6_prefix_address = prefix.toText();
    cass_int32_t reserved_ipv6_prefix_length = prefix_len;

    // Bind to array.
    CqlDataArray where_values;
    where_values.add(reinterpret_cast<void*>(&reserved_ipv6_prefix_address));
    where_values.add(reinterpret_cast<void*>(&reserved_ipv6_prefix_length));

    // Get host id.
    ConstHostPtr host = getHost(*const_cast<const CqlDataArray*>(&where_values),
                                CqlHostExchange::GET_HOST_BY_IPV6_PREFIX);

    if (host == ConstHostPtr()) {
        return ConstHostPtr();
    }

    // Get host.
    HostIdentifier host_identifier = host->getIdentifier();
    ConstHostCollection collection =
        getAll(host->getIdentifierType(), host_identifier.data(),
               host_identifier.size());

    if (collection.empty()) {
        return ConstHostPtr();
    }

    if (collection.size() >= 2U) {
        isc_throw(
            MultipleRecords,
            "CqlHostDataSource::get6(2): multiple records were found in the "
            "database where only one was expected for statement "
                << dbconn_
                       .tagged_statements_[CqlHostExchange::GET_HOST_BY_HOST_ID]
                       .name_);
    }

    return *collection.begin();
}

ConstHostPtr
CqlHostDataSourceImpl::get6(const SubnetID& subnet_id,
                            const DuidPtr& duid,
                            const HWAddrPtr& hwaddr) const {
    /// @todo: Rethink the logic in BaseHostDataSource::get6(subnet, hwaddr,
    /// duid)
    if (hwaddr && duid) {
        isc_throw(BadValue, "CqlHostDataSource::get6(3): both hardware address "
                            "and DUID are specified, only one of them is "
                            "allowed");
    } else if (!hwaddr && !duid) {
        isc_throw(BadValue, "CqlHostDataSource::get6(3): both hardware address "
                            "and DUID are specified, one of them is required");
    } else if (duid) {
        HostIdentifier duid_vector = duid->getDuid();
        // Delegate to get6(4).
        return get6(subnet_id, Host::IDENT_DUID, duid_vector.data(),
                    duid_vector.size());
    } else if (hwaddr) {
        // Delegate to get6(4).
        return get6(subnet_id, Host::IDENT_HWADDR, hwaddr->hwaddr_.data(),
                    hwaddr->hwaddr_.size());
    }
    return ConstHostPtr();
}

ConstHostPtr
CqlHostDataSourceImpl::get6(const SubnetID& subnet_id,
                            const Host::IdentifierType& identifier_type,
                            const uint8_t* identifier_begin,
                            const size_t identifier_len) const {
    // Convert to CQL data types.
    cass_int32_t host_ipv6_subnet_id = static_cast<cass_int32_t>(subnet_id);
    CassHostIdentifier host_identifier(identifier_begin,
                                   identifier_begin + identifier_len);
    cass_int32_t host_identifier_type =
        static_cast<cass_int32_t>(identifier_type);

    // Bind to array.
    CqlDataArray where_values;
    where_values.add(reinterpret_cast<void*>(&host_ipv6_subnet_id));
    where_values.add(reinterpret_cast<void*>(&host_identifier));
    where_values.add(reinterpret_cast<void*>(&host_identifier_type));

    // Run statement.
    return getHost(*const_cast<const CqlDataArray*>(&where_values),
                   CqlHostExchange::GET_HOST_BY_IPV6_SUBNET_ID_AND_HOST_ID);
}

ConstHostPtr
CqlHostDataSourceImpl::get6(const SubnetID& subnet_id,
                            const IOAddress& address) const {
    // Convert to CQL data types.
    cass_int32_t host_ipv6_subnet_id = static_cast<cass_int32_t>(subnet_id);
    std::string reserved_ipv6_prefix_address = address.toText();

    // Bind to array.
    CqlDataArray where_values;
    where_values.add(reinterpret_cast<void*>(&host_ipv6_subnet_id));
    where_values.add(reinterpret_cast<void*>(&reserved_ipv6_prefix_address));

    // Run statement.
    return getHost(*const_cast<const CqlDataArray*>(&where_values),
                   CqlHostExchange::GET_HOST_BY_IPV6_SUBNET_ID_AND_ADDRESS);
}

ConstHostCollection
CqlHostDataSourceImpl::getAll(const HWAddrPtr& hwaddr,
                              const DuidPtr& duid) const {
    if (!duid && !hwaddr) {
        return ConstHostCollection();
    }

    // Convert to CQL data types.
    CassHostIdentifier host_identifier;
    cass_int32_t host_identifier_type;
    if (duid) {
        HostIdentifier duid_vector = duid->getDuid();
        host_identifier =
            CassHostIdentifier(duid_vector.begin(), duid_vector.end());
        host_identifier_type = static_cast<cass_int32_t>(Host::IDENT_DUID);
    } else if (hwaddr) {
        host_identifier = CassHostIdentifier(hwaddr->hwaddr_.begin(),
                                                   hwaddr->hwaddr_.end());
        host_identifier_type = static_cast<cass_int32_t>(Host::IDENT_HWADDR);
    }

    // Bind to array.
    CqlDataArray where_values;
    where_values.add(reinterpret_cast<void*>(&host_identifier));
    where_values.add(reinterpret_cast<void*>(&host_identifier_type));

    // Run statement.
    return getHostCollection(*const_cast<const CqlDataArray*>(&where_values),
                             CqlHostExchange::GET_HOST_BY_HOST_ID);
}

ConstHostCollection
CqlHostDataSourceImpl::getAll(const Host::IdentifierType& identifier_type,
                              const uint8_t* identifier_begin,
                              const size_t identifier_len) const {
    // Convert to CQL data types.
    CassHostIdentifier host_identifier(identifier_begin,
                                             identifier_begin + identifier_len);
    cass_int32_t host_identifier_type =
        static_cast<cass_int32_t>(identifier_type);

    // Bind to array.
    CqlDataArray where_values;
    where_values.add(reinterpret_cast<void*>(&host_identifier));
    where_values.add(reinterpret_cast<void*>(&host_identifier_type));

    // Run statement.
    return getHostCollection(*const_cast<const CqlDataArray*>(&where_values),
                             CqlHostExchange::GET_HOST_BY_HOST_ID);
}

ConstHostCollection
CqlHostDataSourceImpl::getAll4(const asiolink::IOAddress& address) const {
    // Convert to CQL data types.
    cass_int32_t host_ipv4_address =
        static_cast<cass_int32_t>(address.toUint32());

    // Bind to array.
    CqlDataArray where_values;
    where_values.add(reinterpret_cast<void*>(&host_ipv4_address));

    // Run statement.
    return getHostCollection(*const_cast<const CqlDataArray*>(&where_values),
                             CqlHostExchange::GET_HOST_BY_IPV4_ADDRESS);
}

std::string
CqlHostDataSourceImpl::getName() const {
    std::string name = "";
    try {
        name = dbconn_.getParameter("name");
    } catch (...) {
        // Return an empty name
    }
    return name;
}

VersionPair
CqlHostDataSourceImpl::getVersion() const {
    return version_exchange_->retrieveVersion(dbconn_,
                                              CqlHostExchange::GET_VERSION);
}

void
CqlHostDataSourceImpl::commit() {
    dbconn_.commit();
}

void
CqlHostDataSourceImpl::rollback() {
    dbconn_.rollback();
}

void
CqlHostDataSourceImpl::insertHostWithOptions(
    const HostPtr& host,
    const IPv6Resrv* const reservation /* = NULL */,
    const std::list<std::string>& option_spaces
    /* = std::list<std::string>() */,
    const ConstCfgOptionPtr cfg_option /* = ConstCfgOptionPtr() */) {
    // For each option space retrieve all options and insert them into the
    // database.
    bool option_found = false;
    for (std::list<std::string>::const_iterator space = option_spaces.begin();
         space != option_spaces.end(); ++space) {
        OptionContainerPtr options = cfg_option->getAll(*space);
        if (options && !options->empty()) {
            for (OptionContainer::const_iterator option = options->begin();
                 option != options->end(); ++option) {
                option_found = true;
                insertHost(host, OptionalValue<SubnetID>(), reservation, *space,
                           *option);
            }
        }
    }
    if (!option_found) {
        insertHost(host, OptionalValue<SubnetID>(), reservation);
    }
}

void
CqlHostDataSourceImpl::insertHostWithReservations(
    const HostPtr& host,
    const IPv6Resrv* const reservation,
    const std::list<std::string>& option_spaces4,
    const ConstCfgOptionPtr cfg_option4,
    const std::list<std::string>& option_spaces6,
    const ConstCfgOptionPtr cfg_option6) {
    // If host has no reservation, add entries with null reservation.
    // Options could still be present.
    if (cfg_option4 && !cfg_option4->empty()) {
        insertHostWithOptions(host, reservation, option_spaces4, cfg_option4);
    }
    if (cfg_option6 && !cfg_option6->empty()) {
        insertHostWithOptions(host, reservation, option_spaces6, cfg_option6);
    }
    if ((!cfg_option4 || cfg_option4->empty()) &&
        (!cfg_option6 || cfg_option6->empty())) {
        insertHostWithOptions(host, reservation);
    }
}

ConstHostPtr
CqlHostDataSourceImpl::getHost(
    const CqlDataArray& where_values,
    const CqlHostExchange::StatementIndex statement_index) const {
    ConstHostCollection collection =
        getHostCollection(where_values, statement_index);

    if (collection.empty()) {
        return ConstHostPtr();
    }

    if (collection.size() >= 2U) {
        isc_throw(MultipleRecords,
                  "multiple records were found in the database where only one "
                  "was expected for statement "
                      << dbconn_.tagged_statements_[statement_index].name_);
    }

    return *collection.begin();
}

ConstHostCollection
CqlHostDataSourceImpl::getHostCollection(
    const CqlDataArray& where_values,
    const CqlHostExchange::StatementIndex statement_index) const {

    // Run statement.
    CqlDataArray collection = host_exchange_->executeRead(
        dbconn_, where_values, statement_index, false);

    // Form HostPtr objects.
    HostCollection host_collection;
    for (std::vector<void*>::const_iterator it = collection.begin();
         it != collection.end(); ++it) {
        host_collection.push_back(HostPtr(reinterpret_cast<Host*>(*it)));
    }

    // Merge the denormalized table entries that belong to the same host into a
    // single host.
    HostMap map;
    for (HostCollection::iterator it = host_collection.begin();
         it != host_collection.end(); ++it) {
        HostKey key =
            HostKey((*it)->getIdentifier(), (*it)->getIdentifierType(),
                    (*it)->getIPv4SubnetID(), (*it)->getIPv6SubnetID(),
                    (*it)->getIPv4Reservation());
        if (map.find(key) == map.end()) {
            map[key] = *it;
        } else {
            mergeHosts(map[key], *it);
        }
    }

    ConstHostCollection result_collection;
    for (HostMap::const_iterator it = map.begin(); it != map.end(); ++it) {
        result_collection.push_back(it->second);
    }
    return result_collection;
}

void
CqlHostDataSourceImpl::insertHost(
    const HostPtr& host,
    const OptionalValue<SubnetID>& subnet_id
    /* = OptionalValue<SubnetID>() */,
    const IPv6Resrv* const reservation /* = NULL */,
    const std::string& option_space /* = NULL_OPTION_SPACE */,
    const OptionDescriptor& option_descriptor
    /* = OptionDescriptorPtr */) {
    CqlDataArray assigned_values;
    // @todo: Assign actual value to subnet id.
    host_exchange_->createBindForSend(host, subnet_id, reservation,
                                      option_space, option_descriptor,
                                      assigned_values);
    host_exchange_->executeWrite(dbconn_, assigned_values,
                                 CqlHostExchange::INSERT_HOST);
}

void
CqlHostDataSourceImpl::mergeHosts(HostPtr& target_host,
                                  const ConstHostPtr& source_host) const {
    // Merge reservations.
    const IPv6ResrvRange reservations_range =
        source_host->getIPv6Reservations();
    if (std::distance(reservations_range.first, reservations_range.second) >
        0) {
        for (IPv6ResrvIterator reservations_iterator = reservations_range.first;
             reservations_iterator != reservations_range.second;
             ++reservations_iterator) {
            if (!target_host->hasReservation(reservations_iterator->second)) {
                target_host->addReservation(reservations_iterator->second);
            }
        }
    }

    // Merge DHCPv4 options.
    source_host->getCfgOption4()->mergeTo(*target_host->getCfgOption4());

    // Merge DHCPv6 options.
    source_host->getCfgOption6()->mergeTo(*target_host->getCfgOption6());
}

CqlHostDataSource::CqlHostDataSource(
    const CqlConnection::ParameterMap& parameters)
    : impl_(new CqlHostDataSourceImpl(parameters)) {
}

CqlHostDataSource::~CqlHostDataSource() {
    delete impl_;
}

void
CqlHostDataSource::add(const HostPtr& host) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_HOST_ADD);

    impl_->add(host);
}

ConstHostCollection
CqlHostDataSource::getAll(const HWAddrPtr& hwaddr, const DuidPtr& duid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_HOST_GET_ALL);

    return impl_->getAll(hwaddr, duid);
}

ConstHostCollection
CqlHostDataSource::getAll(const Host::IdentifierType& identifier_type,
                          const uint8_t* identifier_begin,
                          const size_t identifier_len) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_HOST_GET_ALL);

    return impl_->getAll(identifier_type, identifier_begin, identifier_len);
}

ConstHostCollection
CqlHostDataSource::getAll4(const asiolink::IOAddress& address) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_HOST_GET_ALL);

    return impl_->getAll4(address);
}

ConstHostPtr
CqlHostDataSource::get4(const SubnetID& subnet_id,
                        const HWAddrPtr& hwaddr,
                        const DuidPtr& duid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_HOST_GET4);

    return impl_->get4(subnet_id, hwaddr, duid);
}

ConstHostPtr
CqlHostDataSource::get4(const SubnetID& subnet_id,
                        const Host::IdentifierType& identifier_type,
                        const uint8_t* identifier_begin,
                        const size_t identifier_len) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_HOST_GET4);

    return impl_->get4(subnet_id, identifier_type, identifier_begin,
                       identifier_len);
}

ConstHostPtr
CqlHostDataSource::get4(const SubnetID& subnet_id,
                        const asiolink::IOAddress& address) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_HOST_GET4);

    return impl_->get4(subnet_id, address);
}

ConstHostPtr
CqlHostDataSource::get6(const SubnetID& subnet_id,
                        const DuidPtr& duid,
                        const HWAddrPtr& hwaddr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_HOST_GET6);

    return impl_->get6(subnet_id, duid, hwaddr);
}

ConstHostPtr
CqlHostDataSource::get6(const SubnetID& subnet_id,
                        const Host::IdentifierType& identifier_type,
                        const uint8_t* identifier_begin,
                        const size_t identifier_len) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_HOST_GET6);

    return impl_->get6(subnet_id, identifier_type, identifier_begin,
                       identifier_len);
}

ConstHostPtr
CqlHostDataSource::get6(const asiolink::IOAddress& prefix,
                        const uint8_t prefix_len) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_HOST_GET6);

    return impl_->get6(prefix, prefix_len);
}

ConstHostPtr
CqlHostDataSource::get6(const SubnetID& subnet_id,
                        const asiolink::IOAddress& address) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_HOST_GET6);

    return impl_->get6(subnet_id, address);
}

std::string
CqlHostDataSource::getType() const {
    return std::string("cql");
}

std::string
CqlHostDataSource::getName() const {
    return impl_->getName();
}

std::string
CqlHostDataSource::getDescription() const {
    return std::string(
        "Host data source that stores host information in the CQL database");
}

VersionPair
CqlHostDataSource::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_HOST_DB_GET_VERSION);

    return impl_->getVersion();
}

void
CqlHostDataSource::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_COMMIT);

    impl_->commit();
}

void
CqlHostDataSource::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_ROLLBACK);

    impl_->rollback();
}

};  // namespace dhcp
};  // namespace isc
