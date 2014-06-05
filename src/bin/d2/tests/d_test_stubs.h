// Copyright (C) 2013-2014 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef D_TEST_STUBS_H
#define D_TEST_STUBS_H

#include <cc/data.h>
#include <cc/session.h>
#include <config/ccsession.h>

#include <d2/d2_asio.h>
#include <d2/d_controller.h>
#include <d2/d_cfg_mgr.h>

#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <sstream>

namespace isc {
namespace d2 {

/// @brief Provides a valid DHCP-DDNS configuration for testing basic
/// parsing fundamentals.
extern const char* valid_d2_config;


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
        ftControllerCommand,
        ftProcessCommand,
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

    /// @brief Static constant that defines a custom process command string.
    static const char* stub_proc_command_;

    /// @brief Constructor
    ///
    /// @param name name is a text label for the process. Generally used
    /// in log statements, but otherwise arbitrary.
    /// @param io_service is the io_service used by the caller for
    /// asynchronous event handling.
    ///
    /// @throw DProcessBaseError is io_service is NULL.
    DStubProcess(const char* name, IOServicePtr io_service);

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
    /// @return an Element that contains the results of configuration composed
    /// of an integer status value (0 means successful, non-zero means failure),
    /// and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr configure(isc::data::ConstElementPtr
                                                 config_set);

    /// @brief Executes the given command.
    ///
    /// This implementation will recognizes one "custom" process command,
    /// stub_proc_command_.  It will fail if SimFailure is set to
    /// ftProcessCommand.
    ///
    /// @param command is a string label representing the command to execute.
    /// @param args is a set of arguments (if any) required for the given
    /// command.
    /// @return an Element that contains the results of command composed
    /// of an integer status value and a string explanation of the outcome.
    /// The status value is:
    /// COMMAND_SUCCESS if the command is recognized and executes successfully.
    /// COMMAND_ERROR if the command is recognized but fails to execute.
    /// COMMAND_INVALID if the command is not recognized.
    virtual isc::data::ConstElementPtr command(const std::string& command,
                                               isc::data::ConstElementPtr args);

    // @brief Destructor
    virtual ~DStubProcess();
};


/// @brief Test Derivation of the DControllerBase class.
///
/// DControllerBase is an abstract class and therefore requires a derivation
/// for testing.  It allows testing the majority of the base class code
/// without polluting production derivations (e.g. D2Process).  It uses
/// DStubProcess as its application process class.  It is a full enough
/// implementation to support running both stand alone and integrated.
/// Obviously BIND10 connectivity is not available under unit tests, so
/// testing here is limited to "failures" to communicate with BIND10.
class DStubController : public DControllerBase {
public:
    /// @brief Static singleton instance method. This method returns the
    /// base class singleton instance member.  It instantiates the singleton
    /// and sets the base class instance member upon first invocation.
    ///
    /// @return returns a pointer reference to the singleton instance.
    static DControllerBasePtr& instance();

    /// @brief Defines a custom controller command string. This is a
    /// custom command supported by DStubController.
    static const char* stub_ctl_command_;

    /// @brief Defines a custom command line option supported by
    /// DStubController.
    static const char* stub_option_x_;

    /// @brief Defines the app name used to construct the controller
    static const char* stub_app_name_;

    /// @brief Defines the executable name used to construct the controller
    static const char* stub_bin_name_;

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

    /// @brief Executes custom controller commands are supported by
    /// DStubController. This implementation supports one custom controller
    /// command, stub_ctl_command_.  It will fail if SimFailure is set
    /// to ftControllerCommand.
    ///
    /// @param command is a string label representing the command to execute.
    /// @param args is a set of arguments (if any) required for the given
    /// command.
    /// @return an Element that contains the results of command composed
    /// of an integer status value and a string explanation of the outcome.
    /// The status value is:
    /// COMMAND_SUCCESS if the command is recognized and executes successfully.
    /// COMMAND_ERROR if the command is recognized but fails to execute.
    /// COMMAND_INVALID if the command is not recognized.
    virtual isc::data::ConstElementPtr customControllerCommand(
            const std::string& command, isc::data::ConstElementPtr args);

    /// @brief Provides a string of the additional command line options
    /// supported by DStubController.  DStubController supports one
    /// addition option, stub_option_x_.
    ///
    /// @return returns a string containing the option letters.
    virtual const std::string getCustomOpts() const;

private:
    /// @brief Constructor is private to protect singleton integrity.
    DStubController();

public:
    virtual ~DStubController();
};

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
    DControllerTest(InstanceGetter instance_getter) {
        // Set the static fetcher member, then invoke it via getController.
        // This ensures the singleton is instantiated.
        instanceGetter_ = instance_getter;
        getController();
    }

    /// @brief Destructor
    /// Note the controller singleton is destroyed. This is essential to ensure
    /// a clean start between tests.
    virtual ~DControllerTest() {
        getController().reset();
        static_cast<void>(unlink(CFG_TEST_FILE));
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

    /// @brief Returns true if the Controller's spec file name matches the
    /// given value.
    ///
    /// @param should_be is the value to compare against.
    ///
    /// @return returns true if the values are equal.
    bool checkSpecFileName(const std::string& should_be) {
        return (getController()->getSpecFileName().compare(should_be) == 0);
    }

    /// @brief Tests the existence of the Controller's application process.
    ///
    /// @return returns true if the process instance exists.
    bool checkProcess() {
        return (getController()->process_);
    }

    /// @brief Tests the existence of the Controller's IOService.
    ///
    /// @return returns true if the IOService exists.
    bool checkIOService() {
        return (getController()->io_service_);
    }

    /// @brief Gets the Controller's IOService.
    ///
    /// @return returns a reference to the IOService
    IOServicePtr& getIOService() {
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
        return (getController()->getConfigFileName() == value);
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

    /// @Wrapper to invoke the Controller's executeCommand method.  Please
    /// refer to DControllerBase::executeCommand for details.
    isc::data::ConstElementPtr executeCommand(const std::string& command,
                                       isc::data::ConstElementPtr args){
        return (getController()->executeCommand(command, args));
    }

    /// @brief Callback that will generate shutdown command via the
    /// command callback function.
    static void genShutdownCallback() {
        isc::data::ElementPtr arg_set;
        DControllerBase::commandHandler(SHUT_DOWN_COMMAND, arg_set);
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
    /// @endcod
    ///
    /// suffix the content within a JSON element with the given module
    /// name or  wrapped by a JSON
    /// element  . Tests will
    /// attempt to read that file.
    ///
    /// @param content JSON text to be written to file
    /// @param module_name  content content to be written to file
    void writeFile(const std::string& content,
                   const std::string module_name = "") {
        std::ofstream out(CFG_TEST_FILE, std::ios::trunc);
        ASSERT_TRUE(out.is_open());

        out << "{ \"" << (!module_name.empty() ? module_name :
                          getController()->getAppName())
             << "\": " << std::endl;

        out << content;
        out << " } " << std::endl;
        out.close();
    }

    /// Name of a config file used during tests
    static const char* CFG_TEST_FILE;
};

/// @brief a collection of elements that store uint32 values
typedef isc::dhcp::ValueStorage<isc::data::ConstElementPtr> ObjectStorage;
typedef boost::shared_ptr<ObjectStorage> ObjectStoragePtr;

/// @brief Simple parser derivation for parsing object elements.
class ObjectParser : public isc::dhcp::DhcpConfigParser {
public:

    /// @brief Constructor
    ///
    /// See @ref DhcpConfigParser class for details.
    ///
    /// @param param_name name of the parsed parameter
    ObjectParser(const std::string& param_name, ObjectStoragePtr& object_values);

    /// @brief Destructor
    virtual ~ObjectParser();

    /// @brief Builds parameter value.
    ///
    /// See @ref DhcpConfigParser class for details.
    ///
    /// @param new_config pointer to the new configuration
    /// @throw throws DCfgMgrBaseError if the SimFailure is set to
    /// ftElementBuild. This allows for the simulation of an
    /// exception during the build portion of parsing an element.
    virtual void build(isc::data::ConstElementPtr new_config);

    /// @brief Commits the parsed value to storage.
    ///
    /// See @ref DhcpConfigParser class for details.
    ///
    /// @throw throws DCfgMgrBaseError if SimFailure is set to ftElementCommit.
    /// This allows for the simulation of an exception during the commit
    /// portion of parsing an element.
    virtual void commit();

private:
    /// name of the parsed parameter
    std::string param_name_;

    /// pointer to the parsed value of the parameter
    isc::data::ConstElementPtr value_;

    /// Pointer to the storage where committed value is stored.
    ObjectStoragePtr object_values_;
};


/// @brief Test Derivation of the DCfgContextBase class.
///
/// This class is used to test basic functionality of configuration context.
/// It adds an additional storage container "extra values" to mimic an
/// application extension of configuration storage.  This permits testing that
/// both the base class content as well as the application content is
/// correctly copied during cloning.  This is vital to configuration backup
/// and rollback during configuration parsing.
class DStubContext : public DCfgContextBase {
public:

    /// @brief Constructor
    DStubContext();

    /// @brief Destructor
    virtual ~DStubContext();

    /// @brief Creates a clone of a DStubContext.
    ///
    /// @return returns a pointer to the new clone.
    virtual DCfgContextBasePtr clone();

    /// @brief Fetches the value for a given "extra" configuration parameter
    /// from the context.
    ///
    /// @param name is the name of the parameter to retrieve.
    /// @param value is an output parameter in which to return the retrieved
    /// value.
    /// @throw throws DhcpConfigError if the context does not contain the
    /// parameter.
    void getObjectParam(const std::string& name,
                        isc::data::ConstElementPtr& value);

    ObjectStoragePtr& getObjectStorage();

protected:
    /// @brief Copy constructor
    DStubContext(const DStubContext& rhs);

private:
    /// @brief Private assignment operator, not implemented.
    DStubContext& operator=(const DStubContext& rhs);

    /// @brief Stores non-scalar configuration elements
    ObjectStoragePtr object_values_;
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

    /// @brief Given an element_id returns an instance of the appropriate
    /// parser. It supports the element ids as described in the class brief.
    ///
    /// @param element_id is the string name of the element as it will appear
    /// in the configuration set.
    ///
    /// @return returns a ParserPtr to the parser instance.
    /// @throw throws DCfgMgrBaseError if SimFailure is ftElementUnknown.
    virtual isc::dhcp::ParserPtr
    createConfigParser(const std::string& element_id);

    /// @brief A list for remembering the element ids in the order they were
    /// parsed.
    ElementIdList parsed_order_;

    /// @todo
    virtual DCfgContextBasePtr createNewContext();
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

/// @brief Defines a small but valid DHCP-DDNS compliant configuration for
/// testing configuration parsing fundamentals.
extern const char* valid_d2_config;

}; // namespace isc::d2
}; // namespace isc

#endif
