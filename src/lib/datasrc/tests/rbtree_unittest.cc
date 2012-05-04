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
    RBTreeTest() : rbtree_expose_empty_node(true), crbtnode(NULL) {
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

TEST_F(RBTreeTest, findError) {
    // For the version that takes a node chain, the chain must be empty.
    RBTreeNodeChain<int> chain;
    EXPECT_EQ(RBTree<int>::EXACTMATCH, rbtree.find<void*>(Name("a"), &crbtnode,
                                                          chain, NULL, NULL));
    // trying to reuse the same chain.  it should result in an exception.
    EXPECT_THROW(rbtree.find<void*>(Name("a"), &crbtnode, chain, NULL, NULL),
                 BadValue);
}

TEST_F(RBTreeTest, flags) {
    EXPECT_EQ(RBTree<int>::SUCCESS, rbtree.insert(Name("flags.example"),
                                                  &rbtnode));

    // by default, flags are all off
    EXPECT_FALSE(rbtnode->getFlag(RBNode<int>::FLAG_CALLBACK));

    // set operation, by default it enables the flag
    rbtnode->setFlag(RBNode<int>::FLAG_CALLBACK);
    EXPECT_TRUE(rbtnode->getFlag(RBNode<int>::FLAG_CALLBACK));

    // try disable the flag explicitly
    rbtnode->setFlag(RBNode<int>::FLAG_CALLBACK, false);
    EXPECT_FALSE(rbtnode->getFlag(RBNode<int>::FLAG_CALLBACK));

    // try enable the flag explicitly
    rbtnode->setFlag(RBNode<int>::FLAG_CALLBACK, true);
    EXPECT_TRUE(rbtnode->getFlag(RBNode<int>::FLAG_CALLBACK));

    // setting an unknown flag will trigger an exception
    EXPECT_THROW(rbtnode->setFlag(static_cast<RBNode<int>::Flags>(2), true),
                 isc::InvalidParameter);
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
    EXPECT_FALSE(rbtnode->getFlag(RBNode<int>::FLAG_CALLBACK));

    // enable/re-disable callback
    rbtnode->setFlag(RBNode<int>::FLAG_CALLBACK);
    EXPECT_TRUE(rbtnode->getFlag(RBNode<int>::FLAG_CALLBACK));
    rbtnode->setFlag(RBNode<int>::FLAG_CALLBACK, false);
    EXPECT_FALSE(rbtnode->getFlag(RBNode<int>::FLAG_CALLBACK));

    // enable again for subsequent tests
    rbtnode->setFlag(RBNode<int>::FLAG_CALLBACK);
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
    EXPECT_TRUE(rbtnode->getFlag(RBNode<int>::FLAG_CALLBACK));
    EXPECT_FALSE(subrbtnode->getFlag(RBNode<int>::FLAG_CALLBACK));
    EXPECT_FALSE(parentrbtnode->getFlag(RBNode<int>::FLAG_CALLBACK));

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
    parentrbtnode->setFlag(RBNode<int>::FLAG_CALLBACK);
    callback_called = false;
    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              rbtree.find(Name("callback.example"), &crbtnode, node_path2,
                          testCallback, &callback_called));
    EXPECT_FALSE(callback_called);
}

TEST_F(RBTreeTest, chainLevel) {
    RBTreeNodeChain<int> chain;

    // by default there should be no level in the chain.
    EXPECT_EQ(0, chain.getLevelCount());

    // insert one node to the tree and find it.  there should be exactly
    // one level in the chain.
    RBTree<int> tree(true);
    Name node_name(Name::ROOT_NAME());
    EXPECT_EQ(RBTree<int>::SUCCESS, tree.insert(node_name, &rbtnode));
    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              tree.find<void*>(node_name, &crbtnode, chain, NULL, NULL));
    EXPECT_EQ(1, chain.getLevelCount());

    /*
     * Now creating a possibly deepest tree with MAX_LABELS levels.
     * it should look like:
     *           (.)
     *            |
     *            a
     *            |
     *            a
     *            : (MAX_LABELS - 1) "a"'s
     *
     * then confirm that find() for the deepest name succeeds without any
     * disruption, and the resulting chain has the expected level.
     * Note that the root name (".") solely belongs to a single level,
     * so the levels begin with 2.
     */
    for (unsigned int i = 2; i <= Name::MAX_LABELS; ++i) {
        node_name = Name("a.").concatenate(node_name);
        EXPECT_EQ(RBTree<int>::SUCCESS, tree.insert(node_name, &rbtnode));
        RBTreeNodeChain<int> found_chain;
        EXPECT_EQ(RBTree<int>::EXACTMATCH,
                  tree.find<void*>(node_name, &crbtnode, found_chain,
                                   NULL, NULL));
        EXPECT_EQ(i, found_chain.getLevelCount());
    }

    // Confirm the last inserted name has the possible maximum length with
    // maximum label count.  This confirms the rbtree and chain level cannot
    // be larger.
    EXPECT_EQ(Name::MAX_LABELS, node_name.getLabelCount());
    EXPECT_THROW(node_name.concatenate(Name("a.")), TooLongName);
}

TEST_F(RBTreeTest, getAbsoluteNameError) {
    // an empty chain isn't allowed.
    RBTreeNodeChain<int> chain;
    EXPECT_THROW(chain.getAbsoluteName(), BadValue);
}

/*
 *the domain order should be:
 * a, b, c, d.e.f, x.d.e.f, w.y.d.e.f, o.w.y.d.e.f, p.w.y.d.e.f, q.w.y.d.e.f,
 * z.d.e.f, j.z.d.e.f, g.h, i.g.h
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
TEST_F(RBTreeTest, nextNode) {
    const char* const names[] = {
        "a", "b", "c", "d.e.f", "x.d.e.f", "w.y.d.e.f", "o.w.y.d.e.f",
        "p.w.y.d.e.f", "q.w.y.d.e.f", "z.d.e.f", "j.z.d.e.f", "g.h", "i.g.h"};
    const int name_count = sizeof(names) / sizeof(names[0]);
    RBTreeNodeChain<int> node_path;
    const RBNode<int>* node = NULL;
    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              rbtree.find<void*>(Name(names[0]), &node, node_path, NULL,
                                 NULL));
    for (int i = 0; i < name_count; ++i) {
        EXPECT_NE(static_cast<void*>(NULL), node);
        EXPECT_EQ(Name(names[i]), node_path.getAbsoluteName());
        node = rbtree.nextNode(node_path);
    }

    // We should have reached the end of the tree.
    EXPECT_EQ(static_cast<void*>(NULL), node);
}

// Check the previousNode
TEST_F(RBTreeTest, previousNode) {
    // First, iterate the whole tree from the end to the beginning.
    const char* const names[] = {
        "a", "b", "c", "d.e.f", "x.d.e.f", "w.y.d.e.f", "o.w.y.d.e.f",
        "p.w.y.d.e.f", "q.w.y.d.e.f", "z.d.e.f", "j.z.d.e.f", "g.h", "i.g.h"};
    const size_t name_count(sizeof(names) / sizeof(*names));
    RBTreeNodeChain<int> node_path;
    const RBNode<int>* node(NULL);
    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              rbtree.find<void*>(Name(names[name_count - 1]), &node, node_path,
                                 NULL, NULL));
    for (size_t i = name_count; i > 0; --i) {
        EXPECT_NE(static_cast<void*>(NULL), node);
        EXPECT_EQ(Name(names[i - 1]), node_path.getAbsoluteName());
        // Find the node at the path and check the value is the same
        // (that it really returns the correct corresponding node)
        const RBNode<int>* node2(NULL);
        RBTreeNodeChain<int> node_path2;
        EXPECT_EQ(RBTree<int>::EXACTMATCH,
                  rbtree.find<void*>(Name(names[i - 1]), &node2, node_path2,
                                     NULL, NULL));
        EXPECT_EQ(node, node2);
        node = rbtree.previousNode(node_path);
    }

    // We should have reached the end of the tree.
    EXPECT_EQ(static_cast<void*>(NULL), node);
    // This is all the same then
    EXPECT_EQ(static_cast<void*>(NULL), node);

    // Now, start somewhere in the middle, but within the real node.
    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              rbtree.find<void*>(Name(names[3]), &node, node_path,
                                 NULL, NULL));

    for (size_t i = 4; i > 0; --i) {
        EXPECT_NE(static_cast<void*>(NULL), node);
        EXPECT_EQ(Name(names[i - 1]), node_path.getAbsoluteName());
        // Find the node at the path and check the value is the same
        // (that it really returns the correct corresponding node)
        const RBNode<int>* node2(NULL);
        RBTreeNodeChain<int> node_path2;
        EXPECT_EQ(RBTree<int>::EXACTMATCH,
                  rbtree.find<void*>(Name(names[i - 1]), &node2, node_path2,
                                     NULL, NULL));
        EXPECT_EQ(node, node2);
        node = rbtree.previousNode(node_path);
    }

    // We should have reached the end of the tree.
    EXPECT_EQ(static_cast<void*>(NULL), node);

    // TODO: The tests where we start in between of the nodes somewhere
}

TEST_F(RBTreeTest, nextNodeError) {
    // Empty chain for nextNode() is invalid.
    RBTreeNodeChain<int> chain;
    EXPECT_THROW(rbtree.nextNode(chain), BadValue);
}

// A helper function for getLastComparedNode() below.
void
comparisonChecks(const RBTreeNodeChain<int>& chain,
                 int expected_order, int expected_common_labels,
                 NameComparisonResult::NameRelation expected_reln)
{
    if (expected_order > 0) {
        EXPECT_LT(0, chain.getLastComparisonResult().getOrder());
    } else if (expected_order < 0) {
        EXPECT_GT(0, chain.getLastComparisonResult().getOrder());
    } else {
        EXPECT_EQ(0, chain.getLastComparisonResult().getOrder());
    }
    EXPECT_EQ(expected_common_labels,
              chain.getLastComparisonResult().getCommonLabels());
    EXPECT_EQ(expected_reln,
              chain.getLastComparisonResult().getRelation());
}

TEST_F(RBTreeTest, getLastComparedNode) {
    RBTree<int>& tree = rbtree_expose_empty_node; // use the "empty OK" mode
    RBTreeNodeChain<int> chain;

    // initially there should be no 'last compared'.
    EXPECT_EQ(static_cast<void*>(NULL), chain.getLastComparedNode());

    // A search for an empty tree should result in no 'last compared', too.
    RBTree<int> empty_tree;
    EXPECT_EQ(RBTree<int>::NOTFOUND,
              empty_tree.find<void*>(Name("a"), &crbtnode, chain, NULL, NULL));
    EXPECT_EQ(static_cast<void*>(NULL), chain.getLastComparedNode());
    chain.clear();

    const RBNode<int>* expected_node = NULL;

    // Exact match case.  The returned node should be last compared.
    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              tree.find<void*>(Name("x.d.e.f"), &expected_node, chain,
                               NULL, NULL));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // 2 = # labels of "x."
    comparisonChecks(chain, 0, 2, NameComparisonResult::EQUAL);
    chain.clear();

    // Partial match, search stopped at the matching node, which should be
    // the last compared node.
    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              tree.find(Name("i.g.h"), &expected_node));
    EXPECT_EQ(RBTree<int>::PARTIALMATCH,
              tree.find<void*>(Name("x.i.g.h"), &crbtnode, chain,
                                 NULL, NULL));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // i.g.h < x.i.g.h, 2 = # labels of "i."
    comparisonChecks(chain, 1, 2, NameComparisonResult::SUBDOMAIN);
    chain.clear();

    // Partial match, search stopped in the subtree below the matching node
    // after following a left branch.
    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              tree.find(Name("x.d.e.f"), &expected_node));
    EXPECT_EQ(RBTree<int>::PARTIALMATCH,
              tree.find<void*>(Name("a.d.e.f"), &crbtnode, chain,
                                 NULL, NULL));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // a < x, 1 = # labels of "." (trailing dot)
    comparisonChecks(chain, -1, 1, NameComparisonResult::COMMONANCESTOR);
    chain.clear();

    // Partial match, search stopped in the subtree below the matching node
    // after following a right branch.
    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              tree.find(Name("z.d.e.f"), &expected_node));
    EXPECT_EQ(RBTree<int>::PARTIALMATCH,
              tree.find<void*>(Name("zz.d.e.f"), &crbtnode, chain,
                                 NULL, NULL));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // zz > z, 1 = # labels of "." (trailing dot)
    comparisonChecks(chain, 1, 1, NameComparisonResult::COMMONANCESTOR);
    chain.clear();

    // Partial match, search stopped at a node for a super domain of the
    // search name in the subtree below the matching node.
    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              tree.find(Name("w.y.d.e.f"), &expected_node));
    EXPECT_EQ(RBTree<int>::PARTIALMATCH,
              tree.find<void*>(Name("y.d.e.f"), &crbtnode, chain,
                                 NULL, NULL));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // y < w.y, 2 = # labels of "y."
    comparisonChecks(chain, -1, 2, NameComparisonResult::SUPERDOMAIN);
    chain.clear();

    // Partial match, search stopped at a node that share a common ancestor
    // with the search name in the subtree below the matching node.
    // (the expected node is the same as the previous case)
    EXPECT_EQ(RBTree<int>::PARTIALMATCH,
              tree.find<void*>(Name("z.y.d.e.f"), &crbtnode, chain,
                                 NULL, NULL));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // z.y > w.y, 2 = # labels of "y."
    comparisonChecks(chain, 1, 2, NameComparisonResult::COMMONANCESTOR);
    chain.clear();

    // Search stops in the highest level after following a left branch.
    EXPECT_EQ(RBTree<int>::EXACTMATCH, tree.find(Name("c"), &expected_node));
    EXPECT_EQ(RBTree<int>::NOTFOUND,
              tree.find<void*>(Name("bb"), &crbtnode, chain, NULL, NULL));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // bb < c, 1 = # labels of "." (trailing dot)
    comparisonChecks(chain, -1, 1, NameComparisonResult::COMMONANCESTOR);
    chain.clear();

    // Search stops in the highest level after following a right branch.
    // (the expected node is the same as the previous case)
    EXPECT_EQ(RBTree<int>::NOTFOUND,
              tree.find<void*>(Name("d"), &crbtnode, chain, NULL, NULL));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // d > c, 1 = # labels of "." (trailing dot)
    comparisonChecks(chain, 1, 1, NameComparisonResult::COMMONANCESTOR);
    chain.clear();
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

// Matching in the "root zone" may be special (e.g. there's no parent,
// any domain names should be considered a subdomain of it), so it makes
// sense to test cases with the root zone explicitly.
TEST_F(RBTreeTest, root) {
    RBTree<int> root;
    root.insert(Name::ROOT_NAME(), &rbtnode);
    rbtnode->setData(RBNode<int>::NodeDataPtr(new int(1)));

    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              root.find(Name::ROOT_NAME(), &crbtnode));
    EXPECT_EQ(rbtnode, crbtnode);
    EXPECT_EQ(RBTree<int>::PARTIALMATCH,
              root.find(Name("example.com"), &crbtnode));
    EXPECT_EQ(rbtnode, crbtnode);

    // Insert a new name that better matches the query name.  find() should
    // find the better one.
    root.insert(Name("com"), &rbtnode);
    rbtnode->setData(RBNode<int>::NodeDataPtr(new int(2)));
    EXPECT_EQ(RBTree<int>::PARTIALMATCH,
              root.find(Name("example.com"), &crbtnode));
    EXPECT_EQ(rbtnode, crbtnode);

    // Perform the same tests for the tree that allows matching against empty
    // nodes.
    RBTree<int> root_emptyok(true);
    root_emptyok.insert(Name::ROOT_NAME(), &rbtnode);
    EXPECT_EQ(RBTree<int>::EXACTMATCH,
              root_emptyok.find(Name::ROOT_NAME(), &crbtnode));
    EXPECT_EQ(rbtnode, crbtnode);
    EXPECT_EQ(RBTree<int>::PARTIALMATCH,
              root_emptyok.find(Name("example.com"), &crbtnode));
    EXPECT_EQ(rbtnode, crbtnode);

    root.insert(Name("com"), &rbtnode);
    EXPECT_EQ(RBTree<int>::PARTIALMATCH,
              root.find(Name("example.com"), &crbtnode));
    EXPECT_EQ(rbtnode, crbtnode);
}
}
