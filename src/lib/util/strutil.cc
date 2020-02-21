// Copyright (C) 2011-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/encode/hex.h>
#include <util/strutil.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>

#include <numeric>
#include <iostream>
#include <sstream>

// Early versions of C++11 regex were buggy, use it if we
// can otherwise, we fall back to regcomp/regexec.  For more info see:
// https://stackoverflow.com/questions/12530406/is-gcc-4-8-or-earlier-buggy-about-regular-expressions
#ifdef USE_REGEX
#include <regex>
#else
#include <sys/types.h>
#include <regex.h>
#endif

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
tokens(const std::string& text, const std::string& delim, bool escape) {
    vector<string> result;
    string token;
    bool in_token = false;
    bool escaped = false;
    for (auto c = text.cbegin(); c != text.cend(); ++c) {
        if (delim.find(*c) != string::npos) {
            // Current character is a delimiter
            if (!in_token) {
                // Two or more delimiters, eat them
            } else if (escaped) {
                // Escaped delimiter in a token: reset escaped and keep it
                escaped = false;
                token.push_back(*c);
            } else {
                // End of the current token: save it if not empty
                if (!token.empty()) {
                    result.push_back(token);
                }
                // Reset state
                in_token = false;
                token.clear();
            }
        } else if (escape && (*c == '\\')) {
            // Current character is the escape character
            if (!in_token) {
                // The escape character is the first character of a new token
                in_token = true;
            }
            if (escaped) {
                // Escaped escape: reset escaped and keep one character
                escaped = false;
                token.push_back(*c);
            } else {
                // Remember to keep the next character
                escaped = true;
            }
        } else {
            // Not a delimiter nor an escape
            if (!in_token) {
                // First character of a new token
                in_token = true;
            }
            if (escaped) {
                // Escaped common character: as escape was false
                escaped = false;
                token.push_back('\\');
                token.push_back(*c);
            } else {
                // The common case: keep it
                token.push_back(*c);
            }
        }
    }
    // End of input: close and save the current token if not empty
    if (escaped) {
        // Pending escape
        token.push_back('\\');
    }
    if (!token.empty()) {
        result.push_back(token);
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
    decodeSeparatedHexString(hex_string, ":", binary);
}

void
decodeSeparatedHexString(const std::string& hex_string, const std::string& sep,
                         std::vector<uint8_t>& binary) {
    std::vector<std::string> split_text;
    boost::split(split_text, hex_string, boost::is_any_of(sep),
                 boost::algorithm::token_compress_off);

    std::vector<uint8_t> binary_vec;
    for (size_t i = 0; i < split_text.size(); ++i) {

        // If there are multiple tokens and the current one is empty, it
        // means that two consecutive colons were specified. This is not
        // allowed.
        if ((split_text.size() > 1) && split_text[i].empty()) {
            isc_throw(isc::BadValue, "two consecutive separators ('" << sep << "') specified in"
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
        decodeSeparatedHexString(hex_string, ":", binary);
    } else if (hex_string.find(' ') != std::string::npos) {
        decodeSeparatedHexString(hex_string, " ", binary);
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

class StringSanitizerImpl {
public:
    StringSanitizerImpl(const std::string& char_set, const std::string& char_replacement)
        : char_set_(char_set), char_replacement_(char_replacement) {
#ifdef USE_REGEX
        try {
            scrub_exp_ = std::regex(char_set, std::regex::extended);
        } catch (const std::exception& ex) {
            isc_throw(isc::BadValue, "invalid regex: '"
                      << char_set_ << "', " << ex.what());
        }
#else
        int ec = regcomp(&scrub_exp_, char_set_.c_str(), REG_EXTENDED);
        if (ec) {
            char errbuf[512] = "";
            static_cast<void>(regerror(ec, &scrub_exp_, errbuf, sizeof(errbuf)));
            regfree(&scrub_exp_);
            isc_throw(isc::BadValue, "invalid regex: '" << char_set_ << "', " << errbuf);
        }
#endif
    }

    /// @brief Destructor.
    ~StringSanitizerImpl() {
#ifndef USE_REGEX
        regfree(&scrub_exp_);
#endif
    }

    std::string scrub(const std::string& original) {
#ifdef USE_REGEX
        std::stringstream result;
        try {
            std::regex_replace(std::ostream_iterator<char>(result),
                               original.begin(), original.end(),
                               scrub_exp_, char_replacement_);
        } catch (const std::exception& ex) {
            isc_throw(isc::BadValue, "replacing '" << char_set_ << "' with '"
                   << char_replacement_ << "' in '" << original << "' failed: ,"
                   << ex.what());
        }

        return (result.str());
#else
        // In order to handle embedded nuls, we have to process it nul-terminated
        // chunks.  We iterate over the original data, doing pattern replacement
        // on each chunk.
        const char* orig_data = original.data();
        const char* dead_end = orig_data + original.size();
        const char* start_from = orig_data;
        stringstream result;

        while (start_from < dead_end) {
            // Iterate over original string, match by match.
            regmatch_t matches[2];  // n matches + 1
            const char* end_at = start_from + strlen(start_from);

            while (start_from < end_at) {
                // Look for the next match
                if (regexec(&scrub_exp_, start_from, 1, matches, 0) == REG_NOMATCH) {
                    // No matches, so add in the remainder
                    result << start_from;
                    start_from = end_at + 1;
                    break;
                }

                // Shouldn't happen, but one never knows eh?
                if (matches[0].rm_so == -1) {
                    isc_throw(isc::Unexpected, "matched but so is -1?");
                }

                // Add everything from starting point up to the current match
                const char* match_at = start_from + matches[0].rm_so;
                while (start_from < match_at) {
                    result << *start_from;
                    ++start_from;
                }

                // Add in the replacement
                result << char_replacement_;

                // Move past the match.
                ++start_from;
            }

            // if we have an embedded nul, replace it and continue
            if (start_from < dead_end) {
                // Add in the replacement
                result << char_replacement_;
                start_from = end_at + 1;
            }
        }

        return (result.str());
#endif
    }

private:
    std::string char_set_;
    std::string char_replacement_;

#ifdef USE_REGEX
    regex scrub_exp_;
#else
    regex_t scrub_exp_;
#endif
};

StringSanitizer::StringSanitizer(const std::string& char_set,
                                 const std::string& char_replacement)
    : impl_(new StringSanitizerImpl(char_set, char_replacement)) {
}

StringSanitizer::~StringSanitizer() {
    delete impl_;
}

std::string
StringSanitizer::scrub(const std::string& original) {
    return (impl_->scrub(original));
}

} // namespace str
} // namespace util
} // namespace isc
