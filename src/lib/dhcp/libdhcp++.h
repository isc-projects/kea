// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <iostream>
#include <util/buffer.h>
#include <dhcp/pkt6.h>

namespace isc {
namespace dhcp {

class LibDHCP {

public:
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
    static uint32_t unpackOptions4(const OptionBuffer& buf,
                                   isc::dhcp::Option::OptionCollection& options);

    /// @brief Parses provided buffer as DHCPv6 options and creates Option objects.
    ///
    /// Parses provided buffer and stores created Option objects
    /// in options container.
    ///
    /// @param buf Buffer to be parsed.
    /// @param options Reference to option container. Options will be
    ///        put here.
    static uint32_t unpackOptions6(const OptionBuffer& buf,
                                   isc::dhcp::Option::OptionCollection& options);

    /// Registers factory method that produces options of specific option types.
    ///
    /// @exception BadValue if provided type is already registered, has too large
    ///            value or invalid universe is specified
    ///
    /// @param u universe of the option (V4 or V6)
    /// @param opt_type option-type
    /// @param factory function pointer
    static void OptionFactoryRegister(Option::Universe u,
                                      uint16_t type,
                                      Option::Factory * factory);
protected:
    /// pointers to factories that produce DHCPv6 options
    static std::map<unsigned short, Option::Factory*> v4factories_;

    /// pointers to factories that produce DHCPv6 options
    static std::map<unsigned short, Option::Factory*> v6factories_;
};

}
}

#endif
