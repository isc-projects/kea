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

#ifndef _USER_H
#define _USER_H

#include <boost/shared_ptr.hpp>

#include <vector>
#include <map>

class UserId {
public:
    enum UserIdType {
        HW_ADDRESS,
        DUID,
        CLIENT_ID
    };

    static const char* HW_ADDRESS_STR;
    static const char* DUID_STR;
    static const char* CLIENT_ID_STR; 

    UserId(UserIdType id_type, const std::vector<uint8_t>& id);

    UserId(UserIdType id_type, const std::string& id_str);

    ~UserId();

    /// @brief Returns a const reference to the actual id value
    const std::vector<uint8_t>& getId() const;

    /// @brief Returns the UserIdType 
    UserIdType getType() const;

    /// @brief Returns textual representation of a id (e.g. 00:01:02:03:ff)
    std::string toText(char delim_char=0x0) const;

    /// @brief Compares two UserIds for equality
    bool operator ==(const UserId & other) const;

    /// @brief Compares two UserIds for inequality
    bool operator !=(const UserId & other) const;

    /// @brief Performs less than comparision of two UserIds
    bool operator <(const UserId & other) const;

    static std::string lookupTypeStr(UserIdType type);

    static UserIdType lookupType(const std::string& type_str);

private:
    void decodeHex(const std::string& input, std::vector<uint8_t>& bytes) const;

    /// @brief The type of id value 
    UserIdType id_type_;

    /// @brief The id value 
    std::vector<uint8_t> id_;

};

std::ostream&
operator<<(std::ostream& os, const UserId& user_id);

typedef boost::shared_ptr<UserId> UserIdPtr;

typedef std::map<std::string, std::string> PropertyMap;

class User {
public:

    User(const UserId & user_id);

    User(UserId::UserIdType id_type, const std::vector<uint8_t>& id);

    User(UserId::UserIdType id_type, const std::string& id_str);

    ~User();

    void setProperty(const std::string& name, const std::string& value);

    std::string getProperty(const std::string& name) const;

    void delProperty(const std::string& name);

    const UserId& getUserId() const;

private:

    UserId user_id_;

    PropertyMap properties_;
};

typedef boost::shared_ptr<User> UserPtr;

#endif
