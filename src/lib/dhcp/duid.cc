// Copyright (C) 2012-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/duid.h>
#include <exceptions/exceptions.h>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <vector>

#include <stdint.h>

namespace isc {
namespace dhcp {

IdentifierBaseType::~IdentifierBaseType() {
}

constexpr size_t DUID::MIN_DUID_LEN;
constexpr size_t DUID::MAX_DUID_LEN;

DUID::DUID(const std::vector<uint8_t>& data) : IdentifierType<3, 130>(data) {
}

DUID::DUID(const uint8_t* data, size_t len) : IdentifierType<3, 130>(data, len) {
}

const std::vector<uint8_t>& DUID::getDuid() const {
    return (data_);
}

DUID::DUIDType DUID::getType() const {
    if (data_.size() < 2) {
        return (DUID_UNKNOWN);
    }
    uint16_t type = (data_[0] << 8) + data_[1];
    if (type < DUID_MAX) {
        return (static_cast<DUID::DUIDType>(type));
    } else {
        return (DUID_UNKNOWN);
    }
}

DUID
DUID::fromText(const std::string& text) {
    return (DUID(IdentifierType::fromText(text)));
}

const DUID&
DUID::EMPTY() {
    static DUID empty({0, 0, 0});
    return (empty);
}

constexpr size_t ClientId::MIN_CLIENT_ID_LEN;
constexpr size_t ClientId::MAX_CLIENT_ID_LEN;

ClientId::ClientId(const std::vector<uint8_t>& data) : IdentifierType<2, 255>(data) {
}

ClientId::ClientId(const uint8_t *data, size_t len) : IdentifierType<2, 255>(data, len) {
}

const std::vector<uint8_t>& ClientId::getClientId() const {
    return (data_);
}

ClientIdPtr ClientId::fromText(const std::string& text) {
    return (ClientIdPtr(new ClientId(IdentifierType::fromText(text))));
}

}  // namespace dhcp
}  // namespace isc
