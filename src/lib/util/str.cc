// Copyright (C) 2011-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/encode/encode.h>
#include <util/str.h>

#include <cstddef>
#include <cstdint>
#include <exception>
#include <iomanip>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>

using namespace std;

namespace isc {
namespace util {
namespace str {

string
trim(const string& input) {
    if (input.empty()) {
        return (string());
    }
    static const char* blanks = " \t\n";

    // Search for first non-blank character in the string.
    size_t const first(input.find_first_not_of(blanks));
    if (first == string::npos) {
        return (string());
    }

    // String not all blanks, so look for last character.
    size_t const last(input.find_last_not_of(blanks));

    // Extract the trimmed substring.
    return (input.substr(first, (last - first + 1)));
}

vector<string>
tokens(const string& text, const string& delim, bool escape) {
    vector<string> result;
    string token;
    bool in_token = false;
    bool escaped = false;
    for (auto const& c : text) {
        if (delim.find(c) != string::npos) {
            // Current character is a delimiter
            if (!in_token) {
                // Two or more delimiters, eat them
            } else if (escaped) {
                // Escaped delimiter in a token: reset escaped and keep it
                escaped = false;
                token.push_back(c);
            } else {
                // End of the current token: save it if not empty
                if (!token.empty()) {
                    result.push_back(token);
                }
                // Reset state
                in_token = false;
                token.clear();
            }
        } else if (escape && (c == '\\')) {
            // Current character is the escape character
            if (!in_token) {
                // The escape character is the first character of a new token
                in_token = true;
            }
            if (escaped) {
                // Escaped escape: reset escaped and keep one character
                escaped = false;
                token.push_back(c);
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
                token.push_back(c);
            } else {
                // The common case: keep it
                token.push_back(c);
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

char
toUpper(char const chr) {
    return (toupper(chr));
}

void
uppercase(string& text) {
    transform(text.begin(), text.end(), text.begin(), toUpper);
}

char
toLower(char const chr) {
    return (tolower(static_cast<int>(chr)));
}

void
lowercase(string& text) {
    transform(text.begin(), text.end(), text.begin(), toLower);
}

vector<uint8_t>
quotedStringToBinary(const string& quoted_string) {
    vector<uint8_t> binary;
    // Remove whitespace before and after the quotes.
    string trimmed_string = trim(quoted_string);

    // We require two quote characters, so the length of the string must be
    // equal to 2 at minimum, and it must start and end with quotes.
    if ((trimmed_string.length() > 1) &&
        ((trimmed_string[0] == '\'') && (trimmed_string[trimmed_string.length() - 1] == '\''))) {
        // Remove quotes and trim the text inside the quotes.
        trimmed_string = trim(trimmed_string.substr(1, trimmed_string.length() - 2));
        // Copy string contents into the vector.
        binary.assign(trimmed_string.begin(), trimmed_string.end());
    }
    // Return resulting vector or empty vector.
    return (binary);
}

void
decodeColonSeparatedHexString(const string& hex_string, vector<uint8_t>& binary) {
    decodeSeparatedHexString(hex_string, ":", binary);
}

void
decodeSeparatedHexString(const string& hex_string, const string& sep, vector<uint8_t>& binary) {
    vector<string> split_text;
    boost::split(split_text, hex_string, boost::is_any_of(sep),
                 boost::algorithm::token_compress_off);

    vector<uint8_t> binary_vec;
    for (size_t i = 0; i < split_text.size(); ++i) {
        // If there are multiple tokens and the current one is empty, it
        // means that two consecutive colons were specified. This is not
        // allowed.
        if ((split_text.size() > 1) && split_text[i].empty()) {
            isc_throw(BadValue, "two consecutive separators ('"
                                    << sep << "') specified in a decoded string '" << hex_string
                                    << "'");

            // Between a colon we expect at most two characters.
        } else if (split_text[i].size() > 2) {
            isc_throw(BadValue, "invalid format of the decoded string"
                                    << " '" << hex_string << "'");

        } else if (!split_text[i].empty()) {
            stringstream s;
            s << "0x";

            for (unsigned int j = 0; j < split_text[i].length(); ++j) {
                // Check if we're dealing with hexadecimal digit.
                if (!isxdigit(split_text[i][j])) {
                    isc_throw(BadValue, "'" << split_text[i][j]
                                            << "' is not a valid hexadecimal digit in"
                                            << " decoded string '" << hex_string << "'");
                }
                s << split_text[i][j];
            }

            // The stream should now have one or two hexadecimal digits.
            // Let's convert it to a number and store in a temporary
            // vector.
            unsigned int binary_value;
            s >> hex >> binary_value;

            binary_vec.push_back(static_cast<uint8_t>(binary_value));
        }
    }

    // All ok, replace the data in the output vector with a result.
    binary.swap(binary_vec);
}

void
decodeFormattedHexString(const string& hex_string, vector<uint8_t>& binary) {
    // If there is at least one colon we assume that the string
    // comprises octets separated by colons (e.g. MAC address notation).
    if (hex_string.find(':') != string::npos) {
        decodeSeparatedHexString(hex_string, ":", binary);
    } else if (hex_string.find(' ') != string::npos) {
        decodeSeparatedHexString(hex_string, " ", binary);
    } else {
        ostringstream s;

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
            isc_throw(BadValue, "'" << hex_string
                                    << "' is not a valid"
                                       " string of hexadecimal digits");
        }
    }
}

class StringSanitizerImpl {
public:
    /// @brief Constructor.
    StringSanitizerImpl(const string& char_set, const string& char_replacement)
        : char_set_(char_set), char_replacement_(char_replacement) {
        if (char_set.size() > StringSanitizer::MAX_DATA_SIZE) {
            isc_throw(BadValue, "char set size: '" << char_set.size() << "' exceeds max size: '"
                                                   << StringSanitizer::MAX_DATA_SIZE << "'");
        }

        if (char_replacement.size() > StringSanitizer::MAX_DATA_SIZE) {
            isc_throw(BadValue, "char replacement size: '"
                                    << char_replacement.size() << "' exceeds max size: '"
                                    << StringSanitizer::MAX_DATA_SIZE << "'");
        }
        try {
            scrub_exp_ = regex(char_set, regex::extended);
        } catch (const exception& ex) {
            isc_throw(BadValue, "invalid regex: '" << char_set_ << "', " << ex.what());
        }
    }

    string scrub(const string& original) {
        stringstream result;
        try {
            regex_replace(ostream_iterator<char>(result), original.begin(), original.end(),
                          scrub_exp_, char_replacement_);
        } catch (const exception& ex) {
            isc_throw(BadValue, "replacing '" << char_set_ << "' with '" << char_replacement_
                                              << "' in '" << original << "' failed: ,"
                                              << ex.what());
        }

        return (result.str());
    }

private:
    /// @brief The char set data for regex.
    string char_set_;

    /// @brief The char replacement data for regex.
    string char_replacement_;

    regex scrub_exp_;
};

// @note The regex engine is implemented using recursion and can cause
// stack overflow if the input data is too large. An arbitrary size of
// 4096 should be enough for all cases.
const uint32_t StringSanitizer::MAX_DATA_SIZE = 4096;

StringSanitizer::StringSanitizer(const string& char_set, const string& char_replacement)
    : impl_(new StringSanitizerImpl(char_set, char_replacement)) {
}

string
StringSanitizer::scrub(const string& original) {
    return (impl_->scrub(original));
}

bool
isPrintable(const string& content) {
    for (char const ch : content) {
        if (isprint(ch) == 0) {
            return (false);
        }
    }
    return (true);
}

bool
isPrintable(const vector<uint8_t>& content) {
    for (uint8_t const ch : content) {
        if (isprint(ch) == 0) {
            return (false);
        }
    }
    return (true);
}

string
dumpAsHex(const uint8_t* data, size_t length) {
    stringstream output;
    for (size_t i = 0; i < length; ++i) {
        if (i) {
            output << ":";
        }

        output << setfill('0') << setw(2) << hex << static_cast<unsigned short>(data[i]);
    }

    return (output.str());
}

}  // namespace str
}  // namespace util
}  // namespace isc
