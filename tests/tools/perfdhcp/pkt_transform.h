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

#ifndef __PKT_TRANSFORM_H
#define __PKT_TRANSFORM_H

#include <boost/shared_ptr.hpp>
#include <dhcp/option.h>

#include "localized_option.h"

namespace isc {
namespace perfdhcp {

/// \brief Read and write raw data to DHCP packets.
///
/// This class provides static functions to read raw
/// data from packet buffer and write raw data to packet
/// buffer. When reading data with unpack() method, the 
/// corresponding options objects are updated. 
/// When writting to the packet buffer with pack() nethod, 
/// options objects carry input data to be written.
/// This class is used both by \ref PerfPkt4 and 
/// \ref PerfPkt6 classes in case DHCP packets are created
/// from template files. In this case, some of the template
/// packet's options are replaced before sending it to 
/// server. Offset of specific options are provided from
/// command line by perfdhcp tool user and passed in
/// options collection.
/// This class also provide mechanism to read some data
/// from incoming packet buffer and update options 
/// in options collection with these data. 
/// It is assumed either in case of writting or reading
/// that all options have to be added to options collection
/// and their offset have to be specified in buffer
/// (\see LocalizedOption).
class PktTransform {
public:

    /// \brief Prepares on-wire format from raw buffer
    ///
    /// The method copies input buffer and options contents
    /// to output buffer. Input buffer must contain whole
    /// initial packet data. Parts of this data will be
    /// overriden by options data specified in options
    /// collection. Such options must have their offsets in 
    /// a packet specified (\see LocalizedOption to find out how
    /// to specify options offset).
    ///
    /// \note Specified options must fit into size of the 
    /// initial packet data. Call to this function will fail
    /// if option's offset + its size is out of bounds.
    ///
    /// \param universe universe used, V4 or V6
    /// \param in_buffer input buffer holiding intial packet
    /// data, this can be directly read from template file
    /// \param options options collection with offsets
    /// \param transid_offset offset of transaction id in a packet,
    /// transatcion id will be written to output buffer at this
    /// offset
    /// \param transid transaction id value
    /// \param out_buffer output buffer holding "packed" data
    /// 
    /// \retrun false, if pack operation failed.
    static bool pack(const dhcp::Option::Universe universe,
                     const dhcp::OptionBuffer& in_buffer,
                     const dhcp::Option::OptionCollection& options,
                     const size_t transid_offset,
                     const uint32_t transid,
                     util::OutputBuffer& out_buffer);

    /// \brief Handles limited binary packet parsing for packets with
    /// custom offsets of options and transaction id.
    ///
    /// Function handles parsing of packet that have non-default values
    /// of options or transaction id offsets. Use
    /// \ref isc::dhcp::Pkt6::addOption to specify which options to parse.
    /// Each option should be of the \ref isc::perfdhcp::LocalizedOption
    /// type with offset value indicated.
    /// Transaction id offset is specified as separate argument and 
    /// is used to read transaction id value from buffer. 
    ///
    /// \param universe universe used, V4 or V6
    /// \param in_buffer input buffer to be parsed
    /// \param options options collection with options offsets
    /// \param transid_offset offset of transaction id in input buffer
    /// \param transid transaction id value read from input buffer
    /// \return false, if unpack operation failed.
    static bool unpack(const dhcp::Option::Universe universe, 
                       const dhcp::OptionBuffer& in_buffer,
                       const dhcp::Option::OptionCollection& options,
                       const size_t transid_offset,
                       uint32_t& transid);

private:
    /// \brief Replaces options contents of options in a buffer
    ///
    /// The method uses localized options collection added to 
    /// replace parts of initial packet data (e.g. read from 
    /// template file). 
    /// This private method is called from \ref PktTransform::pack
    ///
    /// \param in_buffer input buffer holding initial packet data.
    /// \param out_buffer output buffer with "packed" options.
    /// \param options options collection with actual data and offsets.
    /// \throw isc::Unexpected if options update failed.
    static void packOptions(const dhcp::OptionBuffer& in_buffer,
                            util::OutputBuffer& out_buffer,
                            const dhcp::Option::OptionCollection& options);

    /// \brief Reads contents of specified options from buffer
    ///
    /// The method reads options data from the input buffer
    /// and stores read data in options objects. Options
    /// must have their offsets in a buffer specified 
    /// (\see LocalizedOption to find out how to specify
    /// option offset).
    /// This private method is called by \ref PktTransform::unpack.
    ///
    /// \note This method iterates through all options in 
    /// options collection, checks offset of the option
    /// in input buffer and reads data from the buffer to
    /// update option's buffer. If provided options collection
    /// is empty, call to this function will have no effect.
    /// 
    /// \param universe universe used, V4 or V6
    /// \param in_buffer input buffer to be parsed.
    /// \param options oprions collection with their offsets 
    /// in input buffer specified.
    /// \throw isc::Unexpected if options unpack failed.
    static void unpackOptions(const dhcp::Option::Universe universe,
                              const dhcp::OptionBuffer& in_buffer,
                              const dhcp::Option::OptionCollection& options);
};

} // namespace perfdhcp
} // namespace isc

#endif // __PKT_TRANSFORM_H
