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


#include <gtest/gtest.h>

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>

#include <datasrc/rbtree.h>

#include <dns/tests/unittest_util.h>

using namespace std;
using namespace isc;
using namespace isc::dns;
using isc::UnitTestUtil;
using namespace isc::datasrc;

// XXX: some compilers cannot find class static constants used in
// EXPECT_xxx macros, for which we need an explicit empty definition.
const size_t Name::MAX_LABELS;

/* The initial structure of rbtree
 *
 *             b
 *           /   \
 *          a    d.e.f
 *              /  |   \
 *             c   |    g.h
 *                 |     |
 *                w.y    i
 *              /  |  \
 *             x   |   z
 *                 |   |
 *                 p   j
 *               /   \
 *              o     q
 */

namespace {
class RBTreeTest : public::testing::Test {
protected:
    RBTreeTest() : rbtree_expose_empty_node(true) {
        const char* const domain_names[] = {
            "c", "b", "a", "x.d.e.f", "z.d.e.f", "g.h", "i.g.h", "o.w.y.d.e.f",
            "j.z.d.e.f", "p.w.y.d.e.f", "q.w.y.d.e.f"};
        int name_count = sizeof(domain_names) / sizeof(domain_names[0]);
        for (int i = 0; i < name_count; ++i) {
            rbtree.insert(Name(domain_names[i]), &rbtnode);
            rbtnode->setData(RBNode<int>::NodeDataPtr(new int(i + 1)));

            rbtree_expose_empty_node.insert(Name(domain_names[i]), &rbtnode);
            rbtnode->setData(RBNode<int>::NodeDataPtr(new int(i + 1)));

        }
    }

    RBTree<int> rbtree;
    RBTree<int> rbtree_expose_empty_node;
    RBNode<int>* rbtnode;
    const RBNode<int>* crbtnode;
};


TEST_F(RBTreeTest, getNodeCount) {
    EXPECT_EQ(13, rbtree.getNodeCount());
}

TEST_F(RBTreeTest, setGetData) {
    rbtnode->setData(RBNode<int>::NodeDataPtr(new int(11)));
    EXPECT_EQ(11, *(rbtnode->getData()));
}

TEST_F(RBTreeTest, insertNames) {
    EXPECT_EQ(RBTree<int>::ALREADYEXISTS, rbtree.insert(Name("d.e.f"),
                                                        &rbtnode));
    EXPECT_EQ(Name("d.e.f"), rbtnode->getName());
    EXPECT_EQ(13, rbtree.getNodeCount());

    //insert not exist node
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("."), &rbtnode));
    EXPECT_EQ(Name("."), rbtnode->getName());
    EXPECT_EQ(14, rbtree.getNodeCount());


    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("example.com"), &rbtnode));
    EXPECT_EQ(15, rbtree.getNodeCount());
    rbtnode->setData(RBNode<int>::NodeDataPtr(new int(12)));


    // return ALREADYEXISTS, since node "example.com" already has been explicitly inserted
    EXPECT_EQ(RBTree<int>::ALREADYEXISTS, rbtree.insert(Name("example.com"), &rbtnode));
    EXPECT_EQ(15, rbtree.getNodeCount());


    // split the node "d.e.f"
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("k.e.f"), &rbtnode));
    EXPECT_EQ(Name("k"), rbtnode->getName());
    EXPECT_EQ(17, rbtree.getNodeCount());



    // split the node "g.h"
    EXPECT_EQ(RBTree<int>::ALREADYEXISTS, rbtree.insert(Name("h"), &rbtnode));
    EXPECT_EQ(Name("h"), rbtnode->getName());
    EXPECT_EQ(18, rbtree.getNodeCount());


    // add child domain
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("m.p.w.y.d.e.f"), &rbtnode));
    EXPECT_EQ(Name("m"), rbtnode->getName());
    EXPECT_EQ(19, rbtree.getNodeCount());
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("n.p.w.y.d.e.f"), &rbtnode));
    EXPECT_EQ(Name("n"), rbtnode->getName());
    EXPECT_EQ(20, rbtree.getNodeCount());


    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("l.a"), &rbtnode));
    EXPECT_EQ(Name("l"), rbtnode->getName());
    EXPECT_EQ(21, rbtree.getNodeCount());


    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("r.d.e.f"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("s.d.e.f"), &rbtnode));
    EXPECT_EQ(23, rbtree.getNodeCount());


    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("h.w.y.d.e.f"), &rbtnode));

    // add more nodes one by one to cover leftRotate and rightRotate
    EXPECT_EQ(RBTree<int>::ALREADYEXISTS, rbtree.insert(Name("f"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("m"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("nm"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("om"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("k"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("l"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("fe"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("ge"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("i"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("ae"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("n"), &rbtnode));
}

TEST_F(RBTreeTest, findName) {
    // find const rbtnode
    // exact match
    EXPECT_EQ(RBTree<int>::EXACTMATCH, rbtree.find(Name("a"), &crbtnode));
    EXPECT_EQ(Name("a"), crbtnode->getName());

    // not found
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("d.e.f"), &crbtnode));
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("y.d.e.f"), &crbtnode));
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("x"), &crbtnode));
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("m.n"), &crbtnode));

    // if we expose empty node, we can get the empty node created during insert
    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              rbtree_expose_empty_node.find(Name("d.e.f"), &crbtnode));
    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              rbtree_expose_empty_node.find(Name("w.y.d.e.f"), &crbtnode));

    // partial match
    EXPECT_EQ(RBTree<int>::PARTIALMATCH, rbtree.find(Name("m.b"), &crbtnode));
    EXPECT_EQ(Name("b"), crbtnode->getName());
    EXPECT_EQ(RBTree<int>::PARTIALMATCH,
              rbtree_expose_empty_node.find(Name("m.d.e.f"), &crbtnode));

    // find rbtnode
    EXPECT_EQ(RBTree<int>::EXACTMATCH, rbtree.find(Name("q.w.y.d.e.f"), &rbtnode));
    EXPECT_EQ(Name("q"), rbtnode->getName());
}

bool
testCallback(const RBNode<int>&, bool* callack_checker) {
    *callack_checker = true;
    return (false);
}

TEST_F(RBTreeTest, callback) {
    // by default callback isn't enabled
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("callback.example"),
                                                  &rbtnode));
    rbtnode->setData(RBNode<int>::NodeDataPtr(new int(1)));
    EXPECT_FALSE(rbtnode->isCallbackEnabled());

    // enable/re-disable callback
    rbtnode->enableCallback();
    EXPECT_TRUE(rbtnode->isCallbackEnabled());
    rbtnode->disableCallback();
    EXPECT_FALSE(rbtnode->isCallbackEnabled());

    // enable again for subsequent tests
    rbtnode->enableCallback();
    // add more levels below and above the callback node for partial match.
    RBNode<int>* subrbtnode;
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("sub.callback.example"),
                                                  &subrbtnode));
    subrbtnode->setData(RBNode<int>::NodeDataPtr(new int(2)));
    RBNode<int>* parentrbtnode;
    EXPECT_EQ(RBTree<int>::ALREADYEXISTS, rbtree.insert(Name("example"),
                                                       &parentrbtnode));
    //  the chilld/parent nodes shouldn't "inherit" the callback flag.
    // "rbtnode" may be invalid due to the insertion, so we need to re-find
    // it.
    EXPECT_EQ(RBTree<int>::EXACTMATCH, rbtree.find(Name("callback.example"),
                                                   &rbtnode));
    EXPECT_TRUE(rbtnode->isCallbackEnabled());
    EXPECT_FALSE(subrbtnode->isCallbackEnabled());
    EXPECT_FALSE(parentrbtnode->isCallbackEnabled());

    // check if the callback is called from find()
    RBTreeNodeChain<int> node_path1;
    bool callback_called = false;
    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              rbtree.find(Name("sub.callback.example"), &crbtnode, node_path1,
                          testCallback, &callback_called));
    EXPECT_TRUE(callback_called);

    // enable callback at the parent node, but it doesn't have data so
    // the callback shouldn't be called.
    RBTreeNodeChain<int> node_path2;
    parentrbtnode->enableCallback();
    callback_called = false;
    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              rbtree.find(Name("callback.example"), &crbtnode, node_path2,
                          testCallback, &callback_called));
    EXPECT_FALSE(callback_called);
}

TEST_F(RBTreeTest, dumpTree) {
    std::ostringstream str;
    std::ostringstream str2;
    rbtree.dumpTree(str);
    str2 << "tree has 13 node(s)\nb. (black)\n     a. (black)\n          NULL\n          NULL\n     d.e.f. (black)[invisible] \n          begin down from d.e.f.\n          w.y. (black)[invisible] \n               begin down from w.y.\n               p. (black)\n                    o. (red)\n                         NULL\n                         NULL\n                    q. (red)\n                         NULL\n                         NULL\n               end down from w.y.\n               x. (red)\n                    NULL\n                    NULL\n               z. (red)\n                    begin down from z.\n                    j. (black)\n                         NULL\n                         NULL\n                    end down from z.\n                    NULL\n                    NULL\n          end down from d.e.f.\n          c. (red)\n               NULL\n               NULL\n          g.h. (red)\n               begin down from g.h.\n               i. (black)\n                    NULL\n                    NULL\n               end down from g.h.\n               NULL\n               NULL\n";
    EXPECT_EQ(str.str(), str2.str());
}

TEST_F(RBTreeTest, swap) {
    // Store info about the first tree
    std::ostringstream str1;
    rbtree.dumpTree(str1);
    size_t count1(rbtree.getNodeCount());

    // Create second one and store state
    RBTree<int> tree2;
    RBNode<int>* node;
    tree2.insert(Name("second"), &node);
    std::ostringstream str2;
    tree2.dumpTree(str2);

    // Swap them
    ASSERT_NO_THROW(tree2.swap(rbtree));

    // Check their sizes
    ASSERT_EQ(1, rbtree.getNodeCount());
    ASSERT_EQ(count1, tree2.getNodeCount());

    // And content
    std::ostringstream out;
    rbtree.dumpTree(out);
    ASSERT_EQ(str2.str(), out.str());
    out.str("");
    tree2.dumpTree(out);
    ASSERT_EQ(str1.str(), out.str());
}
}
