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

#ifndef __ASIOLINK_H
#define __ASIOLINK_H 1

// IMPORTANT NOTE: only very few ASIO headers files can be included in
// this file.  In particular, asio.hpp should never be included here.
// See the description of the namespace below.
#include <unistd.h>             // for some network system calls
#include <asio/ip/address.hpp>

#include <functional>
#include <string>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/question.h>

#include <exceptions/exceptions.h>

#include <asiolink/ioaddress.h>
#include <asiolink/ioendpoint.h>
#include <asiolink/iomessage.h>
#include <asiolink/iosocket.h>

namespace asio {
// forward declaration for IOService::get_io_service() below
class io_service;
}

/// \namespace asiolink
/// \brief A wrapper interface for the ASIO library.
///
/// The \c asiolink namespace is used to define a set of wrapper interfaces
/// for the ASIO library.
///
/// BIND 10 uses the non-Boost version of ASIO because it's header-only,
/// i.e., does not require a separate library object to be linked, and thus
/// lowers the bar for introduction.
///
/// But the advantage comes with its own costs: since the header-only version
/// includes more definitions in public header files, it tends to trigger
/// more compiler warnings for our own sources, and, depending on the
/// compiler options, may make the build fail.
///
/// We also found it may be tricky to use ASIO and standard C++ libraries
/// in a single translation unit, i.e., a .cc file: depending on the order
/// of including header files, ASIO may or may not work on some platforms.
///
/// This wrapper interface is intended to centralize these
/// problematic issues in a single sub module.  Other BIND 10 modules should
/// simply include \c asiolink.h and use the wrapper API instead of
/// including ASIO header files and using ASIO-specific classes directly.
///
/// This wrapper may be used for other IO libraries if and when we want to
/// switch, but generality for that purpose is not the primary goal of
/// this module.  The resulting interfaces are thus straightforward mapping
/// to the ASIO counterparts.
///
/// Notes to developers:
/// Currently the wrapper interface is fairly specific to use by a
/// DNS server, i.e., b10-auth or b10-recurse.  But the plan is to
/// generalize it and have other modules use it as well.
///
/// One obvious drawback of this approach is performance overhead
/// due to the additional layer.  We should eventually evaluate the cost
/// of the wrapper abstraction in benchmark tests. Another drawback is
/// that the wrapper interfaces don't provide all features of ASIO
/// (at least for the moment).  We should also re-evaluate the
/// maintenance overhead of providing necessary wrappers as we develop
/// more.
///
/// On the other hand, we may be able to exploit the wrapper approach to
/// simplify the interfaces (by limiting the usage) and unify performance
/// optimization points.
///
/// As for optimization, we may want to provide a custom allocator for
/// the placeholder of callback handlers:
/// http://think-async.com/Asio/asio-1.3.1/doc/asio/reference/asio_handler_allocate.html

namespace asiolink {
struct IOServiceImpl;

/// \brief An exception that is thrown if an error occurs within the IO
/// module.  This is mainly intended to be a wrapper exception class for
/// ASIO specific exceptions.
class IOError : public isc::Exception {
public:
    IOError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// \brief Forward declarations for classes used below
class SimpleCallback;
class DNSLookup;
class DNSAnswer;

/// \brief The \c IOService class is a wrapper for the ASIO \c io_service
/// class.
///
/// Currently, the interface of this class is very specific to the
/// authoritative/recursive DNS server implementationss in b10-auth
/// and b10-recurse; this is reflected in the constructor signatures.
/// Ultimately the plan is to generalize it so that other BIND 10
/// modules can use this interface, too.
class IOService {
    ///
    /// \name Constructors and Destructor
    ///
    /// These are currently very specific to the authoritative server
    /// implementation.
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    IOService(const IOService& source);
    IOService& operator=(const IOService& source);
public:
    /// \brief The constructor with a specific IP address and port on which
    /// the services listen on.
    IOService(const char& port, const char& address,
              SimpleCallback* checkin,
              DNSLookup* lookup,
              DNSAnswer* answer);
    /// \brief The constructor with a specific port on which the services
    /// listen on.
    ///
    /// It effectively listens on "any" IPv4 and/or IPv6 addresses.
    /// IPv4/IPv6 services will be available if and only if \c use_ipv4
    /// or \c use_ipv6 is \c true, respectively.
    IOService(const char& port, const bool use_ipv4, const bool use_ipv6,
              SimpleCallback* checkin,
              DNSLookup* lookup,
              DNSAnswer* answer);
    /// \brief The destructor.
    ~IOService();
    //@}

    /// \brief Start the underlying event loop.
    ///
    /// This method does not return control to the caller until
    /// the \c stop() method is called via some handler.
    void run();

    /// \brief Run the underlying event loop for a single event.
    ///
    /// This method return control to the caller as soon as the
    /// first handler has completed.  (If no handlers are ready when
    /// it is run, it will block until one is.)
    void run_one();

    /// \brief Stop the underlying event loop.
    ///
    /// This will return the control to the caller of the \c run() method.
    void stop();

    /// \brief Return the native \c io_service object used in this wrapper.
    ///
    /// This is a short term work around to support other BIND 10 modules
    /// that share the same \c io_service with the authoritative server.
    /// It will eventually be removed once the wrapper interface is
    /// generalized.
    asio::io_service& get_io_service();
private:
    IOServiceImpl* impl_;
};

/// \brief The \c DNSServer class is a wrapper (and base class) for
/// classes which provide DNS server functionality.
/// 
/// The classes derived from this one, \c TCPServer and \c UDPServer,
/// act as the interface layer between clients sending queries, and
/// functions defined elsewhere that provide answers to those queries.
/// Those functions are described in more detail below under
/// \c SimpleCallback, \c DNSLookup, and \c DNSAnswer.
///
/// Notes to developers:
/// When constructed, this class (and its derived classes) will have its
/// "self_" member set to point to "this".  Calls to methods in the base
/// class are then rerouted via this pointer to methods in the derived
/// class.  This allows code from outside asiolink, with no specific
/// knowledge of \c TCPServer or \c UDPServer, to access their methods.
///
/// This class is both assignable and copy-constructable.  Its subclasses
/// use the "stackless coroutine" pattern, meaning that it will copy itself
/// when "forking", and that instances will be posted as ASIO handler
/// objects, which are always copied.
///
/// Because these objects are frequently copied, it is recommended 
/// that derived classes be kept small to reduce copy overhead.
class DNSServer {
protected: 
    ///
    /// \name Constructors and destructors
    ///
    /// This is intentionally defined as \c protected, as this base class
    /// should never be instantiated except as part of a derived class.
    //@{
    DNSServer() : self_(this) {}
public:
    /// \brief The destructor
    virtual ~DNSServer() {}
    //@}

    ///
    /// \name Class methods
    ///
    /// These methods all make their calls indirectly via the "self_"
    /// pointer, ensuring that the functions ultimately invoked will be
    /// the ones in the derived class.
    ///
    //@{
    /// \brief The funtion operator
    virtual void operator()(asio::error_code ec = asio::error_code(),
                            size_t length = 0)
    {
        (*self_)(ec, length);
    }

    /// \brief Resume processing of the server coroutine after an 
    /// asynchronous call (e.g., to the DNS Lookup provider) has completed.
    virtual inline void resume(const bool done) { self_->resume(done); }

    /// \brief Indicate whether the server is able to send an answer
    /// to a query.
    /// 
    /// This is presently used only for testing purposes.
    virtual inline bool hasAnswer() { return (self_->hasAnswer()); }

    /// \brief Returns the current value of the 'coroutine' object
    ///
    /// This is a temporary method, intended to be used for debugging
    /// purposes during development and removed later.  It allows
    /// callers from outside the coroutine object to retrieve information
    /// about its current state.
    virtual inline int value() { return (self_->value()); }

    /// \brief Returns a pointer to a clone of this DNSServer object.
    ///
    /// When a \c DNSServer object is copied or assigned, the result will
    /// normally be another \c DNSServer object containing a copy
    /// of the original "self_" pointer.  Calling clone() guarantees
    /// that the underlying object is also correctly copied.
    virtual inline DNSServer* clone() { return (self_->clone()); }
    //@}

protected:
    /// \brief Lookup handler object.
    ///
    /// This is a protected class; it can only be instantiated
    /// from within a derived class of \c DNSServer.
    ///
    /// A server object that has received a query creates an instance
    /// of this class and scheudles it on the ASIO service queue
    /// using asio::io_service::post().  When the handler executes, it
    /// calls the asyncLookup() method in the server object to start a
    /// DNS lookup.  When the lookup is complete, the server object is
    /// scheduled to resume, again using io_service::post().
    ///
    /// Note that the calling object is copied into the handler object,
    /// not referenced.  This is because, once the calling object yields
    /// control to the handler, it falls out of scope and may disappear
    template <typename T>
    class AsyncLookup {
    public:
        AsyncLookup(T caller) : caller_(caller) {}
        inline void operator()() { caller_.asyncLookup(); }
    private:
        T caller_;
    };

    /// \brief Carries out a DNS lookup.
    ///
    /// This function calls the \c DNSLookup object specified by the
    /// DNS server when the \c IOService was created, passing along
    /// the details of the query and a pointer back to the current
    /// server object.  It is called asynchronously via the AsyncLookup
    /// handler class.
    virtual inline void asyncLookup() { self_->asyncLookup(); }

private:
    DNSServer* self_;
};

/// \brief The \c DNSLookup class is an abstract base class for a DNS
/// Lookup provider function.
///
/// Specific derived class implementations are hidden within the
/// implementation.  Instances of the derived classes can be called
/// as functions via the operator() interface.  Pointers to these
/// instances can then be provided to the \c IOService class
/// via its constructor.
///
/// A DNS Lookup provider function obtains the data needed to answer
/// a DNS query (e.g., from authoritative data source, cache, or upstream
/// query).  After it has run, the OutputBuffer object passed to it
/// should contain the answer to the query, in an internal representation.
class DNSLookup {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    DNSLookup(const DNSLookup& source);
    DNSLookup& operator=(const DNSLookup& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class
    /// should never be instantiated (except as part of a derived class).
    DNSLookup() : self_(this) {}
public:
    /// \brief The destructor
    virtual ~DNSLookup() {}
    //@}
    /// \brief The function operator
    ///
    /// This makes its call indirectly via the "self" pointer, ensuring
    /// that the function ultimately invoked will be the one in the derived
    /// class.
    virtual void operator()(const IOMessage& io_message,
                            isc::dns::MessagePtr message,
                            isc::dns::OutputBufferPtr buffer,
                            DNSServer* server) const
    {
        (*self_)(io_message, message, buffer, server);
    }
private:
    DNSLookup* self_;
};

/// \brief The \c DNSAnswer class is an abstract base class for a DNS
/// Answer provider function.
///
/// Specific derived class implementations are hidden within the
/// implementation.  Instances of the derived classes can be called
/// as functions via the operator() interface.  Pointers to these
/// instances can then be provided to the \c IOService class
/// via its constructor.
///
/// A DNS Answer provider function takes answer data that has been obtained
/// from a DNS Lookup provider functon and readies it to be sent to the
/// client.  After it has run, the OutputBuffer object passed to it should
/// contain the answer to the query rendered into wire format.
class DNSAnswer {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    DNSAnswer(const DNSAnswer& source);
    DNSAnswer& operator=(const DNSAnswer& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class
    /// should never be instantiated (except as part of a derived class).
    DNSAnswer() {}
public:
    /// \brief The destructor
    virtual ~DNSAnswer() {}
    //@}
    /// \brief The function operator
    virtual void operator()(const IOMessage& io_message,
                            isc::dns::MessagePtr message,
                            isc::dns::OutputBufferPtr buffer) const = 0;
};

/// \brief The \c SimpleCallback class is an abstract base class for a
/// simple callback function with the signature:
///
/// Specific derived class implementations are hidden within the
/// implementation.  Instances of the derived classes can be called
/// as functions via the operator() interface.  Pointers to these
/// instances can then be provided to the \c IOService class
/// via its constructor.
///
/// The \c SimpleCallback is expected to be used for basic, generic
/// tasks such as checking for configuration changes.  It may also be
/// used for testing purposes.
class SimpleCallback {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    SimpleCallback(const SimpleCallback& source);
    SimpleCallback& operator=(const SimpleCallback& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class
    /// should never be instantiated (except as part of a derived class).
    SimpleCallback() : self_(this) {}
public:
    /// \brief The destructor
    virtual ~SimpleCallback() {}
    /// \brief The function operator
    //@}
    ///
    /// This makes its call indirectly via the "self" pointer, ensuring
    /// that the function ultimately invoked will be the one in the derived
    /// class.
    virtual void operator()(const IOMessage& io_message) const {
        (*self_)(io_message);
    }
private:
    SimpleCallback* self_;
};

/// \brief The \c RecursiveQuery class provides a layer of abstraction around
/// the ASIO code that carries out an upstream query.
///
/// This design is very preliminary; currently it is only capable of
/// handling simple forward requests to a single resolver.
class RecursiveQuery {
    ///
    /// \name Constructors
    ///
    //@{
public:
    /// \brief Constructor for use when acting as a forwarder
    ///
    /// This is currently the only way to construct \c RecursiveQuery
    /// object.  The address of the forward nameserver is specified,
    /// and all upstream queries will be sent to that one address.
    RecursiveQuery(IOService& io_service, const char& forward,
                   uint16_t port = 53);
    //@}

    /// \brief Initiates an upstream query in the \c RecursiveQuery object.
    ///
    /// \param question The question being answered <qname/qclass/qtype>
    /// \param buffer An output buffer into which the response can be copied
    /// \param server A pointer to the \c DNSServer object handling the client
    ///
    /// When sendQuery() is called, a message is sent asynchronously to
    /// the upstream name server.  When a reply arrives, 'server'
    /// is placed on the ASIO service queue via io_service::post(), so
    /// that the original \c DNSServer objct can resume processing.
    void sendQuery(const isc::dns::Question& question,
                   isc::dns::OutputBufferPtr buffer,
                   DNSServer* server);
private:
    IOService& io_service_;
    asio::ip::address ns_addr_;
    uint16_t port_;
};

}      // asiolink
#endif // __ASIOLINK_H

// Local Variables: 
// mode: c++
// End: 
