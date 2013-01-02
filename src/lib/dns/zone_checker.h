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

#ifndef ZONE_CHECKER_H
#define ZONE_CHECKER_H 1

#include <dns/dns_fwd.h>

#include <boost/function.hpp>

#include <string>

namespace isc {
namespace dns {

class ZoneCheckerCallbacks {
public:
    typedef boost::function<void(const std::string& reason)> IssueCallback;

    ZoneCheckerCallbacks() :
        error_callback_(nullCallback), warn_callback_(nullCallback)
    {}

    ZoneCheckerCallbacks(const IssueCallback& error_callback,
                         const IssueCallback& warn_callback) :
        error_callback_(error_callback), warn_callback_(warn_callback)
    {}

    void error(const std::string& reason) { error_callback_(reason); }
    void warn(const std::string& reason) { warn_callback_(reason); }

private:
    static void nullCallback(const std::string&) {}

    IssueCallback error_callback_;
    IssueCallback warn_callback_;
};

bool
checkZone(const Name& zone_name, const RRClass& zone_class,
          const RRsetCollectionBase& zone_rrsets,
          const ZoneCheckerCallbacks& callbacks = ZoneCheckerCallbacks());

} // namespace dns
} // namespace isc
#endif  // ZONE_CHECKER_H

// Local Variables:
// mode: c++
// End:
