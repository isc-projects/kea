// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FREE_LEASE_QUEUE_H
#define FREE_LEASE_QUEUE_H

#include <asiolink/io_address.h>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/shared_ptr.hpp>

#include <map>

namespace isc {
namespace dhcp {

/// @brief Container holding free leases for various address ranges.
///
/// Free leases can be stored in this container to provide the DHCP
/// allocation engine with the fast lookup mechanism for available
/// leases. This avoids costly lookup for available leases in the
/// lease database backend when the client's packet is being processed.
/// Instead, when the server is being configured, it iterates over
/// the addresses in respective address pools, verifies if leases
/// exist for these addresses and for each addresses for which it
/// doesn't find the lease it creates an appropriate entry in this
/// container.
///
/// This effectively moves the free lease lookup to the configuration
/// phase. When the server is going to allocate a new lease, it will
/// make an appropriate query to this container to get the next
/// available lease for the given pool. If the server decides to
/// use this lease, it is removed from this container. Conversely,
/// when the lease expires (and is reclaimed) or is released it is
/// returned to this container so as it can be offered to a
/// requesting client at some later time.
///
/// The container with free leases is optimized for two use cases.
/// Firstly, it is optimized to get the next available address
/// efficiently. In order to the get the next available address one
/// should call the @c FreeLeaseQueue::next function. The range
/// from which the address is to be returned must be specified in
/// the call. The range corresponds to the address pool boundaries.
/// If the address returned is rejected by the allocation engine
/// for any reason, e.g. conflict with existing host reservations,
/// the address goes to the end of the queue for that address
/// range. The allocation engine may need to perform multiple
/// calls to the @c next function until it gets the satifactionary
/// IP address. However, it should be typically one call per
/// allocation when no reservations are present or there is a low
/// number of in pool reservations.
///
/// The second use case for which this container is optimized is
/// the lease reclamation. This is the process by which expired
/// leases are again made available for allocation. The leases
/// belonging to different pools expire at various times. When the
/// expired leases are reclaimed the server doesn't know to which
/// pools they belong. Since this container associates free leases
/// with certain address ranges it is important that this container
/// can efficiently identify the range. Once the range is identified,
/// the reclaimed lease is appended at the end of the queue for that
/// range.
class FreeLeaseQueue {
public:

    /// @brief Structure representing address range in the @c FreeLeaseQueue.
    struct Range {
        /// IP address denoting the start of the address range.
        asiolink::IOAddress start_;
        /// IP address denoting the end of the address range.
        asiolink::IOAddress end_;

        /// @brief Constructor.
        ///
        /// @param start beginning of the address range.
        /// @param end end of the address range.
        /// @throw BadValue if the @c start is greater than the end or
        /// specified boundaries do not belong to the same family.
        Range(const asiolink::IOAddress& start, const asiolink::IOAddress& end);
    };

    /// @brief Constructor.
    FreeLeaseQueue();

    /// @brief Adds new address range to the container.
    ///
    /// The new range must not overlap with existing address ranges.
    ///
    /// @param range the new range to be added.
    /// @throw BadValue if the new range overlaps with any of the existing ranges.
    void addRange(const Range& range);

    /// @brief Adds new address range to the container.
    ///
    /// This variant of the method accepts the address range as a pair of
    /// start/end arguments.
    ///
    /// @param start beginning of the new address range.
    /// @param end end of the new address range.
    /// @throw BadValue if the new range overlaps with any of the existing ranges.
    void addRange(const asiolink::IOAddress& start, const asiolink::IOAddress& end);

    /// @brief Removes the range from the container.
    ///
    /// It removes all free leases associated with the removed address range.
    ///
    /// @return true if the address range existed and was removed.
    bool removeRange(const Range& range);

    /// @brief Appends an address at the end of the queue for a range.
    ///
    /// This method is typically called when a lease expires and is reclaimed.
    /// The range is not specified by the caller. The method identifies
    /// appropriate address range for that address.
    ///
    /// @param address address to be appended to the range queue.
    /// @return true if the range was found and the address was appended,
    /// false otherwise.
    bool append(const asiolink::IOAddress& address);

    /// @brief Appends an address at the end of the queue for a range.
    ///
    /// This method is typically called upon server startup or reconfiguration.
    /// For each address belonging to the pool for which there is no lease
    /// this method appends free address at the end of the queue for the
    /// specified range.
    ///
    /// @param range specifies the address range to which the given address
    /// belongs.
    /// @param address address to be appended to the range queue.
    /// @throw BadValue if the address does not belong to the specified
    /// range or if the given range does not exist.
    void append(const Range& range, const asiolink::IOAddress& address);

    /// @brief Appends an address at the end of the queue for a range.
    ///
    /// This variant of the @c append method is called upon server startup or
    /// reconfiguration. It is considered faster than the overload of this
    /// method taking the @c Range structure as an argument. The range is
    /// identified by the @c range_index which designates the range index
    /// in the container returned by the @c getRangeIndex method. Use
    /// this method variant to add many addresses to the same range.
    ///
    /// @param range_index address range index returned by @c getRangeIndex.
    /// @param address address to be appended to the range queue.
    /// @throw BadValue if the address does not belong to the specified
    /// range or if the given range does not exist.
    void append(const uint64_t range_index, const asiolink::IOAddress& address);

    /// @brief Removes the specified address from the free addresses.
    ///
    /// This method should be called upon successful lease allocation for
    /// that address.
    ///
    /// @param range from which the free address should be removed.
    /// @return true if the address was found and successfully removed,
    /// false otherwise.
    /// @throw BadValue if the range does not exist.
    bool use(const Range& range, const asiolink::IOAddress& address);

    /// @brief Returns next free address in the range.
    ///
    /// This address is moved to the end of the queue for the range.
    ///
    /// @param range range for which next address is to be returned.
    /// @return Next free address in that range.
    /// @throw BadValue if the range does not exist.
    asiolink::IOAddress next(const Range& range);

    /// @brief Pops and returns next free address in the range.
    ///
    /// The address is removed from the queue. If the caller, i.e. allocation
    /// engine decides to not use this address it should be appended to
    /// the queue using the @c append method.
    ///
    /// @param range range for which next address is to be returned.
    /// @return Next free address in that range.
    /// @throw BadValue if the range does not exist.
    asiolink::IOAddress pop(const Range& range);

    /// @brief Returns range index.
    ///
    /// The range index designates the position of the range within the container.
    /// Searching for a range using the index is faster than searching by the
    /// range itself because it uses random access index.
    ///
    /// @param range range which index is to be returned.
    /// @return range index.
    /// @throw BadValue if the range does not exist.
    uint64_t getRangeIndex(const Range& range) const;

private:

    /// @brief Container holding free leases for a range.
    ///
    /// This container holds free addresses for a given address range.
    /// It contains two indexes. The first index orders free addresses
    /// by address values. The second index is sequential and serves
    /// as a double-ended queue from which addresses are picked.
    typedef boost::multi_index_container<
        isc::asiolink::IOAddress,
        boost::multi_index::indexed_by<
            boost::multi_index::ordered_unique<
                boost::multi_index::identity<asiolink::IOAddress>
                >,
            boost::multi_index::sequenced<>
        >
    > Container;

    /// Pointer to the container of free addresses for a range.
    typedef boost::shared_ptr<Container> ContainerPtr;

    /// @brief Helper structure associating a range with the container of
    /// free addresses.
    struct ContainerDescriptor {
        /// Range start.
        asiolink::IOAddress range_start_;
        /// Range end.
        asiolink::IOAddress range_end_;
        /// Container holding free addresses for the range.
        ContainerPtr container_;
    };

    /// @brief Collection (container) of containers for various address ranges.
    ///
    /// This container provides two indexes for searching a given address range
    /// along with the appropriate container holding free leases. The first index
    /// is by the range start value. The second index is the random access index
    /// allowing faster access once the range index is known.
    typedef boost::multi_index_container<
        ContainerDescriptor,
        boost::multi_index::indexed_by<
            boost::multi_index::ordered_unique<
                boost::multi_index::member<ContainerDescriptor, asiolink::IOAddress,
                                           &ContainerDescriptor::range_start_>
            >,
            boost::multi_index::hashed_unique<
                boost::multi_index::member<ContainerDescriptor, asiolink::IOAddress,
                                           &ContainerDescriptor::range_start_>
            >,
            boost::multi_index::random_access<>
        >
    > Containers;

    /// @brief Returns container for a given address range.
    ///
    /// @param range range for which the container should be returned.
    /// @return Pointer to the container (if found).
    /// @throw BadValue if the specified range does not exist.
    ContainerPtr getContainer(const Range& range);

    /// @brief Returns container descriptor for a given range index.
    ///
    /// The returned descriptor includes the range boundaries and also the
    /// pointer to the container with free leases for the range.
    ///
    /// @param range_index index of the range which descriptor should be
    /// returned.
    /// @return Range descriptor if found.
    /// @throw BadValue if the range with the given index does not exist.
    ContainerDescriptor getContainerDescriptor(const uint64_t range_index);

    /// @brief This is internal implemenation of the @c next and @c pop
    /// methods.
    ///
    /// @param range range for which next address is to be returned.
    /// @param push boolean flag indicating if the value should be appended
    /// to the end of the queue upon return (if true) or removed from the
    /// queue (if false).
    /// @return Next free address in that range.
    /// @throw BadValue if the range does not exist.
    asiolink::IOAddress popNextInternal(const Range& range, const bool push);

    /// @brief Holds a collection of containers with free leases for each
    /// address range.
    Containers containers_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // FREE_LEASE_QUEUE_H
