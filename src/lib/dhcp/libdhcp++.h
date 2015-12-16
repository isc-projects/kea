// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LIBDHCP_H
#define LIBDHCP_H

#include <dhcp/option_definition.h>
#include <dhcp/option_space_container.h>
#include <dhcp/pkt6.h>
#include <util/buffer.h>
#include <util/staged_value.h>

#include <iostream>
#include <string>

namespace isc {
namespace dhcp {

class LibDHCP {

public:

    /// Map of factory functions.
    typedef std::map<unsigned short, Option::Factory*>  FactoryMap;

    /// @brief Return collection of option definitions.
    ///
    /// Method returns the collection of DHCP standard DHCP
    /// option definitions.
    /// @todo DHCPv4 option definitions are not implemented. For now
    /// this function will throw isc::NotImplemented in case of attempt
    /// to get option definitions for V4 universe.
    ///
    /// @param u universe of the options (V4 or V6).
    ///
    /// @return collection of option definitions.
    static const OptionDefContainer& getOptionDefs(const Option::Universe u);

    /// @brief Return the first option definition matching a
    /// particular option code.
    ///
    /// @param u universe (V4 or V6)
    /// @param code option code.
    ///
    /// @return reference to an option definition being requested
    /// or NULL pointer if option definition has not been found.
    static OptionDefinitionPtr getOptionDef(const Option::Universe u,
                                            const uint16_t code);

    /// @brief Return the definition of option having a specified name.
    ///
    /// @param u universe (v4 or V6)
    /// @param name Option name.
    ///
    /// @return Pointer to the option definition or NULL pointer if option
    /// definition has not been found.
    static OptionDefinitionPtr getOptionDef(const Option::Universe u,
                                            const std::string& name);

    /// @brief Returns vendor option definition for a given vendor-id and code
    ///
    /// @param u universe (V4 or V6)
    /// @param vendor_id enterprise-id for a given vendor
    /// @param code option code
    /// @return reference to an option definition being requested
    /// or NULL pointer if option definition has not been found.
    static OptionDefinitionPtr getVendorOptionDef(const Option::Universe u,
                                                  const uint32_t vendor_id,
                                                  const uint16_t code);

    /// @brief Returns vendor option definition for a given vendor-id and
    /// option name.
    ///
    /// @param u Universe (V4 or V6)
    /// @param vendor_id Enterprise-id for a given vendor
    /// @param name Option name.
    ///
    /// @return A pointer to an option definition or NULL pointer if
    /// no option definition found.
    static OptionDefinitionPtr getVendorOptionDef(const Option::Universe u,
                                                  const uint32_t vendor_id,
                                                  const std::string& name);


    /// @brief Returns runtime (non-standard) option definition by space and
    /// option code.
    ///
    /// @param space Option space name.
    /// @param code Option code.
    ///
    /// @return Pointer to option definition or NULL if it doesn't exist.
    static OptionDefinitionPtr getRuntimeOptionDef(const std::string& space,
                                                   const uint16_t code);

    /// @brief Returns runtime (non-standard) option definition by space and
    /// option name.
    ///
    /// @param space Option space name.
    /// @param name Option name.
    ///
    /// @return Pointer to option definition or NULL if it doesn't exist.
    static OptionDefinitionPtr getRuntimeOptionDef(const std::string& space,
                                                   const std::string& name);

    /// @brief Returns runtime (non-standard) option definitions for specified
    /// option space name.
    ///
    /// @param space Option space name.
    ///
    /// @return Pointer to the container holding option definitions or NULL.
    static OptionDefContainerPtr
    getRuntimeOptionDefs(const std::string& space);

    /// @brief Check if the specified option is a standard option.
    ///
    /// @param u universe (V4 or V6)
    /// @param code option code.
    ///
    /// @return true if the specified option is a standard option.
    /// @todo We already create option definitions for the subset if
    /// standard options. We are aiming that this function checks
    /// the presence of the standard option definition and if it finds
    /// it, then the true value is returned. However, at this point
    /// this is not doable because some of the definitions (for less
    /// important options) are not created yet.
    static bool isStandardOption(const Option::Universe u,
                                 const uint16_t code);

    /// @brief Factory function to create instance of option.
    ///
    /// Factory method creates instance of specified option. The option
    /// to be created has to have corresponding factory function
    /// registered with \ref LibDHCP::OptionFactoryRegister.
    ///
    /// @param u universe of the option (V4 or V6)
    /// @param type option-type
    /// @param buf option-buffer
    ///
    /// @return instance of option.
    ///
    /// @throw isc::InvalidOperation if there is no factory function registered
    ///        for the specified option type.
    static isc::dhcp::OptionPtr optionFactory(isc::dhcp::Option::Universe u,
                                              uint16_t type,
                                              const OptionBuffer& buf);

    /// @brief Stores DHCPv4 options in a buffer.
    ///
    /// Stores all options defined in options containers in a on-wire
    /// format in output buffer specified by buf.
    ///
    /// May throw different exceptions if option assembly fails. There
    /// may be different reasons (option too large, option malformed,
    /// too many options etc.)
    ///
    /// This is v4 specific version, which stores Relay Agent Information
    /// option and END options last.
    ///
    /// @param buf output buffer (assembled options will be stored here)
    /// @param options collection of options to store to
    static void packOptions4(isc::util::OutputBuffer& buf,
                             const isc::dhcp::OptionCollection& options);

    /// @brief Stores DHCPv6 options in a buffer.
    ///
    /// Stores all options defined in options containers in a on-wire
    /// format in output buffer specified by buf.
    ///
    /// May throw different exceptions if option assembly fails. There
    /// may be different reasons (option too large, option malformed,
    /// too many options etc.)
    ///
    /// Currently there's no special logic in it. Options are stored in
    /// the order of their option codes.
    ///
    /// @param buf output buffer (assembled options will be stored here)
    /// @param options collection of options to store to
    static void packOptions6(isc::util::OutputBuffer& buf,
                             const isc::dhcp::OptionCollection& options);

    /// @brief Parses provided buffer as DHCPv6 options and creates
    /// Option objects.
    ///
    /// Parses provided buffer and stores created Option objects in
    /// options container. The last two parameters are optional and
    /// are used in relay parsing. If they are specified, relay-msg
    /// option is not created, but rather those two parameters are
    /// specified to point out where the relay-msg option resides and
    /// what is its length. This is a performance optimization that
    /// avoids unnecessary copying of potentially large relay-msg
    /// option. It is not used for anything, except in the next
    /// iteration its content will be treated as buffer to be parsed.
    ///
    /// @param buf Buffer to be parsed.
    /// @param option_space A name of the option space which holds definitions
    ///        to be used to parse options in the packets.
    /// @param options Reference to option container. Options will be
    ///        put here.
    /// @param relay_msg_offset reference to a size_t structure. If specified,
    ///        offset to beginning of relay_msg option will be stored in it.
    /// @param relay_msg_len reference to a size_t structure. If specified,
    ///        length of the relay_msg option will be stored in it.
    /// @return offset to the first byte after the last successfully
    /// parsed option
    ///
    /// @note This function throws when an option type is defined more
    /// than once, and it calls option building routines which can throw.
    /// Partial parsing does not throw: it is the responsibility of the
    /// caller to handle this condition.
    static size_t unpackOptions6(const OptionBuffer& buf,
                                 const std::string& option_space,
                                 isc::dhcp::OptionCollection& options,
                                 size_t* relay_msg_offset = 0,
                                 size_t* relay_msg_len = 0);

    /// @brief Parses provided buffer as DHCPv4 options and creates
    /// Option objects.
    ///
    /// Parses provided buffer and stores created Option objects
    /// in options container.
    ///
    /// @param buf Buffer to be parsed.
    /// @param option_space A name of the option space which holds definitions
    ///        to be used to parse options in the packets.
    /// @param options Reference to option container. Options will be
    ///        put here.
    /// @return offset to the first byte after the last successfully
    /// parsed option or the offset of the DHO_END option type.
    ///
    /// The unpackOptions6 note applies too.
    static size_t unpackOptions4(const OptionBuffer& buf,
                                 const std::string& option_space,
                                 isc::dhcp::OptionCollection& options);

    /// Registers factory method that produces options of specific option types.
    ///
    /// @throw isc::BadValue if provided the type is already registered, has
    ///        too large a value or an invalid universe is specified.
    ///
    /// @param u universe of the option (V4 or V6)
    /// @param type option-type
    /// @param factory function pointer
    static void OptionFactoryRegister(Option::Universe u,
                                      uint16_t type,
                                      Option::Factory * factory);

    /// @brief Returns v4 option definitions for a given vendor
    ///
    /// @param vendor_id enterprise-id of a given vendor
    /// @return a container for a given vendor (or NULL if not option
    ///         definitions are defined)
    static const OptionDefContainer*
    getVendorOption4Defs(const uint32_t vendor_id);

    /// @brief Returns v6 option definitions for a given vendor
    ///
    /// @param vendor_id enterprise-id of a given vendor
    /// @return a container for a given vendor (or NULL if not option
    ///         definitions are defined)
    static const OptionDefContainer*
    getVendorOption6Defs(const uint32_t vendor_id);

    /// @brief Parses provided buffer as DHCPv6 vendor options and creates
    ///        Option objects.
    ///
    /// Parses provided buffer and stores created Option objects
    /// in options container.
    ///
    /// @param vendor_id enterprise-id of the vendor
    /// @param buf Buffer to be parsed.
    /// @param options Reference to option container. Suboptions will be
    ///        put here.
    /// @return offset to the first byte after the last successfully
    /// parsed suboption
    ///
    /// @note unpackVendorOptions6 throws when it fails to parse a suboption
    /// so the return value is currently always the buffer length.
    static size_t unpackVendorOptions6(const uint32_t vendor_id,
                                       const OptionBuffer& buf,
                                       isc::dhcp::OptionCollection& options);

    /// @brief Parses provided buffer as DHCPv4 vendor options and creates
    ///        Option objects.
    ///
    /// Parses provided buffer and stores created Option objects
    /// in options container.
    ///
    /// @param vendor_id enterprise-id of the vendor
    /// @param buf Buffer to be parsed.
    /// @param options Reference to option container. Suboptions will be
    ///        put here.
    /// @return offset to the first byte after the last successfully
    /// parsed suboption
    ///
    /// The unpackVendorOptions6 note applies
    static size_t unpackVendorOptions4(const uint32_t vendor_id,
                                       const OptionBuffer& buf,
                                       isc::dhcp::OptionCollection& options);


    /// @brief Copies option definitions created at runtime.
    ///
    /// Copied option definitions will be used as "runtime" option definitions.
    /// A typical use case is to set option definitions specified by the user
    /// in the server configuration. These option definitions should be removed
    /// or replaced with new option definitions upon reconfiguration.
    ///
    /// @param defs Const reference to a container holding option definitions
    /// grouped by option spaces.
    static void setRuntimeOptionDefs(const OptionDefSpaceContainer& defs);

    /// @brief Removes runtime option definitions.
    static void clearRuntimeOptionDefs();

    /// @brief Reverts uncommited changes to runtime option definitions.
    static void revertRuntimeOptionDefs();

    /// @brief Commits runtime option definitions.
    static void commitRuntimeOptionDefs();

private:

    /// Initialize standard DHCPv4 option definitions.
    ///
    /// The method creates option definitions for all DHCPv4 options.
    /// Currently this function is not implemented.
    ///
    /// @throw std::bad alloc if system went out of memory.
    /// @throw MalformedOptionDefinition if any of the definitions
    /// are incorrect. This is programming error.
    static void initStdOptionDefs4();

    /// Initialize standard DHCPv6 option definitions.
    ///
    /// The method creates option definitions for all DHCPv6 options.
    ///
    /// @throw std::bad_alloc if system went out of memory.
    /// @throw MalformedOptionDefinition if any of the definitions
    /// is incorrect. This is a programming error.
    static void initStdOptionDefs6();

    static void initVendorOptsDocsis4();

    static void initVendorOptsDocsis6();

    /// Initialize private DHCPv6 option definitions.
    static void initVendorOptsIsc6();

    /// pointers to factories that produce DHCPv6 options
    static FactoryMap v4factories_;

    /// pointers to factories that produce DHCPv6 options
    static FactoryMap v6factories_;

    /// Container with DHCPv4 option definitions.
    static OptionDefContainer v4option_defs_;

    /// Container with DHCPv6 option definitions.
    static OptionDefContainer v6option_defs_;

    /// Container for v4 vendor option definitions
    static VendorOptionDefContainers vendor4_defs_;

    /// Container for v6 vendor option definitions
    static VendorOptionDefContainers vendor6_defs_;

    /// Container for additional option defnitions created in runtime.
    static util::StagedValue<OptionDefSpaceContainer> runtime_option_defs_;
};

}
}

#endif // LIBDHCP_H
