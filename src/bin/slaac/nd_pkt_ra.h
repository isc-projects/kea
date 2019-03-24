// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ND_PKT_RA_H
#define ND_PKT_RA_H

#include <nd_pkt.h>

namespace isc {

namespace slaac {

/// @brief Class for classes representing Router Advertisement messages.
///
///      0                   1                   2                   3
///      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
///     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///     |     Type      |     Code      |          Checksum             |
///     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///     | Cur Hop Limit |M|O|  Reserved |       Router Lifetime         |
///     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///     |                         Reachable Time                        |
///     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///     |                          Retrans Timer                        |
///     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///     |   Options ...
///     +-+-+-+-+-+-+-+-+-+-+-+-
///
class RAPkt : public NDPkt {
public:

    /// @brief Minimal RA length.
    static const size_t RA_MIN_LEN = 16;

    /// @brief Constructor.
    ///
    /// This constructor is typically used for transmitted messages as it
    /// creates an empty (no options) packet.
    ///
    /// @param local_addr local IPv6 address
    /// @param remote_addr remote IPv6 address
    RAPkt(const isc::asiolink::IOAddress& local_addr,
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
    RAPkt(const uint8_t* buf, uint32_t len,
          const isc::asiolink::IOAddress& local_addr,
          const isc::asiolink::IOAddress& remote_addr);

    /// @brief Prepares on-wire format of RA packet.
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

    /// @brief Parses on-wire form of RA packet.
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
    virtual const char* getName() const { return ("RA"); };

    /// @brief Virtual destructor.
    ///
    /// There is nothing to clean up here, but since there are virtual methods,
    /// we define virtual destructor to ensure that derived classes will have
    /// a virtual one, too.
    virtual ~RAPkt() {
    }

    /// @brief Returns hop limit.
    ///
    /// @return hop limit (zero means unspecified by this router).
    uint8_t getHopLimit() const { return (hop_limit_); };

    /// @brief Sets hop limit.
    ///
    /// @param hop_limit hop limit to be set.
    void setHopLimit(uint8_t hop_limit) { hop_limit_ = hop_limit; };

    /// @brief Returns managed flag.
    ///
    /// @return managed flag (addresses are available via DHCP).
    bool getManagedFlag() const { return (managed_flag_); };

    /// @brief Sets managed flag.
    ///
    /// @param managed_flag managed flag to be set.
    void setManagedFlag(bool managed_flag) { managed_flag_ = managed_flag; };

    /// @brief Returns other flag.
    ///
    /// @return other flag (other configuration is available via DHCP).
    bool getOtherFlag() const { return (other_flag_); };

    /// @brief Sets other flag.
    ///
    /// @param other_flag other flag to be set.
    void setOtherFlag(bool other_flag) { other_flag_ = other_flag; };

    /// @note: RFC 5175 defines some new flags...

    /// @brief Returns router lifetime.
    ///
    /// @return router lifetime (zero means the router is not a default router).
    uint16_t getRouterLifetime() const { return (router_lifetime_); };

    /// @brief Sets router lifetime.
    ///
    /// @param router_lifetime router lifetime to be set.
    void setRouterLifetime(uint16_t router_lifetime) {
        router_lifetime_ = router_lifetime;
    };

    /// @brief Returns reachable time.
    ///
    /// @return reachable time (zero means unspecified by this router).
    uint32_t getReachableTime() const { return (reachable_time_); };

    /// @brief Sets reachable time.
    ///
    /// @param reachable_time reachable time to be set.
    void setReachableTime(uint32_t reachable_time) {
        reachable_time_ = reachable_time;
    };

    /// @brief Returns retrans timer.
    ///
    /// @return retrans timer (zero means unspecified by this router).
    uint32_t getRetransTimer() const { return (retrans_timer_); };

    /// @brief Sets retrans timer.
    ///
    /// @param retrans_timer retrans timer to be set.
    void setRetransTimer(uint32_t retrans_timer) {
        retrans_timer_ = retrans_timer;
    };

protected:
    // @brief Current Hop Limit (zero means unspecified by this router).
    uint8_t hop_limit_;

    // @brief Managed Flag (addresses are available via DHCP).
    bool managed_flag_;

    // @brief Managed Flag bit.
    static const uint8_t MANAGED_FLAG = 0x80;

    // @brief Other Flag (other configuration is available via DHCP).
    bool other_flag_;

    // @brief Other Flag bit.
    static const uint8_t OTHER_FLAG = 0x40;

    // @brief Router Lifetime (zero means the router is not a default router).
    uint16_t router_lifetime_;

    // @brief Reachable Time (zero means unspecified by this router).
    uint32_t reachable_time_;

    // @brief Retrans Timer (zero means unspecified by this router).
    uint32_t retrans_timer_;
};

/// @brief A pointer to either RA packet
typedef boost::shared_ptr<isc::slaac::RAPkt> RAPktPtr;

}; // namespace isc::slaac
}; // namespace isc

#endif
