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

#ifndef DATASRC_MEMORY_ZONE_DATA_H
#define DATASRC_MEMORY_ZONE_DATA_H 1

#include <util/memory_segment.h>

#include <dns/name.h>
#include <dns/rrclass.h>

#include <datasrc/memory/domaintree.h>
#include <datasrc/memory/rdataset.h>

#include <boost/interprocess/offset_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <vector>

namespace isc {
namespace dns {
namespace rdata {
namespace generic {
class NSEC3PARAM;
class NSEC3;
}
}
}

namespace datasrc {
namespace memory {

typedef DomainTree<RdataSet> ZoneTree;
typedef DomainTreeNode<RdataSet> ZoneNode;

/// \brief NSEC3 data for a DNS zone.
///
/// This class encapsulates a set of NSEC3 related data for a zone
/// that is signed with NSEC3 RRs.  Specifically, it contains hash
/// parameters as given in an NSEC3PARAM RDATA and all NSEC3 RRs of the zone.
///
/// The main concept of the class is generally the same as that of
/// \c ZoneData (see its description for details), but the related data
//// are encapsulated in a more straightforward way in this class.
///
/// The NSEC3 RRs (which should normally have RRSIGs) are stored in a
/// \c DomainTree object whose data type is (a list of) \c RdataSet.
/// This tree is expected to store NSEC3 RRs only, so the RR type of
/// \c RdataSet should be NSEC3.  But this class itself doesn't guarantee
/// this condition.  It's the caller's responsibility.
///
/// Read-only access to the tree is possible via the \c getNSEC3Tree() method.
/// Modifying the tree must be done by specific method; the application
/// cannot directly change the content of the tree in an arbitrary way.
/// This class does not have a strong reason to be that strict, but is
/// defined this way mainly to be consistent with the \c ZoneData class.
///
/// Most of the hash parameters are maintained in the form of straightforward
/// member variables, which can be directly referenced by the application.
/// The exception is the salt, which is encapsulated as opaque data
/// immediately following the main class object, and should be accessible
/// via the \c getSaltLen() and \c getSaltData() method.
///
/// \note The fact that the this class couples one set of hash parameters
/// and the set of NSEC3 RRs implicitly means a zone is assumed to have
/// only one set of NSEC3 parameters.  When we support multiple sets of
/// parameters the design should be revised accordingly.
class NSEC3Data : boost::noncopyable {
public:
    /// \brief Allocate and construct \c NSEC3Data from NSEC3PARAM Rdata.
    ///
    /// The NSEC3 parameters are extracted and stored within the created
    /// \c NSEC3Data object.
    ///
    /// \throw std::bad_alloc Memory allocation fails.
    ///
    /// \param mem_sgmt A \c MemorySegment from which memory for the new
    /// \c NSEC3Data is allocated.
    /// \param rdata An NSEC3PARAM RDATA that specifies the NSEC3 parameters
    /// to be stored.
    static NSEC3Data* create(util::MemorySegment& mem_sgmt,
                             const dns::rdata::generic::NSEC3PARAM& rdata);

    /// \brief Allocate and construct \c NSEC3Data from NSEC3 Rdata.
    ///
    /// The NSEC3 hash parameters are extracted and stored within the created
    /// \c NSEC3Data object.
    ///
    /// \throw std::bad_alloc Memory allocation fails.
    ///
    /// \param mem_sgmt A \c MemorySegment from which memory for the new
    /// \c NSEC3Data is allocated.
    /// \param rdata An NSEC3 RDATA that specifies the NSEC3 parameters
    /// to be stored.
    static NSEC3Data* create(util::MemorySegment& mem_sgmt,
                             const dns::rdata::generic::NSEC3& rdata);

    /// \brief Destruct and deallocate \c NSEC3Data.
    ///
    /// It releases all resources allocated for the internal NSEC3 name space
    /// including NSEC3 RdataSet.  It assumes \c RdataSets objects stored
    /// in the space were allocated using the same memory segment as
    /// \c mem_sgmt.  The caller must ensure this assumption.
    ///
    /// Note that an \c RRClass object must be passed to this method.
    /// It's necessary to destroy the stored \c RdataSet objects
    /// (see its class description).  This class doesn't hold this information;
    /// it's the caller's responsibility to associate an \c NSEC3Data
    /// class object with its expected RR class, and pass it to
    /// \c destroy().  (In practice, it will be passed via
    /// \c ZoneData::destroy().)
    ///
    /// \throw none
    ///
    /// \param mem_sgmt The \c MemorySegment that allocated memory for
    /// \c data.
    /// \param data A non-NULL pointer to a valid NSEC3Data object
    /// that was originally created by the \c create() method (the behavior
    /// is undefined if this condition isn't met).
    /// \param nsec3_class The RR class of the \c RdataSet stored in the NSEC3
    /// name space to be destroyed.
    static void destroy(util::MemorySegment& mem_sgmt, NSEC3Data* data,
                        dns::RRClass nsec3_class);

private:
    // Domain tree for the Internal NSEC3 name space.  Access to it is
    // limited only via public methods.
    const boost::interprocess::offset_ptr<ZoneTree> nsec3_tree_;
public:
    const uint8_t hashalg;      ///< Hash algorithm
    const uint8_t flags;        ///< NSEC3 parameter flags
    const uint16_t iterations;  ///< Hash iterations
    // For 64-bit machines there'll be padding space here, but since
    // only at most one instance (or a few in very rare cases) will be
    // created per zone, the overhead should be acceptable.

    /// \brief Return \c ZoneTree for the NSEC3 name space.
    ///
    /// \throw none
    const ZoneTree& getNSEC3Tree() const { return (*nsec3_tree_); }

    /// \brief Return the size of NSEC3 salt.
    ///
    /// \throw none
    ///
    /// The return value must be in the range between 0 and 255 (inclusive).
    size_t getSaltLen() const { return (*getSaltBuf()); }

    /// \brief Return a pointer to the salt data.
    ///
    /// \throw none
    ///
    /// The valid range is up to the \c getSaltLen() bytes from the
    /// returned value.  If \c getSaltLen() returns 0, the return value
    /// of this method is invalid and must not be used.
    const uint8_t* getSaltData() const { return (getSaltBuf() + 1); }

    /// \brief Insert a name to the NSEC3 name space.
    ///
    /// It allocates resource for the given name in the internal NSEC3 name
    /// space, and returns an access point to it in the form of \c ZoneNode
    /// pointer via the given \c node variable.  If the name already exists
    /// in the name space, it returns a pointer to the existing node.
    ///
    /// This method does not perform any semantics check on the given name
    /// (e.g., whether the first label is a valid encoded string for an NSEC3
    /// owner name).
    ///
    /// \throw std::bad_alloc Memory allocation fails
    ///
    /// \param mem_sgmt Memory segment in which resource for the new memory
    /// is to be allocated.
    /// \param name The name to be inserted.
    /// \param node A pointer to \c ZoneNode pointer in which the created or
    /// found node for the name is stored.  Must not be NULL (the method does
    /// not check that condition).
    void insertName(util::MemorySegment& mem_sgmt, const dns::Name& name,
                    ZoneNode** node);

private:
    // Common subroutine for the public versions of create().
    static NSEC3Data* create(util::MemorySegment& mem_sgmt, uint8_t hashalg,
                             uint8_t flags, uint16_t iterations,
                             const std::vector<uint8_t>& salt);

    /// \brief The constructor.
    ///
    /// An object of this class is always expected to be created by the
    /// allocator (\c create()), so the constructor is hidden as private.
    ///
    /// It never throws an exception.
    NSEC3Data(ZoneTree* nsec3_tree_param, uint8_t hashalg_param,
              uint8_t flags_param, uint16_t iterations_param) :
        nsec3_tree_(nsec3_tree_param), hashalg(hashalg_param),
        flags(flags_param), iterations(iterations_param)
    {}

    const uint8_t* getSaltBuf() const {
        return (reinterpret_cast<const uint8_t*>(this + 1));
    }
    uint8_t* getSaltBuf() {
        return (reinterpret_cast<uint8_t*>(this + 1));
    }
};

/// \brief DNS zone data.
///
/// This class encapsulates the content of a DNS zone (which is essentially a
/// set of RRs) in a memory efficient way and provides accessor interfaces
/// to it.
///
/// The primary goal of this class is to provide a packed structure of the
/// data for memory efficiency.  Basically, this class should be considered
/// a private part of some other classes within this module and should not
/// be used directly from normal applications.  So it's not intended to hide
/// much of the underlying implementation details; rather, it tries
/// to keep the representation simple.
///
/// The RRs are stored in a \c DomainTree object whose data type is
/// (a list of) \c RdataSet.  The tree nodes correspond to owner names,
/// and the \c RdataSet objects (forming a linked list) set in the node
/// represent the rest of the RR parameters except the RR class: type,
/// TTL, and RDATA.  This class does not have any knowledge of the RR class
/// of the zone; since it's quite likely that the application maintains
/// a set of zones of the same RR class, and the number of such zones can be
/// huge, it makes more sense to have the application maintain the class value
/// in a unified way to minimize memory footprint.
///
/// The \c DomainTree object in this class is not expected to hold NSEC3
/// RRs when the zone is signed with NSEC3; they should be maintained
/// in an associated \c NSEC3Data object.  But this class does not prevent
/// the unexpected usage of adding an NSEC3 RdataSet directly in the tree.
/// It's the caller's responsibility to ensure this assumption.
///
/// This class maintains some other meta data and additional zone related
/// content.  First, it automatically creates a \c DomainTree node for the
/// zone's origin name on initialization and keeps a reference to it
/// throughout its lifetime.  This is the case even if the zone doesn't have
/// any RRs (such as in the case before initial loading).  Any valid zone
/// to be served should have an RR at the origin node (at least SOA, for
/// example), so this assumption should be reasonable.  But the application
/// must ensure that any \c ZoneData object in actual use should have an
/// RR at the origin; otherwise the inconsistency between the internal state
/// and the actual zone content could lead to unexpected disruption.
/// In particular, it must be careful when it supports dynamic updates
/// to an existing zone so an update attempt doesn't result in deleting
/// the origin node.
///
/// To ensure integrity regarding the reference to the origin, write
/// access to the tree node can be done only by public methods; the member
/// variable for the tree is hidden as private.  On the other hand, read-only
/// access to the tree is allowed via the const version of \c getZoneTree()
/// method for the convenience of the application.  So, it's intentional
/// that there's no non-const version of this method.  Do not add one
/// when this class is to be extended.
///
/// Another type of meta data is parameters and records of NSEC3 RRs
/// when the zone is signed with NSEC3.  It's represented in the form of
/// an \c NSEC3Data object, and a \c ZoneData object may be associated with
/// 0 or 1 \c NSEC3Data objects using the \c setNSEC3Data() method, which
/// can be retrieved by the \c getNSEC3Data() method.  If the \c ZoneData
/// object is not associated with an \c NSEC3Data object, it's considered not
/// signed with NSEC3 RRs; otherwise it's considered to be signed with
/// NSEC3 RRs and with the parameters stored in the \c NSEC3Data object.
///
/// \note This interpretation may change in the future when we support migration
/// from NSEC to NSEC3 or vice versa, support incremental signing, or support
/// multiple sets of NSEC3 parameters.
///
/// One last type of meta data is the status of the zone in terms of DNSSEC
/// signing.  This class supports the following concepts:
/// - Whether the zone is signed or not, either with NSEC records or NSEC3
///   records.
/// - Whether the zone has a complete set of NSEC3 records.
///
/// The former status can be accessed via the \c isSigned() and \c setSigned()
/// methods; the latter can be retrieved via the \c isNSEC3Signed() method.
///
/// This class does not actually relate the status of signed-or-not to
/// any of its other attributes; it's up to the application how to set or
/// use this status and maintain it in a reasonable way.  One possible
/// definition is to set this status if and only if the zone has a
/// DNSKEY RR at the zone origin (which is BIND 9's definition of signed
/// zone).  When the application adopts this definition, it's the
/// application's responsibility to keep the status consistent with the
/// actual existence or non-existence of a DNSKEY RR.
///
/// In the current implementation, a zone is considered to have a complete
/// set of NSEC3 records if and only if it's associated with an \c NSEC3Data
/// object (as noted above, these concepts may be separated in future).
/// For this reason there is no "set" method for the latter; setting
/// an \c NSEC3Data effectively enables the latter status.  \c isNSEC3Signed()
/// method is still provided (even though it's a kind of trivial wrapper to
/// \c getNSEC3Data()) partly for a more intuitive shortcut, and partly
/// because we won't have to change the application code when we implement
/// the future separation.
///
/// The intended usage of these two status concepts is to implement the
/// \c ZoneFinder::Context::isNSECSigned() and
/// \c ZoneFinder::Context::isNSEC3Signed() methods.  A possible implementation
/// is as follows:
/// - \c ZoneFinder::Context::isNSECSigned() returns true iff \c isSigned()
///   is true and \c isNSEC3Signed() is false.
/// - \c ZoneFinder::Context::isNSEC3Signed() returns true iff \c isSigned()
///   is true and \c isNSEC3Signed() is true.
///
/// Note that even though \c isNSEC3Signed() being true should indicate
/// \c isSigned() is true too in practice, the interfaces do not
/// automatically ensure that, so we'd need to check both conditions
/// explicitly.  And, in fact, if we adopt the above definition of
/// \c isSigned(), it's possible that a zone has a complete set of NSEC3
/// RRs but no DNSKEY (although it's effectively a broken zone unless we
/// support incremental signing).
///
/// This class is designed so an instance can be stored in a shared
/// memory region.  So the pointer member variables (the initial
/// implementation only contains pointer member variables) are defined
/// as offset pointers.  When this class is extended these properties must
/// be preserved, and must also meet other requirements so it can be stored
/// in a shared memory region (see, for example, \c RdataSet description).
/// Future extensions must also be conscious of placing the member variables
/// so that they will not accidentally cause padding and increase memory
/// footprint.
class ZoneData : boost::noncopyable {
private:
    /// \brief The constructor.
    ///
    /// An object of this class is always expected to be created by the
    /// allocator (\c create()), so the constructor is hidden as private.
    ///
    /// It never throws an exception.
    ZoneData(ZoneTree* zone_tree, ZoneNode* origin_node) :
        zone_tree_(zone_tree), origin_node_(origin_node)
    {}

    // Zone node flags.
private:
    // Set in the origin node (which always exists at the same address)
    // to indicate whether the zone is signed or not.  Internal use,
    // so defined as private.
    static const ZoneNode::Flags DNSSEC_SIGNED = ZoneNode::FLAG_USER1;
public:
    /// \brief Node flag indicating it is at a "wildcard level"
    ///
    /// This means one of the node's immediate children is a wildcard.
    static const ZoneNode::Flags WILD_NODE = ZoneNode::FLAG_USER2;

public:
    /// \brief Allocate and construct \c ZoneData.
    ///
    /// \throw std::bad_alloc Memory allocation fails.
    ///
    /// \param mem_sgmt A \c MemorySegment from which memory for the new
    /// \c ZoneData is allocated.
    /// \param name The zone name.
    static ZoneData* create(util::MemorySegment& mem_sgmt,
                            const dns::Name& zone_name);

    /// \brief Destruct and deallocate \c ZoneData.
    ///
    /// It releases all resource allocated in the internal storage NSEC3 for
    /// zone names and RdataSet objects, and if associated, the \c NSEC3Data.
    /// It assumes \c RdataSets objects stored in the space and the
    /// associated \c NSEC3Data object were allocated using the same memory
    /// segment as \c mem_sgmt.  The caller must ensure this assumption.
    ///
    /// Note that an \c RRClass object must be passed to this method.
    /// It's used to destroy the stored \c RdataSet objects
    /// (see its class description).  This class doesn't hold this information;
    /// it's the caller's responsibility to associate a \c ZoneData class object
    /// with its expected RR class, and pass it to \c destroy().
    ///
    /// \throw none
    ///
    /// \param mem_sgmt The \c MemorySegment that allocated memory for
    /// \c zone_data.
    /// \param zone_data A non-NULL pointer to a valid ZoneData object
    /// that was originally created by the \c create() method (the behavior
    /// is undefined if this condition isn't met).
    /// \param zone_class The RR class of the \c RdataSet stored in the
    /// internal tree.
    static void destroy(util::MemorySegment& mem_sgmt, ZoneData* zone_data,
                        dns::RRClass zone_class);

    /// \brief Return zone's origin node.
    ///
    /// This is a convenience and efficient short cut to get access to the
    /// zone origin in the form of \c ZoneNode object.
    ///
    /// The class encapsulation ensures that the origin node always exists at
    /// the same address, so this method always returns a non-NULL valid
    /// valid pointer.
    ///
    /// \throw none
    const ZoneNode* getOriginNode() const {
        return (origin_node_.get());
    }

    /// \brief Return the zone's name space in the form of \c ZoneTree
    ///
    /// \note It's intentional that non-const version of this method
    /// isn't provided.  See the class description.
    ///
    /// \throw none
    const ZoneTree& getZoneTree() const { return (*zone_tree_); }

    /// \brief Return whether or not the zone is signed in terms of DNSSEC.
    ///
    /// Note that this class does not care about what "signed" means.
    /// This method simply returns the last value set by \c setSigned()
    /// (or the default, which is \c false).  The caller is expected to
    /// use this method and \c setSigned() in a reasonable, consistent way.
    ///
    /// \throw none
    bool isSigned() const { return (origin_node_->getFlag(DNSSEC_SIGNED)); }

    /// \brief Return whether or not the zone is signed with NSEC3 RRs.
    ///
    /// In the current implementation, the zone is considered signed with
    /// NSEC3 if and only if it has non-NULL NSEC3 data.
    ///
    /// This also means it's not considered NSEC3 signed by default.
    ///
    /// \throw none
    bool isNSEC3Signed() const { return (nsec3_data_); }

    /// \brief Return NSEC3Data of the zone.
    ///
    /// This method returns non-NULL valid pointer to \c NSEC3Data object
    /// associated to the \c ZoneData if it was set by \c setNSEC3Data();
    /// otherwise it returns NULL.
    ///
    /// \throw none
    const NSEC3Data* getNSEC3Data() const { return (nsec3_data_.get()); }

    /// \brief Insert a name to the zone.
    ///
    /// It allocates resource for the given name in the internal storage
    /// for zone data, and returns an access point to it in the form of
    /// \c ZoneNode pointer via the given \c node variable.  If the name
    /// already exists in the name space, it returns a pointer to the existing
    /// node.
    ///
    /// The name to be inserted by this method is expected to belong to
    /// zone's "normal" (i.e., non-NSEÇ3) name space.  If it's a name for
    /// an NSEC3 RR, it must be set in the corresponding \c NSEC3Data for
    /// this zone data (if it doesn't exist it must be created and set
    /// by \c setNSEC3Data()).
    ///
    /// The name is also expected to be a subdomain of, or equal to the
    /// zone's origin name (specified on creation in \c create()), but
    /// this method does not check that condition.  The caller is responsible
    /// for ensuring this assumption.
    ///
    /// Since this method doesn't perform any semantics check, it always
    /// succeeds (except for the rare case where memory allocation
    /// fails) and \c node will be set to a valid pointer.
    ///
    /// \note We may want to differentiate between the case where the name is
    /// newly created and the case where it already existed.  Right now it's
    /// unclear, so it doesn't return this information.  If we see the need
    /// for it, this method can be extended that way.
    ///
    /// \throw std::bad_alloc Memory allocation fails
    ///
    /// \param mem_sgmt Memory segment in which resource for the new memory
    /// is to be allocated.
    /// \param name The name to be inserted.
    /// \param node A pointer to \c ZoneNode pointer in which the created or
    /// found node for the name is stored.  Must not be NULL (the method does
    /// not check that condition).
    void insertName(util::MemorySegment& mem_sgmt, const dns::Name& name,
                    ZoneNode** node);

    /// \brief Specify whether or not the zone is signed in terms of DNSSEC.
    ///
    /// The zone will be considered "signed" (in that subsequent calls to
    /// \c isSigned() will return \c true) iff the parameter \c on is \c true.
    ///
    /// This class does not care what "signed" actually means; it does not
    /// check any zone RRs to verify if the given state makes sense (e.g.
    /// whether the zone has a DNSKEY RR at the origin).  The caller is
    /// expected to use this method and \c isSigned() in a reasonable,
    /// consistent way.
    ///
    /// \throw none
    void setSigned(bool on) {
        origin_node_->setFlag(DNSSEC_SIGNED, on);
    }

    /// \brief Return NSEC3Data of the zone, non-const version.
    ///
    /// This is similar to the const version, but return a non-const pointer
    /// so the caller can modify the content.
    ///
    /// \throw none
    NSEC3Data* getNSEC3Data() { return (nsec3_data_.get()); }

    /// \brief Associate \c NSEC3Data to the zone.
    ///
    /// This method associates the given \c NSEC3Data object with the zone
    /// data.  If there was already associated \c NSEC3Data object, it will
    /// be returned.  If no \c NSEC3Data object was associated before,
    /// a NULL pointer will be returned.  \c nsec3_data can be NULL, in which
    /// case the zone will be disassociated with a \c NSEC3Data.
    ///
    /// In general, if a non-NULL pointer is passed, it's assumed that
    /// the \c NSEC3Data object was allocated in the same \c MemorySegment
    /// as that for the zone data, so the \c destroy() method can destroy
    /// both with the same memory segment.  If this condition is not met,
    /// the caller must extract the associated \c NSEC3Data by calling
    /// this method with NULL and release any resource for it by itself
    /// before destroying this zone data.
    ///
    /// \throw none
    ///
    /// \param nsec3_data A pointer to \c NSEC3Data object to be associated
    /// with the zone.  Can be NULL.
    /// \return Previously associated \c NSEC3Data object in the zone.  This
    /// can be NULL.
    NSEC3Data* setNSEC3Data(NSEC3Data* nsec3_data) {
        NSEC3Data* old = nsec3_data_.get();
        nsec3_data_ = nsec3_data;
        return (old);
    }

private:
    const boost::interprocess::offset_ptr<ZoneTree> zone_tree_;
    const boost::interprocess::offset_ptr<ZoneNode> origin_node_;
    boost::interprocess::offset_ptr<NSEC3Data> nsec3_data_;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_ZONE_DATA_H

// Local Variables:
// mode: c++
// End:
