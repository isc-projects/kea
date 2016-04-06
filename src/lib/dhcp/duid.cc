// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp/duid.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>
#include <util/strutil.h>
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
    std::vector<uint8_t> binary;
    util::str::decodeFormattedHexString(text, binary);
    return (DUID(binary));
}

DuidPtr
DUID::generateEmpty() {

    // Technically this is a one byte DUID with value of 0. However, we do have
    // a number of safety checks against invalid duids (too long or empty) and
    // we should keep them. Therefore "empty" means a single byte with value of 0.
    std::vector<uint8_t> empty_duid(1,0);

    DuidPtr duid(new DUID(empty_duid));
    return (duid);
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
    std::vector<uint8_t> binary;
    util::str::decodeFormattedHexString(text, binary);
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
