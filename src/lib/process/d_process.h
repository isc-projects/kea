// Copyright (C) 2013-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D_PROCESS_H
#define D_PROCESS_H

#include <asiolink/io_service.h>
#include <cc/data.h>
#include <process/d_cfg_mgr.h>

#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

#include <atomic>

namespace isc {
namespace process {

/// @brief Exception thrown if the process encountered an operational error.
class DProcessBaseError : public isc::Exception {
public:
    DProcessBaseError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief String value for the version-get command.
static const std::string VERSION_GET_COMMAND("version-get");

/// @brief String value for the build-report command.
static const std::string BUILD_REPORT_COMMAND("build-report");

/// @brief String value for the config-get command.
static const std::string CONFIG_GET_COMMAND("config-get");

/// @brief String value for the config-hash-get command.
static const std::string CONFIG_HASH_GET_COMMAND("config-hash-get");

/// @brief String value for the config-write command.
static const std::string CONFIG_WRITE_COMMAND("config-write");

/// @brief String value for the config-test command.
static const std::string CONFIG_TEST_COMMAND("config-test");

/// @brief String value for the config-reload command.
static const std::string CONFIG_RELOAD_COMMAND("config-reload");

/// @brief String value for the config-set command.
static const std::string CONFIG_SET_COMMAND("config-set");

/// @brief String value for the server-tag-get command.
static const std::string SERVER_TAG_GET_COMMAND("server-tag-get");

/// @brief String value for the shutdown command.
static const std::string SHUT_DOWN_COMMAND("shutdown");

/// @brief String value for the status-get command.
static const std::string STATUS_GET_COMMAND("status-get");

/// @brief Application Process Interface
///
/// DProcessBase is an abstract class represents the primary "application"
/// level object in a "managed" asynchronous application. It provides a uniform
/// interface such that a managing layer can construct, initialize, and start
/// the application's event loop.  The event processing is centered around the
/// use of isc::asiolink::io_service. The io_service is shared between the
/// managing layer and the DProcessBase.  This allows management layer IO such
/// as directives to be sensed and handled, as well as processing IO activity
/// specific to the application.  In terms of management layer IO, there are
/// methods shutdown, configuration updates, and commands unique to the
/// application.
class DProcessBase {
public:
    /// @brief Constructor
    ///
    /// @param app_name is a text label for the process. Generally used
    /// in log statements, but otherwise arbitrary.
    /// @param io_service is the io_service used by the caller for
    /// asynchronous event handling.
    /// @param cfg_mgr the configuration manager instance that handles
    /// configuration parsing.
    ///
    /// @throw DProcessBaseError is io_service is NULL.
    DProcessBase(const char* app_name, asiolink::IOServicePtr io_service,
                 DCfgMgrBasePtr cfg_mgr)
        : app_name_(app_name), io_service_(io_service), shut_down_flag_(false),
        cfg_mgr_(cfg_mgr) {
        if (!io_service_) {
            isc_throw (DProcessBaseError, "IO Service cannot be null");
        }

        if (!cfg_mgr_) {
            isc_throw (DProcessBaseError, "CfgMgr cannot be null");
        }
    };

    /// @brief May be used after instantiation to perform initialization unique
    /// to application. It must be invoked prior to invoking run. This would
    /// likely include the creation of additional IO sources and their
    /// integration into the io_service.
    /// @throw DProcessBaseError if the initialization fails.
    virtual void init() = 0;

    /// @brief Implements the process's event loop. In its simplest form it
    /// would an invocation io_service_->run().  This method should not exit
    /// until the process itself is exiting due to a request to shutdown or
    /// some anomaly is forcing an exit.
    /// @throw DProcessBaseError if an operational error is encountered.
    virtual void run() = 0;

    /// @brief Initiates the process's shutdown process.
    ///
    /// This is last step in the shutdown event callback chain, that is
    /// intended to notify the process it is to begin its shutdown process.
    ///
    /// @param args an Element set of shutdown arguments (if any) that are
    /// supported by the process derivation.
    ///
    /// @return an Element that contains the results of argument processing,
    /// consisting of an integer status value (0 means successful,
    /// non-zero means failure), and a string explanation of the outcome.
    ///
    /// @throw DProcessBaseError if an operational error is encountered.
    virtual isc::data::ConstElementPtr
    shutdown(isc::data::ConstElementPtr args) = 0;

    /// @brief Processes the given configuration.
    ///
    /// This method may be called multiple times during the process lifetime.
    /// Certainly once during process startup, and possibly later if the user
    /// alters configuration. This method must not throw, it should catch any
    /// processing errors and return a success or failure answer as described
    /// below. On success the last commit timestamp must be updated.
    ///
    /// @param config_set a new configuration (JSON) for the process
    /// @param check_only true if configuration is to be verified only, not applied
    /// @return an Element that contains the results of configuration composed
    /// of an integer status value (0 means successful, non-zero means failure),
    /// and a string explanation of the outcome.
    virtual isc::data::ConstElementPtr
    configure(isc::data::ConstElementPtr config_set,
              bool check_only = false) = 0;

    /// @brief Destructor
    virtual ~DProcessBase(){};

    /// @brief Checks if the process has been instructed to shut down.
    ///
    /// @return true if process shutdown flag is true.
    bool shouldShutdown() const {
        return (shut_down_flag_);
    }

    /// @brief Sets the process shut down flag to the given value.
    ///
    /// @param value is the new value to assign the flag.
    void setShutdownFlag(bool value) {
        shut_down_flag_ = value;
    }

    /// @brief Fetches the application name.
    ///
    /// @return application name string.
    const std::string getAppName() const {
        return (app_name_);
    }

    /// @brief Fetches the controller's IOService.
    ///
    /// @return a reference to the controller's IOService.
    asiolink::IOServicePtr& getIoService() {
        return (io_service_);
    }

    /// @brief Convenience method for stopping IOservice processing.
    /// Invoking this will cause the process to exit any blocking
    /// IOService method such as run().  No further IO events will be
    /// processed.
    void stopIOService() {
        io_service_->stop();
    }

    /// @brief Fetches the process's configuration manager.
    ///
    /// @return a reference to the configuration manager.
    DCfgMgrBasePtr& getCfgMgr() {
        return (cfg_mgr_);
    }

private:
    /// @brief Text label for the process. Generally used in log statements,
    /// but otherwise can be arbitrary.
    std::string app_name_;

    /// @brief The IOService to be used for asynchronous event handling.
    asiolink::IOServicePtr io_service_;

    /// @brief Boolean flag set when shutdown has been requested.
    std::atomic<bool> shut_down_flag_;

    /// @brief  Pointer to the configuration manager.
    DCfgMgrBasePtr cfg_mgr_;
};

/// @brief Defines a shared pointer to DProcessBase.
typedef boost::shared_ptr<DProcessBase> DProcessBasePtr;

}  // namespace process
}  // namespace isc

#endif
