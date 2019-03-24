// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ND_OPTION_LLADDR_H
#define ND_OPTION_LLADDR_H

#include <slaac/nd_option.h>

namespace isc {
namespace slaac {

/// shared pointer to OptionLLAddr object
class OptionLLAddr;
typedef boost::shared_ptr<OptionLLAddr> OptionLLAddrPtr;

/// @brief Class for Source/Target Link-layer Address options.
///
///      0                   1                   2                   3
///      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
///     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///     |     Type      |    Length     |    Link-Layer Address ...
///     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
///
class OptionLLAddr : public Option {
public:
    /// @brief ctor, used for options constructed, usually during transmission
    ///
    /// @param type option type (ND_SRC_LL_ADDR (1) or ND_TGT_LL_ADDR (2))
    OptionLLAddr(uint8_t type);

    /// @brief Constructor, used for received options.
    ///
    /// This constructor takes vector<uint8_t>& which is used in cases
    /// when content of the option will be copied and stored within
    /// option object.
    ///
    /// @param type option type (ND_SRC_LL_ADDR (1) or ND_TGT_LL_ADDR (2))
    /// @param data content of the option
    OptionLLAddr(uint8_t type, const OptionBuffer& data);

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
    /// @param type option type (ND_SRC_LL_ADDR (1) or ND_TGT_LL_ADDR (2))
    /// @param first iterator to the first element that should be copied
    /// @param last iterator to the next element after the last one
    ///        to be copied.
    OptionLLAddr(uint8_t type, OptionBufferConstIter first,
                 OptionBufferConstIter last);

    /// @brief Returns string representation of the option.
    ///
    /// @param indent number of spaces before printing text
    ///
    /// @return string with text representation.
    virtual std::string toText(int indent = 0) const;

    /// @brief returns if option is valid (e.g. option may be truncated)
    ///
    /// @return true, if option is valid
    virtual bool valid() const;

    /// @brief just to force that every option has virtual dtor
    virtual ~OptionLLAddr();
};

} // namespace isc::slaac
} // namespace isc


#endif // ND_OPTION_LLADDR_H
