#ifndef BOOST_DETAIL_LIGHTWEIGHT_TEST_HPP_INCLUDED
#define BOOST_DETAIL_LIGHTWEIGHT_TEST_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  boost/detail/lightweight_test.hpp - lightweight test library
//
//  Copyright (c) 2002, 2009 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  BOOST_TEST(expression)
//  BOOST_ERROR(message)
//  BOOST_TEST_EQ(expr1, expr2)
//
//  int boost::report_errors()
//

#include <boost/current_function.hpp>
#include <iostream>

namespace boost
{

namespace detail
{

inline int & test_errors()
{
    static int x = 0;
    return x;
}

inline void test_failed_impl(char const * expr, char const * file, int line, char const * function)
{
    std::cerr << file << "(" << line << "): test '" << expr << "' failed in function '" << function << "'" << std::endl;
    ++test_errors();
}

inline void error_impl(char const * msg, char const * file, int line, char const * function)
{
    std::cerr << file << "(" << line << "): " << msg << " in function '" << function << "'" << std::endl;
    ++test_errors();
}

template<class T, class U> inline void test_eq_impl( char const * expr1, char const * expr2, char const * file, int line, char const * function, T const & t, U const & u )
{
    if( t == u )
    {
    }
    else
    {
        std::cerr << file << "(" << line << "): test '" << expr1 << " == " << expr2
            << "' failed in function '" << function << "': "
            << "'" << t << "' != '" << u << "'" << std::endl;
        ++test_errors();
    }
}

} // namespace detail

inline int report_errors()
{
    int errors = detail::test_errors();

    if( errors == 0 )
    {
        std::cerr << "No errors detected." << std::endl;
        return 0;
    }
    else
    {
        std::cerr << errors << " error" << (errors == 1? "": "s") << " detected." << std::endl;
        return 1;
    }
}

} // namespace boost

#define BOOST_TEST(expr) ((expr)? (void)0: ::boost::detail::test_failed_impl(#expr, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION))
#define BOOST_ERROR(msg) ::boost::detail::error_impl(msg, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION)
#define BOOST_TEST_EQ(expr1,expr2) ( ::boost::detail::test_eq_impl(#expr1, #expr2, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, expr1, expr2) )

#endif // #ifndef BOOST_DETAIL_LIGHTWEIGHT_TEST_HPP_INCLUDED
