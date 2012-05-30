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

#ifndef __PERF_PKT6_H
#define __PERF_PKT6_H

#include <time.h>
#include <boost/shared_ptr.hpp>
#include <dhcp/pkt6.h>

namespace isc {
namespace perfdhcp {

/// \brief PerfPkt6 (DHCPv6 packet)
///
/// This class extends functionality of \ref isc::dhcp::Pkt6 by
/// adding ability to specify options offset in DHCP message
/// and override options' contents with new option.
/// This approach is useful when we create paket object from
/// raw template buffer from file and we want to use it as
/// a base to create test packets to be sent to DHCP server.
///
/// Some of the contents of such a template packets always
/// have to be replaced e.g. transaction id, IA_NA. Other
/// contents (options) may be changed e.g. elapsed time,
/// server id.
///
/// In order to create packet from raw template buffer
/// we have to pass this buffer along with transaction id
/// offset. Class will read transaction id from the buffer.
/// Next, in order to replace contents of selected options
/// in a template packet, we need to add these selected options
/// to packet object using addOption() method. Please note
/// that options must be of the
/// \ref isc::perfdhcp::PerfPkt6::PositionedOption type.
///
/// This class also records timestamps of last pack/unpack
/// operation on the packet. This is to track DHCP server
/// performance based on packet's send/receive duration.
///
/// \note: if you don't use template files simply use constructors
/// inherited from parent class and isc::dhcp::Option type instead
///
class PerfPkt6 : public dhcp::Pkt6 {
public:

    /// \brief DHCPv6 option at specific offset
    ///
    /// This class represents DHCPv6 option at specified
    /// offset in DHCPv6 message.
    ///
    class PositionedOption : public dhcp::Option {
    public:

        /// \brief Constructor, sets default (0) option position
        ///
        ///
        /// \param u specifies universe (V4 or V6)
        /// \param type option type (0-255 for V4 and 0-65535 for V6)
        /// \param data content of the option
        PositionedOption(dhcp::Option::Universe u, uint16_t type, const dhcp::OptionBuffer& data);


        /// \brief Constructor, used to create positioned option from buffer
        ///
        ///
        /// \param u specifies universe (V4 or V6)
        /// \param type option type (0-255 for V4 and 0-65535 for V6)
        /// \param data content of the option
        /// \param position absolute position of option in a packet (zero is default)
        PositionedOption(dhcp::Option::Universe u, uint16_t type, const dhcp::OptionBuffer& data,
                         const size_t position);

        /// \brief Constructor, sets default (0) option position
        ///
        /// This contructor is similar to the previous one, but it does not take
        /// the whole vector<uint8_t>, but rather subset of it.
        ///
        /// \param u specifies universe (V4 or V6)
        /// \param type option type (0-255 for V4 and 0-65535 for V6)
        /// \param first iterator to the first element that should be copied
        /// \param last iterator to the next element after the last one
        ///        to be copied.
        /// \param position absolute position of option in a packet (zero is default)
        PositionedOption(dhcp::Option::Universe u, uint16_t type, dhcp::OptionBufferConstIter first,
                         dhcp::OptionBufferConstIter last);

        /// \brief Constructor, used to create positioned option from buffer iterators
        ///
        /// This contructor is similar to the previous one, but it does not take
        /// the whole vector<uint8_t>, but rather subset of it.
        ///
        /// \param u specifies universe (V4 or V6)
        /// \param type option type (0-255 for V4 and 0-65535 for V6)
        /// \param first iterator to the first element that should be copied
        /// \param last iterator to the next element after the last one
        ///        to be copied.
        /// \param position absolute position of option in a packet (zero is default)
        PositionedOption(dhcp::Option::Universe u, uint16_t type, dhcp::OptionBufferConstIter first,
                         dhcp::OptionBufferConstIter last, const size_t position);


        /// \brief Returns absolute position (offset) of an option in a
        /// DHCPv6 packet.
        ///
        /// \return absolute position (offset) of an option in a packet
        size_t getOptionPosition() const { return position_; };

    private:
        size_t position_;   ///< Absolute position of DHCPv6 option in a packet
    };

    typedef boost::shared_ptr<PositionedOption> PositionedOptionPtr;

    /// Constructor, used in message transmission
    ///
    /// Creates new DHCPv6 message using provided buffer. New object
    /// will keep copy of contents of provided buffer. If buffer contains
    /// options at custom offsets (e.g. if packet was read from
    /// template file) additional information about options'
    /// offsets has to be provided - see
    /// \ref isc::perfdhcp::PositionedOption for details.
    ///
    /// Transaction id is not considered DHCP option so
    /// we pass it to constructor as extra argument. This is
    /// required if transaction id offset differs from the
    /// default one for DHCPv6 messages (ocets 2-4).
    ///
    /// \note use this constructor only in case you want to create
    /// DHCPv6 message (incoming or outgoing) from the raw buffer
    /// and you know options offsets. Options offsets are
    /// specified from perfdhcp command line by the user.
    ///
    /// \param buf pointer to a buffer of received packet content
    /// \param len size of buffer of packet content
    /// \param xid_off transaction id offset in a packet
    PerfPkt6(const uint8_t* buf,
             uint32_t len,
             size_t transid_offset_);

    /// \brief Returns transaction id offset in packet buffer
    ///
    /// return transaction id offset in packet buffer
    size_t getTransIdOffset() const { return transid_offset_; };

    /// \brief Returns current packet timestamp
    ///
    /// \return current packet timestamp
    timespec getTimestamp() const { return time_stamp_; }

    /// \brief Prepare on-wire packet format and record timestamp
    ///
    /// Prepares on-wire format of packet and all its options.
    /// This method wraps dhcp::Pkt6::pack() function to
    /// update packet timestamp.
    ///
    /// \note Use this function if you don't use template files
    /// to construct DHCPv6 packets.
    ///
    /// \throw isc::Unexpected if pack and timestamp update failed
    void stampedPack();

    /// \brief Handles binary packet parsing and updates timestamp
    ///
    /// This method wraps dhcp::Pkt6::unpack() function to
    /// update packet timestamp.
    ///
    /// \note Use this function if you don't use template files
    /// and custom options offsets to construct DHCPv6 packets.
    ///
    /// \throw isc::Unexpected if function failed
    void stampedUnpack();

    /// \brief Prepares on-wire format from raw buffer
    ///
    /// The method copies user buffer to output buffer and
    /// extracts transaction id from it based on transaction id
    /// offset provided in constructor.
    /// Eventually, this method updates packet timestamp.
    ///
    /// \note: Use this method to prepare on-wire DHCPv6 message
    /// when you use template packets that require replacement
    /// of selected options contents before sending.
    ///
    /// \throw isc::Unexepected if function failed
    void stampedRawPack();

    /// \brief Handles limited binary packet parsing for packets with
    /// custom offsets of options and transaction id
    ///
    /// Function handles reception of packets that have non-default values
    /// of options or transaction id offsets. Use
    /// \ref isc::dhcp::Pkt6::addOption to specify which options to parse.
    /// Each option should be of the: isc::perfdhcp::PerfPkt6::PositionedOption
    /// type with offset value indicated.
    ///
    /// \throw isc::Unexpected if function failed
    void stampedRawUnpack();

private:

    /// \brief Updates options in the output buffer
    ///
    /// This method updates options in the output buffer
    /// with the ones provided with
    /// \ref isc::dhcp::Pkt6::addOption. It is expected
    /// that these options will be of the
    /// \ref isc::perfdhcp::PerfPkt6::PositionedOption type
    /// with their position (offset) specified.
    ///
    /// throw isc::Unexpected if options update fails
    void updateOptions();

    void rawUnpackOptions();

    /// \brief Update packet timestamp with current time
    ///
    /// \throw isc::Unexpected if timestamp update failed
    void updateTimestamp();

    size_t transid_offset_;      ///< transaction id offset
    timespec time_stamp_;        ///< time stamp of last pack or unpack

};

} // namespace perfdhcp
} // namespace isc

#endif // __PERF_PKT6_H
