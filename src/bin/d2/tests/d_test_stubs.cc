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

#include <d2/d2_log.h>
#include <d2/spec_config.h>
#include <d2/tests/d_test_stubs.h>

using namespace asio;

namespace isc {
namespace d2 {

const char* valid_d2_config = "{ "
                        "\"interface\" : \"eth1\" , "
                        "\"ip_address\" : \"127.0.0.1\" , "
                        "\"port\" : 5031, "
                        "\"tsig_keys\": ["
                        "{ \"name\": \"d2_key.tmark.org\" , "
                        "   \"algorithm\": \"HMAC-MD5\" ,"
                        "   \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\" "
                        "} ],"
                        "\"forward_ddns\" : {"
                        "\"ddns_domains\": [ "
                        "{ \"name\": \"tmark.org.\" , "
                        "  \"key_name\": \"d2_key.tmark.org\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"hostname\": \"one.tmark\" } "
                        "] } ] }, "
                        "\"reverse_ddns\" : {"
                        "\"ddns_domains\": [ "
                        "{ \"name\": \" 0.168.192.in.addr.arpa.\" , "
                        "  \"key_name\": \"d2_key.tmark.org\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"ip_address\": \"127.0.0.101\" , "
                        "    \"port\": 100 } ] } "
                        "] } }";

// Initialize the static failure flag.
SimFailure::FailureType SimFailure::failure_type_ = SimFailure::ftNoFailure;

// Define custom process command supported by DStubProcess.
const char*  DStubProcess::stub_proc_command_("cool_proc_cmd");

DStubProcess::DStubProcess(const char* name, IOServicePtr io_service)
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
    IOServicePtr& io_service = getIoService();
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
DStubProcess::configure(isc::data::ConstElementPtr /*config_set*/) {
    if (SimFailure::shouldFailOn(SimFailure::ftProcessConfigure)) {
        // Simulates a process configure failure.
        return (isc::config::createAnswer(1,
                "Simulated process configuration error."));
    }

    return (isc::config::createAnswer(0, "Configuration accepted."));
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
    : DControllerBase(stub_app_name_, stub_bin_name_) {

    if (getenv("B10_FROM_BUILD")) {
        setSpecFileName(std::string(getenv("B10_FROM_BUILD")) +
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

DStubController::~DStubController() {
}

// Initialize controller wrapper's static instance getter member.
DControllerTest::InstanceGetter DControllerTest::instanceGetter_ = NULL;

//************************** TestParser *************************

TestParser::TestParser(const std::string& param_name):param_name_(param_name) {
}

TestParser::~TestParser(){
}

void
TestParser::build(isc::data::ConstElementPtr new_config) {
    if (SimFailure::shouldFailOn(SimFailure::ftElementBuild)) {
        // Simulates an error during element data parsing.
        isc_throw (DCfgMgrBaseError, "Simulated build exception");
    }

    value_ = new_config;
}

void
TestParser::commit() {
    if (SimFailure::shouldFailOn(SimFailure::ftElementCommit)) {
        // Simulates an error while committing the parsed element data.
        throw std::runtime_error("Simulated commit exception");
    }
}

//************************** DStubContext *************************

DStubContext::DStubContext(): extra_values_(new isc::dhcp::Uint32Storage()) {
}

DStubContext::~DStubContext() {
}

void
DStubContext::getExtraParam(const std::string& name, uint32_t& value) {
    value = extra_values_->getParam(name);
}

isc::dhcp::Uint32StoragePtr
DStubContext::getExtraStorage() {
    return (extra_values_);
}

DCfgContextBasePtr
DStubContext::clone() {
    return (DCfgContextBasePtr(new DStubContext(*this)));
}

DStubContext::DStubContext(const DStubContext& rhs): DCfgContextBase(rhs),
    extra_values_(new isc::dhcp::Uint32Storage(*(rhs.extra_values_))) {
}

//************************** DStubCfgMgr *************************

DStubCfgMgr::DStubCfgMgr()
    : DCfgMgrBase(DCfgContextBasePtr(new DStubContext())) {
}

DStubCfgMgr::~DStubCfgMgr() {
}

isc::dhcp::ParserPtr
DStubCfgMgr::createConfigParser(const std::string& element_id) {
    isc::dhcp::DhcpConfigParser* parser = NULL;
    DStubContextPtr context =
                    boost::dynamic_pointer_cast<DStubContext>(getContext());

    if (element_id == "bool_test") {
        parser = new isc::dhcp::BooleanParser(element_id,
                                              context->getBooleanStorage());
    } else if (element_id == "uint32_test") {
        parser = new isc::dhcp::Uint32Parser(element_id,
                                             context->getUint32Storage());
    } else if (element_id == "string_test") {
        parser = new isc::dhcp::StringParser(element_id,
                                             context->getStringStorage());
    } else if (element_id == "extra_test") {
        parser = new isc::dhcp::Uint32Parser(element_id,
                                             context->getExtraStorage());
    } else {
        // Fail only if SimFailure dictates we should.  This makes it easier
        // to test parse ordering, by permitting a wide range of element ids
        // to "succeed" without specifically supporting them.
        if (SimFailure::shouldFailOn(SimFailure::ftElementUnknown)) {
            isc_throw(DCfgMgrBaseError, "Configuration parameter not supported: "
                      << element_id);
        }

        parsed_order_.push_back(element_id);
        parser = new TestParser(element_id);
    }

    return (isc::dhcp::ParserPtr(parser));
}


}; // namespace isc::d2
}; // namespace isc
