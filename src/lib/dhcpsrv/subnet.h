// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SUBNET_H
#define SUBNET_H

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <cc/user_context.h>
#include <dhcp/option_space_container.h>
#include <dhcpsrv/allocator.h>
#include <dhcpsrv/allocation_state.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/network.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/subnet_id.h>
#include <util/bigints.h>
#include <util/dhcp_space.h>
#include <util/triplet.h>

#include <boost/enable_shared_from_this.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>

#include <cstdint>
#include <map>
#include <utility>

namespace isc {
namespace dhcp {

class Subnet : public virtual Network {
public:

    /// @brief checks if specified address is in range.
    ///
    /// @param addr this address will be checked if it is included in a specific
    ///        range
    /// @return true if address is in range, false otherwise
    bool inRange(const isc::asiolink::IOAddress& addr) const;

    /// @brief checks if the specified address is in pools.
    ///
    /// Note the difference between inRange() and inPool() for addresses
    /// (i.e. *not* prefixes). For a given subnet (e.g. 2001::/64) there
    /// may be one or more pools defined that may or may not cover
    /// entire subnet, e.g. pool 2001::1-2001::10). inPool() returning
    /// true implies inRange(), but the reverse implication is not
    /// always true. For the given example, 2001::1234:abcd would return
    /// true for inRange(), but false for inPool() check.
    ///
    /// @param type type of pools to iterate over
    /// @param addr this address will be checked if it belongs to any pools in
    ///        that subnet
    /// @return true if the address is in any of the pools
    bool inPool(Lease::Type type, const isc::asiolink::IOAddress& addr) const;

    /// @brief checks if the specified address is in allowed pools.
    ///
    /// This takes also into account client classes
    ///
    /// @param type type of pools to iterate over
    /// @param addr this address will be checked if it belongs to any pools in
    ///        that subnet
    /// @param client_classes client class list which must be allowed
    /// @return true if the address is in any of the allowed pools
    bool inPool(Lease::Type type,
                const isc::asiolink::IOAddress& addr,
                const ClientClasses& client_classes) const;

     /// @brief Returns unique ID for that subnet.
    ///
    /// @return unique ID for that subnet
    SubnetID getID() const {
        return (id_);
    }

    /// @brief Returns subnet parameters (prefix and prefix length).
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
    /// A DHCPv4 pool being added must not overlap with any existing DHCPv4
    /// pool. A DHCPv6 pool being added must not overlap with any existing
    /// DHCPv6 pool.
    ///
    /// Pools held within a subnet are sorted by first pool address/prefix
    /// from the lowest to the highest.
    ///
    /// @param pool pool to be added
    ///
    /// @throw isc::BadValue if the pool type is invalid, in the case of address
    /// pools if the address range of the pool does not match the subnet prefix,
    /// or if the pool overlaps with an existing pool within the subnet.
    void addPool(const PoolPtr& pool);

    /// @brief Deletes all pools of specified type.
    ///
    /// This method is used for testing purposes only
    ///
    /// @param type type of pools to be deleted
    void delPools(Lease::Type type);

    /// @brief Returns a pool that specified address belongs to.
    ///
    /// This method uses binary search to retrieve the pool. Thus, the number
    /// of comparisons performed by this method is logarithmic in the number
    /// of pools belonging to a subnet.
    ///
    /// If there is no pool that the address belongs to (hint is invalid), other
    /// pool of specified type will be returned.
    ///
    /// With anypool set to true, this means give me a pool, preferably
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

    /// @brief Returns a pool that specified address belongs to with classes.
    ///
    /// Variant using only pools allowing given classes.
    ///
    /// @param type pool type that the pool is looked for
    /// @param client_classes client class list which must be allowed
    /// @param addr address that the returned pool should cover (optional)
    const PoolPtr getPool(Lease::Type type,
                          const ClientClasses& client_classes,
                          const isc::asiolink::IOAddress& addr) const;

    /// @brief Returns a pool without any address specified.
    ///
    /// @param type pool type that the pool is looked for
    /// @return returns one of the pools defined
    PoolPtr getAnyPool(Lease::Type type) {
        return (getPool(type, default_pool()));
    }

    /// @brief Returns the default address that will be used for pool selection.
    ///
    /// It must be implemented in derived classes (should return :: for Subnet6
    /// and 0.0.0.0 for Subnet4).
    virtual isc::asiolink::IOAddress default_pool() const = 0;

    /// @brief Returns all pools (const variant).
    ///
    /// The reference is only valid as long as the object that returned it.
    ///
    /// @param type lease type to be set
    /// @return a collection of all pools
    const PoolCollection& getPools(Lease::Type type) const;

    /// @brief Returns the number of possible leases for specified lease type.
    ///
    /// @param type type of the lease
    isc::util::uint128_t getPoolCapacity(Lease::Type type) const;

    /// @brief Returns the number of possible leases for specified lease type
    /// allowed for a client which belongs to classes.
    ///
    /// @param type type of the lease
    /// @param client_classes list of classes the client belongs to
    /// @return number of leases matching lease type and classes
    isc::util::uint128_t getPoolCapacity(Lease::Type type,
                                         const ClientClasses& client_classes) const;

    /// @brief Returns the number of possible leases for specified lease type
    /// allowed for a client which belongs to classes and matching selection
    /// criteria relative to provided hint prefix length.
    ///
    /// @param type type of the lease
    /// @param client_classes list of classes the client belongs to
    /// @param prefix_length_match type which indicates the selection criteria
    /// for the pools relative to the provided hint prefix length
    /// @param hint_prefix_length the hint prefix length that the client
    /// provided
    /// @return number of leases matching lease type and classes
    isc::util::uint128_t getPoolCapacity(Lease::Type type,
                                         const ClientClasses& client_classes,
                                         Allocator::PrefixLenMatchType prefix_length_match,
                                         uint8_t hint_prefix_length) const;

    /// @brief Returns textual representation of the subnet (e.g.
    /// "2001:db8::/64").
    ///
    /// @return textual representation
    virtual std::string toText() const;

    /// @brief Resets subnet-id counter to its initial value (1).
    ///
    /// This should be called during reconfiguration, before any new
    /// subnet objects are created. It will ensure that the subnet_id will
    /// be consistent between reconfigures.
    static void resetSubnetID() {
        static_id_ = 1;
    }

    /// @brief Retrieves pointer to a shared network associated with a subnet.
    ///
    /// By implementing it as a template function we overcome a need to
    /// include shared_network.h header file to specify return type explicitly.
    /// The header can't be included because it would cause circular dependency
    /// between subnet.h and shared_network.h.
    ///
    /// This method uses an argument to hold a return value to allow the compiler
    /// to infer the return type without a need to call this function with an
    /// explicit return type as template argument.
    ///
    /// @param [out] shared_network Pointer to the shared network where returned
    /// value should be assigned.
    ///
    /// @tparam Type of the shared network, i.e. @ref SharedNetwork4 or a
    /// @ref SharedNetwork6.
    template<typename SharedNetworkPtrType>
    void getSharedNetwork(SharedNetworkPtrType& shared_network) const {
        shared_network = boost::dynamic_pointer_cast<
            typename SharedNetworkPtrType::element_type>(parent_network_.lock());
    }

    /// @brief Assigns shared network to a subnet.
    ///
    /// This method replaces any shared network associated with a subnet with
    /// a new shared network.
    ///
    /// @param shared_network Pointer to a new shared network to be associated
    /// with the subnet.
    void setSharedNetwork(const NetworkPtr& shared_network) {
        parent_network_ = shared_network;
    }

    /// @brief Returns shared network name.
    ///
    /// @return shared network name
    std::string getSharedNetworkName() const {
        return (shared_network_name_);
    }

    /// @brief Sets new shared network name.
    ///
    /// In certain cases the subnet must be associated with the shared network
    /// but the shared network object is not available. In particular, subnets
    /// are returned from the configuration database with only names of the
    /// shared networks. The actual shared networks must be fetched from the
    /// database using a separate query. In order to not loose associations
    /// of subnets with shared networks, the configuration backends will use
    /// this method to store the shared network names. The servers will later
    /// use those names to associate subnets with shared network instances.
    ///
    /// @param shared_network_name New shared network name.
    void setSharedNetworkName(const std::string& shared_network_name) {
        shared_network_name_ = shared_network_name;
    }

    /// @brief Returns all pools (non-const variant).
    ///
    /// The reference is only valid as long as the object that returned it.
    ///
    /// @param type lease type to be set
    /// @return a collection of all pools
    PoolCollection& getPoolsWritable(Lease::Type type);

    /// @brief Returns lease allocator instance.
    ///
    /// An allocator is responsible for selecting leases from the subnet's
    /// pools. Each subnet has one allocator common for all pools belonging
    /// to the subnet. The allocation engine uses this function to get the
    /// current subnet allocator and uses it to select and offer an address.
    ///
    /// @param type lease type for which the allocator instance should be
    /// returned.
    /// @return Allocator instance.
    AllocatorPtr getAllocator(Lease::Type type) const;

    /// @brief Sets new allocator instance.
    ///
    /// If the server is configured to use a different allocator for the
    /// subnet, it can set the current allocator with this function.
    ///
    /// @param type lease type for which the allocator is set.
    /// @param allocator new allocator instance.
    void setAllocator(Lease::Type type, const AllocatorPtr& allocator);

    /// @brief Returns subnet-specific allocation state.
    ///
    /// The actual type of the state depends on the allocator type.
    ///
    /// @param type lease type for which the allocation state is returned.
    /// @return allocation state.
    SubnetAllocationStatePtr getAllocationState(Lease::Type type) const;

    /// @brief Sets subnet-specific allocation state.
    ///
    /// @param type lease type for which the allocation state is set.
    /// @param allocation_state allocation state instance.
    void setAllocationState(Lease::Type type, const SubnetAllocationStatePtr& allocation_state);

    /// @brief Instantiates the allocators and their states.
    ///
    /// It determines the types of the allocators to create using the list of
    /// the allocator types specified with the @c Network::setAllocatorType method.
    ///
    /// This function is called from the subnet parsers and after fetching
    /// the subnet configuration from a configuration backend.
    virtual void createAllocators() = 0;

    /// @brief Calls @c initAfterConfigure for each allocator.
    void initAllocatorsAfterConfigure();

protected:

    /// @brief Protected constructor.
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
    /// @param id arbitrary subnet id, value of 0 triggers autogeneration
    /// of subnet id
    Subnet(const isc::asiolink::IOAddress& prefix, uint8_t len,
           const SubnetID id);

    /// @brief virtual destructor.
    ///
    /// A virtual destructor is needed because other classes
    /// derive from this class.
    virtual ~Subnet() { };

    /// @brief keeps the subnet-id value.
    ///
    /// It is incremented every time a new Subnet object is created. It is reset
    /// (@ref resetSubnetID) every time reconfiguration
    /// occurs.
    ///
    /// Static value initialized in subnet.cc.
    static SubnetID static_id_;

    /// @brief returns the next unique Subnet-ID.
    ///
    /// This method generates and returns the next unique subnet-id.
    /// It is a strictly monotonously increasing value (1,2,3,...) for
    /// each new Subnet object created. It can be explicitly reset
    /// back to 1 during reconfiguration (@ref resetSubnetID).
    ///
    /// @return the next unique Subnet-ID
    static SubnetID generateNextID() {
        if (static_id_ == SUBNET_ID_MAX) {
            resetSubnetID();
        }

        return (static_id_++);
    }

    /// @brief Checks if used pool type is valid.
    ///
    /// Allowed type for Subnet4 is Pool::TYPE_V4.
    /// Allowed types for Subnet6 are Pool::TYPE_{IA,TA,PD}.
    /// This method is implemented in derived classes.
    ///
    /// @param type type to be checked
    /// @throw BadValue if invalid value is used
    virtual void checkType(Lease::Type type) const = 0;

    /// @brief Returns a sum of possible leases in all pools.
    ///
    /// @param pools list of pools
    /// @return sum of possible leases
    isc::util::uint128_t sumPoolCapacity(const PoolCollection& pools) const;

    /// @brief Returns a sum of possible leases in all pools allowing classes.
    ///
    /// @param pools list of pools
    /// @param client_classes list of classes
    /// @return sum of possible/allowed leases
    isc::util::uint128_t sumPoolCapacity(const PoolCollection& pools,
                                         const ClientClasses& client_classes) const;

    /// @brief Returns a sum of possible leases in all pools allowing classes
    /// and matching selection criteria relative to provided hint prefix length.
    ///
    /// @note This function should be called only for PD pools.
    ///
    /// @param pools list of pools
    /// @param client_classes list of classes
    /// @param prefix_length_match type which indicates the selection criteria
    /// for the pools relative to the provided hint prefix length
    /// @param hint_prefix_length the hint prefix length that the client
    /// provided
    /// @return sum of possible/allowed leases
    isc::util::uint128_t sumPoolCapacity(const PoolCollection& pools,
                                         const ClientClasses& client_classes,
                                         Allocator::PrefixLenMatchType prefix_length_match,
                                         uint8_t hint_prefix_length) const;

    /// @brief Checks if the specified pool overlaps with an existing pool.
    ///
    /// @param pool_type Pool type.
    /// @param pool Pointer to a pool for which the method should check if
    /// it overlaps with any existing pool within this subnet.
    ///
    /// @return true if pool overlaps with an existing pool of a specified
    /// type, false otherwise
    bool poolOverlaps(const Lease::Type& pool_type, const PoolPtr& pool) const;

    /// @brief Unparse a subnet object.
    ///
    /// @return A pointer to unparsed subnet configuration.
    virtual data::ElementPtr toElement() const;

    virtual std::string getLabel() const {
        std::stringstream ss;
        ss << "subnet-id " << id_;
        return (ss.str());
    }

    /// @brief Converts subnet prefix to a pair of prefix/length pair.
    ///
    /// IPv4 and IPv6 specific conversion functions should apply extra checks
    /// on the returned values, i.e. whether length is in range and the IP
    /// address has a valid type.
    ///
    /// @param prefix Prefix to be parsed.
    /// @throw BadValue if provided prefix is not valid.
    static std::pair<asiolink::IOAddress, uint8_t>
    parsePrefixCommon(const std::string& prefix);

    /// @brief subnet-id
    ///
    /// Subnet-id is a unique value that can be used to find or identify
    /// a Subnet4 or Subnet6.
    SubnetID id_;

    /// @brief collection of IPv4 or non-temporary IPv6 pools in that subnet.
    PoolCollection pools_;

    /// @brief collection of IPv6 temporary address pools in that subnet.
    PoolCollection pools_ta_;

    /// @brief collection of IPv6 prefix pools in that subnet.
    PoolCollection pools_pd_;

    /// @brief a prefix of the subnet.
    isc::asiolink::IOAddress prefix_;

    /// @brief a prefix length of the subnet.
    uint8_t prefix_len_;

    /// @brief Shared network name.
    std::string shared_network_name_;

    /// @brief Lease allocators used by the subnet.
    std::map<Lease::Type, AllocatorPtr> allocators_;

    /// @brief Holds subnet-specific allocation state.
    std::map<Lease::Type, SubnetAllocationStatePtr> allocation_states_;
};

/// @brief A generic pointer to either Subnet4 or Subnet6 object
typedef boost::shared_ptr<Subnet> SubnetPtr;


class Subnet4;

/// @brief A const pointer to a @c Subnet4 object.
typedef boost::shared_ptr<const Subnet4> ConstSubnet4Ptr;

/// @brief A pointer to a @c Subnet4 object.
typedef boost::shared_ptr<Subnet4> Subnet4Ptr;

/// @brief A configuration holder for IPv4 subnet.
///
/// This class represents an IPv4 subnet.
/// @note Subnet and Network use virtual inheritance to avoid
/// a diamond issue with UserContext
class Subnet4 : public Subnet, public Network4, public boost::enable_shared_from_this<Subnet4> {
public:

    /// @brief Constructor with all parameters.
    ///
    /// This constructor calls Subnet::Subnet, where subnet-id is generated.
    ///
    /// @param prefix Subnet4 prefix
    /// @param length prefix length
    /// @param t1 renewal timer (in seconds)
    /// @param t2 rebind timer (in seconds)
    /// @param valid_lifetime preferred lifetime of leases (in seconds)
    /// @param id arbitrary subnet id, no default value
    Subnet4(const isc::asiolink::IOAddress& prefix, uint8_t length,
            const util::Triplet<uint32_t>& t1,
            const util::Triplet<uint32_t>& t2,
            const util::Triplet<uint32_t>& valid_lifetime,
            const SubnetID id);

    /// @brief Factory function creating an instance of the @c Subnet4.
    ///
    /// This function should be used to create an instance of the subnet
    /// object within a hooks library in cases when the library may be
    /// unloaded before the object is destroyed. This ensures that the
    /// ownership of the object by the Kea process is retained.
    ///
    /// It associates the subnet with the default, iterative, allocator.
    /// Therefore, using this function should be preferred over the
    /// constructor whenever the subnet needs a default allocator.
    ///
    /// @param prefix Subnet4 prefix
    /// @param length prefix length
    /// @param t1 renewal timer (in seconds)
    /// @param t2 rebind timer (in seconds)
    /// @param valid_lifetime preferred lifetime of leases (in seconds)
    /// @param id arbitrary subnet id, no default value
    ///
    /// @return Pointer to the @c Subnet4 instance.
    static Subnet4Ptr
    create(const isc::asiolink::IOAddress& prefix, uint8_t length,
           const util::Triplet<uint32_t>& t1,
           const util::Triplet<uint32_t>& t2,
           const util::Triplet<uint32_t>& valid_lifetime,
           const SubnetID id);

    /// @brief Returns next subnet within shared network.
    ///
    /// If the current subnet doesn't belong to any shared network or if
    /// the next subnet is the same as first subnet (specified in the
    /// argument) a NULL pointer is returned.
    ///
    /// @param first_subnet Pointer to the subnet from which iterations have
    /// started.
    ///
    /// @return Pointer to the next subnet or NULL pointer if the next subnet
    /// is the first subnet or if the current subnet doesn't belong to a
    /// shared network.
    Subnet4Ptr getNextSubnet(const Subnet4Ptr& first_subnet) const;

    /// @brief Returns next subnet within shared network that matches
    /// client classes.
    ///
    /// @param first_subnet Pointer to the subnet from which iterations have
    /// started.
    /// @param client_classes List of classes that the client belongs to.
    /// The subnets not matching the classes aren't returned by this
    /// method.
    ///
    /// @return Pointer to the next subnet or NULL pointer if the next subnet
    /// is the first subnet or if the current subnet doesn't belong to a
    /// shared network.
    Subnet4Ptr getNextSubnet(const Subnet4Ptr& first_subnet,
                             const ClientClasses& client_classes) const;

    /// @brief Checks whether this subnet and parent shared network supports
    /// the client that belongs to specified classes.
    ///
    /// This method extends the @ref Network::clientSupported method with
    /// additional checks whether shared network owning this class supports
    /// the client belonging to specified classes. If the class doesn't
    /// belong to a shared network this method only checks if the subnet
    /// supports specified classes.
    ///
    /// @param client_classes List of classes the client belongs to.
    /// @return true if client can be supported, false otherwise.
    virtual bool
    clientSupported(const isc::dhcp::ClientClasses& client_classes) const;

    /// @brief Returns DHCP4o6 configuration parameters.
    ///
    /// This structure is always available. If the 4o6 is not enabled, its
    /// enabled_ field will be set to false.
    Cfg4o6& get4o6() {
        return (dhcp4o6_);
    }

    /// @brief Returns const DHCP4o6 configuration parameters.
    ///
    /// This structure is always available. If the 4o6 is not enabled, its
    /// enabled_ field will be set to false.
    const Cfg4o6& get4o6() const {
        return (dhcp4o6_);
    }

    /// @brief Unparse a subnet object.
    ///
    /// @return A pointer to unparsed subnet configuration.
    virtual data::ElementPtr toElement() const;

    /// @brief Instantiates the allocator and its state.
    ///
    /// It uses the type of the allocator specified with the
    /// @c Network::setAllocatorType method.
    ///
    /// This function is called from the subnet parsers and after fetching
    /// the subnet configuration from a configuration backend.
    virtual void createAllocators();

    /// @brief Converts subnet prefix to a pair of prefix/length pair.
    ///
    /// @param prefix Prefix to be parsed.
    /// @throw BadValue if provided invalid IPv4 prefix.
    static std::pair<asiolink::IOAddress, uint8_t>
    parsePrefix(const std::string& prefix);

private:

    /// @brief Deleted copy constructor.
    Subnet4(const Subnet4&) = delete;

    /// @brief Deleted assignment operator.
    Subnet4& operator=(const Subnet4&) = delete;

    /// @brief Returns default address for pool selection.
    ///
    /// @return ANY IPv4 address
    virtual isc::asiolink::IOAddress default_pool() const {
        return (isc::asiolink::IOAddress("0.0.0.0"));
    }

    /// @brief Checks if used pool type is valid.
    ///
    /// Allowed type for Subnet4 is Pool::TYPE_V4.
    ///
    /// @param type type to be checked
    /// @throw BadValue if invalid value is used
    virtual void checkType(Lease::Type type) const;

    /// @brief All the information related to DHCP4o6
    Cfg4o6 dhcp4o6_;
};

class Subnet6;

/// @brief A const pointer to a @c Subnet6 object.
typedef boost::shared_ptr<const Subnet6> ConstSubnet6Ptr;

/// @brief A pointer to a Subnet6 object
typedef boost::shared_ptr<Subnet6> Subnet6Ptr;

/// @brief A configuration holder for IPv6 subnet.
///
/// This class represents an IPv6 subnet.
/// @note Subnet and Network use virtual inheritance to avoid
/// a diamond issue with UserContext
class Subnet6 : public Subnet, public Network6, public boost::enable_shared_from_this<Subnet6> {
public:

    /// @brief Constructor with all parameters.
    ///
    /// This constructor calls Subnet::Subnet, where subnet-id is generated.
    ///
    /// @param prefix Subnet6 prefix
    /// @param length prefix length
    /// @param t1 renewal timer (in seconds)
    /// @param t2 rebind timer (in seconds)
    /// @param preferred_lifetime preferred lifetime of leases (in seconds)
    /// @param valid_lifetime preferred lifetime of leases (in seconds)
    /// @param id arbitrary subnet id, no default value
    /// autogeneration of subnet id
    Subnet6(const isc::asiolink::IOAddress& prefix, uint8_t length,
            const util::Triplet<uint32_t>& t1,
            const util::Triplet<uint32_t>& t2,
            const util::Triplet<uint32_t>& preferred_lifetime,
            const util::Triplet<uint32_t>& valid_lifetime,
            const SubnetID id);

    /// @brief Factory function creating an instance of the @c Subnet4.
    ///
    /// This function should be used to create an instance of the subnet
    /// object within a hooks library in cases when the library may be
    /// unloaded before the object is destroyed. This ensures that the
    /// ownership of the object by the Kea process is retained.
    ///
    /// It associates the subnet with the default, iterative, allocator.
    /// Therefore, using this function should be preferred over the
    /// constructor whenever the subnet needs a default allocator.
    ///
    /// @param prefix Subnet6 prefix
    /// @param length prefix length
    /// @param t1 renewal timer (in seconds)
    /// @param t2 rebind timer (in seconds)
    /// @param preferred_lifetime preferred lifetime of leases (in seconds)
    /// @param valid_lifetime preferred lifetime of leases (in seconds)
    /// @param id arbitrary subnet id, no default value
    ///
    /// @return Pointer to the @c Subnet6 instance.
    static Subnet6Ptr
    create(const isc::asiolink::IOAddress& prefix, uint8_t length,
           const util::Triplet<uint32_t>& t1,
           const util::Triplet<uint32_t>& t2,
           const util::Triplet<uint32_t>& preferred_lifetime,
           const util::Triplet<uint32_t>& valid_lifetime,
           const SubnetID id);

    /// @brief Returns next subnet within shared network.
    ///
    /// If the current subnet doesn't belong to any shared network or if
    /// the next subnet is the same as first subnet (specified in the
    /// arguments) a NULL pointer is returned.
    ///
    /// @param first_subnet Pointer to the subnet from which iterations have
    /// started.
    ///
    /// @return Pointer to the next subnet or NULL pointer if the next subnet
    /// is the first subnet or if the current subnet doesn't belong to a
    /// shared network.
    Subnet6Ptr getNextSubnet(const Subnet6Ptr& first_subnet) const;

    /// @brief Returns next subnet within shared network that matches
    /// client classes.
    ///
    /// @param first_subnet Pointer to the subnet from which iterations have
    /// started.
    /// @param client_classes List of classes that the client belongs to.
    /// The subnets not matching the classes aren't returned by this
    /// method.
    ///
    /// @return Pointer to the next subnet or NULL pointer if the next subnet
    /// is the first subnet or if the current subnet doesn't belong to a
    /// shared network.
    Subnet6Ptr getNextSubnet(const Subnet6Ptr& first_subnet,
                             const ClientClasses& client_classes) const;

    /// @brief Checks whether this subnet and parent shared network supports
    /// the client that belongs to specified classes.
    ///
    /// This method extends the @ref Network::clientSupported method with
    /// additional checks whether shared network owning this class supports
    /// the client belonging to specified classes. If the class doesn't
    /// belong to a shared network this method only checks if the subnet
    /// supports specified classes.
    ///
    /// @param client_classes List of classes the client belongs to.
    /// @return true if client can be supported, false otherwise.
    virtual bool
    clientSupported(const isc::dhcp::ClientClasses& client_classes) const;

    /// @brief Instantiates the allocators and their states.
    ///
    /// It determines the types of the allocators to create using the list of
    /// the allocator types specified with the @c Network::setAllocatorType method.
    ///
    /// This function is called from the subnet parsers and after fetching
    /// the subnet configuration from a configuration backend.
    virtual void createAllocators();

    /// @brief Unparse a subnet object.
    ///
    /// @return A pointer to unparsed subnet configuration.
    virtual data::ElementPtr toElement() const;

    /// @brief Converts subnet prefix to a pair of prefix/length pair.
    ///
    /// @param prefix Prefix to be parsed.
    /// @throw BadValue if provided invalid IPv4 prefix.
    static std::pair<asiolink::IOAddress, uint8_t>
    parsePrefix(const std::string& prefix);

private:

    /// @brief Deleted copy constructor.
    Subnet6(const Subnet6&) = delete;

    /// @brief Deleted assignment operator.
    Subnet6& operator=(const Subnet6&) = delete;

    /// @brief Returns default address for pool selection
    ///
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

};

/// @name Definition of the multi index container holding subnet information
///
//@{

/// @brief Tag for the index for searching by subnet identifier.
struct SubnetSubnetIdIndexTag { };

/// @brief Tag for the index for searching by subnet prefix.
struct SubnetPrefixIndexTag { };

/// @brief Tag for the index for searching by server identifier.
struct SubnetServerIdIndexTag { };

/// @brief Tag for the index for searching by subnet modification time.
struct SubnetModificationTimeIndexTag { };

/// @brief A simple collection of @c Subnet4 objects
///
/// This container provides a set of indexes which can be used to retrieve
/// subnets by subnet identifier and subnet prefix.
///
/// The random access index is used for direct iteration over the collection.
typedef boost::multi_index_container<
    // Multi index container holds pointers to the subnets.
    Subnet4Ptr,
    // The following holds all indexes.
    boost::multi_index::indexed_by<
        // First index allows for searching using subnet identifier.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<SubnetSubnetIdIndexTag>,
            boost::multi_index::const_mem_fun<Subnet, SubnetID, &Subnet::getID>
        >,
        // Second index allows for searching using an output from toText function.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<SubnetPrefixIndexTag>,
            boost::multi_index::const_mem_fun<Subnet, std::string, &Subnet::toText>
        >
    >
> Subnet4SimpleCollection;

/// @brief A collection of @c Subnet4 objects.
///
/// This container provides a set of indexes which can be used to retrieve
/// subnets by various properties.
///
/// This multi index container can hold pointers to @ref Subnet4
/// objects representing subnets. It provides indexes for subnet lookups
/// using subnet properties such as: subnet identifier,
/// subnet prefix or server identifier specified for a subnet. It also
/// provides a random access index which allows for using the container
/// like a vector.
///
/// The random access index is used by the DHCP servers which perform
/// a full scan on subnets to find the one that matches some specific
/// criteria for subnet selection.
///
/// The remaining indexes are used for searching for a specific subnet
/// as a result of receiving a command over the control API, e.g.
/// when 'subnet-get' command is received.
///
/// @todo We should consider optimizing subnet selection by leveraging
/// the indexing capabilities of this container, e.g. searching for
/// a subnet by interface name, relay address etc.
typedef boost::multi_index_container<
    // Multi index container holds pointers to the subnets.
    Subnet4Ptr,
    // The following holds all indexes.
    boost::multi_index::indexed_by<
        // First index allows for searching using subnet identifier.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<SubnetSubnetIdIndexTag>,
            boost::multi_index::const_mem_fun<Subnet, SubnetID, &Subnet::getID>
        >,
        // Second index allows for searching using an output from toText function.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<SubnetPrefixIndexTag>,
            boost::multi_index::const_mem_fun<Subnet, std::string, &Subnet::toText>
        >,

        // Third index allows for searching using an output from getServerId.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<SubnetServerIdIndexTag>,
            boost::multi_index::const_mem_fun<Network4, asiolink::IOAddress,
                                              &Network4::getServerId>
        >,

        // Forth index allows for searching using subnet modification time.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<SubnetModificationTimeIndexTag>,
            boost::multi_index::const_mem_fun<data::BaseStampedElement,
                                              boost::posix_time::ptime,
                                              &data::BaseStampedElement::getModificationTime>
        >
    >
> Subnet4Collection;

/// @brief A simple collection of @c Subnet6 objects
///
/// This container provides a set of indexes which can be used to retrieve
/// subnets by subnet identifier and subnet prefix.
///
/// The random access index is used for direct iteration over the collection.
typedef boost::multi_index_container<
    // Multi index container holds pointers to the subnets.
    Subnet6Ptr,
    // The following holds all indexes.
    boost::multi_index::indexed_by<
        // First index allows for searching using subnet identifier.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<SubnetSubnetIdIndexTag>,
            boost::multi_index::const_mem_fun<Subnet, SubnetID, &Subnet::getID>
        >,
        // Second index allows for searching using an output from toText function.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<SubnetPrefixIndexTag>,
            boost::multi_index::const_mem_fun<Subnet, std::string, &Subnet::toText>
        >
    >
> Subnet6SimpleCollection;

/// @brief A collection of @c Subnet6 objects
///
/// This container provides a set of indexes which can be used to retrieve
/// subnets by various properties.
///
/// This multi index container can hold pointers to @ref Subnet6 objects
/// representing subnets. It provides indexes for subnet lookups using
/// subnet properties such as: subnet identifier or subnet prefix. It
/// also provides a random access index which allows for using the
/// container like a vector.
///
/// The random access index is used by the DHCP servers which perform
/// a full scan on subnets to find the one that matches some specific
/// criteria for subnet selection.
///
/// The remaining indexes are used for searching for a specific subnet
/// as a result of receiving a command over the control API, e.g.
/// when 'subnet-get' command is received.
///
/// @todo We should consider optimizing subnet selection by leveraging
/// the indexing capabilities of this container, e.g. searching for
/// a subnet by interface name, relay address etc.
typedef boost::multi_index_container<
    // Multi index container holds pointers to the subnets.
    Subnet6Ptr,
    // The following holds all indexes.
    boost::multi_index::indexed_by<
        // First index allows for searching using subnet identifier.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<SubnetSubnetIdIndexTag>,
            boost::multi_index::const_mem_fun<Subnet, SubnetID, &Subnet::getID>
        >,
        // Second index allows for searching using an output from toText function.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<SubnetPrefixIndexTag>,
            boost::multi_index::const_mem_fun<Subnet, std::string, &Subnet::toText>
        >,
        // Third index allows for searching using subnet modification time.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<SubnetModificationTimeIndexTag>,
            boost::multi_index::const_mem_fun<data::BaseStampedElement,
                                              boost::posix_time::ptime,
                                              &data::BaseStampedElement::getModificationTime>
        >
    >
> Subnet6Collection;

/// @brief A class containing static convenience methods to fetch the subnets
/// from the containers.
///
/// @tparam ReturnPtrType Type of the returned object, i.e. @c Subnet4Ptr
/// or @c Subnet6Ptr.
/// @tparam CollectionType One of the @c Subnet4SimpleCollection,
/// @c Subnet4Collection, @c Subnet6SimpleCollection or @c Subnet6Collection.
template<typename ReturnPtrType, typename CollectionType>
class SubnetFetcher {
public:

    /// @brief Fetches subnets by id.
    ///
    /// @param collection Const reference to the collection from which the
    /// subnet is to be fetched.
    /// @param subnet_id Id of the subnet to be fetched.
    /// @return Pointer to the fetched subnet or null if no such subnet
    /// could be found.
    static ReturnPtrType get(const CollectionType& collection,
                             const SubnetID& subnet_id) {
        auto& index = collection.template get<SubnetSubnetIdIndexTag>();
        auto s = index.find(subnet_id);
        if (s != index.end()) {
            return (*s);
        }
        // No subnet found. Return null pointer.
        return (ReturnPtrType());
    }
};

/// @brief Type of the @c SubnetFetcher used for IPv4.
using SubnetFetcher4 = SubnetFetcher<Subnet4Ptr, Subnet4Collection>;

/// @brief Type of the @c SubnetFetcher used for IPv6.
using SubnetFetcher6 = SubnetFetcher<Subnet6Ptr, Subnet6Collection>;
//@}

/// @brief adapters for linking templates to qualified names
/// @{
namespace {

template <isc::util::DhcpSpace D>
struct AdapterSubnet {};

template <>
struct AdapterSubnet<isc::util::DHCPv4> {
    using type = Subnet4;
};

template <>
struct AdapterSubnet<isc::util::DHCPv6> {
    using type = Subnet6;
};

}  // namespace

template <isc::util::DhcpSpace D>
using SubnetT = typename AdapterSubnet<D>::type;

template <isc::util::DhcpSpace D>
using SubnetTPtr = boost::shared_ptr<SubnetT<D>>;
/// @}

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // SUBNET_H
