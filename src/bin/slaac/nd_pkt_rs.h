// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ND_PKT_RS_H
#define ND_PKT_RS_H

#include <nd_pkt.h>

namespace isc {

namespace slaac {

/// @brief Class for classes representing Router Solicitation messages.
///
///      0                   1                   2                   3
///      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
///     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///     |     Type      |     Code      |          Checksum             |
///     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///     |                            Reserved                           |
///     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///     |   Options ...
///     +-+-+-+-+-+-+-+-+-+-+-+-
///
class RSPkt : public NDPkt {
public:

    /// @brief Minimal RS length.
    static const size_t RS_MIN_LEN = 8;

    /// @brief Constructor.
    ///
    /// This constructor is typically used for transmitted messages as it
    /// creates an empty (no options) packet.
    ///
    /// @param local_addr local IPv6 address
    /// @param remote_addr remote IPv6 address
    RSPkt(const isc::asiolink::IOAddress& local_addr,
          const isc::asiolink::IOAddress& remote_addr);

    /// @brief Constructor.
    ///
    /// This constructor is typically used for received messages as it takes
    /// a buffer that's going to be parsed as one of arguments.
    ///
    /// @param buf pointer to a buffer that contains on-wire data
    /// @param len length of the pointer specified in buf
    /// @param local_addr local IPv4 or IPv6 address
    /// @param remote_addr remote IPv4 or IPv6 address
    RSPkt(const uint8_t* buf, uint32_t len,
          const isc::asiolink::IOAddress& local_addr,
          const isc::asiolink::IOAddress& remote_addr);

    /// @brief Prepares on-wire format of RS packet.
    ///
    /// Prepares on-wire format of message and all its options.
    /// A caller must ensure that options are stored in options_ field
    /// prior to calling this method.
    ///
    /// Output buffer will be stored in buffer_out_.
    /// The buffer_out_ should be cleared before writing to the buffer
    /// in the derived classes.
    ///
    /// @throw InvalidOperation if packing fails
    virtual void pack();

    /// @brief Parses on-wire form of RS packet.
    ///
    /// Parses received packet, stored in on-wire format in data_.
    ///
    /// Will create a collection of option objects that will
    /// be stored in options_ container.
    ///
    /// Method will throw exception if packet parsing fails.
    virtual void unpack();

    /// @brief Returns text representation of the packet.
    ///
    /// This function is useful mainly for debugging.
    ///
    /// @return string with text representation
    virtual std::string toText() const;

    /// @brief Returns packet size in binary format.
    ///
    /// Returns size of the packet in on-wire format or size needed to store
    /// it in on-wire format.
    ///
    /// @return packet size in bytes
    virtual size_t len();

    /// @brief Returns name of the ND message.
    ///
    /// For all unsupported messages the derived classes must return
    /// "UNKNOWN".
    ///
    /// @return Pointer to "const" string containing ND message name.
    /// The implementations in the derived classes should statically
    /// allocate returned strings and the caller must not release the
    /// returned pointer.
    virtual const char* getName() const { return ("RS"); };

    /// @brief Virtual destructor.
    ///
    /// There is nothing to clean up here, but since there are virtual methods,
    /// we define virtual destructor to ensure that derived classes will have
    /// a virtual one, too.
    virtual ~RSPkt() {
    }
};

/// @brief A pointer to either RS packet
typedef boost::shared_ptr<isc::slaac::RSPkt> RSPktPtr;

}; // namespace isc::slaac
}; // namespace isc

#endif
