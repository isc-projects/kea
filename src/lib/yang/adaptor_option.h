// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_ADAPTOR_OPTION_H
#define ISC_ADAPTOR_OPTION_H 1

#include <dhcp/option_data_types.h>
#include <yang/adaptor.h>

#include <unordered_map>

namespace isc {
namespace yang {

/// @brief Map for DHCP option definitions handling code and
/// an index built from space and name.
///
/// The map is used to store space+name to code mappings so for
/// an option data without a code entry the code entry can be supplied.
using OptionCodes = std::unordered_map<std::string, uint16_t>;

/// @brief JSON adaptor for option data or definition setting defaults.
///
/// Both option data and option definition lists are keyed by the code
/// and space pair so both must be available in setOptionXXX methods.
/// For space there is an implicit default so setSpace must be called
/// to add this default to option entries without space.
/// Note remaining adaptors assume this was done first.
///
/// checkCode and checkType can be used to check if code or type is present
/// (type is mandatory in option definitions).
///
/// A missing code can be found in standard definitions (loaded by initCodes)
/// or in configuration option definitions (at global and client classes
/// scopes). setCode uses the space+name to code map to set missing codes
/// and raises an error when it can't.
class AdaptorOption {
public:
    /// @brief Destructor.
    virtual ~AdaptorOption() = default;

    /// @brief Set space.
    ///
    /// @param option The option.
    /// @param space The default space name.
    static void setSpace(isc::data::ElementPtr option,
                         const std::string& space);

    /// @brief Checks if type is specified in option definition.
    ///
    /// @param option The option.
    /// @throw MissingKey if the type is not present.
    static void checkType(isc::data::ConstElementPtr option);

    /// @brief Check if code is specified in option defintion.
    ///
    /// @param option The option.
    /// @throw MissingKey if the code is not present.
    static void checkCode(isc::data::ConstElementPtr option);

    /// @brief Collect definition.
    ///
    /// This method looks at an option definition and adds the
    /// space+name to code mapping into the OptionCodes codes store
    /// aka definitions.
    ///
    /// @param option The option definition.
    /// @param codes The reference to option definitions.
    static void collect(isc::data::ConstElementPtr option, OptionCodes& codes);

    /// @brief Set code from name and definitions.
    ///
    /// @param option The option data.
    /// @param codes Option definitions.
    static void setCode(isc::data::ElementPtr option,
                        const OptionCodes& codes);

    /// @brief Initialize code map.
    ///
    /// @param codes The reference to option definitions.
    /// @param space The space name.
    static void initCodes(OptionCodes& codes, const std::string& space);

protected:
    /// @brief Initialize code map from option definition parameters.
    ///
    /// @param codes The reference to option definitions.
    /// @param space The space name.
    /// @param params Array of option definition parameters
    /// @param params_size The size of the array.
    static void initCodesInternal(OptionCodes& codes, const std::string& space,
                                  const isc::dhcp::OptionDefParams* params,
                                  size_t params_size);
};  // AdaptorOption

}  // namespace yang
}  // namespace isc

#endif  // ISC_ADAPTOR_OPTION_H
