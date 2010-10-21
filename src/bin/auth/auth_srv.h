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

#include <asiolink/asiolink.h>

namespace isc {
namespace xfr {
class AbstractXfroutClient;
}
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

    /// \brief Process an incoming DNS message, then signal 'server' to resume 
    ///
    /// A DNS query (or other message) has been received by a \c DNSServer
    /// object.  Find an answer, then post the \c DNSServer object on the
    /// I/O service queue and return.  When the server resumes, it can
    /// send the reply.
    ///
    /// \param io_message The I/O service queue
    /// \param message Pointer to the \c Message object
    /// \param buffer Pointer to an \c OutputBuffer for the resposne
    /// \param server Pointer to the \c DNSServer
    void processMessage(const asiolink::IOMessage& io_message,
                        isc::dns::MessagePtr message,
                        isc::dns::OutputBufferPtr buffer,
                        asiolink::DNSServer* server);

    /// \brief Set verbose flag
    ///
    /// \param on The new value of the verbose flag
    void setVerbose(bool on);

    /// \brief Get the current value of the verbose flag
    bool getVerbose() const;

    /// \brief Set and get the config session
    void setConfigSession(isc::config::ModuleCCSession* config_session);
    isc::config::ModuleCCSession* getConfigSession() const;

    /// \brief Handle commands from the config session
    isc::data::ConstElementPtr updateConfig(isc::data::ConstElementPtr config);

    /// \brief Assign an ASIO IO Service queue to this Recursor object
    void setIOService(asiolink::IOService& ios) { io_service_ = &ios; }

    /// \brief Return this object's ASIO IO Service queue
    asiolink::IOService& getIOService() const { return (*io_service_); }

    /// \brief Return pointer to the DNS Lookup callback function
    asiolink::DNSLookup* getDNSLookupProvider() const { return (dns_lookup_); }

    /// \brief Return pointer to the DNS Answer callback function
    asiolink::DNSAnswer* getDNSAnswerProvider() const { return (dns_answer_); }

    /// \brief Return pointer to the Checkin callback function
    asiolink::SimpleCallback* getCheckinProvider() const { return (checkin_); }

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
    asiolink::IOService* io_service_;
    asiolink::SimpleCallback* checkin_;
    asiolink::DNSLookup* dns_lookup_;
    asiolink::DNSAnswer* dns_answer_;
};

#endif // __AUTH_SRV_H

// Local Variables: 
// mode: c++
// End: 
