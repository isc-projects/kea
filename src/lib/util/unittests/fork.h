// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UTIL_UNITTESTS_FORK_H
#define UTIL_UNITTESTS_FORK_H 1

#include <unistd.h>

/**
 * \file fork.h
 * \brief Help functions to fork the test case process.
 * Various functions to fork a process and feed some data to pipe, check
 * its output and such lives here.
 */

namespace isc {
namespace util {
namespace unittests {

/**
 * @short Checks that a process terminates correctly.
 * Waits for a process to terminate (with a short timeout, this should be
 * used whan the process is about to terminate) and checks its exit code.
 *
 * @return True if the process terminates with 0, false otherwise.
 * @param process The ID of process to wait for.
 */
bool
process_ok(pid_t process);

pid_t
provide_input(int* read_pipe, const void* input, const size_t length);

pid_t
check_output(int* write_pipe, const void* const output, const size_t length);

} // End of the namespace
}
}

#endif // UTIL_UNITTESTS_FORK_H
