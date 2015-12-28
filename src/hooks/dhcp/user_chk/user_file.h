// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef _USER_FILE_H
#define _USER_FILE_H

/// @file user_file.h Defines the class, UserFile, which implements the UserDataSource interface for text files.

#include <user_data_source.h>
#include <user.h>

#include <boost/shared_ptr.hpp>
#include <fstream>
#include <string>

namespace user_chk {

/// @brief Thrown a UserFile encounters an error.
/// Note that it derives from UserDataSourceError to comply with the interface.
class UserFileError : public UserDataSourceError {
public:
    UserFileError(const char* file, size_t line, const char* what) :
        UserDataSourceError(file, line, what)
    {}
};

/// @brief Provides a UserDataSource implementation for JSON text files.
/// This class allows a text file of JSON entries to be treated as a source of
/// User entries.  The format of the file is one user entry per line, where
/// each line contains a JSON string as follows:
///
/// { "type" : "<user type>", "id" : "<user_id>" (options)  }
///
/// where:
///
/// &lt;user_type&gt;  text label of the id type: "HW_ADDR" or "DUID"
/// &lt;user_id&gt;  the user's id as a string of hex digits with or without
/// colons (':') as a delimiter
/// (options) zero or more string elements as name-value pairs, separated by
/// commas: "opt1" : "val1",  "other_opt", "77" ...
///
/// Each entry must have a valid entry for "type" and a valid entry or "id".
///
/// If an entry contains duplicate option names, that option will be assigend
/// the last value found. This is typical JSON behavior.
/// Currently, only string option values (i.e. enclosed in quotes) are
/// supported.
///
/// Example file entries might look like this:
/// @code
///
/// { "type" : "HW_ADDR", "id" : "01AC00F03344", "opt1" : "true" }
/// { "type" : "DUID", "id" : "225060de0a0b", "opt1" : "false" }
///
/// @endcode
class UserFile : public UserDataSource {
public:
    /// @brief Maximum length of a single user entry.
    /// This value is somewhat arbitrary. 4K seems reasonably large.  If it
    /// goes beyond this, then a flat file is not likely the way to go.
    static const size_t USER_ENTRY_MAX_LEN = 4096;

    /// @brief Constructor
    ///
    /// Create a UserFile for the given file name without opening the file.
    /// @param fname pathname to the input file.
    ///
    /// @throw UserFileError if given file name is empty.
    UserFile(const std::string& fname);

    /// @brief Destructor.
    ////
    /// The destructor does call the close method.
    virtual ~UserFile();

    /// @brief Opens the input file for reading.
    ///
    /// Upon successful completion, the file is opened and positioned to start
    /// reading from the beginning of the file.
    ///
    /// @throw UserFileError if the file cannot be opened.
    virtual void open();

    /// @brief Fetches the next user from the file.
    ///
    /// Reads the next user entry from the file and attempts to create a
    /// new User from the text therein.  If there is no more data to be read
    /// it returns an empty UserPtr.
    ///
    /// @return A UserPtr pointing to the new User or an empty pointer on EOF.
    ///
    /// @throw UserFileError if an error occurs while reading.
    virtual UserPtr readNextUser();

    /// @brief Closes the underlying file.
    ///
    /// Method is exception safe.
    virtual void close();

    /// @brief Returns true if the file is open.
    ///
    /// @return True if the underlying file is open, false otherwise.
    virtual bool isOpen() const;

    /// @brief Creates a new User instance from JSON text.
    ///
    /// @param user_string string the JSON text for a user entry.
    ///
    /// @return A pointer to the newly created User instance.
    ///
    /// @throw UserFileError if the entry is invalid.
    UserPtr makeUser(const std::string& user_string);

private:
    /// @brief Pathname of the input text file.
    std::string fname_;

    /// @brief Input file stream.
    std::ifstream file_;

};

/// @brief Defines a smart pointer to a UserFile.
typedef boost::shared_ptr<UserFile> UserFilePtr;

} // namespace user_chk

#endif
