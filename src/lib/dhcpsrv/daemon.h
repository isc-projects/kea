// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DAEMON_H
#define DAEMON_H

#include <cc/data.h>
#include <dhcpsrv/srv_config.h>
#include <util/pid_file.h>
#include <util/signal_set.h>
#include <boost/noncopyable.hpp>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when a the PID file points to a live PID
class DaemonPIDExists : public Exception {
public:
    DaemonPIDExists(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

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

    /// @brief Returns config file name.
    /// @return text string
    std::string getConfigFile() const;

    /// @brief Sets the configuration file name
    ///
    /// @param config_file pathname of the configuration file
    void setConfigFile(const std::string& config_file);

    /// @brief returns the process name
    /// This value is used as when forming the default PID file name
    /// @return text string
    std::string getProcName() const;

    /// @brief Sets the process name
    /// @param proc_name name the process by which the process is recognized
    void setProcName(const std::string& proc_name);

    /// @brief Returns the directory used when forming default PID file name
    /// @return text string
    std::string getPIDFileDir() const;

    /// @brief Sets the PID file directory
    /// @param pid_file_dir path into which the PID file should be written
    /// Note the value should not include a trailing slash, '/'
    void setPIDFileDir(const std::string& pid_file_dir);

    /// @brief Returns the current PID file name
    /// @return text string
    std::string getPIDFileName() const;

    /// @brief Sets PID file name
    ///
    /// If this method is called prior to calling createPIDFile,
    /// the value passed in will be treated as the full file name
    /// for the PID file.  This provides a means to override the
    /// default file name with an explicit value.
    ///
    /// @param pid_file_name file name to be used as the PID file
    void setPIDFileName(const std::string& pid_file_name);

    /// @brief Creates the PID file
    ///
    /// If the PID file name has not been previously set, the method
    /// uses manufacturePIDFileName() to set it.  If the PID file
    /// name refers to an existing file whose contents are a PID whose
    /// process is still alive, the method will throw a DaemonPIDExists
    /// exception.  Otherwise, the file created (or truncated) and
    /// the given pid (if not zero) is written to the file.
    ///
    /// @param pid PID to write to the file if not zero, otherwise the
    /// PID of the current process is used.
    void createPIDFile(int pid = 0);

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

    /// @brief Manufacture the pid file name
    std::string makePIDFileName() const;

private:
    /// @brief Config file name or empty if config file not used.
    std::string config_file_;

    /// @brief Name of this process, used when creating its pid file
    std::string proc_name_;

    /// @brief Pointer to the directory where PID file(s) are written
    /// It defaults to --localstatedir
    std::string pid_file_dir_;

    /// @brief Pointer to the PID file for this process
    isc::util::PIDFilePtr pid_file_;

    /// @brief Flag indicating if this instance created the file
    bool am_file_author_;
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif
