// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_DNR_H
#define OPTION_DNR_H

#include <dhcp/option.h>

namespace isc {
namespace dhcp {

class OptionDNR6 : public Option {
    OptionDNR6(const uint16_t type);

    OptionDNR6(const uint16_t type, OptionBufferConstIter begin, OptionBufferConstIter end);

public:
    virtual OptionPtr clone() const;
    virtual void pack(util::OutputBuffer& buf, bool check) const;
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);
    virtual std::string toText(int indent) const;
    virtual uint16_t len() const;
};

class OptionDNR4 : public Option {
    OptionDNR4(const uint16_t type);

    OptionDNR4(const uint16_t type, OptionBufferConstIter begin, OptionBufferConstIter end);

public:
    virtual OptionPtr clone() const;
    virtual void pack(util::OutputBuffer& buf, bool check) const;
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);
    virtual std::string toText(int indent) const;
    virtual uint16_t len() const;
};

}  // namespace dhcp
}  // namespace isc

#endif  // OPTION_DNR_H
