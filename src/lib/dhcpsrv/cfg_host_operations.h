// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_HOST_OPERATIONS_H
#define CFG_HOST_OPERATIONS_H

#include <cc/cfg_to_element.h>
#include <dhcpsrv/host.h>
#include <boost/shared_ptr.hpp>
#include <list>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Forward declaration of the @ref CfgHostOperations.
class CfgHostOperations;

/// @name Pointers to the @ref CfgHostOperations objects.
//@{
/// @brief Pointer to the Non-const object.
typedef boost::shared_ptr<CfgHostOperations> CfgHostOperationsPtr;

/// @brief Pointer to the const object.
typedef boost::shared_ptr<const CfgHostOperations>
ConstCfgHostOperationsPtr;

//@}

/// @brief Represents global configuration for host reservations.
///
/// This class represents server configuration pertaining to host
/// reservations.
///
/// Currently it only holds the ordered list of host identifiers
/// to be used to search for reservations for a particular host.
/// An administrator selects which identifiers the server should
/// use and in which order to search for host reservations to
/// optimize performance of the server.
class CfgHostOperations : public isc::data::CfgToElement {
public:

    /// @brief Type of the container holding ordered list of identifiers.
    typedef std::list<Host::IdentifierType> IdentifierTypes;

    /// @brief Constructor.
    ///
    /// The default configuration:
    /// - no identifiers selected for host reservations searches.
    CfgHostOperations();

    /// @name Factory functions for creating default configurations.
    //@{
    /// @brief Factory function for DHCPv4.
    static CfgHostOperationsPtr createConfig4();

    /// @brief Factory function for DHCPv6.
    static CfgHostOperationsPtr createConfig6();
    //@}

    /// @brief Adds new identifier type to a collection of identifiers
    /// to be used by the server to search for host reservations.
    ///
    /// @param identifier_name Name of the identifier to be added. It
    /// must be one of the names supported by the @ref Host::getIdentifierType
    /// function.
    void addIdentifierType(const std::string& identifier_name);

    /// @brief Returns const reference to ordered collection of identifiers
    /// to be used by the server to search for host reservations.
    const IdentifierTypes& getIdentifierTypes() const {
        return (identifier_types_);
    }

    /// @brief Removes existing identifier types.
    void clearIdentifierTypes();

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

private:

    /// @brief Holds ordered collection of identifiers to be used by the
    /// server to search for host reservations for a client.
    IdentifierTypes identifier_types_;

};

}
}

#endif // CFG_HOST_OPERATIONS_H
