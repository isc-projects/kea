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

#ifndef __AUTH_SRV_H
#define __AUTH_SRV_H 1

#include <string>

// For InMemoryClientPtr below.  This should be a temporary definition until
// we reorganize the data source framework.
#include <boost/shared_ptr.hpp>

#include <cc/data.h>
#include <config/ccsession.h>
#include <dns/message.h>
#include <util/buffer.h>

#include <asiodns/dns_server.h>
#include <asiodns/dns_lookup.h>
#include <asiodns/dns_answer.h>
#include <asiolink/io_message.h>
#include <asiolink/io_service.h>
#include <asiolink/simple_callback.h>

#include <asiolink/asiolink.h>
#include <server_common/portconfig.h>
#include <auth/statistics.h>

namespace isc {
namespace datasrc {
class InMemoryClient;
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
    /// \param use_cache Whether to enable hot spot cache for lookup results.
    /// \param xfrout_client Communication interface with a separate xfrout
    /// process.  It's normally a reference to an xfr::XfroutClient object,
    /// but can refer to a local mock object for testing (or other
    /// experimental) purposes.
    AuthSrv(const bool use_cache,
            isc::xfr::AbstractXfroutClient& xfrout_client);
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
    /// \param message Pointer to the \c Message object
    /// \param buffer Pointer to an \c OutputBuffer for the resposne
    /// \param server Pointer to the \c DNSServer
    ///
    /// \throw isc::Unexpected Protocol type of \a message is unexpected
    void processMessage(const isc::asiolink::IOMessage& io_message,
                        isc::dns::MessagePtr message,
                        isc::util::OutputBufferPtr buffer,
                        isc::asiodns::DNSServer* server);

    /// \brief Updates the data source for the \c AuthSrv object.
    ///
    /// This method installs or replaces the data source that the \c AuthSrv
    /// object refers to for query processing.
    /// Although the method name is generic, the only thing it does is to
    /// update the data source information.
    /// If there is a data source installed, it will be replaced with the
    /// new one.
    ///
    /// In the current implementation, the SQLite data source and InMemoryClient
    /// are assumed.
    /// We can enable memory data source and get the path of SQLite database by
    /// the \c config parameter.  If we disabled memory data source, the SQLite
    /// data source will be used.
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

    /// A shared pointer type for \c InMemoryClient.
    ///
    /// This is defined inside the \c AuthSrv class as it's supposed to be
    /// a short term interface until we integrate the in-memory and other
    /// data source frameworks.
    typedef boost::shared_ptr<isc::datasrc::InMemoryClient> InMemoryClientPtr;

    /// An immutable shared pointer type for \c InMemoryClient.
    typedef boost::shared_ptr<const isc::datasrc::InMemoryClient>
    ConstInMemoryClientPtr;

    /// Returns the in-memory data source configured for the \c AuthSrv,
    /// if any.
    ///
    /// The in-memory data source is configured per RR class.  However,
    /// the data source may not be available for all RR classes.
    /// If it is not available for the specified RR class, an exception of
    /// class \c InvalidParameter will be thrown.
    /// This method never throws an exception otherwise.
    ///
    /// Even for supported RR classes, the in-memory data source is not
    /// configured by default.  In that case a NULL (shared) pointer will
    /// be returned.
    ///
    /// \param rrclass The RR class of the requested in-memory data source.
    /// \return A pointer to the in-memory data source, if configured;
    /// otherwise NULL.
    InMemoryClientPtr getInMemoryClient(const isc::dns::RRClass& rrclass);

    /// Sets or replaces the in-memory data source of the specified RR class.
    ///
    /// As noted in \c getInMemoryClient(), some RR classes may not be
    /// supported, in which case an exception of class \c InvalidParameter
    /// will be thrown.
    /// This method never throws an exception otherwise.
    ///
    /// If there is already an in memory data source configured, it will be
    /// replaced with the newly specified one.
    /// \c memory_datasrc can be NULL, in which case it will (re)disable the
    /// in-memory data source.
    ///
    /// \param rrclass The RR class of the in-memory data source to be set.
    /// \param memory_datasrc A (shared) pointer to \c InMemoryClient to be set.
    void setInMemoryClient(const isc::dns::RRClass& rrclass,
                           InMemoryClientPtr memory_client);

    /// \brief Set the communication session with Statistics.
    ///
    /// This function never throws an exception as far as
    /// AuthCounters::setStatisticsSession() doesn't throw.
    ///
    /// Note: this interface is tentative.  We'll revisit the ASIO and
    /// session frameworks, at which point the session will probably
    /// be passed on construction of the server.
    ///
    /// \param statistics_session A Session object over which statistics
    /// information is exchanged with statistics module.
    /// The session must be established before setting in the server
    /// object.
    /// Ownership isn't transferred: the caller is responsible for keeping
    /// this object to be valid while the server object is working and for
    /// disconnecting the session and destroying the object when the server
    /// is shutdown.
    void setStatisticsSession(isc::cc::AbstractSession* statistics_session);

    /// Return the interval of periodic submission of statistics in seconds.
    ///
    /// If the statistics submission is disabled, it returns 0.
    ///
    /// This method never throws an exception.
    uint32_t getStatisticsTimerInterval() const;

    /// Set the interval of periodic submission of statistics.
    ///
    /// If the specified value is non 0, the \c AuthSrv object will submit
    /// its statistics to the statistics module every \c interval seconds.
    /// If it's 0, and \c AuthSrv currently submits statistics, the submission
    /// will be disabled. \c interval must be equal to or shorter than 86400
    /// seconds (1 day).
    ///
    /// This method should normally not throw an exception; however, its
    /// underlying library routines may involve resource allocation, and
    /// when it fails it would result in a corresponding standard exception.
    ///
    /// \param interval The submission interval in seconds if non 0;
    /// or a value of 0 to disable the submission.
    void setStatisticsTimerInterval(uint32_t interval);

    /// \brief Submit statistics counters to statistics module.
    ///
    /// This function can throw an exception from
    /// AuthCounters::submitStatistics().
    ///
    /// \return true on success, false on failure (e.g. session timeout,
    /// session error).
    bool submitStatistics() const;

    /// \brief Get the value of counter in the AuthCounters.
    /// 
    /// This function calls AuthCounters::getCounter() and
    /// returns its return value.
    ///
    /// This function never throws an exception as far as
    /// AuthCounters::getCounter() doesn't throw.
    /// 
    /// Note: Currently this function is for testing purpose only.
    ///
    /// \param type Type of a counter to get the value of
    ///
    /// \return the value of the counter.
    uint64_t getCounter(const AuthCounters::CounterType type) const;

    /**
     * \brief Set and get the addresses we listen on.
     */
    void setListenAddresses(const isc::server_common::portconfig::AddressList&
                            addreses);
    const isc::server_common::portconfig::AddressList& getListenAddresses()
        const;

    /// \brief Assign an ASIO DNS Service queue to this Auth object
    void setDNSService(isc::asiodns::DNSService& dnss);

    /// \brief Sets the keyring used for verifying and signing
    ///
    /// The parameter is pointer to shared pointer, because the automatic
    /// reloading routines of tsig keys replace the actual keyring object.
    /// It is expected the pointer will point to some statically-allocated
    /// object, it doesn't take ownership of it.
    void setTSIGKeyRing(const boost::shared_ptr<isc::dns::TSIGKeyRing>*
                        keyring);

private:
    AuthSrvImpl* impl_;
    isc::asiolink::SimpleCallback* checkin_;
    isc::asiodns::DNSLookup* dns_lookup_;
    isc::asiodns::DNSAnswer* dns_answer_;
    isc::asiodns::DNSService* dnss_;
};

#endif // __AUTH_SRV_H

// Local Variables: 
// mode: c++
// End: 
