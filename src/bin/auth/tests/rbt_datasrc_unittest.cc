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
    RBTreeTest() : rbtree() {
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
    RBTree<int> rbtree;
    RBNode<int> *rbtnode;
    const RBNode<int>* crbtnode;
};


TEST_F(RBTreeTest, getNodeCount) {
    EXPECT_EQ(13, rbtree.getNodeCount());
}

TEST_F(RBTreeTest, getNameCount) {
    EXPECT_EQ(11, rbtree.getNameCount());
    EXPECT_EQ(0, rbtree.insert(Name("d.e.f"), &rbtnode));
    EXPECT_EQ(12, rbtree.getNameCount());
    EXPECT_EQ(0, rbtree.erase(Name("d.e.f")));
    EXPECT_EQ(11, rbtree.getNameCount());
    EXPECT_EQ(0, rbtree.erase(Name("o.w.y.d.e.f")));
    EXPECT_EQ(10, rbtree.getNameCount());
    EXPECT_EQ(0, rbtree.erase(Name("p.w.y.d.e.f")));
    EXPECT_EQ(9, rbtree.getNameCount());
    EXPECT_EQ(0, rbtree.erase(Name("q.w.y.d.e.f")));
    EXPECT_EQ(8, rbtree.getNameCount());
}

TEST_F(RBTreeTest, insertNames) {
    // a node is considered to "formally" exist only if it has data
    // associated with it
    // return 0, since node "d.e.f" doesn't have data
    EXPECT_EQ(0, rbtree.insert(Name("d.e.f"), &rbtnode));
    EXPECT_EQ(Name("d.e.f"), rbtnode->getName());
    EXPECT_EQ(13, rbtree.getNodeCount());

    EXPECT_EQ(0, rbtree.insert(Name("."), &rbtnode));
    EXPECT_EQ(Name("."), rbtnode->getName());
    EXPECT_EQ(14, rbtree.getNodeCount());

    EXPECT_EQ(0, rbtree.insert(Name("example.com"), &rbtnode));
    EXPECT_EQ(15, rbtree.getNodeCount());

    // return 1, since node "example.com" already has data associated with it
    int data = 10;
    rbtnode->setData(data);
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

    EXPECT_EQ(0, rbtree.insert(Name("r.d.e.f"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("s.d.e.f"), &rbtnode));
    EXPECT_EQ(23, rbtree.getNodeCount());
}

TEST_F(RBTreeTest, findName) {
    // exact match
    EXPECT_EQ(RBTree<int>::EXACTMATCH, rbtree.find(Name("a"), &crbtnode));
    EXPECT_EQ(Name("a"), crbtnode->getName());

    // not found
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("d.e.f"), &crbtnode));
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("x"), &crbtnode));
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("m.n"), &crbtnode));

    // partial match
    EXPECT_EQ(RBTree<int>::PARTIALMATCH, rbtree.find(Name("m.b"), &crbtnode));
    EXPECT_EQ(Name("b"), crbtnode->getName());
}

TEST_F(RBTreeTest, successor) {
    // traverse the trees
    EXPECT_EQ(RBTree<int>::EXACTMATCH, rbtree.find(Name("a"), &crbtnode));
    const RBNode<int> *successor_node = crbtnode->successor();
    EXPECT_EQ(Name("b"), successor_node->getName());
    successor_node = successor_node->successor();
    EXPECT_EQ(Name("c"), successor_node->getName());
    successor_node = successor_node->successor();
    EXPECT_EQ(Name("d.e.f"), successor_node->getName());
    successor_node = successor_node->successor();
    EXPECT_EQ(Name("g.h"), successor_node->getName());
    successor_node = successor_node->successor();

    EXPECT_EQ(RBTree<int>::EXACTMATCH, rbtree.find(Name("x.d.e.f"), &crbtnode));
    EXPECT_EQ(Name("x"), crbtnode->getName());
    successor_node = crbtnode->successor();
    EXPECT_EQ(Name("w.y"), successor_node->getName());
    successor_node = successor_node->successor();
    EXPECT_EQ(Name("z"), successor_node->getName());

    EXPECT_EQ(RBTree<int>::EXACTMATCH, rbtree.find(Name("o.w.y.d.e.f"),
                                                   &crbtnode));
    EXPECT_EQ(Name("o"), crbtnode->getName());
    successor_node = crbtnode->successor();
    EXPECT_EQ(Name("p"), successor_node->getName());
    successor_node = successor_node->successor();
    EXPECT_EQ(Name("q"), successor_node->getName());
}

TEST_F(RBTreeTest, eraseName) {
    EXPECT_EQ(0, rbtree.insert(Name("k"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("r.d.e.f"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("s.d.e.f"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("y"), &rbtnode));
    EXPECT_EQ(17, rbtree.getNodeCount());
    /*
     *             b
     *           /   \
     *          a    d.e.f
     *              /  |   \
     *             c   |     k
     *                 |    / \
     *               w.y   g.h  y
     *             /   | \  |
     *            s    |  z i
     *           / \   |  |
     *          r  x   p  j
     *               /   \
     *              o     q
     */

    EXPECT_EQ(0, rbtree.erase(Name("a")));
    EXPECT_EQ(0, rbtree.insert(Name("a"), &rbtnode));
    EXPECT_EQ(0, rbtree.erase(Name("k")));
    EXPECT_EQ(0, rbtree.erase(Name("y")));

    // can't delete shadow node
    EXPECT_EQ(1, rbtree.erase(Name("d.e.f")));
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("w.y.d.e.f"), &crbtnode));
    EXPECT_EQ(0, rbtree.erase(Name("p.w.y.d.e.f")));
    EXPECT_EQ(14, rbtree.getNodeCount());
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("p.w.y.d.e.f"),
                                                 &crbtnode));

    EXPECT_EQ(0, rbtree.erase(Name("q.w.y.d.e.f")));
    EXPECT_EQ(12, rbtree.getNodeCount());
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("q.w.y.d.e.f"),
                                                 &crbtnode));

    // o would not be rejoined with w.y if w.y had data
    // associated with the key
    EXPECT_EQ(RBTree<int>::EXACTMATCH, rbtree.find(Name("o.w.y.d.e.f"),
                                                   &crbtnode));
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("w.y.d.e.f"), &crbtnode));
    /*
     *               d.e.f
     *              /  |  \
     *            b    |   g.h
     *           / \   |    |
     *          a  c o.w.y  i
     *               /   \
     *             s       z
     *            / \      |
     *           r   x     j
     */
    EXPECT_EQ(0, rbtree.erase(Name("o.w.y.d.e.f")));
    EXPECT_EQ(11, rbtree.getNodeCount());
    EXPECT_EQ(1, rbtree.erase(Name("w.y.d.e.f")));
    EXPECT_EQ(11, rbtree.getNodeCount());
    EXPECT_EQ(0, rbtree.erase(Name("x.d.e.f")));
    EXPECT_EQ(10, rbtree.getNodeCount());
    /*
     *               d.e.f
     *              /  |  \
     *            b    |   g.h
     *           / \   |    |
     *          a  c   s    i
     *                / \
     *               r   z
     *                   |
     *                   j
     */
    // erase a non-exist node
    EXPECT_EQ(1, rbtree.erase(Name("x.d.e.f")));
    // delete all the nodes one by one
    EXPECT_EQ(0, rbtree.erase(Name("c")));
    EXPECT_EQ(9, rbtree.getNodeCount());
    EXPECT_EQ(0, rbtree.erase(Name("a")));
    EXPECT_EQ(8, rbtree.getNodeCount());
    EXPECT_EQ(0, rbtree.erase(Name("b")));
    EXPECT_EQ(7, rbtree.getNodeCount());
    EXPECT_EQ(0, rbtree.erase(Name("i.g.h")));
    EXPECT_EQ(6, rbtree.getNodeCount());
    /*
     *               d.e.f
     *                 |  \
     *                 |   g.h
     *                 |
     *                 s
     *                / \
     *               r   z
     *                   |
     *                   j
     */
    // can't delete shadow node
    EXPECT_EQ(0, rbtree.insert(Name("d.e.f"), &rbtnode));
    EXPECT_EQ(RBTree<int>::EXACTMATCH, rbtree.find(Name("d.e.f"), &crbtnode));
    EXPECT_EQ(0, rbtree.erase(Name("d.e.f")));
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("d.e.f"), &crbtnode));
    // d.e.f node become shadow
    EXPECT_EQ(1, rbtree.erase(Name("d.e.f")));
    // z is a shdow node
    EXPECT_EQ(0, rbtree.erase(Name("z.d.e.f")));
    EXPECT_EQ(6, rbtree.getNodeCount());
    EXPECT_EQ(0, rbtree.erase(Name("j.z.d.e.f")));
    EXPECT_EQ(5, rbtree.getNodeCount());
    EXPECT_EQ(0, rbtree.erase(Name("r.d.e.f")));
    EXPECT_EQ(4, rbtree.getNodeCount());
    // z will rejoin with d.e.f since d.e.f has no data
    EXPECT_EQ(0, rbtree.erase(Name("s.d.e.f")));
    EXPECT_EQ(2, rbtree.getNodeCount());
    /*
     *               z.d.e.f
     *                    \
     *                     g.h
     */

    EXPECT_EQ(0, rbtree.erase(Name("g.h")));
    EXPECT_EQ(1, rbtree.getNodeCount());

    // rebuild rbtree to cover different execution paths
    EXPECT_EQ(0, rbtree.insert(Name("a"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("g"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("b"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("d"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("c"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("e"), &rbtnode));
    /*
     *               z.d.e.f
     *                /   \
     *               b     g
     *             /  \
     *            a    d
     *               /   \
     *              c     e
     */
    EXPECT_EQ(0, rbtree.erase(Name("g")));
    EXPECT_EQ(0, rbtree.erase(Name("z.d.e.f")));
    EXPECT_EQ(5, rbtree.getNodeCount());

    EXPECT_EQ(0, rbtree.insert(Name("da"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("aa"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("ba"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("ca"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("m"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("nm"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("om"), &rbtnode));
    EXPECT_EQ(1, rbtree.insert(Name("da"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("k"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("l"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("fe"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("ge"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("i"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("ae"), &rbtnode));
    EXPECT_EQ(0, rbtree.insert(Name("n"), &rbtnode));
    EXPECT_EQ(19, rbtree.getNodeCount());
    /*
     *                  d
     *              /      \
     *            b          c
     *          /  \       /   \
     *        aa    c     e     nm
     *       / \   / \   / \    /\
     *      a  ae ba ca da ge  m  om
     *                    /  \  \
     *                   fe   k  n
     *                       /
     *                      i
     */
    // delete rbtree node one by one
    EXPECT_EQ(0, rbtree.erase(Name("nm")));
    EXPECT_EQ(0, rbtree.erase(Name("n")));
    EXPECT_EQ(0, rbtree.erase(Name("a")));
    EXPECT_EQ(0, rbtree.erase(Name("ae")));
    EXPECT_EQ(0, rbtree.erase(Name("i")));
    EXPECT_EQ(0, rbtree.erase(Name("aa")));
    EXPECT_EQ(0, rbtree.erase(Name("e")));
    EXPECT_EQ(0, rbtree.erase(Name("ge")));
    EXPECT_EQ(0, rbtree.erase(Name("k")));
    EXPECT_EQ(0, rbtree.erase(Name("m")));
    EXPECT_EQ(9, rbtree.getNodeCount());
    /*
     *                  d
     *              /      \
     *            c          c
     *          /  \       /   \
     *         b   ca     fe    om
     *         \         /
     *         ba       da
     */
    EXPECT_EQ(1, rbtree.erase(Name("am")));
    EXPECT_EQ(0, rbtree.erase(Name("fe")));
    EXPECT_EQ(0, rbtree.erase(Name("da")));
    EXPECT_EQ(0, rbtree.erase(Name("om")));
    EXPECT_EQ(0, rbtree.erase(Name("d")));
    EXPECT_EQ(0, rbtree.erase(Name("b")));
    EXPECT_EQ(0, rbtree.erase(Name("ba")));
    EXPECT_EQ(0, rbtree.erase(Name("ca")));
    EXPECT_EQ(0, rbtree.erase(Name("c")));
    EXPECT_EQ(0, rbtree.erase(Name("l")));
    EXPECT_EQ(0, rbtree.getNodeCount());
}

TEST_F(RBTreeTest, printTree) {
    std::ostringstream str;
    std::ostringstream str2;
    rbtree.printTree(str);
    str2 << "tree has node 5\nb. (black)\n\n     a. (black)\n\n          NULL\n          NULL\n     d.e.f. (black)\n[invisible] \n          begin down from d.e.f.\n          tree has node 3\n          w.y. (black)\n[invisible] \n               begin down from w.y.\n               tree has node 3\n               p. (black)\n\n                    o. (red)\n\n                         NULL\n                         NULL\n                    q. (red)\n\n                         NULL\n                         NULL\n               end down fromw.y.\n               x. (red)\n\n                    NULL\n                    NULL\n               z. (red)\n\n                    begin down from z.\n                    tree has node 1\n                    j. (black)\n\n                         NULL\n                         NULL\n                    end down fromz.\n                    NULL\n                    NULL\n          end down fromd.e.f.\n          c. (red)\n\n               NULL\n               NULL\n          g.h. (red)\n\n               begin down from g.h.\n               tree has node 1\n               i. (black)\n\n                    NULL\n                    NULL\n               end down fromg.h.\n               NULL\n               NULL\n";
    EXPECT_EQ(str.str(), str2.str());
    rbtree.erase(Name("o.w.y.d.e.f"));
    rbtree.erase(Name("p.w.y.d.e.f"));
    rbtree.erase(Name("q.w.y.d.e.f"));
    rbtree.erase(Name("j.z.d.e.f"));
    rbtree.erase(Name("x.d.e.f"));
    str.str("");
    str2.str("");
    rbtree.printTree(str);
    str2 << "tree has node 5\nb. (black)\n\n     a. (black)\n\n          NULL\n          NULL\n     z.d.e.f. (black)\n\n          c. (red)\n\n               NULL\n               NULL\n          g.h. (red)\n\n               begin down from g.h.\n               tree has node 1\n               i. (black)\n\n                    NULL\n                    NULL\n               end down fromg.h.\n               NULL\n               NULL\n";
    EXPECT_EQ(str.str(), str2.str());
}

}
