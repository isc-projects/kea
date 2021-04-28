// Copyright (C) 2019-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the flexible option hook library. In order to test the load
/// function, one must be able to pass it hook library parameters. The
/// the only way to populate these parameters is by actually loading the
/// library via HooksManager::loadLibraries().

#include <config.h>

#include <cc/data.h>
#include <hooks/hooks_manager.h>

#include <gtest/gtest.h>
#include <errno.h>

using namespace std;
using namespace isc;
using namespace isc::hooks;
using namespace isc::data;

namespace {

/// @brief Test fixture for testing loading and unloading the RunScript library.
class LibLoadTest : public ::testing::Test {
public:
    /// @brief Constructor
    LibLoadTest() {
        reset();
    }

    /// @brief Destructor
    ///
    /// Removes files that may be left over from previous tests
    virtual ~LibLoadTest() {
        reset();
    }

    /// @brief Removes files that may be left over from previous tests
    virtual void reset() {
        HooksManager::unloadLibraries();
    }

    /// @brief Add library to the collection of tested libraries.
    ///
    /// @param lib The name of the lib added.
    /// @param params The parameters of the library.
    void addLib(const string& lib, ConstElementPtr params) {
        libraries_.push_back(make_pair(lib, params));
    }

    /// @brief Load libraries.
    ///
    /// @return True if loading succeeded, false otherwise.
    bool loadLibs() {
        return (HooksManager::loadLibraries(libraries_));
    }

    /// @brief Unload libraries.
    ///
    /// @return True if unloading succeeded, false otherwise.
    bool unloadLibs() {
        return (HooksManager::unloadLibraries());
    }

    /// @brief The collection of libraries to be loaded.
    HookLibsCollection libraries_;
};

// Simple test that checks the library can be loaded and unloaded several times.
TEST_F(LibLoadTest, validLoad) {
    // Prepare parameters for the callout parameters library.
    ElementPtr params = Element::createMap();
    ElementPtr name = Element::create(RUN_SCRIPT_TEST_SH);
    params->set("name", name);
    ElementPtr sync = Element::create(false);
    params->set("sync", sync);

    addLib(LIBRUN_SCRIPT_SO, params);

    EXPECT_TRUE(loadLibs());
    EXPECT_NO_THROW(unloadLibs());

    EXPECT_TRUE(loadLibs());
    EXPECT_NO_THROW(unloadLibs());
}

// Simple test that checks the library can not be loaded if using wrong
// parameters.
TEST_F(LibLoadTest, invalidLoad) {
    // Prepare parameters for the callout parameters library.
    ElementPtr params = Element::createMap();
    addLib(LIBRUN_SCRIPT_SO, params);

    // The name parameter is mandatory.
    EXPECT_FALSE(loadLibs());

    // Use invalid name parameter type.
    ElementPtr name = Element::create(false);
    params->set("name", name);
    EXPECT_FALSE(loadLibs());

    // Use invalid name parameter.
    name = Element::create("script_name.sh");
    params->set("name", name);
    EXPECT_FALSE(loadLibs());

    // Use valid name parameter type but use invalid sync parameter type.
    name = Element::create(RUN_SCRIPT_TEST_SH);
    params->set("name", name);
    ElementPtr sync = Element::create("data");
    params->set("sync", sync);
    EXPECT_FALSE(loadLibs());
}

} // end of anonymous namespace
