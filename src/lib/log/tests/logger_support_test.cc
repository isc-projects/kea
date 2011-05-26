// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

/// \brief Example Program
///
/// Simple example program showing how to use the logger.

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <boost/lexical_cast.hpp>

#include <iostream>
#include <string>

#include <log/logger.h>
#include <log/logger_manager.h>
#include <log/logger_specification.h>
#include <log/macros.h>
#include <log/root_logger_name.h>

// Include a set of message definitions.
#include <log/messagedef.h>

using namespace isc::log;
using namespace std;


// Print usage information

void usage() {
    cout <<
"logger_support_test [-h] [-s severity] [-d dbglevel] [-c stream] [localfile]\n"
"\n"
"   -h              Print this message and exit\n"
"   -s severity     Set the severity of messages output.  'severity' is one\n"
"                   of 'debug', 'info', 'warn', 'error', 'fatal', the default\n"
"                   being 'info'.\n"
"   -d dbglevel     Debug level.  Only interpreted if the severity is 'debug'\n"
"                   this is a number between 0 and 99.\n"
"   -c stream       Send output to the console.  'stream' is one of 'stdout'\n"
"                   of 'stderr'.  The '-c' switch is incompatible with '-f'\n"
"                   and '-l'\n"
"\n"
"If none of -c, -f or -l is given, by default, output is sent to stdout\n";
}


// The program sets the attributes on the root logger and logs a set of
// messages.  Looking at the output determines whether the program worked.

int main(int argc, char** argv) {
    const string ROOT_NAME = "alpha";

    bool                c_found = false;    // Set true if "-c" found
    bool                f_found = false;    // Set true if "-f" found
    bool                l_found = false;    // Set true if "-l" found

    const char*         localfile = NULL;   // Local message file
    int                 option;             // For getopt() processing

    LoggerSpecification spec(ROOT_NAME);    // Logger specification
    OutputOption        outopt;             // Logger output option

    // Initialize loggers (to set the root name and initialize logging);
    // We'll reset them later.
    setRootLoggerName(ROOT_NAME);
    Logger rootLogger(ROOT_NAME);

    // Parse options
    while ((option = getopt(argc, argv, "hc:d:s:")) != -1) {
        switch (option) {
        case 'c':
            if (f_found || l_found) {
                cerr << "Cannot specify -c with -f or -l\n";
                return (1);
            }

            c_found = true;
            outopt.destination = OutputOption::DEST_CONSOLE;

            if (strcmp(optarg, "stdout") == 0) {
                outopt.stream = OutputOption::STR_STDOUT;

            } else if (strcmp(optarg, "stderr") == 0) {
                outopt.stream = OutputOption::STR_STDERR;

            } else {
                cerr << "Unrecognised console option: " << optarg << "\n";
                return (1);
            }
            break;

        case 'd':
            spec.setDbglevel(boost::lexical_cast<int>(optarg));
            break;

        case 'h':
            usage();
            return (0);

        case 's':
            if (strcmp(optarg, "debug") == 0) {
                spec.setSeverity(isc::log::DEBUG);

            } else if (strcmp(optarg, "info") == 0) {
                spec.setSeverity(isc::log::INFO);

            } else if (strcmp(optarg, "warn") == 0) {
                spec.setSeverity(isc::log::WARN);

            } else if (strcmp(optarg, "error") == 0) {
                spec.setSeverity(isc::log::ERROR);

            } else if (strcmp(optarg, "fatal") == 0) {
                spec.setSeverity(isc::log::FATAL);

            } else {
                cerr << "Unrecognised severity option: " << optarg << "\n";
                return (1);
            }
            break;

        default:
            std::cerr << "Unrecognised option: " <<
                static_cast<char>(option) << "\n";
            return (1);
        }
    }

    if (optind < argc) {
        localfile = argv[optind];
    }

    // Update the logging parameters
    LoggerManager::init(ROOT_NAME, localfile, isc::log::INFO, 0);

    // Set an output option if we have not done so already.
    if (! (c_found || f_found || l_found)) {
        outopt.destination = OutputOption::DEST_CONSOLE;
        outopt.stream = OutputOption::STR_STDOUT;
    }
    spec.addOutputOption(outopt);

    // Set the logging options for the root logger.
    LoggerManager manager;
    //manager.process(spec);


    // Log a few messages
    isc::log::Logger logger_dlm("dlm");
    isc::log::Logger logger_ex("example");
    LOG_FATAL(logger_ex, MSG_WRITERR).arg("test1").arg("42");
    LOG_ERROR(logger_ex, MSG_RDLOCMES).arg("dummy/file");
    LOG_WARN(logger_dlm, MSG_READERR).arg("a.txt").arg("dummy reason");
    LOG_INFO(logger_dlm, MSG_OPENIN).arg("example.msg").arg("dummy reason");
    LOG_DEBUG(logger_ex, 0, MSG_RDLOCMES).arg("dummy/0");
    LOG_DEBUG(logger_ex, 24, MSG_RDLOCMES).arg("dummy/24");
    LOG_DEBUG(logger_ex, 25, MSG_RDLOCMES).arg("dummy/25");
    LOG_DEBUG(logger_ex, 26, MSG_RDLOCMES).arg("dummy/26");

    return (0);
}
