// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef _USER_REGISTRY_H
#define _USER_REGISTRY_H

/// @file user_registry.h Defines the class, UserRegistry.

#include <dhcp/hwaddr.h>
#include <dhcp/duid.h>
#include <exceptions/exceptions.h>
#include <user.h>
#include <user_data_source.h>

#include <string>

namespace user_chk {

/// @brief Thrown UserRegistry encounters an error
class UserRegistryError : public isc::Exception {
public:
    UserRegistryError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};

/// @brief Defines a map of unique Users keyed by UserId.
typedef std::map<UserId,UserPtr> UserMap;

/// @brief Embodies an update-able, searchable list of unique users
/// This class provides the means to create and maintain a searchable list
/// of unique users. List entries are pointers to instances of User, keyed
/// by their UserIds.
/// Users may be added and removed from the list individually or the list
/// may be updated by loading it from a data source, such as a file.
class UserRegistry {
public:
    /// @brief Constructor
    ///
    /// Creates a new registry with an empty list of users and no data source.
    UserRegistry();

    /// @brief Destructor
    ~UserRegistry();

    /// @brief Adds a given user to the registry.
    ///
    /// @param user A pointer to the user to add
    ///
    /// @throw UserRegistryError if the user is null or if the user already
    /// exists in the registry.
    void addUser(UserPtr& user);

    /// @brief Finds a user in the registry by user id
    ///
    /// @param id The user id for which to search
    ///
    /// @return A pointer to the user if found or an null pointer if not.
    const UserPtr& findUser(const UserId& id) const;

    /// @brief Removes a user from the registry by user id
    ///
    /// Removes the user entry if found, if not simply return.
    ///
    /// @param id The user id of the user to remove
    void removeUser(const UserId&  id);

    /// @brief Finds a user in the registry by hardware address
    ///
    /// @param hwaddr The hardware address for which to search
    ///
    /// @return A pointer to the user if found or an null pointer if not.
    const UserPtr& findUser(const isc::dhcp::HWAddr& hwaddr) const;

    /// @brief Finds a user in the registry by DUID
    ///
    /// @param duid The DUID for which to search
    ///
    /// @return A pointer to the user if found or an null pointer if not.
    const UserPtr& findUser(const isc::dhcp::DUID& duid) const;

    /// @brief Updates the registry from its data source.
    ///
    /// This method will replace the contents of the registry with new content
    /// read from its data source.  It will attempt to open the source and
    /// then add users from the source to the registry until the source is
    /// exhausted.  If an error occurs accessing the source the registry
    /// contents will be restored to that of before the call to refresh.
    ///
    /// @throw UserRegistryError if the data source has not been set (is null)
    /// or if an error occurs accessing the data source.
    void refresh();

    /// @brief Removes all entries from the registry.
    void clearall();

    /// @brief Returns a reference to the data source.
    const UserDataSourcePtr& getSource();

    /// @brief Sets the data source to the given value.
    ///
    /// @param source reference to the data source to use.
    ///
    /// @throw UserRegistryError if new source value is null.
    void setSource(UserDataSourcePtr& source);

private:
    /// @brief The registry of users.
    UserMap users_;

    /// @brief The current data source of users.
    UserDataSourcePtr source_;
};

/// @brief Define a smart pointer to a UserRegistry.
typedef boost::shared_ptr<UserRegistry> UserRegistryPtr;

} // namespace user_chk

#endif
