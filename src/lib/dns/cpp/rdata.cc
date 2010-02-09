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
#include <sstream>
#include <iomanip>
#include <ios>
#include <vector>

#include <stdint.h>
#include <string.h>

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

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
struct GenericImpl {
    GenericImpl(const vector<uint8_t>& data) : data_(data) {}
    vector<uint8_t> data_;
};

Generic::Generic(InputBuffer& buffer, size_t rdata_len)
{
    vector<uint8_t> data(rdata_len);
    buffer.readData(&data[0], rdata_len);
    data.resize(rdata_len);

    impl_ = new GenericImpl(data);
}

Generic::Generic(const string& rdata_string)
{
    istringstream iss(rdata_string);
    string unknown_mark;
    iss >> unknown_mark;
    if (unknown_mark != "\\#") {
        dns_throw(InvalidRdataText,
                  "Missing the special token (\\#) for generic RDATA encoding");
    }

    // RDLENGTH: read into a string so that we can easily reject invalid tokens
    string rdlen_txt;
    iss >> rdlen_txt;
    istringstream iss_rdlen(rdlen_txt);
    int32_t rdlen;
    iss_rdlen >> rdlen;
    if (iss_rdlen.rdstate() != ios::eofbit) {
        dns_throw(InvalidRdataText,
                  "Invalid representation for a generic RDLENGTH");
    }
    if (rdlen < 0 || rdlen > 0xffff) {
        dns_throw(InvalidRdataLength, "RDATA length is out of range");
    }

    vector<uint8_t> data;
    while (!iss.eof() && data.size() < rdlen) {
        string bytes;
        iss >> bytes;
        // Hexadecimal encoding of RDATA: each segment must consist of an even
        // number of hex digits.
        if ((iss.rdstate() & (ios::badbit | ios::failbit)) != 0 ||
            (bytes.size() % 2) != 0) {
            dns_throw(InvalidRdataText,
                      "Invalid hex encoding of generic RDATA");
        }

        for (int pos = 0; pos < bytes.size(); pos += 2) {
            istringstream iss_hex(bytes.substr(pos, 2));

            unsigned int ch;
            iss_hex >> hex >> ch;
            if (iss_hex.rdstate() != ios::eofbit) {
                dns_throw(InvalidRdataText,
                          "Invalid hex encoding of generic RDATA");
            }
            data.push_back(ch);
        }
    }

    if (data.size() != rdlen) {
        dns_throw(InvalidRdataLength,
                  "Generic RDATA code doesn't match RDLENGTH");
    }

    impl_ = new GenericImpl(data);
}

Generic::Generic(const Generic& source) :
    impl_(new GenericImpl(*source.impl_))
{}

Generic&
Generic::operator=(const Generic& source)
{
    if (impl_ == source.impl_) {
        return (*this);
    }

    GenericImpl* newimpl = new GenericImpl(*impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

namespace {
class UnknownRdataDumper {
public:
    UnknownRdataDumper(ostringstream& oss) : oss_(&oss) {}
    void operator()(const unsigned char d)
    {
        *oss_ << setw(2) << static_cast<unsigned int>(d);
    }
private:
    ostringstream* oss_;
};
}

string
Generic::toText() const
{
    ostringstream oss;

    oss << "\\# " << impl_->data_.size() << " ";
    oss.fill('0');
    oss << right << hex;
    for_each(impl_->data_.begin(), impl_->data_.end(), UnknownRdataDumper(oss));

    return (oss.str());
}

void
Generic::toWire(OutputBuffer& buffer) const
{
    buffer.writeData(&impl_->data_[0], impl_->data_.size());
}

void
Generic::toWire(MessageRenderer& renderer) const
{
    renderer.writeData(&impl_->data_[0], impl_->data_.size());
}

int
Generic::compare(const Rdata& other) const
{
    const Generic& other_rdata = dynamic_cast<const Generic&>(other);

    size_t this_len = impl_->data_.size();
    size_t other_len = other_rdata.impl_->data_.size();
    size_t len = (this_len < other_len) ? this_len : other_len;
    int cmp;

    if ((cmp = memcmp(&impl_->data_[0], &other_rdata.impl_->data_[0], len))
        != 0) {
        return (cmp);
    } else {
        return ((this_len == other_len) ? 0 :
                (this_len < other_len) ? -1 : 1);
    }
}

} // end of namespace generic

} // end of namespace rdata
}
}
