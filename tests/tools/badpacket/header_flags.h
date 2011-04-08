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
    struct Flags {
        unsigned int rc : 4;
        unsigned int cd : 1;
        unsigned int ad : 1;
        unsigned int z  : 1;    // Reserved
        unsigned int ra : 1;
        unsigned int rd : 1;
        unsigned int tc : 1;
        unsigned int aa : 1;
        unsigned int op : 4;
        unsigned int qr : 1;
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

    /// \brief Set Header Flags as 16-Bit Value
    ///
    /// \param value 16-bit value to put into object as representing the
    ///        header flags.
    void setValue(uint16_t value) {
        flags_.value = value;
    }

    /// \brief Get Header Flags as 16-bit Value
    uint16_t getValue() const {
        return flags_.value;
    }
    
    /// \brief Get QR Bit
    uint16_t getQR() const {
        return flags_.fields.qr;
    }

    /// \brief Set QR Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setQR(uint16_t value) {
        flags_.fields.qr = (value > 1) ? 1 : value;
    }
    
    /// \brief Get OP Value
    uint16_t getOP() const {
        return flags_.fields.op;
    }

    /// \brief Set OP Value
    ///
    /// \param value New value of the field, which must in the range 0 to 15:
    ///        values outside that range are coerced to the nearest boundary.
    void setOP(uint16_t value) {
        flags_.fields.op = (value > 15) ? 15 : value;
    }
    
    /// \brief Get AA Bit
    uint16_t getAA() const {
        return flags_.fields.aa;
    }

    /// \brief Set AA Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setAA(uint16_t value) {
        flags_.fields.aa = (value > 1) ? 1 : value;
    }
    
    /// \brief Get TC Bit
    uint16_t getTC() const {
        return flags_.fields.tc;
    }

    /// \brief Set TC Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setTC(uint16_t value) {
        flags_.fields.tc = (value > 1) ? 1 : value;
    }
    
    /// \brief Get RD Bit
    uint16_t getRD() const {
        return flags_.fields.rd;
    }

    /// \brief Set RD Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setRD(uint16_t value) {
        flags_.fields.rd = (value > 1) ? 1 : value;
    }
    
    /// \brief Get RA Bit
    uint16_t getRA() const {
        return flags_.fields.ra;
    }

    /// \brief Set RA Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setRA(uint16_t value) {
        flags_.fields.ra = (value > 1) ? 1 : value;
    }
    
    /// \brief Get Z Bit
    uint16_t getZ() const {
        return flags_.fields.z;
    }

    /// \brief Set Z Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setZ(uint16_t value) {
        flags_.fields.z = (value > 1) ? 1 : value;
    }
    
    /// \brief Get AD Bit
    uint16_t getAD() const {
        return flags_.fields.ad;
    }

    /// \brief Set AD Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setAD(uint16_t value) {
        flags_.fields.ad = (value > 1) ? 1 : value;
    }
    
    /// \brief Get CD Bit
    uint16_t getCD() const {
        return flags_.fields.cd;
    }

    /// \brief Set CD Bit
    ///
    /// \param value New value of the field, which must be 0 or 1: values
    ///        outside that range are coerced to the nearest boundary.
    void setCD(uint16_t value) {
        flags_.fields.cd = (value > 1) ? 1 : value;
    }
    
    /// \brief Get RC Value
    uint16_t getRC() const {
        return flags_.fields.rc;
    }

    /// \brief Set RC Value
    ///
    /// \param value New value of the field, which must be in the range 0 to 15:
    ///        values outside that range are coerced to the nearest boundary.
    void setRC(uint16_t value) {
        flags_.fields.rc = (value > 15) ? 15 : value;
    }

private:

    // The variable that performs the conversion
    union {
        uint16_t        value;
        Flags           fields;
    } flags_;
};

} // namespace badpacket
} // namespace isc

#endif // __HEADER_FLAGS_H
