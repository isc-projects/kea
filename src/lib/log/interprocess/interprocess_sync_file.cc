// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// This file requires LOCKFILE_DIR to be defined. It points to the default
// directory where lockfile will be created.

#include <log/interprocess/interprocess_sync_file.h>

#include <string>
#include <cerrno>
#include <cstring>
#include <sstream>
#include <iostream>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace isc {
namespace log {
namespace interprocess {

InterprocessSyncFile::~InterprocessSyncFile() {
    if (fd_ != -1) {
        // This will also release any applied locks.
        close(fd_);
        // The lockfile will continue to exist, and we must not delete
        // it.
    }
}

bool
InterprocessSyncFile::do_lock(int cmd, short l_type) {
    // Open lock file only when necessary (i.e., here). This is so that
    // if a default InterprocessSync object is replaced with another
    // implementation, it doesn't attempt any opens.
    if (fd_ == -1) {
        std::string lockfile_path = LOCKFILE_DIR;

        const char* const env = getenv("KEA_LOCKFILE_DIR");
        if (env != NULL) {
            lockfile_path = env;
        }

        lockfile_path += "/" + task_name_ + "_lockfile";

        // Open the lockfile in the constructor so it doesn't do the access
        // checks every time a message is logged.
        const mode_t mode = umask(S_IXUSR | S_IXGRP | S_IXOTH); // 0111
        fd_ = open(lockfile_path.c_str(), O_CREAT | O_RDWR,
                   S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP); // 0660
        umask(mode);

        if (fd_ == -1) {
            std::stringstream tmp;

            // We failed to create a lockfile. This means that the logging
            // system is unusable. We need to report the issue using plain
            // print to stderr.
            tmp << "Unable to use interprocess sync lockfile ("
                << std::strerror(errno) << "): " << lockfile_path;
            std::cerr << tmp.str() << std::endl;

            // And then throw exception as usual.
            isc_throw(InterprocessSyncFileError, tmp.str());
        }
    }

    struct flock lock;

    memset(&lock, 0, sizeof (lock));
    lock.l_type = l_type;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 1;

    return (fcntl(fd_, cmd, &lock) == 0);
}

bool
InterprocessSyncFile::lock() {
    if (is_locked_) {
        return (true);
    }

    if (do_lock(F_SETLKW, F_WRLCK)) {
        is_locked_ = true;
        return (true);
    }

    return (false);
}

bool
InterprocessSyncFile::tryLock() {
    if (is_locked_) {
        return (true);
    }

    if (do_lock(F_SETLK, F_WRLCK)) {
        is_locked_ = true;
        return (true);
    }

    return (false);
}

bool
InterprocessSyncFile::unlock() {
    if (!is_locked_) {
        return (true);
    }

    if (do_lock(F_SETLKW, F_UNLCK)) {
        is_locked_ = false;
        return (true);
    }

    return (false);
}

} // namespace interprocess
} // namespace log
} // namespace isc
