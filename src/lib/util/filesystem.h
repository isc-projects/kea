// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KEA_UTIL_FILESYSTEM_H
#define KEA_UTIL_FILESYSTEM_H

#include <sys/stat.h>
#include <string>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace util {
namespace file {

/// @brief Get the content of a regular file.
///
/// @param file_name The file name.
///
/// @return The content of the file.
/// @throw BadValue when the file can't be opened or is not a regular one.
std::string
getContent(const std::string& file_name);

/// @brief Check if there is a file or directory at the given path.
///
/// @param path The path being checked.
///
/// @return True if the path points to a file or a directory, false otherwise.
bool
exists(const std::string& path);

/// @brief Check if there is a directory at the given path.
///
/// @param path The path being checked.
///
/// @return True if the path points to a directory, false otherwise including
/// if the pointed location does not exist.
bool
isDir(const std::string& path);

/// @brief Check if there is a file at the given path.
///
/// @param path The path being checked.
///
/// @return True if the path points to a file, false otherwise including
/// if the pointed location does not exist.
bool
isFile(const std::string& path);

/// @brief Set umask (at least 0027 i.e. no group write and no other access).
void
setUmask();

/// \brief Paths on a filesystem
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

/// @brief Embodies a supported path against which file paths can be validated.
class PathChecker {
public:
    /// @brief Constructor.
    ///
    /// Makes a call to getPath(true) to initialize the supported path.
    ///
    /// @param default_path path to use unless overridden by explicitly or via
    /// environment variable.
    /// @param env_name name of environment variable (if one), that can override
    /// the default path.
    PathChecker(const std::string default_path, const std::string env_name = "");

    /// @brief Destructor.
    virtual ~PathChecker() {};

    /// @brief Fetches the supported path.
    ///
    /// When called with reset=true it will calculate the supported path as
    /// follows:
    ///
    /// 1. Use the value of explicit_path parameter if not blank
    /// 2. Use the value of the environment variable, if one is provided and it
    /// is defined in the environment
    /// 3. Use the value of default path.
    ///
    /// @param reset recalculate when true, defaults to false.
    /// @param explicit_path set the default path to this value. This is
    /// for testing purposes only.
    ///
    /// @return String containing the default path.
    std::string getPath(bool reset = false, const std::string explicit_path = "");

    /// @brief Validates a file path against a supported path.
    ///
    /// If the input path specifies a parent path and file name, the parent path
    /// is validated against the supported path. If they match, the function returns
    /// the validated path. If the input path contains only a file name the function
    /// returns valid path using the supported path and the input path name.
    ///
    /// @param input_path_str file path to validate.
    /// @param enforce_path enables validation against the supported path.  If false
    /// verifies only that the path contains a file name.
    ///
    /// @return validated path as a string (supported path + input file name)
    ///
    /// @throw BadValue if the input path does not include a file name or if the
    /// it the parent path does not path the supported path.
    std::string validatePath(const std::string input_path_str,
                             bool enforce_path = true) const;

    /// @brief Fetches the default path.
    std::string getDefaultPath() const {
        return (default_path_);
    }

    /// @brief Fetches the environment variable name.
    std::string getEnvName() const {
        return (env_name_);
    }

private:
    /// @brief Default supported path.
    std::string default_path_;

    /// @brief Name of environment variable (if one) that can override the default.
    std::string env_name_;

    /// @brief The supported path currently in effect.
    std::string path_;
};

/// @brief Defines a pointer to a PathChecker.
typedef boost::shared_ptr<PathChecker> PathCheckerPtr;

}  // namespace file
}  // namespace util
}  // namespace isc

#endif  // KEA_UTIL_FILESYSTEM_H
