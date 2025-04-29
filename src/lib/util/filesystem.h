// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KEA_UTIL_FILESYSTEM_H
#define KEA_UTIL_FILESYSTEM_H

#include <sys/stat.h>
#include <string>

namespace isc {
namespace util {
namespace file {

/// @brief Check if there is a file or directory at the given path.
///
/// @param path The path being checked.
///
/// @return True if the path points to a file or a directory, false otherwise.
bool
exists(const std::string& path);

/// @brief Check if there is a file at the given path.
///
/// @param path The path being checked.
///
/// @return True if the path points to a file, false otherwise including
/// if the pointed location does not exist.
bool
isFile(const std::string& path);

/// @brief RAII device to limit access of created files.
struct Umask {
    /// @brief Constructor
    ///
    /// Set wanted bits in umask.
    Umask(mode_t mask);

    /// @brief Destructor.
    ///
    /// Restore umask.
    ~Umask();

private:
    /// @brief Original umask.
    mode_t orig_umask_;
};

bool
isSocket(const std::string& path);

/// @brief Paths on a filesystem
struct Path {
    /// @brief Constructor
    ///
    /// Splits the full name into components.
    Path(std::string const& path);

    /// @brief Get the path in textual format.
    ///
    /// Counterpart for std::filesystem::path::string.
    ///
    /// @return stored filename.
    std::string str() const;

    /// @brief Get the parent path.
    ///
    /// Counterpart for std::filesystem::path::parent_path.
    ///
    /// @return parent path of current path.
    std::string parentPath() const;

    /// @brief Get the base name of the file without the extension.
    ///
    /// Counterpart for std::filesystem::path::stem.
    ///
    /// @return the base name of current path without the extension.
    std::string stem() const;

    /// @brief Get the extension of the file.
    ///
    /// Counterpart for std::filesystem::path::extension.
    ///
    /// @return extension of current path.
    std::string extension() const;

    /// @brief Get the name of the file, extension included.
    ///
    /// Counterpart for std::filesystem::path::filename.
    ///
    /// @return name + extension of current path.
    std::string filename() const;

    /// @brief Identifies the extension in {replacement}, trims it, and
    /// replaces this instance's extension with it.
    ///
    /// Counterpart for std::filesystem::path::replace_extension.
    ///
    /// The change is done in the members and {this} is returned to allow call
    /// chaining.
    ///
    /// @param replacement The extension to replace with.
    ///
    /// @return The current instance after the replacement was done.
    Path& replaceExtension(std::string const& replacement = std::string());

    /// @brief Trims {replacement} and replaces this instance's parent path with
    /// it.
    ///
    /// The change is done in the members and {this} is returned to allow call
    /// chaining.
    ///
    /// @param replacement The parent path to replace with.
    ///
    /// @return The current instance after the replacement was done.
    Path& replaceParentPath(std::string const& replacement = std::string());

private:
    /// @brief Parent path.
    std::string parent_path_;

    /// @brief Stem.
    std::string stem_;

    /// @brief File name extension.
    std::string extension_;
};

struct TemporaryDirectory {
    TemporaryDirectory();
    ~TemporaryDirectory();
    std::string dirName();
private:
    std::string dir_name_;
};

/// @brief Class that provides basic file related tasks.
class FileManager {
public:
    /// @brief Validates a file path against a supported path.
    ///
    /// If the input path specifies a parent path and file name, the parent path
    /// is validated against the supported path. If they match, the function returns
    /// the validated path. If the input path contains only a file name the function
    /// returns valid path using the supported path and the input path name.
    ///
    /// @param supported_path_str absolute path specifying the  supported path
    /// of the file against which the input path is validated.
    /// @param input_path_str file path to validate.
    /// @param enforce_path enables validation against the supported path.  If false
    /// verifies only that the path contains a file name.
    ///
    /// @return validated path as a string (supported path + input file name)
    ///
    /// @throw BadValue if the input path does not include a file name or if the
    /// it the parent path does not path the supported path.
    static std::string validatePath(const std::string supported_path_str,
                                    const std::string input_path_str,
                                    bool enforce_path = true);
};

}  // namespace file
}  // namespace util
}  // namespace isc

#endif  // KEA_UTIL_FILESYSTEM_H
