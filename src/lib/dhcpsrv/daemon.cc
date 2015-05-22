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
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/daemon.h>
#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <boost/bind.hpp>
#include <logging.h>
#include <log/logger_name.h>
#include <log/logger_support.h>
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
    : signal_set_(), signal_handler_() {
}

Daemon::~Daemon() {
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

};
};
