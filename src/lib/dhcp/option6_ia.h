// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef OPTION_IA_H
#define OPTION_IA_H

#include <dhcp/option.h>

#include <stdint.h>

namespace isc {
namespace dhcp {

class Option6IA: public Option {

public:
    /// Length of IA_NA and IA_PD content
    const static size_t OPTION6_IA_LEN = 12;

    /// @brief Ctor, used for constructed options, usually during transmission.
    ///
    /// @param type option type (usually 4 for IA_NA, 25 for IA_PD)
    /// @param iaid identity association identifier (id of IA)
    Option6IA(uint16_t type, uint32_t iaid);

    /// @brief Ctor, used for received options.
    ///
    /// @param type option type (usually 4 for IA_NA, 25 for IA_PD)
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    Option6IA(uint16_t type, OptionBuffer::const_iterator begin,
              OptionBuffer::const_iterator end);

    /// Writes option in wire-format to buf, returns pointer to first unused
    /// byte after stored option.
    ///
    /// @param buf buffer (option will be stored here)
    void pack(isc::util::OutputBuffer& buf);

    /// @brief Parses received buffer
    ///
    /// Parses received buffer and returns offset to the first unused byte after
    /// parsed option.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);

    /// Provides human readable text representation
    ///
    /// @param indent number of leading space characters
    ///
    /// @return string with text represenation
    virtual std::string
    toText(int indent = 0);

    /// Sets T1 timer.
    ///
    /// @param t1 t1 value to be set
    void setT1(uint32_t t1) { t1_ = t1; }

    /// Sets T2 timer.
    ///
    /// @param t2 t2 value to be set
    void setT2(uint32_t t2) { t2_ = t2; }

    /// Sets Identity Association Identifier.
    ///
    /// @param iaid IAID value to be set
    void setIAID(uint32_t iaid) { iaid_ = iaid; }

    /// Returns IA identifier.
    ///
    /// @return IAID value.
    ///
    uint32_t getIAID() const { return iaid_; }

    /// Returns T1 timer.
    ///
    /// @return T1 value.
    uint32_t getT1() const { return t1_; }

    /// Returns T2 timer.
    ///
    /// @return T2 value.
    uint32_t getT2() const { return t2_; }

    /// @brief returns complete length of option
    ///
    /// Returns length of this option, including option header and suboptions
    ///
    /// @return length of this option
    virtual uint16_t len();

protected:

    /// keeps IA identifier
    uint32_t iaid_;

    /// keeps T1 timer value
    uint32_t t1_;

    /// keeps T2 timer value
    uint32_t t2_;
};

} // isc::dhcp namespace
} // isc namespace

#endif // OPTION_IA_H
