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

#include <dns/character_string.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;
using boost::lexical_cast;
using namespace isc::util;
using namespace isc::dns;
using namespace isc::dns::characterstr;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

namespace {
/// Skip the left whitespaces of the input string
///
/// \param input_str The input string
/// \param input_iterator From which the skipping started
void
skipLeftSpaces(const std::string& input_str,
               std::string::const_iterator& input_iterator)
{
    if (input_iterator >= input_str.end()) {
        isc_throw(InvalidRdataText,
                  "Invalid NAPTR text format, field is missing.");
    }

    if (!isspace(*input_iterator)) {
        isc_throw(InvalidRdataText,
            "Invalid NAPTR text format, fields are not separated by space.");
    }
    // Skip white spaces
    while (input_iterator < input_str.end() && isspace(*input_iterator)) {
        ++input_iterator;
    }
}

} // Anonymous namespace

NAPTR::NAPTR(InputBuffer& buffer, size_t len):
    replacement_(".")
{
    order_ = buffer.readUint16();
    preference_ = buffer.readUint16();

    flags_ = getNextCharacterString(buffer, len);
    services_ = getNextCharacterString(buffer, len);
    regexp_ = getNextCharacterString(buffer, len);
    replacement_ = Name(buffer);
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

    skipLeftSpaces(naptr_str, input_iterator);

    flags_ = getNextCharacterString(naptr_str, input_iterator);

    skipLeftSpaces(naptr_str, input_iterator);

    services_ = getNextCharacterString(naptr_str, input_iterator);

    skipLeftSpaces(naptr_str, input_iterator);

    regexp_ = getNextCharacterString(naptr_str, input_iterator);

    skipLeftSpaces(naptr_str, input_iterator);

    if (input_iterator < naptr_str.end()) {
        string replacementStr(input_iterator, naptr_str.end());

        replacement_ = Name(replacementStr);
    } else {
        isc_throw(InvalidRdataText,
                  "Invalid NAPTR text format, replacement field is missing");
    }
}

NAPTR::NAPTR(const NAPTR& naptr):
    Rdata(), order_(naptr.order_), preference_(naptr.preference_),
    flags_(naptr.flags_), services_(naptr.services_), regexp_(naptr.regexp_),
    replacement_(naptr.replacement_)
{
}

void
NAPTR::toWire(OutputBuffer& buffer) const {
    toWireHelper(buffer);
    replacement_.toWire(buffer);

}

void
NAPTR::toWire(AbstractMessageRenderer& renderer) const {
    toWireHelper(renderer);
    // Type NAPTR is not "well-known", and name compression must be disabled
    // per RFC3597.
    renderer.writeName(replacement_, false);
}

string
NAPTR::toText() const {
    string result;
    result += lexical_cast<string>(order_);
    result += " ";
    result += lexical_cast<string>(preference_);
    result += " \"";
    result += flags_;
    result += "\" \"";
    result += services_;
    result += "\" \"";
    result += regexp_;
    result += "\" ";
    result += replacement_.toText();
    return (result);
}

int
NAPTR::compare(const Rdata& other) const {
    const NAPTR other_naptr = dynamic_cast<const NAPTR&>(other);

    if (order_ < other_naptr.order_) {
        return (-1);
    } else if (order_ > other_naptr.order_) {
        return (1);
    }

    if (preference_ < other_naptr.preference_) {
        return (-1);
    } else if (preference_ > other_naptr.preference_) {
        return (1);
    }

    if (flags_ < other_naptr.flags_) {
        return (-1);
    } else if (flags_ > other_naptr.flags_) {
        return (1);
    }

    if (services_ < other_naptr.services_) {
        return (-1);
    } else if (services_ > other_naptr.services_) {
        return (1);
    }

    if (regexp_ < other_naptr.regexp_) {
        return (-1);
    } else if (regexp_ > other_naptr.regexp_) {
        return (1);
    }

    return (compareNames(replacement_, other_naptr.replacement_));
}

uint16_t
NAPTR::getOrder() const {
    return (order_);
}

uint16_t
NAPTR::getPreference() const {
    return (preference_);
}

const std::string&
NAPTR::getFlags() const {
    return (flags_);
}

const std::string&
NAPTR::getServices() const {
    return (services_);
}

const std::string&
NAPTR::getRegexp() const {
    return (regexp_);
}

const Name&
NAPTR::getReplacement() const {
    return (replacement_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
