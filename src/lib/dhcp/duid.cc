// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/duid.h>
#include <exceptions/exceptions.h>
#include <util/encode/hex.h>
#include <util/io_utilities.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <vector>

#include <stdint.h>

namespace isc {
namespace dhcp {

DUID::DUID(const std::vector<uint8_t>& duid) {
    if (duid.size() > MAX_DUID_LEN) {
        isc_throw(isc::BadValue, "DUID too large");
    }
    if (duid.empty()) {
        isc_throw(isc::BadValue, "Empty DUIDs are not allowed");
    }
    duid_ = duid;
}

DUID::DUID(const uint8_t* data, size_t len) {
    if (len > MAX_DUID_LEN) {
        isc_throw(isc::BadValue, "DUID too large");
    }
    if (len == 0) {
        isc_throw(isc::BadValue, "Empty DUIDs/Client-ids not allowed");
    }

    duid_ = std::vector<uint8_t>(data, data + len);
}

std::vector<uint8_t>
DUID::decode(const std::string& text) {
    /// @todo optimize stream operations here.
    std::vector<std::string> split_text;
    boost::split(split_text, text, boost::is_any_of(":"),
                 boost::algorithm::token_compress_off);

    std::ostringstream s;
    for (size_t i = 0; i < split_text.size(); ++i) {
        // Check that only hexadecimal digits are used.
        size_t ch_index = 0;
        while (ch_index < split_text[i].length()) {
            if (!isxdigit(split_text[i][ch_index])) {
                isc_throw(isc::BadValue, "invalid value '"
                          << split_text[i][ch_index] << "' in"
                          << " DUID '" << text << "'");
            }
            ++ch_index;
        }

        if (split_text.size() > 1) {
            // If there are multiple tokens and the current one is empty, it
            // means that two consecutive colons were specified. This is not
            // allowed for client identifier.
            if (split_text[i].empty()) {
                isc_throw(isc::BadValue, "invalid identifier '"
                          << text << "': tokens must be"
                          " separated with a single colon");
            } else if (split_text[i].size() > 2) {
                isc_throw(isc::BadValue, "invalid identifier '"
                          << text << "'");
            }
        }

        if (split_text[i].size() % 2) {
                s << "0";
        }

        s << split_text[i];
    }

    std::vector<uint8_t> binary;
    try {
        util::encode::decodeHex(s.str(), binary);
    } catch (const Exception& ex) {
        isc_throw(isc::BadValue, "failed to create identifier from text '"
                  << text << "': " << ex.what());
    }
    return (binary);
}

const std::vector<uint8_t>& DUID::getDuid() const {
    return (duid_);
}

DUID::DUIDType DUID::getType() const {
    if (duid_.size() < 2) {
        return (DUID_UNKNOWN);
    }
    uint16_t type = (duid_[0] << 8) + duid_[1];
    if (type < DUID_MAX) {
        return (static_cast<DUID::DUIDType>(type));
    } else {
        return (DUID_UNKNOWN);
    }
}

DUID
DUID::fromText(const std::string& text) {
    std::vector<uint8_t> binary = decode(text);
    return DUID(binary);
}

std::string DUID::toText() const {
    std::stringstream tmp;
    tmp << std::hex;
    bool delim = false;
    for (std::vector<uint8_t>::const_iterator it = duid_.begin();
         it != duid_.end(); ++it) {
        if (delim) {
            tmp << ":";
        }
        tmp << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(*it);
        delim = true;
    }
    return (tmp.str());
}

bool DUID::operator==(const DUID& other) const {
    return (this->duid_ == other.duid_);
}

bool DUID::operator!=(const DUID& other) const {
    return (this->duid_ != other.duid_);
}

// Constructor based on vector<uint8_t>
ClientId::ClientId(const std::vector<uint8_t>& clientid)
    : DUID(clientid) {
    if (clientid.size() < MIN_CLIENT_ID_LEN) {
        isc_throw(isc::BadValue, "client-id is too short (" << clientid.size()
                  << "), at least 2 is required");
    }
}

// Constructor based on C-style data
ClientId::ClientId(const uint8_t *clientid, size_t len)
    : DUID(clientid, len) {
    if (len < MIN_CLIENT_ID_LEN) {
        isc_throw(isc::BadValue, "client-id is too short (" << len
                  << "), at least 2 is required");
    }
}

// Returns a copy of client-id data
const std::vector<uint8_t>& ClientId::getClientId() const {
    return (duid_);
}

// Returns the Client ID in text form
std::string ClientId::toText() const {

    // As DUID is a private base class of ClientId, we can't access
    // its public toText() method through inheritance: instead we
    // need the interface of a ClientId::toText() that calls the
    // equivalent method in the base class.
    return (DUID::toText());
}

ClientIdPtr
ClientId::fromText(const std::string& text) {
    std::vector<uint8_t> binary = decode(text);
    return (ClientIdPtr(new ClientId(binary)));
}

// Compares two client-ids
bool ClientId::operator==(const ClientId& other) const {
    return (this->duid_ == other.duid_);
}

// Compares two client-ids
bool ClientId::operator!=(const ClientId& other) const {
    return (this->duid_ != other.duid_);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
