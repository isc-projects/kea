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

#ifndef DAEMON_H
#define DAEMON_H

#include <cc/data.h>
#include <dhcpsrv/srv_config.h>
#include <util/signal_set.h>
#include <boost/noncopyable.hpp>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Base class for all services
///
/// This is the base class that all daemons (DHCPv4, DHCPv6, D2 and possibly
/// others) are derived from. It provides a standard interface for starting up,
/// reconfiguring, shutting down and several other operations. It also covers
/// some common operations.
///
/// This class is not expected to be instantiated directly, but rather daemon
/// implementations should derive from it.
///
/// Methods are not pure virtual, as we need to instantiate basic daemons (e.g.
/// Dhcpv6Srv) in tests, without going through the hassles of implemeting stub
/// methods.
///
/// This class comprises a static object holding a location of the configuration
/// file. The object must be static because it is instantiated by the signal
/// handler functions, which are static by their nature. The signal handlers
/// are used to reconfigure a running server and they need access to the
/// configuration file location. They get this access by calling
/// @c Daemon::getConfigFile function.
///
/// By default, the configuration file location is empty and its actual value
/// is assigned to the static object in @c Daemon::init function.
///
/// Classes derived from @c Daemon may install custom signal handlers using
/// @c isc::util::SignalSet class. This base class provides a declaration
/// of the @c SignalSet object that should be initialized in the derived
/// classes to install the custom exception handlers.
///
/// @note Only one instance of this class is instantiated as it encompasses
///       the whole operation of the server.  Nothing, however, enforces the
///       singleton status of the object.
class Daemon : public boost::noncopyable {

public:
    /// @brief Default constructor
    ///
    /// Initializes the object installing custom signal handlers for the
    /// process to NULL.
    Daemon();

    /// @brief Desctructor
    ///
    /// Having virtual destructor ensures that all derived classes will have
    /// virtual destructor as well.
    virtual ~Daemon();

    /// @brief Initializes the server.
    ///
    /// Depending on the configuration backend, it establishes msgq session,
    /// or reads the configuration file.
    ///
    /// Note: This function may throw to report enountered problems. It may
    /// also return false if the initialization was skipped. That may seem
    /// redundant, but the idea here is that in some cases the configuration
    /// was read, understood and the decision was made to not start. One
    /// case where such capability could be needed is when we have a single
    /// config file for Kea4 and D2, but the DNS Update is disabled. It is
    /// likely that the D2 will be started, it will analyze its config file,
    /// decide that it is not needed and will shut down.
    ///
    /// @note this method may throw
    ///
    /// @param config_file Config file name (may be empty if unused).
    virtual void init(const std::string& config_file);

    /// @brief Performs final deconfiguration.
    ///
    /// Performs configuration backend specific final clean-up. This is called
    /// shortly before the daemon terminates. Depending on backend, it may
    /// terminat existing msgq session, close LDAP connection or similar.
    ///
    /// The daemon is not expected to receive any further commands or
    /// configuration updates as it is in final stages of shutdown.
    virtual void cleanup();

    /// @brief Initiates shutdown procedure for the whole DHCPv6 server.
    virtual void shutdown();

    /// @brief Returns config file name.
    static std::string getConfigFile() {
        return (config_file_);
    }

    /// @brief Initializes logger
    ///
    /// This method initializes logging system. It also sets the default
    /// output to stdout. This is used in early stages of the startup
    /// phase before config file and parsed and proper logging details
    /// are known.
    ///
    /// @param log_name name used in logger initialization
    /// @param verbose verbose mode (true usually enables DEBUG messages)
    static void loggerInit(const char* log_name, bool verbose);

    /// @brief Configures logger
    ///
    /// Applies configuration stored in "Logging" structure in the
    /// configuration file. This structure has a "loggers" array that
    /// contains 0 or more entries, each configuring one logging source
    /// (name, severity, debuglevel), each with zero or more outputs (file,
    /// maxsize, maximum number of files).
    ///
    /// @param log_config JSON structures that describe logging
    /// @param storage configuration will be stored here
    static void configureLogger(const isc::data::ConstElementPtr& log_config,
                                const isc::dhcp::SrvConfigPtr& storage);

    /// @brief Sets or clears verbose mode
    ///
    /// Verbose mode (-v in command-line) triggers loggers to log everythin
    /// (sets severity to DEBUG and debuglevel to 99). Values specified in the
    /// config file are ignored.
    ///
    /// @param verbose specifies if verbose should be set or not
    void setVerbose(const bool verbose);

    /// @brief Returns if running in verbose mode
    ///
    /// @return verbose mode
    bool getVerbose() const;

    /// @brief returns Kea version on stdout and exits.
    ///
    /// With extended == false, this method returns a simple string
    /// containing version number. With extended == true, it returns
    /// also additional information about sources. It is expected to
    /// return extra information about dependencies and used DB backends.
    ///
    /// As there is no static virtual methods in C++ this class method
    /// has to be redefined in derived classes and called with the
    /// derived class name or a child name.
    ///
    /// @param extended print additional information?
    /// @return text string
    static std::string getVersion(bool extended);

protected:

    /// @brief Invokes handler for the next received signal.
    ///
    /// This function provides a default implementation for the function
    /// handling next signal received by the process. It checks if a pointer
    /// to @c isc::util::SignalSet object and the signal handler function
    /// have been set. If they have been set, the signal handler is invoked for
    /// the the next signal registered in the @c SignalSet object.
    ///
    /// This function should be received in the main loop of the process.
    virtual void handleSignal();

    /// @brief A pointer to the object installing custom signal handlers.
    ///
    /// This pointer needs to be initialized to point to the @c SignalSet
    /// object in the derived classes which need to handle signals received
    /// by the process.
    isc::util::SignalSetPtr signal_set_;

    /// @brief Pointer to the common signal handler invoked by the handleSignal
    /// function.
    ///
    /// This pointer needs to be initialized to point to the signal handler
    /// function for signals being handled by the process. If signal handler
    /// it not initialized, the signals will not be handled.
    isc::util::SignalHandler signal_handler_;

private:

    /// @brief Config file name or empty if config file not used.
    static std::string config_file_;

};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif
