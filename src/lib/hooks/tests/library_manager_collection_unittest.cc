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

/// @brief Library manager collection test class

class LibraryManagerCollectionTest : public ::testing::Test,
                                     public HooksCommonTestClass {
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
    EXPECT_EQ(2, lm_collection.getLoadedLibraryCount());

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
    boost::shared_ptr<CalloutManager> manager =
                                      lm_collection.getCalloutManager();
    {
        SCOPED_TRACE("Doing calculation with libraries loaded");
        executeCallCallouts(manager, 10, 3, 33, 2, 62, 3, 183);
    }

    // Try unloading the libraries.
    EXPECT_NO_THROW(lm_collection.unloadLibraries());
    EXPECT_EQ(0, lm_collection.getLoadedLibraryCount());

    // Re-execute the calculation - callouts can be called but as nothing
    // happens, the result should always be -1.
    {
        SCOPED_TRACE("Doing calculation with libraries not loaded");
        executeCallCallouts(manager, -1, 3, -1, 22, -1, 83, -1);
    }
}

// This is effectively the same test as above, but with a library generating
// an error when loaded. It is expected that no libraries will be loaded.

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

    // Expect no libraries were loaded.
    EXPECT_EQ(0, lm_collection.getLoadedLibraryCount());
}

// Check that everything works even with no libraries loaded.

TEST_F(LibraryManagerCollectionTest, NoLibrariesLoaded) {
    // Set up the list of libraries to be loaded.
    std::vector<std::string> library_names;

    // Set up the library manager collection and get the callout manager we'll
    // be using.
    LibraryManagerCollection lm_collection(library_names);
    EXPECT_TRUE(lm_collection.loadLibraries());
    EXPECT_EQ(0, lm_collection.getLoadedLibraryCount());
    boost::shared_ptr<CalloutManager> manager =
                                      lm_collection.getCalloutManager();

    // Eecute the calculation - callouts can be called but as nothing
    // happens, the result should always be -1.
    executeCallCallouts(manager, -1, 3, -1, 22, -1, 83, -1);
}

// Check that we can get the names of the libraries.

TEST_F(LibraryManagerCollectionTest, LibraryNames) {

    // Set up the list of libraries to be loaded.
    std::vector<std::string> library_names;
    library_names.push_back(std::string(FULL_CALLOUT_LIBRARY));
    library_names.push_back(std::string(BASIC_CALLOUT_LIBRARY));

    // Set up the library manager collection and get the callout manager we'll
    // be using.
    PublicLibraryManagerCollection lm_collection(library_names);

    // Check the names before the libraries are loaded.
    std::vector<std::string> collection_names = lm_collection.getLibraryNames();
    EXPECT_TRUE(library_names == collection_names);

    // Load the libraries and check the names again.
    EXPECT_TRUE(lm_collection.loadLibraries());
    EXPECT_EQ(2, lm_collection.getLoadedLibraryCount());
    collection_names = lm_collection.getLibraryNames();
    EXPECT_TRUE(library_names == collection_names);
}

// Test the library validation function.

TEST_F(LibraryManagerCollectionTest, validateLibraries) {
    const std::string empty;
    const std::string separator(", ");

    // Test different vectors of libraries.

    // No libraries should return a success.
    std::vector<std::string> libraries;
    EXPECT_EQ(empty, LibraryManagerCollection::validateLibraries(libraries));

    // Single valid library should validate.
    libraries.clear();
    libraries.push_back(BASIC_CALLOUT_LIBRARY);
    EXPECT_EQ(empty, LibraryManagerCollection::validateLibraries(libraries));

    // Multiple valid libraries should succeed.
    libraries.clear();
    libraries.push_back(BASIC_CALLOUT_LIBRARY);
    libraries.push_back(FULL_CALLOUT_LIBRARY);
    libraries.push_back(UNLOAD_CALLOUT_LIBRARY);
    EXPECT_EQ(empty, LibraryManagerCollection::validateLibraries(libraries));

    // Single invalid library should fail.
    libraries.clear();
    libraries.push_back(NOT_PRESENT_LIBRARY);
    EXPECT_EQ(std::string(NOT_PRESENT_LIBRARY),
              LibraryManagerCollection::validateLibraries(libraries));

    // Multiple invalid libraries should fail.
    libraries.clear();
    libraries.push_back(INCORRECT_VERSION_LIBRARY);
    libraries.push_back(NO_VERSION_LIBRARY);
    libraries.push_back(FRAMEWORK_EXCEPTION_LIBRARY);
    std::string expected = std::string(INCORRECT_VERSION_LIBRARY) + separator +
                           std::string(NO_VERSION_LIBRARY) + separator +
                           std::string(FRAMEWORK_EXCEPTION_LIBRARY);
    EXPECT_EQ(expected, LibraryManagerCollection::validateLibraries(libraries));

    // Combination of valid and invalid (first one valid) should fail.
    libraries.clear();
    libraries.push_back(FULL_CALLOUT_LIBRARY);
    libraries.push_back(INCORRECT_VERSION_LIBRARY);
    libraries.push_back(NO_VERSION_LIBRARY);

    expected = std::string(INCORRECT_VERSION_LIBRARY) + separator +
               std::string(NO_VERSION_LIBRARY);
    EXPECT_EQ(expected, LibraryManagerCollection::validateLibraries(libraries));

    // Combination of valid and invalid (first one invalid) should fail.
    libraries.clear();
    libraries.push_back(NO_VERSION_LIBRARY);
    libraries.push_back(FULL_CALLOUT_LIBRARY);
    libraries.push_back(INCORRECT_VERSION_LIBRARY);

    expected = std::string(NO_VERSION_LIBRARY) + separator +
               std::string(INCORRECT_VERSION_LIBRARY);
    EXPECT_EQ(expected, LibraryManagerCollection::validateLibraries(libraries));
}

} // Anonymous namespace
