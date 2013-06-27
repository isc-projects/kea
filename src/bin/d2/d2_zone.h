// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef D2_ZONE_H
#define D2_ZONE_H

#include <dns/name.h>
#include <dns/rrclass.h>

#include <boost/shared_ptr.hpp>

namespace isc {
namespace d2 {

/// @brief The @c D2Zone encapsulates the Zone section in DNS Update message.
///
/// This class is used by the @c D2UpdateMessage to encapsulate the Zone section
/// of the DNS Update message. Class members hold corresponding values of
/// section's fields: NAME, CLASS. This class does not hold the RTYPE field
/// value because RTYPE is always equal to SOA for DNS Update message (see
/// RFC 2136, section 2.3).
///
/// Note, that this @c D2Zone class neither exposes functions to decode messages
/// from wire format nor to encode to wire format. This is not needed, because
/// @c isc::d2::D2UpdateMessage class uses @c D2Zone only to return the parsed
/// Zone information to the caller. Internally, D2UpdateMessage parses and
/// stores Zone section using @c isc::dns::Question class, and the @c toWire
/// and @c fromWire functions of the @c isc::dns::Question class are used.
class D2Zone {
public:
    /// @brief Constructor from Name and RRClass.
    ///
    /// @param name The name of the Zone.
    /// @param rrclass The RR class of the Zone.
    D2Zone(const dns::Name& name, const dns::RRClass& rrclass);

    ///
    /// @name Getters
    ///
    //@{
    /// @brief Returns the Zone name.
    ///
    /// @return A reference to the Zone name.
    const dns::Name& getName() const { return (name_); }

    /// @brief Returns the Zone class.
    ///
    /// @return A reference to the Zone class.
    const dns::RRClass& getClass() const { return (rrclass_); }
    //@}

    /// @brief Returns text representation of the Zone.
    ///
    /// This function concatenates the name of the Zone, Class and Type.
    /// The type is always SOA.
    ///
    /// @return A text representation of the Zone.
    std::string toText() const;

    ///
    /// @name Comparison Operators
    ///
    //@{
    /// @brief Equality operator to compare @c D2Zone objects in query and
    /// response messages.
    ///
    /// @param rhs Zone to compare against.
    ///
    /// @return true if name and class are equal, false otherwise.
    bool operator==(const D2Zone& rhs) const {
        return ((rrclass_ == rhs.rrclass_) && (name_ == rhs.name_));
    }

    /// @brief Inequality operator to compare @c D2Zone objects in query and
    /// response messages.
    ///
    /// @param rhs Zone to compare against.
    ///
    /// @return true if any of name or class are unequal, false otherwise.
    bool operator!=(const D2Zone& rhs) const {
        return (!operator==(rhs));
    }
    //@}

private:
    dns::Name name_;       ///< Holds the Zone name.
    dns::RRClass rrclass_; ///< Holds the Zone class.
};

typedef boost::shared_ptr<D2Zone> D2ZonePtr;

/// @brief Insert the @c D2Zone as a string into stream.
///
/// @param os A @c std::ostream object on which the insertion operation is
/// performed.
/// @param zone A reference to the @c D2Zone object output by the
/// operation.
///
/// @return A reference to the same @c std::ostream object referenced by
/// parameter @c os after the insertion operation.
std::ostream& operator<<(std::ostream& os, const D2Zone& zone);

} // namespace d2
} // namespace isc

#endif // D2_ZONE_H
