// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef READY_CHECK_H
#define READY_CHECK_H

namespace isc {
namespace util {

/// @param fd_to_check The file descriptor to test
/// @param timeout_sec Select timeout in seconds
/// @return -1 on error, 0 if no data is available, 1 if data is ready
int selectCheck(const int fd_to_check, const unsigned int timeout_sec = 0);

} // end of isc::util namespace
} // end of isc namespace

#endif  // READY_CHECK_H
