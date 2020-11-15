// Copyright (C) 2012-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include "test_utils.h"
#include <asiolink/io_address.h>
#include <gtest/gtest.h>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;
using namespace isc::asiolink;

namespace isc {
namespace dhcp {
namespace test {

void
detailCompareLease(const Lease4Ptr& first, const Lease4Ptr& second) {
    // Compare address strings.  Comparison of address objects is not used, as
    // odd things happen when they are different: the EXPECT_EQ macro appears to
    // call the operator uint32_t() function, which causes an exception to be
    // thrown for IPv6 addresses.
    ASSERT_TRUE(first);
    ASSERT_TRUE(second);
    EXPECT_EQ(first->addr_, second->addr_);

    // We need to compare the actual HWAddr objects, not pointers
    EXPECT_TRUE(*first->hwaddr_ == *second->hwaddr_);

    if (first->client_id_ && second->client_id_) {
        EXPECT_TRUE(*first->client_id_ == *second->client_id_);
    } else {
        if (first->client_id_ && !second->client_id_) {

            ADD_FAILURE() << "Client-id present in first lease ("
                          << first->client_id_->getClientId().size()
                          << " bytes), but missing in second.";
        }
        if (!first->client_id_ && second->client_id_) {
            ADD_FAILURE() << "Client-id missing in first lease, but present in second ("
                          << second->client_id_->getClientId().size()
                          << " bytes).";
        }
        // else here would mean that both leases do not have client_id_
        // which makes them equal in that regard. It is ok.
    }
    EXPECT_EQ(first->valid_lft_, second->valid_lft_);
    EXPECT_EQ(first->cltt_, second->cltt_);
    EXPECT_EQ(first->subnet_id_, second->subnet_id_);
    EXPECT_EQ(first->fqdn_fwd_, second->fqdn_fwd_);
    EXPECT_EQ(first->fqdn_rev_, second->fqdn_rev_);
    EXPECT_EQ(first->hostname_, second->hostname_);
    if (first->getContext()) {
        EXPECT_TRUE(second->getContext());
        if (second->getContext()) {
            EXPECT_EQ(first->getContext()->str(), second->getContext()->str());
        }
    } else {
        EXPECT_FALSE(second->getContext());
    }
}

void
detailCompareLease(const Lease6Ptr& first, const Lease6Ptr& second) {
    ASSERT_TRUE(first);
    ASSERT_TRUE(second);
    EXPECT_EQ(first->type_, second->type_);

    // Compare address strings.  Comparison of address objects is not used, as
    // odd things happen when they are different: the EXPECT_EQ macro appears to
    // call the operator uint32_t() function, which causes an exception to be
    // thrown for IPv6 addresses.
    EXPECT_EQ(first->addr_, second->addr_);
    EXPECT_EQ(first->prefixlen_, second->prefixlen_);
    EXPECT_EQ(first->iaid_, second->iaid_);
    ASSERT_TRUE(first->duid_);
    ASSERT_TRUE(second->duid_);
    EXPECT_TRUE(*first->duid_ == *second->duid_);
    EXPECT_EQ(first->preferred_lft_, second->preferred_lft_);
    EXPECT_EQ(first->valid_lft_, second->valid_lft_);
    EXPECT_EQ(first->cltt_, second->cltt_);
    EXPECT_EQ(first->subnet_id_, second->subnet_id_);
    EXPECT_EQ(first->fqdn_fwd_, second->fqdn_fwd_);
    EXPECT_EQ(first->fqdn_rev_, second->fqdn_rev_);
    EXPECT_EQ(first->hostname_, second->hostname_);
    if (first->getContext()) {
        EXPECT_TRUE(second->getContext());
        if (second->getContext()) {
            EXPECT_EQ(first->getContext()->str(), second->getContext()->str());
        }
    } else {
        EXPECT_FALSE(second->getContext());
    }
}

int findLastSocketFd() {
    int max_fd_number = getdtablesize();
    int last_socket = -1;
    struct stat stats;

    // Iterate over the open fds
    for (int fd = 0; fd <= max_fd_number; fd++ ) {
        errno = 0;
        fstat(fd, &stats);

        if (errno == EBADF ) {
            // Skip any that aren't open
            continue;
        }

        // it's a socket, remember it
        if (S_ISSOCK(stats.st_mode)) {
            last_socket = fd;
        }
    }

    return (last_socket);
}

FillFdHoles::FillFdHoles(int limit) : fds_() {
    if (limit <= 0) {
        return;
    }
    for (;;) {
        int fd = open("/dev/null", O_RDWR, 0);
        if (fd == -1) {
            return;
        }
        if (fd < limit) {
            fds_.push_front(fd);
        } else {
            static_cast<void>(close(fd));
            return;
        }
    }
}

FillFdHoles::~FillFdHoles() {
    while (!fds_.empty()) {
        static_cast<void>(close(fds_.back()));
        fds_.pop_back();
    }
}

} // namespace test
} // namespace dhcp
} // namespace isc
