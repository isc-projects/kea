// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/patricia_tree.h>

#include <list>
#include <string>

#include <gtest/gtest.h>

#include <arpa/inet.h>
#include <sys/socket.h>

using namespace isc;
using namespace isc::util;
using namespace std;

namespace {

/// @brief Payload type used in tests.
struct Marker {
    int id_;
    explicit Marker(int id) : id_(id) {
    }
};

typedef list<Marker> MarkerList;
typedef PatriciaTree<MarkerList> Tree;
typedef Tree::NodePtr NodePtr;

/// @brief Convert text address to key bytes.
vector<uint8_t>
pton(int family, const string& text) {
    vector<uint8_t> bin(family == AF_INET ? 4 : 16);
    if (inet_pton(family, text.c_str(), &bin[0]) != 1) {
        isc_throw(BadValue, "inet_pton failed for " << text);
    }
    return (bin);
}

/// @brief Fixture with v4 and v6 trees.
class PatriciaTreeTest : public ::testing::Test {
public:
    PatriciaTreeTest() : tree4_(4), tree6_(16) {
    }

    Tree tree4_;
    Tree tree6_;
};

// Empty tree lookups return null / invoke nothing.
TEST_F(PatriciaTreeTest, emptyTree) {
    EXPECT_EQ(0U, tree4_.getNodeCount());
    EXPECT_FALSE(tree4_.getRoot());
    EXPECT_FALSE(tree4_.findExact(pton(AF_INET, "10.0.0.0"), 8));
    EXPECT_FALSE(tree4_.findBest(pton(AF_INET, "10.0.0.1"), 32));

    size_t visits = 0;
    tree4_.findPath(pton(AF_INET, "10.0.0.1"),
                    [&visits](const NodePtr&) { ++visits; });
    EXPECT_EQ(0U, visits);
}

TEST_F(PatriciaTreeTest, rejectBadKeys) {
    EXPECT_THROW(Tree(0), OutOfRange);
    EXPECT_THROW(Tree(32), OutOfRange);

    vector<uint8_t> short_key(2, 0);
    EXPECT_THROW(tree4_.insert(short_key, 8), BadValue);
    EXPECT_THROW(tree4_.findExact(pton(AF_INET, "10.0.0.0"), 40), OutOfRange);
    EXPECT_THROW(tree4_.findPath(pton(AF_INET, "10.0.0.1"),
                                 std::function<void(const NodePtr&)>()),
                 BadValue);
}

// Insert, exact find, and remove a single IPv4 prefix.
TEST_F(PatriciaTreeTest, insertFindRemoveV4) {
    auto key = pton(AF_INET, "192.0.2.0");
    NodePtr node = tree4_.insert(key, 24);
    ASSERT_TRUE(node);
    node->contents_.push_back(Marker(1));
    EXPECT_EQ(1U, tree4_.getNodeCount());
    EXPECT_EQ(node, tree4_.getRoot());

    NodePtr found = tree4_.findExact(key, 24);
    ASSERT_TRUE(found);
    EXPECT_EQ(node, found);
    ASSERT_EQ(1U, found->contents_.size());
    EXPECT_EQ(1, found->contents_.front().id_);

    EXPECT_FALSE(tree4_.findExact(key, 16));
    EXPECT_FALSE(tree4_.findExact(pton(AF_INET, "192.0.3.0"), 24));

    tree4_.remove(found);
    EXPECT_FALSE(tree4_.findExact(key, 24));
    EXPECT_EQ(0U, tree4_.getNodeCount());
    EXPECT_FALSE(tree4_.getRoot());
}

// Nested prefixes: path returns both; findBest returns the longer one.
TEST_F(PatriciaTreeTest, nestedPrefixes) {
    auto n8 = tree4_.insert(pton(AF_INET, "10.0.0.0"), 8);
    n8->contents_.push_back(Marker(8));
    auto n24 = tree4_.insert(pton(AF_INET, "10.0.0.0"), 24);
    n24->contents_.push_back(Marker(24));

    // Two nodes: the root is n8 and n24 is its left.
    EXPECT_EQ(2U, tree4_.getNodeCount());
    EXPECT_EQ(n8, tree4_.getRoot());
    ASSERT_TRUE(n8->left_);
    EXPECT_EQ(n8->left_, n24);

    vector<int> path_ids;
    tree4_.findPath(pton(AF_INET, "10.0.0.5"),
                    [&path_ids](const NodePtr& n) {
                        path_ids.push_back(n->contents_.front().id_);
                    });
    ASSERT_EQ(2U, path_ids.size());
    EXPECT_EQ(8, path_ids[0]);
    EXPECT_EQ(24, path_ids[1]);

    NodePtr best = tree4_.findBest(pton(AF_INET, "10.0.0.5"), 32);
    ASSERT_TRUE(best);
    EXPECT_EQ(24, best->contents_.front().id_);

    // Address outside /24 but inside /8.
    path_ids.clear();
    tree4_.findPath(pton(AF_INET, "10.1.2.3"),
                    [&path_ids](const NodePtr& n) {
                        path_ids.push_back(n->contents_.front().id_);
                    });
    ASSERT_EQ(1U, path_ids.size());
    EXPECT_EQ(8, path_ids[0]);

    best = tree4_.findBest(pton(AF_INET, "10.1.2.3"), 32);
    ASSERT_TRUE(best);
    EXPECT_EQ(8, best->contents_.front().id_);
}

// Disjoint prefixes only match their own branch.
TEST_F(PatriciaTreeTest, disjointPrefixes) {
    tree4_.insert(pton(AF_INET, "10.0.0.0"), 8)->contents_.push_back(Marker(10));
    tree4_.insert(pton(AF_INET, "192.0.2.0"), 24)->contents_.push_back(Marker(192));
    // Three nodes: the root is a glue at the first bit,
    // 10.0.0.0/8 is left and 192.0.2.0/24 is right.
    EXPECT_EQ(3U, tree4_.getNodeCount());
    auto root = tree4_.getRoot();
    ASSERT_TRUE(root);
    EXPECT_FALSE(root->hasPrefix());
    EXPECT_EQ(0U, root->bit_);
    ASSERT_TRUE(root->left_);
    EXPECT_TRUE(root->left_->hasPrefix());
    EXPECT_EQ(pton(AF_INET, "10.0.0.0"), root->left_->addr_);
    EXPECT_EQ(8U, root->left_->len_);
    ASSERT_TRUE(root->right_);
    EXPECT_TRUE(root->right_->hasPrefix());
    EXPECT_EQ(pton(AF_INET, "192.0.2.0"), root->right_->addr_);
    EXPECT_EQ(24U, root->right_->len_);

    vector<int> path_ids;
    tree4_.findPath(pton(AF_INET, "10.9.9.9"),
                    [&path_ids](const NodePtr& n) {
                        path_ids.push_back(n->contents_.front().id_);
                    });
    ASSERT_EQ(1U, path_ids.size());
    EXPECT_EQ(10, path_ids[0]);

    path_ids.clear();
    tree4_.findPath(pton(AF_INET, "192.0.2.10"),
                    [&path_ids](const NodePtr& n) {
                        path_ids.push_back(n->contents_.front().id_);
                    });
    ASSERT_EQ(1U, path_ids.size());
    EXPECT_EQ(192, path_ids[0]);

    path_ids.clear();
    tree4_.findPath(pton(AF_INET, "172.16.0.1"),
                    [&path_ids](const NodePtr& n) {
                        path_ids.push_back(n->contents_.front().id_);
                    });
    EXPECT_TRUE(path_ids.empty());
}

// Removing one sibling leaves the other intact; glue is pruned.
TEST_F(PatriciaTreeTest, removePrunesGlue) {
    auto a = tree4_.insert(pton(AF_INET, "10.0.0.0"), 8);
    a->contents_.push_back(Marker(1));
    auto b = tree4_.insert(pton(AF_INET, "11.0.0.0"), 8);
    b->contents_.push_back(Marker(2));
    EXPECT_GT(tree4_.getNodeCount(), 2U); // root glue + two leaves
    EXPECT_FALSE(tree4_.getRoot()->hasPrefix());
    EXPECT_EQ(7U, tree4_.getRoot()->bit_);

    NodePtr to_remove = tree4_.findExact(pton(AF_INET, "11.0.0.0"), 8);
    ASSERT_TRUE(to_remove);
    EXPECT_EQ(b, to_remove);
    tree4_.remove(to_remove);

    EXPECT_TRUE(tree4_.findExact(pton(AF_INET, "10.0.0.0"), 8));
    EXPECT_FALSE(tree4_.findExact(pton(AF_INET, "11.0.0.0"), 8));

    // After pruning, only the remaining prefix node should remain.
    EXPECT_EQ(1U, tree4_.getNodeCount());
    EXPECT_EQ(a, tree4_.getRoot());
}

// Clear empties the tree; re-insert works.
TEST_F(PatriciaTreeTest, clearAndReinsert) {
    tree4_.insert(pton(AF_INET, "203.0.113.0"), 24);
    tree4_.insert(pton(AF_INET, "198.51.100.0"), 24);
    EXPECT_GT(tree4_.getNodeCount(), 0U);
    EXPECT_TRUE(tree4_.getRoot());

    tree4_.clear();
    EXPECT_EQ(0U, tree4_.getNodeCount());
    EXPECT_FALSE(tree4_.getRoot());
    EXPECT_FALSE(tree4_.findExact(pton(AF_INET, "203.0.113.0"), 24));

    auto node = tree4_.insert(pton(AF_INET, "203.0.113.0"), 24);
    ASSERT_TRUE(node);
    EXPECT_EQ(1U, tree4_.getNodeCount());
    EXPECT_EQ(node, tree4_.getRoot());
}

// IPv6 insert / path / best.
TEST_F(PatriciaTreeTest, ipv6) {
    auto n32 = tree6_.insert(pton(AF_INET6, "2001:db8::"), 32);
    n32->contents_.push_back(Marker(32));
    auto n64 = tree6_.insert(pton(AF_INET6, "2001:db8:1::"), 64);
    n64->contents_.push_back(Marker(64));

    vector<int> path_ids;
    tree6_.findPath(pton(AF_INET6, "2001:db8:1::5"),
                    [&path_ids](const NodePtr& n) {
                        path_ids.push_back(n->contents_.front().id_);
                    });
    ASSERT_EQ(2U, path_ids.size());
    EXPECT_EQ(32, path_ids[0]);
    EXPECT_EQ(64, path_ids[1]);

    NodePtr best = tree6_.findBest(pton(AF_INET6, "2001:db8:1::5"), 128);
    ASSERT_TRUE(best);
    EXPECT_EQ(64, best->contents_.front().id_);

    EXPECT_TRUE(tree6_.findExact(pton(AF_INET6, "2001:db8::"), 32));
    tree6_.remove(n32);
    EXPECT_FALSE(tree6_.findExact(pton(AF_INET6, "2001:db8::"), 32));
    EXPECT_TRUE(tree6_.findExact(pton(AF_INET6, "2001:db8:1::"), 64));
}

// Re-inserting the same prefix returns the same node.
TEST_F(PatriciaTreeTest, insertIdempotent) {
    auto first = tree4_.insert(pton(AF_INET, "172.16.0.0"), 12);
    first->contents_.push_back(Marker(1));
    auto second = tree4_.insert(pton(AF_INET, "172.16.0.0"), 12);
    EXPECT_EQ(first, second);
    EXPECT_EQ(1U, second->contents_.size());
}

// Default route /0 matches every address.
TEST_F(PatriciaTreeTest, defaultRoute) {
    auto def = tree4_.insert(pton(AF_INET, "0.0.0.0"), 0);
    def->contents_.push_back(Marker(0));
    auto specific = tree4_.insert(pton(AF_INET, "10.0.0.0"), 8);
    specific->contents_.push_back(Marker(10));

    vector<int> path_ids;
    tree4_.findPath(pton(AF_INET, "10.0.0.1"),
                    [&path_ids](const NodePtr& n) {
                        path_ids.push_back(n->contents_.front().id_);
                    });
    ASSERT_EQ(2U, path_ids.size());
    EXPECT_EQ(0, path_ids[0]);
    EXPECT_EQ(10, path_ids[1]);

    path_ids.clear();
    tree4_.findPath(pton(AF_INET, "192.0.2.1"),
                    [&path_ids](const NodePtr& n) {
                        path_ids.push_back(n->contents_.front().id_);
                    });
    ASSERT_EQ(1U, path_ids.size());
    EXPECT_EQ(0, path_ids[0]);
}

/// @brief Counting payload.
class CMarkerList {
public:
    static size_t counter_;
    static size_t overflow_;
    CMarkerList() : list_() {
        ++counter_;
    }
    ~CMarkerList() {
        if (counter_ == 0) {
            ++overflow_;
        } else {
            --counter_;
        }
    }
    void push_back(int id) {
        list_.push_back(Marker(id));
    }
    void clear() {
        list_.clear();
    }
    list<Marker> list_;
};

size_t CMarkerList::counter_ = 0;
size_t CMarkerList::overflow_ = 0;

typedef PatriciaTree<CMarkerList> CTree;

// Check tree build and clear.
TEST(PatriciaTreeCounterTest, clear) {
    CTree tree(4);
    int id = 0;
    CMarkerList::counter_ = 0;
    CMarkerList::overflow_ = 0;
    list<pair<string, uint8_t> > prefixes =  {
        { "192.0.2.0", 24 },
        { "10.0.0.0", 8 },
        { "10.0.0.0", 24 },
        { "11.0.0.0", 8 },
        { "203.0.113.0", 24 },
        { "198.51.100.0", 24 },
        { "172.16.0.0", 12 },
        { "0.0.0.0", 0 }
    };
    for (auto const& prefix : prefixes) {
        auto key = pton(AF_INET, prefix.first);
        auto node = tree.insert(key, prefix.second);
        ASSERT_TRUE(node);
        node->contents_.push_back(++id);
    };
    EXPECT_EQ(CMarkerList::counter_, tree.getNodeCount());
    tree.clear();
    EXPECT_EQ(0U, tree.getNodeCount());
    EXPECT_EQ(0U, CMarkerList::counter_);
    ASSERT_EQ(0U, CMarkerList::overflow_);
}

} // namespace
