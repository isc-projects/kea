// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <iostream>
#include <algorithm>
#include <string>

#include <ctype.h>

#include <filename.h>

using namespace std;


namespace isc {
namespace log {

// Split string into components.  Any backslashes are assumed to have
// been replaced by forward slashes.

void Filename::split(const string& full_name, string& directory,
    string& name, string& extension) const
{
    directory = name = extension = "";
    bool dir_present = false;
    if (! full_name.empty()) {

        // Find the directory.
        size_t last_slash = full_name.find_last_of('/');
        if (last_slash != string::npos) {

            // Found the last slash, so extract directory component and
            // set where the scan for the last_dot should terminate.
            directory = full_name.substr(0, last_slash + 1);
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
        if ((last_dot == string::npos) ||
            (dir_present && (last_dot < last_slash))) {

            // Last "." either not found or it occurs to the left of the last
            // slash if a directory was present (so it is part of a directory
            // name).  In this case, the remainder of the string after the slash
            // is the name part.
            name = full_name.substr(last_slash + 1);
            return;
        }

        // Did find a valid dot, so it and everything to the right is the
        // extension...
        extension = full_name.substr(last_dot);

        // ... and the name of the file is everything in between.
        if ((last_dot - last_slash) > 1) {
            name = full_name.substr(last_slash + 1, last_dot - last_slash - 1);
        }
    }

}

// Expand the stored filename with the default.

string Filename::expandWithDefault(const string& defname) const {

    string def_directory("");
    string def_name("");
    string def_extension("");

    // Normalize the input string.
    string copy_defname = StringUtil::trim(defname);
    StringUtil::normalizeSlash(copy_defname);

    // Split into the components
    split(copy_defname, def_directory, def_name, def_extension);

    // Now construct the result.
    string retstring =
        (directory_.empty() ? def_directory : directory_) +
        (name_.empty() ? def_name : name_) +
        (extension_.empty() ? def_extension : extension_);
    return retstring;
}

// Use the stored name as default for a given name

string Filename::useAsDefault(const string& name) const {

    string name_directory("");
    string name_name("");
    string name_extension("");

    // Normalize the input string.
    string copy_name = StringUtil::trim(name);
    StringUtil::normalizeSlash(copy_name);

    // Split into the components
    split(copy_name, name_directory, name_name, name_extension);

    // Now construct the result.
    string retstring =
        (name_directory.empty() ? directory_ : name_directory) +
        (name_name.empty() ? name_ : name_name) +
        (name_extension.empty() ? extension_ : name_extension);
    return retstring;
}


} // namespace log
} // namespace isc
