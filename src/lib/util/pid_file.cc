// Copyright (C) 2015-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/pid_file.h>

#include <cerrno>

#include <fcntl.h>
#include <signal.h>
#include <sys/file.h>
#include <unistd.h>

namespace isc {
namespace util {

int
PIDFile::check() const {
    std::ifstream fs(filename_.c_str());
    int pid;
    bool good;

    // If we weren't able to open the file treat
    // it as if the process wasn't running
    if (!fs.is_open()) {
        return (0);
    }

    // Try to get the pid, get the status and get rid of the file
    fs >> pid;
    good = fs.good();
    fs.close();

    // If we weren't able to read a pid send back an exception
    if (!good) {
        isc_throw(PIDCantReadPID, "Unable to read PID from file '"
                  << filename_ << "'");
    }

    // If the process is still running return its pid.
    if (kill(pid, 0) == 0) {
        return (pid);
    }

    // No process
    return (0);
}

void
PIDFile::write() const {
    write(getpid());
}

void
PIDFile::write(int pid) const {
    std::ofstream fs(filename_.c_str(), std::ofstream::trunc);

    if (!fs.is_open()) {
        isc_throw(PIDFileError, "Unable to open PID file '"
                  << filename_ << "' for write");
    }

    // File is open, write the pid.
    fs << pid << std::endl;

    bool good = fs.good();
    fs.close();

    if (!good) {
        isc_throw(PIDFileError, "Unable to write to PID file '"
                  << filename_ << "'");
    }
}

void
PIDFile::deleteFile() const {
    if ((remove(filename_.c_str()) != 0) &&
        (errno != ENOENT)) {
        isc_throw(PIDFileError, "Unable to delete PID file '"
                  << filename_ << "'");
    }
}

PIDLock::PIDLock(const std::string& lockname)
    : lockname_(lockname), fd_(-1), locked_(false) {
    // Open the lock file.
    fd_ = open(lockname_.c_str(), O_RDONLY | O_CREAT, 0600);
    if (fd_ == -1) {
        if (errno == ENOENT) {
            // Ignoring missing component in the path.
            locked_ = true;
            return;
        }
        std::string errmsg = strerror(errno);
        isc_throw(PIDFileError, "cannot create pid lockfile '"
                  << lockname_ << "': " << errmsg);
    }
    // Try to acquire the lock. If we can't somebody else is actively
    // using it.
    int ret = flock(fd_, LOCK_EX | LOCK_NB);
    if (ret == 0) {
        locked_ = true;
        return;
    }
    if (errno != EWOULDBLOCK) {
        std::string errmsg = strerror(errno);
        isc_throw(PIDFileError, "cannot lock pid lockfile '"
                  << lockname_ << "': " << errmsg);
    }
}

PIDLock::~PIDLock() {
    if (fd_ != -1) {
        if (locked_) {
            // For symmetry as the close releases the lock...
            static_cast<void>(flock(fd_, LOCK_UN));
        }
        static_cast<void>(close(fd_));
        static_cast<void>(remove(lockname_.c_str()));
    }
    fd_ = -1;
    locked_ = false;
}

} // namespace isc::util
} // namespace isc
