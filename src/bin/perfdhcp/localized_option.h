// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LOCALIZED_OPTION_H
#define LOCALIZED_OPTION_H

#include <dhcp/pkt6.h>
#include <dhcp/option6_ia.h>
#include <util/buffer.h>

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

    /// \brief Constructor, used to create localized option from buffer.
    ///
    /// This constructor creates localized option using whole provided
    /// option buffer.
    ///
    /// \param u universe (V4 or V6).
    /// \param type option type (0-255 for V4 and 0-65535 for V6).
    /// Option values 0 and 255 (v4) and 0 (v6) are not valid option
    /// codes but they are accepted here for the server testing purposes.
    /// \param data content of the option.
    /// \param offset location of option in a packet (zero is default).
    LocalizedOption(dhcp::Option::Universe u,
                    uint16_t type,
                    const dhcp::OptionBuffer& data,
                    const size_t offset = 0) :
        dhcp::Option(u, type, data),
        offset_(offset), option_valid_(true) {
    }

    /// \brief Constructor, used to create option from buffer iterators.
    ///
    /// This constructor creates localized option using part of the
    /// option buffer pointed by iterators.
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
                    dhcp::OptionBufferConstIter last,
                    const size_t offset = 0) :
        dhcp::Option(u, type, first, last),
        offset_(offset), option_valid_(true) {
    }

    /// \brief Copy constructor, creates LocalizedOption from Option6IA.
    ///
    /// This copy constructor creates regular option from Option6IA.
    /// The data from Option6IA data members are copied to
    /// option buffer in appropriate sequence.
    ///
    /// \param opt_ia option to be copied.
    /// \param offset location of the option in a packet.
    LocalizedOption(const boost::shared_ptr<dhcp::Option6IA>& opt_ia,
                    const size_t offset) :
        dhcp::Option(Option::V6, 0, dhcp::OptionBuffer()),
        offset_(offset), option_valid_(false) {
        // If given option is NULL we will mark this new option
        // as invalid. User may query if option is valid when
        // object is created.
        if (opt_ia) {
            // Set universe and type.
            universe_ = opt_ia->getUniverse();
            type_ = opt_ia->getType();
            util::OutputBuffer buf(opt_ia->len() - opt_ia->getHeaderLen());
            try {
                // Try to pack option data into the temporary buffer.
                opt_ia->pack(buf);
                if (buf.getLength() > 0) {
                    const char* buf_data = static_cast<const char*>(buf.getData());
                    // Option has been packed along with option type flag
                    // and transaction id so we have to skip first 4 bytes
                    // when copying temporary buffer option buffer.
                    data_.assign(buf_data + 4, buf_data + buf.getLength());
                }
                option_valid_ = true;
            } catch (const Exception&) {
                // If there was an exception somewhere when packing
                // the data into the buffer we assume that option is
                // not valid and should not be used.
                option_valid_ = false;
            }
        } else {
            option_valid_ = false;
        }
    }

    /// \brief Returns offset of an option in a DHCP packet.
    ///
    /// \return option offset in a packet
    size_t getOffset() const { return offset_; };

    /// \brief Checks if option is valid.
    ///
    /// \return true, if option is valid.
    virtual bool valid() {
        return (Option::valid() && option_valid_);
    }

private:
    size_t offset_;   ///< Offset of DHCP option in a packet
    bool option_valid_; ///< Is option valid.
};


} // namespace isc::perfdhcp
} // namespace isc

#endif // LOCALIZED_OPTION_H
