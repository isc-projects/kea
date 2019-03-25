// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ND_OPTION_PREF_INFO_H
#define ND_OPTION_PREF_INFO_H

#include <asiolink/io_address.h>
#include <slaac/nd_option.h>

namespace isc {
namespace slaac {

/// shared pointer to OptionPrefInfo object
class OptionPrefInfo;
typedef boost::shared_ptr<OptionPrefInfo> OptionPrefInfoPtr;

/// @brief Class for Prefix Information option.
///
///       0                   1                   2                   3
///       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
///      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///      |     Type      |    Length     | Prefix Length |L|A| Reserved1 |
///      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///      |                         Valid Lifetime                        |
///      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///      |                       Preferred Lifetime                      |
///      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///      |                           Reserved2                           |
///      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///      |                                                               |
///      +                                                               +
///      |                                                               |
///      +                            Prefix                             +
///      |                                                               |
///      +                                                               +
///      |                                                               |
///      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///
class OptionPrefInfo : public Option {
public:

    /// @brief Length of the Prefix Info option content.
    const static size_t PREFIX_INFO_LEN = 30;

    /// @brief ctor, used for options constructed, usually during transmission
    OptionPrefInfo();

    /// @brief Constructor, used for received options.
    ///
    /// This constructor takes vector<uint8_t>& which is used in cases
    /// when content of the option will be copied and stored within
    /// option object. V4 Options follow that approach already.
    /// @todo Migrate V6 options to that approach.
    ///
    /// @param data content of the option
    OptionPrefInfo(const OptionBuffer& data);

    /// @brief Constructor, used for received options.
    ///
    /// This constructor is similar to the previous one, but it does not take
    /// the whole vector<uint8_t>, but rather subset of it.
    ///
    /// @todo This can be templated to use different containers, not just
    /// vector. Prototype should look like this:
    /// template<typename InputIterator> Option(uint8_t type,
    /// InputIterator first, InputIterator last);
    ///
    /// vector<int8_t> myData;
    /// Example usage: new Option(123, myData.begin()+1, myData.end()-1)
    /// This will create ND option of type 123 that contains data from
    /// trimmed (first and last byte removed) myData vector.
    ///
    /// @param first iterator to the first element that should be copied
    /// @param last iterator to the next element after the last one
    ///        to be copied.
    OptionPrefInfo(OptionBufferConstIter first, OptionBufferConstIter last);

    /// @brief Writes option in wire-format to a buffer.
    ///
    /// Writes option in wire-format to buffer, returns pointer to first unused
    /// byte after stored option (that is useful for writing options one after
    /// another).
    ///
    /// @param buf pointer to a buffer
    virtual void pack(isc::util::OutputBuffer& buf) const;

    /// @brief Parses received buffer.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    virtual void unpack(OptionBufferConstIter begin,
                        OptionBufferConstIter end);

    /// @brief Returns string representation of the option.
    ///
    /// @param indent number of spaces before printing text
    ///
    /// @return string with text representation.
    virtual std::string toText(int indent = 0) const;

    /// @brief Returns option type
    ///
    /// @return option type
    uint8_t getType() const { return (ND_PREFIX_INFO); }

    /// @brief Returns length of the complete option
    ///
    /// @return length of the option
    virtual size_t len() const {
        return (OPTION_HDR_LEN + PREFIX_INFO_LEN);
    }

    /// @brief just to force that every option has virtual dtor
    virtual ~OptionPrefInfo();

    /// @brief Returns prefix length.
    ///
    /// @return prefix length (range from 0 to 128).
    uint8_t getPrefixLength() const { return (prefix_length_); }

    /// @brief Sets prefix length.
    ///
    /// @param prefix_length Prefix length to set.
    /// @throw OutOfRange for values greater than 128.
    void setPrefixLength(uint8_t prefix_length) {
        prefix_length_ = prefix_length;
    }

    /// @brief Returns on-link (L) flag.
    ///
    /// @return on-link flag (prefix can be used for on-link determination).
    bool getOnLinkFlag() const { return (on_link_flag_); }

    /// @brief Sets on-link (L) flag.
    ///
    /// @param on-link_flag On-Link flag to set.
    void setOnLinkFlag(bool on_link_flag) {
        on_link_flag_ = on_link_flag;
    }

    /// @brief On-link (L) flag bit.
    static const uint8_t ON_LINK_FLAG = 0x80;

    /// @brief Returns addr-config (A) flag.
    ///
    /// @return addr-config flag (prefix can be used for address configuration).
    bool getAddrConfigFlag() const { return (addr_config_flag_); }

    /// @brief Sets addr-config (A) flag.
    ///
    /// @param addr-config_flag Addr-Config flag to set.
    void setAddrConfigFlag(bool addr_config_flag) {
        addr_config_flag_ = addr_config_flag;
    }

    /// @brief Addr-config (A) flag bit.
    static const uint8_t ADDR_CONFIG_FLAG = 0x40;

    /// @brief Returns valid lifetime.
    ///
    /// @return valid lifetime (all one bits (0xffffffff) is infinity).
    uint32_t getValidLifetime() const { return (valid_lifetime_); }

    /// @brief Sets valid lifetime.
    ///
    /// @param valid_lifetime Valid lifetime to set.
    void setValidLifetime(uint32_t valid_lifetime) {
        valid_lifetime_ = valid_lifetime;
    }

    /// @brief Returns preferred lifetime.
    ///
    /// @return preferred lifetime (all one bits (0xffffffff) is infinity).
    uint32_t getPreferredLifetime() const { return (preferred_lifetime_); }

    /// @brief Sets preferred lifetime.
    ///
    /// @param preferred_lifetime Preferred lifetime to set.
    void setPreferredLifetime(uint32_t preferred_lifetime) {
        preferred_lifetime_ = preferred_lifetime;
    }

    /// @brief Returns Prefix.
    ///
    /// @return Prefix (bits after prefix length are reserved).
    const isc::asiolink::IOAddress& getPrefix() const { return (prefix_); }

    /// @brief Sets Prefix.
    ///
    /// @param prefix Prefix to set.
    /// @throw BadValue (a reserved bit after prefix length is not zero).
    void setPrefix(const isc::asiolink::IOAddress& prefix) {
        checkPrefix(prefix);
        prefix_ = prefix;
    }

protected:

    /// @brief Parses option buffer.
    virtual void unpack();

    /// @brief Checks that no reserved bit after prefix length is set to 1.
    ///
    /// @throw BadValue if the prefix is incorrect.
    void checkPrefix(const isc::asiolink::IOAddress& prefix);

    /// @brief Prefix length (range from 0 to 128).
    uint8_t prefix_length_;

    /// @brief On-link (L) flag (prefix can be used for on-link determination).
    bool on_link_flag_;

    /// @brief Addr-config (A) flag (prefix can be used for address
    ///        configuration).
    bool addr_config_flag_;

    /// @brief Valid lifetime (all one bits (0xffffffff) is infinity).
    uint32_t valid_lifetime_;

    /// @brief Preferred lifetime (all one bits (0xffffffff) is infinity).
    uint32_t preferred_lifetime_;

    /// @brief Prefix (bits after prefix length are reserved).
    isc::asiolink::IOAddress prefix_;
};

} // namespace isc::slaac
} // namespace isc

#endif // ND_OPTION_PREF_INFO_H
