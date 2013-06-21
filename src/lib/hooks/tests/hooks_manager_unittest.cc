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
#include <hooks/hooks_manager.h>

#include <hooks/tests/common_test_class.h>
#include <hooks/tests/test_libraries.h>

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

#include <algorithm>
#include <string>


using namespace isc;
using namespace isc::hooks;
using namespace std;

namespace {

/// @brief Hooks manager collection test class

class HooksManagerTest : public ::testing::Test,
                         public HooksCommonTestClass {
public:
    /// @brief Constructor
    ///
    /// Reset the hooks manager.  The hooks manager is a singleton, so needs
    /// to be reset for each test.
    HooksManagerTest() {
        HooksManager::getHooksManager().reset();
    }

    /// @brief Call callouts test
    ///
    /// See the header for HooksCommonTestClass::execute for details.
    ///
    /// @param r0...r3, d1..d3 Values and intermediate values expected.  They
    ///        are ordered so that the variables appear in the argument list in
    ///        the order they are used.
    void executeCallCallouts(int r0, int d1, int r1, int d2, int r2, int d3,
                             int r3) {
        static const char* COMMON_TEXT = " callout returned the wong value";
        static const char* RESULT = "result";

        // Get a CalloutHandle for the calculation.
        CalloutHandlePtr handle = HooksManager::createCalloutHandle();

        // Initialize the argument RESULT.  This simplifies testing by
        // eliminating the generation of an exception when we try the unload
        // test.  In that case, RESULT is unchanged.
        int result = -1;
        handle->setArgument(RESULT, result);

        // Seed the calculation.
        HooksManager::callCallouts(isc::hooks::ServerHooks::CONTEXT_CREATE,
                                   *handle);
        handle->getArgument(RESULT, result);
        EXPECT_EQ(r0, result) << "context_create" << COMMON_TEXT;

        // Perform the first calculation.
        handle->setArgument("data_1", d1);
        HooksManager::callCallouts(lm_one_index_, *handle);
        handle->getArgument(RESULT, result);
        EXPECT_EQ(r1, result) << "lm_one" << COMMON_TEXT;

        // ... the second ...
        handle->setArgument("data_2", d2);
        HooksManager::callCallouts(lm_two_index_, *handle);
        handle->getArgument(RESULT, result);
        EXPECT_EQ(r2, result) << "lm_two" << COMMON_TEXT;

        // ... and the third.
        handle->setArgument("data_3", d3);
        HooksManager::callCallouts(lm_three_index_, *handle);
        handle->getArgument(RESULT, result);
        EXPECT_EQ(r3, result) << "lm_three" << COMMON_TEXT;
    }

};
/*
// This is effectively the same test as for LibraryManager, but using the
// LibraryManagerCollection object.

TEST_F(HooksManagerTest, LoadLibraries) {

    // Set up the list of libraries to be loaded.
    std::vector<std::string> library_names;
    library_names.push_back(std::string(FULL_CALLOUT_LIBRARY));
    library_names.push_back(std::string(BASIC_CALLOUT_LIBRARY));

    // Set up the library manager collection and get the callout manager we'll
    // be using.
    PublicLibraryManagerCollection lm_collection(library_names);

    // Load the libraries.
    EXPECT_TRUE(lm_collection.loadLibraries());
    boost::shared_ptr<CalloutManager> manager =
                                      lm_collection.getCalloutManager();

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
        executeCallCallouts(manager, 10, 3, 33, 2, 62, 3, 183);
    }

    // Try unloading the libraries.
    EXPECT_NO_THROW(lm_collection.unloadLibraries());

    // Re-execute the calculation - callouts can be called but as nothing
    // happens, the result should always be -1.
    {
        SCOPED_TRACE("Doing calculation with libraries not loaded");
        executeCallCallouts(manager, -1, 3, -1, 22, -1, 83, -1);
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
    boost::shared_ptr<CalloutManager> manager =
                                      lm_collection.getCalloutManager();

    // Expect only two libraries were loaded.
    EXPECT_EQ(2, manager->getNumLibraries());

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
        executeCallCallouts(manager, 10, 3, 33, 2, 62, 3, 183);
    }

    // Try unloading the libraries.
    EXPECT_NO_THROW(lm_collection.unloadLibraries());

    // Re-execute the calculation - callouts can be called but as nothing
    // happens, the result should always be -1.
    {
        SCOPED_TRACE("Doing calculation with libraries not loaded");
        executeCallCallouts(manager, -1, 3, -1, 22, -1, 83, -1);
    }
}
*/
// Check that everything works even with no libraries loaded.  First that
// calloutsPresent() always returns false.

TEST_F(HooksManagerTest, NoLibrariesCalloutsPresent) {
    // No callouts should be present on any hooks.
    EXPECT_FALSE(HooksManager::calloutsPresent(lm_one_index_));
    EXPECT_FALSE(HooksManager::calloutsPresent(lm_two_index_));
    EXPECT_FALSE(HooksManager::calloutsPresent(lm_three_index_));
}

TEST_F(HooksManagerTest, NoLibrariesCallCallouts) {
    executeCallCallouts(-1, 3, -1, 22, -1, 83, -1);
}

} // Anonymous namespace
