// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef CFG_OPTION_DEF_H
#define CFG_OPTION_DEF_H

#include <dhcp/option_definition.h>
#include <dhcp/option_space_container.h>
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
class CfgOptionDef {
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
    /// @param option_space name of the option space to add definition to.
    ///
    /// @throw isc::dhcp::DuplicateOptionDefinition when the particular
    /// option definition already exists.
    /// @throw isc::dhcp::MalformedOptionDefinition when the pointer to
    /// an option definition is NULL.
    /// @throw isc::BadValue when the option space name is empty or
    /// when trying to override the standard option (in dhcp4 or dhcp6
    /// option space).
    void add(const OptionDefinitionPtr& def, const std::string& option_space);

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
    /// @param option_space pption space.
    /// @param option_name option name.
    ///
    /// @return An option definition or NULL pointer if option definition
    /// has not been found.
    OptionDefinitionPtr get(const std::string& option_space,
                            const std::string& option_name) const;

private:

    /// @brief A collection of option definitions.
    ///
    /// The option definitions stored in this container can be accessed
    /// using the option space name they belong to.
    OptionSpaceContainer<OptionDefContainer, OptionDefinitionPtr,
                         std::string> option_definitions_;

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
