// Copyright (C) 2011-2025 Internet Systems Consortium, Inc. ("ISC")
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
    if (!data) {
        return ("");
    }

    std::string tmp;
    for (size_t i = 0; i < length; ++i) {
        if (i) {
            tmp.push_back(':');
        }

        tmp.append(util::str::byteToHex(data[i]));
    }

    return (tmp);
}

string
dumpAsHex(const std::vector<uint8_t>& vec) {
   return (dumpAsHex(vec.data(), vec.size()));
}

string
dumpAsHex(const std::string& str) {
   std::vector<uint8_t> vec(str.begin(), str.end());
   return (dumpAsHex(vec));
}

string
dumpDouble(double val, size_t precision) {
    std::stringstream oss;
    oss << setprecision(precision) << val;
    return (oss.str());
}

std::string
printOrDump(const std::vector<uint8_t>& data, size_t max_dump) {
    if (data.empty()) {
        return ("");
    }

    auto it = data.begin();
    bool print_it = true;
    for ( ; it != data.end() && *it != 0; ++it) {
        if (!isprint(*it)) {
            print_it = false;
            break;
        }
    }

    if (print_it && it != data.begin()) {
        return (std::string(data.begin(), it));
    }

    bool zeros = true;
    for (auto zit = data.begin(); zit < data.end(); ++zit) {
        if (*zit != 0) {
            zeros = false;
            break;
        }
    }

    if (!zeros) {
        if (data.size() > max_dump) {
           return (dumpAsHex(&data[0], max_dump) + "..");
        }

        return (dumpAsHex(&data[0], data.size()));
    }

    return ("");
}

const std::string& byteToHex(uint8_t byte) {
    static std::vector<std::string> byte_strs{
        "00", "01", "02", "03", "04", "05", "06", "07",
        "08", "09", "0a", "0b", "0c", "0d", "0e", "0f",
        "10", "11", "12", "13", "14", "15", "16", "17",
        "18", "19", "1a", "1b", "1c", "1d", "1e", "1f",
        "20", "21", "22", "23", "24", "25", "26", "27",
        "28", "29", "2a", "2b", "2c", "2d", "2e", "2f",
        "30", "31", "32", "33", "34", "35", "36", "37",
        "38", "39", "3a", "3b", "3c", "3d", "3e", "3f",
        "40", "41", "42", "43", "44", "45", "46", "47",
        "48", "49", "4a", "4b", "4c", "4d", "4e", "4f",
        "50", "51", "52", "53", "54", "55", "56", "57",
        "58", "59", "5a", "5b", "5c", "5d", "5e", "5f",
        "60", "61", "62", "63", "64", "65", "66", "67",
        "68", "69", "6a", "6b", "6c", "6d", "6e", "6f",
        "70", "71", "72", "73", "74", "75", "76", "77",
        "78", "79", "7a", "7b", "7c", "7d", "7e", "7f",
        "80", "81", "82", "83", "84", "85", "86", "87",
        "88", "89", "8a", "8b", "8c", "8d", "8e", "8f",
        "90", "91", "92", "93", "94", "95", "96", "97",
        "98", "99", "9a", "9b", "9c", "9d", "9e", "9f",
        "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7",
        "a8", "a9", "aa", "ab", "ac", "ad", "ae", "af",
        "b0", "b1", "b2", "b3", "b4", "b5", "b6", "b7",
        "b8", "b9", "ba", "bb", "bc", "bd", "be", "bf",
        "c0", "c1", "c2", "c3", "c4", "c5", "c6", "c7",
        "c8", "c9", "ca", "cb", "cc", "cd", "ce", "cf",
        "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7",
        "d8", "d9", "da", "db", "dc", "dd", "de", "df",
        "e0", "e1", "e2", "e3", "e4", "e5", "e6", "e7",
        "e8", "e9", "ea", "eb", "ec", "ed", "ee", "ef",
        "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7",
        "f8", "f9", "fa", "fb", "fc", "fd", "fe", "ff"
    };

    return(byte_strs[byte]);
}


}  // namespace str
}  // namespace util
}  // namespace isc
