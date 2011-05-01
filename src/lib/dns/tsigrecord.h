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

#ifndef __TSIGRECORD_H
#define __TSIGRECORD_H 1

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
    /// Constructor from TSIG key name and RDATA
    ///
    /// \exception std::bad_alloc Resource allocation for copying the name or
    /// RDATA fails
    TSIGRecord(const Name& key_name, const rdata::any::TSIG& tsig_rdata);

    /// Constructor from resource record (RR) parameters.
    ///
    /// \exception DNSMessageFORMERR
    TSIGRecord(const Name& name, const RRClass& rrclass, const RRTTL& ttl,
               const rdata::Rdata& rdata, size_t length);

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

    /// Return the length of the TSIG record
    ///
    /// When constructed from the key name and RDATA, it is the length of
    /// the record when it is rendered by the \c toWire() method.
    ///
    /// \note When constructed "from wire", that will mean the length of
    /// the wire format data for the TSIG RR.  The length will be necessary
    /// to verify the message once parse is completed.  But this part is not
    /// implemented yet.
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
/// \param record An \c TSIGRecord object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream& operator<<(std::ostream& os, const TSIGRecord& record);
}
}

#endif  // __TSIGRECORD_H

// Local Variables:
// mode: c++
// End:
