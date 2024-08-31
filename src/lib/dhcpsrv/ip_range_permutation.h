// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IP_RANGE_PERMUTATION_H
#define IP_RANGE_PERMUTATION_H

#include <asiolink/io_address.h>
#include <dhcpsrv/ip_range.h>
#include <util/bigints.h>

#include <boost/shared_ptr.hpp>

#include <map>
#include <random>

namespace isc {
namespace dhcp {

/// @brief Random IP address/prefix permutation based on Fisher-Yates shuffle.
///
/// This class is used to shuffle IP addresses or delegated prefixes within
/// the specified range. It is following the Fisher-Yates shuffle algorithm
/// described in https://en.wikipedia.org/wiki/Fisher–Yates_shuffle.
///
/// The original algorithm is modified to keep the minimal information about
/// the current state of the permutation and relies on the caller to collect
/// and store the next available value. In other words, the generated and
/// already returned random values are not stored by this class.
///
/// The class assumes that initially the IP addresses or delegated prefixes
/// in the specified range are in increasing order. Suppose we're dealing with
/// the following address range: 192.0.2.1-192.0.2.5. Therefore our addresses
/// are initially ordered like this: a[0]=192.0.2.1, a[1]=192.0.2.2 ...,
/// a[4]=192.0.2.5. The algorithm starts from the end of that range, i.e. i=4,
/// so a[i]=192.0.2.5. A random value from the range of [0..i-1] is picked,
/// i.e. a value from the range of [0..3]. Let's say it is 1. This value initially
/// corresponds to the address a[1]=192.0.2.2. In the original algorithm the
/// value of a[1] is swapped with a[4], yelding the following partial permutation:
/// 192.0.2.1, 192.0.2.5, 192.0.2.3, 192.0.2.4, 192.0.2.2. In our case, we simply
/// return the value of 192.0.2.2 to the caller and remember that
/// a[1]=192.0.2.5. At this point we don't store the values of a[0], a[2] and
/// a[3] because the corresponding IP addresses can be calculated from the
/// range start and their index in the permutation. The value of a[1] must be
/// stored because it has been swapped with a[4] and can't be calculated from
/// the position index.
///
/// In the next step, the current index i (cursor value) is decreased by one.
/// It now has the value of 3. Again, a random index is picked from the range
/// of [0..3]. Note that it can be the same or different index than selected
/// in the previous step. Let's assume it is 0. This corresponds to the address
/// of 192.0.2.1. This address will be returned to the caller. The value of
/// a[3]=192.0.2.4 is moved to a[0]. This yelds the following permutation:
/// 192.0.2.4, 192.0.2.5, 192.0.2.3, 192.0.2.1, 192.0.2.2. However, we only
/// remember a[0] and a[1]. The a[3] can be still computed from the range
/// start and the position. The other two have been already returned to the
/// caller so we forget them.
///
/// This algorithm guarantees that all IP addresses or delegated prefixes
/// belonging to the given range are returned and no duplicates are returned.
/// The addresses or delegated prefixes are returned in a random order.
///
/// @todo Methods of this class should be called in thread safe context. Otherwise
/// they should be made thread safe.
class IPRangePermutation {
public:

    /// @brief Constructor for address ranges.
    ///
    /// @param range address range for which the permutation will be generated.
    IPRangePermutation(const AddressRange& range);

    /// @brief Constructor for prefix ranges.
    ///
    /// @param range range of delegated prefixes for which the permutation will
    /// be generated.
    IPRangePermutation(const PrefixRange& range);

    /// @brief Checks if the range has been exhausted.
    ///
    /// @return false if the algorithm went over all addresses or prefixes in
    /// the range, true otherwise.
    bool exhausted() const {
        return (done_);
    }

    /// @brief Returns next random address or prefix from the permutation.
    ///
    /// This method returns all addresses or prefixes belonging to the specified
    /// range in random order. For the first number of calls equal to the size of
    /// the range it guarantees to return a non-zero IP address from that range
    /// without duplicates.
    ///
    /// @param [out] done this parameter is set to true if no more addresses
    /// or prefixes can be returned for this permutation.
    /// @return next available IP address or prefix. It returns IPv4 zero or IPv6
    /// zero address after this method walked over all available IP addresses or
    /// prefixes in the range.
    asiolink::IOAddress next(bool& done);

    /// @brief Resets the permutation state.
    ///
    /// It effectively causes the permutation to start over the process of
    /// serving addresses. Any previously returned addresses can be returned
    /// again after calling this function.
    void reset();

private:

    /// Beginning of the range.
    asiolink::IOAddress range_start_;

    /// Distance between two neighboring addresses or delegated prefixes,
    /// i.e. 1 for address range and delegated prefix size for delegated
    /// prefixes.
    isc::util::uint128_t step_;

    /// Keeps the position of the next address or prefix to be swapped with
    /// a randomly picked address or prefix from the range of 0..cursor-1. The
    /// cursor value is decreased every time a new IP address or prefix
    /// is returned.
    isc::util::uint128_t cursor_;

    /// Keeps the initial cursor position for @c reset function.
    isc::util::uint128_t initial_cursor_;

    /// Keeps the current permutation state. The state associates the
    /// swapped IP addresses or delegated prefixes with their positions in
    /// the permutation.
    std::map<isc::util::uint128_t, asiolink::IOAddress> state_;

    /// Indicates if the addresses or delegated prefixes are exhausted.
    bool done_;

    /// Random generator.
    std::mt19937 generator_;
};

/// @brief Pointer to the @c IPRangePermutation.
typedef boost::shared_ptr<IPRangePermutation> IPRangePermutationPtr;

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // IP_RANGE_PERMUTATION_H
