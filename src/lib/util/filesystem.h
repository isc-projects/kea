// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KEA_UTIL_FILESYSTEM_H
#define KEA_UTIL_FILESYSTEM_H

#include <string>

namespace isc {
namespace util {
namespace file {

/// \brief Get the content of a regular file.
///
/// \param file_name The file name.
///
/// \return The content of the file.
/// \throw BadValue when the file can't be opened or is not a regular one.
std::string
getContent(const std::string& file_name);

/// \brief Check if there is a file or directory at the given path.
///
/// \param path The path being checked.
///
/// \return True if the path points to a file or a directory, false otherwise.
bool
exists(const std::string& path);

/// \brief Check if there is a directory at the given path.
///
/// \param path The path being checked.
///
/// \return True if the path points to a directory, false otherwise including
/// if the pointed location does not exist.
bool
isDir(const std::string& path);

/// \brief Check if there is a file at the given path.
///
/// \param path The path being checked.
///
/// \return True if the path points to a file, false otherwise including
/// if the pointed location does not exist.
bool
isFile(const std::string& path);

/// \brief Paths on a filesystem
struct Path {
    /// \brief Constructor
    ///
    /// Splits the full name into components.
    Path(std::string const& path);

    /// \brief Get the path in textual format.
    ///
    /// Counterpart for std::filesystem::path::string.
    ///
    /// \return stored filename.
    std::string str() const;

    /// \brief Get the parent path.
    ///
    /// Counterpart for std::filesystem::path::parent_path.
    ///
    /// \return parent path of current path.
    std::string parentPath() const;

    /// \brief Get the base name of the file without the extension.
    ///
    /// Counterpart for std::filesystem::path::stem.
    ///
    /// \return the base name of current path without the extension.
    std::string stem() const;

    /// \brief Get the extension of the file.
    ///
    /// Counterpart for std::filesystem::path::extension.
    ///
    /// \return extension of current path.
    std::string extension() const;

    /// \brief Get the name of the file, extension included.
    ///
    /// Counterpart for std::filesystem::path::filename.
    ///
    /// \return name + extension of current path.
    std::string filename() const;

    /// \brief Identifies the extension in {replacement}, trims it, and
    /// replaces this instance's extension with it.
    ///
    /// Counterpart for std::filesystem::path::replace_extension.
    ///
    /// The change is done in the members and {this} is returned to allow call
    /// chaining.
    ///
    /// \param replacement The extension to replace with.
    ///
    /// \return The current instance after the replacement was done.
    Path& replaceExtension(std::string const& replacement = std::string());

    /// \brief Trims {replacement} and replaces this instance's parent path with
    /// it.
    ///
    /// The change is done in the members and {this} is returned to allow call
    /// chaining.
    ///
    /// \param replacement The parent path to replace with.
    ///
    /// \return The current instance after the replacement was done.
    Path& replaceParentPath(std::string const& replacement = std::string());

private:
    /// \brief Parent path.
    std::string parent_path_;

    /// \brief Stem.
    std::string stem_;

    /// \brief File name extension.
    std::string extension_;
};

}  // namespace file
}  // namespace util
}  // namespace isc

#endif  // KEA_UTIL_FILESYSTEM_H
