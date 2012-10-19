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

#include <boost/weak_ptr.hpp>

#include <map>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace isc::util::thread;

namespace isc {
namespace util {

namespace { // unnamed namespace

typedef std::map<std::string, boost::weak_ptr<isc::util::thread::Mutex> >
    SyncMap;

SyncMap&
getSyncMap() {
    // avoid static destruction fiasco when the SyncMap is destroyed
    // before clients which use it such as logger objects. This leaks,
    // but isn't a growing leak.
    static SyncMap* sync_map = new SyncMap;

    return (*sync_map);
}

Mutex&
getSyncMapMutex() {
    // avoid static destruction fiasco when the Mutex is destroyed
    // before clients which use it such as logger objects. This leaks,
    // but isn't a growing leak.
    static Mutex* sync_map_mutex = new Mutex;

    return (*sync_map_mutex);
}

} // end of unnamed namespace

InterprocessSyncFile::InterprocessSyncFile(const std::string& task_name) :
    InterprocessSync(task_name),
    fd_(-1)
{
    Mutex::Locker locker(getSyncMapMutex());

    SyncMap& sync_map = getSyncMap();
    SyncMap::iterator it = sync_map.find(task_name);
    if (it != sync_map.end()) {
        mutex_ = it->second.lock();
    } else {
        mutex_.reset(new Mutex());
        sync_map[task_name] = mutex_;
    }

    // Lock on sync_map_mutex is automatically unlocked during
    // destruction when basic block is exited.
}

InterprocessSyncFile::~InterprocessSyncFile() {
    if (fd_ != -1) {
        // This will also release any applied locks.
        close(fd_);
        // The lockfile will continue to exist, and we must not delete
        // it.
    }

    Mutex::Locker locker(getSyncMapMutex());

    // Unref the shared mutex.
    locker_.reset();
    mutex_.reset();

    // Remove name from the map if it is unused anymore.
    SyncMap& sync_map = getSyncMap();
    SyncMap::iterator it = sync_map.find(task_name_);
    assert(it != sync_map.end());

    if (it->second.expired()) {
        sync_map.erase(it);
    }

    // Lock on sync_map_mutex is automatically unlocked during
    // destruction when basic block is exited.
}

bool
InterprocessSyncFile::do_lock(int cmd, short l_type) {
    // Open lock file only when necessary (i.e., here). This is so that
    // if a default InterprocessSync object is replaced with another
    // implementation, it doesn't attempt any opens.
    if (fd_ == -1) {
        std::string lockfile_path = LOCKFILE_DIR;

        const char* const env = getenv("B10_FROM_BUILD");
        if (env != NULL) {
            lockfile_path = env;
        }

        const char* const env2 = getenv("B10_FROM_BUILD_LOCALSTATEDIR");
        if (env2 != NULL) {
            lockfile_path = env2;
        }

        const char* const env3 = getenv("B10_LOCKFILE_DIR_FROM_BUILD");
        if (env3 != NULL) {
            lockfile_path = env3;
        }

        lockfile_path += "/" + task_name_ + "_lockfile";

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

    // First grab the thread lock...
    LockerPtr locker(new Mutex::Locker(*mutex_));

    // ... then the file lock.
    if (do_lock(F_SETLKW, F_WRLCK)) {
        is_locked_ = true;
        locker_ = locker;
        return (true);
    }

    return (false);
}

bool
InterprocessSyncFile::tryLock() {
    if (is_locked_) {
        return (true);
    }

    // First grab the thread lock...
    LockerPtr locker;
    try {
        locker.reset(new Mutex::Locker(*mutex_, false));
    } catch (const Mutex::Locker::AlreadyLocked&) {
        return (false);
    }

    // ... then the file lock.
    if (do_lock(F_SETLK, F_WRLCK)) {
        is_locked_ = true;
        locker_ = locker;
        return (true);
    }

    return (false);
}

bool
InterprocessSyncFile::unlock() {
    if (!is_locked_) {
        return (true);
    }

    // First release the file lock...
    if (do_lock(F_SETLKW, F_UNLCK) == 0) {
        return (false);
    }

    locker_.reset();
    is_locked_ = false;
    return (true);
}

} // namespace util
} // namespace isc
