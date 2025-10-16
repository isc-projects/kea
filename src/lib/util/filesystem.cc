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
#include <iostream>

#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

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
    getline(file, content);
    return (content);
}

bool
exists(string const& path) {
    struct stat statbuf;
    return (::stat(path.c_str(), &statbuf) == 0);
}

mode_t
getPermissions(const std::string path) {
    struct stat statbuf;
    if (::stat(path.c_str(), &statbuf) < 0) {
        return (0);
    }

    return (statbuf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
}

bool
hasPermissions(const std::string path, const mode_t& permissions) {
    return (getPermissions(path) == permissions);
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

bool
isSocket(string const& path) {
    struct stat statbuf;
    if (::stat(path.c_str(), &statbuf) < 0) {
        return (false);
    }
    return ((statbuf.st_mode & S_IFMT) == S_IFSOCK);
}

void
setUmask() {
    // No group write and no other access.
    mode_t mask(S_IWGRP | S_IRWXO);
    mode_t orig = umask(mask);
    // Handle the case where the original umask was already more restrictive.
    if ((orig | mask) != mask) {
        static_cast<void>(umask(orig | mask));
    }
}

bool amRunningAsRoot() {
    return (getuid() == 0 || geteuid() == 0);
}

Path::Path(string const& full_name) {
    dir_present_ = false;
    if (!full_name.empty()) {
        // Find the directory.
        size_t last_slash = full_name.find_last_of('/');
        if (last_slash != string::npos) {
            // Found a directory so note the fact.
            dir_present_ = true;

            // Found the last slash, so extract directory component and
            // set where the scan for the last_dot should terminate.
            parent_path_ = full_name.substr(0, last_slash);
            if (last_slash == full_name.size()) {
                // The entire string was a directory, so exit and don't
                // do any more searching.
                return;
            }
        }

        // Now search backwards for the last ".".
        size_t last_dot = full_name.find_last_of('.');
        if ((last_dot == string::npos) || (dir_present_ && (last_dot < last_slash))) {
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
    return (parent_path_ + (dir_present_ ? "/" : "") + stem_ + extension_);
}

string
Path::parentPath() const {
    return (parent_path_);
}

string
Path::parentDirectory() const {
    return (parent_path_ + (dir_present_ ? "/" : ""));
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
    dir_present_ = (trimmed_replacement.find_last_of('/') != string::npos);
    if (trimmed_replacement.empty() || (trimmed_replacement == "/")) {
        parent_path_ = string();
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

PathChecker::PathChecker(const std::string default_path,
                             const std::string env_name /* = "" */)
    : default_path_(default_path), env_name_(env_name),
      default_overridden_(false) {
    getPath(true);
}

std::string
PathChecker::getPath(bool reset /* = false */,
                     const std::string explicit_path /* = "" */) {
    if (reset) {
        if (!explicit_path.empty()) {
            path_ = explicit_path;
        } else if (!env_name_.empty()) {
            path_ = std::string(std::getenv(env_name_.c_str()) ?
                                std::getenv(env_name_.c_str()) : default_path_);
        } else {
            path_ = default_path_;
        }

        // Remove the trailing "/" if it is present so comparison to
        // other Path::parentPath() works.
        while (!path_.empty() && path_.back() == '/') {
            path_.pop_back();
        }

        default_overridden_ = (path_ != default_path_);
    }

    return (path_);
}

std::string
PathChecker::validatePath(const std::string input_path_str,
                          bool enforce_path /* = PathChecker::shouldEnforceSecurity() */) const {
    Path input_path(trim(input_path_str));
    auto filename = input_path.filename();
    if (filename.empty()) {
        isc_throw(BadValue, "path: '" << input_path.str() << "' has no filename");
    }

    auto parent_path = input_path.parentPath();
    auto parent_dir = input_path.parentDirectory();
    if (!parent_dir.empty()) {
        // We only allow absolute path equal to default. Catch an invalid path.
        if ((parent_path != path_) || (parent_dir == "/")) {
            std::ostringstream oss;
            oss << "invalid path specified: '"
                << (parent_path.empty() ? "/" : parent_path)
                << "', supported path is '"
                << path_ << "'";

            if (enforce_path) {
                isc_throw(SecurityError, oss.str());
            } else {
                isc_throw(SecurityWarn, oss.str());
            }
        }
    }

    std::string valid_path(path_ + "/" +  filename);
    return (valid_path);
}

std::string
PathChecker::validateDirectory(const std::string input_path_str,
                               bool enforce_path /* = PathChecker::shouldEnforceSecurity() */) const {
    // We only allow absolute path equal to default. Catch an invalid path.
    if (!input_path_str.empty()) {
        std::string input_copy = input_path_str;
        while (!input_copy.empty() && input_copy.back() == '/') {
               input_copy.pop_back();
        }

        if (input_copy != path_) {
            std::ostringstream oss;
            oss << "invalid path specified: '"
                << input_path_str << "', supported path is '"
                << path_ << "'";

            if (enforce_path) {
                isc_throw(SecurityError, oss.str());
            } else {
                isc_throw(SecurityWarn, oss.str());
            }
        }
    }

    return (path_);
}

bool
PathChecker::pathHasPermissions(mode_t permissions, bool enforce_perms
                                /* = PathChecker::shouldEnforceSecurity() */) const {
    return((!enforce_perms) || hasPermissions(path_, permissions));
}

bool
PathChecker::isDefaultOverridden() {
    return (default_overridden_);
}

bool PathChecker::shouldEnforceSecurity() {
    return (enforce_security_);
}

void PathChecker::enableEnforcement(bool enable) {
    enforce_security_ = enable;
}

bool PathChecker::enforce_security_ = true;

}  // namespace file
}  // namespace util
}  // namespace isc
