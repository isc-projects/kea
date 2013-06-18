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

#include <hooks/callout_handle.h>
#include <hooks/callout_manager.h>
#include <hooks/library_manager.h>
#include <hooks/server_hooks.h>

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

using namespace isc;
using namespace isc::hooks;
using namespace std;

/// @brief Library manager test class

class LibraryManagerTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Sets up a collection of three LibraryHandle objects to use in the test.
    LibraryManagerTest() {

        // Set up the server hooks.  There is sone singleton for all tests,
        // so reset it and explicitly set up the hooks for the test.
        ServerHooks& hooks = ServerHooks::getServerHooks();
        hooks.reset();
        alpha_index_ = hooks.registerHook("alpha");
        beta_index_ = hooks.registerHook("beta");
        gamma_index_ = hooks.registerHook("gamma");

        // Set up the callout manager with these hooks.  Assume a maximum of
        // four libraries.
        callout_manager_.reset(new CalloutManager(1));

        // Set up the callout handle.
        callout_handle_.reset(new CalloutHandle(callout_manager_));
    }

    /// @brief Return the callout handle
    CalloutHandle& getCalloutHandle() {
        return (*callout_handle_);
    }

    /// @brief Return the callout manager
    boost::shared_ptr<CalloutManager> getCalloutManager() {
        return (callout_manager_);
    }

    /// Hook indexes.  These are somewhat ubiquitous, so are made public for
    /// ease of reference instead of being accessible by a function.
    int alpha_index_;
    int beta_index_;
    int gamma_index_;

private:
    /// Callout handle used in calls
    boost::shared_ptr<CalloutHandle> callout_handle_;

    /// Callout manager used for the test
    boost::shared_ptr<CalloutManager> callout_manager_;
};


/// @brief Library manager class
///
/// This is an instance of the LibraryManager class but with the protected
/// methods made public for test purposes.

class PublicLibraryManager : public isc::hooks::LibraryManager {
public:
    /// @brief Constructor
    ///
    /// Stores the library name.  The actual loading is done in loadLibrary().
    ///
    /// @param name Name of the library to load.  This should be an absolute
    ///        path name.
    /// @param index Index of this library
    /// @param manager CalloutManager object
    PublicLibraryManager(const std::string& name, int index,
                         const boost::shared_ptr<CalloutManager>& manager)
        : LibraryManager(name, index, manager)
    {}

    /// Public methods that call protected methods on the superclass
    //@{
    /// @brief Open library
    ///
    /// Opens the library associated with this LibraryManager.  A message is
    /// logged on an error.
    ///
    /// @return true if the library opened successfully, false otherwise.
    bool openLibrary() {
        return (LibraryManager::openLibrary());
    }

    /// @brief Close library
    ///
    /// Closes the library associated with this LibraryManager.  A message is
    /// logged on an error.
    ///
    /// @return true if the library closed successfully, false otherwise.
    bool closeLibrary() {
        return (LibraryManager::closeLibrary());
    }


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
    bool checkVersion() const {
        return (LibraryManager::checkVersion());
    }

    //@}
};

// Names of the libraries used in these tests.  These libraries are built using
// libtool, so we need to look in the hidden ".libs" directory to locate the
// .so file.  Note that we access the .so file - libtool creates this as a
// like to the real shared library.
static const char* NOT_PRESENT_LIBRARY = "/home/stephen/bind10/src/lib/hooks/tests/.libs/libnothere.so";
static const char* NO_VERSION_LIBRARY = "/home/stephen/bind10/src/lib/hooks/tests/.libs/libnv.so";
static const char* INCORRECT_VERSION_LIBRARY = "/home/stephen/bind10/src/lib/hooks/tests/.libs/libiv.so";
static const char* BASIC_CALLOUT_LIBRARY = "/home/stephen/bind10/src/lib/hooks/tests/.libs/libbco.so";


namespace {

// Tests that OpenLibrary reports an error for an unknown library.

TEST_F(LibraryManagerTest, NonExistentLibrary) {
    // Check that opening a non-existent library fails.
    PublicLibraryManager lib_manager(std::string(NOT_PRESENT_LIBRARY),
                                     0, getCalloutManager());
    EXPECT_FALSE(lib_manager.openLibrary());
}

// Tests that OpenLibrary handles the case of no version present.

TEST_F(LibraryManagerTest, NoVersionFunction) {
    PublicLibraryManager lib_manager(std::string(NO_VERSION_LIBRARY),
                                     0, getCalloutManager());
    // Open should succeed.
    EXPECT_TRUE(lib_manager.openLibrary());

    // Version check should fail.
    EXPECT_FALSE(lib_manager.checkVersion());

    // Tidy up.
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// Tests that OpenLibrary reports an error for an unknown library.

TEST_F(LibraryManagerTest, IncorrectVersionReturned) {
    PublicLibraryManager lib_manager(std::string(INCORRECT_VERSION_LIBRARY),
                                     0, getCalloutManager());
    // Open should succeed.
    EXPECT_TRUE(lib_manager.openLibrary());

    // Version check should fail.
    EXPECT_FALSE(lib_manager.checkVersion());

    // Tidy up.
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// Tests that the openLibrary() and closeLibrary() methods work.

TEST_F(LibraryManagerTest, OpenClose) {

    // Create the library manager.
    PublicLibraryManager lib_manager(std::string(BASIC_CALLOUT_LIBRARY),
                                     0, getCalloutManager());

    // Open and close the library
    EXPECT_TRUE(lib_manager.openLibrary());
    EXPECT_TRUE(lib_manager.closeLibrary());

    // Check that closing an already closed library causes no problems.
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// Checks the basic functionality - loads a library where the callouts are
// named after the hooks, calls the callouts and checks the results.

TEST_F(LibraryManagerTest, BasicCalloutTest) {

    // Load the only library, specifying the index of 0 as it's the only
    // library.  This should load all callouts.
    LibraryManager lib_manager(std::string(BASIC_CALLOUT_LIBRARY),
                               0, getCalloutManager());
    EXPECT_NO_THROW(lib_manager.loadLibrary());

    // Set up abbreviations...
    boost::shared_ptr<CalloutManager> co_manager = getCalloutManager();
    CalloutHandle& callout_handle = getCalloutHandle();

    // Now execute the callouts in the order expected.  context_create
    // always comes first.  This sets the context value to 10.
    co_manager->callCallouts(ServerHooks::CONTEXT_CREATE, callout_handle);

    // First callout adds 5 to the context value.
    callout_handle.setArgument("data_1", static_cast<int>(5));
    co_manager->callCallouts(alpha_index_, callout_handle);

    // Second callout multiples the context value by 7
    callout_handle.setArgument("data_2", static_cast<int>(7));
    co_manager->callCallouts(beta_index_, callout_handle);

    // Third callour retrieves the context value.
    co_manager->callCallouts(gamma_index_, callout_handle);
    int result;
    callout_handle.getArgument("result", result);
    EXPECT_EQ(105, result);
}

} // Anonymous namespace
