// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SLAAC_PROCESS_H
#define SLAAC_PROCESS_H

#include <slaac/slaac_cfg_mgr.h>
#include <process/d_process.h>
#include <vector>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <boost/asio/ip/address_v6.hpp>


namespace isc {
namespace slaac {

class RequestHandler
{
public:
    RequestHandler(boost::asio::io_service& io_service,
                   const SlaacCfgMgrPtr& cfg_mgr);
    void start_receiving();
    void handle_receive(const boost::system::error_code &err_code, std::size_t size);
    boost::asio::streambuf buffer_;
    boost::asio::ip::icmp::socket socket_;
    boost::asio::ip::icmp::endpoint endpoint_;

    const SlaacCfgMgrPtr& cfg_mgr_;
};

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
class SlaacProcess : public process::DProcessBase {
public:
    /// @brief Constructor
    ///
    /// @param name name is a text label for the process. Generally used
    /// in log statements, but otherwise arbitrary.
    /// @param io_service is the io_service used by the caller for
    /// asynchronous event handling.
    SlaacProcess(const char* name, const asiolink::IOServicePtr& io_service);

    /// @brief Destructor
    virtual ~SlaacProcess();

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
    /// SlaacProcess::garbageCollectListeners is invoked, which
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
    SlaacCfgMgrPtr getSlaacCfgMgr();

    /// @brief Polls all ready handlers and then runs one handler if none
    /// handlers have been executed as a result of polling.
    ///
    /// @return Number of executed handlers.
    size_t runIO();

    /// @brief Checks if the process is listening to the HTTP requests.
    ///
    /// @return true if the process is listening.
    bool isListening() const;

private:

    RequestHandler req_hdlr_;

};

/// @brief Defines a shared pointer to SlaacProcess.
typedef boost::shared_ptr<SlaacProcess> SlaacProcessPtr;

}; // namespace isc::agent
}; // namespace isc

#endif // CTRL_AGENT_PROCESS_H
