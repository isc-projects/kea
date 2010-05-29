//
// hash_map.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HASH_MAP_HPP
#define BOOST_ASIO_DETAIL_HASH_MAP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

#include <boost/asio/detail/push_options.hpp>
#include <cassert>
#include <list>
#include <utility>
#include <vector>
#include <boost/functional/hash.hpp>
#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/socket_types.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
inline std::size_t calculate_hash_value(const T& t)
{
  return boost::hash_value(t);
}

#if defined(_WIN64)
inline std::size_t calculate_hash_value(SOCKET s)
{
  return static_cast<std::size_t>(s);
}
#endif // defined(_WIN64)

// Note: assumes K and V are POD types.
template <typename K, typename V>
class hash_map
  : private noncopyable
{
public:
  // The type of a value in the map.
  typedef std::pair<K, V> value_type;

  // The type of a non-const iterator over the hash map.
  typedef typename std::list<value_type>::iterator iterator;

  // The type of a const iterator over the hash map.
  typedef typename std::list<value_type>::const_iterator const_iterator;

  // Constructor.
  hash_map()
    : size_(0)
  {
    rehash(hash_size(0));
  }

  // Get an iterator for the beginning of the map.
  iterator begin()
  {
    return values_.begin();
  }

  // Get an iterator for the beginning of the map.
  const_iterator begin() const
  {
    return values_.begin();
  }

  // Get an iterator for the end of the map.
  iterator end()
  {
    return values_.end();
  }

  // Get an iterator for the end of the map.
  const_iterator end() const
  {
    return values_.end();
  }

  // Check whether the map is empty.
  bool empty() const
  {
    return values_.empty();
  }

  // Find an entry in the map.
  iterator find(const K& k)
  {
    size_t bucket = calculate_hash_value(k) % buckets_.size();
    iterator it = buckets_[bucket].first;
    if (it == values_.end())
      return values_.end();
    iterator end = buckets_[bucket].last;
    ++end;
    while (it != end)
    {
      if (it->first == k)
        return it;
      ++it;
    }
    return values_.end();
  }

  // Find an entry in the map.
  const_iterator find(const K& k) const
  {
    size_t bucket = calculate_hash_value(k) % buckets_.size();
    const_iterator it = buckets_[bucket].first;
    if (it == values_.end())
      return it;
    const_iterator end = buckets_[bucket].last;
    ++end;
    while (it != end)
    {
      if (it->first == k)
        return it;
      ++it;
    }
    return values_.end();
  }

  // Insert a new entry into the map.
  std::pair<iterator, bool> insert(const value_type& v)
  {
    if (size_ + 1 >= buckets_.size())
      rehash(hash_size(size_ + 1));
    size_t bucket = calculate_hash_value(v.first) % buckets_.size();
    iterator it = buckets_[bucket].first;
    if (it == values_.end())
    {
      buckets_[bucket].first = buckets_[bucket].last =
        values_insert(values_.end(), v);
      ++size_;
      return std::pair<iterator, bool>(buckets_[bucket].last, true);
    }
    iterator end = buckets_[bucket].last;
    ++end;
    while (it != end)
    {
      if (it->first == v.first)
        return std::pair<iterator, bool>(it, false);
      ++it;
    }
    buckets_[bucket].last = values_insert(end, v);
    ++size_;
    return std::pair<iterator, bool>(buckets_[bucket].last, true);
  }

  // Erase an entry from the map.
  void erase(iterator it)
  {
    assert(it != values_.end());

    size_t bucket = calculate_hash_value(it->first) % buckets_.size();
    bool is_first = (it == buckets_[bucket].first);
    bool is_last = (it == buckets_[bucket].last);
    if (is_first && is_last)
      buckets_[bucket].first = buckets_[bucket].last = values_.end();
    else if (is_first)
      ++buckets_[bucket].first;
    else if (is_last)
      --buckets_[bucket].last;

    values_erase(it);
    --size_;
  }

  // Remove all entries from the map.
  void clear()
  {
    // Clear the values.
    values_.clear();
    size_ = 0;

    // Initialise all buckets to empty.
    for (size_t i = 0; i < buckets_.size(); ++i)
      buckets_[i].first = buckets_[i].last = values_.end();
  }

private:
  // Calculate the hash size for the specified number of elements.
  static std::size_t hash_size(std::size_t num_elems)
  {
    static std::size_t sizes[] =
    {
#if defined(BOOST_ASIO_HASH_MAP_BUCKETS)
      BOOST_ASIO_HASH_MAP_BUCKETS
#else // BOOST_ASIO_HASH_MAP_BUCKETS
      3, 13, 23, 53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,
      49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469,
      12582917, 25165843
#endif // BOOST_ASIO_HASH_MAP_BUCKETS
    };
    const std::size_t nth_size = sizeof(sizes) / sizeof(std::size_t) - 1;
    for (std::size_t i = 0; i < nth_size; ++i)
      if (num_elems < sizes[i])
        return sizes[i];
    return sizes[nth_size];
  }

  // Re-initialise the hash from the values already contained in the list.
  void rehash(std::size_t num_buckets)
  {
    if (num_buckets == buckets_.size())
      return;

    iterator end = values_.end();

    // Update number of buckets and initialise all buckets to empty.
    buckets_.resize(num_buckets);
    for (std::size_t i = 0; i < buckets_.size(); ++i)
      buckets_[i].first = buckets_[i].last = end;

    // Put all values back into the hash.
    iterator iter = values_.begin();
    while (iter != end)
    {
      std::size_t bucket = calculate_hash_value(iter->first) % buckets_.size();
      if (buckets_[bucket].last == end)
      {
        buckets_[bucket].first = buckets_[bucket].last = iter++;
      }
      else if (++buckets_[bucket].last == iter)
      {
        ++iter;
      }
      else
      {
        values_.splice(buckets_[bucket].last, values_, iter++);
        --buckets_[bucket].last;
      }
    }
  }

  // Insert an element into the values list by splicing from the spares list,
  // if a spare is available, and otherwise by inserting a new element.
  iterator values_insert(iterator it, const value_type& v)
  {
    if (spares_.empty())
    {
      return values_.insert(it, v);
    }
    else
    {
      spares_.front() = v;
      values_.splice(it, spares_, spares_.begin());
      return --it;
    }
  }

  // Erase an element from the values list by splicing it to the spares list.
  void values_erase(iterator it)
  {
    *it = value_type();
    spares_.splice(spares_.begin(), values_, it);
  }

  // The number of elements in the hash.
  std::size_t size_;

  // The list of all values in the hash map.
  std::list<value_type> values_;

  // The list of spare nodes waiting to be recycled. Assumes that POD types only
  // are stored in the hash map.
  std::list<value_type> spares_;

  // The type for a bucket in the hash table.
  struct bucket_type
  {
    bucket_type() {}
    bucket_type(const bucket_type&) { /* noop */ }
    iterator first;
    iterator last;
  };

  // The buckets in the hash.
  std::vector<bucket_type> buckets_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_HASH_MAP_HPP
