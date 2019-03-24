// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ND_OPTION_MTU_H
#define ND_OPTION_MTU_H

#include <slaac/nd_option.h>

namespace isc {
namespace slaac {

/// shared pointer to OptionMtu object
class OptionMtu;
typedef boost::shared_ptr<OptionMtu> OptionMtuPtr;

class OptionMtu : public Option {
public:

    /// @brief ctor, used for options constructed, usually during transmission
    OptionMtu();

    /// @brief Constructor, used for received options.
    ///
    /// This constructor takes vector<uint8_t>& which is used in cases
    /// when content of the option will be copied and stored within
    /// option object. V4 Options follow that approach already.
    /// @todo Migrate V6 options to that approach.
    ///
    /// @param data content of the option
    OptionMtu(const OptionBuffer& data);

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
    OptionMtu(OptionBufferConstIter first, OptionBufferConstIter last);

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
    uint8_t getType() const { return (ND_MTU); }

    /// @brief just to force that every option has virtual dtor
    virtual ~OptionMtu();

    /// @brief Returns MTU.
    ///
    /// @return MTU.
    uint32_t getMtu() const { return (mtu_); }

    /// @brief Sets MTU.
    ///
    /// @param mtu MTU to set.
    void setMtu(uint32_t mtu) { mtu_ = mtu; }

protected:

    /// @brief Recommended MTU for the link.
    uint32_t mtu_;
};

} // namespace isc::slaac
} // namespace isc

#endif // ND_OPTION_MTU_H
