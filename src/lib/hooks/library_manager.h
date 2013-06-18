// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef LIBRARY_MANAGER_H
#define LIBRARY_MANAGER_H

#include <boost/shared_ptr.hpp>

#include <string>

namespace isc {
namespace hooks {

class CalloutManager;
class LibraryManager;

/// @brief Library manager
///
/// This class handles the loading and unloading of a specific library.
///
/// On loading, it opens the library using dlopen and checks the version (set
/// with the "version" method.  If all is OK, it iterates through the list of
/// known hooks and locates their symbols, registering each callout as it
/// does so.  Finally it locates the "load" and "unload" functions (if present),
/// calling the "load" callouts if present.
///
/// On unload, it calls the "unload" method if one was located, clears the
/// callouts from all hooks and closes the library.

class LibraryManager {
private:
    /// Useful typedefs for the framework functions
    typedef int (*version_function_ptr)();          ///< version() signature
    typedef int (*load_function_ptr)();             ///< load() signature
    typedef int (*unload_function_ptr)(LibraryHandle&); ///< unload() signature

public:
    /// @brief Constructor
    ///
    /// Stores the library name.  The actual loading is done in loadLibrary().
    ///
    /// @param name Name of the library to load.  This should be an absolute
    ///        path name.
    /// @param index Index of this library
    /// @param manager CalloutManager object
    LibraryManager(const std::string& name, int index,
                   const boost::shared_ptr<CalloutManager>& manager)
        : dl_handle_(NULL), index_(index), manager_(manager),
          library_name_(name), load_func_(NULL), unload_func_(NULL)
    {}

    /// @brief Destructor
    ///
    /// If the library is open, closes it.  This is principally a safety
    /// feature to ensure closure in the case of an exception destroying
    /// this object.
    ~LibraryManager() {
        static_cast<void>(closeLibrary());
    }

    /// @brief Loads a library
    ///
    /// Open the library and check the version.  If all is OK, load all
    /// standard symbols then call "load" if present.
    void loadLibrary() {}

    /// @brief Unloads a library
    ///
    /// Calls the libraries "unload" function if present, the closes the
    /// library.
    void unloadLibrary() {}

    /// @brief Return library name
    ///
    /// @return Name of this library
    std::string getName() const {
        return (library_name_);
    }

protected:
    // The following methods are protected as they are accessed in testing.

    /// @brief Open library
    ///
    /// Opens the library associated with this LibraryManager.  A message is
    /// logged on an error.
    ///
    /// @return true if the library opened successfully, false otherwise.
    bool openLibrary();

    /// @brief Close library
    ///
    /// Closes the library associated with this LibraryManager.  A message is
    /// logged on an error.
    ///
    /// @return true if the library closed successfully, false otherwise.
    ///         "true" is also returned if the library were already closed
    ///         when this method was called.
    bool closeLibrary();


    /// @brief Check library version
    ///
    /// With the library open, accesses the "version()" function and, if
    /// present, checks the returned value against the hooks version symbol
    /// for the currently running BIND 10.
    ///
    /// If there is no version() function, or if there is a mismatch in
    /// version number, a message logged.
    ///
    /// @return bool true if the check succeeded
    bool checkVersion() const;

private:
    void*       dl_handle_;     ///< Handle returned by dlopen
    int         index_;         ///< Index associated with this library
    boost::shared_ptr<CalloutManager> manager_;
                                ///< Callout manager for registration
    std::string library_name_;  ///< Name of the library

    load_function_ptr       load_func_;     ///< Pointer to "load" function
    unload_function_ptr     unload_func_;   ///< Pointer to "unload" function
};

} // namespace hooks
} // namespace isc

#endif  // LIBRARY_MANAGER_H
