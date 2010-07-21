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

#ifndef _XFROUT_CLIENT_H
#define _XFROUT_CLIENT_H

#include <stdint.h>

#include <string>

#include <exceptions/exceptions.h>

namespace isc {
namespace xfr {

struct XfroutClientImpl;

class XfroutError: public Exception {
public:
    XfroutError(const char *file, size_t line, const char *what):
        isc::Exception(file, line, what) {}
};

/// \brief The AbstractXfroutClient class is an abstract base class that
/// defines the interfaces of XfroutClient.
///
/// The intended primary usage of abstraction is to allow tests for the
/// user class of XfroutClient without requiring actual communication.
class AbstractXfroutClient {
    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private to make it explicit that this is a
    /// pure base class.
    //@{
private:
    AbstractXfroutClient(const AbstractXfroutClient& source);
    AbstractXfroutClient& operator=(const AbstractXfroutClient& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class should
    /// never be instantiated (except as part of a derived class).
    AbstractXfroutClient() {}
public:
    /// \brief The destructor.
    virtual ~AbstractXfroutClient() {}
    //@}
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual int sendXfroutRequestInfo(int tcp_sock, const void* msg_data,
                                      uint16_t msg_len) = 0;
};

class XfroutClient : public AbstractXfroutClient {
public:
    XfroutClient(const std::string& file);
    ~XfroutClient();
private:
    // make this class non copyable
    XfroutClient(const XfroutClient& source);
    XfroutClient& operator=(const XfroutClient& source);
public:
    virtual void connect();
    virtual void disconnect();
    virtual int sendXfroutRequestInfo(int tcp_sock, const void* msg_data,
                                      uint16_t msg_len);
private:
    XfroutClientImpl* impl_;
};

} // End for namespace xfr
} // End for namespace isc

#endif

// Local Variables: 
// mode: c++
// End: 
