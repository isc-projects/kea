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

#ifndef AUTH_SRV_H
#define AUTH_SRV_H 1

#include <config/ccsession.h>

#include <datasrc/factory.h>
#include <datasrc/client_list.h>
#include <datasrc/datasrc_config.h>

#include <dns/message.h>
#include <dns/opcode.h>
#include <util/buffer.h>

#include <asiodns/dns_server.h>
#include <asiodns/dns_service.h>
#include <asiodns/dns_lookup.h>
#include <asiodns/dns_answer.h>
#include <asiolink/io_message.h>
#include <asiolink/io_service.h>
#include <asiolink/simple_callback.h>

#include <asiolink/asiolink.h>
#include <server_common/portconfig.h>

#include <auth/statistics.h>
#include <auth/datasrc_clients_mgr.h>

#include <boost/shared_ptr.hpp>

namespace isc {
namespace util {
namespace io {
class BaseSocketSessionForwarder;
}
namespace thread {
class Mutex;
}
}
namespace datasrc {
class ConfigurableClientList;
}
namespace xfr {
class AbstractXfroutClient;
}
namespace dns {
class TSIGKeyRing;
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
///
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
    /// \param xfrout_client Communication interface with a separate xfrout
    /// process.  It's normally a reference to an xfr::XfroutClient object,
    /// but can refer to a local mock object for testing (or other
    /// experimental) purposes.
    /// \param ddns_forwarder TODO
    AuthSrv(isc::xfr::AbstractXfroutClient& xfrout_client,
            isc::util::io::BaseSocketSessionForwarder& ddns_forwarder);
    ~AuthSrv();
    //@}

    /// Stop the server.
    ///
    /// It stops the internal event loop of the server and subsequently
    /// returns the control to the top level context.
    ///
    /// This method should never throw an exception.
    void stop();

    /// \brief Process an incoming DNS message, then signal 'server' to resume
    ///
    /// A DNS query (or other message) has been received by a \c DNSServer
    /// object.  Find an answer, then post the \c DNSServer object on the
    /// I/O service queue and return.  When the server resumes, it can
    /// send the reply.
    ///
    /// \param io_message The raw message received
    /// \param message the \c Message object
    /// \param buffer an \c OutputBuffer for the resposne
    /// \param server Pointer to the \c DNSServer
    ///
    /// \throw isc::Unexpected Protocol type of \a message is unexpected
    void processMessage(const isc::asiolink::IOMessage& io_message,
                        isc::dns::Message& message,
                        isc::util::OutputBuffer& buffer,
                        isc::asiodns::DNSServer* server);

    /// \brief Updates the configuration for the \c AuthSrv object.
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

    /// \brief Returns the command and configuration session for the
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

    /// \brief Return this object's ASIO IO Service queue
    isc::asiolink::IOService& getIOService();

    /// \brief Return pointer to the DNS Lookup callback function
    isc::asiodns::DNSLookup* getDNSLookupProvider() const { return (dns_lookup_); }

    /// \brief Return pointer to the DNS Answer callback function
    isc::asiodns::DNSAnswer* getDNSAnswerProvider() const { return (dns_answer_); }

    /// \brief Return pointer to the Checkin callback function
    isc::asiolink::SimpleCallback* getCheckinProvider() const { return (checkin_); }

    /// \brief Return data source clients manager.
    ///
    /// \throw None
    isc::auth::DataSrcClientsMgr& getDataSrcClientsMgr();

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

    /// \brief Returns statistics data
    ///
    /// This function can throw an exception from
    /// Counters::get().
    ///
    /// \return JSON format statistics data.
    isc::data::ConstElementPtr getStatistics() const;

    /**
     * \brief Set and get the addresses we listen on.
     */
    void setListenAddresses(const isc::server_common::portconfig::AddressList&
                            addresses);
    const isc::server_common::portconfig::AddressList& getListenAddresses()
        const;

    /// \brief Assign an ASIO DNS Service queue to this Auth object
    void setDNSService(isc::asiodns::DNSServiceBase& dnss);

    /// \brief Sets the keyring used for verifying and signing
    ///
    /// The parameter is pointer to shared pointer, because the automatic
    /// reloading routines of tsig keys replace the actual keyring object.
    /// It is expected the pointer will point to some statically-allocated
    /// object, it doesn't take ownership of it.
    void setTSIGKeyRing(const boost::shared_ptr<isc::dns::TSIGKeyRing>*
                        keyring);

    /// \brief Create the internal forwarder for DDNS update messages
    ///
    /// Until this method is called (it is called when the
    /// start_ddns_forwarder command is sent to b10-auth), b10-auth will
    /// respond to UPDATE messages with a NOTIMP rcode.
    /// If the internal forwarder was already created, it is destroyed and
    /// created again. This is useful for instance when b10-ddns is shut
    /// down and restarted.
    void createDDNSForwarder();

    /// \brief Destroy the internal forwarder for DDNS update messages
    ///
    /// After this method has been called (it is called when the
    /// stop_ddns_forwarder command is sent to b10-auth), DDNS Update
    /// messages are no longer forwarded internally, but b10-auth will
    /// immediately respond with a NOTIMP rcode.
    /// If there was no forwarder yet, this method does nothing.
    void destroyDDNSForwarder();

    /// \brief Sets the timeout for incoming TCP connections
    ///
    /// Incoming TCP connections that have not sent their data
    /// within this time are dropped.
    ///
    /// \param timeout The timeout (in milliseconds). If se to
    /// zero, no timeouts are used, and the connection will remain
    /// open forever.
    void setTCPRecvTimeout(size_t timeout);

private:
    AuthSrvImpl* impl_;
    isc::asiolink::SimpleCallback* checkin_;
    isc::asiodns::DNSLookup* dns_lookup_;
    isc::asiodns::DNSAnswer* dns_answer_;
    isc::asiodns::DNSServiceBase* dnss_;
};

#endif // AUTH_SRV_H

// Local Variables:
// mode: c++
// End:
