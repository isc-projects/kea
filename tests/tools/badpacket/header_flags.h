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

#ifndef HEADER_FLAGS_H
#define HEADER_FLAGS_H

#include <exceptions/exceptions.h>
#include "option_info.h"

namespace isc {
namespace badpacket {

/// \brief Header Flags
///
/// Simple class providing easy conversion between the header flags in a DNS
/// message and a 16-bit value.

class HeaderFlags {
public:

    /// \brief Constructor
    HeaderFlags() {
        reset();
    }

    /// \brief Reset values to zero
    ///
    /// Clears all flags.
    void reset() {
        setValue(0);
    }

    /// \brief Get header flags as 16-bit value
    uint16_t getValue() const {
        return (flags_);
    }

    /// \brief Set header flags as 16-bit value
    ///
    /// \param value 16-bit value to put into object as representing the
    ///        header flags.
    void setValue(uint16_t value) {
        flags_ = value;
    }

    /// \brief Get field
    ///
    /// Return the value of a bit field in the flags word.
    ///
    /// \param int Index of the bit field in the OptionInfo data structure
    ///
    /// \return Value of the field.
    uint16_t get(int index) const {
        OptionInfo::checkIndex(index);
        return ((flags_ & OptionInfo::mask(index)) >> OptionInfo::offset(index));
    }

    /// \brief Set field
    ///
    /// Sets the value of a bit field.
    ///
    /// \param int Index of the bit field in the OptionInfo data structure
    /// \param value Value to set.  If the value is more than the field can
    ///        hold, a BadValue exception is thrown.
    void set(int index, uint16_t value) {

        // Declare an OptionInfo object for brevity and check the index is
        // valid.
        OptionInfo o;
        o.checkIndex(index);

        // Ensure the value is within limits and throw an exception if not. (This
        // should not really be needed, as the command line parsing should have
        // checked the limits.  But be safe.)
        if ((value < o.minval(index)) || (value > o.maxval(index))) {
            isc_throw(isc::BadValue, "value of index " << index << " is out of range");
        }

        // Clear the field then set it with the value.
        flags_ &= ~o.mask(index);
        flags_ |= (value << o.offset(index));
    }

private:
    uint16_t        flags_;     ///< Variable holding field values
};

} // namespace badpacket
} // namespace isc

#endif // HEADER_FLAGS_H
