// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

// $Id$

#ifndef __ASIOLINK_H
#define __ASIOLINK_H

#include <string>
#include <sys/socket.h>

/// \brief IO Address Dummy Class
///
/// As part of ther recursor, Evan has written the asiolink.h file, which
/// encapsulates some of the boost::asio classes.  Until these are checked
/// into trunk and merged with this branch, these dummy classes should fulfill
/// their function.

class IOAddress {
public:
    /// \param address_str String representing the address
    IOAddress(const std::string& address_str) : address_(address_str)
    {}

    /// \return Textual representation of the address
    std::string toText() const
    {return address_;}

    /// \return Address family of the address
    virtual short getFamily() const {
        return ((address_.find(".") != std::string::npos) ? AF_INET : AF_INET6);
    }

    /// \return true if two addresses are equal
    bool equal(const IOAddress& address)
    {return (toText() == address.toText());}

private:
    std::string     address_;       ///< Address represented
};

#endif // __ASIOLINK_H
