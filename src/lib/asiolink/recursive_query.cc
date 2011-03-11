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

#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>             // for some IPC/network system calls

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include <config.h>

#include <log/dummylog.h>

#include <dns/question.h>
#include <dns/message.h>
#include <dns/opcode.h>

#include <resolve/resolve.h>
#include <cache/resolver_cache.h>

#include <asio.hpp>
#include <asiolink/dns_service.h>
#include <asiolink/io_fetch.h>
#include <asiolink/io_service.h>
#include <asiolink/recursive_query.h>

using isc::log::dlog;
using namespace isc::dns;

namespace asiolink {

typedef std::vector<std::pair<std::string, uint16_t> > AddressVector;

// Here we do not use the typedef above, as the SunStudio compiler
// mishandles this in its name mangling, and wouldn't compile.
// We can probably use a typedef, but need to move it to a central
// location and use it consistently.
RecursiveQuery::RecursiveQuery(DNSService& dns_service,
    const std::vector<std::pair<std::string, uint16_t> >& upstream,
    const std::vector<std::pair<std::string, uint16_t> >& upstream_root,
    int query_timeout, int client_timeout, int lookup_timeout,
    unsigned retries) :
    dns_service_(dns_service), upstream_(new AddressVector(upstream)),
    upstream_root_(new AddressVector(upstream_root)),
    test_server_("", 0),
    query_timeout_(query_timeout), client_timeout_(client_timeout),
    lookup_timeout_(lookup_timeout), retries_(retries)
{}

// Set the test server - only used for unit testing.

void
RecursiveQuery::setTestServer(const std::string& address, uint16_t port) {
    dlog("Setting test server to " + address + "(" +
            boost::lexical_cast<std::string>(port) + ")");
    test_server_.first = address;
    test_server_.second = port;
}


namespace {

typedef std::pair<std::string, uint16_t> addr_t;

/*
 * This is a query in progress. When a new query is made, this one holds
 * the context information about it, like how many times we are allowed
 * to retry on failure, what to do when we succeed, etc.
 *
 * Used by RecursiveQuery::sendQuery.
 */
class RunningQuery : public IOFetch::Callback {
private:
    // The io service to handle async calls
    IOService& io_;

    // Info for (re)sending the query (the question and destination)
    Question question_;

    // This is where we build and store our final answer
    MessagePtr answer_message_;

    // currently we use upstream as the current list of NS records
    // we should differentiate between forwarding and resolving
    boost::shared_ptr<AddressVector> upstream_;

    // root servers...just copied over to the zone_servers_
    boost::shared_ptr<AddressVector> upstream_root_;

    // Test server - only used for testing.  This takes precedence over all
    // other servers if the port is non-zero.
    std::pair<std::string, uint16_t> test_server_;

    // Buffer to store the result.
    OutputBufferPtr buffer_;

    // Server to notify when we succeed or fail
    //shared_ptr<DNSServer> server_;
    isc::resolve::ResolverInterface::CallbackPtr resolvercallback_;

    // Protocol used for the last query.  This is set to IOFetch::UDP when a
    // new upstream query is initiated, and changed to IOFetch::TCP if a
    // packet is returned with the TC bit set.  It is stored here to detect the
    // case of a TCP packet being returned with the TC bit set.
    IOFetch::Protocol protocol_;

    // To prevent both unreasonably long cname chains and cname loops,
    // we simply keep a counter of the number of CNAMEs we have
    // followed so far (and error if it exceeds RESOLVER_MAX_CNAME_CHAIN
    // from lib/resolve/response_classifier.h)
    unsigned cname_count_;

    /*
     * TODO Do something more clever with timeouts. In the long term, some
     *     computation of average RTT, increase with each retry, etc.
     */
    // Timeout information
    int query_timeout_;
    unsigned retries_;

    // normal query state

    // Not using NSAS at this moment, so we keep a list
    // of 'current' zone servers
    std::vector<addr_t> zone_servers_;

    // Update the question that will be sent to the server
    void setQuestion(const Question& new_question) {
        question_ = new_question;
    }

    // TODO: replace by our wrapper
    asio::deadline_timer client_timer;
    asio::deadline_timer lookup_timer;

    size_t queries_out_;
    
    // If we timed out ourselves (lookup timeout), stop issuing queries
    bool done_;

    // If we have a client timeout, we send back an answer, but don't
    // stop. We use this variable to make sure we don't send another
    // answer if we do find one later (or if we have a lookup_timeout)
    bool answer_sent_;

    // Reference to our cache
    isc::cache::ResolverCache& cache_;

    // perform a single lookup; first we check the cache to see
    // if we have a response for our query stored already. if
    // so, call handlerecursiveresponse(), if not, we call send()
    void doLookup() {
        dlog("doLookup: try cache");
        Message cached_message(Message::RENDER);
        isc::resolve::initResponseMessage(question_, cached_message);
        if (cache_.lookup(question_.getName(), question_.getType(),
                          question_.getClass(), cached_message)) {
            dlog("Message found in cache, returning that");
            handleRecursiveAnswer(cached_message);
        } else {
            send();
        }
        
    }

    // (re)send the query to the server.
    //
    // \param protocol Protocol to use for the fetch (default is UDP)
    void send(IOFetch::Protocol protocol = IOFetch::UDP) {
        const int uc = upstream_->size();
        const int zs = zone_servers_.size();
        protocol_ = protocol;   // Store protocol being used for this
        buffer_->clear();
        if (test_server_.second != 0) {
            dlog("Sending upstream query (" + question_.toText() +
                 ") to test server at " + test_server_.first);
            IOFetch query(protocol, io_, question_,
                test_server_.first,
                test_server_.second, buffer_, this,
                query_timeout_);
            ++queries_out_;
            io_.get_io_service().post(query);
        } else if (uc > 0) {
            int serverIndex = rand() % uc;
            dlog("Sending upstream query (" + question_.toText() +
                ") to " + upstream_->at(serverIndex).first);
            IOFetch query(protocol, io_, question_,
                upstream_->at(serverIndex).first,
                upstream_->at(serverIndex).second, buffer_, this,
                query_timeout_);
            ++queries_out_;
            io_.get_io_service().post(query);
        } else if (zs > 0) {
            int serverIndex = rand() % zs;
            dlog("Sending query to zone server (" + question_.toText() +
                ") to " + zone_servers_.at(serverIndex).first);
            IOFetch query(protocol, io_, question_,
                zone_servers_.at(serverIndex).first,
                zone_servers_.at(serverIndex).second, buffer_, this,
                query_timeout_);
            ++queries_out_;
            io_.get_io_service().post(query);
        } else {
            dlog("Error, no upstream servers to send to.");
        }
    }
    
    // This function is called by operator() if there is an actual
    // answer from a server and we are in recursive mode
    // depending on the contents, we go on recursing or return
    //
    // Note that the footprint may change as this function may
    // need to append data to the answer we are building later.
    //
    // returns true if we are done (either we have an answer or an
    //              error message)
    // returns false if we are not done
    bool handleRecursiveAnswer(const Message& incoming) {
        dlog("Handle response");
        // In case we get a CNAME, we store the target
        // here (classify() will set it when it walks through
        // the cname chain to verify it).
        Name cname_target(question_.getName());
        
        isc::resolve::ResponseClassifier::Category category =
            isc::resolve::ResponseClassifier::classify(
                question_, incoming, cname_target, cname_count_);

        bool found_ns_address = false;
            
        // If the packet is OK, store it in the cache
        if (!isc::resolve::ResponseClassifier::error(category)) {
            cache_.update(incoming);
        }

        switch (category) {
        case isc::resolve::ResponseClassifier::ANSWER:
        case isc::resolve::ResponseClassifier::ANSWERCNAME:
            // Done. copy and return.
            isc::resolve::copyResponseMessage(incoming, answer_message_);
            return true;
            break;
        case isc::resolve::ResponseClassifier::CNAME:
            dlog("Response is CNAME!");
            // (unfinished) CNAME. We set our question_ to the CNAME
            // target, then start over at the beginning (for now, that
            // is, we reset our 'current servers' to the root servers).
            if (cname_count_ >= RESOLVER_MAX_CNAME_CHAIN) {
                // just give up
                dlog("CNAME chain too long");
                isc::resolve::makeErrorMessage(answer_message_,
                                               Rcode::SERVFAIL());
                return true;
            }

            answer_message_->appendSection(Message::SECTION_ANSWER,
                                           incoming);
            setZoneServersToRoot();

            question_ = Question(cname_target, question_.getClass(),
                                 question_.getType());

            dlog("Following CNAME chain to " + question_.toText());
            doLookup();
            return false;
            break;
        case isc::resolve::ResponseClassifier::NXDOMAIN:
            // NXDOMAIN, just copy and return.
            isc::resolve::copyResponseMessage(incoming, answer_message_);
            return true;
            break;
        case isc::resolve::ResponseClassifier::REFERRAL:
            // Referral. For now we just take the first glue address
            // we find and continue with that
            zone_servers_.clear();

            for (RRsetIterator rrsi = incoming.beginSection(Message::SECTION_ADDITIONAL);
                 rrsi != incoming.endSection(Message::SECTION_ADDITIONAL) && !found_ns_address;
                 rrsi++) {
                ConstRRsetPtr rrs = *rrsi;
                if (rrs->getType() == RRType::A()) {
                    // found address
                    RdataIteratorPtr rdi = rrs->getRdataIterator();
                    // just use the first for now
                    if (!rdi->isLast()) {
                        std::string addr_str = rdi->getCurrent().toText();
                        dlog("[XX] first address found: " + addr_str);
                        // now we have one address, simply
                        // resend that exact same query
                        // to that address and yield, when it
                        // returns, loop again.
                        
                        // TODO should use NSAS
                        zone_servers_.push_back(addr_t(addr_str, 53));
                        found_ns_address = true;
                        break;
                    }
                }
            }
            if (found_ns_address) {
                // next resolver round
                // we do NOT use doLookup() here, but send() (i.e. we
                // skip the cache), since if we had the final answer
                // instead of a delegation cached, we would have been
                // there by now.
                send();
                return false;
            } else {
                dlog("[XX] no ready-made addresses in additional. need nsas.");
                // TODO this will result in answering with the delegation. oh well
                isc::resolve::copyResponseMessage(incoming, answer_message_);
                return true;
            }
            break;
        case isc::resolve::ResponseClassifier::TRUNCATED:
            // Truncated packet.  If the protocol we used for the last one is
            // UDP, re-query using TCP.  Otherwise regard it as an error.
            if (protocol_ == IOFetch::UDP) {
                dlog("Response truncated, re-querying over TCP");
                send(IOFetch::TCP);
                return false;
            }
            // Was a TCP query so we have received a packet over TCP with the TC
            // bit set: drop through to common error processing.
            // TODO: Can we use what we have received instead of discarding it?

        case isc::resolve::ResponseClassifier::EMPTY:
        case isc::resolve::ResponseClassifier::EXTRADATA:
        case isc::resolve::ResponseClassifier::INVNAMCLASS:
        case isc::resolve::ResponseClassifier::INVTYPE:
        case isc::resolve::ResponseClassifier::MISMATQUEST:
        case isc::resolve::ResponseClassifier::MULTICLASS:
        case isc::resolve::ResponseClassifier::NOTONEQUEST:
        case isc::resolve::ResponseClassifier::NOTRESPONSE:
        case isc::resolve::ResponseClassifier::NOTSINGLE:
        case isc::resolve::ResponseClassifier::OPCODE:
        case isc::resolve::ResponseClassifier::RCODE:

            // Should we try a different server rather than SERVFAIL?
            isc::resolve::makeErrorMessage(answer_message_,
                                           Rcode::SERVFAIL());
            return true;
            break;
        }
        // should not be reached. assert here?
        dlog("[FATAL] unreachable code");
        return true;
    }
    
public:
    RunningQuery(IOService& io,
        const Question &question,
        MessagePtr answer_message,
        boost::shared_ptr<AddressVector> upstream,
        boost::shared_ptr<AddressVector> upstream_root,
        std::pair<std::string, uint16_t>& test_server,
        OutputBufferPtr buffer,
        isc::resolve::ResolverInterface::CallbackPtr cb,
        int query_timeout, int client_timeout, int lookup_timeout,
        unsigned retries,
        isc::cache::ResolverCache& cache) :
        io_(io),
        question_(question),
        answer_message_(answer_message),
        upstream_(upstream),
        upstream_root_(upstream_root),
        test_server_(test_server),
        buffer_(buffer),
        resolvercallback_(cb),
        protocol_(IOFetch::UDP),
        cname_count_(0),
        query_timeout_(query_timeout),
        retries_(retries),
        client_timer(io.get_io_service()),
        lookup_timer(io.get_io_service()),
        queries_out_(0),
        done_(false),
        answer_sent_(false),
        cache_(cache)
    {
        // Setup the timer to stop trying (lookup_timeout)
        if (lookup_timeout >= 0) {
            lookup_timer.expires_from_now(
                boost::posix_time::milliseconds(lookup_timeout));
            lookup_timer.async_wait(boost::bind(&RunningQuery::stop, this, false));
        }
        
        // Setup the timer to send an answer (client_timeout)
        if (client_timeout >= 0) {
            client_timer.expires_from_now(
                boost::posix_time::milliseconds(client_timeout));
            client_timer.async_wait(boost::bind(&RunningQuery::clientTimeout, this));
        }
        
        // should use NSAS for root servers
        // Adding root servers if not a forwarder
        if (upstream_->empty()) {
            setZoneServersToRoot();
        }

        doLookup();
    }

    void setZoneServersToRoot() {
        zone_servers_.clear();
        if (upstream_root_->empty()) { //if no root ips given, use this
            zone_servers_.push_back(addr_t("192.5.5.241", 53));
        } else {
            // copy the list
            dlog("Size is " + 
                boost::lexical_cast<std::string>(upstream_root_->size()) + 
                "\n");
            for(AddressVector::iterator it = upstream_root_->begin();
                it < upstream_root_->end(); ++it) {
            zone_servers_.push_back(addr_t(it->first,it->second));
            dlog("Put " + zone_servers_.back().first + "into root list\n");
            }
        }
    }
    virtual void clientTimeout() {
        // Return a SERVFAIL, but do not stop until
        // we have an answer or timeout ourselves
        isc::resolve::makeErrorMessage(answer_message_,
                                       Rcode::SERVFAIL());
        if (!answer_sent_) {
            answer_sent_ = true;
            resolvercallback_->success(answer_message_);
        }
    }

    virtual void stop(bool resume) {
        // if we cancel our timers, we will still get an event for
        // that, so we cannot delete ourselves just yet (those events
        // would be bound to a deleted object)
        // cancel them one by one, both cancels should get us back
        // here again.
        // same goes if we have an outstanding query (can't delete
        // until that one comes back to us)
        done_ = true;
        if (resume && !answer_sent_) {
            answer_sent_ = true;

            // There are two types of messages we could store in the
            // cache;
            // 1. answers to our fetches from authoritative servers,
            //    exactly as we receive them, and
            // 2. answers to queries we received from clients, which
            //    have received additional processing (following CNAME
            //    chains, for instance)
            //
            // Doing only the first would mean we would have to re-do
            // processing when we get data from our cache, and doing
            // only the second would miss out on the side-effect of
            // having nameserver data in our cache.
            //
            // So right now we do both. Since the cache (currently)
            // stores Messages on their question section only, this
            // does mean that we overwrite the messages we stored in
            // the previous iteration if we are following a delegation.
            cache_.update(*answer_message_);

            resolvercallback_->success(answer_message_);
        } else {
            resolvercallback_->failure();
        }
        if (lookup_timer.cancel() != 0) {
            return;
        }
        if (client_timer.cancel() != 0) {
            return;
        }
        if (queries_out_ > 0) {
            return;
        }
        delete this;
    }

    // This function is used as callback from DNSQuery.
    virtual void operator()(IOFetch::Result result) {
        --queries_out_;
        if (!done_ && result != IOFetch::TIME_OUT) {
            // we got an answer
            Message incoming(Message::PARSE);
            InputBuffer ibuf(buffer_->getData(), buffer_->getLength());
            incoming.fromWire(ibuf);

            if (upstream_->size() == 0 &&
                incoming.getRcode() == Rcode::NOERROR()) {
                done_ = handleRecursiveAnswer(incoming);
            } else {
                isc::resolve::copyResponseMessage(incoming, answer_message_);
                done_ = true;
            }
            
            if (done_) {
                stop(true);
            }
        } else if (!done_ && retries_--) {
            // We timed out, but we have some retries, so send again
            dlog("Timeout, resending query");
            send();
        } else {
            // out of retries, give up for now
            stop(false);
        }
    }
};

}

void
RecursiveQuery::resolve(const QuestionPtr& question,
    const isc::resolve::ResolverInterface::CallbackPtr callback)
{
    IOService& io = dns_service_.getIOService();

    MessagePtr answer_message(new Message(Message::RENDER));
    isc::resolve::initResponseMessage(*question, *answer_message);

    OutputBufferPtr buffer(new OutputBuffer(0));

    dlog("Try out cache first (direct call to resolve)");
    // First try to see if we have something cached in the messagecache
    if (cache_.lookup(question->getName(), question->getType(),
                      question->getClass(), *answer_message)) {
        dlog("Message found in cache, returning that");
        // TODO: err, should cache set rcode as well?
        answer_message->setRcode(Rcode::NOERROR());
        callback->success(answer_message);
    } else {
        dlog("Message not found in cache, starting recursive query");
        // It will delete itself when it is done
        new RunningQuery(io, *question, answer_message, upstream_,
                         upstream_root_, test_server_,
                         buffer, callback, query_timeout_,
                         client_timeout_, lookup_timeout_, retries_,
                         cache_);
    }
}

void
RecursiveQuery::resolve(const Question& question,
                        MessagePtr answer_message,
                        OutputBufferPtr buffer,
                        DNSServer* server)
{
    // XXX: eventually we will need to be able to determine whether
    // the message should be sent via TCP or UDP, or sent initially via
    // UDP and then fall back to TCP on failure, but for the moment
    // we're only going to handle UDP.
    IOService& io = dns_service_.getIOService();

    isc::resolve::ResolverInterface::CallbackPtr crs(
        new isc::resolve::ResolverCallbackServer(server));

    // TODO: general 'prepareinitialanswer'
    answer_message->setOpcode(isc::dns::Opcode::QUERY());
    answer_message->addQuestion(question);
    
    // First try to see if we have something cached in the messagecache
    dlog("Try out cache first (started by incoming event)");
    if (cache_.lookup(question.getName(), question.getType(),
                      question.getClass(), *answer_message)) {
        dlog("Message found in cache, returning that");
        // TODO: err, should cache set rcode as well?
        answer_message->setRcode(Rcode::NOERROR());
        crs->success(answer_message);
    } else {
        dlog("Message not found in cache, starting recursive query");
        // It will delete itself when it is done
        new RunningQuery(io, question, answer_message, upstream_, upstream_root_,
                         test_server_,
                         buffer, crs, query_timeout_, client_timeout_,
                         lookup_timeout_, retries_, cache_);
    }
}



} // namespace asiolink
