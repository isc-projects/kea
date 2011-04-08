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

#ifndef __HEADER_FLAGS_H
#define __HEADER_FLAGS_H

namespace isc {
namespace badpacket {

/// \brief Header Flags
///
/// Simple class providing easy conversion between the header flags in a DNS
/// message and a 16-bit value.

class HeaderFlags {
public:

    // The following declaration describes the various fields in the DNS
    // packet header.
    enum FieldParameter {
        QR_MASK = 0x8000,   // Maskd efining the field
        QR_OFF  = 15,       // Offset of field in the flags word (i.e. shift
        OP_MASK = 0x7800,   //    ... this number of bits to the left)
        OP_OFF  = 11,
        AA_MASK = 0x0400,
        AA_OFF  = 10,
        TC_MASK = 0x0200,
        TC_OFF  = 9,
        RD_MASK = 0x0100,
        RD_OFF  = 8,
        RA_MASK = 0x0080,
        RA_OFF  = 7,
        Z_MASK  = 0x0040,
        Z_OFF   = 6,
        AD_MASK = 0x0020,
        AD_OFF  = 5,
        CD_MASK = 0x0010,
        CD_OFF  = 4,
        RC_MASK = 0x000F,
        RC_OFF  = 0
    };

    /// \brief Constructor
    HeaderFlags() {
        reset();
    }

    /// \brief Reset Values to Zero
    ///
    /// Clears all flags.
    void reset() {
        setValue(0);
    }

    /// \brief Get Header Flags as 16-bit Value
    uint16_t getValue() const {
        return (flags_);
    }

    /// \brief Set Header Flags as 16-Bit Value
    ///
    /// \param value 16-bit value to put into object as representing the
    ///        header flags.
    void setValue(uint16_t value) {
        flags_ = value;
    }

    /// \brief Get QR Bit
    uint16_t getQR() const {
        return (getField(QR_MASK, QR_OFF));
    }

    /// \brief Set QR Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setQR(uint16_t value) {
        setField(value, QR_MASK, QR_OFF);
    }

    /// \brief Get OP Value
    uint16_t getOP() const {
        return (getField(OP_MASK, OP_OFF));
    }

    /// \brief Set OP Value
    ///
    /// \param value New value of the field, which must in the range 0 to 15:
    ///        values outside that range are coerced to the nearest boundary.
    void setOP(uint16_t value) {
        setField(value, OP_MASK, OP_OFF);
    }

    /// \brief Get AA Bit
    uint16_t getAA() const {
        return (getField(AA_MASK, AA_OFF));
    }

    /// \brief Set AA Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setAA(uint16_t value) {
        setField(value, AA_MASK, AA_OFF);
    }

    /// \brief Get TC Bit
    uint16_t getTC() const {
        return (getField(TC_MASK, TC_OFF));
    }

    /// \brief Set TC Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setTC(uint16_t value) {
        setField(value, TC_MASK, TC_OFF);
    }

    /// \brief Get RD Bit
    uint16_t getRD() const {
        return (getField(RD_MASK, RD_OFF));
    }

    /// \brief Set RD Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setRD(uint16_t value) {
        setField(value, RD_MASK, RD_OFF);
    }

    /// \brief Get RA Bit
    uint16_t getRA() const {
        return (getField(RA_MASK, RA_OFF));
    }

    /// \brief Set RA Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setRA(uint16_t value) {
        setField(value, RA_MASK, RA_OFF);
    }

    /// \brief Get Z Bit
    uint16_t getZ() const {
        return (getField(Z_MASK, Z_OFF));
    }

    /// \brief Set Z Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setZ(uint16_t value) {
        setField(value, Z_MASK, Z_OFF);
    }

    /// \brief Get AD Bit
    uint16_t getAD() const {
        return (getField(AD_MASK, AD_OFF));
    }

    /// \brief Set AD Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setAD(uint16_t value) {
        setField(value, AD_MASK, AD_OFF);
    }

    /// \brief Get CD Bit
    uint16_t getCD() const {
        return (getField(CD_MASK, CD_OFF));
    }

    /// \brief Set CD Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setCD(uint16_t value) {
        setField(value, CD_MASK, CD_OFF);
    }

    /// \brief Get RC Value
    uint16_t getRC() const {
        return (getField(RC_MASK, RC_OFF));
    }

    /// \brief Set RC Value
    ///
    /// \param value New value of the field, which must be in the range 0 to 15:
    ///        values outside that range are coerced to the nearest boundary.
    void setRC(uint16_t value) {
        setField(value, RC_MASK, RC_OFF);
    }

private:

    /// \brief Get Field
    ///
    /// Return the value of a bit field in the flags word.
    ///
    /// \param mask Bit mask identifying the field.
    /// \param offset Offset of the field in the flags word.
    ///
    /// \return Value of the field.
    uint16_t getField(FieldParameter mask, FieldParameter offset) const {
        return ((flags_ & mask) >> offset);
    }

    /// \brief Set Field
    ///
    /// Sets the value of a bit field.
    ///
    /// \param value Value to set.  If the value is more than the field can
    ///        hold, it is set to the maximum.
    /// \param mask Bit mask identifying the field.
    /// \param offset Offset of the field in the flags word.
    void setField(uint16_t value, FieldParameter mask, FieldParameter offset) {

        // Ensure the value is within limits.
        uint16_t maxval = mask >> offset;
        uint16_t val = (value > maxval) ? maxval : value;

        // Clear the field then set it with the value.
        flags_ &= ~mask;
        flags_ |= (val << offset);
    }

    uint16_t        flags_;     ///< Variable holding field values
};

} // namespace badpacket
} // namespace isc

#endif // __HEADER_FLAGS_H
