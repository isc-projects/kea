// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef FORK_DETECTOR_H
#define FORK_DETECTOR_H

#include <sys/types.h>
#include <unistd.h>

namespace isc {
namespace util {

/// @brief Class which detects being child process.
///
/// This class detects if it is in the child process, by checking if the
/// process PID matches the PID of the process which created instance of
/// the class.
///
/// Detecting if we're in the child process is important when the application
/// spawns new process using fork/exec. If exec step fails for any reason
/// the child process exits. However, to exit gracefully the process may
/// need to know if it is a child or parent and take a different path
/// during destruction.
class ForkDetector {
public:

    /// @brief Constructor.
    ///
    /// Stores the PID of the process creating this instance.
    ForkDetector()
        : creator_pid_(getpid()) {
    }

    /// @brief Check if the process is a parent process;
    ///
    /// @return true if the process is a parent process.
    bool isParent() const {
        return (getpid() == creator_pid_);
    }

private:

    /// @brief PID of the process which created instance of this class.
    pid_t creator_pid_;

};

} // namespace isc::util
} // namespace isc

#endif // FORK_DETECTOR_H
