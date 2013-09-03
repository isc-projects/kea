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

#include <util/memory_segment_local.h>
#include <util/random/random_number_generator.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>

#include <datasrc/memory/domaintree.h>

#include <dns/tests/unittest_util.h>

#include <boost/format.hpp>

#include <fstream>

using namespace std;
using namespace isc;
using namespace isc::dns;
using isc::UnitTestUtil;
using namespace isc::datasrc::memory;

// XXX: some compilers cannot find class static constants used in
// EXPECT_xxx macros, for which we need an explicit empty definition.
const size_t Name::MAX_LABELS;

/* The initial structure of dtree
 *
 *             .
 *             |
 *             b
 *           /   \
 *          a    d.e.f
 *              /  |   \
 *             c   |    g.h
 *                 |     |
 *                w.y    i
 *              /  |  \   \
 *             x   |   z   k
 *                 |   |
 *                 p   j
 *               /   \
 *              o     q
 */

namespace {

// The full absolute names of the nodes in the tree with the addition of
// the explicit root node.
const char* const domain_names[] = {
    "c", "b", "a", "x.d.e.f", "z.d.e.f", "g.h", "i.g.h", "o.w.y.d.e.f",
    "j.z.d.e.f", "p.w.y.d.e.f", "q.w.y.d.e.f", "k.g.h"
};

// These are set as the node data.
const int node_distances[] = {
    3, 1, 2, 2, 2, 3, 1, 2, 1, 1, 2, 2
};

const int name_count = sizeof(domain_names) / sizeof(domain_names[0]);

/*
 * The domain order should be:
 * ., a, b, c, d.e.f, x.d.e.f, w.y.d.e.f, o.w.y.d.e.f, p.w.y.d.e.f,
 * q.w.y.d.e.f, z.d.e.f, j.z.d.e.f, g.h, i.g.h, k.g.h
 *             . (no data, can't be found)
 *             |
 *             b
 *           /   \
 *          a    d.e.f
 *              /  |   \
 *             c   |    g.h
 *                 |     |
 *                w.y    i
 *              /  |  \   \
 *             x   |   z   k
 *                 |   |
 *                 p   j
 *               /   \
 *              o     q
 */

const char* const ordered_names[] = {
    "a", "b", "c", "d.e.f", "x.d.e.f", "w.y.d.e.f", "o.w.y.d.e.f",
    "p.w.y.d.e.f", "q.w.y.d.e.f", "z.d.e.f", "j.z.d.e.f",
    "g.h", "i.g.h", "k.g.h"};
const size_t ordered_names_count(sizeof(ordered_names) /
                                 sizeof(*ordered_names));

const char* const upper_node_names[] = {
    ".", ".", ".", ".", "d.e.f", "d.e.f", "w.y.d.e.f",
    "w.y.d.e.f", "w.y.d.e.f", "d.e.f", "z.d.e.f",
    ".", "g.h", "g.h"};

void deleteData(int* i) {
    delete i;
}

typedef DomainTree<int> TestDomainTree;
typedef DomainTreeNode<int> TestDomainTreeNode;
typedef DomainTreeNodeChain<int> TestDomainTreeNodeChain;

class TreeHolder {
public:
    TreeHolder(util::MemorySegment& mem_sgmt, TestDomainTree* tree) :
        mem_sgmt_(mem_sgmt), tree_(tree)
    {}
    ~TreeHolder() {
        TestDomainTree::destroy(mem_sgmt_, tree_, deleteData);
    }
    TestDomainTree* get() { return (tree_); }
private:
    util::MemorySegment& mem_sgmt_;
    TestDomainTree* tree_;
};

class DomainTreeTest : public::testing::Test {
protected:
    DomainTreeTest() :
        dtree_holder_(mem_sgmt_, TestDomainTree::create(mem_sgmt_)),
        dtree_expose_empty_node_holder_(mem_sgmt_,
                                         TestDomainTree::create(mem_sgmt_, true)),
        dtree(*dtree_holder_.get()),
        dtree_expose_empty_node(*dtree_expose_empty_node_holder_.get()),
        cdtnode(NULL)
    {
        for (int i = 0; i < name_count; ++i) {
            dtree.insert(mem_sgmt_, Name(domain_names[i]), &dtnode);
            // Check the node doesn't have any data initially.
            EXPECT_EQ(static_cast<int*>(NULL),
                      dtnode->setData(new int(i + 1)));

            dtree_expose_empty_node.insert(mem_sgmt_, Name(domain_names[i]),
                                            &dtnode);
            EXPECT_EQ(static_cast<int*>(NULL), dtnode->setData(
                          new int(node_distances[i])));
        }
    }

    util::MemorySegmentLocal mem_sgmt_;
    TreeHolder dtree_holder_;
    TreeHolder dtree_expose_empty_node_holder_;
    TestDomainTree& dtree;
    TestDomainTree& dtree_expose_empty_node;
    TestDomainTreeNode* dtnode;
    const TestDomainTreeNode* cdtnode;
    uint8_t buf[LabelSequence::MAX_SERIALIZED_LENGTH];
};

TEST_F(DomainTreeTest, nodeCount) {
    EXPECT_EQ(15, dtree.getNodeCount());

    // Delete all nodes, then the count should be set to 0.  This also tests
    // the behavior of removeAllNodes().
    dtree.removeAllNodes(mem_sgmt_, deleteData);
    EXPECT_EQ(0, dtree.getNodeCount());
}

TEST_F(DomainTreeTest, getDistance) {
    TestDomainTreeNodeChain node_path;
    const TestDomainTreeNode* node = NULL;
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("a"),
                                           &node,
                                           node_path));
    while (node != NULL) {
        const int* distance = node->getData();
        if (distance != NULL) {
            EXPECT_EQ(*distance, node->getDistance());
        }
        node = dtree_expose_empty_node.nextNode(node_path);
    }
}

TEST_F(DomainTreeTest, checkDistanceRandom) {
    // This test checks an important performance-related property of the
    // DomainTree (a red-black tree), which is important for us: the
    // longest path from a sub-tree's root to a node is no more than
    // 2log(n). This tests that the tree is balanced.

    // Names are inserted in random order.

    TreeHolder mytree_holder(mem_sgmt_, TestDomainTree::create(mem_sgmt_));
    TestDomainTree& mytree = *mytree_holder.get();
    isc::util::random::UniformRandomIntegerGenerator gen('a', 'z');
    const int log_num_nodes = 20;

    // Make a large million+ node top-level domain tree, i.e., the
    // following code inserts names such as:
    //
    //   savoucnsrkrqzpkqypbygwoiliawpbmz.
    //   wkadamcbbpjtundbxcmuayuycposvngx.
    //   wzbpznemtooxdpjecdxynsfztvnuyfao.
    //   yueojmhyffslpvfmgyfwioxegfhepnqq.
    //
    for (int i = 0; i < (1 << log_num_nodes); i++) {
        string namestr;
        while (true) {
            for (int j = 0; j < 32; j++) {
                namestr += gen();
            }
            namestr += '.';

            if (mytree.insert(mem_sgmt_, Name(namestr), &dtnode) ==
                TestDomainTree::SUCCESS) {
                break;
            }

            namestr.clear();
        }

        EXPECT_EQ(static_cast<int*>(NULL), dtnode->setData(new int(i + 1)));
    }

    // The distance from each node to its sub-tree root must be less
    // than 2 * log(n).
    EXPECT_GE(2 * log_num_nodes, mytree.getHeight());

    // Also check RB tree properties
    EXPECT_TRUE(mytree.checkProperties());
}

TEST_F(DomainTreeTest, checkDistanceSorted) {
    // This test checks an important performance-related property of the
    // DomainTree (a red-black tree), which is important for us: the
    // longest path from a sub-tree's root to a node is no more than
    // 2log(n). This tests that the tree is balanced.

    // Names are inserted in sorted order.

    TreeHolder mytree_holder(mem_sgmt_, TestDomainTree::create(mem_sgmt_));
    TestDomainTree& mytree = *mytree_holder.get();
    const int log_num_nodes = 20;

    // Make a large million+ node top-level domain tree, i.e., the
    // following code inserts names such as:
    //
    //   name00000000.
    //   name00000001.
    //   name00000002.
    //   name00000003.
    //
    for (int i = 0; i < (1 << log_num_nodes); i++) {
        const string namestr(boost::str(boost::format("name%08x.") % i));
        mytree.insert(mem_sgmt_, Name(namestr), &dtnode);
        EXPECT_EQ(static_cast<int*>(NULL), dtnode->setData(new int(i + 1)));
    }

    // The distance from each node to its sub-tree root must be less
    // than 2 * log(n).
    EXPECT_GE(2 * log_num_nodes, mytree.getHeight());

    // Also check RB tree properties
    EXPECT_TRUE(mytree.checkProperties());
}

TEST_F(DomainTreeTest, setGetData) {
    // set new data to an existing node.  It should have some data.
    int* newdata = new int(11);
    int* olddata = dtnode->setData(newdata);
    EXPECT_NE(static_cast<int*>(NULL), olddata);
    deleteData(olddata);
    EXPECT_EQ(11, *(dtnode->getData()));

    // clear the node.  we should get the new data back we just passed.
    olddata = dtnode->setData(NULL);
    EXPECT_EQ(newdata, olddata);
    deleteData(olddata);
}

TEST_F(DomainTreeTest, insertNames) {
    EXPECT_EQ(TestDomainTree::ALREADYEXISTS, dtree.insert(mem_sgmt_,
                                                        Name("d.e.f"),
                                                        &dtnode));
    EXPECT_EQ(Name("d.e.f"), dtnode->getName());
    EXPECT_EQ(15, dtree.getNodeCount());

    // insert not exist node
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_, Name("0"),
                                                  &dtnode));
    EXPECT_EQ(Name("0"), dtnode->getName());
    EXPECT_EQ(16, dtree.getNodeCount());

    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_,
                                                  Name("example.com"),
                                                  &dtnode));
    EXPECT_EQ(17, dtree.getNodeCount());
    // add data to it; also make sure it doesn't have data right now
    // (otherwise it would leak)
    EXPECT_EQ(static_cast<int*>(NULL), dtnode->setData(new int(12)));

    // return ALREADYEXISTS, since node "example.com" already has
    // been explicitly inserted
    EXPECT_EQ(TestDomainTree::ALREADYEXISTS, dtree.insert(mem_sgmt_,
                                                        Name("example.com"),
                                                        &dtnode));
    EXPECT_EQ(17, dtree.getNodeCount());

    // split the node "d.e.f"
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_, Name("k.e.f"),
                                                  &dtnode));
    EXPECT_EQ(Name("k"), dtnode->getName());
    EXPECT_EQ(19, dtree.getNodeCount());

    // split the node "g.h"
    EXPECT_EQ(TestDomainTree::ALREADYEXISTS, dtree.insert(mem_sgmt_, Name("h"),
                                                        &dtnode));
    EXPECT_EQ(Name("h"), dtnode->getName());
    EXPECT_EQ(20, dtree.getNodeCount());

    // add child domain
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_,
                                                  Name("m.p.w.y.d.e.f"),
                                                  &dtnode));
    EXPECT_EQ(Name("m"), dtnode->getName());
    EXPECT_EQ(21, dtree.getNodeCount());
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_,
                                                  Name("n.p.w.y.d.e.f"),
                                                  &dtnode));
    EXPECT_EQ(Name("n"), dtnode->getName());
    EXPECT_EQ(22, dtree.getNodeCount());

    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_, Name("l.a"),
                                                  &dtnode));
    EXPECT_EQ(Name("l"), dtnode->getName());
    EXPECT_EQ(23, dtree.getNodeCount());

    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_, Name("r.d.e.f"),
                                                  &dtnode));
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_, Name("s.d.e.f"),
                                                  &dtnode));
    EXPECT_EQ(25, dtree.getNodeCount());

    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_,
                                                  Name("h.w.y.d.e.f"),
                                                  &dtnode));

    // add more nodes one by one to cover leftRotate and rightRotate
    EXPECT_EQ(TestDomainTree::ALREADYEXISTS, dtree.insert(mem_sgmt_, Name("f"),
                                                        &dtnode));
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_, Name("m"),
                                                  &dtnode));
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_, Name("nm"),
                                                  &dtnode));
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_, Name("om"),
                                                  &dtnode));
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_, Name("k"),
                                                  &dtnode));
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_, Name("l"),
                                                  &dtnode));
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_, Name("fe"),
                                                  &dtnode));
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_, Name("ge"),
                                                  &dtnode));
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_, Name("i"),
                                                  &dtnode));
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_, Name("ae"),
                                                  &dtnode));
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_, Name("n"),
                                                  &dtnode));
}

TEST_F(DomainTreeTest, remove) {
    // Delete single nodes and check if the rest of the nodes exist
    for (int j = 0; j < ordered_names_count; ++j) {
        TreeHolder holder(mem_sgmt_, TestDomainTree::create(mem_sgmt_, true));
        TestDomainTree& tree(*holder.get());
        TestDomainTreeNode* node;

        for (int i = 0; i < name_count; ++i) {
            tree.insert(mem_sgmt_, Name(domain_names[i]), NULL);
        }

        for (int i = 0; i < ordered_names_count; ++i) {
            EXPECT_EQ(TestDomainTree::EXACTMATCH,
                      tree.find(Name(ordered_names[i]), &node));
            EXPECT_EQ(static_cast<int*>(NULL),
                      node->setData(new int(i)));
        }

        // Now, delete the j'th node from the tree.
        EXPECT_EQ(TestDomainTree::EXACTMATCH,
                  tree.find(Name(ordered_names[j]), &node));
        tree.remove(mem_sgmt_, node, deleteData);

        // Check RB tree properties
        EXPECT_TRUE(tree.checkProperties());

        // Now, walk through nodes in order.
        TestDomainTreeNodeChain node_path;
        const TestDomainTreeNode* cnode;
        int start_node;

        if (j == 0) {
            EXPECT_NE(TestDomainTree::EXACTMATCH,
                      tree.find(Name(ordered_names[0]),
                                &cnode));
            EXPECT_EQ(TestDomainTree::EXACTMATCH,
                      tree.find(Name(ordered_names[1]),
                                &cnode, node_path));
            start_node = 1;
        } else {
            EXPECT_EQ(TestDomainTree::EXACTMATCH,
                      tree.find(Name(ordered_names[0]),
                                &cnode, node_path));
            start_node = 0;
        }

        for (int i = start_node; i < ordered_names_count; ++i) {
            // If a superdomain is deleted, everything under that
            // sub-tree goes away.
            const Name nj(ordered_names[j]);
            const Name ni(ordered_names[i]);
            const NameComparisonResult result = nj.compare(ni);
            if ((result.getRelation() == NameComparisonResult::EQUAL) ||
                (result.getRelation() == NameComparisonResult::SUPERDOMAIN)) {
                continue;
            }

            EXPECT_NE(static_cast<void*>(NULL), cnode);
            const int* data = cnode->getData();
            EXPECT_EQ(i, *data);

            cnode = tree.nextNode(node_path);
        }

        // We should have reached the end of the tree.
        EXPECT_EQ(static_cast<void*>(NULL), cnode);
    }
}

TEST_F(DomainTreeTest, nodeFusion) {
    // Test that node fusion occurs when conditions permit.

    /* Original tree:
     *             .
     *             |
     *             b
     *           /   \
     *          a    d.e.f
     *              /  |   \
     *             c   |    g.h
     *                 |     |
     *                w.y    i
     *              /  |  \   \
     *             x   |   z   k
     *                 |   |
     *                 p   j
     *               /   \
     *              o     q
     *
     */

    // First, check that "d.e.f" and "w.y" exist independently.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("d.e.f"), &cdtnode));
    EXPECT_EQ(Name("d.e.f"), cdtnode->getName());

    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("w.y.d.e.f"), &cdtnode));
    EXPECT_EQ(Name("w.y"), cdtnode->getName());

    // Now, delete "x" node.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("x.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    // "d.e.f" should still exist independently as "w.y" still has a
    // left or right child.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("d.e.f"), &cdtnode));
    EXPECT_EQ(Name("d.e.f"), cdtnode->getName());

    // Now, delete "z" node.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("z.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    /* Deleting 'x' and 'z' should cause "w.y" to be fused with "d.e.f":
     *             .
     *             |
     *             b
     *           /   \
     *          a   w.y.d.e.f
     *              /  |    \
     *             c   |     g.h
     *                 |      |
     *                 p      i
     *               /   \     \
     *              o     q     k
     */

    // Check that "w.y" got fused with "d.e.f"
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("w.y.d.e.f"), &cdtnode));
    EXPECT_EQ(Name("w.y.d.e.f"), cdtnode->getName());

    // Check that "p" exists independently. This also checks that the
    // down pointer got saved correctly during the last fusion.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("p.w.y.d.e.f"), &cdtnode));
    EXPECT_EQ(Name("p"), cdtnode->getName());

    // Now, delete "o" and "q" nodes.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("o.w.y.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("q.w.y.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    /* Deleting 'o' and 'q' should cause "p" to be fused with "w.y.d.e.f":
     *             .
     *             |
     *             b
     *           /   \
     *          a   p.w.y.d.e.f
     *              /       \
     *             c         g.h
     *                        |
     *                        i
     *                         \
     *                          k
     */

    // Check that "p" got fused with "w.y.d.e.f"
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("p.w.y.d.e.f"), &cdtnode));
    EXPECT_EQ(Name("p.w.y.d.e.f"), cdtnode->getName());
}

TEST_F(DomainTreeTest, nodeFusionWithData) {
    // Test that node fusion does not occur when there is data in the
    // parent node.

    /* Original tree:
     *             .
     *             |
     *             b
     *           /   \
     *          a    d.e.f
     *              /  |   \
     *             c   |    g.h
     *                 |     |
     *                w.y    i
     *              /  |  \   \
     *             x   |   z   k
     *                 |   |
     *                 p   j
     *               /   \
     *              o     q
     *
     */

    // First, check that "d.e.f" and "w.y" exist independently.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("d.e.f"), &cdtnode));
    EXPECT_EQ(Name("d.e.f"), cdtnode->getName());

    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("w.y.d.e.f"), &cdtnode));
    EXPECT_EQ(Name("w.y"), cdtnode->getName());

    // Set data (some value 42) in the "d.e.f" node
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("d.e.f"), &dtnode));
    EXPECT_EQ(static_cast<int*>(NULL),
              dtnode->setData(new int(42)));

    // Now, delete "x" and "z" nodes.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("x.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("z.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    /* Deleting 'x' and 'z' should not cause "w.y" to be fused with
     * "d.e.f" because "d.e.f" is not empty (has data) in this case.
     *             .
     *             |
     *             b
     *           /   \
     *          a    d.e.f
     *              /  |   \
     *             c   |    g.h
     *                 |     |
     *                w.y    i
     *                 |      \
     *                 |       k
     *                 |
     *                 p
     *               /   \
     *              o     q
     *
     */

    // Check that "w.y" did not get fused with "d.e.f"
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("d.e.f"), &cdtnode));
    EXPECT_EQ(Name("d.e.f"), cdtnode->getName());

    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("w.y.d.e.f"), &cdtnode));
    EXPECT_EQ(Name("w.y"), cdtnode->getName());
}

TEST_F(DomainTreeTest, nodeFusionMultiple) {
    // Test that node fusion occurs up the tree multiple times when
    // conditions permit.

    /* Original tree:
     *             .
     *             |
     *             b
     *           /   \
     *          a    d.e.f
     *              /  |   \
     *             c   |    g.h
     *                 |     |
     *                w.y    i
     *              /  |  \   \
     *             x   |   z   k
     *                 |   |
     *                 p   j
     *               /   \
     *              o     q
     *
     */

    // Set data (some value 42) in the "d.e.f" node
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("d.e.f"), &dtnode));
    EXPECT_EQ(static_cast<int*>(NULL),
              dtnode->setData(new int(42)));

    // Now, delete "x" and "z" nodes.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("x.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("z.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    /* Deleting 'x' and 'z' should not cause "w.y" to be fused with
     * "d.e.f" because "d.e.f" is not empty (has data) in this case.
     *             .
     *             |
     *             b
     *           /   \
     *          a    d.e.f
     *              /  |   \
     *             c   |    g.h
     *                 |     |
     *                w.y    i
     *                 |      \
     *                 |       k
     *                 |
     *                 p
     *               /   \
     *              o     q
     *
     */

    // Check that "w.y" did not get fused with "d.e.f"
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("d.e.f"), &cdtnode));
    EXPECT_EQ(Name("d.e.f"), cdtnode->getName());

    // Now, clear the data on "d.e.f". (Ideally, this itself should
    // cause fusion of "d.e.f" and "w.y" to occur, but we only do fusion
    // during deletion in our DomainTree implementation.)
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("d.e.f"), &dtnode));
    delete dtnode->setData(NULL);

    // Check that "p" exists independently.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("p.w.y.d.e.f"), &cdtnode));
    EXPECT_EQ(Name("p"), cdtnode->getName());

    // Now, delete "o" and "q" nodes.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("o.w.y.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("q.w.y.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    // The deletion of "o" and "q" should cause "p" to fuse with "w.y"
    // to form "p.w.y". Then, as "d.e.f" is now empty and conditions
    // permit, for a second time up the forest, "p.w.y" is fused with
    // "d.e.f" to form "p.w.y.d.e.f".
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("p.w.y.d.e.f"), &cdtnode));
    EXPECT_EQ(Name("p.w.y.d.e.f"), cdtnode->getName());
}

TEST_F(DomainTreeTest, DISABLED_remove1) {
    ofstream o1("d1.dot");
    dtree_expose_empty_node.dumpDot(o1);
    o1.close();

    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("x.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    ofstream o2("d2.dot");
    dtree_expose_empty_node.dumpDot(o2);
    o2.close();

    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("z.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    ofstream o3("d3.dot");
    dtree_expose_empty_node.dumpDot(o3);
    o3.close();

    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("q.w.y.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    ofstream o4("d4.dot");
    dtree_expose_empty_node.dumpDot(o4);
    o4.close();

    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("o.w.y.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    ofstream o5("d5.dot");
    dtree_expose_empty_node.dumpDot(o5);
    o5.close();
}

TEST_F(DomainTreeTest, DISABLED_remove2) {
    ofstream o1("g1.dot");
    dtree_expose_empty_node.dumpDot(o1);
    o1.close();

    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("p.w.y.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    ofstream o2("g2.dot");
    dtree_expose_empty_node.dumpDot(o2);
    o2.close();
}

TEST_F(DomainTreeTest, DISABLED_remove3) {
    ofstream o1("g1.dot");
    dtree_expose_empty_node.dumpDot(o1);
    o1.close();

    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("b"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    ofstream o2("g2.dot");
    dtree_expose_empty_node.dumpDot(o2);
    o2.close();
}

TEST_F(DomainTreeTest, DISABLED_remove4) {
    ofstream o1("g1.dot");
    dtree_expose_empty_node.dumpDot(o1);
    o1.close();

    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("j.z.d.e.f"), &dtnode));
    dtree_expose_empty_node.remove(mem_sgmt_, dtnode, deleteData);

    ofstream o2("g2.dot");
    dtree_expose_empty_node.dumpDot(o2);
    o2.close();
}

TEST_F(DomainTreeTest, subTreeRoot) {
    // This is a testcase for a particular issue that went unchecked in
    // #2089's implementation, but was fixed in #2092. The issue was
    // that when a node was fissioned, FLAG_SUBTREE_ROOT was not being
    // copied correctly.

    EXPECT_EQ(TestDomainTree::ALREADYEXISTS,
              dtree_expose_empty_node.insert(mem_sgmt_, Name("d.e.f"),
                                              &dtnode));
    EXPECT_EQ(TestDomainTree::SUCCESS,
              dtree_expose_empty_node.insert(mem_sgmt_, Name("0"),
                                              &dtnode));
    EXPECT_EQ(TestDomainTree::SUCCESS,
              dtree_expose_empty_node.insert(mem_sgmt_, Name("example.com"),
                                              &dtnode));
    EXPECT_EQ(TestDomainTree::ALREADYEXISTS,
              dtree_expose_empty_node.insert(mem_sgmt_, Name("example.com"),
                                              &dtnode));
    EXPECT_EQ(TestDomainTree::SUCCESS,
              dtree_expose_empty_node.insert(mem_sgmt_, Name("k.e.f"),
                                              &dtnode));

    // "g.h" is not a subtree root
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("g.h"), &cdtnode));
    EXPECT_FALSE(cdtnode->getFlag(TestDomainTreeNode::FLAG_SUBTREE_ROOT));

    // fission the node "g.h"
    EXPECT_EQ(TestDomainTree::ALREADYEXISTS,
              dtree_expose_empty_node.insert(mem_sgmt_, Name("h"),
                                              &dtnode));

    // the node "h" (h.down_ -> "g") should not be a subtree root. "g"
    // should be a subtree root.
    EXPECT_FALSE(dtnode->getFlag(TestDomainTreeNode::FLAG_SUBTREE_ROOT));

    // "g.h" should be a subtree root now.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("g.h"), &cdtnode));
    EXPECT_TRUE(cdtnode->getFlag(TestDomainTreeNode::FLAG_SUBTREE_ROOT));
}

TEST_F(DomainTreeTest, additionalNodeFission) {
    // These are additional nodeFission tests added by #2054's rewrite
    // of DomainTree::nodeFission(). These test specific corner cases that
    // are not covered by other tests.

    // Insert "t.0" (which becomes the left child of its parent)
    EXPECT_EQ(TestDomainTree::SUCCESS,
              dtree_expose_empty_node.insert(mem_sgmt_, Name("t.0"),
                                             &dtnode));

    // "t.0" is not a subtree root
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("t.0"), &cdtnode));
    EXPECT_FALSE(cdtnode->getFlag(TestDomainTreeNode::FLAG_SUBTREE_ROOT));

    // fission the node "t.0"
    EXPECT_EQ(TestDomainTree::ALREADYEXISTS,
              dtree_expose_empty_node.insert(mem_sgmt_, Name("0"),
                                             &dtnode));

    // the node "0" ("0".down_ -> "t") should not be a subtree root. "t"
    // should be a subtree root.
    EXPECT_FALSE(dtnode->getFlag(TestDomainTreeNode::FLAG_SUBTREE_ROOT));

    // "t.0" should be a subtree root now.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("t.0"), &cdtnode));
    EXPECT_TRUE(cdtnode->getFlag(TestDomainTreeNode::FLAG_SUBTREE_ROOT));
}

TEST_F(DomainTreeTest, findName) {
    // find const dtnode
    // exact match
    EXPECT_EQ(TestDomainTree::EXACTMATCH, dtree.find(Name("a"), &cdtnode));
    EXPECT_EQ(Name("a"), cdtnode->getName());

    // not found
    EXPECT_EQ(TestDomainTree::NOTFOUND, dtree.find(Name("d.e.f"), &cdtnode));
    EXPECT_EQ(TestDomainTree::NOTFOUND, dtree.find(Name("y.d.e.f"), &cdtnode));
    EXPECT_EQ(TestDomainTree::NOTFOUND, dtree.find(Name("x"), &cdtnode));
    EXPECT_EQ(TestDomainTree::NOTFOUND, dtree.find(Name("m.n"), &cdtnode));

    // if we expose empty node, we can get the empty node created during insert
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("d.e.f"), &cdtnode));
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name("w.y.d.e.f"), &cdtnode));

    // partial match
    EXPECT_EQ(TestDomainTree::PARTIALMATCH, dtree.find(Name("m.b"), &cdtnode));
    EXPECT_EQ(Name("b"), cdtnode->getName());
    EXPECT_EQ(TestDomainTree::PARTIALMATCH,
              dtree_expose_empty_node.find(Name("m.d.e.f"), &cdtnode));

    // find cdtnode
    EXPECT_EQ(TestDomainTree::EXACTMATCH, dtree.find(Name("q.w.y.d.e.f"),
                                                   &cdtnode));
    EXPECT_EQ(Name("q"), cdtnode->getName());
}

TEST_F(DomainTreeTest, findError) {
    // For the version that takes a node chain, the chain must be empty.
    TestDomainTreeNodeChain chain;
    EXPECT_EQ(TestDomainTree::EXACTMATCH, dtree.find(Name("a"), &cdtnode,
                                                   chain));
    // trying to reuse the same chain.  it should result in an exception.
    EXPECT_THROW(dtree.find(Name("a"), &cdtnode, chain),
                 BadValue);
}

TEST_F(DomainTreeTest, flags) {
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt_,
                                                  Name("flags.example"),
                                                  &dtnode));

    // by default, flags are all off
    EXPECT_FALSE(dtnode->getFlag(TestDomainTreeNode::FLAG_CALLBACK));

    // set operation, by default it enables the flag
    dtnode->setFlag(TestDomainTreeNode::FLAG_CALLBACK);
    EXPECT_TRUE(dtnode->getFlag(TestDomainTreeNode::FLAG_CALLBACK));

    // try disable the flag explicitly
    dtnode->setFlag(TestDomainTreeNode::FLAG_CALLBACK, false);
    EXPECT_FALSE(dtnode->getFlag(TestDomainTreeNode::FLAG_CALLBACK));

    // try enable the flag explicitly
    dtnode->setFlag(TestDomainTreeNode::FLAG_CALLBACK, true);
    EXPECT_TRUE(dtnode->getFlag(TestDomainTreeNode::FLAG_CALLBACK));

    // setting an unknown flag will trigger an exception
    EXPECT_THROW(dtnode->setFlag(static_cast<TestDomainTreeNode::Flags>(2), true),
                 isc::InvalidParameter);
}

bool
testCallback(const TestDomainTreeNode&, bool* callback_checker) {
    *callback_checker = true;
    return (false);
}

template <typename T>
void
performCallbackTest(TestDomainTree& dtree,
                    util::MemorySegmentLocal& mem_sgmt,
                    const T& name_called,
                    const T& name_not_called)
{
    TestDomainTreeNode* dtnode;
    const TestDomainTreeNode* cdtnode;

    // by default callback isn't enabled
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt,
                                                  Name("callback.example"),
                                                  &dtnode));
    EXPECT_EQ(static_cast<int*>(NULL), dtnode->setData(new int(1)));
    EXPECT_FALSE(dtnode->getFlag(TestDomainTreeNode::FLAG_CALLBACK));

    // enable/re-disable callback
    dtnode->setFlag(TestDomainTreeNode::FLAG_CALLBACK);
    EXPECT_TRUE(dtnode->getFlag(TestDomainTreeNode::FLAG_CALLBACK));
    dtnode->setFlag(TestDomainTreeNode::FLAG_CALLBACK, false);
    EXPECT_FALSE(dtnode->getFlag(TestDomainTreeNode::FLAG_CALLBACK));

    // enable again for subsequent tests
    dtnode->setFlag(TestDomainTreeNode::FLAG_CALLBACK);
    // add more levels below and above the callback node for partial match.
    TestDomainTreeNode* subdtnode;
    EXPECT_EQ(TestDomainTree::SUCCESS, dtree.insert(mem_sgmt,
                                                  Name("sub.callback.example"),
                                                  &subdtnode));
    EXPECT_EQ(static_cast<int*>(NULL), subdtnode->setData(new int(2)));
    TestDomainTreeNode* parentdtnode;
    EXPECT_EQ(TestDomainTree::ALREADYEXISTS, dtree.insert(mem_sgmt,
                                                        Name("example"),
                                                        &parentdtnode));
    // the child/parent nodes shouldn't "inherit" the callback flag.
    // "dtnode" should still validly point to "callback.example", but we
    // explicitly confirm it.
    EXPECT_EQ(TestDomainTree::EXACTMATCH, dtree.find(Name("callback.example"),
                                                     &cdtnode));
    ASSERT_EQ(dtnode, cdtnode);
    EXPECT_TRUE(cdtnode->getFlag(TestDomainTreeNode::FLAG_CALLBACK));
    EXPECT_FALSE(subdtnode->getFlag(TestDomainTreeNode::FLAG_CALLBACK));
    EXPECT_FALSE(parentdtnode->getFlag(TestDomainTreeNode::FLAG_CALLBACK));

    // check if the callback is called from find()
    TestDomainTreeNodeChain node_path1;
    bool callback_called = false;
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree.find(name_called, &cdtnode, node_path1,
                          testCallback, &callback_called));
    EXPECT_TRUE(callback_called);

    // enable callback at the parent node, but it doesn't have data so
    // the callback shouldn't be called.
    TestDomainTreeNodeChain node_path2;
    parentdtnode->setFlag(TestDomainTreeNode::FLAG_CALLBACK);
    callback_called = false;
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree.find(name_not_called, &cdtnode, node_path2,
                          testCallback, &callback_called));
    EXPECT_FALSE(callback_called);
}

TEST_F(DomainTreeTest, callbackName) {
    const Name n1("sub.callback.example");
    const Name n2("callback.example");

    performCallbackTest(dtree, mem_sgmt_, n1, n2);
}

TEST_F(DomainTreeTest, callbackLabelSequence) {
    const Name n1("sub.callback.example");
    const Name n2("callback.example");
    const LabelSequence ls1(n1);
    const LabelSequence ls2(n2);

    performCallbackTest(dtree, mem_sgmt_, ls1, ls2);
}

TEST_F(DomainTreeTest, findInSubTree) {
    // For the version that takes a node chain, the chain must be empty.
    DomainTreeNodeChain<int> chain;
    bool flag;

    // Searching for a non-absolute (right-stripped) label sequence when
    // chain is empty should throw.
    const Name n0("w.y.d.e.f");
    LabelSequence ls0(n0);
    ls0.stripRight(1);
    EXPECT_THROW(dtree_expose_empty_node.find(ls0, &cdtnode, chain,
                                              testCallback, &flag),
                 isc::BadValue);

    // First, find a sub-tree node
    chain.clear();
    const LabelSequence ls1(n0);
    DomainTree<int>::Result result =
        dtree_expose_empty_node.find(ls1, &cdtnode, chain,
                                     testCallback, &flag);
    EXPECT_EQ(DomainTree<int>::EXACTMATCH, result);
    EXPECT_EQ(n0, chain.getAbsoluteName());

    // Searching for an absolute label sequence when chain is already
    // populated should throw.
    const Name n2a("o");
    const LabelSequence ls2a(n2a);
    EXPECT_THROW(dtree_expose_empty_node.find(ls2a, &cdtnode, chain,
                                              testCallback, &flag),
                 isc::BadValue);

    // Now, find "o.w.y.d.e.f." by right-stripping the "w.y.d.e.f."
    // suffix to "o" (non-absolute).
    const Name n2("o.w.y.d.e.f");
    LabelSequence ls2(n2);
    ls2.stripRight(6);
    EXPECT_EQ("o", ls2.toText());

    result = dtree_expose_empty_node.find(ls2, &cdtnode, chain,
                                          testCallback, &flag);
    EXPECT_EQ(DomainTree<int>::EXACTMATCH, result);
    EXPECT_EQ(n2, chain.getAbsoluteName());

    // Another test. Start with "d.e.f." node.
    chain.clear();
    const Name n3("d.e.f");
    const LabelSequence ls3(n3);
    result =
        dtree_expose_empty_node.find(ls3, &cdtnode, chain,
                                     testCallback, &flag);
    EXPECT_EQ(DomainTree<int>::EXACTMATCH, result);
    EXPECT_EQ(n3, chain.getAbsoluteName());

    // Now, find "o.w.y.d.e.f." by right-stripping the "w.y.d.e.f."
    // suffix to "o.w.y" (non-absolute).
    const Name n4("o.w.y.d.e.f");
    LabelSequence ls4(n2);
    ls4.stripRight(4);
    EXPECT_EQ("o.w.y", ls4.toText());

    result = dtree_expose_empty_node.find(ls4, &cdtnode, chain,
                                          testCallback, &flag);
    EXPECT_EQ(DomainTree<int>::EXACTMATCH, result);
    EXPECT_EQ(n4, chain.getAbsoluteName());
}

TEST_F(DomainTreeTest, findInSubTreeSameLabelSequence) {
    // For the version that takes a node chain, the chain must be empty.
    DomainTreeNodeChain<int> chain;
    bool flag;

    const Name n1("c.g.h");

    // First insert a "c.g.h." node.
    dtree_expose_empty_node.insert(mem_sgmt_, n1, &dtnode);

    /* Now, the tree looks like:
     *
     *             .
     *             |
     *             b
     *           /   \
     *          a    d.e.f
     *              /  |  \____
     *             c   |       \
     *                 |        g.h
     *                 |         |
     *                w.y        i
     *              /  |  \     / \
     *             x   |   z   c   k
     *                 |   |
     *                 p   j
     *               /   \
     *              o     q
     */

    // Make a non-absolute label sequence. We will search for this same
    // sequence in two places in the tree.
    LabelSequence ls1(n1);
    ls1.stripRight(3);
    EXPECT_EQ("c", ls1.toText());

    // First, find "g.h."
    const Name n2("g.h");
    const LabelSequence ls2(n2);
    DomainTree<int>::Result result =
        dtree_expose_empty_node.find(ls2, &cdtnode, chain,
                                     testCallback, &flag);
    EXPECT_EQ(DomainTree<int>::EXACTMATCH, result);
    EXPECT_EQ(n2, chain.getAbsoluteName());

    // Now, find "c.g.h." by searching just the non-absolute ls1 label
    // sequence.
    result = dtree_expose_empty_node.find(ls1, &cdtnode, chain,
                                          testCallback, &flag);
    EXPECT_EQ(DomainTree<int>::EXACTMATCH, result);
    EXPECT_EQ(n1, chain.getAbsoluteName());

    // Now, find "." (the root node)
    chain.clear();
    const Name n3(".");
    const LabelSequence ls3(n3);
    result =
        dtree_expose_empty_node.find(ls3, &cdtnode, chain,
                                     testCallback, &flag);
    EXPECT_EQ(DomainTree<int>::EXACTMATCH, result);
    EXPECT_EQ(n3, chain.getAbsoluteName());

    // Now, find "c." by searching just the non-absolute ls1 label
    // sequence.
    result = dtree_expose_empty_node.find(ls1, &cdtnode, chain,
                                          testCallback, &flag);
    EXPECT_EQ(DomainTree<int>::EXACTMATCH, result);
    EXPECT_EQ(Name("c."), chain.getAbsoluteName());
}

TEST_F(DomainTreeTest, chainLevel) {
    TestDomainTreeNodeChain chain;

    // by default there should be no level in the chain.
    EXPECT_EQ(0, chain.getLevelCount());

    // Copy should be consistent
    TestDomainTreeNodeChain chain2(chain);
    EXPECT_EQ(chain.getLevelCount(), chain2.getLevelCount());

    // insert one node to the tree and find it.  there should be exactly
    // one level in the chain.
    TreeHolder tree_holder(mem_sgmt_, TestDomainTree::create(mem_sgmt_, true));
    TestDomainTree& tree(*tree_holder.get());
    Name node_name(Name::ROOT_NAME());
    EXPECT_EQ(TestDomainTree::SUCCESS, tree.insert(mem_sgmt_, node_name,
                                                &dtnode));
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              tree.find(node_name, &cdtnode, chain));
    EXPECT_EQ(1, chain.getLevelCount());

    // Copy should be consistent
    TestDomainTreeNodeChain chain3(chain);
    EXPECT_EQ(chain.getLevelCount(), chain3.getLevelCount());
    EXPECT_EQ(chain.getAbsoluteName(), chain3.getAbsoluteName());

    // Check the name of the found node (should have '.' as both non-absolute
    // and absolute name
    EXPECT_EQ(".", cdtnode->getLabels().toText());
    EXPECT_EQ(".", cdtnode->getAbsoluteLabels(buf).toText());

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
        EXPECT_EQ(TestDomainTree::SUCCESS, tree.insert(mem_sgmt_, node_name,
                                                    &dtnode));
        TestDomainTreeNodeChain found_chain;
        EXPECT_EQ(TestDomainTree::EXACTMATCH,
                  tree.find(node_name, &cdtnode, found_chain));
        EXPECT_EQ(i, found_chain.getLevelCount());

        // The non-absolute name should only have the first label
        EXPECT_EQ("a", cdtnode->getLabels().toText());
        // But the absolute name should have all labels
        EXPECT_EQ(node_name.toText(),
                  cdtnode->getAbsoluteLabels(buf).toText());
    }

    // Confirm the last inserted name has the possible maximum length with
    // maximum label count.  This confirms the dtree and chain level cannot
    // be larger.
    EXPECT_EQ(Name::MAX_LABELS, node_name.getLabelCount());
    EXPECT_THROW(node_name.concatenate(Name("a.")), TooLongName);
}

TEST_F(DomainTreeTest, getAbsoluteNameError) {
    // an empty chain isn't allowed.
    TestDomainTreeNodeChain chain;
    EXPECT_THROW(chain.getAbsoluteName(), BadValue);
}

TEST_F(DomainTreeTest, getUpperNode) {
    TestDomainTreeNodeChain node_path;
    const TestDomainTreeNode* node = NULL;
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name(ordered_names[0]),
                                           &node,
                                           node_path));
    for (int i = 0; i < ordered_names_count; ++i) {
        EXPECT_NE(static_cast<void*>(NULL), node);

        const TestDomainTreeNode* upper_node = node->getUpperNode();
        if (upper_node_names[i] != NULL) {
            const TestDomainTreeNode* upper_node2 = NULL;
            EXPECT_EQ(TestDomainTree::EXACTMATCH,
                      dtree_expose_empty_node.find(Name(upper_node_names[i]),
                                                    &upper_node2));
            EXPECT_NE(static_cast<void*>(NULL), upper_node2);
            EXPECT_EQ(upper_node, upper_node2);
        } else {
            EXPECT_EQ(static_cast<void*>(NULL), upper_node);
        }

        node = dtree_expose_empty_node.nextNode(node_path);
    }

    // We should have reached the end of the tree.
    EXPECT_EQ(static_cast<void*>(NULL), node);
}


#if 0
// Disabled and kept still, for use in case we make getSubTreeRoot() a
// public function again.

const char* const subtree_root_node_names[] = {
    "b", "b", "b", "b", "w.y.d.e.f", "w.y.d.e.f", "p.w.y.d.e.f",
    "p.w.y.d.e.f", "p.w.y.d.e.f", "w.y.d.e.f", "j.z.d.e.f",
    "b", "i.g.h", "i.g.h"};

TEST_F(DomainTreeTest, getSubTreeRoot) {
    TestDomainTreeNodeChain node_path;
    const TestDomainTreeNode* node = NULL;
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree_expose_empty_node.find(Name(ordered_names[0]),
                                            &node,
                                            node_path));
    for (int i = 0; i < name_count; ++i) {
        EXPECT_NE(static_cast<void*>(NULL), node);

        const TestDomainTreeNode* sr_node = node->getSubTreeRoot();
        if (subtree_root_node_names[i] != NULL) {
            const TestDomainTreeNode* sr_node2 = NULL;
            EXPECT_EQ(TestDomainTree::EXACTMATCH,
                dtree_expose_empty_node.find(Name(subtree_root_node_names[i]),
                                             &sr_node2));
            EXPECT_NE(static_cast<void*>(NULL), sr_node2);
            EXPECT_EQ(sr_node, sr_node2);
        } else {
            EXPECT_EQ(static_cast<void*>(NULL), sr_node);
        }

        node = dtree_expose_empty_node.nextNode(node_path);
    }

    // We should have reached the end of the tree.
    EXPECT_EQ(static_cast<void*>(NULL), node);
}

#endif // disabled getSubTreeRoot()


TEST_F(DomainTreeTest, nextNode) {
    TestDomainTreeNodeChain node_path;
    const TestDomainTreeNode* node = NULL;
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              dtree.find(Name(ordered_names[0]), &node, node_path));
    for (int i = 0; i < ordered_names_count; ++i) {
        EXPECT_NE(static_cast<void*>(NULL), node);
        EXPECT_EQ(Name(ordered_names[i]), node_path.getAbsoluteName());
        node = dtree.nextNode(node_path);
    }

    // We should have reached the end of the tree.
    EXPECT_EQ(static_cast<void*>(NULL), node);
}

// Just walk using previousNode until the beginning of the tree and check it is
// OK
//
// dtree - the tree to walk
// node - result of previous call to find(), starting position of the walk
// node_path - the path from the previous call to find(), will be modified
// chain_length - the number of names that should be in the chain to be walked
//   (0 means it should be empty, 3 means 'a', 'b' and 'c' should be there -
//   this is always from the beginning of the ordered_names[] list).
// skip_first - if this is false, the node should already contain the node with
//   the first name of the chain. If it is true, the node should be NULL
//   (true is for finds that return no match, false for the ones that return
//   match)
void
previousWalk(TestDomainTree& dtree, const TestDomainTreeNode* node,
             TestDomainTreeNodeChain& node_path, size_t chain_length,
             bool skip_first)
{
    if (skip_first) {
        // If the first is not found, this is supposed to be NULL and we skip
        // it in our checks.
        EXPECT_EQ(static_cast<void*>(NULL), node);
        node = dtree.previousNode(node_path);
    }
    for (size_t i(chain_length); i > 0; --i) {
        EXPECT_NE(static_cast<void*>(NULL), node);
        EXPECT_EQ(Name(ordered_names[i - 1]), node_path.getAbsoluteName());
        // Find the node at the path and check the value is the same
        // (that it really returns the correct corresponding node)
        //
        // The "empty" nodes can not be found
        if (node->getData()) {
            const TestDomainTreeNode* node2(NULL);
            TestDomainTreeNodeChain node_path2;
            EXPECT_EQ(TestDomainTree::EXACTMATCH,
                      dtree.find(Name(ordered_names[i - 1]),
                                 &node2, node_path2));
            EXPECT_EQ(node, node2);
        }
        node = dtree.previousNode(node_path);
    }

    // We should have reached the start of the tree.
    ASSERT_NE(static_cast<void*>(NULL), node);
    EXPECT_EQ(".", node->getLabels().toText());

    // With one more call it results in NULL
    node = dtree.previousNode(node_path);
    EXPECT_EQ(static_cast<void*>(NULL), node);

    // Calling previousNode() yet again should still return NULL without
    // fail.
    node = dtree.previousNode(node_path);
    EXPECT_EQ(static_cast<void*>(NULL), node);
}

// Check the previousNode
TEST_F(DomainTreeTest, previousNode) {
    // First, iterate the whole tree from the end to the beginning.
    TestDomainTreeNodeChain node_path;
    EXPECT_THROW(dtree.previousNode(node_path), isc::BadValue) <<
        "Throw before a search was done on the path";
    const TestDomainTreeNode* node(NULL);
    {
        SCOPED_TRACE("Iterate through");
        EXPECT_EQ(TestDomainTree::EXACTMATCH,
                  dtree.find(Name(ordered_names[ordered_names_count - 1]),
                             &node, node_path));
        previousWalk(dtree, node, node_path, ordered_names_count, false);
        node = NULL;
        node_path.clear();
    }

    {
        SCOPED_TRACE("Iterate from the middle");
        // Now, start somewhere in the middle, but within the real node.
        EXPECT_EQ(TestDomainTree::EXACTMATCH,
                  dtree.find(Name(ordered_names[4]), &node, node_path));
        previousWalk(dtree, node, node_path, 5, false);
        node = NULL;
        node_path.clear();
    }

    {
        SCOPED_TRACE("Start at the first");
        // If we start at the lowest (which is "a"), we get to the beginning
        // right away.
        EXPECT_EQ(TestDomainTree::EXACTMATCH,
                  dtree.find(Name(ordered_names[0]), &node, node_path));
        EXPECT_NE(static_cast<void*>(NULL), node);
        node = dtree.previousNode(node_path);
        ASSERT_NE(static_cast<void*>(NULL), node);
        EXPECT_EQ(".", node->getLabels().toText());
        node = NULL;
        node_path.clear();
    }

    {
        SCOPED_TRACE("Start before the first");
        // If we start before the lowest (. < 0. < a.), we should not get a
        // node.  Its previous node should be the root.
        EXPECT_EQ(TestDomainTree::NOTFOUND,
                  dtree.find<void*>(Name("0"), &node, node_path, NULL, NULL));
        EXPECT_EQ(static_cast<void*>(NULL), node);
        node = dtree.previousNode(node_path);
        ASSERT_NE(static_cast<void*>(NULL), node);
        EXPECT_EQ(".", node->getLabels().toText());
        node = NULL;
        node_path.clear();
    }

    {
        SCOPED_TRACE("Start after the last");
        EXPECT_EQ(TestDomainTree::NOTFOUND,
                  dtree.find(Name("z"), &node, node_path));
        previousWalk(dtree, node, node_path, ordered_names_count, true);
        node = NULL;
        node_path.clear();
    }

    {
        SCOPED_TRACE("Start below a leaf");
        // We exit a leaf by going down. We should start by the one
        // we exited - 'c' (actually, we should get it by the find, as partial
        // match).
        EXPECT_EQ(TestDomainTree::PARTIALMATCH,
                  dtree.find(Name("b.c"), &node, node_path));
        previousWalk(dtree, node, node_path, 3, false);
        node = NULL;
        node_path.clear();
    }

    {
        SCOPED_TRACE("Start to the right of a leaf");
        // When searching for this, we exit the 'x' node to the right side,
        // so we should go x afterwards.

        // The d.e.f is empty node, so it is hidden by find. Therefore NOTFOUND
        // and not PARTIALMATCH.
        EXPECT_EQ(TestDomainTree::NOTFOUND,
                  dtree.find(Name("xy.d.e.f"), &node, node_path));
        previousWalk(dtree, node, node_path, 5, true);
        node = NULL;
        node_path.clear();
    }

    {
        SCOPED_TRACE("Start to the left of a leaf");
        // This is similar to the previous, but we exit the 'z' leaf to the
        // left side, so should not visit z at all then.

        // The d.e.f is empty node, so it is hidden by find. Therefore NOTFOUND
        // and not PARTIALMATCH.
        EXPECT_EQ(TestDomainTree::NOTFOUND,
                  dtree.find(Name("yz.d.e.f"), &node, node_path));
        previousWalk(dtree, node, node_path, 9, true);
        node = NULL;
        node_path.clear();
    }

    {
        SCOPED_TRACE("Start to the right of a parent");
        // When searching for this, we exit the 'g.h' node to the right
        // side, so we should go to g.h's children afterwards.

        // 'g.h' is an empty node, so we get a NOTFOUND and not
        // PARTIALMATCH.
        EXPECT_EQ(TestDomainTree::NOTFOUND,
                  dtree.find(Name("x.h"), &node, node_path));
        // 'g.h' is the COMMONANCESTOR.
        EXPECT_EQ(node_path.getLastComparedNode()->getName(), Name("g.h"));
        EXPECT_EQ(NameComparisonResult::COMMONANCESTOR,
                  node_path.getLastComparisonResult().getRelation());
        // find() exits to the right of 'g.h'
        EXPECT_GT(node_path.getLastComparisonResult().getOrder(), 0);
        // We then descend into 'i.g.h' and walk all the nodes in the
        // tree.
        previousWalk(dtree, node, node_path, ordered_names_count, true);
        node = NULL;
        node_path.clear();
    }

    {
        SCOPED_TRACE("Start inside a wrong node");
        // The d.e.f is a single node, but we want only part of it. We
        // should start iterating before it.
        EXPECT_EQ(TestDomainTree::NOTFOUND,
                  dtree.find(Name("e.f"), &node, node_path));
        previousWalk(dtree, node, node_path, 3, true);
        node = NULL;
        node_path.clear();
    }

    {
        SCOPED_TRACE("Lookup in empty tree");
        // Just check it doesn't crash, etc.
        TreeHolder tree_holder(mem_sgmt_, TestDomainTree::create(mem_sgmt_));
        TestDomainTree& empty_tree(*tree_holder.get());
        EXPECT_EQ(TestDomainTree::NOTFOUND,
                  empty_tree.find(Name("x"), &node, node_path));
        EXPECT_EQ(static_cast<void*>(NULL), node);
        EXPECT_EQ(static_cast<void*>(NULL),
                  empty_tree.previousNode(node_path));
        node = NULL;
        node_path.clear();
    }
}

TEST_F(DomainTreeTest, largestNode) {
    cdtnode = dtree.largestNode();
    EXPECT_EQ(Name("k"), cdtnode->getName());

    // Check for largest node in an empty tree.
    TreeHolder empty_tree_holder
        (mem_sgmt_, TestDomainTree::create(mem_sgmt_));
    TestDomainTree& empty_tree(*empty_tree_holder.get());
    EXPECT_EQ(static_cast<void*>(NULL), empty_tree.largestNode());
}

TEST_F(DomainTreeTest, nextNodeError) {
    // Empty chain for nextNode() is invalid.
    TestDomainTreeNodeChain chain;
    EXPECT_THROW(dtree.nextNode(chain), BadValue);
}

// A helper function for getLastComparedNode() below.
void
comparisonChecks(const TestDomainTreeNodeChain& chain,
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

TEST_F(DomainTreeTest, getLastComparedNode) {
    TestDomainTree& tree = dtree_expose_empty_node; // use the "empty OK" mode
    TestDomainTreeNodeChain chain;

    // initially there should be no 'last compared'.
    EXPECT_EQ(static_cast<void*>(NULL), chain.getLastComparedNode());

    // A search for an empty tree should result in no 'last compared', too.
    TreeHolder tree_holder(mem_sgmt_, TestDomainTree::create(mem_sgmt_));
    TestDomainTree& empty_tree(*tree_holder.get());
    EXPECT_EQ(TestDomainTree::NOTFOUND,
              empty_tree.find(Name("a"), &cdtnode, chain));
    EXPECT_EQ(static_cast<void*>(NULL), chain.getLastComparedNode());
    chain.clear();

    const TestDomainTreeNode* expected_node = NULL;

    // Exact match case.  The returned node should be last compared.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              tree.find(Name("x.d.e.f"), &expected_node, chain));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // 1 = # labels of "x" (note: excluding ".")
    comparisonChecks(chain, 0, 1, NameComparisonResult::EQUAL);
    chain.clear();

    // Partial match, search stopped at the matching node, which should be
    // the last compared node.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              tree.find(Name("k.g.h"), &expected_node));
    EXPECT_EQ(TestDomainTree::PARTIALMATCH,
              tree.find(Name("x.k.g.h"), &cdtnode, chain));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // k.g.h < x.k.g.h, 1 = # labels of "k"
    comparisonChecks(chain, 1, 1, NameComparisonResult::SUBDOMAIN);
    chain.clear();

    // Partial match, search stopped in the subtree below the matching node
    // after following a left branch.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              tree.find(Name("x.d.e.f"), &expected_node));
    EXPECT_EQ(TestDomainTree::PARTIALMATCH,
              tree.find(Name("a.d.e.f"), &cdtnode, chain));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // a < x, no common labels
    comparisonChecks(chain, -1, 0, NameComparisonResult::NONE);
    chain.clear();

    // Partial match, search stopped in the subtree below the matching node
    // after following a right branch.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              tree.find(Name("z.d.e.f"), &expected_node));
    EXPECT_EQ(TestDomainTree::PARTIALMATCH,
              tree.find(Name("zz.d.e.f"), &cdtnode, chain));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // zz > z, no common label
    comparisonChecks(chain, 1, 0, NameComparisonResult::NONE);
    chain.clear();

    // Partial match, search stopped at a node for a super domain of the
    // search name in the subtree below the matching node.
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              tree.find(Name("w.y.d.e.f"), &expected_node));
    EXPECT_EQ(TestDomainTree::PARTIALMATCH,
              tree.find(Name("y.d.e.f"), &cdtnode, chain));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // y < w.y, 1 = # labels of "y"
    comparisonChecks(chain, -1, 1, NameComparisonResult::SUPERDOMAIN);
    chain.clear();

    // Partial match, search stopped at a node that share a common ancestor
    // with the search name in the subtree below the matching node.
    // (the expected node is the same as the previous case)
    EXPECT_EQ(TestDomainTree::PARTIALMATCH,
              tree.find(Name("z.y.d.e.f"), &cdtnode, chain));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // z.y > w.y, 1 = # labels of "y"
    comparisonChecks(chain, 1, 1, NameComparisonResult::COMMONANCESTOR);
    chain.clear();

    // Search stops in the highest level (under ".") after following a left
    // branch. (find() still returns PARTIALMATCH due to the top level ".")
    EXPECT_EQ(TestDomainTree::EXACTMATCH, tree.find(Name("c"), &expected_node));
    EXPECT_EQ(TestDomainTree::PARTIALMATCH,
              tree.find(Name("bb"), &cdtnode, chain));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // bb < c, no common label
    comparisonChecks(chain, -1, 0, NameComparisonResult::NONE);
    chain.clear();

    // Search stops in the highest level (under ".") after following a right
    // branch. (the expected node is the same as the previous case)
    EXPECT_EQ(TestDomainTree::PARTIALMATCH,
              tree.find(Name("d"), &cdtnode, chain));
    EXPECT_EQ(expected_node, chain.getLastComparedNode());
    // d > c, no common label
    comparisonChecks(chain, 1, 0, NameComparisonResult::NONE);
    chain.clear();
}

TEST_F(DomainTreeTest, dumpTree) {
    std::ostringstream str;
    std::ostringstream str2;
    dtree.dumpTree(str);
    str2 << "tree has 15 node(s)\n"
            ". (black) [invisible] [subtreeroot]\n"
            "     begin down from .\n"
            "     b (black) [subtreeroot]\n"
            "          a (black)\n"
            "               NULL\n"
            "               NULL\n"
            "          d.e.f (black) [invisible]\n"
            "               begin down from d.e.f\n"
            "               w.y (black) [invisible] [subtreeroot]\n"
            "                    begin down from w.y\n"
            "                    p (black) [subtreeroot]\n"
            "                         o (red)\n"
            "                              NULL\n"
            "                              NULL\n"
            "                         q (red)\n"
            "                              NULL\n"
            "                              NULL\n"
            "                    end down from w.y\n"
            "                    x (red)\n"
            "                         NULL\n"
            "                         NULL\n"
            "                    z (red)\n"
            "                         begin down from z\n"
            "                         j (black) [subtreeroot]\n"
            "                              NULL\n"
            "                              NULL\n"
            "                         end down from z\n"
            "                         NULL\n"
            "                         NULL\n"
            "               end down from d.e.f\n"
            "               c (red)\n"
            "                    NULL\n"
            "                    NULL\n"
            "               g.h (red)\n"
            "                    begin down from g.h\n"
            "                    i (black) [subtreeroot]\n"
            "                         NULL\n"
            "                         k (red)\n"
            "                              NULL\n"
            "                              NULL\n"
            "                    end down from g.h\n"
            "                    NULL\n"
            "                    NULL\n"
            "     end down from .\n"
            "     NULL\n"
            "     NULL\n";
    EXPECT_EQ(str2.str(), str.str());
}

TEST_F(DomainTreeTest, swap) {
    // Store info about the first tree
    std::ostringstream str1;
    dtree.dumpTree(str1);
    size_t count1(dtree.getNodeCount());

    // Create second one and store state
    TreeHolder tree_holder(mem_sgmt_, TestDomainTree::create(mem_sgmt_));
    TestDomainTree& tree2(*tree_holder.get());
    TestDomainTreeNode* node;
    tree2.insert(mem_sgmt_, Name("second"), &node);
    std::ostringstream str2;
    tree2.dumpTree(str2);

    // Swap them
    ASSERT_NO_THROW(tree2.swap(dtree));

    // Check their sizes
    ASSERT_EQ(1, dtree.getNodeCount());
    ASSERT_EQ(count1, tree2.getNodeCount());

    // And content
    std::ostringstream out;
    dtree.dumpTree(out);
    ASSERT_EQ(str2.str(), out.str());
    out.str("");
    tree2.dumpTree(out);
    ASSERT_EQ(str1.str(), out.str());
}

// Matching in the "root zone" may be special (e.g. there's no parent,
// any domain names should be considered a subdomain of it), so it makes
// sense to test cases with the root zone explicitly.
TEST_F(DomainTreeTest, root) {
    TreeHolder tree_holder(mem_sgmt_, TestDomainTree::create(mem_sgmt_));
    TestDomainTree& root(*tree_holder.get());
    root.insert(mem_sgmt_, Name::ROOT_NAME(), &dtnode);
    EXPECT_EQ(static_cast<int*>(NULL), dtnode->setData(new int(1)));

    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              root.find(Name::ROOT_NAME(), &cdtnode));
    EXPECT_EQ(dtnode, cdtnode);
    EXPECT_EQ(TestDomainTree::PARTIALMATCH,
              root.find(Name("example.com"), &cdtnode));
    EXPECT_EQ(dtnode, cdtnode);

    // Insert a new name that better matches the query name.  find() should
    // find the better one.
    root.insert(mem_sgmt_, Name("com"), &dtnode);
    EXPECT_EQ(static_cast<int*>(NULL), dtnode->setData(new int(2)));
    EXPECT_EQ(TestDomainTree::PARTIALMATCH,
              root.find(Name("example.com"), &cdtnode));
    EXPECT_EQ(dtnode, cdtnode);

    // Perform the same tests for the tree that allows matching against empty
    // nodes.
    TreeHolder tree_holder_emptyok(mem_sgmt_,
                                   TestDomainTree::create(mem_sgmt_, true));
    TestDomainTree& root_emptyok(*tree_holder_emptyok.get());
    root_emptyok.insert(mem_sgmt_, Name::ROOT_NAME(), &dtnode);
    EXPECT_EQ(TestDomainTree::EXACTMATCH,
              root_emptyok.find(Name::ROOT_NAME(), &cdtnode));
    EXPECT_EQ(dtnode, cdtnode);
    EXPECT_EQ(TestDomainTree::PARTIALMATCH,
              root_emptyok.find(Name("example.com"), &cdtnode));
    EXPECT_EQ(dtnode, cdtnode);

    root.insert(mem_sgmt_, Name("com"), &dtnode);
    EXPECT_EQ(TestDomainTree::PARTIALMATCH,
              root.find(Name("example.com"), &cdtnode));
    EXPECT_EQ(dtnode, cdtnode);
}

TEST_F(DomainTreeTest, getAbsoluteLabels) {
    // The names of the nodes themselves, as they end up in the tree
    const char* const first_labels[] = {
        "c", "b", "a", "x", "z", "g.h", "i", "o",
        "j", "p", "q", "k"};

    for (int i = 0; i < name_count; ++i) {
        EXPECT_EQ(TestDomainTree::EXACTMATCH, dtree.find(Name(domain_names[i]),
                  &cdtnode));

        // First make sure the names themselves are not absolute
        const LabelSequence ls(cdtnode->getLabels());
        EXPECT_EQ(first_labels[i], ls.toText());
        EXPECT_FALSE(ls.isAbsolute());

        // Now check the absolute names
        const LabelSequence abs_ls(cdtnode->getAbsoluteLabels(buf));
        EXPECT_EQ(Name(domain_names[i]).toText(), abs_ls.toText());
        EXPECT_TRUE(abs_ls.isAbsolute());
    }

    // Explicitly add and find a root node, to see that getAbsoluteLabels
    // also works when getLabels() already returns an absolute LabelSequence
    dtree.insert(mem_sgmt_, Name("."), &dtnode);
    dtnode->setData(new int(1));

    EXPECT_EQ(TestDomainTree::EXACTMATCH, dtree.find(Name("."), &cdtnode));

    EXPECT_TRUE(cdtnode->getLabels().isAbsolute());
    EXPECT_EQ(".", cdtnode->getLabels().toText());
    EXPECT_TRUE(cdtnode->getAbsoluteLabels(buf).isAbsolute());
    EXPECT_EQ(".", cdtnode->getAbsoluteLabels(buf).toText());
}
}
