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

std::string
characterstr::getNextCharacterString(const std::string& input_str,
                              std::string::const_iterator& input_iterator)
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

    if (quotes_separated) {
        ++input_iterator;
    }

    while(input_iterator < input_str.end()){
        if (quotes_separated) {
            // If the <character-string> is seperated with quotes symbol and
            // another quotes symbol is encountered, it is the end of the
            // <character-string>
            if (*input_iterator == '"') {
                // Inside a " delimited string any character can occur, except
                // for a " itself, which must be quoted using \ (back slash).
                if (*(input_iterator - 1) == '\\') {
                    // pop the '\' character
                    result.resize(result.size() - 1);
                } else {
                    ++input_iterator;
                    // Reach the end of character string
                    break;
                }
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
