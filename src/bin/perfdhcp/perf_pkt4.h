// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PERF_PKT4_H
#define PERF_PKT4_H

#include <time.h>
#include <boost/shared_ptr.hpp>
#include <dhcp/pkt4.h>

#include "localized_option.h"
#include "pkt_transform.h"

namespace isc {
namespace perfdhcp {

/// \brief PerfPkt4 (DHCPv4 packet)
///
/// This class extends the functionality of \ref isc::dhcp::Pkt4 by adding the
/// ability to specify an options offset in the DHCP message and to override
/// options' contents.  This is particularly useful when we create a packet
/// object using a template file (i.e. do not build it dynamically). The client
/// class should read data from the template file and pass it to this class in
/// a buffer.
///
/// The contents of such a packet can be later partially replaced, notably the
/// selected options and the transaction ID.  (The transaction ID and its
/// offset in the template file are passed via the constructor.)
///
/// In order to replace contents of the options, the client class has to
/// create a collection of \ref LocalizedOption, adding them using
/// \ref dhcp::Pkt4::addOption.
///
/// \note If you don't use template files simply use constructors
/// inherited from parent class and isc::dhcp::Option type instead

class PerfPkt4 : public dhcp::Pkt4 {
public:

    /// Localized option pointer type.
    typedef boost::shared_ptr<LocalizedOption> LocalizedOptionPtr;

    /// \brief Constructor, used to create  messages from packet
    /// template files.
    ///
    /// Creates a new DHCPv4 message using the provided buffer.
    /// The transaction ID and its offset are specified via this
    /// constructor. The transaction ID is stored in outgoing message
    /// when client class calls \ref PerfPkt4::rawPack. Transaction id
    /// offset value is used for incoming and outgoing messages to
    /// identify transaction ID field's position in incoming and outgoing
    /// messages.
    ///
    /// \param buf buffer holding contents of the message (this can
    /// be directly read from template file).
    /// \param len length of the data in the buffer.
    /// \param transid_offset transaction id offset in a message.
    /// \param transid transaction id to be stored in outgoing message.
    PerfPkt4(const uint8_t* buf,
             size_t len,
             size_t transid_offset = 1,
             uint32_t transid = 0);

    /// \brief Returns transaction id offset in packet buffer
    ///
    /// \return Transaction ID offset in packet buffer
    size_t getTransidOffset() const { return transid_offset_; };

    /// \brief Prepares on-wire format from raw buffer.
    ///
    /// The method copies the buffer provided in the constructor to the
    /// output buffer and replaces the transaction ID and selected
    /// options with new data.
    ///
    /// \note Use this method to prepare an on-wire DHCPv4 message
    /// when you use template packets that require replacement
    /// of selected options' contents before sending.
    ///
    /// \return false ID pack operation failed.
    bool rawPack();

    /// \brief Handles limited binary packet parsing for packets with
    /// custom offsets of options and transaction ID
    ///
    /// This method handles the parsing of packets that have custom offsets
    /// of options or transaction ID. Use
    /// \ref isc::dhcp::Pkt4::addOption to specify which options to parse.
    /// Options should be of the \ref isc::perfdhcp::LocalizedOption
    /// type with offset values provided. Each added option will
    /// be updated with actual data read from the binary packet buffer.
    ///
    /// \return false If unpack operation failed.
    bool rawUnpack();

    /// \brief Replace contents of buffer with data.
    ///
    /// Function replaces part of the buffer with data from vector.
    ///
    /// \param dest_pos position in buffer where data is replaced.
    /// \param first beginning of data range in source vector.
    /// \param last end of data range in source vector.
    void writeAt(size_t dest_pos,
                 std::vector<uint8_t>::iterator first,
                 std::vector<uint8_t>::iterator last);

    /// \brief Replace contents of buffer with value.
    ///
    /// Function replaces part of buffer with value.
    ///
    /// \param dest_pos position in buffer where value is
    /// to be written.
    /// \param val value to be written.
    template<typename T>
    void writeValueAt(size_t dest_pos, T val) {
        PktTransform::writeValueAt<T>(data_, dest_pos, val);
    }

private:
    size_t transid_offset_;      ///< transaction id offset

};

typedef boost::shared_ptr<PerfPkt4> PerfPkt4Ptr;

} // namespace perfdhcp
} // namespace isc

#endif // PERF_PKT4_H
