// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef USER_H
#define USER_H

#include <boost/shared_ptr.hpp>

#include <map>
#include <stdint.h>
#include <vector>

namespace user_chk {

/// @file user.h This file defines classes: UserId and User.
/// @brief These classes are used to describe and recognize DHCP lease
/// clients.

/// @brief Encapsulates a unique identifier for a DHCP client.
/// This class provides a generic wrapper around the information used to
/// uniquely identify the requester in a DHCP request packet.  It provides
/// the necessary operators such that it can be used as a key within STL
/// containers such as maps.  It supports both IPv4 and IPv6 clients.
class UserId {
public:
    /// @brief Defines the supported types of user ids.
    // Use explicit values to ensure consistent numeric ordering for key
    // comparisons.
    enum UserIdType {
        /// @brief Hardware addresses (MAC) are used for IPv4 clients.
        HW_ADDRESS = 0,
        /// @brief DUIDs are used for IPv6 clients.
        DUID = 1
    };

    /// @brief Defines the text label hardware address id type.
    static const char* HW_ADDRESS_STR;
    /// @brief Define the text label DUID id type.
    static const char* DUID_STR;

    /// @brief Constructor
    ///
    /// Constructs a UserId from an id type and id vector.
    ///
    /// @param id_type The type of user id contained in vector
    /// @param id a vector of unsigned bytes containing the id
    ///
    /// @throw isc::BadValue if the vector is empty.
    UserId(UserIdType id_type, const std::vector<uint8_t>& id);

    /// @brief Constructor
    ///
    /// Constructs a UserId from an id type and id string.
    ///
    /// @param id_type The type of user id contained in string.
    /// The string is expected to contain an even number of hex digits
    /// with or without colon (':') as a delimiter.
    ///
    /// @param id_str string of hex digits representing the user's id
    ///
    /// @throw isc::BadValue if the string is empty, contains non
    /// valid hex digits, or an odd number of hex digits.
    UserId(UserIdType id_type, const std::string& id_str);

    /// @brief Destructor.
    ~UserId();

    /// @brief Returns a const reference to the actual id value
    const std::vector<uint8_t>& getId() const;

    /// @brief Returns the user id type
    UserIdType getType() const;

    /// @brief Returns textual representation of the id
    ///
    /// Outputs a string of hex digits representing the id with an
    /// optional delimiter between digit pairs (i.e. bytes).
    ///
    /// Without a delimiter:
    ///   "0c220F"
    ///
    /// with colon as a delimiter:
    ///   "0c:22:0F"
    ///
    /// @param delim_char The delimiter to place in between
    /// "bytes". It defaults to none.
    ///  (e.g. 00010203ff)
    std::string toText(char delim_char=0x0) const;

    /// @brief Compares two UserIds for equality
    bool operator ==(const UserId & other) const;

    /// @brief Compares two UserIds for inequality
    bool operator !=(const UserId & other) const;

    /// @brief Performs less than comparison of two UserIds
    bool operator <(const UserId & other) const;

    /// @brief Returns the text label for a given id type
    ///
    /// @param type The id type value for which the label is desired
    ///
    /// @throw isc::BadValue if type is not valid.
    static std::string lookupTypeStr(UserIdType type);

    /// @brief Returns the id type for a given text label
    ///
    /// @param type_str The text label for which the id value is desired
    ///
    /// @throw isc::BadValue if type_str is not a valid text label.
    static UserIdType lookupType(const std::string& type_str);

private:
    /// @brief The type of id value
    UserIdType id_type_;

    /// @brief The id value
    std::vector<uint8_t> id_;

};

/// @brief Outputs the UserId contents in a string to the given stream.
///
/// The output string has the form "<type>=<id>" where:
///
/// &lt;type&gt; is the text label returned by UserId::lookupTypeStr()
/// &lt;id&gt; is the output of UserId::toText() without a delimiter.
///
/// Examples:
///       HW_ADDR=0c0e0a01ff06
///       DUID=0001000119efe63b000c01020306
///
/// @param os output stream to which to write
/// @param user_id source object to output
std::ostream&
operator<<(std::ostream& os, const UserId& user_id);

/// @brief Defines a smart pointer to UserId
typedef boost::shared_ptr<UserId> UserIdPtr;

/// @brief Defines a map of string values keyed by string labels.
typedef std::map<std::string, std::string> PropertyMap;

/// @brief Represents a unique DHCP user
/// This class is used to represent a specific DHCP user who is identified by a
/// unique id and who possesses a set of properties.
class User {
public:
    /// @brief Constructor
    ///
    /// Constructs a new User from a given id with an empty set of properties.
    ///
    /// @param user_id Id to assign to the user
    ///
    /// @throw isc::BadValue if user id is blank.
    User(const UserId & user_id);

    /// @brief Constructor
    ///
    /// Constructs a new User from a given id type and vector containing the
    /// id data with an empty set of properties.
    ///
    /// @param id_type Type of id contained in the id vector
    /// @param id Vector of data representing the user's id
    ///
    /// @throw isc::BadValue if user id vector is empty.
    User(UserId::UserIdType id_type, const std::vector<uint8_t>& id);

    /// @brief Constructor
    ///
    /// Constructs a new User from a given id type and string containing the
    /// id data with an empty set of properties.
    ///
    /// @param id_type Type of id contained in the id vector
    /// @param id_str string of hex digits representing the user's id
    ///
    /// @throw isc::BadValue if user id string is empty or invalid
    User(UserId::UserIdType id_type, const std::string& id_str);

    /// @brief Destructor
    ~User();

    /// @brief Returns a reference to the map of properties.
    ///
    /// Note that this reference can go out of scope and should not be
    /// relied upon other than for momentary use.
    const PropertyMap& getProperties() const;

    /// @brief Sets the user's properties from a given property map
    ///
    /// Replaces the contents of the user's property map with the given
    /// property map.
    ///
    /// @param properties property map to assign to the user
    void setProperties(const PropertyMap& properties);

    /// @brief Sets a given property to the given value
    ///
    /// Adds or updates the given property to the given value.
    ///
    /// @param name string by which the property is identified (keyed)
    /// @param value string data to associate with the property
    ///
    /// @throw isc::BadValue if name is blank.
    void setProperty(const std::string& name, const std::string& value);

    /// @brief Fetches the string value for a given property name.
    ///
    /// @param name property name to fetch
    ///
    /// @return Returns the string value for the given name or an empty string
    /// if the property is not found in the property map.
    std::string getProperty(const std::string& name) const;

    /// @brief Removes the given property from the property map.
    ///
    /// Removes the given property from the map if found. If not, no harm no
    /// foul.
    ///
    /// @param name property name to remove
    void delProperty(const std::string& name);

    /// @brief Returns the user's id.
    ///
    /// Note that this reference can go out of scope and should not be
    /// relied upon other than for momentary use.
    const UserId& getUserId() const;

private:
    /// @brief The user's id.
    UserId user_id_;

    /// @brief The user's property map.
    PropertyMap properties_;
};

/// @brief Defines a smart pointer to a User.
typedef boost::shared_ptr<User> UserPtr;

} // namespace user_chk

#endif
