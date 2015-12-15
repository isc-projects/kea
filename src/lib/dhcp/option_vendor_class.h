// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_VENDOR_CLASS_H
#define OPTION_VENDOR_CLASS_H

#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/opaque_data_tuple.h>
#include <dhcp/option.h>
#include <util/buffer.h>
#include <boost/shared_ptr.hpp>
#include <stdint.h>

namespace isc {
namespace dhcp {

/// @brief This class encapsulates DHCPv6 Vendor Class and DHCPv4 V-I Vendor
/// Class options.
///
/// The format of DHCPv6 Vendor Class option (16) is described in section 22.16
/// of RFC3315 and the format of the DHCPv4 V-I Vendor Class option (124) is
/// described in section 3 of RFC3925. Each of these options carries enterprise
/// id followed by the collection of tuples carring opaque data. A single tuple
/// consists of the field holding opaque data length and the actual data.
/// In case of the DHCPv4 V-I Vendor Class each tuple is preceded by the
/// 4-byte long enterprise id. Also, the field which carries the length of
/// the tuple is 1-byte long for DHCPv4 V-I Vendor Class and 2-bytes long
/// for the DHCPv6 Vendor Class option.
///
/// Whether the encapsulated format is DHCPv4 V-I Vendor Class or DHCPv6
/// Vendor Class option is controlled by the @c u (universe) parameter passed
/// to the constructor.
///
/// @todo Currently, the enterprise id field is set to a value of the first
/// enterprise id occurrence in the parsed option. At some point we should
/// be able to differentiate between enterprise ids.
class OptionVendorClass : public Option {
public:

    /// @brief Collection of opaque data tuples carried by the option.
    typedef std::vector<OpaqueDataTuple> TuplesCollection;

    /// @brief Constructor.
    ///
    /// This constructor instance of the DHCPv4 V-I Vendor Class option (124)
    /// or DHCPv6 Vendor Class option (16), depending on universe specified.
    /// If the universe is v4, the constructor adds one empty tuple to the
    /// option, as per RFC3925, section 3. the complete option must hold at
    /// least one data-len field for opaque data. If the specified universe
    /// is v6, the constructor adds no tuples.
    ///
    /// @param u universe (v4 or v6).
    /// @param vendor_id vendor enterprise id (unique 32-bit integer).
    OptionVendorClass(Option::Universe u, const uint32_t vendor_id);

    /// @brief Constructor.
    ///
    /// This constructor creates an instance of the option using a buffer with
    /// on-wire data. It may throw an exception if the @c unpack method throws.
    ///
    /// @param u universe (v4 or v6)
    /// @param begin Iterator pointing to the beginning of the buffer holding an
    /// option.
    /// @param end Iterator pointing to the end of the buffer holding an option.
    OptionVendorClass(Option::Universe u, OptionBufferConstIter begin,
                      OptionBufferConstIter end);

    /// @brief Renders option into the buffer in the wire format.
    ///
    /// @param [out] buf Buffer to which the option is rendered.
    virtual void pack(isc::util::OutputBuffer& buf);

    /// @brief Parses buffer holding an option.
    ///
    /// This function parses the buffer holding an option and initializes option
    /// properties: enterprise ids and the collection of tuples.
    ///
    /// @param begin Iterator pointing to the beginning of the buffer holding an
    /// option.
    /// @param end Iterator pointing to the end of the buffer holding an option.
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);

    /// @brief Returns enterprise id.
    uint32_t getVendorId() const {
        return (vendor_id_);
    }

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

    /// @brief Checks if the Vendor Class holds the opaque data tuple with the
    /// specified string.
    ///
    /// @param tuple_str String representation of the tuple being searched.
    /// @return true if the specified tuple exists for this option.
    bool hasTuple(const std::string& tuple_str) const;

    /// @brief Returns the full length of the option, including option header.
    virtual uint16_t len();

    /// @brief Returns text representation of the option.
    ///
    /// @param indent Number of space characters before text.
    /// @return Text representation of the option.
    virtual std::string toText(int indent = 0);

private:

    /// @brief Returns option code appropriate for the specified universe.
    ///
    /// This function is called by the constructor to map the specified
    /// universe to the option code.
    ///
    /// @param u universe (V4 or V6).
    /// @return DHCPv4 V-I Vendor Class or DHCPv6 Vendor Class option code.
    static uint16_t getOptionCode(Option::Universe u) {
        return (u == V4 ? DHO_VIVCO_SUBOPTIONS : D6O_VENDOR_CLASS);
    }

    /// @brief Returns the tuple length field type for the given universe.
    ///
    /// This function returns the length field type which should be used
    /// for the opaque data tuples being added to this option.
    ///
    /// @return Tuple length field type for the universe this option belongs to.
    OpaqueDataTuple::LengthFieldType getLengthFieldType() const {
        return (getUniverse() == V4 ? OpaqueDataTuple::LENGTH_1_BYTE :
                OpaqueDataTuple::LENGTH_2_BYTES);
    }

    /// @brief Returns minimal length of the option for the given universe.
    uint16_t getMinimalLength() const {
        return (getUniverse() == Option::V4 ? 7 : 8);
    }

    /// @brief Enterprise ID.
    uint32_t vendor_id_;

    /// @brief Collection of opaque data tuples carried by the option.
    TuplesCollection tuples_;

};

/// @brief Defines a pointer to the @c OptionVendorClass.
typedef boost::shared_ptr<OptionVendorClass> OptionVendorClassPtr;

}
}

#endif // OPTION_VENDOR_CLASS_H
