// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/patricia_tree.h>
#include <exceptions/exceptions.h>
#include <gtest/gtest.h>
#include <arpa/inet.h>
#include <string>
#include <vector>

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

typedef PatriciaTree<Marker> Tree;
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
    EXPECT_EQ(0, tree4_.getNodeCount());
    EXPECT_FALSE(tree4_.findExact(pton(AF_INET, "10.0.0.0"), 8));
    EXPECT_FALSE(tree4_.findBest(pton(AF_INET, "10.0.0.1"), 32));

    size_t visits = 0;
    tree4_.findPath(pton(AF_INET, "10.0.0.1"),
                    [&visits](const NodePtr&) { ++visits; });
    EXPECT_EQ(0, visits);
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
    EXPECT_EQ(1, tree4_.getNodeCount());

    NodePtr found = tree4_.findExact(key, 24);
    ASSERT_TRUE(found);
    EXPECT_EQ(node, found);
    ASSERT_EQ(1, found->contents_.size());
    EXPECT_EQ(1, found->contents_.front().id_);

    EXPECT_FALSE(tree4_.findExact(key, 16));
    EXPECT_FALSE(tree4_.findExact(pton(AF_INET, "192.0.3.0"), 24));

    tree4_.remove(found);
    EXPECT_FALSE(tree4_.findExact(key, 24));
    EXPECT_EQ(0, tree4_.getNodeCount());
}

// Nested prefixes: path returns both; findBest returns the longer one.
TEST_F(PatriciaTreeTest, nestedPrefixes) {
    auto n8 = tree4_.insert(pton(AF_INET, "10.0.0.0"), 8);
    n8->contents_.push_back(Marker(8));
    auto n24 = tree4_.insert(pton(AF_INET, "10.0.0.0"), 24);
    n24->contents_.push_back(Marker(24));

    vector<int> path_ids;
    tree4_.findPath(pton(AF_INET, "10.0.0.5"),
                    [&path_ids](const NodePtr& n) {
                        path_ids.push_back(n->contents_.front().id_);
                    });
    ASSERT_EQ(2, path_ids.size());
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
    ASSERT_EQ(1, path_ids.size());
    EXPECT_EQ(8, path_ids[0]);

    best = tree4_.findBest(pton(AF_INET, "10.1.2.3"), 32);
    ASSERT_TRUE(best);
    EXPECT_EQ(8, best->contents_.front().id_);
}

// Disjoint prefixes only match their own branch.
TEST_F(PatriciaTreeTest, disjointPrefixes) {
    tree4_.insert(pton(AF_INET, "10.0.0.0"), 8)->contents_.push_back(Marker(10));
    tree4_.insert(pton(AF_INET, "192.0.2.0"), 24)->contents_.push_back(Marker(192));

    vector<int> path_ids;
    tree4_.findPath(pton(AF_INET, "10.9.9.9"),
                    [&path_ids](const NodePtr& n) {
                        path_ids.push_back(n->contents_.front().id_);
                    });
    ASSERT_EQ(1, path_ids.size());
    EXPECT_EQ(10, path_ids[0]);

    path_ids.clear();
    tree4_.findPath(pton(AF_INET, "192.0.2.10"),
                    [&path_ids](const NodePtr& n) {
                        path_ids.push_back(n->contents_.front().id_);
                    });
    ASSERT_EQ(1, path_ids.size());
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
    EXPECT_GT(tree4_.getNodeCount(), 2); // root glue + two leaves

    NodePtr to_remove = tree4_.findExact(pton(AF_INET, "11.0.0.0"), 8);
    ASSERT_TRUE(to_remove);
    tree4_.remove(to_remove);

    EXPECT_TRUE(tree4_.findExact(pton(AF_INET, "10.0.0.0"), 8));
    EXPECT_FALSE(tree4_.findExact(pton(AF_INET, "11.0.0.0"), 8));

    // After pruning, only the remaining prefix node should remain.
    EXPECT_EQ(1, tree4_.getNodeCount());
}

// Clear empties the tree; re-insert works.
TEST_F(PatriciaTreeTest, clearAndReinsert) {
    tree4_.insert(pton(AF_INET, "203.0.113.0"), 24);
    tree4_.insert(pton(AF_INET, "198.51.100.0"), 24);
    EXPECT_GT(tree4_.getNodeCount(), 0);

    tree4_.clear();
    EXPECT_EQ(0, tree4_.getNodeCount());
    EXPECT_FALSE(tree4_.findExact(pton(AF_INET, "203.0.113.0"), 24));

    auto node = tree4_.insert(pton(AF_INET, "203.0.113.0"), 24);
    ASSERT_TRUE(node);
    EXPECT_EQ(1, tree4_.getNodeCount());
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
    ASSERT_EQ(2, path_ids.size());
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
    EXPECT_EQ(1, second->contents_.size());
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
    ASSERT_EQ(2, path_ids.size());
    EXPECT_EQ(0, path_ids[0]);
    EXPECT_EQ(10, path_ids[1]);

    path_ids.clear();
    tree4_.findPath(pton(AF_INET, "192.0.2.1"),
                    [&path_ids](const NodePtr& n) {
                        path_ids.push_back(n->contents_.front().id_);
                    });
    ASSERT_EQ(1, path_ids.size());
    EXPECT_EQ(0, path_ids[0]);
}

} // namespace
