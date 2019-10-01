// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
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

#include <flex_option.h>
#include <hooks/hooks_manager.h>

#include <gtest/gtest.h>
#include <errno.h>

using namespace std;
using namespace isc;
using namespace isc::hooks;
using namespace isc::data;
using namespace isc::dhcp;

namespace {

/// @brief Test fixture for testing loading and unloading the flex-option library
class LibLoadTest : public ::testing::Test {
public:
    /// @brief Constructor
    LibLoadTest() {
        reset();
    }

    /// @brief Destructor
    /// Removes files that may be left over from previous tests
    virtual ~LibLoadTest() {
        reset();
    }

    /// @brief Removes files that may be left over from previous tests
    virtual void reset() {
        HooksManager::unloadLibraries();
    }

    void addLib(const std::string& lib, ConstElementPtr params) {
        libraries_.push_back(make_pair(lib, params));
    }

    void loadLibs() {
        EXPECT_TRUE(HooksManager::loadLibraries(libraries_));
    }

    void unloadLibs() {
        EXPECT_NO_THROW(HooksManager::unloadLibraries());
    }

    HookLibsCollection libraries_;
};

// Simple test that checks the library can be loaded and unloaded several times.
TEST_F(LibLoadTest, validLoad) {

    // Prepare parameters for the callout parameters library.
    ElementPtr params = Element::createMap();
    ElementPtr options = Element::createList();
    params->set("options", options);

    addLib(FLEX_OPTION_LIB_SO, params);

    loadLibs();
    unloadLibs();

    loadLibs();
    unloadLibs();
}

} // end of anonymous namespace
