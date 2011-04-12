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

#ifndef __OPTION_INFO_H
#define __OPTION_INFO_H

#include <stdint.h>
#include "exceptions/exceptions.h"

namespace isc {
namespace badpacket {

/// \brief Option Information
///
/// Holds details about the options that can be specified on the command line
/// that require values.  Some of these options correspond to fields in the
/// DNS message header, and information about these fields is supplied.

class OptionInfo {
public:

    /// \brief Array Indexes
    ///
    /// The data for the flags options are held in an array.  This enum
    /// specifies the position of the data for each flags field.
    enum Index {
        QR = 0,
        OP = 1,
        AA = 2,
        TC = 3,
        RD = 4,
        RA = 5,
        Z  = 6,
        AD = 7,
        CD = 8,
        RC = 9,
        SIZE = 10   // Number of index values
    };

    /// \brief Option Parameters
    ///
    /// Defines a structure that holds information associated with each of the
    /// flags field command options.
    struct Parameter {
        const char*     long_form;      // Long form of the command switch
        uint16_t        mask;           // Bit mask of the field in the flags word
        int             offset;         // Offset of field in flags word
        uint32_t        minval;         // Minimum valid value for this field
        uint32_t        maxval;         // Maximum valid value for this field
    };

    /// \brief Return long form of command switch for this field
    static const char* name(Index i);

    /// \brief Return mask associated with switch field
    static uint16_t mask(Index i);

    /// \brief Return offset associated with switch field
    static int offset(Index i);

    /// \brief Return minimum allowed value of field
    static uint32_t minval(Index i);

    /// \brief Return maximum allowed value of field
    static uint32_t maxval(Index i);

private:
    /// \brief Check Array Index
    ///
    /// Checks the passed field index and throws an exception if out of range.
    static void checkIndex(Index i) {
        if ((i < 0) || (i >= SIZE)) {
            isc_throw(isc::OutOfRange, "option index must be in the range "
                      "0 to " << SIZE);
        }
    }
};

} // namespace badpacket
} // namespace isc

#endif // __OPTION_INFO_H
