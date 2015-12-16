// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_service.h>
#include <d2/d2_log.h>
#include <d2/spec_config.h>
#include <d2/tests/d_test_stubs.h>

using namespace boost::asio;

namespace isc {
namespace d2 {

const char* valid_d2_config = "{ "
                        "\"ip-address\" : \"127.0.0.1\" , "
                        "\"port\" : 5031, "
                        "\"tsig-keys\": ["
                        "{ \"name\": \"d2_key.tmark.org\" , "
                        "   \"algorithm\": \"HMAC-MD5\" ,"
                        "   \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\" "
                        "} ],"
                        "\"forward-ddns\" : {"
                        "\"ddns-domains\": [ "
                        "{ \"name\": \"tmark.org.\" , "
                        "  \"key-name\": \"d2_key.tmark.org\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.101\" } "
                        "] } ] }, "
                        "\"reverse-ddns\" : {"
                        "\"ddns-domains\": [ "
                        "{ \"name\": \" 0.168.192.in.addr.arpa.\" , "
                        "  \"key-name\": \"d2_key.tmark.org\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.101\" , "
                        "    \"port\": 100 } ] } "
                        "] } }";

// Initialize the static failure flag.
SimFailure::FailureType SimFailure::failure_type_ = SimFailure::ftNoFailure;

// Define custom process command supported by DStubProcess.
const char*  DStubProcess::stub_proc_command_("cool_proc_cmd");

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
                std::string("Process run method failed:") + ex.what());
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
    return (isc::config::createAnswer(0, "Shutdown inititiated."));
}

isc::data::ConstElementPtr
DStubProcess::configure(isc::data::ConstElementPtr config_set) {
    if (SimFailure::shouldFailOn(SimFailure::ftProcessConfigure)) {
        // Simulates a process configure failure.
        return (isc::config::createAnswer(1,
                "Simulated process configuration error."));
    }

    return (getCfgMgr()->parseConfig(config_set));
}

isc::data::ConstElementPtr
DStubProcess::command(const std::string& command,
                      isc::data::ConstElementPtr /* args */) {
    isc::data::ConstElementPtr answer;
    if (SimFailure::shouldFailOn(SimFailure::ftProcessCommand)) {
        // Simulates a process command execution failure.
        answer = isc::config::createAnswer(COMMAND_ERROR,
                                          "SimFailure::ftProcessCommand");
    } else if (command.compare(stub_proc_command_) == 0) {
        answer = isc::config::createAnswer(COMMAND_SUCCESS, "Command accepted");
    } else {
        answer = isc::config::createAnswer(COMMAND_INVALID,
                                           "Unrecognized command:" + command);
    }

    return (answer);
}

DStubProcess::~DStubProcess() {
};

//************************** DStubController *************************

// Define custom controller command supported by DStubController.
const char* DStubController::stub_ctl_command_("spiffy");

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
      processed_signals_(), record_signal_only_(false) {

    if (getenv("KEA_FROM_BUILD")) {
        setSpecFileName(std::string(getenv("KEA_FROM_BUILD")) +
            "/src/bin/d2/dhcp-ddns.spec");
    } else {
        setSpecFileName(D2_SPECFILE_LOCATION);
    }
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

isc::data::ConstElementPtr
DStubController::customControllerCommand(const std::string& command,
                                     isc::data::ConstElementPtr /* args */) {
    isc::data::ConstElementPtr answer;
    if (SimFailure::shouldFailOn(SimFailure::ftControllerCommand)) {
        // Simulates command failing to execute.
        answer = isc::config::createAnswer(COMMAND_ERROR,
                                          "SimFailure::ftControllerCommand");
    } else if (command.compare(stub_ctl_command_) == 0) {
        answer = isc::config::createAnswer(COMMAND_SUCCESS, "Command accepted");
    } else {
        answer = isc::config::createAnswer(COMMAND_INVALID,
                                           "Unrecognized command:" + command);
    }

    return (answer);
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
    write_timer_->setup(boost::bind(&DControllerTest::timedWriteCallback, this),
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
        // calculate elasped time, then rethrow it
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

DCfgContextBasePtr
DControllerTest::getContext() {
    DCfgContextBasePtr p;
    if (getCfgMgr()) {
        p = getCfgMgr()->getContext();
    }

    return (p);
}

// Initialize controller wrapper's static instance getter member.
DControllerTest::InstanceGetter DControllerTest::instanceGetter_ = NULL;

/// @brief Defines the name of the configuration file to use
const char* DControllerTest::CFG_TEST_FILE = "d2-test-config.json";

//************************** ObjectParser *************************

ObjectParser::ObjectParser(const std::string& param_name,
                       ObjectStoragePtr& object_values)
    : param_name_(param_name), object_values_(object_values) {
}

ObjectParser::~ObjectParser(){
}

void
ObjectParser::build(isc::data::ConstElementPtr new_config) {
    if (SimFailure::shouldFailOn(SimFailure::ftElementBuild)) {
        // Simulates an error during element data parsing.
        isc_throw (DCfgMgrBaseError, "Simulated build exception");
    }

    value_ = new_config;
}

void
ObjectParser::commit() {
    if (SimFailure::shouldFailOn(SimFailure::ftElementCommit)) {
        // Simulates an error while committing the parsed element data.
        throw std::runtime_error("Simulated commit exception");
    }

    object_values_->setParam(param_name_, value_,
                             isc::data::Element::Position());
}

//************************** DStubContext *************************

DStubContext::DStubContext(): object_values_(new ObjectStorage()) {
}

DStubContext::~DStubContext() {
}

void
DStubContext::getObjectParam(const std::string& name,
                             isc::data::ConstElementPtr& value) {
    value = object_values_->getParam(name);
}

ObjectStoragePtr&
DStubContext::getObjectStorage() {
    return (object_values_);
}

DCfgContextBasePtr
DStubContext::clone() {
    return (DCfgContextBasePtr(new DStubContext(*this)));
}

DStubContext::DStubContext(const DStubContext& rhs): DCfgContextBase(rhs),
    object_values_(new ObjectStorage(*(rhs.object_values_))) {
}

//************************** DStubCfgMgr *************************

DStubCfgMgr::DStubCfgMgr()
    : DCfgMgrBase(DCfgContextBasePtr(new DStubContext())) {
}

DStubCfgMgr::~DStubCfgMgr() {
}

DCfgContextBasePtr
DStubCfgMgr::createNewContext() {
    return (DCfgContextBasePtr (new DStubContext()));
}

isc::dhcp::ParserPtr
DStubCfgMgr::createConfigParser(const std::string& element_id,
                                const isc::data::Element::Position& pos) {
    isc::dhcp::ParserPtr parser;
    DStubContextPtr context
        = boost::dynamic_pointer_cast<DStubContext>(getContext());
    if (element_id == "bool_test") {
        parser.reset(new isc::dhcp::
                         BooleanParser(element_id,
                                       context->getBooleanStorage()));
    } else if (element_id == "uint32_test") {
        parser.reset(new isc::dhcp::Uint32Parser(element_id,
                                                 context->getUint32Storage()));
    } else if (element_id == "string_test") {
        parser.reset(new isc::dhcp::StringParser(element_id,
                                                 context->getStringStorage()));
    } else {
        // Fail only if SimFailure dictates we should.  This makes it easier
        // to test parse ordering, by permitting a wide range of element ids
        // to "succeed" without specifically supporting them.
        if (SimFailure::shouldFailOn(SimFailure::ftElementUnknown)) {
            isc_throw(DCfgMgrBaseError,
                      "Configuration parameter not supported: " << element_id
                      << pos);
        }

        // Going to assume anything else is an object element.
        parser.reset(new ObjectParser(element_id, context->getObjectStorage()));
    }

    parsed_order_.push_back(element_id);
    return (parser);
}

}; // namespace isc::d2
}; // namespace isc
