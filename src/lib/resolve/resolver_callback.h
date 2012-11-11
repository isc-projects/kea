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

#ifndef ISC_RESOLVER_CALLBACK_H
#define ISC_RESOLVER_CALLBACK_H 1

#include <asiodns/dns_server.h>
#include <dns/message.h>

#include <resolve/resolver_interface.h>

namespace isc {
namespace resolve {

/// \short Standard Callback for sendQuery for DNSServer instances
///
/// This is a standard ResolverInterface::Callback implementation
/// that is used by Resolver; when RunningQuery finishes and has either
/// some data or an error, DNSServer::resume() will be called.
///
/// This class will ignore the response MessagePtr in the callback,
/// as the server itself should also have a reference.
class ResolverCallbackServer : public ResolverInterface::Callback {
public:
    ResolverCallbackServer(asiodns::DNSServer* server) :
        server_(server->clone()) {}
    ~ResolverCallbackServer() { delete server_; };
    
    void success(const isc::dns::MessagePtr response);
    void failure();

private:
    asiodns::DNSServer* server_;
};

} //namespace resolve
} //namespace isc

#endif // ISC_RESOLVER_CALLBACK_H_
