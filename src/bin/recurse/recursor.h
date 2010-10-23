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

#ifndef __RECURSOR_H
#define __RECURSOR_H 1

#include <string>
#include <vector>
#include <utility>

#include <cc/data.h>
#include <config/ccsession.h>

#include <asiolink/asiolink.h>

class RecursorImpl;

class Recursor {
    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private.
    //@{
private:
    Recursor(const Recursor& source);
    Recursor& operator=(const Recursor& source);
public:
    /// The constructor.
    Recursor();
    ~Recursor();
    //@}

    /// \brief Process an incoming DNS message, then signal 'server' to resume 
    ///
    /// A DNS query (or other message) has been received by a \c DNSServer
    /// object.  Find an answer, then post the \c DNSServer object on the
    /// I/O service queue and return.  When the server resumes, it can
    /// send the reply.
    ///
    /// \param io_message The I/O service queue
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
    void setVerbose(bool on);

    /// \brief Get the current value of the verbose flag
    bool getVerbose() const;

    /// \brief Set and get the config session
    isc::config::ModuleCCSession* getConfigSession() const;
    void setConfigSession(isc::config::ModuleCCSession* config_session);

    /// \brief Handle commands from the config session
    isc::data::ConstElementPtr updateConfig(isc::data::ConstElementPtr config);

    /// \brief Assign an ASIO IO Service queue to this Recursor object
    void setIOService(asiolink::IOService& ios);

    /// \brief Return this object's ASIO IO Service queue
    asiolink::IOService& getIOService() const { return (*io_); }

    /// \brief Return pointer to the DNS Lookup callback function
    asiolink::DNSLookup* getDNSLookupProvider() { return (dns_lookup_); }

    /// \brief Return pointer to the DNS Answer callback function
    asiolink::DNSAnswer* getDNSAnswerProvider() { return (dns_answer_); }

    /// \brief Return pointer to the Checkin callback function
    asiolink::SimpleCallback* getCheckinProvider() { return (checkin_); }

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
     * Set and get the addresses we listen on.
     */
    void setListenAddresses(const std::vector<std::pair<std::string,
        uint16_t> >& addresses);
    std::vector<std::pair<std::string, uint16_t> > getListenAddresses() const;

private:
    RecursorImpl* impl_;
    asiolink::IOService* io_;
    asiolink::SimpleCallback* checkin_;
    asiolink::DNSLookup* dns_lookup_;
    asiolink::DNSAnswer* dns_answer_;
};

#endif // __RECURSOR_H

// Local Variables: 
// mode: c++
// End: 
