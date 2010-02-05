#ifndef BOOST_SERIALIZATION_BINARY_OBJECT_HPP
#define BOOST_SERIALIZATION_BINARY_OBJECT_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// nvp.hpp: interface for serialization system.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cassert>

#include <cstddef> // std::size_t
#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ 
    using ::size_t; 
} // namespace std
#endif

#include <boost/preprocessor/stringize.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/wrapper.hpp>

namespace boost {
namespace serialization {

struct binary_object {
    /* const */ void * const m_t;
    const std::size_t m_size;
    template<class Archive>
    void save(Archive & ar, const unsigned int /* file_version */) const {
        ar.save_binary(m_t, m_size);
    }
    template<class Archive>
    void load(Archive & ar, const unsigned int /* file_version */) const {
        ar.load_binary(const_cast<void *>(m_t), m_size);
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
    binary_object(/* const */ void * const t, std::size_t size) :
        m_t(t),
        m_size(size)
    {}
    binary_object(const binary_object & rhs) :
        m_t(rhs.m_t),
        m_size(rhs.m_size)
    {}
};

// just a little helper to support the convention that all serialization
// wrappers follow the naming convention make_xxxxx
inline 
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
const
#endif
binary_object 
make_binary_object(/* const */ void * t, std::size_t size){
    return binary_object(t, size);
}

// this is a wrapper

template <>
struct is_wrapper<binary_object>
 : public mpl::true_
{};

} // namespace serialization
} // boost

// don't need versioning info for this type
BOOST_CLASS_IMPLEMENTATION(
    binary_object, 
    boost::serialization::object_serializable
)

// don't track binary objects - usually they will be created on the stack
// and tracking algorithm (which uses the object address) might get
// confused.  note that these address will likely be members of some
// other structure which itself is tracked, so as a practical matter
// suppressing tracking shouldn't cause any redundancy.

BOOST_CLASS_TRACKING(binary_object, boost::serialization::track_never) 

#endif // BOOST_SERIALIZATION_BINARY_OBJECT_HPP
