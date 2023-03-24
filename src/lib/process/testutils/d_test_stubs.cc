// Copyright (C) 2013-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_service.h>
#include <process/d_log.h>
#include <process/testutils/d_test_stubs.h>
#include <process/daemon.h>
#include <cc/command_interpreter.h>
#include <functional>

using namespace boost::asio;

namespace isc {
namespace process {

// Initialize the static failure flag.
SimFailure::FailureType SimFailure::failure_type_ = SimFailure::ftNoFailure;

DStubProcess::DStubProcess(const char* name, asiolink::IOServicePtr io_service)
    : DProcessBase(name, io_service, DCfgMgrBasePtr(new DStubCfgMgr())) {
};


void
DStubProcess::init() {
    if (SimFailure::shouldFailOn(SimFailure::ftProcessInit)) {
        // Simulates a failure to instantiate the process.
        isc_throw(DProcessBaseError, "DStubProcess simulated init() failure");
    }
};

void
DStubProcess::run() {
    // Until shut down or an fatal error occurs, wait for and
    // execute a single callback. This is a preliminary implementation
    // that is likely to evolve as development progresses.
    // To use run(), the "managing" layer must issue an io_service::stop
    // or the call to run will continue to block, and shutdown will not
    // occur.
    asiolink::IOServicePtr& io_service = getIoService();
    while (!shouldShutdown()) {
        try {
            io_service->run_one();
        } catch (const std::exception& ex) {
            isc_throw (DProcessBaseError,
                std::string("Process run method failed: ") + ex.what());
        }
    }
};

isc::data::ConstElementPtr
DStubProcess::shutdown(isc::data::ConstElementPtr /* args */) {
    if (SimFailure::shouldFailOn(SimFailure::ftProcessShutdown)) {
        // Simulates a failure during shutdown process.
        isc_throw(DProcessBaseError, "DStubProcess simulated shutdown failure");
    }

    setShutdownFlag(true);
    stopIOService();
    return (isc::config::createAnswer(isc::config::CONTROL_RESULT_SUCCESS,
                                      "Shutdown initiated."));
}

isc::data::ConstElementPtr
DStubProcess::configure(isc::data::ConstElementPtr config_set, bool check_only) {
    if (SimFailure::shouldFailOn(SimFailure::ftProcessConfigure)) {
        // Simulates a process configure failure.
        return (isc::config::createAnswer(isc::config::CONTROL_RESULT_ERROR,
                                          "Simulated process configuration error."));
    }

    return (getCfgMgr()->simpleParseConfig(config_set, check_only));
}

DStubProcess::~DStubProcess() {
    Daemon::setVerbose(false);
};

//************************** DStubController *************************

// Define custom command line option command supported by DStubController.
const char* DStubController::stub_option_x_ = "x";

/// @brief Defines the app name used to construct the controller
const char* DStubController::stub_app_name_ = "TestService";

/// @brief Defines the bin name used to construct the controller
const char* DStubController::stub_bin_name_ = "TestBin";


DControllerBasePtr&
DStubController::instance() {
    // If the singleton hasn't been created, do it now.
    if (!getController()) {
        DControllerBasePtr p(new DStubController());
        setController(p);
    }

    return (getController());
}

DStubController::DStubController()
    : DControllerBase(stub_app_name_, stub_bin_name_),
      processed_signals_(), record_signal_only_(false), use_alternate_parser_(false) {
}

bool
DStubController::customOption(int option, char* /* optarg */)
{
    // Check for the custom option supported by DStubController.
    if (static_cast<char>(option) == *stub_option_x_) {
        return (true);
    }

    return (false);
}

DProcessBase* DStubController::createProcess() {
    if (SimFailure::shouldFailOn(SimFailure::ftCreateProcessException)) {
        // Simulates a failure to instantiate the process due to exception.
        throw std::runtime_error("SimFailure::ftCreateProcess");
    }

    if (SimFailure::shouldFailOn(SimFailure::ftCreateProcessNull)) {
        // Simulates a failure to instantiate the process.
        return (NULL);
    }

    // This should be a successful instantiation.
    return (new DStubProcess(getAppName().c_str(), getIOService()));
}

const std::string DStubController::getCustomOpts() const {
    // Return the "list" of custom options supported by DStubController.
    return (std::string(stub_option_x_));
}

void
DStubController::processSignal(int signum){
    processed_signals_.push_back(signum);
    if (record_signal_only_) {
        return;
    }

    DControllerBase::processSignal(signum);
}

isc::data::ConstElementPtr
DStubController::parseFile(const std::string& /*file_name*/) {
    isc::data::ConstElementPtr elements;
    if (use_alternate_parser_) {
        std::ostringstream os;

        os << "{ \"" << getController()->getAppName()
            << "\": " << std::endl;
        os <<  "{ \"string_test\": \"alt value\" } ";
        os << " } " << std::endl;
        elements = isc::data::Element::fromJSON(os.str());
    }

    return (elements);
}

DStubController::~DStubController() {
}

//************************** DControllerTest *************************

void
DControllerTest::writeFile(const std::string& content,
                           const std::string& module_name) {
    std::ofstream out(CFG_TEST_FILE, std::ios::trunc);
    ASSERT_TRUE(out.is_open());

    out << "{ \"" << (!module_name.empty() ? module_name
                      : getController()->getAppName())
        << "\": " << std::endl;

    out << content;
    out << " } " << std::endl;
    out.close();
}

void
DControllerTest::timedWriteCallback() {
    writeFile(new_cfg_content_);
}

void
DControllerTest::scheduleTimedWrite(const std::string& config,
                                    int write_time_ms) {
    new_cfg_content_ = config;
    write_timer_.reset(new asiolink::IntervalTimer(*getIOService()));
    write_timer_->setup(std::bind(&DControllerTest::timedWriteCallback, this),
                        write_time_ms, asiolink::IntervalTimer::ONE_SHOT);
}

void
DControllerTest::runWithConfig(const std::string& config, int run_time_ms,
                               time_duration& elapsed_time) {
    // Create the config file.
    writeFile(config);

    // Shutdown (without error) after runtime.
    isc::asiolink::IntervalTimer timer(*getIOService());
    timer.setup(genShutdownCallback, run_time_ms);

    // Record start time, and invoke launch().
    // We catch and rethrow to allow testing error scenarios.
    ptime start = microsec_clock::universal_time();
    try  {
        // Set up valid command line arguments
        char* argv[] = { const_cast<char*>("progName"),
                         const_cast<char*>("-c"),
                         const_cast<char*>(DControllerTest::CFG_TEST_FILE),
                         const_cast<char*>("-d") };
        launch(4, argv);
    } catch (...) {
        // calculate elapsed time, then rethrow it
        elapsed_time = microsec_clock::universal_time() - start;
        throw;
    }

    elapsed_time = microsec_clock::universal_time() - start;
}

void
DControllerTest::runWithConfig(const std::string& config, int run_time_ms,
                               const TestCallback& callback,
                               time_duration& elapsed_time) {
    // Create the config file.
    writeFile(config);

    // Shutdown (without error) after runtime.
    isc::asiolink::IntervalTimer timer(*getIOService());
    timer.setup([&] { callback(); genShutdownCallback(); }, run_time_ms);

    // Record start time, and invoke launch().
    // We catch and rethrow to allow testing error scenarios.
    ptime start = microsec_clock::universal_time();
    try  {
        // Set up valid command line arguments
        char* argv[] = { const_cast<char*>("progName"),
                         const_cast<char*>("-c"),
                         const_cast<char*>(DControllerTest::CFG_TEST_FILE),
                         const_cast<char*>("-d") };
        launch(4, argv);
    } catch (...) {
        // calculate elapsed time, then rethrow it
        elapsed_time = microsec_clock::universal_time() - start;
        throw;
    }

    elapsed_time = microsec_clock::universal_time() - start;
}

DProcessBasePtr
DControllerTest:: getProcess() {
    DProcessBasePtr p;
    if (getController()) {
        p = getController()->getProcess();
    }
    return (p);
}

DCfgMgrBasePtr
DControllerTest::getCfgMgr() {
    DCfgMgrBasePtr p;
    if (getProcess()) {
        p = getProcess()->getCfgMgr();
    }

    return (p);
}

ConfigPtr
DControllerTest::getContext() {
    ConfigPtr p;
    if (getCfgMgr()) {
        p = getCfgMgr()->getContext();
    }

    return (p);
}

// Initialize controller wrapper's static instance getter member.
DControllerTest::InstanceGetter DControllerTest::instanceGetter_ = NULL;

/// @brief Defines the name of the configuration file to use
const char* DControllerTest::CFG_TEST_FILE = "d2-test-config.json";

//************************** DStubContext *************************

DStubContext::DStubContext() {
}

DStubContext::~DStubContext() {
}

ConfigPtr
DStubContext::clone() {
    return (ConfigPtr(new DStubContext(*this)));
}

DStubContext::DStubContext(const DStubContext& rhs): ConfigBase(rhs) {
}

isc::data::ElementPtr
DStubContext::toElement() const {
    return (isc::data::Element::createMap());
}

//************************** DStubCfgMgr *************************

DStubCfgMgr::DStubCfgMgr()
    : DCfgMgrBase(ConfigPtr(new DStubContext())) {
}

DStubCfgMgr::~DStubCfgMgr() {
}

ConfigPtr
DStubCfgMgr::createNewContext() {
    return (ConfigPtr (new DStubContext()));
}

isc::data::ConstElementPtr
DStubCfgMgr::parse(isc::data::ConstElementPtr /*config*/, bool /*check_only*/) {
    return (isc::config::createAnswer(isc::config::CONTROL_RESULT_SUCCESS,
                                      "It all went fine. I promise"));
}

} // namespace isc::process
} // namespace isc
