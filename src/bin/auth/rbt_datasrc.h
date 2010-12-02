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

#include <dns/name.h>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/pool/object_pool.hpp>
#include <exception>
#include <iostream>
#include <iterator>
#include <stack>

namespace isc {
namespace datasrc {

namespace helper{
/// helper function to remove the base domain from super domain
/// the precondition of this function is the super_name contains the
/// sub_name
isc::dns::Name
operator-(const isc::dns::Name& super_name, const isc::dns::Name& sub_name) {
    return (super_name.split(0, super_name.getLabelCount() -
                             sub_name.getLabelCount()));
}

/// for indent purpose, add certian mount empty charachter to output stream
/// according to the depth,
void
indent(std::ostream& os, unsigned int depth) {
    static const unsigned int INDENT_FOR_EACH_DEPTH = 5;
    os << std::string(depth * INDENT_FOR_EACH_DEPTH, ' ');
}

}

/// \brief Define rbtree color
enum RBTreeColor {BLACK, RED};
template <typename T>
class RBTree;
/// \brief \c RBNode class represents one domain name in the domain space

/// It has two roles, the first one is as one node in the \c RBTree,
/// the second one is to store the data related to DNS. As for the first role,
/// it has left, right, parent and color members
/// which is used to keep the balance of the \c RBTree. As for the second role,
//  it stores the RRsets that belong to the domain name and a rbtree which
/// includes all the subdomains of this node.
/// The name stored in the node is relative related to its parent node.
/// One special kind of node is non-terminal node
/// which has subdomains with RRset but itself doesn't have any RRsets. and typically
/// this kind of node is shadow to end user
///
/// \note: \c RBNode should be created or destroyed only by \c RBTree so
/// constructor and destructor function aren't exposed. The memory management of each
/// node will be handled by a pool, so the node deconstruction will do nothing
template <typename T>
class RBNode : public boost::noncopyable {
public:
    /// only \c RBTree can create and destroy \c RBNode
    friend class RBTree<T>;
    friend class RBTree<T>::Iterator;
    /// \name Test functions
    //@{
    /// \brief return the name of current node, it's relative to its parents
    //
    /// \todo Is it meaningful to return the absolute of the node?
    const isc::dns::Name& getName() const { return (name_); }

    /// \brief return the data store in this node
    T& getData() { return (data_); }

    /// \brief return the next node which is bigger than current node
    /// in the same tree
    RBNode<T>* successor()const;
    //@}

    /// \name Modify functions
    /// \brief set the data stored in the node
    void setData(const T& data) { data_ = data; }

private:
    /// \name Constructors and destructor
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

    /// \brief copy the the data saved in the node into another node
    /// the data copied exclude the rbtree related data like left,right,parent 
    /// and color
    void copyContent(RBNode<T>& node);

    /// data to maintain the rbtree balance
    RBNode<T>*  parent_;
    RBNode<T>*  left_;
    RBNode<T>*  right_;
    RBTreeColor color_;


    isc::dns::Name     name_;
    /// this will make type T should have default constructor
    /// without any parameters
    T           data_;
    /// the down pointer points to the root node of sub domains of current 
    /// domain 
    /// \par Adding down pointer to \c RBNode is for two purpose:
    /// \li Accelerate the search process, with sub domain tree, it split the
    /// big flat tree into several hierarchy trees
    /// \li It save memory useage, so same label won't be saved several times 
    RBNode<T>*  down_;

    ///the node won't be returned to end user, if the node is shadow.
    ///shadow node is created by rbtree for inner use, it's opaque to
    ///end user. 
    /// \par shadow node is the node with sub domain tree, but itself don't
    /// contain any data, so the \c down_ pointer of a shadow node cannot be NULL
    bool        is_shadow_;
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
    down_(NULL),
    is_shadow_(false)
{
}

template <typename T>
RBNode<T>::RBNode(const isc::dns::Name& name) :
    parent_(NULL_NODE()),
    left_(NULL_NODE()),
    right_(NULL_NODE()),
    color_(RED),
    name_(name),
    down_(NULL),
    is_shadow_(false)
{
}


template <typename T>
RBNode<T>*
RBNode<T>::successor()const {
    RBNode<T>* current = const_cast<RBNode<T>*>(this);
    // If it has right node, the successor is the left-most node of the right
    // subtree.
    if (right_ != NULL_NODE()) {
        current = right_;
        while (current->left_ != NULL_NODE()) {
            current = current->left_;
        }
        return (current);
    }

    // Otherwise go up until we find the first left branch on our path to
    // root.  If found, the parent of the branch is the successor.
    // Otherwise, we return the null node.
    RBNode<T>* parent = current->parent_;
    while (parent != NULL_NODE() && current == parent->right_) {
        current = parent;
        parent = parent->parent_;
    }
    return (parent);
}

template <typename T>
void
RBNode<T>::copyContent(RBNode<T>& node) {
    node.name_ = name_;
    node.data_ = data_;
    node.down_ = down_;
    node.is_shadow_ = is_shadow_;
}


/// \brief \c RBTree class represents all the domains with the same suffix,
/// so it can be used to store the domains in one zone.
///
/// \c RBTree is a generic red black tree, and contains all the nodes with
/// the same suffix, since each
/// name may have sub domain names so \c RBTree is a recursive data structure
/// or tree in tree.
/// So for one zone, several RBTrees may be involved. But from outside, the sub
/// tree is opaque for end users.
template <typename T>
class RBTree : public boost::noncopyable {
    friend class RBNode<T>;
public:
    /// the max count of labels in a name
    enum {MAX_PATH_LEN_TO_ROOT = 254};
    /// \brief The return value for the \c find() insert() and erase() method
    enum Result {
        SUCCEED, //insert or erase succeed
        EXACTMATCH, //find the target name
        PARTIALMATCH, //find part of target name
        NOTFOUND,  // for find function means no related name found
                   // for erase function means erase not exist name
        ALREADYEXIST, //for insert operation, the name to insert already exist
        NOMEM //no memory to create new node
    };

    /// \name Constructor and Destructor
    //@{
    RBTree();

    /// \b Note: RBTree is not intended to be inherited so the destructor
    /// is not virtual
    ~RBTree();
    //@}

    /// \name Inquery methods
    //@{
    /// \brief Find the node with the name
    /// \param name Target to be found
    /// \param node Point to the node when the return vaule is \c not
    /// NOTFOUND, if the return value is NOTFOUND, the value of node is
    /// \c unknown
    Result find(const isc::dns::Name& name, RBNode<T>** node) const;
    Result find(const isc::dns::Name& name, const RBNode<T>** node) const;

    /// \brief Get the total node count in the tree
    /// the node count including the node created common suffix node,
    /// this function will only be used for debuging
    int getNodeCount() const { return (node_count_);}


    /// \brief Get the total names has been inserted into the tree
    int getNameCount() const { return (name_count_);}
    //@}

    /// \name Debug function
    //@{
    /// \brief print the nodes in the trees
    /// \todo is it better to return one string instead of print to the stdout?
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
    /// \return return SUCCEED means no node exists in the tree with the name before
    /// insert; return ALREADYEXIST means already has the node with the given name
    /// return NOMEM means no memory left to allocate new node
    //
    /// To add an RRset into one node when it's not known whether the node
    /// already exists, it is better to call \c insert and then call the
    /// RBNode interface instead of calling \c find().
    Result insert(const isc::dns::Name& name, RBNode<T>** inserted_node);

    /// \brief Erase the node with the domain name
    /// \return NOTEXSIT means no node with given name
    /// otherwise return SUCCEED
    Result erase(const isc::dns::Name& name);
    //@}



    /// \brief iterator of domain tree, mainly used to walk throught the whole tree
    /// in ascending order according to domain name
    /// \todo make find and insert in domain tree return iterator not rbnode pointer,
    /// \note the iterator should know the node it points to and the tree the node 
    /// belongs to, since the tree can only search from up to down, the up nodes 
    /// has travelled has to be stored, the iterator has similar functionality as 
    /// dns_rbtnodechain in bind9. Keep the constuction and deconstruction private is
    /// becuase there is no default iterator.
    class Iterator : public std::iterator<std::input_iterator_tag, RBNode<T> >
    {
        friend class RBTree<T>;
        public:
            /// copy and assign constructor 
            /// \name
            //@{
            Iterator(const Iterator& itr);
            Iterator& operator=(const Iterator& itr);
            //@}

            const RBNode<T>& operator*() const { return (*node_);}
            RBNode<T>& operator*()             { return (*node_);}

            const RBNode<T>* operator->() const { return (node_);}
            RBNode<T>* operator->() { return (node_);}

            Iterator& operator++() { node_ = nextVisibleSuccessor(node_); return (*this);}
            Iterator  operator++(int) { Iterator old = *this; node_ = nextVisibleSuccessor(node_); return (old);}

            bool operator==(const Iterator &itr) const { return (itr.node_ == node_);}
            bool operator!=(const Iterator &itr) const { return !(*this == itr); }

        private:
            /// constructor
            Iterator(RBNode<T> *node, RBTree<T> *tree, RBNode<T> **nodes_to_root_path = NULL, int path_len = 0);
            /// the difference between \c successor and \c nextVisibleSuccessor is that, \c nextVisibleSuccessor will
            /// travel in the whole tree including the down trees, and also it will return non-shadow node
            RBNode<T> *nextVisibleSuccessor(RBNode<T> *node);

            RBNode<T>* node_;
            RBTree<T>* tree_;
            RBNode<T>* up_node_path_[RBTree<T>::MAX_PATH_LEN_TO_ROOT];
            int path_len_;
    };

    friend class Iterator;
    /// \name iterator related functions
    //@{
    /// \brief begin point to the smallest visible node in the tree
    Iterator begin() const;
    const Iterator begin();

    Iterator end()  const{ return (Iterator(NULLNODE, const_cast<RBTree<T>*>(this)));}
    const Iterator end() { return (Iterator(NULLNODE, this));}
    //@}

private:
    /// \name RBTree balance functions
    //@{
    void deleteRebalance(RBNode<T>** root, RBNode<T>* node);
    void insertRebalance(RBNode<T>** root, RBNode<T>* node);
    RBNode<T>* rightRotate(RBNode<T>** root, RBNode<T>* node);
    RBNode<T>* leftRotate(RBNode<T>** root, RBNode<T>* node);
    //@}

    /// \name Helper functions
    //@{
    /// Each public function has related recursive helper function
    void eraseNode(RBNode<T>** root, RBNode<T>* node);
    Result findHelper(const isc::dns::Name& name, RBNode<T>** up,
                      RBNode<T>** node) const;
    void dumpTreeHelper(std::ostream& os, const RBNode<T>* node,
                        unsigned int depth) const;

    /// get one node from the node pool, if no memory left return NULL
    /// without throw exception
    RBNode<T>* createNode();
    RBNode<T>* createNode(const isc::dns::Name& name);
    /// return the node to node pool
    void  freeNode(RBNode<T>* node);


    /// Split one node into two nodes, keep the old node and create one new
    /// node, old node will hold the base name, new node will be the down node
    /// of old node, new node will hold the sub_name, the data
    /// of old node will be move into new node, and old node became shadow
    /// \return NOMEM: means no memory to create new node
    /// otherwise return SUCCEED
    Result nodeFission(RBNode<T>& node, const isc::dns::Name& sub_name);

    /// Merge node with its down node, down node will be deleted and the data of
    /// down node will move to up node.
    /// \note the precondition of this function is that, the down tree of node
    /// has only one node and current node is shadow
    void nodeFussion(RBNode<T>& node);

    /// return the node with smallest name, according to DNS domain name order
    /// normally it's the most left node
    RBNode<T>* smallestNodeInTree(const RBNode<T>* root) const;
    //@}

    RBNode<T>*  root_;
    RBNode<T>*  NULLNODE;
    /// the node count of current tree 
    unsigned int node_count_;
    /// the count of real name user inserted into the domain tree
    unsigned int name_count_;
    /// use mem pool to manage rbnode to accelerate node creation and destruction
    boost::object_pool<RBNode<T> > node_pool_;
};

/*
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
*/
template <typename T>
RBTree<T>::RBTree() {
    NULLNODE = RBNode<T>::NULL_NODE();
    root_ = NULLNODE;
    node_count_ = 0;
    name_count_ = 0;
}

template <typename T>
RBTree<T>::~RBTree() {
    assert(root_ != NULL);
}

template <typename T>
RBNode<T>*
RBTree<T>::createNode() {
    RBNode<T>* raw_mem = node_pool_.malloc();
    if (raw_mem) {
        return (new(raw_mem)RBNode<T>());
    } else {
        return (NULL);
    }
}

template <typename T>
RBNode<T>*
RBTree<T>::createNode(const isc::dns::Name& name) {
    RBNode<T>* raw_mem = node_pool_.malloc();
    if (raw_mem) {
        return (new(raw_mem)RBNode<T>(name));
    } else {
        return (NULL);
    }
}

template <typename T>
void
RBTree<T>::freeNode(RBNode<T>* node) {
    // NULLNODE isn't alloc in heap
    assert(node != NULLNODE);
    node_pool_.destroy(node);
}


template <typename T>
typename RBTree<T>::Result
RBTree<T>::find(const isc::dns::Name& name, RBNode<T>** node) const {
    RBNode<T>* up_node = NULL;
    return (findHelper(name, &up_node, node));
}

template <typename T>
typename RBTree<T>::Result
RBTree<T>::find(const isc::dns::Name& name, const RBNode<T>** node) const {
    RBNode<T>* up_node;
    RBNode<T>* target_node;
    const typename RBTree<T>::Result ret =
        findHelper(name, &up_node, &target_node);
    if (ret != NOTFOUND) {
        *node = target_node;
    }
    return (ret);
}

template <typename T>
typename RBTree<T>::Result
RBTree<T>::findHelper(const isc::dns::Name& target_name, RBNode<T>** up_node,
                      RBNode<T>** target) const
{
    using namespace helper;

    RBNode<T>* node = root_;
    typename RBTree<T>::Result ret = NOTFOUND;
    *up_node = NULL;
    isc::dns::Name name = target_name;

    while (node != NULLNODE) {
        const isc::dns::NameComparisonResult compare_result =
            name.compare(node->name_);
        const isc::dns::NameComparisonResult::NameRelation relation =
            compare_result.getRelation();
        if (relation == isc::dns::NameComparisonResult::EQUAL) {
            if (!node->is_shadow_) {
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
                *up_node = node;
                name = name - node->name_;
                if (node->is_shadow_) {
                    assert(node->down_ != NULL);
                    node = node->down_;
                } else {
                    ret = RBTree<T>::PARTIALMATCH;
                    *target = node;
                    if (node->down_ != NULL)
                        node = node->down_;
                    else
                        break;
                }
            } else {
                break;
            }
        }
    }

    return (ret);
}

template <typename T>
typename RBTree<T>::Iterator
RBTree<T>::begin() const {
    Iterator beg(smallestNodeInTree(root_), const_cast<RBTree<T>*>(this));
    if (beg->is_shadow_) {
        ++beg;
    }
    return (beg);
}

template <typename T>
const typename RBTree<T>::Iterator
RBTree<T>::begin() {
    Iterator beg(smallestNodeInTree(root_), this);
    if (beg->is_shadow_) {
        ++beg;
    }
    return (beg);
}

template <typename T>
RBNode<T> *
RBTree<T>::smallestNodeInTree(const RBNode<T>* root) const {
    const RBNode<T>* left_most = root;
    while (left_most->left_ != NULLNODE) {
        left_most = left_most->left_;
    }
    return (const_cast<RBNode<T>*>(left_most));
}

template <typename T>
typename RBTree<T>::Result
RBTree<T>::insert(const isc::dns::Name& target_name, RBNode<T>** new_node) {
    using namespace helper;
    RBNode<T>* parent = NULLNODE;
    RBNode<T>* current = root_;
    RBNode<T>* up_node = NULL;
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
            // if the node is a common suffix not user inserted, return succeed
            // otherwise return already exist
            if (current->is_shadow_) {
                current->is_shadow_ = false;
                ++name_count_;
                return (SUCCEED);
            } else {
                return (ALREADYEXIST);
            }
        } else {
            const int common_label_count = compare_result.getCommonLabels();
            if (common_label_count == 1) {
                parent = current;
                order = compare_result.getOrder();
                current = order < 0 ? current->left_ : current->right_;
            } else {
                // insert sub domain to sub tree
                if (relation == isc::dns::NameComparisonResult::SUBDOMAIN) {
                    if (current->down_ == NULL) {
                        RBNode<T>* node = createNode(name - current->name_);
                        //root node of sub tree, the initial color is BLACK
                        node->color_ = BLACK;
                        if (node == NULL) {
                            return (NOMEM);
                        }
                        current->down_ = node;
                        if (new_node != NULL) {
                            *new_node = node;
                        }
                        ++node_count_;
                        ++name_count_;
                        return (SUCCEED);
                    } else {
                        up_node = current;
                        name = name - current->name_;
                        current = current->down_;
                    }
                } else {
                    // The number of labels in common is fewer
                    // than the number of labels at the current
                    // node, so the current node must be adjusted
                    // to have just the common suffix, and a down
                    // pointer made to a new tree.
                    const isc::dns::Name common_ancestor = name.split(
                        name.getLabelCount() - common_label_count,
                        common_label_count);
                    if (nodeFission(*current, common_ancestor) == NOMEM) {
                        return (NOMEM);
                    }
                }
            }
        }
    }

    RBNode<T>** current_root = up_node ? &(up_node->down_) : &root_;
    RBNode<T>* node = createNode(name);
    if (node == NULL) {
        return (NOMEM);
    }

    node->parent_ = parent;
    if (parent == NULLNODE) {
        *current_root = node;
    } else if (order < 0) {
        parent->left_ = node;
    } else {
        parent->right_ = node;
    }
    insertRebalance(current_root, node);
    if (new_node != NULL) {
        *new_node = node;
    }

    ++node_count_;
    ++name_count_;
    return (SUCCEED);
}


template <typename T>
typename RBTree<T>::Result
RBTree<T>::nodeFission(RBNode<T>& node, const isc::dns::Name& base_name) {
    using namespace helper;
    const isc::dns::Name sub_name = node.name_ - base_name;
    RBNode<T>* down_node = createNode(node.name_ - base_name);
    if (down_node == NULL) {
        return (NOMEM);
    }

    node.copyContent(*down_node);
    node.name_ = base_name;
    node.down_ = down_node;
    node.is_shadow_ = true;
    down_node->name_ = sub_name;
    //root node of sub tree, the initial color is BLACK
    down_node->color_ = BLACK;
    ++node_count_;
    return (SUCCEED);
}

template <typename T>
void
RBTree<T>::insertRebalance(RBNode<T>** root, RBNode<T>* node) {

    RBNode<T>* uncle;
    while (node != *root && node->parent_->color_ == RED) {
        if (node->parent_ == node->parent_->parent_->left_) {
            uncle = node->parent_->parent_->right_;

            if (uncle->color_ == RED) {
                node->parent_->color_ = BLACK;
                uncle->color_ = BLACK;
                node->parent_->parent_->color_ = RED;
                node = node->parent_->parent_;
            } else {
                if (node == node->parent_->right_) {
                    node = node->parent_;
                    leftRotate(root, node);
                }
                node->parent_->color_ = BLACK;
                node->parent_->parent_->color_ = RED;
                rightRotate(root, node->parent_->parent_);
            }
        } else {
            uncle = node->parent_->parent_->left_;
            if (uncle->color_ == RED) {
                node->parent_->color_ = BLACK;
                uncle->color_ = BLACK;
                node->parent_->parent_->color_ = RED;
                node = node->parent_->parent_;
            } else {
                if (node == node->parent_->left_) {
                    node = node->parent_;
                    rightRotate(root, node);
                }
                node->parent_->color_ = BLACK;
                node->parent_->parent_->color_ = RED;
                leftRotate(root, node->parent_->parent_);
            }
        }
    }

    (*root)->color_ = BLACK;
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
typename RBTree<T>::Result
RBTree<T>::erase(const isc::dns::Name& name) {
    RBNode<T>* node = NULLNODE;
    RBNode<T>* up_node = NULL;
    if (findHelper(name, &up_node, &node) != RBTree<T>::EXACTMATCH) {
        return (NOTFOUND);
    }
    --name_count_;

    // For node with downpointer, set it to shadow.
    // Since there is at least one node below this one, the deletion is
    // complete.  The down node from this node might be all by itself on a
    // single level, so we could collapse the subtree to reduce the levels
    if (node->down_ != NULL) {
        assert(node->is_shadow_ == false);
        node->is_shadow_ = true;
        RBNode<T>* down_node = node->down_;
        if (down_node->left_ == NULLNODE &&
            down_node->right_ == NULLNODE) {
            nodeFussion(*node);
        }
        return (SUCCEED);
    }

    RBNode<T>** root = up_node ? &up_node->down_ : &root_;
    eraseNode(root, node);

    if (up_node != NULL) {
        assert(up_node->down_ != NULL);
        RBNode<T>* down_node = up_node->down_;
        if (down_node == NULLNODE) {
            up_node->down_ = NULL;
        // if there is only one node in the sub tree, and the up node
        // is shadow, merge the root of subtree to the up node
        } else if (up_node->is_shadow_ &&
                down_node->left_ == NULLNODE &&
                down_node->right_ == NULLNODE) {
            nodeFussion(*up_node);
        }
    }
    return (SUCCEED);
}

template <typename T>
void
RBTree<T>::eraseNode(RBNode<T>** root, RBNode<T>* target) {
    RBNode<T>* to_delete = target;

    if (to_delete->left_ != NULLNODE && to_delete->right_ != NULLNODE)
        to_delete = to_delete->successor();

    // fix the parent relationship of the child of to_delete
    RBNode<T>* child = (to_delete->left_ != NULLNODE) ? to_delete->left_ :
        to_delete->right_;
    child->parent_ = to_delete->parent_;

    // fix the child relation of the parent of to delete
    RBNode<T>* parent = to_delete->parent_;
    if (parent == NULLNODE) {
        *root = child;
    } else if (to_delete == parent->left_) {
        parent->left_ = child;
    } else {
        parent->right_ = child;
    }

    if (to_delete != target) {
        to_delete->copyContent(*target);
        to_delete->down_ = NULL;
    }

    if (to_delete->color_ == BLACK) {
        deleteRebalance(root, child);
    }

    to_delete->left_ = NULL;
    to_delete->right_ = NULL;
    to_delete->down_ = NULL;
    freeNode(to_delete);
    --node_count_;
}

template <typename T>
void
RBTree<T>::nodeFussion(RBNode<T>& up_node) {
    RBNode<T>* down_node = up_node.down_;
    assert(down_node);

    const isc::dns::Name merged_name =
    down_node->name_.concatenate(up_node.name_);
    down_node->copyContent(up_node);
    up_node.down_ = NULL;
    up_node.name_ = merged_name;
    up_node.is_shadow_ = false;
    freeNode(down_node);

    --node_count_;
}


template <typename T>
void
RBTree<T>::deleteRebalance(RBNode<T>** root, RBNode<T>* node) {
    RBNode<T>* sibling  = NULLNODE;

    while (node != *root && node->color_ == BLACK) {
        if (node == node->parent_->left_) {
            sibling = node->parent_->right_;

            if (sibling->color_ == RED) {
                sibling->color_ = BLACK;
                node->parent_->color_ = RED;
                leftRotate(root, node->parent_);
                sibling = node->parent_->right_;
            }

            if (sibling->left_->color_ == BLACK && sibling->right_->color_ == BLACK) {
                sibling->color_ = RED;
                node = node->parent_;
            } else {
                if (sibling->right_->color_ == BLACK) {
                    sibling->left_->color_ = BLACK;
                    sibling->color_ = RED;
                    rightRotate(root, sibling);
                    sibling = node->parent_->right_;
                }

                sibling->color_ = node->parent_->color_;
                node->parent_->color_ = BLACK;
                sibling->right_->color_ = BLACK;
                leftRotate(root, node->parent_);
                node = *root;
            }
        } else {
            sibling = node->parent_->left_;
            if (sibling->color_ == RED) {
                sibling->color_ = BLACK;
                node->parent_->color_ = RED;
                rightRotate(root, node->parent_);
                sibling = node->parent_->left_;
            }

            if (sibling->right_->color_ == BLACK && sibling->left_->color_ == BLACK) {
                sibling->color_ = RED;
                node = node->parent_;
            } else {
                if (sibling->left_->color_ == BLACK) {
                    sibling->right_->color_ = BLACK;
                    sibling->color_ = RED;
                    leftRotate(root, sibling);
                    sibling = node->parent_->left_;
                }
                sibling->color_ = node->parent_->color_;
                node->parent_->color_ = BLACK;
                sibling->left_->color_ = BLACK;
                rightRotate(root, node->parent_);
                node = *root;
            }
        }
    }

    node->color_ = BLACK;
}


template <typename T>
void
RBTree<T>::dumpTree(std::ostream& os, unsigned int depth) const {
    helper::indent(os, depth);
    os << "tree has node(s) " << node_count_ << "\n";
    dumpTreeHelper(os, root_, depth);
}

template <typename T>
void
RBTree<T>::dumpTreeHelper(std::ostream& os, const RBNode<T>* node,
                          unsigned int depth) const
{
    helper::indent(os, depth);
    os << node->name_.toText() << " ("
              << ((node->color_ == BLACK) ? "black" : "red") << ")";
    os << ((node->is_shadow_) ? "[invisible] \n" : "\n");
    if (node->down_ != NULL) {
        helper::indent(os, depth + 1);
        os << "begin down from "<< node->name_.toText() << "\n";
        dumpTreeHelper(os, node->down_, depth + 1);
        helper::indent(os, depth + 1);
        os << "end down from " << node->name_.toText() << "\n";
    }

    if (node->left_ != NULLNODE) {
        dumpTreeHelper(os, node->left_, depth + 1);
    } else {
        helper::indent(os, depth + 1);
        os << "NULL\n";
    }

    if (node->right_ != NULLNODE) {
        dumpTreeHelper(os, node->right_, depth + 1);
    } else {
        helper::indent(os, depth + 1);
        os << "NULL\n";
    }
}

template <typename T>
RBTree<T>::Iterator::Iterator(const RBTree<T>::Iterator& itr) {
    node_ = itr.node_;
    tree_ = itr.tree_;
    path_len_ = itr.path_len_;
    if (path_len_ > 0) {
        memcpy(up_node_path_, itr.up_node_path_, path_len_ * sizeof(RBNode<T> *));
    }
}

template <typename T>
typename RBTree<T>::Iterator&
RBTree<T>::Iterator::operator=(const RBTree<T>::Iterator& itr) {
    node_ = itr.node_;
    tree_ = itr.tree_;
    path_len_ = itr.path_len_;
    if (path_len_ > 0) {
        memcpy(up_node_path_, itr.up_node_path_, path_len_ * sizeof(RBNode<T> *));
    }
    return (*this);
}

template <typename T>
RBTree<T>::Iterator::Iterator(RBNode<T>* node, RBTree<T>* tree,
                              RBNode<T>** nodes_to_root_path, int path_len) :
                         node_(node),
                         tree_(tree),
                         path_len_(path_len)
{
    if (path_len > 0) {
        memcpy(up_node_path_, nodes_to_root_path, path_len * sizeof(RBNode<T>*));
    }
}

template <typename T>
RBNode<T>*
RBTree<T>::Iterator::nextVisibleSuccessor(RBNode<T>* node) {
    // If node has down tree, next bigger node should resides in it
    if (node->down_) {
        up_node_path_[path_len_ ++] = node;
        RBNode<T>* smallest_node = tree_->smallestNodeInTree(node->down_);
        if (!smallest_node->is_shadow_) {
            return (smallest_node);
        } else {
            return (nextVisibleSuccessor(smallest_node));
        }
    }
    // otherwise found the visible successor in current level
    // if no successor found move to up level, the next visible successor
    // is the successor of up node in the up level tree
    RBNode<T>* next_visible = node->successor();
    if (next_visible == tree_->NULLNODE) {
        while (path_len_ > 0) {
            RBNode<T>* up_node = up_node_path_[--path_len_];
            RBNode<T>* up_next = up_node->successor();
            if (up_next != tree_->NULLNODE) {
                if (up_next->is_shadow_) {
                    return (nextVisibleSuccessor(up_next));
                } else {
                    return (up_next);
                }
            }
        }
        return (tree_->NULLNODE);
    } else if (next_visible->is_shadow_) {
        return nextVisibleSuccessor(next_visible);
    } else {
        return (next_visible);
    }
}
}
}

#endif  // _RBTREE_H

// Local Variables:
// mode: c++
// End:
