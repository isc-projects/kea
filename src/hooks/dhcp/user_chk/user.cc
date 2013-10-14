// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/hwaddr.h>
#include <dhcp/duid.h>
#include <exceptions/exceptions.h>

#include <user.h>

#include <iomanip>
#include <sstream>

//********************************* UserId ******************************
const char* UserId::HW_ADDRESS_STR = "HW_ADDR";
const char* UserId::DUID_STR = "DUID";
const char* UserId::CLIENT_ID_STR = "CLIENT_ID";

UserId::UserId(UserIdType id_type, const std::vector<uint8_t>& id)
    : id_type_(id_type), id_(id) {
    if (id.size() == 0) {
        isc_throw(isc::BadValue, "UserId id may not be blank");
    }
}

UserId::UserId(UserIdType id_type, const std::string & id_str) :
    id_type_(id_type) {

    if (id_str.empty()) {
        isc_throw(isc::BadValue, "UserId id string may not be blank");
    }

    // logic to convert id_str etc...
    // input str is expected to be 2-digits per bytes, no delims
    std::vector<uint8_t> addr_bytes;
    decodeHex(id_str, addr_bytes);

    // Attempt to instantiate the appropriate id class to leverage validation.
    switch (id_type) {
        case HW_ADDRESS: {
            isc::dhcp::HWAddr hwaddr(addr_bytes, isc::dhcp::HTYPE_ETHER);
            break;
            }
        case CLIENT_ID: {
            isc::dhcp::ClientId client_id(addr_bytes);
            break;
            }
        case DUID: {
            isc::dhcp::DUID duid(addr_bytes);
            break;
            }
        default:
            isc_throw (isc::BadValue, "Invalid id_type: " << id_type);
            break;
    }

    // It's a valid id.
    id_ = addr_bytes;
}

UserId::~UserId() {
}

const std::vector<uint8_t>&
UserId::getId() const {
    return (id_);
}

UserId::UserIdType
UserId::getType() const {
    return (id_type_);
}

std::string
UserId::toText(char delim_char) const {
    std::stringstream tmp;
    tmp << std::hex;
    bool delim = false;
    for (std::vector<uint8_t>::const_iterator it = id_.begin();
         it != id_.end(); ++it) {
        if (delim_char && delim) {
            tmp << delim_char;
        }

        tmp << std::setw(2) << std::setfill('0')
            << static_cast<unsigned int>(*it);
        delim = true;
    }

    return (tmp.str());
}

bool
UserId::operator ==(const UserId & other) const {
    return ((this->id_type_ == other.id_type_) && (this->id_ == other.id_));
}

bool
UserId::operator !=(const UserId & other) const {
    return (!(*this == other));
}

bool
UserId::operator <(const UserId & other) const {
    return ((this->id_type_ < other.id_type_) ||
            ((this->id_type_ == other.id_type_) && (this->id_ < other.id_)));
}

void
UserId::decodeHex(const std::string& input, std::vector<uint8_t>& bytes)
const {
    int len = input.size();
    if ((len % 2) != 0) {
        isc_throw (isc::BadValue,
                   "input string must be event number of digits: "
                             << input);
    }

    for (int i = 0; i < len / 2; i++) {
        unsigned int tmp;
        if (sscanf (&input[i*2], "%02x", &tmp) != 1) {
            isc_throw (isc::BadValue,
                       "input string contains invalid characters: "
                                 << input);
        }

        bytes.push_back(static_cast<uint8_t>(tmp));
    }
}

std::string
UserId::lookupTypeStr(UserIdType type) {
    const char* tmp = NULL;
    switch (type) {
        case HW_ADDRESS:
            tmp = HW_ADDRESS_STR;
            break;
        case DUID:
            tmp = DUID_STR;
            break;
        case CLIENT_ID:
            tmp = CLIENT_ID_STR;
            break;
        default:
            isc_throw(isc::BadValue, "Invalid UserIdType:" << type);
            break;
    }

    return (std::string(tmp));
}

UserId::UserIdType
UserId::lookupType(const std::string& type_str) {
    if (type_str.compare(HW_ADDRESS_STR) == 0) {
        return (HW_ADDRESS);
    } else if (type_str.compare(DUID_STR) == 0) {
        return (DUID);
    } else if (type_str.compare(CLIENT_ID_STR) == 0) {
        return (CLIENT_ID);
    }

    isc_throw(isc::BadValue, "Invalid UserIdType string:" << type_str);
}

std::ostream&
operator<<(std::ostream& os, const UserId& user_id) {
    std::string tmp = UserId::lookupTypeStr(user_id.getType());
    os << tmp << "=" << user_id.toText();
    return (os);
}

//********************************* User ******************************

User::User(const UserId& user_id) : user_id_(user_id) {
}

User::User(UserId::UserIdType id_type, const std::vector<uint8_t>& id)
    : user_id_(id_type, id) {
}

User::User(UserId::UserIdType id_type, const std::string& id_str)
    : user_id_(id_type, id_str) {
}

User::~User() {
}

const PropertyMap&
User::getProperties() const {
    return (properties_);
}

void
User::setProperties(const PropertyMap& properties) {
    properties_ = properties;
}

void User::setProperty(const std::string& name, const std::string& value) {
    if (name.empty()) {
        isc_throw (isc::BadValue, "User property name cannot be blank");
    }

    properties_[name]=value;
}

std::string
User::getProperty(const std::string& name) const {
    PropertyMap::const_iterator it = properties_.find(name);
    if (it != properties_.end()) {
        return ((*it).second);
    }

    return ("");
}

void
User::delProperty(const std::string & name) {
    PropertyMap::iterator it = properties_.find(name);
    if (it != properties_.end()) {
        properties_.erase(it);
    }
}

const UserId&
User::getUserId() const {
    return (user_id_);
}
