// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <cstdlib> // For rand(), temporary until better forwarding is done

#include <unistd.h>             // for some IPC/network system calls
#include <sys/socket.h>
#include <netinet/in.h>

#include <vector>
#include <asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <boost/shared_ptr.hpp>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/rcode.h>

#include <asiolink/asiolink.h>
#include <asiolink/internal/tcpdns.h>
#include <asiolink/internal/udpdns.h>

#include <log/dummylog.h>


using namespace asio;
using asio::ip::udp;
using asio::ip::tcp;

using namespace std;
using namespace isc::dns;
using isc::log::dlog;
using namespace boost;

// Is this something we can use in libdns++?
namespace {
    class SectionInserter {
    public:
        SectionInserter(MessagePtr message, const Message::Section sect) :
            message_(message), section_(sect)
        {}
        void operator()(const RRsetPtr rrset) {
            //dlog("Adding RRSet to message section " +
            //    boost::lexical_cast<string>(section_));
            message_->addRRset(section_, rrset, true);
        }
        MessagePtr message_;
        const Message::Section section_;
    };


    /// \brief Copies the parts relevant for a DNS answer to the
    /// target message
    ///
    /// This adds all the RRsets in the answer, authority and
    /// additional sections to the target, as well as the response
    /// code
    void copyAnswerMessage(const Message& source, MessagePtr target) {
        target->setRcode(source.getRcode());

        for_each(source.beginSection(Message::SECTION_ANSWER),
                 source.endSection(Message::SECTION_ANSWER),
                 SectionInserter(target, Message::SECTION_ANSWER));
        for_each(source.beginSection(Message::SECTION_AUTHORITY),
                 source.endSection(Message::SECTION_AUTHORITY),
                 SectionInserter(target, Message::SECTION_AUTHORITY));
        for_each(source.beginSection(Message::SECTION_ADDITIONAL),
                 source.endSection(Message::SECTION_ADDITIONAL),
                 SectionInserter(target, Message::SECTION_ADDITIONAL));
    }
}

namespace asiolink {

typedef pair<string, uint16_t> addr_t;

class IOServiceImpl {
private:
    IOServiceImpl(const IOService& source);
    IOServiceImpl& operator=(const IOService& source);
public:
    /// \brief The constructor
    IOServiceImpl() :
        io_service_(),
        work_(io_service_)
    {};
    /// \brief The destructor.
    ~IOServiceImpl() {};
    //@}

    /// \brief Start the underlying event loop.
    ///
    /// This method does not return control to the caller until
    /// the \c stop() method is called via some handler.
    void run() { io_service_.run(); };

    /// \brief Run the underlying event loop for a single event.
    ///
    /// This method return control to the caller as soon as the
    /// first handler has completed.  (If no handlers are ready when
    /// it is run, it will block until one is.)
    void run_one() { io_service_.run_one();} ;

    /// \brief Stop the underlying event loop.
    ///
    /// This will return the control to the caller of the \c run() method.
    void stop() { io_service_.stop();} ;

    /// \brief Return the native \c io_service object used in this wrapper.
    ///
    /// This is a short term work around to support other BIND 10 modules
    /// that share the same \c io_service with the authoritative server.
    /// It will eventually be removed once the wrapper interface is
    /// generalized.
    asio::io_service& get_io_service() { return io_service_; };
private:
    asio::io_service io_service_;
    asio::io_service::work work_;
};

IOService::IOService() {
    io_impl_ = new IOServiceImpl();
}

IOService::~IOService() {
    delete io_impl_;
}

void
IOService::run() {
    io_impl_->run();
}

void
IOService::run_one() {
    io_impl_->run_one();
}

void
IOService::stop() {
    io_impl_->stop();
}

asio::io_service&
IOService::get_io_service() {
    return (io_impl_->get_io_service());
}

class DNSServiceImpl {
public:
    DNSServiceImpl(IOService& io_service, const char& port,
                  const ip::address* v4addr, const ip::address* v6addr,
                  SimpleCallback* checkin, DNSLookup* lookup,
                  DNSAnswer* answer);

    IOService& io_service_;

    typedef boost::shared_ptr<UDPServer> UDPServerPtr;
    typedef boost::shared_ptr<TCPServer> TCPServerPtr;
    typedef boost::shared_ptr<DNSServer> DNSServerPtr;
    vector<DNSServerPtr> servers_;
    SimpleCallback *checkin_;
    DNSLookup *lookup_;
    DNSAnswer *answer_;

    void addServer(uint16_t port, const ip::address& address) {
        try {
            dlog(std::string("Initialize TCP server at ") + address.to_string() + ":" + boost::lexical_cast<string>(port));
            TCPServerPtr tcpServer(new TCPServer(io_service_.get_io_service(),
                address, port, checkin_, lookup_, answer_));
            (*tcpServer)();
            servers_.push_back(tcpServer);
            dlog(std::string("Initialize UDP server at ") + address.to_string() + ":" + boost::lexical_cast<string>(port));
            UDPServerPtr udpServer(new UDPServer(io_service_.get_io_service(),
                address, port, checkin_, lookup_, answer_));
            (*udpServer)();
            servers_.push_back(udpServer);
        }
        catch (const asio::system_error& err) {
            // We need to catch and convert any ASIO level exceptions.
            // This can happen for unavailable address, binding a privilege port
            // without the privilege, etc.
            isc_throw(IOError, "Failed to initialize network servers: " <<
                      err.what());
        }
    }
    void addServer(const char& port, const ip::address& address) {
        uint16_t portnum;
        try {
            // XXX: SunStudio with stlport4 doesn't reject some invalid
            // representation such as "-1" by lexical_cast<uint16_t>, so
            // we convert it into a signed integer of a larger size and perform
            // range check ourselves.
            const int32_t portnum32 = boost::lexical_cast<int32_t>(&port);
            if (portnum32 < 0 || portnum32 > 65535) {
                isc_throw(IOError, "Invalid port number '" << &port);
            }
            portnum = portnum32;
        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(IOError, "Invalid port number '" << &port << "': " <<
                      ex.what());
        }
        addServer(portnum, address);
    }
};

DNSServiceImpl::DNSServiceImpl(IOService& io_service,
                               const char& port,
                               const ip::address* const v4addr,
                               const ip::address* const v6addr,
                               SimpleCallback* checkin,
                               DNSLookup* lookup,
                               DNSAnswer* answer) :
    io_service_(io_service),
    checkin_(checkin),
    lookup_(lookup),
    answer_(answer)
{

    if (v4addr) {
        addServer(port, *v4addr);
    }
    if (v6addr) {
        addServer(port, *v6addr);
    }
}

DNSService::DNSService(IOService& io_service,
                       const char& port, const char& address,
                       SimpleCallback* checkin,
                       DNSLookup* lookup,
                       DNSAnswer* answer) :
    impl_(new DNSServiceImpl(io_service, port, NULL, NULL, checkin, lookup,
        answer)), io_service_(io_service)
{
    addServer(port, &address);
}

DNSService::DNSService(IOService& io_service,
                       const char& port,
                       const bool use_ipv4, const bool use_ipv6,
                       SimpleCallback* checkin,
                       DNSLookup* lookup,
                       DNSAnswer* answer) :
    impl_(NULL), io_service_(io_service)
{
    const ip::address v4addr_any = ip::address(ip::address_v4::any());
    const ip::address* const v4addrp = use_ipv4 ? &v4addr_any : NULL; 
    const ip::address v6addr_any = ip::address(ip::address_v6::any());
    const ip::address* const v6addrp = use_ipv6 ? &v6addr_any : NULL;
    impl_ = new DNSServiceImpl(io_service, port, v4addrp, v6addrp, checkin, lookup, answer);
}

DNSService::DNSService(IOService& io_service, SimpleCallback* checkin,
    DNSLookup* lookup, DNSAnswer *answer) :
    impl_(new DNSServiceImpl(io_service, *"0", NULL, NULL, checkin, lookup,
        answer)), io_service_(io_service)
{
}

DNSService::~DNSService() {
    delete impl_;
}

namespace {

typedef std::vector<std::pair<std::string, uint16_t> > AddressVector;

}

RecursiveQuery::RecursiveQuery(DNSService& dns_service,
    const AddressVector& upstream, int timeout, unsigned retries) :
    dns_service_(dns_service), upstream_(new AddressVector(upstream)),
    timeout_(timeout), retries_(retries)
{}

namespace {

ip::address
convertAddr(const string& address) {
    error_code err;
    ip::address addr = ip::address::from_string(address, err);
    if (err) {
        isc_throw(IOError, "Invalid IP address '" << &address << "': "
            << err.message());
    }
    return (addr);
}

}

void
DNSService::addServer(const char& port, const string& address) {
    impl_->addServer(port, convertAddr(address));
}

void
DNSService::addServer(uint16_t port, const string& address) {
    impl_->addServer(port, convertAddr(address));
}

void
DNSService::clearServers() {
    // FIXME: This does not work, it does not close the socket.
    // How is it done?
    impl_->servers_.clear();
}

namespace {

/*
 * This is a query in progress. When a new query is made, this one holds
 * the context information about it, like how many times we are allowed
 * to retry on failure, what to do when we succeed, etc.
 *
 * Used by RecursiveQuery::sendQuery.
 */
class RunningQuery : public UDPQuery::Callback {
private:
    // The io service to handle async calls
    asio::io_service& io_;

    // Info for (re)sending the query (the question and destination)
    Question question_;

    // This is where we build and store our final answer
    MessagePtr answer_message_;

    // currently we use upstream as the current list of NS records
    // we should differentiate between forwarding and resolving
    shared_ptr<AddressVector> upstream_;

    // Buffer to store the result.
    OutputBufferPtr buffer_;

    // Server to notify when we succeed or fail
    shared_ptr<DNSServer> server_;

    /*
     * TODO Do something more clever with timeouts. In the long term, some
     *     computation of average RTT, increase with each retry, etc.
     */
    // Timeout information
    int timeout_;
    unsigned retries_;

    // normal query state

    // if we change this to running and add a sent, we can do
    // decoupled timeouts i think
    bool done;

    // Not using NSAS at this moment, so we keep a list
    // of 'current' zone servers
    vector<addr_t> zone_servers_;

    // Update the question that will be sent to the server
    void setQuestion(const Question& new_question) {
        question_ = new_question;
    }

    // (re)send the query to the server.
    void send() {
        const int uc = upstream_->size();
        const int zs = zone_servers_.size();
        buffer_->clear();
        if (uc > 0) {
            int serverIndex = rand() % uc;
            dlog("Sending upstream query (" + question_.toText() +
                ") to " + upstream_->at(serverIndex).first);
            UDPQuery query(io_, question_,
                upstream_->at(serverIndex).first,
                upstream_->at(serverIndex).second, buffer_, this,
                timeout_);
            io_.post(query);
        } else if (zs > 0) {
            int serverIndex = rand() % zs;
            dlog("Sending query to zone server (" + question_.toText() +
                ") to " + zone_servers_.at(serverIndex).first);
            UDPQuery query(io_, question_,
                zone_servers_.at(serverIndex).first,
                zone_servers_.at(serverIndex).second, buffer_, this,
                timeout_);
            io_.post(query);
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
    // returns true if we are done
    // returns false if we are not done
    bool handleRecursiveAnswer(const Message& incoming) {
        if (incoming.getRRCount(Message::SECTION_ANSWER) > 0) {
            dlog("[XX] this looks like the final result");
            copyAnswerMessage(incoming, answer_message_);
            return true;
        } else {
            dlog("[XX] this looks like a delegation");
            // ok we need to do some more processing.
            // the ns list should contain all nameservers
            // while the additional may contain addresses for
            // them.
            // this needs to tie into NSAS of course
            // for this very first mockup, hope there is an
            // address in additional and just use that

            // send query to the addresses in the delegation
            bool found_ns_address = false;
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
                        
                        // should use NSAS
                        zone_servers_.push_back(addr_t(addr_str, 53));
                        found_ns_address = true;
                    }
                }
            }
            if (found_ns_address) {
                // next resolver round
                send();
                return false;
            } else {
                dlog("[XX] no ready-made addresses in additional. need nsas.");
                // this will result in answering with the delegation. oh well
                copyAnswerMessage(incoming, answer_message_);
                return true;
            }
        }
    }
    

public:
    RunningQuery(asio::io_service& io, const Question &question,
        MessagePtr answer_message, shared_ptr<AddressVector> upstream,
        OutputBufferPtr buffer, DNSServer* server, int timeout,
        unsigned retries) :
        io_(io),
        question_(question),
        answer_message_(answer_message),
        upstream_(upstream),
        buffer_(buffer),
        server_(server->clone()),
        timeout_(timeout),
        retries_(retries),
        zone_servers_()
    {
        dlog("[XX] Started a new RunningQuery");
        done = false;

        dlog("[XX] zone_servers size: " + zone_servers_.size());
        // hardcoded f.root-servers.net now, should use NSAS
        if (upstream_->empty()) {
            zone_servers_.push_back(addr_t("192.5.5.241", 53));
        }
        send();
    }


    // This function is used as callback from DNSQuery.
    virtual void operator()(UDPQuery::Result result) {
        dlog("[XX] RunningQuery operator() called with result: " + result);
        // XXX is this the place for TCP retry?
        if (result != UDPQuery::TIME_OUT) {
            // we got an answer
            std::cout << "[XX] for question: " << question_.toText() << std::endl;
            Message incoming(Message::PARSE);
            InputBuffer ibuf(buffer_->getData(), buffer_->getLength());
            incoming.fromWire(ibuf);
            std::cout << "[XX] received answer: " << incoming.toText() << std::endl;

            if (upstream_->size() == 0 &&
                incoming.getRcode() == Rcode::NOERROR()) {
                done = handleRecursiveAnswer(incoming);
            } else {
                copyAnswerMessage(incoming, answer_message_);
                done = true;
            }
            
            if (done) {
                std::cerr << "[XX] Done, returning to server" << std::endl;
                server_->resume(result == UDPQuery::SUCCESS);
                delete this;
            }
        } else if (retries_--) {
            dlog("Resending query");
            // We timed out, but we have some retries, so send again
            send();
        } else {
            // out of retries, give up for now
            server_->resume(false);
            delete this;
        }
    }
};

}

void
RecursiveQuery::sendQuery(const Question& question,
                          MessagePtr answer_message,
                          OutputBufferPtr buffer,
                          DNSServer* server)
{
    // XXX: eventually we will need to be able to determine whether
    // the message should be sent via TCP or UDP, or sent initially via
    // UDP and then fall back to TCP on failure, but for the moment
    // we're only going to handle UDP.
    asio::io_service& io = dns_service_.get_io_service();
    // It will delete itself when it is done
    new RunningQuery(io, question, answer_message, upstream_, buffer,
                     server, timeout_, retries_);
}

class IntervalTimerImpl {
private:
    // prohibit copy
    IntervalTimerImpl(const IntervalTimerImpl& source);
    IntervalTimerImpl& operator=(const IntervalTimerImpl& source);
public:
    IntervalTimerImpl(IOService& io_service);
    ~IntervalTimerImpl();
    void setupTimer(const IntervalTimer::Callback& cbfunc,
                    const uint32_t interval);
    void callback(const asio::error_code& error);
private:
    // a function to update timer_ when it expires
    void updateTimer();
    // a function to call back when timer_ expires
    IntervalTimer::Callback cbfunc_;
    // interval in seconds
    uint32_t interval_;
    // asio timer
    asio::deadline_timer timer_;
};

IntervalTimerImpl::IntervalTimerImpl(IOService& io_service) :
    timer_(io_service.get_io_service())
{}

IntervalTimerImpl::~IntervalTimerImpl()
{}

void
IntervalTimerImpl::setupTimer(const IntervalTimer::Callback& cbfunc,
                              const uint32_t interval)
{
    // Interval should not be 0.
    if (interval == 0) {
        isc_throw(isc::BadValue, "Interval should not be 0");
    }
    // Call back function should not be empty.
    if (cbfunc.empty()) {
        isc_throw(isc::InvalidParameter, "Callback function is empty");
    }
    cbfunc_ = cbfunc;
    interval_ = interval;
    // Set initial expire time.
    // At this point the timer is not running yet and will not expire.
    // After calling IOService::run(), the timer will expire.
    updateTimer();
    return;
}

void
IntervalTimerImpl::updateTimer() {
    try {
        // Update expire time to (current time + interval_).
        timer_.expires_from_now(boost::posix_time::seconds(interval_));
    } catch (const asio::system_error& e) {
        isc_throw(isc::Unexpected, "Failed to update timer");
    }
    // Reset timer.
    timer_.async_wait(boost::bind(&IntervalTimerImpl::callback, this, _1));
}

void
IntervalTimerImpl::callback(const asio::error_code& cancelled) {
    // Do not call cbfunc_ in case the timer was cancelled.
    // The timer will be canelled in the destructor of asio::deadline_timer.
    if (!cancelled) {
        cbfunc_();
        // Set next expire time.
        updateTimer();
    }
}

IntervalTimer::IntervalTimer(IOService& io_service) {
    impl_ = new IntervalTimerImpl(io_service);
}

IntervalTimer::~IntervalTimer() {
    delete impl_;
}

void
IntervalTimer::setupTimer(const Callback& cbfunc, const uint32_t interval) {
    return (impl_->setupTimer(cbfunc, interval));
}

}
