// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <util/buffer.h>

#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

struct SRVImpl {
    // straightforward representation of SRV RDATA fields
    SRVImpl(uint16_t priority, uint16_t weight, uint16_t port,
           const Name& target) :
        priority_(priority), weight_(weight), port_(port),
        target_(target)
    {}

    uint16_t priority_;
    uint16_t weight_;
    uint16_t port_;
    Name target_;
};

SRV::SRV(const string& srv_str) :
    impl_(NULL)
{
    istringstream iss(srv_str);
    string targetname;
    unsigned int priority, weight, port;

    iss >> priority >> weight >> port >> targetname;
    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid SRV text");
    }
    if (priority > 0xffff) {
        isc_throw(InvalidRdataText, "SRV priority out of range");
    }
    if (weight > 0xffff) {
        isc_throw(InvalidRdataText, "SRV weight out of range");
    }
    if (port > 0xffff) {
        isc_throw(InvalidRdataText, "SRV port out of range");
    }

    impl_ = new SRVImpl(priority, weight, port, Name(targetname));
}

SRV::SRV(InputBuffer& buffer, size_t rdata_len) {
    if (rdata_len < 6) {
        isc_throw(InvalidRdataLength, "SRV too short");
    }

    uint16_t priority = buffer.readUint16();
    uint16_t weight = buffer.readUint16();
    uint16_t port = buffer.readUint16();
    const Name targetname(buffer);

    impl_ = new SRVImpl(priority, weight, port, targetname);
}

SRV::SRV(const SRV& source) :
    Rdata(), impl_(new SRVImpl(*source.impl_))
{}

SRV&
SRV::operator=(const SRV& source) {
    if (impl_ == source.impl_) {
        return (*this);
    }

    SRVImpl* newimpl = new SRVImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

SRV::~SRV() {
    delete impl_;
}

string
SRV::toText() const {
    using namespace boost;
    return (lexical_cast<string>(static_cast<int>(impl_->priority_)) +
        " " + lexical_cast<string>(static_cast<int>(impl_->weight_)) +
        " " + lexical_cast<string>(static_cast<int>(impl_->port_)) +
        " " + impl_->target_.toText());
}

void
SRV::toWire(OutputBuffer& buffer) const {
    buffer.writeUint16(impl_->priority_);
    buffer.writeUint16(impl_->weight_);
    buffer.writeUint16(impl_->port_);
    impl_->target_.toWire(buffer);
}

void
SRV::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeUint16(impl_->priority_);
    renderer.writeUint16(impl_->weight_);
    renderer.writeUint16(impl_->port_);
    // According to RFC 2782, name compression is not
    // to be used for this field.
    renderer.writeName(impl_->target_, false);
}

int
SRV::compare(const Rdata& other) const {
    const SRV& other_srv = dynamic_cast<const SRV&>(other);

    if (impl_->priority_ != other_srv.impl_->priority_) {
        return (impl_->priority_ < other_srv.impl_->priority_ ? -1 : 1);
    }
    if (impl_->weight_ != other_srv.impl_->weight_) {
        return (impl_->weight_ < other_srv.impl_->weight_ ? -1 : 1);
    }
    if (impl_->port_ != other_srv.impl_->port_) {
        return (impl_->port_ < other_srv.impl_->port_ ? -1 : 1);
    }

    return (compareNames(impl_->target_, other_srv.impl_->target_));
}

uint16_t
SRV::getPriority() const {
    return (impl_->priority_);
}

uint16_t
SRV::getWeight() const {
    return (impl_->weight_);
}

uint16_t
SRV::getPort() const {
    return (impl_->port_);
}

const Name&
SRV::getTarget() const {
    return (impl_->target_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
