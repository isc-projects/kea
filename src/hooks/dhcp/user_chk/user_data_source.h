// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef _USER_DATA_SOURCE_H
#define _USER_DATA_SOURCE_H

/// @file user_data_source.h Defines the base class, UserDataSource.
#include <exceptions/exceptions.h>
#include <user.h>

namespace user_chk {

/// @brief Thrown if UserDataSource encounters an error
class UserDataSourceError : public isc::Exception {
public:
    UserDataSourceError(const char* file, size_t line,
                               const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Defines an interface for reading user data into a registry.
/// This is an abstract class which defines the interface for reading Users
/// from an IO source such as a file.
class UserDataSource {
public:
    /// @brief Constructor.
    UserDataSource() {};

    /// @brief Virtual Destructor.
    virtual ~UserDataSource() {};

    /// @brief Opens the data source.
    ///
    /// Prepares the data source for reading.  Upon successful completion the
    /// data source is ready to read from the beginning of its content.
    ///
    /// @throw UserDataSourceError if the source fails to open.
    virtual void open() = 0;

    /// @brief Fetches the next user from the data source.
    ///
    /// Reads the next User from the data source and returns it.  If no more
    /// data is available it should return an empty (null) user.
    ///
    /// @throw UserDataSourceError if an error occurs.
    virtual UserPtr readNextUser() = 0;

    /// @brief Closes that data source.
    ///
    /// Closes the data source.
    ///
    /// This method must not throw exceptions.
    virtual void close() = 0;

    /// @brief Returns true if the data source is open.
    ///
    /// This method should return true once the data source has been
    /// successfully opened and until it has been closed.
    ///
    /// It is assumed to be exception safe.
    virtual bool isOpen() const = 0;
};

/// @brief Defines a smart pointer to a UserDataSource.
typedef boost::shared_ptr<UserDataSource> UserDataSourcePtr;

} // namespace user_chk

#endif
