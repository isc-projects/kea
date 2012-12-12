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

#ifndef RESOLVER_H
#define RESOLVER_H 1

#include <string>
#include <vector>
#include <utility>

#include <boost/shared_ptr.hpp>

#include <cc/data.h>
#include <config/ccsession.h>
#include <acl/dns.h>
#include <dns/message.h>
#include <util/buffer.h>

#include <asiodns/dns_server.h>
#include <asiodns/dns_service.h>
#include <asiodns/dns_lookup.h>
#include <asiodns/dns_answer.h>
#include <asiolink/io_message.h>
#include <asiolink/io_service.h>
#include <asiolink/simple_callback.h>

#include <nsas/nameserver_address_store.h>
#include <cache/resolver_cache.h>

#include <resolve/resolver_interface.h>

class ResolverImpl;

/**
 * \short The recursive nameserver.
 *
 * It is a concreate class implementing recursive DNS server protocol
 * processing. It is responsible for handling incoming DNS requests. It parses
 * them, passes them deeper into the resolving machinery and then creates the
 * answer. It doesn't really know about chasing referrals and similar, it
 * simply plugs the parts that know into the network handling code.
 */
class Resolver : public isc::resolve::ResolverInterface {
    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private.
    //@{
private:
    Resolver(const Resolver& source);
    Resolver& operator=(const Resolver& source);
public:
    /// The constructor.
    Resolver();
    ~Resolver();
    //@}

    virtual void resolve(
        const isc::dns::QuestionPtr& question,
        const isc::resolve::ResolverInterface::CallbackPtr& callback);

    /// \brief Process an incoming DNS message, then signal 'server' to resume 
    ///
    /// A DNS query (or other message) has been received by a \c DNSServer
    /// object.  Find an answer, then post the \c DNSServer object on the
    /// I/O service queue and return.  When the server resumes, it can
    /// send the reply.
    ///
    /// \param io_message The raw message received
    /// \param query_message Pointer to the query Message object we
    /// received from the client
    /// \param answer_message Pointer to the anwer Message object we
    /// shall return to the client
    /// \param buffer Pointer to an \c OutputBuffer for the resposne
    /// \param server Pointer to the \c DNSServer
    void processMessage(const isc::asiolink::IOMessage& io_message,
                        isc::dns::MessagePtr query_message,
                        isc::dns::MessagePtr answer_message,
                        isc::util::OutputBufferPtr buffer,
                        isc::asiodns::DNSServer* server);

    /// \brief Set and get the config session
    isc::config::ModuleCCSession* getConfigSession() const;
    void setConfigSession(isc::config::ModuleCCSession* config_session);

    /// \brief Handle commands from the config session.
    ///
    /// By default, or if \c startup is set to false explicitly, this method
    /// will ignore any other configuration parameters if listen_on fails;
    /// if \c startup is true, it will install as many parameters as possible.
    isc::data::ConstElementPtr updateConfig(isc::data::ConstElementPtr config,
                                            bool startup = false);

    /// \brief Assign an ASIO IO Service queue to this Resolver object
    void setDNSService(isc::asiodns::DNSServiceBase& dnss);

    /// \brief Assign a NameserverAddressStore to this Resolver object
    void setNameserverAddressStore(isc::nsas::NameserverAddressStore &nsas);

    /// \brief Assign a cache to this Resolver object
    void setCache(isc::cache::ResolverCache& cache);

    /// \brief Return this object's ASIO IO Service queue
    isc::asiodns::DNSServiceBase& getDNSService() const { return (*dnss_); }

    /// \brief Returns this object's NSAS
    isc::nsas::NameserverAddressStore& getNameserverAddressStore() const {
        return *nsas_;
    };

    /// \brief Returns this object's ResolverCache
    isc::cache::ResolverCache& getResolverCache() const {
        return *cache_;
    };

    /// \brief Return pointer to the DNS Lookup callback function
    isc::asiodns::DNSLookup* getDNSLookupProvider() { return (dns_lookup_); }

    /// \brief Return pointer to the DNS Answer callback function
    isc::asiodns::DNSAnswer* getDNSAnswerProvider() { return (dns_answer_); }

    /// \brief Return pointer to the Checkin callback function
    isc::asiolink::SimpleCallback* getCheckinProvider() { return (checkin_); }

    /**
     * \brief Specify the list of upstream servers.
     *
     * Specify the list off addresses of upstream servers to forward queries
     * to. If the list is empty, this server is set to full recursive mode.
     * If it is non-empty, it switches to forwarder.
     *
     * @param addresses The list of addresses to use (each one is the address
     * and port pair).
     */
    void setForwardAddresses(const std::vector<std::pair<std::string,
        uint16_t> >& addresses);
    /**
     * \short Get list of upstream addresses.
     *
     * \see setForwardAddresses.
     */
    std::vector<std::pair<std::string, uint16_t> > getForwardAddresses() const;
    /// Return if we are in forwarding mode (if not, we are in fully recursive)
    bool isForwarding() const;

    /**
     * \brief Specify the list of root nameservers.
     *
     * Specify the list of addresses of root nameservers
     *
     * @param addresses The list of addresses to use (each one is the address
     * and port pair).
     */
    void setRootAddresses(const std::vector<std::pair<std::string,
                          uint16_t> >& addresses);

    /**
     * \short Get list of root addresses.
     *
     * \see setRootAddresses.
     */
    std::vector<std::pair<std::string, uint16_t> > getRootAddresses() const;

    /**
     * Set and get the addresses we listen on.
     */
    void setListenAddresses(const std::vector<std::pair<std::string,
        uint16_t> >& addresses);
    std::vector<std::pair<std::string, uint16_t> > getListenAddresses() const;

    /**
     * \short Set options related to timeouts.
     *
     * This sets the time of timeout and number of retries.
     * \param query_timeout The timeout we use for queries we send
     * \param client_timeout The timeout at which point we send back a
     * SERVFAIL (while continuing to resolve the query)
     * \param lookup_timeout The timeout at which point we give up and
     * stop.
     * \param retries The number of retries (0 means try the first time only,
     *     do not retry).
     */
    void setTimeouts(int query_timeout = 2000,
                     int client_timeout = 4000,
                     int lookup_timeout = 30000,
                     unsigned retries = 3);

    /**
     * \short Get info about timeouts.
     *
     * \returns Timeout and retries (as described in setTimeouts).
     */
    std::pair<int, unsigned> getTimeouts() const;

    /**
     * \brief Get the timeout for outgoing queries
     *
     * \returns Timeout for outgoing queries
     */
    int getQueryTimeout() const;

    /**
     * \brief Get the timeout for incoming client queries
     *
     * After this timeout, a SERVFAIL shall be sent back
     * (internal resolving on the query will continue, see
     * \c getLookupTimeout())
     * 
     * \returns Timeout for outgoing queries
     */
    int getClientTimeout() const;

    /**
     * \brief Get the timeout for lookups
     *
     * After this timeout, internal processing shall stop
     */
    int getLookupTimeout() const;

    /**
     * \brief Get the number of retries for outgoing queries
     *
     * If a query times out (value of \c getQueryTimeout()), we
     * will retry this number of times
     */
    int getRetries() const;

    /// Get the query ACL.
    ///
    /// \exception None
    const isc::acl::dns::RequestACL& getQueryACL() const;

    /// Set the new query ACL.
    ///
    /// This method replaces the existing query ACL completely.
    /// Normally this method will be called via the configuration handler,
    /// but is publicly available for convenience of tests (and other
    /// experimental purposes).
    /// \c new_acl must not be a NULL pointer.
    ///
    /// \exception InvalidParameter The given pointer is NULL
    ///
    /// \param new_acl The new ACL to replace the existing one.
    void setQueryACL(boost::shared_ptr<const isc::acl::dns::RequestACL>
                     new_acl);

private:
    ResolverImpl* impl_;
    isc::asiodns::DNSServiceBase* dnss_;
    isc::asiolink::SimpleCallback* checkin_;
    isc::asiodns::DNSLookup* dns_lookup_;
    isc::asiodns::DNSAnswer* dns_answer_;
    isc::nsas::NameserverAddressStore* nsas_;
    isc::cache::ResolverCache* cache_;
};

#endif // RESOLVER_H

// Local Variables:
// mode: c++
// End:
