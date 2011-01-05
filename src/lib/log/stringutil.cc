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

#include <string.h>
#include <stringutil.h>

using namespace std;

namespace isc {
namespace log {

// Trim String

string StringUtil::trim(const string& instring) {
    static const char* blanks = " \t\n";

    string retstring = "";
    if (! instring.empty()) {

        // Search for first non-blank character in the string
        size_t first = instring.find_first_not_of(blanks);
        if (first != string::npos) {

            // String not all blanks, so look for last character
            size_t last = instring.find_last_not_of(blanks);

            // Extract the trimmed substring
            retstring = instring.substr(first, (last - first + 1));
        }
    }

    return retstring;
}

// Tokenise string.  As noted in the header, this is locally written to avoid
// another dependency on a Boost library.

vector<string> StringUtil::tokens(const std::string text,
    const std::string& delim)
{
    vector<string> result;

    // Search for the first non-delimiter character
    size_t start = text.find_first_not_of(delim);
    while (start != string::npos) {

        // Non-delimiter found, look for next delimiter
        size_t end = text.find_first_of(delim, start);
        if (end != string::npos) {

            // Delimiter found, so extract string & search for start of next
            // non-delimiter segment.
            result.push_back(text.substr(start, (end - start)));
            start = text.find_first_not_of(delim, end);

        } else {

            // End of string found, extract rest of string and flag to exit
            result.push_back(text.substr(start));
            start = string::npos;
        }
    }

    return result;
}

} // namespace log
} // namespace isc
