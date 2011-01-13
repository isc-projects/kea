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

#ifndef _RBTREE_H
#define _RBTREE_H 1

//! \file datasrc/rbtree.h
///
/// \note The purpose of the RBTree is to provide a generic map with
///     domain names as the key that can be used by various BIND 10 modules or
///     even by other applications.  However, because of some unresolved design
///     issue, the design and interface are not fixed, and RBTree isn't ready
///     to be used as a base data structure by other modules.

#include <dns/name.h>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <exception>
#include <ostream>
#include <algorithm>

namespace isc {
namespace datasrc {

namespace helper {

/// \brief Helper function to remove the base domain from super domain.
///
/// The precondition of this function is the super_name contains the
/// sub_name so
/// \code Name a("a.b.c");
/// Name b("b.c");
/// Name c = a - b;
/// \endcode
/// c will contain "a".
///
/// \note Functions in this namespace is not intended to be used outside of
///     RBTree implementation.
inline isc::dns::Name
operator-(const isc::dns::Name& super_name, const isc::dns::Name& sub_name) {
    return (super_name.split(0, super_name.getLabelCount() -
                             sub_name.getLabelCount()));
}
}

template <typename T>
class RBTree;

/// \brief \c RBNode is used by RBTree to store any data related to one domain
///     name.
///
/// This is meant to be used only from RBTree. It is meaningless to inherit it
/// or create instances of it from elsewhere. For that reason, the constructor
/// is private.
///
/// It serves three roles. One is to keep structure of the \c RBTree as a
/// red-black tree. For that purpose, it has left, right and parent pointers
/// and color member. These are private and accessed only from within the tree.
///
/// The second one is to store data for one domain name. The data related
/// functions can be used to access and set the data.
///
/// The third role is to keep the hierarchy of domains. The down pointer points
/// to a subtree of subdomains. Note that we can traverse the hierarchy down,
/// but not up.
///
/// One special kind of node is non-terminal node. It has subdomains with
/// RRsets, but doesn't have any RRsets itself.
template <typename T>
class RBNode : public boost::noncopyable {
private:
    /// The RBNode is meant for use from within RBTree, so it has access to
    /// it.
    friend class RBTree<T>;

    /// \name Constructors
    ///
    /// \note The existence of a RBNode without a RBTree is meaningless.
    ///     Therefore the constructors are private.
    //@{

    /// \brief Default constructor.
    ///
    /// This constructor is provided specifically for generating a special
    /// "null" node.
    RBNode();

    /// \brief Constructor from the node name.
    ///
    /// \param name The *relative* domain name (if this will live inside
    ///     a.b.c and is called d.e.a.b.c, then you pass d.e).
    RBNode(const isc::dns::Name& name);
    //@}

public:
    /// \brief Alias for shared pointer to the data.
    typedef boost::shared_ptr<T> NodeDataPtr;

    /// \brief Destructor
    ///
    /// It might seem strange that constructors are private and destructor
    /// public, but this is needed because of shared pointers need access
    /// to the destructor.
    ///
    /// You should never call anything like:
    /// \code delete pointer_to_node; \endcode
    /// The RBTree handles both creation and destructoion of nodes.
    ~RBNode();

    /// \name Getter functions.
    //@{
    /// \brief Return the name of current node.
    ///
    /// It's relative to its containing node.
    ///
    /// To get the absolute name of one node, the node path from the top node
    /// to current node has to be recorded.
    const isc::dns::Name& getName() const { return (name_); }

    /// \brief Return the data stored in this node.
    ///
    /// You should not delete the data, it is handled by shared pointers.
    NodeDataPtr& getData() { return (data_); }
    /// \brief Return the data stored in this node.
    const NodeDataPtr& getData() const { return (data_); }

    /// \brief return whether the node has related data.
    ///
    /// There can be empty nodes inside the RBTree. They are usually the
    /// non-terminal domains, but it is possible (yet probably meaningless)
    /// empty nodes anywhere.
    bool isEmpty() const { return (data_.get() == NULL); }
    //@}

    /// \name Setter functions.
    //@{
    /// \brief Set the data stored in the node.
    void setData(const NodeDataPtr& data) { data_ = data; }
    //@}

    /// \name Callback related methods
    ///
    /// See the description of \c RBTree<T>::find() about callbacks.
    ///
    /// These methods never throw an exception.
    //@{
    /// Return if callback is enabled at the node.
    bool isCallbackEnabled() const { return (callback_required_); }

    /// Enable callback at the node.
    void enableCallback() { callback_required_ = true; }

    /// Disable callback at the node.
    void disableCallback() { callback_required_ = false; }
    //@}


private:
    /// \brief Define rbnode color
    enum RBNodeColor {BLACK, RED};
    /// This is a factory class method of a special singleton null node.
    static RBNode<T>* NULL_NODE() {
        static RBNode<T> null_node;
        return (&null_node);
    }

    /// \name Data to maintain the rbtree structure.
    //@{
    RBNode<T>*  parent_;
    RBNode<T>*  left_;
    RBNode<T>*  right_;
    RBNodeColor color_;
    //@}

    /// \brief Relative name of the node.
    isc::dns::Name     name_;
    /// \brief Data stored here.
    NodeDataPtr       data_;

    /// \brief The subdomain tree.
    ///
    /// This points to the root node of trees of subdomains of this domain.
    ///
    /// \par Adding down pointer to \c RBNode has two purposes:
    /// \li Accelerate the search process, with sub domain tree, it splits the
    ///     big flat tree into several hierarchy trees.
    /// \li It saves memory useage as it allows storing only relative names,
    ///     avoiding storage of the same domain labels multiple times.
    RBNode<T>*  down_;

    /// \brief If callback should be called when traversing this node in
    /// RBTree::find().
    ///
    /// \todo It might be needed to put it into more general attributes field.
    bool callback_required_;
};


// This is only to support NULL nodes.
template <typename T>
RBNode<T>::RBNode() :
    parent_(this),
    left_(this),
    right_(this),
    color_(BLACK),
    // dummy name, the value doesn't matter:
    name_(isc::dns::Name::ROOT_NAME()),
    down_(this),
    callback_required_(false)
{
}

template <typename T>
RBNode<T>::RBNode(const isc::dns::Name& name) :
    parent_(NULL_NODE()),
    left_(NULL_NODE()),
    right_(NULL_NODE()),
    color_(RED),
    name_(name),
    down_(NULL_NODE()),
    callback_required_(false)
{
}


template <typename T>
RBNode<T>::~RBNode() {
}

// note: the following class description is documented using multiline comments
// because the verbatim diagram contain a backslash, which could be interpreted
// as escape of newline in singleline comment.
/**
 *  \brief \c RBTree class represents all the domains with the same suffix.
 *      It can be used to store the domains in one zone, for example.
 *
 *  RBTree is a generic map from domain names to any kind of data. Internally,
 *  it uses a red-black tree. However, it isn't one tree containing everything.
 *  Subdomains are trees, so this structure is recursive - trees inside trees.
 *  But, from the interface point of view, it is opaque data structure.
 *
 *  \c RBTree splits the domain space into hierarchy red black trees; nodes
 * in one tree has the same base name. The benefit of this struct is that:
 *  - Enhances the query performace compared with one big flat red black tree.
 *  - Decreases the memory footprint, as it doesn't store the suffix labels
 *      multiple times.
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
 * the tree will looks like:
 *  \verbatim
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
 *  \note open problems:
 *  - current \c find() function only returns non-empty nodes, so there is no
 *    difference between find a non existent name and a name corresponding to
 *    an empty non-terminal nodes, but in DNS query logic, they are different
 *  \todo
 *  - add remove interface
 *  - add iterator to iterate over the whole \c RBTree.  This may be necessary,
 *    for example, to support AXFR.
 *  - since \c RBNode only has down pointer without up pointer, the node path
 *    during finding should be recorded for later use
 */
template <typename T>
class RBTree : public boost::noncopyable {
    friend class RBNode<T>;
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

    /// \name Constructor and Destructor
    //@{
    /// The constructor.
    ///
    /// It never throws an exception.
    explicit RBTree();

    /// \b Note: RBTree is not intended to be inherited so the destructor
    /// is not virtual
    ~RBTree();
    //@}

    /// \name Find methods
    ///
    /// \brief Find the node that gives a longest match against the given name.
    ///
    /// \anchor find
    ///
    /// These methods search the RBTree for a node whose name is a longest
    /// against name. The found node, if any, is returned via the node pointer.
    ///
    /// By default, nodes that don't have data (see RBNode::isEmpty) are
    /// ignored and the result can be NOTFOUND even if there's a node whose
    /// name mathes. The plan is to introduce a "no data OK" mode for this
    /// method, that would match any node of the tree regardless of wheather
    /// the node has any data or not.
    ///
    /// The case with "no data OK" mode is not as easy as it seems. For example
    /// in the diagram shown in the class description, the name y.d.e.f is
    /// logically contained in the tree as part of the node w.y.  It cannot be
    /// identified simply by checking whether existing nodes (such as
    /// d.e.f or w.y) has data.
    ///
    /// These methods involves operations on names that can throw an exception.
    /// If that happens the exception will be propagated to the caller.
    /// The callback function should generally not throw an exception, but
    /// if it throws, the exception will be propagated to the caller.
    ///
    /// The \c name parameter says what should be found. The node parameter
    /// is output only and in case of EXACTMATCH and PARTIALMATCH, it is set
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

    /// \brief Find with callback.
    ///
    /// \anchor callback
    ///
    /// This version of find calls the callback whenever traversing (on the
    /// way from root down the tree) a marked node on the way down through the
    /// domain namespace (see RBNode::enableCallback and related functions).
    ///
    /// If you return true from the callback, the search is stopped and a
    /// PARTIALMATCH is returned with the given node. Note that this node
    /// doesn't really need to be the one with longest possible match.
    ///
    /// This callback mechanism was designed with zone cut (delegation)
    /// processing in mind. The marked nodes would be the ones at delegation
    /// points. It is not expected that any other applications would need
    /// callbacks; they should use the versions of find without callbacks.
    /// The callbacks are not general functors for the same reason - we don't
    /// expect it to be needed.
    ///
    /// \param name Target to be found
    /// \param node On success (either \c EXACTMATCH or \c PARTIALMATCH)
    ///     it will store a pointer to the matching node
    /// \param callback If non \c NULL, a call back function to be called
    ///     at marked nodes (see above).
    /// \param callback_arg A caller supplied argument to be passed to
    ///     \c callback.
    ///
    /// \return As described above, but in case of callback returning true,
    ///     it returns immediately with the current node.
    template <typename CBARG>
    Result find(const isc::dns::Name& name, RBNode<T>** node,
                bool (*callback)(const RBNode<T>&, CBARG),
                CBARG callback_arg) const;

    /// \brief Find with callback returning immutable node.
    ///
    /// It has the same behaviour as the find with \ref callback version.
    template <typename CBARG>
    Result find(const isc::dns::Name& name, const RBNode<T>** node,
                bool (*callback)(const RBNode<T>&, CBARG),
                CBARG callback_arg) const;

    /// \brief Simple find.
    ///
    /// Acts as described in the \ref find section.
    Result find(const isc::dns::Name& name, RBNode<T>** node) const {
        return (find<void*>(name, node, NULL, NULL));
    }

    /// \brieg Simple find returning immutable node.
    ///
    /// Acts as described in the \ref find section, but returns immutable node
    /// pointer.
    Result find(const isc::dns::Name& name, const RBNode<T>** node) const {
        return (find<void*>(name, node, NULL, NULL));
    }
    //@}

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
    //@}

    /// \name Modify functions
    //@{
    /// \brief Insert the domain name into the tree.
    ///
    /// It either finds an already existing node of the given name or inserts
    /// a new one, if none exists yet. In any case, the inserted_node parameter
    /// is set to point to that node. You can fill data into it or modify it.
    /// So, if you don't know if a node exists or not and you need to modify
    /// it, just call insert and act by the result.
    ///
    /// Please note that the tree can add some empty nodes by itself, so don't
    /// assume that if you didn't insert a node of that name it doesn't exist.
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
    /// \param name The name to be inserted into the tree.
    /// \param inserted_node This is an output parameter and is set to the
    ///     node.
    ///
    /// \return
    ///  - SUCCESS The node was added.
    ///  - ALREADYEXISTS There was already a node of that name, so it was not
    ///     added.
    Result insert(const isc::dns::Name& name, RBNode<T>** inserted_node);

    /// \brief Swaps two tree's contents.
    ///
    /// This acts the same as many std::*.swap functions, exchanges the
    /// contents. This doesn't throw anything.
    void swap(RBTree<T>& other) {
        std::swap(root_, other.root_);
        std::swap(NULLNODE, other.NULLNODE);
        std::swap(node_count_, other.node_count_);
    }
    //@}

private:
    /// \name RBTree balance functions
    //@{
    void insertRebalance(RBNode<T>** root, RBNode<T>* node);
    RBNode<T>* rightRotate(RBNode<T>** root, RBNode<T>* node);
    RBNode<T>* leftRotate(RBNode<T>** root, RBNode<T>* node);
    //@}

    /// \name Helper functions
    //@{
    /// \brief delete tree whose root is equal to node
    void deleteHelper(RBNode<T> *node);
    /// \brief find the node with name
    ///
    /// Internal searching function.
    ///
    /// \param name What should be found.
    /// \param up It will point to the node whose down pointer points
    ///     to the tree containing node. If we looked for o.w.y.d.e.f in the
    ///     \ref diagram, the up would point to the w.y node.
    ///     This parameter is not used currently, but it will be soon.
    /// \param node The found node.
    template <typename CBARG>
    Result findHelper(const isc::dns::Name& name, const RBNode<T>** up,
                      RBNode<T>** node,
                      bool (*callback)(const RBNode<T>&, CBARG),
                      CBARG callback_arg) const;
    void dumpTreeHelper(std::ostream& os, const RBNode<T>* node,
                        unsigned int depth) const;
    /// \brief Indentation helper function for dumpTree
    static void indent(std::ostream& os, unsigned int depth);

    /// Split one node into two nodes, keep the old node and create one new
    /// node, old node will hold the base name, new node will be the down node
    /// of old node, new node will hold the sub_name, the data
    /// of old node will be move into new node, and old node became non-terminal
    void nodeFission(RBNode<T>& node, const isc::dns::Name& sub_name);
    //@}

    RBNode<T>*  root_;
    RBNode<T>*  NULLNODE;
    /// the node count of current tree
    unsigned int node_count_;
};

template <typename T>
RBTree<T>::RBTree() {
    NULLNODE = RBNode<T>::NULL_NODE();
    root_ = NULLNODE;
    node_count_ = 0;
}

template <typename T>
RBTree<T>::~RBTree() {
    deleteHelper(root_);
    assert(node_count_ == 0);
}

template <typename T>
void RBTree<T> ::deleteHelper(RBNode<T> *root) {
    if (root == NULLNODE) {
        return;
    }

    RBNode<T> *node = root;
    while (root->left_ != NULLNODE || root->right_ != NULLNODE) {
        while (node->left_ != NULLNODE || node->right_ != NULLNODE) {
            node = (node->left_ != NULLNODE) ? node->left_ : node->right_;
        }

        RBNode<T> *parent = node->parent_;
        if (parent->left_ == node) {
            parent->left_ = NULLNODE;
        } else {
            parent->right_ = NULLNODE;
        }

        deleteHelper(node->down_);
        delete node;
        --node_count_;
        node = parent;
    }

    deleteHelper(root->down_);
    delete root;
    --node_count_;
}

template <typename T> template <typename CBARG>
typename RBTree<T>::Result
RBTree<T>::find(const isc::dns::Name& name, RBNode<T>** node,
                bool (*callback)(const RBNode<T>&, CBARG),
                CBARG callback_arg) const
{
    const RBNode<T>* up_node = NULLNODE;
    return (findHelper(name, &up_node, node, callback, callback_arg));
}

template <typename T> template <typename CBARG>
typename RBTree<T>::Result
RBTree<T>::find(const isc::dns::Name& name, const RBNode<T>** node,
                bool (*callback)(const RBNode<T>&, CBARG),
                CBARG callback_arg) const
{
    const RBNode<T>* up_node;
    RBNode<T>* target_node;
    const typename RBTree<T>::Result ret =
        findHelper(name, &up_node, &target_node, callback, callback_arg);
    if (ret != NOTFOUND) {
        *node = target_node;
    }
    return (ret);
}

template <typename T> template <typename CBARG>
typename RBTree<T>::Result
RBTree<T>::findHelper(const isc::dns::Name& target_name,
                      const RBNode<T>** up_node,
                      RBNode<T>** target,
                      bool (*callback)(const RBNode<T>&, CBARG),
                      CBARG callback_arg) const
{
    using namespace helper;

    RBNode<T>* node = root_;
    typename RBTree<T>::Result ret = NOTFOUND;
    *up_node = NULLNODE;
    isc::dns::Name name = target_name;

    while (node != NULLNODE) {
        const isc::dns::NameComparisonResult compare_result =
            name.compare(node->name_);
        const isc::dns::NameComparisonResult::NameRelation relation =
            compare_result.getRelation();
        if (relation == isc::dns::NameComparisonResult::EQUAL) {
            if (!node->isEmpty()) {
                *target = node;
                ret = EXACTMATCH;
            }
            break;
        } else {
            const int common_label_count = compare_result.getCommonLabels();
            // If the common label count is 1, there is no common label between
            // the two names, except the trailing "dot".
            if (common_label_count == 1) {
                node = (compare_result.getOrder() < 0) ?
                    node->left_ : node->right_;
            } else if (relation == isc::dns::NameComparisonResult::SUBDOMAIN) {
                if (!node->isEmpty()) {
                    ret = RBTree<T>::PARTIALMATCH;
                    *target = node;
                    if (callback != NULL && node->callback_required_) {
                        if ((callback)(*node, callback_arg)) {
                            break;
                        }
                    }
                }
                *up_node = node;
                name = name - node->name_;
                node = node->down_;
            } else {
                break;
            }
        }
    }

    return (ret);
}

template <typename T>
typename RBTree<T>::Result
RBTree<T>::insert(const isc::dns::Name& target_name, RBNode<T>** new_node) {
    using namespace helper;
    RBNode<T>* parent = NULLNODE;
    RBNode<T>* current = root_;
    RBNode<T>* up_node = NULLNODE;
    isc::dns::Name name = target_name;

    int order = -1;
    while (current != NULLNODE) {
        const isc::dns::NameComparisonResult compare_result =
            name.compare(current->name_);
        const isc::dns::NameComparisonResult::NameRelation relation =
            compare_result.getRelation();
        if (relation == isc::dns::NameComparisonResult::EQUAL) {
            if (new_node != NULL) {
                *new_node = current;
            }
            return (ALREADYEXISTS);
        } else {
            const int common_label_count = compare_result.getCommonLabels();
            if (common_label_count == 1) {
                parent = current;
                order = compare_result.getOrder();
                current = order < 0 ? current->left_ : current->right_;
            } else {
                // insert sub domain to sub tree
                if (relation == isc::dns::NameComparisonResult::SUBDOMAIN) {
                    parent = NULLNODE;
                    up_node = current;
                    name = name - current->name_;
                    current = current->down_;
                } else {
                    // The number of labels in common is fewer
                    // than the number of labels at the current
                    // node, so the current node must be adjusted
                    // to have just the common suffix, and a down
                    // pointer made to a new tree.
                    const isc::dns::Name common_ancestor = name.split(
                        name.getLabelCount() - common_label_count,
                        common_label_count);
                    nodeFission(*current, common_ancestor);
                }
            }
        }
    }

    RBNode<T>** current_root = (up_node != NULLNODE) ?
        &(up_node->down_) : &root_;
    // using auto_ptr here is avoid memory leak in case of exceptoin raised
    // after the RBNode creation, if we can make sure no exception will be
    // raised until the end of the function, we can remove it for optimization
    std::auto_ptr<RBNode<T> > node(new RBNode<T>(name));
    node->parent_ = parent;
    if (parent == NULLNODE) {
        *current_root = node.get();
        //node is the new root of sub tree, so its init color
        // is BLACK
        node->color_ = RBNode<T>::BLACK;
    } else if (order < 0) {
        parent->left_ = node.get();
    } else {
        parent->right_ = node.get();
    }
    insertRebalance(current_root, node.get());
    if (new_node != NULL) {
        *new_node = node.get();
    }

    ++node_count_;
    node.release();
    return (SUCCESS);
}

template <typename T>
void
RBTree<T>::nodeFission(RBNode<T>& node, const isc::dns::Name& base_name) {
    using namespace helper;
    const isc::dns::Name sub_name = node.name_ - base_name;
    // using auto_ptr here is to avoid memory leak in case of exception raised
    // after the RBNode creation
    std::auto_ptr<RBNode<T> > down_node(new RBNode<T>(sub_name));
    node.name_ = base_name;
    // the rest of this function should be exception free so that it keeps
    // consistent behavior (i.e., a weak form of strong exception guarantee)
    // even if code after the call to this function throws an exception.
    std::swap(node.data_, down_node->data_);
    std::swap(node.callback_required_, down_node->callback_required_);
    down_node->down_ = node.down_;
    node.down_ = down_node.get();
    // root node of sub tree, the initial color is BLACK
    down_node->color_ = RBNode<T>::BLACK;
    ++node_count_;
    down_node.release();
}

template <typename T>
void
RBTree<T>::insertRebalance(RBNode<T>** root, RBNode<T>* node) {

    RBNode<T>* uncle;
    while (node != *root && node->parent_->color_ == RBNode<T>::RED) {
        if (node->parent_ == node->parent_->parent_->left_) {
            uncle = node->parent_->parent_->right_;

            if (uncle->color_ == RBNode<T>::RED) {
                node->parent_->color_ = RBNode<T>::BLACK;
                uncle->color_ = RBNode<T>::BLACK;
                node->parent_->parent_->color_ = RBNode<T>::RED;
                node = node->parent_->parent_;
            } else {
                if (node == node->parent_->right_) {
                    node = node->parent_;
                    leftRotate(root, node);
                }
                node->parent_->color_ = RBNode<T>::BLACK;
                node->parent_->parent_->color_ = RBNode<T>::RED;
                rightRotate(root, node->parent_->parent_);
            }
        } else {
            uncle = node->parent_->parent_->left_;
            if (uncle->color_ == RBNode<T>::RED) {
                node->parent_->color_ = RBNode<T>::BLACK;
                uncle->color_ = RBNode<T>::BLACK;
                node->parent_->parent_->color_ = RBNode<T>::RED;
                node = node->parent_->parent_;
            } else {
                if (node == node->parent_->left_) {
                    node = node->parent_;
                    rightRotate(root, node);
                }
                node->parent_->color_ = RBNode<T>::BLACK;
                node->parent_->parent_->color_ = RBNode<T>::RED;
                leftRotate(root, node->parent_->parent_);
            }
        }
    }

    (*root)->color_ = RBNode<T>::BLACK;
}


template <typename T>
RBNode<T>*
RBTree<T>::leftRotate(RBNode<T>** root, RBNode<T>* node) {
    RBNode<T>* right = node->right_;
    node->right_ = right->left_;
    if (right->left_ != NULLNODE)
        right->left_->parent_ = node;

    right->parent_ = node->parent_;

    if (node->parent_ != NULLNODE) {
        if (node == node->parent_->left_) {
            node->parent_->left_ = right;
        } else  {
            node->parent_->right_ = right;
        }
    } else {
        *root = right;
    }

    right->left_ = node;
    node->parent_ = right;
    return (node);
}

template <typename T>
RBNode<T>*
RBTree<T>::rightRotate(RBNode<T>** root, RBNode<T>* node) {
    RBNode<T>* left = node->left_;
    node->left_ = left->right_;
    if (left->right_ != NULLNODE)
        left->right_->parent_ = node;

    left->parent_ = node->parent_;

    if (node->parent_ != NULLNODE) {
        if (node == node->parent_->right_) {
            node->parent_->right_ = left;
        } else  {
            node->parent_->left_ = left;
        }
    } else {
        *root = left;
    }
    left->right_ = node;
    node->parent_ = left;
    return (node);
}

template <typename T>
void
RBTree<T>::dumpTree(std::ostream& os, unsigned int depth) const {
    indent(os, depth);
    os << "tree has " << node_count_ << " node(s)\n";
    dumpTreeHelper(os, root_, depth);
}

template <typename T>
void
RBTree<T>::dumpTreeHelper(std::ostream& os, const RBNode<T>* node,
                          unsigned int depth) const
{
    if (node == NULLNODE) {
        indent(os, depth);
        os << "NULL\n";
        return;
    }

    indent(os, depth);
    os << node->name_.toText() << " ("
              << ((node->color_ == RBNode<T>::BLACK) ? "black" : "red") << ")";
    os << ((node->isEmpty()) ? "[invisible] \n" : "\n");

    if (node->down_ != NULLNODE) {
        indent(os, depth + 1);
        os << "begin down from " << node->name_.toText() << "\n";
        dumpTreeHelper(os, node->down_, depth + 1);
        indent(os, depth + 1);
        os << "end down from " << node->name_.toText() << "\n";
    }
    dumpTreeHelper(os, node->left_, depth + 1);
    dumpTreeHelper(os, node->right_, depth + 1);
}

template <typename T>
void
RBTree<T>::indent(std::ostream& os, unsigned int depth) {
    static const unsigned int INDENT_FOR_EACH_DEPTH = 5;
    os << std::string(depth * INDENT_FOR_EACH_DEPTH, ' ');
}

}
}

#endif  // _RBTREE_H

// Local Variables:
// mode: c++
// End:
