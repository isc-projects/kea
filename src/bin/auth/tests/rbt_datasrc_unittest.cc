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

#include <auth/rbt_datasrc.h>

#include <dns/tests/unittest_util.h>

using namespace std;
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
    RBTreeTest() : rbtree()
    {
        rbtree.insert(Name("a"), &rbtnode);
        rbtree.insert(Name("b"), &rbtnode);
        rbtree.insert(Name("c"), &rbtnode);
        rbtree.insert(Name("x.d.e.f"), &rbtnode);
        rbtree.insert(Name("z.d.e.f"), &rbtnode);
        rbtree.insert(Name("g.h"), &rbtnode);
        rbtree.insert(Name("i.g.h"), &rbtnode);
        rbtree.insert(Name("o.w.y.d.e.f"), &rbtnode);
        rbtree.insert(Name("j.z.d.e.f"), &rbtnode);
        rbtree.insert(Name("p.w.y.d.e.f"), &rbtnode);
        rbtree.insert(Name("q.w.y.d.e.f"), &rbtnode);
    }
    RBTree rbtree;
    RBNode *rbtnode;
};


TEST_F(RBTreeTest, getNodeCount) {
    EXPECT_EQ(13, rbtree.getNodeCount());
}

TEST_F(RBTreeTest, insertNames) {
    // a node is considered to "formally" exist only if it has data
    // associated with it

    // EXPECT_EQ(0, rbtree.insert(Name("r"), &rbtnode));
    // return 0, since node "d.e.f" doesn't have data
    EXPECT_EQ(0, rbtree.insert(Name("d.e.f"), &rbtnode));
    EXPECT_EQ(Name("d.e.f"), rbtnode->getName());
    EXPECT_EQ(13, rbtree.getNodeCount());

    EXPECT_EQ(0, rbtree.insert(Name("."), &rbtnode));
    EXPECT_EQ(Name("."), rbtnode->getName());
    EXPECT_EQ(14, rbtree.getNodeCount());

    EXPECT_EQ(0, rbtree.insert(Name("example.com"), &rbtnode));
    EXPECT_EQ(15, rbtree.getNodeCount());

    // return 1, since node "d.e.f" already has data associated with it
    RRsetPtr rrset = RRsetPtr(new RRset(Name("example.com"), RRClass::IN(), RRType::NS(),
                                       RRTTL(3600)));
    rbtnode->addRRset(rrset);
    EXPECT_EQ(1, rbtree.insert(Name("example.com"), &rbtnode));
    EXPECT_EQ(15, rbtree.getNodeCount());

    // split the node "d.e.f"
    EXPECT_EQ(0, rbtree.insert(Name("k.e.f"), &rbtnode));
    EXPECT_EQ(Name("k"), rbtnode->getName());
    EXPECT_EQ(17, rbtree.getNodeCount());

    // split the node "g.h"
    EXPECT_EQ(0, rbtree.insert(Name("h"), &rbtnode));
    EXPECT_EQ(Name("h"), rbtnode->getName());
    EXPECT_EQ(18, rbtree.getNodeCount());

    // add child domain
    EXPECT_EQ(0, rbtree.insert(Name("m.p.w.y.d.e.f"), &rbtnode));
    EXPECT_EQ(Name("m"), rbtnode->getName());
    EXPECT_EQ(19, rbtree.getNodeCount());
    EXPECT_EQ(0, rbtree.insert(Name("n.p.w.y.d.e.f"), &rbtnode));
    EXPECT_EQ(Name("n"), rbtnode->getName());
    EXPECT_EQ(20, rbtree.getNodeCount());

    EXPECT_EQ(0, rbtree.insert(Name("l.a"), &rbtnode));
    EXPECT_EQ(Name("l"), rbtnode->getName());
    EXPECT_EQ(21, rbtree.getNodeCount());
}

TEST_F(RBTreeTest, findName) {
    // exact match
    EXPECT_EQ(RBTree::EXACTMATCH, rbtree.find(Name("a"), &rbtnode));
    EXPECT_EQ(Name("a"), rbtnode->getName());
    EXPECT_EQ(RBTree::EXACTMATCH, rbtree.find(Name("d.e.f"), &rbtnode));
    EXPECT_EQ(Name("d.e.f"), rbtnode->getName());

    // not found
    EXPECT_EQ(RBTree::NOTFOUND, rbtree.find(Name("x"), &rbtnode));
    EXPECT_EQ(RBTree::NOTFOUND, rbtree.find(Name("m.n"), &rbtnode));
    EXPECT_EQ(RBTree::NOTFOUND, rbtree.find(Name("o.p.w.y.d.e.f"), &rbtnode));
    EXPECT_EQ(RBTree::NOTFOUND, rbtree.find(Name("m.w.y.d.e.f"), &rbtnode));

    // find referral
    RRsetPtr rrset = RRsetPtr(new RRset(Name("d.e.f"), RRClass::IN(), RRType::NS(),
                                       RRTTL(3600)));
    rbtnode->addRRset(rrset);
    EXPECT_EQ(RBTree::FINDREFERRAL, rbtree.find(Name("m.d.e.f"), &rbtnode));
    EXPECT_EQ(Name("d.e.f"), rbtnode->getName());
}

TEST_F(RBTreeTest, successor) {
    // traverse the trees
    EXPECT_EQ(RBTree::EXACTMATCH, rbtree.find(Name("a"), &rbtnode));
    RBNode *successor_node = rbtnode->successor();
    EXPECT_EQ(Name("b"), successor_node->getName());
    successor_node = successor_node->successor();
    EXPECT_EQ(Name("c"), successor_node->getName());
    successor_node = successor_node->successor();
    EXPECT_EQ(Name("d.e.f"), successor_node->getName());
    successor_node = successor_node->successor();
    EXPECT_EQ(Name("g.h"), successor_node->getName());
    successor_node = successor_node->successor();

    EXPECT_EQ(RBTree::EXACTMATCH, rbtree.find(Name("x.d.e.f"), &rbtnode));
    EXPECT_EQ(Name("x"), rbtnode->getName());
    successor_node = rbtnode->successor();
    EXPECT_EQ(Name("w.y"), successor_node->getName());
    successor_node = successor_node->successor();
    EXPECT_EQ(Name("z"), successor_node->getName());

    EXPECT_EQ(RBTree::EXACTMATCH, rbtree.find(Name("o.w.y.d.e.f"), &rbtnode));
    EXPECT_EQ(Name("o"), rbtnode->getName());
    successor_node = rbtnode->successor();
    EXPECT_EQ(Name("p"), successor_node->getName());
    successor_node = successor_node->successor();
    EXPECT_EQ(Name("q"), successor_node->getName());
}

TEST_F(RBTreeTest, eraseName) {
    EXPECT_EQ(13, rbtree.getNodeCount());
    // can't delete non terminal
    int ret = rbtree.erase(Name("d.e.f"));
    EXPECT_EQ(1, ret);
    EXPECT_EQ(RBTree::EXACTMATCH, rbtree.find(Name("w.y.d.e.f"), &rbtnode));
    RRsetPtr rrset = RRsetPtr(new RRset(Name("w.y.d.e.f"), RRClass::IN(), RRType::A(),
                                       RRTTL(3600)));
    rbtnode->addRRset(rrset);
    ret = rbtree.erase(Name("p.w.y.d.e.f"));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(12, rbtree.getNodeCount());
    EXPECT_EQ(RBTree::NOTFOUND, rbtree.find(Name("p.w.y.d.e.f"), &rbtnode));

    ret = rbtree.erase(Name("q.w.y.d.e.f"));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(11, rbtree.getNodeCount());
    EXPECT_EQ(RBTree::NOTFOUND, rbtree.find(Name("q.w.y.d.e.f"), &rbtnode));

    // o would not be rejoined with w.y if w.y had data
    // associated with the key
    EXPECT_EQ(RBTree::EXACTMATCH, rbtree.find(Name("o.w.y.d.e.f"), &rbtnode));
    EXPECT_EQ(RBTree::EXACTMATCH, rbtree.find(Name("w.y.d.e.f"), &rbtnode));
    /*
     *             b
     *           /   \
     *          a    d.e.f
     *               / | \
     *              c  |  g.h
     *                 |   |
     *                w.y  i
     *               / | \
     *              x  |  z
     *                 |  |
     *                 o  j
     */
    // z would be rejoined with d.e.f, since d.e.f has no data associated with the key
    ret = rbtree.erase(Name("o.w.y.d.e.f"));

    EXPECT_EQ(0, ret);
    EXPECT_EQ(10, rbtree.getNodeCount());
    ret = rbtree.erase(Name("w.y.d.e.f"));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(9, rbtree.getNodeCount());
    ret = rbtree.erase(Name("x.d.e.f"));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(7, rbtree.getNodeCount());
    /*
     *             b
     *           /   \
     *          a   z.d.e.f
     *               / | \
     *              c  j  g.h
     *                     |
     *                     i
     */
    // erase a non-exist node
    ret = rbtree.erase(Name("x.d.e.f"));
    EXPECT_EQ(1, ret);

    // delete all the nodes one by one
    ret = rbtree.erase(Name("a"));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(6, rbtree.getNodeCount());
    ret = rbtree.erase(Name("g.h"));
    EXPECT_EQ(1, ret);
    EXPECT_EQ(6, rbtree.getNodeCount());
    ret = rbtree.erase(Name("c"));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(5, rbtree.getNodeCount());
    ret = rbtree.erase(Name("b"));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(4, rbtree.getNodeCount());
    ret = rbtree.erase(Name("i.g.h"));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(3, rbtree.getNodeCount());
    ret = rbtree.erase(Name("j.z.d.e.f"));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(2, rbtree.getNodeCount());
    ret = rbtree.erase(Name("g.h"));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(1, rbtree.getNodeCount());
    ret = rbtree.erase(Name("z.d.e.f"));
    EXPECT_EQ(0, ret);
    EXPECT_EQ(0, rbtree.getNodeCount());
}


TEST_F(RBTreeTest, isDelegate) {
    EXPECT_EQ(RBTree::EXACTMATCH, rbtree.find(Name("d.e.f"), &rbtnode));
    EXPECT_FALSE(rbtnode->isDelegate());

    // add a rrset
    RRsetPtr a_rrset = RRsetPtr(new RRset(Name("d.e.f"), RRClass::IN(), RRType::A(),
                                       RRTTL(3600)));
    rbtnode->addRRset(a_rrset);
    EXPECT_FALSE(rbtnode->isDelegate());

    // add ns rrset
    RRsetPtr ns_rrset = RRsetPtr(new RRset(Name("d.e.f"), RRClass::IN(), RRType::NS(),
                                       RRTTL(3600)));
    rbtnode->addRRset(ns_rrset);
    EXPECT_TRUE(rbtnode->isDelegate());
}

}
