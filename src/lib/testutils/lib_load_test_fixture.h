// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TESTUTILS_LIB_LOAD_TEST_FIXTURE_H
#define ISC_TESTUTILS_LIB_LOAD_TEST_FIXTURE_H

#include <cc/data.h>

#include <gtest/gtest.h>

namespace isc {
namespace test {

/// @brief Test fixture for testing loading and unloading of hook libraries.
struct LibLoadTest : ::testing::Test {
    /// @brief Constructor. Unloads any previously loaded libraries.
    LibLoadTest() {
        unloadLibraries();
    }

    /// @brief Destructor. Unloads any previously loaded libraries.
    ~LibLoadTest() {
        unloadLibraries();
    }

    /// @brief Adds a library along with its parameters to the list of libraries to be loaded.
    ///
    /// @param library the path to the library to be loaded
    /// @param parameters the library's parameters in Element format
    void addLibrary(const std::string& library, isc::data::ConstElementPtr parameters) {
        libraries_.push_back({library, parameters});
    }

    void clearLibraries() {
        libraries_.clear();
    }

    /// @brief Load all libraries.
    ///
    /// @return true if all libraries loaded successfully, false if one or more
    ///     libraries failed to load.
    bool loadLibraries() {
        bool result(false);
        EXPECT_NO_THROW(result = isc::hooks::HooksManager::loadLibraries(libraries_));
        return result;
    }

    /// @brief Unloads all libraries.
    ///
    /// @return true if all libraries unloaded successfully, false if they
    ///     are still in memory.
    bool unloadLibraries() {
        bool result(false);
        EXPECT_NO_THROW(result = isc::hooks::HooksManager::unloadLibraries());
        return result;
    }

    /// @brief Libraries
    isc::hooks::HookLibsCollection libraries_;
};

}  // namespace test
}  // namespace isc

#endif  // ISC_TESTUTILS_LIB_LOAD_TEST_FIXTURE_H
