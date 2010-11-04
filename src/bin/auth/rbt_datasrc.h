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

class RBNode
{
    public:
        friend class RBTree;
        typedef boost::shared_ptr<RRsetList> RRsetListPtr;

        bool isDelegate() const { return is_delegate_;}
        int addRRset(RRsetPtr rrset);
        Name getName() const {return name_;}

    private:
        RBNode(const Name &name, RRsetListPtr rrsets = RRsetListPtr(), RBNode* nullnode = NULL);
        ~RBNode(); //the class isn't left to be inherited
        RBNode * successor();
        void cloneDNSData(RBNode &node);

        /// data to maintain the rbtree balance
        RBNode *  parent_;
        RBNode *  left_;
        RBNode *  right_;
        int       color_;

        /// data to carry dns info
        Name      name_;

        RRsetListPtr rrsets_;
        RBTree *  down_;
        bool      is_delegate_;

};


class RBTree
{
    public:
        enum FindResult{EXACTMATCH, FINDREFERRAL, NOTFOUND};

        RBTree(RBNode *up = NULL);
        ~RBTree();

        FindResult find(const Name &name, RBNode **node)const;
        int getNodeCount() const;
        void printTree(int depth = 0)const;

        int insert(const Name &name, RBNode **inserted_node);
        int erase(const Name &name);

    private:
        void deleteRebalance(RBNode* node);
        void insertRebalance(RBNode* node);
        RBNode * rightRotate(RBNode* p);
        RBNode * leftRotate(RBNode* p);
        void printTreeHelper(RBNode *node, int depth)const;
        void eraseNode(RBNode *node);
        FindResult findHelper(const Name &name, RBTree **tree, RBNode **node)const;
        int getNodeCountHelper(const RBNode *node) const;

        RBNode *  root_;
        RBNode *  NULLNODE;
        RBNode *  up_;
        unsigned int node_count_; //current  tree node count exclude the node in down pointing trees
};
}
}


#endif

