// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/filesystem.h>
#include <util/str.h>

#include <algorithm>
#include <cctype>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include <fcntl.h>
#include <sys/stat.h>

using namespace isc::util::str;
using namespace std;

namespace isc {
namespace util {
namespace file {

string
getContent(string const& file_name) {
    if (!exists(file_name)) {
        isc_throw(BadValue, "Expected a file at path '" << file_name << "'");
    }
    if (!isFile(file_name)) {
        isc_throw(BadValue, "Expected '" << file_name << "' to be a regular file");
    }
    ifstream file(file_name, ios::in);
    if (!file.is_open()) {
        isc_throw(BadValue, "Cannot open '" << file_name);
    }
    string content;
    file >> content;
    return (content);
}

bool
exists(string const& path) {
    struct stat statbuf;
    return (::stat(path.c_str(), &statbuf) == 0);
}

bool
isDir(string const& path) {
    struct stat statbuf;
    if (::stat(path.c_str(), &statbuf) < 0) {
        return (false);
    }
    return ((statbuf.st_mode & S_IFMT) == S_IFDIR);
}

bool
isFile(string const& path) {
    struct stat statbuf;
    if (::stat(path.c_str(), &statbuf) < 0) {
        return (false);
    }
    return ((statbuf.st_mode & S_IFMT) == S_IFREG);
}

Path::Path(string const& full_name) {
    if (!full_name.empty()) {
        bool dir_present = false;
        // Find the directory.
        size_t last_slash = full_name.find_last_of('/');
        if (last_slash != string::npos) {
            // Found the last slash, so extract directory component and
            // set where the scan for the last_dot should terminate.
            parent_path_ = full_name.substr(0, last_slash + 1);
            if (last_slash == full_name.size()) {
                // The entire string was a directory, so exit not and don't
                // do any more searching.
                return;
            }

            // Found a directory so note the fact.
            dir_present = true;
        }

        // Now search backwards for the last ".".
        size_t last_dot = full_name.find_last_of('.');
        if ((last_dot == string::npos) || (dir_present && (last_dot < last_slash))) {
            // Last "." either not found or it occurs to the left of the last
            // slash if a directory was present (so it is part of a directory
            // name).  In this case, the remainder of the string after the slash
            // is the name part.
            stem_ = full_name.substr(last_slash + 1);
            return;
        }

        // Did find a valid dot, so it and everything to the right is the
        // extension...
        extension_ = full_name.substr(last_dot);

        // ... and the name of the file is everything in between.
        if ((last_dot - last_slash) > 1) {
            stem_ = full_name.substr(last_slash + 1, last_dot - last_slash - 1);
        }
    }
}

string
Path::str() const {
    return (parent_path_ + stem_ + extension_);
}

string
Path::parentPath() const {
    return (parent_path_);
}

string
Path::stem() const {
    return (stem_);
}

string
Path::extension() const {
    return (extension_);
}

string
Path::filename() const {
    return (stem_ + extension_);
}

Path&
Path::replaceExtension(string const& replacement) {
    string const trimmed_replacement(trim(replacement));
    if (trimmed_replacement.empty()) {
        extension_ = string();
    } else {
        size_t const last_dot(trimmed_replacement.find_last_of('.'));
        if (last_dot == string::npos) {
            extension_ = "." + trimmed_replacement;
        } else {
            extension_ = trimmed_replacement.substr(last_dot);
        }
    }
    return (*this);
}

Path&
Path::replaceParentPath(string const& replacement) {
    string const trimmed_replacement(trim(replacement));
    if (trimmed_replacement.empty()) {
        parent_path_ = string();
    } else if (trimmed_replacement.at(trimmed_replacement.size() - 1) == '/') {
        parent_path_ = trimmed_replacement;
    } else {
        parent_path_ = trimmed_replacement + '/';
    }
    return (*this);
}

}  // namespace file
}  // namespace util
}  // namespace isc
