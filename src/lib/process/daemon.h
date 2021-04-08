// Copyright (C) 2014-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DAEMON_H
#define DAEMON_H

#include <cc/data.h>
#include <process/config_base.h>
#include <util/pid_file.h>
#include <asiolink/io_service_signal.h>

#include <boost/noncopyable.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <list>
#include <string>

namespace isc {
namespace process {

/// @brief Exception thrown when the PID file points to a live PID
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
/// Dhcpv4Srv and Dhcpv6Srv) in tests, without going through the hassles of
/// implementing stub methods.
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

    /// @brief Destructor
    ///
    /// Having virtual destructor ensures that all derived classes will have
    /// virtual destructor as well.
    virtual ~Daemon();

    /// @brief Performs final deconfiguration.
    ///
    /// Performs configuration backend specific final clean-up. This is called
    /// shortly before the daemon terminates. Depending on backend, it may
    /// terminate existing msgq session, close LDAP connection or similar.
    ///
    /// The daemon is not expected to receive any further commands or
    /// configuration updates as it is in final stages of shutdown.
    virtual void cleanup();

    /// @brief Initiates shutdown procedure for the whole server.
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
    /// Applies configuration stored in a top-level structure in the
    /// configuration file. This structure has a "loggers" array that
    /// contains 0 or more entries, each configuring one logging source
    /// (name, severity, debuglevel), each with zero or more outputs (file,
    /// maxsize, maximum number of files).
    ///
    /// @param log_config JSON structures that describe logging
    /// @param storage configuration will be stored here
    static void configureLogger(const isc::data::ConstElementPtr& log_config,
                                const isc::process::ConfigPtr& storage);

    /// @brief Sets or clears verbose mode
    ///
    /// Verbose mode (-v in command-line) triggers loggers to log everything
    /// (sets severity to DEBUG and debuglevel to 99). Values specified in the
    /// config file are ignored.
    ///
    /// @param verbose specifies if verbose should be set or not
    static void setVerbose(const bool verbose);

    /// @brief Returns if running in verbose mode
    ///
    /// @return verbose mode
    static bool getVerbose();

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

    /// @brief Checks the configuration file name.
    /// @throw BadValue when the configuration file name is bad.
    void checkConfigFile() const;

    /// @brief Writes current configuration to specified file
    ///
    /// This method writes the current configuration to specified file.
    /// @todo: this logically more belongs to CPL process file. Once
    /// Daemon is merged with CPL architecture, it will be a better
    /// fit.
    ///
    /// If cfg is not specified, the current config (as returned by
    /// CfgMgr::instance().getCurrentCfg() will be returned.
    ///
    /// @param config_file name of the file to write the configuration to
    /// @param cfg configuration to write (optional)
    /// @return number of files written
    /// @throw Unexpected if CfgMgr can't retrieve configuration or file cannot
    ///                   be written
    virtual size_t
    writeConfigFile(const std::string& config_file,
                    isc::data::ConstElementPtr cfg = isc::data::ConstElementPtr()) const;

    /// @brief returns the process name
    /// This value is used as when forming the default PID file name
    /// @return text string
    static std::string getProcName();

    /// @brief Sets the process name
    /// @param proc_name name the process by which the process is recognized
    static void setProcName(const std::string& proc_name);

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

    /// @brief Returns default logger name.
    static std::string getDefaultLoggerName() {
        return (default_logger_name_);
    }

    /// @brief Sets the default logger name.
    ///
    /// This name is used in cases when a user doesn't provide a configuration
    /// for logger in the Kea configuration file.
    static void setDefaultLoggerName(const std::string& logger) {
        default_logger_name_ = logger;
    }

    /// @brief Fetches the exit value.
    int getExitValue() {
        return (exit_value_);
    }

    /// @brief Sets the exit value.
    ///
    /// @param value new exit value.
    void setExitValue(int value) {
        exit_value_ = value;
    }

    /// @brief Return a list of all paths that contain passwords or secrets.
    ///
    /// Used in @ref isc::process::Daemon::redactConfig to only make copies and
    /// only redact configuration subtrees that contain passwords or secrets. To
    /// be overridden by derived classes.
    ///
    /// @return the list of lists of sequential JSON map keys needed to reach
    /// the passwords and secrets.
    virtual std::list<std::list<std::string>> jsonPathsToRedact() const;

    /// @brief Redact a configuration.
    ///
    /// Calls @ref isc::process::redactConfig
    ///
    /// @param config the Element tree structure that describes the configuration.
    ///
    /// @return the redacted configuration
    isc::data::ConstElementPtr redactConfig(isc::data::ConstElementPtr const& config);

protected:

    /// @brief A pointer to the object installing custom signal handlers.
    ///
    /// This pointer needs to be initialized to point to the @c IOSignalSet
    /// object in the derived classes which need to handle signals received
    /// by the process.
    isc::asiolink::IOSignalSetPtr signal_set_;

    /// @brief Manufacture the pid file name
    std::string makePIDFileName() const;

    /// @brief Timestamp of the start of the daemon.
    boost::posix_time::ptime start_;

private:
    /// @brief Config file name or empty if config file not used.
    std::string config_file_;

    /// @brief Name of this process, used when creating its pid file
    static std::string proc_name_;

    /// @brief Pointer to the directory where PID file(s) are written
    /// It defaults to --localstatedir / run
    std::string pid_file_dir_;

    /// @brief Pointer to the PID file for this process
    isc::util::PIDFilePtr pid_file_;

    /// @brief Indicates whether verbose mode is turned on or not.
    static bool verbose_;

    /// @brief Stores default logger name
    static std::string default_logger_name_;

    /// @brief Flag indicating if this instance created the file
    bool am_file_author_;

    /// @brief Exit value the process should use.  Typically set
    /// by the application during a controlled shutdown.
    int exit_value_;
};

} // namespace process
} // namespace isc

#endif
