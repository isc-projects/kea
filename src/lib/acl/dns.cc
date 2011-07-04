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

#include "dns.h"
#include "logic_check.h"

using boost::shared_ptr;

namespace isc {
namespace acl {
namespace dns {

Loader&
getLoader() {
    static Loader* loader(NULL);
    if (loader == NULL) {
        // TODO:
        // There's some trick with auto_ptr in the branch when IP check
        // is added here. That one is better, bring it in on merge.
        loader = new Loader(REJECT);
        loader->registerCreator(
            shared_ptr<NotCreator<RequestContext> >(
                new NotCreator<RequestContext>("NOT")));
        loader->registerCreator(
            shared_ptr<LogicCreator<AnyOfSpec, RequestContext> >(
                new LogicCreator<AnyOfSpec, RequestContext>("ANY")));
        loader->registerCreator(
            shared_ptr<LogicCreator<AllOfSpec, RequestContext> >(
                new LogicCreator<AllOfSpec, RequestContext>("ALL")));
    }
    return (*loader);
}

}
}
}
