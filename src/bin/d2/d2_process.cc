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

#include <config/ccsession.h>
#include <d2/d2_log.h>
#include <d2/d2_process.h>

using namespace asio;

namespace isc {
namespace d2 {

D2Process::D2Process(const char* name, IOServicePtr io_service)
    : DProcessBase(name, io_service) {
};

void
D2Process::init() {
};

void
D2Process::run() {
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
                       "Process run method failed: " << ex.what());
        }
    }

    LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2PRC_RUN_EXIT);
};

void
D2Process::shutdown() {
    LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2PRC_SHUTDOWN);
    setShutdownFlag(true);
}

isc::data::ConstElementPtr
D2Process::configure(isc::data::ConstElementPtr config_set) {
    // @TODO This is the initial implementation which simply accepts
    // any content in config_set as valid.  This is sufficient to
    // allow participation as a BIND10 module, while D2 configuration support
    // is being developed.
    LOG_DEBUG(d2_logger, DBGLVL_TRACE_BASIC,
              D2PRC_CONFIGURE).arg(config_set->str());

    return (isc::config::createAnswer(0, "Configuration accepted."));
}

isc::data::ConstElementPtr
D2Process::command(const std::string& command, isc::data::ConstElementPtr args){
    // @TODO This is the initial implementation.  If and when D2 is extended
    // to support its own commands, this implementation must change. Otherwise
    // it should reject all commands as it does now.
    LOG_DEBUG(d2_logger, DBGLVL_TRACE_BASIC,
              D2PRC_COMMAND).arg(command).arg(args->str());

    return (isc::config::createAnswer(COMMAND_INVALID, "Unrecognized command: "
                                      + command));
}

D2Process::~D2Process() {
};

}; // namespace isc::d2
}; // namespace isc
