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

#ifndef D_TEST_STUBS_H
#define D_TEST_STUBS_H

#include <asiolink/asiolink.h>
#include <cc/data.h>
#include <cc/session.h>
#include <config/ccsession.h>

#include <d2/d_controller.h>
#include <gtest/gtest.h>

namespace isc {
namespace d2 {

/// @brief Class is used to set a globally accessible value that indicates 
/// a specific type of failure to simulate.  Test derivations of base classes
/// can excercize error handling code paths by testing for specific SimFailure
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
        ftProcessCommand
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

    static void clear() {
       failure_type_ = ftNoFailure;
    }

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
    static const std::string custom_process_command_;

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
    /// process by throwing a DProcesssBaseError if SimFailure is set to
    /// ftProcessInit.  
    virtual void init();

    /// @brief Implements the process's event loop. 
    /// This implementation is quite basic, surrounding calls to 
    /// io_service->runOne() with a test of the shutdown flag. Once invoked, 
    /// the method will continue until the process itself is exiting due to a 
    /// request to shutdown or some anomaly forces an exit.
    /// @return  returns 0 upon a successful, "normal" termination, non-zero to
    /// indicate an abnormal termination.    
    virtual int run();

    /// @brief Implements the process shutdown procedure. Currently this is
    /// limited to setting the instance shutdown flag, which is monitored in
    /// run().
    virtual int shutdown();

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
    /// custom_process_command_.  It will fail if SimFailure is set to 
    /// ftProcessCommand. 
    ///
    /// @param command is a string label representing the command to execute.
    /// @param args is a set of arguments (if any) required for the given
    /// command. 
    /// @return an Element that contains the results of command composed
    /// of an integer status value and a string explanation of the outcome.  
    /// The status value is:
    /// COMMAND_SUCCESS if the command is recongized and executes successfully.
    /// COMMAND_ERROR if the command is recongized but fails to execute.
    /// COMMAND_INVALID if the command is not recognized.
    virtual isc::data::ConstElementPtr command(const std::string& command, 
                                               isc::data::ConstElementPtr args);

    // @brief Destructor
    virtual ~DStubProcess();
};


/// @brief Test Derivation of the DControllerBase class.
///
/// DControllerBase is an abstract class and therefore requires a derivation
/// for testing.  It allows testing the majority of the base classs code 
/// without polluting production derivations (e.g. D2Process).  It uses 
/// D2StubProcess as its application process class.  It is a full enough
/// implementation to support running both stand alone and integrated. 
/// Obviously BIND10 connectivity is not available under unit tests, so
/// testing here is limited to "failures" to communicate with BIND10.
class DStubController : public DControllerBase {
public:
    /// @brief Static singleton instance method. This method returns the
    /// base class singleton instance member.  It instantiates the singleton 
    /// and sets the base class instance member upon first invocation. 
    ///
    /// @return returns the a pointer reference to the singleton instance.
    static DControllerBasePtr& instance();

    /// @brief Defines a custom controller command string. This is a 
    /// custom command supported by DStubController.
    static const std::string custom_ctl_command_;

protected:
    /// @brief Handles additional command line options that are supported
    /// by DStubController.  This implementation supports an option "-x".
    ///
    /// @param option is the option "character" from the command line, without
    /// any prefixing hypen(s)
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
    /// @throw throws std::runtime_error if SimFailure is ste to
    /// ftCreateProcessException.
    virtual DProcessBase* createProcess();

    /// @brief Executes custom controller commands are supported by 
    /// DStubController. This implementation supports one custom controller 
    /// command, custom_controller_command_.  It will fail if SimFailure is set
    /// to ftControllerCommand.
    ///
    /// @param command is a string label representing the command to execute.
    /// @param args is a set of arguments (if any) required for the given
    /// command. 
    /// @return an Element that contains the results of command composed
    /// of an integer status value and a string explanation of the outcome.  
    /// The status value is:
    /// COMMAND_SUCCESS if the command is recongized and executes successfully.
    /// COMMAND_ERROR if the command is recongized but fails to execute.
    /// COMMAND_INVALID if the command is not recognized.
    virtual isc::data::ConstElementPtr customControllerCommand(
            const std::string& command, isc::data::ConstElementPtr args);

    /// @brief Provides a string of the additional command line options 
    /// supported by DStubController. 
    ///
    /// @return returns a string containing the option letters.
    virtual const std::string getCustomOpts();

private:
    /// @brief Constructor is private to protect singleton integrity.
    DStubController();

public:
    virtual ~DStubController();
};

/// @brief Test fixture class that wraps a DControllerBase.  This class 
/// is a friend class of DControllerBase which allows it access to class
/// content to facilitate testing.  It provides numerous wrapper methods for 
/// the protected and private methods and member of the base class.  Note that
/// this class specifically supports DStubController testing, it is designed
/// to be reused, by simply by overriding the init_controller and 
/// destroy_controller methods. 
class DControllerTest : public ::testing::Test {
public:

    typedef DControllerBasePtr& (*InstanceGetter)();
    static InstanceGetter instanceGetter_;

#if 0
    /// @brief Constructor - Invokes virtual init_controller method which
    /// initializes the controller class's singleton instance.
    DControllerTest() {
       init_controller(); 
    }
#endif

    DControllerTest(InstanceGetter instanceGetter) {
        instanceGetter_ = instanceGetter;
    }

    /// @brief Destructor - Invokes virtual init_controller method which
    /// initializes the controller class's singleton instance.  This is
    /// essential to ensure a clean start between tests.
    virtual ~DControllerTest() {
       destroy_controller();
    }

    /// @brief Virtual method which sets static copy of the controller class's 
    /// singleton instance.  We need this copy so we can generically access
    /// the singleton in derivations. 
    void init_controller() {
#if 0
        std::cout << "Calling DController test init_controller" << std::endl;
        controller_under_test_ = DStubController::instance();
#else
        getController();
#endif
    }


    void destroy_controller() {
#if 0
        std::cout << "Calling DController test destroy_controller" << std::endl;
        DStubController::instance().reset();
#else
        getController().reset();
#endif
    }

    void resetController() {
        destroy_controller();
        init_controller();
    }

    static DControllerBasePtr& getController() {
#if 0
        return (controller_under_test_);
#else
        return ((*instanceGetter_)());
#endif
    }

    bool checkName(const std::string& should_be) {
        return (getController()->getName().compare(should_be) == 0);
    }

    bool checkSpecFileName(const std::string& should_be) {
        return (getController()->getSpecFileName().compare(should_be) == 0);
    }

    bool checkProcess() {
        return (getController()->process_);
    }

    bool checkIOService() {
        return (getController()->io_service_);
    }

    IOServicePtr& getIOService() {
        return (getController()->io_service_);
    }

    bool checkStandAlone(bool value) {
        return (getController()->isStandAlone() == value);
    }

    void setStandAlone(bool value) {
        getController()->setStandAlone(value);
    }

    bool checkVerbose(bool value) {
        return (getController()->isVerbose() == value);
    }


    void parseArgs(int argc, char* argv[]) {
        getController()->parseArgs(argc, argv);
    }

    void initProcess() {
        getController()->initProcess();
    }

    void establishSession() {
        getController()->establishSession();
    }

    int launch(int argc, char* argv[]) {
        optind = 1;
        return (getController()->launch(argc, argv));
    }

    void disconnectSession() {
        getController()->disconnectSession();
    }

    isc::data::ConstElementPtr updateConfig(isc::data::ConstElementPtr 
                                            new_config) {
        return (getController()->updateConfig(new_config));
    }

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

    /// @brief Static member that retains a copy of controller singleton 
    /// instance.  This is needed for static asio callback handlers.
    static DControllerBasePtr controller_under_test_;
};

class DStubControllerTest : public DControllerTest {
public:

    DStubControllerTest() : DControllerTest (DStubController::instance) {
    }

    virtual ~DStubControllerTest() {
    }
};



}; // namespace isc::d2 
}; // namespace isc

#endif
