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
    /// \return \c true if the \message contains a response to be returned;
    /// otherwise \c false.
    bool processMessage(const asio_link::IOMessage& io_message,
                        isc::dns::Message& message,
                        isc::dns::MessageRenderer& response_renderer);

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
};

#endif // __AUTH_SRV_H

// Local Variables: 
// mode: c++
// End: 
