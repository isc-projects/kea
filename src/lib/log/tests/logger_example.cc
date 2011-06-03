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
/// Simple example program showing how to use the logger.  The various
/// command-line options let most aspects of the logger be exercised, so
/// making this a useful tool for testing.
///
/// See the usage() method for details of use.

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <boost/lexical_cast.hpp>

#include <iostream>
#include <string>

#include <util/strutil.h>

#include <log/logger.h>
#include <log/logger_level.h>
#include <log/logger_manager.h>
#include <log/logger_name.h>
#include <log/logger_specification.h>
#include <log/macros.h>

// Include a set of message definitions.
#include <log/messagedef.h>

using namespace isc::log;
using namespace std;


// Print usage information

void usage() {
    cout <<
"logger_support_test [-h] [-c stream] [-d dbglevel] [-f file]\n"
"                    [-s severity] [localfile]\n"
"\n"
"   -h              Print this message and exit\n"
"\n"
"   -d dbglevel     Debug level.  Only interpreted if the severity is 'debug'\n"
"                   this is a number between 0 and 99.\n"
"   -c stream       Send output to the console.  'stream' is one of 'stdout'\n"
"                   of 'stderr'.  The '-c' switch is incompatible with '-f'\n"
"                   and '-l'\n"
"   -f file         Send output to specified file, appending to existing file\n"
"                   if one exists.  Incompatible with -c and -l switches.\n"
"   -s severity     Set the severity of messages output.  'severity' is one\n"
"                   of 'debug', 'info', 'warn', 'error', 'fatal', the default\n"
"                   being 'info'.\n"
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

    int                 option;             // For getopt() processing

    LoggerSpecification spec(ROOT_NAME);    // Logger specification
    OutputOption        outopt;             // Logger output option

    // Initialize loggers (to set the root name and initialize logging);
    LoggerManager::init(ROOT_NAME);

    // Parse options
    while ((option = getopt(argc, argv, "hc:d:f:s:")) != -1) {
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

        case 'f':
            if (c_found || l_found) {
                cerr << "Cannot specify -f with -c or -l\n";
                return (1);
            }

            f_found = true;

            outopt.destination = OutputOption::DEST_FILE;
            outopt.filename = optarg;
            break;

        case 'h':
            usage();
            return (0);

        case 's':
            {
                string severity(optarg);
                isc::util::str::uppercase(severity);
                spec.setSeverity(getSeverity(severity));
            }
            break;

        default:
            std::cerr << "Unrecognised option: " <<
                static_cast<char>(option) << "\n";
            return (1);
        }
    }

    // Update the logging parameters.  If no output options
    // were set, the defaults will be used.
    spec.addOutputOption(outopt);

    // Set the logging options for the root logger.
    LoggerManager manager;
    manager.process(spec);

    // Set the local file
    if (optind < argc) {
        LoggerManager::readLocalMessageFile(argv[optind]);
    }


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
