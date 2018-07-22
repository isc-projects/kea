// Copyright (C) 2014-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_H
#define HOST_H

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <cc/user_context.h>
#include <dhcp/classify.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/subnet_id.h>
#include <boost/shared_ptr.hpp>
#include <list>
#include <map>
#include <string>
#include <utility>

namespace isc {
namespace dhcp {

/// @brief HostID (used only when storing in MySQL, PostgreSQL or Cassandra)
typedef uint64_t HostID;

/// @brief Authentication keys
/// 
/// This class represents authentication keys to be used for 
/// calculating HMAC in the authentication field of the recofigure message
class AuthKey {
public:
    /// @brief Length of the key - 128 bits
    const static uint8_t KEY_LEN = 16;

    /// @brief Constructor
    ///
    /// Constructor for assigning auth keys in host reservation
    ///  Ensures the key length is not greater than 16 bytes
    /// @param string auth key to be stored
    AuthKey(const std::string key);
    
    /// @brief Constructor
    ///
    /// Constructor for generating auth keys, with no argument
    /// shall use the internal function for generationg random keys
    AuthKey(void);

    // @brief get random string
    ///
    /// Random string is generated by default will be used for
    /// the keys to be used for signing Reconfigure Message.
    /// @return auth keys
    /// @todo Move randomization function to cryptolink
    static std::string getRandomKeyString();

    /// @brief set auth key value
    ///
    /// Set the key value.
    //  If the size is greater than 16 bytes, we resize to 16 Bytes
    /// Doesnt throw an exception
    /// @param string key to be stored
    void setAuthKey(const std::string& key);

    /// @brief return auth key
    ///
    /// @return auth key
    std::string getAuthKey() {
        return authKey_;
    }

    /// @brief return text format for keys
    ///
    /// Although returning member would have sufficed
    /// this is added incase in future authkey is no longer std::string
    std::string ToText() const; 

    /// 
    /// @brief equality operator
    ///
    /// equality operator to compare two AuthKey classes
    /// @param Authkey to be compared against
    bool operator==(const AuthKey& other) const;

    /// @brief inequality operator
    ///
    /// inequality operator to compare two AuthKey classes
    /// @param Authkey to be compared against
    bool operator!=(const AuthKey& other) const;

private:
    std::string authKey_;
};

/// @brief IPv6 reservation for a host.
///
/// This class represents a reservation for a host of a single IPv6
/// address or prefix (in @c Host object).
///
/// The class holds the address and prefix length, a value of 128
/// for the latter implying that the reservation is for a single
/// IPv6 address.
class IPv6Resrv {
public:

    /// @brief Type of the reservation.
    ///
    /// Currently supported types are NA and PD.
    enum Type {
        TYPE_NA,
        TYPE_PD
    };

    /// @brief Constructor.
    ///
    /// Creates a reservation from the IPv6 address and prefix length
    /// value. If the prefix length is not specified, the default value
    /// of 128 is used. This value indicates that the reservation is made
    /// for an IPv6 address.
    ///
    /// @param type Reservation type: NA or PD.
    /// @param prefix Address or prefix to be reserved.
    /// @param prefix_len Prefix length.
    ///
    /// @throw isc::BadValue if prefix is not IPv6 prefix, is a
    /// multicast address or the prefix length is greater than 128.
    IPv6Resrv(const Type& type,
              const asiolink::IOAddress& prefix,
              const uint8_t prefix_len = 128);

    /// @brief Returns prefix for the reservation.
    const asiolink::IOAddress& getPrefix() const {
        return (prefix_);
    }

    /// @brief Returns prefix length.
    uint8_t getPrefixLen() const {
        return (prefix_len_);
    }

    /// @brief Returns reservation type.
    ///
    /// The type of reservation is determined using a prefix length.
    ///
    /// @return NA for prefix length equal to 128, PD otherwise.
    Type getType() const {
        return (type_);
    }

    /// @brief Sets a new prefix and prefix length.
    ///
    /// @param type Reservation type: NA or PD.
    /// @param prefix New prefix.
    /// @param prefix_len New prefix length.
    ///
    /// @throw isc::BadValue if prefix is not IPv6 prefix, is a
    /// multicast address or the prefix length is greater than 128.
    void set(const Type& type, const asiolink::IOAddress& prefix,
             const uint8_t prefix_len);

    /// @brief Returns information about the reservation in the textual format.
    std::string toText() const;

    /// @brief Equality operator.
    ///
    /// @param other Reservation to compare to.
    bool operator==(const IPv6Resrv& other) const;

    /// @brief Inequality operator.
    ///
    /// @param other Reservation to compare to.
    bool operator!=(const IPv6Resrv& other) const;

private:

    Type type_;                  ///< Reservation type.
    asiolink::IOAddress prefix_; ///< Prefix
    uint8_t prefix_len_;         ///< Prefix length.
};

/// @brief Collection of IPv6 reservations for the host.
typedef std::multimap<IPv6Resrv::Type, IPv6Resrv> IPv6ResrvCollection;
typedef IPv6ResrvCollection::const_iterator IPv6ResrvIterator;
typedef std::pair<IPv6Resrv::Type, IPv6Resrv> IPv6ResrvTuple;
typedef std::pair<IPv6ResrvIterator, IPv6ResrvIterator> IPv6ResrvRange;

/// @brief Represents a device with IPv4 and/or IPv6 reservations.
///
/// This class represents a network device which can be identified
/// by a unique property, such as MAC address on the interface or
/// client identifier (DUID), and for which some resources are statically
/// assigned:
/// - IPv4 address which the device obtains when it contacts a DHCPv4 server
/// - IPv6 address(es) which the device obtains when it contacts a DHCPv6
/// server
/// - IPv6 prefix(es) obtained when the device contacts the DHCPv6 server
/// and requests allocation of prefixes using prefix delegation mechanism
/// - hostname which is used for dynamic DNS updates for both DHCPv4 and
/// DHCPv6 exchanges.
/// - client classes which the client is associated with
/// - DHCP options specifically configured for the device
///
/// Note, that "host" in this context has a different meaning from
/// host construed as device attached to a network with (possibly) multiple
/// interfaces. For the MAC address based reservations, each interface on a
/// network device maps to a single @c Host object as each @c Host object
/// contains at most one MAC address. So, it is possible that a single
/// device is associated with multiple distinct @c Host objects if the
/// device has multiple interfaces. Under normal circumstances, a non-mobile
/// dual stack device using one interface should be represented by a single
/// @c Host object.
///
/// A DHCPv6 DUID is common for all interfaces on a device. Therefore, for
/// DUID based reservations a @c Host object may represent a network device with
/// multiple interfaces. However, since @c Host objects are grouped by
/// subnets to which device's interfaces are connected a single instance of
/// @c Host object usually defines reservations for a single interface.
///
/// The @c Host object combines reservations for both IPv4 and IPv6 resources
/// to allow for correlation of the information about the dual stack devices
/// using DHCPv4 and DHCPv6 respectively. For example: both the DHCPv4 and
/// DHCPv6 servers may use the same database for storing host reservations, so
/// the information about the DHCPv4 reservations are available for the
/// DHCPv6 server and vice versa. Also, this approach allows for reserving
/// common resources such as host name for DHCPv4 and DHCPv6 clients.
///
/// This class also holds pointers to specific DHCP options reserved
/// for a host. Options instances are held in @c CfgOption objects.
/// There are two @c CfgOption objects in this class, one holding
/// DHCPv4 options, another one holding DHCPv6 options.
///
/// @todo This class offers basic functionality for storing host information.
/// It will need to be extended to allow for the following operations:
/// - remove and replace IPv6 reservations
/// - remove and replace client classes
/// - disable IPv4 reservation without a need to set it to the 0.0.0.0 address
/// Note that the last three operations are mainly required for managing
/// host reservations which will be implemented later.
class Host : public UserContext {
public:

    /// @brief Type of the host identifier.
    ///
    /// Currently supported identifiers are:
    /// - hardware address (DHCPv4 and DHCPv6) (identifier name: "hw-address"),
    /// - DUID (DHCPv4 and DHCPv6) (identifier name: "duid"),
    /// - circuit identifier (DHCPv4) (identifier name: "circuit-id"),
    /// - client identifier (DHCPv4) (identifier name: "client-id")
    enum IdentifierType {
        IDENT_HWADDR,
        IDENT_DUID,
        IDENT_CIRCUIT_ID,
        IDENT_CLIENT_ID,
        IDENT_FLEX, ///< Flexible host identifier.
    };

    /// @brief Constant pointing to the last identifier of the
    /// @ref IdentifierType enumeration.
    static const IdentifierType LAST_IDENTIFIER_TYPE = IDENT_FLEX;

    /// @brief Constructor.
    ///
    /// Creates a @c Host object using an identifier in a binary format. This
    /// is most useful in cases where the identifier is obtained from the
    /// database. The constructor will create an instance of the @c HWAddr
    /// or @c DUID object depending on the identifier type.
    ///
    /// @param identifier Pointer to the binary value holding an identifier.
    /// @param identifier_len Length of the identifier.
    /// @param identifier_type Type of the identifier (hardware address or
    /// DUID).
    /// @param ipv4_subnet_id Identifier of the IPv4 subnet to which the host
    /// is connected.
    /// @param ipv6_subnet_id Identifier of the IPv6 subnet to which the host
    /// is connected.
    /// @param ipv4_reservation An IPv4 address reserved for the client. If
    /// this address is set to 0, there is no reservation.
    /// @param hostname Hostname to be allocated to both DHCPv4 and DHCPv6
    /// clients. This is empty string if hostname is not allocated.
    /// @param dhcp4_client_classes A string holding DHCPv4 client class names
    /// separated by commas. The names get trimmed by this constructor.
    /// @param dhcp6_client_classes A string holding DHCPv6 client class names
    /// separated by commas. The names get trimmed by this constructor.
    /// @param next_server IPv4 address of next server (siaddr).
    /// @param server_host_name Server host name (a.k.a. sname).
    /// @param boot_file_name Boot file name (a.k.a. file).
    ///
    /// @throw BadValue if the provided values are invalid. In particular,
    /// if the identifier is invalid.
    Host(const uint8_t* identifier, const size_t identifier_len,
         const IdentifierType& identifier_type,
         const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
         const asiolink::IOAddress& ipv4_reservation,
         const std::string& hostname = "",
         const std::string& dhcp4_client_classes = "",
         const std::string& dhcp6_client_classes = "",
         const asiolink::IOAddress& next_server = asiolink::IOAddress::IPV4_ZERO_ADDRESS(),
         const std::string& server_host_name = "",
         const std::string& boot_file_name = "",
         const AuthKey& auth_key = std::string(""));

    /// @brief Constructor.
    ///
    /// Creates @c Host object using an identifier in a textual format. This
    /// is useful in cases when the reservation is specified in the server
    /// configuration file. Identifiers can be specified in the following
    /// formats:
    /// - "yy:yy:yy:yy:yy:yy"
    /// - "yyyyyyyyyy",
    /// - "0xyyyyyyyyyy",
    /// - "'some identifier'".
    /// where y is a hexadecimal digit.
    ///
    /// Note that it is possible to use textual representation, e.g. 'some identifier',
    /// which is converted to a vector of ASCII codes representing characters in a
    /// given string, excluding quotes. This is useful in cases when specific
    /// identifiers, e.g. circuit-id are manually assigned user friendly values.
    ///
    /// @param identifier Identifier in the textual format. The expected formats
    /// for the hardware address and other identifiers are provided above.
    /// @param identifier_name One of the supported identifiers in the text form as
    /// described for @ref IdentifierType.
    /// @param ipv4_subnet_id Identifier of the IPv4 subnet to which the host
    /// is connected.
    /// @param ipv6_subnet_id Identifier of the IPv6 subnet to which the host
    /// is connected.
    /// @param ipv4_reservation An IPv4 address reserved for the client. If
    /// this address is set to 0, there is no reservation.
    /// @param hostname Hostname to be allocated to both DHCPv4 and DHCPv6
    /// clients. This is empty string if hostname is not allocated.
    /// @param dhcp4_client_classes A string holding DHCPv4 client class names
    /// separated by commas. The names get trimmed by this constructor.
    /// @param dhcp6_client_classes A string holding DHCPv6 client class names
    /// separated by commas. The names get trimmed by this constructor.
    /// @param next_server IPv4 address of next server (siaddr).
    /// @param server_host_name Server host name (a.k.a. sname).
    /// @param boot_file_name Boot file name (a.k.a. file).
    ///
    /// @throw BadValue if the provided values are invalid. In particular,
    /// if the identifier is invalid.
    Host(const std::string& identifier, const std::string& identifier_name,
         const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
         const asiolink::IOAddress& ipv4_reservation,
         const std::string& hostname = "",
         const std::string& dhcp4_client_classes = "",
         const std::string& dhcp6_client_classes = "",
         const asiolink::IOAddress& next_server = asiolink::IOAddress::IPV4_ZERO_ADDRESS(),
         const std::string& server_host_name = "",
         const std::string& boot_file_name = "",
         const AuthKey& auth_key = std::string(""));

    /// @brief Replaces currently used identifier with a new identifier.
    ///
    /// This method sets a new identifier type and value for a host.
    /// This method is called by the @c Host constructor.
    ///
    /// @param identifier Pointer to a buffer holding an identifier.
    /// @param len Length of the identifier that the @c identifier points to.
    /// @param type Identifier type.
    ///
    /// @throw BadValue if the identifier is invalid.
    void setIdentifier(const uint8_t* identifier, const size_t len,
                       const IdentifierType& type);

    /// @brief Replaces currently used identifier with a new identifier.
    ///
    /// This method sets a new identifier type and value for a host.
    /// This method is called by the @c Host constructor.
    ///
    /// @param identifier Reference to a new identifier in the textual format.
    /// @param name One of the supported identifiers in the text form as
    /// described for @ref IdentifierType.
    ///
    /// @throw BadValue if the identifier is invalid.
    void setIdentifier(const std::string& identifier, const std::string& name);

    /// @brief Returns hardware address for which the reservations are made.
    ///
    /// @return Pointer to the @c HWAddr structure or null if the reservation
    /// is not associated with a hardware address.
    HWAddrPtr getHWAddress() const;

    /// @brief Returns DUID for which the reservations are made.
    ///
    /// @return Pointer to the @c DUID structure or null if the reservation
    /// is not associated with a DUID.
    DuidPtr getDuid() const;

    /// @brief Returns the identifier in a binary form.
    ///
    /// @return const reference to a vector<uint8_t> holding an identifier
    /// value.
    const std::vector<uint8_t>& getIdentifier() const;

    /// @brief Returns the identifier type.
    ///
    IdentifierType getIdentifierType() const;

    /// @brief Converts identifier name to identifier type.
    ///
    /// @param identifier_name Identifier name.
    /// @return Identifier type.
    static IdentifierType getIdentifierType(const std::string& identifier_name);

    /// @brief Returns host identifier in a textual form.
    ///
    /// @return Identifier in the form of type=value.
    std::string getIdentifierAsText() const;

    /// @brief Returns name of the identifier of a specified type.
    static std::string getIdentifierName(const IdentifierType& type);

    /// @brief Returns host identifier in textual form.
    ///
    /// @param type Identifier type.
    /// @param value Pointer to a buffer holding identifier.
    /// @param length Length of the identifier.
    /// @return Identifier in the form of type=value.
    static std::string getIdentifierAsText(const IdentifierType& type,
                                           const uint8_t* value,
                                           const size_t length);

    /// @brief Sets new IPv4 subnet identifier.
    ///
    /// @param ipv4_subnet_id New subnet identifier.
    void setIPv4SubnetID(const SubnetID ipv4_subnet_id) {
        ipv4_subnet_id_ = ipv4_subnet_id;
    }

    /// @brief Sets new IPv6 subnet identifier.
    ///
    /// @param ipv6_subnet_id New subnet identifier.
    void setIPv6SubnetID(const SubnetID ipv6_subnet_id) {
        ipv6_subnet_id_ = ipv6_subnet_id;
    }

    /// @brief Returns subnet identifier for IPv4 reservation.
    SubnetID getIPv4SubnetID() const {
        return (ipv4_subnet_id_);
    }

    /// @brief Returns subnet identifier for IPv6 reservations.
    SubnetID getIPv6SubnetID() const {
        return (ipv6_subnet_id_);
    }

    /// @brief Sets new IPv4 reservation.
    ///
    /// The new reservation removes a previous reservation.
    ///
    /// @param address Address to be reserved for the client.
    ///
    /// @throw isc::BadValue if the provided address is not an IPv4 address,
    /// is a 0 address or broadcast address.
    void setIPv4Reservation(const asiolink::IOAddress& address);

    /// @brief Removes the IPv4 reservation.
    ///
    /// Sets the IPv4 reserved address to 0.
    void removeIPv4Reservation();

    /// @brief Returns reserved IPv4 address.
    ///
    /// @return IPv4 address or 0.0.0.0 if no IPv4 reservation specified.
    const asiolink::IOAddress& getIPv4Reservation() const {
        return (ipv4_reservation_);
    }

    /// @brief Adds new IPv6 reservation.
    ///
    /// @param reservation New IPv6 reservation to be appended.
    void addReservation(const IPv6Resrv& reservation);

    /// @brief Returns IPv6 reservations of a specified type.
    ///
    /// @param type Type of the reservations to be returned (NA or PD).
    ///
    /// @return A range of iterators pointing to the reservations of
    /// the specified type.
    IPv6ResrvRange getIPv6Reservations(const IPv6Resrv::Type& type) const;

    /// @brief Returns all IPv6 reservations.
    ///
    /// @return A range of iterators pointing to the reservations of
    /// the specified type.
    IPv6ResrvRange getIPv6Reservations() const;

    /// @brief Checks if there is at least one IPv6 reservation for this host.
    ///
    /// @return true if there is a reservation for the host, false otherwise.
    bool hasIPv6Reservation() const;

    /// @brief Checks if specified IPv6 reservation exists for the host.
    ///
    /// @param reservation A reservation to be checked for the host.
    ///
    /// @return true if the reservation already exists for the host, false
    /// otherwise.
    bool hasReservation(const IPv6Resrv& reservation) const;

    /// @brief Sets new hostname.
    ///
    /// @param hostname New hostname.
    void setHostname(const std::string& hostname) {
        hostname_ = hostname;
    }

    /// @brief Returns reserved hostname.
    const std::string& getHostname() const {
        return (hostname_);
    }

    /// @brief Adds new client class for DHCPv4.
    ///
    /// @param class_name Class name.
    void addClientClass4(const std::string& class_name);

    /// @brief Returns classes which DHCPv4 client is associated with.
    const ClientClasses& getClientClasses4() const {
        return (dhcp4_client_classes_);
    }

    /// @brief Adds new client class for DHCPv6.
    ///
    /// @param class_name Class name.
    void addClientClass6(const std::string& class_name);

    /// @brief Returns classes which DHCPv6 client is associated with.
    const ClientClasses& getClientClasses6() const {
        return (dhcp6_client_classes_);
    }

    /// @brief Sets new value for next server field (siaddr).
    ///
    /// @param next_server New address of a next server.
    ///
    /// @throw isc::BadValue if the provided address is not an IPv4 address,
    /// is broadcast address.
    void setNextServer(const asiolink::IOAddress& next_server);

    /// @brief Returns value of next server field (siaddr).
    const asiolink::IOAddress& getNextServer() const {
        return (next_server_);
    }

    /// @brief Sets new value for server hostname (sname).
    ///
    /// @param server_host_name New value for server hostname.
    ///
    /// @throw BadValue if hostname is longer than 63 bytes.
    void setServerHostname(const std::string& server_host_name);

    /// @brief Returns value of server hostname (sname).
    const std::string& getServerHostname() const {
        return (server_host_name_);
    }

    /// @brief Sets new value for boot file name (file).
    ///
    /// @param boot_file_name New value of boot file name.
    ///
    /// @throw BadValue if boot file name is longer than 128 bytes.
    void setBootFileName(const std::string& boot_file_name);

    /// @brief Returns value of boot file name (file).
    const std::string& getBootFileName() const {
        return (boot_file_name_);
    }

    /// @brief Returns pointer to the DHCPv4 option data configuration for
    /// this host.
    ///
    /// Returned pointer can be used to add, remove and update options
    /// reserved for a host.
    CfgOptionPtr getCfgOption4() {
        return (cfg_option4_);
    }

    /// @brief Returns const pointer to the DHCPv4 option data configuration for
    /// this host.
    ConstCfgOptionPtr getCfgOption4() const {
        return (cfg_option4_);
    }

    /// @brief Returns pointer to the DHCPv6 option data configuration for
    /// this host.
    ///
    /// Returned pointer can be used to add, remove and update options
    /// reserved for a host.
    CfgOptionPtr getCfgOption6() {
        return (cfg_option6_);
    }

    /// @brief Returns const pointer to the DHCPv6 option data configuration for
    /// this host.
    ConstCfgOptionPtr getCfgOption6() const {
        return (cfg_option6_);
    }

    /// @brief Returns information about the host in the textual format.
    std::string toText() const;

    /// @brief Sets Host ID (primary key in MySQL, PostgreSQL and Cassandra backends)
    /// @param id HostId value
    void setHostId(HostID id) {
        host_id_ = id;
    }

    /// @brief Returns Host ID (primary key in MySQL, PostgreSQL and Cassandra backends)
    /// @return id HostId value (or 0 if not set)
    HostID getHostId() const {
        return (host_id_);
    }

    /// @brief Sets the negative cached flag.
    ///
    /// @param negative sets whether this is a negative cached host,
    /// i.e. a fake host in the cache which indicates non-existence
    /// and avoids to lookup in a slow backend.
    void setNegative(bool negative) {
        negative_ = negative;
    }

    /// @brief Return the negative cache flag value.
    /// When true standard lookup methods return null host pointer instead.
    bool getNegative() const {
        return (negative_);
    }

    /// @brief Unparses (converts to Element representation) IPv4 host
    ///
    /// @return Element representation of the host
    isc::data::ElementPtr toElement4() const;

    /// @brief Unparses (converts to Element representation) IPv6 host
    ///
    /// @return Element representation of the host
    isc::data::ElementPtr toElement6() const;
    
    /// @brief sets key.
    ///
    /// Keys are used for signing the Reconfigure Message.
    void setKey(const AuthKey& key) {
        key_ = key;
    }
    
    /// @brief Returns the key.
    ///
    /// Keys are used for signing the Reconfigure Message.
    AuthKey getKey() const {
        return(key_);
    }

private:

    /// @brief Adds new client class for DHCPv4 or DHCPv6.
    ///
    /// This method is called internally by the @c addClientClass4 and
    /// @c addClientClass6 functions. It adds the class of the specified name
    /// to the supplied class set. The class names are trimmed before they are
    /// added. Empty class names are ignored.
    ///
    /// @param [out] classes Set of classes to which the new class should be
    /// inserted.
    /// @param class_name Class name.
    void addClientClassInternal(ClientClasses& classes,
                                const std::string& class_name);

    /// @brief Identifier type.
    IdentifierType identifier_type_;
    /// @brief Vector holding identifier value.
    std::vector<uint8_t> identifier_value_;
    /// @brief Subnet identifier for the DHCPv4 client.
    SubnetID ipv4_subnet_id_;
    /// @brief Subnet identifier for the DHCPv6 client.
    SubnetID ipv6_subnet_id_;
    /// @brief Reserved IPv4 address.
    asiolink::IOAddress ipv4_reservation_;
    /// @brief Collection of IPv6 reservations for the host.
    IPv6ResrvCollection ipv6_reservations_;
    /// @brief Name reserved for the host.
    std::string hostname_;
    /// @brief Collection of classes associated with a DHCPv4 client.
    ClientClasses dhcp4_client_classes_;
    /// @brief Collection of classes associated with a DHCPv6 client.
    ClientClasses dhcp6_client_classes_;
    /// @brief Next server (a.k.a. siaddr, carried in DHCPv4 message).
    asiolink::IOAddress next_server_;
    /// @brief Server host name (a.k.a. sname, carried in DHCPv4 message).
    std::string server_host_name_;
    /// @brief Boot file name (a.k.a. file, carried in DHCPv4 message)
    std::string boot_file_name_;

    /// @brief HostID (a unique identifier assigned when the host is stored in
    ///     MySQL, PostgreSQL or Cassandra)
    uint64_t host_id_;

    /// @brief Pointer to the DHCPv4 option data configuration for this host.
    CfgOptionPtr cfg_option4_;
    /// @brief Pointer to the DHCPv6 option data configuration for this host.
    CfgOptionPtr cfg_option6_;

    /// @brief Negative cached flag.
    ///
    /// This flag determines whether this object is a negative cache, i.e.
    /// we queried other backends for specific host and there was no
    /// entry for it.
    bool negative_;

    /// @brief key for authentication .
    ///
    /// key is a 16 byte value to be used in the authentication field.
    /// Server replies will contain the below key in authentication field as specified in the RFC 3315bis. 
    //  While sending reconfigure message authentication field 
    /// shall contain MD5 hash computed using this key.
    AuthKey key_;
};

/// @brief Pointer to the @c Host object.
typedef boost::shared_ptr<Host> HostPtr;

/// @brief Const pointer to the @c Host object.
typedef boost::shared_ptr<const Host> ConstHostPtr;

/// @brief Collection of the const Host objects.
typedef std::vector<ConstHostPtr> ConstHostCollection;

/// @brief Collection of the @c Host objects.
typedef std::vector<HostPtr> HostCollection;

}
}

#endif // HOST_H
