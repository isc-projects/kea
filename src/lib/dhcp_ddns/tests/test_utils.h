// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
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
