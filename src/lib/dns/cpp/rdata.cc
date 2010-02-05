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

#include <cctype>
#include <string>

#include <stdint.h>
#include <string.h>

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

#include <arpa/inet.h> // XXX: for inet_pton/ntop(), not exist in C++ standards

#include "buffer.h"
#include "name.h"
#include "messagerenderer.h"
#include "rdata.h"
#include "rrparamregistry.h"
#include "rrtype.h"

using namespace std;
using namespace boost;

namespace isc {
namespace dns {
namespace rdata {

// XXX: we need to specify std:: for string to help doxygen match the
// function signature with that given in the header file.
RdataPtr
createRdata(const RRType& rrtype, const RRClass& rrclass,
            const std::string& rdata_string)
{
    return (RRParamRegistry::getRegistry().createRdata(rrtype, rrclass,
                                                       rdata_string));
}

RdataPtr
createRdata(const RRType& rrtype, const RRClass& rrclass,
            InputBuffer& buffer, size_t len)
{
    size_t old_pos = buffer.getPosition();

    RdataPtr rdata =
        RRParamRegistry::getRegistry().createRdata(rrtype, rrclass, buffer,
                                                   len);
                                                   
    if (buffer.getPosition() - old_pos != len) {
        dns_throw(InvalidRdataLength, "RDLENGTH mismatch");
    }

    return (rdata);
}

RdataPtr
createRdata(const RRType& rrtype, const RRClass& rrclass, const Rdata& source)
{
    return (RRParamRegistry::getRegistry().createRdata(rrtype, rrclass,
                                                       source));
}

int
compareNames(const Name& n1, const Name& n2)
{
    size_t len1 = n1.getLength();
    size_t len2 = n2.getLength();
    size_t cmplen = (len1 < len2) ? len1 : len2;

    for (size_t i = 0; i < cmplen; ++i) {
        uint8_t c1 = tolower(n1.at(i));
        uint8_t c2 = tolower(n2.at(i));
        if (c1 < c2) {
            return (-1);
        } else if (c2 > c1) {
            return (1);
        }
    }

    return ((len1 == len2) ? 0 : (len1 < len2) ? -1 : 1);
}

namespace generic {
Generic::Generic(InputBuffer& buffer, size_t rdata_len) :
    data_(rdata_len)
{
    buffer.readData(&data_[0], rdata_len);
    data_.resize(rdata_len);
}

Generic::Generic(const string& rdata_string)
{
    // parse the \# n xx xx... format (TBD)
}

string
Generic::toText() const
{
    // return rdata in the \# n xx xx format (TBD)
    dns_throw(InvalidRdataText, "Not implemented yet");
}

void
Generic::toWire(OutputBuffer& buffer) const
{
    buffer.writeData(&data_[0], data_.size());
}

void
Generic::toWire(MessageRenderer& renderer) const
{
    renderer.writeData(&data_[0], data_.size());
}

int
Generic::compare(const Rdata& other) const
{
    const Generic& other_rdata = dynamic_cast<const Generic&>(other);

    size_t this_len = data_.size();
    size_t other_len = other_rdata.data_.size();
    size_t len = (this_len < other_len) ? this_len : other_len;
    int cmp;

    if ((cmp = memcmp(&data_[0], &other_rdata.data_[0], len)) != 0) {
        return (cmp);
    } else {
        return ((this_len == other_len) ? 0 :
                (this_len < other_len) ? -1 : 1);
    }
}

} // end of namespace generic

namespace in {
} // end of namespace in

namespace ch {
} // end of namespace ch
} // end of namespace rdata
}
}
