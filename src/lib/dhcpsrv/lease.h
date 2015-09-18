// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef LEASE_H
#define LEASE_H

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/option.h>
#include <dhcp/hwaddr.h>

namespace isc {
namespace dhcp {

/// @brief Unique identifier for a subnet (both v4 and v6)
///
/// Let's copy SubnetID definition from subnet.h. We can't include it directly,
/// because subnet.h needs Lease::Type, so it includes lease.h
typedef uint32_t SubnetID;

/// @brief a common structure for IPv4 and IPv6 leases
///
/// This structure holds all information that is common between IPv4 and IPv6
/// leases.
struct Lease {

    /// @brief Type of lease or pool
    typedef enum {
        TYPE_NA = 0, /// the lease contains non-temporary IPv6 address
        TYPE_TA = 1, /// the lease contains temporary IPv6 address
        TYPE_PD = 2, /// the lease contains IPv6 prefix (for prefix delegation)
        TYPE_V4 = 3  /// IPv4 lease
    } Type;

    /// @brief returns text representation of a lease type
    /// @param type lease or pool type to be converted
    /// @return text decription
    static std::string typeToText(Type type);

    /// @name Common lease states constants.
    //@{
    ///
    /// @brief A lease in the default state.
    static const uint32_t STATE_DEFAULT;

    /// @brief Declined lease.
    static const uint32_t STATE_DECLINED;

    /// @brief Expired and reclaimed lease.
    static const uint32_t STATE_EXPIRED_RECLAIMED;

    //@}

    /// @brief Returns name(s) of the basic lease state(s).
    ///
    /// @param state A numeric value holding a state information.
    /// Some states may be composite, i.e. the single state value
    /// maps to multiple logical states of the lease.
    ///
    /// @return Comma separated list of state names.
    static std::string basicStatesToText(const uint32_t state);

    /// @brief Constructor
    ///
    /// @param addr IP address
    /// @param t1 renewal time
    /// @param t2 rebinding time
    /// @param valid_lft Lifetime of the lease
    /// @param subnet_id Subnet identification
    /// @param cltt Client last transmission time
    /// @param fqdn_fwd If true, forward DNS update is performed for a lease.
    /// @param fqdn_rev If true, reverse DNS update is performed for a lease.
    /// @param hostname FQDN of the client which gets the lease.
    /// @param hwaddr Hardware/MAC address
    Lease(const isc::asiolink::IOAddress& addr, uint32_t t1, uint32_t t2,
          uint32_t valid_lft, SubnetID subnet_id, time_t cltt,
          const bool fqdn_fwd, const bool fqdn_rev,
          const std::string& hostname,
          const HWAddrPtr& hwaddr);

    /// @brief Destructor
    virtual ~Lease() {}

    /// @brief IPv4 ot IPv6 address
    ///
    /// IPv4, IPv6 address or, in the case of a prefix delegation, the prefix.
    isc::asiolink::IOAddress addr_;

    /// @brief Renewal timer
    ///
    /// Specifies renewal time. Although technically it is a property of the
    /// IA container and not the address itself, since our data model does not
    /// define a separate IA entity, we are keeping it in the lease. In the
    /// case of multiple addresses/prefixes for the same IA, each must have
    /// consistent T1 and T2 values. This is specified in seconds since cltt.
    uint32_t t1_;

    /// @brief Rebinding timer
    ///
    /// Specifies rebinding time. Although technically it is a property of the
    /// IA container and not the address itself, since our data model does not
    /// define a separate IA entity, we are keeping it in the lease. In the
    /// case of multiple addresses/prefixes for the same IA, each must have
    /// consistent T1 and T2 values. This is specified in seconds since cltt.
    uint32_t t2_;

    /// @brief Valid lifetime
    ///
    /// Expressed as number of seconds since cltt.
    uint32_t valid_lft_;

    /// @brief Client last transmission time
    ///
    /// Specifies a timestamp giving the time when the last transmission from a
    /// client was received.
    time_t cltt_;

    /// @brief Subnet identifier
    ///
    /// Specifies the identification of the subnet to which the lease belongs.
    SubnetID subnet_id_;

    /// @brief Client hostname
    ///
    /// This field may be empty
    std::string hostname_;

    /// @brief Forward zone updated?
    ///
    /// Set true if the DNS AAAA record for this lease has been updated.
    bool fqdn_fwd_;

    /// @brief Reverse zone updated?
    ///
    /// Set true if the DNS PTR record for this lease has been updated.
    bool fqdn_rev_;

    /// @brief Client's MAC/hardware address
    ///
    /// This information may not be available in certain cases.
    HWAddrPtr hwaddr_;

    /// @brief Holds the lease state(s).
    ///
    /// This is the field that holds the lease state(s). Typically, a
    /// lease remains in a single states. However, it is posible to
    /// define a value for state which indicates that the lease remains
    /// in multiple logical states.
    ///
    /// The defined states are represented by the "STATE_*" constants
    /// belonging to this class.
    uint32_t state_;

    /// @brief Convert Lease to Printable Form
    ///
    /// @return String form of the lease
    virtual std::string toText() const = 0;

    /// @brief returns true if the lease is expired
    /// @return true if the lease is expired
    bool expired() const;

    /// @brief Indicates if the lease is in the "expired-reclaimed" state.
    ///
    /// @return true if the lease is in the "expired-reclaimed" state, false
    /// otherwise.
    bool stateExpiredReclaimed() const;

    /// @brief Returns true if the other lease has equal FQDN data.
    ///
    /// @param other Lease which FQDN data is to be compared with our lease.
    ///
    /// @return Boolean value which indicates whether FQDN data of the other
    /// lease is equal to the FQDN data of our lease (true) or not (false).
    bool hasIdenticalFqdn(const Lease& other) const;

    /// @brief Returns raw (as vector) hardware address
    ///
    /// This method is needed in multi-index container as key extractor.
    /// The const reference is only valid as long as the object that returned it.
    /// In the unlikely case when Lease4 does not have a hardware address,
    /// the function will return an empty vector.
    ///
    /// @return const reference to the hardware address
    const std::vector<uint8_t>& getHWAddrVector() const;

    /// @brief Returns lease expiration time.
    ///
    /// The lease expiration time is a sum of a client last transmission time
    /// and valid lifetime.
    int64_t getExpirationTime() const;

    /// @brief Sets lease to DECLINED state.
    ///
    /// All client identifying parameters will be stripped off (HWaddr,
    /// client_id, hostname), timers set to 0 (t1, t2), cltt will be set
    /// to current time and valid_lft to parameter specified as probation
    /// period. Note that This method only sets fields in the structure.
    /// It is caller's responsibility to clean up DDNS, bump up stats,
    /// log, call hooks ets.
    ///
    /// @param probation_period lease lifetime will be set to this value
    virtual void decline(uint32_t probation_period) = 0;
};

/// @brief Structure that holds a lease for IPv4 address
///
/// For performance reasons it is a simple structure, not a class. If we chose
/// make it a class, all fields would have to made private and getters/setters
/// would be required. As this is a critical part of the code that will be used
/// extensively, direct access is warranted.
struct Lease4 : public Lease {

    /// @brief Client identifier
    ///
    /// @todo Should this be a pointer to a client ID or the ID itself?
    ///       Compare with the DUID in the Lease6 structure.
    ClientIdPtr client_id_;

    /// @brief Constructor
    ///
    /// @param addr IPv4 address.
    /// @param hwaddr A pointer to HWAddr structure
    /// @param clientid Client identification buffer
    /// @param clientid_len Length of client identification buffer
    /// @param valid_lft Lifetime of the lease
    /// @param t1 renewal time
    /// @param t2 rebinding time
    /// @param cltt Client last transmission time
    /// @param subnet_id Subnet identification
    /// @param fqdn_fwd If true, forward DNS update is performed for a lease.
    /// @param fqdn_rev If true, reverse DNS update is performed for a lease.
    /// @param hostname FQDN of the client which gets the lease.
    Lease4(const isc::asiolink::IOAddress& addr, const HWAddrPtr& hwaddr,
           const uint8_t* clientid, size_t clientid_len, uint32_t valid_lft,
           uint32_t t1, uint32_t t2, time_t cltt, uint32_t subnet_id,
           const bool fqdn_fwd = false, const bool fqdn_rev = false,
           const std::string& hostname = "")
        : Lease(addr, t1, t2, valid_lft, subnet_id, cltt, fqdn_fwd, fqdn_rev,
                hostname, hwaddr) {
        if (clientid_len) {
            client_id_.reset(new ClientId(clientid, clientid_len));
        }
    }

    /// @brief Constructor.
    ///
    /// @param address IPv4 address.
    /// @param hw_address Pointer to client's HW addresss.
    /// @param client_id  pointer to the client id structure.
    /// @param valid_lifetime Valid lifetime value.
    /// @param t1 Renew timer.
    /// @param t2 Rebind timer.
    /// @param cltt Timestamp when the lease is acquired, renewed.
    /// @param subnet_id Subnet identifier.
    /// @param fqdn_fwd Forward DNS update performed.
    /// @param fqdn_rev Reverse DNS update performed.
    /// @param hostname Client's name for the DNS update..
    Lease4(const isc::asiolink::IOAddress& address,
           const HWAddrPtr& hw_address,
           const ClientIdPtr& client_id,
           const uint32_t valid_lifetime,
           const uint32_t t1,
           const uint32_t t2,
           const time_t cltt,
           const SubnetID subnet_id,
           const bool fqdn_fwd = false,
           const bool fqdn_rev = false,
           const std::string& hostname = "");


    /// @brief Default constructor
    ///
    /// Initialize fields that don't have a default constructor.
    Lease4() : Lease(0, 0, 0, 0, 0, 0, false, false, "", HWAddrPtr())
    {
    }

    /// @brief Copy constructor
    ///
    /// @param other the @c Lease4 object to be copied.
    Lease4(const Lease4& other);

    /// @brief Returns name of the lease states specific to DHCPv4.
    ///
    /// @todo Currently it simply returns common states for DHCPv4 and DHCPv6.
    /// This method will have to be extended to handle DHCPv4 specific states
    /// when they are defined.
    ///
    /// @param state Numeric value holding lease states.
    /// @return Comma separated list of lease state names.
    static std::string statesToText(const uint32_t state);

    /// @brief Returns a client identifier.
    ///
    /// @warning Since the function returns the reference to a vector (not a
    /// copy), the returned object should be used with caution because it will
    /// remain valid only for the period of time when an object which returned
    /// it exists.
    ///
    /// @return A reference to a vector holding client identifier,
    /// or an empty vector if client identifier is NULL.
    const std::vector<uint8_t>& getClientIdVector() const;

    /// @brief Check if the lease belongs to the client with the given
    /// identifiers.
    ///
    /// This method checks if the lease belongs to the client using the
    /// specified HW address and/or client identifier. Note that any of the
    /// pointers passed to this method may be set to null, in which case
    /// they are treated as unspecified and are not used for matching the
    /// client with the lease.
    ///
    /// According to the DHCPv4 specifications, the client identifier takes
    /// precedence over the HW address when identifying the lease for the
    /// client on the server side. In particular, the RFC4361 introduces the
    /// use of DUID for DHCPv4 which should be a stable identifier for the
    /// client. The use of stable identifier allows for the correlation of the
    /// DHCPv4 and DHCPv6 clients in the dual stack networks. It also allows
    /// for allocating the same lease to the client which hardware (and thus
    /// MAC address) has changed.
    ///
    /// By default, Kea respects the precedence of the client identifier over
    /// MAC address and when this method finds the match of the client
    /// identifier with the client identifier stored in the lease, it will
    /// treat the lease as the lease of this client, even when the HW
    /// address doesn't match.
    ///
    /// The HW address is used for matching the client with the lease only
    /// when the lease is not associated with any client identifier (client
    /// identifier for the lease is null) or when the client identifier
    /// parameter passed to this method is null. This facilitates the following
    /// cases:
    /// - client didn't generate client identifier and is only using the chaddr
    ///   field to identify itself.
    /// - server's administrator configured the server to NOT match client
    ///   identifiers, the client obtained the new lease, and the administrator
    ///   reconfigured the server to match the client identifiers. The client
    ///   is trying to renew its lease and both the client identifier and HW
    ///   address is used for matching the lease which doesn't have the record
    ///   of the client identifier.
    /// - client obtained the lease using the HW address and client identifier,
    ///   the server's administrator configured the server to NOT match the
    ///   client identifiers, and the client returns to renew the lease. This
    ///   time, the lease has a record of both client identifier and the HW
    ///   address but only the HW address is used for matching the client to
    ///   the lease.
    ///
    /// Note that the typical case when the server's administrator may want to
    /// disable matching the client identifier passed in the client's message
    /// is when the client is performing multi-stage boot. In such case, the
    /// client identifiers may change on various stages of the boot, but the
    /// HW address will remain stable. The server's administrator prefers
    /// using the HW address for client identification in this case.
    ///
    /// It may also be useful to disable matching client identifiers to
    /// mitigate the problem of broken client implementations which generate
    /// new client identifiers every time they connect to the network.
    ///
    /// @param hw_address Pointer to the HW address of the client.
    /// @param client_id Pointer to the client identifier structure.
    ///
    /// @return true if the lease belongs to the client using the specified
    /// hardware address and/or client identifier.
    bool belongsToClient(const HWAddrPtr& hw_address,
                         const ClientIdPtr& client_id) const;

    /// @brief Assignment operator.
    ///
    /// @param other the @c Lease4 object to be assigned.
    Lease4& operator=(const Lease4& other);

    /// @brief Compare two leases for equality
    ///
    /// @param other lease6 object with which to compare
    bool operator==(const Lease4& other) const;

    /// @brief Compare two leases for inequality
    ///
    /// @param other lease6 object with which to compare
    bool operator!=(const Lease4& other) const {
        return (!operator==(other));
    }

    /// @brief Convert lease to printable form
    ///
    /// @return Textual represenation of lease data
    virtual std::string toText() const;

    /// @brief Sets IPv4 lease to declined state.
    ///
    /// See @ref Lease::decline for detailed description.
    ///
    /// @param probation_period valid lifetime will be set to this value
    void decline(uint32_t probation_period);

    /// @todo: Add DHCPv4 failover related fields here
};

/// @brief Pointer to a Lease4 structure.
typedef boost::shared_ptr<Lease4> Lease4Ptr;

/// @brief A collection of IPv4 leases.
typedef std::vector<Lease4Ptr> Lease4Collection;

/// @brief Structure that holds a lease for IPv6 address and/or prefix
///
/// For performance reasons it is a simple structure, not a class. If we chose
/// make it a class, all fields would have to made private and getters/setters
/// would be required. As this is a critical part of the code that will be used
/// extensively, direct access is warranted.
struct Lease6 : public Lease {

    /// @brief Lease type
    ///
    /// One of normal address, temporary address, or prefix.
    Type type_;

    /// @brief IPv6 prefix length
    ///
    /// This is used only for prefix delegations and is ignored otherwise.
    uint8_t prefixlen_;

    /// @brief Identity Association Identifier (IAID)
    ///
    /// DHCPv6 stores all addresses and prefixes in IA containers (IA_NA,
    /// IA_TA, IA_PD). All containers may appear more than once in a message.
    /// To differentiate between them, the IAID field is present
    uint32_t iaid_;

    /// @brief Client identifier
    DuidPtr duid_;

    /// @brief preferred lifetime
    ///
    /// This parameter specifies the preferred lifetime since the lease was
    /// assigned or renewed (cltt), expressed in seconds.
    uint32_t preferred_lft_;

    /// @todo: Add DHCPv6 failover related fields here

    /// @brief Constructor
    /// @param type Lease type.
    /// @param addr Assigned address.
    /// @param duid A pointer to an object representing DUID.
    /// @param iaid IAID.
    /// @param preferred Preferred lifetime.
    /// @param valid Valid lifetime.
    /// @param t1 A value of the T1 timer.
    /// @param t2 A value of the T2 timer.
    /// @param subnet_id A Subnet identifier.
    /// @param hwaddr hardware/MAC address (optional)
    /// @param prefixlen An address prefix length (optional, defaults to 128)
    Lease6(Type type, const isc::asiolink::IOAddress& addr, DuidPtr duid,
           uint32_t iaid, uint32_t preferred, uint32_t valid, uint32_t t1,
           uint32_t t2, SubnetID subnet_id, const HWAddrPtr& hwaddr = HWAddrPtr(),
           uint8_t prefixlen = 128);

    /// @brief Constructor, including FQDN data.
    ///
    /// @param type Lease type.
    /// @param addr Assigned address.
    /// @param duid A pointer to an object representing DUID.
    /// @param iaid IAID.
    /// @param preferred Preferred lifetime.
    /// @param valid Valid lifetime.
    /// @param t1 A value of the T1 timer.
    /// @param t2 A value of the T2 timer.
    /// @param subnet_id A Subnet identifier.
    /// @param fqdn_fwd If true, forward DNS update is performed for a lease.
    /// @param fqdn_rev If true, reverse DNS update is performed for a lease.
    /// @param hostname FQDN of the client which gets the lease.
    /// @param hwaddr hardware address (MAC), may be NULL
    /// @param prefixlen An address prefix length.
    Lease6(Type type, const isc::asiolink::IOAddress& addr, DuidPtr duid,
           uint32_t iaid, uint32_t preferred, uint32_t valid, uint32_t t1,
           uint32_t t2, SubnetID subnet_id, const bool fqdn_fwd,
           const bool fqdn_rev, const std::string& hostname,
           const HWAddrPtr& hwaddr = HWAddrPtr(), uint8_t prefixlen = 0);

    /// @brief Constructor
    ///
    /// Initialize fields that don't have a default constructor.
    Lease6();

    /// @brief Returns name of the lease states specific to DHCPv6.
    ///
    /// @todo Currently it simply returns common states for DHCPv4 and DHCPv6.
    /// This method will have to be extended to handle DHCPv6 specific states
    /// when they are defined.
    ///
    /// @param state Numeric value holding lease states.
    /// @return Comma separated list of lease state names.
    static std::string statesToText(const uint32_t state);

    /// @brief Returns a reference to a vector representing a DUID.
    ///
    /// @warning Since the function returns the reference to a vector (not a
    /// copy), the returned object should be used with caution because it will
    /// remain valid only for the period of time when an object which returned
    /// it exists.
    ///
    /// @return A reference to a vector holding a DUID.
    const std::vector<uint8_t>& getDuidVector() const;

    /// @brief Sets IPv6 lease to declined state.
    ///
    /// See @ref Lease::decline for detailed description.
    ///
    /// @param probation_period valid lifetime will be set to this value
    void decline(uint32_t probation_period);

    /// @brief Compare two leases for equality
    ///
    /// @param other lease6 object with which to compare
    bool operator==(const Lease6& other) const;

    /// @brief Compare two leases for inequality
    ///
    /// @param other lease6 object with which to compare
    bool operator!=(const Lease6& other) const {
        return (!operator==(other));
    }

    /// @brief Convert Lease to Printable Form
    ///
    /// @return String form of the lease
    virtual std::string toText() const;
};

/// @brief Pointer to a Lease6 structure.
typedef boost::shared_ptr<Lease6> Lease6Ptr;

/// @brief Pointer to a const Lease6 structure.
typedef boost::shared_ptr<const Lease6> ConstLease6Ptr;

/// @brief A collection of IPv6 leases.
typedef std::vector<Lease6Ptr> Lease6Collection;

/// @brief Stream output operator.
///
/// Dumps the output of Lease::toText to the given stream.
/// @param os output stream to which the output is
/// @param lease reference to Lease object to dump
/// @return a reference to the output stream paramater
std::ostream&
operator<<(std::ostream& os, const Lease& lease);

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // LEASE_H
