// Copyright (C) 2011-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION6_IAADDR_H
#define OPTION6_IAADDR_H

#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

class Option6IAAddr;

/// A pointer to the @c isc::dhcp::Option6IAAddr object.
typedef boost::shared_ptr<Option6IAAddr> Option6IAAddrPtr;

class Option6IAAddr: public Option {

public:
    /// length of the fixed part of the IAADDR option
    static const size_t OPTION6_IAADDR_LEN = 24;

    /// @brief Constructor, used for options constructed (during transmission).
    ///
    /// @throw BadValue if specified addr is not IPv6
    ///
    /// @param type option type
    /// @param addr reference to an address
    /// @param preferred address preferred lifetime (in seconds)
    /// @param valid address valid lifetime (in seconds)
    Option6IAAddr(uint16_t type, const isc::asiolink::IOAddress& addr,
                  uint32_t preferred, uint32_t valid);

    /// @brief Constructor, used for received options.
    ///
    /// @throw OutOfRange if specified option is truncated
    ///
    /// @param type option type
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    Option6IAAddr(uint32_t type, OptionBuffer::const_iterator begin,
                  OptionBuffer::const_iterator end);

    /// @brief Copies this option and returns a pointer to the copy.
    virtual OptionPtr clone() const;

    /// @brief Writes option in wire-format.
    ///
    /// Writes option in wire-format to buf, returns pointer to first unused
    /// byte after stored option.
    ///
    /// @param buf pointer to a buffer
    /// @param check if set to false, allows options larger than 255 for v4
    void pack(isc::util::OutputBuffer& buf, bool check = true) const;

    /// @brief Parses received buffer.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    virtual void unpack(OptionBufferConstIter begin,
                        OptionBufferConstIter end);

    /// Returns string representation of the option.
    ///
    /// @param indent number of spaces before printing text
    ///
    /// @return string with text representation.
    virtual std::string
    toText(int indent = 0) const;


    /// sets address in this option.
    ///
    /// @param addr address to be sent in this option
    void setAddress(const isc::asiolink::IOAddress& addr) { addr_ = addr; }

    /// Sets preferred lifetime (in seconds)
    ///
    /// @param pref address preferred lifetime (in seconds)
    ///
    void setPreferred(unsigned int pref) { preferred_=pref; }

    /// Sets valid lifetime (in seconds).
    ///
    /// @param valid address valid lifetime (in seconds)
    ///
    void setValid(unsigned int valid) { valid_=valid; }

    /// Returns  address contained within this option.
    ///
    /// @return address
    isc::asiolink::IOAddress
    getAddress() const { return addr_; }

    /// Returns preferred lifetime of an address.
    ///
    /// @return preferred lifetime (in seconds)
    unsigned int
    getPreferred() const { return preferred_; }

    /// Returns valid lifetime of an address.
    ///
    /// @return valid lifetime (in seconds)
    unsigned int
    getValid() const { return valid_; }

    /// returns data length (data length + DHCPv4/DHCPv6 option header)
    virtual uint16_t len() const;

protected:
    /// contains an IPv6 address
    isc::asiolink::IOAddress addr_;

    /// contains preferred-lifetime timer (in seconds)
    unsigned int preferred_;

    /// contains valid-lifetime timer (in seconds)
    unsigned int valid_;
};

} // isc::dhcp namespace
} // isc namespace

#endif // OPTION_IA_H
