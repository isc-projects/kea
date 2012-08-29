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

#ifndef _DOMAINTREE_H
#define _DOMAINTREE_H 1

//! \file datasrc/memory/domaintree.h
///
/// \note The purpose of the DomainTree is to provide a generic map with
///     domain names as the key that can be used by various BIND 10
///     modules or even by other applications.  However, because of some
///     unresolved design issue, the design and interface are not fixed,
///     and DomainTree isn't ready to be used as a base data structure
///     by other modules.

#include <exceptions/exceptions.h>
#include <util/memory_segment.h>
#include <dns/name.h>
#include <dns/labelsequence.h>

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/static_assert.hpp>

#include <ostream>
#include <algorithm>
#include <cassert>

namespace isc {
namespace datasrc {
namespace memory {

/// Forward declare DomainTree class here is convinent for following
/// friend class declare inside DomainTreeNode and DomainTreeNodeChain
template <typename T>
class DomainTree;

/// \brief \c DomainTreeNode is used by DomainTree to store any data
///     related to one domain name.
///
/// This is meant to be used only from DomainTree. It is meaningless to
/// inherit it or create instances of it from elsewhere. For that
/// reason, the constructor (and the allocator, see below) is private.
///
/// It serves three roles. One is to keep structure of the \c DomainTree
/// as a red-black tree. For that purpose, it has left, right and parent
/// pointers and color member. These are private and accessed only from
/// within the tree.
///
/// The second one is to store data for one domain name. The data
/// related functions can be used to access and set the data.
///
/// The third role is to keep the hierarchy of domains. The down pointer
/// points to a subtree of subdomains. The parent pointer of a subtree's
/// root node points to the parent leaf of the upper tree.
///
/// One special kind of node is non-terminal node. It has subdomains
/// with RRsets, but doesn't have any RRsets itself.
///
/// In order to keep memory footprint as small as possible, the node
/// data are heavily packed.  Specifically, some internal node
/// properties (such as the node color) are encoded as part of "flags",
/// some of the flag bits can also be set by the user application.  Each
/// node is associated with a sequence of domain name labels, which is
/// essentially the search/insert key for the node (see also the
/// description of DomainTree).  This is encoded as opaque binary
/// immediately following the main node object.  The size of the
/// allocated space for the labels data is encoded by borrowing some
/// bits of the "flags" field.
template <typename T>
class DomainTreeNode : public boost::noncopyable {
private:
    /// The DomainTreeNode is meant for use from within DomainTree, so
    /// it has access to it.
    friend class DomainTree<T>;

    /// \brief Just a type alias
    ///
    /// We are going to use a lot of these offset pointers here and they
    /// have a long name.
    typedef boost::interprocess::offset_ptr<DomainTreeNode<T> >
        DomainTreeNodePtr;

    /// \name Constructors
    ///
    /// \note The existence of a DomainTreeNode without a DomainTree is
    ///     meaningless.  Therefore the constructors are private.
    //@{

    /// \brief Constructor from normal nodes.
    DomainTreeNode(size_t labels_capacity);

    /// \brief Destructor
    ~DomainTreeNode();

    //@}

    /// \brief Accessor to the memory region for node labels.
    ///
    /// The only valid usage of the returned pointer is to pass it to
    /// the corresponding constructor of \c dns::LabelSequence.
    const void* getLabelsData() const { return (this + 1); }

    /// \brief Accessor to the memory region for node labels, mutable version.
    ///
    /// The only valid usage of the returned pointer is to pass it to
    /// \c LabelSequence::serialize() with the node's labels_capacity_ member
    /// (which should be sufficiently large for the \c LabelSequence in that
    /// context).
    void* getLabelsData() { return (this + 1); }

    /// \brief Allocate and construct \c DomainTreeNode
    ///
    /// This static method allocates memory for a new \c DomainTreeNode
    /// object from the given memory segment, constructs the object, and
    /// returns a pointer to it.
    ///
    /// \throw std::bad_alloc Memory allocation fails.
    ///
    /// \param mem_sgmt A \c MemorySegment from which memory for the new
    /// \c DomainTreeNode is allocated.
    static DomainTreeNode<T>* create(util::MemorySegment& mem_sgmt,
                                     const dns::LabelSequence& labels)
    {
        const size_t labels_len = labels.getSerializedLength();
        void* p = mem_sgmt.allocate(sizeof(DomainTreeNode<T>) + labels_len);
        DomainTreeNode<T>* node = new(p) DomainTreeNode<T>(labels_len);
        labels.serialize(node->getLabelsData(), labels_len);
        return (node);
    }

    /// \brief Destruct and deallocate \c DomainTreeNode
    ///
    /// \throw none
    ///
    /// \param mem_sgmt The \c MemorySegment that allocated memory for
    /// \c node.
    /// \param node A non NULL pointer to a valid \c DomainTreeNode object
    /// that was originally created by the \c create() method (the behavior
    /// is undefined if this condition isn't met).
    static void destroy(util::MemorySegment& mem_sgmt,
                        DomainTreeNode<T>* node)
    {
        const size_t labels_capacity = node->labels_capacity_;
        node->~DomainTreeNode<T>();
        mem_sgmt.deallocate(node,
                            sizeof(DomainTreeNode<T>) + labels_capacity);
    }

    /// \brief Reset node's label sequence to a new one.
    ///
    /// The new labels must be a sub sequence of the current label sequence;
    /// otherwise the serialize() method will throw an exception.
    void resetLabels(const dns::LabelSequence& labels) {
        labels.serialize(getLabelsData(), labels_capacity_);
    }

public:
    /// Node flags.
    ///
    /// Each flag value defines a non default property for a specific node.
    /// These are defined as bitmask type values for the convenience of
    /// internal implementation, but applications are expected to use
    /// each flag separately via the enum definitions.
    ///
    /// All (settable) flags are off by default; they must be explicitly
    /// set to on by the \c setFlag() method.
    enum Flags {
        FLAG_CALLBACK = 1, ///< Callback enabled. See \ref callback
        FLAG_RED = 2, ///< Node color; 1 if node is red, 0 if node is black.
        FLAG_SUBTREE_ROOT = 4, ///< Set if the node is the root of a subtree
        FLAG_USER1 = 0x400000U, ///< Application specific flag
        FLAG_USER2 = 0x200000U, ///< Application specific flag
        FLAG_USER3 = 0x100000U, ///< Application specific flag
        FLAG_MAX = 0x400000U    // for integrity check
    };
private:
    // Some flag values are expected to be used for internal purposes
    // (e.g., representing the node color) in future versions, so we
    // limit the settable flags via the \c setFlag() method to those
    // explicitly defined in \c Flags.  This constant represents all
    // such flags.
    static const uint32_t SETTABLE_FLAGS = (FLAG_CALLBACK | FLAG_USER1 |
                                            FLAG_USER2 | FLAG_USER3);

public:

    /// \name Getter functions.
    //@{
    /// \brief Return the name of current node.
    ///
    /// It's relative to its containing node.
    ///
    /// To get the absolute name of one node, the node path from the top node
    /// to current node has to be recorded.
    ///
    /// \note We should eventually deprecate this method and revise all its
    /// usage with \c getLabels().  At this point the only user of this method
    /// is getAbsoluteName()::getAbsoluteName(), which would have to be revised
    /// using \c LabelSequence.  Until then we keep this interface as a
    /// simplest form of wrapper; it's not efficient, but should be replaced
    /// before we need to worry about that.
    const isc::dns::Name getName() const {
        return (dns::Name(dns::LabelSequence(getLabelsData()).toText()));
    }

    /// \brief Return the label sequence of the node.
    ///
    /// This method returns the label sequence corresponding to this node
    /// in the form of \c dns::LabelSequence object.  Any modification to
    /// the tree can invalidate the returned \c LabelSequence object or copy
    /// of it; in general, it's expected to be used in a very limited scope.
    dns::LabelSequence getLabels() const {
        return (dns::LabelSequence(getLabelsData()));
    }

    /// \brief Return the absolute label sequence of the node.
    ///
    /// This method returns the label sequence corresponding to the full
    /// name of the node; i.e. the entire name as it appears in the zone.
    ///
    /// It takes the (partial) name of the node itself, and extends it
    /// with all upper nodes.
    ///
    /// \note Care must be taken with the buffer that is used here; this
    /// method overwrites its data, so it should not be associated with
    /// any other LabelSequence during the lifetime of the LabelSequence
    /// returned by this method. See LabelSequence::extend(), which is used
    /// by this method.
    ///
    /// \param buf A data buffer where the label sequence will be built.
    ///            The data in this buffer will be overwritten by this call.
    /// \return A LabelSequence with the absolute name of this node.
    isc::dns::LabelSequence getAbsoluteLabels(
        uint8_t buf[isc::dns::LabelSequence::MAX_SERIALIZED_LENGTH]) const;

    /// \brief Return the data stored in this node.
    ///
    /// You should not delete the data, it is deleted when the tree is
    /// destroyed.
    T* getData() { return (data_.get()); }

    /// \brief Return the data stored in this node (const).
    const T* getData() const { return (data_.get()); }

    /// \brief return whether the node has related data.
    ///
    /// There can be empty nodes inside the DomainTree. They are usually the
    /// non-terminal domains, but it is possible (yet probably meaningless)
    /// empty nodes anywhere.
    bool isEmpty() const { return (!data_); }
    //@}

    /// \name Setter functions.
    //@{

    /// \brief Set the data stored in the node.
    ///
    /// If there is old data, a pointer to the data will be returned;
    /// otherwise NULL will be returned.  The caller is responsible for
    /// releasing any resource for the old data if it's not needed any more.
    /// See also the note about data ownership in the \c DomainTree
    /// description.
    ///
    /// \c data can be NULL, in which case it effectively clears any existing
    /// old data.
    ///
    /// \param data The new data to set.  It can be NULL.
    /// \return A pointer to the old data or NULL if the node doesn't have
    /// data.
    T* setData(T* data) {
        T* olddata = data_.get();
        data_ = data;
        return (olddata);
    }
    //@}

    /// \name Node flag manipulation methods
    //@{
    /// Get the status of a node flag.
    ///
    /// This method returns whether the given node flag is set (enabled)
    /// on the node.  The \c flag parameter is expected to be one of the
    /// defined \c Flags constants.  For simplicity, the method interface
    /// does not prohibit passing an undefined flag or combined flags, but
    /// the return value in such a case will be meaningless for the caller
    /// (an application would have to use an ugly cast for such an unintended
    /// form of call, which will hopefully avoid accidental misuse).
    ///
    /// \exception None
    /// \param flag The flag to be tested.
    /// \return \c true if the \c flag is set; \c false otherwise.
    bool getFlag(Flags flag) const {
        return ((flags_ & flag) != 0);
    }

    /// Set or clear a node flag.
    ///
    /// This method changes the status of the specified node flag to either
    /// "on" (enabled) or "off" (disabled).  The new status is specified by
    /// the \c on parameter.
    /// Like the \c getFlag() method, \c flag is expected to be one of the
    /// defined \c Flags constants.  If an undefined or unsettable flag is
    /// specified, \c isc::InvalidParameter exception will be thrown.
    ///
    /// \exception isc::InvalidParameter Unsettable flag is specified
    /// \exception None otherwise
    /// \param flag The node flag to be changed.
    /// \param on If \c true, set the flag to on; otherwise set it to off.
    void setFlag(Flags flag, bool on = true) {
        if ((flag & ~SETTABLE_FLAGS) != 0) {
            isc_throw(isc::InvalidParameter,
                      "Unsettable DomainTree flag is being set");
        }
        if (on) {
            flags_ |= flag;
        } else {
            flags_ &= ~flag;
        }
    }
    //@}

private:
    /// \name Callback related methods
    ///
    /// See the description of \c DomainTree<T>::find() at \ref callback
    /// about callbacks.
    ///
    /// These methods never throw an exception.
    //@{
    /// Return if callback is enabled at the node.
    //@}


    /// \brief Define node color
    enum DomainTreeNodeColor {BLACK, RED};

    /// \brief Returns the color of this node
    DomainTreeNodeColor getColor() const {
        if ((flags_ & FLAG_RED) != 0) {
            return (RED);
        } else {
            return (BLACK);
        }
    }

    /// \brief Sets the color of this node
    void setColor(const DomainTreeNodeColor color) {
        if (color == RED) {
            flags_ |= FLAG_RED;
        } else {
            flags_ &= ~FLAG_RED;
        }
    }

    void setSubTreeRoot(bool root) {
        if (root) {
            flags_ |= FLAG_SUBTREE_ROOT;
        } else {
            flags_ &= ~FLAG_SUBTREE_ROOT;
        }
    }

    bool isSubTreeRoot() const {
        return ((flags_ & FLAG_SUBTREE_ROOT) != 0);
    }

public:
    /// \brief returns the parent of the root of its subtree
    ///
    /// This method takes a node and returns the parent of the root of
    /// its subtree (i.e, it returns the node's immediate ancestor in
    /// the tree-of-tree hierarchy). If the node is at the top level
    /// (which should be absolute), it will return \c NULL.
    ///
    /// This method never throws an exception.
    const DomainTreeNode<T>* getUpperNode() const;

private:
    /// \brief return the next node which is bigger than current node
    /// in the same subtree
    ///
    /// The next successor for this node is the next bigger node in terms of
    /// the DNSSEC order relation within the same single subtree.
    /// Note that it may NOT be the next bigger node in the entire DomainTree;
    ///  DomainTree is a tree in tree, and the real next node may reside in
    /// an upper or lower subtree of the subtree where this node belongs.
    /// For example, if this node has a sub domain, the real next node is
    /// the smallest node in the sub domain tree.
    ///
    /// If this node is the biggest node within the subtree, this method
    /// returns \c NULL.
    ///
    /// This method never throws an exception.
    const DomainTreeNode<T>* successor() const;

    /// \brief return the next node which is smaller than current node
    /// in the same subtree
    ///
    /// The predecessor for this node is the next smaller node in terms of
    /// the DNSSEC order relation within the same single subtree.
    /// Note that it may NOT be the next smaller node in the entire DomainTree;
    /// DomainTree is a tree in tree, and the real next node may reside in
    /// an upper or lower subtree of the subtree where this node belongs.
    /// For example, if the predecessor node has a sub domain, the real next
    /// node is the largest node in the sub domain tree.
    ///
    /// If this node is the smallest node within the subtree, this method
    /// returns \c NULL.
    ///
    /// This method never throws an exception.
    const DomainTreeNode<T>* predecessor() const;

    /// \brief private shared implementation of successor and predecessor
    ///
    /// As the two mentioned functions are merely mirror images of each other,
    /// it makes little sense to keep both versions. So this is the body of the
    /// functions and we call it with the correct pointers.
    ///
    /// Not to be called directly, not even by friends.
    ///
    /// The overhead of the member pointers should be optimised out, as this
    /// will probably get completely inlined into predecessor and successor
    /// methods.
    const DomainTreeNode<T>*
        abstractSuccessor(typename DomainTreeNode<T>::DomainTreeNodePtr
                          DomainTreeNode<T>::*left,
                          typename DomainTreeNode<T>::DomainTreeNodePtr
                          DomainTreeNode<T>::*right)
        const;

    /// \name Data to maintain the rbtree structure.
    ///
    /// We keep them as offset pointers. This is part of a future plan, when we
    /// want to share the image of the tree between multiple processes.
    /// However, whenever we have a chance, we switch to bare pointers during
    /// the processing. The pointers on stack are never shared and the offset
    /// pointers have non-trivial performance impact.
    //@{
    DomainTreeNodePtr parent_;
    /// \brief Access the parent_ as bare pointer.
    DomainTreeNode<T>* getParent() {
        return (parent_.get());
    }
    /// \brief Access the parent_ as bare pointer, const.
    const DomainTreeNode<T>* getParent() const {
        return (parent_.get());
    }
    DomainTreeNodePtr left_;
    /// \brief Access the left_ as bare pointer.
    DomainTreeNode<T>* getLeft() {
        return (left_.get());
    }
    /// \brief Access the left_ as bare pointer, const.
    const DomainTreeNode<T>* getLeft() const {
        return (left_.get());
    }
    DomainTreeNodePtr right_;
    /// \brief Access the right_ as bare pointer.
    DomainTreeNode<T>* getRight() {
        return (right_.get());
    }
    /// \brief Access the right_ as bare pointer, const.
    const DomainTreeNode<T>* getRight() const {
        return (right_.get());
    }
    //@}

    /// \brief The subdomain tree.
    ///
    /// This points to the root node of trees of subdomains of this domain.
    ///
    /// \par Adding down pointer to \c DomainTreeNode has two purposes:
    /// \li Accelerate the search process, with sub domain tree, it splits the
    ///     big flat tree into several hierarchy trees.
    /// \li It saves memory usage as it allows storing only relative names,
    ///     avoiding storage of the same domain labels multiple times.
    DomainTreeNodePtr down_;
    /// \brief Access the down_ as bare pointer.
    DomainTreeNode<T>* getDown() {
        return (down_.get());
    }
    /// \brief Access the down_ as bare pointer, const.
    const DomainTreeNode<T>* getDown() const {
        return (down_.get());
    }

    /// \brief Data stored here.
    boost::interprocess::offset_ptr<T> data_;

    /// \brief Internal or user-configurable flags of node's properties.
    ///
    /// See the \c Flags enum for available flags.
    ///
    /// For memory efficiency reasons, we only use a subset of the 32-bit
    /// space, and use the rest to store the allocated size for the node's
    /// label sequence data.
    uint32_t flags_ : 23;          // largest flag being 0x400000
    BOOST_STATIC_ASSERT((1 << 23) > FLAG_MAX); // assumption check

    const uint32_t labels_capacity_ : 9; // size for labelseq; range is 0..511
    // Make sure the reserved space for labels_capacity_ is sufficiently
    // large.  In effect, we use the knowledge of the implementation of the
    // serialization, but we still only use its public interface, and the
    // public interface of this class doesn't rely on this assumption.
    // So we can change this implementation without affecting its users if
    // a future change to LabelSequence breaks this assumption.
    BOOST_STATIC_ASSERT((1 << 9) > dns::LabelSequence::MAX_SERIALIZED_LENGTH);
};

template <typename T>
DomainTreeNode<T>::DomainTreeNode(size_t labels_capacity) :
    parent_(NULL),
    left_(NULL),
    right_(NULL),
    down_(NULL),
    data_(NULL),
    flags_(FLAG_RED | FLAG_SUBTREE_ROOT),
    labels_capacity_(labels_capacity)
{
}

template <typename T>
DomainTreeNode<T>::~DomainTreeNode() {
}

template <typename T>
const DomainTreeNode<T>*
DomainTreeNode<T>::getUpperNode() const {
    const DomainTreeNode<T>* current = this;

    // current would never be equal to NULL here (in a correct tree
    // implementation)
    while (!current->isSubTreeRoot()) {
        current = current->getParent();
    }

    return (current->getParent());
}

template <typename T>
isc::dns::LabelSequence
DomainTreeNode<T>::getAbsoluteLabels(
    uint8_t buf[isc::dns::LabelSequence::MAX_SERIALIZED_LENGTH]) const
{
    isc::dns::LabelSequence result(getLabels(), buf);
    const DomainTreeNode<T>* upper = getUpperNode();
    while (upper != NULL) {
        result.extend(upper->getLabels(), buf);
        upper = upper->getUpperNode();
    }

    return (result);
}

template <typename T>
const DomainTreeNode<T>*
DomainTreeNode<T>::abstractSuccessor(
    typename DomainTreeNode<T>::DomainTreeNodePtr DomainTreeNode<T>::*left,
    typename DomainTreeNode<T>::DomainTreeNodePtr DomainTreeNode<T>::*right)
    const
{
    // This function is written as a successor. It becomes predecessor if
    // the left and right pointers are swapped. So in case of predecessor,
    // the left pointer points to right and vice versa. Don't get confused
    // by the idea, just imagine the pointers look into a mirror.

    const DomainTreeNode<T>* current = this;
    // If it has right node, the successor is the left-most node of the right
    // subtree.
    if ((current->*right).get() != NULL) {
        current = (current->*right).get();
        const DomainTreeNode<T>* left_n;
        while ((left_n = (current->*left).get()) != NULL) {
            current = left_n;
        }
        return (current);
    }

    // Otherwise go up until we find the first left branch on our path to
    // root.  If found, the parent of the branch is the successor.
    // Otherwise, we return the null node
    const DomainTreeNode<T>* parent = current->getParent();
    while ((!current->isSubTreeRoot()) &&
           (current == (parent->*right).get())) {
        current = parent;
        parent = parent->getParent();
    }

    if (!current->isSubTreeRoot()) {
        return (parent);
    } else {
        return (NULL);
    }
}

template <typename T>
const DomainTreeNode<T>*
DomainTreeNode<T>::successor() const {
    return (abstractSuccessor(&DomainTreeNode<T>::left_,
                              &DomainTreeNode<T>::right_));
}

template <typename T>
const DomainTreeNode<T>*
DomainTreeNode<T>::predecessor() const {
    // Swap the left and right pointers for the abstractSuccessor
    return (abstractSuccessor(&DomainTreeNode<T>::right_,
                              &DomainTreeNode<T>::left_));
}

/// \brief DomainTreeNodeChain stores detailed information of \c
/// DomainTree::find() result.
///
/// - The \c DomainTreeNode that was last compared with the search name, and
///   the comparison result at that point in the form of
///   \c isc::dns::NameComparisonResult.
/// - A sequence of nodes that forms a path to the found node.
///
/// The comparison result can be used to handle some rare cases such as
/// empty node processing.
/// The node sequence keeps track of the nodes to reach any given node from
/// the root of DomainTree.
///
/// Currently, DomainTreeNode does not have "up" pointers in them (i.e.,
/// back pointers from the root of one level of tree of trees to the
/// node in the parent tree whose down pointer points to that root node)
/// for memory usage reasons, so there is no other way to find the path
/// back to the root from any given DomainTreeNode.
///
/// \note This design may change in future versions.  In particular, it's
/// quite likely we want to have that pointer if we want to optimize name
/// compression by exploiting the structure of the zone.  If and when that
/// happens we should also revisit the need for the chaining.
/// Also, the class name may not be appropriate now that it contains other
/// information than a node "chain", and the chain itself may even be
/// deprecated.  Something like "DomainTreeFindContext" may be a better name.
/// This point should be revisited later.
///
/// DomainTreeNodeChain is constructed and manipulated only inside the
/// \c DomainTree class.
/// \c DomainTree uses it as an inner data structure to iterate over the whole
/// DomainTree.
/// This is the reason why manipulation methods such as \c push() and \c pop()
/// are private (and not shown in the doxygen document).
template <typename T>
class DomainTreeNodeChain {
    /// DomainTreeNodeChain is initialized by DomainTree, only DomainTree has
    /// knowledge to manipulate it.
    friend class DomainTree<T>;
public:
    /// \name Constructors and Assignment Operator.
    ///
    /// \note The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non copyable.
    /// This may have to be changed in a future version with newer need.
    /// For now we explicitly disable copy to avoid accidental copy happens
    /// unintentionally.
    //{@
    /// The default constructor.
    ///
    /// \exception None
    DomainTreeNodeChain() : node_count_(0), last_compared_(NULL),
                        // XXX: meaningless initial values:
                        last_comparison_(0, 0,
                                         isc::dns::NameComparisonResult::EQUAL)
    {}

private:
    DomainTreeNodeChain(const DomainTreeNodeChain<T>&);
    DomainTreeNodeChain<T>& operator=(const DomainTreeNodeChain<T>&);
    //@}

public:
    /// Clear the state of the chain.
    ///
    /// This method re-initializes the internal state of the chain so that
    /// it can be reused for subsequent operations.
    ///
    /// \exception None
    void clear() {
        node_count_ = 0;
        last_compared_ = NULL;
    }

    /// Return the \c DomainTreeNode that was last compared in \c
    /// DomainTree::find().
    ///
    /// If this chain has been passed to \c DomainTree::find() and there
    /// has been name comparison against the search name, the last
    /// compared \c DomainTreeNode is recorded within the chain.  This
    /// method returns that node.
    ///
    /// If \c DomainTree::find() hasn't been called with this chain or
    /// name comparison hasn't taken place (which is possible if the
    /// tree is empty), this method returns \c NULL.
    ///
    /// \exception None
    const DomainTreeNode<T>* getLastComparedNode() const {
        return (last_compared_);
    }

    /// Return the result of last name comparison in \c DomainTree::find().
    ///
    /// Like \c getLastComparedNode(), \c DomainTree::find() records the result
    /// of the last name comparison in the chain.  This method returns the
    /// result.
    /// The return value of this method is only meaningful when comparison
    /// has taken place, i.e, when \c getLastComparedNode() would return a
    /// non \c NULL value.
    ///
    /// \exception None
    const isc::dns::NameComparisonResult& getLastComparisonResult() const {
        return (last_comparison_);
    }

    /// \brief Return the number of levels stored in the chain.
    ///
    /// It's equal to the number of nodes in the chain; for an empty
    /// chain, 0 will be returned.
    ///
    /// \exception None
    unsigned int getLevelCount() const { return (node_count_); }

    /// \brief return the absolute name for the node which this
    /// \c DomainTreeNodeChain currently refers to.
    ///
    /// The chain must not be empty.
    ///
    /// \exception isc::BadValue the chain is empty.
    /// \exception std::bad_alloc memory allocation for the new name fails.
    isc::dns::Name getAbsoluteName() const {
        if (isEmpty()) {
            isc_throw(isc::BadValue,
                      "DomainTreeNodeChain::getAbsoluteName is "
                      "called on an empty chain");
        }

        const DomainTreeNode<T>* top_node = top();
        isc::dns::Name absolute_name = top_node->getName();
        int node_count = node_count_ - 1;
        while (node_count > 0) {
            top_node = nodes_[node_count - 1];
            absolute_name = absolute_name.concatenate(top_node->getName());
            --node_count;
        }
        return (absolute_name);
    }

private:
    // the following private functions check invariants about the internal
    // state using assert() instead of exception.  The state of a chain
    // can only be modified by operations within this file, so if any of the
    // assumptions fails it means an internal bug.

    /// \brief return whether node chain has node in it.
    ///
    /// \exception None
    bool isEmpty() const { return (node_count_ == 0); }

    /// \brief return the top node for the node chain
    ///
    /// DomainTreeNodeChain store all the nodes along top node to
    /// root node of DomainTree
    ///
    /// \exception None
    const DomainTreeNode<T>* top() const {
        assert(!isEmpty());
        return (nodes_[node_count_ - 1]);
    }

    /// \brief pop the top node from the node chain
    ///
    /// After pop, up/super node of original top node will be
    /// the top node
    ///
    /// \exception None
    void pop() {
        assert(!isEmpty());
        --node_count_;
    }

    /// \brief add the node into the node chain
    ///
    /// If the node chain isn't empty, the node should be
    /// the sub domain of the original top node in node chain
    /// otherwise the node should be the root node of DomainTree.
    ///
    /// \exception None
    void push(const DomainTreeNode<T>* node) {
        assert(node_count_ < RBT_MAX_LEVEL);
        nodes_[node_count_++] = node;
    }

private:
    // The max label count for one domain name is Name::MAX_LABELS
    // (128).  Since each node in domaintree stores at least one label,
    // it's also equal to the possible maximum level.
    const static int RBT_MAX_LEVEL = isc::dns::Name::MAX_LABELS;

    int node_count_;
    const DomainTreeNode<T>* nodes_[RBT_MAX_LEVEL];
    const DomainTreeNode<T>* last_compared_;
    isc::dns::NameComparisonResult last_comparison_;
};


// note: the following class description is documented using multiline comments
// because the verbatim diagram contain a backslash, which could be interpreted
// as escape of newline in singleline comment.
/**
 *  \brief \c DomainTree class represents all the domains with the same suffix.
 *      It can be used to store the domains in one zone, for example.
 *
 * DomainTree is a generic map from domain names to any kind of
 * data. Internally, it uses a red-black tree. However, it isn't one
 * tree containing everything.  Subdomains are trees, so this structure
 * is recursive - trees inside trees.  But, from the interface point of
 * view, it is opaque data structure.
 *
 * The data of DomainTree are set by the application via the
 * DomainTreeNode::setData() method.  The ownership of the data isn't
 * transferred to the DomainTree; if the application replaces existing
 * data for a specific name in DomainTree by setData(), the application is
 * responsible for releasing any resource for the old data.  When the
 * application destroys the entire DomainTree by the \c destroy() method,
 * it needs to pass a deleter object for any remained data in the DomainTree.
 * The DomainTree will call that object with all the data in the tree so that
 * the application complete the cleanup about the remaining data.
 *
 *  \c DomainTree splits the domain space into hierarchy red black trees; nodes
 * in one tree has the same base name. The benefit of this struct is that:
 *  - Enhances the query performance compared with one big flat red black tree.
 *  - Decreases the memory footprint, as it doesn't store the suffix labels
 *      multiple times.
 *
 * Depending on different usage, domaintree will support different
 * search policies.  Whether to return an empty node to end user is one
 * policy among them.  The default policy is to NOT return an empty node
 * to end user; to change the behavior, specify \c true for the
 * constructor parameter \c returnEmptyNode.
 * \note The search policy only affects the \c find() behavior of DomainTree.
 * When inserting one name into DomainTree, if the node with the name already
 * exists in the DomainTree and it's an empty node which doesn't have any data,
 * the \c insert() method will still return \c ALREADYEXISTS regardless of
 * the search policy.
 *
 * The template parameter taken by \c DomainTree is \c T (the type of
 * data which is stored by the tree).
 *
 * \anchor diagram
 *
 * with the following names:
 *  - a
 *  - b
 *  - c
 *  - x.d.e.f
 *  - z.d.e.f
 *  - g.h
 *  - o.w.y.d.e.f
 *  - p.w.y.d.e.f
 *  - q.w.y.d.e.f
 *
 * the tree will look like:
 *  \verbatim
                                .
                                |
                                b
                              /   \
                             a    d.e.f
                                    /|\
                                   c | g.h
                                     |
                                    w.y
                                    /|\
                                   x | z
                                     |
                                     p
                                    / \
                                   o   q
   \endverbatim
 *  \todo
 *  - add remove interface
 */
template <typename T>
class DomainTree : public boost::noncopyable {
    friend class DomainTreeNode<T>;
public:
    /// \brief The return value for the \c find() and insert() methods
    enum Result {
        SUCCESS,    ///< Insert was successful
        /// \brief The node returned from find mathes exactly the name given
        EXACTMATCH,
        PARTIALMATCH, ///< A superdomain node was found
        NOTFOUND,   ///< Not even any superdomain was found
        /// \brief Returned by insert() if a node of the name already exists
        ALREADYEXISTS,
    };

    /// \brief Allocate and construct \c DomainTree
    ///
    /// This static method allocates memory for a new \c DomainTree object
    /// from the given memory segment, constructs the object, and returns
    /// a pointer to it.
    ///
    /// \throw std::bad_alloc Memory allocation fails.
    ///
    /// \param mem_sgmt A \c MemorySegment from which memory for the new
    /// \c DomainTree is allocated.
    static DomainTree* create(util::MemorySegment& mem_sgmt,
                              bool return_empty_node = false)
    {
        void* p = mem_sgmt.allocate(sizeof(DomainTree<T>));
        return (new(p) DomainTree<T>(return_empty_node));
    }

    /// \brief Destruct and deallocate \c DomainTree
    ///
    /// This method also destroys and deallocates all nodes inserted to the
    /// tree.
    ///
    /// The template parameter, \c DataDeleter, is a type whose instance is
    /// used to destroy data stored in the tree nodes.  It must have a
    /// <code>operator()</code> method, which is called on a \c DataDeleter
    /// instance and passed a pointer to the data (<code>T*</code>) to be
    /// destroyed. This method should be written to accept a \c NULL argument.
    ///
    /// \note The memory segment (\c mem_sgmt) must be the same one that
    /// was originally used to allocate memory for the tree (and for all
    /// nodes inserted to the tree, due to the requirement of \c insert()),
    /// since the tree itself doesn't maintain a reference to the segment.
    /// This is not a robust interface, but since we plan to share the tree
    /// structure by multiple processes via shared memory or possibly allow
    /// the memory image to be dumped to a file for later reload, there
    /// doesn't seem to be an easy way to store such reference in the data
    /// itself.  We should probably consider a wrapper interface that
    /// encapsulates the corresponding segment and always use it for any
    /// allocation/deallocation of tree related data (the tree itself, their
    /// nodes, and node data) to keep the usage as safe as possible.
    ///
    /// \throw none
    ///
    /// \param mem_sgmt The \c MemorySegment that allocated memory for
    /// \c tree and for all nodes inserted to the tree.
    /// \param tree A non NULL pointer to a valid \c DomainTree object
    /// that was originally created by the \c create() method (the behavior
    /// is undefined if this condition isn't met).
    /// \param deleter A deleter functor or function to delete node data.
    template <typename DataDeleter>
    static void destroy(util::MemorySegment& mem_sgmt,
                        DomainTree<T>* tree,
                        DataDeleter deleter)
    {
        tree->deleteAllNodes(mem_sgmt, deleter);
        tree->~DomainTree<T>();
        mem_sgmt.deallocate(tree, sizeof(DomainTree<T>));
    }

private:
    /// \name Constructor and Destructor
    //@{
    /// \brief The constructor.
    ///
    /// An object of this class is always expected to be created by the
    /// allocator (\c create()), so the constructor is hidden as private.
    ///
    /// It never throws an exception.
    explicit DomainTree(bool returnEmptyNode = false);

    /// \brief The destructor.
    ///
    /// An object of this class is always expected to be destroyed explicitly
    /// by \c destroy(), so the destructor is hidden as private.
    ///
    /// \note DomainTree is not intended to be inherited so the destructor
    /// is not virtual
    ~DomainTree();
    //@}

public:

    /// \name Find methods
    ///
    /// \brief Find the node that gives a longest match against the given name.
    ///
    /// \anchor find
    ///
    /// These methods search the DomainTree for a node whose name is
    /// longest against name. The found node, if any, is returned via
    /// the node pointer.
    ///
    /// By default, nodes that don't have data (see
    /// DomainTreeNode::isEmpty) are ignored and the result can be
    /// NOTFOUND even if there's a node whose name matches.  If the \c
    /// DomainTree is constructed with its \c returnEmptyNode parameter
    /// being \c true, empty nodes will also be match candidates.
    ///
    /// \note Even when \c returnEmptyNode is \c true, not all empty
    /// nodes in terms of the DNS protocol may necessarily be found by
    /// this method.  For example, in the \ref diagram shown in the
    /// class description, the name y.d.e.f is logically contained in
    /// the tree as part of the node w.y, but the \c find() variants
    /// cannot find the former for the search key of y.d.e.f, no matter
    /// how the \c DomainTree is constructed.  The caller of this method
    /// must use a different way to identify the hidden match when
    /// necessary.
    ///
    /// These methods involve operations on names that can throw an
    /// exception.  If that happens the exception will be propagated to
    /// the caller.  The callback function should generally not throw an
    /// exception, but if it throws, the exception will be propagated to
    /// the caller.
    ///
    /// The \c name parameter says what should be found. The node parameter
    /// is output-only, and in case of EXACTMATCH or PARTIALMATCH, it is set
    /// to a pointer to the found node.
    ///
    /// They return:
    ///  - EXACTMATCH when a node with the same name as requested exists.
    ///  - PARTIALMATCH when a node with the same name does not exist (or is
    ///    empty), but there's a (nonempty) superdomain of the requested one.
    ///    The superdomain with longest name is returned through the node
    ///    parameter. Beware that if you store a zone in the tree, you may get
    ///    PARTIALMATCH with zone apex when the given domain name is not there.
    ///    You should not try to delegate into another zone in that case.
    ///  - NOTFOUND if there's no node with the same name nor any superdomain
    ///    of it. In that case, node parameter is left intact.
    //@{

    /// \brief Simple find.
    ///
    /// Acts as described in the \ref find section.
    Result find(const isc::dns::Name& name,
                DomainTreeNode<T>** node) const {
        DomainTreeNodeChain<T> node_path;
        const isc::dns::LabelSequence ls(name);
        return (find<void*>(ls, node, node_path, NULL, NULL));
    }

    /// \brief Simple find returning immutable node.
    ///
    /// Acts as described in the \ref find section, but returns immutable node
    /// pointer.
    Result find(const isc::dns::Name& name,
                const DomainTreeNode<T>** node) const {
        DomainTreeNodeChain<T> node_path;
        DomainTreeNode<T> *target_node = NULL;
        const isc::dns::LabelSequence ls(name);
        Result ret = (find<void*>(ls, &target_node, node_path, NULL, NULL));
        if (ret != NOTFOUND) {
            *node = target_node;
        }
        return (ret);
    }

    /// \brief Simple find, with node_path tracking
    ///
    /// Acts as described in the \ref find section.
    Result find(const isc::dns::Name& name, DomainTreeNode<T>** node,
                DomainTreeNodeChain<T>& node_path) const
    {
        const isc::dns::LabelSequence ls(name);
        return (find<void*>(ls, node, node_path, NULL, NULL));
    }

    /// \brief Simple find returning immutable node, with node_path tracking
    ///
    /// Acts as described in the \ref find section, but returns immutable node
    /// pointer.
    Result find(const isc::dns::Name& name, const DomainTreeNode<T>** node,
                DomainTreeNodeChain<T>& node_path) const
    {
        DomainTreeNode<T> *target_node = NULL;
        const isc::dns::LabelSequence ls(name);
        Result ret = (find<void*>(ls, &target_node, node_path, NULL, NULL));
        if (ret != NOTFOUND) {
            *node = target_node;
        }
        return (ret);
    }

    /// \brief Simple find returning immutable node.
    ///
    /// Acts as described in the \ref find section, but returns immutable
    /// node pointer.
    template <typename CBARG>
    Result find(const isc::dns::Name& name,
                const DomainTreeNode<T>** node,
                DomainTreeNodeChain<T>& node_path,
                bool (*callback)(const DomainTreeNode<T>&, CBARG),
                CBARG callback_arg) const
    {
        DomainTreeNode<T>* target_node = NULL;
        const isc::dns::LabelSequence ls(name);
        Result ret = find(ls, &target_node, node_path, callback,
                          callback_arg);
        if (ret != NOTFOUND) {
            *node = target_node;
        }
        return (ret);
    }

    /// \brief Find with callback and node chain
    /// \anchor callback
    ///
    /// This version of \c find() is specifically designed for the backend
    /// of the \c InMemoryZoneFinder class, and implements all necessary
    /// features for that purpose.  Other applications shouldn't need these
    /// additional features, and should normally use the simpler versions.
    ///
    /// This version of \c find() calls the callback whenever traversing (on
    /// the way from root down the tree) a marked node on the way down through
    /// the domain namespace (see \c DomainTreeNode::FLAG_CALLBACK).
    ///
    /// Also, this version takes a \c LabelSequence object, not a \c Name
    /// object to be as efficient as possible; operations on the former
    /// needed for the search are generally much more efficient than those
    /// for the latter.  Since \c Name objects are more commonly used
    /// in other parts of the implementation, other versions take a \c Name
    /// and convert it to \c LabelSequence.  This conversion is cheap,
    /// while the other direction isn't, and since there would be cases
    /// where an implementation primarily handles \c LabelSequence objects
    /// as an efficient representation of names, it would make most sense
    /// to provide the interface that takes \c LabelSequence.
    ///
    /// If you return true from the callback, the search is stopped and a
    /// PARTIALMATCH is returned with the given node. Note that this node
    /// doesn't really need to be the one with longest possible match.
    ///
    /// The callback is not called for the node which matches exactly
    /// (EXACTMATCH is returned). This is typically the last node in the
    /// traversal during a successful search.
    ///
    /// This callback mechanism was designed with zone cut (delegation)
    /// processing in mind. The marked nodes would be the ones at delegation
    /// points. It is not expected that any other applications would need
    /// callbacks; they should use the versions of find without callbacks.
    /// The callbacks are not general functors for the same reason - we don't
    /// expect it to be needed.
    ///
    /// Another special feature of this version is the ability to record
    /// more detailed information regarding the search result.
    ///
    /// This information will be returned via the \c node_path parameter,
    /// which is an object of class \c DomainTreeNodeChain.
    /// The passed parameter must be empty.
    ///
    /// On success, the node sequence stored in \c node_path will contain all
    /// the ancestor nodes from the found node towards the root.
    /// For example, if we look for o.w.y.d.e.f in the example \ref diagram,
    /// \c node_path will contain w.y and d.e.f; the \c top() node of the
    /// chain will be o, w.y and d.e.f will be stored below it.
    ///
    /// This feature can be used to get the absolute name for a node; to
    /// do so, we need to travel upside from the node toward the root,
    /// concatenating all ancestor labels.  A node chain can also be
    /// used to find the next and previous nodes of a given node in the
    /// entire DomainTree; the \c nextNode() and \c previousNode()
    /// methods take a node chain as a parameter.
    ///
    /// \exception isc::BadValue node_path is not empty.
    ///
    /// \param target_labels_orig Target to be found
    /// \param node On success (either \c EXACTMATCH or \c PARTIALMATCH)
    ///     it will store a pointer to the matching node
    /// \param node_path Other search details will be stored (see the
    ///        description)
    /// \param callback If non- \c NULL, a call back function to be called
    ///     at marked nodes (see the description).
    /// \param callback_arg A caller supplied argument to be passed to
    ///     \c callback.
    ///
    /// \return As in the description, but in case of callback returning
    ///     \c true, it returns immediately with the current node.
    template <typename CBARG>
    Result find(const isc::dns::LabelSequence& target_labels_orig,
                DomainTreeNode<T>** node,
                DomainTreeNodeChain<T>& node_path,
                bool (*callback)(const DomainTreeNode<T>&, CBARG),
                CBARG callback_arg) const;

    /// \brief Simple find returning immutable node.
    ///
    /// Acts as described in the \ref find section, but returns immutable
    /// node pointer.
    template <typename CBARG>
    Result find(const isc::dns::LabelSequence& target_labels,
                const DomainTreeNode<T>** node,
                DomainTreeNodeChain<T>& node_path,
                bool (*callback)(const DomainTreeNode<T>&, CBARG),
                CBARG callback_arg) const
    {
        DomainTreeNode<T>* target_node = NULL;
        Result ret = find(target_labels, &target_node, node_path,
                          callback, callback_arg);
        if (ret != NOTFOUND) {
            *node = target_node;
        }
        return (ret);
    }
    //@}

    /// \brief return the next bigger node in DNSSEC order from a given node
    /// chain.
    ///
    /// This method identifies the next bigger node of the node currently
    /// referenced in \c node_path and returns it.
    /// This method also updates the passed \c node_path so that it will store
    /// the path for the returned next node.
    /// It will be convenient when we want to iterate over the all nodes
    /// of \c DomainTree; we can do this by calling this method repeatedly
    /// starting from the root node.
    ///
    /// \note \c nextNode() will iterate over all the nodes in
    /// DomainTree including empty nodes. If empty node isn't desired,
    /// it's easy to add logic to check return node and keep invoking \c
    /// nextNode() until the non-empty node is retrieved.
    ///
    /// \exception isc::BadValue node_path is empty.
    ///
    /// \param node_path A node chain that stores all the nodes along
    /// the path from root to node.
    ///
    /// \return An \c DomainTreeNode that is next bigger than \c node;
    /// if \c node is the largest, \c NULL will be returned.
    const DomainTreeNode<T>*
    nextNode(DomainTreeNodeChain<T>& node_path) const;

    /// \brief return the next smaller node in DNSSEC order from a node
    ///     searched by DomainTree::find().
    ///
    /// This acts similarly to \c nextNode(), but it walks in the other
    /// direction. But unlike \c nextNode(), this can start even if the
    /// node requested by \c find() was not found. In that case, it will
    /// identify the node that is previous to the queried name.
    ///
    /// \note \c previousNode() will iterate over all the nodes in DomainTree
    /// including empty nodes. If empty node isn't desired, it's easy to add
    /// logic to check return node and keep invoking \c previousNode() until the
    /// non-empty node is retrieved.
    ///
    /// \exception isc::BadValue node_path is empty.
    ///
    /// \param node_path A node chain that stores all the nodes along the path
    /// from root to node and the result of \c find(). This will get modified.
    /// You should not use the node_path again except for repetitive calls
    /// of this method.
    ///
    /// \return An \c DomainTreeNode that is next smaller than \c node;
    /// if \c node is the smallest, \c NULL will be returned.
    const DomainTreeNode<T>*
    previousNode(DomainTreeNodeChain<T>& node_path) const;

    /// \brief Get the total number of nodes in the tree
    ///
    /// It includes nodes internally created as a result of adding a domain
    /// name that is a subdomain of an existing node of the tree.
    /// This function is mainly intended to be used for debugging.
    int getNodeCount() const { return (node_count_); }

    /// \name Debug function
    //@{
    /// \brief Print the nodes in the trees.
    ///
    /// \param os A \c std::ostream object to which the tree is printed.
    /// \param depth A factor of the initial indentation.  Each line
    /// will begin with space character repeating <code>5 * depth</code>
    /// times.
    void dumpTree(std::ostream& os, unsigned int depth = 0) const;

    /// \brief Print the nodes in the trees for processing with
    /// Graphviz's dot.
    ///
    /// \param os A \c std::ostream object to which the tree is printed.
    /// \param show_pointers Show node and parent pointers in the node
    void dumpDot(std::ostream& os, bool show_pointers = false) const;
    //@}

    /// \name Modify functions
    //@{
    /// \brief Insert the domain name into the tree.
    ///
    /// It either finds an already existing node of the given name, or
    /// inserts a new one if none exists yet. In any case, the \c
    /// inserted_node parameter is set to point to that node. You can
    /// fill data into it or modify it.  So, if you don't know if a node
    /// exists or not and you need to modify it, just call insert and
    /// act by the result.
    ///
    /// Please note that the tree can add some empty nodes by itself, so
    /// don't assume that if you didn't insert a node of that name it
    /// doesn't exist.
    ///
    /// This method normally involves resource allocation.  If it fails
    /// the corresponding standard exception will be thrown.
    ///
    /// This method does not provide the strong exception guarantee in its
    /// strict sense; if an exception is thrown in the middle of this
    /// method, the internal structure may change.  However, it should
    /// still retain the same property as a mapping container before this
    /// method is called.  For example, the result of \c find() should be
    /// the same.  This method provides the weak exception guarantee in its
    /// normal sense.
    ///
    /// \param mem_sgmt A \c MemorySegment object for allocating memory of
    /// a new node to be inserted.  Must be the same segment as that used
    /// for creating the tree itself.
    /// \param name The name to be inserted into the tree.
    /// \param inserted_node This is an output parameter and is set to the
    ///     node.
    ///
    /// \return
    ///  - SUCCESS The node was added.
    ///  - ALREADYEXISTS There was already a node of that name, so it was not
    ///     added.
    Result insert(util::MemorySegment& mem_sgmt, const isc::dns::Name& name,
                  DomainTreeNode<T>** inserted_node);

    /// \brief Delete all tree nodes.
    ///
    /// \throw none.
    ///
    /// \param mem_sgmt The \c MemorySegment object used to insert the nodes
    /// (which was also used for creating the tree due to the requirement of
    /// \c inert()).
    template <typename DataDeleter>
    void deleteAllNodes(util::MemorySegment& mem_sgmt, DataDeleter deleter);

    /// \brief Swaps two tree's contents.
    ///
    /// This and \c other trees must have been created with the same
    /// memory segment (see the discussion in \c create()); otherwise the
    /// behavior is undefined.
    ///
    /// This acts the same as many std::*.swap functions, exchanges the
    /// contents. This doesn't throw anything.
    void swap(DomainTree<T>& other) {
        std::swap(root_, other.root_);
        std::swap(node_count_, other.node_count_);
    }
    //@}

private:
    /// \name DomainTree balance functions
    //@{
    void
    insertRebalance(typename DomainTreeNode<T>::DomainTreeNodePtr* root,
                    DomainTreeNode<T>* node);

    DomainTreeNode<T>*
    rightRotate(typename DomainTreeNode<T>::DomainTreeNodePtr* root,
                DomainTreeNode<T>* node);

    DomainTreeNode<T>*
    leftRotate(typename DomainTreeNode<T>::DomainTreeNodePtr* root,
               DomainTreeNode<T>* node);
    //@}

    /// \name Helper functions
    //@{
    /// \brief delete tree whose root is equal to node
    template <typename DataDeleter>
    void deleteHelper(util::MemorySegment& mem_sgmt,
                      DomainTreeNode<T> *node,
                      const DataDeleter& deleter);

    /// \brief Print the information of given DomainTreeNode.
    void dumpTreeHelper(std::ostream& os, const DomainTreeNode<T>* node,
                        unsigned int depth) const;

    /// \brief Print the information of given DomainTreeNode for dot.
    int dumpDotHelper(std::ostream& os, const DomainTreeNode<T>* node,
                      int* nodecount, bool show_pointers) const;

    /// \brief Indentation helper function for dumpTree
    static void indent(std::ostream& os, unsigned int depth);

    /// Split one node into two nodes for "prefix" and "suffix" parts of
    /// the labels of the original node, respectively.  The given node
    /// will hold the prefix, while a newly created node will hold the prefix.
    /// Note that the original node still represents the same domain name in
    /// the entire tree.  This ensures that a pointer to a node keeps its
    /// semantics even if the tree structure is changed (as long as the node
    /// itself remains valid).
    void nodeFission(util::MemorySegment& mem_sgmt, DomainTreeNode<T>& node,
                     const isc::dns::LabelSequence& new_prefix,
                     const isc::dns::LabelSequence& new_suffix);
    //@}

    typename DomainTreeNode<T>::DomainTreeNodePtr root_;
    /// the node count of current tree
    unsigned int node_count_;
    /// search policy for domaintree
    const bool needsReturnEmptyNode_;
};

template <typename T>
DomainTree<T>::DomainTree(bool returnEmptyNode) :
    root_(NULL),
    node_count_(0),
    needsReturnEmptyNode_(returnEmptyNode)
{
}

template <typename T>
DomainTree<T>::~DomainTree() {
    assert(node_count_ == 0);
}

template <typename T>
template <typename DataDeleter>
void
DomainTree<T>::deleteHelper(util::MemorySegment& mem_sgmt,
                            DomainTreeNode<T>* root,
                            const DataDeleter& deleter)
{
    while (root != NULL) {
        // If there is a left, right or down node, walk into it and
        // iterate.
        if (root->getLeft() != NULL) {
            DomainTreeNode<T>* node = root;
            root = root->getLeft();
            node->left_ = NULL;
        } else if (root->getRight() != NULL) {
            DomainTreeNode<T>* node = root;
            root = root->getRight();
            node->right_ = NULL;
        } else if (root->getDown() != NULL) {
            DomainTreeNode<T>* node = root;
            root = root->getDown();
            node->down_ = NULL;
        } else {
            // There are no left, right or down nodes, so we can
            // free this one and go back to its parent.
            DomainTreeNode<T>* node = root;
            root = root->getParent();
            deleter(node->data_.get());
            DomainTreeNode<T>::destroy(mem_sgmt, node);
            --node_count_;
        }
    }
}

template <typename T>
template <typename CBARG>
typename DomainTree<T>::Result
DomainTree<T>::find(const isc::dns::LabelSequence& target_labels_orig,
                    DomainTreeNode<T>** target,
                    DomainTreeNodeChain<T>& node_path,
                    bool (*callback)(const DomainTreeNode<T>&, CBARG),
                    CBARG callback_arg) const
{
    if (!node_path.isEmpty()) {
        isc_throw(isc::BadValue,
                  "DomainTree::find is given a non empty chain");
    }

    DomainTreeNode<T>* node = root_.get();
    Result ret = NOTFOUND;
    dns::LabelSequence target_labels(target_labels_orig);

    while (node != NULL) {
        node_path.last_compared_ = node;
        node_path.last_comparison_ = target_labels.compare(node->getLabels());
        const isc::dns::NameComparisonResult::NameRelation relation =
            node_path.last_comparison_.getRelation();

        if (relation == isc::dns::NameComparisonResult::EQUAL) {
            if (needsReturnEmptyNode_ || !node->isEmpty()) {
                node_path.push(node);
                *target = node;
                ret = EXACTMATCH;
            }
            break;
        } else if (relation == isc::dns::NameComparisonResult::NONE) {
            // If the two labels have no hierarchical relationship in terms
            // of matching, we should continue the binary search.
            node = (node_path.last_comparison_.getOrder() < 0) ?
                node->getLeft() : node->getRight();
        } else {
            if (relation == isc::dns::NameComparisonResult::SUBDOMAIN) {
                if (needsReturnEmptyNode_ || !node->isEmpty()) {
                    ret = PARTIALMATCH;
                    *target = node;
                    if (callback != NULL &&
                        node->getFlag(DomainTreeNode<T>::FLAG_CALLBACK)) {
                        if ((callback)(*node, callback_arg)) {
                            break;
                        }
                    }
                }
                node_path.push(node);
                target_labels.stripRight(
                    node_path.last_comparison_.getCommonLabels());
                node = node->getDown();
            } else {
                break;
            }
        }
    }

    return (ret);
}

template <typename T>
const DomainTreeNode<T>*
DomainTree<T>::nextNode(DomainTreeNodeChain<T>& node_path) const {
    if (node_path.isEmpty()) {
        isc_throw(isc::BadValue,
                  "DomainTree::nextNode is given an empty chain");
    }

    const DomainTreeNode<T>* node = node_path.top();
    // if node has sub domain, the next domain is the smallest
    // domain in sub domain tree
    const DomainTreeNode<T>* down = node->getDown();
    if (down != NULL) {
        const DomainTreeNode<T>* left_most = down;
        while (left_most->getLeft() != NULL) {
            left_most = left_most->getLeft();
        }
        node_path.push(left_most);
        return (left_most);
    }

    // try to find a successor.
    // if no successor found move to up level, the next successor
    // is the successor of up node in the up level tree, if
    // up node doesn't have successor we gonna keep moving to up
    // level
    while (!node_path.isEmpty()) {
        const DomainTreeNode<T>* up_node_successor =
            node_path.top()->successor();
        node_path.pop();
        if (up_node_successor != NULL) {
            node_path.push(up_node_successor);
            return (up_node_successor);
        }
    }

    return (NULL);
}

template <typename T>
const DomainTreeNode<T>*
DomainTree<T>::previousNode(DomainTreeNodeChain<T>& node_path) const {
    if (getNodeCount() == 0) {
        // Special case for empty trees. It would look every time like
        // we didn't search, because the last compared is empty. This is
        // a slight hack and not perfect, but this is better than throwing
        // on empty tree. And we probably won't meet an empty tree in practice
        // anyway.
        return (NULL);
    }
    if (node_path.last_compared_ == NULL) {
        isc_throw(isc::BadValue,
                  "DomainTree::previousNode() called before find()");
    }

    // If the relation isn't EQUAL, it means the find was called previously
    // and didn't find the exact node. Therefore we need to locate the place
    // to start iterating the chain of domains.
    //
    // The logic here is not too complex, we just need to take care to handle
    // all the cases and decide where to go from there.
    switch (node_path.last_comparison_.getRelation()) {
        case dns::NameComparisonResult::COMMONANCESTOR:
        case dns::NameComparisonResult::NONE:
            // We compared with a leaf in the tree and wanted to go to one of
            // the children. But the child was not there. It now depends on the
            // direction in which we wanted to go.
            if (node_path.last_comparison_.getOrder() < 0) {
                // We wanted to go left. So the one we compared with is
                // the one higher than we wanted. If we just put it into
                // the node_path, then the following algorithm below will find
                // the smaller one.
                //
                // This is exactly the same as with superdomain below.
                // Therefore, we just fall through to the next case.
            } else {
                // We wanted to go right. That means we want to output the
                // one which is the largest in the tree defined by the
                // compared one (it is either the compared one, or some
                // subdomain of it). There probably is not an easy trick
                // for this, so we just find the correct place.
                const DomainTreeNode<T>* current(node_path.last_compared_);
                while (current != NULL) {
                    node_path.push(current);
                    // Go a level down and as much right there as possible
                    current = current->getDown();
                    if (current != NULL) {
                        const DomainTreeNode<T>* right;
                        while ((right = current->getRight()) != NULL) {
                            current = right;
                        }
                    }
                }
                // Now, the one on top of the path is the one we want. We
                // return it now and leave it there, so we can search for
                // previous of it the next time we'are called.
                node_path.last_comparison_ =
                    dns::NameComparisonResult(0, 0,
                                              dns::NameComparisonResult::EQUAL);
                return (node_path.top());
            }
            // No break; here - we want to fall through. See above.
        case dns::NameComparisonResult::SUPERDOMAIN:
            // This is the case there's a "compressed" node and we looked for
            // only part of it. The node itself is larger than we wanted, but
            // if we put it to the node_path and then go one step left from it,
            // we get the correct result.
            node_path.push(node_path.last_compared_);
            // Correct the comparison result, so we won't trigger this case
            // next time previousNode is called. We already located the correct
            // place to start. The value is partly nonsense, but that doesn't
            // matter any more.
            node_path.last_comparison_ =
                dns::NameComparisonResult(0, 0,
                                          dns::NameComparisonResult::EQUAL);
            break;
        case dns::NameComparisonResult::SUBDOMAIN:
            // A subdomain means we returned the one above the searched one
            // already and it is on top of the stack. This is was smaller
            // than the one already, but we want to return yet smaller one.
            // So we act as if it was EQUAL.
            break;
        case dns::NameComparisonResult::EQUAL:
            // The find gave us an exact match or the previousNode was called
            // already, which located the exact node. The rest of the function
            // goes one domain left and returns it for us.
            break;
    }

    // So, the node_path now contains the path to a node we want previous for.
    // We just need to go one step left.

    if (node_path.isEmpty()) {
        // We got past the first one. So, we're returning NULL from
        // now on.
        return (NULL);
    }

    const DomainTreeNode<T>* node(node_path.top());

    // Try going left in this tree
    node = node->predecessor();
    if (node == NULL) {
        // We are the smallest ones in this tree. We go one level
        // up. That one is the smaller one than us.

        node_path.pop();
        if (node_path.isEmpty()) {
            // We're past the first one
            return (NULL);
        } else {
            return (node_path.top());
        }
    }

    // Exchange the node at the top of the path, as we move horizontaly
    // through the domain tree
    node_path.pop();
    node_path.push(node);

    // Try going as deep as possible, keeping on the right side of the trees
    const DomainTreeNode<T>* down;
    while ((down = node->getDown()) != NULL) {
        // Move to the tree below
        node = down;
        if (node != NULL) {
            // And get as much to the right of the tree as possible
            const DomainTreeNode<T>* right;
            while ((right = node->getRight()) != NULL) {
                node = right;
            }
        }
        // Now, we found the right-most node in the sub-tree, we need to
        // include it in the path
        node_path.push(node);
    }

    // Now, if the current node has no down_ pointer any more, it's the
    // correct one.
    return (node);
}

template <typename T>
typename DomainTree<T>::Result
DomainTree<T>::insert(util::MemorySegment& mem_sgmt,
                      const isc::dns::Name& target_name,
                      DomainTreeNode<T>** new_node)
{
    DomainTreeNode<T>* parent = NULL;
    DomainTreeNode<T>* current = root_.get();
    DomainTreeNode<T>* up_node = NULL;
    isc::dns::LabelSequence target_labels(target_name);

    int order = -1;
    // For possible LabelSequence serialization we always store labels data
    // in the separate local buffer.
    uint8_t labels_buf[dns::LabelSequence::MAX_SERIALIZED_LENGTH];
    while (current != NULL) {
        const dns::LabelSequence current_labels(
            dns::LabelSequence(current->getLabels(), labels_buf));
        const isc::dns::NameComparisonResult compare_result =
            target_labels.compare(current_labels);
        const isc::dns::NameComparisonResult::NameRelation relation =
            compare_result.getRelation();
        if (relation == isc::dns::NameComparisonResult::EQUAL) {
            if (new_node != NULL) {
                *new_node = current;
            }
            return (ALREADYEXISTS);
        } else if (relation == isc::dns::NameComparisonResult::NONE) {
            parent = current;
            order = compare_result.getOrder();
            current = order < 0 ? current->getLeft() : current->getRight();
        } else if (relation == isc::dns::NameComparisonResult::SUBDOMAIN) {
            // insert sub domain to sub tree
            parent = NULL;
            up_node = current;
            target_labels.stripRight(compare_result.getCommonLabels());
            current = current->getDown();
        } else {
            // The number of labels in common is fewer than the number of
            // labels at the current node, so the current node must be
            // adjusted to have just the common suffix, and a down pointer
            // made to a new tree.
            dns::LabelSequence common_ancestor = target_labels;
            common_ancestor.stripLeft(target_labels.getLabelCount() -
                                      compare_result.getCommonLabels());
            dns::LabelSequence new_prefix = current_labels;
            new_prefix.stripRight(compare_result.getCommonLabels());
            nodeFission(mem_sgmt, *current, new_prefix, common_ancestor);
            current = current->getParent();
        }
    }

    typename DomainTreeNode<T>::DomainTreeNodePtr* current_root =
        (up_node != NULL) ? &(up_node->down_) : &root_;
    // Once a new node is created, no exception will be thrown until the end
    // of the function, so we can simply create and hold a new node pointer.
    DomainTreeNode<T>* node = DomainTreeNode<T>::create(mem_sgmt,
                                                        target_labels);
    node->parent_ = parent;
    if (parent == NULL) {
        *current_root = node;
        // node is the new root of sub tree, so its init color is BLACK
        node->setColor(DomainTreeNode<T>::BLACK);
        node->setSubTreeRoot(true);
        node->parent_ = up_node;
    } else if (order < 0) {
        node->setSubTreeRoot(false);
        parent->left_ = node;
    } else {
        node->setSubTreeRoot(false);
        parent->right_ = node;
    }
    insertRebalance(current_root, node);
    if (new_node != NULL) {
        *new_node = node;
    }

    ++node_count_;
    return (SUCCESS);
}

template <typename T>
template <typename DataDeleter>
void
DomainTree<T>::deleteAllNodes(util::MemorySegment& mem_sgmt,
                              DataDeleter deleter)
{
    deleteHelper(mem_sgmt, root_.get(), deleter);
    root_ = NULL;
}

template <typename T>
void
DomainTree<T>::nodeFission(util::MemorySegment& mem_sgmt,
                           DomainTreeNode<T>& node,
                           const isc::dns::LabelSequence& new_prefix,
                           const isc::dns::LabelSequence& new_suffix)
{
    // Create and reset the labels.
    // Once a new node is created, no exception will be thrown until
    // the end of the function, and it will keep consistent behavior
    // (i.e., a weak form of strong exception guarantee) even if code
    // after the call to this function throws an exception.
    DomainTreeNode<T>* up_node = DomainTreeNode<T>::create(mem_sgmt,
                                                           new_suffix);
    node.resetLabels(new_prefix);

    up_node->parent_ = node.getParent();
    if (node.getParent() != NULL) {
        if (node.getParent()->getLeft() == &node) {
            node.getParent()->left_ = up_node;
        } else if (node.getParent()->getRight() == &node) {
            node.getParent()->right_ = up_node;
        } else {
            node.getParent()->down_ = up_node;
        }
    } else {
        this->root_ = up_node;
    }

    up_node->down_ = &node;
    node.parent_ = up_node;

    // inherit the left/right pointers from the original node, and set
    // the original node's left/right pointers to NULL.
    up_node->left_ = node.getLeft();
    if (node.getLeft() != NULL) {
        node.getLeft()->parent_ = up_node;
    }
    up_node->right_ = node.getRight();
    if (node.getRight() != NULL) {
        node.getRight()->parent_ = up_node;
    }
    node.left_ = NULL;
    node.right_ = NULL;

    // set color of both nodes; the initial subtree node color is BLACK
    up_node->setColor(node.getColor());
    node.setColor(DomainTreeNode<T>::BLACK);

    // set the subtree root flag of both nodes
    up_node->setSubTreeRoot(node.isSubTreeRoot());
    node.setSubTreeRoot(true);

    ++node_count_;
}


template <typename T>
void
DomainTree<T>::insertRebalance
    (typename DomainTreeNode<T>::DomainTreeNodePtr* root,
     DomainTreeNode<T>* node)
{
    DomainTreeNode<T>* uncle;
    DomainTreeNode<T>* parent;
    while (node != (*root).get() &&
           ((parent = node->getParent())->getColor()) ==
           DomainTreeNode<T>::RED) {
        // Here, node->parent_ is not NULL and it is also red, so
        // node->parent_->parent_ is also not NULL.
        if (parent == parent->getParent()->getLeft()) {
            uncle = parent->getParent()->getRight();

            if (uncle != NULL && uncle->getColor() ==
                DomainTreeNode<T>::RED) {
                parent->setColor(DomainTreeNode<T>::BLACK);
                uncle->setColor(DomainTreeNode<T>::BLACK);
                parent->getParent()->setColor(DomainTreeNode<T>::RED);
                node = parent->getParent();
            } else {
                if (node == parent->getRight()) {
                    node = parent;
                    leftRotate(root, node);
                    parent = node->getParent();
                }
                parent->setColor(DomainTreeNode<T>::BLACK);
                parent->getParent()->setColor(DomainTreeNode<T>::RED);
                rightRotate(root, parent->getParent());
            }
        } else {
            uncle = parent->getParent()->getLeft();

            if (uncle != NULL && uncle->getColor() ==
                DomainTreeNode<T>::RED) {
                parent->setColor(DomainTreeNode<T>::BLACK);
                uncle->setColor(DomainTreeNode<T>::BLACK);
                parent->getParent()->setColor(DomainTreeNode<T>::RED);
                node = parent->getParent();
            } else {
                if (node == parent->getLeft()) {
                    node = parent;
                    rightRotate(root, node);
                    parent = node->getParent();
                }
                parent->setColor(DomainTreeNode<T>::BLACK);
                parent->getParent()->setColor(DomainTreeNode<T>::RED);
                leftRotate(root, parent->getParent());
            }
        }
    }

    (*root)->setColor(DomainTreeNode<T>::BLACK);
}


template <typename T>
DomainTreeNode<T>*
DomainTree<T>::leftRotate
    (typename DomainTreeNode<T>::DomainTreeNodePtr* root,
     DomainTreeNode<T>* node)
{
    DomainTreeNode<T>* const right = node->getRight();
    DomainTreeNode<T>* const rleft = right->getLeft();
    node->right_ = rleft;
    if (rleft != NULL) {
        rleft->parent_ = node;
    }

    DomainTreeNode<T>* const parent = node->getParent();
    right->parent_ = parent;

    if (!node->isSubTreeRoot()) {
        right->setSubTreeRoot(false);
        if (node == parent->getLeft()) {
            parent->left_ = right;
        } else  {
            parent->right_ = right;
        }
    } else {
        right->setSubTreeRoot(true);
        *root = right;
    }

    right->left_ = node;
    node->parent_ = right;
    node->setSubTreeRoot(false);
    return (node);
}

template <typename T>
DomainTreeNode<T>*
DomainTree<T>::rightRotate
    (typename DomainTreeNode<T>::DomainTreeNodePtr* root,
     DomainTreeNode<T>* node)
{
    DomainTreeNode<T>* const left = node->getLeft();
    DomainTreeNode<T>* const lright = left->getRight();
    node->left_ = lright;
    if (lright != NULL) {
        lright->parent_ = node;
    }

    DomainTreeNode<T>* const parent = node->getParent();
    left->parent_ = parent;

    if (!node->isSubTreeRoot()) {
        left->setSubTreeRoot(false);
        if (node == parent->getRight()) {
            parent->right_ = left;
        } else  {
            parent->left_ = left;
        }
    } else {
        left->setSubTreeRoot(true);
        *root = left;
    }
    left->right_ = node;
    node->parent_ = left;
    node->setSubTreeRoot(false);

    return (node);
}


template <typename T>
void
DomainTree<T>::dumpTree(std::ostream& os, unsigned int depth) const {
    indent(os, depth);
    os << "tree has " << node_count_ << " node(s)\n";
    dumpTreeHelper(os, root_.get(), depth);
}

template <typename T>
void
DomainTree<T>::dumpTreeHelper(std::ostream& os,
                              const DomainTreeNode<T>* node,
                              unsigned int depth) const
{
    if (node == NULL) {
        indent(os, depth);
        os << "NULL\n";
        return;
    }

    indent(os, depth);
    os << node->getLabels() << " ("
       << ((node->getColor() == DomainTreeNode<T>::BLACK) ? "black" : "red")
       << ")";
    if (node->isEmpty()) {
        os << " [invisible]";
    }
    if (node->isSubTreeRoot()) {
        os << " [subtreeroot]";
    }
    os << "\n";

    const DomainTreeNode<T>* down = node->getDown();
    if (down != NULL) {
        indent(os, depth + 1);
        os << "begin down from " << node->getLabels() << "\n";
        dumpTreeHelper(os, down, depth + 1);
        indent(os, depth + 1);
        os << "end down from " << node->getLabels() << "\n";
    }
    dumpTreeHelper(os, node->getLeft(), depth + 1);
    dumpTreeHelper(os, node->getRight(), depth + 1);
}

template <typename T>
void
DomainTree<T>::indent(std::ostream& os, unsigned int depth) {
    static const unsigned int INDENT_FOR_EACH_DEPTH = 5;
    os << std::string(depth * INDENT_FOR_EACH_DEPTH, ' ');
}

template <typename T>
void
DomainTree<T>::dumpDot(std::ostream& os, bool show_pointers) const {
    int nodecount = 0;

    os << "digraph g {\n";
    os << "node [shape = record,height=.1];\n";
    dumpDotHelper(os, root_.get(), &nodecount, show_pointers);
    os << "}\n";
}

template <typename T>
int
DomainTree<T>::dumpDotHelper(std::ostream& os,
                             const DomainTreeNode<T>* node,
                             int* nodecount, bool show_pointers) const
{
    if (node == NULL) {
        return 0;
    }

    int l = dumpDotHelper(os, node->getLeft(), nodecount, show_pointers);
    int r = dumpDotHelper(os, node->getRight(), nodecount, show_pointers);
    int d = dumpDotHelper(os, node->getDown(), nodecount, show_pointers);

    *nodecount += 1;

    os << "node" << *nodecount <<
          "[label = \"<f0> |<f1> " << node->getLabels() <<
          "|<f2>";
    if (show_pointers) {
        os << "|<f3> n=" << node << "|<f4> p=" << node->getParent();
    }
    os << "\"] [";

    if (node->getColor() == DomainTreeNode<T>::RED) {
        os << "color=red";
    } else {
        os << "color=black";
    }

    if (node->isSubTreeRoot()) {
        os << ",penwidth=3";
    }

    if (node->isEmpty()) {
        os << ",style=filled,fillcolor=lightgrey";
    }

    os << "];\n";

    if (node->getLeft() != NULL) {
        os << "\"node" << *nodecount << "\":f0 -> \"node" << l << "\":f1;\n";
    }

    if (node->getDown() != NULL) {
        os << "\"node" << *nodecount << "\":f1 -> \"node" << d <<
              "\":f1 [penwidth=5];\n";
    }

    if (node->getRight() != NULL) {
        os << "\"node" << *nodecount << "\":f2 -> \"node" << r << "\":f1;\n";
    }

    return (*nodecount);
}

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif  // _DOMAINTREE_H

// Local Variables:
// mode: c++
// End:
