// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEGAL_LOG_MGR_FACTORY_H
#define LEGAL_LOG_MGR_FACTORY_H

#include <database/database_connection.h>
#include <dhcpsrv/legal_log_mgr.h>
#include <exceptions/exceptions.h>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include <functional>
#include <map>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Backend Store Factory
///
/// This class comprises nothing but static methods used to create a forensic
/// backend store.  It analyzes the database information passed to the creation
/// function and instantiates an appropriate forensic backend store based on the
/// type requested.
///
/// Strictly speaking these functions could be stand-alone functions.  However,
/// it is convenient to encapsulate them in a class for naming purposes.
class LegalLogMgrFactory : public boost::noncopyable {
private:

    /// @brief Type of the backend factory function.
    ///
    /// Factory function returns a pointer to the instance of the configuration
    /// backend created.
    typedef std::function<LegalLogMgrPtr (const db::DatabaseConnection::ParameterMap&)> Factory;

    /// @brief Type of backend store version.
    typedef std::function<std::string ()> DBVersion;

public:

    /// @brief Registers new backend factory function for a given backend type.
    ///
    /// If the backend of the given type has already been registered, perhaps
    /// by another hooks library, the CBM will refuse to register another
    /// backend of the same type.
    ///
    /// @param db_type backend type, e.g. "mysql".
    /// @param factory pointer to the backend factory function.
    /// @param no_log do not log (default false)
    /// @param db_version forensic backend version
    /// @return true if the factory was successfully added to the map, false
    /// if it already exists.
    bool static registerBackendFactory(const std::string& db_type,
                                       const Factory& factory,
                                       bool no_log = false,
                                       DBVersion db_version = DBVersion());

    /// @brief Unregisters the backend factory function for a given backend type.
    ///
    /// @param db_type backend type, e.g. "mysql".
    /// @param no_log do not log (default false)
    /// @return false if no factory for the given type was unregistered, true
    /// if the factory was removed.
    bool static unregisterBackendFactory(const std::string& db_type,
                                         bool no_log = false);

    /// @brief Create an instance of a forensic log backend.
    ///
    /// This method uses provided @c parameters map representing database
    /// connection information to create an instance of the forensic log
    /// backend. If the specified backend type is not supported, i.e. there
    /// is no relevant factory function registered, an exception is thrown.
    ///
    /// @param parameters database parameters.
    /// @param id the forensic backend manager ID
    /// (default value is 0 and it is used only in unit tests).
    ///
    /// @throw InvalidParameter if access string lacks database type value.
    /// @throw db::InvalidType if the type of the database backend is not
    /// supported.
    /// @throw Unexpected if the backend factory function returned NULL.
    static void addBackend(db::DatabaseConnection::ParameterMap& parameters, ManagerID id = 0);

    /// @brief Removes all backends from the pool.
    static void delAllBackends();

    /// @brief Deletes all backends of the given type from the pool.
    ///
    /// @param db_type backend to remove.
    static void delAllBackends(const std::string& db_type);

    /// @brief Returns the forensic backend manager with specified ID.
    ///
    /// @param id the forensic backend manager ID
    /// (default value is 0 and it is used only in unit tests).
    /// @return the forensic backend manager instance or null pointer.
    static LegalLogMgrPtr& instance(ManagerID id = 0);

    /// @brief Sets the forensic backend manager parameters.
    ///
    /// @param parameters database parameters.
    /// @param id the forensic backend manager ID
    /// (default value is 0 and it is used only in unit tests).
    static void setParameters(isc::db::DatabaseConnection::ParameterMap parameters,
                              ManagerID id = 0);

    /// @brief Gets the forensic backend manager parameters.
    ///
    /// @param parameters database parameters.
    /// @param id the forensic backend manager ID
    /// (default value is 0 and it is used only in unit tests).
    static isc::db::DatabaseConnection::ParameterMap getParameters(ManagerID id = 0);

    /// @brief Delete a forensic backend manager.
    ///
    /// Delete the first instance of a config database manager which matches
    /// specific parameters.
    /// This should have the effect of closing the database connection.
    ///
    /// @param db_type backend to remove.
    /// @param parameters database parameters.
    /// @param if_unusable Flag which indicates if the config backend should be
    /// deleted only if it is unusable.
    /// @return false when not removed because it is not found or because it is
    /// still usable (if_unusable is true), true otherwise.
    static bool delBackend(const std::string& db_type,
                           db::DatabaseConnection::ParameterMap& parameters,
                           bool if_unusable = false);

    /// @brief Delete a forensic backend manager.
    ///
    /// Delete the first instance of a config database manager which matches
    /// specific parameters.
    /// This should have the effect of closing the database connection.
    ///
    /// @param id the forensic backend manager ID.
    /// @param if_unusable Flag which indicates if the forensic backend should be
    /// deleted only if it is unusable.
    /// @return false when not removed because it is not found or because it is
    /// still usable (if_unusable is true), true otherwise.
    static bool delBackend(ManagerID id,
                           bool if_unusable = false);

    /// @brief Check if a backend store factory was registered
    ///
    /// @param db_type database type
    /// @return true if a factory was registered for db_type, false if not.
    static bool registeredFactory(const std::string& db_type);

    /// @brief Logs out all registered backends.
    ///
    /// We need a dedicated method for this, because we sometimes can't log
    /// the backend type when doing early initialization for backends
    /// initialized statically.
    static void logRegistered();

    /// @brief Return extended version info for registered backends.
    static std::list<std::string> getDBVersions();

    /// @brief Returns underlying forensic log backend pool.
    static LegalLogMgrPool getPool() {
        return (pool_);
    }

    /// @brief Returns true is respective backend store is present, false otherwise.
    ///
    /// @param type the backend store type to check if it exists.
    static bool haveInstance(std::string type);

    /// @brief Get the hook I/O service.
    ///
    /// @return the hook I/O service.
    static isc::asiolink::IOServicePtr getIOService() {
        return (io_service_);
    }

    /// @brief Set the hook I/O service.
    ///
    /// @param io_service the hook I/O service.
    static void setIOService(isc::asiolink::IOServicePtr io_service) {
        io_service_ = io_service;
    }

protected:

    /// @brief The hook I/O service.
    static isc::asiolink::IOServicePtr io_service_;

    /// @brief A map holding registered backend factory functions.
    static std::map<std::string, std::pair<LegalLogMgrFactory::Factory, LegalLogMgrFactory::DBVersion>> map_;

    /// @brief Pointer to the forensic log backends pool.
    static LegalLogMgrPool pool_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // LEGAL_LOG_MGR_FACTORY_H
