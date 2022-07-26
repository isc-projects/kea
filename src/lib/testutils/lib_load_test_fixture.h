// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TESTUTILS_LIB_LOAD_TEST_FIXTURE_H
#define ISC_TESTUTILS_LIB_LOAD_TEST_FIXTURE_H

#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <process/daemon.h>

#include <gtest/gtest.h>

namespace isc {
namespace test {

/// @brief Test fixture for testing loading and unloading of hook libraries.
class LibLoadTest : public ::testing::Test {
public:
    /// @brief Constructor. Unloads any previously loaded libraries.
    ///
    /// @param lib_so_name_ full pathname to the library so file under test
    LibLoadTest(const std::string lib_so_name = "no-lib-specified")
        : lib_so_name_(lib_so_name) {
        unloadLibraries();
    }

    /// @brief Destructor. Unloads any previously loaded libraries.
    ~LibLoadTest() {
        unloadLibraries();
    }

    /// @brief Adds a library along with its parameters to the list of
    /// libraries to be loaded.
    ///
    /// @param library the path to the library to be loaded
    /// @param parameters the library's parameters in Element format
    void addLibrary(const std::string& library,
                    isc::data::ConstElementPtr parameters) {
        libraries_.push_back({library, parameters});
    }

    void clearLibraries() {
        libraries_.clear();
    }

    /// @brief Load all libraries.
    ///
    /// @return true if all libraries loaded successfully, false if one or more
    /// libraries failed to load.
    bool loadLibraries() {
        bool result(false);
        EXPECT_NO_THROW(result = isc::hooks::HooksManager::loadLibraries(libraries_));
        return result;
    }

    /// @brief Unloads all libraries.
    ///
    /// @return true if all libraries unloaded successfully, false if they
    /// are still in memory.
    bool unloadLibraries() {
        bool result(false);
        EXPECT_NO_THROW(result = isc::hooks::HooksManager::unloadLibraries());
        return result;
    }

    /// @brief Verifies that a valid daemon can load and unload a
    /// library multiple times.
    ///
    /// @param daemon_name name of the daemon that should try to load the library
    /// @param family Protocol family of the loading daemon, either
    /// AF_INET or AF_INET6. Defaults to AF_INET.
    /// @param params ElementPtr to set of parameters that are valid for the library.
    /// Defaults to an empty pointer.
    void validDaemonTest(const std::string& daemon_name,
                         uint16_t family = AF_INET,
                         const isc::data::ElementPtr& params = isc::data::ElementPtr());

    /// @brief Verifies that an invalid daemon cannot load the library.
    ///
    /// @param libname full path to the library's SO. Typically this
    /// value is defined in the Makefile (e.g. -DLIBDHCP_BOOTP_SO=...)
    /// @param daemon_name name of the daemon that should try to load the library
    /// @param family Protocol family of the loading daemon, either
    /// AF_INET or AF_INET6. Defaults to AF_INET.
    /// @param params ElementPtr to set of parameters that are valid
    /// for the library. Defaults to an empty pointer.
    void invalidDaemonTest(const std::string& daemon_name,
                           uint16_t family = AF_INET,
                           const isc::data::ElementPtr& params = isc::data::ElementPtr());

    /// @brief full pathname to the library so file under test;
    std::string lib_so_name_;

    /// @brief Libraries
    isc::hooks::HookLibsCollection libraries_;
};

}  // namespace test
}  // namespace isc

#endif // ISC_TESTUTILS_LIB_LOAD_TEST_FIXTURE_H
