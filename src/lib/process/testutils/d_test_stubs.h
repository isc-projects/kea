// Copyright (C) 2013-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D_TEST_STUBS_H
#define D_TEST_STUBS_H

#include <asiolink/interval_timer.h>

#include <cc/data.h>
#include <cc/command_interpreter.h>

#include <log/logger_support.h>

#include <process/d_controller.h>
#include <process/d_cfg_mgr.h>

#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::posix_time;

#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <sstream>

namespace isc {
namespace process {

/// @brief Class is used to set a globally accessible value that indicates
/// a specific type of failure to simulate.  Test derivations of base classes
/// can exercise error handling code paths by testing for specific SimFailure
/// values at the appropriate places and then causing the error to "occur".
/// The class consists of an enumerated set of failures, and static methods
/// for getting, setting, and testing the current value.
class SimFailure {
public:
    enum FailureType {
        ftUnknown = -1,
        ftNoFailure = 0,
        ftCreateProcessException,
        ftCreateProcessNull,
        ftProcessInit,
        ftProcessConfigure,
        ftProcessShutdown,
        ftElementBuild,
        ftElementCommit,
        ftElementUnknown
    };

    /// @brief Sets the SimFailure value to the given value.
    ///
    /// @param value is the new value to assign to the global value.
    static void set(enum FailureType value) {
       failure_type_ = value;
    }

    /// @brief Gets the current global SimFailure value
    ///
    /// @return returns the current SimFailure value
    static enum FailureType get() {
       return (failure_type_);
    }

    /// @brief One-shot test of the SimFailure value. If the global
    /// SimFailure value is equal to the given value, clear the global
    /// value and return true.  This makes it convenient for code to
    /// test and react without having to explicitly clear the global
    /// value.
    ///
    /// @param value is the value against which the global value is
    /// to be compared.
    ///
    /// @return returns true if current SimFailure value matches the
    /// given value.
    static bool shouldFailOn(enum FailureType value) {
        if (failure_type_ == value) {
            clear();
            return (true);
        }

        return (false);
    }

    /// @brief Resets the failure type to none.
    static void clear() {
       failure_type_ = ftNoFailure;
    }

    /// @brief Static value for holding the failure type to simulate.
    static enum FailureType failure_type_;
};

/// @brief Test Derivation of the DProcessBase class.
///
/// This class is used primarily to server as a test process class for testing
/// DControllerBase.  It provides minimal, but sufficient implementation to
/// test the majority of DControllerBase functionality.
class DStubProcess : public DProcessBase {
public:

    /// @brief Constructor
    ///
    /// @param name name is a text label for the process. Generally used
    /// in log statements, but otherwise arbitrary.
    /// @param io_service is the io_service used by the caller for
    /// asynchronous event handling.
    ///
    /// @throw DProcessBaseError is io_service is NULL.
    DStubProcess(const char* name, asiolink::IOServicePtr io_service);

    /// @brief Invoked after process instantiation to perform initialization.
    /// This implementation supports simulating an error initializing the
    /// process by throwing a DProcessBaseError if SimFailure is set to
    /// ftProcessInit.
    virtual void init();

    /// @brief Implements the process's event loop.
    /// This implementation is quite basic, surrounding calls to
    /// io_service->runOne() with a test of the shutdown flag. Once invoked,
    /// the method will continue until the process itself is exiting due to a
    /// request to shutdown or some anomaly forces an exit.
    /// @return  returns 0 upon a successful, "normal" termination, non-zero to
    /// indicate an abnormal termination.
    virtual void run();

    /// @brief Implements the process shutdown procedure.
    ///
    /// This sets the instance shutdown flag monitored by run()  and stops
    /// the IO service.
    virtual isc::data::ConstElementPtr shutdown(isc::data::ConstElementPtr);

    /// @brief Processes the given configuration.
    ///
    /// This implementation fails if SimFailure is set to ftProcessConfigure.
    /// Otherwise it will complete successfully.  It does not check the content
    /// of the inbound configuration.
    ///
    /// @param config_set a new configuration (JSON) for the process
    /// @param check_only true if configuration is to be verified only, not applied
    /// @return an Element that contains the results of configuration composed
    /// of an integer status value (0 means successful, non-zero means failure),
    /// and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr
    configure(isc::data::ConstElementPtr config_set, bool check_only);

    /// @brief Returns configuration summary in the textual format.
    ///
    /// @return Always an empty string.
    virtual std::string getConfigSummary(const uint32_t) {
        return ("");
    }

    /// @brief Destructor
    virtual ~DStubProcess();
};


/// @brief Test Derivation of the DControllerBase class.
///
/// DControllerBase is an abstract class and therefore requires a derivation
/// for testing.  It allows testing the majority of the base class code
/// without polluting production derivations (e.g. D2Process).  It uses
/// DStubProcess as its application process class.  It is a full enough
/// implementation to support running both stand alone and integrated.
class DStubController : public DControllerBase {
public:
    /// @brief Static singleton instance method. This method returns the
    /// base class singleton instance member.  It instantiates the singleton
    /// and sets the base class instance member upon first invocation.
    ///
    /// @return returns a pointer reference to the singleton instance.
    static DControllerBasePtr& instance();

    /// @brief Defines a custom command line option supported by
    /// DStubController.
    static const char* stub_option_x_;

    /// @brief Defines the app name used to construct the controller
    static const char* stub_app_name_;

    /// @brief Defines the executable name used to construct the controller
    static const char* stub_bin_name_;

    /// @brief Gets the list of signals that have been caught and processed.
    std::vector<int>& getProcessedSignals() {
        return (processed_signals_);
    }

    /// @brief Deals with other (i.e. not application name) global objects.
    using DControllerBase::handleOtherObjects;

    /// @brief Controls whether signals are processed in full or merely
    /// recorded.
    ///
    /// If true, signal handling will stop after recording the signal.
    /// Otherwise the base class signal handler,
    /// DControllerBase::processSignals will also be invoked. This switch is
    /// useful for ensuring that IOSignals are delivered as expected without
    /// incurring the full impact such as reconfiguring or shutting down.
    ///
    /// @param value boolean which if true enables record-only behavior
    void recordSignalOnly(bool value) {
       record_signal_only_ = value;
    }

    /// @brief Determines if parseFile() implementation is used
    ///
    /// If true, parseFile() will return a Map of elements with fixed content,
    /// mimicking a controller which is using alternate JSON parsing.
    /// If false, parseFile() will return an empty pointer mimicking a
    /// controller which is using original JSON parsing supplied by the
    /// Element class.
    ///
    /// @param value boolean which if true enables record-only behavior
    void useAlternateParser(bool value) {
       use_alternate_parser_ = value;
    }

protected:
    /// @brief Handles additional command line options that are supported
    /// by DStubController.  This implementation supports an option "-x".
    ///
    /// @param option is the option "character" from the command line, without
    /// any prefixing hyphen(s)
    /// @optarg optarg is the argument value (if one) associated with the option
    ///
    /// @return returns true if the option is "x", otherwise ti returns false.
    virtual bool customOption(int option, char *optarg);

    /// @brief Instantiates an instance of DStubProcess.
    ///
    /// This implementation will fail if SimFailure is set to
    /// ftCreateProcessException OR ftCreateProcessNull.
    ///
    /// @return returns a pointer to the new process instance (DProcessBase*)
    /// or NULL if SimFailure is set to ftCreateProcessNull.
    /// @throw throws std::runtime_error if SimFailure is set to
    /// ftCreateProcessException.
    virtual DProcessBase* createProcess();

    /// @brief Provides a string of the additional command line options
    /// supported by DStubController.  DStubController supports one
    /// addition option, stub_option_x_.
    ///
    /// @return returns a string containing the option letters.
    virtual const std::string getCustomOpts() const;

    /// @brief Application-level "signal handler"
    ///
    /// Overrides the base class implementation such that this method
    /// is invoked each time an IOSignal is processed.  It records the
    /// signal received and unless we are in record-only behavior, it
    /// in invokes the base class implementation.
    ///
    /// @param signum OS signal value received
    virtual void processSignal(int signum);

    /// @brief Provides alternate parse file implementation
    ///
    /// Overrides the base class implementation to mimic controllers which
    /// implement alternate file parsing.  If enabled via useAlternateParser()
    /// the method will return a fixed map of elements reflecting the following
    /// JSON:
    ///
    /// @code
    ///     { "<name>getController()->getAppName()" :
    ///          { "string_test": "alt value" };
    ///     }
    ///
    /// @endcode
    ///
    ///  where <name> is getController()->getAppName()
    ///
    /// otherwise it return an empty pointer.
    virtual isc::data::ConstElementPtr parseFile(const std::string&);

public:

    /// @brief Provides additional extended version text
    ///
    /// Overrides the base class implementation so we can
    /// verify the getting the extended version text
    /// contains derivation specific contributions.
    virtual std::string getVersionAddendum() {
        return ("StubController Version Text");
    }

private:
    /// @brief Constructor is private to protect singleton integrity.
    DStubController();

    /// @brief Vector to record the signal values received.
    std::vector<int> processed_signals_;

    /// @brief Boolean for controlling if signals are merely recorded.
    bool record_signal_only_;

    /// @brief Boolean for controlling if parseFile is "implemented"
    bool use_alternate_parser_;

public:
    virtual ~DStubController();
};

/// @brief Defines a pointer to a DStubController.
typedef boost::shared_ptr<DStubController> DStubControllerPtr;

/// @brief Abstract Test fixture class that wraps a DControllerBase. This class
/// is a friend class of DControllerBase which allows it access to class
/// content to facilitate testing.  It provides numerous wrapper methods for
/// the protected and private methods and member of the base class.
class DControllerTest : public ::testing::Test {
public:

    /// @brief Defines a function pointer for controller singleton fetchers.
    typedef DControllerBasePtr& (*InstanceGetter)();

    /// @brief Static storage of the controller class's singleton fetcher.
    /// We need this this statically available for callbacks.
    static InstanceGetter instanceGetter_;

    /// @brief Constructor
    ///
    /// @param instance_getter is a function pointer to the static instance
    /// method of the DControllerBase derivation under test.
    DControllerTest(InstanceGetter instance_getter)
         : write_timer_(), new_cfg_content_() {
        // Set the static fetcher member, then invoke it via getController.
        // This ensures the singleton is instantiated.
        instanceGetter_ = instance_getter;
        getController();
    }

    /// @brief Destructor
    /// Note the controller singleton is destroyed. This is essential to ensure
    /// a clean start between tests.
    virtual ~DControllerTest() {
        // Some unit tests update the logging configuration which has a side
        // effect that all subsequent tests print the output to stdout. This
        // is to ensure that the logging settings are back to default.
        isc::log::setDefaultLoggingOutput();

        if (write_timer_) {
            write_timer_->cancel();
        }

        getController().reset();
        static_cast<void>(remove(CFG_TEST_FILE));
    }

    /// @brief Convenience method that destructs and then recreates the
    /// controller singleton under test.  This is handy for tests within
    /// tests.
    void resetController() {
        getController().reset();
        getController();
    }

    /// @brief Static method which returns the instance of the controller
    /// under test.
    /// @return returns a reference to the controller instance.
    static DControllerBasePtr& getController() {
        return ((*instanceGetter_)());
    }

    /// @brief Returns true if the Controller's app name matches the
    /// given value.
    ///
    /// @param should_be is the value to compare against.
    ///
    /// @return returns true if the values are equal.
    bool checkAppName(const std::string& should_be) {
        return (getController()->getAppName().compare(should_be) == 0);
    }

    /// @brief Returns true if the Controller's service name matches the
    /// given value.
    ///
    /// @param should_be is the value to compare against.
    ///
    /// @return returns true if the values are equal.
    bool checkBinName(const std::string& should_be) {
        return (getController()->getBinName().compare(should_be) == 0);
    }

    /// @brief Tests the existence of the Controller's application process.
    ///
    /// @return returns true if the process instance exists.
    bool checkProcess() {
        return (getController()->process_.get() != 0);
    }

    /// @brief Tests the existence of the Controller's IOService.
    ///
    /// @return returns true if the IOService exists.
    bool checkIOService() {
        return (getController()->io_service_.get() != 0);
    }

    /// @brief Gets the Controller's IOService.
    ///
    /// @return returns a reference to the IOService
    asiolink::IOServicePtr& getIOService() {
        return (getController()->io_service_);
    }

    /// @brief Compares verbose flag with the given value.
    ///
    /// @param value
    ///
    /// @return returns true if the verbose flag is equal to the given value.
    bool checkVerbose(bool value) {
        return (getController()->isVerbose() == value);
    }

    /// @brief Compares configuration file name with the given value.
    ///
    /// @param value file name to compare against
    ///
    /// @return returns true if the verbose flag is equal to the given value.
    bool checkConfigFileName(const std::string& value) {
        return (getController()->getConfigFile() == value);
    }

    /// @Wrapper to invoke the Controller's parseArgs method.  Please refer to
    /// DControllerBase::parseArgs for details.
    void parseArgs(int argc, char* argv[]) {
        getController()->parseArgs(argc, argv);
    }

    /// @Wrapper to invoke the Controller's init method.  Please refer to
    /// DControllerBase::init for details.
    void initProcess() {
        getController()->initProcess();
    }

    /// @Wrapper to invoke the Controller's launch method.  Please refer to
    /// DControllerBase::launch for details.
    void launch(int argc, char* argv[]) {
        optind = 1;
        getController()->launch(argc, argv, true);
    }

    /// @Wrapper to invoke the Controller's updateConfig method.  Please
    /// refer to DControllerBase::updateConfig for details.
    isc::data::ConstElementPtr updateConfig(isc::data::ConstElementPtr
                                            new_config) {
        return (getController()->updateConfig(new_config));
    }

    /// @Wrapper to invoke the Controller's checkConfig method.  Please
    /// refer to DControllerBase::checkConfig for details.
    isc::data::ConstElementPtr checkConfig(isc::data::ConstElementPtr
                                           new_config) {
        return (getController()->checkConfig(new_config));
    }

    /// @brief Callback that will generate shutdown command via the
    /// command callback function.
    static void genShutdownCallback() {
        isc::data::ElementPtr arg_set;
        getController()->shutdownHandler(SHUT_DOWN_COMMAND, arg_set);
    }

    /// @brief Callback that throws an exception.
    static void genFatalErrorCallback() {
        isc_throw (DProcessBaseError, "simulated fatal error");
    }

    /// @brief writes specified content to a well known file
    ///
    /// Writes given JSON content to CFG_TEST_FILE. It will wrap the
    /// content within a JSON element whose name is equal to the controller's
    /// app name or the given module name if not blank:
    ///
    /// @code
    ///    { "<app_name>" : <content> }
    /// @endcode
    ///
    /// suffix the content within a JSON element with the given module
    /// name or  wrapped by a JSON
    /// element  . Tests will
    /// attempt to read that file.
    ///
    /// @param content JSON text to be written to file
    /// @param module_name  content content to be written to file
    void writeFile(const std::string& content,
                   const std::string& module_name = "");

    /// @brief Method used as timer callback to invoke writeFile.
    ///
    /// Wraps a call to writeFile passing in new_cfg_content_.  This allows
    /// the method to be bound as an IntervalTimer callback.
    virtual void timedWriteCallback();

    /// @brief Schedules the given content to overwrite the config file.
    ///
    /// Creates a one-shot IntervalTimer whose callback will overwrite the
    /// configuration with the given content.  This allows the configuration
    /// file to replaced write_time_ms after DControllerBase::launch() has
    /// invoked runProcess().
    ///
    /// @param config JSON string containing the desired content for the config
    /// file.
    /// @param write_time_ms time in milliseconds to delay before writing the
    /// file.
    void scheduleTimedWrite(const std::string& config, int write_time_ms);

    /// @brief Convenience method for invoking standard, valid launch
    ///
    /// This method sets up a timed run of the DController::launch.  It does
    /// the following:
    /// - It creates command line argument variables argc/argv
    /// - Invokes writeFile to create the config file with the given content
    /// - Schedules a shutdown time timer to call DController::executeShutdown
    /// after the interval
    /// - Records the start time
    /// - Invokes DController::launch() with the command line arguments
    /// - After launch returns, it calculates the elapsed time and returns it
    ///
    /// @param config configuration file content to write before calling launch
    /// @param run_time_ms  maximum amount of time to allow runProcess() to
    /// continue.
    /// @param[out] elapsed_time the actual time in ms spent in launch().
    void runWithConfig(const std::string& config, int run_time_ms,
                       time_duration& elapsed_time);

    /// @brief Type of testing callbacks
    typedef std::function<void()> TestCallback;

    /// @brief Convenience method for invoking standard, valid launch
    /// with a testing callback
    ///
    /// This method sets up a timed run of the DController::launch.  It does
    /// the following:
    /// - It creates command line argument variables argc/argv
    /// - Invokes writeFile to create the config file with the given content
    /// - Schedules a shutdown time timer to call DController::executeShutdown
    /// after the interval
    /// - Records the start time
    /// - Invokes DController::launch() with the command line arguments
    /// - After launch returns, it calculates the elapsed time and returns it
    ///
    /// @note the callback is called before the shutdown and MUST NOT throw
    /// @param config configuration file content to write before calling launch
    /// @param run_time_ms  maximum amount of time to allow runProcess() to
    /// continue.
    /// @param callback testing callback of TestCallback type
    /// @param[out] elapsed_time the actual time in ms spent in launch().
    void runWithConfig(const std::string& config, int run_time_ms,
                       const TestCallback& callback,
                       time_duration& elapsed_time);

    /// @brief Fetches the controller's process
    ///
    /// @return A pointer to the process which may be null if it has not yet
    /// been instantiated.
    DProcessBasePtr getProcess();

    /// @brief Fetches the process's configuration manager
    ///
    /// @return A pointer to the manager which may be null if it has not yet
    /// been instantiated.
    DCfgMgrBasePtr getCfgMgr();

    /// @brief Fetches the configuration manager's context
    ///
    /// @return A pointer to the context which may be null if it has not yet
    /// been instantiated.
    ConfigPtr getContext();

    /// @brief Timer used for delayed configuration file writing.
    asiolink::IntervalTimerPtr write_timer_;

    /// @brief String which contains the content delayed file writing will use.
    std::string new_cfg_content_;

    /// @brief Name of a config file used during tests
    static const char* CFG_TEST_FILE;
};

/// @brief Test Derivation of the ConfigBase class.
///
/// This class is used to test basic functionality of configuration context.
/// It adds an additional storage container "extra values" to mimic an
/// application extension of configuration storage.  This permits testing that
/// both the base class content as well as the application content is
/// correctly copied during cloning.  This is vital to configuration backup
/// and rollback during configuration parsing.
class DStubContext : public ConfigBase {
public:

    /// @brief Constructor
    DStubContext();

    /// @brief Destructor
    virtual ~DStubContext();

    /// @brief Creates a clone of a DStubContext.
    ///
    /// @return returns a pointer to the new clone.
    virtual ConfigPtr clone();

protected:
    /// @brief Copy constructor
    DStubContext(const DStubContext& rhs);

private:
    /// @brief Private assignment operator, not implemented.
    DStubContext& operator=(const DStubContext& rhs);

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to a configuration
    virtual isc::data::ElementPtr toElement() const;
};

/// @brief Defines a pointer to DStubContext.
typedef boost::shared_ptr<DStubContext> DStubContextPtr;

/// @brief Test Derivation of the DCfgMgrBase class.
///
/// This class is used to test basic functionality of configuration management.
/// It supports the following configuration elements:
///
/// "bool_test" - Boolean element, tests parsing and committing a boolean
///               configuration parameter.
/// "uint32_test" - Uint32 element, tests parsing and committing a uint32_t
///               configuration parameter.
/// "string_test" - String element, tests parsing and committing a string
///               configuration parameter.
/// "extra_test" - "Extra" element, tests parsing and committing an extra
///               configuration parameter. (This is used to demonstrate
///               derivation's addition of storage to configuration context.
///
/// It also keeps track of the element ids that are parsed in the order they
/// are parsed.  This is used to test ordered and non-ordered parsing.
class DStubCfgMgr : public DCfgMgrBase {
public:
    /// @brief Constructor
    DStubCfgMgr();

    /// @brief Destructor
    virtual ~DStubCfgMgr();

    /// @brief Pretends to parse the config
    ///
    /// This method pretends to parse the configuration specified on input
    /// and returns a positive answer. The check_only flag is currently ignored.
    ///
    /// @param config configuration specified
    /// @param check_only whether it's real configuration (false) or just
    ///                configuration check (true)
    /// @return always positive answer
    ///
    isc::data::ConstElementPtr
    parse(isc::data::ConstElementPtr config, bool check_only);

    /// @brief Returns a summary of the configuration in the textual format.
    ///
    /// @return Always an empty string.
    virtual std::string getConfigSummary(const uint32_t) {
        return ("");
    }

    /// @todo
    virtual ConfigPtr createNewContext();
};

/// @brief Defines a pointer to DStubCfgMgr.
typedef boost::shared_ptr<DStubCfgMgr> DStubCfgMgrPtr;

/// @brief Test fixture base class for any fixtures which test parsing.
/// It provides methods for converting JSON strings to configuration element
/// sets and checking parse results
class ConfigParseTest : public ::testing::Test {
public:

    /// @brief Constructor
    ConfigParseTest(){
    }

    /// @brief Destructor
    ~ConfigParseTest() {
    }

    /// @brief Converts a given JSON string into an Element set and stores the
    /// result the member variable, config_set_.
    ///
    /// @param json_text contains the configuration text in JSON format to
    /// convert.
    /// @return returns AssertionSuccess if there were no parsing errors,
    /// AssertionFailure otherwise.
    ::testing::AssertionResult fromJSON(const std::string& json_text) {
        try  {
            config_set_ = isc::data::Element::fromJSON(json_text);
        } catch (const isc::Exception &ex) {
            return (::testing::AssertionFailure(::testing::Message() <<
                                                "JSON text failed to parse:"
                                                << ex.what()));
        }

        return (::testing::AssertionSuccess());
    }

    /// @brief Compares the status in the  parse result stored in member
    /// variable answer_ to a given value.
    ///
    /// @param should_be is an integer against which to compare the status.
    ///
    /// @return returns AssertionSuccess if there were no parsing errors,
    /// AssertionFailure otherwise.
    ::testing::AssertionResult checkAnswer(int should_be) {
        return (checkAnswer(answer_, should_be));
    }

    /// @brief Compares the status in the given parse result to a given value.
    ///
    /// @param answer Element set containing an integer response and string
    /// comment.
    /// @param should_be is an integer against which to compare the status.
    ///
    /// @return returns AssertionSuccess if there were no parsing errors,
    /// AssertionFailure otherwise.
    ::testing::AssertionResult checkAnswer(isc::data::ConstElementPtr answer,
                                           int should_be) {
        int rcode = 0;
        isc::data::ConstElementPtr comment;
        comment = isc::config::parseAnswer(rcode, answer);
        if (rcode == should_be) {
            return (testing::AssertionSuccess());
        }

        return (::testing::AssertionFailure(::testing::Message() <<
                                            "checkAnswer rcode:" << rcode
                                            << " comment: " << *comment));
    }

    /// @brief Configuration set being tested.
    isc::data::ElementPtr config_set_;

    /// @brief Results of most recent element parsing.
    isc::data::ConstElementPtr answer_;
};

} // namespace isc::process
} // namespace isc

#endif
