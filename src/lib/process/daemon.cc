// Copyright (C) 2014-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <process/daemon.h>
#include <process/log_parser.h>
#include <exceptions/exceptions.h>
#include <log/logger_name.h>
#include <log/logger_support.h>
#include <process/config_base.h>
#include <process/redact_config.h>
#include <util/filename.h>

#include <functional>
#include <sstream>
#include <fstream>

#include <errno.h>

using namespace isc::data;
namespace ph = std::placeholders;

/// @brief provides default implementation for basic daemon operations
///
/// This file provides stub implementations that are expected to be redefined
/// in derived classes (e.g. ControlledDhcpv6Srv)
namespace isc {
namespace process {

bool Daemon::verbose_ = false;

std::string Daemon::proc_name_("");

std::string Daemon::default_logger_name_("kea");

Daemon::Daemon()
    : signal_set_(), config_file_(""),
      pid_file_dir_(DATA_DIR), pid_file_(), am_file_author_(false),
      exit_value_(EXIT_SUCCESS) {

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

void Daemon::cleanup() {
}

void Daemon::shutdown() {
}

void Daemon::configureLogger(const ConstElementPtr& log_config,
                             const ConfigPtr& storage) {

    if (log_config) {
        ConstElementPtr loggers = log_config->get("loggers");
        if (loggers) {
            LogConfigParser parser(storage);
            parser.parseConfiguration(loggers, verbose_);
        }
    }
}

void
Daemon::setVerbose(bool verbose) {
    verbose_ = verbose;
}

bool
Daemon::getVerbose() {
    return (verbose_);
}

void Daemon::loggerInit(const char* name, bool verbose) {

    setenv("KEA_LOGGER_DESTINATION", "stdout", 0);

    // Initialize logger system
    isc::log::initLogger(name, isc::log::DEBUG, isc::log::MAX_DEBUG_LEVEL, 0);

    // Apply default configuration (log INFO or DEBUG to stdout)
    isc::log::setDefaultLoggingOutput(verbose);
}

std::string Daemon::getVersion(bool /*extended*/) {
    isc_throw(isc::NotImplemented, "Daemon::getVersion() called");
}

std::string
Daemon::getConfigFile() const {
    return (config_file_);
}

void
Daemon::setConfigFile(const std::string& config_file) {
    config_file_ = config_file;
}

void
Daemon::checkConfigFile() const {
    if (config_file_.empty()) {
        isc_throw(isc::BadValue, "config file name is not set");
    }

    // Create Filename instance from the config_file_ pathname, and
    // check the file name component.
    isc::util::Filename file(config_file_);
    if (file.name().empty()) {
        isc_throw(isc::BadValue, "config file:" << config_file_
                  << " is missing file name");
    }
}

std::string
Daemon::getProcName() {
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

    // Create Filename instance from the config_file_ pathname, so we can
    // extract the fname component.
    isc::util::Filename file(config_file_);
    if (file.name().empty()) {
        isc_throw(isc::BadValue, "Daemon::makePIDFileName config file:"
                  << config_file_ << " is missing file name");
    }

    if (proc_name_.empty()) {
        isc_throw(isc::InvalidOperation,
                  "Daemon::makePIDFileName process name is not set");
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

size_t
Daemon::writeConfigFile(const std::string& config_file,
                        ConstElementPtr cfg) const {
    if (!cfg) {
        isc_throw(Unexpected, "Can't write configuration: conversion to JSON failed");
    }

    std::ofstream out(config_file, std::ios::trunc);
    if (!out.good()) {
        isc_throw(Unexpected, "Unable to open file " + config_file + " for writing");
    }

    // Write the actual content using pretty printing.
    prettyPrint(cfg, out);

    size_t bytes = static_cast<size_t>(out.tellp());

    out.close();

    return (bytes);
}

std::list<std::list<std::string>>
Daemon::jsonPathsToRedact() const {
    static std::list<std::list<std::string>> const list;
    return list;
}

isc::data::ConstElementPtr
Daemon::redactConfig(isc::data::ConstElementPtr const& config) {
    isc::data::ConstElementPtr result(config);
    for (std::list<std::string>& json_path : jsonPathsToRedact()) {
        result = isc::process::redactConfig(result, json_path);
    }
    return result;
}

}  // namespace process
}  // namespace isc
