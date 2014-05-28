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
#include <string>
#include <boost/noncopyable.hpp>


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
/// @note Only one instance of this class is instantiated as it encompasses
///       the whole operation of the server.  Nothing, however, enforces the
///       singleton status of the object.
class Daemon : public boost::noncopyable {

public:
    /// @brief Default constructor
    ///
    /// Currently it does nothing.
    Daemon();

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

    /// @brief Desctructor
    ///
    /// Having virtual destructor ensures that all derived classes will have
    /// virtual destructor as well.
    virtual ~Daemon();

    /// @brief Returns config file name.
    static std::string getConfigFile() {
        return (config_file_);
    }

    /// Initializes logger
    ///
    /// This method initializes logger.
    static void loggerInit(const char* log_name, bool verbose, bool stand_alone);

private:

    /// @brief Config file name or empty if config file not used.
    static std::string config_file_;
};

}; // end of isc::dhcp namespace
}; // end of isc namespace
