// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_OPAQUE_DATA_TUPLES_H
#define OPTION_OPAQUE_DATA_TUPLES_H

#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/opaque_data_tuple.h>
#include <dhcp/option.h>
#include <util/buffer.h>
#include <boost/shared_ptr.hpp>
#include <dhcp/option_data_types.h>
#include <stdint.h>

namespace isc {
namespace dhcp {

/// @brief This class encapsulates a collection of data tuples and could be
/// used by multiple options.  It is tailored for use with the DHCPv6
/// Bootfile-param option (option 60).
///
/// The format of the option is described in section 3.2 of RFC5970.
/// This option may carry an arbitrary number of tuples carrying opaque data.
/// Each tuple consists of a field holding the length of the opaque data
/// followed by a string containing the data itself.  For option 60 each
/// length field is 2 bytes long and the data is a UTF-8 string that is not
/// null terminated.
///
/// @todo The class is similar to the class used by the DHCPv6 Vendor Class
/// (16) and DHCPv4 V-I Vendor Class (124) options, though they include an
/// enterprise (or vendor) ID in the option.  In the future it may
/// make sense to rewrite the OptionVendorClass to derive from this class.
class OptionOpaqueDataTuples : public Option {
public:

    /// @brief Collection of opaque data tuples carried by the option.
    typedef std::vector<OpaqueDataTuple> TuplesCollection;

    /// @brief Constructor.
    ///
    /// This constructor creates an instance of an OptionOpaqueDataTuples
    /// that can be used for an option such as DHCPv6 Bootfile Parameters (60).
    ///
    /// @param u universe (v4 or v6).
    /// @param type option type
    /// @param length_field_type Indicates a length of the field which holds
    /// the size of the tuple. If not provided explicitly, it is evaluated
    /// basing on Option's v4/v6 universe.
    OptionOpaqueDataTuples(Option::Universe u,
                           const uint16_t type,
                           OpaqueDataTuple::LengthFieldType length_field_type = OpaqueDataTuple::LENGTH_EMPTY);

    /// @brief Constructor.
    ///
    /// This constructor creates an instance of the option using a buffer with
    /// on-wire data. It may throw an exception if the @c unpack method throws.
    ///
    /// @param u universe (v4 or v6)
    /// @param type option type
    /// @param begin Iterator pointing to the beginning of the buffer holding an
    /// option.
    /// @param end Iterator pointing to the end of the buffer holding an option.
    /// @param length_field_type Indicates a length of the field which holds
    /// the size of the tuple. If not provided explicitly, it is evaluated
    /// basing on Option's v4/v6 universe.
    OptionOpaqueDataTuples(Option::Universe u,
                           const uint16_t type,
                           OptionBufferConstIter begin,
                           OptionBufferConstIter end,
                           OpaqueDataTuple::LengthFieldType length_field_type = OpaqueDataTuple::LENGTH_EMPTY);

    /// @brief Copies this option and returns a pointer to the copy.
    OptionPtr clone() const;

    /// @brief Renders option into the buffer in the wire format.
    ///
    /// @param [out] buf Buffer to which the option is rendered.
    /// @param check if set to false, allows options larger than 255 for v4
    virtual void pack(isc::util::OutputBuffer& buf, bool check = true) const;

    /// @brief Parses buffer holding an option.
    ///
    /// This function parses the buffer holding an option and initializes option
    /// properties: the collection of tuples.
    ///
    /// @param begin Iterator pointing to the beginning of the buffer holding an
    /// option.
    /// @param end Iterator pointing to the end of the buffer holding an option.
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);

    /// @brief Adds a new opaque data tuple to the option.
    ///
    /// @param tuple Tuple to be added.
    /// @throw isc::BadValue if the type of the tuple doesn't match the
    /// universe this option belongs to.
    void addTuple(const OpaqueDataTuple& tuple);

    /// @brief Replaces tuple at the specified index with a new tuple.
    ///
    /// This function replaces an opaque data tuple at the specified position
    /// with the new tuple. If the specified index is out of range an exception
    /// is thrown.
    ///
    /// @param at Index at which the tuple should be replaced.
    /// @param tuple Tuple to be set.
    /// @throw isc::OutOfRange if the tuple position is out of range.
    /// @throw isc::BadValue if the type of the tuple doesn't match the
    /// universe this option belongs to.
    void setTuple(const size_t at, const OpaqueDataTuple& tuple);

    /// @brief Returns opaque data tuple at the specified position.
    ///
    /// If the specified position is out of range an exception is thrown.
    ///
    /// @param at Index for which tuple to get.
    /// @throw isc::OutOfRange if the tuple position is out of range.
    OpaqueDataTuple getTuple(const size_t at) const;

    /// @brief Returns the number of opaque data tuples added to the option.
    size_t getTuplesNum() const {
        return (tuples_.size());
    }

    /// @brief Returns collection of opaque data tuples carried in the option.
    const TuplesCollection& getTuples() const {
        return (tuples_);
    }

    /// @brief Checks if the object holds the opaque data tuple with the
    /// specified string.
    ///
    /// @param tuple_str String representation of the tuple being searched.
    /// @return true if the specified tuple exists for this option.
    bool hasTuple(const std::string& tuple_str) const;

    /// @brief Returns the full length of the option, including option header.
    virtual uint16_t len() const;

    /// @brief Returns text representation of the option.
    ///
    /// @param indent Number of space characters before text.
    /// @return Text representation of the option.
    virtual std::string toText(int indent = 0) const;

private:
    /// @brief length of the field which holds the size of the tuple.
    OpaqueDataTuple::LengthFieldType length_field_type_;

    /// @brief Collection of opaque data tuples carried by the option.
    TuplesCollection tuples_;

};

/// @brief Defines a pointer to the @c OptionOpaqueDataTuples.
typedef boost::shared_ptr<OptionOpaqueDataTuples> OptionOpaqueDataTuplesPtr;

}
}

#endif // OPTION_OPAQUE_DATA_TUPLES_H
