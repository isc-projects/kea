// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

namespace isc {
namespace cryptolink {
namespace ossl {

/// @brief Decode the HashAlgorithm enum into an EVP_MD pointer (or 0)
///
/// EVP_MD pointer is a OpenSSL's way of identifying hash algorithms
/// @param algorithm algorithm to be converted
/// @return pointer to a static EVP_MD which identifies the algorithm
const EVP_MD*
getHashAlgorithm(isc::cryptolink::HashAlgorithm algorithm);

/// Secure Buffers which are wiped out when released.
/// Subset of the std::vector interface but not derived from
/// to avoid unwanted inheritance.
template<typename T>
class SecBuf {
public:
    typedef typename std::vector<T>::iterator iterator;

    typedef typename std::vector<T>::const_iterator const_iterator;

    explicit SecBuf() : vec_(std::vector<T>()) {}

    explicit SecBuf(size_t n, const T& value = T()) :
        vec_(std::vector<T>(n, value))
    {}

    SecBuf(iterator first, iterator last) :
        vec_(std::vector<T>(first, last))
    {}

    SecBuf(const_iterator first, const_iterator last) :
        vec_(std::vector<T>(first, last))
    {}

    SecBuf(const std::vector<T>& x) : vec_(x) {}

    ~SecBuf() {
        std::memset(&vec_[0], 0, vec_.capacity() * sizeof(T));
    };

    iterator begin() {
        return (vec_.begin());
    };

    const_iterator begin() const {
        return (vec_.begin());
    };

    iterator end() {
        return (vec_.end());
    };

    const_iterator end() const {
        return (vec_.end());
    };

    size_t size() const {
        return (vec_.size());
    };

    void resize(size_t sz) {
        vec_.resize(sz);
    };

    SecBuf& operator=(const SecBuf& x) {
        if (&x != *this) {
            vec_ = x.vec_;
        }
        return (*this);
    };

    T& operator[](size_t n) {
        return (vec_[n]);
    };

    const T& operator[](size_t n) const {
        return (vec_[n]);
    };

    // constant time comparison against timing attacks
    // (same type than XXX::verify() so const void* (vs. const T*) x)
    bool same(const void* x, size_t len) const {
        bool ret = true;
        const T* p = static_cast<const T*>(x);
        for (size_t i = 0; i < len; ++i)
            ret = ret && (vec_[i] == p[i]);
        return ret;
    };

private:
    std::vector<T> vec_;
};

} // namespace ossl
} // namespace cryptolink
} // namespace isc
