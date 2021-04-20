// Copyright (C) 2016-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CTRL_AGENT_PROCESS_H
#define CTRL_AGENT_PROCESS_H

#include <agent/ca_cfg_mgr.h>
#include <http/listener.h>
#include <process/d_process.h>
#include <vector>

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
    /// A usual problem related to the system reconfiguration is how to preserve
    /// configuration integrity in case of errors. In this case, when the
    /// HTTP listener's configuration is modified there is a need to close all
    /// existing connections and gracefully shutdown the listener's instance.
    /// This, however, makes it possible that the control agent looses
    /// connectivity if opening a new listener is unsuccessful. In fact, this
    /// is quite possible scenario when the user is setting up the listener to
    /// use a restricted port range or non-existing IP address. In this case,
    /// the configuration parser will not signal the problem because IP address
    /// and/or port are syntactically correct.
    ///
    /// This method deals with this problem by opening a new listener aside of
    /// the currently running listener (if the new listener settings are
    /// different than current settings). Both instances are held until the
    /// CtrlAgentProcess::garbageCollectListeners is invoked, which
    /// removes any listeners which are no longer used.
    ///
    /// @param config_set a new configuration (JSON) for the process
    /// @param check_only true if configuration is to be verified only, not applied
    /// @return an Element that contains the results of configuration composed
    /// of an integer status value (0 means successful, non-zero means failure),
    /// and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr
    configure(isc::data::ConstElementPtr config_set,
              bool check_only = false);

    /// @brief Returns a pointer to the configuration manager.
    CtrlAgentCfgMgrPtr getCtrlAgentCfgMgr();

    /// @brief Returns a const pointer to the HTTP listener used by the process.
    ///
    /// @return Const pointer to the currently used listener or null pointer if
    /// we're not listening. In fact, the latter should never be the case given
    /// that we provide default listener configuration.
    http::ConstHttpListenerPtr getHttpListener() const;

    /// @brief Checks if the process is listening to the HTTP requests.
    ///
    /// @return true if the process is listening.
    bool isListening() const;

private:

    /// @brief Removes listeners which are no longer in use.
    ///
    /// This method should be called after executing
    /// @ref CtrlAgentProcess::configure to remove listeners used previously
    /// (no longer used because the listening address and port has changed as
    // a result of the reconfiguration). If there are no listeners additional
    /// to the one that is currently in use, the method has no effect.
    /// This method is reused to remove all listeners at shutdown time.
    ///
    /// @param leaving The number of listener to leave (default one).
    void garbageCollectListeners(size_t leaving = 1);

    /// @brief Polls all ready handlers and then runs one handler if none
    /// handlers have been executed as a result of polling.
    ///
    /// @return Number of executed handlers.
    size_t runIO();

    /// @brief Holds a list of pointers to the active listeners.
    std::vector<http::HttpListenerPtr> http_listeners_;

};

/// @brief Defines a shared pointer to CtrlAgentProcess.
typedef boost::shared_ptr<CtrlAgentProcess> CtrlAgentProcessPtr;

}; // namespace isc::agent
}; // namespace isc

#endif // CTRL_AGENT_PROCESS_H
