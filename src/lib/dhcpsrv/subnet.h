// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef SUBNET_H
#define SUBNET_H

#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <dhcp/classify.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfg_4o6.h>
#include <dhcpsrv/option_space_container.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/triplet.h>
#include <dhcpsrv/lease.h>

#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief a base class for Subnet4 and Subnet6
///
/// This class presents a common base for IPv4 and IPv6 subnets.
/// In a physical sense, a subnet defines a single network link with all devices
/// attached to it. In most cases all devices attached to a single link can
/// share the same parameters. Therefore Subnet holds several values that are
/// typically shared by all hosts: renew timer (T1), rebind timer (T2) and
/// leased addresses lifetime (valid-lifetime). It also holds the set
/// of DHCP option instances configured for the subnet. These options are
/// included in DHCP messages being sent to clients which are connected
/// to the particular subnet.
///
/// @todo: Implement support for options here

/// @brief Unique identifier for a subnet (both v4 and v6)
typedef uint32_t SubnetID;

class Subnet {
public:

    /// @brief Holds optional information about relay.
    ///
    /// In some cases it is beneficial to have additional information about
    /// a relay configured in the subnet. For now, the structure holds only
    /// IP address, but there may potentially be additional parameters added
    /// later, e.g. relay interface-id or relay-id.
    struct RelayInfo {

        /// @brief default and the only constructor
        ///
        /// @param addr an IP address of the relay (may be :: or 0.0.0.0)
        RelayInfo(const isc::asiolink::IOAddress& addr);

        /// @brief IP address of the relay
        isc::asiolink::IOAddress addr_;
    };

    /// @brief Specifies allowed host reservation mode.
    ///
    typedef enum  {

        /// None - host reservation is disabled. No reservation types
        /// are allowed.
        HR_DISABLED,

        /// Only out-of-pool reservations is allowed. This mode
        /// allows AllocEngine to skip reservation checks when
        /// dealing with with addresses that are in pool.
        HR_OUT_OF_POOL,

        /// Both out-of-pool and in-pool reservations are allowed. This is the
        /// most flexible mode, where sysadmin have biggest liberty. However,
        /// there is a non-trivial performance penalty for it, as the
        /// AllocEngine code has to check whether there are reservations, even
        /// when dealing with reservations from within the dynamic pools.
        HR_ALL
    } HRMode;

    /// Pointer to the RelayInfo structure
    typedef boost::shared_ptr<Subnet::RelayInfo> RelayInfoPtr;

    /// @brief checks if specified address is in range
    bool inRange(const isc::asiolink::IOAddress& addr) const;

    /// @brief checks if the specified address is in pools
    ///
    /// Note the difference between inRange() and inPool(). For a given
    /// subnet (e.g. 2001::/64) there may be one or more pools defined
    /// that may or may not cover entire subnet, e.g. pool 2001::1-2001::10).
    /// inPool() returning true implies inRange(), but the reverse implication
    /// is not always true. For the given example, 2001::1234:abcd would return
    /// true for inRange(), but false for inPool() check.
    ///
    /// @param type type of pools to iterate over
    /// @param addr this address will be checked if it belongs to any pools in
    ///        that subnet
    /// @return true if the address is in any of the pools
    bool inPool(Lease::Type type, const isc::asiolink::IOAddress& addr) const;

    /// @brief Return valid-lifetime for addresses in that prefix
    Triplet<uint32_t> getValid() const {
        return (valid_);
    }

    /// @brief Returns T1 (renew timer), expressed in seconds
    Triplet<uint32_t> getT1() const {
        return (t1_);
    }

    /// @brief Returns T2 (rebind timer), expressed in seconds
    Triplet<uint32_t> getT2() const {
        return (t2_);
    }

    /// @brief Returns pointer to the option data configuration for this subnet.
    CfgOptionPtr getCfgOption() {
        return (cfg_option_);
    }

    /// @brief Returns const pointer to the option data configuration for this
    /// subnet.
    ConstCfgOptionPtr getCfgOption() const {
        return (cfg_option_);
    }

    /// @brief returns the last address that was tried from this pool
    ///
    /// This method returns the last address that was attempted to be allocated
    /// from this subnet. This is used as helper information for the next
    /// iteration of the allocation algorithm.
    ///
    /// @todo: Define map<SubnetID, IOAddress> somewhere in the
    ///        AllocEngine::IterativeAllocator and keep the data there
    ///
    /// @param type lease type to be returned
    /// @return address/prefix that was last tried from this pool
    isc::asiolink::IOAddress getLastAllocated(Lease::Type type) const;

    /// @brief sets the last address that was tried from this pool
    ///
    /// This method sets the last address that was attempted to be allocated
    /// from this subnet. This is used as helper information for the next
    /// iteration of the allocation algorithm.
    ///
    /// @todo: Define map<SubnetID, IOAddress> somewhere in the
    ///        AllocEngine::IterativeAllocator and keep the data there
    /// @param addr address/prefix to that was tried last
    /// @param type lease type to be set
    void setLastAllocated(Lease::Type type,
                          const isc::asiolink::IOAddress& addr);

    /// @brief Returns unique ID for that subnet
    /// @return unique ID for that subnet
    SubnetID getID() const { return (id_); }

    /// @brief Returns subnet parameters (prefix and prefix length)
    ///
    /// @return (prefix, prefix length) pair
    std::pair<isc::asiolink::IOAddress, uint8_t> get() const {
        return (std::make_pair(prefix_, prefix_len_));
    }

    /// @brief Adds a new pool for the subnet.
    ///
    /// This method checks that the address range represented by the pool
    /// matches the subnet prefix, if the pool type is different than
    /// IA_PD. The prefixes from the IA_PD pools don't need to match the
    /// prefix from the subnet from which they are handed out to the
    /// requesting router because the requesting router may use the
    /// delegated prefixes in different networks (using different subnets).
    ///
    /// @param pool pool to be added
    ///
    /// @throw isc::BadValue if the pool type is invalid or the pool
    /// is not an IA_PD pool and the address range of this pool does not
    /// match the subnet prefix.
    void addPool(const PoolPtr& pool);


    /// @brief Deletes all pools of specified type
    ///
    /// This method is used for testing purposes only
    /// @param type type of pools to be deleted
    void delPools(Lease::Type type);

    /// @brief Returns a pool that specified address belongs to
    ///
    /// If there is no pool that the address belongs to (hint is invalid), other
    /// pool of specified type will be returned.
    ///
    /// With anypool set to true, this is means give me a pool, preferably
    /// the one that addr belongs to. With anypool set to false, it means
    /// give me a pool that addr belongs to (or NULL if here is no such pool)
    ///
    /// @param type pool type that the pool is looked for
    /// @param addr address that the returned pool should cover (optional)
    /// @param anypool other pool may be returned as well, not only the one
    ///        that addr belongs to
    /// @return found pool (or NULL)
    const PoolPtr getPool(Lease::Type type, const isc::asiolink::IOAddress& addr,
                          bool anypool = true) const;

    /// @brief Returns a pool without any address specified
    ///
    /// @param type pool type that the pool is looked for
    /// @return returns one of the pools defined
    PoolPtr getAnyPool(Lease::Type type) {
        return (getPool(type, default_pool()));
    }

    /// @brief Returns the default address that will be used for pool selection
    ///
    /// It must be implemented in derived classes (should return :: for Subnet6
    /// and 0.0.0.0 for Subnet4)
    virtual isc::asiolink::IOAddress default_pool() const = 0;

    /// @brief Returns all pools (const variant)
    ///
    /// The reference is only valid as long as the object that returned it.
    ///
    /// @param type lease type to be set
    /// @return a collection of all pools
    const PoolCollection& getPools(Lease::Type type) const;

    /// @brief Returns the number of possible leases for specified lease type
    ///
    /// @param type type of the lease
    uint64_t getPoolCapacity(Lease::Type type) const;

    /// @brief Sets name of the network interface for directly attached networks
    ///
    /// @param iface_name name of the interface
    void setIface(const std::string& iface_name);

    /// @brief Network interface name used to reach subnet (or "" for remote
    /// subnets)
    /// @return network interface name for directly attached subnets or ""
    std::string getIface() const;

    /// @brief Returns textual representation of the subnet (e.g.
    /// "2001:db8::/64")
    ///
    /// @return textual representation
    virtual std::string toText() const;

    /// @brief Resets subnet-id counter to its initial value (1)
    ///
    /// This should be called during reconfiguration, before any new
    /// subnet objects are created. It will ensure that the subnet_id will
    /// be consistent between reconfigures.
    static void resetSubnetID() {
        static_id_ = 1;
    }

    /// @brief Sets information about relay
    ///
    /// In some situations where there are shared subnets (i.e. two different
    /// subnets are available on the same physical link), there is only one
    /// relay that handles incoming requests from clients. In such a case,
    /// the usual subnet selection criteria based on relay belonging to the
    /// subnet being selected are no longer sufficient and we need to explicitly
    /// specify a relay. One notable example of such uncommon, but valid
    /// scenario is a cable network, where there is only one CMTS (one relay),
    /// but there are 2 distinct subnets behind it: one for cable modems
    /// and another one for CPEs and other user equipment behind modems.
    /// From manageability perspective, it is essential that modems get addresses
    /// from different subnet, so users won't tinker with their modems.
    ///
    /// Setting this parameter is not needed in most deployments.
    /// This structure holds IP address only for now, but it is expected to
    /// be extended in the future.
    ///
    /// @param relay structure that contains relay information
    void setRelayInfo(const isc::dhcp::Subnet::RelayInfo& relay);


    /// @brief Returns const reference to relay information
    ///
    /// @note The returned reference is only valid as long as the object
    /// returned it is valid.
    ///
    /// @return const reference to the relay information
    const isc::dhcp::Subnet::RelayInfo& getRelayInfo() {
        return (relay_);
    }

    /// @brief checks whether this subnet supports client that belongs to
    ///        specified classes.
    ///
    /// This method checks whether a client that belongs to given classes can
    /// use this subnet. For example, if this class is reserved for client
    /// class "foo" and the client belongs to classes "foo", "bar" and "baz",
    /// it is supported. On the other hand, client belonging to classes
    /// "foobar" and "zyxxy" is not supported.
    ///
    /// @todo: Currently the logic is simple: client is supported if it belongs
    /// to any class mentioned in white_list_. We will eventually need a
    /// way to specify more fancy logic (e.g. to meet all classes, not just
    /// any)
    ///
    /// @param client_classes list of all classes the client belongs to
    /// @return true if client can be supported, false otherwise
    bool
    clientSupported(const isc::dhcp::ClientClasses& client_classes) const;

    /// @brief adds class class_name to the list of supported classes
    ///
    /// Also see explanation note in @ref white_list_.
    ///
    /// @param class_name client class to be supported by this subnet
    void
    allowClientClass(const isc::dhcp::ClientClass& class_name);

    /// @brief Specifies what type of Host Reservations are supported.
    ///
    /// Host reservations may be either in-pool (they reserve an address that
    /// is in the dynamic pool) or out-of-pool (they reserve an address that is
    /// not in the dynamic pool). HR may also be completely disabled for
    /// performance reasons.
    ///
    /// @return whether in-pool host reservations are allowed.
    HRMode
    getHostReservationMode() const {
        return (host_reservation_mode_);
    }

    /// @brief Sets host reservation mode.
    ///
    /// See @ref getHostReservationMode for details.
    ///
    /// @param mode mode to be set
    void setHostReservationMode(HRMode mode) {
        host_reservation_mode_ = mode;
    }

protected:
    /// @brief Returns all pools (non-const variant)
    ///
    /// The reference is only valid as long as the object that returned it.
    ///
    /// @param type lease type to be set
    /// @return a collection of all pools
    PoolCollection& getPoolsWritable(Lease::Type type);

    /// @brief Protected constructor
    //
    /// By making the constructor protected, we make sure that no one will
    /// ever instantiate that class. Subnet4 and Subnet6 should be used instead.
    ///
    /// This constructor assigns a new subnet-id (see @ref generateNextID).
    /// This subnet-id has unique value that is strictly monotonously increasing
    /// for each subnet, until it is explicitly reset back to 1 during
    /// reconfiguration process.
    ///
    /// @param prefix subnet prefix
    /// @param len prefix length for the subnet
    /// @param t1 T1 (renewal-time) timer, expressed in seconds
    /// @param t2 T2 (rebind-time) timer, expressed in seconds
    /// @param valid_lifetime valid lifetime of leases in this subnet (in seconds)
    /// @param relay optional relay information (currently with address only)
    /// @param id arbitraty subnet id, value of 0 triggers autogeneration
    /// of subnet id
    Subnet(const isc::asiolink::IOAddress& prefix, uint8_t len,
           const Triplet<uint32_t>& t1,
           const Triplet<uint32_t>& t2,
           const Triplet<uint32_t>& valid_lifetime,
           const isc::dhcp::Subnet::RelayInfo& relay,
           const SubnetID id);

    /// @brief virtual destructor
    ///
    /// A virtual destructor is needed because other classes
    /// derive from this class.
    virtual ~Subnet() { };

    /// @brief keeps the subnet-id value
    ///
    /// It is inreased every time a new Subnet object is created. It is reset
    /// (@ref resetSubnetID) every time reconfiguration
    /// occurs.
    ///
    /// Static value initialized in subnet.cc.
    static SubnetID static_id_;

    /// @brief returns the next unique Subnet-ID
    ///
    /// This method generates and returns the next unique subnet-id.
    /// It is a strictly monotonously increasing value (1,2,3,...) for
    /// each new Subnet object created. It can be explicitly reset
    /// back to 1 during reconfiguration (@ref resetSubnetID).
    ///
    /// @return the next unique Subnet-ID
    static SubnetID generateNextID() {
        return (static_id_++);
    }

    /// @brief Checks if used pool type is valid
    ///
    /// Allowed type for Subnet4 is Pool::TYPE_V4.
    /// Allowed types for Subnet6 are Pool::TYPE_{IA,TA,PD}.
    /// This method is implemented in derived classes.
    ///
    /// @param type type to be checked
    /// @throw BadValue if invalid value is used
    virtual void checkType(Lease::Type type) const = 0;

    /// @brief returns a sum of possible leases in all pools
    /// @param pools list of pools
    /// @return sum of possible leases
    uint64_t sumPoolCapacity(const PoolCollection& pools) const;

    /// @brief subnet-id
    ///
    /// Subnet-id is a unique value that can be used to find or identify
    /// a Subnet4 or Subnet6.
    SubnetID id_;

    /// @brief collection of IPv4 or non-temporary IPv6 pools in that subnet
    PoolCollection pools_;

    /// @brief collection of IPv6 temporary address pools in that subnet
    PoolCollection pools_ta_;

    /// @brief collection of IPv6 prefix pools in that subnet
    PoolCollection pools_pd_;

    /// @brief a prefix of the subnet
    isc::asiolink::IOAddress prefix_;

    /// @brief a prefix length of the subnet
    uint8_t prefix_len_;

    /// @brief a tripet (min/default/max) holding allowed renew timer values
    Triplet<uint32_t> t1_;

    /// @brief a tripet (min/default/max) holding allowed rebind timer values
    Triplet<uint32_t> t2_;

    /// @brief a tripet (min/default/max) holding allowed valid lifetime values
    Triplet<uint32_t> valid_;

    /// @brief last allocated address
    ///
    /// This is the last allocated address that was previously allocated from
    /// this particular subnet. Some allocation algorithms (e.g. iterative) use
    /// that value, others do not. It should be noted that although the value
    /// is usually correct, there are cases when it is invalid, e.g. after
    /// removing a pool, restarting or changing allocation algorithms. For
    /// that purpose it should be only considered a help that should not be
    /// fully trusted.
    isc::asiolink::IOAddress last_allocated_ia_;

    /// @brief last allocated temporary address
    ///
    /// See @ref last_allocated_ia_ for details.
    isc::asiolink::IOAddress last_allocated_ta_;

    /// @brief last allocated IPv6 prefix
    ///
    /// See @ref last_allocated_ia_ for details.
    isc::asiolink::IOAddress last_allocated_pd_;

    /// @brief Name of the network interface (if connected directly)
    std::string iface_;

    /// @brief Relay information
    ///
    /// See @ref RelayInfo for detailed description. This structure is public,
    /// so its fields are easily accessible. Making it protected would bring in
    /// the issue of returning references that may become stale after its parent
    /// subnet object disappears.
    RelayInfo relay_;

    /// @brief optional definition of a client class
    ///
    /// If defined, only clients belonging to that class will be allowed to use
    /// this particular subnet. The default value for this is an empty list,
    /// which means that any client is allowed, regardless of its class.
    ///
    /// @todo This is just a single list of allowed classes. We'll also need
    /// to add a black-list (only classes on the list are rejected, the rest
    /// are allowed). Implementing this will require more fancy parser logic,
    /// so it may be a while until we support this.
    ClientClasses white_list_;

    /// @brief Specifies host reservation mode
    ///
    /// See @ref HRMode type for details.
    HRMode host_reservation_mode_;
private:

    /// @brief Pointer to the option data configuration for this subnet.
    CfgOptionPtr cfg_option_;
};

/// @brief A generic pointer to either Subnet4 or Subnet6 object
typedef boost::shared_ptr<Subnet> SubnetPtr;


/// @brief A configuration holder for IPv4 subnet.
///
/// This class represents an IPv4 subnet.
class Subnet4 : public Subnet {
public:

    /// @brief Constructor with all parameters
    ///
    /// This constructor calls Subnet::Subnet, where subnet-id is generated.
    ///
    /// @param prefix Subnet4 prefix
    /// @param length prefix length
    /// @param t1 renewal timer (in seconds)
    /// @param t2 rebind timer (in seconds)
    /// @param valid_lifetime preferred lifetime of leases (in seconds)
    /// @param id arbitraty subnet id, default value of 0 triggers
    /// autogeneration of subnet id
    Subnet4(const isc::asiolink::IOAddress& prefix, uint8_t length,
            const Triplet<uint32_t>& t1,
            const Triplet<uint32_t>& t2,
            const Triplet<uint32_t>& valid_lifetime,
            const SubnetID id = 0);

    /// @brief Sets siaddr for the Subnet4
    ///
    /// Will be used for siaddr field (the next server) that typically is used
    /// as TFTP server. If not specified, the default value of 0.0.0.0 is
    /// used.
    void setSiaddr(const isc::asiolink::IOAddress& siaddr);

    /// @brief Returns siaddr for this subnet
    ///
    /// @return siaddr value
    isc::asiolink::IOAddress getSiaddr() const;

    /// @brief Sets the flag indicating if the client identifier should be
    /// used to identify the client's lease.
    ///
    /// @param match If this value is true, the client identifiers are not
    /// used for lease lookup.
    void setMatchClientId(const bool match) {
        match_client_id_ = match;
    }

    /// @brief Returns the flag indicating if the client identifiers should
    /// be used to identify the client's lease.
    ///
    /// @return true if client identifiers should be used, false otherwise.
    bool getMatchClientId() const {
        return (match_client_id_);
    }

    /// @brief Returns DHCP4o6 configuration parameters.
    ///
    /// This structure is always available. If the 4o6 is not enabled, its
    /// enabled_ field will be set to false.
    Cfg4o6& get4o6() {
        return (dhcp4o6_);
    }

private:

    /// @brief Returns default address for pool selection
    /// @return ANY IPv4 address
    virtual isc::asiolink::IOAddress default_pool() const {
        return (isc::asiolink::IOAddress("0.0.0.0"));
    }

    /// @brief Checks if used pool type is valid
    ///
    /// Allowed type for Subnet4 is Pool::TYPE_V4.
    ///
    /// @param type type to be checked
    /// @throw BadValue if invalid value is used
    virtual void checkType(Lease::Type type) const;

    /// @brief siaddr value for this subnet
    isc::asiolink::IOAddress siaddr_;

    /// @brief Should server use client identifiers for client lease
    /// lookup.
    bool match_client_id_;

    /// @brief All the information related to DHCP4o6
    Cfg4o6 dhcp4o6_;
};

/// @brief A pointer to a @c Subnet4 object
typedef boost::shared_ptr<Subnet4> Subnet4Ptr;

/// @brief A collection of @c Subnet4 objects
///
/// That is a simple vector of pointers. It does not make much sense to
/// optimize access time (e.g. using a map), because typical search
/// pattern will use calling inRange() method on each subnet until
/// a match is found.
typedef std::vector<Subnet4Ptr> Subnet4Collection;

/// @brief A configuration holder for IPv6 subnet.
///
/// This class represents an IPv6 subnet.
class Subnet6 : public Subnet {
public:

    /// @brief Constructor with all parameters
    ///
    /// This constructor calls Subnet::Subnet, where subnet-id is generated.
    ///
    /// @param prefix Subnet6 prefix
    /// @param length prefix length
    /// @param t1 renewal timer (in seconds)
    /// @param t2 rebind timer (in seconds)
    /// @param preferred_lifetime preferred lifetime of leases (in seconds)
    /// @param valid_lifetime preferred lifetime of leases (in seconds)
    /// @param id arbitraty subnet id, default value of 0 triggers
    /// autogeneration of subnet id
    Subnet6(const isc::asiolink::IOAddress& prefix, uint8_t length,
            const Triplet<uint32_t>& t1,
            const Triplet<uint32_t>& t2,
            const Triplet<uint32_t>& preferred_lifetime,
            const Triplet<uint32_t>& valid_lifetime,
            const SubnetID id = 0);

    /// @brief Returns preverred lifetime (in seconds)
    ///
    /// @return a triplet with preferred lifetime
    Triplet<uint32_t> getPreferred() const {
        return (preferred_);
    }

    /// @brief sets interface-id option (if defined)
    ///
    /// @param ifaceid pointer to interface-id option
    void setInterfaceId(const OptionPtr& ifaceid) {
        interface_id_ = ifaceid;
    }

    /// @brief returns interface-id value (if specified)
    /// @return interface-id option (if defined)
    OptionPtr getInterfaceId() const {
        return interface_id_;
    }

    /// @brief Enables or disables Rapid Commit option support for the subnet.
    ///
    /// @param rapid_commit A boolean value indicating that the Rapid Commit
    /// option support is enabled (if true), or disabled (if false).
    void setRapidCommit(const bool rapid_commit) {
        rapid_commit_ = rapid_commit;
    };

    /// @brief Returns boolean value indicating that the Rapid Commit option
    /// is supported or unsupported for the subnet.
    ///
    /// @return true if the Rapid Commit option is supported, false otherwise.
    bool getRapidCommit() const {
        return (rapid_commit_);
    }

private:

    /// @brief Returns default address for pool selection
    /// @return ANY IPv6 address
    virtual isc::asiolink::IOAddress default_pool() const {
        return (isc::asiolink::IOAddress("::"));
    }

    /// @brief Checks if used pool type is valid
    ///
    /// allowed types for Subnet6 are Pool::TYPE_{IA,TA,PD}.
    ///
    /// @param type type to be checked
    /// @throw BadValue if invalid value is used
    virtual void checkType(Lease::Type type) const;

    /// @brief specifies optional interface-id
    OptionPtr interface_id_;

    /// @brief a triplet with preferred lifetime (in seconds)
    Triplet<uint32_t> preferred_;

    /// @brief A flag indicating if Rapid Commit option is supported
    /// for this subnet.
    ///
    /// It's default value is false, which indicates that the Rapid
    /// Commit is disabled for the subnet.
    bool rapid_commit_;

};

/// @brief A pointer to a Subnet6 object
typedef boost::shared_ptr<Subnet6> Subnet6Ptr;

/// @brief A collection of Subnet6 objects
typedef std::vector<Subnet6Ptr> Subnet6Collection;

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // SUBNET_H
