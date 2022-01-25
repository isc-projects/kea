// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/filename.h>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

namespace isc {
namespace util {
namespace file {

string
getContent(const string& file_name) {
    // Open the file.
    int fd = ::open(file_name.c_str(), O_RDONLY);
    if (fd < 0) {
        isc_throw(BadValue, "can't open file '" << file_name << "': "
                  << std::strerror(errno));
    }
    try {
        struct stat stats;
        if (fstat(fd, &stats) < 0) {
            isc_throw(BadValue, "can't stat file '" << file_name << "': "
                      << std::strerror(errno));
        }
        if ((stats.st_mode & S_IFMT) != S_IFREG) {
            isc_throw(BadValue, "'" << file_name
                      << "' must be a regular file");
        }
        string content(stats.st_size, ' ');
        ssize_t got = ::read(fd, &content[0], stats.st_size);
        if (got < 0) {
            isc_throw(BadValue, "can't read file '" << file_name << "': "
                      << std::strerror(errno));
        }
        if (got != stats.st_size) {
            isc_throw(BadValue, "can't read whole file '" << file_name
                      << "' (got " << got << " of " << stats.st_size << ")");
        }
        static_cast<void>(close(fd));
        return (content);
    } catch (const std::exception&) {
        static_cast<void>(close(fd));
        throw;
    }
}

bool
isDir(const string& name) {
    struct stat stats;
    if (::stat(name.c_str(), &stats) < 0) {
        return (false);
    }
    return ((stats.st_mode & S_IFMT) == S_IFDIR);
}

} // namespace file
} // namespace log
} // namespace isc
