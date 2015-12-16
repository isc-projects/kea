// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

/// @file test_utils.h Common dhcp_ddns testing elements

#include <gtest/gtest.h>


namespace isc {
namespace dhcp_ddns {

/// @brief Returns the result of select() given an fd to check for read status.
///
/// @param fd_to_check The file descriptor to test
///
/// @return Returns less than one on an error, 0 if the fd is not ready to
/// read, > 0 if it is ready to read. 
int selectCheck(int fd_to_check);

}; // namespace isc::dhcp_ddns;
}; // namespace isc;

#endif 
