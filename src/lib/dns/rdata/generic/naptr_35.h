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

// BEGIN_HEADER_GUARD

#include <string>

#include <dns/name.h>
#include <dns/rdata.h>
#include <util/buffer.h>

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

/// \brief \c NAPTR class represents the NAPTR rdata defined in
/// RFC2915, RFC2168 and RFC3403
///
/// This class implements the basic interfaces inherited from the
/// \c rdata::Rdata class, and provides accessors specific to the
/// NAPTR rdata.
class NAPTR : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    // NAPTR specific methods
    uint16_t getOrder() const;
    uint16_t getPreference() const;
    const std::string& getFlags() const;
    const std::string& getServices() const;
    const std::string& getRegexp() const;
    const Name& getReplacement() const;
private:
    /// Helper template function for toWire()
    ///
    /// \param outputer Where to write data in
    template <typename T>
    void toWireHelper(T& outputer) const {
        outputer.writeUint16(order_);
        outputer.writeUint16(preference_);

        outputer.writeUint8(flags_.size());
        outputer.writeData(flags_.c_str(), flags_.size());

        outputer.writeUint8(services_.size());
        outputer.writeData(services_.c_str(), services_.size());

        outputer.writeUint8(regexp_.size());
        outputer.writeData(regexp_.c_str(), regexp_.size());
    }

    uint16_t order_;
    uint16_t preference_;
    std::string flags_;
    std::string services_;
    std::string regexp_;
    Name replacement_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables:
// mode: c++
// End:
