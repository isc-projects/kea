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
#include <hooks/library_manager_collection.h>
#include <hooks/server_hooks.h>

#include <hooks/tests/marker_file.h>
#include <hooks/tests/test_libraries.h>

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

#include <algorithm>
#include <fstream>
#include <string>

#include <unistd.h>


using namespace isc;
using namespace isc::hooks;
using namespace std;

namespace {

/// @brief Library manager collection test class

class LibraryManagerCollectionTest : public ::testing::Test {
public:
    /// @brief Constructor
    LibraryManagerCollectionTest() {

        // Set up the server hooks.  ServerHooks is a singleton, so we reset it
        // between each test.
        ServerHooks& hooks = ServerHooks::getServerHooks();
        hooks.reset();
        lm_one_index_ = hooks.registerHook("lm_one");
        lm_two_index_ = hooks.registerHook("lm_two");
        lm_three_index_ = hooks.registerHook("lm_three");

        // Ensure the marker file is not present at the start of a test.
        static_cast<void>(unlink(MARKER_FILE));
    }

    /// @brief Destructor
    ///
    /// Ensures a marker file is removed after each test.
    ~LibraryManagerCollectionTest() {
        static_cast<void>(unlink(MARKER_FILE));
    }

    /// @brief Call callouts test
    ///
    /// All of the loaded libraries for which callouts are called register four
    /// callouts: a context_create callout and three callouts that are attached
    /// to hooks lm_one, lm_two and lm_three.  These four callouts, executed
    /// in sequence, perform a series of calculations. Data is passed between
    /// callouts in the argument list, in a variable named "result".
    ///
    /// context_create initializes the calculation by setting a seed
    /// value, called r0 here.  This value is dependent on the library being
    /// loaded.  Prior to that, the argument "result" is initialized to -1,
    /// the purpose being to avoid exceptions when running this test with no
    /// libraries loaded.
    ///
    /// Callout lm_one is passed a value d1 and performs a simple arithmetic
    /// operation on it and r0 yielding a result r1.  Hence we can say that
    /// @f[ r1 = lm1(r0, d1) @f]
    ///
    /// Callout lm_two is passed a value d2 and peforms another simple
    /// arithmetic operation on it and d2, yielding r2, i.e.
    /// @f[ r2 = lm2(d1, d2) @f]
    ///
    /// lm_three does a similar operation giving @f[ r3 = lm3(r2, d3) @f].
    ///
    /// The details of the operations lm1, lm2 and lm3 depend on the library.
    /// However the sequence of calls needed to do this set of calculations
    /// is identical regardless of the exact functions. This method performs
    /// those operations and checks the results of each step.
    ///
    /// It is assumed that callout_manager_ has been set up appropriately.
    ///
    /// @note The CalloutHandle used in the calls is declared locally here.
    ///       The advantage of this (apart from scope reduction) is that on
    ///       exit, it is destroyed.  This removes any references to memory
    ///       allocated by loaded libraries while they are still loaded.
    ///
    /// @param r0...r3, d1..d3 Values and intermediate values expected.  They
    ///        are ordered so that the variables appear in the argument list in
    ///        the order they are used.
    void executeCallCallouts(int r0, int d1, int r1, int d2, int r2, int d3,
                             int r3) {
        static const char* COMMON_TEXT = " callout returned the wong value";
        static const char* RESULT = "result";

        int result;

        // Set up a callout handle for the calls.
        CalloutHandle callout_handle(callout_manager_);

        // Initialize the argument RESULT.  This simplifies testing by
        // eliminating the generation of an exception when we try the unload
        // test.  In that case, RESULT is unchanged.
        callout_handle.setArgument(RESULT, -1);

        // Seed the calculation.
        callout_manager_->callCallouts(ServerHooks::CONTEXT_CREATE,
                                       callout_handle);
        callout_handle.getArgument(RESULT, result);
        EXPECT_EQ(r0, result) << "context_create" << COMMON_TEXT;

        // Perform the first calculation.
        callout_handle.setArgument("data_1", d1);
        callout_manager_->callCallouts(lm_one_index_, callout_handle);
        callout_handle.getArgument(RESULT, result);
        EXPECT_EQ(r1, result) << "lm_one" << COMMON_TEXT;

        // ... the second ...
        callout_handle.setArgument("data_2", d2);
        callout_manager_->callCallouts(lm_two_index_, callout_handle);
        callout_handle.getArgument(RESULT, result);
        EXPECT_EQ(r2, result) << "lm_two" << COMMON_TEXT;

        // ... and the third.
        callout_handle.setArgument("data_3", d3);
        callout_manager_->callCallouts(lm_three_index_, callout_handle);
        callout_handle.getArgument(RESULT, result);
        EXPECT_EQ(r3, result) << "lm_three" << COMMON_TEXT;
    }

    /// Hook indexes.  These are are made public for ease of reference.
    int lm_one_index_;
    int lm_two_index_;
    int lm_three_index_;

    /// Callout manager used in the executeCallCallouts() call.
    boost::shared_ptr<CalloutManager> callout_manager_;
};

/// @brief Public library manager collection class
///
/// This is an instance of the LibraryManagerCollection class but with the
/// protected methods made public for test purposes.

class PublicLibraryManagerCollection
                : public isc::hooks::LibraryManagerCollection {
public:
    /// @brief Constructor
    ///
    /// @param List of libraries that this collection will manage.  The order
    ///        of the libraries is important.
    PublicLibraryManagerCollection(const std::vector<std::string>& libraries)
        : LibraryManagerCollection(libraries)
    {}

    /// Public methods that call protected methods on the superclass.
    using LibraryManagerCollection::unloadLibraries;
};


// This is effectively the same test as for LibraryManager, but using the
// LibraryManagerCollection object.

TEST_F(LibraryManagerCollectionTest, LoadLibraries) {

    // Set up the list of libraries to be loaded.
    std::vector<std::string> library_names;
    library_names.push_back(std::string(FULL_CALLOUT_LIBRARY));
    library_names.push_back(std::string(BASIC_CALLOUT_LIBRARY));

    // Set up the library manager collection and get the callout manager we'll
    // be using.
    PublicLibraryManagerCollection lm_collection(library_names);

    // Load the libraries.
    EXPECT_TRUE(lm_collection.loadLibraries());
    callout_manager_ = lm_collection.getCalloutManager();

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
    {
        SCOPED_TRACE("Doing calculation with libraries loaded");
        executeCallCallouts(10, 3, 33, 2, 62, 3, 183);
    }

    // Try unloading the libraries.
    EXPECT_NO_THROW(lm_collection.unloadLibraries());

    // Re-execute the calculation - callouts can be called but as nothing
    // happens, the result should always be -1.
    {
        SCOPED_TRACE("Doing calculation with libraries not loaded");
        executeCallCallouts(-1, 3, -1, 22, -1, 83, -1);
    }
}

// This is effectively the same test as above, but with a library generating
// an error when loaded. It is expected that the failing library will not be
// loaded, but others will be.

TEST_F(LibraryManagerCollectionTest, LoadLibrariesWithError) {

    // Set up the list of libraries to be loaded.
    std::vector<std::string> library_names;
    library_names.push_back(std::string(FULL_CALLOUT_LIBRARY));
    library_names.push_back(std::string(INCORRECT_VERSION_LIBRARY));
    library_names.push_back(std::string(BASIC_CALLOUT_LIBRARY));

    // Set up the library manager collection and get the callout manager we'll
    // be using.
    PublicLibraryManagerCollection lm_collection(library_names);

    // Load the libraries.  We expect a failure status to be returned as
    // one of the libraries failed to load.
    EXPECT_FALSE(lm_collection.loadLibraries());
    callout_manager_ = lm_collection.getCalloutManager();

    // Expect only two libraries were loaded.
    EXPECT_EQ(2, callout_manager_->getNumLibraries());

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
    {
        SCOPED_TRACE("Doing calculation with libraries loaded");
        executeCallCallouts(10, 3, 33, 2, 62, 3, 183);
    }

    // Try unloading the libraries.
    EXPECT_NO_THROW(lm_collection.unloadLibraries());

    // Re-execute the calculation - callouts can be called but as nothing
    // happens, the result should always be -1.
    {
        SCOPED_TRACE("Doing calculation with libraries not loaded");
        executeCallCallouts(-1, 3, -1, 22, -1, 83, -1);
    }
}

// Check that everything works even with no libraries loaded.

TEST_F(LibraryManagerCollectionTest, NoLibrariesLoaded) {
    // Set up the list of libraries to be loaded.
    std::vector<std::string> library_names;

    // Set up the library manager collection and get the callout manager we'll
    // be using.
    LibraryManagerCollection lm_collection(library_names);
    EXPECT_TRUE(lm_collection.loadLibraries());
    callout_manager_ = lm_collection.getCalloutManager();

    // Load the libraries.
    EXPECT_TRUE(lm_collection.loadLibraries());

    // Eecute the calculation - callouts can be called but as nothing
    // happens, the result should always be -1.
    executeCallCallouts(-1, 3, -1, 22, -1, 83, -1);
}

} // Anonymous namespace
