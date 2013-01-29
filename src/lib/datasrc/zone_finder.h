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

#ifndef DATASRC_ZONE_FINDER_H
#define DATASRC_ZONE_FINDER_H 1

#include <dns/name.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>

#include <datasrc/exceptions.h>
#include <datasrc/result.h>

#include <utility>
#include <vector>

namespace isc {
namespace datasrc {

/// \brief Out of zone exception
///
/// This is thrown when a method is called for a name or RRset which
/// is not in or below the zone.
class OutOfZone : public ZoneException {
public:
    OutOfZone(const char* file, size_t line, const char* what) :
        ZoneException(file, line, what) {}
};

/// \brief The base class to search a zone for RRsets
///
/// The \c ZoneFinder class is an abstract base class for representing
/// an object that performs DNS lookups in a specific zone accessible via
/// a data source.  In general, different types of data sources (in-memory,
/// database-based, etc) define their own derived classes of \c ZoneFinder,
/// implementing ways to retrieve the required data through the common
/// interfaces declared in the base class.  Each concrete \c ZoneFinder
/// object is therefore (conceptually) associated with a specific zone
/// of one specific data source instance.
///
/// The origin name and the RR class of the associated zone are available
/// via the \c getOrigin() and \c getClass() methods, respectively.
///
/// The most important method of this class is \c find(), which performs
/// the lookup for a given domain and type.  See the description of the
/// method for details.
///
/// \note It's not clear whether we should request that a zone finder form a
/// "transaction", that is, whether to ensure the finder is not susceptible
/// to changes made by someone else than the creator of the finder.  If we
/// don't request that, for example, two different lookup results for the
/// same name and type can be different if other threads or programs make
/// updates to the zone between the lookups.  We should revisit this point
/// as we gain more experiences.
class ZoneFinder {
public:
    /// Result codes of the \c find() method.
    ///
    /// Note: the codes are tentative.  We may need more, or we may find
    /// some of them unnecessary as we implement more details.
    ///
    /// See the description of \c find() for further details of how
    /// these results should be interpreted.
    enum Result {
        SUCCESS,                ///< An exact match is found.
        DELEGATION,             ///< The search encounters a zone cut.
        NXDOMAIN, ///< There is no domain name that matches the search name
        NXRRSET,  ///< There is a matching name but no RRset of the search type
        CNAME,    ///< The search encounters and returns a CNAME RR
        DNAME    ///< The search encounters and returns a DNAME RR
    };

    /// Special attribute flags on the result of the \c find() method
    ///
    /// The flag values defined here are intended to signal to the caller
    /// that it may need special handling on the result.  This is particularly
    /// of concern when DNSSEC is requested.  For example, for negative
    /// responses the caller would want to know whether the zone is signed
    /// with NSEC or NSEC3 so that it can subsequently provide necessary
    /// proof of the result.
    ///
    /// The caller is generally expected to get access to the information
    /// via read-only getter methods of \c FindContext so that it won't rely
    /// on specific details of the representation of the flags.  So these
    /// definitions are basically only meaningful for data source
    /// implementations.
    enum FindResultFlags {
        RESULT_DEFAULT = 0,       ///< The default flags
        RESULT_WILDCARD = 1,      ///< find() resulted in a wildcard match
        RESULT_NSEC_SIGNED = 2,   ///< The zone is signed with NSEC RRs
        RESULT_NSEC3_SIGNED = 4   ///< The zone is signed with NSEC3 RRs
    };

    /// Find options.
    ///
    /// The option values are used as a parameter for \c find().
    /// These are values of a bitmask type.  Bitwise operations can be
    /// performed on these values to express compound options.
    enum FindOptions {
        FIND_DEFAULT = 0,       ///< The default options
        FIND_GLUE_OK = 1,       ///< Allow search under a zone cut
        FIND_DNSSEC = 2,        ///< Require DNSSEC data in the answer
                                ///< (RRSIG, NSEC, etc.). The implementation
                                ///< is allowed to include it even if it is
                                ///< not set.
        NO_WILDCARD = 4         ///< Do not try wildcard matching.
    };

protected:
    /// \brief A convenient tuple representing a set of find() results.
    ///
    /// This helper structure is specifically expected to be used as an input
    /// for the construct of the \c Context class object used by derived
    /// ZoneFinder implementations.  This is therefore defined as protected.
    struct ResultContext {
        ResultContext(Result code_param,
                      isc::dns::ConstRRsetPtr rrset_param,
                      FindResultFlags flags_param = RESULT_DEFAULT) :
            code(code_param), rrset(rrset_param), flags(flags_param)
        {}
        const Result code;
        const isc::dns::ConstRRsetPtr rrset;
        const FindResultFlags flags;
    };

public:
    /// \brief A helper function to strip RRSIGs when FIND_DNSSEC is not
    /// requested.
    static isc::dns::ConstRRsetPtr
    stripRRsigs(isc::dns::ConstRRsetPtr rp, const FindOptions options);

    /// \brief Context of the result of a find() call.
    ///
    /// This class encapsulates results and (possibly) associated context
    /// of a call to the \c find() method.   The public member variables of
    /// this class represent the result of the call.  They are a
    /// straightforward tuple of the result code and a pointer (and
    /// optionally special flags) to the found RRset.
    ///
    /// These member variables will be initialized on construction and never
    /// change, so for convenience we allow the applications to refer to some
    /// of the members directly.  For some others we provide read-only accessor
    /// methods to hide specific representation.
    ///
    /// Another role of this class is to provide the interface to some common
    /// processing logic that may be necessary using the result of \c find().
    /// Specifically, it's expected to be used in the context of DNS query
    /// handling, where the caller would need to look into the data source
    /// again based on the \c find() result.  For example, it would need to
    /// get A and/or AAAA records for some of the answer or authority RRs.
    ///
    /// This class defines (a set of) method(s) that can be commonly used
    /// for such purposes for any type of data source (as long as it conforms
    /// to the public \c find() interface).  In some cases, a specific data
    /// source implementation may want to (and can) optimize the processing
    /// exploiting its internal data structure and the knowledge of the context
    /// of the precedent \c find() call.  Such a data source implementation
    /// can define a derived class of the base Context and override the
    /// specific virtual method.
    ///
    /// This base class defines these common protected methods along with
    /// some helper pure virtual methods that would be necessary for the
    /// common methods.  If a derived class wants to use the common version
    /// of the protected method, it needs to provide expected result through
    /// their implementation of the pure virtual methods.
    ///
    /// This class object is generally expected to be associated with the
    /// ZoneFinder that originally performed the \c find() call, and expects
    /// the finder is valid throughout the lifetime of this object.  It's
    /// caller's responsibility to ensure that assumption.
    class Context {
    public:
        /// \brief The constructor.
        ///
        /// \param options The find options specified for the find() call.
        /// \param result The result of the find() call.
        Context(FindOptions options, const ResultContext& result) :
            code(result.code), rrset(result.rrset),
            flags_(result.flags), options_(options)
        {}

        /// \brief The destructor.
        virtual ~Context() {}

        const Result code;
        const isc::dns::ConstRRsetPtr rrset;

        /// Return true iff find() results in a wildcard match.
        bool isWildcard() const { return ((flags_ & RESULT_WILDCARD) != 0); }

        /// Return true when the underlying zone is signed with NSEC.
        ///
        /// The \c find() implementation allows this to return false if
        /// \c FIND_DNSSEC isn't specified regardless of whether the zone
        /// is signed or which of NSEC/NSEC3 is used.
        ///
        /// When this is returned, the implementation of find() must ensure
        /// that \c rrset be a valid NSEC RRset as described in \c find()
        /// documentation.
        bool isNSECSigned() const {
            return ((flags_ & RESULT_NSEC_SIGNED) != 0);
        }

        /// Return true when the underlying zone is signed with NSEC3.
        ///
        /// The \c find() implementation allows this to return false if
        /// \c FIND_DNSSEC isn't specified regardless of whether the zone
        /// is signed or which of NSEC/NSEC3 is used.
        bool isNSEC3Signed() const {
            return ((flags_ & RESULT_NSEC3_SIGNED) != 0);
        }

        /// \brief Find and return additional RRsets corresponding to the
        ///        result of \c find().
        ///
        /// If this context is based on a normal find() call that resulted
        /// in SUCCESS or DELEGATION, it examines the returned RRset (in many
        /// cases NS, sometimes MX or others), searches the data source for
        /// specified type of additional RRs for each RDATA of the RRset
        /// (e.g., A or AAAA for the name server addresses), and stores the
        /// result in the given vector.  The vector may not be empty; this
        /// method appends any found RRsets to it, without touching existing
        /// elements.
        ///
        /// If this context is based on a findAll() call that resulted in
        /// SUCCESS, it performs the same process for each RRset returned in
        /// the \c findAll() call.
        ///
        /// The caller specifies desired RR types of the additional RRsets
        /// in \c requested_types.  Normally it consists of A and/or AAAA
        /// types, but other types can be specified.
        ///
        /// This method is meaningful only when the precedent find()/findAll()
        /// call resulted in SUCCESS or DELEGATION.  Otherwise this method
        /// does nothing.
        ///
        /// \note The additional RRsets returned via method are limited to
        /// ones contained in the zone which the corresponding find/findAll
        /// call searched (possibly including glues under a zone cut where
        /// they are applicable).  If the caller needs to get out-of-zone
        /// additional RRsets, it needs to explicitly finds them by
        /// identifying the corresponding zone and calls \c find() for it.
        ///
        /// \param requested_types A vector of RR types for desired additional
        ///  RRsets.
        /// \param result A vector to which any found additional RRsets are
        /// to be inserted.
        void getAdditional(
            const std::vector<isc::dns::RRType>& requested_types,
            std::vector<isc::dns::ConstRRsetPtr>& result)
        {
            // Perform common checks, and delegate the process to the default
            // or specialized implementation.
            if (code != SUCCESS && code != DELEGATION) {
                return;
            }

            getAdditionalImpl(requested_types, result);
        }

    protected:
        /// \brief Return the \c ZoneFinder that created this \c Context.
        ///
        /// A derived class implementation can return NULL if it defines
        /// other protected methods that require a non NULL result from
        /// this method.  Otherwise it must return a valid, non NULL pointer
        /// to the \c ZoneFinder object.
        ///
        /// When returning non NULL, the ownership of the pointed object
        /// was not transferred to the caller; it cannot be assumed to be
        /// valid after the originating \c Context object is destroyed.
        /// Also, the caller must not try to delete the returned object.
        virtual ZoneFinder* getFinder() = 0;

        /// \brief Return a vector of RRsets corresponding to findAll() result.
        ///
        /// This method returns a set of RRsets that correspond to the
        /// returned RRsets to a prior \c findAll() call.
        ///
        /// A derived class implementation can return NULL if it defines
        /// other protected methods that require a non NULL result from
        /// this method.  Otherwise it must return a valid, non NULL pointer
        /// to a vector that correspond to the expected set of RRsets.
        ///
        /// When returning non NULL, the ownership of the pointed object
        /// was not transferred to the caller; it cannot be assumed to be
        /// valid after the originating \c Context object is destroyed.
        /// Also, the caller must not try to delete the returned object.
        virtual const std::vector<isc::dns::ConstRRsetPtr>*
        getAllRRsets() const = 0;

        /// \brief Actual implementation of getAdditional().
        ///
        /// This base class defines a default implementation that can be
        /// used for any type of data sources.  A data source implementation
        /// can override it.
        ///
        /// The default version of this implementation requires both
        /// \c getFinder() and \c getAllRRsets() return valid results.
        virtual void getAdditionalImpl(
            const std::vector<isc::dns::RRType>& requested_types,
            std::vector<isc::dns::ConstRRsetPtr>& result);

    private:
        const FindResultFlags flags_;
    protected:
        const FindOptions options_;
    };

    /// \brief Generic ZoneFinder context that works for all implementations.
    ///
    /// This is a concrete derived class of \c ZoneFinder::Context that
    /// only use the generic (default) versions of the protected methods
    /// and therefore work for any data source implementation.
    ///
    /// A data source implementation can use this class to create a
    /// \c Context object as a return value of \c find() or \c findAll()
    /// method if it doesn't have to optimize specific protected methods.
    class GenericContext : public Context {
    public:
        /// \brief The constructor for the normal find call.
        ///
        /// This constructor is expected to be called from the \c find()
        /// method when it constructs the return value.
        ///
        /// \param finder The ZoneFinder on which find() is called.
        /// \param options See the \c Context class.
        /// \param result See the \c Context class.
        GenericContext(ZoneFinder& finder, FindOptions options,
                       const ResultContext& result) :
            Context(options, result), finder_(finder)
        {}

        /// \brief The constructor for the normal findAll call.
        ///
        /// This constructor is expected to be called from the \c findAll()
        /// method when it constructs the return value.
        ///
        /// It copies the vector that is to be returned to the caller of
        /// \c findAll() for possible subsequent use.  Note that it cannot
        /// simply hold a reference to the vector because the caller may
        /// alter it after the \c findAll() call.
        ///
        /// \param finder The ZoneFinder on which findAll() is called.
        /// \param options See the \c Context class.
        /// \param result See the \c Context class.
        /// \param all_set Reference to the vector given by the caller of
        ///       \c findAll(), storing the RRsets to be returned.
        GenericContext(ZoneFinder& finder, FindOptions options,
                       const ResultContext& result,
                       const std::vector<isc::dns::ConstRRsetPtr>& all_set) :
            Context(options, result), finder_(finder), all_set_(all_set)
        {}

    protected:
        virtual ZoneFinder* getFinder() { return (&finder_); }
        virtual const std::vector<isc::dns::ConstRRsetPtr>*
        getAllRRsets() const {
            return (&all_set_);
        }

    private:
        ZoneFinder& finder_;
        std::vector<isc::dns::ConstRRsetPtr> all_set_;
    };

    ///
    /// \name Constructors and Destructor.
    ///
    //@{
protected:
    /// The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class should
    /// never be instantiated (except as part of a derived class).
    ZoneFinder() {}
public:
    /// The destructor.
    virtual ~ZoneFinder() {}
    //@}

    ///
    /// \name Getter Methods
    ///
    /// These methods should never throw an exception.
    //@{
    /// Return the origin name of the zone.
    virtual isc::dns::Name getOrigin() const = 0;

    /// Return the RR class of the zone.
    virtual isc::dns::RRClass getClass() const = 0;
    //@}

    ///
    /// \name Search Methods
    ///
    //@{
    /// \brief Search the zone for a given pair of domain name and RR type.
    ///
    /// Each derived version of this method searches the underlying backend
    /// for the data that best matches the given name and type.
    /// This method is expected to be "intelligent", and identifies the
    /// best possible answer for the search key.  Specifically,
    ///
    /// - If the search name belongs under a zone cut, it returns the code
    ///   of \c DELEGATION and the NS RRset at the zone cut.
    /// - If there is no matching name, it returns the code of \c NXDOMAIN.
    /// - If there is a matching name but no RRset of the search type, it
    ///   returns the code of \c NXRRSET.  This case includes the search name
    ///   matches an empty node of the zone.
    /// - If there is a CNAME RR of the searched name but there is no
    ///   RR of the searched type of the name (so this type is different from
    ///   CNAME), it returns the code of \c CNAME and that CNAME RR.
    ///   Note that if the searched RR type is CNAME, it is considered
    ///   a successful match, and the code of \c SUCCESS will be returned.
    /// - If the search name matches a delegation point of DNAME, it returns
    ///   the code of \c DNAME and that DNAME RR.
    ///
    /// No RRset will be returned in the \c NXDOMAIN and \c NXRRSET cases
    /// (\c rrset member of \c FindContext will be NULL), unless DNSSEC data
    /// are required.  See below for the cases with DNSSEC.
    ///
    /// The returned \c FindContext object can also provide supplemental
    /// information about the search result via its methods returning a
    /// boolean value.  Such information may be useful for the caller if
    /// the caller wants to collect additional DNSSEC proofs based on the
    /// search result.
    ///
    /// The \c options parameter specifies customized behavior of the search.
    /// Their semantics is as follows (they are or bit-field):
    ///
    /// - \c FIND_GLUE_OK Allow search under a zone cut.  By default the search
    ///   will stop once it encounters a zone cut.  If this option is specified
    ///   it remembers information about the highest zone cut and continues
    ///   the search until it finds an exact match for the given name or it
    ///   detects there is no exact match.  If an exact match is found,
    ///   RRsets for that name are searched just like the normal case;
    ///   otherwise, if the search has encountered a zone cut, \c DELEGATION
    ///   with the information of the highest zone cut will be returned.
    ///   Note: the term "glue" in the DNS protocol standard may sometimes
    ///   cause confusion: some people use this term strictly for an address
    ///   record (type AAAA or A) for the name used in the RDATA of an NS RR;
    ///   some others seem to give it broader flexibility.  Nevertheless,
    ///   in this API the "GLUE OK" simply means the search by find() can
    ///   continue beyond a zone cut; the derived class implementation does
    ///   not have to, and should not, check whether the type is an address
    ///   record or whether the query name is pointed by some NS RR.
    ///   It's up to the caller with which definition of "glue" the search
    ///   result with this option should be used.
    /// - \c FIND_DNSSEC Request that DNSSEC data (like NSEC, RRSIGs) are
    ///   returned with the answer. It is allowed for the data source to
    ///   include them even when not requested.
    /// - \c NO_WILDCARD Do not try wildcard matching.  This option is of no
    ///   use for normal lookups; it's intended to be used to get a DNSSEC
    ///   proof of the non existence of any matching wildcard or non existence
    ///   of an exact match when a wildcard match is found.
    ///
    /// In general, \c name is expected to be included in the zone, that is,
    /// it should be equal to or a subdomain of the zone origin.  Otherwise
    /// this method will return \c NXDOMAIN with an empty RRset.  But such a
    /// case should rather be considered a caller's bug.
    ///
    /// \note For this reason it's probably better to throw an exception
    /// than returning \c NXDOMAIN.  This point should be revisited in a near
    /// future version.  In any case applications shouldn't call this method
    /// for an out-of-zone name.
    ///
    /// <b>DNSSEC considerations:</b>
    /// The result when DNSSEC data are required can be very complicated,
    /// especially if it involves negative result or wildcard match.
    /// Specifically, if an application calls this method for DNS query
    /// processing with DNSSEC data, and if the search result code is
    /// either \c NXDOMAIN or \c NXRRRSET, and/or \c isWildcard() returns
    /// true, then the application will need to find additional NSEC or
    /// NSEC3 records for supplemental proofs.  This method helps the
    /// application for such post search processing.
    ///
    /// First, it tells the application whether the zone is signed with
    /// NSEC or NSEC3 via the \c isNSEC(3)Signed() method.  Any sanely signed
    /// zone should be signed with either (and only one) of these two types
    /// of RRs; however, the application should expect that the zone could
    /// be broken and these methods could both return false.  But this method
    /// should ensure that not both of these methods return true.
    ///
    /// In case it's signed with NSEC3, there is no further information
    /// returned from this method.
    ///
    /// In case it's signed with NSEC, this method will possibly return
    /// a related NSEC RRset in the \c rrset member of \c FindContext.
    /// What kind of NSEC is returned depends on the result code
    /// (\c NXDOMAIN or \c NXRRSET) and on whether it's a wildcard match:
    ///
    /// - In case of NXDOMAIN, the returned NSEC covers the queried domain
    ///   that proves that the query name does not exist in the zone.  Note
    ///   that this does not necessarily prove it doesn't even match a
    ///   wildcard (even if the result of NXDOMAIN can only happen when
    ///   there's no matching wildcard either).  It is caller's
    ///   responsibility to provide a proof that there is no matching
    ///   wildcard if that proof is necessary.
    /// - In case of NXRRSET, we need to consider the following cases
    ///   referring to Section 3.1.3 of RFC4035:
    ///
    /// -# (Normal) no data: there is a matching non-wildcard name with a
    ///    different RR type.  This is the "No Data" case of the RFC.
    /// -# (Normal) empty non terminal: there is no matching (exact or
    ///    wildcard) name, but there is a subdomain with an RR of the query
    ///    name.  This is one case of "Name Error" of the RFC.
    /// -# Wildcard empty non terminal: similar to 2a, but the empty name
    ///    is a wildcard, and matches the query name by wildcard expansion.
    ///    This is a special case of "Name Error" of the RFC.
    /// -# Wildcard no data: there is no exact match name, but there is a
    ///    wildcard name that matches the query name with a different type
    ///    of RR.  This is the "Wildcard No Data" case of the RFC.
    ///
    /// In case 1, \c find() returns NSEC of the matching name.
    ///
    /// In case 2, \c find() will return NSEC for the interval where the
    /// empty nonterminal lives. The end of the interval is the subdomain
    /// causing existence of the empty nonterminal (if there's
    /// sub.x.example.com, and no record in x.example.com, then
    /// x.example.com exists implicitly - is the empty nonterminal and
    /// sub.x.example.com is the subdomain causing it).  Note that this NSEC
    /// proves not only the existence of empty non terminal name but also
    /// the non existence of possibly matching wildcard name, because
    /// there can be no better wildcard match than the exact matching empty
    /// name.
    ///
    /// In case 3, \c find() will return NSEC for the interval where the
    /// wildcard empty nonterminal lives.   Cases 2 and 3 are especially
    /// complicated and confusing.  See the examples below.
    ///
    /// In case 4, \c find() will return NSEC of the matching wildcard name.
    ///
    /// Examples: if zone "example.com" has the following record:
    /// \code
    /// a.example.com. NSEC a.b.example.com.
    /// \endcode
    /// a call to \c find() for "b.example.com." with the FIND_DNSSEC option
    /// will result in NXRRSET, and this NSEC will be returned.
    /// Likewise, if zone "example.org" has the following record,
    /// \code
    /// a.example.org. NSEC x.*.b.example.org.
    /// \endcode
    /// a call to \c find() for "y.b.example.org" with FIND_DNSSEC will
    /// result in NXRRSET and this NSEC; \c isWildcard() on the returned
    /// \c FindContext object will return true.
    ///
    /// \exception std::bad_alloc Memory allocation such as for constructing
    ///  the resulting RRset fails
    /// \throw OutOfZone The Name \c name is outside of the origin of the
    /// zone of this ZoneFinder.
    /// \exception DataSourceError Derived class specific exception, e.g.
    /// when encountering a bad zone configuration or database connection
    /// failure.  Although these are considered rare, exceptional events,
    /// it can happen under relatively usual conditions (unlike memory
    /// allocation failure).  So, in general, the application is expected
    /// to catch this exception, either specifically or as a result of
    /// catching a base exception class, and handle it gracefully.
    ///
    /// \param name The domain name to be searched for.
    /// \param type The RR type to be searched for.
    /// \param options The search options.
    /// \return A \c FindContext object enclosing the search result
    ///         (see above).
    virtual boost::shared_ptr<Context> find(const isc::dns::Name& name,
                                            const isc::dns::RRType& type,
                                            const FindOptions options
                                            = FIND_DEFAULT) = 0;

    /// \brief Search for an RRset of given RR type at the zone origin.
    ///
    /// In terms of API this method is equivalent to a call to \c find() where
    /// the \c name parameter is the zone origin (return value of
    /// \c getOrigin()) and is redundant.  This method is provided as an
    /// optimization point for some kind of finder implementations that can
    /// exploit the fact that the query name is the zone origin and for
    /// applications that want to possibly benefit from such implementations.
    ///
    /// If \c use_minttl is set to \c true and the returned context would
    /// contain a non NULL RRset, its RR TTL is (possibly) adjusted so that
    /// it's set to the minimum of its own TTL and the minimum TTL field value
    /// of the zone's SOA record.  If the RRset contains an RRSIG, its TTL
    /// is also adjusted in the same way.
    ///
    /// The origin of a zone is special in some points: for any valid zone
    /// there should always be an SOA and at least one NS RR there, which
    /// also means the origin name is never empty.  Also, the SOA record can
    /// be used in a DNS response for negative answers, in which case the
    /// RR TTL must be set to minimum of its own RRTTL and the value of the
    /// minimum TTL field.  Although these operations can be performed
    /// through other public interfaces, they can be sometimes suboptimal
    /// in performance or could be more efficient in a specialized
    /// implementation.  For example, a specific implementation of
    /// \c getOrigin() could involve a dynamic creation of a \c Name object,
    /// which is less efficient; on the other hand, the underlying finder
    /// implementation may have an efficient way to access RRs of the origin
    /// in implementation specific way; and, while reconstructing an RRset
    /// with replacing the TTL is relatively expensive, this can be done
    /// much faster if the need for it is known beforehand.
    ///
    /// If the underlying finder implementation wants to optimize these cases,
    /// it can do so by specializing the method.  It has the default
    /// implementation for any other implementations, which should work for
    /// any finder implementation as long as it conforms to other public
    /// interfaces.
    ///
    /// So, an implementation of a finder does not have to care about this
    /// method unless it sees the need for optimizing the behavior.
    /// Also, applications normally do not have to use this interface;
    /// using the generic \c find() method (with some post call processing)
    /// can do everything this method can provide.  The default implementation
    /// may even be slower than such straightforward usage due to the
    /// internal overhead.  This method should be used if and only if the
    /// application needs to achieve the possible best performance with an
    /// optimized finder implementation.
    ///
    /// \param type The RR type to be searched for.
    /// \param use_minttl Whether to adjust the TTL (see the description).
    /// \param options The search options.  Same for \c find().
    ///
    /// \return A \c FindContext object enclosing the search result.
    ///         See \c find().
    virtual boost::shared_ptr<Context> findAtOrigin(
        const isc::dns::RRType& type, bool use_minttl,
        FindOptions options);

public:
    ///
    /// \brief Finds all RRsets in the given name.
    ///
    /// This function works almost exactly in the same way as the find one. The
    /// only difference is, when the lookup is successful (eg. the code is
    /// SUCCESS), all the RRsets residing in the named node are
    /// copied into the \c target parameter and the rrset member of the result
    /// is NULL. All the other (unsuccessful) cases are handled the same,
    /// including returning delegations, NSEC/NSEC3 availability and NSEC
    /// proofs, wildcard information etc. The options parameter works the
    /// same way and it should conform to the same exception restrictions.
    ///
    /// \param name \see find, parameter name
    /// \param target the successfull result is returned through this
    /// \param options \see find, parameter options
    /// \return \see find and it's result
    virtual boost::shared_ptr<Context> findAll(
        const isc::dns::Name& name,
        std::vector<isc::dns::ConstRRsetPtr> &target,
        const FindOptions options = FIND_DEFAULT) = 0;

    /// A helper structure to represent the search result of \c findNSEC3().
    ///
    /// The idea is similar to that of \c FindContext, but \c findNSEC3() has
    /// special interface and semantics, we use a different structure to
    /// represent the result.
    struct FindNSEC3Result {
        FindNSEC3Result(bool param_matched, uint8_t param_closest_labels,
                        isc::dns::ConstRRsetPtr param_closest_proof,
                        isc::dns::ConstRRsetPtr param_next_proof) :
            matched(param_matched), closest_labels(param_closest_labels),
            closest_proof(param_closest_proof),
            next_proof(param_next_proof)
        {}

        /// true iff closest_proof is a matching NSEC3
        const bool matched;

        /// The number of labels of the identified closest encloser.
        const uint8_t closest_labels;

        /// Either the NSEC3 for the closest provable encloser of the given
        /// name or NSEC3 that covers the name
        const isc::dns::ConstRRsetPtr closest_proof;

        /// When non NULL, NSEC3 for the next closer name.
        const isc::dns::ConstRRsetPtr next_proof;
    };

    /// Search the zone for the NSEC3 RR(s) that prove existence or non
    /// existence of a give name.
    ///
    /// It searches the NSEC3 namespace of the zone (how that namespace is
    /// implemented can vary in specific data source implementation) for NSEC3
    /// RRs that match or cover the NSEC3 hash value for the given name.
    ///
    /// If \c recursive is false, it will first look for the NSEC3 that has
    /// a matching hash.  If it doesn't exist, it identifies the covering NSEC3
    /// for the hash.  In either case the search stops at that point and the
    /// found NSEC3 RR(set) will be returned in the closest_proof member of
    /// \c FindNSEC3Result.  \c matched is true or false depending on
    /// the found NSEC3 is a matched one or covering one.  \c next_proof
    /// is always NULL.  closest_labels must be equal to the number of
    /// labels of \c name (and therefore meaningless).
    ///
    /// If \c recursive is true, it will continue the search toward the zone
    /// apex (origin name) until it finds a provable encloser, that is,
    /// an ancestor of \c name that has a matching NSEC3.  This is the closest
    /// provable encloser of \c name as defined in RFC5155.  In this case,
    /// if the found encloser is not equal to \c name, the search should
    /// have seen a covering NSEC3 for the immediate child of the found
    /// encloser.  That child name is the next closer name as defined in
    /// RFC5155.  In this case, this method returns the NSEC3 for the
    /// closest encloser in \c closest_proof, and the NSEC3 for the next
    /// closer name in \c next_proof of \c FindNSEC3Result.  This set of
    /// NSEC3 RRs provide the closest encloser proof as defined in RFC5155.
    /// closest_labels will be set to the number of labels of the identified
    /// closest encloser.  This will be useful when the caller needs to
    /// construct the closest encloser name from the original \c name.
    /// If, on the other hand, the found closest name is equal to \c name,
    /// this method simply returns it in \c closest_proof.  \c next_proof
    /// is set to NULL.  In all cases \c matched is set to true.
    /// closest_labels will be set to the number of labels of \c name.
    ///
    /// When looking for NSEC3, this method retrieves NSEC3 parameters from
    /// the corresponding zone to calculate hash values.  Actual implementation
    /// of how to do this will differ in different data sources.  If the
    /// NSEC3 parameters are not available \c DataSourceError exception
    /// will be thrown.
    ///
    /// \note This implicitly means this method assumes the zone does not
    /// have more than one set of parameters.  This assumption should be
    /// reasonable in actual deployment and will help simplify the interface
    /// and implementation.  But if there's a real need for supporting
    /// multiple sets of parameters in a single zone, we will have to
    /// extend this method so that, e.g., the caller can specify the parameter
    /// set.
    ///
    /// In general, this method expects the zone is properly signed with NSEC3
    /// RRs.  Specifically, it assumes at least the apex node has a matching
    /// NSEC3 RR (so the search in the recursive mode must always succeed);
    /// it also assumes that it can retrieve NSEC parameters (iterations,
    /// algorithm, and salt) from the zone as noted above.  If these
    /// assumptions aren't met, \c DataSourceError exception will be thrown.
    ///
    /// \exception OutOfZone name is not a subdomain of the zone origin
    /// \exception DataSourceError Low-level or internal datasource errors
    /// happened, or the zone isn't properly signed with NSEC3
    /// (NSEC3 parameters cannot be found, no NSEC3s are available, etc).
    /// \exception std::bad_alloc The underlying implementation involves
    /// memory allocation and it fails
    ///
    /// \param name The name for which NSEC3 RRs are to be found.  It must
    /// be a subdomain of the zone.
    /// \param recursive Whether or not search should continue until it finds
    /// a provable encloser (see above).
    ///
    /// \return The search result and whether or not the closest_proof is
    /// a matching NSEC3, in the form of \c FindNSEC3Result object.
    virtual FindNSEC3Result
    findNSEC3(const isc::dns::Name& name, bool recursive) = 0;
    //@}
};

/// \brief Operator to combine FindOptions
///
/// We would need to manually static-cast the options if we put or
/// between them, which is undesired with bit-flag options. Therefore
/// we hide the cast here, which is the simplest solution and it still
/// provides reasonable level of type safety.
inline ZoneFinder::FindOptions operator |(ZoneFinder::FindOptions a,
                                          ZoneFinder::FindOptions b)
{
    return (static_cast<ZoneFinder::FindOptions>(static_cast<unsigned>(a) |
                                                 static_cast<unsigned>(b)));
}

/// \brief Operator to combine FindResultFlags
///
/// Similar to the same operator for \c FindOptions.  Refer to the description
/// of that function.
inline ZoneFinder::FindResultFlags operator |(
    ZoneFinder::FindResultFlags a,
    ZoneFinder::FindResultFlags b)
{
    return (static_cast<ZoneFinder::FindResultFlags>(
                static_cast<unsigned>(a) | static_cast<unsigned>(b)));
}

/// \brief A pointer-like type pointing to a \c ZoneFinder object.
typedef boost::shared_ptr<ZoneFinder> ZoneFinderPtr;

/// \brief A pointer-like type pointing to an immutable \c ZoneFinder object.
typedef boost::shared_ptr<const ZoneFinder> ConstZoneFinderPtr;

/// \brief A pointer-like type pointing to a \c ZoneFinder::Context object.
typedef boost::shared_ptr<ZoneFinder::Context> ZoneFinderContextPtr;

/// \brief A pointer-like type pointing to an immutable
/// \c ZoneFinder::Context object.
typedef boost::shared_ptr<ZoneFinder::Context> ConstZoneFinderContextPtr;

} // end of datasrc
} // end of isc

#endif  // DATASRC_ZONE_FINDER_H

// Local Variables:
// mode: c++
// End:
