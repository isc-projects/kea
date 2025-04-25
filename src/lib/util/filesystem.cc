// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/filesystem.h>
#include <util/str.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>

#include <dirent.h>
#include <fcntl.h>

using namespace isc;
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

Umask::Umask(mode_t mask) : orig_umask_(umask(S_IWGRP | S_IWOTH)) {
    umask(orig_umask_ | mask);
}

Umask::~Umask() {
    umask(orig_umask_);
}

bool
isSocket(string const& path) {
    struct stat statbuf;
    if (::stat(path.c_str(), &statbuf) < 0) {
        return (false);
    }
    return ((statbuf.st_mode & S_IFMT) == S_IFSOCK);
}

Path::Path(string const& full_name) {
    if (!full_name.empty()) {
        bool dir_present = false;
        // Find the directory.
        size_t last_slash = full_name.find_last_of('/');
        if (last_slash != string::npos) {
            // Found the last slash, so extract directory component and
            // set where the scan for the last_dot should terminate.
            parent_path_ = full_name.substr(0, last_slash);
            if (last_slash == full_name.size()) {
                // The entire string was a directory, so exit and don't
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
    return (parent_path_ + ((parent_path_.empty() || parent_path_ == "/") ? string() : "/") + stem_ + extension_);
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
    } else if (trimmed_replacement == "/") {
        parent_path_ = trimmed_replacement;
    } else if (trimmed_replacement.at(trimmed_replacement.size() - 1) == '/') {
        parent_path_ = trimmed_replacement.substr(0, trimmed_replacement.size() - 1);
    } else {
        parent_path_ = trimmed_replacement;
    }
    return (*this);
}

TemporaryDirectory::TemporaryDirectory() {
    char dir[]("/tmp/kea-tmpdir-XXXXXX");
    char const* dir_name = mkdtemp(dir);
    if (!dir_name) {
        isc_throw(Unexpected, "mkdtemp failed " << dir << ": " << strerror(errno));
    }
    dir_name_ = string(dir_name);
}

TemporaryDirectory::~TemporaryDirectory() {
    DIR *dir(opendir(dir_name_.c_str()));
    if (!dir) {
        return;
    }

    std::unique_ptr<DIR, void(*)(DIR*)> defer(dir, [](DIR* d) { closedir(d); });

    struct dirent *i;
    string filepath;
    while ((i = readdir(dir))) {
        if (strcmp(i->d_name, ".") == 0 || strcmp(i->d_name, "..") == 0) {
            continue;
        }

        filepath = dir_name_ + '/' + i->d_name;
        remove(filepath.c_str());
    }

    rmdir(dir_name_.c_str());
}

string TemporaryDirectory::dirName() {
    return dir_name_;
}

std::string
FileManager::validatePath(const std::string supported_path_str, const std::string input_path_str,
                          bool enforce_path /* = true */) {
    // Remove the trailing "/" if it present so comparision to
    // input's parent path functions.
    auto supported_path_copy(supported_path_str);
    if (supported_path_copy.back() == '/') {
        supported_path_copy.pop_back();
    }

    Path input_path(trim(input_path_str));
    auto filename = input_path.filename();
    if (filename.empty()) {
        isc_throw(BadValue, "path: '" << input_path.str() << "' has no filename");
     }
 
    auto parent_path = input_path.parentPath();
    if (!parent_path.empty()) {
         if (!enforce_path) {
             // Security set to lax, let it fly.
             return (input_path_str);
         }
 
         // We only allow absolute path equal to default. Catch an invalid path.
        if (parent_path != supported_path_copy) {
             isc_throw(BadValue, "invalid path specified: '"
                      << parent_path << "', supported path is '"
                      << supported_path_copy << "'");
         }
     }
 
    std::string valid_path(supported_path_copy + "/" +  filename);
    return (valid_path);
}

}  // namespace file
}  // namespace util
}  // namespace isc
