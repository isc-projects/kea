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

#include <config.h>

#include <string>

#include <boost/lexical_cast.hpp>

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;
using namespace boost;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE


HINFO::HINFO(const string& hinfo_str) {
    string::const_iterator input_iterator = hinfo_str.begin();
    cpu_ = getNextCharacterString(hinfo_str, input_iterator);

    skipLeftSpaces(hinfo_str, input_iterator);

    os_ = getNextCharacterString(hinfo_str, input_iterator);
}

HINFO::HINFO(InputBuffer& buffer, size_t rdata_len) {
    cpu_ = getNextCharacterString(buffer, rdata_len);
    os_ = getNextCharacterString(buffer, rdata_len);
}

HINFO::HINFO(const HINFO& source):
    Rdata(), cpu_(source.cpu_), os_(source.os_)
{
}

std::string
HINFO::toText() const {
    string result;
    result += "\"";
    result += cpu_;
    result += "\" \"";
    result += os_;
    result += "\"";
    return (result);
}

void
HINFO::toWire(OutputBuffer& buffer) const {
    buffer.writeUint8(cpu_.size());
    buffer.writeData(cpu_.c_str(), cpu_.size());

    buffer.writeUint8(os_.size());
    buffer.writeData(os_.c_str(), os_.size());
}

void
HINFO::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeUint8(cpu_.size());
    renderer.writeData(cpu_.c_str(), cpu_.size());

    renderer.writeUint8(os_.size());
    renderer.writeData(os_.c_str(), os_.size());
}

int
HINFO::compare(const Rdata& other) const {
    const HINFO& other_hinfo = dynamic_cast<const HINFO&>(other);

    if (cpu_ < other_hinfo.cpu_) {
        return (-1);
    } else if (cpu_ > other_hinfo.cpu_) {
        return (1);
    }

    if (os_ < other_hinfo.os_) {
        return (-1);
    } else if (os_ > other_hinfo.os_) {
        return (1);
    }

    return (0);
}

const std::string&
HINFO::getCPU() const {
    return (cpu_);
}

const std::string&
HINFO::getOS() const {
    return (os_);
}

void
HINFO::skipLeftSpaces(const std::string& input_str,
                      std::string::const_iterator& input_iterator)
{
    if (input_iterator >= input_str.end()) {
        isc_throw(InvalidRdataText,
                  "Invalid HINFO text format, field is missing.");
    }

    if (!isspace(*input_iterator)) {
        isc_throw(InvalidRdataText,
            "Invalid HINFO text format, fields are not separated by space.");
    }
    // Skip white spaces
    while (input_iterator < input_str.end() && isspace(*input_iterator)) {
        ++input_iterator;
    }
}

std::string
HINFO::getNextCharacterString(const std::string& input_str,
                              std::string::const_iterator& input_iterator)
{
    string result;

    // If the input string only contains white-spaces, it is an invalid
    // <character-string>
    if (input_iterator >= input_str.end()) {
        isc_throw(InvalidRdataText, "Invalid HINFO text format, \
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
                ++input_iterator;
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
        isc_throw(CharStringTooLong, "HINFO <character-string> is too long");
    }

    return (result);
}

std::string
HINFO::getNextCharacterString(InputBuffer& buffer, size_t len) {
    uint8_t str_len = buffer.readUint8();

    size_t pos = buffer.getPosition();
    if (len - pos < str_len) {
        isc_throw(InvalidRdataLength, "Invalid HINFO string length");
    }

    uint8_t buf[MAX_CHARSTRING_LEN];
    buffer.readData(buf, str_len);
    return (string(buf, buf + str_len));
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
