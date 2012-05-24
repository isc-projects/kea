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

#ifndef __INTERPROCESS_SYNC_FILE_H__
#define __INTERPROCESS_SYNC_FILE_H__

#include "util/interprocess_sync.h"
#include "exceptions/exceptions.h"

namespace isc {
namespace util {

///
/// \brief Exception that is thrown if it's not possible to open the
/// lock file.
///
class InterprocessSyncFileError : public Exception {
public:
    InterprocessSyncFileError(const char* file, size_t line,
                              const char* what) :
        isc::Exception(file, line, what) {}
};

class InterprocessSyncFile : public InterprocessSync {
public:
    /// \brief Constructor
    InterprocessSyncFile(const std::string component_name) :
        InterprocessSync(component_name), fd_(-1)
    {}

    /// \brief Destructor
    ~InterprocessSyncFile();

protected:
    bool lock();
    bool tryLock();
    bool unlock();

private:
    bool do_lock(int cmd, short l_type);

    int fd_;
};

} // namespace util
} // namespace isc

#endif // __INTERPROCESS_SYNC_FILE_H__
