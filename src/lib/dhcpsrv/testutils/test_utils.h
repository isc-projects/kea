// Copyright (C) 2012-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LIBDHCPSRV_TEST_UTILS_H
#define LIBDHCPSRV_TEST_UTILS_H

#include <dhcpsrv/lease_mgr.h>
#include <list>
#include <vector>

namespace isc {
namespace dhcp {
namespace test {

// @brief performs details comparison between two IPv6 leases
//
// @param first first lease to compare
// @param second second lease to compare
//
// This method is intended to be run from gtest tests as it
// uses gtest macros and possibly reports gtest failures.
void
detailCompareLease(const Lease6Ptr& first, const Lease6Ptr& second);

// @brief performs details comparison between two IPv4 leases
//
// @param first first lease to compare
// @param second second lease to compare
//
// This method is intended to be run from gtest tests as it
// uses gtest macros and possibly reports gtest failures.
void
detailCompareLease(const Lease4Ptr& first, const Lease4Ptr& second);

/// @brief Function that finds the last open socket descriptor
///
/// This function is used to attempt lost connectivity
/// with backends, notably MySQL and Postgresql.
///
/// The theory being, that in a confined test environment the last
/// such descriptor is the SQL client socket descriptor.  This allows
/// us to the close that descriptor and simulate a loss of server
/// connectivity.
///
/// @return the descriptor of the last open socket or -1 if there
/// are none.
int findLastSocketFd();

/// @brief RAII tool which fills holes in the file descriptor sequence
///
/// The @ref findLastSocketFd requires new socket descriptors are allocated
/// after the last open socket descriptor so there is no hole i.e. a free
/// file descriptor in the sequence.
/// This tool detects and fills such holes. It uses the RAII idiom to avoid
/// file descriptor leaks: the destructor called when the object goes out
/// of scope closes all file descriptors which were opened by the constructor.
class FillFdHoles {
public:
    /// @brief Constructor
    ///
    /// Holes between 0 and the specified limit will be filled by opening
    /// the null device. Typically the limit argument is the result of
    /// a previous call to @ref findLastSocketFd. Note if the limit is
    /// 0 or negative the constructor returns doing nothing.
    ///
    /// @param limit Holes will be filled up to this limit
    FillFdHoles(int limit);

    /// @brief Destructor
    ///
    /// The destructor closes members of the list
    ~FillFdHoles();

private:
    /// @brief The list of holes
    std::list<int> fds_;
};

} // namespace test
} // namespace dhcp
} // namespace isc

#endif
