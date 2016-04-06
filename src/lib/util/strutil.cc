// Copyright (C) 2011-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <util/encode/hex.h>
#include <util/strutil.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>

#include <numeric>
#include <sstream>
#include <string.h>


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

std::vector<uint8_t>
quotedStringToBinary(const std::string& quoted_string) {
    std::vector<uint8_t> binary;
    // Remove whitespace before and after the quotes.
    std::string trimmed_string = trim(quoted_string);

    // We require two quote characters, so the length of the string must be
    // equal to 2 at minimum, and it must start and end with quotes.
    if ((trimmed_string.length() > 1) && ((trimmed_string[0] == '\'') &&
        (trimmed_string[trimmed_string.length()-1] == '\''))) {
        // Remove quotes and trim the text inside the quotes.
        trimmed_string = trim(trimmed_string.substr(1, trimmed_string.length() - 2));
        // Copy string contents into the vector.
        binary.assign(trimmed_string.begin(), trimmed_string.end());
    }
    // Return resulting vector or empty vector.
    return (binary);
}

void
decodeColonSeparatedHexString(const std::string& hex_string,
                              std::vector<uint8_t>& binary) {
    std::vector<std::string> split_text;
    boost::split(split_text, hex_string, boost::is_any_of(":"),
                 boost::algorithm::token_compress_off);

    std::vector<uint8_t> binary_vec;
    for (size_t i = 0; i < split_text.size(); ++i) {

        // If there are multiple tokens and the current one is empty, it
        // means that two consecutive colons were specified. This is not
        // allowed.
        if ((split_text.size() > 1) && split_text[i].empty()) {
            isc_throw(isc::BadValue, "two consecutive colons specified in"
                      " a decoded string '" << hex_string << "'");

        // Between a colon we expect at most two characters.
        } else if (split_text[i].size() > 2) {
            isc_throw(isc::BadValue, "invalid format of the decoded string"
                      << " '" << hex_string << "'");

        } else if (!split_text[i].empty()) {
            std::stringstream s;
            s << "0x";

            for (unsigned int j = 0; j < split_text[i].length(); ++j) {
                // Check if we're dealing with hexadecimal digit.
                if (!isxdigit(split_text[i][j])) {
                    isc_throw(isc::BadValue, "'" << split_text[i][j]
                              << "' is not a valid hexadecimal digit in"
                              << " decoded string '" << hex_string << "'");
                }
                s << split_text[i][j];
            }

            // The stream should now have one or two hexadecimal digits.
            // Let's convert it to a number and store in a temporary
            // vector.
            unsigned int binary_value;
            s >> std::hex >> binary_value;

            binary_vec.push_back(static_cast<uint8_t>(binary_value));
        }

    }

    // All ok, replace the data in the output vector with a result.
    binary.swap(binary_vec);
}

void
decodeFormattedHexString(const std::string& hex_string,
                         std::vector<uint8_t>& binary) {
    // If there is at least one colon we assume that the string
    // comprises octets separated by colons (e.g. MAC address notation).
    if (hex_string.find(':') != std::string::npos) {
        decodeColonSeparatedHexString(hex_string, binary);

    } else {
        std::ostringstream s;

        // If we have odd number of digits we'll have to prepend '0'.
        if (hex_string.length() % 2 != 0) {
            s << "0";
        }

        // It is ok to use '0x' prefix in a string.
        if ((hex_string.length() > 2) && (hex_string.substr(0, 2) == "0x")) {
            // Exclude '0x' from the decoded string.
            s << hex_string.substr(2);

        } else {
            // No '0x', so decode the whole string.
            s << hex_string;
        }

        try {
            // Decode the hex string.
            encode::decodeHex(s.str(), binary);

        } catch (...) {
            isc_throw(isc::BadValue, "'" << hex_string << "' is not a valid"
                      " string of hexadecimal digits");
        }
    }
}

} // namespace str
} // namespace util
} // namespace isc
