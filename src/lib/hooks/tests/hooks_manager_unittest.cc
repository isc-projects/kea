// Copyright (C) 2013-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <hooks/callout_handle.h>
#include <hooks/hooks_manager.h>
#include <hooks/server_hooks.h>

#include <hooks/tests/common_test_class.h>
#include <hooks/tests/test_libraries.h>
#include <cc/data.h>

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

#include <algorithm>
#include <string>

using namespace isc;
using namespace isc::hooks;
using namespace isc::data;
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
        HooksManager::unloadLibraries();
    }

    /// @brief Destructor
    ///
    /// Unload all libraries and reset the shared manager.
    ~HooksManagerTest() {
        HooksManager::unloadLibraries();
        HooksManager::getSharedCalloutManager().reset();
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
        static const char* COMMON_TEXT = " callout returned the wrong value";
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
        HooksManager::callCallouts(hookpt_one_index_, *handle);
        handle->getArgument(RESULT, result);
        EXPECT_EQ(r1, result) << "hookpt_one" << COMMON_TEXT;

        // ... the second ...
        handle->setArgument("data_2", d2);
        HooksManager::callCallouts(hookpt_two_index_, *handle);
        handle->getArgument(RESULT, result);
        EXPECT_EQ(r2, result) << "hookpt_two" << COMMON_TEXT;

        // ... and the third.
        handle->setArgument("data_3", d3);
        HooksManager::callCallouts(hookpt_three_index_, *handle);
        handle->getArgument(RESULT, result);
        EXPECT_EQ(r3, result) << "hookpt_three" << COMMON_TEXT;
    }

    /// @brief Call command handlers test.
    ///
    /// This test is similar to @c executeCallCallouts but it uses
    /// @ref HooksManager::callCommandHandlers to execute the command
    /// handlers for the following commands: 'command-one' and 'command-two'.
    ///
    /// @param r1..r2, d1..d2 Data (dN) and expected results (rN).
    void executeCallCommandHandlers(int d1, int r1, int d2, int r2) {
        static const char* COMMON_TEXT = " command handler returned the wrong value";
        static const char* RESULT = "result";

        int result;

        // Set up a callout handle for the calls.
        CalloutHandlePtr handle = HooksManager::createCalloutHandle();

        // Initialize the argument RESULT.  This simplifies testing by
        // eliminating the generation of an exception when we try the unload
        // test.  In that case, RESULT is unchanged.
        handle->setArgument(RESULT, -1);

        // Perform the first calculation: it should assign the data to the
        // result.
        handle->setArgument("data_1", d1);
        HooksManager::callCommandHandlers("command-one", *handle);
        handle->getArgument(RESULT, result);
        EXPECT_EQ(r1, result) << "command-one" << COMMON_TEXT;

        // Perform the second calculation: it should multiply the data by 10
        // and return in the result.
        handle->setArgument("data_2", d2);
        HooksManager::callCommandHandlers("command-two", *handle);
        handle->getArgument(RESULT, result);
        EXPECT_EQ(r2, result) << "command-two" << COMMON_TEXT;
    }

private:
    /// To avoid unused variable errors
    std::string dummy(int i) {
        if (i == 0) {
            return (MARKER_FILE);
        } else if (i > 0) {
            return (LOAD_CALLOUT_LIBRARY);
        } else {
            return (LOAD_ERROR_CALLOUT_LIBRARY);
        }
    }
};

// This is effectively the same test as for LibraryManager, but using the
// HooksManager object.

TEST_F(HooksManagerTest, LoadLibraries) {

    // Set up the list of libraries to be loaded.
    HookLibsCollection library_names;
    library_names.push_back(make_pair(std::string(FULL_CALLOUT_LIBRARY),
                                      data::ConstElementPtr()));
    library_names.push_back(make_pair(std::string(BASIC_CALLOUT_LIBRARY),
                                      data::ConstElementPtr()));

    // Load the libraries.
    EXPECT_TRUE(HooksManager::loadLibraries(library_names));

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
        SCOPED_TRACE("Calculation with libraries loaded");
        executeCallCallouts(10, 3, 33, 2, 62, 3, 183);
    }

    // r2 = 5 * 7 * 10
    {
        SCOPED_TRACE("Calculation using command handlers");
        executeCallCommandHandlers(5, 5, 7, 350);
    }

    // Try unloading the libraries.
    EXPECT_NO_THROW(HooksManager::unloadLibraries());

    // Re-execute the calculation - callouts can be called but as nothing
    // happens, the result should always be -1.
    {
        SCOPED_TRACE("Calculation with libraries not loaded");
        executeCallCallouts(-1, 3, -1, 22, -1, 83, -1);
    }
}

// This is effectively the same test as above, but with a library generating
// an error when loaded. It is expected that the failing library will not be
// loaded, but others will be.

TEST_F(HooksManagerTest, LoadLibrariesWithError) {

    // Set up the list of libraries to be loaded.
    HookLibsCollection library_names;
    library_names.push_back(make_pair(std::string(FULL_CALLOUT_LIBRARY),
                                      data::ConstElementPtr()));
    library_names.push_back(make_pair(std::string(INCORRECT_VERSION_LIBRARY),
                                      data::ConstElementPtr()));
    library_names.push_back(make_pair(std::string(BASIC_CALLOUT_LIBRARY),
                                      data::ConstElementPtr()));

    // Load the libraries.  We expect a failure return because one of the
    // libraries fails to load.
    EXPECT_FALSE(HooksManager::loadLibraries(library_names));
}

// Test that we can unload a set of libraries while we have a CalloutHandle
// created on them in existence, and can delete the handle afterwards.

TEST_F(HooksManagerTest, CalloutHandleUnloadLibrary) {

    // Set up the list of libraries to be loaded.
    HookLibsCollection library_names;
    library_names.push_back(make_pair(std::string(FULL_CALLOUT_LIBRARY),
                                      data::ConstElementPtr()));

    // Load the libraries.
    EXPECT_TRUE(HooksManager::loadLibraries(library_names));

    // Execute the callouts.  This library implements:
    //
    // r3 = (7 * d1 - d2) * d3
    {
        SCOPED_TRACE("Calculation with full callout library loaded");
        executeCallCallouts(7, 4, 28, 8, 20, 2, 40);
    }

    // Get an outstanding callout handle on this library.
    CalloutHandlePtr handle = HooksManager::createCalloutHandle();

    // Execute once of the callouts again to ensure that the handle contains
    // memory allocated by the library.
    HooksManager::callCallouts(ServerHooks::CONTEXT_CREATE, *handle);

    // Unload the libraries.
    HooksManager::unloadLibraries();

    // Deleting the callout handle should not cause a segmentation fault.
    handle.reset();
}

// Test that we can load a new set of libraries while we have a CalloutHandle
// created on them in existence, and can delete the handle afterwards.

TEST_F(HooksManagerTest, CalloutHandleLoadLibrary) {

    // Set up the list of libraries to be loaded.
    HookLibsCollection library_names;
    library_names.push_back(make_pair(std::string(FULL_CALLOUT_LIBRARY),
                                      data::ConstElementPtr()));

    // Load the libraries.
    EXPECT_TRUE(HooksManager::loadLibraries(library_names));

    // Execute the callouts.  This library implements:
    //
    // r3 = (7 * d1 - d2) * d3
    {
        SCOPED_TRACE("Calculation with full callout library loaded");
        executeCallCallouts(7, 4, 28, 8, 20, 2, 40);
    }

    // Get an outstanding callout handle on this library and execute one of
    // the callouts again to ensure that the handle contains memory allocated
    // by the library.
    CalloutHandlePtr handle = HooksManager::createCalloutHandle();
    HooksManager::callCallouts(ServerHooks::CONTEXT_CREATE, *handle);

    // Load a new library that implements the calculation
    //
    // r3 = (10 + d1) * d2 - d3
    HookLibsCollection new_library_names;
    new_library_names.push_back(make_pair(std::string(BASIC_CALLOUT_LIBRARY),
                                          data::ConstElementPtr()));

    // Load the libraries.
    EXPECT_TRUE(HooksManager::loadLibraries(new_library_names));

    // Execute the calculation.  Note that we still have the CalloutHandle
    // for the old library: however, this should not affect the new calculation.
    {
        SCOPED_TRACE("Calculation with basic callout library loaded");
        executeCallCallouts(10, 7, 17, 3, 51, 16, 35);
    }

    // Deleting the old callout handle should not cause a segmentation fault.
    handle.reset();
}

// This is effectively the same test as the LoadLibraries test.

TEST_F(HooksManagerTest, ReloadSameLibraries) {

    // Set up the list of libraries to be loaded.
    HookLibsCollection library_names;
    library_names.push_back(make_pair(std::string(FULL_CALLOUT_LIBRARY),
                                      data::ConstElementPtr()));
    library_names.push_back(make_pair(std::string(BASIC_CALLOUT_LIBRARY),
                                      data::ConstElementPtr()));

    // Load the libraries.
    EXPECT_TRUE(HooksManager::loadLibraries(library_names));

    // Execute the callouts.  See the LoadLibraries test for an explanation of
    // the calculation.
    {
        SCOPED_TRACE("Calculation with libraries loaded");
        executeCallCallouts(10, 3, 33, 2, 62, 3, 183);
    }

    // Try reloading the libraries and re-execute the calculation - we should
    // get the same results.
    EXPECT_NO_THROW(HooksManager::loadLibraries(library_names));
    {
        SCOPED_TRACE("Calculation with libraries reloaded");
        executeCallCallouts(10, 3, 33, 2, 62, 3, 183);
    }
}

TEST_F(HooksManagerTest, ReloadLibrariesReverseOrder) {

    // Set up the list of libraries to be loaded and load them.
    HookLibsCollection library_names;
    library_names.push_back(make_pair(std::string(FULL_CALLOUT_LIBRARY),
                                      data::ConstElementPtr()));
    library_names.push_back(make_pair(std::string(BASIC_CALLOUT_LIBRARY),
                                      data::ConstElementPtr()));
    EXPECT_TRUE(HooksManager::loadLibraries(library_names));

    // Execute the callouts.  The first library implements the calculation.
    //
    // r3 = (7 * d1 - d2) * d3
    //
    // The last-loaded library implements the calculation
    //
    // r3 = (10 + d1) * d2 - d3
    //
    // Putting the processing for each library together in the given order
    // gives.
    //
    // r3 = ((10 * d1 + d1) - d2) * d2 * d3 - d3
    {
        SCOPED_TRACE("Calculation with libraries loaded");
        executeCallCallouts(10, 3, 33, 2, 62, 3, 183);
    }

    // Reload the libraries in the reverse order.
    std::reverse(library_names.begin(), library_names.end());
    EXPECT_TRUE(HooksManager::loadLibraries(library_names));

    // The calculation in the reverse order gives:
    //
    // r3 = ((((7 + d1) * d1) * d2 - d2) - d3) * d3
    {
        SCOPED_TRACE("Calculation with libraries loaded in reverse order");
        executeCallCallouts(7, 3, 30, 3, 87, 7, 560);
    }
}

// Local callouts for the test of server-registered callouts.

namespace {

    int
testPreCallout(CalloutHandle& handle) {
    handle.setArgument("result", static_cast<int>(1027));
    return (0);
}

int
testPostCallout(CalloutHandle& handle) {
    int result;
    handle.getArgument("result", result);
    result *= 2;
    handle.setArgument("result", result);
    return (0);
}

}

// The next test registers the pre and post- callouts above for hook hookpt_two,
// and checks they are called.

TEST_F(HooksManagerTest, PrePostCalloutTest) {

    // Load a single library.
    HookLibsCollection library_names;
    library_names.push_back(make_pair(std::string(FULL_CALLOUT_LIBRARY),
                                      data::ConstElementPtr()));
    EXPECT_TRUE(HooksManager::loadLibraries(library_names));

    // Load the pre- and post- callouts.
    HooksManager::preCalloutsLibraryHandle().registerCallout("hookpt_two",
                                                             testPreCallout);
    HooksManager::postCalloutsLibraryHandle().registerCallout("hookpt_two",
                                                              testPostCallout);

    // Execute the callouts.  hookpt_two implements the calculation:
    //
    //  "result - data_2"
    //
    // With the pre- and post- callouts above, the result expected is
    //
    // (1027 - data_2) * 2
    CalloutHandlePtr handle = HooksManager::createCalloutHandle();
    handle->setArgument("result", static_cast<int>(0));
    handle->setArgument("data_2", static_cast<int>(15));

    HooksManager::callCallouts(hookpt_two_index_, *handle);

    int result = 0;
    handle->getArgument("result", result);
    EXPECT_EQ(2024, result);

    // ... and check that the pre- and post- callout functions don't survive a
    // reload.
    EXPECT_TRUE(HooksManager::loadLibraries(library_names));
    handle = HooksManager::createCalloutHandle();

    handle->setArgument("result", static_cast<int>(0));
    handle->setArgument("data_2", static_cast<int>(15));

    HooksManager::callCallouts(hookpt_two_index_, *handle);

    result = 0;
    handle->getArgument("result", result);
    EXPECT_EQ(-15, result);
}

// Test with a shared manager the pre- and post- callout functions survive
// a reload

TEST_F(HooksManagerTest, PrePostCalloutShared) {

    HookLibsCollection library_names;

    // Initialize the shared manager.
    HooksManager::getSharedCalloutManager().reset(new CalloutManager(0));

    // Load the pre- and post- callouts.
    HooksManager::preCalloutsLibraryHandle().registerCallout("hookpt_two",
                                                             testPreCallout);
    HooksManager::postCalloutsLibraryHandle().registerCallout("hookpt_two",
                                                              testPostCallout);

    // With the pre- and post- callouts above, the result expected is
    //
    // 1027 * 2
    CalloutHandlePtr handle = HooksManager::createCalloutHandle();
    handle->setArgument("result", static_cast<int>(0));
    handle->setArgument("data_2", static_cast<int>(15));

    HooksManager::callCallouts(hookpt_two_index_, *handle);

    int result = 0;
    handle->getArgument("result", result);
    EXPECT_EQ(2054, result);

    // ... and check that the pre- and post- callout functions survive a
    // reload.
    EXPECT_TRUE(HooksManager::loadLibraries(library_names));
    handle = HooksManager::createCalloutHandle();

    handle->setArgument("result", static_cast<int>(0));
    handle->setArgument("data_2", static_cast<int>(15));

    HooksManager::callCallouts(hookpt_two_index_, *handle);

    // Expect same value i.e. 1027 * 2
    result = 0;
    handle->getArgument("result", result);
    EXPECT_EQ(2054, result);
}

// Test with a shared manager the pre- and post- callout functions survive
// a reload but not with a not empty list of libraries

TEST_F(HooksManagerTest, PrePostCalloutSharedNotEmpty) {

    HookLibsCollection library_names;
    library_names.push_back(make_pair(std::string(FULL_CALLOUT_LIBRARY),
                                      data::ConstElementPtr()));

    // Initialize the shared manager.
    HooksManager::getSharedCalloutManager().reset(new CalloutManager(0));

    // Load the pre- and post- callouts.
    HooksManager::preCalloutsLibraryHandle().registerCallout("hookpt_two",
                                                             testPreCallout);
    HooksManager::postCalloutsLibraryHandle().registerCallout("hookpt_two",
                                                              testPostCallout);

    // With the pre- and post- callouts above, the result expected is
    //
    // 1027 * 2
    CalloutHandlePtr handle = HooksManager::createCalloutHandle();
    handle->setArgument("result", static_cast<int>(0));
    handle->setArgument("data_2", static_cast<int>(15));

    HooksManager::callCallouts(hookpt_two_index_, *handle);

    int result = 0;
    handle->getArgument("result", result);
    EXPECT_EQ(2054, result);

    // ... and check that the pre- and post- callout functions don't survive a
    // reload with a not empty list of libraries.
    EXPECT_TRUE(HooksManager::loadLibraries(library_names));
    handle = HooksManager::createCalloutHandle();

    handle->setArgument("result", static_cast<int>(0));
    handle->setArgument("data_2", static_cast<int>(15));

    HooksManager::callCallouts(hookpt_two_index_, *handle);

    // Expect result - data_2
    result = 0;
    handle->getArgument("result", result);
    EXPECT_EQ(-15, result);
}

// Test with a shared manager the pre- and post- callout functions don't
// survive a reload if the shared manager is initialized too late.

TEST_F(HooksManagerTest, PrePostCalloutSharedTooLate) {

    HookLibsCollection library_names;
    EXPECT_TRUE(HooksManager::loadLibraries(library_names));

    // Initialize the shared manager (after loadLibraries so too late)
    HooksManager::getSharedCalloutManager().reset(new CalloutManager(0));

    // Load the pre- and post- callouts.
    HooksManager::preCalloutsLibraryHandle().registerCallout("hookpt_two",
                                                             testPreCallout);
    HooksManager::postCalloutsLibraryHandle().registerCallout("hookpt_two",
                                                              testPostCallout);

    // With the pre- and post- callouts above, the result expected is
    //
    // 1027 * 2
    CalloutHandlePtr handle = HooksManager::createCalloutHandle();
    handle->setArgument("result", static_cast<int>(0));
    handle->setArgument("data_2", static_cast<int>(15));

    HooksManager::callCallouts(hookpt_two_index_, *handle);

    int result = 0;
    handle->getArgument("result", result);
    EXPECT_EQ(2054, result);

    // ... and check that the pre- and post- callout functions don't survive a
    // reload.
    EXPECT_TRUE(HooksManager::loadLibraries(library_names));
    handle = HooksManager::createCalloutHandle();

    handle->setArgument("result", static_cast<int>(0));
    handle->setArgument("data_2", static_cast<int>(15));

    HooksManager::callCallouts(hookpt_two_index_, *handle);

    // Expect no change so result = 0
    result = 0;
    handle->getArgument("result", result);
    EXPECT_EQ(0, result);
}

// Check that everything works even with no libraries loaded.  First that
// calloutsPresent() always returns false.

TEST_F(HooksManagerTest, NoLibrariesCalloutsPresent) {
    // No callouts should be present on any hooks.
    EXPECT_FALSE(HooksManager::calloutsPresent(hookpt_one_index_));
    EXPECT_FALSE(HooksManager::calloutsPresent(hookpt_two_index_));
    EXPECT_FALSE(HooksManager::calloutsPresent(hookpt_three_index_));
    EXPECT_FALSE(HooksManager::commandHandlersPresent("command-one"));
    EXPECT_FALSE(HooksManager::commandHandlersPresent("command-two"));
}

TEST_F(HooksManagerTest, NoLibrariesCallCallouts) {
    executeCallCallouts(-1, 3, -1, 22, -1, 83, -1);
}

// Test the encapsulation of the ServerHooks::registerHook() method.

TEST_F(HooksManagerTest, RegisterHooks) {
    ServerHooks::getServerHooks().reset();
    EXPECT_EQ(2, ServerHooks::getServerHooks().getCount());

    // Check that the hook indexes are as expected. (Use temporary variables
    // as it appears that Google test can't access the constants.)
    int sh_cc = ServerHooks::CONTEXT_CREATE;
    int hm_cc = HooksManager::CONTEXT_CREATE;
    EXPECT_EQ(sh_cc, hm_cc);

    int sh_cd = ServerHooks::CONTEXT_DESTROY;
    int hm_cd = HooksManager::CONTEXT_DESTROY;
    EXPECT_EQ(sh_cd, hm_cd);

    // Register a few hooks and check we have the indexes as expected.
    EXPECT_EQ(2, HooksManager::registerHook(string("alpha")));
    EXPECT_EQ(3, HooksManager::registerHook(string("beta")));
    EXPECT_EQ(4, HooksManager::registerHook(string("gamma")));


    // The code used to throw, but it now allows to register the same
    // hook several times. It simply returns existing index.
    //EXPECT_THROW(static_cast<void>(HooksManager::registerHook(string("alpha"))),
    //             DuplicateHook);
    EXPECT_EQ(2, HooksManager::registerHook(string("alpha")));

    // ... an check the hooks are as we expect.
    EXPECT_EQ(5, ServerHooks::getServerHooks().getCount());
    vector<string> names = ServerHooks::getServerHooks().getHookNames();
    sort(names.begin(), names.end());

    EXPECT_EQ(string("alpha"), names[0]);
    EXPECT_EQ(string("beta"), names[1]);
    EXPECT_EQ(string("context_create"), names[2]);
    EXPECT_EQ(string("context_destroy"), names[3]);
    EXPECT_EQ(string("gamma"), names[4]);
}

// Check that we can get the names of the libraries.

TEST_F(HooksManagerTest, LibraryNames) {

    // Set up the list of libraries to be loaded.
    HookLibsCollection library_names;
    library_names.push_back(make_pair(std::string(FULL_CALLOUT_LIBRARY),
                                      data::ConstElementPtr()));
    library_names.push_back(make_pair(std::string(BASIC_CALLOUT_LIBRARY),
                                      data::ConstElementPtr()));

    // Check the names before the libraries are loaded.
    std::vector<std::string> loaded_names = HooksManager::getLibraryNames();
    EXPECT_TRUE(loaded_names.empty());

    // Load the libraries and check the names again.
    EXPECT_TRUE(HooksManager::loadLibraries(library_names));
    loaded_names = HooksManager::getLibraryNames();
    EXPECT_TRUE(extractNames(library_names) == loaded_names);

    // Unload the libraries and check again.
    EXPECT_NO_THROW(HooksManager::unloadLibraries());
    loaded_names = HooksManager::getLibraryNames();
    EXPECT_TRUE(loaded_names.empty());
}

// Test the library validation function.

TEST_F(HooksManagerTest, validateLibraries) {
    // Vector of libraries that failed validation
    std::vector<std::string> failed;

    // Test different vectors of libraries.

    // No libraries should return a success.
    std::vector<std::string> libraries;

    failed = HooksManager::validateLibraries(libraries);
    EXPECT_TRUE(failed.empty());

    // Single valid library should validate.
    libraries.clear();
    libraries.push_back(BASIC_CALLOUT_LIBRARY);

    failed = HooksManager::validateLibraries(libraries);
    EXPECT_TRUE(failed.empty());

    // Multiple valid libraries should succeed.
    libraries.clear();
    libraries.push_back(BASIC_CALLOUT_LIBRARY);
    libraries.push_back(FULL_CALLOUT_LIBRARY);
    libraries.push_back(UNLOAD_CALLOUT_LIBRARY);

    failed = HooksManager::validateLibraries(libraries);
    EXPECT_TRUE(failed.empty());

    // Single invalid library should fail.
    libraries.clear();
    libraries.push_back(NOT_PRESENT_LIBRARY);

    failed = HooksManager::validateLibraries(libraries);
    EXPECT_TRUE(failed == libraries);

    // Multiple invalid libraries should fail.
    libraries.clear();
    libraries.push_back(INCORRECT_VERSION_LIBRARY);
    libraries.push_back(NO_VERSION_LIBRARY);
    libraries.push_back(FRAMEWORK_EXCEPTION_LIBRARY);

    failed = HooksManager::validateLibraries(libraries);
    EXPECT_TRUE(failed == libraries);

    // Combination of valid and invalid (first one valid) should fail.
    libraries.clear();
    libraries.push_back(FULL_CALLOUT_LIBRARY);
    libraries.push_back(INCORRECT_VERSION_LIBRARY);
    libraries.push_back(NO_VERSION_LIBRARY);

    std::vector<std::string> expected_failures;
    expected_failures.push_back(INCORRECT_VERSION_LIBRARY);
    expected_failures.push_back(NO_VERSION_LIBRARY);

    failed = HooksManager::validateLibraries(libraries);
    EXPECT_TRUE(failed == expected_failures);

    // Combination of valid and invalid (first one invalid) should fail.
    libraries.clear();
    libraries.push_back(NO_VERSION_LIBRARY);
    libraries.push_back(FULL_CALLOUT_LIBRARY);
    libraries.push_back(INCORRECT_VERSION_LIBRARY);

    expected_failures.clear();
    expected_failures.push_back(NO_VERSION_LIBRARY);
    expected_failures.push_back(INCORRECT_VERSION_LIBRARY);

    failed = HooksManager::validateLibraries(libraries);
    EXPECT_TRUE(failed == expected_failures);
}

// This test verifies that the specified parameters are accessed properly.
TEST_F(HooksManagerTest, LibraryParameters) {

    // Prepare parameters for the callout parameters library.
    ElementPtr params = Element::createMap();
    params->set("svalue", Element::create("string value"));
    params->set("ivalue", Element::create(42));
    params->set("bvalue", Element::create(true));

    // Set up the list of libraries to be loaded.
    HookLibsCollection library_names;
    library_names.push_back(make_pair(std::string(BASIC_CALLOUT_LIBRARY),
                                      data::ConstElementPtr()));
    library_names.push_back(make_pair(std::string(CALLOUT_PARAMS_LIBRARY),
                                      params));

    // Load the libraries. Note that callout params library checks if
    // all mandatory parameters are there, so if anything is missing, its
    // load() function will return error, thus causing the library to not
    // load.
    EXPECT_TRUE(HooksManager::loadLibraries(library_names));

    // Try unloading the libraries.
    EXPECT_NO_THROW(HooksManager::unloadLibraries());
}


} // Anonymous namespace
