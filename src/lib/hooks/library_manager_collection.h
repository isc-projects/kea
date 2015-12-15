// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LIBRARY_MANAGER_COLLECTION_H
#define LIBRARY_MANAGER_COLLECTION_H

#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace isc {
namespace hooks {

/// @brief LoadLibraries not called
///
/// Thrown if an attempt is made get a CalloutManager before the libraries
/// have been loaded.
class LoadLibrariesNotCalled : public Exception {
public:
    LoadLibrariesNotCalled(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};


// Forward declarations
class CalloutManager;
class LibraryManager;

/// @brief Library manager collection
///
/// The LibraryManagerCollection class, as the name implies, is responsible for
/// managing the collection of LibraryManager objects that describe the loaded
/// libraries.  As such, it converts a single operation (e.g load libraries)
/// into multiple operations, one per library.  However, the class does more
/// than that - it provides a single object with which to manage lifetimes.
///
/// As described in the LibraryManager documentation, a CalloutHandle may end
/// up with pointers to memory within the address space of a loaded library.
/// If the library is unloaded before this address space is deleted, the
/// deletion of the CalloutHandle may attempt to free memory into the newly-
/// unmapped address space and cause a segmentation fault.
///
/// To prevent this, each CalloutHandle maintains a shared pointer to the
/// LibraryManagerCollection current when it was created.  In addition, the
/// containing HooksManager object also maintains a shared pointer to it.  A
/// a LibraryManagerCollection is never explicitly deleted: when a new set
/// of libraries is loaded, the HooksManager clears its pointer to the
/// collection.  The LibraryManagerCollection is only destroyed when all
/// CallHandle objects referencing it are destroyed.
///
/// Note that this does not completely solve the problem - a hook function may
/// have modified a packet being processed by the server and that packet may
/// hold a pointer to memory in the library's virtual address space. To avoid
/// a segmentation fault, that packet needs to free the memory before the
/// LibraryManagerCollection is destroyed and this places demands on the server
/// code.  However, the link with the CalloutHandle does at least mean that
/// authors of server code do not need to be so careful about when they destroy
/// CalloutHandles.
///
/// The collection object also provides a utility function to validate a set
/// of libraries.  The function checks that each library exists, can be opened,
/// that the "version" function exists and return the right number.

class LibraryManagerCollection {
public:
    /// @brief Constructor
    ///
    /// @param libraries List of libraries that this collection will manage.
    ///        The order of the libraries is important.
    LibraryManagerCollection(const std::vector<std::string>& libraries)
        : library_names_(libraries)
    {}

    /// @brief Destructor
    ///
    /// Unloads all loaded libraries.
    ~LibraryManagerCollection() {
        static_cast<void>(unloadLibraries());
    }

    /// @brief Load libraries
    ///
    /// Loads the libraries.  This creates the LibraryManager associated with
    /// each library and calls its loadLibrary() method.  If a library fails
    /// to load, the loading is abandoned and all libraries loaded so far
    /// are unloaded.
    ///
    /// @return true if all libraries loaded, false if one or more failed t
    ////        load.
    bool loadLibraries();

    /// @brief Get callout manager
    ///
    /// Returns a callout manager that can be used with this set of loaded
    /// libraries (even if the number of loaded libraries is zero).  This
    /// method may only be caslled after loadLibraries() has been called.
    ///
    /// @return Pointer to a callout manager for this set of libraries.
    ///
    /// @throw LoadLibrariesNotCalled Thrown if this method is called between
    ///        construction and the time loadLibraries() is called.
    boost::shared_ptr<CalloutManager> getCalloutManager() const;

    /// @brief Get library names
    ///
    /// Returns the list of library names.  If called before loadLibraries(),
    /// the list is the list of names to be loaded; if called afterwards, it
    /// is the list of libraries that have been loaded.
    std::vector<std::string> getLibraryNames() const {
        return (library_names_);
    }

    /// @brief Get number of loaded libraries
    ///
    /// Mainly for testing, this returns the number of libraries that are
    /// loaded.
    ///
    /// @return Number of libraries that are loaded.
    int getLoadedLibraryCount() const;

    /// @brief Validate libraries
    ///
    /// Utility function to validate libraries.  It checks that the libraries
    /// exist, can be opened, that a "version" function is present in them, and
    /// that it returns the right number.  All errors are logged.
    ///
    /// @param libraries List of libraries to validate
    ///
    /// @return Vector of libraries that faled to validate, or an empty vector
    ///         if all validated.
    static std::vector<std::string>
    validateLibraries(const std::vector<std::string>& libraries);

protected:
    /// @brief Unload libraries
    ///
    /// Unloads and closes all loaded libraries.  They are unloaded in the
    /// reverse order to the order in which they were loaded.
    void unloadLibraries();

private:

    /// Vector of library names
    std::vector<std::string>                        library_names_;

    /// Vector of library managers
    std::vector<boost::shared_ptr<LibraryManager> > lib_managers_;

    /// Callout manager to be associated with the libraries
    boost::shared_ptr<CalloutManager>               callout_manager_;
};

} // namespace hooks
} // namespace isc


#endif // LIBRARY_MANAGER_COLLECTION_H
