// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef HOST_H
#define HOST_H

#include <asiolink/io_address.h>
#include <dhcp/classify.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/subnet_id.h>
#include <util/ntp_utils.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <list>
#include <map>
#include <string>
#include <utility>

namespace isc {
namespace dhcp {

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
/// - filename of public key or certificate of the client for
/// secure DHCPv6.
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
/// @todo This class offers basic functionality for storing host information.
/// It will need to be extended to allow for the following operations:
/// - store DHCPv4 and DHCPv6 options for the host,
/// - remove and replace IPv6 reservations
/// - remove and replace client classes
/// - disable IPv4 reservation without a need to set it to the 0.0.0.0 address
/// - implement Trust-on-first-use for secure DHCPv6
/// Note that the last three operations are mainly required for managing
/// host reservations which will be implemented later.
class Host {
public:

    /// @brief Type of the host identifier.
    ///
    /// Currently hardware address assigned to an interface and the
    /// DHCPv6 client's DUID are supported.
    enum IdentifierType {
        IDENT_HWADDR,
        IDENT_DUID
    };

    /// @brief Temporary state structure
    ///
    /// The extend (aka lifetime) of the temporary state is the same
    /// than for the host reservation object.
    struct TmpState {
        /// @brief Date of the last received and accepted packet
        isc::util::Ntp rd_last_;
        /// @brief Date of the last received and accepted timestamp
        isc::util::Ntp ts_last_;
    };

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
    ///
    /// @throw BadValue if the provided values are invalid. In particular,
    /// if the identifier is invalid.
    Host(const uint8_t* identifier, const size_t identifier_len,
         const IdentifierType& identifier_type,
         const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
         const asiolink::IOAddress& ipv4_reservation,
         const std::string& hostname = "",
         const std::string& dhcp4_client_classes = "",
         const std::string& dhcp6_client_classes = "");

    /// @brief Constructor.
    ///
    /// Creates @c Host object using an identifier in a textual format. This
    /// is useful in cases when the reservation is specified in the server
    /// configuration file, where:
    /// - MAC address is specified as: "01:02:03:04:05:06"
    /// - DUID is specified as: "010203040506abcd"
    ///
    /// @param identifier Identifier in the textual format. The expected formats
    /// for the hardware address and DUID have been shown above.
    /// @param identifier_name One of "hw-address" or "duid"
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
    ///
    /// @throw BadValue if the provided values are invalid. In particular,
    /// if the identifier is invalid.
    Host(const std::string& identifier, const std::string& identifier_name,
         const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
         const asiolink::IOAddress& ipv4_reservation,
         const std::string& hostname = "",
         const std::string& dhcp4_client_classes = "",
         const std::string& dhcp6_client_classes = "");

    /// @brief Replaces currently used identifier with a new identifier.
    ///
    /// This method initializes hardware address or DUID (@c hw_address_ or
    /// @c duid_ respectively). The other (not initialized member) is
    /// deallocated.
    ///
    /// This method is called by the @c Host constructor.
    ///
    /// @param identifier Pointer to the new identifier in the textual format.
    /// @param len Length of the identifier that the @c identifier points to.
    /// @param type Identifier type.
    ///
    /// @throw BadValue if the identifier is invalid.
    void setIdentifier(const uint8_t* identifier, const size_t len,
                       const IdentifierType& type);

    /// @brief Replaces currently used identifier with a new identifier.
    ///
    /// This method initializes hardware address or DUID (@c hw_address_ or
    /// @c duid_ respectively). The other (not initialized member) is
    /// deallocated.
    ///
    /// This method is called by the @c Host constructor.
    ///
    /// @param identifier Pointer to the new identifier in the textual format.
    /// @param name One of "hw-address" or "duid".
    ///
    /// @throw BadValue if the identifier is invalid.
    void setIdentifier(const std::string& identifier, const std::string& name);

    /// @brief Returns hardware address for which the reservations are made.
    ///
    /// @return Pointer to the @c HWAddr structure or null if the reservation
    /// is not associated with a hardware address.
    HWAddrPtr getHWAddress() const {
        return (hw_address_);
    }

    /// @brief Returns DUID for which the reservations are made.
    ///
    /// @return Pointer to the @c DUID structure or null if the reservation
    /// is not associated with a DUID.
    DuidPtr getDuid() const {
        return (duid_);
    }

    /// @brief Returns the identifier (MAC or DUID) in binary form.
    /// @return const reference to MAC or DUID in vector<uint8_t> form
    const std::vector<uint8_t>& getIdentifier() const;

    /// @brief Returns the identifier type.
    /// @return the identifier type
    IdentifierType getIdentifierType() const;

    /// @brief Returns host identifier (mac or DUID) in printer friendly form.
    /// @return text form of the identifier, including (duid= or mac=).
    std::string getIdentifierAsText() const;

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

    /// @brief Sets new credential (public key or certificate)
    ///
    /// @param filename New filename to the public key or certificate.
    void setCredential(const std::string& filename) {
        credential_ = filename;
    }

    /// @brief Returns credential
    const std::string& getCredential() const {
        return (credential_);
    }

    /// @brief Sets the date of the last received and accepted packet
    ///
    /// @param timestamp Date in NTP format
    void setRDlast(const isc::util::Ntp& timestamp) const {
        tmp_state_->rd_last_ = timestamp;
    }

    /// @brief Returns the date of the last received and accepted packet
    const isc::util::Ntp& getRDlast() const {
        return (tmp_state_->rd_last_);
    }

    /// @brief Sets the date from the last received and accepted packet
    ///
    /// @param timestamp Date in NTP format
    void setTSlast(const isc::util::Ntp& timestamp) const {
        tmp_state_->ts_last_ = timestamp;
    }

    /// @brief Returns the date from the last received and accepted packet
    const isc::util::Ntp& getTSlast() const {
        return (tmp_state_->ts_last_);
    }

    /// @brief Returns information about the host in the textual format.
    std::string toText() const;

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

    /// @brief Pointer to the hardware address associated with the reservations
    /// for the host.
    HWAddrPtr hw_address_;
    /// @brief Pointer to the DUID associated with the reservations for the
    /// host.
    DuidPtr duid_;
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
    /// @brief Credential (filename of public key or certificate)
    std::string credential_;
    /// @brief Smart pointer to the temporary state
    boost::scoped_ptr<TmpState> tmp_state_;
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
