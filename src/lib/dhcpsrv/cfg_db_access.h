// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_DBACCESS_H
#define CFG_DBACCESS_H

#include <cc/cfg_to_element.h>
#include <boost/shared_ptr.hpp>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Holds access parameters and the configuration of the
/// lease and hosts database connection.
///
/// The database access strings use the same format as the strings
/// passed to the @ref isc::dhcp::LeaseMgrFactory::create function.
class CfgDbAccess {
public:

    /// @brief Constructor.
    CfgDbAccess();

    /// @brief Sets parameters which will be appended to the database
    /// access strings.
    ///
    /// @param appended_parameters String holding collection of parameters
    /// in the following format: "parameter0=value0 parameter1=value1 ...".
    void setAppendedParameters(const std::string& appended_parameters) {
        appended_parameters_ = appended_parameters;
    }

    /// @brief Retrieves lease database access string.
    ///
    /// @return Lease database access string with additional parameters
    /// specified with @ref CfgDbAccess::setAppendedParameters.
    std::string getLeaseDbAccessString() const;

    /// @brief Sets lease database access string.
    ///
    /// @param lease_db_access New lease database access string.
    void setLeaseDbAccessString(const std::string& lease_db_access) {
        lease_db_access_ = lease_db_access;
    }

    /// @brief Retrieves host database access string.
    ///
    /// @return Host database access string with additional parameters
    /// specified with @ref CfgDbAccess::setAppendedParameters.
    std::string getHostDbAccessString() const;

    /// @brief Sets host database access string.
    ///
    /// @param host_db_access New host database access string.
    void setHostDbAccessString(const std::string& host_db_access) {
        host_db_access_ = host_db_access;
    }

    /// @brief Creates instance of lease manager and host data source
    /// according to the configuration specified.
    void createManagers() const;

    /// @brief Unparse an access string
    ///
    /// @param dbaccess the database access string
    /// @return a pointer to configuration
    static
    isc::data::ElementPtr toElementDbAccessString(const std::string& dbaccess);

protected:

    /// @brief Returns lease or host database access string.
    ///
    /// @param access_string without additional (appended) parameters.
    std::string getAccessString(const std::string& access_string) const;

    /// @brief Parameters to be appended to the database access
    /// strings.
    std::string appended_parameters_;

    /// @brief Holds lease database access string.
    std::string lease_db_access_;

    /// @brief Holds host database access string.
    std::string host_db_access_;

};

/// @brief A pointer to the @c CfgDbAccess.
typedef boost::shared_ptr<CfgDbAccess> CfgDbAccessPtr;

/// @brief A pointer to the const @c CfgDbAccess.
typedef boost::shared_ptr<const CfgDbAccess> ConstCfgDbAccessPtr;

/// @brief utility class for unparsing
struct CfgLeaseDbAccess : public CfgDbAccess, public isc::data::CfgToElement {
    /// @brief Constructor
    CfgLeaseDbAccess(const CfgDbAccess& super) : CfgDbAccess(super) { }

    /// @brief Unparse
    ///
    /// @ref isc::data::CfgToElement::toElement
    ///
    /// @result a pointer to a configuration
    virtual isc::data::ElementPtr toElement() const {
        return (CfgDbAccess::toElementDbAccessString(lease_db_access_));
    }
};

struct CfgHostDbAccess : public CfgDbAccess, public isc::data::CfgToElement {
    /// @brief Constructor
    CfgHostDbAccess(const CfgDbAccess& super) : CfgDbAccess(super) { }

    /// @brief Unparse
    ///
    /// @ref isc::data::CfgToElement::toElement
    ///
    /// @result a pointer to a configuration
    virtual isc::data::ElementPtr toElement() const {
        return (CfgDbAccess::toElementDbAccessString(host_db_access_));
    }
};

}
}

#endif // CFG_DBACCESS_H
