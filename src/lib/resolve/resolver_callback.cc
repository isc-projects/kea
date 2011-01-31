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

#include <resolve/resolver_callback.h>

namespace isc {
namespace resolve {

void
ResolverCallbackServer::success(isc::dns::MessagePtr response)
{
    // ignore our response here
    (void)response;
    
    server_->resume(true);
    // delete our clone now
    delete server_;
    delete this;
}

void
ResolverCallbackServer::failure()
{
    server_->resume(false);
    // delete our clone now
    delete server_;
    delete this;
}

void
ResolverCallbackDirect::success(isc::dns::MessagePtr response)
{
    if (response &&
        response->getRcode() == isc::dns::Rcode::NOERROR() &&
        response->getRRCount(isc::dns::Message::SECTION_ANSWER) > 0) {
        callback_->success(response);
        // once called back we don't need ourselves anymore
        delete this;
    } else {
        failure();
    }
}

void
ResolverCallbackDirect::failure()
{
    callback_->failure();
    // once called back we don't need ourselves anymore
    delete this;
}


} // namespace resolve
} // namespace isc
