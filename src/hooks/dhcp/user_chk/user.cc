// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp/hwaddr.h>
#include <dhcp/duid.h>
#include <exceptions/exceptions.h>
#include <util/encode/hex.h>

#include <user.h>

#include <iomanip>
#include <sstream>

namespace user_chk {

//********************************* UserId ******************************

const char* UserId::HW_ADDRESS_STR = "HW_ADDR";
const char* UserId::DUID_STR = "DUID";

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

    // Convert the id string to vector.
    // Input is expected to be 2-digits per bytes, no delimiters.
    std::vector<uint8_t> addr_bytes;

    // Strip out colon delimeters, decodeHex doesn't like them.
    std::string clean_id_str = id_str;
    std::string::iterator end_pos = std::remove(clean_id_str.begin(),
                                                clean_id_str.end(), ':');
    clean_id_str.erase(end_pos, clean_id_str.end());

    isc::util::encode::decodeHex(clean_id_str, addr_bytes);

    // Attempt to instantiate the appropriate id class to leverage validation.
    switch (id_type) {
        case HW_ADDRESS: {
            isc::dhcp::HWAddr hwaddr(addr_bytes, isc::dhcp::HTYPE_ETHER);
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

    // Note that if the property exists its value will be updated.
    properties_[name]=value;
}

std::string
User::getProperty(const std::string& name) const {
    PropertyMap::const_iterator it = properties_.find(name);
    if (it != properties_.end()) {
        return ((*it).second);
    }

    // By returning an empty string rather than throwing, we allow the
    // flexibility of defaulting to blank if not specified.  Let the caller
    // decide if that is valid or not.
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

} // namespace user_chk
