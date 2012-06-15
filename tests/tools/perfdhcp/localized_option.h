// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __LOCALIZED_OPTION_H
#define __LOCALIZED_OPTION_H

#include <dhcp/pkt6.h>

namespace isc {
namespace perfdhcp {

/// \brief DHCP option at specific offset
///
/// This class represents DHCP option with data placed at specified
/// offset in DHCP message.
/// Objects of this type are intended to be used when DHCP packets
/// are created from templates (e.g. read from template file).
/// Such packets have number of options with contents that have to be
/// replaced before sending: e.g. DUID can be randomized.
/// If option of this type is added to \ref PerfPkt6 options collection,
/// \ref perfdhcp::PerfPkt6 will call \ref getOffset on this object
/// to retrieve user-defined option position and replace contents of
/// the output buffer at this offset before packet is sent to the server.
/// (\see perfdhcp::PerfPkt6::rawPack).
/// In order to read on-wire data from incoming packet client class
/// has to specify options of \ref perfdhcp::LocalizedOption type
/// with expected offsets of these options in a packet. The
/// \ref perfdhcp::PerfPkt6 will use offsets to read fragments
/// of packet and store them in options' buffers.
/// (\see perfdhcp::PerfPkt6::rawUnpack).
///
class LocalizedOption : public dhcp::Option {
public:
    /// \brief Constructor, sets default (0) option offset
    ///
    /// \param u specifies universe (V4 or V6)
    /// \param type option type (0-255 for V4 and 0-65535 for V6)
    /// \param data content of the option
    LocalizedOption(dhcp::Option::Universe u,
                    uint16_t type,
                    const dhcp::OptionBuffer& data) :
        dhcp::Option(u, type, data),
        offset_(0) {
    }


    /// \brief Constructor, used to create localized option from buffer
    ///
    /// \param u specifies universe (V4 or V6)
    /// \param type option type (0-255 for V4 and 0-65535 for V6)
    /// \param data content of the option
    /// \param offset location of option in a packet (zero is default)
    LocalizedOption(dhcp::Option::Universe u,
                    uint16_t type,
                    const dhcp::OptionBuffer& data,
                    const size_t offset) :
        dhcp::Option(u, type, data),
        offset_(offset) {
    }

    /// \brief Constructor, sets default (0) option offset
    ///
    /// This contructor is similar to the previous one, but it does not take
    /// the whole vector<uint8_t>, but rather subset of it.
    ///
    /// \param u specifies universe (V4 or V6)
    /// \param type option type (0-255 for V4 and 0-65535 for V6)
    /// \param first iterator to the first element that should be copied
    /// \param last iterator to the next element after the last one
    ///        to be copied.
    LocalizedOption(dhcp::Option::Universe u,
                    uint16_t type,
                    dhcp::OptionBufferConstIter first,
                    dhcp::OptionBufferConstIter last) :
        dhcp::Option(u, type, first, last),
        offset_(0) {
    }


    /// \brief Constructor, used to create option from buffer iterators
    ///
    /// This contructor is similar to the previous one, but it does not take
    /// the whole vector<uint8_t>, but rather subset of it.
    ///
    /// \param u specifies universe (V4 or V6)
    /// \param type option type (0-255 for V4 and 0-65535 for V6)
    /// \param first iterator to the first element that should be copied
    /// \param last iterator to the next element after the last one
    ///        to be copied.
    /// \param offset offset of option in a packet (zero is default)
    LocalizedOption(dhcp::Option::Universe u,
                    uint16_t type,
                    dhcp::OptionBufferConstIter first,
                    dhcp::OptionBufferConstIter last, const size_t offset) :
        dhcp::Option(u, type, first, last),
        offset_(offset) {
    }

    /// \brief Returns offset of an option in a DHCP packet.
    ///
    /// \return option offset in a packet
    size_t getOffset() const { return offset_; };

private:
    size_t offset_;   ///< Offset of DHCP option in a packet
};


} // namespace perfdhcp
} // namespace isc

#endif // __LOCALIZED_OPTION_H
