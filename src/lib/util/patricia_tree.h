// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PATRICIA_TREE_H
#define PATRICIA_TREE_H

#include <exceptions/exceptions.h>
#include <boost/shared_ptr.hpp>
#include <cstdint>
#include <cstring>
#include <functional>
#include <list>
#include <vector>

namespace isc {
namespace util {

/// @brief Node of a binary Patricia / radix tree for fixed-width bit keys.
///
/// @tparam ContentType Type of values stored at a prefix node.
template <typename ContentType>
struct PatriciaNode {
    /// @brief Shared pointer to a node.
    typedef boost::shared_ptr<PatriciaNode> NodePtr;

    /// @brief Parent node (null for the root).
    NodePtr parent_;

    /// @brief Child taken when the branch bit is 0.
    NodePtr left_;

    /// @brief Child taken when the branch bit is 1.
    NodePtr right_;

    /// @brief Values associated with this exact prefix (empty for glue).
    std::list<ContentType> contents_;

    /// @brief Bit index at which this node branches (0 .. key_bits).
    uint16_t bit_;

    /// @brief Stored prefix key bytes (empty when this is a glue-only node).
    std::vector<uint8_t> addr_;

    /// @brief Stored prefix length in bits (meaningful when @c addr_ is set).
    uint8_t len_;

    /// @brief Constructor.
    PatriciaNode() : parent_(), left_(), right_(), contents_(), bit_(0),
                     addr_(), len_(0) {
    }

    /// @brief True when this node holds a stored prefix.
    bool hasPrefix() const {
        return (!addr_.empty());
    }
};

/// @brief Binary Patricia tree over fixed-size network addresses.
///
/// Keys are MSB-first bit strings of length @c addr_size * 8 (typically 32 for
/// IPv4 and 128 for IPv6). Stored prefixes may be shorter than the full key
/// width. Glue nodes without a stored prefix exist only to branch.
///
/// @tparam ContentType Type of values stored at prefix nodes.
template <typename ContentType>
class PatriciaTree {
public:
    /// @brief Node type used by this tree.
    typedef PatriciaNode<ContentType> Node;

    /// @brief Shared pointer to a node.
    typedef typename Node::NodePtr NodePtr;

    /// @brief Constructor.
    ///
    /// @param addr_size Key width in octets (must be less than 32).
    /// @throw OutOfRange if @c addr_size is 0 or >= 32.
    explicit PatriciaTree(uint8_t addr_size)
        : addr_size_(addr_size), key_bits_(static_cast<uint16_t>(addr_size) * 8),
          node_count_(0), root_() {
        if ((addr_size == 0) || (addr_size >= 32)) {
            isc_throw(OutOfRange, "PatriciaTree address size must be in 1..31");
        }
    }

    /// @brief Destructor.
    ~PatriciaTree() {
        clear();
    }

    /// @brief Non-copyable (nodes form an ownership graph via shared_ptr).
    PatriciaTree(const PatriciaTree&) = delete;
    PatriciaTree& operator=(const PatriciaTree&) = delete;

    /// @brief Key width in octets.
    uint8_t getAddrSize() const {
        return (addr_size_);
    }

    /// @brief Number of allocated nodes (including glue).
    size_t getNodeCount() const {
        return (node_count_);
    }

    /// @brief Remove all nodes.
    void clear() {
        if (!root_) {
            return;
        }
        // Detach children iteratively to avoid deep recursion on destroy.
        std::vector<NodePtr> stack;
        stack.push_back(root_);
        root_.reset();
        while (!stack.empty()) {
            NodePtr node = stack.back();
            stack.pop_back();
            if (node->left_) {
                stack.push_back(node->left_);
            }
            if (node->right_) {
                stack.push_back(node->right_);
            }
            node->left_.reset();
            node->right_.reset();
            node->parent_.reset();
            node->contents_.clear();
            node->addr_.clear();
            --node_count_;
        }
    }

    /// @brief Find the node for an exact prefix.
    ///
    /// @param addr Prefix address bytes (@c addr_size long).
    /// @param len Prefix length in bits.
    /// @return Matching node or null.
    /// @throw BadValue / OutOfRange on invalid key.
    NodePtr findExact(const std::vector<uint8_t>& addr, uint8_t len) const {
        checkKey(addr, len);
        if (!root_) {
            return (NodePtr());
        }

        NodePtr node = root_;
        while (node && (node->bit_ < len)) {
            node = bitIsSet(addr, node->bit_) ? node->right_ : node->left_;
        }

        if (!node || !node->hasPrefix() || (node->len_ != len) ||
            !prefixEqual(node->addr_, addr, len)) {
            return (NodePtr());
        }
        return (node);
    }

    /// @brief Longest prefix match for a key of length @c len.
    ///
    /// @param addr Key bytes.
    /// @param len Number of significant bits in @c addr.
    /// @return Best matching stored prefix node or null.
    NodePtr findBest(const std::vector<uint8_t>& addr, uint8_t len) const {
        checkKey(addr, len);
        if (!root_) {
            return (NodePtr());
        }

        NodePtr best;
        NodePtr node = root_;
        while (node && (node->bit_ < len)) {
            if (node->hasPrefix() && (node->len_ <= len) &&
                prefixEqual(node->addr_, addr, node->len_)) {
                best = node;
            }
            node = bitIsSet(addr, node->bit_) ? node->right_ : node->left_;
        }

        if (node && node->hasPrefix() && (node->len_ <= len) &&
            prefixEqual(node->addr_, addr, node->len_)) {
            best = node;
        }
        return (best);
    }

    /// @brief Invoke @c fun for every stored prefix that contains @c addr.
    ///
    /// Callbacks are issued from shorter prefixes toward longer ones along
    /// the descent path.
    ///
    /// @param addr Full-width key (@c addr_size bytes).
    /// @param fun Callback invoked for each matching node.
    /// @throw BadValue if @c fun is empty or @c addr has the wrong size.
    void findPath(const std::vector<uint8_t>& addr,
                  const std::function<void(const NodePtr&)>& fun) const {
        if (!fun) {
            isc_throw(BadValue, "empty function (PatriciaTree::findPath)");
        }
        if (addr.size() != addr_size_) {
            isc_throw(BadValue, "bad address size (PatriciaTree::findPath)");
        }
        if (!root_) {
            return;
        }

        NodePtr node = root_;
        while (node) {
            if (node->hasPrefix() &&
                prefixEqual(node->addr_, addr, node->len_)) {
                fun(node);
            }
            if (node->bit_ >= key_bits_) {
                break;
            }
            node = bitIsSet(addr, node->bit_) ? node->right_ : node->left_;
        }
    }

    /// @brief Ensure a node exists for the given prefix and return it.
    ///
    /// If the exact prefix already exists, the existing node is returned.
    ///
    /// @param addr Prefix address bytes.
    /// @param len Prefix length in bits.
    /// @return Node for the prefix (payload list may still be empty).
    NodePtr insert(const std::vector<uint8_t>& addr, uint8_t len) {
        checkKey(addr, len);

        if (!root_) {
            NodePtr node = makeNode();
            node->bit_ = len;
            node->addr_ = addr;
            node->len_ = len;
            root_ = node;
            return (node);
        }

        // Walk as far as the key allows, stopping at a dead end.
        NodePtr node = root_;
        while (node && ((node->bit_ < len) || !node->hasPrefix())) {
            NodePtr next;
            if (node->bit_ < key_bits_) {
                next = bitIsSet(addr, node->bit_) ? node->right_ : node->left_;
            }
            if (!next) {
                break;
            }
            node = next;
        }

        // Find first differing bit between addr/len and node's stored key.
        uint16_t check = node->bit_;
        if (len < check) {
            check = len;
        }
        uint16_t differ = firstDiffBit(addr, node->addr_, check);
        if (differ > check) {
            differ = check;
        }

        // Ascend to the node that should become the attachment point.
        while (node->parent_ && (node->parent_->bit_ >= differ)) {
            node = node->parent_;
        }

        // Exact prefix already present (possibly as a former glue node).
        if ((differ == len) && (node->bit_ == len)) {
            if (!node->hasPrefix()) {
                node->addr_ = addr;
                node->len_ = len;
            }
            return (node);
        }

        NodePtr new_node = makeNode();
        new_node->bit_ = len;
        new_node->addr_ = addr;
        new_node->len_ = len;

        if (node->bit_ == differ) {
            // Attach as child of node.
            new_node->parent_ = node;
            if (bitIsSet(addr, node->bit_)) {
                node->right_ = new_node;
            } else {
                node->left_ = new_node;
            }
            return (new_node);
        }

        if (len == differ) {
            // New node becomes parent of node.
            if (bitIsSet(node->addr_, len)) {
                new_node->right_ = node;
            } else {
                new_node->left_ = node;
            }
            reparent(node, new_node);
            node->parent_ = new_node;
            return (new_node);
        }

        // Insert a glue node at the diverge bit.
        NodePtr glue = makeNode();
        glue->bit_ = differ;
        if (bitIsSet(addr, differ)) {
            glue->right_ = new_node;
            glue->left_ = node;
        } else {
            glue->left_ = new_node;
            glue->right_ = node;
        }
        new_node->parent_ = glue;
        reparent(node, glue);
        node->parent_ = glue;
        return (new_node);
    }

    /// @brief Remove a stored-prefix node (or clear its payload and prune).
    ///
    /// Clears the stored prefix and contents. If the node has both children it
    /// remains as glue. Otherwise it is unlinked and empty glue parents are
    /// pruned.
    ///
    /// @param node Node to remove (must belong to this tree).
    /// @throw BadValue if @c node is null.
    void remove(NodePtr& node) {
        if (!node) {
            isc_throw(BadValue, "null node (PatriciaTree::remove)");
        }

        node->addr_.clear();
        node->len_ = 0;
        node->contents_.clear();

        // Keep as glue when both children exist.
        if (node->left_ && node->right_) {
            return;
        }

        NodePtr child = node->left_ ? node->left_ : node->right_;
        NodePtr parent = node->parent_;

        if (child) {
            child->parent_ = parent;
        }

        if (!parent) {
            root_ = child;
        } else if (parent->left_ == node) {
            parent->left_ = child;
        } else {
            parent->right_ = child;
        }

        node->left_.reset();
        node->right_.reset();
        node->parent_.reset();
        destroyNode(node);
        node.reset();

        // Prune parent glue that lost its only reason to exist.
        if (parent && !parent->hasPrefix() &&
            !(parent->left_ && parent->right_)) {
            remove(parent);
        }
    }

private:
    /// @brief Validate key size and prefix length.
    void checkKey(const std::vector<uint8_t>& addr, uint8_t len) const {
        if (addr.size() != addr_size_) {
            isc_throw(BadValue, "bad address size for PatriciaTree");
        }
        if (len > key_bits_) {
            isc_throw(OutOfRange, "prefix length exceeds key width");
        }
    }

    /// @brief Test one bit in a key (MSB-first within each octet).
    static bool bitIsSet(const std::vector<uint8_t>& addr, uint16_t bit) {
        return ((addr[bit >> 3] & (0x80 >> (bit & 7))) != 0);
    }

    /// @brief Compare two keys for equality over @c len bits.
    static bool prefixEqual(const std::vector<uint8_t>& a,
                            const std::vector<uint8_t>& b,
                            uint8_t len) {
        if (len == 0) {
            return (true);
        }
        size_t full = len / 8;
        if ((full > 0) && (std::memcmp(&a[0], &b[0], full) != 0)) {
            return (false);
        }
        uint8_t rem = len % 8;
        if (rem == 0) {
            return (true);
        }
        uint8_t mask = static_cast<uint8_t>(0xff << (8 - rem));
        return ((a[full] & mask) == (b[full] & mask));
    }

    /// @brief Index of the first differing bit in [0, check), or @c check.
    static uint16_t firstDiffBit(const std::vector<uint8_t>& a,
                                 const std::vector<uint8_t>& b,
                                 uint16_t check) {
        uint16_t differ = 0;
        for (uint16_t i = 0; (i * 8) < check; ++i) {
            uint8_t x = static_cast<uint8_t>(a[i] ^ b[i]);
            if (x == 0) {
                differ = static_cast<uint16_t>((i + 1) * 8);
                continue;
            }
            for (uint8_t j = 0; j < 8; ++j) {
                if (x & (0x80 >> j)) {
                    return (static_cast<uint16_t>(i * 8 + j));
                }
            }
        }
        if (differ > check) {
            return (check);
        }
        return (differ);
    }

    /// @brief Make @c new_parent replace @c child in the child's old parent.
    void reparent(const NodePtr& child, const NodePtr& new_parent) {
        new_parent->parent_ = child->parent_;
        if (!child->parent_) {
            root_ = new_parent;
        } else if (child->parent_->left_ == child) {
            child->parent_->left_ = new_parent;
        } else {
            child->parent_->right_ = new_parent;
        }
    }

    /// @brief Allocate a node and account for it.
    NodePtr makeNode() {
        NodePtr node(new Node());
        ++node_count_;
        return (node);
    }

    /// @brief Account for destroying a node (pointer already detaching).
    void destroyNode(const NodePtr&) {
        if (node_count_ > 0) {
            --node_count_;
        }
    }

    /// @brief Key width in octets.
    const uint8_t addr_size_;

    /// @brief Key width in bits.
    const uint16_t key_bits_;

    /// @brief Allocated node count.
    size_t node_count_;

    /// @brief Root of the tree.
    NodePtr root_;
};

} // namespace util
} // namespace isc

#endif // PATRICIA_TREE_H
