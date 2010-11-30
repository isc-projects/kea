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
    RBNode<int>* rbtnode;
    const RBNode<int>* crbtnode;
};


TEST_F(RBTreeTest, getNodeCount) {
    EXPECT_EQ(13, rbtree.getNodeCount());
}

TEST_F(RBTreeTest, Iterator) {
    // test begin()
    RBTree<int>::Iterator iterator = rbtree.begin();

    // test operator "->"
    EXPECT_EQ(Name("a"), iterator->getName());

    // test operator "*"
    EXPECT_EQ(Name("a"), (*iterator).getName());

    // test operator "="
    RBTree<int>::Iterator back_iterator = iterator;

    // test operator "=="
    ASSERT_TRUE(iterator == back_iterator);

    // test operator "++"
    EXPECT_EQ(Name("a"), (iterator++)->getName());
    EXPECT_EQ(Name("b"), iterator->getName());

    // test operator "!="
    ASSERT_TRUE(iterator != back_iterator);

    // make the smallest node shadow
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("m.a"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("n.a"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("a")));
    iterator = rbtree.begin();
    EXPECT_EQ(Name("m"), iterator->getName());
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("k.x.d.e.f"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("l.x.d.e.f"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("x.d.e.f")));

    // test operator "++(int)"
    EXPECT_EQ(Name("n"), (++iterator)->getName());
    EXPECT_EQ(Name("b"), (++iterator)->getName());
    EXPECT_EQ(Name("c"), (++iterator)->getName());
    EXPECT_EQ(Name("k"), (++iterator)->getName());
    EXPECT_EQ(Name("l"), (++iterator)->getName());
    EXPECT_EQ(Name("o"), (++iterator)->getName());
    EXPECT_EQ(Name("p"), (++iterator)->getName());
    EXPECT_EQ(Name("q"), (++iterator)->getName());
    EXPECT_EQ(Name("z"), (++iterator)->getName());
    EXPECT_EQ(Name("j"), (++iterator)->getName());
    EXPECT_EQ(Name("g.h"), (++iterator)->getName());
    EXPECT_EQ(Name("i"), (++iterator)->getName());

    back_iterator = iterator;
    EXPECT_EQ(Name("i"), back_iterator->getName());
    // copy constructor
    RBTree<int>::Iterator copy_iterator(iterator);
    EXPECT_EQ(Name("i"), copy_iterator->getName());

    // test end()
    ASSERT_TRUE((++iterator) == rbtree.end());

}

TEST_F(RBTreeTest, set_get_Data) {
    int data = 10;
    rbtnode->setData(data);
    EXPECT_EQ(10, rbtnode->getData());
}

TEST_F(RBTreeTest, getNameCount) {
    EXPECT_EQ(11, rbtree.getNameCount());
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("d.e.f"), &rbtnode));
    EXPECT_EQ(12, rbtree.getNameCount());
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("d.e.f")));
    EXPECT_EQ(11, rbtree.getNameCount());
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("o.w.y.d.e.f")));
    EXPECT_EQ(10, rbtree.getNameCount());
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("p.w.y.d.e.f")));
    EXPECT_EQ(9, rbtree.getNameCount());
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("q.w.y.d.e.f")));
    EXPECT_EQ(8, rbtree.getNameCount());
}


TEST_F(RBTreeTest, insertNames) {
    // a node is considered to "formally" exist only if it's explicitly inserted
    // return SUCCEED, since name "d.e.f" hasn't been explicitly inserted
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("d.e.f"), &rbtnode));
    EXPECT_EQ(Name("d.e.f"), rbtnode->getName());
    EXPECT_EQ(13, rbtree.getNodeCount());

    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("."), &rbtnode));
    EXPECT_EQ(Name("."), rbtnode->getName());
    EXPECT_EQ(14, rbtree.getNodeCount());

    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("example.com"), &rbtnode));
    EXPECT_EQ(15, rbtree.getNodeCount());

    // return ALREADYEXIST, since node "example.com" already has been explicitly inserted
    EXPECT_EQ(RBTree<int>::ALREADYEXIST, rbtree.insert(Name("example.com"), &rbtnode));
    EXPECT_EQ(15, rbtree.getNodeCount());

    // split the node "d.e.f"
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("k.e.f"), &rbtnode));
    EXPECT_EQ(Name("k"), rbtnode->getName());
    EXPECT_EQ(17, rbtree.getNodeCount());

    // split the node "g.h"
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("h"), &rbtnode));
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
}

TEST_F(RBTreeTest, findName) {
    // find const rbtnode
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

    // find rbtnode
    EXPECT_EQ(RBTree<int>::EXACTMATCH, rbtree.find(Name("q.w.y.d.e.f"), &rbtnode));
    EXPECT_EQ(Name("q"), rbtnode->getName());
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
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("k"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("r.d.e.f"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("s.d.e.f"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("y"), &rbtnode));
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

    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("a")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("a"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("k")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("y")));

    // can't delete shadow node
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.erase(Name("d.e.f")));
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("w.y.d.e.f"), &crbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("p.w.y.d.e.f")));
    EXPECT_EQ(14, rbtree.getNodeCount());
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("p.w.y.d.e.f"),
                                                 &crbtnode));

    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("q.w.y.d.e.f")));
    EXPECT_EQ(12, rbtree.getNodeCount());
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("q.w.y.d.e.f"),
                                                 &crbtnode));

    // o would not be rejoined with w.y if w.y has been explicitly inserted
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
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("o.w.y.d.e.f")));
    EXPECT_EQ(11, rbtree.getNodeCount());
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.erase(Name("w.y.d.e.f")));
    EXPECT_EQ(11, rbtree.getNodeCount());
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("x.d.e.f")));
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
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.erase(Name("x.d.e.f")));
    // delete all the nodes one by one
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("c")));
    EXPECT_EQ(9, rbtree.getNodeCount());
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("a")));
    EXPECT_EQ(8, rbtree.getNodeCount());
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("b")));
    EXPECT_EQ(7, rbtree.getNodeCount());
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("i.g.h")));
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
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("d.e.f"), &rbtnode));
    EXPECT_EQ(RBTree<int>::EXACTMATCH, rbtree.find(Name("d.e.f"), &crbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("d.e.f")));
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.find(Name("d.e.f"), &crbtnode));
    // d.e.f node become shadow
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.erase(Name("d.e.f")));
    // j will rejoin with z since z is shadow
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("z.d.e.f")));
    EXPECT_EQ(5, rbtree.getNodeCount());
    /*
     *               d.e.f
     *                 |  \
     *                 |   g.h
     *                 |
     *                 s
     *                / \
     *               r  j.z
     */
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("j.z.d.e.f")));
    EXPECT_EQ(4, rbtree.getNodeCount());

    // s will rejoin with d.e.f since d.e.f is shadow
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("r.d.e.f")));
    EXPECT_EQ(2, rbtree.getNodeCount());
    /*
     *               s.d.e.f
     *                    \
     *                     g.h
     *
     *
     */
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("s.d.e.f")));
    EXPECT_EQ(1, rbtree.getNodeCount());

    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("g.h")));
    EXPECT_EQ(0, rbtree.getNodeCount());

    // rebuild rbtree to cover different execution paths
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("f"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("a"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("g"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("b"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("d"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("c"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("e"), &rbtnode));
    /*
     *                  f
     *                /   \
     *               b     g
     *             /  \
     *            a    d
     *               /   \
     *              c     e
     */
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("g")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("f")));
    EXPECT_EQ(5, rbtree.getNodeCount());

    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("da"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("aa"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("ba"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("ca"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("m"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("nm"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("om"), &rbtnode));
    EXPECT_EQ(RBTree<int>::ALREADYEXIST, rbtree.insert(Name("da"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("k"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("l"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("fe"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("ge"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("i"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("ae"), &rbtnode));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.insert(Name("n"), &rbtnode));
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
    // delete rbtree nodes one by one
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("nm")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("n")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("a")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("ae")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("i")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("aa")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("e")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("ge")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("k")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("m")));
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
    EXPECT_EQ(RBTree<int>::NOTFOUND, rbtree.erase(Name("am")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("fe")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("da")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("om")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("d")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("b")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("ba")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("ca")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("c")));
    EXPECT_EQ(RBTree<int>::SUCCEED, rbtree.erase(Name("l")));
    EXPECT_EQ(0, rbtree.getNodeCount());
}

TEST_F(RBTreeTest, dumpTree) {
    std::ostringstream str;
    std::ostringstream str2;
    rbtree.dumpTree(str);
    str2 << "tree has node(s) 13\nb. (black)\n     a. (black)\n          NULL\n          NULL\n     d.e.f. (black)[invisible] \n          begin down from d.e.f.\n          w.y. (black)[invisible] \n               begin down from w.y.\n               p. (black)\n                    o. (red)\n                         NULL\n                         NULL\n                    q. (red)\n                         NULL\n                         NULL\n               end down from w.y.\n               x. (red)\n                    NULL\n                    NULL\n               z. (red)\n                    begin down from z.\n                    j. (black)\n                         NULL\n                         NULL\n                    end down from z.\n                    NULL\n                    NULL\n          end down from d.e.f.\n          c. (red)\n               NULL\n               NULL\n          g.h. (red)\n               begin down from g.h.\n               i. (black)\n                    NULL\n                    NULL\n               end down from g.h.\n               NULL\n               NULL\n";
    EXPECT_EQ(str.str(), str2.str());
    rbtree.erase(Name("o.w.y.d.e.f"));
    rbtree.erase(Name("p.w.y.d.e.f"));
    rbtree.erase(Name("q.w.y.d.e.f"));
    rbtree.erase(Name("j.z.d.e.f"));
    rbtree.erase(Name("x.d.e.f"));
    str.str("");
    str2.str("");
    rbtree.dumpTree(str);
    str2 << "tree has node(s) 6\nb. (black)\n     a. (black)\n          NULL\n          NULL\n     z.d.e.f. (black)\n          c. (red)\n               NULL\n               NULL\n          g.h. (red)\n               begin down from g.h.\n               i. (black)\n                    NULL\n                    NULL\n               end down from g.h.\n               NULL\n               NULL\n";
    EXPECT_EQ(str.str(), str2.str());
}

}
