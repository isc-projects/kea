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

#ifndef RRCOLLATOR_H
#define RRCOLLATOR_H 1

#include <dns/master_loader_callbacks.h>
#include <dns/rrset.h>

#include <boost/function.hpp>

namespace isc {
namespace dns {

class RRCollator {
public:
    typedef boost::function<void(const RRsetPtr& rrset)> AddRRsetCallback;

    RRCollator(const AddRRsetCallback& callback);
    ~RRCollator();
    AddRRCallback getCallback();
    void finish();

private:
    class Impl;
    Impl* impl_;
};

} // namespace dns
} // namespace isc
#endif  // RRCOLLATOR_H

// Local Variables:
// mode: c++
// End:
