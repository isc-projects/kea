// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/pool.h>
#include <dhcpsrv/triplet.h>

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


/// @brief Unique indentifier for a subnet (both v4 and v6)
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
        OptionDescriptor(OptionPtr& opt, bool persist)
            : option(opt), persistent(persist) {};

        /// @brief Constructor
        ///
        /// @param persist if true option is always sent.
        OptionDescriptor(bool persist)
            : option(OptionPtr()), persistent(persist) {};
    };

    /// @brief Extractor class to extract key with another key.
    ///
    /// This class solves the problem of accessing index key values
    /// that are stored in objects nested in other objects.
    /// Each OptionDescriptor structure contains the OptionPtr object.
    /// The value retured by one of its accessors (getType) is used
    /// as an indexing value in the multi_index_container defined below.
    /// There is no easy way to mark that value returned by Option::getType
    /// should be an index of this multi_index_container. There are standard
    /// key extractors such as 'member' or 'mem_fun' but they are not
    /// sufficient here. The former can be used to mark that member of
    /// the structure that is held in the container should be used as an
    /// indexing value. The latter can be used if the indexing value is
    /// a product of the class being held in the container. In this complex
    /// scenario when the indexing value is a product of the function that
    /// is wrapped by the structure, this new extractor template has to be
    /// defined. The template class provides a 'chain' of two extractors
    /// to access the value returned by nested object and to use it as
    /// indexing value.
    /// For some more examples of complex keys see:
    /// http://www.cs.brown.edu/~jwicks/boost/libs/multi_index/doc/index.html
    ///
    /// @tparam KeyExtractor1 extractor used to access data in
    /// OptionDescriptor::option
    /// @tparam KeyExtractor2 extractor used to access
    /// OptionDescriptor::option member.
    template<typename KeyExtractor1, typename KeyExtractor2>
    class KeyFromKey {
    public:
        typedef typename KeyExtractor1::result_type result_type;

        /// @brief Constructor.
        KeyFromKey()
            : key1_(KeyExtractor1()), key2_(KeyExtractor2()) { };

        /// @brief Extract key with another key.
        ///
        /// @param arg the key value.
        ///
        /// @tparam key value type.
        template<typename T>
        result_type operator() (T& arg) const {
            return (key1_(key2_(arg)));
        }
    private:
        KeyExtractor1 key1_; ///< key 1.
        KeyExtractor2 key2_; ///< key 2.
    };

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
                // KeyFromKey is the index key extractor that allows accessing
                // option type being held by the OptionPtr through
                // OptionDescriptor structure.
                KeyFromKey<
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

    /// Type of the index #1 - option type.
    typedef OptionContainer::nth_index<1>::type OptionContainerTypeIndex;
    /// Pair of iterators to represent the range of options having the
    /// same option type value. The first element in this pair represents
    /// the begining of the range, the second element represents the end.
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
    ///
    /// @throw isc::BadValue if invalid option provided.
    void addOption(OptionPtr& option, bool persistent = false);

    /// @brief Delete all options configured for the subnet.
    void delOptions();

    /// @brief checks if the specified address is in pools
    ///
    /// Note the difference between inSubnet() and inPool(). For a given
    /// subnet (e.g. 2001::/64) there may be one or more pools defined
    /// that may or may not cover entire subnet, e.g. pool 2001::1-2001::10).
    /// inPool() returning true implies inSubnet(), but the reverse implication
    /// is not always true. For the given example, 2001::1234:abcd would return
    /// true for inSubnet(), but false for inPool() check.
    ///
    /// @param addr this address will be checked if it belongs to any pools in
    ///        that subnet
    /// @return true if the address is in any of the pools
    bool inPool(const isc::asiolink::IOAddress& addr) const;

    /// @brief return valid-lifetime for addresses in that prefix
    Triplet<uint32_t> getValid() const {
        return (valid_);
    }

    /// @brief returns T1 (renew timer), expressed in seconds
    Triplet<uint32_t> getT1() const {
        return (t1_);
    }

    /// @brief returns T2 (rebind timer), expressed in seconds
    Triplet<uint32_t> getT2() const {
        return (t2_);
    }

    /// @brief Return a collection of options.
    ///
    /// @return reference to collection of options configured for a subnet.
    /// The returned reference is valid as long as the Subnet object which
    /// returned it still exists.
    const OptionContainer& getOptions() const {
        return (options_);
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
    /// @return address that was last tried from this pool
    isc::asiolink::IOAddress getLastAllocated() const {
        return (last_allocated_);
    }

    /// @brief sets the last address that was tried from this pool
    ///
    /// This method sets the last address that was attempted to be allocated
    /// from this subnet. This is used as helper information for the next
    /// iteration of the allocation algorithm.
    ///
    /// @todo: Define map<SubnetID, IOAddress> somewhere in the
    ///        AllocEngine::IterativeAllocator and keep the data there
    void setLastAllocated(const isc::asiolink::IOAddress& addr) {
        last_allocated_ = addr;
    }

    /// @brief returns unique ID for that subnet
    /// @return unique ID for that subnet
    SubnetID getID() const { return (id_); }

    /// @brief returns subnet parameters (prefix and prefix length)
    ///
    /// @return (prefix, prefix length) pair
    std::pair<isc::asiolink::IOAddress, uint8_t> get() const {
        return (std::make_pair(prefix_, prefix_len_));
    }

    /// @brief Adds a new pool.
    /// @param pool pool to be added
    void addPool(const PoolPtr& pool);

    /// @brief Returns a pool that specified address belongs to
    ///
    /// @param addr address that the returned pool should cover (optional)
    /// @return Pointer to found Pool4 or Pool6 (or NULL)
    PoolPtr getPool(isc::asiolink::IOAddress addr);

    /// @brief Returns a pool without any address specified
    /// @return returns one of the pools defined
    PoolPtr getPool() {
        return (getPool(default_pool()));
    }

    /// @brief Returns the default address that will be used for pool selection
    ///
    /// It must be implemented in derived classes (should return :: for Subnet6
    /// and 0.0.0.0 for Subnet4)
    virtual isc::asiolink::IOAddress default_pool() const = 0;

    /// @brief returns all pools
    ///
    /// The reference is only valid as long as the object that returned it.
    ///
    /// @return a collection of all pools
    const PoolCollection& getPools() const {
        return pools_;
    }

    /// @brief returns textual representation of the subnet (e.g. "2001:db8::/64")
    ///
    /// @return textual representation
    virtual std::string toText() const;

protected:
    /// @brief protected constructor
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

    /// @brief Check if option is valid and can be added to a subnet.
    ///
    /// @param option option to be validated.
    virtual void validateOption(const OptionPtr& option) const = 0;

    /// @brief subnet-id
    ///
    /// Subnet-id is a unique value that can be used to find or identify
    /// a Subnet4 or Subnet6.
    SubnetID id_;

    /// @brief collection of pools in that list
    PoolCollection pools_;

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

    /// @brief a collection of DHCP options configured for a subnet.
    OptionContainer options_;

    /// @brief last allocated address
    ///
    /// This is the last allocated address that was previously allocated from
    /// this particular subnet. Some allocation algorithms (e.g. iterative) use
    /// that value, others do not. It should be noted that although the value
    /// is usually correct, there are cases when it is invalid, e.g. after
    /// removing a pool, restarting or changing allocation algorithms. For
    /// that purpose it should be only considered a help that should not be
    /// fully trusted.
    isc::asiolink::IOAddress last_allocated_;
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

    /// @brief collection of pools in that list
    Pool6Collection pools_;

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
