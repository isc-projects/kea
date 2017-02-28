// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CTRL_AGENT_PROCESS_H
#define CTRL_AGENT_PROCESS_H

#include <agent/ca_cfg_mgr.h>
#include <process/d_process.h>

namespace isc {
namespace agent {

/// @brief Kea Control Agent Application Process
///
/// CtrlAgentProcess provides top level application logic for the Control
/// Agent, a process managing Kea servers.
///
/// The Control Agent receives JSON control commands over HTTP and forwards
/// the JSON commands to the respective Kea servers. The JSON command
/// includes a name of the server to which the command pertains. After
/// receiving a response from the Kea server it is sent back over HTTP
/// to the control API client.
///
/// Some commands are handled by the Control Agent process itself, rather than
/// forwarded to the Kea servers. An example of such command is the one that
/// instructs the agent to start a specific service.
class CtrlAgentProcess : public process::DProcessBase {
public:
    /// @brief Constructor
    ///
    /// @param name name is a text label for the process. Generally used
    /// in log statements, but otherwise arbitrary.
    /// @param io_service is the io_service used by the caller for
    /// asynchronous event handling.
    CtrlAgentProcess(const char* name, const asiolink::IOServicePtr& io_service);

    /// @brief Destructor
    virtual ~CtrlAgentProcess();

    /// @brief Initialize the Control Agent process.
    ///
    /// This is invoked by the controller after command line arguments but
    /// prior to configuration reception. The base class provides this method
    /// as a place to perform any derivation-specific initialization steps
    /// that are inappropriate for the constructor but necessary prior to
    /// launch.
    virtual void init();

    /// @brief Implements the process's event loop.
    ///
    /// @throw DProcessBaseError if an operational error is encountered.
    virtual void run();

    /// @brief Initiates the process's shutdown process.
    ///
    /// This is last step in the shutdown event callback chain, that is
    /// intended to notify the process it is to begin its shutdown process.
    ///
    /// @param args an Element set of shutdown arguments (if any) that are
    /// supported by the process derivation.
    ///
    /// @return an Element that contains the results of argument processing,
    /// consisting of an integer status value (0 means successful,
    /// non-zero means failure), and a string explanation of the outcome.
    ///
    /// @throw DProcessBaseError if an operational error is encountered.
    virtual isc::data::ConstElementPtr
    shutdown(isc::data::ConstElementPtr args);

    /// @brief Processes the given configuration.
    ///
    /// This method may be called multiple times during the process lifetime.
    /// Certainly once during process startup, and possibly later if the user
    /// alters configuration. This method must not throw, it should catch any
    /// processing errors and return a success or failure answer as described
    /// below.
    ///
    /// @param config_set a new configuration (JSON) for the process
    /// @return an Element that contains the results of configuration composed
    /// of an integer status value (0 means successful, non-zero means failure),
    /// and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr
    configure(isc::data::ConstElementPtr config_set);

    /// @brief Processes the given command.
    ///
    /// This method is called to execute any custom commands supported by the
    /// process. This method must not throw, it should catch any processing
    /// errors and return a success or failure answer as described below.
    ///
    /// @param command is a string label representing the command to execute.
    /// @param args is a set of arguments (if any) required for the given
    /// command.
    /// @return an Element that contains the results of command composed
    /// of an integer status value:
    ///
    /// - COMMAND_SUCCESS indicates a command was successful.
    /// - COMMAND_ERROR indicates a valid command failed execute.
    /// - COMMAND_INVALID indicates a command is not valid.
    ///
    /// and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr
    command(const std::string& command, isc::data::ConstElementPtr args);

    /// @brief Returns a pointer to the configuration manager.
    CtrlAgentCfgMgrPtr getCtrlAgentCfgMgr();
};

/// @brief Defines a shared pointer to CtrlAgentProcess.
typedef boost::shared_ptr<CtrlAgentProcess> CtrlAgentProcessPtr;

}; // namespace isc::agent
}; // namespace isc

#endif // CTRL_AGENT_PROCESS_H
