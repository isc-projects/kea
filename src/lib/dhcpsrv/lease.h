// Copyright (C) 2013-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_H
#define LEASE_H

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/option.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/subnet_id.h>
#include <cc/user_context.h>
#include <cc/cfg_to_element.h>
#include <util/dhcp_space.h>

namespace isc {
namespace dhcp {

struct Lease;

/// @brief Pointer to the lease object.
typedef boost::shared_ptr<Lease> LeasePtr;

/// @brief a common structure for IPv4 and IPv6 leases
///
/// This structure holds all information that is common between IPv4 and IPv6
/// leases.
struct Lease : public isc::data::UserContext, public isc::data::CfgToElement {

    /// @brief Infinity (means static, i.e. never expire)
    static const uint32_t INFINITY_LFT = 0xffffffff;

    /// @brief Print lifetime
    ///
    /// This converts a lifetime to a string taking into account the
    /// infinity special value.
    ///
    /// @param lifetime lifetime to print
    /// @return a string representing the finite value or "infinity"
    static std::string lifetimeToText(uint32_t lifetime);

    /// @brief Type of lease or pool
    typedef enum {
        TYPE_NA = 0, ///< the lease contains non-temporary IPv6 address
        TYPE_TA = 1, ///< the lease contains temporary IPv6 address
        TYPE_PD = 2, ///< the lease contains IPv6 prefix (for prefix delegation)
        TYPE_V4 = 3  ///< IPv4 lease
    } Type;

    /// @brief returns text representation of a lease type
    /// @param type lease or pool type to be converted
    /// @return text description
    static std::string typeToText(Type type);

    /// @brief Converts type name to the actual type.
    ///
    /// @param text lease type as text.
    /// @return converted type.
    /// @throw BadValue if the text contains unsupported value.
    static Type textToType(const std::string& text);

    /// @name Common lease states constants.
    //@{
    ///
    /// @brief A lease in the default state.
    static const uint32_t STATE_DEFAULT;

    /// @brief Declined lease.
    static const uint32_t STATE_DECLINED;

    /// @brief Expired and reclaimed lease.
    static const uint32_t STATE_EXPIRED_RECLAIMED;

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
    /// @param valid_lft Lifetime of the lease
    /// @param subnet_id Subnet identification
    /// @param cltt Client last transmission time
    /// @param fqdn_fwd If true, forward DNS update is performed for a lease.
    /// @param fqdn_rev If true, reverse DNS update is performed for a lease.
    /// @param hostname FQDN of the client which gets the lease.
    /// @param hwaddr Hardware/MAC address
    ///
    /// @note When creating a new Lease object, current_cltt_ matches cltt_ and
    /// current_valid_lft_ matches valid_lft_. Any update operation that changes
    /// cltt_ or valid_lft_ in the database must also update the current_cltt_
    /// and current_valid_lft_ after the database response so that additional
    /// operations can be performed on the same object. Failing to do so will
    /// result in the new actions to be rejected by the database.
    Lease(const isc::asiolink::IOAddress& addr,
          uint32_t valid_lft, SubnetID subnet_id, time_t cltt,
          const bool fqdn_fwd, const bool fqdn_rev,
          const std::string& hostname,
          const HWAddrPtr& hwaddr);

    /// @brief Destructor
    virtual ~Lease() {}

    /// @brief Returns Lease type
    ///
    /// One of normal address, temporary address, or prefix, or V4
    virtual Lease::Type getType() const = 0;

    /// @brief IPv4 ot IPv6 address
    ///
    /// IPv4, IPv6 address or, in the case of a prefix delegation, the prefix.
    isc::asiolink::IOAddress addr_;

    /// @brief Valid lifetime
    ///
    /// Expressed as number of seconds since cltt.
    uint32_t valid_lft_;

    /// @brief Current valid lifetime
    ///
    /// Expressed as number of seconds since cltt before update.
    uint32_t current_valid_lft_;

    /// @brief Remaining valid lifetime
    ///
    /// Expressed as number of seconds since current time, also
    /// valid lifetime - age where age is old cltt - new cltt.
    /// The value 0 is used for the "cannot be reused" condition.
    uint32_t reuseable_valid_lft_;

    /// @brief Client last transmission time
    ///
    /// Specifies a timestamp giving the time when the last transmission from a
    /// client was received.
    time_t cltt_;

    /// @brief Current client last transmission time
    ///
    /// Specifies a timestamp giving the time when the last transmission from a
    /// client was received before update.
    time_t current_cltt_;

    /// @brief Subnet identifier
    ///
    /// Specifies the identification of the subnet to which the lease belongs.
    SubnetID subnet_id_;

    /// @brief The pool id
    ///
    /// Specifies the identification of the pool from a subnet to which the lease belongs.
    uint32_t pool_id_;

    /// @brief Client hostname
    ///
    /// This field is in lower case and may be empty.
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
    /// lease remains in a single states. However, it is possible to
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

    /// @brief Indicates if the lease is in the "declined" state.
    ///
    /// @return true if the lease is in the "declined" state, false otherwise.
    bool stateDeclined() const;

    /// @brief Returns true if the other lease has equal FQDN data.
    ///
    /// The comparison of the hostname is case insensitive.
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
    /// client_id, hostname), cltt will be set to current time and
    /// valid_lft to parameter specified as probation period.
    /// Note that This method only sets fields in the structure.
    /// It is caller's responsibility to clean up DDNS, bump up stats,
    /// log, call hooks ets.
    ///
    /// @param probation_period lease lifetime will be set to this value
    virtual void decline(uint32_t probation_period) = 0;

    /// Avoid a clang spurious error
    using isc::data::CfgToElement::toElement;

    /// Sync lease current expiration time with new value from another lease,
    /// so that additional operations can be done without performing extra read
    /// from the database.
    ///
    /// @note The lease current expiration time is represented by the
    /// @ref current_cltt_ and  @ref current_valid_lft_ and the new value by
    /// @ref cltt_ and @ref valid_lft_
    ///
    /// @param from The lease with latest value of expiration time.
    /// @param [out] to The lease that needs to be updated.
    static void syncCurrentExpirationTime(const Lease& from, Lease& to);

    /// Update lease current expiration time with new value,
    /// so that additional operations can be done without performing extra read
    /// from the database.
    ///
    /// @note The lease current expiration time is represented by the
    /// @ref current_cltt_ and  @ref current_valid_lft_ and the new value by
    /// @ref cltt_ and @ref valid_lft_
    void updateCurrentExpirationTime();

protected:

    /// @brief Sets common (for v4 and v6) properties of the lease object.
    ///
    /// This method is called by the @c fromElement methods of the @c Lease
    /// class derivations.
    ///
    /// @param [out] lease pointer to the lease object for which common
    /// properties should be set.
    /// @param element pointer to the data element object to be parsed.
    static void fromElementCommon(const LeasePtr& lease,
                                  const data::ConstElementPtr& element);

};

struct Lease4;

/// @brief Pointer to a Lease4 structure.
typedef boost::shared_ptr<Lease4> Lease4Ptr;

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
    /// @param cltt Client last transmission time
    /// @param subnet_id Subnet identification
    /// @param fqdn_fwd If true, forward DNS update is performed for a lease.
    /// @param fqdn_rev If true, reverse DNS update is performed for a lease.
    /// @param hostname FQDN of the client which gets the lease.
    Lease4(const isc::asiolink::IOAddress& addr, const HWAddrPtr& hwaddr,
           const uint8_t* clientid, size_t clientid_len, uint32_t valid_lft,
           time_t cltt, uint32_t subnet_id,
           const bool fqdn_fwd = false, const bool fqdn_rev = false,
           const std::string& hostname = "")
        : Lease(addr, valid_lft, subnet_id, cltt, fqdn_fwd, fqdn_rev,
                hostname, hwaddr) {
        if (clientid_len) {
            client_id_.reset(new ClientId(clientid, clientid_len));
        }
    }

    /// @brief Constructor.
    ///
    /// @param address IPv4 address.
    /// @param hw_address Pointer to client's HW address.
    /// @param client_id  pointer to the client id structure.
    /// @param valid_lifetime Valid lifetime value.
    /// @param cltt Timestamp when the lease is acquired, renewed.
    /// @param subnet_id Subnet identifier.
    /// @param fqdn_fwd Forward DNS update performed.
    /// @param fqdn_rev Reverse DNS update performed.
    /// @param hostname Client's name for the DNS update..
    Lease4(const isc::asiolink::IOAddress& address,
           const HWAddrPtr& hw_address,
           const ClientIdPtr& client_id,
           const uint32_t valid_lifetime,
           const time_t cltt,
           const SubnetID subnet_id,
           const bool fqdn_fwd = false,
           const bool fqdn_rev = false,
           const std::string& hostname = "");


    /// @brief Default constructor
    ///
    /// Initialize fields that don't have a default constructor.
    Lease4();

    /// @brief Returns Lease type
    ///
    /// Since @c Lease does not define a member for lease type, we implement this
    /// so we don't store the same value in a billion v4 lease instances.
    ///
    /// @return Lease::TYPE_V4
    virtual Lease::Type getType() const {
        return (Lease::TYPE_V4);
    }

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
    /// @return Textual representation of lease data
    virtual std::string toText() const;

    /// @brief Sets IPv4 lease to declined state.
    ///
    /// See @ref Lease::decline for detailed description.
    ///
    /// @param probation_period valid lifetime will be set to this value
    void decline(uint32_t probation_period);

    /// @brief Return the JSON representation of a lease
    virtual isc::data::ElementPtr toElement() const;

    /// @brief Returns pointer to the IPv4 lease created from JSON
    /// representation.
    ///
    /// @param element pointer to the data element object to be parsed.
    /// @return Pointer to the created lease.
    static Lease4Ptr fromElement(const data::ConstElementPtr& element);

    /// @todo: Add DHCPv4 failover related fields here

    /// @brief Remote identifier for Bulk Lease Query
    std::vector<uint8_t> remote_id_;

    /// @brief Relay identifier for Bulk Lease Query
    std::vector<uint8_t> relay_id_;
};

/// @brief A collection of IPv4 leases.
typedef std::vector<Lease4Ptr> Lease4Collection;

/// @brief A shared pointer to the collection of IPv4 leases.
typedef boost::shared_ptr<Lease4Collection> Lease4CollectionPtr;

struct Lease6;

/// @brief Pointer to a Lease6 structure.
typedef boost::shared_ptr<Lease6> Lease6Ptr;

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
    Lease::Type type_;

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

    /// @brief Preferred lifetime
    ///
    /// This parameter specifies the preferred lifetime since the lease was
    /// assigned or renewed (cltt), expressed in seconds.
    uint32_t preferred_lft_;

    /// @brief Remaining preferred lifetime
    ///
    /// Expressed as number of seconds since current time, also
    /// preferred lifetime - age where age is old cltt - new cltt.
    /// This parameter is used only when reuseable_valid_lft_ is not zero,
    /// i.e. when the lease can be reused.
    uint32_t reuseable_preferred_lft_;

    /// @brief Action on extended info tables.
    typedef enum {
        ACTION_IGNORE, ///< ignore extended info,
        ACTION_DELETE, ///< delete reference to the lease
        ACTION_UPDATE  ///< update extended info tables.
    } ExtendedInfoAction;

    /// @brief Record the action on extended info tables in the lease.
    ExtendedInfoAction extended_info_action_;

    /// @todo: Add DHCPv6 failover related fields here

    /// @brief Constructor
    /// @param type Lease type.
    /// @param addr Assigned address.
    /// @param duid A pointer to an object representing DUID.
    /// @param iaid IAID.
    /// @param preferred Preferred lifetime.
    /// @param valid Valid lifetime.
    /// @param subnet_id A Subnet identifier.
    /// @param hwaddr hardware/MAC address (optional)
    /// @param prefixlen An address prefix length (optional, defaults to 128)
    Lease6(Lease::Type type, const isc::asiolink::IOAddress& addr, DuidPtr duid,
           uint32_t iaid, uint32_t preferred, uint32_t valid,
           SubnetID subnet_id, const HWAddrPtr& hwaddr = HWAddrPtr(),
           uint8_t prefixlen = 128);

    /// @brief Constructor, including FQDN data.
    ///
    /// @param type Lease type.
    /// @param addr Assigned address.
    /// @param duid A pointer to an object representing DUID.
    /// @param iaid IAID.
    /// @param preferred Preferred lifetime.
    /// @param valid Valid lifetime.
    /// @param subnet_id A Subnet identifier.
    /// @param fqdn_fwd If true, forward DNS update is performed for a lease.
    /// @param fqdn_rev If true, reverse DNS update is performed for a lease.
    /// @param hostname FQDN of the client which gets the lease.
    /// @param hwaddr hardware address (MAC), may be NULL
    /// @param prefixlen An address prefix length (optional, defaults to 128)
    Lease6(Lease::Type type, const isc::asiolink::IOAddress& addr, DuidPtr duid,
           uint32_t iaid, uint32_t preferred, uint32_t valid,
           SubnetID subnet_id, const bool fqdn_fwd,
           const bool fqdn_rev, const std::string& hostname,
           const HWAddrPtr& hwaddr = HWAddrPtr(), uint8_t prefixlen = 128);

    /// @brief Constructor
    ///
    /// Initialize fields that don't have a default constructor.
    Lease6();

    /// @brief Returns Lease type
    ///
    /// Since @c Lease does not define a member for lease type, we implement this
    /// so code that only has LeasePtr can see what it has.
    ///
    /// @return Type of lease
    virtual Lease::Type getType() const {
        return (type_);
    }

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

    /// @brief Return the JSON representation of a lease
    virtual isc::data::ElementPtr toElement() const;

    /// @brief Returns pointer to the IPv6 lease created from JSON
    /// representation.
    ///
    /// @param element pointer to the data element object to be parsed.
    /// @return Pointer to the created lease.
    static Lease6Ptr fromElement(const data::ConstElementPtr& element);
};

/// @brief Pointer to a const Lease6 structure.
typedef boost::shared_ptr<const Lease6> ConstLease6Ptr;

/// @brief A collection of IPv6 leases.
typedef std::vector<Lease6Ptr> Lease6Collection;

/// @brief A shared pointer to the collection of IPv6 leases.
typedef boost::shared_ptr<Lease6Collection> Lease6CollectionPtr;

/// @brief Stream output operator.
///
/// Dumps the output of Lease::toText to the given stream.
/// @param os output stream to which the output is
/// @param lease reference to Lease object to dump
/// @return a reference to the output stream parameter
std::ostream&
operator<<(std::ostream& os, const Lease& lease);

/// @brief adapters for linking templates to qualified names
/// @{
namespace {

template <isc::util::DhcpSpace D>
struct AdapterLease {};

template <>
struct AdapterLease<isc::util::DHCPv4> {
    using type = Lease4;
};

template <>
struct AdapterLease<isc::util::DHCPv6> {
    using type = Lease6;
};

}  // namespace

template <isc::util::DhcpSpace D>
using LeaseT = typename AdapterLease<D>::type;

template <isc::util::DhcpSpace D>
using LeaseTPtr = boost::shared_ptr<LeaseT<D>>;
/// @}

}  // end of isc::dhcp namespace
}  // end of isc namespace

#endif // LEASE_H
