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


#include <cstdio>
#include <iostream>
#include <cassert>
#include "rbt_datasrc.h"

using namespace isc::dns;
namespace {
    /// helper function to remove the base domain from super domain
    /// the precondition of this function is thant super_name contains sub_name
    Name operator-(const Name& super_name, const Name& sub_name) {
        return (super_name.split(0, super_name.getLabelCount() - sub_name.getLabelCount()));
    }
}

namespace isc {
namespace datasrc {
RBNode::RBNode(const Name& name, RRsetListPtr rrsets, RBNode* nullnode)
:   parent_(nullnode),
    left_(nullnode),
    right_(nullnode),
    color_(RED),
    name_(name),
    rrsets_(rrsets),
    down_(NULL),
    is_delegate_(false),
    is_nonterminal_(false) {
}

RBNode::~RBNode() {
    if (down_)
        delete down_;
}

RBNode*
RBNode::successor() {
    RBNode* current = this;

    if (right_ != right_->right_) {
        current = right_;
        while (current->left_ != current->left_->left_)
            current = current->left_;
        return (current);
    }

    RBNode* s = current->parent_;
    while (s != s->left_ && current == s->right_) {
        current = s;
        s = s->parent_;
    }
    return (s);
}

/// no duplication is checked now
int
RBNode::addRRset(RRsetPtr rrset) {
    if (rrset->getType() == RRType::NS())
        is_delegate_ = true;
    if (rrsets_.get() == NULL)
        rrsets_.reset(new RRsetList());
    rrsets_->addRRset(rrset);
    is_nonterminal_ = false;
    return (0);
}

void
RBNode::cloneDNSData(RBNode& node) {
    node.name_ = name_;
    node.rrsets_ = rrsets_;
    node.is_delegate_ = is_delegate_;
    node.is_nonterminal_ = is_nonterminal_;
}

void
RBNode::setDownTree(RBTree* down) {
    down_ = down;
    if (down)
        down->up_ = this;
}


RBTree::RBTree() {
    NULLNODE = new RBNode(Name(" "));
    NULLNODE->parent_  = NULLNODE->left_ = NULLNODE->right_ = NULLNODE;
    NULLNODE->color_ = BLACK;
    root_ = NULLNODE;
    node_count_ = 0;
    up_ = NULL;
}


RBTree::~RBTree() {
    assert(root_ != NULL);

    delete NULLNODE;
    if (root_ == NULLNODE)
        return;

    RBNode* node = root_;
    while (root_->left_ != NULLNODE || root_->right_ != NULLNODE) {
        while (node->left_ != NULLNODE || node->right_ != NULLNODE)
            node = (node->left_ != NULLNODE) ? node->left_ : node->right_;

        RBNode* parent = node->parent_;
        if (parent->left_ == node)
            parent->left_ = NULLNODE;
        else
            parent->right_ = NULLNODE;
        delete node;
        node = parent;
    }

    delete root_;
    root_ = NULL;
}

RBTree::FindResult
RBTree::find(const Name& name, RBNode** node)const {
    RBTree* tree;
    return (findHelper(name, &tree, node));
}


RBTree::FindResult
RBTree::findHelper(const Name& name, RBTree** tree, RBNode** ret)const {
    RBNode* node = root_;
    while (node != NULLNODE) {
        NameComparisonResult compare_result = name.compare(node->name_);
        NameComparisonResult::NameRelation relation = compare_result.getRelation();
        if (relation == NameComparisonResult::EQUAL) {
            *tree = (RBTree*)this;
            *ret = node;
            return (RBTree::EXACTMATCH);
        }
        else {
            int common_label_count = compare_result.getCommonLabels();
            ///common label count equal one means, there is no common between two names
            if (common_label_count == 1)
                node = (compare_result.getOrder() < 0) ? node->left_ : node->right_;
            else if (NameComparisonResult::SUBDOMAIN == relation) {
                if (node->isDelegate()) {
                    *tree = (RBTree*)this;
                    *ret = node;
                    return (RBTree::FINDREFERRAL);
                }
                else if (node->down_)
                    /// the node all save the relative name, so we need to remove the suffix
                    return (node->down_->findHelper(name - node->name_, tree, ret));
                else
                    return (RBTree::NOTFOUND);

            }
            else
                return (RBTree::NOTFOUND);
        }
    }

    return (RBTree::NOTFOUND);
}

int
RBTree::getNodeCount() const {
    return (getNodeCountHelper(root_));

}

int
RBTree::getNodeCountHelper(const RBNode *node) const {
    if (NULLNODE == node)
        return (0);

    int sub_tree_node_count = node->down_ ? node->down_->getNodeCount() : 0;
    return (1 + sub_tree_node_count + getNodeCountHelper(node->left_) + getNodeCountHelper(node->right_));
}

int
RBTree::insert(const Name& name, RBNode** new_node) {
    RBNode* parent = NULLNODE;
    RBNode* current = root_;

    int order = -1;
    while (current != NULLNODE) {
        parent = current;

        NameComparisonResult compare_result = name.compare(current->name_);
        NameComparisonResult::NameRelation relation = compare_result.getRelation();
        if (relation == NameComparisonResult::EQUAL) {
            if (new_node)
                *new_node = current;
            /// if the node is non-ternimal, it doesn't exist, so we return 0
            return (current->rrsets_.get() ? 1 : 0);
        }
        else {
            int common_label_count = compare_result.getCommonLabels();
            if (common_label_count == 1) {
                order = compare_result.getOrder();
                current = order < 0 ? current->left_ : current->right_;
            } else {
                //insert sub domain to sub tree
                if (relation == NameComparisonResult::SUBDOMAIN) {
                    if (NULL == current->down_)
                        current->setDownTree(new RBTree());
                    return (current->down_->insert(name - current->name_, new_node));
                } else {
                    // for super domain or has common label domain, create common node first
                    // then insert current name and new name into the sub tree
                    Name common_ancestor = name.split(name.getLabelCount() - common_label_count, common_label_count);
                    Name sub_name = current->name_ - common_ancestor;
                    current->name_ = common_ancestor;
                    RBTree* down_old = current->down_;
                    current->setDownTree(new RBTree());
                    RBNode* sub_root;
                    current->down_->insert(sub_name, &sub_root);

                    current->cloneDNSData(*sub_root);
                    sub_root->setDownTree(down_old);
                    sub_root->name_ = sub_name;

                    current->rrsets_.reset();
                    //if insert name is the super domain of current node, no need insert
                    //otherwise insert it into the down tree
                    if (name.getLabelCount() == common_label_count) {
                        *new_node = current;
                        return (0);
                    } else {
                        current->is_nonterminal_ = true;
                        return (current->down_->insert(name - common_ancestor, new_node));
                    }
                }
            }

        }
    }

    RBNode* node = new RBNode(name, RBNode::RRsetListPtr(), NULLNODE);
    node->parent_ = parent;
    if (parent == NULLNODE)
        root_ = node;
    else if (order < 0)
        parent->left_ = node;
    else
        parent->right_ = node;

    insertRebalance(node);
    if (new_node)
        *new_node = node;
    ++node_count_;
    return (0);
}

void
RBTree::insertRebalance(RBNode* node) {
    RBNode* uncle;

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


RBNode*
RBTree::leftRotate(RBNode* p) {
    RBNode* c = p->right_;

    p->right_ = c->left_;

    if (c->left_ != NULLNODE)
        c->left_->parent_ = p;

    c->parent_ = p->parent_;

    if (p->parent_ == NULLNODE)
        root_ = c;
    else if (p == p->parent_->left_)
        p->parent_->left_ = c;
    else
        p->parent_->right_ = c;

    c->left_ = p;
    p->parent_ = c;

    return (c);
}

RBNode*
RBTree::rightRotate(RBNode* p) {
    RBNode* c = p->left_;

    p->left_ = c->right_;

    if (c->right_ != NULLNODE)
        c->right_->parent_ = p;

    c->parent_ = p->parent_;

    if (p->parent_ == NULLNODE)
        root_ = c;
    else if (p == p->parent_->left_)
        p->parent_->left_ = c;
    else
        p->parent_->right_ = c;

    c->right_ = p;
    p->parent_ = c;

    return (c);
}


int
RBTree::erase(const Name& name) {
    RBNode* node;
    RBTree* tree;
    if (findHelper(name, &tree, &node) != RBTree::EXACTMATCH)
        return (1);

    /// cann't delete non terminal
    if (node->down_ != NULL)
        return (1);

    tree->eraseNode(node);
    ///merge down to up
    if (tree->node_count_ == 1 && tree->up_ != NULL && tree->up_->isNonterminal()) {
        RBNode* up = tree->up_;
        Name merged_name = tree->root_->name_.concatenate(up->name_);
        tree->root_->cloneDNSData(*up);
        up->setDownTree(tree->root_->down_);
        tree->root_->setDownTree(NULL);
        up->name_ = merged_name;
        up->is_nonterminal_ = false;
        delete tree;
    } else if (tree->node_count_ == 0 && tree->up_) { ///delete empty tree
        tree->up_->setDownTree(NULL);
        delete tree;
    }

    return (0);
}


void
RBTree::eraseNode(RBNode *node) {
    RBNode* y = NULLNODE;
    RBNode* x = NULLNODE;

    if (node->left_ == NULLNODE || node->right_ == NULLNODE)
        y = node;
    else
        y = node->successor();

    if (y->left_ != NULLNODE)
        x = y->left_;
    else
        x = y->right_;

    x->parent_ = y->parent_;

    if (y->parent_ == NULLNODE)
        root_ = x;
    else if ( y == y->parent_->left_ )
        y->parent_->left_ = x;
    else
        y->parent_->right_ = x;

    if (y != node) {
        y->cloneDNSData(*node);
        node->setDownTree(y->down_);
        y->down_ = NULL;
    }

    if (y->color_ == BLACK)
        deleteRebalance(x);


    if ( y == root_)
        root_ = NULLNODE;

    y->left_ = NULL;
    y->right_ = NULL;
    delete y;
    --node_count_;
}

void
RBTree::deleteRebalance(RBNode* node) {
    RBNode* w = NULLNODE;

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
            } if (w->right_->color_ == BLACK && w->left_->color_ == BLACK) {
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

#define INDNET(depth) do{\
    int i = 0;\
    for (; i < (depth) * 5; ++i)\
        std::cout << " ";\
}while(0)

void
RBTree::printTree(int depth) const {
    INDNET(depth);
    std::cout << "tree has node " << node_count_ << "\n";
    printTreeHelper(root_, depth);
}


void
RBTree::printTreeHelper(RBNode* node, int depth) const {

    INDNET(depth);
    std::cout << node->name_.toText() << " (" << ((node->color_ == BLACK) ? "black" : "red") << ")\n";
    std::cout << ((node->isNonterminal()) ? "[non-terminal] \n" : "\n");
    if (node->down_) {
        assert(node->down_->up_ == node);
        INDNET(depth + 1);
        std::cout << "begin down from "<< node->name_.toText() << "\n";
        node->down_->printTree(depth + 1);
        INDNET(depth + 1);
        std::cout << "end down from" << node->name_.toText() <<"\n";
    }

    if (node->left_ != NULLNODE)
        printTreeHelper(node->left_, depth + 1);
    else {
        INDNET(depth + 1);
        std::cout << "NULL\n";
    }

    if (node->right_ != NULLNODE)
        printTreeHelper(node->right_, depth + 1);
    else {
        INDNET(depth + 1);
        std::cout << "NULL\n";
    }
}
}
}
