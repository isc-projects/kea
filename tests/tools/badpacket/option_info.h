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
/// that require values and which control data put in the DNS message sent to
/// the remote system.
///
/// Currently all of these options correspond to fields in the flags word of the
/// DNS message header, so the information includes details about the position
/// of the fields and an appropriate bit mask.
///
/// Note that the class does not hold values specified on the command line - it
/// only holds information about command-line options.

class OptionInfo {
public:

    /// \brief Array Indexes
    ///
    /// The data for the flags options are held in an array.  Although an enum,
    /// only the numeric values are used - they are indexes into arrays.
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
        const char      short_form;     // Short form of the command switch
        const char*     long_form;      // Long form of the command switch
        uint16_t        mask;           // Bit mask of the field in the flags word
        int             offset;         // Offset of field in flags word
        uint32_t        minval;         // Minimum valid value for this field
        uint32_t        maxval;         // Maximum valid value for this field
    };

    /// \brief Return index for command option
    ///
    /// Given the short form of a switch, return the index into the options
    /// array.
    ///
    /// \param c The character that is the short form of the command line option.
    ///        An 'int' is used as the value passed will be the return vaue from
    ///        'getopt()' (or equivalent) which is an int.
    ///
    /// \return A valid index value (else an exception is thrown).
    static int getIndex(int c);

    /// \brief Return long form of command switch for this field
    ///
    /// \param index A valid index (one of the values in the 'Index' enum).
    ///
    /// \return The long option name (e.q. "qr" for the Query/Response field).
    static const char* name(int index);

    /// \brief Return mask associated with switch field
    ///
    /// \param index A valid index (one of the values in the 'Index' enum).
    ///
    /// \return The mask for this particular option in the DNS message flags field.
    static uint16_t mask(int index);

    /// \brief Return offset associated with switch field
    ///
    /// \param index A valid index (one of the values in the 'Index' enum).
    ///
    /// \return The offset of the field corresponding to this option in the DNS
    ///         message flags field.
    static int offset(int index);

    /// \brief Return minimum allowed value of field
    ///
    /// \param index A valid index (one of the values in the 'Index' enum).
    ///
    /// \return Minimum allowed value for this option.  This is usually 0.
    static uint32_t minval(int index);

    /// \brief Return maximum allowed value of field
    ///
    /// \param index A valid index (one of the values in the 'Index' enum).
    ///
    /// \return Maximum allowed value for this option.  If the option is a bit
    ///         in the flags field of the DNS message hearder, this will be 1.
    static uint32_t maxval(int index);

    /// \brief Check Array Index
    ///
    /// Checks the passed field index and throws an exception if it does not
    /// correspond to one of the valid indexes in the 'Index' enum.
    ///
    /// \param index An index value.
    ///
    static void checkIndex(int i) {
        if ((i < 0) || (i >= SIZE)) {
            isc_throw(isc::OutOfRange, "option index must be in the range "
                      "0 to " << SIZE);
        }
    }
};

} // namespace badpacket
} // namespace isc

#endif // __OPTION_INFO_H
