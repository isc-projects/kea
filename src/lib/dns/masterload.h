// Copyright (C) 2010-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MASTERLOAD_H
#define MASTERLOAD_H 1

#include <dns/rrset.h>
#include <exceptions/exceptions.h>

#include <functional>
#include <iosfwd>

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
typedef std::function<void(RRsetPtr)> MasterLoadCallback;

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
/// More precisely, it can be anything that this form of std::function
/// can represent, but the caller normally doesn't have to care about
/// that level of details.
///
/// The ownership of constructed RRsets is transferred to the callback
/// and this function never uses it once it is called.
/// The callback can freely modify the passed \c RRset.
///
/// This function internally uses the MasterLoader class, and basically
/// accepts and rejects input that MasterLoader accepts and rejects,
/// accordingly.  In addition, this function performs the following validation:
/// if an SOA RR is included, its owner name must be the origin name.
///
/// It does not perform other semantical checks, however.  For example,
/// it doesn't check if an NS RR of the origin name is included or if
/// there is more than one SOA RR.  Such further checks are the caller's
/// (or the callback's) responsibility.
///
/// <b>Exceptions</b>
///
/// This function throws an exception of class \c MasterLoadError in the
/// following cases:
/// - Any of the validation checks fails (see above).
/// - The input data has a syntax error.
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
/// wrapping things with \c std::bind would be handy:
/// \code class ZoneDumper {
/// public:
///    void dump(ConstRRsetPtr rrset) const {
///        std::cout << *rrset;
///    }
/// };
/// ...
///    ZoneDumper dumper;
///    masterLoad(rr_stream, Name("example.com"), RRClass::IN(),
///               std::bind(&ZoneDumper::dump, &dumper, _1));
/// \endcode
/// You can find a bit more complicated examples in the unit tests code for
/// this function.
///
/// <b>Implementation Notes</b>
///
/// The current implementation is in a preliminary level and needs further
/// extensions.  Some design decisions may also have to be reconsidered as
/// we gain experiences.  Those include:
/// - We may want to allow optional conditions.  For example, we may want to
///   be generous about some validation failures and be able to continue
///   parsing.
/// - Especially if we allow to be generous, we may also want to support
///   returning an error code instead of throwing an exception when we
///   encounter validation failure.
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
/// Note: The 'source' parameter is now ignored, but it was only used in
/// exception messages on some error.  So the compatibility effect should be
/// minimal.
///
/// \param input An input stream object that is to emit zone's RRs.
/// \param origin The origin name of the zone.
/// \param zone_class The RR class of the zone.
/// \param callback A callback functor or function that is to be called for
/// each RRset.
/// \param source This parameter is now ignored but left for compatibility.
void masterLoad(std::istream& input, const Name& origin,
                const RRClass& zone_class, MasterLoadCallback callback,
                const char* source = NULL);
}


//@}
}

#endif  // MASTERLOAD_H

// Local Variables:
// mode: c++
// End:
