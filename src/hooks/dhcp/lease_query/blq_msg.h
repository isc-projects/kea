// Copyright (C) 2022-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BLQ_MSG_H
#define BLQ_MSG_H

#include <config.h>
#include <dhcp/pkt.h>
#include <tcp/tcp_stream_msg.h>

namespace isc {
namespace lease_query {

/// @brief Defines a Bulk LeaseQuery transaction id.
typedef uint32_t Xid;

/// @brief Lease Query specific wrapper around DHCPx packet.
/// The class is intended as a wrapper around DHCP<4/6> packets to isolate
/// lease query infrastructure from protocol specifics as well as
/// provide an opportunity to house and add lease query specifics.
class BlqMsg {
public:
    /// @brief Constructor
    ///
    /// @param pkt  Pointer to the DHCPx lease query packet
    BlqMsg(dhcp::PktPtr pkt)
        : pkt_(pkt) {
        if (!pkt) {
            isc_throw(BadValue, "BlqMsg::pkt cannot be empty");
        }
    }

    /// @brief Destructor.
    virtual ~BlqMsg() {
    }

    /// @brief Returns the transaction id.
    Xid getXid() const {
        return (pkt_->getTransid());
    }

    /// @brief Sets the transaction id.
    ///
    /// @param xid new transaction id
    void setXid(const Xid& xid) {
        pkt_->setTransid(xid);
    }

    /// @brief Returns a pointer to the DHCPx packet.
    dhcp::PktPtr getPkt() const {
        return (pkt_);
    }

    /// @brief Packs the packet into wire form ready for TCP transmission.
    void pack() {
        // We need the wire form of the query, so pack it.
        pkt_->pack();
        auto buffer = pkt_->getBuffer();

        // Prepend the length of the request.
        uint16_t size = static_cast<uint16_t>(buffer.getLength());
        wire_data_.reserve(size + 2);
        wire_data_.push_back(static_cast<uint8_t>((size & 0xff00U) >> 8));
        wire_data_.push_back(static_cast<uint8_t>(size & 0x00ffU));

        // Add on the packet data.
        auto const& data = buffer.getVector();
        wire_data_.insert(wire_data_.end(), data.cbegin(), data.cend());
    }

    /// @brief Returns size of the packed wire data.
    size_t getWireSize() const {
        return (wire_data_.size());
    }

    /// @brief Returns a reference to the wire data.
    tcp::WireData& getWireData() {
        return (wire_data_);
    }

protected:
    /// @brief The DHCP(4/6) packet containing the query.
    dhcp::PktPtr pkt_;

    /// @brief Holds the TCP stream wire form of the query.
    tcp::WireData wire_data_;
};

/// @brief Defines a shared pointer to an BlqMsg.
typedef boost::shared_ptr<BlqMsg> BlqMsgPtr;

/// @brief Holds a bulk lease query query packet.
class BlqQuery : public BlqMsg {
public:
    /// @brief Constructor.
    ///
    /// @param query Pointer to the DHCPx lease query query packet.
    BlqQuery(dhcp::PktPtr query)
        : BlqMsg(query) {
    }

    /// @brief Destructor.
    virtual ~BlqQuery() {
    }

    /// @brief Returns the DHCPx query packet.
    dhcp::PktPtr getQuery() {
        return (getPkt());
    }
};

/// @brief Defines a shared pointer to an BlqQuery.
typedef boost::shared_ptr<BlqQuery> BlqQueryPtr;

/// @brief Contains a list of BlqQuery pointers.
typedef std::list<BlqQueryPtr> BlqQueryList;

/// @brief Holds a bulk lease query response packet.
/// Queries can result in an arbitrary number of responses
/// e.g. one per matching client (more or less).
class BlqResponse : public BlqMsg {
public:
    /// @brief Constructor.
    ///
    /// @param response Pointer to the DHCPx lease query response packet.
    BlqResponse(dhcp::PktPtr response)
        : BlqMsg(response) {
    }

    /// @brief Destructor.
    virtual ~BlqResponse() {};

    /// @brief Returns the DHCPx response packet.
    dhcp::PktPtr getResponse() {
        return (getPkt());
    }
};

/// @brief Defines a shared pointer to an BlqResponse.
typedef boost::shared_ptr<BlqResponse> BlqResponsePtr;

/// @brief Contains a list of BlqResponse pointers.
typedef std::list<BlqResponsePtr> BlqResponseList;

} // end of namespace isc::lease_query
} // end of namespace isc

#endif // BLQ_MSG_H
