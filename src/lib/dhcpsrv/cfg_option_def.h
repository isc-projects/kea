// Copyright (C) 2014-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_OPTION_DEF_H
#define CFG_OPTION_DEF_H

#include <dhcp/option_definition.h>
#include <dhcp/option_space_container.h>
#include <cc/cfg_to_element.h>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Represents option definitions used by the DHCP server.
///
/// This class provides methods to add and retrieve option definitions
/// specified by the administrator for the DHCP server. Option definitions
/// specify formats of the options. This class doesn't hold information
/// about the data being carried by the options.
///
/// Option definitions are grouped by option spaces. The option space is
/// identified by the unique name which is specified as a string. The
/// following names: "dhcp4" and "dhcp6" are reserved, though. They are
/// names of option spaces used for standard top-level DHCPv4 and DHCPv6
/// options respectively.
class CfgOptionDef : public isc::data::CfgToElement {
public:

    /// @brief Copies this configuration to a new configuration.
    ///
    /// This method copies the option definitions stores in the configuration
    /// to an object passed as parameter. There are no shared objects or
    /// pointers between the original object and a copy.
    ///
    /// @param [out] new_config An object to which the configuration will be
    /// copied.
    void copyTo(CfgOptionDef& new_config) const;

    /// @name Methods and operators used for comparing objects.
    ///
    //@{
    /// @brief Check if configuration is equal to other configuration.
    ///
    /// @param other An object holding configuration to compare to.
    ///
    /// @return true if configurations are equal, false otherwise.
    bool equals(const CfgOptionDef& other) const;

    /// @brief Equality operator.
    ///
    /// @param other An object holding configuration to compare to.
    ///
    /// @return true if configurations are equal, false otherwise.
    bool operator==(const CfgOptionDef& other) const {
        return (equals(other));
    }

    /// @brief Inequality operator.
    ///
    /// @param other An object holding configuration to compare to.
    ///
    /// @return true if configurations are unequal, false otherwise.
    bool operator!=(const CfgOptionDef& other) const {
        return (!equals(other));
    }

    //@}

    /// @brief Add new option definition.
    ///
    /// @param def option definition to be added.
    ///
    /// @throw isc::dhcp::DuplicateOptionDefinition when the particular
    /// option definition already exists.
    /// @throw isc::dhcp::MalformedOptionDefinition when the pointer to
    /// an option definition is NULL.
    /// @throw isc::BadValue when the option space name is empty or
    /// when trying to override the standard option (in dhcp4 or dhcp6
    /// option space).
    void add(const OptionDefinitionPtr& def);

    /// @brief Return option definitions for particular option space.
    ///
    /// @param option_space option space.
    ///
    /// @return Pointer to the collection of option definitions for
    /// the particular option space. The option collection is empty
    /// if no option exists for the option space specified.
    OptionDefContainerPtr getAll(const std::string& option_space) const;

    /// @brief Return option definition for a particular option space and code.
    ///
    /// @param option_space option space.
    /// @param option_code option code.
    ///
    /// @return An option definition or NULL pointer if option definition
    /// has not been found.
    OptionDefinitionPtr get(const std::string& option_space,
                            const uint16_t option_code) const;

    /// @brief Return option definition for the particular option space and name.
    ///
    /// @param option_space option space.
    /// @param option_name option name.
    ///
    /// @return An option definition or NULL pointer if option definition
    /// has not been found.
    OptionDefinitionPtr get(const std::string& option_space,
                            const std::string& option_name) const;

    /// @brief Deletes all option definitions having a given database id.
    ///
    /// Note that there are cases when there will be multiple option
    /// definitions having the same id (typically id of 0). When
    /// configuration backend is in use it sets the unique ids from the
    /// database. In cases when the configuration backend is not used,
    /// the ids default to 0. Passing the id of 0 would result in
    /// deleting all option definitions that were not added via the
    /// database.
    ///
    /// @param id Identifier of the option definitions to be deleted.
    ///
    /// @return Number of deleted option definitions.
    uint64_t del(const uint64_t id);

    /// @brief Returns reference to container holding option definitions.
    const OptionDefSpaceContainer& getContainer() const {
        return (option_definitions_);
    }

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

    /// @brief Unparse a configuration object with optionally including
    /// the metadata.
    ///
    /// @param include_metadata boolean value indicating if the metadata
    /// should be included (if true) or not (if false).
    ///
    /// @return A pointer to the unparsed configuration.
    isc::data::ElementPtr
    toElementWithMetadata(const bool include_metadata) const;

    /// @brief Merges specified option definitions from a configuration
    /// into this configuration.
    ///
    /// This method merges the option definitions from the @c other
    /// configuration into this configuration.  The merged set of
    /// definitions is created as follows:
    ///
    /// Iterator over the definitions in each name space in this configuration:
    /// If either the definition's name or code are defined in @c other
    /// then skip over the definition otherwise add it to @c other.
    ///
    /// Replace this configuration's definitions with the definitions
    /// in @c other using @c copyTo().
    ///
    /// @param other option definitions to merge in.
    ///
    /// @warning The merge operation affects @c other.
    /// Therefore, the caller must not rely on the data held in the @c other
    /// object after the call to @c merge. Also, the data held in @c other must
    /// not be modified after the call to @c merge because it may affect the
    /// merged configuration.
    void merge(CfgOptionDef& other);

private:

    /// @brief A collection of option definitions.
    ///
    /// The option definitions stored in this container can be accessed
    /// using the option space name they belong to.
    OptionDefSpaceContainer option_definitions_;

};

/// @name Pointers to the @c CfgOptionDef objects.
//@{
/// @brief Non-const pointer.
typedef boost::shared_ptr<CfgOptionDef> CfgOptionDefPtr;

/// @brief Const pointer.
typedef boost::shared_ptr<const CfgOptionDef> ConstCfgOptionDefPtr;

//@}

}
}

#endif // CFG_OPTION_DEF_H
