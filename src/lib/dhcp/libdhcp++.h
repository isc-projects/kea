// Copyright (C) 2011-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LIBDHCP_H
#define LIBDHCP_H

#include <dhcp/option_definition.h>
#include <dhcp/option_space_container.h>
#include <dhcp/option_space.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <util/buffer.h>
#include <util/staged_value.h>

#include <iostream>
#include <stdint.h>
#include <string>

namespace isc {
namespace dhcp {

/// @brief A pointer to a ScopedPktOptionsCopy object instantiated using Pkt4.
typedef ScopedPktOptionsCopy<Pkt4> ScopedPkt4OptionsCopy;
/// @brief A pointer to a ScopedPktOptionsCopy object instantiated using Pkt6.
typedef ScopedPktOptionsCopy<Pkt6> ScopedPkt6OptionsCopy;
/// @brief A pointer to a ScopedSubOptionsCopy object.
typedef std::shared_ptr<ScopedSubOptionsCopy> ScopedOptionsCopyPtr;
/// @brief A container of ScopedOptionsCopyPtr objects.
typedef std::vector<ScopedOptionsCopyPtr> ScopedOptionsCopyContainer;

struct ManagedScopedOptionsCopyContainer {
    /// @brief Constructor.
    ManagedScopedOptionsCopyContainer() {
    }

    /// @brief Destructor.
    ~ManagedScopedOptionsCopyContainer() {
        // Destroy the scoped options in same order so that parent options
        // (stored last) are kept alive longer.
        for (auto& scoped : scoped_options_) {
            scoped.reset();
        }
    }

    /// @brief The container.
    ScopedOptionsCopyContainer scoped_options_;
};

class LibDHCP {

public:

    /// Map of factory functions.
    typedef std::map<unsigned short, Option::Factory*> FactoryMap;

    /// @brief Returns collection of option definitions.
    ///
    /// This method returns a collection of option definitions for a specified
    /// option space.
    ///
    /// @param space Option space.
    ///
    /// @return Pointer to a collection of option definitions.
    static const OptionDefContainerPtr getOptionDefs(const std::string& space);

    /// @brief Return the first option definition matching a
    /// particular option code.
    ///
    /// @param space option space.
    /// @param code option code.
    ///
    /// @return reference to an option definition being requested
    /// or NULL pointer if option definition has not been found.
    static OptionDefinitionPtr getOptionDef(const std::string& space,
                                            const uint16_t code);

    /// @brief Return the definition of option having a specified name.
    ///
    /// @param space option space.
    /// @param name Option name.
    ///
    /// @return Pointer to the option definition or NULL pointer if option
    /// definition has not been found.
    static OptionDefinitionPtr getOptionDef(const std::string& space,
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
    static OptionDefContainerPtr getRuntimeOptionDefs(const std::string& space);

    /// @brief Returns last resort option definition by space and option code.
    ///
    /// @param space Option space name.
    /// @param code Option code.
    ///
    /// @return Pointer to option definition or NULL if it doesn't exist.
    static OptionDefinitionPtr getLastResortOptionDef(const std::string& space,
                                                      const uint16_t code);

    /// @brief Returns last resort option definition by space and option name.
    ///
    /// @param space Option space name.
    /// @param name Option name.
    ///
    /// @return Pointer to option definition or NULL if it doesn't exist.
    static OptionDefinitionPtr getLastResortOptionDef(const std::string& space,
                                                      const std::string& name);

    /// @brief Returns last resort option definitions for specified option
    /// space name.
    ///
    /// @param space Option space name.
    ///
    /// @return Pointer to the container holding option definitions or NULL.
    static OptionDefContainerPtr getLastResortOptionDefs(const std::string& space);

    /// @brief Checks if an option unpacking has to be deferred.
    ///
    /// DHCPv4 option 43 and 224-254 unpacking is done after classification.
    ///
    /// @param space Option space name.
    /// @param code Option code.
    ///
    /// @return True if option processing should be deferred.
    static bool shouldDeferOptionUnpack(const std::string& space,
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
    /// This is v4 specific version, which stores DHCP message type first,
    /// and the Relay Agent Information option and END options last. This
    /// function is initially called to pack the options for a packet in
    /// @ref Pkt4::pack(). That call leads to it being called recursively in
    /// @ref Option::packOptions(). Thus the logic used to output the
    /// message type should only be executed by the top-most. This is governed
    /// by the parameter top, below.
    ///
    /// @param buf output buffer (assembled options will be stored here)
    /// @param options collection of options to store to
    /// @param top indicates if this is the first call to pack the options.
    /// When true logic to emit the message type first is executed. It
    /// defaults to false.
    /// @param check indicates if the code should be more flexible with
    /// PAD and END options. If true, PAD and END options will not be parsed.
    /// This is useful for partial parsing and slightly broken packets.
    static void packOptions4(isc::util::OutputBuffer& buf,
                             const isc::dhcp::OptionCollection& options,
                             bool top = false, bool check = true);

    /// @brief Split long options in multiple options with the same option code
    /// (RFC3396).
    ///
    /// @param options The option container which needs to be updated with split
    /// options.
    /// @param scopedOptions temporary storage for options that are going to be
    /// split. See @ref ScopedPktOptionsCopy for explanation.
    /// @param used The size of the buffer that has already been used by the
    /// parent option effectively shrinking the maximum supported length for
    /// each options in the container.
    /// @return True if any option has been split, false otherwise.
    static bool splitOptions4(isc::dhcp::OptionCollection& options,
                              ScopedOptionsCopyContainer& scopedOptions,
                              uint32_t used = 0);

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

    /// @brief Fuse multiple options with the same option code in long options
    /// (RFC3396).
    ///
    /// @param options The option container which needs to be updated with fused
    /// options.
    /// @return True if any option has been fused, false otherwise.
    static bool fuseOptions4(isc::dhcp::OptionCollection& options);

    /// @brief Extend vendor options from fused options in multiple OptionVendor
    /// or OptionVendorClass options and add respective suboptions or values.
    ///
    /// @param options The option container which needs to be updated with
    /// extended vendor options.
    static void extendVendorOptions4(isc::dhcp::OptionCollection& options);

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
    /// @param deferred Reference to an option code list. Options which
    ///        processing is deferred will be put here.
    /// @param flexible_pad_end Parse options 0 and 255 as PAD and END
    ///        when they are not defined in the option space.
    /// @return offset to the first byte after the last successfully
    /// parsed option or the offset of the DHO_END option type.
    ///
    /// The unpackOptions6 note applies too.
    static size_t unpackOptions4(const OptionBuffer& buf,
                                 const std::string& option_space,
                                 isc::dhcp::OptionCollection& options,
                                 std::list<uint16_t>& deferred,
                                 bool flexible_pad_end = false);

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

    /// @brief Returns option definitions for given universe and vendor
    ///
    /// @param u option universe
    /// @param vendor_id enterprise-id of a given vendor
    ///
    /// @return a container for a given vendor (or NULL if no option
    ///         definitions are defined)
    static const OptionDefContainerPtr getVendorOptionDefs(Option::Universe u,
                                                           const uint32_t vendor_id);

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

    /// @brief Reverts uncommitted changes to runtime option definitions.
    static void revertRuntimeOptionDefs();

    /// @brief Commits runtime option definitions.
    static void commitRuntimeOptionDefs();

    /// @brief Converts option space name to vendor id.
    ///
    /// If the option space name is specified in the following format:
    /// "vendor-X" where X is an uint32_t number, it is assumed to be
    /// a vendor space and the uint32_t number is returned by this function.
    /// If the option space name is invalid this method will return 0, which
    /// is not a valid vendor-id, to signal an error.
    ///
    /// @todo remove this function once when the conversion is dealt by the
    /// appropriate functions returning options by option space names.
    ///
    /// @param option_space Option space name.
    /// @return vendor id.
    static uint32_t optionSpaceToVendorId(const std::string& option_space);

private:

    /// Initialize DHCP option definitions.
    ///
    /// The method creates option definitions for all DHCP options.
    ///
    /// @throw std::bad alloc if system went out of memory.
    /// @throw MalformedOptionDefinition if any of the definitions
    /// are incorrect. This is programming error.
    static bool initOptionDefs();

    /// flag which indicates initialization state
    static bool initialized_;

    /// pointers to factories that produce DHCPv6 options
    static FactoryMap v4factories_;

    /// pointers to factories that produce DHCPv6 options
    static FactoryMap v6factories_;

    /// Container that holds option definitions for various option spaces.
    static OptionDefContainers option_defs_;

    /// Container for additional option definitions created in runtime.
    static util::StagedValue<OptionDefSpaceContainer> runtime_option_defs_;
};

}
}

#endif // LIBDHCP_H
