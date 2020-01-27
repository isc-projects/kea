// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NETCONF_PROCESS_H
#define NETCONF_PROCESS_H

#include <netconf/netconf.h>
#include <process/d_process.h>
#include <vector>
#include <atomic>

namespace isc {
namespace netconf {

/// @brief Kea Netconf Application Process
///
/// NetconfProcess provides top level application logic for the Netconf,
/// a process managing Kea servers using YANG / NETCONF.
///
/// The Netconf receives YANG configuration change events, converts them
/// to JSON commands sent to the respective Kea servers.
class NetconfProcess : public process::DProcessBase {
public:
    /// @brief Constructor
    ///
    /// @param name name is a text label for the process. Generally used
    /// in log statements, but otherwise arbitrary.
    /// @param io_service is the io_service used by the caller for
    /// asynchronous event handling.
    NetconfProcess(const char* name, const asiolink::IOServicePtr& io_service);

    /// @brief Destructor
    virtual ~NetconfProcess();

    /// @brief Initialize the Netconf process.
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
    /// @param check_only true if configuration is to be verified only, not applied
    /// @return an Element that contains the results of configuration composed
    /// of an integer status value (0 means successful, non-zero means failure),
    /// and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr
    configure(isc::data::ConstElementPtr config_set,
              bool check_only = false);

    /// @brief Returns a pointer to the configuration manager.
    NetconfCfgMgrPtr getNetconfCfgMgr();

    /// @brief Global (globally visible) shutdown flag.
    static std::atomic<bool> shut_down;

private:

    /// @brief Polls all ready handlers and then runs one handler if none
    /// handlers have been executed as a result of polling.
    ///
    /// @return Number of executed handlers.
    size_t runIO();

    /// @brief Netconf agent.
    NetconfAgent agent_;
};

/// @brief Defines a shared pointer to NetconfProcess.
typedef boost::shared_ptr<NetconfProcess> NetconfProcessPtr;

}; // namespace isc::netconf
}; // namespace isc

#endif // NETCONF_PROCESS_H
