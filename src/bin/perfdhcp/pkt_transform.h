// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PKT_TRANSFORM_H
#define PKT_TRANSFORM_H

#include <dhcp/option.h>

#include "localized_option.h"

namespace isc {
namespace perfdhcp {

/// \brief Read and write raw data to DHCP packets.
///
/// This class provides static functions to read/write raw data from/to the
/// packet buffer. When reading data with the unpack() method, the
/// corresponding options objects are updated.  When writing to the packet
/// buffer with pack(), options objects carry input data to be written.
///
/// This class is used both by \ref PerfPkt4 and
/// \ref PerfPkt6 classes in case DHCP packets are created
/// from template files. In this case, some of the template
/// packet's options are replaced before sending it to the
/// server. Offset of specific options are provided from the
/// command line by the perfdhcp tool user, and passed in an
/// options collection.
class PktTransform {
public:

    /// \brief Prepares on-wire format from raw buffer.
    ///
    /// The method copies the input buffer and options contents
    /// to the output buffer. The input buffer must contain whole
    /// initial packet data. Parts of this data will be
    /// overriden by options data specified in an options
    /// collection. Such options must have their offsets within
    /// a packet specified (see \ref LocalizedOption to find out
    /// how to specify options offset).
    ///
    /// \note The specified options must fit into the size of the
    /// initial packet data. A call to this method will fail
    /// if the option's offset + its size is beyond the packet's size.
    ///
    /// \param universe Universe used, V4 or V6
    /// \param in_buffer Input buffer holding initial packet
    /// data, this can be directly read from template file
    /// \param options Options collection with offsets
    /// \param transid_offset offset of transaction id in a packet,
    /// transaction ID will be written to output buffer at this
    /// offset
    /// \param transid Transaction ID value
    /// \param out_buffer Output buffer holding "packed" data
    ///
    /// \return false, if pack operation failed.
    static bool pack(const dhcp::Option::Universe universe,
                     const dhcp::OptionBuffer& in_buffer,
                     const dhcp::OptionCollection& options,
                     const size_t transid_offset,
                     const uint32_t transid,
                     util::OutputBuffer& out_buffer);

    /// \brief Handles selective binary packet parsing.
    ///
    /// This method handles the parsing of packets that have non-default
    /// options or transaction ID offsets. The client class has to use
    /// \ref isc::dhcp::Pkt6::addOption to specify which options to parse.
    /// Each option should be of the \ref isc::perfdhcp::LocalizedOption
    /// type with the offset value specified.
    ///
    /// \param universe universe used, V4 or V6
    /// \param in_buffer input buffer to be parsed
    /// \param options options collection with options offsets
    /// \param transid_offset offset of transaction id in input buffer
    /// \param transid transaction id value read from input buffer
    ///
    /// \return false, if unpack operation failed.
    static bool unpack(const dhcp::Option::Universe universe,
                       const dhcp::OptionBuffer& in_buffer,
                       const dhcp::OptionCollection& options,
                       const size_t transid_offset,
                       uint32_t& transid);

    /// \brief Replace contents of buffer with vector.
    ///
    /// Function replaces data of the buffer with data from vector.
    ///
    /// \param in_buffer destination buffer.
    /// \param dest_pos position in destination buffer.
    /// \param first beginning of data range in source vector.
    /// \param last end of data range in source vector.
    static void writeAt(dhcp::OptionBuffer& in_buffer, size_t dest_pos,
                        std::vector<uint8_t>::iterator first,
                        std::vector<uint8_t>::iterator last);

    /// \brief Replace contents of one vector with uint16 value.
    ///
    /// Function replaces data inside one vector with uint16_t value.
    ///
    /// \param in_buffer destination buffer.
    /// \param dest_pos position in destination buffer.
    /// \param val value to be written.
    template<typename T>
    static void writeValueAt(dhcp::OptionBuffer& in_buffer, size_t dest_pos,
                        T val) {
        // @todo consider replacing the loop with switch statement
        // checking sizeof(T).
        for (int i = 0; i < sizeof(T); ++i) {
            in_buffer[dest_pos + i] = (val >> 8 * (sizeof(T) - i - 1)) & 0xFF;
        }
    }

private:
    /// \brief Replaces contents of options in a buffer.
    ///
    /// The method uses a localized options collection to
    /// replace parts of packet data (e.g. data read
    /// from template file).
    /// This private method is called from \ref PktTransform::pack
    ///
    /// \param in_buffer input buffer holding initial packet data.
    /// \param out_buffer output buffer with "packed" options.
    /// \param options options collection with actual data and offsets.
    ///
    /// \throw isc::Unexpected if options update failed.
    static void packOptions(const dhcp::OptionBuffer& in_buffer,
                            const dhcp::OptionCollection& options,
                            util::OutputBuffer& out_buffer);

    /// \brief Reads contents of specified options from buffer.
    ///
    /// The method reads options data from the input buffer
    /// and stores it in options objects. Offsets of the options
    /// must be specified (see \ref LocalizedOption to find out how to specify
    /// the option offset).
    /// This private method is called by \ref PktTransform::unpack.
    ///
    /// \note This method iterates through all options in an
    /// options collection, checks the offset of the option
    /// in input buffer and reads data from the buffer to
    /// update the option's buffer. If the provided options collection
    /// is empty, a call to this method will have no effect.
    ///
    /// \param universe universe used, V4 or V6
    /// \param in_buffer input buffer to be parsed.
    /// \param options oprions collection with their offsets
    /// in input buffer specified.
    ///
    /// \throw isc::Unexpected if options unpack failed.
    static void unpackOptions(const dhcp::OptionBuffer& in_buffer,
                              const dhcp::OptionCollection& options);

};

} // namespace perfdhcp
} // namespace isc

#endif // PKT_TRANSFORM_H
