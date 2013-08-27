// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef D_CONTROLLER_H
#define D_CONTROLLER_H

#include <asiolink/asiolink.h>
#include <cc/data.h>
#include <cc/session.h>
#include <config/ccsession.h>
#include <d2/d2_log.h>
#include <d2/d_process.h>
#include <exceptions/exceptions.h>
#include <log/logger_support.h>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>


namespace isc {
namespace d2 {

/// @brief DControllerBase launch exit status values.  Upon service shutdown
/// normal or otherwise, the Controller's launch method will return one of
/// these values.

/// @brief Exception thrown when the command line is invalid.
class InvalidUsage : public isc::Exception {
public:
    InvalidUsage(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when the application process fails.
class ProcessInitError: public isc::Exception {
public:
    ProcessInitError (const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when the session start up fails.
class SessionStartError: public isc::Exception {
public:
    SessionStartError (const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when the application process encounters an
/// operation in its event loop (i.e. run method).
class ProcessRunError: public isc::Exception {
public:
    ProcessRunError (const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when the session end fails.
class SessionEndError: public isc::Exception {
public:
    SessionEndError (const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};


/// @brief Exception thrown when the controller encounters an operational error.
class DControllerBaseError : public isc::Exception {
public:
    DControllerBaseError (const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};


/// @brief Defines a shared pointer to DControllerBase.
class DControllerBase;
typedef boost::shared_ptr<DControllerBase> DControllerBasePtr;

/// @brief Defines a shared pointer to a Session.
typedef boost::shared_ptr<isc::cc::Session> SessionPtr;

/// @brief Defines a shared pointer to a ModuleCCSession.
typedef boost::shared_ptr<isc::config::ModuleCCSession> ModuleCCSessionPtr;


/// @brief Application Controller
///
/// DControllerBase is an abstract singleton which provides the framework and
/// services for managing an application process that implements the
/// DProcessBase interface.  It allows the process to run either in
/// integrated mode as a BIND10 module or stand-alone. It coordinates command
/// line argument parsing, process instantiation and initialization, and runtime
/// control through external command and configuration event handling.
/// It creates the IOService instance which is used for runtime control
/// events and passes the IOService into the application process at process
/// creation.  In integrated mode it is responsible for establishing BIND10
/// session(s) and passes this IOService into the session creation method(s).
/// It also provides the callback handlers for command and configuration events
/// received from the external framework (aka BIND10).  For example, when
/// running in integrated mode and a user alters the configuration with the
/// bindctl tool, BIND10 will emit a configuration message which is sensed by
/// the controller's IOService. The IOService in turn invokes the configuration
/// callback, DControllerBase::configHandler().  If the user issues a command
/// such as shutdown via bindctl,  BIND10 will emit a command message, which is
/// sensed by controller's IOService which invokes the command callback,
/// DControllerBase::commandHandler().
///
/// NOTE: Derivations must supply their own static singleton instance method(s)
/// for creating and fetching the instance. The base class declares the instance
/// member in order for it to be available for BIND10 callback functions. This
/// would not be required if BIND10 supported instance method callbacks.
class DControllerBase : public boost::noncopyable {
public:
    /// @brief Constructor
    ///
    /// @param app_name is display name of the application under control. This
    /// name appears in log statements.
    /// @param bin_name is the name of the application executable. Typically
    /// this matches the BIND10 module name.
    DControllerBase(const char* app_name, const char* bin_name);

    /// @brief Destructor
    virtual ~DControllerBase();

    /// @brief Acts as the primary entry point into the controller execution
    /// and provides the outermost application control logic:
    ///
    /// 1. parse command line arguments
    /// 2. instantiate and initialize the application process
    /// 3. establish BIND10 session(s) if in integrated mode
    /// 4. start and wait on the application process event loop
    /// 5. upon event loop completion, disconnect from BIND10 (if needed)
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
    /// this suitable for D2 running as a bind10 module.
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
    /// SessionStartError  - Could not connect to BIND10 (integrated mode only).
    /// ProcessRunError - A fatal error occurred while in the application
    /// process event loop.
    /// SessionEndError - Could not disconnect from BIND10 (integrated mode
    /// only).
    void launch(int argc, char* argv[], const bool test_mode);

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


    /// @brief Instance method invoked by the command event handler and  which
    /// processes the actual command directive.
    ///
    /// It supports the execution of:
    ///
    ///   1. Stock controller commands - commands common to all DControllerBase
    /// derivations.  Currently there is only one, the shutdown command.
    ///
    ///   2. Custom controller commands - commands that the deriving controller
    /// class implements.  These commands are executed by the deriving
    /// controller.
    ///
    ///   3. Custom application commands - commands supported by the application
    /// process implementation.  These commands are executed by the application
    /// process.
    ///
    /// @param command is a string label representing the command to execute.
    /// @param args is a set of arguments (if any) required for the given
    /// command.
    ///
    /// @return an Element that contains the results of command composed
    /// of an integer status value and a string explanation of the outcome.
    /// The status value is one of the following:
    ///   D2::COMMAND_SUCCESS - Command executed successfully
    ///   D2::COMMAND_ERROR - Command is valid but suffered an operational
    ///   failure.
    ///   D2::COMMAND_INVALID - Command is not recognized as valid be either
    ///   the controller or the application process.
    virtual isc::data::ConstElementPtr
    executeCommand(const std::string& command, isc::data::ConstElementPtr args);

protected:
    /// @brief Virtual method that provides derivations the opportunity to
    /// support additional command line options.  It is invoked during command
    /// line argument parsing (see parseArgs method) if the option is not
    /// recognized as a stock DControllerBase option.
    ///
    /// @param option is the option "character" from the command line, without
    /// any prefixing hyphen(s)
    /// @param optarg is the argument value (if one) associated with the option
    ///
    /// @return must return true if the option was valid, false is it is
    /// invalid. (Note the default implementation always returns false.)
    virtual bool customOption(int option, char *optarg);

    /// @brief Abstract method that is responsible for instantiating the
    /// application process object. It is invoked by the controller after
    /// command line argument parsing as part of the process initialization
    /// (see initProcess method).
    ///
    /// @return returns a pointer to the new process object (DProcessBase*)
    /// or NULL if the create fails.
    /// Note this value is subsequently wrapped in a smart pointer.
    virtual DProcessBase* createProcess() = 0;

    /// @brief Virtual method that provides derivations the opportunity to
    /// support custom external commands executed by the controller.  This
    /// method is invoked by the processCommand if the received command is
    /// not a stock controller command.
    ///
    /// @param command is a string label representing the command to execute.
    /// @param args is a set of arguments (if any) required for the given
    /// command.
    ///
    /// @return an Element that contains the results of command composed
    /// of an integer status value and a string explanation of the outcome.
    /// The status value is one of the following:
    ///   D2::COMMAND_SUCCESS - Command executed successfully
    ///   D2::COMMAND_ERROR - Command is valid but suffered an operational
    ///   failure.
    ///   D2::COMMAND_INVALID - Command is not recognized as a valid custom
    ///   controller command.
    virtual isc::data::ConstElementPtr customControllerCommand(
            const std::string& command, isc::data::ConstElementPtr args);

    /// @brief Virtual method which is invoked after the controller successfully
    /// establishes BIND10 connectivity.  It provides an opportunity for the
    /// derivation to execute any custom behavior associated with session
    /// establishment.
    ///
    /// Note, it is not called  when running stand-alone.
    ///
    /// @throw should throw a DControllerBaseError if it fails.
    virtual void onSessionConnect(){};

    /// @brief Virtual method which is invoked as the first action taken when
    /// the controller is terminating the session(s) with BIND10.  It provides
    /// an opportunity for the derivation to execute any custom behavior
    /// associated with session termination.
    ///
    /// Note, it is not called  when running stand-alone.
    ///
    /// @throw should throw a DControllerBaseError if it fails.
    virtual void onSessionDisconnect(){};

    /// @brief Virtual method which can be used to contribute derivation
    /// specific usage text.  It is invoked by the usage() method under
    /// invalid usage conditions.
    ///
    /// @return returns the desired text.
    virtual const std::string getUsageText() const {
        return ("");
    }

    /// @brief Virtual method which returns a string containing the option
    /// letters for any custom command line options supported by the derivation.
    /// These are added to the stock options of "s" and "v" during command
    /// line interpretation.
    ///
    /// @return returns a string containing the custom option letters.
    virtual const std::string getCustomOpts() const {
        return ("");
    }

    /// @brief Fetches the name of the application under control.
    ///
    /// @return returns the controller service name string
    const std::string getAppName() const {
        return (app_name_);
    }

    /// @brief Fetches the name of the application executable.
    ///
    /// @return returns the controller logger name string
    const std::string getBinName() const {
        return (bin_name_);
    }

    /// @brief Supplies whether or not the controller is in stand alone mode.
    ///
    /// @return returns true if in stand alone mode, false otherwise
    bool isStandAlone() const {
        return (stand_alone_);
    }

    /// @brief Method for enabling or disabling stand alone mode.
    ///
    /// @param value is the new value to assign the flag.
    void setStandAlone(bool value) {
        stand_alone_ = value;
    }

    /// @brief Supplies whether or not verbose logging is enabled.
    ///
    /// @return returns true if verbose logging is enabled.
    bool isVerbose() const {
        return (verbose_);
    }

    /// @brief Method for enabling or disabling verbose logging.
    ///
    /// @param value is the new value to assign the flag.
    void setVerbose(bool value) {
        verbose_ = value;
    }

    /// @brief Getter for fetching the controller's IOService
    ///
    /// @return returns a pointer reference to the IOService.
    IOServicePtr& getIOService() {
        return (io_service_);
    }

    /// @brief Getter for fetching the name of the controller's BIND10 spec
    /// file.
    ///
    /// @return returns the file name string.
    const std::string getSpecFileName() const {
        return (spec_file_name_);
    }

    /// @brief Setter for setting the name of the controller's BIND10 spec file.
    ///
    /// @param spec_file_name the file name string.
    void setSpecFileName(const std::string& spec_file_name) {
        spec_file_name_ = spec_file_name;
    }

    /// @brief Static getter which returns the singleton instance.
    ///
    /// @return returns a pointer reference to the private singleton instance
    /// member.
    static DControllerBasePtr& getController() {
        return (controller_);
    }

    /// @brief Static setter which sets the singleton instance.
    ///
    /// @param controller is a pointer to the singleton instance.
    ///
    /// @throw throws DControllerBase error if an attempt is made to set the
    /// instance a second time.
    static void setController(const DControllerBasePtr& controller);

private:
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

    /// @brief Instantiates the application process and then initializes it.
    /// This is the second step taken during launch, following successful
    /// command line parsing. It is used to invoke the derivation-specific
    /// implementation of createProcess, following by an invoking of the
    /// newly instantiated process's init method.
    ///
    /// @throw throws DControllerBaseError or indirectly DProcessBaseError
    /// if there is a failure creating or initializing the application process.
    void initProcess();

    /// @brief Establishes connectivity with BIND10.  This method is used
    /// invoked during launch, if running in integrated mode, following
    /// successful process initialization.  It is responsible for establishing
    /// the BIND10 control and config sessions. During the session creation,
    /// it passes in the controller's IOService and the callbacks for command
    /// directives and config events.  Lastly, it will invoke the onConnect
    /// method providing the derivation an opportunity to execute any custom
    /// logic associated with session establishment.
    ///
    /// @throw the BIND10 framework may throw std::exceptions.
    void establishSession();

    /// @brief Invokes the application process's event loop,(DBaseProcess::run).
    /// It is called during launch only after successfully completing the
    /// requested setup: command line parsing, application initialization,
    /// and session establishment (if not stand-alone).
    /// The process event loop is expected to only return upon application
    /// shutdown either in response to the shutdown command or due to an
    /// unrecoverable error.
    ///
    // @throw throws DControllerBaseError or indirectly DProcessBaseError
    void runProcess();

    /// @brief Terminates connectivity with BIND10. This method is invoked
    /// in integrated mode after the application event loop has exited. It
    /// first calls the onDisconnect method providing the derivation an
    /// opportunity to execute custom logic if needed, and then terminates the
    /// BIND10 config and control sessions.
    ///
    /// @throw the BIND10 framework may throw std:exceptions.
    void disconnectSession();

    /// @brief Initiates shutdown procedure.  This method is invoked
    /// by executeCommand in response to the shutdown command. It will invoke
    /// the application process's shutdown method which causes the process to
    /// to begin its shutdown process.
    ///
    /// Note, it is assumed that the process of shutting down is neither
    /// instanteneous nor synchronous.  This method does not "block" waiting
    /// until the process has halted.  Rather it is used to convey the
    /// need to shutdown.  A successful return indicates that the shutdown
    /// has successfully commenced, but does not indicate that the process
    /// has actually exited. 
    ///
    /// @return returns an Element that contains the results of shutdown
    /// command composed of an integer status value (0 means successful,
    /// non-zero means failure), and a string explanation of the outcome.
    isc::data::ConstElementPtr shutdown(isc::data::ConstElementPtr args);

    /// @brief Prints the program usage text to std error.
    ///
    /// @param text is a string message which will preceded the usage text.
    /// This is intended to be used for specific usage violation messages.
    void usage(const std::string& text);

private:
    /// @brief Display name of the service under control. This name
    /// appears in log statements.
    std::string app_name_;

    /// @brief Name of the service executable. By convention this matches
    /// the BIND10 module name. It is also used to establish the logger
    /// name.
    std::string bin_name_;

    /// @brief Indicates if the controller stand alone mode is enabled. When
    /// enabled, the controller will not establish connectivity with BIND10.
    bool stand_alone_;

    /// @brief Indicates if the verbose logging mode is enabled.
    bool verbose_;

    /// @brief The absolute file name of the BIND10 spec file.
    std::string spec_file_name_;

    /// @brief Pointer to the instance of the process.
    ///
    /// This is required for config and command handlers to gain access to
    /// the process
    DProcessBasePtr process_;

    /// @brief Shared pointer to an IOService object, used for ASIO operations.
    IOServicePtr io_service_;

    /// @brief Helper session object that represents raw connection to msgq.
    SessionPtr cc_session_;

    /// @brief Session that receives configuration and commands.
    ModuleCCSessionPtr config_session_;

    /// @brief Singleton instance value.
    static DControllerBasePtr controller_;

// DControllerTest is named a friend class to facilitate unit testing while
// leaving the intended member scopes intact.
friend class DControllerTest;
};

}; // namespace isc::d2
}; // namespace isc

#endif
