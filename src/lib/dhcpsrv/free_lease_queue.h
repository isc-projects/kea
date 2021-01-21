// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FREE_LEASE_QUEUE_H
#define FREE_LEASE_QUEUE_H

#include <asiolink/io_address.h>
#include <dhcpsrv/ip_range.h>
#include <exceptions/exceptions.h>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/shared_ptr.hpp>

#include <iterator>
#include <map>

namespace isc {
namespace dhcp {

/// @brief Queue holding free leases for various address and prefix ranges.
///
/// Free leases can be stored in this queue to provide the DHCP allocation
/// engine with the fast lookup mechanism for available leases. This avoids
/// costly lookup for available leases in the lease database backend when
/// the client's packet is being processed. Instead, when the server is being
/// configured, it iterates over the addresses and/or prefixes in respective
/// pools, verifies if leases exist for these addresses and/or prefixes and
/// for each of them for which it doesn't find the lease it creates an
/// appropriate entry in the queue.
///
/// This effectively moves the free lease lookup to the configuration phase.
/// When the server is going to allocate a new lease, it will make an
/// appropriate query to this queue to get the next available lease for the
/// given pool. If the server decides to use this lease, it is removed from
/// this queue. Conversely, when the lease expires (and is reclaimed) or is
/// released it is returned to this queue so it can be offered to a requesting
/// client at some later time.
///
/// The queue with free leases is optimized for two use cases. Firstly, it is
/// optimized to get the next available address or prefix efficiently. In order
/// to the get the next available lease the allocation engine can call the
/// @c FreeLeaseQueue::next function. The range from which the lease is to be
/// returned must be specified in the call. The range corresponds to the address
/// or prefix pool boundaries. The @c next function puts the returned lease
/// at the end of the queue. If the lease is rejected by the allocation engine
/// for any reason, e.g. conflict with existing host reservations, the allocation
/// engine simply calls @c next function again. It may need to perform multiple
/// calls to the @c next function until it gets the satifactionary lease.
/// However, it should be typically one call per allocation when no reservations
/// are present or there is a low number of in pool reservations. If the
/// allocation engine decides to allocate the returned lease, it must call
/// @c FreeLeaseQueue::use to remove this lease from the queue.
///
/// If the @c FreeLeaseQueue::pop method is used instead of @c next to get
/// the next available lease the returned lease is removed from the queue.
/// In that case, the allocation engine must not call @c FreeLeaseQueue::use
/// function when this lease is allocated. However, if the allocation engine
/// rejects this lease the @c FreeLeaseQueue::append must be called to return
/// the lease to the queue.
///
/// The second use case for which this queue is optimized is the lease
/// reclamation. This is the process by which expired leases are again made
/// available for allocation. The leases belonging to different pools expire at
/// various times. When the expired leases are reclaimed the server doesn't know
/// to which pools they belong. Since this queue associates free leases with
/// certain ranges it is important that this container can efficiently identify
/// the range. Once the range is identified, the reclaimed lease is appended to
/// the end of the queue for that range.
///
/// @todo Methods of this class should be called in thread safe context. Otherwise
/// they should be made thread safe.
class FreeLeaseQueue {
public:

    /// @brief Constructor.
    FreeLeaseQueue();

    /// @brief Adds new address range to the queue.
    ///
    /// The new range must not overlap with existing ranges.
    ///
    /// @param range the new range to be added.
    /// @throw BadValue if the new range overlaps with any of the existing ranges.
    void addRange(const AddressRange& range);

    /// @brief Adds new address range to the queue.
    ///
    /// This variant of the method accepts the address range as a pair of
    /// start/end arguments.
    ///
    /// @param start beginning of the new address range.
    /// @param end end of the new address range.
    /// @throw BadValue if the new range overlaps with any of the existing ranges.
    void addRange(const asiolink::IOAddress& start, const asiolink::IOAddress& end);

    /// @brief Adds new delegated prefix range to the queue.
    ///
    /// The new range must not overlap with existing ranges.
    ///
    /// @param range the new range to be added.
    /// @throw BadValue of the new range overlaps with any of the existing ranges.
    void addRange(const PrefixRange& range);

    /// @brief Adds new delegated prefix range to the queue.
    ///
    /// This variant of the method accepts the prefix range specified with three
    /// parameters: prefix, prefix length and delegated prefix length.
    ///
    /// @param prefix range prefix.
    /// @param prefix_length range prefix length.
    /// @param delegated_length delegated prefix length.
    /// @throw BadValue if the new range overlaps with any of the existing ranges.
    void addRange(const asiolink::IOAddress& prefix, const uint8_t prefix_length,
                  const uint8_t delegated_length);

    /// @brief Removes the range from the queue.
    ///
    /// It removes all free leases associated with the removed address range.
    ///
    /// @param range range to be removed.
    /// @tparam RangeType type of the range, i.e. @c Range or @c PrefixRange.
    /// @return true if the range existed and was removed.
    template<typename RangeType>
    bool removeRange(const RangeType& range) {
        return (ranges_.get<1>().erase(range.start_) > 0);
    }

    /// @brief Appends an address to the end of the queue for a range.
    ///
    /// This method is typically called when a lease expires and is reclaimed.
    /// The range is not specified by the caller. The method identifies
    /// appropriate address range for that address.
    ///
    /// @param address address to be appended to the range queue.
    /// @return true if the range was found and the address was appended,
    /// false otherwise.
    bool append(const asiolink::IOAddress& address);

    /// @brief Appends a delegated prefix to the end of the queue for a range.
    ///
    /// This method is typically called when a lease expires and is reclaimed.
    /// The range is not specified by the caller. The method identifies
    /// appropriate prefix range for that prefix.
    ///
    /// @param prefix delegated prefix to be appended to the range queue.
    /// @param delegated_length delegated prefix length.
    /// @return true if the range was found and the prefix was appended,
    /// false otherwise.
    bool append(const asiolink::IOAddress& prefix, const uint8_t delegated_length);

    /// @brief Appends an address to the end of the queue for a range.
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
    void append(const AddressRange& range, const asiolink::IOAddress& address);

    /// @brief Appends a prefix to the end of the queue for a range.
    ///
    /// This method is typically called upon server startup or reconfiguration.
    /// For each delegated prefix belonging to the pool for which there is no
    /// lease this method appends free delegated prefix at the end of the queue
    /// for the specified range.
    ///
    /// @param range specifies the prefix range to which the given prefix
    /// belongs.
    /// @param prefix delegated prefix to be appended to the range queue.
    /// @throw BadValue if the prefix does not belong to the specified
    /// range or if the given range does not exist.
    void append(const PrefixRange& range, const asiolink::IOAddress& prefix);

    /// @brief Appends an address or prefix to the end of the queue for a range.
    ///
    /// This variant of the @c append method is called upon server startup or
    /// reconfiguration. It is considered faster than the overload of this
    /// method taking the @c Range structure as an argument. The range is
    /// identified by the @c range_index which designates the range index
    /// in the queue returned by the @c getRangeIndex method. Use
    /// this method variant to add many addresses to the same range.
    ///
    /// @param range_index address range index returned by @c getRangeIndex.
    /// @param ip address or prefix to be appended to the range queue.
    /// @throw BadValue if the address or prefix does not belong to the
    /// specified range or if the given range does not exist.
    void append(const uint64_t range_index, const asiolink::IOAddress& ip);

    /// @brief Removes the specified address from the free addresses.
    ///
    /// This method should be called upon successful lease allocation for
    /// that address.
    ///
    /// @param range range from which the free address should be removed.
    /// @param address address to remove.
    /// @return true if the address was found and successfully removed,
    /// false otherwise.
    /// @throw BadValue if the range does not exist.
    bool use(const AddressRange& range, const asiolink::IOAddress& address);

    /// @brief Removes the specified delegated prefix from the free prefixes.
    ///
    /// This method should be called upon successful lease allocation for
    /// that delegated prefix.
    ///
    /// @param range range from which the free prefix should be removed.
    /// @param prefix prefix to remove.
    /// @return true if the prefix was found and successfully removed,
    /// false otherwise.
    /// @throw BadValue if the range does not exist.
    bool use(const PrefixRange& range, const asiolink::IOAddress& prefix);

    /// @brief Returns next free address or delegated prefix in the range.
    ///
    /// This address or delegated prefix is moved to the end of the queue
    /// for the range.
    ///
    /// @param range range for which next address is to be returned.
    /// @tparam RangeType type of the range, i.e. @c AddressRange or @c PrefixRange.
    /// @return Next free address or delegated prefix in that range.
    /// @throw BadValue if the range does not exist.
    template<typename RangeType>
    asiolink::IOAddress next(const RangeType& range) {
        return (popNextInternal(range, true));
    }

    /// @brief Pops and returns next free address or delegated prefix in the range.
    ///
    /// The address or delegated prefix is removed from the queue. If the caller,
    /// i.e. allocation engine decides to not use this address or prefix it
    /// should be appended to the queue using the @c append method.
    ///
    /// @param range range for which next address or prefix is to be returned.
    /// @tparam RangeType type of the range, i.e. @c AddressRange or @c PrefixRange.
    /// @return Next free address or delegated prefix in that range.
    /// @throw BadValue if the range does not exist.
    template<typename RangeType>
    asiolink::IOAddress pop(const RangeType& range) {
        return (popNextInternal(range, false));
    }

    /// @brief Returns range index.
    ///
    /// The range index designates the position of the range within the queue.
    /// Searching for a range using the index is faster than searching by the
    /// range itself because it uses random access index.
    ///
    /// @param range range which index is to be returned.
    /// @tparam RangeType type of the range, i.e. @c AddressRange or PrefixRange.
    /// @return range index.
    /// @throw BadValue if the range does not exist.
    template<typename RangeType>
    uint64_t getRangeIndex(const RangeType& range) const {
        auto cont = ranges_.get<1>().find(range.start_);
        if (cont == ranges_.get<1>().end()) {
            isc_throw(BadValue, "container for the specified range " << range.start_
                      << ":" << range.end_ << " does not exist");
        }
        return (std::distance(ranges_.get<2>().begin(), ranges_.project<2>(cont)));
    }

private:

    /// @brief Queue holding free leases for a range.
    ///
    /// This container holds free leases for a given range. It contains two
    /// indexes. The first index orders free leases by address values. The
    /// second index is sequential and serves as a double-ended queue from
    /// which leases are picked.
    typedef boost::multi_index_container<
        isc::asiolink::IOAddress,
        boost::multi_index::indexed_by<
            boost::multi_index::ordered_unique<
                boost::multi_index::identity<asiolink::IOAddress>
                >,
            boost::multi_index::sequenced<>
        >
    > Leases;

    /// Pointer to the queue of free leases for a range.
    typedef boost::shared_ptr<Leases> LeasesPtr;

    /// @brief Helper structure associating a range with the queue of
    /// free leases.
    struct RangeDescriptor {
        /// Range start.
        asiolink::IOAddress range_start_;
        /// Range end.
        asiolink::IOAddress range_end_;
        /// Delegated length (used in prefix delegation).
        uint8_t delegated_length_;
        /// Queue holding free addresses for the range.
        LeasesPtr leases_;
    };

    /// @brief Collection (container) of containers for various ranges.
    ///
    /// This container provides two indexes for searching a given range along with
    /// the appropriate container holding free leases. The first index is by the
    /// range start value. The second index is the random access index allowing
    /// faster access once the range index is known.
    typedef boost::multi_index_container<
        RangeDescriptor,
        boost::multi_index::indexed_by<
            boost::multi_index::ordered_unique<
                boost::multi_index::member<RangeDescriptor, asiolink::IOAddress,
                                           &RangeDescriptor::range_start_>
            >,
            boost::multi_index::hashed_unique<
                boost::multi_index::member<RangeDescriptor, asiolink::IOAddress,
                                           &RangeDescriptor::range_start_>
            >,
            boost::multi_index::random_access<>
        >
    > Ranges;

    /// @brief Checks if the specified address or delegated prefix is within the
    /// range.
    ///
    /// @param range range for which the check should be performed.
    /// @param ip address or delegated prefix for which the check should be performed.
    /// @param prefix boolean value indicating if the specified IP is an address or
    /// delegated prefix - used in error logging.
    /// @tparam RangeType type of the range used, i.e. @c AddressRange or @c PrefixRange.
    /// @throw BadValue of the address or delegated prefix does not belong to the range.
    template<typename RangeType>
    void checkRangeBoundaries(const RangeType& range, const asiolink::IOAddress& ip,
                              const bool prefix = false) const;

    /// @brief Checks if the specified address or prefix range overlaps with an
    /// existing range.
    ///
    /// @param start beginning of the range.
    /// @param end end of the range.
    /// @throw BadValue if the specified range overlaps with an existing range.
    void checkRangeOverlaps(const asiolink::IOAddress& start,
                            const asiolink::IOAddress& end) const;

    /// @brief Returns queue for a given address range.
    ///
    /// @param range range for which the container should be returned.
    /// @return Pointer to the container (if found).
    /// @throw BadValue if the specified range does not exist.
    LeasesPtr getLeases(const AddressRange& range) const;

    /// @brief Returns queue for a given prefix range.
    ///
    /// @param range range for which the container should be returned.
    /// @return Pointer to the container (if found).
    /// @throw BadValue if the specified range does not exist.
    LeasesPtr getLeases(const PrefixRange& range) const;

    /// @brief Returns descriptor for a given range index.
    ///
    /// The returned descriptor includes the range boundaries and also the
    /// pointer to the queue with free leases for the range.
    ///
    /// @param range_index index of the range which descriptor should be
    /// returned.
    /// @return Range descriptor if found.
    /// @throw BadValue if the range with the given index does not exist.
    RangeDescriptor getRangeDescriptor(const uint64_t range_index) const;

    /// @brief This is internal implementation of the @c next and @c pop
    /// methods.
    ///
    /// @param range range for which next address is to be returned.
    /// @param push boolean flag indicating if the value should be appended
    /// to the end of the queue upon return (if true) or removed from the
    /// queue (if false).
    /// @return Next free address in that range.
    /// @throw BadValue if the range does not exist.
    template<typename RangeType>
    asiolink::IOAddress popNextInternal(const RangeType& range, const bool push) {
        auto cont = getLeases(range);
        if (cont->empty()) {
            return (range.start_.isV4() ? asiolink::IOAddress::IPV4_ZERO_ADDRESS() :
                    asiolink::IOAddress::IPV6_ZERO_ADDRESS());
        }
        auto& idx = cont->template get<1>();
        auto next = idx.front();
        idx.pop_front();
        if (push) {
            idx.push_back(next);
        }
        return (next);
    }

    /// @brief Holds a collection of containers with free leases for each
    /// address range.
    Ranges ranges_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // FREE_LEASE_QUEUE_H
