// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PROCESS_CONFIG_CTL_INFO_H
#define PROCESS_CONFIG_CTL_INFO_H

#include <cc/cfg_to_element.h>
#include <database/database_connection.h>
#include <util/optional.h>

#include <boost/shared_ptr.hpp>
#include <stdint.h>
#include <vector>

namespace isc {
namespace process {

/// @brief Provides configuration information used during a server's
/// configuration process.
///
class ConfigDbInfo : public isc::data::CfgToElement {
public:
    /// @brief Constructor
    ConfigDbInfo() {};

    /// @brief Set the access string.
    ///
    /// Sets the db's access string to the given value and then parses it
    /// into name-value pairs and storing them internally as a
    /// DatabaseConnection::ParameterMap.  It discards the existing content
    /// of the map first.  It does not validate the parameter names of values,
    /// ensuring the validity of the string content is placed upon the caller.
    ///
    /// @param access_str string of name=value pairs separated by spaces.
    /// @param test_mode flag used in unittests only to skip parsing the access
    /// string and storing the parameters.
    void setAccessString(const std::string& access_str, bool test_mode = false);

    /// @brief Retrieves the database access string.
    ///
    /// @return database access string.
    std::string getAccessString() const {
        return (access_str_);
    }

    /// @brief Retrieves the database access string with password redacted.
    ///
    /// @return database access string with password redacted.
    std::string redactedAccessString() const {
        return (db::DatabaseConnection::redactedAccessString(access_params_));
    }

    /// @brief Retrieve the map of parameter values.
    ///
    /// @return Constant reference to the database's parameter map.
    const db::DatabaseConnection::ParameterMap& getParameters() const {
        return (access_params_);
    }

    /// @brief Fetch the value of a given parameter.
    ///
    /// @param name name of the parameter value to fetch.
    /// @param[out] value string which will contain the value of the
    /// parameter (if found).
    ///
    /// @return Boolean true if the parameter named is found in the map,
    /// false otherwise.
    bool getParameterValue(const std::string& name,
                           std::string& value) const;

    /// @brief Unparse a configuration object.
    ///
    /// @return a pointer to unparsed configuration.
    virtual isc::data::ElementPtr toElement() const;

    /// @brief Compares two objects for equality.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if objects are equal, false otherwise.
    bool equals(const ConfigDbInfo& other) const;

    /// @brief Compares two objects for equality.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if objects are equal, false otherwise.
    bool operator==(const ConfigDbInfo& other) const {
        return (equals(other));
    }

    /// @brief Compares two objects for inequality.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if objects are not equal, false otherwise.
    bool operator!=(const ConfigDbInfo& other) const {
        return (!equals(other));
    }

private:
    /// @brief Access string of parameters used to access this database.
    std::string access_str_;

    /// @brief Map of the access parameters and their values.
    db::DatabaseConnection::ParameterMap access_params_;
};

typedef std::vector<ConfigDbInfo> ConfigDbInfoList;

/// @brief Embodies configuration information used during a server's
/// configuration process.
///
/// This is class conveys the configuration control information
/// described by the following JSON text:
///
/// @code
/// "config-control" :
/// {
///     "config-databases":
///     [
///     {
///         # first config db
///         # common database access parameters
///         "type": <"mysql"|"postgresql">,
///         "name": <"db name">,
///         "host": <"db host name">,
///             :
///     },
///     {
///         # next config db
///     }
///     ]
///
/// }
/// @endcode
///
class ConfigControlInfo : public isc::data::CfgToElement {
public:

    /// @brief Constructor.
    ConfigControlInfo()
        : config_fetch_wait_time_(30, true) {};

    /// @brief Copy Constructor.
    ConfigControlInfo(const ConfigControlInfo& other);

    /// @brief Sets new value of the config-fetch-wait-time.
    ///
    /// @param config_fetch_wait_time New value of the parameter which
    /// specifies a time period in seconds between the attempts to
    /// fetch the server configuration updates. The value of 0 disables
    /// the periodic attempts to fetch the updates.
    void setConfigFetchWaitTime(const util::Optional<uint16_t>& config_fetch_wait_time) {
        config_fetch_wait_time_ = config_fetch_wait_time;
    }

    /// @brief Returns configured config-fetch-wait-time value.
    ///
    /// This value specifies the time period in seconds between the
    /// attempts to fetch the server configuration updates via the
    /// configuration backends. The value of 0 means that the
    /// mechanism to periodically fetch the configuration updates
    /// is disabled.
    ///
    /// @return Time period between the subsequent attempts to
    /// fetch server configuration updates in seconds.
    const util::Optional<uint16_t>& getConfigFetchWaitTime() const {
        return (config_fetch_wait_time_);
    }

    /// @brief Sets configuration database access string.
    ///
    /// @param access_str database access string.
    ///
    /// @throw BadValue if an entry exists that matches the parameters
    /// in the given access string, or if the access string is invalid.
    void addConfigDatabase(const std::string& access_str);

    /// @brief Retrieves the list of databases.
    ///
    /// The entries in the list are stored in the order they were
    /// added to it (FIFO).
    ///
    /// @return a reference to a const list of databases.
    const ConfigDbInfoList& getConfigDatabases() const {
        return (db_infos_);
    }

    /// @brief Retrieves the database with the given access parameter value.
    ///
    /// @return A reference to the matching database or the not-found value
    /// available via @c EMPTY_DB().
    const ConfigDbInfo& findConfigDb(const std::string& param_name,
                                     const std::string& param_value);

    /// @brief Empties the contents of the class, including the database list.
    void clear();

    /// @brief Merges specified configuration into this configuration.
    ///
    /// If the other configuration is non-empty it completely replaces
    /// this configuration.
    ///
    /// @param other the other configuration to be merged into this
    /// configuration.
    void merge(const ConfigControlInfo& other);

    /// @brief Unparse a configuration object.
    ///
    /// @return a pointer to unparsed configuration.
    virtual isc::data::ElementPtr toElement() const;

    /// @brief Fetches the not-found value returned by database list searches.
    ///
    /// @return a reference to the empty ConfigDBInfo.
    static const ConfigDbInfo& EMPTY_DB();

    /// @brief Compares two objects for equality.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if objects are equal, false otherwise.
    bool equals(const ConfigControlInfo& other) const;

private:

    /// @brief Configured value of the config-fetch-wait-time.
    util::Optional<uint16_t> config_fetch_wait_time_;

    /// @brief List of configuration databases.
    ConfigDbInfoList db_infos_;
};

/// @brief Defines a pointer to a ConfigControlInfo.
typedef boost::shared_ptr<ConfigControlInfo> ConfigControlInfoPtr;

/// @brief Defines a pointer to a const ConfigControlInfo.
typedef boost::shared_ptr<const ConfigControlInfo> ConstConfigControlInfoPtr;

} // namespace process
} // end namespace isc

#endif // PROCESS_CONFIG_CTL_INFO_H
