// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include "interprocess_sync_file.h"

#include <string>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace isc {
namespace util {

InterprocessSyncFile::InterprocessSyncFile(const std::string component_name) :
    InterprocessSync(component_name)
{
    std::string lockfile_path = LOCKFILE_DIR;

    const char* const env = getenv("B10_FROM_SOURCE");
    if (env != NULL) {
        lockfile_path = env;
    }

    const char* const env2 = getenv("B10_FROM_SOURCE_LOCALSTATEDIR");
    if (env2 != NULL) {
        lockfile_path = env2;
    }

    lockfile_path += "/" + component_name_ + "_lockfile";

    // Open the lockfile in the constructor so it doesn't do the access
    // checks every time a message is logged.
    const mode_t mode = umask(0111);
    fd_ = open(lockfile_path.c_str(), O_CREAT | O_RDWR, 0660);
    umask(mode);

    if (fd_ == -1) {
        isc_throw(InterprocessSyncFileError,
                  "Unable to use interprocess sync lockfile: " +
                  lockfile_path);
    }
}

InterprocessSyncFile::~InterprocessSyncFile() {
    if (fd_ != -1) {
        // This will also release any applied locks.
        close(fd_);
    }

    // The lockfile will continue to exist, and we must not delete it.
}

static bool
do_lock(int fd, int cmd, short l_type)
{
    struct flock lock;

    memset(&lock, 0, sizeof (lock));
    lock.l_type = l_type;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 1;

    const int status = fcntl(fd, cmd, &lock);

    return ((status == 0) ? true : false);
}

bool
InterprocessSyncFile::lock() {
    if (is_locked_) {
        return (true);
    }

    if (do_lock(fd_, F_SETLKW, F_WRLCK)) {
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

    if (do_lock(fd_, F_SETLK, F_WRLCK)) {
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

    if (do_lock(fd_, F_SETLKW, F_UNLCK)) {
        is_locked_ = false;
        return (true);
    }

    return (false);
}

} // namespace util
} // namespace isc
