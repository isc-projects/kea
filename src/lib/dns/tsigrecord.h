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

#include <boost/shared_ptr.hpp>

#include <util/buffer.h>

#include <dns/name.h>
#include <dns/rdataclass.h>

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
}
}

#endif  // __TSIGRECORD_H

// Local Variables:
// mode: c++
// End:
