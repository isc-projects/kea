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

#ifndef __PERF_PKT4_H
#define __PERF_PKT4_H

#include <time.h>
#include <boost/shared_ptr.hpp>
#include <dhcp/pkt4.h>

#include "localized_option.h"

namespace isc {
namespace perfdhcp {

/// \brief PerfPkt4 (DHCPv4 packet)
///
/// This class extends functionality of \ref isc::dhcp::Pkt4 by
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
/// \ref isc::perfdhcp::LocalizedOption type.
///
/// \note: if you don't use template files simply use constructors
/// inherited from parent class and isc::dhcp::Option type instead
///
class PerfPkt4 : public dhcp::Pkt4 {
public:

    /// Localized option pointer type.
    typedef boost::shared_ptr<LocalizedOption> LocalizedOptionPtr;

    /// \brief Constructor, used for outgoing and incoming messages
    ///
    /// This constructor initializes transaction id and
    /// transaction id offset of the packet with default
    /// values.
    ///
    /// \param buf buffer holding contents of the message.
    /// \param len length of the data in the buffer.
    PerfPkt4(const uint8_t* buf, size_t len);

    /// \brief Constructor, used for outgoing DHCP messages.
    ///
    /// Creates new DHCPv4 message using provided buffer.
    /// Transaction id and its offset are specified through this
    /// constructor so as they are stored in outgoing message
    /// when client class calls \ref PerfPkt4::rawPack.
    ///
    /// \note This constructor should be used only for outgoing
    /// messages that are created from raw buffer (e.g. read from
    /// template files).
    ///
    /// \param buf buffer holiding contents of the message (this can
    /// be directly read from template file).
    /// \param len length of the data in the buffer.
    /// \param transid_offset transaction id offset in outgoing message.
    /// \param transid transaction id to be stored in outgoing message.
    PerfPkt4(const uint8_t* buf,
             size_t len,
             size_t transid_offset,
             uint32_t transid);

    /// Constructor, used for incoming DHCP messages.
    ///
    /// Creates new DHCPv6 message using provided buffer. New object
    /// will keep copy of contents of provided buffer. If buffer contains
    /// options at custom offsets (e.g. if packet was read from
    /// template file) additional information about options'
    /// offsets has to be provided - see
    /// \ref isc::perfdhcp::LocalizedOption for details.
    ///
    /// Transaction id offset point to location of raw data where
    /// transaction id field is stored. The transaction id will
    /// be read from this location when PerfPkt4::rawUnpack is
    /// called. The transid_ class member will be updated accordingly.
    ///
    /// \note use this constructor only in case you want to create
    /// incoming DHCPv6 object from the raw buffer
    /// and you know options offsets. Options offsets are
    /// specified from perfdhcp command line by the user.
    ///
    /// \param buf pointer to a buffer of received packet content.
    /// \param len size of buffer of packet content.
    /// \param transid_offset transaction id offset in a message.
    PerfPkt4(const uint8_t* buf,
             size_t len,
             size_t transid_offset);

    /// \brief Returns transaction id offset in packet buffer
    ///
    /// return transaction id offset in packet buffer
    size_t getTransIdOffset() const { return transid_offset_; };

    /// \brief Prepares on-wire format from raw buffer
    ///
    /// The method copies user buffer to output buffer and
    /// extracts transaction id from it based on transaction id
    /// offset provided in constructor.
    ///
    /// \note: Use this method to prepare on-wire DHCPv6 message
    /// when you use template packets that require replacement
    /// of selected options' contents before sending.
    ///
    /// \retrun false, id pack operation failed.
    bool rawPack();

    /// \brief Handles limited binary packet parsing for packets with
    /// custom offsets of options and transaction id
    ///
    /// Function handles reception of packets that have non-default values
    /// of options or transaction id offsets. Use
    /// \ref isc::dhcp::Pkt4::addOption to specify which options to parse.
    /// Each option should be of the: isc::perfdhcp::LocalizedOption
    /// type with offset value indicated.
    ///
    /// \return false, if unpack operation failed.
    bool rawUnpack();

    /// \brief Update packet timestamp with current time
    ///
    /// \throw isc::Unexpected if timestamp update failed
    void updateTimestamp();

private:
    size_t transid_offset_;      ///< transaction id offset

};

} // namespace perfdhcp
} // namespace isc

#endif // __PERF_PKT4_H
