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

#ifndef __TSIG_H
#define __TSIG_H 1

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <dns/rdataclass.h>
#include <dns/tsigerror.h>
#include <dns/tsigkey.h>

namespace isc {
namespace dns {
/// TSIG resource record.
///
/// A \c TSIGRecord class object represents a TSIG resource record and is
/// responsible for conversion to and from wire format TSIG record based on
/// the protocol specification (RFC2845).
/// This class is provided so that other classes and applications can handle
/// TSIG without knowing protocol details of TSIG, such as that it uses a
/// fixed constant of TTL.
///
/// \note So the plan is to eventually provide a \c toWire() method and
/// the "from wire" constructor.  They are not yet provided in this initial
/// step.
///
/// \note
/// This class could be a derived class of \c AbstractRRset.  That way
/// it would be able to be used in a polymorphic way; for example,
/// an application can construct a TSIG RR by itself and insert it to a
/// \c Message object as a generic RRset.  On the other hand, it would mean
/// this class would have to implement an \c RdataIterator (even though it
/// can be done via straightforward forwarding) while the iterator is mostly
/// redundant since there should be one and only one RDATA for a valid TSIG
/// RR.  Likewise, some methods such as \c setTTL() method wouldn't be well
/// defined due to such special rules for TSIG as using a fixed TTL.
/// Overall, TSIG is a very special RR type that simply uses the compatible
/// resource record format, and it will be unlikely that a user wants to
/// handle it through a generic interface in a polymorphic way.
/// We therefore chose to define it as a separate class.  This is also
/// similar to why \c EDNS is a separate class.
class TSIGRecord {
public:
    /// Constructor from TSIG RDATA
    ///
    /// \exception std::bad_alloc Resource allocation for copying the RDATA
    /// fails
    explicit TSIGRecord(const rdata::any::TSIG& tsig_rdata) :
        rdata_(tsig_rdata)
    {}

    /// Return the RDATA of the TSIG RR
    ///
    /// \exception None
    const rdata::any::TSIG& getRdata() const { return (rdata_); }

    /// \name Protocol constants and defaults
    ///
    //@{
    /// Return the RR class of TSIG
    ///
    /// TSIG always uses the ANY RR class.  This static method returns it,
    /// when, though unlikely, an application wants to know which class TSIG
    /// is supposed to use.
    ///
    /// \exception None
    static const RRClass& getClass();

    /// The TTL value to be used in TSIG RRs.
    static const uint32_t TSIG_TTL = 0;
    //@}

private:
    const rdata::any::TSIG rdata_;
};

/// A pointer-like type pointing to a \c TSIGRecord object.
typedef boost::shared_ptr<TSIGRecord> TSIGRecordPtr;

/// A pointer-like type pointing to an immutable \c TSIGRecord object.
typedef boost::shared_ptr<const TSIGRecord> ConstTSIGRecordPtr;

/// TSIG session context.
///
/// The \c TSIGContext class maintains a context of a signed session of
/// DNS transactions by TSIG.  In many cases a TSIG signed session consists
/// of a single set of request (e.g. normal query) and reply (e.g. normal
/// response), where the request is initially signed by the client, and the
/// reply is signed by the server using the initial signature.  As mentioned
/// in RFC2845, a session can consist of multiple exchanges in a TCP
/// connection.  As also mentioned in the RFC, an AXFR response often contains
/// multiple DNS messages, which can belong to the same TSIG session.
/// This class supports all these cases.
///
/// A \c TSIGContext object is generally constructed with a TSIG key to be
/// used for the session, and keeps track of various kinds of session specific
/// information, such as the original digest while waiting for a response or
/// verification error information that is to be used for a subsequent
/// response.
///
/// This class has two main methods, \c sign() and \c verify().
/// The \c sign() method signs given data (which is supposed to be a complete
/// DNS message without the TSIG itself) using the TSIG key and other
/// related information associated with the \c TSIGContext object.
/// The \c verify() method verifies a given DNS message that contains a TSIG
/// RR using the key and other internal information.
///
/// In general, a DNS client that wants to send a signed query will construct
/// a \c TSIGContext object with the TSIG key that the client is intending to
/// use, and sign the query with the context.  The client will keeps the
/// context, and verify the response with it.
///
/// On the other hand, a DNS server will construct a \c TSIGContext object
/// with the information of the TSIG RR included in a query with a set of
/// possible keys (in the form of a \c TSIGKeyRing object).  The constructor
/// in this mode will identify the appropriate TSIG key (or internally record
/// an error if it doesn't find a key).  The server will then verify the
/// query with the context, and generate a signed response using the same
/// same context.  (Note: this mode is not yet implemented and may change,
/// see below).
///
/// When multiple messages belong to the same TSIG session, either side
/// (signer or verifier) will keep using the same context.  It records
/// the latest session state (such as the previous digest) so that repeated
/// calls to \c sign() or \c verify() work correctly in terms of the TSIG
/// protocol.
///
/// \note The \c verify() method is not yet implemented.  The implementation
/// and documentation should be updated in the corresponding task.
///
/// <b>TCP Consideration</b>
///
/// RFC2845 describes the case where a single TSIG session is used for
/// multiple DNS messages (Section 4.4).  This class supports signing and
/// verifying the messages in this scenario, but does not care if the messages
/// were delivered over a TCP connection or not.  If, for example, the
/// same \c TSIGContext object is used to sign two independent DNS queries
/// sent over UDP, they will be considered to belong to the same TSIG
/// session, and, as a result, verification will be likely to fail.
///
/// \b Copyability
///
/// This class is currently non copyable based on the observation of the
/// typical usage as described above.  But there is no strong technical
/// reason why this class cannot be copyable.  If we see the need for it
/// in future we may change the implementation on this point.
///
/// <b>Note to developers:</b>
/// One basic design choice is to make the \c TSIGContext class is as
/// independent from the \c Message class.  This is because the latter is
/// much more complicated, depending on many other classes, while TSIG is
/// a very specific part of the entire DNS protocol set.  If the \c TSIGContext
/// class depends on \c \c Message, it will be more vulnerable to changes
/// to other classes, and will be more difficult to test due to the
/// direct or indirect dependencies.  The interface of \c sign() that takes
/// opaque data (instead of, e.g., a \c Message or \c MessageRenderer object)
/// is therefore a deliberate design decision.
class TSIGContext : boost::noncopyable {
public:
    /// Internal state of context
    ///
    /// The constants of this enum type define a specific state of
    /// \c TSIGContext to adjust the behavior.  The definition is public
    /// and the state can be seen via the \c getState() method, but this is
    /// mostly private information.  It's publicly visible mainly for testing
    /// purposes; there is no API for the application to change the state
    /// directly.
    enum State {
        INIT,                   ///< Initial state
        SIGNED,                 ///< Sign completed
        CHECKED ///< Verification completed (may or may not successfully)
    };

    /// \name Constructors and destructor
    ///
    //@{
    /// Constructor from a TSIG key.
    ///
    /// \exception std::bad_alloc Resource allocation for internal data fails
    ///
    /// \param key The TSIG key to be used for TSIG sessions with this context.
    explicit TSIGContext(const TSIGKey& key);

    /// The destructor.
    ~TSIGContext();
    //@}

    /// Sign a DNS message.
    ///
    /// This method computes the TSIG MAC for the given data, which is
    /// generally expected to be a complete, wire-format DNS message
    /// that doesn't contain a TSIG RR, based on the TSIG key and
    /// other context information of \c TSIGContext, and returns a
    /// result in the form of a (pointer object pointing to)
    /// \c TSIGRecord object.
    ///
    /// The caller of this method will use the returned value to render a
    /// complete TSIG RR into the message that has been signed so that it
    /// will become a complete TSIG-signed message.
    ///
    /// \note Normal applications are not expected to call this method
    /// directly; they will usually use the \c Message::toWire() method
    /// with a \c TSIGContext object being a parameter and have the
    /// \c Message class create a complete signed message.
    ///
    /// This method treats the given data as opaque, even though it's generally
    /// expected to represent a wire-format DNS message (see also the class
    /// description), and doesn't inspect it in any way.  For example, it
    /// doesn't check whether the data length is sane for a valid DNS message.
    /// This is also the reason why this method takes the \c qid parameter,
    /// which will be used as the original ID of the resulting
    /// \c TSIGRecordx object, even though this value should be stored in the
    /// first two octets (in wire format) of the given data.
    ///
    /// \note This method still checks and rejects empty data (\c NULL pointer
    /// data or the specified data length is 0) in order to avoid catastrophic
    /// effect such as program crash.  Empty data is not necessarily invalid
    /// for HMAC computation, but obviously it doesn't make sense for a DNS
    /// message.
    ///
    /// This method provides the strong exception guarantee; unless the method
    /// returns (without an exception being thrown), the internal state of
    /// the \c TSIGContext won't be modified.
    ///
    /// \exception InvalidParameter \c data is NULL or \c data_len is 0
    /// \exception cryptolink::LibraryError Some unexpected error in the
    /// underlying crypto operation
    /// \exception std::bad_alloc Temporary resource allocation failure
    ///
    /// \param qid The QID to be as the value of the original ID field of
    /// the resulting TSIG record
    /// \param data Points to the wire-format data to be signed
    /// \param data_len The length of \c data in bytes
    ///
    /// \return A TSIG record for the given data along with the context.
    ConstTSIGRecordPtr sign(const uint16_t qid, const void* const data,
                            const size_t data_len);

    /// Return the current state of the context
    ///
    /// \note
    /// The states are visible in public mainly for testing purposes.
    /// Normal applications won't have to deal with them.
    ///
    /// \exception None
    State getState() const;

    /// Return the TSIG error as a result of the latest verification
    ///
    /// This method can be called even before verifying anything, but the
    /// returned value is meaningless in that case.
    ///
    /// \exception None
    TSIGError getError() const;

    // This method is tentatively added for testing until a complete
    // verify() method is implemented.  Once it's done this should be
    // removed, and corresponding tests should be updated.
    //
    // This tentative "verify" method changes the internal state of
    // the TSIGContext to the CHECKED as if it were verified (though possibly
    // unsuccessfully) with given tsig_rdata.  If the error parameter is
    // given and not NOERROR, it's recorded inside the context so that the
    // subsequent sign() will behave accordingly.
    void verifyTentative(ConstTSIGRecordPtr tsig,
                         TSIGError error = TSIGError::NOERROR());

    /// \name Protocol constants and defaults
    ///
    //@{
    /// The recommended fudge value (in seconds) by RFC2845.
    ///
    /// Right now fudge is not tunable, and all TSIGs generated by this API
    /// will have this value of fudge.
    static const uint16_t DEFAULT_FUDGE = 300;
    //@}

private:
    struct TSIGContextImpl;
    TSIGContextImpl* impl_;
};
}
}

#endif  // __TSIG_H

// Local Variables:
// mode: c++
// End:
