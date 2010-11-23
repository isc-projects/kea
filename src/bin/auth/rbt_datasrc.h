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
#include <dns/rrset.h>
#include <dns/rrsetlist.h>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <exception>
#include <iostream> 

using namespace isc::dns;
namespace isc {
namespace datasrc {

namespace {
/// helper function to remove the base domain from super domain
/// the precondition of this function is the super_name contains the
/// sub_name
Name
operator-(const Name& super_name, const Name& sub_name) {
    return (super_name.split(0, super_name.getLabelCount() -
                             sub_name.getLabelCount()));
}
}

/// \brief Define rbtree color
enum RBTreeColor {BLACK = 1, RED};
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
/// which has subdomains with RRset but itself doesn't have any RRsets.
///
/// \b Note: \c RBNode should be created or destroyed only by \c RBTree so
/// constructor and destructor function aren't exposed.
template <typename T>
class RBNode : public boost::noncopyable {
public:
    /// only \c RBTree can create and destroy \c RBNode
    friend class RBTree<T>;
    /// \name Test functions
    //@{
    /// \brief return the name of current node, it's relative to its parents
    //
    /// \todo Is it meaningful to return the absolute of the node?
    const Name& getName() const { return (name_); }

    /// \breif return the data store in this node
    T& getData() { return (data_); }

    /// \brief return next node whose name is bigger than current node
    const RBNode<T>* successor() const;
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
    RBNode(const Name &name);

    /// the class isn't left to be inherited
    ~RBNode();
    //@}

    /// This is a factory class method of a special singleton null node.
    static RBNode<T>* NULL_NODE() {
        static RBNode<T> null_node;
        return (&null_node);
    }

    /// \brief copy the DNS related data to another node except the sub domain
    /// tree
    void cloneDNSData(RBNode<T>& node);

    /// \brief when copy the DNS data from one node to another, except the
    /// RRsets, name etc,
    /// also needs to maintain the down and up relationship, which includes
    /// set the down point of current node and up point of sub domain tree
    void setDownTree(RBTree<T>* down);

    /// data to maintain the rbtree balance
    RBNode<T>*  parent_;
    RBNode<T>*  left_;
    RBNode<T>*  right_;
    RBTreeColor color_;

    /// data to carry dns info
    Name        name_;
    /// this will make type T should have default constructor 
    /// without any parameters
    T           data_;
    RBTree<T>*  down_;

    ///the node won't be returned to end user, if the node is shadow.
    ///shadow node is created by rbtree for inner use, it's opaque to
    ///end user. 
    bool        is_shadow_; 
};

template <typename T>
RBNode<T>::RBNode() :
    parent_(this),
    left_(this),
    right_(this),
    color_(BLACK),
    name_(Name::ROOT_NAME()),   // dummy name, the value doesn't matter.
    down_(NULL),
    is_shadow_(false) 
{
}

template <typename T>
RBNode<T>::RBNode(const Name& name) :
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
RBNode<T>::~RBNode() {
    delete down_;
}

template <typename T>
const RBNode<T>*
RBNode<T>::successor() const {
    const RBNode<T>* current = this;

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
    const RBNode<T>* s = current->parent_;
    while (s != NULL_NODE() && current == s->right_) {
        current = s;
        s = s->parent_;
    }
    return (s);
}

template <typename T>
void
RBNode<T>::cloneDNSData(RBNode<T>& node) {
    node.name_ = name_;
    node.data_ = data_;
    node.is_shadow_ = is_shadow_;
}

template <typename T>
void
RBNode<T>::setDownTree(RBTree<T>* down) {
    down_ = down;
    if (down != NULL) {
        down->up_ = this;
    }
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
    /// \brief The return value for the \c find() method
    /// - EXACTMATCH: return the node in the tree exactly same with the target
    /// - PARTIALMATCH: return the node which is an ancestor of the target 
    ///   which also is the longest match
    /// - NOTFOUND: other conditions except EXACTMATCH & FINDREFERRAL
    enum FindResult{EXACTMATCH, PARTIALMATCH, NOTFOUND};

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
    FindResult find(const Name& name, RBNode<T>** node) const;
    FindResult find(const Name& name, const RBNode<T>** node) const;

    /// \brief Get the total node count in the tree
    /// the node count including the node created common suffix node
    int getNodeCount() const;


    /// \brief Get the total names inserted into the tree
    int getNameCount() const;
    //@}

    /// \name Debug function
    //@{
    /// \brief print the nodes in the trees
    /// \todo is it better to return one string instead of print to the stdout?
    void printTree(std::ostream& os, int depth = 0) const;
    //@}

    /// \name Modify function
    //@{
    /// \brief Insert the domain name into the tree
    /// \param name The name to be inserted into the tree
    /// \param inserted_node If no node with the name in the tree,
    /// new \c RBNode will be created, otherwise nothing will be done.
    /// Anyway the pointer point to the node with the name will be assigned to
    /// inserted_node
    /// \return return 0 means no node exists in the tree with the name before
    /// insert; return 1 means already has the node with the given name
    /// return -1 means no memory left to allocate new node
    //
    /// To add an RRset into one node when it's not known whether the node
    /// already exists, it is better to call \c insert and then call the
    /// RBNode interface instead of calling \c find().
    int insert(const Name& name, RBNode<T>** inserted_node);

    /// \brief Erase the node with the domain name
    /// \return If no node with the name, return 1; otherwise return 0
    int erase(const Name& name);
    //@}

private:
    /// \name RBTree balance functions
    //@{
    void deleteRebalance(RBNode<T>* node);
    void insertRebalance(RBNode<T>* node);
    RBNode<T>* rightRotate(RBNode<T>* p);
    RBNode<T>* leftRotate(RBNode<T>* p);
    //@}

    /// \name Helper functions
    //@{
    /// Each public function has related recursive helper function
    void eraseNode(RBNode<T>* node);
    FindResult findHelper(const Name& name, const RBTree<T>** tree,
                          RBNode<T>** node) const;
    int getNodeCountHelper(const RBNode<T>* node) const;
    int getNameCountHelper(const RBNode<T>* node) const;
    void printTreeHelper(std::ostream &os, const RBNode<T>* node, int depth) const;
    //@}

    RBNode<T>*  root_;
    RBNode<T>*  NULLNODE;
    RBNode<T>*  up_;
    /// the node count of current tree except the sub domain trees
    unsigned int node_count_;
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
    up_ = NULL;
}

template <typename T>
RBTree<T>::~RBTree() {
    assert(root_ != NULL);

    if (NULLNODE == root_) {
        return;
    }

    RBNode<T>* node = root_;
    while (root_->left_ != NULLNODE || root_->right_ != NULLNODE) {
        while (node->left_ != NULLNODE || node->right_ != NULLNODE) {
            node = (node->left_ != NULLNODE) ? node->left_ : node->right_;
        }

        RBNode<T>* parent = node->parent_;
        if (parent->left_ == node) {
            parent->left_ = NULLNODE;
        } else {
            parent->right_ = NULLNODE;
        }
        delete node;
        node = parent;
    }

    delete root_;
    root_ = NULL;
}


template <typename T>
typename RBTree<T>::FindResult
RBTree<T>::find(const Name& name, RBNode<T>** node) const {
    const RBTree<T> *tree;
    return (findHelper(name, &tree, node));
}

template <typename T>
typename RBTree<T>::FindResult
RBTree<T>::find(const Name& name, const RBNode<T>** node) const {
    const RBTree<T> *tree;
    RBNode<T> *target_node; 
    const typename RBTree<T>::FindResult ret =
        findHelper(name, &tree, &target_node);
    if (ret != NOTFOUND) {
        *node = target_node;
    }
    return (ret);
}

template <typename T>
typename RBTree<T>::FindResult
RBTree<T>::findHelper(const Name& name, const RBTree<T>** tree,
                      RBNode<T>** ret) const 
{
    RBNode<T>* node = root_;
    while (node != NULLNODE) {
        const NameComparisonResult compare_result = name.compare(node->name_);
        const NameComparisonResult::NameRelation relation =
            compare_result.getRelation();
        if (relation == NameComparisonResult::EQUAL) {
            if (node->is_shadow_) {
                return (RBTree<T>::NOTFOUND);
            } else {
                *tree = this;
                *ret = node;
                return (RBTree<T>::EXACTMATCH);
            }
        } else {
            const int common_label_count = compare_result.getCommonLabels();
            // common label count equal one means, there is no common between
            // two names
            if (common_label_count == 1) {
                node = (compare_result.getOrder() < 0) ?
                    node->left_ : node->right_;
            } else if (NameComparisonResult::SUBDOMAIN == relation) {
                if (node->is_shadow_) {
                    assert(node->down_ != NULL);
                    return (node->down_->findHelper(name - node->name_, tree,
                                                    ret));
                } else {
                    typename RBTree<T>::FindResult result =
                        RBTree<T>::NOTFOUND;
                    if (node->down_ != NULL) {
                        result = node->down_->findHelper(name - node->name_,
                                                         tree, ret);
                    }
                    // if not found in sub domain tree, so current node is the
                    // longest match
                    // otherwise return the result in sub domin tree
                    if (RBTree<T>::NOTFOUND == result) {
                        *tree = this;
                        *ret = node;
                        return (RBTree<T>::PARTIALMATCH);
                    } else {
                        return (result);
                    }
                }
            } else {
                return (RBTree<T>::NOTFOUND);
            }
        }
    }

    return (RBTree<T>::NOTFOUND);
}

template <typename T>
int
RBTree<T>::getNodeCount() const {
    return (getNodeCountHelper(root_));
}

template <typename T>
int
RBTree<T>::getNodeCountHelper(const RBNode<T> *node) const {
    if (NULLNODE == node) {
        return (0);
    }

    const int sub_tree_node_count =
        node->down_ ? node->down_->getNodeCount() : 0;
    return (1 + sub_tree_node_count + getNodeCountHelper(node->left_) +
            getNodeCountHelper(node->right_));
}

template <typename T>
int
RBTree<T>::getNameCount() const {
    return (getNameCountHelper(root_));
}

template <typename T>
int
RBTree<T>::getNameCountHelper(const RBNode<T> *node) const {
    if (NULLNODE == node) {
        return (0);
    }

    const int sub_tree_name_count =
        node->down_ ? node->down_->getNameCount() : 0;
    return ((node->is_shadow_ ? 0 : 1) + sub_tree_name_count +
            getNameCountHelper(node->left_) +
            getNameCountHelper(node->right_));
}

template <typename T>
int
RBTree<T>::insert(const Name& name, RBNode<T>** new_node) {
    RBNode<T>* parent = NULLNODE;
    RBNode<T>* current = root_;

    int order = -1;
    while (current != NULLNODE) {
        parent = current;

        const NameComparisonResult compare_result =
            name.compare(current->name_);
        const NameComparisonResult::NameRelation relation =
            compare_result.getRelation();
        if (relation == NameComparisonResult::EQUAL) {
            if (new_node != NULL) {
                *new_node = current;
            }
            // if the node is a common suffix not user inserted, return 0
            // otherwise return 1
            if (current->is_shadow_) {
                current->is_shadow_ = false;
                return (0);
            } else {
                return (1);
            }
        } else {
            const int common_label_count = compare_result.getCommonLabels();
            if (common_label_count == 1) {
                order = compare_result.getOrder();
                current = order < 0 ? current->left_ : current->right_;
            } else {
                // insert sub domain to sub tree
                if (relation == NameComparisonResult::SUBDOMAIN) {
                    if (NULL == current->down_) {
                        try {
                            RBTree<T>* new_sub_tree = new RBTree();
                            int ret = new_sub_tree->insert(name -
                                                           current->name_,
                                                           new_node);
                            if (-1 == ret) {
                                delete new_sub_tree;
                                return (-1);
                            }
                            current->setDownTree(new_sub_tree);
                            return (ret);
                        } catch (std::bad_alloc&) {
                            return (-1);
                        }
                    } else {
                        return (current->down_->insert(name - current->name_,
                                                       new_node));
                    }
                } else {
                    // for super domain or has common label domain, create
                    // common node first then insert current name and new name
                    // into the sub tree
                    const Name common_ancestor = name.split(
                        name.getLabelCount() - common_label_count,
                        common_label_count);
                    const Name sub_name = current->name_ - common_ancestor;
                    try {
                        // create new sub domain tree, and ty to insert 
                        // (current_name - common_ancestor) and (name - common_ancestor)
                        RBTree<T>* new_sub_tree = new RBTree();
                        RBNode<T>* sub_root;
                        if (-1 == new_sub_tree->insert(sub_name, &sub_root)) {
                            delete new_sub_tree;
                            return (-1);
                        }

                        int ret = 0;
                        if (name.getLabelCount() != common_label_count) {
                            ret = new_sub_tree->insert(name - common_ancestor,
                                                       new_node);
                            if (-1 == ret) {
                                delete new_sub_tree;
                                return (-1);
                            }
                        }
                            
                        RBTree<T>* down_old = current->down_;
                        current->setDownTree(new_sub_tree);
                        current->name_ = common_ancestor;
                        current->cloneDNSData(*sub_root);
                        sub_root->setDownTree(down_old);
                        sub_root->name_ = sub_name;
                        current->is_shadow_ = true;

                        if (name.getLabelCount() == common_label_count) {
                            *new_node = current;
                            current->is_shadow_ = false;
                            return (0);
                        } else {
                            return (ret);
                        }
                    } catch (std::bad_alloc&) {
                        return (-1);
                    }
                }
            }
        }
    }

    try {
        RBNode<T>* node = new RBNode<T>(name);
        node->parent_ = parent;
        if (parent == NULLNODE) {
            root_ = node;
        } else if (order < 0) {
            parent->left_ = node;
        } else {
            parent->right_ = node;
        }
        insertRebalance(node);
        if (new_node != NULL) {
            *new_node = node;
        }
    } catch (std::bad_alloc&) {
        return (-1);
    }

    ++node_count_;
    return (0);
}

template <typename T>
void
RBTree<T>::insertRebalance(RBNode<T>* node) {
    RBNode<T>* uncle;

    while (node->parent_->color_ == RED) {
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
                    leftRotate(node);
                }

                node->parent_->color_ = BLACK;
                node->parent_->parent_->color_ = RED;

                rightRotate(node->parent_->parent_);
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
                    rightRotate(node);
                }

                node->parent_->color_ = BLACK;
                node->parent_->parent_->color_ = RED;

                leftRotate(node->parent_->parent_);
            }
        }
    }

    root_->color_ = BLACK;
}

template <typename T>
RBNode<T>*
RBTree<T>::leftRotate(RBNode<T>* p) {
    RBNode<T>* c = p->right_;

    p->right_ = c->left_;

    if (c->left_ != NULLNODE) {
        c->left_->parent_ = p;
    }

    c->parent_ = p->parent_;

    if (p->parent_ == NULLNODE) {
        root_ = c;
    } else if (p == p->parent_->left_) {
        p->parent_->left_ = c;
    } else {
        p->parent_->right_ = c;
    }

    c->left_ = p;
    p->parent_ = c;

    return (c);
}

template <typename T>
RBNode<T>*
RBTree<T>::rightRotate(RBNode<T>* p) {
    RBNode<T>* c = p->left_;

    p->left_ = c->right_;

    if (c->right_ != NULLNODE) {
        c->right_->parent_ = p;
    }

    c->parent_ = p->parent_;

    if (p->parent_ == NULLNODE) {
        root_ = c;
    } else if (p == p->parent_->left_) {
        p->parent_->left_ = c;
    } else {
        p->parent_->right_ = c;
    }

    c->right_ = p;
    p->parent_ = c;

    return (c);
}

template <typename T>
int
RBTree<T>::erase(const Name& name) {
    RBNode<T>* node;
    const RBTree<T>* ctree;
    if (findHelper(name, &ctree, &node) != RBTree<T>::EXACTMATCH) {
        return (1);
    }

    // for node with downpointer, set it to shadow
    if (node->down_ != NULL) {
        assert(node->is_shadow_ == false);
        node->is_shadow_ = true;
        return (0);
    }

    RBTree<T>* tree = const_cast<RBTree<T>*>(ctree);
    tree->eraseNode(node);

    if (NULL != tree->up_) {
        // merge down to up
        if (1 == tree->node_count_ && tree->up_->is_shadow_) {
            RBNode<T>* up = tree->up_;
            const Name merged_name = tree->root_->name_.concatenate(up->name_);
            tree->root_->cloneDNSData(*up);
            up->setDownTree(tree->root_->down_);
            tree->root_->setDownTree(NULL);
            up->name_ = merged_name;
            up->is_shadow_ = false;
            delete tree;
        } else if (0 == tree->node_count_) { // delete empty tree
            tree->up_->setDownTree(NULL);
            delete tree;
        }
    }
    return (0);
}

template <typename T>
void
RBTree<T>::eraseNode(RBNode<T> *node) {
    RBNode<T>* y = NULLNODE;
    RBNode<T>* x = NULLNODE;

    if (node->left_ == NULLNODE || node->right_ == NULLNODE) {
        y = node;
    } else {
        y = const_cast<RBNode<T>*>(node->successor());
    }

    if (y->left_ != NULLNODE) {
        x = y->left_;
    } else {
        x = y->right_;
    }

    x->parent_ = y->parent_;

    if (y->parent_ == NULLNODE) {
        root_ = x;
    } else if (y == y->parent_->left_) {
        y->parent_->left_ = x;
    } else {
        y->parent_->right_ = x;
    }

    if (y != node) {
        y->cloneDNSData(*node);
        node->setDownTree(y->down_);
        y->down_ = NULL;
    }

    if (y->color_ == BLACK) {
        deleteRebalance(x);
    }

    y->left_ = NULL;
    y->right_ = NULL;
    delete y;
    --node_count_;
}

template <typename T>
void
RBTree<T>::deleteRebalance(RBNode<T>* node) {
    RBNode<T>* w = NULLNODE;

    while (node != root_ && node->color_ == BLACK) {
        if (node == node->parent_->left_) {
            w = node->parent_->right_;

            if (w->color_ == RED) {
                w->color_ = BLACK;
                node->parent_->color_ = RED;
                leftRotate(node->parent_);
                w = node->parent_->right_;
            }

            if (w->left_->color_ == BLACK && w->right_->color_ == BLACK) {
                w->color_ = RED;
                node = node->parent_;
            } else {
                if (w->right_->color_ == BLACK) {
                    w->left_->color_ = BLACK;
                    w->color_ = RED;
                    rightRotate(w);
                    w = node->parent_->right_;
                }

                w->color_ = node->parent_->color_;
                node->parent_->color_ = BLACK;
                w->right_->color_ = BLACK;
                leftRotate(node->parent_);
                node = root_;
            }
        } else {
            w = node->parent_->left_;
            if (w->color_ == RED) {
                w->color_ = BLACK;
                node->parent_->color_ = RED;
                rightRotate(node->parent_);
                w = node->parent_->left_;
            }

            if (w->right_->color_ == BLACK && w->left_->color_ == BLACK) {
                w->color_ = RED;
                node = node->parent_;
            } else {
                if (w->left_->color_ == BLACK) {
                    w->right_->color_ = BLACK;
                    w->color_ = RED;
                    leftRotate(w);
                    w = node->parent_->left_;
                }
                w->color_ = node->parent_->color_;
                node->parent_->color_ = BLACK;
                w->left_->color_ = BLACK;
                rightRotate(node->parent_);
                node = root_;
            }
        }
    }

    node->color_ = BLACK;
}

#define INDNET(os, depth) do { \
    int i = 0; \
    for (; i < (depth) * 5; ++i) { \
        (os) << " "; \
    } \
} while(0)

template <typename T>
void
RBTree<T>::printTree(std::ostream &os, int depth) const {
    INDNET(os, depth);
    os << "tree has node " << node_count_ << "\n";
    printTreeHelper(os, root_, depth);
}

template <typename T>
void
RBTree<T>::printTreeHelper(std::ostream& os, const RBNode<T>* node,
                           int depth) const
{
    INDNET(os, depth);
    os << node->name_.toText() << " ("
              << ((node->color_ == BLACK) ? "black" : "red") << ")\n";
    os << ((node->is_shadow_) ? "[invisible] \n" : "\n");
    if (node->down_) {
        assert(node->down_->up_ == node);
        INDNET(os, depth + 1);
        os << "begin down from "<< node->name_.toText() << "\n";
        node->down_->printTree(os, depth + 1);
        INDNET(os, depth + 1);
        os << "end down from" << node->name_.toText() <<"\n";
    }

    if (node->left_ != NULLNODE) {
        printTreeHelper(os, node->left_, depth + 1);
    } else {
        INDNET(os, depth + 1);
        os << "NULL\n";
    }

    if (node->right_ != NULLNODE) {
        printTreeHelper(os, node->right_, depth + 1);
    } else {
        INDNET(os, depth + 1);
        os << "NULL\n";
    }
}

}
}

#endif  // _RBTREE_H

// Local Variables:
// mode: c++
// End:
