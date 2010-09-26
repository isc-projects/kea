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

#ifndef __AUTH_SRV_H
#define __AUTH_SRV_H 1

#include <string>

#include <cc/data.h>
#include <config/ccsession.h>

namespace isc {
namespace dns {
class InputBuffer;
class Message;
class MessageRenderer;
}

namespace xfr {
class AbstractXfroutClient;
};
}

namespace asio_link {
class IOMessage;
}

class AuthSrvImpl;

class AuthSrv {
    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private.
    //@{
private:
    AuthSrv(const AuthSrv& source);
    AuthSrv& operator=(const AuthSrv& source);
public:
    /// The constructor.
    ///
    /// \param use_cache Whether to enable hot spot cache for lookup results.
    /// \param xfrout_client Communication interface with a separate xfrout
    /// process.  It's normally a reference to an xfr::XfroutClient object,
    /// but can refer to a local mock object for testing (or other
    /// experimental) purposes.
    AuthSrv(const bool use_cache,
            isc::xfr::AbstractXfroutClient& xfrout_client);
    ~AuthSrv();
    //@}
    /// \return \c true if the \message contains a response to be returned;
    /// otherwise \c false.
    bool processMessage(const asio_link::IOMessage& io_message,
                        isc::dns::Message& message,
                        isc::dns::MessageRenderer& response_renderer);
    void setVerbose(bool on);
    bool getVerbose() const;
    isc::data::ConstElementPtr updateConfig(isc::data::ConstElementPtr config);
    isc::config::ModuleCCSession* configSession() const;
    void setConfigSession(isc::config::ModuleCCSession* config_session);

    /// \brief Set or update the size (number of slots) of hot spot cache.
    ///
    /// If the specified size is 0, it means the size will be unlimited.
    /// The specified size is recorded even if the cache is disabled; the
    /// new size will be effective when the cache is enabled.
    ///
    /// This method never throws an exception.
    ///
    /// \param slots The number of cache slots.
    void setCacheSlots(const size_t slots);

    /// \brief Get the current size (number of slots) of hot spot cache.
    ///
    /// It always returns the recorded size regardless of the cache is enabled.
    ///
    /// This method never throws an exception.
    ///
    /// \return The current number of cache slots.
    size_t getCacheSlots() const;

    ///
    /// Note: this interface is tentative.  We'll revisit the ASIO and session
    /// frameworks, at which point the session will probably be passed on
    /// construction of the server.
    ///
    /// \param xfrin_session A Session object over which NOTIFY message
    /// information is exchanged with a XFRIN handler.
    /// The session must be established before setting in the server
    /// object.
    /// Ownership isn't transferred: the caller is responsible for keeping
    /// this object to be valid while the server object is working and for
    /// disconnecting the session and destroying the object when the server
    ///
    void setXfrinSession(isc::cc::AbstractSession* xfrin_session);
private:
    AuthSrvImpl* impl_;
};

#endif // __AUTH_SRV_H

// Local Variables: 
// mode: c++
// End: 
