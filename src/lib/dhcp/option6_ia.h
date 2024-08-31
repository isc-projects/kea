// Copyright (C) 2011-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_IA_H
#define OPTION_IA_H

#include <dhcp/option.h>
#include <boost/shared_ptr.hpp>
#include <stdint.h>

namespace isc {
namespace dhcp {

class Option6IA;

/// A pointer to the @c Option6IA object.
typedef boost::shared_ptr<Option6IA> Option6IAPtr;

class Option6IA: public Option {

public:
    /// Length of IA_NA and IA_PD content
    const static size_t OPTION6_IA_LEN = 12;

    /// @brief Ctor, used for constructed options, usually during transmission.
    ///
    /// @param type option type (usually 4 for IA_NA, 25 for IA_PD)
    /// @param iaid identity association identifier (id of IA)
    Option6IA(uint16_t type, uint32_t iaid);

    /// @brief Ctor, used for received options.
    ///
    /// @param type option type (usually 4 for IA_NA, 25 for IA_PD)
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    Option6IA(uint16_t type, OptionBuffer::const_iterator begin,
              OptionBuffer::const_iterator end);

    /// @brief Copies this option and returns a pointer to the copy.
    virtual OptionPtr clone() const;

    /// Writes option in wire-format to buf, returns pointer to first unused
    /// byte after stored option.
    ///
    /// @param buf buffer (option will be stored here)
    /// @param check if set to false, allows options larger than 255 for v4
    void pack(isc::util::OutputBuffer& buf, bool check = true) const;

    /// @brief Parses received buffer
    ///
    /// Parses received buffer and returns offset to the first unused byte after
    /// parsed option.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);

    /// Provides human readable text representation
    ///
    /// @param indent number of leading space characters
    ///
    /// @return string with text representation
    virtual std::string toText(int indent = 0) const;

    /// Sets T1 timer.
    ///
    /// @param t1 t1 value to be set
    void setT1(uint32_t t1) { t1_ = t1; }

    /// Sets T2 timer.
    ///
    /// @param t2 t2 value to be set
    void setT2(uint32_t t2) { t2_ = t2; }

    /// Sets Identity Association Identifier.
    ///
    /// @param iaid IAID value to be set
    void setIAID(uint32_t iaid) { iaid_ = iaid; }

    /// Returns IA identifier.
    ///
    /// @return IAID value.
    ///
    uint32_t getIAID() const { return iaid_; }

    /// Returns T1 timer.
    ///
    /// @return T1 value.
    uint32_t getT1() const { return t1_; }

    /// Returns T2 timer.
    ///
    /// @return T2 value.
    uint32_t getT2() const { return t2_; }

    /// @brief returns complete length of option
    ///
    /// Returns length of this option, including option header and suboptions
    ///
    /// @return length of this option
    virtual uint16_t len() const;

protected:

    /// keeps IA identifier
    uint32_t iaid_;

    /// keeps T1 timer value
    uint32_t t1_;

    /// keeps T2 timer value
    uint32_t t2_;
};

} // isc::dhcp namespace
} // isc namespace

#endif // OPTION_IA_H
