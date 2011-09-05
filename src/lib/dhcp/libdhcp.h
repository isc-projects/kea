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
#include "dhcp/pkt6.h"

namespace isc {
namespace dhcp {

class LibDHCP {

public:
    /// Returns version of the library.
    ///
    /// @return string that contains libdhcp version.
    ///
    static std::string
    version();

    /// Builds collection of options.
    ///
    /// Builds raw (on-wire) data for provided collection of options.
    ///
    /// @param buf shared pointer to buffer. Data will be stored there.
    /// @param buf_len buffer length. Used for buffer overflow protection.
    /// @param offset Offset from beginning of the buffer, where store options
    /// @param options collection of options to store to
    ///
    /// @return offset to the first unused byte in buffer (next one after last
    ///         used byte)
    ///
    static unsigned int
    packOptions6(boost::shared_array<char> buf, unsigned int buf_len,
                 unsigned int offset,
                 isc::dhcp::Option::Option6Lst& options);

    ///
    /// Parses provided buffer and creates Option objects.
    ///
    /// Parses provided buf array and stores created Option objects
    /// in options container.
    ///
    /// @param buf Buffer to be parsed.
    /// @param offset Specifies offset for the first option.
    /// @param options Reference to option container. Options will be
    ///        put here.
    ///
    /// @return offset to first byte after last parsed option
    ///
    static unsigned int
    unpackOptions6(boost::shared_array<char> buf, unsigned int buf_len,
                   unsigned int offset, unsigned int parse_len,
                   isc::dhcp::Option::Option6Lst& options_);

    ///
    /// Registers factory method that produces options of specific option types.
    ///
    /// @param u universe of the option (V4 or V6)
    /// @param opt_type option-type
    /// @param factory function pointer
    ///
    /// @return true, if registration was successful, false otherwise
    ///
    static bool
    OptionFactoryRegister(Option::Universe u,
                          unsigned short type,
                          Option::Factory * factory);
protected:
    // pointers to factories that produce DHCPv6 options
    static std::map<unsigned short, Option::Factory*> v6factories_;
};

}
}

#endif
