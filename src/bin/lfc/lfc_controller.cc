// Copyright (C) 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <lfc/lfc_controller.h>
#include <lfc/lfc_log.h>
#include <util/pid_file.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/csv_lease_file4.h>
#include <dhcpsrv/csv_lease_file6.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <dhcpsrv/memfile_lease_storage.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_file_loader.h>
#include <log/logger_manager.h>
#include <log/logger_name.h>
#include <cfgrpt/config_report.h>

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdlib.h>
#include <cerrno>

using namespace std;
using namespace isc::util;
using namespace isc::dhcp;
using namespace isc::log;

namespace {
/// @brief Maximum number of errors to allow when reading leases from the file.
const uint32_t MAX_LEASE_ERRORS = 100;
}; // namespace anonymous

namespace isc {
namespace lfc {

// Refer to config_report so it will be embedded in the binary
const char* const* lfc_config_report = isc::detail::config_report;

/// @brief Defines the application name, it may be used to locate
/// configuration data and appears in log statements.
const char* LFCController::lfc_app_name_ = "DhcpLFC";

/// @brief Defines the executable name.
const char* LFCController::lfc_bin_name_ = "kea-lfc";

LFCController::LFCController()
    : protocol_version_(0), verbose_(false), config_file_(""), previous_file_(""),
      copy_file_(""), output_file_(""), finish_file_(""), pid_file_("") {
}

LFCController::~LFCController() {
}

void
LFCController::launch(int argc, char* argv[], const bool test_mode) {
    bool do_rotate = true;

    // It would be nice to set up the logger as the first step
    // in the process, but we don't know where to send logging
    // info until after we have parsed our arguments.  As we
    // don't currently log anything when trying to parse the
    // arguments we do the parse before the logging setup.  If
    // we do decide to log something then the code will need
    // to move around a bit.

    try {
        parseArgs(argc, argv);
    } catch (const InvalidUsage& ex) {
        usage(ex.what());
        throw;  // rethrow it
    }

    // Start up the logging system.
    startLogger(test_mode);

    LOG_INFO(lfc_logger, LFC_START);

    // verify we are the only instance
    PIDFile pid_file(pid_file_);

    try {
        if (pid_file.check()) {
            // Already running instance, bail out
            LOG_FATAL(lfc_logger, LFC_RUNNING);
            return;
        }

        // create the pid file for this instance
        pid_file.write();
    } catch (const PIDFileError& pid_ex) {
        LOG_FATAL(lfc_logger, LFC_FAIL_PID_CREATE).arg(pid_ex.what());
        return;
    }

    // If we don't have a finish file do the processing.  We
    // don't know the exact type of the finish file here but
    // all we care about is if it exists so that's okay
    CSVFile lf_finish(getFinishFile());
    if (!lf_finish.exists()) {
        LOG_INFO(lfc_logger, LFC_PROCESSING)
          .arg(previous_file_)
          .arg(copy_file_);

        try {
            if (getProtocolVersion() == 4) {
                processLeases<Lease4, CSVLeaseFile4, Lease4Storage>();
            } else {
                processLeases<Lease6, CSVLeaseFile6, Lease6Storage>();
            }
        } catch (const std::exception& proc_ex) {
            // We don't want to do the cleanup but do want to get rid of the pid
            do_rotate = false;
            LOG_FATAL(lfc_logger, LFC_FAIL_PROCESS).arg(proc_ex.what());
        }
    }

    // If do_rotate is true We either already had a finish file or
    // were able to create one.  We now want to do the file cleanup,
    // we don't want to return after the catch as we
    // still need to cleanup the pid file
    if (do_rotate) {
        LOG_INFO(lfc_logger, LFC_ROTATING);

        try {
            fileRotate();
        } catch (const RunTimeFail& run_ex) {
          LOG_FATAL(lfc_logger, LFC_FAIL_ROTATE).arg(run_ex.what());
        }
    }

    // delete the pid file for this instance
    try {
        pid_file.deleteFile();
    } catch (const PIDFileError& pid_ex) {
          LOG_FATAL(lfc_logger, LFC_FAIL_PID_DEL).arg(pid_ex.what());
    }

    LOG_INFO(lfc_logger, LFC_TERMINATE);
}

void
LFCController::parseArgs(int argc, char* argv[]) {
    int ch;

    opterr = 0;
    optind = 1;
    while ((ch = getopt(argc, argv, ":46dvVWp:x:i:o:c:f:")) != -1) {
        switch (ch) {
        case '4':
            // Process DHCPv4 lease files.
            protocol_version_ = 4;
            break;

        case '6':
            // Process DHCPv6 lease files.
            protocol_version_ = 6;
            break;

        case 'v':
            // Print just Kea vesion and exit.
            std::cout << getVersion(false) << std::endl;
            exit(EXIT_SUCCESS);

        case 'V':
            // Print extended  Kea vesion and exit.
            std::cout << getVersion(true) << std::endl;
            exit(EXIT_SUCCESS);

        case 'W':
            // Display the configuration report and exit.
            std::cout << isc::detail::getConfigReport() << std::endl;
            exit(EXIT_SUCCESS);

        case 'd':
            // Verbose output.
            verbose_ = true;
            break;

        case 'p':
            // PID file name.
            if (optarg == NULL) {
                isc_throw(InvalidUsage, "PID file name missing");
            }
            pid_file_ = optarg;
            break;

        case 'x':
            // Previous (or ex) file name.
            if (optarg == NULL) {
                isc_throw(InvalidUsage, "Previous (ex) file name missing");
            }
            previous_file_ = optarg;
            break;

        case 'i':
            // Copy file name.
            if (optarg == NULL) {
                isc_throw(InvalidUsage, "Copy file name missing");
            }
            copy_file_ = optarg;
            break;

        case 'o':
            // Output file name.
            if (optarg == NULL) {
                isc_throw(InvalidUsage, "Output file name missing");
            }
            output_file_ = optarg;
            break;

        case 'f':
            // Finish file name.
            if (optarg == NULL) {
                isc_throw(InvalidUsage, "Finish file name missing");
            }
            finish_file_ = optarg;
            break;

        case 'c':
            // Configuration file name
            if (optarg == NULL) {
                isc_throw(InvalidUsage, "Configuration file name missing");
            }
            config_file_ = optarg;
            break;

        case 'h':
            usage("");
            exit(EXIT_SUCCESS);

        case '?':
            // Unknown argument
            isc_throw(InvalidUsage, "Unknown argument");

        case ':':
            // Missing option argument
            isc_throw(InvalidUsage, "Missing option argument");

        default:
            // I don't think we should get here as the unknown arguments
            // and missing options cases should cover everything else
            isc_throw(InvalidUsage, "Invalid command line");
        }
    }

    // Check for extraneous parameters.
    if (argc > optind) {
        isc_throw(InvalidUsage, "Extraneous parameters.");
    }

    if (protocol_version_ == 0) {
        isc_throw(InvalidUsage, "DHCP version required");
    }

    if (pid_file_.empty()) {
        isc_throw(InvalidUsage, "PID file not specified");
    }

    if (previous_file_.empty()) {
        isc_throw(InvalidUsage, "Previous file not specified");
    }

    if (copy_file_.empty()) {
        isc_throw(InvalidUsage, "Copy file not specified");
    }

    if (output_file_.empty()) {
        isc_throw(InvalidUsage, "Output file not specified");
    }

    if (finish_file_.empty()) {
        isc_throw(InvalidUsage, "Finish file not specified");
    }

    if (config_file_.empty()) {
        isc_throw(InvalidUsage, "Config file not specified");
    }

    // If verbose is set echo the input information
    if (verbose_) {
        std::cout << "Protocol version:    DHCPv" << protocol_version_ << std::endl
                  << "Previous or ex lease file: " << previous_file_ << std::endl
                  << "Copy lease file:           " << copy_file_ << std::endl
                  << "Output lease file:         " << output_file_ << std::endl
                  << "Finish file:               " << finish_file_ << std::endl
                  << "Config file:               " << config_file_ << std::endl
                  << "PID file:                  " << pid_file_ << std::endl
                  << std::endl;
    }
}

void
LFCController::usage(const std::string& text) {
    if (!text.empty()) {
        std::cerr << "Usage error: " << text << std::endl;
    }

    std::cerr << "Usage: " << lfc_bin_name_ << std::endl
              << " [-4|-6] -p file -x file -i file -o file -f file -c file" << std::endl
              << "   -4 or -6 clean a set of v4 or v6 lease files" << std::endl
              << "   -p <file>: PID file" << std::endl
              << "   -x <file>: previous or ex lease file" << std::endl
              << "   -i <file>: copy of lease file" << std::endl
              << "   -o <file>: output lease file" << std::endl
              << "   -f <file>: finish file" << std::endl
              << "   -c <file>: configuration file" << std::endl
              << "   -v: print version number and exit" << std::endl
              << "   -V: print extended version inforamtion and exit" << std::endl
              << "   -d: optional, verbose output " << std::endl
              << "   -h: print this message " << std::endl
              << std::endl;
}

std::string
LFCController::getVersion(const bool extended) const{
    std::stringstream version_stream;

    version_stream << VERSION;
    if (extended) {
        version_stream << std::endl << EXTENDED_VERSION << std::endl
        << "database: " << isc::dhcp::Memfile_LeaseMgr::getDBVersion();
    }

    return (version_stream.str());
}

template<typename LeaseObjectType, typename LeaseFileType, typename StorageType>
void
LFCController::processLeases() const {
    StorageType storage;

    // If a previous file exists read the entries into storage
    LeaseFileType lf_prev(getPreviousFile());
    if (lf_prev.exists()) {
        LeaseFileLoader::load<LeaseObjectType>(lf_prev, storage,
                                               MAX_LEASE_ERRORS);
    }

    // Follow that with the copy of the current lease file
    LeaseFileType lf_copy(getCopyFile());
    if (lf_copy.exists()) {
        LeaseFileLoader::load<LeaseObjectType>(lf_copy, storage,
                                               MAX_LEASE_ERRORS);
    }

    // Write the result out to the output file
    LeaseFileType lf_output(getOutputFile());
    LeaseFileLoader::write<LeaseObjectType>(lf_output, storage);

    // If desired log the stats
    LOG_INFO(lfc_logger, LFC_READ_STATS)
      .arg(lf_prev.getReadLeases() + lf_copy.getReadLeases())
      .arg(lf_prev.getReads() + lf_copy.getReads())
      .arg(lf_prev.getReadErrs() + lf_copy.getReadErrs());

    LOG_INFO(lfc_logger, LFC_WRITE_STATS)
      .arg(lf_output.getWriteLeases())
      .arg(lf_output.getWrites())
      .arg(lf_output.getWriteErrs());

    // Once we've finished the output file move it to the complete file
    if (rename(getOutputFile().c_str(), getFinishFile().c_str()) != 0) {
        isc_throw(RunTimeFail, "Unable to move output (" << output_file_
                  << ") to complete (" << finish_file_
                  << ") error: " << strerror(errno));
    }
}

void
LFCController::fileRotate() const {
    // Remove the old previous file
    if ((remove(getPreviousFile().c_str()) != 0) &&
        (errno != ENOENT)) {
        isc_throw(RunTimeFail, "Unable to delete previous file '"
                  << previous_file_ << "' error: " << strerror(errno));
    }

    // Remove the copy file
    if ((remove(getCopyFile().c_str()) != 0) &&
        (errno != ENOENT)) {
        isc_throw(RunTimeFail, "Unable to delete copy file '"
                  << copy_file_ << "' error: " << strerror(errno));
    }

    // Rename the finish file to be the previous file
    if (rename(finish_file_.c_str(), previous_file_.c_str()) != 0) {
        isc_throw(RunTimeFail, "Unable to move finish (" << finish_file_
                  << ") to previous (" << previous_file_
                  << ") error: " << strerror(errno));
    }
}

void
LFCController::startLogger(const bool test_mode) const {
    // If we are running in test mode use the environment variables
    // else use our defaults
    if (test_mode) {
        initLogger();
    }
    else {
        OutputOption option;
        LoggerManager manager;

        initLogger(lfc_app_name_, INFO, 0, NULL, false);

        // Prepare the objects to define the logging specification
        LoggerSpecification spec(getRootLoggerName(),
                                 keaLoggerSeverity(INFO),
                                 keaLoggerDbglevel(0));

        // If we are running in verbose (debugging) mode
        // we send the output to the console, otherwise
        // by default we send it to the SYSLOG
        if (verbose_) {
            option.destination = OutputOption::DEST_CONSOLE;
        } else {
            option.destination = OutputOption::DEST_SYSLOG;
        }

        // ... and set the destination
        spec.addOutputOption(option);

        manager.process(spec);
    }
}

}; // namespace isc::lfc
}; // namespace isc
