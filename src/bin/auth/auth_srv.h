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

/// \brief The implementation class for the \c AuthSrv class using the pimpl
/// idiom.
class AuthSrvImpl;

/// \brief The authoritative nameserver class.
///
/// \c AuthSrv is a concrete class that implements authoritative DNS server
/// protocol processing.
/// An \c AuthSrv object is primarily responsible for handling incoming DNS
/// requests: It parses the request and dispatches subsequent processing to
/// the corresponding module (which may be an internal library or a separate
/// process) depending on the request type.  For normal queries, the
/// \c AuthSrv object searches configured data sources for the answer to the
/// query, and builds a response containing the answer.
///
/// This class uses the "pimpl" idiom, and hides detailed implementation
/// through the \c impl_ pointer (which points to an instance of the
/// \c AuthSrvImpl class).  An \c AuthSrv object is supposed to exist for quite
/// a long period, and only a few \c AuthSrv objects will be created (in fact,
/// in this current implementation there will only be one object), so the
/// construction overhead of this approach should be acceptable.
///
/// The design of this class is still in flux.  It's quite likely to change
/// in future versions.
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
    /// \param io_message The raw message received
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

    /// \brief Enable or disable verbose logging.
    ///
    /// This method never throws an exception.
    ///
    /// \param on \c true to enable verbose logging; \c false to disable
    /// verbose logging.
    void setVerbose(const bool on);

    /// \brief Returns the logging verbosity of the \c AuthSrv object.
    ///
    /// This method never throws an exception.
    ///
    /// \return \c true if verbose logging is enabled; otherwise \c false.

    /// \brief Get the current value of the verbose flag
    bool getVerbose() const;

    /// \brief Updates the data source for the \c AuthSrv object.
    ///
    /// This method installs or replaces the data source that the \c AuthSrv
    /// object refers to for query processing.
    /// Although the method name is generic, the only thing it does is to
    /// update the data source information.
    /// If there is a data source installed, it will be replaced with the
    /// new one.
    ///
    /// In the current implementation, the SQLite data source is assumed.
    /// The \c config parameter will simply be passed to the initialization
    /// routine of the \c Sqlite3DataSrc class.
    ///
    /// On success this method returns a data \c Element (in the form of a
    /// pointer like object) indicating the successful result,
    /// i.e., {"result": [0]}.
    /// Otherwise, it returns a data \c Element explaining the error:
    /// {"result": [1, <error-description>]}.
    ///
    /// This method is mostly exception free (error conditions are represented
    /// via the return value).  But it may still throw a standard exception
    /// if memory allocation fails inside the method.
    /// When a standard exception is thrown or an implementation specific
    /// exception is triggered and caught internally, this function provides
    /// the strong exception guarantee: Unless everything succeeds, currently
    /// installed data source (if any) won't be replaced.
    ///
    /// \param config An immutable pointer-like object to a data \c Element,
    /// possibly containing the data source information to be used.
    /// \return An immutable pointer-like object to a data \c Element
    /// containing the result of the update operation.
    isc::data::ConstElementPtr updateConfig(isc::data::ConstElementPtr config);

    /// \param Returns the command and configuration session for the
    /// \c AuthSrv.
    ///
    /// This method never throws an exception.
    ///
    /// \return A pointer to \c ModuleCCSession object stored in the
    /// \c AuthSrv object.  In this implementation it could be NULL.
    isc::config::ModuleCCSession* getConfigSession() const;

    /// \brief Set the command and configuration session for the \c AuthSrv.
    ///
    /// Note: this interface is tentative.  We'll revisit the ASIO and session
    /// frameworks, at which point the session will probably be passed on
    /// construction of the server.
    /// In the current implementation, this method is expected to be called
    /// exactly once as part of initialization.  If this method is called
    /// multiple times, previously specified session is silently overridden.
    ///
    /// This method never throws an exception.
    ///
    /// \param config_session A pointer to \c ModuleCCSession object to receive
    /// control commands and configuration updates.
    void setConfigSession(isc::config::ModuleCCSession* config_session);

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

    /// \brief Set the communication session with a separate process for
    /// outgoing zone transfers.
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
    /// is shutdown.
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
