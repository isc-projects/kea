// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <boost/shared_ptr.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/member.hpp>

#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <dhcpsrv/key_from_key.h>
#include <dhcpsrv/option_space_container.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/triplet.h>
#include <dhcpsrv/lease.h>

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

    /// @brief Option descriptor.
    ///
    /// Option descriptor holds information about option configured for
    /// a particular subnet. This information comprises the actual option
    /// instance and information whether this option is sent to DHCP client
    /// only on request (persistent = false) or always (persistent = true).
    struct OptionDescriptor {
        /// Option instance.
        OptionPtr option;
        /// Persistent flag, if true option is always sent to the client,
        /// if false option is sent to the client on request.
        bool persistent;

        /// @brief Constructor.
        ///
        /// @param opt option
        /// @param persist if true option is always sent.
        OptionDescriptor(const OptionPtr& opt, bool persist)
            : option(opt), persistent(persist) {};

        /// @brief Constructor
        ///
        /// @param persist if true option is always sent.
        OptionDescriptor(bool persist)
            : option(OptionPtr()), persistent(persist) {};
    };

    /// A pointer to option descriptor.
    typedef boost::shared_ptr<OptionDescriptor> OptionDescriptorPtr;

    /// @brief Multi index container for DHCP option descriptors.
    ///
    /// This container comprises three indexes to access option
    /// descriptors:
    /// - sequenced index: used to access elements in the order they
    /// have been added to the container,
    /// - option type index: used to search option descriptors containing
    /// options with specific option code (aka option type).
    /// - persistency flag index: used to search option descriptors with
    /// 'persistent' flag set to true.
    ///
    /// This container is the equivalent of three separate STL containers:
    /// - std::list of all options,
    /// - std::multimap of options with option code used as a multimap key,
    /// - std::multimap of option descriptors with option persistency flag
    /// used as a multimap key.
    /// The major advantage of this container over 3 separate STL containers
    /// is automatic synchronization of all indexes when elements are added,
    /// removed or modified in the container. With separate containers,
    /// the synchronization would have to be guaranteed by the Subnet class
    /// code. This would increase code complexity and presumably it would
    /// be much harder to add new search criteria (indexes).
    ///
    /// @todo we may want to search for options using option spaces when
    /// they are implemented.
    ///
    /// @see http://www.boost.org/doc/libs/1_51_0/libs/multi_index/doc/index.html
    typedef boost::multi_index_container<
        // Container comprises elements of OptionDescriptor type.
        OptionDescriptor,
        // Here we start enumerating various indexes.
        boost::multi_index::indexed_by<
            // Sequenced index allows accessing elements in the same way
            // as elements in std::list.
            // Sequenced is an index #0.
            boost::multi_index::sequenced<>,
            // Start definition of index #1.
            boost::multi_index::hashed_non_unique<
                // KeyFromKeyExtractor is the index key extractor that allows
                // accessing option type being held by the OptionPtr through
                // OptionDescriptor structure.
                KeyFromKeyExtractor<
                    // Use option type as the index key. The type is held
                    // in OptionPtr object so we have to call Option::getType
                    // to retrieve this key for each element.
                    boost::multi_index::const_mem_fun<
                        Option,
                        uint16_t,
                        &Option::getType
                    >,
                    // Indicate that OptionPtr is a member of
                    // OptionDescriptor structure.
                    boost::multi_index::member<
                        OptionDescriptor,
                        OptionPtr,
                        &OptionDescriptor::option
                    >
                 >
            >,
            // Start definition of index #2.
            // Use 'persistent' struct member as a key.
            boost::multi_index::hashed_non_unique<
                boost::multi_index::member<
                    OptionDescriptor,
                    bool,
                    &OptionDescriptor::persistent
                >
            >
        >
    > OptionContainer;

    // Pointer to the OptionContainer object.
    typedef boost::shared_ptr<OptionContainer> OptionContainerPtr;
    /// Type of the index #1 - option type.
    typedef OptionContainer::nth_index<1>::type OptionContainerTypeIndex;
    /// Pair of iterators to represent the range of options having the
    /// same option type value. The first element in this pair represents
    /// the beginning of the range, the second element represents the end.
    typedef std::pair<OptionContainerTypeIndex::const_iterator,
                      OptionContainerTypeIndex::const_iterator> OptionContainerTypeRange;
    /// Type of the index #2 - option persistency flag.
    typedef OptionContainer::nth_index<2>::type OptionContainerPersistIndex;

    /// @brief checks if specified address is in range
    bool inRange(const isc::asiolink::IOAddress& addr) const;

    /// @brief Add new option instance to the collection.
    ///
    /// @param option option instance.
    /// @param persistent if true, send an option regardless if client
    /// requested it or not.
    /// @param option_space name of the option space to add an option to.
    ///
    /// @throw isc::BadValue if invalid option provided.
    void addOption(const OptionPtr& option, bool persistent,
                   const std::string& option_space);

    void addVendorOption(const OptionPtr& option, bool persistent,
                         uint32_t vendor_id);

    /// @brief Delete all options configured for the subnet.
    void delOptions();

    void delVendorOptions();

    /// @brief checks if the specified address is in pools
    ///
    /// Note the difference between inSubnet() and inPool(). For a given
    /// subnet (e.g. 2001::/64) there may be one or more pools defined
    /// that may or may not cover entire subnet, e.g. pool 2001::1-2001::10).
    /// inPool() returning true implies inSubnet(), but the reverse implication
    /// is not always true. For the given example, 2001::1234:abcd would return
    /// true for inSubnet(), but false for inPool() check.
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

    /// @brief Return a collection of option descriptors.
    ///
    /// @param option_space name of the option space.
    ///
    /// @return pointer to collection of options configured for a subnet.
    OptionContainerPtr
    getOptionDescriptors(const std::string& option_space) const;

    OptionContainerPtr
    getVendorOptionDescriptors(uint32_t vendor_id) const;

    /// @brief Return single option descriptor.
    ///
    /// @param option_space name of the option space.
    /// @param option_code code of the option to be returned.
    ///
    /// @return option descriptor found for the specified option space
    /// and option code.
    OptionDescriptor
    getOptionDescriptor(const std::string& option_space,
                        const uint16_t option_code);

    OptionDescriptor
    getVendorOptionDescriptor(uint32_t vendor_id, uint16_t option_code);

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

    /// @brief Adds a new pool.
    /// @param pool pool to be added
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
    /// By making the constructor protected, we make sure that noone will
    /// ever instantiate that class. Pool4 and Pool6 should be used instead.
    Subnet(const isc::asiolink::IOAddress& prefix, uint8_t len,
           const Triplet<uint32_t>& t1,
           const Triplet<uint32_t>& t2,
           const Triplet<uint32_t>& valid_lifetime);

    /// @brief virtual destructor
    ///
    /// A virtual destructor is needed because other classes
    /// derive from this class.
    virtual ~Subnet() { };

    /// @brief returns the next unique Subnet-ID
    ///
    /// @return the next unique Subnet-ID
    static SubnetID getNextID() {
        static SubnetID id = 0;
        return (id++);
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

    /// @brief Check if option is valid and can be added to a subnet.
    ///
    /// @param option option to be validated.
    virtual void validateOption(const OptionPtr& option) const = 0;

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

private:

    /// A collection of option spaces grouping option descriptors.
    typedef OptionSpaceContainer<OptionContainer,
        OptionDescriptor, std::string> OptionSpaceCollection;

    typedef OptionSpaceContainer<OptionContainer,
        OptionDescriptor, uint32_t> VendorOptionSpaceCollection;

    OptionSpaceCollection option_spaces_;

    VendorOptionSpaceCollection vendor_option_spaces_;
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
    /// @param prefix Subnet4 prefix
    /// @param length prefix length
    /// @param t1 renewal timer (in seconds)
    /// @param t2 rebind timer (in seconds)
    /// @param valid_lifetime preferred lifetime of leases (in seconds)
    Subnet4(const isc::asiolink::IOAddress& prefix, uint8_t length,
            const Triplet<uint32_t>& t1,
            const Triplet<uint32_t>& t2,
            const Triplet<uint32_t>& valid_lifetime);

protected:

    /// @brief Check if option is valid and can be added to a subnet.
    ///
    /// @param option option to be validated.
    ///
    /// @throw isc::BadValue if provided option is invalid.
    virtual void validateOption(const OptionPtr& option) const;

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
};

/// @brief A pointer to a Subnet4 object
typedef boost::shared_ptr<Subnet4> Subnet4Ptr;

/// @brief A collection of Subnet6 objects
typedef std::vector<Subnet4Ptr> Subnet4Collection;


/// @brief A configuration holder for IPv6 subnet.
///
/// This class represents an IPv6 subnet.
class Subnet6 : public Subnet {
public:

    /// @brief Constructor with all parameters
    ///
    /// @param prefix Subnet6 prefix
    /// @param length prefix length
    /// @param t1 renewal timer (in seconds)
    /// @param t2 rebind timer (in seconds)
    /// @param preferred_lifetime preferred lifetime of leases (in seconds)
    /// @param valid_lifetime preferred lifetime of leases (in seconds)
    Subnet6(const isc::asiolink::IOAddress& prefix, uint8_t length,
            const Triplet<uint32_t>& t1,
            const Triplet<uint32_t>& t2,
            const Triplet<uint32_t>& preferred_lifetime,
            const Triplet<uint32_t>& valid_lifetime);

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

protected:

    /// @brief Check if option is valid and can be added to a subnet.
    ///
    /// @param option option to be validated.
    ///
    /// @throw isc::BadValue if provided option is invalid.
    virtual void validateOption(const OptionPtr& option) const;

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
};

/// @brief A pointer to a Subnet6 object
typedef boost::shared_ptr<Subnet6> Subnet6Ptr;

/// @brief A collection of Subnet6 objects
typedef std::vector<Subnet6Ptr> Subnet6Collection;

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // SUBNET_T
