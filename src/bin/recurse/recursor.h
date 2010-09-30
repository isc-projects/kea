// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __RECURSOR_H
#define __RECURSOR_H 1

#include <string>

#include <cc/data.h>
#include <config/ccsession.h>

#include <asiolink/asiolink.h>

namespace isc {
namespace dns {
class InputBuffer;
class Message;
class MessageRenderer;
}
}

namespace asiolink {
class IOMessage;
}

class RecursorImpl;

class Recursor {
    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private.
    //@{
private:
    Recursor(const Recursor& source);
    Recursor& operator=(const Recursor& source);
public:
    /// The constructor.
    ///
    /// \param use_cache Whether to enable hot spot cache for lookup results.
    /// \param xfrout_client Communication interface with a separate xfrout
    /// process.  It's normally a reference to an xfr::XfroutClient object,
    /// but can refer to a local mock object for testing (or other
    /// experimental) purposes.
    Recursor(asiolink::IOService& io_service);
    ~Recursor();
    //@}
    /// \return \c true if the \message contains a response to be returned;
    /// otherwise \c false.
    void processMessage(const asiolink::IOMessage& io_message,
                        isc::dns::Message& message,
                        isc::dns::MessageRenderer& response_renderer,
                        asiolink::BasicServer* server, bool& complete);
    void setVerbose(bool on);
    bool getVerbose() const;
    isc::data::ConstElementPtr updateConfig(isc::data::ConstElementPtr config);
    isc::config::ModuleCCSession* configSession() const;
    void setConfigSession(isc::config::ModuleCCSession* config_session);

    asiolink::DNSLookup* getDNSLookupProvider() {
        return (dns_lookup_);
    }
    asiolink::DNSAnswer* getDNSAnswerProvider() {
        return (dns_answer_);
    }
    asiolink::IOCallback* getCheckinProvider() {
        return (checkin_);
    }

private:
    RecursorImpl* impl_;
    asiolink::IOCallback* checkin_;
    asiolink::DNSLookup* dns_lookup_;
    asiolink::DNSAnswer* dns_answer_;
};

#endif // __RECURSOR_H

// Local Variables: 
// mode: c++
// End: 
