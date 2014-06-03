// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp4/json_config_parser.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/dhcp4_log.h>
#include <exceptions/exceptions.h>

#include <string>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace std;

namespace {

/// @brief Configure DHCPv4 server using the configuration file specified.
///
/// This function is used to both configure the DHCP server on its startup
/// and dynamically reconfigure the server when SIGHUP signal is received.
///
/// It fetches DHCPv6 server's configuration from the 'Dhcp4' section of
/// the JSON configuration file.
///
/// @param file_name Configuration file location.
void configure(const std::string& file_name) {
    // This is a configuration backend implementation that reads the
    // configuration from a JSON file.

    isc::data::ConstElementPtr json;
    isc::data::ConstElementPtr dhcp4;
    isc::data::ConstElementPtr result;

    // Basic sanity check: file name must not be empty.
    try {
        if (file_name.empty()) {
            // Basic sanity check: file name must not be empty.
            isc_throw(isc::BadValue, "JSON configuration file not specified."
                      " Please use -c command line option.");
        }

        // Read contents of the file and parse it as JSON
        json = isc::data::Element::fromJSONFile(file_name, true);

        if (!json) {
            LOG_ERROR(dhcp4_logger, DHCP4_CONFIG_LOAD_FAIL)
                .arg("Config file " + file_name + " missing or empty.");
            isc_throw(isc::BadValue, "Unable to process JSON configuration"
                      " file: " << file_name);
        }

        // Get Dhcp4 component from the config
        dhcp4 = json->get("Dhcp4");

        if (!dhcp4) {
            LOG_ERROR(dhcp4_logger, DHCP4_CONFIG_LOAD_FAIL)
                .arg("Config file " + file_name + " does not include 'Dhcp4'"
                     " entry.");
            isc_throw(isc::BadValue, "Unable to process JSON configuration"
                      " file: " << file_name);
        }

        // Use parsed JSON structures to configure the server
        result = ControlledDhcpv4Srv::processCommand("config-reload", dhcp4);

    }  catch (const std::exception& ex) {
        LOG_ERROR(dhcp4_logger, DHCP4_CONFIG_LOAD_FAIL).arg(ex.what());
        isc_throw(isc::BadValue, "Unable to process JSON configuration file: "
                  << file_name);
    }

    if (!result) {
        // Undetermined status of the configuration. This should never happen,
        // but as the configureDhcp4Server returns a pointer, it is
        // theoretically possible that it will return NULL.
        LOG_ERROR(dhcp4_logger, DHCP4_CONFIG_LOAD_FAIL)
            .arg("Configuration failed: Undefined result of processCommand("
                 "config-reload, " + file_name + ")");
        isc_throw(isc::BadValue, "Configuration failed: Undefined result of "
                  "processCommand('config-reload', " << file_name << ")");
    }

    // Now check is the returned result is successful (rcode=0) or not
    isc::data::ConstElementPtr comment; /// see @ref isc::config::parseAnswer
    int rcode;
    comment = isc::config::parseAnswer(rcode, result);
    if (rcode != 0) {
        string reason = "";
        if (comment) {
            reason = string(" (") + comment->stringValue() + string(")");
        }
        LOG_ERROR(dhcp4_logger, DHCP4_CONFIG_LOAD_FAIL).arg(reason);
        isc_throw(isc::BadValue, "Failed to apply configuration: " << reason);
    }
}

/// @brief Signals handler for DHCPv4 server.
///
/// This signal handler handles the following signals received by the DHCPv4
/// server process:
/// - SIGHUP - triggers server's dynamic reconfiguration.
/// - SIGTERM - triggers server's shut down.
/// - SIGINT - triggers server's shut down.
///
/// @param signo Signal number received.
void signalHandler(int signo) {
    // SIGHUP signals a request to reconfigure the server.
    if (signo == SIGHUP) {
        // Get configuration file name.
        std::string file = ControlledDhcpv4Srv::getInstance()->getConfigFile();
        try {
            LOG_INFO(dhcp4_logger, DHCP4_DYNAMIC_RECONFIGURATION).arg(file);
            configure(file);
        } catch (const std::exception& ex) {
            // Log the unsuccessful reconfiguration. The reason for failure
            // should be already logged. Don't rethrow an exception so as
            // the server keeps working.
            LOG_ERROR(dhcp4_logger, DHCP4_DYNAMIC_RECONFIGURATION_FAIL)
                .arg(file);
        }
    } else if ((signo == SIGTERM) || (signo == SIGINT)) {
        isc::data::ElementPtr params(new isc::data::MapElement());
        ControlledDhcpv4Srv::processCommand("shutdown", params);
    }
}

}

namespace isc {
namespace dhcp {

void
ControlledDhcpv4Srv::init(const std::string& file_name) {
    // Call parent class's init to initialize file name.
    Daemon::init(file_name);

    // Configure the server using JSON file.
    configure(file_name);

    // We don't need to call openActiveSockets() or startD2() as these
    // methods are called in processConfig() which is called by
    // processCommand("reload-config", ...)

    // Set signal handlers. When the SIGHUP is received by the process
    // the server reconfiguration will be triggered. When SIGTERM or
    // SIGINT will be received, the server will start shutting down.
    signal_set_.reset(new isc::util::io::SignalSet(SIGINT, SIGHUP, SIGTERM));
    // Set the pointer to the handler function.
    signal_handler_ = signalHandler;

}

void ControlledDhcpv4Srv::cleanup() {
    // Nothing to do here. No need to disconnect from anything.
}

/// This is a logger initialization for JSON file backend.
/// For now, it's just setting log messages to be printed on stdout.
/// @todo: Implement this properly (see #3427)
void Daemon::loggerInit(const char*, bool verbose) {

    setenv("B10_LOCKFILE_DIR_FROM_BUILD", "/tmp", 1);
    setenv("B10_LOGGER_ROOT", "kea", 0);
    setenv("B10_LOGGER_SEVERITY", (verbose ? "DEBUG":"INFO"), 0);
    setenv("B10_LOGGER_DBGLEVEL", "99", 0);
    setenv("B10_LOGGER_DESTINATION",  "stdout", 0);
    isc::log::initLogger();
}

};
};
