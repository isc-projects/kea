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
#include <sstream>
#include <vector>

#include "base64.h"
#include "buffer.h"
#include "messagerenderer.h"
#include "name.h"
#include "rrtype.h"
#include "rrttl.h"
#include "rdata.h"
#include "rdataclass.h"
#include <boost/lexical_cast.hpp>

using namespace std;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

namespace {
inline uint32_t
convertDNSSECTime(const string time_txt)
{
    istringstream iss(time_txt);

    uint32_t timeval;
    iss >> timeval;

    // right now, we don't support the YYYYMMDDHHmmSS format for
    // expire/inception
    if (iss.bad() || iss.fail() || !iss.eof()) {
        dns_throw(InvalidRdataText, "Invalid RRSIG Time format");
    }

    return (timeval);
}
}

struct RRSIGImpl {
    // straightforward representation of RRSIG RDATA fields
    RRSIGImpl(const RRType& covered, uint8_t algorithm, uint8_t labels,
              uint32_t originalttl, uint32_t timeexpire, uint32_t timeinception,
              uint16_t keyid, const Name& signer,
              const vector<char>& signature) :
        covered_(covered), algorithm_(algorithm), labels_(labels),
        originalttl_(originalttl), timeexpire_(timeexpire),
        timeinception_(timeinception), keyid_(keyid), signer_(signer),
        signature_(signature)
    {}

    const RRType covered_;
    uint8_t algorithm_;
    uint8_t labels_;
    uint32_t originalttl_;
    uint32_t timeexpire_;
    uint32_t timeinception_;
    uint16_t keyid_;
    const Name signer_;
    const vector<char> signature_;
};

RRSIG::RRSIG(const string& rrsig_str) :
    impl_(NULL)
{
    istringstream iss(rrsig_str);
    string covered_txt, signer_txt, expire_txt, inception_txt;
    unsigned int algorithm, labels;
    uint32_t originalttl;
    uint16_t keyid;
    stringbuf signaturebuf;

    iss >> covered_txt >> algorithm >> labels >> originalttl
        >> expire_txt >> inception_txt >> keyid >> signer_txt
        >> &signaturebuf;
    if (iss.bad() || iss.fail() || !iss.eof()) {
        dns_throw(InvalidRdataText, "Invalid RRSIG text");
    }
    if (algorithm > 0xff) {
        dns_throw(InvalidRdataText, "RRSIG algorithm out of range");
    }
    if (labels > 0xff) {
        dns_throw(InvalidRdataText, "RRSIG labels out of range");
    }

    uint32_t timeexpire = convertDNSSECTime(expire_txt);
    uint32_t timeinception = convertDNSSECTime(inception_txt);

    vector<char> signature;
    decodeBase64(signaturebuf.str(), signature);

    impl_ = new RRSIGImpl(RRType(covered_txt), algorithm, labels,
                          originalttl, timeexpire, timeinception, keyid,
                          Name(signer_txt), signature);
}

RRSIG::RRSIG(InputBuffer& buffer, size_t rdata_len)
{
}

RRSIG::RRSIG(const RRSIG& source) :
    impl_(new RRSIGImpl(*source.impl_))
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
    return (impl_->covered_.toText() +
            " " + boost::lexical_cast<string>(static_cast<int>(impl_->algorithm_))
            + " " + boost::lexical_cast<string>(static_cast<int>(impl_->labels_))
            + " " + boost::lexical_cast<string>(impl_->originalttl_)
            + " " + boost::lexical_cast<string>(impl_->timeexpire_)
            + " " + boost::lexical_cast<string>(impl_->timeinception_)
            + " " + boost::lexical_cast<string>(impl_->keyid_)
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
    buffer.writeUint16(impl_->keyid_);
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
    renderer.writeUint16(impl_->keyid_);
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
    if (impl_->keyid_ != other_rrsig.impl_->keyid_) {
        return (impl_->keyid_ < other_rrsig.impl_->keyid_ ? -1 : 1);
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
