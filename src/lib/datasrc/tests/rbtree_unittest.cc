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

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>

#include <datasrc/rbtree.h>

#include <dns/tests/unittest_util.h>

using namespace std;
using namespace isc::dns;
using isc::UnitTestUtil;
using namespace isc::datasrc;

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
    RBTreeTest() : rbtree() {
        rbtree.insert(Name("c"), &rbtnode);
        rbtnode->setData(RBNode<int>::NodeDataPtr(new int(1)));
        rbtree.insert(Name("b"), &rbtnode);
        rbtnode->setData(RBNode<int>::NodeDataPtr(new int(2)));
        rbtree.insert(Name("a"), &rbtnode);
        rbtnode->setData(RBNode<int>::NodeDataPtr(new int(3)));
        rbtree.insert(Name("x.d.e.f"), &rbtnode);
        rbtnode->setData(RBNode<int>::NodeDataPtr(new int(4)));
        rbtree.insert(Name("z.d.e.f"), &rbtnode);
        rbtnode->setData(RBNode<int>::NodeDataPtr(new int(5)));
        rbtree.insert(Name("g.h"), &rbtnode);
        rbtnode->setData(RBNode<int>::NodeDataPtr(new int(6)));
        rbtree.insert(Name("i.g.h"), &rbtnode);
        rbtnode->setData(RBNode<int>::NodeDataPtr(new int(7)));
        rbtree.insert(Name("o.w.y.d.e.f"), &rbtnode);
        rbtnode->setData(RBNode<int>::NodeDataPtr(new int(8)));
        rbtree.insert(Name("j.z.d.e.f"), &rbtnode);
        rbtnode->setData(RBNode<int>::NodeDataPtr(new int(9)));
        rbtree.insert(Name("p.w.y.d.e.f"), &rbtnode);
        rbtnode->setData(RBNode<int>::NodeDataPtr(new int(10)));
        rbtree.insert(Name("q.w.y.d.e.f"), &rbtnode);
        rbtnode->setData(RBNode<int>::NodeDataPtr(new int(11)));
    }
    RBTree<int> rbtree;
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
    EXPECT_EQ(RBTree<int>::ALREADYEXIST, rbtree.insert(Name("d.e.f"), &rbtnode));
    EXPECT_EQ(Name("d.e.f"), rbtnode->getName());
    EXPECT_EQ(13, rbtree.getNodeCount());

    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("."), &rbtnode));
    EXPECT_EQ(Name("."), rbtnode->getName());
    EXPECT_EQ(14, rbtree.getNodeCount());

    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("example.com"), &rbtnode));
    EXPECT_EQ(15, rbtree.getNodeCount());
    rbtnode->setData(RBNode<int>::NodeDataPtr(new int(12)));

    // return ALREADYEXIST, since node "example.com" already has been explicitly inserted
    EXPECT_EQ(RBTree<int>::ALREADYEXIST, rbtree.insert(Name("example.com"), &rbtnode));
    EXPECT_EQ(15, rbtree.getNodeCount());

    // split the node "d.e.f"
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("k.e.f"), &rbtnode));
    EXPECT_EQ(Name("k"), rbtnode->getName());
    EXPECT_EQ(17, rbtree.getNodeCount());

    // split the node "g.h"
    EXPECT_EQ(RBTree<int>::ALREADYEXIST, rbtree.insert(Name("h"), &rbtnode));
    EXPECT_EQ(Name("h"), rbtnode->getName());
    EXPECT_EQ(18, rbtree.getNodeCount());

    // add child domain
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("m.p.w.y.d.e.f"), &rbtnode));
    EXPECT_EQ(Name("m"), rbtnode->getName());
    EXPECT_EQ(19, rbtree.getNodeCount());
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("n.p.w.y.d.e.f"), &rbtnode));
    EXPECT_EQ(Name("n"), rbtnode->getName());
    EXPECT_EQ(20, rbtree.getNodeCount());

    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("l.a"), &rbtnode));
    EXPECT_EQ(Name("l"), rbtnode->getName());
    EXPECT_EQ(21, rbtree.getNodeCount());

    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("r.d.e.f"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("s.d.e.f"), &rbtnode));
    EXPECT_EQ(23, rbtree.getNodeCount());

    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("h.w.y.d.e.f"), &rbtnode));

    // add more nodes one by one to cover leftRotate and rightRotate
    EXPECT_EQ(RBTree<int>::ALREADYEXIST, rbtree.insert(Name("f"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("m"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("nm"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("om"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("k"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("l"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("fe"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("ge"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("i"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("ae"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("n"), &rbtnode));
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

    // partial match
    EXPECT_EQ(RBTree<int>::PARTIALMATCH, rbtree.find(Name("m.b"), &crbtnode));
    EXPECT_EQ(Name("b"), crbtnode->getName());

    // find rbtnode
    EXPECT_EQ(RBTree<int>::EXACTMATCH, rbtree.find(Name("q.w.y.d.e.f"), &rbtnode));
    EXPECT_EQ(Name("q"), rbtnode->getName());
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
