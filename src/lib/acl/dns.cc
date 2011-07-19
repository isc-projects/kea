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

#include <memory>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <dns/tsigrecord.h>

#include <cc/data.h>

#include <acl/dns.h>
#include <acl/ip_check.h>
#include <acl/dnsname_check.h>
#include <acl/loader.h>
#include <acl/logic_check.h>

using namespace std;
using boost::shared_ptr;
using namespace isc::dns;
using namespace isc::data;

namespace isc {
namespace acl {

/// The specialization of \c IPCheck for access control with \c RequestContext.
///
/// It returns \c true if the remote (source) IP address of the request
/// matches the expression encapsulated in the \c IPCheck, and returns
/// \c false if not.
template <>
bool
IPCheck<dns::RequestContext>::matches(
    const dns::RequestContext& request) const
{
    return (compare(request.remote_address.getData(),
                    request.remote_address.getFamily()));
}

namespace dns {

/// The specialization of \c NameCheck for access control with
/// \c RequestContext.
///
/// TBD
template<>
bool
NameCheck<RequestContext>::matches(const RequestContext& request) const {
    return (request.tsig != NULL && request.tsig->getName() == name_);
}

vector<string>
internal::RequestCheckCreator::names() const {
    // Probably we should eventually build this vector in a more
    // sophisticated way.  For now, it's simple enough to hardcode
    // everything.
    vector<string> supported_names;
    supported_names.push_back("from");
    supported_names.push_back("key");
    return (supported_names);
}

shared_ptr<RequestCheck>
internal::RequestCheckCreator::create(const string& name,
                                      ConstElementPtr definition,
                                      // unused:
                                      const acl::Loader<RequestContext>&)
{
    if (!definition) {
        isc_throw(LoaderError,
                  "NULL pointer is passed to RequestCheckCreator");
    }

    if (name == "from") {
        return (shared_ptr<internal::RequestIPCheck>(
                    new internal::RequestIPCheck(definition->stringValue())));
    } else if (name == "key") {
        return (shared_ptr<internal::RequestKeyCheck>(
                    new internal::RequestKeyCheck(
                        Name(definition->stringValue()))));
    } else {
        // This case shouldn't happen (normally) as it should have been
        // rejected at the loader level.  But we explicitly catch the case
        // and throw an exception for that.
        isc_throw(LoaderError, "Invalid check name for RequestCheck: " <<
                  name);
    }
}

RequestLoader&
getRequestLoader() {
    static RequestLoader* loader(NULL);
    if (loader == NULL) {
        // Creator registration may throw, so we first store the new loader
        // in an auto pointer in order to provide the strong exception
        // guarantee.
        auto_ptr<RequestLoader> loader_ptr =
            auto_ptr<RequestLoader>(new RequestLoader(REJECT));

        // Register default check creator(s)
        loader_ptr->registerCreator(shared_ptr<internal::RequestCheckCreator>(
                                        new internal::RequestCheckCreator()));
        loader_ptr->registerCreator(
            shared_ptr<NotCreator<RequestContext> >(
                new NotCreator<RequestContext>("NOT")));
        loader_ptr->registerCreator(
            shared_ptr<LogicCreator<AnyOfSpec, RequestContext> >(
                new LogicCreator<AnyOfSpec, RequestContext>("ANY")));
        loader_ptr->registerCreator(
            shared_ptr<LogicCreator<AllOfSpec, RequestContext> >(
                new LogicCreator<AllOfSpec, RequestContext>("ALL")));

        // From this point there shouldn't be any exception thrown
        loader = loader_ptr.release();
    }

    return (*loader);
}

}
}
}
