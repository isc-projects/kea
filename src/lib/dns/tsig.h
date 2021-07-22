// Copyright (C) 2011-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// IMPORTANT: the server side of this code MUST NOT be used until
// it was fixed, cf RFC 8945. Note that Kea uses only the client side.

#ifndef TSIG_H
#define TSIG_H 1

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

#include <dns/tsigerror.h>
#include <dns/tsigkey.h>
#include <dns/tsigrecord.h>

namespace isc {
namespace dns {

/// An exception that is thrown for logic errors identified in TSIG
/// sign/verify operations.
///
/// Note that this exception is not thrown for TSIG protocol errors such as
/// verification failures.  In general, this exception indicates an internal
/// program bug.
class TSIGContextError : public isc::Exception {
public:
    TSIGContextError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

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
/// same context.
///
/// When multiple messages belong to the same TSIG session, either side
/// (signer or verifier) will keep using the same context.  It records
/// the latest session state (such as the previous digest) so that repeated
/// calls to \c sign() or \c verify() work correctly in terms of the TSIG
/// protocol.
///
/// \b Examples
///
/// This is a typical client application that sends a TSIG signed query
/// and verifies the response.
///
/// \code
///    // "renderer" is of MessageRenderer to render the message.
///    // (TSIGKey would be configured from config or command line in real app)
///    TSIGContext ctx(TSIGKey("key.example:MSG6Ng=="));
///    Message message(Message::RENDER);
///    message.addQuestion(Question(Name("www.example.com"), RRClass::IN(),
///                                 RRType::A()));
///    message.toWire(renderer, ctx);
///
///    // sendto, then recvfrom.  received result in (data, data_len)
///
///    message.clear(Message::PARSE);
///    InputBuffer buffer(data, data_len);
///    message.fromWire(buffer);
///    TSIGError tsig_error = ctx.verify(message.getTSIGRecord(),
///                                      data, data_len);
///    if (tsig_error == TSIGError::NOERROR()) {
///        // okay.  ctx can be continuously used if it's receiving subsequent
///        // signed responses from a TCP stream.
///    } else if (message.getRcode() == Rcode::NOTAUTH()) {
///        // hard error.  give up this transaction per RFC2845 4.6.
///    } else {
///        // Other error: discard response keep waiting with the same ctx
///        // for another (again, RFC2845 4.6).
///    } \endcode
///
/// And this is a typical server application that authenticates a signed
/// query and returns a response according to the result.
///
/// \code
///    // Assume "message" is of type Message for query handling and
///    // "renderer" is of MessageRenderer to render responses.
///    Message message(Message::RENDER);
///
///    TSIGKeyRing keyring; // this must be configured with keys somewhere
///
///    // Receive a query and store it in (data, data_len)
///    InputBuffer buffer(data, data_len);
///    message.clear(Message::PARSE);
///    message.fromWire(buffer);
///
///    const TSIGRecord* tsig = message.getTSIGRecord();
///    if (tsig) {
///        TSIGContext ctx(tsig->getName(), tsig->getRdata().getAlgorithm(),
///                        keyring);
///        ctx.verify(tsig, data, data_len);
///
///        // prepare response
///        message.makeResponse();
///        //...
///        message.toWire(renderer, ctx);
///
///        // send the response data back to the client.
///        // If this is a beginning of a signed session over a TCP and
///        // server has more data to send to the client, this ctx
///        // will be used to sign subsequent messages.
///    } \endcode
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
        SENT_REQUEST,           ///< Client sent a signed request, waiting response
        RECEIVED_REQUEST,       ///< Server received a signed request
        SENT_RESPONSE,          ///< Server sent a signed response
        VERIFIED_RESPONSE       ///< Client successfully verified a response
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

    /// Constructor from key parameters and key ring.
    TSIGContext(const Name& key_name, const Name& algorithm_name,
                const TSIGKeyRing& keyring);

    /// The destructor.
    virtual ~TSIGContext();
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
    /// In general, this method is called once by a client to send a
    /// signed request or one more times by a server to sign
    /// response(s) to a signed request.  To avoid allowing accidental
    /// misuse, if this method is called after a "client" validates a
    /// response, an exception of class \c TSIGContextError will be
    /// thrown.
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
    /// \note This method still checks and rejects empty data (null pointer
    /// data or the specified data length is 0) in order to avoid catastrophic
    /// effect such as program crash.  Empty data is not necessarily invalid
    /// for HMAC computation, but obviously it doesn't make sense for a DNS
    /// message.
    ///
    /// This method provides the strong exception guarantee; unless the method
    /// returns (without an exception being thrown), the internal state of
    /// the \c TSIGContext won't be modified.
    ///
    /// \exception TSIGContextError Context already verified a response.
    /// \exception InvalidParameter \c data is 0 or \c data_len is 0
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
    virtual ConstTSIGRecordPtr
    sign(const uint16_t qid, const void* const data, const size_t data_len);

    /// Verify a DNS message.
    ///
    /// This method verifies given data along with the context and a given
    /// TSIG in the form of a \c TSIGRecord object.  The data to be verified
    /// is generally expected to be a complete, wire-format DNS message,
    /// exactly as received by the host, and ending with a TSIG RR.
    /// After verification process this method updates its internal state,
    /// and returns the result in the form of a \c TSIGError object.
    /// Possible return values are (see the \c TSIGError class description
    /// for the mnemonics):
    ///
    /// - \c NOERROR: The data has been verified correctly.
    /// - \c FORMERR: \c TSIGRecord is not given (see below).
    /// - \c BAD_KEY: Appropriate key is not found or specified key doesn't
    ///               match for the data.
    /// - \c BAD_TIME: The current time doesn't fall in the range specified
    ///                in the TSIG.
    /// - \c BAD_SIG: The signature given in the TSIG doesn't match against
    ///               the locally computed digest or is the signature is
    ///               invalid in other way.
    /// - \c BAD_MODE: Not yet implemented TKEY error
    /// - \c BAD_NAME: Not yet implemented TKEY error
    /// - \c BAD_ALG: Not yet implemented TKEY error
    /// - \c BAD_TRUNC: The signature or truncated signature length is too
    ///                 small.
    ///
    /// If this method is called by a DNS client waiting for a signed
    /// response and the result is not \c NOERROR, the context can be used
    /// to try validating another signed message as described in RFC2845
    /// Section 4.6.
    ///
    /// If this method is called by a DNS server that tries to authenticate
    /// a signed request, and if the result is not \c NOERROR, the
    /// corresponding error condition is recorded in the context so that
    /// the server can return a response indicating what was wrong by calling
    /// \c sign() with the updated context.
    ///
    /// In general, this method is called once by a server for
    /// authenticating a signed request or one more times by a client to
    /// validate signed response(s) to a signed request.  To avoid allowing
    /// accidental misuse, if this method is called after a "server" signs
    /// a response, an exception of class \c TSIGContextError will be thrown.
    ///
    /// The \c record parameter can be 0; in that case this method simply
    /// returns \c FORMERR as the case described in Section 4.6 of RFC2845,
    /// i.e., receiving an unsigned response to a signed request.  This way
    /// a client can transparently pass the result of
    /// \c Message::getTSIGRecord() without checking whether it isn't 0
    /// and take an appropriate action based on the result of this method.
    ///
    /// This method handles the given data mostly as opaque.  It digests
    /// the data assuming it begins with a DNS header and ends with a TSIG
    /// RR whose length is given by calling \c TSIGRecord::getLength() on
    /// \c record, but otherwise it doesn't parse the data to confirm the
    /// assumption.  It's caller's responsibility to ensure the data is
    /// valid and consistent with \c record.  To avoid disruption, this
    /// method performs minimal validation on the given \c data and \c record:
    /// \c data must not be 0; \c data_len must not be smaller than the
    /// sum of the DNS header length (fixed, 12 octets) and the length of
    /// the TSIG RR.  If this check fails it throws an \c InvalidParameter
    /// exception.
    ///
    /// One unexpected case that is not covered by this method is that a
    /// client receives a signed response to an unsigned request.  RFC2845 is
    /// silent about such cases; BIND 9 explicitly identifies the case and
    /// rejects it.  With this implementation, the client can know that the
    /// response contains a TSIG via the result of
    /// \c Message::getTSIGRecord() and that it is an unexpected TSIG due to
    /// the fact that it doesn't have a corresponding \c TSIGContext.
    /// It's up to the client implementation whether to react to such a case
    /// explicitly (for example, it could either ignore the TSIG and accept
    /// the response or drop it).
    ///
    /// This method provides the strong exception guarantee; unless the method
    /// returns (without an exception being thrown), the internal state of
    /// the \c TSIGContext won't be modified.
    ///
    /// \todo Signature truncation support based on RFC4635
    ///
    /// \exception TSIGContextError Context already signed a response.
    /// \exception InvalidParameter \c data is 0 or \c data_len is too small.
    ///
    /// \param record The \c TSIGRecord to be verified with \c data
    /// \param data Points to the wire-format data (exactly as received) to
    /// be verified
    /// \param data_len The length of \c data in bytes
    /// \return The \c TSIGError that indicates verification result
    virtual TSIGError
    verify(const TSIGRecord* const record, const void* const data, const size_t data_len);

    /// \brief Check whether the last verified message was signed.
    ///
    /// RFC2845 allows for some of the messages not to be signed. However,
    /// the last message must be signed and the class has no knowledge if a
    /// given message is the last one, therefore it can't check directly.
    ///
    /// It is up to the caller to check if the last verified message was signed
    /// after all are verified by calling this function.
    ///
    /// \return If the last message was signed or not.
    /// \exception TSIGContextError if no message was verified yet.
    virtual bool lastHadSignature() const;

    /// Return the expected length of TSIG RR after \c sign()
    ///
    /// This method returns the length of the TSIG RR that would be
    /// produced as a result of \c sign() with the state of the context
    /// at the time of the call.  The expected length can be decided
    /// from the key and the algorithm (which determines the MAC size if
    /// included) and the recorded TSIG error.  Specifically, if a key
    /// related error has been identified, the MAC will be excluded; if
    /// a time error has occurred, the TSIG will include "other data".
    ///
    /// This method is provided mainly for the convenience of the Message
    /// class, which needs to know the expected TSIG length in rendering a
    /// signed DNS message so that it can handle truncated messages with TSIG
    /// correctly.  Normal applications wouldn't need this method.  The Python
    /// binding for this method won't be provided for the same reason.
    ///
    /// \exception None
    ///
    /// \return The expected TSIG RR length in bytes
    virtual size_t getTSIGLength() const;

    /// Return the current state of the context
    ///
    /// \note
    /// The states are visible in public mainly for testing purposes.
    /// Normal applications won't have to deal with them.
    ///
    /// \exception None
    virtual State getState() const;

    /// Return the TSIG error as a result of the latest verification
    ///
    /// This method can be called even before verifying anything, but the
    /// returned value is meaningless in that case.
    ///
    /// \exception None
    virtual TSIGError getError() const;

    /// \name Protocol constants and defaults
    ///
    //@{
    /// The recommended fudge value (in seconds) by RFC2845.
    ///
    /// Right now fudge is not tunable, and all TSIGs generated by this API
    /// will have this value of fudge.
    static const uint16_t DEFAULT_FUDGE = 300;
    //@}

protected:
    /// \brief Update internal HMAC state by more data.
    ///
    /// This is used mostly internally, when we need to verify a message without
    /// TSIG signature in the middle of signed TCP stream. However, it is also
    /// used in tests, so it's protected instead of private, to allow tests
    /// in.
    ///
    /// It doesn't contain sanity checks, and it is not tested directly. But
    /// we may want to add these one day to allow generating the skipped TSIG
    /// messages too. Until then, do not use this method.
    void update(const void* const data, size_t len);

private:
    struct TSIGContextImpl;
    TSIGContextImpl* impl_;
};

typedef boost::shared_ptr<TSIGContext> TSIGContextPtr;
typedef boost::shared_ptr<TSIGKey> TSIGKeyPtr;

}
}

#endif  // TSIG_H

// Local Variables:
// mode: c++
// End:
