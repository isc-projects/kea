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

#ifndef OPTION_INFO_H
#define OPTION_INFO_H

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
/// Some of the fields are no applicable to all options.  For example, some of
/// the options correspond to fields in the flags word of the DNS message
/// header, so the information includes details about the position of the fields
/// and an appropriate bit mask.
///
/// Note that the class does not hold values specified on the command line - it
/// only holds information about the available options.

class OptionInfo {
public:

    /// \brief Array Indexes
    ///
    /// The data for the flags options are held in an array.  Although declared
    /// as an enum, only the numeric values are used as they are the indexes
    /// into the array.
    enum Index {
        FLAGS_START = 0,    // Start of flags field codes
        QR = 0,             // Query/response
        OP = 1,             // Opcode
        AA = 2,             // Authoritative answer
        TC = 3,             // Truncated
        RD = 4,             // Recursion desired
        RA = 5,             // Recursion available
        Z  = 6,             // Zero (reserved)
        AD = 7,             // Authenticated data
        CD = 8,             // Checking disabled
        RC = 9,             // Response code
        FLAGS_END = 9,      // End of flags field codes
        COUNT_START = 10,   // Start of count fields
        QC = 10,            // Query count
        AC = 11,            // Answer count
        UC = 12,            // Authority count
        DC = 13,            // Additional count
        COUNT_END = 13,     // End of count fields
        OTHER_START = 14,   // Start of other fields
        MS = 14,            // Message size
        OTHER_END = 14,     // End of other fields
        SIZE = 15           // Number of index values
    };

    /// \brief Option parameters
    ///
    /// Defines a structure that holds information associated with each of the
    /// flags field command options.  Not all members of the structure are
    /// relevant to all options.
    struct Parameter {
        const char      short_form;     // Short form of the command switch
        const char*     long_form;      // Long form of the command switch
        int             word;           // Byte offset of word in message header
        uint16_t        mask;           // Bit mask of field in the flags word
        int             offset;         // Offset of field in flags word
        uint32_t        defval;         // Default value
        uint32_t        minval;         // Minimum valid value for this field
        uint32_t        maxval;         // Maximum valid value for this field
    };

    /// \brief Return index for command option
    ///
    /// Given the short form of a command-line option, return the index in the
    /// options array corresponding to that option.
    ///
    /// \param c The character that is the short form of the command line option.
    ///        An 'int' is used as the value passed will be the return value
    ///        from 'getopt()' (or equivalent) which is an int.  If the
    ///        character is not found, an exception will be thrown.
    ///
    /// \return A valid index value.
    static int getIndex(int c);

    /// \brief Return long form of command switch for this field
    ///
    /// \param index A valid index (one of the values in the 'Index' enum).
    ///
    /// \return The long option name (e.q. "qr" for the Query/Response field).
    static const char* name(int index);

    /// \brief Return header word offset
    ///
    /// Returns the byte offset in the DNS message header of the two-byte word 
    /// holding the data in question.
    ///
    /// \param index A valid index (one of the values in the 'Index' enum).
    ///
    /// \return The offset in the header for this datum.
    static int word(int index);

    /// \brief Return mask associated with switch field
    ///
    /// \param index A valid index (one of the values in the 'Index' enum).
    ///
    /// \return The mask for this particular option in the DNS message flags
    ///         word.  The returned value is only valid for options that
    ///         correspond to fields in the flags word.
    static uint16_t mask(int index);

    /// \brief Return offset associated with option field
    ///
    /// \param index A valid index (one of the values in the 'Index' enum).
    ///
    /// \return The offset of the field corresponding to this option in the DNS
    ///         message flags field.  The returned value is only valid for
    ///         options that correpond to fields in the flags word.
    static int offset(int index);

    /// \brief Return minimum allowed value of an option
    ///
    /// \param index A valid index (one of the values in the 'Index' enum).
    ///
    /// \return Minimum allowed value for this option.
    static uint32_t minval(int index);

    /// \brief Return default value of an option
    ///
    /// \param index A valid index (one of the values in the 'Index' enum).
    ///
    /// \return Default value for this option
    static uint32_t defval(int index);

    /// \brief Return maximum allowed value of an option
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
    static void checkIndex(int i) {
        if ((i < 0) || (i >= SIZE)) {
            isc_throw(isc::OutOfRange, "option index must be in the range "
                      "0 to " << SIZE);
        }
    }
};

} // namespace badpacket
} // namespace isc

#endif // OPTION_INFO_H
