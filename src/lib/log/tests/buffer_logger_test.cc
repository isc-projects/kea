// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <log/macros.h>
#include <log/logger_support.h>
#include <log/logger_manager.h>
#include <log/log_messages.h>
#include <log/interprocess/interprocess_sync_null.h>

using namespace isc::log;

namespace {
void usage() {
    std::cout << "Usage: buffer_logger_test [-n]" << std::endl;
}
} // end unnamed namespace

/// \brief Test InitLogger
///
/// A program used in testing the logger that initializes logging with
/// buffering enabled, so that initial log messages are not immediately
/// logged, but are not lost (they should be logged the moment process()
/// is called.
///
/// If -n is given as an argument, process() is never called. In this
/// case, upon exit, all leftover log messages should be printed to
/// stdout, but without normal logging additions (such as time and
/// logger name)
int
main(int argc, char** argv) {
    bool do_process = true;
    int opt;
    while ((opt = getopt(argc, argv, "n")) != -1) {
        switch (opt) {
        case 'n':
            do_process = false;
            break;
        default:
            usage();
            return (1);
        }
    }

    // Note, level is INFO, so DEBUG should normally not show
    // up. Unless process is never called (at which point it
    // will end up in the dump at the end).
    initLogger("buffertest", isc::log::INFO, 0, NULL, true);
    Logger logger("log");
    // No need for file interprocess locking in this test
    logger.setInterprocessSync(
        new isc::log::interprocess::InterprocessSyncNull("logger"));
    LOG_INFO(logger, LOG_BAD_SEVERITY).arg("info");
    LOG_DEBUG(logger, 50, LOG_BAD_DESTINATION).arg("debug-50");
    LOG_INFO(logger, LOG_BAD_SEVERITY).arg("info");
    // process should cause them to be logged
    if (do_process) {
        LoggerManager logger_manager;
        logger_manager.process();
    }
    return (0);
}
