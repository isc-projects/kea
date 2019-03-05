// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SANDBOX_H
#define SANDBOX_H

#include <exceptions/exceptions.h>

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <ftw.h>

namespace isc {
namespace test {

/// @brief A Sandbox class that provides access to unit test unique
///    temporary folder.
///
/// The sandbox's temporary folder is created in constructor ie.
/// in unit test setup phase, and then it is deleted with its content
/// in destructor ie. in unit test tear down phase.
class Sandbox {
    /// Path to temporary folder
    std::string path_;

    /// @brief Method for deleting files and folders, used in nftw traversal function.
    static int rmFile(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
        (void)sb;
        (void)typeflag;
        (void)ftwbuf;
        return(remove(fpath));
    }

public:
    /// @brief Sandbox constructor.
    Sandbox() {
        char tmpl[] = {P_tmpdir "/kea-XXXXXX"};
        path_ = mkdtemp(tmpl);
    }

    /// @brief Destructor, it deletes temporary folder with its content.
    ~Sandbox() {
        // Delete content of path_ recursively.
        if (nftw(path_.c_str(), Sandbox::rmFile, 10, FTW_DEPTH | FTW_MOUNT | FTW_PHYS) < 0) {
            isc_throw(isc::Unexpected, "Some issue occured while deleting unit test sandbox.");
        }
    }

    // @brief Join sandbox path with indicated file subpath.
    std::string join(std::string file) {
        return path_ + "/" + file;
    }
};


}; // end of isc::test namespace
}; // end of isc namespace

#endif // SANDBOX_H
