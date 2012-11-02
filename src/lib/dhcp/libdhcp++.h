// Copyright (C) 2011-2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef LIBDHCP_H_
#define LIBDHCP_H_

#include <dhcp/option_definition.h>
#include <dhcp/pkt6.h>
#include <util/buffer.h>
#include <iostream>

namespace isc {
namespace dhcp {

class LibDHCP {

public:

    /// Map of factory functions.
    typedef std::map<unsigned short, Option::Factory*>  FactoryMap;

    /// @brief Return collection of option definitions.
    ///
    /// @param u universe of the options (V4 or V6).
    /// @return collection of option definitions.
    static const OptionDefContainer& getOptionDefs(Option::Universe u);

    /// @brief Factory function to create instance of option.
    ///
    /// Factory method creates instance of specified option. The option
    /// to be created has to have corresponding factory function
    /// registered with \ref LibDHCP::OptionFactoryRegister.
    ///
    /// @param u universe of the option (V4 or V6)
    /// @param type option-type
    /// @param buf option-buffer
    /// @throw isc::InvalidOperation if there is no factory function
    /// registered for specified option type.
    /// @return instance of option.
    static isc::dhcp::OptionPtr optionFactory(isc::dhcp::Option::Universe u,
                                              uint16_t type,
                                              const OptionBuffer& buf);

    /// Builds collection of options.
    ///
    /// Builds raw (on-wire) data for provided collection of options.
    ///
    /// @param buf output buffer (assembled options will be stored here)
    /// @param options collection of options to store to
    static void packOptions6(isc::util::OutputBuffer& buf,
                             const isc::dhcp::Option::OptionCollection& options);


    /// @brief Stores options in a buffer.
    ///
    /// Stores all options defined in options containers in a on-wire
    /// format in output buffer specified by buf.
    ///
    /// May throw different exceptions if option assembly fails. There
    /// may be different reasons (option too large, option malformed,
    /// too many options etc.)
    ///
    /// @param buf output buffer (assembled options will be stored here)
    /// @param options collection of options to store to
    static void packOptions(isc::util::OutputBuffer& buf,
                            const isc::dhcp::Option::OptionCollection& options);

    /// @brief Parses provided buffer as DHCPv4 options and creates Option objects.
    ///
    /// Parses provided buffer and stores created Option objects
    /// in options container.
    ///
    /// @param buf Buffer to be parsed.
    /// @param options Reference to option container. Options will be
    ///        put here.
    static size_t unpackOptions4(const OptionBuffer& buf,
                                 isc::dhcp::Option::OptionCollection& options);

    /// @brief Parses provided buffer as DHCPv6 options and creates Option objects.
    ///
    /// Parses provided buffer and stores created Option objects
    /// in options container.
    ///
    /// @param buf Buffer to be parsed.
    /// @param options Reference to option container. Options will be
    ///        put here.
    static size_t unpackOptions6(const OptionBuffer& buf,
                                 isc::dhcp::Option::OptionCollection& options);

    /// Registers factory method that produces options of specific option types.
    ///
    /// @exception BadValue if provided type is already registered, has too large
    ///            value or invalid universe is specified
    ///
    /// @param u universe of the option (V4 or V6)
    /// @param type option-type
    /// @param factory function pointer
    static void OptionFactoryRegister(Option::Universe u,
                                      uint16_t type,
                                      Option::Factory * factory);

    /// Initialize standard DHCP options (V4 or V6).
    ///
    /// The method creates option definitions for all options
    /// (DHCPv4 or DHCPv6 depending on universe specified).
    /// Currently DHCPv4 option definitions initialization is not
    /// implemented thus this function will throw isc::NotImplemented
    /// if V4 universe is specified.
    ///
    /// @param u universe
    /// @throw isc::Unexpected if internal error occured during option
    /// definitions creation.
    /// @throw std::bad_alloc if system went out of memory.
    /// @throw isc::NotImplemented when V4 universe specified.
    static void initStdOptionDefs(Option::Universe u);

private:

    /// Initialize standard DHCPv4 option definitions.
    ///
    /// The method creates option definitions for all DHCPv4 options.
    /// Currently this function is not implemented.
    ///
    /// @todo implemend this function.
    ///
    /// @throw isc::NotImplemeneted
    static void initStdOptionDefs4();

    /// Initialize standard DHCPv6 option definitions.
    ///
    /// The method creates option definitions for all DHCPv6 options.
    ///
    /// @throw isc::Unexpected if internal error occured during option
    /// definitions creation.
    /// @throw std::bad_alloc if system went out of memory.
    static void initStdOptionDefs6();

    /// pointers to factories that produce DHCPv6 options
    static FactoryMap v4factories_;

    /// pointers to factories that produce DHCPv6 options
    static FactoryMap v6factories_;

    /// Container with DHCPv4 option definitions.
    static OptionDefContainer v4option_defs_;

    /// Container with DHCPv6 option definitions.
    static OptionDefContainer v6option_defs_;
};

}
}

#endif
