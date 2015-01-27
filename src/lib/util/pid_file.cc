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

#include <util/pid_file.h>
#include <cstdio>
#include <signal.h>
#include <unistd.h>

namespace isc {
namespace util {

PIDFile::PIDFile(const std::string& filename)
    : filename_(filename) {
}

PIDFile::~PIDFile() {
}

bool
PIDFile::check() {
    std::ifstream fs(filename_.c_str());
    int pid;
    bool good;

    // If we weren't able to open the file treat
    // it as if the process wasn't running
    if (fs.is_open() == false) {
        return (false);
    }

    // Try to get the pid, get the status and get rid of the file
    fs >> pid;
    good = fs.good();
    fs.close();

    // Treat being unable to read a pid the same as if we
    // got a pid and the process is still running.
    if ((good == false) || (kill(pid, 0) == 0)) {
        return (true);
    }

    // No process
    return (false);
}

void
PIDFile::write() {
    write(getpid());
}

void
PIDFile::write(int pid) {
    std::ofstream fs(filename_.c_str());

    if (fs.is_open() == false) {
        isc_throw(PIDFileError, "Unable to open PID file '"
                  << filename_ << "' for write");
    }

    // File is open, write the pid.
    fs << pid << std::endl;

    // That's it
    fs.close();
}

void
PIDFile::deleteFile() {
    if (remove(filename_.c_str()) != 0) {
        isc_throw(PIDFileError, "Unable to delete PID file '"
                  << filename_ << "'");
    }
}

} // namespace isc::util
} // namespace isc
