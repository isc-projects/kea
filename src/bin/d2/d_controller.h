// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_service.h>
#include <cc/data.h>
#include <d2/d2_log.h>
#include <d2/d_process.h>
#include <d2/io_service_signal.h>
#include <dhcpsrv/daemon.h>
#include <exceptions/exceptions.h>
#include <log/logger_support.h>
#include <util/signal_set.h>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>


namespace isc {
namespace d2 {

/// @brief Exception thrown when the command line is invalid.
class InvalidUsage : public isc::Exception {
public:
    InvalidUsage(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception used to convey version info upwards.
/// Since command line argument parsing is done as part of
/// DControllerBase::launch(), it uses this exception to propagate
/// version information up to main(), when command line argument
/// -v or -V is given.
class VersionMessage : public isc::Exception {
public:
    VersionMessage(const char* file, size_t line, const char* what) :
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
class DControllerBase : public dhcp::Daemon {
public:
    /// @brief Constructor
    ///
    /// @param app_name is display name of the application under control. This
    /// name appears in log statements.
    /// @param bin_name is the name of the application executable.
    DControllerBase(const char* app_name, const char* bin_name);

    /// @brief Destructor
    virtual ~DControllerBase();

    /// @brief Acts as the primary entry point into the controller execution
    /// and provides the outermost application control logic:
    ///
    /// 1. parse command line arguments
    /// 2. instantiate and initialize the application process
    /// 3. load the configuration file
    /// 4. initialize signal handling
    /// 5. start and wait on the application process event loop
    /// 6. exit to the caller
    ///
    /// It is intended to be called from main() and be given the command line
    /// arguments.
    ///
    /// This function can be run in "test mode". It prevents initialization
    /// of D2 module logger. This is used in unit tests which initialize logger
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
    virtual void launch(int argc, char* argv[], const bool test_mode);

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

    /// @brief Reconfigures the process from a configuration file
    ///
    /// By default the file is assumed to be a JSON text file whose contents
    /// include at least:
    ///
    /// @code
    ///  { "<module-name>": {<module-config>} }
    ///
    ///  where:
    ///     module-name : is a label which uniquely identifies the
    ///                   configuration data for this controller's application
    ///
    ///     module-config: a set of zero or more JSON elements which comprise
    ///                    the application's configuration values
    /// @endcode
    ///
    /// The method extracts the set of configuration elements for the
    /// module-name which matches the controller's app_name_ and passes that
    /// set into @c udpateConfig().
    ///
    /// The file may contain an arbitrary number of other modules.
    ///
    /// @return returns an Element that contains the results of configuration
    /// update composed of an integer status value (0 means successful,
    /// non-zero means failure), and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr configFromFile();

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
    virtual isc::data::ConstElementPtr executeCommand(const std::string&
                                                      command,
                                                      isc::data::
                                                      ConstElementPtr args);

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
    /// These are added to the stock options of "c" and "v" during command
    /// line interpretation.
    ///
    /// @return returns a string containing the custom option letters.
    virtual const std::string getCustomOpts() const {
        return ("");
    }

    /// @brief Application-level signal processing method.
    ///
    /// This method is the last step in processing a OS signal occurrence.  It
    /// is invoked when an IOSignal's internal timer callback is executed by
    /// IOService.  It currently supports the following signals as follows:
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

    /// @brief Getter for fetching the controller's IOService
    ///
    /// @return returns a pointer reference to the IOService.
    asiolink::IOServicePtr& getIOService() {
        return (io_service_);
    }

    /// @brief Getter for fetching the name of the controller's config spec
    /// file.
    ///
    /// @return returns the file name string.
    const std::string getSpecFileName() const {
        return (spec_file_name_);
    }

    /// @brief Setter for setting the name of the controller's config spec file.
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

    /// @brief Processes the command line arguments. It is the first step
    /// taken after the controller has been launched.  It combines the stock
    /// list of options with those returned by getCustomOpts(), and uses
    /// cstdlib's getopt to loop through the command line.
    /// It handles stock options directly, and passes any custom options into
    /// the customOption method.  Currently there are only two stock options
    /// -c for specifying the configuration file, and -v for verbose logging.
    ///
    /// @param argc  is the number of command line arguments supplied
    /// @param argv  is the array of string (char *) command line arguments
    ///
    /// @throw InvalidUsage when there are usage errors.
    /// @throw VersionMessage if the -v or -V arguments is given.
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
    /// It instantiates an IOSignalQueue, registers @c osSignalHandler() as
    /// the SignalSet "on-receipt" handler, and lastly instantiates a SignalSet
    /// which listens for SIGHUP, SIGINT, and SIGTERM.
    void initSignalHandling();

    /// @brief Handler for processing OS-level signals
    ///
    /// This method is installed as the SignalSet "on-receipt" handler. Upon
    /// invocation, it uses the controller's IOSignalQueue to schedule an
    /// IOSignal with for the given signal value.
    ///
    /// @param signum OS signal value (e.g. SIGINT, SIGUSR1 ...) to received
    ///
    /// @return SignalSet "on-receipt" handlers are required to return a
    /// boolean indicating if the OS signal has been processed (true) or if it
    /// should be saved for deferred processing (false).  Currently this
    /// method processes all received signals, so it always returns true.
    bool osSignalHandler(int signum);

    /// @brief Handler for processing IOSignals
    ///
    /// This method is supplied as the callback when IOSignals are scheduled.
    /// It fetches the IOSignal for the given sequence_id and then invokes
    /// the virtual method, @c processSignal() passing it the signal value
    /// obtained from the IOSignal.  This allows derivations to supply a
    /// custom signal processing method, while ensuring IOSignalQueue
    /// integrity.
    ///
    /// @param sequence_id id of the IOSignal instance "received"
    void ioSignalHandler(IOSignalId sequence_id);

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

    /// @brief The absolute file name of the JSON spec file.
    std::string spec_file_name_;

    /// @brief Pointer to the instance of the process.
    ///
    /// This is required for config and command handlers to gain access to
    /// the process
    DProcessBasePtr process_;

    /// @brief Shared pointer to an IOService object, used for ASIO operations.
    asiolink::IOServicePtr io_service_;

    /// @brief Set of registered signals to handle.
    util::SignalSetPtr signal_set_;

    /// @brief Queue for propagating caught signals to the IOService.
    IOSignalQueuePtr io_signal_queue_;

    /// @brief Singleton instance value.
    static DControllerBasePtr controller_;

// DControllerTest is named a friend class to facilitate unit testing while
// leaving the intended member scopes intact.
friend class DControllerTest;
};

}; // namespace isc::d2
}; // namespace isc

#endif
