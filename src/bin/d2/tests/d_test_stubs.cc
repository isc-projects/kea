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

#include <d2/spec_config.h>
#include <d2/tests/d_test_stubs.h>

using namespace asio;

namespace isc {
namespace d2 {

SimFailure::FailureType SimFailure::failure_type_ = SimFailure::ftNoFailure;

const std::string DStubProcess::custom_process_command_("valid_prc_command");

DStubProcess::DStubProcess(const char* name, IOServicePtr io_service) 
    : DProcessBase(name, io_service) {
};

void
DStubProcess::init() {
    if (SimFailure::shouldFailOn(SimFailure::ftProcessInit)) {
        // Simulates a failure to instantiate the process. 
        isc_throw(DProcessBaseError, "DStubProcess simulated init failure");
    }
};

int
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
            return (EXIT_FAILURE); 
        }
    }

    LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2PRC_RUN_EXIT);
    return (EXIT_SUCCESS);
};

int 
DStubProcess::shutdown() {
    LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2PRC_SHUTDOWN);
    setShutdownFlag(true);
    return (0);
}    

isc::data::ConstElementPtr 
DStubProcess::configure(isc::data::ConstElementPtr config_set) {
    LOG_DEBUG(d2_logger, DBGLVL_TRACE_BASIC, 
              D2PRC_CONFIGURE).arg(config_set->str());

    if (SimFailure::shouldFailOn(SimFailure::ftProcessConfigure)) {
        return (isc::config::createAnswer(1,
                "Simulated process configuration error."));
    }

    return (isc::config::createAnswer(0, "Configuration accepted."));
}

isc::data::ConstElementPtr 
DStubProcess::command(const std::string& command, isc::data::ConstElementPtr args){
    LOG_DEBUG(d2_logger, DBGLVL_TRACE_BASIC, 
              D2PRC_COMMAND).arg(command).arg(args->str());

    isc::data::ConstElementPtr answer;
    if (SimFailure::shouldFailOn(SimFailure::ftProcessCommand)) {
        answer = isc::config::createAnswer(COMMAND_ERROR,
                                          "SimFailure::ftProcessCommand");
    } else if (command.compare(custom_process_command_) == 0) {
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

const std::string DStubController::custom_ctl_command_("valid_ctrl_command");

DControllerBasePtr&
DStubController::instance() {
    if (!getController()) {
        setController(new DStubController());
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
    // Default implementation returns false
    if (option == 'x') {
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
        answer = isc::config::createAnswer(COMMAND_ERROR,
                                          "SimFailure::ftControllerCommand");
    } else if (command.compare(custom_ctl_command_) == 0) {
        answer = isc::config::createAnswer(COMMAND_SUCCESS, "Command accepted");
    } else {
        answer = isc::config::createAnswer(COMMAND_INVALID,
                                           "Unrecognized command:" + command);
    }

    return (answer);
}

const std::string DStubController::getCustomOpts(){
    return (std::string("x"));
}

DStubController::~DStubController() {
}

DControllerBasePtr DControllerTest::controller_under_test_;
DControllerTest::InstanceGetter DControllerTest::instanceGetter_ = NULL;

}; // namespace isc::d2 
}; // namespace isc
