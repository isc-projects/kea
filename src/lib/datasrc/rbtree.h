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
/// domain names as the key that can be used by various BIND 10 modules or
/// even by other applications.  However, because of some unresolved design
/// issue, the design and interface are not fixed, and RBTree isn't ready to
/// be used as a base data structure by other modules.

#include <dns/name.h>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <exception>
#include <ostream>
#include <algorithm>

namespace isc {
namespace datasrc {

namespace helper {

/// Helper function to remove the base domain from super domain
///
/// the precondition of this function is the super_name contains the
/// sub_name so
/// \code Name a("a.b.c");
/// Name b("b.c");
/// Name c = a - b;
/// \endcode
///
/// \note function in this namespace is not intended to be used outside.
inline isc::dns::Name
operator-(const isc::dns::Name& super_name, const isc::dns::Name& sub_name) {
    return (super_name.split(0, super_name.getLabelCount() -
                             sub_name.getLabelCount()));
}
}

template <typename T>
class RBTree;

/// \brief \c RBNode use by RBTree to store any data related to one domain name
///
/// It has two roles, the first one is as one node in the \c RBTree,
/// the second one is to store the data related to one domain name and maintain
/// the domain name hierarchy struct in one domain name space.
/// As for the first role, it has left, right, parent and color members
/// which is used to keep the balance of the \c RBTree.
/// As for the second role, \c RBNode use down pointer to refer to all its sub
/// domains, so the name of current node always relative to the up node. since
/// we only has down pointer without up pointer, so we can only walk down from
/// top domain to sub domain.
/// One special kind of node is non-terminal node
/// which has subdomains with RRset but itself doesn't have any RRsets.
///
/// \note \c RBNode basically used internally by RBTree, it is meaningless to
/// inherited from it or create it without \c RBTree.
template <typename T>
class RBNode : public boost::noncopyable {
public:
    /// only \c RBTree can create and destroy \c RBNode
    friend class RBTree<T>;
    typedef boost::shared_ptr<T> NodeDataPtr;

    /// \name Destructor
    /// \note it's seems a little strange that constructor is private
    /// but deconstructor left public, the reason is for some smart pointer
    /// like std::auto_ptr, they needs to delete RBNode in sometimes, but
    /// \code delete *pointer_to_node \endcode shouldn't be called directly
    //@{
    ~RBNode();
    //@}

    /// \name Test functions
    //@{
    /// \brief return the name of current node, it's relative to its top node
    ///
    /// To get the absolute name of one node, the node path from the top node
    /// to current node has to be recorded
    const isc::dns::Name& getName() const { return (name_); }

    /// \brief return the data store in this node
    /// \note, since the data is managed by RBNode, developer should not
    /// free the pointer
    NodeDataPtr& getData() { return (data_); }
    /// \brief return the data stored in this node, read-only version
    const NodeDataPtr& getData() const { return (data_); }

    /// \brief return whether the node has related data
    /// \note it's meaningless has empty \c RBNode in one RBTree, the only
    /// exception is for non-terminal node which has sub domain nodes who
    /// has data(rrset)
    bool isEmpty() const { return (data_.get() == NULL); }
    //@}

    /// \name Modify functions
    //@{
    /// \breif set the data stored in the node
    void setData(const NodeDataPtr& data) { data_ = data; }
    //@}

    /// \name Callback related methods
    ///
    /// See the description of \c RBTree<T>::find() about callbacks.
    ///
    /// These methods never throw an exception.
    //@{
    /// Return if callback is enabled at the node.
    ///
    /// This method never throws an exception.
    bool isCallbackEnabled() const { return (callback_required_); }

    /// Enable callback at the node.
    void enableCallback() { callback_required_ = true; }

    /// Disable callback at the node.
    void disableCallback() { callback_required_ = false; }
    //@}


private:
    /// \brief Define rbnode color
    enum RBNodeColor {BLACK, RED};

    /// \name Constructors
    /// \note \c Single RBNode is meaningless without living inside one \c RBTree
    /// the creation and destroy of one \c RBNode is handle by host \c RBTree, so
    /// the constructors and destructor of \c RBNode is left private
    //@{
    /// \brief Default constructor.
    ///
    /// This constructor is provided specifically for generating a special
    /// "null" node, and is intended be used only internally.
    RBNode();

    /// \brief Constructor from the node name.
    ///
    /// \param name The domain name corresponding to the node.
    RBNode(const isc::dns::Name& name);
    //@}

    /// This is a factory class method of a special singleton null node.
    static RBNode<T>* NULL_NODE() {
        static RBNode<T> null_node;
        return (&null_node);
    }

    /// data to maintain the rbtree balance
    RBNode<T>*  parent_;
    RBNode<T>*  left_;
    RBNode<T>*  right_;
    RBNodeColor color_;

    isc::dns::Name     name_;
    NodeDataPtr       data_;

    /// the down pointer points to the root node of sub domains of current
    /// domain
    /// \par Adding down pointer to \c RBNode is for two purpose:
    /// \li Accelerate the search process, with sub domain tree, it split the
    /// big flat tree into several hierarchy trees
    /// \li It save memory useage, so same label won't be saved several times
    RBNode<T>*  down_;

    // If true, callback should be called at this node in search.
    // (This may have to become part of more general "attribute flags")
    bool callback_required_;
};


// typically each node should has a name associate with it
// this construction is only used to create \c NULLNODE
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

// note: the following class description is documented using C-style comments
// because the verbatim diagram contain a backslash, which could be interpreted
// as part of a multi-line comment with C++ style comments.
/**
 *  \brief \c RBTree class represents all the domains with the same suffix,
 *  so it can be used to store the domains in one zone.
 * 
 *  \c RBTree is a generic red black tree, and contains all the nodes with
 *  the same suffix, since each name may have sub domain names
 *  so \c RBTree is a recursive data structure namely tree in tree.
 *  So for one zone, several RBTrees may be involved. But from outside, the sub
 *  tree is opaque for end users.
 * 
 *  \c RBTree split the domain space into hierarchy red black trees, nodes in one
 *  tree has the same base name. The benefit of this struct is that:
 *  - enhance the query performace compared with one big flat red black tree
 *  - decrase the memory footprint to save common labels only once.
 * 
 *  \verbatim
  with the following names:
      a       x.d.e.f     o.w.y.d.e.f
      b       z.d.e.f     p.w.y.d.e.f
      c       g.h         q.w.y.d.e.f
      the tree will looks like:
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
 *  \endverbatim
 *  \note open problems:
 *  - current find funciton only return non-empty nodes, so there is no difference
 *    between find one not exist name with empty non-terminal nodes, but in DNS query
 *    logic, they are different
 *  \todo
 *  - add remove interface
 *  - add iterator to iterate the whole rbtree while may needed by axfr
 *  - since \c RBNode only has down pointer without up pointer, the node path during finding
 *    should be recorded for later use
 */
template <typename T>
class RBTree : public boost::noncopyable {
    friend class RBNode<T>;
public:
    /// \brief The return value for the \c find() insert() and erase() method
    enum Result {
        SUCCEED, //insert or erase succeed
        EXACTMATCH, //find the target name
        PARTIALMATCH, //find part of target name
        NOTFOUND,  // for find function means no related name found
                   // for erase function means erase not exist name
        ALREADYEXIST, //for insert operation, the name to insert already exist
    };

    /// \name Constructor and Destructor
    //@{
    explicit RBTree();

    /// \b Note: RBTree is not intended to be inherited so the destructor
    /// is not virtual
    ~RBTree();
    //@}

    /// \name Inquery methods
    //@{
    /// \brief Find the node that gives a longest match against the given name
    ///
    /// This method searches the \c RBTree for a node whose name is a longest
    /// match against \c name.  The found node, if any, is returned via the
    /// \c node pointer.
    /// By default, nodes that don't have data will be ignored, and the result
    /// can be \c NOTFOUND even if there is a node whose name matches the
    /// given \c name.
    /// We'll soon introduce a "no data OK" mode in this method.  It would
    /// match any node of the tree regardless of whether the node has data
    /// or not.
    /// Since the tree is "compressed", i.e., a node can contain multiple
    /// name labels, there are counter intuitive cases in the "no data OK"
    /// mode.  For example, see the diagram of the class description.
    /// Name "y.d.e.f" is logically contained in the tree as part of the
    /// "compressed" node of "w.y".  But the search logic of this method
    /// cannot find the logical match, and would return a \c PARTIALMATCH
    /// result pointing to node "d.e.f".  To correctly identify the real
    /// longest match, "y.d.e.f" with empty data, the caller needs to
    /// perform additional steps.
    ///
    /// This version of \c find() method is templated to allow the caller
    /// to specify a "hook" at nodes that give a partial match.
    /// When the search encounters a node with data that partially matches
    /// \c name (i.e. node's name is a superdomain of \c name) and has
    /// enabled callback (via the \c RBNode::enableCallback() method), if
    /// \c callback is non \c NULL then the callback function is called
    /// with the argument of a reference to the node and the given
    /// callback argument (\c callback_arg).  The template parameter specifies
    /// the type of the callback argument.
    /// The callback function returns either \c true or \c false, meaning
    /// the search should stop or continue, respectively.
    /// If the return value is \c true the search stops immediately at the
    /// node even if there could be a longer matching name below it.
    /// In reality, this convoluted callback rule is specifically intended
    /// to be used to handle a zone cut (delegation) at a name search inside
    /// a zone, and won't be used in any other cases.
    /// Other applications of the tree won't need callbacks, and they should
    /// use the non templated version of the \c find() method.
    ///
    /// Since the expected usage of callback is very limited, we do not
    /// generalize the interface so that it can be an arbitrary functions or
    /// functor objects in favor of simplicity and efficiency.
    ///
    /// This method involves operations on names that can throw an exception.
    /// If that happens the exception will be propagated to the caller.
    /// The callback function should generally not throw an exception, but
    /// if it throws, the exception will be propagated to the caller.
    ///
    /// \param name Target to be found
    /// \param node On success (either \c EXAMPLE or \c PARTIALMATCH) it will
    /// store a pointer to the matching node
    /// \param callback If non \c NULL, a call back function to be called
    /// at "delegation" nodes (see above).
    /// \param callback_arg A caller supplied argument to be passed to
    /// \c callback.
    ///
    /// \return \c EXACTMATCH A node that whose name is equal to \c name is
    /// found.  \c *node will be set to point to that node.
    /// \return \c PARTIALMATCH There is a no exact match, but a superdomain
    /// of \c name exists.  \c node will be set to point to the node whose
    /// name is the longest among such superdomains.
    /// \return \c NOTFOUND There is no exact or partial match against \c name
    /// \c *node will be intact in this case.
    template <typename CBARG>
    Result find(const isc::dns::Name& name, RBNode<T>** node,
                bool (*callback)(const RBNode<T>&, CBARG),
                CBARG callback_arg) const;

    /// Same as the other version, but the returned \c node will be immutable.
    template <typename CBARG>
    Result find(const isc::dns::Name& name, const RBNode<T>** node,
                bool (*callback)(const RBNode<T>&, CBARG),
                CBARG callback_arg) const;

    /// Same as the templated version, but does not use callback.
    ///
    /// Applications except the zone implementation should generally use the
    /// non templated version.
    Result find(const isc::dns::Name& name, RBNode<T>** node) const {
        return (find<void*>(name, node, NULL, NULL));
    }

    /// Same as the templated version, but does not use callback, and the
    /// returned \c node will be immutable.
    ///
    /// In general, this version should be preferred over the other non
    /// templated version, unless the caller knows it should modify the
    /// returned node.
    Result find(const isc::dns::Name& name, const RBNode<T>** node) const {
        return (find<void*>(name, node, NULL, NULL));
    }

    /// \brief Get the total node count in the tree
    /// the node count including the node created common suffix node,
    /// this function will only be used for debuging
    int getNodeCount() const { return (node_count_);}
    //@}

    /// \name Debug function
    //@{
    /// \brief print the nodes in the trees
    void dumpTree(std::ostream& os, unsigned int depth = 0) const;
    //@}

    /// \name Modify function
    //@{
    /// \brief Insert the domain name into the tree
    /// \param name The name to be inserted into the tree
    /// \param inserted_node If no node with the name in the tree,
    /// new \c RBNode will be created, otherwise nothing will be done.
    /// Anyway the pointer point to the node with the name will be assigned to
    /// inserted_node
    /// \return
    //  - SUCCEED means no node exists in the tree with the name before insert
    /// - ALREADYEXIST means already has the node with the given name
    //
    /// \node To modify the data related with one name but not sure the name has
    /// inserted or not, it is better to call \c insert,instead of
    /// \c find(), in case the name isn't exist and needs to insert again
    Result insert(const isc::dns::Name& name, RBNode<T>** inserted_node);
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
    /// \param name is the target, up will points to the base domain of
    /// the tree which name resides, node will point to the target node
    /// if we has exact same name or partical name in current tree.
    /// so for example, in zone a, we has
    /// b.a, c.b.a and d.b.a search c.b.a, up will points to b.a.
    /// and node will points to c.b.a
    /// \note parameter up now is not used by any funciton, but we are gonna
    /// need it soon to implement function like remove
    template <typename CBARG>
    Result findHelper(const isc::dns::Name& name, const RBNode<T>** up,
                      RBNode<T>** node,
                      bool (*callback)(const RBNode<T>&, CBARG),
                      CBARG callback_arg) const;
    void dumpTreeHelper(std::ostream& os, const RBNode<T>* node,
                        unsigned int depth) const;
    /// for indent purpose, add certian mount empty charachter to output stream
    /// according to the depth. This is a helper function which is only used when
    /// dump tree
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
            return (ALREADYEXIST);
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
    return (SUCCEED);
}

template <typename T>
void
RBTree<T>::nodeFission(RBNode<T>& node, const isc::dns::Name& base_name) {
    using namespace helper;
    const isc::dns::Name sub_name = node.name_ - base_name;
    // using auto_ptr here is to avoid memory leak in case of exceptoin raised
    // after the RBNode creation
    std::auto_ptr<RBNode<T> > down_node(new RBNode<T>(sub_name));
    std::swap(node.data_, down_node->data_);
    std::swap(node.callback_required_, down_node->callback_required_);
    down_node->down_ = node.down_;
    node.name_ = base_name;
    node.down_ = down_node.get();
    //root node of sub tree, the initial color is BLACK
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
