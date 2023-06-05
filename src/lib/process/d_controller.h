// Copyright (C) 2013-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D_CONTROLLER_H
#define D_CONTROLLER_H

#include <asiolink/io_service.h>
#include <asiolink/io_service_signal.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <log/logger_support.h>
#include <process/daemon.h>
#include <process/d_log.h>
#include <process/d_process.h>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <string>
#include <set>

namespace isc {
namespace process {

/// @brief Exception thrown when the command line is invalid.
/// Can be used to transmit negative messages too.
class InvalidUsage : public isc::Exception {
public:
    InvalidUsage(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception used to convey version info upwards.
/// Since command line argument parsing is done as part of
/// DControllerBase::launch(), it uses this exception to propagate
/// version information up to main(), when command line argument
/// -v, -V or -W is given. Can be used to transmit positive messages too.
class VersionMessage : public isc::Exception {
public:
    VersionMessage(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when the controller launch fails.
class LaunchError: public isc::Exception {
public:
    LaunchError (const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when the application process fails.
class ProcessInitError: public isc::Exception {
public:
    ProcessInitError (const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when the application process encounters an
/// operation in its event loop (i.e. run method).
class ProcessRunError: public isc::Exception {
public:
    ProcessRunError (const char* file, size_t line, const char* what) :
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

/// @brief Application Controller
///
/// DControllerBase is an abstract singleton which provides the framework and
/// services for managing an application process that implements the
/// DProcessBase interface.  It runs the process like a stand-alone, command
/// line driven executable, which must be supplied a configuration file at
/// startup. It coordinates command line argument parsing, process
/// instantiation and initialization, and runtime control through external
/// command and configuration event handling.
/// It creates the IOService instance which is used for runtime control
/// events and passes the IOService into the application process at process
/// creation.
/// It provides the callback handlers for command and configuration events
/// which could be triggered by an external source.  Such sources are intended
/// to be registered with and monitored by the controller's IOService such that
/// the appropriate handler can be invoked.
///
/// DControllerBase provides dynamic configuration file reloading upon receipt
/// of SIGHUP, and graceful shutdown upon receipt of either SIGINT or SIGTERM.
///
/// NOTE: Derivations must supply their own static singleton instance method(s)
/// for creating and fetching the instance. The base class declares the instance
/// member in order for it to be available for static callback functions.
class DControllerBase : public Daemon {
public:
    /// @brief Constructor
    ///
    /// @param app_name is display name of the application under control. This
    /// name appears in log statements.
    /// @param bin_name is the name of the application executable.
    DControllerBase(const char* app_name, const char* bin_name);

    /// @brief Destructor
    virtual ~DControllerBase();

    /// @brief returns Kea version on stdout and exit.
    /// redeclaration/redefinition. @ref isc::process::Daemon::getVersion()
    std::string getVersion(bool extended);

    /// @brief Acts as the primary entry point into the controller execution
    /// and provides the outermost application control logic:
    ///
    /// 1. parse command line arguments
    /// 2. instantiate and initialize the application process
    /// 3. load the configuration file
    /// 4. record the start timestamp
    /// 5. initialize signal handling
    /// 6. start and wait on the application process event loop
    /// 7. exit to the caller
    ///
    /// It is intended to be called from main() and be given the command line
    /// arguments.
    ///
    /// This function can be run in "test mode". It prevents initialization
    /// of module logger. This is used in unit tests which initialize logger
    /// in their main function. Such a logger uses environmental variables to
    /// control severity, verbosity etc.
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
    /// ProcessRunError - A fatal error occurred while in the application
    /// process event loop.
    /// @return The value from @c Daemon::getExitValue().
    virtual int launch(int argc, char* argv[], const bool test_mode);

    /// @brief Instance method invoked by the configuration event handler and
    /// which processes the actual configuration update.  Provides behavioral
    /// path for both integrated and stand-alone modes. The current
    /// implementation will merge the configuration update into the existing
    /// configuration and then invoke the application process' configure method.
    ///
    /// @param  new_config is the new configuration
    ///
    /// @return returns an Element that contains the results of configuration
    /// update composed of an integer status value (0 means successful,
    /// non-zero means failure), and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr updateConfig(isc::data::ConstElementPtr
                                                    new_config);

    /// @brief Instance method invoked by the configuration event handler and
    /// which processes the actual configuration check.  Provides behavioral
    /// path for both integrated and stand-alone modes. The current
    /// implementation will merge the configuration update into the existing
    /// configuration and then invoke the application process' configure method
    /// with a final rollback.
    ///
    /// @param  new_config is the new configuration
    ///
    /// @return returns an Element that contains the results of configuration
    /// update composed of an integer status value (0 means successful,
    /// non-zero means failure), and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr checkConfig(isc::data::ConstElementPtr
                                                   new_config);

    /// @brief Reconfigures the process from a configuration file
    ///
    /// By default the file is assumed to be a JSON text file whose contents
    /// include at least:
    ///
    /// @code
    ///  { "<module-name>": {<module-config>}
    ///  }
    ///
    ///  where:
    ///     module-name : is a label which uniquely identifies the
    ///                   configuration data for this controller's application
    ///
    ///     module-config: a set of zero or more JSON elements which comprise
    ///                    the application's configuration values
    /// @endcode
    ///
    /// To translate the JSON content into Elements, @c parseFile() is called
    /// first.  This virtual method provides derivations a means to parse the
    /// file content using an alternate parser.  If it returns an empty pointer
    /// than the JSON parsing providing by Element::fromJSONFile() is called.
    ///
    /// Once parsed, the method extracts the set of configuration
    /// elements for the module-name that matches the controller's app_name_,
    /// looks for the loggers entry and, if present uses it to configure
    /// logging. It then passes that set into @c updateConfig() (or
    /// @c checkConfig()).
    ///
    /// The file may contain an arbitrary number of other modules.
    ///
    /// @return returns an Element that contains the results of configuration
    /// update composed of an integer status value (0 means successful,
    /// non-zero means failure), and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr configFromFile();

    /// @brief Fetches the name of the application under control.
    ///
    /// @return returns the controller service name string
    std::string getAppName() const {
        return (app_name_);
    }

    /// @brief Fetches the name of the application executable.
    ///
    /// @return returns the controller logger name string
    std::string getBinName() const {
        return (bin_name_);
    }

    /// @brief handler for version-get command
    ///
    /// This method handles the version-get command. It returns the basic and
    /// extended version.
    ///
    /// @param command (ignored)
    /// @param args (ignored)
    /// @return answer with version details.
    isc::data::ConstElementPtr
    versionGetHandler(const std::string& command,
                      isc::data::ConstElementPtr args);

    /// @brief handler for 'build-report' command
    ///
    /// This method handles build-report command. It returns the output printed
    /// by configure script which contains most compilation parameters.
    ///
    /// @param command (ignored)
    /// @param args (ignored)
    /// @return answer with build report
    isc::data::ConstElementPtr
    buildReportHandler(const std::string& command,
                       isc::data::ConstElementPtr args);

    /// @brief handler for config-get command
    ///
    /// This method handles the config-get command, which retrieves
    /// the current configuration and returns it in response.
    ///
    /// @param command (ignored)
    /// @param args (ignored)
    /// @return current configuration wrapped in a response
    isc::data::ConstElementPtr
    configGetHandler(const std::string& command,
                     isc::data::ConstElementPtr args);

    /// @brief handler for config-hash-get command
    ///
    /// This method handles the config-hash-get command, which retrieves
    /// the current configuration and returns it in response.
    ///
    /// @param command (ignored)
    /// @param args (ignored)
    /// @return hash of current configuration wrapped in a response
    isc::data::ConstElementPtr
    configHashGetHandler(const std::string& command,
                         isc::data::ConstElementPtr args);

    /// @brief handler for config-write command
    ///
    /// This handle processes write-config command, which writes the
    /// current configuration to disk. This command takes one optional
    /// parameter called filename. If specified, the current configuration
    /// will be written to that file. If not specified, the file used during
    /// Kea start-up will be used. To avoid any exploits, the path is
    /// always relative and .. is not allowed in the filename. This is
    /// a security measure against exploiting file writes remotely.
    ///
    /// @param command (ignored)
    /// @param args may contain optional string argument filename
    /// @return status of the configuration file write
    isc::data::ConstElementPtr
    configWriteHandler(const std::string& command,
                       isc::data::ConstElementPtr args);

    /// @brief handler for config-test command
    ///
    /// This method handles the config-test command, which checks
    /// configuration specified in args parameter.
    ///
    /// @param command (ignored)
    /// @param args configuration to be checked.
    /// @return status of the command
    isc::data::ConstElementPtr
    configTestHandler(const std::string& command,
                      isc::data::ConstElementPtr args);

    /// @brief handler for config-reload command
    ///
    /// This method handles the config-reload command, which reloads
    /// the configuration file.
    ///
    /// @param command (ignored)
    /// @param args (ignored)
    /// @return status of the command
    isc::data::ConstElementPtr
    configReloadHandler(const std::string& command,
                        isc::data::ConstElementPtr args);

    /// @brief handler for config-set command
    ///
    /// This method handles the config-set command, which loads
    /// configuration specified in args parameter.
    ///
    /// @param command (ignored)
    /// @param args configuration to be checked.
    /// @return status of the command
    isc::data::ConstElementPtr
    configSetHandler(const std::string& command,
                     isc::data::ConstElementPtr args);

    /// @brief handler for 'shutdown' command
    ///
    /// This method handles shutdown command. It initiates the shutdown procedure
    /// using CPL methods.
    /// @param command (ignored)
    /// @param args (ignored)
    /// @return answer confirming that the shutdown procedure is started
    isc::data::ConstElementPtr
    shutdownHandler(const std::string& command,
                    isc::data::ConstElementPtr args);

    /// @brief handler for server-tag-get command
    ///
    /// This method handles the server-tag-get command, which retrieves
    /// the current server tag and returns it in response.
    ///
    /// @param command (ignored)
    /// @param args (ignored)
    /// @return current configuration wrapped in a response
    isc::data::ConstElementPtr
    serverTagGetHandler(const std::string& command,
                        isc::data::ConstElementPtr args);

    /// @brief handler for status-get command
    ///
    /// This method handles the status-get command, which retrieves
    /// the server process information i.e. the pid and returns it in
    /// response.
    ///
    /// @param command (ignored)
    /// @param args (ignored)
    /// @return process information wrapped in a response
    isc::data::ConstElementPtr
    statusGetHandler(const std::string& command,
                     isc::data::ConstElementPtr args);

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
    /// @return must return true if the option was valid, false if it is
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
    /// These are added to the stock options of "c", "d", ..., during command
    /// line interpretation.
    ///
    /// @return returns a string containing the custom option letters.
    virtual const std::string getCustomOpts() const {
        return ("");
    }

    /// @brief Check the configuration
    ///
    /// Called by @c launch() when @c check_only_ mode is enabled
    /// @throw VersionMessage when successful but a message should be displayed
    /// @throw InvalidUsage when an error was detected
    void checkConfigOnly();

    /// @brief Application-level signal processing method.
    ///
    /// This method is the last step in processing a OS signal occurrence.
    /// It currently supports the following signals as follows:
    /// -# SIGHUP - instigates reloading the configuration file
    /// -# SIGINT - instigates a graceful shutdown
    /// -# SIGTERM - instigates a graceful shutdown
    /// If it receives any other signal, it will issue a debug statement and
    /// discard it.
    /// Derivations wishing to support additional signals could override this
    /// method with one that: processes the signal if it is one of additional
    /// signals, otherwise invoke this method (DControllerBase::processSignal())
    /// with the signal value.
    /// @todo Provide a convenient way for derivations to register additional
    /// signals.
    virtual void processSignal(int signum);

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

    /// @brief Supplies whether or not check only mode is enabled.
    ///
    /// @return returns true if check only is enabled.
    bool isCheckOnly() const {
        return (check_only_);
    }

    /// @brief Method for enabling or disabling check only mode.
    ///
    /// @todo this method and @c setVerbose are currently not used.
    ///
    /// @param value is the new value to assign the flag.
    void setCheckOnly(bool value) {
        check_only_ = value;
    }

    /// @brief Getter for fetching the controller's IOService
    ///
    /// @return returns a pointer reference to the IOService.
    asiolink::IOServicePtr& getIOService() {
        return (io_service_);
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

    /// @brief Processes the command line arguments. It is the first step
    /// taken after the controller has been launched.  It combines the stock
    /// list of options with those returned by getCustomOpts(), and uses
    /// cstdlib's getopt to loop through the command line.
    /// It handles stock options directly, and passes any custom options into
    /// the customOption method.  Currently there are only some stock options
    /// -c/t for specifying the configuration file, -d for verbose logging,
    /// and -v/V/W for version reports.
    ///
    /// @param argc  is the number of command line arguments supplied
    /// @param argv  is the array of string (char *) command line arguments
    ///
    /// @throw InvalidUsage when there are usage errors.
    /// @throw VersionMessage if the -v, -V or -W arguments is given.
    void parseArgs(int argc, char* argv[]);

    ///@brief Parse a given file into Elements
    ///
    /// This method provides a means for deriving classes to use alternate
    /// parsing mechanisms to parse configuration files into the corresponding
    /// isc::data::Elements. The elements produced must be equivalent to those
    /// which would be produced by the original JSON parsing.  Implementations
    /// should throw when encountering errors.
    ///
    /// The default implementation returns an empty pointer, signifying to
    /// callers that they should submit the file to the original parser.
    ///
    /// @param file_name pathname of the file to parse
    ///
    /// @return pointer to the elements created
    ///
    virtual isc::data::ConstElementPtr parseFile(const std::string& file_name);

    ///@brief Parse text into Elements
    ///
    /// This method provides a means for deriving classes to use alternate
    /// parsing mechanisms to parse configuration text into the corresponding
    /// isc::data::Elements. The elements produced must be equivalent to those
    /// which would be produced by the original JSON parsing.  Implementations
    /// should throw when encountering errors.
    ///
    /// The default implementation returns an empty pointer, signifying to
    /// callers that they should submit the text to the original parser.
    ///
    /// @param input text to parse
    ///
    /// @return pointer to the elements created
    ///
    virtual isc::data::ConstElementPtr parseText(const std::string& input) {
        static_cast<void>(input); // just tu shut up the unused parameter warning
        isc::data::ConstElementPtr elements;
        return (elements);
    }

    /// @brief Instantiates the application process and then initializes it.
    /// This is the second step taken during launch, following successful
    /// command line parsing. It is used to invoke the derivation-specific
    /// implementation of createProcess, following by an invoking of the
    /// newly instantiated process's init method.
    ///
    /// @throw throws DControllerBaseError or indirectly DProcessBaseError
    /// if there is a failure creating or initializing the application process.
    void initProcess();

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

    /// @brief Initiates shutdown procedure.  This method is invoked
    /// by executeCommand in response to the shutdown command. It will invoke
    /// the application process's shutdown method which causes the process to
    /// to begin its shutdown process.
    ///
    /// Note, it is assumed that the process of shutting down is neither
    /// instantaneous nor synchronous.  This method does not "block" waiting
    /// until the process has halted.  Rather it is used to convey the
    /// need to shutdown.  A successful return indicates that the shutdown
    /// has successfully commenced, but does not indicate that the process
    /// has actually exited.
    ///
    /// @return returns an Element that contains the results of shutdown
    /// command composed of an integer status value (0 means successful,
    /// non-zero means failure), and a string explanation of the outcome.
    ///
    /// @param args is a set of derivation-specific arguments (if any)
    /// for the shutdown command.
    isc::data::ConstElementPtr shutdownProcess(isc::data::ConstElementPtr args);

    /// @brief Initializes signal handling
    ///
    /// This method configures the controller to catch and handle signals.
    /// It instantiates a IOSignalSet which listens for SIGHUP, SIGINT, and
    /// SIGTERM.
    void initSignalHandling();

    /// @brief Fetches the current process
    ///
    /// @return a pointer to the current process instance.
    DProcessBasePtr getProcess() {
        return (process_);
    }

    /// @brief Prints the program usage text to std error.
    ///
    /// @param text is a string message which will preceded the usage text.
    /// This is intended to be used for specific usage violation messages.
    void usage(const std::string& text);

    /// @brief Fetches text containing additional version specifics
    ///
    /// This method is provided so derivations can append any additional
    /// desired information such as library dependencies to the extended
    /// version text returned when DControllerBase::getVersion(true) is
    /// invoked.
    /// @return a string containing additional version info
    virtual std::string getVersionAddendum() { return (""); }

    /// @brief Deals with other (i.e. not application name) global objects.
    ///
    /// Code shared between configuration handlers:
    ///  - check obsolete or unknown (aka unsupported) objects.
    ///
    /// @param args Command arguments.
    /// @return Error message or empty string.
    std::string handleOtherObjects(isc::data::ConstElementPtr args);

private:
    /// @brief Name of the service under control.
    /// This name is used as the configuration module name and appears in log
    /// statements.
    std::string app_name_;

    /// @brief Name of the service executable.
    /// By convention this matches the executable name. It is also used to
    /// establish the logger name.
    std::string bin_name_;

    /// @brief Indicates if the verbose logging mode is enabled.
    bool verbose_;

    /// @brief Indicates if the check only mode for the configuration
    /// is enabled (usually specified by the command line -t argument).
    bool check_only_;

    /// @brief Pointer to the instance of the process.
    ///
    /// This is required for config and command handlers to gain access to
    /// the process
    DProcessBasePtr process_;

    /// @brief Shared pointer to an IOService object, used for ASIO operations.
    isc::asiolink::IOServicePtr io_service_;

    /// @brief ASIO signal set.
    isc::asiolink::IOSignalSetPtr io_signal_set_;

    /// @brief Singleton instance value.
    static DControllerBasePtr controller_;

// DControllerTest is named a friend class to facilitate unit testing while
// leaving the intended member scopes intact.
friend class DControllerTest;
};

}  // namespace process
}  // namespace isc

#endif
