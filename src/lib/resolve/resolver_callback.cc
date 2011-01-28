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
ResolverCallbackServer::callback(bool result) {
    server_->resume(result);
    delete server_;
    delete this;
}

void
ResolverCallbackDirect::callback(bool result)
{
    // simply return with the first rrset from answer right now
    if (result &&
        answer_message_->getRcode() == isc::dns::Rcode::NOERROR() &&
        answer_message_->getRRCount(isc::dns::Message::SECTION_ANSWER) > 0) {
        std::cout << *answer_message_ << std::endl;
        isc::dns::RRsetIterator rrsi = answer_message_->beginSection(isc::dns::Message::SECTION_ANSWER);
        const isc::dns::RRsetPtr result = *rrsi;
        callback_->success(result);
    } else {
        callback_->failure();
    }
    // once called back we don't need ourselves anymore
    delete this;
}

} // namespace resolve
} // namespace isc
