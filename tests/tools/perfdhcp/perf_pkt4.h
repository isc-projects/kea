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
/// and override options' contents.
/// This is in particular useful when we create packet object using
/// template file (do not build it dynamically). Client class
/// should read data from template file and pass data to this class
/// as buffer.
/// Contents of such packet can be later partially replaced: preciselly
/// selected options and transaction id can be replaced.
/// Transaction id and its offset in template file is passed via
/// constructor.
/// In order to replace contents of options client class has to
/// create collection of \ref LocalizedOption by adding them using
/// \ref dhcp::Pkt4::addOption.
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
    /// Transaction id and its offset are specified via this
    /// constructor. Transaction id is stored in outgoing message
    /// when client class calls \ref PerfPkt4::rawPack.
    ///
    /// \note This constructor should be used only for outgoing
    /// messages that are created from template files.
    ///
    /// \param buf buffer holding contents of the message (this can
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
    /// Creates new DHCPv4 message using provided buffer.
    /// Client class may indicate which options are to be read
    /// from the buffer. Such options should be added to
    /// options collection using dhcp::Pkt4::addOption. Such
    /// options should be of \ref LocalizedOption class.
    ///
    /// Transaction id offset points to location where
    /// transaction id field is stored. The transaction id will
    /// be read from this location when PerfPkt4::rawUnpack is
    /// called. The transid_ class member will be updated accordingly.
    ///
    /// \note use this constructor only in case you want to create
    /// incoming DHCPv4 object from the raw buffer
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

    /// \brief Prepares on-wire format from raw buffer.
    ///
    /// The method copies buffer provided in constructor to
    /// output buffer and replaces transaction id and selected
    /// options with new data.
    ///
    /// \note: Use this method to prepare on-wire DHCPv4 message
    /// when you use template packets that require replacement
    /// of selected options' contents before sending.
    ///
    /// \retrun false, id pack operation failed.
    bool rawPack();

    /// \brief Handles limited binary packet parsing for packets with
    /// custom offsets of options and transaction id
    ///
    /// Function handles parsing of packets that have custom offsets
    /// of options or transaction id. Use
    /// \ref isc::dhcp::Pkt4::addOption to specify which options to parse.
    /// Options should be of the: isc::perfdhcp::LocalizedOption
    /// type with offset values provided. Each added option will
    /// be updated with actual data read from the binary packet buffer.
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
