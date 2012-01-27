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

#ifndef OPTION_IA_H_
#define OPTION_IA_H_

#include <stdint.h>
#include "option.h"

namespace isc {
namespace dhcp {

class Option6IA: public Option {

public:
    /// Length of IA_NA and IA_PD content
    const static size_t OPTION6_IA_LEN = 12;

    /// @brief ctor, used for options constructed, usually during transmission
    ///
    /// @param type option type (usually 4 for IA_NA, 25 for IA_PD)
    /// @param iaid identity association identifier (id of IA)
    Option6IA(uint16_t type, uint32_t iaid);

    /// @brief ctor, used for received options
    ///
    /// boost::shared_array allows sharing a buffer, but it requires that
    /// different instances share pointer to the whole array, not point
    /// to different elements in shared array. Therefore we need to share
    /// pointer to the whole array and remember offset where data for
    /// this option begins
    ///
    /// @param type option type (usually 4 for IA_NA, 25 for IA_PD)
    /// @param buf buffer to be parsed
    /// @param buf_len buffer length
    /// @param offset offset in buffer
    /// @param len number of bytes to parse
    Option6IA(uint16_t type, const boost::shared_array<uint8_t>& buf,
              unsigned int buf_len, unsigned int offset, unsigned int len);

    /// Writes option in wire-format to buf, returns pointer to first unused
    /// byte after stored option.
    ///
    /// @param buf buffer (option will be stored here)
    /// @param buf_len (buffer length)
    /// @param offset offset place where option should be stored
    ///
    /// @return offset to the first unused byte after stored option
    unsigned int
    pack(boost::shared_array<uint8_t>& buf, unsigned int buf_len,
         unsigned int offset);

    /// @brief Parses received buffer
    ///
    /// Parses received buffer and returns offset to the first unused byte after
    /// parsed option.
    ///
    /// @param buf pointer to buffer
    /// @param buf_len length of buf
    /// @param offset offset, where start parsing option
    /// @param parse_len how many bytes should be parsed
    ///
    /// @return offset after last parsed octet
    virtual unsigned int
    unpack(const boost::shared_array<uint8_t>& buf, unsigned int buf_len,
           unsigned int offset, unsigned int parse_len);

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
    void setT1(unsigned int t1) { t1_=t1; }


    /// Sets T2 timer.
    ///
    /// @param t2 t2 value to be set
    void setT2(unsigned int t2) { t2_=t2; }

    /// Returns IA identifier.
    ///
    /// @return IAID value.
    ///
    unsigned int getIAID() const { return iaid_; }

    /// Returns T1 timer.
    ///
    /// @return T1 value.
    unsigned int getT1() const { return t1_; }

    /// Returns T2 timer.
    ///
    /// @return T2 value.
    unsigned int getT2() const { return t2_; }

    /// @brief returns complete length of option
    ///
    /// Returns length of this option, including option header and suboptions
    ///
    /// @return length of this option
    virtual uint16_t
    len();

protected:

    /// keeps IA identifier
    unsigned int iaid_;

    /// keeps T1 timer value
    unsigned int t1_;

    /// keeps T2 timer value
    unsigned int t2_;
};

} // isc::dhcp namespace
} // isc namespace

#endif /* OPTION_IA_H_ */
