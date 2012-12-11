// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include "character_string.h"
#include "rdata.h"

using namespace std;
using namespace isc::dns::rdata;

namespace isc {
namespace dns {

namespace {
bool isDigit(char c) {
    return (('0' <= c) && (c <= '9'));
}
}

std::string
characterstr::getNextCharacterString(const std::string& input_str,
                              std::string::const_iterator& input_iterator,
                              bool* quoted)
{
    string result;

    // If the input string only contains white-spaces, it is an invalid
    // <character-string>
    if (input_iterator >= input_str.end()) {
        isc_throw(InvalidRdataText, "Invalid text format, \
                  <character-string> field is missing.");
    }

    // Whether the <character-string> is separated with double quotes (")
    bool quotes_separated = (*input_iterator == '"');
    // Whether the quotes are pared if the string is quotes separated
    bool quotes_paired = false;

    if (quotes_separated) {
        ++input_iterator;
    }

    while(input_iterator < input_str.end()){
        // Escaped characters processing
        if (*input_iterator == '\\') {
            if (input_iterator + 1 == input_str.end()) {
                isc_throw(InvalidRdataText, "<character-string> ended \
                          prematurely.");
            } else {
                if (isDigit(*(input_iterator + 1))) {
                    // \DDD where each D is a digit. It its the octet
                    // corresponding to the decimal number described by DDD
                    if (input_iterator + 3 >= input_str.end()) {
                        isc_throw(InvalidRdataText, "<character-string> ended \
                                  prematurely.");
                    } else {
                        int n = 0;
                        ++input_iterator;
                        for (int i = 0; i < 3; ++i) {
                            if (isDigit(*input_iterator)) {
                                n = n*10 + (*input_iterator - '0');
                                ++input_iterator;
                            } else {
                                isc_throw(InvalidRdataText, "Illegal decimal \
                                          escaping series");
                            }
                        }
                        if (n > 255) {
                            isc_throw(InvalidRdataText, "Illegal octet \
                                      number");
                        }
                        result.push_back(n);
                        continue;
                    }
                } else {
                    ++input_iterator;
                    result.push_back(*input_iterator);
                    ++input_iterator;
                    continue;
                }
            }
        }

        if (quotes_separated) {
            // If the <character-string> is seperated with quotes symbol and
            // another quotes symbol is encountered, it is the end of the
            // <character-string>
            if (*input_iterator == '"') {
                quotes_paired = true;
                ++input_iterator;
                // Reach the end of character string
                break;
            }
        } else if (*input_iterator == ' ') {
            // If the <character-string> is not seperated with quotes symbol,
            // it is seperated with <space> char
            break;
        }

        result.push_back(*input_iterator);

        ++input_iterator;
    }

    if (result.size() > MAX_CHARSTRING_LEN) {
        isc_throw(CharStringTooLong, "<character-string> is too long");
    }

    if (quotes_separated && !quotes_paired) {
        isc_throw(InvalidRdataText, "The quotes are not paired");
    }

    if (quoted != NULL) {
        *quoted = quotes_separated;
    }

    return (result);
}

std::string
characterstr::getNextCharacterString(util::InputBuffer& buffer, size_t len) {
    uint8_t str_len = buffer.readUint8();

    size_t pos = buffer.getPosition();
    if (len - pos < str_len) {
        isc_throw(InvalidRdataLength, "Invalid string length");
    }

    uint8_t buf[MAX_CHARSTRING_LEN];
    buffer.readData(buf, str_len);
    return (string(buf, buf + str_len));
}

} // end of namespace dns
} // end of namespace isc
