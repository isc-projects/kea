// Copyright (C) 2010-2013, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <boost/foreach.hpp>

#include <string>
#include <string.h>

using namespace std;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

/// \brief Constructor.
OPT::PseudoRR::PseudoRR(uint16_t code,
                        boost::shared_ptr<std::vector<uint8_t> >& data) :
    code_(code),
    data_(data)
{
}

uint16_t
OPT::PseudoRR::getCode() const {
    return (code_);
}

const uint8_t*
OPT::PseudoRR::getData() const {
    return (&(*data_)[0]);
}

uint16_t
OPT::PseudoRR::getLength() const {
    return (data_->size());
}

struct OPTImpl {
    OPTImpl() :
        rdlength_(0)
    {}

    uint16_t rdlength_;
    std::vector<OPT::PseudoRR> pseudo_rrs_;
};

/// \brief Default constructor.
OPT::OPT() :
    impl_(new OPTImpl)
{
}

/// \brief Constructor from string.
///
/// This constructor cannot be used, and always throws an exception.
///
/// \throw InvalidRdataText OPT RR cannot be constructed from text.
OPT::OPT(const std::string&) :
    impl_(NULL)
{
    isc_throw(InvalidRdataText, "OPT RR cannot be constructed from text");
}

/// \brief Constructor with a context of MasterLexer.
///
/// This constructor cannot be used, and always throws an exception.
///
/// \throw InvalidRdataText OPT RR cannot be constructed from text.
OPT::OPT(MasterLexer&, const Name*,
         MasterLoader::Options, MasterLoaderCallbacks&) :
    impl_(NULL)
{
    isc_throw(InvalidRdataText, "OPT RR cannot be constructed from text");
}

OPT::OPT(InputBuffer& buffer, size_t rdata_len) :
    impl_(NULL)
{
    std::auto_ptr<OPTImpl> impl_ptr(new OPTImpl);

    while (true) {
        if (rdata_len == 0) {
            break;
        }

        if (rdata_len < 4) {
            isc_throw(InvalidRdataLength,
                      "Pseudo OPT RR record too short: "
                      << rdata_len << " bytes");
        }

        const uint16_t option_code = buffer.readUint16();
        const uint16_t option_length = buffer.readUint16();
        rdata_len -= 4;

        if (static_cast<uint16_t>(impl_ptr->rdlength_ + option_length) <
            impl_ptr->rdlength_)
        {
            isc_throw(InvalidRdataText,
                      "Option length " << option_length
                      << " would overflow OPT RR RDLEN (currently "
                      << impl_ptr->rdlength_ << ").");
        }

        if (rdata_len < option_length) {
            isc_throw(InvalidRdataLength, "Corrupt pseudo OPT RR record");
        }

        boost::shared_ptr<std::vector<uint8_t> >
            option_data(new std::vector<uint8_t>(option_length));
        buffer.readData(&(*option_data)[0], option_length);
        impl_ptr->pseudo_rrs_.push_back(PseudoRR(option_code, option_data));
        impl_ptr->rdlength_ += option_length;
        rdata_len -= option_length;
    }

    impl_ = impl_ptr.release();
}

OPT::OPT(const OPT& other) :
    Rdata(), impl_(new OPTImpl(*other.impl_))
{
}

OPT&
OPT::operator=(const OPT& source) {
    if (this == &source) {
        return (*this);
    }

    OPTImpl* newimpl = new OPTImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

OPT::~OPT() {
    delete impl_;
}

std::string
OPT::toText() const {
    isc_throw(isc::InvalidOperation,
              "OPT RRs do not have a presentation format");
}

void
OPT::toWire(OutputBuffer& buffer) const {
    BOOST_FOREACH(const PseudoRR& pseudo_rr, impl_->pseudo_rrs_) {
        buffer.writeUint16(pseudo_rr.getCode());
        const uint16_t length = pseudo_rr.getLength();
        buffer.writeUint16(length);
        if (length > 0) {
            buffer.writeData(pseudo_rr.getData(), length);
        }
    }
}

void
OPT::toWire(AbstractMessageRenderer& renderer) const {
    BOOST_FOREACH(const PseudoRR& pseudo_rr, impl_->pseudo_rrs_) {
        renderer.writeUint16(pseudo_rr.getCode());
        const uint16_t length = pseudo_rr.getLength();
        renderer.writeUint16(length);
        if (length > 0) {
            renderer.writeData(pseudo_rr.getData(), length);
        }
    }
}

int
OPT::compare(const Rdata&) const {
    isc_throw(isc::InvalidOperation,
              "It is meaningless to compare a set of OPT pseudo RRs; "
              "they have unspecified order");
    return (0);
}

void
OPT::appendPseudoRR(uint16_t code, const uint8_t* data, uint16_t length) {
    // See if it overflows 16-bit length field. We only worry about the
    // pseudo-RR length here, not the whole message length (which should
    // be checked and enforced elsewhere).
    if (static_cast<uint16_t>(impl_->rdlength_ + length) <
        impl_->rdlength_)
    {
        isc_throw(isc::InvalidParameter,
                  "Option length " << length
                  << " would overflow OPT RR RDLEN (currently "
                  << impl_->rdlength_ << ").");
    }

    boost::shared_ptr<std::vector<uint8_t> >
        option_data(new std::vector<uint8_t>(length));
    if (length != 0) {
        std::memcpy(&(*option_data)[0], data, length);
    }
    impl_->pseudo_rrs_.push_back(PseudoRR(code, option_data));
    impl_->rdlength_ += length;
}

const std::vector<OPT::PseudoRR>&
OPT::getPseudoRRs() const {
    return (impl_->pseudo_rrs_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
