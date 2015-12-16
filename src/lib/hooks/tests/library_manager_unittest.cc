// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <hooks/callout_handle.h>
#include <hooks/callout_manager.h>
#include <hooks/library_manager.h>
#include <hooks/server_hooks.h>

#include <hooks/tests/common_test_class.h>
#include <hooks/tests/marker_file.h>
#include <hooks/tests/test_libraries.h>

#include <log/message_dictionary.h>
#include <log/message_initializer.h>

#include <gtest/gtest.h>

#include <algorithm>
#include <fstream>
#include <string>

#include <unistd.h>


using namespace isc;
using namespace isc::hooks;
using namespace isc::log;
using namespace std;

namespace {

/// @brief Library manager test class

class LibraryManagerTest : public ::testing::Test,
                           public HooksCommonTestClass {
public:
    /// @brief Constructor
    ///
    /// Initializes the CalloutManager object used in the tests.  It sets it
    /// up with the hooks initialized in the HooksCommonTestClass object and
    /// with four libraries.
    LibraryManagerTest() {
        callout_manager_.reset(new CalloutManager(4));

        // Ensure the marker file is not present at the start of a test.
        static_cast<void>(remove(MARKER_FILE));
    }

    /// @brief Destructor
    ///
    /// Ensures a marker file is removed after each test.
    ~LibraryManagerTest() {
        static_cast<void>(remove(MARKER_FILE));
    }

    /// @brief Marker file present
    ///
    /// Convenience function to check whether a marker file is present.  It
    /// does this by opening the file.
    ///
    /// @return true if the marker file is present.
    bool markerFilePresent() const {

        // Try to open it.
        std::fstream marker;
        marker.open(MARKER_FILE, std::fstream::in);

        // Check if it is open and close it if so.
        bool exists = marker.is_open();
        if (exists) {
            marker.close();
        }

        return (exists);
    }

    /// @brief Call callouts test
    ///
    /// A wrapper around the method of the same name in the HooksCommonTestClass
    /// object, this passes this class's CalloutManager to that method.
    ///
    /// @param r0...r3, d1..d3 Values and intermediate values expected.  They
    ///        are ordered so that the variables appear in the argument list in
    ///        the order they are used.  See HooksCommonTestClass::execute for
    ///        a full description. (rN is used to indicate an expected result,
    ///        dN is data to be passed to the calculation.)
    void executeCallCallouts(int r0, int d1, int r1, int d2, int r2, int d3,
                             int r3) {
        HooksCommonTestClass::executeCallCallouts(callout_manager_, r0, d1,
                                                  r1, d2, r2, d3, r3);
    }

    /// Callout manager used for the test.
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
    /// @param index Index of this library.  For all these tests, it will be
    ///        zero, as we are only using one library.
    /// @param manager CalloutManager object
    PublicLibraryManager(const std::string& name, int index,
                         const boost::shared_ptr<CalloutManager>& manager)
        : LibraryManager(name, index, manager)
    {}

    /// Public methods that call protected methods on the superclass.
    using LibraryManager::openLibrary;
    using LibraryManager::closeLibrary;
    using LibraryManager::checkVersion;
    using LibraryManager::registerStandardCallouts;
    using LibraryManager::runLoad;
    using LibraryManager::runUnload;
};


// Check that openLibrary() reports an error when it can't find the specified
// library.

TEST_F(LibraryManagerTest, NoLibrary) {
    PublicLibraryManager lib_manager(std::string(NOT_PRESENT_LIBRARY),
                                     0, callout_manager_);
    EXPECT_FALSE(lib_manager.openLibrary());
}

// Check that the openLibrary() and closeLibrary() methods work.

TEST_F(LibraryManagerTest, OpenClose) {
    PublicLibraryManager lib_manager(std::string(BASIC_CALLOUT_LIBRARY),
                                     0, callout_manager_);

    // Open and close the library
    EXPECT_TRUE(lib_manager.openLibrary());
    EXPECT_TRUE(lib_manager.closeLibrary());

    // Check that a second close on an already closed library does not report
    // an error.
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// Check that the code handles the case of a library with no version function.

TEST_F(LibraryManagerTest, NoVersion) {
    PublicLibraryManager lib_manager(std::string(NO_VERSION_LIBRARY),
                                     0, callout_manager_);
    // Open should succeed.
    EXPECT_TRUE(lib_manager.openLibrary());

    // Version check should fail.
    EXPECT_FALSE(lib_manager.checkVersion());

    // Tidy up.
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// Check that the code handles the case of a library with a version function
// that returns an incorrect version number.

TEST_F(LibraryManagerTest, WrongVersion) {
    PublicLibraryManager lib_manager(std::string(INCORRECT_VERSION_LIBRARY),
                                     0, callout_manager_);
    // Open should succeed.
    EXPECT_TRUE(lib_manager.openLibrary());

    // Version check should fail.
    EXPECT_FALSE(lib_manager.checkVersion());

    // Tidy up.
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// Check that the code handles the case of a library where the version function
// throws an exception.

TEST_F(LibraryManagerTest, VersionException) {
    PublicLibraryManager lib_manager(std::string(FRAMEWORK_EXCEPTION_LIBRARY),
                                     0, callout_manager_);
    // Open should succeed.
    EXPECT_TRUE(lib_manager.openLibrary());

    // Version check should fail.
    EXPECT_FALSE(lib_manager.checkVersion());

    // Tidy up.
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// Tests that checkVersion() function succeeds in the case of a library with a
// version function that returns the correct version number.

TEST_F(LibraryManagerTest, CorrectVersionReturned) {
    PublicLibraryManager lib_manager(std::string(BASIC_CALLOUT_LIBRARY),
                                     0, callout_manager_);
    // Open should succeed.
    EXPECT_TRUE(lib_manager.openLibrary());

    // Version check should succeed.
    EXPECT_TRUE(lib_manager.checkVersion());

    // Tidy up.
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// Checks the registration of standard callouts.

TEST_F(LibraryManagerTest, RegisterStandardCallouts) {

    // Load the only library, specifying the index of 0 as it's the only
    // library.  This should load all callouts.
    PublicLibraryManager lib_manager(std::string(BASIC_CALLOUT_LIBRARY),
                               0, callout_manager_);
    EXPECT_TRUE(lib_manager.openLibrary());

    // Check the version of the library.
    EXPECT_TRUE(lib_manager.checkVersion());

    // Load the standard callouts
    EXPECT_NO_THROW(lib_manager.registerStandardCallouts());

    // Now execute the callouts in the order expected.  The library performs
    // the calculation:
    //
    // r3 = (10 + d1) * d2 - d3
    executeCallCallouts(10, 5, 15, 7, 105, 17, 88);

    // Tidy up
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// Test that the "load" function is called correctly.

TEST_F(LibraryManagerTest, CheckLoadCalled) {

    // Load the only library, specifying the index of 0 as it's the only
    // library.  This should load all callouts.
    PublicLibraryManager lib_manager(std::string(LOAD_CALLOUT_LIBRARY),
                                     0, callout_manager_);
    EXPECT_TRUE(lib_manager.openLibrary());

    // Check the version of the library.
    EXPECT_TRUE(lib_manager.checkVersion());

    // Load the standard callouts
    EXPECT_NO_THROW(lib_manager.registerStandardCallouts());

    // Check that only context_create and hookpt_one have callouts registered.
    EXPECT_TRUE(callout_manager_->calloutsPresent(
                ServerHooks::CONTEXT_CREATE));
    EXPECT_TRUE(callout_manager_->calloutsPresent(hookpt_one_index_));
    EXPECT_FALSE(callout_manager_->calloutsPresent(hookpt_two_index_));
    EXPECT_FALSE(callout_manager_->calloutsPresent(hookpt_three_index_));
    EXPECT_FALSE(callout_manager_->calloutsPresent(
                 ServerHooks::CONTEXT_DESTROY));

    // Call the runLoad() method to run the load() function.
    EXPECT_TRUE(lib_manager.runLoad());
    EXPECT_TRUE(callout_manager_->calloutsPresent(
                ServerHooks::CONTEXT_CREATE));
    EXPECT_TRUE(callout_manager_->calloutsPresent(hookpt_one_index_));
    EXPECT_TRUE(callout_manager_->calloutsPresent(hookpt_two_index_));
    EXPECT_TRUE(callout_manager_->calloutsPresent(hookpt_three_index_));
    EXPECT_FALSE(callout_manager_->calloutsPresent(
                 ServerHooks::CONTEXT_DESTROY));

    // Now execute the callouts in the order expected.  The library performs
    // the calculation:
    //
    // r3 = (5 * d1 + d2) * d3
    executeCallCallouts(5, 5, 25, 7, 32, 10, 320);

    // Tidy up
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// Check handling of a "load" function that throws an exception

TEST_F(LibraryManagerTest, CheckLoadException) {

    // Load the only library, specifying the index of 0 as it's the only
    // library.  This should load all callouts.
    PublicLibraryManager lib_manager(std::string(FRAMEWORK_EXCEPTION_LIBRARY),
                                     0, callout_manager_);
    EXPECT_TRUE(lib_manager.openLibrary());

    // Running the load function should fail.
    EXPECT_FALSE(lib_manager.runLoad());

    // Tidy up
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// Check handling of a "load" function that returns an error.

TEST_F(LibraryManagerTest, CheckLoadError) {

    // Load the only library, specifying the index of 0 as it's the only
    // library.  This should load all callouts.
    PublicLibraryManager lib_manager(std::string(LOAD_ERROR_CALLOUT_LIBRARY),
                                     0, callout_manager_);
    EXPECT_TRUE(lib_manager.openLibrary());

    // Check that we catch a load error
    EXPECT_FALSE(lib_manager.runLoad());

    // Tidy up
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// No unload function

TEST_F(LibraryManagerTest, CheckNoUnload) {

    // Load the only library, specifying the index of 0 as it's the only
    // library.  This should load all callouts.
    PublicLibraryManager lib_manager(std::string(BASIC_CALLOUT_LIBRARY),
                                     0, callout_manager_);
    EXPECT_TRUE(lib_manager.openLibrary());

    // Check that no unload function returns true.
    EXPECT_TRUE(lib_manager.runUnload());

    // Tidy up
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// Unload function returns an error

TEST_F(LibraryManagerTest, CheckUnloadError) {

    // Load the only library, specifying the index of 0 as it's the only
    // library.  This should load all callouts.
    PublicLibraryManager lib_manager(std::string(LOAD_ERROR_CALLOUT_LIBRARY),
                                     0, callout_manager_);
    EXPECT_TRUE(lib_manager.openLibrary());

    // Check that unload function returning an error returns false.
    EXPECT_FALSE(lib_manager.runUnload());

    // Tidy up
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// Unload function throws an exception.

TEST_F(LibraryManagerTest, CheckUnloadException) {

    // Load the only library, specifying the index of 0 as it's the only
    // library.  This should load all callouts.
    PublicLibraryManager lib_manager(std::string(FRAMEWORK_EXCEPTION_LIBRARY),
                                     0, callout_manager_);
    EXPECT_TRUE(lib_manager.openLibrary());

    // Check that we detect that the unload function throws an exception.
    EXPECT_FALSE(lib_manager.runUnload());

    // Tidy up
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// Check that the case of the library's unload() function returning a
// success is handled correctly.

TEST_F(LibraryManagerTest, CheckUnload) {

    // Load the only library, specifying the index of 0 as it's the only
    // library.  This should load all callouts.
    PublicLibraryManager lib_manager(std::string(UNLOAD_CALLOUT_LIBRARY),
                                     0, callout_manager_);
    EXPECT_TRUE(lib_manager.openLibrary());


    // Check that the marker file is not present (at least that the file
    // open fails).
    EXPECT_FALSE(markerFilePresent());

    // Check that unload function runs and returns a success
    EXPECT_TRUE(lib_manager.runUnload());

    // Check that the marker file was created.
    EXPECT_TRUE(markerFilePresent());

    // Tidy up
    EXPECT_TRUE(lib_manager.closeLibrary());
}

// Test the operation of unloadLibrary().  We load a library with a set
// of callouts then unload it.  We need to check that the callouts have been
// removed.  We'll also check that the library's unload() function was called
// as well.

TEST_F(LibraryManagerTest, LibUnload) {

    // Load the only library, specifying the index of 0 as it's the only
    // library.  This should load all callouts.
    PublicLibraryManager lib_manager(std::string(FULL_CALLOUT_LIBRARY),
                               0, callout_manager_);
    EXPECT_TRUE(lib_manager.openLibrary());

    // Check the version of the library.
    EXPECT_TRUE(lib_manager.checkVersion());

    // No callouts should be registered at the moment.
    EXPECT_FALSE(callout_manager_->calloutsPresent(hookpt_one_index_));
    EXPECT_FALSE(callout_manager_->calloutsPresent(hookpt_two_index_));
    EXPECT_FALSE(callout_manager_->calloutsPresent(hookpt_three_index_));

    // Load the single standard callout and check it is registered correctly.
    EXPECT_NO_THROW(lib_manager.registerStandardCallouts());
    EXPECT_TRUE(callout_manager_->calloutsPresent(hookpt_one_index_));
    EXPECT_FALSE(callout_manager_->calloutsPresent(hookpt_two_index_));
    EXPECT_FALSE(callout_manager_->calloutsPresent(hookpt_three_index_));

    // Call the load function to load the other callouts.
    EXPECT_TRUE(lib_manager.runLoad());
    EXPECT_TRUE(callout_manager_->calloutsPresent(hookpt_one_index_));
    EXPECT_TRUE(callout_manager_->calloutsPresent(hookpt_two_index_));
    EXPECT_TRUE(callout_manager_->calloutsPresent(hookpt_three_index_));

    // Unload the library and check that the callouts have been removed from
    // the CalloutManager.
    lib_manager.unloadLibrary();
    EXPECT_FALSE(callout_manager_->calloutsPresent(hookpt_one_index_));
    EXPECT_FALSE(callout_manager_->calloutsPresent(hookpt_two_index_));
    EXPECT_FALSE(callout_manager_->calloutsPresent(hookpt_three_index_));
}

// Now come the loadLibrary() tests that make use of all the methods tested
// above.  These tests are really to make sure that the methods have been
// tied together correctly.

// First test the basic error cases - no library, no version function, version
// function returning an error.

TEST_F(LibraryManagerTest, LoadLibraryNoLibrary) {
    LibraryManager lib_manager(std::string(NOT_PRESENT_LIBRARY), 0,
                                           callout_manager_);
    EXPECT_FALSE(lib_manager.loadLibrary());
}

// Check that the code handles the case of a library with no version function.

TEST_F(LibraryManagerTest, LoadLibraryNoVersion) {
    LibraryManager lib_manager(std::string(NO_VERSION_LIBRARY), 0,
                                           callout_manager_);
    EXPECT_FALSE(lib_manager.loadLibrary());
}

// Check that the code handles the case of a library with a version function
// that returns an incorrect version number.

TEST_F(LibraryManagerTest, LoadLibraryWrongVersion) {
    LibraryManager lib_manager(std::string(INCORRECT_VERSION_LIBRARY), 0,
                                           callout_manager_);
    EXPECT_FALSE(lib_manager.loadLibrary());
}

// Check that the full loadLibrary call works.

TEST_F(LibraryManagerTest, LoadLibrary) {
    LibraryManager lib_manager(std::string(FULL_CALLOUT_LIBRARY), 0,
                                           callout_manager_);
    EXPECT_TRUE(lib_manager.loadLibrary());

    // Now execute the callouts in the order expected.  The library performs
    // the calculation:
    //
    // r3 = (7 * d1 - d2) * d3
    executeCallCallouts(7, 5, 35, 9, 26, 3, 78);

    EXPECT_TRUE(lib_manager.unloadLibrary());

    // Check that the callouts have been removed from the callout manager.
    EXPECT_FALSE(callout_manager_->calloutsPresent(hookpt_one_index_));
    EXPECT_FALSE(callout_manager_->calloutsPresent(hookpt_two_index_));
    EXPECT_FALSE(callout_manager_->calloutsPresent(hookpt_three_index_));
}

// Now test for multiple libraries.  We'll load the full callout library
// first, then load some of the libraries with missing framework functions.
// This will check that when searching for framework functions, only the
// specified library is checked, not other loaded libraries. We will
// load a second library with suitable callouts and check that the callouts
// are added correctly. Finally, we'll unload one of the libraries and
// check that only the callouts belonging to that library were removed.

TEST_F(LibraryManagerTest, LoadMultipleLibraries) {
    // Load a library with all framework functions.
    LibraryManager lib_manager_1(std::string(FULL_CALLOUT_LIBRARY), 0,
                                 callout_manager_);
    EXPECT_TRUE(lib_manager_1.loadLibrary());

    // Attempt to load a library with no version() function.  We should detect
    // this and not end up calling the function from the already loaded
    // library.
    LibraryManager lib_manager_2(std::string(NO_VERSION_LIBRARY), 1,
                                 callout_manager_);
    EXPECT_FALSE(lib_manager_2.loadLibrary());

    // Attempt to load the library with an incorrect version.  This should
    // be detected.
    LibraryManager lib_manager_3(std::string(INCORRECT_VERSION_LIBRARY), 1,
                                 callout_manager_);
    EXPECT_FALSE(lib_manager_3.loadLibrary());

    // Load the basic callout library.  This only has standard callouts so,
    // if the first library's load() function gets called, some callouts
    // will be registered twice and lead to incorrect results.
    LibraryManager lib_manager_4(std::string(BASIC_CALLOUT_LIBRARY), 1,
                                 callout_manager_);
    EXPECT_TRUE(lib_manager_4.loadLibrary());

    // Execute the callouts.  The first library implements the calculation.
    //
    // r3 = (7 * d1 - d2) * d3
    //
    // The last-loaded library implements the calculation
    //
    // r3 = (10 + d1) * d2 - d3
    //
    // Putting the processing for each library together in the appropriate
    // order, we get:
    //
    // r3 = ((10 * d1 + d1) - d2) * d2 * d3 - d3
    executeCallCallouts(10, 3, 33, 2, 62, 3, 183);

    // All done, so unload the first library.
    EXPECT_TRUE(lib_manager_1.unloadLibrary());

    // Now execute the callouts again and check that the results are as
    // expected for the new calculation.
    executeCallCallouts(10, 5, 15, 7, 105, 17, 88);

    // ... and tidy up.
    EXPECT_TRUE(lib_manager_4.unloadLibrary());
}

// Check that libraries can be validated.

TEST_F(LibraryManagerTest, validateLibraries) {
    EXPECT_TRUE(LibraryManager::validateLibrary(BASIC_CALLOUT_LIBRARY));
    EXPECT_TRUE(LibraryManager::validateLibrary(FULL_CALLOUT_LIBRARY));
    EXPECT_FALSE(LibraryManager::validateLibrary(FRAMEWORK_EXCEPTION_LIBRARY));
    EXPECT_FALSE(LibraryManager::validateLibrary(INCORRECT_VERSION_LIBRARY));
    EXPECT_TRUE(LibraryManager::validateLibrary(LOAD_CALLOUT_LIBRARY));
    EXPECT_TRUE(LibraryManager::validateLibrary(LOAD_ERROR_CALLOUT_LIBRARY));
    EXPECT_FALSE(LibraryManager::validateLibrary(NOT_PRESENT_LIBRARY));
    EXPECT_FALSE(LibraryManager::validateLibrary(NO_VERSION_LIBRARY));
    EXPECT_TRUE(LibraryManager::validateLibrary(UNLOAD_CALLOUT_LIBRARY));
}

// Check that log messages are properly registered and unregistered.

TEST_F(LibraryManagerTest, libraryLoggerSetup) {
    // Load a library with all framework functions.
    LibraryManager lib_manager(std::string(BASIC_CALLOUT_LIBRARY), 0,
                               callout_manager_);
    EXPECT_TRUE(lib_manager.loadLibrary());

    // After loading the library, the global logging dictionary should
    // contain log messages registerd for this library.
    const MessageDictionaryPtr& dict = MessageDictionary::globalDictionary();
    EXPECT_EQ("basic callout load %1", dict->getText("BCL_LOAD_START"));
    EXPECT_EQ("basic callout load end", dict->getText("BCL_LOAD_END"));
    // Some of the messages defined by the hook library are duplicates. But,
    // the loadLibrary function should have logged the duplicates and clear
    // the duplicates list. By checking that the list of duplicates is empty
    // we test that the LibraryManager handles the duplicates (logs and
    // clears them).
    EXPECT_TRUE(MessageInitializer::getDuplicates().empty());

    // After unloading the library, the messages should be unregistered.
    EXPECT_TRUE(lib_manager.unloadLibrary());
    EXPECT_TRUE(dict->getText("BCL_LOAD_START").empty());
    EXPECT_TRUE(dict->getText("BCL_LOAD_END").empty());
}

} // Anonymous namespace
