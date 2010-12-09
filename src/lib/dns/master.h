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

#ifndef __MASTER_H
#define __MASTER_H 1

#include <iosfwd>

#include <exceptions/exceptions.h>

#include <dns/rrset.h>

namespace isc {
namespace dns {
class Name;
class RRClass;

/// \brief An exception that is thrown if an error occurs while loading a
/// master zone data.
class MasterError : public Exception {
public:
    MasterError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

class MasterLoadCallback {
public:
    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// For our purpose, we don't the assignment operator for this class.
    /// For simply we hide it as a private method for now.
    //@{
    /// Constructor.
    ///
    /// note: this constructor is intentionally not defined as "explicit"
    /// for the convenience of the caller of \c masterLoad().
    template <typename FUNC>
    MasterLoadCallback(FUNC func) :
        func_(new FUNC(func)),
        invoker_(invoke<FUNC>),
        deleter_(cleanup<FUNC>),
        copier_(copyFunctor<FUNC>)
    {}

    /// Copy constructor.
    MasterLoadCallback(const MasterLoadCallback& source) :
        func_((*source.copier_)(source.func_)),
        invoker_(source.invoker_),
        deleter_(source.deleter_),
        copier_(source.copier_)
    {}

    /// The destructor.
    ~MasterLoadCallback() { (*deleter_)(func_); }
    //@}

    void operator()(RRsetPtr rrset) {
        (*invoker_)(func_, rrset);
    }
private:
    MasterLoadCallback& operator=(const MasterLoadCallback& source);
    
    template <typename FUNC>
    static void invoke(void* func, RRsetPtr rrset) {
        FUNC* funcobj = static_cast<FUNC*>(func);
        return ((*funcobj)(rrset));
    }
    template <typename FUNC>
    static void cleanup(void* func) {
        delete static_cast<FUNC*>(func);
    }
    template <typename FUNC>
    static void* copyFunctor(void* func) {
        return (new FUNC(*static_cast<FUNC*>(func)));
    }
    void* func_;
    void (*invoker_)(void*, RRsetPtr);
    void (*deleter_)(void*);
    void* (*copier_)(void*);
};

///
/// \name Master zone file loader functions.
///
//@{
/// Master zone file loader from a file.
///
/// Ownership is transferred once the callback is called.  The callback
/// can freely modify the passed \c RRset.
///
/// <b>Acceptable Format</b>
///
/// The current implementation only supports a restricted form of master files
/// for simplicity.  Specifically, each RR must consist of exactly one line
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
/// - <TTL>, <RRCLASS>, and <RRTYPE> must be recognizable by the \c RRTTL,
///   RRClass and RRType class implementations of this library.  In particular,
///   as of this writing TTL must be a decimal number (a convenient extension
///   such as "1H" instead of 3600 cannot be used).  Not all standard RR
///   classes and RR types are supported yet, so the mnemonics of them will
///   be rejected, too.
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
/// The acceptable form may seem too restrictive, but an arbitrary zone file
/// can be converted into this form by using BIND 9's named-compilezone tool
/// with both the input and output formats being "text".  Here is an example:
/// \code % named-compilezone -f text -F text -o example.com.norm
///      example.com example.com.zone
/// \endcode
/// where example.com.zone is the original zone file for the "example.com"
/// zone.  The output file is example.com.norm, which should be acceptable
/// by this implementation.
///
/// <b>Exceptions</b>
///
/// If the RR class of a given RR is different from \c zone_class,
/// an exception of class \c MasterError will be thrown.
///
/// <b>Usage Examples</b>
///
/// <b>Implementation Notes</b>
///
/// RRSIG consideration (later)?
/// may eventually want to make it a class; for now, it's not clear whether
/// we need that level of abstraction.
/// may want to have load options; may want to support incremental load.
/// may want to support "generous" mode.
///
/// \param filename A path to a master zone file to be loaded.
/// \param origin The origin name of the zone.
/// \param zone_class The RR class of the zone.
/// \param callbck A callback functor that is to be called for each RRset.
void masterLoad(const char* const filename, const Name& origin,
                const RRClass& zone_class, MasterLoadCallback callback);

/// Master zone file loader from input stream.
///
/// All descriptions of the other version
/// (\c masterLoad(const char* const, const Name&, const RRClass&, MasterLoadCallback))
/// apply to this version except those specific to file I/O.
///
/// \param input An input stream object that is to emit zone's RRs.
/// \param origin The origin name of the zone.
/// \param zone_class The RR class of the zone.
/// \param callbck A callback functor that is to be called for each RRset.
void masterLoad(std::istream& input, const Name& origin,
                const RRClass& zone_class, MasterLoadCallback callback);
}
//@}
}

#endif  // __MASTER_H

// Local Variables:
// mode: c++
// End:
