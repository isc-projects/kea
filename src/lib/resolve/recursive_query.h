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

#ifndef RECURSIVE_QUERY_H
#define RECURSIVE_QUERY_H 1

#include <util/buffer.h>
#include <asiodns/dns_service.h>
#include <asiodns/dns_server.h>
#include <nsas/nameserver_address_store.h>
#include <cache/resolver_cache.h>

namespace isc {
namespace asiodns {

/// \brief RTT Recorder
///
/// Used for testing, this class will hold the set of round-trip times to
/// nameservers for the current recursive query.
///
/// A pointer to an object of this class is passed to RecursiveQuery which in
/// turn passes it to the created RunningQuery class.  When a running query
/// completes, its RTT is passed to the RTT Recorder object.
class RttRecorder {
public:
    /// \brief Record Time
    ///
    /// Adds a round-trip time to the internal vector of times.
    ///
    /// \param rtt RTT to record.
    void addRtt(uint32_t rtt) {
        rtt_.push_back(rtt);
    }

    /// \brief Return RTT Vector
    std::vector<uint32_t> getRtt() const {
        return rtt_;
    }

private:
    std::vector<uint32_t>   rtt_;   ///< Stored round-trip times
};

typedef std::vector<std::pair<std::string, uint16_t> > AddressVector;

/// \brief A Running query
///
/// This base class represents an active running query object;
/// i.e. an outstanding query to an authoritative name server or
/// upstream server (when running in forwarder mode).
///
/// It can not be instantiated directly, but is created by
/// RecursiveQuery::resolve() and RecursiveQuery::forward().
///
/// Its only public method is its destructor, and that should in theory
/// not be called either except in some unit tests. Instances should
/// delete themselves when the query is finished.
class AbstractRunningQuery {
protected:
    AbstractRunningQuery() {};
public:
    virtual ~AbstractRunningQuery() {};
};

/// \brief Recursive Query
///
/// The \c RecursiveQuery class provides a layer of abstraction around
/// the ASIO code that carries out an upstream query.

class RecursiveQuery {
    ///
    /// \name Constructors
    ///
    //@{
public:
    /// \brief Constructor
    ///
    /// This is currently the only way to construct \c RecursiveQuery
    /// object. If the addresses of the forward nameservers is specified,
    /// and every upstream query will be sent to one random address, and
    /// the result sent back directly. If not, it will do full resolving.
    ///
    /// \param dns_service The DNS Service to perform the recursive
    ///        query on.
    /// \param nsas Nameserver address store, used to hold information about zone
    ///        nameservers.
    /// \param cache Resolver cache object, used to hold information about retrieved
    ///        records.
    /// \param upstream Addresses and ports of the upstream servers
    ///        to forward queries to.
    /// \param upstream_root Addresses and ports of the root servers
    ///        to use when resolving.
    /// \param query_timeout Timeout value for queries we sent, in ms
    /// \param client_timeout Timeout value for when we send back an
    ///        error, in ms
    /// \param lookup_timeout Timeout value for when we give up, in ms
    /// \param retries how many times we try again (0 means just send and
    ///     and return if it returs).
    RecursiveQuery(DNSServiceBase& dns_service,
                   isc::nsas::NameserverAddressStore& nsas,
                   isc::cache::ResolverCache& cache,
                   const std::vector<std::pair<std::string, uint16_t> >&
                   upstream,
                   const std::vector<std::pair<std::string, uint16_t> >&
                   upstream_root,
                   int query_timeout = 2000,
                   int client_timeout = 4000,
                   int lookup_timeout = 30000,
                   unsigned retries = 3);
    //@}

    /// \brief Set Round-Trip Time Recorder
    ///
    /// Sets the RTT recorder object.  This is not accessed directly, instead
    /// it is passed to created RunningQuery objects.
    ///
    /// \param recorder Pointer to the RTT recorder object used to hold RTTs.
    void setRttRecorder(boost::shared_ptr<RttRecorder>& recorder);

    /// \brief Initiate resolving
    ///
    /// When sendQuery() is called, a (set of) message(s) is sent
    /// asynchronously. If upstream servers are set, one is chosen
    /// and the response (if any) from that server will be returned.
    ///
    /// If not upstream is set, a root server is chosen from the
    /// root_servers, and the RunningQuery shall do a full resolve
    /// (i.e. if the answer is a delegation, it will be followed, etc.)
    /// until there is an answer or an error.
    ///
    /// When there is a response or an error and we give up, the given
    /// CallbackPtr object shall be called (with either success() or
    /// failure(). See ResolverInterface::Callback for more information.
    ///
    /// \param question The question being answered <qname/qclass/qtype>
    /// \param callback Callback object. See
    ///        \c ResolverInterface::Callback for more information
    AbstractRunningQuery* resolve(const isc::dns::QuestionPtr& question,
        const isc::resolve::ResolverInterface::CallbackPtr callback);


    /// \brief Initiates resolving for the given question.
    ///
    /// This actually calls the previous sendQuery() with a default
    /// callback object, which calls resume() on the given DNSServer
    /// object.
    ///
    /// \param question The question being answered <qname/qclass/qtype>
    /// \param answer_message An output Message into which the final response will
    ///        be copied.
    /// \param buffer An output buffer into which the intermediate responses will
    ///        be copied.
    /// \param server A pointer to the \c DNSServer object handling the client
    /// \return A pointer to the active AbstractRunningQuery object
    ///         created by this call (if any); this object should delete
    ///         itself in normal circumstances, and can normally be ignored
    ///         by the caller, but a pointer is returned for use-cases
    ///         such as unit tests.
    ///         Returns NULL if the data was found internally and no actual
    ///         query was sent.
    AbstractRunningQuery* resolve(const isc::dns::Question& question,
                          isc::dns::MessagePtr answer_message,
                          isc::util::OutputBufferPtr buffer,
                          DNSServer* server);

    /// \brief Initiates forwarding for the given query.
    ///
    ///  Others parameters are same with the parameters of
    ///  function resolve().
    ///
    /// \param query_message the full query got from client.
    /// \param answer_message the full answer received from other server.
    /// \param buffer Output buffer into which the responses will be copied.
    /// \param server Server object that handles receipt and processing of the
    ///               received messages.
    /// \param callback callback object
    /// \return A pointer to the active ForwardQuery created by this call;
    ///         this object should delete itself in normal circumstances,
    ///         and can normally be ignored by the caller, but a pointer
    ///         is returned for use-cases such as unit tests.
    AbstractRunningQuery* forward(isc::dns::ConstMessagePtr query_message,
                 isc::dns::MessagePtr answer_message,
                 isc::util::OutputBufferPtr buffer,
                 DNSServer* server,
                 isc::resolve::ResolverInterface::CallbackPtr callback =
                     isc::resolve::ResolverInterface::CallbackPtr());

    /// \brief Set Test Server
    ///
    /// This method is *only* for unit testing the class.  If set, it enables
    /// recursive behaviour but, regardless of responses received, sends every
    /// query to the test server.
    ///
    /// The test server is enabled by setting a non-zero port number.
    ///
    /// \param address IP address of the test server.
    /// \param port Port number of the test server
    void setTestServer(const std::string& address, uint16_t port);

private:
    DNSServiceBase& dns_service_;
    isc::nsas::NameserverAddressStore& nsas_;
    isc::cache::ResolverCache& cache_;
    boost::shared_ptr<std::vector<std::pair<std::string, uint16_t> > >
        upstream_;
    boost::shared_ptr<std::vector<std::pair<std::string, uint16_t> > >
        upstream_root_;
    std::pair<std::string, uint16_t> test_server_;
    int query_timeout_;
    int client_timeout_;
    int lookup_timeout_;
    unsigned retries_;
    boost::shared_ptr<RttRecorder>  rtt_recorder_;  ///< Round-trip time recorder
};

}      // namespace asiodns
}      // namespace isc
#endif // RECURSIVE_QUERY_H
