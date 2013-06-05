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

// Initialize the static failure flag.
SimFailure::FailureType SimFailure::failure_type_ = SimFailure::ftNoFailure;

// Define custom process command supported by DStubProcess.
const char*  DStubProcess::stub_proc_command_("cool_proc_cmd");

DStubProcess::DStubProcess(const char* name, IOServicePtr io_service)
    : DProcessBase(name, io_service) {
};

void
DStubProcess::init() {
    LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2PRC_PROCESS_INIT);
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
    LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2PRC_RUN_ENTER);
    IOServicePtr& io_service = getIoService();
    while (!shouldShutdown()) {
        try {
            io_service->run_one();
        } catch (const std::exception& ex) {
            LOG_FATAL(d2_logger, D2PRC_FAILED).arg(ex.what());
            isc_throw (DProcessBaseError,
                std::string("Process run method failed:") + ex.what());
        }
    }

    LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2PRC_RUN_EXIT);
};

void
DStubProcess::shutdown() {
    LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2PRC_SHUTDOWN);
    if (SimFailure::shouldFailOn(SimFailure::ftProcessShutdown)) {
        // Simulates a failure during shutdown process.
        isc_throw(DProcessBaseError, "DStubProcess simulated shutdown failure");
    }

    DProcessBase::shutdown();
}

isc::data::ConstElementPtr
DStubProcess::configure(isc::data::ConstElementPtr config_set) {
    LOG_DEBUG(d2_logger, DBGLVL_TRACE_BASIC,
              D2PRC_CONFIGURE).arg(config_set->str());

    if (SimFailure::shouldFailOn(SimFailure::ftProcessConfigure)) {
        // Simulates a process configure failure.
        return (isc::config::createAnswer(1,
                "Simulated process configuration error."));
    }

    return (isc::config::createAnswer(0, "Configuration accepted."));
}

isc::data::ConstElementPtr
DStubProcess::command(const std::string& command,
                      isc::data::ConstElementPtr args) {
    LOG_DEBUG(d2_logger, DBGLVL_TRACE_BASIC,
              D2PRC_COMMAND).arg(command).arg(args->str());

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

DControllerBasePtr&
DStubController::instance() {
    // If the singleton hasn't been created, do it now.
    if (!getController()) {
        //setController(new DStubController());
        DControllerBasePtr p(new DStubController());
        setController(p);
    }

    return (getController());
}

DStubController::DStubController()
    : DControllerBase(D2_MODULE_NAME) {

    if (getenv("B10_FROM_BUILD")) {
        setSpecFileName(std::string(getenv("B10_FROM_BUILD")) +
            "/src/bin/d2/d2.spec");
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
    return (new DStubProcess(getName().c_str(), getIOService()));
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

}; // namespace isc::d2
}; // namespace isc
