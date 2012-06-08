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

#ifndef __PERF_PKT6_H
#define __PERF_PKT6_H

#include <time.h>
#include <boost/shared_ptr.hpp>
#include <dhcp/pkt6.h>

#include "localized_option.h"

namespace isc {
namespace perfdhcp {

/// \brief PerfPkt6 (DHCPv6 packet)
///
/// This class extends the functionality of \ref isc::dhcp::Pkt6 by
/// adding the ability to specify an options offset in the DHCP message
/// and so override the options' contents. This is particularly useful when we
/// create a packet object using a template file (i.e. do not build it
/// dynamically). The client class should read the data from the template file
/// and pass it to this class as a buffer.
///
/// The contents of such packet can be later partially replaced: in particular,
/// selected options and the transaction ID can be altered. (The transaction
/// ID and its offset in the template file is passed via the constructor.)
///
/// In order to replace the contents of options, the client class has to
/// create a collection of \ref LocalizedOption by adding them using
/// \ref dhcp::Pkt6::addOption.
///
/// \note If you don't use template files, simply use constructors
/// inherited from parent class and the \ref isc::dhcp::Option type instead.

class PerfPkt6 : public dhcp::Pkt6 {
public:

    /// Localized option pointer type.
    typedef boost::shared_ptr<LocalizedOption> LocalizedOptionPtr;

    /// \brief Constructor, used for outgoing and incoming messages
    ///
    /// This constructor initializes the transaction ID and the
    /// transaction ID offset of the packet with default
    /// values.
    ///
    /// \param buf buffer holding contents of the message.
    /// \param len length of the data in the buffer.
    PerfPkt6(const uint8_t* buf, size_t len);

    /// \brief Constructor, used for outgoing DHCP messages.
    ///
    /// Creates a new DHCPv6 message using the provided buffer.
    /// The transaction ID and its offset are specified via this
    /// constructor. The transaction ID is stored in outgoing message
    /// when client class calls \ref PerfPkt6::rawPack.
    ///
    /// \note This constructor should be used only for outgoing
    /// messages that are created from template files.
    ///
    /// \param buf buffer holding contents of the message (this can
    /// be directly read from template file).
    /// \param len length of the data in the buffer.
    /// \param transid_offset transaction id offset in outgoing message.
    /// \param transid transaction id to be stored in outgoing message.
    PerfPkt6(const uint8_t* buf,
             size_t len,
             size_t transid_offset,
             uint32_t transid);

    /// Constructor, used for incoming DHCP messages.
    ///
    /// Creates a new DHCPv6 message using the provided buffer. The
    /// client class may indicate which options are to be read
    /// from the buffer. Such options should be added to the
    /// options collection using \ref dhcp::Pkt4::addOption. The
    /// options should be of \ref LocalizedOption class.
    ///
    /// The transaction ID offset points to location where the
    /// transaction ID field is stored. The transaction ID will
    /// be read from this location when \ref PerfPkt4::rawUnpack is
    /// called. The transid_ class member will be updated accordingly.
    ///
    /// \note Use this constructor only in the case where you want to create
    /// incoming DHCPv4 object from the raw buffer
    /// and you know the options offsets. Options offsets are
    /// specified on the perfdhcp command line by the user.
    ///
    /// \param buf pointer to a buffer of received packet content.
    /// \param len size of buffer of packet content.
    /// \param transid_offset transaction id offset in a message.
    PerfPkt6(const uint8_t* buf,
             size_t len,
             size_t transid_offset);

    /// \brief Returns transaction id offset in packet buffer
    ///
    /// \return Transaction ID offset in the packet buffer.
    size_t getTransIdOffset() const { return transid_offset_; };

    /// \brief Prepares on-wire format from raw buffer
    ///
    /// The method copies the buffer provided in constructor to the
    /// output buffer and replaces the transaction ID and selected
    /// options with new data.
    ///
    /// \note Use this method to prepare an on-wire DHCPv6 message
    /// when you use template packets that require replacement
    /// of selected options' contents before sending.
    ///
    /// \return false ID pack operation failed.
    bool rawPack();

    /// \brief Handles limited binary packet parsing for packets with
    /// custom offsets of options and transaction id
    ///
    /// This methoid handles the parsing of packets that have custom offsets
    /// of options or transaction ID. Use
    /// \ref isc::dhcp::Pkt4::addOption to specify which options to parse.
    /// Options should be of the \ref isc::perfdhcp::LocalizedOption
    /// type with offset values provided. Each added option will
    /// be updated with actual data read from the binary packet buffer.
    ///
    /// \return false if unpack operation failed.
    bool rawUnpack();

private:
    size_t transid_offset_;      ///< transaction id offset

};

} // namespace perfdhcp
} // namespace isc

#endif // __PERF_PKT6_H
