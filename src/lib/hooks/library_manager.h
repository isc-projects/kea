// Copyright (C) 2013, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>

#include <string>

namespace isc {
namespace hooks {

/// @brief No Callout Manager
///
/// Thrown if a library manager is instantiated by an external agency without
/// specifying a CalloutManager object.
class NoCalloutManager : public Exception {
public:
    NoCalloutManager(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

class CalloutManager;
class LibraryHandle;
class LibraryManager;

/// @brief Library manager
///
/// This class handles the loading and unloading of a specific library.  It also
/// provides a static method for checking that a library is valid (this is used
/// in configuration parsing).
///
/// On loading, it opens the library using dlopen and checks the version (set
/// with the "version" method.  If all is OK, it iterates through the list of
/// known hooks and locates their symbols, registering each callout as it does
/// so.  Finally it locates the "load" function (if present) and calls it.
///
/// On unload, it calls the "unload" method if present, clears the callouts on
/// all hooks, and closes the library.
///
/// @note Caution needs to be exercised when using the unload method. During
///       normal use, data will pass between the server and the library.  In
///       this process, the library may allocate memory and pass it back to the
///       server.  This could happen by the server setting arguments or context
///       in the CalloutHandle object, or by the library modifying the content
///       of pointed-to data. If the library is unloaded, this memory may lie
///       in the virtual address space deleted in that process. (The word "may"
///       is used, as this could be operating-system specific.) Should this
///       happen, any reference to the memory will cause a segmentation fault.
///       This can occur in a quite obscure place, for example in the middle of
///       a destructor of an STL class when it is deleting memory allocated
///       when the data structure was extended by a function in the library.
///
/// @note The only safe way to run the "unload" function is to ensure that all
///       possible references to it are removed first.  This means that all
///       CalloutHandles must be destroyed, as must any data items that were
///       passed to the callouts.  In practice, it could mean that a server
///       suspends processing of new requests until all existing ones have
///       been serviced and all packet/context structures destroyed before
///       reloading the libraries.
///
/// When validating a library, only the fact that the library can be opened and
/// version() exists and returns the correct number is checked.  The library
/// is closed after the validation.

class LibraryManager {
public:
    /// @brief Constructor
    ///
    /// This constructor is used by external agencies (i.e. the
    /// LibraryManagerCollection) when instantiating a LibraryManager.  It
    /// stores the library name - the actual actual loading is done in
    /// loadLibrary().
    ///
    /// @param name Name of the library to load.  This should be an absolute
    ///        path name.
    /// @param index Index of this library
    /// @param manager CalloutManager object
    ///
    /// @throw NoCalloutManager Thrown if the manager argument is NULL.
    LibraryManager(const std::string& name, int index,
                   const boost::shared_ptr<CalloutManager>& manager);

    /// @brief Destructor
    ///
    /// If the library is open, closes it.  This is principally a safety
    /// feature to ensure closure in the case of an exception destroying this
    /// object.  However, see the caveat in the class header about when it is
    /// safe to unload libraries.
    ~LibraryManager();

    /// @brief Validate library
    ///
    /// A static method that is used to validate a library.  Validation checks
    /// that the library can be opened, that "version" exists, and that it
    /// returns the right number.
    ///
    /// @param name Name of the library to validate
    ///
    /// @return true if the library validated, false if not.  If the library
    /// fails to validate, the reason for the failure is logged.
    static bool validateLibrary(const std::string& name);

    /// @brief Loads a library
    ///
    /// Open the library and check the version.  If all is OK, load all standard
    /// symbols then call "load" if present.
    ///
    /// It also calls the @c isc::log::MessageInitializer::loadDictionary, prior
    /// to invoking the @c version function of the library, to update the global
    /// logging dictionary with the log messages registered by the loaded library.
    ///
    /// @return true if the library loaded successfully, false otherwise. In the
    ///         latter case, the library will be unloaded if possible.
    bool loadLibrary();

    /// @brief Unloads a library
    ///
    /// Calls the libraries "unload" function if present, the closes the
    /// library.
    ///
    /// However, see the caveat in the class header about when it is safe to
    /// unload libraries.
    ///
    /// @return true if the library unloaded successfully, false if an error
    ///         occurred in the process (most likely the unload() function
    ///         (if present) returned an error).  Even if an error did occur,
    ///         the library is closed if possible.
    bool unloadLibrary();

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
    /// @return true if the library closed successfully, false otherwise. "true"
    ///         is also returned if the library were already closed when this
    ///         method was called.
    bool closeLibrary();

    /// @brief Check library version
    ///
    /// With the library open, accesses the "version()" function and, if
    /// present, checks the returned value against the hooks version symbol
    /// for the currently running Kea.  The "version()" function is
    /// mandatory and must be present (and return the correct value) for the
    /// library to load.
    ///
    /// If there is no version() function, or if there is a mismatch in
    /// version number, a message logged.
    ///
    /// @return bool true if the check succeeded
    bool checkVersion() const;

    /// @brief Register standard callouts
    ///
    /// Loops through the list of hook names and searches the library for
    /// functions with those names.  Any that are found are registered as
    /// callouts for that hook.
    void registerStandardCallouts();

    /// @brief Run the load function if present
    ///
    /// Searches for the "load" framework function and, if present, runs it.
    ///
    /// @return bool true if not found or found and run successfully,
    ///         false on an error.  In this case, an error message will
    ///         have been output.
    bool runLoad();

    /// @brief Run the unload function if present
    ///
    /// Searches for the "unload" framework function and, if present, runs it.
    ///
    /// @return bool true if not found or found and run successfully,
    ///         false on an error.  In this case, an error message will
    ///         have been output.
    bool runUnload();

private:
    /// @brief Validating constructor
    ///
    /// Constructor used when the LibraryManager is instantiated to validate
    /// a library (i.e. by the "validateLibrary" static method).
    ///
    /// @param name Name of the library to load.  This should be an absolute
    ///        path name.
    explicit LibraryManager(const std::string& name);

    // Member variables

    void*       dl_handle_;     ///< Handle returned by dlopen
    int         index_;         ///< Index associated with this library
    boost::shared_ptr<CalloutManager> manager_;
                                ///< Callout manager for registration
    std::string library_name_;  ///< Name of the library

};

} // namespace hooks
} // namespace isc

#endif  // LIBRARY_MANAGER_H
