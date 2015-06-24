// Copyright (C) 2012, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>

#include <dns/exceptions.h>
#include <dns/rdata.h>
#include <dns/master_lexer.h>
#include <dns/rdata/generic/detail/char_string.h>
#include <util/buffer.h>

#include <boost/lexical_cast.hpp>

#include <cassert>
#include <cctype>
#include <cstring>
#include <vector>

#include <stdint.h>

namespace isc {
namespace dns {
namespace rdata {
namespace generic {
namespace detail {

namespace {
// Convert a DDD form to the corresponding integer
int
decimalToNumber(const char* s, const char* s_end) {
    if (s_end - s < 3) {
        isc_throw(InvalidRdataText, "Escaped digits too short");
    }

    const std::string num_str(s, s + 3);
    try {
        const int i = boost::lexical_cast<int>(num_str);
        if (i > 255) {
            isc_throw(InvalidRdataText, "Escaped digits too large: "
                      << num_str);
        }
        return (i);
    } catch (const boost::bad_lexical_cast&) {
        isc_throw(InvalidRdataText,
                  "Invalid form for escaped digits: " << num_str);
    }
}
}

void
stringToCharString(const MasterToken::StringRegion& str_region,
                   CharString& result)
{
    // make a space for the 1-byte length field; filled in at the end
    result.push_back(0);

    bool escape = false;
    const char* s = str_region.beg;
    const char* const s_end = str_region.beg + str_region.len;

    for (size_t n = str_region.len; n != 0; --n, ++s) {
        int c = (*s & 0xff);
        if (escape && std::isdigit(c) != 0) {
            c = decimalToNumber(s, s_end);
            assert(n >= 3);
            n -= 2;
            s += 2;
        } else if (!escape && c == '\\') {
            escape = true;
            continue;
        }
        escape = false;
        result.push_back(c);
    }
    if (escape) {               // terminated by non-escaped '\'
        isc_throw(InvalidRdataText, "character-string ends with '\\'");
    }
    if (result.size() > MAX_CHARSTRING_LEN + 1) { // '+ 1' due to the len field
        isc_throw(CharStringTooLong, "character-string is too long: " <<
                  (result.size() - 1) << "(+1) characters");
    }
    result[0] = result.size() - 1;
}

void
stringToCharStringData(const MasterToken::StringRegion& str_region,
                       CharStringData& result)
{
    bool escape = false;
    const char* s = str_region.beg;
    const char* const s_end = str_region.beg + str_region.len;

    for (size_t n = str_region.len; n != 0; --n, ++s) {
        int c = (*s & 0xff);
        if (escape && std::isdigit(c) != 0) {
            c = decimalToNumber(s, s_end);
            // decimalToNumber() already throws if (s_end - s) is less
            // than 3, so the following assertion is unnecessary. But we
            // assert it anyway. 'n' is an unsigned type (size_t) and
            // can underflow.
            assert(n >= 3);
            // 'n' and 's' are also updated by 1 in the for statement's
            // expression, so we update them by 2 instead of 3 here.
            n -= 2;
            s += 2;
        } else if (!escape && c == '\\') {
            escape = true;
            continue;
        }
        escape = false;
        result.push_back(c);
    }
    if (escape) {               // terminated by non-escaped '\'
        isc_throw(InvalidRdataText, "character-string ends with '\\'");
    }
}

std::string
charStringToString(const CharString& char_string) {
    std::string s;
    for (CharString::const_iterator it = char_string.begin() + 1;
         it != char_string.end(); ++it) {
        const uint8_t ch = *it;
        if ((ch < 0x20) || (ch >= 0x7f)) {
            // convert to escaped \xxx (decimal) format
            s.push_back('\\');
            s.push_back('0' + ((ch / 100) % 10));
            s.push_back('0' + ((ch / 10) % 10));
            s.push_back('0' + (ch % 10));
            continue;
        }
        if ((ch == '"') || (ch == ';') || (ch == '\\')) {
            s.push_back('\\');
        }
        s.push_back(ch);
    }

    return (s);
}

std::string
charStringDataToString(const CharStringData& char_string) {
    std::string s;
    for (CharString::const_iterator it = char_string.begin();
         it != char_string.end(); ++it) {
        const uint8_t ch = *it;
        if ((ch < 0x20) || (ch >= 0x7f)) {
            // convert to escaped \xxx (decimal) format
            s.push_back('\\');
            s.push_back('0' + ((ch / 100) % 10));
            s.push_back('0' + ((ch / 10) % 10));
            s.push_back('0' + (ch % 10));
            continue;
        }
        if ((ch == '"') || (ch == ';') || (ch == '\\')) {
            s.push_back('\\');
        }
        s.push_back(ch);
    }

    return (s);
}

int compareCharStrings(const detail::CharString& self,
                       const detail::CharString& other) {
    if (self.size() == 0 && other.size() == 0) {
        return (0);
    }
    if (self.size() == 0) {
        return (-1);
    }
    if (other.size() == 0) {
        return (1);
    }
    const size_t self_len = self[0];
    const size_t other_len = other[0];
    const size_t cmp_len = std::min(self_len, other_len);
    if (cmp_len == 0) {
        if (self_len < other_len) {
            return (-1);
        } else if (self_len > other_len) {
            return (1);
        } else {
            return (0);
        }
    }
    const int cmp = std::memcmp(&self[1], &other[1], cmp_len);
    if (cmp < 0) {
        return (-1);
    } else if (cmp > 0) {
        return (1);
    } else if (self_len < other_len) {
        return (-1);
    } else if (self_len > other_len) {
        return (1);
    } else {
        return (0);
    }
}

int compareCharStringDatas(const detail::CharStringData& self,
                           const detail::CharStringData& other) {
    if (self.size() == 0 && other.size() == 0) {
        return (0);
    }
    if (self.size() == 0) {
        return (-1);
    }
    if (other.size() == 0) {
        return (1);
    }
    const size_t self_len = self.size();
    const size_t other_len = other.size();
    const size_t cmp_len = std::min(self_len, other_len);
    const int cmp = std::memcmp(&self[0], &other[0], cmp_len);
    if (cmp < 0) {
        return (-1);
    } else if (cmp > 0) {
        return (1);
    } else if (self_len < other_len) {
        return (-1);
    } else if (self_len > other_len) {
        return (1);
    } else {
        return (0);
    }
}

size_t
bufferToCharString(isc::util::InputBuffer& buffer, size_t rdata_len,
                   CharString& target) {
    if (rdata_len < 1 || buffer.getLength() - buffer.getPosition() < 1) {
        isc_throw(isc::dns::DNSMessageFORMERR,
                  "insufficient data to read character-string length");
    }
    const uint8_t len = buffer.readUint8();
    if (rdata_len < len + 1) {
        isc_throw(isc::dns::DNSMessageFORMERR,
                  "character string length is too large: " <<
                  static_cast<int>(len));
    }
    if (buffer.getLength() - buffer.getPosition() < len) {
        isc_throw(isc::dns::DNSMessageFORMERR,
                  "not enough data in buffer to read character-string of len"
                  << static_cast<int>(len));
    }

    target.resize(len + 1);
    target[0] = len;
    buffer.readData(&target[0] + 1, len);

    return (len + 1);
}

} // end of detail
} // end of generic
} // end of rdata
} // end of dns
} // end of isc
