// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
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
#include <log/logger_level.h>
#include <log/logger_name.h>
#include <log/logger_manager.h>
#include <log/logger_specification.h>
#include <log/logger_support.h>
#include <log/output_option.h>
#include <dhcpsrv/daemon.h>
#include <exceptions/exceptions.h>
#include <fstream>
#include <errno.h>

/// @brief provides default implementation for basic daemon operations
/// 
/// This file provides stub implementations that are expected to be redefined
/// in derived classes (e.g. ControlledDhcpv6Srv)
namespace isc {
namespace dhcp {

Daemon::Daemon() {
}

bool Daemon::init(const std::string&) {
    return false;
}

void Daemon::cleanup() {

}

void Daemon::shutdown() {

}

Daemon::~Daemon() {
}

std::string Daemon::readFile(const std::string& file_name) {

    // This is the fastest method to read a file according to:
    // http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html

    std::ifstream infile(file_name.c_str(), std::ios::in | std::ios::binary);
    if (infile.is_open())
    {
        std::string contents;
        infile.seekg(0, std::ios::end);
        contents.resize(infile.tellg());
        infile.seekg(0, std::ios::beg);
        infile.read(&contents[0], contents.size());
        infile.close();
        return(contents);
    }
    isc_throw(InvalidOperation, "Failed to read file " << file_name << ",error:"
              << errno);
}

void Daemon::loggerInit(const char* log_name, bool verbose, bool ) {
    // This method configures logger. For now it is very simple.
    // We'll make it more robust once we add support for JSON-based logging
    // configuration.

    using namespace isc::log;

    Severity severity = b10LoggerSeverity(verbose ? isc::log::DEBUG : isc::log::INFO);

    // Set a directory for creating lockfiles when running tests
    // @todo: Find out why this is needed. Without this, the logger doesn't
    // work.
    setenv("B10_LOCKFILE_DIR_FROM_BUILD", TOP_BUILDDIR, 1);
    
    // Initialize logging
    initLogger(log_name, severity, isc::log::MAX_DEBUG_LEVEL, NULL);

    // Now configure logger output to stdout.
    /// @todo: Make this configurable as part of #3427.
    LoggerSpecification spec(log_name, severity,
                             b10LoggerDbglevel(isc::log::MAX_DEBUG_LEVEL));
    OutputOption option;
    option.destination = OutputOption::DEST_CONSOLE;
    option.stream = OutputOption::STR_STDOUT;

    spec.addOutputOption(option);
    LoggerManager manager;
    manager.process(spec);
}

};
};
