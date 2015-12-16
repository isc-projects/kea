// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <numeric>

#include <string.h>
#include <util/strutil.h>

using namespace std;

namespace isc {
namespace util {
namespace str {

// Normalize slashes

void
normalizeSlash(std::string& name) {
    if (!name.empty()) {
        size_t pos = 0;
        while ((pos = name.find('\\', pos)) != std::string::npos) {
            name[pos] = '/';
        }
    }
}

// Trim String

string
trim(const string& instring) {
    string retstring = "";
    if (!instring.empty()) {
        static const char* blanks = " \t\n";

        // Search for first non-blank character in the string
        size_t first = instring.find_first_not_of(blanks);
        if (first != string::npos) {

            // String not all blanks, so look for last character
            size_t last = instring.find_last_not_of(blanks);

            // Extract the trimmed substring
            retstring = instring.substr(first, (last - first + 1));
        }
    }

    return (retstring);
}

// Tokenize string.  As noted in the header, this is locally written to avoid
// another dependency on a Boost library.

vector<string>
tokens(const std::string& text, const std::string& delim) {
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

    return (result);
}

// Local function to pass to accumulate() for summing up string lengths.

namespace {

size_t
lengthSum(string::size_type curlen, const string& cur_string) {
    return (curlen + cur_string.size());
}

}

// Provide printf-style formatting.

std::string
format(const std::string& format, const std::vector<std::string>& args) {

    static const string flag = "%s";

    // Initialize return string.  To speed things up, we'll reserve an
    // appropriate amount of space - current string size, plus length of all
    // the argument strings, less two characters for each argument (the %s in
    // the format string is being replaced).
    string result;
    size_t length = accumulate(args.begin(), args.end(), format.size(),
        lengthSum) - (args.size() * flag.size());
    result.reserve(length);

    // Iterate through replacing all tokens
    result = format;
    size_t tokenpos = 0;    // Position of last token replaced
    std::vector<std::string>::size_type i = 0; // Index into argument array

    while ((i < args.size()) && (tokenpos != string::npos)) {
        tokenpos = result.find(flag, tokenpos);
        if (tokenpos != string::npos) {
            result.replace(tokenpos, flag.size(), args[i++]);
        }
    }

    return (result);
}

std::string
getToken(std::istringstream& iss) {
    string token;
    iss >> token;
    if (iss.bad() || iss.fail()) {
        isc_throw(StringTokenError, "could not read token from string");
    }
    return (token);
}


} // namespace str
} // namespace util
} // namespace isc
