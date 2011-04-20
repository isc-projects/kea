#ifndef BOOST_ARCHIVE_ITERATORS_BINARY_FROM_BASE32HEX_HPP
#define BOOST_ARCHIVE_ITERATORS_BINARY_FROM_BASE32HEX_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_from_base32hex.h (derived from boost binary_from_base64.hpp)

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cassert>

// We use the same boost header files used in "_from_base64".  Since the
// precise path to these headers may vary depending on the boost version we
// simply include the base64 header here.
#include <boost/archive/iterators/binary_from_base64.hpp>

#include <exceptions/exceptions.h>

namespace boost { 
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// convert base32hex characters to binary data

namespace detail {

template<class CharType>
struct to_5_bit {
    typedef CharType result_type;
    CharType operator()(CharType t) const{
        const char lookup_table[] = {
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 00-0f
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 10-1f
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 20-2f
             0, 1, 2, 3, 4, 5, 6, 7, 8, 9,-1,-1,-1,-1,-1,-1, // 30-3f
            -1,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24, // 40-4f
            25,26,27,28,29,30,31,-1,-1,-1,-1,-1,-1,-1,-1,-1, // 50-5f
            -1,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24, // 60-6f
            25,26,27,28,29,30,31,-1,-1,-1,-1,-1,-1,-1,-1,-1  // 70-7f
        };
        // metrowerks trips this assertion - how come?
        #if ! defined(__MWERKS__)
        BOOST_STATIC_ASSERT(0x80 == sizeof(lookup_table));
        #endif
        signed char value = -1;
        if((unsigned)t < sizeof(lookup_table))
            value = lookup_table[(unsigned)t];
        if(-1 == value) { 
            isc_throw(isc::BadValue,
                      "attempt to decode a value not in base32hex char set");
        }
        return (value);
    }
};

} // namespace detail

// note: what we would like to do is
// template<class Base, class CharType = BOOST_DEDUCED_TYPENAME Base::value_type>
//  typedef transform_iterator<
//      from_5_bit<CharType>,
//      transform_width<Base, 5, sizeof(Base::value_type) * 8, CharType>
//  > base32hex_from_binary;
// but C++ won't accept this.  Rather than using a "type generator" and
// using a different syntax, make a derivation which should be equivalent.
//
// Another issue addressed here is that the transform_iterator doesn't have
// a templated constructor.  This makes it incompatible with the dataflow
// ideal.  This is also addressed here.

template<
    class Base, 
    class CharType = BOOST_DEDUCED_TYPENAME boost::iterator_value<Base>::type
>
class binary_from_base32hex : public
    transform_iterator<
        detail::to_5_bit<CharType>,
        Base
    >
{
    friend class boost::iterator_core_access;
    typedef transform_iterator<
        detail::to_5_bit<CharType>,
        Base
    > super_t;
public:
    // make composible buy using templated constructor
    template<class T>
    binary_from_base32hex(BOOST_PFTO_WRAPPER(T)  start) :
        super_t(
            Base(BOOST_MAKE_PFTO_WRAPPER(static_cast<T>(start))), 
            detail::to_5_bit<CharType>()
        )
    {}
    // intel 7.1 doesn't like default copy constructor
    binary_from_base32hex(const binary_from_base32hex & rhs) : 
        super_t(
            Base(rhs.base_reference()),
            detail::to_5_bit<CharType>()
        )
    {}
//    binary_from_base32hex(){};
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_BINARY_FROM_BASE32HEX_HPP

// Local Variables: 
// mode: c++
// End: 
