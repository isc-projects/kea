// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TSIGRECORD_H
#define TSIGRECORD_H 1

#include <ostream>
#include <string>

#include <boost/shared_ptr.hpp>

#include <util/buffer.h>

#include <dns/name.h>
#include <dns/rdataclass.h>

namespace isc {
namespace util {
class OutputBuffer;
}
namespace dns {
class AbstractMessageRenderer;

/// TSIG resource record.
///
/// A \c TSIGRecord class object represents a TSIG resource record and is
/// responsible for conversion to and from wire format TSIG record based on
/// the protocol specification (RFC2845).
/// This class is provided so that other classes and applications can handle
/// TSIG without knowing protocol details of TSIG, such as that it uses a
/// fixed constant of TTL.
///
/// \todo So the plan is to eventually provide  the "from wire" constructor.
/// It's not yet provided in the current phase of development.
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
    ///
    /// \name Constructors
    ///
    /// We use the default copy constructor, default copy assignment operator,
    /// (and default destructor) intentionally.
    //@{
    /// Constructor from TSIG key name and RDATA
    ///
    /// \exception std::bad_alloc Resource allocation for copying the name or
    /// RDATA fails
    TSIGRecord(const Name& key_name, const rdata::any::TSIG& tsig_rdata);

    /// Constructor from resource record (RR) parameters.
    ///
    /// This constructor is intended to be used in the context of parsing
    /// an incoming DNS message that contains a TSIG.  The parser would
    /// first extract the owner name, RR type (which is TSIG) class, TTL and
    /// the TSIG RDATA from the message.  This constructor is expected to
    /// be given these RR parameters (except the RR type, because it must be
    /// TSIG).
    ///
    /// According to RFC2845, a TSIG RR uses fixed RR class (ANY) and TTL (0).
    /// If the RR class or TTL is different from the expected one, this
    /// implementation considers it an invalid record and throws an exception
    /// of class \c DNSMessageFORMERR.
    ///
    /// \note This behavior is not specified in the protocol specification,
    /// but this implementation rejects unexpected values for the following
    /// reasons (but in any case, this won't matter much in practice as
    /// RFC2848 clearly states these fields always have the fixed values and
    /// any sane implementation of TSIG signer will follow that):
    /// According to the RFC editor (in a private communication), the intended
    /// use of the TSIG TTL field is to signal protocol extensions (currently
    /// no such extension is defined), so this field may actually be
    /// validly non 0 in future.  However, until the implementation supports
    /// that extension it may not always be able to handle the extended
    /// TSIG as intended; the extension may even affect digest computation.
    /// There's a related issue on this point.  Different implementations
    /// interpret the RFC in different ways on the received TTL when
    /// digesting the message: BIND 9 uses the received value (even if
    /// it's not 0) as part of the TSIG variables; NLnet Labs' LDNS and NSD
    /// always use a fixed constant of 0 regardless of the received TTL value.
    /// This means if and when an extension with non 0 TTL is introduced
    /// there will be interoperability problems in the form of verification
    /// failure.  By explicitly rejecting it (and subsequently returning
    /// a response with a format error) we can indicate the source of the
    /// problem more clearly than a "bad signature" TSIG error, which can
    /// happen for various reasons.  On the other hand, rejecting unexpected
    /// RR classes is mostly for consistency; the RFC lists these two fields
    /// in the same way, so it makes more sense to handle them equally.
    /// (BIND 9 rejects unexpected RR classes for TSIG, but that is part of
    /// general check on RR classes on received RRs; it generally requests
    /// all classes are the same, and if the protocol specifies the use of
    /// a particular class for a particular type of RR, it requests that
    /// class be used).
    ///
    /// Likewise, if \c rdata is not of type \c any::TSIG, an exception of
    /// class DNSMessageFORMERR will be thrown.  When the caller is a
    /// DNS message parser and builds \c rdata from incoming wire format
    /// data as described above, this case happens when the RR class is
    /// different from ANY (in the implementation, the type check takes place
    /// before the explicit check against the RR class explained in the
    /// previous paragraph).
    ///
    /// The \c length parameter is intended to be the length of the TSIG RR
    /// (from the beginning of the owner name to the end of the RDATA) when
    /// the caller is a DNS message parser.  Note that it is the actual length
    /// for the RR in the format; if the owner name or the algorithm name
    /// (in the RDATA) is compressed (although the latter should not be
    /// compressed according to RFC3597), the length must be the size of the
    /// compressed data.  The length is recorded inside the class and will
    /// be returned via subsequent calls to \c getLength().  It's intended to
    /// be used in the context TSIG verification; in the verify process
    /// the MAC computation must be performed for the original data without
    /// TSIG, so, to avoid parsing the entire data in the verify process
    /// again, it's necessary to record information that can identify the
    /// length to be digested for the MAC.  This parameter serves for that
    /// purpose.
    ///
    /// \note Since the constructor doesn't take the wire format data per se,
    /// it doesn't (and cannot) check the validity of \c length, and simply
    /// accepts any given value.  It even accepts obviously invalid values
    /// such as 0.  It's caller's responsibility to provide a valid value of
    /// length, and, the verifier's responsibility to use the length safely.
    ///
    /// <b>DISCUSSION:</b> this design is fragile in that it introduces
    /// a tight coupling between message parsing and TSIG verification via
    /// the \c TSIGRecord class.  In terms of responsibility decoupling,
    /// the ideal way to have \c TSIGRecord remember the entire wire data
    /// along with the length of the TSIG.  Then in the TSIG verification
    /// we could refer to the necessary potion of data solely from a
    /// \c TSIGRecord object.  However, this approach would require expensive
    /// heavy copy of the original data or introduce another kind of coupling
    /// between the data holder and this class (if the original data is freed
    /// while a \c TSIGRecord object referencing the data still exists, the
    /// result will be catastrophic).  As a "best current compromise", we
    /// use the current design.  We may reconsider it if it turns out to
    /// cause a big problem or we come up with a better idea.
    ///
    /// \exception DNSMessageFORMERR Given RR parameters are invalid for TSIG.
    /// \exception std::bad_alloc Internal resource allocation fails.
    ///
    /// \param name The owner name of the TSIG RR
    /// \param rrclass The RR class of the RR.  Must be \c RRClass::ANY()
    /// (see above)
    /// \param ttl The TTL of the RR.  Must be 0 (see above)
    /// \param rdata The RDATA of the RR.  Must be of type \c any::TSIG.
    /// \param length The size of the RR (see above)
    TSIGRecord(const Name& name, const RRClass& rrclass, const RRTTL& ttl,
               const rdata::Rdata& rdata, size_t length);
    //@}

    /// Return the owner name of the TSIG RR, which is the TSIG key name
    ///
    /// \exception None
    const Name& getName() const { return (key_name_); }

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

    /// Return the TTL value of TSIG
    ///
    /// TSIG always uses 0 TTL.  This static method returns it,
    /// when, though unlikely, an application wants to know the TTL TSIG
    /// is supposed to use.
    ///
    /// \exception None
    static const RRTTL& getTTL();
    //@}

    /// Return the length of the TSIG record
    ///
    /// When constructed from the key name and RDATA, it is the length of
    /// the record when it is rendered by the \c toWire() method.
    ///
    /// \note When constructed "from wire", that will mean the length of
    /// the wire format data for the TSIG RR.  The length will be necessary
    /// to verify the message once parse is completed.
    ///
    /// \exception None
    size_t getLength() const { return (length_); }

    /// \brief Render the \c TSIG RR in the wire format.
    ///
    /// This method renders the TSIG record as a form of a DNS TSIG RR
    /// via \c renderer, which encapsulates output buffer and other rendering
    /// contexts.
    ///
    /// Normally this version of \c toWire() method tries to compress the
    /// owner name of the RR whenever possible, but this method intentionally
    /// skips owner name compression.  This is due to a report that some
    /// Windows clients refuse a TSIG if its owner name is compressed
    /// (See http://marc.info/?l=bind-workers&m=126637138430819&w=2).
    /// Reportedly this seemed to be specific to GSS-TSIG, but this
    /// implementation skip compression regardless of the algorithm.
    ///
    /// If by adding the TSIG RR the message size would exceed the limit
    /// maintained in \c renderer, this method skips rendering the RR
    /// and returns 0 and mark \c renderer as "truncated" (so that a
    /// subsequent call to \c isTruncated() on \c renderer will result in
    /// \c true); otherwise it returns 1, which is the number of RR
    /// rendered.
    ///
    /// \note If the caller follows the specification of adding TSIG
    /// as described in RFC2845, this should not happen; the caller is
    /// generally expected to leave a sufficient room in the message for
    /// the TSIG.  But this method checks the unexpected case nevertheless.
    ///
    /// \exception std::bad_alloc Internal resource allocation fails (this
    /// should be rare).
    ///
    /// \param renderer DNS message rendering context that encapsulates the
    /// output buffer and name compression information.
    /// \return 1 if the TSIG RR fits in the message size limit; otherwise 0.
    int toWire(AbstractMessageRenderer& renderer) const;

    /// \brief Render the \c TSIG RR in the wire format.
    ///
    /// This method is same as \c toWire(AbstractMessageRenderer&)const
    /// except it renders the RR in an \c OutputBuffer and therefore
    /// does not care about message size limit.
    /// As a consequence it always returns 1.
    int toWire(isc::util::OutputBuffer& buffer) const;

    /// Convert the TSIG record to a string.
    ///
    /// The output format is the same as the result of \c toText() for
    /// other normal types of RRsets (with always using the same RR class
    /// and TTL).  It also ends with a newline.
    ///
    /// \exception std::bad_alloc Internal resource allocation fails (this
    /// should be rare).
    ///
    /// \return A string representation of \c TSIG record
    std::string toText() const;

    /// The TTL value to be used in TSIG RRs.
    static const uint32_t TSIG_TTL = 0;
    //@}

private:
    const Name key_name_;
    const rdata::any::TSIG rdata_;
    const size_t length_;
};

/// A pointer-like type pointing to a \c TSIGRecord object.
typedef boost::shared_ptr<TSIGRecord> TSIGRecordPtr;

/// A pointer-like type pointing to an immutable \c TSIGRecord object.
typedef boost::shared_ptr<const TSIGRecord> ConstTSIGRecordPtr;

/// Insert the \c TSIGRecord as a string into stream.
///
/// This method convert \c record into a string and inserts it into the
/// output stream \c os.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param record A \c TSIGRecord object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream& operator<<(std::ostream& os, const TSIGRecord& record);
}
}

#endif  // TSIGRECORD_H

// Local Variables:
// mode: c++
// End:
