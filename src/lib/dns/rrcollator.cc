// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/name.h>
#include <dns/rrcollator.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rdata.h>
#include <dns/rrset.h>

#include <boost/bind.hpp>

namespace isc {
namespace dns {

class RRCollator::Impl {
public:
    Impl(const AddRRsetCallback& callback) : callback_(callback) {}

    void addRR(const Name& name, const RRClass& rrclass,
               const RRType& rrtype, const RRTTL& rrttl,
               const rdata::RdataPtr& rdata);

    RRsetPtr current_rrset_;
    AddRRsetCallback callback_;
};

void
RRCollator::Impl::addRR(const Name& name, const RRClass& rrclass,
                        const RRType& rrtype, const RRTTL& rrttl,
                        const rdata::RdataPtr& rdata)
{
    if (current_rrset_ && current_rrset_->getType() != rrtype) {
        callback_(current_rrset_);
        current_rrset_.reset();
    }

    if (!current_rrset_) {
        current_rrset_ = RRsetPtr(new RRset(name, rrclass, rrtype, rrttl));
    }
    current_rrset_->addRdata(rdata);
}

RRCollator::RRCollator(const AddRRsetCallback& callback) :
    impl_(new Impl(callback))
{}

RRCollator::~RRCollator() {
    delete impl_;
}

AddRRCallback
RRCollator::getCallback() {
    return (boost::bind(&RRCollator::Impl::addRR, this->impl_,
                        _1, _2, _3, _4, _5));
}

void
RRCollator::finish() {
    // TODO: case when !current_rrset_
    impl_->callback_(impl_->current_rrset_);
}

} // end namespace dns
} // end namespace isc
