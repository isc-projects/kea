// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <util/io_utilities.h>

#include <iomanip>
#include <sstream>
#include <vector>

#include <stdint.h>

namespace isc {
namespace dhcp {

DUID::DUID(const std::vector<uint8_t>& duid) {
    if (duid.size() > MAX_DUID_LEN) {
        isc_throw(OutOfRange, "DUID too large");
    } else {
        duid_ = duid;
    }
}

DUID::DUID(const uint8_t* data, size_t len) {
    if (len > MAX_DUID_LEN) {
        isc_throw(OutOfRange, "DUID too large");
    }

    duid_ = std::vector<uint8_t>(data, data + len);
}

const std::vector<uint8_t> DUID::getDuid() const {
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
}

// Constructor based on C-style data
ClientId::ClientId(const uint8_t *clientid, size_t len)
    : DUID(clientid, len) {
}

// Returns a copy of client-id data
const std::vector<uint8_t> ClientId::getClientId() const {
    return (duid_);
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
