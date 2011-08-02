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

#include <util/buffer.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;
using namespace boost;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

NAPTR::NAPTR(InputBuffer& buffer, size_t len):
    replacement_(".")
{
}

NAPTR::NAPTR(const std::string& naptr_str):
    replacement_(".")
{
    istringstream iss(naptr_str);
    uint16_t order;
    uint16_t preference;

    iss >> order >> preference;

    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid NAPTR text format");
    }

    order_ = order;
    preference_ = preference;

    string::const_iterator input_iterator = naptr_str.begin() + iss.tellg();
    flags_ = getNextCharacterString(naptr_str, input_iterator);
}

NAPTR::NAPTR(const NAPTR& naptr):
    replacement_(".")
{
}

void
NAPTR::toWire(OutputBuffer& buffer) const {
}

void
NAPTR::toWire(AbstractMessageRenderer& renderer) const {
}

string
NAPTR::toText() const {
    return "";
}

int
NAPTR::compare(const Rdata& other) const {
    return 0;
}

uint16_t
NAPTR::getOrder() const {
    return order_;
}

uint16_t
NAPTR::getPreference() const {
    return preference_;
}

const std::string&
NAPTR::getFlags() const {
    return flags_;
}

const std::string&
NAPTR::getServices() const {
    return services_;
}

const std::string&
NAPTR::getRegexp() const {
    return regexp_;
}

const Name&
NAPTR::getReplacement() const {
    return replacement_;
}

std::string
NAPTR::getNextCharacterString(const std::string& input_str, std::string::const_iterator& input_iterator){
    string result;

    // Skip white spaces
    while (input_iterator < input_str.end() && isspace(*input_iterator)) {
        ++input_iterator;
    }

    // If the input string only contains white-spaces, it is an invalid <character-string>
    if (input_iterator >= input_str.end()) {
        isc_throw(InvalidRdataText, "Invalid NAPTR text format");
    }

    // Whether the <character-string> is seperated with doulble quotes symbol (")
    bool quotes_seperated = (*input_iterator == '"');

    if (quotes_seperated) {
        ++input_iterator;
    }

    while(input_iterator < input_str.end()){
        if (quotes_seperated) {
            // If the <character-string> is seperated with quotes symbol and another
            // quotes symbol is encountered, it is the end of the <character-string>
            if (*input_iterator == '"') {
                break;
            }
        } else if (*input_iterator == ' ') {
            // If the <character-string> is not seperated with quotes symbol, it is 
            // seperated with <space> char
            break;
        }

        result.push_back(*input_iterator);

        ++input_iterator;
    }

    return result;
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
