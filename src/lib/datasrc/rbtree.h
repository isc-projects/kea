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
#include <exception>
#include <ostream>
#include <algorithm>

namespace isc {
namespace datasrc {

namespace helper {

/// \note function in this namespace isnot intended to be used outside

/// helper function to remove the base domain from super domain
/// the precondition of this function is the super_name contains the
/// sub_name so \code Name a("a.b.c"); Name b("b.c"); 
/// Name c = a - b; \\c will be "a" \endcode
isc::dns::Name
operator-(const isc::dns::Name& super_name, const isc::dns::Name& sub_name) {
    return (super_name.split(0, super_name.getLabelCount() -
                             sub_name.getLabelCount()));
}

/// for indent purpose, add certian mount empty charachter to output stream
/// according to the depth.
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
/// \brief \c RBNode use by RBTree to store any data related to one domain name

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
/// For data stored in \c RBNode, RBNode will hold the ownership, therefore RBNode
/// will release it(call the deconstructor)finally, so it will be has problem if two
/// RBNode store the same data, or the data RBNode managed is delete outside RBNode
/// both will cause double delete.
template <typename T>
class RBNode : public boost::noncopyable {
public:
    /// only \c RBTree can create and destroy \c RBNode
    friend class RBTree<T>;

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

    /// \brief Deconstructor.
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
    T* getData() { return (data_); }
    /// \brief return the data stored in this node, read-only version
    const T *getData() const { return (data_);}

    /// \brief return whether the node has related data 
    /// \note it's meaningless has empty \c RBNode in one RBTree, the only 
    /// exception is for non-terminal node which has sub domain nodes who
    /// has data(rrset)
    bool isEmpty() const { return (data_ == NULL);}
    //@}

    /// \name Modify functions
    /// \brief set the data stored in the node
    /// this function also means ownership transfer, then data is owned by
    /// \c RBNode, and RBNode will in charge of the memory management
    /// \note when set new data, old data will be deleted first
    void setData(T* data);


private:
    /// This is a factory class method of a special singleton null node.
    static RBNode<T>* NULL_NODE() {
        static RBNode<T> null_node;
        return (&null_node);
    }

    /// \brief swap the content of two node, the content here refers to
    /// name, data, down
    void swap(RBNode<T>& node);

    /// data to maintain the rbtree balance
    RBNode<T>*  parent_;
    RBNode<T>*  left_;
    RBNode<T>*  right_;
    RBTreeColor color_;


    isc::dns::Name     name_;
    T*          data_;
    /// the down pointer points to the root node of sub domains of current 
    /// domain 
    /// \par Adding down pointer to \c RBNode is for two purpose:
    /// \li Accelerate the search process, with sub domain tree, it split the
    /// big flat tree into several hierarchy trees
    /// \li It save memory useage, so same label won't be saved several times 
    RBNode<T>*  down_;
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
    data_(NULL),
    down_(NULL)
{
}

template <typename T>
RBNode<T>::RBNode(const isc::dns::Name& name) :
    parent_(NULL_NODE()),
    left_(NULL_NODE()),
    right_(NULL_NODE()),
    color_(RED),
    name_(name),
    data_(NULL),
    down_(NULL)
{
}


template <typename T>
RBNode<T>::~RBNode() {
    delete data_;
}


template <typename T>
void 
RBNode<T>::setData(T* data) {
    if (data_ != data) {
        delete data_;
        data_ = data;
    }
}

template <typename T>
void
RBNode<T>::swap(RBNode<T>& node) {
    std::swap(node.name_, name_);
    std::swap(node.data_, data_);
    std::swap(node.down_, down_);
}


/// \brief \c RBTree class represents all the domains with the same suffix,
/// so it can be used to store the domains in one zone.
///
/// \c RBTree is a generic red black tree, and contains all the nodes with
/// the same suffix, since each name may have sub domain names 
/// so \c RBTree is a recursive data structure namely tree in tree.
/// So for one zone, several RBTrees may be involved. But from outside, the sub
/// tree is opaque for end users. 
///
/// \c RBTree split the domain space into hierarchy red black trees, nodes in one
/// tree has the same base name. The benefit of this struct is that:
/// - enhance the query performace compared with one big flat red black tree
/// - decrase the memory footprint to save common labels only once. 

/*
/// \verbatim
/// with the following names:
///     a       x.d.e.f     o.w.y.d.e.f
///     b       z.d.e.f     p.w.y.d.e.f
///     c       g.h         q.w.y.d.e.f
///     the tree will looks like:
///                               b
///                             /   \
///                            a    d.e.f
///                                   /|\
///                                  c | g.h
///                                    |
///                                   w.y
///                                   /|\
///                                  x | z
///                                    |
///                                    p
///                                   / \
///                                  o   q
/// \endverbatim
/// \note open problems:
/// - current find funciton only return non-empty nodes, so there is no difference 
///   between find one not exist name with empty non-terminal nodes, but in DNS query
///   logic, they are different
/// \todo 
/// - add remove interface
/// - add iterator to iterate the whole rbtree while may needed by axfr
/// - since \c RBNode only has down pointer without up pointer, the node path during finding 
///   should be recorded for later use
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
    /// inserted or not, it is better to call \code insert \endcode,instead of 
    /// \code find() \endcode, in case the name isn't exist and needs to insert again
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
    /// Each public function has related recursive helper function
    /// \brief tree with node as its root
    void deleteHelper(RBNode<T> *node);
    /// \brief find the node with name
    /// \param name is the target, up will points to the base domain of 
    /// the tree which name resides, node will point to the target node
    /// if we has exact same name or partical name in current tree.
    /// so for example, in zone a, we has 
    /// b.a, c.b.a and d.b.a search c.b.a, up will points to b.a. 
    /// and node will points to c.b.a
    Result findHelper(const isc::dns::Name& name, RBNode<T>** up,
                      RBNode<T>** node) const;
    void dumpTreeHelper(std::ostream& os, const RBNode<T>* node,
                        unsigned int depth) const;

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
    /// the count of real name user inserted into the domain tree
    unsigned int name_count_;
};

template <typename T>
RBTree<T>::RBTree() {
    NULLNODE = RBNode<T>::NULL_NODE();
    root_ = NULLNODE;
    node_count_ = 0;
    name_count_ = 0;
}

template <typename T>
RBTree<T>::~RBTree() {
    deleteHelper(root_);
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

        if (node->down_) {
            deleteHelper(node->down_);
        }
        delete node;
        node = parent;
    }
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
                *up_node = node;
                name = name - node->name_;
                if (node->isEmpty()) {
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
            if (current->isEmpty()) {
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
                        std::auto_ptr<RBNode<T> > node(new RBNode<T>(name - current->name_));
                        //root node of sub tree, the initial color is BLACK
                        node->color_ = BLACK;
                        current->down_ = node.get();
                        if (new_node != NULL) {
                            *new_node = node.get();
                        }
                        ++node_count_;
                        ++name_count_;
                        node.release();
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
                    nodeFission(*current, common_ancestor);
                }
            }
        }
    }

    RBNode<T>** current_root = up_node ? &(up_node->down_) : &root_;
    std::auto_ptr<RBNode<T> > node(new RBNode<T>(name));
    node->parent_ = parent;
    if (parent == NULLNODE) {
        *current_root = node.get();
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
    ++name_count_;
    node.release();
    return (SUCCEED);
}


template <typename T>
void
RBTree<T>::nodeFission(RBNode<T>& node, const isc::dns::Name& base_name) {
    using namespace helper;
    const isc::dns::Name sub_name = node.name_ - base_name;
    std::auto_ptr<RBNode<T> > down_node(new RBNode<T>(node.name_ - base_name));
    node.swap(*down_node);
    node.name_ = base_name;
    node.down_ = down_node.get();
    down_node->name_ = sub_name;
    //root node of sub tree, the initial color is BLACK
    down_node->color_ = BLACK;
    ++node_count_;
    down_node.release();
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
    os << ((node->isEmpty()) ? "[invisible] \n" : "\n");
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

}
}

#endif  // _RBTREE_H

// Local Variables:
// mode: c++
// End:
