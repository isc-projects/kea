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

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <dns/util/base64.h>
#include <dns/buffer.h>
#include <dns/dnssectime.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <stdio.h>
#include <time.h>

using namespace std;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

namespace {
// This is the minimum necessary length of all wire-format RRSIG RDATA:
// - two 8-bit fields (algorithm and labels)
// - two 16-bit fields (covered and tag)
// - three 32-bit fields (original TTL, expire and inception)
const size_t RRSIG_MINIMUM_LEN = 2 * sizeof(uint8_t) + 2 * sizeof(uint16_t) +
    3 * sizeof(uint32_t);
}

struct RRSIGImpl {
    // straightforward representation of RRSIG RDATA fields
    RRSIGImpl(const RRType& covered, uint8_t algorithm, uint8_t labels,
              uint32_t originalttl, uint32_t timeexpire, uint32_t timeinception,
              uint16_t tag, const Name& signer,
              const vector<uint8_t>& signature) :
        covered_(covered), algorithm_(algorithm), labels_(labels),
        originalttl_(originalttl), timeexpire_(timeexpire),
        timeinception_(timeinception), tag_(tag), signer_(signer),
        signature_(signature)
    {}

    const RRType covered_;
    uint8_t algorithm_;
    uint8_t labels_;
    uint32_t originalttl_;
    uint32_t timeexpire_;
    uint32_t timeinception_;
    uint16_t tag_;
    const Name signer_;
    const vector<uint8_t> signature_;
};

RRSIG::RRSIG(const string& rrsig_str) :
    impl_(NULL)
{
    istringstream iss(rrsig_str);
    string covered_txt, signer_txt, expire_txt, inception_txt;
    unsigned int algorithm, labels;
    uint32_t originalttl;
    uint16_t tag;
    stringbuf signaturebuf;

    iss >> covered_txt >> algorithm >> labels >> originalttl
        >> expire_txt >> inception_txt >> tag >> signer_txt
        >> &signaturebuf;
    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid RRSIG text");
    }
    if (algorithm > 0xff) {
        isc_throw(InvalidRdataText, "RRSIG algorithm out of range");
    }
    if (labels > 0xff) {
        isc_throw(InvalidRdataText, "RRSIG labels out of range");
    }

    uint32_t timeexpire = timeFromText(expire_txt);
    uint32_t timeinception = timeFromText(inception_txt);

    vector<uint8_t> signature;
    decodeBase64(signaturebuf.str(), signature);

    impl_ = new RRSIGImpl(RRType(covered_txt), algorithm, labels,
                          originalttl, timeexpire, timeinception, tag,
                          Name(signer_txt), signature);
}

RRSIG::RRSIG(InputBuffer& buffer, size_t rdata_len)
{
    size_t pos = buffer.getPosition();

    if (rdata_len < RRSIG_MINIMUM_LEN) {
        isc_throw(InvalidRdataLength, "RRSIG too short");
    }

    RRType covered(buffer);
    uint8_t algorithm = buffer.readUint8();
    uint8_t labels = buffer.readUint8();
    uint32_t originalttl = buffer.readUint32();
    uint32_t timeexpire = buffer.readUint32();
    uint32_t timeinception = buffer.readUint32();
    uint16_t tag = buffer.readUint16();
    Name signer(buffer);

    // rdata_len must be sufficiently large to hold non empty signature data.
    if (rdata_len <= buffer.getPosition() - pos) {
        isc_throw(InvalidRdataLength, "RRSIG too short");
    }
    rdata_len -= (buffer.getPosition() - pos);

    vector<uint8_t> signature(rdata_len);
    buffer.readData(&signature[0], rdata_len);

    impl_ = new RRSIGImpl(covered, algorithm, labels,
                          originalttl, timeexpire, timeinception, tag,
                          signer, signature);
}

RRSIG::RRSIG(const RRSIG& source) :
    Rdata(), impl_(new RRSIGImpl(*source.impl_))
{}

RRSIG&
RRSIG::operator=(const RRSIG& source)
{
    if (impl_ == source.impl_) {
        return (*this);
    }

    RRSIGImpl* newimpl = new RRSIGImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

RRSIG::~RRSIG()
{
    delete impl_;
}

string
RRSIG::toText() const
{
    string expire = timeToText(impl_->timeexpire_);
    string inception = timeToText(impl_->timeinception_);

    return (impl_->covered_.toText() +
            " " + boost::lexical_cast<string>(static_cast<int>(impl_->algorithm_))
            + " " + boost::lexical_cast<string>(static_cast<int>(impl_->labels_))
            + " " + boost::lexical_cast<string>(impl_->originalttl_)
            + " " + expire
            + " " + inception
            + " " + boost::lexical_cast<string>(impl_->tag_)
            + " " + impl_->signer_.toText()
            + " " + encodeBase64(impl_->signature_));
}

void
RRSIG::toWire(OutputBuffer& buffer) const
{
    impl_->covered_.toWire(buffer);
    buffer.writeUint8(impl_->algorithm_);
    buffer.writeUint8(impl_->labels_);
    buffer.writeUint32(impl_->originalttl_);
    buffer.writeUint32(impl_->timeexpire_);
    buffer.writeUint32(impl_->timeinception_);
    buffer.writeUint16(impl_->tag_);
    impl_->signer_.toWire(buffer);
    buffer.writeData(&impl_->signature_[0], impl_->signature_.size());
}

void
RRSIG::toWire(MessageRenderer& renderer) const
{
    impl_->covered_.toWire(renderer);
    renderer.writeUint8(impl_->algorithm_);
    renderer.writeUint8(impl_->labels_);
    renderer.writeUint32(impl_->originalttl_);
    renderer.writeUint32(impl_->timeexpire_);
    renderer.writeUint32(impl_->timeinception_);
    renderer.writeUint16(impl_->tag_);
    renderer.writeName(impl_->signer_, false);
    renderer.writeData(&impl_->signature_[0], impl_->signature_.size());
}

int
RRSIG::compare(const Rdata& other) const
{
    const RRSIG& other_rrsig = dynamic_cast<const RRSIG&>(other);

    if (impl_->covered_.getCode() != other_rrsig.impl_->covered_.getCode()) {
        return (impl_->covered_.getCode() <
                other_rrsig.impl_->covered_.getCode() ? -1 : 1);
    }
    if (impl_->algorithm_ != other_rrsig.impl_->algorithm_) {
        return (impl_->algorithm_ < other_rrsig.impl_->algorithm_ ? -1 : 1);
    }
    if (impl_->labels_ != other_rrsig.impl_->labels_) {
        return (impl_->labels_ < other_rrsig.impl_->labels_ ? -1 : 1);
    }
    if (impl_->originalttl_ != other_rrsig.impl_->originalttl_) {
        return (impl_->originalttl_ < other_rrsig.impl_->originalttl_ ?
                -1 : 1);
    }
    if (impl_->timeexpire_ != other_rrsig.impl_->timeexpire_) {
        return (impl_->timeexpire_ < other_rrsig.impl_->timeexpire_ ?
                -1 : 1);
    }
    if (impl_->timeinception_ != other_rrsig.impl_->timeinception_) {
        return (impl_->timeinception_ < other_rrsig.impl_->timeinception_ ?
                -1 : 1);
    }
    if (impl_->tag_ != other_rrsig.impl_->tag_) {
        return (impl_->tag_ < other_rrsig.impl_->tag_ ? -1 : 1);
    }

    int cmp = compareNames(impl_->signer_, other_rrsig.impl_->signer_);
    if (cmp != 0) {
        return (cmp);
    }

    size_t this_len = impl_->signature_.size();
    size_t other_len = other_rrsig.impl_->signature_.size();
    size_t cmplen = min(this_len, other_len);
    cmp = memcmp(&impl_->signature_[0], &other_rrsig.impl_->signature_[0],
                 cmplen);
    if (cmp != 0) {
        return (cmp);
    } else {
        return ((this_len == other_len) ? 0 : (this_len < other_len) ? -1 : 1);
    }
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
