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

#ifndef __MASTERLOAD_H
#define __MASTERLOAD_H 1

#include <iosfwd>

#include <boost/function.hpp>

#include <exceptions/exceptions.h>

#include <dns/rrset.h>

namespace isc {
namespace dns {
class Name;
class RRClass;

/// \brief An exception that is thrown if an error occurs while loading a
/// master zone data.
class MasterLoadError : public isc::Exception {
public:
    MasterLoadError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// The type of the \c callback parameter of \c masterLoad().
///
/// This represents a functor object or a function that takes one parameter
/// of type \c RRsetPtr and returns nothing.
typedef boost::function<void(RRsetPtr)> MasterLoadCallback;

///
/// \name Master zone file loader functions.
///
//@{
/// Master zone file loader from a file.
///
/// This function parses a given file as a master DNS zone file for
/// the given origin name and RR class, constructs a sequence of \c RRset
/// from the RRs containing in the file, and calls the given \c callback
/// functor object or function with each \c RRset.
///
/// The \c callback parameter is a functor object or a function that
/// takes one parameter of type \c RRsetPtr and returns nothing,
/// i.e. \c void (see below for specific examples).
/// More precisely, it can be anything that this form of boost::function
/// can represent, but the caller normally doesn't have to care about
/// that level of details.
///
/// The ownership of constructed RRsets is transferred to the callback
/// and this function never uses it once it is called.
/// The callback can freely modify the passed \c RRset.
///
/// This function performs minimum level of validation on the input:
/// - Each RR is a valid textual representation per the DNS protocol.
/// - The class of each RR must be identical to the specified RR class.
/// - The owner name of each RR must be a subdomain of the origin name
///   (that can be equal to the origin).
/// - If an SOA RR is included, its owner name must be the origin name.
/// If any of these validation checks fails, this function throws an
/// exception of class \c MasterLoadError.
///
/// It does not perform other semantical checks, however.  For example,
/// it doesn't check if an NS RR of the origin name is included or if
/// there is more than one SOA RR.  Such further checks are the caller's
/// (or the callback's) responsibility.
///
/// <b>Acceptable Format</b>
///
/// The current implementation only supports a restricted form of master files
/// for simplicity.  One easy way to ensure that a handwritten zone file is
/// acceptable to this implementation is to preprocess it with BIND 9's
/// named-compilezone tool with both the input and output formats being
/// "text".
/// Here is an example:
/// \code % named-compilezone -f text -F text -o example.com.norm
///      example.com example.com.zone
/// \endcode
/// where example.com.zone is the original zone file for the "example.com"
/// zone.  The output file is example.com.norm, which should be acceptable
/// by this implementation.
///
/// Below are specific restrictions that this implementation assumes.
/// Basically, each RR must consist of exactly one line
/// (so there shouldn't be a multi-line RR) in the following format:
/// \code  <owner name> <TTL> <RRCLASS> <RRTYPE> <RDATA (single line)>
/// \endcode
/// Here are some more details about the restrictions:
/// - No special directives such as $TTL are supported.
/// - The owner name must be absolute, that is, it must end with a period.
/// - "@" is not recognized as a valid owner name.
/// - Owner names, TTL and RRCLASS cannot be omitted.
/// - As a corollary, a non blank line must not begin with a space character.
/// - The order of the RR parameters is fixed, for example, this is acceptable:
/// \code example.com. 3600 IN A 192.0.2.1
/// \endcode
///  but this is not even though it's valid per RFC1035:
/// \code example.com. IN 3600 A 192.0.2.1
/// \endcode
/// - "TTL", "RRCLASS", and "RRTYPE" must be recognizable by the \c RRTTL,
///   RRClass and RRType class implementations of this library.  In particular,
///   as of this writing TTL must be a decimal number (a convenient extension
///   such as "1H" instead of 3600 cannot be used).  Not all standard RR
///   classes and RR types are supported yet, so the mnemonics of them will
///   be rejected, too.
/// - RR TTLs of the same RRset must be the same; even if they are different,
///   this implementation simply uses the TTL of the first RR.
///
/// Blank lines and lines beginning with a semi-colon are allowed, and will
/// be simply ignored.  Comments cannot coexist with an RR line, however.
/// For example, this will be rejected:
/// \code example.com. 3600 IN A 192.0.2.1 ; this is a comment
/// \endcode
///
/// This implementation assumes that RRs of a single RRset are not
/// interleaved with RRs of a different RRset.
/// That is, the following sequence shouldn't happen:
/// \code example.com. 3600 IN A 192.0.2.1
/// example.com. 3600 IN AAAA 2001:db8::1
/// example.com. 3600 IN A 192.0.2.2
/// \endcode
/// But it does not consider this an error; it will simply regard each RR
/// as a separate RRset and call the callback with them separately.
/// It is up to the callback to merge multiple RRsets into one if possible
/// and necessary.
///
/// <b>Exceptions</b>
///
/// This function throws an exception of class \c MasterLoadError in the
/// following cases:
/// - Any of the validation checks fails (see the class description).
/// - The input data is not in the acceptable format (see the details of
///   the format above).
/// - The specified file cannot be opened for loading.
/// - An I/O error occurs during the loading.
///
/// In addition, this function requires resource allocation for parsing and
/// constructing RRsets.  If it fails, the corresponding standard exception
/// will be thrown.
///
/// The callback may throw its own function.  This function doesn't catch it
/// and will simply propagate it towards the caller.
///
/// <b>Usage Examples</b>
///
/// A simplest example usage of this function would be to parse a zone
/// file and (after validation) dump the content to the standard output.
/// This is an example functor object and a call to \c masterLoad
/// that implements this scenario:
/// \code struct ZoneDumper {
///     void operator()(ConstRRsetPtr rrset) const {
///        std::cout << *rrset;
///     }
/// };
/// ...
///    masterLoad(zone_file, Name("example.com"), RRClass::IN(), ZoneDumper());
/// \endcode
/// Alternatively, you can use a normal function instead of a functor:
/// \code void zoneDumper(ConstRRsetPtr rrset) {
///    std::cout << *rrset;
/// }
/// ...
///    masterLoad(zone_file, Name("example.com"), RRClass::IN(), zoneDumper);
/// \endcode
/// Or, if you want to use it with a member function of some other class,
/// wrapping things with \c boost::bind would be handy:
/// \code class ZoneDumper {
/// public:
///    void dump(ConstRRsetPtr rrset) const {
///        std::cout << *rrset;
///    }
/// };
/// ...
///    ZoneDumper dumper;
///    masterLoad(rr_stream, Name("example.com"), RRClass::IN(),
///               boost::bind(&ZoneDumper::dump, &dumper, _1));
/// \endcode
/// You can find a bit more complicated examples in the unit tests code for
/// this function.
///
/// <b>Implementation Notes</b>
///
/// The current implementation is in a preliminary level and needs further
/// extensions.  Some design decisions may also have to be reconsidered as
/// we gain experiences.  Those include:
/// - We should be more flexible about the input format.
/// - We may want to allow optional conditions.  For example, we may want to
///   be generous about some validation failures and be able to continue
///   parsing.
/// - Especially if we allow to be generous, we may also want to support
///   returning an error code instead of throwing an exception when we
///   encounter validation failure.
/// - We may want to support incremental loading.
/// - If we add these optional features we may want to introduce a class
///   that encapsulates loading status and options.
/// - RRSIGs are handled as separate RRsets, i.e. they are not included in
///   the RRset they cover.
///
/// \param filename A path to a master zone file to be loaded.
/// \param origin The origin name of the zone.
/// \param zone_class The RR class of the zone.
/// \param callback A callback functor or function that is to be called
/// for each RRset.
void masterLoad(const char* const filename, const Name& origin,
                const RRClass& zone_class, MasterLoadCallback callback);

/// Master zone file loader from input stream.
///
/// This function is same as the other version
/// (\c masterLoad(const char* const, const Name&, const RRClass&, MasterLoadCallback))
/// except that it takes a \c std::istream instead of a file.
/// It extracts lines from the stream and handles each line just as a line
/// of a file for the other version of function.
/// All descriptions of the other version apply to this version except those
/// specific to file I/O.
///
/// \param input An input stream object that is to emit zone's RRs.
/// \param origin The origin name of the zone.
/// \param zone_class The RR class of the zone.
/// \param callback A callback functor or function that is to be called for
/// each RRset.
/// \param source A string to use in error messages if zone content is bad
/// (e.g. the file name when reading from a file). If this value is NULL,
/// or left out, the error will use the string '<unknown>'
void masterLoad(std::istream& input, const Name& origin,
                const RRClass& zone_class, MasterLoadCallback callback,
                const char* source=NULL);
}


//@}
}

#endif  // __MASTERLOAD_H

// Local Variables:
// mode: c++
// End:
