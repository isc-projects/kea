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

using namespace isc::dns;
namespace isc {
namespace datasrc {

enum RBTreeColor {BLACK = 1, RED};
class RBTree;

/// RBNode generally contains the data for one domain name
/// It's a general node of one rbtree with left, right, parent and color
/// It also carray the dns data like the rrsets belongs to the domain name
/// and a rbtree which is the subdomain of this node
/// the name of the node is relative. One special kind of node is non-terminal node
/// which has subdomains with rrset but it self doesn't has any rrset
///
///
/// RBNode memory management is totally handled by rbtree, so no constructor and destructor function is exposed

class RBNode {
    public:
        friend class RBTree;
        typedef boost::shared_ptr<RRsetList> RRsetListPtr;

        ///whether current domain name contains ns records
        bool isDelegate() const { return is_delegate_;}
        //subname has rrset, but it self doesn't has
        bool isNonterminal() const { return is_nonterminal_;}
        int addRRset(RRsetPtr rrset);
        const Name &getName() const {return name_;}

        //next domain name which is bigger than current one
        RBNode* successor();

    private:
        RBNode(const Name& name, RRsetListPtr rrsets = RRsetListPtr(), RBNode* nullnode = NULL);
        ~RBNode(); //the class isn't left to be inherited
        void cloneDNSData(RBNode& node);
        void setDownTree(RBTree* down);

        /// data to maintain the rbtree balance
        RBNode*  parent_;
        RBNode*  left_;
        RBNode*  right_;
        int       color_;

        /// data to carry dns info
        Name      name_;
        RRsetListPtr rrsets_;
        RBTree*  down_;
        bool      is_delegate_;
        bool      is_nonterminal_;
};

/// RBTree is a generic red black tree, it contains all the node with same suffix
/// So for one zone, severl RBTrees are involved. But from outside, the sub tree is
/// opaque for end user. if the sub tree only has one node and the base node which is pointed by the
/// "up_" pointer is one non-terminal, the single node will merge with the "up_" node then the sub tree will
/// be deleted
class RBTree {
    friend class RBNode;
    public:
        enum FindResult{EXACTMATCH, FINDREFERRAL, NOTFOUND};

        RBTree();
        ~RBTree();

        /// if find result isn't NOTFOUND, the node will point to the result
        /// with return value equal to NOTFOUND, the value of node is undetermined
        FindResult find(const Name& name, RBNode** node)const;

        /// get all the node count recursively, including the sub trees
        /// note that the return value isn't same with valid domain names in the tree
        /// the interface just used for test the tree logic, later will be removed
        int getNodeCount() const;


        void printTree(int depth = 0)const;

        /// if the name exists, return value will be one, and inserted_node will point to
        /// the existed node, otherwise return value is zero, and inserted_node points to
        /// new created node
        int insert(const Name& name, RBNode** inserted_node);

        /// if the node doesn't exist, return value will be one otherwise zero
        int erase(const Name& name);

    private:
        void deleteRebalance(RBNode* node);
        void insertRebalance(RBNode* node);
        RBNode* rightRotate(RBNode* p);
        RBNode* leftRotate(RBNode* p);
        void printTreeHelper(RBNode* node, int depth)const;
        void eraseNode(RBNode* node);

        /// recursive find one name in the tree, and return the exact tree has the name
        FindResult findHelper(const Name& name, RBTree** tree, RBNode** node)const;
        int getNodeCountHelper(const RBNode* node) const;

        void setUpNode(RBNode *node);

        RBNode*  root_;
        RBNode*  NULLNODE;
        RBNode*  up_;
        unsigned int node_count_; //current  tree node count exclude the node in down pointing trees
};
}
}


#endif

