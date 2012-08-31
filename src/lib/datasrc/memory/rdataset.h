// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DATASRC_MEMORY_RDATASET_H
#define DATASRC_MEMORY_RDATASET_H 1

#include <util/memory_segment.h>

#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>

#include <boost/interprocess/offset_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <stdint.h>

namespace isc {
namespace datasrc {
namespace memory {
class RdataEncoder;

/// \brief General error on creating RdataSet.
///
/// This is thrown when creating \c RdataSet encounters a rare, unsupported
/// situation.
class RdataSetError : public Exception {
public:
    RdataSetError(const char* file, size_t line, const char* what) :
        Exception(file, line, what) {}
};

/// \brief Memory-efficient representation of RRset data with RRSIGs.
///
/// This class provides memory-efficient and lightweight interface to various
/// attributes of an RRset, which may or may not be signed with RRSIGs.
///
/// This class is primarily intended to be used in the in-memory data source
/// implementation, and is not supposed to be used by general applications.
/// The major design goals is to keep required memory footprint for the given
/// amount of data as small as possible, while providing a reasonably
/// efficient interface to examine the data, focusing on zone lookup and DNS
/// message rendering.
///
/// It encodes a specific set of RRset and (when signed) its RRSIGs, excluding
/// the owner name and the RR class.  The owner name is supposed to be
/// maintained by the application outside this class (the intended place to
/// store this information is a \c DomainTree node, although this
/// implementation does not rely on that intent).  The RR class must be the
/// same in a single zone, and it's simply a waste if we have it with each
/// RRset.  The RR class information is therefore expected to be maintained
/// outside this class.
///
/// This class imposes some limitations on the number of RDATAs of the RRset
/// and RRSIG: a (non RRSIG) RRset containing more than 8191 (2^13 - 1)
/// or an RRSIG containing more than 65535 (2^16 - 1) RDATAs cannot be
/// maintained in this class.  The former restriction comes from the
/// following observation: any RR in wire format in a DNS message must at
/// least contain 10 bytes of data (for RR type, class, TTL and RDATA length),
/// and since a valid DNS message must not be larger than 65535 bytes,
/// no valid DNS response can contain more than 6554 RRs.  So, in practice,
/// it should be reasonable even if we reject very large RRsets that would
/// not fit in a DNS message.  For the same reason we restrict the number of
/// RRSIGs, although due to internal implementation details the limitation
/// is more relaxed for RRSIGs.
///
/// \note (This is pure implementation details) By limiting the number of
/// RDATAs so it will fit in a 13-bit integer, we can use 3 more bits in a
/// 2-byte integer for other purposes.  We use this additional field to
/// represent the number of RRSIGs up to 6, while using the value of 7 to mean
/// there are more than 6 RRSIGs.  In the vast majority of real world
/// deployment, an RRset should normally have only a few RRSIGs, and 6 should
/// normally be more than sufficient.  So we can cover most practical cases
/// regarding the number of records with this 2-byte field.
///
/// A set of objects of this class (which would be \c RdataSets of various
/// types of the same owner name) will often be maintained in a single linked
/// list.  The class has a member variable to make the link.
///
/// This class is designed so an instance can be stored in a shared
/// memory region.  So it only contains straightforward data (e.g., it
/// doesn't hold a pointer to an object of some base class that
/// contains virtual methods), and the pointer member (see the
/// previous paragraph) is represented as an offset pointer.  For the
/// same reason this class should never have virtual methods (and as a
/// result, should never be inherited in practice).  When this class
/// is extended these properties must be preserved.
///
/// The \c RdataSet class itself only contains a subset of attributes that
/// it is conceptually expected to contain.  The rest of the attributes
/// are encoded in a consecutive memory region immediately following the main
/// \c RdataSet object.  The memory layout would be as follows:
/// \verbatim
/// RdataSet object
/// (optional) uint16_t: number of RRSIGs, if it's larger than 6 (see above)
/// encoded RDATA (generated by RdataEncoder) \endverbatim
///
/// This is shown here only for reference purposes.  The application must not
/// assume any particular format of data in this region directly; it must
/// get access to it via public interfaces provided in the main \c RdataSet
/// class.
class RdataSet : boost::noncopyable {
public:
    /// \brief Allocate and construct \c RdataSet
    ///
    /// This static method allocates memory for a new \c RdataSet
    /// object for the set of an RRset and (if it's supposed to be signed)
    /// RRSIG from the given memory segment, constructs the object, and
    /// returns a pointer to it.
    ///
    /// Normally the (non RRSIG) RRset is given (\c rrset is not NULL) while
    /// its RRSIG (\c sig_rrset) may or may not be provided.  But it's also
    /// expected that in some rare (mostly broken) cases there can be an RRSIG
    /// RR in a zone without having the covered RRset in the zone.  To handle
    /// such cases, this class allows to only hold RRSIG, in which case
    /// \c rrset can be NULL.  At least \c rrset or \c sig_rrset must be
    /// non NULL, however.  Also, if non NULL, the RRset must not be empty,
    /// that is, it must contain at least one RDATA.
    ///
    /// The RR type of \c rrset must not be RRSIG; the RR type of \c sig_rrset
    /// must be RRSIG.
    ///
    /// When both \c rrset and \c sig_rrset are provided (both are non
    /// NULL), the latter must validly cover the former: the RR class
    /// must be identical; the type covered field of any RDATA of \c
    /// sig_rrset must be identical to the RR type of \c rrset.  The owner
    /// name of these RRsets must also be identical, but this implementation
    /// doesn't require it because \c RdataSet itself does not rely on the
    /// owner name, and it should be pretty likely that this condition is met
    /// in the context where this class is used (and, name comparison is
    /// relatively expensive, and if we end up comparing them twice the
    /// overhead can be non negligible).
    ///
    /// If any of the above conditions isn't met, an isc::BadValue exception
    /// will be thrown; basically, there should be a bug in the caller if this
    /// happens.
    ///
    /// Due to implementation limitations, this class cannot contain more than
    /// 8191 RDATAs for the non RRISG RRset; also, it cannot contain more than
    /// 65535 RRSIGs.  If the given RRset(s) fail to meet this condition,
    /// an \c RdataSetError exception will be thrown.
    ///
    /// \throw isc::BadValue Given RRset(s) are invalid (see the description)
    /// \throw RdataSetError Number of RDATAs exceed the limits
    /// \throw std::bad_alloc Memory allocation fails.
    ///
    /// \param mem_sgmt A \c MemorySegment from which memory for the new
    /// \c RdataSet is allocated.
    /// \param encoder The RDATA encoder to encode \c rrset and \c sig_rrset
    /// with the \c RdataSet to be created.
    /// \param rrset A (non RRSIG) RRset from which the \c RdataSet is to be
    /// created.  Can be NULL if sig_rrset is not.
    /// \param sig_rrset An RRSIG RRset from which the \c RdataSet is to be
    /// created.  Can be NULL if rrset is not.
    ///
    /// \return A pointer to the created \c RdataSet.
    static RdataSet* create(util::MemorySegment& mem_sgmt,
                            RdataEncoder& encoder,
                            dns::ConstRRsetPtr rrset,
                            dns::ConstRRsetPtr sig_rrset);

    /// \brief Destruct and deallocate \c RdataSet
    ///
    /// Note that this method needs to know the expected RR class of the
    /// \c RdataSet.  This is because the destruction may depend on the
    /// internal data encoding that only \c RdataEncoder and \c RdataReader
    /// know, and they need to know the corresponding RR class and type to
    /// identify the internal data representation.  Since \c RdataSet itself
    /// does not hold the class information, the caller needs to provide it.
    /// Obviously, this RR class must be identical to the RR class of \c rrset
    /// (when given) or of \c sig_rrset (when \c rrset isn't given) at the
    /// \c create() time.
    ///
    /// \throw none
    ///
    /// \param mem_sgmt The \c MemorySegment that allocated memory for
    /// \c node.
    /// \param rrclass The RR class of the \c RdataSet to be destroyed.
    /// \param rdataset A non NULL pointer to a valid \c RdataSet object
    /// that was originally created by the \c create() method (the behavior
    /// is undefined if this condition isn't met).
    static void destroy(util::MemorySegment& mem_sgmt, dns::RRClass rrclass,
                        RdataSet* rdataset);

    /// \brief Find \c RdataSet of given RR type from a list (const version).
    ///
    /// This function is a convenient shortcut for commonly used operation of
    /// finding a given type of \c RdataSet from a linked list of them.
    ///
    /// It follows the linked list of \c RdataSet objects (via their \c next
    /// member) starting the given head, until it finds an object of the
    /// given RR type.  If found, it returns a (bare) pointer to the object;
    /// if not found in the entire list, it returns NULL.  The head pointer
    /// can be NULL, in which case this function will simply return NULL.
    ///
    /// \note This function is defined as a (static) class method to
    /// clarify its an operation for \c RdataSet objects and to make the
    /// name shorter.  But its implementation does not depend on private
    /// members of the class, and it should be kept if and when this method
    /// needs to be extended, unless there's a reason other than simply
    /// because it's already a member function.
    ///
    /// \param rdata_head A pointer to \c RdataSet from which the search
    /// starts.  It can be NULL.
    /// \param type The RRType of \c RdataSet to find.
    /// \return A pointer to the found \c RdataSet or NULL if none found.
    static const RdataSet*
    find(const RdataSet* rdataset_head, const dns::RRType& type) {
        return (find<const RdataSet>(rdataset_head, type));
    }

    /// \brief Find \c RdataSet of given RR type from a list (non const
    /// version).
    ///
    /// This is similar to the const version, except it takes and returns non
    /// const pointers.
    static RdataSet*
    find(RdataSet* rdataset_head, const dns::RRType& type) {
        return (find<RdataSet>(rdataset_head, type));
    }

    typedef boost::interprocess::offset_ptr<RdataSet> RdataSetPtr;
    typedef boost::interprocess::offset_ptr<const RdataSet> ConstRdataSetPtr;

    // Note: the size and order of the members are carefully chosen to
    // maximize efficiency.  Don't change them unless there's strong reason
    // for that and the consequences are considered.
    // For convenience (and since this class is mostly intended to be an
    // internal definition for the in-memory data source implementation),
    // we allow the application to get access to some members directly.
    // Some others require some conversion to use in a meaningful way,
    // for which we force the application to use accessor methods in order
    // to prevent misuse.

    RdataSetPtr next; ///< Pointer to the next \c RdataSet (when linked)
    const dns::RRType type;     ///< The RR type of the \c RdataSet

private:
    const uint16_t sig_rdata_count_ : 3; // # of RRSIGs, up to 6 (7 means many)
    const uint16_t rdata_count_ : 13; // # of RDATAs, up to 8191
    const uint32_t ttl_;       // TTL of the RdataSet, net byte order

    // Max number of normal RDATAs that can be stored in \c RdataSet.
    // It's 2^13 - 1 = 8191.
    static const size_t MAX_RDATA_COUNT = (1 << 13) - 1;

    // Max number of RRSIGs that can be stored in \c RdataSet.
    // It's 2^16 - 1 = 65535.
    static const size_t MAX_RRSIG_COUNT = (1 << 16) - 1;

    // Indicate the \c RdataSet contains many RRSIGs that require an additional
    // field for the real number of RRSIGs.  It's 2^3 - 1 = 7.
    static const size_t MANY_RRSIG_COUNT = (1 << 3) - 1;

public:
    /// \brief Return the bare pointer to the next node.
    ///
    /// In such an operation as iterating over a linked list of \c RdataSet
    /// object, using this method is generally more efficient than using
    /// the \c next member directly because it prevents unintentional
    /// creation of offset pointer objects.  While the application can
    /// get the same result by directly calling get() on \c next, it would
    /// help encourage the use of more efficient usage if we provide an
    /// explicit accessor.
    const RdataSet* getNext() const { return (next.get()); }

    /// \brief Return the bare pointer to the next node, mutable version.
    RdataSet* getNext() { return (next.get()); }

    /// \brief Return the number of RDATAs stored in the \c RdataSet.
    size_t getRdataCount() const { return (rdata_count_); }

    /// \brief Return the number of RRSIG RDATAs stored in the \c RdataSet.
    size_t getSigRdataCount() const {
        if (sig_rdata_count_ < MANY_RRSIG_COUNT) {
            return (sig_rdata_count_);
        } else {
            return (*getExtSIGCountBuf());
        }
    }

    /// \brief Return a pointer to the TTL data of the \c RdataSet.
    ///
    /// The returned pointer points to a memory region that is valid at least
    /// for 32 bits, storing the TTL of the \c RdataSet in the network byte
    /// order.  It returns opaque data to make it clear that unless the wire
    /// format data is necessary (e.g., when rendering it in a DNS message),
    /// it should be converted to, e.g., an \c RRTTL object explicitly.
    ///
    /// \throw none
    const void* getTTLData() const { return (&ttl_); }

    /// \brief Accessor to the memory region for encoded RDATAs.
    ///
    /// The only valid usage of the returned pointer is to pass it to
    /// the constructor of \c RdataReader.
    ///
    /// \throw none
    const void* getDataBuf() const {
        return (getDataBuf<const void, const RdataSet>(this));
    }

private:
    /// \brief Accessor to the memory region for encoded RDATAs, mutable
    /// version.
    ///
    /// This version is only used within the class implementation, so it's
    /// defined as private.
    void* getDataBuf() {
        return (getDataBuf<void, RdataSet>(this));
    }

    // Implementation of getDataBuf().  Templated to unify the mutable and
    // immutable versions.
    template <typename RetType, typename ThisType>
    static RetType* getDataBuf(ThisType* rdataset) {
        if (rdataset->sig_rdata_count_ < MANY_RRSIG_COUNT) {
            return (rdataset + 1);
        } else {
            return (rdataset->getExtSIGCountBuf() + 1);
        }
    }

    /// \brief Accessor to the memory region for the RRSIG count field for
    /// a large number of RRSIGs.
    ///
    /// These are used only internally and defined as private.
    const uint16_t* getExtSIGCountBuf() const {
        return (reinterpret_cast<const uint16_t*>(this + 1));
    }
    uint16_t* getExtSIGCountBuf() {
        return (reinterpret_cast<uint16_t*>(this + 1));
    }

    // Shared by both mutable and immutable versions of find()
    template <typename RdataSetType>
    static RdataSetType*
    find(RdataSetType* rdataset_head, const dns::RRType& type) {
        for (RdataSetType* rdataset = rdataset_head;
             rdataset != NULL;
             rdataset = rdataset->getNext()) // use getNext() for efficiency
        {
            if (rdataset->type == type) {
                return (rdataset);
            }
        }
        return (NULL);
    }

    /// \brief The constructor.
    ///
    /// An object of this class is always expected to be created by the
    /// allocator (\c create()), so the constructor is hidden as private.
    ///
    /// It never throws an exception.
    RdataSet(dns::RRType type, size_t rdata_count, size_t sig_rdata_count,
             dns::RRTTL ttl);

    /// \brief The destructor.
    ///
    /// An object of this class is always expected to be destroyed explicitly
    /// by \c destroy(), so the destructor is hidden as private.
    ///
    /// This currently does nothing, but is explicitly defined to clarify
    /// it's intentionally defined as private.
    ~RdataSet() {}
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_RDATASET_H

// Local Variables:
// mode: c++
// End:
