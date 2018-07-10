// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SLAAC_AGENT_CONTROLLER_H
#define SLAAC_AGENT_CONTROLLER_H

#include <slaac/slaac_process.h>
#include <process/d_controller.h>

namespace isc {
namespace slaac {

/// @brief Process Controller for Control Agent Process.
///
/// This class is the Control Agent specific derivation of the DControllerBase.
/// It creates and manages an instance of the Control Agent application process,
/// SlaacAgentProcess.
class SlaacController : public process::DControllerBase {
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
    virtual ~SlaacController();

    /// @brief Returns pointer to an instance of the underlying process object.
    SlaacProcessPtr getSlaacProcess();

    /// @brief Defines the application name, this is passed into base class
    /// and appears in log statements.
    static const char* _app_name_;

    /// @brief Defines the executable name. This is passed into the base class
    /// by convention this should match the executable name.
    static const char* _bin_name_;

    /// @brief Parses the configuration file using ::ParserContext (bison)
    ///
    /// @param name name of the text file to be parsed
    /// @return Element tree structure representing parsed configuration
    isc::data::ConstElementPtr
    parseFile(const std::string& name);

    /// @brief Register commands.
    void registerCommands();

    /// @brief Deregister commands.
    void deregisterCommands();

private:

    /// @brief Creates an instance of the Control  application
    /// process.
    ///
    /// This method is invoked during the process initialization step of
    /// the controller launch.
    ///
    /// @return returns a DProcessBase* to the application process created.
    /// Note the caller is responsible for destructing the process. This
    /// is handled by the base class, which wraps this pointer with a smart
    /// pointer.
    virtual process::DProcessBase* createProcess();

    /// @brief Constructor is declared private to maintain the integrity of
    /// the singleton instance.
    SlaacController();
};

// @Defines a shared pointer to SlaacController
typedef boost::shared_ptr<SlaacController> SlaacControllerPtr;

} // namespace isc::slaac
} // namespace isc

#endif // SLAAC_CONTROLLER_H
