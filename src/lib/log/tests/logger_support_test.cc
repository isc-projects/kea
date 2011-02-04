// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id: $

/// \brief Example Program
///
/// Simple example program showing how to use the logger.

#include <unistd.h>
#include <string.h>

#include <iostream>

#include <log/logger.h>
#include <log/logger_support.h>
#include <log/root_logger_name.h>

// Include a set of message definitions.
#include <log/messagedef.h>

using namespace isc::log;

// Declare root logger and a logger to use an example.
//RootLoggerName root_name("testing");

RootLoggerName root("alpha");
Logger logger_ex("example");
Logger logger_dlm("dlm");

// The program is invoked:
//
// logger_support_test [-s severity] [-d level ] [local_file]
//
// "severity" is one of "debug", "info", "warn", "error", "fatal"
// "level" is the debug level, a number between 0 and 99
// "local_file" is the name of a local file.
//
// The program sets the attributes on the root logger and logs a set of
// messages.  Looking at the output determines whether the program worked.

int main(int argc, char** argv) {

    isc::log::Severity  severity = isc::log::INFO;
    int                 dbglevel = -1;
    const char*         localfile = NULL;
    int                 option;

    // Parse options
    while ((option = getopt(argc, argv, "s:d:")) != -1) {
        switch (option) {
            case 's':
                if (strcmp(optarg, "debug") == 0) {
                    severity = isc::log::DEBUG;
                } else if (strcmp(optarg, "info") == 0) {
                    severity = isc::log::INFO;
                } else if (strcmp(optarg, "warn") == 0) {
                    severity = isc::log::WARN;
                } else if (strcmp(optarg, "error") == 0) {
                    severity = isc::log::ERROR;
                } else if (strcmp(optarg, "fatal") == 0) {
                    severity = isc::log::FATAL;
                } else {
                    std::cout << "Unrecognised severity option: " <<
                        optarg << "\n";
                    exit(1);
                }
                break;

            case 'd':
                dbglevel = atoi(optarg);
                break;

            default:
                std::cout << "Unrecognised option: " <<
                    static_cast<char>(option) << "\n";
        }
    }

    if (optind < argc) {
        localfile = argv[optind];
    }

    // Update the logging parameters
    runTimeInit(severity, dbglevel, localfile);

    // Log a few messages
    logger_ex.fatal(MSG_WRITERR, "test1", "42");
    logger_ex.error(MSG_UNRECDIR, "false");
    logger_dlm.warn(MSG_READERR, "a.txt", "dummy test");
    logger_dlm.info(MSG_OPENIN, "example.msg", "dummy test");
    logger_ex.debug(0, MSG_UNRECDIR, "[abc]");
    logger_ex.debug(24, MSG_UNRECDIR, "[24]");
    logger_ex.debug(25, MSG_UNRECDIR, "[25]");
    logger_ex.debug(26, MSG_UNRECDIR, "[26]");
    return 0;
}
