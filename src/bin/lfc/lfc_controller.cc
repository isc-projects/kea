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

#include <lfc/lfc_controller.h>
#include <util/pid_file.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/csv_lease_file4.h>
#include <dhcpsrv/csv_lease_file6.h>
#include <dhcpsrv/memfile_lease_storage.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_file_loader.h>
#include <config.h>

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdlib.h>
#include <cerrno>

using namespace std;
using namespace isc::util;
using namespace isc::dhcp;

namespace isc {
namespace lfc {

/// @brief Defines the application name, it may be used to locate
/// configuration data and appears in log statements.
const char* LFCController::lfc_app_name_ = "DhcpLFC";

/// @brief Defines the executable name.
const char* LFCController::lfc_bin_name_ = "kea-lfc";

/// @brief Maximum number of errors to allow when reading leases from the file.
const uint32_t MAX_LEASE_ERRORS = 100;

LFCController::LFCController()
    : protocol_version_(0), verbose_(false), config_file_(""), previous_file_(""),
      copy_file_(""), output_file_(""), finish_file_(""), pid_file_("") {
}

LFCController::~LFCController() {
}

void
LFCController::launch(int argc, char* argv[]) {
    bool do_clean = true;

    try {
        parseArgs(argc, argv);
    } catch (const InvalidUsage& ex) {
        usage(ex.what());
        throw;  // rethrow it
    }

    if (verbose_ == true)
        std::cerr << "Starting lease file cleanup" << std::endl;

    // verify we are the only instance
    PIDFile pid_file(pid_file_);

    try {
        if (pid_file.check() == true) {
            // Already running instance, bail out
            std::cerr << "LFC instance already running" <<  std::endl;
            return;
        }
    } catch (const PIDFileError& pid_ex) {
        std::cerr << pid_ex.what() << std::endl;
        return;
    }

    // create the pid file for this instance
    try {
        pid_file.write();
    } catch (const PIDFileError& pid_ex) {
        std::cerr << pid_ex.what() << std::endl;
        return;
    }

    // If we don't have a finish file do the processing
    if (access(finish_file_.c_str(), F_OK) == -1) {
        if (verbose_ == true)
            std::cerr << "LFC Processing files" << std::endl;

        try {
            if (protocol_version_ == 4) {
                processLeases<Lease4, CSVLeaseFile4, Lease4Storage>();
            } else {
                processLeases<Lease6, CSVLeaseFile6, Lease6Storage>();
            }
        } catch (const isc::Exception& proc_ex) {
            // We don't want to do the cleanup but do want to get rid of the pid
            do_clean = false;
            std::cerr << "Processing failed: " << proc_ex.what() << std::endl;
        }
    }

    // If do_clean is true We either already had a finish file or
    // were able to create one.  We now want to do the file cleanup,
    // we don't want to return after the catch as we
    // still need to cleanup the pid file
    if (do_clean == true) {
        if (verbose_ == true)
            std::cerr << "LFC cleaning files" << std::endl;
        try {
            fileCleanup();
        } catch (const RunTimeFail& run_ex) {
            std::cerr << run_ex.what() << std::endl;
        }
    }

    // delete the pid file for this instance
    try {
        pid_file.deleteFile();
    } catch (const PIDFileError& pid_ex) {
        std::cerr << pid_ex.what() << std::endl;
    }

    if (verbose_ == true)
        std::cerr << "LFC complete" << std::endl;
}

void
LFCController::parseArgs(int argc, char* argv[]) {
    int ch;

    opterr = 0;
    optind = 1;
    while ((ch = getopt(argc, argv, ":46dvVp:x:i:o:c:f:")) != -1) {
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
    if (verbose_ == true) {
        std::cerr << "Protocol version:    DHCPv" << protocol_version_ << std::endl
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
    if (text != "") {
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
        version_stream << std::endl << EXTENDED_VERSION;
    }

    return (version_stream.str());
}

template<typename LeaseObjectType, typename LeaseFileType, typename StorageType>
void
LFCController::processLeases() const {
    LeaseFileType lf_prev(previous_file_.c_str());
    LeaseFileType lf_copy(copy_file_.c_str());
    LeaseFileType lf_output(output_file_.c_str());
    StorageType storage;
    storage.clear();

    // If a previous file exists read the entries into storage
    if (lf_prev.exists()) {
        LeaseFileLoader::load<LeaseObjectType>(lf_prev, storage,
                                               MAX_LEASE_ERRORS);
    }

    // Follow that with the copy of the current lease file
    if (lf_copy.exists()) {
        LeaseFileLoader::load<LeaseObjectType>(lf_copy, storage,
                                               MAX_LEASE_ERRORS);
    }

    // Write the result out to the output file
    LeaseFileLoader::write<LeaseObjectType>(lf_output, storage);

    // Once we've finished the output file move it to the complete file
    if (rename(output_file_.c_str(), finish_file_.c_str()) != 0)
        isc_throw(RunTimeFail, "Unable to move output (" << output_file_
                  << ") to complete (" << finish_file_
                  << ") error: " << strerror(errno));
}

void
LFCController::fileCleanup() const {
    // Remove the old previous file
    if ((remove(previous_file_.c_str()) != 0) &&
        (errno != ENOENT)) {
        isc_throw(RunTimeFail, "Unable to delete previous file '"
                  << previous_file_ << "' error: " << strerror(errno));
    }

    // Remove the copy file
    if ((remove(copy_file_.c_str()) != 0) &&
        (errno != ENOENT)) {
        isc_throw(RunTimeFail, "Unable to delete copy file '"
                  << copy_file_ << "' error: " << strerror(errno));
    }

    // Rename the finish file to be the previous file
    if (rename(finish_file_.c_str(), previous_file_.c_str()) != 0)
        isc_throw(RunTimeFail, "Unable to move finish (" << finish_file_
                  << ") to previous (" << previous_file_
                  << ") error: " << strerror(errno));
}
}; // namespace isc::lfc
}; // namespace isc
