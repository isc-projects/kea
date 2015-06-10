// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef BUNDY_D2_CONTROLLER_H
#define BUNDY_D2_CONTROLLER_H

#include <asiolink/io_service.h>
#include <cc/data.h>
#include <cc/session.h>
#include <cc/command_interpreter.h>
#include <d2/d2_log.h>
#include <d2/d_controller.h>
#include <d2/d_process.h>
#include <exceptions/exceptions.h>
#include <log/logger_support.h>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>


namespace isc {
namespace d2 {

/// @brief Exception thrown when the session start up fails.
class SessionStartError: public isc::Exception {
public:
    SessionStartError (const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when the session end fails.
class SessionEndError: public isc::Exception {
public:
    SessionEndError (const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Defines a shared pointer to a Session.
typedef boost::shared_ptr<isc::cc::Session> SessionPtr;

/// @brief Defines a shared pointer to a ModuleCCSession.
typedef boost::shared_ptr<isc::config::ModuleCCSession> ModuleCCSessionPtr;

/// @brief Bundy-integrated Process Controller for D2 Process 
/// This class is the DHCP-DDNS specific derivation of DControllerBase which
/// is managed by BUNDY. It creates and manages an instance of the DHCP-DDNS 
/// application process, D2Process.
///
/// D2 will be constructed with this class if the project is configured with
/// --with-kea-config=BUNDY
class D2Controller : public DControllerBase {
public:
    /// @brief Static singleton instance method. This method returns the
    /// base class singleton instance member.  It instantiates the singleton
    /// and sets the base class instance member upon first invocation.
    ///
    /// @return returns the pointer reference to the singleton instance.
    static DControllerBasePtr& instance();

    /// @brief Destructor.
    virtual ~D2Controller();

    /// @brief Defines the application name, this is passed into base class
    /// and appears in log statements.
    static const char* d2_app_name_;

    /// @brief Defines the executable name. This is passed into the base class
    /// by convention this should match the BUNDY module name.
    static const char* d2_bin_name_;

    /// @brief Acts as the primary entry point into the controller execution
    /// and provides the outermost application control logic:
    ///
    /// 1. parse command line arguments
    /// 2. instantiate and initialize the application process
    /// 3. establish BUNDY session(s) if in integrated mode
    /// 4. start and wait on the application process event loop
    /// 5. upon event loop completion, disconnect from BUNDY (if needed)
    /// 6. exit to the caller
    ///
    /// It is intended to be called from main() and be given the command line
    /// arguments. Note this method is deliberately not virtual to ensure the
    /// proper sequence of events occur.
    ///
    /// This function can be run in the test mode. It prevents initialization
    /// of D2 module logger. This is used in unit tests which initialize logger
    /// in their main function. Such logger uses environmental variables to
    /// control severity, verbosity etc. Reinitialization of logger by this
    /// function would replace unit tests specific logger configuration with
    /// this suitable for D2 running as a Bundy module.
    ///
    /// @param argc  is the number of command line arguments supplied
    /// @param argv  is the array of string (char *) command line arguments
    /// @param test_mode is a bool value which indicates if
    /// @c DControllerBase::launch should be run in the test mode (if true).
    /// This parameter doesn't have default value to force test implementers to
    /// enable test mode explicitly.
    ///
    /// @throw throws one of the following exceptions:
    /// InvalidUsage - Indicates invalid command line.
    /// ProcessInitError  - Failed to create and initialize application
    /// process object.
    /// SessionStartError  - Could not connect to BUNDY (integrated mode only).
    /// ProcessRunError - A fatal error occurred while in the application
    /// process event loop.
    /// SessionEndError - Could not disconnect from BUNDY (integrated mode
    /// only).
    virtual void launch(int argc, char* argv[], const bool test_mode);

    /// @brief A dummy configuration handler that always returns success.
    ///
    /// This configuration handler does not perform configuration
    /// parsing and always returns success. A dummy handler should
    /// be installed using \ref isc::config::ModuleCCSession ctor
    /// to get the initial configuration. This initial configuration
    /// comprises values for only those elements that were modified
    /// the previous session. The D2 configuration parsing can't be
    /// used to parse the initial configuration because it may need the
    /// full configuration to satisfy dependencies between the
    /// various configuration values. Installing the dummy handler
    /// that guarantees to return success causes initial configuration
    /// to be stored for the session being created and that it can
    /// be later accessed with \ref isc::config::ConfigData::getFullConfig.
    ///
    /// @param new_config new configuration.
    ///
    /// @return success configuration status.
    static isc::data::ConstElementPtr
    dummyConfigHandler(isc::data::ConstElementPtr new_config);

    /// @brief A callback for handling all incoming configuration updates.
    ///
    /// As a pointer to this method is used as a callback in ASIO for
    /// ModuleCCSession, it has to be static.  It acts as a wrapper around
    /// the virtual instance method, updateConfig.
    ///
    /// @param new_config textual representation of the new configuration
    ///
    /// @return status of the config update
    static isc::data::ConstElementPtr
    configHandler(isc::data::ConstElementPtr new_config);

    /// @brief A callback for handling all incoming commands.
    ///
    /// As a pointer to this method is used as a callback in ASIO for
    /// ModuleCCSession, it has to be static.  It acts as a wrapper around
    /// the virtual instance method, executeCommand.
    ///
    /// @param command textual representation of the command
    /// @param args parameters of the command. It can be NULL pointer if no
    /// arguments exist for a particular command.
    ///
    /// @return status of the processed command
    static isc::data::ConstElementPtr
    commandHandler(const std::string& command, isc::data::ConstElementPtr args);

    /// @brief Instance method invoked by the configuration event handler and
    /// which processes the actual configuration update.  Provides behavioral
    /// path for both integrated and stand-alone modes. The current
    /// implementation will merge the configuration update into the existing
    /// configuration and then invoke the application process' configure method.
    ///
    /// @todo This implementation is will evolve as the D2 configuration
    /// management task is implemented (trac #2957).
    ///
    /// @param  new_config is the new configuration
    ///
    /// @return returns an Element that contains the results of configuration
    /// update composed of an integer status value (0 means successful,
    /// non-zero means failure), and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr
    updateConfig(isc::data::ConstElementPtr new_config);

protected:
    /// @brief Processes the command line arguments. It is the first step
    /// taken after the controller has been launched.  It combines the stock
    /// list of options with those returned by getCustomOpts(), and uses
    /// cstdlib's getopt to loop through the command line.  The stock options
    /// It handles stock options directly, and passes any custom options into
    /// the customOption method.  Currently there are only two stock options
    /// -s for stand alone mode, and -v for verbose logging.
    ///
    /// @param argc  is the number of command line arguments supplied
    /// @param argv  is the array of string (char *) command line arguments
    ///
    /// @throw throws InvalidUsage when there are usage errors.
    void parseArgs(int argc, char* argv[]);

    /// @brief Establishes connectivity with BUNDY.  This method is used
    /// invoked during launch, if running in integrated mode, following
    /// successful process initialization.  It is responsible for establishing
    /// the BUNDY control and config sessions. During the session creation,
    /// it passes in the controller's IOService and the callbacks for command
    /// directives and config events.  Lastly, it will invoke the onConnect
    /// method providing the derivation an opportunity to execute any custom
    /// logic associated with session establishment.
    ///
    /// @throw the BUNDY framework may throw std::exceptions.
    void establishSession();

    /// @brief Terminates connectivity with BUNDY. This method is invoked
    /// in integrated mode after the application event loop has exited. It
    /// first calls the onDisconnect method providing the derivation an
    /// opportunity to execute custom logic if needed, and then terminates the
    /// BUNDY config and control sessions.
    ///
    /// @throw the BUNDY framework may throw std:exceptions.
    void disconnectSession();

    /// @brief Prints the program usage text to std error.
    ///
    /// @param text is a string message which will preceded the usage text.
    /// This is intended to be used for specific usage violation messages.
    void usage(const std::string& text);

private:
    /// @brief Creates an instance of the DHCP-DDNS specific application
    /// process.  This method is invoked during the process initialization
    /// step of the controller launch.
    ///
    /// @return returns a DProcessBase* to the application process created.
    /// Note the caller is responsible for destructing the process. This
    /// is handled by the base class, which wraps this pointer with a smart
    /// pointer.
    virtual DProcessBase* createProcess();

    /// @brief Helper session object that represents raw connection to msgq.
    SessionPtr cc_session_;

    /// @brief Session that receives configuration and commands.
    ModuleCCSessionPtr config_session_;

    /// @brief Constructor is declared private to maintain the integrity of
    /// the singleton instance.
    D2Controller();

    // DControllerTest is named a friend class to facilitate unit testing while
    // leaving the intended member scopes intact.
    friend class DControllerTest;
};

}; // namespace isc::d2
}; // namespace isc

#endif
