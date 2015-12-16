// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
#include <vector>

#include <util/strutil.h>

#include <log/logger.h>
#include <log/logger_level.h>
#include <log/logger_manager.h>
#include <log/logger_name.h>
#include <log/logger_specification.h>
#include <log/macros.h>

// Include a set of message definitions.
#include <log/log_messages.h>
#include <log/interprocess/interprocess_sync_null.h>

using namespace isc::log;
using namespace std;
using isc::log::interprocess::InterprocessSyncNull;

// Print usage information

void usage() {
    cout <<
"logger_support_test [-h | [logger_spec] [[logger_spec]...]]\n"
"\n"
"     -h            Print this message and exit\n"
"\n"
"The rest of the command line comprises the set of logger specifications.\n"
"Each specification is of the form:\n"
"\n"
"    -l logger  [-s severity] [-d dbglevel] output_spec] [[output_spec] ...\n"
"\n"
"where:\n"
"\n"
"    -l logger      Give the name of the logger to which the following\n"
"                   output specifications will apply.\n"
"\n"
"Each logger is followed by the indication of the severity it is logging\n"
"and, if applicable, its debug level:\n"
"\n"
"   -d dbglevel     Debug level.  Only interpreted if the severity is 'debug'\n"
"                   this is a number between 0 and 99.\n"
"   -s severity     Set the severity of messages output.  'severity' is one\n"
"                   of 'debug', 'info', 'warn', 'error', 'fatal', the default\n"
"                   being 'info'.\n"
"\n"
"The output specifications - there may be more than one per logger - detail\n"
"the output streams attached to the logger.  These are of the form:\n"
"\n"
"   -c stream | -f file [-m maxver] [-z maxsize] | -y facility\n"
"\n"
"These are:\n"
"\n"
"   -c stream       Send output to the console.  'stream' is one of 'stdout'\n"
"                   of 'stderr'.\n"
"   -f file         Send output to specified file, appending to existing file\n"
"                   if one exists.\n"
"   -y facility     Send output to the syslog file with the given facility\n"
"                   name (e.g. local1, cron etc.)\n"
"\n"
"The following can be specified for the file logger:\n"
"\n"
"   -m maxver       If file rolling is selected (by the maximum file size being\n"
"                   non-zero), the maximum number of versions to keep (defaults\n"
"                   to 0)\n"
"   -z maxsize      Maximum size of the file before the file is closed and a\n"
"                   new one opened.  The default of 0 means no maximum size.\n"
"\n"
"If none of -c, -f or -y is given, by default, output is sent to stdout.  If no\n"
"logger is specified, the default is the program's root logger ('example').\n";

}


// The program sets the attributes on the root logger and logs a set of
// messages.  Looking at the output determines whether the program worked.

int main(int argc, char** argv) {
    const char* ROOT_NAME = "example";

    bool                sw_found = false;   // Set true if switch found
    bool                c_found = false;    // Set true if "-c" found
    bool                f_found = false;    // Set true if "-f" found
    bool                y_found = false;    // Set true if "-y" found
    int                 option;             // For getopt() processing
    OutputOption        def_opt;            // Default output option - used
                                            //    for initialization
    LoggerSpecification cur_spec(ROOT_NAME);// Current specification
    OutputOption        cur_opt;            // Current output option
    vector<LoggerSpecification> loggers;    // Set of logger specifications
    std::string                 severity;   // Severity set for logger

    // Initialize logging system - set the root logger name.
    LoggerManager manager;
    manager.init(ROOT_NAME);

    // In the parsing loop that follows, the construction of the logging
    // specification is always "one behind".  In other words, the parsing of
    // command-line options updates thge current logging specification/output
    // options.  When the flag indicating a new logger or output specification
    // is encountered, the previous one is added to the list.
    //
    // One complication is that there is deemed to be a default active when
    // the parsing starts (console output for the Kea root logger).  This
    // is included in the logging specifications UNLESS the first switch on
    // the command line is a "-l" flag starting a new logger.  To track this,
    // the "sw_found" flag is set when a switch is completely processed. The
    // processing of "-l" will only add information for a previous logger to
    // the list if this flag is set.
    while ((option = getopt(argc, argv, "hc:d:f:l:m:s:y:z:")) != -1) {
        switch (option) {
        case 'c':   // Console output
            // New output spec.  If one was currently active, add it to the
            // list and reset the current output option to the defaults.
            if (c_found || f_found || y_found) {
                cur_spec.addOutputOption(cur_opt);
                cur_opt = def_opt;
                f_found = y_found = false;
            }

            // Set the output option for this switch.
            c_found = true;
            cur_opt.destination = OutputOption::DEST_CONSOLE;
            if (strcmp(optarg, "stdout") == 0) {
                cur_opt.stream = OutputOption::STR_STDOUT;

            } else if (strcmp(optarg, "stderr") == 0) {
                cur_opt.stream = OutputOption::STR_STDERR;

            } else {
                cerr << "Unrecognized console option: " << optarg << "\n";
                return (1);
            }
            break;

        case 'd':   // Debug level
            cur_spec.setDbglevel(boost::lexical_cast<int>(optarg));
            break;

        case 'f':   // File output specification
            // New output spec.  If one was currently active, add it to the
            // list and reset the current output option to the defaults.
            if (c_found || f_found || y_found) {
                cur_spec.addOutputOption(cur_opt);
                cur_opt = def_opt;
                c_found = y_found = false;
            }

            // Set the output option for this switch.
            f_found = true;
            cur_opt.destination = OutputOption::DEST_FILE;
            cur_opt.filename = optarg;
            break;

        case 'h':   // Help
            usage();
            return (0);

        case 'l':   // Logger
            // If a current specification is active, add the last output option
            // to it, add it to the list and reset.  A specification is active
            // if at least one switch has been previously found.
            if (sw_found) {
                cur_spec.addOutputOption(cur_opt);
                loggers.push_back(cur_spec);
                cur_spec.reset();
            }

            // Set the logger name
            cur_spec.setName(std::string(optarg));

            // Reset the output option to the default.
            cur_opt = def_opt;

            // Indicate nothing is found to prevent the console option (the
            // default output option) being added to the output list if an
            // output option is found.
            c_found = f_found = y_found = false;
            break;

        case 'm':   // Maximum file version
            if (!f_found) {
                std::cerr << "Attempt to set maximum version (-m) "
                             "outside of file output specification\n";
                return (1);
            }
            try {
                cur_opt.maxver = boost::lexical_cast<unsigned int>(optarg);
            } catch (boost::bad_lexical_cast&) {
                std::cerr << "Maximum version (-m) argument must be a positive "
                             "integer\n";
                return (1);
            }
            break;

        case 's':   // Severity
            severity = optarg;
            isc::util::str::uppercase(severity);
            cur_spec.setSeverity(getSeverity(severity));
            break;

        case 'y':   // Syslog output
            // New output spec.  If one was currently active, add it to the
            // list and reset the current output option to the defaults.
            if (c_found || f_found || y_found) {
                cur_spec.addOutputOption(cur_opt);
                cur_opt = def_opt;
                c_found = f_found = false;
            }
            y_found = true;
            cur_opt.destination = OutputOption::DEST_SYSLOG;
            cur_opt.facility = optarg;
            break;

        case 'z':   // Maximum size
            if (! f_found) {
                std::cerr << "Attempt to set file size (-z) "
                             "outside of file output specification\n";
                return (1);
            }
            try {
                cur_opt.maxsize = boost::lexical_cast<size_t>(optarg);
            } catch (boost::bad_lexical_cast&) {
                std::cerr << "File size (-z) argument must be a positive "
                             "integer\n";
                return (1);
            }
            break;


        default:
            std::cerr << "Unrecognized option: " <<
                static_cast<char>(option) << "\n";
            return (1);
        }

        // Have found at least one command-line switch, so note the fact.
        sw_found = true;
    }

    // Add the current (unfinished specification) to the list.
    cur_spec.addOutputOption(cur_opt);
    loggers.push_back(cur_spec);

    // Set the logging options.
    manager.process(loggers.begin(), loggers.end());

    // Set the local file
    if (optind < argc) {
        LoggerManager::readLocalMessageFile(argv[optind]);
    }

    // Log a few messages to different loggers. Here, we switch to using
    // null interprocess sync objects for the loggers below as the
    // logger example can be used as a standalone program (which may not
    // have write access to a local state directory to create
    // lockfiles).
    isc::log::Logger logger_ex(ROOT_NAME);
    logger_ex.setInterprocessSync(new InterprocessSyncNull("logger"));
    isc::log::Logger logger_alpha("alpha");
    logger_alpha.setInterprocessSync(new InterprocessSyncNull("logger"));
    isc::log::Logger logger_beta("beta");
    logger_beta.setInterprocessSync(new InterprocessSyncNull("logger"));

    LOG_FATAL(logger_ex, LOG_WRITE_ERROR).arg("test1").arg("42");
    LOG_ERROR(logger_ex, LOG_READING_LOCAL_FILE).arg("dummy/file");
    LOG_WARN(logger_ex, LOG_BAD_STREAM).arg("example");
    LOG_WARN(logger_alpha, LOG_READ_ERROR).arg("a.txt").arg("dummy reason");
    LOG_INFO(logger_alpha, LOG_INPUT_OPEN_FAIL).arg("example.msg").arg("dummy reason");
    LOG_DEBUG(logger_ex, 0, LOG_READING_LOCAL_FILE).arg("example/0");
    LOG_DEBUG(logger_ex, 24, LOG_READING_LOCAL_FILE).arg("example/24");
    LOG_DEBUG(logger_ex, 25, LOG_READING_LOCAL_FILE).arg("example/25");
    LOG_DEBUG(logger_ex, 26, LOG_READING_LOCAL_FILE).arg("example/26");
    LOG_FATAL(logger_beta, LOG_BAD_SEVERITY).arg("beta_fatal");
    LOG_ERROR(logger_beta, LOG_BAD_DESTINATION).arg("beta_error");
    LOG_WARN(logger_beta, LOG_BAD_STREAM).arg("beta_warn");
    LOG_INFO(logger_beta, LOG_READ_ERROR).arg("beta").arg("info");
    LOG_DEBUG(logger_beta, 25, LOG_BAD_SEVERITY).arg("beta/25");
    LOG_DEBUG(logger_beta, 26, LOG_BAD_SEVERITY).arg("beta/26");

    return (0);
}
