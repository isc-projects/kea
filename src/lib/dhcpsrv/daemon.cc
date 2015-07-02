// Copyright (C) 2014, 2015  Internet Systems Consortium, Inc. ("ISC")
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
#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/daemon.h>
#include <exceptions/exceptions.h>
#include <log/logger_name.h>
#include <log/logger_support.h>
#include <logging.h>
#include <util/filename.h>

#include <boost/bind.hpp>

#include <sstream>
#include <errno.h>

/// @brief provides default implementation for basic daemon operations
///
/// This file provides stub implementations that are expected to be redefined
/// in derived classes (e.g. ControlledDhcpv6Srv)
namespace isc {
namespace dhcp {

// This is an initial config file location.
std::string Daemon::config_file_ = "";

Daemon::Daemon()
    : signal_set_(), signal_handler_(), proc_name_(""),
    pid_file_dir_(DHCP_DATA_DIR), pid_file_(), am_file_author_(false) {

    // The pid_file_dir can be overridden via environment variable
    // This is primarily intended to simplify testing
    const char* const env = getenv("KEA_PIDFILE_DIR");
    if (env) {
        pid_file_dir_ = env;
    }
}

Daemon::~Daemon() {
    if (pid_file_ && am_file_author_) {
        pid_file_->deleteFile();
    }
}

void Daemon::init(const std::string& config_file) {
    config_file_ = config_file;
}

void Daemon::cleanup() {

}

void Daemon::shutdown() {

}

void Daemon::handleSignal() {
    if (signal_set_ && signal_handler_) {
        signal_set_->handleNext(boost::bind(signal_handler_, _1));
    }
}

void Daemon::configureLogger(const isc::data::ConstElementPtr& log_config,
                             const SrvConfigPtr& storage) {

    if (log_config) {
        isc::data::ConstElementPtr loggers = log_config->get("loggers");
        if (loggers) {
            LogConfigParser parser(storage);
            parser.parseConfiguration(loggers, CfgMgr::instance().isVerbose());
        }
    }
}

void
Daemon::setVerbose(bool verbose) {
    CfgMgr::instance().setVerbose(verbose);
}

bool
Daemon::getVerbose() const {
    return (CfgMgr::instance().isVerbose());
}

void Daemon::loggerInit(const char* name, bool verbose) {

    setenv("KEA_LOGGER_DESTINATION",  "stdout", 0);

    // Initialize logger system
    isc::log::initLogger(name, isc::log::DEBUG, isc::log::MAX_DEBUG_LEVEL,
                         NULL);

    // Apply default configuration (log INFO or DEBUG to stdout)
    isc::log::setDefaultLoggingOutput(verbose);
}

std::string Daemon::getVersion(bool /*extended*/) {
    isc_throw(isc::NotImplemented, "Daemon::getVersion() called");
}

void
Daemon::setConfigFile(const std::string& config_file) {
    config_file_ = config_file;
}

std::string
Daemon::getProcName() const {
    return (proc_name_);
};

void
Daemon::setProcName(const std::string& proc_name) {
    proc_name_ = proc_name;
}

std::string
Daemon::getPIDFileDir() const {
    return(pid_file_dir_);
}

void
Daemon::setPIDFileDir(const std::string& pid_file_dir) {
    pid_file_dir_ = pid_file_dir;
}

std::string
Daemon::getPIDFileName() const {
    if (pid_file_) {
        return (pid_file_->getFilename());
    }

    return ("");
};

void
Daemon::setPIDFileName(const std::string& pid_file_name) {
    if (pid_file_) {
        isc_throw(isc::InvalidOperation, "Daemon::setConfigFile"
                  " file name already set to:" << pid_file_->getFilename());
    }

    if (pid_file_name.empty()) {
        isc_throw(isc::BadValue, "Daemon::setPIDFileName"
                  " file name may not be empty");
    }

    pid_file_.reset(new util::PIDFile(pid_file_name));
};

std::string
Daemon::makePIDFileName() const {
    if (config_file_.empty()) {
        isc_throw(isc::InvalidOperation,
                  "Daemon::makePIDFileName config file name is not set");
    }

    if (proc_name_.empty()) {
        isc_throw(isc::InvalidOperation,
                  "Daemon::makePIDFileName process name is not set");
    }

    // Create Filename instance from the config_file_ pathname, so we can
    // extract the fname component.
    isc::util::Filename file(config_file_);
    if (file.name().empty()) {
        isc_throw(isc::BadValue, "Daemon::makePIDFileName config file:"
                  << config_file_ << " is missing file name");
    }

    // Make the pathname for the PID file from the runtime directory,
    // configuration name and process name.
    std::ostringstream stream;
    stream  << pid_file_dir_ << "/" << file.name()
            << "." << proc_name_ << ".pid";

    return(stream.str());
};

void
Daemon::createPIDFile(int pid) {
    // If pid_file_ hasn't been instantiated explicitly, then do so
    // using the default name.
    if (!pid_file_) {
        setPIDFileName(makePIDFileName());
    }

    // If we find a pre-existing file containing a live PID we bail.
    int chk_pid = pid_file_->check();
    if (chk_pid > 0) {
        isc_throw(DaemonPIDExists, "Daemon::createPIDFile: PID: " << chk_pid
                 << " exists, PID file: " << getPIDFileName());
    }

    if (pid == 0) {
        // Write the PID of the current process
        pid_file_->write();
    } else {
        // Write the PID we were given
        pid_file_->write(pid);
    }

    am_file_author_ = true;
}

};
};
