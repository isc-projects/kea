// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/duid_factory.h>
#include <dhcpsrv/cfg_duid.h>
#include <util/encode/hex.h>
#include <util/strutil.h>
#include <iostream>

using namespace isc;
using namespace isc::util::encode;
using namespace isc::util::str;

namespace isc {
namespace dhcp {

CfgDUID::CfgDUID()
    : type_(DUID::DUID_LLT), identifier_(), htype_(0), time_(0),
      enterprise_id_(0) {
}

void
CfgDUID::setIdentifier(const std::string& identifier_as_hex) {
    // Remove whitespaces.
    const std::string identifier = trim(identifier_as_hex);
    // Temporary result of parsing.
    std::vector<uint8_t> binary;
    if (!identifier.empty()) {
        try {
            // Decode identifier specified as a string of hexadecimal digits.
            decodeHex(identifier, binary);
            // All went ok, so let's replace identifier with a new value.
            identifier_.swap(binary);
        } catch (const std::exception& ex) {
            isc_throw(BadValue, "identifier specified in the DUID"
                      " configuration '" << identifier
                      << "' is not a valid string of hexadecimal digits");
        }

    } else {
         // If specified identifier is empty, clear our internal identifier.
        identifier_.clear();
    }
}

DuidPtr
CfgDUID::create(const std::string& duid_file_path) const {
    // Use DUID factory to create a DUID instance.
    DUIDFactory factory(duid_file_path);

    switch (getType()) {
    case DUID::DUID_LLT:
        factory.createLLT(getHType(), getTime(), getIdentifier());
        break;
    case DUID::DUID_EN:
        factory.createEN(getEnterpriseId(), getIdentifier());
        break;
    case DUID::DUID_LL:
        factory.createLL(getHType(), getIdentifier());
        break;
    default:
        // This should actually never happen.
        isc_throw(Unexpected, "invalid DUID type used " << getType()
                  << " to create a new DUID");
    }

    // Return generated DUID.
    return (factory.get());
}


}
}
