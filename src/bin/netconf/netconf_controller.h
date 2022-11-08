// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NETCONF_CONTROLLER_H
#define NETCONF_CONTROLLER_H

#include <netconf/netconf_process.h>
#include <process/d_controller.h>

namespace isc {
namespace netconf {

/// @brief Process Controller for Netconf Process.
///
/// This class is the Netconf specific derivation of the DControllerBase.
/// It creates and manages an instance of the Netconf application process,
/// NetconfProcess.
class NetconfController : public process::DControllerBase {
public:

    /// @brief Static singleton instance method.
    ///
    /// This method returns the base class singleton instance member.
    /// It instantiates the singleton and sets the base class instance
    /// member upon first invocation.
    ///
    /// @return returns the pointer reference to the singleton instance.
    static process::DControllerBasePtr& instance();

    /// @brief Destructor
    virtual ~NetconfController() = default;

    /// @brief Returns pointer to an instance of the underlying process object.
    NetconfProcessPtr getNetconfProcess();

    /// @brief Defines the application name, this is passed into base class
    /// and appears in log statements.
    static const char* netconf_app_name_;

    /// @brief Defines the executable name. This is passed into the base class
    /// by convention this should match the executable name.
    static const char* netconf_bin_name_;

    /// @brief Parses the configuration file using Netconf::ParserContext (bison)
    ///
    /// @param name name of the text file to be parsed
    /// @return Element tree structure representing parsed configuration
    isc::data::ConstElementPtr
    parseFile(const std::string& name) override final;

    /// @brief Redefined application-level signal processing method.
    ///
    /// This method ignores SIGHUP as configuration reloading is not yet
    /// supported.
    /// @param signum signal number to process.
    void processSignal(int signum) override final;

private:

    /// @brief Creates an instance of the Netconf application process.
    ///
    /// This method is invoked during the process initialization step of
    /// the controller launch.
    ///
    /// @return returns a DProcessBase* to the application process created.
    /// Note the caller is responsible for destructing the process. This
    /// is handled by the base class, which wraps this pointer with a smart
    /// pointer.
    process::DProcessBase* createProcess() override final;

    /// @brief Constructor is declared private to maintain the integrity of
    /// the singleton instance.
    NetconfController();
};  // NetconfController

// @Defines a shared pointer to NetconfController
using NetconfControllerPtr = std::shared_ptr<NetconfController>;

}  // namespace netconf
}  // namespace isc

#endif  // NETCONF_CONTROLLER_H
